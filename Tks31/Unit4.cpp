//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
#define MAXLINE 15

int flag = 0;
int SearchFlag = 1;
int Priflag = 1;
int Passflag = 1;
AnsiString OLD_KENSA_YMD,NOW_KENSA_YMD;
int OLDPageNo;
int MoreFlag = 0;
int Pageline = 1;
int NextPageFlag = 0;
int EndFlag = 0;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//ŒŸ¸“ú
void __fastcall TForm4::QRLabel3Print(TObject *sender, AnsiString &Value)
{
    AnsiString str;
    AnsiString Daystr;
    if ( Priflag == 0 ) {
        Value = " ";
        return;
    }
    str = Form4->Query1->FieldValues["KENSA_YMD"];
    Daystr = str.SubString(1,4) + "/";
    Daystr += str.SubString(5,2) + "/";
    Daystr += str.SubString(7,2);
    Value = Daystr;
}
//---------------------------------------------------------------------------
//ŒŸ¸ˆõ–¼
void __fastcall TForm4::QRLabel4Print(TObject *sender, AnsiString &Value)
{
    if ( Priflag == 0 ) {
        Value = " ";
        return;
    }
    if ( Form4->Query1->FieldValues["TANNAM"].IsNull()  ){
        Value = USER_NAM;
    } else {
        Value = Form4->Query1->FieldValues["TANNAM"];
    }
}
//---------------------------------------------------------------------------
//“¾ˆÓæƒR[ƒh
void __fastcall TForm4::QRLabel5Print(TObject *sender, AnsiString &Value)
{
    Value = Form4->Query1->FieldValues["DTKSCOD"];
}
//---------------------------------------------------------------------------
//“¾ˆÓæ•i”Ô
void __fastcall TForm4::QRLabel7Print(TObject *sender, AnsiString &Value)
{
    Value = Form4->Query1->FieldValues["DTKSHIN"];
}
//---------------------------------------------------------------------------
//ÞŽ¿–¼
void __fastcall TForm4::QRLabel8Print(TObject *sender, AnsiString &Value)
{
    Value = Form4->Query1->FieldValues["ZISNAM"];
}
//---------------------------------------------------------------------------
//ƒƒbƒgNO
void __fastcall TForm4::QRLabel9Print(TObject *sender, AnsiString &Value)
{
    Value = Form4->Query1->FieldValues["LOTNO"];
}
//---------------------------------------------------------------------------
//‰ºŒÀ’l`ãŒÀ’l
void __fastcall TForm4::QRLabel10Print(TObject *sender, AnsiString &Value)
{
    AnsiString sBuf;

    if( Form4->Query1->FieldValues["HIST_KIKAK"] == 1
            || Form4->Query1->FieldValues["HIST_KIKAK"] == 2 ) {
        sBuf = FormatFloat("0.000", StrToFloat(Form4->Query1->FieldValues["HIST_MIN"]));
    } else {
        sBuf = "-";
    }
    Value = AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf + " ` ";

    if( Form4->Query1->FieldValues["HIST_KIKAK"] == 1
            || Form4->Query1->FieldValues["HIST_KIKAK"] == 3 ) {
        sBuf = FormatFloat("0.000", StrToFloat(Form4->Query1->FieldValues["HIST_MAX"]));
    } else {
        sBuf = "-";
    }
    Value = Value + AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf;

}
//---------------------------------------------------------------------------
//‘ª’è” ‚m
void __fastcall TForm4::QRLabel11Print(TObject *sender, AnsiString &Value)
{
    Value =  FormatFloat("0", StrToFloat(Form4->Query1->FieldValues["SOKUTE_SU"]));
}
//---------------------------------------------------------------------------
//•½‹Ï’l Ave
void __fastcall TForm4::QRLabel12Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.AVE_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_Ave"]));
}
//---------------------------------------------------------------------------
//‚l‚‰‚Ž
void __fastcall TForm4::QRLabel13Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.MIN_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_MIN"]));
}
//---------------------------------------------------------------------------
//‚l‚‚˜
void __fastcall TForm4::QRLabel14Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.MAX_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_MAX"]));
}
//---------------------------------------------------------------------------
//•W€•Î· ƒÐ
void __fastcall TForm4::QRLabel15Print(TObject *sender, AnsiString &Value)
{
    KETA.SOKUTE_SGM = StrToFloat(Form4->Query1->FieldValues["SOKUTE_SGM"]);
	KETA.SGM_str = Form1->ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
    Value = FormatFloat(KETA.SGM_str,KETA.SOKUTE_SGM);
}
//---------------------------------------------------------------------------
//‚q ‚l‚`‚w|‚l‚h‚m
void __fastcall TForm4::QRLabel16Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.R_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_R"]));
}
//---------------------------------------------------------------------------
//‚b‚
void __fastcall TForm4::QRLabel17Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.CP_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_CP"]));
}
//---------------------------------------------------------------------------
//‚j
void __fastcall TForm4::QRLabel18Print(TObject *sender, AnsiString &Value)
{
    KETA.SOKUTE_K = StrToFloat(Form4->Query1->FieldValues["SOKUTE_K"]);
	KETA.K_str = Form1->ConvKETA2( KETA.K,KETA.SOKUTE_K ,2 );
    Value = FormatFloat(KETA.K_str, KETA.SOKUTE_K);
}
//---------------------------------------------------------------------------
//‚b‚‚j
void __fastcall TForm4::QRLabel19Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.CPK_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_CpK"]));
}
//---------------------------------------------------------------------------
//•s—Ç—¦ ‚o
void __fastcall TForm4::QRLabel20Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.P_str, StrToFloat(Form4->Query1->FieldValues["SOKUTE_P"]));
}
//---------------------------------------------------------------------------
//ƒy[ƒW”Ô†
void __fastcall TForm4::QRLabel32Print(TObject *sender, AnsiString &Value)
{
    AnsiString sBuf;
    sBuf = "page " + IntToStr(QuickRep1->PageNumber);
    Value = AnsiString::StringOfChar(' ', 15-sBuf.Length()) + sBuf;
}

