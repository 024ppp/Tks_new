//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

USERES("TKS52.res");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
//---------------------------------------------------------------------------
AnsiString  sArgALL;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
        mx = CreateMutex(NULL,true,"ID_TKS52");
        if( GetLastError() ){
                // �쐬���s
                ShowMessage("���̃v���O�����͊��ɋN������Ă��܂��B");
                exit(-1);
        }

        try
        {
                 Application->Initialize();
                 Application->Title = "�ގ��K�i�}�X�^�����e";
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(TForm2), &Form2);
         sArgALL = Arg;
                 Form1->ExtractCode(sArgALL);
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
