//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
     Database1->Open();

     // グリッドの初期化
     SGr1->ColWidths[0]  = Panel8->Width;       // NO
     SGr1->ColWidths[1]  = Panel43->Width;      // 焼成仕様コード
     SGr1->ColWidths[2]  = Panel19->Width;      // 炉No
     SGr1->ColWidths[3]  = Panel16->Width;      // 最高温度
     SGr1->ColWidths[4]  = Panel14->Width;      // サイクル時間
     SGr1->ColWidths[5]  = Panel23->Width;      // メモ
     SGr1->ColWidths[6]  = 0;                   // 更新回数
     SGr1->ColWidths[7]  = 0;                   // 更新日

     // ボタンの初期化
     BtnF01->Enabled = false;
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

}


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

    // 初期化表示
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

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
// 「Ｆ５：画面印刷」
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{

    if( !BtnF05->Enabled )    return;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "画面印刷中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     Form1->Print();

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

}

//---------------------------------------------------------------------------
// 「Ｆ６：印刷」
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;

    Form2->QuickRep1->Preview();
//    Form2->QuickRep1->Print();
}

//---------------------------------------------------------------------------
// 「Ｆ７：検索」
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int i;
     int iRow;
     AnsiString sBuf;

     if( !BtnF07->Enabled )    return;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select SYOSEI_CD,RO_NO,MAX_ONDO,CYCLE_TIME,MEMO,UPDCNT,ADDYMD,UPDYMD from KM04";
     if( EdtCOD->Text != "" ){
         sBuf += " where SYOSEI_CD like '";
         sBuf += EdtCOD->Text ;
         sBuf += "%'";
     }
     sBuf = sBuf + " order by SYOSEI_CD";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     iRow = 0;
     while( !Query1->Eof ){

          // グリッドの最大行数が超えていないかチェックする
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // グリッドにデータをセットします。
          sBuf = iRow + 1;                                 // NO
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[0]->AsString;      // 焼成コード
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[1]->AsString;      // 炉NO
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[2]->AsString;      // 最高温度
          SGr1->Cells[3][iRow] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;      // サイクル温度
          SGr1->Cells[4][iRow] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;      // メモ
          SGr1->Cells[5][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;      // 更新回数
          SGr1->Cells[6][iRow] = sBuf;

          if( sBuf != "" ) {
             if( StrToInt(sBuf) > 0 )
                sBuf = Query1->Fields->Fields[7]->AsString;   // 変更日
             else
                sBuf = Query1->Fields->Fields[6]->AsString;   // 登録日
          }
          else{
             sBuf = Query1->Fields->Fields[6]->AsString;   // 登録日
          }
          SGr1->Cells[7][iRow] = sBuf;

          // カーソルを次にセットする
          Query1->Next();

          iRow += 1;
     }

     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

     if( iRow == 0 ){

         // 検索結果該当なしの場合
         EdtCOD->SetFocus();

         // ボタンの初期化
         BtnF01->Enabled = false;
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

     }
     else{
         // グリッドを選択
         SGr1SelectCell( Sender, 1, 0, true);

         SGr1->SetFocus();

         // 新しいトランザクションを開始
         if( Database1->InTransaction == false ){
             Database1->StartTransaction();
             DataSave = false;
         }

         // ボタンの初期化
         BtnF01->Enabled = false;
         BtnF02->Enabled = true;
         BtnF03->Enabled = true;
         BtnF04->Enabled = false;
         BtnF05->Enabled = true;
         BtnF06->Enabled = true;
         BtnF07->Enabled = true;
         BtnF08->Enabled = true;
         BtnF09->Enabled = true;
         BtnF10->Enabled = true;
         BtnF11->Enabled = true;
         BtnF12->Enabled = true;

     }

     // ステータスメッセージ
     sBuf = FormatFloat( "検索結果 0件です。", iRow );
     SBr1->Panels->Items[0]->Text = sBuf;
     SBr1->Update();

}


