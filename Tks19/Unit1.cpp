
/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１９）                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 座屈測定メインプログラム                            *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
// 表示する履歴ﾃﾞｰﾀの最大個数
int LOTMAX = 10 ;

//----------------------------------------------------------------------------
// RS232C Open or Create の指示フラグ
// 0: Create   1: Open
int iRS232C = 1 ;
//2009.03.13 MTS E.Takase [001]  ↓
//材料試験機（単独使用）は機器タイプを5とする
//int iChNo = 7;
//int KikiType =3;
int iChNo = 10;
int KikiType =5;
//2009.03.13 MTS E.Takase [001]  ↑int iChNo = 7;
int ret_232 = 0;

//----------------------------------------------------------------------------
int USER_COD ;              // 担当者ｺｰﾄﾞ
AnsiString USER_NAM;        // 担当者名
AnsiString BUMO_COD;        // 部門ｺｰﾄﾞ
AnsiString BUMO_NAM;        // 部門名
int RSInputFlag;            //RS232C読み込みフラグ

//---------------------------------------------------------------------------
//RS232C通信用変数
#define WM_Notify_WriteData WM_USER + 3040	// 相手プロセスに通知します
#define WM_Notify_WriteData1 WM_USER + 3041	// 相手プロセスに通知します
char SharedBuff[BUFFERSIZE];                    // 受信BUFFER
int  iShareFlag = 0 ;                           // RS232C接続フラグ
int  ShareFlag = 0 ;                            // RS232Cと接続するかどうかの指示フラグ


//---------------------------------------------------------------------------
// KD91構造体変数
structKD91 KD91Data[30];      // 座屈ﾃﾞｰﾀﾌｧｲﾙ  KD91

//KD93W構造体変数
structKD93W KD93WData[30];    //座屈計測履歴ﾃﾞｰﾀﾜｰｸﾌｧｲﾙ  KD93W


//---------------------------------------------------------------------------
//画面操作用変数
int iRec_Kd91;              // 一覧検索結果件数
int CurField;               // 1: ｶｰｿﾙが検索部にいる
                            // 2: ｶｰｿﾙが計測部にいる
                            // 3: ｶｰｿﾙが画面下の機能ﾎﾞﾀﾝにいる
int ymdtl_flg;              // 1: ｶｰｿﾙが計測予定日にいる
                            // 2: ｶｰｿﾙがﾄﾚｰNOにいる
int btn_flg;                //  画面下の機能ﾎﾞﾀﾝの指示フラグ
int DataNoIdx;              // 一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO

int SamplePositionIdx;      // ｻﾝﾌﾟﾙポジションNO

int iFirstPosition ;        // 計測するﾃﾞｰﾀ先頭のｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
int iLastPosition ;         // 計測するﾃﾞｰﾀの最後の ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO

int iKskStart=0;            // １: 計測開始  0: 計測できない

int AllDataChg=0;           // 画面に表示しているﾃﾞｰﾀ更新されるかどうか
int CurSampChg=0;
int CurDataChg=0;           // 更新した場合 =1   更新しない場合 =0


int iSaveFlag= 0;           // ScrollbarのChangeイベントで使う変数
int CurBackFlg = 0 ;
int HaveSokutei = 0;
int Update_err = 0;         // 計測ﾃﾞｰﾀを保存する際エラーが発生しているかどうか
int Save_Click =0;          //[保存」ﾎﾞﾀﾝを押した場合の指示フラグ

int iKojoKbn = 0 ;          // 工場区分

//---------------------------------------------------------------------------
// [Option]ﾎﾞﾀﾝを押す場合使う変数
int iOption = 1 ;           // iOption == 1  測定履歴表示（音ON, 色ON)
                            // iOPtion == 2  工程能力表示（音ON, 色ON)
                            // iOption == 3   表示なし（音OFF, 色OFF)
//---------------------------------------------------------------------------
// 表示メッセージ
AnsiString MSG_00 = "機器番号（PC1〜PC4)を定義して下さい";
AnsiString MSG_01 = "検索中です... しばらくお待ちください。" ;
AnsiString MSG_02 = "検索結果０件。" ;
AnsiString MSG_03 = "検索結果０件。" ;
AnsiString MSG_04 = "更新中です... しばらくお待ちください。" ;
AnsiString MSG_05 = "集計中です... しばらくお待ちください。" ;
AnsiString MSG_06 = "更新中です... しばらくお待ちください。" ;
AnsiString MSG_07 = "Ch  設定" ;
AnsiString MSG_08 = "データ収録精度(1/100)設定。" ;
AnsiString MSG_09 = "画面印刷中です... しばらくお待ちください。" ;
AnsiString MSG_10 = "データが編集されています。\n保存しますか？" ;
AnsiString MSG_11 = "計測機器の初期化に失敗しました。　検索及びキーボードからの入力は使用可能です。" ;
AnsiString MSG_14 = "計測機器の応答がありません。　検索及びキーボードからの入力は使用可能です。" ;
AnsiString MSG_15 = "計測機器は他のパソコンで使用しています。　検索及びキーボードからの入力は使用可能です。" ;
AnsiString MSG_12 = "履歴データ ０ 件。" ;

//----------------------------------------------------------------------------
// 画面ｺﾝﾄﾛｰﾙ保存変数
TNumberEdit *pEdt1[30] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt2[30] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt3[30] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt4[30] ;    //  ﾃﾞｰﾀ値番号を保存
TPanel *pPnlP[30] ;         //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
TPanel *pPnlN[30] ;         //  列N(ﾃﾞｰﾀ個数)のｺﾝﾄﾛｰﾙを保存
TScrollBar *pScrl[30];      //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存


// 関数の宣言
void SaveCtlID() ;
void ToDrawGraph( int, int  ) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] , int );
void SetEnabel(int );
void SetEnter(void);
void SaveRegaiDt(void);
void CheckInKikaku(int );
int  CheckDtNo(void);
void ToNextData(void);
void ToPreData(void);
void DisplayInfo(void);
void StatBarClear(AnsiString );
void ClearRed(void) ;
void SetRed(int );
void CurseBack(void);

void ExecF1(void);
void ExecF6(void); //2002/11/07 E.Takase
void ExecF10(void);
void ExecF11(void);

void AddKd93W(void);
int  CheckLotNo(int ) ;
void CopyKD91Data(void) ;

int  Kd91_Serch01(void);
int  Kd91_Serch02(void);
void Kd91_Update01(void);
long  Kd93W_Create01(AnsiString, int, int) ;
int  Kd93W_Serch01();
int IsNullSpace(AnsiString);
void Kd93W_Delete01(void);
void KD93WFormat(void);

extern void WriteLog(char *);

