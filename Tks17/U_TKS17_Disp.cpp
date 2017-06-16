/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�V�j                  *
*  file   name   : U_TKS1�V_DISP.cpp                                   *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �ŗL��R������GUI�����p�֐�                         *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
int IsKeisokuEnd(void) ;
void EndBeep(int);
int EndBeepFlag = 0;         //  �Ō�̌v���ް����ǂ����̎w���t���O
int EndErrorFlag = 0;        //  �K���l���K�i�����ǂ����̎w���t���O

/***********************************************************************
*  function name : void ToNextData(void )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : F3,�u�����v, Return���������ꍇ���ق����̍��ڂֈړ� *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ToNextData(void)
{
   int irec, n;
   int iFlg;

   EndBeepFlag = 0;

   //  Focus�������\����ɗL�����ꍇ�ڰNO�ɐݒ�
   if(  Form1->edtymd->Focused() ) {
        Form1->edttlno->SetFocus();
        return ;
   }

   //  Focus���ڰNO�ɗL�����ꍇ�ŏ��v���l�ɐݒ�
   if(  Form1->edttlno->Focused()){
          if( HaveSokutei)
            pEdt1[iFirstPosition-1]->SetFocus();

        return ;
   }

    //  F3 Function key ������ ���� ���݂��������ꍇ
    //  �ް�1(����f�[�^���ׁj��Focus������
    if( pEdt1_S[0]->Focused() ||
        pEdt1_S[1]->Focused()   ) {

        pEdt2[SamplePositionIdx-1]->SetFocus();

         // �ް��Z�[�u�t���O�̃N���A
         iSaveFlag = 0;
         return ;
     }

     // �ް��Q��Focus������
     if(pEdt2_S[0]->Focused() ||
        pEdt2_S[1]->Focused()  ) {

        //�v���f�[�^���Q�̏ꍇ
        if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 )
        {
            pEdt3[SamplePositionIdx-1]->SetFocus();

         }else{    //�f�[�^�Q�̏ꍇ

            //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
            irec =0;
            iFlg = 0;
            while( 1 ){
                irec +=1 ;
                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;

                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1){
                    iFlg = 1;
                    break ;
                 }
             }
             if( iFlg == 0 ){

                  EndBeepFlag = 1;

                  //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt2[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     //Form1->BtnF11->SetFocus();
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                     //EndBeep(1);
                     pEdt1[iFirstPosition-1]->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(1);
                  }

                  //if( HaveSokutei)
                  //     pEdt1[iFirstPosition-1]->SetFocus();
             }else{

                //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                pEdt1[SamplePositionIdx+irec-1]->SetFocus();
             }
         }

         // �ް��Z�[�u�t���O�̃N���A
         iSaveFlag = 0;

         return ;
    }

     //�v���f�[�^���Q�̏ꍇ
     if(pEdt3_S[0]->Focused() ||
        pEdt3_S[1]->Focused() ||
        pEdt4_S[0]->Focused() ||
        pEdt4_S[1]->Focused() ||
        pScrl_S[0]->Focused() ||
        pScrl_S[1]->Focused()   ) {

        // checkDTno
        if( CheckDtNo() < 0)  return ;

         // �Y���v���ް����Z�[�u����
         SaveRegaiDt() ;

         // �ް��Z�[�u�t���O��ݒ�
         iSaveFlag = 1;

          //���ăf�[�^NO
          n=pEdt4_S[iKomoku -1]->Value  ;

          // ���ăf�[�^NO �� �v���f�[�^NO�̏ꍇ
          if( n >= KD71Data[SamplePositionIdx-1].SOKUTEI_NM  ){

              //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
              irec =0;
              iFlg =0;
              while( 1 ){
                irec+=1 ;

                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;
                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1)
                {
                    iFlg = 1 ;
                    break ;
                 }
              }

              if( iFlg== 0){
                 EndBeepFlag = 1;

                 //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt3[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                     //EndBeep(1);
                     pEdt1[iFirstPosition-1]->SetFocus();}
                     if ( EndErrorFlag == 0 ) EndBeep(1);

              }else{

                 //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                 pEdt1[SamplePositionIdx+irec-1]->SetFocus();
              }

          }else{

             CheckInKikaku(1);

            //���ė������̍X�V
            ToDrawGraph(SamplePositionIdx, iOption);

             //�f�[�^�̍X�V
             pEdt3[SamplePositionIdx-1]->Text = KD71Data[SamplePositionIdx-1].SOKUTEI_T[n] ;
             pScrl[SamplePositionIdx-1]->Position = n+1 ;
             pEdt4[SamplePositionIdx-1]->Text = IntToStr( n+1) ;

             //���薾��
             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n] );
             }else{
                pEdt3_S[0]->Text ="0.000";
             }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }else{
                     pScrl_S[0]->Position = n+1 ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }

              pScrl_S[1]->Position = n+1 ;
              pEdt4_S[1]->Text = IntToStr(n+1) ;

              pScrl_S[2]->Position = n+1 ;
              pEdt4_S[2]->Text = IntToStr(n+1) ;

              pScrl_S[3]->Position = n+1 ;
              pEdt4_S[3]->Text = IntToStr(n+1);

              DataNoIdx = n+1 ;

              CheckInKikaku(0);

              pEdt3_S[iKomoku-1]->SetFocus();
              pEdt3_S[iKomoku-1]->SelectAll();

           }

        }

       // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;
        CurDataChg = 0;

        return ;
}


/***********************************************************************
*  function name : void ToNextData_AV(void )                           *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : RS232C�����M�����ꍇ���ق����̍��ڂֈړ� �@�@�@�@ *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ToNextData_AV(void)
{
   int irec, n;
   int iFlg;

    EndBeepFlag = 0;

    // �ް�1(����f�[�^���ׁj��Focus������
    if( pEdt1_V[0]->Focused() ){
        pEdt1_V[1]->SetFocus();
         return ;
     }

     if(pEdt1_A[0]->Focused() ){
        pEdt1_A[1]->SetFocus() ;
         return ;
     }

     if( pEdt1_V[1]->Focused() ){
         pEdt2_V[0]->SetFocus();
         return ;
     }

     if(pEdt1_A[1]->Focused() ){
        pEdt2_A[0]->SetFocus();
         return ;
     }

     // �ް��Q��Focus������
     if( pEdt2_V[0]->Focused() ){
         pEdt2_V[1]->SetFocus();
         return ;
     }

     if(pEdt2_A[0]->Focused() ){
        pEdt2_A[1]->SetFocus();
         return ;
     }

     if(pEdt2_V[1]->Focused() ||
        pEdt2_A[1]->Focused()   ) {

        //�v���f�[�^���Q�̏ꍇ
        if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 )
        {
             if(pEdt2_V[1]->Focused()) pEdt3_V[0]->SetFocus()  ;
             if(pEdt2_A[1]->Focused()) pEdt3_A[0]->SetFocus() ;


         }else{    //�f�[�^�Q�̏ꍇ

            //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
            irec =0;
            iFlg = 0;
            while( 1 ){
                irec +=1 ;
                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;

                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1){
                    iFlg = 1;
                    break ;
                 }
             }
             if( iFlg == 0 ){
                  EndBeepFlag = 1;

                 //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt2[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                    // EndBeep(1);
                     FlagAV = 1 ;
                     iKomoku = 3;
                     pEdt1[iFirstPosition-1]->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(1);
                  }
             }else{

                //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                FlagAV = 1 ;
                iKomoku = 3;
                pEdt1[SamplePositionIdx+irec-1]->SetFocus();
             }
         }

         // �ް��Z�[�u�t���O�̃N���A
         iSaveFlag = 0;

         return ;
    }

    //�v���f�[�^���Q�̏ꍇ
    if( pEdt3_V[0]->Focused() ||
        pEdt3_A[0]->Focused() ||
        pScrl_S[2]->Focused() ||
        pEdt4_S[2]->Focused()  ) {

        if(pEdt3_V[0]->Focused() ||
           pScrl_S[2]->Focused() ||
           pEdt4_S[2]->Focused()    ) pEdt3_V[1]->SetFocus()  ;

        if(pEdt3_A[0]->Focused()) pEdt3_A[1]->SetFocus() ;

        return;
    }

     if(pEdt3_V[1]->Focused() ||
        pEdt4_S[3]->Focused() ||
        pScrl_S[3]->Focused() ||
        pEdt3_A[1]->Focused()  ) {
//        pEdt3_A[1]->SetFocus();
//        return;
//     }

//     if( pEdt3_A[1]->Focused() ){

         // �ް��Z�[�u�t���O��ݒ�
         iSaveFlag = 1;

          //���ăf�[�^NO
          n=pEdt4_S[iKomoku -1]->Value  ;

          // ���ăf�[�^NO �� �v���f�[�^NO�̏ꍇ
          if( n >= KD71Data[SamplePositionIdx-1].SOKUTEI_NM  ){

              //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
              irec =0;
              iFlg =0;
              while( 1 ){
                irec+=1 ;

                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;
                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1)
                {
                    iFlg = 1 ;
                    break ;
                 }
              }

              if( iFlg== 0){

                 EndBeepFlag = 1;

                 //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt3[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                     //EndBeep(1);
                     FlagAV = 1 ;
                     iKomoku = 3;
                     pEdt1[iFirstPosition-1]->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(1);
                   }

              }else{

                 //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                 FlagAV = 1 ;
                 iKomoku = 3;

                 pEdt1[SamplePositionIdx+irec-1]->SetFocus();
              }

          }else{

             pEdt3_V[0]->SetFocus();
             pEdt3_V[0]->SelectAll();

             //�f�[�^�̍X�V
             pEdt3[SamplePositionIdx-1]->Text = KD71Data[SamplePositionIdx-1].SOKUTEI_T[n] ;
             pScrl[SamplePositionIdx-1]->Position = n+1 ;
             pEdt4[SamplePositionIdx-1]->Text = IntToStr( n+1) ;

             //���薾��
             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n] );
             }else{
                pEdt3_S[0]->Text ="0.000";
             }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }else{
                     pScrl_S[0]->Position = n+1 ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }

              pScrl_S[1]->Position = n+1 ;
              pEdt4_S[1]->Text = IntToStr(n+1) ;

              pScrl_S[2]->Position = n+1 ;
              pEdt4_S[2]->Text = IntToStr(n+1) ;

              pScrl_S[3]->Position = n+1 ;
              pEdt4_S[3]->Text = IntToStr(n+1);

              DataNoIdx = n+1 ;

              CheckInKikaku(0);
              //CheckInKikaku_1(0);
              CheckInKikaku_3();
              CheckInKikaku_4();   //2002/12/02 E.Takase
            }
         }

       // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;

        return ;
}


/***********************************************************************
*  function name : void ReturnExec(void )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : F2, F3,Return���������ꍇ���ق����̍��ڂֈړ�       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ReturnExec(void)
{
   int irec, n;
   int iFlg;

   EndBeepFlag = 0;

   //  Focus�������\����ɗL�����ꍇ�ڰNO�ɐݒ�
   if(  Form1->edtymd->Focused() ) {
        Form1->edttlno->SetFocus();
        return ;
   }

   //  Focus���ڰNO�ɗL�����ꍇ�ŏ��v���l�ɐݒ�
   if(  Form1->edttlno->Focused()){
          if( HaveSokutei)
            pEdt1[iFirstPosition-1]->SetFocus();

        return ;
   }

    // �ް��PmV/A L  and  mV/A R (����f�[�^���ׁj��Focus������
    if( pEdt1_V[0]->Focused() ){
        pEdt1_A[0]->SetFocus() ;
        return ;
     }

    if( pEdt1_A[0]->Focused() ){
        pEdt1_V[1]->SetFocus() ;
        return ;
    }

    if( pEdt1_V[1]->Focused() ) {
        pEdt1_A[1]->SetFocus() ;
        return ;
    }

    if( pEdt1_A[1]->Focused() ) {
        pEdt2_V[0]->SetFocus() ;
        return ;
    }

    // �ް��Q mV/A L  and  mV/A R ��Focus������
    if( pEdt2_V[0]->Focused() ){
        pEdt2_A[0]->SetFocus() ;
        return ;
     }

    if( pEdt2_A[0]->Focused() ){
        pEdt2_V[1]->SetFocus() ;
        return ;
    }

    if( pEdt2_V[1]->Focused() ) {
        pEdt2_A[1]->SetFocus() ;
        return ;
    }

    if( pEdt2_A[1]->Focused() ) {

        //�v���f�[�^���Q�̏ꍇ
        if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 )
        {
            pEdt3_V[0]->SetFocus() ;

         }else{    //�f�[�^�Q�̏ꍇ

            //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
            irec =0;
            iFlg = 0;
            while( 1 ){
                irec +=1 ;
                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;

                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1){
                    iFlg = 1;
                    break ;
                 }
             }
             if( iFlg == 0 ){
                  EndBeepFlag = 1;

                 //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt2[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                     //EndBeep(1);
                     FlagAV = 1 ;
                    iKomoku = 3;
                    pEdt1[iFirstPosition-1]->SetFocus();
                    if ( EndErrorFlag == 0 ) EndBeep(1);

                  }
             }else{

                //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                FlagAV = 1 ;
                 iKomoku = 3;
                pEdt1[SamplePositionIdx+irec-1]->SetFocus();
             }
         }

         // �ް��Z�[�u�t���O�̃N���A
         iSaveFlag = 0;

         return ;
    }

    //�f�[�^�R�`�@�@�i�v���f�[�^���Q�̏ꍇ�j
    if( pEdt3_V[0]->Focused() ||
        pScrl_S[2]->Focused() ||
        pEdt4_S[2]->Focused()  ){
         pEdt3_A[0]->SetFocus() ;
         return ;
     }

    if( pEdt3_A[0]->Focused() ){
         pEdt3_V[1]->SetFocus() ;
          return ;
    }

    if( pEdt3_V[1]->Focused() ||
        pScrl_S[3]->Focused() ||
        pEdt4_S[3]->Focused()  ) {

        pEdt3_A[1]->SetFocus() ;
        return ;
    }

    if( pEdt3_A[1]->Focused() ) {

         // �ް��Z�[�u�t���O��ݒ�
         iSaveFlag = 1;

          //���ăf�[�^NO
          n=pEdt4_S[iKomoku -1]->Value  ;

          // ���ăf�[�^NO �� �v���f�[�^NO�̏ꍇ
          if( n >= KD71Data[SamplePositionIdx-1].SOKUTEI_NM  ){

              //���̌v���f�[�^��T���A�v�����Ȃ��f�[�^���΂�
              irec =0;
              iFlg =0;
              while( 1 ){
                irec+=1 ;

                if( (SamplePositionIdx-1+irec) == iLastPosition ) break ;
                if( KD71Data[SamplePositionIdx-1+irec].SOKUTE_KBN  == 1)
                {
                    iFlg = 1 ;
                    break ;
                 }
              }

              if( iFlg== 0){
                  EndBeepFlag = 1;

                  //�Ō�̌v���l�֓��������ꍇ�AFocus���u�ۑ��v���݂֐ݒ�
                  pEdt3[SamplePositionIdx-1]->Color = clWindow ;
                  Form1->BtnF11->SetFocus();

                  // �S���ڂ��v�������ꍇ
                  if( IsKeisokuEnd() ){
                     //EndBeep(2);
                     Form1->BtnF11->SetFocus();
                     if ( EndErrorFlag == 0 ) EndBeep(2);

                  // �S���ڂ��v�����Ă��Ȃ��ꍇ
                  }else{
                    if( HaveSokutei) {
                     //  EndBeep(1);
                       FlagAV = 1 ;
                       iKomoku = 3;
                       pEdt1[iFirstPosition-1]->SetFocus();
                       if ( EndErrorFlag == 0 ) EndBeep(1);
                     }
                  }
              }else{

                 //�t�H�[�J�X�����̃f�[�^�փZ�b�g
                 FlagAV = 1;
                 iKomoku = 3 ;
                 pEdt1[SamplePositionIdx+irec-1]->SetFocus();
              }

          }else{

             pEdt3_V[0]->SetFocus();
             pEdt3_V[0]->SelectAll();

            //���ė������̍X�V
            //ToDrawGraph(SamplePositionIdx, iOption);

            //�f�[�^�̍X�V
             pEdt3[SamplePositionIdx-1]->Text = KD71Data[SamplePositionIdx-1].SOKUTEI_T[n] ;
             pScrl[SamplePositionIdx-1]->Position = n+1 ;
             pEdt4[SamplePositionIdx-1]->Text = IntToStr( n+1) ;

             //���薾��
            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }else{
                     pScrl_S[0]->Position = n+1 ;
                     pEdt4_S[0]->Text = IntToStr(n+1) ;
              }

              pScrl_S[1]->Position = n+1 ;
              pEdt4_S[1]->Text = IntToStr(n+1) ;

              pScrl_S[2]->Position = n+1 ;
              pEdt4_S[2]->Text = IntToStr(n+1) ;

              pScrl_S[3]->Position = n+1 ;
              pEdt4_S[3]->Text = IntToStr(n+1);

              DataNoIdx = n+1;

              CheckInKikaku(0);
             // CheckInKikaku_1(0);
              CheckInKikaku_3();
              CheckInKikaku_4();   //2002/12/02 E.Takase

             // ToDrawGraph(SamplePositionIdx, iOption);

             //  pEdt3_V[0]->SetFocus();
               pEdt3_V[0]->SelectAll();

           }
        }

       // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;

        return ;

}

/***********************************************************************
*  function name : void ToPreData(void)                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : F2,�u�O���v���������ꍇ�J�[�\����O�̍��ڂֈړ�     *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ToPreData()
{
int irec;
int iFlg, n;

   //  Focus���v���\����ɂ���ꍇ
   if(  Form1->edtymd->Focused()){
         return ;
   }

   //  Focus���ڰNO�ɗL�����ꍇ�ŏ��v���l�ɐݒ�
   if(  Form1->edttlno->Focused()){
         Form1->edtymd->SetFocus();
        return ;
   }

     //  Focus��PUSH���݂ɂ���ꍇ�Ō��߼޼��NO�ɐݒ�
    if( Form1->BtnF01->Focused() ||
        Form1->BtnF02->Focused() ||
        Form1->BtnF03->Focused() ||
        Form1->BtnF05->Focused() ||
        Form1->BtnF07->Focused() ||
        Form1->BtnF10->Focused() ||
        Form1->BtnF11->Focused() ||
        Form1->BtnF12->Focused() ){

        if( !HaveSokutei ) {
          Form1->edttlno->SetFocus() ;
          return;
         }

        if( KD71Data[iLastPosition-1].SOKUTEI_NM > 2 )
            pEdt3[iLastPosition-1]->SetFocus();
        else
            pEdt2[iLastPosition-1]->SetFocus();
        return ;
   }

   // �ް�2��Focus������
    if( pEdt2_S[0]->Focused() ||
        pEdt2_S[1]->Focused()   ) {

         pEdt1[SamplePositionIdx-1]->SetFocus();

         // �ް��Z�[�u�t���O�̃N���A
         iSaveFlag = 0;

         return ;
    }

    // �ް�1��Focus������
    if( pEdt1_S[0]->Focused() ||
        pEdt1_S[1]->Focused()   ) {

         // �ް��Z�[�u�t���O��ݒ�
        iSaveFlag = 1;

        // �O�̃f�[�^��T���ɍs���A�v�����Ȃ��f�[�^���΂�
        irec =0;
        iFlg = 0;
        while( 1 ){
              irec +=1 ;

              if( SamplePositionIdx == iFirstPosition ) break ;

              if( KD71Data[SamplePositionIdx-1-irec].SOKUTE_KBN  == 1) {
               iFlg = 1;
                break ;}
        }

        if( iFlg == 0 ){

              //�Ő擪�̌v���l�̏ꍇ
              pEdt1[SamplePositionIdx-1]->Color = clWindow ;
              Form1->edttlno->SetFocus();

         }else{
              // �v���f�[�^�� ���Q�̏ꍇ
              if( KD71Data[SamplePositionIdx-irec-1].SOKUTEI_NM > 2 ){

                 //�v���f�[�^NO�i�Ō�̃f�[�^�j
                 n= KD71Data[SamplePositionIdx-irec-1].SOKUTEI_NM ;

                 pEdt3[SamplePositionIdx-irec-1]->SetFocus();


              }else{
                   // �f�[�^NO �����Q�̏ꍇ
                   pEdt2[SamplePositionIdx-irec-1]->SetFocus();
              }
        }

        // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;
        return ;
    }


    // �ް�3��Focus������
     if(pEdt3_S[0]->Focused() ||
        pEdt3_S[1]->Focused() ||
        pEdt4_S[0]->Focused() ||
        pEdt4_S[1]->Focused() ||
        pScrl_S[0]->Focused() ||
        pScrl_S[1]->Focused()   ) {

         if( CheckDtNo() < 0)  return ;

         // �Y���v���ް����Z�[�u����
         SaveRegaiDt() ;

         // �ް��Z�[�u�t���O��ݒ�
         iSaveFlag = 1;

          //���ăf�[�^NO
          n = pEdt4_S[iKomoku-1]->Value  ;
          if( n <= 3){

                //��O�̌v���l�փJ�[�\����ݒ�
                pEdt2[SamplePositionIdx-1]->SetFocus();

           }else{
                 CheckInKikaku(1);

                 //�������̍X�V
                 ToDrawGraph(SamplePositionIdx, iOption);

                 // �f�[�^�̍X�V
                 pEdt3[SamplePositionIdx-1]->Text = KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1-1] ;
                 pScrl[SamplePositionIdx-1]->Position = n-1 ;
                 pEdt4[SamplePositionIdx-1]->Text = IntToStr( n-1) ;

                 //���薾��
                 if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                     pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1-1] );
                  }else{
                  pEdt3_S[0]->Text ="0.000";
                 }
                 pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1-1] );

                 pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1-1] );
                 pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1-1] );
                 pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1-1] );
                 pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1-1] );

                 if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n-1) ;
                  }else{
                     pScrl_S[0]->Position = n-1 ;
                     pEdt4_S[0]->Text = IntToStr(n-1) ;
                  }

                  pScrl_S[1]->Position = n-1 ;
                  pEdt4_S[1]->Text = IntToStr(n-1) ;

                  pScrl_S[2]->Position = n-1 ;
                  pEdt4_S[2]->Text = IntToStr(n-1) ;

                  pScrl_S[3]->Position = n-1 ;
                  pEdt4_S[3]->Text = IntToStr(n-1);

                  DataNoIdx = n-1;
                  CheckInKikaku(0);

                  pEdt3_S[iKomoku-1]->SetFocus();
                  pEdt3_S[iKomoku-1]->SelectAll();

           }

        }

       // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;
        CurDataChg=0;

        return ;


}

/***********************************************************************
*  function name : void ToPreData_AV(void)                             *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : F2���������ꍇ(mV�^AL mV/A R))�J�[�\����O�̍��ڂֈړ�     *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ToPreData_AV()
{
int irec;
int iFlg, n;

   //  Focus���v���\����ɂ���ꍇ
   if(  Form1->edtymd->Focused()){
         return ;
   }

   //  Focus���ڰNO�ɗL�����ꍇ�ŏ��v���l�ɐݒ�
   if(  Form1->edttlno->Focused()){
         Form1->edtymd->SetFocus();
        return ;
   }

    //  Focus��PUSH���݂ɂ���ꍇ�Ō��߼޼��NO�ɐݒ�
    if( Form1->BtnF01->Focused() ||
        Form1->BtnF02->Focused() ||
        Form1->BtnF03->Focused() ||
        Form1->BtnF05->Focused() ||
        Form1->BtnF07->Focused() ||
        Form1->BtnF10->Focused() ||
        Form1->BtnF11->Focused() ||
        Form1->BtnF12->Focused() ){

        if( !HaveSokutei ) {
          Form1->edttlno->SetFocus() ;
          return;
         }

        if( KD71Data[iLastPosition-1].SOKUTEI_NM > 2 )
            pEdt3[iLastPosition-1]->SetFocus();
        else
            pEdt2[iLastPosition-1]->SetFocus();
        return ;
   }

    // �ް�2��Focus������
    if( pEdt2_A[1]->Focused() ) {
        pEdt2_V[1]->SetFocus();
        return ;
    }
    if( pEdt2_V[1]->Focused() ) {
        pEdt2_A[0]->SetFocus();
        return ;
    }
    if( pEdt2_A[0]->Focused() ) {
        pEdt2_V[0]->SetFocus();
        return ;
    }
    if( pEdt2_V[0]->Focused() ) {
        pEdt1_A[1]->SetFocus();
        return ;
    }

    // �ް�1��Focus������
    if( pEdt1_A[1]->Focused() ) {
        pEdt1_V[1]->SetFocus();
        return ;
    }
    if( pEdt1_V[1]->Focused() ) {
        pEdt1_A[0]->SetFocus();
        return ;
    }
    if( pEdt1_A[0]->Focused() ) {
        pEdt1_V[0]->SetFocus();
        return ;
    }

    if( pEdt1_V[0]->Focused() ) {

         // �ް��Z�[�u�t���O��ݒ�
        iSaveFlag = 1;

        // �O�̃f�[�^��T���ɍs���A�v�����Ȃ��f�[�^���΂�
        irec =0;
        iFlg = 0;
        while( 1 ){
              irec +=1 ;

              if( SamplePositionIdx == iFirstPosition ) break ;

              if( KD71Data[SamplePositionIdx-1-irec].SOKUTE_KBN  == 1) {
               iFlg = 1;
                break ;}
        }

        if( iFlg == 0 ){

              //�Ő擪�̌v���l�̏ꍇ
              pEdt1[SamplePositionIdx-1]->Color = clWindow ;
              Form1->edttlno->SetFocus();

         }else{
              // �v���f�[�^�� ���Q�̏ꍇ
              if( KD71Data[SamplePositionIdx-irec-1].SOKUTEI_NM > 2 ){

                 //�v���f�[�^NO�i�Ō�̃f�[�^�j
                 n= KD71Data[SamplePositionIdx-irec-1].SOKUTEI_NM ;
                 FlagAV = 2;
                 iKomoku = 4;
                 pEdt3[SamplePositionIdx-irec-1]->SetFocus();

              }else{
                   // �f�[�^NO �����Q�̏ꍇ
                   FlagAV = 2;
                   iKomoku = 4;
                   pEdt2[SamplePositionIdx-irec-1]->SetFocus();
              }
        }

        // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;
        return ;
    }


    // �ް�3��Focus������
    if( pEdt3_A[1]->Focused() ||
        pEdt4_S[3]->Focused() ||
        pScrl_S[3]->Focused()   ) {

        pEdt3_V[1]->SetFocus();
        return ;
    }
    if( pEdt3_V[1]->Focused() ) {
        pEdt3_A[0]->SetFocus();
        return ;
    }
    if( pEdt3_A[0]->Focused() ||
        pEdt4_S[2]->Focused() ||
        pScrl_S[2]->Focused()   ) {

        pEdt3_V[0]->SetFocus();
        return ;
    }

    if( pEdt3_V[0]->Focused() ) {

         // �ް��Z�[�u�t���O��ݒ�
         iSaveFlag = 1;

          //���ăf�[�^NO
          n = pEdt4_S[iKomoku-1]->Value  ;
          if( n <= 3){

                //��O�̌v���l�փJ�[�\����ݒ�
                pEdt2_A[1]->SetFocus();
           }else{

               //  if( FlagAV == 1 ){
               //      pEdt3_V[iKomoku-3]->SetFocus();
               //      pEdt3_V[iKomoku-3]->SelectAll();
               //   }else{
                     pEdt3_A[1]->SetFocus();
                     pEdt3_A[1]->SelectAll();
                //  }

                 // �f�[�^�̍X�V
                 pEdt3[SamplePositionIdx-1]->Text = KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1-1] ;
                 pScrl[SamplePositionIdx-1]->Position = n-1 ;
                 pEdt4[SamplePositionIdx-1]->Text = IntToStr( n-1) ;

                 //���薾��
                 if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                     pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1-1] );
                  }else{
                  pEdt3_S[0]->Text ="0.000";
                 }
                 pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1-1] );

                 pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1-1] );
                 pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1-1] );
                 pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1-1] );
                 pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1-1] );

                 if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n-1) ;
                  }else{
                     pScrl_S[0]->Position = n-1 ;
                     pEdt4_S[0]->Text = IntToStr(n-1) ;
                  }

                  pScrl_S[1]->Position = n-1 ;
                  pEdt4_S[1]->Text = IntToStr(n-1) ;

                  pScrl_S[2]->Position = n-1 ;
                  pEdt4_S[2]->Text = IntToStr(n-1) ;

                  pScrl_S[3]->Position = n-1 ;
                  pEdt4_S[3]->Text = IntToStr(n-1);

                  DataNoIdx = n-1;
                  CheckInKikaku(0);
                  // CheckInKikaku_1(0);
                  CheckInKikaku_3();
                  CheckInKikaku_4();   //2002/12/02 E.Takase

           }

        }

       // �ް��Z�[�u�t���O�̃N���A
        iSaveFlag = 0;

        return ;


}
/***********************************************************************
*  function name : void CorseBack(void)                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �}�E�X�ŉ�ʉ��u�O���v�u�����v�uOption�v�������ꍇ  *
*                : ���ق�O�̂���ꏊ�֖߂�                            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void CurseBack(void)
{

   CurBackFlg = 1;

   //�t�H�[�J�X����ʏ�̌����������ɂ���ꍇ
   if( CurField == 1 ){
      if( ymdtl_flg == 1 )  Form1->edtymd->SetFocus() ;
      if( ymdtl_flg == 2 )  Form1->edttlno->SetFocus() ;
      CurBackFlg = 0;
      return ;
   }

   //�t�H�[�J�X���v���f�[�^���ɂ���ꍇ
   if( CurField == 2) {
      if( DataNoIdx == 1 ){
          if( iKomoku == 1 || iKomoku == 2 )
              pEdt1_S[iKomoku-1]->SetFocus();
          else {
             if( FlagAV==1  ){
                 pEdt1_V[iKomoku-3]->SetFocus();

             }
            if( FlagAV==2 ) {
                pEdt1_A[iKomoku-3]->SetFocus();

            }
          }

      }else if( DataNoIdx == 2 ){
          if(  iKomoku == 1 || iKomoku == 2 ){
               pEdt2_S[iKomoku-1]->SetFocus();
          }else {
             if( FlagAV == 1  ){
                 pEdt2_V[iKomoku-3]->SetFocus();

             }
            if( FlagAV == 2 ) {
                pEdt2_A[iKomoku-3]->SetFocus();

            }
          }
      }else{
         if( iKomoku == 1 || iKomoku == 2 )  {
             pEdt3_S[iKomoku-1]->SetFocus();
         }else{
             if( FlagAV== 1  ){
                 pEdt3_V[iKomoku-3]->SetFocus();

             }
            if( FlagAV==2 ) {
                pEdt3_A[iKomoku-3]->SetFocus();

            }
         }
      }
   }

   CurBackFlg = 0;

   return ;
}

/***********************************************************************
*  function name : void CheckInKikaku(int iBeep )                      *
*                  +--------------------------------------+            *
*          ��  ��  |   iBeep    |0: NoBeep 1: Beep        |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���Čv���l(��R�j���K�i�͈͈̔ȓ����ǂ����̃`�F�b�N *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void CheckInKikaku(int iBeep)
{
	double  dBuf1;
	int     errflg=0;

	//�F�ABeep���I�t����ꍇ
	//if( iOption == 3  ||  iKskStart == 0 )  return ;
	if( iKskStart == 0 ) return ;

	if( iOption == 3 ){
		EndErrorFlag = 0;

		//RS232C�ǂݍ��݃t���O 1 �Ȃ� RSInput.wav��炷
		//�Ō�̌v���l�֓��������ꍇ RSInput.wav��炳�Ȃ�
		if (RSInputFlag == 1 && EndBeepFlag == 0 ) {
			Form1->MdPlayer->FileName = "RSInput.wav";
			Form1->MdPlayer->Open();
			Form1->MdPlayer->Play();
		}
		RSInputFlag = 0;

		return ;
	}

	// �K�i�ɂ���ăf�[�^���`�F�b�N����
	if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
									SamplePositionIdx <= iLastPosition ) ){

		//�S���ڂ��v�����Ȃ��ꍇ�A�K�i���������Ȃ�
		if( CheckKomoku(SamplePositionIdx, DataNoIdx) ) {
			// �v���d���l�̋K�i�G���[�`�F�b�N
			errflg = CheckInKikaku_1(0 ) ;
			errflg += CheckInKikaku_2(0 ) ;

			// �d���G���[�̏ꍇBeep()��炷
			if( errflg ) {
				Beep();
			//RS232C�ǂݍ��݃t���O 1 �Ȃ� RSInput.wav��炷
			//�Ō�̌v���l�֓��������ꍇ RSInput.wav��炳�Ȃ�
			} else if ( RSInputFlag == 1 && EndBeepFlag == 0 ) {
				Form1->MdPlayer->FileName = "RSInput.wav";
				Form1->MdPlayer->Open();
				Form1->MdPlayer->Play();
			}
			RSInputFlag = 0;
			return ;
		}

		// �ŗL��R���K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
		if( DataNoIdx == 1 ){
			dBuf1 = pEdt1[SamplePositionIdx-1]->Value;
		}else if(DataNoIdx == 2 ){
			dBuf1 = pEdt2[SamplePositionIdx-1]->Value;
		}else {
			dBuf1 = pEdt3[SamplePositionIdx-1]->Value ;
		}

		// �v���d���A�d���l�̋K�i�`�F�b�N
		//�R���~�Ή� 2002/11/06 E.Takase
		if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){
			
			//��ɃO���[�\��
			if( DataNoIdx == 1 ){
				pEdt1[SamplePositionIdx-1]->Font->Color = clGray;
			}else if( DataNoIdx == 2 ){
				pEdt2[SamplePositionIdx-1]->Font->Color = clGray;
			}else {
				pEdt3[SamplePositionIdx-1]->Font->Color = clGray;
            }
			/*
			if( ((dBuf1 > KD71Data[SamplePositionIdx-1].KOYU_MAX  ||
					dBuf1 < KD71Data[SamplePositionIdx-1].KOYU_MIN )  ) &&
					DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR  ){

				if( DataNoIdx == 1 ){
					pEdt1[SamplePositionIdx-1]->Font->Color = clRed;
					errflg = 1;
				}else if( DataNoIdx == 2 ){
					pEdt2[SamplePositionIdx-1]->Font->Color = clRed;
					errflg = 2 ;
				}else {
					pEdt3[SamplePositionIdx-1]->Font->Color = clRed;
					pEdt4[SamplePositionIdx-1]->Font->Color = clPurple;
					errflg = 3 ;
				}
			}else{
				if( DataNoIdx == 1 ){
					pEdt1[SamplePositionIdx-1]->Font->Color = clBlack;
				}else if( DataNoIdx == 2 ){
					pEdt2[SamplePositionIdx-1]->Font->Color = clBlack;
				}else {
					pEdt3[SamplePositionIdx-1]->Font->Color = clBlack;
			}
			*/
		} else {
			if( ((dBuf1 > KD71Data[SamplePositionIdx-1].KOYU_MAX  ||
					dBuf1 < KD71Data[SamplePositionIdx-1].KOYU_MIN ) ||
					( KD71Data[SamplePositionIdx-1].SOKUTEA_L[DataNoIdx-1] >  KD71Data[SamplePositionIdx-1].D_Kikaku_Max    ||
					  KD71Data[SamplePositionIdx-1].SOKUTEA_L[DataNoIdx-1] <  KD71Data[SamplePositionIdx-1].D_Kikaku_Min  ) ||
					( KD71Data[SamplePositionIdx-1].SOKUTEA_R[DataNoIdx-1] >  KD71Data[SamplePositionIdx-1].D_Kikaku_Max    ||
					  KD71Data[SamplePositionIdx-1].SOKUTEA_R[DataNoIdx-1] <  KD71Data[SamplePositionIdx-1].D_Kikaku_Min   )  ) &&
					  DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR  ){

				if( DataNoIdx == 1 ){
					pEdt1[SamplePositionIdx-1]->Font->Color = clRed;
					errflg = 1;
				}else if( DataNoIdx == 2 ){
					pEdt2[SamplePositionIdx-1]->Font->Color = clRed;
					errflg = 2 ;
				}else {
					pEdt3[SamplePositionIdx-1]->Font->Color = clRed;
					pEdt4[SamplePositionIdx-1]->Font->Color = clPurple;
					errflg = 3 ;
				}
			}else{
				if( DataNoIdx == 1 ){
					pEdt1[SamplePositionIdx-1]->Font->Color = clBlack;
				}else if( DataNoIdx == 2 ){
					pEdt2[SamplePositionIdx-1]->Font->Color = clBlack;
				}else {
					pEdt3[SamplePositionIdx-1]->Font->Color = clBlack;	
				}
			
			}
		}
		//�s���i�f�[�^���L��Ή���炷
		if( errflg && iBeep ) {
			Beep();
			EndErrorFlag = 1;

		}else{

			EndErrorFlag = 0;

			//RS232C�ǂݍ��݃t���O 1 �Ȃ� RSInput.wav��炷
			//�Ō�̌v���l�֓��������ꍇ RSInput.wav��炳�Ȃ�
			if ( RSInputFlag == 1 && EndBeepFlag == 0 ) {
				Form1->MdPlayer->FileName = "RSInput.wav";
				Form1->MdPlayer->Open();
				Form1->MdPlayer->Play();
			}
		}
		RSInputFlag = 0;

		//�R�`�X�X�܂ł��ް��ɕs���i�ް����Ȃ���΁ApEdt4[i]�𔒂ɂ���
		if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 && DataNoIdx >=3  && errflg != 3){
			int k=0;
			for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){

				//�R���~�Ή� 2002/11/06 E.Takase
				if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 5 ){
					// �v���d���A�d���l�̋K�i�`�F�b�N
					if( (( KD71Data[SamplePositionIdx-1].SOKUTEI_T[i] > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
							  KD71Data[SamplePositionIdx-1].SOKUTEI_T[i] < KD71Data[SamplePositionIdx-1].KOYU_MIN ) ||
							( KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] >  KD71Data[SamplePositionIdx-1].D_Kikaku_Max    ||
							  KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] <  KD71Data[SamplePositionIdx-1].D_Kikaku_Min  ) ||
							( KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] >  KD71Data[SamplePositionIdx-1].D_Kikaku_Max    ||
							  KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] <  KD71Data[SamplePositionIdx-1].D_Kikaku_Min   ) )  &&
							KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
							DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR ){

						k= 1 ;
						break ;
					}
				}
			}

				
			//�R���~�Ή� 2002/11/06 E.Takase
			if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 5 ){
				pEdt4[SamplePositionIdx-1]->Font->Color = clGray;
			} else {
				//��ɃO���[�\��
				// �R�Ԗڂ���̃f�[�^�ɕs���i�ް�������ꍇ
				if( k){
					pEdt4[SamplePositionIdx-1]->Font->Color = clPurple;
					errflg = 3;
				}else{
					pEdt4[SamplePositionIdx-1]->Font->Color = clBlack;
				}
			}
		}
	}
}


