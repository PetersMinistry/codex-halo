function Initialize()
    limitsPath = SKIN:MakePathAbsolute(SELF:GetOption('LimitsPath'))
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
        SKIN:Bang('!UpdateMeasure', measure)
    end

    SKIN:Bang('!UpdateMeter', '*')
    SKIN:Bang('!Redraw')
end
