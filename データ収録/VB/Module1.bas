Attribute VB_Name = "Module1"
Option Explicit

'<設定関係>
Public ITEM(1 To 10) As String        '測定項目
Public JYUN(1 To 10) As Integer       '測定方向
Public PORT(1 To 10) As Integer       'ﾎﾟｰﾄ番号
Public KIKADP(1 To 10) As Integer, KOSADP(1 To 10) As Integer, DATADP(1 To 10) As Integer
Public MSTST(1 To 10) As Single, MSTUL(1 To 10) As Single, MSTLL(1 To 10) As Single
Public MSTMAX(1 To 10) As Single, MSTMIN(1 To 10) As Single

Public SELCOL As Integer


'インデックスを計算する関数
Public Function Fgi(r As Integer, c As Integer) As Integer
    Fgi = c + frmMain.Fg2.Cols * r
End Function