/***********************************************************************
*  function name : int  CheckInKikaku_1(int iBeep )                    *
*                  +--------------------------------------+            *
*          ��  ��  |   iBeep    |0: NoBeep 1: Beep        |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002/11/05 �R���~�̏ꍇ�̓`�F�b�N�Ȃ� E.Takase      *
*  contents      : ���Čv���l�i�d��  mV/AL || mV/AR �j�̋K�i�`�F�b�N   *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int CheckInKikaku_1(int iBeep)
{
  double  dBuf1,dBuf2;
  int     errflg = 0;

    // �F�ABeep���I�t����ꍇ
    if( iOption == 3  ||  iKskStart == 0 )  return 0;

    if( iKomoku != 3 && iKomoku != 4 ) return 0;

    //�R���~�̏ꍇ�̓`�F�b�N�Ȃ� 2002/11/05 E.Takase
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) return 0;

    // �K�i�ɂ���ăf�[�^���`�F�b�N����
    if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
                                  SamplePositionIdx <= iLastPosition ) ){
       //�d���̃`�F�b�N
     if( iKomoku == 3 ){

//------
       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       if( DataNoIdx == 1 ){
              dBuf1 = pEdt1_A[0]->Value;
       }else if(DataNoIdx == 2 ){
              dBuf1 = pEdt2_A[0]->Value;
       }else {
              dBuf1 = pEdt3_A[0]->Value;
       }

       if( (dBuf1 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
            dBuf1 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min )&&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR){

         if( DataNoIdx == 1 ){
              pEdt1_A[0]->Font->Color = clRed;
              errflg = 1;
         }else if( DataNoIdx == 2 ){
              pEdt2_A[0]->Font->Color = clRed;
              errflg =2;
         }else {
              pEdt3_A[0]->Font->Color = clRed;
              pEdt4_S[2]->Font->Color = clPurple;
              errflg = 3;
         }
       }else{
           if( DataNoIdx == 1 ){
                pEdt1_A[0]->Font->Color = clBlack;
           }else if( DataNoIdx == 2 ){
                pEdt2_A[0]->Font->Color = clBlack;
           }else {
                pEdt3_A[0]->Font->Color = clBlack;
                pEdt4_S[2]->Font->Color = clBlack;
           }
       }


      //�s���i�f�[�^���L��Ή���炷
      //if( errflg && iBeep ) Beep();
 /******
      //�R�`�X�X�܂ł��ް��ɕs���i�ް����Ȃ���΁AEdtA4�𔒂ɂ���
      if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 && DataNoIdx >=3 && errflg != 3){
          int k=0;
         // for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){
            for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR; i++ ){
              if(( KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
                  KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] < KD71Data[SamplePositionIdx-1].D_Kikaku_Min )
                   &&  KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                   DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR  ){
                   k= 1 ;
                   break ;
              }
         }

         // �R�Ԗڂ���̃f�[�^�ɕs���i�ް�������ꍇ
         if( k){
                 pEdt4_S[2]->Font->Color = clPurple;
                 errflg= 3;
         }else{
                 pEdt4_S[2]->Font->Color = clBlack;
         }
       }
   ******/
