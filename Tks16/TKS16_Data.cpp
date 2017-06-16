/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r16�j                    *
*  file   name   : TKS16_Data.cpp                                      *
*  create        : 1999.11.26                                          *
*  contents      : �d�x�����f�[�^�A�N�Z�X�֐�                          *
*  written by    : �� �Ԗ� �iNKK Unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Tks16.h"

AnsiString sBuf ;            // ���[�N�ϐ�

extern int Hsc_HaveSokutei;
extern int Hsd_HaveSokutei;

void KD61Format(void);
void SetTable61(void);
int IsNullSpace( AnsiString  str );
void KD63WFormat(void);
void SetTable63W(int iSp);
int  CheckLotNo(int iSp);

// �d�x�����ް�̧�ق��猟���\����A�ڰNo�𒊏o
int Kd61_Serch01(void)
{

    //�d�x�����ް�̧�ق���}�X�^�f�[�^�𒊏o
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += "DISTINCT KENSA_YMD, TOLEY_NO ";
    sBuf += "FROM KD61 ";
    sBuf += "WHERE KD61.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
    sBuf += "ORDER BY KENSA_YMD desc, TOLEY_NO";

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

    if ( Form1->Query1->RecordCount <= 0 ) {
      // ShowMessage( MSG_02 );
      return 0;
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

   return Form1->Query1->RecordCount ;
}

//�d�x�ް�̧�ق����ް��𒊏o
int Kd61_Serch02( void)
{
    int n,i, iPos;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;

    // KD61Data�\���̕ϐ��̏�����
    KD61Format();

    //�����l�̂̎擾
    strVal01 = Form1->edtymd->Text;
    // ���t(YYYY/MM/DD)����(YYYYMMDD)�֕ϊ�
    while ((iPos = strVal01.AnsiPos("/")) != 0) {
       strVal01.Delete(iPos,1);
    }
    strVal02 = Form1->edttlno->Text;

    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�\�[�g���� ,�����\����A�g���[No
    sBuf = "SELECT *  ";
    sBuf += "FROM KD61 ";
    sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
    sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
    sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
    //2001.05.21 �C�� sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P";
    sBuf += "ORDER BY SAMPLE_P";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();

    if (Form1->Query1->Eof) { // �f�[�^����
       return -1;
    } else {
       while (!Form1->Query1->Eof ) {
          SetTable61();
          Form1->Query1->Next();
       }
    }

    //Link NO
    for ( i=0; i<29; i++ ){
        if ((KD61Data[i].SOKUTE_KBN1 || KD61Data[i].SOKUTE_KBN2) && KD61Data[i].SAMPLE_P != -1 ) {
           if (KD61Data[i].LINK == 0 ){
              for (int j=i+1; j<30; j++ ){
                  if (KD61Data[i].DTKSHIN == KD61Data[j].DTKSHIN)
                     KD61Data[j].LINK = KD61Data[i].SAMPLE_P;
              }
           }
        }
    }

    //�v�����m���Q�̏ꍇ �d�x����i��O�j̧�ق�ǂݍ���
    for ( i = 0; i<30; i++ ) {
        if ((KD61Data[i].HSC_SK_NUM > 2 && KD61Data[i].SOKUTE_KBN1 >= 1) ||
           (KD61Data[i].HSD_SK_NUM > 2 && KD61Data[i].SOKUTE_KBN2 >= 1)) {

           Form1->Query1->Close();
           Form1->Query1->SQL->Clear();

           strVal03 = IntToStr( KD61Data[i].SAMPLE_P );

           //�₢���������s
           //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����
           sBuf = "SELECT ";
	   sBuf += "HSC_A, HSC_S, HSD_A, HSD_S, SOKUTEI_NO ";
	   sBuf += "FROM KD62 ";
           sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	   sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
	   sBuf += "AND SAMPLE_P = '" + strVal03 + "' ";
           sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	   //2001.05.21 �C�� sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
           sBuf += "ORDER BY SOKUTEI_NO";

           Form1->Query1->SQL->Add(sBuf);
           Form1->Query1->Open();

           if (Form1->Query1->Eof) { // KD62�Ƀf�[�^������܂���
               continue;
           } else {
               while( !Form1->Query1->Eof ) {
                  if (Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                     n = 3;
                  }else {
                     n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                  }

                  if ( Form1->Query1->FieldValues["HSC_A"].IsNull()) {
                     KD61Data[i].HSC_A_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSC_A_CH[n-1] =  Form1->Query1->FieldValues["HSC_A"];
                  }

                  if ( Form1->Query1->FieldValues["HSC_S"].IsNull()) {
                     KD61Data[i].HSC_S_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSC_S_CH[n-1] =  Form1->Query1->FieldValues["HSC_S"];
                  }

                  if ( Form1->Query1->FieldValues["HSD_A"].IsNull()) {
                     KD61Data[i].HSD_A_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSD_A_CH[n-1] =  Form1->Query1->FieldValues["HSD_A"];
                  }

                  if ( Form1->Query1->FieldValues["HSD_S"].IsNull()) {
                     KD61Data[i].HSD_S_CH[n-1] = 0.0;
                  } else {
                     KD61Data[i].HSD_S_CH[n-1] =  Form1->Query1->FieldValues["HSD_S"];
                  }

                  Form1->Query1->Next();
               }
           }
        }

    }
    return 0;
}

// �d�x�f�[�^�\����KD61Data��������
// update  2002.11.07 ���l�ް��ǉ� E.Takase
void KD61Format(void)
{
   for( int i=0; i<30; i++){
      KD61Data[i].KENSA_YMD =  '\0';   //�����\���
      KD61Data[i].TOLEY_NO = 0 ;       //�ڰNO
      KD61Data[i].SAMPLE_P = -1 ;      //������߼޼��NO
      KD61Data[i].SOKUTE_KBN1 = 0;     //����敪 Hsc
      KD61Data[i].SOKUTE_KBN2 = 0;     //����敪 Hsd
      KD61Data[i].DTKSCOD = '\0';      //���Ӑ�R�[�h
      KD61Data[i].DTKSHIN = '\0';      //���Ӑ�i��
      KD61Data[i].LOTNO = '\0';        //���b�gNO
      KD61Data[i].HINBAN = '\0';       //���Еi��
      KD61Data[i].ZISCOD = '\0';       //�ގ��R�[�h
      KD61Data[i].ZISNAM = '\0';       //�ގ���

      // HsC
      KD61Data[i].HSC_A_MIN = 0.0;     //HsC ���� �K�i��
      KD61Data[i].HSC_A_MAX = 0.0;     //HsC ���� �K�i��
      KD61Data[i].HSC_S_MIN = 0.0;     //HsC ���� �K�i��
      KD61Data[i].HSC_S_MAX = 0.0;     //HsC ���� �K�i��
      KD61Data[i].HSC_SK_NUM = 0;      //HsC ���� ���|�w����
      KD61Data[i].HSC_SK_SU = 0;       //Hsc ���� ��
      KD61Data[i].HSC_A_AVE = 0.0;     //HsC ���� ���蕽�ϒl
      KD61Data[i].HSC_S_AVE = 0.0;     //HsC ���� ���蕽�ϒl
      memset(KD61Data[i].HSC_A_CH,(int)NULL, sizeof(int) * 100); ; //Hsc ���ʑ���l
      memset(KD61Data[i].HSC_S_CH,(int)NULL, sizeof(int) * 100); ; //Hsc ���ʑ���l

      // HsD
      KD61Data[i].HSD_A_MIN = 0.0;     //HsD ���� �K�i��
      KD61Data[i].HSD_A_MAX = 0.0;     //HsD ���� �K�i��
      KD61Data[i].HSD_S_MIN = 0.0;     //HsD ���� �K�i��
      KD61Data[i].HSD_S_MAX = 0.0;     //HsD ���� �K�i��
      KD61Data[i].HSD_SK_NUM = 0;      //HsD ���� ���|�w����
      KD61Data[i].HSD_SK_SU = 0;       //HsD ���� ��
      KD61Data[i].HSD_A_AVE = 0.0;     //HsD ���� ���蕽�ϒl
      KD61Data[i].HSD_S_AVE = 0.0;     //HsD ���� ���蕽�ϒl
      memset(KD61Data[i].HSC_A_CH,(int)NULL, sizeof(double) * 100); ; //Hsc ���ʑ���l
      memset(KD61Data[i].HSC_S_CH,(int)NULL, sizeof(double) * 100); ; //Hsc ���ʑ���l

      KD61Data[i].ADDYMD = '\0';      //�o�^��
      KD61Data[i].ADDTIM = '\0';      //�o�^����
      KD61Data[i].UPDYMD = '\0';      //�ύX��
      KD61Data[i].UPDTIM = '\0';      //�ύX����
      KD61Data[i].UPDCHR = 0;      //�X�V��
      KD61Data[i].UPDCNT = 0;      //�X�V��

      KD61Data[i].LINK = 0;
      KD61Data[i].HSC_SK_NUM_CUR = 0;
      KD61Data[i].HSD_SK_NUM_CUR = 0;
      KD61Data[i].MEMO = '\0';         //���l 2002/11/07 E.Takase
   }
}

// KD61Data�\���̂��ް���ݒ�
// update  2002.11.07 ���l�ް��ǉ� E.Takase
void SetTable61()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

     if (iRec <= 0)
        return;

     KD61Data[iRec-1].SAMPLE_P  = iRec  ;

     iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD61Data[iRec].KENSA_YMD = " ";
     } else {
          KD61Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD61Data[iRec].TOLEY_NO = 0;
     } else {
          KD61Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN1"].IsNull()) {
          KD61Data[iRec].SOKUTE_KBN1 = 0;
     } else
          KD61Data[iRec].SOKUTE_KBN1 =  Form1->Query1->FieldValues["SOKUTE_KBN1"];

     if ( Form1->Query1->FieldValues["SOKUTE_KBN2"].IsNull()) {
          KD61Data[iRec].SOKUTE_KBN2 = 0;
     } else
          KD61Data[iRec].SOKUTE_KBN2 =  Form1->Query1->FieldValues["SOKUTE_KBN2"];

     if( Hsc_HaveSokutei == 0 && KD61Data[iRec].SOKUTE_KBN1 >= 1) {
         Hsc_HaveSokutei = 1;
     }

     if( Hsd_HaveSokutei == 0 && KD61Data[iRec].SOKUTE_KBN2 >= 1) {
         Hsd_HaveSokutei = 1;
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD61Data[iRec].DTKSCOD = " ";
     }else {
          KD61Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD61Data[iRec].DTKSHIN = " ";
     }else {
          KD61Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD61Data[iRec].LOTNO = " ";
     }else {
          KD61Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD61Data[iRec].HINBAN = " ";
     }else {
          KD61Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD61Data[iRec].ZISCOD = " ";
     }else {
          KD61Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD61Data[iRec].ZISNAM = " ";
     }else {
          KD61Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_MIN"].IsNull()) {
          KD61Data[iRec].HSC_A_MIN = 0;
     }else {
          KD61Data[iRec].HSC_A_MIN =  Form1->Query1->FieldValues["HSC_A_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_MAX"].IsNull()) {
          KD61Data[iRec].HSC_A_MAX = 0;
     }else {
          KD61Data[iRec].HSC_A_MAX =  Form1->Query1->FieldValues["HSC_A_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_MIN"].IsNull()) {
          KD61Data[iRec].HSC_S_MIN = 0;
     }else {
          KD61Data[iRec].HSC_S_MIN =  Form1->Query1->FieldValues["HSC_S_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_MAX"].IsNull()) {
          KD61Data[iRec].HSC_S_MAX = 0;
     }else {
          KD61Data[iRec].HSC_S_MAX =  Form1->Query1->FieldValues["HSC_S_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_1"].IsNull()) {
          KD61Data[iRec].HSC_A_CH[0] = 0;
     }else {
          KD61Data[iRec].HSC_A_CH[0] =  Form1->Query1->FieldValues["HSC_A_1"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_2"].IsNull()) {
          KD61Data[iRec].HSC_A_CH[1] = 0;
     }else {
          KD61Data[iRec].HSC_A_CH[1] =  Form1->Query1->FieldValues["HSC_A_2"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_1"].IsNull()) {
          KD61Data[iRec].HSC_S_CH[0] = 0;
     }else {
          KD61Data[iRec].HSC_S_CH[0] =  Form1->Query1->FieldValues["HSC_S_1"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_2"].IsNull()) {
          KD61Data[iRec].HSC_S_CH[1] = 0;
     }else {
          KD61Data[iRec].HSC_S_CH[1] =  Form1->Query1->FieldValues["HSC_S_2"];
     }

     if ( Form1->Query1->FieldValues["HSC_SK_NUM"].IsNull()) {
          KD61Data[iRec].HSC_SK_NUM = 0;
     }else {
          KD61Data[iRec].HSC_SK_NUM =  Form1->Query1->FieldValues["HSC_SK_NUM"];
     }

     if ( Form1->Query1->FieldValues["HSC_SK_SU"].IsNull()) {
          KD61Data[iRec].HSC_SK_SU = 0;
     }else {
          KD61Data[iRec].HSC_SK_SU =  Form1->Query1->FieldValues["HSC_SK_SU"];
     }

     if ( Form1->Query1->FieldValues["HSC_A_AVE"].IsNull()) {
          KD61Data[iRec].HSC_A_AVE = 0.0;
     }else {
          KD61Data[iRec].HSC_A_AVE =  Form1->Query1->FieldValues["HSC_A_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSC_S_AVE"].IsNull()) {
          KD61Data[iRec].HSC_S_AVE = 0.0;
     }else {
          KD61Data[iRec].HSC_S_AVE =  Form1->Query1->FieldValues["HSC_S_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_MIN"].IsNull()) {
          KD61Data[iRec].HSD_A_MIN = 0.0;
     }else {
          KD61Data[iRec].HSD_A_MIN =  Form1->Query1->FieldValues["HSD_A_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_MAX"].IsNull()) {
          KD61Data[iRec].HSD_A_MAX = 0.0;
     }else {
          KD61Data[iRec].HSD_A_MAX =  Form1->Query1->FieldValues["HSD_A_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_MIN"].IsNull()) {
          KD61Data[iRec].HSD_S_MIN = 0.0;
     }else {
          KD61Data[iRec].HSD_S_MIN =  Form1->Query1->FieldValues["HSD_S_MIN"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_MAX"].IsNull()) {
          KD61Data[iRec].HSD_S_MAX = 0.0;
     }else {
          KD61Data[iRec].HSD_S_MAX =  Form1->Query1->FieldValues["HSD_S_MAX"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_1"].IsNull()) {
          KD61Data[iRec].HSD_A_CH[0] = 0.0;
     }else {
          KD61Data[iRec].HSD_A_CH[0] =  Form1->Query1->FieldValues["HSD_A_1"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_2"].IsNull()) {
          KD61Data[iRec].HSD_A_CH[1] = 0.0;
     }else {
          KD61Data[iRec].HSD_A_CH[1] =  Form1->Query1->FieldValues["HSD_A_2"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_1"].IsNull()) {
          KD61Data[iRec].HSD_S_CH[0] = 0.0;
     }else {
          KD61Data[iRec].HSD_S_CH[0] =  Form1->Query1->FieldValues["HSD_S_1"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_2"].IsNull()) {
          KD61Data[iRec].HSD_S_CH[1] = 0.0;
     }else {
          KD61Data[iRec].HSD_S_CH[1] =  Form1->Query1->FieldValues["HSD_S_2"];
     }

     if ( Form1->Query1->FieldValues["HSD_SK_NUM"].IsNull()) {
          KD61Data[iRec].HSD_SK_NUM = 0;
     }else {
          KD61Data[iRec].HSD_SK_NUM =  Form1->Query1->FieldValues["HSD_SK_NUM"];
     }

     if ( Form1->Query1->FieldValues["HSD_SK_SU"].IsNull()) {
          KD61Data[iRec].HSD_SK_SU = 0;
     }else {
          KD61Data[iRec].HSD_SK_SU =  Form1->Query1->FieldValues["HSD_SK_SU"];
     }

     if ( Form1->Query1->FieldValues["HSD_A_AVE"].IsNull()) {
          KD61Data[iRec].HSD_A_AVE = 0.0;
     }else {
          KD61Data[iRec].HSD_A_AVE =  Form1->Query1->FieldValues["HSD_A_AVE"];
     }

     if ( Form1->Query1->FieldValues["HSD_S_AVE"].IsNull()) {
          KD61Data[iRec].HSD_S_AVE = 0.0;
     }else {
          KD61Data[iRec].HSD_S_AVE =  Form1->Query1->FieldValues["HSD_S_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD61Data[iRec].ADDYMD = " ";
          KD61Data[iRec].HSC_SK_NUM_CUR = 0;
          KD61Data[iRec].HSD_SK_NUM_CUR = 0;
          KD61Data[iRec].HSC_SK_SU = 0;
          KD61Data[iRec].HSD_SK_SU = 0;
     }else {
          KD61Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD61Data[iRec].ADDYMD )){
             KD61Data[iRec].HSC_SK_NUM_CUR = 0;
             KD61Data[iRec].HSD_SK_NUM_CUR = 0;
             KD61Data[iRec].HSC_SK_SU = 0;
             KD61Data[iRec].HSD_SK_SU = 0;
          }else{
             switch (KD61Data[iRec].SOKUTE_KBN1) {
             case 0:
                  KD61Data[iRec].HSC_SK_NUM_CUR = 0;
                  break;
             case 1:
             case 2:
                  //KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM;
                  KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_SU;
                  break;
             case 3:
                  KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM + KD61Data[iRec].HSC_SK_SU ;
                  //KD61Data[iRec].HSC_SK_NUM_CUR = KD61Data[iRec].HSC_SK_NUM * 2;
                  break;
             }
             switch (KD61Data[iRec].SOKUTE_KBN2) {
             case 0:
                  KD61Data[iRec].HSD_SK_NUM_CUR = 0;
                  break;
             case 1:
             case 2:
                  //KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM;
                  KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_SU;
                  break;
             case 3:
                  //KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM * 2;
                  KD61Data[iRec].HSD_SK_NUM_CUR = KD61Data[iRec].HSD_SK_NUM + KD61Data[iRec].HSD_SK_SU ;
                  break;
             }
          }
     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD61Data[iRec].ADDTIM = " ";
     }else {
          KD61Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD61Data[iRec].UPDYMD = " ";
     }else {
          KD61Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD61Data[iRec].UPDCHR = 0;
     }else {
          KD61Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD61Data[iRec].UPDCNT = 0;
     }else {
          KD61Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //���l 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD61Data[iRec].MEMO =  " ";
     }else {
          KD61Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

 }

// �����񒆂�NULL�ASpace�ȊO�̕����������Ă��邩�ǂ���
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

// �d�x�ް����d�x�ް�̧�ق֏�������  KD61
int Kd61_Update01(void)
{
    int i,j,n,iToroku, rtn;
    AnsiString str;
    char str_c[256];
    double a,s;
    int ErrFlag = 0;

    // �eSample Loop
    for ( i=0; i<30; i++ ){

        //if (KD61Data[i].SAMPLE_P == -1)
        //   continue;

        iToroku = 1;

        if ((KD61Data[i].SOKUTE_KBN1 >= 1 || KD61Data[i].SOKUTE_KBN2 >= 1) &&
           KD61Data[i].SAMPLE_P != -1  && (KD61Data[i].HSC_SK_NUM_CUR > 0 ||
           KD61Data[i].HSD_SK_NUM_CUR > 0)){

           //�S���Һ���
           KD61Data[i].UPDCHR = USER_COD ;

           //HSc:����l���ϒl�̎Z�o
           a = 0.0;
           s = 0.0;
           if (KD61Data[i].SOKUTE_KBN1 >= 1 && KD61Data[i].HSC_SK_NUM_CUR > 0) {

              switch(KD61Data[i].SOKUTE_KBN1) {
              case 1:
              case 2:
                   KD61Data[i].HSC_SK_SU =  KD61Data[i].HSC_SK_NUM_CUR;
                   break;
              case 3:
                   if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM)
                      KD61Data[i].HSC_SK_SU = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                   else
                      KD61Data[i].HSC_SK_SU = KD61Data[i].HSC_SK_NUM_CUR;
                   break;
              }

              // ���ʃf�[�^
              if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                 for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR; j++ ) {
                     if (j < KD61Data[i].HSC_SK_NUM)
                        a += KD61Data[i].HSC_A_CH[j];
                 }
              }

              // ���ʃf�[�^
              if (KD61Data[i].SOKUTE_KBN1 == 2) {
                 for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR; j++ )
                     if (j < KD61Data[i].HSC_SK_NUM)
                        s += KD61Data[i].HSC_S_CH[j];
              } else {
                 if (KD61Data[i].SOKUTE_KBN1 == 3) {
                    for (j=0; j< KD61Data[i].HSC_SK_NUM_CUR-KD61Data[i].HSC_SK_NUM; j++ )
                        s += KD61Data[i].HSC_S_CH[j];
                 }
              }

             if (KD61Data[i].HSC_SK_NUM ) {
                KD61Data[i].HSC_A_AVE = a/KD61Data[i].HSC_SK_NUM;
                KD61Data[i].HSC_S_AVE = s/KD61Data[i].HSC_SK_NUM;
             }
           } else {
             KD61Data[i].HSC_A_AVE = 0.0;
             KD61Data[i].HSC_S_AVE = 0.0;
           }

           //HSD:����l���ϒl�̎Z�o
           a = 0.0;
           s = 0.0;
           if (KD61Data[i].SOKUTE_KBN2 >= 1 && KD61Data[i].HSD_SK_NUM_CUR > 0) {

              switch(KD61Data[i].SOKUTE_KBN2) {
              case 1:
              case 2:
                   KD61Data[i].HSD_SK_SU =  KD61Data[i].HSD_SK_NUM_CUR;
                   break;
              case 3:
                   if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM)
                      KD61Data[i].HSD_SK_SU = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                   else
                      KD61Data[i].HSD_SK_SU = KD61Data[i].HSD_SK_NUM_CUR;
                   break;
              }

              // ���ʃf�[�^
              if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                 for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR; j++ ) {
                     if (j <= KD61Data[i].HSD_SK_NUM)
                        a += KD61Data[i].HSD_A_CH[j];
                 }
              }

              // ���ʃf�[�^
              if (KD61Data[i].SOKUTE_KBN2 == 2)  {
                 for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR; j++ )
                     if (j < KD61Data[i].HSD_SK_NUM)
                        s += KD61Data[i].HSD_S_CH[j];
              } else {
                 if (KD61Data[i].SOKUTE_KBN2 == 3) {
                    for (j=0; j< KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM; j++ )
                        s += KD61Data[i].HSD_S_CH[j];
                 }
              }

             if (KD61Data[i].HSD_SK_NUM ) {
                KD61Data[i].HSD_A_AVE = a/KD61Data[i].HSD_SK_NUM;
                KD61Data[i].HSD_S_AVE = s/KD61Data[i].HSD_SK_NUM;
             }
           } else {
             KD61Data[i].HSD_A_AVE = 0.0;
             KD61Data[i].HSD_S_AVE = 0.0;
           }

	        // �o�^���A�o�^����
	        if (IsNullSpace( KD61Data[i].ADDYMD )){
	           KD61Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
	           KD61Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

	           //�X�V��
	           KD61Data[i].UPDCNT = 0;
	        } else {
	           // �ύX���A�ύX����
	           KD61Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
	           KD61Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

	           //�X�V��
	           KD61Data[i].UPDCNT += 1;

	           iToroku = 0;
	        }

	        str_c[0] = NULL ;

	        //Initial Query1
	        Form1->Query1->Close();
	        Form1->Query1->SQL->Clear();
	        if ( Form1->Database1->InTransaction == false ){
	           Form1->Database1->StartTransaction();
	        }

	        //���₢������  Update
	        sprintf(str_c, " update KD61 set HSC_A_1=%2d, HSC_S_1=%2d, HSC_A_2=%2d, HSC_S_2=%2d, ",
	                           KD61Data[i].HSC_A_CH[0], KD61Data[i].HSC_S_CH[0],
	                           KD61Data[i].HSC_A_CH[1], KD61Data[i].HSC_S_CH[1]);
	        str = str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSC_A_AVE=%9.7f, HSC_S_AVE=%9.7f, HSC_SK_SU=%d, ",
	                           KD61Data[i].HSC_A_AVE,
	                           KD61Data[i].HSC_S_AVE,
	                           KD61Data[i].HSC_SK_SU);
	        str += str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSD_A_1=%3.1f, HSD_S_1=%3.1f, HSD_A_2=%3.1f, HSD_S_2=%3.1f,",
	                           KD61Data[i].HSD_A_CH[0], KD61Data[i].HSD_S_CH[0],
	                           KD61Data[i].HSD_A_CH[1], KD61Data[i].HSD_S_CH[1]);
	        str += str_c ;
	        str_c[0] = NULL ;

	        sprintf(str_c, " HSD_A_AVE=%9.7f, HSD_S_AVE=%9.7f, HSD_SK_SU=%d, ",
	                           KD61Data[i].HSD_A_AVE,
	                           KD61Data[i].HSD_S_AVE,
	                           KD61Data[i].HSD_SK_SU);
	        str += str_c ;
	        str_c[0] = NULL ;

	        //���l�ǉ� 2002/11/07 E.Takase
	        sprintf(str_c, " MEMO='%s' ,",
	                          KD61Data[i].MEMO);
	        str += str_c ;
	        str_c[0] = NULL ;

	        if (iToroku ){
	           wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
	                           KD61Data[i].ADDYMD.c_str(),
	                           KD61Data[i].ADDTIM.c_str(),
	                           KD61Data[i].UPDCHR,
	                           KD61Data[i].UPDCNT );
	        } else{
	           wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
	                           KD61Data[i].UPDYMD.c_str(),
	                           KD61Data[i].UPDTIM.c_str(),
	                           KD61Data[i].UPDCHR,
	                           KD61Data[i].UPDCNT );
	        }
	        str += str_c ;
	        str_c[0] = NULL ;

	        //wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
	        //                        KD61Data[i].KENSA_YMD.c_str(),
	        //                        KD61Data[i].TOLEY_NO ,
	        //                        KD61Data[i].SAMPLE_P );
                // 20160630_�H��敪�ǉ�
		wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
					KD61Data[i].KENSA_YMD.c_str(),
					KD61Data[i].TOLEY_NO ,
					KD61Data[i].SAMPLE_P ,
					iKojoKbn );

	        str += str_c ;
	        Form1->Query1->SQL->Add(str);

	        //���₢�������̎��s
	        try
	        {
	            Form1->Query1->ExecSQL();
	            Form1->Database1->Commit(); // ���������ꍇ�C�ύX���R�~�b�g����;
	        }
	        catch(EDatabaseError& e)
	        {
	           // ShowMessage(e.Message);
	           Form1->StatBarClear( e.Message )  ;
	        }
	        catch(Exception& e)
	        {
	           Form1->Database1->Rollback(); // ���s�����ꍇ�C�ύX��������
	           // ShowMessage(e.Message);
	           Form1->StatBarClear( e.Message )  ;
	           ErrFlag = 1;
	        }

	        //�d�x����i��O�j̧�ق̍X�V
	        if( KD61Data[i].HSC_SK_NUM > 2 || KD61Data[i].HSD_SK_NUM > 2){
	           rtn = Kd62_Update01(i) ;
	           if (rtn <= 0)
	              ErrFlag = 1;
	        }
        } else {
			//���l�̂ݓ����Ă����ꍇ�A���l�̂ݕۑ�
			if(!(IsNullSpace( KD61Data[i].ADDYMD )) || !(IsNullSpace(KD61Data[i].MEMO))){
				// �o�^���A�o�^����
				if( IsNullSpace( KD61Data[i].ADDYMD )){
					KD61Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD61Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD61Data[i].UPDCNT = 0;

				}else{
					// �ύX���A�ύX����
					KD61Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD61Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD61Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD61 set MEMO='%s' , ", KD61Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD61Data[i].ADDYMD.c_str(),
										KD61Data[i].ADDTIM.c_str(),
										KD61Data[i].UPDCHR,
										KD61Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD61Data[i].UPDYMD.c_str(),
										KD61Data[i].UPDTIM.c_str(),
										KD61Data[i].UPDCHR,
										KD61Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD61Data[i].KENSA_YMD.c_str(),
				//					KD61Data[i].TOLEY_NO ,
				//					KD61Data[i].SAMPLE_P );
                                // 20160630_�H��敪�ǉ�
		                wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
                                                KD61Data[i].KENSA_YMD.c_str(),
					        KD61Data[i].TOLEY_NO ,
					        KD61Data[i].SAMPLE_P ,
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
					Form1->StatBarClear( e.Message )  ;
					ErrFlag = 1;
				}
				catch(Exception& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
					Form1->StatBarClear( e.Message )  ;
					ErrFlag = 1;
				}
			}
        }

   }

   if (ErrFlag == 0)
      return 1; // OK
   else
      return 0;
}

