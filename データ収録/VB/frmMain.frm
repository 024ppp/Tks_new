VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmMain 
   Caption         =   "ＰＱＣ７１０５データ測定（サンプルソフト）"
   ClientHeight    =   5475
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   5685
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5475
   ScaleWidth      =   5685
   StartUpPosition =   3  'Windows の既定値
   Begin VB.PictureBox picIF 
      BorderStyle     =   0  'なし
      Height          =   1695
      Left            =   120
      ScaleHeight     =   1695
      ScaleWidth      =   5415
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   120
      Width           =   5415
      Begin VB.Frame Frame1 
         Caption         =   "ﾌﾞｻﾞｰ設定"
         BeginProperty Font 
            Name            =   "ＭＳ Ｐゴシック"
            Size            =   9
            Charset         =   128
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   855
         Left            =   3480
         TabIndex        =   19
         Top             =   120
         Width           =   1815
         Begin VB.PictureBox picBuzzer 
            BorderStyle     =   0  'なし
            Height          =   375
            Left            =   240
            MouseIcon       =   "frmMain.frx":0442
            MousePointer    =   99  'ﾕｰｻﾞｰ定義
            ScaleHeight     =   375
            ScaleWidth      =   1335
            TabIndex        =   20
            Top             =   240
            Width           =   1335
            Begin VB.Label lblBuzzerOn 
               Caption         =   "ﾌﾞｻﾞｰ[ON]"
               Height          =   180
               Left            =   360
               TabIndex        =   21
               Top             =   120
               Width           =   885
            End
            Begin VB.Shape shpBuzzerOn 
               FillColor       =   &H0080FF80&
               FillStyle       =   0  '塗りつぶし
               Height          =   135
               Left            =   120
               Shape           =   3  '円
               Top             =   140
               Width           =   135
            End
            Begin VB.Label lblBuzzerOff 
               Caption         =   "ﾌﾞｻﾞｰ[OFF]"
               Height          =   180
               Left            =   360
               TabIndex        =   22
               Top             =   120
               Width           =   885
            End
            Begin VB.Shape shpBuzzerOff 
               FillColor       =   &H000000FF&
               FillStyle       =   0  '塗りつぶし
               Height          =   135
               Left            =   120
               Shape           =   3  '円
               Top             =   140
               Width           =   135
            End
         End
      End
      Begin VB.PictureBox picPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Index           =   4
         Left            =   2280
         MouseIcon       =   "frmMain.frx":074C
         MousePointer    =   99  'ﾕｰｻﾞｰ定義
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   7
         TabStop         =   0   'False
         ToolTipText     =   "測定ﾎﾟｰﾄを[５]に切り替えます。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpPort 
            FillColor       =   &H00000080&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Index           =   4
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.PictureBox picPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Index           =   3
         Left            =   1800
         MouseIcon       =   "frmMain.frx":0A56
         MousePointer    =   99  'ﾕｰｻﾞｰ定義
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   6
         TabStop         =   0   'False
         ToolTipText     =   "測定ﾎﾟｰﾄを[４]に切り替えます。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpPort 
            FillColor       =   &H00000080&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Index           =   3
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.PictureBox picPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Index           =   2
         Left            =   1320
         MouseIcon       =   "frmMain.frx":0D60
         MousePointer    =   99  'ﾕｰｻﾞｰ定義
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   5
         TabStop         =   0   'False
         ToolTipText     =   "測定ﾎﾟｰﾄを[３]に切り替えます。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpPort 
            FillColor       =   &H00000080&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Index           =   2
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.PictureBox picPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Index           =   0
         Left            =   360
         MouseIcon       =   "frmMain.frx":106A
         MousePointer    =   99  'ﾕｰｻﾞｰ定義
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   4
         TabStop         =   0   'False
         ToolTipText     =   "測定ﾎﾟｰﾄを[１]に切り替えます。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpPort 
            FillColor       =   &H00000080&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Index           =   1
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.PictureBox picPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Index           =   1
         Left            =   840
         MouseIcon       =   "frmMain.frx":1374
         MousePointer    =   99  'ﾕｰｻﾞｰ定義
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   3
         TabStop         =   0   'False
         ToolTipText     =   "測定ﾎﾟｰﾄを[２]に切り替えます。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpPort 
            FillColor       =   &H00000080&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Index           =   0
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.PictureBox picOnPort 
         BackColor       =   &H00C0FFFF&
         BorderStyle     =   0  'なし
         Height          =   135
         Left            =   360
         ScaleHeight     =   135
         ScaleWidth      =   255
         TabIndex        =   8
         TabStop         =   0   'False
         ToolTipText     =   "現在、設定されている測定ﾎﾟｰﾄです。"
         Top             =   480
         Width           =   255
         Begin VB.Shape shpOnPort 
            FillColor       =   &H000000FF&
            FillStyle       =   0  '塗りつぶし
            Height          =   135
            Left            =   0
            Shape           =   3  '円
            Top             =   0
            Width           =   255
         End
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   " (ｸﾘｯｸするとﾎﾟｰﾄを変更できます。)"
         Height          =   180
         Index           =   1
         Left            =   2400
         TabIndex        =   18
         Top             =   1440
         Width           =   2670
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "I/F PQC7105"
         BeginProperty Font 
            Name            =   "Times New Roman"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   120
         TabIndex        =   17
         Top             =   0
         Width           =   1125
      End
      Begin VB.Shape Shape3 
         FillColor       =   &H00000080&
         FillStyle       =   0  '塗りつぶし
         Height          =   135
         Index           =   1
         Left            =   120
         Shape           =   3  '円
         Top             =   1440
         Width           =   255
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "：測定不可能なﾎﾟｰﾄです。"
         Height          =   180
         Index           =   0
         Left            =   360
         TabIndex        =   16
         Top             =   1440
         Width           =   1995
      End
      Begin VB.Shape Shape3 
         FillColor       =   &H000000FF&
         FillStyle       =   0  '塗りつぶし
         Height          =   135
         Index           =   0
         Left            =   120
         Shape           =   3  '円
         Top             =   1200
         Width           =   255
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "：測定可能なﾎﾟｰﾄです。"
         Height          =   180
         Left            =   360
         TabIndex        =   15
         Top             =   1200
         Width           =   1815
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "power"
         BeginProperty Font 
            Name            =   "ＭＳ Ｐゴシック"
            Size            =   8.25
            Charset         =   128
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   165
         Left            =   2640
         TabIndex        =   14
         Top             =   280
         Width           =   420
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "5"
         Height          =   180
         Index           =   4
         Left            =   2370
         TabIndex        =   13
         Top             =   285
         Width           =   90
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "4"
         Height          =   180
         Index           =   3
         Left            =   1890
         TabIndex        =   12
         Top             =   280
         Width           =   90
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "3"
         Height          =   180
         Index           =   2
         Left            =   1410
         TabIndex        =   11
         Top             =   280
         Width           =   90
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "2"
         Height          =   180
         Index           =   1
         Left            =   930
         TabIndex        =   10
         Top             =   280
         Width           =   90
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         BackStyle       =   0  '透明
         Caption         =   "1"
         Height          =   180
         Index           =   0
         Left            =   470
         TabIndex        =   9
         Top             =   285
         Width           =   90
      End
      Begin VB.Shape Shape4 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Left            =   2760
         Shape           =   3  '円
         Top             =   720
         Width           =   255
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Index           =   4
         Left            =   2160
         Top             =   720
         Width           =   495
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Index           =   3
         Left            =   1680
         Top             =   720
         Width           =   495
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Index           =   2
         Left            =   1200
         Top             =   720
         Width           =   495
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Index           =   1
         Left            =   720
         Top             =   720
         Width           =   495
      End
      Begin VB.Shape Shape2 
         FillStyle       =   0  '塗りつぶし
         Height          =   255
         Index           =   0
         Left            =   240
         Top             =   720
         Width           =   495
      End
      Begin VB.Shape shpPowerOff 
         FillColor       =   &H00008000&
         FillStyle       =   0  '塗りつぶし
         Height          =   135
         Left            =   2760
         Shape           =   3  '円
         Top             =   480
         Width           =   255
      End
      Begin VB.Shape shpPowerOn 
         FillColor       =   &H0080FF80&
         FillStyle       =   0  '塗りつぶし
         Height          =   135
         Left            =   2760
         Shape           =   3  '円
         Top             =   480
         Width           =   255
      End
      Begin VB.Shape Shape1 
         FillColor       =   &H00C0FFFF&
         FillStyle       =   0  '塗りつぶし
         Height          =   855
         Left            =   120
         Shape           =   4  '丸みのある長方形
         Top             =   240
         Width           =   3135
      End
   End
   Begin VB.TextBox txtEdit 
      BackColor       =   &H0000FFFF&
      BorderStyle     =   0  'なし
      BeginProperty Font 
         Name            =   "ＭＳ 明朝"
         Size            =   9
         Charset         =   128
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000000&
      Height          =   255
      Left            =   240
      TabIndex        =   1
      TabStop         =   0   'False
      Text            =   "Text1"
      Top             =   2160
      Visible         =   0   'False
      Width           =   975
   End
   Begin MSFlexGridLib.MSFlexGrid Fg2 
      Height          =   3420
      Left            =   120
      TabIndex        =   0
      ToolTipText     =   "[測定器]・[ｷｰﾎﾞｰﾄﾞ]どちらからでも入力できます。"
      Top             =   1920
      Width           =   5415
      _ExtentX        =   9551
      _ExtentY        =   6033
      _Version        =   393216
      Rows            =   24
      Cols            =   11
      FixedRows       =   4
      BackColor       =   12648447
      BackColorFixed  =   8388608
      ForeColorFixed  =   65280
      BackColorBkg    =   12632256
      GridColor       =   8421504
      AllowBigSelection=   0   'False
      Enabled         =   -1  'True
      FocusRect       =   2
      FillStyle       =   1
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   0
      Top             =   4560
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      InBufferSize    =   2048
      InputLen        =   1
      NullDiscard     =   -1  'True
      OutBufferSize   =   1024
      ParityReplace   =   0
      RThreshold      =   1
      RTSEnable       =   -1  'True
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'/**********************************************************/
'   [機能概要]  | ＰＱＣ７１０５用サンプルソフト
'    　　　　   |                   By H.Sakaue  1998/04/10
'   [動作環境]  | Windows95以上
'   [開発環境]  | Windows95 OSR 2.0/ Visual Basic 5.0 Pro SP2
'/**********************************************************/
Option Explicit

