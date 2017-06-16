/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１７）                  *
*  file   name   : U_TKS18_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率測定処理データアクセス関数                *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void SetTable71(void);
int  Kd72_Serch02( AnsiString , int , int, int );
void Kd72_Update01( int );
void Kd72_Update02( AnsiString , int, int, int );
void Kd72_Insert01( AnsiString , int ,int, int );
void SetTable73W(int);
extern void WriteLog2(AnsiString);		// 2004/08/30 A.Tamura ログ出力

/***********************************************************************
*  function name : int  Kd71_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd71_Serch01(void)
{

    // 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD71.KENSA_YMD, KD71.TOLEY_NO ";
    sBuf += "FROM KD71 ";
    sBuf += "WHERE KD71.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD71.KENSA_YMD desc, KD71.TOLEY_NO";

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
*  function name : void Kd71_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD71              *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd71_Serch02( void)
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
	    sBuf += "FROM KD71 ";
	    sBuf += "WHERE  KD71.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD71.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND KD71.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD71.KENSA_YMD, KD71.TOLEY_NO, KD71.SAMPLE_P";
	    sBuf += "ORDER BY KD71.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD71にデータがありません");
          return -1;
        }else {

            // ﾄﾚｰNOの設定
           if( Save_Click )
               Form1->edttlno->Text = strVal02 ;

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable71();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD71Data[i].SOKUTE_KBN  && KD71Data[i].SAMPLE_P != -1 ) {
             if( KD71Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD71Data[i].DTKSHIN == KD71Data[j].DTKSHIN)
                        KD71Data[j].LINK = KD71Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 固有抵抗率測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
         // if( KD71Data[i].SOKUTEI_NM > 2 && KD71Data[i].SOKUTE_KBN == 1 &&
         //     KD71Data[i].SOKUTEI_NT_CUR > 0 ) {

             if( KD71Data[i].SOKUTE_KBN == 1 ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD71Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KD72 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD72にデータがありません");
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

                              //電圧 右左
                             if ( Form1->Query1->FieldValues["SOKUTEV_R"].IsNull()) {
                                   KD71Data[i].SOKUTEV_R[n-1] = 0.0;
                             }else {
                                   KD71Data[i].SOKUTEV_R[n-1] =  Form1->Query1->FieldValues["SOKUTEV_R"];
                             }
                             if ( Form1->Query1->FieldValues["SOKUTEV_L"].IsNull()) {
                                   KD71Data[i].SOKUTEV_L[n-1] = 0.0;
                             }else {
                                   KD71Data[i].SOKUTEV_L[n-1] =  Form1->Query1->FieldValues["SOKUTEV_L"];
                             }

                             //電流 右左
                             if ( Form1->Query1->FieldValues["SOKUTEA_R"].IsNull()) {
                                   KD71Data[i].SOKUTEA_R[n-1] = 0.0;
                             }else {
                                   KD71Data[i].SOKUTEA_R[n-1] =  Form1->Query1->FieldValues["SOKUTEA_R"];
                             }
                             if ( Form1->Query1->FieldValues["SOKUTEA_L"].IsNull()) {
                                   KD71Data[i].SOKUTEA_L[n-1] = 0.0;
                             }else {
                                   KD71Data[i].SOKUTEA_L[n-1] =  Form1->Query1->FieldValues["SOKUTEA_L"];
                             }

                             //プローブ
                            if ( Form1->Query1->FieldValues["SOKUTEI_P"].IsNull()) {
                                   KD71Data[i].SOKUTEI_P[n-1] = 0.0;
                             }else {
                                   KD71Data[i].SOKUTEI_P[n-1] =  Form1->Query1->FieldValues["SOKUTEI_P"];
                             }

                             if( !iBotai ) {
                                  //厚さ寸法
                                  if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                       KD71Data[i].SOKUTEI_S[n-1] = 0.0;
                                  }else {
                                       KD71Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                                  }
                                  //幅寸法
                                 if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                       KD71Data[i].SOKUTEI_H[n-1] = 0.0;
                                 }else {
                                       KD71Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                                 }

                                //固有抵抗率
                                if ( Form1->Query1->FieldValues["SOKUTEI_T"].IsNull()) {
                                     KD71Data[i].SOKUTEI_T[n-1] = 0.0;
                                }else {
                                     KD71Data[i].SOKUTEI_T[n-1] =  Form1->Query1->FieldValues["SOKUTEI_T"];
                                }

                             }else{

                                // 固有抵抗率の再計算
                                 KTeikouCal(i+1,n ) ;
                             }


                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}
/***********************************************************************
*  function name : void Kd71_Serch03(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙに指定した検査日とﾄﾚｰNOのﾁｪｯｸ KD71*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd71_Serch03( void)
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
        sBuf += "FROM KD71 ";
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
*  function name : void SetTable71(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : KD71Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable71()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD71Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD71Data[iRec].KENSA_YMD = " ";
     }else {
          KD71Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD71Data[iRec].TOLEY_NO = 0;
     }else {
          KD71Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD71Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD71Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 && KD71Data[iRec].SOKUTE_KBN == 1 ){
            HaveSokutei = 1;
          }
     }
     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KD71Data[iRec].KEIJYO_KBN = 0;
     }else {
         KD71Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }
     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD71Data[iRec].DTKSCOD = " ";
     }else {
          KD71Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD71Data[iRec].DTKSHIN = " ";
     }else {
          KD71Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD71Data[iRec].LOTNO = " ";
     }else {
          KD71Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD71Data[iRec].HINBAN = " ";
     }else {
          KD71Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD71Data[iRec].ZISCOD = " ";
     }else {
          KD71Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD71Data[iRec].ZISNAM = " ";
     }else {
          KD71Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["KOYU_MIN"].IsNull()) {
          KD71Data[iRec].KOYU_MIN = 0.0;
     }else {
          KD71Data[iRec].KOYU_MIN =  Form1->Query1->FieldValues["KOYU_MIN"];
     }

     if ( Form1->Query1->FieldValues["KOYU_MAX"].IsNull()) {
          KD71Data[iRec].KOYU_MAX = 0.0;
     }else {
          KD71Data[iRec].KOYU_MAX =  Form1->Query1->FieldValues["KOYU_MAX"];
     }

     if ( Form1->Query1->FieldValues["KOYU_DEN"].IsNull()) {
          KD71Data[iRec].KOYU_DEN = 0.0;
     }else {
          KD71Data[iRec].KOYU_DEN =  Form1->Query1->FieldValues["KOYU_DEN"];
     }

      //計測電流最大値.最小値
      KD71Data[iRec].D_Kikaku_Max = 1.1*KD71Data[iRec].KOYU_DEN;
      KD71Data[iRec].D_Kikaku_Min = 0.9*KD71Data[iRec].KOYU_DEN;

     if ( Form1->Query1->FieldValues["KOYU_PRO"].IsNull()) {
          KD71Data[iRec].KOYU_PRO = 0;
     }else {
          KD71Data[iRec].KOYU_PRO =  Form1->Query1->FieldValues["KOYU_PRO"];
     }

      //電圧右１、２
     if ( Form1->Query1->FieldValues["SOKUTEV_1R"].IsNull()) {
          KD71Data[iRec].SOKUTEV_R[0] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEV_R[0] =  Form1->Query1->FieldValues["SOKUTEV_1R"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEV_2R"].IsNull()) {
          KD71Data[iRec].SOKUTEV_R[1] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEV_R[1] =  Form1->Query1->FieldValues["SOKUTEV_2R"];
     }

      //電圧左１、２
     if ( Form1->Query1->FieldValues["SOKUTEV_1L"].IsNull()) {
          KD71Data[iRec].SOKUTEV_L[0] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEV_L[0] =  Form1->Query1->FieldValues["SOKUTEV_1L"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEV_2L"].IsNull()) {
          KD71Data[iRec].SOKUTEV_L[1] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEV_L[1] =  Form1->Query1->FieldValues["SOKUTEV_2L"];
     }
      //電流右１、２
     if ( Form1->Query1->FieldValues["SOKUTEA_1R"].IsNull()) {
          KD71Data[iRec].SOKUTEA_R[0] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEA_R[0] =  Form1->Query1->FieldValues["SOKUTEA_1R"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEA_2R"].IsNull()) {
          KD71Data[iRec].SOKUTEA_R[1] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEA_R[1] =  Form1->Query1->FieldValues["SOKUTEA_2R"];
     }

      //電流左１、２
     if ( Form1->Query1->FieldValues["SOKUTEA_1L"].IsNull()) {
          KD71Data[iRec].SOKUTEA_L[0] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEA_L[0] =  Form1->Query1->FieldValues["SOKUTEA_1L"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEA_2L"].IsNull()) {
          KD71Data[iRec].SOKUTEA_L[1] = 0.0;
     }else {
          KD71Data[iRec].SOKUTEA_L[1] =  Form1->Query1->FieldValues["SOKUTEA_2L"];
     }

     //プローブ１、２
      if ( Form1->Query1->FieldValues["SOKUTEI_1P"].IsNull()) {
          KD71Data[iRec].SOKUTEI_P[0] = 0;
     }else {
          KD71Data[iRec].SOKUTEI_P[0] =  Form1->Query1->FieldValues["SOKUTEI_1P"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2P"].IsNull()) {
          KD71Data[iRec].SOKUTEI_P[1] = 0;
     }else {
          KD71Data[iRec].SOKUTEI_P[1] =  Form1->Query1->FieldValues["SOKUTEI_2P"];
     }

     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD71Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD71Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
    if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD71Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD71Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
         KD71Data[iRec].ADDYMD = " ";
     }else {
          KD71Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
     }

          if( IsNullSpace( KD71Data[iRec].ADDYMD )){
              KD71Data[iRec].SOKUTEI_NT_CUR = 0;
              if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){

                 KD71Data[iRec].SOKUTEI_NS_CUR = 0;
                 KD71Data[iRec].SOKUTEI_NH_CUR = 0;
              }
              KD71Data[iRec].SOKUTEI_NVL_CUR = 0;
              KD71Data[iRec].SOKUTEI_NAL_CUR = 0;
              KD71Data[iRec].SOKUTEI_NVR_CUR = 0;
              KD71Data[iRec].SOKUTEI_NAR_CUR = 0;

              //指示ﾌﾟﾛｰﾌﾞをﾜｰｸ変数へ設定
              for( int i=0; i< KD71Data[iRec].SOKUTEI_NM; i++ )
                   KD71Data[iRec].SOKUTEI_P[i] =  KD71Data[iRec].KOYU_PRO ;

              KD71Data[iRec].SOKUTEI_NP_CUR = KD71Data[iRec].SOKUTEI_SU;

          }else{
              KD71Data[iRec].SOKUTEI_NT_CUR = KD71Data[iRec].SOKUTEI_SU;
              if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR){
                KD71Data[iRec].SOKUTEI_NS_CUR = KD71Data[iRec].SOKUTEI_SU;
                KD71Data[iRec].SOKUTEI_NH_CUR = KD71Data[iRec].SOKUTEI_SU;
              }
              KD71Data[iRec].SOKUTEI_NVL_CUR = KD71Data[iRec].SOKUTEI_SU;
              KD71Data[iRec].SOKUTEI_NAL_CUR = KD71Data[iRec].SOKUTEI_SU;
              KD71Data[iRec].SOKUTEI_NVR_CUR = KD71Data[iRec].SOKUTEI_SU;
              KD71Data[iRec].SOKUTEI_NAR_CUR = KD71Data[iRec].SOKUTEI_SU;
              KD71Data[iRec].SOKUTEI_NP_CUR = KD71Data[iRec].SOKUTEI_SU;

          }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD71Data[iRec].ADDTIM = " ";
     }else {
          KD71Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD71Data[iRec].UPDYMD = " ";
     }else {
          KD71Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD71Data[iRec].UPDCHR = 0;
     }else {
          KD71Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD71Data[iRec].UPDCNT = 0;
     }else {
          KD71Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
         KD71Data[iRec].MEMO =  " ";
     }else {
         KD71Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
     
     // 母体比重計測ﾃﾞｰﾀを使う場合
   //  if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
     if(  iBotai == 0 ){
          // 厚さ寸法１、厚さ寸法２
         if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
             KD71Data[iRec].SOKUTEI_S[0] = 0.0;
          }else {
             KD71Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
          }
          if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
             KD71Data[iRec].SOKUTEI_S[1] = 0.0;
          }else {
             KD71Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
          }

         //幅寸法１、幅寸法２
         if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
              KD71Data[iRec].SOKUTEI_H[0] = 0.0;
         }else {
              KD71Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
         }
        if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
              KD71Data[iRec].SOKUTEI_H[1] = 0.0;
        }else {
              KD71Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
        }

         //測定値１固有抵抗率
         if ( Form1->Query1->FieldValues["SOKUTEI_1T"].IsNull()) {
             KD71Data[iRec].SOKUTEI_T[0] = 0;
         }else {
             KD71Data[iRec].SOKUTEI_T[0] =  Form1->Query1->FieldValues["SOKUTEI_1T"];
         }
         //測定値２ 固有抵抗率
         if ( Form1->Query1->FieldValues["SOKUTEI_2T"].IsNull()) {
             KD71Data[iRec].SOKUTEI_T[1] = 0;
         }else {
             KD71Data[iRec].SOKUTEI_T[1] =  Form1->Query1->FieldValues["SOKUTEI_2T"];
         }

         //測定値平均値（固有抵抗率）
         if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
              KD71Data[iRec].SOKUTE_AVE = 0.0;
         }else {
              KD71Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
         }


     }else{

         // 固有抵抗率の再計算
          KTeikouCal(iRec+1,1 ) ;
          KTeikouCal(iRec+1,2 ) ;

          //平均値は使っていないので無視する
     }

 }

/***********************************************************************
*  function name : void KD71Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : リード線取付抵抗データ構造体KD71Dataを初期化  KD71  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD71Format(void)
{
   for( int i=0; i<30; i++){
      KD71Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD71Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD71Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD71Data[i].SOKUTE_KBN = 0;     //測定区分
      KD71Data[i].KEIJYO_KBN = 0;     //形状区分
      KD71Data[i].DTKSCOD = '\0';     //得意先コード
      KD71Data[i].DTKSHIN = '\0';     //得意先品番
      KD71Data[i].LOTNO = '\0';       //ロットNO
      KD71Data[i].HINBAN = '\0';      //自社品番
      KD71Data[i].ZISCOD = '\0';      //材質コード
      KD71Data[i].ZISNAM = '\0';      //材質名

      KD71Data[i].KOYU_MAX = 0.0;    //固有抵抗率 規格上
      KD71Data[i].KOYU_MIN = 0.0;    //固有抵抗率 規格下
      KD71Data[i].KOYU_DEN = 0.0;    //固有抵抗率 測定電流
      KD71Data[i].KOYU_PRO = 0 ;     //固有抵抗率 プローブ
      KD71Data[i].SOKUTEI_NM = 0;    //固有抵抗率 測定個数
      KD71Data[i].SOKUTEI_SU = 0;    //固有抵抗率 測定個数
      KD71Data[i].SOKUTE_AVE = 0.0;  //固有抵抗率 測定平均値

      memset(KD71Data[i].SOKUTEI_T,(int)NULL, sizeof(int) * 100); ;     //測定値
      memset(KD71Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //厚さ寸法
      memset(KD71Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //幅寸法
      memset(KD71Data[i].SOKUTEV_R,(int)NULL, sizeof(double) * 100); ;  //電圧
      memset(KD71Data[i].SOKUTEV_L,(int)NULL, sizeof(double) * 100); ;  //電圧
      memset(KD71Data[i].SOKUTEA_R,(int)NULL, sizeof(double) * 100); ;  //電流
      memset(KD71Data[i].SOKUTEA_L,(int)NULL, sizeof(double) * 100); ;  //電流
      memset(KD71Data[i].SOKUTEI_P,(int)NULL, sizeof(int) * 100); ;     //プローブ

      KD71Data[i].ADDYMD = '\0';      //登録日
      KD71Data[i].ADDTIM = '\0';      //登録時間
      KD71Data[i].UPDYMD = '\0';      //変更日
      KD71Data[i].UPDTIM = '\0';      //変更時間
      KD71Data[i].UPDCHR = 0;         //更新者
      KD71Data[i].UPDCNT = 0;         //更新回数
      KD71Data[i].LINK = 0;
      KD71Data[i].SOKUTEI_NT_CUR = 0;
      KD71Data[i].SOKUTEI_NS_CUR = 0;
      KD71Data[i].SOKUTEI_NH_CUR = 0;
      KD71Data[i].SOKUTEI_NVL_CUR = 0;
      KD71Data[i].SOKUTEI_NAL_CUR = 0;
      KD71Data[i].SOKUTEI_NVR_CUR = 0;
      KD71Data[i].SOKUTEI_NAR_CUR = 0;
      KD71Data[i].SOKUTEI_NP_CUR = 0;
      KD71Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void Kd71_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀを固有抵抗率ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD71        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd71_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得( Exit Event発生しない場合)
    if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ1
             if( iKomoku==1)
                 KD71Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD71Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3 || iKomoku == 4){
                 KD71Data[SamplePositionIdx-1].SOKUTEV_L[0] = pEdt1_V[0]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_L[0] = pEdt1_A[0]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEV_R[0] = pEdt1_V[1]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_R[0] = pEdt1_A[1]->Value;
             }
             KTeikouCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // 計測ﾃﾞｰﾀ2
             if( iKomoku==1)
                 KD71Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD71Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3 || iKomoku == 4){
                 KD71Data[SamplePositionIdx-1].SOKUTEV_L[1] = pEdt2_V[0]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_L[1] = pEdt2_A[0]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEV_R[1] = pEdt2_V[1]->Value;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_R[1] = pEdt2_A[1]->Value;
             }
             KTeikouCal(SamplePositionIdx, 2 );

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                n = pEdt4_S[iKomoku-1]->Value;

                if( n>=3 && n <= KD71Data[SamplePositionIdx-1].SOKUTEI_NM ) {

                   // 計測ﾃﾞｰﾀ2
                   if( iKomoku==1)
                      KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==2)
                      KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==3 || iKomoku == 4){
                      KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] = pEdt3_V[0]->Value;
                      KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] = pEdt3_A[0]->Value;
                      KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] = pEdt3_V[1]->Value;
                      KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] = pEdt3_A[1]->Value;
                   }
                  KTeikouCal(SamplePositionIdx, n );
               }
             }
    }

	for( i=0; i<30; i++ ){

	iToroku = 1;

		if( KD71Data[i].SOKUTE_KBN == 1 && KD71Data[i].SAMPLE_P != -1 &&
			!( KD71Data[i].SOKUTEI_NT_CUR == 0 &&
			KD71Data[i].SOKUTEI_NS_CUR == 0 &&
			KD71Data[i].SOKUTEI_NH_CUR == 0 &&
			KD71Data[i].SOKUTEI_NVL_CUR == 0 &&
			KD71Data[i].SOKUTEI_NAL_CUR == 0 &&
			KD71Data[i].SOKUTEI_NVR_CUR == 0 &&
			KD71Data[i].SOKUTEI_NAR_CUR == 0     )){

			//担当者ｺｰﾄﾞ
			KD71Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KD71Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			//KD71Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD71Data[i].SOKUTEI_NT_CUR; j++ )
				a += KD71Data[i].SOKUTEI_T[j] ;
			if( KD71Data[i].SOKUTEI_NT_CUR )
				KD71Data[i].SOKUTE_AVE = a/KD71Data[i].SOKUTEI_NT_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD71Data[i].ADDYMD )){
				KD71Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD71Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD71Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD71Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD71Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD71Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD71 set SOKUTEI_SU=%d ,SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KD71Data[i].SOKUTEI_NT_CUR,
								KD71Data[i].SOKUTEI_S[0],
								KD71Data[i].SOKUTEI_S[1],
								KD71Data[i].SOKUTEI_H[0],
								KD71Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEV_1R=%6.2f , SOKUTEV_2R=%6.2f, SOKUTEV_1L=%6.2f , SOKUTEV_2L=%6.2f ,",
								KD71Data[i].SOKUTEV_R[0],
								KD71Data[i].SOKUTEV_R[1],
								KD71Data[i].SOKUTEV_L[0],
								KD71Data[i].SOKUTEV_L[1]);
			str += str_c ;
			str_c[0] = NULL ;


			sprintf(str_c, " SOKUTEA_1R=%6.2f , SOKUTEA_2R=%6.2f, SOKUTEA_1L=%6.2f , SOKUTEA_2L=%6.2f ,",
								KD71Data[i].SOKUTEA_R[0],
								KD71Data[i].SOKUTEA_R[1],
								KD71Data[i].SOKUTEA_L[0],
								KD71Data[i].SOKUTEA_L[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1P=%d , SOKUTEI_2P=%d ,",
								KD71Data[i].SOKUTEI_P[0],
								KD71Data[i].SOKUTEI_P[1]);
			str += str_c ;
			str_c[0] = NULL ;

			//2003.02.05 E.Takase sprintf(str_c, " SOKUTEI_1T=%d , SOKUTEI_2T=%d, SOKUTE_AVE=%9.3f,",
			sprintf(str_c, " SOKUTEI_1T=%6.2f , SOKUTEI_2T=%6.2f, SOKUTE_AVE=%9.3f,",
								KD71Data[i].SOKUTEI_T[0],
								KD71Data[i].SOKUTEI_T[1],
								KD71Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD71Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD71Data[i].ADDYMD.c_str(),
									KD71Data[i].ADDTIM.c_str(),
									KD71Data[i].UPDCHR,
									KD71Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD71Data[i].UPDYMD.c_str(),
									KD71Data[i].UPDTIM.c_str(),
									KD71Data[i].UPDCHR,
									KD71Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD71Data[i].KENSA_YMD.c_str(),
			//					KD71Data[i].TOLEY_NO ,
			//					KD71Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD71Data[i].KENSA_YMD.c_str(),
						KD71Data[i].TOLEY_NO ,
						KD71Data[i].SAMPLE_P ,
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
                // 2004/08/30 A.Tamuraログ出力
                WriteLog2("EDatabaseError:" + e.Message);
                WriteLog2(str);

				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}
			catch(Exception& e)
			{
                // 2004/08/30 A.Tamuraログ出力
                WriteLog2("Exception:" + e.Message);
                WriteLog2(str);

				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			// 固有抵抗率測定（例外）ﾌｧｲﾙの更新
			if( KD71Data[i].SOKUTEI_NM > 2 ){
				Kd72_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD71Data[i].ADDYMD )) || !(IsNullSpace(KD71Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD71Data[i].ADDYMD )){
					KD71Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD71Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD71Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD71Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD71Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD71Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD71 set MEMO='%s' , ", KD71Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD71Data[i].ADDYMD.c_str(),
										KD71Data[i].ADDTIM.c_str(),
										KD71Data[i].UPDCHR,
										KD71Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD71Data[i].UPDYMD.c_str(),
										KD71Data[i].UPDTIM.c_str(),
										KD71Data[i].UPDCHR,
										KD71Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD71Data[i].KENSA_YMD.c_str(),
				//					KD71Data[i].TOLEY_NO ,
				//					KD71Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD71Data[i].KENSA_YMD.c_str(),
						KD71Data[i].TOLEY_NO ,
						KD71Data[i].SAMPLE_P ,
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
	                // 2004/08/30 A.Tamuraログ出力
	                WriteLog2("EDatabaseError:" + e.Message);
	                WriteLog2(str);

					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
				catch(Exception& e)
				{
	                // 2004/08/30 A.Tamuraログ出力
	                WriteLog2("Exception:" + e.Message);
	                WriteLog2(str);

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
*  function name : void Kd72_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀ(>2)を固有抵抗率測定(例外）ﾌｧｲﾙへ書き込む  KD72 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd72_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD71Data[iRec].SOKUTEI_NM; i++ ){

         // KD72へ追加するレコード存在するかどうかのチェック
         iRtn = Kd72_Serch02( KD71Data[iRec].KENSA_YMD,
                          KD71Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn < 0 ) {
                Kd72_Insert01( KD71Data[iRec].KENSA_YMD,
                          KD71Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                Kd72_Update02( KD71Data[iRec].KENSA_YMD,
                          KD71Data[iRec].TOLEY_NO,
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
*  function name : int Kd72_Serch02(AnsiString sYmd, int iTlno,        *
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
*  contents      : 指定したﾚｺｰﾄﾞが固有抵抗率例外ﾌｧｲﾙにあるかどうかのﾁｪｯｸ   *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd72_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD72 ";
        sBuf += "WHERE  KD72.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD72.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD72.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD72.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD72.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD72.KENSA_YMD, KD72.TOLEY_NO, KD72.SAMPLE_P, KD72.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd72_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD72へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd72_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD72 set SOKUTEI_S=%6.2f ,", KD71Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.2f ,", KD71Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEV_R=%6.2f ,", KD71Data[iSp-1].SOKUTEV_R[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEV_L=%6.2f ,", KD71Data[iSp-1].SOKUTEV_L[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEA_R=%6.2f ,", KD71Data[iSp-1].SOKUTEA_R[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEA_L=%6.2f ,", KD71Data[iSp-1].SOKUTEA_L[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_P=%d ,", KD71Data[iSp-1].SOKUTEI_P[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    //2003.02.05 E.Takase sprintf(str_c, " SOKUTEI_T=%d", KD71Data[iSp-1].SOKUTEI_T[iDtNo-1]);
    sprintf(str_c, " SOKUTEI_T=%6.2f", KD71Data[iSp-1].SOKUTEI_T[iDtNo-1]);
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
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("EDatabaseError:" + e.Message);
         WriteLog2(str);

         StatBarClear( e.Message )  ;
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
     }
     catch(Exception& e)
     {
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("Exception:" + e.Message);
         WriteLog2(str);

         StatBarClear( e.Message )  ;
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
     }
 }

/***********************************************************************
*  function name : void Kd72_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD72へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd72_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD72(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO,SOKUTEI_S,SOKUTEI_H, SOKUTEV_R,SOKUTEV_L,SOKUTEA_R,SOKUTEA_L,SOKUTEI_P, SOKUTEI_T, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    //2003.02.05 E.Takase sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%6.2f,%6.2f,%6.2f,%d,%d,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    //20161201 Y.Onishi n数3以上の保存時バグの修正
    //sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%6.2f,%6.2f,%6.2f,%d,%6.2f)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%6.2f,%6.2f,%6.2f,%d,%6.2f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
                                                      KD71Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEV_R[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEV_L[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEA_R[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEA_L[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEI_P[iDtNo-1],
                                                      KD71Data[iSp-1].SOKUTEI_T[iDtNo-1],
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
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("EDatabaseError:" + e.Message);
         WriteLog2(str);

         StatBarClear( e.Message )  ;
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
     }
     catch(Exception& e)
     {
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("Exception:" + e.Message);
         WriteLog2(str);

         StatBarClear( e.Message )  ;
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
     }
 }


/***********************************************************************
*  function name : void Kd73W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : 履歴作画のために KD73Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd73W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD73WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗履歴ﾜｰｸﾃﾞｰﾀ構造体KD73dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD73WFormat(void)
{
   for( int i=0; i<30; i++){
       KD73WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD73WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KD73WData[i].KOYU_MAX[j] = 0.0  ;    //固有抵抗率 規格上
            KD73WData[i].KOYU_MIN[j] = 0.0  ;    //固有抵抗率 規格下
            KD73WData[i].SOKUTE_AVE[j] = 0.0;
            KD73WData[i].SOKUTE_AVE_L[j] = 0.0;
            KD73WData[i].SOKUTE_AVE_R[j] = 0.0;
            KD73WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ ) {
               KD73WData[i].SOKUTEI[j][k] = 0.0;  //測定値
               KD73WData[i].SOKUTEV_R[j][k] = 0.0;  //測定値
               KD73WData[i].SOKUTEV_L[j][k] = 0.0;  //測定値
            }
       }

       KD73WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd73W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD73Wﾜｰｸﾃｰﾌﾞﾙからリード線取付抵抗履歴データ抽出KD73W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd73W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD71Data[i].SOKUTE_KBN == 0 && KD71Data[i].SAMPLE_P == -1 ) continue ;
             if( KD71Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
             strVal01 = KD71Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD73W ";
	      sBuf += "WHERE  KD73W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD73W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD71にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable73W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD73WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD73WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              double dAve_L =0.0;
              double dAve_R =0.0;
              for( int k=0; k < KD73WData[i].SOKUTEI_NM[j]; k++) {
                   dAve += KD73WData[i].SOKUTEI[j][k] ;
                   dAve_L += KD73WData[i].SOKUTEV_L[j][k] ;
                   dAve_R += KD73WData[i].SOKUTEV_R[j][k] ;
              }

               if( KD73WData[i].SOKUTEI_NM[j] !=0 ) {
                   KD73WData[i].SOKUTE_AVE[j] = dAve/KD73WData[i].SOKUTEI_NM[j] ;
                   KD73WData[i].SOKUTE_AVE_L[j] = dAve_L/KD73WData[i].SOKUTEI_NM[j] ;
                   KD73WData[i].SOKUTE_AVE_R[j] = dAve_R/KD73WData[i].SOKUTEI_NM[j] ;
               }
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable73W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD73WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable73W(int iSp)
{

     int iLotno = KD73WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD73WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD73WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD73WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["KOYU_MIN"].IsNull()) {
               KD73WData[iSp].KOYU_MIN[iLotno] = 0.0;
            }else {
                KD73WData[iSp].KOYU_MIN[iLotno] = Form1->Query1->FieldValues["KOYU_MIN"];
            }

            if ( Form1->Query1->FieldValues["KOYU_MAX"].IsNull()) {
               KD73WData[iSp].KOYU_MAX[iLotno] = 0.0;
            }else {
                KD73WData[iSp].KOYU_MAX[iLotno] = Form1->Query1->FieldValues["KOYU_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD73WData[iSp].DTKSHIN = " ";
     }else {
            KD73WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD73WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD73WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD73WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

	//2002/11/30 E.Takase
	//測定値 電圧 右
	if ( Form1->Query1->FieldValues["SOKUTEI_L"].IsNull()) {
	   KD73WData[iSp].SOKUTEV_L[iLotno][iDtNo] = 0.0;
	}else {
	    KD73WData[iSp].SOKUTEV_L[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI_L"];
	}

	//測定値 電圧 左
	if ( Form1->Query1->FieldValues["SOKUTEI_R"].IsNull()) {
	   KD73WData[iSp].SOKUTEV_R[iLotno][iDtNo] = 0.0;
	}else {
	    KD73WData[iSp].SOKUTEV_R[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI_R"];
	}

	//形状区分
	if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
	   KD73WData[iSp].KEIJYO_KBN = 0;
	}else {
	    KD73WData[iSp].KEIJYO_KBN = Form1->Query1->FieldValues["KEIJYO_KBN"];
	}

     iDtNo  += 1;
     KD73WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD73WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD71Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD71DataをKD71Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD71Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD71Data[i].SOKUTE_KBN == 0 || KD71Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD71Data[i].LINK == 0 ){
            iLinkSp = KD71Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD71Data[i].LINK;
        }

        if( KD73WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD73WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD73WData[iLinkSp-1].DTKSHIN =  KD71Data[i].DTKSHIN;

           //ロットNO
           KD73WData[iLinkSp-1].LOTNO[0]  = KD71Data[i].LOTNO ;

           // 規格下
           KD73WData[iLinkSp-1].KOYU_MIN[0] = KD71Data[i].KOYU_MIN;
           // 規格上
           KD73WData[iLinkSp-1].KOYU_MAX[0] = KD71Data[i].KOYU_MAX;

           KD73WData[iLinkSp-1].SOKUTEI_NM[0] = KD71Data[i].SOKUTEI_NT_CUR;

           if( KD71Data[i].SOKUTEI_NT_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           double a_L=0.0;
           double a_R=0.0;
           for( k=0; k < KD71Data[i].SOKUTEI_NM; k++ ) {
                  KD73WData[iLinkSp-1].SOKUTEI[0][k] = KD71Data[i].SOKUTEI_T[k];
                  KD73WData[iLinkSp-1].SOKUTEV_L[0][k] = KD71Data[i].SOKUTEV_L[k];
                  KD73WData[iLinkSp-1].SOKUTEV_R[0][k] = KD71Data[i].SOKUTEV_R[k];
                  a += KD73WData[iLinkSp-1].SOKUTEI[0][k] ;
                  a_L += KD73WData[iLinkSp-1].SOKUTEV_L[0][k] ;
                  a_R += KD73WData[iLinkSp-1].SOKUTEV_R[0][k] ;
           }

            //平均値
           if( KD71Data[i].SOKUTEI_NM != 0 ) {
             KD73WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD71Data[i].SOKUTEI_NM;
             KD73WData[iLinkSp-1].SOKUTE_AVE_L[0] = a_L/KD71Data[i].SOKUTEI_NM;
             KD73WData[iLinkSp-1].SOKUTE_AVE_R[0] = a_R/KD71Data[i].SOKUTEI_NM;
           }

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD73WData[iLinkSp-1].LOTCNT += 1;

          n = KD73WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD73WData[iLinkSp-1].LOTNO[n-1]  = KD71Data[i].LOTNO ;

          //リード線長さ 規格下
          KD73WData[iLinkSp-1].KOYU_MIN[n-1] = KD71Data[i].KOYU_MIN;

          //リード線長さ 規格上
          KD73WData[iLinkSp-1].KOYU_MAX[n-1] = KD71Data[i].KOYU_MAX;

          KD73WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD71Data[i].SOKUTEI_NT_CUR;

          if( KD71Data[i].SOKUTEI_NT_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          double a_L=0.0;
          double a_R=0.0;
          for( k=0; k < KD71Data[i].SOKUTEI_NM; k++ ) {
               KD73WData[iLinkSp-1].SOKUTEI[n-1][k] = KD71Data[i].SOKUTEI_T[k];
               KD73WData[iLinkSp-1].SOKUTEV_L[n-1][k] = KD71Data[i].SOKUTEV_L[k];
               KD73WData[iLinkSp-1].SOKUTEV_R[n-1][k] = KD71Data[i].SOKUTEV_R[k];
               a += KD73WData[iLinkSp-1].SOKUTEI[n-1][k] ;
               a_L += KD73WData[iLinkSp-1].SOKUTEV_L[n-1][k] ;
               a_R += KD73WData[iLinkSp-1].SOKUTEV_R[n-1][k] ;
          }

          KD73WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD71Data[i].SOKUTEI_NM;
          KD73WData[iLinkSp-1].SOKUTE_AVE_L[n-1] = a_L/KD71Data[i].SOKUTEI_NM;
          KD73WData[iLinkSp-1].SOKUTE_AVE_R[n-1] = a_R/KD71Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd73w(void)                                 *
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
void  AddKd73W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD71Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD71Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD73WData[iLinkSp-1].LOTNO[iRtn] = KD71Data[SamplePositionIdx-1].LOTNO;

   //規格下
    KD73WData[iLinkSp-1].KOYU_MIN[iRtn]= KD71Data[SamplePositionIdx-1].KOYU_MIN;

    //規格上
    KD73WData[iLinkSp-1].KOYU_MAX[iRtn] = KD71Data[SamplePositionIdx-1].KOYU_MAX;

    KD73WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR;

    //測定値
    for( i=0; i < KD73WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ ) {
         KD73WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD71Data[SamplePositionIdx-1].SOKUTEI_T[i];
         KD73WData[iLinkSp-1].SOKUTEV_R[iRtn][i] = KD71Data[SamplePositionIdx-1].SOKUTEV_R[i];
         KD73WData[iLinkSp-1].SOKUTEV_L[iRtn][i] = KD71Data[SamplePositionIdx-1].SOKUTEV_L[i];
    }
   double dAve ;
   double dAve_L ;
   double dAve_R ;
   dAve = 0.0;
   dAve_L = 0.0;
   dAve_R = 0.0;
   for( i=0; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR; i++ ){
        dAve += KD71Data[SamplePositionIdx-1].SOKUTEI_T[i];
        dAve_L += KD71Data[SamplePositionIdx-1].SOKUTEV_R[i];
        dAve_R += KD71Data[SamplePositionIdx-1].SOKUTEV_L[i];
   }

   dAve= dAve/KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR ;
   dAve_L= dAve_L/KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR ;
   dAve_R= dAve_R/KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR ;

   KD73WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;
   KD73WData[iLinkSp-1].SOKUTE_AVE_R[iRtn]=dAve_L;
   KD73WData[iLinkSp-1].SOKUTE_AVE_L[iRtn]=dAve_R;

   KD73WData[iLinkSp-1].KEIJYO_KBN=KD71Data[SamplePositionIdx-1].KEIJYO_KBN;

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
*  update        : 長さも設定する（コンミ対応） 2002/11/02 E.Takase    *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD51                *
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
            //20161128 Y.Onishi
            sBuf += "AND KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";
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
                //20161128 Y.Onishi
                sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";
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

                             //2002.11.02 E.Takase
                             //長さ（外径）寸法
                             if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   KD51Data[i].SOKUTEI_N[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_N[n-1] =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

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
*  update        : 長さも設定する（コンミ対応） 2002/11/02 E.Takase    *
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
*  update        : コンミ対応 2002/11/02 E.Takase                      *
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
*  function name : void CopyKD51to71(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : コンミ対応 2002/11/02 E.Takase                      *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙの厚さ、幅を KD８１へコピーする     *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void CopyKD51to71(void)
{
  int j;

  for( int i=0; i<30; i++){

      if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].SOKUTEI_NB_CUR ){

          //コンミ対応 2002/11/02 E.Takase
          // 形状区分４の場合
          if( KD51Data[i].KEIJYO_KBN == 4 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD71Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD71Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;

          }else if( KD51Data[i].KEIJYO_KBN == 5 ){
          // 形状区分５の場合
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD71Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_N[j] ;
                  //KD71Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD71Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
               //KD71Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;

          }else{
          // 形状区分１、２、３の場合
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD71Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_S[j] ;
                  KD71Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD71Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
               KD71Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;

          }
     }
   }
}


/***********************************************************************
*  function name : void Kd73W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd73Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd73W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD73W");

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
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("EDatabaseError:" + e.Message);
         WriteLog2(str);

         //  ShowMessage(e.Message);
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         StatBarClear( e.Message )  ;
         Update_err = 1;
     }
     catch(Exception& e)
     {
         // 2004/08/30 A.Tamuraログ出力
         WriteLog2("Exception:" + e.Message);
         WriteLog2(str);

         // ShowMessage(e.Message);
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         StatBarClear( e.Message )  ;
         Update_err = 1;
     }
 }