//---------------------------------------------------------------------------
// 「Ｆ８：新規登録」
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
     int i;
     AnsiString sBuf;

     if( !BtnF08->Enabled )    return;

     if( Edt1->Text == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "必須項目を入力して下さい。";
        SBr1->Update();
        Beep();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     //2002/11/22 「'」→「_」に置換 E.Takase
	 if( Edt1->Text != "" ) Edt1->Text = StrReplace(Edt1->Text , "'", "_");
	 if( Edt2->Text != "" ) Edt2->Text = StrReplace(Edt2->Text , "'", "_");
	 if( Edt5->Text != "" ) Edt5->Text = StrReplace(Edt5->Text , "'", "_");

     // データをバッファに格納します。
     KM04.SYOSEI_CD  = Edt1->Text;        // 焼成コード
     KM04.RO_NO      = Edt2->Text;        // 炉NO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX温度
     KM04.CYCLE_TIME = Edt4->Value;       // サイクルタイム
     KM04.MEMO       = Edt5->Text;        // メモ
     KM04.ADDYMD     = FormatDateTime("yyyymmdd",Date());               // 登録日
     KM04.ADDTIM     = FormatDateTime("hhmm",TDateTime::CurrentTime()); // 登録時間
     KM04.UPDCHR     = USER_COD;          // 更新者
     KM04.UPDCNT     = 0;                 // 更新回数

     // AddData
     if( AddData() == False ){
        return;
     }

     // グリッドにデータをセットします。
     sBuf = SGr1->RowCount ;                            // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     sBuf = KM04.SYOSEI_CD;                           // 焼成コード
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;

     sBuf = KM04.RO_NO;                               // 炉NO
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;

     sBuf = IntToStr(KM04.MAX_ONDO);                  // 最高温度
     SGr1->Cells[3][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM04.CYCLE_TIME);                // サイクル温度
     SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = KM04.MEMO;                                // メモ
     SGr1->Cells[5][SGr1->RowCount - 1] = sBuf;

     sBuf = IntToStr(KM04.UPDCNT);                    // 更新回数
     SGr1->Cells[6][SGr1->RowCount - 1] = sBuf;

     sBuf = KM04.ADDYMD;                              // 更新日
     SGr1->Cells[7][SGr1->RowCount - 1] = sBuf;

     // 一行増やす
     SGr1->RowCount = SGr1->RowCount + 1;

     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // 新しい行を選択
     SGr1->Row = SGr1->RowCount - 1;

     Edt1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

}

//---------------------------------------------------------------------------
// 「Ｆ９：修正」
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
     AnsiString sBuf;

     if( !BtnF09->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
        SBr1->Update();
        Beep();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     //2002/11/22 「'」→「_」に置換 E.Takase
	 if( Edt1->Text != "" ) Edt1->Text = StrReplace(Edt1->Text , "'", "_");
	 if( Edt2->Text != "" ) Edt2->Text = StrReplace(Edt2->Text , "'", "_");
	 if( Edt5->Text != "" ) Edt5->Text = StrReplace(Edt5->Text , "'", "_");

     // データをバッファに格納します。
     KM04.SYOSEI_CD  = Edt1->Text;        // 焼成コード
     KM04.RO_NO      = Edt2->Text;        // 炉NO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX温度
     KM04.CYCLE_TIME = Edt4->Value;       // サイクルタイム
     KM04.MEMO       = Edt5->Text;        // メモ
     KM04.UPDYMD     = FormatDateTime("yyyymmdd",Date());               // 登録日
     KM04.UPDTIM     = FormatDateTime("hhmm",TDateTime::CurrentTime()); // 登録時間
     KM04.UPDCHR     = USER_COD;          // 更新者
     if( SGr1->Cells[6][SGr1->Row] == "" ){
        KM04.UPDCNT  = 0;
     }
     else{
        KM04.UPDCNT  = StrToInt(SGr1->Cells[6][SGr1->Row]);
        KM04.UPDCNT += 1 ;                  // 更新回数
     }

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row]) == False ){
        return;
     }

     // グリッドにデータをセットします。
     sBuf = KM04.SYOSEI_CD;                           // 焼成コード
     SGr1->Cells[1][SGr1->Row] = sBuf;

     sBuf = KM04.RO_NO;                               // 炉NO
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = IntToStr(KM04.MAX_ONDO);                  // 最高温度
     SGr1->Cells[3][SGr1->Row] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM04.CYCLE_TIME);                // サイクル温度
     SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = KM04.MEMO;                                // メモ
     SGr1->Cells[5][SGr1->Row] = sBuf;

     sBuf = IntToStr(KM04.UPDCNT);                    // 更新回数
     SGr1->Cells[6][SGr1->Row] = sBuf;

     sBuf = KM04.UPDYMD;                              // 更新日
     SGr1->Cells[7][SGr1->Row] = sBuf;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

}

