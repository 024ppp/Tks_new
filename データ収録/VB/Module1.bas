Attribute VB_Name = "Module1"
Option Explicit

'<�ݒ�֌W>
Public ITEM(1 To 10) As String        '���荀��
Public JYUN(1 To 10) As Integer       '�������
Public PORT(1 To 10) As Integer       '�߰Ĕԍ�
Public KIKADP(1 To 10) As Integer, KOSADP(1 To 10) As Integer, DATADP(1 To 10) As Integer
Public MSTST(1 To 10) As Single, MSTUL(1 To 10) As Single, MSTLL(1 To 10) As Single
Public MSTMAX(1 To 10) As Single, MSTMIN(1 To 10) As Single

Public SELCOL As Integer


'�C���f�b�N�X���v�Z����֐�
Public Function Fgi(r As Integer, c As Integer) As Integer
    Fgi = c + frmMain.Fg2.Cols * r
End Function

