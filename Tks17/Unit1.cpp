/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１７）                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 固有抵抗率測定メインプログラム                      *
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
int iChNo = 2;
int iChNo_Old=2; ;
int KikiType = 1;
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
// KD71構造体変数
structKD71 KD71Data[30];      // 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙ  KD71

//KD73W構造体変数
structKD73W KD73WData[30];    // 固有抵抗率履歴ﾃﾞｰﾀﾜｰｸﾌｧｲﾙ  KD73W

//KD51構造体変数
structKD51 KD51Data[30];      // 母体比重ﾃﾞｰﾀﾜｰｸﾌｧｲﾙ  KD51
//---------------------------------------------------------------------------
//画面操作用変数
int iRec_Kd71;              // 一覧検索結果件数
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
int AllDataChg=0;           // 画面に表示しているﾃﾞｰﾀ更新されたかどうか
int CurSampChg=0;           // ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOのﾃﾞｰﾀを更新されたかどうか
int CurDataChg=0;           // ｶﾚﾝﾄ計測値を更新されたかどうか
int Update_err = 0;         // 計測ﾃﾞｰﾀを保存する際エラーが発生しているかどうか
int Save_Click =0;          //[保存」ﾎﾞﾀﾝを押した場合の指示フラグ

int iSaveFlag= 0;           // ScrollbarのChangeイベントで使う変数

int CurBackFlg =0 ;
int iKomoku=1;              //測定項目の指示フラグ

int HaveSokutei = 0 ;       //ﾃﾞｰﾀﾍﾞｰｽから検索結果中で計測ﾃﾞｰﾀあるかどうかの指示フラグ
int FlagAV =0;              //ｶｰｿﾙが電流にあるか電圧にあるかの指示フラグ
int iBotai;                 // 母体比重計測ﾃﾞｰﾀ反印するかどうかの指示フラグ

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
AnsiString MSG_13 = "母体比重の計測結果を反映させますか？" ;
// 2004/09/13 A.Tamura 検索時は、常に「母体比重の計測結果を反映させますか？」を表示するため
AnsiString MSG_16 = "次のトレーの母体比重計測結果を反映させますか？" ;

//----------------------------------------------------------------------------
// 画面ｺﾝﾄﾛｰﾙ保存変数
TNumberEdit *pEdt1[30] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt2[30] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt3[30] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt4[30] ;    //  ﾃﾞｰﾀ値番号を保存
TPanel *pPnlP[30] ;         //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
TPanel *pPnlN[30] ;         //  列N(ﾃﾞｰﾀ個数)のｺﾝﾄﾛｰﾙを保存
TScrollBar *pScrl[30];      //  ScrollBarのｺﾝﾄﾛｰﾙを保存

//測定明細
TNumberEdit *pEdt1_S[2] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt2_S[2] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt3_S[2] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存

TNumberEdit *pEdt1_V[2] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt2_V[2] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt3_V[2] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt1_A[2] ;    //  列ﾃﾞｰﾀ１のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt2_A[2] ;    //  列ﾃﾞｰﾀ2 のｺﾝﾄﾛｰﾙを保存
TNumberEdit *pEdt3_A[2] ;    //  列ﾃﾞｰﾀ3 のｺﾝﾄﾛｰﾙを保存

TNumberEdit *pEdt4_S[4] ;    //  ﾃﾞｰﾀ値番号を保存
TPanel *pPnl_S[4] ;          //  列NO（ﾎﾟｼﾞｼｮﾝ番号）のｺﾝﾄﾛｰﾙを保存
TScrollBar *pScrl_S[4];      //  ScrollBarのｺﾝﾄﾛｰﾙを保存

// 関数の宣言
void SaveCtlID() ;
void ToDrawGraph( int, int  ) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] , int );
void SetEnabel(int );
void SetEnter(void);
int SaveRegaiDt(void);
void CheckInKikaku(int );
int  CheckInKikaku_1(int) ;
int  CheckInKikaku_2(int) ;   //2002/12/02 E.Takase
void CheckInKikaku_3(void );
void CheckInKikaku_4(void );  //2002/12/02 E.Takase
int  CheckDtNo(void);
void ToNextData(void);
void ToPreData(void);
void ToNextData_AV(void);
void ToPreData_AV(void);
void ReturnExec(void);
void DisplayInfo(void);
void StatBarClear(AnsiString );
void ClearRed(void) ;
void SetRed(int );
void CurseBack(void);

void ExecF1(void);
void ExecF4(void);
void ExecF6(void); //2002/11/07 E.Takase
void ExecF8(void);
void ExecF9(void);
void ExecF10(void);
bool ExecF11(void);

void KD73WFormat(void);
void AddKd73W(void);
int  CheckLotNo(int ) ;
void CopyKD71Data(void) ;
void KD71Format(void);

int  Kd71_Serch01(void);
int  Kd71_Serch02(void);
int  Kd71_Serch03( void);
void Kd71_Update01(void);
long Kd73W_Create01(AnsiString, int, int) ;
int  Kd73W_Serch01();
int  IsNullSpace(AnsiString);
int  KTeikouCal(int ,int ) ;
int  CheckKomoku(int , int ) ;
void DenryuCheck(void) ;

void KD51Format(void);
void SetTable51(void );
int  Kd51_Serch02(void) ;
void CopyKD51to71(void) ;
void Kd73W_Delete01(void);
void KD73WFormat(void);

extern void WriteLog(char *);
extern void WriteLog2(AnsiString);		// 2004/08/30 A.Tamura ログ出力
int GetItem(char **, char *) ;

AnsiString DelSEPA( AnsiString );
AnsiString InsSEPA( AnsiString );

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//--------------------------------------------------------------------------
void __fastcall TForm1::OnNotifyWriteData(TMessage &Message)
{
 int nNumber;
 double dV, dA;
 char item1[56], item2[56], *p;


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
                                 SamplePositionIdx <= iLastPosition  )){


           if( KikiType == 1 || KikiType == 2 ){
               if( iKomoku == 3  || iKomoku == 4 ) return ;
           }

           if( KikiType == 3 || KikiType == 4 ){
               if( iKomoku == 1 || iKomoku == 2 ) return ;
           }

           if( KikiType == 1 || KikiType == 2 ){
              dV = atof( SharedBuff );
           }else{
              item1[0] = NULL ;
              item2[0] = NULL ;

              p= SharedBuff ;

              GetItem( &p, item1) ;
              GetItem( &p, item2);

              dV = atof( item1 );
              dA = atof( item2 );
           }

           if( DataNoIdx == 1 ) {
                  if( iKomoku == 1 || iKomoku == 2 )
                      pEdt1_S[iKomoku-1]->Text = FormatFloat("#0.000",dV );
                  else if( iKomoku == 3){

                      pEdt1_V[0]->Text = FormatFloat("#0.00",dV );
                      pEdt1_A[0]->Text = FormatFloat("#0.00",dA );
                 }else{
                      pEdt1_V[1]->Text = FormatFloat("#0.00",dV );
                      pEdt1_A[1]->Text = FormatFloat("#0.00",dA );
                 }
           }else if (DataNoIdx == 2 ){
                  if( iKomoku == 1 || iKomoku == 2 )
                      pEdt2_S[iKomoku-1]->Text = FormatFloat("#0.000",dV );
                  else if( iKomoku == 3 ){
                      pEdt2_V[0]->Text = FormatFloat("#0.00",dV );
                      pEdt2_A[0]->Text = FormatFloat("#0.00",dA );
                  }else{
                      pEdt2_V[1]->Text = FormatFloat("#0.00",dV );
                      pEdt2_A[1]->Text = FormatFloat("#0.00",dA );
                  }
           }else{
                  if( iKomoku == 1 || iKomoku == 2 )
                      pEdt3_S[iKomoku-1]->Text = FormatFloat("#0.000",dV );
                  else if( iKomoku == 3 ){
                      pEdt3_V[0]->Text = FormatFloat("#0.00",dV );
                      pEdt3_A[0]->Text = FormatFloat("#0.00",dA );
                  }else{
                      pEdt3_V[1]->Text = FormatFloat("#0.00",dV );
                      pEdt3_A[1]->Text = FormatFloat("#0.00",dA );
                  }
           }

           //RS232C読み込みフラグ1
           RSInputFlag = 1;

           //ｶﾚﾝﾄﾃﾞｰﾀをセットしてからカーソルを自動的に次の測定値へ移動
           if( iKomoku == 1 || iKomoku == 2 ){
               ToNextData();
           }else{
               ToNextData_AV();
           }
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

     //固有抵抗率ﾃﾞｰﾀﾌｧｲﾙからデータを抽出
     iRec_Kd71 = Kd71_Serch01() ;

      if( iRec_Kd71 <= 0 ) {
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

    if( iKomoku == 1 || iKomoku == 2 )
           ToPreData();
    else
          ToPreData_AV();
 }

//---------------------------------------------------------------------------
// 次項ボタン
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    //カソールを元に戻す
    CurseBack();

    if( iKomoku == 1 || iKomoku == 2 )
        ToNextData();
    else
        ReturnExec();
}

