//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"
#pragma hdrstop

USERES("Tks16.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFILE("Tks16.h");
USEUNIT("TKS16_Data.cpp");
USEUNIT("DrawGraph.cpp");
//---------------------------------------------------------------------------
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS16");
        if( GetLastError() ){
                // �쐬���s
                ShowMessage("���̃v���O�����͊��ɋN������Ă��܂��B");
                exit(-1);
        }

        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TForm3), &Form3);
                 str = Arg;
                 Form1->ExtractCode();
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }

        // �Ō�� return 0 �̑O�ɒǉ�
        ReleaseMutex(mx);

        return 0;
}
//---------------------------------------------------------------------------
