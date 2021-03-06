//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <stdio.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int KENSAKU_Mode;           //一覧検索モード
int     SEQNOMAX;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;

KETA_DATA KETA;

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
    BtnF02->Enabled = true;
    BtnF03->Enabled = true;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = true;
    BtnF07->Enabled = true;
    BtnF08->Enabled = false;
    BtnF09->Enabled = false;
    BtnF10->Enabled = false;
    BtnF11->Enabled = false;
    BtnF12->Enabled = true;

    //USER_COD = 1;
    KENSAKU_Mode = 1;

    // 検査予定日の初期化
    EdtYMD->Text = FormatDateTime("yyyy/mm/dd",Date());
    EdtSYM->Text = FormatDateTime("yyyy/mm",Date());
    EdtEYM->Text = FormatDateTime("yyyy/mm",Date());
    //部門、担当者
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

}

//---------------------------------------------------------------------------
//「Ｆ１：一覧検索」
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
     if ( !BtnF01->Enabled ) return;
     Form2->ShowModal();
}

//---------------------------------------------------------------------------
//「Ｆ２：検査日別選択」
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    RadioButton1->Checked = true;
    RadioButton1Click(Sender);
    EdtYMD->SetFocus();
}

//---------------------------------------------------------------------------
//「Ｆ３：ロットNo別選択」
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    RadioButton2->Checked = true;
    RadioButton2Click(Sender);
    EdtTKSHIN->SetFocus();

}

//---------------------------------------------------------------------------
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
    AnsiString sBuf;
    int n;
    AnsiString sYMD;

    sYMD = DelSEPA(EdtYMD->Text);
    if( !BtnF06->Enabled )    return;

    //印刷桁数 既定値
	KETA.MIN = 2;
	KETA.MAX = 2;
	KETA.R = 2;
	KETA.AVE =  2 + 1;
	KETA.SGM = 3;
	KETA.CP = 2;
	KETA.K = 3;
	KETA.CPK = 2;
	KETA.P = 3;

    Form5->ShowModal();
    if ( Form5->ModalResult == mrCancel ) return;


    //桁数指定（フォーマット）を求める
	KETA.AVE_str = ConvKETA1( KETA.AVE,KETA.SOKUTE_AVE );
	KETA.MIN_str = ConvKETA1( KETA.MIN,KETA.SOKUTE_MIN );
	KETA.MAX_str = ConvKETA1( KETA.MAX,KETA.SOKUTE_MAX );
	KETA.R_str   = ConvKETA1( KETA.R  ,KETA.SOKUTE_R   );
	//KETA.SGM_str = ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
	KETA.CP_str  = ConvKETA1( KETA.CP ,KETA.SOKUTE_CP  );
	KETA.CPK_str = ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	//KETA.K_str   = ConvKETA2( KETA.K  ,KETA.SOKUTE_K ,2 );
	KETA.P_str   = ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );



    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    if ( RadioButton1->Checked == true ) {
    //検査日別
        if ( Form3->Search(0) == 0 ) {
            // ステータスメッセージ
            SBr1->Panels->Items[0]->Text = "検索結果 0件です。";
            SBr1->Update();
            return;
        }

        //n = Form3->Search(1);
        //レポート オープン
        Form3->QuickRep1->Print();
        //Form3->QuickRep1->Preview();


    } else {
    //品番・ロットNo別
        //テスト用コメント
        //if ( Trim(EdtTKSHIN->Text) == "" ) {
        //    // ステータスメッセージ
        //    SBr1->Panels->Items[0]->Text = "得意先品番を入力してください";
        //    SBr1->Update();
        //    return;
        //}
        if ( Form4->Search( 0 ) == 0 ) {
            // ステータスメッセージ
            SBr1->Panels->Items[0]->Text = "検索結果 0件です。";
            SBr1->Update();
            return;
        }
        n = Form4->Search( 1 );
        //レポート オープン
        Form4->QuickRep1->Print();
        //Form4->QuickRep1->Preview();
    }
    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = " ";
    SBr1->Update();


}

