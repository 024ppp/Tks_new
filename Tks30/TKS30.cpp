//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("TKS30.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFILE("TKS30.h");
USEFORM("Unit4.cpp", Form4);
USEUNIT("SharedMemory.cpp");
USEUNIT("U_Excel.cpp");
USEFORM("Unit5.cpp", Form5);

AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS30");
        if( GetLastError() ){
                // 作成失敗
                ShowMessage("このプログラムは既に起動されています。");
                exit(-1);
        }

        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm3), &Form3);
         Application->CreateForm(__classid(TForm4), &Form4);
         Application->CreateForm(__classid(TForm5), &Form5);
         str = Arg;
         Form1->ExtractCode(str);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }

        // 最後の return 0 の前に追加
        ReleaseMutex(mx);

        return 0;
}
//---------------------------------------------------------------------------