Dim MSGTITL As String, MSGGID As String
Dim MOV(1 To 3) As String

Dim BUZZERFLG As Boolean

'<RS232C通信関係>
Dim RCVBF As String         '受信ﾃﾞｰﾀ格納ﾊﾞｯﾌｧ
Dim RCVFLG As Boolean       '受信完了ﾌﾗｸﾞ [True]:完了  [False]:未完了
Dim RCVDATAFLG As Boolean   '測定ﾃﾞｰﾀ受信待ちﾌﾗｸﾞ

'I/F→1文字毎受信
'
'   1文字受信毎に受信ﾊﾞｯﾌｧにﾃﾞｰﾀをｾｯﾄする。ﾀｰﾐﾈｰﾀｰ[CR]を受信時に受信完了ﾌﾗｸﾞを真[True]にする。
Private Sub RCVtoTRM(RecvData As String)
    'ﾀｰﾐﾈｰﾀｰまで1文字毎に受信ﾊﾞｯﾌｧにｾｯﾄする(ﾀｰﾐﾈｰﾀｰは受信ﾊﾞｯﾌｧにｾｯﾄしない)
    If RecvData = vbCr Then
        RCVFLG = True
    Else
        RCVBF = RCVBF + RecvData
    End If
        
    '測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ送信時のI/Fﾘﾀｰﾝ値をﾁｪｯｸする
    If RCVFLG = True And RCVDATAFLG = True Then
        'I/Fﾘﾀｰﾝ値 <STX><ﾎﾟｰﾄNo><ﾃﾞｰﾀ> の時、ﾃﾞｰﾀを抜き出しｾｯﾄする
        If Mid$(RCVBF, 1, 1) = Chr$(&H2) Then
            MSFlexGridEdit Fg2, txtEdit, 32
            txtEdit = Mid$(RCVBF, 3, 11)
            EditKeyCode Fg2, txtEdit, 13, 0
        
        'I/Fﾘﾀｰﾝ値 <EOT> の時、再度測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞを送信する
        ElseIf Mid$(RCVBF, 1, 1) = Chr$(&H4) Then
            '測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ送信
            MeasureInputDataWait
        
        'I/Fﾘﾀｰﾝ値が上記以外の時、再度測定要求ｺﾏﾝﾄﾞから送信する
        Else
            '測定要求ｺﾏﾝﾄﾞ送信
            MeasureReqest PORT(Fg2.Col)
        End If
    End If
