/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD41.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD41 SQL etc                                        *
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
*  function name : void KD41_42Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x�f�[�^�t�@�C������f�[�^�𒊏o      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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

	//Q_Work pass  ���[�h���������x KD41
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD41Data.LD_HP_MIN = KM01_04Data.LD_HP_KYO;
	KD41Data.LD_HP_NM = KM01_04Data.SK_LD_HP;
	//LD_HP_VAL[100]
	//LD_HP_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
	//���[�h���������x �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD41Data.LD_HP_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD41Data.LD_HP_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD41Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD41Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD41Data.LD_HP_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD41Data.LD_HP_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
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
			//ShowMessage("KD42�Ƀf�[�^������܂���");
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x�f�[�^���K�i�����ǂ����𔻒f        *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD41Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
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
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x�f�[�^��������                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD41Format01(void)
{
    KD41Data.PASS = 0;             	//���[�h���������x �������i �s���i
    KD41Data.LD_HP_NM = 0;        	//���[�h���������x �����f�[�^��
    KD41Data.LD_HP_MIN = 0;   	    //���[�h���������x �K�i��
    KD41Data.UPDCHR = 0;            //�X�V��
    memset(KD41Data.LD_HP_VAL, (int)NULL, sizeof(int) * 100);  //���[�h���������x �����f�[�^

}

