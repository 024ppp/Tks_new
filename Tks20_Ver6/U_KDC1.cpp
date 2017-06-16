/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KDC1.cpp                                          *
*  create        : 2002.12.06                                          *
*  update        :                                                     *
*  contents      : KDC1 SQL etc                                        *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
/***********************************************************************
*  function name : void KDC1_C2Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 現物抗折力データファイルからデータを抽出            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KDC1_C2Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  現物抗折力 KDC1
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KDC1Data.MAGEG_MIN = KM01_04Data.MAGEG_MIN;
	KDC1Data.MAGEG_MAX = KM01_04Data.MAGEG_MAX;
	KDC1Data.MAGEG_NM = KM01_04Data.SK_MAGEG;
	//MAGEG_VAL[100]
	//MAGEG_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KDC1.SOKUTEI_1M, KDC1.SOKUTEI_2M, KDC1.SOKUTEI_NM, SOKUTEI_SU,KDC1.UPDCHR ";
	str += "FROM KDC1 ";
	str += "WHERE  KDC1.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KDC1.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KDC1.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KDC1.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
    //コンミ印刷の場合 形状区分=5
    if ( Flagcnd == 2 || Flagcnd == 3 ) {
	   str += "AND  KDC1.KEIJYO_KBN = 5 ";
    }
	str += "ORDER BY KDC1.KENSA_YMD, KDC1.TOLEY_NO, KDC1.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//現物抗折力 検査値、検査個数、更新者
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1M"])))
		KDC1Data.MAGEG_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1M"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2M"])))
		KDC1Data.MAGEG_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2M"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KDC1Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KDC1Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KDC1Data.MAGEG_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//検査個数のチェック
	if ( KDC1Data.MAGEG_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KDC2.SOKUTEI_M, KDC2.SOKUTEI_NO ";
		str += "FROM KDC2 ";
		str += "WHERE  KDC2.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KDC2.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KDC2.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KDC2.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KDC2.KENSA_YMD, KDC2.TOLEY_NO, KDC2.SAMPLE_P, KDC2.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KDC2にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_M"])))
					KDC1Data.MAGEG_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_M"];
				else KDC1Data.MAGEG_VAL[n] = 0;
				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KDC1Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 現物抗折力データが規格内かどうかを判断              *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KDC1Compare01(void)
{
    int a;
    int i;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KDC1Data.MAGEG_NM - 1; i++ ) {
        if ( KDC1Data.MAGEG_MIN <= KDC1Data.MAGEG_VAL[i]
            &&  KDC1Data.MAGEG_MAX >= KDC1Data.MAGEG_VAL[i] ) {
            a = 1;

        }
        else {
            KDC1Data.PASS = 0;
            return;
        }
    }
    KDC1Data.PASS = 1;
}

/***********************************************************************
*  function name : void KDC1Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 現物抗折力データを初期化                          *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KDC1Format01(void)
{
    KDC1Data.PASS = 0;             	//現物抗折力 検査合格 不合格
    KDC1Data.MAGEG_NM = 0;        	//現物抗折力 検査データ数
    KDC1Data.MAGEG_MIN = 0;   	    //現物抗折力 規格下
    KDC1Data.MAGEG_MAX = 0;       	//現物抗折力 規格上
    KDC1Data.UPDCHR = 0;            //更新者
    memset(KDC1Data.MAGEG_VAL, (int)NULL, sizeof(int) * 100);  //現物抗折力 検査データ
}
