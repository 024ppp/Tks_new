//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

#define MAXLINE 15

int flag = 0;
int Priflag = 1;
int Passflag = 1;
AnsiString OLD_DTKSHIN,NOW_DTKSHIN;
//20161102 Y.Onishi
AnsiString OLD_KOJOKBN,NOW_KOJOKBN;
int OLDPageNo;
int SearchFlag = 1;
int MoreFlag = 0;
int Pageline = 1;
int NextPageFlag = 0;
//int EndFlag;
extern KETA_DATA KETA;  //印刷時の桁数


//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//検査日
void __fastcall TForm3::QRLabel3Print(TObject *sender, AnsiString &Value)
{
    AnsiString str;
    AnsiString Daystr;
    str = Form1->EdtYMD->Text;
    //Daystr = str.SubString(1,4) + "/";
    //Daystr += str.SubString(5,2) + "/";
    //Daystr += str.SubString(7,2);
    Value = str;
}
//---------------------------------------------------------------------------
//検査員名
void __fastcall TForm3::QRLabel4Print(TObject *sender, AnsiString &Value)
{

    if ( Form3->Query1->FieldValues["TANNAM"].IsNull()){
        Value = USER_NAM;
    } else {
        Value = Form3->Query1->FieldValues["TANNAM"];
    }
}
//---------------------------------------------------------------------------
//得意先品番
void __fastcall TForm3::QRLabel7Print(TObject *sender, AnsiString &Value)
{
    if ( Priflag == 0 ) {
        Value = " ";
        return;
    }
    //20161102 Y.Onishi
    //Value = Form3->Query1->FieldValues["DTKSHIN"];
    if ( Form3->Query1->FieldValues["KOJOKBN"] == 0 ) {
        Value = "本)" + Form3->Query1->FieldValues["DTKSHIN"];
    }
    else if ( Form3->Query1->FieldValues["KOJOKBN"] == 1 ) {
        Value = "広)" + Form3->Query1->FieldValues["DTKSHIN"];
    }
    else {
        Value = "？)" + Form3->Query1->FieldValues["DTKSHIN"];
    }
}
//---------------------------------------------------------------------------
//材質名
void __fastcall TForm3::QRLabel8Print(TObject *sender, AnsiString &Value)
{
    if ( Priflag == 0 ) {
        Value = " ";
        return;
    }
    Value = Form3->Query1->FieldValues["ZISNAM"];
}
//---------------------------------------------------------------------------
//ロットNO
void __fastcall TForm3::QRLabel9Print(TObject *sender, AnsiString &Value)
{
    Value = Form3->Query1->FieldValues["LOTNO"];
}
//---------------------------------------------------------------------------
//下限値〜上限値
void __fastcall TForm3::QRLabel10Print(TObject *sender, AnsiString &Value)
{
    AnsiString sBuf;

    if ( Priflag == 0 ) {
        Value = " ";
        return;
    }
    if( Form3->Query1->FieldValues["HIST_KIKAK"] == 1
            || Form3->Query1->FieldValues["HIST_KIKAK"] == 2 ) {
        sBuf = FormatFloat("0.000", StrToFloat(Form3->Query1->FieldValues["HIST_MIN"]));
    } else {
        sBuf = "-";
    }
    Value = AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf + " 〜 ";

    if( Form3->Query1->FieldValues["HIST_KIKAK"] == 1
            || Form3->Query1->FieldValues["HIST_KIKAK"] == 3 ) {
        sBuf = FormatFloat("0.000", StrToFloat(Form3->Query1->FieldValues["HIST_MAX"]));
    } else {
        sBuf = "-";
    }
    Value = Value + AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf;

}
//---------------------------------------------------------------------------
//測定数 Ｎ
void __fastcall TForm3::QRLabel11Print(TObject *sender, AnsiString &Value)
{
    Value =  FormatFloat("0", StrToFloat(Form3->Query1->FieldValues["SOKUTE_SU"]));
}
//---------------------------------------------------------------------------
//平均値 Ave
void __fastcall TForm3::QRLabel12Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.AVE_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_Ave"]));
}
//---------------------------------------------------------------------------
//Ｍｉｎ
void __fastcall TForm3::QRLabel13Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.MIN_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_MIN"]));
}
//---------------------------------------------------------------------------
//Ｍａｘ
void __fastcall TForm3::QRLabel14Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.MAX_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_MAX"]));
}
//---------------------------------------------------------------------------
//標準偏差 σ
void __fastcall TForm3::QRLabel15Print(TObject *sender, AnsiString &Value)
{
    KETA.SOKUTE_SGM = StrToFloat(Form3->Query1->FieldValues["SOKUTE_SGM"]);
	KETA.SGM_str = Form1->ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );

    Value = FormatFloat(KETA.SGM_str, KETA.SOKUTE_SGM);
}
//---------------------------------------------------------------------------
//Ｒ ＭＡＸ−ＭＩＮ
void __fastcall TForm3::QRLabel16Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.R_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_R"]));
}
//---------------------------------------------------------------------------
//Ｃｐ
void __fastcall TForm3::QRLabel17Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.CP_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_CP"]));
}
//---------------------------------------------------------------------------
//Ｋ
void __fastcall TForm3::QRLabel18Print(TObject *sender, AnsiString &Value)
{
    KETA.SOKUTE_K = StrToFloat(Form3->Query1->FieldValues["SOKUTE_K"]);
	KETA.K_str = Form1->ConvKETA2( KETA.K,KETA.SOKUTE_K ,2 );

    Value = FormatFloat(KETA.K_str, KETA.SOKUTE_K);
}
//---------------------------------------------------------------------------
//ＣｐＫ
void __fastcall TForm3::QRLabel19Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.CPK_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_CpK"]));
}
//---------------------------------------------------------------------------
//不良率 Ｐ
void __fastcall TForm3::QRLabel20Print(TObject *sender, AnsiString &Value)
{
    Value = FormatFloat(KETA.P_str, StrToFloat(Form3->Query1->FieldValues["SOKUTE_P"]));
}
//---------------------------------------------------------------------------
//ページ番号
void __fastcall TForm3::QRLabel32Print(TObject *sender, AnsiString &Value)
{
    AnsiString sBuf;
    sBuf = "page " + IntToStr(QuickRep1->PageNumber);
    Value = AnsiString::StringOfChar(' ', 15-sBuf.Length()) + sBuf;
}

