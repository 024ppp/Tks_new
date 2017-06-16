/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_KM0104.cpp                                        *
*  create        : 1999.10.19                                          *
*  update        :                                                     *
*  contents      : KM01_04 SQL etc                                     *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
/***********************************************************************
*  function name : void DataNoSet(void)                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.12.05 E.Takase �R���~�p�̏����ǉ�              *
*  contents      : �ő呪��f�[�^������                                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void DataNoSet(void)
{
    DataNo = 2;

    if ( DataNo < KM01_04Data.SK_LD_LNG ) DataNo = KM01_04Data.SK_LD_LNG;
    if ( DataNo < KM01_04Data.SK_BURASI ) DataNo = KM01_04Data.SK_BURASI;
    if ( DataNo < KM01_04Data.SK_BURASIT ) DataNo = KM01_04Data.SK_BURASIT;
    if ( DataNo < KM01_04Data.SK_BOTAI ) DataNo = KM01_04Data.SK_BOTAI;
    if ( DataNo < KM01_04Data.SK_KOYU ) DataNo = KM01_04Data.SK_KOYU;
    if ( DataNo < KM01_04Data.SK_MAGE ) DataNo = KM01_04Data.SK_MAGE;
    if ( DataNo < KM01_04Data.SK_HSC_A ) DataNo = KM01_04Data.SK_HSC_A;
    if ( DataNo < KM01_04Data.SK_HSC_S ) DataNo = KM01_04Data.SK_HSC_S;
    if ( DataNo < KM01_04Data.SK_HSD_A ) DataNo = KM01_04Data.SK_HSD_A;
    if ( DataNo < KM01_04Data.SK_HSD_S ) DataNo = KM01_04Data.SK_HSD_S;
    if ( DataNo < KM01_04Data.SK_ZAKUT ) DataNo = KM01_04Data.SK_ZAKUT;

    if ( Flagcnd == 0 || Flagcnd == 1 ) {
        if ( DataNo < KM01_04Data.SK_LD_TR ) DataNo = KM01_04Data.SK_LD_TR;
        if ( DataNo < KM01_04Data.SK_LD_HP ) DataNo = KM01_04Data.SK_LD_HP;
    } else {
        if ( DataNo < KM01_04Data.SK_MAGEG ) DataNo = KM01_04Data.SK_MAGEG;
    }

    if ( Flagcnd == 0 || Flagcnd == 1 ) {
        if ( KM01_04Data.SK_LD_LNG == 0 &&
				KM01_04Data.SK_BURASI == 0 &&
				KM01_04Data.SK_BURASIT == 0 &&
				KM01_04Data.SK_LD_TR == 0 &&
				KM01_04Data.SK_LD_HP == 0 &&
				KM01_04Data.SK_BOTAI == 0 &&
				KM01_04Data.SK_KOYU  == 0 &&
				KM01_04Data.SK_MAGE  == 0 &&
				KM01_04Data.SK_HSC_A == 0 &&
				KM01_04Data.SK_HSC_S == 0 &&
				KM01_04Data.SK_HSD_A == 0 &&
				KM01_04Data.SK_HSD_S == 0 &&
				KM01_04Data.SK_ZAKUT == 0	) DataNo = -1;
    } else {
        if ( KM01_04Data.SK_LD_LNG == 0 &&
				KM01_04Data.SK_BURASI == 0 &&
				KM01_04Data.SK_BURASIT == 0 &&
				KM01_04Data.SK_BOTAI == 0 &&
				KM01_04Data.SK_KOYU  == 0 &&
				KM01_04Data.SK_MAGE  == 0 &&
				KM01_04Data.SK_MAGEG == 0 &&
				KM01_04Data.SK_HSC_A == 0 &&
				KM01_04Data.SK_HSC_S == 0 &&
				KM01_04Data.SK_HSD_A == 0 &&
				KM01_04Data.SK_HSD_S == 0 &&
				KM01_04Data.SK_ZAKUT == 0	) DataNo = -1;
    }



}

/***********************************************************************
*  function name : void PassSet(void)                                  *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.12.05 E.Takase �R���~�p�̏����ǉ�              *
*  contents      : ���i���s���i��������                                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void PassSet(void)
{
    if ( Flagcnd == 0 || Flagcnd == 1 ) {
       if ( KD01Data.PASS == 0 ||  KD11Data.PASS == 0 || KD21Data.PASS == 0 ||
            KD31Data.PASS == 0 ||  KD41Data.PASS == 0 || KD51Data.PASS == 0 ||
            KD61Data.PASS == 0 ||  KD71Data.PASS == 0 || KD81Data.PASS == 0 ||
            KD91Data.PASS == 0   ) {
          pass = 0;
          } else {
            pass = 1;
          }
     } else {
       if ( KD01Data.PASS == 0 ||  KD11Data.PASS == 0 || KD21Data.PASS == 0 ||
            KD51Data.PASS == 0 ||  KD61Data.PASS == 0 || KD81Data.PASS == 0 ||
            KD71Data_L.PASS == 0 || KD71Data_R.PASS == 0 || KDC1Data.PASS == 0 ||
            KD91Data.PASS == 0   ) {
          pass = 0;
          } else {
            pass = 1;
          }
     }

}

/***********************************************************************
*  function name : void KM01_04Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.12.06 E.Takase �����Ȃ��A��R��L�ER�ǉ�        *
*  contents      : �����w���}�X�^����}�X�^�f�[�^�𒊏o                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KM01_04Serch01(void)
{
    AnsiString str;

    //�����w���}�X�^����}�X�^�f�[�^�𒊏o
    Form1->Q_KM01->Close();
    Form1->Q_KM01->SQL->Clear();
    //�₢���������s
    //�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	str = "SELECT ";
	str += "KM01.KENSA_YMD, KM01.TOLEY_NO, KM01.SAMPLE_P, KM01.KOKBNG, ";
	str += "KM01.DTKSCOD, KM01.DTKSHIN, KM01.LOTNO, KM01.HINBAN, ";
	str += "KM01.ZISCOD, KM01.ZISNAM, KM01.SYOSCOD, ";
	str += "KM01.NUM, KM01.SORTKEY, KM01.KEIJKBN, KM01.SK_LD_LNG, ";
	str += "KM01.SK_BURASI, KM01.SK_BURASIT, KM01.SK_LD_TR, KM01.SK_LD_HP, ";
	str += "KM01.SK_BOTAI, KM01.SK_KOYU, KM01.SK_MAGE, KM01.SK_HSC_A, ";
	str += "KM01.SK_HSC_S, KM01.SK_HSD_A, KM01.SK_HSD_S, KM01.HIST_SOKUT, ";
	str += "KM01.SK_ZAKUT, ";
	str += "KM01.HIST_KIKAK, KM01.HIST_MIN, KM01.HIST_MAX, KM01.LD_LNG_MIN, ";
	str += "KM01.LD_LNG_MAX, KM01.BURASI_MIN, KM01.BURASI_MAX, KM01.BURASIT_MIN, ";
	str += "KM01.BURASIT_MAX, KM01.LD_TR_DENA,KM01.LD_TR_DENR, KM01.LD_TR_TIME, ";
	str += "KM01.LD_HP_SPD, KM01.LD_HP_KYO, KM01.LD_HP_TAN, KM01.BOTAI_MIN, ";
	str += "KM01.BOTAI_MAX, KM01.KOYU_MIN, KM01.KOYU_MAX, KM01.KOYU_DEN, ";
	str += "KM01.KOYU_PRO, KM01.MAGE_MIN, KM01.MAGE_MAX, KM01.MAGE_TAN, ";
	str += "KM01.MAGE_SPAN, KM01.HSC_A_MIN, KM01.HSC_A_MAX, KM01.HSC_S_MIN, ";
	str += "KM01.HSC_S_MAX, KM01.HSD_A_MIN, KM01.HSD_A_MAX, KM01.HSD_S_MIN, ";
	str += "KM01.ZAKUT_MAX, KM01.ZAKUT_MIN, ";
	str += "KM01.HSD_S_MAX, KM01.ADDYMD, KM01.ADDTIM, KM01.UPDYMD, KM01.UPDTIM, ";
	str += "KM01.UPDCHR, KM01.UPDCNT, ";
	str += "KM04.RO_NO, KM04.MAX_ONDO, KM04.CYCLE_TIME, ";
    //2002/12/05 E.Takase
	str += "KM01.SK_MAGEG, KM01.MAGEG_MIN, KM01.MAGEG_MAX, KM01.MAGEG_TAN, KM01.MAGEG_SPAN ";
        //20161024 Y.Onishi �H��敪�ǉ�
        str += ", KM01.KOJOKBN ";

	str += "FROM KM01, KM04 ";
	str += "WHERE  (KM01.SYOSCOD = KM04.SYOSEI_CD (+))  ";
    if ( Flagcnd == 0 ) {
    //��������
	    str += "and KM01.KENSA_YMD = '" + strcnd + "' ";
	    if ( Trim(DTKSCODcnd) != "") str += "and KM01.DTKSCOD = '" + DTKSCODcnd + "' ";

    }
    if ( Flagcnd == 1 ) {
    //���Ӑ�i�ԕ�
	    if ( Trim(DTKSHINcnd) != "") str += "and KM01.DTKSHIN = '" + DTKSHINcnd + "' ";
	    if ( Trim(StartLOTcnd) != "") str += "and KM01.LOTNO >= '" + StartLOTcnd + "' ";
	    if ( Trim(EndLOTcnd) != "") str += "and KM01.LOTNO <= '" +EndLOTcnd + "' ";
	    if ( Trim(strcnd) != "") str += "and KM01.KENSA_YMD >= '" + strcnd + "' ";
	    if ( Trim(strcnd2) != "") str += "and KM01.KENSA_YMD <= '" +strcnd2 + "' ";
    }
    //2002.12.06 E.Takase �R���~����p
    if ( Flagcnd == 2 ) {
    //��������
	    str += "and KM01.KENSA_YMD = '" + strcnd + "' ";
	    if ( Trim(DTKSCODcnd) != "") str += "and KM01.DTKSCOD = '" + DTKSCODcnd + "' ";
	    str += "and KM01.KEIJKBN = 5 ";

    }
    if ( Flagcnd == 3 ) {
    //���Ӑ�i�ԕ�
	    str += "and KM01.KEIJKBN = 5 ";
	    if ( Trim(DTKSHINcnd) != "") str += "and KM01.DTKSHIN = '" + DTKSHINcnd + "' ";
	    if ( Trim(StartLOTcnd) != "") str += "and KM01.LOTNO >= '" + StartLOTcnd + "' ";
	    if ( Trim(EndLOTcnd) != "") str += "and KM01.LOTNO <= '" +EndLOTcnd + "' ";
	    if ( Trim(strcnd) != "") str += "and KM01.KENSA_YMD >= '" + strcnd + "' ";
	    if ( Trim(strcnd2) != "") str += "and KM01.KENSA_YMD <= '" +strcnd2 + "' ";
    }

    //20161021 Y.Onishi
    //����ΏۑI����ǉ�
    if ( Form1->RadioHON->Checked == true ) {
        //�{�Ђ̂�
    	str += " AND KM01.KOJOKBN = 0 ";
    } else if ( Form1->RadioKOU->Checked == true ) {
        //�L�z�̂�
    	str += " AND KM01.KOJOKBN = 1 ";
    } else if ( Form1->RadioRYO->Checked == true ) {
        //Nothing
    } else {
        //Nothing
    }

    //str += "ORDER BY KM01.KENSA_YMD,KM01.DTKSCOD, KM01.DTKSHIN, KM01.LOTNO";
    str += "ORDER BY KM01.KENSA_YMD,KM01.DTKSCOD, KM01.DTKSHIN, KM01.LOTNO, KM01.KOJOKBN";

    Form1->Q_KM01->SQL->Add(str);
    Form1->Q_KM01->Open();

}
/***********************************************************************
*  function name : void KM01_04Sub01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  | �Ȃ�       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | �Ȃ�       |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.12.06 E.Takase �����Ȃ��A��R��L�ER�ǉ�        *
*  contents      : �J�����g���R�[�h�̓��e��ϐ��ɑ��                  *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KM01_04Sub01(void)
{

 Variant sBuf;
 Variant str;


	KM01_04Data.KENSA_YMD		 = ""; 		//	�����\��N����
	KM01_04Data.TOLEY_NO		 = 0;	    //	�g���[No
	KM01_04Data.SAMPLE_P		 = 0;       //	�T���v���|�W�V����
	KM01_04Data.KOKBNG			 = 0;	    //	�H��No
	KM01_04Data.DTKSCOD			 = "";		//	���Ӑ�R�[�h
	KM01_04Data.DTKSHIN			 = "";		//	���Ӑ�i��
	KM01_04Data.LOTNO			 = "";		//	���b�gNo
	KM01_04Data.HINBAN			 = "";		//	���Еi��
	KM01_04Data.ZISCOD			 = "";		//	�ގ��R�[�h
	KM01_04Data.ZISNAM			 = "";		//	�ގ���
	KM01_04Data.NUM				 = 0;       //	�Đ��R�[�h
	KM01_04Data.SYOSCOD			 = "";		//	�Đ��R�[�h
	KM01_04Data.SORTKEY			 = 0;	    //	�\�[�g�L�[
	KM01_04Data.KEIJKBN			 = 0;		//	�`��敪
	KM01_04Data.SK_LD_LNG		 = 0;		//	����敪�@������
	KM01_04Data.SK_BURASI		 = 0;		//	�@�V�@�@�@�u���V��
	KM01_04Data.SK_BURASIT		 = 0;		//	�@�V�@�@�@�u���V���c����
	KM01_04Data.SK_LD_TR		 = 0;		//	�@�V�@�@�@����t��R
	KM01_04Data.SK_LD_HP		 = 0;		//	�@�V�@�@�@���������x
	KM01_04Data.SK_BOTAI		 = 0;		//	�@�V�@�@�@��̔�d
	KM01_04Data.SK_KOYU			 = 0;		//	�@�V�@�@�@�ŗL��R
	KM01_04Data.SK_MAGE			 = 0;		//	�@�V�@�@�@�R�ܗ�
	KM01_04Data.SK_HSC_A		 = 0;		//	�@�V�@�@�@HsC�d�x�i���ʁj
	KM01_04Data.SK_HSC_S		 = 0; 		//	�@�V�@�@�@HsC�d�x�i���ʁj
	KM01_04Data.SK_HSD_A		 = 0;		//	�@�V�@�@�@HsD�d�x�i���ʁj
	KM01_04Data.SK_HSD_S		 = 0;		//	�@�V�@�@�@HsD�d�x�i���ʁj
	KM01_04Data.SK_ZAKUT		 = 0;		//	�@�V�@�@�@����
	KM01_04Data.HIST_SOKUT		 = 0;		//	�q�X�g�O�������萔
	KM01_04Data.HIST_KIKAK		 = 0;		//	�@�V�@�@�@�@�@�K�i
	KM01_04Data.HIST_MIN		 = 0;		//	�@�V�@�@�@�@�@�����K�i
	KM01_04Data.HIST_MAX		 = 0;		//	�@�V�@�@�@�@�@����K�i
	KM01_04Data.LD_LNG_MIN		 = 0;		//	���[�h�������@���
	KM01_04Data.LD_LNG_MAX		 = 0;		//	�@�V�@�@�@�@�@����
	KM01_04Data.BURASI_MIN		 = 0;		//	�u���V���@���
	KM01_04Data.BURASI_MAX		 = 0;		//	�@�V�@�@�@����
	KM01_04Data.BURASIT_MIN		 = 0;		//	�u���V���c�������
	KM01_04Data.BURASIT_MAX		 = 0;		//	�@�V�@�@�@�@�@����
	KM01_04Data.LD_TR_DENA		 = 0;		//	���[�h����t����d��
	KM01_04Data.LD_TR_DENR		 = 0;		//	���[�h����t����d��
	KM01_04Data.LD_TR_TIME		 = 0;		//	�@�V�@�@��t���莞��
	KM01_04Data.LD_TR_TEKO		 = 0;		//	�@�V�@�@��t��R
	KM01_04Data.LD_HP_SPD		 = 0;		//	���[�h���������葬�x
	KM01_04Data.LD_HP_KYO		 = 0;		//	�@�V�@�@�������x
	KM01_04Data.LD_HP_TAN		 = 0;		//	�@�V�@�@�������x�P��
	KM01_04Data.BOTAI_MIN		 = 0;		//	��̔�d�@����
	KM01_04Data.BOTAI_MAX		 = 0;		//	�@�V�@�@�@���
	KM01_04Data.KOYU_MIN		 = 0;		//	�ŗL��R���@����
	KM01_04Data.KOYU_MAX		 = 0;		//	�@�V�@�@�@�@���
	KM01_04Data.KOYU_DEN		 = 0;		//	�@�V�@�@�@�@�d��
	KM01_04Data.KOYU_PRO		 = 0;		//	�@�V�@�@�@�@�v���[�u
	KM01_04Data.MAGE_MIN		 = 0;		//	�Ȃ����x�@����
	KM01_04Data.MAGE_MAX		 = 0;		//	�@�V�@�@�@���
	KM01_04Data.MAGE_TAN		 = 0;		//	�@�V�@�@�@�P��
	KM01_04Data.MAGE_SPAN		 = 0;		//	�@�V�@�@�@�X�p��
	KM01_04Data.HSC_A_MIN		 = 0;		//	�g���b�d�x�i���ʁj����
	KM01_04Data.HSC_A_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM01_04Data.HSC_S_MIN		 = 0;		//	�@�V�@�@�@�i���ʁj����
	KM01_04Data.HSC_S_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM01_04Data.HSD_A_MIN		 = 0;		//	�g���c�d�x�i���ʁj����
	KM01_04Data.HSD_A_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM01_04Data.HSD_S_MIN		 = 0;		//	�@�V�@�@�@�i���ʁj����
	KM01_04Data.HSD_S_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM01_04Data.ZAKUT_MIN		 = 0;		//	�����@����
	KM01_04Data.ZAKUT_MAX		 = 0;		//	�@�V�@���
	KM01_04Data.ADDYMD			 = 0;		//	�o�^��
	KM01_04Data.ADDTIM			 = 0;		//	�o�^����
	KM01_04Data.UPDYMD			 = 0;		//	�ύX��
	KM01_04Data.UPDTIM			 = "";		//	�ύX����
	KM01_04Data.UPDCHR			 = 0;		//	�X�V��
	KM01_04Data.UPDCNT			 = 0;		//	�X�V��
	KM01_04Data.RO_NO			 = "";		//	�FNo
	KM01_04Data.MAX_ONDO		 = 0;		//	MAX���x
	KM01_04Data.CYCLE_TIME		 = 0;		//	�T�C�N���^�C��
    //2002.12.05 E.Takase
	KM01_04Data.SK_MAGEG		 = 0;		//	����敪�@�����Ȃ����x
	KM01_04Data.MAGEG_MIN		 = 0;		//	�Ȃ����x�@����
	KM01_04Data.MAGEG_MAX		 = 0;		//	�@�V�@�@�@���
	KM01_04Data.MAGEG_TAN		 = 0;		//	�@�V�@�@�@�P��
	KM01_04Data.MAGEG_SPAN		 = 0;		//	�@�V�@�@�@�X�p��
        //20161024 Y.Onishi �H��敪�ǉ�
        KM01_04Data.KOJOKBN		 = 0;		//	�H��敪

    if ( !(VarIsNull ( Form1->Q_KM01->FieldValues["KENSA_YMD"])))
		KM01_04Data.KENSA_YMD = Form1->Q_KM01->FieldValues["KENSA_YMD"]; 					//	�����\��N����
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["TOLEY_NO"])))
		KM01_04Data.TOLEY_NO = Form1->Q_KM01->FieldValues["TOLEY_NO"];	            	//	�g���[No

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SAMPLE_P"])))
		KM01_04Data.SAMPLE_P = Form1->Q_KM01->FieldValues["SAMPLE_P"];       		//	�T���v���|�W�V����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOKBNG"])))
		KM01_04Data.KOKBNG = Form1->Q_KM01->FieldValues["KOKBNG"];	            	//	�H��No

    //sBuf = Form1->Q_KM01->FieldValues["DTKSCOD"];
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["DTKSCOD"] )) )
		KM01_04Data.DTKSCOD = Form1->Q_KM01->FieldValues["DTKSCOD"];				//	���Ӑ�R�[�h

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["DTKSHIN"])))
		KM01_04Data.DTKSHIN = Form1->Q_KM01->FieldValues["DTKSHIN"];				//	���Ӑ�i��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LOTNO"])))
		KM01_04Data.LOTNO = Form1->Q_KM01->FieldValues["LOTNO"];					//	���b�gNo

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HINBAN"])))
		KM01_04Data.HINBAN = Form1->Q_KM01->FieldValues["HINBAN"];					//	���Еi��

    sBuf = Form1->Q_KM01->FieldValues["ZISCOD"];
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ZISCOD"])))
		KM01_04Data.ZISCOD = Form1->Q_KM01->FieldValues["ZISCOD"];					//	�ގ��R�[�h

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ZISNAM"])))
		KM01_04Data.ZISNAM = Form1->Q_KM01->FieldValues["ZISNAM"];					//	�ގ���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["NUM"])))
		KM01_04Data.NUM = Form1->Q_KM01->FieldValues["NUM"];				    	//	����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SYOSCOD"])))
		KM01_04Data.SYOSCOD = Form1->Q_KM01->FieldValues["SYOSCOD"];				//	�Đ��R�[�h

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SORTKEY"])))
		KM01_04Data.SORTKEY = Form1->Q_KM01->FieldValues["SORTKEY"];	      		//	�\�[�g�L�[

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KEIJKBN"])))
		KM01_04Data.KEIJKBN = Form1->Q_KM01->FieldValues["KEIJKBN"];				//	�`��敪

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_LD_LNG"])))
		KM01_04Data.SK_LD_LNG = Form1->Q_KM01->FieldValues["SK_LD_LNG"];			//	����敪�@������

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_BURASI"])))
		KM01_04Data.SK_BURASI = Form1->Q_KM01->FieldValues["SK_BURASI"];			//	�@�V�@�@�@�u���V��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_BURASIT"])))
		KM01_04Data.SK_BURASIT = Form1->Q_KM01->FieldValues["SK_BURASIT"];			//	�@�V�@�@�@�u���V���c����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_LD_TR"])))
		KM01_04Data.SK_LD_TR = Form1->Q_KM01->FieldValues["SK_LD_TR"];				//	�@�V�@�@�@����t��R

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_LD_HP"])))
		KM01_04Data.SK_LD_HP = Form1->Q_KM01->FieldValues["SK_LD_HP"];				//	�@�V�@�@�@���������x

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_BOTAI"])))
		KM01_04Data.SK_BOTAI = Form1->Q_KM01->FieldValues["SK_BOTAI"];				//	�@�V�@�@�@��̔�d

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_KOYU"])))
		KM01_04Data.SK_KOYU = Form1->Q_KM01->FieldValues["SK_KOYU"];				//	�@�V�@�@�@�ŗL��R

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_MAGE"])))
		KM01_04Data.SK_MAGE = Form1->Q_KM01->FieldValues["SK_MAGE"];				//	�@�V�@�@�@�R�ܗ�

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_HSC_A"])))
		KM01_04Data.SK_HSC_A = Form1->Q_KM01->FieldValues["SK_HSC_A"];				//	�@�V�@�@�@HsC�d�x�i���ʁj

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_HSC_S"])))
		KM01_04Data.SK_HSC_S = Form1->Q_KM01->FieldValues["SK_HSC_S"];				//	�@�V�@�@�@HsC�d�x�i���ʁj

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_HSD_A"])))
		KM01_04Data.SK_HSD_A = Form1->Q_KM01->FieldValues["SK_HSD_A"];				//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_HSD_S"])))
		KM01_04Data.SK_HSD_S = Form1->Q_KM01->FieldValues["SK_HSD_S"];				//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_ZAKUT"])))
		KM01_04Data.SK_ZAKUT = Form1->Q_KM01->FieldValues["SK_ZAKUT"];				//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HIST_SOKUT"])))
		KM01_04Data.HIST_SOKUT = Form1->Q_KM01->FieldValues["HIST_SOKUT"];			//	�q�X�g�O�������萔

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HIST_KIKAK"])))
		KM01_04Data.HIST_KIKAK = Form1->Q_KM01->FieldValues["HIST_KIKAK"];			//	�@�V�@�@�@�@�@�K�i

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HIST_MIN"])))
		KM01_04Data.HIST_MIN = Form1->Q_KM01->FieldValues["HIST_MIN"];			//	�@�V�@�@�@�@�@�����K�i

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HIST_MAX"])))
		KM01_04Data.HIST_MAX = Form1->Q_KM01->FieldValues["HIST_MAX"];			//	�@�V�@�@�@�@�@����K�i

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_LNG_MIN"])))
		KM01_04Data.LD_LNG_MIN = Form1->Q_KM01->FieldValues["LD_LNG_MIN"];		//	���[�h�������@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_LNG_MAX"])))
		KM01_04Data.LD_LNG_MAX = Form1->Q_KM01->FieldValues["LD_LNG_MAX"];		//	�@�V�@�@�@�@�@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BURASI_MIN"])))
		KM01_04Data.BURASI_MIN = Form1->Q_KM01->FieldValues["BURASI_MIN"];		//	�u���V���@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BURASI_MAX"])))
		KM01_04Data.BURASI_MAX = Form1->Q_KM01->FieldValues["BURASI_MAX"];		//	�@�V�@�@�@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BURASIT_MIN"])))
		KM01_04Data.BURASIT_MIN = Form1->Q_KM01->FieldValues["BURASIT_MIN"];		//	�u���V���c�������

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BURASIT_MAX"])))
		KM01_04Data.BURASIT_MAX = Form1->Q_KM01->FieldValues["BURASIT_MAX"];		//	�@�V�@�@�@�@�@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_TR_DENA"])))
		KM01_04Data.LD_TR_DENA = Form1->Q_KM01->FieldValues["LD_TR_DENA"];			//	���[�h����t����d��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_TR_DENR"])))
		KM01_04Data.LD_TR_DENR = Form1->Q_KM01->FieldValues["LD_TR_DENR"];			//	���[�h����t����d��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_TR_DENR"])))
	    KM01_04Data.LD_TR_TEKO = int(DivAB(KM01_04Data.LD_TR_DENA , ( KM01_04Data.LD_TR_DENR * 1.0 )));


    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_TR_TIME"])))
		KM01_04Data.LD_TR_TIME = Form1->Q_KM01->FieldValues["LD_TR_TIME"];			//	�@�V�@�@��t���莞��

		//KM01_04Data.LD_TR_TEKO = Form1->Q_KM01->FieldValues["LD_TR_TEKO"];			//	�@�V�@�@��t��R
	if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_HP_SPD"])))
		KM01_04Data.LD_HP_SPD = Form1->Q_KM01->FieldValues["LD_HP_SPD"];			//	���[�h���������葬�x

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_HP_KYO"])))
		KM01_04Data.LD_HP_KYO = Form1->Q_KM01->FieldValues["LD_HP_KYO"];			//	�@�V�@�@�������x

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["LD_HP_TAN"])))
		KM01_04Data.LD_HP_TAN = Form1->Q_KM01->FieldValues["LD_HP_TAN"];			//	�@�V�@�@�������x�P��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BOTAI_MIN"])))
		KM01_04Data.BOTAI_MIN = Form1->Q_KM01->FieldValues["BOTAI_MIN"];			//	��̔�d�@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["BOTAI_MAX"])))
		KM01_04Data.BOTAI_MAX = Form1->Q_KM01->FieldValues["BOTAI_MAX"];			//	�@�V�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOYU_MIN"])))
		KM01_04Data.KOYU_MIN = Form1->Q_KM01->FieldValues["KOYU_MIN"];				//	�ŗL��R���@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOYU_MAX"])))
		KM01_04Data.KOYU_MAX = Form1->Q_KM01->FieldValues["KOYU_MAX"];				//	�@�V�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOYU_DEN"])))
		KM01_04Data.KOYU_DEN = Form1->Q_KM01->FieldValues["KOYU_DEN"];			//	�@�V�@�@�@�@�d��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOYU_PRO"])))
		KM01_04Data.KOYU_PRO = Form1->Q_KM01->FieldValues["KOYU_PRO"];				//	�@�V�@�@�@�@�v���[�u

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGE_MIN"])))
		KM01_04Data.MAGE_MIN = Form1->Q_KM01->FieldValues["MAGE_MIN"];				//	�Ȃ����x�@����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGE_MAX"])))
		KM01_04Data.MAGE_MAX = Form1->Q_KM01->FieldValues["MAGE_MAX"];				//	�@�V�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGE_TAN"])))
		KM01_04Data.MAGE_TAN = Form1->Q_KM01->FieldValues["MAGE_TAN"];				//	�@�V�@�@�@�P��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGE_SPAN"])))
		KM01_04Data.MAGE_SPAN = Form1->Q_KM01->FieldValues["MAGE_SPAN"];			//	�@�V�@�@�@�X�p��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSC_A_MIN"])))
		KM01_04Data.HSC_A_MIN = Form1->Q_KM01->FieldValues["HSC_A_MIN"];			//	�g���b�d�x�i���ʁj����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSC_A_MAX"])))
		KM01_04Data.HSC_A_MAX = Form1->Q_KM01->FieldValues["HSC_A_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSC_S_MIN"])))
		KM01_04Data.HSC_S_MIN = Form1->Q_KM01->FieldValues["HSC_S_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSC_S_MAX"])))
		KM01_04Data.HSC_S_MAX = Form1->Q_KM01->FieldValues["HSC_S_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSD_A_MIN"])))
		KM01_04Data.HSD_A_MIN = Form1->Q_KM01->FieldValues["HSD_A_MIN"];			//	�g���c�d�x�i���ʁj����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSD_A_MAX"])))
		KM01_04Data.HSD_A_MAX = Form1->Q_KM01->FieldValues["HSD_A_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSD_S_MIN"])))
		KM01_04Data.HSD_S_MIN = Form1->Q_KM01->FieldValues["HSD_S_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["HSD_S_MAX"])))
		KM01_04Data.HSD_S_MAX = Form1->Q_KM01->FieldValues["HSD_S_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ZAKUT_MIN"])))
		KM01_04Data.ZAKUT_MIN = Form1->Q_KM01->FieldValues["ZAKUT_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ZAKUT_MAX"])))
		KM01_04Data.ZAKUT_MAX = Form1->Q_KM01->FieldValues["ZAKUT_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ADDYMD"])))
		KM01_04Data.ADDYMD = Form1->Q_KM01->FieldValues["ADDYMD"];					//	�o�^��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["ADDTIM"])))
		KM01_04Data.ADDTIM = Form1->Q_KM01->FieldValues["ADDTIM"];					//	�o�^����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["UPDYMD"])))
		KM01_04Data.UPDYMD = Form1->Q_KM01->FieldValues["UPDYMD"];					//	�ύX��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["UPDTIM"])))
		KM01_04Data.UPDTIM = Form1->Q_KM01->FieldValues["UPDTIM"];					//	�ύX����

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["UPDCHR"])))
		KM01_04Data.UPDCHR = Form1->Q_KM01->FieldValues["UPDCHR"];					//	�X�V��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["UPDCNT"])))
		KM01_04Data.UPDCNT = Form1->Q_KM01->FieldValues["UPDCNT"];					//	�X�V��

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["RO_NO"])))
		KM01_04Data.RO_NO = Form1->Q_KM01->FieldValues["RO_NO"];					//	�FNo

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAX_ONDO"])))
		KM01_04Data.MAX_ONDO = Form1->Q_KM01->FieldValues["MAX_ONDO"];				//	MAX���x

    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["CYCLE_TIME"])))
		KM01_04Data.CYCLE_TIME = Form1->Q_KM01->FieldValues["CYCLE_TIME"];			//	�T�C�N���^�C��

    //2002/12/06 E.Takase
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["SK_MAGEG"])))
		KM01_04Data.SK_MAGEG = Form1->Q_KM01->FieldValues["SK_MAGEG"];				//	����敪�@�����Ȃ����x
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGEG_MIN"])))
		KM01_04Data.MAGEG_MIN = Form1->Q_KM01->FieldValues["MAGEG_MIN"];			//	�Ȃ����x�@����
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGEG_MAX"])))
		KM01_04Data.MAGEG_MAX = Form1->Q_KM01->FieldValues["MAGEG_MAX"];			//	�@�V�@�@�@���
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGEG_TAN"])))
		KM01_04Data.MAGEG_TAN = Form1->Q_KM01->FieldValues["MAGEG_TAN"];			//	�@�V�@�@�@�P��
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["MAGEG_SPAN"])))
		KM01_04Data.MAGEG_SPAN = Form1->Q_KM01->FieldValues["MAGEG_SPAN"];			//	�@�V�@�@�@�X�p��
    //20161024 Y.Onishi �H��敪�ǉ�
    if ( !(VarIsNull (Form1->Q_KM01->FieldValues["KOJOKBN"])))
		KM01_04Data.KOJOKBN = Form1->Q_KM01->FieldValues["KOJOKBN"];			        //	�@�H��敪

}

/***********************************************************************
*  function name : void DTKSHIN_CIYCLEInsert01(void)                   *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���Ӑ�i�Ԃ��� ���َ��Ԃ܂ł̃f�[�^�����[�N�ɒǉ�   *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void DTKSHIN_CIYCLEInsert01(void)
{
    //int i,n;

    AnsiString str;
    AnsiString sBuf;
    AnsiString str_S;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;
    //20161031 Y.Onishi �H��敪�ǉ�
    AnsiString str_KK;
        /***************************/
        /*                         */
        /* ���Ӑ�i�Ԃ��� ���َ��� */
        /*                         */
        /***************************/
        str_c[0] = '\0';
        //Initial Query
        Form1->Q_TW_TKS21PR->Close();
        Form1->Q_TW_TKS21PR->SQL->Clear();

        //add sql INSERT
        //str = "insert into TW_TKS21PR(CODE,KENSA_YMD,TOLEY_NO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2) ";
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            //20161024 Y.Onishi �H��敪�ǉ�
            //str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

            //���Ӑ於�@����
		    //KM01����DTKSCOD�𒊏o
		    Form2->Query1->Close();
		    Form2->Query1->SQL->Clear();

		    //�₢���������s
		    //�����\����A�g���[No
		    sBuf = "SELECT ";
		    sBuf += "DISTINCT TRSCOD, TRSNAM ";
		    sBuf += "FROM SM16S ";
		    sBuf += " WHERE  TRSCOD = '" + KM01_04Data.DTKSCOD + "'";
		    sBuf += " ORDER BY TRSCOD";
		    Form2->Query1->SQL->Add(sBuf);
		    Form2->Query1->Open();
		    Form2->Query1->Active = true;

		    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
		      Form2->Select_DTKSNAM = " ";
		      return;
		    }else {
		      Form2->Query1->First();
			if ( Form2->Query1->FieldValues["TRSNAM"].IsEmpty() ) Form2->Select_DTKSNAM = " ";
		     	else Form2->Select_DTKSNAM = Form2->Query1->FieldValues["TRSNAM"];
		    }

        }
        else {
            //20161024 Y.Onishi �H��敪�ǉ�
            //str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";
        }

        str_S = "�k";
        //add sql VALUES  ������strVal_c  �󔒁�strBlank_c

        //20161031 Y.Onishi �H��敪�ǉ�
        //wsprintf(strVal_c,"%-20s %-20s %-6s     %-7d       %-4s     %-4s       %-4d     %-3d    %s",
        //                    KM01_04Data.DTKSHIN.c_str(),
        //                    KM01_04Data.ZISNAM.c_str(),
        //                    KM01_04Data.LOTNO.c_str(),
        //                    KM01_04Data.NUM,
        //                    KM01_04Data.SYOSCOD.c_str(),
        //                    KM01_04Data.RO_NO.c_str(),
        //                    KM01_04Data.MAX_ONDO,
        //                    KM01_04Data.CYCLE_TIME,
        //                    str_S.c_str()        );
        if (KM01_04Data.KOJOKBN == 0 ) {
                str_KK = "�{)";
        }
        else if (KM01_04Data.KOJOKBN == 1 ) {
                str_KK = "�L)";
        }
        else {
                str_KK = "�H)";
        }
        wsprintf(strVal_c,"%s%-20s %-20s %-6s     %-7d       %-4s     %-4s       %-4d     %-3d    %s",
                            str_KK,
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.ZISNAM.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.NUM,
                            KM01_04Data.SYOSCOD.c_str(),
                            KM01_04Data.RO_NO.c_str(),
                            KM01_04Data.MAX_ONDO,
                            KM01_04Data.CYCLE_TIME,
                            str_S.c_str()        );

        //strVal01 = varstr(Form1->Q_KM01->FieldValues["KENSA_YMD"]);
        //strVal02 = varstr(Form1->Q_KM01->FieldValues["TOLEY_NO"]);
        //strVal03 = varstr(Form1->Q_KM01->FieldValues["SAMPLE_P"]);
        //strVal04 = varstr(Form1->Q_KM01->FieldValues["DTKSCOD"]);

        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s','%s') ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str() ,
                            Form2->Select_DTKSNAM.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );

        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s') ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
        }
        */
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s','%s',%d) ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str() ,
                            Form2->Select_DTKSNAM.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );

        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s',%d) ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );
        }
        //str += str_c;
        Form1->Q_TW_TKS21PR->SQL->Add(str + str_c);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();

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
*  function name : void LOT_SOKUTEIInsert01(void)                      *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ���b�gNo���� ������܂ł̃f�[�^�����[�N�ɒǉ�       *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void LOT_SOKUTEIInsert01(void)
{
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    AnsiString tableNo;
    AnsiString Daystr;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;
    //20161031 Y.Onishi �H��敪�ǉ�
    AnsiString str_KK;
        /***************************/
        /*                         */
        /* ���b�gNo���� �����     */
        /*                         */
        /***************************/
        str_c[0] = '\0';
        //Initial Query
        Form1->Q_TW_TKS21PR->Close();
        Form1->Q_TW_TKS21PR->SQL->Clear();

        //add sql INSERT
        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        //str = "insert into TW_TKS21PR(CODE,KENSA_YMD,TOLEY_NO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2) ";
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";
        }
        */
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO,KOJOKBN) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";
        }

        //add sql VALUES  ������strVal_c  �󔒁�strBlank_c
        Daystr = KM01_04Data.KENSA_YMD.SubString(1,4) + "/";
        Daystr += KM01_04Data.KENSA_YMD.SubString(5,2) + "/";
        Daystr += KM01_04Data.KENSA_YMD.SubString(7,2) ;

        //20161031 Y.Onishi �H��敪�ǉ�
        //wsprintf(strVal_c,"%-6s   %-20s  %-7d  %-10s   �k",
        //                    KM01_04Data.LOTNO.c_str(),
        //                    KM01_04Data.ZISNAM.c_str(),
        //                    KM01_04Data.NUM,
        //                    Daystr.c_str()      );
        if (KM01_04Data.KOJOKBN == 0 ) {
                str_KK = "�{)";
        }
        else if (KM01_04Data.KOJOKBN == 1 ) {
                str_KK = "�L)";
        }
        else {
                str_KK = "�H)";
        }
        wsprintf(strVal_c,"%s%-6s   %-20s  %-7d  %-10s   �k",
                            str_KK,
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.ZISNAM.c_str(),
                            KM01_04Data.NUM,
                            Daystr.c_str()      );

        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s') ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );

        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s') ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
        }
        */
        if ( Flagcnd == 0 || Flagcnd == 2  ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s',%d) ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );

        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s',%d) ",
                            1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );
        }
        //str += str_c;
        Form1->Q_TW_TKS21PR->SQL->Add(str + str_c);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();
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
*  function name : void KIKAKU_MINInsert01(void)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KIKAKU_MINInsert01(void)
{
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    char strTmp_c[STRMAX];
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString Kara01;

        /***************************/
        /*                         */
        /* �K�i���`                */
        /*                         */
        /***************************/

        str_c[0] = '\0';
        strVal_c[0] = '\0';
        strTmp_c[0] = '\0';

        //add sql VALUES  ������strVal_c
        //��̔�d
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BOTAI, KM01_04Data.BOTAI_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_BOTAI);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BOTAI, KM01_04Data.BOTAI_MAX,2);
        wsprintf(strTmp_c,"%6s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���b�j ����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_A, KM01_04Data.HSC_A_MIN);
        Kara01= Kara(KM01_04Data.SK_HSC_A);
        wsprintf(strTmp_c,"%2s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_A, KM01_04Data.HSC_A_MAX);
        wsprintf(strTmp_c,"%2s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���b�j ����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_S, KM01_04Data.HSC_S_MIN);
        Kara01 = Kara(KM01_04Data.SK_HSC_S);
        wsprintf(strTmp_c,"%2s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_S, KM01_04Data.HSC_S_MAX);
        wsprintf(strTmp_c,"%2s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���c�j ����
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_A, KM01_04Data.HSD_A_MIN,1);
        Kara01 = Kara(KM01_04Data.SK_HSD_A);
        wsprintf(strTmp_c,"%4s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_A, KM01_04Data.HSD_A_MAX,1);
        wsprintf(strTmp_c,"%4s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���c�j ����
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_S, KM01_04Data.HSD_S_MIN,1);
        Kara01 = Kara(KM01_04Data.SK_HSD_S);
        wsprintf(strTmp_c,"%4s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);
        //koko
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_S, KM01_04Data.HSD_S_MAX,1);
        wsprintf(strTmp_c,"%4s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�ŗL��R
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MIN);
        Kara01 = Kara(KM01_04Data.SK_KOYU);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MAX);
        wsprintf(strTmp_c,"%6s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�Ȃ�
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MIN,1);
        //2003.02.07 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_MAGE);
        wsprintf(strTmp_c,"%10s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MAX,1);
        //2003.02.07 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MAX,2);
        wsprintf(strTmp_c,"%10s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_ZAKUT, KM01_04Data.ZAKUT_MIN);
        Kara01 = Kara(KM01_04Data.SK_ZAKUT);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_ZAKUT, KM01_04Data.ZAKUT_MAX);
        wsprintf(strTmp_c,"%6s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //��t��R SOKUTEIstrI( 0, KM01_04Data.SK_LD_TR, KM01_04Data.LD_TR_TEKO);
        strVal01 = " ";
        Kara01 = Kara(0);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        //strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_LD_TR, KM01_04Data.LD_TR_DENA);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_TR, KM01_04Data.LD_TR_DENA,1);
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�������x
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_HP, KM01_04Data.LD_HP_KYO,1);
        Kara01 = Kara(KM01_04Data.SK_LD_HP);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = " ";
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //������
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_LNG, KM01_04Data.LD_LNG_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_LD_LNG);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_LNG, KM01_04Data.LD_LNG_MAX,2);
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //��
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASI, KM01_04Data.BURASI_MIN,3);
        Kara01 = Kara(KM01_04Data.SK_BURASI);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASI, KM01_04Data.BURASI_MAX,3);
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //���i�c�j
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASIT, KM01_04Data.BURASIT_MIN,3);
        Kara01 = Kara(KM01_04Data.SK_BURASIT);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASIT, KM01_04Data.BURASIT_MAX,3);
        wsprintf(strTmp_c,"%7s ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);


        if ( Flagcnd == 0 ) {
            //Initial Query
            Form1->Q_TW_TKS21PR->Close();
            Form1->Q_TW_TKS21PR->SQL->Clear();

            //add sql INSERT
            //20161024 Y.Onishi �H��敪�ǉ�
            /*
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO) ";
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s') ",
                            2,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
            */
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO,KOJOKBN) ";
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s',%d) ",
                            2,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );

            str += str_c;
            Form1->Q_TW_TKS21PR->SQL->Add(str);

            //execute sql
            try
            {
                Form1->Q_TW_TKS21PR->ExecSQL();
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
        else {
            KIKAKUMINstr = strVal_c;
        }


}

