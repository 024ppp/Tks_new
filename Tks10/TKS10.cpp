//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Tks10.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFILE("Main.h");
USEUNIT("U_TKS10_Data.cpp");
USEUNIT("SharedMemory.cpp");
USEUNIT("DrawGraph.cpp");
USEUNIT("U_TKS10_Disp.cpp");

#include "Main.h"
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS10");
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
                 Form1->ExtractCode( str) ;
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
