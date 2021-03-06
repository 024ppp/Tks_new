/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 2000.01.06                                          *
*  update        : 2002.02.26(検索条件追加：検査日)                    *
*  contents      : メインプログラム                                    *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <stdio.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int KENSAKU_Mode;           //一覧検索モード
int     USER_COD;           //担当者コード
String  USER_NAM;           //担当者名
String  BUMO_COD;           //部署コード
String  BUMO_NAM;           //部署名

KD_DATA KD;
CAL_DATA CALD;

int intKEIJKBN; //形状区分 //2002/12/07 E.Takase

int iKojoKbn = 0;                   // 工場区分

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
AnsiString MSG_10 = "データを保存しますか？。" ;
AnsiString MSG_11 = "RS232C接続エラーが発生しました。" ;
AnsiString MSG_12 = "測定数を減らします。よろしいですか？";


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//フォーム作成時
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Database1->Open();

    // ボタンの初期化
    BtnF01->Enabled = true;
    BtnF02->Enabled = false;
    BtnF03->Enabled = false;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = true;
    BtnF07->Enabled = false;
    BtnF08->Enabled = false;
    BtnF09->Enabled = false;
    BtnF10->Enabled = false;
    BtnF11->Enabled = false;
    BtnF12->Enabled = true;

    //USER_COD = 1;
    KENSAKU_Mode = 1;

    //部門、担当者
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    //CheckBox1
    CheckBox1->Caption = "リード線長さ";
	CheckBox2->Caption = "ブラシ幅";
	CheckBox3->Caption = "ブラシ幅(縦押し)";
	CheckBox4->Caption = "リード線取付抵抗";
	CheckBox5->Caption = "リード線取付強度";
	CheckBox6->Caption = "見掛比重";
	CheckBox7->Caption = "硬度(HsC 圧面)";
	CheckBox8->Caption = "硬度(HsC 側面)";
	CheckBox9->Caption = "硬度(HsD 圧面)";
	CheckBox10->Caption = "硬度(HsD 側面)";
	CheckBox11->Caption = "抵抗率";
	CheckBox12->Caption = "曲げ強さ";
	CheckBox13->Caption = "座屈";
	CheckBox14->Caption = "曲げ強さ(現物)";

    //ラジオボタン
    RadioKANSA->Checked = true;
    RadioLOT->Checked   = false;

    // 20160630_iniファイル読み込み追加
    Read_Ini();

    //20160704追加
    if ( iKojoKbn == 0 ) {
       RadioHON->Checked = true;
       RadioKOU->Checked = false;
       RadioRYO->Checked = false;
    } else if ( iKojoKbn == 1 ) {
       RadioHON->Checked = false;
       RadioKOU->Checked = true;
       RadioRYO->Checked = false;
    } else {
       RadioHON->Checked = false;
       RadioKOU->Checked = false;
       RadioRYO->Checked = true;
    }

}

//---------------------------------------------------------------------------
//「Ｆ１：一覧検索」
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
     if ( !BtnF01->Enabled ) return;
     Form2->ShowModal();
}

//-------------------------------------------------------------------------
//「Ｆ５：画面印刷」
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
//「Ｆ６：印刷」
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
//    if ( Search_MAIN() > 0 ) {
//    	if ( Write_CSVMain() ) {
//        	ShowMessage("印刷！");
//       } else {
//        	ShowMessage("CSV出力失敗");
//        }
//
//    } else {
//    	ShowMessage("検索結果 0件");
//    }

	AnsiString sBuf;

    //指定された得意先品番の形状を検索
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

    sBuf = "SELECT KEIJKBN  FROM KM02 ";
	sBuf += " where DTKSHIN = '" + EdtTKSHIN->Text + "'";
	sBuf += " and REVCNT = 0";
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//検索結果 ０件
        ShowMessage("検索結果 0件です");
		return;
	}
	intKEIJKBN = Form1->Query1->FieldValues["KEIJKBN"];



    //指定された測定項目を印刷
	switch(Write_CSVMain())
	{
    	case 0:
        	ShowMessage("検索結果 0件です");
            break;

    	case -1:
        	ShowMessage("CSV出力 失敗しました");
            break;

    	case 1:

            if (!(Excel_Write() )) ShowMessage("Excelの起動に失敗しました");
            break;

        default:
        	ShowMessage("データ作成 失敗しました");
            break;

	}

}

