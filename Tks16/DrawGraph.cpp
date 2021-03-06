/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ16）                    *
*  file   name   : DrawGraph.cpp                                       *
*  create        : 1999.12.01                                          *
*  update        :                                                     *
*  contents      : 硬度測定履歴、工程能力作画関数                      *
*  written by    : 周 欽銘 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Tks16.h"

#define COM_DIFF 0.000001

double S_Cpk = 1.33;
double S_Cp = 1.33;

// 表示する履歴ﾃﾞｰﾀの最大個数
extern int LOTMAX;

void DispKoutei( int iSp, int AS_Flag, int A_No );
void SetData(int ,double,double,double,double,double,double,double,double,double,int,int) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void DrawRireki0(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void DrawRireki1(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void SetRirekiData(int iSp, int AS_Flag, int A_No);
double SetScalVal(double , double, int) ;
double SetScalVal0(double , double) ;

extern int  CheckLotNo(int iSp);

//---------------------------------------------------------------------------
#pragma package(smart_init)

// 作画ｺﾝﾄﾛｰﾙ関数
// iSp: SampleNo
// iOpt: 1: 圧面測定履歴図
//       2: 圧面工程能力図
//       3: 側面測定履歴図
//       4: 側面工程能力図
//       5: 表示なし
// A_No: 1: Ｈｓｃ
//       2: Ｈｓｄ
void ToDrawGraph( int iSp, int iOpt, int A_No )
{
    // 表示条件チェック
    if (!(A_No == 1 || A_No == 2) || KD61Data[iSp-1].SAMPLE_P == -1 ||
       (A_No == 1 && KD61Data[iSp-1].SOKUTE_KBN1 == 0) ||
       (A_No == 2 && KD61Data[iSp-1].SOKUTE_KBN2 == 0)) {
       switch (A_No) {
       case 1:
            Form1->PageCtl_Hsc->Visible = false ;
            break;
       case 2:
            Form1->PageCtl_Hsd->Visible = false ;
            break;
       }
       return;
    }

    // iSp ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ番号
    if (A_No == 1) {   // Hsc
       switch(iOpt) {
       case 1:     // 圧面 測定履歴図
            Form1->PageCtl_Hsc->Visible = true ;
            Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet1;

            SetRirekiData(iSp, 0, A_No);
            break;
       case 2:     // 圧面 工程能力図
            Form1->PageCtl_Hsc->Visible = true ;
            Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet2;
            DispKoutei(iSp, 0, A_No) ;
            break;
       case 3:     // 側面 測定履歴図
            Form1->PageCtl_Hsc->Visible = true ;
            Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet3;

            SetRirekiData(iSp, 1, A_No);
            break;
       case 4:     // 側面 工程能力図
            Form1->PageCtl_Hsc->Visible = true ;
            Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet4;
            DispKoutei(iSp, 1, A_No) ;
            break;
       case 5:     //  表示しない
            Form1->PageCtl_Hsc->Visible = false ;
            break;
       default:
           break;
       }
     } else { // Hsd
       switch(iOpt) {
       case 1:     // 圧面 測定履歴図
            Form1->PageCtl_Hsd->Visible = true ;
            Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet1;

            SetRirekiData(iSp, 0, A_No);
            break;
       case 2:     // 圧面 工程能力図
            Form1->PageCtl_Hsd->Visible = true ;
            Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet2;
            DispKoutei(iSp, 0, A_No) ;
            break;
       case 3:     // 側面 測定履歴図
            Form1->PageCtl_Hsd->Visible = true ;
            Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet3;

            SetRirekiData(iSp, 1, A_No);
            break;
       case 4:     // 側面 工程能力図
            Form1->PageCtl_Hsd->Visible = true ;
            Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet4;
            DispKoutei(iSp, 1, A_No) ;
            break;
       case 5:     //  表示しない
            Form1->PageCtl_Hsd->Visible = false ;
            break;
       default:
           break;
       }
    }
}

//工程能力情報を計算し、画面へセットする
// iSp:      SampleNo
// AS_Flag:  0: 圧面工程能力図
//           1: 側面工程能力図
// A_No:     1: Ｈｓｃ
//           2: Ｈｓｄ
void DispKoutei( int iSp, int AS_Flag, int A_No )
{
   double dMax, dMin, dAve;
   double dR, dA, dB;
   double dSigma;
   double dCp, dCpk, dK, dFuryo;
   int n, i,j , iLotStart;
   int Cur_Num;
   int ErrorNum;

   if (!(A_No == 1 || A_No == 2))
      return;

   if (!(AS_Flag == 0 || AS_Flag == 1))
      return;

   if (A_No == 1 && AS_Flag == 1 && KD61Data[iSp-1].SOKUTE_KBN1 == 1)
      return;

   if (A_No == 1 && AS_Flag == 0 && KD61Data[iSp-1].SOKUTE_KBN1 == 2)
      return;

   if (A_No == 2 && AS_Flag == 1 && KD61Data[iSp-1].SOKUTE_KBN2 == 1)
      return;

   if (A_No == 2 && AS_Flag == 0 && KD61Data[iSp-1].SOKUTE_KBN2 == 2)
      return;

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
   ErrorNum = 0;  // 規格以外Count

   double maxa =-9999999.0 ;
   double mina = 9999999.0;

   //表示データを求める
   int iLinkSp;
   if(  KD61Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD61Data[iSp-1].LINK;
   }

   // 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

   if( iRtn < (LOTMAX-1) )
     iLotStart = 0;
   else
     iLotStart = iRtn-LOTMAX + 1 ;

   dAve =0.0 ;
   n=0;
   dMax = maxa;
   dMin = mina ;

   //履歴ﾃﾞｰﾀ
   if (A_No == 1) {   // Hsc
      for (i=iLotStart; i < iRtn ; i++ ) {
          if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i] == 0)
             continue ;

          //履歴データ個数
          n += KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i] ;

          // 平均値の計算
          dAve += KD63WData[iLinkSp-1].HSC_AVE[AS_Flag][i] *
                  KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i];

          // 最大値と最小値
          for (j=0; j< KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i]; j++ ) {
              if (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] > dMax )
                 dMax = KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j];

              if (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] < dMin )
                 dMin = KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j];

              // 規格チェック
              if (!(KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] >= KD63WData[iLinkSp-1].HSC_MIN[AS_Flag][i] &&
                  KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] <= KD63WData[iLinkSp-1].HSC_MAX[AS_Flag][i]))
                 ErrorNum++;
          }
      }

      // 現在計測データ数
      if (AS_Flag == 0) { // 圧面
         if (KD61Data[iSp-1].HSC_SK_NUM_CUR <= KD61Data[iSp-1].HSC_SK_NUM)
            Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR;
         else
            Cur_Num = KD61Data[iSp-1].HSC_SK_NUM;
      } else {    // 側面
         if (KD61Data[iSp-1].HSC_SK_NUM_CUR <= KD61Data[iSp-1].HSC_SK_NUM)
            Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR;
         else
            Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR - KD61Data[iSp-1].HSC_SK_NUM;
      }

      //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
      if (Cur_Num > 0 ) {
         //データ個数
         n += Cur_Num;

         // 平均値の計算
         for (j = 0; j < Cur_Num; j++ ) {
             if (AS_Flag == 0) {  // 圧面
                dAve += KD61Data[iSp-1].HSC_A_CH[j];
                if (KD61Data[iSp-1].HSC_A_CH[j] > dMax)
                   dMax = KD61Data[iSp-1].HSC_A_CH[j];
                if (KD61Data[iSp-1].HSC_A_CH[j] < dMin)
                   dMin = KD61Data[iSp-1].HSC_A_CH[j];
                // 規格チェック
                if (!(KD61Data[iSp-1].HSC_A_CH[j] >= KD61Data[iSp-1].HSC_A_MIN &&
                      KD61Data[iSp-1].HSC_A_CH[j] <= KD61Data[iSp-1].HSC_A_MAX))
                   ErrorNum++;
             } else {   // 側面
                dAve += KD61Data[iSp-1].HSC_S_CH[j];
                if (KD61Data[iSp-1].HSC_S_CH[j] > dMax)
                   dMax = KD61Data[iSp-1].HSC_S_CH[j];
                if (KD61Data[iSp-1].HSC_S_CH[j] < dMin)
                   dMin = KD61Data[iSp-1].HSC_S_CH[j];
                // 規格チェック
                if (!(KD61Data[iSp-1].HSC_S_CH[j] >= KD61Data[iSp-1].HSC_S_MIN &&
                      KD61Data[iSp-1].HSC_S_CH[j] <= KD61Data[iSp-1].HSC_S_MAX))
                   ErrorNum++;
             }
         }
      }

      if (n== 0 ) {
         SetData( 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, AS_Flag, A_No);
         return ;
      }

      // 工程能力計算
      //全体の平均値
      dAve = dAve/n;

      dR = dMax - dMin ;

      //σの計算
      dSigma = 0.0;
      if (n!= 1 ){
         for (i=iLotStart; i<iRtn ; i++ ) {
             for (j = 0; j < KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i]; j++ )
                 dSigma += (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] - dAve) *
                        (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] - dAve) ;
         }

         if (Cur_Num > 0 ) {
            for (i=0; i < Cur_Num; i++ ) {
                if (AS_Flag == 0) { // 圧面
                   dSigma += (KD61Data[iSp-1].HSC_A_CH[i] - dAve) *
                          (KD61Data[iSp-1].HSC_A_CH[i] - dAve) ;
                } else {   // 側面
                   dSigma += (KD61Data[iSp-1].HSC_S_CH[i] - dAve) *
                          (KD61Data[iSp-1].HSC_S_CH[i] - dAve) ;
                }
            }
            dSigma = sqrt(dSigma/(n-1)) ;
         }
      }

      //K
      if (AS_Flag == 0) { // 圧面
         dA = KD61Data[iSp-1].HSC_A_MAX + KD61Data[iSp-1].HSC_A_MIN ;
         dB = KD61Data[iSp-1].HSC_A_MAX - KD61Data[iSp-1].HSC_A_MIN ;
      } else { // 側面
         dA = KD61Data[iSp-1].HSC_S_MAX + KD61Data[iSp-1].HSC_S_MIN ;
         dB = KD61Data[iSp-1].HSC_S_MAX - KD61Data[iSp-1].HSC_S_MIN ;
      }

      // Cp
      if (dSigma > 0.0 )
         dCp = dB/(6*dSigma) ;
      else
         dCp = 0.0 ;

      //K
      dK = fabs(dA*0.5-dAve);

      if (dB > 0.0 ){
         dK = dK/(dB*0.5);
      } else {
         dK = 0.0 ;
      }

      // dCpk
      dCpk = (1-dK)*dCp ;

      //不良率
      dFuryo =(double)ErrorNum/(double)n * 100.0;

      SetData( n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo, AS_Flag, A_No );

      return ;
   } else {  // HSD
      for (i=iLotStart; i < iRtn ; i++ ) {
          if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i] == 0 ) continue ;

          //履歴データ個数
          n += KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i] ;

          dAve += KD63WData[iLinkSp-1].HSD_AVE[AS_Flag][i] *
                  KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i];

          // 平均値の計算
          for (j=0; j< KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i]; j++ ) {
              if (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] > dMax )
                 dMax = KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j];

              if (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] < dMin )
                 dMin = KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j];

              // 規格チェック
              if (!(KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] >= KD63WData[iLinkSp-1].HSD_MIN[AS_Flag][i] &&
                  KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] <= KD63WData[iLinkSp-1].HSD_MAX[AS_Flag][i]))
                 ErrorNum++;
          }
      }

      // 現在計測データ数
      if (AS_Flag == 0) { // 圧面
         if (KD61Data[iSp-1].HSD_SK_NUM_CUR <= KD61Data[iSp-1].HSD_SK_NUM)
            Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR;
         else
            Cur_Num = KD61Data[iSp-1].HSD_SK_NUM;
      } else {    // 側面
         if (KD61Data[iSp-1].HSD_SK_NUM_CUR <= KD61Data[iSp-1].HSD_SK_NUM)
            Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR;
         else
            Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR - KD61Data[iSp-1].HSD_SK_NUM;
      }

      //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
      if (Cur_Num > 0 ) {
         //データ個数
         n += Cur_Num ;

         // 平均値の計算
         for (j=0; j < Cur_Num; j++ ) {
             if (AS_Flag == 0) {  // 圧面
                dAve += KD61Data[iSp-1].HSD_A_CH[j];
                if (KD61Data[iSp-1].HSD_A_CH[j] > dMax)
                   dMax = KD61Data[iSp-1].HSD_A_CH[j];
                if (KD61Data[iSp-1].HSD_A_CH[j] < dMin)
                   dMin = KD61Data[iSp-1].HSD_A_CH[j];
                // 規格チェック
                if (!(KD61Data[iSp-1].HSD_A_CH[j] >= KD61Data[iSp-1].HSD_A_MIN &&
                      KD61Data[iSp-1].HSD_A_CH[j] <= KD61Data[iSp-1].HSD_A_MAX))
                   ErrorNum++;
             } else {   // 側面
                dAve += KD61Data[iSp-1].HSD_S_CH[j];
                if (KD61Data[iSp-1].HSD_S_CH[j] > dMax)
                   dMax = KD61Data[iSp-1].HSD_S_CH[j];
                if (KD61Data[iSp-1].HSD_S_CH[j] < dMin)
                   dMin = KD61Data[iSp-1].HSD_S_CH[j];
                // 規格チェック
                if (!(KD61Data[iSp-1].HSD_S_CH[j] >= KD61Data[iSp-1].HSD_S_MIN &&
                      KD61Data[iSp-1].HSD_S_CH[j] <= KD61Data[iSp-1].HSD_S_MAX))
                   ErrorNum++;
             }
         }
      }

      if (n== 0 ) {
         SetData(0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, AS_Flag, A_No);
         return ;
      }

      //全体の平均値
      dAve = dAve/n;

      dR = dMax - dMin ;

      //σの計算
      dSigma = 0.0;
      if (n!= 1 ){
         for (i=iLotStart; i<iRtn ; i++ ) {
             for (j=0; j< KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i]; j++ )
                 dSigma += (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] - dAve) *
                        (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] - dAve) ;
         }

         if (Cur_Num > 0 ) {
            for (i = 0; i < Cur_Num; i++ ) {
                if (AS_Flag == 0) { // 圧面
                   dSigma += (KD61Data[iSp-1].HSD_A_CH[i] - dAve) *
                          (KD61Data[iSp-1].HSD_A_CH[i] - dAve) ;
                } else {   // 側面
                   dSigma += (KD61Data[iSp-1].HSD_S_CH[i] - dAve) *
                          (KD61Data[iSp-1].HSD_S_CH[i] - dAve) ;
                }
            }
            dSigma = sqrt(dSigma/(n-1)) ;
         }
      }

      //K
      if (AS_Flag == 0) { // 圧面
         dA = KD61Data[iSp-1].HSD_A_MAX + KD61Data[iSp-1].HSD_A_MIN ;
         dB = KD61Data[iSp-1].HSD_A_MAX - KD61Data[iSp-1].HSD_A_MIN ;
      } else { // 側面
         dA = KD61Data[iSp-1].HSD_S_MAX + KD61Data[iSp-1].HSD_S_MIN ;
         dB = KD61Data[iSp-1].HSD_S_MAX - KD61Data[iSp-1].HSD_S_MIN ;
      }

      // Cp
      if (dSigma > 0.0 )
         dCp = dB/(6*dSigma) ;
      else
         dCp = 0.0 ;

      //K
      dK = fabs(dA*0.5-dAve);

      if (dB > 0.0 ){
         dK = dK/(dB*0.5);
      } else {
         dK = 0.0 ;
      }

      // dCpk
      dCpk = (1-dK)*dCp ;

      //不良率
      dFuryo =(double)ErrorNum/(double)n * 100.0;

      SetData(n, dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo, AS_Flag, A_No );

      return ;
   }
}

