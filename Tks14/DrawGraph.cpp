/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１４）                  *
*  file   name   : DrawGraph.cpp                                       *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾘｰﾄﾞ線引張強度測定履歴、工程能力作画関数            *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

int SetRirekiData(void ) ;
void DispKoutei(int);
int  CheckLotNo(int ) ;
void SetData( int,double ,double ,double  ,double ,double ,double , double ,double ,  double ) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] , int );
void SetRirekiData(int ) ;
double SetScalVal(double , double, int ) ;

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
            DispKoutei(iSp) ;
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
   if(  KD41Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD41Data[iSp-1].LINK;
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
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD43WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

           //履歴データ個数
           n += KD43WData[iLinkSp-1].SOKUTEI_NM[i] ;

           // 平均値の計算
           dAve += KD43WData[iLinkSp-1].SOKUTE_AVE[i]*KD43WData[iLinkSp-1].SOKUTEI_NM[i];

           for( j=0; j< KD43WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

                if( KD43WData[iLinkSp-1].SOKUTEI[i][j] > dMax ) dMax = KD43WData[iLinkSp-1].SOKUTEI[i][j];
                if( KD43WData[iLinkSp-1].SOKUTEI[i][j] < dMin ) dMin = KD43WData[iLinkSp-1].SOKUTEI[i][j];

                 //不合格ﾃﾞｰﾀのﾁｪｯｸ
                if(  KD43WData[iLinkSp-1].SOKUTEI[i][j] <  KD43WData[iLinkSp-1].LD_HP_MIN[i] )
                 FuryoCnt +=1 ;
           }
   }

   //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
   if( KD41Data[iSp-1].SOKUTEI_NM_CUR != 0 )
   {
            //データ個数
            n += KD41Data[iSp-1].SOKUTEI_NM_CUR ;

            // 平均値の計算
            for( j=0; j< KD41Data[iSp-1].SOKUTEI_NM_CUR; j++ ) {
                dAve += KD41Data[iSp-1].SOKUTEICHI[j];

               if( KD41Data[iSp-1].SOKUTEICHI[j] > dMax ) dMax = KD41Data[iSp-1].SOKUTEICHI[j];
               if( KD41Data[iSp-1].SOKUTEICHI[j] < dMin ) dMin = KD41Data[iSp-1].SOKUTEICHI[j];

               //不合格ﾃﾞｰﾀのﾁｪｯｸ
                if( KD41Data[iSp-1].SOKUTEICHI[j] <  KD41Data[iSp-1].LD_HP_MIN )
                 FuryoCnt +=1 ;
           }

   }

   if( n== 0 ) {
       SetData( 0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
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
           for( int j=0; j< KD43WData[iLinkSp-1].SOKUTEI_NM[i]; j++ )
                dSigma += (KD43WData[iLinkSp-1].SOKUTEI[i][j] - dAve)*(KD43WData[iLinkSp-1].SOKUTEI[i][j] - dAve) ;
       }

       if( KD41Data[iSp-1].SOKUTEI_NM_CUR != 0 ) {
           for( i=0; i<KD41Data[iSp-1].SOKUTEI_NM_CUR ; i++ )
                dSigma += (KD41Data[iSp-1].SOKUTEICHI[i] - dAve)*(KD41Data[iSp-1].SOKUTEICHI[i] - dAve) ;
       }

       dSigma = sqrt(dSigma/(double)(n-1)) ;
    }

       // Cp
       if( dSigma > 0.0 )
           dCp = fabs(dAve-KD41Data[iSp-1].LD_HP_MIN)/(3*dSigma) ;
       else
           dCp = 0.0 ;

       //K
       dK = 0.0;

       // dCpk
       dCpk = 0.0 ;

        //dCp, dCpkの規格ﾁｪｯｸ
       if( iOption == 2 ){
       if( dCp < 1.33 ){
         //Beep();
         Form1->Pnl33->Font->Color = clRed ;
       }else{
         Form1->Pnl33->Font->Color = clBlack ;
       }
       }
       //不良率
       dFuryo =((double)FuryoCnt/(double)n)*100.0;

       SetData( n,dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

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
  AnsiString str;
  char Xstr[50][5];
  double Max[50];
  double Min[50];
  double Val[50];

  double maxa =-9999999.0 ;
  double mina = 9999999.0;


  // 作画用変数の初期化
   for(i=0; i<LOTMAX*5; i++ ){
     memset( Xstr[i], 0x0, 5 );
     Max[i] = 0.0;
     Min[i] = 0.0;
     Val[i] = 0.0;
   }

   int iLinkSp=0;
   if(  KD41Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD41Data[iSp-1].LINK;
   }

   // 履歴ﾃﾞｰﾀの中にｶﾚﾝﾄロット番号のINDEXを探す
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

   if( iRtn <= (LOTMAX-1) )
     iLotStart = 0;
   else
     iLotStart = iRtn-LOTMAX + 1 ;

   //履歴ﾃﾞｰﾀ
   n=0;
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD43WData[iLinkSp-1].SOKUTEI_NM[i] != 0 ) {

              // 最大値、最小値、平均値の計算
              Max[i-iLotStart] = maxa;
              Min[i-iLotStart] = mina ;
              for(  j=0; j<KD43WData[iLinkSp-1].SOKUTEI_NM[i] ; j++ ){
                    if( KD43WData[iLinkSp-1].SOKUTEI[i][j] > Max[i-iLotStart] ) Max[i-iLotStart] = KD43WData[iLinkSp-1].SOKUTEI[i][j];
                    if( KD43WData[iLinkSp-1].SOKUTEI[i][j] < Min[i-iLotStart] ) Min[i-iLotStart] = KD43WData[iLinkSp-1].SOKUTEI[i][j];

                    Val[i-iLotStart] += KD43WData[iLinkSp-1].SOKUTEI[i][j] ;
              }

              Val[i-iLotStart] = Val[i-iLotStart]/KD43WData[iLinkSp-1].SOKUTEI_NM[i] ;
          }

          str = KD43WData[iLinkSp-1].LOTNO[i] ;
          if( str.Length() > 5 ) str = str.Delete(1,1);
          strncpy(Xstr[i-iLotStart],str.c_str() , str.Length());

          n += 1;
   }

   //ｶﾚﾝﾄｶｰｿﾙがある計測ﾃﾞｰﾀ
   iRRR = iRtn ;
   if( iRtn >= LOTMAX ) iRRR = 9;
   if( KD41Data[iSp-1].SOKUTEI_NM_CUR != 0 )
   {


         //計測データ中の最大値と最小値
         Max[iRRR] = maxa;
         Min[iRRR] = mina ;
         for( i=0; i< KD41Data[iSp-1].SOKUTEI_NM_CUR ; i++ ){
              if( KD41Data[iSp-1].SOKUTEICHI[i] > Max[iRRR] ) Max[iRRR] = KD41Data[iSp-1].SOKUTEICHI[i];
              if( KD41Data[iSp-1].SOKUTEICHI[i] < Min[iRRR] ) Min[iRRR] = KD41Data[iSp-1].SOKUTEICHI[i];
         }

         // 平均値の計算
         for( i=0; i< KD41Data[iSp-1].SOKUTEI_NM_CUR; i++ )
              Val[iRRR] += KD41Data[iSp-1].SOKUTEICHI[i] ;
         Val[iRRR] = Val[iRRR]/KD41Data[iSp-1].SOKUTEI_NM_CUR ;
   }

   str = KD41Data[iSp-1].LOTNO ;
   if( str.Length() > 5 ) str = str.Delete(1,1);
   strncpy(Xstr[iRRR],str.c_str(), str.Length() );
   n += 1;

   DrawRireki( Form1->GraphyImg, n , &Xstr[0][0], Max, Min, Val, iRRR) ;

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

    //最大値、最小値の検索
    MinY = KD41Data[SamplePositionIdx-1].LD_HP_MIN;

    MaxY = Max[0];
    for ( i = 0; i < n; i++ ) {
        //最大値の検索
        if ( MaxY < Max[i] ) MaxY = Max[i];
        if ( MaxY < Min[i] ) MaxY = Min[i];
    }

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MaxY =MinY+1.0 ;
    }

    if( MaxY < MinY ) MaxY = MinY + 1.0 ;

    //目盛りの間隔、最小値、最大値の設定
    ScaleVal = SetScalVal( MaxY, MinY, 4 );
    ScaleMin = MinY ;

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
            str = FormatFloat ("#0.0", MinY );
            str1 = AnsiString::StringOfChar(' ', 7-str.Length())+str;
        }else{
            str = FormatFloat ("#0.0", (ScaleMin + ( ScaleVal * i )));
            str1 = AnsiString::StringOfChar(' ', 7-str.Length())+str;
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
        GraphName->Canvas->Pen->Width = 2;      //線の太さ
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

/***********************************************************************
*  function name : double SetScalVal(double dMax, double dMin, int sno)*
*                  +--------------------------------------+            *
*          引  数  |   dmax    |  最大座標値              |            *
*                  |   dMin    |  最小座標値              |            *
*                  |   sno     |  等分数                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |          ｜刻みサイズ                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 最大座標値と最小座標値から刻み大きさを求める        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
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

  for( i=0; i<63; i++ )
  {
     if( DeltaD > Val[i] ) {
           if( i== 0)
              ScalVal = Val[i] ;
           else
              ScalVal = Val[i-1];
       break ;
      }

  }
  return ScalVal ;
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

void SetData( int iN, double dMin,double  dMax,double  dAve,double  dR,double  dSigma,
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
   Form1->Pnl43->Caption = FormatFloat("#0.000", dFuryo );

   Form1->Pnl41->Color = clMenu ;
   Form1->Pnl42->Color = clMenu ;
   Form1->Panel93->Color = clMenu ;
   Form1->Panel94->Color = clMenu ;

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
*  contents      : KD43Wから読み込んだﾃﾞｰﾀ中にに指定したロットNo       *
*                :  有るかどうか のチェック                            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  CheckLotNo(int iSp)
{

   int iLinkSp;

   int iFlag = -1;

    if(  KD41Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD41Data[iSp-1].LINK;
   }

   for( int i=0; i<  KD43WData[iLinkSp-1].LOTCNT; i++ ){
      if(  KD41Data[iSp-1].LOTNO ==  KD43WData[iLinkSp-1].LOTNO[i] )
      {
        iFlag = i ;
        break ;
       }
   }

   return iFlag ;
}



