/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１８）                  *
*  file   name   : U_TKS18_Data.cpp                                    *
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
int  Kd82_Serch02( AnsiString , int , int, int );
void Kd82_Update01( int );
void Kd82_Update02( AnsiString , int, int, int );
void Kd82_Insert01( AnsiString , int ,int, int );
void SetTable83W(int);

/***********************************************************************
*  function name : int  Kd81_Serch01(void)                             *
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
int Kd81_Serch01(void)
{

    // 抗折力ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD81.KENSA_YMD, KD81.TOLEY_NO ";
    sBuf += "FROM KD81 ";
    sBuf += "WHERE KD81.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD81.KENSA_YMD desc, KD81.TOLEY_NO";

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
*  function name : void Kd81_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 抗折力ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD81                  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd81_Serch02( void)
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
	    sBuf += "FROM KD81 ";
	    sBuf += "WHERE  KD81.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD81.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND  KD81.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD81.KENSA_YMD, KD81.TOLEY_NO, KD81.SAMPLE_P";
	    sBuf += "ORDER BY KD81.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->RecordCount <= 0 ) {
          // ShowMessage("KD81にデータがありません");
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
          if( KD81Data[i].SOKUTE_KBN  && KD81Data[i].SAMPLE_P != -1 ) {
             if( KD81Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD81Data[i].DTKSHIN == KD81Data[j].DTKSHIN)
                        KD81Data[j].LINK = KD81Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 抗折力測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
         // if( KD81Data[i].SOKUTEI_NM > 2 && KD81Data[i].SOKUTE_KBN == 1 &&
         //     KD81Data[i].SOKUTEI_NM_CUR > 0 ) {

             if(  KD81Data[i].SOKUTE_KBN == 1 ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD81Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KD82 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加 
	        //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD82にデータがありません");
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
                                   KD81Data[i].SOKUTEI_K[n-1] = 0.0;
                             }else {
                                   KD81Data[i].SOKUTEI_K[n-1] =  Form1->Query1->FieldValues["SOKUTEI_K"];
                             }
                             //ｽﾊﾟﾝ
                            if ( Form1->Query1->FieldValues["SOKUTEI_P"].IsNull()) {
                                   KD81Data[i].SOKUTEI_P[n-1] = 0.0;
                             }else {
                                   KD81Data[i].SOKUTEI_P[n-1] =  Form1->Query1->FieldValues["SOKUTEI_P"];
                             }

                             if( !iBotai ) {

                                 //厚さ寸法
                                 if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                      KD81Data[i].SOKUTEI_S[n-1] = 0.0;
                                 }else {
                                      KD81Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                                 }
                                 //幅寸法
                                if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                      KD81Data[i].SOKUTEI_H[n-1] = 0.0;
                                 }else {
                                     KD81Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                                 }
                                 //抗折力
                                if ( Form1->Query1->FieldValues["SOKUTEI_M"].IsNull()) {
                                     KD81Data[i].SOKUTEI_M[n-1] = 0.0;
                                }else {
                                     KD81Data[i].SOKUTEI_M[n-1] =  Form1->Query1->FieldValues["SOKUTEI_M"];
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
*  contents      : KD81Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable81()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD81Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD81Data[iRec].KENSA_YMD = " ";
     }else {
          KD81Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD81Data[iRec].TOLEY_NO = 0;
     }else {
          KD81Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD81Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD81Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 && KD81Data[iRec].SOKUTE_KBN == 1 ){
            HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KD81Data[iRec].KEIJYO_KBN = 0;
     }else {
          KD81Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }


     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD81Data[iRec].DTKSCOD = " ";
     }else {
          KD81Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD81Data[iRec].DTKSHIN = " ";
     }else {
          KD81Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD81Data[iRec].LOTNO = " ";
     }else {
          KD81Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD81Data[iRec].HINBAN = " ";
     }else {
          KD81Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD81Data[iRec].ZISCOD = " ";
     }else {
          KD81Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD81Data[iRec].ZISNAM = " ";
     }else {
          KD81Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["MAGE_MIN"].IsNull()) {
          KD81Data[iRec].MAGE_MIN = 0.0;
     }else {
          KD81Data[iRec].MAGE_MIN =  Form1->Query1->FieldValues["MAGE_MIN"];
     }

     if ( Form1->Query1->FieldValues["MAGE_MAX"].IsNull()) {
          KD81Data[iRec].MAGE_MAX = 0.0;
     }else {
          KD81Data[iRec].MAGE_MAX =  Form1->Query1->FieldValues["MAGE_MAX"];
     }

     if ( Form1->Query1->FieldValues["MAGE_SPAN"].IsNull()) {
          KD81Data[iRec].MAGE_SPAN = 0.0;
     }else {
          KD81Data[iRec].MAGE_SPAN =  Form1->Query1->FieldValues["MAGE_SPAN"];
     }

     if ( Form1->Query1->FieldValues["MAGE_TAN"].IsNull()) {
          KD81Data[iRec].MAGE_TAN = 0;
     }else {
          KD81Data[iRec].MAGE_TAN =  Form1->Query1->FieldValues["MAGE_TAN"];
     }

      //破壊荷重１、破壊荷重２
     if ( Form1->Query1->FieldValues["SOKUTEI_1K"].IsNull()) {
          KD81Data[iRec].SOKUTEI_K[0] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_K[0] =  Form1->Query1->FieldValues["SOKUTEI_1K"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2K"].IsNull()) {
          KD81Data[iRec].SOKUTEI_K[1] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_K[1] =  Form1->Query1->FieldValues["SOKUTEI_2K"];
     }
     //ｽﾊﾟﾝ１、ｽﾊﾟﾝ２
      if ( Form1->Query1->FieldValues["SOKUTEI_1P"].IsNull()) {
          KD81Data[iRec].SOKUTEI_P[0] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_P[0] =  Form1->Query1->FieldValues["SOKUTEI_1P"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2P"].IsNull()) {
          KD81Data[iRec].SOKUTEI_P[1] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_P[1] =  Form1->Query1->FieldValues["SOKUTEI_2P"];
     }

     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD81Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD81Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD81Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD81Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD81Data[iRec].ADDYMD = " ";
     }else {
          KD81Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];

     }

     if( IsNullSpace( KD81Data[iRec].ADDYMD )){
             KD81Data[iRec].SOKUTEI_NM_CUR = 0 ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
                 KD81Data[iRec].SOKUTEI_NS_CUR = 0;
                 KD81Data[iRec].SOKUTEI_NH_CUR = 0;
             }
             KD81Data[iRec].SOKUTEI_NK_CUR = 0;

             //指示スパンをﾜｰｸ変数へ保存
             for( int i=0; i< KD81Data[iRec].SOKUTEI_NM; i++ )
                   KD81Data[iRec].SOKUTEI_P[i] = KD81Data[iRec].MAGE_SPAN;

              KD81Data[iRec].SOKUTEI_NP_CUR = KD81Data[iRec].SOKUTEI_SU ;
     }else{
             KD81Data[iRec].SOKUTEI_NM_CUR = KD81Data[iRec].SOKUTEI_SU ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR){
                KD81Data[iRec].SOKUTEI_NS_CUR = KD81Data[iRec].SOKUTEI_SU ;
                KD81Data[iRec].SOKUTEI_NH_CUR = KD81Data[iRec].SOKUTEI_SU ;
             }
             KD81Data[iRec].SOKUTEI_NK_CUR = KD81Data[iRec].SOKUTEI_SU ;
             KD81Data[iRec].SOKUTEI_NP_CUR = KD81Data[iRec].SOKUTEI_SU ;
     }
     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD81Data[iRec].ADDTIM = " ";
     }else {
          KD81Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD81Data[iRec].UPDYMD = " ";
     }else {
          KD81Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD81Data[iRec].UPDCHR = 0;
     }else {
          KD81Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD81Data[iRec].UPDCNT = 0;
     }else {
          KD81Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD81Data[iRec].MEMO = " ";
     }else {
          KD81Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

     // 母体比重計測ﾃﾞｰﾀを使う場合
  //   if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
        if( ! iBotai ){

       // 厚さ寸法１、厚さ寸法２
       if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
          KD81Data[iRec].SOKUTEI_S[0] = 0.0;
        }else {
          KD81Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
             KD81Data[iRec].SOKUTEI_S[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
        }

        //幅寸法１、幅寸法２
         if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
             KD81Data[iRec].SOKUTEI_H[0] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
             KD81Data[iRec].SOKUTEI_H[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
        }

        //測定値１抗折力
         if ( Form1->Query1->FieldValues["SOKUTEI_1M"].IsNull()) {
              KD81Data[iRec].SOKUTEI_M[0] = 0.0;
         }else {
              KD81Data[iRec].SOKUTEI_M[0] =  Form1->Query1->FieldValues["SOKUTEI_1M"];
         }
         //測定値２ 抗折力
        if ( Form1->Query1->FieldValues["SOKUTEI_2M"].IsNull()) {
             KD81Data[iRec].SOKUTEI_M[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_M[1] =  Form1->Query1->FieldValues["SOKUTEI_2M"];
        }

        //測定値平均値（抗折力）
        if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
             KD81Data[iRec].SOKUTE_AVE = 0.0;
        }else {
             KD81Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
        }
        //備考 2002/11/07 E.Takase
        if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
             KD81Data[iRec].MEMO =  " ";
        }else {
             KD81Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
        }
     }else{

        // 固有抵抗率の再計算
          MForceCal(iRec+1,1 ) ;
          MForceCal(iRec+1,2 ) ;

          //平均値は使っていないので無視する
     }

 }

/***********************************************************************
*  function name : void KD81Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : リード線取付抵抗データ構造体KD81Dataを初期化  KD81  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD81Format(void)
{
   for( int i=0; i<30; i++){
      KD81Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD81Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD81Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD81Data[i].SOKUTE_KBN = 0;     //測定区分
      KD81Data[i].KEIJYO_KBN =0 ;     //形状区分
      KD81Data[i].DTKSCOD = '\0';     //得意先コード
      KD81Data[i].DTKSHIN = '\0';     //得意先品番
      KD81Data[i].LOTNO = '\0';       //ロットNO
      KD81Data[i].HINBAN = '\0';      //自社品番
      KD81Data[i].ZISCOD = '\0';      //材質コード
      KD81Data[i].ZISNAM = '\0';      //材質名

      KD81Data[i].MAGE_MAX = 0.0;    //曲げ強度 規格上
      KD81Data[i].MAGE_MIN = 0.0;    //曲げ強度 規格下
      KD81Data[i].MAGE_SPAN = 0.0;   //曲げ強度 測定ｽﾊﾟﾝ
      KD81Data[i].MAGE_TAN = 0;      //曲げ強度 単位
      KD81Data[i].SOKUTEI_NM = 0;    //曲げ強度 測定個数
      KD81Data[i].SOKUTEI_SU = 0;    //曲げ強度 測定個数
      KD81Data[i].SOKUTE_AVE = 0.0;  //曲げ強度 測定平均値

      memset(KD81Data[i].SOKUTEI_M,(int)NULL, sizeof(double) * 100); ;  //測定値
      memset(KD81Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //厚さ寸法
      memset(KD81Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //幅寸法
      memset(KD81Data[i].SOKUTEI_K,(int)NULL, sizeof(double) * 100); ;  //破壊荷重
      memset(KD81Data[i].SOKUTEI_P,(int)NULL, sizeof(double) * 100); ;  //ｽﾊﾟﾝ

      KD81Data[i].ADDYMD = '\0';      //登録日
      KD81Data[i].ADDTIM = '\0';      //登録時間
      KD81Data[i].UPDYMD = '\0';      //変更日
      KD81Data[i].UPDTIM = '\0';      //変更時間
      KD81Data[i].UPDCHR = 0;         //更新者
      KD81Data[i].UPDCNT = 0;         //更新回数
      KD81Data[i].LINK = 0;
      KD81Data[i].SOKUTEI_NM_CUR = 0;
      KD81Data[i].SOKUTEI_NS_CUR = 0;
      KD81Data[i].SOKUTEI_NH_CUR = 0;
      KD81Data[i].SOKUTEI_NK_CUR = 0;
      KD81Data[i].SOKUTEI_NP_CUR = 0;
      KD81Data[i].SOKUTEI_NP_CUR = 0;

      KD81Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void Kd81_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀを抗折力ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD81            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd81_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ1
             if( iKomoku==1)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_K[0] = pEdt1_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // 計測ﾃﾞｰﾀ2
             if( iKomoku==1)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_K[1] = pEdt2_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 2 );

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD81Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                 n = pEdt4_S[iKomoku-1]->Value;
                 if( n>=3 && n <= KD81Data[SamplePositionIdx-1].SOKUTEI_NM ) {

                    // 計測ﾃﾞｰﾀ2
                   if( iKomoku==1)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==2)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==3)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_K[n-1] = pEdt3_S[iKomoku-1]->Value;

                   MForceCal(SamplePositionIdx, n );
                 }
             }
    }


	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD81Data[i].SOKUTE_KBN == 1 && KD81Data[i].SAMPLE_P != -1 &&
				!( KD81Data[i].SOKUTEI_NM_CUR == 0 &&
				KD81Data[i].SOKUTEI_NS_CUR == 0 &&
				KD81Data[i].SOKUTEI_NH_CUR == 0 &&
				KD81Data[i].SOKUTEI_NK_CUR == 0 )  ){

			//担当者ｺｰﾄﾞ
			KD81Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KD81Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			//KD81Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD81Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD81Data[i].SOKUTEI_M[j] ;
			if( KD81Data[i].SOKUTEI_NM_CUR )
				KD81Data[i].SOKUTE_AVE = a/KD81Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD81Data[i].ADDYMD )){
				KD81Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD81Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD81Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD81Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD81Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD81Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD81 set SOKUTEI_SU=%d, SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KD81Data[i].SOKUTEI_NM_CUR,
								KD81Data[i].SOKUTEI_S[0],
								KD81Data[i].SOKUTEI_S[1],
								KD81Data[i].SOKUTEI_H[0],
								KD81Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			//2003.02.10 E.Takase sprintf(str_c, " SOKUTEI_1K=%6.1f , SOKUTEI_2K=%6.1f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
			sprintf(str_c, " SOKUTEI_1K=%6.2f , SOKUTEI_2K=%6.2f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
								KD81Data[i].SOKUTEI_K[0],
								KD81Data[i].SOKUTEI_K[1],
								KD81Data[i].SOKUTEI_P[0],
								KD81Data[i].SOKUTEI_P[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1M=%9.3f , SOKUTEI_2M=%9.3f, SOKUTE_AVE=%12.6f,",
								KD81Data[i].SOKUTEI_M[0],
								KD81Data[i].SOKUTEI_M[1],
								KD81Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD81Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD81Data[i].ADDYMD.c_str(),
									KD81Data[i].ADDTIM.c_str(),
									KD81Data[i].UPDCHR,
									KD81Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD81Data[i].UPDYMD.c_str(),
									KD81Data[i].UPDTIM.c_str(),
									KD81Data[i].UPDCHR,
									KD81Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD81Data[i].KENSA_YMD.c_str(),
			//					KD81Data[i].TOLEY_NO ,
			//					KD81Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD81Data[i].KENSA_YMD.c_str(),
						KD81Data[i].TOLEY_NO ,
						KD81Data[i].SAMPLE_P ,
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
			if( KD81Data[i].SOKUTEI_NM > 2 ){
				Kd82_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD81Data[i].ADDYMD )) || !(IsNullSpace(KD81Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD81Data[i].ADDYMD )){
					KD81Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD81Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD81Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD81Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD81Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD81Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD81 set MEMO='%s' , ", KD81Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD81Data[i].ADDYMD.c_str(),
										KD81Data[i].ADDTIM.c_str(),
										KD81Data[i].UPDCHR,
										KD81Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD81Data[i].UPDYMD.c_str(),
										KD81Data[i].UPDTIM.c_str(),
										KD81Data[i].UPDCHR,
										KD81Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD81Data[i].KENSA_YMD.c_str(),
				//					KD81Data[i].TOLEY_NO ,
				//					KD81Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD81Data[i].KENSA_YMD.c_str(),
						KD81Data[i].TOLEY_NO ,
						KD81Data[i].SAMPLE_P ,
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
*  function name : void Kd82_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀ(>2)を抗折力測定(例外）ﾌｧｲﾙへ書き込む  KD82 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD81Data[iRec].SOKUTEI_NM; i++ ){

         // KD82へ追加するレコード存在するかどうかのチェック
         iRtn = Kd82_Serch02( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn < 0 ) {
                Kd82_Insert01( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                Kd82_Update02( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
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
*  function name : int Kd82_Serch02(AnsiString sYmd, int iTlno,        *
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
int  Kd82_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD82 ";
        sBuf += "WHERE  KD82.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD82.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD82.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD82.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD82.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD82.KENSA_YMD, KD82.TOLEY_NO, KD82.SAMPLE_P, KD82.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd82_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD82へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD82 set SOKUTEI_S=%6.3f ,", KD81Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.3f ,", KD81Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, "SOKUTEI_K=%6.1f ,", KD81Data[iSp-1].SOKUTEI_K[iDtNo-1]);
    sprintf(str_c, "SOKUTEI_K=%6.2f ,", KD81Data[iSp-1].SOKUTEI_K[iDtNo-1]);

    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_P=%4.1f ,", KD81Data[iSp-1].SOKUTEI_P[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEI_M=%9.3f", KD81Data[iSp-1].SOKUTEI_M[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
                                sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );     // 20160630_工場区分追加

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
*  function name : void Kd82_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD82へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD82(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO,SOKUTEI_S,SOKUTEI_H, SOKUTEI_K,SOKUTEI_P, SOKUTEI_M, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.1f,%4.1f,%9.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    //20161201 Y.Onishi n数3以上の保存時バグの修正
    //sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%4.1f,%9.3f)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    	sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%4.1f,%9.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
                                                      KD81Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_K[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_P[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_M[iDtNo-1],
                                                      iKojoKbn);      // 20160630_工場区分追加

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
*  function name : void Kd83W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : 履歴作画のために KD83Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd83W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD83WFormat(void)                              *
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
void KD83WFormat(void)
{
   for( int i=0; i<30; i++){
       KD83WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD83WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KD83WData[i].MAGE_MAX[j] = 0.0  ;    //曲げ強度 規格上
            KD83WData[i].MAGE_MIN[j] = 0.0  ;    //曲げ強度 規格下
            KD83WData[i].SOKUTE_AVE[j] = 0.0;
            KD83WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD83WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD83WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd83W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD83Wﾜｰｸﾃｰﾌﾞﾙからリード線取付抵抗履歴データ抽出KD83W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd83W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD81Data[i].SOKUTE_KBN == 0 && KD81Data[i].SAMPLE_P == -1 ) continue ;
             if( KD81Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
             strVal01 = KD81Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD83W ";
	      sBuf += "WHERE  KD83W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD83W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD81にデータがありません");
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
                     KD83WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD83WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD83WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KD83WData[i].SOKUTEI[j][k] ;

               if( KD83WData[i].SOKUTEI_NM[j] !=0 )
                   KD83WData[i].SOKUTE_AVE[j] = dAve/KD83WData[i].SOKUTEI_NM[j] ;
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
*  contents      : ﾜｰｸﾃﾞｰﾀKD83WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable83W(int iSp)
{

     int iLotno = KD83WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD83WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD83WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD83WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["MAGE_MIN"].IsNull()) {
               KD83WData[iSp].MAGE_MIN[iLotno] = 0.0;
            }else {
                KD83WData[iSp].MAGE_MIN[iLotno] = Form1->Query1->FieldValues["MAGE_MIN"];
            }

            if ( Form1->Query1->FieldValues["MAGE_MAX"].IsNull()) {
               KD83WData[iSp].MAGE_MAX[iLotno] = 0.0;
            }else {
                KD83WData[iSp].MAGE_MAX[iLotno] = Form1->Query1->FieldValues["MAGE_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD83WData[iSp].DTKSHIN = " ";
     }else {
            KD83WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD83WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD83WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD83WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD83WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD83WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD81Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD81DataをKD81Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD81Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD81Data[i].SOKUTE_KBN == 0 || KD81Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD81Data[i].LINK == 0 ){
            iLinkSp = KD81Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD81Data[i].LINK;
        }

        if( KD83WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD83WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD83WData[iLinkSp-1].DTKSHIN =  KD81Data[i].DTKSHIN;

           //ロットNO
           KD83WData[iLinkSp-1].LOTNO[0]  = KD81Data[i].LOTNO ;

           // 規格下
           KD83WData[iLinkSp-1].MAGE_MIN[0] = KD81Data[i].MAGE_MIN;
           // 規格上
           KD83WData[iLinkSp-1].MAGE_MAX[0] = KD81Data[i].MAGE_MAX;

           KD83WData[iLinkSp-1].SOKUTEI_NM[0] = KD81Data[i].SOKUTEI_NM_CUR;

           if( KD81Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD81Data[i].SOKUTEI_NM; k++ ) {
                  KD83WData[iLinkSp-1].SOKUTEI[0][k] = KD81Data[i].SOKUTEI_M[k];
                  a += KD83WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD81Data[i].SOKUTEI_NM != 0 )
             KD83WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD81Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD83WData[iLinkSp-1].LOTCNT += 1;

          n = KD83WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD83WData[iLinkSp-1].LOTNO[n-1]  = KD81Data[i].LOTNO ;

          //リード線長さ 規格下
          KD83WData[iLinkSp-1].MAGE_MIN[n-1] = KD81Data[i].MAGE_MIN;

          //リード線長さ 規格上
          KD83WData[iLinkSp-1].MAGE_MAX[n-1] = KD81Data[i].MAGE_MAX;

          KD83WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD81Data[i].SOKUTEI_NM_CUR;

          if( KD81Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD81Data[i].SOKUTEI_NM; k++ ) {
               KD83WData[iLinkSp-1].SOKUTEI[n-1][k] = KD81Data[i].SOKUTEI_M[k];
               a += KD83WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD83WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD81Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd83w(void)                                 *
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
void  AddKd83W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD81Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD81Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD83WData[iLinkSp-1].LOTNO[iRtn] = KD81Data[SamplePositionIdx-1].LOTNO;

   //リード線長さ 規格下
    KD83WData[iLinkSp-1].MAGE_MIN[iRtn]= KD81Data[SamplePositionIdx-1].MAGE_MIN;

    //リード線長さ 規格上
    KD83WData[iLinkSp-1].MAGE_MAX[iRtn] = KD81Data[SamplePositionIdx-1].MAGE_MAX;

    KD83WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KD83WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD83WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD81Data[SamplePositionIdx-1].SOKUTEI_M[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD81Data[SamplePositionIdx-1].SOKUTEI_M[i];
   }

   dAve= dAve/KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD83WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

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
                sBuf += "AND  KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
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
*  function name : void Kd81_Serch03(void)                             *
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
int  Kd81_Serch03( void)
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
        sBuf += "FROM KD81 ";
        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加

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
                  KD81Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD81Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
           // 形状区分５の場合
          }else if( KD51Data[i].KEIJYO_KBN == 5 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD81Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_N[j] ;
               }
               KD81Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          // 形状区分１、２、３の場合
          }else{
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD81Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_S[j] ;
                  KD81Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD81Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
               KD81Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          }


     }
   }
}



/***********************************************************************
*  function name : void Kd83W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd83Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd83W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD83W");

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
