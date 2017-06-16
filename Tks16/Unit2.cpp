//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Tks16.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

AnsiString sYMD;
AnsiString sTL;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{
     // グリッドの初期化
     SGr1->ColWidths[0]  = 40;
     SGr1->ColWidths[1]  = 90 ;
     SGr1->ColWidths[2]  = 40;

     if( iRec_Kd61){
        // カソールを最初レコードへ設定
        SGr1->Row = 1;
        SGr1->SetFocus();

       // 最初レコードのﾃﾞｰﾀを変数へ保存
       sYMD = SGr1->Cells[1][1] ;
       sTL = SGr1->Cells[2][1] ;
      }else{
         BtnF02->Enabled = false;
         BtnF03->Enabled = false;
         BtnF04->Enabled = false;
      }

}
//---------------------------------------------------------------------------
void __fastcall TForm2::SGr1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:    BtnF02Click(Sender);    break;
         case VK_F3:    BtnF03Click(Sender);    break;
         case VK_F4:    BtnF04Click(Sender);    break;
         case VK_F12:   BtnF12Click(Sender);    break;
         case VK_RETURN:BtnF04Click(Sender);    break;

     }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   //ｶﾚﾝﾄレコードのﾃﾞｰﾀを変数へ保存
   sYMD = SGr1->Cells[1][ARow] ;
   sTL = SGr1->Cells[2][ARow] ;        
}
//---------------------------------------------------------------------------
// 一覧検索の前項
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
    }
}
//---------------------------------------------------------------------------
//一覧検索の次項
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-2) > SGr1->Row ){
        SGr1->Row += 1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
 AnsiString TString;

     TString = sYMD;
     TString.Insert("/",5);
     TString.Insert("/",8);
     Form1->edtymd->Text = TString;
     Form1->edttlno->Text = sTL ;

     // カソールを「ﾄﾚｰNO」へ
     Form1->edttlno->SetFocus();
     Hsc_SamplePositionIdx = -1 ;
     Hsd_SamplePositionIdx = -1;
     
     Close();        
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     // カソールを「ﾄﾚｰNO」へ
     Form1->edttlno->SetFocus();
     Close();        
}
//---------------------------------------------------------------------------
