Attribute VB_Name = "Module1"

Sub Auto_close()
    'MsgBox "終了"
End Sub
Sub Auto_open()
    Dim SelectKey As Integer
    
    SelectKey = GetControl
    'MsgBox SelectKey
    Select Case SelectKey
        Case 0
            'メニュー Excel入力用
            'csvにデータを書き込みます
            ActiveWorkbook.Save
            Call Write_csv("社内", "社内.csv")
            Call Write_csv("社外", "社外.csv")
            'MsgBox ("Case 0 CSVファイルに出力しました")
        
        Case 1
            'メニュー Excel出力用
            'csvからデータを読込みます
            Call Read_csv("社内", "社内.csv")
            Call Read_csv("社外", "社外.csv")
            'SelectKey = MsgBox("個人日報表を出力しますか【data.xls 社内日報, 社外日報】？", vbYesNo + vbQuestion, "日報出力")
            'Select Case SelectKey
            'Case vbYes
            '    Call SyagaiKojin("社内", "社内日報")
            '    Call SyagaiKojin("社外", "社外日報")
            '    ActiveWorkbook.Save
            'Case vbNo
            '    Exit Sub
            'End Select
            ActiveWorkbook.Save
            'MsgBox ("Case 1 csvからデータを読込みます")
        
        Case 2
            'メニュー 日報出力用
            'SyagaiKojin
                Call SyagaiKojin("社内", "社内日報")
                Call SyagaiKojin("社外", "社外日報")
                ActiveWorkbook.Save
            'MsgBox ("Case 2 SyagaiKojin")
        Case 3
            'メニュー 工数登録処理用
            'csvからデータを読込みます
            Call Read_csv("社内", "社内.csv")
            Call Read_csv("社外", "社外.csv")
            ActiveWorkbook.Save
        Case 4
            'シートを表示します
            'MsgBox ("Case 3")
        Case Else ' その他の値の場合。
            'シートを表示します
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
   
   Dim RowNo As Integer 'sheet1のデータの数
   Dim check As Integer
 
   Dim SelectKey As Integer
  
  
  
    'SelectKey = MsgBox("個人日報表を出力しますか【data.xls 社内日報, 社外日報】？", vbYesNo + vbQuestion, "日報出力")
      
    'Select Case SelectKey
  
    'Case vbYes
     
        Sheets(sheetName2).Cells.Clear   'sheet3の初期化
        
        check = 0
        RowNo = 0
        i = 1
        Do
            
            If RowNo > 1 Then
              For k = 2 To RowNo
                  '同じ所属で同じ日に同じカードを投入する場合
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
                  'MsgBox "違ったよ" & i
                  RowNo = RowNo + 1
                  Sheets(sheetName2).Cells(RowNo, 1).Value = Sheets(sheetName1).Cells(i, 1).Value '名前のみ
                  For j = 12 To 42
                    If Trim(Sheets(sheetName1).Cells(i, j).Value) <> "" Then
                      Sheets(sheetName2).Cells(RowNo, j).Value = Sheets(sheetName1).Cells(i, j).Value
                    End If
                  Next j
                  
              End If
            
            Else
              '第１行及び２行
              RowNo = RowNo + 1
              Sheets(sheetName2).Cells(RowNo, 1).Value = Sheets(sheetName1).Cells(i, 1).Value '名前のみ
              For j = 12 To 42
                If Trim(Sheets(sheetName1).Cells(i, j).Value) <> "" Then
                  Sheets(sheetName2).Cells(RowNo, j).Value = Sheets(sheetName1).Cells(i, j).Value
                End If
              Next j
            End If
          
            
        i = i + 1
        check = 0
        Loop Until Trim(Sheets(sheetName1).Cells(i, 1).Value) = ""
        
        
        '不要な列の削除
        Sheets(sheetName2).Columns("B:K").Delete
        '***************************************************************
        '以上社外用
        
        '日付の表示形式
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
    'データをクリアする列数を求める
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    CSVPath = ActiveWorkbook.Path
    'CSVName = "社内.csv"
    'write csv file
    nFileNum = FreeFile
    
    '「社内.csv」に保管
    i = 0
    k = 0
    Open CSVPath & "\" & CSVName For Output As #nFileNum
    'ファイルに文字列を書き込みます。
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
                'csvにデータを書き込みます
                GetControl = 0
            Case 1
                'csvからデータを読込みます
                GetControl = 1
            Case 2
                'SyagaiKojin
                GetControl = 2
            Case 3
                '工数登録処理
                GetControl = 3
            Case 4
                'シートを表示します
                GetControl = 4
            Case Else ' その他の値の場合。
                'シートを表示します
                GetControl = 4
        End Select
    Else
        'MsgBox ControlName
        'シートを表示します
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
    'SheetName = "社内"
    CSVPath = ActiveWorkbook.Path
    'CSVName = "社内.csv"
    
    Sheets(sheetName).Select


    'don't update screen during this operation
    '画面を更新させないようにする
    Application.ScreenUpdating = False

    'L:\OA-N821艤装\日報\社内.csv
    'CSVName2 = "L:\OA-N821艤装\日報\社内.csv"
    'ActiveWorkbook.Path
    'CSVName2 = ActiveWorkbook.Path & "\社内.csv"
    'MsgBox CSVName2
    ' record count
    Tflag = True
    RecCnt = 1
    
    'データをクリアする行数を求める
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
    'データをクリアする列数を求める
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    ' delete all cell
    '選択範囲から数式と文字をクリアします。
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
    '画面を更新させる
    Application.ScreenUpdating = True
    Windows(fileName).Activate
    Range("A1").Select
    