End Sub

'I/F←測定要求ｺﾏﾝﾄﾞ送信
'
'   測定要求ｺﾏﾝﾄﾞ[<EOT><ﾎﾟｰﾄNo><CR>]を送信する。
'   I/Fﾘﾀｰﾝ値が、<ACK>時は測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ[<ENQ><CR>]を送信する。
Private Sub MeasureReqest(ptno As Integer)
MeasureReqest_Loop:
    RCVFLG = False: RCVDATAFLG = False: RCVBF = ""
    
    '測定要求ｺﾏﾝﾄﾞ送信  <EOT><ﾎﾟｰﾄNo><CR>
    MSComm1.Output = Chr$(&H4) & CStr(ptno) & vbCr

    'ﾘﾀｰﾝ値受信待ち
    Do
        DoEvents
        'RS232Cﾎﾟｰﾄｸﾛｰｽﾞ時は、強制的に抜ける
        If MSComm1.PortOpen = False Then
            Exit Sub
        End If
    Loop Until RCVFLG = True

    'I/Fﾘﾀｰﾝ値ﾁｪｯｸ
    '<ACK> の時
    If Mid$(RCVBF, 1, 1) = Chr$(&H6) Then
        '測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ送信
        MeasureInputDataWait
    '<ACK> 以外の時
    Else
        '再送信
        GoTo MeasureReqest_Loop
    End If
