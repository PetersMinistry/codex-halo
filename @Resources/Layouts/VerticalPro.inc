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

[MeterPanel]
Meter=Shape
X=#PanelX#
Y=#PanelY#
W=#PanelW#
H=#PanelH#
Shape=Rectangle 0,0,#PanelW#,#PanelH#,#PanelRadius# | Fill Color #PanelFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Rectangle #AccentX#,#AccentY#,#AccentW#,#AccentH#,#AccentRadius# | Fill Color #AccentFill# | StrokeWidth 0
DynamicVariables=1

[MeterTitle]
Meter=String
X=#TitleX#
Y=#TitleY#
W=#TitleW#
H=#TitleH#
FontFace=#FontFace#
FontSize=#TitleSize#
FontWeight=800
FontColor=#TextColor#
StringAlign=Left
AntiAlias=1
ClipString=1
Text=CODEX LIMITS
DynamicVariables=1

[MeterSubtitle]
Meter=String
X=#TitleX#
Y=#SubtitleY#
W=#TitleW#
H=#SubtitleH#
FontFace=#TextFace#
FontSize=#SubtitleSize#
FontColor=#DimText#
StringAlign=Left
AntiAlias=1
ClipString=1
Text=#VariantName#
DynamicVariables=1

[MeterStatusPill]
Meter=Shape
X=#StatusX#
Y=#StatusY#
W=#StatusW#
H=#StatusH#
Shape=Rectangle 0,0,#StatusW#,#StatusH#,#StatusRadius# | Fill Color #PillFill# | StrokeWidth 1 | Stroke Color #PillStroke#
DynamicVariables=1
ToolTipText=Refresh data | 5H #FiveHourValue#% until #FiveHourReset# | WK #WeeklyValue#% until #WeeklyReset# | checked #LastChecked#
MouseOverAction=[!SetOption MeterStatusPill Shape "Rectangle 0,0,#StatusW#,#StatusH#,#StatusRadius# | Fill Color 255,255,255,36 | StrokeWidth 1 | Stroke Color 255,255,255,68"][!UpdateMeter MeterStatusPill][!Redraw]
MouseLeaveAction=[!SetOption MeterStatusPill Shape "Rectangle 0,0,#StatusW#,#StatusH#,#StatusRadius# | Fill Color #PillFill# | StrokeWidth 1 | Stroke Color #PillStroke#"][!UpdateMeter MeterStatusPill][!Redraw]
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking latest event..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

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
LeftMouseUpAction=[!SetOption MeterStatusText Text "checking..."][!SetOption MeterFooter Text "checking latest event..."][!UpdateMeter MeterStatusText][!UpdateMeter MeterFooter][!Redraw][!CommandMeasure MeasureRefresh "Run"]

[MeterFiveCard]
Meter=Shape
X=#CardX#
Y=#FiveCardY#
W=#CardW#
H=#CardH#
Shape=Rectangle 0,0,#CardW#,#CardH#,#CardRadius# | Fill Color #CardFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Rectangle #CardAccentX#,#CardAccentY#,#CardAccentW#,#CardAccentH#,#CardAccentRadius# | Fill Color #FiveColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset#

[MeterFiveLabel]
Meter=String
X=#CardCenterX#
Y=#FiveLabelY#
W=#CardTextW#
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
X=#CardCenterX#
Y=#FiveValueY#
W=#CardTextW#
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

[MeterFiveReset]
Meter=String
Hidden=1
X=#CardCenterX#
Y=#FiveResetY#
W=#CardTextW#
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
X=#CardBarX#
Y=#FiveBarY#
W=#BarTrackW#
H=#BarH#
Shape=Rectangle 0,0,#BarTrackW#,#BarH#,#BarRadius# | Fill Color 255,255,255,28 | StrokeWidth 0
Shape2=Rectangle 0,0,[MeasureFiveBar],#BarH#,#BarRadius# | Fill Color #FiveColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=5H #FiveHourValue#% until #FiveHourReset#

[MeterWeekCard]
Meter=Shape
X=#CardX#
Y=#WeekCardY#
W=#CardW#
H=#CardH#
Shape=Rectangle 0,0,#CardW#,#CardH#,#CardRadius# | Fill Color #CardFill# | StrokeWidth 1 | Stroke Color #PanelEdge#
Shape2=Rectangle #CardAccentX#,#CardAccentY#,#CardAccentW#,#CardAccentH#,#CardAccentRadius# | Fill Color #WeekColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=WK #WeeklyValue#% until #WeeklyReset#

[MeterWeekLabel]
Meter=String
X=#CardCenterX#
Y=#WeekLabelY#
W=#CardTextW#
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
X=#CardCenterX#
Y=#WeekValueY#
W=#CardTextW#
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

[MeterWeekReset]
Meter=String
Hidden=1
X=#CardCenterX#
Y=#WeekResetY#
W=#CardTextW#
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
X=#CardBarX#
Y=#WeekBarY#
W=#BarTrackW#
H=#BarH#
Shape=Rectangle 0,0,#BarTrackW#,#BarH#,#BarRadius# | Fill Color 255,255,255,28 | StrokeWidth 0
Shape2=Rectangle 0,0,[MeasureWeekBar],#BarH#,#BarRadius# | Fill Color #WeekColor# | StrokeWidth 0
DynamicVariables=1
ToolTipText=WK #WeeklyValue#% until #WeeklyReset#

[MeterFooter]
Meter=String
Hidden=1
X=#PanelCenterX#
Y=#FooterY#
W=#FooterW#
H=#FooterH#
FontFace=#TextFace#
FontSize=#FooterSize#
FontColor=255,255,255,130
StringAlign=Center
AntiAlias=1
ClipString=1
Text=checked #LastChecked#
DynamicVariables=1
