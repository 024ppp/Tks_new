/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD31.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD31 SQL etc                                        *
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
*  function name : void KD31_32Serch01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗データファイルからデータを抽出      *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD31_32Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  リード線取付抵抗 KD31
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD31Data.LD_TR_DEN = KM01_04Data.LD_TR_DENA;
	KD31Data.LD_TR_TIME = KM01_04Data.LD_TR_TIME;
	KD31Data.LD_TR_TEKO = KM01_04Data.LD_TR_TEKO;
	KD31Data.LD_TR_NM = KM01_04Data.SK_LD_TR;
	//LD_TR_VAL[100]
	//LD_TR_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD31.SOKUTEI_1V, KD31.SOKUTEI_2V, KD31.SOKUTEI_1A, KD31.SOKUTEI_2A,";
	str += "KD31.SOKUTEI_1, KD31.SOKUTEI_2,KD31.SOKUTEI_NM, SOKUTEI_SU,KD31.UPDCHR ";
	str += "FROM KD31 ";
	str += "WHERE  KD31.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD31.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD31.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD31.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD31.KENSA_YMD, KD31.TOLEY_NO, KD31.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//リード線取付抵抗 検査値、検査個数、更新者

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1V"])))
		KD31Data.LD_TRV_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1V"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2V"])))
		KD31Data.LD_TRV_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2V"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1A"])))
		KD31Data.LD_TRA_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1A"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2A"])))
		KD31Data.LD_TRA_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2A"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD31Data.LD_TRR_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD31Data.LD_TRR_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD31Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD31Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];

	//検査個数のチェック
	if ( KD31Data.LD_TR_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD32.SOKUTEI_V, KD32.SOKUTEI_A, KD32.SOKUTEI_NO ,KD32.SOKUTEICHI ";
		str += "FROM KD32 ";
		str += "WHERE  KD32.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD32.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD32.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD32.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD32.KENSA_YMD, KD32.TOLEY_NO, KD32.SAMPLE_P, KD32.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD32にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_V"])))
					KD31Data.LD_TRV_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_V"];
				else KD31Data.LD_TRV_VAL[n] = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_A"])))
					KD31Data.LD_TRA_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_A"];
				else KD31Data.LD_TRA_VAL[n] = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD31Data.LD_TRR_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD31Data.LD_TRR_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD31Compare01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗データが規格内かどうかを判断        *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD31Compare01(void)
{
    int i;
    int a;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD31Data.LD_TR_NM - 1; i++ ) {
        if ( KD31Data.LD_TR_DEN >= KD31Data.LD_TRR_VAL[i] ) {
            a = 1;

        }
        else {
            KD31Data.PASS = 0;
            return;
        }
    }
    KD31Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD31Format01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : リード線取付抵抗データを初期化                      *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD31Format01(void)
{
    KD31Data.PASS = 0;             	//リード線取付抵抗 検査合格 不合格
    KD31Data.LD_TR_NM = 0;        	//リード線取付抵抗 検査データ数
    KD31Data.LD_TR_DEN = 0;    		//リード線取付抵抗 測定電圧
    KD31Data.LD_TR_TIME = 0;   	  	//リード線取付抵抗 測定時間
    KD31Data.LD_TR_TEKO = 0;   	  	//リード線取付抵抗 測定電流
    KD31Data.UPDCHR = 0;            //更新者
    memset(KD31Data.LD_TRV_VAL, (int)NULL, sizeof(double) * 100);	//リード線取付抵抗 測定電圧 検査データ
    memset(KD31Data.LD_TRA_VAL, (int)NULL, sizeof(double) * 100); 	//リード線取付抵抗 測定電流 検査データ
    memset(KD31Data.LD_TRR_VAL, (int)NULL, sizeof(double) * 100); 	//リード線取付抵抗 測定抵抗 検査データ
}