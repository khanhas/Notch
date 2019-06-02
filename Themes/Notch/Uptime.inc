[Variables]
Uptime_X=786
;Left, Right or Center
Uptime_Anchor=right

[Metadata]
Name=Notch\\Uptime
Author=reddit.com/u/khanhas
Description=Display up time.

[UptimeAnchor]
Measure=String
String = #Uptime_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = !SetOption UptimeContainer X "(#Bar_OffsetX#+#*Uptime_X*#-[*UptimeContainer:W*]/2)"
IfMatch2 = Right|right
IfMatchAction2 = !SetOption UptimeContainer X "(#Bar_OffsetX#+#*Uptime_X*#-[*UptimeContainer:W*])"

[MeasureUptime]
Measure=upTime
Format="%3!i!h, %2!i!m, %1!i!s"

[UptimeIcon]
Meter=String
Text=[\xE8B3]
FontFace=Material Icons
FontSize=(#Font_Size#*16/13)
FontColor=#Color_Scheme3#
AntiAlias=1
StringAlign=LeftCenter
Y=(#Bar_Height#/2)
Container = UptimeContainer

[Uptime]
Meter=String
MeasureName=MeasureUptime
FontFace=#Font_Face#
FontSize=#Font_Size#
FontColor=#Color_Scheme2#
FontWeight=#Font_Weight#
AntiAlias=1
StringAlign=LeftCenter
X=5R
Y=r
Container = UptimeContainer

[UptimeContainer]
Meter = Shape
X = (#Bar_OffsetX#+#Uptime_X#)
Y = #Bar_OffsetY#
Shape = Rectangle 0,0,([UptimeIcon:W] + [Uptime:W] + 5),#Bar_Height# | StrokeWidth 0
DynamicVariables = 1
