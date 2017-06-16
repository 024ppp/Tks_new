/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ16）                    *
*  file   name   : TKS16_Data.cpp                                      *
*  create        : 1999.11.26                                          *
*  contents      : 硬度処理データアクセス関数                          *
*  written by    : 周 欽銘 （NKK Unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Tks16.h"

AnsiString sBuf ;            // ワーク変数

extern int Hsc_HaveSokutei;
extern int Hsd_HaveSokutei;

void KD61Format(void);
void SetTable61(void);
int IsNullSpace( AnsiString  str );
void KD63WFormat(void);
void SetTable63W(int iSp);
int  CheckLotNo(int iSp);

// 硬度処理ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出
int Kd61_Serch01(void)
{

    //硬度測定ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KENSA_YMD, TOLEY_NO ";
    sBuf += "FROM KD61 ";
    sBuf += "WHERE KD61.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KENSA_YMD desc, TOLEY_NO";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;


    sBuf = "検査予定年月日";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "ﾄﾚｰNO.";
    Form2->SGr1->Cells[2][iRow] = sBuf;

    iRow += 1;

    if ( Form1->Query1->RecordCount <= 0 ) {
      // ShowMessage( MSG_02 );
      return 0;
    }else {
      Form1->Query1->First();
      while( !Form1->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

            sBuf = Form1->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] = sBuf;

            sBuf = Form1->Query1->Fields->Fields[1]->AsString;
            Form2->SGr1->Cells[2][iRow] = sBuf;


            Form1->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return Form1->Query1->RecordCount ;
}

//硬度ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出
int Kd61_Serch02( void)
{
    int n,i, iPos;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;

    // KD61Data構造体変数の初期化
    KD61Format();

    //検査値のの取得
    strVal01 = Form1->edtymd->Text;
    // 日付(YYYY/MM/DD)から(YYYYMMDD)へ変換
    while ((iPos = strVal01.AnsiPos("/")) != 0) {
       strVal01.Delete(iPos,1);
    }
    strVal02 = Form1->edttlno->Text;

    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //ソート昇順 ,検査予定日、トレーNo
    sBuf = "SELECT *  ";
    sBuf += "FROM KD61 ";
    sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
    sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
    sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
    //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P";
    sBuf += "ORDER BY SAMPLE_P";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();

    if (Form1->Query1->Eof) { // データ無し
       return -1;
    } else {
       while (!Form1->Query1->Eof ) {
          SetTable61();
          Form1->Query1->Next();
       }
    }

    //Link NO
    for ( i=0; i<29; i++ ){
        if ((KD61Data[i].SOKUTE_KBN1 || KD61Data[i].SOKUTE_KBN2) && KD61Data[i].SAMPLE_P != -1 ) {
           if (KD61Data[i].LINK == 0 ){
              for (int j=i+1; j<30; j++ ){
                  if (KD61Data[i].DTKSHIN == KD61Data[j].DTKSHIN)
                     KD61Data[j].LINK = KD61Data[i].SAMPLE_P;
              }
           }
        }
    }

    //計測数Ｎ＞２の場合 硬度測定（例外）ﾌｧｲﾙを読み込む
    for ( i = 0; i<30; i++ ) {
        if ((KD61Data[i].HSC_SK_NUM > 2 && KD61Data[i].SOKUTE_KBN1 >= 1) ||
           (KD61Data[i].HSD_SK_NUM > 2 && KD61Data[i].SOKUTE_KBN2 >= 1)) {

           Form1->Query1->Close();
           Form1->Query1->SQL->Clear();

           strVal03 = IntToStr( KD61Data[i].SAMPLE_P );

           //問い合せ文実行
           //ソート昇順 、検査予定日、トレーNo、サンプルポジション
           sBuf = "SELECT ";
	   sBuf += "HSC_A, HSC_S, HSD_A, HSD_S, SOKUTEI_NO ";
	   sBuf += "FROM KD62 ";
           sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	   sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
	   sBuf += "AND SAMPLE_P = '" + strVal03 + "' ";
           sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	   //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
           sBuf += "ORDER BY SOKUTEI_NO";

           Form1->Query1->SQL->Add(sBuf);
           Form1->Query1->Open();

           if (Form1->Query1->Eof) { // KD62にデータがありません
               continue;
           } else {
               while( !Form1->Query1->Eof ) {
                  if (Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                     n = 3;
                  }else {
                     n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                  }

                  if ( Form1->Query1->FieldValues["HSC_A"].IsNull()) {
                     KD61Data[i].HSC_A_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSC_A_CH[n-1] =  Form1->Query1->FieldValues["HSC_A"];
                  }

                  if ( Form1->Query1->FieldValues["HSC_S"].IsNull()) {
                     KD61Data[i].HSC_S_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSC_S_CH[n-1] =  Form1->Query1->FieldValues["HSC_S"];
                  }

                  if ( Form1->Query1->FieldValues["HSD_A"].IsNull()) {
                     KD61Data[i].HSD_A_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSD_A_CH[n-1] =  Form1->Query1->FieldValues["HSD_A"];
                  }

                  if ( Form1->Query1->FieldValues["HSD_S"].IsNull()) {
                     KD61Data[i].HSD_S_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSD_S_CH[n-1] =  Form1->Query1->FieldValues["HSD_S"];
                  }

                  Form1->Query1->Next();
               }
           }
        }

    }
    return 0;
}

// 硬度データ構造体KD61Dataを初期化
// update  2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase
void KD61Format(void)
{
   for( int i=0; i<30; i++){
      KD61Data[i].KENSA_YMD =  '\0';   //検索予定日
      KD61Data[i].TOLEY_NO = 0 ;       //ﾄﾚｰNO
      KD61Data[i].SAMPLE_P = -1 ;      //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD61Data[i].SOKUTE_KBN1 = 0;     //測定区分 Hsc
      KD61Data[i].SOKUTE_KBN2 = 0;     //測定区分 Hsd
      KD61Data[i].DTKSCOD = '\0';      //得意先コード
      KD61Data[i].DTKSHIN = '\0';      //得意先品番
      KD61Data[i].LOTNO = '\0';        //ロットNO
      KD61Data[i].HINBAN = '\0';       //自社品番
      KD61Data[i].ZISCOD = '\0';       //材質コード
      KD61Data[i].ZISNAM = '\0';       //材質名

      // HsC
      KD61Data[i].HSC_A_MIN = 0.0;     //HsC 圧面 規格下
      KD61Data[i].HSC_A_MAX = 0.0;     //HsC 圧面 規格上
      KD61Data[i].HSC_S_MIN = 0.0;     //HsC 圧面 規格下
      KD61Data[i].HSC_S_MAX = 0.0;     //HsC 圧面 規格上
      KD61Data[i].HSC_SK_NUM = 0;      //HsC 測定 個数－指示数
      KD61Data[i].HSC_SK_SU = 0;       //Hsc 測定 個数
      KD61Data[i].HSC_A_AVE = 0.0;     //HsC 圧面 測定平均値
      KD61Data[i].HSC_S_AVE = 0.0;     //HsC 側面 測定平均値
      memset(KD61Data[i].HSC_A_CH,(int)NULL, sizeof(int) * 100); ; //Hsc 圧面測定値
      memset(KD61Data[i].HSC_S_CH,(int)NULL, sizeof(int) * 100); ; //Hsc 側面測定値

      // HsD
      KD61Data[i].HSD_A_MIN = 0.0;     //HsD 圧面 規格下
      KD61Data[i].HSD_A_MAX = 0.0;     //HsD 圧面 規格上
      KD61Data[i].HSD_S_MIN = 0.0;     //HsD 圧面 規格下
      KD61Data[i].HSD_S_MAX = 0.0;     //HsD 圧面 規格上
      KD61Data[i].HSD_SK_NUM = 0;      //HsD 測定 個数－指示数
      KD61Data[i].HSD_SK_SU = 0;       //HsD 測定 個数
      KD61Data[i].HSD_A_AVE = 0.0;     //HsD 圧面 測定平均値
      KD61Data[i].HSD_S_AVE = 0.0;     //HsD 側面 測定平均値
      memset(KD61Data[i].HSC_A_CH,(int)NULL, sizeof(double) * 100); ; //Hsc 圧面測定値
      memset(KD61Data[i].HSC_S_CH,(int)NULL, sizeof(double) * 100); ; //Hsc 側面測定値

      KD61Data[i].ADDYMD = '\0';      //登録日
      KD61Data[i].ADDTIM = '\0';      //登録時間
      KD61Data[i].UPDYMD = '\0';      //変更日
      KD61Data[i].UPDTIM = '\0';      //変更時間
      KD61Data[i].UPDCHR = 0;      //更新者
      KD61Data[i].UPDCNT = 0;      //更新回数

      KD61Data[i].LINK = 0;
      KD61Data[i].HSC_SK_NUM_CUR = 0;
      KD61Data[i].HSD_SK_NUM_CUR = 0;
      KD61Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase
   }
}

// KD61Data構造体へﾃﾞｰﾀを設定
// update  2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase
void SetTable61()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

     if (iRec <= 0)
        return;

     KD61Data[iRec-1].SAMPLE_P  = iRec  ;

     iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD61Data[iRec].KENSA_YMD = " ";
     } else {
          KD61Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD61Data[iRec].TOLEY_NO = 0;
     } else {
          KD61Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN1"].IsNull()) {
          KD61Data[iRec].SOKUTE_KBN1 = 0;
     } else
          KD61Data[iRec].SOKUTE_KBN1 =  Form1->Query1->FieldValues["SOKUTE_KBN1"];

     if ( Form1->Query1->FieldValues["SOKUTE_KBN2"].IsNull()) {
          KD61Data[iRec].SOKUTE_KBN2 = 0;
     } else
          KD61Data[iRec].SOKUTE_KBN2 =  Form1->Query1->FieldValues["SOKUTE_KBN2"];

     if( Hsc_HaveSokutei == 0 && KD61Data[iRec].SOKUTE_KBN1 >= 1) {
         Hsc_HaveSokutei = 1;
     }

     if( Hsd_HaveSokutei == 0 && KD61Data[iRec].SOKUTE_KBN2 >= 1) {
         Hsd_HaveSokutei = 1;
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD61Data[iRec].DTKSCOD = " ";
     }else {
          KD61Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD61Data[iRec].DTKSHIN = " ";
     }else {
          KD61Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD61Data[iRec].LOTNO = " ";
     }else {
          KD61Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD61Data[iRec].HINBAN = " ";
     }else {
          KD61Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD61Data[iRec].ZISCOD = " ";
     }else {
          KD61Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD61Data[iRec].ZISNAM = " ";
     }else {
          KD61Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_MIN"].IsNull()) {
          KD61Data[iRec].HSC_A_MIN = 0;
     }else {
          KD61Data[iRec].HSC_A_MIN =  Form1->Query1->FieldValues["HSC_A_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_MAX"].IsNull()) {
          KD61Data[iRec].HSC_A_MAX = 0;
     }else {
          KD61Data[iRec].HSC_A_MAX =  Form1->Query1->FieldValues["HSC_A_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_MIN"].IsNull()) {
          KD61Data[iRec].HSC_S_MIN = 0;
     }else {
          KD61Data[iRec].HSC_S_MIN =  Form1->Query1->FieldValues["HSC_S_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_MAX"].IsNull()) {
          KD61Data[iRec].HSC_S_MAX = 0;
     }else {
          KD61Data[iRec].HSC_S_MAX =  Form1->Query1->FieldValues["HSC_S_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_1"].IsNull()) {
          KD61Data[iRec].HSC_A_CH[0] = 0;
     }else {
          KD61Data[iRec].HSC_A_CH[0] =  Form1->Query1->FieldValues["HSC_A_1"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_2"].IsNull()) {
          KD61Data[iRec].HSC_A_CH[1] = 0;
     }else {
          KD61Data[iRec].HSC_A_CH[1] =  Form1->Query1->FieldValues["HSC_A_2"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_1"].IsNull()) {
          KD61Data[iRec].HSC_S_CH[0] = 0;
     }else {
          KD61Data[iRec].HSC_S_CH[0] =  Form1->Query1->FieldValues["HSC_S_1"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_2"].IsNull()) {
          KD61Data[iRec].HSC_S_CH[1] = 0;
     }else {
          KD61Data[iRec].HSC_S_CH[1] =  Form1->Query1->FieldValues["HSC_S_2"];
     }

     if ( Form1->Query1->FieldValues["HSC_SK_NUM"].IsNull()) {
          KD61Data[iRec].HSC_SK_NUM = 0;
     }else {
          KD61Data[iRec].HSC_SK_NUM =  Form1->Query1->FieldValues["HSC_SK_NUM"];
     }

     if ( Form1->Query1->FieldValues["HSC_SK_SU"].IsNull()) {
          KD61Data[iRec].HSC_SK_SU = 0;
     }else {
          KD61Data[iRec].HSC_SK_SU =  Form1->Query1->FieldValues["HSC_SK_SU"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_AVE"].IsNull()) {
          KD61Data[iRec].HSC_A_AVE = 0.0;
     }else {
          KD61Data[iRec].HSC_A_AVE =  Form1->Query1->FieldValues["HSC_A_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_AVE"].IsNull()) {
          KD61Data[iRec].HSC_S_AVE = 0.0;
     }else {
          KD61Data[iRec].HSC_S_AVE =  Form1->Query1->FieldValues["HSC_S_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_MIN"].IsNull()) {
          KD61Data[iRec].HSD_A_MIN = 0.0;
     }else {
          KD61Data[iRec].HSD_A_MIN =  Form1->Query1->FieldValues["HSD_A_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_MAX"].IsNull()) {
          KD61Data[iRec].HSD_A_MAX = 0.0;
     }else {
          KD61Data[iRec].HSD_A_MAX =  Form1->Query1->FieldValues["HSD_A_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_MIN"].IsNull()) {
          KD61Data[iRec].HSD_S_MIN = 0.0;
     }else {
          KD61Data[iRec].HSD_S_MIN =  Form1->Query1->FieldValues["HSD_S_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_MAX"].IsNull()) {
          KD61Data[iRec].HSD_S_MAX = 0.0;
     }else {
          KD61Data[iRec].HSD_S_MAX =  Form1->Query1->FieldValues["HSD_S_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_1"].IsNull()) {
          KD61Data[iRec].HSD_A_CH[0] = 0.0;
     }else {
          KD61Data[iRec].HSD_A_CH[0] =  Form1->Query1->FieldValues["HSD_A_1"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_2"].IsNull()) {
          KD61Data[iRec].HSD_A_CH[1] = 0.0;
     }else {
          KD61Data[iRec].HSD_A_CH[1] =  Form1->Query1->FieldValues["HSD_A_2"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_1"].IsNull()) {
          KD61Data[iRec].HSD_S_CH[0] = 0.0;
     }else {
          KD61Data[iRec].HSD_S_CH[0] =  Form1->Query1->FieldValues["HSD_S_1"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_2"].IsNull()) {
          KD61Data[iRec].HSD_S_CH[1] = 0.0;
     }else {
          KD61Data[iRec].HSD_S_CH[1] =  Form1->Query1->FieldValues["HSD_S_2"];
     }

     if ( Form1->Query1->FieldValues["HSD_SK_NUM"].IsNull()) {
          KD61Data[iRec].HSD_SK_NUM = 0;
     }else {
          KD61Data[iRec].HSD_SK_NUM =  Form1->Query1->FieldValues["HSD_SK_NUM"];
     }

     if ( Form1->Query1->FieldValues["HSD_SK_SU"].IsNull()) {
          KD61Data[iRec].HSD_SK_SU = 0;
     }else {
          KD61Data[iRec].HSD_SK_SU =  Form1->Query1->FieldValues["HSD_SK_SU"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_AVE"].IsNull()) {
          KD61Data[iRec].HSD_A_AVE = 0.0;
     }else {
          KD61Data[iRec].HSD_A_AVE =  Form1->Query1->FieldValues["HSD_A_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_AVE"].IsNull()) {
          KD61Data[iRec].HSD_S_AVE = 0.0;
     }else {
          KD61Data[iRec].HSD_S_AVE =  Form1->Query1->FieldValues["HSD_S_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD61Data[iRec].ADDYMD = " ";
          KD61Data[iRec].HSC_SK_NUM_CUR = 0;
          KD61Data[iRec].HSD_SK_NUM_CUR = 0;
          KD61Data[iRec].HSC_SK_SU = 0;
          KD61Data[iRec].HSD_SK_SU = 0;
     }else {
          KD61Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD61Data[iRec].ADDYMD )){
             KD61Data[iRec].HSC_SK_NUM_CUR = 0;
             KD61Data[iRec].HSD_SK_NUM_CUR = 0;
             KD61Data[iRec].HSC_SK_SU = 0;
             KD61Data[iRec].HSD_SK_SU = 0;
          }else{
             switch (KD61Data[iRec].SOKUTE_KBN1) {
             case 0:
                  KD61Data[iRec].HSC_SK_NUM_CUR = 0;
                  break;
             case 1:
             case 2:
                  //KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM;
                  KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_SU;
                  break;
             case 3:
                  KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM + KD61Data[iRec].HSC_SK_SU ;
                  //KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM * 2;
                  break;
             }
             switch (KD61Data[iRec].SOKUTE_KBN2) {
             case 0:
                  KD61Data[iRec].HSD_SK_NUM_CUR = 0;
                  break;
             case 1:
             case 2:
                  //KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM;
                  KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_SU;
                  break;
             case 3:
                  //KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM * 2;
                  KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM + KD61Data[iRec].HSD_SK_SU ;
                  break;
             }
          }
     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD61Data[iRec].ADDTIM = " ";
     }else {
          KD61Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD61Data[iRec].UPDYMD = " ";
     }else {
          KD61Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD61Data[iRec].UPDCHR = 0;
     }else {
          KD61Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD61Data[iRec].UPDCNT = 0;
     }else {
          KD61Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD61Data[iRec].MEMO =  " ";
     }else {
          KD61Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

 }

// 文字列中でNULL、Space以外の文字が入っているかどうか
int IsNullSpace( AnsiString  str )
{
   char sBuf[256];
   int i, iRtn;

   iRtn = 1;

   sBuf[0] = NULL ;
   strcpy( sBuf,str.c_str());

   for( i=0; i<str.Length(); i++ ){
      if( sBuf[i] != NULL && sBuf[i] != ' ' ){
         iRtn = 0 ;
         break ;
       }
   }

   return iRtn;

}

// 硬度ﾃﾞｰﾀを硬度ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD61
int Kd61_Update01(void)
{
    int i,j,n,iToroku, rtn;
    AnsiString str;
    char str_c[256];
    double a,s;
    int ErrFlag = 0;

    // 各Sample Loop
    for ( i=0; i<30; i++ ){

        //if (KD61Data[i].SAMPLE_P == -1)
        //   continue;

        iToroku = 1;

        if ((KD61Data[i].SOKUTE_KBN1 >= 1 || KD61Data[i].SOKUTE_KBN2 >= 1) &&
           KD61Data[i].SAMPLE_P != -1  && (KD61Data[i].HSC_SK_NUM_CUR > 0 ||
           KD61Data[i].HSD_SK_NUM_CUR > 0)){

           //担当者ｺｰﾄﾞ
           KD61Data[i].UPDCHR = USER_COD ;

           //HSc:測定値平均値の算出
           a = 0.0;
           s = 0.0;
           if (KD61Data[i].SOKUTE_KBN1 >= 1 && KD61Data[i].HSC_SK_NUM_CUR > 0) {

              switch(KD61Data[i].SOKUTE_KBN1) {
              case 1:
              case 2:
                   KD61Data[i].HSC_SK_SU =  KD61Data[i].HSC_SK_NUM_CUR;
                   break;
              case 3:
                   if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM)
                      KD61Data[i].HSC_SK_SU = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                   else
                      KD61Data[i].HSC_SK_SU = KD61Data[i].HSC_SK_NUM_CUR;
                   break;
              }

              // 圧面データ
              if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                 for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR; j++ ) {
                     if (j < KD61Data[i].HSC_SK_NUM)
                        a += KD61Data[i].HSC_A_CH[j];
                 }
              }

              // 側面データ
              if (KD61Data[i].SOKUTE_KBN1 == 2) {
                 for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR; j++ )
                     if (j < KD61Data[i].HSC_SK_NUM)
                        s += KD61Data[i].HSC_S_CH[j];
              } else {
                 if (KD61Data[i].SOKUTE_KBN1 == 3) {
                    for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR-KD61Data[i].HSC_SK_NUM; j++ )
                        s += KD61Data[i].HSC_S_CH[j];
                 }
              }

             if (KD61Data[i].HSC_SK_NUM ) {
                KD61Data[i].HSC_A_AVE = a/KD61Data[i].HSC_SK_NUM;
                KD61Data[i].HSC_S_AVE = s/KD61Data[i].HSC_SK_NUM;
             }
           } else {
             KD61Data[i].HSC_A_AVE = 0.0;
             KD61Data[i].HSC_S_AVE = 0.0;
           }

           //HSD:測定値平均値の算出
           a = 0.0;
           s = 0.0;
           if (KD61Data[i].SOKUTE_KBN2 >= 1 && KD61Data[i].HSD_SK_NUM_CUR > 0) {

              switch(KD61Data[i].SOKUTE_KBN2) {
              case 1:
              case 2:
                   KD61Data[i].HSD_SK_SU =  KD61Data[i].HSD_SK_NUM_CUR;
                   break;
              case 3:
                   if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM)
                      KD61Data[i].HSD_SK_SU = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                   else
                      KD61Data[i].HSD_SK_SU = KD61Data[i].HSD_SK_NUM_CUR;
                   break;
              }

              // 圧面データ
              if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                 for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR; j++ ) {
                     if (j <= KD61Data[i].HSD_SK_NUM)
                        a += KD61Data[i].HSD_A_CH[j];
                 }
              }

              // 側面データ
              if (KD61Data[i].SOKUTE_KBN2 == 2)  {
                 for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR; j++ )
                     if (j < KD61Data[i].HSD_SK_NUM)
                        s += KD61Data[i].HSD_S_CH[j];
              } else {
                 if (KD61Data[i].SOKUTE_KBN2 == 3) {
                    for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM; j++ )
                        s += KD61Data[i].HSD_S_CH[j];
                 }
              }

             if (KD61Data[i].HSD_SK_NUM ) {
                KD61Data[i].HSD_A_AVE = a/KD61Data[i].HSD_SK_NUM;
                KD61Data[i].HSD_S_AVE = s/KD61Data[i].HSD_SK_NUM;
             }
           } else {
             KD61Data[i].HSD_A_AVE = 0.0;
             KD61Data[i].HSD_S_AVE = 0.0;
           }

	        // 登録日、登録時間
	        if (IsNullSpace( KD61Data[i].ADDYMD )){
	           KD61Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
	           KD61Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

	           //更新回数
	           KD61Data[i].UPDCNT = 0;
	        } else {
	           // 変更日、変更時間
	           KD61Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
	           KD61Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

	           //更新回数
	           KD61Data[i].UPDCNT += 1;

	           iToroku = 0;
	        }

	        str_c[0] = NULL ;

	        //Initial Query1
	        Form1->Query1->Close();
	        Form1->Query1->SQL->Clear();
	        if ( Form1->Database1->InTransaction == false ){
	           Form1->Database1->StartTransaction();
	        }

	        //お問い合せ文  Update
	        sprintf(str_c, " update KD61 set HSC_A_1=%2d, HSC_S_1=%2d, HSC_A_2=%2d, HSC_S_2=%2d, ",
	                           KD61Data[i].HSC_A_CH[0], KD61Data[i].HSC_S_CH[0],
	                           KD61Data[i].HSC_A_CH[1], KD61Data[i].HSC_S_CH[1]);
	        str = str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSC_A_AVE=%9.7f, HSC_S_AVE=%9.7f, HSC_SK_SU=%d, ",
	                           KD61Data[i].HSC_A_AVE,
	                           KD61Data[i].HSC_S_AVE,
	                           KD61Data[i].HSC_SK_SU);
	        str += str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSD_A_1=%3.1f, HSD_S_1=%3.1f, HSD_A_2=%3.1f, HSD_S_2=%3.1f,",
	                           KD61Data[i].HSD_A_CH[0], KD61Data[i].HSD_S_CH[0],
	                           KD61Data[i].HSD_A_CH[1], KD61Data[i].HSD_S_CH[1]);
	        str += str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSD_A_AVE=%9.7f, HSD_S_AVE=%9.7f, HSD_SK_SU=%d, ",
	                           KD61Data[i].HSD_A_AVE,
	                           KD61Data[i].HSD_S_AVE,
	                           KD61Data[i].HSD_SK_SU);
	        str += str_c ;
	        str_c[0] = NULL ;

	        //備考追加 2002/11/07 E.Takase
	        sprintf(str_c, " MEMO='%s' ,",
	                          KD61Data[i].MEMO);
	        str += str_c ;
	        str_c[0] = NULL ;

	        if (iToroku ){
	           wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
	                           KD61Data[i].ADDYMD.c_str(),
	                           KD61Data[i].ADDTIM.c_str(),
	                           KD61Data[i].UPDCHR,
	                           KD61Data[i].UPDCNT );
	        } else{
	           wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
	                           KD61Data[i].UPDYMD.c_str(),
	                           KD61Data[i].UPDTIM.c_str(),
	                           KD61Data[i].UPDCHR,
	                           KD61Data[i].UPDCNT );
	        }
	        str += str_c ;
	        str_c[0] = NULL ;

	        //wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
	        //                        KD61Data[i].KENSA_YMD.c_str(),
	        //                        KD61Data[i].TOLEY_NO ,
	        //                        KD61Data[i].SAMPLE_P );
                // 20160630_工場区分追加
		wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
					KD61Data[i].KENSA_YMD.c_str(),
					KD61Data[i].TOLEY_NO ,
					KD61Data[i].SAMPLE_P ,
					iKojoKbn );

	        str += str_c ;
	        Form1->Query1->SQL->Add(str);

	        //お問い合せ文の実行
	        try
	        {
	            Form1->Query1->ExecSQL();
	            Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
	        }
	        catch(EDatabaseError& e)
	        {
	           // ShowMessage(e.Message);
	           Form1->StatBarClear( e.Message )  ;
	        }
	        catch(Exception& e)
	        {
	           Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
	           // ShowMessage(e.Message);
	           Form1->StatBarClear( e.Message )  ;
	           ErrFlag = 1;
	        }

	        //硬度測定（例外）ﾌｧｲﾙの更新
	        if( KD61Data[i].HSC_SK_NUM > 2 || KD61Data[i].HSD_SK_NUM > 2){
	           rtn = Kd62_Update01(i) ;
	           if (rtn <= 0)
	              ErrFlag = 1;
	        }
        } else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD61Data[i].ADDYMD )) || !(IsNullSpace(KD61Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD61Data[i].ADDYMD )){
					KD61Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD61Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD61Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD61Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD61Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD61Data[i].UPDCNT += 1;

					iToroku = 0;
				}


				str_c[0] = NULL ;
				//Initial Query1
				Form1->Query1->Close();
				Form1->Query1->SQL->Clear();
				if(Form1->Database1->InTransaction == false ){
					Form1->Database1->StartTransaction();
				}
				//お問い合せ文  Update
				sprintf(str_c, " update KD61 set MEMO='%s' , ", KD61Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD61Data[i].ADDYMD.c_str(),
										KD61Data[i].ADDTIM.c_str(),
										KD61Data[i].UPDCHR,
										KD61Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD61Data[i].UPDYMD.c_str(),
										KD61Data[i].UPDTIM.c_str(),
										KD61Data[i].UPDCHR,
										KD61Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD61Data[i].KENSA_YMD.c_str(),
				//					KD61Data[i].TOLEY_NO ,
				//					KD61Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
		                wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
                                                KD61Data[i].KENSA_YMD.c_str(),
					        KD61Data[i].TOLEY_NO ,
					        KD61Data[i].SAMPLE_P ,
					        iKojoKbn );

				str += str_c ;
				Form1->Query1->SQL->Add(str);

				//お問い合せ文の実行
				try
				{
					Form1->Query1->ExecSQL();
					Form1->Database1->Commit();    // 成功した場合、変更をコミットする
				}
				catch(EDatabaseError& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					Form1->StatBarClear( e.Message )  ;
					ErrFlag = 1;
				}
				catch(Exception& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					Form1->StatBarClear( e.Message )  ;
					ErrFlag = 1;
				}
			}
        }

   }

   if (ErrFlag == 0)
      return 1; // OK
   else
      return 0;
}

