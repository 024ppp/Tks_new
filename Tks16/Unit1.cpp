#pragma link "NumberEdit"
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Tks16.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//----------------------------------------------------------------------------
extern AnsiString str;
int USER_COD ;              // 担当者ｺｰﾄﾞ
AnsiString USER_NAM;        // 担当者名
AnsiString BUMO_COD;        // 部門ｺｰﾄﾞ
AnsiString BUMO_NAM;        // 部門名

//---------------------------------------------------------------------------
// KD61構造体変数
structKD61 KD61Data[30];      //硬度データﾌｧｲﾙ  KD61
int Bk_HSC_A_CH[30][100];       //Hsc硬度圧面1
int Bk_HSC_S_CH[30][100];       //Hsc硬度側面1
int Bk_HSC_SK_SU[30];           //Hsc測定個数
double Bk_HSD_A_CH[30][100];    //Hsd硬度圧面
double Bk_HSD_S_CH[30][100];    //Hsd硬度側面
int Bk_HSD_SK_SU[30];           //Hsd測定個数

//KD63W構造体変数
structKD63W KD63WData[30]; //硬度計測履歴ﾃﾞｰﾀﾜｰｸﾌｧｲﾙ  KD63W

//画面操作用変数
int iRec_Kd61 ;             //一覧検索結果件数

//---------------------------------------------------------------------------
// 表示メッセージ
AnsiString MSG_00 = "機器番号（PC1～PC4)を定義して下さい";
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
AnsiString MSG_11 = "RS232C接続エラーが発生しました。" ;
AnsiString MSG_12 = "履歴データ ０ 件。" ;

int iKskStart = 0;          // １: 計測開始  0: 計測できない

int Hsc_DataNoIdx;          // Hsc：一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO
int Hsc_SamplePositionIdx;  // Hsc：ｻﾝﾌﾟﾙポジションNO
int Hsd_DataNoIdx;          // Hsd：一つｻﾝﾌﾟﾙポジションNOに対するﾃﾞｰﾀNO
int Hsd_SamplePositionIdx;  // Hsd：ｻﾝﾌﾟﾙポジションNO

int Hsc_HaveSokutei = 0;    // 測定データあるかどうかフラグ
int Hsd_HaveSokutei = 0;    // 測定データあるかどうかフラグ

int AreaFlag = 0;           // 0: 現在測定データ無し;
                            // 1: 現在Hscを測定している;
                            // 2: 現在Hsdを測定している

int iKojoKbn = 0 ;          // 工場区分

//---------------------------------------------------------------------------
// [Option]ﾎﾞﾀﾝを押す場合使う変数
int Hsc_iOption = 1 ;           // iOption == 1  測定履歴表示（音ON, 色ON)
                                // iOPtion == 2  工程能力表示（音ON, 色ON)
                                // iOption == 3  測定履歴表示（音ON, 色ON)
                                // iOption == 4  工程能力表示（音ON, 色ON)
                                // iOption == 5   表示なし（音OFF, 色OFF)
int Hsd_iOption = 1 ;           // iOption == 1  測定履歴表示（音ON, 色ON)
                                // iOPtion == 2  工程能力表示（音ON, 色ON)
                                // iOption == 3  測定履歴表示（音ON, 色ON)
                                // iOption == 4  工程能力表示（音ON, 色ON)
                                // iOption == 5   表示なし（音OFF, 色OFF)
//---------------------------------------------------------------------------
int Hsc_AllDataChg;             // 画面に表示しているﾃﾞｰﾀ更新されるかどうか
int Hsc_CurSampChg;
int Hsc_CurDataChg;
                                // 更新した場合 =1   更新しない場合 =0
int Hsd_AllDataChg;             // 画面に表示しているﾃﾞｰﾀ更新されるかどうか
int Hsd_CurSampChg;
int Hsd_CurDataChg;
                                // 更新した場合 =1   更新しない場合 =0
//---------------------------------------------------------------------------
int Sample_P_Min, Sample_P_Max;

int WriteDatabaseError = 0;    // データベースへ書込みフラグ
int NextToreiFlag = 1;         // 保存時に次トレイをSearchフラグ
int ScreenInitFlag = 0;        // 画面初期化フラグ

// 表示する履歴ﾃﾞｰﾀの最大個数
int LOTMAX = 10 ;

int EndErrorFlag = 0;

void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void DrawRireki0(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void DrawRireki1(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] ,int, double, double);
void ExecF6(void); //2002/11/07 E.Takase
void Kd63W_Delete01(void);
void KD63WFormat(void);


__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
     //ﾃﾞｰﾀベースとの接続
     Database1->Open() ;

     // 画面に各ｺﾝﾄﾛｰﾙIDを保存する
     //SaveCtlID() ;

     // 画面を開く際の初期値ﾃﾞｰﾀの設定
     SetInit(0) ;

     //計測予定日、ﾄﾚｰNO、一覧検索ﾎﾞﾀﾝ, 検索を除く、無効にする
     //SetEnabel (0);

     // 2003/02/12 A.Tamura
     //Hsc_AllDataChg = 0;
     //Hsd_AllDataChg = 0;

     // 20160630_iniファイル読み込み追加
     Read_Ini();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetInit(int flag)
{
     AnsiString YMD;

      // メイン画面の初期化
      if( flag == 0 ){
         // 計測予定年月日
         YMD = FormatDateTime("yyyymmdd",Date());
         YMD.Insert("/",5);
         YMD.Insert("/",8);
         edtymd->Text = YMD;

         // トレーNO
         edttlno->Text ="1";
      }

      //測定ｻﾝﾌﾟﾙ情報の表示
      InitPnl(Pnl7, " ") ;
      InitPnl(Pnl8, " ") ;
      InitPnl(Pnl9, " ") ;
      InitPnl(Pnl10, " ") ;
      InitPnl(Pnl11, " ") ;
      InitPnl(Pnl12, " ") ;

      // HSC : ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO及び測定個数N
      InitEdt(Edt_Hsc_Sample, "0");
      InitPnl(Pan_Hsc1, "0");
      InitPnl(Pan_Hsc2, "0");
      InitPnl(Pan_Hsc3, "0");
      InitPnl(Pan_Hsc4, "0");
      InitPnl(Pan_Hsc5, "0");
      InitPnl(Pan_Hsc6, "0");
      InitEdt(Edt_Hsc11, "0");
      InitEdt(Edt_Hsc12, "0");
      InitEdt(Edt_Hsc13, "0");
      InitEdt(Edt_Hsc14, "0");
      InitEdt(Edt_Hsc21, "0");
      InitEdt(Edt_Hsc22, "0");
      InitEdt(Edt_Hsc23, "0");
      InitEdt(Edt_Hsc24, "0");

      // HSD : ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO及び測定個数N
      InitEdt(Edt_Hsd_Sample, "0");
      InitPnl(Pan_Hsd1, "0");
      InitPnl(Pan_Hsd2, "0");
      InitPnl(Pan_Hsd3, "0");
      InitPnl(Pan_Hsd4, "0");
      InitPnl(Pan_Hsd5, "0");
      InitPnl(Pan_Hsd6, "0");
      InitEdt(Edt_Hsd11, "0");
      InitEdt(Edt_Hsd12, "0");
      InitEdt(Edt_Hsd13, "0");
      InitEdt(Edt_Hsd14, "0");
      InitEdt(Edt_Hsd21, "0");
      InitEdt(Edt_Hsd22, "0");
      InitEdt(Edt_Hsd23, "0");
      InitEdt(Edt_Hsd24, "0");

      //ＨＳＣ：工程能力ｺﾝﾄﾛｰﾙのクリア
      InitPnl(Pan_Hsc_N1, "0");
      InitPnl(Pan_Hsc_Min1, "0.00") ;
      InitPnl(Pan_Hsc_Max1, "0.00") ;
      InitPnl(Pan_Hsc_Ave1, "0.000") ;

      InitPnl(Pan_Hsc_R1, "0.00000") ;
      InitPnl(Pan_Hsc_Siguma1, "0.00000") ;
      InitPnl(Pan_Hsc_Cp1, "0.00") ;

      InitPnl(Pan_Hsc_Cpk1, "0.00") ;
      InitPnl(Pan_Hsc_K1, "0.000") ;
      InitPnl(Pan_Hsc_P1, "0.000") ;

      InitPnl(Pan_Hsc_N2, "0");
      InitPnl(Pan_Hsc_Min2, "0.00") ;
      InitPnl(Pan_Hsc_Max2, "0.00") ;
      InitPnl(Pan_Hsc_Ave2, "0.000") ;

      InitPnl(Pan_Hsc_R2, "0.00000") ;
      InitPnl(Pan_Hsc_Siguma2, "0.00000") ;
      InitPnl(Pan_Hsc_Cp2, "0.00") ;

      InitPnl(Pan_Hsc_Cpk2, "0.00") ;
      InitPnl(Pan_Hsc_K2, "0.000") ;
      InitPnl(Pan_Hsc_P2, "0.000") ;

      //ＨＳＤ：工程能力ｺﾝﾄﾛｰﾙのクリア
      InitPnl(Pan_Hsd_N1, "0");
      InitPnl(Pan_Hsd_Min1, "0.00") ;
      InitPnl(Pan_Hsd_Max1, "0.00") ;
      InitPnl(Pan_Hsd_Ave1, "0.000") ;

      InitPnl(Pan_Hsd_R1, "0.00000") ;
      InitPnl(Pan_Hsd_Siguma1, "0.00000") ;
      InitPnl(Pan_Hsd_Cp1, "0.00") ;

      InitPnl(Pan_Hsd_Cpk1, "0.00") ;
      InitPnl(Pan_Hsd_K1, "0.000") ;
      InitPnl(Pan_Hsd_P1, "0.000") ;

      InitPnl(Pan_Hsd_N2, "0");
      InitPnl(Pan_Hsd_Min2, "0.00") ;
      InitPnl(Pan_Hsd_Max2, "0.00") ;
      InitPnl(Pan_Hsd_Ave2, "0.000") ;

      InitPnl(Pan_Hsd_R2, "0.00000") ;
      InitPnl(Pan_Hsd_Siguma2, "0.00000") ;
      InitPnl(Pan_Hsd_Cp2, "0.00") ;

      InitPnl(Pan_Hsd_Cpk2, "0.00") ;
      InitPnl(Pan_Hsd_K2, "0.000") ;
      InitPnl(Pan_Hsd_P2, "0.000") ;

      // HsD 初期状態設定
      Unenable(1);
      Unenable(2);

      // Button 初期状態設定
      Button1->Enabled = true;
      Button2->Enabled = false;
      Button3->Enabled = false;
      Button4->Enabled = false;
      Button5->Enabled = true;
      Button7->Enabled = true;
      Button10->Enabled = false;
      Button11->Enabled = false;
      Button12->Enabled = true;

      Pan_Hsc->Color = clBtnFace;
      Pan_Hsd->Color = clBtnFace;

      // 2003/02/12 A.Tamura
      //Hsc_AllDataChg = 0;
      //Hsd_AllDataChg = 0;
}

void __fastcall TForm1::InitEdt(TNumberEdit *P_Edit, AnsiString Str)
{
       P_Edit->Text = Str ;
}
//--------------------------------------------------------------------------
void __fastcall TForm1::InitPnl(TPanel *P_Pnl, AnsiString Str)
{
    P_Pnl->Caption = Str ;
}