//---------------------------------------------------------------------------
//項目F4
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    //カソールを元に戻す
    CurseBack();

    ExecF4();
}

void ExecF4(void)
{
   if( !HaveSokutei ) return ;

   //厚さ,幅,長さ、重量を計測の場合
   if( iKomoku == 4 || iKomoku == 3 ){
       if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
           iKomoku = 2 ;
           Form1->Rad2->Checked = true ;
       }else{
           iKomoku = 1 ;
           Form1->Rad1->Checked = true ;
       }
   }else if( iKomoku == 1 ) {
       if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){
          iKomoku =3 ;
          Form1->Rad3->Checked = true ;
       } else {
          iKomoku =2 ;
          Form1->Rad2->Checked = true ;
       }
   }else if( iKomoku == 2 ) {
       iKomoku =3 ;
       Form1->Rad3->Checked = true ;
   }

}
//---------------------------------------------------------------------------
//マウスで項目を選択する場合
void __fastcall TForm1::Rad1Click(TObject *Sender)
{
   int i;
   char tempo[64];


   //厚さ,幅計測の場合
   if( Rad1->Checked == true  ){
       iKomoku = 1 ;
       iChNo = iChNo_Old ;
       if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
            iKomoku  <= 2 && iChNo <= 5 ) {
             BtnF08->Enabled = true ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
       }else
            BtnF08->Enabled = false ;

   }else if( Rad2->Checked == true ) {
       iKomoku =2 ;
       iChNo = iChNo_Old ;
       if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
            iKomoku  <= 2 && iChNo <= 5 ) {
            BtnF08->Enabled = true ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
       }else
            BtnF08->Enabled = false ;

   }else if( Rad3->Checked == true ) {
       iKomoku =3 ;

       //電流チェック
       DenryuCheck();

       if ( ShareFlag ){

         iChNo_Old = iChNo ;
         iChNo = 9 ;

         if(  KikiType == 3 || KikiType == 4   ) {

            Form1->BtnF08->Enabled = false ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
         }else
           Form1->BtnF08->Enabled = true ;

       //  iChNo = iChNo_Old ;

       }else
         Form1->BtnF08->Enabled = false ;
   }

   // ScrollBarの初期値設定
   int n;
   for( i=0; i<30; i++ ){
        if( KD71Data[i].SOKUTE_KBN == 1  &&
           KD71Data[i].SOKUTEI_NM > 2  ){
           n=pEdt4[i]->Value ;
           if( n > 3 ){
             pScrl[i]->Position = 3 ;
             pEdt4[i]->Text="3";
             pEdt3[i]->Text = FormatFloat("0", KD71Data[i].SOKUTEI_T[2]);
           }
        }
   }

     // 計測値１,計測値２の有効か無効かの設定
     for( i=0; i<2; i++ ){
      if( i==iKomoku-1){
          IsEnabledEdt( pEdt1_S[i], 1 );
          IsEnabledEdt( pEdt2_S[i], 1 );
      }else{
          IsEnabledEdt( pEdt1_S[i], 0 );
          IsEnabledEdt( pEdt2_S[i], 0 );
      }
     }

     if( iKomoku == 3 || iKomoku == 4 ){
          IsEnabledEdt( pEdt1_V[0], 1 );
          IsEnabledEdt( pEdt1_A[0], 1 );
          IsEnabledEdt( pEdt2_V[0], 1 );
          IsEnabledEdt( pEdt2_A[0], 1 );
          IsEnabledEdt( pEdt1_V[1], 1 );
          IsEnabledEdt( pEdt1_A[1], 1 );
          IsEnabledEdt( pEdt2_V[1], 1 );
          IsEnabledEdt( pEdt2_A[1], 1 );
     }else{
          IsEnabledEdt( pEdt1_V[0], 0 );
          IsEnabledEdt( pEdt1_A[0], 0 );
          IsEnabledEdt( pEdt2_V[0], 0 );
          IsEnabledEdt( pEdt2_A[0], 0 );
          IsEnabledEdt( pEdt1_V[1], 0 );
          IsEnabledEdt( pEdt1_A[1], 0 );
          IsEnabledEdt( pEdt2_V[1], 0 );
          IsEnabledEdt( pEdt2_A[1], 0 );
     }

    //測定個数＞２の場合
    if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM  > 2 ){

            //３個目以降の計測データｺﾝﾄﾛｰﾙを有効にする
            for( i=0; i< 2; i++ ){
               if( i== iKomoku-1 ){
                    IsEnabledEdt( pEdt3_S[i], 1 );
                    IsEnabledEdt( pEdt4_S[i], 1 );
                    IsEnabledPnl( pPnl_S[i], 1 );
                    pScrl_S[i]->Enabled = true ;

                }else{
                    IsEnabledEdt( pEdt3_S[i], 0 );
                    IsEnabledEdt( pEdt4_S[i], 0 );
                    IsEnabledPnl( pPnl_S[i], 0 );
                    pScrl_S[i]->Enabled = false ;
                }
            }

            if( iKomoku == 3 || iKomoku == 4 ){
                    IsEnabledEdt( pEdt3_V[0], 1 );
                    IsEnabledEdt( pEdt3_A[0], 1 );
                    IsEnabledEdt( pEdt4_S[2], 1 );
                    IsEnabledPnl( pPnl_S[2], 1 );
                    pScrl_S[2]->Enabled = true ;
                    IsEnabledEdt( pEdt3_V[1], 1 );
                    IsEnabledEdt( pEdt3_A[1], 1 );
                    IsEnabledEdt( pEdt4_S[3], 1 );
                    IsEnabledPnl( pPnl_S[3], 1 );
                    pScrl_S[3]->Enabled = true ;
            }else{
                    IsEnabledEdt( pEdt3_V[0], 0 );
                    IsEnabledEdt( pEdt3_A[0], 0 );
                    IsEnabledEdt( pEdt4_S[2], 0 );
                    IsEnabledPnl( pPnl_S[2], 0 );
                    pScrl_S[2]->Enabled = false ;
                    IsEnabledEdt( pEdt3_V[1], 0 );
                    IsEnabledEdt( pEdt3_A[1], 0 );
                    IsEnabledEdt( pEdt4_S[3], 0 );
                    IsEnabledPnl( pPnl_S[3], 0 );
                    pScrl_S[3]->Enabled = false ;
            }

     }else{

             //３個目以降の計測データｺﾝﾄﾛｰﾙを無効にする
             for(int i=0; i<4; i++){
                 pScrl_S[i]->Enabled = false ;
                 IsEnabledEdt( pEdt4_S[i], 0 );
                 IsEnabledPnl( pPnl_S[i], 0 );
            }

            for(int i=0; i<2; i++)
                 IsEnabledEdt( pEdt3_S[i], 0 );

            for( i=2; i<4; i++ )
            {
                 IsEnabledEdt( pEdt3_V[i-2], 0 );
                 IsEnabledEdt( pEdt3_A[i-2], 0 );
            }
     }

     //ｶｰｿﾙを測定データ明細へ移動
    if( DataNoIdx == 1 ){
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt1_S[iKomoku-1]->SetFocus();
          pEdt1_S[iKomoku-1]->SelectAll();
       }else{
          if( FlagAV == 1  || FlagAV == 0){
            pEdt1_V[iKomoku-3]->SetFocus();
            pEdt1_V[iKomoku-3]->SelectAll();
          }else{
            pEdt1_A[iKomoku-3]->SetFocus();
            pEdt1_A[iKomoku-3]->SelectAll();
          }
       }
    }else if( DataNoIdx == 2 ){
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt2_S[iKomoku-1]->SetFocus();
          pEdt2_S[iKomoku-1]->SelectAll();
       }else{
          if( FlagAV == 1  || FlagAV == 0){
            pEdt2_V[iKomoku-3]->SetFocus();
            pEdt2_V[iKomoku-3]->SelectAll();
          }else{
            pEdt2_A[iKomoku-3]->SetFocus();
            pEdt2_A[iKomoku-3]->SelectAll();
          }
       }
    }else {
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt3_S[iKomoku-1]->SetFocus();
          pEdt3_S[iKomoku-1]->SelectAll();
       }else{
          if(FlagAV == 1  || FlagAV == 0 ){
            pEdt3_V[iKomoku-3]->SetFocus();
            pEdt3_V[iKomoku-3]->SelectAll();
          }else{
            pEdt3_A[iKomoku-3]->SetFocus();
            pEdt3_A[iKomoku-3]->SelectAll();
          }
       }
    }
  //ｶｰｿﾙを先頭計測値へ戻る
  // pEdt1[iFirstPosition-1]->SetFocus();

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
   int HaveSokutei_old;
   int iKskStart_old;
   bool ret;

   // 検索条件のﾁｪｯｸ
   strVal01 = DelSEPA(Form1->edtymd->Text);
   strVal02 = Form1->edttlno->Text;

   if( !strVal01.Length() || !strVal02.Length() ||
       IsNullSpace(strVal01) || IsNullSpace(strVal02) ||
       !edttlno->Value  ) return ;

   // 更新したﾃﾞｰﾀをｾｰﾌﾞするかどうかの確認メッセージ
   if( AllDataChg ){
       switch( MessageDlg( MSG_10, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
                ret = ExecF11();
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

   if( Save_Click ){

      // 指定した検査予定日とﾄﾚｰNOがない場合、何もしない
      if( Kd71_Serch03() < 0 )  return ;

      // 2004/09/13 A.Tamura 保存時の次トレー検索時も母体比重反映の確認を行う。
      // 母体比重計測ﾃﾞｰﾀを読み込むかどうかの確認メッセージ
      iBotai = 0;
      switch( MessageDlg( MSG_16, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」
            case mrYes:
                 iBotai = 1;
                 break;
            // 「No」
            case mrNo:
                 iBotai = 0;
                 break;
            case mrCancel:
                 iBotai = 0;
                 return;
                 break;
      }
   }else{

      // 母体比重計測ﾃﾞｰﾀを読み込むかどうかの確認メッセージ
      iBotai = 0;
      switch( MessageDlg( MSG_13, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」
            case mrYes:
                 iBotai = 1;
                 break;
            // 「No」
            case mrNo:
                 iBotai = 0;
                 break;
            case mrCancel:
                 iBotai = 0;
                 return;
                 break;
      }
   }
   // ステータスメッセージ
   StatBarClear(MSG_01) ;
   HaveSokutei_old = HaveSokutei;
   iKskStart_old = iKskStart ;

   HaveSokutei = 0;
   iKskStart = 0 ;

    // KD71Data構造体変数の初期化
    KD71Format();

    if( iBotai ){

       // 母体比重計測で計測した厚さ、幅を検索する
       // 母体比重ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD51
       if( Kd51_Serch02() > 0 )
           CopyKD51to71();

    }

    // 固有抵抗率ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD71
    if(  Kd71_Serch02() <= 0 ) {
        if( Save_Click ){
            StatBarClear( " ") ;
            HaveSokutei = HaveSokutei_old;
            iKskStart =  iKskStart_old;

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

    // KD71Data構造体変数の初期化
    KD73WFormat();

	// 測定履歴も検索する場合   2002/10/28 A.Tamura
	if( CheckBoxRireki->Checked ){

            //ロットNOの再読み込み　　2003/1/23 A.Tamura
            strVal02 = Form1->edttlno->Text;

            //KD73W履歴ﾃﾞｰﾀテーブルの作成
	    //int iRec = Kd73W_Create01(KD71Data[0].KENSA_YMD, KD71Data[0].TOLEY_NO, LOTMAX);
	    int iRec = Kd73W_Create01(strVal01, strVal02.ToIntDef(0), LOTMAX);

		if( iRec >0 ){

		//KD73W履歴ﾃﾞｰﾀﾌｧｲﾙを読み込む
			i  =  Kd73W_Serch01();

		}else{
			StatBarClear( MSG_12) ;
		}

	} else{


        //KD73W履歴ﾃﾞｰﾀ 削除
        Kd73W_Delete01();

        //KD73W履歴ﾃﾞｰﾀ フォーマット
        KD73WFormat();

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
     if( HaveSokutei ) CopyKD71Data();

     // 指定した計測予定日とﾄﾚｰNOで検索したﾚｺｰﾄﾞを画面へセット
    int flag = 0;
    for( i=0; i<30; i++ )
    {
           //2003.02.05 E.Takase
           if ( KD71Data[i].KEIJYO_KBN == 5 ) { //コンミ
              pEdt1[i]->FPos = 2;
              pEdt2[i]->FPos = 2;
              pEdt3[i]->FPos = 2;
           } else {
              pEdt1[i]->FPos = 0;
              pEdt2[i]->FPos = 0;
              pEdt3[i]->FPos = 0;
           }

          //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
          if( KD71Data[i].SAMPLE_P == -1 )
          {
               // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ
            /*   IsEnabledEdt( pEdt1[i], 0 );
               IsEnabledEdt( pEdt2[i], 0 );
               IsEnabledPnl( pPnlN[i], 0 );

               //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
               IsEnabledEdt( pEdt3[i], 0 );
               IsEnabledEdt( pEdt4[i], 0 );

                // ScrollBarの初期値設定
                //pScrl[i]->Min = 0;
                //pScrl[i]->Max = 0;
                //pScrl[i]->Position = 0 ;
                IsEnabledScrl(pScrl[i],0 );
              */
            }else{

               //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがあるの場合
               //ﾃﾞｰﾀ１、ﾃﾞｰﾀ２の設定

               //2003.02.05 E.Takase
               if ( KD71Data[i].KEIJYO_KBN == 5 ) { //コンミ
                  pEdt1[i]->Text =  FormatFloat("0.00",KD71Data[i].SOKUTEI_T[0] );
                  pEdt2[i]->Text =  FormatFloat("0.00",KD71Data[i].SOKUTEI_T[1] );
               } else {
                  pEdt1[i]->Text =  FormatFloat("0",KD71Data[i].SOKUTEI_T[0] );
                  pEdt2[i]->Text =  FormatFloat("0",KD71Data[i].SOKUTEI_T[1] );
               }
               pPnlN[i]->Caption = IntToStr( KD71Data[i].SOKUTEI_NM) ;

               // 例外ﾃﾞｰﾀ の設定
               if( KD71Data[i].SOKUTEI_NM > 2 )
               {
                    //2003.02.05 E.Takase
                    if ( KD71Data[i].KEIJYO_KBN == 5 ) { //コンミ
                       pEdt3[i]->Text =  FormatFloat("0.00",KD71Data[i].SOKUTEI_T[2] );
                    } else {
                       pEdt3[i]->Text =  FormatFloat("0",KD71Data[i].SOKUTEI_T[2] );
                    }
                     pEdt4[i]->Text =  IntToStr(3);
               }

                if(  KD71Data[i].SOKUTE_KBN == 1 ){
                  // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ
                   IsEnabledEdt( pEdt1[i], 1 );
                   IsEnabledEdt( pEdt2[i], 1 );
                   IsEnabledPnl( pPnlN[i], 1 );

                   // 計測個数＞２の場合
                  if( KD71Data[i].SOKUTEI_NM > 2 )
                  {
                    //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
                    IsEnabledEdt( pEdt3[i], 1 );
                    IsEnabledEdt( pEdt4[i], 1 );
                    IsEnabledScrl(pScrl[i], 1 );

                    // ScrollBarの初期値設定
                    pScrl[i]->Min = 3;
                    pScrl[i]->Max = KD71Data[i].SOKUTEI_NM;
                    pScrl[i]->Position = 3 ;

                  }

                  //最初計測レコード
                  if( flag == 0 && HaveSokutei){
                     flag=1;
                     SamplePositionIdx = i+1 ;
                     iFirstPosition = SamplePositionIdx ;
                  }

                  iLastPosition = KD71Data[i].SAMPLE_P ;
             }else{
                   // ﾃﾞｰﾀ１、ﾃﾞｰﾀ２ｺﾝﾄﾛｰﾙ
                /*   IsEnabledEdt( pEdt1[i], 0 );
                   IsEnabledEdt( pEdt2[i], 0 );
                   IsEnabledPnl( pPnlN[i], 0 );

                    //例外ﾃﾞｰﾀｺﾝﾄﾛｰﾙ
                    IsEnabledEdt( pEdt3[i], 0 );
                    IsEnabledEdt( pEdt4[i], 0 );
                    IsEnabledScrl(pScrl[i],0 );
                 */
              }

          }
    }


    //備考をヒントにセット 2002/11/08 E.Takase
    SetMEMO();

    if( HaveSokutei ){

         //画面下のﾎﾞﾀﾝを有効にする
         SetEnabel(1) ;

        //測定明細項目名の設定
        if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
           Rad2->Caption ="　 直  径" ;
           if( iBotai ){
             iKomoku = 3;
             Rad3->Checked = true ;
           }else{
             iKomoku = 2;
             Rad2->Checked = true ;
           }

           if( Rad1->Enabled == true ) Rad1->Enabled = false ;
           if( Rad2->Enabled == false ) Rad2->Enabled = true ;
           if( Rad3->Enabled == false ) Rad3->Enabled = true ;
        //コンミ対応 2002/11/02 E.Takase
        }else if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){
           Rad2->Caption ="　  幅" ;
           if( iBotai){
              iKomoku = 3;
              Rad3->Checked = true ;
           }else{
              iKomoku = 1;
              Rad1->Checked = true ;

           }
           if( Rad1->Enabled == false ) Rad1->Enabled = true ;
           if( Rad2->Enabled==true) Rad2->Enabled = false ;
           if( Rad3->Enabled==false) Rad3->Enabled = true ;
        }else{
           Rad2->Caption ="　  幅" ;
           if( iBotai){
              iKomoku = 3;
              Rad3->Checked = true ;
           }else{
              iKomoku = 1;
              Rad1->Checked = true ;

           }
           if( Rad1->Enabled==false) Rad1->Enabled = true ;
           if( Rad2->Enabled==false) Rad2->Enabled = true ;
           if( Rad3->Enabled==false) Rad3->Enabled = true ;
        }

         //最初計測データを画面へセット
         pEdt1[SamplePositionIdx-1]->SetFocus();

         DisplayInfo();
         ToDrawGraph(SamplePositionIdx, iOption);

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
//F8  CH切り替え
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    //カソールを元に戻す
    CurseBack();

    ExecF8();
}
void ExecF8()
{
   char tempo[64];

    //計測項目の設定
    if ( ShareFlag && ( iKomoku  == 1 || iKomoku  == 2 )) {

            // チャネル番号の設定

            if ( iChNo < 5)
               iChNo++;
            else
               iChNo = 1;

            iChNo_Old=iChNo ;
            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));

            // ステータスメッセージ
            //sprintf(tempo, "チャネル番号： %d", iChNo);
            //StatBarClear(tempo) ;

    }

    // iKomoku = 3.4
    // Connect 9を固定

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
      //カソールを元に戻す
      CurseBack();
      ExecF9();

}
void ExecF9(void)
{
  if( !HaveSokutei ) return ;

  Form4->ShowModal();
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

        Form1->PageCtrl->ActivePage = Form1->TabSheet1;
        //StatBarClear("測定履歴 （音ON, 色ON)");

        // 画面色のリセット
        SetRed(2);


     }else if( iOption == 2 )
     {
        // 工程能力作画
        Form1->PageCtrl->Visible = true ;
        Form1->PageCtrl->ActivePage = Form1->TabSheet2;
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
   bool ret;

   if( !HaveSokutei ) return ;

   //計測したﾃﾞｰﾀを保存する
   ret = ExecF11();
   // 2004/08/30 A.Tamura 保存処理失敗時は、次のトレーへ移行しない。
   if ( ret == false )	return ;

   Save_Click = 1;

   //次のﾄﾚｰNOが有れば、次のﾄﾚｰNOのﾃﾞｰﾀを自動的に画面へセット
   BtnF07Click(Sender);

   //カーソロを「保存」ボタンへセット
   if( BtnF11->Font->Color == clRed )
      BtnF12->SetFocus();
   Save_Click = 0;

}
bool ExecF11(void)
{
    if( !HaveSokutei ) return(true);

    // ステータスメッセージ
    StatBarClear(MSG_04);

    // ﾃﾞｰﾀをﾌｧｲﾙKD71、Kd72へ書き込む
    Kd71_Update01();

    // 2004/08/30 A.Tamura 保存処理のエラー時は、メッセージボックスを表示します。
    if( Update_err == 1 ){
        ShowMessage("データ保存処理時にエラーの可能性がありました。\nDBError.Logファイルを参照して下さい。");
        return(false);
    }

    //入力ﾃﾞｰﾀを更新される場合のフラグのクリア
    AllDataChg = 0;
    CurSampChg = 0;
    CurDataChg = 0;
    Update_err = 0;

    // ステータスメッセージ
    StatBarClear( " ") ;

    return(true);

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
         case VK_F2:
             if( iKomoku == 1 || iKomoku == 2 )
                 ToPreData();
             else
                 ToPreData_AV();
             break;

         case VK_F3:
            if( iKomoku == 1 || iKomoku == 2 )
               ToNextData() ;
            else
               ReturnExec();
               break;
         case VK_F4:  ExecF4();               break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F7:
               //検索部にフォーカスがある場合、検索実行
               BtnF07Click(Sender);
               break;
         case VK_F9: ExecF9();               break;
         case VK_F8: ExecF8();               break;
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
         case VK_F2:
             if( iKomoku == 1 || iKomoku == 2 )
                 ToPreData();
             else
                 ToPreData_AV();
             break;

         case VK_F3:
            if( iKomoku == 1 || iKomoku == 2 )
               ToNextData() ;
            else
               ReturnExec();
               break;
         case VK_F4:  ExecF4();               break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
              //検索部以外にフォーカスがある場合、検索部にフォーカスをセット
              edtymd->SetFocus();

               break;
         case VK_F9: ExecF9();               break;
         case VK_F8: ExecF8();               break;
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
                            !BtnF11->Focused() && !BtnF12->Focused() &&
                            !edtymd->Focused() && !edttlno->Focused()){
                            if( iKomoku == 1 || iKomoku == 2 )
                                ToNextData();
                            else
                                ReturnExec();
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


//------------------------------------------------------------------------------
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

      WriteLog("TKS17.exe起動");

      // 機器番号を読込む
      GetCurrentDirectory(256,DirName);
      sprintf(FileName, "%s\\Tks.ini", DirName);
      GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, FileName);							//Seed値
      KikiType = atoi(tempo);
      if ( KikiType <= 0 || KikiType > 4)
          ret_232 = -1;
         // StatBarClear(MSG_00) ;

      ShareFlag = 0;
      if (iRS232C) {
         if (KikiType == 1 || KikiType == 2) {
            ShareFlag = 1;
            iChNo = 2;
            iChNo_Old = 2 ;
         }
         if (KikiType == 3 || KikiType == 4) {
            ShareFlag = 1;
            iChNo = 9;
          }
      }

      // 工場区分を読み込む
      GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, FileName);
      iKojoKbn = atoi(tempo);

     // シェアメモリ作成
     if (ShareFlag) {

        ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS1", 1);
        ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS2", 2);

        if (ret_232 < 0) {
           ShareFlag = 0;
        }

        //RS232C接続フラグを１に設定
        iShareFlag = 1;

       sprintf(tempo, "CONNECT %d", iChNo);
       SharedMemory_Write(1, 0, tempo, strlen(tempo));
     }


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

      //測定ｻﾝﾌﾟﾙ情報の表示
      InitPnl(Pnl5, "0") ;
      InitPnl(Pnl6, "0") ;
      InitPnl(Pnl7, " ") ;
      InitPnl(Pnl8, " ") ;
      InitPnl(Pnl9, " ") ;
      InitPnl(Pnl10, " ") ;
      InitPnl(Pnl11, " ") ;
      InitPnl(Pnl12, " ") ;

      //ScrollBarの初期値の設定
      for( i=0; i<30; i++ )
      {
        pScrl[i]->Min = 0;
        pScrl[i]->Max = 99;
        pScrl[i]->Position =0;
      }

      //工程能力ｺﾝﾄﾛｰﾙのクリア
      InitPnl(Pnl21, "0") ;
      InitPnl(Pnl22, "0") ;
      InitPnl(Pnl23, "0.000") ;
      InitPnl(Pnl24, "0") ;

      InitPnl(Pnl31, "0.00000") ;
      InitPnl(Pnl32, "0.00000") ;
      InitPnl(Pnl33, "0.00") ;

      InitPnl(Pnl41, "0.00") ;
      InitPnl(Pnl42, "0.000") ;
      InitPnl(Pnl43, "0.000") ;

      //測定明細
      for( i=0; i<2; i++ ){
          InitEdt(pEdt1_S[i], "0.000");
          InitEdt(pEdt2_S[i], "0.000");
          InitEdt(pEdt3_S[i], "0.000");
          InitEdt(pEdt1_V[i], "0.00");
          InitEdt(pEdt1_A[i], "0.00");
          InitEdt(pEdt2_V[i], "0.00");
          InitEdt(pEdt2_A[i], "0.00");
          InitEdt(pEdt3_V[i], "0.00");
          InitEdt(pEdt3_A[i], "0.00");
      }

      for( i=0; i<4; i++ ){
          InitEdt(pEdt4_S[i], "0");
          InitPnl(pPnl_S[i], "0") ;
          pScrl_S[i]->Min = 0;
          pScrl_S[i]->Max = 99;
          pScrl_S[i]->Position =0;
      }

      InitPnl(PnlSpan1, "0") ;
      InitPnl(PnlSpan2, "0") ;
      InitPnl(PnlSpan3, "0") ;

      //計測条件
      InitPnl(Pnl13, "0") ;
      InitPnl(PnlD, "0") ;

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
  int i;

  if( flag == 0 ){

      //画面を開く時に、入力ｺﾝﾄﾛｰﾙを無効にする
      for( i=0; i<30; i++ )
      {
       IsEnabledEdt( pEdt1[i], 0 );
       IsEnabledEdt( pEdt2[i], 0 );
       IsEnabledEdt( pEdt3[i], 0 );
       IsEnabledEdt( pEdt4[i], 0 );
       IsEnabledPnl( pPnlP[i], 0 );
       IsEnabledPnl( pPnlN[i], 0 );
       IsEnabledScrl( pScrl[i],0 );
       }

       //計測明細ｺﾝﾄﾛｰﾙ
      for( i=0; i<2; i++ ){
          IsEnabledEdt(pEdt1_S[i], 0);
          IsEnabledEdt(pEdt2_S[i], 0);
          IsEnabledEdt(pEdt3_S[i], 0);
          IsEnabledEdt(pEdt1_V[i], 0);
          IsEnabledEdt(pEdt1_A[i], 0);
          IsEnabledEdt(pEdt2_V[i], 0);
          IsEnabledEdt(pEdt2_A[i], 0);
          IsEnabledEdt(pEdt3_V[i], 0);
          IsEnabledEdt(pEdt3_A[i], 0);
      }

       for( i=0; i<4; i++ ){
            IsEnabledEdt( pEdt4_S[i], 0 );
            IsEnabledPnl( pPnl_S[i], 0 );
            IsEnabledScrl( pScrl_S[i],0 );
       }

       Rad1->Enabled = false ;
       Rad2->Enabled = false ;
       Rad3->Enabled = false ;

       //計測条件
       IsEnabledPnl( Pnl13, 0 );
       IsEnabledPnl( PnlD, 0 );

       //前項、次項、印刷ﾎﾞﾀﾝなどを無効にする
       BtnF02->Enabled = false ;
       BtnF03->Enabled = false ;
       BtnF04->Enabled = false ;
       //BtnF06->Enabled = false ;
       if( !ShareFlag || KikiType == 3 || KikiType == 4 ){ // PC1, PC1
           BtnF08->Enabled = false ;
       }
       BtnF09->Enabled = false ;
       BtnF10->Enabled = false ;
       BtnF11->Enabled = false ;
  }else if( flag == 1 ){

         //前項、次項、印刷ﾎﾞﾀﾝなどを有効にする
         if( BtnF02->Enabled==false)  BtnF02->Enabled = true ;
         if( BtnF03->Enabled==false)  BtnF03->Enabled = true ;
         if( BtnF04->Enabled==false)  BtnF04->Enabled = true ;
         //if( BtnF06->Enabled==false)  BtnF06->Enabled = true ;
         if ( KikiType == 1 || KikiType == 2 ){ // PC1, PC2
             if (ShareFlag){
                if( BtnF08->Enabled==false) BtnF08->Enabled = true;
              }
         }else{ // PC3, PC4
            BtnF08->Enabled = false;
         }

         if( BtnF09->Enabled==false) BtnF09->Enabled = true ;
         if( BtnF10->Enabled==false) BtnF10->Enabled = true ;
         if( BtnF11->Enabled==false) BtnF11->Enabled = true ;
  }else{
         //前項、次項、印刷ﾎﾞﾀﾝなどを無効にする
         if( BtnF02->Enabled==true) BtnF02->Enabled = false ;
         if( BtnF03->Enabled==true) BtnF03->Enabled = false ;
         if( BtnF04->Enabled==true) BtnF04->Enabled = false ;
         //if( BtnF06->Enabled==true) BtnF06->Enabled = false ;
         if( !ShareFlag || KikiType == 3 || KikiType == 4){ // PC3, PC4
            if( BtnF08->Enabled==true)
                   BtnF08->Enabled = false ;
         }
         if( BtnF09->Enabled==true) BtnF09->Enabled = false ;
         if( BtnF10->Enabled==true) BtnF10->Enabled = false ;
         if( BtnF11->Enabled==true) BtnF11->Enabled = false ;
  }

}

//---------------------------------------------------------------------------
void __fastcall TForm1:: OnEditEnter( int spflag, int dtflag, TNumberEdit *pEdit )
{

    int pos, i;

    // spflag :  ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
    // dtflag :  一つｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOに対してのﾃﾞｰﾀNO

    if( CurBackFlg ) return ;

     //計測データ部指示フラグ
    CurField = 2;

    //一覧検索ﾎﾞﾀﾝを無効にする
    BtnF01->Enabled = false ;

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

       //SamplePositionIdx_old = SamplePositionIdx;

       //カレントサンプルポジションデータを履歴ファイルへ更新
       if( CurSampChg){
          AddKd73W();
          CurSampChg = 0;
       }

       SamplePositionIdx = spflag ;

        //測定明細項目名の設定
        if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
           Rad2->Caption ="　 直  径" ;
           if( iKomoku == 1 ) {
              Rad2->Checked = true ;
              iKomoku = 2 ;
           }
           if( Rad1->Enabled == true ) Rad1->Enabled = false ;
           if( Rad2->Enabled == false ) Rad2->Enabled = true ;
           if( Rad3->Enabled == false ) Rad3->Enabled = true ;
        //コンミの場合 2002/11/02 E.Takase
        }else if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){
           Rad2->Caption ="　  幅" ;
           if( iKomoku == 2 ) {
              Rad3->Checked = true ;
              iKomoku = 3 ;
           }
           if( Rad1->Enabled == false ) Rad1->Enabled = true ;
           if( Rad2->Enabled==true) Rad2->Enabled = false ;
           if( Rad3->Enabled==false) Rad3->Enabled = true ;
        }else{
           Rad2->Caption ="　  幅" ;
           if( Rad1->Enabled==false) Rad1->Enabled = true ;
           if( Rad2->Enabled==false) Rad2->Enabled = true ;
           if( Rad3->Enabled==false) Rad3->Enabled = true ;
        }

       // 表示する電流値の規格チェック
       DenryuCheck();

       //サンプル情報の表示
       DisplayInfo();

       //履歴図と工程能力の作画
       ToDrawGraph(SamplePositionIdx, iOption);
    }

     // 計測値１,計測値２の有効か無効かの設定
     for( i=0; i<2; i++ ){
      if( i==iKomoku-1){
          IsEnabledEdt( pEdt1_S[i], 1 );
          IsEnabledEdt( pEdt2_S[i], 1 );
      }else{
          IsEnabledEdt( pEdt1_S[i], 0 );
          IsEnabledEdt( pEdt2_S[i], 0 );
      }
     }

     if( iKomoku == 3 || iKomoku == 4 ){
          IsEnabledEdt( pEdt1_V[0], 1 );
          IsEnabledEdt( pEdt1_A[0], 1 );
          IsEnabledEdt( pEdt2_V[0], 1 );
          IsEnabledEdt( pEdt2_A[0], 1 );
          IsEnabledEdt( pEdt1_V[1], 1 );
          IsEnabledEdt( pEdt1_A[1], 1 );
          IsEnabledEdt( pEdt2_V[1], 1 );
          IsEnabledEdt( pEdt2_A[1], 1 );
     }else{
          IsEnabledEdt( pEdt1_V[0], 0 );
          IsEnabledEdt( pEdt1_A[0], 0 );
          IsEnabledEdt( pEdt2_V[0], 0 );
          IsEnabledEdt( pEdt2_A[0], 0 );
          IsEnabledEdt( pEdt1_V[1], 0 );
          IsEnabledEdt( pEdt1_A[1], 0 );
          IsEnabledEdt( pEdt2_V[1], 0 );
          IsEnabledEdt( pEdt2_A[1], 0 );
     }

    //測定個数＞２の場合
    if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM  > 2 ){

            PnlSpan3->Visible = true ;

            //3個目以降のデータNO
            pos = pEdt4[SamplePositionIdx-1]->Value ;

            //ScrollBarの初期化
            for(  i=0; i<4; i++){
              if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 && i== 0  ) continue;

             pScrl_S[i]->Min = 0;
             pScrl_S[i]->Max = 99;

             //固有抵抗率に合わせて項目明細のScrollBarを設定する
             pScrl_S[i]->Min = 3;
             pScrl_S[i]->Max = KD71Data[SamplePositionIdx-1].SOKUTEI_NM;
             pScrl_S[i]->Position = pos ;
            }

            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[pos-1] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[pos-1] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[pos-1] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[pos-1] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[pos-1] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[pos-1] );

             PnlSpan3->Caption  = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_P[pos-1] );

             for( i=0; i<4; i++ ){
                if(  KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 && i== 0 ){
                     pEdt4_S[i]->Text = "0" ;
                     pPnl_S[i]->Caption = "0" ;
                }else {
                    pEdt4_S[i]->Text = IntToStr(pos) ;

                    //測定個数の設定
                    pPnl_S[i]->Caption = IntToStr( KD71Data[SamplePositionIdx-1].SOKUTEI_NM );
                }
             }

            //３個目以降の計測データｺﾝﾄﾛｰﾙを有効にする
            for( i=0; i< 2; i++ ){
               if( i== iKomoku-1 ){
                    IsEnabledEdt( pEdt3_S[i], 1 );
                    IsEnabledEdt( pEdt4_S[i], 1 );
                    IsEnabledPnl( pPnl_S[i], 1 );
                    pScrl_S[i]->Enabled = true ;

                }else{
                    IsEnabledEdt( pEdt3_S[i], 0 );
                    IsEnabledEdt( pEdt4_S[i], 0 );
                    IsEnabledPnl( pPnl_S[i], 0 );
                    pScrl_S[i]->Enabled = false ;
                }
            }

            if( iKomoku == 3 || iKomoku == 4 ){
                    IsEnabledEdt( pEdt3_V[0], 1 );
                    IsEnabledEdt( pEdt3_A[0], 1 );
                    IsEnabledEdt( pEdt4_S[2], 1 );
                    IsEnabledPnl( pPnl_S[2], 1 );
                    pScrl_S[2]->Enabled = true ;
                    IsEnabledEdt( pEdt3_V[1], 1 );
                    IsEnabledEdt( pEdt3_A[1], 1 );
                    IsEnabledEdt( pEdt4_S[3], 1 );
                    IsEnabledPnl( pPnl_S[3], 1 );
                    pScrl_S[3]->Enabled = true ;
            }else{
                    IsEnabledEdt( pEdt3_V[0], 0 );
                    IsEnabledEdt( pEdt3_A[0], 0 );
                    IsEnabledEdt( pEdt4_S[2], 0 );
                    IsEnabledPnl( pPnl_S[2], 0 );
                    pScrl_S[2]->Enabled = false ;
                    IsEnabledEdt( pEdt3_V[1], 0 );
                    IsEnabledEdt( pEdt3_A[1], 0 );
                    IsEnabledEdt( pEdt4_S[3], 0 );
                    IsEnabledPnl( pPnl_S[3], 0 );
                    pScrl_S[3]->Enabled = false ;
            }

     }else{

             //３個目以降の計測データｺﾝﾄﾛｰﾙを無効にする
             for(int i=0; i<4; i++){
                 pScrl_S[i]->Enabled = false ;
                 IsEnabledEdt( pEdt4_S[i], 0 );
                 IsEnabledPnl( pPnl_S[i], 0 );
            }

            for(int i=0; i<2; i++)
                 IsEnabledEdt( pEdt3_S[i], 0 );

            for( i=2; i<4; i++ )
            {
                 IsEnabledEdt( pEdt3_V[i-2], 0 );
                 IsEnabledEdt( pEdt3_A[i-2], 0 );
            }

             for(int i=0; i<4; i++){

                 pEdt3_S[i]->Text = "0.0" ;
                 pEdt4_S[i]->Text = "0" ;
                 if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                     pPnl_S[i]->Caption = IntToStr( KD71Data[SamplePositionIdx-1].SOKUTEI_NM ) ;
            }

            PnlSpan3->Visible = false ;

     }

    // 測定データ明細の表示
    if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
       pEdt1_S[0]->Text =  FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[0] );
       pEdt2_S[0]->Text =  FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[1] );
     }else
     {
       pEdt1_S[0]->Text =  "0.000";
       pEdt2_S[0]->Text =  "0.000";
     }
     pEdt1_S[1]->Text =  FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[0] );
     pEdt2_S[1]->Text =  FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[1] );

     pEdt1_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[0] );
     pEdt1_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[0] );
     pEdt2_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[1] );
     pEdt2_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[1] );

     pEdt1_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[0] );
     pEdt1_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[0] );
     pEdt2_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[1] );
     pEdt2_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[1] );

     PnlSpan1->Caption  =  FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_P[0] );
     PnlSpan2->Caption  =  FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_P[1] );

     
    //ｶｰｿﾙを測定データ明細へ移動
    if( DataNoIdx == 1 ){
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt1_S[iKomoku-1]->SetFocus();
          pEdt1_S[iKomoku-1]->SelectAll();
       }else{
          if( FlagAV == 1  || FlagAV == 0){
            pEdt1_V[iKomoku-3]->SetFocus();
            pEdt1_V[iKomoku-3]->SelectAll();
          }else{
            pEdt1_A[iKomoku-3]->SetFocus();
            pEdt1_A[iKomoku-3]->SelectAll();
          }
       }
    }else if( DataNoIdx == 2 ){
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt2_S[iKomoku-1]->SetFocus();
          pEdt2_S[iKomoku-1]->SelectAll();
       }else{
          if( FlagAV == 1  || FlagAV == 0){
            pEdt2_V[iKomoku-3]->SetFocus();
            pEdt2_V[iKomoku-3]->SelectAll();
          }else{
            pEdt2_A[iKomoku-3]->SetFocus();
            pEdt2_A[iKomoku-3]->SelectAll();
          }
       }
    }else {
       if(  iKomoku == 1 || iKomoku == 2 ){
          pEdt3_S[iKomoku-1]->SetFocus();
          pEdt3_S[iKomoku-1]->SelectAll();
       }else{
          if(FlagAV == 1  || FlagAV == 0 ){
            pEdt3_V[iKomoku-3]->SetFocus();
            pEdt3_V[iKomoku-3]->SelectAll();
          }else{
            pEdt3_A[iKomoku-3]->SetFocus();
            pEdt3_A[iKomoku-3]->SelectAll();
          }
       }
    }

    CurDataChg = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::edttlnoEnter(TObject *Sender)
{
      if( CurBackFlg ) return ;

       //検索条件部
      CurField = 1;
      BtnF01->Enabled = true ;

      FlagAV = 1;

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

/*
   //計測作業始まる前 、つまり「検索」ﾎﾞﾀﾝを押す前
   if( ! iKskStart )  return ;

   // マウスでScrollBarを変更する以外の場合
   if( iSaveFlag ) return ;

   // マウスでScrollBarを変更する場合
   if( SamplePositionIdx > 0 &&
       ( SamplePositionIdx >= iFirstPosition && SamplePositionIdx <= iLastPosition ) &&
         DataNoIdx > 2   ){

          if( SaveRegaiDt()< 0) return ;
          CheckInKikaku(1);
          ToDrawGraph(SamplePositionIdx, iOption);

          int pos = pScrl[SamplePositionIdx-1]->Position ;

          pEdt4[SamplePositionIdx-1]->Text = IntToStr(pos);

          // ﾃﾞｰﾀ更新
          pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",
                                      KD71Data[SamplePositionIdx-1].SOKUTEI_T[pos-1] );


          pEdt3[SamplePositionIdx-1]->SetFocus();

          // 更新したデータをチェックする
          CheckInKikaku(0);

      }
*/

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBarVChange(TObject *Sender)
{

   //計測作業始まる前 、つまり「検索」ﾎﾞﾀﾝを押す前
   if( ! iKskStart )  return ;

      // マウスでScrollBarを変更する以外の場合
   if( iSaveFlag ) return ;

   // マウスでScrollBarを変更する場合
   if( SamplePositionIdx >0 &&
       ( SamplePositionIdx >= iFirstPosition && SamplePositionIdx <= iLastPosition ) &&
         DataNoIdx > 2   ){

          if(SaveRegaiDt()<0) return ;

           CheckInKikaku(1);
           CheckInKikaku_1(1);
           CheckInKikaku_2(1);

          ToDrawGraph(SamplePositionIdx, iOption);

          int pos = pScrl_S[iKomoku-1]->Position ;

          pEdt4[SamplePositionIdx-1]->Text = IntToStr(pos);

          // ﾃﾞｰﾀ更新
          pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",
                                      KD71Data[SamplePositionIdx-1].SOKUTEI_T[pos-1] );

          pEdt3[SamplePositionIdx-1]->SetFocus();

          // 更新したデータをチェックする
          CheckInKikaku(0);
          CheckInKikaku_3();
          CheckInKikaku_4();   //2002/12/02 E.Takase
  }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Edt01_1Change(TObject *Sender)
{
 /*   if( iKskStart ) {

    // TNumberEdit *Edt = (TNumberEdit *)Sender;

     //画面に表示しているﾃﾞｰﾀ値を更新される場合
      AllDataChg = 1;
      CurSampChg = 1;
      CurDataChg = 1;

      // 計測したデータCount
      if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR < DataNoIdx ){
           KD71Data[SamplePositionIdx-1].SOKUTEI_NT_CUR = DataNoIdx ;
      }
   }
   */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_1Exit(TObject *Sender)
{
    if( CurBackFlg ) return ;

    // 計測値のチェック
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

     //  CurDataChg = 0;
      if( DataNoIdx == 1 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEI_S[0]- pEdt1_S[0]->Value ) > 0.000001 ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < DataNoIdx ){
                 KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = DataNoIdx ;
             }

             //測定値１
             KD71Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[0]->Value;

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 1 );

             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             } else {
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             }
         }
      }else if( DataNoIdx == 2 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEI_S[1]- pEdt2_S[0]->Value) > 0.000001 ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < DataNoIdx ){
                 KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = DataNoIdx ;
             }

            //測定値２
            KD71Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[0]->Value;

            //固有抵抗率の計算
            KTeikouCal(SamplePositionIdx, 2 ) ;
            //2003.02.05 E.Takase
            if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
               pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
            } else {
               pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
            }
        }
      }else{

           int n=pEdt4_S[0]->Value ;

           if( fabs( pEdt3_S[0]->Value - KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1]) > 0.0000001  ){

                //画面に表示しているﾃﾞｰﾀ値を更新される場合
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // 計測したデータ数をｶﾝトー
               if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < n )
                    KD71Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = n ;

                KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[0]->Value;

                //固有抵抗率の計算
                KTeikouCal(SamplePositionIdx, n ) ;
                //2003.02.05 E.Takase
                if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                } else {
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                }
            }
      }

      //抵抗値規格のチェック
      CheckInKikaku(1);

      if( CurDataChg ) ToDrawGraph(SamplePositionIdx, iOption);
   }

   CurDataChg = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_2Exit(TObject *Sender)
{
    if( CurBackFlg ) return ;

    // 計測値のチェック
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

     //  CurDataChg = 0;
      if( DataNoIdx == 1 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEI_H[0]- pEdt1_S[1]->Value ) > 0.000001 ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < DataNoIdx ){
                 KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = DataNoIdx ;
             }

             //測定値１
             KD71Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[1]->Value;

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 1 ) ;
             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             } else {
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             }
         }
      }else if( DataNoIdx == 2 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEI_H[1]- pEdt2_S[1]->Value) > 0.000001 ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < DataNoIdx ){
                 KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = DataNoIdx ;
             }

            //測定値２
            KD71Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[1]->Value;

            //固有抵抗率の計算
            KTeikouCal(SamplePositionIdx, 2 ) ;
            //2003.02.05 E.Takase
            if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
               pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
            } else {
               pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
            }
        }
      }else{

           int n=pEdt4_S[2]->Value ;
           if( fabs(pEdt3_S[1]->Value - KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1]) > 0.0000001 ){

                //画面に表示しているﾃﾞｰﾀ値を更新される場合
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // 計測したデータ数をｶﾝトー
               if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < n )
                    KD71Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = n ;

                KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[1]->Value;

                //固有抵抗率の計算
                KTeikouCal(SamplePositionIdx, n ) ;
                //2003.02.05 E.Takase
                if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                } else {
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                }
            }
      }

      //抵抗率規格のチェック
      CheckInKikaku(1);

      if( CurDataChg ) ToDrawGraph(SamplePositionIdx, iOption);
   }

   CurDataChg = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtVL_1Exit(TObject *Sender)
{
    if( CurBackFlg ) return ;

     // 計測値のチェック
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

        if( DataNoIdx == 1 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_L[0]- pEdt1_V[0]->Value ) > 0.0000001 ||
             fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_L[0]- pEdt1_A[0]->Value ) > 0.0000001 ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_L[0]- pEdt1_V[0]->Value ) > 0.0000001  ){
                  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR < DataNoIdx )
                       KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR = DataNoIdx ;

                   KD71Data[SamplePositionIdx-1].SOKUTEV_L[0] = pEdt1_V[0]->Value;
             }
             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_L[0]- pEdt1_A[0]->Value ) > 0.0000001 ){
                  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR < DataNoIdx )
                       KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR = DataNoIdx ;

                  KD71Data[SamplePositionIdx-1].SOKUTEA_L[0] = pEdt1_A[0]->Value;
             }

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 1 ) ;
             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             } else {
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             }
         }
      }else if( DataNoIdx == 2 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_L[1]- pEdt2_V[0]->Value ) > 0.0000001 ||
             fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_L[1]- pEdt2_A[0]->Value ) > 0.0000001   ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_L[1]- pEdt2_V[0]->Value ) > 0.0000001 ){
                 if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR < DataNoIdx )
                      KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR = DataNoIdx ;

                 KD71Data[SamplePositionIdx-1].SOKUTEV_L[1] = pEdt2_V[0]->Value;
             }

             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_L[1]- pEdt2_A[0]->Value ) > 0.0000001){
                if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR < DataNoIdx )
                     KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR = DataNoIdx ;

                 KD71Data[SamplePositionIdx-1].SOKUTEA_L[1] = pEdt2_A[0]->Value;
             }

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 2 ) ;
             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
             } else {
                pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
             }
        }
      }else{

          if( CheckDtNo() < 0)  return ;

          int n=pEdt4_S[2]->Value ;

          if( fabs(pEdt3_V[0]->Value -KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1]) > 0.000001  ||
              fabs(pEdt3_A[0]->Value - KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1]) > 0.000001){

                //画面に表示しているﾃﾞｰﾀ値を更新される場合
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

                // 計測したデータ数をｶﾝトー
                if( fabs(pEdt3_V[0]->Value -KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1]) > 0.000001 ) {
                    if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR < n )
                         KD71Data[SamplePositionIdx-1].SOKUTEI_NVL_CUR = n ;

                    KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] = pEdt3_V[0]->Value;
                }

                if( fabs(pEdt3_A[0]->Value - KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1]) > 0.000001) {
                   if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR < n  )
                        KD71Data[SamplePositionIdx-1].SOKUTEI_NAL_CUR = n ;
                    KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] = pEdt3_A[0]->Value;
               }

               //固有抵抗率の計算
                KTeikouCal(SamplePositionIdx, n ) ;
                //2003.02.05 E.Takase
                if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                } else {
                   pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
                }
            }

      }

      //抵抗値規格のチェック
      CheckInKikaku(1);
      CheckInKikaku_1(1);
      CheckInKikaku_2(1);

      if( CurDataChg)  ToDrawGraph(SamplePositionIdx, iOption);

   }

   CurDataChg = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EdtVR_1Exit(TObject *Sender)
{
    if( CurBackFlg ) return ;

     // 計測値のチェック
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

      if( DataNoIdx == 1 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_R[0]- pEdt1_V[1]->Value ) > 0.0000001 ||
             fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_R[0]- pEdt1_A[1]->Value ) > 0.0000001   ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_R[0]- pEdt1_V[1]->Value ) > 0.0000001){
                if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR < DataNoIdx )
                     KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR = DataNoIdx ;

                 KD71Data[SamplePositionIdx-1].SOKUTEV_R[0] = pEdt1_V[1]->Value;
             }

             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_R[0]- pEdt1_A[1]->Value ) > 0.0000001 ){
               if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR < DataNoIdx )
                    KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR = DataNoIdx ;
                KD71Data[SamplePositionIdx-1].SOKUTEA_R[0] = pEdt1_A[1]->Value;
            }

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 1 ) ;
             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             } else {
                pEdt1[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[0] );
             }
         }
      }else if( DataNoIdx == 2 ){

         if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_R[1]- pEdt2_V[1]->Value ) > 0.0000001 ||
             fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_R[1]- pEdt2_A[1]->Value ) > 0.0000001   ){

             //画面に表示しているデータ値を更新される場合
             AllDataChg = 1;
             CurSampChg = 1;
             CurDataChg = 1;

             // 計測したデータCount
             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEV_R[1]- pEdt2_V[1]->Value ) > 0.0000001 ){
                if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR < DataNoIdx )
                     KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR = DataNoIdx ;
                KD71Data[SamplePositionIdx-1].SOKUTEV_R[1] = pEdt2_V[1]->Value;
             }

             if( fabs(KD71Data[SamplePositionIdx-1].SOKUTEA_R[1]- pEdt2_A[1]->Value ) > 0.0000001){
                if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR < DataNoIdx )
                     KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR = DataNoIdx ;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_R[1] = pEdt2_A[1]->Value;
             }

             //固有抵抗率の計算
             KTeikouCal(SamplePositionIdx, 2 ) ;
             //2003.02.05 E.Takase
             if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
             } else {
                pEdt2[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[1] );
             }
        }
      }else{

          if( CheckDtNo() < 0)  return ;

          int n=pEdt4_S[3]->Value ;
          if( fabs(pEdt3_V[1]->Value - KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1]) > 0.000001 ||
                fabs(pEdt3_A[1]->Value - KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1]) > 0.000001 ){

                //画面に表示しているﾃﾞｰﾀ値を更新される場合
                AllDataChg = 1;
                CurSampChg = 1;
                CurDataChg = 1;

               // 計測したデータ数をｶﾝトー
               if( fabs(pEdt3_V[1]->Value - KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1]) > 0.000001){
                  if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR < n )
                       KD71Data[SamplePositionIdx-1].SOKUTEI_NVR_CUR = n ;
                   KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] = pEdt3_V[1]->Value;
               }

               if( fabs(pEdt3_A[1]->Value - KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1]) > 0.000001) {
                 if ( KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR < n )
                      KD71Data[SamplePositionIdx-1].SOKUTEI_NAR_CUR = n ;
                 KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] = pEdt3_A[1]->Value;
               }

               //固有抵抗率の計算
               KTeikouCal(SamplePositionIdx, n ) ;
               //2003.02.05 E.Takase
               if ( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ) { //コンミ
                  pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0.00",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
               } else {
                  pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
               }
            }
      }

      //抵抗値規格のチェック
      CheckInKikaku(1);
      CheckInKikaku_1(1);
      CheckInKikaku_2(1);

      if( CurDataChg) ToDrawGraph(SamplePositionIdx, iOption);
   }

   CurDataChg = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtymdChange(TObject *Sender)
{
     // ステータスメッセージ
     StatBarClear( "  ");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edt01_4Exit(TObject *Sender)
{
     // 入力したﾃﾞｰﾀNO ３〜９９を超えているかどうかのチェック
   if( iKskStart ){
        CheckDtNo() ;
        CurDataChg = 0;
   }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::PageCtrlChange(TObject *Sender)
{
       if( !HaveSokutei ) return ;

       // ステータスメッセージ
       StatBarClear( "  ");

        //測定履歴作画
       if( Form1->PageCtrl->ActivePage == TabSheet1)
          iOption = 1 ;
       if( Form1->PageCtrl->ActivePage == TabSheet2)
          iOption = 2;

       ToDrawGraph(SamplePositionIdx, iOption);

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
               Kd71_Update01();

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

      if (ShareFlag) {
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


void __fastcall TForm1::EdtVL_1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;
    iKomoku = 3;

    FlagAV= 1;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_V[0]->Focused() ) DataNoIdx = 1;
    if( pEdt2_V[0]->Focused() ) DataNoIdx = 2;
    if( pEdt3_V[0]->Focused() ||
        pEdt4_S[2]->Focused() ||
        pScrl_S[2]->Focused() ) DataNoIdx = pEdt4_S[2]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtAL_1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;
    iKomoku = 3 ;

    FlagAV = 2;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_A[0]->Focused() ) DataNoIdx = 1;
    if( pEdt2_A[0]->Focused() ) DataNoIdx = 2;
    if( pEdt3_A[0]->Focused() ||
        pEdt4_S[2]->Focused() ||
        pScrl_S[2]->Focused() ) DataNoIdx = pEdt4_S[2]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtVR_1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;
    FlagAV= 1;

    iKomoku = 4;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_V[1]->Focused() ) DataNoIdx = 1;
    if( pEdt2_V[1]->Focused() ) DataNoIdx = 2;
    if( pEdt3_V[1]->Focused() ||
        pEdt4_S[3]->Focused() ||
        pScrl_S[3]->Focused() ) DataNoIdx = pEdt4_S[3]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtAR_1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    FlagAV = 2 ;
    iKomoku = 4;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_A[1]->Focused() ) DataNoIdx = 1;
    if( pEdt2_A[1]->Focused() ) DataNoIdx = 2;
    if( pEdt3_A[1]->Focused() ||
        pEdt4_S[3]->Focused() ||
        pScrl_S[3]->Focused() ) DataNoIdx = pEdt4_S[3]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;
    FlagAV =0;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_S[0]->Focused() ) DataNoIdx = 1;
    if( pEdt2_S[0]->Focused() ) DataNoIdx = 2;
    if( pEdt3_S[0]->Focused() ||
        pEdt4_S[0]->Focused() ||
        pScrl_S[0]->Focused() ) DataNoIdx = pEdt4_S[0]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_2Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;
    FlagAV=0;
    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // ﾃﾞｰﾀNOの設定
    if( pEdt1_S[1]->Focused() ) DataNoIdx = 1;
    if( pEdt2_S[1]->Focused() ) DataNoIdx = 2;
    if( pEdt3_S[1]->Focused() ||
        pEdt4_S[1]->Focused() ||
        pScrl_S[1]->Focused() ) DataNoIdx = pEdt4_S[1]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }
}