// �v���ް����d�x(��O�j̧�ق֏������� KD62
int Kd62_Update01( int iRec)
{

    int i, iRtn;
    int MaxNum;
    int ErrFlag = 0;

    // �ő呪��f�[�^��T���iHSC��HSD�̊ԁj
    MaxNum = 0;
    if (KD61Data[iRec].SOKUTE_KBN1 >= 1)
       MaxNum = KD61Data[iRec].HSC_SK_NUM;

    if (KD61Data[iRec].SOKUTE_KBN2 >= 1)
       if (MaxNum < KD61Data[iRec].HSD_SK_NUM)
          MaxNum = KD61Data[iRec].HSD_SK_NUM;

    if (MaxNum == 0)
       return 1;

    for ( i=2; i < MaxNum; i++ ){
        // KD62�֒ǉ����郌�R�[�h���݂��邩�ǂ����̃`�F�b�N
        iRtn = Kd62_Serch02( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

        Form1->Database1->StartTransaction();

        // �Y�����R�[�h�����݂��Ȃ��ꍇ�ǉ��iInsert�j
        if (iRtn <= 0 ) {
           iRtn = Kd62_Insert01( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
           if (iRtn <= 0)
              ErrFlag = 1;

        } else{   // �Y�����R�[�h�����݂���ꍇ�X�V�iUpdate�j
           Kd62_Update02( KD61Data[iRec].KENSA_YMD,
                          KD61Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
           if (iRtn <= 0)
              ErrFlag = 1;
        }
    }

    if (ErrFlag == 0)
       return 1;
    else
       return 0;
}

// �w�肵��ں�Ă��d�x��O̧�قɂ��邩�ǂ���
// sYmd: �����\��N����
// iTlno: �g���[No
// iSp:   Sample No
// iDtNo: ����m��
int  Kd62_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
     sBuf += "FROM KD62 ";
     sBuf += "WHERE KENSA_YMD = '" + strVal01 + "' ";
     sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
     sBuf += "AND SAMPLE_P = '" + strVal03 + "' ";
     sBuf += "AND SOKUTEI_NO = '" + strVal04 + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_�H��敪�ǉ�
     //2001.05.21 �C�� sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";

     Form1->Query1->SQL->Add(sBuf);
     Form1->Query1->Open();

     if ( Form1->Query1->Eof  )
        return 0 ;

    return  1;
}

// KD62�֎w�肵��ں��ނ��X�V����
// sYmd: �����\��N����
// iTlno: �g���[No
// iSp:   Sample No
// iDtNo: ����m��
int Kd62_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //���₢������  Update
    sprintf(str_c, " update KD62 set HSC_A=%2d, HSC_S=%2d, HSD_A=%3.1f, HSD_S=%3.1f ",
                    KD61Data[iSp-1].HSC_A_CH[iDtNo-1], KD61Data[iSp-1].HSC_S_CH[iDtNo-1],
                    KD61Data[iSp-1].HSD_A_CH[iDtNo-1], KD61Data[iSp-1].HSD_S_CH[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
                     sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );     // 20160630_�H��敪�ǉ�

    str += str_c ;
    Form1->Query1->SQL->Add(str);

    //���₢�������̎��s
    try
    {
       Form1->Query1->ExecSQL();
       Form1->Database1->Commit(); // ���������ꍇ�C�ύX���R�~�b�g����;
    }
    catch(EDatabaseError& e)
    {
       Form1->Database1->Rollback(); // ���s�����ꍇ�C�ύX��������
       // ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
    }
    catch(Exception& e)
    {
       Form1->Database1->Rollback(); // ���s�����ꍇ�C�ύX��������
       ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
    }

    if (ErrFlag == 1)
       return 0;
    else
       return 0;
}

// KD62�֎w�肵��ں��ނ�ǉ�����
int Kd62_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;

    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //���₢������  Update
    sprintf(str_c, " insert into KD62(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, HSC_A, HSC_S, HSD_A, HSD_S, KOJOKBN)");    // 20160630_�H��敪�ǉ�

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%d,%d,%.1f,%.1f,%d)",
            sYmd.c_str(), iTlno, iSp, iDtNo , KD61Data[iSp-1].HSC_A_CH[iDtNo-1],
            KD61Data[iSp-1].HSC_S_CH[iDtNo-1], KD61Data[iSp-1].HSD_A_CH[iDtNo-1],
            KD61Data[iSp-1].HSD_S_CH[iDtNo-1], iKojoKbn);      // 20160630_�H��敪�ǉ�

    str += str_c ;
    Form1->Query1->SQL->Add(str);

    //���₢�������̎��s
    try
    {
       Form1->Query1->ExecSQL();
       Form1->Database1->Commit(); // ���������ꍇ�C�ύX���R�~�b�g����;
    }
    catch(EDatabaseError& e)
    {
       //  ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       Form1->Database1->Rollback(); // ���s�����ꍇ�C�ύX��������
       ErrFlag = 1;
    }
    catch(Exception& e)
    {
       //  ShowMessage(e.Message);
       Form1->StatBarClear( e.Message )  ;
       Form1->Database1->Rollback(); // ���s�����ꍇ�C�ύX��������
       ErrFlag = 1;
    }

    if (ErrFlag == 0)
       return 1;
    else
       return 0;
}

