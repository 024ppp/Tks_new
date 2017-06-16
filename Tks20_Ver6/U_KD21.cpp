/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD21.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD21 SQL etc                                        *
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
*  function name : void KD21_22Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法縦押しデータファイルからデータを抽出    *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD21_22Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  ブラシ幅寸法縦押し KD21
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD21Data.BURASIT_MIN = KM01_04Data.BURASIT_MIN;
	KD21Data.BURASIT_MAX = KM01_04Data.BURASIT_MAX;
	KD21Data.BURASIT_NM = KM01_04Data.SK_BURASIT;
	//BURASIT_VAL[100]
	//BURASIT_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD21.SOKUTEI_1, KD21.SOKUTEI_2, KD21.SOKUTEI_NM,SOKUTEI_SU, KD21.UPDCHR ";
	str += "FROM KD21 ";
	str += "WHERE  KD21.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD21.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD21.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD21.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD21.KENSA_YMD, KD21.TOLEY_NO, KD21.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//ブラシ幅寸法縦押し 検査値、検査個数、更新者
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD21Data.BURASIT_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD21Data.BURASIT_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD21Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD21Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD21Data.BURASIT_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//検査個数のチェック
	if ( KD21Data.BURASIT_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD22.SOKUTEICHI, KD22.SOKUTEI_NO ";
		str += "FROM KD22 ";
		str += "WHERE  KD22.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD22.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD22.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD22.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD22.KENSA_YMD, KD22.TOLEY_NO, KD22.SAMPLE_P, KD22.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD22にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD21Data.BURASIT_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD21Data.BURASIT_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD21Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法縦押しデータが規格内かどうかを判断            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD21Compare01(void)
{
    int i;
    int a;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD21Data.BURASIT_NM - 1; i++ ) {
        if ( KD21Data.BURASIT_MIN <= KD21Data.BURASIT_VAL[i]
            &&  KD21Data.BURASIT_MAX >= KD21Data.BURASIT_VAL[i] ) {
            a = 1;

        }
        else {
            KD21Data.PASS = 0;
            return;
        }
    }
    KD21Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD21Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法縦押しデータを初期化                          *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD21Format01(void)
{
    KD21Data.PASS = 0;             	//ブラシ幅寸法縦押し 検査合格 不合格
    KD21Data.BURASIT_NM = 0;        	//ブラシ幅寸法縦押し 検査データ数
    KD21Data.BURASIT_MIN = 0;   	    //ブラシ幅寸法縦押し 規格下
    KD21Data.BURASIT_MAX = 0;     	//ブラシ幅寸法縦押し 規格上
    KD21Data.UPDCHR = 0;            //更新者
    memset(KD21Data.BURASIT_VAL, (int)NULL, sizeof(double) * 100);  //ブラシ幅寸法縦押し 検査データ

}