//-----
     }else{
//----
       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       if( DataNoIdx == 1 ){
              dBuf2 = pEdt1_A[1]->Value;

       }else if(DataNoIdx == 2 ){
              dBuf2 = pEdt2_A[1]->Value;
       }else {
              dBuf2= pEdt3_A[1]->Value;
       }

       if( (dBuf2 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
            dBuf2 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){

         if( DataNoIdx == 1 ){
              pEdt1_A[1]->Font->Color = clRed;
              errflg = 4;
         }else if( DataNoIdx == 2 ){
              pEdt2_A[1]->Font->Color = clRed;
              errflg =5;
         }else {
              pEdt3_A[1]->Font->Color = clRed;
              pEdt4_S[3]->Font->Color = clPurple;
              errflg = 6;
         }
        }else{
           if( DataNoIdx == 1 ){
                pEdt1_A[1]->Font->Color = clBlack;
           }else if( DataNoIdx == 2 ){
                pEdt2_A[1]->Font->Color = clBlack;
           }else {
                pEdt3_A[1]->Font->Color = clBlack;
                pEdt4_S[3]->Font->Color = clBlack;
           }
        }

       //�s���i�f�[�^���L��Ή���炷
       //if( errflg && iBeep ) Beep();

  /*******
       //�R�`�X�X�܂ł��ް��ɕs���i�ް����Ȃ���΁AEdtA4�𔒂ɂ���
       if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 && DataNoIdx >=3 && errflg != 6){
          int k=0;

          // �v���d���l�̋K�i�`�F�b�N
         // for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){
          for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR; i++ ){
             if(( KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
                  KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] < KD71Data[SamplePositionIdx-1].D_Kikaku_Min ) &&
                  KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                  DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR  ){
                   k= 1 ;
                   break ;

              }
          }

         // �R�Ԗڂ���̃f�[�^�ɕs���i�ް�������ꍇ
         if( k){
               pEdt4_S[3]->Font->Color = clPurple;
               errflg= 6;
         }else{
               pEdt4_S[3]->Font->Color = clBlack;
         }
       }

   *****/


     }  // iKomoku ==3 or 4
  }
   return errflg;
}