// 測定履歴作画用データを求める
// iSp:      SampleNo
// AS_Flag:  0: 圧面工程能力図
//           1: 側面工程能力図
// A_No:     1: Ｈｓｃ
//           2: Ｈｓｄ
void SetRirekiData(int iSp, int AS_Flag, int A_No)
{
  int i,j, n, iLotStart;
  int iRRR;
  AnsiString str;
  char Xstr[50][5];
  double Max[50];
  double Min[50];
  double Val[50];

  double maxa =-9999999.0 ;
  double mina = 9999999.0;
  int Cur_Num;

  if (!(A_No == 1 || A_No == 2))
     return;

  if (!(AS_Flag == 0 || AS_Flag == 1))
     return;

   if (A_No == 1 && AS_Flag == 1 && KD61Data[iSp-1].SOKUTE_KBN1 == 1)
      return;

   if (A_No == 1 && AS_Flag == 0 && KD61Data[iSp-1].SOKUTE_KBN1 == 2)
      return;

   if (A_No == 2 && AS_Flag == 1 && KD61Data[iSp-1].SOKUTE_KBN2 == 1)
      return;

   if (A_No == 2 && AS_Flag == 0 && KD61Data[iSp-1].SOKUTE_KBN2 == 2)
      return;

  // 作画用変数の初期化
  for (i=0; i<LOTMAX*5; i++ ){
      memset( Xstr[i], 0x0, 5 );
      Max[i] = 0.0;
      Min[i] = 0.0;
      Val[i] = 0.0;
  }

  //表示データを求める
  int iLinkSp=0;
  if (KD61Data[iSp-1].LINK == 0 ){
     iLinkSp = iSp ;
  } else {
     iLinkSp = KD61Data[iSp-1].LINK;
  }

  // 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
  int iRtn =  CheckLotNo( iSp ) ;
  if (iRtn <0 ) return ;

  if (iRtn <= (LOTMAX-1) )
     iLotStart = 0;
  else
     iLotStart = iRtn-LOTMAX + 1 ;

  if (A_No == 1) {           // Hsc
     //履歴ﾃﾞｰﾀ
     n=0;
     for (i=iLotStart; i < iRtn ; i++ ) {
         if (KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i] > 0 ) {
            // 最大値、最小値、平均値の計算
            Max[i-iLotStart] = maxa;
            Min[i-iLotStart] = mina ;

            for (j=0; j<KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i]; j++ ) {
                if (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] > Max[i-iLotStart])
                   Max[i-iLotStart] = KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j];

                if (KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] < Min[i-iLotStart])
                   Min[i-iLotStart] = KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j];

                Val[i-iLotStart] += KD63WData[iLinkSp-1].HSC_CH[AS_Flag][i][j] ;
            }

            Val[i-iLotStart] = Val[i-iLotStart]/KD63WData[iLinkSp-1].HSC_SOKUTEI_NM[AS_Flag][i] ;
         }

         str = KD63WData[iLinkSp-1].LOTNO[i] ;
         if (str.Length() > 5 )
            str = str.Delete(1,1);

         strncpy(Xstr[i-iLotStart],str.c_str() , str.Length());

         n += 1;
     }

     // 現在計測データ数
     if (AS_Flag == 0) { // 圧面
        if (KD61Data[iSp-1].HSC_SK_NUM_CUR <= KD61Data[iSp-1].HSC_SK_NUM)
           Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR;
        else
           Cur_Num = KD61Data[iSp-1].HSC_SK_NUM;
     } else {    // 側面
        if (KD61Data[iSp-1].HSC_SK_NUM_CUR <= KD61Data[iSp-1].HSC_SK_NUM)
           Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR;
        else
           Cur_Num = KD61Data[iSp-1].HSC_SK_NUM_CUR - KD61Data[iSp-1].HSC_SK_NUM;
     }

     //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
     iRRR = iRtn ;
     if (iRtn >= LOTMAX )
        iRRR = 9;

     if (Cur_Num > 0 ) {
        //計測データ中の最大値と最小値
        Max[iRRR] = maxa;
        Min[iRRR] = mina ;
        for (i=0; i < Cur_Num; i++ ){
            if (AS_Flag == 0) { // 圧面
               if (KD61Data[iSp-1].HSC_A_CH[i] > Max[iRRR])
                  Max[iRRR] = KD61Data[iSp-1].HSC_A_CH[i];
               if (KD61Data[iSp-1].HSC_A_CH[i] < Min[iRRR])
                  Min[iRRR] = KD61Data[iSp-1].HSC_A_CH[i];
            } else { // 側面
               if (KD61Data[iSp-1].HSC_S_CH[i] > Max[iRRR])
                  Max[iRRR] = KD61Data[iSp-1].HSC_S_CH[i];
               if (KD61Data[iSp-1].HSC_S_CH[i] < Min[iRRR])
                  Min[iRRR] = KD61Data[iSp-1].HSC_S_CH[i];
            }
        }

        // 平均値の計算
        for (i=0; i < Cur_Num; i++ ) {
            if (AS_Flag == 0)
               Val[iRRR] += KD61Data[iSp-1].HSC_A_CH[i] ;
            else
               Val[iRRR] += KD61Data[iSp-1].HSC_S_CH[i] ;
        }
        Val[iRRR] = Val[iRRR]/Cur_Num;
     }

     str = KD61Data[iSp-1].LOTNO ;
     if (str.Length() > 5 ) str = str.Delete(1,1);
     strncpy(Xstr[iRRR],str.c_str(), str.Length() );
     n += 1;

     if (AS_Flag == 0)
        DrawRireki1( Form1->GraphyImg_Hsc1, n , &Xstr[0][0], Max, Min, Val, iRRR,
                    (double)KD61Data[iSp-1].HSC_A_MIN, (double)KD61Data[iSp-1].HSC_A_MAX);
     else
        DrawRireki1( Form1->GraphyImg_Hsc2, n , &Xstr[0][0], Max, Min, Val, iRRR,
                    (double)KD61Data[iSp-1].HSC_S_MIN, (double)KD61Data[iSp-1].HSC_S_MAX);

     return ;
  } else {  // HSD
     //履歴ﾃﾞｰﾀ
     n=0;
     for (i=iLotStart; i < iRtn ; i++ ) {
         if (KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i] > 0 ) {
            // 最大値、最小値、平均値の計算
            Max[i-iLotStart] = maxa;
            Min[i-iLotStart] = mina ;

            for (j=0; j<KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i]; j++ ) {
                if (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] > Max[i-iLotStart])
                   Max[i-iLotStart] = KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j];

                if (KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] < Min[i-iLotStart])
                   Min[i-iLotStart] = KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j];

                Val[i-iLotStart] += KD63WData[iLinkSp-1].HSD_CH[AS_Flag][i][j] ;
            }

            Val[i-iLotStart] = Val[i-iLotStart]/KD63WData[iLinkSp-1].HSD_SOKUTEI_NM[AS_Flag][i] ;
         }

         str = KD63WData[iLinkSp-1].LOTNO[i] ;
         if (str.Length() > 5 )
            str = str.Delete(1,1);

         strncpy(Xstr[i-iLotStart],str.c_str() , str.Length());

         n += 1;
     }

     // 現在計測データ数
     if (AS_Flag == 0) { // 圧面
        if (KD61Data[iSp-1].HSD_SK_NUM_CUR <= KD61Data[iSp-1].HSD_SK_NUM)
           Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR;
        else
           Cur_Num = KD61Data[iSp-1].HSD_SK_NUM;
     } else {    // 側面
        if (KD61Data[iSp-1].HSD_SK_NUM_CUR <= KD61Data[iSp-1].HSD_SK_NUM)
           Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR;
        else
           Cur_Num = KD61Data[iSp-1].HSD_SK_NUM_CUR - KD61Data[iSp-1].HSD_SK_NUM;
     }

     //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
     iRRR = iRtn ;
     if (iRtn >= LOTMAX )
        iRRR = 9;

     if (Cur_Num > 0 ) {
        //計測データ中の最大値と最小値
        Max[iRRR] = maxa;
        Min[iRRR] = mina ;
        for (i=0; i < Cur_Num; i++ ){
            if (AS_Flag == 0) { // 圧面
               if (KD61Data[iSp-1].HSD_A_CH[i] > Max[iRRR])
                  Max[iRRR] = KD61Data[iSp-1].HSD_A_CH[i];
               if (KD61Data[iSp-1].HSD_A_CH[i] < Min[iRRR])
                  Min[iRRR] = KD61Data[iSp-1].HSD_A_CH[i];
            } else { // 側面
               if (KD61Data[iSp-1].HSD_S_CH[i] > Max[iRRR])
                  Max[iRRR] = KD61Data[iSp-1].HSD_S_CH[i];
               if (KD61Data[iSp-1].HSD_S_CH[i] < Min[iRRR])
                  Min[iRRR] = KD61Data[iSp-1].HSD_S_CH[i];
            }
        }

        // 平均値の計算
        for (i=0; i < Cur_Num; i++ ) {
            if (AS_Flag == 0)
               Val[iRRR] += KD61Data[iSp-1].HSD_A_CH[i] ;
            else
               Val[iRRR] += KD61Data[iSp-1].HSD_S_CH[i] ;
        }
        Val[iRRR] = Val[iRRR]/Cur_Num;
     }

     str = KD61Data[iSp-1].LOTNO ;
     if (str.Length() > 5 ) str = str.Delete(1,1);
     strncpy(Xstr[iRRR],str.c_str(), str.Length() );
     n += 1;

     if (AS_Flag == 0)
        DrawRireki( Form1->GraphyImg_Hsd1, n , &Xstr[0][0], Max, Min, Val, iRRR,
                    KD61Data[iSp-1].HSD_A_MIN, KD61Data[iSp-1].HSD_A_MAX);
     else
        DrawRireki( Form1->GraphyImg_Hsd2, n , &Xstr[0][0], Max, Min, Val, iRRR,
                    KD61Data[iSp-1].HSD_S_MIN, KD61Data[iSp-1].HSD_S_MAX);

     return ;
  }
}

