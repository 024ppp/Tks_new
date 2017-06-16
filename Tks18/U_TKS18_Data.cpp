/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�W�j                  *
*  file   name   : U_TKS18_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �R�ܗ͑��菈���f�[�^�A�N�Z�X�֐�                    *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ���[�N�ϐ�

// �֐��̐錾
void SetTable81(void);
int  Kd82_Serch02( AnsiString , int , int, int );
void Kd82_Update01( int );
void Kd82_Update02( AnsiString , int, int, int );
void Kd82_Insert01( AnsiString , int ,int, int );
void SetTable83W(int);

/***********************************************************************
*  function name : int  Kd81_Serch01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �R�ܗ��ް�̧�ق��猟���\����A�ڰNo�𒊏o           *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int Kd81_Serch01(void)
{

    // �R�ܗ��ް�̧�ق���}�X�^�f�[�^�𒊏o
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD81.KENSA_YMD, KD81.TOLEY_NO ";
    sBuf += "FROM KD81 ";
    sBuf += "WHERE KD81.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
    sBuf += "ORDER BY KD81.KENSA_YMD desc, KD81.TOLEY_NO";

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
*  function name : void Kd81_Serch02(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �R�ܗ��ް�̧�ق����ް��𒊏o  KD81                  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd81_Serch02( void)
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

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //�₢���������s
        //�\�[�g���� ,�����\����A�g���[No
	    sBuf = "SELECT *  ";
	    sBuf += "FROM KD81 ";
	    sBuf += "WHERE  KD81.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD81.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND  KD81.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	    //2001.05.21 �C�� sBuf += "ORDER BY KD81.KENSA_YMD, KD81.TOLEY_NO, KD81.SAMPLE_P";
	    sBuf += "ORDER BY KD81.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->RecordCount <= 0 ) {
          // ShowMessage("KD81�Ƀf�[�^������܂���");
          return -1;
        }else {

            // �ڰNO�̐ݒ�
           if( Save_Click )
               Form1->edttlno->Text = strVal02 ;

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable81();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD81Data[i].SOKUTE_KBN  && KD81Data[i].SAMPLE_P != -1 ) {
             if( KD81Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD81Data[i].DTKSHIN == KD81Data[j].DTKSHIN)
                        KD81Data[j].LINK = KD81Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //�v�����m���Q�̏ꍇ �R�ܗ͑���i��O�j̧�ق�ǂݍ���
       for( i=0; i<30; i++ )
       {
         // if( KD81Data[i].SOKUTEI_NM > 2 && KD81Data[i].SOKUTE_KBN == 1 &&
         //     KD81Data[i].SOKUTEI_NM_CUR > 0 ) {

             if(  KD81Data[i].SOKUTE_KBN == 1 ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD81Data[i].SAMPLE_P );

              //�₢���������s
              //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����
	        sBuf = "SELECT  * ";
	        sBuf += "FROM KD82 ";
	        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND   TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND   SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND   KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ� 
	        //2001.05.21 �C�� sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P, SOKUTEI_NO";
	        sBuf += "ORDER BY SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD82�Ƀf�[�^������܂���");
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

                             //�j��׏d
                             if ( Form1->Query1->FieldValues["SOKUTEI_K"].IsNull()) {
                                   KD81Data[i].SOKUTEI_K[n-1] = 0.0;
                             }else {
                                   KD81Data[i].SOKUTEI_K[n-1] =  Form1->Query1->FieldValues["SOKUTEI_K"];
                             }
                             //����
                            if ( Form1->Query1->FieldValues["SOKUTEI_P"].IsNull()) {
                                   KD81Data[i].SOKUTEI_P[n-1] = 0.0;
                             }else {
                                   KD81Data[i].SOKUTEI_P[n-1] =  Form1->Query1->FieldValues["SOKUTEI_P"];
                             }

                             if( !iBotai ) {

                                 //�������@
                                 if ( Form1->Query1->FieldValues["SOKUTEI_S"].IsNull()) {
                                      KD81Data[i].SOKUTEI_S[n-1] = 0.0;
                                 }else {
                                      KD81Data[i].SOKUTEI_S[n-1] =  Form1->Query1->FieldValues["SOKUTEI_S"];
                                 }
                                 //�����@
                                if ( Form1->Query1->FieldValues["SOKUTEI_H"].IsNull()) {
                                      KD81Data[i].SOKUTEI_H[n-1] = 0.0;
                                 }else {
                                     KD81Data[i].SOKUTEI_H[n-1] =  Form1->Query1->FieldValues["SOKUTEI_H"];
                                 }
                                 //�R�ܗ�
                                if ( Form1->Query1->FieldValues["SOKUTEI_M"].IsNull()) {
                                     KD81Data[i].SOKUTEI_M[n-1] = 0.0;
                                }else {
                                     KD81Data[i].SOKUTEI_M[n-1] =  Form1->Query1->FieldValues["SOKUTEI_M"];
                                }
                            }else{
                                // �R�ܗ͂̍Čv�Z
                                 MForceCal(i+1,n ) ;
                            }


                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable81(int )                               *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : KD81Data�\���̂��ް���ݒ�                          *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable81()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD81Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD81Data[iRec].KENSA_YMD = " ";
     }else {
          KD81Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD81Data[iRec].TOLEY_NO = 0;
     }else {
          KD81Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD81Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD81Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 && KD81Data[iRec].SOKUTE_KBN == 1 ){
            HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["KEIJYO_KBN"].IsNull()) {
          KD81Data[iRec].KEIJYO_KBN = 0;
     }else {
          KD81Data[iRec].KEIJYO_KBN =  Form1->Query1->FieldValues["KEIJYO_KBN"];
     }


     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD81Data[iRec].DTKSCOD = " ";
     }else {
          KD81Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD81Data[iRec].DTKSHIN = " ";
     }else {
          KD81Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD81Data[iRec].LOTNO = " ";
     }else {
          KD81Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD81Data[iRec].HINBAN = " ";
     }else {
          KD81Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD81Data[iRec].ZISCOD = " ";
     }else {
          KD81Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD81Data[iRec].ZISNAM = " ";
     }else {
          KD81Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["MAGE_MIN"].IsNull()) {
          KD81Data[iRec].MAGE_MIN = 0.0;
     }else {
          KD81Data[iRec].MAGE_MIN =  Form1->Query1->FieldValues["MAGE_MIN"];
     }

     if ( Form1->Query1->FieldValues["MAGE_MAX"].IsNull()) {
          KD81Data[iRec].MAGE_MAX = 0.0;
     }else {
          KD81Data[iRec].MAGE_MAX =  Form1->Query1->FieldValues["MAGE_MAX"];
     }

     if ( Form1->Query1->FieldValues["MAGE_SPAN"].IsNull()) {
          KD81Data[iRec].MAGE_SPAN = 0.0;
     }else {
          KD81Data[iRec].MAGE_SPAN =  Form1->Query1->FieldValues["MAGE_SPAN"];
     }

     if ( Form1->Query1->FieldValues["MAGE_TAN"].IsNull()) {
          KD81Data[iRec].MAGE_TAN = 0;
     }else {
          KD81Data[iRec].MAGE_TAN =  Form1->Query1->FieldValues["MAGE_TAN"];
     }

      //�j��׏d�P�A�j��׏d�Q
     if ( Form1->Query1->FieldValues["SOKUTEI_1K"].IsNull()) {
          KD81Data[iRec].SOKUTEI_K[0] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_K[0] =  Form1->Query1->FieldValues["SOKUTEI_1K"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2K"].IsNull()) {
          KD81Data[iRec].SOKUTEI_K[1] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_K[1] =  Form1->Query1->FieldValues["SOKUTEI_2K"];
     }
     //���݂P�A���݂Q
      if ( Form1->Query1->FieldValues["SOKUTEI_1P"].IsNull()) {
          KD81Data[iRec].SOKUTEI_P[0] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_P[0] =  Form1->Query1->FieldValues["SOKUTEI_1P"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2P"].IsNull()) {
          KD81Data[iRec].SOKUTEI_P[1] = 0.0;
     }else {
          KD81Data[iRec].SOKUTEI_P[1] =  Form1->Query1->FieldValues["SOKUTEI_2P"];
     }

     //�����
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD81Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD81Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD81Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD81Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD81Data[iRec].ADDYMD = " ";
     }else {
          KD81Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];

     }

     if( IsNullSpace( KD81Data[iRec].ADDYMD )){
             KD81Data[iRec].SOKUTEI_NM_CUR = 0 ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
                 KD81Data[iRec].SOKUTEI_NS_CUR = 0;
                 KD81Data[iRec].SOKUTEI_NH_CUR = 0;
             }
             KD81Data[iRec].SOKUTEI_NK_CUR = 0;

             //�w���X�p����ܰ��ϐ��֕ۑ�
             for( int i=0; i< KD81Data[iRec].SOKUTEI_NM; i++ )
                   KD81Data[iRec].SOKUTEI_P[i] = KD81Data[iRec].MAGE_SPAN;

              KD81Data[iRec].SOKUTEI_NP_CUR = KD81Data[iRec].SOKUTEI_SU ;
     }else{
             KD81Data[iRec].SOKUTEI_NM_CUR = KD81Data[iRec].SOKUTEI_SU ;
             if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR){
                KD81Data[iRec].SOKUTEI_NS_CUR = KD81Data[iRec].SOKUTEI_SU ;
                KD81Data[iRec].SOKUTEI_NH_CUR = KD81Data[iRec].SOKUTEI_SU ;
             }
             KD81Data[iRec].SOKUTEI_NK_CUR = KD81Data[iRec].SOKUTEI_SU ;
             KD81Data[iRec].SOKUTEI_NP_CUR = KD81Data[iRec].SOKUTEI_SU ;
     }
     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD81Data[iRec].ADDTIM = " ";
     }else {
          KD81Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD81Data[iRec].UPDYMD = " ";
     }else {
          KD81Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD81Data[iRec].UPDCHR = 0;
     }else {
          KD81Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD81Data[iRec].UPDCNT = 0;
     }else {
          KD81Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //���l 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD81Data[iRec].MEMO = " ";
     }else {
          KD81Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

     // ��̔�d�v���ް����g���ꍇ
  //   if( ! iBotai ||  ! KD51Data[iRec].SOKUTEI_NB_CUR ){
        if( ! iBotai ){

       // �������@�P�A�������@�Q
       if ( Form1->Query1->FieldValues["SOKUTEI_1S"].IsNull()) {
          KD81Data[iRec].SOKUTEI_S[0] = 0.0;
        }else {
          KD81Data[iRec].SOKUTEI_S[0] =  Form1->Query1->FieldValues["SOKUTEI_1S"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2S"].IsNull()) {
             KD81Data[iRec].SOKUTEI_S[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_S[1] =  Form1->Query1->FieldValues["SOKUTEI_2S"];
        }

        //�����@�P�A�����@�Q
         if ( Form1->Query1->FieldValues["SOKUTEI_1H"].IsNull()) {
             KD81Data[iRec].SOKUTEI_H[0] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_H[0] =  Form1->Query1->FieldValues["SOKUTEI_1H"];
        }
        if ( Form1->Query1->FieldValues["SOKUTEI_2H"].IsNull()) {
             KD81Data[iRec].SOKUTEI_H[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_H[1] =  Form1->Query1->FieldValues["SOKUTEI_2H"];
        }

        //����l�P�R�ܗ�
         if ( Form1->Query1->FieldValues["SOKUTEI_1M"].IsNull()) {
              KD81Data[iRec].SOKUTEI_M[0] = 0.0;
         }else {
              KD81Data[iRec].SOKUTEI_M[0] =  Form1->Query1->FieldValues["SOKUTEI_1M"];
         }
         //����l�Q �R�ܗ�
        if ( Form1->Query1->FieldValues["SOKUTEI_2M"].IsNull()) {
             KD81Data[iRec].SOKUTEI_M[1] = 0.0;
        }else {
             KD81Data[iRec].SOKUTEI_M[1] =  Form1->Query1->FieldValues["SOKUTEI_2M"];
        }

        //����l���ϒl�i�R�ܗ́j
        if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
             KD81Data[iRec].SOKUTE_AVE = 0.0;
        }else {
             KD81Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
        }
        //���l 2002/11/07 E.Takase
        if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
             KD81Data[iRec].MEMO =  " ";
        }else {
             KD81Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
        }
     }else{

        // �ŗL��R���̍Čv�Z
          MForceCal(iRec+1,1 ) ;
          MForceCal(iRec+1,2 ) ;

          //���ϒl�͎g���Ă��Ȃ��̂Ŗ�������
     }

 }

/***********************************************************************
*  function name : void KD81Format(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : ���[�h����t��R�f�[�^�\����KD81Data��������  KD81  *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD81Format(void)
{
   for( int i=0; i<30; i++){
      KD81Data[i].KENSA_YMD =  '\0';  //�����\���
      KD81Data[i].TOLEY_NO = 0 ;      //�ڰNO
      KD81Data[i].SAMPLE_P = -1 ;     //������߼޼��NO
      KD81Data[i].SOKUTE_KBN = 0;     //����敪
      KD81Data[i].KEIJYO_KBN =0 ;     //�`��敪
      KD81Data[i].DTKSCOD = '\0';     //���Ӑ�R�[�h
      KD81Data[i].DTKSHIN = '\0';     //���Ӑ�i��
      KD81Data[i].LOTNO = '\0';       //���b�gNO
      KD81Data[i].HINBAN = '\0';      //���Еi��
      KD81Data[i].ZISCOD = '\0';      //�ގ��R�[�h
      KD81Data[i].ZISNAM = '\0';      //�ގ���

      KD81Data[i].MAGE_MAX = 0.0;    //�Ȃ����x �K�i��
      KD81Data[i].MAGE_MIN = 0.0;    //�Ȃ����x �K�i��
      KD81Data[i].MAGE_SPAN = 0.0;   //�Ȃ����x �������
      KD81Data[i].MAGE_TAN = 0;      //�Ȃ����x �P��
      KD81Data[i].SOKUTEI_NM = 0;    //�Ȃ����x �����
      KD81Data[i].SOKUTEI_SU = 0;    //�Ȃ����x �����
      KD81Data[i].SOKUTE_AVE = 0.0;  //�Ȃ����x ���蕽�ϒl

      memset(KD81Data[i].SOKUTEI_M,(int)NULL, sizeof(double) * 100); ;  //����l
      memset(KD81Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //�������@
      memset(KD81Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //�����@
      memset(KD81Data[i].SOKUTEI_K,(int)NULL, sizeof(double) * 100); ;  //�j��׏d
      memset(KD81Data[i].SOKUTEI_P,(int)NULL, sizeof(double) * 100); ;  //����

      KD81Data[i].ADDYMD = '\0';      //�o�^��
      KD81Data[i].ADDTIM = '\0';      //�o�^����
      KD81Data[i].UPDYMD = '\0';      //�ύX��
      KD81Data[i].UPDTIM = '\0';      //�ύX����
      KD81Data[i].UPDCHR = 0;         //�X�V��
      KD81Data[i].UPDCNT = 0;         //�X�V��
      KD81Data[i].LINK = 0;
      KD81Data[i].SOKUTEI_NM_CUR = 0;
      KD81Data[i].SOKUTEI_NS_CUR = 0;
      KD81Data[i].SOKUTEI_NH_CUR = 0;
      KD81Data[i].SOKUTEI_NK_CUR = 0;
      KD81Data[i].SOKUTEI_NP_CUR = 0;
      KD81Data[i].SOKUTEI_NP_CUR = 0;

      KD81Data[i].MEMO = '\0';         //���l 2002/11/07 E.Takase

   }
}

/***********************************************************************
*  function name : void Kd81_Update01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : �v���ް����R�ܗ��ް�̧�ق֏�������  KD81            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd81_Update01( void)
{
    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // ��ʂ̓����ް����擾
    if( DataNoIdx == 1 ){

             // �v���ް�1
             if( iKomoku==1)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_K[0] = pEdt1_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 1 );

    }else if( DataNoIdx == 2 ){

             // �v���ް�2
             if( iKomoku==1)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==2)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[iKomoku-1]->Value;
             if( iKomoku==3)
                 KD81Data[SamplePositionIdx-1].SOKUTEI_K[1] = pEdt2_S[iKomoku-1]->Value;

              MForceCal(SamplePositionIdx, 2 );

    }else {
             // �v���ް� n?
             if( KD81Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

                 n = pEdt4_S[iKomoku-1]->Value;
                 if( n>=3 && n <= KD81Data[SamplePositionIdx-1].SOKUTEI_NM ) {

                    // �v���ް�2
                   if( iKomoku==1)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==2)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;
                   if( iKomoku==3)
                      KD81Data[SamplePositionIdx-1].SOKUTEI_K[n-1] = pEdt3_S[iKomoku-1]->Value;

                   MForceCal(SamplePositionIdx, n );
                 }
             }
    }


	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD81Data[i].SOKUTE_KBN == 1 && KD81Data[i].SAMPLE_P != -1 &&
				!( KD81Data[i].SOKUTEI_NM_CUR == 0 &&
				KD81Data[i].SOKUTEI_NS_CUR == 0 &&
				KD81Data[i].SOKUTEI_NH_CUR == 0 &&
				KD81Data[i].SOKUTEI_NK_CUR == 0 )  ){

			//�S���Һ���
			KD81Data[i].UPDCHR = USER_COD ;

			// ����\���
			//KD81Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// �ڰNO
			//KD81Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//����l���ϒl�̎Z�o
			double a = 0.0;
			for(j=0; j< KD81Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD81Data[i].SOKUTEI_M[j] ;
			if( KD81Data[i].SOKUTEI_NM_CUR )
				KD81Data[i].SOKUTE_AVE = a/KD81Data[i].SOKUTEI_NM_CUR ;

			// �o�^���A�o�^����
			if( IsNullSpace( KD81Data[i].ADDYMD )){
				KD81Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD81Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD81Data[i].UPDCNT = 0;

			}else{
				// �ύX���A�ύX����
				KD81Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD81Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD81Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD81 set SOKUTEI_SU=%d, SOKUTEI_1S=%6.3f , SOKUTEI_2S=%6.3f, SOKUTEI_1H=%6.3f , SOKUTEI_2H=%6.3f ,",
								KD81Data[i].SOKUTEI_NM_CUR,
								KD81Data[i].SOKUTEI_S[0],
								KD81Data[i].SOKUTEI_S[1],
								KD81Data[i].SOKUTEI_H[0],
								KD81Data[i].SOKUTEI_H[1]);
			str = str_c ;
			str_c[0] = NULL ;

			//2003.02.10 E.Takase sprintf(str_c, " SOKUTEI_1K=%6.1f , SOKUTEI_2K=%6.1f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
			sprintf(str_c, " SOKUTEI_1K=%6.2f , SOKUTEI_2K=%6.2f, SOKUTEI_1P=%6.1f , SOKUTEI_2P=%6.1f ,",
								KD81Data[i].SOKUTEI_K[0],
								KD81Data[i].SOKUTEI_K[1],
								KD81Data[i].SOKUTEI_P[0],
								KD81Data[i].SOKUTEI_P[1]);
			str += str_c ;
			str_c[0] = NULL ;

			sprintf(str_c, " SOKUTEI_1M=%9.3f , SOKUTEI_2M=%9.3f, SOKUTE_AVE=%12.6f,",
								KD81Data[i].SOKUTEI_M[0],
								KD81Data[i].SOKUTEI_M[1],
								KD81Data[i].SOKUTE_AVE);
			str += str_c ;
			str_c[0] = NULL ;

			//���l�ǉ� 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD81Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD81Data[i].ADDYMD.c_str(),
									KD81Data[i].ADDTIM.c_str(),
									KD81Data[i].UPDCHR,
									KD81Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD81Data[i].UPDYMD.c_str(),
									KD81Data[i].UPDTIM.c_str(),
									KD81Data[i].UPDCHR,
									KD81Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD81Data[i].KENSA_YMD.c_str(),
			//					KD81Data[i].TOLEY_NO ,
			//					KD81Data[i].SAMPLE_P );
                        // 20160630_�H��敪�ǉ�
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD81Data[i].KENSA_YMD.c_str(),
						KD81Data[i].TOLEY_NO ,
						KD81Data[i].SAMPLE_P ,
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

			// �R�ܗ͑���i��O�j̧�ق̍X�V
			if( KD81Data[i].SOKUTEI_NM > 2 ){
				Kd82_Update01(i) ;
			}
		} else {
			//���l�̂ݓ����Ă����ꍇ�A���l�̂ݕۑ�
			if(!(IsNullSpace( KD81Data[i].ADDYMD )) || !(IsNullSpace(KD81Data[i].MEMO))){
				// �o�^���A�o�^����
				if( IsNullSpace( KD81Data[i].ADDYMD )){
					KD81Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD81Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD81Data[i].UPDCNT = 0;

				}else{
					// �ύX���A�ύX����
					KD81Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD81Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD81Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD81 set MEMO='%s' , ", KD81Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD81Data[i].ADDYMD.c_str(),
										KD81Data[i].ADDTIM.c_str(),
										KD81Data[i].UPDCHR,
										KD81Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD81Data[i].UPDYMD.c_str(),
										KD81Data[i].UPDTIM.c_str(),
										KD81Data[i].UPDCHR,
										KD81Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD81Data[i].KENSA_YMD.c_str(),
				//					KD81Data[i].TOLEY_NO ,
				//					KD81Data[i].SAMPLE_P );
                                // 20160630_�H��敪�ǉ�
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD81Data[i].KENSA_YMD.c_str(),
						KD81Data[i].TOLEY_NO ,
						KD81Data[i].SAMPLE_P ,
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
*  function name : void Kd82_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   iRec     | ���Ļ�����߼޼��NO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v���ް�(>2)���R�ܗ͑���(��O�j̧�ق֏�������  KD82 *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD81Data[iRec].SOKUTEI_NM; i++ ){

         // KD82�֒ǉ����郌�R�[�h���݂��邩�ǂ����̃`�F�b�N
         iRtn = Kd82_Serch02( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // �Y�����R�[�h�����݂��Ȃ��ꍇ�ǉ��iInsert�j
         if( iRtn < 0 ) {
                Kd82_Insert01( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // �Y�����R�[�h�����݂���ꍇ�X�V�iUpdate�j
                Kd82_Update02( KD81Data[iRec].KENSA_YMD,
                          KD81Data[iRec].TOLEY_NO,
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
*  function name : int Kd82_Serch02(AnsiString sYmd, int iTlno,        *
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
*  update        :                                                     *
*  contents      : �w�肵��ں��ނ��R�ܗ͗�O̧�قɂ��邩�ǂ���������   *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd82_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD82 ";
        sBuf += "WHERE  KD82.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD82.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD82.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD82.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD82.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_�H��敪�ǉ�
        //2001.05.21 �C�� sBuf += "ORDER BY KD82.KENSA_YMD, KD82.TOLEY_NO, KD82.SAMPLE_P, KD82.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof ) return -1 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd82_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD82�֎w�肵��ں��ނ��X�V����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD82 set SOKUTEI_S=%6.3f ,", KD81Data[iSp-1].SOKUTEI_S[iDtNo-1]);
    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_H=%6.3f ,", KD81Data[iSp-1].SOKUTEI_H[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, "SOKUTEI_K=%6.1f ,", KD81Data[iSp-1].SOKUTEI_K[iDtNo-1]);
    sprintf(str_c, "SOKUTEI_K=%6.2f ,", KD81Data[iSp-1].SOKUTEI_K[iDtNo-1]);

    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, "SOKUTEI_P=%4.1f ,", KD81Data[iSp-1].SOKUTEI_P[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " SOKUTEI_M=%9.3f", KD81Data[iSp-1].SOKUTEI_M[iDtNo-1]);
    str += str_c ;
    str_c[0] = NULL ;

    wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
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
*  function name : void Kd82_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD82�֎w�肵��ں��ނ�ǉ�����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd82_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD82(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO,SOKUTEI_S,SOKUTEI_H, SOKUTEI_K,SOKUTEI_P, SOKUTEI_M, KOJOKBN)");	// 20160630_�H��敪�ǉ�

    str = str_c ;
    str_c[0] = NULL ;

    //2003.02.10 E.Takase sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.1f,%4.1f,%9.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    //20161201 Y.Onishi n��3�ȏ�̕ۑ����o�O�̏C��
    //sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%4.1f,%9.3f)",sYmd.c_str(), iTlno, iSp, iDtNo ,
    	sprintf(str_c, " values('%s',%d,%d,%d,%6.3f,%6.3f,%6.2f,%4.1f,%9.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo ,
                                                      KD81Data[iSp-1].SOKUTEI_S[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_H[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_K[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_P[iDtNo-1],
                                                      KD81Data[iSp-1].SOKUTEI_M[iDtNo-1],
                                                      iKojoKbn);      // 20160630_�H��敪�ǉ�

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
*  function name : void Kd83W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : �������̂��߂� KD83Wܰ��e�[�u�����쐬����         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
long  Kd83W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD83WFormat(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���[�h����t��R����ܰ��ް��\����KD83data��������   *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD83WFormat(void)
{
   for( int i=0; i<30; i++){
       KD83WData[i].DTKSHIN = '\0';              //���Ӑ�i��

       for( int j=0; j< 50 ; j++ ){
            KD83WData[i].LOTNO[j]  = 0.0 ;       //���b�gNO
            KD83WData[i].MAGE_MAX[j] = 0.0  ;    //�Ȃ����x �K�i��
            KD83WData[i].MAGE_MIN[j] = 0.0  ;    //�Ȃ����x �K�i��
            KD83WData[i].SOKUTE_AVE[j] = 0.0;
            KD83WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD83WData[i].SOKUTEI[j][k] = 0.0;  //����l
       }

       KD83WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd83W_Search01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD83Wܰ�ð��ق��烊�[�h����t��R�����f�[�^���oKD83W*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd83W_Serch01( void)
{
       int i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // �������f�[�^��ǂݍ���
        for( i=0; i<30; i++ ){

             // ���肵�Ȃ��ꍇ�A�������Ȃ�
             if( KD81Data[i].SOKUTE_KBN == 0 && KD81Data[i].SAMPLE_P == -1 ) continue ;
             if( KD81Data[i].LINK ) continue ;

             //�����߼޼��NO�̕i�Ԃƃ��b�gNO�Ō���
             strVal01 = KD81Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //�₢���������s
              //�\�[�g���� ,�����\����A�g���[No
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD83W ";
	      sBuf += "WHERE  KD83W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //�H��敪�Ɋւ�炸���藚�����擾����
              //sBuf += "AND KD83W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_�H��敪�ǉ�
               sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD81�Ƀf�[�^������܂���");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable83W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD83WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD83WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD83WData[i].SOKUTEI_NM[j]; k++)
                   dAve += KD83WData[i].SOKUTEI[j][k] ;

               if( KD83WData[i].SOKUTEI_NM[j] !=0 )
                   KD83WData[i].SOKUTE_AVE[j] = dAve/KD83WData[i].SOKUTEI_NM[j] ;
            }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable83W(int )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ܰ��ް�KD83WData���ް���ݒ�                        *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable83W(int iSp)
{

     int iLotno = KD83WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD83WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD83WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD83WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["MAGE_MIN"].IsNull()) {
               KD83WData[iSp].MAGE_MIN[iLotno] = 0.0;
            }else {
                KD83WData[iSp].MAGE_MIN[iLotno] = Form1->Query1->FieldValues["MAGE_MIN"];
            }

            if ( Form1->Query1->FieldValues["MAGE_MAX"].IsNull()) {
               KD83WData[iSp].MAGE_MAX[iLotno] = 0.0;
            }else {
                KD83WData[iSp].MAGE_MAX[iLotno] = Form1->Query1->FieldValues["MAGE_MAX"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD83WData[iSp].DTKSHIN = " ";
     }else {
            KD83WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // ����l
     int iDtNo = KD83WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD83WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD83WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD83WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD83WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD81Data(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD81Data��KD81W�փR�s�[����                         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD81Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD81Data[i].SOKUTE_KBN == 0 || KD81Data[i].SAMPLE_P == -1 ) continue ;

        // ���ĕi�Ԃ��n�߂Čv���ꍇ
        if(  KD81Data[i].LINK == 0 ){
            iLinkSp = KD81Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD81Data[i].LINK;
        }

        if( KD83WData[iLinkSp-1].LOTCNT == -1 ){

           //ۯ�NO�J���^�[
           KD83WData[iLinkSp-1].LOTCNT = 1;

           //���Ӑ�i��
           KD83WData[iLinkSp-1].DTKSHIN =  KD81Data[i].DTKSHIN;

           //���b�gNO
           KD83WData[iLinkSp-1].LOTNO[0]  = KD81Data[i].LOTNO ;

           // �K�i��
           KD83WData[iLinkSp-1].MAGE_MIN[0] = KD81Data[i].MAGE_MIN;
           // �K�i��
           KD83WData[iLinkSp-1].MAGE_MAX[0] = KD81Data[i].MAGE_MAX;

           KD83WData[iLinkSp-1].SOKUTEI_NM[0] = KD81Data[i].SOKUTEI_NM_CUR;

           if( KD81Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //����l
           double a=0.0;
           for( k=0; k < KD81Data[i].SOKUTEI_NM; k++ ) {
                  KD83WData[iLinkSp-1].SOKUTEI[0][k] = KD81Data[i].SOKUTEI_M[k];
                  a += KD83WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //���ϒl
           if( KD81Data[i].SOKUTEI_NM != 0 )
             KD83WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD81Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // �����ް����ɶ��ĕi�Ԃ��������Ă���ꍇ
     }else{

          // �����ް��̌��ֶ���ۯ�NO���ް���ǉ�
          //ۯ�NO�J���^�[
          KD83WData[iLinkSp-1].LOTCNT += 1;

          n = KD83WData[iLinkSp-1].LOTCNT ;

          //���b�gNO
          KD83WData[iLinkSp-1].LOTNO[n-1]  = KD81Data[i].LOTNO ;

          //���[�h������ �K�i��
          KD83WData[iLinkSp-1].MAGE_MIN[n-1] = KD81Data[i].MAGE_MIN;

          //���[�h������ �K�i��
          KD83WData[iLinkSp-1].MAGE_MAX[n-1] = KD81Data[i].MAGE_MAX;

          KD83WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD81Data[i].SOKUTEI_NM_CUR;

          if( KD81Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //����l
          double a=0.0;
          for( k=0; k < KD81Data[i].SOKUTEI_NM; k++ ) {
               KD83WData[iLinkSp-1].SOKUTEI[n-1][k] = KD81Data[i].SOKUTEI_M[k];
               a += KD83WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD83WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD81Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd83w(void)                                 *
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
void  AddKd83W(void)
{
   int i,iLinkSp;

   //�����ް�̧�ق̃`�F�b�N

   if( KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ���ĕi�Ԃ��n�߂Čv���ꍇ
   if(  KD81Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD81Data[SamplePositionIdx-1].LINK;
   }

   //�����ް����ɶ���ۯ�No��INDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //�v�������ް��̍X�V
   //���b�gNO
    KD83WData[iLinkSp-1].LOTNO[iRtn] = KD81Data[SamplePositionIdx-1].LOTNO;

   //���[�h������ �K�i��
    KD83WData[iLinkSp-1].MAGE_MIN[iRtn]= KD81Data[SamplePositionIdx-1].MAGE_MIN;

    //���[�h������ �K�i��
    KD83WData[iLinkSp-1].MAGE_MAX[iRtn] = KD81Data[SamplePositionIdx-1].MAGE_MAX;

    KD83WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //����l
    for( i=0; i < KD83WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD83WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD81Data[SamplePositionIdx-1].SOKUTEI_M[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD81Data[SamplePositionIdx-1].SOKUTEI_M[i];
   }

   dAve= dAve/KD81Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD83WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}

/***********************************************************************
*  function name : void Kd51_Serch02(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��̔�d�ް�̧�ق����ް��𒊏o  KD51                  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd51_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD51Data�\���̕ϐ��̏�����
        KD51Format();

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
            sBuf += "AND  KD51.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
	    //2001.05.21 �C�� sBuf += "ORDER BY KD51.KENSA_YMD, KD51.TOLEY_NO, KD51.SAMPLE_P";
	    sBuf += "ORDER BY KD51.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD51�Ƀf�[�^������܂���");
          return -1;
        }else {
           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable51();
                     Form1->Query1->Next();

            }
       }

       //�v�����m���Q�̏ꍇ ��̔�d����i��O�j̧�ق�ǂݍ���
       for( i=0; i<30; i++ )
       {
        //  if( KD51Data[i].SOKUTEI_NM > 2 && KD51Data[i].SOKUTE_KBN == 1 &&
        //      KD51Data[i].SOKUTEI_NB_CUR  ) {

             if( KD51Data[i].SOKUTE_KBN == 1 ) {
             
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
                sBuf += "AND  KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
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

                             //2002.11.06 E.Takase
                             //�����i�O�a�j���@
                             if ( Form1->Query1->FieldValues["SOKUHEI_N"].IsNull()) {
                                   KD51Data[i].SOKUTEI_N[n-1] = 0.0;
                             }else {
                                   KD51Data[i].SOKUTEI_N[n-1] =  Form1->Query1->FieldValues["SOKUHEI_N"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}
/***********************************************************************
*  function name : void Kd81_Serch03(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �Ȃ������ް�̧�قɎw�肵�����������ڰNO������ KD71  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd81_Serch03( void)
{
       int n;
       AnsiString strVal01;
       AnsiString strVal02;

        //�����l�̂̎擾
        strVal01 = DelSEPA(Form1->edtymd->Text);

        n= Form1->edttlno->Value + 1;
        strVal02 = IntToStr(n);

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //�₢���������s
        //�\�[�g���� ,�����\����A�g���[No
        sBuf = "SELECT *  ";
        sBuf += "FROM KD81 ";
        sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof && Form1->Query1->Bof )
          return -1;
        else
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
*  update        :                                                     *
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

     //�R���~�Ή� 2002/11/02 E.Takase
     //����(�O�`)���@�P�A�����i�O�`�j���@�Q
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

     //�����
     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD51Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD51Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }

     //�o�^��
     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD51Data[iRec].ADDYMD = " ";
          KD51Data[iRec].SOKUTEI_NB_CUR = 0;
     }else {
           KD51Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD51Data[iRec].ADDYMD ) ){
             KD51Data[iRec].SOKUTEI_NB_CUR = 0 ;
          }else{
             KD51Data[iRec].SOKUTEI_NB_CUR = KD51Data[iRec].SOKUTEI_NM ;
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
*  update        :                                                     *
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
      KD51Data[i].KEIJYO_KBN = 0;     //��̔�d �`��敪
      KD51Data[i].SOKUTEI_NM = 0;    //��̔�d �����
      memset(KD51Data[i].SOKUTEI_S,(int)NULL, sizeof(double) * 100); ;  //�������@
      memset(KD51Data[i].SOKUTEI_H,(int)NULL, sizeof(double) * 100); ;  //�����@
      //�R���~�Ή� 2002/11/02 E.Takase
      memset(KD51Data[i].SOKUTEI_N,(int)NULL, sizeof(double) * 100); ;  //�������@
      KD51Data[i].ADDYMD = '\0';      //�o�^��
      KD51Data[i].SOKUTEI_NB_CUR = 0;
   }
}

/***********************************************************************
*  function name : void CopyKD51to81(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.05 �R���~�Ή� E.Takase                      *
*  contents      : ��̔�d�ް�̧�ق̌����A���� KD�W�P�փR�s�[����     *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void CopyKD51to81(void)
{
  int i, j;

  for( int i=0; i<30; i++){

      if( KD51Data[i].SOKUTE_KBN == 1 && KD51Data[i].SOKUTEI_NB_CUR ){

           // �`��敪�S�̏ꍇ
           if( KD51Data[i].KEIJYO_KBN == 4 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD81Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD81Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
           // �`��敪�T�̏ꍇ
          }else if( KD51Data[i].KEIJYO_KBN == 5 ){
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD81Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_N[j] ;
               }
               KD81Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          // �`��敪�P�A�Q�A�R�̏ꍇ
          }else{
               for( j=0; j< KD51Data[i].SOKUTEI_NM ; j++ ){
                  KD81Data[i].SOKUTEI_S[j] = KD51Data[i].SOKUTEI_S[j] ;
                  KD81Data[i].SOKUTEI_H[j] = KD51Data[i].SOKUTEI_H[j] ;
               }
               KD81Data[i].SOKUTEI_NS_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
               KD81Data[i].SOKUTEI_NH_CUR = KD51Data[i].SOKUTEI_NB_CUR ;
          }


     }
   }
}



/***********************************************************************
*  function name : void Kd83W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd83W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd83W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD83W");

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