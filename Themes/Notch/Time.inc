[Variables]
Time_X=33
;Left, Right or Center
Time_Anchor=left

[Metadata]
Name=Notch\\Clock
Author=reddit.com/u/khanhas
Description=Clock with material icon.

[TimeAnchor]
Measure=String
String = #Time_Anchor#
IfMatch = Center|center|Middle|middle
IfMatchAction = [!SetOption Time StringAlign CenterCenter]
IfMatch2 = Right|right
IfMatchAction2 = [!SetOption Time StringAlign RightCenter]

[MeasureTime]
Measure=Time
Format=%I:%M

[Time]
Meter=String
MeasureName=MeasureTime
FontFace=#Font_Face#
FontSize=#Font_Size#
FontWeight=#Font_Weight#
FontColor=#Color_Scheme2#
AntiAlias=1
StringAlign=LeftCenter
X=(#Bar_OffsetX#+#Time_X#)
Y=(#Bar_OffsetY#+#Bar_Height#/2)
DynamicVariables=1