/***********************************************************************
*  function name : int  CheckInKikaku_2(int iBeep )                    *
*                  +--------------------------------------+            *
*          ��  ��  |   iBeep    |0: NoBeep 1: Beep        |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : ���Čv���l�i�d��  mV/AL || mV/AR �j�̋K�i�`�F�b�N   *
*  written by    : ���� �b��(NKK unics Corp.)                          *
***********************************************************************/
int CheckInKikaku_2(int iBeep)
{
  double  dBuf1,dBuf2;
  int     errflg = 0;

    // �F�ABeep���I�t����ꍇ
    if( iOption == 3  ||  iKskStart == 0 )  return 0;

    if( iKomoku != 3 && iKomoku != 4 ) return 0;

    //�R���~�ȊO�̏ꍇ�̓`�F�b�N�Ȃ�
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 5 ) return 0;

    // �K�i�ɂ���ăf�[�^���`�F�b�N����
    if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
                                  SamplePositionIdx <= iLastPosition ) ){
       //�d���̃`�F�b�N
     if( iKomoku == 3 ){

//------
       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       if( DataNoIdx == 1 ){
              dBuf1 = pEdt1_V[0]->Value;
       }else if(DataNoIdx == 2 ){
              dBuf1 = pEdt2_V[0]->Value;
       }else {
              dBuf1 = pEdt3_V[0]->Value;
       }

       if( (dBuf1 > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
            dBuf1 < KD71Data[SamplePositionIdx-1].KOYU_MIN )&&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR){

         if( DataNoIdx == 1 ){
              pEdt1_V[0]->Font->Color = clRed;
              errflg = 1;
         }else if( DataNoIdx == 2 ){
              pEdt2_V[0]->Font->Color = clRed;
              errflg =2;
         }else {
              pEdt3_V[0]->Font->Color = clRed;
              pEdt4_S[2]->Font->Color = clPurple;
              errflg = 3;
         }
       }else{
           if( DataNoIdx == 1 ){
                pEdt1_V[0]->Font->Color = clBlack;
           }else if( DataNoIdx == 2 ){
                pEdt2_V[0]->Font->Color = clBlack;
           }else {
                pEdt3_V[0]->Font->Color = clBlack;
                pEdt4_S[2]->Font->Color = clBlack;
           }
       }


      //�s���i�f�[�^���L��Ή���炷
      //if( errflg && iBeep ) Beep();
 /******
      //�R�`�X�X�܂ł��ް��ɕs���i�ް����Ȃ���΁AEdtA4�𔒂ɂ���
      if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 && DataNoIdx >=3 && errflg != 3){
          int k=0;
         // for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){
            for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR; i++ ){
              if(( KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
                  KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] < KD71Data[SamplePositionIdx-1].KOYU_MIN )
                   &&  KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                   DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR  ){
                   k= 1 ;
                   break ;
              }
         }

         // �R�Ԗڂ���̃f�[�^�ɕs���i�ް�������ꍇ
         if( k){
                 pEdt4_S[2]->Font->Color = clPurple;
                 errflg= 3;
         }else{
                 pEdt4_S[2]->Font->Color = clBlack;
         }
       }
   ******/
//-----
     }else{
//----
       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       if( DataNoIdx == 1 ){
              dBuf2 = pEdt1_V[1]->Value;

       }else if(DataNoIdx == 2 ){
              dBuf2 = pEdt2_V[1]->Value;
       }else {
              dBuf2= pEdt3_V[1]->Value;
       }

       if( (dBuf2 > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
            dBuf2 < KD71Data[SamplePositionIdx-1].KOYU_MIN) &&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){

         if( DataNoIdx == 1 ){
              pEdt1_V[1]->Font->Color = clRed;
              errflg = 4;
         }else if( DataNoIdx == 2 ){
              pEdt2_V[1]->Font->Color = clRed;
              errflg =5;
         }else {
              pEdt3_V[1]->Font->Color = clRed;
              pEdt4_S[3]->Font->Color = clPurple;
              errflg = 6;
         }
        }else{
           if( DataNoIdx == 1 ){
                pEdt1_V[1]->Font->Color = clBlack;
           }else if( DataNoIdx == 2 ){
                pEdt2_V[1]->Font->Color = clBlack;
           }else {
                pEdt3_V[1]->Font->Color = clBlack;
                pEdt4_S[3]->Font->Color = clBlack;
           }
        }

       //�s���i�f�[�^���L��Ή���炷
       //if( errflg && iBeep ) Beep();

  /*******
       //�R�`�X�X�܂ł��ް��ɕs���i�ް����Ȃ���΁AEdtA4�𔒂ɂ���
       if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2 && DataNoIdx >=3 && errflg != 6){
          int k=0;

          // �v���d���l�̋K�i�`�F�b�N
         // for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){
          for(int  i=2; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR; i++ ){
             if(( KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
                  KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] < KD71Data[SamplePositionIdx-1].KOYU_MIN ) &&
                  KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                  DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR  ){
                   k= 1 ;
                   break ;

              }
          }

         // �R�Ԗڂ���̃f�[�^�ɕs���i�ް�������ꍇ
         if( k){
               pEdt4_S[3]->Font->Color = clPurple;
               errflg= 6;
         }else{
               pEdt4_S[3]->Font->Color = clBlack;
         }
       }

   *****/


     }  // iKomoku ==3 or 4
  }
   return errflg;
}