// 計測ﾃﾞｰﾀを硬度(例外）ﾌｧｲﾙへ書き込む KD62
int Kd62_Update01( int iRec)
{

    int i, iRtn;
    int MaxNum;
    int ErrFlag = 0;

    // 最大測定データを探す（HSCとHSDの間）
    MaxNum = 0;
    if (KD61Data[iRec].SOKUTE_KBN1 >= 1)
       MaxNum = KD61Data[iRec].HSC_SK_NUM;

    if (KD61Data[iRec].SOKUTE_KBN2 >= 1)
       if (MaxNum < KD61Data[iRec].HSD_SK_NUM)
          MaxNum = KD61Data[iRec].HSD_SK_NUM;

    if (MaxNum == 0)
       return 1;

    for ( i=2; i < MaxNum; i++ ){
        // KD62へ追加するレコード存在するかどうかのチェック
        iRtn = Kd62_Serch02( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

        Form1->Database1->StartTransaction();

        // 該当レコードが存在しない場合追加（Insert）
        if (iRtn <= 0 ) {
           iRtn = Kd62_Insert01( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
           if (iRtn <= 0)
              ErrFlag = 1;

        } else{   // 該当レコードが存在する場合更新（Update）
           Kd62_Update02( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
           if (iRtn <= 0)
              ErrFlag = 1;
        }
    }

    if (ErrFlag == 0)
       return 1;
    else
       return 0;
}

// 指定したﾚｺｰﾄが硬度例外ﾌｧｲﾙにあるかどうか
// sYmd: 検査予定年月日
// iTlno: トレーNo
// iSp:   Sample No
// iDtNo: 測定Ｎｏ
int  Kd62_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
     AnsiString strVal01;
     AnsiString strVal02;
     AnsiString strVal03;
     AnsiString strVal04;

     //検査値のの取得
     strVal01 = sYmd;
     strVal02 = IntToStr(iTlno);
     strVal03 = IntToStr( iSp );
     strVal04 = IntToStr( iDtNo );

     Form1->Query1->Close();
     Form1->Query1->SQL->Clear();

     //問い合せ文実行
     //ソート昇順 、検査予定日、トレーNo、サンプルポジション,ﾃﾞｰﾀNO
     sBuf = "SELECT * ";
     sBuf += "FROM KD62 ";
     sBuf += "WHERE KENSA_YMD = '" + strVal01 + "' ";
     sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
     sBuf += "AND SAMPLE_P = '" + strVal03 + "' ";
     sBuf += "AND SOKUTEI_NO = '" + strVal04 + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
     //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";

     Form1->Query1->SQL->Add(sBuf);
     Form1->Query1->Open();

     if ( Form1->Query1->Eof  )
        return 0 ;

    return  1;
}

// KD62へ指定したﾚｺｰﾄﾞを更新する
// sYmd: 検査予定年月日
// iTlno: トレーNo
// iSp:   Sample No
// iDtNo: 測定Ｎｏ
int Kd62_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //お問い合せ文  Update
    sprintf(str_c, " update KD62 set HSC_A=%2d, HSC_S=%2d, HSD_A=%3.1f, HSD_S=%3.1f ",
                    KD61Data[iSp-1].HSC_A_CH[iDtNo-1], KD61Data[iSp-1].HSC_S_CH[iDtNo-1],
                    KD61Data[iSp-1].HSD_A_CH[iDtNo-1], KD61Data[iSp-1].HSD_S_CH[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
                     sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );     // 20160630_工場区分追加

    str += str_c ;
    Form1->Query1->SQL->Add(str);

    //お問い合せ文の実行
    try
    {
       Form1->Query1->ExecSQL();
       Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
    }
    catch(EDatabaseError& e)
    {
       Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
       // ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
    }
    catch(Exception& e)
    {
       Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
       ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
    }

    if (ErrFlag == 1)
       return 0;
    else
       return 0;
}

// KD62へ指定したﾚｺｰﾄﾞを追加する
int Kd62_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //お問い合せ文  Update
    sprintf(str_c, " insert into KD62(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, HSC_A, HSC_S, HSD_A, HSD_S, KOJOKBN)");    // 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%d,%d,%.1f,%.1f,%d)",
            sYmd.c_str(), iTlno, iSp, iDtNo , KD61Data[iSp-1].HSC_A_CH[iDtNo-1],
            KD61Data[iSp-1].HSC_S_CH[iDtNo-1], KD61Data[iSp-1].HSD_A_CH[iDtNo-1],
            KD61Data[iSp-1].HSD_S_CH[iDtNo-1], iKojoKbn);      // 20160630_工場区分追加

    str += str_c ;
    Form1->Query1->SQL->Add(str);

    //お問い合せ文の実行
    try
    {
       Form1->Query1->ExecSQL();
       Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
    }
    catch(EDatabaseError& e)
    {
       //  ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
       ErrFlag = 1;
    }
    catch(Exception& e)
    {
       //  ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
       ErrFlag = 1;
    }

    if (ErrFlag == 0)
       return 1;
    else
       return 0;
}

