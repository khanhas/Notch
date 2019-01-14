function Initialize()
	measureName = SKIN:GetMeasure(SELF:GetOption('MeasureName'))
	autoRefresh = SELF:GetOption('AutoRefresh')*1 == 1
	appCalc = SKIN:GetMeasure("AppVolumeCalc")
end

function Generate(num)
	local filePath = SKIN:MakePathAbsolute(SELF:GetOption('IncFile'))
	if not filePath then
		error("Invalid inc file path.")
		return
	end

	local file = io.open(filePath, 'w+')
	if not file then
		error("Could not open inc file.")
		return
	end
	if num == 0 then
		-- Clear file
		file:write("")
	else
		for i = 1, num do
			local sec, secCount = SELF:GetOption('S1'), 1
			while sec and sec ~= '' do
				file:write('[', sec:gsub('%%%%', i), ']\n')
				local key, keyCount = SELF:GetOption('S' .. secCount .. 'K1'), 1
				while key and key ~= '' do
					key = key:gsub('%%%%', i)
					file:write(key:gsub('%%%%', i):gsub('{.-}', parseFormula), '\n')
					keyCount = keyCount + 1
					key = SELF:GetOption('S' .. secCount .. 'K' .. keyCount)
				end
				secCount = secCount + 1
				sec = SELF:GetOption('S' .. secCount)
			end
		end
	end
	file:close()
	SKIN:Bang('!WriteKeyValue', 'Variables', 'MaxMeter', num)
end

function Update()
	local num = measureName:GetValue()
	if num ~= SKIN:GetVariable('MaxMeter')*1 then
		Generate(num)
		if autoRefresh then
			SKIN:Bang('!Refresh')
		end
	end
end

function parseFormula(formula)
	return SKIN:ParseFormula("(" .. formula:sub(2, -2) .. ")")
end

function slidingAppVolume(index)
	SKIN:Bang('!CommandMeasure', 'AppVol'..index, 'SetVolume '..appCalc:GetValue())
end