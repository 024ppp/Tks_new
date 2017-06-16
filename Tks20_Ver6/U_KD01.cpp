/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD01.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD01 SQL etc                                        *
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
*  function name : void KD01_02Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h�������f�[�^�t�@�C������f�[�^�𒊏o          *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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

	//Q_Work pass  ���[�h������ KD01
	//�����l�̌���
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
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
	//���[�h������ �����l�A�������A�X�V��

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD01Data.LD_LNG_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD01Data.LD_LNG_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD01Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];

	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD01Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];

	//�������̃`�F�b�N
	if ( KD01Data.LD_LNG_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
		    //ShowMessage("KD02�Ƀf�[�^������܂���");
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h�������f�[�^���K�i�����ǂ����𔻒f            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD01Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h�������f�[�^��������                          *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD01Format01(void)
{

    KD01Data.PASS = 0;             	//���[�h������ �������i �s���i
    KD01Data.LD_LNG_NM = 0;        	//���[�h������ �����f�[�^��
    KD01Data.LD_LNG_MIN = 0;   	    //���[�h������ �K�i��
    KD01Data.LD_LNG_MAX = 0;     	//���[�h������ �K�i��
    KD01Data.UPDCHR = 0;            //�X�V��

    memset(KD01Data.LD_LNG_VAL, (int)NULL, sizeof(double) * 100);  //���[�h������ �����f�[�^

}