/***********************************************************************
*  function name : void KIKAKU_MINInsert02(void)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : �������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KIKAKU_MINInsert02(void)
{
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    char strTmp_c[STRMAX];
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString Kara01;

        /***************************/
        /*                         */
        /* �K�i���`                */
        /*                         */
        /***************************/

        str_c[0] = '\0';
        strVal_c[0] = '\0';
        strTmp_c[0] = '\0';

        //add sql VALUES  ������strVal_c
        //��̔�d
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BOTAI, KM01_04Data.BOTAI_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_BOTAI);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BOTAI, KM01_04Data.BOTAI_MAX,2);
        wsprintf(strTmp_c,"%6s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���b�j ����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_A, KM01_04Data.HSC_A_MIN);
        Kara01= Kara(KM01_04Data.SK_HSC_A);
        wsprintf(strTmp_c,"%2s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_A, KM01_04Data.HSC_A_MAX);
        wsprintf(strTmp_c,"%2s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���b�j ����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_S, KM01_04Data.HSC_S_MIN);
        Kara01 = Kara(KM01_04Data.SK_HSC_S);
        wsprintf(strTmp_c,"%2s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_HSC_S, KM01_04Data.HSC_S_MAX);
        wsprintf(strTmp_c,"%2s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���c�j ����
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_A, KM01_04Data.HSD_A_MIN,1);
        Kara01 = Kara(KM01_04Data.SK_HSD_A);
        wsprintf(strTmp_c,"%4s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_A, KM01_04Data.HSD_A_MAX,1);
        wsprintf(strTmp_c,"%4s   ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�d�x�i�g���c�j ����
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_S, KM01_04Data.HSD_S_MIN,1);
        Kara01 = Kara(KM01_04Data.SK_HSD_S);
        wsprintf(strTmp_c,"%4s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);
        //koko
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_HSD_S, KM01_04Data.HSD_S_MAX,1);
        wsprintf(strTmp_c,"%4s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�ŗL��R
        //2003.02.08 E.Takase strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MIN);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_KOYU);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        //2003.02.08 E.Takase strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MAX);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MAX,2);
        wsprintf(strTmp_c,"%6s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�ŗL��R
        //2003.02.08 E.Takase strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MIN);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_KOYU);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        //2003.02.08 E.Takase strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MAX);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_KOYU, KM01_04Data.KOYU_MAX,2);
        wsprintf(strTmp_c,"%6s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�Ȃ�
        //2003.02.05 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MIN,1);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_MAGE);
        wsprintf(strTmp_c,"%10s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        //2003.02.05 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MAX,1);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGE, KM01_04Data.MAGE_MAX,2);
        wsprintf(strTmp_c,"%10s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //�����Ȃ�
        //2003.02.05 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGEG, KM01_04Data.MAGEG_MIN,1);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGEG, KM01_04Data.MAGEG_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_MAGEG);
        wsprintf(strTmp_c,"%10s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        //2003.02.05 E.Takase strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGEG, KM01_04Data.MAGEG_MAX,1);
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_MAGEG, KM01_04Data.MAGEG_MAX,2);
        wsprintf(strTmp_c,"%10s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //����
        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_ZAKUT, KM01_04Data.ZAKUT_MIN);
        Kara01 = Kara(KM01_04Data.SK_ZAKUT);
        wsprintf(strTmp_c,"%6s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrI( 0, KM01_04Data.SK_ZAKUT, KM01_04Data.ZAKUT_MAX);
        wsprintf(strTmp_c,"%6s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //������
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_LNG, KM01_04Data.LD_LNG_MIN,2);
        Kara01 = Kara(KM01_04Data.SK_LD_LNG);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_LD_LNG, KM01_04Data.LD_LNG_MAX,2);
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //��
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASI, KM01_04Data.BURASI_MIN,3);
        Kara01 = Kara(KM01_04Data.SK_BURASI);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASI, KM01_04Data.BURASI_MAX,3);
        wsprintf(strTmp_c,"%7s  ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);

        //���i�c�j
        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASIT, KM01_04Data.BURASIT_MIN,3);
        Kara01 = Kara(KM01_04Data.SK_BURASIT);
        wsprintf(strTmp_c,"%7s%2s",strVal01.c_str(),Kara01.c_str());
        strcat(strVal_c,strTmp_c);

        strVal01 = SOKUTEIstrF( 0, KM01_04Data.SK_BURASIT, KM01_04Data.BURASIT_MAX,3);
        wsprintf(strTmp_c,"%7s ",strVal01.c_str());
        strcat(strVal_c,strTmp_c);


        if ( Flagcnd == 2 ) {
            //Initial Query
            Form1->Q_TW_TKS21PR->Close();
            Form1->Q_TW_TKS21PR->SQL->Clear();

            //add sql INSERT
            //20161024 Y.Onishi �H��敪�ǉ�
            /*
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO) ";
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s') ",
                            2,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
            */
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO,KOJOKBN) ";
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s',%d) ",
                            2,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );

            str += str_c;
            Form1->Q_TW_TKS21PR->SQL->Add(str);

            //execute sql
            try
            {
                Form1->Q_TW_TKS21PR->ExecSQL();
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
        else {
            KIKAKUMINstr = strVal_c;
        }


}



/***********************************************************************
*  function name : void KIKAKU_MAXInsert01(void)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ڂ̋K�i��̃f�[�^�����[�N�ɒǉ�              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void KIKAKU_MAXInsert01(void)
{
    AnsiString str;
    str = " ";
    KIKAKUMAXstr = str.c_str();
}

/***********************************************************************
*  function name : void SOKUTEIInsert01(void)                          *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void SOKUTEIInsert01(void)
{
    int j;
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    AnsiString TANI01;
    AnsiString TANI02;
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;
    AnsiString strVal04;
    AnsiString strVal05;
    AnsiString strVal06;
    AnsiString strVal07;
    AnsiString strVal08;
    AnsiString strVal09;
    AnsiString strVal10;
    AnsiString strVal11;
    AnsiString strVal12;
    AnsiString strVal13;
    AnsiString Kara01;
    AnsiString Kara02;
    AnsiString Kara03;
    AnsiString Kara04;
    AnsiString Kara05;
    AnsiString Kara06;
    AnsiString Kara07;
    AnsiString Kara08;
    AnsiString Kara09;
    AnsiString Kara10;
    AnsiString Kara11;
    AnsiString Kara12;
    AnsiString Kara13;

    for ( j = 0; j < DataNo; j++) {
        /***************************/
        /*                         */
        /*      ����l             */
        /*                         */
        /***************************/
        str_c[0] = '\0';
        //Initial Query
        Form1->Q_TW_TKS21PR->Close();
        Form1->Q_TW_TKS21PR->SQL->Clear();

        //add sql INSERT
        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 0 ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";
        }
        */
        if ( Flagcnd == 0 ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO,KOJOKBN) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";
        }

        strVal01 = SOKUTEIstrF( j, KM01_04Data.SK_BOTAI, KD51Data.BOTAI_VAL[j],2);
        Kara01 = Kara(0);
        strVal01 += Kara01;

        strVal02 = SOKUTEIstrI( j, KM01_04Data.SK_KOYU, KD71Data.KOYU_VAL[j]);
        Kara02 = Kara(0);
        strVal02 += Kara02;

        strVal03 = SOKUTEIstrF( j, KM01_04Data.SK_MAGE, KD81Data.MAGE_VAL[j],1);
        //2003.02.07 E.Takase strVal03 = SOKUTEIstrF( j, KM01_04Data.SK_MAGE, KD81Data.MAGE_VAL[j],2);
        Kara03 = Kara(0);
        strVal03 += Kara03;
        //�P��
		switch ( KM01_04Data.MAGE_TAN ) {
			case 2:
				TANI02 = "*";
				break;
			case 4:
				TANI02 = "#";
				break;

			case 5:
				TANI02 = "#";
				break;
			default:
				TANI02 = " ";
			break;
		}
//        if ( KM01_04Data.MAGE_TAN  == 3 ) TANI02 = " ";
//        else  TANI02 = "*";
        strVal03 += TANI02;

        strVal04 = SOKUTEIstrI( j, KM01_04Data.SK_ZAKUT, KD91Data.ZAKUT_VAL[j]);
        Kara04 = Kara(0);
        strVal04 += Kara04;

        strVal05 = SOKUTEIstrF( j, KM01_04Data.SK_LD_TR, KD31Data.LD_TRR_VAL[j],1);
        Kara05 = Kara(0);
        strVal05 += Kara05;

        strVal06 = SOKUTEIstrF( j, KM01_04Data.SK_LD_HP, KD41Data.LD_HP_VAL[j],1);
        Kara06 = Kara(0);
        strVal06 += Kara06;

        strVal07 = SOKUTEIstrF( j, KM01_04Data.SK_LD_LNG, KD01Data.LD_LNG_VAL[j],2);
        Kara07 = Kara(0);
        strVal07 += Kara07;

        strVal08 = SOKUTEIstrF( j, KM01_04Data.SK_BURASI, KD11Data.BURASI_VAL[j],3);
        Kara08 = Kara(0);
        strVal08 += Kara08;

        strVal09 = SOKUTEIstrF( j, KM01_04Data.SK_BURASIT, KD21Data.BURASIT_VAL[j],3);
        Kara09 = Kara(0);
        strVal09 += Kara09;

        strVal10 = SOKUTEIstrI( j, KM01_04Data.SK_HSC_A, KD61Data.HSC_A_VAL[j]);
        Kara10 = Kara(0);
        strVal10 += Kara10;

        strVal11 = SOKUTEIstrI( j, KM01_04Data.SK_HSC_S, KD61Data.HSC_S_VAL[j]);
        Kara11 = Kara(0);
        strVal11 += Kara11;

        strVal12 = SOKUTEIstrF( j, KM01_04Data.SK_HSD_A, KD61Data.HSD_A_VAL[j],1);
        Kara12 = Kara(0);
        strVal12 += Kara12;

        strVal13 = SOKUTEIstrF( j, KM01_04Data.SK_HSD_S, KD61Data.HSD_S_VAL[j],1);
        Kara13 = Kara(0);
        strVal13 += Kara13;

       //                   �@  �A   �B  �C   �D   �E   �F   �G   �H   �I      �J   �K  �L
       //                  ��d���� ���ʈ��� ���� ��R �Ȃ� ���� ��t ����    ����  ��  �c
      //wsprintf(strVal_c,"%8s %4s  %4s %6s  %6s  %8s  %12s %8s %9s  %9s    %9s  %9s %9s",
      //wsprintf(strVal_c,"%8s %8s  %6s %8s  %8s  %10s %16s %10s%12s %12s   %12s %12s %12s",
        wsprintf(strVal_c,"%8s %12s %8s %10s %10s %12s %19s%14s %14s %15s%17s %15s %15s",
                            strVal01.c_str(),
                            strVal10.c_str(),
                            strVal11.c_str(),
                            strVal12.c_str(),
                            strVal13.c_str(),
                            strVal02.c_str(),
                            strVal03.c_str(),
                            strVal04.c_str(),
                            strVal05.c_str(),
                            strVal06.c_str(),
                            strVal07.c_str(),
                            strVal08.c_str(),
                            strVal09.c_str()
                               );

        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 0 ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s') ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s') ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr,
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                           );
        }
        */
        if ( Flagcnd == 0 ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s',%d) ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s',%d) ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr,
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                           );
        }

        //str += str_c;
        Form1->Q_TW_TKS21PR->SQL->Add( str + str_c);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();
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

}

