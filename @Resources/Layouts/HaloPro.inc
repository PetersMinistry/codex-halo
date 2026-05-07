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

[MeasureFiveBar]
Measure=Calc
Formula=(#FiveHourValue# * #BarScale#)
DynamicVariables=1

[MeasureWeekBar]
Measure=Calc
Formula=(#WeeklyValue# * #BarScale#)
DynamicVariables=1

[MeasureReadLimits]
Measure=Script
ScriptFile=#@#Scripts\Read-CodexLimits.lua
LimitsPath=#@#CodexLimits.inc
UpdateDivider=-1

[MeasureRefresh]
Measure=Plugin
Plugin=RunCommand
Program=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe
Parameter=-NoProfile -ExecutionPolicy Bypass -File "#@#Scripts\Update-CodexLimits.ps1" -OutputPath "#@#CodexLimits.inc"
State=Hide
OutputType=ANSI
UpdateDivider=-1
FinishAction=[!CommandMeasure MeasureReadLimits "ReadLimits()"]

[MeasureAutoRun]
Measure=Plugin
Plugin=RunCommand
Program=%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe
Parameter=-NoProfile -ExecutionPolicy Bypass -File "#@#Scripts\Update-CodexLimits.ps1" -OutputPath "#@#CodexLimits.inc"
State=Hide
OutputType=ANSI
UpdateDivider=-1
FinishAction=[!CommandMeasure MeasureReadLimits "ReadLimits()"]

[MeasureAutoRefresh]
Measure=Calc
Formula=1
UpdateDivider=#RefreshSeconds#
DynamicVariables=1
OnUpdateAction=[!CommandMeasure MeasureAutoRun "Run"]

[MeterCanvas]
Meter=Shape
X=0
Y=0
W=#CanvasW#
H=#CanvasH#
Shape=Rectangle 0,0,#CanvasW#,#CanvasH# | Fill Color 0,0,0,1 | StrokeWidth 0
DynamicVariables=1

[MeterHaloShell]
Meter=Shape
X=0
Y=0
W=#RingSize#
H=#RingSize#
Shape=Ellipse #Center#,#Center#,#PlateOuter#,#PlateOuter# | Fill Color #Panel# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Ellipse #Center#,#Center#,#PlateInner#,#PlateInner# | Fill Color 0,0,0,1 | StrokeWidth 1 | Stroke Color 255,255,255,22
Shape3=Ellipse #Center#,#Center#,#DockOuter#,#DockOuter# | Fill Color 0,0,0,1 | StrokeWidth 1 | Stroke Color 255,255,255,36
Shape4=Ellipse #Center#,#Center#,#DockInner#,#DockInner# | Fill Color 0,0,0,1 | StrokeWidth 1 | Stroke Color 0,0,0,120
Shape5=Ellipse #Center#,#Center#,#DockCore#,#DockCore# | Fill Color 0,0,0,1 | StrokeWidth 1 | Stroke Color 255,255,255,18
DynamicVariables=1

[MeterGlassSweep]
Meter=Shape
X=0
Y=0
W=#RingSize#
H=#RingSize#
Shape=Path Sweep | Fill Color 255,255,255,12 | StrokeWidth 0
Sweep=#SweepStartX#,#SweepStartY# | LineTo #SweepOneX#,#SweepOneY# | LineTo #SweepTwoX#,#SweepTwoY# | LineTo #Center#,#Center# | ClosePath 1
DynamicVariables=1

[MeterOuterGlow]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureFive
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#OuterGlowStart#
LineLength=#OuterGlowEnd#
LineColor=#FiveGlow#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterOuterTrack]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureFull
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#OuterTrackStart#
LineLength=#OuterTrackEnd#
LineColor=#OuterTrack#
Solid=1
AntiAlias=1

[MeterOuterValue]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureFive
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#OuterTrackStart#
LineLength=#OuterTrackEnd#
LineColor=#FiveColor#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterInnerGlow]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureWeek
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#InnerGlowStart#
LineLength=#InnerGlowEnd#
LineColor=#WeekGlow#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterInnerTrack]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureFull
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#InnerTrackStart#
LineLength=#InnerTrackEnd#
LineColor=#InnerTrack#
Solid=1
AntiAlias=1

[MeterInnerValue]
Meter=Roundline
X=0
Y=0
W=#RingSize#
H=#RingSize#
MeasureName=MeasureWeek
StartAngle=4.712389
RotationAngle=6.283185
LineStart=#InnerTrackStart#
LineLength=#InnerTrackEnd#
LineColor=#WeekColor#
Solid=1
AntiAlias=1
DynamicVariables=1

[MeterTicks]
Meter=Shape
X=0
Y=0
W=#RingSize#
H=#RingSize#
Shape=Rectangle #TopTickX#,#TopTickY#,#TickThin#,#TickLong#,#TickRadius# | Fill Color #Accent# | StrokeWidth 0
Shape2=Rectangle #BottomTickX#,#BottomTickY#,#TickThin#,#TickLong#,#TickRadius# | Fill Color 255,255,255,74 | StrokeWidth 0
Shape3=Rectangle #LeftTickX#,#SideTickY#,#TickLong#,#TickThin#,#TickRadius# | Fill Color 255,255,255,74 | StrokeWidth 0
Shape4=Rectangle #RightTickX#,#SideTickY#,#TickLong#,#TickThin#,#TickRadius# | Fill Color 255,255,255,74 | StrokeWidth 0
Shape5=Rectangle #DiagLeftX#,#DiagTopY#,#TickThin#,#DiagLong#,#TickRadius# | Fill Color #FiveColor# | StrokeWidth 0 | Rotate -42,#DiagLeftPivotX#,#DiagTopPivotY#
Shape6=Rectangle #DiagRightX#,#DiagTopY#,#TickThin#,#DiagLong#,#TickRadius# | Fill Color #WeekColor# | StrokeWidth 0 | Rotate 42,#DiagRightPivotX#,#DiagTopPivotY#
DynamicVariables=1

[MeterTitle]
Meter=String
X=#Center#
Y=#TitleY#
W=#TitleW#
H=#TitleH#
FontFace=#FontFace#
FontSize=#TitleSize#
FontWeight=800
FontColor=#TextColor#
StringAlign=Center
AntiAlias=1
Text=CODEX HALO
DynamicVariables=1

[MeterStatusPill]
Meter=Shape
X=#StatusPillX#
Y=#StatusPillY#
W=#StatusPillW#
H=#StatusPillH#
Shape=Rectangle 0,0,#StatusPillW#,#StatusPillH#,#StatusPillRadius# | Fill Color #PillFill# | StrokeWidth 1 | Stroke Color #PillStroke#
DynamicVariables=1
ToolTipText=Refresh data | 5H #FiveHourValue#% until #FiveHourReset# | WK #WeeklyValue#% until #WeeklyReset# | checked #LastChecked#
MouseOverAction=[!SetOption MeterStatusPill Shape "Rectangle 0,0,#StatusPillW#,#StatusPillH#,#StatusPillRadius# | Fill Color 255,255,255,34 | StrokeWidth 1 | Stroke Color 255,255,255,62"][!UpdateMeter MeterStatusPill][!Redraw]
MouseLeaveAction=[!SetOption MeterStatusPill Shape "Rectangle 0,0,#StatusPillW#,#StatusPillH#,#StatusPillRadius# | Fill Color #PillFill# | StrokeWidth 1 | Stroke Color #PillStroke#"][!UpdateMeter MeterStatusPill][!Redraw]
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterStatusText]
Meter=String
X=#StatusTextX#
Y=#StatusTextY#
W=#StatusTextW#
H=#StatusTextH#
FontFace=#TextFace#
FontSize=#StatusSize#
FontColor=#DimText#
StringAlign=Center
AntiAlias=1
ClipString=1
Text=#DataStatus#
DynamicVariables=1
ToolTipText=Refresh data | 5H #FiveHourValue#% until #FiveHourReset# | WK #WeeklyValue#% until #WeeklyReset# | checked #LastChecked#
MouseOverAction=[!SetOption MeterStatusText FontColor "255,255,255,230"][!UpdateMeter MeterStatusText][!Redraw]
MouseLeaveAction=[!SetOption MeterStatusText FontColor "#DimText#"][!UpdateMeter MeterStatusText][!Redraw]
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterConsole]
Meter=Shape
X=#ConsoleX#
Y=#ConsoleY#
W=#ConsoleW#
H=#ConsoleH#
Shape=Rectangle 0,0,#ConsoleW#,#ConsoleH#,#ConsoleRadius# | Fill Color #ConsoleFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Rectangle #ConsoleInset#,#DividerY#,#DividerW#,#DividerH#,#DividerRadius# | Fill Color 255,255,255,28 | StrokeWidth 0
Shape3=Rectangle #ConsoleDividerX#,#DividerTop#,#DividerThin#,#DividerTall#,#DividerRadius# | Fill Color 255,255,255,24 | StrokeWidth 0
DynamicVariables=1
ToolTipText=Refresh data | 5H #FiveHourValue#% until #FiveHourReset# | WK #WeeklyValue#% until #WeeklyReset# | checked #LastChecked#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterFiveLabel]
Meter=String
X=#LeftValueX#
Y=#LabelY#
W=#ColumnW#
H=#LabelH#
FontFace=#TextFace#
FontSize=#LabelSize#
FontWeight=700
FontColor=#FiveColor#
StringAlign=Center
AntiAlias=1
Text=5H

