//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"


#pragma hdrstop
USERES("TKS21.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFILE("TKS21.h");
USEUNIT("Unit3.cpp");
USEUNIT("Unit4.cpp");

//---------------------------------------------------------------------------
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS21");
        if( GetLastError() ){
                // 作成失敗
                ShowMessage("このプログラムは既に起動されています。");
                return -1;
//                exit(-1);
        }

        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
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