/***********************************************************************
*  function name : void CheckInKikaku_3( void  )                       *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002/11/05 �R���~�̏ꍇ�̓`�F�b�N�Ȃ� E.Takase      *
*  contents      : ���Čv���l���Q�̏ꍇ,�d��(mV/A L&& mV/A R)�̋K�i����*
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void CheckInKikaku_3(void )
{
  double  dBuf1,dBuf2;

    // �F�ABeep���I�t����ꍇ
    if( iOption == 3  ||  iKskStart == 0 )  return ;

    if( iKomoku != 3 && iKomoku != 4 ) return ;

    //�R���~�̏ꍇ�̓`�F�b�N�Ȃ� 2002/11/05 E.Takase
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) return ;

    // �K�i�ɂ���ăf�[�^���`�F�b�N����
    if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
                                  SamplePositionIdx <= iLastPosition ) ){

       //�d���̃`�F�b�N
       dBuf1 = pEdt3_A[0]->Value;

       if( (dBuf1 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
            dBuf1 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min )&&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR){

              pEdt3_A[0]->Font->Color = clRed;
              pEdt4_S[2]->Font->Color = clPurple;
       }else{
              pEdt3_A[0]->Font->Color = clBlack;
              pEdt4_S[2]->Font->Color = clBlack;
       }

       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       dBuf2= pEdt3_A[1]->Value;

       if( (dBuf2 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
            dBuf2 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){

              pEdt3_A[1]->Font->Color = clRed;
              pEdt4_S[3]->Font->Color = clPurple;
        }else{
              pEdt3_A[1]->Font->Color = clBlack;
              pEdt4_S[3]->Font->Color = clBlack;
        }
  }

}

/***********************************************************************
*  function name : void CheckInKikaku_4( void  )                       *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : ���Čv���l���Q�̏ꍇ,�d��(mV/A L&& mV/A R)�̋K�i����*
*  written by    : ���� �b��(NKK unics Corp.)                          *
***********************************************************************/
void CheckInKikaku_4(void )
{
  double  dBuf1,dBuf2;

    // �F�ABeep���I�t����ꍇ
    if( iOption == 3  ||  iKskStart == 0 )  return ;

    if( iKomoku != 3 && iKomoku != 4 ) return ;

    //�R���~�ȊO�̏ꍇ�̓`�F�b�N�Ȃ�
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 5 ) return ;

    // �K�i�ɂ���ăf�[�^���`�F�b�N����
    if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
                                  SamplePositionIdx <= iLastPosition ) ){

       //�d���̃`�F�b�N
       dBuf1 = pEdt3_V[0]->Value;

       if( (dBuf1 > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
            dBuf1 < KD71Data[SamplePositionIdx-1].KOYU_MIN )&&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR){

              pEdt3_V[0]->Font->Color = clRed;
              pEdt4_S[2]->Font->Color = clPurple;
       }else{
              pEdt3_V[0]->Font->Color = clBlack;
              pEdt4_S[2]->Font->Color = clBlack;
       }

       // �K�i�̍ő�l�A�ŏ��l�𒴂��Ă��邩�ǂ����̃`�F�b�N
       dBuf2= pEdt3_V[1]->Value;

       if( (dBuf2 > KD71Data[SamplePositionIdx-1].KOYU_MAX ||
            dBuf2 < KD71Data[SamplePositionIdx-1].KOYU_MIN) &&
            DataNoIdx <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){

              pEdt3_V[1]->Font->Color = clRed;
              pEdt4_S[3]->Font->Color = clPurple;
        }else{
              pEdt3_V[1]->Font->Color = clBlack;
              pEdt4_S[3]->Font->Color = clBlack;
        }
  }

}