// �������̂��߂� KD63Wܰ��e�[�u�����쐬����
long  Kd63W_Create01(AnsiString sYmd, int iTlno, int iNum)
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

// KD63Wܰ�ð��ق��烊�[�h�������v�������f�[�^���oKD63W
int Kd63W_Serch01(void)
{
    int i,j, j1;
    AnsiString strVal01;
    double dAve =0.0;

    // KD63Data�\���̕ϐ��̏�����
    KD63WFormat();

    // �������f�[�^��ǂݍ���
    for (i=0; i<30; i++ ){
       // ���肵�Ȃ��ꍇ�A�������Ȃ�
       if (KD61Data[i].SAMPLE_P == -1 ) continue ;

       if (KD61Data[i].SOKUTE_KBN1 == 0 && KD61Data[i].SOKUTE_KBN2 == 0) continue;

       if (KD61Data[i].LINK ) continue ;

       //�����߼޼��NO�̕i�Ԃƃ��b�gNO�Ō���
       strVal01 = KD61Data[i].DTKSHIN;

       Form1->Query1->Close();
       Form1->Query1->SQL->Clear();

       //�₢���������s
       //�\�[�g���� ,�����\����A�g���[No
       sBuf = "SELECT *  ";
       sBuf += "FROM KD63W ";
       sBuf += "WHERE  DTKSHIN = '" + strVal01 + "' ";
       //20161128 Y.Onishi
       //�H��敪�Ɋւ�炸���藚�����擾����
       //sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_�H��敪�ǉ�
       sBuf += "ORDER BY ROWNO desc" ;

       Form1->Query1->SQL->Add(sBuf);
       Form1->Query1->Open();

       if (Form1->Query1->RecordCount <= 0 ) {
          // ShowMessage("KD01�Ƀf�[�^������܂���");
          //return -1;
          continue ;
       } else {
          Form1->Query1->First();
          while ( !Form1->Query1->Eof ) {
                SetTable63W(i);
                Form1->Query1->Next();
          }

          KD63WData[i].LOTCNT +=1  ;
       }

       for (j=0; j < KD63WData[i].LOTCNT; j++ ){
           // HSC
           for (j1 = 0; j1 < 2; j1++) {   // ���ʁA����
               dAve =0.0;
               if (KD63WData[i].HSC_SOKUTEI_NM[j1][j] > 0) {
                  for (int k=0; k < KD63WData[i].HSC_SOKUTEI_NM[j1][j]; k++)
                      dAve += KD63WData[i].HSC_CH[j1][j][k] ;

                  if (KD63WData[i].HSC_SOKUTEI_NM[j1][j] !=0 )
                     KD63WData[i].HSC_AVE[j1][j] = dAve/KD63WData[i].HSC_SOKUTEI_NM[j1][j] ;
               } else
                  KD63WData[i].HSC_AVE[j1][j] = 0.0;
           }
           // HSC
           for (j1 = 0; j1 < 2; j1++) {   // ���ʁA����
               dAve =0.0;
               if (KD63WData[i].HSD_SOKUTEI_NM[j1][j] > 0) {
                  for (int k=0; k < KD63WData[i].HSD_SOKUTEI_NM[j1][j]; k++)
                      dAve += KD63WData[i].HSD_CH[j1][j][k] ;

                  if (KD63WData[i].HSD_SOKUTEI_NM[j1][j] !=0 )
                     KD63WData[i].HSD_AVE[j1][j] = dAve/KD63WData[i].HSD_SOKUTEI_NM[j1][j] ;
               } else
                  KD63WData[i].HSD_AVE[j1][j] = 0.0;
           }
       }
    }

    return 0;
}

