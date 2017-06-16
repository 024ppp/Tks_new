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

//硬度データﾌｧｲﾙ変数
struct structKD61{
      AnsiString KENSA_YMD ;   //検索予定日
      int TOLEY_NO;            //ﾄﾚｰNO
      int SAMPLE_P ;           //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ
      int SOKUTE_KBN1;         //測定区分 HsC
      int SOKUTE_KBN2;         //測定区分 HsD
      AnsiString DTKSCOD;      //得意先コード
      AnsiString DTKSHIN;      //得意先品番
      AnsiString LOTNO;        //ロットNO
      AnsiString HINBAN;       //自社品番
      AnsiString ZISCOD ;      //材質コード
      AnsiString ZISNAM ;      //材質名
      int HSC_A_MIN;           //Hsc硬度圧面 規格下
      int HSC_A_MAX;           //Hsc硬度圧面 規格上
      int HSC_S_MIN;           //Hsc硬度側面 規格下
      int HSC_S_MAX;           //Hsc硬度側面 規格上
      int HSC_A_CH[100];       //Hsc硬度圧面1
      int HSC_S_CH[100];       //Hsc硬度側面1
      int HSC_SK_NUM;          //Hsc測定個数指示数
      int HSC_SK_SU;           //Hsc測定個数
      double HSC_A_AVE;        //Hsc硬度圧面測定平均値
      double HSC_S_AVE;        //Hsc硬度側面測定平均値

      double HSD_A_MIN;        //Hsd硬度圧面 規格下
      double HSD_A_MAX;        //Hsd硬度圧面 規格上
      double HSD_S_MIN;        //Hsd硬度側面 規格下
      double HSD_S_MAX;        //Hsd硬度側面 規格上
      double HSD_A_CH[100];    //Hsd硬度圧面
      double HSD_S_CH[100];    //Hsd硬度側面
      int HSD_SK_NUM;          //Hsd測定個数指示数
      int HSD_SK_SU;           //Hsd測定個数
      double HSD_A_AVE;        //Hsd硬度圧面測定平均値
      double HSD_S_AVE;        //Hsd硬度側面測定平均値

      AnsiString ADDYMD ;      //登録日
      AnsiString ADDTIM ;      //登録時間
      AnsiString UPDYMD ;      //変更日
      AnsiString UPDTIM ;      //変更時間
      int UPDCHR ;             //更新者
      int UPDCNT ;             //更新回数

      // データベース以外
      int HSC_SK_NUM_CUR;      //ｶﾚﾝﾄ測定データNO
      int HSD_SK_NUM_CUR;      //ｶﾚﾝﾄ測定データNO
      int LINK;
      AnsiString MEMO ;        //備考 2002/11/07 追加 E.Takase
};

//硬度データ変数 KD63W
struct structKD63W{
      AnsiString DTKSHIN;          //得意先品番
      AnsiString LOTNO[50];        //ロットNO
      int HSC_MIN[2][50];          //HSC 硬度 規格下  (0: 圧面、１：側面）
      int HSC_MAX[2][50];          //HSC 硬度 規格上
      int HSC_CH[2][50][100];      //HSC 硬度 測定値
      double HSC_AVE[2][50];       //HSC 硬度 測定平均値

      double HSD_MIN[2][50];       //HSD 硬度圧面 規格下
      double HSD_MAX[2][50];       //HSD 硬度圧面 規格上
      double HSD_CH[2][50][100];   //HSD 硬度圧面 測定値
      double HSD_AVE[2][50];       //HSD 硬度圧面 測定平均値

      int LOTCNT;                  //ロット個数
      int HSC_SOKUTEI_NM[2][50];   //各ロットの計測個数
      int HSD_SOKUTEI_NM[2][50];   //各ロットの計測個数
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

extern int iRec_Kd61;              //一覧検索結果件数

extern int iKskStart ;             // １: 計測開始  0: 計測できない

extern int Hsc_DataNoIdx;          // Hsc：一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO
extern int Hsc_SamplePositionIdx;  // Hsc：ｻﾝﾌﾟﾙポジションNO
extern int Hsd_DataNoIdx;          // Hsd：一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO
extern int Hsd_SamplePositionIdx;  // Hsd：ｻﾝﾌﾟﾙポジションNO

extern int iKojoKbn ;            //工場区分 2016/06/30 追加

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