/***********************************************************************
*  function name : void SaveRegaiDt(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �v���f�[�^�f�[�^��ϐ��֕ۑ�                        *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
//---------------------------------------------------------------------------
int  SaveRegaiDt(void )
{
   int n;
   double a, b;

   if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2  &&
       KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&  DataNoIdx >  2 )
   {

       n= pEdt4_S[iKomoku-1]->Value;


       // ����
       if( iKomoku == 1 ) {
            a  = KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1];

            if( fabs( pEdt3_S[iKomoku-1]->Value - a) > 0.0000001  ){

                //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // �v�������f�[�^����݃g�[
               if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < n )
                    KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = n ;

                KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[iKomoku-1]->Value;

                 //�ŗL��R���̌v�Z
                if( KTeikouCal(SamplePositionIdx, n ) ){
                    pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
              //      if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR < n )
                //          KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR = n ;
                }
            }
       //��
       }else if( iKomoku == 2 ){
            a  = KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1];
            if( fabs(pEdt3_S[iKomoku-1]->Value - a) > 0.0000001 ){

                //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // �v�������f�[�^����݃g�[
               if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < n )
                    KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = n ;

                KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[iKomoku-1]->Value;

                //�ŗL��R���̌v�Z
               if( KTeikouCal(SamplePositionIdx, n ) ){
                  // if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR < n )
                  //        KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR = n ;
                  pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
               }
            }
       // mV /A  L
       }else if( iKomoku == 3  ){
            a  = KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1];
            b  = KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1];

            if( fabs(pEdt3_V[0]->Value - a) > 0.000001  || fabs(pEdt3_A[0]->Value - b) > 0.000001){

                //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // �v�������f�[�^����݃g�[
                if( fabs(pEdt3_V[0]->Value -a) > 0.000001 ) {
                    if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR < n )
                         KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR = n ;

                    KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] = pEdt3_V[0]->Value;
                }

                if( fabs(pEdt3_A[0]->Value - b) > 0.000001) {
                   if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR < n  )
                        KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR = n ;
                    KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] = pEdt3_A[0]->Value;
               }

               //�ŗL��R���̌v�Z
               if( KTeikouCal(SamplePositionIdx, n ) ){
                //  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR < n )
                //          KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR = n ;
                pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
               }
            }
       ////  mV/A R
       }else{
            a  = KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1];
            b  = KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] ;

            if( fabs(pEdt3_V[1]->Value - a) > 0.000001 || fabs(pEdt3_A[1]->Value - b) > 0.000001 ){

                //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // �v�������f�[�^����݃g�[
               if(  fabs(pEdt3_V[1]->Value - a) > 0.000001 ){
                  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR < n )
                       KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR = n ;
                  KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] = pEdt3_V[1]->Value;
               }

               if( fabs(pEdt3_A[1]->Value - b) > 0.000001 ){
                  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR < n )
                       KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR = n ;
                  KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] = pEdt3_A[1]->Value;
                }

               //�ŗL��R���̌v�Z
               if( KTeikouCal(SamplePositionIdx, n ) ){
                 // if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR < n )
                 //         KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR = n ;
                  pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
               }

            }
       }

   }
   return 0;
}


//---------------------------------------------------------------------------
/***********************************************************************
*  function name : void DisplayInfo(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   iRec     | ���R�[�h��              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �������ُ���\��                                 *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
//---------------------------------------------------------------------------
void DisplayInfo(void)
{
    int iden=0;

     Form1->Pnl5->Caption = FormatFloat("0", KD71Data[SamplePositionIdx-1].KOYU_MIN) ;
     Form1->Pnl6->Caption = FormatFloat("0", KD71Data[SamplePositionIdx-1].KOYU_MAX) ;

     Form1->Pnl7->Caption = KD71Data[SamplePositionIdx-1].DTKSCOD ;
     Form1->Pnl8->Caption = KD71Data[SamplePositionIdx-1].DTKSHIN ;
     Form1->Pnl9->Caption = KD71Data[SamplePositionIdx-1].LOTNO ;
     Form1->Pnl10->Caption = KD71Data[SamplePositionIdx-1].HINBAN ;
     Form1->Pnl11->Caption = KD71Data[SamplePositionIdx-1].ZISCOD ;
     Form1->Pnl12->Caption = KD71Data[SamplePositionIdx-1].ZISNAM ;

     iden = int( KD71Data[SamplePositionIdx-1].KOYU_DEN );
     if( fabs(KD71Data[SamplePositionIdx-1].KOYU_DEN - iden ) > 0.0 )
         Form1->PnlD->Caption = FormatFloat("#0.0", KD71Data[SamplePositionIdx-1].KOYU_DEN) ;
     else
         Form1->PnlD->Caption = FormatFloat("0", KD71Data[SamplePositionIdx-1].KOYU_DEN) ;


     Form1->Pnl13->Caption = FormatFloat("0", KD71Data[SamplePositionIdx-1].KOYU_PRO) ;
 }

/***********************************************************************
*  function name : void StatBarClear( AnsiString sMsg )                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : // �X�e�[�^�X���b�Z�[�W�̕\��                       *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void StatBarClear( AnsiString sMsg )
{

     // �X�e�[�^�X���b�Z�[�W
     Form1->SBr1->SimpleText =  sMsg;
     Form1->SBr1->Update();
 }

/***********************************************************************
*  function name : int CheckDtNo( void)                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   <0     |   <3 or > 99              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �f�[�^NO�̃`�F�b�N                                  *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  CheckDtNo( void )
{
  int n, iRtn, pos;

   iRtn = 0;

   n = pEdt4_S[iKomoku-1]->Value;

   if( n < 3 || n > KD71Data[SamplePositionIdx-1].SOKUTEI_NM ) {

     //ScrollBar�̏����l�ݒ�
     if( iKomoku == 1 ){
       pos = pScrl_S[0]->Position ;
       pEdt4_S[0]->Text = IntToStr(pos) ;
     }
     else if( iKomoku == 2 ){
       pos = pScrl_S[1]->Position ;
       pEdt4_S[1]->Text = IntToStr(pos) ;
     }
     else if( iKomoku == 3 ){
       pos = pScrl_S[2]->Position ;
       pEdt4_S[2]->Text = IntToStr(pos) ;
     }
     else {
       pos = pScrl_S[3]->Position ;
       pEdt4_S[3]->Text = IntToStr(pos) ;
     }

     iRtn = -1;

   }
   return iRtn ;
}

/***********************************************************************
*  function name : void SaveCtlID(void)                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��ʊe���۰ق�z��ϐ��֕ۑ�����                    *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void SaveCtlID()
{
    // ��ʊe���۰ق�z��ϐ��֕ۑ�����
    pPnlP[0] =  Form1->PnlP1 ;         pEdt1[0] =  Form1->Edt01_1 ;
    pEdt2[0] =  Form1->Edt01_2 ;       pEdt3[0] =  Form1->Edt01_3 ;
    pEdt4[0] =  Form1->Edt01_4 ;       pScrl[0] =  Form1->ScrollBar1 ;
    pPnlN[0] =  Form1->PnlN1 ;
    pPnlP[1] =  Form1->PnlP2 ;         pEdt1[1] =  Form1->Edt02_1 ;
    pEdt2[1] =  Form1->Edt02_2 ;       pEdt3[1] =  Form1->Edt02_3 ;
    pEdt4[1] =  Form1->Edt02_4 ;       pScrl[1] =  Form1->ScrollBar2;
    pPnlN[1] =  Form1->PnlN2 ;
    pPnlP[2] =  Form1->PnlP3 ;         pEdt1[2] =  Form1->Edt03_1 ;
    pEdt2[2] =  Form1->Edt03_2 ;       pEdt3[2] =  Form1->Edt03_3 ;
    pEdt4[2] =  Form1->Edt03_4 ;       pScrl[2] =  Form1->ScrollBar3 ;
    pPnlN[2] =  Form1->PnlN3 ;
    pPnlP[3] =  Form1->PnlP4 ;         pEdt1[3] =  Form1->Edt04_1 ;
    pEdt2[3] =  Form1->Edt04_2 ;       pEdt3[3] =  Form1->Edt04_3 ;
    pEdt4[3] =  Form1->Edt04_4 ;       pScrl[3] =  Form1->ScrollBar4;
    pPnlN[3] =  Form1->PnlN4 ;
    pPnlP[4] =  Form1->PnlP5 ;         pEdt1[4] =  Form1->Edt05_1 ;
    pEdt2[4] =  Form1->Edt05_2 ;       pEdt3[4] =  Form1->Edt05_3 ;
    pEdt4[4] =  Form1->Edt05_4 ;       pScrl[4] =  Form1->ScrollBar5 ;
    pPnlN[4] =  Form1->PnlN5 ;
    pPnlP[5] =  Form1->Pnlp6 ;         pEdt1[5] =  Form1->Edt06_1 ;
    pEdt2[5] =  Form1->Edt06_2 ;       pEdt3[5] =  Form1->Edt06_3 ;
    pEdt4[5] =  Form1->Edt06_4 ;       pScrl[5] =  Form1->ScrollBar6 ;
    pPnlN[5] =  Form1->PnlN6 ;
    pPnlP[6] =  Form1->PnlP7 ;         pEdt1[6] =  Form1->Edt07_1 ;
    pEdt2[6] =  Form1->Edt07_2 ;       pEdt3[6] =  Form1->Edt07_3 ;
    pEdt4[6] =  Form1->Edt07_4 ;       pScrl[6] =  Form1->ScrollBar7 ;
    pPnlN[6] =  Form1->PnlN7 ;
    pPnlP[7] =  Form1->PnlP8 ;         pEdt1[7] =  Form1->Edt08_1 ;
    pEdt2[7] =  Form1->Edt08_2 ;       pEdt3[7] =  Form1->Edt08_3 ;
    pEdt4[7] =  Form1->Edt08_4 ;       pScrl[7] =  Form1->ScrollBar8 ;
    pPnlN[7] =  Form1->PnlN8 ;
    pPnlP[8] =  Form1->PnlP9 ;         pEdt1[8] =  Form1->Edt09_1 ;
    pEdt2[8] =  Form1->Edt09_2 ;       pEdt3[8] =  Form1->Edt09_3 ;
    pEdt4[8] =  Form1->Edt09_4 ;       pScrl[8] =  Form1->ScrollBar9;
    pPnlN[8] =  Form1->PnlN9 ;
    pPnlP[9] =  Form1->PnlP10 ;        pEdt1[9] =  Form1->Edt10_1 ;
    pEdt2[9] =  Form1->Edt10_2 ;       pEdt3[9] =  Form1->Edt10_3 ;
    pEdt4[9] =  Form1->Edt10_4 ;       pScrl[9] =  Form1->ScrollBar10 ;
    pPnlN[9] =  Form1->PnlN10 ;
    pPnlP[10] =  Form1->PnlP11 ;       pEdt1[10] =  Form1->Edt11_1 ;
    pEdt2[10] =  Form1->Edt11_2 ;      pEdt3[10] =  Form1->Edt11_3 ;
    pEdt4[10] =  Form1->Edt11_4 ;      pScrl[10] =  Form1->ScrollBar11 ;
    pPnlN[10] =  Form1->PnlN11 ;
    pPnlP[11] =  Form1->PnlP12 ;       pEdt1[11] =  Form1->Edt12_1 ;
    pEdt2[11] =  Form1->Edt12_2 ;      pEdt3[11] =  Form1->Edt12_3 ;
    pEdt4[11] =  Form1->Edt12_4 ;      pScrl[11] =  Form1->ScrollBar12 ;
    pPnlN[11] =  Form1->PnlN12 ;
    pPnlP[12] =  Form1->PnlP13 ;       pEdt1[12] =  Form1->Edt13_1 ;
    pEdt2[12] =  Form1->Edt13_2 ;      pEdt3[12] =  Form1->Edt13_3 ;
    pEdt4[12] =  Form1->Edt13_4 ;      pScrl[12] =  Form1->ScrollBar13 ;
    pPnlN[12] =  Form1->PnlN13 ;
    pPnlP[13] =  Form1->PnlP14 ;       pEdt1[13] =  Form1->Edt14_1 ;
    pEdt2[13] =  Form1->Edt14_2 ;      pEdt3[13] =  Form1->Edt14_3 ;
    pEdt4[13] =  Form1->Edt14_4 ;      pScrl[13] =  Form1->ScrollBar14 ;
    pPnlN[13] =  Form1->PnlN14 ;
    pPnlP[14] =  Form1->PnlP15 ;       pEdt1[14] =  Form1->Edt15_1 ;
    pEdt2[14] =  Form1->Edt15_2 ;      pEdt3[14] =  Form1->Edt15_3 ;
    pEdt4[14] =  Form1->Edt15_4 ;      pScrl[14] =  Form1->ScrollBar15 ;
    pPnlN[14] =  Form1->PnlN15 ;
    pPnlP[15] =  Form1->PnlP16 ;       pEdt1[15] =  Form1->Edt16_1 ;
    pEdt2[15] =  Form1->Edt16_2 ;      pEdt3[15] =  Form1->Edt16_3 ;
    pEdt4[15] =  Form1->Edt16_4 ;      pScrl[15] =  Form1->ScrollBar16 ;
    pPnlN[15] =  Form1->PnlN16 ;
    pPnlP[16] =  Form1->PnlP17 ;       pEdt1[16] =  Form1->Edt17_1 ;
    pEdt2[16] =  Form1->Edt17_2 ;      pEdt3[16] =  Form1->Edt17_3 ;
    pEdt4[16] =  Form1->Edt17_4 ;      pScrl[16] =  Form1->ScrollBar17 ;
    pPnlN[16] =  Form1->PnlN17 ;
    pPnlP[17] =  Form1->PnlP18 ;       pEdt1[17] =  Form1->Edt18_1 ;
    pEdt2[17] =  Form1->Edt18_2 ;      pEdt3[17] =  Form1->Edt18_3 ;
    pEdt4[17] =  Form1->Edt18_4 ;      pScrl[17] =  Form1->ScrollBar18 ;
    pPnlN[17] =  Form1->PnlN18 ;
    pPnlP[18] =  Form1->PnlP19 ;       pEdt1[18] =  Form1->Edt19_1 ;
    pEdt2[18] =  Form1->Edt19_2 ;      pEdt3[18] =  Form1->Edt19_3 ;
    pEdt4[18] =  Form1->Edt19_4 ;      pScrl[18] =  Form1->ScrollBar19 ;
    pPnlN[18] =  Form1->PnlN19 ;
    pPnlP[19] =  Form1->PnlP20 ;       pEdt1[19] =  Form1->Edt20_1 ;
    pEdt2[19] =  Form1->Edt20_2 ;      pEdt3[19] =  Form1->Edt20_3 ;
    pEdt4[19] =  Form1->Edt20_4 ;      pScrl[19] =  Form1->ScrollBar20 ;
    pPnlN[19] =  Form1->PnlN20 ;
    pPnlP[20] =  Form1->PnlP21 ;       pEdt1[20] =  Form1->Edt21_1 ;
    pEdt2[20] =  Form1->Edt21_2 ;      pEdt3[20] =  Form1->Edt21_3 ;
    pEdt4[20] =  Form1->Edt21_4 ;      pScrl[20] =  Form1->ScrollBar21 ;
    pPnlN[20] =  Form1->PnlN21 ;
    pPnlP[21] =  Form1->PnlP22 ;       pEdt1[21] =  Form1->Edt22_1 ;
    pEdt2[21] =  Form1->Edt22_2 ;      pEdt3[21] =  Form1->Edt22_3 ;
    pEdt4[21] =  Form1->Edt22_4 ;      pScrl[21] =  Form1->ScrollBar22 ;
    pPnlN[21] =  Form1->PnlN22 ;
    pPnlP[22] =  Form1->PnlP23 ;       pEdt1[22] =  Form1->Edt23_1 ;
    pEdt2[22] =  Form1->Edt23_2 ;      pEdt3[22] =  Form1->Edt23_3 ;
    pEdt4[22] =  Form1->Edt23_4 ;      pScrl[22] =  Form1->ScrollBar23 ;
    pPnlN[22] =  Form1->PnlN23 ;
    pPnlP[23] =  Form1->PnlP24 ;       pEdt1[23] =  Form1->Edt24_1 ;
    pEdt2[23] =  Form1->Edt24_2 ;      pEdt3[23] =  Form1->Edt24_3 ;
    pEdt4[23] =  Form1->Edt24_4 ;      pScrl[23] =  Form1->ScrollBar24 ;
    pPnlN[23] =  Form1->PnlN24 ;
    pPnlP[24] =  Form1->PnlP25 ;       pEdt1[24] =  Form1->Edt25_1 ;
    pEdt2[24] =  Form1->Edt25_2 ;      pEdt3[24] =  Form1->Edt25_3 ;
    pEdt4[24] =  Form1->Edt25_4 ;      pScrl[24] =  Form1->ScrollBar25 ;
    pPnlN[24] =  Form1->PnlN25 ;
    pPnlP[25] =  Form1->PnlP26 ;       pEdt1[25] =  Form1->Edt26_1 ;
    pEdt2[25] =  Form1->Edt26_2 ;      pEdt3[25] =  Form1->Edt26_3 ;
    pEdt4[25] =  Form1->Edt26_4 ;      pScrl[25] =  Form1->ScrollBar26 ;
    pPnlN[25] =  Form1->PnlN26 ;
    pPnlP[26] =  Form1->PnlP27 ;       pEdt1[26] =  Form1->Edt27_1 ;
    pEdt2[26] =  Form1->Edt27_2 ;      pEdt3[26] =  Form1->Edt27_3 ;
    pEdt4[26] =  Form1->Edt27_4 ;      pScrl[26] =  Form1->ScrollBar27 ;
    pPnlN[26] =  Form1->PnlN27 ;
    pPnlP[27] =  Form1->PnlP28 ;       pEdt1[27] =  Form1->Edt28_1 ;
    pEdt2[27] =  Form1->Edt28_2 ;      pEdt3[27] =  Form1->Edt28_3 ;
    pEdt4[27] =  Form1->Edt28_4 ;      pScrl[27] =  Form1->ScrollBar28 ;
    pPnlN[27] =  Form1->PnlN28 ;
    pPnlP[28] =  Form1->PnlP29 ;       pEdt1[28] =  Form1->Edt29_1 ;
    pEdt2[28] =  Form1->Edt29_2 ;      pEdt3[28] =  Form1->Edt29_3 ;
    pEdt4[28] =  Form1->Edt29_4 ;      pScrl[28] =  Form1->ScrollBar29 ;
    pPnlN[28] =  Form1->PnlN29 ;
    pPnlP[29] =  Form1->PnlP30 ;       pEdt1[29] =  Form1->Edt30_1 ;
    pEdt2[29] =  Form1->Edt30_2 ;      pEdt3[29] =  Form1->Edt30_3 ;
    pEdt4[29] =  Form1->Edt30_4 ;      pScrl[29] =  Form1->ScrollBar30 ;
    pPnlN[29] =  Form1->PnlN30 ;

    //���薾��
    pEdt1_S[0] = Form1->EdtS1_1;
    pEdt1_S[1] = Form1->EdtS1_2;

    pEdt2_S[0] = Form1->EdtS2_1;
    pEdt2_S[1] = Form1->EdtS2_2;

    pEdt3_S[0] = Form1->EdtS3_1;
    pEdt3_S[1] = Form1->EdtS3_2;

    //Mv/a L   MV/A R
    pEdt1_V[0] = Form1->EdtVL_1;
    pEdt1_V[1] = Form1->EdtVR_1;
    pEdt2_V[0] = Form1->EdtVL_2;
    pEdt2_V[1] = Form1->EdtVR_2;
    pEdt3_V[0] = Form1->EdtVL_3;
    pEdt3_V[1] = Form1->EdtVR_3;

    pEdt1_A[0] = Form1->EdtAL_1;
    pEdt1_A[1] = Form1->EdtAR_1;
    pEdt2_A[0] = Form1->EdtAL_2;
    pEdt2_A[1] = Form1->EdtAR_2;
    pEdt3_A[0] = Form1->EdtAL_3;
    pEdt3_A[1] = Form1->EdtAR_3;

    pEdt4_S[0] = Form1->EdtS4_1;
    pEdt4_S[1] = Form1->EdtS4_2;
    pEdt4_S[2] = Form1->EdtS4_3;
    pEdt4_S[3] = Form1->EdtS4_4;

    pScrl_S[0] = Form1->ScrlS1;
    pScrl_S[1] = Form1->ScrlS2;
    pScrl_S[2] = Form1->ScrlS3;
    pScrl_S[3] = Form1->ScrlS4;

    pPnl_S[0] = Form1->PnlS1;
    pPnl_S[1] = Form1->PnlS2;
    pPnl_S[2] = Form1->PnlS3;
    pPnl_S[3] = Form1->PnlS4;


}

/***********************************************************************
*  function name : void ClearRed(void )                                *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��ʂɐԂɂȂ��Ă�����۰ق𔒂ɕς���              *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ClearRed(void)
{
   int i ;

   for( i=0; i<30 ; i++ ){
      if( KD71Data[i].SOKUTE_KBN == 1 ){
            pEdt1[i]->Font->Color = clBlack;
            pEdt2[i]->Font->Color = clBlack;
            pEdt3[i]->Font->Color = clBlack;
            pEdt4[i]->Font->Color = clBlack;
       }
   }

  //�d������
  for( i=0; i<2; i++ ){
     pEdt1_A[i]->Font->Color = clBlack;
     pEdt2_A[i]->Font->Color = clBlack;
     pEdt3_A[i]->Font->Color = clBlack;
     pEdt4_S[i+2]->Font->Color = clBlack;
  }


}

/***********************************************************************
*  function name : void SetRed(int iFlg )                              *
*                  +--------------------------------------+            *
*          ��  ��  |   1        |  �u�����v���݉����ꍇ   |            *
*                  |   2        |  �uOption�v���݉����ꍇ |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.12.02 E.Takase �R���~�̏ꍇ��ǉ�              *
*  contents      : �K�i�𒴂����v���l�̺��۰ِF��Ԃɕς���            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void SetRed(int iFlg)
{
	int i,j,k  ;
	//�ŏ��o�^�̂Ƃ��ɋK�i�`�F�b�N���Ȃ�
	if( iFlg == 1 && IsNullSpace( KD71Data[iFirstPosition-1].ADDYMD ) ) {
		//�d������
		for( i=0; i<2; i++ ){
			pEdt1_A[i]->Font->Color = clBlack;
			pEdt2_A[i]->Font->Color = clBlack;
			pEdt3_A[i]->Font->Color = clBlack;
			pEdt4_S[i+2]->Font->Color = clBlack;
		}
	}
	for( i=0; i<30 ; i++ ){
		if( KD71Data[i].SOKUTE_KBN != 1 ) continue ;
		//�ŏ��o�^�̂Ƃ��ɋK�i�`�F�b�N���Ȃ�
		if( iFlg == 1 && IsNullSpace( KD71Data[i].ADDYMD ) ) {
			pEdt1[i]->Font->Color = clBlack;
			pEdt2[i]->Font->Color = clBlack;
			pEdt3[i]->Font->Color = clBlack;
			pEdt4[i]->Font->Color == clBlack;
			continue ;
		}
		// �v��ں��ނ����K�i���`�F�b�N����
		//2002/12/02 E.Takase
		//�R���~�̏ꍇ
		if ( KD71Data[i].KEIJYO_KBN == 5 ) {
            //��ɃO���[�\��
            pEdt1[i]->Font->Color = clGray;
            pEdt2[i]->Font->Color = clGray;
            if( KD71Data[i].SOKUTEI_NM > 2 ){
			    k = 0;
				for( j=2; j< KD71Data[i].SOKUTEI_NM ; j++){
					pEdt3[i]->Font->Color = clGray;
					pEdt4[i]->Font->Color = clGray;
                }
            }
            //�����ɓd���l���`�F�b�N

			//����l�P �d����
			if( ( KD71Data[i].SOKUTEV_L[0] >  KD71Data[i].KOYU_MAX   ||
					  KD71Data[i].SOKUTEV_L[0] <  KD71Data[i].KOYU_MIN ) && ! CheckKomoku(i+1, 1) ){
				pEdt1_V[0]->Font->Color = clRed;
			}else{
				pEdt1_V[0]->Font->Color = clBlack;
			}
			//����l2 �d����
			if( (( KD71Data[i].SOKUTEV_L[1] >  KD71Data[i].KOYU_MAX   ||
				  KD71Data[i].SOKUTEV_L[1] <  KD71Data[i].KOYU_MIN )  ) && ! CheckKomoku(i+1, 2)){
				pEdt2_V[0]->Font->Color = clRed;
			}else{
				pEdt2_V[0]->Font->Color = clBlack;
			}
			if( KD71Data[i].SOKUTEI_NM > 2 ){
			k = 0;
				for( j=2; j< KD71Data[i].SOKUTEI_NM ; j++){
					//����l3�` �d����
					if( ( KD71Data[i].SOKUTEV_L[j] >  KD71Data[i].KOYU_MAX  ||
							  KD71Data[i].SOKUTEV_L[j] <  KD71Data[i].KOYU_MIN ) &&! CheckKomoku(i+1, j+1)){
							k = 1 ;
							break ;
					}
				}
				if( k ){
					if( j==2 )
						pEdt3_V[0]->Font->Color = clRed;
					else
						pEdt3_V[0]->Font->Color = clBlack;
				}else{
					pEdt3_V[0]->Font->Color = clBlack;
				}
			}

			//����l�P �d���E
			if( ( KD71Data[i].SOKUTEV_R[0] >  KD71Data[i].KOYU_MAX   ||
					  KD71Data[i].SOKUTEV_R[0] <  KD71Data[i].KOYU_MIN ) && ! CheckKomoku(i+1, 1) ){
				pEdt1_V[1]->Font->Color = clRed;
			}else{
				pEdt1_V[1]->Font->Color = clBlack;
			}
			//����l2 �d���E
			if( (( KD71Data[i].SOKUTEV_R[1] >  KD71Data[i].KOYU_MAX   ||
				  KD71Data[i].SOKUTEV_R[1] <  KD71Data[i].KOYU_MIN )  ) && ! CheckKomoku(i+1, 2)){
				pEdt2_V[1]->Font->Color = clRed;
			}else{
				pEdt2_V[1]->Font->Color = clBlack;
			}
			if( KD71Data[i].SOKUTEI_NM > 2 ){
			k = 0;
				for( j=2; j< KD71Data[i].SOKUTEI_NM ; j++){
					//����l3�` �d���E
					if( ( KD71Data[i].SOKUTEV_R[j] >  KD71Data[i].KOYU_MAX  ||
							  KD71Data[i].SOKUTEV_R[j] <  KD71Data[i].KOYU_MIN ) &&! CheckKomoku(i+1, j+1)){
							k = 1 ;
							break ;
					}
				}
				if( k ){
					if( j==2 )
						pEdt3_V[1]->Font->Color = clRed;
					else
						pEdt3_V[1]->Font->Color = clBlack;
				}else{
					pEdt3_V[1]->Font->Color = clBlack;
				}
			}

            /* ��ɃO���[�\��
			//����l�P (��R�j
			if( ( KD71Data[i].SOKUTEI_T[0] >  KD71Data[i].KOYU_MAX   ||
					  KD71Data[i].SOKUTEI_T[0] <  KD71Data[i].KOYU_MIN ) && ! CheckKomoku(i+1, 1) ){
				pEdt1[i]->Font->Color = clRed;
			}else{
				pEdt1[i]->Font->Color = clBlack;
			}
			//����l2 (��R�j
			if( (( KD71Data[i].SOKUTEI_T[1] >  KD71Data[i].KOYU_MAX   ||
				  KD71Data[i].SOKUTEI_T[1] <  KD71Data[i].KOYU_MIN )  ) && ! CheckKomoku(i+1, 2)){
				pEdt2[i]->Font->Color = clRed;
			}else{
				pEdt2[i]->Font->Color = clBlack;
			}
			if( KD71Data[i].SOKUTEI_NM > 2 ){
			k = 0;
				for( j=2; j< KD71Data[i].SOKUTEI_NM ; j++){
					//����l3�` �i��R�j
					if( ( KD71Data[i].SOKUTEI_T[j] >  KD71Data[i].KOYU_MAX  ||
							  KD71Data[i].SOKUTEI_T[j] <  KD71Data[i].KOYU_MIN ) &&! CheckKomoku(i+1, j+1)){
							k = 1 ;
							break ;
					}
				}
				if( k ){
					if( j==2 )
						pEdt3[i]->Font->Color = clRed;
					else
						pEdt3[i]->Font->Color = clBlack;
						pEdt4[i]->Font->Color = clPurple;
				}else{
					pEdt3[i]->Font->Color = clBlack;
					pEdt4[i]->Font->Color = clBlack;
				}
			}
            */

		//�R���~�ȊO�̏ꍇ
		} else {
			//����l�P (��R�j
			if( (( KD71Data[i].SOKUTEI_T[0] >  KD71Data[i].KOYU_MAX   ||
					  KD71Data[i].SOKUTEI_T[0] <  KD71Data[i].KOYU_MIN ) ||
					( KD71Data[i].SOKUTEA_L[0] >  KD71Data[i].D_Kikaku_Max    ||
					  KD71Data[i].SOKUTEA_L[0] <  KD71Data[i].D_Kikaku_Min  ) ||
					( KD71Data[i].SOKUTEA_R[0] >  KD71Data[i].D_Kikaku_Max    ||
					  KD71Data[i].SOKUTEA_R[0] <  KD71Data[i].D_Kikaku_Min   )  ) && ! CheckKomoku(i+1, 1) ){
				pEdt1[i]->Font->Color = clRed;
			}else{
				pEdt1[i]->Font->Color = clBlack;
			}
			//����l2 (��R�j
			if( (( KD71Data[i].SOKUTEI_T[1] >  KD71Data[i].KOYU_MAX   ||
				  KD71Data[i].SOKUTEI_T[1] <  KD71Data[i].KOYU_MIN ) ||
				( KD71Data[i].SOKUTEA_L[1] >  KD71Data[i].D_Kikaku_Max    ||
				  KD71Data[i].SOKUTEA_L[1] <  KD71Data[i].D_Kikaku_Min  ) ||
				( KD71Data[i].SOKUTEA_R[1] >  KD71Data[i].D_Kikaku_Max    ||
				  KD71Data[i].SOKUTEA_R[1] <  KD71Data[i].D_Kikaku_Min   )  ) && ! CheckKomoku(i+1, 2)){
				pEdt2[i]->Font->Color = clRed;
			}else{
				pEdt2[i]->Font->Color = clBlack;
			}
			if( KD71Data[i].SOKUTEI_NM > 2 ){
			k = 0;
				for( j=2; j< KD71Data[i].SOKUTEI_NM ; j++){
					//����l3�` �i��R�j
					if( ( ( KD71Data[i].SOKUTEI_T[j] >  KD71Data[i].KOYU_MAX  ||
							  KD71Data[i].SOKUTEI_T[j] <  KD71Data[i].KOYU_MIN ) ||
							( KD71Data[i].SOKUTEA_L[j] >  KD71Data[i].D_Kikaku_Max    ||
							  KD71Data[i].SOKUTEA_L[j] <  KD71Data[i].D_Kikaku_Min  ) ||
							( KD71Data[i].SOKUTEA_R[j] >  KD71Data[i].D_Kikaku_Max    ||
							  KD71Data[i].SOKUTEA_R[j] <  KD71Data[i].D_Kikaku_Min   ) ) &&! CheckKomoku(i+1, j+1)){
							k = 1 ;
							break ;
					}
				}
				if( k ){
					if( j==2 )
						pEdt3[i]->Font->Color = clRed;
					else
						pEdt3[i]->Font->Color = clBlack;
						pEdt4[i]->Font->Color = clPurple;
				}else{
					pEdt3[i]->Font->Color = clBlack;
					pEdt4[i]->Font->Color = clBlack;
				}
			}
		}
	}	// i=1,30
	//�d���̃`�F�b�N
	if( iKomoku == 3 || iKomoku == 4 )
		DenryuCheck();
}
/***********************************************************************
*  function name : void DenryuCheck(void)                              *
*                  +--------------------------------------+            *
*          ��  ��  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   �Ȃ�     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���Ļ�����߼޼��NO�̑S�v���l(�d���j�̋K�i�`�F�b�N   *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void DenryuCheck(void)
{
  double  dBuf1,dBuf2, dBuf3, dBuf4,dBuf5,dBuf6;
  int errflg ;

    errflg = 0;

    // �F�ABeep���I�t����ꍇ
    if( iOption == 3 )  return ;
    //�R���~�̏ꍇ�`�F�b�N���Ȃ� 2002/12/02 E.Takase
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) return ;

    if( iKomoku != 3 && iKomoku != 4 ) return ;

    // �K�i�ɂ���ăf�[�^���`�F�b�N����
    if( SamplePositionIdx > 0 && (SamplePositionIdx >= iFirstPosition &&
                                  SamplePositionIdx <= iLastPosition ) ){

       //�d���̃`�F�b�N
       dBuf1 = KD71Data[SamplePositionIdx-1].SOKUTEA_L[0];
       dBuf2 = KD71Data[SamplePositionIdx-1].SOKUTEA_R[0];
       dBuf3 = KD71Data[SamplePositionIdx-1].SOKUTEA_L[1];
       dBuf4 = KD71Data[SamplePositionIdx-1].SOKUTEA_R[1];


       if( (dBuf1 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max   ||
            dBuf1 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min  ) &&
            1<=KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR ){
            pEdt1_A[0]->Font->Color = clRed;
            errflg = 1;
       }else{
            pEdt1_A[0]->Font->Color = clBlack;
       }

       if( (dBuf2 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max   ||
            dBuf2 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
            KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR>=1 ){
            pEdt1_A[1]->Font->Color = clRed;
            errflg = 2;
       }else{
            pEdt1_A[1]->Font->Color = clBlack;
       }

       if( (dBuf3 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max   ||
            dBuf3 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
            KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR>=2 ){
            pEdt2_A[0]->Font->Color = clRed;
            errflg = 3;
       }else{
            pEdt2_A[0]->Font->Color = clBlack;
       }

       if( (dBuf4 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max   ||
            dBuf4 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
            2 <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR){
            pEdt2_A[1]->Font->Color = clRed;
            errflg = 4;
       }else{
            pEdt2_A[1]->Font->Color = clBlack;
       }

      //�R�`�X�X�܂ł̑S�ް��ɕs���i�ް����Ȃ���΁AEdtA4�𔒂ɂ���
      if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM > 2){

         dBuf5 = KD71Data[SamplePositionIdx-1].SOKUTEA_L[2];
         dBuf6 = KD71Data[SamplePositionIdx-1].SOKUTEA_R[2];

          // mV/A L
          if( (dBuf5 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max  ||
               dBuf5 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min ) &&
               3 <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR ){
                pEdt3_A[0]->Font->Color = clRed;
                pEdt4_S[2]->Font->Color = clPurple;
                errflg = 5;
          }else{
                pEdt3_A[0]->Font->Color = clBlack;
          }

       //�R�Ԗڂ��ް����i�̏ꍇ
       if( errflg != 5 ){
         int k=0;
         for(int  i=3; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){

             if( ( KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
                   KD71Data[SamplePositionIdx-1].SOKUTEA_L[i] < KD71Data[SamplePositionIdx-1].D_Kikaku_Min ) &&
                    KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                    i <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR  ){
                   k= 1 ;
                   break ;

             }
         }

         //�s���i�ް�������ꍇ
         if( k){
               pEdt4_S[2]->Font->Color = clPurple;
               errflg = 5;
         }else{
               pEdt4_S[2]->Font->Color = clBlack;
         }
       }


        // mV/A R
          if(( dBuf6 > KD71Data[SamplePositionIdx-1].D_Kikaku_Max  ||
               dBuf6 < KD71Data[SamplePositionIdx-1].D_Kikaku_Min) &&
                3 <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){
                pEdt3_A[1]->Font->Color = clRed;
                pEdt4_S[3]->Font->Color = clPurple;
                errflg = 6;
          }else{
                pEdt3_A[1]->Font->Color = clBlack;
          }

       //�R�Ԗڂ��ް����i�̏ꍇ
       if( errflg != 6 ){
         int k=0;
         for(int  i=3; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){

             if( ( KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] > KD71Data[SamplePositionIdx-1].D_Kikaku_Max ||
                   KD71Data[SamplePositionIdx-1].SOKUTEA_R[i] < KD71Data[SamplePositionIdx-1].D_Kikaku_Min ) &&
                    KD71Data[SamplePositionIdx-1].SOKUTE_KBN == 1 &&
                    i <= KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR ){
                   k= 1 ;
                   break ;

             }
         }

         //�s���i�ް�������ꍇ
         if( k){
               pEdt4_S[3]->Font->Color = clPurple;
               errflg = 6;
         }else{
               pEdt4_S[3]->Font->Color = clBlack;
         }
       }

      }

      // ����l�P�A����Q�s���i�̏ꍇ
     // if( errflg )  Beep();
  }
}


/***********************************************************************
*  function name : int  KTeikouCal(int iSp,int iDt)                    *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp      |  ������߼޼��NO         |            *
*                  |   iDt      |  �����ް�NO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   0        | �v�Z���Ȃ�              |            *
*                  |   1        | �v�Z����                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.02 E.Takase                                 *
*  contents      : �ŗL��R���̌v�Z                                    *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  KTeikouCal(int iSp,int iDt)
{
  int ret;
  double dv, da, dtmp;

  ret = 0;

  //�ŗL��R���̌v�Z
  //�R���~�̏ꍇ�̌v�Z���ǉ� 2002/11/02 E.Takase
  //�~���̏ꍇ
  if(  KD71Data[iSp-1].KEIJYO_KBN == 4) {
     if(  CheckKomoku( iSp, iDt ) == 0  ){
          dv =( KD71Data[iSp-1].SOKUTEV_L[iDt-1] + KD71Data[iSp-1].SOKUTEV_R[iDt-1])/2.0 ;
          da =( KD71Data[iSp-1].SOKUTEA_L[iDt-1] + KD71Data[iSp-1].SOKUTEA_R[iDt-1])/2.0 ;

           dtmp = (dv*KD71Data[iSp-1].SOKUTEI_H[iDt-1]*KD71Data[iSp-1].SOKUTEI_H[iDt-1]*0.01*3.14159*1000.0/4.0)/
                                            (da*KD71Data[iSp-1].SOKUTEI_P[iDt-1]*0.1);
           KD71Data[iSp-1].SOKUTEI_T[iDt-1] = dtmp;
           ret = 1 ;

     }else{
         KD71Data[iSp-1].SOKUTEI_T[iDt-1] = 0.0 ;
         ret = 0;
     }

  }else if(  KD71Data[iSp-1].KEIJYO_KBN == 5) {
  //�R���~�̏ꍇ
      if( CheckKomoku( iSp, iDt ) == 0  ){

          dv =( KD71Data[iSp-1].SOKUTEV_L[iDt-1] + KD71Data[iSp-1].SOKUTEV_R[iDt-1])/2.0 ;
          dtmp= dv;

          KD71Data[iSp-1].SOKUTEI_T[iDt-1] = dtmp;
          ret = 1 ;

      }else{
         KD71Data[iSp-1].SOKUTEI_T[iDt-1] = 0.0 ;
         ret = 0;
      }

  }else{
  //�u���b�N�̏ꍇ
      if( CheckKomoku( iSp, iDt ) == 0  ){

          dv =( KD71Data[iSp-1].SOKUTEV_L[iDt-1] + KD71Data[iSp-1].SOKUTEV_R[iDt-1])/2.0 ;
          da =( KD71Data[iSp-1].SOKUTEA_L[iDt-1] + KD71Data[iSp-1].SOKUTEA_R[iDt-1])/2.0 ;

          dtmp= (dv*KD71Data[iSp-1].SOKUTEI_S[iDt-1]*KD71Data[iSp-1].SOKUTEI_H[iDt-1]*0.01*1000.0)/
                                              (da*KD71Data[iSp-1].SOKUTEI_P[iDt-1]*0.1);
          KD71Data[iSp-1].SOKUTEI_T[iDt-1] = dtmp;
          ret = 1 ;

      }else{
         KD71Data[iSp-1].SOKUTEI_T[iDt-1] = 0.0 ;
         ret = 0;
      }

 }

 // �R�ܗ͌v����
 if( ret){
      if ( KD71Data[iSp-1].SOKUTEI_NT_CUR < iDt )
           KD71Data[iSp-1].SOKUTEI_NT_CUR = iDt ;
 }

  return ret ;
}

/***********************************************************************
*  function name : int  CheckKomoku(int iSp,int iDt)                   *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp      |  ������߼޼��NO         |            *
*                  |   iDt      |  �����ް�NO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   0        | �v�Z���Ȃ�              |            *
*                  |   1        | �v�Z����                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���Čv���l�̑S���ڂ��v���������ǂ���������          *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int CheckKomoku(int iSp, int iDt)
{
  int ret = 0;

  //�~���̏ꍇ
  if(  KD71Data[iSp-1].KEIJYO_KBN == 4) {
   if( KD71Data[iSp-1].SOKUTEI_NVL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NVR_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAR_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NH_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NP_CUR == 0  ){
       ret = 1 ;
       return ret;
   }

   if(  KD71Data[iSp-1].SOKUTEI_H[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEI_P[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_R[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_R[iDt-1] <= 0.0000001    ){
        ret = 2;
        return ret ;
   }
  //�R���~�̏ꍇ
  } else if(  KD71Data[iSp-1].KEIJYO_KBN == 5) {
   if( KD71Data[iSp-1].SOKUTEI_NVL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NVR_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAR_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NS_CUR == 0  ){
       ret = 1 ;
       return ret;
   }

   if(  KD71Data[iSp-1].SOKUTEI_S[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEI_P[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_R[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_R[iDt-1] <= 0.0000001    ){
        ret = 2;
        return ret ;
   }
  // �����̂̏ꍇ
  }else{
   if( KD71Data[iSp-1].SOKUTEI_NVL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAL_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NVR_CUR == 0  &&
       KD71Data[iSp-1].SOKUTEI_NAR_CUR == 0  &&
      KD71Data[iSp-1].SOKUTEI_NS_CUR == 0  &&
      KD71Data[iSp-1].SOKUTEI_NH_CUR == 0  &&
      KD71Data[iSp-1].SOKUTEI_NP_CUR == 0  ){
      ret = 1 ;
      return ret;
   }

   if(  KD71Data[iSp-1].SOKUTEI_S[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEI_H[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEI_P[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEV_R[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_L[iDt-1] <= 0.0000001 ||
        KD71Data[iSp-1].SOKUTEA_R[iDt-1] <= 0.0000001    ){
        ret = 2;
        return ret ;
   }
  }
 return ret ;
}

/***********************************************************************
*  function name : int  IsKeisokuEnd(void  )                           *
*                  +--------------------------------------+            *
*          ��  ��  |   ����     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   0        | �v���r��                |            *
*                  |   1        | �v���I��                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �S�����ް����v���I�����ǂ����̃`�F�b�N              *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int IsKeisokuEnd(void)
{
  int i,ret;

  ret = 1;

  for( i=0; i<30; i++ ){

     if(  (KD71Data[i].SOKUTEI_NT_CUR < KD71Data[i].SOKUTEI_NM) &&
           KD71Data[i].SOKUTE_KBN == 1 ){
              ret = 0 ;
             break;
      }
  }

 return ret ;
}
/*---------------------------------------------------------------------------
 * -- BEGIN_MAN -------------------------------------------------------------
 *
 * --- (Name) ----------
 *
 * GetItem()
 *
 * --- (Form) ----------
 *
 * int	GetItem(buff, item)
 * char	**buff;
 * char	*item;
 *
 * --- (Discription) ---
 *
 *   �^����ꂽ������ւ̃|�C���^�����؂蕶���i�X�y�[�X�j�ŕ������ꂽ�A�C�e
 * �������o���B���o������ɁA������ւ̃|�C���^�����o�����A�C�e���̌��
 * �X�V����B
 *
 * --- (ReturnValue) ---
 *
 * �A�C�e�������o����΂O�A���o���Ȃ����-1��Ԃ��B
 *
 * --- (Reference) -----
 *
 * �Ȃ�
 *
 * --- (Notice) --------
 *
 * -- END_MAN ---------------------------------------------------------------
 */

