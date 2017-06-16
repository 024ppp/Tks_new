/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : Unit6.cpp                                           *
*  create        : 2002.12.07                                          *
*  update        :                                                     *
*  contents      : 印刷プログラム                                      *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//1ページの行数
#define MAXREC 45

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
int flag = 0;
int QRrec = 0;
int NowPage = 1;
int PageFlag = 0;
AnsiString a;
AnsiString b;
int i,j;
int n,m;
int test = 0;
int DTKSPageNo = 1;
TFontStyles theStyle;

//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    QRrec++;
    //test = 0;
    if ( flag == 0 ) {
        flag = 1;
        QRrec = 1;
        QRBand3->Height = 14;
        //QRDBText2->Top = 0;
        QRDBText7->Top = 0;
        a = Form1->Query3->FieldValues["DTKSCOD"];
        i = Form1->Query3->FieldValues["PASS"];
        n = Form1->Query3->FieldValues["CODE"];
        m = n;
        QRLabel37->Enabled = true;
        QRLabel38->Enabled = true;
        QRLabel3->Enabled = true;
    }
    else {

        b = Form1->Query3->FieldValues["DTKSCOD"];
        j = Form1->Query3->FieldValues["PASS"];
        m = Form1->Query3->FieldValues["CODE"];

        //得意先が違うとき 改ページする
        //合格 不合格
        if ( a != b ) {
            QRLabel37->Enabled = true;
            QRLabel38->Enabled = true;
            QRLabel3->Enabled = true;
        }
        else {
            QRLabel37->Enabled = false;
            QRLabel38->Enabled = false;
            QRLabel3->Enabled = false;
        }



        if (( a != b ) || ( i != j )) {
            QRLabel42->Caption = "END";
            QuickRep1->NewColumn();
            //test = 1;
            NowPage = QuickRep1->PageNumber;
            QRrec = 1;
            DTKSPageNo = 1;
            QRLabel42->Caption = "  ";
        }
        else {
            QRLabel42->Caption = "  ";
            if ( m == 1 ) {
                QRBand2->Height = 24;
                //QRDBText2->Top = 16;
                QRDBText7->Top = 12;
                QRLabel39->Top = 12;
                QRrec++;
            }
            else {
                QRBand2->Height = 12;
                //QRDBText2->Top = 0;
                QRLabel39->Top = 0;
                QRDBText7->Top = 0;
            }
        }

        a = b;
        i = j;
        n = m;
    }

    if ( m == 1 ) {
        if (( QRrec + 4 ) > MAXREC ) {
            QuickRep1->NewColumn();
            DTKSPageNo++;
            //test = 2;
            QRBand2->Height = 12;
            QRDBText7->Top = 0;
            QRLabel39->Top = 0;
            NowPage = QuickRep1->PageNumber;
            QRrec = 1;
        }
        if ( QuickRep1->PageNumber > NowPage ) {
            DTKSPageNo += QuickRep1->PageNumber - NowPage;
            NowPage = QuickRep1->PageNumber;
            DTKSPageNo++;
            QRrec = 1;
            //PageFlag = 1;
        }

    }
    if ( m > 1 && QRrec >= MAXREC) PageFlag = 1;

    if ( QRrec > MAXREC ) {
        //test = 3;
        QuickRep1->NewColumn();
        DTKSPageNo++;
    }
    if ( QuickRep1->PageNumber > NowPage ) {
        NowPage = QuickRep1->PageNumber;
        QRrec = 1;
        PageFlag = 1;
    }

    //フォントの指定
    //得意先品番の行 m=1    太字
    //規格の行       m=2,3  斜体
    //測定値 指定なしm=4～
    theStyle.Clear();
    if ( m == 1 || m == 0 ) {
        QRDBText7->Font->Size = 8;
        theStyle << fsBold;
        QRDBText7->Font->Style = theStyle;
    }
    else {
        if ( m == Form1->Query3->FieldValues["SOKUTEI_NM"] + 2 ) {
            QRDBText7->Font->Size = 7;
            QRDBText7->Font->Style = theStyle;
        }
        else {
            QRDBText7->Font->Size = 8;
            QRDBText7->Font->Style = theStyle;
        }
    }


}
//---------------------------------------------------------------------------
void __fastcall TForm6::QRDBText6Print(TObject *sender, AnsiString &Value)
{
    if ( Value == "1" ) Value = "合格";
    else Value = "不合格";

}
//---------------------------------------------------------------------------
void __fastcall TForm6::QRLabel35Print(TObject *sender, AnsiString &Value)
{
    if ( PageFlag == 1 )
    {
        Value = "*";
        PageFlag = 0;
    }
    else Value = " ";
    //switch ( test ){
    //    case 1:
    //        Value = "1";
    //        break;
    //    case 2:
    //        Value = "2";
    //        break;
    //    case 3:
    //        Value = "3";
    //        break;
    // }
}
//---------------------------------------------------------------------------
//得意先品番
void __fastcall TForm6::QRDBText3Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->Edt_DTKSHIN->Text;
}
//---------------------------------------------------------------------------

//開始ロットNo
void __fastcall TForm6::QRDBText1Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->Edt_StartLOT->Text;
}
//---------------------------------------------------------------------------

//終了ロットNo
void __fastcall TForm6::QRDBText2Print(TObject *sender, AnsiString &Value)
{
    Value = Form1->Edt_EndLOT->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm6::QRBand1BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
//        if ( QuickRep1->PageNumber == 1 ){
//            QRLabel3->Enabled = true;
//        }
//        else {
//            QRLabel3->Enabled = false;
//        }

}
//---------------------------------------------------------------------------

void __fastcall TForm6::QRLabel39Print(TObject *sender, AnsiString &Value)
{
    static int p = 0;

    if ( m == 1 || p == 0)
    {
        Value = "〕";
        p = 1;
    }
    else Value = "";

}
//---------------------------------------------------------------------------

void __fastcall TForm6::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    flag = 0;
    QRrec = 0;
    NowPage = 1;
    PageFlag = 0;
    
}
//---------------------------------------------------------------------------

void __fastcall TForm6::QRLabel41Print(TObject *sender, AnsiString &Value)
{

     Value = "page " + IntToStr(DTKSPageNo);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::QRLabel42Print(TObject *sender, AnsiString &Value)
{
     if ( Form1->Query3->Eof == true ) {
        Value = "END";
     }

}
//---------------------------------------------------------------------------

