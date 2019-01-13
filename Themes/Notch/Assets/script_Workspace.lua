function Initialize()
	maximumWorkspace = tonumber(SKIN:GetVariable('Maximum_Workspace'))
	dotGap = tonumber(SKIN:GetVariable('Workspace_Number_Gap'))
	totalWorkspaceMeasure = SKIN:GetMeasure("Workspace_Total")
	currentWorkspaceMeasure = SKIN:GetMeasure("Workspace_Current")
end

oldCurrentWorkspace = 1
changingWorkspace = false
function Update()
	totalWorkspace = totalWorkspaceMeasure:GetValue()
	currentWorkspace = currentWorkspaceMeasure:GetValue()

	for i = 1, maximumWorkspace do
		if i <= totalWorkspace then
			SKIN:Bang('!ShowMeter', 'Workspace'..i)
		else
			SKIN:Bang('!HideMeter', 'Workspace'..i)
		end
	end
	if totalWorkspace ~= -1 then
		local trueTotalWorkspace = math.min(totalWorkspace, maximumWorkspace)
		SKIN:Bang('!SetOption', 'WorkspaceContainer', 'Shape', 'Rectangle 0,0,('..(dotGap*2*trueTotalWorkspace)..'),#Bar_Height#')
	end
	if oldCurrentWorkspace ~= currentWorkspace and not changingWorkspace then
		SKIN:Bang('[!CommandMeasure WorkspaceActionTimer "Stop 1"][!CommandMeasure WorkspaceActionTimer "Execute 1"]')
		timing=1
		changingWorkspace = true
	end
end

timing = 0
maxTime = 40
function ChangeWorkspaceAnimation()
	if timing > 0 and timing < maxTime then
		timing = timing + 1
		local aniFactor = outQuart(timing,0,1,maxTime)
		slideAnimation = (oldCurrentWorkspace-1)*dotGap*2+(currentWorkspace-oldCurrentWorkspace)*dotGap*2*aniFactor
		if currentWorkspace <= maximumWorkspace then
			SKIN:Bang('!ShowMeter', 'WorkspaceCurrent')
			SKIN:Bang('!SetOption', 'WorkspaceCurrent', 'Shape', 'Ellipse '..slideAnimation..',0,5.5 | Extend Trait')
			SKIN:Bang('!UpdateMeter', 'WorkspaceCurrent')
			SKIN:Bang('!Redraw')
		else
			SKIN:Bang('!HideMeter', 'WorkspaceCurrent')
		end
	elseif timing == maxTime then
		timing = 0
		oldCurrentWorkspace = currentWorkspace
		changingWorkspace = false
		SKIN:Bang('!CommandMeasure', 'WorkspaceActionTimer', 'Stop 1')
	end
end

function outQuart(t, b, c, d)
  t = t / d - 1
  return -c * (t * t - 1) + b
end