/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１３）                  *
*  file   name   : U_TKS13_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾘｰﾄﾞ線取付抵抗測定処理データアクセス関数            *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void KD31Format(void);
void SetTable11(void);
int  Kd32_Serch02( AnsiString , int , int, int );
void Kd32_Update01( int );
void Kd32_Update02( AnsiString , int, int, int );
void Kd32_Insert01( AnsiString , int ,int, int );
void SetTable33W(int);

/***********************************************************************
*  function name : int  Kd31_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd31_Serch01(void)
{

    //リード線取付抵抗ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD31.KENSA_YMD, KD31.TOLEY_NO ";
    sBuf += "FROM KD31 ";
	sBuf += "WHERE KD31.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD31.KENSA_YMD desc, KD31.TOLEY_NO";

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

   return 1 ;
 }


/***********************************************************************
*  function name : void Kd31_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : リード線取付抵抗ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD31        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd31_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

       // KD31Data構造体変数の初期化(「検索」ﾎﾞﾀﾝを押した場合)
       if( !Save_Click ) KD31Format();

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
	    sBuf += "FROM KD31 ";
	    sBuf += "WHERE  KD31.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD31.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND KD31.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD31.KENSA_YMD, KD31.TOLEY_NO, KD31.SAMPLE_P";
	    sBuf += "ORDER BY KD31.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD31にデータがありません");
          return -1;
        }else {

          // 「保存」ﾎﾞﾀﾝを押して次のﾄﾚｰNOを検索する場合
          if( Save_Click )
           {
               // ﾄﾚｰNOの設定
               Form1->edttlno->Text = strVal02 ;

               // KD31Data構造体変数の初期化
               KD31Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable11();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD31Data[i].SOKUTE_KBN  && KD31Data[i].SAMPLE_P != -1 ) {
             if( KD31Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD31Data[i].DTKSHIN == KD31Data[j].DTKSHIN)
                        KD31Data[j].LINK = KD31Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 リード線取付抵抗測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
         // if( KD31Data[i].SOKUTEI_NM > 2 && KD31Data[i].SOKUTE_KBN == 1 &&
         //     KD31Data[i].SOKUTEI_NM_CUR ) {

            if(  KD31Data[i].SOKUTE_KBN == 1 ) {
              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD31Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT ";
	        sBuf += " SOKUTEI_NO, SOKUTEI_V, SOKUTEI_A, SOKUTEICHI  ";
	        sBuf += "FROM KD32 ";
	        sBuf += "WHERE  KD32.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD32.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD32.SAMPLE_P = '" + strVal03 + "' ";
            sBuf += "AND KD32.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KD32.KENSA_YMD, KD32.TOLEY_NO, KD32.SAMPLE_P, KD32.SOKUTEI_NO";
	        sBuf += "ORDER BY KD32.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD32にデータがありません");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {

                             if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }
                             //電圧、電流、抵抗
                             if ( Form1->Query1->FieldValues["SOKUTEI_V"].IsNull()) {
                                   KD31Data[i].SOKUTEI_V[n-1] = 0.0;
                             }else {
                                   KD31Data[i].SOKUTEI_V[n-1] =  Form1->Query1->FieldValues["SOKUTEI_V"];
                             }
                             if ( Form1->Query1->FieldValues["SOKUTEI_A"].IsNull()) {
                                   KD31Data[i].SOKUTEI_A[n-1] = 0.0;
                             }else {
                                   KD31Data[i].SOKUTEI_A[n-1] =  Form1->Query1->FieldValues["SOKUTEI_A"];
                             }

                             if ( Form1->Query1->FieldValues["SOKUTEICHI"].IsNull()) {
                                   KD31Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD31Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable11(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : KD31Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable11()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD31Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD31Data[iRec].KENSA_YMD = " ";
     }else {
          KD31Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD31Data[iRec].TOLEY_NO = 0;
     }else {
          KD31Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD31Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD31Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];
          if( HaveSokutei == 0 &&KD31Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD31Data[iRec].DTKSCOD = " ";
     }else {
          KD31Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD31Data[iRec].DTKSHIN = " ";
     }else {
          KD31Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD31Data[iRec].LOTNO = " ";
     }else {
          KD31Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD31Data[iRec].HINBAN = " ";
     }else {
          KD31Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD31Data[iRec].ZISCOD = " ";
     }else {
          KD31Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD31Data[iRec].ZISNAM = " ";
     }else {
          KD31Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["LD_TR_MAX"].IsNull()) {
          KD31Data[iRec].LD_TR_MAX = 0.0;
     }else {
          KD31Data[iRec].LD_TR_MAX =  Form1->Query1->FieldValues["LD_TR_MAX"];
     }

     if ( Form1->Query1->FieldValues["LD_TR_DEN"].IsNull()) {
          KD31Data[iRec].LD_TR_DEN = 0.0;
     }else {
          KD31Data[iRec].LD_TR_DEN =  Form1->Query1->FieldValues["LD_TR_DEN"];
     }

     if ( Form1->Query1->FieldValues["LD_TR_TYPE"].IsNull()) {
          KD31Data[iRec].LD_TR_TYPE = " ";
     }else {
          KD31Data[iRec].LD_TR_TYPE =  Form1->Query1->FieldValues["LD_TR_TYPE"];
     }
     ////計測電流最大値.最小値
      KD31Data[iRec].D_Kikaku_Max = 1.1*KD31Data[iRec].LD_TR_DEN;
      KD31Data[iRec].D_Kikaku_Min = 0.9*KD31Data[iRec].LD_TR_DEN;


     if ( Form1->Query1->FieldValues["LD_TR_TIME"].IsNull()) {
          KD31Data[iRec].LD_TR_TIME = 0.0;
     }else {
          KD31Data[iRec].LD_TR_TIME =  Form1->Query1->FieldValues["LD_TR_TIME"];
     }

     //測定値１
      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD31Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     //測定値２
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD31Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     //電圧１、電圧２
      if ( Form1->Query1->FieldValues["SOKUTEI_1V"].IsNull()) {
          KD31Data[iRec].SOKUTEI_V[0] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEI_V[0] =  Form1->Query1->FieldValues["SOKUTEI_1V"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2V"].IsNull()) {
          KD31Data[iRec].SOKUTEI_V[1] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEI_V[1] =  Form1->Query1->FieldValues["SOKUTEI_2V"];
     }

     //電流１、電流２
      if ( Form1->Query1->FieldValues["SOKUTEI_1A"].IsNull()) {
          KD31Data[iRec].SOKUTEI_A[0] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEI_A[0] =  Form1->Query1->FieldValues["SOKUTEI_1A"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2A"].IsNull()) {
          KD31Data[iRec].SOKUTEI_A[1] = 0.0;
     }else {
          KD31Data[iRec].SOKUTEI_A[1] =  Form1->Query1->FieldValues["SOKUTEI_2A"];
     }
     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD31Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD31Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD31Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD31Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }
     //測定値平均値（抵抗）
     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD31Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD31Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD31Data[iRec].ADDYMD = " ";
          KD31Data[iRec].SOKUTEI_NM_CUR = 0;
          KD31Data[iRec].SOKUTEI_NA_CUR = 0;
     }else {
          KD31Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD31Data[iRec].ADDYMD )){
             KD31Data[iRec].SOKUTEI_NM_CUR = 0 ;
             KD31Data[iRec].SOKUTEI_NA_CUR = 0;
          }else{
             KD31Data[iRec].SOKUTEI_NM_CUR = KD31Data[iRec].SOKUTEI_SU ;
             KD31Data[iRec].SOKUTEI_NA_CUR = KD31Data[iRec].SOKUTEI_SU;
          }
     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD31Data[iRec].ADDTIM = " ";
     }else {
          KD31Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD31Data[iRec].UPDYMD = " ";
     }else {
          KD31Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD31Data[iRec].UPDCHR = 0;
     }else {
          KD31Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD31Data[iRec].UPDCNT = 0;
     }else {
          KD31Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }
     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD31Data[iRec].MEMO =  " ";
     }else {
          KD31Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
 }

/***********************************************************************
*  function name : void KD31Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : リード線取付抵抗データ構造体KD31Dataを初期化  KD31  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD31Format(void)
{
   for( int i=0; i<30; i++){
      KD31Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD31Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD31Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD31Data[i].SOKUTE_KBN = 0;     //測定区分
      KD31Data[i].DTKSCOD = '\0';     //得意先コード
      KD31Data[i].DTKSHIN = '\0';     //得意先品番
      KD31Data[i].LOTNO = '\0';       //ロットNO
      KD31Data[i].HINBAN = '\0';      //自社品番
      KD31Data[i].ZISCOD = '\0';      //材質コード
      KD31Data[i].ZISNAM = '\0';      //材質名
      KD31Data[i].LD_TR_MAX = 0.0;    //リード線取付抵抗 規格上
      KD31Data[i].LD_TR_DEN = 0.0;    //リード線取付抵抗 計測電流
      KD31Data[i].LD_TR_TIME = 0.0;    //リード線取付抵抗 計測時間
      KD31Data[i].LD_TR_TYPE = " \0";
      KD31Data[i].SOKUTEI_NM = 0;     //リード線取付抵抗測定個数
      KD31Data[i].SOKUTEI_SU = 0;     //リード線取付抵抗測定個数
      KD31Data[i].SOKUTE_AVE = 0.0;   //測定平均値
      memset(KD31Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //測定値
      memset(KD31Data[i].SOKUTEI_V,(int)NULL, sizeof(double) * 100); ;  //電圧
      memset(KD31Data[i].SOKUTEI_A,(int)NULL, sizeof(double) * 100); ;  //電流
      KD31Data[i].ADDYMD = '\0';      //登録日
      KD31Data[i].ADDTIM = '\0';      //登録時間
      KD31Data[i].UPDYMD = '\0';      //変更日
      KD31Data[i].UPDTIM = '\0';      //変更時間
      KD31Data[i].UPDCHR = 0;         //更新者
      KD31Data[i].UPDCNT = 0;         //更新回数
      KD31Data[i].D_Kikaku_Max = 0.0; //計測電流最大値
      KD31Data[i].D_Kikaku_Min = 0.0; //計測電流最小値
      KD31Data[i].LINK = 0;
      KD31Data[i].SOKUTEI_NM_CUR = 0;
      KD31Data[i].SOKUTEI_NA_CUR = 0;
      KD31Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase
   }
}

/***********************************************************************
*  function name : void Kd31_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀをリード線取付抵抗ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD31  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd31_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){
              // 計測ﾃﾞｰﾀ1
             KD31Data[SamplePositionIdx-1].SOKUTEI_V[0] = Form1->EdtV1->Value;
             KD31Data[SamplePositionIdx-1].SOKUTEI_A[0] = Form1->EdtA1->Value;
             KD31Data[SamplePositionIdx-1].SOKUTEICHI[0]= Form1->EdtV1->Value;

    }else if( DataNoIdx == 2 ){

             // 計測ﾃﾞｰﾀ2
             KD31Data[SamplePositionIdx-1].SOKUTEI_V[1] = Form1->EdtV2->Value;
             KD31Data[SamplePositionIdx-1].SOKUTEI_A[1] = Form1->EdtA2->Value;
             KD31Data[SamplePositionIdx-1].SOKUTEICHI[1]= Form1->EdtV2->Value;

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD31Data[SamplePositionIdx-1].SOKUTEI_NM > 2){
                 n = pEdt4[SamplePositionIdx-1]->Value;

                 if( n >=3 && n<= KD31Data[SamplePositionIdx-1].SOKUTEI_NM ){
                     KD31Data[SamplePositionIdx-1].SOKUTEI_V[n-1] = Form1->EdtV3->Value;
                     KD31Data[SamplePositionIdx-1].SOKUTEI_A[n-1] = Form1->EdtA3->Value;
                     KD31Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = Form1->EdtV3->Value;
                 }
             }
    }


	for( i=0; i<30; i++ ){
		iToroku = 1;

		if( KD31Data[i].SOKUTE_KBN == 1 && KD31Data[i].SAMPLE_P != -1 &&
			KD31Data[i].SOKUTEI_NM_CUR != 0 ){

			//担当者ｺｰﾄﾞ
			KD31Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KD31Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			// KD31Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD31Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD31Data[i].SOKUTEICHI[j] ;
			if( KD31Data[i].SOKUTEI_NM_CUR )
				KD31Data[i].SOKUTE_AVE = a/KD31Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD31Data[i].ADDYMD )){
				KD31Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD31Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD31Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD31Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD31Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD31Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD31 set SOKUTEI_SU=%d , SOKUTEI_1V=%6.1f , SOKUTEI_2V=%6.1f, SOKUTEI_1A=%6.1f , SOKUTEI_2A=%6.1f ,",
								KD31Data[i].SOKUTEI_NM_CUR,
								KD31Data[i].SOKUTEI_V[0],
								KD31Data[i].SOKUTEI_V[1],
								KD31Data[i].SOKUTEI_A[0],
								KD31Data[i].SOKUTEI_A[1]);
			str = str_c ;
			str_c[0] = NULL ;


			sprintf(str_c, " SOKUTEI_1=%6.1f , SOKUTEI_2=%6.1f, SOKUTE_AVE=%9.4f,",
								KD31Data[i].SOKUTEICHI[0],
								KD31Data[i].SOKUTEICHI[1],
								KD31Data[i].SOKUTE_AVE);


			str += str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD31Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD31Data[i].ADDYMD.c_str(),
									KD31Data[i].ADDTIM.c_str(),
									KD31Data[i].UPDCHR,
									KD31Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD31Data[i].UPDYMD.c_str(),
									KD31Data[i].UPDTIM.c_str(),
									KD31Data[i].UPDCHR,
									KD31Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD31Data[i].KENSA_YMD.c_str(),
			//					KD31Data[i].TOLEY_NO ,
			//					KD31Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD31Data[i].KENSA_YMD.c_str(),
						KD31Data[i].TOLEY_NO ,
						KD31Data[i].SAMPLE_P ,
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

			//リード線取付抵抗測定（例外）ﾌｧｲﾙの更新
			if( KD31Data[i].SOKUTEI_NM > 2 ){
			Kd32_Update01(i) ;
			}

		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD31Data[i].ADDYMD )) || !(IsNullSpace(KD31Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD31Data[i].ADDYMD )){
					KD31Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD31Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD31Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD31Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD31Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD31Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD31 set MEMO='%s' , ", KD31Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD31Data[i].ADDYMD.c_str(),
										KD31Data[i].ADDTIM.c_str(),
										KD31Data[i].UPDCHR,
										KD31Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD31Data[i].UPDYMD.c_str(),
										KD31Data[i].UPDTIM.c_str(),
										KD31Data[i].UPDCHR,
										KD31Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD31Data[i].KENSA_YMD.c_str(),
				//					KD31Data[i].TOLEY_NO ,
				//					KD31Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD31Data[i].KENSA_YMD.c_str(),
						KD31Data[i].TOLEY_NO ,
						KD31Data[i].SAMPLE_P ,
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
*  function name : void Kd32_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀをリード線取付抵抗(例外）ﾌｧｲﾙへ書き込む KD32*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd32_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD31Data[iRec].SOKUTEI_NM; i++ ){

         // KD32へ追加するレコード存在するかどうかのチェック
         iRtn = Kd32_Serch02( KD31Data[iRec].KENSA_YMD,
                          KD31Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn <= 0 ) {
                Kd32_Insert01( KD31Data[iRec].KENSA_YMD,
                          KD31Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                Kd32_Update02( KD31Data[iRec].KENSA_YMD,
                          KD31Data[iRec].TOLEY_NO,
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
*  function name : int Kd32_Serch02(AnsiString sYmd, int iTlno,        *
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
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : 指定したﾚｺｰﾄﾞをﾘｰﾄﾞ線取付抵抗例外ﾌｧｲﾙにあるかどうか *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd32_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD32 ";
        sBuf += "WHERE  KD32.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD32.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD32.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD32.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD32.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD32.KENSA_YMD, KD32.TOLEY_NO, KD32.SAMPLE_P, KD32.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof )
          return 0 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd32_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD32へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd32_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD32 set SOKUTEI_V=%.1f ,", KD31Data[iSp-1].SOKUTEI_V[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_A=%.1f ,", KD31Data[iSp-1].SOKUTEI_A[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEICHI=%.1f", KD31Data[iSp-1].SOKUTEICHI[iDtNo-1]);
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
*  function name : void Kd32_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD32へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd32_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD32(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO,SOKUTEI_V,SOKUTEI_A, SOKUTEICHI, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%.1f,%.1f,%.1f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
                                                      KD31Data[iSp-1].SOKUTEI_V[iDtNo-1],
                                                      KD31Data[iSp-1].SOKUTEI_A[iDtNo-1],
                                                      KD31Data[iSp-1].SOKUTEICHI[iDtNo-1],
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
*  function name : void Kd33W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : 履歴作画のために KD33Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd33W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD33WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗履歴ﾜｰｸﾃﾞｰﾀ構造体KD33dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD33WFormat(void)
{
   for( int i=0; i<30; i++){
       KD33WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD33WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KD33WData[i].LD_TR_MAX[j] = 0.0  ;   //リード線取付抵抗 規格上
            KD33WData[i].SOKUTE_AVE[j] = 0.0;
            KD33WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD33WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD33WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd33W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD33Wﾜｰｸﾃｰﾌﾞﾙからリード線取付抵抗履歴データ抽出KD33W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd33W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD31Data構造体変数の初期化
        KD33WFormat();

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD31Data[i].SOKUTE_KBN == 0 && KD31Data[i].SAMPLE_P == -1 ) continue ;
             if( KD31Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
             strVal01 = KD31Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD33W ";
	      sBuf += "WHERE  KD33W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD33W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
              sBuf += "ORDER BY ROWNO desc" ;

              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();

              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD31にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable33W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD33WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD33WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD33WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KD33WData[i].SOKUTEI[j][k] ;

               if( KD33WData[i].SOKUTEI_NM[j] !=0 )
                   KD33WData[i].SOKUTE_AVE[j] = dAve/KD33WData[i].SOKUTEI_NM[j] ;
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable33W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD33WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable33W(int iSp)
{

     int iLotno = KD33WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD33WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD33WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD33WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["LD_TR_MAX"].IsNull()) {
               KD33WData[iSp].LD_TR_MAX[iLotno] = 0.0;
            }else {
                KD33WData[iSp].LD_TR_MAX[iLotno] = Form1->Query1->FieldValues["LD_TR_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD33WData[iSp].DTKSHIN = " ";
     }else {
            KD33WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD33WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD33WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD33WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD33WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD33WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD31Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD31DataをKD31Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD31Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD31Data[i].SOKUTE_KBN == 0 || KD31Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD31Data[i].LINK == 0 ){
            iLinkSp = KD31Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD31Data[i].LINK;
        }

        if( KD33WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD33WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD33WData[iLinkSp-1].DTKSHIN =  KD31Data[i].DTKSHIN;

           //ロットNO
           KD33WData[iLinkSp-1].LOTNO[0]  = KD31Data[i].LOTNO ;

           // 規格上
           KD33WData[iLinkSp-1].LD_TR_MAX[0] = KD31Data[i].LD_TR_MAX;

           KD33WData[iLinkSp-1].SOKUTEI_NM[0] = KD31Data[i].SOKUTEI_NM_CUR;

           if( KD31Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD31Data[i].SOKUTEI_NM; k++ ) {
                  KD33WData[iLinkSp-1].SOKUTEI[0][k] = KD31Data[i].SOKUTEICHI[k];
                  a += KD33WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD31Data[i].SOKUTEI_NM != 0 )
             KD33WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD31Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD33WData[iLinkSp-1].LOTCNT += 1;

          n = KD33WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD33WData[iLinkSp-1].LOTNO[n-1]  = KD31Data[i].LOTNO ;

          //リード線長さ 規格上
          KD33WData[iLinkSp-1].LD_TR_MAX[n-1] = KD31Data[i].LD_TR_MAX;

          KD33WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD31Data[i].SOKUTEI_NM_CUR;

          if( KD31Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD31Data[i].SOKUTEI_NM; k++ ) {
               KD33WData[iLinkSp-1].SOKUTEI[n-1][k] = KD31Data[i].SOKUTEICHI[k];
               a += KD33WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD33WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD31Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd33w(void)                                 *
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
void  AddKd33W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD31Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD31Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD31Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD33WData[iLinkSp-1].LOTNO[iRtn] = KD31Data[SamplePositionIdx-1].LOTNO;

    //リード線長さ 規格上
    KD33WData[iLinkSp-1].LD_TR_MAX[iRtn] = KD31Data[SamplePositionIdx-1].LD_TR_MAX;

    KD33WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD31Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KD33WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD33WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD31Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD31Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD31Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD31Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD33WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}


/***********************************************************************
*  function name : void Kd33W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd33Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd33W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD33W");

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