End Sub

'I/F←測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ送信
'
'   測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ[<ENQ><CR>]を送信する。
Private Sub MeasureInputDataWait()
    RCVFLG = False: RCVDATAFLG = True: RCVBF = ""
    
    '測定ﾃﾞｰﾀ入力待ちｺﾏﾝﾄﾞ送信  <ENQ><CR>
    MSComm1.Output = Chr$(&H5) & vbCr
End Sub

'I/F←測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信
'
'   測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ[<EOT><C><CR>]を送信する。
Private Sub MeasureReqestCancel()
    '測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信  <EOT><C><CR>
    MSComm1.Output = Chr$(&H4) & "C" & vbCr
End Sub

'I/F←OKﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信
'
'   OKﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ[<EOT><O><CR>]を送信する。
Private Sub MeasureOKBuzzer()
    'OKﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信  <EOT><O><CR>
'    MSComm1.Output = Chr$(&H4) & "O" & vbCr
End Sub

'I/F←NGﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信
'
'   NGﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ[<EOT><N><CR>]を送信する。
Private Sub MeasureNGBuzzer()
    'NGﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信  <EOT><N><CR>
'    MSComm1.Output = Chr$(&H4) & "N" & vbCr
End Sub

'フォーム上のＩ／Ｆのポートを点灯させます
Private Sub PortOnMove(ptno As Integer)
    picOnPort.Top = picPort(ptno - 1).Top
    picOnPort.Left = picPort(ptno - 1).Left
    picOnPort.ZOrder
End Sub

'単精度浮動小数点型の値(dt)を指定小数点(dp)で編集し8ﾊﾞｲﾄの文字列型に変換する。
Private Function EDITtypeSngtoStr(dt As Single, dp As Integer) As String
    Dim strTemp As String
    Select Case dp
        Case 0
            strTemp = Format(CStr(Format(dt, "#######0")), "@@@@@@@@")
        Case 1
            strTemp = Format(CStr(Format(dt, "#####0.0")), "@@@@@@@@")
        Case 2
            strTemp = Format(CStr(Format(dt, "####0.00")), "@@@@@@@@")
        Case 3
            strTemp = Format(CStr(Format(dt, "###0.000")), "@@@@@@@@")
        Case 4
            strTemp = Format(CStr(Format(dt, "##0.0000")), "@@@@@@@@")
        Case 5
            strTemp = Format(CStr(Format(dt, "#0.00000")), "@@@@@@@@")
        Case 6
            strTemp = Format(CStr(Format(dt, "0.000000")), "@@@@@@@@")
        Case Else
            strTemp = "********"
    End Select
    EDITtypeSngtoStr = Trim$(strTemp)
End Function

Private Sub MSFlexGridEdit(MSFlexGrid As Control, _
                    Edt As Control, KeyAscii As Integer)
    '入力された文字を使います
    Select Case KeyAscii
        '空白は、現在のテキストの編集を示します
        Case 0 To 32
            Edt = MSFlexGrid
            Edt.SelStart = 1000
    
        'そのほかは、現在のテキストを置き換えます
        Case Else
            Edt = Chr(KeyAscii)
            Edt.SelStart = 1
    End Select
    
    '右側に Edt を表示します
    With MSFlexGrid
        Edt.Move .Left + .CellLeft, .Top + .CellTop, .CellWidth, .CellHeight
    End With
    Edt.Visible = True
    
    '実行します
    Edt.SetFocus