void __fastcall TForm1::Button5Click(TObject *Sender)
{
     // ステータスメッセージ
     StatBarClear(MSG_09);

     Form1->Print();

     // ステータスメッセージ
     StatBarClear(" ");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatBarClear( AnsiString sMsg )
{
     // ステータスメッセージ
     StatusBar1->SimpleText =  sMsg;
     StatusBar1->Update();
}

void __fastcall TForm1::FormActivate(TObject *Sender)
{
     Panel6->Caption = USER_COD;
     Panel7->Caption = USER_NAM;
     Panel3->Caption = BUMO_COD;
     Panel4->Caption = BUMO_NAM;
     edtymd->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::edtymd1Enter(TObject *Sender)
{
     ButtonInputMode(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edttlnoEnter(TObject *Sender)
{
     ButtonInputMode(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExecF1(void)
{
     // ステータスメッセージ
     StatBarClear( MSG_01);

     //硬度データファイルからデータを抽出
     iRec_Kd61 =  Kd61_Serch01() ;
     if (iRec_Kd61 <= 0 ) {
        StatBarClear( MSG_02);
     }else{
        StatBarClear( " ");
     }

     // 一覧検索結果の表示画面を開く
     Form2->ShowModal();
}

//-----------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   ExecF1();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   int  i,k;
   int iRtn;
   int button;

   int iPos;
   AnsiString strVal01;
   AnsiString strVal02;

   //検査値の取得
   strVal01 = Form1->edtymd->Text;
   // 日付(YYYY/MM/DD)から(YYYYMMDD)へ変換
   while ((iPos = strVal01.AnsiPos("/")) != 0) {
      strVal01.Delete(iPos,1);
   }
   strVal02 = Form1->edttlno->Text;

   //2002/11/19 履歴表示チェックボックスにフォーカスがあるときも検索実行 E.Takase
   //if ((edtymd->Focused() || edttlno->Focused() ) && (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1)) {  // Update ?
   // 2003/02/12 A.Tamura
   //if ((edtymd->Focused() || edttlno->Focused() || CheckBoxRireki->Focused()) && (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1)) {  // Update ?
   if ((edtymd->Focused() || edttlno->Focused() || CheckBoxRireki->Focused())
      && (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1 || CheckChangeData() == true) ) {  // Update ?
      button = MessageDlg( MSG_10.c_str(), mtConfirmation, mbYesNoCancel, 0);
      if (button == mrCancel){
         return;
      } else {  // YES or No
         if (button == mrNo) {
            // 2003/02/12 A.Tamura
            //Hsc_AllDataChg = 0;
            //Hsd_AllDataChg = 0;
         } else{  // Yes
            NextToreiFlag = 0;
            Button11Click(Sender);
            if (WriteDatabaseError == 1)
               return;
            // 2003/02/12 A.Tamura
            //Hsc_AllDataChg = 0;
            //Hsd_AllDataChg = 0;
         }
      }
   }

   //2002/11/19 履歴表示チェックボックスにフォーカスがないとき 追加 E.Takase
   //if (!(edtymd->Focused() || edttlno->Focused())) {
   if (!(edtymd->Focused() || edttlno->Focused()|| CheckBoxRireki->Focused())) {
      edtymd->SetFocus();
      return;
   }

   // ステータスメッセージ
   StatBarClear(MSG_01) ;

   Hsc_HaveSokutei = 0;
   Hsd_HaveSokutei = 0;

   // 硬度ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD61
   iRtn = Kd61_Serch02();

   if (iRtn == -1 ) {
      // ステータスメッセージ
      StatBarClear(MSG_02) ;

      GraphyImg_Hsc1->Canvas->Brush->Color = clMenu;
      GraphyImg_Hsc1->Canvas->FillRect( GraphyImg_Hsc1->ClientRect );
      GraphyImg_Hsc2->Canvas->Brush->Color = clMenu;
      GraphyImg_Hsc2->Canvas->FillRect( GraphyImg_Hsc2->ClientRect );

      GraphyImg_Hsd1->Canvas->Brush->Color = clMenu;
      GraphyImg_Hsd1->Canvas->FillRect( GraphyImg_Hsd1->ClientRect );
      GraphyImg_Hsd2->Canvas->Brush->Color = clMenu;
      GraphyImg_Hsd2->Canvas->FillRect( GraphyImg_Hsd1->ClientRect );

      SetInit(1);

      return;
   }

   ScreenInitFlag = 1;

   // 保存時の確認用に測定値のバックアップを行います。
   for( i=0; i<30; i++){
      for( k=0; k<100; k++){
         Bk_HSC_A_CH[i][k] = KD61Data[i].HSC_A_CH[k];
         Bk_HSC_S_CH[i][k] = KD61Data[i].HSC_S_CH[k];
         Bk_HSD_A_CH[i][k] = KD61Data[i].HSD_A_CH[k];
         Bk_HSD_S_CH[i][k] = KD61Data[i].HSD_S_CH[k];
      }
      Bk_HSC_SK_SU[i] = KD61Data[i].HSC_SK_SU;
      Bk_HSD_SK_SU[i] = KD61Data[i].HSD_SK_SU;
   }


   ////KD63W履歴ﾃﾞｰﾀテーブルの作成
   //Kd63W_Create01(KD61Data[0].KENSA_YMD, KD61Data[0].TOLEY_NO, LOTMAX);
   //
   ////KD63W履歴ﾃﾞｰﾀﾌｧｲﾙを読み込む
   //i  =  Kd63W_Serch01();
   // 測定履歴も検索する場合   2002/10/28 A.Tamura
   if( CheckBoxRireki->Checked ){

      //ロットNOの再読み込み　　2003/1/23 A.Tamura
      strVal02 = Form1->edttlno->Text;

	     //KD63W履歴ﾃﾞｰﾀテーブルの作成
	     //int iRec = Kd63W_Create01(KD61Data[0].KENSA_YMD, KD61Data[0].TOLEY_NO, LOTMAX);
	     int iRec = Kd63W_Create01(strVal01, strVal02.ToIntDef(0), LOTMAX);

	     if( iRec >0 ){

	        //KD63W履歴ﾃﾞｰﾀﾌｧｲﾙを読み込む
	        i  =  Kd63W_Serch01();

	     }else{
	       StatBarClear( MSG_12) ;
	     }

	} else{

        //KD63W履歴ﾃﾞｰﾀ 削除
        Kd63W_Delete01();

        //KD63W履歴ﾃﾞｰﾀ フォーマット
        KD63WFormat();

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
		DrawRireki1( Form1->GraphyImg_Hsc1, 0, &Xstr[0][0], Max, Min, Val, -1, 0, 0);
		DrawRireki1( Form1->GraphyImg_Hsc2, 0, &Xstr[0][0], Max, Min, Val, -1, 0, 0);
		DrawRireki( Form1->GraphyImg_Hsd1, 0, &Xstr[0][0], Max, Min, Val, -1, 0, 0);
		DrawRireki( Form1->GraphyImg_Hsd2, 0, &Xstr[0][0], Max, Min, Val, -1, 0, 0);
//        iOption = 2;
//        ToDrawGraph(1, iOption);
   }

   //計測ﾃﾞｰﾀがあればそのﾃﾞｰﾀを履歴ﾌｧｲﾙへコピー
   if (Hsc_HaveSokutei || Hsd_HaveSokutei)
       CopyKD61Data();

   //ScrollBarの初期値の設定
   Scr_Hsc1->Min = 0;
   Scr_Hsc1->Max = 0;
   Scr_Hsc1->Position =0;

   Scr_Hsc2->Min = 0;
   Scr_Hsc2->Max = 0;
   Scr_Hsc2->Position =0;

   Scr_Hsc3->Min = 0;
   Scr_Hsc3->Max = 0;
   Scr_Hsc3->Position =0;

   Scr_Hsd1->Min = 0;
   Scr_Hsd1->Max = 0;
   Scr_Hsd1->Position =0;

   Scr_Hsd2->Min = 0;
   Scr_Hsd2->Max = 0;
   Scr_Hsd2->Position =0;

   Scr_Hsd3->Min = 0;
   Scr_Hsd3->Max = 0;
   Scr_Hsd3->Position =0;

   //履歴作画（音ON, 色ON)
   Hsc_iOption = 1;
   Hsd_iOption = 1;

   // 計測値の変更があったかどうかの指示フラグ
   //Hsc_AllDataChg = 0;       // 2003/02/12
   Hsc_CurSampChg = 0;
   Hsc_CurDataChg = 0;

   //Hsd_AllDataChg = 0;       // 2003/02/12
   Hsd_CurSampChg = 0;
   Hsd_CurDataChg = 0;

   AreaFlag = 0;    // 0: 現在測定データ無し; 1: 現在Hscを測定している; 2: 現在Hsdを測定している

   if (Hsc_HaveSokutei == 0 && Hsd_HaveSokutei == 0) {
      ScreenInitFlag = 0;
      return;
   }

   iKskStart = 1;      // 測定開始

   // 最小有効SampleNoを探す
   Sample_P_Min = 0;
   Sample_P_Max = 0;
   for (i = 0; i < 30; i++) {
      if (KD61Data[i].SAMPLE_P != -1) {
         if (Sample_P_Min == 0)
            Sample_P_Min = i+1;
         Sample_P_Max = i+1;
      }
   }

   Hsc_DataNoIdx = 0;
   Hsd_DataNoIdx = 0;

   if (Hsc_HaveSokutei > 0) { // Hsc測定データあり
      Hsc_SamplePositionIdx = Sample_P_Min;
      // 圧面
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;

      // 側面
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;
   } else { // Hsc測定データなし
      Hsc_DataNoIdx = 0;
      Hsc_SamplePositionIdx = 0;
   }

   if (Hsd_HaveSokutei > 0) { // Hsd測定データあり
      Hsd_SamplePositionIdx = Sample_P_Min;
      // 圧面
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
          KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
         Hsd_DataNoIdx = 1;

      // 側面
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2 ||
          KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
         Hsd_DataNoIdx = 1;
   } else { // Hsd測定データなし
      Hsd_DataNoIdx = 0;
      Hsd_SamplePositionIdx = 0;
   }

   if (Hsc_SamplePositionIdx > 0) {
      // 有効Sampleを探す
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
         while (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
            Hsc_SamplePositionIdx++;
            if (Hsc_SamplePositionIdx > 30)
               Hsc_SamplePositionIdx = 1;
         }
      }
      SetAreaInfo(1, 0);
      Scr_Hsc1->Position = Hsc_SamplePositionIdx;
      //ToDrawGraph(Hsc_SamplePositionIdx, 3, 1);
   } else {
      // HsC 初期状態設定
      Unenable(1);
   }

   if (Hsd_SamplePositionIdx > 0) {
      // 有効Sampleを探す
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 <= 0) {
         while (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 <= 0) {
            Hsd_SamplePositionIdx++;
            if (Hsd_SamplePositionIdx > 30)
               Hsd_SamplePositionIdx = 1;
         }
      }
      SetAreaInfo(2, 0);
      Scr_Hsd1->Position = Hsd_SamplePositionIdx;
      //ToDrawGraph(Hsd_SamplePositionIdx, 3, 2);
   } else {
      // HsD 初期状態設定
      Unenable(2);
   }

   //備考をヒントにセット 2002/11/08 E.Takase
   SetMEMO();

   // Focus Area ： Hsc？Hsd？
   if (Hsc_HaveSokutei > 0) {
      Pan_Hsc->Color = clYellow;
      Pan_Hsd->Color = clMenu;
      PageCtl_Hsc->Enabled = true;
      PageCtl_Hsd->Enabled = false;
      AreaFlag = 1;
   } else {
      Pan_Hsc->Color = clMenu;
      if (Hsd_HaveSokutei > 0) {
         Pan_Hsd->Color = clYellow;
         AreaFlag = 2;
         PageCtl_Hsd->Enabled = true;
         PageCtl_Hsc->Enabled = false;
      } else {
         Pan_Hsd->Color = clMenu;
         PageCtl_Hsc->Enabled = false;
         PageCtl_Hsd->Enabled = false;
      }
   }

   SetAreaInfo(AreaFlag, 1);

   // ステータスメッセージ
   StatBarClear("  ") ;

   // 2003/02/12 A.Tamura
   //Hsc_AllDataChg = 0;
   //Hsd_AllDataChg = 0;

   ScreenInitFlag = 0;   
}

//---------------------------------------------------------------------------

void __fastcall TForm1::SetAreaInfo(int AreaNo, int SetFlag)
{
 int Old_Cur;
 int Old_Chg;

 if (!(AreaNo == 1 || AreaNo == 2))
    return;

 if (AreaNo == 1 && Hsc_SamplePositionIdx <= 0)
    return;

 if (AreaNo == 2 && Hsd_SamplePositionIdx <= 0)
    return;

 if (AreaNo == 1) { // Hsc
   Hsc_DataNoIdx = 1;
   // HSC_SK_NUM_CURをチェック
   switch (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1) {
   case 0:
        KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = 0;
        break;
   case 1:
   case 2:
        if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM)
           KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR =  KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
        break;
   case 3:
        if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM * 2)
           KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR =  KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM * 2;
        break;
   }

   Old_Cur = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
   // 2003/02/12 A.Tamura
   //Old_Chg = Hsc_AllDataChg;

   if (!Scr_Hsc1->Enabled) {
      Scr_Hsc1->Enabled = true;
      Edt_Hsc_Sample->Enabled = true;
      Edt_Hsc_Sample->Color = clWhite;
   }

   Scr_Hsc1->Max = Sample_P_Max;
   Scr_Hsc1->Min = Sample_P_Min;

   Scr_Hsc1->Position =Hsc_SamplePositionIdx;
   Edt_Hsc_Sample->Text = Hsc_SamplePositionIdx;

   // 圧面
   if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
      KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {

      // データ１、２表示
      if (!Edt_Hsc11->Enabled || Edt_Hsc11->ReadOnly) {
         Edt_Hsc11->Enabled = true;
         Edt_Hsc11->ReadOnly = false;
         Edt_Hsc11->Color = clWhite;
         Edt_Hsc12->Enabled = true;
         Edt_Hsc12->Color = clWhite;
         Edt_Hsc11->Font->Color = clWindowText;
         Edt_Hsc12->Font->Color = clWindowText;
      }
      Edt_Hsc11->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[0];
      KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
      Edt_Hsc11->Font->Color = clWindowText;
      FieldColor(Hsc_SamplePositionIdx, 1, 1);
      Edt_Hsc12->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[1];
      KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
      Edt_Hsc12->Font->Color = clWindowText;
      FieldColor(Hsc_SamplePositionIdx, 2, 1);
      Pan_Hsc5->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;

      // データ３以降
      if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM > 2) {
         if (!Scr_Hsc2->Enabled) {
            Scr_Hsc2->Enabled = true;
            Edt_Hsc14->Enabled = true;
            Edt_Hsc14->Color = clWhite;
            Edt_Hsc13->Enabled = true;
            Edt_Hsc13->Color = clWhite;
            Edt_Hsc13->Font->Color = clWindowText;
         }

         Scr_Hsc2->Max = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
         Scr_Hsc2->Min = 3;
         Scr_Hsc2->Position = 3;
         Edt_Hsc14->Text = 3;

         Edt_Hsc13->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[2];
         KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
         Edt_Hsc13->Font->Color = clWindowText;
         FieldColor(Hsc_SamplePositionIdx, 3, 1);
      } else {
         Scr_Hsc2->Enabled = false;
         Edt_Hsc14->Text = 0;
         Edt_Hsc14->Color = clMenu;
         Edt_Hsc14->Enabled = false;
         Edt_Hsc13->Enabled = false;
         Edt_Hsc13->Color = clMenu;
         Edt_Hsc13->Font->Color = clWindowText;
      }

      // 計測規格
      Pan_Hsc1->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MIN;
      Pan_Hsc2->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_MAX;

   } else {
      //Edt_Hsc11->Enabled = false;
      Edt_Hsc11->ReadOnly = true;
      Edt_Hsc11->Color = clMenu;
      Edt_Hsc11->Font->Color = clWindowText;
      Edt_Hsc12->Enabled = false;
      Edt_Hsc12->Color = clMenu;
      Edt_Hsc12->Font->Color = clWindowText;
      Edt_Hsc13->Enabled = false;
      Edt_Hsc13->Color = clMenu;
      Edt_Hsc13->Font->Color = clWindowText;
      Scr_Hsc2->Enabled = false;
      Edt_Hsc14->Text = 0;
      Edt_Hsc14->Color = clMenu;
      Edt_Hsc14->Enabled = false;
      Pan_Hsc1->Caption = 0;
      Pan_Hsc2->Caption = 0;
      Pan_Hsc5->Caption = 0;
   }

   // 側面
   if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2 ||
      KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {

      // データ１、２表示
      if (!Edt_Hsc21->Enabled) {
         Edt_Hsc21->Enabled = true;
         Edt_Hsc21->Color = clWhite;
         Edt_Hsc22->Enabled = true;
         Edt_Hsc22->Color = clWhite;
         Edt_Hsc21->Font->Color = clWindowText;
         Edt_Hsc22->Font->Color = clWindowText;
      }
      Edt_Hsc21->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[0];
      KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
      Edt_Hsc21->Font->Color = clWindowText;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2)
         FieldColor(Hsc_SamplePositionIdx, 1, 1);
      else
         FieldColor(Hsc_SamplePositionIdx, KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM + 1, 1);
      Edt_Hsc22->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[1];
      KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
      Edt_Hsc22->Font->Color = clWindowText;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2)
         FieldColor(Hsc_SamplePositionIdx, 2, 1);
      else
         FieldColor(Hsc_SamplePositionIdx, KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM + 2, 1);
      Pan_Hsc6->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;

      // データ３以降
      if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM > 2) {
         if (!Scr_Hsc3->Enabled) {
            Scr_Hsc3->Enabled = true;
            Edt_Hsc24->Enabled = true;
            Edt_Hsc24->Color = clWhite;
            Edt_Hsc23->Enabled = true;
            Edt_Hsc23->Color = clWhite;
            Edt_Hsc23->Font->Color = clWindowText;
         }

         Scr_Hsc3->Max = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
         Scr_Hsc3->Min = 3;
         Scr_Hsc3->Position = 3;
         Edt_Hsc24->Text = 3;

         Edt_Hsc23->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[2];
         KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
         Edt_Hsc23->Font->Color = clWindowText;
         if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2)
            FieldColor(Hsc_SamplePositionIdx, 3, 1);
         else
            FieldColor(Hsc_SamplePositionIdx, KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM + 3, 1);
      } else {
         Scr_Hsc3->Enabled = false;
         Edt_Hsc24->Text = 0;
         Edt_Hsc23->Font->Color = clWindowText;
         Edt_Hsc24->Enabled = false;
         Edt_Hsc24->Color = clMenu;
         Edt_Hsc23->Enabled = false;
         Edt_Hsc23->Color = clMenu;
      }

      // 計測規格
      Pan_Hsc3->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MIN;
      Pan_Hsc4->Caption = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_MAX;
   } else {
      Scr_Hsc3->Enabled = false;
      Edt_Hsc24->Enabled = false;
      Edt_Hsc24->Color = clMenu;
      Pan_Hsc3->Caption = 0;
      Pan_Hsc4->Caption = 0;

      Edt_Hsc21->Enabled = false;
      Edt_Hsc21->Color = clMenu;
      Edt_Hsc21->Font->Color = clWindowText;
      Edt_Hsc22->Enabled = false;
      Edt_Hsc22->Color = clMenu;
      Edt_Hsc22->Font->Color = clWindowText;
      Edt_Hsc23->Enabled = false;
      Edt_Hsc23->Color = clMenu;
      Edt_Hsc23->Font->Color = clWindowText;
      Scr_Hsc3->Enabled = false;
      Edt_Hsc24->Enabled = false;
      Edt_Hsc24->Color = clMenu;
      Edt_Hsc24->Text = 0;
      Pan_Hsc3->Caption = 0;
      Pan_Hsc4->Caption = 0;
      Pan_Hsc6->Caption = 0;
   }

   // サンプル情報
   Pnl7->Caption = KD61Data[Hsc_SamplePositionIdx-1].DTKSCOD;
   Pnl8->Caption = KD61Data[Hsc_SamplePositionIdx-1].DTKSHIN;
   Pnl9->Caption = KD61Data[Hsc_SamplePositionIdx-1].LOTNO;
   Pnl10->Caption = KD61Data[Hsc_SamplePositionIdx-1].HINBAN;
   Pnl11->Caption = KD61Data[Hsc_SamplePositionIdx-1].ZISCOD;
   Pnl12->Caption = KD61Data[Hsc_SamplePositionIdx-1].ZISNAM;

   KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;

   if (SetFlag == 1) {
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
         KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {
         if (!Edt_Hsc11->Enabled)
            Edt_Hsc11->Enabled = true;
         Edt_Hsc11->SetFocus();
         Edt_Hsc11->SelectAll();
      } else {
         if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2) {
            if (!Edt_Hsc21->Enabled)
               Edt_Hsc21->Enabled = true;
            Edt_Hsc21->SetFocus();
            Edt_Hsc21->SelectAll();
         } else {
            //Edt_Hsc_Sample->SetFocus();
            if (!Edt_Hsc11->Enabled)
               Edt_Hsc11->Enabled = true;
            Edt_Hsc11->SetFocus();
            Edt_Hsc11->SelectAll();
         }
      }
   }

   // Hsd Area Unenable
   Unenable(2);
   KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
   // 2003/02/12 A.Tamura
   //Hsc_AllDataChg = Old_Chg;
 } else {   // Hsd
   Hsd_DataNoIdx = 1;
   // HSD_SK_NUM_CURをチェック
   switch (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2) {
   case 0:
        KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = 0;
        break;
   case 1:
   case 2:
        if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM)
           KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR =  KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
        break;
   case 3:
        if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM * 2)
           KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR =  KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM * 2;
        break;
   }

   Old_Cur = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
   // 2003/02/12 A.Tamura
   //Old_Chg = Hsd_AllDataChg;
   if (!Scr_Hsd1->Enabled) {
      Scr_Hsd1->Enabled = true;
      Edt_Hsd_Sample->Enabled = true;
      Edt_Hsd_Sample->Color = clWhite;
   }

   Scr_Hsd1->Max = Sample_P_Max;
   Scr_Hsd1->Min = Sample_P_Min;

   Scr_Hsd1->Position =Hsd_SamplePositionIdx;
   Edt_Hsd_Sample->Text = Hsd_SamplePositionIdx;

   Pan_Hsd5->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;

   // 圧面
   if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
      KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) {

      // データ１、２表示
      if (!Edt_Hsd11->Enabled || Edt_Hsd11->ReadOnly) {
         Edt_Hsd11->Enabled = true;
         Edt_Hsd11->ReadOnly = false;
         Edt_Hsd11->Color = clWhite;
         Edt_Hsd12->Enabled = true;
         Edt_Hsd12->Color = clWhite;
         Edt_Hsd11->Font->Color = clWindowText;
         Edt_Hsd21->Font->Color = clWindowText;
      }
      Edt_Hsd11->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[0];
      KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
      Edt_Hsd11->Font->Color = clWindowText;
      FieldColor(Hsd_SamplePositionIdx, 1, 2);
      Edt_Hsd12->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[1];
      Edt_Hsd12->Font->Color = clWindowText;
      KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
      FieldColor(Hsd_SamplePositionIdx, 2, 2);

      // データ３以降
      if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM > 2) {
         if (!Scr_Hsd2->Enabled) {
            Scr_Hsd2->Enabled = true;
            Edt_Hsd14->Enabled = true;
            Edt_Hsd14->Color = clWhite;
            Edt_Hsd13->Enabled = true;
            Edt_Hsd13->Color = clWhite;
            Edt_Hsd13->Font->Color = clWindowText;
         }

         Scr_Hsd2->Max = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
         Scr_Hsd2->Min = 3;
         Scr_Hsd2->Position = 3;
         Edt_Hsd14->Text = 3;

         Edt_Hsd13->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[2];
         KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
         Edt_Hsd13->Font->Color = clWindowText;
         FieldColor(Hsd_SamplePositionIdx, 3, 2);
      } else {
         Scr_Hsd2->Enabled = false;
         Edt_Hsd14->Text = 0;
         Edt_Hsd14->Enabled = false;
         Edt_Hsd14->Color = clMenu;
         Edt_Hsd13->Enabled = false;
         Edt_Hsd13->Color = clMenu;
         Edt_Hsd13->Font->Color = clWindowText;
      }

      // 計測規格
      Pan_Hsd1->Caption = FormatFloat("#0.0",KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MIN);
      Pan_Hsd2->Caption = FormatFloat("#0.0",KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MAX);
      //Pan_Hsd1->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MIN;
      //Pan_Hsd2->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_MAX;

   } else {
      //Edt_Hsd11->Enabled = false;
      Edt_Hsd11->ReadOnly = true;
      Edt_Hsd11->Color = clMenu;
      Edt_Hsd11->Font->Color = clWindowText;
      Edt_Hsd12->Enabled = false;
      Edt_Hsd12->Color = clMenu;
      Edt_Hsd12->Font->Color = clWindowText;
      Edt_Hsd13->Enabled = false;
      Edt_Hsd13->Color = clMenu;
      Edt_Hsd13->Font->Color = clWindowText;
      Scr_Hsd2->Enabled = false;
      Edt_Hsd14->Text = 0;
      Edt_Hsd14->Enabled = false;
      Edt_Hsd14->Color = clMenu;
      Pan_Hsd1->Caption = 0;
      Pan_Hsd2->Caption = 0;
      Pan_Hsd5->Caption = 0;
   }

   // 側面
   if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2 ||
      KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) {

      // データ１、２表示
      if (!Edt_Hsd21->Enabled) {
         Edt_Hsd21->Enabled = true;
         Edt_Hsd21->Color = clWhite;
         Edt_Hsd22->Enabled = true;
         Edt_Hsd22->Color = clWhite;
         Edt_Hsd21->Font->Color = clWindowText;
         Edt_Hsd22->Font->Color = clWindowText;
      }
      Edt_Hsd21->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[0];
      KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
      Edt_Hsd21->Font->Color = clWindowText;
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2)
         FieldColor(Hsd_SamplePositionIdx, 1, 2);
      else
         FieldColor(Hsd_SamplePositionIdx, KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM + 1, 2);
      Edt_Hsd22->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[1];
      KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
      Edt_Hsd22->Font->Color = clWindowText;
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2)
         FieldColor(Hsd_SamplePositionIdx, 2, 2);
      else
         FieldColor(Hsd_SamplePositionIdx, KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM + 2, 2);
      Pan_Hsd6->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;

      // データ３以降
      if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM > 2) {
         if (!Scr_Hsd3->Enabled) {
            Scr_Hsd3->Enabled = true;
            Edt_Hsd24->Enabled = true;
            Edt_Hsd24->Color = clWhite;
            Edt_Hsd23->Enabled = true;
            Edt_Hsd23->Color = clWhite;
            Edt_Hsd23->Font->Color = clWindowText;
         }

         Scr_Hsd3->Max = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
         Scr_Hsd3->Min = 3;
         Scr_Hsd3->Position = 3;
         Edt_Hsd24->Text = 3;

         Edt_Hsd23->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[2];
         KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
         Edt_Hsd23->Font->Color = clWindowText;
         if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2)
            FieldColor(Hsd_SamplePositionIdx, 3, 2);
         else
            FieldColor(Hsd_SamplePositionIdx, KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM + 3, 2);
      } else {
         Scr_Hsd3->Enabled = false;
         Edt_Hsd24->Text = 0;
         Edt_Hsd24->Enabled = false;
         Edt_Hsd24->Color = clMenu;
         Edt_Hsd23->Enabled = false;
         Edt_Hsd23->Color = clMenu;
         Edt_Hsd23->Font->Color = clWindowText;
      }

      // 計測規格
      //Pan_Hsd3->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MIN;
      //Pan_Hsd4->Caption = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MAX;
      Pan_Hsd3->Caption = FormatFloat("#0.0",KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MIN);
      Pan_Hsd4->Caption = FormatFloat("#0.0",KD61Data[Hsd_SamplePositionIdx-1].HSD_S_MAX);
   } else {
      Scr_Hsd3->Enabled = false;
      Edt_Hsd24->Enabled = false;
      Edt_Hsd24->Color = clMenu;
      Pan_Hsd3->Caption = 0;
      Pan_Hsd4->Caption = 0;

      Edt_Hsd21->Enabled = false;
      Edt_Hsd21->Color = clMenu;
      Edt_Hsd21->Font->Color = clWindowText;
      Edt_Hsd22->Enabled = false;
      Edt_Hsd22->Color = clMenu;
      Edt_Hsd22->Font->Color = clWindowText;
      Edt_Hsd23->Enabled = false;
      Edt_Hsd23->Color = clMenu;
      Edt_Hsd23->Font->Color = clWindowText;
      Scr_Hsd3->Enabled = false;
      Edt_Hsd24->Text = 0;
      Edt_Hsd24->Enabled = false;
      Edt_Hsd24->Color = clMenu;
      Pan_Hsd3->Caption = 0;
      Pan_Hsd4->Caption = 0;
      Pan_Hsd6->Caption = 0;
   }

   KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;

   // サンプル情報
   Pnl7->Caption = KD61Data[Hsd_SamplePositionIdx-1].DTKSCOD;
   Pnl8->Caption = KD61Data[Hsd_SamplePositionIdx-1].DTKSHIN;
   Pnl9->Caption = KD61Data[Hsd_SamplePositionIdx-1].LOTNO;
   Pnl10->Caption = KD61Data[Hsd_SamplePositionIdx-1].HINBAN;
   Pnl11->Caption = KD61Data[Hsd_SamplePositionIdx-1].ZISCOD;
   Pnl12->Caption = KD61Data[Hsd_SamplePositionIdx-1].ZISNAM;

   if (SetFlag == 1) {
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
         KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) {
         if (!Edt_Hsd11->Enabled)
            Edt_Hsd11->Enabled = true;
         Edt_Hsd11->SetFocus();
         Edt_Hsd11->SelectAll();
      } else {
         if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2) {
            if (!Edt_Hsd21->Enabled)
               Edt_Hsd21->Enabled = true;
            Edt_Hsd21->SetFocus();
            Edt_Hsd21->SelectAll();
         } else {
            //Edt_Hsd_Sample->SetFocus();
            if (!Edt_Hsd11->Enabled)
               Edt_Hsd11->Enabled = true;
            Edt_Hsd11->SetFocus();
            Edt_Hsd11->SelectAll();
         }
      }
   }

   // Hsd Area Unenable
   Unenable(1);
   KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
   // 2003/02/12 A.Tamura
   //Hsd_AllDataChg = Old_Chg;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc_SampleEnter(TObject *Sender)
{
     AreaFlag = 1;
     ButtonInputMode(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonInputMode(int Opt)
{
 if (Opt == 1) { // 入力Mode
    if (Button1->Enabled)
       Button1->Enabled = false;
    if (!Button2->Enabled)
       Button2->Enabled = true;
    if (!Button3->Enabled)
       Button3->Enabled = true;
    if (!Button10->Enabled)
       Button10->Enabled = true;
    if (!Button11->Enabled)
       Button11->Enabled = true;
    if (Hsc_SamplePositionIdx > 0 && Hsd_SamplePositionIdx > 0)
       Button4->Enabled = true;
    else
       Button4->Enabled = false;
 } else {
    if (!Button1->Enabled)
       Button1->Enabled = true;
//    if (Button2->Enabled)             // 2000.3.10
//       Button2->Enabled = false;
//    if (Button3->Enabled)
//       Button3->Enabled = false;
    if (!Button2->Enabled)
       Button2->Enabled = true;
    if (!Button3->Enabled)
       Button3->Enabled = true;
    if (Button10->Enabled)
       Button10->Enabled = false;
    if (Button11->Enabled)
       Button11->Enabled = false;
    if (Button4->Enabled)
       Button4->Enabled = false;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc_SampleExit(TObject *Sender)
{
 int n;

   if (Hsc_CurSampChg == 1) {
      AddKd63W(1);
      Hsc_CurSampChg = 0;
   }

   // マウスでScrollBarを変更する場合
   if (Hsc_SamplePositionIdx > 0 && Hsc_SamplePositionIdx >= Sample_P_Min &&
       Hsc_SamplePositionIdx <= Sample_P_Max) {

      n = Edt_Hsc_Sample->Value;

      if (n >= Sample_P_Min && n <= Sample_P_Max) {

         if (KD61Data[n-1].SAMPLE_P == -1) {
            //Edt_Hsc_Sample->SetFocus();
            return;
         }

         Hsc_SamplePositionIdx = n;

         Hsc_DataNoIdx = 0;
         if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
             KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
            Hsc_DataNoIdx = 1;

         if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2 ||
             KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
            Hsc_DataNoIdx = 1;

         SetAreaInfo(1, 1);
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd_SampleExit(TObject *Sender)
{
 int n;

   if (Hsd_CurSampChg == 1) {
      AddKd63W(2);
      Hsd_CurSampChg = 0;
   }

   // マウスでScrollBarを変更する場合
   if (Hsd_SamplePositionIdx > 0 && Hsd_SamplePositionIdx >= Sample_P_Min &&
       Hsd_SamplePositionIdx <= Sample_P_Max) {

      n = Edt_Hsd_Sample->Value;

      if (n >= Sample_P_Min && n <= Sample_P_Max) {

         if (KD61Data[n-1].SAMPLE_P == -1) {
            //Edt_Hsd_Sample->SetFocus();
            return;
         }

         Hsd_SamplePositionIdx = n;

         Hsd_DataNoIdx = 0;

         if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
             KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
            Hsd_DataNoIdx = 1;

         if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2 ||
             KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
            Hsd_DataNoIdx = 1;

         SetAreaInfo(2, 1);
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc_SampleKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{


 if (Key == VK_F2 || Key == VK_F3 || Key == VK_F4 || Key == VK_F5 ||
    Key == VK_F7 || Key == VK_F10 || Key == VK_F11 || Key == VK_F12) {

    if (Edt_Hsc11->Focused() || Edt_Hsc12->Focused() || Edt_Hsc13->Focused() ||
       Edt_Hsc21->Focused() || Edt_Hsc22->Focused() || Edt_Hsc23->Focused()) {
       Edt_Hsc11Exit(Sender);
    }

    if (Edt_Hsd11->Focused() || Edt_Hsd12->Focused() || Edt_Hsd13->Focused() ||
       Edt_Hsd21->Focused() || Edt_Hsd22->Focused() || Edt_Hsd23->Focused()) {
       Edt_Hsd11Exit(Sender);
    }
 }

 switch(Key) {
 case VK_F1:
      ExecF1();
      break;
 case VK_F2:
      // 2000.3.10 Add by Zhou Qinming  トレーNoに戻る
      if ((Edt_Hsc_Sample->Focused() && Hsc_SamplePositionIdx == Sample_P_Min) ||
          (Edt_Hsd_Sample->Focused() && Hsd_SamplePositionIdx == Sample_P_Min)) {
         edttlno->SetFocus();
         edttlno->SetFocus();
         edttlno->SelectAll();
         return;
      }
      if (Edt_Hsc11->Focused() && Hsc_SamplePositionIdx == Sample_P_Min) {
         Edt_Hsc_Sample->SetFocus();
         Edt_Hsc_Sample->SelectAll();
         return;
      }
      if (Edt_Hsd11->Focused() && Hsd_SamplePositionIdx == Sample_P_Min) {
         Edt_Hsd_Sample->SetFocus();
         Edt_Hsd_Sample->SelectAll();
         return;
      }
      // end of add

      ScreenInitFlag = 1;
      Button2Click(Sender);
      ScreenInitFlag = 0;
      break;
 case VK_F3:
      // 2000.3.10 Add by Zhou Qinming
      if (Edt_Hsc_Sample->Focused() && Hsc_SamplePositionIdx == Sample_P_Max) {
         Edt_Hsc11->SetFocus();
         Edt_Hsc11->SelectAll();
         return;
      }
      if (Edt_Hsd_Sample->Focused() && Hsd_SamplePositionIdx == Sample_P_Max) {
         Edt_Hsd11->SetFocus();
         Edt_Hsd11->SelectAll();
         return;
      }
      // End of Add
      ScreenInitFlag = 1;
      Button3Click(Sender);
      ScreenInitFlag = 0;
      break;
 case VK_F4:
      if (Edt_Hsc_Sample->Focused()) {
         Edt_Hsc11->SetFocus();
         Edt_Hsc11->SelectAll();
      }
      if (Edt_Hsd_Sample->Focused()) {
         Edt_Hsd11->SetFocus();
         Edt_Hsd11->SelectAll();
      }
      Button4Click(Sender);
      break;
 case VK_F5:
      Button5Click(Sender);
      break;
 case VK_F6:
      Button6Click(Sender);
      break;
 case VK_F7:
      Button7Click(Sender);
      break;
 case VK_F10:
      Key = 0;
      Button10Click(Sender);
      break;
 case VK_F11:
      NextToreiFlag = 1;
      Button11Click(Sender);
      break;
 case VK_F12:
      Button12Click(Sender);
      break;
 case VK_RETURN:
      if (edtymd->Focused()) {
         edttlno->SetFocus();
         break;
      }
      if (edttlno->Focused()) {
         Button7Click(Sender);
         break;
      }
      if (Edt_Hsc_Sample->Focused()) {
         Edt_Hsc_SampleExit(Sender);
         break;
      }
      if (Edt_Hsd_Sample->Focused()) {
         Edt_Hsd_SampleExit(Sender);
         break;
      }
      if (Edt_Hsc11->Focused() || Edt_Hsc12->Focused() || Edt_Hsc13->Focused() ||
         Edt_Hsc21->Focused() || Edt_Hsc22->Focused() || Edt_Hsc23->Focused()) {
         Edt_Hsc11Exit(Sender);
         ScreenInitFlag = 1;
         Button3Click(Sender);
         ScreenInitFlag = 0;
         break;
      }

      if (Edt_Hsd11->Focused() || Edt_Hsd12->Focused() || Edt_Hsd13->Focused() ||
         Edt_Hsd21->Focused() || Edt_Hsd22->Focused() || Edt_Hsd23->Focused()) {
         Edt_Hsd11Exit(Sender);
         ScreenInitFlag = 1;
         Button3Click(Sender);
         ScreenInitFlag = 0;
         break;
      }
      if (Edt_Hsc14->Focused()) {
         Edt_Hsc13->SetFocus();
         Edt_Hsc13->SelectAll();
         break;
      }
      if (Edt_Hsc24->Focused()) {
         Edt_Hsc23->SetFocus();
         Edt_Hsc23->SelectAll();
         break;
      }
      if (Edt_Hsd14->Focused()) {
         Edt_Hsd13->SetFocus();
         Edt_Hsd13->SelectAll();
         break;
      }
      if (Edt_Hsd24->Focused()) {
         Edt_Hsd23->SetFocus();
         Edt_Hsd23->SelectAll();
         break;
      }
      break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc11Enter(TObject *Sender)
{
    //ScreenInitFlag = 1;
     AreaFlag = 1;
     ButtonInputMode(1);
     if (Edt_Hsc11->Focused()) {
        //Edt_Hsc11->Color = clYellow;
        Hsc_DataNoIdx = 1;
     }
     if (Edt_Hsc12->Focused()) {
        //Edt_Hsc12->Color = clYellow;
        Hsc_DataNoIdx = 2;
     }
     if (Edt_Hsc13->Focused() || Edt_Hsc14->Focused() ) {
        //if (Edt_Hsc13->Focused())
        //   Edt_Hsc13->Color = clYellow;
        Hsc_DataNoIdx = Edt_Hsc14->Value;
     }
     if (Edt_Hsc21->Focused()) {
        //Edt_Hsc21->Color = clYellow;
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 != 3)
           Hsc_DataNoIdx = 1;
        else
           Hsc_DataNoIdx = 1 + KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
     }
     if (Edt_Hsc22->Focused()) {
        //Edt_Hsc22->Color = clYellow;
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 != 3)
           Hsc_DataNoIdx = 2;
        else
           Hsc_DataNoIdx = 2 + KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
     }
     if (Edt_Hsc23->Focused() || Edt_Hsc24->Focused() ) {
        //if (Edt_Hsc23->Focused())
        //   Edt_Hsc23->Color = clYellow;
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 != 3)
           Hsc_DataNoIdx = Edt_Hsc24->Value;
        else
           Hsc_DataNoIdx = Edt_Hsc24->Value + KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
     }
//     FieldColor(Hsc_SamplePositionIdx, Hsc_DataNoIdx, 1);

// 2003/02/12 A.Tamura
// Hsc_CurDataChg = 0;
     if (Edt_Hsc11->Focused() || Edt_Hsc12->Focused() ||
         Edt_Hsc13->Focused() || Edt_Hsc14->Focused()) {
        if (Hsc_iOption == 3)
           Hsc_iOption = 1;
        if (Hsc_iOption == 4)
           Hsc_iOption = 2;
        ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);
     } else {
        if (Hsc_iOption == 1)
           Hsc_iOption = 3;
        if (Hsc_iOption == 2)
           Hsc_iOption = 4;
        ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);
   }
//   ScreenInitFlag = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Unenable(int Opt)
{

 if (Opt == 1) {
      // HsC 初期状態設定
      Edt_Hsc_Sample->Enabled = false;
      Edt_Hsc_Sample->Color = clMenu;
      Scr_Hsc1->Enabled = false;
      Scr_Hsc2->Enabled = false;
      Scr_Hsc3->Enabled = false;
      Edt_Hsc11->Enabled = false;
      Edt_Hsc11->Color = clMenu;
      Edt_Hsc12->Enabled = false;
      Edt_Hsc12->Color = clMenu;
      Edt_Hsc13->Enabled = false;
      Edt_Hsc13->Color = clMenu;
      Edt_Hsc14->Enabled = false;
      Edt_Hsc14->Color = clMenu;
      Edt_Hsc21->Enabled = false;
      Edt_Hsc21->Color = clMenu;
      Edt_Hsc22->Enabled = false;
      Edt_Hsc22->Color = clMenu;
      Edt_Hsc23->Enabled = false;
      Edt_Hsc23->Color = clMenu;
      Edt_Hsc24->Enabled = false;
      Edt_Hsc24->Color = clMenu;
 } else {
      Edt_Hsd_Sample->Enabled = false;
      Edt_Hsd_Sample->Color = clMenu;
      Scr_Hsd1->Enabled = false;
      Scr_Hsd2->Enabled = false;
      Scr_Hsd3->Enabled = false;
      Edt_Hsd11->Enabled = false;
      Edt_Hsd11->Color = clMenu;
      Edt_Hsd12->Enabled = false;
      Edt_Hsd12->Color = clMenu;
      Edt_Hsd13->Enabled = false;
      Edt_Hsd13->Color = clMenu;
      Edt_Hsd14->Enabled = false;
      Edt_Hsd14->Color = clMenu;
      Edt_Hsd21->Enabled = false;
      Edt_Hsd21->Color = clMenu;
      Edt_Hsd22->Enabled = false;
      Edt_Hsd22->Color = clMenu;
      Edt_Hsd23->Enabled = false;
      Edt_Hsd23->Color = clMenu;
      Edt_Hsd24->Enabled = false;
      Edt_Hsd24->Color = clMenu;
 }
}

// HscとHsdを切り替え
void __fastcall TForm1::Button4Click(TObject *Sender)
{
     if (Hsc_HaveSokutei == 0 || Hsd_HaveSokutei == 0)
        return;

     if (AreaFlag == 1) {
        if (Hsc_CurSampChg == 1) {
           AddKd63W(AreaFlag);
           Hsc_CurSampChg = 0;
        }
        Pan_Hsd->Color = clYellow;
        Pan_Hsc->Color = clMenu;
        PageCtl_Hsc->Enabled = false;
        PageCtl_Hsd->Enabled = true;
        AreaFlag = 2;
     } else {
        if (Hsd_CurSampChg == 1) {
           AddKd63W(AreaFlag);
           Hsd_CurSampChg = 0;
        }
        Pan_Hsc->Color = clYellow;
        Pan_Hsd->Color = clMenu;
        PageCtl_Hsd->Enabled = false;
        PageCtl_Hsc->Enabled = true;
        AreaFlag = 1;
     }
     SetAreaInfo(AreaFlag, 1);
     Hsc_DataNoIdx = 1;
     Hsd_DataNoIdx = 1;

     //Beep();
}
//---------------------------------------------------------------------------

// 前項
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 int FldNum;

     if (!(AreaFlag == 1 || AreaFlag == 2))
        return;

     if (AreaFlag == 1 && (Hsc_HaveSokutei == 0 || Hsc_SamplePositionIdx <= 0))
        return;

     if (AreaFlag == 2 && (Hsd_HaveSokutei == 0 || Hsd_SamplePositionIdx <= 0))
        return;

     if (AreaFlag == 1) {  // Hsc
        // CursorがSample入力Fieldにいる？
        if (Edt_Hsc_Sample->Focused()) {
           if (Hsc_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsc_CurSampChg = 0;
           }
           if (Hsc_SamplePositionIdx == Sample_P_Min) {
              Hsc_DataNoIdx = 1;
              SetFieldFocus();
           } else {
                Hsc_SamplePositionIdx--;
                SetAreaInfo(AreaFlag, 1);
                Hsc_DataNoIdx = 1;
                SetFieldFocus();
           }
           Edt_Hsc_Sample->SetFocus();
           Edt_Hsc_Sample->SelectAll();
           return;
        }

        // このSampleは測定データあるかどうか？
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 0) { // Pre Sample
           if (Hsc_SamplePositionIdx == Sample_P_Min)
              SetFieldFocus();
           else {
              Hsc_SamplePositionIdx--;
              SetAreaInfo(AreaFlag, 1);
              switch (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1) {
              case 0:
                   Hsc_DataNoIdx = 1;
                   break;
              case 1:
              case 2:
                   Hsc_DataNoIdx = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
                   break;
              case 3:
                   Hsc_DataNoIdx = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM*2;
                   break;
              }
              SetFieldFocus();
           }
           return;
        }

        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM * 2;
        else
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;

        if (Hsc_DataNoIdx == 1) {  // Change Sample
           if (Hsc_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsc_CurSampChg = 0;
           }
           if (Hsc_SamplePositionIdx == Sample_P_Min)
              SetFieldFocus();
           else {
              Hsc_SamplePositionIdx--;
              SetAreaInfo(AreaFlag, 1);
              switch (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1) {
              case 0:
                   Hsc_DataNoIdx = 1;
                   break;
              case 1:
              case 2:
                   Hsc_DataNoIdx = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
                   //Edt_Hsc14->Text = Hsc_DataNoIdx;
                   break;
              case 3:
                   Hsc_DataNoIdx = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM*2;
                   //Edt_Hsc14->Text = Hsc_DataNoIdx;
                   break;
              }
              SetFieldFocus();
           }
        } else {
           Hsc_DataNoIdx--;
           SetFieldFocus();
        }
     } else { // HSD
        // CursorがSample入力Fieldにいる？
        if (Edt_Hsd_Sample->Focused()) {
           if (Hsd_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsd_CurSampChg = 0;
           }
           if (Hsd_SamplePositionIdx == Sample_P_Min) {
              Hsc_DataNoIdx = 1;
              SetFieldFocus();
           } else {
                Hsd_SamplePositionIdx--;
                SetAreaInfo(AreaFlag,1);
                Hsd_DataNoIdx = 1;
                SetFieldFocus();
           }
           Edt_Hsd_Sample->SetFocus();
           Edt_Hsd_Sample->SelectAll() ;
           return;
        }

        // このSampleは測定データあるかどうか？
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 0) { // Pre Sample
           if (Hsd_SamplePositionIdx == Sample_P_Min)
              SetFieldFocus();
           else {
              Hsd_SamplePositionIdx--;
              SetAreaInfo(AreaFlag,1);
              switch (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2) {
              case 0:
                   Hsd_DataNoIdx = 1;
                   break;
              case 1:
              case 2:
                   Hsd_DataNoIdx = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
                   //Edt_Hsd14->Text = Hsd_DataNoIdx;
                   break;
              case 3:
                   Hsd_DataNoIdx = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM*2;
                   //Edt_Hsd14->Text = Hsd_DataNoIdx;
                   break;
              }
              SetFieldFocus();
           }
           return;
        }
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSD_SK_NUM * 2;
        else
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSD_SK_NUM;

        if (Hsd_DataNoIdx == 1) {  // Change Sample
           if (Hsd_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsd_CurSampChg = 0;
           }
           if (Hsd_SamplePositionIdx == Sample_P_Min)
              SetFieldFocus();
           else {
              Hsd_SamplePositionIdx--;
              SetAreaInfo(AreaFlag,1);
              switch (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2) {
              case 0:
                   Hsd_DataNoIdx = 1;
                   break;
              case 1:
              case 2:
                   Hsd_DataNoIdx = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
                   break;
              case 3:
                   Hsd_DataNoIdx = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM*2;
                   break;
              }
              SetFieldFocus();
           }
        } else {
           Hsd_DataNoIdx--;
           SetFieldFocus();
        }
     }
}
//---------------------------------------------------------------------------
//次項
void __fastcall TForm1::Button3Click(TObject *Sender)
{
 int FldNum;

     if (!(AreaFlag == 1 || AreaFlag == 2))
        return;

     if (AreaFlag == 1 && (Hsc_HaveSokutei == 0 || Hsc_SamplePositionIdx <= 0))
        return;

     if (AreaFlag == 2 && (Hsd_HaveSokutei == 0 || Hsd_SamplePositionIdx <= 0))
        return;

     if (AreaFlag == 1) {  // Hsc
        // CursorがSample入力Fieldにいる？
        if (Edt_Hsc_Sample->Focused()) {
           if (Hsc_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsc_CurSampChg = 0;
           }
           if (Hsc_SamplePositionIdx == Sample_P_Max) {
              Hsc_DataNoIdx = 1;
              SetFieldFocus();
           } else {
                Hsc_SamplePositionIdx++;
                SetAreaInfo(AreaFlag,1);
                Hsc_DataNoIdx = 1;
                SetFieldFocus();
           }
           Edt_Hsc_Sample->SetFocus();
           Edt_Hsc_Sample->SelectAll();
           return;
        }

        // このSampleは測定データあるかどうか？
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 0) { // Next Sample
           if (Hsc_SamplePositionIdx == Sample_P_Max) {
              //Hsc_DataNoIdx = 1;   1999.12.10 Update
              SetFieldFocus();   // Beepと色
              //Beep();
              if (Hsd_SamplePositionIdx > 0) {
                 Button4Click(Sender);
                 if (EndErrorFlag == 0 || Hsc_iOption == 5) {
                    MdPlayer->FileName = "Kchang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 } else {
                    Button11->SetFocus();
                    if (EndErrorFlag == 0 || Hsc_iOption == 5) {
                       MdPlayer->FileName = "End.wav";
                       MdPlayer->Open();
                       MdPlayer->Play();
                    }
                 }
              }
           } else {
              Hsc_SamplePositionIdx++;
              SetAreaInfo(AreaFlag, 1);
              Hsc_DataNoIdx = 1;
           }
           return;
        }
        if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM * 2;
        else
           FldNum = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;

        if (Hsc_DataNoIdx == FldNum) {  // Change Sample
           if (Hsc_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsc_CurSampChg = 0;
           }
           if (Hsc_SamplePositionIdx == Sample_P_Max) {
              SetFieldFocus();        // Beepと色
              //Beep();
              if (Hsd_SamplePositionIdx > 0) {
                 Button4Click(Sender);
                 if (Hsc_iOption == 5 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 Button11->SetFocus();
                 if (Hsc_iOption == 5 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           } else {
              Hsc_SamplePositionIdx++;
              SetAreaInfo(AreaFlag, 1);
              Hsc_DataNoIdx = 1;
           }
        } else {
           Hsc_DataNoIdx++;
           SetFieldFocus();
        }
     } else { // HSD
        // CursorがSample入力Fieldにいる？
        if (Edt_Hsd_Sample->Focused()) {
           if (Hsd_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsd_CurSampChg = 0;
           }
           if (Hsd_SamplePositionIdx == Sample_P_Max) {
              Hsd_DataNoIdx = 1;
              SetFieldFocus();
           } else {
                Hsd_SamplePositionIdx++;
                SetAreaInfo(AreaFlag, 1);
                Hsd_DataNoIdx = 1;
                SetFieldFocus();
           }
           Edt_Hsd_Sample->SetFocus();
           Edt_Hsd_Sample->SelectAll();
           return;
        }

        // このSampleは測定データあるかどうか？
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 0) {  // Next Sample
           if (Hsd_SamplePositionIdx == Sample_P_Max) {
              //Hsd_DataNoIdx = 1;   1999.12.10 Update
              SetFieldFocus();       // Beepと色
              Button11->SetFocus();
              if (EndErrorFlag == 0 || Hsd_iOption == 5) {
                 MdPlayer->FileName = "End.wav";
                 MdPlayer->Open();
                 MdPlayer->Play();
              }
              //Beep();
           } else {
              Hsd_SamplePositionIdx++;
              SetAreaInfo(AreaFlag, 1);
              Hsd_DataNoIdx = 1;
           }
           return;
        }
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
           FldNum = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM * 2;
        else
           FldNum = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;

        if (Hsd_DataNoIdx == FldNum) {  // Change Sample
           if (Hsd_CurSampChg == 1) {
              AddKd63W(AreaFlag);
              Hsd_CurSampChg = 0;
           }
           if (Hsd_SamplePositionIdx == Sample_P_Max) {
              SetFieldFocus();        // Beepと色
              Button11->SetFocus();
              if (EndErrorFlag == 0 || Hsd_iOption == 5) {
                 MdPlayer->FileName = "End.wav";
                 MdPlayer->Open();
                 MdPlayer->Play();
              }
              //Beep();
           } else {
              Hsd_SamplePositionIdx++;
              SetAreaInfo(AreaFlag, 1);
              Hsd_DataNoIdx = 1;
           }
           return;
        } else {
           Hsd_DataNoIdx++;
           SetFieldFocus();
        }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetFieldFocus(void)
{
 int Old_Cur;

 if (!(AreaFlag == 1 || AreaFlag == 2))
    return;

 if (AreaFlag == 1) { // Hsc
    if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 0) {
       Edt_Hsc11->SetFocus();
       Edt_Hsc11->SelectAll();
       return;
    }
    if (Hsc_DataNoIdx <= KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
       if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) { // 圧面
          switch (Hsc_DataNoIdx) {
          case 1:
               Edt_Hsc11->SetFocus();
               Edt_Hsc11->SelectAll();
               break;
          case 2:
               Edt_Hsc12->SetFocus();
               Edt_Hsc12->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
               Edt_Hsc13->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx-1];
               Edt_Hsc14->Text = Hsc_DataNoIdx;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
               Edt_Hsc13->SetFocus();
               Edt_Hsc13->SelectAll();
               break;

          }
       } else { // 側面
          switch (Hsc_DataNoIdx) {
          case 1:
               Edt_Hsc21->SetFocus();
               Edt_Hsc21->SelectAll();
               break;
          case 2:
               Edt_Hsc22->SetFocus();
               Edt_Hsc22->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
               Edt_Hsc23->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx-1];
               Edt_Hsc24->Text = Hsc_DataNoIdx;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
               Edt_Hsc23->SetFocus();
               Edt_Hsc23->SelectAll();
               break;
          }
       }
    } else { // Hsc_DataNoIdx > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM
       if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {
          switch (Hsc_DataNoIdx - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
          case 1:
               Edt_Hsc21->SetFocus();
               Edt_Hsc21->SelectAll();
               break;
          case 2:
               Edt_Hsc22->SetFocus();
               Edt_Hsc22->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR;
               Edt_Hsc23->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx-1 - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM];
               Edt_Hsc24->Text = Hsc_DataNoIdx - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Old_Cur;
               Edt_Hsc23->SetFocus();
               Edt_Hsc23->SelectAll();
               break;
          }
       }
    }
    ScreenInitFlag = 1;
    FieldColor(Hsc_SamplePositionIdx, Hsc_DataNoIdx, 1);
    ScreenInitFlag = 0;
 } else {     // Hsd
    if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 0) {
       Edt_Hsd11->SetFocus();
       Edt_Hsd11->SelectAll();
       return;
    }
    if (Hsd_DataNoIdx <= KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
       if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
          KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) { // 圧面
          switch (Hsd_DataNoIdx) {
          case 1:
               Edt_Hsd11->SetFocus();
               Edt_Hsd11->SelectAll();
               break;
          case 2:
               Edt_Hsd12->SetFocus();
               Edt_Hsd12->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
               Edt_Hsd13->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[Hsd_DataNoIdx-1];
               Edt_Hsd14->Text = Hsd_DataNoIdx;
               KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
               Edt_Hsd13->SetFocus();
               Edt_Hsd13->SelectAll();
               break;
          }
       } else { // 側面
          switch (Hsd_DataNoIdx) {
          case 1:
               Edt_Hsd21->SetFocus();
               Edt_Hsd21->SelectAll();
               break;
          case 2:
               Edt_Hsd22->SetFocus();
               Edt_Hsd22->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
               Edt_Hsd23->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx-1];
               Edt_Hsd24->Text = Hsd_DataNoIdx;
               KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
               Edt_Hsd23->SetFocus();
               Edt_Hsd23->SelectAll();
               break;
          }
       }
    } else { // Hsd_DataNoIdx > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM
       if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) {
          switch (Hsd_DataNoIdx - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
          case 1:
               Edt_Hsd21->SetFocus();
               Edt_Hsd21->SelectAll();
               break;
          case 2:
               Edt_Hsd22->SetFocus();
               Edt_Hsd22->SelectAll();
               break;
          default:
               // change value
               Old_Cur = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR;
               Edt_Hsd23->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx-1 - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM];
               Edt_Hsd24->Text = Hsd_DataNoIdx - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
               KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Old_Cur;
               Edt_Hsd23->SetFocus();
               Edt_Hsd23->SelectAll();
               break;
          }
       }
    }
    ScreenInitFlag = 1;
    FieldColor(Hsd_SamplePositionIdx, Hsd_DataNoIdx, 2);
    ScreenInitFlag = 0;
 }
}

