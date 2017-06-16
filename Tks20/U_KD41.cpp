/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD41.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD41 SQL etc                                        *
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
*  function name : void KD41_42Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線引張強度データファイルからデータを抽出      *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD41_42Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  リード線引張強度 KD41
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD41Data.LD_HP_MIN = KM01_04Data.LD_HP_KYO;
	KD41Data.LD_HP_NM = KM01_04Data.SK_LD_HP;
	//LD_HP_VAL[100]
	//LD_HP_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD41.SOKUTEI_1, KD41.SOKUTEI_2, KD41.SOKUTEI_NM,SOKUTEI_SU, KD41.UPDCHR ";
	str += "FROM KD41 ";
	str += "WHERE  KD41.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD41.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD41.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD41.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD41.KENSA_YMD, KD41.TOLEY_NO, KD41.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//リード線引張強度 検査値、検査個数、更新者
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD41Data.LD_HP_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD41Data.LD_HP_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD41Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD41Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD41Data.LD_HP_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//検査個数のチェック
	if ( KD41Data.LD_HP_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD42.SOKUTEICHI, KD42.SOKUTEI_NO ";
		str += "FROM KD42 ";
		str += "WHERE  KD42.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD42.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD42.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD42.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD42.KENSA_YMD, KD42.TOLEY_NO, KD42.SAMPLE_P, KD42.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD42にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD41Data.LD_HP_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD41Data.LD_HP_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD41Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線引張強度データが規格内かどうかを判断        *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD41Compare01(void)
{
    int i;
    int a;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD41Data.LD_HP_NM - 1; i++ ) {
        if ( KD41Data.LD_HP_MIN <= KD41Data.LD_HP_VAL[i]  ) {
            a = 1;

        }
        else {
            KD41Data.PASS = 0;
            return;
        }
    }
    KD41Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD41Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線引張強度データを初期化                      *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD41Format01(void)
{
    KD41Data.PASS = 0;             	//リード線引張強度 検査合格 不合格
    KD41Data.LD_HP_NM = 0;        	//リード線引張強度 検査データ数
    KD41Data.LD_HP_MIN = 0;   	    //リード線引張強度 規格下
    KD41Data.UPDCHR = 0;            //更新者
    memset(KD41Data.LD_HP_VAL, (int)NULL, sizeof(int) * 100);  //リード線引張強度 検査データ

}