//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_1Change(TObject *Sender)
{
   int n;
   if( iKskStart ) {

         n = pEdt4_S[0]->Value;

         if( n >= 3 && n <= KD71Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[0]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            // 抗折力
            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;


            //測定明細
            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
              }else{
                     pScrl_S[0]->Position = n ;
              }

              pScrl_S[1]->Position = n ;
              pEdt4_S[1]->Text = IntToStr(n) ;

              pScrl_S[2]->Position = n ;
              pEdt4_S[2]->Text = IntToStr(n) ;

              pScrl_S[3]->Position = n ;
              pEdt4_S[3]->Text = IntToStr(n) ;

              DataNoIdx = n;

              iSaveFlag = 0;

         }

   }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_2Change(TObject *Sender)
{
   int n;
   if( iKskStart ) {

         n = pEdt4_S[1]->Value;

         if( n >= 3 && n <= KD71Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[1]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            // 抗折力
            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

            //測定明細
            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }else{
                     pScrl_S[0]->Position = n ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }

              pScrl_S[1]->Position = n ;

              pScrl_S[2]->Position = n ;
              pEdt4_S[2]->Text = IntToStr(n) ;

              pScrl_S[3]->Position = n ;
              pEdt4_S[3]->Text = IntToStr(n) ;

              DataNoIdx = n;

              iSaveFlag = 0;

         }

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_3Change(TObject *Sender)
{
    int n;
   if( iKskStart ) {

         n = pEdt4_S[2]->Value;

         if( n >= 3 && n <= KD71Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[2]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            // 抗折力
            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

            //測定明細
            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }else{
                     pScrl_S[0]->Position = n ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }

              pScrl_S[1]->Position = n ;
              pEdt4_S[1]->Text = IntToStr(n) ;

              pScrl_S[2]->Position = n ;
              //pEdt4_S[2]->Text = IntToStr(n) ;

              pScrl_S[3]->Position = n ;
              pEdt4_S[3]->Text = IntToStr(n) ;

              DataNoIdx = n;

             iSaveFlag = 0;

         }

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_4Change(TObject *Sender)
{
   int n;
   if( iKskStart ) {

         n = pEdt4_S[3]->Value;

         if( n >= 3 && n <= KD71Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[3]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            // 抗折力
            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

            //測定明細
            if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
                pEdt3_S[0]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
            }else{
                pEdt3_S[0]->Text ="0.000";
            }
             pEdt3_S[1]->Text = FormatFloat("#0.000",KD71Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );

             pEdt3_V[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_L[n-1] );
             pEdt3_A[0]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_L[n-1] );
             pEdt3_V[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEV_R[n-1] );
             pEdt3_A[1]->Text =  FormatFloat("#0.00",KD71Data[SamplePositionIdx-1].SOKUTEA_R[n-1] );

             if( KD71Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }else{
                     pScrl_S[0]->Position = n ;
                     pEdt4_S[0]->Text = IntToStr(n) ;
              }

              pScrl_S[1]->Position = n ;
              pEdt4_S[1]->Text = IntToStr(n) ;

              pScrl_S[2]->Position = n ;
              pEdt4_S[2]->Text = IntToStr(n) ;

              pScrl_S[3]->Position = n ;
             // pEdt4_S[3]->Text = IntToStr(n) ;

              DataNoIdx = n;

              iSaveFlag = 0;

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



void __fastcall TForm1::BtnF11Enter(TObject *Sender)
{
  BtnF11->Font->Color = clRed ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF11Exit(TObject *Sender)
{
 BtnF11->Font->Color = clBlack ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Enter(TObject *Sender)
{
 BtnF12->Font->Color = clRed ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Exit(TObject *Sender)
{
  BtnF12->Font->Color = clBlack ;
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
//備考をヒントにセット 2002/11/07 E.Takse
void __fastcall TForm1::SetMEMO(void)
{
    int i;

	for( i=0; i<30; i++ )
    {
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD71Data[i].SAMPLE_P == -1 )
		{
			//pPnlP[i]->ShowHint = false;
			pEdt1[i]->ShowHint = false;
			pEdt2[i]->ShowHint = false;
			pEdt3[i]->ShowHint = false;
			pEdt4[i]->ShowHint = false;
			pScrl[i]->ShowHint = false;
			pPnlN[i]->ShowHint = false;
		} else {
			if ( Trim(KD71Data[i].MEMO) != "" ) {
				//pPnlP[i]->Hint = KD71Data[i].MEMO;
				pEdt1[i]->Hint = KD71Data[i].MEMO;
				pEdt2[i]->Hint = KD71Data[i].MEMO;
				pEdt3[i]->Hint = KD71Data[i].MEMO;
				pEdt4[i]->Hint = KD71Data[i].MEMO;
				pScrl[i]->Hint = KD71Data[i].MEMO;
				pPnlN[i]->Hint = KD71Data[i].MEMO;

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


