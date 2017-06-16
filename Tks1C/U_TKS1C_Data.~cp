/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１Ｃ）                  *
*  file   name   : U_TKS1C_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 抗折力測定処理データアクセス関数                    *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void SetTable81(void);
int  KDC2_Serch02( AnsiString , int , int, int );
void KDC2_Update01( int );
void KDC2_Update02( AnsiString , int, int, int );
void KDC2_Insert01( AnsiString , int ,int, int );
void SetTable83W(int);

/***********************************************************************
*  function name : int  KDC1_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 抗折力ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出           *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int KDC1_Serch01(void)
{

    // 抗折力ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KDC1.KENSA_YMD, KDC1.TOLEY_NO ";
    sBuf += "FROM KDC1 ";
	sBuf += "WHERE KDC1.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KDC1.KENSA_YMD desc, KDC1.TOLEY_NO";

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

    if ( Form1->Query1->Eof ) {
      return -1;
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

   return 1 ;
 }


/***********************************************************************
*  function name : void KDC1_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 抗折力ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KDC1                  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  KDC1_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        //検査値のの取得
        strVal01 = DelSEPA(Form1->edtymd->Text);
        if( Save_Click ){
           n= Form1->edttlno->Value + 1;
           strVal02 = IntToStr(n);
        }else
           strVal02 = Form1->edttlno->Text;

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //問い合せ文実行
        //ソート昇順 ,検査予定日、トレーNo
	    sBuf = "SELECT *  ";
	    sBuf += "FROM KDC1 ";
	    sBuf += "WHERE  KDC1.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KDC1.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND  KDC1.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KDC1.KENSA_YMD, KDC1.TOLEY_NO, KDC1.SAMPLE_P";
	    sBuf += "ORDER BY KDC1.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->RecordCount <= 0 ) {
          // ShowMessage("KDC1にデータがありません");
          return -1;
        }else {

            // ﾄﾚｰNOの設定
           if( Save_Click )
               Form1->edttlno->Text = strVal02 ;

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable81();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KDC1Data[i].SOKUTE_KBN  && KDC1Data[i].SAMPLE_P != -1 ) {
             if( KDC1Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KDC1Data[i].DTKSHIN == KDC1Data[j].DTKSHIN)
                        KDC1Data[j].LINK = KDC1Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 抗折力測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
         // if( KDC1Data[i].SOKUTEI_NM > 2 && KDC1Data[i].SOKUTE_KBN == 1 &&
         //     KDC1Data[i].SOKUTEI_NM_CUR > 0 ) {

             if(  KDC1Data[i].SOKUTE_KBN == 1 ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KDC1Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KDC2 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KDC2にデータがありません");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {
                            //測定NO
                            if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             //破壊荷重
                             if ( Form1->Query1->FieldValues["SOKUTEI_K"].IsNull()) {
                                   KDC1Data[i].SOKUTEI_K[n-1] = 0.0;
                             }else {
                                   KDC1Data[i].SOKUTEI_K[n-1] =  Form1->Query1->FieldValues["SOKUTEI_K"];
                             }
                             //ｽﾊﾟﾝ
                            if ( Form1->Query1->FieldValues["SOKUTEI_P"].IsNull()) {
                                   KDC1Data[i].SOKUTEI_P[n-1] = 0.0;
                             }else {
                                   KDC1Data[i].SOKUTEI_P[n-1] =  Form1->Query1->FieldValues["SOKUTEI_P"];
                             }

                             if( !iBotai ) {

                                 //厚さ寸法
                                 if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                      KDC1Data[i].SOKUTEI_S[n-1] = 0.0;
                                 }else {
                                      KDC1Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                                 }
                                 //幅寸法
                                if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                      KDC1Data[i].SOKUTEI_H[n-1] = 0.0;
                                 }else {
                                     KDC1Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                                 }
                                 //抗折力
                                if ( Form1->Query1->FieldValues["SOKUTEI_M"].IsNull()) {
                                     KDC1Data[i].SOKUTEI_M[n-1] = 0.0;
                                }else {
                                     KDC1Data[i].SOKUTEI_M[n-1] =  Form1->Query1->FieldValues["SOKUTEI_M"];
                                }
                            }else{
                                // 抗折力の再計算
                                 MForceCal(i+1,n ) ;
                            }


                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable81(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : KDC1Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable81()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KDC1Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KDC1Data[iRec].KENSA_YMD = " ";
     }else {
          KDC1Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KDC1Data[iRec].TOLEY_NO = 0;
     }else {
          KDC1Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KDC1Data[iRec].SOKUTE_KBN = 0;
     }else {
          KDC1Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 && KDC1Data[iRec].SOKUTE_KBN == 1 ){
            HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KDC1Data[iRec].KEIJYO_KBN = 0;
     }else {
          KDC1Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }


     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KDC1Data[iRec].DTKSCOD = " ";
     }else {
          KDC1Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KDC1Data[iRec].DTKSHIN = " ";
     }else {
          KDC1Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KDC1Data[iRec].LOTNO = " ";
     }else {
          KDC1Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KDC1Data[iRec].HINBAN = " ";
     }else {
          KDC1Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KDC1Data[iRec].ZISCOD = " ";
     }else {
          KDC1Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KDC1Data[iRec].ZISNAM = " ";
     }else {
          KDC1Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["MAGEG_MIN"].IsNull()) {
          KDC1Data[iRec].MAGEG_MIN = 0.0;
     }else {
          KDC1Data[iRec].MAGEG_MIN =  Form1->Query1->FieldValues["MAGEG_MIN"];
     }

     if ( Form1->Query1->FieldValues["MAGEG_MAX"].IsNull()) {
          KDC1Data[iRec].MAGEG_MAX = 0.0;
     }else {
          KDC1Data[iRec].MAGEG_MAX =  Form1->Query1->FieldValues["MAGEG_MAX"];
     }

     if ( Form1->Query1->FieldValues["MAGEG_SPAN"].IsNull()) {
          KDC1Data[iRec].MAGEG_SPAN = 0.0;
     }else {
          KDC1Data[iRec].MAGEG_SPAN =  Form1->Query1->FieldValues["MAGEG_SPAN"];
     }

     if ( Form1->Query1->FieldValues["MAGEG_TAN"].IsNull()) {
          KDC1Data[iRec].MAGEG_TAN = 0;
     }else {
          KDC1Data[iRec].MAGEG_TAN =  Form1->Query1->FieldValues["MAGEG_TAN"];
     }

      //破壊荷重１、破壊荷重２
     if ( Form1->Query1->FieldValues["SOKUTEI_1K"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_K[0] = 0.0;
     }else {
          KDC1Data[iRec].SOKUTEI_K[0] =  Form1->Query1->FieldValues["SOKUTEI_1K"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2K"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_K[1] = 0.0;
     }else {
          KDC1Data[iRec].SOKUTEI_K[1] =  Form1->Query1->FieldValues["SOKUTEI_2K"];
     }
     //ｽﾊﾟﾝ１、ｽﾊﾟﾝ２
      if ( Form1->Query1->FieldValues["SOKUTEI_1P"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_P[0] = 0.0;
     }else {
          KDC1Data[iRec].SOKUTEI_P[0] =  Form1->Query1->FieldValues["SOKUTEI_1P"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2P"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_P[1] = 0.0;
     }else {
          KDC1Data[iRec].SOKUTEI_P[1] =  Form1->Query1->FieldValues["SOKUTEI_2P"];
     }

     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_NM = 0;
     }else {
          KDC1Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_SU = 0;
     }else {
          KDC1Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KDC1Data[iRec].ADDYMD = " ";
     }else {
          KDC1Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];

     }

     if( IsNullSpace( KDC1Data[iRec].ADDYMD )){
             KDC1Data[iRec].SOKUTEI_NM_CUR = 0 ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
                 KDC1Data[iRec].SOKUTEI_NS_CUR = 0;
                 KDC1Data[iRec].SOKUTEI_NH_CUR = 0;
             }
             KDC1Data[iRec].SOKUTEI_NK_CUR = 0;

             //指示スパンをﾜｰｸ変数へ保存
             for( int i=0; i< KDC1Data[iRec].SOKUTEI_NM; i++ )
                   KDC1Data[iRec].SOKUTEI_P[i] = KDC1Data[iRec].MAGEG_SPAN;

              KDC1Data[iRec].SOKUTEI_NP_CUR = KDC1Data[iRec].SOKUTEI_SU ;
     }else{
             KDC1Data[iRec].SOKUTEI_NM_CUR = KDC1Data[iRec].SOKUTEI_SU ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR){
                KDC1Data[iRec].SOKUTEI_NS_CUR = KDC1Data[iRec].SOKUTEI_SU ;
                KDC1Data[iRec].SOKUTEI_NH_CUR = KDC1Data[iRec].SOKUTEI_SU ;
             }
             KDC1Data[iRec].SOKUTEI_NK_CUR = KDC1Data[iRec].SOKUTEI_SU ;
             KDC1Data[iRec].SOKUTEI_NP_CUR = KDC1Data[iRec].SOKUTEI_SU ;
     }
     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KDC1Data[iRec].ADDTIM = " ";
     }else {
          KDC1Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KDC1Data[iRec].UPDYMD = " ";
     }else {
          KDC1Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KDC1Data[iRec].UPDCHR = 0;
     }else {
          KDC1Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KDC1Data[iRec].UPDCNT = 0;
     }else {
          KDC1Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KDC1Data[iRec].MEMO = " ";
     }else {
          KDC1Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

     // 母体比重計測ﾃﾞｰﾀを使う場合
  //   if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
        if( ! iBotai ){

       // 厚さ寸法１、厚さ寸法２
       if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
          KDC1Data[iRec].SOKUTEI_S[0] = 0.0;
        }else {
          KDC1Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
             KDC1Data[iRec].SOKUTEI_S[1] = 0.0;
        }else {
             KDC1Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
        }

        //幅寸法１、幅寸法２
         if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
             KDC1Data[iRec].SOKUTEI_H[0] = 0.0;
        }else {
             KDC1Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
             KDC1Data[iRec].SOKUTEI_H[1] = 0.0;
        }else {
             KDC1Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
        }

        //測定値１抗折力
         if ( Form1->Query1->FieldValues["SOKUTEI_1M"].IsNull()) {
              KDC1Data[iRec].SOKUTEI_M[0] = 0.0;
         }else {
              KDC1Data[iRec].SOKUTEI_M[0] =  Form1->Query1->FieldValues["SOKUTEI_1M"];
         }
         //測定値２ 抗折力
        if ( Form1->Query1->FieldValues["SOKUTEI_2M"].IsNull()) {
             KDC1Data[iRec].SOKUTEI_M[1] = 0.0;
        }else {
             KDC1Data[iRec].SOKUTEI_M[1] =  Form1->Query1->FieldValues["SOKUTEI_2M"];
        }

        //測定値平均値（抗折力）
        if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
             KDC1Data[iRec].SOKUTE_AVE = 0.0;
        }else {
             KDC1Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
        }
        //備考 2002/11/07 E.Takase
        if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
             KDC1Data[iRec].MEMO =  " ";
        }else {
             KDC1Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
        }
     }else{

        // 固有抵抗率の再計算
          MForceCal(iRec+1,1 ) ;
          MForceCal(iRec+1,2 ) ;

          //平均値は使っていないので無視する
     }

 }

/***********************************************************************
*  function name : void KDC1Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : リード線取付抵抗データ構造体KDC1Dataを初期化  KDC1  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KDC1Format(void)
{
   for( int i=0; i<30; i++){
      KDC1Data[i].KENSA_YMD =  '\0';  //検索予定日
      KDC1Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KDC1Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KDC1Data[i].SOKUTE_KBN = 0;     //測定区分
      KDC1Data[i].KEIJYO_KBN =0 ;     //形状区分
      KDC1Data[i].DTKSCOD = '\0';     //得意先コード
      KDC1Data[i].DTKSHIN = '\0';     //得意先品番
      KDC1Data[i].LOTNO = '\0';       //ロットNO
      KDC1Data[i].HINBAN = '\0';      //自社品番
      KDC1Data[i].ZISCOD = '\0';      //材質コード
      KDC1Data[i].ZISNAM = '\0';      //材質名

      KDC1Data[i].MAGEG_MAX = 0.0;    //曲げ強度 規格上
      KDC1Data[i].MAGEG_MIN = 0.0;    //曲げ強度 規格下
      KDC1Data[i].MAGEG_SPAN = 0.0;   //曲げ強度 測定ｽﾊﾟﾝ
      KDC1Data[i].MAGEG_TAN = 0;      //曲げ強度 単位
      KDC1Data[i].SOKUTEI_NM = 0;    //曲げ強度 測定個数
      KDC1Data[i].SOKUTEI_SU = 0;    //曲げ強度 測定個数
      KDC1Data[i].SOKUTE_AVE = 0.0;  //曲げ強度 測定平均値

      memset(KDC1Data[i].SOKUTEI_M,(int)NULL, sizeof(double) * 100); ;  //測定値
      memset(KDC1Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //厚さ寸法
      memset(KDC1Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //幅寸法
      memset(KDC1Data[i].SOKUTEI_K,(int)NULL, sizeof(double) * 100); ;  //破壊荷重
      memset(KDC1Data[i].SOKUTEI_P,(int)NULL, sizeof(double) * 100); ;  //ｽﾊﾟﾝ

      KDC1Data[i].ADDYMD = '\0';      //登録日
      KDC1Data[i].ADDTIM = '\0';      //登録時間
      KDC1Data[i].UPDYMD = '\0';      //変更日
      KDC1Data[i].UPDTIM = '\0';      //変更時間
      KDC1Data[i].UPDCHR = 0;         //更新者
      KDC1Data[i].UPDCNT = 0;         //更新回数
      KDC1Data[i].LINK = 0;
      KDC1Data[i].SOKUTEI_NM_CUR = 0;
      KDC1Data[i].SOKUTEI_NS_CUR = 0;
      KDC1Data[i].SOKUTEI_NH_CUR = 0;
      KDC1Data[i].SOKUTEI_NK_CUR = 0;
      KDC1Data[i].SOKUTEI_NP_CUR = 0;
      KDC1Data[i].SOKUTEI_NP_CUR = 0;

      KDC1Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void KDC1_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀを抗折力ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KDC1            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  KDC1_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ1
             if( iKomoku==1)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_K[0] = pEdt1_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // 計測ﾃﾞｰﾀ2
             if( iKomoku==1)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KDC1Data[SamplePositionIdx-1].SOKUTEI_K[1] = pEdt2_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 2 );

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KDC1Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                 n = pEdt4_S[iKomoku-1]->Value;
                 if( n>=3 && n <= KDC1Data[SamplePositionIdx-1].SOKUTEI_NM ) {

                    // 計測ﾃﾞｰﾀ2
                   if( iKomoku==1)
                      KDC1Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==2)
                      KDC1Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==3)
                      KDC1Data[SamplePositionIdx-1].SOKUTEI_K[n-1] = pEdt3_S[iKomoku-1]->Value;

                   MForceCal(SamplePositionIdx, n );
                 }
             }
    }


	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KDC1Data[i].SOKUTE_KBN == 1 && KDC1Data[i].SAMPLE_P != -1 &&
				!( KDC1Data[i].SOKUTEI_NM_CUR == 0 &&
				KDC1Data[i].SOKUTEI_NS_CUR == 0 &&
				KDC1Data[i].SOKUTEI_NH_CUR == 0 &&
				KDC1Data[i].SOKUTEI_NK_CUR == 0 )  ){

			//担当者ｺｰﾄﾞ
			KDC1Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KDC1Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			//KDC1Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KDC1Data[i].SOKUTEI_NM_CUR; j++ )
				a += KDC1Data[i].SOKUTEI_M[j] ;
			if( KDC1Data[i].SOKUTEI_NM_CUR )
				KDC1Data[i].SOKUTE_AVE = a/KDC1Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KDC1Data[i].ADDYMD )){
				KDC1Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KDC1Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KDC1Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KDC1Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KDC1Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KDC1Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KDC1 set SOKUTEI_SU=%d, SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KDC1Data[i].SOKUTEI_NM_CUR,
								KDC1Data[i].SOKUTEI_S[0],
								KDC1Data[i].SOKUTEI_S[1],
								KDC1Data[i].SOKUTEI_H[0],
								KDC1Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			//2003.02.10 E.Takase sprintf(str_c, " SOKUTEI_1K=%6.1f , SOKUTEI_2K=%6.1f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
			sprintf(str_c, " SOKUTEI_1K=%6.2f , SOKUTEI_2K=%6.2f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
								KDC1Data[i].SOKUTEI_K[0],
								KDC1Data[i].SOKUTEI_K[1],
								KDC1Data[i].SOKUTEI_P[0],
								KDC1Data[i].SOKUTEI_P[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1M=%9.3f , SOKUTEI_2M=%9.3f, SOKUTE_AVE=%12.6f,",
								KDC1Data[i].SOKUTEI_M[0],
								KDC1Data[i].SOKUTEI_M[1],
								KDC1Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KDC1Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KDC1Data[i].ADDYMD.c_str(),
									KDC1Data[i].ADDTIM.c_str(),
									KDC1Data[i].UPDCHR,
									KDC1Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KDC1Data[i].UPDYMD.c_str(),
									KDC1Data[i].UPDTIM.c_str(),
									KDC1Data[i].UPDCHR,
									KDC1Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
								KDC1Data[i].KENSA_YMD.c_str(),
								KDC1Data[i].TOLEY_NO ,
								KDC1Data[i].SAMPLE_P ,
                                                                iKojoKbn);           //工場区分追加

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
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}
			catch(Exception& e)
			{
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			// 抗折力測定（例外）ﾌｧｲﾙの更新
			if( KDC1Data[i].SOKUTEI_NM > 2 ){
				KDC2_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KDC1Data[i].ADDYMD )) || !(IsNullSpace(KDC1Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KDC1Data[i].ADDYMD )){
					KDC1Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KDC1Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KDC1Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KDC1Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KDC1Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KDC1Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KDC1 set MEMO='%s' , ", KDC1Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KDC1Data[i].ADDYMD.c_str(),
										KDC1Data[i].ADDTIM.c_str(),
										KDC1Data[i].UPDCHR,
										KDC1Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KDC1Data[i].UPDYMD.c_str(),
										KDC1Data[i].UPDTIM.c_str(),
										KDC1Data[i].UPDCHR,
										KDC1Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
									KDC1Data[i].KENSA_YMD.c_str(),
									KDC1Data[i].TOLEY_NO ,
									KDC1Data[i].SAMPLE_P ,
                                                                        iKojoKbn);           //工場区分追加

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
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
				catch(Exception& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
			}
		}
	}
}



/***********************************************************************
*  function name : void KDC2_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀ(>2)を抗折力測定(例外）ﾌｧｲﾙへ書き込む  KDC2 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  KDC2_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KDC1Data[iRec].SOKUTEI_NM; i++ ){

         // KDC2へ追加するレコード存在するかどうかのチェック
         iRtn = KDC2_Serch02( KDC1Data[iRec].KENSA_YMD,
                          KDC1Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn < 0 ) {
                KDC2_Insert01( KDC1Data[iRec].KENSA_YMD,
                          KDC1Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                KDC2_Update02( KDC1Data[iRec].KENSA_YMD,
                          KDC1Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
          }
    }
}

/***********************************************************************
*  function name : int IsNullSpace( AnsiString str)                   *
*                  +--------------------------------------+            *
*          引  数  | str       |  チェックする文字列      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  0      |  NULL or Space             |            *
*                  |  １     |  NULL or Space以外の文字   |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 文字列中でNULL、Space以外の文字が入っているかどうか *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
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

/***********************************************************************
*  function name : int KDC2_Serch02(AnsiString sYmd, int iTlno,        *
*                                   int iSp, int iDtNo)                *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  0      |  レコード無し              |            *
*                  |  ＞０   |  レコード数                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 指定したﾚｺｰﾄﾞが抗折力例外ﾌｧｲﾙにあるかどうかのﾁｪｯｸ   *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  KDC2_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KDC2 ";
        sBuf += "WHERE  KDC2.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KDC2.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KDC2.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KDC2.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KDC2.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KDC2.KENSA_YMD, KDC2.TOLEY_NO, KDC2.SAMPLE_P, KDC2.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void KDC2_Update02(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KDC2へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  KDC2_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //お問い合せ文  Update
    sprintf(str_c, " update KDC2 set SOKUTEI_S=%6.3f ,", KDC1Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.3f ,", KDC1Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, "SOKUTEI_K=%6.1f ,", KDC1Data[iSp-1].SOKUTEI_K[iDtNo-1]);
    sprintf(str_c, "SOKUTEI_K=%6.2f ,", KDC1Data[iSp-1].SOKUTEI_K[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_P=%4.1f ,", KDC1Data[iSp-1].SOKUTEI_P[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEI_M=%9.3f", KDC1Data[iSp-1].SOKUTEI_M[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
                                sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );    //工場区分追加

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
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
 }

/***********************************************************************
*  function name : void KDC2_Insert01(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KDC2へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  KDC2_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }
    //お問い合せ文  Update
    sprintf(str_c, " insert into  KDC2(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO,SOKUTEI_S,SOKUTEI_H, SOKUTEI_K,SOKUTEI_P, SOKUTEI_M, KOJOKBN )");

    str = str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.1f,%4.1f,%9.3f)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%4.1f,%9.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
                                                      KDC1Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                                      KDC1Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                                      KDC1Data[iSp-1].SOKUTEI_K[iDtNo-1],
                                                      KDC1Data[iSp-1].SOKUTEI_P[iDtNo-1],
                                                      KDC1Data[iSp-1].SOKUTEI_M[iDtNo-1],
                                                      iKojoKbn );                        //工場区分追加

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
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
 }


/***********************************************************************
*  function name : void KDC3W_Create01(AnsiString sYmd, int iTlno,     *
*                                                       int iNum)      *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iNum       |  ロット数               |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |             | レコード数             |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 履歴作画のために KDC3Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  KDC3W_Create01(AnsiString sYmd, int iTlno, int iNum)
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

/***********************************************************************
*  function name : void KDC3WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗履歴ﾜｰｸﾃﾞｰﾀ構造体KD83dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KDC3WFormat(void)
{
   for( int i=0; i<30; i++){
       KDC3WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KDC3WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KDC3WData[i].MAGEG_MAX[j] = 0.0  ;    //曲げ強度 規格上
            KDC3WData[i].MAGEG_MIN[j] = 0.0  ;    //曲げ強度 規格下
            KDC3WData[i].SOKUTE_AVE[j] = 0.0;
            KDC3WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KDC3WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KDC3WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  KDC3W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KDC3Wﾜｰｸﾃｰﾌﾞﾙからリード線取付抵抗履歴データ抽出KDC3W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  KDC3W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KDC1Data[i].SOKUTE_KBN == 0 && KDC1Data[i].SAMPLE_P == -1 ) continue ;
             if( KDC1Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
             strVal01 = KDC1Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KDC3W ";
	      sBuf += "WHERE  KDC3W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KDC3W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        //工場区分追加
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KDC1にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable83W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KDC3WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KDC3WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KDC3WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KDC3WData[i].SOKUTEI[j][k] ;

               if( KDC3WData[i].SOKUTEI_NM[j] !=0 )
                   KDC3WData[i].SOKUTE_AVE[j] = dAve/KDC3WData[i].SOKUTEI_NM[j] ;
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable83W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKDC3WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable83W(int iSp)
{

     int iLotno = KDC3WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KDC3WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KDC3WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KDC3WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["MAGEG_MIN"].IsNull()) {
               KDC3WData[iSp].MAGEG_MIN[iLotno] = 0.0;
            }else {
                KDC3WData[iSp].MAGEG_MIN[iLotno] = Form1->Query1->FieldValues["MAGEG_MIN"];
            }

            if ( Form1->Query1->FieldValues["MAGEG_MAX"].IsNull()) {
               KDC3WData[iSp].MAGEG_MAX[iLotno] = 0.0;
            }else {
                KDC3WData[iSp].MAGEG_MAX[iLotno] = Form1->Query1->FieldValues["MAGEG_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KDC3WData[iSp].DTKSHIN = " ";
     }else {
            KDC3WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KDC3WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KDC3WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KDC3WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KDC3WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KDC3WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKDC1Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KDC1DataをKDC1Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKDC1Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KDC1Data[i].SOKUTE_KBN == 0 || KDC1Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KDC1Data[i].LINK == 0 ){
            iLinkSp = KDC1Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KDC1Data[i].LINK;
        }

        if( KDC3WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KDC3WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KDC3WData[iLinkSp-1].DTKSHIN =  KDC1Data[i].DTKSHIN;

           //ロットNO
           KDC3WData[iLinkSp-1].LOTNO[0]  = KDC1Data[i].LOTNO ;

           // 規格下
           KDC3WData[iLinkSp-1].MAGEG_MIN[0] = KDC1Data[i].MAGEG_MIN;
           // 規格上
           KDC3WData[iLinkSp-1].MAGEG_MAX[0] = KDC1Data[i].MAGEG_MAX;

           KDC3WData[iLinkSp-1].SOKUTEI_NM[0] = KDC1Data[i].SOKUTEI_NM_CUR;

           if( KDC1Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KDC1Data[i].SOKUTEI_NM; k++ ) {
                  KDC3WData[iLinkSp-1].SOKUTEI[0][k] = KDC1Data[i].SOKUTEI_M[k];
                  a += KDC3WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KDC1Data[i].SOKUTEI_NM != 0 )
             KDC3WData[iLinkSp-1].SOKUTE_AVE[0] = a/KDC1Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KDC3WData[iLinkSp-1].LOTCNT += 1;

          n = KDC3WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KDC3WData[iLinkSp-1].LOTNO[n-1]  = KDC1Data[i].LOTNO ;

          //リード線長さ 規格下
          KDC3WData[iLinkSp-1].MAGEG_MIN[n-1] = KDC1Data[i].MAGEG_MIN;

          //リード線長さ 規格上
          KDC3WData[iLinkSp-1].MAGEG_MAX[n-1] = KDC1Data[i].MAGEG_MAX;

          KDC3WData[iLinkSp-1].SOKUTEI_NM[n-1] = KDC1Data[i].SOKUTEI_NM_CUR;

          if( KDC1Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KDC1Data[i].SOKUTEI_NM; k++ ) {
               KDC3WData[iLinkSp-1].SOKUTEI[n-1][k] = KDC1Data[i].SOKUTEI_M[k];
               a += KDC3WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KDC3WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KDC1Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKDC3W(void)                                 *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測したｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOのﾃﾞｰﾀを履歴ﾃﾞｰﾀへ追加        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  AddKDC3W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KDC1Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KDC1Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KDC1Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KDC3WData[iLinkSp-1].LOTNO[iRtn] = KDC1Data[SamplePositionIdx-1].LOTNO;

   //リード線長さ 規格下
    KDC3WData[iLinkSp-1].MAGEG_MIN[iRtn]= KDC1Data[SamplePositionIdx-1].MAGEG_MIN;

    //リード線長さ 規格上
    KDC3WData[iLinkSp-1].MAGEG_MAX[iRtn] = KDC1Data[SamplePositionIdx-1].MAGEG_MAX;

    KDC3WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KDC1Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KDC3WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KDC3WData[iLinkSp-1].SOKUTEI[iRtn][i] = KDC1Data[SamplePositionIdx-1].SOKUTEI_M[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KDC1Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KDC1Data[SamplePositionIdx-1].SOKUTEI_M[i];
   }

   dAve= dAve/KDC1Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KDC3WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}

/***********************************************************************
*  function name : void Kd51_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD51                  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd51_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD51Data構造体変数の初期化
        KD51Format();

        //検査値のの取得
        strVal01 = DelSEPA(Form1->edtymd->Text);
        if( Save_Click ){
           n= Form1->edttlno->Value + 1;
           strVal02 = IntToStr(n);
        }else
           strVal02 = Form1->edttlno->Text;

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //問い合せ文実行
        //ソート昇順 ,検査予定日、トレーNo
	    sBuf = "SELECT *  ";
	    sBuf += "FROM KD51 ";
	    sBuf += "WHERE  KD51.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD51.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND  KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	    sBuf += "ORDER BY KD51.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD51にデータがありません");
          return -1;
        }else {
           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable51();
                     Form1->Query1->Next();

            }
       }

       //計測数Ｎ＞２の場合 母体比重測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
        //  if( KD51Data[i].SOKUTEI_NM > 2 && KD51Data[i].SOKUTE_KBN == 1 &&
        //      KD51Data[i].SOKUTEI_NB_CUR  ) {

             if( KD51Data[i].SOKUTE_KBN == 1 ) {
             
              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD51Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KD52 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD52にデータがありません");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {

                            //測定NO
                            if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             //厚さ寸法
                             if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                   KD51Data[i].SOKUTEI_S[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                             }

                             //幅（外径）寸法
                            if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                   KD51Data[i].SOKUTEI_H[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                             }

                             //2002.11.06 E.Takase
                             //長さ（外径）寸法
                             if ( Form1->Query1->FieldValues["SOKUHEI_N"].IsNull()) {
                                   KD51Data[i].SOKUTEI_N[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_N[n-1] =  Form1->Query1->FieldValues["SOKUHEI_N"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}
/***********************************************************************
*  function name : void KDC1_Serch03(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 曲げ強さﾃﾞｰﾀﾌｧｲﾙに指定した検査日とﾄﾚｰNOのﾁｪｯｸ KD71  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  KDC1_Serch03( void)
{
       int n;
       AnsiString strVal01;
       AnsiString strVal02;

        //検査値のの取得
        strVal01 = DelSEPA(Form1->edtymd->Text);

        n= Form1->edttlno->Value + 1;
        strVal02 = IntToStr(n);

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //問い合せ文実行
        //ソート昇順 ,検査予定日、トレーNo
        sBuf = "SELECT *  ";
        sBuf += "FROM KDC1 ";
        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof && Form1->Query1->Bof )
          return -1;
        else
          return 1;
}
/***********************************************************************
*  function name : void SetTable51(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD51Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable51()
{
     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD51Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     //検索予定日
     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD51Data[iRec].KENSA_YMD = " ";
     }else {
          KD51Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }
     //ﾄﾚｰNO
     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD51Data[iRec].TOLEY_NO = 0;
     }else {
          KD51Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     //測定区分
     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD51Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD51Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];
     }

     //形状区分
     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KD51Data[iRec].KEIJYO_KBN = 0;
     }else {
          KD51Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }

     // 厚さ寸法１、厚さ寸法２
     if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
          KD51Data[iRec].SOKUTEI_S[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
          KD51Data[iRec].SOKUTEI_S[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
     }

     //幅(外形)寸法１、幅（外形）寸法２
      if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
          KD51Data[iRec].SOKUTEI_H[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
          KD51Data[iRec].SOKUTEI_H[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
     }

     //コンミ対応 2002/11/02 E.Takase
     //長さ(外形)寸法１、長さ（外形）寸法２
      if ( Form1->Query1->FieldValues["SOKUTEI_1N"].IsNull()) {
          KD51Data[iRec].SOKUTEI_N[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_N[0] =  Form1->Query1->FieldValues["SOKUTEI_1N"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2N"].IsNull()) {
          KD51Data[iRec].SOKUTEI_N[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_N[1] =  Form1->Query1->FieldValues["SOKUTEI_2N"];
     }

     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD51Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD51Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }

     //登録日
     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD51Data[iRec].ADDYMD = " ";
          KD51Data[iRec].SOKUTEI_NB_CUR = 0;
     }else {
           KD51Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD51Data[iRec].ADDYMD ) ){
             KD51Data[iRec].SOKUTEI_NB_CUR = 0 ;
          }else{
             KD51Data[iRec].SOKUTEI_NB_CUR = KD51Data[iRec].SOKUTEI_NM ;
          }
     }
 }

/***********************************************************************
*  function name : void KD51Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗データ構造体KD51Dataを初期化  KD51  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD51Format(void)
{
   for( int i=0; i<30; i++){
      KD51Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD51Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD51Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD51Data[i].SOKUTE_KBN = 0;     //測定区分
      KD51Data[i].KEIJYO_KBN = 0;     //母体比重 形状区分
      KD51Data[i].SOKUTEI_NM = 0;    //母体比重 測定個数
      memset(KD51Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //厚さ寸法
      memset(KD51Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //幅寸法
      //コンミ対応 2002/11/02 E.Takase
      memset(KD51Data[i].SOKUTEI_N,(int)NULL, sizeof(double) * 100); ;  //長さ寸法
      KD51Data[i].ADDYMD = '\0';      //登録日
      KD51Data[i].SOKUTEI_NB_CUR = 0;
   }
}

/***********************************************************************
*  function name : void CopyKD51to81(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.05 コンミ対応 E.Takase                      *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙの厚さ、幅を KD８１へコピーする     *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void CopyKD51to81(void)
{
  int i, j;

  for( int i=0; i<30; i++){

      if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].SOKUTEI_NB_CUR ){

           // 形状区分４の場合
           if( KD51Data[i].KEIJYO_KBN == 4 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KDC1Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KDC1Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
           // 形状区分５の場合
          }else if( KD51Data[i].KEIJYO_KBN == 5 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KDC1Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_N[j] ;
               }
               KDC1Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          // 形状区分１、２、３の場合
          }else{
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KDC1Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_S[j] ;
                  KDC1Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KDC1Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
               KDC1Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          }


     }
   }
}



/***********************************************************************
*  function name : void KDC3W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : KDC3Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  KDC3W_Delete01(void)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //お問い合せ文  Update
    sprintf(str_c, " DELETE FROM KDC3W");

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
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
     catch(Exception& e)
     {
       // ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
 }