AnsiString DelSEPA( AnsiString );
AnsiString InsSEPA( AnsiString );

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TForm1::OnNotifyWriteData(TMessage &Message)
{
 int nNumber;
 double dVal;

 // CONNECT n:   Return:  OK/ERROR
 // [Data]

     nNumber = SharedMemory_Read(2, SharedBuff);

     // RS232Cと接続した場合
     if (iShareFlag == 1) {      // OK/ERROR

         // RS232Cと接続成功した場合
        if( strncmp( SharedBuff, "OK", 2) == 0 ){
            iShareFlag = 2;

         // RS232Cと接続エラーの場合
        }else if( strncmp( SharedBuff, "ERROR", 5) == 0 ){
             Beep();
             StatBarClear(MSG_14) ;

             iShareFlag = 0;
        }else if( strncmp( SharedBuff, "C_ERROR", 7) == 0 ){
             Beep();
             StatBarClear(MSG_15) ;

             iShareFlag = 0;
        }
     }

     // RS232Cと接続成功した場合 、受信した測定値を画面へ表示
     if (iShareFlag == 2) {

         // カソールを測定値ｺﾝﾄﾛｰﾙに合わせる場合しかﾃﾞｰﾀを受信しない
        if( nNumber > 0 &&  strncmp( SharedBuff, "OK", 2) != 0 &&
                            strncmp(SharedBuff, "ERROR", 5) != 0 &&
                            strncmp(SharedBuff, "C_ERROR", 7) != 0 &&
                            ( !Form1->BtnF01->Focused()  &&
                              !Form1->BtnF02->Focused()  &&
                              !Form1->BtnF03->Focused()  &&
                              !Form1->BtnF05->Focused()  &&
                              !Form1->BtnF07->Focused()  &&
                              !Form1->BtnF10->Focused()  &&
                              !Form1->BtnF11->Focused()  &&
                              !Form1->BtnF12->Focused()  &&
                              !Form1->edtymd->Focused()  &&
                              !Form1->edttlno->Focused() ) &&
                             (SamplePositionIdx >= iFirstPosition &&
                                 SamplePositionIdx <= iLastPosition )) {

           dVal = atof( SharedBuff );
           if( DataNoIdx == 1 ) {
               //測定値１のセット
               pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0", dVal);

           }else if (DataNoIdx == 2 ){
               //測定値２のセット
               pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0", dVal);

           }else{
               // 測定値NO＞２の場合ﾃﾞｰﾀのセット
               pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0", dVal);
           }

           //RS232C読み込みフラグ 1
           RSInputFlag = 1;

           //ｶﾚﾝﾄﾃﾞｰﾀをセットしてからカーソルを自動的に次の測定値へ移動
            ToNextData();
        }
    }
}

//---------------------------------------------------------------------------
// 一覧検索ボタン
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    //カソールを元に戻す
   CurseBack();

   ExecF1();
}

void ExecF1(void)
{
   if( Form1->edtymd->Focused() || Form1->edttlno->Focused() ){

      // ステータスメッセージ
      StatBarClear( MSG_01);

     // 座屈ﾃﾞｰﾀﾌｧｲﾙからデータを抽出
     iRec_Kd91 = Kd91_Serch01() ;
     if( iRec_Kd91 <= 0 ) {
          StatBarClear( MSG_02);
      }else{
          StatBarClear( " ");
      }

      // 一覧検索結果の表示画面を開く
      Form2->ShowModal();

      }
}
//---------------------------------------------------------------------------
// 前項ボタン
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
      //カソールを元に戻す
       CurseBack();
       ToPreData ();
 }

//---------------------------------------------------------------------------
// 次項ボタン
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{

        //カソールを元に戻す
        CurseBack();
        ToNextData();
}

//---------------------------------------------------------------------------
//画面印刷
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
     // ステータスメッセージ
     StatBarClear(MSG_09);

     Form1->Print();

     // ステータスメッセージ
     StatBarClear( "  ");

}