End Sub

Private Sub EditKeyCode(MSFlexGrid As Control, Edt As _
                Control, KeyCode As Integer, Shift As Integer)
    Dim sngTemp As Single
    Dim i As Integer

    '標準の編集コントールの処理です
    Select Case KeyCode
        Case 27         'Esc キーは、非表示にしてフォーカスを MSFlexGrid に戻す
            Edt.Visible = False
            MSFlexGrid.SetFocus
    
        Case 13         'Enter キー
            sngTemp = Val(Edt)
            '測定ﾃﾞｰﾀ規格ﾁｪｯｸ
            If sngTemp > MSTMAX(MSFlexGrid.Col) Or sngTemp < MSTMIN(MSFlexGrid.Col) Then
                MSFlexGrid.CellForeColor = QBColor(12)
                'ﾌﾞｻﾞｰ[ON]の時
                If BUZZERFLG = True Then
                    'NGﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信
                    MeasureNGBuzzer
                End If
            Else
                MSFlexGrid.CellForeColor = QBColor(9)
                'ﾌﾞｻﾞｰ[ON]の時
                If BUZZERFLG = True Then
                    'OKﾌﾞｻﾞｰ音発生ｺﾏﾝﾄﾞ送信
                    MeasureOKBuzzer
                End If
            End If
            'ｾﾙにﾃﾞｰﾀをｾｯﾄする
            MSFlexGrid = EDITtypeSngtoStr(sngTemp, DATADP(MSFlexGrid.Col))
            MSFlexGrid.SetFocus
            DoEvents
            '測定方向に従ってｾﾙを進める
            If JYUN(MSFlexGrid.Col) = 1 Then
                If MSFlexGrid.Row < MSFlexGrid.Rows - 1 Then
                    MSFlexGrid.Row = MSFlexGrid.Row + 1
                Else
                    MSFlexGrid.Row = MSFlexGrid.FixedRows
                End If
            ElseIf JYUN(MSFlexGrid.Col) = 2 Then
                If MSFlexGrid.Col < MSFlexGrid.Cols - 1 Then
                    MSFlexGrid.Col = MSFlexGrid.Col + 1
                End If
            ElseIf JYUN(MSFlexGrid.Col) = 3 Then
                If MSFlexGrid.Row < MSFlexGrid.Rows - 1 Then
                    MSFlexGrid.Row = MSFlexGrid.Row + 1
                Else
                    MSFlexGrid.Row = MSFlexGrid.FixedRows
                End If
                For i = MSFlexGrid.Col To MSFlexGrid.FixedCols + 1 Step -1
                    If JYUN(i - 1) = 1 Or JYUN(i - 1) = 3 Then
                        Exit For
                    End If
                Next i
                MSFlexGrid.Col = i
            End If
            '移動したｾﾙが表示されているかﾁｪｯｸする
            If MSFlexGrid.RowIsVisible(MSFlexGrid.Row) = False Then
                MSFlexGrid.TopRow = MSFlexGrid.Row
            End If
            If MSFlexGrid.ColIsVisible(MSFlexGrid.Col) = False Then
                MSFlexGrid.LeftCol = MSFlexGrid.Col
            End If
    
        Case 38         '↑キー
            MSFlexGrid.SetFocus
            DoEvents
            If MSFlexGrid.Row > MSFlexGrid.FixedRows Then
                MSFlexGrid.Row = MSFlexGrid.Row - 1
            End If
    
        Case 40         '↓キー
            MSFlexGrid.SetFocus
            DoEvents
            If MSFlexGrid.Row < MSFlexGrid.Rows - 1 Then
                MSFlexGrid.Row = MSFlexGrid.Row + 1
            End If
    End Select
End Sub

Private Sub Fg2_DblClick()
    MSFlexGridEdit Fg2, txtEdit, 32         '空白を代入する
End Sub

Private Sub Fg2_GotFocus()
    If txtEdit.Visible = False Then Exit Sub
    txtEdit.Visible = False
End Sub

Private Sub Fg2_KeyPress(KeyAscii As Integer)
    MSFlexGridEdit Fg2, txtEdit, KeyAscii
End Sub