// 履歴作画のために KD63Wﾜｰｸテーブルを作成する
long  Kd63W_Create01(AnsiString sYmd, int iTlno, int iNum)
{
     //検査予定年月日
     Form1->StoredProc1->Params->Items[0]->AsString = sYmd;

     //ﾄﾚｰNO
     Form1->StoredProc1->Params->Items[1]->AsInteger = iTlno;

     //ロット数
     Form1->StoredProc1->Params->Items[2]->AsInteger = iNum;

     //プログラム実行
     Form1->StoredProc1->Prepare();
     Form1->StoredProc1->ExecProc();

     //レコード数
     long n  = Form1->StoredProc1->Params->Items[3]->AsInteger;

     return n;
}

// KD63Wﾜｰｸﾃｰﾌﾞﾙからリード線長さ計測履歴データ抽出KD63W
int Kd63W_Serch01(void)
{
    int i,j, j1;
    AnsiString strVal01;
    double dAve =0.0;

    // KD63Data構造体変数の初期化
    KD63WFormat();

    // 履歴作画データを読み込む
    for (i=0; i<30; i++ ){
       // 測定しない場合、検索しない
       if (KD61Data[i].SAMPLE_P == -1 ) continue ;

       if (KD61Data[i].SOKUTE_KBN1 == 0 && KD61Data[i].SOKUTE_KBN2 == 0) continue;

       if (KD61Data[i].LINK ) continue ;

       //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
       strVal01 = KD61Data[i].DTKSHIN;

       Form1->Query1->Close();
       Form1->Query1->SQL->Clear();

       //問い合せ文実行
       //ソート昇順 ,検査予定日、トレーNo
       sBuf = "SELECT *  ";
       sBuf += "FROM KD63W ";
       sBuf += "WHERE  DTKSHIN = '" + strVal01 + "' ";
       //20161128 Y.Onishi
       //工場区分に関わらず測定履歴を取得する
       //sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
       sBuf += "ORDER BY ROWNO desc" ;

       Form1->Query1->SQL->Add(sBuf);
       Form1->Query1->Open();

       if (Form1->Query1->RecordCount <= 0 ) {
          // ShowMessage("KD01にデータがありません");
          //return -1;
          continue ;
       } else {
          Form1->Query1->First();
          while ( !Form1->Query1->Eof ) {
                SetTable63W(i);
                Form1->Query1->Next();
          }

          KD63WData[i].LOTCNT +=1  ;
       }

       for (j=0; j < KD63WData[i].LOTCNT; j++ ){
           // HSC
           for (j1 = 0; j1 < 2; j1++) {   // 圧面、側面
               dAve =0.0;
               if (KD63WData[i].HSC_SOKUTEI_NM[j1][j] > 0) {
                  for (int k=0; k < KD63WData[i].HSC_SOKUTEI_NM[j1][j]; k++)
                      dAve += KD63WData[i].HSC_CH[j1][j][k] ;

                  if (KD63WData[i].HSC_SOKUTEI_NM[j1][j] !=0 )
                     KD63WData[i].HSC_AVE[j1][j] = dAve/KD63WData[i].HSC_SOKUTEI_NM[j1][j] ;
               } else
                  KD63WData[i].HSC_AVE[j1][j] = 0.0;
           }
           // HSC
           for (j1 = 0; j1 < 2; j1++) {   // 圧面、側面
               dAve =0.0;
               if (KD63WData[i].HSD_SOKUTEI_NM[j1][j] > 0) {
                  for (int k=0; k < KD63WData[i].HSD_SOKUTEI_NM[j1][j]; k++)
                      dAve += KD63WData[i].HSD_CH[j1][j][k] ;

                  if (KD63WData[i].HSD_SOKUTEI_NM[j1][j] !=0 )
                     KD63WData[i].HSD_AVE[j1][j] = dAve/KD63WData[i].HSD_SOKUTEI_NM[j1][j] ;
               } else
                  KD63WData[i].HSD_AVE[j1][j] = 0.0;
           }
       }
    }

    return 0;
}

