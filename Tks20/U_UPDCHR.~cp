//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
static int CHRNO[13];
//AnsiString CHRstr01;


//---------------------------------------------------------------------------
#pragma package(smart_init)
/***********************************************************************
*  function name : void UPDCHR_Make01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2000.01                                             *
*  update        :                                                     *
*  contents      : 更新者のグループ化                                  *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_Make01(int CurNo)
{


    if ( CurNo > 0 && DTKSData.DTKSCOD == KM01_04Data.DTKSCOD ) {
	    if ( CHRNO[0] <= 0 && KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[0] == -1 || KD51Data.UPDCHR != 0 ) {
				CHRNO[0]  = KD51Data.UPDCHR;
			}
		}
	    if ( CHRNO[5] <= 0 && KD71Data.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[5] == -1 || KD71Data.UPDCHR != 0 ) {
		    	CHRNO[5]  = KD71Data.UPDCHR;
			}
		}
	    if ( CHRNO[6] <= 0 && KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[6] == -1 || KD81Data.UPDCHR != 0 ) {
		    	CHRNO[6]  = KD81Data.UPDCHR;
			}
		}
	    if ( CHRNO[7] <= 0 && KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[7] == -1 || KD91Data.UPDCHR != 0 ) {
			    CHRNO[7]  = KD91Data.UPDCHR;
			}
		}
	    if ( CHRNO[8] <= 0 && KD31Data.LD_TR_NM != 0 && KD31Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[8] == -1 || KD31Data.UPDCHR != 0 ) {
			    CHRNO[8]  = KD31Data.UPDCHR;
			}
		}
	    if ( CHRNO[9] <= 0 && KD41Data.LD_HP_NM != 0 && KD41Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[9] == -1 || KD41Data.UPDCHR != 0 ) {
			    CHRNO[9]  = KD41Data.UPDCHR;
			}
		}
	    if ( CHRNO[10] <= 0 && KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[10] == -1 || KD01Data.UPDCHR != 0 ) {
			    CHRNO[10]  = KD01Data.UPDCHR;
			}
		}
	    if ( CHRNO[11] <= 0 && KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[11] == -1 || KD11Data.UPDCHR != 0 ) {
			    CHRNO[11]  = KD11Data.UPDCHR;
			}
		}
	    if ( CHRNO[12] <= 0 && KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[12] == -1 || KD21Data.UPDCHR != 0 ) {
			    CHRNO[12] = KD21Data.UPDCHR;
			}
		}
	    if ( CHRNO[1] <= 0 && KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
			if ( CHRNO[1] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[1]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[2] <= 0 && KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
			if ( CHRNO[2] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[2]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[3] <= 0 && KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
			if ( CHRNO[3] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[3]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[4] <= 0 && KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
			if ( CHRNO[4] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[4]  = KD61Data.UPDCHR;
			}
		}


	}
	if ( CurNo > 0 && DTKSData.DTKSCOD != KM01_04Data.DTKSCOD ) {
		//「検査員=・・・・」文字列作成
		UPDCHR_Make02();
		//TW_UPDCHR に 追加
		UPDCHRInsert02();
		//DTKSData CHRNO[] 初期化
		CHRNO[0] = -1;
		CHRNO[1] = -1;
		CHRNO[2] = -1;
		CHRNO[3] = -1;
		CHRNO[4] = -1;
		CHRNO[5] = -1;
		CHRNO[6] = -1;
		CHRNO[7] = -1;
		CHRNO[8] = -1;
		CHRNO[9] = -1;
		CHRNO[10] = -1;
		CHRNO[11] = -1;
		CHRNO[12] = -1;
		CHRNO[13] = -1;

		DTKSData.DTKSCOD = KM01_04Data.DTKSCOD;
	    if ( KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 ) {
			CHRNO[0]  = KD51Data.UPDCHR;
		}
	    if ( KD71Data.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 ) {
		    CHRNO[5]  = KD71Data.UPDCHR;
		}
	    if ( KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 ) {
		    CHRNO[6]  = KD81Data.UPDCHR;
		}
	    if ( KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 ) {
		    CHRNO[7]  = KD91Data.UPDCHR;
		}
	    if ( KD31Data.LD_TR_NM != 0 && KD31Data.SOKUTEI_SU > 0 ) {
		    CHRNO[8]  = KD31Data.UPDCHR;
		}
	    if ( KD41Data.LD_HP_NM != 0 && KD41Data.SOKUTEI_SU > 0 ) {
		    CHRNO[9]  = KD41Data.UPDCHR;
		}
	    if ( KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 ) {
		    CHRNO[10]  = KD01Data.UPDCHR;
		}
	    if ( KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 ) {
		    CHRNO[11]  = KD11Data.UPDCHR;
		}
	    if ( KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 ) {
		    CHRNO[12] = KD21Data.UPDCHR;
		}
	    if ( KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
		    CHRNO[1]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
		    CHRNO[2]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
		    CHRNO[3]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
		    CHRNO[4]  = KD61Data.UPDCHR;
		}

	}

	//一番最初の行の時
	if ( CurNo == 0 ) {

		//CHRNO[] 初期化
		CHRNO[0] = -1;
		CHRNO[1] = -1;
		CHRNO[2] = -1;
		CHRNO[3] = -1;
		CHRNO[4] = -1;
		CHRNO[5] = -1;
		CHRNO[6] = -1;
		CHRNO[7] = -1;
		CHRNO[8] = -1;
		CHRNO[9] = -1;
		CHRNO[10] = -1;
		CHRNO[11] = -1;
		CHRNO[12] = -1;
		CHRNO[13] = -1;
        DTKSData.DTKSCOD = KM01_04Data.DTKSCOD;
	    if ( KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 && KD51Data.UPDCHR != 0 ) {
			CHRNO[0]  = KD51Data.UPDCHR;
		}
	    if ( KD71Data.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 && KD71Data.UPDCHR != 0 ) {
		    CHRNO[5]  = KD71Data.UPDCHR;
		}
	    if ( KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 && KD81Data.UPDCHR != 0 ) {
		    CHRNO[6]  = KD81Data.UPDCHR;
		}
	    if ( KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 && KD91Data.UPDCHR != 0 ) {
		    CHRNO[7]  = KD91Data.UPDCHR;
		}
	    if ( KD31Data.LD_TR_NM != 0 && KD31Data.SOKUTEI_SU > 0 && KD31Data.UPDCHR != 0 ) {
		    CHRNO[8]  = KD31Data.UPDCHR;
		}
	    if ( KD41Data.LD_HP_NM != 0 && KD41Data.SOKUTEI_SU > 0 && KD41Data.UPDCHR != 0 ) {
		    CHRNO[9]  = KD41Data.UPDCHR;
		}
	    if ( KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 && KD01Data.UPDCHR != 0 ) {
		    CHRNO[10]  = KD01Data.UPDCHR;
		}
	    if ( KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 && KD11Data.UPDCHR != 0 ) {
		    CHRNO[11]  = KD11Data.UPDCHR;
		}
	    if ( KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 && KD21Data.UPDCHR != 0 ) {
		    CHRNO[12] = KD21Data.UPDCHR;
		}
	    if ( KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[1]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[2]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[3]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[4]  = KD61Data.UPDCHR;
		}
	}

    if ( CurNo == -2 ) {
		//「検査員=・・・・」文字列作成
		UPDCHR_Make02();
		//TW_UPDCHR に 追加
		UPDCHRInsert02();
    }
}


/***********************************************************************
*  function name : AnsiString UPDCHR_Make02(void)                      *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | AnsiString | 更新者                  |            *
*                  +--------------------------------------+            *
*  create        : 2000.01                                             *
*  update        :                                                     *
*  contents      : 更新者のグループ化                                  *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_Make02(void)
{
    AnsiString SQLstr;
    AnsiString x[13][13];
    AnsiString str2[13];
    AnsiString str3[13];
    int flag[13];
    int i,j,n,m;


    memset(flag, (int)NULL, sizeof(int) * 13);
    memset(str2, (int)NULL, sizeof(AnsiString) * 13);
    //CHRNO[0] = KD51Data.UPDCHR;
    //CHRNO[2] = KD71Data.UPDCHR;
    //CHRNO[3] = KD81Data.UPDCHR;
    //CHRNO[4] = KD91Data.UPDCHR;
    //CHRNO[5] = KD31Data.UPDCHR;
    //CHRNO[6] = KD41Data.UPDCHR;
    //CHRNO[7] = KD01Data.UPDCHR;
    //CHRNO[8] = KD11Data.UPDCHR;
    //CHRNO[9] = KD21Data.UPDCHR;
    //CHRNO[1] = KD61Data.UPDCHR;

    str2[0] = "見掛比重";
    str2[5] = "抵抗率";
    str2[6] = "曲げ強さ";
    str2[7] = "座屈";
    str2[8] = "取付抵抗";
    str2[9] = "取付強度";
    str2[10] = "線長さ";
    str2[11] = "ブラシ幅";
    str2[12] = "ブラシ縦";
    str2[1] = "HsC(圧面)";
    str2[2] = "HsC(側面)";
    str2[3] = "HsD(圧面)";
    str2[4] = "HsD(側面)";

    for ( i = 0; i < 12; i++ ) {
        //担当者マスタからマスタデータを抽出
        Form1->Q_STRS->Close();
        Form1->Q_STRS->SQL->Clear();
        //問い合せ文実行
        //ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	    SQLstr = "SELECT ";
	    SQLstr += "TANNAM  FROM SM12S ";
        SQLstr += "WHERE  TANSYA = '" + IntToStr(CHRNO[i]) + "'" ;
        Form1->Q_STRS->SQL->Add(SQLstr);
        Form1->Q_STRS->Open();
        if( Form1->Q_STRS->Bof == true && Form1->Q_STRS->Eof){
        //if( Form1->Q_STRS->RecordCount > 0 ) {
            str3[i] = " ";
        }
        else {
            Form1->Q_STRS->First();
            str3[i] = Form1->Q_STRS->FieldValues["TANNAM"];
        }
    }


    i = j = n = m = 0;
	UPDCHRstr02 = " ";
    for ( i = 0; i < 12; i++ ) {
    	if ( CHRNO[i] != -1 ) {
		    n = 0;
	        if ( flag[i] == 0 ) {
	            if ( n == 0 ) n = 1;
	            else  UPDCHRstr02 += "/";
	            UPDCHRstr02 += str2[i];
	        }
	        for ( j = i + 1; j < 12; j++ ) {
	            if ( CHRNO[i] == CHRNO[j] ) {
	                if ( flag[j] == 0 ) {
	                    if ( n == 0 ) n = 1;
	                    else  UPDCHRstr02 += "/";
	                    UPDCHRstr02 += str2[j];
	                    flag[j] = 1;
	                }
	            }
	        }
	        if ( flag[i] == 0 ) {
	            UPDCHRstr02 += "=";
	            UPDCHRstr02 += str3[i];
	            UPDCHRstr02 += "  ";

	        }
		}

    }

    m = 0;


}

/***********************************************************************
*  function name : void UPDCHRInsert02(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2000.01                                             *
*  update        :                                                     *
*  contents      : 検査員のデータをワークに追加                        *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHRInsert02(void)
{
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];

    str_c[0] = '\0';
    //Initial Query
    Form1->Q_TW_UPDCHR->Close();
    Form1->Q_TW_UPDCHR->SQL->Clear();

    //add sql INSERT

    str = "insert into TW_UPDCHR(DTKSCOD,str) ";

    wsprintf(str_c,"values('%s','検査員(%s)') ",
                            DTKSData.DTKSCOD.c_str(),
							UPDCHRstr02.c_str()
                            );

	//str += str_c;
	Form1->Q_TW_UPDCHR->SQL->Add(str + str_c);

	//execute sql
	try
	{
	    Form1->Q_TW_UPDCHR->ExecSQL();
	    rec++;
	}
	catch(EDatabaseError& e)
	{
	    ShowMessage(e.Message);
	}
	catch(Exception& e)
	{
	    ShowMessage(e.Message);
	}
}

/***********************************************************************
*  function name : void UPDCHR_2_Make01(void)                          *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 更新者のグループ化                                  *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_2_Make01(int CurNo)
{


    if ( CurNo > 0 && DTKSData.DTKSCOD == KM01_04Data.DTKSCOD ) {
	    if ( CHRNO[0] <= 0 && KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[0] == -1 || KD51Data.UPDCHR != 0 ) {
				CHRNO[0]  = KD51Data.UPDCHR;
			}
		}
	    if ( CHRNO[5] <= 0 && KD71Data.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[5] == -1 || KD71Data.UPDCHR != 0 ) {
		    	CHRNO[5]  = KD71Data.UPDCHR;
			}
		}
	    if ( CHRNO[6] <= 0 && KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[6] == -1 || KD81Data.UPDCHR != 0 ) {
		    	CHRNO[6]  = KD81Data.UPDCHR;
			}
		}
	    if ( CHRNO[7] <= 0 && KDC1Data.MAGEG_NM != 0 && KDC1Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[7] == -1 || KDC1Data.UPDCHR != 0 ) {
		    	CHRNO[7]  = KDC1Data.UPDCHR;
			}
		}
	    if ( CHRNO[8] <= 0 && KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[8] == -1 || KD91Data.UPDCHR != 0 ) {
			    CHRNO[8]  = KD91Data.UPDCHR;
			}
		}

	    if ( CHRNO[9] <= 0 && KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[9] == -1 || KD01Data.UPDCHR != 0 ) {
			    CHRNO[9]  = KD01Data.UPDCHR;
			}
		}
	    if ( CHRNO[10] <= 0 && KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[10] == -1 || KD11Data.UPDCHR != 0 ) {
			    CHRNO[10]  = KD11Data.UPDCHR;
			}
		}
	    if ( CHRNO[11] <= 0 && KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 ) {
			if ( CHRNO[11] == -1 || KD21Data.UPDCHR != 0 ) {
			    CHRNO[11] = KD21Data.UPDCHR;
			}
		}
	    if ( CHRNO[1] <= 0 && KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
			if ( CHRNO[1] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[1]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[2] <= 0 && KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
			if ( CHRNO[2] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[2]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[3] <= 0 && KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
			if ( CHRNO[3] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[3]  = KD61Data.UPDCHR;
			}
		}
	    if ( CHRNO[4] <= 0 && KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
			if ( CHRNO[4] == -1 || KD61Data.UPDCHR != 0 ) {
			    CHRNO[4]  = KD61Data.UPDCHR;
			}
		}


	}
	if ( CurNo > 0 && DTKSData.DTKSCOD != KM01_04Data.DTKSCOD ) {
		//「検査員=・・・・」文字列作成
		UPDCHR_2_Make02();
		//TW_UPDCHR に 追加
		UPDCHRInsert02();
		//DTKSData CHRNO[] 初期化
		CHRNO[0] = -1;
		CHRNO[1] = -1;
		CHRNO[2] = -1;
		CHRNO[3] = -1;
		CHRNO[4] = -1;
		CHRNO[5] = -1;
		CHRNO[6] = -1;
		CHRNO[7] = -1;
		CHRNO[8] = -1;
		CHRNO[9] = -1;
		CHRNO[10] = -1;
		CHRNO[11] = -1;
		CHRNO[12] = -1;
		CHRNO[13] = -1;

		DTKSData.DTKSCOD = KM01_04Data.DTKSCOD;
	    if ( KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 ) {
			CHRNO[0]  = KD51Data.UPDCHR;
		}
	    if ( KD71Data_R.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 ) {
		    CHRNO[5]  = KD71Data.UPDCHR;
		}
	    if ( KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 ) {
		    CHRNO[6]  = KD81Data.UPDCHR;
		}
	    if ( KDC1Data.MAGEG_NM != 0 && KDC1Data.SOKUTEI_SU > 0 ) {
		    CHRNO[7]  = KD81Data.UPDCHR;
		}
	    if ( KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 ) {
		    CHRNO[8]  = KD91Data.UPDCHR;
		}
	    if ( KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 ) {
		    CHRNO[9]  = KD01Data.UPDCHR;
		}
	    if ( KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 ) {
		    CHRNO[10]  = KD11Data.UPDCHR;
		}
	    if ( KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 ) {
		    CHRNO[11] = KD21Data.UPDCHR;
		}
	    if ( KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
		    CHRNO[1]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 ) {
		    CHRNO[2]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
		    CHRNO[3]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 ) {
		    CHRNO[4]  = KD61Data.UPDCHR;
		}

	}

	//一番最初の行の時
	if ( CurNo == 0 ) {

		//CHRNO[] 初期化
		CHRNO[0] = -1;
		CHRNO[1] = -1;
		CHRNO[2] = -1;
		CHRNO[3] = -1;
		CHRNO[4] = -1;
		CHRNO[5] = -1;
		CHRNO[6] = -1;
		CHRNO[7] = -1;
		CHRNO[8] = -1;
		CHRNO[9] = -1;
		CHRNO[10] = -1;
		CHRNO[11] = -1;
		CHRNO[12] = -1;
		CHRNO[13] = -1;
        DTKSData.DTKSCOD = KM01_04Data.DTKSCOD;
	    if ( KD51Data.BOTAI_NM != 0 && KD51Data.SOKUTEI_SU > 0 && KD51Data.UPDCHR != 0 ) {
			CHRNO[0]  = KD51Data.UPDCHR;
		}
	    if ( KD71Data.KOYU_NM != 0 && KD71Data.SOKUTEI_SU > 0 && KD71Data.UPDCHR != 0 ) {
		    CHRNO[5]  = KD71Data.UPDCHR;
		}
	    if ( KD81Data.MAGE_NM != 0 && KD81Data.SOKUTEI_SU > 0 && KD81Data.UPDCHR != 0 ) {
		    CHRNO[6]  = KD81Data.UPDCHR;
		}
	    if ( KDC1Data.MAGEG_NM != 0 && KDC1Data.SOKUTEI_SU > 0 && KDC1Data.UPDCHR != 0 ) {
		    CHRNO[7]  = KDC1Data.UPDCHR;
		}
	    if ( KD91Data.ZAKUT_NM != 0 && KD91Data.SOKUTEI_SU > 0 && KD91Data.UPDCHR != 0 ) {
		    CHRNO[8]  = KD91Data.UPDCHR;
		}
	    if ( KD01Data.LD_LNG_NM != 0 && KD01Data.SOKUTEI_SU > 0 && KD01Data.UPDCHR != 0 ) {
		    CHRNO[9]  = KD01Data.UPDCHR;
		}
	    if ( KD11Data.BURASI_NM != 0 && KD11Data.SOKUTEI_SU > 0 && KD11Data.UPDCHR != 0 ) {
		    CHRNO[10]  = KD11Data.UPDCHR;
		}
	    if ( KD21Data.BURASIT_NM != 0 && KD21Data.SOKUTEI_SU > 0 && KD21Data.UPDCHR != 0 ) {
		    CHRNO[11] = KD21Data.UPDCHR;
		}
	    if ( KD61Data.HSC_A_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[1]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSC_S_SK_NM != 0 && KD61Data.HSC_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[2]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_A_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[3]  = KD61Data.UPDCHR;
		}
	    if ( KD61Data.HSD_S_SK_NM != 0 && KD61Data.HSD_SK_SU > 0 && KD61Data.UPDCHR != 0 ) {
		    CHRNO[4]  = KD61Data.UPDCHR;
		}
	}

    if ( CurNo == -2 ) {
		//「検査員=・・・・」文字列作成
		UPDCHR_2_Make02();
		//TW_UPDCHR に 追加
		UPDCHRInsert02();
    }
}


/***********************************************************************
*  function name : AnsiString UPDCHR_2_Make02(void)                    *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | AnsiString | 更新者                  |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 更新者のグループ化                                  *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_2_Make02(void)
{
    AnsiString SQLstr;
    AnsiString x[13][13];
    AnsiString str2[13];
    AnsiString str3[13];
    int flag[13];
    int i,j,n,m;


    memset(flag, (int)NULL, sizeof(int) * 13);
    memset(str2, (int)NULL, sizeof(AnsiString) * 13);

    str2[0] = "見掛比重";
    str2[1] = "HsC(圧面)";
    str2[2] = "HsC(側面)";
    str2[3] = "HsD(圧面)";
    str2[4] = "HsD(側面)";
    str2[5] = "抵抗率";
    str2[6] = "曲げ強さ";
    str2[7] = "現物曲げ強さ";
    str2[8] = "座屈";
    str2[9] = "線長さ";
    str2[10] = "ブラシ幅";
    str2[11] = "ブラシ縦";

    for ( i = 0; i < 12; i++ ) {
        //担当者マスタからマスタデータを抽出
        Form1->Q_STRS->Close();
        Form1->Q_STRS->SQL->Clear();
        //問い合せ文実行
        //ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
	    SQLstr = "SELECT ";
	    SQLstr += "TANNAM  FROM SM12S ";
        SQLstr += "WHERE  TANSYA = '" + IntToStr(CHRNO[i]) + "'" ;
        Form1->Q_STRS->SQL->Add(SQLstr);
        Form1->Q_STRS->Open();
        if( Form1->Q_STRS->Bof == true && Form1->Q_STRS->Eof){
        //if( Form1->Q_STRS->RecordCount > 0 ) {
            str3[i] = " ";
        }
        else {
            Form1->Q_STRS->First();
            str3[i] = Form1->Q_STRS->FieldValues["TANNAM"];
        }
    }


    i = j = n = m = 0;
	UPDCHRstr02 = " ";
    for ( i = 0; i < 12; i++ ) {
    	if ( CHRNO[i] != -1 ) {
		    n = 0;
	        if ( flag[i] == 0 ) {
	            if ( n == 0 ) n = 1;
	            else  UPDCHRstr02 += "/";
	            UPDCHRstr02 += str2[i];
	        }
	        for ( j = i + 1; j < 12; j++ ) {
	            if ( CHRNO[i] == CHRNO[j] ) {
	                if ( flag[j] == 0 ) {
	                    if ( n == 0 ) n = 1;
	                    else  UPDCHRstr02 += "/";
	                    UPDCHRstr02 += str2[j];
	                    flag[j] = 1;
	                }
	            }
	        }
	        if ( flag[i] == 0 ) {
	            UPDCHRstr02 += "=";
	            UPDCHRstr02 += str3[i];
	            UPDCHRstr02 += "  ";

	        }
		}

    }

    m = 0;


}


