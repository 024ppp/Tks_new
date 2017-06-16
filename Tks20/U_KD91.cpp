/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD91.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD91 SQL etc                                        *
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
*  function name : void KD91_92Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �����f�[�^�t�@�C������f�[�^�𒊏o                  *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD91_92Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  ���� KD91
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD91Data.ZAKUT_MIN = KM01_04Data.ZAKUT_MIN;
	KD91Data.ZAKUT_MAX = KM01_04Data.ZAKUT_MAX;
	KD91Data.ZAKUT_NM = KM01_04Data.SK_ZAKUT;
	//ZAKUT_VAL[100]
	//ZAKUT_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KD91.SOKUTEI_1, KD91.SOKUTEI_2, KD91.SOKUTEI_NM,SOKUTEI_SU, KD91.UPDCHR ";
	str += "FROM KD91 ";
	str += "WHERE  KD91.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD91.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD91.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD91.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD91.KENSA_YMD, KD91.TOLEY_NO, KD91.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//���� �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD91Data.ZAKUT_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD91Data.ZAKUT_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD91Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD91Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD91Data.ZAKUT_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD91Data.ZAKUT_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
		str = "SELECT ";
		str += "KD92.SOKUTEICHI, KD92.SOKUTEI_NO ";
		str += "FROM KD92 ";
		str += "WHERE  KD92.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD92.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD92.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD92.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD92.KENSA_YMD, KD92.TOLEY_NO, KD92.SAMPLE_P, KD92.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD92�Ƀf�[�^������܂���");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD91Data.ZAKUT_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD91Data.ZAKUT_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD91Compare01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �����f�[�^���K�i�����ǂ����𔻒f                    *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD91Compare01(void)
{
    int a;
    int i;
    //0 : �s���i   1 : ���i
    for ( i = 0; i <= KD91Data.ZAKUT_NM - 1; i++ ) {
        if ( KD91Data.ZAKUT_MIN <= KD91Data.ZAKUT_VAL[i]
            &&  KD91Data.ZAKUT_MAX >= KD91Data.ZAKUT_VAL[i] ) {
            a = 1;

        }
        else {
            KD91Data.PASS = 0;
            return;
        }
    }
    KD91Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD91Format01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �����f�[�^��������                                  *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD91Format01(void)
{
    KD91Data.PASS = 0;             	//���� �������i �s���i
    KD91Data.ZAKUT_NM = 0;        	//���� �����f�[�^��
    KD91Data.ZAKUT_MIN = 0;   	    //���� �K�i��
    KD91Data.ZAKUT_MAX = 0;       	//���� �K�i��
    KD91Data.UPDCHR = 0;            //�X�V��
    memset(KD91Data.ZAKUT_VAL, (int)NULL, sizeof(int) * 100);  //���� �����f�[�^
}