//---------------------------------------------------------------------------
// 「Ｆ１０：削除」
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     int i;

     if( !BtnF10->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "削除対象ではありません。";
        SBr1->Update();
        Beep();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "削除中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // データをバッファに格納します。
     KM04.SYOSEI_CD  = Edt1->Text;        // 焼成コード
     KM04.RO_NO      = Edt2->Text;        // 炉NO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX温度
     KM04.CYCLE_TIME = Edt4->Value;       // サイクルタイム
     KM04.MEMO       = Edt5->Text;        // メモ
     KM04.UPDCHR     = USER_COD;          // 更新者
     if( SGr1->Cells[6][SGr1->Row] == "" ){
        KM04.UPDCNT  = 0;
     }
     else{
        KM04.UPDCNT  = StrToInt(SGr1->Cells[6][SGr1->Row]) ;        // 更新回数
     }

     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // グリッドの一行を削除します。
         SGr1->Cells[1][i] = SGr1->Cells[1][i+1];        // 焼成コード
         SGr1->Cells[2][i] = SGr1->Cells[2][i+1];        // 炉NO
         SGr1->Cells[3][i] = SGr1->Cells[3][i+1];        // 最高温度
         SGr1->Cells[4][i] = SGr1->Cells[4][i+1];        // サイクル温度
         SGr1->Cells[5][i] = SGr1->Cells[5][i+1];        // メモ
         SGr1->Cells[6][i] = SGr1->Cells[6][i+1];        // 更新回数
         SGr1->Cells[7][i] = SGr1->Cells[7][i+1];        // 更新日
     }

     // 一行減らす
     SGr1->RowCount = SGr1->RowCount - 1;

     // 新しい行を選択
     if( SGr1->RowCount == SGr1->Row)    SGr1->Row = SGr1->Row - 1;
     else                                SGr1->Row = SGr1->Row;

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     //SGr1->SetFocus();

     // データを変更したフラグ
     DataSave = true;

}

//---------------------------------------------------------------------------
// 「Ｆ１１：保存」
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{

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
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = false;

}

//---------------------------------------------------------------------------
// 「Ｆ１２：戻る」
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;

     Close();
}

