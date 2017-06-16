/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : Unit3.cpp                                           *
*  create        : 2000.01.07                                          *
*  update        : 2002.02.26(���������ǉ��F������)                    *
*  contents      : �f�[�^�������v���O����                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop


#include "Unit1.h"
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//����MAIN
int __fastcall TForm1::Search_MAIN(void)
{
	int n;
    int flag;

    flag = 0;

    //KD01 ���[�h���������@ ����
	//n = Search_KD(0);
    if ( n > 0 || flag > 0 ) flag = 1;

    return ( flag );

}
//---------------------------------------------------------------------------
//�w�肳�ꂽ�������ڂ̃f�[�^������
//testItem�i�������ځj
int __fastcall TForm1::Search_KD(int testItem)
{
	int iRow,i;
	AnsiString sBuf;

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s
	//���� KD01����
	switch(testItem)
	{

		case  0: //���[�h������
			sBuf = "SELECT *  FROM KD01";
			break;

		case  1: //�u���V��
			sBuf = "SELECT *  FROM KD11";
			break;

		case  2: //�u���V��(�c����)
			sBuf = "SELECT *  FROM KD21";
			break;

		case  3: //���[�h����t��R
			sBuf = "SELECT *  FROM KD31";
			break;

		case  4: //���[�h����t���x
			sBuf = "SELECT *  FROM KD41";
			break;

		case  5: //���|��d
			sBuf = "SELECT *  FROM KD51";
			break;

		case  6: //�d�x(HsC ����)
			sBuf = "SELECT *  FROM KD61";
			break;

		case  7: //�d�x(HsC ����)
			sBuf = "SELECT *  FROM KD61";
			break;

		case  8: //�d�x(HsD ����)
			sBuf = "SELECT *  FROM KD61";
			break;

		case  9: //�d�x(HsD ����)
			sBuf = "SELECT *  FROM KD61";
			break;

		case 10: //��R��
		case 14: //��R��(L) //2002/12/07 E.Takase
		case 15: //��R��(R) //2002/12/07 E.Takase
			sBuf = "SELECT *  FROM KD71";
			break;

		case 11: //�Ȃ�����
			sBuf = "SELECT *  FROM KD81";
			break;

		case 12: //����
			sBuf = "SELECT *  FROM KD91";
			break;

		case 13: //�Ȃ�����(����)  //2002/12/07 E.Takase
			sBuf = "SELECT *  FROM KDC1";
			break;

    }

    //Where����
    //���Ӑ�i��
	sBuf += " where DTKSHIN = '" + EdtTKSHIN->Text + "'";
    //�J�n���b�g�ԍ��i�󔒂̏ꍇ�͎w�肵�Ȃ��j
    if ( EdtSLOT->Text != "" ) {
		sBuf += " AND LOTNO >= '" + EdtSLOT->Text + "'";
    }
    //�I�����b�g�ԍ��i�󔒂̏ꍇ�͎w�肵�Ȃ��j
    if ( EdtELOT->Text != "" ) {
		sBuf += " AND LOTNO <= '" + EdtELOT->Text + "'";
    }

    //2002/02/26�ǉ�
    //�J�n���i�󔒂̏ꍇ�͎w�肵�Ȃ��j
    if ( EdtSYMD->Text != "" ) {
		sBuf += " AND KENSA_YMD >= '" + DelSEPA(EdtSYMD->Text) + "'";
    }
    //�I�����i�󔒂̏ꍇ�͎w�肵�Ȃ��j
    if ( EdtEYMD->Text != "" ) {
		sBuf += " AND KENSA_YMD <= '" + DelSEPA(EdtEYMD->Text) + "'";
    }

	switch(testItem)
	{
		case  0: //���[�h������
		case  1: //�u���V��
		case  2: //�u���V��(�c����)
		case  3: //���[�h����t��R
		case  4: //���[�h����t���x
		case  5: //���|��d
		case 10: //��R��
		case 11: //�Ȃ�����
		case 12: //����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
		case 14: //��R��(L) //2002/12/07 E.Takase
		case 15: //��R��(R) //2002/12/07 E.Takase
			sBuf += " AND SOKUTEI_SU > 0";
			sBuf += " AND SOKUTE_KBN = 1";
			break;

		case  6: //�d�x(HsC ����)
			sBuf += " AND HSC_SK_SU > 0";
			sBuf += " AND ( SOKUTE_KBN1 = 1 OR SOKUTE_KBN1 = 3 )";
			break;

		case  7: //�d�x(HsC ����)
			sBuf += " AND HSC_SK_SU > 0";
			sBuf += " AND ( SOKUTE_KBN1 = 2 OR SOKUTE_KBN1 = 3 )";
			break;

		case  8: //�d�x(HsD ����)
			sBuf += " AND HSD_SK_SU > 0";
			sBuf += " AND ( SOKUTE_KBN2 = 1 OR SOKUTE_KBN2 = 3 )";
			break;

		case  9: //�d�x(HsD ����)
			sBuf += " AND HSD_SK_SU > 0";
			sBuf += " AND ( SOKUTE_KBN2 = 2 OR SOKUTE_KBN2 = 3 )";
			break;
    }
    //sBuf += " AND SOKUTE_KBN = 1";

    //20160704�ǉ�
    if ( Form1->RadioHON->Checked == true ) {
        //�{�Ђ̂�
    	sBuf += " AND KOJOKBN = 0";
    } else if ( Form1->RadioKOU->Checked == true ) {
        //�L�z�̂�
    	sBuf += " AND KOJOKBN = 1";
    } else if ( Form1->RadioRYO->Checked == true ) {
        //Nothing
    } else {
        //Nothing
    }

    //2000.11.07�C�� �������Ń\�[�g OR ���b�gNO�Ń\�[�g
    if ( Form1->RadioKANSA->Checked == true ) {
		sBuf += " order by KENSA_YMD,LOTNO";
    } else {
		sBuf += " order by LOTNO,KENSA_YMD";
    }

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//�������� �O��
		return(0);
	}
    return(1);

}

