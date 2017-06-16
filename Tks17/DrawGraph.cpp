/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�V�j                  *
*  file   name   : DrawGraph.cpp                                       *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �ŗL��R�� ���藚���A�H���\�͍��֐�               *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

int SetRirekiData(void ) ;
void DispKoutei(int);
void DispKoutei_2(int);
int  CheckLotNo(int ) ;
void SetData( int,double ,double ,double  ,double ,double ,double , double ,double ,  double ) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] , int );
void SetRirekiData(int ) ;

//---------------------------------------------------------------------------
#pragma package(smart_init)

/***********************************************************************
*  function name : void ToDrawGraph( int iSp )                         *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp     | ���Ļ�����߼޼��NO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �����۰ي֐�                                      *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void ToDrawGraph( int iSp, int iOpt )
{

     // iSp ���Ļ�����߼޼�ݔԍ�
    switch(iOpt)
    {
         case 1:     // ���藚��}
            Form1->PageCtrl->Visible = true ;
            Form1->PageCtrl->ActivePage = Form1->TabSheet1;

            SetRirekiData(iSp);
           break;
         case 2:     //  �H���\�͐}
            Form1->PageCtrl->Visible = true ;
            Form1->PageCtrl->ActivePage = Form1->TabSheet2;
            if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
                DispKoutei(iSp) ;
            } else {
                DispKoutei_2(iSp) ;
            }
           break;
         case 3:     //  �\�����Ȃ�
            Form1->PageCtrl->Visible = false ;
           break;
         default:
           break;
    }
}

/***********************************************************************
*  function name : void DispKotei(int iSp )                            *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp     | ���Ļ�����߼޼��NO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �H���\�͏����v�Z���A��ʂփZ�b�g����              *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void DispKoutei( int iSp )
{
   double dMax, dMin, dAve;
   double dR;
   double dSigma;
   double dCp, dCpk, dK, dFuryo;
   int n, i,j , iLotStart;
   int FuryoCnt =0;

   // �ϐ��̏�����
   dMax = 0.0 ;
   dMin = 0.0 ;
   dR = 0.0 ;
   dCp = 0.0 ;
   dCpk = 0.0 ;
   dK = 0.0 ;
   dFuryo = 0.0 ;
   dSigma = 0.0 ;
   dAve = 0.0;

   double maxa =-9999999.0 ;
   double mina = 9999999.0;

   //�\���f�[�^�����߂�
   int iLinkSp;
   if(  KD71Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD71Data[iSp-1].LINK;
   }

   // �����ް��̒��ɶ��ă��b�g�ԍ���INDEX��T��
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

//   if( iRtn < (LOTMAX-1) )
//     iLotStart = 0;
//   else
//     iLotStart = iRtn-LOTMAX + 1 ;
    //�R���~�Ή� 2003.02.14 E.Takase
    if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
        if( iRtn <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = iRtn-LOTMAX + 1 ;
     } else {
        if( (iRtn*2) <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = ((iRtn * 2) - LOTMAX)/2 + 1 ;
     }


   dAve =0.0 ;
   n=0;
   dMax = maxa;
   dMin = mina ;

   //�����ް�
   for( i=iLotStart; i < iRtn ; i++ ){

          if(KD73WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

           //�����f�[�^��
           n += KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;

           // ���ϒl�̌v�Z
           dAve += KD73WData[iLinkSp-1].SOKUTE_AVE[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];

           for( j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

                if( KD73WData[iLinkSp-1].SOKUTEI[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEI[i][j];
                if( KD73WData[iLinkSp-1].SOKUTEI[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEI[i][j];

                 //�s���i�ް�������
                if(  KD73WData[iLinkSp-1].SOKUTEI[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
                     KD73WData[iLinkSp-1].SOKUTEI[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
                 FuryoCnt +=1 ;

           }
   }

   //���Ķ��ق�����v���ް�
   if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 )
   {

            //�f�[�^��
            n += KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            // ���ϒl�̌v�Z
            for( j=0; j< KD71Data[iSp-1].SOKUTEI_NT_CUR; j++ ) {
                dAve += KD71Data[iSp-1].SOKUTEI_T[j];

               if( KD71Data[iSp-1].SOKUTEI_T[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEI_T[j];
               if( KD71Data[iSp-1].SOKUTEI_T[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEI_T[j];

                //�s���i�ް�������
                if(  KD71Data[iSp-1].SOKUTEI_T[j] >  KD71Data[iSp-1].KOYU_MAX ||
                     KD71Data[iSp-1].SOKUTEI_T[j] <  KD71Data[iSp-1].KOYU_MIN )
                 FuryoCnt +=1 ;
           }

   }

   if( n== 0 ) {
       SetData( 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
        return ;
   }

   //�S�̂̕��ϒl
   dAve = dAve/n;

   dR   = dMax - dMin ;

   //�Ђ̌v�Z
   dSigma = 0.0;
   if( n!= 1 ){

       for( i=iLotStart; i<iRtn ; i++ )
       {
           for( int j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ )
                dSigma += (KD73WData[iLinkSp-1].SOKUTEI[i][j] - dAve)*(KD73WData[iLinkSp-1].SOKUTEI[i][j] - dAve) ;
       }

       if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 ) {
           for( i=0; i<KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ )
                dSigma += (KD71Data[iSp-1].SOKUTEI_T[i] - dAve)*(KD71Data[iSp-1].SOKUTEI_T[i] - dAve) ;
       }

       dSigma = sqrt(dSigma/(n-1)) ;
   }


   double dA = KD71Data[iSp-1].KOYU_MAX + KD71Data[iSp-1].KOYU_MIN ;
   double dB = KD71Data[iSp-1].KOYU_MAX - KD71Data[iSp-1].KOYU_MIN ;

   // Cp
   if( dSigma > 0.0 )
       dCp = dB/(6*dSigma) ;
   else
       dCp = 0.0 ;

    //K
    dK = fabs(dA*0.5-dAve);

    if( dB > 0.0 ){
        dK = dK/(dB*0.5);
    }else{
        dK = 0.0 ;
    }

    // dCpk
    dCpk = (1-dK)*dCp ;

    //dCp, dCpk�̋K�i����
    if( iOption == 2 ){
    //if( dCp < 1.33 || dCpk < 1.33 ){
      // Beep();
    //}
    if( dCp < 1.33 )
          Form1->Pnl33->Font->Color = clRed ;
    else
          Form1->Pnl33->Font->Color = clBlack ;
    if( dCpk < 1.33 )
          Form1->Pnl41->Font->Color = clRed ;
    else
          Form1->Pnl41->Font->Color = clBlack ;
    }

    //�s�Ǘ�
    dFuryo =((double)FuryoCnt/(double)n)*100.0;

    SetData( n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

    return ;

}
/***********************************************************************
*  function name : void DispKotei_2(int iSp )                          *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp     | ���Ļ�����߼޼��NO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : �H���\�͏����v�Z���A��ʂփZ�b�g����              *
*  written by    : ���� �b��(NKK unics Corp.)                          *
***********************************************************************/
void DispKoutei_2( int iSp )
{
	double dMax, dMin, dAve;
	double dR;
	double dSigma;
	double dCp, dCpk, dK, dFuryo;
	int n, i,j , iLotStart;
	int FuryoCnt =0;

	// �ϐ��̏�����
	dMax = 0.0 ;
	dMin = 0.0 ;
	dR = 0.0 ;
	dCp = 0.0 ;
	dCpk = 0.0 ;
	dK = 0.0 ;
	dFuryo = 0.0 ;
	dSigma = 0.0 ;
	dAve = 0.0;

	double maxa =-9999999.0 ;
	double mina = 9999999.0;

	//�\���f�[�^�����߂�
	int iLinkSp;
	if(  KD71Data[iSp-1].LINK == 0 ){
		iLinkSp = iSp ;
	}else {
		iLinkSp = KD71Data[iSp-1].LINK;
	}

	// �����ް��̒��ɶ��ă��b�g�ԍ���INDEX��T��
	int iRtn =  CheckLotNo( iSp ) ;
	if( iRtn <0 ) return ;

	//if( iRtn < (LOTMAX-1) )
	//	iLotStart = 0;
	//else
	//	iLotStart = iRtn-LOTMAX + 1 ;
    //�R���~�Ή� 2003.02.14 E.Takase
    if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
        if( iRtn <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = iRtn-LOTMAX + 1 ;
     } else {
        if( (iRtn*2) <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = ((iRtn * 2) - LOTMAX)/2 + 1 ;
     }

	dAve =0.0 ;
	n=0;
	dMax = maxa;
	dMin = mina ;

	//�����ް�
	for( i=iLotStart; i < iRtn ; i++ ){

		if(KD73WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

		//�����f�[�^��
		n += (KD73WData[iLinkSp-1].SOKUTEI_NM[i]*2) ;

		//���ϒl�̌v�Z
		dAve += KD73WData[iLinkSp-1].SOKUTE_AVE_L[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];
		dAve += KD73WData[iLinkSp-1].SOKUTE_AVE_R[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];

		for( j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

			if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];

			//�s���i�ް�������
			//�d�� ��
			if(  KD73WData[iLinkSp-1].SOKUTEV_L[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
					KD73WData[iLinkSp-1].SOKUTEV_L[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
				FuryoCnt +=1 ;
			//�d�� �E
			if(  KD73WData[iLinkSp-1].SOKUTEV_R[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
					KD73WData[iLinkSp-1].SOKUTEV_R[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
				FuryoCnt +=1 ;

		}
	}

	//���Ķ��ق�����v���ް�
	if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 )
	{

	    //�f�[�^��
	    n += (KD71Data[iSp-1].SOKUTEI_NT_CUR*2) ;

	    // ���ϒl�̌v�Z
	    for( j=0; j< KD71Data[iSp-1].SOKUTEI_NT_CUR; j++ ) {
		    dAve += KD71Data[iSp-1].SOKUTEV_L[j];
		    dAve += KD71Data[iSp-1].SOKUTEV_R[j];

		    if( KD71Data[iSp-1].SOKUTEV_L[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEV_L[j];
		    if( KD71Data[iSp-1].SOKUTEV_R[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEV_R[j];
		    if( KD71Data[iSp-1].SOKUTEV_L[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEV_L[j];
		    if( KD71Data[iSp-1].SOKUTEV_R[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEV_R[j];

		    //�s���i�ް�������
		    if(  KD71Data[iSp-1].SOKUTEV_L[j] >  KD71Data[iSp-1].KOYU_MAX ||
			        KD71Data[iSp-1].SOKUTEV_L[j] <  KD71Data[iSp-1].KOYU_MIN ) {
			    FuryoCnt +=1 ;
		    }
		    if(  KD71Data[iSp-1].SOKUTEV_R[j] >  KD71Data[iSp-1].KOYU_MAX ||
				    KD71Data[iSp-1].SOKUTEV_R[j] <  KD71Data[iSp-1].KOYU_MIN ) {
			    FuryoCnt +=1 ;
		    }

	    }
    }

	if( n== 0 ) {
		SetData( 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
		return ;
	}

	//�S�̂̕��ϒl
	dAve = dAve/n;

	dR = dMax - dMin ;

	//�Ђ̌v�Z
	dSigma = 0.0;
	if( n!= 1 ){

		for( i=iLotStart; i<iRtn ; i++ )
		{
			for( int j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {
				dSigma += (KD73WData[iLinkSp-1].SOKUTEV_L[i][j] - dAve)*(KD73WData[iLinkSp-1].SOKUTEV_L[i][j] - dAve) ;
				dSigma += (KD73WData[iLinkSp-1].SOKUTEV_R[i][j] - dAve)*(KD73WData[iLinkSp-1].SOKUTEV_R[i][j] - dAve) ;
			}
		}

		if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 ) {
			for( i=0; i<KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ) {
				dSigma += (KD71Data[iSp-1].SOKUTEV_L[i] - dAve)*(KD71Data[iSp-1].SOKUTEV_L[i] - dAve) ;
				dSigma += (KD71Data[iSp-1].SOKUTEV_R[i] - dAve)*(KD71Data[iSp-1].SOKUTEV_R[i] - dAve) ;
    		}
		}

		dSigma = sqrt(dSigma/(n-1)) ;
	}


	double dA = KD71Data[iSp-1].KOYU_MAX + KD71Data[iSp-1].KOYU_MIN ;
	double dB = KD71Data[iSp-1].KOYU_MAX - KD71Data[iSp-1].KOYU_MIN ;

	// Cp
	if( dSigma > 0.0 )
		dCp = dB/(6*dSigma) ;
	else
		dCp = 0.0 ;

	//K
	dK = fabs(dA*0.5-dAve);

	if( dB > 0.0 ){
		dK = dK/(dB*0.5);
	}else{
		dK = 0.0 ;
	}

	// dCpk
	dCpk = (1-dK)*dCp ;

	//dCp, dCpk�̋K�i����
	if( iOption == 2 ){
	    //if( dCp < 1.33 || dCpk < 1.33 ){
		    // Beep();
	    //}
	    if( dCp < 1.33 )
	    	Form1->Pnl33->Font->Color = clRed ;
	    else
	    	Form1->Pnl33->Font->Color = clBlack ;
	    if( dCpk < 1.33 )
	    	Form1->Pnl41->Font->Color = clRed ;
	    else
    		Form1->Pnl41->Font->Color = clBlack ;
    }

	//�s�Ǘ�
	dFuryo =((double)FuryoCnt/(double)n)*100.0;

	SetData( n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

	return ;

}

/***********************************************************************
*  function name : int  SetRirekiData( int iSp )                       *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp     | ���Ļ�����߼޼��NO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���藚�����p�f�[�^�����߂�                        *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
void SetRirekiData(int iSp)
{
  int i,j, n, iLotStart;
  int iRRR;
  int iPos;
  AnsiString str;
  //char Xstr[50][5];
  //double Max[50];
  //double Min[50];
  //double Val[50];
  char Xstr[100][10];
  double Max[100];
  double Min[100];
  double Val[100];

  double maxa =-9999999.0 ;
  double mina = 9999999.0;


  // ���p�ϐ��̏�����
   //for(i=0; i<LOTMAX*5; i++ ){
   for(i=0; i<LOTMAX*10; i++ ){
     memset( Xstr[i], 0x0, 5 );
     Max[i] = 0.0;
     Min[i] = 0.0;
     Val[i] = 0.0;
   }

   int iLinkSp=0;
   if(  KD71Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD71Data[iSp-1].LINK;
   }

   // �����ް��̒��ɶ��ă��b�g�ԍ���INDEX��T��
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

    //�R���~�Ή� 2003.02.14 E.Takase
    if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
        if( iRtn <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = iRtn-LOTMAX + 1 ;
     } else {
        if( (iRtn*2) <= (LOTMAX-1) )
            iLotStart = 0;
        else
            iLotStart = ((iRtn * 2) - LOTMAX)/2 + 1 ;
     }
   //�����ް�
   n=0;
   iPos = 0;
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD73WData[iLinkSp-1].SOKUTEI_NM[i] != 0 ) {
              //�R���~�ȊO
              if ( KD73WData[iLinkSp-1].KEIJYO_KBN != 5 ) {
                // �ő�l�A�ŏ��l�A���ϒl�̌v�Z
                //Max[i-iLotStart] = maxa;
                //Min[i-iLotStart] = mina ;
                //for(  j=0; j<KD73WData[iLinkSp-1].SOKUTEI_NM[i] ; j++ ){
                //    if( KD73WData[iLinkSp-1].SOKUTEI[i][j] > Max[i-iLotStart] ) Max[i-iLotStart] = KD73WData[iLinkSp-1].SOKUTEI[i][j];
                //    if( KD73WData[iLinkSp-1].SOKUTEI[i][j] < Min[i-iLotStart] ) Min[i-iLotStart] = KD73WData[iLinkSp-1].SOKUTEI[i][j];
                //
                //    Val[i-iLotStart] += KD73WData[iLinkSp-1].SOKUTEI[i][j] ;
                //}
                //
                //Val[i-iLotStart] = Val[i-iLotStart]/KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;
                Max[iPos] = maxa;
                Min[iPos] = mina ;
                for(  j=0; j<KD73WData[iLinkSp-1].SOKUTEI_NM[i] ; j++ ){
                    if( KD73WData[iLinkSp-1].SOKUTEI[i][j] > Max[iPos] ) Max[iPos] = KD73WData[iLinkSp-1].SOKUTEI[i][j];
                    if( KD73WData[iLinkSp-1].SOKUTEI[i][j] < Min[iPos] ) Min[iPos] = KD73WData[iLinkSp-1].SOKUTEI[i][j];

                    Val[iPos] += KD73WData[iLinkSp-1].SOKUTEI[i][j] ;
                }
                Val[iPos] = Val[iPos]/KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;

                str = KD73WData[iLinkSp-1].LOTNO[i] ;
                if( str.Length() > 5 ) str = str.Delete(1,1);
                strncpy(Xstr[iPos],str.c_str() , str.Length());
                Xstr[iPos][5] = '\0';

              //�R���~
              } else {
                // �ő�l�A�ŏ��l�A���ϒl�̌v�Z
                //L
                Max[iPos] = maxa;
                Min[iPos] = mina ;
                for(  j=0; j<KD73WData[iLinkSp-1].SOKUTEI_NM[i] ; j++ ){
                    if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] > Max[iPos] ) Max[iPos] = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];
                    if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] < Min[iPos] ) Min[iPos] = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];

                    Val[iPos] += KD73WData[iLinkSp-1].SOKUTEV_L[i][j] ;
                }
                Val[iPos] = Val[iPos]/KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;

                str = KD73WData[iLinkSp-1].LOTNO[i] ;
                if( str.Length() > 5 ) str = str.Delete(1,1);
                //strncpy(Xstr[iPos],str.c_str() , str.Length());
                sprintf(Xstr[iPos], "%s   L", str.c_str());

                //R
                iPos++;
                Max[iPos] = maxa;
                Min[iPos] = mina ;
                for(  j=0; j<KD73WData[iLinkSp-1].SOKUTEI_NM[i] ; j++ ){
                    if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] > Max[iPos] ) Max[iPos] = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];
                    if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] < Min[iPos] ) Min[iPos] = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];

                    Val[iPos] += KD73WData[iLinkSp-1].SOKUTEV_R[i][j] ;
                }
                Val[iPos] = Val[iPos]/KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;

                str = KD73WData[iLinkSp-1].LOTNO[i] ;
                if( str.Length() > 5 ) str = str.Delete(1,1);
                //strncpy(Xstr[iPos],str.c_str() , str.Length());
                sprintf(Xstr[iPos], "%s   R", str.c_str());

              }
          } else {

            str = KD73WData[iLinkSp-1].LOTNO[i] ;
            if( str.Length() > 5 ) str = str.Delete(1,1);
            strncpy(Xstr[iPos],str.c_str() , str.Length());
            Xstr[iPos][5] = '\0';

          }

          n += 1;
          iPos++;
   }

   //���Ķ��ق�����v���ް�
   //2002/11/30 E.Takase
   //iRRR = iRtn ;
   iRRR = iPos ;

   //if( iRtn >= LOTMAX ) iRRR = 9;
   if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
      if( iRtn >= LOTMAX ) iRRR = 9;
   } else {
      if( iRtn >= LOTMAX ) iRRR = 8;
   }

   if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 )
   {

         //�R���~�ȊO
         if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
            //�v���f�[�^���̍ő�l�ƍŏ��l
            Max[iPos] = maxa;
            Min[iPos] = mina ;
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ){
              if( KD71Data[iSp-1].SOKUTEI_T[i] > Max[iPos] ) Max[iPos] = KD71Data[iSp-1].SOKUTEI_T[i];
              if( KD71Data[iSp-1].SOKUTEI_T[i] < Min[iPos] ) Min[iPos] = KD71Data[iSp-1].SOKUTEI_T[i];
            }

            // ���ϒl�̌v�Z
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR; i++ )
              Val[iPos] += KD71Data[iSp-1].SOKUTEI_T[i] ;
            Val[iPos] = Val[iPos]/KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            str = KD71Data[iSp-1].LOTNO ;
            if( str.Length() > 5 ) str = str.Delete(1,1);
            strncpy(Xstr[iPos],str.c_str(), str.Length() );
            Xstr[iPos][5] = '\0';

         //�R���~
         } else {
            //�v���f�[�^���̍ő�l�ƍŏ��l
            //L
            Max[iPos] = maxa;
            Min[iPos] = mina ;
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ){
              if( KD71Data[iSp-1].SOKUTEV_L[i] > Max[iPos] ) Max[iPos] = KD71Data[iSp-1].SOKUTEV_L[i];
              if( KD71Data[iSp-1].SOKUTEV_L[i] < Min[iPos] ) Min[iPos] = KD71Data[iSp-1].SOKUTEV_L[i];
            }

            // ���ϒl�̌v�Z
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR; i++ )
              Val[iPos] += KD71Data[iSp-1].SOKUTEV_L[i] ;
            Val[iPos] = Val[iPos]/KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            str = KD71Data[iSp-1].LOTNO ;
            if( str.Length() > 5 ) str = str.Delete(1,1);
            //strncpy(Xstr[iPos],str.c_str(), str.Length() );
            //Xstr[iPos][5] = '\0';
            sprintf(Xstr[iPos], "%s   L", str.c_str());

            iPos++;

            //R
            Max[iPos] = maxa;
            Min[iPos] = mina ;
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ){
              if( KD71Data[iSp-1].SOKUTEV_R[i] > Max[iPos] ) Max[iPos] = KD71Data[iSp-1].SOKUTEV_R[i];
              if( KD71Data[iSp-1].SOKUTEV_R[i] < Min[iPos] ) Min[iPos] = KD71Data[iSp-1].SOKUTEV_R[i];
            }

            // ���ϒl�̌v�Z
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR; i++ )
              Val[iPos] += KD71Data[iSp-1].SOKUTEV_R[i] ;
            Val[iPos] = Val[iPos]/KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            str = KD71Data[iSp-1].LOTNO ;
            if( str.Length() > 5 ) str = str.Delete(1,1);
            //strncpy(Xstr[iPos],str.c_str(), str.Length() );
            //Xstr[iPos][5] = '\0';
            sprintf(Xstr[iPos], "%s   R", str.c_str());

         }
   }

   n += 1;
   iPos++;

   //DrawRireki( Form1->GraphyImg, n , &Xstr[0][0], Max, Min, Val, iRRR) ;
   DrawRireki( Form1->GraphyImg, iPos , &Xstr[0][0], Max, Min, Val, iRRR) ;

   return ;

}

/***********************************************************************
*  function name : void DrawRireki(TImage *GraphName,int n,            *
*                                   char Xstr[12][5],                  *
*                                   double Max[12], double Min[12],    *
*                                   double Val[12] )                   *
*                  +--------------------------------------+            *
*          ��  ��  |   GraphName | �����۰�             |            *
*                  |   n         | �o�̓��b�g��         |            *
*                  |   Xstr      | ���b�gNO               |            *
*                  |   Max       | ۯ�NO���̋K�i����l    |            *
*                  |   Min       | ۯ�NO���̋K�i�����l    |            *
*                  |   Val       | ۯ�NO���̑���l���ϒl  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ���藚�����֐�                                    *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
//---------------------------------------------------------------------------
void DrawRireki(TImage *GraphName,int n, char *Pstr, double Max[10], double Min[10], double Val[10], int iCur)
{

    int i;
    int x1,x2,y1,y2, x3, y3 ;                     //����`�悷��Ƃ��̍��W
    double MaxY,MinY;                             //Y���@�ǂݍ��񂾃f�[�^�̒��̍ő�l�A�ŏ��l
    double ScaleMax,ScaleMin,ScaleVal, ScaleMid;   //�ڐ���̍ő�l�A�ŏ��l�A�Ԋu
    int ItemWidth;
    int CharWidth;                                //Y�����W�l��`�悷�邽�߂̗]��
    int CharHeight;                               //X�����W�l��`�悷�邽�߂̗]��
    int FontHeight;
    double XWidth,YHeight,ScaleHeight;
    int PreScaleNo,MasterScaleNo,ScaleNo;         //�ڐ���̗\�����A��ڐ��萔
    int ImageH,ImageW;                            //�C���[�W�̍����A��
    AnsiString str;
    char Xstr[10][10];
    AnsiString sBuf;
    AnsiString sBuf2;
    int iLen;
    AnsiString FormatStr;//Y���̖ڐ���̕�����̏����i"0" or "0.00"�j

    //memcpy(Xstr, Pstr, 50);
    memcpy(Xstr, Pstr, 100);

    //�ڐ���̐��̐ݒ�
    PreScaleNo = 1;
    MasterScaleNo = 3;
    ScaleNo = MasterScaleNo + ( PreScaleNo * 2 );

    GraphName->Canvas->Brush->Color = clInfoBk;
    GraphName->Canvas->Brush->Style = bsSolid;
    GraphName->Canvas->Pen->Color = clWhite;
    GraphName->Canvas->FillRect( GraphName->ClientRect );

    //�F�A���̃X�^�C���A�t�H���g�T�C�Y�̐ݒ�
    GraphName->Canvas->Pen->Color = clBlack; //���̐F
    GraphName->Canvas->Pen->Style = psSolid; //���̃X�^�C������
    GraphName->Canvas->Pen->Width = 1;       //���̑���
    GraphName->Canvas->Font->Size = 8;       //�����̃T�C�Y

    //Y���̖ڐ���̏��� 2003.02.06 E.Takase
    if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //�R���~
        FormatStr = "0.00";
    } else {
        FormatStr = "0";
    }

    //�ő�l�A�ŏ��l�̌���
    MaxY = KD71Data[SamplePositionIdx-1].KOYU_MAX ;
    MinY = KD71Data[SamplePositionIdx-1].KOYU_MIN;

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MaxY =MinY+1.0 ;
    }

    // �ڐ���̊Ԋu�A�ŏ��l�A�ő�l�̐ݒ�
     ScaleVal = (MaxY-MinY)/(ScaleNo-1) ;
     ScaleMin = MinY ;
     ScaleMid = ( MaxY+ MinY )/2.0;

    //�O���t�`��̍ۂɎg�p����萔�̐ݒ�
    CharWidth = -GraphName->Canvas->Font->Height * 3;   //���[��Y���̊Ԃ̗]��
    CharHeight = -GraphName->Canvas->Font->Height * 2;  //���[��X���̊Ԃ̗]��
    FontHeight = -GraphName->Canvas->Font->Height;      //�����̍���
    ScaleHeight =( GraphName->Height - ( CharHeight * 2 )) //�P�ڐ���̍���
                                            / (( ScaleNo + 1 ) * 1.0 );
    XWidth = ( GraphName->Width - ( CharWidth * 2 ) )
                                           / (( LOTMAX + 1 ) * 1.0 ); //X���̒萔
    YHeight = ScaleHeight / ( ScaleVal * 1.0 ) ;   //Y���̒萔
    ImageH = GraphName->Height;  //GraphImage�̍���
    ImageW = GraphName->Width;   //GraphImage�̕�
    ItemWidth = 3;                       //Min,Max�̉����̕�

    GraphName->Canvas->Pen->Width = 2;  //���̑���2

    ////////
    CharWidth =  CharWidth-GraphName->Canvas->Font->Height * 0.6;   //���[��Y���̊Ԃ̗]��

    //
    double HMax = ImageH - CharHeight;
    double HMin = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));

    //X�� ��
    x1 = CharWidth;
    x2 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    y1 = ImageH - CharHeight;
    y2 = y1;
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    //Y�� ��
    x1 = CharWidth;
    x2 = x1;
    y1 = ImageH - CharHeight;
    y2 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    GraphName->Canvas->Pen->Width = 1;      //���̑���

    //X�� �E
    x1 = CharWidth;
    x2 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    y1 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    y2 = y1;
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    //Y�� ��
    x1 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    x2 = x1;
    y1 = ImageH - CharHeight;
    y2 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    GraphName->Canvas->Pen->Color = clGray; //���̐F

    for ( i = 0; i < LOTMAX; i++ ){

        //�c��
        x1 = CharWidth + ( XWidth * ( i + 1 ));
        x2 = x1;
        y1 = ImageH - CharHeight;
        y2 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
        GraphName->Canvas->MoveTo(x1,y1);
        GraphName->Canvas->LineTo(x2,y2);

          char sTmp[6];
          sTmp[0]= NULL ;
          //memcpy(sTmp,Xstr[i],5);
          //sTmp[5] = NULL ;
          sBuf = Xstr[i];
          //GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sTmp);
          if( i < n ){
	          if ( sBuf.Length() > 5 ) {
          		sBuf2 = sBuf.SubString(1,5);
          		GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sBuf2.c_str());
          		sBuf2 = sBuf.SubString(6, sBuf.Length() - 5);
          		GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3 + ( FontHeight ), sBuf2.c_str());
	          
	          } else {
          		GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sBuf.c_str());
	          }
          }
    }

    AnsiString str1;
    for ( i = 0; i < ScaleNo; i++ ){

        if( i == 0 ){
             GraphName->Canvas->Pen->Color = clRed;
             GraphName->Canvas->Pen->Width = 2;     //���̑���2
        }else if( i== ScaleNo-1 ) {
             GraphName->Canvas->Pen->Color = clRed;
             GraphName->Canvas->Pen->Width = 2;     //���̑���2
        }else{
            GraphName->Canvas->Pen->Color = clGray; //���̐F
            GraphName->Canvas->Pen->Width = 1;      //���̑���2
        }

        //����
        x1 = CharWidth;
        x2 = CharWidth + ( XWidth * ( LOTMAX+ 1 ));
        y1 = ImageH - CharHeight - ( ScaleVal * YHeight * ( i + 1 ));
        y2 = y1;

        GraphName->Canvas->MoveTo(x1,y1);
        GraphName->Canvas->LineTo(x2,y2);

        if( i== 0 ) {
            //200.02.06 E.Takase str = FormatFloat ("0",MinY );
            str = FormatFloat (FormatStr,MinY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }else if( i== ScaleNo-1 ) {
            //200.02.06 E.Takase str = FormatFloat ("0", MaxY );
            str = FormatFloat (FormatStr, MaxY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }else if( i== 2 ){
            //200.02.06 E.Takase str = FormatFloat ("0", ScaleMid);
            str = FormatFloat (FormatStr, ScaleMid);
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }
    }

    for ( i = 0; i <  n ; i++ ){

        if( Val[i] <=0.0 ) continue  ;

        //�v�����Ă���ۯ�NO�̏ꍇ�F��ς���
        //2002/11/21 E.Takase
        //if( i== iCur ) {
        if( i >= iCur ) {
             GraphName->Canvas->Pen->Color = clBlue;
        }else{
            GraphName->Canvas->Pen->Color = clBlack; //���̐F
        }
        x1 = CharWidth + ( XWidth * ( i + 1 ));
        y1 = ImageH - CharHeight - (( Val[i]- ScaleMin + ScaleVal ) * YHeight );

        if( y1 < HMin || y1 > HMax ) continue ;


        x2 = x1-ItemWidth;
        y2 = y1+ItemWidth;
        x3 = x1+ItemWidth;
        y3 = y1-ItemWidth;

        GraphName->Canvas->Brush->Style = bsSolid ;
        GraphName->Canvas->Ellipse( x2,y2,x3,y3 );
     }

    GraphName->Canvas->Pen->Width = 2;      //���̑���

    for ( i = 0; i < n; i++ ){

        if( Val[i]  <= 0.0 ) continue ;

         //�v�����Ă���ۯ�NO�̏ꍇ�F��ς���
         //2002/11/21 E.Takase
         //if( i== iCur ) {
        if( i >= iCur ) {
             GraphName->Canvas->Pen->Color = clBlue;
        }else{
            GraphName->Canvas->Pen->Color = clBlack; //���̐F
        }

        //Min�̉���
        x1 = CharWidth + ( XWidth * ( i + 1 )) - ItemWidth;
        x2 = x1 + ( ItemWidth * 2 );
        y1 = ImageH - CharHeight - (( Min[i]- ScaleMin + ScaleVal ) * YHeight );
        y2 = y1;

        if( y2 <= HMax && y2 >= HMin){

            GraphName->Canvas->MoveTo(x1,y1);
            GraphName->Canvas->LineTo(x2,y2);
        }
        //Max�̉���
        x1 = CharWidth + ( XWidth * ( i + 1 )) - ItemWidth;
        x2 = x1 + ( ItemWidth * 2 );
        y1 = ImageH - CharHeight - (( Max[i]- ScaleMin + ScaleVal ) * YHeight );
        y2 = y1;

        if( y2 <= HMax && y2 >= HMin){

           GraphName->Canvas->MoveTo(x1,y1);
           GraphName->Canvas->LineTo(x2,y2);
        }

        //Min�AMax�̏c��
        x1 = CharWidth + ( XWidth * ( i + 1 ));
        x2 = x1;
        y1 = ImageH - CharHeight - (( Min[i]- ScaleMin + ScaleVal ) * YHeight );
        y2 = ImageH - CharHeight - (( Max[i]- ScaleMin + ScaleVal ) * YHeight );

        if( y1 <HMin && y2 <HMin ) continue ;
        if( y1 >HMax && y2 >HMax ) continue ;

        if( y1 > HMax )  y1 = HMax ;
        if( y2 < HMin )  y2 = HMin ;

        GraphName->Canvas->MoveTo(x1,y1);
        GraphName->Canvas->LineTo(x2,y2);

    }
}


/***********************************************************************
*  function name : void SetData( double dMin,double  dMax,double  dAve,*
*                                 double  dR,double  dSigma,           *
*                                 double dCp, double  dCpk,double  dK, *
*                                 double dFuryo )                      *
*                  +--------------------------------------+            *
*          ��  ��  |   dMin     | Min                     |            *
*                  |   dMax     | Max                     |            *
*                  |   dAve     | Ave                     |            *
*                  |   dR       | R                       |            *
*                  |   dSigma   | ��                      |            *
*                  |   dCp      | Cp                      |            *
*                  |   dCpk     | Cpk                     |            *
*                  |   dK       | K                       |            *
*                  |   dFuryo   | �s�Ǘ�                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   ����    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �H���\�͏�����ʂփZ�b�g����                      *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/

void SetData( int iN,double dMin,double  dMax,double  dAve,double  dR,double  dSigma,
              double dCp, double  dCpk,double  dK,  double dFuryo )
{
   //��ʂփf�[�^�ݒ�
   Form1->Pnl24->Caption = FormatFloat("0", iN );
   Form1->Pnl21->Caption = FormatFloat("#0.00", dMin );
   Form1->Pnl22->Caption = FormatFloat("#0.00", dMax );
   Form1->Pnl23->Caption = FormatFloat("#0.000", dAve );

   Form1->Pnl31->Caption = FormatFloat("#0.00000", dR );
   Form1->Pnl32->Caption = FormatFloat("#0.00000", dSigma );
   Form1->Pnl33->Caption = FormatFloat("#0.00", dCp );

   Form1->Pnl41->Caption = FormatFloat("#0.00", dCpk );
   Form1->Pnl42->Caption = FormatFloat("#0.000", dK );
   Form1->Pnl43->Caption = FormatFloat("#0.000", dFuryo );

}

/***********************************************************************
*  function name : int  CheckLotNo(int iSp)                            *
*                  +--------------------------------------+            *
*          ��  ��  |   iSp     | ���Ļ�����߼޼��NO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |   =0      |�Ȃ�                      |            *
*                  |   >0      | Index NO                 |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD73W����ǂݍ����ް����ɂɎw�肵�����b�gNo       *
*                :  �L�邩�ǂ��� �̃`�F�b�N                            *
*  written by    : �� ���N(NKK unics Corp.)                            *
***********************************************************************/
int  CheckLotNo(int iSp)
{

   int iLinkSp;

   int iFlag = -1;

    if(  KD71Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD71Data[iSp-1].LINK;
   }

   for( int i=0; i<  KD73WData[iLinkSp-1].LOTCNT; i++ ){
      if(  KD71Data[iSp-1].LOTNO ==  KD73WData[iLinkSp-1].LOTNO[i] )
      {
        iFlag = i ;
        break ;
       }
   }

   return iFlag ;
}




