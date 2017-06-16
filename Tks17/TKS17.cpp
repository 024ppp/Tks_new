//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Tks17.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFILE("Main.h");
USEUNIT("U_TKS17_Data.cpp");
USEUNIT("SharedMemory.cpp");
USEUNIT("U_TKS17_Disp.cpp");
USEFORM("Unit4.cpp", Form4);
USEUNIT("DrawGraph.cpp");
//---------------------------------------------------------------------------
#include "Main.h"
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS17");
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
         str = Arg;
                 Form1->ExtractCode( str) ;
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