// 硬度計測履歴ﾜｰｸﾃﾞｰﾀ構造体KD63dataを初期化
void KD63WFormat(void)
{
   for( int i=0; i<30; i++){
       KD63WData[i].DTKSHIN = '\0';     //得意先品番
       KD63WData[i].LOTCNT = -1;

       for (int j=0; j< 50 ; j++ ){
           KD63WData[i].LOTNO[j]  = "\0";          //ロットNO
           // HSC
           for (int j1 = 0; j1 < 2; j1++) {
               KD63WData[i].HSC_MIN[j1][j] = 0  ;  //規格下
               KD63WData[i].HSC_MAX[j1][j] = 0;    //規格上
               KD63WData[i].HSC_AVE[j1][j] = 0.0;
               KD63WData[i].HSC_SOKUTEI_NM[j1][j] = 0;
               for ( int k=0; k<100; k++ )
                   KD63WData[i].HSC_CH[j1][j][k] = 0.0;  //測定値
           }

           // HSD
           for (int j1 = 0; j1 < 2; j1++) {
               KD63WData[i].HSD_MIN[j1][j] = 0  ;  //規格下
               KD63WData[i].HSD_MAX[j1][j] = 0;    //規格上
               KD63WData[i].HSD_AVE[j1][j] = 0.0;
               KD63WData[i].HSD_SOKUTEI_NM[j1][j] = 0;
               for ( int k=0; k<100; k++ )
                   KD63WData[i].HSD_CH[j1][j][k] = 0.0;  //測定値
           }
       }
    }
}

