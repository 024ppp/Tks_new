//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>

#pragma hdrstop


#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 *Form1;

KDA1_DATA Cur_Kda1;             // 選択したヒストグラムデータ
KDA1_DATA Tmp_Kda1;             // 選択したヒストグラムデータ

KDA2_DATA M_Kda2[1000];         // 計測データ（最大値：１０００個）
KETA_DATA KETA;  //印刷時の桁数

double E_Screen_Data[3][20];
int E_Scale;

int     SEQNOMAX;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
bool    DataSave;
int 	RSInputFlag;

int     KENSAKU_Mode;           //一覧検索モード

// メッセージ
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
AnsiString MSG_10 = "データを保存しますか？" ;
AnsiString MSG_11 = "RS232C接続エラーが発生しました。" ;
AnsiString MSG_12 = "測定数を減らします。よろしいですか？";

void Tmp_Kda1_SYOKI(void);

char PC12FileName[MAX_PATH];
char PC34FileName[MAX_PATH];
char StartPATH[MAX_PATH];

int KikiType;               // 機器番号PC1,2,3,4
int ShellExeFlag = 0;       // PC12Ctrl.exe 実行フラグ

int iKojoKbn = 0 ;          // 工場区分

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//「起動時」
//---------------------------------------------------------------------------
//2002/11/21 備考 追加 E.Takase
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Database1->Open();

    // グリッドの初期化
    SGr1->ColWidths[0]  =	Panel8->Width;		//	No

	SGr1->ColWidths[1]  =	Panel10->Width;		//	得意先コード
	SGr1->ColWidths[2]  =	Panel19->Width;		//	得意先品番
	SGr1->ColWidths[3]  =	Panel12->Width;		//	ロットNO
	SGr1->ColWidths[4]  =	Panel18->Width;		//	自社品番

	SGr1->ColWidths[5]  =	Panel13->Width;		//	ヒストグラム測定数

	SGr1->ColWidths[6]  =	Panel22->Width;		//	　〃　　　　規格
	SGr1->ColWidths[7]  =	Panel14->Width;		//	　〃　　　　下限規格
	SGr1->ColWidths[8]  =	Panel15->Width;		//	　〃　　　　上限規格

	SGr1->ColWidths[9]  =	Panel16->Width;		//	材質名

	SGr1->ColWidths[10]  =	Panel17->Width;		//	測定済

    //2002/11/21 備考 追加 E.Takase
	//SGr1->ColWidths[11]  =	0;		            //	検査予定日
	SGr1->ColWidths[11]  =	Panel11->Width;	    //	備考

	SGr1->ColWidths[31]  =	0;		            //	検査予定日
	SGr1->ColWidths[12]  =	0;		            //	SEQ-NO

	SGr1->ColWidths[13]  =	0;		            //	材質コード
	SGr1->ColWidths[14]  =	0;		            //	ヒストグラム規格
	SGr1->ColWidths[15]  =	0;		            //	測定数
	SGr1->ColWidths[16]  =	0;		            //	平均値
	SGr1->ColWidths[17]  =	0;		            //	ＭＩＮ
	SGr1->ColWidths[18]  =	0;		            //	ＭＡＸ
	SGr1->ColWidths[19]  =	0;		            //	Ｒ
	SGr1->ColWidths[20]  =	0;		            //	標準偏差
	SGr1->ColWidths[21]  =	0;		            //	ＣＰ
	SGr1->ColWidths[22]  =	0;		            //	ＣＰＫ
	SGr1->ColWidths[23]  =	0;		            //	Ｋ
	SGr1->ColWidths[24]  =	0;		            //	不良率
	SGr1->ColWidths[25]  =	0;		            //	登録日
	SGr1->ColWidths[26]  =	0;		            //	登録時間
	SGr1->ColWidths[27]  =	0;		            //	変更日
	SGr1->ColWidths[28]  =	0;		            //	変更時間
	SGr1->ColWidths[29]  =	0;		            //	更新者
	SGr1->ColWidths[30]  =	0;		            //	更新回数

    // ボタンの初期化
    BtnF01->Enabled = true;
    BtnF02->Enabled = false;
    BtnF03->Enabled = false;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = false;
    BtnF07->Enabled = true;
    BtnF08->Enabled = false;
    BtnF09->Enabled = false;
    BtnF10->Enabled = false;
    BtnF11->Enabled = false;
    BtnF12->Enabled = true;

    //USER_COD = 1;
    KENSAKU_Mode = 1;
    // 検査予定日の初期化
    EdtCOD->Text = FormatDateTime("yyyy/mm/dd",Date());

    //部門、担当者
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    //RS232C 読み込みフラグ
    RSInputFlag = 0;

    Read_Ini();

}
// 「Ｆ１：一覧検索」
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    //ShowMessage(IntToStr(KENSAKU_Mode));
    if ( KENSAKU_Mode != -1 ) Form2->ShowModal();

}

//---------------------------------------------------------------------------
// 「Ｆ２：前項」
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
    if(SGr1->Row > 0){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}