//---------------------------------------------------------------------------
//レポート印刷前
void __fastcall TForm3::QuickRep1BeforePrint(TCustomQuickRep *Sender,
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
    n = Form3->Search(1);
    Form3->Query1->First();
}
//---------------------------------------------------------------------------
//詳細項目 1行 印刷後
void __fastcall TForm3::QRBand2AfterPrint(TQRCustomBand *Sender,
      bool BandPrinted)
{
    Form3->Query1->Next();
    iPrtRow++;
    //if ( Pageline > MAXLINE ) { NextPageFlag = 1;  Pageline = 1; }
    //else { NextPageFlag = 0;  Pageline++; }
    

}
//---------------------------------------------------------------------------
//MoreData
void __fastcall TForm3::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    AnsiString sBuf;

    if ( MoreFlag == 0 &&  Form3->Query1->Eof ) {
        MoreFlag = 1;
        Pageline = 1;
        Passflag = 0;

        flag= 1;
        if ( Search(2) == 0 ) {
            MoreData = false;
        } else {
            iPrtRow2 = 1;
            Form3->Query1->First();
            QuickRep1->NewColumn();
            //ShowMessage(IntToStr(QuickRep1->PageNumber));
            MoreData = true;
            Pageline = 1;
            NextPageFlag = 0;
            SearchFlag = 2;
        }
    } else {
        MoreData = !(Form3->Query1->Eof);
    }

}
//---------------------------------------------------------------------------
//詳細項目 1行 印刷前
void __fastcall TForm3::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    if ( flag == 0 ) {
        flag= 1;
        OLD_DTKSHIN = Form3->Query1->FieldValues["DTKSHIN"];
        //20161102 Y.Onishi
        OLD_KOJOKBN = Form3->Query1->FieldValues["KOJOKBN"];

        OLDPageNo = QuickRep1->PageNumber;
        Priflag = 1;
        NextPageFlag = 0;  Pageline++;
    } else {
        NOW_DTKSHIN = Form3->Query1->FieldValues["DTKSHIN"];
        //20161102 Y.Onishi
        NOW_KOJOKBN = Form3->Query1->FieldValues["KOJOKBN"];
        
        NextPageFlag = 0;
        if ( Pageline > MAXLINE ) {
            QuickRep1->NewColumn();
            //ShowMessage("改ページ");
            NextPageFlag = 1;
            Pageline = 2;
            Priflag = 1;
        } else {
            //NextPageFlag = 0;  Pageline++;
            Pageline++;
            if ( iPrtRow2 == 1 ) {
                Priflag = 1;
                iPrtRow2 = 0;
            } else {
                //20161102 Y.Onishi
                //if ( OLD_DTKSHIN == NOW_DTKSHIN && NextPageFlag == 0 ) Priflag = 0;
                if ( OLD_DTKSHIN == NOW_DTKSHIN && OLD_KOJOKBN == NOW_KOJOKBN && NextPageFlag == 0 ) Priflag = 0;
                else Priflag = 1;
            }
        }
        OLDPageNo = QuickRep1->PageNumber;
        OLD_DTKSHIN = NOW_DTKSHIN;
    }
    //ShowMessage(IntToStr( QuickRep1->PageNumber));
}
//---------------------------------------------------------------------------
//QRBand1 印刷前
void __fastcall TForm3::QRBand1BeforePrint(TQRCustomBand *Sender,
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
//合格or不合格 ラベル印刷前
void __fastcall TForm3::QRLabel6Print(TObject *sender, AnsiString &Value)
{
    if ( Passflag == 1 )  Value = "合格";
    else  Value = "不合格";
}
//---------------------------------------------------------------------------
//検索
int __fastcall TForm3::Search(int flag)
{
    AnsiString sBuf;
    AnsiString sYMD;

    sYMD = Form1->DelSEPA(Form1->EdtYMD->Text);
    // Initial Query
    Form3->Query1->Close();
    Form3->Query1->SQL->Clear();

    //問い合わせ文 実行
    // flag = 0 すべて抽出
    // flag = 1 CPK 1.3以上だけ抽出（合格）
    // flag = 2 CPK 1.3未満だけ抽出（不合格）
    //sBuf = "SELECT *  FROM KDA1 ";
	sBuf = "SELECT KDA1.KENSA_YMD, KDA1.SEQNO, KDA1.DTKSCOD, KDA1.DTKSHIN, KDA1.LOTNO, ";
	sBuf += "KDA1.HINBAN, KDA1.ZISCOD, KDA1.ZISNAM, KDA1.HIST_SOKUT, KDA1.HIST_KIKAK,  ";
	sBuf += "KDA1.HIST_MIN, KDA1.HIST_MAX, KDA1.SOKUTE_SU, KDA1.SOKUTE_AVE, KDA1.SOKUTE_MIN,  ";
	sBuf += "KDA1.SOKUTE_MAX, KDA1.SOKUTE_R, KDA1.SOKUTE_SGM, KDA1.SOKUTE_CP, KDA1.SOKUTE_CPK,  ";
	sBuf += "KDA1.SOKUTE_K, KDA1.SOKUTE_P, KDA1.ADDYMD, KDA1.ADDTIM, KDA1.UPDYMD, KDA1.UPDTIM,  ";
	sBuf += "KDA1.UPDCHR, KDA1.UPDCNT, SM12S.TANNAM ";
        //20161102 Y.Onishi
        sBuf += ", KDA1.KOJOKBN ";
	sBuf += "FROM KDA1, SM12S ";
	sBuf += "WHERE  (KDA1.UPDCHR = SM12S.TANSYA (+))   ";

    if (Trim(Form1->EdtYMD->Text) != "") {
        sBuf += " AND  KDA1.KENSA_YMD = '" + sYMD + "'";
    }

    switch( flag ){
        case  1: sBuf += " AND KDA1.SOKUTE_CPK >= 1.3 ";   break;
        case  2: sBuf += " AND KDA1.SOKUTE_CPK < 1.3 ";   break;
        break;
    }

    //20160704追加
    if (Form1->RadioHON->Checked == true ) {
         sBuf += " AND KDA1.KOJOKBN = 0";
    } else if (Form1->RadioKOU->Checked == true ) {
         sBuf += " AND KDA1.KOJOKBN = 1";
    } else if (Form1->RadioRYO->Checked == true ) {
         //Nothing
    } else {
         //Nothing
    }

    //20161102 Y.Onishi
    //sBuf += " ORDER BY KDA1.DTKSHIN, KDA1.LOTNO, KDA1.KENSA_YMD, KDA1.SEQNO";
    sBuf += " ORDER BY KDA1.DTKSHIN, KDA1.LOTNO, KDA1.KENSA_YMD, KDA1.SEQNO, KDA1.KOJOKBN ";

    Form3->Query1->SQL->Add(sBuf);
    Form3->Query1->Open();
    Form3->Query1->Active = true;

    if ( Form3->Query1->Bof == true && Form3->Query1->Eof == true ) {
        return ( 0 );
    } else {
        return ( 1 );
    }

}
//---------------------------------------------------------------------------
//「END」
void __fastcall TForm3::QRLabel42Print(TObject *sender, AnsiString &Value)
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

