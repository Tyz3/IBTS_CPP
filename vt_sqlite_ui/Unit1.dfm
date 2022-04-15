object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = 'Chrome History Viewer'
  ClientHeight = 361
  ClientWidth = 566
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  GlassFrame.Enabled = True
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 143
    Top = 304
    Width = 82
    Height = 18
    AutoSize = False
    Caption = #1055#1086#1089#1077#1097#1077#1085#1080#1081
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 231
    Top = 304
    Width = 41
    Height = 18
    Alignment = taRightJustify
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object DebugLabel: TLabel
    Left = 8
    Top = 8
    Width = 550
    Height = 34
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 48
    Width = 550
    Height = 249
    Header.AutoSizeIndex = 0
    Header.Height = 23
    Header.Options = [hoColumnResize, hoDrag, hoShowImages, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnAddToSelection = VirtualStringTree1AddToSelection
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 70
      end
      item
        Position = 1
        Text = #1057#1089#1099#1083#1082#1072
        Width = 210
      end
      item
        BiDiMode = bdLeftToRight
        Options = [coAllowClick, coDraggable, coEnabled, coParentColor, coResizable, coShowDropMark, coVisible, coAllowFocus, coUseCaptionAlignment, coEditable, coStyleColor]
        Position = 2
        Text = #1047#1072#1075#1086#1083#1086#1074#1086#1082
        Width = 265
      end>
  end
  object FillButton: TButton
    Left = 8
    Top = 303
    Width = 129
    Height = 50
    Caption = #1047#1072#1087#1086#1083#1085#1080#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = FillButtonClick
  end
  object RemoveLineButton: TButton
    Left = 143
    Top = 328
    Width = 129
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = RemoveLineButtonClick
  end
  object DropTableButton: TButton
    Left = 429
    Top = 328
    Width = 129
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Calibri'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = DropTableButtonClick
  end
  object FileDialog: TOpenTextFileDialog
    FileName = 'History.db'
    InitialDir = '.'
    Left = 48
    Top = 88
  end
end
