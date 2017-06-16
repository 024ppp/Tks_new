//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

USERES("TKS51.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEUNIT("Unit4.cpp");
//---------------------------------------------------------------------------
AnsiString  sArgALL;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS51");
        if( GetLastError() ){
                // 作成失敗
                ShowMessage("このプログラムは既に起動されています。");
                exit(-1);
        }

        try
        {
                 Application->Initialize();
                 Application->Title = "製品規格マスターメンテ";
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         Application->CreateForm(__classid(TForm3), &Form3);
         sArgALL = Arg;
                 Form1->ExtractCode(sArgALL);
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