//「Ｆ１２：終了」
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();

}
//「FormKeyダウン」
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
//         case VK_F2:  BtnF02Click(Sender);    break;
//         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
//         case VK_F7:  BtnF07Click(Sender);    break;
//         case VK_F8:  BtnF08Click(Sender);    break;
//         case VK_F9:  BtnF09Click(Sender);    break;
//         case VK_F10: BtnF10Click(Sender);    break;
//         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;


         // 前項
         case VK_UP:
         case VK_LEFT:
                //得意先品番
                if(EdtTKSHIN->Focused() && EdtTKSHIN->SelStart == 0 && EdtTKSHIN->SelLength == 0 ){
                    EdtEYMD->SetFocus();
                    break;
                }
                //開始ロット
                if(EdtSLOT->Focused() && EdtSLOT->SelStart == 0 && EdtSLOT->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                //終了ロット
                if(EdtELOT->Focused() && EdtELOT->SelStart == 0 && EdtELOT->SelLength == 0 ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //2001.02.26追加
                //開始日
                if(EdtSYMD->Focused() && EdtSYMD->SelStart == 0 && EdtSYMD->SelLength == 0 ){
                    EdtELOT->SetFocus();
                    break;
                }
                //終了日
                if(EdtEYMD->Focused() && EdtEYMD->SelStart == 0 && EdtEYMD->SelLength == 0 ){
                    EdtSYMD->SetFocus();
                    break;
                }

                break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                //得意先品番
                if(EdtTKSHIN->Focused() && EdtTKSHIN->SelStart == EdtTKSHIN->Text.Length() && EdtTKSHIN->SelLength == 0 ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //開始ロット
                if(EdtSLOT->Focused() && EdtSLOT->SelStart == EdtSLOT->Text.Length() && EdtSLOT->SelLength == 0 ){
                    EdtELOT->SetFocus();
                    break;
                }
                //終了ロット
                if(EdtELOT->Focused() && EdtELOT->SelStart == EdtELOT->Text.Length() && EdtELOT->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                //2001.02.26追加
                //開始日
                if(EdtSYMD->Focused() && EdtSYMD->SelStart == EdtSYMD->Text.Length() && EdtSYMD->SelLength == 0 ){
                    EdtEYMD->SetFocus();
                    break;
                }
                //終了日
                if(EdtEYMD->Focused() && EdtEYMD->SelStart == EdtEYMD->Text.Length() && EdtEYMD->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }

                break;

         // Enter
         case VK_RETURN:
                //得意先品番
                if(EdtTKSHIN->Focused() ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //開始ロット
                if(EdtSLOT->Focused()){
                    EdtELOT->SetFocus();
                    break;
                }
                //終了ロット
                if(EdtELOT->Focused()){
                    EdtSYMD->SetFocus();
                    break;
                }
                //2001.02.26追加
                //開始日
                if(EdtSYMD->Focused()){
                    EdtEYMD->SetFocus();
                    break;
                }
                //終了日
                if(EdtEYMD->Focused()){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                break;

     }
}

//---------------------------------------------------------------------------
//「フォーカス取得時」
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtTKSHIN->Focused() ){
        KENSAKU_Mode = 2;
        BtnF01->Enabled = true;
        return;
    }
    if(EdtSLOT->Focused() ){
        KENSAKU_Mode = 3;
        BtnF01->Enabled = true;
        return;
    }
    if(EdtELOT->Focused() ){
        KENSAKU_Mode = 4;
        BtnF01->Enabled = true;
        return;
    }

    KENSAKU_Mode = -1;
    BtnF01->Enabled = false;

}

//---------------------------------------------------------------------------
//小数点以下
AnsiString __fastcall TForm1::ConvKETA1(int keta,double n)
{
    int x;
    double m;
    AnsiString str;

    //小数点以下 keta桁
    x = pow(10,keta);
    m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

    str = "#0." + AnsiString::StringOfChar('0', keta );

    return( str );
}
//---------------------------------------------------------------------------
//有効桁数
AnsiString __fastcall TForm1::ConvKETA2(int keta,double n)
{
    int i,x;
    double m;
    AnsiString str;
    AnsiString tmp_s1,tmp_s2;
    int tmp_n1,tmp_n2;
    AnsiString Formatstr;
    char test[256];
    AnsiString test2;
    int flag,pos;
    int flag_M;

    //有効桁数
    if ( n < 0 ) {
        //マイナス
        flag_M = -1;
        n = n * -1;
    } else {
        flag_M = 1;
    }

    if ( n >= 1 ) {
        //1以上
        flag = 1;
    } else {
        //0以上1未満
        flag = 2;
    }

    switch( flag ){
        case 1:
            str = FormatFloat("#0.0#", n );
            pos = str.AnsiPos(".") - 1;
            if ( pos <  keta ) {
                Formatstr = "#0." + AnsiString::StringOfChar('0', keta-pos );
            } else {
                if ( pos == keta ) {
                    Formatstr = "#0";
                } else {
                //keta = 2, n = 1234.5 → 1200
                    Formatstr = "#0";
                    tmp_s1 = FloatToStr((int(n)));
                    tmp_n1 = tmp_s1.Length();
                    tmp_n2 = pow(10,(tmp_n1-keta));

                }
            }
            break;

        case 2:
            x = pow(10,keta);
            m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

            if ( n == 0 ) {
            	Formatstr = "#0."+ AnsiString::StringOfChar('0', (keta - 1));
            } else {
            	i = 1;
            	while(1) {
            		if ( int(n*( pow(10,i))) > 0 ) {
                		break;
                	} else {
                		i++;
                	}
            	}
            	Formatstr = "#0." + AnsiString::StringOfChar('0', (i - 1 + keta));
			}
            break;
    }
    return ( Formatstr );
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



