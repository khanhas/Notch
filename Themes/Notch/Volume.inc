[Variables]
Volume_X =966
;Left, Right or Center
Volume_Anchor=right

[Metadata]
Name=Notch\\Volume
Author=reddit.com/u/khanhas
Description=Display volume, increase and decrease volume by mouse scroll, click at speaker icon to mute. Click at volume number to activate volume slider and audio device changer.

[VolumeAnchor]
Measure=String
String = #Volume_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = !SetOption VolumeContainer X "(#Bar_OffsetX#+#*Volume_X*#-[*VolumeContainer:W*]/2)"
IfMatch2 = Right|right
IfMatchAction2 = !SetOption VolumeContainer X "(#Bar_OffsetX#+#*Volume_X*#-[*VolumeContainer:W*])"

[VolumeLevel]
Measure=Plugin
Plugin=Win7AudioPlugin
Group = Volume
IfCondition=VolumeLevel < 0
IfTrueAction=[!SetOption VolumeIcon Text "[\xE04F]"][!UpdateMeterGroup Volume][!Redraw]
IfCondition2=VolumeLevel = 0
IfTrueAction2=[!SetOption VolumeIcon Text "[\xE04E]"][!UpdateMeterGroup Volume][!Redraw]
IfCondition3=(VolumeLevel <= 50) && (VolumeLevel > 0)
IfTrueAction3=[!SetOption VolumeIcon Text "[\xE04D]"][!UpdateMeterGroup Volume][!Redraw]
IfCondition4=VolumeLevel > 50
IfTrueAction4=[!SetOption VolumeIcon Text "[\xE050]"][!UpdateMeterGroup Volume][!Redraw]
Group = Volume

[VolumeLevelCalc]
Measure = Calc
Formula = Clamp(VolumeLevel, 0, 100)
Group = Volume

[VolumeIcon]
Meter=String
FontFace=Material Icons
FontSize=(#Font_Size#*16/13)
FontColor=#Color_Scheme3#
AntiAlias=1
StringAlign=LeftCenter
Y=(#Bar_Height#/2)
LeftMouseUpAction=[!CommandMeasure VolumeLevel "ToggleMute"][!UpdateMeasureGroup Volume][!UpdateMeterGroup Volume][!Redraw]
Group=Volume
H=#Bar_Height#
Container = VolumeContainer

[Volume]
Meter=String
MeasureName=VolumeLevelCalc
Postfix=%
FontFace=#Font_Face#
FontSize=#Font_Size#
FontWeight=#Font_Weight#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=5R
Y=r
H=#Bar_Height#
LeftMouseUpAction=[!WriteKeyValue Variables Curr_X ([VolumeContainer:X]+[VolumeContainer:W]/2+#CURRENTCONFIGX#) "#ROOTCONFIGPATH#\Themes\#Theme#\Assets\VolumeControl.ini"][!WriteKeyValue Variables Curr_Y [SubSkinYPositionCalc] "#ROOTCONFIGPATH#\Themes\#Theme#\Assets\VolumeControl.ini"][!WriteKeyValue Variables Dir [SubSkinDirectionCalc] "#ROOTCONFIGPATH#\Themes\#Theme#\Assets\VolumeControl.ini"][!ToggleConfig "#ROOTCONFIG#\Themes\#Theme#\Assets" "VolumeControl.ini"]
MouseScrollDownAction=[!CommandMeasure VolumeLevel "ChangeVolume -5"][!UpdateMeasureGroup Volume][!UpdateMeterGroup Volume][!Redraw]
MouseScrollUpAction=[!CommandMeasure VolumeLevel "ChangeVolume +5"][!UpdateMeasureGroup Volume][!UpdateMeterGroup Volume][!Redraw]
Group=Volume
Container = VolumeContainer
DynamicVariables=1
MouseLeaveAction=!CommandMeasure AdditionalSkinActionTimer "Execute 1"
MouseOverAction=!CommandMeasure AdditionalSkinActionTimer "Stop 1"

[VolumeContainer]
Meter = Shape
X = (#Bar_OffsetX#+#Volume_X#)
Y = #Bar_OffsetY#
Shape = Rectangle 0,0,([VolumeIcon:W] + [Volume:W] + 5),#Bar_Height# | StrokeWidth 0
DynamicVariables = 1
Group=Volume
