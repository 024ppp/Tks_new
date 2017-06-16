//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit8.h"
#include "unit1.h"
#include "unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void  __fastcall TForm1::Tmp_KDB1_SYOKIKA(void)
{
//Tmp_KDB1初期化
	Tmp_KDB1.KENSA_YMD	= "";		//	検査年月日
	Tmp_KDB1.DTKSHIN	= "";		//	得意先品番
	Tmp_KDB1.HINBAN		= "";		//	自社品番
	Tmp_KDB1.ZISCOD		= "";		//	材質コード
	Tmp_KDB1.ZISNAM		= "";		//	材質名
	Tmp_KDB1.LOTNO		= "";		//	ロットNO
	Tmp_KDB1.SEQNO		= 0;		//	SEQ-NO
	Tmp_KDB1.KENSA_KMK	= 0;		//	検査項目
	Tmp_KDB1.KOUMOKU_J	= "";		//	検査項目名（日本語）
	Tmp_KDB1.KOUMOKU_E	= "";		//	検査項目名（English）
	Tmp_KDB1.HIST_SOKUT	= 0;		//	工程能力 測定数
	Tmp_KDB1.HIST_KIKAK	= 0;		//	工程能力 規格
	Tmp_KDB1.HIST_MIN	= 0.0;		//	工程能力 下限規格
	Tmp_KDB1.HIST_MAX	= 0.0;		//	工程能力 上限規格
	Tmp_KDB1.SOKUTE_SU	= 0;		//	測定数
	Tmp_KDB1.SOKUTE_AVE	= 0.0;		//	平均値
	Tmp_KDB1.SOKUTE_MIN	= 0.0;		//	ＭＩＮ
	Tmp_KDB1.SOKUTE_MAX	= 0.0;		//	ＭＡＸ
	Tmp_KDB1.SOKUTE_R	= 0.0;		//	Ｒ
	Tmp_KDB1.SOKUTE_SGM	= 0.0;		//	標準偏差
	Tmp_KDB1.SOKUTE_CP	= 0.0;		//	ＣＰ
	Tmp_KDB1.SOKUTE_CPK	= 0.0;		//	ＣＰＫ
	Tmp_KDB1.SOKUTE_K	= 0.0;		//	Ｋ
	Tmp_KDB1.SOKUTE_P	= 0.0;		//	不良率
	Tmp_KDB1.JYOKEN1	= 0.0;		//	測定条件１
	Tmp_KDB1.JYOKEN2	= 0.0;		//	　〃　　２
	Tmp_KDB1.JYOKEN3	= " ";		//	　〃　　３
	Tmp_KDB1.ADDYMD		= "";		//	登録日
	Tmp_KDB1.ADDTIM		= "";		//	登録時間
	Tmp_KDB1.UPDYMD		= "";		//	変更日
	Tmp_KDB1.UPDTIM		= "";		//	変更時間
	Tmp_KDB1.UPDCHR		= 0;		//	更新者
	Tmp_KDB1.UPDCNT		= 0;		//	更新回数
}

