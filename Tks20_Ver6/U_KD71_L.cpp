/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_KD71_L.cpp                                        *
*  create        : 2002.12.06                                          *
*  update        :                                                     *
*  contents      : KD71 SQL etc                                        *
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
*  function name : void KD71_72_LSerch01(void)                         *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率データファイルからデータを抽出            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD71_72_LSerch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  固有抵抗率 KD71
	//検査値の検索
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD71Data_L.KOYU_MIN = KM01_04Data.KOYU_MIN;
	KD71Data_L.KOYU_MAX = KM01_04Data.KOYU_MAX;
	KD71Data_L.KOYU_NM = KM01_04Data.SK_KOYU;
	//KOYU_VAL[100]
	//KOYU_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//問い合せ文実行
	//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	str = "SELECT ";
	str += "KD71.SOKUTEV_1L, KD71.SOKUTEV_2L, KD71.SOKUTEI_NM,SOKUTEI_SU, KD71.UPDCHR ";
	str += "FROM KD71 ";
	str += "WHERE  KD71.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD71.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD71.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD71.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
    //コンミ印刷の場合 形状区分=5
    if ( Flagcnd == 2 || Flagcnd == 3 ) {
	   str += "AND  KD71.KEIJYO_KBN = 5 ";
    }
	str += "ORDER BY KD71.KENSA_YMD, KD71.TOLEY_NO, KD71.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//固有抵抗率 検査値、検査個数、更新者
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEV_1L"])))
		KD71Data_L.KOYU_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEV_1L"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEV_2L"])))
		KD71Data_L.KOYU_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEV_2L"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD71Data_L.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD71Data_L.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD71Data_L.KOYU_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//検査個数のチェック
	if ( KD71Data_L.KOYU_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//問い合せ文実行
		//ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
		str = "SELECT ";
		str += "KD72.SOKUTEV_L, KD72.SOKUTEI_NO ";
		str += "FROM KD72 ";
		str += "WHERE  KD72.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD72.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD72.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD72.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD72.KENSA_YMD, KD72.TOLEY_NO, KD72.SAMPLE_P, KD72.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD72にデータがありません");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEV_L"])))
					KD71Data_L.KOYU_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEV_L"];
				else KD71Data_L.KOYU_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD71_LCompare01(void)                          *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率データが規格内かどうかを判断              *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD71_LCompare01(void)
{
    int i;
    int a;
    //0 : 不合格   1 : 合格
    for ( i = 0; i <= KD71Data_L.KOYU_NM - 1; i++ ) {
        if ( KD71Data_L.KOYU_MIN <= KD71Data_L.KOYU_VAL[i]
            &&  KD71Data_L.KOYU_MAX >= KD71Data_L.KOYU_VAL[i] ) {
            a = 1;

        }
        else {
            KD71Data_L.PASS = 0;
            return;
        }
    }
    KD71Data_L.PASS = 1;
}

/***********************************************************************
*  function name : void KD71_LFormat01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率データを初期化                            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void KD71_LFormat01(void)
{
    KD71Data_L.PASS = 0;            //固有抵抗率 検査合格 不合格
    KD71Data_L.KOYU_NM = 0;        	//固有抵抗率 検査データ数
    KD71Data_L.KOYU_MIN = 0;   	    //固有抵抗率 規格下
    KD71Data_L.KOYU_MAX = 0;    	//固有抵抗率 規格上
    KD71Data_L.UPDCHR = 0;          //更新者
    memset(KD71Data_L.KOYU_VAL, (int)NULL, sizeof(int) * 100);  //固有抵抗率 検査データ

}