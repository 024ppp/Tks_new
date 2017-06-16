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
// 焼成コード
void __fastcall TForm2::QRLbl1Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[1][iPrtRow];
}

//---------------------------------------------------------------------------
// 炉No
void __fastcall TForm2::QRLbl2Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[2][iPrtRow];

}

//---------------------------------------------------------------------------
// 最高温度
void __fastcall TForm2::QRLbl3Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[3][iPrtRow];

}

//---------------------------------------------------------------------------
// サイクル温度
void __fastcall TForm2::QRLbl4Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[4][iPrtRow];

}

//---------------------------------------------------------------------------
// メモ
void __fastcall TForm2::QRLbl5Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->SGr1->Cells[5][iPrtRow];

}

//---------------------------------------------------------------------------
// 更新日
void __fastcall TForm2::QRLbl6Print(TObject *sender, AnsiString &Value)
{

    Value = Form1->SGr1->Cells[7][iPrtRow];
    Value = Value.Insert("/",5);
    Value = Value.Insert("/",8);

    //iPrtRow += 1;

//    Value = FormatDateTime("yyyy/mm/dd",StrToDate(Form1->SGr1->Cells[7][iPrtRow]));

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
    QRLabel10->Enabled = false;
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
        QRLabel10->Enabled = true;
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