Private Sub Fg2_LeaveCell()
    If txtEdit.Visible = False Then Exit Sub
    txtEdit.Visible = False
End Sub

Private Sub Fg2_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim i As Integer
    
    If Button = 2 And y < (Fg2.CellHeight * 4) Then
        For i = 1 To 10
            If x >= (Fg2.CellWidth * i) And x <= (Fg2.CellWidth * (i + 1)) Then
                SELCOL = i
                Exit For
            End If
        Next i
        Form1.Show vbModal
        Fg2.TextArray(Fgi(0, SELCOL)) = ITEM(SELCOL)
        Fg2.TextArray(Fgi(1, SELCOL)) = MOV(JYUN(SELCOL))
        Fg2.TextArray(Fgi(2, SELCOL)) = EDITtypeSngtoStr(MSTMAX(SELCOL), DATADP(SELCOL))
        Fg2.TextArray(Fgi(3, SELCOL)) = EDITtypeSngtoStr(MSTMIN(SELCOL), DATADP(SELCOL))
    End If
End Sub

Private Sub Fg2_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    If y > (Fg2.CellHeight * 4) Then
        Fg2.ToolTipText = "[測定器]・[ｷｰﾎﾞｰﾄﾞ]どちらからでも入力できます。"
    Else
        Fg2.ToolTipText = "右ｸﾘｯｸで[測定項目]・[測定方向]・[規格上下限]が設定できます。"
    End If
End Sub

Private Sub Fg2_RowColChange()
    '測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信
    MeasureReqestCancel
    '測定要求ｺﾏﾝﾄﾞ送信
    MeasureReqest PORT(Fg2.Col)
    'ﾌｫｰﾑ上のI/Fのﾎﾟｰﾄ点灯
    PortOnMove PORT(Fg2.Col)
End Sub

Private Sub Fg2_Scroll()
    If txtEdit.Visible Then
        With Fg2
            txtEdit.Move .Left + .CellLeft, .Top + .CellTop, .CellWidth, .CellHeight
        End With
    End If
End Sub

Private Sub Form_Load()
    Dim strTemp As String
    Dim i As Integer, n As Integer
    
'<<初期処理>>
    MOV(1) = "↓": MOV(2) = "→": MOV(3) = "←"
    BUZZERFLG = True
    '小数点・規格値・上限値・下限値設定
    For i = 1 To 10
        Select Case i
            Case 1
                strTemp = "Ａ"
            Case 2
                strTemp = "Ｂ"
            Case 3
                strTemp = "Ｃ"
            Case 4
                strTemp = "Ｄ"
            Case 5
                strTemp = "Ｅ"
            Case 6
                strTemp = "Ｆ"
            Case 7
                strTemp = "Ｇ"
            Case 8
                strTemp = "Ｈ"
            Case 9
                strTemp = "Ｉ"
            Case 10
                strTemp = "Ｊ"
        End Select
        ITEM(i) = strTemp
        DATADP(i) = 2
        MSTST(i) = 9! + i
        MSTUL(i) = 0.5
        MSTLL(i) = -0.5
        MSTMAX(i) = MSTST(i) + MSTUL(i)
        MSTMIN(i) = MSTST(i) + MSTLL(i)
    Next i
    '測定方向設定
    JYUN(1) = 1: JYUN(2) = 2: JYUN(3) = 3: JYUN(4) = 2: JYUN(5) = 3
    JYUN(6) = 2: JYUN(7) = 2: JYUN(8) = 2: JYUN(9) = 2: JYUN(10) = 3
    'ﾎﾟｰﾄ番号設定
    PORT(1) = 1: PORT(2) = 2: PORT(3) = 3: PORT(4) = 4: PORT(5) = 5
    PORT(6) = 1: PORT(7) = 2: PORT(8) = 3: PORT(9) = 4: PORT(10) = 5
    'ｸﾞｯﾘﾄﾞに設定値をｾｯﾄする
    Fg2.ColWidth(0) = 1000
    For i = 0 To 10
        Fg2.FixedAlignment(i) = 4
    Next i
    Fg2.TextArray(Fgi(0, 0)) = "測定項目"
    For i = 1 To 10
        Fg2.TextArray(Fgi(0, i)) = ITEM(i)
    Next i
    Fg2.TextArray(Fgi(1, 0)) = "測定方向"
    For i = 1 To 10
        Fg2.TextArray(Fgi(1, i)) = MOV(JYUN(i))
    Next i
    Fg2.TextArray(Fgi(2, 0)) = "規格上限"
    For i = 1 To 10
        Fg2.TextArray(Fgi(2, i)) = EDITtypeSngtoStr(MSTMAX(i), DATADP(i))
    Next i
    Fg2.TextArray(Fgi(3, 0)) = "規格下限"
    For i = 1 To 10
        Fg2.TextArray(Fgi(3, i)) = EDITtypeSngtoStr(MSTMIN(i), DATADP(i))
    Next i
    n = 0
    For i = Fg2.FixedRows To Fg2.Rows - 1
        n = n + 1
        Fg2.TextArray(Fgi(i, 0)) = n
    Next i
    
    Me.Show
    
    '編集ボックスを初期化し、ここでロードする
    txtEdit = ""
    
    'RS232Cﾎﾟｰﾄｵｰﾌﾟﾝ
    MSComm1.PortOpen = True

    '測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信
    MeasureReqestCancel
    '測定要求ｺﾏﾝﾄﾞ送信
    MeasureReqest PORT(Fg2.Col)
    'ﾌｫｰﾑ上のI/FのPOWER点灯
    shpPowerOn.ZOrder
    'ﾌｫｰﾑ上のI/Fのﾎﾟｰﾄ点灯
    PortOnMove PORT(Fg2.Col)