//---------------------------------------------------------------------------
//1�s���̃f�[�^��ǂݍ���
//testItem�i�������ځj
void __fastcall TForm1::ReadLineData(int testItem)
{
	AnsiString sBuf;

	//�����z��̏�����
	KD.KENSA_YMD	 = " ";		// ������
	KD.DTKSHIN		 = " ";     // ���Ӑ�i��
	KD.LOTNO		 = " ";    	// ���b�gNo
	KD.ZISNAM		 = " ";     // �ގ���
	KD.KIKAK_MIN	 = 0.0;     // �����K�i
	KD.KIKAK_MAX	 = 0.0;     // ����K�i
	KD.SOKUTE_SU	 = 0;       // ���萔
	KD.SOKUTE_NM	 = 0;       // ����w����
	KD.SOKUTEI_1	 = 0.0;     // ����l1
	KD.SOKUTEI_2	 = 0.0;     // ����l2
	KD.X_AVE		 = 0.0;     // X���ϒl
	KD.R			 = 0.0;     // R
	KD.TANI			 = 0.0;     // �P��

	sBuf = Form1->Query1->FieldValues["KENSA_YMD"];
	KD.KENSA_YMD = sBuf;							// ������

	sBuf = Form1->Query1->FieldValues["DTKSHIN"];
	KD.DTKSHIN = sBuf;      						// ���Ӑ�i��

	sBuf = Form1->Query1->FieldValues["LOTNO"];
	KD.LOTNO = sBuf;    							// ���b�gNo

	sBuf = Form1->Query1->FieldValues["ZISNAM"];
	KD.ZISNAM = sBuf;       						// �ގ���

    //���ڂɂ���Ă� �P�ʂ��K�v
	switch(testItem)
	{

		case  0: //���[�h������
			sBuf = Form1->Query1->FieldValues["LD_LNG_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["LD_LNG_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  1: //�u���V��
			sBuf = Form1->Query1->FieldValues["BURASI_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["BURASI_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  2: //�u���V��(�c����)
			sBuf = Form1->Query1->FieldValues["BURASIT_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["BURASIT_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  3: //���[�h����t��R
			sBuf = Form1->Query1->FieldValues["LD_TR_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  4: //���[�h����t���x
			sBuf = Form1->Query1->FieldValues["LD_HP_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			sBuf = Form1->Query1->FieldValues["LD_HP_TAN"];
			KD.TANI = StrToInt(sBuf);    					// �P��

			break;

		case  5: //���|��d
			sBuf = Form1->Query1->FieldValues["BOTAI_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["BOTAI_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1B"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2B"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  6: //�d�x(HsC ����)
			sBuf = Form1->Query1->FieldValues["HSC_A_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["HSC_A_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["HSC_A_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["HSC_A_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  7: //�d�x(HsC ����)
			sBuf = Form1->Query1->FieldValues["HSC_S_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["HSC_S_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["HSC_S_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["HSC_S_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  8: //�d�x(HsD ����)
			sBuf = Form1->Query1->FieldValues["HSD_A_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["HSD_A_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["HSD_A_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["HSD_A_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case  9: //�d�x(HsD ����)
			sBuf = Form1->Query1->FieldValues["HSD_S_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["HSD_S_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["HSD_S_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["HSD_S_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case 10: //��R��
			sBuf = Form1->Query1->FieldValues["KOYU_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["KOYU_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1T"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2T"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;

		case 11: //�Ȃ�����
			sBuf = Form1->Query1->FieldValues["MAGE_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["MAGE_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1M"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2M"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2
			sBuf = Form1->Query1->FieldValues["MAGE_TAN"];
			KD.TANI = StrToInt(sBuf);    					// �P��

			break;

		case 12: //����
			sBuf = Form1->Query1->FieldValues["ZAKUT_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["ZAKUT_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;
        //2002/12/07 E.Takase
		case 13: //�Ȃ�����(����)
			sBuf = Form1->Query1->FieldValues["MAGEG_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["MAGEG_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEI_1M"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEI_2M"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2
			sBuf = Form1->Query1->FieldValues["MAGEG_TAN"];
			KD.TANI = StrToInt(sBuf);    					// �P��

			break;

		//2002/12/07 E.Takase
		case 14: //��R��(L) 
			sBuf = Form1->Query1->FieldValues["KOYU_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["KOYU_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEV_1L"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEV_2L"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;
            
		//2002/12/07 E.Takase
		case 15: //��R��(R) 
			sBuf = Form1->Query1->FieldValues["KOYU_MIN"];
			KD.KIKAK_MIN = StrToFloat(sBuf);    			// �����K�i

			sBuf = Form1->Query1->FieldValues["KOYU_MAX"];
			KD.KIKAK_MAX = StrToFloat(sBuf);    			// ����K�i

			sBuf = Form1->Query1->FieldValues["SOKUTEV_1R"];
			KD.SOKUTEI_1 = StrToFloat(sBuf);    			// ����l1

			sBuf = Form1->Query1->FieldValues["SOKUTEV_2R"];
			KD.SOKUTEI_2 = StrToFloat(sBuf);    			// ����l2

			break;



	}

    //X���ϒl
    KD.X_AVE = ( KD.SOKUTEI_1 + KD.SOKUTEI_2 ) / 2.0;
    //R
    if ( KD.SOKUTEI_1 > KD.SOKUTEI_2 ) {
		KD.R = KD.SOKUTEI_1 - KD.SOKUTEI_2;
    } else {
		KD.R = KD.SOKUTEI_2 - KD.SOKUTEI_1;
    }

}
