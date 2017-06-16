//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
// ÞŽ¿ƒR[ƒh
void __fastcall TForm2::QRLbl1Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[1][iPrtRow];
}

//---------------------------------------------------------------------------
// ÞŽ¿–¼Ì
void __fastcall TForm2::QRLbl2Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[2][iPrtRow];
}

//---------------------------------------------------------------------------
// XV“ú
void __fastcall TForm2::QRLbl3Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[19][iPrtRow];
    Value = Value.Insert("/",5);
    Value = Value.Insert("/",8);
}


//---------------------------------------------------------------------------
// •ê‘Ì”äd
void __fastcall TForm2::QRLbl4Print(TObject *sender, AnsiString &Value)
{
    sBuf1 = Form1->SGr1->Cells[3][iPrtRow];
    sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length()) + sBuf1;

    sBuf2 = Form1->SGr1->Cells[4][iPrtRow];
    sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------
// ŒÅ—L’ïR—¦
void __fastcall TForm2::QRLbl5Print(TObject *sender, AnsiString &Value)
{
    sBuf1 = Form1->SGr1->Cells[5][iPrtRow];
    sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length()) + sBuf1;

    sBuf2 = Form1->SGr1->Cells[6][iPrtRow];
    sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------
// ‹È‚°‹­“x
void __fastcall TForm2::QRLbl6Print(TObject *sender, AnsiString &Value)
{
    sBuf1 = Form1->SGr1->Cells[7][iPrtRow];
    sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length()) + sBuf1;

    sBuf2 = Form1->SGr1->Cells[8][iPrtRow];
    sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
    // ’PˆÊ•t‚«
    // Value = sBuf1 + "`" + sBuf2 + Form1->SGr1->Cells[9][iPrtRow];
}

//---------------------------------------------------------------------------
// d“xHsC@ˆ³–Ê
void __fastcall TForm2::QRLbl7Print(TObject *sender, AnsiString &Value)
{
    if( Form1->SGr1->Cells[10][iPrtRow] == "" ){
        sBuf1 = "0";
    }
    else{
        sBuf1 = StrToInt(Form1->SGr1->Cells[10][iPrtRow]);
    }
    sBuf1 = AnsiString::StringOfChar(' ', 2 - sBuf1.Length()) + sBuf1;

    if( Form1->SGr1->Cells[11][iPrtRow] == "" ){
        sBuf2 = "0";
    }
    else{
        sBuf2 = StrToInt(Form1->SGr1->Cells[11][iPrtRow]);
    }
    sBuf2 = AnsiString::StringOfChar(' ', 2 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------
// d“xHsC@‘¤–Ê
void __fastcall TForm2::QRLbl8Print(TObject *sender, AnsiString &Value)
{
    if( Form1->SGr1->Cells[12][iPrtRow] == "" ){
        sBuf1 = "0";
    }
    else{
        sBuf1 = StrToInt(Form1->SGr1->Cells[12][iPrtRow]);
    }
    sBuf1 = AnsiString::StringOfChar(' ', 2 - sBuf1.Length()) + sBuf1;

    if( Form1->SGr1->Cells[13][iPrtRow] == "" ){
        sBuf2 = "0";
    }
    else{
        sBuf2 = StrToInt(Form1->SGr1->Cells[13][iPrtRow]);
    }
    sBuf2 = AnsiString::StringOfChar(' ', 2 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------
// d“xHsD@ˆ³–Ê
void __fastcall TForm2::QRLbl9Print(TObject *sender, AnsiString &Value)
{
    sBuf1 = Form1->SGr1->Cells[14][iPrtRow];
    sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length()) + sBuf1;

    sBuf2 = Form1->SGr1->Cells[15][iPrtRow];
    sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------
// d“xHsD@‘¤–Ê
void __fastcall TForm2::QRLbl10Print(TObject *sender, AnsiString &Value)
{
    sBuf1 = Form1->SGr1->Cells[16][iPrtRow];
    sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length()) + sBuf1;

    sBuf2 = Form1->SGr1->Cells[17][iPrtRow];
    sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length()) + sBuf2;

    Value = sBuf1 + "`" + sBuf2;
}

//---------------------------------------------------------------------------

void __fastcall TForm2::QRBand3AfterPrint(TQRCustomBand *Sender,
      bool BandPrinted)
{
    iPrtRow += 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    iPrtRow = 0;
    QRLabel19->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::QRLabel9Print(TObject *sender, AnsiString &Value)
{
    Value = IntToStr(QuickRep1->PageNumber);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    MoreData = iPrtRow < (Form1->SGr1->RowCount - 1);
    if( !MoreData ){
        QRLabel19->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::QRBand1BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    if(QuickRep1->PageNumber == 1)  QRLabel1->Enabled = true;
    else                            QRLabel1->Enabled = false;
}
//---------------------------------------------------------------------------