// �d�x�v������ܰ��ް��\����KD63data��������
void KD63WFormat(void)
{
   for( int i=0; i<30; i++){
       KD63WData[i].DTKSHIN = '\0';     //���Ӑ�i��
       KD63WData[i].LOTCNT = -1;

       for (int j=0; j< 50 ; j++ ){
           KD63WData[i].LOTNO[j]  = "\0";          //���b�gNO
           // HSC
           for (int j1 = 0; j1 < 2; j1++) {
               KD63WData[i].HSC_MIN[j1][j] = 0  ;  //�K�i��
               KD63WData[i].HSC_MAX[j1][j] = 0;    //�K�i��
               KD63WData[i].HSC_AVE[j1][j] = 0.0;
               KD63WData[i].HSC_SOKUTEI_NM[j1][j] = 0;
               for ( int k=0; k<100; k++ )
                   KD63WData[i].HSC_CH[j1][j][k] = 0.0;  //����l
           }

           // HSD
           for (int j1 = 0; j1 < 2; j1++) {
               KD63WData[i].HSD_MIN[j1][j] = 0  ;  //�K�i��
               KD63WData[i].HSD_MAX[j1][j] = 0;    //�K�i��
               KD63WData[i].HSD_AVE[j1][j] = 0.0;
               KD63WData[i].HSD_SOKUTEI_NM[j1][j] = 0;
               for ( int k=0; k<100; k++ )
                   KD63WData[i].HSD_CH[j1][j][k] = 0.0;  //����l
           }
       }
    }
}

