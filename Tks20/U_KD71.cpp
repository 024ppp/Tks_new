/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD71.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD71 SQL etc                                        *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
/***********************************************************************
*  function name : void KD71_72Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �ŗL��R���f�[�^�t�@�C������f�[�^�𒊏o            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD71_72Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  �ŗL��R�� KD71
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD71Data.KOYU_MIN = KM01_04Data.KOYU_MIN;
	KD71Data.KOYU_MAX = KM01_04Data.KOYU_MAX;
	KD71Data.KOYU_NM = KM01_04Data.SK_KOYU;
	//KOYU_VAL[100]
	//KOYU_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KD71.SOKUTEI_1T, KD71.SOKUTEI_2T, KD71.SOKUTEI_NM,SOKUTEI_SU, KD71.UPDCHR ";
	str += "FROM KD71 ";
	str += "WHERE  KD71.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD71.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD71.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD71.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD71.KENSA_YMD, KD71.TOLEY_NO, KD71.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//�ŗL��R�� �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1T"])))
		KD71Data.KOYU_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1T"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2T"])))
		KD71Data.KOYU_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2T"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD71Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD71Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD71Data.KOYU_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD71Data.KOYU_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
		str = "SELECT ";
		str += "KD72.SOKUTEI_T, KD72.SOKUTEI_NO ";
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
			//ShowMessage("KD72�Ƀf�[�^������܂���");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_T"])))
					KD71Data.KOYU_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_T"];
				else KD71Data.KOYU_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD71Compare01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �ŗL��R���f�[�^���K�i�����ǂ����𔻒f              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD71Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
    for ( i = 0; i <= KD71Data.KOYU_NM - 1; i++ ) {
        if ( KD71Data.KOYU_MIN <= KD71Data.KOYU_VAL[i]
            &&  KD71Data.KOYU_MAX >= KD71Data.KOYU_VAL[i] ) {
            a = 1;

        }
        else {
            KD71Data.PASS = 0;
            return;
        }
    }
    KD71Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD71Format01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �ŗL��R���f�[�^��������                            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD71Format01(void)
{
    KD71Data.PASS = 0;             	//�ŗL��R�� �������i �s���i
    KD71Data.KOYU_NM = 0;        	//�ŗL��R�� �����f�[�^��
    KD71Data.KOYU_MIN = 0;   	    //�ŗL��R�� �K�i��
    KD71Data.KOYU_MAX = 0;    	 	//�ŗL��R�� �K�i��
    KD71Data.UPDCHR = 0;            //�X�V��
    memset(KD71Data.KOYU_VAL, (int)NULL, sizeof(int) * 100);  //�ŗL��R�� �����f�[�^

}