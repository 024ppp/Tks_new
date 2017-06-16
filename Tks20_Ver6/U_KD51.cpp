/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD51.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD51 SQL etc                                        *
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
*  function name : void KD51_52Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ��̔�d�f�[�^�t�@�C������f�[�^�𒊏o              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD51_52Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  ��̔�d KD51
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD51Data.BOTAI_MIN = KM01_04Data.BOTAI_MIN;
	KD51Data.BOTAI_MAX = KM01_04Data.BOTAI_MAX;
	KD51Data.BOTAI_NM = KM01_04Data.SK_BOTAI;
	//BOTAI_VAL[100]
	//BOTAI_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KD51.SOKUTEI_1B, KD51.SOKUTEI_2B, KD51.SOKUTEI_NM,SOKUTEI_SU, KD51.UPDCHR ";
	str += "FROM KD51 ";
	str += "WHERE  KD51.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD51.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD51.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD51.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//��̔�d �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1B"])))
		KD51Data.BOTAI_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1B"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2B"])))
		KD51Data.BOTAI_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2B"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD51Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD51Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD51Data.BOTAI_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD51Data.BOTAI_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
		str = "SELECT ";
		str += "KD52.SOKUTEI_B, KD52.SOKUTEI_NO ";
		str += "FROM KD52 ";
		str += "WHERE  KD52.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD52.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD52.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD52.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD52.KENSA_YMD, KD52.TOLEY_NO, KD52.SAMPLE_P, KD52.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD52�Ƀf�[�^������܂���");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_B"])))
					KD51Data.BOTAI_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEI_B"];
				else KD51Data.BOTAI_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD51Compare01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ��̔�d�f�[�^���K�i�����ǂ����𔻒f                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD51Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
    for ( i = 0; i <= KD51Data.BOTAI_NM - 1; i++ ) {
        if ( KD51Data.BOTAI_MIN <= KD51Data.BOTAI_VAL[i]
            &&  KD51Data.BOTAI_MAX >= KD51Data.BOTAI_VAL[i] ) {
            a = 1;

        }
        else {
            KD51Data.PASS = 0;
            return;
        }
    }
    KD51Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD51Format01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ��̔�d�f�[�^��������                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD51Format01(void)
{
    KD51Data.PASS = 0;             	//��̔�d �������i �s���i
    KD51Data.BOTAI_NM = 0;         	//��̔�d �����f�[�^��
    KD51Data.BOTAI_MIN = 0;   	    //��̔�d �K�i��
    KD51Data.BOTAI_MAX = 0;     	//��̔�d �K�i��
    KD51Data.UPDCHR = 0;            //�X�V��
    memset(KD51Data.BOTAI_VAL, (int)NULL, sizeof(double) * 100);  //��̔�d �����f�[�^

}