//---------------------------------------------------------------------------
//F7 検索
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{

   int  i;
   AnsiString strVal01;
   AnsiString strVal02;
   int HaveSokutei_old ;
   int iKskStart_old  ;

   //検索条件のﾁｪｯｸ
   strVal01 = DelSEPA(Form1->edtymd->Text);
   strVal02 = Form1->edttlno->Text;

   if( !strVal01.Length() || !strVal02.Length() ||
       IsNullSpace(strVal01) || IsNullSpace(strVal02) ||
       !edttlno->Value  ) return ;

   //更新したﾃﾞｰﾀをｾｰﾌﾞするかどうかの確認メッセージ
   if( AllDataChg ){
       switch( MessageDlg( MSG_10, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
                ExecF11();
                break;
            // 「No」       変更を破棄
            case mrNo:
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                return;
                break;
         }
       AllDataChg = 0;
   }

   // ステータスメッセージ
   StatBarClear(MSG_01) ;

   HaveSokutei_old = HaveSokutei;
   iKskStart_old = iKskStart ;

   HaveSokutei = 0;
   iKskStart = 0 ;

    // リード線長さ寸法ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD91
    int iRtn = Kd91_Serch02();
    if( iRtn <= 0 ) {
        if( Save_Click ){
            StatBarClear( " ") ;
            HaveSokutei = HaveSokutei_old ;
            iKskStart =  iKskStart_old ;

         }else{
            // ステータスメッセージ
            StatBarClear( MSG_02) ;

            //画面の初期化
            SetInit(1) ;
            SetEnabel(0);

            Form1->PageCtrl->ActivePage = Form1->TabSheet1;
            GraphyImg->Canvas->Brush->Color = clMenu;
            GraphyImg->Canvas->FillRect( GraphyImg->ClientRect );
         }
         return;
    }

     //画面の初期化
     SetInit(1) ;
     SetEnabel(0) ;

    // 計測ﾃﾞｰﾀNO
    DataNoIdx = 1 ;

    //履歴作画（音ON, 色ON)
    iOption = 1 ;

    // 計測値の変更があったかどうかの指示フラグ
     AllDataChg = 0;
     CurSampChg = 0;
     CurDataChg = 0;

     ////KD93W履歴ﾃﾞｰﾀテーブルの作成
     //Kd93W_Create01(KD91Data[0].KENSA_YMD, KD91Data[0].TOLEY_NO, LOTMAX);
     ////if( iRec >0 ){
     //
     //   //KD93W履歴ﾃﾞｰﾀﾌｧｲﾙを読み込む
     //   i  =  Kd93W_Serch01();
     ////}
	 // 測定履歴も検索する場合   2002/10/28 A.Tamura
	 if( CheckBoxRireki->Checked ){

             //ロットNOの再読み込み　　2003/1/23 A.Tamura
             strVal02 = Form1->edttlno->Text;

	     //KD93W履歴ﾃﾞｰﾀテーブルの作成
	     //int iRec = Kd93W_Create01(KD91Data[0].KENSA_YMD, KD91Data[0].TOLEY_NO, LOTMAX);
	     int iRec = Kd93W_Create01(strVal01, strVal02.ToIntDef(0), LOTMAX);
	 	
	     if( iRec >0 ){

	        //KD93W履歴ﾃﾞｰﾀﾌｧｲﾙを読み込む
	        i  =  Kd93W_Serch01();

	     }else{
	       StatBarClear( MSG_12) ;
	     }

	 } else{

        //KD93W履歴ﾃﾞｰﾀ 削除
        Kd93W_Delete01();

        //KD93W履歴ﾃﾞｰﾀ フォーマット
        KD93WFormat();

		char Xstr[50][5];
		double Max[50];
		double Min[50];
		double Val[50];

		// 作画用変数の初期化
		for(i=0; i<LOTMAX*5; i++ ){
			memset( Xstr[i], 0x0, 5 );
			Max[i] = 0.0;
			Min[i] = 0.0;
			Val[i] = 0.0;
		}

		// 測定履歴を検索しないので測定履歴表示画面をクリアします。
		DrawRireki( Form1->GraphyImg, 0, &Xstr[0][0], Max, Min, Val, -1);
//        iOption = 2;
//        ToDrawGraph(1, iOption);
     }

     //計測ﾃﾞｰﾀがあればそのﾃﾞｰﾀを履歴ﾌｧｲﾙへコピー
     if( HaveSokutei ) CopyKD91Data();

     // 指定した計測予定日とﾄﾚｰNOで検索したﾚｺｰﾄﾞを画面へセット
    int flag = 0;
    for( i=0; i<30; i++ )
    {
          //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
          if( KD91Data[i].SAMPLE_P == -1 )
          {
               // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ

             /*  IsEnabledEdt( pEdt1[i], 0 );
               IsEnabledEdt( pEdt2[i], 0 );
               IsEnabledPnl( pPnlN[i], 0 );

               //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
               IsEnabledEdt( pEdt3[i], 0 );
               IsEnabledEdt( pEdt4[i], 0 );

                // ScrollBarの初期値設定
                pScrl[i]->Min = 0;
                pScrl[i]->Max = 0;
                pScrl[i]->Position = 0 ;
              */

            }else{

                //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがあるの場合
                //ﾃﾞｰﾀ１、ﾃﾞｰﾀ２の設定
               pEdt1[i]->Text =  FormatFloat("0",KD91Data[i].SOKUTEICHI[0] );
               pEdt2[i]->Text =  FormatFloat("0",KD91Data[i].SOKUTEICHI[1] );
               pPnlN[i]->Caption = IntToStr( KD91Data[i].SOKUTEI_NM) ;

               // 例外ﾃﾞｰﾀ の設定
               if( KD91Data[i].SOKUTEI_NM > 2 )
               {
                 pEdt3[i]->Text =  FormatFloat("0",KD91Data[i].SOKUTEICHI[2] );
                 pEdt4[i]->Text =  IntToStr(3);
               }

                if(  KD91Data[i].SOKUTE_KBN == 1 ){
                   // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ
                   IsEnabledEdt( pEdt1[i], 1 );
                   IsEnabledEdt( pEdt2[i], 1 );
                   IsEnabledPnl( pPnlN[i], 1 );

                   // 計測個数＞２の場合
                  if( KD91Data[i].SOKUTEI_NM > 2 )
                  {
                    //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
                    IsEnabledEdt( pEdt3[i], 1 );
                    IsEnabledEdt( pEdt4[i], 1 );
                    IsEnabledScrl(pScrl[i], 1 );

                    // ScrollBarの初期値設定
                    pScrl[i]->Min = 3;
                    pScrl[i]->Max = KD91Data[i].SOKUTEI_NM;
                    pScrl[i]->Position = 3 ;


                  }

                  //最初計測レコード
                  if( flag == 0 && HaveSokutei){
                     flag=1;
                     SamplePositionIdx = i+1 ;
                     iFirstPosition = SamplePositionIdx ;
                  }

                  iLastPosition = KD91Data[i].SAMPLE_P ;

                }else{
                   // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ
                /*   IsEnabledEdt( pEdt1[i], 0 );
                   IsEnabledEdt( pEdt2[i], 0 );
                   IsEnabledPnl( pPnlN[i], 0 );

                    //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
                    IsEnabledEdt( pEdt3[i], 0 );
                    IsEnabledEdt( pEdt4[i], 0 );
                    IsEnabledScrl(pScrl[i],0 );*/
              }
          }
    }

    //備考をヒントにセット 2002/11/08 E.Takase
    SetMEMO();

    if( HaveSokutei ){

         //画面下のﾎﾞﾀﾝを有効にする
         SetEnabel(1) ;

         //カーソルを最初計測値へセット

         pEdt1[SamplePositionIdx-1]->SetFocus();

         DisplayInfo();
        // ToDrawGraph(SamplePositionIdx, iOption);


         //ﾃﾞｰﾀﾍﾞｰｽ中の既存ﾚｺｰﾄﾞを更新する場合、ﾃﾞｰﾀﾍﾞｰｽから読み込んだ
         //ﾃﾞｰﾀを規格範囲内かどうかのチェック

         SetRed(1) ;

         //計測作業が始める
         iKskStart = 1 ;

    }else{
         Form1->PageCtrl->ActivePage = Form1->TabSheet1;
         GraphyImg->Canvas->Brush->Color = clMenu;
         GraphyImg->Canvas->FillRect( GraphyImg->ClientRect );
         SetEnabel(2) ;
   }


    // ステータスメッセージ
    StatBarClear("  ") ;

}

//---------------------------------------------------------------------------
// F10 Option
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     //カソールを元に戻す
     CurseBack();

     ExecF10();
}
void ExecF10(void)
{

     // iOption == 1  測定履歴作画
     // iOPtion == 2  工程能力作画
     // iOption == 3  作画、Beep, 色 --> OFF

    if( !HaveSokutei ) return ;

    if( iOption == 3 ){
       iOption = 1 ;
     }else{
       iOption += 1;
     }

     if( iOption == 1 ){
        //測定履歴作画
        Form1->PageCtrl->Visible = true ;

        // Form1->PageCtrl->ActivePage = TabSheet1;
        Form1->PageCtrl->SelectNextPage(false);
        //StatBarClear("測定履歴 （音ON, 色ON)");

        // 画面色のリセット
        SetRed(2);
     }else if( iOption == 2 )
     {
        // 工程能力作画
        Form1->PageCtrl->Visible = true ;
        //Form1->PageCtrl->ActivePage = TabSheet2;
        Form1->PageCtrl->SelectNextPage(false);
        //StatBarClear("工程能力 （音ON, 色ON)");

        // 画面色のリセット
        SetRed(2) ;
     }else if( iOption == 3 )
     {
        //作画領域をクリア
        Form1->PageCtrl->Visible = false ;
        //StatBarClear("作画なし（音OFF, 色OFF)");

        // 画面色のリセット
        ClearRed();
     }

     //履歴作画と工程能力図
     ToDrawGraph(SamplePositionIdx, iOption);

}
//---------------------------------------------------------------------------
// F11 保存
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
   if( !HaveSokutei ) return ;

   //計測したﾃﾞｰﾀを保存する
   ExecF11();

   Save_Click = 1;

   //次のﾄﾚｰNOが有れば、次のﾄﾚｰNOのﾃﾞｰﾀを自動的に画面へセット
   BtnF07Click(Sender);

   if( BtnF11->Font->Color == clRed )
       BtnF12->SetFocus();

   Save_Click = 0;

}
void ExecF11(void)
{
   if( !HaveSokutei ) return ;

    // ステータスメッセージ
    StatBarClear(MSG_04);

    // ﾃﾞｰﾀをﾌｧｲﾙKD91、Kd92へ書き込む
    Kd91_Update01();

    //入力ﾃﾞｰﾀを更新される場合のフラグのクリア
     AllDataChg = 0;
     CurSampChg = 0;
     CurDataChg = 0;
     Update_err = 0;

     // ステータスメッセージ
     StatBarClear( " ") ;
}
//---------------------------------------------------------------------------
// F12 戻る
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{

   Close();

}

