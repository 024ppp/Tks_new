/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD01.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD01 SQL etc                                        *
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
*  function name : void KD01_02Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線長さデータファイルからデータを抽出          *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD01_02Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  リード線長さ KD01
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD01Data.LD_LNG_MIN = KM01_04Data.LD_LNG_MIN;
	KD01Data.LD_LNG_MAX = KM01_04Data.LD_LNG_MAX;
	KD01Data.LD_LNG_NM = KM01_04Data.SK_LD_LNG;
	//LD_LNG_VAL[100]
	//LD_LNG_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD01.SOKUTEI_1, KD01.SOKUTEI_2, KD01.SOKUTEI_NM,KD01.SOKUTEI_SU,KD01.UPDCHR ";
	str += "FROM KD01 ";
	str += "WHERE  KD01.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD01.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD01.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD01.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD01.KENSA_YMD, KD01.TOLEY_NO, KD01.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//リード線長さ 検査値、検査個数、更新者

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD01Data.LD_LNG_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD01Data.LD_LNG_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD01Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD01Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];

	//検査個数のチェック
	if ( KD01Data.LD_LNG_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD02.SOKUTEICHI, KD02.SOKUTEI_NO ";
		str += "FROM KD02 ";
		str += "WHERE  KD02.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD02.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD02.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD02.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD02.KENSA_YMD, KD02.TOLEY_NO, KD02.SAMPLE_P, KD02.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true ) {
		    //ShowMessage("KD02にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD01Data.LD_LNG_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD01Data.LD_LNG_VAL[n] = 0;
					// KD01Data.LD_LNG_VAL[n] = vardouble(Form1->Q_Work->FieldValues["SOKUTEICHI"]);
				Form1->Q_Work->Next();
		    }

		}


	}


}

/***********************************************************************
*  function name : void KD01Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線長さデータが規格内かどうかを判断            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD01Compare01(void)
{
    int i;
    int a;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD01Data.LD_LNG_NM - 1; i++ ) {
        if ( KD01Data.LD_LNG_MIN <= KD01Data.LD_LNG_VAL[i]
            &&  KD01Data.LD_LNG_MAX >= KD01Data.LD_LNG_VAL[i] ) {
            a = 1;

        }
        else {
            KD01Data.PASS = 0;
            return;
        }
    }
    KD01Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD01Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線長さデータを初期化                          *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD01Format01(void)
{

    KD01Data.PASS = 0;             	//リード線長さ 検査合格 不合格
    KD01Data.LD_LNG_NM = 0;        	//リード線長さ 検査データ数
    KD01Data.LD_LNG_MIN = 0;   	    //リード線長さ 規格下
    KD01Data.LD_LNG_MAX = 0;     	//リード線長さ 規格上
    KD01Data.UPDCHR = 0;            //更新者

    memset(KD01Data.LD_LNG_VAL, (int)NULL, sizeof(double) * 100);  //リード線長さ 検査データ

}