//---------------------------------------------------------------------------
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
//         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_UP:  if( SGr1->Focused() )   break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_DOWN:if( SGr1->Focused() )   break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
                      // 検索部にフォーカスがある場合は、検索実行
                      if( EdtCOD->Focused() ){
                          BtnF07Click(Sender);
                      }
                      // 検索部以外にフォーカスがある場合は、検索部にセットフォーカス
                      else{
                          EdtCOD->SetFocus();
                      }
                      break;
         case VK_F8:  BtnF08Click(Sender);    break;
         case VK_F9:  BtnF09Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);
                      Key = 0;
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;


         // 前項
         case VK_LEFT:
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == 0 && Edt2->SelLength == 0 ){
                    Edt1->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == 0 && Edt3->SelLength == 0 ){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == 0 && Edt4->SelLength == 0 ){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == 0 && Edt5->SelLength == 0 ){
                    Edt4->SetFocus();
                    break;
                }
                break;

         // 次項
         case VK_RIGHT:
                if(Edt1->Focused() && Edt1->SelStart == Edt1->Text.Length() && Edt1->SelLength == 0 ){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == Edt2->Text.Length() && Edt2->SelLength == 0 ){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == Edt3->Text.Length() && Edt3->SelLength == 0 ){
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == Edt4->Text.Length() && Edt4->SelLength == 0 ){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == Edt5->Text.Length() && Edt5->SelLength == 0 ){
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD->Focused()){
                    BtnF07Click(Sender);
                    break;
                }
                if(Edt1->Focused()){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused()){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused()){
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused()){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused()){
                    Edt1->SetFocus();
                    break;
                }
                break;

     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{

    // ステータスメッセージ
    if(SBr1->Panels->Items[0]->Text != ""){
       SBr1->Panels->Items[0]->Text = "";
       SBr1->Update();
    }

    // NO
    PnlNO->Caption = SGr1->Cells[0][ARow];
    // 焼成コード
    Edt1->Text = SGr1->Cells[1][ARow];
    // 炉NO
    Edt2->Text = SGr1->Cells[2][ARow];
    // 最高温度
    Edt3->Text = SGr1->Cells[3][ARow];
    // サイクル時間
    Edt4->Text = SGr1->Cells[4][ARow];
    // メモ
    Edt5->Text = SGr1->Cells[5][ARow];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr1_KeyPress(TObject *Sender, char &Key)
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
         case VK_RETURN:Edt1->SetFocus();       break;
     }

}

//---------------------------------------------------------------------------
// データを追加します。
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "select SYOSEI_CD from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // 焼成コード

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "既に登録されています。";
            SBr1->Update();
            Beep();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "insert into KM04(SYOSEI_CD,RO_NO,MAX_ONDO,CYCLE_TIME,MEMO,ADDYMD,ADDTIM,UPDCHR,UPDCNT)";
     sBuf += " values('";
     sBuf += KM04.SYOSEI_CD             + "','";        // 焼成コード
     sBuf += KM04.RO_NO                 + "'," ;        // 炉NO
     sBuf += IntToStr(KM04.MAX_ONDO)    +  "," ;        // MAX温度
     sBuf += IntToStr(KM04.CYCLE_TIME)  +  ",'";        // サイクルタイム
     sBuf += KM04.MEMO                  + "','";        // メモ
     sBuf += KM04.ADDYMD                + "','";        // 登録日
     sBuf += KM04.ADDTIM                + "'," ;        // 登録時間
     sBuf += IntToStr(KM04.UPDCHR)      +  "," ;        // 更新者
     sBuf += IntToStr(KM04.UPDCNT)      +  ")" ;        // 更新回数

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// データを修正します。
bool __fastcall TForm1::CollectData(String OldKey)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "update KM04 set ";
     sBuf = sBuf + "SYOSEI_CD='"  + KM04.SYOSEI_CD            + "', ";  // 焼成コード
     sBuf = sBuf + "RO_NO='"      + KM04.RO_NO                + "', ";  // 炉NO
     sBuf = sBuf + "MAX_ONDO="    + IntToStr(KM04.MAX_ONDO)   + ", " ;  // MAX温度
     sBuf = sBuf + "CYCLE_TIME="  + IntToStr(KM04.CYCLE_TIME) + ", " ;  // サイクルタイム
     sBuf = sBuf + "MEMO='"       + KM04.MEMO                 + "', ";  // メモ
     sBuf = sBuf + "UPDYMD='"     + KM04.UPDYMD               + "', ";  // 更新日
     sBuf = sBuf + "UPDTIM='"     + KM04.UPDTIM               + "', ";  // 更新時間
     sBuf = sBuf + "UPDCHR="      + IntToStr(KM04.UPDCHR)     + ", " ;  // 更新者
     sBuf = sBuf + "UPDCNT="      + IntToStr(KM04.UPDCNT)     + " "  ;  // 更新回数
     sBuf = sBuf + "where SYOSEI_CD='" + OldKey + "'";

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
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
     sBuf = "select SYOSEI_CD from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // 焼成コード

     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "該当の焼成コードが見つかりません。削除できませんでした。";
            SBr1->Update();
            Beep();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }



     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "delete from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // 焼成コード


     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
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

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
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


