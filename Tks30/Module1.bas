Attribute VB_Name = "Module1"

Sub Auto_close()
    'MsgBox "�I��"
End Sub
Sub Auto_open()
    Dim SelectKey As Integer
    
    SelectKey = GetControl
    'MsgBox SelectKey
    Select Case SelectKey
        Case 0
            '���j���[ Excel���͗p
            'csv�Ƀf�[�^���������݂܂�
            ActiveWorkbook.Save
            Call Write_csv("�Г�", "�Г�.csv")
            Call Write_csv("�ЊO", "�ЊO.csv")
            'MsgBox ("Case 0 CSV�t�@�C���ɏo�͂��܂���")
        
        Case 1
            '���j���[ Excel�o�͗p
            'csv����f�[�^��Ǎ��݂܂�
            Call Read_csv("�Г�", "�Г�.csv")
            Call Read_csv("�ЊO", "�ЊO.csv")
            'SelectKey = MsgBox("�l����\���o�͂��܂����ydata.xls �Г�����, �ЊO����z�H", vbYesNo + vbQuestion, "����o��")
            'Select Case SelectKey
            'Case vbYes
            '    Call SyagaiKojin("�Г�", "�Г�����")
            '    Call SyagaiKojin("�ЊO", "�ЊO����")
            '    ActiveWorkbook.Save
            'Case vbNo
            '    Exit Sub
            'End Select
            ActiveWorkbook.Save
            'MsgBox ("Case 1 csv����f�[�^��Ǎ��݂܂�")
        
        Case 2
            '���j���[ ����o�͗p
            'SyagaiKojin
                Call SyagaiKojin("�Г�", "�Г�����")
                Call SyagaiKojin("�ЊO", "�ЊO����")
                ActiveWorkbook.Save
            'MsgBox ("Case 2 SyagaiKojin")
        Case 3
            '���j���[ �H���o�^�����p
            'csv����f�[�^��Ǎ��݂܂�
            Call Read_csv("�Г�", "�Г�.csv")
            Call Read_csv("�ЊO", "�ЊO.csv")
            ActiveWorkbook.Save
        Case 4
            '�V�[�g��\�����܂�
            'MsgBox ("Case 3")
        Case Else ' ���̑��̒l�̏ꍇ�B
            '�V�[�g��\�����܂�
            'MsgBox ("Case Else")
    End Select


End Sub

Public Function SyagaiKojin(sheetName1 As String, sheetName2 As String)
  Dim i As Integer, j As Integer, k As Integer
   'Dim MyXL As Object
   'Dim Worksheets As Object
   'Dim ExcelWasNotRunning As Boolean
   'Dim fileName As String
   'Dim sheetName As String
   
   Dim RowNo As Integer 'sheet1�̃f�[�^�̐�
   Dim check As Integer
 
   Dim SelectKey As Integer
  
  
  
    'SelectKey = MsgBox("�l����\���o�͂��܂����ydata.xls �Г�����, �ЊO����z�H", vbYesNo + vbQuestion, "����o��")
      
    'Select Case SelectKey
  
    'Case vbYes
     
        Sheets(sheetName2).Cells.Clear   'sheet3�̏�����
        
        check = 0
        RowNo = 0
        i = 1
        Do
            
            If RowNo > 1 Then
              For k = 2 To RowNo
                  '���������œ������ɓ����J�[�h�𓊓�����ꍇ
                  If Trim(Sheets(sheetName2).Cells(k, 1).Value) = Trim(Sheets(sheetName1).Cells(i, 1).Value) Then
                    For j = 12 To 42
                      If Trim(Sheets(sheetName1).Cells(i, j).Value) <> "" Then
                         Sheets(sheetName2).Cells(k, j).Value = Sheets(sheetName2).Cells(k, j).Value + Sheets(sheetName1).Cells(i, j).Value
                      Else
                        
                      End If
                    Next j
                    check = check + 1
                   Else
                   End If
              Next k
              'MsgBox check
              If check = 0 Then
                  'MsgBox "�������" & i
                  RowNo = RowNo + 1
                  Sheets(sheetName2).Cells(RowNo, 1).Value = Sheets(sheetName1).Cells(i, 1).Value '���O�̂�
                  For j = 12 To 42
                    If Trim(Sheets(sheetName1).Cells(i, j).Value) <> "" Then
                      Sheets(sheetName2).Cells(RowNo, j).Value = Sheets(sheetName1).Cells(i, j).Value
                    End If
                  Next j
                  
              End If
            
            Else
              '��P�s�y�тQ�s
              RowNo = RowNo + 1
              Sheets(sheetName2).Cells(RowNo, 1).Value = Sheets(sheetName1).Cells(i, 1).Value '���O�̂�
              For j = 12 To 42
                If Trim(Sheets(sheetName1).Cells(i, j).Value) <> "" Then
                  Sheets(sheetName2).Cells(RowNo, j).Value = Sheets(sheetName1).Cells(i, j).Value
                End If
              Next j
            End If
          
            
        i = i + 1
        check = 0
        Loop Until Trim(Sheets(sheetName1).Cells(i, 1).Value) = ""
        
        
        '�s�v�ȗ�̍폜
        Sheets(sheetName2).Columns("B:K").Delete
        '***************************************************************
        '�ȏ�ЊO�p
        
        '���t�̕\���`��
        For i = 2 To 32
          Sheets(sheetName2).Cells(1, i).NumberFormatLocal = "m/d"
        Next i
        
        Sheets(sheetName2).Columns.AutoFit
        
    'Case vbNo
    '   Exit Function
    'End Select
    
