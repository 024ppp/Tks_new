'�L�z
'ini�t�@�C���ҏW
set fso = createobject("scripting.filesystemobject")
ForReading = 1
ForWriteing = 2
'ini�t�@�C���p�X
sFilePath = "C:\Tks_New\Tks.ini"
'�ύX������
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

'�f�ތ����v���O�������s
Dim objWShell
Set objWShell = CreateObject("WScript.Shell")
'KTRS.exe�𒼐ڎw�肷��ƁA�H��敪�Ɋւ�炸�{�ЂŋN������Ă��܂��������K�v�H
'sExePath = "C:\Tks_New\KTRS.exe"
sExePath = "C:\�f�ތ���"
objWShell.Run sExePath
Set objWShell = Nothing