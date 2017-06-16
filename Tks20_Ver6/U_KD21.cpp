/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD21.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD21 SQL etc                                        *
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
*  function name : void KD21_22Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�c�����f�[�^�t�@�C������f�[�^�𒊏o    *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD21_22Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  �u���V�����@�c���� KD21
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD21Data.BURASIT_MIN = KM01_04Data.BURASIT_MIN;
	KD21Data.BURASIT_MAX = KM01_04Data.BURASIT_MAX;
	KD21Data.BURASIT_NM = KM01_04Data.SK_BURASIT;
	//BURASIT_VAL[100]
	//BURASIT_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KD21.SOKUTEI_1, KD21.SOKUTEI_2, KD21.SOKUTEI_NM,SOKUTEI_SU, KD21.UPDCHR ";
	str += "FROM KD21 ";
	str += "WHERE  KD21.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD21.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD21.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD21.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD21.KENSA_YMD, KD21.TOLEY_NO, KD21.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//�u���V�����@�c���� �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD21Data.BURASIT_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD21Data.BURASIT_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD21Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD21Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD21Data.BURASIT_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD21Data.BURASIT_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
		str = "SELECT ";
		str += "KD22.SOKUTEICHI, KD22.SOKUTEI_NO ";
		str += "FROM KD22 ";
		str += "WHERE  KD22.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD22.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD22.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD22.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD22.KENSA_YMD, KD22.TOLEY_NO, KD22.SAMPLE_P, KD22.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
			//ShowMessage("KD22�Ƀf�[�^������܂���");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {

				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD21Data.BURASIT_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD21Data.BURASIT_VAL[n] = 0;

				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD21Compare01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�c�����f�[�^���K�i�����ǂ����𔻒f            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD21Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
    for ( i = 0; i <= KD21Data.BURASIT_NM - 1; i++ ) {
        if ( KD21Data.BURASIT_MIN <= KD21Data.BURASIT_VAL[i]
            &&  KD21Data.BURASIT_MAX >= KD21Data.BURASIT_VAL[i] ) {
            a = 1;

        }
        else {
            KD21Data.PASS = 0;
            return;
        }
    }
    KD21Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD21Format01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�c�����f�[�^��������                          *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD21Format01(void)
{
    KD21Data.PASS = 0;             	//�u���V�����@�c���� �������i �s���i
    KD21Data.BURASIT_NM = 0;        	//�u���V�����@�c���� �����f�[�^��
    KD21Data.BURASIT_MIN = 0;   	    //�u���V�����@�c���� �K�i��
    KD21Data.BURASIT_MAX = 0;     	//�u���V�����@�c���� �K�i��
    KD21Data.UPDCHR = 0;            //�X�V��
    memset(KD21Data.BURASIT_VAL, (int)NULL, sizeof(double) * 100);  //�u���V�����@�c���� �����f�[�^

}