[MeterFiveValue]
Meter=String
X=#LeftValueX#
Y=#ValueY#
W=#ColumnW#
H=#ValueH#
FontFace=#FontFace#
FontSize=#ValueSize#
FontWeight=800
FontColor=#FiveColor#
StringAlign=Center
AntiAlias=1
Text=#FiveHourValue#%
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterFiveReset]
Meter=String
Hidden=1
X=#LeftValueX#
Y=#ResetY#
W=#ColumnW#
H=#ResetH#
FontFace=#TextFace#
FontSize=#ResetSize#
FontColor=#DimText#
StringAlign=Center
AntiAlias=1
ClipString=1
Text=until #FiveHourReset#
DynamicVariables=1

[MeterFiveBar]
Meter=Shape
X=#LeftBarX#
Y=#BarY#
W=#BarTrackW#
H=#BarH#
Shape=Rectangle 0,0,#BarTrackW#,#BarH#,#BarRadius# | Fill Color 255,255,255,28 | StrokeWidth 0
Shape2=Rectangle 0,0,[MeasureFiveBar],#BarH#,#BarRadius# | Fill Color #FiveColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterWeekLabel]
Meter=String
X=#RightValueX#
Y=#LabelY#
W=#ColumnW#
H=#LabelH#
FontFace=#TextFace#
FontSize=#LabelSize#
FontWeight=700
FontColor=#WeekColor#
StringAlign=Center
AntiAlias=1
Text=WEEK

