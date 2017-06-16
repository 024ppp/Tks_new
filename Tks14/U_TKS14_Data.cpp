/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�S�j                  *
*  file   name   : U_TKS14_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ذ�ސ��������x���菈���f�[�^�A�N�Z�X�֐�            *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ���[�N�ϐ�

// �֐��̐錾
void KD41Format(void);
void SetTable41(void);
int  Kd42_Serch02( AnsiString , int , int, int );
void Kd42_Update01( int );
void Kd42_Update02( AnsiString , int, int, int );
void Kd42_Insert01( AnsiString , int ,int, int );
void SetTable43W(int);

/***********************************************************************
*  function name : int  Kd41_Serch01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x�ް�̧�ق��猟���\����A�ڰNo�𒊏o *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int Kd41_Serch01(void)
{

    //���[�h���������x�ް�̧�ق���}�X�^�f�[�^�𒊏o
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD41.KENSA_YMD, KD41.TOLEY_NO ";
    sBuf += "FROM KD41 ";
	sBuf += "WHERE KD41.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
    sBuf += "ORDER BY KD41.KENSA_YMD desc, KD41.TOLEY_NO";

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

   return 1 ;
 }


/***********************************************************************
*  function name : void Kd41_Serch02(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL�� �C��)                              *
*  contents      : ���[�h���������x�ް�̧�ق����ް��𒊏o  KD41        *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd41_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

       // KD41Data�\���̕ϐ��̏�����(�u�����v���݂��������ꍇ)
       if( !Save_Click) KD41Format();

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
	    sBuf += "FROM KD41 ";
	    sBuf += "WHERE  KD41.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD41.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND KD41.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	    //2001.05.21 �C�� sBuf += "ORDER BY KD41.KENSA_YMD, KD41.TOLEY_NO, KD41.SAMPLE_P";
	    sBuf += "ORDER BY KD41.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD41�Ƀf�[�^������܂���");
          return -1;
        }else {

          // �u�ۑ��v���݂������Ď����ڰNO����������ꍇ
          if( Save_Click )
          {
               // �ڰNO�̐ݒ�
               Form1->edttlno->Text = strVal02 ;

               // KD41Data�\���̕ϐ��̏�����
                KD41Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable41();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD41Data[i].SOKUTE_KBN  && KD41Data[i].SAMPLE_P != -1 ) {
             if( KD41Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD41Data[i].DTKSHIN == KD41Data[j].DTKSHIN)
                        KD41Data[j].LINK = KD41Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //�v�����m���Q�̏ꍇ ���[�h���������@����i��O�j̧�ق�ǂݍ���
       for( i=0; i<30; i++ )
       {
          if( KD41Data[i].SOKUTEI_NM > 2 && KD41Data[i].SOKUTE_KBN == 1 &&
              KD41Data[i].SOKUTEI_NM_CUR ) {
              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD41Data[i].SAMPLE_P );

              //�₢���������s
              //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����
	        sBuf = "SELECT ";
	        sBuf += "KD42.SOKUTEICHI, KD42.SOKUTEI_NO ";
	        sBuf += "FROM KD42 ";
	        sBuf += "WHERE  KD42.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD42.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD42.SAMPLE_P = '" + strVal03 + "' ";
            sBuf += "AND  KD42.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ�
	        //2001.05.21 �C�� sBuf += "ORDER BY KD42.KENSA_YMD, KD42.TOLEY_NO, KD42.SAMPLE_P, KD42.SOKUTEI_NO";
	        sBuf += "ORDER BY KD42.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD42�Ƀf�[�^������܂���");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {

                             if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             if ( Form1->Query1->FieldValues["SOKUTEICHI"].IsNull()) {
                                   KD41Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD41Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable41(int )                               *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : KD41Data�\���̂��ް���ݒ�                          *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable41()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD41Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD41Data[iRec].KENSA_YMD = " ";
     }else {
          KD41Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD41Data[iRec].TOLEY_NO = 0;
     }else {
          KD41Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD41Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD41Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 &&KD41Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD41Data[iRec].DTKSCOD = " ";
     }else {
          KD41Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD41Data[iRec].DTKSHIN = " ";
     }else {
          KD41Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD41Data[iRec].LOTNO = " ";
     }else {
          KD41Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD41Data[iRec].HINBAN = " ";
     }else {
          KD41Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD41Data[iRec].ZISCOD = " ";
     }else {
          KD41Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD41Data[iRec].ZISNAM = " ";
     }else {
          KD41Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_MIN"].IsNull()) {
          KD41Data[iRec].LD_HP_MIN = 0.0;
     }else {
          KD41Data[iRec].LD_HP_MIN =  Form1->Query1->FieldValues["LD_HP_MIN"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_SPD"].IsNull()) {
          KD41Data[iRec].LD_HP_SPD = 0;
     }else {
          KD41Data[iRec].LD_HP_SPD =  Form1->Query1->FieldValues["LD_HP_SPD"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_TAN"].IsNull()) {
          KD41Data[iRec].LD_HP_TAN = 0;
     }else {
          KD41Data[iRec].LD_HP_TAN =  Form1->Query1->FieldValues["LD_HP_TAN"];
     }

      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD41Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD41Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD41Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD41Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD41Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD41Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD41Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD41Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD41Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD41Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD41Data[iRec].ADDYMD = " ";
          KD41Data[iRec].SOKUTEI_NM_CUR = 0;
     }else {
          KD41Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD41Data[iRec].ADDYMD )){
             KD41Data[iRec].SOKUTEI_NM_CUR = 0 ;
          }else{
             KD41Data[iRec].SOKUTEI_NM_CUR = KD41Data[iRec].SOKUTEI_SU ;
          }
     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD41Data[iRec].ADDTIM = " ";
     }else {
          KD41Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD41Data[iRec].UPDYMD = " ";
     }else {
          KD41Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD41Data[iRec].UPDCHR = 0;
     }else {
          KD41Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD41Data[iRec].UPDCNT = 0;
     }else {
          KD41Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }
     //���l 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD41Data[iRec].MEMO =  " ";
     }else {
          KD41Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
 }

/***********************************************************************
*  function name : void KD41Format(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x�f�[�^�\����KD41Data��������  KD41  *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD41Format(void)
{
   for( int i=0; i<30; i++){
      KD41Data[i].KENSA_YMD =  '\0';  //�����\���
      KD41Data[i].TOLEY_NO = 0 ;      //�ڰNO
      KD41Data[i].SAMPLE_P = -1 ;     //������߼޼��NO
      KD41Data[i].SOKUTE_KBN = 0;     //����敪
      KD41Data[i].DTKSCOD = '\0';     //���Ӑ�R�[�h
      KD41Data[i].DTKSHIN = '\0';     //���Ӑ�i��
      KD41Data[i].LOTNO = '\0';       //���b�gNO
      KD41Data[i].HINBAN = '\0';      //���Еi��
      KD41Data[i].ZISCOD = '\0';      //�ގ��R�[�h
      KD41Data[i].ZISNAM = '\0';      //�ގ���
      KD41Data[i].LD_HP_MIN = 0.0;    //���[�h���������x �K�i��
      KD41Data[i].LD_HP_SPD = 0;      //���[�h���������x �v�����x
      KD41Data[i].LD_HP_TAN = 0;      //���[�h���������x �P��
      KD41Data[i].SOKUTEI_NM = 0;     //���[�h���������x�����
      KD41Data[i].SOKUTEI_SU = 0;     //���[�h���������x�����
      KD41Data[i].SOKUTE_AVE = 0.0;   //���蕽�ϒl
      memset(KD41Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //����l
      KD41Data[i].ADDYMD = '\0';      //�o�^��
      KD41Data[i].ADDTIM = '\0';      //�o�^����
      KD41Data[i].UPDYMD = '\0';      //�ύX��
      KD41Data[i].UPDTIM = '\0';      //�ύX����
      KD41Data[i].UPDCHR = 0;         //�X�V��
      KD41Data[i].UPDCNT = 0;         //�X�V��
      KD41Data[i].LINK = 0;
      KD41Data[i].SOKUTEI_NM_CUR = 0;
      KD41Data[i].MEMO = '\0';         //���l 2002/11/07 E.Takase
   }
}


/***********************************************************************
*  function name : void Kd41_Update01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v���ް������[�h���������x�ް�̧�ق֏�������  KD41  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd41_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // ��ʂ̓����ް����擾
    if( DataNoIdx == 1 ){
               // �v���ް�1
             KD41Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;
    }else if( DataNoIdx == 1 ){

             // �v���ް�2
             KD41Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;

    }else {
             // �v���ް� n?
             if( KD41Data[SamplePositionIdx-1].SOKUTEI_NM > 2){
                 n = pEdt4[SamplePositionIdx-1]->Value;
                 if( n >=3 && n<= KD41Data[SamplePositionIdx-1].SOKUTEI_NM )
                    KD41Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = pEdt3[SamplePositionIdx-1]->Value;
             }
    }

	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD41Data[i].SOKUTE_KBN == 1 && KD41Data[i].SAMPLE_P != -1 &&
			KD41Data[i].SOKUTEI_NM_CUR != 0 ){

		//�S���Һ���
		KD41Data[i].UPDCHR = USER_COD ;

		// ����\���
		//KD41Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

		// �ڰNO
		//KD41Data[i].TOLEY_NO =  Form1->edttlno->Value ;

		//����l���ϒl�̎Z�o
		double a = 0.0;
		for(j=0; j< KD41Data[i].SOKUTEI_NM_CUR; j++ )
			a += KD41Data[i].SOKUTEICHI[j] ;

		if( KD41Data[i].SOKUTEI_NM_CUR )
			KD41Data[i].SOKUTE_AVE = a/KD41Data[i].SOKUTEI_NM_CUR ;

			// �o�^���A�o�^����
			if( IsNullSpace( KD41Data[i].ADDYMD )){
				KD41Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD41Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD41Data[i].UPDCNT = 0;

			}else{
				// �ύX���A�ύX����
				KD41Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD41Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD41Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD41 set SOKUTEI_SU=%d , SOKUTEI_1=%6.1f , SOKUTEI_2=%6.1f, SOKUTE_AVE=%9.4f,",
								KD41Data[i].SOKUTEI_NM_CUR,
								KD41Data[i].SOKUTEICHI[0],
								KD41Data[i].SOKUTEICHI[1],
								KD41Data[i].SOKUTE_AVE);


			str = str_c ;
			str_c[0] = NULL ;

			//���l�ǉ� 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD41Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD41Data[i].ADDYMD.c_str(),
									KD41Data[i].ADDTIM.c_str(),
									KD41Data[i].UPDCHR,
									KD41Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD41Data[i].UPDYMD.c_str(),
									KD41Data[i].UPDTIM.c_str(),
									KD41Data[i].UPDCHR,
									KD41Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD41Data[i].KENSA_YMD.c_str(),
			//					KD41Data[i].TOLEY_NO ,
			//					KD41Data[i].SAMPLE_P );
                        // 20160630_�H��敪�ǉ�
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD41Data[i].KENSA_YMD.c_str(),
						KD41Data[i].TOLEY_NO ,
						KD41Data[i].SAMPLE_P ,
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

			//���[�h���������x����i��O�j̧�ق̍X�V
			if( KD41Data[i].SOKUTEI_NM > 2 ){
				Kd42_Update01(i) ;
			}
		} else {
			//���l�̂ݓ����Ă����ꍇ�A���l�̂ݕۑ�
			if(!(IsNullSpace( KD41Data[i].ADDYMD )) || !(IsNullSpace(KD41Data[i].MEMO))){
				// �o�^���A�o�^����
				if( IsNullSpace( KD41Data[i].ADDYMD )){
					KD41Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD41Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD41Data[i].UPDCNT = 0;

				}else{
					// �ύX���A�ύX����
					KD41Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD41Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD41Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD41 set MEMO='%s' , ", KD41Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD41Data[i].ADDYMD.c_str(),
										KD41Data[i].ADDTIM.c_str(),
										KD41Data[i].UPDCHR,
										KD41Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD41Data[i].UPDYMD.c_str(),
										KD41Data[i].UPDTIM.c_str(),
										KD41Data[i].UPDCHR,
										KD41Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD41Data[i].KENSA_YMD.c_str(),
				//					KD41Data[i].TOLEY_NO ,
				//					KD41Data[i].SAMPLE_P );
                                // 20160630_�H��敪�ǉ�
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD41Data[i].KENSA_YMD.c_str(),
						KD41Data[i].TOLEY_NO ,
						KD41Data[i].SAMPLE_P ,
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
*  function name : void Kd42_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   iRec     | ���Ļ�����߼޼��NO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v���ް������[�h���������x(��O�j̧�ق֏������� KD42*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD41Data[iRec].SOKUTEI_NM; i++ ){

         // KD42�֒ǉ����郌�R�[�h���݂��邩�ǂ����̃`�F�b�N
         iRtn = Kd42_Serch02( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // �Y�����R�[�h�����݂��Ȃ��ꍇ�ǉ��iInsert�j
         if( iRtn <= 0 ) {
                Kd42_Insert01( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // �Y�����R�[�h�����݂���ꍇ�X�V�iUpdate�j
                Kd42_Update02( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
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
*  function name : int Kd42_Serch02(AnsiString sYmd, int iTlno,        *
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
*  contents      : �w�肵��ں��ނ�ذ�ސ��������x��O̧�قɂ��邩�ǂ��� *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd42_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD42 ";
        sBuf += "WHERE  KD42.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD42.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD42.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD42.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD42.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_�H��敪�ǉ�
        //2001.05.21 �C�� sBuf += "ORDER BY KD42.KENSA_YMD, KD42.TOLEY_NO, KD42.SAMPLE_P, KD42.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof )
          return 0 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd42_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD42�֎w�肵��ں��ނ��X�V����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD42 set SOKUTEICHI=%.1f", KD41Data[iSp-1].SOKUTEICHI[iDtNo-1]);

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
*  function name : void Kd42_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD42�֎w�肵��ں��ނ�ǉ�����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD42(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEICHI, KOJOKBN)");	// 20160630_�H��敪�ǉ�

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%.1f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo , KD41Data[iSp-1].SOKUTEICHI[iDtNo-1] , iKojoKbn);      // 20160630_�H��敪�ǉ�

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
*  function name : void Kd43W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : �������̂��߂� KD43Wܰ��e�[�u�����쐬����         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
long  Kd43W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD43WFormat(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���[�h���������x����ܰ��ް��\����KD43data��������   *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD43WFormat(void)
{
   for( int i=0; i<30; i++){
       KD43WData[i].DTKSHIN = '\0';              //���Ӑ�i��

       for( int j=0; j< 50 ; j++ ){
            KD43WData[i].LOTNO[j]  = " " ;       //���b�gNO
            KD43WData[i].LD_HP_MIN[j] = 0.0  ;  //���[�h���������x �K�i��
            KD43WData[i].SOKUTE_AVE[j] = 0.0;
            KD43WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD43WData[i].SOKUTEI[j][k] = 0.0;  //����l
       }

       KD43WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd43W_Search01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD43Wܰ�ð��ق��烊�[�h���������x�����f�[�^���oKD43W*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd43W_Serch01( void)
{
       int i;
       AnsiString strVal01;

        // KD41Data�\���̕ϐ��̏�����
        KD43WFormat();

        // �������f�[�^��ǂݍ���
        for( i=0; i<30; i++ ){

             // ���肵�Ȃ��ꍇ�A�������Ȃ�
             if( KD41Data[i].SOKUTE_KBN == 0 && KD41Data[i].SAMPLE_P == -1 ) continue ;
             if( KD41Data[i].LINK ) continue ;

             //�����߼޼��NO�̕i�ԂŌ���
             strVal01 = KD41Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //�₢���������s
              //�\�[�g���� ,�����\����A�g���[No
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD43W ";
	      sBuf += "WHERE  KD43W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //�H��敪�Ɋւ�炸���藚�����擾����
              //sBuf += "AND KD43W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_�H��敪�ǉ�
              sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD21�Ƀf�[�^������܂���");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable43W(i);
                        Form1->Query1->Next();

                     }

                     //
                    KD43WData[i].LOTCNT +=1  ;
               }


            for( int j=0; j < KD43WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD43WData[i].SOKUTEI_NM[j]; k++)
                dAve += KD43WData[i].SOKUTEI[j][k] ;

               if( KD43WData[i].SOKUTEI_NM[j] !=0 )
                  KD43WData[i].SOKUTE_AVE[j] = dAve/KD43WData[i].SOKUTEI_NM[j] ;
           }


       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable43W(int )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ܰ��ް�KD43WData���ް���ݒ�                        *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable43W(int iSp)
{

     int iLotno = KD43WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD43WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD43WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD43WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["LD_HP_MIN"].IsNull()) {
               KD43WData[iSp].LD_HP_MIN[iLotno] = 0.0;
            }else {
                KD43WData[iSp].LD_HP_MIN[iLotno] = Form1->Query1->FieldValues["LD_HP_MIN"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD43WData[iSp].DTKSHIN = " ";
     }else {
            KD43WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // ����l
     int iDtNo = KD43WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD43WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD43WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD43WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD43WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD41Data(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD41Data��KD41W�փR�s�[����                         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD41Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD41Data[i].SOKUTE_KBN == 0 || KD41Data[i].SAMPLE_P == -1 ) continue ;

        // ���ĕi�Ԃ��n�߂Čv���ꍇ
        if(  KD41Data[i].LINK == 0 ){
            iLinkSp = KD41Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD41Data[i].LINK;
        }

        if( KD43WData[iLinkSp-1].LOTCNT == -1 ){

           //ۯ�NO�J���^�[
           KD43WData[iLinkSp-1].LOTCNT = 1;

           //���Ӑ�i��
           KD43WData[iLinkSp-1].DTKSHIN =  KD41Data[i].DTKSHIN;

           //���b�gNO
           KD43WData[iLinkSp-1].LOTNO[0]  = KD41Data[i].LOTNO ;

           // �K�i��
           KD43WData[iLinkSp-1].LD_HP_MIN[0] = KD41Data[i].LD_HP_MIN;

           KD43WData[iLinkSp-1].SOKUTEI_NM[0] = KD41Data[i].SOKUTEI_NM_CUR;

           if( KD41Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //����l
           double a=0.0;
           for( k=0; k < KD41Data[i].SOKUTEI_NM; k++ ) {
                  KD43WData[iLinkSp-1].SOKUTEI[0][k] = KD41Data[i].SOKUTEICHI[k];
                  a += KD43WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //���ϒl
           if( KD41Data[i].SOKUTEI_NM != 0 )
             KD43WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD41Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // �����ް����ɶ��ĕi�Ԃ��������Ă���ꍇ
     }else{

          // �����ް��̌��ֶ���ۯ�NO���ް���ǉ�
          //ۯ�NO�J���^�[
          KD43WData[iLinkSp-1].LOTCNT += 1;

          n = KD43WData[iLinkSp-1].LOTCNT ;

          //���b�gNO
          KD43WData[iLinkSp-1].LOTNO[n-1]  = KD41Data[i].LOTNO ;

          //���[�h������ �K�i��
          KD43WData[iLinkSp-1].LD_HP_MIN[n-1] = KD41Data[i].LD_HP_MIN;

          KD43WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD41Data[i].SOKUTEI_NM_CUR;

          if( KD41Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //����l
          double a=0.0;
          for( k=0; k < KD41Data[i].SOKUTEI_NM; k++ ) {
               KD43WData[iLinkSp-1].SOKUTEI[n-1][k] = KD41Data[i].SOKUTEICHI[k];
               a += KD43WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD43WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD41Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd43w(void)                                 *
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
void  AddKd43W(void)
{
   int i,iLinkSp;

   //�����ް�̧�ق̃`�F�b�N

   if( KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ���ĕi�Ԃ��n�߂Čv���ꍇ
   if(  KD41Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD41Data[SamplePositionIdx-1].LINK;
   }

   //�����ް����ɶ���ۯ�No��INDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //�v�������ް��̍X�V
   //���b�gNO
    KD43WData[iLinkSp-1].LOTNO[iRtn] = KD41Data[SamplePositionIdx-1].LOTNO;

   //���[�h������ �K�i��
    KD43WData[iLinkSp-1].LD_HP_MIN[iRtn]= KD41Data[SamplePositionIdx-1].LD_HP_MIN;

    KD43WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //����l
    for( i=0; i < KD43WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD43WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD41Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD41Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD43WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}



/***********************************************************************
*  function name : void Kd43W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd43W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd43W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD43W");

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
