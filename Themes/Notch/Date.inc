[Variables]
date_x=210
;Left, Right or Center
Date_Anchor=left

[Metadata]
Name=Notch\\Date
Author=reddit.com/u/khanhas
Description=Display date. Click to activate Calendar View with Google Calendar and Microsoft Outlook support.

[DateAnchor]
Measure=String
String = #Date_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction=!SetOption DateContainer X "(#Bar_OffsetX#+#*Date_X*#-[*DateContainer:W*]/2)"
IfMatch2 = Right|right
IfMatchAction2 =!SetOption DateContainer X "(#Bar_OffsetX#+#*Date_X*#-[*DateContainer:W*])"

[DateParseSchedule]
Measure=Script
ScriptFile=#@#Scripts\Calendar_Common_Script.lua

[DateScheduleFetch]
Measure=Plugin
Plugin=WebParser
URL=
Download=1
DownloadFile=calendarSchedule.txt
Debug=1
FinishAction=[!CommandMeasure DateParseSchedule "moduleNotification = true; notificationMeter = 'DateNotification'; parseSchedule()"]
UpdateRate=1000

[MeasureDate]
Measure=Time
Format=%a, %b %#d

[DateIcon]
Meter=String
Text=[\xE878]
FontFace=Material Icons
FontSize=(#Font_Size#*16/13)
FontColor=#Color_Scheme3#
AntiAlias=1
StringAlign=LeftCenter
Y=(#Bar_Height#/2)
Container = DateContainer

[Date]
Meter=String
MeasureName=MeasureDate
FontFace=#Font_Face#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
FontWeight=#Font_Weight#
AntiAlias=1
StringAlign=LeftCenter
X=5R
Y=r
LeftMouseUpAction=[!WriteKeyValue Variables Curr_X ([DateContainer:X]+[DateContainer:W]/2+#CURRENTCONFIGX#) "#ROOTCONFIGPATH#Themes\#Theme#\Assets\CalendarView.ini"][!WriteKeyValue Variables Curr_Y [SubSkinYPositionCalc] "#ROOTCONFIGPATH#Themes\#Theme#\Assets\CalendarView.ini"][!WriteKeyValue Variables Dir [SubSkinDirectionCalc] "#ROOTCONFIGPATH#\Themes\#Theme#\Assets\CalendarView.ini"][!ToggleConfig "#ROOTCONFIG#\Themes\#Theme#\Assets" "CalendarView.ini"]
MouseOverAction=!CommandMeasure AdditionalSkinActionTimer "Stop 1"
MouseLeaveAction=!CommandMeasure AdditionalSkinActionTimer "Execute 1"
Container = DateContainer

[DateNotification]
Meter=Shape
X=([DateIcon:X]+[DateIcon:W])
Y=(#Bar_OffsetY#+#Bar_Height#/2+#Font_Size#*8/13)
Shape=Ellipse 0,0,(#Font_Size#*4/13) | StrokeWidth 0 | Fill Color #Color_Scheme3#
DynamicVariables=1
Hidden=1
Container = DateContainer

[DateContainer]
Meter = Shape
X = (#Bar_OffsetX#+#Date_X#)
Y = #Bar_OffsetY#
Shape = Rectangle 0,0,([DateIcon:W] + [Date:W] + 5),#Bar_Height# | StrokeWidth 0
DynamicVariables = 1
