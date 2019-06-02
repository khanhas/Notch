[Variables]
Weather2_X =104
;Left, Right or Center
Weather2_Anchor=left
; LocationCode can be obtained at http://wxdata.weather.com/wxdata/search/search?where=YourCityName
Weather2_LocationCode=USVA0944
; Unit can be "f" (Fahrenheit / Imperial) or "m" (Celsius / Metric)
Weather2_Unit = m
; Locale (language) to use in the feed.
; https://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
; Note that Weather.com uses "_" underline instead of "-" dash in the codes.
Weather2_Locale=en_US

; Should not touch this
Weather2_URL=http://wxdata.weather.com/wxdata/weather/local/#Weather2_LocationCode#?cc=*&unit=#Weather2_Unit#&locale=#Weather2_Locale#

[Metadata]
Name=Notch\\Weather2
Author=reddit.com/u/khanhas
Description=Fetch data from wxdata.weather.com. Display current weather and temperature. Hover mouse on text for more information.

[Weather2Anchor]
Measure=String
String = #Weather2_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = !SetOption Weather2Container X "(#Bar_OffsetX#+#*Weather2_X*#-[*Weather2Container:W*]/2)"
IfMatch2 = Right|right
IfMatchAction2 = !SetOption Weather2Container X "(#Bar_OffsetX#+#*Weather2_X*#-[*Weather2Container:W*])"

[Weather2Measure]
Measure=Plugin
Plugin=PowershellRM
Line=$data = [xml](Invoke-WebRequest $RmAPI.VariableStr("Weather2_URL") -UseBasicParsing)
; Line2=$RmAPI.Bang("!UpdateMeasureGroup Weather2Measures")
UpdateDivider = 3600

[Weather2Location]
Measure=Plugin
Plugin=PowershellRM
Parent=Weather2Measure
Line=$data.weather.loc.dnam
Group=Weather2Measures
UpdateDivider = -1

[Weather2Des]
Measure=Plugin
Plugin=PowershellRM
Parent=Weather2Measure
Line=$data.weather.cc.t
Group=Weather2Measures
UpdateDivider = -1

[Weather2IconM]
Measure=Plugin
Plugin=PowershellRM
Parent=Weather2Measure
Line  = $iconIndex = $data.weather.cc.icon
Line2 = if ((0..4),38,47 -contains $iconIndex) {return "storm"}
Line3 = if ((5..8),10,17,18 -contains $iconIndex) {return "sleet"}
Line4 = if ((9,11,12,37,39,40,45) -contains $iconIndex) {return "rain"}
Line5 = if ((13..16),25,35,41,42,43,46 -contains $iconIndex) {return "snow"}
Line6 = if ((19..22),33,34,44 -contains $iconIndex) {return "fog"}
Line7 = if ((23,24) -contains $iconIndex) {return "wind"}
Line8 = if ((26..30) -contains $iconIndex) {return "cloudy"}
Line9 = if ((32,36) -contains $iconIndex) {return "clear_day"}
Line10= if (31 -eq $iconIndex) {return "clear_night"}
Group=Weather2Measures
UpdateDivider = -1

[Weather2Temp]
Measure=Plugin
Plugin=PowershellRM
Parent=Weather2Measure
Line=$data.weather.cc.tmp
Group=Weather2Measures
UpdateDivider = -1

[Weather2Unit]
Measure=Plugin
Plugin=PowershellRM
Parent=Weather2Measure
Line=$data.weather.head.ut
Group=Weather2Measures
UpdateDivider = -1

[Weather2Icon]
Meter=Image
MeasureName=Weather2IconM
MeasureName2=Weather2Des
MeasureName3=Weather2Location
ImagePath=#ROOTCONFIGPATH#Themes\#Theme#\Assets
ImageTint=#Color_Scheme3#
W=(#Font_Size#*20/13)
Y=((#Bar_Height#-[Weather2Icon:H])/2)
DynamicVariables=1
ToolTipText=Today is %2#CRLF#Location: %3
Container = Weather2Container

[Weather2]
Meter=String
MeasureName=Weather2Temp
MeasureName2=Weather2Unit
MeasureName3=Weather2Des
MeasureName4=Weather2Location
Text=%1[\x00B0]%2
FontFace=#Font_Face#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
FontWeight=#Font_Weight#
AntiAlias=1
StringAlign=LeftCenter
X=10R
Y=(#Bar_Height#/2)
ToolTipText=Today is %3#CRLF#Location: %4
Container = Weather2Container

[Weather2Container]
Meter = Shape
X = (#Bar_OffsetX#+#Weather2_X#)
Y = #Bar_OffsetY#
Shape = Rectangle 0,0,([Weather2Icon:W] + [Weather2:W] + 10),#Bar_Height# | StrokeWidth 0
DynamicVariables = 1