//---------------------------------------------------------------------------
//「Ｆ７：照会」
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{

    AnsiString sBuf;
    int n;
    AnsiString sYMD;

    sYMD = DelSEPA(EdtYMD->Text);
    if( !BtnF06->Enabled )    return;

    //印刷桁数 既定値
	KETA.MIN = 2;
	KETA.MAX = 2;
	KETA.R = 2;
	KETA.AVE =  2 + 1;
	KETA.SGM = 3;
	KETA.CP = 2;
	KETA.K = 3;
	KETA.CPK = 2;
	KETA.P = 3;

    Form5->ShowModal();
    if ( Form5->ModalResult == mrCancel ) return;


    //桁数指定（フォーマット）を求める
	KETA.AVE_str = ConvKETA1( KETA.AVE,KETA.SOKUTE_AVE );
	KETA.MIN_str = ConvKETA1( KETA.MIN,KETA.SOKUTE_MIN );
	KETA.MAX_str = ConvKETA1( KETA.MAX,KETA.SOKUTE_MAX );
	KETA.R_str   = ConvKETA1( KETA.R  ,KETA.SOKUTE_R   );
	//KETA.SGM_str = ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
	KETA.CP_str  = ConvKETA1( KETA.CP ,KETA.SOKUTE_CP  );
	KETA.CPK_str = ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	//KETA.K_str   = ConvKETA2( KETA.K  ,KETA.SOKUTE_K ,2 );
	KETA.P_str   = ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );



    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
    SBr1->Update();

    if ( RadioButton1->Checked == true ) {
    //検査日別
        if ( Form3->Search(0) == 0 ) {
            // ステータスメッセージ
            SBr1->Panels->Items[0]->Text = "検索結果 0件です。";
            SBr1->Update();
            return;
        }

        n = Form3->Search(1);
        //レポート オープン
        Form3->QuickRep1->Preview();


    } else {
    //品番・ロットNo別
        if ( Form4->Search( 0 ) == 0 ) {
            // ステータスメッセージ
            SBr1->Panels->Items[0]->Text = "検索結果 0件です。";
            SBr1->Update();
            return;
        }
        n = Form4->Search( 1 );
        //レポート オープン
        Form4->QuickRep1->Preview();
    }
    // ステータスメッセージ
    SBr1->Panels->Items[0]->Text = " ";
    SBr1->Update();

}

//---------------------------------------------------------------------------
//「Ｆ１２：終了」
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();

}

//---------------------------------------------------------------------------
//品番・ロットNO別 選択
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
     Panel77->Color = clSilver;
     Panel77->Font->Color = clGray;
     EdtYMD->Enabled = False;

     Panel8->Color = 0x00FEE7BA;
     Panel8->Font->Color = clWindowText;
     EdtTKSHIN->Enabled = True;
     Panel10->Color = 0x00FEE7BA;
     Panel10->Font->Color = clWindowText;
     EdtSLOT->Enabled = True;
     EdtELOT->Enabled = True;
     Panel11->Color = 0x00FEE7BA;
     Panel11->Font->Color = clWindowText;
     EdtSYM->Enabled = True;
     EdtEYM->Enabled = True;
     EdtTKSHIN->SetFocus();
}

//---------------------------------------------------------------------------
//検査日別 選択
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
     Panel77->Color = 0x00FEE7BA;
     Panel77->Font->Color = clWindowText;
     EdtYMD->Enabled = True;

     Panel8->Color = clSilver;
     Panel8->Font->Color = clGray;
     EdtTKSHIN->Enabled = False;
     Panel10->Color = clSilver;
     Panel10->Font->Color = clGray;
     EdtSLOT->Enabled = False;
     EdtELOT->Enabled = False;
     Panel11->Color = clSilver;
     Panel11->Font->Color = clGray;
     EdtSYM->Enabled = False;
     EdtEYM->Enabled = False;

     EdtYMD->SetFocus();

}

//---------------------------------------------------------------------------
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
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  BtnF07Click(Sender);    break;
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
                    EdtEYM->SetFocus();
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
                //開始測定日
                if(EdtSYM->Focused() && EdtSYM->SelStart == 0 && EdtSYM->SelLength == 0 ){
					EdtELOT->SetFocus();
                    break;
                }
                //終了測定日
                if(EdtEYM->Focused() && EdtEYM->SelStart == 0 && EdtEYM->SelLength == 0 ){
					EdtSYM->SetFocus();
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
                    EdtSYM->SetFocus();
                    break;
                }
                //開始測定日
                if(EdtSYM->Focused() && EdtSYM->SelStart == EdtSYM->Text.Length() && EdtSYM->SelLength == 0 ){
                    EdtEYM->SetFocus();
                    break;
                }
                //終了測定日
                if(EdtEYM->Focused() && EdtEYM->SelStart == EdtEYM->Text.Length() && EdtEYM->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                //検査日
                if(EdtYMD->Focused() ){
                    //BtnF01Click(Sender);
                    EdtYMD->SelStart = EdtYMD->Text.Length();
                    break;
                }

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
                    EdtSYM->SetFocus();
                    break;
                }
                //開始測定日
                if(EdtSYM->Focused()){
                    EdtEYM->SetFocus();
                    break;
                }
                //終了測定日
                if(EdtEYM->Focused()){
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
    if(EdtYMD->Focused() ){
        KENSAKU_Mode = 1;
        BtnF01->Enabled = true;
        return;
    }
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
    if(EdtSYM->Focused() ){
        KENSAKU_Mode = 5;
        BtnF01->Enabled = true;
        return;
    }
    if(EdtEYM->Focused() ){
        KENSAKU_Mode = 6;
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
//有効桁数
AnsiString __fastcall TForm1::ConvKETA2(int keta,double n,int SGM_K)
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

                    //switch( SGM_K ) {
                    //    case 1:
                    //        //SGM
                    //        KETA.SOKUTE_SGM = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //    case 2:
                    //        //K
                    //        KETA.SOKUTE_K = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //}

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