//---------------------------------------------------------------------------

void __fastcall TForm1::edtymdKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      // ステータスメッセージ
     if(SBr1->SimpleText != ""){
        SBr1->SimpleText = "";
        SBr1->Update();
     }

     switch(Key)
     {
         case VK_F1:  ExecF1();               break;
         case VK_F2:  ToPreData();            break;
         case VK_F3:  ToNextData();           break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F7:
                  //検索部にフォーカスがある場合、検索実行
                  BtnF07Click(Sender);

                break;
         case VK_F10:
                      Key = 0;
                      ExecF10();
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         case VK_RETURN:

                      //検索部
                      if( edtymd->Focused()){
                          edttlno->SetFocus();
                          break;
                       }

                       if( edttlno->Focused() || CheckBoxRireki->Focused() ){
                           BtnF07Click( Sender);
                            break;
                        }
                break;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     // ステータスメッセージ
     if(SBr1->SimpleText != ""){
        SBr1->SimpleText = "";
        SBr1->Update();
     }

     switch(Key)
     {
         case VK_F1:  ExecF1();               break;
         case VK_F2:  ToPreData();            break;
         case VK_F3:  ToNextData();           break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
                //検索部以外にフォーカスがある場合、検索部にフォーカスをセット
                edtymd->SetFocus();

                break;
         case VK_F10:
                      Key = 0;
                      ExecF10();
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         case VK_RETURN:

                        //データ計測部
                        if( !BtnF01->Focused() && !BtnF02->Focused() &&
                            !BtnF03->Focused() && !BtnF04->Focused() &&
                            !BtnF05->Focused() && !BtnF06->Focused() &&
                            !BtnF07->Focused() && !BtnF08->Focused() &&
                            !BtnF09->Focused() && !BtnF10->Focused() &&
                            !BtnF11->Focused() && !BtnF12->Focused() ){
                                ToNextData();
                        }
                break;
         case VK_UP:
                break ;
         case VK_LEFT:

                ToPreData();
                break;
         case VK_DOWN:
                break ;
         case VK_RIGHT:

                ToNextData();
                break;


     }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
     edtymd->SetFocus();

     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOの初期化
     SamplePositionIdx = 1;

     // 計測ﾃﾞｰﾀNO
     DataNoIdx = 1 ;

     //計測作業始めるかどうかの指示フラグ
     iKskStart = 0 ;

     // 計測値の変更があったかどうかの指示フラグ
     AllDataChg = 0;
     CurSampChg = 0;
     CurDataChg = 0;


     //担当者名、部門名などを画面へセット
     Pnl1->Caption = BUMO_COD ;
     Pnl2->Caption = BUMO_NAM ;
     Pnl3->Caption = IntToStr(USER_COD );
     Pnl4->Caption = USER_NAM ;

     //20161128 Y.Onishi
     //PC6の場合、エラーメッセージを出さない
     //if (ret_232 < 0) {
     //       Beep();
     //       StatBarClear(MSG_11) ;
     //}
     if (KikiType != 6) {
        if (ret_232 < 0) {
            Beep();
            StatBarClear(MSG_11) ;
        }
     }
}

