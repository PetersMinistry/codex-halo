// Rainmeter Codex Halo
// Fetches the same usage payload the Codex app uses for its account menu.

const fs = require('fs');
const https = require('https');
const os = require('os');
const path = require('path');

const usageUrl = 'https://chatgpt.com/backend-api/wham/usage';

function directoryExists(value) {
  try {
    return value && fs.statSync(value).isDirectory();
  } catch {
    return false;
  }
}

function getCodexRoot() {
  if (directoryExists(process.env.CODEX_HOME)) {
    return process.env.CODEX_HOME;
  }

  const profile = process.env.USERPROFILE || os.homedir();
  const fallback = path.join(profile, '.codex');
  return directoryExists(fallback) ? fallback : null;
}

function pickWindow(window) {
  if (!window) {
    return null;
  }

  return {
    used_percent: Number(window.used_percent || 0),
    reset_at: Number(window.reset_at || 0),
    limit_window_seconds: Number(window.limit_window_seconds || 0),
  };
}

function pickRateLimit(usage) {
  const candidates = [];
  if (usage.rate_limit && usage.rate_limit.primary_window && usage.rate_limit.secondary_window) {
    candidates.push({
      name: usage.rate_limit_name || 'root',
      rateLimit: usage.rate_limit,
      isAdditional: false,
    });
  }

  const additionalLimits = Array.isArray(usage.additional_rate_limits)
    ? usage.additional_rate_limits
    : [];
  for (const item of additionalLimits) {
    if (item && item.rate_limit && item.rate_limit.primary_window && item.rate_limit.secondary_window) {
      candidates.push({
        name: item.limit_name || item.rate_limit_name || 'additional',
        rateLimit: item.rate_limit,
        isAdditional: true,
      });
    }
  }

  candidates.sort((left, right) => {
    const leftReset = Number(left.rateLimit.secondary_window.reset_at || 0);
    const rightReset = Number(right.rateLimit.secondary_window.reset_at || 0);
    if (rightReset !== leftReset) {
      return rightReset - leftReset;
    }

    return Number(right.isAdditional) - Number(left.isAdditional);
  });

  return candidates[0] || { name: null, rateLimit: null, isAdditional: false };
}

function getJson(url, accessToken, redirectsRemaining = 2) {
  return new Promise((resolve, reject) => {
    const request = https.request(
      url,
      {
        method: 'GET',
        headers: {
          Authorization: `Bearer ${accessToken}`,
          Accept: 'application/json',
          'User-Agent': 'Codex-Halo/0.5',
        },
        timeout: 12000,
      },
      (response) => {
        if (
          response.statusCode >= 300 &&
          response.statusCode < 400 &&
          response.headers.location &&
          redirectsRemaining > 0
        ) {
          response.resume();
          const nextUrl = new URL(response.headers.location, url).toString();
          getJson(nextUrl, accessToken, redirectsRemaining - 1).then(resolve, reject);
          return;
        }

        let body = '';
        response.setEncoding('utf8');
        response.on('data', (chunk) => {
          body += chunk;
        });
        response.on('end', () => {
          if (response.statusCode < 200 || response.statusCode >= 300) {
            reject(new Error(`HTTP ${response.statusCode}`));
            return;
          }

          try {
            resolve(JSON.parse(body));
          } catch {
            reject(new Error('usage response was not valid JSON'));
          }
        });
      }
    );

    request.on('timeout', () => {
      request.destroy(new Error('usage request timed out'));
    });
    request.on('error', reject);
    request.end();
  });
}

async function main() {
  const codexRoot = getCodexRoot();
  if (!codexRoot) {
    throw new Error('Codex settings folder was not found');
  }

  const authPath = path.join(codexRoot, 'auth.json');
  const auth = JSON.parse(fs.readFileSync(authPath, 'utf8'));
  const accessToken = auth && auth.tokens && auth.tokens.access_token;
  if (!accessToken) {
    throw new Error('Codex access token was not found');
  }

  const usage = await getJson(usageUrl, accessToken);
  const picked = pickRateLimit(usage || {});
  const rateLimit = picked.rateLimit;
  const primary = pickWindow(rateLimit && rateLimit.primary_window);
  const secondary = pickWindow(rateLimit && rateLimit.secondary_window);

  if (!primary || !secondary || !primary.reset_at || !secondary.reset_at) {
    throw new Error('usage response did not contain Codex limit windows');
  }

  process.stdout.write(
    JSON.stringify({
      source: 'wham usage',
      limit_name: picked.name,
      is_additional_limit: picked.isAdditional,
      fetched_at: Math.floor(Date.now() / 1000),
      primary,
      secondary,
    })
  );
}

main().catch((error) => {
  process.stderr.write(error.message);
  process.exit(1);
});