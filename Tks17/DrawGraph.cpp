/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１７）                  *
*  file   name   : DrawGraph.cpp                                       *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率 測定履歴、工程能力作画関数               *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
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
*          引  数  |   iSp     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 作画ｺﾝﾄﾛｰﾙ関数                                      *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void ToDrawGraph( int iSp, int iOpt )
{

     // iSp ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ番号
    switch(iOpt)
    {
         case 1:     // 測定履歴図
            Form1->PageCtrl->Visible = true ;
            Form1->PageCtrl->ActivePage = Form1->TabSheet1;

            SetRirekiData(iSp);
           break;
         case 2:     //  工程能力図
            Form1->PageCtrl->Visible = true ;
            Form1->PageCtrl->ActivePage = Form1->TabSheet2;
            if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
                DispKoutei(iSp) ;
            } else {
                DispKoutei_2(iSp) ;
            }
           break;
         case 3:     //  表示しない
            Form1->PageCtrl->Visible = false ;
           break;
         default:
           break;
    }
}

/***********************************************************************
*  function name : void DispKotei(int iSp )                            *
*                  +--------------------------------------+            *
*          引  数  |   iSp     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 工程能力情報を計算し、画面へセットする              *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void DispKoutei( int iSp )
{
   double dMax, dMin, dAve;
   double dR;
   double dSigma;
   double dCp, dCpk, dK, dFuryo;
   int n, i,j , iLotStart;
   int FuryoCnt =0;

   // 変数の初期化
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

   //表示データを求める
   int iLinkSp;
   if(  KD71Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD71Data[iSp-1].LINK;
   }

   // 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

//   if( iRtn < (LOTMAX-1) )
//     iLotStart = 0;
//   else
//     iLotStart = iRtn-LOTMAX + 1 ;
    //コンミ対応 2003.02.14 E.Takase
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

   //履歴ﾃﾞｰﾀ
   for( i=iLotStart; i < iRtn ; i++ ){

          if(KD73WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

           //履歴データ個数
           n += KD73WData[iLinkSp-1].SOKUTEI_NM[i] ;

           // 平均値の計算
           dAve += KD73WData[iLinkSp-1].SOKUTE_AVE[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];

           for( j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

                if( KD73WData[iLinkSp-1].SOKUTEI[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEI[i][j];
                if( KD73WData[iLinkSp-1].SOKUTEI[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEI[i][j];

                 //不合格ﾃﾞｰﾀのﾁｪｯｸ
                if(  KD73WData[iLinkSp-1].SOKUTEI[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
                     KD73WData[iLinkSp-1].SOKUTEI[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
                 FuryoCnt +=1 ;

           }
   }

   //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
   if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 )
   {

            //データ個数
            n += KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            // 平均値の計算
            for( j=0; j< KD71Data[iSp-1].SOKUTEI_NT_CUR; j++ ) {
                dAve += KD71Data[iSp-1].SOKUTEI_T[j];

               if( KD71Data[iSp-1].SOKUTEI_T[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEI_T[j];
               if( KD71Data[iSp-1].SOKUTEI_T[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEI_T[j];

                //不合格ﾃﾞｰﾀのﾁｪｯｸ
                if(  KD71Data[iSp-1].SOKUTEI_T[j] >  KD71Data[iSp-1].KOYU_MAX ||
                     KD71Data[iSp-1].SOKUTEI_T[j] <  KD71Data[iSp-1].KOYU_MIN )
                 FuryoCnt +=1 ;
           }

   }

   if( n== 0 ) {
       SetData( 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
        return ;
   }

   //全体の平均値
   dAve = dAve/n;

   dR   = dMax - dMin ;

   //σの計算
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

    //dCp, dCpkの規格ﾁｪｯｸ
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

    //不良率
    dFuryo =((double)FuryoCnt/(double)n)*100.0;

    SetData( n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

    return ;

}
/***********************************************************************
*  function name : void DispKotei_2(int iSp )                          *
*                  +--------------------------------------+            *
*          引  数  |   iSp     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 2002.12                                             *
*  update        :                                                     *
*  contents      : 工程能力情報を計算し、画面へセットする              *
*  written by    : 高瀬 恵利(NKK unics Corp.)                          *
***********************************************************************/
void DispKoutei_2( int iSp )
{
	double dMax, dMin, dAve;
	double dR;
	double dSigma;
	double dCp, dCpk, dK, dFuryo;
	int n, i,j , iLotStart;
	int FuryoCnt =0;

	// 変数の初期化
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

	//表示データを求める
	int iLinkSp;
	if(  KD71Data[iSp-1].LINK == 0 ){
		iLinkSp = iSp ;
	}else {
		iLinkSp = KD71Data[iSp-1].LINK;
	}

	// 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
	int iRtn =  CheckLotNo( iSp ) ;
	if( iRtn <0 ) return ;

	//if( iRtn < (LOTMAX-1) )
	//	iLotStart = 0;
	//else
	//	iLotStart = iRtn-LOTMAX + 1 ;
    //コンミ対応 2003.02.14 E.Takase
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

	//履歴ﾃﾞｰﾀ
	for( i=iLotStart; i < iRtn ; i++ ){

		if(KD73WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

		//履歴データ個数
		n += (KD73WData[iLinkSp-1].SOKUTEI_NM[i]*2) ;

		//平均値の計算
		dAve += KD73WData[iLinkSp-1].SOKUTE_AVE_L[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];
		dAve += KD73WData[iLinkSp-1].SOKUTE_AVE_R[i]*KD73WData[iLinkSp-1].SOKUTEI_NM[i];

		for( j=0; j< KD73WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

			if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] > dMax ) dMax = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_L[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEV_L[i][j];
			if( KD73WData[iLinkSp-1].SOKUTEV_R[i][j] < dMin ) dMin = KD73WData[iLinkSp-1].SOKUTEV_R[i][j];

			//不合格ﾃﾞｰﾀのﾁｪｯｸ
			//電圧 左
			if(  KD73WData[iLinkSp-1].SOKUTEV_L[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
					KD73WData[iLinkSp-1].SOKUTEV_L[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
				FuryoCnt +=1 ;
			//電圧 右
			if(  KD73WData[iLinkSp-1].SOKUTEV_R[i][j] >  KD73WData[iLinkSp-1].KOYU_MAX[i] ||
					KD73WData[iLinkSp-1].SOKUTEV_R[i][j] <  KD73WData[iLinkSp-1].KOYU_MIN[i] )
				FuryoCnt +=1 ;

		}
	}

	//ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
	if( KD71Data[iSp-1].SOKUTEI_NT_CUR != 0 )
	{

	    //データ個数
	    n += (KD71Data[iSp-1].SOKUTEI_NT_CUR*2) ;

	    // 平均値の計算
	    for( j=0; j< KD71Data[iSp-1].SOKUTEI_NT_CUR; j++ ) {
		    dAve += KD71Data[iSp-1].SOKUTEV_L[j];
		    dAve += KD71Data[iSp-1].SOKUTEV_R[j];

		    if( KD71Data[iSp-1].SOKUTEV_L[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEV_L[j];
		    if( KD71Data[iSp-1].SOKUTEV_R[j] > dMax ) dMax = KD71Data[iSp-1].SOKUTEV_R[j];
		    if( KD71Data[iSp-1].SOKUTEV_L[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEV_L[j];
		    if( KD71Data[iSp-1].SOKUTEV_R[j] < dMin ) dMin = KD71Data[iSp-1].SOKUTEV_R[j];

		    //不合格ﾃﾞｰﾀのﾁｪｯｸ
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

	//全体の平均値
	dAve = dAve/n;

	dR = dMax - dMin ;

	//σの計算
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

	//dCp, dCpkの規格ﾁｪｯｸ
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

	//不良率
	dFuryo =((double)FuryoCnt/(double)n)*100.0;

	SetData( n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

	return ;

}

/***********************************************************************
*  function name : int  SetRirekiData( int iSp )                       *
*                  +--------------------------------------+            *
*          引  数  |   iSp     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 測定履歴作画用データを求める                        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
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


  // 作画用変数の初期化
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

   // 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

    //コンミ対応 2003.02.14 E.Takase
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
   //履歴ﾃﾞｰﾀ
   n=0;
   iPos = 0;
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD73WData[iLinkSp-1].SOKUTEI_NM[i] != 0 ) {
              //コンミ以外
              if ( KD73WData[iLinkSp-1].KEIJYO_KBN != 5 ) {
                // 最大値、最小値、平均値の計算
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

              //コンミ
              } else {
                // 最大値、最小値、平均値の計算
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

   //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
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

         //コンミ以外
         if ( KD71Data[iSp-1].KEIJYO_KBN != 5 ) {
            //計測データ中の最大値と最小値
            Max[iPos] = maxa;
            Min[iPos] = mina ;
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ){
              if( KD71Data[iSp-1].SOKUTEI_T[i] > Max[iPos] ) Max[iPos] = KD71Data[iSp-1].SOKUTEI_T[i];
              if( KD71Data[iSp-1].SOKUTEI_T[i] < Min[iPos] ) Min[iPos] = KD71Data[iSp-1].SOKUTEI_T[i];
            }

            // 平均値の計算
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR; i++ )
              Val[iPos] += KD71Data[iSp-1].SOKUTEI_T[i] ;
            Val[iPos] = Val[iPos]/KD71Data[iSp-1].SOKUTEI_NT_CUR ;

            str = KD71Data[iSp-1].LOTNO ;
            if( str.Length() > 5 ) str = str.Delete(1,1);
            strncpy(Xstr[iPos],str.c_str(), str.Length() );
            Xstr[iPos][5] = '\0';

         //コンミ
         } else {
            //計測データ中の最大値と最小値
            //L
            Max[iPos] = maxa;
            Min[iPos] = mina ;
            for( i=0; i< KD71Data[iSp-1].SOKUTEI_NT_CUR ; i++ ){
              if( KD71Data[iSp-1].SOKUTEV_L[i] > Max[iPos] ) Max[iPos] = KD71Data[iSp-1].SOKUTEV_L[i];
              if( KD71Data[iSp-1].SOKUTEV_L[i] < Min[iPos] ) Min[iPos] = KD71Data[iSp-1].SOKUTEV_L[i];
            }

            // 平均値の計算
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

            // 平均値の計算
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
*          引  数  |   GraphName | 作画ｺﾝﾄﾛｰﾙ             |            *
*                  |   n         | 出力ロット個数         |            *
*                  |   Xstr      | ロットNO               |            *
*                  |   Max       | ﾛｯﾄNO毎の規格上限値    |            *
*                  |   Min       | ﾛｯﾄNO毎の規格下限値    |            *
*                  |   Val       | ﾛｯﾄNO毎の測定値平均値  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 測定履歴作画関数                                    *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
//---------------------------------------------------------------------------
void DrawRireki(TImage *GraphName,int n, char *Pstr, double Max[10], double Min[10], double Val[10], int iCur)
{

    int i;
    int x1,x2,y1,y2, x3, y3 ;                     //線を描画するときの座標
    double MaxY,MinY;                             //Y軸　読み込んだデータの中の最大値、最小値
    double ScaleMax,ScaleMin,ScaleVal, ScaleMid;   //目盛りの最大値、最小値、間隔
    int ItemWidth;
    int CharWidth;                                //Y軸座標値を描画するための余白
    int CharHeight;                               //X軸座標値を描画するための余白
    int FontHeight;
    double XWidth,YHeight,ScaleHeight;
    int PreScaleNo,MasterScaleNo,ScaleNo;         //目盛りの予備数、主目盛り数
    int ImageH,ImageW;                            //イメージの高さ、幅
    AnsiString str;
    char Xstr[10][10];
    AnsiString sBuf;
    AnsiString sBuf2;
    int iLen;
    AnsiString FormatStr;//Y軸の目盛りの文字列の書式（"0" or "0.00"）

    //memcpy(Xstr, Pstr, 50);
    memcpy(Xstr, Pstr, 100);

    //目盛りの数の設定
    PreScaleNo = 1;
    MasterScaleNo = 3;
    ScaleNo = MasterScaleNo + ( PreScaleNo * 2 );

    GraphName->Canvas->Brush->Color = clInfoBk;
    GraphName->Canvas->Brush->Style = bsSolid;
    GraphName->Canvas->Pen->Color = clWhite;
    GraphName->Canvas->FillRect( GraphName->ClientRect );

    //色、線のスタイル、フォントサイズの設定
    GraphName->Canvas->Pen->Color = clBlack; //線の色
    GraphName->Canvas->Pen->Style = psSolid; //線のスタイル実線
    GraphName->Canvas->Pen->Width = 1;       //線の太さ
    GraphName->Canvas->Font->Size = 8;       //文字のサイズ

    //Y軸の目盛りの書式 2003.02.06 E.Takase
    if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
        FormatStr = "0.00";
    } else {
        FormatStr = "0";
    }

    //最大値、最小値の検索
    MaxY = KD71Data[SamplePositionIdx-1].KOYU_MAX ;
    MinY = KD71Data[SamplePositionIdx-1].KOYU_MIN;

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MaxY =MinY+1.0 ;
    }

    // 目盛りの間隔、最小値、最大値の設定
     ScaleVal = (MaxY-MinY)/(ScaleNo-1) ;
     ScaleMin = MinY ;
     ScaleMid = ( MaxY+ MinY )/2.0;

    //グラフ描画の際に使用する定数の設定
    CharWidth = -GraphName->Canvas->Font->Height * 3;   //左端とY軸の間の余白
    CharHeight = -GraphName->Canvas->Font->Height * 2;  //下端とX軸の間の余白
    FontHeight = -GraphName->Canvas->Font->Height;      //文字の高さ
    ScaleHeight =( GraphName->Height - ( CharHeight * 2 )) //１目盛りの高さ
                                            / (( ScaleNo + 1 ) * 1.0 );
    XWidth = ( GraphName->Width - ( CharWidth * 2 ) )
                                           / (( LOTMAX + 1 ) * 1.0 ); //X軸の定数
    YHeight = ScaleHeight / ( ScaleVal * 1.0 ) ;   //Y軸の定数
    ImageH = GraphName->Height;  //GraphImageの高さ
    ImageW = GraphName->Width;   //GraphImageの幅
    ItemWidth = 3;                       //Min,Maxの横線の幅

    GraphName->Canvas->Pen->Width = 2;  //線の太さ2

    ////////
    CharWidth =  CharWidth-GraphName->Canvas->Font->Height * 0.6;   //左端とY軸の間の余白

    //
    double HMax = ImageH - CharHeight;
    double HMin = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));

    //X軸 左
    x1 = CharWidth;
    x2 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    y1 = ImageH - CharHeight;
    y2 = y1;
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    //Y軸 下
    x1 = CharWidth;
    x2 = x1;
    y1 = ImageH - CharHeight;
    y2 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    GraphName->Canvas->Pen->Width = 1;      //線の太さ

    //X軸 右
    x1 = CharWidth;
    x2 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    y1 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    y2 = y1;
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    //Y軸 上
    x1 = CharWidth + ( XWidth * ( LOTMAX + 1 ));
    x2 = x1;
    y1 = ImageH - CharHeight;
    y2 = ImageH - CharHeight - ( ScaleVal * YHeight * ( ScaleNo + 1 ));
    GraphName->Canvas->MoveTo(x1,y1);
    GraphName->Canvas->LineTo(x2,y2);

    GraphName->Canvas->Pen->Color = clGray; //線の色

    for ( i = 0; i < LOTMAX; i++ ){

        //縦軸
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
             GraphName->Canvas->Pen->Width = 2;     //線の太さ2
        }else if( i== ScaleNo-1 ) {
             GraphName->Canvas->Pen->Color = clRed;
             GraphName->Canvas->Pen->Width = 2;     //線の太さ2
        }else{
            GraphName->Canvas->Pen->Color = clGray; //線の色
            GraphName->Canvas->Pen->Width = 1;      //線の太さ2
        }

        //横軸
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

        //計測しているﾛｯﾄNOの場合色を変える
        //2002/11/21 E.Takase
        //if( i== iCur ) {
        if( i >= iCur ) {
             GraphName->Canvas->Pen->Color = clBlue;
        }else{
            GraphName->Canvas->Pen->Color = clBlack; //線の色
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

    GraphName->Canvas->Pen->Width = 2;      //線の太さ

    for ( i = 0; i < n; i++ ){

        if( Val[i]  <= 0.0 ) continue ;

         //計測しているﾛｯﾄNOの場合色を変える
         //2002/11/21 E.Takase
         //if( i== iCur ) {
        if( i >= iCur ) {
             GraphName->Canvas->Pen->Color = clBlue;
        }else{
            GraphName->Canvas->Pen->Color = clBlack; //線の色
        }

        //Minの横線
        x1 = CharWidth + ( XWidth * ( i + 1 )) - ItemWidth;
        x2 = x1 + ( ItemWidth * 2 );
        y1 = ImageH - CharHeight - (( Min[i]- ScaleMin + ScaleVal ) * YHeight );
        y2 = y1;

        if( y2 <= HMax && y2 >= HMin){

            GraphName->Canvas->MoveTo(x1,y1);
            GraphName->Canvas->LineTo(x2,y2);
        }
        //Maxの横線
        x1 = CharWidth + ( XWidth * ( i + 1 )) - ItemWidth;
        x2 = x1 + ( ItemWidth * 2 );
        y1 = ImageH - CharHeight - (( Max[i]- ScaleMin + ScaleVal ) * YHeight );
        y2 = y1;

        if( y2 <= HMax && y2 >= HMin){

           GraphName->Canvas->MoveTo(x1,y1);
           GraphName->Canvas->LineTo(x2,y2);
        }

        //Min、Maxの縦線
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
*          引  数  |   dMin     | Min                     |            *
*                  |   dMax     | Max                     |            *
*                  |   dAve     | Ave                     |            *
*                  |   dR       | R                       |            *
*                  |   dSigma   | σ                      |            *
*                  |   dCp      | Cp                      |            *
*                  |   dCpk     | Cpk                     |            *
*                  |   dK       | K                       |            *
*                  |   dFuryo   | 不良率                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   無し    |                          |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 工程能力情報を画面へセットする                      *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/

void SetData( int iN,double dMin,double  dMax,double  dAve,double  dR,double  dSigma,
              double dCp, double  dCpk,double  dK,  double dFuryo )
{
   //画面へデータ設定
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
*          引  数  |   iSp     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   =0      |なし                      |            *
*                  |   >0      | Index NO                 |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD73Wから読み込んだﾃﾞｰﾀ中にに指定したロットNo       *
*                :  有るかどうか のチェック                            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
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