//---------------------------------------------------------------------------
//ƒŒƒ|[ƒgˆóü‘O
void __fastcall TForm4::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    int n;

    flag = 0;
    iPrtRow = 0;
    iPrtRow2 = 0;
    MoreFlag = 0;
    EndFlag = 0;
    Passflag = 1;
    Pageline = 1;
    NextPageFlag = 0;
    n = Form4->Search(1);
    SearchFlag = 1;
    Form4->Query1->First();
}
//---------------------------------------------------------------------------
//Ú×€–Ú 1s ˆóüŒã
void __fastcall TForm4::QRBand2AfterPrint(TQRCustomBand *Sender,
      bool BandPrinted)
{
    Form4->Query1->Next();
    iPrtRow++;
    //if ( Pageline > MAXLINE ) { NextPageFlag = 1;  Pageline = 1; }
    //else { NextPageFlag = 0;  Pageline++; }
    

}
//---------------------------------------------------------------------------
//MoreData
void __fastcall TForm4::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    AnsiString sBuf;

    if ( MoreFlag == 0 &&  Form4->Query1->Eof ) {
        MoreFlag = 1;
        Pageline = 1;
        Passflag = 0;
        Priflag = 1;

//        // Initial Query
//        Form4->Query1->Close();
//        Form4->Query1->SQL->Clear();
//
//        //–â‚¢‡‚í‚¹•¶ ŽÀs 1.3–¢–ž‚¾‚¯’Šo
//        sBuf = "SELECT *  FROM KDA1 ";
//        sBuf += " WHERE  KENSA_YMD = '" + Form1->EdtYMD->Text + "'";
//        sBuf += " AND SOKUTE_CPK < 1.3 ";
//        sBuf += " ORDER BY DTKSHIN, KENSA_YMD, SEQNO";
//
//        Form4->Query1->SQL->Add(sBuf);
//        Form4->Query1->Open();
//        Form4->Query1->Active = true;
//
//        if ( Form4->Query1->Bof == true && Form4->Query1->Eof == true ) {
        if ( Search(2) == 0 ) {
            MoreData = false;
        } else {
            iPrtRow2 = 1;
            Form4->Query1->First();
            SearchFlag = 2;
            QuickRep1->NewColumn();
            MoreData = true;
        }
    } else {
        MoreData = !(Form4->Query1->Eof);
    }
}
//---------------------------------------------------------------------------
//Ú×€–Ú 1s ˆóü‘O
void __fastcall TForm4::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    if ( flag == 0 ) {
        flag= 1;
        OLD_KENSA_YMD = Form4->Query1->FieldValues["KENSA_YMD"];
        OLDPageNo = QuickRep1->PageNumber;
        Priflag = 1;
        NextPageFlag = 0;  Pageline++;
    } else {
        NextPageFlag = 0;
        NOW_KENSA_YMD = Form4->Query1->FieldValues["KENSA_YMD"];
        if ( Pageline > MAXLINE ) {
            QuickRep1->NewColumn();
            NextPageFlag = 1;
            Pageline = 2;
            Priflag = 1;
        } else {
            //NextPageFlag = 0;  Pageline++;
            Pageline++;
            if ( iPrtRow2 == 1 ) {
                iPrtRow2 = 0;
                Priflag = 1;
            } else {
                if ( OLD_KENSA_YMD == NOW_KENSA_YMD && NextPageFlag == 0 ) Priflag = 0;
                else Priflag = 1;
            }
        }
        OLDPageNo = QuickRep1->PageNumber;
        OLD_KENSA_YMD = NOW_KENSA_YMD;
    }
}
//---------------------------------------------------------------------------
//QRBand1 ˆóü‘O
void __fastcall TForm4::QRBand1BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    if(QuickRep1->PageNumber == 1) {
        QRLabel1->Enabled = true;
        QRLabel33->Enabled = true;
        QRLabel34->Enabled = true;

    } else {
        QRLabel1->Enabled = false;
        QRLabel33->Enabled = false;
        QRLabel34->Enabled = false;
    }

}
//---------------------------------------------------------------------------
//‡Šior•s‡Ši ƒ‰ƒxƒ‹ˆóü‘O
void __fastcall TForm4::QRLabel6Print(TObject *sender, AnsiString &Value)
{
    if ( Passflag == 1 )  Value = "‡Ši";
    else  Value = "•s‡Ši";
}
//---------------------------------------------------------------------------
//ŒŸõ
int __fastcall TForm4::Search(int flag)
{
    AnsiString sBuf;
    // Initial Query
    Form4->Query1->Close();
    Form4->Query1->SQL->Clear();

    //–â‚¢‡‚í‚¹•¶ ŽÀs
    // flag = 0 ‚·‚×‚Ä’Šo
    // flag = 1 CPK 1.3ˆÈã‚¾‚¯’Šoi‡Šij
    // flag = 2 CPK 1.3–¢–ž‚¾‚¯’Šoi•s‡Šij
    //sBuf = "SELECT *  FROM KDA1 ";
	sBuf = "SELECT KDA1.KENSA_YMD, KDA1.SEQNO, KDA1.DTKSCOD, KDA1.DTKSHIN, KDA1.LOTNO, ";
	sBuf += "KDA1.HINBAN, KDA1.ZISCOD, KDA1.ZISNAM, KDA1.HIST_SOKUT, KDA1.HIST_KIKAK,  ";
	sBuf += "KDA1.HIST_MIN, KDA1.HIST_MAX, KDA1.SOKUTE_SU, KDA1.SOKUTE_AVE, KDA1.SOKUTE_MIN,  ";
	sBuf += "KDA1.SOKUTE_MAX, KDA1.SOKUTE_R, KDA1.SOKUTE_SGM, KDA1.SOKUTE_CP, KDA1.SOKUTE_CPK,  ";
	sBuf += "KDA1.SOKUTE_K, KDA1.SOKUTE_P, KDA1.ADDYMD, KDA1.ADDTIM, KDA1.UPDYMD, KDA1.UPDTIM,  ";
	sBuf += "KDA1.UPDCHR, KDA1.UPDCNT, SM12S.TANNAM ";
	sBuf += "FROM KDA1, SM12S ";
	sBuf += "WHERE  (KDA1.UPDCHR = SM12S.TANSYA (+))   ";
    sBuf += " AND  KDA1.DTKSHIN = '" + Form1->EdtTKSHIN->Text + "'";
    if ( Trim( Form1->EdtSLOT->Text ) != "" ) {
    //    sBuf += " AND  KDA1.LOTNO >= '000000'";
    //} else {
        sBuf += " AND  KDA1.LOTNO >= '" + Form1->EdtSLOT->Text + "'";
    }
    if ( Trim( Form1->EdtELOT->Text ) != "" ) {
    //    sBuf += " AND  KDA1.LOTNO <= '999999'";
    //} else {
        sBuf += " AND  KDA1.LOTNO >= '" + Form1->EdtELOT->Text + "'";
    }
    if ( Trim( Form1->EdtSYM->Text ) != "" ) {
    //    sBuf += " AND  KDA1.KENSA_YMD >= '00000000'";
    //} else {
        sBuf += " AND  KDA1.KENSA_YMD >= '" + Form1->DelSEPA(Form1->EdtSYM->Text) + "00'";
    }
    if ( Trim( Form1->EdtEYM->Text ) != "" ) {
    //    sBuf += " AND  KDA1.KENSA_YMD <= '99999999'";
    //} else {
        sBuf += " AND  KDA1.KENSA_YMD <= '" + Form1->DelSEPA(Form1->EdtEYM->Text) + "99'";
    }
    switch( flag ){
        case  1: sBuf += " AND KDA1.SOKUTE_CPK >= 1.3 ";   break;
        case  2: sBuf += " AND KDA1.SOKUTE_CPK < 1.3 ";   break;
        break;
    }
    sBuf += " ORDER BY KDA1.DTKSHIN, KDA1.LOTNO, KDA1.KENSA_YMD, KDA1.SEQNO";

    Form4->Query1->SQL->Add(sBuf);
    Form4->Query1->Open();
    Form4->Query1->Active = true;

    if ( Form4->Query1->Bof == true && Form4->Query1->Eof == true ) {
        return ( 0 );
    } else {
        return ( 1 );
    }

}


//---------------------------------------------------------------------------

void __fastcall TForm4::QRLabel44Print(TObject *sender, AnsiString &Value)
{
     Value = " ";
     if ( Query1->Eof == true ) {
        if ( SearchFlag == 2 ) {
            Value = "END";
        } else {
            EndFlag = 1;
        }
     }

}
//---------------------------------------------------------------------------