[MeterWeekValue]
Meter=String
X=#RightValueX#
Y=#ValueY#
W=#ColumnW#
H=#ValueH#
FontFace=#FontFace#
FontSize=#ValueSize#
FontWeight=800
FontColor=#WeekColor#
StringAlign=Center
AntiAlias=1
Text=#WeeklyValue#%
DynamicVariables=1
ToolTipText=WK #WeeklyValue#% until #WeeklyReset#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterWeekReset]
Meter=String
Hidden=1
X=#RightValueX#
Y=#ResetY#
W=#ColumnW#
H=#ResetH#
FontFace=#TextFace#
FontSize=#ResetSize#
FontColor=#DimText#
StringAlign=Center
AntiAlias=1
ClipString=1
Text=until #WeeklyReset#
DynamicVariables=1

[MeterWeekBar]
Meter=Shape
X=#RightBarX#
Y=#BarY#
W=#BarTrackW#
H=#BarH#
Shape=Rectangle 0,0,#BarTrackW#,#BarH#,#BarRadius# | Fill Color 255,255,255,28 | StrokeWidth 0
Shape2=Rectangle 0,0,[MeasureWeekBar],#BarH#,#BarRadius# | Fill Color #WeekColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=WK #WeeklyValue#% until #WeeklyReset#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterFooter]
Meter=String
Hidden=1
X=#Center#
Y=#FooterY#
W=#FooterW#
H=#FooterH#
FontFace=#TextFace#
FontSize=#FooterSize#
FontColor=255,255,255,128
StringAlign=Center
AntiAlias=1
ClipString=1
Text=checked #LastChecked#
DynamicVariables=1
ToolTipText=Refresh data | checked #LastChecked#
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking snapshot..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]
