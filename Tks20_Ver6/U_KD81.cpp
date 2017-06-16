/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD81.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD81 SQL etc                                        *
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
*  function name : void KD81_82Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 抗折力データファイルからデータを抽出                *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD81_82Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  抗折力 KD81
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD81Data.MAGE_MIN = KM01_04Data.MAGE_MIN;
	KD81Data.MAGE_MAX = KM01_04Data.MAGE_MAX;
	KD81Data.MAGE_NM = KM01_04Data.SK_MAGE;
	//MAGE_VAL[100]
	//MAGE_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD81.SOKUTEI_1M, KD81.SOKUTEI_2M, KD81.SOKUTEI_NM, SOKUTEI_SU,KD81.UPDCHR ";
	str += "FROM KD81 ";
	str += "WHERE  KD81.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD81.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD81.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD81.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD81.KENSA_YMD, KD81.TOLEY_NO, KD81.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//抗折力 検査値、検査個数、更新者
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1M"])))
		KD81Data.MAGE_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1M"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2M"])))
		KD81Data.MAGE_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2M"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD81Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD81Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD81Data.MAGE_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//検査個数のチェック
	if ( KD81Data.MAGE_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD82.SOKUTEI_M, KD82.SOKUTEI_NO ";
		str += "FROM KD82 ";
		str += "WHERE  KD82.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD82.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD82.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD82.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD82.KENSA_YMD, KD82.TOLEY_NO, KD82.SAMPLE_P, KD82.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD82にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_M"])))
					KD81Data.MAGE_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_M"];
				else KD81Data.MAGE_VAL[n] = 0;
				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD81Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 抗折力データが規格内かどうかを判断                  *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD81Compare01(void)
{
    int a;
    int i;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD81Data.MAGE_NM - 1; i++ ) {
        if ( KD81Data.MAGE_MIN <= KD81Data.MAGE_VAL[i]
            &&  KD81Data.MAGE_MAX >= KD81Data.MAGE_VAL[i] ) {
            a = 1;

        }
        else {
            KD81Data.PASS = 0;
            return;
        }
    }
    KD81Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD81Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 抗折力データを初期化                          *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD81Format01(void)
{
    KD81Data.PASS = 0;             	//抗折力 検査合格 不合格
    KD81Data.MAGE_NM = 0;        	//抗折力 検査データ数
    KD81Data.MAGE_MIN = 0;   	    //抗折力 規格下
    KD81Data.MAGE_MAX = 0;       	//抗折力 規格上
    KD81Data.UPDCHR = 0;            //更新者
    memset(KD81Data.MAGE_VAL, (int)NULL, sizeof(int) * 100);  //抗折力 検査データ
}
