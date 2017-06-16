/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD31.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD31 SQL etc                                        *
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
*  function name : void KD31_32Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h����t��R�f�[�^�t�@�C������f�[�^�𒊏o      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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

	//Q_Work pass  ���[�h����t��R KD31
	//�����l�̌���
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
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
	//���[�h����t��R �����l�A�������A�X�V��

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

	//�������̃`�F�b�N
	if ( KD31Data.LD_TR_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
			//ShowMessage("KD32�Ƀf�[�^������܂���");
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h����t��R�f�[�^���K�i�����ǂ����𔻒f        *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD31Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h����t��R�f�[�^��������                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD31Format01(void)
{
    KD31Data.PASS = 0;             	//���[�h����t��R �������i �s���i
    KD31Data.LD_TR_NM = 0;        	//���[�h����t��R �����f�[�^��
    KD31Data.LD_TR_DEN = 0;    		//���[�h����t��R ����d��
    KD31Data.LD_TR_TIME = 0;   	  	//���[�h����t��R ���莞��
    KD31Data.LD_TR_TEKO = 0;   	  	//���[�h����t��R ����d��
    KD31Data.UPDCHR = 0;            //�X�V��
    memset(KD31Data.LD_TRV_VAL, (int)NULL, sizeof(double) * 100);	//���[�h����t��R ����d�� �����f�[�^
    memset(KD31Data.LD_TRA_VAL, (int)NULL, sizeof(double) * 100); 	//���[�h����t��R ����d�� �����f�[�^
    memset(KD31Data.LD_TRR_VAL, (int)NULL, sizeof(double) * 100); 	//���[�h����t��R �����R �����f�[�^
}