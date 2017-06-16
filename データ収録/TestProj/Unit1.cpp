//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TEdit *MyEdit;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
     for (int i = 0; i < Nums; i++) {
         Edits[i] = new TEdit(Form1);
         Edits[i]->Text = i+1;
         Edits[i]->Parent = Form1;
         Edits[i]->Width = 65;
         Edits[i]->Height = 17;
         Edits[i]->Left = 17;
         Edits[i]->Top = i* 20;
     }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
     for (int i = 0; i < Nums; i++)
         Edits[i]->Free();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Enter(TObject *Sender)
{
     Edit1->Text = "ABC";
}
//---------------------------------------------------------------------------