void __fastcall TForm1::edtymdEnter(TObject *Sender)
{
     ButtonInputMode(0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edtymdKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key) {
         case VK_F1:
              ExecF1();
              break;
         // F2, F3機能を追加 2000.3.11
         case VK_F2:
              if (edttlno->Focused()) {
                 edtymd->SetFocus();
                 break;
              }
              break;
         case VK_F3:
              if (edtymd->Focused())
                 edttlno->SetFocus();
              else {
                 if (Hsc_SamplePositionIdx > 0 && AreaFlag == 1) {
                    Edt_Hsc_Sample->SetFocus();
                    break;
                 }
                 if (Hsd_SamplePositionIdx > 0 && AreaFlag == 2) {
                    Edt_Hsd_Sample->SetFocus();
                    break;
                 }
              }
              break;
         // end of add
         case VK_F5:
              Button5Click(Sender);
              break;
         case VK_F7:
              Button7Click(Sender);
              break;
         case VK_F12:
              Button12Click(Sender);
              break;
         case VK_RETURN:
              if (edtymd->Focused()) {
                 edttlno->SetFocus();
                 break;
              } else {
                 if (edttlno->Focused() || CheckBoxRireki->Focused()) {
                    Button7Click(Sender);
                    break;
                 }
              }
              break;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd_SampleEnter(TObject *Sender)
{
     AreaFlag = 2;
     ButtonInputMode(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd11Enter(TObject *Sender)
{
     AreaFlag = 2;
     ButtonInputMode(1);
     if (Edt_Hsd11->Focused()) {
        Hsd_DataNoIdx = 1;
     }
     if (Edt_Hsd12->Focused()) {
        Hsd_DataNoIdx = 2;
     }
     if (Edt_Hsd13->Focused() || Edt_Hsd14->Focused() ) {
        Hsd_DataNoIdx = Edt_Hsd14->Value;
     }
     if (Edt_Hsd21->Focused()) {
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 != 3)
           Hsd_DataNoIdx = 1;
        else
           Hsd_DataNoIdx = 1 + KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
     }
     if (Edt_Hsd22->Focused()) {
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 != 3)
           Hsd_DataNoIdx = 2;
        else
           Hsd_DataNoIdx = 2 + KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
     }
     if (Edt_Hsd23->Focused() || Edt_Hsd24->Focused() ) {
        if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 != 3)
           Hsd_DataNoIdx = Edt_Hsd24->Value;
        else
           Hsd_DataNoIdx = Edt_Hsd24->Value + KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
     }
     //FieldColor(Hsd_SamplePositionIdx, Hsd_DataNoIdx, 2);
     Hsd_CurDataChg = 0;
     if (Edt_Hsd11->Focused() || Edt_Hsd12->Focused() ||
         Edt_Hsd13->Focused() || Edt_Hsd14->Focused()){
        if (Hsd_iOption == 3)
           Hsd_iOption = 1;
        if (Hsd_iOption == 4)
           Hsd_iOption = 2;
        ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
     } else {
        if (Hsd_iOption == 1)
           Hsd_iOption = 3;
        if (Hsd_iOption == 2)
           Hsd_iOption = 4;
        ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExtractCode()
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


void __fastcall TForm1::Edt_Hsc14Exit(TObject *Sender)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM >= 3) {

      n = Edt_Hsc14->Value;

      if (n < Scr_Hsc2->Min)
         n = Scr_Hsc2->Min;
      if (n > Scr_Hsc2->Max)
         n = Scr_Hsc2->Max;
      Edt_Hsc14->Text = n;
      Hsc_DataNoIdx = n;
      Scr_Hsc2->Position = n;
      Edt_Hsc13->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc24Exit(TObject *Sender)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM >= 3) {

      n = Edt_Hsc24->Value;

      if (n < Scr_Hsc3->Min)
         n = Scr_Hsc3->Min;
      if (n > Scr_Hsc3->Max)
         n = Scr_Hsc3->Max;
      Edt_Hsc24->Text = n;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM+n;
      else
         Hsc_DataNoIdx = n;
      Scr_Hsc3->Position = n;
      Edt_Hsc23->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd14Exit(TObject *Sender)
{
   int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM >= 3) {

      n = Edt_Hsd14->Value;

      if (n < Scr_Hsd2->Min)
         n = Scr_Hsd2->Min;
      if (n > Scr_Hsd2->Max)
         n = Scr_Hsd2->Max;
      Edt_Hsd14->Text = n;
      Hsd_DataNoIdx = n;
      Scr_Hsd2->Position = n;
      Edt_Hsd13->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd24Exit(TObject *Sender)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM >= 3) {

      n = Edt_Hsd24->Value;

      if (n < Scr_Hsd3->Min)
         n = Scr_Hsd3->Min;
      if (n > Scr_Hsd3->Max)
         n = Scr_Hsd3->Max;
      Edt_Hsd24->Text = n;
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
         Hsd_DataNoIdx = KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM+n;
      else
         Hsd_DataNoIdx = n;
      Scr_Hsd3->Position = n;
      Edt_Hsd23->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc11Change(TObject *Sender)
{
// 2003/02/12 A.Tamura
// Hsc_AllDataChg = 1;
 Hsc_CurSampChg = 1;
 Hsc_CurDataChg = 1;
 if (Hsc_DataNoIdx > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR)
     KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM_CUR = Hsc_DataNoIdx;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd11Change(TObject *Sender)
{
// 2003/02/12 A.Tamura
// Hsd_AllDataChg = 1;
 Hsd_CurSampChg = 1;
 Hsd_CurDataChg = 1;
 if (Hsd_DataNoIdx > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR)
     KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM_CUR = Hsd_DataNoIdx;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsc11Exit(TObject *Sender)
{

 if (Hsc_CurDataChg == 1) {
    Hsc_CurDataChg = 0;
    if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 != 0) {
       switch(Hsc_DataNoIdx) {
       case 1:
            if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2) {
               // 2003/02/12 A.Tamura
               // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] != Edt_Hsc21->Value ) Hsc_AllDataChg = 1;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] = Edt_Hsc21->Value;
            } else {
               // 2003/02/12 A.Tamura
               // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] != Edt_Hsc11->Value ) Hsc_AllDataChg = 1;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] = Edt_Hsc11->Value;
            }
            break;
       case 2:
            if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2) {
               // 2003/02/12 A.Tamura
               // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] != Edt_Hsc22->Value ) Hsc_AllDataChg = 1;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] = Edt_Hsc22->Value;
            } else {
               // 2003/02/12 A.Tamura
               // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] != Edt_Hsc12->Value ) Hsc_AllDataChg = 1;
               KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] = Edt_Hsc12->Value;
            }
            break;
       default:
            if (Hsc_DataNoIdx > KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
               if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {
                  switch(Hsc_DataNoIdx - KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM) {
                  case 1:
                       // 2003/02/12 A.Tamura
                       // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] != Edt_Hsc21->Value ) Hsc_AllDataChg = 1;
                       KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] = Edt_Hsc21->Value;
                       break;
                  case 2:
                       // 2003/02/12 A.Tamura
                       // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] != Edt_Hsc22->Value ) Hsc_AllDataChg = 1;
                       KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] = Edt_Hsc22->Value;
                       break;
                  default:
                       // 2003/02/12 A.Tamura
                       // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] != Edt_Hsc23->Value ) Hsc_AllDataChg = 1;
                       KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1-KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM] = Edt_Hsc23->Value;
                       break;
                  }
               }
            } else { // <= KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM
               if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
                  KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3) {
                  // 2003/02/12 A.Tamura
                  // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] != Edt_Hsc13->Value ) Hsc_AllDataChg = 1;
                  KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[Hsc_DataNoIdx -1] = Edt_Hsc13->Value;
               } else {
                  // 2003/02/12 A.Tamura
                  // if( KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] != Edt_Hsc23->Value ) Hsc_AllDataChg = 1;
                  KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[Hsc_DataNoIdx -1] = Edt_Hsc23->Value;
               }
            }
            break;
       }
    }
    ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);
 }

 //if (Edt_Hsc11->Focused())
 //   Edt_Hsc11->Color = clWindow;
 //if (Edt_Hsc12->Focused())
 //   Edt_Hsc12->Color = clWindow;
 //if (Edt_Hsc13->Focused())
 //   Edt_Hsc13->Color = clWindow;
 //if (Edt_Hsc21->Focused())
 //   Edt_Hsc21->Color = clWindow;
 //if (Edt_Hsc22->Focused())
 //   Edt_Hsc22->Color = clWindow;
 //if (Edt_Hsc23->Focused())
 //   Edt_Hsc23->Color = clWindow;

 FieldColor(Hsc_SamplePositionIdx, Hsc_DataNoIdx, 1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_Hsd11Exit(TObject *Sender)
{
 if (Hsd_CurDataChg == 1) {
    Hsd_CurDataChg = 0;
    if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 != 0) {
       switch(Hsd_DataNoIdx) {
       case 1:
            if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2) {
               KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1] = Edt_Hsd21->Value;
            } else
               KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[Hsd_DataNoIdx -1] = Edt_Hsd11->Value;
            break;
       case 2:
            if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2) {
               KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1] = Edt_Hsd22->Value;
            } else
               KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[Hsd_DataNoIdx -1] = Edt_Hsd12->Value;
            break;
       default:
            if (Hsd_DataNoIdx > KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
               if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3) {
                  switch(Hsd_DataNoIdx - KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM) {
                  case 1:
                       KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1-KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM] = Edt_Hsd21->Value;
                       break;
                  case 2:
                       KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1-KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM] = Edt_Hsd22->Value;
                       break;
                  default:
                       KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1-KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM] = Edt_Hsd23->Value;
                       break;
                  }
               }
            } else { // <= KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM
               if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
                  KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
                  KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[Hsd_DataNoIdx -1] = Edt_Hsd13->Value;
               else
                  KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[Hsd_DataNoIdx -1] = Edt_Hsd23->Value;
            }
            break;
       }
    }
    ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
 }
 FieldColor(Hsd_SamplePositionIdx, Hsd_DataNoIdx, 2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button111Click(TObject *Sender)
{
 int i,k;
 WriteDatabaseError = 0;

 // 2003/02/12 A.Tamura
 //if ((Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1) && (Hsc_HaveSokutei == 1 || Hsd_HaveSokutei == 1)) {
 if ( (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1 || CheckChangeData() == true)
    && (Hsc_HaveSokutei == 1 || Hsd_HaveSokutei == 1)) {

    // ステータスメッセージ
    StatBarClear(MSG_04);

    // ﾃﾞｰﾀをﾌｧｲﾙKD61、Kd62へ書き込む
    int rtn = Kd61_Update01();

    if (rtn > 0) {
       //入力ﾃﾞｰﾀを更新される場合のフラグのクリア
       // 2003/02/12 A.Tamura
       //Hsc_AllDataChg = 0;
       Hsc_CurSampChg = 0;
       Hsc_CurDataChg = 0;

       // 2003/02/12 A.Tamura
       //Hsd_AllDataChg = 0;
       Hsd_CurSampChg = 0;
       Hsd_CurDataChg = 0;

       // 保存時の確認用に測定値のバックアップを行います。
       for( i=0; i<30; i++){
          for( k=0; k<100; k++){
             Bk_HSC_A_CH[i][k] = KD61Data[i].HSC_A_CH[k];
             Bk_HSC_S_CH[i][k] = KD61Data[i].HSC_S_CH[k];
             Bk_HSD_A_CH[i][k] = KD61Data[i].HSD_A_CH[k];
             Bk_HSD_S_CH[i][k] = KD61Data[i].HSD_S_CH[k];
          }
          Bk_HSC_SK_SU[i] = KD61Data[i].HSC_SK_SU;
          Bk_HSD_SK_SU[i] = KD61Data[i].HSD_SK_SU;
       }

       // ステータスメッセージ
       StatBarClear( " ") ;
    } else { // Error
       Beep();
       StatBarClear( "データベースへ書込みエラー ") ;
       WriteDatabaseError = 1;
       NextToreiFlag = 1;
       return;
    }
 }

 if (NextToreiFlag == 1)
    NextTorei();
}
//---------------------------------------------------------------------------

// 測定値と測定規格を比較し、Fieldのいろを付ける
// A_Flag: 1: Hsc; 2: Hsd
// SampleDataIdx: A_Flagによって、Hsc_SamplePositionIdx又はHsd_SamplePositionIdx
// DataNoIdx: A_Flagによって、Hsc_DataNoIdx又はHsd_DataNoIdx
void __fastcall TForm1::FieldColor(int SampleDataIdx, int DataNoIdx, int A_Flag)
{
 EndErrorFlag = 0;

 if (KD61Data[SampleDataIdx-1].SAMPLE_P == -1 || !(A_Flag == 1 || A_Flag == 2))
    return;

 if (A_Flag == 1 && Hsc_iOption == 5) {
    Edt_Hsc11->Font->Color = clWindowText;
    Edt_Hsc12->Font->Color = clWindowText;
    Edt_Hsc13->Font->Color = clWindowText;
    Edt_Hsc21->Font->Color = clWindowText;
    Edt_Hsc22->Font->Color = clWindowText;
    Edt_Hsc23->Font->Color = clWindowText;
    return;
 }

 if (A_Flag == 2 && Hsd_iOption == 5) {
    Edt_Hsd11->Font->Color = clWindowText;
    Edt_Hsd12->Font->Color = clWindowText;
    Edt_Hsd13->Font->Color = clWindowText;
    Edt_Hsd21->Font->Color = clWindowText;
    Edt_Hsd22->Font->Color = clWindowText;
    Edt_Hsd23->Font->Color = clWindowText;
    return;
 }

 // 規格判断
 if (A_Flag == 1) { // Hsc
    if (DataNoIdx <= KD61Data[SampleDataIdx-1].HSC_SK_NUM_CUR) {
       if (DataNoIdx <= KD61Data[SampleDataIdx-1].HSC_SK_NUM) {
          switch (KD61Data[SampleDataIdx-1].SOKUTE_KBN1) {
          case 1:    // 圧面
          case 3:
               switch (DataNoIdx) {
               case 1:
                    if (KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_A_MAX) {
                       Edt_Hsc11->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc11->Font->Color = clWindowText;
                    break;
               case 2:
                    if (KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_A_MAX) {
                       Edt_Hsc12->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc12->Font->Color = clWindowText;
                    break;
               default:
                    if (KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_A_MAX) {
                       Edt_Hsc13->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc13->Font->Color = clWindowText;
                    break;
               }
               break;
          case 2:    // 側面
               switch (SampleDataIdx) {
               case 1:
                    if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                       Edt_Hsc21->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc21->Font->Color = clWindowText;
                    break;
               case 2:
                    if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                       Edt_Hsc22->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc22->Font->Color = clWindowText;
                    break;
               default:
                    if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                       Edt_Hsc23->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsc23->Font->Color = clWindowText;
                    break;
               }
               break;
          }
       } else { // DataNoIdx > KD61Data[SampleDataIdx-1].HSC_SK_NUM
          if (KD61Data[SampleDataIdx-1].SOKUTE_KBN1 == 3) {
             switch (DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM) {
             case 1:
                  if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                     Edt_Hsc21->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsc21->Font->Color = clWindowText;
                  break;
             case 2:
                  if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                     Edt_Hsc22->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsc22->Font->Color = clWindowText;
                  break;
             default:
                  if (KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSC_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSC_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSC_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSC_S_MAX) {
                     Edt_Hsc23->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsc23->Font->Color = clWindowText;
                  break;
             }
          }
       }
    }
 } else { // HSD
    if (DataNoIdx <= KD61Data[SampleDataIdx-1].HSD_SK_NUM_CUR) {
       if (DataNoIdx <= KD61Data[SampleDataIdx-1].HSD_SK_NUM) {
          switch (KD61Data[SampleDataIdx-1].SOKUTE_KBN2) {
          case 1:    // 圧面
          case 3:
               switch (DataNoIdx) {
               case 1:
                    if (KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_A_MAX) {
                       Edt_Hsd11->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd11->Font->Color = clWindowText;
                    break;
               case 2:
                    if (KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_A_MAX) {
                       Edt_Hsd12->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd12->Font->Color = clWindowText;
                    break;
               default:
                    if (KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_A_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_A_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_A_MAX) {
                       Edt_Hsd13->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd13->Font->Color = clWindowText;
                    break;
               }
               break;
          case 2:    // 側面
               switch (SampleDataIdx) {
               case 1:
                    if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                       Edt_Hsd21->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd21->Font->Color = clWindowText;
                    break;
               case 2:
                    if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                       Edt_Hsd22->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd22->Font->Color = clWindowText;
                    break;
               default:
                    if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                       KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                       Edt_Hsd23->Font->Color = clRed;
                       EndErrorFlag = 1;
                       if (ScreenInitFlag == 0)
                          Beep();
                    } else
                       Edt_Hsd23->Font->Color = clWindowText;
                    break;
               }
               break;
          }
       } else { // DataNoIdx > KD61Data[SampleDataIdx-1].HSD_SK_NUM
          if (KD61Data[SampleDataIdx-1].SOKUTE_KBN2 == 3) {
             switch (DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM) {
             case 1:
                  if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                     Edt_Hsd21->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsd21->Font->Color = clWindowText;
                  break;
             case 2:
                  if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                     Edt_Hsd22->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsd22->Font->Color = clWindowText;
                  break;
             default:
                  if (KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] < KD61Data[SampleDataIdx-1].HSD_S_MIN ||
                     KD61Data[SampleDataIdx-1].HSD_S_CH[DataNoIdx-KD61Data[SampleDataIdx-1].HSD_SK_NUM-1] > KD61Data[SampleDataIdx-1].HSD_S_MAX) {
                     Edt_Hsd23->Font->Color = clRed;
                     EndErrorFlag = 1;
                     if (ScreenInitFlag == 0)
                        Beep();
                  } else
                     Edt_Hsd23->Font->Color = clWindowText;
                  break;
             }
          }
       }
    }
 }
}

void __fastcall TForm1::PageCtl_HscChange(TObject *Sender)
{
       if (!Hsc_HaveSokutei)
          return ;

       // ステータスメッセージ
       StatBarClear( "  ");

        //測定履歴作画
       if( Form1->PageCtl_Hsc->ActivePage == Hsc_Sheet1)
          Hsc_iOption = 1 ;
       if( Form1->PageCtl_Hsc->ActivePage == Hsc_Sheet2)
          Hsc_iOption = 2;
       if( Form1->PageCtl_Hsc->ActivePage == Hsc_Sheet3)
          Hsc_iOption = 3 ;
       if( Form1->PageCtl_Hsc->ActivePage == Hsc_Sheet4)
          Hsc_iOption = 4;

       ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PageCtl_HsdChange(TObject *Sender)
{
       if (!Hsd_HaveSokutei)
          return ;

       // ステータスメッセージ
       StatBarClear( "  ");

        //測定履歴作画
       if( Form1->PageCtl_Hsd->ActivePage == Hsd_Sheet1)
          Hsd_iOption = 1 ;
       if( Form1->PageCtl_Hsd->ActivePage == Hsd_Sheet2)
          Hsd_iOption = 2;
       if( Form1->PageCtl_Hsd->ActivePage == Hsd_Sheet3)
          Hsd_iOption = 3 ;
       if( Form1->PageCtl_Hsd->ActivePage == Hsd_Sheet4)
          Hsd_iOption = 4;

       ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
 int Cur_DataNoIdx;

     if (!(AreaFlag == 1 || AreaFlag == 2))
        return;

     if (AreaFlag == 1) {   // Hsc
        Cur_DataNoIdx = Hsc_DataNoIdx;

        if ( !Hsc_HaveSokutei )
           return ;

        if (Hsc_iOption == 5 ){
           Hsc_iOption = 1 ;
        } else {
           Hsc_iOption += 1;
        }

        switch (Hsc_iOption) {
        case 1:
             //測定履歴作画 (圧面）
             Form1->PageCtl_Hsc->Visible = true ;
             Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet1;
             break;
        case 2:
             //工程能力作画 (圧面）
             Form1->PageCtl_Hsc->Visible = true ;
             Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet2;
             break;
        case 3:
             //測定履歴作画 (側面）
             Form1->PageCtl_Hsc->Visible = true ;
             Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet3;
             break;
        case 4:
             //工程能力作画 (側面）
             Form1->PageCtl_Hsc->Visible = true ;
             Form1->PageCtl_Hsc->ActivePage = Form1->Hsc_Sheet4;
             break;
        case 5:
             //作画領域をクリア
             Form1->PageCtl_Hsc->Visible = false ;
             break;
        }

        SetAreaInfo(1, 0);
        //履歴作画と工程能力図
        ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);

        Hsc_DataNoIdx = Cur_DataNoIdx;
        SetFieldFocus();
     } else { // Hsd
        Cur_DataNoIdx = Hsd_DataNoIdx;

        if ( !Hsd_HaveSokutei )
           return ;

        if (Hsd_iOption == 5 ){
           Hsd_iOption = 1 ;
        } else {
           Hsd_iOption += 1;
        }

        switch (Hsd_iOption) {
        case 1:
             //測定履歴作画 (圧面）
             Form1->PageCtl_Hsd->Visible = true ;
             Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet1;
             break;
        case 2:
             //工程能力作画 (圧面）
             Form1->PageCtl_Hsd->Visible = true ;
             Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet2;
             break;
        case 3:
             //測定履歴作画 (側面）
             Form1->PageCtl_Hsd->Visible = true ;
             Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet3;
             break;
        case 4:
             //工程能力作画 (側面）
             Form1->PageCtl_Hsd->Visible = true ;
             Form1->PageCtl_Hsd->ActivePage = Form1->Hsd_Sheet4;
             break;
        case 5:
             //作画領域をクリア
             Form1->PageCtl_Hsd->Visible = false ;
             break;
        }

        SetAreaInfo(2, 0);
        //履歴作画と工程能力図
        ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
        Hsd_DataNoIdx = Cur_DataNoIdx;
        SetFieldFocus();
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsc11Change(TObject *Sender)
{
 int Increase;

   if (Hsc_CurSampChg == 1) {
      AddKd63W(1);
      Hsc_CurSampChg = 0;
   }

   // マウスでScrollBarを変更する場合
   if (Hsc_SamplePositionIdx > 0 && Hsc_SamplePositionIdx >= Sample_P_Min &&
       Hsc_SamplePositionIdx <= Sample_P_Max) {

//      if (Scr_Hsc1->Position == Hsc_SamplePositionIdx)
//         return;

      // 有効Sampleを探す
      if (Scr_Hsc1->Position > Hsc_SamplePositionIdx)
         Increase = 1;
      else
         Increase = 0;
      Hsc_SamplePositionIdx = Scr_Hsc1->Position;

//      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
//         while (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
      if (KD61Data[Hsc_SamplePositionIdx-1].SAMPLE_P == -1) {
         while (KD61Data[Hsc_SamplePositionIdx-1].SAMPLE_P == -1) {

            if (Increase == 1) {
               Hsc_SamplePositionIdx++;
               if (Hsc_SamplePositionIdx > 30)
                  Hsc_SamplePositionIdx = 1;
            } else {
               Hsc_SamplePositionIdx--;
               if (Hsc_SamplePositionIdx <= 0)
                  Hsc_SamplePositionIdx = 30;
            }
         }
      }

      Edt_Hsc_Sample->Text = Hsc_SamplePositionIdx;

      Hsc_DataNoIdx = 0;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;

      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;

      SetAreaInfo(1, 1);
   }

   ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Scr_Hsc1Click(TObject *Sender, TUDBtnType Button)
{
 int Increase;

 int pos =Scr_Hsc1->Position ;

   if (Hsc_CurSampChg == 1) {
      Edt_Hsc11Exit(Sender);
      AddKd63W(1);
      Hsc_CurSampChg = 0;
   }

   // マウスでScrollBarを変更する場合
   if (Hsc_SamplePositionIdx > 0 && Hsc_SamplePositionIdx >= Sample_P_Min &&
       Hsc_SamplePositionIdx <= Sample_P_Max) {

//      if (Scr_Hsc1->Position == Hsc_SamplePositionIdx)
//         return;

      // 有効Sampleを探す
      if (Scr_Hsc1->Position > Hsc_SamplePositionIdx)
         Increase = 1;
      else
         Increase = 0;
      Hsc_SamplePositionIdx = Scr_Hsc1->Position;

//      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
//         while (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 <= 0) {
      if (KD61Data[Hsc_SamplePositionIdx-1].SAMPLE_P == -1) {
         while (KD61Data[Hsc_SamplePositionIdx-1].SAMPLE_P == -1) {

            if (Increase == 1) {
               Hsc_SamplePositionIdx++;
               if (Hsc_SamplePositionIdx > Sample_P_Max)
                  Hsc_SamplePositionIdx = Sample_P_Min;
               Scr_Hsc1->Position = Hsc_SamplePositionIdx;
            } else {
               Hsc_SamplePositionIdx--;
               if (Hsc_SamplePositionIdx < Sample_P_Min)
                  Hsc_SamplePositionIdx = Sample_P_Max;
               Scr_Hsc1->Position = Hsc_SamplePositionIdx;
            }
         }
      }

      Edt_Hsc_Sample->Text = Hsc_SamplePositionIdx;

      Hsc_DataNoIdx = 0;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 1 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;

      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 2 ||
          KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 == 3)
         Hsc_DataNoIdx = 1;

      ScreenInitFlag = 1;
      SetAreaInfo(1, 1);
      ScreenInitFlag = 0;
   }

   ToDrawGraph(Hsc_SamplePositionIdx, Hsc_iOption, 1);
   //備考をヒントにセット 2002/11/08 E.Takase
   SetMEMO();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsd1Click(TObject *Sender, TUDBtnType Button)
{
 int Increase;

   if (Hsd_CurSampChg == 1) {
      Edt_Hsd11Exit(Sender);
      AddKd63W(2);
      Hsd_CurSampChg = 0;
   }

   // マウスでScrollBarを変更する場合
   if (Hsd_SamplePositionIdx > 0 && Hsd_SamplePositionIdx >= Sample_P_Min &&
       Hsd_SamplePositionIdx <= Sample_P_Max) {

      if (Scr_Hsd1->Position == Hsd_SamplePositionIdx)
         return;

      // 有効Sampleを探す
      if (Scr_Hsd1->Position > Hsd_SamplePositionIdx)
         Increase = 1;
      else
         Increase = 0;

      Hsd_SamplePositionIdx = Scr_Hsd1->Position;

//      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 <= 0) {
//         while (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 <= 0) {
      if (KD61Data[Hsd_SamplePositionIdx-1].SAMPLE_P == -1) {
         while (KD61Data[Hsd_SamplePositionIdx-1].SAMPLE_P == -1) {

            if (Increase == 1) {
               Hsd_SamplePositionIdx++;
               if (Hsd_SamplePositionIdx > Sample_P_Max)
                  Hsd_SamplePositionIdx = Sample_P_Min;
               Scr_Hsd1->Position = Hsd_SamplePositionIdx;
            } else {
               Hsd_SamplePositionIdx--;
               if (Hsd_SamplePositionIdx < Sample_P_Min)
                  Hsd_SamplePositionIdx = Sample_P_Max;
               Scr_Hsd1->Position = Hsd_SamplePositionIdx;
            }
         }
      }

      Edt_Hsd_Sample->Text = Hsd_SamplePositionIdx;
      Hsd_DataNoIdx = 0;

      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 1 ||
          KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
         Hsd_DataNoIdx = 1;

      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 2 ||
          KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 == 3)
         Hsd_DataNoIdx = 1;

      ScreenInitFlag = 1;
      SetAreaInfo(2, 1);
      ScreenInitFlag = 0;
   }

   ToDrawGraph(Hsd_SamplePositionIdx, Hsd_iOption, 2);
   //備考をヒントにセット 2002/11/08 E.Takase
   SetMEMO();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsc2Click(TObject *Sender, TUDBtnType Button)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM >= 3) {

      if (Hsc_CurSampChg == 1) {
         Edt_Hsc11Exit(Sender);
         AddKd63W(1);
         Hsc_CurSampChg = 0;
      }
      n = Scr_Hsc2->Position;

      if (n < Scr_Hsc2->Min)
         n = Scr_Hsc2->Min;
      if (n > Scr_Hsc2->Max)
         n = Scr_Hsc2->Max;
      Edt_Hsc14->Text = n;
      Hsc_DataNoIdx = n;
      Edt_Hsc13->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_A_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsc3Click(TObject *Sender, TUDBtnType Button)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM >= 3) {

      if (Hsc_CurSampChg == 1) {
         Edt_Hsc11Exit(Sender);
         AddKd63W(1);
         Hsc_CurSampChg = 0;
      }
      n = Scr_Hsc3->Position;

      if (n < Scr_Hsc3->Min)
         n = Scr_Hsc3->Min;
      if (n > Scr_Hsc3->Max)
         n = Scr_Hsc3->Max;
      Edt_Hsc24->Text = n;
      if (KD61Data[Hsc_SamplePositionIdx-1].SOKUTE_KBN1 != 3)
         Hsc_DataNoIdx = n;
      else
         Hsc_DataNoIdx = n + KD61Data[Hsc_SamplePositionIdx-1].HSC_SK_NUM;
      Edt_Hsc23->Text = KD61Data[Hsc_SamplePositionIdx-1].HSC_S_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsd2Click(TObject *Sender, TUDBtnType Button)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM >= 3) {

      if (Hsd_CurSampChg == 1) {
         Edt_Hsd11Exit(Sender);
         AddKd63W(2);
         Hsd_CurSampChg = 0;
      }
      n = Scr_Hsd2->Position;

      if (n < Scr_Hsd2->Min)
         n = Scr_Hsd2->Min;
      if (n > Scr_Hsd2->Max)
         n = Scr_Hsd2->Max;
      Edt_Hsd14->Text = n;
      Hsd_DataNoIdx = n;
      Edt_Hsd13->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_A_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Scr_Hsd3Click(TObject *Sender, TUDBtnType Button)
{
 int n;

   // マウスでScrollBarを変更する場合
   if (KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM >= 3) {

      if (Hsd_CurSampChg == 1) {
         Edt_Hsd11Exit(Sender);
         AddKd63W(2);
         Hsd_CurSampChg = 0;
      }
      n = Scr_Hsd3->Position;

      if (n < Scr_Hsd3->Min)
         n = Scr_Hsd3->Min;
      if (n > Scr_Hsd3->Max)
         n = Scr_Hsd3->Max;
      Edt_Hsd24->Text = n;
      if (KD61Data[Hsd_SamplePositionIdx-1].SOKUTE_KBN2 != 3)
         Hsd_DataNoIdx = n;
      else
         Hsd_DataNoIdx = n + KD61Data[Hsd_SamplePositionIdx-1].HSD_SK_NUM;
      Edt_Hsd23->Text = KD61Data[Hsd_SamplePositionIdx-1].HSD_S_CH[n-1];
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NextTorei()
{
    int n,i, iPos;
    AnsiString strVal01;
    AnsiString strVal02;
    AnsiString strVal03;
    AnsiString sBuf ;            // ワーク変数

    // 現在トレイ番号を取る
    n = StrToFloat(Form1->edttlno->Text);
    Form1->edttlno->Text = n+1;

    //検査値のの取得
    strVal01 = Form1->edtymd->Text;
    // 日付(YYYY/MM/DD)から(YYYYMMDD)へ変換
    while ((iPos = strVal01.AnsiPos("/")) != 0) {
       strVal01.Delete(iPos,1);
    }
    strVal02 = Form1->edttlno->Text;

    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //ソート昇順 ,検査予定日、トレーNo
    sBuf = "SELECT *  ";
    sBuf += "FROM KD61 ";
    sBuf += "WHERE  KENSA_YMD = '" + strVal01 + "' ";
    sBuf += "AND TOLEY_NO = '" + strVal02 + "' ";
    //20170425 Y.Onishi トレーNoの最終を超えるバグを修正
    sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";
    sBuf += "ORDER BY KENSA_YMD, TOLEY_NO, SAMPLE_P";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();

    if (Form1->Query1->Eof) {// データ無し
       Form1->edttlno->Text = n;   // トレイ番号を戻す
       if (Button11->Font->Color == clRed)
          Button12->SetFocus();
       return;
    }

    // データあり
    Form1->edttlno->SetFocus();
    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);

    return;
}



void __fastcall TForm1::Button11Click(TObject *Sender)
{
 int i,k;

 WriteDatabaseError = 0;

 // 2003/02/12 A.Tamura
 //if ((Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1) && (Hsc_HaveSokutei == 1 || Hsd_HaveSokutei == 1)) {
 if ( (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1 || CheckChangeData() == true )
    && (Hsc_HaveSokutei == 1 || Hsd_HaveSokutei == 1)) {

    // ステータスメッセージ
    StatBarClear(MSG_04);

    // ﾃﾞｰﾀをﾌｧｲﾙKD61、Kd62へ書き込む
    int rtn = Kd61_Update01();

    if (rtn > 0) {
       //入力ﾃﾞｰﾀを更新される場合のフラグのクリア
       // 2003/02/12 A.Tamura
       //Hsc_AllDataChg = 0;
       Hsc_CurSampChg = 0;
       Hsc_CurDataChg = 0;

       // 2003/02/12 A.Tamura
       //Hsd_AllDataChg = 0;
       Hsd_CurSampChg = 0;
       Hsd_CurDataChg = 0;

       // 保存時の確認用に測定値のバックアップを行います。
       for( i=0; i<30; i++){
          for( k=0; k<100; k++){
             Bk_HSC_A_CH[i][k] = KD61Data[i].HSC_A_CH[k];
             Bk_HSC_S_CH[i][k] = KD61Data[i].HSC_S_CH[k];
             Bk_HSD_A_CH[i][k] = KD61Data[i].HSD_A_CH[k];
             Bk_HSD_S_CH[i][k] = KD61Data[i].HSD_S_CH[k];
          }
          Bk_HSC_SK_SU[i] = KD61Data[i].HSC_SK_SU;
          Bk_HSD_SK_SU[i] = KD61Data[i].HSD_SK_SU;
       }

       // ステータスメッセージ
       StatBarClear( " ") ;
    } else { // Error
       Beep();
       StatBarClear( "データベースへ書込みエラー ") ;
       WriteDatabaseError = 1;
       NextToreiFlag = 1;
       return;
    }
 }

 if (NextToreiFlag == 1)
    NextTorei();
 else {
     if (Button11->Font->Color == clRed)
        Button12->SetFocus();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Enter(TObject *Sender)
{
 Button11->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Exit(TObject *Sender)
{
 Button11->Font->Color = clBlack;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
 int button;
 char tempo[64];

   // 2003/02/12 A.Tamura
   // if (Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1){  // Updated ?
   if ( Hsc_AllDataChg == 1 || Hsd_AllDataChg == 1 || CheckChangeData() == true ){  // Updated ?
      button = MessageDlg( MSG_10.c_str(), mtConfirmation, mbYesNoCancel, 0);
      if (button == mrCancel){
         return;
      } else {  // YES or No
         if (button == mrNo) {
            // 2003/02/12 A.Tamura
            //Hsc_AllDataChg = 0;
            //Hsd_AllDataChg = 0;
            Close();
            return;
         } else{  // Yes
            NextToreiFlag = 0;
            Button11Click(Sender);
            if (WriteDatabaseError == 0) { // データ書込む成功
               // 2003/02/12 A.Tamura
               //Hsc_AllDataChg = 0;
               //Hsd_AllDataChg = 0;
               Close();
            }
            return ;
         }
      }
   } else {
     Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Enter(TObject *Sender)
{
 Button12->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Exit(TObject *Sender)
{
 Button12->Font->Color = clBlack;
}
//---------------------------------------------------------------------------
//備考入力画面 表示 2002/11/07 Add E.Takase
void __fastcall TForm1::Button6Click(TObject *Sender)
{

    //カソールを元に戻す
    //CurseBack();
    ExecF6();
    //備考をヒントにセット 2002/11/08 E.Takase
    if ( Form3->ModalResult == 1 ) {

        SetMEMO();
        //AllDataChg = 1;

        // 備考更新用のフラグとして用いる　2003/02/12 A.Tamura
        Hsc_AllDataChg = 1;
        Hsd_AllDataChg = 1;
    }
}

void ExecF6(void)
{
    //if( !HaveSokutei ) return ;

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

	//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
    i = Hsc_SamplePositionIdx-1;
	if (KD61Data[i].SAMPLE_P == -1) {
		Form1->Edt_Hsc11->ShowHint = false;
		Form1->Edt_Hsc12->ShowHint = false;
		Form1->Edt_Hsc13->ShowHint = false;
		Form1->Edt_Hsc14->ShowHint = false;
		Form1->Scr_Hsc2->ShowHint = false;
		Form1->Pan_Hsc5->ShowHint = false;
		Form1->Edt_Hsc21->ShowHint = false;
		Form1->Edt_Hsc22->ShowHint = false;
		Form1->Edt_Hsc23->ShowHint = false;
		Form1->Edt_Hsc24->ShowHint = false;
		Form1->Scr_Hsc3->ShowHint = false;
		Form1->Pan_Hsc6->ShowHint = false;

	} else {
	    if ( Trim(KD61Data[i].MEMO) != "" ) {
			Form1->Edt_Hsc11->Hint =  KD61Data[i].MEMO;
			Form1->Edt_Hsc12->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc13->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc14->Hint = KD61Data[i].MEMO;
			Form1->Scr_Hsc2->Hint = KD61Data[i].MEMO;
			Form1->Pan_Hsc5->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc21->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc22->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc23->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsc24->Hint = KD61Data[i].MEMO;
			Form1->Scr_Hsc3->Hint = KD61Data[i].MEMO;
			Form1->Pan_Hsc6->Hint = KD61Data[i].MEMO;

			Form1->Edt_Hsc11->ShowHint = true;
			Form1->Edt_Hsc12->ShowHint = true;
			Form1->Edt_Hsc13->ShowHint = true;
			Form1->Edt_Hsc14->ShowHint = true;
			Form1->Scr_Hsc2->ShowHint = true;
			Form1->Pan_Hsc5->ShowHint = true;
			Form1->Edt_Hsc21->ShowHint = true;
			Form1->Edt_Hsc22->ShowHint = true;
			Form1->Edt_Hsc23->ShowHint = true;
			Form1->Edt_Hsc24->ShowHint = true;
			Form1->Scr_Hsc3->ShowHint = true;
			Form1->Pan_Hsc6->ShowHint = true;

        } else {
		    Form1->Edt_Hsc11->ShowHint = false;
		    Form1->Edt_Hsc12->ShowHint = false;
		    Form1->Edt_Hsc13->ShowHint = false;
		    Form1->Edt_Hsc14->ShowHint = false;
		    Form1->Scr_Hsc2->ShowHint = false;
		    Form1->Pan_Hsc5->ShowHint = false;
		    Form1->Edt_Hsc21->ShowHint = false;
		    Form1->Edt_Hsc22->ShowHint = false;
		    Form1->Edt_Hsc23->ShowHint = false;
		    Form1->Edt_Hsc24->ShowHint = false;
		    Form1->Scr_Hsc3->ShowHint = false;
		    Form1->Pan_Hsc6->ShowHint = false;

        }

	}

    i = Hsd_SamplePositionIdx-1;
	if (KD61Data[i].SAMPLE_P != -1) {
		Form1->Edt_Hsd11->ShowHint = false;
		Form1->Edt_Hsd12->ShowHint = false;
		Form1->Edt_Hsd13->ShowHint = false;
		Form1->Edt_Hsd14->ShowHint = false;
		Form1->Scr_Hsd2->ShowHint = false;
		Form1->Pan_Hsd5->ShowHint = false;
		Form1->Edt_Hsd21->ShowHint = false;
		Form1->Edt_Hsd22->ShowHint = false;
		Form1->Edt_Hsd23->ShowHint = false;
		Form1->Edt_Hsd24->ShowHint = false;
		Form1->Scr_Hsd3->ShowHint = false;
		Form1->Pan_Hsd6->ShowHint = false;

	} else {
	    if ( Trim(KD61Data[i].MEMO) == "" ) {
			Form1->Edt_Hsd11->Hint =  KD61Data[i].MEMO;
			Form1->Edt_Hsd12->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd13->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd14->Hint = KD61Data[i].MEMO;
			Form1->Scr_Hsd2->Hint = KD61Data[i].MEMO;
			Form1->Pan_Hsd5->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd21->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd22->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd23->Hint = KD61Data[i].MEMO;
			Form1->Edt_Hsd24->Hint = KD61Data[i].MEMO;
			Form1->Scr_Hsd3->Hint = KD61Data[i].MEMO;
			Form1->Pan_Hsd6->Hint = KD61Data[i].MEMO;

			Form1->Edt_Hsd11->ShowHint = true;
			Form1->Edt_Hsd12->ShowHint = true;
			Form1->Edt_Hsd13->ShowHint = true;
			Form1->Edt_Hsd14->ShowHint = true;
			Form1->Scr_Hsd2->ShowHint = true;
			Form1->Pan_Hsd5->ShowHint = true;
			Form1->Edt_Hsd21->ShowHint = true;
			Form1->Edt_Hsd22->ShowHint = true;
			Form1->Edt_Hsd23->ShowHint = true;
			Form1->Edt_Hsd24->ShowHint = true;
			Form1->Scr_Hsd3->ShowHint = true;
			Form1->Pan_Hsd6->ShowHint = true;

        } else {
		    Form1->Edt_Hsd11->ShowHint = false;
		    Form1->Edt_Hsd12->ShowHint = false;
		    Form1->Edt_Hsd13->ShowHint = false;
		    Form1->Edt_Hsd14->ShowHint = false;
		    Form1->Scr_Hsd2->ShowHint = false;
		    Form1->Pan_Hsd5->ShowHint = false;
		    Form1->Edt_Hsd21->ShowHint = false;
		    Form1->Edt_Hsd22->ShowHint = false;
		    Form1->Edt_Hsd23->ShowHint = false;
		    Form1->Edt_Hsd24->ShowHint = false;
		    Form1->Scr_Hsd3->ShowHint = false;
		    Form1->Pan_Hsd6->ShowHint = false;

        }

	}


}
//---------------------------------------------------------------------------
// 検索時のデータと終了前のデータをチェックし、
// データが変更されているかどうかをチェックします。
bool __fastcall TForm1::CheckChangeData(void)
{
   int i,k;
   bool ret;

   ret = false;

   // 比較を行います。
   for( i=0; i<30; i++){
      for( k=0; k<100; k++){
         if( Bk_HSC_A_CH[i][k] != KD61Data[i].HSC_A_CH[k]) ret = true;
         if( Bk_HSC_S_CH[i][k] != KD61Data[i].HSC_S_CH[k]) ret = true;
         if( Bk_HSD_A_CH[i][k] != KD61Data[i].HSD_A_CH[k]) ret = true;
         if( Bk_HSD_S_CH[i][k] != KD61Data[i].HSD_S_CH[k]) ret = true;
         if( ret == true ) break;
      }
      if( Bk_HSC_SK_SU[i] != KD61Data[i].HSC_SK_SU) ret = true;
      if( Bk_HSD_SK_SU[i] != KD61Data[i].HSD_SK_SU) ret = true;
      if( ret == true ) break;
   }

   return( ret );
}
//---------------------------------------------------------------------------
//INIファイル 読み込み 工場区分取得
void __fastcall TForm1::Read_Ini()
{
     int getlen1;
     char windir[MAX_PATH];	//Windows Dir
     char CurDir[MAX_PATH];	//Current Dir
     char tempo[MAX_PATH];

     //設定ファイル　( "windows\TKSMAIN.ini" or "winnt\TKSMAIN.ini" )
     char INIname[MAX_PATH];

     // 機器番号を読込む
     GetCurrentDirectory(256,CurDir);
     sprintf(INIname, "%s\\Tks.ini", CurDir);
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);
     iKojoKbn = atoi(tempo);
     
}
//---------------------------------------------------------------------------


