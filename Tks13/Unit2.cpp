/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�R�j                  *
*  file   name   : Unit2.cpp                                           *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ذ�ސ���t��R����u�ꗗ�����v�\����ʏ���          *
*  written by    : �� ���N �iNKK unics Corp.)                          *
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
     // �O���b�h�̏�����
     SGr1->ColWidths[0]  = 40;
     SGr1->ColWidths[1]  = 90 ;
     SGr1->ColWidths[2]  = 40;

     if( iRec_Kd31){
        // �J�\�[�����ŏ����R�[�h�֐ݒ�
        SGr1->Row = 1;
        SGr1->SetFocus();

       // �ŏ����R�[�h���ް���ϐ��֕ۑ�
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
// �u�e�Q�F�O���v
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
    }
}
//---------------------------------------------------------------------------
// �u�e�R�F�����v
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-2) > SGr1->Row ){
        SGr1->Row += 1;
    }
}
//---------------------------------------------------------------------------
// �u�e�R�F�I���v
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{

     Form1->edtymd->Text = InsSEPA(sYMD) ;
     Form1->edttlno->Text = sTL ;

     // �J�\�[�����u�ڰNO�v��
     Form1->edttlno->SetFocus();
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     // �J�\�[�����u�ڰNO�v��
     Form1->edttlno->SetFocus();
     Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   //���ă��R�[�h���ް���ϐ��֕ۑ�
   sYMD = SGr1->Cells[1][ARow] ;
   sTL = SGr1->Cells[2][ARow] ;
}
//---------------------------------------------------------------------------