/***********************************************************************
*  function name : void SOKUTEIInsert02(void)                          *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void SOKUTEIInsert02(void)
{
    int j;
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    AnsiString TANI01;
    AnsiString TANI02;
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;
    AnsiString strVal04;
    AnsiString strVal05;
    AnsiString strVal06;
    AnsiString strVal07;
    AnsiString strVal08;
    AnsiString strVal09;
    AnsiString strVal10;
    AnsiString strVal11;
    AnsiString strVal12;
    AnsiString strVal13;
    AnsiString Kara01;
    AnsiString Kara02;
    AnsiString Kara03;
    AnsiString Kara04;
    AnsiString Kara05;
    AnsiString Kara06;
    AnsiString Kara07;
    AnsiString Kara08;
    AnsiString Kara09;
    AnsiString Kara10;
    AnsiString Kara11;
    AnsiString Kara12;
    AnsiString Kara13;

    for ( j = 0; j < DataNo; j++) {
        /***************************/
        /*                         */
        /*      ����l             */
        /*                         */
        /***************************/
        str_c[0] = '\0';
        //Initial Query
        Form1->Q_TW_TKS21PR->Close();
        Form1->Q_TW_TKS21PR->SQL->Clear();

        //add sql INSERT
        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 2 ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";
        }
        */
        if ( Flagcnd == 2 ) {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,DTKSHIN,LOTNO,KOJOKBN) ";
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";
        }

        strVal01 = SOKUTEIstrF( j, KM01_04Data.SK_BOTAI, KD51Data.BOTAI_VAL[j],2);
        Kara01 = Kara(0);
        strVal01 += Kara01;

		//�����Ȃ�����
        //2003.02.05 E.Takase strVal02 = SOKUTEIstrF( j, KM01_04Data.SK_MAGEG, KDC1Data.MAGEG_VAL[j],1);
		strVal02 = SOKUTEIstrF( j, KM01_04Data.SK_MAGEG, KDC1Data.MAGEG_VAL[j],2);
        Kara02 = Kara(0);
        strVal02 += Kara02;
        //�P��
		switch ( KM01_04Data.MAGEG_TAN ) {
			case 2:
				TANI02 = "*";
				break;
			case 4:
				TANI02 = "#";
				break;
            //2003/07/22 E.Takase �P�ʒǉ�
			case 5:
				TANI02 = "N";
				break;
			default:
				TANI02 = " ";
			break;
		}
        strVal02 += TANI02;

        
		//�Ȃ�����
        //2003.02.05 E.Takase  strVal03 = SOKUTEIstrF( j, KM01_04Data.SK_MAGE, KD81Data.MAGE_VAL[j],1);
		strVal03 = SOKUTEIstrF( j, KM01_04Data.SK_MAGE, KD81Data.MAGE_VAL[j],2);
        Kara03 = Kara(0);
        strVal03 += Kara03;
        //�P��
		switch ( KM01_04Data.MAGE_TAN ) {
			case 2:
				TANI02 = "*";
				break;
			case 4:
				TANI02 = "#";
				break;
			default:
				TANI02 = " ";
			break;
		}
