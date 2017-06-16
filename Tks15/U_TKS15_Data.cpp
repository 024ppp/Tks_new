/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�T�j                  *
*  file   name   : U_TKS15_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��̔�d���菈���f�[�^�A�N�Z�X�֐�                  *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ���[�N�ϐ�

// �֐��̐錾
void KD51Format(void);
void SetTable51(void);
int  Kd52_Serch02( AnsiString , int , int, int );
void Kd52_Update01( int );
void Kd52_Update02( AnsiString , int, int, int );
void Kd52_Insert01( AnsiString , int ,int, int );
void SetTable53W(int);
//int Kd51_Serch03(void);
void SetTable51_C(void);

/***********************************************************************
*  function name : int  Kd51_Serch01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��̔�d�ް�̧�ق��猟���\����A�ڰNo�𒊏o           *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int Kd51_Serch01(void)
{

    // ��̔�d�ް�̧�ق���}�X�^�f�[�^�𒊏o
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD51.KENSA_YMD, KD51.TOLEY_NO ";
    sBuf += "FROM KD51 ";
	sBuf += "WHERE KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
    sBuf += "ORDER BY KD51.KENSA_YMD desc, KD51.TOLEY_NO";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;


    sBuf = "�����\��N����";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "�ڰNO.";
    Form2->SGr1->Cells[2][iRow] = sBuf;

    iRow += 1;

    if ( Form1->Query1->Eof ) {
      return -1;
    }else {
      Form1->Query1->First();
      while( !Form1->Query1->Eof ) {

            // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

            sBuf = Form1->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] = sBuf;

            sBuf = Form1->Query1->Fields->Fields[1]->AsString;
            Form2->SGr1->Cells[2][iRow] = sBuf;


            Form1->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return 1 ;
 }


/***********************************************************************
*  function name : void Kd51_Serch02(int flag)                         *
*                  +--------------------------------------+            *
*          ��  ��  |  int       |   flag                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL�� �C��)                              *
*  contents      : ��̔�d�ް�̧�ق����ް��𒊏o  KD51                *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd51_Serch02(int flag)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD51Data�\���̕ϐ��̏�����(�u�����v���݂��������ꍇ)
        if( !Save_Click ) KD51Format();

        //�����l�̂̎擾
        strVal01 = DelSEPA(Form1->edtymd->Text);

        if( Save_Click ){
           n= Form1->edttlno->Value + 1;
           strVal02 = IntToStr(n);
        }else
           strVal02 = Form1->edttlno->Text;

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //�₢���������s
        //�\�[�g���� ,�����\����A�g���[No
	    sBuf = "SELECT *  ";
	    sBuf += "FROM KD51 ";
	    sBuf += "WHERE  KD51.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD51.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	    //2001.05.21 �C�� sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	    sBuf += "ORDER BY KD51.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD51�Ƀf�[�^������܂���");
          return -1;
        }else {

           // �u�ۑ��v���݂������Ď����ڰNO����������ꍇ
           if( Save_Click )  {
               // �ڰNO�̐ݒ�
               Form1->edttlno->Text = strVal02 ;

               // KD51Data�\���̕ϐ��̏�����
               KD51Format();
           }
           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable51();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD51Data[i].SOKUTE_KBN  && KD51Data[i].SAMPLE_P != -1 ) {
             if( KD51Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD51Data[i].DTKSHIN == KD51Data[j].DTKSHIN)
                        KD51Data[j].LINK = KD51Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //�v�����m���Q�̏ꍇ ��̔�d����i��O�j̧�ق�ǂݍ���
       for( i=0; i<30; i++ )
       {
        //  if( KD51Data[i].SOKUTEI_NM > 2 && KD51Data[i].SOKUTE_KBN == 1 &&
        //      KD51Data[i].SOKUTEI_NB_CUR  ) {

              if( KD51Data[i].SOKUTE_KBN == 1 ){

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD51Data[i].SAMPLE_P );

              //�₢���������s
              //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KD52 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	        //2001.05.21 �C�� sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD52�Ƀf�[�^������܂���");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {

                            //����NO
                            if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             //�������@
                             if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                   KD51Data[i].SOKUTEI_S[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                             }
                             //���i�O�a�j���@
                            if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                   KD51Data[i].SOKUTEI_H[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                             }
                             //�������@
                             if ( Form1->Query1->FieldValues["SOKUHEI_N"].IsNull()) {
                                   KD51Data[i].SOKUTEI_N[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_N[n-1] =  Form1->Query1->FieldValues["SOKUHEI_N"];
                             }
                             //�d��
                            if ( Form1->Query1->FieldValues["SOKUTEI_J"].IsNull()) {
                                   KD51Data[i].SOKUTEI_J[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_J[n-1] =  Form1->Query1->FieldValues["SOKUTEI_J"];
                             }
                             //��̔�d
                             if ( Form1->Query1->FieldValues["SOKUTEI_B"].IsNull()) {
                                   KD51Data[i].SOKUTEI_B[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_B[n-1] =  Form1->Query1->FieldValues["SOKUTEI_B"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

       //�R���~�̃f�[�^�i���a�E�O�^�j�R�s�[
       if ( flag == 1 ) {
          SetTable51_C();
       }

    return 1;
}
/***********************************************************************
*  function name : int  Kd51_Serch03(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 2003.02                                             *
*  update        :                                                     *
*  contents      : ��̔�d�ް�̧�ق����ް��𒊏o  KD51 �R���~�̂�     *
*  written by    : ���� �b��(JFE MTS Corp.)                            *
***********************************************************************/
int Kd51_Serch03(void)
{

	int n,i;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//�����l�̂̎擾
	strVal01 = DelSEPA(Form1->edtymd->Text);

	if( Save_Click ){
		n= Form1->edttlno->Value + 1;
		strVal02 = IntToStr(n);
	}else
		strVal02 = Form1->edttlno->Text;

	Form1->Query2->Close();
	Form1->Query2->SQL->Clear();

	//�₢���������s
	//�\�[�g���� ,�����\����A�g���[No
	sBuf = "SELECT *  ";
	sBuf += "FROM KD51 ";
	sBuf += "WHERE  KD51.KENSA_YMD = '" + strVal01 + "' ";
	sBuf += "AND  KD51.TOLEY_NO = '" + strVal02 + "' ";
	sBuf += "AND  KD51.KEIJYO_KBN = 5 ";
        sBuf += "AND  KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // �H��敪�ǉ�
	//2001.05.21 �C�� sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	sBuf += "ORDER BY KD51.SAMPLE_P";

	Form1->Query2->SQL->Add(sBuf);
	Form1->Query2->Open();

	if ( Form1->Query2->Eof ) {
		return -1;

	}

	return 1;



}


/***********************************************************************
*  function name : void SetTable51(int )                               *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : KD51Data�\���̂��ް���ݒ�                          *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable51()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD51Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

      //�����\���
     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD51Data[iRec].KENSA_YMD = " ";
     }else {
          KD51Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }
     //�ڰNO
     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD51Data[iRec].TOLEY_NO = 0;
     }else {
          KD51Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }
     //����敪
     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD51Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD51Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 && KD51Data[iRec].SOKUTE_KBN == 1 ){
              HaveSokutei = 1;
          }
     }
     //���Ӑ溰��
     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD51Data[iRec].DTKSCOD = " ";
     }else {
          KD51Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }
     //���Ӑ�i��
     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD51Data[iRec].DTKSHIN = " ";
     }else {
          KD51Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }
     //ۯ�NO
     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD51Data[iRec].LOTNO = " ";
     }else {
          KD51Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }
     //���Еi��
     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD51Data[iRec].HINBAN = " ";
     }else {
          KD51Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }
     //�ގ�����
     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD51Data[iRec].ZISCOD = " ";
     }else {
          KD51Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }
     //�ގ���
     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD51Data[iRec].ZISNAM = " ";
     }else {
          KD51Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }
     //��̔�d ����
     if ( Form1->Query1->FieldValues["BOTAI_MIN"].IsNull()) {
          KD51Data[iRec].BOTAI_MIN = 0.0;
     }else {
          KD51Data[iRec].BOTAI_MIN =  Form1->Query1->FieldValues["BOTAI_MIN"];
     }
     //��̔�d ���
     if ( Form1->Query1->FieldValues["BOTAI_MAX"].IsNull()) {
          KD51Data[iRec].BOTAI_MAX = 0.0;
     }else {
          KD51Data[iRec].BOTAI_MAX =  Form1->Query1->FieldValues["BOTAI_MAX"];
     }
     //�`��敪
     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KD51Data[iRec].KEIJYO_KBN = 0;
     }else {
          KD51Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }

     // �������@�P�A�������@�Q
      if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
          KD51Data[iRec].SOKUTEI_S[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
          KD51Data[iRec].SOKUTEI_S[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
     }

     //��(�O�`)���@�P�A���i�O�`�j���@�Q
      if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
          KD51Data[iRec].SOKUTEI_H[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
          KD51Data[iRec].SOKUTEI_H[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
     }

      //�������@�P�A�������@�Q
     if ( Form1->Query1->FieldValues["SOKUTEI_1N"].IsNull()) {
          KD51Data[iRec].SOKUTEI_N[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_N[0] =  Form1->Query1->FieldValues["SOKUTEI_1N"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2N"].IsNull()) {
          KD51Data[iRec].SOKUTEI_N[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_N[1] =  Form1->Query1->FieldValues["SOKUTEI_2N"];
     }
     //�d�ʂP�A�d�ʂQ
      if ( Form1->Query1->FieldValues["SOKUTEI_1J"].IsNull()) {
          KD51Data[iRec].SOKUTEI_J[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_J[0] =  Form1->Query1->FieldValues["SOKUTEI_1J"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2J"].IsNull()) {
          KD51Data[iRec].SOKUTEI_J[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_J[1] =  Form1->Query1->FieldValues["SOKUTEI_2J"];
     }

     //����l�P ����l�Q, ��̔�d
     if ( Form1->Query1->FieldValues["SOKUTEI_1B"].IsNull()) {
          KD51Data[iRec].SOKUTEI_B[0] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_B[0] =  Form1->Query1->FieldValues["SOKUTEI_1B"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2B"].IsNull()) {
          KD51Data[iRec].SOKUTEI_B[1] = 0.0;
     }else {
          KD51Data[iRec].SOKUTEI_B[1] =  Form1->Query1->FieldValues["SOKUTEI_2B"];
     }

     //�����
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD51Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD51Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD51Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD51Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }
     //����l���ϒl�i��̔�d�j
     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD51Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD51Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }
     //�o�^��
     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD51Data[iRec].ADDYMD = " ";
     }else {
          KD51Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
     }

    if( IsNullSpace( KD51Data[iRec].ADDYMD ) ){
             KD51Data[iRec].SOKUTEI_NB_CUR = 0 ;
             KD51Data[iRec].SOKUTEI_NS_CUR = 0;
             KD51Data[iRec].SOKUTEI_NH_CUR = 0;
             KD51Data[iRec].SOKUTEI_NN_CUR = 0;
             KD51Data[iRec].SOKUTEI_NJ_CUR = 0;
    }else{
             KD51Data[iRec].SOKUTEI_NB_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NS_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NH_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NN_CUR = KD51Data[iRec].SOKUTEI_SU ;
             KD51Data[iRec].SOKUTEI_NJ_CUR = KD51Data[iRec].SOKUTEI_SU ;
    }

     //�o�^����
     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD51Data[iRec].ADDTIM = " ";
     }else {
          KD51Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }
     //�X�V��
     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD51Data[iRec].UPDYMD = " ";
     }else {
          KD51Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }
     //�X�V����

     //�X�V��
     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD51Data[iRec].UPDCHR = 0;
     }else {
          KD51Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     //�X�V��
     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD51Data[iRec].UPDCNT = 0;
     }else {
          KD51Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //���l 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD51Data[iRec].MEMO =  " ";
     }else {
          KD51Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

 }

/***********************************************************************
*  function name : void SetTable51_C(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2003.02                                             *
*  update        :                                                     *
*  contents      : KD51Data�\���̂��ް���ݒ�(�R���~�p)                *
*  written by    : ���� �b�� (JFE MTS Corp.)                           *
***********************************************************************/
void SetTable51_C(void)
{

	int n,i;
	AnsiString strVal01;
	AnsiString strVal02;
	AnsiString strVal03;

	//�����l�̂̎擾
	strVal01 = DelSEPA(Form1->edtymd->Text);

	if( Save_Click ){
		n= Form1->edttlno->Value + 1;
		strVal02 = IntToStr(n);
	}else
		strVal02 = Form1->edttlno->Text;

	for( i=0; i<30; i++ ) {
	
		if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].KEIJYO_KBN == 5 ){

			strVal03 = IntToStr( KD51Data[i].SAMPLE_P );

			//���a KD11
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//�₢���������s
			//�\�[�g���� ,�����\����A�g���[No
			sBuf = "SELECT SOKUTEI_1, SOKUTEI_2 ";
			sBuf += "FROM KD11 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				// ���a 
				if ( Form1->Query2->FieldValues["SOKUTEI_1"].IsNull()) {
					KD51Data[i].SOKUTEI_S[0] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_S[0] =  Form1->Query2->FieldValues["SOKUTEI_1"];
				}
				if ( Form1->Query2->FieldValues["SOKUTEI_2"].IsNull()) {
					KD51Data[i].SOKUTEI_S[1] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_S[1] =  Form1->Query2->FieldValues["SOKUTEI_2"];
				}

                //��̔�d�̌v�Z
                BHijyuCal(i+1, 1);
                BHijyuCal(i+1, 2);

			}

			//���a KD12
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//�₢���������s
			//�\�[�g���� ,�����\����A�g���[No
			sBuf = "SELECT SOKUTEI_NO,SOKUTEICHI ";
			sBuf += "FROM KD12 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				while( !Form1->Query2->Eof ) {
					//����NO
					if ( Form1->Query2->FieldValues["SOKUTEI_NO"].IsNull()) {
						n = 3;
					}else {
						n =  Form1->Query2->FieldValues["SOKUTEI_NO"];
					}
					// ���a 
					if ( Form1->Query2->FieldValues["SOKUTEICHI"].IsNull()) {
						KD51Data[i].SOKUTEI_S[n-1] = 0.0;
					}else {
						KD51Data[i].SOKUTEI_S[n-1] =  Form1->Query2->FieldValues["SOKUTEICHI"];
					}
                    Form1->Query2->Next();

                    //��̔�d�̌v�Z
                    BHijyuCal(i+1, n);
				}
			}

			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//�O�a KD21
			//�₢���������s
			//�\�[�g���� ,�����\����A�g���[No
			sBuf = "SELECT SOKUTEI_1, SOKUTEI_2 ";
			sBuf += "FROM KD21 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {

				//��(�O�`)���@�P�A���i�O�`�j���@�Q
				if ( Form1->Query2->FieldValues["SOKUTEI_1"].IsNull()) {
					KD51Data[i].SOKUTEI_H[0] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_H[0] =  Form1->Query2->FieldValues["SOKUTEI_1"];
				}
				if ( Form1->Query2->FieldValues["SOKUTEI_2"].IsNull()) {
					KD51Data[i].SOKUTEI_H[1] = 0.0;
				}else {
					KD51Data[i].SOKUTEI_H[1] =  Form1->Query2->FieldValues["SOKUTEI_2"];
				}
                //��̔�d�̌v�Z
                BHijyuCal(i+1, 1);
                BHijyuCal(i+1, 2);
			}

			//���a KD22
			Form1->Query2->Close();
			Form1->Query2->SQL->Clear();

			//�₢���������s
			//�\�[�g���� ,�����\����A�g���[No
			sBuf = "SELECT SOKUTEI_NO,SOKUTEICHI ";
			sBuf += "FROM KD22 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";

			Form1->Query2->SQL->Add(sBuf);
			Form1->Query2->Open();

			if (!( Form1->Query2->Eof )) {
				while( !Form1->Query2->Eof ) {
					//����NO
					if ( Form1->Query2->FieldValues["SOKUTEI_NO"].IsNull()) {
						n = 3;
					}else {
						n =  Form1->Query2->FieldValues["SOKUTEI_NO"];
					}
					// ���a 
					if ( Form1->Query2->FieldValues["SOKUTEICHI"].IsNull()) {
						KD51Data[i].SOKUTEI_H[n-1] = 0.0;
					}else {
						KD51Data[i].SOKUTEI_H[n-1] =  Form1->Query2->FieldValues["SOKUTEICHI"];
					}
                    Form1->Query2->Next();
                    //��̔�d�̌v�Z
                    BHijyuCal(i+1, n);

				}
			}


		}
	}


}



