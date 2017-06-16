/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : ÉgÉâÉCÉXåüç∏ÉVÉXÉeÉÄÅiÇsÇjÇrÇQÇPÅj                  *
*  file   name   : U_KD61.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD61 SQL etc                                        *
*  written by    : çÇê£  åbóò(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
/***********************************************************************
*  function name : void KD61_62Serch01(void)                           *
*                  +--------------------------------------+            *
*          à¯  êî  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          ñﬂÇËíl  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ÇgÇìçdìxÉfÅ[É^ÉtÉ@ÉCÉãÇ©ÇÁÉfÅ[É^Çíäèo              *
*  written by    : çÇê£  åbóò(NKK unics Corp.)                         *
***********************************************************************/
void KD61_62Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  ÇgÇìçdìx KD61
	//åüç∏ílÇÃåüçı
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD61Data.HSC_A_MIN = KM01_04Data.HSC_A_MIN;
	KD61Data.HSC_A_MAX = KM01_04Data.HSC_A_MAX;
	KD61Data.HSC_S_MIN = KM01_04Data.HSC_S_MIN;
	KD61Data.HSC_S_MAX = KM01_04Data.HSC_S_MAX;
	KD61Data.HSD_A_MIN = KM01_04Data.HSD_A_MIN;
	KD61Data.HSD_A_MAX = KM01_04Data.HSD_A_MAX;
	KD61Data.HSD_S_MIN = KM01_04Data.HSD_S_MIN;
	KD61Data.HSD_S_MAX = KM01_04Data.HSD_S_MAX;
	KD61Data.HSC_A_SK_NM = KM01_04Data.SK_HSC_A;
	KD61Data.HSC_S_SK_NM = KM01_04Data.SK_HSC_S;
	KD61Data.HSD_A_SK_NM = KM01_04Data.SK_HSD_A;
	KD61Data.HSD_S_SK_NM = KM01_04Data.SK_HSD_S;
	//HSC_A_VAL[100]
	//HSC_A_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//ñ‚Ç¢çáÇπï∂é¿çs
	//É\Å[Égè∏èá ìæà”êÊ∫∞ƒﬁÅAåüç∏ó\íËì˙ÅAÉgÉåÅ[NoÅAÉTÉìÉvÉãÉ|ÉWÉVÉáÉì
	str = "SELECT ";
	str += "KD61.HSC_A_1, KD61.HSC_A_2, ";
	str += "KD61.HSC_S_1, KD61.HSC_S_2, ";
	str += "KD61.HSD_A_1, KD61.HSD_A_2, ";
	str += "KD61.HSD_S_1, KD61.HSD_S_2, ";
	str += "KD61.HSC_SK_NUM, KD61.HSD_SK_NUM,HSC_SK_SU,HSD_SK_SU, KD61.UPDCHR ";
	str += "FROM KD61 ";
	str += "WHERE  KD61.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD61.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD61.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD61.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD61.KENSA_YMD, KD61.TOLEY_NO, KD61.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//ÇgÇìçdìx åüç∏ílÅAåüç∏å¬êîÅAçXêVé“
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_A_1"])))
		KD61Data.HSC_A_VAL[0] = Form1->Q_Work->FieldValues["HSC_A_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_A_2"])))
		KD61Data.HSC_A_VAL[1] = Form1->Q_Work->FieldValues["HSC_A_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_S_1"])))
		KD61Data.HSC_S_VAL[0] = Form1->Q_Work->FieldValues["HSC_S_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_S_2"])))
		KD61Data.HSC_S_VAL[1] =Form1->Q_Work->FieldValues["HSC_S_2"];

		//KD61Data.HSC_SK_NM = vardouble(Form1->Q_Work->FieldValues["HSC_SK_NUM"]);
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_A_1"])))
		KD61Data.HSD_A_VAL[0] = Form1->Q_Work->FieldValues["HSD_A_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_A_2"])))
		KD61Data.HSD_A_VAL[1] = Form1->Q_Work->FieldValues["HSD_A_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_S_1"])))
		KD61Data.HSD_S_VAL[0] = Form1->Q_Work->FieldValues["HSD_S_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_S_2"])))
		KD61Data.HSD_S_VAL[1] = Form1->Q_Work->FieldValues["HSD_S_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD61Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_SK_SU"])))
		KD61Data.HSC_SK_SU = Form1->Q_Work->FieldValues["HSC_SK_SU"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_SK_SU"])))
		KD61Data.HSD_SK_SU = Form1->Q_Work->FieldValues["HSD_SK_SU"];
	//KD61Data.HSD_SK_NM = vardouble(Form1->Q_Work->FieldValues["HSD_SK_NUM"]);

	//åüç∏å¬êîÇÃÉ`ÉFÉbÉN
	if ( KD61Data.HSC_A_SK_NM > 2 || KD61Data.HSC_S_SK_NM > 2
	     || KD61Data.HSD_A_SK_NM > 2 || KD61Data.HSD_S_SK_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//ñ‚Ç¢çáÇπï∂é¿çs
		//É\Å[Égè∏èá ìæà”êÊ∫∞ƒﬁÅAåüç∏ó\íËì˙ÅAÉgÉåÅ[NoÅAÉTÉìÉvÉãÉ|ÉWÉVÉáÉì
		str = "SELECT ";
		str += "KD62.HSC_A, ";
		str += "KD62.HSC_S, ";
		str += "KD62.HSD_A, ";
		str += "KD62.HSD_S, ";
		str += "KD62.SOKUTEI_NO ";
		str += "FROM KD62 ";
		str += "WHERE  KD62.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD62.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD62.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD62.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD62.KENSA_YMD, KD62.TOLEY_NO, KD62.SAMPLE_P, KD62.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD62Ç…ÉfÅ[É^Ç™Ç†ÇËÇ‹ÇπÇÒ");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_A"])))
					KD61Data.HSC_A_VAL[n] = Form1->Q_Work->FieldValues["HSC_A"];
				else KD61Data.HSC_A_VAL[n] = 0;

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSC_S"])))
					KD61Data.HSC_S_VAL[n] = Form1->Q_Work->FieldValues["HSC_S"];
				else KD61Data.HSC_S_VAL[n] = 0;

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_A"])))
					KD61Data.HSD_A_VAL[n] = Form1->Q_Work->FieldValues["HSD_A"];
				else KD61Data.HSD_A_VAL[n] = 0;

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["HSD_S"])))
					KD61Data.HSD_S_VAL[n] = Form1->Q_Work->FieldValues["HSD_S"];
				else KD61Data.HSD_S_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


}


}

