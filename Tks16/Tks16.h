#ifndef MainMenuH
#define MainMenuH

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>


#include <fcntl.h>
#include <io.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dir.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <winbase.h>
#include <shellapi.h>
#include <Printers.hpp>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <wingdi.h>

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//#include "DrawGraph.h"

//�d�x�f�[�^̧�ٕϐ�
struct structKD61{
      AnsiString KENSA_YMD ;   //�����\���
      int TOLEY_NO;            //�ڰNO
      int SAMPLE_P ;           //������߼޼��
      int SOKUTE_KBN1;         //����敪 HsC
      int SOKUTE_KBN2;         //����敪 HsD
      AnsiString DTKSCOD;      //���Ӑ�R�[�h
      AnsiString DTKSHIN;      //���Ӑ�i��
      AnsiString LOTNO;        //���b�gNO
      AnsiString HINBAN;       //���Еi��
      AnsiString ZISCOD ;      //�ގ��R�[�h
      AnsiString ZISNAM ;      //�ގ���
      int HSC_A_MIN;           //Hsc�d�x���� �K�i��
      int HSC_A_MAX;           //Hsc�d�x���� �K�i��
      int HSC_S_MIN;           //Hsc�d�x���� �K�i��
      int HSC_S_MAX;           //Hsc�d�x���� �K�i��
      int HSC_A_CH[100];       //Hsc�d�x����1
      int HSC_S_CH[100];       //Hsc�d�x����1
      int HSC_SK_NUM;          //Hsc������w����
      int HSC_SK_SU;           //Hsc�����
      double HSC_A_AVE;        //Hsc�d�x���ʑ��蕽�ϒl
      double HSC_S_AVE;        //Hsc�d�x���ʑ��蕽�ϒl

      double HSD_A_MIN;        //Hsd�d�x���� �K�i��
      double HSD_A_MAX;        //Hsd�d�x���� �K�i��
      double HSD_S_MIN;        //Hsd�d�x���� �K�i��
      double HSD_S_MAX;        //Hsd�d�x���� �K�i��
      double HSD_A_CH[100];    //Hsd�d�x����
      double HSD_S_CH[100];    //Hsd�d�x����
      int HSD_SK_NUM;          //Hsd������w����
      int HSD_SK_SU;           //Hsd�����
      double HSD_A_AVE;        //Hsd�d�x���ʑ��蕽�ϒl
      double HSD_S_AVE;        //Hsd�d�x���ʑ��蕽�ϒl

      AnsiString ADDYMD ;      //�o�^��
      AnsiString ADDTIM ;      //�o�^����
      AnsiString UPDYMD ;      //�ύX��
      AnsiString UPDTIM ;      //�ύX����
      int UPDCHR ;             //�X�V��
      int UPDCNT ;             //�X�V��

      // �f�[�^�x�[�X�ȊO
      int HSC_SK_NUM_CUR;      //���đ���f�[�^NO
      int HSD_SK_NUM_CUR;      //���đ���f�[�^NO
      int LINK;
      AnsiString MEMO ;        //���l 2002/11/07 �ǉ� E.Takase
};

//�d�x�f�[�^�ϐ� KD63W
struct structKD63W{
      AnsiString DTKSHIN;          //���Ӑ�i��
      AnsiString LOTNO[50];        //���b�gNO
      int HSC_MIN[2][50];          //HSC �d�x �K�i��  (0: ���ʁA�P�F���ʁj
      int HSC_MAX[2][50];          //HSC �d�x �K�i��
      int HSC_CH[2][50][100];      //HSC �d�x ����l
      double HSC_AVE[2][50];       //HSC �d�x ���蕽�ϒl

      double HSD_MIN[2][50];       //HSD �d�x���� �K�i��
      double HSD_MAX[2][50];       //HSD �d�x���� �K�i��
      double HSD_CH[2][50][100];   //HSD �d�x���� ����l
      double HSD_AVE[2][50];       //HSD �d�x���� ���蕽�ϒl

      int LOTCNT;                  //���b�g��
      int HSC_SOKUTEI_NM[2][50];   //�e���b�g�̌v����
      int HSD_SOKUTEI_NM[2][50];   //�e���b�g�̌v����
};

extern AnsiString MSG_01 ;
extern AnsiString MSG_02 ;
extern AnsiString MSG_03 ;
extern AnsiString MSG_04 ;
extern AnsiString MSG_05 ;
extern AnsiString MSG_06 ;
extern AnsiString MSG_07 ;
extern AnsiString MSG_08 ;
extern AnsiString MSG_09 ;
extern AnsiString MSG_10 ;
extern AnsiString MSG_11 ;

extern int USER_COD ;
extern AnsiString USER_NAM;
extern AnsiString BUMO_COD;
extern AnsiString BUMO_NAM;

extern int iRec_Kd61;              //�ꗗ�������ʌ���

extern int iKskStart ;             // �P: �v���J�n  0: �v���ł��Ȃ�

extern int Hsc_DataNoIdx;          // Hsc�F��»���ك|�W�V����NO�ɑ΂����ް�NO
extern int Hsc_SamplePositionIdx;  // Hsc�F����ك|�W�V����NO
extern int Hsd_DataNoIdx;          // Hsd�F��»���ك|�W�V����NO�ɑ΂����ް�NO
extern int Hsd_SamplePositionIdx;  // Hsd�F����ك|�W�V����NO

extern int iKojoKbn ;            //�H��敪 2016/06/30 �ǉ�

#endif

extern structKD61 KD61Data[30];
extern int Kd61_Serch02( void);
extern structKD63W KD63WData[30];

int Kd61_Serch01(void);
int Kd61_Update01(void);
int Kd62_Update01( int iRec);
int  Kd62_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo);
int  Kd62_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo);
int  Kd62_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo);
int Kd63W_Serch01(void);
void  CopyKD61Data(void);
void  AddKd63W(int A_No);

long  Kd63W_Create01(AnsiString sYmd, int iTlno, int iNum);
void ToDrawGraph( int iSp, int iOpt, int A_No );