/***********************************************************************
*  function name : void KD51Format(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : ���[�h����t��R�f�[�^�\����KD51Data��������  KD51  *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD51Format(void)
{
   for( int i=0; i<30; i++){
      KD51Data[i].KENSA_YMD =  '\0';  //�����\���
      KD51Data[i].TOLEY_NO = 0 ;      //�ڰNO
      KD51Data[i].SAMPLE_P = -1 ;     //������߼޼��NO
      KD51Data[i].SOKUTE_KBN = 0;     //����敪
      KD51Data[i].DTKSCOD = '\0';     //���Ӑ�R�[�h
      KD51Data[i].DTKSHIN = '\0';     //���Ӑ�i��
      KD51Data[i].LOTNO = '\0';       //���b�gNO
      KD51Data[i].HINBAN = '\0';      //���Еi��
      KD51Data[i].ZISCOD = '\0';      //�ގ��R�[�h
      KD51Data[i].ZISNAM = '\0';      //�ގ���

      KD51Data[i].BOTAI_MAX = 0.0;    //��̔�d �K�i��
      KD51Data[i].BOTAI_MIN = 0.0;    //��̔�d �K�i��
      KD51Data[i].KEIJYO_KBN = 0;     //��̔�d �`��敪
      KD51Data[i].SOKUTEI_NM = 0;    //��̔�d �����
      KD51Data[i].SOKUTEI_SU = 0;    //��̔�d �����
      KD51Data[i].SOKUTE_AVE = 0.0;  //��̔�d ���蕽�ϒl

      memset(KD51Data[i].SOKUTEI_B,(int)NULL, sizeof(double) * 100); ;  //����l
      memset(KD51Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //�������@
      memset(KD51Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //�����@
      memset(KD51Data[i].SOKUTEI_N,(int)NULL, sizeof(double) * 100); ;  //����
      memset(KD51Data[i].SOKUTEI_J,(int)NULL, sizeof(double) * 100); ;  //�d��

      KD51Data[i].ADDYMD = '\0';      //�o�^��
      KD51Data[i].ADDTIM = '\0';      //�o�^����
      KD51Data[i].UPDYMD = '\0';      //�ύX��
      KD51Data[i].UPDTIM = '\0';      //�ύX����
      KD51Data[i].UPDCHR = 0;         //�X�V��
      KD51Data[i].UPDCNT = 0;         //�X�V��
      KD51Data[i].LINK = 0;
      KD51Data[i].SOKUTEI_NB_CUR = 0;
      KD51Data[i].SOKUTEI_NS_CUR = 0;
      KD51Data[i].SOKUTEI_NH_CUR = 0;
      KD51Data[i].SOKUTEI_NN_CUR = 0;
      KD51Data[i].SOKUTEI_NJ_CUR = 0;
      KD51Data[i].MEMO = '\0';         //���l 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void Kd51_Update01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : �v���ް����̔�d�ް�̧�ق֏�������  KD51            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd51_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // ��ʂ̓����ް����擾
    if( DataNoIdx == 1 ){

             // �v���ް�1
             if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_N[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==4)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_J[0] = pEdt1_S[iKomoku-1]->Value;

              BHijyuCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // �v���ް�2
             if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_N[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==4)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_J[1] = pEdt2_S[iKomoku-1]->Value;

              BHijyuCal(SamplePositionIdx, 2 );

    }else {
             // �v���ް� n?
             if( KD51Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                 n = pEdt4_S[iKomoku-1]->Value;

                 // �v���ް�2
                if( iKomoku==1 && KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                    KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==2)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==3)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] = pEdt3_S[iKomoku-1]->Value;
                if( iKomoku==4)
                    KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] = pEdt3_S[iKomoku-1]->Value;

                 BHijyuCal(SamplePositionIdx, n );
             }
    }




	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].SAMPLE_P != -1 &&
		      !( KD51Data[i].SOKUTEI_NB_CUR == 0 &&
				KD51Data[i].SOKUTEI_NS_CUR == 0 &&
				KD51Data[i].SOKUTEI_NH_CUR == 0 &&
				KD51Data[i].SOKUTEI_NN_CUR == 0 &&
				KD51Data[i].SOKUTEI_NJ_CUR == 0     )){

			//�S���Һ���
			KD51Data[i].UPDCHR = USER_COD ;

			// ����\���
			//KD51Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// �ڰNO
			//KD51Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//����l���ϒl�̎Z�o
			double a = 0.0;
			for(j=0; j< KD51Data[i].SOKUTEI_NB_CUR; j++ )
				a += KD51Data[i].SOKUTEI_B[j] ;
			if( KD51Data[i].SOKUTEI_NB_CUR )
				KD51Data[i].SOKUTE_AVE = a/KD51Data[i].SOKUTEI_NB_CUR ;

			// �o�^���A�o�^����
			if( IsNullSpace( KD51Data[i].ADDYMD )){
				KD51Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD51Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD51Data[i].UPDCNT = 0;

			}else{
				// �ύX���A�ύX����
				KD51Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD51Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD51Data[i].UPDCNT += 1;

				iToroku = 0;

			}

			str_c[0] = NULL ;

			//Initial Query1
			Form1->Query1->Close();
			Form1->Query1->SQL->Clear();
			if(Form1->Database1->InTransaction == false ){
				Form1->Database1->StartTransaction();
			}
			//���₢������  Update
			sprintf(str_c, " update KD51 set SOKUTEI_SU=%d ,SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KD51Data[i].SOKUTEI_NB_CUR,
								KD51Data[i].SOKUTEI_S[0],
								KD51Data[i].SOKUTEI_S[1],
								KD51Data[i].SOKUTEI_H[0],
								KD51Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1N=%6.3f , SOKUTEI_2N=%6.3f, SOKUTEI_1J=%6.3f , SOKUTEI_2J=%6.3f ,",
								KD51Data[i].SOKUTEI_N[0],
								KD51Data[i].SOKUTEI_N[1],
								KD51Data[i].SOKUTEI_J[0],
								KD51Data[i].SOKUTEI_J[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1B=%6.2f , SOKUTEI_2B=%6.2f, SOKUTE_AVE=%9.5f,",
								KD51Data[i].SOKUTEI_B[0],
								KD51Data[i].SOKUTEI_B[1],
								KD51Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//���l�ǉ� 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD51Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD51Data[i].ADDYMD.c_str(),
									KD51Data[i].ADDTIM.c_str(),
									KD51Data[i].UPDCHR,
									KD51Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD51Data[i].UPDYMD.c_str(),
									KD51Data[i].UPDTIM.c_str(),
									KD51Data[i].UPDCHR,
									KD51Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD51Data[i].KENSA_YMD.c_str(),
			//					KD51Data[i].TOLEY_NO ,
			//					KD51Data[i].SAMPLE_P );
                        // 20160630_�H��敪�ǉ�
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD51Data[i].KENSA_YMD.c_str(),
						KD51Data[i].TOLEY_NO ,
						KD51Data[i].SAMPLE_P ,
						iKojoKbn );

			str += str_c ;
			Form1->Query1->SQL->Add(str);

			//���₢�������̎��s
			try
			{
				Form1->Query1->ExecSQL();
				Form1->Database1->Commit();    // ���������ꍇ�A�ύX���R�~�b�g����
			}
			catch(EDatabaseError& e)
			{
				Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}
			catch(Exception& e)
			{
				Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			// ��̔�d����i��O�j̧�ق̍X�V
			if( KD51Data[i].SOKUTEI_NM > 2 ){
				Kd52_Update01(i) ;
			}
		} else {
			//���l�̂ݓ����Ă����ꍇ�A���l�̂ݕۑ�
			if(!(IsNullSpace( KD51Data[i].ADDYMD )) || !(IsNullSpace(KD51Data[i].MEMO))){
				// �o�^���A�o�^����
				if( IsNullSpace( KD51Data[i].ADDYMD )){
					KD51Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD51Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD51Data[i].UPDCNT = 0;

				}else{
					// �ύX���A�ύX����
					KD51Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD51Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD51Data[i].UPDCNT += 1;

					iToroku = 0;
				}


				str_c[0] = NULL ;
				//Initial Query1
				Form1->Query1->Close();
				Form1->Query1->SQL->Clear();
				if(Form1->Database1->InTransaction == false ){
					Form1->Database1->StartTransaction();
				}
				//���₢������  Update
				sprintf(str_c, " update KD51 set MEMO='%s' , ", KD51Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD51Data[i].ADDYMD.c_str(),
										KD51Data[i].ADDTIM.c_str(),
										KD51Data[i].UPDCHR,
										KD51Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD51Data[i].UPDYMD.c_str(),
										KD51Data[i].UPDTIM.c_str(),
										KD51Data[i].UPDCHR,
										KD51Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD51Data[i].KENSA_YMD.c_str(),
				//					KD51Data[i].TOLEY_NO ,
				//					KD51Data[i].SAMPLE_P );
                                // 20160630_�H��敪�ǉ�
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD51Data[i].KENSA_YMD.c_str(),
						KD51Data[i].TOLEY_NO ,
						KD51Data[i].SAMPLE_P ,
						iKojoKbn );

				str += str_c ;
				Form1->Query1->SQL->Add(str);

				//���₢�������̎��s
				try
				{
					Form1->Query1->ExecSQL();
					Form1->Database1->Commit();    // ���������ꍇ�A�ύX���R�~�b�g����
				}
				catch(EDatabaseError& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
				catch(Exception& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
			}
		}
	}

}



/***********************************************************************
*  function name : void Kd52_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   iRec     | ���Ļ�����߼޼��NO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v���ް�(>2)���̔�d����(��O�j̧�ق֏�������  KD52 *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD51Data[iRec].SOKUTEI_NM; i++ ){

         // KD52�֒ǉ����郌�R�[�h���݂��邩�ǂ����̃`�F�b�N
         iRtn = Kd52_Serch02( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // �Y�����R�[�h�����݂��Ȃ��ꍇ�ǉ��iInsert�j
         if( iRtn < 0 ) {
                Kd52_Insert01( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // �Y�����R�[�h�����݂���ꍇ�X�V�iUpdate�j
                Kd52_Update02( KD51Data[iRec].KENSA_YMD,
                          KD51Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
          }
    }
}

/***********************************************************************
*  function name : int IsNullSpace( AnsiString str)                   *
*                  +--------------------------------------+            *
*          ��  ��  | str       |  �`�F�b�N���镶����      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  0      |  NULL or Space             |            *
*                  |  �P     |  NULL or Space�ȊO�̕���   |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �����񒆂�NULL�ASpace�ȊO�̕����������Ă��邩�ǂ��� *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int IsNullSpace( AnsiString  str )
{
   char sBuf[256];
   int i, iRtn;

   iRtn = 1;

   sBuf[0] = NULL ;
   strcpy( sBuf,str.c_str());

   for( i=0; i<str.Length(); i++ ){
      if( sBuf[i] != NULL && sBuf[i] != ' ' ){
         iRtn = 0 ;
         break ;
       }
   }

   return iRtn;

}

/***********************************************************************
*  function name : int Kd52_Serch02(AnsiString sYmd, int iTlno,        *
*                                   int iSp, int iDtNo)                *
*                  +--------------------------------------+            *
*          ��  ��  | sYmd       |  �����\���             |            *
*                  | iTlno      |  �ڰNO                  |            *
*                  | iSp        |  ���Ļ�����߼޼��       |            *
*                  | iDtNo      |  �v���ް�NO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  0      |  ���R�[�h����              |            *
*                  |  ���O   |  ���R�[�h��                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL�� �C��)                              *
*  contents      : �w�肵��ں��ނ���̔�d��O̧�قɂ��邩�ǂ���������   *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd52_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;
       AnsiString strVal04;

        //�����l�̂̎擾
        strVal01 = sYmd;
        strVal02 = IntToStr(iTlno);
        strVal03 = IntToStr( iSp );
        strVal04 = IntToStr( iDtNo );

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //�₢���������s
        //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����,�ް�NO
        sBuf = "SELECT * ";
        sBuf += "FROM KD52 ";
        sBuf += "WHERE  KD52.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD52.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD52.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD52.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD52.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
        //2001.05.21 �C�� sBuf += "ORDER BY KD52.KENSA_YMD, KD52.TOLEY_NO, KD52.SAMPLE_P, KD52.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd52_Update02(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          ��  ��  | sYmd       |  �����\���             |            *
*                  | iTlno      |  �ڰNO                  |            *
*                  | iSp        |  ���Ļ�����߼޼��       |            *
*                  | iDtNo      |  �v���ް�NO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD52�֎w�肵��ں��ނ��X�V����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //���₢������  Update
    sprintf(str_c, " update KD52 set SOKUTEI_S=%6.3f ,", KD51Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.3f ,", KD51Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUHEI_N=%6.3f ,", KD51Data[iSp-1].SOKUTEI_N[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_J=%6.3f ,", KD51Data[iSp-1].SOKUTEI_J[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEI_B=%6.2f", KD51Data[iSp-1].SOKUTEI_B[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d",
                                sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );     // 20160630_�H��敪�ǉ�

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //���₢�������̎��s
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // ���������ꍇ�A�ύX���R�~�b�g����
     }
     catch(EDatabaseError& e)
     {
         Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
         Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
 }

/***********************************************************************
*  function name : void Kd52_Insert01(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          ��  ��  | sYmd       |  �����\���             |            *
*                  | iTlno      |  �ڰNO                  |            *
*                  | iSp        |  ���Ļ�����߼޼��       |            *
*                  | iDtNo      |  �v���ް�NO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD52�֎w�肵��ں��ނ�ǉ�����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd52_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //���₢������  Update
    sprintf(str_c, " insert into  KD52 ( KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEI_S, SOKUTEI_H, SOKUHEI_N, SOKUTEI_J, SOKUTEI_B, KOJOKBN)");	// 20160630_�H��敪�ǉ�

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s', %d, %d, %d, %6.3f, %6.3f, %6.3f, %6.3f, %6.2f, %d)",
                                  sYmd.c_str(), iTlno, iSp, iDtNo ,
                                  KD51Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_N[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_J[iDtNo-1],
                                  KD51Data[iSp-1].SOKUTEI_B[iDtNo-1], iKojoKbn);      // 20160630_�H��敪�ǉ�

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //���₢�������̎��s
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // ���������ꍇ�A�ύX���R�~�b�g����
     }
     catch(EDatabaseError& e)
     {
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
 }


/***********************************************************************
*  function name : void Kd53W_Create01(AnsiString sYmd, int iTlno,     *
*                                                       int iNum)      *
*                  +--------------------------------------+            *
*          ��  ��  | sYmd       |  �����\���             |            *
*                  | iTlno      |  �ڰNO                  |            *
*                  | iNum       |  ���b�g��               |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |             | ���R�[�h��             |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �������̂��߂� KD53Wܰ��e�[�u�����쐬����         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
long  Kd53W_Create01(AnsiString sYmd, int iTlno, int iNum)
{
     //�����\��N����
     Form1->StoredProc1->Params->Items[0]->AsString = sYmd;

     //�ڰNO
     Form1->StoredProc1->Params->Items[1]->AsInteger = iTlno;

     //���b�g��
     Form1->StoredProc1->Params->Items[2]->AsInteger = iNum;

     //�v���O�������s
     Form1->StoredProc1->Prepare();
     Form1->StoredProc1->ExecProc();

     //���R�[�h��
     long n  = Form1->StoredProc1->Params->Items[3]->AsInteger;

     return n;
}

/***********************************************************************
*  function name : void KD53WFormat(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���[�h����t��R����ܰ��ް��\����KD53data��������   *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD53WFormat(void)
{
   for( int i=0; i<30; i++){
       KD53WData[i].DTKSHIN = '\0';              //���Ӑ�i��

       for( int j=0; j< 50 ; j++ ){
            KD53WData[i].LOTNO[j]  = 0.0 ;       //���b�gNO
            KD53WData[i].BOTAI_MAX[j] = 0.0  ;    //��̔�d �K�i��
            KD53WData[i].BOTAI_MIN[j] = 0.0  ;    //��̔�d �K�i��
            KD53WData[i].SOKUTE_AVE[j] = 0.0;
            KD53WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD53WData[i].SOKUTEI[j][k] = 0.0;  //����l
       }

       KD53WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd53W_Search01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD53Wܰ�ð��ق��烊�[�h����t��R�����f�[�^���oKD53W*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd53W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // �������f�[�^��ǂݍ���
        for( i=0; i<30; i++ ){

             // ���肵�Ȃ��ꍇ�A�������Ȃ�
             if( KD51Data[i].SOKUTE_KBN == 0 && KD51Data[i].SAMPLE_P == -1 ) continue ;
             if( KD51Data[i].LINK ) continue ;

             //�����߼޼��NO�̕i�Ԃƃ��b�gNO�Ō���
             strVal01 = KD51Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //�₢���������s
              //�\�[�g���� ,�����\����A�g���[No
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD53W ";
	      sBuf += "WHERE  KD53W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //�H��敪�Ɋւ�炸���藚�����擾����
              //sBuf += "AND KD53W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_�H��敪�ǉ�
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD51�Ƀf�[�^������܂���");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable53W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD53WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD53WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD53WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KD53WData[i].SOKUTEI[j][k] ;

               if( KD53WData[i].SOKUTEI_NM[j] !=0 )
                   KD53WData[i].SOKUTE_AVE[j] = dAve/KD53WData[i].SOKUTEI_NM[j] ;
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable53W(int )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ܰ��ް�KD53WData���ް���ݒ�                        *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable53W(int iSp)
{

     int iLotno = KD53WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD53WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD53WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD53WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["BOTAI_MIN"].IsNull()) {
               KD53WData[iSp].BOTAI_MIN[iLotno] = 0.0;
            }else {
                KD53WData[iSp].BOTAI_MIN[iLotno] = Form1->Query1->FieldValues["BOTAI_MIN"];
            }

            if ( Form1->Query1->FieldValues["BOTAI_MAX"].IsNull()) {
               KD53WData[iSp].BOTAI_MAX[iLotno] = 0.0;
            }else {
                KD53WData[iSp].BOTAI_MAX[iLotno] = Form1->Query1->FieldValues["BOTAI_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD53WData[iSp].DTKSHIN = " ";
     }else {
            KD53WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // ����l
     int iDtNo = KD53WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD53WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD53WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD53WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD53WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD51Data(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD51Data��KD51W�փR�s�[����                         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD51Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD51Data[i].SOKUTE_KBN == 0 || KD51Data[i].SAMPLE_P == -1 ) continue ;

        // ���ĕi�Ԃ��n�߂Čv���ꍇ
        if(  KD51Data[i].LINK == 0 ){
            iLinkSp = KD51Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD51Data[i].LINK;
        }

        if( KD53WData[iLinkSp-1].LOTCNT == -1 ){

           //ۯ�NO�J���^�[
           KD53WData[iLinkSp-1].LOTCNT = 1;

           //���Ӑ�i��
           KD53WData[iLinkSp-1].DTKSHIN =  KD51Data[i].DTKSHIN;

           //���b�gNO
           KD53WData[iLinkSp-1].LOTNO[0]  = KD51Data[i].LOTNO ;

           // �K�i��
           KD53WData[iLinkSp-1].BOTAI_MIN[0] = KD51Data[i].BOTAI_MIN;
           // �K�i��
           KD53WData[iLinkSp-1].BOTAI_MAX[0] = KD51Data[i].BOTAI_MAX;

           KD53WData[iLinkSp-1].SOKUTEI_NM[0] = KD51Data[i].SOKUTEI_NB_CUR;

           if( KD51Data[i].SOKUTEI_NB_CUR == 0 ) continue ;

           //����l
           double a=0.0;
           for( k=0; k < KD51Data[i].SOKUTEI_NM; k++ ) {
                  KD53WData[iLinkSp-1].SOKUTEI[0][k] = KD51Data[i].SOKUTEI_B[k];
                  a += KD53WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //���ϒl
           if( KD51Data[i].SOKUTEI_NM != 0 )
             KD53WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD51Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // �����ް����ɶ��ĕi�Ԃ��������Ă���ꍇ
     }else{

          // �����ް��̌��ֶ���ۯ�NO���ް���ǉ�
          //ۯ�NO�J���^�[
          KD53WData[iLinkSp-1].LOTCNT += 1;

          n = KD53WData[iLinkSp-1].LOTCNT ;

          //���b�gNO
          KD53WData[iLinkSp-1].LOTNO[n-1]  = KD51Data[i].LOTNO ;

          //���[�h������ �K�i��
          KD53WData[iLinkSp-1].BOTAI_MIN[n-1] = KD51Data[i].BOTAI_MIN;

          //���[�h������ �K�i��
          KD53WData[iLinkSp-1].BOTAI_MAX[n-1] = KD51Data[i].BOTAI_MAX;

          KD53WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD51Data[i].SOKUTEI_NB_CUR;

          if( KD51Data[i].SOKUTEI_NB_CUR == 0 ) continue ;

          //����l
          double a=0.0;
          for( k=0; k < KD51Data[i].SOKUTEI_NM; k++ ) {
               KD53WData[iLinkSp-1].SOKUTEI[n-1][k] = KD51Data[i].SOKUTEI_B[k];
               a += KD53WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD53WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD51Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd53w(void)                                 *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v������������߼޼��NO���ް��𗚗��ް��֒ǉ�        *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  AddKd53W(void)
{
   int i,iLinkSp;

   //�����ް�̧�ق̃`�F�b�N

   if( KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR == 0 ) return ;

   //-------------------------------------
   // ���ĕi�Ԃ��n�߂Čv���ꍇ
   if(  KD51Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD51Data[SamplePositionIdx-1].LINK;
   }

   //�����ް����ɶ���ۯ�No��INDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //�v�������ް��̍X�V
   //���b�gNO
    KD53WData[iLinkSp-1].LOTNO[iRtn] = KD51Data[SamplePositionIdx-1].LOTNO;

   // �K�i��
    KD53WData[iLinkSp-1].BOTAI_MIN[iRtn]= KD51Data[SamplePositionIdx-1].BOTAI_MIN;

    //�K�i��
    KD53WData[iLinkSp-1].BOTAI_MAX[iRtn] = KD51Data[SamplePositionIdx-1].BOTAI_MAX;

    KD53WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR;

    //����l
    for( i=0; i < KD53WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD53WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD51Data[SamplePositionIdx-1].SOKUTEI_B[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR; i++ ){
        dAve += KD51Data[SamplePositionIdx-1].SOKUTEI_B[i];
   }

   dAve= dAve/KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR ;

   KD53WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}




/***********************************************************************
*  function name : void Kd53W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd53W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd53W_Delete01(void)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //���₢������  Update
    sprintf(str_c, " DELETE FROM KD53W");

    str = str_c ;
    str_c[0] = NULL ;

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //���₢�������̎��s
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // ���������ꍇ�A�ύX���R�~�b�g����
     }
     catch(EDatabaseError& e)
     {
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
     catch(Exception& e)
     {
       // ShowMessage(e.Message);
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
 }