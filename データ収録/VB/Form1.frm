VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  '固定ﾀﾞｲｱﾛｸﾞ
   Caption         =   "測定条件の設定"
   ClientHeight    =   2055
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4125
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2055
   ScaleWidth      =   4125
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'ｵｰﾅｰ ﾌｫｰﾑの中央
   Begin VB.CommandButton cmdCancel 
      Caption         =   "ｷｬﾝｾﾙ"
      Height          =   375
      Left            =   2520
      TabIndex        =   11
      Top             =   720
      Width           =   1455
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   2520
      TabIndex        =   10
      Top             =   240
      Width           =   1455
   End
   Begin VB.TextBox txtLcl 
      Height          =   270
      Left            =   1200
      TabIndex        =   9
      Top             =   1680
      Width           =   975
   End
   Begin VB.TextBox txtUcl 
      Height          =   270
      Left            =   1200
      TabIndex        =   7
      Top             =   1320
      Width           =   975
   End
   Begin VB.TextBox txtStd 
      Height          =   270
      Left            =   1200
      TabIndex        =   5
      Top             =   960
      Width           =   975
   End
   Begin VB.ComboBox cmbHoko 
      Height          =   300
      ItemData        =   "Form1.frx":000C
      Left            =   1200
      List            =   "Form1.frx":0019
      TabIndex        =   3
      Top             =   600
      Width           =   975
   End
   Begin VB.TextBox txtItem 
      Height          =   270
      Left            =   1200
      TabIndex        =   1
      Top             =   240
      Width           =   975
   End
   Begin VB.Label Label5 
      Alignment       =   1  '右揃え
      Caption         =   "下限"
      Height          =   255
      Left            =   360
      TabIndex        =   8
      Top             =   1680
      Width           =   615
   End
   Begin VB.Label Label4 
      Alignment       =   1  '右揃え
      Caption         =   "上限"
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   1320
      Width           =   615
   End
   Begin VB.Label Label3 
      Alignment       =   1  '右揃え
      Caption         =   "規格値"
      Height          =   255
      Left            =   360
      TabIndex        =   4
      Top             =   960
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "測定方向"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   600
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "測定項目"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim hokoidx As Integer

Private Sub cmbHoko_Click()
    hokoidx = cmbHoko.ItemData(cmbHoko.ListIndex)
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    ITEM(SELCOL) = Trim(txtItem.Text)
    JYUN(SELCOL) = hokoidx
    MSTST(SELCOL) = CSng(txtStd.Text)
    MSTUL(SELCOL) = CSng(txtUcl.Text)
    MSTLL(SELCOL) = CSng(txtLcl.Text)
    MSTMAX(SELCOL) = MSTST(SELCOL) + MSTUL(SELCOL)
    MSTMIN(SELCOL) = MSTST(SELCOL) + MSTLL(SELCOL)
    Unload Me
End Sub

Private Sub Form_Load()
    txtItem.Text = frmMain.Fg2.TextArray(Fgi(0, SELCOL))
    hokoidx = JYUN(SELCOL)
    cmbHoko.Text = cmbHoko.List(JYUN(SELCOL) - 1)
    txtStd.Text = Format(MSTST(SELCOL), "###0.00")
    txtUcl.Text = Format(MSTUL(SELCOL), "###0.00")
    txtLcl.Text = Format(MSTLL(SELCOL), "###0.00")
End Sub
