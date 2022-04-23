object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 500
  ClientWidth = 433
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DebugLabel: TLabel
    Left = 8
    Top = 70
    Width = 419
    Height = 25
    AutoSize = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 143
    Top = 13
    Width = 73
    Height = 17
    Alignment = taCenter
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = #1041#1091#1082#1074#1072' '#1076#1080#1089#1082#1072':'
    ParentBiDiMode = False
  end
  object StartReadBtn: TButton
    Left = 8
    Top = 8
    Width = 129
    Height = 25
    Caption = #1055#1088#1086#1095#1080#1090#1072#1090#1100
    TabOrder = 0
    OnClick = StartReadBtnClick
  end
  object ChooseDeviceEdit: TEdit
    Left = 222
    Top = 8
    Width = 50
    Height = 25
    Alignment = taCenter
    AutoSize = False
    TabOrder = 1
  end
  object LogsMemo: TMemo
    Left = 8
    Top = 101
    Width = 419
    Height = 391
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
  end
  object StopReadBtn: TButton
    Left = 8
    Top = 39
    Width = 129
    Height = 25
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100
    Enabled = False
    TabOrder = 3
    OnClick = StopReadBtnClick
  end
end
