local limitsPath = nil
local lastAutoRefresh = 0

function Initialize()
    limitsPath = SKIN:MakePathAbsolute(SELF:GetOption('LimitsPath'))
    lastAutoRefresh = os.time()
end

function Update()
    local refreshSeconds = tonumber(SKIN:GetVariable('RefreshSeconds', '300')) or 300
    if refreshSeconds < 30 then
        refreshSeconds = 30
    end

    local now = os.time()

    if now - lastAutoRefresh >= refreshSeconds then
        RefreshLimits()
    end

    return 0
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

function RefreshLimits(measureName)
    if SKIN:GetVariable('RefreshBusy', '0') == '1' then
        return
    end

    lastAutoRefresh = os.time()
    SKIN:Bang('!SetVariable', 'RefreshBusy', '1')
    SKIN:Bang('!CommandMeasure', measureName or 'MeasureRefresh', 'Run')
end

function FinishRefresh()
    lastAutoRefresh = os.time()
    SKIN:Bang('!SetVariable', 'RefreshBusy', '0')
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
