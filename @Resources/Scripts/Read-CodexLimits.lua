local limitsPath = nil
local lastAutoRefresh = 0
local refreshStarted = 0

function Initialize()
    limitsPath = SKIN:MakePathAbsolute(SELF:GetOption('LimitsPath'))
    lastAutoRefresh = os.time()
    refreshStarted = 0
end

local function getRefreshSeconds()
    local refreshSeconds = tonumber(SKIN:GetVariable('RefreshSeconds', '30')) or 30
    if refreshSeconds < 30 then
        refreshSeconds = 30
    end

    return refreshSeconds
end

function Update()
    AutoRefreshLimits()
    return 0
end

function AutoRefreshLimits()
    local refreshSeconds = getRefreshSeconds()
    local now = os.time()

    if now - lastAutoRefresh >= refreshSeconds then
        RefreshLimits(nil, now, false)
    end
end

local function readLimitsFile(path)
    local values = {}
    local file = io.open(path, 'r')
    if not file then
        return values
    end

    for line in file:lines() do
        local key, value = line:match('^%s*([^=%[%];]+)%s*=%s*(.-)%s*$')
        if key and value then
            values[key] = value
        end
    end

    file:close()
    return values
end

function ReadLimits()
    local values = readLimitsFile(limitsPath)
    local keys = {
        'FiveHourValue',
        'FiveHourReset',
        'WeeklyValue',
        'WeeklyReset',
        'LastChecked',
        'DataStatus'
    }

    for _, key in ipairs(keys) do
        if values[key] then
            SKIN:Bang('!SetVariable', key, values[key])
        end
    end

    local measures = {
        'MeasureFive',
        'MeasureWeek',
        'MeasureFiveBar',
        'MeasureWeekBar',
        'MeasureFiveRail',
        'MeasureFiveRailX',
        'MeasureWeekRail'
    }

    for _, measure in ipairs(measures) do
        if measureExists(measure) then
            SKIN:Bang('!UpdateMeasure', measure)
        end
    end

    SKIN:Bang('!UpdateMeter', '*')
    SKIN:Bang('!Redraw')
end

function ManualRefreshLimits(measureName)
    RefreshLimits(measureName, os.time(), true)
end

function RefreshLimits(measureName, now, force)
    now = now or os.time()

    if not force and now - lastAutoRefresh < getRefreshSeconds() then
        return
    end

    if SKIN:GetVariable('RefreshBusy', '0') == '1' then
        local busyTimeout = math.max(getRefreshSeconds() + 10, 40)
        if refreshStarted > 0 and now - refreshStarted < busyTimeout then
            return
        end

        SKIN:Bang('!SetVariable', 'RefreshBusy', '0')
    end

    lastAutoRefresh = now
    refreshStarted = now
    SKIN:Bang('!SetVariable', 'RefreshBusy', '1')

    local refreshMeasure = measureName or 'MeasureRefresh'
    SKIN:Bang('!EnableMeasure', refreshMeasure)
    SKIN:Bang('!CommandMeasure', refreshMeasure, 'Run')
end

function FinishRefresh()
    lastAutoRefresh = os.time()
    refreshStarted = 0
    SKIN:Bang('!SetVariable', 'RefreshBusy', '0')
    SKIN:Bang('!DisableMeasure', 'MeasureRefresh')
    ReadLimits()
end

function measureExists(name)
    if not SKIN.GetMeasure then
        return false
    end

    local ok, measure = pcall(function()
        return SKIN:GetMeasure(name)
    end)

    return ok and measure ~= nil
end