End Function


Public Function Write_csv(sheetName As String, CSVName As String)
    Dim i As Integer, j As Integer
    Dim nFileNum As Integer
    Dim Tflag As Boolean
    Dim DataCnt As Integer
    Dim CSVPath As String
    
    Sheets(sheetName).Select
    
    Tflag = True
    DataCnt = 1
    '�f�[�^���N���A����񐔂����߂�
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    CSVPath = ActiveWorkbook.Path
    'CSVName = "�Г�.csv"
    'write csv file
    nFileNum = FreeFile
    
    '�u�Г�.csv�v�ɕۊ�
    i = 0
    k = 0
    Open CSVPath & "\" & CSVName For Output As #nFileNum
    '�t�@�C���ɕ�������������݂܂��B
        Do Until Range("A1").Offset(i, 0) = ""
            For j = 0 To DataCnt
                Print #nFileNum, Range("A1").Offset(i, j); ",";
            Next j
            k = k + 1
            Print #nFileNum,
          i = i + 1
        Loop
    Close #nFileNum
    
    

End Function
Public Function GetControl() As Integer
    Dim nFileNum As Integer
    Dim sRec As String
    Dim ControlPath As String
    Dim ControlName As String

    ControlPath = ActiveWorkbook.Path
    ControlName = "control.ini"
    
    If Dir(ControlPath & "\" & ControlName) = ControlName Then
        'read csv file
        nFileNum = FreeFile
         
        Open ControlPath & "\" & ControlName For Input Access Read As #nFileNum
        
        'read a line from file
        Line Input #nFileNum, sRec
                    
        Close (nFileNum)
        
        Select Case sRec
            Case 0
                'csv�Ƀf�[�^���������݂܂�
                GetControl = 0
            Case 1
                'csv����f�[�^��Ǎ��݂܂�
                GetControl = 1
            Case 2
                'SyagaiKojin
                GetControl = 2
            Case 3
                '�H���o�^����
                GetControl = 3
            Case 4
                '�V�[�g��\�����܂�
                GetControl = 4
            Case Else ' ���̑��̒l�̏ꍇ�B
                '�V�[�g��\�����܂�
                GetControl = 4
        End Select
    Else
        'MsgBox ControlName
        '�V�[�g��\�����܂�
        GetControl = 4
    End If
        
End Function

Public Function Read_csv(sheetName As String, CSVName As String)
    Dim nFileNum As Integer
    Dim sRec As String
    Dim sWindows As String * 256
    Dim Tflag As Boolean
    Dim RecCnt As Integer
    Dim DataCnt As Integer
    Dim sRec1 As String
    Dim INI_FILENAME As String
    Dim CSVPath As String
    'Dim CSVName As String
    Dim ret As Integer
    Dim RangerVar As Object
    Dim Spos As Integer
    Dim rtn As Boolean
    Dim tempo As String
    'Dim SheetName As String
    Dim fileName As String

    'FileName = "datatest.xls"
    fileName = ActiveWorkbook.Name
    'SheetName = "�Г�"
    CSVPath = ActiveWorkbook.Path
    'CSVName = "�Г�.csv"
    
    Sheets(sheetName).Select


    'don't update screen during this operation
    '��ʂ��X�V�����Ȃ��悤�ɂ���
    Application.ScreenUpdating = False

    'L:\OA-N821�~��\����\�Г�.csv
    'CSVName2 = "L:\OA-N821�~��\����\�Г�.csv"
    'ActiveWorkbook.Path
    'CSVName2 = ActiveWorkbook.Path & "\�Г�.csv"
    'MsgBox CSVName2
    ' record count
    Tflag = True
    RecCnt = 1
    
    '�f�[�^���N���A����s�������߂�
    Do While (Tflag)
        If Range("A1").Offset(RecCnt, 0).Value = "" Then
            Tflag = False
        Else
            RecCnt = RecCnt + 1
        End If
    Loop
    RecCnt = RecCnt
    
    Tflag = True
    DataCnt = 1
    '�f�[�^���N���A����񐔂����߂�
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    ' delete all cell
    '�I��͈͂��琔���ƕ������N���A���܂��B
    Range(Cells(1, 1), Cells(RecCnt, DataCnt)).Select
    Selection.ClearContents
    
    'read csv file
    nFileNum = FreeFile
     
    Open CSVPath & "\" & CSVName For Input Access Read As #nFileNum
    
    j = 0
    
    Do While Not EOF(nFileNum)
        'read a line from file
        Line Input #nFileNum, sRec
        
        'get field and fill it to excel's cell
        llen = LenB(sRec)
        ret = 0
        Spos = 1
        j = j + 1
        For i = 1 To llen
            If Mid(sRec, i, 1) = "," Then
                Range("A1").Offset(j - 1, ret).Value = Mid(sRec, Spos, i - Spos)
                Spos = i + 1
                ret = ret + 1
            End If
        Next
        Range("A1").Offset(j, ret).Value = Mid(sRec, Spos, llen - Spos)
    Loop
    
        
    Close (nFileNum)
    
    'return to default
    '��ʂ��X�V������
    Application.ScreenUpdating = True
    Windows(fileName).Activate
    Range("A1").Select
    
'    '���t�̕\���`��
    For i = 12 To 42
      Range("A1").Offset(0, i - 1).NumberFormatLocal = "m/d"
    Next i

    Sheets(sheetName).Columns.AutoFit

    Range("A1").Select
    'MsgBox ("����")
End Function
Public Function Read_csv2(sheetName As String, CSVName As String)
    Dim nFileNum As Integer
    Dim sRec As String
    Dim sWindows As String * 256
    Dim Tflag As Boolean
    Dim RecCnt As Integer
    Dim DataCnt As Integer
    Dim sRec1 As String
    Dim INI_FILENAME As String
    Dim CSVPath As String
    'Dim CSVName As String
    Dim ret As Integer
    Dim RangerVar As Object
    Dim Spos As Integer
    Dim rtn As Boolean
    Dim tempo As String
    'Dim SheetName As String
    Dim fileName As String

    'FileName = "datatest.xls"
    fileName = ActiveWorkbook.Name
    'SheetName = "�Г�"
    CSVPath = ActiveWorkbook.Path
    'CSVName = "�Г�.csv"
    
    Sheets(sheetName).Select

    'don't update screen during this operation
    '��ʂ��X�V�����Ȃ��悤�ɂ���
    Application.ScreenUpdating = False
    
    ' record count
    Tflag = True
    RecCnt = 1
    
    '�f�[�^���N���A����s�������߂�
    Do While (Tflag)
        If Range("A1").Offset(RecCnt, 0).Value = "" Then
            Tflag = False
        Else
            RecCnt = RecCnt + 1
        End If
    Loop
    RecCnt = RecCnt
    
    Tflag = True
    DataCnt = 1
    '�f�[�^���N���A����񐔂����߂�
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    ' delete all cell
    '�I��͈͂��琔���ƕ������N���A����B
    Range(Cells(1, 1), Cells(RecCnt, DataCnt)).Select
    Selection.ClearContents
    
    
    'MsgBox CSVPath & "\" & CSVName
    'csv�t�@�C���u�Г�.csv�v�� �J��
    'Workbooks.OpenText FileName:=CSVPath & "\" & CSVName, StartRow:=1, _
        DataType:=xlDelimited, TextQualifier:=xlNone, ConsecutiveDelimiter:=False _
        , Tab:=False, Semicolon:=False, Comma:=True, Space:=False, Other:= _
        False, FieldInfo:=Array(Array(1, 2), Array(2, 2), Array(3, 2), Array(4, 2), Array(5, 2), _
                Array(6, 2), Array(7, 2), Array(8, 2), Array(9, 2), Array(10, 2), Array(11, 2))
    Windows(CSVName).Activate
    Cells.Select
    Selection.Copy
    
    'Excel�t�@�C���udata.xls�v���A�N�e�B�u�ɂ���
    Windows(fileName).Activate
    Range("A1").Select
    
    '�l�����\��t����
    Selection.PasteSpecial Paste:=xlValues, Operation:=xlNone, SkipBlanks:= _
        False, Transpose:=False
    Range("A1").Select
    
    'csv�t�@�C���u�Г�.csv�v���A�N�e�B�u�ɂ���
    Windows(CSVName).Activate
    Range("A1").Select
    
    '�R�s�[ ���[�h����������
    Application.CutCopyMode = False
    
    '�}�N���̎��s���ɓ���̌x���⃁�b�Z�[�W��\�����Ȃ��悤�ɂ���
    Application.DisplayAlerts = False
    
     'csv�t�@�C���u�Г�.csv�v�����
    ActiveWindow.Close
    
    '�}�N���̎��s���ɓ���̌x���⃁�b�Z�[�W��\������悤�ɂ���
    Application.DisplayAlerts = True
    
    Windows(fileName).Activate
    Range("A1").Select
'    '���t�̕\���`��
    For i = 12 To 42
      Range("A1").Offset(0, i - 1).NumberFormatLocal = "m/d"
    Next i

    Sheets(sheetName).Columns.AutoFit

    'MsgBox ("����")
    
End Function


