//---------------------------------------------------------------------------
#include <vcl.h>
#include "Unit1.h"

#pragma hdrstop
USERES("Tks20.res");
USEFORM("Unit4.cpp", Form4);
USEUNIT("U_KD01.cpp");
USEUNIT("U_KD11.cpp");
USEUNIT("U_KD21.cpp");
USEUNIT("U_KD31.cpp");
USEUNIT("U_KD41.cpp");
USEUNIT("U_KD51.cpp");
USEUNIT("U_KD61.cpp");
USEUNIT("U_KD71.cpp");
USEUNIT("U_KD81.cpp");
USEUNIT("U_KM0104.cpp");
USEUNIT("U_MakeData.cpp");
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit5.cpp", Form5);
USEFORM("Unit6.cpp", Form6);
USEUNIT("U_Func.cpp");
USEFILE("Main.h");
USEUNIT("U_KD91.cpp");
USEUNIT("U_UPDCHR.cpp");
USEUNIT("U_KDC1.cpp");
USEUNIT("U_KD71_L.cpp");
USEUNIT("U_KD71_R.cpp");
//---------------------------------------------------------------------------
AnsiString str;

HANDLE mx;

//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR Arg, int)
{
    mx = CreateMutex(NULL,true,"ID_TKS20");
    if( GetLastError() ){
         // 作成失敗
         ShowMessage("このプログラムは既に起動されています。");
//         exit(-1);
         return -1;
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
