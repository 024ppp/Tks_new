/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KD11.cpp                                          *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : KD11 SQL etc                                        *
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
*  function name : void KD11_12Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�f�[�^�t�@�C������f�[�^�𒊏o          *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD11_12Serch01(void)
{
	int i,n;
	AnsiString str;
	char str_c[256];
	char strVal_c[256];
	AnsiString tableNo;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//Q_Work pass  �u���V�����@ KD11
	//�����l�̌���
	strVal01 = KM01_04Data.KENSA_YMD;
	strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
	strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	KD11Data.BURASI_MIN = KM01_04Data.BURASI_MIN;
	KD11Data.BURASI_MAX = KM01_04Data.BURASI_MAX;
	KD11Data.BURASI_NM = KM01_04Data.SK_BURASI;
	//BURASI_VAL[100]
	//BURASI_NM

	Form1->Q_Work->Close();
	Form1->Q_Work->SQL->Clear();
	//�₢���������s
	//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KD11.SOKUTEI_1, KD11.SOKUTEI_2, KD11.SOKUTEI_NM,SOKUTEI_SU,KD11.UPDCHR ";
	str += "FROM KD11 ";
	str += "WHERE  KD11.KENSA_YMD = '" + strVal01 + "' ";
	str += "AND  KD11.TOLEY_NO = '" + strVal02 + "' ";
	str += "AND  KD11.SAMPLE_P = '" + strVal03 + "' ";
        //20161021 Y.Onishi
        str += " AND KD11.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
	str += "ORDER BY KD11.KENSA_YMD, KD11.TOLEY_NO, KD11.SAMPLE_P";

	Form1->Q_Work->SQL->Add(str);
	Form1->Q_Work->Open();
	//�u���V�����@ �����l�A�������A�X�V��
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_1"])))
		KD11Data.BURASI_VAL[0] = Form1->Q_Work->FieldValues["SOKUTEI_1"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_2"])))
		KD11Data.BURASI_VAL[1] = Form1->Q_Work->FieldValues["SOKUTEI_2"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["UPDCHR"])))
		KD11Data.UPDCHR = Form1->Q_Work->FieldValues["UPDCHR"];
	if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_SU"])))
		KD11Data.SOKUTEI_SU = Form1->Q_Work->FieldValues["SOKUTEI_SU"];
	//KD11Data.BURASI_NM = vardouble(Form1->Q_Work->FieldValues["SOKUTEI_NM"]);

	//�������̃`�F�b�N
	if ( KD11Data.BURASI_NM > 2 ) {
		i = 0;
		Form1->Q_Work->Close();
		Form1->Q_Work->SQL->Clear();
		//�₢���������s
		//�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
		str = "SELECT ";
		str += "KD12.SOKUTEICHI, KD12.SOKUTEI_NO ";
		str += "FROM KD12 ";
		str += "WHERE  KD12.KENSA_YMD = '" + strVal01 + "' ";
		str += "AND  KD12.TOLEY_NO = '" + strVal02 + "' ";
		str += "AND  KD12.SAMPLE_P = '" + strVal03 + "' ";
                //20161021 Y.Onishi
                str += " AND KD12.KOJOKBN = " + IntToStr(KM01_04Data.KOJOKBN) + " ";
		str += "ORDER BY KD12.KENSA_YMD, KD12.TOLEY_NO, KD12.SAMPLE_P, KD12.SOKUTEI_NO";

		Form1->Q_Work->SQL->Add(str);
		Form1->Q_Work->Open();

		if ( Form1->Q_Work->Bof == true &&  Form1->Q_Work->Eof == true) {
		    //ShowMessage("KD12�Ƀf�[�^������܂���");
		}
		else {
			Form1->Q_Work->First();
			while( !Form1->Q_Work->Eof ) {
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEI_NO"])))
					n = Form1->Q_Work->FieldValues["SOKUTEI_NO"] - 1;
				else n = 0;
				if ( !(VarIsNull ( Form1->Q_Work->FieldValues["SOKUTEICHI"])))
					KD11Data.BURASI_VAL[n] = Form1->Q_Work->FieldValues["SOKUTEICHI"];
				else KD11Data.BURASI_VAL[n] = 0;
				Form1->Q_Work->Next();
			}

		}


	}


}

/***********************************************************************
*  function name : void KD11Compare01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�f�[�^���K�i�����ǂ����𔻒f            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD11Compare01(void)
{
    int i;
    int a;
    //0 : �s���i   1 : ���i
    for ( i = 0; i <= KD11Data.BURASI_NM - 1; i++ ) {
        if ( KD11Data.BURASI_MIN <= KD11Data.BURASI_VAL[i]
            &&  KD11Data.BURASI_MAX >= KD11Data.BURASI_VAL[i] ) {
            a = 1;

        }
        else {
            KD11Data.PASS = 0;
            return;
        }
    }
    KD11Data.PASS = 1;
}

/***********************************************************************
*  function name : void KD11Format01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�f�[�^��������                          *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KD11Format01(void)
{
    KD11Data.PASS = 0;             	//�u���V�����@ �������i �s���i
    KD11Data.BURASI_NM = 0;        	//�u���V�����@ �����f�[�^��
    KD11Data.BURASI_MIN = 0;   	    //�u���V�����@ �K�i��
    KD11Data.BURASI_MAX = 0;     	//�u���V�����@ �K�i��
    KD11Data.UPDCHR = 0;            //�X�V��
    memset(KD11Data.BURASI_VAL, (int)NULL, sizeof(double) * 100);  //�u���V�����@ �����f�[�^

}