//---------------------------------------------------------------------------
// 「Ｆ３：次項」
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
//「Ｆ４：測定」
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
 AnsiString sBuf ;
 int i, T_No;

 bool retDLL;
 bool wReturn;
 int PassFlag;
 STARTUPINFO si;
 PROCESS_INFORMATION pi;
 char curpass[MAX_PATH];
 SHELLEXECUTEINFO sei;

     if( !BtnF04->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }
     
     //データベース保存
     BtnF11Click(Sender);

     //2002/11/21 E.Takase
     //Cur_Kda1.KENSA_YMD = SGr1->Cells[11][SGr1->Row];
     Cur_Kda1.KENSA_YMD = SGr1->Cells[31][SGr1->Row];
     Cur_Kda1.SEQNO = StrToInt(SGr1->Cells[12][SGr1->Row]);
     Cur_Kda1.No = SGr1->Row+1;

     // Read Data Base (Kda2)
     //データベース Query 初期化
     Query_Kda1->Close();
     Query_Kda1->SQL->Clear();

     //問い合せ文実行
     //検査予定日、トレーNo
     sBuf = "SELECT ";
     sBuf += "* ";
     sBuf += "FROM KDA1 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kda1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kda1.SEQNO + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_工場区分追加

     Query_Kda1->SQL->Add(sBuf);
     Query_Kda1->Open();
     Query_Kda1->Active = true;

     if ( Query_Kda1->RecordCount > 0 ) {
        Query_Kda1->First();
        if ( Query_Kda1->FieldValues["DTKSCOD"].IsNull())
           Cur_Kda1.DTKSCOD = " ";
        else
           Cur_Kda1.DTKSCOD = Query_Kda1->FieldValues["DTKSCOD"];

        if ( Query_Kda1->FieldValues["DTKSHIN"].IsNull())
           Cur_Kda1.DTKSHIN = " ";
        else
           Cur_Kda1.DTKSHIN = Query_Kda1->FieldValues["DTKSHIN"];

        if ( Query_Kda1->FieldValues["LOTNO"].IsNull())
           Cur_Kda1.LOTNO = " ";
        else
           Cur_Kda1.LOTNO = Query_Kda1->FieldValues["LOTNO"];

        if ( Query_Kda1->FieldValues["HINBAN"].IsNull())
           Cur_Kda1.HINBAN = " ";
        else
           Cur_Kda1.HINBAN = Query_Kda1->FieldValues["HINBAN"];

        if ( Query_Kda1->FieldValues["ZISCOD"].IsNull())
           Cur_Kda1.ZISCOD = " ";
        else
           Cur_Kda1.ZISCOD = Query_Kda1->FieldValues["ZISCOD"];

        if ( Query_Kda1->FieldValues["ZISNAM"].IsNull())
           Cur_Kda1.ZISNAM = " ";
        else
           Cur_Kda1.ZISNAM = Query_Kda1->FieldValues["ZISNAM"];

        if ( Query_Kda1->FieldValues["HIST_SOKUT"].IsNull())
           Cur_Kda1.HIST_SOKUT = 0;
        else
           Cur_Kda1.HIST_SOKUT = Query_Kda1->FieldValues["HIST_SOKUT"];
        Cur_Kda1.HIST_SOKUT_Ori = Cur_Kda1.HIST_SOKUT;

        if ( Query_Kda1->FieldValues["SOKUTE_KET"].IsNull())
           Cur_Kda1.SOKUTE_KET = 3;                                    //onishi
        else
           Cur_Kda1.SOKUTE_KET = Query_Kda1->FieldValues["SOKUTE_KET"];

        if ( Query_Kda1->FieldValues["HIST_KIKAK"].IsNull())
           Cur_Kda1.HIST_KIKAK = 0;
        else
           Cur_Kda1.HIST_KIKAK = Query_Kda1->FieldValues["HIST_KIKAK"];

        if ( Query_Kda1->FieldValues["HIST_MIN"].IsNull())
           Cur_Kda1.HIST_MIN = 0;
        else
           Cur_Kda1.HIST_MIN = Query_Kda1->FieldValues["HIST_MIN"];

        if ( Query_Kda1->FieldValues["HIST_MAX"].IsNull())
           Cur_Kda1.HIST_MAX = 0;
        else
           Cur_Kda1.HIST_MAX = Query_Kda1->FieldValues["HIST_MAX"];

        if ( Query_Kda1->FieldValues["SOKUTE_SU"].IsNull())
           Cur_Kda1.SOKUTE_SU = 0;
        else
           Cur_Kda1.SOKUTE_SU = Query_Kda1->FieldValues["SOKUTE_SU"];
        Cur_Kda1.SOKUTE_SU_Ori = Cur_Kda1.SOKUTE_SU;

        if ( Query_Kda1->FieldValues["SOKUTE_AVE"].IsNull())
           Cur_Kda1.SOKUTE_AVE = 0;
        else
           Cur_Kda1.SOKUTE_AVE = Query_Kda1->FieldValues["SOKUTE_AVE"];

        if ( Query_Kda1->FieldValues["SOKUTE_MIN"].IsNull())
           Cur_Kda1.SOKUTE_MIN = 0;
        else
           Cur_Kda1.SOKUTE_MIN = Query_Kda1->FieldValues["SOKUTE_MIN"];

        if ( Query_Kda1->FieldValues["SOKUTE_MAX"].IsNull())
           Cur_Kda1.SOKUTE_MAX = 0;
        else
           Cur_Kda1.SOKUTE_MAX = Query_Kda1->FieldValues["SOKUTE_MAX"];

        if ( Query_Kda1->FieldValues["SOKUTE_R"].IsNull())
           Cur_Kda1.SOKUTE_R = 0;
        else
           Cur_Kda1.SOKUTE_R = Query_Kda1->FieldValues["SOKUTE_R"];

        if ( Query_Kda1->FieldValues["SOKUTE_SGM"].IsNull())
           Cur_Kda1.SOKUTE_SGM = 0;
        else
           Cur_Kda1.SOKUTE_SGM = Query_Kda1->FieldValues["SOKUTE_SGM"];

        if ( Query_Kda1->FieldValues["SOKUTE_CP"].IsNull())
           Cur_Kda1.SOKUTE_CP = 0;
        else
           Cur_Kda1.SOKUTE_CP = Query_Kda1->FieldValues["SOKUTE_CP"];

        if ( Query_Kda1->FieldValues["SOKUTE_CPK"].IsNull())
           Cur_Kda1.SOKUTE_CPK = 0;
        else
           Cur_Kda1.SOKUTE_CPK = Query_Kda1->FieldValues["SOKUTE_CPK"];

        if ( Query_Kda1->FieldValues["SOKUTE_K"].IsNull())
           Cur_Kda1.SOKUTE_K = 0;
        else
           Cur_Kda1.SOKUTE_K = Query_Kda1->FieldValues["SOKUTE_K"];

        if ( Query_Kda1->FieldValues["SOKUTE_P"].IsNull())
           Cur_Kda1.SOKUTE_P = 0;
        else
           Cur_Kda1.SOKUTE_P = Query_Kda1->FieldValues["SOKUTE_P"];

        if ( Query_Kda1->FieldValues["UPDCNT"].IsNull())
           Cur_Kda1.UPDCNT = 0;
        else
           Cur_Kda1.UPDCNT = Query_Kda1->FieldValues["UPDCNT"];

        if ( Query_Kda1->FieldValues["ADDYMD"].IsNull())
           Cur_Kda1.ADDYMD = " ";
        else
           Cur_Kda1.ADDYMD = Query_Kda1->FieldValues["ADDYMD"];


        if ( Query_Kda1->FieldValues["ADDTIM"].IsNull())
           Cur_Kda1.ADDTIM = " ";
        else
           Cur_Kda1.ADDTIM = Query_Kda1->FieldValues["ADDTIM"];

        //2002/11/21 備考追加 E.Takase
        if ( Query_Kda1->FieldValues["MEMO"].IsNull())
           Cur_Kda1.MEMO = " ";
        else
           Cur_Kda1.MEMO = Query_Kda1->FieldValues["MEMO"];

      } else {
        Query_Kda1->Close();
        return ;
      }

     Query_Kda1->Close();

     for ( i = 0; i < Nums; i++) {
        M_Kda2[i].SOKUTEI_CH = 0;
        M_Kda2[i].DatabaseFlag = 0;
     }

     // Read Data Base (Kda2)
     //データベース Query 初期化
     Query_Kda2->Close();
     Query_Kda2->SQL->Clear();

     //問い合せ文実行
     //検査予定日、トレーNo
     sBuf = "SELECT ";
     sBuf += "SOKUTEI_NO, SOKUTEI_CH ";
     sBuf += "FROM KDA2 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kda1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kda1.SEQNO + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_工場区分追加
     sBuf += "ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

     Query_Kda2->SQL->Add(sBuf);
     Query_Kda2->Open();
     Query_Kda2->Active = true;

     if ( Query_Kda2->RecordCount > 0 ) {
        Query_Kda2->First();
        while( !Query_Kda2->Eof ) {
           if ( Query_Kda2->FieldValues["SOKUTEI_NO"].IsNull()) {
              T_No = 0;
           } else {
              T_No = Query_Kda2->FieldValues["SOKUTEI_NO"];
           }

           if (T_No > 0 && T_No <= Cur_Kda1.SOKUTE_SU) {
              M_Kda2[T_No - 1].DatabaseFlag = 1;
              if ( Query_Kda2->FieldValues["SOKUTEI_CH"].IsNull())
                 M_Kda2[T_No - 1].SOKUTEI_CH = 0;
              else
                 M_Kda2[T_No - 1].SOKUTEI_CH = Query_Kda2->FieldValues["SOKUTEI_CH"];
           }
           Query_Kda2->Next();
        }
     }

     Query_Kda2->Close();

     // 測定プログラム起動する
     if (KikiType == 1 || KikiType == 2) {
        ZeroMemory( &sei, sizeof(sei) );
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//sei.hwnd = hWnd;
	sei.lpVerb = "open";
        sei.lpFile = PC12FileName;
        //sei.nShow = SW_SHOWMINIMIZED ;
        sei.nShow = SW_SHOWNOACTIVATE | SW_SHOWMINIMIZED ;
        //sei.nShow = SW_SHOWNORMAL;
        sei.lpDirectory = StartPATH;
        sei.lpParameters = "";
        while (FindWindow("WSockWClass", "TRIS ： 中間検査(PC1)") != NULL)
              Sleep(1000);
	retDLL = ShellExecuteEx(&sei);
        Sleep(2000);
        ShellExeFlag = 1;
     } else
        ShellExeFlag = 0;

     // 測定画面を開く
     Form1->Hide();
     Form3->FormScreenInit(0);
     Form3->ShowModal();

     if (ShellExeFlag == 1)
        Sleep(2000);

     // 画面の測定数を変更する
     //ヒストグラム測定数 HISUT_SOKUT
     //SGr1->Cells[5][SGr1->Row] = Cur_Kda1.HIST_SOKUT_Ori;
	 sBuf = IntToStr( Cur_Kda1.HIST_SOKUT_Ori);//	ヒストグラム測定数
	 SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     //測定数 SOKUTE_SU
     SGr1->Cells[15][SGr1->Row] = Cur_Kda1.SOKUTE_SU_Ori;

     if ( StrToInt (SGr1->Cells[5][SGr1->Row]) == StrToInt (SGr1->Cells[15][SGr1->Row])) {
        sBuf = "済";//	測定済
     } else  {
     	if (Cur_Kda1.SOKUTE_SU > 0 ) {
           sBuf = "途中";//	測定途中
        } else {
	   sBuf = "未";//	未測定
        }
     }
     SGr1->Cells[10][SGr1->Row] = sBuf;

     //備考 MEMO 2002/11/21 E.Takase
     SGr1->Cells[11][SGr1->Row] = Cur_Kda1.MEMO;
     Edt9->Text = Cur_Kda1.MEMO;


}