// ﾜｰｸﾃﾞｰﾀKD63WDataへﾃﾞｰﾀを設定
void SetTable63W(int iSp)
{

     int iDtNo;

     int iLotno = KD63WData[iSp].LOTCNT ;

     if (Form1->Query1->FieldValues["LOTNO"] != KD63WData[iSp].LOTNO[iLotno] )
     {
        iLotno += 1;
        if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
           KD63WData[iSp].LOTNO[iLotno] = " ";
        }else {
           KD63WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
        }

        // HSCのMAXとMIN
        if (Form1->Query1->FieldValues["HSC_A_MIN"].IsNull()) {
           KD63WData[iSp].HSC_MIN[0][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MIN[0][iLotno] = Form1->Query1->FieldValues["HSC_A_MIN"];
        }
        if (Form1->Query1->FieldValues["HSC_A_MAX"].IsNull()) {
           KD63WData[iSp].HSC_MAX[0][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MAX[0][iLotno] = Form1->Query1->FieldValues["HSC_A_MAX"];
        }

        if (Form1->Query1->FieldValues["HSC_S_MIN"].IsNull()) {
           KD63WData[iSp].HSC_MIN[1][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MIN[1][iLotno] = Form1->Query1->FieldValues["HSC_S_MIN"];
        }
        if (Form1->Query1->FieldValues["HSC_S_MAX"].IsNull()) {
           KD63WData[iSp].HSC_MAX[1][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MAX[1][iLotno] = Form1->Query1->FieldValues["HSC_S_MAX"];
        }

        // HSDのMAXとMIN
        if (Form1->Query1->FieldValues["HSD_A_MIN"].IsNull()) {
           KD63WData[iSp].HSD_MIN[0][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MIN[0][iLotno] = Form1->Query1->FieldValues["HSD_A_MIN"];
        }
        if (Form1->Query1->FieldValues["HSD_A_MAX"].IsNull()) {
           KD63WData[iSp].HSD_MAX[0][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MAX[0][iLotno] = Form1->Query1->FieldValues["HSD_A_MAX"];
        }

        if (Form1->Query1->FieldValues["HSD_S_MIN"].IsNull()) {
           KD63WData[iSp].HSD_MIN[1][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MIN[1][iLotno] = Form1->Query1->FieldValues["HSD_S_MIN"];
        }
        if (Form1->Query1->FieldValues["HSD_S_MAX"].IsNull()) {
           KD63WData[iSp].HSD_MAX[1][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MAX[1][iLotno] = Form1->Query1->FieldValues["HSD_S_MAX"];
        }
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD63WData[iSp].DTKSHIN = " ";
     }else {
            KD63WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // HSCの圧面測定値
     iDtNo = KD63WData[iSp].HSC_SOKUTEI_NM[0][iLotno] ;

     if (Form1->Query1->FieldValues["HSC_A"].IsNull()) {
         KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] = Form1->Query1->FieldValues["HSC_A"];
     }
     if (KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSC_SOKUTEI_NM[0][iLotno] = iDtNo;
     }

     // HSCの側面測定値
     iDtNo = KD63WData[iSp].HSC_SOKUTEI_NM[1][iLotno] ;

     if (Form1->Query1->FieldValues["HSC_S"].IsNull()) {
         KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] = Form1->Query1->FieldValues["HSC_S"];
     }
     if (KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSC_SOKUTEI_NM[1][iLotno] = iDtNo;
     }

     // HSDの圧面測定値
     iDtNo = KD63WData[iSp].HSD_SOKUTEI_NM[0][iLotno] ;

     if (Form1->Query1->FieldValues["HSD_A"].IsNull()) {
         KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] = Form1->Query1->FieldValues["HSD_A"];
     }
     if (KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSD_SOKUTEI_NM[0][iLotno] = iDtNo;
     }

     // HSDの側面測定値
     iDtNo = KD63WData[iSp].HSD_SOKUTEI_NM[1][iLotno] ;

     if (Form1->Query1->FieldValues["HSD_S"].IsNull()) {
         KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] = Form1->Query1->FieldValues["HSD_S"];
     }
     if (KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSD_SOKUTEI_NM[1][iLotno] = iDtNo;
     }

     KD63WData[iSp].LOTCNT = iLotno ;
 }

// KD61DataをKD63Wへコピーする
void  CopyKD61Data(void)
{

   int i,n,k,iLinkSp, Cur_Num;
   double a, b;

   for( i = 0; i < 30; i++ ){

        if (KD61Data[i].SAMPLE_P == -1 ) continue ;

        if( KD61Data[i].SOKUTE_KBN1 == 0 && KD61Data[i].SOKUTE_KBN2 == 0 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD61Data[i].LINK == 0 ){
            iLinkSp = KD61Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD61Data[i].LINK;
        }

        if (KD63WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD63WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD63WData[iLinkSp-1].DTKSHIN =  KD61Data[i].DTKSHIN;

           //ロットNO
           KD63WData[iLinkSp-1].LOTNO[0]  = KD61Data[i].LOTNO ;

           // HSC
           // 規格下
           KD63WData[iLinkSp-1].HSC_MIN[0][0] = KD61Data[i].HSC_A_MIN;
           KD63WData[iLinkSp-1].HSC_MIN[1][0] = KD61Data[i].HSC_S_MIN;

           // 規格上
           KD63WData[iLinkSp-1].HSC_MAX[0][0] = KD61Data[i].HSC_A_MAX;
           KD63WData[iLinkSp-1].HSC_MAX[1][0] = KD61Data[i].HSC_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN1) {
           case 1:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = 0;
                break;
           case 3:
                if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM) {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = 0;
                }
                break;
           }

           // HSD
           // 規格下
           KD63WData[iLinkSp-1].HSD_MIN[0][0] = KD61Data[i].HSD_A_MIN;
           KD63WData[iLinkSp-1].HSD_MIN[1][0] = KD61Data[i].HSD_S_MIN;

           // 規格上
           KD63WData[iLinkSp-1].HSD_MAX[0][0] = KD61Data[i].HSD_A_MAX;
           KD63WData[iLinkSp-1].HSD_MAX[1][0] = KD61Data[i].HSD_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN2) {
           case 1:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = 0;
                break;
           case 3:
                if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM) {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = 0;
                }
                break;
           }

           if ( KD61Data[i].HSC_SK_NUM_CUR > 0) {    // HSC
              //測定値
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM && KD61Data[i].SOKUTE_KBN1 == 3) {
                 Cur_Num = KD61Data[i].HSC_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSC_CH[0][0][k] = KD61Data[i].HSC_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSC_CH[0][0][k] ;
                 }
                 //平均値
                 KD63WData[iLinkSp-1].HSC_AVE[0][0] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSC_CH[1][0][k] = KD61Data[i].HSC_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSC_CH[1][0][k] ;
                 }
                 KD63WData[iLinkSp-1].HSC_AVE[1][0] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSC_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                        KD63WData[iLinkSp-1].HSC_CH[0][0][k] = KD61Data[i].HSC_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSC_CH[0][0][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN1 == 2) {
                        KD63WData[iLinkSp-1].HSC_CH[1][0][k] = KD61Data[i].HSC_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSC_CH[1][0][k] ;
                     }
                 }

                 //平均値
                 KD63WData[iLinkSp-1].HSC_AVE[0][0] = a/KD61Data[i].HSC_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSC_AVE[1][0] = b/KD61Data[i].HSC_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSC_AVE[0][0] = 0.0;
              KD63WData[iLinkSp-1].HSC_AVE[1][0] = 0.0;
           }

           if ( KD61Data[i].HSD_SK_NUM_CUR > 0) {    // HSD
              //測定値
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM && KD61Data[i].SOKUTE_KBN2 == 3) {
                 Cur_Num = KD61Data[i].HSD_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSD_CH[0][0][k] = KD61Data[i].HSD_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSD_CH[0][0][k] ;
                 }
                 //平均値
                 KD63WData[iLinkSp-1].HSD_AVE[0][0] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSD_CH[1][0][k] = KD61Data[i].HSD_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSD_CH[1][0][k] ;
                 }
                 KD63WData[iLinkSp-1].HSD_AVE[1][0] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSD_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                        KD63WData[iLinkSp-1].HSD_CH[0][0][k] = KD61Data[i].HSD_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSD_CH[0][0][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN2 == 2) {
                        KD63WData[iLinkSp-1].HSD_CH[1][0][k] = KD61Data[i].HSD_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSD_CH[1][0][k] ;
                     }
                 }

                 //平均値
                 KD63WData[iLinkSp-1].HSD_AVE[0][0] = a/KD61Data[i].HSD_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSD_AVE[1][0] = b/KD61Data[i].HSD_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSD_AVE[0][0] = 0.0;
              KD63WData[iLinkSp-1].HSD_AVE[1][0] = 0.0;
           }
        //----------------------------------------------------------------
        // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
        }else{

           // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
           //ﾛｯﾄNOカンター
           KD63WData[iLinkSp-1].LOTCNT += 1;

           n = KD63WData[iLinkSp-1].LOTCNT ;

           //ロットNO
           KD63WData[iLinkSp-1].LOTNO[n-1]  = KD61Data[i].LOTNO ;

           //HSCの規格下
           KD63WData[iLinkSp-1].HSC_MIN[0][n-1] = KD61Data[i].HSC_A_MIN;
           KD63WData[iLinkSp-1].HSC_MIN[1][n-1] = KD61Data[i].HSC_S_MIN;

           //HSCの規格上
           KD63WData[iLinkSp-1].HSC_MAX[0][n-1] = KD61Data[i].HSC_A_MAX;
           KD63WData[iLinkSp-1].HSC_MAX[1][n-1] = KD61Data[i].HSC_S_MAX;

           //HSDの規格下
           KD63WData[iLinkSp-1].HSD_MIN[0][n-1] = KD61Data[i].HSD_A_MIN;
           KD63WData[iLinkSp-1].HSD_MIN[1][n-1] = KD61Data[i].HSD_S_MIN;

           //HSDの規格上
           KD63WData[iLinkSp-1].HSD_MAX[0][n-1] = KD61Data[i].HSD_A_MAX;
           KD63WData[iLinkSp-1].HSD_MAX[1][n-1] = KD61Data[i].HSD_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN1) {
           case 1:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = 0;
                break;
           case 3:
                if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM) {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = 0;
                }
                break;
           }

           switch (KD61Data[i].SOKUTE_KBN2) {
           case 1:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = 0;
                break;
           case 3:
                if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM) {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = 0;
                }
                break;
           }

           if ( KD61Data[i].HSC_SK_NUM_CUR > 0) {    // HSC
              //測定値
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM && KD61Data[i].SOKUTE_KBN1 == 3) {
                 Cur_Num = KD61Data[i].HSC_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] = KD61Data[i].HSC_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] ;
                 }
                 //平均値
                 KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] = KD61Data[i].HSC_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] ;
                 }
                 KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSC_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                        KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] = KD61Data[i].HSC_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN1 == 2) {
                        KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] = KD61Data[i].HSC_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] ;
                     }
                 }

                 //平均値
                 KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = a/KD61Data[i].HSC_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = b/KD61Data[i].HSC_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = 0.0;
              KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = 0.0;
           }

           if ( KD61Data[i].HSD_SK_NUM_CUR > 0) {    // HSD
              //測定値
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM && KD61Data[i].SOKUTE_KBN2 == 3) {
                 Cur_Num = KD61Data[i].HSD_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] = KD61Data[i].HSD_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] ;
                 }
                 //平均値
                 KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] = KD61Data[i].HSD_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] ;
                 }
                 KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSD_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                        KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] = KD61Data[i].HSD_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN2 == 2) {
                        KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] = KD61Data[i].HSD_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] ;
                     }
                 }

                 //平均値
                 KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = a/KD61Data[i].HSD_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = b/KD61Data[i].HSD_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = 0.0;
              KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = 0.0;
           }
        }

   }
}

