'広陽
'iniファイル編集
set fso = createobject("scripting.filesystemobject")
ForReading = 1
ForWriteing = 2
'iniファイルパス
sFilePath = "C:\Tks_New\Tks.ini"
'変更文字列
sBefore = "KOJOKBN = 1"
sAfter = "KOJOKBN = 0"

Set f = fso.OpenTextFile(sFilePath, ForReading)
ReadAllTextFile = f.ReadAll
f.close
f3 = split(ReadAllTextFile,chr(13) & chr(10))
for i = 0 to ubound(f3)
	if trim(f3(i)) = sBefore then
		f3(i) = sAfter
	end if
next
Set f1 = fso.OpenTextFile(sFilePath, ForWriteing , true)
MyString = Join(f3 , chr(13) & chr(10) )
f1.write MyString
f1.close

'素材検査プログラム実行
Dim objWShell
Set objWShell = CreateObject("WScript.Shell")
'KTRS.exeを直接指定すると、工場区分に関わらず本社で起動されてしまう→引数必要？
'sExePath = "C:\Tks_New\KTRS.exe"
sExePath = "C:\素材検査"
objWShell.Run sExePath
Set objWShell = Nothing