//---------------------------------------------------------------------------
// 「Ｆ５：画面印刷」
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{

    if( !BtnF05->Enabled )    return;
     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = MSG_09;
     SBr1->Update();

     Form1->Print();

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();
}

//---------------------------------------------------------------------------
// 「Ｆ７：検索」
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     if( !BtnF07->Enabled )    return;
     int iRow,i;
     AnsiString sBuf;
     AnsiString sYMD;

     sYMD = DelSEPA(EdtCOD->Text);
     if( sYMD == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "検査日を入力してください";
        SBr1->Update();
        KENSAKU_Mode = 1;
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     //SGr1初期化
     SGr1->RowCount = 1;
     SGr1->Cells[0][0] = "";
     SGr1->Cells[1][0] = "";
     SGr1->Cells[2][0] = "";
     SGr1->Cells[3][0] = "";
     SGr1->Cells[4][0] = "";
     SGr1->Cells[5][0] = "";
     SGr1->Cells[6][0] = "";
     SGr1->Cells[7][0] = "";
     SGr1->Cells[8][0] = "";
     SGr1->Cells[9][0] = "";
     SGr1->Cells[10][0] = "";
     SGr1->Cells[11][0] = "";
     SGr1->Cells[12][0] = "";
     SGr1->Cells[13][0] = "";
     SGr1->Cells[14][0] = "";
     SGr1->Cells[15][0] = "";
     SGr1->Cells[16][0] = "";
     SGr1->Cells[17][0] = "";
     SGr1->Cells[18][0] = "";
     SGr1->Cells[19][0] = "";
     SGr1->Cells[20][0] = "";
     SGr1->Cells[21][0] = "";
     SGr1->Cells[22][0] = "";
     SGr1->Cells[23][0] = "";
     SGr1->Cells[24][0] = "";
     SGr1->Cells[25][0] = "";
     SGr1->Cells[26][0] = "";
     SGr1->Cells[27][0] = "";
     SGr1->Cells[28][0] = "";
     SGr1->Cells[29][0] = "";
     SGr1->Cells[30][0] = "";
     SGr1->Cells[31][0] = "";

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select KENSA_YMD, SEQNO, DTKSCOD, DTKSHIN, LOTNO, HINBAN, ";
     sBuf += "ZISCOD, ZISNAM, HIST_SOKUT, HIST_KIKAK, HIST_MIN, HIST_MAX, ";
     sBuf += "SOKUTE_SU, SOKUTE_AVE, SOKUTE_MIN, SOKUTE_MAX, SOKUTE_R, ";
     sBuf += "SOKUTE_SGM, SOKUTE_CP, SOKUTE_CPK, SOKUTE_K, SOKUTE_P, ";
     sBuf += "ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, MEMO";
     sBuf += " From KDA1 ";

     sBuf += " where KENSA_YMD = '";
     sBuf += sYMD + "'";
     sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof == true ) {
     //検索結果 ０件
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = MSG_02;
        SBr1->Update();
        KENSAKU_Mode = 1;
    	// ボタンの初期化
    	BtnF01->Enabled = true;
    	BtnF02->Enabled = false;
    	BtnF03->Enabled = false;
    	BtnF04->Enabled = false;
    	BtnF05->Enabled = true;
    	BtnF06->Enabled = false;
    	BtnF07->Enabled = true;
    	BtnF08->Enabled = true;
    	BtnF09->Enabled = false;
    	BtnF10->Enabled = false;
    	BtnF11->Enabled = false;
    	BtnF12->Enabled = true;

        return;

     }
     iRow = 0;
     SEQNOMAX = 0;
     while( !Query1->Eof ){

          // グリッドの最大行数が超えていないかチェックする
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // グリッドにデータをセットします。
          sBuf = iRow + 1;//	No
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[2]->AsString;//	得意先コード
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;//	得意先品番
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;//	ロットNo
          SGr1->Cells[3][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;//	自社品番
          SGr1->Cells[4][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[8]->AsString;//	ヒストグラム測定数
          SGr1->Cells[5][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[9]->AsString;
          switch(StrToInt(sBuf))
          {
            case 1:
	        SGr1->Cells[6][iRow] = "両側";

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[10]->AsString));//	　〃　　　　下限規格
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[11]->AsString));//	　〃　　　　上限規格
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
	        SGr1->Cells[6][iRow] = "下限";

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[10]->AsString));//	　〃　　　　下限規格
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf = " ";//	　〃　　　　上限規格
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
	        SGr1->Cells[6][iRow] = "上限";

	        sBuf = " ";//	　〃　　　　下限規格
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf =FormatFloat("#0.000", StrToFloat(Query1->Fields->Fields[11]->AsString));//	　〃　　　　上限規格
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

          }

		sBuf = Query1->Fields->Fields[7]->AsString;//	材質名
		SGr1->Cells[9][iRow] = sBuf;


		if ( StrToInt (Query1->Fields->Fields[8]->AsString) == StrToInt (Query1->Fields->Fields[12]->AsString )) {
			sBuf = "済";//	測定済
		} else  {
            if (StrToInt (Query1->Fields->Fields[12]->AsString ) > 0 ) {
                sBuf = "途中";//	測定途中
            } else {
                sBuf = "未";//	未測定
            }
        }
		SGr1->Cells[10][iRow] = sBuf;

        //備考追加 2002/11/21 E.Takase
		sBuf = Query1->Fields->Fields[28]->AsString;//	備考
		SGr1->Cells[11][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[0]->AsString;//	検査予定日
		//SGr1->Cells[11][iRow] = sBuf;
		SGr1->Cells[31][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[1]->AsString;//	SEQ-NO
		SGr1->Cells[12][iRow] = sBuf;
        if ( SEQNOMAX < StrToInt(SGr1->Cells[12][iRow]))
            SEQNOMAX = StrToInt(SGr1->Cells[12][iRow]);

		sBuf = Query1->Fields->Fields[6]->AsString;//	材質コード
		SGr1->Cells[13][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[9]->AsString;//	ヒストグラム規格
		SGr1->Cells[14][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[12]->AsString;//	測定数
		SGr1->Cells[15][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[13]->AsString;//	平均値
		SGr1->Cells[16][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[14]->AsString;//	ＭＩＮ
		SGr1->Cells[17][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[15]->AsString;//	ＭＡＸ
		SGr1->Cells[18][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[16]->AsString;//	Ｒ
		SGr1->Cells[19][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[17]->AsString;//	標準偏差
		SGr1->Cells[20][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[18]->AsString;//	ＣＰ
		SGr1->Cells[21][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[19]->AsString;//	ＣＰＫ
		SGr1->Cells[22][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[20]->AsString;//	Ｋ
		SGr1->Cells[23][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[21]->AsString;//	不良率
		SGr1->Cells[24][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[22]->AsString;//	登録日
		SGr1->Cells[25][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[23]->AsString;//	登録時間
		SGr1->Cells[26][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[24]->AsString;//	変更日
		SGr1->Cells[27][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[25]->AsString;//	変更時間
		SGr1->Cells[28][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[26]->AsString;//	更新者
		SGr1->Cells[29][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[27]->AsString;//	更新回数
		SGr1->Cells[30][iRow] = sBuf;

          // カーソルを次にセットする
          Query1->Next();

          iRow += 1;
     }

     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     SGr1->SetFocus();

     // 新しいトランザクションを開始
     if( Database1->InTransaction == false ){
         Database1->StartTransaction();
         DataSave = false;
     }

     // ボタンの初期化
     BtnF01->Enabled = true;
     BtnF02->Enabled = true;
     BtnF03->Enabled = true;
     BtnF04->Enabled = true;
     BtnF05->Enabled = true;
     BtnF06->Enabled = true;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     BtnF09->Enabled = true;
     BtnF10->Enabled = true;
     BtnF11->Enabled = true;
     BtnF12->Enabled = true;

     KENSAKU_Mode = -1;

     SGr1SelectCell( Sender, 1, 0, true);
}

//---------------------------------------------------------------------------
//「Ｆ８：新規登録」
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    AnsiString sYMD;
    int i;

    if( !BtnF08->Enabled )    return;
    //if( Edt1->Text == "" ){
    //    // ステータスメッセージ
    //    SBr1->Panels->Items[0]->Text = "必須項目を入力して下さい。";
    //    SBr1->Update();
    //    return;
    //}

     sYMD = DelSEPA(EdtCOD->Text);

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
     SBr1->Update();

    //Tmp_Kda1 初期化
    Tmp_Kda1_SYOKI();

    // データをバッファに格納します。
    if ( Edt1->Text.IsEmpty() ) {
        ////ShowMessage("必須項目(得意先コード)を入力して下さい。");
        //SBr1->Panels->Items[0]->Text = "必須項目(得意先コード)を入力して下さい。";
        //SBr1->Update();
        //return;
        Edt1->Text = " ";
        Tmp_Kda1.DTKSCOD = " ";
    } else { // 得意先コード
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt1->Text = StrReplace(Edt1->Text,"'","_");
        Tmp_Kda1.DTKSCOD = Edt1->Text;
    }

    if ( Edt2->Text.IsEmpty() ) {
        //ShowMessage("必須項目(得意先品番)を入力して下さい。");
        SBr1->Panels->Items[0]->Text = "必須項目(得意先品番)を入力して下さい。";
        SBr1->Update();
        return;
    } else { // 得意先品番
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt2->Text = StrReplace(Edt2->Text,"'","_");
        Tmp_Kda1.DTKSHIN = Edt2->Text;
    }

    if ( Edt3->Text.IsEmpty() ) {
        //ShowMessage("必須項目(ロットNo)を入力して下さい。");
        //SBr1->Panels->Items[0]->Text = "必須項目(ロットNo)を入力して下さい。";
        //SBr1->Update();
        //return;
        Edt3->Text = " ";
        Tmp_Kda1.LOTNO = " ";
    } else { // ロットNo
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt3->Text = StrReplace(Edt3->Text,"'","_");
        Tmp_Kda1.LOTNO = Edt3->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("必須項目(自社品番)を入力して下さい。");
        //SBr1->Panels->Items[0]->Text = "必須項目(自社品番)を入力して下さい。";
        //SBr1->Update();
        //return;
        Edt4->Text = " ";
        Tmp_Kda1.HINBAN = " ";
    } else { // 自社品番
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt4->Text = StrReplace(Edt4->Text,"'","_");
        Tmp_Kda1.HINBAN = Edt4->Text;
    }

    if ( Edt8->Text.IsEmpty() ) {
        //ShowMessage("必須項目(材質名)を入力して下さい。");
        //SBr1->Panels->Items[0]->Text = "必須項目(材質名)を入力して下さい。";
        //SBr1->Update();
        //return;
        Edt8->Text = " ";
        Tmp_Kda1.ZISNAM = " ";
    } else { // 材質名
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt8->Text = StrReplace(Edt8->Text,"'","_");
        Tmp_Kda1.ZISNAM = Edt8->Text;
    }
    //2002/11/21 E.Takase 備考追加
    //if ( !(Edt9->Text.IsEmpty() )) // 備考
    //    Tmp_Kda1.MEMO = Edt9->Text;
    if ( !(Edt9->Text.IsEmpty() )) // 備考
        Edt9->Text = StrReplace(Edt9->Text,"'","_");
    Tmp_Kda1.MEMO = Edt9->Text;

    //Tmp_Kda1.ZISCOD;       // 材質コード 検索
    sBuf = "SELECT ZISCOD FROM KM03 WHERE KM03.ZISNAM = '";
    sBuf += Tmp_Kda1.ZISNAM + "'";
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
    if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
      //ShowMessage( "材質名が間違っています。" );
      //return;
      Tmp_Kda1.ZISCOD = " ";
    }else {
      Form1->Query1->First();
      Tmp_Kda1.ZISCOD = Form1->Query1->Fields->Fields[0]->AsString;
    }

    if ( !(Edt5->Text.IsEmpty() )) // ヒストグラム測定数
         Tmp_Kda1.HIST_SOKUT = StrToFloat(Edt5->Text);

    if ( Cmb1->ItemIndex != -1 ) // ヒストグラム規格（１，２，３）
         Tmp_Kda1.HIST_KIKAK = Cmb1->ItemIndex + 1;

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 2  )) // ヒストグラム下限規格
         Tmp_Kda1.HIST_MIN = StrToFloat(Edt6->Text);

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 3  ))// ヒストグラム上限規格
         Tmp_Kda1.HIST_MAX = StrToFloat(Edt7->Text);

    // 登録日
    Tmp_Kda1.ADDYMD = FormatDateTime("yyyymmdd",Date());
    // 登録時間
    Tmp_Kda1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // 更新回数
    Tmp_Kda1.UPDCNT  = 0;
    // 更新者
    Tmp_Kda1.UPDCHR  = USER_COD;
    // 測定日
    Tmp_Kda1.KENSA_YMD  = sYMD;
    // SEQNO
    Tmp_Kda1.SEQNO  = SEQNOMAX + 1;
    // 測定桁
    Tmp_Kda1.SOKUTE_KET = 3;                                          //onishi


     /// AddData
     if( AddData() == False ){
        return;
     }

     //// グリッドにデータをセットします。
     sBuf = SGr1->RowCount ;                            // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
		//	得意先コード
		SGr1->Cells[1][SGr1->RowCount - 1] = Tmp_Kda1.DTKSCOD;
		//	得意先品番
		SGr1->Cells[2][SGr1->RowCount - 1] = Tmp_Kda1.DTKSHIN;
		//	ロットNO
		SGr1->Cells[3][SGr1->RowCount - 1] = Tmp_Kda1.LOTNO;
		//	自社品番
		SGr1->Cells[4][SGr1->RowCount - 1] = Tmp_Kda1.HINBAN;

		sBuf = IntToStr( Tmp_Kda1.HIST_SOKUT);//	ヒストグラム測定数
		SGr1->Cells[5][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

        switch(Tmp_Kda1.HIST_KIKAK )
        {
            case 1:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "両側";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MAX);//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "下限";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = " ";//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "上限";

		        sBuf = " ";//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf =FormatFloat("#0.000", Tmp_Kda1.HIST_MAX);//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

        }

		//	材質名
		SGr1->Cells[9][SGr1->RowCount - 1] = Tmp_Kda1.ZISNAM;
		//	備考 2002/11/21 E.Takase
		SGr1->Cells[11][SGr1->RowCount - 1] = Tmp_Kda1.MEMO;
		//	検査予定日
		//SGr1->Cells[11][SGr1->RowCount - 1] = Tmp_Kda1.KENSA_YMD;
		SGr1->Cells[31][SGr1->RowCount - 1] = Tmp_Kda1.KENSA_YMD;
		//	SEQ-NO
		SGr1->Cells[12][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.SEQNO);
		//	材質コード
		SGr1->Cells[13][SGr1->RowCount - 1] = Tmp_Kda1.ZISCOD;

		if ( Tmp_Kda1.HIST_SOKUT == Tmp_Kda1.SOKUTE_SU) {
			sBuf = "済";//	測定済
		} else  {
            if (Tmp_Kda1.SOKUTE_SU > 0 ) {
                sBuf = "途中";//	測定途中
            } else {
                sBuf = "未";//	未測定
            }
        }
		SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;

		//	材質コード
		SGr1->Cells[13][SGr1->RowCount - 1] = Tmp_Kda1.ZISCOD;
		//	ヒストグラム規格
		SGr1->Cells[14][SGr1->RowCount - 1] = Tmp_Kda1.HIST_KIKAK;
		//	変更日
		SGr1->Cells[25][SGr1->RowCount - 1] = Tmp_Kda1.ADDYMD;
		//	変更時間
		SGr1->Cells[26][SGr1->RowCount - 1] = Tmp_Kda1.ADDTIM;
		//	更新者
		SGr1->Cells[29][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.UPDCHR);
		//	更新回数
		SGr1->Cells[30][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.UPDCNT);


     // 一行増やす
     SGr1->RowCount = SGr1->RowCount + 1;
     
     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // 新しい行を選択
     SGr1->Row = SGr1->RowCount - 1;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // ボタンの初期化
     BtnF01->Enabled = true;
     BtnF02->Enabled = true;
     BtnF03->Enabled = true;
     BtnF04->Enabled = true;
     BtnF05->Enabled = true;
     BtnF06->Enabled = true;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     BtnF09->Enabled = true;
     BtnF10->Enabled = true;
     BtnF11->Enabled = true;
     BtnF12->Enabled = true;
     // データを変更したフラグ
     DataSave = true;
     SEQNOMAX ++;

}

//---------------------------------------------------------------------------
//「Ｆ９：修正」
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
     AnsiString sYMD;
     AnsiString sBuf;
     if( !BtnF09->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     sYMD = DelSEPA(EdtCOD->Text);
     
    //Tmp_Kda1 初期化
    Tmp_Kda1_SYOKI();
    // データをバッファに格納します。
    //ShowMessage ("修正");
    if ( Edt1->Text.IsEmpty() ) {
        ////ShowMessage("必須項目(得意先コード)を入力して下さい。");
        //SBr1->Panels->Items[0]->Text = "必須項目(得意先コード)を入力して下さい。";
        //SBr1->Update();
        //return;
        Edt1->Text = " ";
        Tmp_Kda1.DTKSCOD = " ";

    } else { // 得意先コード
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt1->Text = StrReplace(Edt1->Text,"'","_");
        Tmp_Kda1.DTKSCOD = Edt1->Text;
    }

    if ( Edt2->Text.IsEmpty() ) {
        //ShowMessage("必須項目(得意先品番)を入力して下さい。");
        SBr1->Panels->Items[0]->Text = "必須項目(得意先品番)を入力して下さい。";
        SBr1->Update();
        return;
    } else { // 得意先品番
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt2->Text = StrReplace(Edt2->Text,"'","_");
        Tmp_Kda1.DTKSHIN = Edt2->Text;
    }

    if ( Edt3->Text.IsEmpty() ) {
        //ShowMessage("必須項目(ロットNo)を入力して下さい。");
        SBr1->Panels->Items[0]->Text = "必須項目(ロットNo)を入力して下さい。";
        SBr1->Update();
        return;
    } else { // ロットNo
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt3->Text = StrReplace(Edt3->Text,"'","_");
        Tmp_Kda1.LOTNO = Edt3->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("必須項目(自社品番)を入力して下さい。");
        SBr1->Panels->Items[0]->Text = "必須項目(自社品番)を入力して下さい。";
        SBr1->Update();
        return;
    } else { // 自社品番
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt4->Text = StrReplace(Edt4->Text,"'","_");
        Tmp_Kda1.HINBAN = Edt4->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("必須項目(材質名)を入力して下さい。");
        SBr1->Panels->Items[0]->Text = "必須項目(材質名)を入力して下さい。";
        SBr1->Update();
        return;
    } else { // 材質名
        //2002/11/22 「'」→「_」に置換 E.Takase
        Edt8->Text = StrReplace(Edt8->Text,"'","_");
        Tmp_Kda1.ZISNAM = Edt8->Text;
    }
    //Tmp_Kda1.ZISCOD;       // 材質コード 検索
    sBuf = "SELECT ZISCOD FROM KM03 WHERE KM03.ZISNAM = '";
    sBuf += Tmp_Kda1.ZISNAM + "'";
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
    if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
      //ShowMessage( "材質名が間違っています。" );
      //return;
      Tmp_Kda1.ZISCOD = " ";
    }else {
      Form1->Query1->First();
      Tmp_Kda1.ZISCOD = Form1->Query1->Fields->Fields[0]->AsString;
    }

    if ( !(Edt5->Text.IsEmpty() )) // ヒストグラム測定数
         Tmp_Kda1.HIST_SOKUT = StrToFloat(Edt5->Text);

    if ( Cmb1->ItemIndex != -1 ) // ヒストグラム規格（１，２，３）
         Tmp_Kda1.HIST_KIKAK = Cmb1->ItemIndex + 1;

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 2  )) // ヒストグラム下限規格
         Tmp_Kda1.HIST_MIN = StrToFloat(Edt6->Text);

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 3  ))// ヒストグラム上限規格
         Tmp_Kda1.HIST_MAX = StrToFloat(Edt7->Text);

    // 変更日
    Tmp_Kda1.UPDYMD = FormatDateTime("yyyymmdd",Date());
    // 変更時間
    Tmp_Kda1.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    if( SGr1->Cells[30][SGr1->Row] == "" ){
        Tmp_Kda1.UPDCNT  = 0;
    }
    else{
       Tmp_Kda1.UPDCNT  = StrToInt(SGr1->Cells[30][SGr1->Row]);
       Tmp_Kda1.UPDCNT += 1 ;                  // 更新回数
    }
    //2002/11/21 E.Takase
    //Tmp_Kda1.KENSA_YMD  = SGr1->Cells[11][SGr1->Row];
    Tmp_Kda1.KENSA_YMD  = SGr1->Cells[31][SGr1->Row];
    Tmp_Kda1.SEQNO  = StrToInt(SGr1->Cells[12][SGr1->Row]);
    //2002/11/27 E.Takase
    Tmp_Kda1.SOKUTE_SU  = StrToInt(SGr1->Cells[15][SGr1->Row]);

    //2002/11/21 E.Takase 備考追加
    if ( !(Edt9->Text.IsEmpty() )) // 備考
        Tmp_Kda1.MEMO = StrReplace(Edt9->Text,"'","_");
    Edt9->Text = Tmp_Kda1.MEMO;

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row]) == False ){
        return;
     }

     // データを変更したフラグ
     DataSave = true;

		//	得意先コード
		SGr1->Cells[1][SGr1->Row] = Tmp_Kda1.DTKSCOD;
		//	得意先品番
		SGr1->Cells[2][SGr1->Row] = Tmp_Kda1.DTKSHIN;
		//	ロットNO
		SGr1->Cells[3][SGr1->Row] = Tmp_Kda1.LOTNO;
		//	自社品番
		SGr1->Cells[4][SGr1->Row] = Tmp_Kda1.HINBAN;

		sBuf = IntToStr( Tmp_Kda1.HIST_SOKUT);//	ヒストグラム測定数
		SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

        switch(Tmp_Kda1.HIST_KIKAK )
        {
            case 1:
		        SGr1->Cells[6][SGr1->Row] = "両側";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MAX);//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
		        SGr1->Cells[6][SGr1->Row] = "下限";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = " ";//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
		        SGr1->Cells[6][SGr1->Row] = "上限";

		        sBuf = " ";//	　〃　　　　下限規格
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf =FormatFloat("#0.000", Tmp_Kda1.HIST_MAX);//	　〃　　　　上限規格
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

        }

		//	材質名
		SGr1->Cells[9][SGr1->Row] = Tmp_Kda1.ZISNAM;

		if ( Tmp_Kda1.HIST_SOKUT == Tmp_Kda1.SOKUTE_SU) {
			sBuf = "済";//	測定済
		} else  {
            if (Tmp_Kda1.SOKUTE_SU > 0 ) {
                sBuf = "途中";//	測定途中
            } else {
                sBuf = "未";//	未測定
            }
        }
		SGr1->Cells[10][SGr1->Row] = sBuf;

		//	材質コード
		SGr1->Cells[13][SGr1->Row] = Tmp_Kda1.ZISCOD;
		//	ヒストグラム規格
		SGr1->Cells[14][SGr1->Row] = Tmp_Kda1.HIST_KIKAK;
		//	変更日
		SGr1->Cells[27][SGr1->Row] = Tmp_Kda1.UPDYMD;
		//	変更時間
		SGr1->Cells[28][SGr1->Row] = Tmp_Kda1.UPDTIM;
		//	更新回数
		SGr1->Cells[30][SGr1->Row] = IntToStr(Tmp_Kda1.UPDCNT);

		//	備考 2002/11/21 E.Takase
		SGr1->Cells[11][SGr1->Row] = Tmp_Kda1.MEMO;

     SGr1->SetFocus();
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

}

//---------------------------------------------------------------------------
//「Ｆ１０：削除」
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     int i;
     AnsiString sYMD;

     if( !BtnF10->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "削除対象ではありません。";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     sYMD = DelSEPA(EdtCOD->Text);

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
     SBr1->Update();

    //Tmp_Kda1 初期化
    Tmp_Kda1_SYOKI();

    // データをバッファに格納します。
    //ShowMessage ("削除");
    //測定日
     //2002/11/21 E.Takase
     //Tmp_Kda1.KENSA_YMD  = SGr1->Cells[11][SGr1->Row];
     Tmp_Kda1.KENSA_YMD  = SGr1->Cells[31][SGr1->Row];
    //SEQNO
     Tmp_Kda1.SEQNO  = StrToInt(SGr1->Cells[12][SGr1->Row]);



     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // グリッドの一行を削除します。
         SGr1->Cells[1][i] = SGr1->Cells[1][i+1];
         SGr1->Cells[2][i] = SGr1->Cells[2][i+1];
         SGr1->Cells[3][i] = SGr1->Cells[3][i+1];
         SGr1->Cells[4][i] = SGr1->Cells[4][i+1];
         SGr1->Cells[5][i] = SGr1->Cells[5][i+1];
         SGr1->Cells[6][i] = SGr1->Cells[6][i+1];
         SGr1->Cells[7][i] = SGr1->Cells[7][i+1];
         SGr1->Cells[8][i] = SGr1->Cells[8][i+1];
         SGr1->Cells[9][i] = SGr1->Cells[9][i+1];
         SGr1->Cells[10][i] = SGr1->Cells[10][i+1];
         SGr1->Cells[11][i] = SGr1->Cells[11][i+1];
         SGr1->Cells[12][i] = SGr1->Cells[12][i+1];
         SGr1->Cells[13][i] = SGr1->Cells[13][i+1];
         SGr1->Cells[14][i] = SGr1->Cells[14][i+1];
         SGr1->Cells[15][i] = SGr1->Cells[15][i+1];
         SGr1->Cells[16][i] = SGr1->Cells[16][i+1];
         SGr1->Cells[17][i] = SGr1->Cells[17][i+1];
         SGr1->Cells[18][i] = SGr1->Cells[18][i+1];
         SGr1->Cells[19][i] = SGr1->Cells[19][i+1];
         SGr1->Cells[20][i] = SGr1->Cells[20][i+1];
         SGr1->Cells[21][i] = SGr1->Cells[21][i+1];
         SGr1->Cells[22][i] = SGr1->Cells[22][i+1];
         SGr1->Cells[23][i] = SGr1->Cells[23][i+1];
         SGr1->Cells[24][i] = SGr1->Cells[24][i+1];
         SGr1->Cells[25][i] = SGr1->Cells[25][i+1];
         SGr1->Cells[26][i] = SGr1->Cells[26][i+1];
         SGr1->Cells[27][i] = SGr1->Cells[27][i+1];
         SGr1->Cells[28][i] = SGr1->Cells[28][i+1];
         SGr1->Cells[29][i] = SGr1->Cells[29][i+1];
         SGr1->Cells[30][i] = SGr1->Cells[30][i+1];
         SGr1->Cells[31][i] = SGr1->Cells[31][i+1];
     }

     // 一行減らす
     SGr1->RowCount = SGr1->RowCount - 1;

     // 新しい行を選択
     if( SGr1->RowCount == SGr1->Row)    SGr1->Row = SGr1->Row - 1;
     else                                SGr1->Row = SGr1->Row;

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     SGr1->SetFocus();

     // データを変更したフラグ
     DataSave = true;

}

//---------------------------------------------------------------------------
//「Ｆ１１：保存」
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
     //ShowMessage ("保存");
     if( !BtnF11->Enabled )    return;
     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "保存中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // 変更，挿入，削除を永続的に保存し，現在のトランザクションを終了
     if( Database1->InTransaction == True ){
         Database1->Commit();
         // 新しいトランザクションを開始
         Database1->StartTransaction();
     }
     SGr1->SetFocus();
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = false;
}

