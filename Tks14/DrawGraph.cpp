/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�S�j                  *
*  file   name   : DrawGraph.cpp                                       *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ذ�ސ��������x���藚���A�H���\�͍��֐�            *
*  written by    : �� ���N �iNKK unics Corp.)                          *
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
            DispKoutei(iSp) ;
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
   if(  KD41Data[iSp-1].LINK == 0 ){
       iLinkSp = iSp ;
   }else {
       iLinkSp = KD41Data[iSp-1].LINK;
   }

   // �����ް��̒��ɶ��ă��b�g�ԍ���INDEX��T��
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

   //�����ް�
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD43WData[iLinkSp-1].SOKUTEI_NM[i] == 0 ) continue ;

           //�����f�[�^��
           n += KD43WData[iLinkSp-1].SOKUTEI_NM[i] ;

           // ���ϒl�̌v�Z
           dAve += KD43WData[iLinkSp-1].SOKUTE_AVE[i]*KD43WData[iLinkSp-1].SOKUTEI_NM[i];

           for( j=0; j< KD43WData[iLinkSp-1].SOKUTEI_NM[i]; j++ ) {

                if( KD43WData[iLinkSp-1].SOKUTEI[i][j] > dMax ) dMax = KD43WData[iLinkSp-1].SOKUTEI[i][j];
                if( KD43WData[iLinkSp-1].SOKUTEI[i][j] < dMin ) dMin = KD43WData[iLinkSp-1].SOKUTEI[i][j];

                 //�s���i�ް�������
                if(  KD43WData[iLinkSp-1].SOKUTEI[i][j] <  KD43WData[iLinkSp-1].LD_HP_MIN[i] )
                 FuryoCnt +=1 ;
           }
   }

   //���Ķ��ق�����v���ް�
   if( KD41Data[iSp-1].SOKUTEI_NM_CUR != 0 )
   {
            //�f�[�^��
            n += KD41Data[iSp-1].SOKUTEI_NM_CUR ;

            // ���ϒl�̌v�Z
            for( j=0; j< KD41Data[iSp-1].SOKUTEI_NM_CUR; j++ ) {
                dAve += KD41Data[iSp-1].SOKUTEICHI[j];

               if( KD41Data[iSp-1].SOKUTEICHI[j] > dMax ) dMax = KD41Data[iSp-1].SOKUTEICHI[j];
               if( KD41Data[iSp-1].SOKUTEICHI[j] < dMin ) dMin = KD41Data[iSp-1].SOKUTEICHI[j];

               //�s���i�ް�������
                if( KD41Data[iSp-1].SOKUTEICHI[j] <  KD41Data[iSp-1].LD_HP_MIN )
                 FuryoCnt +=1 ;
           }

   }

   if( n== 0 ) {
       SetData( 0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 );
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

        //dCp, dCpk�̋K�i����
       if( iOption == 2 ){
       if( dCp < 1.33 ){
         //Beep();
         Form1->Pnl33->Font->Color = clRed ;
       }else{
         Form1->Pnl33->Font->Color = clBlack ;
       }
       }
       //�s�Ǘ�
       dFuryo =((double)FuryoCnt/(double)n)*100.0;

       SetData( n,dMin, dMax, dAve, dR, dSigma, dCp, dCpk, dK, dFuryo );

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
  AnsiString str;
  char Xstr[50][5];
  double Max[50];
  double Min[50];
  double Val[50];

  double maxa =-9999999.0 ;
  double mina = 9999999.0;


  // ���p�ϐ��̏�����
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

   // �����ް��̒��ɶ��ă��b�g�ԍ���INDEX��T��
   int iRtn =  CheckLotNo( iSp ) ;
   if( iRtn <0 ) return ;

   if( iRtn <= (LOTMAX-1) )
     iLotStart = 0;
   else
     iLotStart = iRtn-LOTMAX + 1 ;

   //�����ް�
   n=0;
   for( i=iLotStart; i < iRtn ; i++ ) {

          if( KD43WData[iLinkSp-1].SOKUTEI_NM[i] != 0 ) {

              // �ő�l�A�ŏ��l�A���ϒl�̌v�Z
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

   //���Ķ��ق�����v���ް�
   iRRR = iRtn ;
   if( iRtn >= LOTMAX ) iRRR = 9;
   if( KD41Data[iSp-1].SOKUTEI_NM_CUR != 0 )
   {


         //�v���f�[�^���̍ő�l�ƍŏ��l
         Max[iRRR] = maxa;
         Min[iRRR] = mina ;
         for( i=0; i< KD41Data[iSp-1].SOKUTEI_NM_CUR ; i++ ){
              if( KD41Data[iSp-1].SOKUTEICHI[i] > Max[iRRR] ) Max[iRRR] = KD41Data[iSp-1].SOKUTEICHI[i];
              if( KD41Data[iSp-1].SOKUTEICHI[i] < Min[iRRR] ) Min[iRRR] = KD41Data[iSp-1].SOKUTEICHI[i];
         }

         // ���ϒl�̌v�Z
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
    int x1,x2,y1,y2, x3, y3 ;     //����`�悷��Ƃ��̍��W
    double MaxY,MinY;    //Y���@�ǂݍ��񂾃f�[�^�̒��̍ő�l�A�ŏ��l
    double ScaleMin,ScaleVal;   //�ڐ���̍ő�l�A�ŏ��l�A�Ԋu
    int ItemWidth;
    int CharWidth;          //Y�����W�l��`�悷�邽�߂̗]��
    int CharHeight;         //X�����W�l��`�悷�邽�߂̗]��
    int FontHeight;
    double XWidth,YHeight,ScaleHeight;
    int PreScaleNo,MasterScaleNo,ScaleNo; //�ڐ���̗\�����A��ڐ��萔
    int ImageH,ImageW;      //�C���[�W�̍����A��
    AnsiString str;
    char Xstr[10][5];

    memcpy(Xstr, Pstr, 50);

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

    //�ő�l�A�ŏ��l�̌���
    MinY = KD41Data[SamplePositionIdx-1].LD_HP_MIN;

    MaxY = Max[0];
    for ( i = 0; i < n; i++ ) {
        //�ő�l�̌���
        if ( MaxY < Max[i] ) MaxY = Max[i];
        if ( MaxY < Min[i] ) MaxY = Min[i];
    }

    if( fabs(MaxY - MinY) < 0.0000001 ) {
           MaxY =MinY+1.0 ;
    }

    if( MaxY < MinY ) MaxY = MinY + 1.0 ;

    //�ڐ���̊Ԋu�A�ŏ��l�A�ő�l�̐ݒ�
    ScaleVal = SetScalVal( MaxY, MinY, 4 );
    ScaleMin = MinY ;

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

        //�v�����Ă���ۯ�NO�̏ꍇ�F��ς���
        if( i== iCur ) {
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
        GraphName->Canvas->Pen->Width = 2;      //���̑���
        GraphName->Canvas->Brush->Style = bsSolid ;
        GraphName->Canvas->Ellipse( x2,y2,x3,y3 );
     }

    GraphName->Canvas->Pen->Width = 2;      //���̑���

    for ( i = 0; i < n; i++ ){

        if( Val[i] <=0.0 ) continue  ;

         //�v�����Ă���ۯ�NO�̏ꍇ�F��ς���
        if( i== iCur ) {
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
*  function name : double SetScalVal(double dMax, double dMin, int sno)*
*                  +--------------------------------------+            *
*          ��  ��  |   dmax    |  �ő���W�l              |            *
*                  |   dMin    |  �ŏ����W�l              |            *
*                  |   sno     |  ������                  |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |          �b���݃T�C�Y                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : �ő���W�l�ƍŏ����W�l���獏�ݑ傫�������߂�        *
*  written by    : �� ���N(NKK unics Corp.)                            *
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

void SetData( int iN, double dMin,double  dMax,double  dAve,double  dR,double  dSigma,
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
   Form1->Pnl43->Caption = FormatFloat("#0.000", dFuryo );

   Form1->Pnl41->Color = clMenu ;
   Form1->Pnl42->Color = clMenu ;
   Form1->Panel93->Color = clMenu ;
   Form1->Panel94->Color = clMenu ;

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
*  contents      : KD43W����ǂݍ����ް����ɂɎw�肵�����b�gNo       *
*                :  �L�邩�ǂ��� �̃`�F�b�N                            *
*  written by    : �� ���N(NKK unics Corp.)                            *
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



