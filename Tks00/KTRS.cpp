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
                // �쐬���s
                ShowMessage("���̃v���O�����͊��ɋN������Ă��܂��B");
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

        // �Ō�� return 0 �̑O�ɒǉ�
        ReleaseMutex(mx);

        return 0;
}
//---------------------------------------------------------------------------