'    '日付の表示形式
    For i = 12 To 42
      Range("A1").Offset(0, i - 1).NumberFormatLocal = "m/d"
    Next i

    Sheets(sheetName).Columns.AutoFit

    Range("A1").Select
    'MsgBox ("完了")
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
    'SheetName = "社内"
    CSVPath = ActiveWorkbook.Path
    'CSVName = "社内.csv"
    
    Sheets(sheetName).Select

    'don't update screen during this operation
    '画面を更新させないようにする
    Application.ScreenUpdating = False
    
    ' record count
    Tflag = True
    RecCnt = 1
    
    'データをクリアする行数を求める
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
    'データをクリアする列数を求める
    Do While (Tflag)
        If Range("A1").Offset(0, DataCnt).Value = "" Then
            Tflag = False
        Else
            DataCnt = DataCnt + 1
        End If
    Loop
    DataCnt = DataCnt
    
    ' delete all cell
    '選択範囲から数式と文字をクリアする。
    Range(Cells(1, 1), Cells(RecCnt, DataCnt)).Select
    Selection.ClearContents
    
    
    'MsgBox CSVPath & "\" & CSVName
    'csvファイル「社内.csv」を 開く
    'Workbooks.OpenText FileName:=CSVPath & "\" & CSVName, StartRow:=1, _
        DataType:=xlDelimited, TextQualifier:=xlNone, ConsecutiveDelimiter:=False _
        , Tab:=False, Semicolon:=False, Comma:=True, Space:=False, Other:= _
        False, FieldInfo:=Array(Array(1, 2), Array(2, 2), Array(3, 2), Array(4, 2), Array(5, 2), _
                Array(6, 2), Array(7, 2), Array(8, 2), Array(9, 2), Array(10, 2), Array(11, 2))
    Windows(CSVName).Activate
    Cells.Select
    Selection.Copy
    
    'Excelファイル「data.xls」をアクティブにする
    Windows(fileName).Activate
    Range("A1").Select
    
    '値だけ貼り付ける
    Selection.PasteSpecial Paste:=xlValues, Operation:=xlNone, SkipBlanks:= _
        False, Transpose:=False
    Range("A1").Select
    
    'csvファイル「社内.csv」をアクティブにする
    Windows(CSVName).Activate
    Range("A1").Select
    
    'コピー モードを解除する
    Application.CutCopyMode = False
    
    'マクロの実行中に特定の警告やメッセージを表示しないようにする
    Application.DisplayAlerts = False
    
     'csvファイル「社内.csv」を閉じる
    ActiveWindow.Close
    
    'マクロの実行中に特定の警告やメッセージを表示するようにする
    Application.DisplayAlerts = True
    
    Windows(fileName).Activate
    Range("A1").Select
'    '日付の表示形式
    For i = 12 To 42
      Range("A1").Offset(0, i - 1).NumberFormatLocal = "m/d"
    Next i

    Sheets(sheetName).Columns.AutoFit

    'MsgBox ("完了")
    
End Function