// 小数点1桁表示 (Copy from TKS13)
// 測定履歴作画関数
// GraphName : 作画ｺﾝﾄﾛｰﾙ
// n         : 出力ロット個数
// Xstr      : ロットNO
// Max       : ﾛｯﾄNO毎の規格上限値
// Min       : ﾛｯﾄNO毎の規格下限値
// Val       : ﾛｯﾄNO毎の測定値平均値
// T_MinY    : 規格の下限
// T_MaxY    : 規格の上限
void DrawRireki(TImage *GraphName,int n, char *Pstr, double Max[10], double Min[10], double Val[10], int iCur,
                       double T_MinY, double T_MaxY)
{
    int i;
    int x1,x2,y1,y2, x3, y3 ;     //線を描画するときの座標
    double MaxY,MinY;    //Y軸　読み込んだデータの中の最大値、最小値
    double ScaleMin,ScaleVal;   //目盛りの最大値、最小値、間隔
    int ItemWidth;
    int CharWidth;          //Y軸座標値を描画するための余白
    int CharHeight;         //X軸座標値を描画するための余白
    int FontHeight;
    double XWidth,YHeight,ScaleHeight;
    int PreScaleNo,MasterScaleNo,ScaleNo; //目盛りの予備数、主目盛り数
    int ImageH,ImageW;      //イメージの高さ、幅
    AnsiString str;
    char Xstr[10][5];

    memcpy(Xstr, Pstr, 50);

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

    //最小値の検索
    //MaxY = KD31Data[SamplePositionIdx-1].LD_TR_MAX ;
    //MinY = Min[0];

    //最大値、最小値の検索
    MaxY = T_MaxY ;
    MinY = T_MinY;

    for ( i = 0; i < n; i++ ) {
         //最小値の検索
        if ( MinY > Min[i] ) MinY = Min[i];
        if ( MinY > Max[i] ) MinY = Max[i];
    }

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MinY =MaxY-1.0 ;
    }
    if( MinY > MaxY ) MinY = 0.0 ;

    //目盛りの間隔、最小値、最大値の設定
    ScaleVal = SetScalVal( MaxY, MinY, 4 );
    ScaleMin = MaxY - ( ScaleVal *  (ScaleNo-1));

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
          memcpy(sTmp,Xstr[i],5);
          sTmp[5] = NULL ;
          if( i <n ){
           GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sTmp);
          }
    }

    AnsiString str1;
    for ( i = 0; i < ScaleNo; i++ ){

        //2003/01/06 E.Takase
        //if( i== ScaleNo-1 ) {
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

        if( i== ScaleNo-1 ) {
            str = FormatFloat ("#0.0", MaxY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length())+str;
        }else{
            double a =  ScaleMin + ( ScaleVal * i ) ;
            if( a >= 0.0  ){
               str = FormatFloat ("#0.0",  a );
               str1 = AnsiString::StringOfChar(' ', 7-str.Length())+str;
            }
        }

        GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
    }

    for ( i = 0; i <  n ; i++ ){

        if( Val[i] <=0.0 ) continue  ;

        //計測しているﾛｯﾄNOの場合色を変える
        if( i== iCur ) {
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

       if( Val[i] <=0.0 ) continue  ;

         //計測しているﾛｯﾄNOの場合色を変える
        if( i== iCur ) {
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

// 整数桁表示(Copy From TKS17)
// 測定履歴作画関数
// GraphName : 作画ｺﾝﾄﾛｰﾙ
// n         : 出力ロット個数
// Xstr      : ロットNO
// Max       : ﾛｯﾄNO毎の規格上限値
// Min       : ﾛｯﾄNO毎の規格下限値
// Val       : ﾛｯﾄNO毎の測定値平均値
// T_MinY    : 規格の下限
// T_MaxY    : 規格の上限
void DrawRireki1(TImage *GraphName,int n, char *Pstr, double Max[10], double Min[10], double Val[10], int iCur,
                       double T_MinY, double T_MaxY)
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
    char Xstr[10][5];

    memcpy(Xstr, Pstr, 50);

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

    //最大値、最小値の検索
    //MaxY = KD71Data[SamplePositionIdx-1].KOYU_MAX ;
    //MinY = KD71Data[SamplePositionIdx-1].KOYU_MIN;
    MaxY = T_MaxY;
    MinY = T_MinY;

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
          memcpy(sTmp,Xstr[i],5);
          sTmp[5] = NULL ;
          if( i <n ){
           GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sTmp);
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
            str = FormatFloat ("0",MinY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }else if( i== ScaleNo-1 ) {
            str = FormatFloat ("0", MaxY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }else if( i== 2 ){
            str = FormatFloat ("0", ScaleMid);
            str1 = AnsiString::StringOfChar(' ', 7-str.Length()) + str;
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 3.5 ),y1 - ( FontHeight / 2),str1);
        }
    }

    for ( i = 0; i <  n ; i++ ){

        if( Val[i] <=0.0 ) continue  ;

        //計測しているﾛｯﾄNOの場合色を変える
        if( i== iCur ) {
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
        if( i== iCur ) {
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

// 測定履歴作画関数
// GraphName : 作画ｺﾝﾄﾛｰﾙ
// n         : 出力ロット個数
// Xstr      : ロットNO
// Max       : ﾛｯﾄNO毎の規格上限値
// Min       : ﾛｯﾄNO毎の規格下限値
// Val       : ﾛｯﾄNO毎の測定値平均値
// T_MinY    : 規格の下限
// T_MaxY    : 規格の上限
void DrawRireki0(TImage *GraphName,int n, char *Pstr, double Max[10], double Min[10], double Val[10], int iCur,
                       double T_MinY, double T_MaxY)
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
    char Xstr[10][5];

    memcpy(Xstr, Pstr, 50);

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

    //最大値、最小値の検索
    MaxY = T_MaxY ;
    MinY = T_MinY;

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MaxY =MinY+1.0 ;
    }

    // 目盛りの間隔、最小値、最大値の設定
     ScaleVal = (MaxY-MinY)/(ScaleNo-1) ;
     ScaleMin = MinY ;

     if( ScaleMin < 0.0 ) ScaleMin = 0.0 ;
     ScaleMax = ScaleMin + ( ScaleVal *  ScaleNo);

     ScaleMid = SetScalVal0( MaxY, MinY);

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
          memcpy(sTmp,Xstr[i],5);
          sTmp[5] = NULL ;
          if( i <n ){
           GraphName->Canvas->TextOut(x1 - ( FontHeight ),y1+3, sTmp);
          }
    }

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
            str = FormatFloat ("#0.00", T_MinY );
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 2.5 ),y1 - ( FontHeight / 2),str);
        }else if( i== ScaleNo-1 ) {
              if( T_MinY == T_MaxY )
                 str = FormatFloat ("#0.00", T_MinY+1.0 );
              else
                 str = FormatFloat ("#0.00", T_MaxY);

              GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 2.5 ),y1 - ( FontHeight / 2),str);
        }else if( i== 2 ){
            str = FormatFloat ("#0.00", ScaleMid);
            GraphName->Canvas->TextOut
                        (x1 - ( FontHeight * 2.5 ),y1 - ( FontHeight / 2),str);
        }
    }

  //  if (KD03WData[SamplePositionIdx-1].LOTCNT <0 ) return ;

    for ( i = 0; i <  n ; i++ ){

        if( Val[i] <=0.0 ) continue  ;

        //計測しているﾛｯﾄNOの場合色を変える
        if( i== iCur ) {
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
        if( i== iCur ) {
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


        //if( y1 < HMin || y1 > HMax ) y1 = HMax ;
        //if( y2 < HMin || y2 > HMax ) y2 = HMin ;

        if( y1 <HMin && y2 <HMin ) continue ;
        if( y1 >HMax && y2 >HMax ) continue ;

        if( y1 > HMax )  y1 = HMax ;
        if( y2 < HMin )  y2 = HMin ;

        GraphName->Canvas->MoveTo(x1,y1);
        GraphName->Canvas->LineTo(x2,y2);

    }

}

//最大座標値と最小座標値から刻み大きさを求める
//dmax    :  最大座標値
//dMin    :  最小座標値
double SetScalVal(double dMax , double dMin, int sno )
{
  int i;
  double ScalVal ;
  double Val[41] = {  500.0,  450.0,  400.0,  350.0, 250.0,  200.0,
                      150.0,  100.0,   75.0,   65.0,  60.0,   55.0,
                       50.0,   45.0,   40.0,   35.0,  25.0,   20.0,
                       15.0,   10.0,    7.5,    6.5,   5.5,    5.0,
                        4.5,    4.0,    3.5,    3.0,   2.5,    2.0,
                        1.5,    1.0,    0.9,    0.8,   0.7,    0.6,
                        0.5,    0.4,    0.3,    0.2,    0.1         };


  ScalVal = 1.0 ;

  double DeltaD = (dMax-dMin)/sno;

  for( i=0; i<41; i++ )
  {
     if( DeltaD > Val[i] ) {
           if( i== 0) ScalVal = Val[i] ;
           else ScalVal = Val[i-1];
       break ;
      }

  }

  return ScalVal ;
}

double SetScalVal0(double dMax , double dMin )
{
  int i;
  double ScalVal, a;
  int    iScalVal ;
  double Val[66] = { 500.0, 450,400,350,        250.0,  200.0,  150.0,   100.0,  75.0,
                      65,60, 55,
                      50.0, 45,   40,35,        25.0,   20.0,   15.0,    10.0,   7.5,
                       6.5, 6,5.5,
                       5.0, 4.5,  4.0, 3.5,     2.5,    2.0,    1.5,     1.0,   0.75,
                       0.65,0.6,0.55,
                       0.5, 0.45, 0.4, 0.35,    0.25,   0.2,    0.15,    0.1,   0.075,
                       0.065,0.06, 0.055,
                       0.05,0.045,0.04,0.035,   0.025,  0.02,   0.015,   0.01,  0.0075 ,
                       0.005,0.0045, 0.004,0.0035, 0.0025, 0.002,  0.0015,  0.001, 0.00075 };


   ScalVal = (dMax+dMin)/2.0 ;

   iScalVal = int( ScalVal) ;
    a = ScalVal-(double)iScalVal ;

    if( a == 0.0 ) return ScalVal ;

    for( i=0; i<66; i++ )
    {
      if( a > Val[i] ) {
           if( i== 0) ScalVal = Val[i]+iScalVal ;
           else ScalVal = Val[i-1]+iScalVal;
         break ;
       }

    }
  return ScalVal ;
}

// 工程能力情報を画面へセットする
// dn       : n
// dMin     : Min
// dMax     : Max
// dAve     : Ave
// dR       : R
// dSigma   : σ
// dCp      : Cp
// dCpk     : Cpk
// dK       : K
// dFuryo   : 不良率
// AS_Flag  : ０：圧面; １：側面
// A_No     : 1: Hsc; 2: Hsd
void SetData( int dn, double dMin,double  dMax,double  dAve,double  dR,double  dSigma,
              double dCp, double  dCpk,double  dK, double dFuryo, int AS_Flag, int A_No)
{

   //画面へデータ設定
   if (A_No == 1) { // Hsc
      if (AS_Flag == 0) { // 圧面
         Form1->Pan_Hsc_N1->Caption = FormatFloat("#0", dn );
         Form1->Pan_Hsc_Min1->Caption = FormatFloat("#0.00", dMin );
         Form1->Pan_Hsc_Max1->Caption = FormatFloat("#0.00", dMax );
         Form1->Pan_Hsc_Ave1->Caption = FormatFloat("#0.000", dAve );

         Form1->Pan_Hsc_R1->Caption = FormatFloat("#0.00000", dR );
         Form1->Pan_Hsc_Siguma1->Caption = FormatFloat("#0.00000", dSigma );

         if (fabs(dCp) > COM_DIFF && dCp < S_Cp) {
            //Beep();
            Form1->Pan_Hsc_Cp1->Font->Color = clRed;
         } else
            Form1->Pan_Hsc_Cp1->Font->Color = clWindowText;
         Form1->Pan_Hsc_Cp1->Caption = FormatFloat("#0.00", dCp );

         if (fabs(dCpk) > COM_DIFF && dCpk < S_Cpk) {
            //Beep();
            Form1->Pan_Hsc_Cpk1->Font->Color = clRed;
         } else
            Form1->Pan_Hsc_Cpk1->Font->Color = clWindowText;
         Form1->Pan_Hsc_Cpk1->Caption = FormatFloat("#0.00", dCpk );

         Form1->Pan_Hsc_K1->Caption = FormatFloat("#0.000", dK );
         Form1->Pan_Hsc_P1->Caption = FormatFloat("#0.000", dFuryo );
      } else {   // 側面
         Form1->Pan_Hsc_N2->Caption = FormatFloat("#0", dn );
         Form1->Pan_Hsc_Min2->Caption = FormatFloat("#0.00", dMin );
         Form1->Pan_Hsc_Max2->Caption = FormatFloat("#0.00", dMax );
         Form1->Pan_Hsc_Ave2->Caption = FormatFloat("#0.000", dAve );

         Form1->Pan_Hsc_R2->Caption = FormatFloat("#0.00000", dR );
         Form1->Pan_Hsc_Siguma2->Caption = FormatFloat("#0.00000", dSigma );

         if (fabs(dCp) > COM_DIFF && dCp < S_Cp) {
            //Beep();
            Form1->Pan_Hsc_Cp2->Font->Color = clRed;
         } else
            Form1->Pan_Hsc_Cp2->Font->Color = clWindowText;
         Form1->Pan_Hsc_Cp2->Caption = FormatFloat("#0.00", dCp );

         if (fabs(dCpk) > COM_DIFF && dCpk < S_Cpk) {
            //Beep();
            Form1->Pan_Hsc_Cpk2->Font->Color = clRed;
         } else
            Form1->Pan_Hsc_Cpk2->Font->Color = clWindowText;
         Form1->Pan_Hsc_Cpk2->Caption = FormatFloat("#0.00", dCpk );

         Form1->Pan_Hsc_K2->Caption = FormatFloat("#0.000", dK );
         Form1->Pan_Hsc_P2->Caption = FormatFloat("#0.000", dFuryo );
      }
   } else { // Hsd
      if (AS_Flag == 0) { // 圧面
         Form1->Pan_Hsd_N1->Caption = FormatFloat("#0", dn );
         Form1->Pan_Hsd_Min1->Caption = FormatFloat("#0.00", dMin );
         Form1->Pan_Hsd_Max1->Caption = FormatFloat("#0.00", dMax );
         Form1->Pan_Hsd_Ave1->Caption = FormatFloat("#0.000", dAve );

         Form1->Pan_Hsd_R1->Caption = FormatFloat("#0.00000", dR );
         Form1->Pan_Hsd_Siguma1->Caption = FormatFloat("#0.00000", dSigma );

         if (fabs(dCp) > COM_DIFF && dCp < S_Cp) {
            //Beep();
            Form1->Pan_Hsd_Cp1->Font->Color = clRed;
         } else
            Form1->Pan_Hsd_Cp1->Font->Color = clWindowText;
         Form1->Pan_Hsd_Cp1->Caption = FormatFloat("#0.00", dCp );

         if (fabs(dCpk) > COM_DIFF && dCpk < S_Cpk) {
            //Beep();
            Form1->Pan_Hsd_Cpk1->Font->Color = clRed;
         } else
            Form1->Pan_Hsd_Cpk1->Font->Color = clWindowText;
         Form1->Pan_Hsd_Cpk1->Caption = FormatFloat("#0.00", dCpk );

         Form1->Pan_Hsd_K1->Caption = FormatFloat("#0.000", dK );
         Form1->Pan_Hsd_P1->Caption = FormatFloat("#0.000", dFuryo );
      } else {   // 側面
         Form1->Pan_Hsd_N2->Caption = FormatFloat("#0", dn );
         Form1->Pan_Hsd_Min2->Caption = FormatFloat("#0.00", dMin );
         Form1->Pan_Hsd_Max2->Caption = FormatFloat("#0.00", dMax );
         Form1->Pan_Hsd_Ave2->Caption = FormatFloat("#0.000", dAve );

         Form1->Pan_Hsd_R2->Caption = FormatFloat("#0.00000", dR );
         Form1->Pan_Hsd_Siguma2->Caption = FormatFloat("#0.00000", dSigma );

         if (fabs(dCp) > COM_DIFF && dCp < S_Cp) {
            //Beep();
            Form1->Pan_Hsd_Cp2->Font->Color = clRed;
         } else
            Form1->Pan_Hsd_Cp2->Font->Color = clWindowText;
         Form1->Pan_Hsd_Cp2->Caption = FormatFloat("#0.00", dCp );

         if (fabs(dCpk) > COM_DIFF && dCpk < S_Cpk) {
            //Beep();
            Form1->Pan_Hsd_Cpk2->Font->Color = clRed;
         } else
            Form1->Pan_Hsd_Cpk2->Font->Color = clWindowText;
         Form1->Pan_Hsd_Cpk2->Caption = FormatFloat("#0.00", dCpk );

         Form1->Pan_Hsd_K2->Caption = FormatFloat("#0.000", dK );
         Form1->Pan_Hsd_P2->Caption = FormatFloat("#0.000", dFuryo );
      }
   }
}