// ܰ��ް�KD63WData���ް���ݒ�
void SetTable63W(int iSp)
{

     int iDtNo;

     int iLotno = KD63WData[iSp].LOTCNT ;

     if (Form1->Query1->FieldValues["LOTNO"] != KD63WData[iSp].LOTNO[iLotno] )
     {
        iLotno += 1;
        if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
           KD63WData[iSp].LOTNO[iLotno] = " ";
        }else {
           KD63WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
        }

        // HSC��MAX��MIN
        if (Form1->Query1->FieldValues["HSC_A_MIN"].IsNull()) {
           KD63WData[iSp].HSC_MIN[0][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MIN[0][iLotno] = Form1->Query1->FieldValues["HSC_A_MIN"];
        }
        if (Form1->Query1->FieldValues["HSC_A_MAX"].IsNull()) {
           KD63WData[iSp].HSC_MAX[0][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MAX[0][iLotno] = Form1->Query1->FieldValues["HSC_A_MAX"];
        }

        if (Form1->Query1->FieldValues["HSC_S_MIN"].IsNull()) {
           KD63WData[iSp].HSC_MIN[1][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MIN[1][iLotno] = Form1->Query1->FieldValues["HSC_S_MIN"];
        }
        if (Form1->Query1->FieldValues["HSC_S_MAX"].IsNull()) {
           KD63WData[iSp].HSC_MAX[1][iLotno] = 0;
        }else {
           KD63WData[iSp].HSC_MAX[1][iLotno] = Form1->Query1->FieldValues["HSC_S_MAX"];
        }

        // HSD��MAX��MIN
        if (Form1->Query1->FieldValues["HSD_A_MIN"].IsNull()) {
           KD63WData[iSp].HSD_MIN[0][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MIN[0][iLotno] = Form1->Query1->FieldValues["HSD_A_MIN"];
        }
        if (Form1->Query1->FieldValues["HSD_A_MAX"].IsNull()) {
           KD63WData[iSp].HSD_MAX[0][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MAX[0][iLotno] = Form1->Query1->FieldValues["HSD_A_MAX"];
        }

        if (Form1->Query1->FieldValues["HSD_S_MIN"].IsNull()) {
           KD63WData[iSp].HSD_MIN[1][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MIN[1][iLotno] = Form1->Query1->FieldValues["HSD_S_MIN"];
        }
        if (Form1->Query1->FieldValues["HSD_S_MAX"].IsNull()) {
           KD63WData[iSp].HSD_MAX[1][iLotno] = 0.0;
        }else {
           KD63WData[iSp].HSD_MAX[1][iLotno] = Form1->Query1->FieldValues["HSD_S_MAX"];
        }
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD63WData[iSp].DTKSHIN = " ";
     }else {
            KD63WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // HSC�̈��ʑ���l
     iDtNo = KD63WData[iSp].HSC_SOKUTEI_NM[0][iLotno] ;

     if (Form1->Query1->FieldValues["HSC_A"].IsNull()) {
         KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] = Form1->Query1->FieldValues["HSC_A"];
     }
     if (KD63WData[iSp].HSC_CH[0][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSC_SOKUTEI_NM[0][iLotno] = iDtNo;
     }

     // HSC�̑��ʑ���l
     iDtNo = KD63WData[iSp].HSC_SOKUTEI_NM[1][iLotno] ;

     if (Form1->Query1->FieldValues["HSC_S"].IsNull()) {
         KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] = Form1->Query1->FieldValues["HSC_S"];
     }
     if (KD63WData[iSp].HSC_CH[1][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSC_SOKUTEI_NM[1][iLotno] = iDtNo;
     }

     // HSD�̈��ʑ���l
     iDtNo = KD63WData[iSp].HSD_SOKUTEI_NM[0][iLotno] ;

     if (Form1->Query1->FieldValues["HSD_A"].IsNull()) {
         KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] = Form1->Query1->FieldValues["HSD_A"];
     }
     if (KD63WData[iSp].HSD_CH[0][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSD_SOKUTEI_NM[0][iLotno] = iDtNo;
     }

     // HSD�̑��ʑ���l
     iDtNo = KD63WData[iSp].HSD_SOKUTEI_NM[1][iLotno] ;

     if (Form1->Query1->FieldValues["HSD_S"].IsNull()) {
         KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] = 0.0;
     }else {
         KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] = Form1->Query1->FieldValues["HSD_S"];
     }
     if (KD63WData[iSp].HSD_CH[1][iLotno][iDtNo] > 0.0) {
        iDtNo += 1;
        KD63WData[iSp].HSD_SOKUTEI_NM[1][iLotno] = iDtNo;
     }

     KD63WData[iSp].LOTCNT = iLotno ;
 }

// KD61Data��KD63W�փR�s�[����
void  CopyKD61Data(void)
{

   int i,n,k,iLinkSp, Cur_Num;
   double a, b;

   for( i = 0; i < 30; i++ ){

        if (KD61Data[i].SAMPLE_P == -1 ) continue ;

        if( KD61Data[i].SOKUTE_KBN1 == 0 && KD61Data[i].SOKUTE_KBN2 == 0 ) continue ;

        // ���ĕi�Ԃ��n�߂Čv���ꍇ
        if(  KD61Data[i].LINK == 0 ){
            iLinkSp = KD61Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD61Data[i].LINK;
        }

        if (KD63WData[iLinkSp-1].LOTCNT == -1 ){

           //ۯ�NO�J���^�[
           KD63WData[iLinkSp-1].LOTCNT = 1;

           //���Ӑ�i��
           KD63WData[iLinkSp-1].DTKSHIN =  KD61Data[i].DTKSHIN;

           //���b�gNO
           KD63WData[iLinkSp-1].LOTNO[0]  = KD61Data[i].LOTNO ;

           // HSC
           // �K�i��
           KD63WData[iLinkSp-1].HSC_MIN[0][0] = KD61Data[i].HSC_A_MIN;
           KD63WData[iLinkSp-1].HSC_MIN[1][0] = KD61Data[i].HSC_S_MIN;

           // �K�i��
           KD63WData[iLinkSp-1].HSC_MAX[0][0] = KD61Data[i].HSC_A_MAX;
           KD63WData[iLinkSp-1].HSC_MAX[1][0] = KD61Data[i].HSC_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN1) {
           case 1:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = 0;
                break;
           case 3:
                if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM) {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][0] = KD61Data[i].HSC_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][0] = 0;
                }
                break;
           }

           // HSD
           // �K�i��
           KD63WData[iLinkSp-1].HSD_MIN[0][0] = KD61Data[i].HSD_A_MIN;
           KD63WData[iLinkSp-1].HSD_MIN[1][0] = KD61Data[i].HSD_S_MIN;

           // �K�i��
           KD63WData[iLinkSp-1].HSD_MAX[0][0] = KD61Data[i].HSD_A_MAX;
           KD63WData[iLinkSp-1].HSD_MAX[1][0] = KD61Data[i].HSD_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN2) {
           case 1:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = 0;
                break;
           case 3:
                if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM) {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][0] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][0] = 0;
                }
                break;
           }

           if ( KD61Data[i].HSC_SK_NUM_CUR > 0) {    // HSC
              //����l
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM && KD61Data[i].SOKUTE_KBN1 == 3) {
                 Cur_Num = KD61Data[i].HSC_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSC_CH[0][0][k] = KD61Data[i].HSC_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSC_CH[0][0][k] ;
                 }
                 //���ϒl
                 KD63WData[iLinkSp-1].HSC_AVE[0][0] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSC_CH[1][0][k] = KD61Data[i].HSC_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSC_CH[1][0][k] ;
                 }
                 KD63WData[iLinkSp-1].HSC_AVE[1][0] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSC_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                        KD63WData[iLinkSp-1].HSC_CH[0][0][k] = KD61Data[i].HSC_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSC_CH[0][0][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN1 == 2) {
                        KD63WData[iLinkSp-1].HSC_CH[1][0][k] = KD61Data[i].HSC_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSC_CH[1][0][k] ;
                     }
                 }

                 //���ϒl
                 KD63WData[iLinkSp-1].HSC_AVE[0][0] = a/KD61Data[i].HSC_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSC_AVE[1][0] = b/KD61Data[i].HSC_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSC_AVE[0][0] = 0.0;
              KD63WData[iLinkSp-1].HSC_AVE[1][0] = 0.0;
           }

           if ( KD61Data[i].HSD_SK_NUM_CUR > 0) {    // HSD
              //����l
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM && KD61Data[i].SOKUTE_KBN2 == 3) {
                 Cur_Num = KD61Data[i].HSD_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSD_CH[0][0][k] = KD61Data[i].HSD_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSD_CH[0][0][k] ;
                 }
                 //���ϒl
                 KD63WData[iLinkSp-1].HSD_AVE[0][0] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSD_CH[1][0][k] = KD61Data[i].HSD_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSD_CH[1][0][k] ;
                 }
                 KD63WData[iLinkSp-1].HSD_AVE[1][0] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSD_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                        KD63WData[iLinkSp-1].HSD_CH[0][0][k] = KD61Data[i].HSD_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSD_CH[0][0][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN2 == 2) {
                        KD63WData[iLinkSp-1].HSD_CH[1][0][k] = KD61Data[i].HSD_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSD_CH[1][0][k] ;
                     }
                 }

                 //���ϒl
                 KD63WData[iLinkSp-1].HSD_AVE[0][0] = a/KD61Data[i].HSD_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSD_AVE[1][0] = b/KD61Data[i].HSD_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSD_AVE[0][0] = 0.0;
              KD63WData[iLinkSp-1].HSD_AVE[1][0] = 0.0;
           }
        //----------------------------------------------------------------
        // �����ް����ɶ��ĕi�Ԃ��������Ă���ꍇ
        }else{

           // �����ް��̌��ֶ���ۯ�NO���ް���ǉ�
           //ۯ�NO�J���^�[
           KD63WData[iLinkSp-1].LOTCNT += 1;

           n = KD63WData[iLinkSp-1].LOTCNT ;

           //���b�gNO
           KD63WData[iLinkSp-1].LOTNO[n-1]  = KD61Data[i].LOTNO ;

           //HSC�̋K�i��
           KD63WData[iLinkSp-1].HSC_MIN[0][n-1] = KD61Data[i].HSC_A_MIN;
           KD63WData[iLinkSp-1].HSC_MIN[1][n-1] = KD61Data[i].HSC_S_MIN;

           //HSC�̋K�i��
           KD63WData[iLinkSp-1].HSC_MAX[0][n-1] = KD61Data[i].HSC_A_MAX;
           KD63WData[iLinkSp-1].HSC_MAX[1][n-1] = KD61Data[i].HSC_S_MAX;

           //HSD�̋K�i��
           KD63WData[iLinkSp-1].HSD_MIN[0][n-1] = KD61Data[i].HSD_A_MIN;
           KD63WData[iLinkSp-1].HSD_MIN[1][n-1] = KD61Data[i].HSD_S_MIN;

           //HSD�̋K�i��
           KD63WData[iLinkSp-1].HSD_MAX[0][n-1] = KD61Data[i].HSD_A_MAX;
           KD63WData[iLinkSp-1].HSD_MAX[1][n-1] = KD61Data[i].HSD_S_MAX;

           switch (KD61Data[i].SOKUTE_KBN1) {
           case 1:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = 0;
                break;
           case 3:
                if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM) {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][n-1] = KD61Data[i].HSC_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][n-1] = 0;
                }
                break;
           }

           switch (KD61Data[i].SOKUTE_KBN2) {
           case 1:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = 0;
                break;
           case 2:
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = 0;
                break;
           case 3:
                if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM) {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                } else {
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][n-1] = KD61Data[i].HSD_SK_NUM_CUR;
                   KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][n-1] = 0;
                }
                break;
           }

           if ( KD61Data[i].HSC_SK_NUM_CUR > 0) {    // HSC
              //����l
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSC_SK_NUM_CUR > KD61Data[i].HSC_SK_NUM && KD61Data[i].SOKUTE_KBN1 == 3) {
                 Cur_Num = KD61Data[i].HSC_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] = KD61Data[i].HSC_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] ;
                 }
                 //���ϒl
                 KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSC_SK_NUM_CUR - KD61Data[i].HSC_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] = KD61Data[i].HSC_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] ;
                 }
                 KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSC_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN1 == 1 || KD61Data[i].SOKUTE_KBN1 == 3) {
                        KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] = KD61Data[i].HSC_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSC_CH[0][n-1][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN1 == 2) {
                        KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] = KD61Data[i].HSC_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSC_CH[1][n-1][k] ;
                     }
                 }

                 //���ϒl
                 KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = a/KD61Data[i].HSC_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = b/KD61Data[i].HSC_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSC_AVE[0][n-1] = 0.0;
              KD63WData[iLinkSp-1].HSC_AVE[1][n-1] = 0.0;
           }

           if ( KD61Data[i].HSD_SK_NUM_CUR > 0) {    // HSD
              //����l
              a = 0.0;
              b = 0.0;

              if (KD61Data[i].HSD_SK_NUM_CUR > KD61Data[i].HSD_SK_NUM && KD61Data[i].SOKUTE_KBN2 == 3) {
                 Cur_Num = KD61Data[i].HSD_SK_NUM;
                 for (k=0; k < Cur_Num; k++ ) {
                     KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] = KD61Data[i].HSD_A_CH[k];
                     a += KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] ;
                 }
                 //���ϒl
                 KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = a/Cur_Num;

                 Cur_Num = KD61Data[i].HSD_SK_NUM_CUR - KD61Data[i].HSD_SK_NUM;
                 for (k = 0; k < Cur_Num; k++) {
                     KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] = KD61Data[i].HSD_S_CH[k];
                     b += KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] ;
                 }
                 KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = b/Cur_Num;
              } else {
                 for (k=0; k < KD61Data[i].HSD_SK_NUM_CUR; k++ ) {
                     if (KD61Data[i].SOKUTE_KBN2 == 1 || KD61Data[i].SOKUTE_KBN2 == 3) {
                        KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] = KD61Data[i].HSD_A_CH[k];
                        a += KD63WData[iLinkSp-1].HSD_CH[0][n-1][k] ;
                     }
                     if (KD61Data[i].SOKUTE_KBN2 == 2) {
                        KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] = KD61Data[i].HSD_S_CH[k];
                        b += KD63WData[iLinkSp-1].HSD_CH[1][n-1][k] ;
                     }
                 }

                 //���ϒl
                 KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = a/KD61Data[i].HSD_SK_NUM_CUR;
                 KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = b/KD61Data[i].HSD_SK_NUM_CUR;
              }
           } else {
              KD63WData[iLinkSp-1].HSD_AVE[0][n-1] = 0.0;
              KD63WData[iLinkSp-1].HSD_AVE[1][n-1] = 0.0;
           }
        }

   }
}

