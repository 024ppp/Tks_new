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

//母体比重ﾃﾞｰﾀﾌｧｲﾙ変数
extern struct structKD51{
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
      double BOTAI_MAX ;       //母体比重 規格上
      double BOTAI_MIN ;       //母体比重 規格下
      int    KEIJYO_KBN;       //母体比重 形状区分
      int    SOKUTEI_NM ;      //測定個数
      int    SOKUTEI_SU ;      //測定個数
      double SOKUTE_AVE ;      //測定平均値
      double SOKUTEI_S[100] ;  //測定値     厚さ寸法
      double SOKUTEI_H[100] ;  //測定値     幅寸法
      double SOKUTEI_N[100] ;  //測定値     長さ
      double SOKUTEI_J[100] ;  //測定値     重量
      double SOKUTEI_B[100] ;  //測定値     母体比重
      AnsiString ADDYMD ;      //登録日
      AnsiString ADDTIM ;      //登録時間
      AnsiString UPDYMD ;      //変更日
      AnsiString UPDTIM ;      //変更時間
      int UPDCHR ;             //更新者
      int UPDCNT ;             //更新回数
      int SOKUTEI_NB_CUR;      //ｶﾚﾝﾄ測定データNO 母体比重
      int SOKUTEI_NS_CUR;      //ｶﾚﾝﾄ測定データNO 厚さ寸法
      int SOKUTEI_NH_CUR;      //ｶﾚﾝﾄ測定データNO 幅寸法
      int SOKUTEI_NN_CUR;      //ｶﾚﾝﾄ測定データNO 長さ
      int SOKUTEI_NJ_CUR;      //ｶﾚﾝﾄ測定データNO 重量
      int LINK;
      AnsiString MEMO ;        //備考 2002/11/07 追加 E.Takase
}KD51Data[30];

//母体比重履歴作画用テーブル変数 KD53W
extern struct structKD53W{
      AnsiString DTKSHIN;          //得意先品番
      AnsiString LOTNO[50];        //ロットNO
      double BOTAI_MAX[50] ;       //母体比重 規格上
      double BOTAI_MIN[50] ;       //母体比重 規格下
      double SOKUTEI[50][100] ;    //測定値 抵抗
      double SOKUTE_AVE[50] ;      //測定平均値 抵抗
      int LOTCNT;
      int SOKUTEI_NM[50];
}KD53WData[30];

extern TNumberEdit *pEdt1[30] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt2[30] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt3[30] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt4[30] ;    //  ﾃﾞｰﾀ値番号を保存
extern TPanel *pPnlP[30] ;         //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
extern TPanel *pPnlN[30] ;         //  列N(ﾃﾞｰﾀ個数)のｺﾝﾄﾛｰﾙを保存
extern TScrollBar *pScrl[30];      //  ScrollBarのｺﾝﾄﾛｰﾙを保存

//測定明細
extern TNumberEdit *pEdt1_S[4] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt2_S[4] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt3_S[4] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
extern TNumberEdit *pEdt4_S[4] ;    //  ﾃﾞｰﾀ値番号を保存
extern TPanel *pPnl_S[4] ;          //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
extern TScrollBar *pScrl_S[4];      //  ScrollBarのｺﾝﾄﾛｰﾙを保存


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

extern int iRec_Kd51;              // 一覧検索結果件数
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

extern int iSaveFlag;              //

extern int CurBackFlg ;
extern  int iKomoku;                //測定項目の指示フラグ
extern int Save_Click ;

// [Option]ﾎﾞﾀﾝを押す場合使う変数
extern int iOption     ;           // iOption == 1  測定履歴表示（音ON, 色ON)
                                   // iOPtion == 2  工程能力表示（音ON, 色ON)
                                   // iOption == 3   表示なし（音OFF, 色OFF)
extern int LOTMAX;                 // 履歴ﾃﾞｰﾀﾌｧｲﾙ中の最大ﾛｯﾄ個数
extern int iKskStart ;             // １: 計測開始  0: 計測できない
extern int HaveSokutei;            // KD51から検索した結果の中に計測区分１に
                                   // なっているﾚｺｰﾄﾞあるかどうかの指示フラグ
extern int AllDataChg;             // 画面に表示しているﾃﾞｰﾀ更新されるかどうか
extern int CurSampChg;
extern int CurDataChg;
extern int Update_err;

extern int iKojoKbn ;            //工場区分 2016/06/30 追加

// 関数の宣言
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