//---------------------------------------------------------------------------
// 「Ｆ１２：終了」
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();
}

//---------------------------------------------------------------------------
//「セルが選択される前」
// 2002/11/21 備考追加 E.Takase
void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    AnsiString sBuf;

    //	No
    PnlNO->Caption = SGr1->Cells[0][ARow];

    //	得意先コード
    Edt1->Text = SGr1->Cells[1][ARow];

    //	得意先品番
    Edt2->Text = SGr1->Cells[2][ARow];
    //	ロットNO
    Edt3->Text = SGr1->Cells[3][ARow];
    //	自社品番
    Edt4->Text = SGr1->Cells[4][ARow];
    //	ヒストグラム測定数
    Edt5->Text = SGr1->Cells[5][ARow];

    //		　〃　　　　規格
    if ( Trim( SGr1->Cells[14][ARow] ) != "" )
        Cmb1->ItemIndex =StrToInt( SGr1->Cells[14][ARow]) - 1;
    else Cmb1->ItemIndex = -1;

    //	　〃　　　　下限規格
    if ( Trim( SGr1->Cells[7][ARow] ) != "" ) {
        Edt6->Enabled = true;
        Edt6->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[7][ARow]));
    }
    else {
        Edt6->Text = "";
        Edt6->Enabled = false;
    }

    //	　〃　　　　上限規格
    if ( Trim( SGr1->Cells[8][ARow] ) != "" ) {
        Edt7->Enabled = true;
        Edt7->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[8][ARow]));
    }
    else {
        Edt7->Text = "";
        Edt7->Enabled = false;
    }

    //	材質名称
    Edt8->Text = SGr1->Cells[9][ARow];

    //	備考 2002/11/21 E.Takase
    Edt9->Text = SGr1->Cells[11][ARow];

}
//---------------------------------------------------------------------------
//「フォーム KeyDown」
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     // ステータスメッセージ
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key)
     {
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
//         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  BtnF07Click(Sender);    break;
         case VK_F8:  BtnF08Click(Sender);    break;
         case VK_F9:  BtnF09Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;


         // 前項
         case VK_UP:
         case VK_LEFT:
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    //2002/11/21 E.Takase 備考追加
                    //Edt8->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == 0 && Edt2->SelLength == 0 ){
                   // KENSAKU_Mode = 2;
				   //	BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == 0 && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == 0 && Edt4->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
                    //BtnF01->Enabled = false;
					Edt3->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == 0 && Edt5->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                //if(Cmb1->Focused() && Cmb1->SelStart == 0 && Cmb1->SelLength == 0 ){
                //if(Cmb1->Focused() ){
                //    KENSAKU_Mode = -1;
                //    Edt5->SetFocus();
                //    break;
                //}
                if(Cmb1->Focused() && Cmb1->SelStart == 0 && Cmb1->SelLength == 0 && Key == VK_LEFT ){
                    Edt5->SetFocus();
                    break;
                }

                if(Edt6->Focused() && Edt6->SelStart == 0 && Edt6->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == 0 && Edt7->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1  ) {
                        Edt6->SetFocus();
                    }else { Cmb1->SetFocus(); }
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == 0 && Edt8->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    }else { Edt6->SetFocus(); }
                    break;
                }
                //2002/11/21 E.Takase 備考追加
                if(Edt9->Focused() && Edt9->SelStart == 0 && Edt9->SelLength == 0 ){
                    Edt8->SetFocus();
                    break;
                }

                break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if(Edt1->Focused() && Edt1->SelStart == Edt1->Text.Length() && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == Edt2->Text.Length() && Edt2->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == Edt3->Text.Length() && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == Edt4->Text.Length() && Edt4->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == Edt5->Text.Length() && Edt5->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                //if(Cmb1->Focused() ){
                ////if(Cmb1->Focused() && Cmb1->SelStart == Cmb1->Text.Length() && Cmb1->SelLength == 0 ){
                //    KENSAKU_Mode = -1;
                //    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 ) {
                //        Edt6->SetFocus();
                //    } else { Edt7->SetFocus(); }
                //    break;
                //}
                if(Cmb1->Focused() && Cmb1->SelStart == Cmb1->Text.Length() && Cmb1->SelLength == 0 && Key == VK_RIGHT ) {                   KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1 ) {
                        Edt6->SetFocus();
                    } else { Edt7->SetFocus(); }
                    break;
                }
                if(Edt6->Focused() && Edt6->SelStart == Edt6->Text.Length() && Edt6->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    } else { Edt8->SetFocus(); }
                    break;
                }
                //break;
                if(Edt7->Focused() && Edt7->SelStart == Edt7->Text.Length() && Edt7->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt8->SetFocus();
                    break;
                }
                //break;
                if(Edt8->Focused() && Edt8->SelStart == Edt8->Text.Length() && Edt8->SelLength == 0 ){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    //2002/11/21 E.Takase 備考追加
                    //Edt1->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                //2002/11/21 E.Takase 備考追加
                if(Edt9->Focused() && Edt9->SelStart == Edt9->Text.Length() && Edt9->SelLength == 0 ){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    BtnF07Click(Sender);
                    break;
                }
                if(Edt1->Focused()){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                if(Cmb1->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1  ) {
                        Edt6->SetFocus();
                    } else { Edt7->SetFocus(); }
                    break;
                }
                if(Edt6->Focused()){
					//BtnF01->Enabled = false;
                    //KENSAKU_Mode = -1;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    }else { Edt8->SetFocus(); }
                    break;
                }
                if(Edt7->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused()){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    //2002/11/21 E.Takase 備考追加
                    //Edt1->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                //2002/11/21 E.Takase 備考追加
                if(Edt9->Focused()){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                break;

     }

}

//---------------------------------------------------------------------------
//SGr1KeyPress
void __fastcall TForm1::SGr1KeyPress(TObject *Sender, char &Key)
{
     switch(Key)
     {
         // 前項
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT: BtnF03Click(Sender);    break;

         // Enter
         case VK_RETURN:Edt1->SetFocus();
                        KENSAKU_Mode = 2;
                        BtnF01->Enabled = true;      break;
     }

}

//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
// データを追加します。
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     // 問合せ文作成
     sBuf = "select KENSA_YMD from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "既に登録されています。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     //2002/11/21 E.Takase 備考追加
     sBuf = "insert into KDA1(";
     sBuf += " KENSA_YMD,SEQNO,DTKSCOD,DTKSHIN,LOTNO,HINBAN,";
     sBuf += "ZISCOD,ZISNAM,HIST_SOKUT,HIST_KIKAK,HIST_MIN,";
     //sBuf += "HIST_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,SOKUTE_KET )";
     sBuf += "HIST_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,SOKUTE_KET,MEMO, KOJOKBN )";  //20160701_工場区分追加

     sBuf += " values('";
	 sBuf += Tmp_Kda1.KENSA_YMD				    + "',";		// 検査予定年月日
	 sBuf += IntToStr(Tmp_Kda1.SEQNO)		    + ",'";		// SEQ-NO
	 sBuf += Tmp_Kda1.DTKSCOD				    + "','";	// 得意先コード
	 sBuf += Tmp_Kda1.DTKSHIN				    + "','";    // 得意先品番
	 sBuf += Tmp_Kda1.LOTNO					    + "','";	// ロットNo
	 sBuf += Tmp_Kda1.HINBAN					+ "','";	// 自社品番
	 sBuf += Tmp_Kda1.ZISCOD					+ "','";    // 材質コード
	 sBuf += Tmp_Kda1.ZISNAM					+ "',";     // 材質名
	 sBuf += IntToStr(Tmp_Kda1.HIST_SOKUT)	    + ",";      // ヒストグラム測定数
	 sBuf += IntToStr(Tmp_Kda1.HIST_KIKAK)	    + ",";      // ヒストグラム規格（１，２，３)
	 sBuf += FloatToStr(Tmp_Kda1.HIST_MIN)	    + ",";      // ヒストグラム下限規格
	 sBuf += FloatToStr(Tmp_Kda1.HIST_MAX)	    + ",'";     // ヒストグラム上限規格
	 sBuf += Tmp_Kda1.ADDYMD					+ "','";    // 登録日
	 sBuf += Tmp_Kda1.ADDTIM					+ "','";    // 登録時間
	 sBuf += IntToStr(Tmp_Kda1.UPDCHR)		   	+ "',";     // 更新者
	 sBuf += IntToStr(Tmp_Kda1.UPDCNT)			+ ",";      // 更新回数
	 sBuf += IntToStr(Tmp_Kda1.SOKUTE_KET)		+ ",'";     // 測定桁数
	 sBuf += Tmp_Kda1.MEMO  		            + "',";      // 備考
         sBuf += IntToStr(iKojoKbn)  		            + " ";      // 20160701_工場区分追加
     sBuf += ")";
     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// データを修正します。
//2002/11/21 E.Takase 備考追加
bool __fastcall TForm1::CollectData(String OldKey)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     //2002/11/21 E.Takase 備考追加
     sBuf = "update KDA1 set ";
     sBuf = sBuf + "DTKSCOD='"    + Tmp_Kda1.DTKSCOD      + "', "; // 得意先コード
     sBuf = sBuf + "DTKSHIN='"    + Tmp_Kda1.DTKSHIN      + "', "; // 得意先品番
     sBuf = sBuf + "LOTNO='"      + Tmp_Kda1.LOTNO        + "', "; // ロットNo
     sBuf = sBuf + "HINBAN='"     + Tmp_Kda1.HINBAN       + "', "; // 自社品番
     sBuf = sBuf + "ZISNAM='"     + Tmp_Kda1.ZISNAM       + "', "; // 材質名
     sBuf = sBuf + "ZISCOD='"     + Tmp_Kda1.ZISCOD       + "', "; // 材質コード 検索
     sBuf = sBuf + "HIST_SOKUT="  + Tmp_Kda1.HIST_SOKUT   + ", ";  // ヒストグラム測定数
     sBuf = sBuf + "HIST_KIKAK="  + Tmp_Kda1.HIST_KIKAK   + ", ";  // ヒストグラム規格（１，２，３）
     sBuf = sBuf + "HIST_MIN="    + Tmp_Kda1.HIST_MIN     + ", ";  // ヒストグラム下限規格
     sBuf = sBuf + "HIST_MAX="    + Tmp_Kda1.HIST_MAX     + ", ";  // ヒストグラム上限規格
     sBuf = sBuf + "UPDYMD='"     + Tmp_Kda1.UPDYMD       + "', "; // 変更日
     sBuf = sBuf + "UPDTIM='"     + Tmp_Kda1.UPDTIM       + "', "; // 変更時間
     sBuf = sBuf + "UPDCNT='"     + Tmp_Kda1.UPDCNT       + "', "; // 更新回数
     sBuf = sBuf + "MEMO='"       + Tmp_Kda1.MEMO         + "' ";   // 備考
     sBuf = sBuf + "where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";
     sBuf = sBuf + "AND SEQNO=" + Tmp_Kda1.SEQNO + "";
     sBuf = sBuf + " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// データを削除します。
bool __fastcall TForm1::DelData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();


     // 問合せ文作成
     sBuf = "select KENSA_YMD from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "該当のデータが見つかりません。削除できませんでした。";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }



     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "delete from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     //KDA2
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "delete from KDA2 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // 測定日
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    // データを変更したかどうかのフラグチェック
    if( DataSave ){
        switch( MessageDlg( "データが編集されています。\n保存しますか？",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
                if( Database1->InTransaction == True )  Database1->Commit();
                break;
            // 「No」       変更を破棄
            case mrNo:
                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
                break;
        }
    }
    else{
        if( Database1->InTransaction == True )  Database1->Commit();
    }
    
}


//---------------------------------------------------------------------------
//「Ｃｍｂ１ 変更」
void __fastcall TForm1::Cmb1Change(TObject *Sender)
{
    switch( Cmb1->ItemIndex){
        case 0: //0 両側
            Edt6->Enabled = true;
            Edt7->Enabled = true;
            break;
        case 1: //0 下限
            Edt6->Enabled = true;
            Edt7->Text = "0";
            Edt7->Enabled = false;
            break;
        case 2: //0 上限
            Edt6->Text = "0";
            Edt6->Enabled = false;
            Edt7->Enabled = true;
            break;
    }
}
//---------------------------------------------------------------------------
void Tmp_Kda1_SYOKI(void)
{
	Tmp_Kda1.No = 0;				// 選択番号
	Tmp_Kda1.KENSA_YMD = "";		// 検査予定年月日
	Tmp_Kda1.SEQNO = 0;				// SEQ-NO
	Tmp_Kda1.DTKSCOD = "";			// 得意先コード
	Tmp_Kda1.DTKSHIN = "";      	// 得意先品番
	Tmp_Kda1.LOTNO = "";			// ロットNo
	Tmp_Kda1.HINBAN = "";			// 自社品番
	Tmp_Kda1.ZISCOD = "";       	// 材質コード
	Tmp_Kda1.ZISNAM = "";       	// 材質名
	Tmp_Kda1.HIST_SOKUT_Ori = 0;    // ヒストグラム測定数(Origal)
	Tmp_Kda1.HIST_SOKUT = 0;        // ヒストグラム測定数
	Tmp_Kda1.HIST_KIKAK = 0;        // ヒストグラム規格（１，２，３）
	Tmp_Kda1.HIST_MIN = 0.0;        // ヒストグラム下限規格
	Tmp_Kda1.HIST_MAX = 0.0;        // ヒストグラム上限規格
	Tmp_Kda1.SOKUTE_SU = 0;         // 測定数
	Tmp_Kda1.SOKUTE_AVE = 0.0;      // 平均値
	Tmp_Kda1.SOKUTE_MIN = 0.0;      // 最小値
	Tmp_Kda1.SOKUTE_MAX = 0.0;      // 最大値
	Tmp_Kda1.SOKUTE_R = 0.0;        // R
	Tmp_Kda1.SOKUTE_SGM = 0.0;      // 標準偏差σ
	Tmp_Kda1.SOKUTE_CP = 0.0;       // CP
	Tmp_Kda1.SOKUTE_CPK = 0.0;      // CPK
	Tmp_Kda1.SOKUTE_K = 0.0;        // K
	Tmp_Kda1.SOKUTE_P = 0.0;        // 不良率
	Tmp_Kda1.ADDYMD = "";       	// 登録日
	Tmp_Kda1.ADDTIM = "";       	// 登録時間
	Tmp_Kda1.UPDYMD = "";       	// 変更日
	Tmp_Kda1.UPDTIM = "";       	// 変更時間
	Tmp_Kda1.UPDCHR = 0;            // 更新者
	Tmp_Kda1.UPDCNT = 0;            // 更新回数
	Tmp_Kda1.MEMO = "";             // 備考
}


//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtCOD->Focused() ){
        KENSAKU_Mode = 1;
        BtnF01->Enabled = true;
        return;
    }
    if(Edt1->Focused() ){
        KENSAKU_Mode = 2;
        BtnF01->Enabled = true;
        return;
    }
    if(Edt2->Focused() ){
        KENSAKU_Mode = 3;
        BtnF01->Enabled = true;
        return;
    }

    KENSAKU_Mode = -1;
    BtnF01->Enabled = false;

}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::DelSEPA(AnsiString sYMD)
{
    int         iPos;
    AnsiString  sRet;

    sRet = sYMD;
    while( (iPos = sRet.AnsiPos("/")) != 0){
        sRet.Delete(iPos,1);
    }

    return( sRet );
}