// �v������������߼޼��NO���ް��𗚗��ް��֒ǉ�
// A_No: 1: Hsc
//       2: Hsd
void  AddKd63W(int A_No)
{
   int i,iLinkSp, iRtn;
   double dAve ;

   if (!(A_No == 1 || A_No == 2))
      return;

   //�����ް�̧�ق̃`�F�b�N
   if (A_No == 1) { // Hsc

      if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR == 0 ) return ;

      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 0 ) return ;

      //-------------------------------------
      // ���ĕi�Ԃ��n�߂Čv���ꍇ
      if (KD61Data[Hsc_SamplePositionIdx-1].LINK == 0 ){
         iLinkSp = Hsc_SamplePositionIdx ;
      } else {
         iLinkSp = KD61Data[Hsc_SamplePositionIdx-1].LINK;
      }

      //�����ް����ɶ���ۯ�No��INDEXNO
      iRtn =  CheckLotNo(Hsc_SamplePositionIdx ) ;
      if (iRtn <0 ) return ;

      //�v�������ް��̍X�V
      //���b�gNO
      KD63WData[iLinkSp-1].LOTNO[iRtn] = KD61Data[Hsc_SamplePositionIdx-1].LOTNO;

      // HSC
      //�K�i��
      KD63WData[iLinkSp-1].HSC_MIN[0][iRtn]= KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MIN;
      KD63WData[iLinkSp-1].HSC_MIN[1][iRtn]= KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MIN;

      //�K�i��
      KD63WData[iLinkSp-1].HSC_MAX[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MAX;
      KD63WData[iLinkSp-1].HSC_MAX[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MAX;

      switch (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1) {
      case 1:
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = 0;
           break;
      case 2:
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = 0;
           break;
      case 3:
           if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
           } else {
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
              KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] = 0;
           }
           break;
      }

      // ����
      if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn] > 0) {
         //����l
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSC_CH[0][iRtn][i] = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[i];
             dAve += KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[0][iRtn];

         KD63WData[iLinkSp-1].HSC_AVE[0][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSC_AVE[0][iRtn]=0.0;

      // ����
      if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn] > 0) {
         //����l
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSC_CH[1][iRtn][i] = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[i];
             dAve += KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[1][iRtn];

         KD63WData[iLinkSp-1].HSC_AVE[1][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSC_AVE[1][iRtn]=0.0;
   } else { // HSD

      if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR == 0 ) return ;

      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 0 ) return ;

      //-------------------------------------
      // ���ĕi�Ԃ��n�߂Čv���ꍇ
      if (KD61Data[Hsd_SamplePositionIdx-1].LINK == 0 ){
         iLinkSp = Hsd_SamplePositionIdx ;
      } else {
         iLinkSp = KD61Data[Hsd_SamplePositionIdx-1].LINK;
      }

      //�����ް����ɶ���ۯ�No��INDEXNO
      iRtn =  CheckLotNo(Hsd_SamplePositionIdx ) ;
      if (iRtn <0 ) return ;

      //�v�������ް��̍X�V
      //���b�gNO
      KD63WData[iLinkSp-1].LOTNO[iRtn] = KD61Data[Hsd_SamplePositionIdx-1].LOTNO;

      // HSC
      //�K�i��
      KD63WData[iLinkSp-1].HSD_MIN[0][iRtn]= KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MIN;
      KD63WData[iLinkSp-1].HSD_MIN[1][iRtn]= KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MIN;

      //�K�i��
      KD63WData[iLinkSp-1].HSD_MAX[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MAX;
      KD63WData[iLinkSp-1].HSD_MAX[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MAX;

      switch (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2) {
      case 1:
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = 0;
           break;
      case 2:
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
           KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = 0;
           break;
      case 3:
           if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
           } else {
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
              KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] = 0;
           }
           break;
      }

      // ����
      if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn] > 0) {
         //����l
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSD_CH[0][iRtn][i] = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[i];
             dAve += KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[0][iRtn];

         KD63WData[iLinkSp-1].HSD_AVE[0][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSD_AVE[0][iRtn]=0.0;

      // ����
      if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn] > 0) {
         //����l
         dAve = 0.0;
         for ( i=0; i < KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn]; i++ ) {
             KD63WData[iLinkSp-1].HSD_CH[1][iRtn][i] = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[i];
             dAve += KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[i];
         }

         dAve= dAve/KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[1][iRtn];

         KD63WData[iLinkSp-1].HSD_AVE[1][iRtn]=dAve;
      } else
         KD63WData[iLinkSp-1].HSD_AVE[1][iRtn]=0.0;
   }
}

// KD63W����ǂݍ����ް����ɂɎw�肵�����b�gNo �L�邩�ǂ��� �̃`�F�b�N                            *
int  CheckLotNo(int iSp)
{

   int iLinkSp;

   int iFlag = -1;

    if (KD61Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   } else {
       iLinkSp = KD61Data[iSp-1].LINK;
   }

   for (int i=0; i < KD63WData[iLinkSp-1].LOTCNT; i++ ){
      if (KD61Data[iSp-1].LOTNO ==  KD63WData[iLinkSp-1].LOTNO[i] )
      {
        iFlag = i ;
        break ;
       }
   }

   return iFlag ;
}



/***********************************************************************
*  function name : void Kd63W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd63W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd63W_Delete01(void)
{
    AnsiString str;
    char str_c[256];
    int ErrFlag = 0;


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //���₢������  Update
    sprintf(str_c, " DELETE FROM KD63W");

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
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
     }
     catch(Exception& e)
     {
       // ShowMessage(e.Message);
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       Form1->StatBarClear( e.Message )  ;
       ErrFlag = 1;
     }
 }
