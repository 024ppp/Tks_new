//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "unit1.h"
#include "unit3.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm5 *Form5;
extern KDB1_DATA Cur_Kdb1;             // 選択したヒストグラムデータ

extern KDB2_DATA M_Kdb2[1000];         // 計測データ（最大値：１０００個）

extern int USER_COD;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
 int button, i;

 if (Cur_Kdb1.KENSA_KMK == 7) {
    for (i = 0; i < Nums; i++)
        M_Kdb2[i].SOKUTEI_MEI7 = Edt_Number->Value;
 } else {
   for (i = 0; i < Nums; i++)
        M_Kdb2[i].SOKUTEI_MEI4 = Edt_Number->Value;
 }

 Form3->ScreenInitFlag = 1;
 Form3->FormScreenInit(1);

 Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormScreenInit()
{
     Edt_Number->Text = 0;

     if (Cur_Kdb1.KENSA_KMK == 7) {
        Form5->Caption = "プローブ変更";
        Panel1->Caption = "現在プローブ";
        Panel3->Caption = "新プローブ";
        Panel2->Caption = M_Kdb2[0].SOKUTEI_MEI7;
     } else {
        Form5->Caption = "スパン変更";
        Panel1->Caption = "現在スパン";
        Panel3->Caption = "新スパン";
        Panel2->Caption = M_Kdb2[0].SOKUTEI_MEI4;
     }
}
void __fastcall TForm5::FormActivate(TObject *Sender)
{
     Edt_Number->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm5::Edt_NumberKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_RETURN:
              Button1->SetFocus();
              break;
      }
}
//---------------------------------------------------------------------------
