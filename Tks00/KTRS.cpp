//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

USERES("KTRS.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        mx = CreateMutex(NULL,true,"ID_KTRS");
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