End Sub

Private Sub Form_Resize()
    If Me.WindowState <> 1 Then
        Fg2.Width = Me.Width - 360
        Fg2.Height = Me.Height - Fg2.Top - 480
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'ﾌｫｰﾑ上のI/FのPOWER消灯
    shpPowerOff.ZOrder
    '測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信
    MeasureReqestCancel
    'RS232Cﾎﾟｰﾄｸﾛｰｽﾞ
    MSComm1.PortOpen = False
    End
End Sub

Private Sub MSComm1_OnComm()
    '最新の通信ｲﾍﾞﾝﾄ・ｴﾗｰ
    Select Case MSComm1.CommEvent
        '通信ｲﾍﾞﾝﾄ
        Case comEvReceive           '[RThreshold指定文字数受信]
            '1文字受信毎に受信ﾃﾞｰﾀをｾｯﾄする
            Call RCVtoTRM(MSComm1.Input)
        '通信ｴﾗｰ値
        Case comRxOver              '[受信ﾊﾞｯﾌｧｵｰﾊﾞｰﾌﾛｰ]
            '受信ﾊﾞｯﾌｧｰｸﾘｱｰ
            MSComm1.InBufferCount = 0
        Case comTxFull              '[伝送ﾊﾞｯﾌｧｵｰﾊﾞｰﾌﾛｰ]
            '伝送ﾊﾞｯﾌｧｰｸﾘｱｰ
            MSComm1.OutBufferCount = 0
    End Select
End Sub

Private Sub picBuzzer_Click()
    If BUZZERFLG = False Then
        BUZZERFLG = True
        shpBuzzerOn.ZOrder
        lblBuzzerOn.ZOrder
    Else
        BUZZERFLG = False
        shpBuzzerOff.ZOrder
        lblBuzzerOff.ZOrder
    End If
    Fg2.SetFocus
End Sub

Private Sub picIF_Click()
    Fg2.SetFocus
End Sub

Private Sub picOnPort_Click()
    Fg2.SetFocus
End Sub

Private Sub picPort_Click(Index As Integer)
    PORT(Fg2.Col) = Index + 1
    '測定要求ｷｬﾝｾﾙｺﾏﾝﾄﾞ送信
    MeasureReqestCancel
    '測定要求ｺﾏﾝﾄﾞ送信
    MeasureReqest PORT(Fg2.Col)
    'ﾌｫｰﾑ上のI/Fのﾎﾟｰﾄ点灯
    PortOnMove PORT(Fg2.Col)
    
    Fg2.TextArray(Fgi(1, Fg2.Col)) = MOV(JYUN(Fg2.Col))
    Fg2.SetFocus
End Sub

Private Sub txtEdit_KeyDown(KeyCode As Integer, Shift As Integer)
    EditKeyCode Fg2, txtEdit, KeyCode, Shift
End Sub

Private Sub txtEdit_KeyPress(KeyAscii As Integer)
    Dim sngTemp As Single
    
    '改行文字を削除し、警告音が発生しないようにする
    If KeyAscii = Asc(vbCr) Then
        KeyAscii = 0
    End If
End Sub