int
GetItem(buff, item)
char	**buff;			/* ������ւ̃|�C���^�̃A�h���X */
char	*item;			/* ���o�����A�C�e�����i�[����o�b�t�@ */
{

     /***** �o�b�t�@����Ȃ�G���[���^�[������ *****/

    if (*buff == 0)
	return -1;

    if (**buff == '\n' || strlen(*buff) == 0)
	return -1;

    /***** ��؂蕶����ǂݔ�΂� *****/

    while (**buff == ' ')
	++(*buff);

    /***** �A�C�e���̎��o�� *****/

    while (**buff != ' ' && **buff != '\n' && **buff != 0) {
	*item = **buff;
	++item;
	++(*buff);
    }
    *item = '\0';

    return 0;
}

/***********************************************************************
*  function name : Ansistring DelSEPA( Ansistring sYMD )               *
*                  +--------------------------------------+            *
*          ��  ��  |   sYMD        |  ���t�iYYYY/MM/DD�j  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |               |  ���t�iYYYYMMDD�j    |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���t(YYYY/MM/DD)����(YYYYMMDD)�֕ϊ�                *
*  written by    :                            *
***********************************************************************/
AnsiString DelSEPA( AnsiString sYMD )
{
  int        iPos;
  AnsiString sRet;

  sRet = sYMD ;
  while( ( iPos = sRet.AnsiPos("/")) != 0 ){
      sRet.Delete(iPos, 1) ;

  }
  return ( sRet );

}

/***********************************************************************
*  function name : Ansistring DelSEPA( Ansistring sYMD )               *
*                  +--------------------------------------+            *
*          ��  ��  |   sYMD        |  ���t�iYYYYMMDD�j    |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |               |  ���t�iYYYY/MM/DD�j  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���t(YYYYMMDD)����(YYYY/MM/DD)�֕ϊ�                *
*  written by    :                                                     *
***********************************************************************/
AnsiString InsSEPA( AnsiString sYMD )
{
  AnsiString sRet;

  sRet = sYMD ;

  sRet.Insert("/",5);
  sRet.Insert("/",8);

  return ( sRet );

}

/***********************************************************************
*  function name : void EndBeep(void)                                  *
*                  +--------------------------------------+            *
*          ��  ��  |   ����        |                      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����        |                      |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���f�B�A�̍Đ�                                      *
*  written by    :                                                     *
***********************************************************************/
void EndBeep(int flg)
{
   if( flg == 1 )
      Form1->MdPlayer->FileName = "KChang.wav";
   else
      Form1->MdPlayer->FileName = "End.wav";

    Form1->MdPlayer->Open();
    Form1->MdPlayer->Play();

   return ;
}
