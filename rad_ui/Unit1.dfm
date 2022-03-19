object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Form1'
  ClientHeight = 218
  ClientWidth = 481
  Color = clBtnHighlight
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 96
  TextHeight = 15
  object rad_gn_label: TLabel
    Left = 256
    Top = 35
    Width = 200
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object rad_sn_label: TLabel
    Left = 256
    Top = 66
    Width = 200
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object vs_gn_label: TLabel
    Left = 256
    Top = 139
    Width = 200
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object vs_sn_label: TLabel
    Left = 256
    Top = 170
    Width = 200
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object rad_head_label: TLabel
    Left = 8
    Top = 8
    Width = 110
    Height = 21
    Caption = 'RAD Studio DLL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object vs_head_label: TLabel
    Left = 8
    Top = 112
    Width = 121
    Height = 21
    Caption = 'Visual Studio DLL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object rad_gn_btn: TButton
    Left = 8
    Top = 35
    Width = 225
    Height = 25
    Caption = #1053#1086#1084#1077#1088' '#1075#1088#1091#1087#1087#1099' (RAD)'
    TabOrder = 0
    OnClick = rad_gn_btnClick
  end
  object rad_sn_btn: TButton
    Left = 8
    Top = 66
    Width = 225
    Height = 25
    Caption = #1060#1048#1054' '#1089#1090#1091#1076#1077#1085#1090#1072' (RAD)'
    TabOrder = 1
    OnClick = rad_sn_btnClick
  end
  object vs_gn_btn: TButton
    Left = 8
    Top = 139
    Width = 225
    Height = 25
    Caption = #1053#1086#1084#1077#1088' '#1075#1088#1091#1087#1087#1099' (VS)'
    TabOrder = 2
    OnClick = vs_gn_btnClick
  end
  object vs_sn_btn: TButton
    Left = 8
    Top = 170
    Width = 225
    Height = 25
    Caption = #1060#1072#1084#1080#1083#1080#1103' '#1080' '#1048#1084#1103' '#1089#1090#1091#1076#1077#1085#1090#1072' (VS)'
    TabOrder = 3
    OnClick = vs_sn_btnClick
  end
end
