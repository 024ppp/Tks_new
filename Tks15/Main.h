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

#include "SharedMemory.h"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "DrawGraph.h"

//��̔�d�ް�̧�ٕϐ�
extern struct structKD51{
      AnsiString KENSA_YMD ;   //�����\���
      int TOLEY_NO;            //�ڰNO
      int SAMPLE_P ;           //������߼޼��
      int SOKUTE_KBN ;         //����敪
      AnsiString DTKSCOD;      //���Ӑ�R�[�h
      AnsiString DTKSHIN;      //���Ӑ�i��
      AnsiString LOTNO;        //���b�gNO
      AnsiString HINBAN;       //���Еi��
      AnsiString ZISCOD ;      //�ގ��R�[�h
      AnsiString ZISNAM ;      //�ގ���
      double BOTAI_MAX ;       //��̔�d �K�i��
      double BOTAI_MIN ;       //��̔�d �K�i��
      int    KEIJYO_KBN;       //��̔�d �`��敪
      int    SOKUTEI_NM ;      //�����
      int    SOKUTEI_SU ;      //�����
      double SOKUTE_AVE ;      //���蕽�ϒl
      double SOKUTEI_S[100] ;  //����l     �������@
      double SOKUTEI_H[100] ;  //����l     �����@
      double SOKUTEI_N[100] ;  //����l     ����
      double SOKUTEI_J[100] ;  //����l     �d��
      double SOKUTEI_B[100] ;  //����l     ��̔�d
      AnsiString ADDYMD ;      //�o�^��
      AnsiString ADDTIM ;      //�o�^����
      AnsiString UPDYMD ;      //�ύX��
      AnsiString UPDTIM ;      //�ύX����
      int UPDCHR ;             //�X�V��
      int UPDCNT ;             //�X�V��
      int SOKUTEI_NB_CUR;      //���đ���f�[�^NO ��̔�d
      int SOKUTEI_NS_CUR;      //���đ���f�[�^NO �������@
      int SOKUTEI_NH_CUR;      //���đ���f�[�^NO �����@
      int SOKUTEI_NN_CUR;      //���đ���f�[�^NO ����
      int SOKUTEI_NJ_CUR;      //���đ���f�[�^NO �d��
      int LINK;
      AnsiString MEMO ;        //���l 2002/11/07 �ǉ� E.Takase
}KD51Data[30];

//��̔�d�������p�e�[�u���ϐ� KD53W
extern struct structKD53W{
      AnsiString DTKSHIN;          //���Ӑ�i��
      AnsiString LOTNO[50];        //���b�gNO
      double BOTAI_MAX[50] ;       //��̔�d �K�i��
      double BOTAI_MIN[50] ;       //��̔�d �K�i��
      double SOKUTEI[50][100] ;    //����l ��R
      double SOKUTE_AVE[50] ;      //���蕽�ϒl ��R
      int LOTCNT;
      int SOKUTEI_NM[50];
}KD53WData[30];

extern TNumberEdit *pEdt1[30] ;    //  ���ް��P�̺��۰ق�ۑ�
extern TNumberEdit *pEdt2[30] ;    //  ���ް�2 �̺��۰ق�ۑ�
extern TNumberEdit *pEdt3[30] ;    //  ���ް�3 �̺��۰ق�ۑ�
extern TNumberEdit *pEdt4[30] ;    //  �ް��l�ԍ���ۑ�
extern TPanel *pPnlP[30] ;         //  ��NO�i�߼޼�ݔԍ��j�̺��۰ق�ۑ�
extern TPanel *pPnlN[30] ;         //  ��N(�ް���)�̺��۰ق�ۑ�
extern TScrollBar *pScrl[30];      //  ScrollBar�̺��۰ق�ۑ�

//���薾��
extern TNumberEdit *pEdt1_S[4] ;    //  ���ް��P�̺��۰ق�ۑ�
extern TNumberEdit *pEdt2_S[4] ;    //  ���ް�2 �̺��۰ق�ۑ�
extern TNumberEdit *pEdt3_S[4] ;    //  ���ް�3 �̺��۰ق�ۑ�
extern TNumberEdit *pEdt4_S[4] ;    //  �ް��l�ԍ���ۑ�
extern TPanel *pPnl_S[4] ;          //  ��NO�i�߼޼�ݔԍ��j�̺��۰ق�ۑ�
extern TScrollBar *pScrl_S[4];      //  ScrollBar�̺��۰ق�ۑ�


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
extern int RSInputFlag;

extern int iRec_Kd51;              // �ꗗ�������ʌ���
extern int CurField;               // 1: ���ق��������ɂ���
                                   // 2: ���ق��v�����ɂ���
                                   // 3: ���ق���ʉ��̋@�\���݂ɂ���
extern int ymdtl_flg;              // 1: ���ق��v���\����ɂ���
                                   // 2: ���ق��ڰNO�ɂ���
extern int btn_flg;                //  ��ʉ��̋@�\���݂̎w���t���O

extern int SamplePositionIdx;      // ����ك|�W�V����NO
extern int DataNoIdx;              // ��»���ك|�W�V����NO�ɑ΂����ް�NO
                                   // �X�V�����ꍇ =1   �X�V���Ȃ��ꍇ =0
extern int iFirstPosition ;        // �v�������ް��擪�̻�����߼޼��NO
extern int iLastPosition ;         // �v�������ް��̍Ō�� ������߼޼��NO

extern int iSaveFlag;              //

extern int CurBackFlg ;
extern  int iKomoku;                //���荀�ڂ̎w���t���O
extern int Save_Click ;

// [Option]���݂������ꍇ�g���ϐ�
extern int iOption     ;           // iOption == 1  ���藚��\���i��ON, �FON)
                                   // iOPtion == 2  �H���\�͕\���i��ON, �FON)
                                   // iOption == 3   �\���Ȃ��i��OFF, �FOFF)
extern int LOTMAX;                 // �����ް�̧�ْ��̍ő�ۯČ�
extern int iKskStart ;             // �P: �v���J�n  0: �v���ł��Ȃ�
extern int HaveSokutei;            // KD51���猟���������ʂ̒��Ɍv���敪�P��
                                   // �Ȃ��Ă���ں��ނ��邩�ǂ����̎w���t���O
extern int AllDataChg;             // ��ʂɕ\�����Ă����ް��X�V����邩�ǂ���
extern int CurSampChg;
extern int CurDataChg;
extern int Update_err;

extern int iKojoKbn ;            //�H��敪 2016/06/30 �ǉ�

// �֐��̐錾
extern void SaveCtlID();
extern void DisplayInfo(void);
extern int  SaveRegaiDt(void ) ;
extern void CheckInKikaku(int) ;
extern int CheckDtNo(void);
extern void ToNextData(void);
extern void ToPreData(void);
extern void StatBarClear(AnsiString );
extern void SetRed(int ) ;
extern void ClearRed(void) ;
extern void CurseBack(void);

extern void KD53WFormat(void);
extern void AddKd53W(void);
extern int  CheckLotNo(int ) ;

extern int IsNullSpace(AnsiString);
extern int GetItem(char **buff, char *item) ;
extern int Kd51_Serch01(void);
extern int Kd51_Serch02(void);
extern void Kd51_Update01(void);

extern long  Kd53W_Create01(AnsiString, int, int) ;
extern int   Kd53W_Serch01();

extern void ToDrawGraph( int, int  ) ;
extern void DrawGraph(int , char, double , double , double );

extern int BHijyuCal(int iSp,int iDt) ;
extern int CheckKomoku(int iSp, int iDt) ;

extern AnsiString DelSEPA( AnsiString );
extern AnsiString InsSEPA( AnsiString );
#endif