//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::InsSEPA(AnsiString sYMD)
{
    AnsiString  sRet;

    sRet = sYMD;
    sRet.Insert("/",5);
    sRet.Insert("/",8);

    return( sRet );
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

    //部門、担当者
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    //部門、担当者
    Form3->Panel3->Caption = BUMO_COD;
    Form3->Panel4->Caption = BUMO_NAM;
    Form3->Panel6->Caption = IntToStr(USER_COD);
    Form3->Panel7->Caption = USER_NAM;


}
void __fastcall TForm1::EdtKeyPress(TObject *Sender, char &Key)
{
    //ビープ音ならさないようにする
    switch(Key){
        // リターン
        case VK_RETURN:
            Key = 0;
            break;
    }

}
//---------------------------------------------------------------------------

//INIファイル 読み込み プログラム名取得
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
     GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, INIname);
     KikiType = atoi(tempo);
     if (KikiType <= 0 || KikiType > 4)
        KikiType = 1;

     // 工場区分を読み込む
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);
     iKojoKbn = atoi(tempo);

     /*Windowsﾃﾞｨﾚｸﾄﾘを検出*/
     getlen1 = GetWindowsDirectory((LPSTR)windir, sizeof(windir));
     if (getlen1 == 0){
     	ShowMessage("GetWindowsDirectory Fail");
     	return;
     }else {
     	//INIﾌｧｲﾙ名にﾊﾟｽを追加
     	wsprintf(INIname, "%s%s", windir, "\\TKSMAIN.ini");	//file name
     }   

     // INIﾌｧｲﾙからの読み込み
     GetPrivateProfileString("FILE", "PATH", "", StartPATH, MAX_PATH, INIname);

     GetPrivateProfileString("FILE", "PC12", "", tempo, MAX_PATH, INIname);
     strcpy(PC12FileName,StartPATH);
     strcat(PC12FileName,"\\");
     strcat(PC12FileName,tempo);

     GetPrivateProfileString("FILE", "PC34", "", tempo, MAX_PATH, INIname);
     strcpy(PC34FileName,StartPATH);
     strcat(PC34FileName,"\\");
     strcat(PC34FileName,tempo);
}
//---------------------------------------------------------------------------
//str内にaの文字列が含まれている場合、bに置換して返す
AnsiString __fastcall TForm1::StrReplace(AnsiString str, AnsiString a, AnsiString b)
{
    int i;
    AnsiString tmpStr;

    tmpStr = str;
    while ( 1 ) {
        i = tmpStr.AnsiPos(a);
        if ( i <= 0 ) {
            return ( tmpStr );
        }

        tmpStr.Delete(i, a.Length());
        tmpStr.Insert(b, i);
    }

    return(tmpStr);
}
//---------------------------------------------------------------------------