//---------------------------------------------------------------------------
// データを追加します。
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "select KENSA_YMD from KDB1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO);            // SEQNO
     sBuf +=" AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";        // DTKSHIN
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";            // LOTNO

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "既に登録されています。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "insert into KDB1(";
     sBuf += " KENSA_YMD, DTKSHIN, HINBAN, ZISCOD, ZISNAM, LOTNO, SEQNO, ";
     sBuf += " KENSA_KMK, KOUMOKU_J, KOUMOKU_E, HIST_SOKUT, HIST_KIKAK, ";
     //sBuf += " HIST_MIN, HIST_MAX, SOKUTE_SU, ADDYMD, ADDTIM, UPDCHR, UPDCNT, ";
     sBuf += " HIST_MIN, HIST_MAX,  ADDYMD, ADDTIM, UPDCHR, UPDCNT, ";
     sBuf += " KEIJKBN, TANI, SOKUTE_KET, JYOKEN1, JYOKEN2, JYOKEN3 ";
//     if ( Tmp_KDB1.KENSA_KMK == 5 ) {
//        sBuf += " ,JYOKEN1 ";
//     }
     sBuf += " )";

     sBuf += " values('";
     sBuf += Tmp_KDB1.KENSA_YMD				+ "','";		//	検査年月日
	 sBuf += Tmp_KDB1.DTKSHIN				+ "','";		//	得意先品番
	 sBuf += Tmp_KDB1.HINBAN					+ "','";	//	自社品番
	 sBuf += Tmp_KDB1.ZISCOD					+ "','";	//	材質コード
	 sBuf += Tmp_KDB1.ZISNAM					+ "','";	//	材質名
	 sBuf += Tmp_KDB1.LOTNO					+ "',";			//	ロットNO
	 sBuf += IntToStr(Tmp_KDB1.SEQNO)		+ ",";			//	SEQ-NO
	 sBuf += IntToStr(Tmp_KDB1.KENSA_KMK)	+ ",'";			//	検査項目
	 sBuf += Tmp_KDB1.KOUMOKU_J				+ "','";		//	検査項目名（日本語）
	 sBuf += Tmp_KDB1.KOUMOKU_E				+ "',";			//	検査項目名（English）
	 sBuf += IntToStr(Tmp_KDB1.HIST_SOKUT)	+ ",";			//	工程能力 測定数
	 sBuf += IntToStr(Tmp_KDB1.HIST_KIKAK)	+ ",";			//	工程能力 規格
	 sBuf += FloatToStr(Tmp_KDB1.HIST_MIN)	+ ",";			//	工程能力 下限規格
	 sBuf += FloatToStr(Tmp_KDB1.HIST_MAX)	+ ",'";			//	工程能力 上限規格
//	 sBuf += IntToStr(Tmp_KDB1.SOKUTE_SU)	+ ",'";			//	測定数
	 sBuf += Tmp_KDB1.ADDYMD					+ "','";	//	登録日
	 sBuf += Tmp_KDB1.ADDTIM					+ "',";		//	登録時間
	 sBuf += IntToStr(Tmp_KDB1.UPDCHR)		+ ",";			//	更新者
	 sBuf += IntToStr(Tmp_KDB1.UPDCNT)		+ ",";			//	更新回数
	 sBuf += IntToStr(Tmp_KDB1.KEIJKBN)		+ ",'";			//	形状区分
	 sBuf += Tmp_KDB1.TANI          		+ "',";			//	単位
	 sBuf += IntToStr(Tmp_KDB1.SOKUTE_KET)	+ "," ;				//	測定桁
     sBuf += FloatToStr(Tmp_KDB1.JYOKEN1)	+ ",";
     sBuf += FloatToStr(Tmp_KDB1.JYOKEN2)	+ ",'";
     sBuf += Tmp_KDB1.JYOKEN3	+ "'";
     //if ( Tmp_KDB1.KENSA_KMK == 5 ) {
     //   sBuf += "," + FloatToStr(Tmp_KDB1.JYOKEN1);
     //}

     sBuf += ")";

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// データを修正します。
bool __fastcall TForm1::CollectData(String OldKey)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "update KDB1 set ";
	 sBuf +=	"HINBAN='"		+ Tmp_KDB1.HINBAN				+ "', "	;		//	自社品番
	 sBuf +=	"ZISCOD='"		+ Tmp_KDB1.ZISCOD				+ "', "	;		//	材質コード
	 sBuf +=	"ZISNAM='"		+ Tmp_KDB1.ZISNAM				+ "', "	;		//	材質名
	 sBuf +=	"LOTNO='"		+ Tmp_KDB1.LOTNO				+ "', "	;		//	ロットNO
	 sBuf +=	"KENSA_KMK=	"	+ IntToStr(Tmp_KDB1.KENSA_KMK)	+ ", "	;		//	検査項目
	 sBuf +=	"KOUMOKU_J='"	+ Tmp_KDB1.KOUMOKU_J			+ "', "	;		//	検査項目名（日本語）
	 sBuf +=	"KOUMOKU_E='"	+ Tmp_KDB1.KOUMOKU_E			+ "', "	;		//	検査項目名（English）
	 sBuf +=	"HIST_SOKUT="	+ IntToStr(Tmp_KDB1.HIST_SOKUT)	+ ", "	;		//	工程能力 測定数
	 sBuf +=	"HIST_KIKAK="	+ IntToStr(Tmp_KDB1.HIST_KIKAK)	+ ", "	;		//	工程能力 規格
	 sBuf +=	"HIST_MIN="		+ FloatToStr(Tmp_KDB1.HIST_MIN)	+ ", ";			//	工程能力 下限規格
	 sBuf +=	"HIST_MAX="		+ FloatToStr(Tmp_KDB1.HIST_MAX)	+ ", ";			//	工程能力 上限規格
	 sBuf +=	"SOKUTE_SU="	+ IntToStr(Tmp_KDB1.SOKUTE_SU)	+ ", "	;		//	測定数
	 sBuf +=	"UPDYMD='"		+ Tmp_KDB1.UPDYMD				+ "', "	;		//	変更日
	 sBuf +=	"UPDTIM='"		+ Tmp_KDB1.UPDTIM				+ "', "	;		//	変更時間
	 sBuf +=	"UPDCHR="		+ IntToStr(Tmp_KDB1.UPDCHR)		+ ", "	;		//	更新者
	 sBuf +=	"UPDCNT="		+ IntToStr(Tmp_KDB1.UPDCNT)		+ ", "	;		//	更新回数
	 sBuf +=	"KEIJKBN="		+ IntToStr(Tmp_KDB1.KEIJKBN)	+ ", "	;		//	形状区分
	 sBuf +=	"TANI='"		+ Tmp_KDB1.TANI					+ "', ";		//	単位
	 sBuf +=	"JYOKEN1="		+ FloatToStr(Tmp_KDB1.JYOKEN1)	+ ","	;		//	測定条件１
	 sBuf +=	"JYOKEN2="		+ FloatToStr(Tmp_KDB1.JYOKEN2)	+ ","	;		//	測定条件２
	 sBuf +=	"JYOKEN3='"		+ Tmp_KDB1.JYOKEN3 + "'";								//	測定条件３
//     if ( Tmp_KDB1.KENSA_KMK == 5 ) {
//        sBuf +=	", JYOKEN1="		+ FloatToStr(Tmp_KDB1.JYOKEN1)				;		//	形状区分
//     }
     //sBuf += " ) ";


     sBuf += "where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";
     sBuf += "AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";
     sBuf += "AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO) + "";
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";            // LOTNO

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// データを削除します。
bool __fastcall TForm1::DelData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();


     // 問合せ文作成
     sBuf = "select KENSA_YMD from KDB1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO);         // SEQNO
     sBuf +=" AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";        // DTKSHIN
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";            // LOTNO

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "該当のデータが見つかりません。削除できませんでした。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }



     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "delete from KDB1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";  	// 測定日
     sBuf +=" AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";      	// DTKSHIN
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";      		// LOTNO
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO);         	// SEQNO


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "delete from KDB2 ";
     sBuf +=" where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";  	// 測定日
     sBuf +=" AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";      	// DTKSHIN
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";      		// LOTNO
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO);         	// SEQNO


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::DelSEPA(AnsiString sYMD)
{
    int         iPos;
    AnsiString  sRet;

    sRet = sYMD;
    while( (iPos = sRet.AnsiPos("/")) != 0){
        sRet.Delete(iPos,1);
    }

    return( sRet );
}


//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::InsSEPA(AnsiString sYMD)
{
    AnsiString  sRet;

    sRet = sYMD;
    sRet.Insert("/",5);
    sRet.Insert("/",8);

    return( sRet );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExtractCode(AnsiString str)
{
    //ユーザコード、ユーザ名、部署コード、部署名 抽出
    int i,n1,m,strlen;

    //初期化
	USER_COD = 0;
	USER_NAM = "";
	BUMO_COD = "";
	BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //区切り記号","の検索
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=iの時は文字列NULL
                switch(m){
                //変数に文字列代入
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //次の文字列開始位置
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    //部門、担当者
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    Form3->Panel3->Caption = BUMO_COD;
    Form3->Panel4->Caption = BUMO_NAM;
    Form3->Panel6->Caption = IntToStr(USER_COD);
    Form3->Panel7->Caption = USER_NAM;


}


