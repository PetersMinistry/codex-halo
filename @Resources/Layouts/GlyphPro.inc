; Rainmeter Codex Halo

[MeasureFull]
Measure=Calc
Formula=100
MinValue=0
MaxValue=100

[MeasureFive]
Measure=Calc
Formula=#FiveHourValue#
MinValue=0
MaxValue=100
DynamicVariables=1

[MeasureWeek]
Measure=Calc
Formula=#WeeklyValue#
MinValue=0
MaxValue=100
DynamicVariables=1

[MeasureHourlyPulse]
Measure=Calc
Formula=Counter
IfCondition=(MeasureHourlyPulse >= #RefreshSeconds#) && ((MeasureHourlyPulse % #RefreshSeconds#) = 0)
IfTrueAction=[!CommandMeasure MeasureRefresh "Run"]
DynamicVariables=1

[MeasureRefresh]
Measure=Plugin
Plugin=RunCommand
Program=powershell.exe
Parameter=-NoProfile -ExecutionPolicy Bypass -File "#ResourceRoot#Scripts\Update-CodexLimits.ps1" -OutputPath "#ResourceRoot#CodexLimits.inc"
State=Hide
OutputType=ANSI
UpdateDivider=-1
FinishAction=[!RefreshApp]

[MeterCanvas]
Meter=Shape
X=0
Y=0
W=#CanvasW#
H=#CanvasH#
Shape=Rectangle 0,0,#CanvasW#,#CanvasH# | Fill Color 0,0,0,1 | StrokeWidth 0
DynamicVariables=1

[MeterPanel]
Meter=Shape
X=#PanelX#
Y=#PanelY#
W=#PanelW#
H=#PanelH#
Shape=Rectangle 0,0,#PanelW#,#PanelH#,#PanelRadius# | Fill Color #PanelFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Rectangle #DividerX#,#DividerY#,#DividerW#,#DividerH#,#DividerRadius# | Fill Color 255,255,255,24 | StrokeWidth 0
Shape3=Rectangle #TopRailX#,#TopRailY#,#TopRailW#,#TopRailH#,#RailRadius# | Fill Color 255,255,255,64 | StrokeWidth 0
Shape4=Rectangle #BottomRailX#,#BottomRailY#,#BottomRailW#,#BottomRailH#,#RailRadius# | Fill Color 255,255,255,26 | StrokeWidth 0
DynamicVariables=1

[MeterOrbShell]
Meter=Shape
X=0
Y=0
W=#CanvasW#
H=#CanvasH#
Shape=Ellipse #FiveCenterX#,#OrbCenterY#,#OrbShellR#,#OrbShellR# | Fill Color #OrbFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Ellipse #WeekCenterX#,#OrbCenterY#,#OrbShellR#,#OrbShellR# | Fill Color #OrbFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape3=Ellipse #FiveCenterX#,#OrbCenterY#,#CoreR#,#CoreR# | Fill Color 0,0,0,18 | StrokeWidth 1 | Stroke Color #FiveCoreStroke#
Shape4=Ellipse #WeekCenterX#,#OrbCenterY#,#CoreR#,#CoreR# | Fill Color 0,0,0,18 | StrokeWidth 1 | Stroke Color #WeekCoreStroke#
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset# | WK #WeeklyValue#% until #WeeklyReset#

[MeterFiveTrack]
Meter=Roundline
X=#FiveOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureFull
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#TrackStart#
LineLength=#TrackEnd#
LineColor=#TrackColor#
Solid=1
AntiAlias=1

[MeterFiveGlow]
Meter=Roundline
X=#FiveOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureFive
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#GlowStart#
LineLength=#GlowEnd#
LineColor=#FiveGlow#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterFiveRing]
Meter=Roundline
X=#FiveOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureFive
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#TrackStart#
LineLength=#TrackEnd#
LineColor=#FiveColor#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterWeekTrack]
Meter=Roundline
X=#WeekOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureFull
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#TrackStart#
LineLength=#TrackEnd#
LineColor=#TrackColor#
Solid=1
AntiAlias=1

[MeterWeekGlow]
Meter=Roundline
X=#WeekOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureWeek
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#GlowStart#
LineLength=#GlowEnd#
LineColor=#WeekGlow#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterWeekRing]
Meter=Roundline
X=#WeekOrbX#
Y=#OrbY#
W=#OrbSize#
H=#OrbSize#
MeasureName=MeasureWeek
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#TrackStart#
LineLength=#TrackEnd#
LineColor=#WeekColor#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterGlyphMarks]
Meter=Shape
X=0
Y=0
W=#CanvasW#
H=#CanvasH#
Shape=Rectangle #FiveMarkX#,#MarkY#,#MarkW#,#MarkH#,#MarkRadius# | Fill Color #FiveColor# | StrokeWidth 0
Shape2=Rectangle #WeekMarkX#,#MarkY#,#MarkW#,#MarkH#,#MarkRadius# | Fill Color #WeekColor# | StrokeWidth 0
Shape3=Rectangle #FiveSlashX#,#SlashY#,#SlashW#,#SlashH#,#MarkRadius# | Fill Color #FiveColor# | StrokeWidth 0 | Rotate -34,#FiveSlashPivotX#,#SlashPivotY#
Shape4=Rectangle #WeekSlashX#,#SlashY#,#SlashW#,#SlashH#,#MarkRadius# | Fill Color #WeekColor# | StrokeWidth 0 | Rotate 34,#WeekSlashPivotX#,#SlashPivotY#
DynamicVariables=1

[MeterFiveLabel]
Meter=String
X=#FiveCenterX#
Y=#LabelY#
W=#OrbTextW#
H=#LabelH#
FontFace=#TextFace#
FontSize=#LabelSize#
FontWeight=800
FontColor=#FiveColor#
StringAlign=Center
AntiAlias=1
Text=5H

[MeterFiveValue]
Meter=String
X=#FiveCenterX#
Y=#ValueY#
W=#OrbTextW#
H=#ValueH#
FontFace=#FontFace#
FontSize=#ValueSize#
FontWeight=850
FontColor=#FiveColor#
StringAlign=Center
AntiAlias=1
Text=#FiveHourValue#%
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset#

[MeterFiveReset]
Meter=String
Hidden=1
X=#FiveCenterX#
Y=#ResetY#
W=#OrbTextW#
H=#ResetH#
FontFace=#TextFace#
FontSize=#ResetSize#
FontColor=#DimText#
StringAlign=Center
AntiAlias=1
ClipString=1
Text=#FiveHourReset#
DynamicVariables=1

[MeterWeekLabel]
Meter=String
X=#WeekCenterX#
Y=#LabelY#
W=#OrbTextW#
H=#LabelH#
FontFace=#TextFace#
FontSize=#LabelSize#
FontWeight=800
FontColor=#WeekColor#
StringAlign=Center
AntiAlias=1
Text=WK

[MeterWeekValue]
Meter=String
X=#WeekCenterX#
Y=#ValueY#
W=#OrbTextW#
H=#ValueH#
FontFace=#FontFace#
FontSize=#ValueSize#
FontWeight=850
FontColor=#WeekColor#
StringAlign=Center
AntiAlias=1
Text=#WeeklyValue#%
DynamicVariables=1
ToolTipText=WK #WeeklyValue#% until #WeeklyReset#

[MeterWeekReset]
Meter=String
Hidden=1
X=#WeekCenterX#
Y=#ResetY#
W=#OrbTextW#
H=#ResetH#
FontFace=#TextFace#
FontSize=#ResetSize#
FontColor=#DimText#
StringAlign=Center
AntiAlias=1
ClipString=1
Text=#WeeklyReset#
DynamicVariables=1

[MeterStatusDot]
Meter=Shape
X=0
Y=0
W=#CanvasW#
H=#CanvasH#
Shape=Ellipse #StatusDotX#,#StatusDotY#,#StatusDotR#,#StatusDotR# | Fill Color #FiveColor# | StrokeWidth 1 | Stroke Color 255,255,255,82
DynamicVariables=1
ToolTipText=#DataStatus# | checked #LastChecked# | click to refresh
MouseOverAction=[!SetOption MeterStatusDot Shape "Ellipse #StatusDotX#,#StatusDotY#,#StatusDotR#,#StatusDotR# | Fill Color 255,255,255,210 | StrokeWidth 1 | Stroke Color 255,255,255,120"][!UpdateMeter MeterStatusDot][!Redraw]
MouseLeaveAction=[!SetOption MeterStatusDot Shape "Ellipse #StatusDotX#,#StatusDotY#,#StatusDotR#,#StatusDotR# | Fill Color #FiveColor# | StrokeWidth 1 | Stroke Color 255,255,255,82"][!UpdateMeter MeterStatusDot][!Redraw]
LeftMouseUpAction=[!CommandMeasure MeasureRefresh "Run"]
