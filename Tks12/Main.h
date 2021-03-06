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
#include "DrawGraph.h"

//ブラシ幅寸法（縦押し）計測ﾃﾞｰﾀﾌｧｲﾙ変数
extern struct structKD21{
      AnsiString KENSA_YMD ;   //検索予定日
      int TOLEY_NO;            //ﾄﾚｰNO
      int SAMPLE_P ;           //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ
      int SOKUTE_KBN ;         //測定区分
      AnsiString DTKSCOD;      //得意先コード
      AnsiString DTKSHIN;      //得意先品番
      AnsiString LOTNO;        //ロットNO
      AnsiString HINBAN;       //自社品番
      AnsiString ZISCOD ;      //材質コード
      AnsiString ZISNAM ;      //材質名
      double BURASIT_MIN ;      //ブラシ幅（縦押し） 規格下
      double BURASIT_MAX ;      //ブラシ幅（縦押し） 規格上
      int SOKUTEI_NM ;         //ブラシ幅寸法測定個数
      int SOKUTEI_SU ;         //ブラシ幅寸法測定個数
      double SOKUTE_AVE ;      //測定平均値
      double SOKUTEICHI[100] ; //測定値
      AnsiString ADDYMD ;      //登録日
      AnsiString ADDTIM ;      //登録時間
      AnsiString UPDYMD ;      //変更日
      AnsiString UPDTIM ;      //変更時間
      int UPDCHR ;             //更新者
      int UPDCNT ;             //更新回数
      int SOKUTEI_NM_CUR;      //ｶﾚﾝﾄ測定データNO
      int LINK;
      AnsiString MEMO ;        //備考 2002/11/07 追加 E.Takase
}KD21Data[30];

//ブラシ幅寸法（縦押し）計測履歴ﾃﾞｰﾀﾌｧｲﾙ変数 KD23W
extern struct structKD23W{
      AnsiString DTKSHIN;         //得意先品番
      AnsiString LOTNO[50];        //ロットNO
      double BURASIT_MIN[50] ;      //ブラシ幅（縦押し） 規格下
      double BURASIT_MAX[50] ;      //ブラシ幅（縦押し） 規格上
      double SOKUTEI[50][100] ;    //測定値
      double SOKUTE_AVE[50] ;      //測定平均値
      int LOTCNT;                  //該当品番のﾛｯﾄNO数
      int SOKUTEI_NM[50];          // 該当ﾛｯﾄNOの測定ﾃﾞｰﾀ数
}KD23WData[30];

extern TNumberEdit *pEdt1[30] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt2[30] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt3[30] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt4[30] ;    //  ﾃﾞｰﾀ値番号を保存
extern TPanel *pPnlP[30] ;         //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
extern TPanel *pPnlN[30] ;         //  列N(ﾃﾞｰﾀ個数)のｺﾝﾄﾛｰﾙを保存
extern TScrollBar *pScrl[30];      //  Scrollbarのｺﾝﾄﾛｰﾙを保存

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

extern int iRec_Kd21;              // 一覧検索結果件数
extern int CurField;               // 1: ｶｰｿﾙが検索部にいる
                                   // 2: ｶｰｿﾙが計測部にいる
                                   // 3: ｶｰｿﾙが画面下の機能ﾎﾞﾀﾝにいる
extern int ymdtl_flg;              // 1: ｶｰｿﾙが計測予定日にいる
                                   // 2: ｶｰｿﾙがﾄﾚｰNOにいる
extern int btn_flg;                //  画面下の機能ﾎﾞﾀﾝの指示フラグ

extern int SamplePositionIdx;      // ｻﾝﾌﾟﾙポジションNO
extern int DataNoIdx;              // 一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO
                                   // 更新した場合 =1   更新しない場合 =0
extern int iFirstPosition ;        // 計測するﾃﾞｰﾀ先頭のｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
extern int iLastPosition ;         // 計測するﾃﾞｰﾀの最後の ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO

extern int iSaveFlag;
extern int CurBackFlg ;
extern int HaveSokutei;

extern int AllDataChg;            // 画面に表示しているﾃﾞｰﾀ更新されるかどうか
extern int CurSampChg;
extern int CurDataChg;
extern int Update_err;            // 計測ﾃﾞｰﾀを保存する際エラーが発生しているかどうか
extern int Save_Click;            // [保存」ﾎﾞﾀﾝを押した場合の指示フラグ

// [Option]ﾎﾞﾀﾝを押す場合使う変数
extern int iOption     ;           // iOption == 1  測定履歴表示（音ON, 色ON)
                                   // iOPtion == 2  工程能力表示（音ON, 色ON)
                                   // iOption == 3   表示なし（音OFF, 色OFF)
extern int LOTMAX;
extern int iKskStart ;             // １: 計測開始  0: 計測できない

extern int iKojoKbn ;            //工場区分 2016/06/30 追加

// 関数の宣言
extern void SaveCtlID();
extern void DisplayInfo(void);
extern void SaveRegaiDt(void ) ;
extern void CheckInKikaku(int) ;
extern int CheckDtNo(void);
extern void ToNextData(void);
extern void ToPreData(void);
extern void StatBarClear(AnsiString );
extern void SetRed(int ) ;
extern void ClearRed(void) ;
extern void CurseBack(void);

extern void AddKd23W(void);
extern int  CheckLotNo(int ) ;
extern void CopyKD21Data(void) ;


extern int IsNullSpace(AnsiString);
extern int Kd21_Serch01(void);
extern int Kd21_Serch02(void);
extern void Kd21_Update01(void);

extern long  Kd23W_Create01(AnsiString, int, int) ;
extern int  Kd23W_Serch01();

extern void ToDrawGraph( int, int  ) ;
extern void DrawGraph(int , char, double , double , double );

extern AnsiString DelSEPA( AnsiString );
extern AnsiString InsSEPA( AnsiString );

#endif







