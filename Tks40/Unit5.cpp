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
extern KDB1_DATA Cur_Kdb1;             // �I�������q�X�g�O�����f�[�^

extern KDB2_DATA M_Kdb2[1000];         // �v���f�[�^�i�ő�l�F�P�O�O�O�j

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
        Form5->Caption = "�v���[�u�ύX";
        Panel1->Caption = "���݃v���[�u";
        Panel3->Caption = "�V�v���[�u";
        Panel2->Caption = M_Kdb2[0].SOKUTEI_MEI7;
     } else {
        Form5->Caption = "�X�p���ύX";
        Panel1->Caption = "���݃X�p��";
        Panel3->Caption = "�V�X�p��";
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
