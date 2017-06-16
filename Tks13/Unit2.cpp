/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１３）                  *
*  file   name   : Unit2.cpp                                           *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾘｰﾄﾞ線取付抵抗測定「一覧検索」表示画面処理          *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
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

     if( iRec_Kd31){
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

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
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
// 「Ｆ２：前項」
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
    }
}
//---------------------------------------------------------------------------
// 「Ｆ３：次項」
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-2) > SGr1->Row ){
        SGr1->Row += 1;
    }
}
//---------------------------------------------------------------------------
// 「Ｆ３：選択」
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{

     Form1->edtymd->Text = InsSEPA(sYMD) ;
     Form1->edttlno->Text = sTL ;

     // カソールを「ﾄﾚｰNO」へ
     Form1->edttlno->SetFocus();
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



void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   //ｶﾚﾝﾄレコードのﾃﾞｰﾀを変数へ保存
   sYMD = SGr1->Cells[1][ARow] ;
   sTL = SGr1->Cells[2][ARow] ;
}
//---------------------------------------------------------------------------




