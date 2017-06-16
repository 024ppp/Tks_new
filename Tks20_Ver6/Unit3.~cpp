/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : Unit3.cpp                                           *
*  create        : 1999.10.12                                          *
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
TForm3 *Form3;
int flag = 0;
int QRrec = 0;
int NowPage = 1;
int PageFlag = 0;
AnsiString a;
AnsiString b;
int i,j;
int n,m;
int A1 = 1;
int A2 = 0;

AnsiString sBufDTKSCOD;

int EndFlag = 0;
int DTKSPageNo = 1;
TFontStyles theStyle;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm3::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{

    QRrec++;
    if ( flag == 0 ) {
    //if ( Form1->Query2->RecNo <= 1 ) {
        flag = 1;
        //QRBand2->Height = 18;
        QRBand2->Height = 12;
        //QRDBText2->Top = 0;
        QRDBText7->Top = 0;
        a = Form1->Query2->FieldValues["DTKSCOD"];
        i = Form1->Query2->FieldValues["PASS"];
        n = Form1->Query2->FieldValues["CODE"];
        m = n;

        QRLabel37->Enabled = true;
        QRLabel38->Enabled = true;
        QRLabel3->Enabled = true;

    }
    else {
        //Form1->Query2->MoveBy(-1);
        //Form1->Query2->Next();
        b = Form1->Query2->FieldValues["DTKSCOD"];
        j = Form1->Query2->FieldValues["PASS"];
        m = Form1->Query2->FieldValues["CODE"];

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
            NowPage = QuickRep1->PageNumber;
            DTKSPageNo = 1;
            //QRrec = 0;
            QRrec = 1;
            EndFlag = 1;
            QRLabel42->Caption = "  ";
       }
        else {
            QRLabel42->Caption = "  ";
            if ( m == 1 ) {
                QRBand2->Height = 24;
                QRDBText7->Top = 12;
                QRLabel39->Top = 12;
                QRrec++;
            }
            else {
                //QRBand2->Height = 18;
                QRBand2->Height = 12;
                //QRDBText2->Top = 0;
                QRDBText7->Top = 0;
                QRLabel39->Top = 0;
            }
        }

        a = b;
        i = j;
        n = m;
    }
    //if ( QRrec > 0 && ( QRrec % MAXREC ) == 0 ) {
    //    PageFlag =1;
    //}

    if ( m == 1 ) {
        if ((QRrec + 4 ) > MAXREC ) {
            if ( PageFlag == 1 ) PageFlag = 0;
            QuickRep1->NewColumn();
            DTKSPageNo++;
            QRBand2->Height = 12;
            QRDBText7->Top = 0;
            QRLabel39->Top = 0;
            NowPage = QuickRep1->PageNumber;
            //QRrec = 0;
            QRrec = 1;
        }
        else {
            if( PageFlag == 1 ) {
                PageFlag = 0;
            }
        }
        if ( Form1->Query2->FieldValues["SOKUTEI_NM"] > 2 ) {
            A1 =  QuickRep1->PageNumber;
        }

    }
    //if ( QRrec == MAXREC ) PageFlag = 1;
    if ( m >= 4 && QRrec >= MAXREC) PageFlag = 1;
    if ( QRrec > MAXREC ) {
       
        QuickRep1->NewColumn();
        DTKSPageNo++;
    }
    if ( QuickRep1->PageNumber > NowPage ) {
        DTKSPageNo += QuickRep1->PageNumber - NowPage;
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
        //if ( m == 2 || m == 3 ) {
        if ( m == 2  ) {
            QRDBText7->Font->Size =7;
            theStyle << fsItalic;
            QRDBText7->Font->Style = theStyle;
        }
        else {
            QRDBText7->Font->Size = 8;
            QRDBText7->Font->Style = theStyle;
        }
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm3::QRDBText6Print(TObject *sender, AnsiString &Value)
{
    if ( Value == "1" ) Value = "合格";
    else Value = "不合格";

}
//---------------------------------------------------------------------------




void __fastcall TForm3::QRLabel35Print(TObject *sender, AnsiString &Value)
{
    if ( PageFlag == 1 )
    {
        Value = "*";
        PageFlag = 0;
    }
    else Value = " ";

}
//---------------------------------------------------------------------------

void __fastcall TForm3::QRDBText3Print(TObject *sender, AnsiString &Value)
{
    AnsiString str;
    AnsiString Daystr;
    str = Value;
    Daystr = str.SubString(1,4) + "/";
    Daystr += str.SubString(5,2) + "/";
    Daystr += str.SubString(7,2);
    Value = Daystr;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::QRLabel39Print(TObject *sender, AnsiString &Value)
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

void __fastcall TForm3::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    flag = 0;
    QRrec = 0;
    NowPage = 1;
    PageFlag = 0;
    EndFlag = 0;
    DTKSPageNo = 1;

}
//---------------------------------------------------------------------------


void __fastcall TForm3::QRLabel41Print(TObject *sender, AnsiString &Value)
{
     Value = "page " + IntToStr(DTKSPageNo);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::QRLabel42Print(TObject *sender, AnsiString &Value)
{
     if ( Form1->Query2->Eof == true ) {
        Value = "END";
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::QRBand1BeforePrint(TQRCustomBand *Sender,
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
//得意先名
void __fastcall TForm3::QRLabel44Print(TObject *sender, AnsiString &Value)
{
    Value = "   ";
}
//---------------------------------------------------------------------------

void __fastcall TForm3::QRDBText1Print(TObject *sender, AnsiString &Value)
{
    sBufDTKSCOD = Value;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::QRDBText2Print(TObject *sender, AnsiString &Value)
{
    AnsiString SQLstr;

    //検索 検査員
    Form1->Q_TW_UPDCHR->Close();
    Form1->Q_TW_UPDCHR->SQL->Clear();
    //問い合せ文実行
    //ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
    SQLstr = "SELECT ";
    SQLstr += "str  FROM TW_UPDCHR ";
    SQLstr += "WHERE  DTKSCOD = '" + sBufDTKSCOD + "'" ;
    Form1->Q_TW_UPDCHR->SQL->Add(SQLstr);
    Form1->Q_TW_UPDCHR->Open();
    if( Form1->Q_TW_UPDCHR->Bof == true && Form1->Q_TW_UPDCHR->Eof){
    //if( Form1->Q_STRS->RecordCount > 0 ) {
        Value = " ";
    }
    else {
        Form1->Q_TW_UPDCHR->First();
        Value = Form1->Q_TW_UPDCHR->FieldValues["str"];
    }

}
//---------------------------------------------------------------------------

