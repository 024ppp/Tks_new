//---------------------------------------------------------------------------

#include <vcl.h>
#include "Unit1.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit5.cpp", Form5);
USEFORM("Unit6.cpp", Form6);
USEFORM("Unit11.cpp", Form11);
//---------------------------------------------------------------------------
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
    mx = CreateMutex(NULL,true,"ID_TKS40");
    if( GetLastError() ){
        // 作成失敗
        ShowMessage("このプログラムは既に起動されています。");
        return -1;
//      exit(-1);
    }
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm3), &Form3);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TForm5), &Form5);
         Application->CreateForm(__classid(TForm6), &Form6);
         Application->CreateForm(__classid(TForm11), &Form11);
         Application->CreateForm(__classid(TForm6), &Form6);
         Application->CreateForm(__classid(TForm11), &Form11);
         str = Arg;
		Form1->ExtractCode(str);
		Application->Run();
    }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }

        // 最後の return 0 の前に追加
        ReleaseMutex(mx);
        return 0;
}
//---------------------------------------------------------------------------