//--------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   char DirName[256], FileName[256], tempo[64];

     WriteLog("TKS19.exe起動");

      // 機器番号を読込む
      GetCurrentDirectory(256,DirName);
      sprintf(FileName, "%s\\Tks.ini", DirName);
      GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, FileName);							//Seed値
      KikiType = atoi(tempo);
      //2009.03.13 MTS E.Takase [001]  ↓
      //材料試験機（単独使用）は機器タイプを5とする
      //if ( KikiType <= 0 || KikiType > 4)  ret_232 = -1;
      if ( KikiType <= 0 || KikiType > 5)  ret_232 = -1;
      //2009.03.13 MTS E.Takase [001]  ↑
         //  StatBarClear(MSG_00) ;

      ShareFlag = 0;
      //2009.03.13 MTS E.Takase [001]  ↓
      //材料試験機（単独使用）は機器タイプを5とする
      //if (iRS232C) {
      //   if (KikiType == 3 || KikiType == 4) {
      //      ShareFlag = 1;
      //      iChNo = 7;
      //   }
      //}
      if (iRS232C) {
         if (KikiType == 5) {
            ShareFlag = 1;
            iChNo = 10;
         }
      }
      //2009.03.13 MTS E.Takase [001]  ↑

      // 工場区分を読み込む
      GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, FileName);
      iKojoKbn = atoi(tempo);

     // シェアメモリ作成
     if ( ShareFlag ) {

          ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS1", 1);
          ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS2", 2);
          if (ret_232 < 0) {
            ShareFlag = 0;
          }

          //RS232C接続フラグを１に設定
          iShareFlag = 1;

          // チャネル番号の設定
          sprintf(tempo, "CONNECT %d", iChNo);
          SharedMemory_Write(1, 0, tempo, strlen(tempo));
      } else
          iShareFlag = 0;

      //RS232C 読み込みフラグ 初期化
      RSInputFlag = 0;


      //ﾃﾞｰﾀベースとの接続
      Database1->Open() ;

      // 画面に各ｺﾝﾄﾛｰﾙIDを保存する
      SaveCtlID() ;

      // 画面を開く際の初期値ﾃﾞｰﾀの設定
      SetInit(0) ;

      //計測予定日、ﾄﾚｰNO、一覧検索ﾎﾞﾀﾝ, 検索を除く、無効にする
      SetEnabel (0);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::InitEdt(TNumberEdit *P_Edit, AnsiString Str)
{
       P_Edit->Text = Str ;
}
//--------------------------------------------------------------------------
void __fastcall TForm1::InitPnl(TPanel *P_Pnl, AnsiString Str)
{
        P_Pnl->Caption = Str ;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::SetInit(int flag)
{
     int i ;
     AnsiString Str, Str1;

      // メイン画面の初期化

      if( flag == 0 ){
         // 計測予定年月日
         edtymd->Text = FormatDateTime("yyyy/mm/dd",Date());

         // トレーNO
         edttlno->Text ="1";
        }


      // ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO及び測定個数N
      for( i=0; i<30; i++ ){
          InitEdt(pEdt1[i], "0");
          InitEdt(pEdt2[i], "0");
          InitEdt(pEdt3[i], "0");
          InitEdt(pEdt4[i], "0");
          InitPnl(pPnlN[i], "0") ;
      }

      Str = "0" ;
      Str1 = "" ;
      //測定ｻﾝﾌﾟﾙ情報の表示
      InitPnl(Pnl5, Str) ;
      InitPnl(Pnl6, Str) ;

      InitPnl(Pnl7, Str1) ;
      InitPnl(Pnl8, Str1) ;
      InitPnl(Pnl9, Str1) ;
      InitPnl(Pnl10, Str1) ;
      InitPnl(Pnl11, Str1) ;
      InitPnl(Pnl12, Str1) ;

      //ScrollBarの初期値の設定
      for( i=0; i<30; i++ )
      {
        pScrl[i]->Min = 0;
        pScrl[i]->Max = 99;
        pScrl[i]->Position =0;
      }

      //工程能力ｺﾝﾄﾛｰﾙのクリア
      InitPnl(Pnl21, "0.00") ;
      InitPnl(Pnl22, "0.00") ;
      InitPnl(Pnl23, "0.000") ;
      InitPnl(Pnl24, "0") ;

      InitPnl(Pnl31, "0.00000") ;
      InitPnl(Pnl32, "0.00000") ;
      InitPnl(Pnl33, "0.00") ;

      InitPnl(Pnl41, "0.00") ;
      InitPnl(Pnl42, "0.000") ;
      InitPnl(Pnl43, "0.000") ;

}

//--------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledPnl(TPanel *P_Pnl, int flag)
{
       // パネルﾎﾞﾀﾝをEnabled or Unenabled
       //  flag == 1   true    flag == 0  false
       if( flag == 1 ){
           P_Pnl->Enabled = true ;
       }else {
           P_Pnl->Enabled = false ;
        }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledEdt(TNumberEdit *P_Edit, int flag)
{
      // EditﾎﾞﾀﾝをEnabled or Unenabled
      //  flag == 1   true    flag == 0  false
       if( flag == 1 ){
           P_Edit->Enabled = true ;
           P_Edit->Color = clWindow;
       }else {
           P_Edit->Enabled = false ;
           P_Edit->Color = 0x00E0E0E0;
           }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledScrl(TScrollBar *P_Scrl, int flag)
{
       // ScrollﾎﾞﾀﾝをEnabled or Unenabled
       //  flag == 1   true    flag == 0  false
       if( flag == 1 )
           P_Scrl->Enabled = true ;
       else
           P_Scrl->Enabled = false ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetEnabel(int flag )
{
  if( flag == 0 ){
      //画面を開く時に、入力ｺﾝﾄﾛｰﾙを無効にする
      for( int i=0; i<30; i++ )
      {
       IsEnabledEdt( pEdt1[i], 0 );
       IsEnabledEdt( pEdt2[i], 0 );
       IsEnabledEdt( pEdt3[i], 0 );
       IsEnabledEdt( pEdt4[i], 0 );
       IsEnabledPnl( pPnlP[i], 0 );
       IsEnabledPnl( pPnlN[i], 0 );
       IsEnabledScrl( pScrl[i],0 );
       }

         //前項、次項、印刷ﾎﾞﾀﾝなどを無効にする
         BtnF02->Enabled = false ;
         BtnF03->Enabled = false ;
        // BtnF04->Enabled = false ;
        // BtnF05->Enabled = false ;
        // BtnF06->Enabled = false ;
        // BtnF08->Enabled = false ;
        // BtnF09->Enabled = false ;
         BtnF10->Enabled = false ;
         BtnF11->Enabled = false ;
  }else if( flag == 1 ){

         //前項、次項、印刷ﾎﾞﾀﾝなどを有効にする
         if( BtnF02->Enabled==false)  BtnF02->Enabled = true ;
         if( BtnF03->Enabled==false)  BtnF03->Enabled = true ;
        // if( BtnF04->Enabled==false)  BtnF04->Enabled = true ;
        // if( BtnF05->Enabled==false)  BtnF05->Enabled = true ;
        // if( BtnF06->Enabled==false)  BtnF06->Enabled = true ;
        // if( BtnF08->Enabled==false) BtnF08->Enabled = true;
        // if( BtnF09->Enabled==false) BtnF09->Enabled = true ;
         if( BtnF10->Enabled==false) BtnF10->Enabled = true ;
         if( BtnF11->Enabled==false) BtnF11->Enabled = true ;
  }else{
         //前項、次項、印刷ﾎﾞﾀﾝなどを無効にする
         if( BtnF02->Enabled==true) BtnF02->Enabled = false ;
         if( BtnF03->Enabled==true) BtnF03->Enabled = false ;
        // if( BtnF04->Enabled==true) BtnF04->Enabled = false ;
         //if( BtnF05->Enabled==true) BtnF05->Enabled = false ;
       //  if( BtnF06->Enabled==true) BtnF06->Enabled = false ;
       //  if( BtnF08->Enabled==true) BtnF08->Enabled = false ;
       //  if( BtnF09->Enabled==true) BtnF09->Enabled = false ;
         if( BtnF10->Enabled==true) BtnF10->Enabled = false ;
         if( BtnF11->Enabled==true) BtnF11->Enabled = false ;
  }

}

//---------------------------------------------------------------------------
void __fastcall TForm1:: OnEditEnter( int spflag, int dtflag, TNumberEdit *pEdit )
{

    // spflag :  ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
    // dtflag :  一つｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOに対してのﾃﾞｰﾀNO

    if( CurBackFlg ) return ;
    BtnF01->Enabled = false ;
    //計測データ部指示フラグ
    CurField = 2;

    //ｶﾚﾝﾄｶｰｿﾙ位置の背景色を元色へ戻す
    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
    }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
    }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
    }


    // ﾃﾞｰﾀNOの設定
    if( dtflag == 1 || dtflag == 2 ){
       DataNoIdx = dtflag;
    }else {
       DataNoIdx = pEdit->Value;
    }


    // ｻﾝﾌﾟﾙポジション番号の設定
    if( spflag != SamplePositionIdx ){

         //ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝデータを履歴ﾌｧｲﾙへ追加
        if( CurSampChg ) AddKd93W();

        SamplePositionIdx = spflag ;

        DisplayInfo();
        CurSampChg = 0;
    }

    //ｻﾝﾌﾟﾙ情報と作画
    //DisplayInfo();
    ToDrawGraph(SamplePositionIdx, iOption);

   //ｶﾚﾝﾄｶｰｿﾙ位置の背景色の設定
    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color =  clYellow;
    }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color =  clYellow;
    }else {
       pEdt3[SamplePositionIdx-1]->Color =  clYellow;
    }


    CurDataChg = 0;

}

//---------------------------------------------------------------------------