/***********************************************************************
*  function name : void KD61Compare01(void)                            *
*                  +--------------------------------------+            *
*          à¯  êî  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          ñﬂÇËíl  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ÇgÇìçdìxÉfÅ[É^Ç™ãKäiì‡Ç©Ç«Ç§Ç©Çîªíf                *
*  written by    : çÇê£  åbóò(NKK unics Corp.)                         *
***********************************************************************/
void KD61Compare01(void)
{
    int i;
    int a;
    //0 : ïsçáäi   1 : çáäi
    for ( i = 0; i <= KD61Data.HSC_A_SK_NM - 1; i++ ) {
        if ( KD61Data.HSC_A_MIN <= KD61Data.HSC_A_VAL[i]
            &&  KD61Data.HSC_A_MAX >= KD61Data.HSC_A_VAL[i] ) {
            a = 1;

        }
        else {
            KD61Data.PASS = 0;
            return;
        }
    }
    for ( i = 0; i <= KD61Data.HSC_S_SK_NM - 1; i++ ) {
        if ( KD61Data.HSC_S_MIN <= KD61Data.HSC_S_VAL[i]
            &&  KD61Data.HSC_S_MAX >= KD61Data.HSC_S_VAL[i] ) {
            a = 1;

        }
        else {
            KD61Data.PASS = 0;
            return;
        }
    }

    for ( i = 0; i <= KD61Data.HSD_A_SK_NM - 1; i++ ) {
        if ( KD61Data.HSD_A_MIN <= KD61Data.HSD_A_VAL[i]
            &&  KD61Data.HSD_A_MAX >= KD61Data.HSD_A_VAL[i] ) {
            a = 1;

        }
        else {
            KD61Data.PASS = 0;
            return;
        }
    }
    for ( i = 0; i <= KD61Data.HSD_S_SK_NM - 1; i++ ) {
        if ( KD61Data.HSD_S_MIN <= KD61Data.HSD_S_VAL[i]
            &&  KD61Data.HSD_S_MAX >= KD61Data.HSD_S_VAL[i] ) {
            a = 1;

        }
        else {
            KD61Data.PASS = 0;
            return;
        }
    }


    KD61Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD61Format01(void)                             *
*                  +--------------------------------------+            *
*          à¯  êî  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          ñﬂÇËíl  |   Ç»Çµ     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ÇgÇìçdìxÉfÅ[É^Çèâä˙âª                              *
*  written by    : çÇê£  åbóò(NKK unics Corp.)                         *
***********************************************************************/
void KD61Format01(void)
{
    KD61Data.PASS = 0;             	//ÇgÇìçdìx åüç∏çáäi ïsçáäi
    KD61Data.HSC_A_SK_NM = 0;        	//ÇgÇìÇbçdìx åüç∏ÉfÅ[É^êî
    KD61Data.HSD_A_SK_NM = 0;        	//ÇgÇìÇcçdìx åüç∏ÉfÅ[É^êî
    KD61Data.HSC_S_SK_NM = 0;        	//ÇgÇìÇbçdìx åüç∏ÉfÅ[É^êî
    KD61Data.HSD_S_SK_NM = 0;        	//ÇgÇìÇcçdìx åüç∏ÉfÅ[É^êî
    KD61Data.HSC_A_MIN = 0;     	//ÇgÇìÇb_Ç`çdìx ãKäiâ∫
    KD61Data.HSC_A_MAX = 0;     	//ÇgÇìÇb_Ç`çdìx ãKäiè„
    memset(KD61Data.HSC_A_VAL, (int)NULL, sizeof(int) * 100);  //ÇgÇìÇb_Ç`çdìx åüç∏ÉfÅ[É^
    KD61Data.HSC_S_MIN = 0;   	    //ÇgÇìÇb_Çrçdìx ãKäiâ∫
    KD61Data.HSC_S_MAX = 0;     	//ÇgÇìÇb_Çrçdìx ãKäiè„
    memset(KD61Data.HSC_A_VAL, (int)NULL, sizeof(int) * 100);  //ÇgÇìÇb_Çrçdìx åüç∏ÉfÅ[É^
    KD61Data.HSD_A_MIN = 0;   	    //ÇgÇìÇc_Ç`çdìx ãKäiâ∫
    KD61Data.HSD_A_MAX = 0;     	//ÇgÇìÇc_Ç`çdìx ãKäiè„
    memset(KD61Data.HSD_A_VAL, (int)NULL, sizeof(double) * 100);  //ÇgÇìçdìx åüç∏ÉfÅ[É^
    KD61Data.HSD_S_MIN = 0;   	    //ÇgÇìÇc_Çrçdìx ãKäiâ∫
    KD61Data.HSD_S_MAX = 0;     	//ÇgÇìÇc_Çrçdìx ãKäiè„
    memset(KD61Data.HSD_A_VAL, (int)NULL, sizeof(double) * 100);  //ÇgÇìÇc_Çrçdìx åüç∏ÉfÅ[É^
    KD61Data.UPDCHR = 0;            //çXêVé“

}