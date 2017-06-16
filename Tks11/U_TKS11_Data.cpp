/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�P�j                  *
*  file   name   : U_TKS11_Data.cpp                                    *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�v��  �����f�[�^�A�N�Z�X�֐�            *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ���[�N�ϐ�

// �֐��̐錾
void KD11Format(void);
void SetTable11(void);
int  Kd12_Serch02( AnsiString , int , int, int );
void Kd12_Update01( int );
void Kd12_Update02( AnsiString , int, int, int );
void Kd12_Insert01( AnsiString , int ,int, int );
void SetTable13W(int);

/***********************************************************************
*  function name : int  Kd11_Serch01(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�ް�̧�ق��猟���\����A�ڰNo�𒊏o     *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int Kd11_Serch01(void)
{

    //�u���V�����@�ް�̧�ق���}�X�^�f�[�^�𒊏o
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD11.KENSA_YMD, KD11.TOLEY_NO ";
    sBuf += "FROM KD11 ";
	sBuf += "WHERE KD11.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // �H��敪�ǉ�
    sBuf += "ORDER BY KD11.KENSA_YMD desc, KD11.TOLEY_NO";

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
*  function name : void Kd11_Serch02(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2001.05.21(SQL�� �C��)                              *
*  contents      : �u���V�����@�ް�̧�ق����ް��𒊏o  KD11            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd11_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD11Data�\���̕ϐ��̏�����(�u�����v���݂��������ꍇ)
        if( !Save_Click) KD11Format();

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
	    sBuf += "FROM KD11 ";
	    sBuf += "WHERE  KD11.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD11.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND KD11.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ� 
	    //2001.05.21 �C�� sBuf += "ORDER BY KD11.KENSA_YMD, KD11.TOLEY_NO, KD11.SAMPLE_P";
	    sBuf += "ORDER BY KD11.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD11�Ƀf�[�^������܂���");
          return -1;
        }else {

           // �u�ۑ��v���݂������Ď����ڰNO����������ꍇ
           if( Save_Click ){
               // �ڰNO�̐ݒ�
               Form1->edttlno->Text = strVal02 ;

               // KD11Data�\���̕ϐ��̏�����
               KD11Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable11();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD11Data[i].SOKUTE_KBN  && KD11Data[i].SAMPLE_P != -1 ) {
             if( KD11Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD11Data[i].DTKSHIN == KD11Data[j].DTKSHIN)
                        KD11Data[j].LINK = KD11Data[i].SAMPLE_P ;
                }
             }
          }
       }

       //�v�����m���Q�̏ꍇ �u���V�����@�i��O�j̧�ق�ǂݍ���
       for( i=0; i<30; i++ )
       {
          if( KD11Data[i].SOKUTEI_NM > 2 && KD11Data[i].SOKUTE_KBN == 1 &&
              KD11Data[i].SOKUTEI_NM_CUR  ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD11Data[i].SAMPLE_P );

              //�₢���������s
              //�\�[�g���� �A�����\����A�g���[No�A�T���v���|�W�V����
	        sBuf = "SELECT ";
	        sBuf += "KD12.SOKUTEICHI, KD12.SOKUTEI_NO ";
	        sBuf += "FROM KD12 ";
	        sBuf += "WHERE  KD12.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD12.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD12.SAMPLE_P = '" + strVal03 + "' ";
            sBuf += "AND  KD12.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // �H��敪�ǉ� 
	        //2001.05.21 �C�� sBuf += "ORDER BY KD12.KENSA_YMD, KD12.TOLEY_NO, KD12.SAMPLE_P, KD12.SOKUTEI_NO";
	        sBuf += "ORDER BY KD12.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->RecordCount <= 0 ) {
                    //ShowMessage("KD12�Ƀf�[�^������܂���");
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
                                   KD11Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD11Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable11(int )                               *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : �u���V�����@�ް���ۑ�����\����KD11Data���ް���ݒ�*
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable11()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD11Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD11Data[iRec].KENSA_YMD = " ";
     }else {
          KD11Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD11Data[iRec].TOLEY_NO = 0;
     }else {
          KD11Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD11Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD11Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 &&KD11Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD11Data[iRec].DTKSCOD = " ";
     }else {
          KD11Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD11Data[iRec].DTKSHIN = " ";
     }else {
          KD11Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD11Data[iRec].LOTNO = " ";
     }else {
          KD11Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD11Data[iRec].HINBAN = " ";
     }else {
          KD11Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD11Data[iRec].ZISCOD = " ";
     }else {
          KD11Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD11Data[iRec].ZISNAM = " ";
     }else {
          KD11Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["BURASI_MIN"].IsNull()) {
          KD11Data[iRec].BURASI_MIN = 0.0;
     }else {
          KD11Data[iRec].BURASI_MIN =  Form1->Query1->FieldValues["BURASI_MIN"];
     }

     if ( Form1->Query1->FieldValues["BURASI_MAX"].IsNull()) {
          KD11Data[iRec].BURASI_MAX = 0.0;
     }else {
          KD11Data[iRec].BURASI_MAX =  Form1->Query1->FieldValues["BURASI_MAX"];
     }

      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD11Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD11Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD11Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD11Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD11Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD11Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }

    if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD11Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD11Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD11Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD11Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD11Data[iRec].ADDYMD = " ";
          KD11Data[iRec].SOKUTEI_NM_CUR = 0;
     }else {
          KD11Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD11Data[iRec].ADDYMD )){
             KD11Data[iRec].SOKUTEI_NM_CUR = 0 ;
          }else{
             KD11Data[iRec].SOKUTEI_NM_CUR = KD11Data[iRec].SOKUTEI_SU ;
          }

     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD11Data[iRec].ADDTIM = " ";
     }else {
          KD11Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD11Data[iRec].UPDYMD = " ";
     }else {
          KD11Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD11Data[iRec].UPDCHR = 0;
     }else {
          KD11Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD11Data[iRec].UPDCNT = 0;
     }else {
          KD11Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }
     //���l 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD11Data[iRec].MEMO =  " ";
     }else {
          KD11Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
 }

/***********************************************************************
*  function name : void KD11Format(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : �u���V�����@�ް���ۑ�����\����KD11Data��������KD11*
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD11Format(void)
{
   for( int i=0; i<30; i++){
      KD11Data[i].KENSA_YMD =  '\0';  //�����\���
      KD11Data[i].TOLEY_NO = 0 ;      //�ڰNO
      KD11Data[i].SAMPLE_P = -1 ;     //������߼޼��NO
      KD11Data[i].SOKUTE_KBN = 0;     //����敪
      KD11Data[i].DTKSCOD = '\0';     //���Ӑ�R�[�h
      KD11Data[i].DTKSHIN = '\0';     //���Ӑ�i��
      KD11Data[i].LOTNO = '\0';       //���b�gNO
      KD11Data[i].HINBAN = '\0';      //���Еi��
      KD11Data[i].ZISCOD = '\0';      //�ގ��R�[�h
      KD11Data[i].ZISNAM = '\0';      //�ގ���
      KD11Data[i].BURASI_MIN = 0.0;   //�u���V�����@ �K�i��
      KD11Data[i].BURASI_MAX = 0.0;   //�u���V�����@ �K�i��
      KD11Data[i].SOKUTEI_NM = 0;     //�u���V�����@�v����
      KD11Data[i].SOKUTEI_SU = 0;     //�u���V�����@�v����
      KD11Data[i].SOKUTE_AVE = 0.0;   //���蕽�ϒl
      memset(KD11Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //����l
      KD11Data[i].ADDYMD = '\0';      //�o�^��
      KD11Data[i].ADDTIM = '\0';      //�o�^����
      KD11Data[i].UPDYMD = '\0';      //�ύX��
      KD11Data[i].UPDTIM = '\0';      //�ύX����
      KD11Data[i].UPDCHR = 0;         //�X�V��
      KD11Data[i].UPDCNT = 0;         //�X�V��
      KD11Data[i].LINK = 0;
      KD11Data[i].SOKUTEI_NM_CUR = 0;
      KD11Data[i].MEMO = '\0';         //���l 2002/11/07 E.Takase
   }
}


/***********************************************************************
*  function name : void Kd11_Update01(void)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 ���l�ް��ǉ� E.Takase                    *
*  contents      : �v���ް����u���V�����@�v���ް�̧�ق֏�������  KD11  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd11_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err = 0;

    // ��ʂ̓����ް����擾
    // �v���ް�1
    if( DataNoIdx == 1 )
        KD11Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;

       // �v���ް�2
    else if ( DataNoIdx == 2 )
        KD11Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;

    // �v���ް� n?
    else {
        n = pEdt4[SamplePositionIdx-1]->Value;
        if( n >=3 && n<= KD11Data[SamplePositionIdx-1].SOKUTEI_NM )
            KD11Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = pEdt3[SamplePositionIdx-1]->Value;
    }

	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD11Data[i].SOKUTE_KBN == 1 && KD11Data[i].SAMPLE_P != -1 &&
			KD11Data[i].SOKUTEI_NM_CUR != 0 ){

			//�S���Һ���
			KD11Data[i].UPDCHR = USER_COD ;

			// ����\���
			// KD11Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// �ڰNO
			// KD11Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//����l���ϒl�̎Z�o
			double a = 0.0;
			for(j=0; j< KD11Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD11Data[i].SOKUTEICHI[j] ;

			if( KD11Data[i].SOKUTEI_NM_CUR )
				KD11Data[i].SOKUTE_AVE = a/KD11Data[i].SOKUTEI_NM_CUR ;

			// �o�^���A�o�^����
			if( IsNullSpace( KD11Data[i].ADDYMD )){
				KD11Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD11Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD11Data[i].UPDCNT = 0;

			}else{
				// �ύX���A�ύX����
				KD11Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD11Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//�X�V��
				KD11Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD11 set SOKUTEI_SU=%d ,SOKUTEI_1=%6.3f , SOKUTEI_2=%6.3f, SOKUTE_AVE=%9.6f,",
								KD11Data[i].SOKUTEI_NM_CUR,
								KD11Data[i].SOKUTEICHI[0],
								KD11Data[i].SOKUTEICHI[1],
								KD11Data[i].SOKUTE_AVE);


			str = str_c ;
			str_c[0] = NULL ;

			//���l�ǉ� 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD11Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD11Data[i].ADDYMD.c_str(),
									KD11Data[i].ADDTIM.c_str(),
									KD11Data[i].UPDCHR,
									KD11Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD11Data[i].UPDYMD.c_str(),
									KD11Data[i].UPDTIM.c_str(),
									KD11Data[i].UPDCHR,
									KD11Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD11Data[i].KENSA_YMD.c_str(),
			//					KD11Data[i].TOLEY_NO ,
			//					KD11Data[i].SAMPLE_P );
                        // 20160630_�H��敪�ǉ�
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD11Data[i].KENSA_YMD.c_str(),
						KD11Data[i].TOLEY_NO ,
						KD11Data[i].SAMPLE_P ,
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
				StatBarClear( e.Message )  ;
				Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
				Update_err = 1;
			}
			catch(Exception& e)
			{
				// ShowMessage(e.Message);
				Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			//�u���V�����@�v���i��O�j̧�ق̍X�V
			if( KD11Data[i].SOKUTEI_NM > 2 ){
				Kd12_Update01(i) ;
			}
		} else {
			//2002/11/22 E.Takase
			//���l�̂ݓ����Ă����ꍇ�A���l�̂ݕۑ�
			if(!(IsNullSpace( KD11Data[i].ADDYMD )) || !(IsNullSpace(KD11Data[i].MEMO))){
				// �o�^���A�o�^����
				if( IsNullSpace( KD11Data[i].ADDYMD )){
					KD11Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD11Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD11Data[i].UPDCNT = 0;

				}else{
					// �ύX���A�ύX����
					KD11Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD11Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//�X�V��
					KD11Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD11 set MEMO='%s' , ", KD11Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD11Data[i].ADDYMD.c_str(),
										KD11Data[i].ADDTIM.c_str(),
										KD11Data[i].UPDCHR,
										KD11Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD11Data[i].UPDYMD.c_str(),
										KD11Data[i].UPDTIM.c_str(),
										KD11Data[i].UPDCHR,
										KD11Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD11Data[i].KENSA_YMD.c_str(),
				//					KD11Data[i].TOLEY_NO ,
				//					KD11Data[i].SAMPLE_P );
                                // 20160630_�H��敪�ǉ�
				wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
									KD11Data[i].KENSA_YMD.c_str(),
									KD11Data[i].TOLEY_NO ,
									KD11Data[i].SAMPLE_P ,
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
*  function name : void Kd12_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          ��  ��  |   iRec     | ���Ļ�����߼޼��NO-1    |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �v���ް����u���V�����@�v��(��O�j̧�ق֏������� KD12*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD11Data[iRec].SOKUTEI_NM; i++ ){

         // KD12�֒ǉ����郌�R�[�h���݂��邩�ǂ����̃`�F�b�N
         iRtn = Kd12_Serch02( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // �Y�����R�[�h�����݂��Ȃ��ꍇ�ǉ��iInsert�j
         if( iRtn <= 0 ) {
           Kd12_Insert01( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // �Y�����R�[�h�����݂���ꍇ�X�V�iUpdate�j

           Kd12_Update02( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
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
*  create        : 1999.10                                             *
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
*  function name : int Kd12_Serch02(AnsiString sYmd, int iTlno,        *
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
*  create        : 1999.10                                             *
*  update        : 2001.05.21(SQL�� �C��)                              *
*  contents      : �w�肵��ں��ނ��u���V�����@��O̧�قɂ��邩�ǂ���   *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd12_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD12 ";
        sBuf += "WHERE  KD12.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD12.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD12.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD12.SOKUTEI_NO = '" + strVal04 + "' ";
		sBuf += "AND  KD12.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_�H��敪�ǉ�
        //2001.05.21 �C�� sBuf += "ORDER BY KD12.KENSA_YMD, KD12.TOLEY_NO, KD12.SAMPLE_P, KD12.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof )
          return 0 ;

    return  1 ;
}


/***********************************************************************
*  function name : void Kd12_Update02(AnsiString sYmd, int iTlno,      *
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
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�ް�̧��KD12�֎w�肵��ں��ނ��X�V����                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD12 set SOKUTEICHI=%.3f", KD11Data[iSp-1].SOKUTEICHI[iDtNo-1]);

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
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
         // ShowMessage(e.Message);
         Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
 }

/***********************************************************************
*  function name : void Kd12_Insert01(AnsiString sYmd, int iTlno,      *
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
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@KD12�֎w�肵��ں��ނ�ǉ�����           *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //���₢������  Update
    sprintf(str_c, " insert into  KD12(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEICHI, KOJOKBN)");	// 20160630_�H��敪�ǉ�

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo , KD11Data[iSp-1].SOKUTEICHI[iDtNo-1], iKojoKbn);      // 20160630_�H��敪�ǉ�

     str += str_c ;
     Form1->Query1->SQL->Add(str);
     if(Form1->Database1->InTransaction == false ){
        Form1->Database1->StartTransaction();
     }

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
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // ���s�����ꍇ�A�ύX��������
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
 }


/***********************************************************************
*  function name : void Kd13W_Create01(AnsiString sYmd, int iTlno,     *
*                                                       int iNum)      *
*                  +--------------------------------------+            *
*          ��  ��  | sYmd       |  �����\���             |            *
*                  | iTlno      |  �ڰNO                  |            *
*                  | iNum       |  ���b�g��               |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |             | ���R�[�h��             |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������̂��߂� KD13Wܰ��e�[�u�����쐬����         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
long  Kd13W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD13WFormat(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �u���V�����@�v������ܰ��ް��\����KD13data��������   *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void KD13WFormat(void)
{
   for( int i=0; i<30; i++){
       KD13WData[i].DTKSHIN = '\0';              //���Ӑ�i��

       for( int j=0; j< 50 ; j++ ){
            KD13WData[i].LOTNO[j]  = 0.0 ;       //���b�gNO
            KD13WData[i].BURASI_MIN[j] = 0.0  ;  //�u���V�����@ �K�i��
            KD13WData[i].BURASI_MAX[j] = 0.0;    //�u���V�����@ �K�i��
            KD13WData[i].SOKUTE_AVE[j] = 0.0;    //�v�����ϒl
            KD13WData[i].SOKUTEI_NM[j] = 0;      //ۯ�NO���̌v���ް���
            for( int k=0; k<100; k++ )
               KD13WData[i].SOKUTEI[j][k] = 0.0;  //����l
       }

       KD13WData[i].LOTCNT = -1;                  //�i�Ԗ���ۯ�NO��
    }
}

/***********************************************************************
*  function name : int  Kd13W_Search01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : KD13Wܰ�ð��ق���u���V�����@�v�������f�[�^���oKD13W*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  Kd13W_Serch01( void)
{
       int i,j;
       AnsiString strVal01;

        // KD13Data�\���̕ϐ��̏�����
        KD13WFormat();

         // �������f�[�^��ǂݍ���
        for( i=0; i<30; i++ ){

             // ���肵�Ȃ��ꍇ�A�������Ȃ�
             if( KD11Data[i].SOKUTE_KBN == 0 && KD11Data[i].SAMPLE_P == -1 ) continue ;
              if( KD11Data[i].LINK ) continue ;

             //�����߼޼��NO�̕i�ԂŌ���
             strVal01 = KD11Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //�₢���������s
              //�\�[�g���� ,�����\����A�g���[No
	          sBuf = "SELECT *  ";
	          sBuf += "FROM KD13W ";
	          sBuf += "WHERE  KD13W.DTKSHIN = '" + strVal01 + "' ";
                  //20161128 Y.Onishi
              //�H��敪�Ɋւ�炸���藚�����擾����
              //sBuf += "AND KD13W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_�H��敪�ǉ�
              sBuf += "ORDER BY ROWNO desc" ;

              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();

              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD11�Ƀf�[�^������܂���");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable13W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD13WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD13WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD13WData[i].SOKUTEI_NM[j]; k++)
                dAve += KD13WData[i].SOKUTEI[j][k] ;

               if( KD13WData[i].SOKUTEI_NM[j] !=0 )
                  KD13WData[i].SOKUTE_AVE[j] = dAve/KD13WData[i].SOKUTEI_NM[j] ;
             }

       }
    return 1;
}

/***********************************************************************
*  function name : void SetTable13W(int )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ܰ��ް�KD13WData���ް���ݒ�                        *
*  written by    : �� ���N (NKK unics Corp.)                           *
***********************************************************************/
void SetTable13W(int iSp)
{

     int iLotno = KD13WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD13WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD13WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD13WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }
            if ( Form1->Query1->FieldValues["BURASI_MIN"].IsNull()) {
               KD13WData[iSp].BURASI_MIN[iLotno] = 0.0;
            }else {
                KD13WData[iSp].BURASI_MIN[iLotno] = Form1->Query1->FieldValues["BURASI_MIN"];
            }
            if ( Form1->Query1->FieldValues["BURASI_MAX"].IsNull()) {
               KD13WData[iSp].BURASI_MAX[iLotno] = 0.0;
            }else {
               KD13WData[iSp].BURASI_MAX[iLotno] = Form1->Query1->FieldValues["BURASI_MAX"];
            }


     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD13WData[iSp].DTKSHIN = " ";
     }else {
            KD13WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // ����l
     int iDtNo = KD13WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD13WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD13WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD13WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD13WData[iSp].LOTCNT = iLotno ;

 }

 /***********************************************************************
*  function name : void CopyKD11Data(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD11Data��KD11W�փR�s�[����                         *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD11Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD11Data[i].SOKUTE_KBN == 0 || KD11Data[i].SAMPLE_P == -1 ) continue ;

        // ���ĕi�Ԃ��n�߂Čv���ꍇ
        if(  KD11Data[i].LINK == 0 ){
            iLinkSp = KD11Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD11Data[i].LINK;
        }

        if( KD13WData[iLinkSp-1].LOTCNT == -1 ){

           //ۯ�NO�J���^�[
           KD13WData[iLinkSp-1].LOTCNT = 1;

           //���Ӑ�i��
           KD13WData[iLinkSp-1].DTKSHIN =  KD11Data[i].DTKSHIN;

           //���b�gNO
           KD13WData[iLinkSp-1].LOTNO[0]  = KD11Data[i].LOTNO ;

           // �K�i��
           KD13WData[iLinkSp-1].BURASI_MIN[0] = KD11Data[i].BURASI_MIN;
           // �K�i��
           KD13WData[iLinkSp-1].BURASI_MAX[0] = KD11Data[i].BURASI_MAX;

           KD13WData[iLinkSp-1].SOKUTEI_NM[0] = KD11Data[i].SOKUTEI_NM_CUR;

           if( KD11Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //����l
           double a=0.0;
           for( k=0; k < KD11Data[i].SOKUTEI_NM; k++ ) {
                  KD13WData[iLinkSp-1].SOKUTEI[0][k] = KD11Data[i].SOKUTEICHI[k];
                  a += KD13WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //���ϒl
           if( KD11Data[i].SOKUTEI_NM != 0 )
             KD13WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD11Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // �����ް����ɶ��ĕi�Ԃ��������Ă���ꍇ
     }else{

          // �����ް��̌��ֶ���ۯ�NO���ް���ǉ�
          //ۯ�NO�J���^�[
          KD13WData[iLinkSp-1].LOTCNT += 1;

          n = KD13WData[iLinkSp-1].LOTCNT ;

          //���b�gNO
          KD13WData[iLinkSp-1].LOTNO[n-1]  = KD11Data[i].LOTNO ;

          //���[�h������ �K�i��
          KD13WData[iLinkSp-1].BURASI_MIN[n-1] = KD11Data[i].BURASI_MIN;

          //���[�h������ �K�i��
          KD13WData[iLinkSp-1].BURASI_MAX[n-1] = KD11Data[i].BURASI_MAX;

          KD13WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD11Data[i].SOKUTEI_NM_CUR;

          if( KD11Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //����l
          double a=0.0;
          for( k=0; k < KD11Data[i].SOKUTEI_NM; k++ ) {
               KD13WData[iLinkSp-1].SOKUTEI[n-1][k] = KD11Data[i].SOKUTEICHI[k];
               a += KD13WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD13WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD11Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd13w(void)                                 *
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
void  AddKd13W(void)
{
   int i,iLinkSp;

   //�����ް�̧�ق̃`�F�b�N

   if( KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ���ĕi�Ԃ��n�߂Čv���ꍇ
   if(  KD11Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD11Data[SamplePositionIdx-1].LINK;
   }

   //�����ް����ɶ���ۯ�No��INDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //�v�������ް��̍X�V
   //���b�gNO
    KD13WData[iLinkSp-1].LOTNO[iRtn] = KD11Data[SamplePositionIdx-1].LOTNO;

   //���[�h������ �K�i��
    KD13WData[iLinkSp-1].BURASI_MIN[iRtn]= KD11Data[SamplePositionIdx-1].BURASI_MIN;

    //���[�h������ �K�i��
    KD13WData[iLinkSp-1].BURASI_MAX[iRtn] = KD11Data[SamplePositionIdx-1].BURASI_MAX;

    KD13WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //����l
    for( i=0; i < KD13WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD13WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD11Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD11Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD13WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}
/***********************************************************************
*  function name : void Kd03W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd03W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd03W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD03W");

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



/***********************************************************************
*  function name : void Kd03W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          ��  ��  | ����       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  ����      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd13W�̃f�[�^���폜����                             *
*  written by    : ���� �b��(NKK unics Corp.)                           *
***********************************************************************/
void  Kd13W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD13W");

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