//        if ( KM01_04Data.MAGE_TAN  == 3 ) TANI02 = " ";
//        else  TANI02 = "*";
        strVal03 += TANI02;

        strVal04 = SOKUTEIstrI( j, KM01_04Data.SK_ZAKUT, KD91Data.ZAKUT_VAL[j]);
        Kara04 = Kara(0);
        strVal04 += Kara04;

        //��R�� L
        //2003.02.08 E.Takase strVal05 = SOKUTEIstrI( j, KM01_04Data.SK_KOYU, KD71Data_L.KOYU_VAL[j]);
        strVal05 = SOKUTEIstrF( j, KM01_04Data.SK_KOYU, KD71Data_L.KOYU_VAL[j],2);
        Kara05 = Kara(0);
        strVal05 += Kara05;

        //��R�� R
        //2003.02.08 strVal06 = SOKUTEIstrI( j, KM01_04Data.SK_KOYU, KD71Data_R.KOYU_VAL[j]);
        strVal06 = SOKUTEIstrF( j, KM01_04Data.SK_KOYU, KD71Data_R.KOYU_VAL[j],2);
        Kara06 = Kara(0);
        strVal06 += Kara06;

        strVal07 = SOKUTEIstrF( j, KM01_04Data.SK_LD_LNG, KD01Data.LD_LNG_VAL[j],2);
        Kara07 = Kara(0);
        strVal07 += Kara07;

        strVal08 = SOKUTEIstrF( j, KM01_04Data.SK_BURASI, KD11Data.BURASI_VAL[j],3);
        Kara08 = Kara(0);
        strVal08 += Kara08;

        strVal09 = SOKUTEIstrF( j, KM01_04Data.SK_BURASIT, KD21Data.BURASIT_VAL[j],3);
        Kara09 = Kara(0);
        strVal09 += Kara09;

        strVal10 = SOKUTEIstrI( j, KM01_04Data.SK_HSC_A, KD61Data.HSC_A_VAL[j]);
        Kara10 = Kara(0);
        strVal10 += Kara10;

        strVal11 = SOKUTEIstrI( j, KM01_04Data.SK_HSC_S, KD61Data.HSC_S_VAL[j]);
        Kara11 = Kara(0);
        strVal11 += Kara11;

        strVal12 = SOKUTEIstrF( j, KM01_04Data.SK_HSD_A, KD61Data.HSD_A_VAL[j],1);
        Kara12 = Kara(0);
        strVal12 += Kara12;

        strVal13 = SOKUTEIstrF( j, KM01_04Data.SK_HSD_S, KD61Data.HSD_S_VAL[j],1);
        Kara13 = Kara(0);
        strVal13 += Kara13;

       //                   �@  �A   �B  �C   �D   �E   �F   �G   �H   �I   �J   �K  �L
       //                  ��d���� ���ʈ��� ���� ��RL��RR�Ȃ� ���� ���� ����  ��  �c
        wsprintf(strVal_c,"%8s %12s %8s %10s %10s %12s %12s %19s%19s %15s %17s %15s %15s",
                            strVal01.c_str(),
                            strVal10.c_str(),
                            strVal11.c_str(),
                            strVal12.c_str(),
                            strVal13.c_str(),
                            strVal05.c_str(),
                            strVal06.c_str(),
                            strVal03.c_str(),
                            strVal02.c_str(),
                            strVal04.c_str(),
                            strVal07.c_str(),
                            strVal08.c_str(),
                            strVal09.c_str()
                               );

        //20161024 Y.Onishi �H��敪�ǉ�
        /*
        if ( Flagcnd == 2 ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s') ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s') ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr,
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                           );
        }
        */
        if ( Flagcnd == 2 ) {
            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','������(%s)','%s','%s',%d) ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            UPDCHRstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );
        }
        else {
            str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

            wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'%s','%s','%s','%s','%s',%d) ",
                            Master_rec + j + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            strVal_c,
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr,
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                           );
        }

        //str += str_c;
        Form1->Q_TW_TKS21PR->SQL->Add( str + str_c);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();
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

}
/***********************************************************************
*  function name : void UPDCHRInsert01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������̃f�[�^�����[�N�ɒǉ�                        *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHRInsert01(void)
{
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];

    str_c[0] = '\0';
    //Initial Query
    Form1->Q_TW_TKS21PR->Close();
    Form1->Q_TW_TKS21PR->SQL->Clear();

    //add sql INSERT
    //20161024 Y.Onishi �H��敪�ǉ�
    /*
    str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO) ";

    wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'������(%s)','%s','%s','%s','%s') ",
                            Master_rec + DataNo + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            UPDCHRstr.c_str(),
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str()
                            );
    */
    str = "insert into TW_TKS21PR(CODE,KENYMD,TRYNO,SAMPLE_P,DTKSCOD,PASS,NEWPAGE,SOKUTEI_NM,STR1,STR2,STR3,DTKSHIN,LOTNO,KOJOKBN) ";

    wsprintf(str_c,"values(%d,'%s',%d,%d,'%s',%d,%d,%d,'������(%s)','%s','%s','%s','%s',%d) ",
                            Master_rec + DataNo + 1,
                            KM01_04Data.KENSA_YMD.c_str(),
                            KM01_04Data.TOLEY_NO,
                            KM01_04Data.SAMPLE_P,
                            KM01_04Data.DTKSCOD.c_str(),
                            pass,
                            newpage,
                            DataNo,
                            UPDCHRstr.c_str(),
                            KIKAKUMINstr.c_str(),
                            KIKAKUMAXstr.c_str(),
                            KM01_04Data.DTKSHIN.c_str(),
                            KM01_04Data.LOTNO.c_str(),
                            KM01_04Data.KOJOKBN
                            );

        //str += str_c;
        Form1->Q_TW_TKS21PR->SQL->Add(str + str_c);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();
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
*  function name : void UPDCHR_Serch01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �X�V�҂̃O���[�v��                                  *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_Serch01(void)
{
    AnsiString x[13][13];
    int str[13];
    AnsiString str2[13];
    AnsiString str3[13];
    AnsiString SQLstr;
    int flag[13];
    int i,j,n,m;


    memset(flag, (int)NULL, sizeof(int) * 13);
    memset(str, (int)NULL, sizeof(int) * 13);
    memset(str2, (int)NULL, sizeof(AnsiString) * 13);
//    str[0] = KD51Data.UPDCHR;
//    str[2] = KD71Data.UPDCHR;
//    str[3] = KD81Data.UPDCHR;
//    str[4] = KD91Data.UPDCHR;
//    str[5] = KD31Data.UPDCHR;
//    str[6] = KD41Data.UPDCHR;
//    str[7] = KD01Data.UPDCHR;
//    str[8] = KD11Data.UPDCHR;
//    str[9] = KD21Data.UPDCHR;
//    str[1] = KD61Data.UPDCHR;
//
//    str2[0] = "���|��d";
//     str2[2] = "��R��";
//    str2[3] = "�Ȃ�����";
//    str2[4] = "����";
//    str2[5] = "��t��R";
//    str2[6] = "��t���x";
//    str2[7] = "������";
//    str2[8] = "�u���V��";
//    str2[9] = "�u���V�c";
//    str2[1] = "HsC/HsD";
    str[0] = -1;
    str[5] = -1;
    str[6] = -1;
    str[7] = -1;
    str[8] = -1;
    str[9] = -1;
    str[10] =-1;
    str[11] =-1;
    str[12] =-1;
    str[1] = -1;
    str[2] = -1;
    str[3] = -1;
    str[4] = -1;
    if ( ( KD51Data.BOTAI_NM != 0 ) && ( KD51Data.SOKUTEI_SU > 0 )	 ) str[0] = KD51Data.UPDCHR;
    if ( ( KD71Data.KOYU_NM != 0 ) && ( KD71Data.SOKUTEI_SU > 0 )	 ) str[5] = KD71Data.UPDCHR;
    if ( ( KD81Data.MAGE_NM != 0 ) && ( KD81Data.SOKUTEI_SU > 0 )	 ) str[6] = KD81Data.UPDCHR;
    if ( ( KD91Data.ZAKUT_NM != 0 ) && ( KD91Data.SOKUTEI_SU > 0 )	 ) str[7] = KD91Data.UPDCHR;
    if ( ( KD31Data.LD_TR_NM != 0 ) && ( KD31Data.SOKUTEI_SU > 0 )	 ) str[8] = KD31Data.UPDCHR;
    if ( ( KD41Data.LD_HP_NM != 0 ) && ( KD41Data.SOKUTEI_SU > 0 )	 ) str[9] = KD41Data.UPDCHR;
    if ( ( KD01Data.LD_LNG_NM != 0 ) && ( KD01Data.SOKUTEI_SU > 0 ) ) str[10] = KD01Data.UPDCHR;
    if ( ( KD11Data.BURASI_NM != 0 ) && ( KD11Data.SOKUTEI_SU > 0 ) ) str[11] = KD11Data.UPDCHR;
    if ( ( KD21Data.BURASIT_NM != 0 ) && ( KD21Data.SOKUTEI_SU > 0 )) str[12] = KD21Data.UPDCHR;
    if ( ( KD61Data.HSC_A_SK_NM  != 0 ) && ( KD61Data.HSC_SK_SU  > 0 )) str[1] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSC_S_SK_NM  != 0 ) && ( KD61Data.HSC_SK_SU  > 0 )) str[2] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSD_A_SK_NM  != 0 ) && ( KD61Data.HSD_SK_SU  > 0 )) str[3] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSD_S_SK_NM  != 0 ) && ( KD61Data.HSD_SK_SU  > 0 )) str[4] = KD61Data.UPDCHR;


    str2[0] = "���|��d";
    str2[5] = "��R��";
    str2[6] = "�Ȃ�����";
    str2[7] = "����";
    str2[8] = "��t��R";
    str2[9] = "��t���x";
    str2[10] = "������";
    str2[11] = "�u���V��";
    str2[12] = "�u���V�c";
    str2[1] = "HsC(����)";
    str2[2] = "HsC(����)";
    str2[3] = "HsD(����)";
    str2[4] = "HsD(����)";




    for ( i = 0; i < 12; i++ ) {
        //�S���҃}�X�^����}�X�^�f�[�^�𒊏o
        Form1->Q_STRS->Close();
        Form1->Q_STRS->SQL->Clear();
        //�₢���������s
        //�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	    SQLstr = "SELECT ";
	    SQLstr += "TANNAM  FROM SM12S ";
        SQLstr += "WHERE  TANSYA = '" + IntToStr(str[i]) + "'" ;
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
     UPDCHRstr = "";
    for ( i = 0; i < 12; i++ ) {
        if ( str[i] != -1 ) {
            n = 0;
            if ( flag[i] == 0 ) {
                if ( n == 0 ) n = 1;
                else  UPDCHRstr += "/";
                UPDCHRstr += str2[i];
            }
            for ( j = i + 1; j < 12; j++ ) {
                if ( str[i] == str[j] ) {
                    if ( flag[j] == 0 ) {
                        if ( n == 0 ) n = 1;
                        else  UPDCHRstr += "/";
                        UPDCHRstr += str2[j];
                        flag[j] = 1;
                    }
                }
            }
            if ( flag[i] == 0 ) {
                UPDCHRstr += "=";
                UPDCHRstr += str3[i];
                UPDCHRstr += "  ";

            }
        }

    }

    m = 0;



}
/***********************************************************************
*  function name : void UPDCHR_2_Serch01(void)                         *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : �X�V�҂̃O���[�v��                                  *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void UPDCHR_2_Serch01(void)
{
    AnsiString x[13][13];
    int str[13];
    AnsiString str2[13];
    AnsiString str3[13];
    AnsiString SQLstr;
    int flag[13];
    int i,j,n,m;


    memset(flag, (int)NULL, sizeof(int) * 13);
    memset(str, (int)NULL, sizeof(int) * 13);
    memset(str2, (int)NULL, sizeof(AnsiString) * 13);
//    str[0] = KD51Data.UPDCHR;
//    str[2] = KD71Data.UPDCHR;
//    str[3] = KD81Data.UPDCHR;
//    str[4] = KD91Data.UPDCHR;
//    str[5] = KD31Data.UPDCHR;
//    str[6] = KD41Data.UPDCHR;
//    str[7] = KD01Data.UPDCHR;
//    str[8] = KD11Data.UPDCHR;
//    str[9] = KD21Data.UPDCHR;
//    str[1] = KD61Data.UPDCHR;
//
//    str2[0] = "���|��d";
//     str2[2] = "��R��";
//    str2[3] = "�Ȃ�����";
//    str2[4] = "����";
//    str2[5] = "��t��R";
//    str2[6] = "��t���x";
//    str2[7] = "������";
//    str2[8] = "�u���V��";
//    str2[9] = "�u���V�c";
//    str2[1] = "HsC/HsD";
    str[0] = -1;
    str[5] = -1;
    str[6] = -1;
    str[7] = -1;
    str[8] = -1;
    str[9] = -1;
    str[10] =-1;
    str[11] =-1;
    str[12] =-1;
    str[1] = -1;
    str[2] = -1;
    str[3] = -1;
    str[4] = -1;
    if ( ( KD51Data.BOTAI_NM != 0 ) && ( KD51Data.SOKUTEI_SU > 0 )	 ) str[0] = KD51Data.UPDCHR;
    if ( ( KD71Data.KOYU_NM != 0 ) && ( KD71Data.SOKUTEI_SU > 0 )	 ) str[5] = KD71Data.UPDCHR;
    if ( ( KD81Data.MAGE_NM != 0 ) && ( KD81Data.SOKUTEI_SU > 0 )	 ) str[6] = KD81Data.UPDCHR;
    if ( ( KDC1Data.MAGEG_NM != 0 ) && ( KDC1Data.SOKUTEI_SU > 0 )	 ) str[7] = KD81Data.UPDCHR;
    if ( ( KD91Data.ZAKUT_NM != 0 ) && ( KD91Data.SOKUTEI_SU > 0 )	 ) str[8] = KD91Data.UPDCHR;
    if ( ( KD01Data.LD_LNG_NM != 0 ) && ( KD01Data.SOKUTEI_SU > 0 ) ) str[9] = KD01Data.UPDCHR;
    if ( ( KD11Data.BURASI_NM != 0 ) && ( KD11Data.SOKUTEI_SU > 0 ) ) str[10] = KD11Data.UPDCHR;
    if ( ( KD21Data.BURASIT_NM != 0 ) && ( KD21Data.SOKUTEI_SU > 0 )) str[11] = KD21Data.UPDCHR;
    if ( ( KD61Data.HSC_A_SK_NM  != 0 ) && ( KD61Data.HSC_SK_SU  > 0 )) str[1] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSC_S_SK_NM  != 0 ) && ( KD61Data.HSC_SK_SU  > 0 )) str[2] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSD_A_SK_NM  != 0 ) && ( KD61Data.HSD_SK_SU  > 0 )) str[3] = KD61Data.UPDCHR;
    if ( ( KD61Data.HSD_S_SK_NM  != 0 ) && ( KD61Data.HSD_SK_SU  > 0 )) str[4] = KD61Data.UPDCHR;


    str2[0] = "���|��d";
    str2[5] = "��R��";
    str2[6] = "�Ȃ�����";
    str2[7] = "�����Ȃ�����";
    str2[8] = "����";
    str2[9] = "������";
    str2[10] = "�u���V��";
    str2[11] = "�u���V�c";
    str2[1] = "HsC(����)";
    str2[2] = "HsC(����)";
    str2[3] = "HsD(����)";
    str2[4] = "HsD(����)";




    for ( i = 0; i < 12; i++ ) {
        //�S���҃}�X�^����}�X�^�f�[�^�𒊏o
        Form1->Q_STRS->Close();
        Form1->Q_STRS->SQL->Clear();
        //�₢���������s
        //�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
	    SQLstr = "SELECT ";
	    SQLstr += "TANNAM  FROM SM12S ";
        SQLstr += "WHERE  TANSYA = '" + IntToStr(str[i]) + "'" ;
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
     UPDCHRstr = "";
    for ( i = 0; i < 12; i++ ) {
        if ( str[i] != -1 ) {
            n = 0;
            if ( flag[i] == 0 ) {
                if ( n == 0 ) n = 1;
                else  UPDCHRstr += "/";
                UPDCHRstr += str2[i];
            }
            for ( j = i + 1; j < 12; j++ ) {
                if ( str[i] == str[j] ) {
                    if ( flag[j] == 0 ) {
                        if ( n == 0 ) n = 1;
                        else  UPDCHRstr += "/";
                        UPDCHRstr += str2[j];
                        flag[j] = 1;
                    }
                }
            }
            if ( flag[i] == 0 ) {
                UPDCHRstr += "=";
                UPDCHRstr += str3[i];
                UPDCHRstr += "  ";

            }
        }

    }

    m = 0;



}

/***********************************************************************
*  function name : void PASS_FailUpdate01(void)                        *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : PASS��0�i�s���i�j�ɂ���                             *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void PASS_FailUpdate01(void)
{
    int i,j,n,k;
    AnsiString str;
    char str_c[STRMAX];
    char strVal_c[STRMAX];
    char strBlank_c[10];
    char strTest_C[STRMAX];
    AnsiString tableNo;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;

        str_c[0] = '\0';
        //Initial Query
        Form1->Q_TW_TKS21PR->Close();
        Form1->Q_TW_TKS21PR->SQL->Clear();

        //add sql UPDATE
        str = "UPDATE TW_TKS21PR SET PASS = " + IntToStr( pass ) + " ";

        //add sql VALUES  ������strVal_c  �󔒁�strBlank_c
        strVal01 = KM01_04Data.KENSA_YMD;
        strVal02 = IntToStr( KM01_04Data.TOLEY_NO );
        strVal03 = IntToStr( KM01_04Data.SAMPLE_P );

	    str += "WHERE  TW_TKS21PR.KENSA_YMD = '" + strVal01 + "' ";
	    str += "and TW_TKS21PR.TOLEY_NO = " + strVal02 + " ";
	    str += "and TW_TKS21PR.SAMPLE_P = " + strVal03 + " ";

        Form1->Q_TW_TKS21PR->SQL->Add(str);

        //execute sql
        try
        {
            Form1->Q_TW_TKS21PR->ExecSQL();
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

