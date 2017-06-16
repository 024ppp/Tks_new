/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_MakeData.cpp                                      *
*  create        : 1999.10.18                                          *
*  update        :                                                     *
*  contents      : ����f�[�^�쐬�v���O����                            *
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
*  function name : void MakeData(void)                                 *
*                  +--------------------------------------+            *
*          ��  ��  | �Ȃ�       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | �Ȃ�       |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ����f�[�^���쐬����                                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void MakeData(void)
{
    int i,j,n;
    double k;
    Master_rec = 3;//�}�X�^������s
    rec = 0;       //���R�[�h��
    pass = 1;      //���i1�A�s���i0
    newpage = 1;   //���y�[�WNo
    Last_DTKSCOD = "";
    AnsiString str;
    //�󔒕����̐ݒ�
    //strcpy(strBlank_c,"   ");

    KM01_04Serch01();        //�����w���}�X�^����}�X�^�f�[�^�𒊏o

    //���[�N�e�[�u���Ɉ���f�[�^����͂��Ă���
    //���[�N�e�[�u�� ������
    //Initial Query
    Form1->Q_TW_TKS21PR->Close();
    Form1->Q_TW_TKS21PR->SQL->Clear();
    str = "delete from TW_TKS21PR";
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
    Form1->Q_TW_TKS21PR->Close();

    //���[�N�e�[�u��(������) ������
    //Initial Query
    Form1->Q_TW_UPDCHR->Close();
    Form1->Q_TW_UPDCHR->SQL->Clear();
    str = "delete from TW_UPDCHR";
    Form1->Q_TW_UPDCHR->SQL->Add(str);

    //execute sql
    try
    {
        Form1->Q_TW_UPDCHR->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
        ShowMessage(e.Message);
    }
    catch(Exception& e)
    {
        ShowMessage(e.Message);
    }
    Form1->Q_TW_UPDCHR->Close();


    //if ( Form1->Q_KM01->RecordCount == 0 ) {
    if ( Form1->Q_KM01->Bof == true  && Form1->Q_KM01->Eof == true ) {
        ShowMessage("�����f�[�^����܂���");
        return;
    }
    Form1->Q_KM01->First();
    Last_DTKSCOD = Form1->Q_KM01->FieldValues["DTKSCOD"];
    i = 0;
    n = Form1->Q_KM01->RecordCount;
    k = 100 / ( n * 1.0 );
    while( !Form1->Q_KM01->Eof ) {

        Form1->ProgressBar1->Position = int(k * i);

		//�����z��̏�����
		//memset(KM01_04Data, (int)NULL, sizeof(struct structKM01_04));
        pass = 1;
        DataNo = 0;
        KD01Format01();
        KD11Format01();
        KD21Format01();
        KD31Format01();
        KD41Format01();
        KD51Format01();
        KD61Format01();
        KD71Format01();
        KD81Format01();
        KD91Format01();

        //2002.12.05 E.Takase �R���~�p�̏����ǉ�
        KDC1Format01();
        KD71_LFormat01();
        KD71_RFormat01();


        /**********************/
        /*                    */
        /* ���Ӑ�i�Ԃ���K�i */
        /*                    */
        /**********************/
        KM01_04Sub01();                 //�J�����g���R�[�h�̓��e��ϐ��ɑ��

        if ( Last_DTKSCOD != KM01_04Data.DTKSCOD )  {
            Last_DTKSCOD = KM01_04Data.DTKSCOD;
            newpage++;
        }


        /*************************/
        /*                       */
        /*   �����l�̍s��ǉ�    */
        /*                       */
        /*************************/
        //�����l����͂���s��ǉ�

        //�����l���X�V���Ă���
        KD01_02Serch01();               //���[�h�������f�[�^�t�@�C������f�[�^�𒊏o
        KD01Compare01();                //���[�h�������f�[�^���K�i�����ǂ����𔻒f

        KD11_12Serch01();               //�u���V�����@�f�[�^�t�@�C������f�[�^�𒊏o
        KD11Compare01();                //�u���V�����@�f�[�^���K�i�����ǂ����𔻒f

        KD21_22Serch01();               //�u���V�����@�c�����f�[�^�t�@�C������f�[�^�𒊏o
        KD21Compare01();                //�u���V�����@�c�����f�[�^���K�i�����ǂ����𔻒f

        //�R���~����̏ꍇ�͎��s���Ȃ�
        if ( Flagcnd == 0 || Flagcnd == 1 ) {
           KD31_32Serch01();               //���[�h����t��R�f�[�^�t�@�C������f�[�^�𒊏o
           KD31Compare01();                //���[�h����t��R�f�[�^���K�i�����ǂ����𔻒f

           KD41_42Serch01();               //���[�h���������x�f�[�^�t�@�C������f�[�^�𒊏o
           KD41Compare01();                //���[�h���������x�f�[�^���K�i�����ǂ����𔻒f
        }

        KD51_52Serch01();               //��̔�d�f�[�^�t�@�C������f�[�^�𒊏o
        KD51Compare01();                //��̔�d�f�[�^���K�i�����ǂ����𔻒f

        KD61_62Serch01();               //�g���d�x�f�[�^�t�@�C������f�[�^�𒊏o
        KD61Compare01();                //�g���d�x�f�[�^���K�i�����ǂ����𔻒f

        KD71_72Serch01();               //�ŗL��R���f�[�^�t�@�C������f�[�^�𒊏o
        KD71Compare01();                //�ŗL��R���f�[�^���K�i�����ǂ����𔻒f

        KD81_82Serch01();               //�R�ܗ̓f�[�^�t�@�C������f�[�^�𒊏o
        KD81Compare01();                //�R�ܗ̓f�[�^���K�i�����ǂ����𔻒f

        KD91_92Serch01();               //�����f�[�^�t�@�C������f�[�^�𒊏o
        KD91Compare01();                //�����f�[�^���K�i�����ǂ����𔻒f

        //�R���~����̏ꍇ�͎��s����
        if ( Flagcnd == 2 || Flagcnd == 3 ) {

           KD71_72_LSerch01();               //�ŗL��R�����f�[�^�t�@�C������f�[�^�𒊏o
           KD71_LCompare01();                //�ŗL��R�����f�[�^���K�i�����ǂ����𔻒f
           KD71_72_RSerch01();               //�ŗL��R���E�f�[�^�t�@�C������f�[�^�𒊏o
           KD71_RCompare01();                //�ŗL��R���E�f�[�^���K�i�����ǂ����𔻒f
           KDC1_C2Serch01();                 //�����Ȃ��f�[�^�t�@�C������f�[�^�𒊏o
           KDC1Compare01();                  //�����Ȃ��f�[�^���K�i�����ǂ����𔻒f

        }

        PassSet();                      //���i���s���i������
        DataNoSet();                    //�ő呪��f�[�^������

        //if ( pass == 1 ) {
        //    if ( KD61Data.PASS == 0 ) {
        //        pass = 0;
        //        PASS_FailUpdate01();    //�s���i�t���O������
        //    }
        //}

	switch(Flagcnd)
	{
		case 0:
            if ( DataNo != -1 ) {
                Master_rec = 2;

                //������������쐬
                UPDCHR_Make01(i);

                UPDCHR_Serch01();               //�X�V�҂̃O���[�v��

                DTKSHIN_CIYCLEInsert01();       //���Ӑ�i�Ԃ��� ���َ��Ԃ܂ł̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MINInsert01();           //�������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MAXInsert01();           //�������ڂ̋K�i��̃f�[�^�����[�N�ɒǉ�

                SOKUTEIInsert01();              //�������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�
            }
			break;

		case 1:
            if ( DataNo != -1 ) {
                Master_rec = 1;

                KIKAKU_MINInsert01();           //�������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MAXInsert01();           //�������ڂ̋K�i��̃f�[�^�����[�N�ɒǉ�

                UPDCHR_Serch01();               //�X�V�҂̃O���[�v��

                LOT_SOKUTEIInsert01();       //���Ӑ�i�Ԃ��� ���َ��Ԃ܂ł̃f�[�^�����[�N�ɒǉ�


                SOKUTEIInsert01();              //�������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�

                UPDCHRInsert01();               //�������̃f�[�^�����[�N�ɒǉ�
            }
			break;
		case 2:
            if ( DataNo != -1 ) {
                Master_rec = 2;

                //������������쐬
                UPDCHR_2_Make01(i);

                UPDCHR_Serch01();               //�X�V�҂̃O���[�v��

                DTKSHIN_CIYCLEInsert01();       //���Ӑ�i�Ԃ��� ���َ��Ԃ܂ł̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MINInsert02();           //�������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MAXInsert01();           //�������ڂ̋K�i��̃f�[�^�����[�N�ɒǉ�

                SOKUTEIInsert02();              //�������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�
            }
			break;

		case 3:
            if ( DataNo != -1 ) {
                Master_rec = 1;

                KIKAKU_MINInsert02();           //�������ڂ̋K�i���̃f�[�^�����[�N�ɒǉ�

                KIKAKU_MAXInsert01();           //�������ڂ̋K�i��̃f�[�^�����[�N�ɒǉ�

                UPDCHR_Serch01();               //�X�V�҂̃O���[�v��

                LOT_SOKUTEIInsert01();       //���Ӑ�i�Ԃ��� ���َ��Ԃ܂ł̃f�[�^�����[�N�ɒǉ�


                SOKUTEIInsert02();              //�������ڂ̑���l�̃f�[�^�����[�N�ɒǉ�

                UPDCHRInsert01();               //�������̃f�[�^�����[�N�ɒǉ�
            }
			break;
	}


        Form1->Q_KM01->Next();  //���̃��R�[�h�Ɉړ�
        i++;
    }


    if ( Flagcnd == 0 ) {
        if ( DataNo != -1 ) {
            //������������쐬
            UPDCHR_Make01(-2);
        }
    }

}


