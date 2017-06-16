//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm4 *Form4;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
    Form4->Tag = 1;
    if( EdtNum->Value >= 1 && EdtNum->Value <= 44 ){
        Form3->iPrtStart = EdtNum->Value - 1;
    }
    else{
        Form3->iPrtStart = 0;
    }
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm4::Button2Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm4::FormActivate(TObject *Sender)
{
    Form4->Tag = 0;
    EdtNum->SelectAll();
    EdtNum->SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall TForm4::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

    switch(Key) {
        // Enter
        case VK_RETURN:
             Button1Click(Sender);
             break;
    }

}

//---------------------------------------------------------------------------
void __fastcall TForm4::EdtNumKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    Form1->AllKeyUp( Sender, Key, Shift);
}

//---------------------------------------------------------------------------