void __fastcall TForm1::edtymdEnter(TObject *Sender)
{
      if( CurBackFlg ) return ;

      //検索条件部
      CurField = 1;

      BtnF01->Enabled = true ;

      if(  edtymd->Focused() ) ymdtl_flg = 1;
      if(  edttlno->Focused()) ymdtl_flg = 2;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_1Enter(TObject *Sender)
{
          OnEditEnter(1,1,Edt01_4);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_2Enter(TObject *Sender)
{

    OnEditEnter(1,2,Edt01_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_3Enter(TObject *Sender)
{
    OnEditEnter(1,3,Edt01_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_4Enter(TObject *Sender)
{
    OnEditEnter(1,4,Edt01_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Enter(TObject *Sender)
{
    OnEditEnter(1,5,Edt01_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_1Enter(TObject *Sender)
{
    OnEditEnter(2,1,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_2Enter(TObject *Sender)
{
    OnEditEnter(2,2,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_3Enter(TObject *Sender)
{
    OnEditEnter(2,3,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_4Enter(TObject *Sender)
{
    OnEditEnter(2,4,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar2Enter(TObject *Sender)
{
    OnEditEnter(2,5,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_1Enter(TObject *Sender)
{
    OnEditEnter(3,1,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_2Enter(TObject *Sender)
{
    OnEditEnter(3,2,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_3Enter(TObject *Sender)
{
    OnEditEnter(3,3,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_4Enter(TObject *Sender)
{
    OnEditEnter(3,4,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar3Enter(TObject *Sender)
{
    OnEditEnter(3,5,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_1Enter(TObject *Sender)
{
    OnEditEnter(4,1,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_2Enter(TObject *Sender)
{
    OnEditEnter(4,2,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_3Enter(TObject *Sender)
{
    OnEditEnter(4,3,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_4Enter(TObject *Sender)
{
    OnEditEnter(4,4,Edt04_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar4Enter(TObject *Sender)
{
    OnEditEnter(4,5,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_1Enter(TObject *Sender)
{
     OnEditEnter(5,1,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_2Enter(TObject *Sender)
{
     OnEditEnter(5,2,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_3Enter(TObject *Sender)
{
     OnEditEnter(5,3,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_4Enter(TObject *Sender)
{
     OnEditEnter(5,4,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar5Enter(TObject *Sender)
{
     OnEditEnter(5,5,Edt05_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt06_1Enter(TObject *Sender)
{
     OnEditEnter(6,1,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_2Enter(TObject *Sender)
{
     OnEditEnter(6,2,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_3Enter(TObject *Sender)
{
     OnEditEnter(6,3,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_4Enter(TObject *Sender)
{
     OnEditEnter(6,4,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar6Enter(TObject *Sender)
{
     OnEditEnter(6,5,Edt06_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt07_1Enter(TObject *Sender)
{
      OnEditEnter(7,1,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_2Enter(TObject *Sender)
{
       OnEditEnter(7,2,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_3Enter(TObject *Sender)
{
       OnEditEnter(7,3,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_4Enter(TObject *Sender)
{
      OnEditEnter(7,4,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar7Enter(TObject *Sender)
{
       OnEditEnter(7,5,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_1Enter(TObject *Sender)
{
       OnEditEnter(8,1,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_2Enter(TObject *Sender)
{
       OnEditEnter(8,2,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_3Enter(TObject *Sender)
{
       OnEditEnter(8,3,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_4Enter(TObject *Sender)
{
       OnEditEnter(8,4,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar8Enter(TObject *Sender)
{
       OnEditEnter(8,5,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_1Enter(TObject *Sender)
{
        OnEditEnter(9,1,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_2Enter(TObject *Sender)
{
        OnEditEnter(9,2,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_3Enter(TObject *Sender)
{
        OnEditEnter(9,3,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_4Enter(TObject *Sender)
{
        OnEditEnter(9,4,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar9Enter(TObject *Sender)
{
        OnEditEnter(9,5,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_1Enter(TObject *Sender)
{
        OnEditEnter(10,1,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_2Enter(TObject *Sender)
{
         OnEditEnter(10,2,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_3Enter(TObject *Sender)
{
        OnEditEnter(10,3,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_4Enter(TObject *Sender)
{
        OnEditEnter(10,4,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar10Enter(TObject *Sender)
{
        OnEditEnter(10,5,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_1Enter(TObject *Sender)
{
        OnEditEnter(11,1,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_2Enter(TObject *Sender)
{
         OnEditEnter(11,2,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_3Enter(TObject *Sender)
{
        OnEditEnter(11,3,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_4Enter(TObject *Sender)
{
        OnEditEnter(11,4,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar11Enter(TObject *Sender)
{
        OnEditEnter(11,5,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_1Enter(TObject *Sender)
{
        OnEditEnter(12,1,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_2Enter(TObject *Sender)
{
        OnEditEnter(12,2,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_3Enter(TObject *Sender)
{
       OnEditEnter(12,3,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_4Enter(TObject *Sender)
{
       OnEditEnter(12,4,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar12Enter(TObject *Sender)
{
       OnEditEnter(12,5,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_1Enter(TObject *Sender)
{
       OnEditEnter(13,1,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_2Enter(TObject *Sender)
{
       OnEditEnter(13,2,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_3Enter(TObject *Sender)
{
       OnEditEnter(13,3,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_4Enter(TObject *Sender)
{
       OnEditEnter(13,4,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar13Enter(TObject *Sender)
{
       OnEditEnter(13,5,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_1Enter(TObject *Sender)
{
       OnEditEnter(14,1,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_2Enter(TObject *Sender)
{
       OnEditEnter(14,2,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_3Enter(TObject *Sender)
{
       OnEditEnter(14,3,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_4Enter(TObject *Sender)
{
       OnEditEnter(14,4,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar14Enter(TObject *Sender)
{
       OnEditEnter(14,5,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_1Enter(TObject *Sender)
{
       OnEditEnter(15,1,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_2Enter(TObject *Sender)
{
       OnEditEnter(15,2,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_3Enter(TObject *Sender)
{
       OnEditEnter(15,3,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_4Enter(TObject *Sender)
{
       OnEditEnter(15,4,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar15Enter(TObject *Sender)
{
       OnEditEnter(15,5,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_1Enter(TObject *Sender)
{
       OnEditEnter(16,1,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_2Enter(TObject *Sender)
{
       OnEditEnter(16,2,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_3Enter(TObject *Sender)
{
       OnEditEnter(16,3,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_4Enter(TObject *Sender)
{
       OnEditEnter(16,4,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar16Enter(TObject *Sender)
{
       OnEditEnter(16,5,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_1Enter(TObject *Sender)
{
       OnEditEnter(17,1,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_2Enter(TObject *Sender)
{
       OnEditEnter(17,2,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_3Enter(TObject *Sender)
{
       OnEditEnter(17,3,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_4Enter(TObject *Sender)
{
       OnEditEnter(17,4,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar17Enter(TObject *Sender)
{
       OnEditEnter(17,5,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_1Enter(TObject *Sender)
{
       OnEditEnter(18,1,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_2Enter(TObject *Sender)
{
       OnEditEnter(18,2,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_3Enter(TObject *Sender)
{
       OnEditEnter(18,3,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_4Enter(TObject *Sender)
{
       OnEditEnter(18,4,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar18Enter(TObject *Sender)
{
       OnEditEnter(18,5,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_1Enter(TObject *Sender)
{
       OnEditEnter(19,1,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_2Enter(TObject *Sender)
{
       OnEditEnter(19,2,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_3Enter(TObject *Sender)
{
       OnEditEnter(19,3,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_4Enter(TObject *Sender)
{
       OnEditEnter(19,4,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar19Enter(TObject *Sender)
{
       OnEditEnter(19,5,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_1Enter(TObject *Sender)
{
       OnEditEnter(20,1,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_2Enter(TObject *Sender)
{
       OnEditEnter(20,2,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_3Enter(TObject *Sender)
{
       OnEditEnter(20,3,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_4Enter(TObject *Sender)
{
       OnEditEnter(20,4,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar20Enter(TObject *Sender)
{
       OnEditEnter(20,5,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_1Enter(TObject *Sender)
{
       OnEditEnter(21,1,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_2Enter(TObject *Sender)
{
        OnEditEnter(21,2,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_3Enter(TObject *Sender)
{
       OnEditEnter(21,3,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_4Enter(TObject *Sender)
{
       OnEditEnter(21,4,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar21Enter(TObject *Sender)
{
       OnEditEnter(21,5,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_1Enter(TObject *Sender)
{
       OnEditEnter(22,1,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_2Enter(TObject *Sender)
{
       OnEditEnter(22,2,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_3Enter(TObject *Sender)
{
       OnEditEnter(22,3,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_4Enter(TObject *Sender)
{
       OnEditEnter(22,4,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar22Enter(TObject *Sender)
{
       OnEditEnter(22,5,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_1Enter(TObject *Sender)
{
       OnEditEnter(23,1,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_2Enter(TObject *Sender)
{
       OnEditEnter(23,2,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_3Enter(TObject *Sender)
{
       OnEditEnter(23,3,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_4Enter(TObject *Sender)
{
       OnEditEnter(23,4,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar23Enter(TObject *Sender)
{
       OnEditEnter(23,5,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_1Enter(TObject *Sender)
{
       OnEditEnter(24,1,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_2Enter(TObject *Sender)
{
       OnEditEnter(24,2,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_3Enter(TObject *Sender)
{
       OnEditEnter(24,3,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_4Enter(TObject *Sender)
{
       OnEditEnter(24,4,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar24Enter(TObject *Sender)
{
       OnEditEnter(24,5,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_1Enter(TObject *Sender)
{
       OnEditEnter(25,1,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_2Enter(TObject *Sender)
{
       OnEditEnter(25,2,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_3Enter(TObject *Sender)
{
       OnEditEnter(25,3,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_4Enter(TObject *Sender)
{
       OnEditEnter(25,4,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar25Enter(TObject *Sender)
{
       OnEditEnter(25,5,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_1Enter(TObject *Sender)
{
       OnEditEnter(26,1,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_2Enter(TObject *Sender)
{
       OnEditEnter(26,2,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_3Enter(TObject *Sender)
{
       OnEditEnter(26,3,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_4Enter(TObject *Sender)
{
       OnEditEnter(26,4,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar26Enter(TObject *Sender)
{
       OnEditEnter(26,5,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_1Enter(TObject *Sender)
{
       OnEditEnter(27,1,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_2Enter(TObject *Sender)
{
       OnEditEnter(27,2,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_3Enter(TObject *Sender)
{
       OnEditEnter(27,3,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_4Enter(TObject *Sender)
{
       OnEditEnter(27,4,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar27Enter(TObject *Sender)
{
       OnEditEnter(27,5,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_1Enter(TObject *Sender)
{
       OnEditEnter(28,1,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_2Enter(TObject *Sender)
{
       OnEditEnter(28,2,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_3Enter(TObject *Sender)
{
       OnEditEnter(28,3,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_4Enter(TObject *Sender)
{
       OnEditEnter(28,4,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar28Enter(TObject *Sender)
{
       OnEditEnter(28,5,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_1Enter(TObject *Sender)
{
       OnEditEnter(29,1,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_2Enter(TObject *Sender)
{
       OnEditEnter(29,2,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_3Enter(TObject *Sender)
{
       OnEditEnter(29,3,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_4Enter(TObject *Sender)
{
       OnEditEnter(29,4,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar29Enter(TObject *Sender)
{
       OnEditEnter(29,5,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_1Enter(TObject *Sender)
{
       OnEditEnter(30,1,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_2Enter(TObject *Sender)
{
       OnEditEnter(30,2,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_3Enter(TObject *Sender)
{
       OnEditEnter(30,3,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_4Enter(TObject *Sender)
{
       OnEditEnter(30,4,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar30Enter(TObject *Sender)
{
       OnEditEnter(30,5,Edt30_4);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{

   //計測作業始まる前 、つまり「検索」ﾎﾞﾀﾝを押す前
   if( ! iKskStart )  return ;

   // マウスでScrollBarを変更する以外の場合
   if( iSaveFlag ) return ;

   // マウスでScrollBarを変更する場合
   if( SamplePositionIdx >0 &&
       ( SamplePositionIdx >= iFirstPosition && SamplePositionIdx <= iLastPosition ) &&
         DataNoIdx > 2   ){

          SaveRegaiDt();
          CheckInKikaku(1);
          ToDrawGraph(SamplePositionIdx, iOption);

          int pos = pScrl[SamplePositionIdx-1]->Position ;

          pEdt4[SamplePositionIdx-1]->Text = IntToStr(pos);

          // ﾃﾞｰﾀ更新
          pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",
                                      KD91Data[SamplePositionIdx-1].SOKUTEICHI[pos-1] );

          pEdt3[SamplePositionIdx-1]->SetFocus() ;
          pEdt3[SamplePositionIdx-1]->SelectAll() ;

           // 更新したデータをチェックする
           CheckInKikaku(0);

      }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Edt01_1Change(TObject *Sender)
{
    if( iKskStart ) {

   //  TNumberEdit *Edt = (TNumberEdit *)Sender;

     //画面に表示しているﾃﾞｰﾀ値を更新される場合
         AllDataChg = 1;
         CurSampChg = 1;
         CurDataChg = 1;

        // 計測したデータCount
        if ( KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR < DataNoIdx ){
             KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR = DataNoIdx ;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_1Exit(TObject *Sender)
{
   // 計測値のチェック
   if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1) {

     if( CurDataChg ){

        CurDataChg = 0;
        if( DataNoIdx == 1 ){
           KD91Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;

        }else if( DataNoIdx == 2 ){
           KD91Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;
        }else {
           SaveRegaiDt();
           if (iSaveFlag ){
             CheckInKikaku(1);
             return ; }
        }
      }
       // CheckInKikaku();
       // DisplayInfo();
      CheckInKikaku(1);

      //ｶﾚﾝﾄｶｰｿﾙ位置の背景色を元色へ戻す
      if( DataNoIdx == 1 ){
         pEdt1[SamplePositionIdx-1]->Color = clWindow;
      }else if( DataNoIdx == 2 ){
         pEdt2[SamplePositionIdx-1]->Color = clWindow;
      }else {
         pEdt3[SamplePositionIdx-1]->Color = clWindow;
      }
   }
}

//--------------------------------------------------------------------------

void __fastcall TForm1::edtymdChange(TObject *Sender)
{
     // ステータスメッセージ
     StatBarClear( "  ");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edt01_4Exit(TObject *Sender)
{
     // 入力したﾃﾞｰﾀNO ３〜９９を超えているかどうかのチェック
   if( iKskStart ) {
       CheckDtNo() ;
       CurDataChg = 0;}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::PageCtrlChange(TObject *Sender)
{
  if( HaveSokutei ){

       // ステータスメッセージ
       StatBarClear( "  ");

        //測定履歴作画
       if( Form1->PageCtrl->ActivePage == TabSheet1)
          iOption = 1 ;
       if( Form1->PageCtrl->ActivePage == TabSheet2)
          iOption = 2;

       ToDrawGraph(SamplePositionIdx, iOption);
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    char tempo[56];

    // データを変更したかどうかのフラグチェック
    if( AllDataChg ){
        switch( MessageDlg( MSG_10, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
               // BtnF11Click(Sender);
                              // ステータスメッセージ
               StatBarClear(MSG_04);

               // ﾃﾞｰﾀをﾌｧｲﾙKD01、Kd02へ書き込む
               Kd91_Update01();

               //入力ﾃﾞｰﾀを更新される場合のフラグのクリア
               AllDataChg = 0;
               CurSampChg = 0;
               CurDataChg = 0;

               // ステータスメッセージ
               StatBarClear( " ") ;

                if( Update_err ){
                  CanClose = false;
                  Update_err = 0;
                }
                
                break;
            // 「No」       変更を破棄
            case mrNo:
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
                break;
        }
    }

    if( CanClose == true ) {

      if ( ShareFlag ) {
        sprintf(tempo, "CLOSE");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        sprintf(tempo, "EXIT");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        SharedMemory_Close(1);
        SharedMemory_Close(2);
      }

    }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF02Enter(TObject *Sender)
{
   BtnF01->Enabled = false ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt01_4Change(TObject *Sender)
{
  int n;

  if( iKskStart ) {

      n = pEdt4[SamplePositionIdx-1]->Value;

     if( n >= 3 && n <= KD91Data[SamplePositionIdx-1].SOKUTEI_NM ){
          if( n == pScrl[SamplePositionIdx-1]->Position ) return ;
         pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD91Data[SamplePositionIdx-1].SOKUTEICHI[n-1] );
         pScrl[SamplePositionIdx-1]->Position = n ;

         DataNoIdx = n;
     }
   }

  }
//---------------------------------------------------------------------------

void __fastcall TForm1::ExtractCode(AnsiString str)
{
    //ユーザコード、ユーザ名、部署コード、部署名 抽出
    int i,n1,m,strlen;

    //初期化
	USER_COD = 0;
	USER_NAM = "";
	BUMO_COD = "";
	BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //区切り記号","の検索
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=iの時は文字列NULL
                switch(m){
                //変数に文字列代入
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //次の文字列開始位置
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }
}

//------------------------------------------------------------------------
void __fastcall TForm1::BtnF11Enter(TObject *Sender)
{
    BtnF01->Enabled = false ;

    BtnF11->Font->Color=clRed ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF11Exit(TObject *Sender)
{
    BtnF11->Font->Color=clBlack ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Enter(TObject *Sender)
{
    BtnF12->Font->Color=clRed ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Exit(TObject *Sender)
{
   BtnF12->Font->Color=clBlack ;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//備考入力画面 表示 2002/11/07 Add E.Takase
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{

    //カソールを元に戻す
    CurseBack();
    ExecF6();
    //備考をヒントにセット 2002/11/08 E.Takase
    if ( Form3->ModalResult == 1 ) {

        SetMEMO();
        AllDataChg = 1;
    }
}
void ExecF6(void)
{
    if( !HaveSokutei ) return ;

    Form3->ShowModal();

}
//---------------------------------------------------------------------------

// 検査予定年月日の↑↓ボタン　2002/10/28 A.Tamura
void __fastcall TForm1::UpDownymdClick(TObject *Sender, TUDBtnType Button)
{

   try{

      //char str[256];
      //sprintf(str,"Max=%d Min=%d Pos=%d", UpDownymd->Max, UpDownymd->Min, UpDownymd->Position);

      // 検査予定年月日
      edtymd->SetFocus();
      TDateTime dtDate = StrToDate(edtymd->Text);
      if( Button == Comctrls::btNext ){
         dtDate++;
      } else{
         dtDate--;
      }
      edtymd->Text = FormatDateTime("yyyy/mm/dd",dtDate.FormatString("YYYY/MM/DD"));
   }
   catch(...){
   }
}
//---------------------------------------------------------------------------

// トレーNOの↑↓ボタン　2002/10/28 A.Tamura
void __fastcall TForm1::UpDowntlnoClick(TObject *Sender, TUDBtnType Button)
{
   int i;

   try{
      //char str[256];
      //sprintf(str, "Max=%d Min=%d Pos=%d",UpDowntlno->Max, UpDowntlno->Min, UpDowntlno->Position);

      // トレーNO - 1
      edttlno->SetFocus();
      i = StrToInt(edttlno->Text);
      if( Button == Comctrls::btNext ){
         if( i < 99 )i++;
      } else{
         if( i > 1 ) i--;
      }
      edttlno->Text = IntToStr(i);
   }
   catch(...){
   }

}
//---------------------------------------------------------------------------
//備考をヒントにセット 2002/11/07 E.Takse
void __fastcall TForm1::SetMEMO(void)
{
    int i;

	for( i=0; i<30; i++ )
    {
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{
			//pPnlP[i]->ShowHint = false;
			pEdt1[i]->ShowHint = false;
			pEdt2[i]->ShowHint = false;
			pEdt3[i]->ShowHint = false;
			pEdt4[i]->ShowHint = false;
			pScrl[i]->ShowHint = false;
			pPnlN[i]->ShowHint = false;
		} else {
			if ( Trim(KD91Data[i].MEMO) != "" ) {
				//pPnlP[i]->Hint = KD91Data[i].MEMO;
				pEdt1[i]->Hint = KD91Data[i].MEMO;
				pEdt2[i]->Hint = KD91Data[i].MEMO;
				pEdt3[i]->Hint = KD91Data[i].MEMO;
				pEdt4[i]->Hint = KD91Data[i].MEMO;
				pScrl[i]->Hint = KD91Data[i].MEMO;
				pPnlN[i]->Hint = KD91Data[i].MEMO;

				//pPnlP[i]->ShowHint = true;
				pEdt1[i]->ShowHint = true;
				pEdt2[i]->ShowHint = true;
				pEdt3[i]->ShowHint = true;
				pEdt4[i]->ShowHint = true;
				pScrl[i]->ShowHint = true;
				pPnlN[i]->ShowHint = true;

			} else {
				//pPnlP[i]->ShowHint = false;
				pEdt1[i]->ShowHint = false;
				pEdt2[i]->ShowHint = false;
				pEdt3[i]->ShowHint = false;
				pEdt4[i]->ShowHint = false;
				pScrl[i]->ShowHint = false;
				pPnlN[i]->ShowHint = false;

			}
		}
	 }

}
//---------------------------------------------------------------------------