// 計測したｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOのﾃﾞｰﾀを履歴ﾃﾞｰﾀへ追加
// A_No: 1: Hsc
//       2: Hsd
void  AddKd63W(int A_No)
{
   int i,iLinkSp, iRtn;
   double dAve ;

   if (!(A_No == 1 || A_No == 2))
      return;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック
   if (A_No == 1) { // Hsc

      if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR == 0 ) return ;

      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 0 ) return ;

      //-------------------------------------
      // ｶﾚﾝﾄ品番が始めて計測場合
      if (KD61Data[Hsc_SamplePositionIdx-1].LINK == 0 ){
         iLinkSp = Hsc_SamplePositionIdx ;
      } else {
         iLinkSp = KD61Data[Hsc_SamplePositionIdx-1].LINK;
      }

      //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
      iRtn =  CheckLotNo(Hsc_SamplePositionIdx ) ;
      if (iRtn <0 ) return ;

      //計測履歴ﾃﾞｰﾀの更新
      //ロットNO
      KD63WData[iLinkSp-1].LOTNO[iRtn] = KD61Data[Hsc_SamplePositionIdx-1].LOTNO;

      // HSC
      //規格下
      KD63WData[iLinkSp-1].HSC_MIN[0][iRtn]= KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MIN;
      KD63WData[iLinkSp-1].HSC_MIN[1][iRtn]= KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MIN;

      //規格上
      KD63WData[iLinkSp-1].HSC_MAX[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MAX;
      KD63WData[iLinkSp-1].HSC_MAX[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MAX;

      switch (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1) {
      case 1:
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = 0;
           break;
      case 2:
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = 0;
           break;
      case 3:
           if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
           } else {
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = 0;
           }
           break;
      }

      // 圧面
      if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] > 0) {
         //測定値
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSC_CH[0][iRtn][i] = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[i];
             dAve += KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn];

         KD63WData[iLinkSp-1].HSC_AVE[0][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSC_AVE[0][iRtn]=0.0;

      // 側面
      if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] > 0) {
         //測定値
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSC_CH[1][iRtn][i] = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[i];
             dAve += KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn];

         KD63WData[iLinkSp-1].HSC_AVE[1][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSC_AVE[1][iRtn]=0.0;
   } else { // HSD

      if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR == 0 ) return ;

      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 0 ) return ;

      //-------------------------------------
      // ｶﾚﾝﾄ品番が始めて計測場合
      if (KD61Data[Hsd_SamplePositionIdx-1].LINK == 0 ){
         iLinkSp = Hsd_SamplePositionIdx ;
      } else {
         iLinkSp = KD61Data[Hsd_SamplePositionIdx-1].LINK;
      }

      //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
      iRtn =  CheckLotNo(Hsd_SamplePositionIdx ) ;
      if (iRtn <0 ) return ;

      //計測履歴ﾃﾞｰﾀの更新
      //ロットNO
      KD63WData[iLinkSp-1].LOTNO[iRtn] = KD61Data[Hsd_SamplePositionIdx-1].LOTNO;

      // HSC
      //規格下
      KD63WData[iLinkSp-1].HSD_MIN[0][iRtn]= KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MIN;
      KD63WData[iLinkSp-1].HSD_MIN[1][iRtn]= KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MIN;

      //規格上
      KD63WData[iLinkSp-1].HSD_MAX[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MAX;
      KD63WData[iLinkSp-1].HSD_MAX[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MAX;

      switch (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2) {
      case 1:
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = 0;
           break;
      case 2:
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = 0;
           break;
      case 3:
           if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
           } else {
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = 0;
           }
           break;
      }

      // 圧面
      if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] > 0) {
         //測定値
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSD_CH[0][iRtn][i] = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[i];
             dAve += KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn];

         KD63WData[iLinkSp-1].HSD_AVE[0][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSD_AVE[0][iRtn]=0.0;

      // 側面
      if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] > 0) {
         //測定値
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSD_CH[1][iRtn][i] = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[i];
             dAve += KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn];

         KD63WData[iLinkSp-1].HSD_AVE[1][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSD_AVE[1][iRtn]=0.0;
   }
}

// KD63Wから読み込んだﾃﾞｰﾀ中にに指定したロットNo 有るかどうか のチェック                            *
int  CheckLotNo(int iSp)
{

   int iLinkSp;

   int iFlag = -1;

    if (KD61Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   } else {
       iLinkSp = KD61Data[iSp-1].LINK;
   }

   for (int i=0; i < KD63WData[iLinkSp-1].LOTCNT; i++ ){
      if (KD61Data[iSp-1].LOTNO ==  KD63WData[iLinkSp-1].LOTNO[i] )
      {
        iFlag = i ;
        break ;
       }
   }

   return iFlag ;
}



/***********************************************************************
*  function name : void Kd63W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd63Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd63W_Delete01(void)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //お問い合せ文  Update
    sprintf(str_c, " DELETE FROM KD63W");

    str = str_c ;
    str_c[0] = NULL ;

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //お問い合せ文の実行
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // 成功した場合、変更をコミットする
     }
     catch(EDatabaseError& e)
     {
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
     }
     catch(Exception& e)
     {
       // ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
     }
 }
