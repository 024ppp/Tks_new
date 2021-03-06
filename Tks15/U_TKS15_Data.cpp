/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１５）                  *
*  file   name   : U_TKS15_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 母体比重測定処理データアクセス関数                  *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void KD51Format(void);
void SetTable51(void);
int  Kd52_Serch02( AnsiString , int , int, int );
void Kd52_Update01( int );
void Kd52_Update02( AnsiString , int, int, int );
void Kd52_Insert01( AnsiString , int ,int, int );
void SetTable53W(int);
//int Kd51_Serch03(void);
void SetTable51_C(void);

/***********************************************************************
*  function name : int  Kd51_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出           *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd51_Serch01(void)
{

    // 母体比重ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD51.KENSA_YMD, KD51.TOLEY_NO ";
    sBuf += "FROM KD51 ";
	sBuf += "WHERE KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD51.KENSA_YMD desc, KD51.TOLEY_NO";

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
*  function name : void Kd51_Serch02(int flag)                         *
*                  +--------------------------------------+            *
*          引  数  |  int       |   flag                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD51                *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd51_Serch02(int flag)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD51Data構造体変数の初期化(「検索」ﾎﾞﾀﾝを押した場合)
        if( !Save_Click ) KD51Format();

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
            sBuf += "AND KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	    sBuf += "ORDER BY KD51.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD51にデータがありません");
          return -1;
        }else {

           // 「保存」ﾎﾞﾀﾝを押して次のﾄﾚｰNOを検索する場合
           if( Save_Click )  {
               // ﾄﾚｰNOの設定
               Form1->edttlno->Text = strVal02 ;

               // KD51Data構造体変数の初期化
               KD51Format();
           }
           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable51();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD51Data[i].SOKUTE_KBN  && KD51Data[i].SAMPLE_P != -1 ) {
             if( KD51Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD51Data[i].DTKSHIN == KD51Data[j].DTKSHIN)
                        KD51Data[j].LINK = KD51Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 母体比重測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
        //  if( KD51Data[i].SOKUTEI_NM > 2 && KD51Data[i].SOKUTE_KBN == 1 &&
        //      KD51Data[i].SOKUTEI_NB_CUR  ) {

              if( KD51Data[i].SOKUTE_KBN == 1 ){

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
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
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
                             //長さ寸法
                             if ( Form1->Query1->FieldValues["SOKUHEI_N"].IsNull()) {
                                   KD51Data[i].SOKUTEI_N[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_N[n-1] =  Form1->Query1->FieldValues["SOKUHEI_N"];
                             }
                             //重量
                            if ( Form1->Query1->FieldValues["SOKUTEI_J"].IsNull()) {
                                   KD51Data[i].SOKUTEI_J[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_J[n-1] =  Form1->Query1->FieldValues["SOKUTEI_J"];
                             }
                             //母体比重
                             if ( Form1->Query1->FieldValues["SOKUTEI_B"].IsNull()) {
                                   KD51Data[i].SOKUTEI_B[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_B[n-1] =  Form1->Query1->FieldValues["SOKUTEI_B"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

       //コンミのデータ（内径・外型）コピー
       if ( flag == 1 ) {
          SetTable51_C();
       }

    return 1;
}
/***********************************************************************
*  function name : int  Kd51_Serch03(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 2003.02                                             *
*  update        :                                                     *
*  contents      : 母体比重ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD51 コンミのみ     *
*  written by    : 高瀬 恵利(JFE MTS Corp.)                            *
***********************************************************************/
int Kd51_Serch03(void)
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

	Form1->Query2->Close();
	Form1->Query2->SQL->Clear();

	//問い合せ文実行
	//ソート昇順 ,検査予定日、トレーNo
	sBuf = "SELECT *  ";
	sBuf += "FROM KD51 ";
	sBuf += "WHERE  KD51.KENSA_YMD = '" + strVal01 + "' ";
	sBuf += "AND  KD51.TOLEY_NO = '" + strVal02 + "' ";
	sBuf += "AND  KD51.KEIJYO_KBN = 5 ";
        sBuf += "AND  KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 工場区分追加
	//2001.05.21 修正 sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	sBuf += "ORDER BY KD51.SAMPLE_P";

	Form1->Query2->SQL->Add(sBuf);
	Form1->Query2->Open();

	if ( Form1->Query2->Eof ) {
		return -1;

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
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
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

          if( HaveSokutei == 0 && KD51Data[iRec].SOKUTE_KBN == 1 ){
              HaveSokutei = 1;
          }
     }
     //得意先ｺｰﾄﾞ
     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD51Data[iRec].DTKSCOD = " ";
     }else {
          KD51Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }
     //得意先品番
     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD51Data[iRec].DTKSHIN = " ";
     }else {
          KD51Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }
     //ﾛｯﾄNO
     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD51Data[iRec].LOTNO = " ";
     }else {
          KD51Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }
     //自社品番
     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD51Data[iRec].HINBAN = " ";
     }else {
          KD51Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }
     //材質ｺｰﾄﾞ
     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD51Data[iRec].ZISCOD = " ";
     }else {
          KD51Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }
     //材質名
     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD51Data[iRec].ZISNAM = " ";
     }else {
          KD51Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }
     //母体比重 下限
     if ( Form1->Query1->FieldValues["BOTAI_MIN"].IsNull()) {
          KD51Data[iRec].BOTAI_MIN = 0.0;
     }else {
          KD51Data[iRec].BOTAI_MIN =  Form1->Query1->FieldValues["BOTAI_MIN"];
     }
     //母体比重 上限
     if ( Form1->Query1->FieldValues["BOTAI_MAX"].IsNull()) {
          KD51Data[iRec].BOTAI_MAX = 0.0;
     }else {
          KD51Data[iRec].BOTAI_MAX =  Form1->Query1->FieldValues["BOTAI_MAX"];
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

      //長さ寸法１、長さ寸法２
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
     //重量１、重量２
      if ( Form1->Query1->FieldValues["SOKUTEI_1J"].IsNull()) {
          KD51Data[iRec].SOKUTEI_J[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_J[0] =  Form1->Query1->FieldValues["SOKUTEI_1J"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2J"].IsNull()) {
          KD51Data[iRec].SOKUTEI_J[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_J[1] =  Form1->Query1->FieldValues["SOKUTEI_2J"];
     }

     //測定値１ 測定値２, 母体比重
     if ( Form1->Query1->FieldValues["SOKUTEI_1B"].IsNull()) {
          KD51Data[iRec].SOKUTEI_B[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_B[0] =  Form1->Query1->FieldValues["SOKUTEI_1B"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2B"].IsNull()) {
          KD51Data[iRec].SOKUTEI_B[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_B[1] =  Form1->Query1->FieldValues["SOKUTEI_2B"];
     }

     //測定個数
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD51Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD51Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD51Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD51Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }
     //測定値平均値（母体比重）
     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD51Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD51Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }
     //登録日
     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD51Data[iRec].ADDYMD = " ";
     }else {
          KD51Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
     }

    if( IsNullSpace( KD51Data[iRec].ADDYMD ) ){
             KD51Data[iRec].SOKUTEI_NB_CUR = 0 ;
             KD51Data[iRec].SOKUTEI_NS_CUR = 0;
             KD51Data[iRec].SOKUTEI_NH_CUR = 0;
             KD51Data[iRec].SOKUTEI_NN_CUR = 0;
             KD51Data[iRec].SOKUTEI_NJ_CUR = 0;
    }else{
             KD51Data[iRec].SOKUTEI_NB_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NS_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NH_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NN_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NJ_CUR = KD51Data[iRec].SOKUTEI_SU ;
    }

     //登録時間
     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD51Data[iRec].ADDTIM = " ";
     }else {
          KD51Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }
     //更新日
     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD51Data[iRec].UPDYMD = " ";
     }else {
          KD51Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }
     //更新時間

     //更新者
     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD51Data[iRec].UPDCHR = 0;
     }else {
          KD51Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     //更新回数
     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD51Data[iRec].UPDCNT = 0;
     }else {
          KD51Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD51Data[iRec].MEMO =  " ";
     }else {
          KD51Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

 }

/***********************************************************************
*  function name : void SetTable51_C(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2003.02                                             *
*  update        :                                                     *
*  contents      : KD51Data構造体へﾃﾞｰﾀを設定(コンミ用)                *
*  written by    : 高瀬 恵利 (JFE MTS Corp.)                           *
***********************************************************************/
void SetTable51_C(void)
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

	for( i=0; i<30; i++ ) {
	
		if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].KEIJYO_KBN == 5 ){

			strVal03 = IntToStr( KD51Data[i].SAMPLE_P );

			//内径 KD11
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//問い合せ文実行
			//ソート昇順 ,検査予定日、トレーNo
			sBuf = "SELECT SOKUTEI_1, SOKUTEI_2 ";
			sBuf += "FROM KD11 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				// 内径 
				if ( Form1->Query2->FieldValues["SOKUTEI_1"].IsNull()) {
					KD51Data[i].SOKUTEI_S[0] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_S[0] =  Form1->Query2->FieldValues["SOKUTEI_1"];
				}
				if ( Form1->Query2->FieldValues["SOKUTEI_2"].IsNull()) {
					KD51Data[i].SOKUTEI_S[1] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_S[1] =  Form1->Query2->FieldValues["SOKUTEI_2"];
				}

                //母体比重の計算
                BHijyuCal(i+1, 1);
                BHijyuCal(i+1, 2);

			}

			//内径 KD12
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//問い合せ文実行
			//ソート昇順 ,検査予定日、トレーNo
			sBuf = "SELECT SOKUTEI_NO,SOKUTEICHI ";
			sBuf += "FROM KD12 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				while( !Form1->Query2->Eof ) {
					//測定NO
					if ( Form1->Query2->FieldValues["SOKUTEI_NO"].IsNull()) {
						n = 3;
					}else {
						n =  Form1->Query2->FieldValues["SOKUTEI_NO"];
					}
					// 内径 
					if ( Form1->Query2->FieldValues["SOKUTEICHI"].IsNull()) {
						KD51Data[i].SOKUTEI_S[n-1] = 0.0;
					}else {
						KD51Data[i].SOKUTEI_S[n-1] =  Form1->Query2->FieldValues["SOKUTEICHI"];
					}
                    Form1->Query2->Next();

                    //母体比重の計算
                    BHijyuCal(i+1, n);
				}
			}

			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//外径 KD21
			//問い合せ文実行
			//ソート昇順 ,検査予定日、トレーNo
			sBuf = "SELECT SOKUTEI_1, SOKUTEI_2 ";
			sBuf += "FROM KD21 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {

				//幅(外形)寸法１、幅（外形）寸法２
				if ( Form1->Query2->FieldValues["SOKUTEI_1"].IsNull()) {
					KD51Data[i].SOKUTEI_H[0] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_H[0] =  Form1->Query2->FieldValues["SOKUTEI_1"];
				}
				if ( Form1->Query2->FieldValues["SOKUTEI_2"].IsNull()) {
					KD51Data[i].SOKUTEI_H[1] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_H[1] =  Form1->Query2->FieldValues["SOKUTEI_2"];
				}
                //母体比重の計算
                BHijyuCal(i+1, 1);
                BHijyuCal(i+1, 2);
			}

			//内径 KD22
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//問い合せ文実行
			//ソート昇順 ,検査予定日、トレーNo
			sBuf = "SELECT SOKUTEI_NO,SOKUTEICHI ";
			sBuf += "FROM KD22 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				while( !Form1->Query2->Eof ) {
					//測定NO
					if ( Form1->Query2->FieldValues["SOKUTEI_NO"].IsNull()) {
						n = 3;
					}else {
						n =  Form1->Query2->FieldValues["SOKUTEI_NO"];
					}
					// 内径 
					if ( Form1->Query2->FieldValues["SOKUTEICHI"].IsNull()) {
						KD51Data[i].SOKUTEI_H[n-1] = 0.0;
					}else {
						KD51Data[i].SOKUTEI_H[n-1] =  Form1->Query2->FieldValues["SOKUTEICHI"];
					}
                    Form1->Query2->Next();
                    //母体比重の計算
                    BHijyuCal(i+1, n);

				}
			}


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
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
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
      KD51Data[i].DTKSCOD = '\0';     //得意先コード
      KD51Data[i].DTKSHIN = '\0';     //得意先品番
      KD51Data[i].LOTNO = '\0';       //ロットNO
      KD51Data[i].HINBAN = '\0';      //自社品番
      KD51Data[i].ZISCOD = '\0';      //材質コード
      KD51Data[i].ZISNAM = '\0';      //材質名

      KD51Data[i].BOTAI_MAX = 0.0;    //母体比重 規格上
      KD51Data[i].BOTAI_MIN = 0.0;    //母体比重 規格下
      KD51Data[i].KEIJYO_KBN = 0;     //母体比重 形状区分
      KD51Data[i].SOKUTEI_NM = 0;    //母体比重 測定個数
      KD51Data[i].SOKUTEI_SU = 0;    //母体比重 測定個数
      KD51Data[i].SOKUTE_AVE = 0.0;  //母体比重 測定平均値

      memset(KD51Data[i].SOKUTEI_B,(int)NULL, sizeof(double) * 100); ;  //測定値
      memset(KD51Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //厚さ寸法
      memset(KD51Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //幅寸法
      memset(KD51Data[i].SOKUTEI_N,(int)NULL, sizeof(double) * 100); ;  //長さ
      memset(KD51Data[i].SOKUTEI_J,(int)NULL, sizeof(double) * 100); ;  //重量

      KD51Data[i].ADDYMD = '\0';      //登録日
      KD51Data[i].ADDTIM = '\0';      //登録時間
      KD51Data[i].UPDYMD = '\0';      //変更日
      KD51Data[i].UPDTIM = '\0';      //変更時間
      KD51Data[i].UPDCHR = 0;         //更新者
      KD51Data[i].UPDCNT = 0;         //更新回数
      KD51Data[i].LINK = 0;
      KD51Data[i].SOKUTEI_NB_CUR = 0;
      KD51Data[i].SOKUTEI_NS_CUR = 0;
      KD51Data[i].SOKUTEI_NH_CUR = 0;
      KD51Data[i].SOKUTEI_NN_CUR = 0;
      KD51Data[i].SOKUTEI_NJ_CUR = 0;
      KD51Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void Kd51_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀを母体比重ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD51            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd51_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ1
             if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_N[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==4)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_J[0] = pEdt1_S[iKomoku-1]->Value;

              BHijyuCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // 計測ﾃﾞｰﾀ2
             if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_N[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==4)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_J[1] = pEdt2_S[iKomoku-1]->Value;

              BHijyuCal(SamplePositionIdx, 2 );

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD51Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                 n = pEdt4_S[iKomoku-1]->Value;

                 // 計測ﾃﾞｰﾀ2
                if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                    KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==2)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==3)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==4)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] = pEdt3_S[iKomoku-1]->Value;

                 BHijyuCal(SamplePositionIdx, n );
             }
    }




	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].SAMPLE_P != -1 &&
		      !( KD51Data[i].SOKUTEI_NB_CUR == 0 &&
				KD51Data[i].SOKUTEI_NS_CUR == 0 &&
				KD51Data[i].SOKUTEI_NH_CUR == 0 &&
				KD51Data[i].SOKUTEI_NN_CUR == 0 &&
				KD51Data[i].SOKUTEI_NJ_CUR == 0     )){

			//担当者ｺｰﾄﾞ
			KD51Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KD51Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			//KD51Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD51Data[i].SOKUTEI_NB_CUR; j++ )
				a += KD51Data[i].SOKUTEI_B[j] ;
			if( KD51Data[i].SOKUTEI_NB_CUR )
				KD51Data[i].SOKUTE_AVE = a/KD51Data[i].SOKUTEI_NB_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD51Data[i].ADDYMD )){
				KD51Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD51Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD51Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD51Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD51Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD51Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD51 set SOKUTEI_SU=%d ,SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KD51Data[i].SOKUTEI_NB_CUR,
								KD51Data[i].SOKUTEI_S[0],
								KD51Data[i].SOKUTEI_S[1],
								KD51Data[i].SOKUTEI_H[0],
								KD51Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1N=%6.3f , SOKUTEI_2N=%6.3f, SOKUTEI_1J=%6.3f , SOKUTEI_2J=%6.3f ,",
								KD51Data[i].SOKUTEI_N[0],
								KD51Data[i].SOKUTEI_N[1],
								KD51Data[i].SOKUTEI_J[0],
								KD51Data[i].SOKUTEI_J[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1B=%6.2f , SOKUTEI_2B=%6.2f, SOKUTE_AVE=%9.5f,",
								KD51Data[i].SOKUTEI_B[0],
								KD51Data[i].SOKUTEI_B[1],
								KD51Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD51Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD51Data[i].ADDYMD.c_str(),
									KD51Data[i].ADDTIM.c_str(),
									KD51Data[i].UPDCHR,
									KD51Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD51Data[i].UPDYMD.c_str(),
									KD51Data[i].UPDTIM.c_str(),
									KD51Data[i].UPDCHR,
									KD51Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD51Data[i].KENSA_YMD.c_str(),
			//					KD51Data[i].TOLEY_NO ,
			//					KD51Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD51Data[i].KENSA_YMD.c_str(),
						KD51Data[i].TOLEY_NO ,
						KD51Data[i].SAMPLE_P ,
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

			// 母体比重測定（例外）ﾌｧｲﾙの更新
			if( KD51Data[i].SOKUTEI_NM > 2 ){
				Kd52_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD51Data[i].ADDYMD )) || !(IsNullSpace(KD51Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD51Data[i].ADDYMD )){
					KD51Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD51Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD51Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD51Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD51Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD51Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD51 set MEMO='%s' , ", KD51Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD51Data[i].ADDYMD.c_str(),
										KD51Data[i].ADDTIM.c_str(),
										KD51Data[i].UPDCHR,
										KD51Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD51Data[i].UPDYMD.c_str(),
										KD51Data[i].UPDTIM.c_str(),
										KD51Data[i].UPDCHR,
										KD51Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD51Data[i].KENSA_YMD.c_str(),
				//					KD51Data[i].TOLEY_NO ,
				//					KD51Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD51Data[i].KENSA_YMD.c_str(),
						KD51Data[i].TOLEY_NO ,
						KD51Data[i].SAMPLE_P ,
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
*  function name : void Kd52_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀ(>2)を母体比重測定(例外）ﾌｧｲﾙへ書き込む  KD52 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD51Data[iRec].SOKUTEI_NM; i++ ){

         // KD52へ追加するレコード存在するかどうかのチェック
         iRtn = Kd52_Serch02( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn < 0 ) {
                Kd52_Insert01( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                Kd52_Update02( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
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
*  function name : int Kd52_Serch02(AnsiString sYmd, int iTlno,        *
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
*  contents      : 指定したﾚｺｰﾄﾞが母体比重例外ﾌｧｲﾙにあるかどうかのﾁｪｯｸ   *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd52_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD52 ";
        sBuf += "WHERE  KD52.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD52.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD52.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD52.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD52.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD52.KENSA_YMD, KD52.TOLEY_NO, KD52.SAMPLE_P, KD52.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd52_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD52へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD52 set SOKUTEI_S=%6.3f ,", KD51Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.3f ,", KD51Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUHEI_N=%6.3f ,", KD51Data[iSp-1].SOKUTEI_N[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_J=%6.3f ,", KD51Data[iSp-1].SOKUTEI_J[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEI_B=%6.2f", KD51Data[iSp-1].SOKUTEI_B[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d",
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
*  function name : void Kd52_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD52へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD52 ( KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEI_S, SOKUTEI_H, SOKUHEI_N, SOKUTEI_J, SOKUTEI_B, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s', %d, %d, %d, %6.3f, %6.3f, %6.3f, %6.3f, %6.2f, %d)",
                                  sYmd.c_str(), iTlno, iSp, iDtNo ,
                                  KD51Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_N[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_J[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_B[iDtNo-1], iKojoKbn);      // 20160630_工場区分追加

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
*  function name : void Kd53W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : 履歴作画のために KD53Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd53W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD53WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗履歴ﾜｰｸﾃﾞｰﾀ構造体KD53dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD53WFormat(void)
{
   for( int i=0; i<30; i++){
       KD53WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD53WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KD53WData[i].BOTAI_MAX[j] = 0.0  ;    //母体比重 規格上
            KD53WData[i].BOTAI_MIN[j] = 0.0  ;    //母体比重 規格下
            KD53WData[i].SOKUTE_AVE[j] = 0.0;
            KD53WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD53WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD53WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd53W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD53Wﾜｰｸﾃｰﾌﾞﾙからリード線取付抵抗履歴データ抽出KD53W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd53W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD51Data[i].SOKUTE_KBN == 0 && KD51Data[i].SAMPLE_P == -1 ) continue ;
             if( KD51Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番とロットNOで検索
             strVal01 = KD51Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD53W ";
	      sBuf += "WHERE  KD53W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD53W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD51にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable53W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD53WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD53WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD53WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KD53WData[i].SOKUTEI[j][k] ;

               if( KD53WData[i].SOKUTEI_NM[j] !=0 )
                   KD53WData[i].SOKUTE_AVE[j] = dAve/KD53WData[i].SOKUTEI_NM[j] ;
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable53W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD53WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable53W(int iSp)
{

     int iLotno = KD53WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD53WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD53WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD53WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["BOTAI_MIN"].IsNull()) {
               KD53WData[iSp].BOTAI_MIN[iLotno] = 0.0;
            }else {
                KD53WData[iSp].BOTAI_MIN[iLotno] = Form1->Query1->FieldValues["BOTAI_MIN"];
            }

            if ( Form1->Query1->FieldValues["BOTAI_MAX"].IsNull()) {
               KD53WData[iSp].BOTAI_MAX[iLotno] = 0.0;
            }else {
                KD53WData[iSp].BOTAI_MAX[iLotno] = Form1->Query1->FieldValues["BOTAI_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD53WData[iSp].DTKSHIN = " ";
     }else {
            KD53WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD53WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD53WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD53WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD53WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD53WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD51Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD51DataをKD51Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD51Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD51Data[i].SOKUTE_KBN == 0 || KD51Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD51Data[i].LINK == 0 ){
            iLinkSp = KD51Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD51Data[i].LINK;
        }

        if( KD53WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD53WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD53WData[iLinkSp-1].DTKSHIN =  KD51Data[i].DTKSHIN;

           //ロットNO
           KD53WData[iLinkSp-1].LOTNO[0]  = KD51Data[i].LOTNO ;

           // 規格下
           KD53WData[iLinkSp-1].BOTAI_MIN[0] = KD51Data[i].BOTAI_MIN;
           // 規格上
           KD53WData[iLinkSp-1].BOTAI_MAX[0] = KD51Data[i].BOTAI_MAX;

           KD53WData[iLinkSp-1].SOKUTEI_NM[0] = KD51Data[i].SOKUTEI_NB_CUR;

           if( KD51Data[i].SOKUTEI_NB_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD51Data[i].SOKUTEI_NM; k++ ) {
                  KD53WData[iLinkSp-1].SOKUTEI[0][k] = KD51Data[i].SOKUTEI_B[k];
                  a += KD53WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD51Data[i].SOKUTEI_NM != 0 )
             KD53WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD51Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD53WData[iLinkSp-1].LOTCNT += 1;

          n = KD53WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD53WData[iLinkSp-1].LOTNO[n-1]  = KD51Data[i].LOTNO ;

          //リード線長さ 規格下
          KD53WData[iLinkSp-1].BOTAI_MIN[n-1] = KD51Data[i].BOTAI_MIN;

          //リード線長さ 規格上
          KD53WData[iLinkSp-1].BOTAI_MAX[n-1] = KD51Data[i].BOTAI_MAX;

          KD53WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD51Data[i].SOKUTEI_NB_CUR;

          if( KD51Data[i].SOKUTEI_NB_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD51Data[i].SOKUTEI_NM; k++ ) {
               KD53WData[iLinkSp-1].SOKUTEI[n-1][k] = KD51Data[i].SOKUTEI_B[k];
               a += KD53WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD53WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD51Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd53w(void)                                 *
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
void  AddKd53W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD51Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD51Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD53WData[iLinkSp-1].LOTNO[iRtn] = KD51Data[SamplePositionIdx-1].LOTNO;

   // 規格下
    KD53WData[iLinkSp-1].BOTAI_MIN[iRtn]= KD51Data[SamplePositionIdx-1].BOTAI_MIN;

    //規格上
    KD53WData[iLinkSp-1].BOTAI_MAX[iRtn] = KD51Data[SamplePositionIdx-1].BOTAI_MAX;

    KD53WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR;

    //測定値
    for( i=0; i < KD53WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD53WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD51Data[SamplePositionIdx-1].SOKUTEI_B[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR; i++ ){
        dAve += KD51Data[SamplePositionIdx-1].SOKUTEI_B[i];
   }

   dAve= dAve/KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR ;

   KD53WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}




/***********************************************************************
*  function name : void Kd53W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd53Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd53W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD53W");

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
