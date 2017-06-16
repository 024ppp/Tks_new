//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "unit1.h"
#include "unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm4 *Form4;
const int Nums = 500;

extern KDA1_DATA Cur_Kda1;             // 選択したヒストグラムデータ

extern KDA2_DATA M_Kda2[1000];         // 計測データ（最大値：１０００個）

extern int USER_COD;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormActivate(TObject *Sender)
{
     Edt_Number->SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TForm4::FormScreenInit()
{
     Edt_Number->Text = 0;
     Panel2->Caption = Cur_Kda1.HIST_SOKUT;
}

void __fastcall TForm4::Button1Click(TObject *Sender)
{
 int button, i;

 if (Edt_Number->Value > Nums)
    Edt_Number->Value = Nums;

 if (Edt_Number->Value < Cur_Kda1.HIST_SOKUT) {
    button = MessageDlg(MSG_12.c_str(), mtConfirmation, mbOKCancel, 0);
    if (button == mrCancel){
       return;
    }
 }

 Cur_Kda1.HIST_SOKUT = Edt_Number->Value;

 if (Cur_Kda1.SOKUTE_SU > Cur_Kda1.HIST_SOKUT) {
    for (i = Cur_Kda1.HIST_SOKUT; i < Cur_Kda1.SOKUTE_SU; i++)
        M_Kda2[i].SOKUTEI_CH = 0;
    Cur_Kda1.SOKUTE_SU = Cur_Kda1.HIST_SOKUT;
 }

 Form3->FormScreenInit(1);

 if (Edt_Number->Value > 0)
    Form3->Edt_001->SetFocus();

 Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Edt_NumberKeyDown(TObject *Sender, WORD &Key,
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

