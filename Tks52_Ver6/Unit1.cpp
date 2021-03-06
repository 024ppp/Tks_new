//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
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
     SGr1->ColWidths[0]  = Panel8->Width;                    // NO
     SGr1->ColWidths[1]  = Panel43->Width;                   // 材質名称
     SGr1->ColWidths[2]  = Panel19->Width;                   // 材質コード
     SGr1->ColWidths[3]  = Panel16->Width / 2;               // 母体比重（下限）
     SGr1->ColWidths[4]  = Panel16->Width / 2 - 1;           // 母体比重（上限）
     SGr1->ColWidths[5]  = Panel14->Width / 2;               // 固有抵抗率（下限）
     SGr1->ColWidths[6]  = Panel14->Width / 2 - 1;           // 固有抵抗率（上限）
     SGr1->ColWidths[7]  = Panel14->Width / 2;               // 曲げ強度（下限）
     SGr1->ColWidths[8]  = Panel14->Width / 2 - 1;           // 曲げ強度（上限）
     SGr1->ColWidths[9]  = Panel23->Width - Panel14->Width;  // 曲げ強度（単位）
     SGr1->ColWidths[10] = Panel28->Width / 2;               // HsC硬度 圧面（下限）
     SGr1->ColWidths[11] = Panel28->Width / 2;               // HsC硬度 圧面（上限）
     SGr1->ColWidths[12] = Panel34->Width / 2;               // HsC硬度 側面（下限）
     SGr1->ColWidths[13] = Panel34->Width / 2;               // HsC硬度 側面（上限）
     SGr1->ColWidths[14] = Panel36->Width / 2;               // HsD硬度 圧面（下限）
     SGr1->ColWidths[15] = Panel36->Width / 2;               // HsD硬度 圧面（上限）
     SGr1->ColWidths[16] = Panel41->Width / 2;               // HsD硬度 側面（下限）
     SGr1->ColWidths[17] = Panel41->Width / 2;               // HsD硬度 側面（上限）
     SGr1->ColWidths[18] = 0;                                // 更新回数
     SGr1->ColWidths[19] = 0;                                // 更新日

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
     AnsiString sBuf2;

    if( !BtnF07->Enabled )    return;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select ZISNAM,ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
     sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,";
     sBuf = sBuf + "UPDCNT,ADDYMD,UPDYMD from KM03";
     i = 0;
     if( EdtCOD1->Text != "" ){
         // 材質名称
         sBuf += " where ZISNAM like '";
         sBuf += EdtCOD1->Text ;
         sBuf += "%'";
         i = 1;
     }
     if( EdtCOD2->Text != "" ){
         // 材質コード
         if( i == 0 )   sBuf += " where";
         else           sBuf += " and";
         sBuf += " ZISCOD like '";
         sBuf += EdtCOD2->Text ;
         sBuf += "%'";
     }
     sBuf = sBuf + " order by ZISNAM,ZISCOD";
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

          sBuf = Query1->Fields->Fields[0]->AsString;      // 材質名称
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[1]->AsString;      // 材質コード
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = FormatFloat("0.00",Query1->Fields->Fields[2]->AsFloat);      // 母体比重（下限）
          SGr1->Cells[3][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.00",Query1->Fields->Fields[3]->AsFloat);      // 母体比重（上限）
          SGr1->Cells[4][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[4]->AsInteger);              // 固有抵抗率（下限）
          SGr1->Cells[5][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[5]->AsInteger);              // 固有抵抗率（上限）
          SGr1->Cells[6][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[6]->AsFloat);     // 曲げ強度（下限）
          if( sBuf.Length() > 6 ){
              sBuf = FormatFloat("0",Query1->Fields->Fields[6]->AsFloat);
          }
          SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[7]->AsFloat);     // 曲げ強度（上限）
          if( sBuf.Length() > 6 ){
              sBuf = FormatFloat("0",Query1->Fields->Fields[7]->AsFloat);
          }
          SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          switch( Query1->Fields->Fields[8]->AsInteger ){ // 曲げ強度（単位）
              case 1: sBuf = "Kgf/cm2";  break;   // kgf/cm2
              case 2: sBuf = "N/cm2";    break;   // N/cm2
              case 3: sBuf = "MPa";      break;   // MPa
              case 4: sBuf = "N/mm2";    break;   // N/mm2
          }
          SGr1->Cells[9][iRow] = sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[9]->AsInteger);              // ＨｓＣ硬度　圧面（下限）
          SGr1->Cells[10][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[10]->AsInteger);             // ＨｓＣ硬度　圧面（上限）
          SGr1->Cells[11][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[11]->AsInteger);             // ＨｓＣ硬度　側面（下限）
          SGr1->Cells[12][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[12]->AsInteger);             // ＨｓＣ硬度　側面（上限）
          SGr1->Cells[13][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[13]->AsFloat);      // ＨｓＤ硬度　圧面（下限）
          SGr1->Cells[14][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[14]->AsFloat);      // ＨｓＤ硬度　圧面（上限）
          SGr1->Cells[15][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[15]->AsFloat);      // ＨｓＤ硬度　側面（下限）
          SGr1->Cells[16][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[16]->AsFloat);      // ＨｓＤ硬度　側面（上限）
          SGr1->Cells[17][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[17]->AsString;     // 更新回数
          SGr1->Cells[18][iRow] = sBuf;

          if( sBuf != "" ) {
             if( StrToInt(sBuf) > 0 )
                sBuf = Query1->Fields->Fields[19]->AsString;   // 変更日
             else
                sBuf = Query1->Fields->Fields[18]->AsString;   // 登録日
          }
          else{
             sBuf = Query1->Fields->Fields[18]->AsString;      // 登録日
          }
          SGr1->Cells[19][iRow] = sBuf;                    // 更新日

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
         EdtCOD1->SetFocus();

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
         SGr1SelectCell( Sender, 1, 0, true);

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

     // データをバッファに格納します。
     KM03.ZISNAM    = Edt1->Text;      // 材質名称
     KM03.ZISCOD    = Edt2->Text;      // 材質コード
     KM03.BOTAI_MIN = Edt3->Value;     // 母体比重（下限）
     KM03.BOTAI_MAX = Edt4->Value;     // 母体比重（上限）
     KM03.KOYU_MIN  = Edt5->Value;     // 固有抵抗率（下限）
     KM03.KOYU_MAX  = Edt6->Value;     // 固有抵抗率（上限）
     KM03.MAGE_MIN  = Edt7->Value;     // 曲げ強度（下限）
     KM03.MAGE_MAX  = Edt8->Value;     // 曲げ強度（上限）
     KM03.MAGE_TAN  = 0;               // 曲げ強度（単位）
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC硬度 圧面（下限）
     KM03.HSC_A_MAX = Edt10->Value;    // HsC硬度 圧面（上限）
     KM03.HSC_S_MIN = Edt11->Value;    // HsC硬度 側面（下限）
     KM03.HSC_S_MAX = Edt12->Value;    // HsC硬度 側面（上限）
     KM03.HSD_A_MIN = Edt13->Value;    // HsD硬度 圧面（下限）
     KM03.HSD_A_MAX = Edt14->Value;    // HsD硬度 圧面（上限）
     KM03.HSD_S_MIN = Edt15->Value;    // HsD硬度 側面（下限）
     KM03.HSD_S_MAX = Edt16->Value;    // HsD硬度 側面（上限）
     KM03.ADDYMD    = FormatDateTime("yyyymmdd",Date());                // 登録日
     KM03.ADDTIM    = FormatDateTime("hhmm",TDateTime::CurrentTime());  // 登録時間
     KM03.UPDCHR    = USER_COD;        // 更新者
     KM03.UPDCNT    = 0;               // 更新回数

     // AddData
     if( AddData() == False ){
        return;
     }

     // グリッドにデータをセットします。
     sBuf = SGr1->RowCount ;                          // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     sBuf = KM03.ZISNAM;                              // 材質名称
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;

     sBuf = KM03.ZISCOD;                              // 材質コード
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MIN);       // 母体比重（下限）
     SGr1->Cells[3][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MAX);       // 母体比重（上限）
     SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MIN);                  // 固有抵抗率（下限）
     SGr1->Cells[5][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MAX);                  // 固有抵抗率（上限）
     SGr1->Cells[6][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MIN);         // 曲げ強度（下限）
     SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MAX);         // 曲げ強度（上限）
     SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     if( KM03.MAGE_TAN == 1 ) sBuf = "Kgf/cm2";
     if( KM03.MAGE_TAN == 2 ) sBuf = "N/cm2";
     if( KM03.MAGE_TAN == 3 ) sBuf = "MPa";
     if( KM03.MAGE_TAN == 4 ) sBuf = "N/mm2";
     SGr1->Cells[9][SGr1->RowCount - 1] = sBuf;       // 曲げ強度（単位）

     sBuf = IntToStr(KM03.HSC_A_MIN);                 // HsC硬度 圧面（下限）
     SGr1->Cells[10][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_A_MAX);                 // HsC硬度 圧面（上限）
     SGr1->Cells[11][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MIN);                 // HsC硬度 側面（下限）
     SGr1->Cells[12][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MAX);                 // HsC硬度 側面（上限）
     SGr1->Cells[13][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MIN);        // HsD硬度 圧面（下限）
     SGr1->Cells[14][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MAX);        // HsD硬度 圧面（上限）
     SGr1->Cells[15][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MIN);        // HsD硬度 側面（下限）
     SGr1->Cells[16][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MAX);        // HsD硬度 側面（上限）
     SGr1->Cells[17][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.UPDCNT);                    // 更新回数
     SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;

     sBuf = KM03.ADDYMD;                              // 更新日
     SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;


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

     // データをバッファに格納します。
     KM03.ZISNAM    = Edt1->Text;      // 材質名称
     KM03.ZISCOD    = Edt2->Text;      // 材質コード
     KM03.BOTAI_MIN = Edt3->Value;     // 母体比重（下限）
     KM03.BOTAI_MAX = Edt4->Value;     // 母体比重（上限）
     KM03.KOYU_MIN  = Edt5->Value;     // 固有抵抗率（下限）
     KM03.KOYU_MAX  = Edt6->Value;     // 固有抵抗率（上限）
     KM03.MAGE_MIN  = Edt7->Value;     // 曲げ強度（下限）
     KM03.MAGE_MAX  = Edt8->Value;     // 曲げ強度（上限）
     KM03.MAGE_TAN  = 0;               // 曲げ強度（単位）
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC硬度 圧面（下限）
     KM03.HSC_A_MAX = Edt10->Value;    // HsC硬度 圧面（上限）
     KM03.HSC_S_MIN = Edt11->Value;    // HsC硬度 側面（下限）
     KM03.HSC_S_MAX = Edt12->Value;    // HsC硬度 側面（上限）
     KM03.HSD_A_MIN = Edt13->Value;    // HsD硬度 圧面（下限）
     KM03.HSD_A_MAX = Edt14->Value;    // HsD硬度 圧面（上限）
     KM03.HSD_S_MIN = Edt15->Value;    // HsD硬度 側面（下限）
     KM03.HSD_S_MAX = Edt16->Value;    // HsD硬度 側面（上限）
     KM03.UPDYMD    = FormatDateTime("yyyymmdd",Date());               // 登録日
     KM03.UPDTIM    = FormatDateTime("hhmm",TDateTime::CurrentTime()); // 登録時間
     KM03.UPDCHR    = USER_COD;        // 更新者
     if( SGr1->Cells[18][SGr1->Row] == "" ){
        KM03.UPDCNT  = 0;
     }
     else{
        KM03.UPDCNT  = StrToInt(SGr1->Cells[18][SGr1->Row]) ;        // 更新回数
        KM03.UPDCNT += 1 ;
     }

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row], SGr1->Cells[2][SGr1->Row]) == False ){
        return;
     }

     // グリッドにデータをセットします。
     sBuf = KM03.ZISNAM;                              // 材質名称
     SGr1->Cells[1][SGr1->Row] = sBuf;

     sBuf = KM03.ZISCOD;                              // 材質コード
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MIN);       // 母体比重（下限）
     SGr1->Cells[3][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MAX);       // 母体比重（上限）
     SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MIN);                  // 固有抵抗率（下限）
     SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MAX);                  // 固有抵抗率（上限）
     SGr1->Cells[6][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MIN);         // 曲げ強度（下限）
     SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MAX);         // 曲げ強度（上限）
     SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     if( KM03.MAGE_TAN == 1 ) sBuf = "Kgf/cm2";
     if( KM03.MAGE_TAN == 2 ) sBuf = "N/cm2";
     if( KM03.MAGE_TAN == 3 ) sBuf = "MPa";
     if( KM03.MAGE_TAN == 4 ) sBuf = "N/mm2";
     SGr1->Cells[9][SGr1->Row] = sBuf;       // 曲げ強度（単位）

     sBuf = IntToStr(KM03.HSC_A_MIN);                 // HsC硬度 圧面（下限）
     SGr1->Cells[10][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_A_MAX);                 // HsC硬度 圧面（上限）
     SGr1->Cells[11][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MIN);                 // HsC硬度 側面（下限）
     SGr1->Cells[12][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MAX);                 // HsC硬度 側面（上限）
     SGr1->Cells[13][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MIN);        // HsD硬度 圧面（下限）
     SGr1->Cells[14][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MAX);        // HsD硬度 圧面（上限）
     SGr1->Cells[15][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MIN);        // HsD硬度 側面（下限）
     SGr1->Cells[16][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MAX);        // HsD硬度 側面（上限）
     SGr1->Cells[17][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.UPDCNT);                    // 更新回数
     SGr1->Cells[18][SGr1->Row] = sBuf;

     sBuf = KM03.UPDYMD;                              // 更新日
     SGr1->Cells[19][SGr1->Row] = sBuf;


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
     KM03.ZISNAM    = Edt1->Text;      // 材質名
     KM03.ZISCOD    = Edt2->Text;      // 材質コード
     KM03.BOTAI_MIN = Edt3->Value;     // 母体比重（下限）
     KM03.BOTAI_MAX = Edt4->Value;     // 母体比重（上限）
     KM03.KOYU_MIN  = Edt5->Value;     // 固有抵抗率（下限）
     KM03.KOYU_MAX  = Edt6->Value;     // 固有抵抗率（上限）
     KM03.MAGE_MIN  = Edt7->Value;     // 曲げ強度（下限）
     KM03.MAGE_MAX  = Edt8->Value;     // 曲げ強度（上限）
     KM03.MAGE_TAN  = 0;               // 曲げ強度（単位）
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC硬度 圧面（下限）
     KM03.HSC_A_MAX = Edt10->Value;    // HsC硬度 圧面（上限）
     KM03.HSC_S_MIN = Edt11->Value;    // HsC硬度 側面（下限）
     KM03.HSC_S_MAX = Edt12->Value;    // HsC硬度 側面（上限）
     KM03.HSD_A_MIN = Edt13->Value;    // HsD硬度 圧面（下限）
     KM03.HSD_A_MAX = Edt14->Value;    // HsD硬度 圧面（上限）
     KM03.HSD_S_MIN = Edt15->Value;    // HsD硬度 側面（下限）
     KM03.HSD_S_MAX = Edt16->Value;    // HsD硬度 側面（上限）
     KM03.UPDCHR    = USER_COD;        // 更新者
     if( SGr1->Cells[18][SGr1->Row] == "" ){
        KM03.UPDCNT  = 0;
     }
     else{
        KM03.UPDCNT  = StrToInt(SGr1->Cells[18][SGr1->Row]) ;        // 更新回数
     }

     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // グリッドの一行を削除します。
         SGr1->Cells[1][i]  = SGr1->Cells[1][i+1];        // 材質名称
         SGr1->Cells[2][i]  = SGr1->Cells[2][i+1];        // 材質コード
         SGr1->Cells[3][i]  = SGr1->Cells[3][i+1];        // 母体比重（下限）
         SGr1->Cells[4][i]  = SGr1->Cells[4][i+1];        // 母体比重（上限）
         SGr1->Cells[5][i]  = SGr1->Cells[5][i+1];        // 固有抵抗率（下限）
         SGr1->Cells[6][i]  = SGr1->Cells[6][i+1];        // 固有抵抗率（上限）
         SGr1->Cells[7][i]  = SGr1->Cells[7][i+1];        // 曲げ強度（下限）
         SGr1->Cells[8][i]  = SGr1->Cells[8][i+1];        // 曲げ強度（上限）
         SGr1->Cells[9][i]  = SGr1->Cells[9][i+1];        // 曲げ強度（単位）
         SGr1->Cells[10][i] = SGr1->Cells[10][i+1];       // HsC硬度 圧面（下限）
         SGr1->Cells[11][i] = SGr1->Cells[11][i+1];       // HsC硬度 圧面（上限）
         SGr1->Cells[12][i] = SGr1->Cells[12][i+1];       // HsC硬度 側面（下限）
         SGr1->Cells[13][i] = SGr1->Cells[13][i+1];       // HsC硬度 側面（上限）
         SGr1->Cells[14][i] = SGr1->Cells[14][i+1];       // HsD硬度 圧面（下限）
         SGr1->Cells[15][i] = SGr1->Cells[15][i+1];       // HsD硬度 圧面（上限）
         SGr1->Cells[16][i] = SGr1->Cells[16][i+1];       // HsD硬度 側面（下限）
         SGr1->Cells[17][i] = SGr1->Cells[17][i+1];       // HsD硬度 側面（上限）
         SGr1->Cells[18][i] = SGr1->Cells[18][i+1];       // 更新回数
         SGr1->Cells[19][i] = SGr1->Cells[19][i+1];       // 更新日
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
         case VK_UP:  if( SGr1->Focused() || CmbBox1->Focused() )   break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_DOWN:if( SGr1->Focused() || CmbBox1->Focused() )   break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  // 検索部にフォーカスがある場合は、検索実行
                      if( EdtCOD1->Focused() || EdtCOD2->Focused() ){
                          BtnF07Click(Sender);
                      }
                      // 検索部以外にフォーカスがある場合は、検索部にセットフォーカス
                      else{
                          EdtCOD1->SetFocus();
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
                    Edt16->SetFocus();
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
                if(Edt6->Focused() && Edt6->SelStart == 0 && Edt6->SelLength == 0 ){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == 0 && Edt7->SelLength == 0 ){
                    Edt6->SetFocus();
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == 0 && Edt8->SelLength == 0 ){
                    Edt7->SetFocus();
                    break;
                }
                if(CmbBox1->Focused() && CmbBox1->SelStart == 0 && CmbBox1->SelLength == 0 && Key == VK_LEFT ){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt9->Focused() && Edt9->SelStart == 0 && Edt9->SelLength == 0 ){
                    CmbBox1->SetFocus();
                    break;
                }
                if(Edt10->Focused() && Edt10->SelStart == 0 && Edt10->SelLength == 0 ){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt11->Focused() && Edt11->SelStart == 0 && Edt11->SelLength == 0 ){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt12->Focused() && Edt12->SelStart == 0 && Edt12->SelLength == 0 ){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt13->Focused() && Edt13->SelStart == 0 && Edt13->SelLength == 0 ){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt14->Focused() && Edt14->SelStart == 0 && Edt14->SelLength == 0 ){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt15->Focused() && Edt15->SelStart == 0 && Edt15->SelLength == 0 ){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt16->Focused() && Edt16->SelStart == 0 && Edt16->SelLength == 0 ){
                    Edt15->SetFocus();
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
                    Edt6->SetFocus();
                    break;
                }
                if(Edt6->Focused() && Edt6->SelStart == Edt6->Text.Length() && Edt6->SelLength == 0 ){
                    Edt7->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == Edt7->Text.Length() && Edt7->SelLength == 0 ){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == Edt8->Text.Length() && Edt8->SelLength == 0 ){
                    CmbBox1->SetFocus();
                    break;
                }
                if(CmbBox1->Focused() && CmbBox1->SelStart == CmbBox1->Text.Length() && CmbBox1->SelLength == 0 && Key == VK_RIGHT ){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt9->Focused() && Edt9->SelStart == Edt9->Text.Length() && Edt9->SelLength == 0 ){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt10->Focused() && Edt10->SelStart == Edt10->Text.Length() && Edt10->SelLength == 0 ){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt11->Focused() && Edt11->SelStart == Edt11->Text.Length() && Edt11->SelLength == 0 ){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt12->Focused() && Edt12->SelStart == Edt12->Text.Length() && Edt12->SelLength == 0 ){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt13->Focused() && Edt13->SelStart == Edt13->Text.Length() && Edt13->SelLength == 0 ){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt14->Focused() && Edt14->SelStart == Edt14->Text.Length() && Edt14->SelLength == 0 ){
                    Edt15->SetFocus();
                    break;
                }
                if(Edt15->Focused() && Edt15->SelStart == Edt15->Text.Length() && Edt15->SelLength == 0 ){
                    Edt16->SetFocus();
                    break;
                }
                if(Edt16->Focused() && Edt16->SelStart == Edt16->Text.Length() && Edt16->SelLength == 0 ){
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD1->Focused()){
                    EdtCOD2->SetFocus();
                    break;
                }
                if(EdtCOD2->Focused()){
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
                    Edt6->SetFocus();
                    break;
                }
                if(Edt6->Focused()){
                    Edt7->SetFocus();
                    break;
                }
                if(Edt7->Focused()){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused()){
                    CmbBox1->SetFocus();
                    break;
                }
                if(CmbBox1->Focused()){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt9->Focused()){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt10->Focused()){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt11->Focused()){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt12->Focused()){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt13->Focused()){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt14->Focused()){
                    Edt15->SetFocus();
                    break;
                }
                if(Edt15->Focused()){
                    Edt16->SetFocus();
                    break;
                }
                if(Edt16->Focused()){
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
    // 材質名称
    Edt1->Text = SGr1->Cells[1][ARow];
    // 材質コード
    Edt2->Text = SGr1->Cells[2][ARow];
    // 母体比重（下限）
    Edt3->Text = SGr1->Cells[3][ARow];
    // 母体比重（上限）
    Edt4->Text = SGr1->Cells[4][ARow];
    // 固有抵抗率（下限）
    Edt5->Text = SGr1->Cells[5][ARow];
    // 固有抵抗率（上限）
    Edt6->Text = SGr1->Cells[6][ARow];
    // 曲げ強度（下限）
    Edt7->Text = SGr1->Cells[7][ARow];
    // 曲げ強度（上限）
    Edt8->Text = SGr1->Cells[8][ARow];
    // 曲げ強度（単位）
    if( SGr1->Cells[9][ARow].UpperCase() == "KGF/CM2" )   CmbBox1->ItemIndex = 0;     // kgf/cm2
    if( SGr1->Cells[9][ARow].UpperCase() == "N/CM2"   )   CmbBox1->ItemIndex = 1;     // N/cm2
    if( SGr1->Cells[9][ARow].UpperCase() == "N/MM2"   )   CmbBox1->ItemIndex = 3;     // N/mm2
    if( SGr1->Cells[9][ARow].UpperCase() == "MPA"     )   CmbBox1->ItemIndex = 2;     // MPa
    // HsC硬度 圧面（下限）
    Edt9->Text = SGr1->Cells[10][ARow];
    // HsC硬度 圧面（上限）
    Edt10->Text = SGr1->Cells[11][ARow];
    // HsC硬度 側面（下限）
    Edt11->Text = SGr1->Cells[12][ARow];
    // HsC硬度 側面（上限）
    Edt12->Text = SGr1->Cells[13][ARow];
    // HsD硬度 圧面（下限）
    Edt13->Text = SGr1->Cells[14][ARow];
    // HsD硬度 圧面（上限）
    Edt14->Text = SGr1->Cells[15][ARow];
    // HsD硬度 側面（下限）
    Edt15->Text = SGr1->Cells[16][ARow];
    // HsD硬度 側面（上限）
    Edt16->Text = SGr1->Cells[17][ARow];

}

//---------------------------------------------------------------------------
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
     sBuf = "select ZISNAM from KM03 where ZISNAM='";
     sBuf += KM03.ZISNAM + "'";        // 材質名称

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
     sBuf = "insert into KM03(ZISNAM,ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,";
     sBuf += "MAGE_MIN,MAGE_MAX,MAGE_TAN,HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,";
     sBuf += "HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT)";
     sBuf += " values('";
     sBuf += KM03.ZISNAM                + "','";    // 材質名称
     sBuf += KM03.ZISCOD                + "'," ;    // 材質コード
     sBuf += FloatToStr(KM03.BOTAI_MIN) +  "," ;    // 母体比重（下限）
     sBuf += FloatToStr(KM03.BOTAI_MAX) +  "," ;    // 母体比重（上限）
     sBuf += IntToStr(KM03.KOYU_MIN)    +  "," ;    // 固有抵抗率（下限）
     sBuf += IntToStr(KM03.KOYU_MAX)    +  "," ;    // 固有抵抗率（上限）
     sBuf += FloatToStr(KM03.MAGE_MIN)  +  "," ;    // 曲げ強度（下限）
     sBuf += FloatToStr(KM03.MAGE_MAX)  +  "," ;    // 曲げ強度（上限）
     sBuf += FloatToStr(KM03.MAGE_TAN)  +  "," ;    // 曲げ強度（単位）
     sBuf += IntToStr(KM03.HSC_A_MIN)   +  "," ;    // HsC硬度 圧面（下限）
     sBuf += IntToStr(KM03.HSC_A_MAX)   +  "," ;    // HsC硬度 圧面（上限）
     sBuf += IntToStr(KM03.HSC_S_MIN)   +  "," ;    // HsC硬度 側面（下限）
     sBuf += IntToStr(KM03.HSC_S_MAX)   +  "," ;    // HsC硬度 側面（上限）
     sBuf += FloatToStr(KM03.HSD_A_MIN) +  "," ;    // HsD硬度 圧面（下限）
     sBuf += FloatToStr(KM03.HSD_A_MAX) +  "," ;    // HsD硬度 圧面（上限）
     sBuf += FloatToStr(KM03.HSD_S_MIN) +  "," ;    // HsD硬度 側面（下限）
     sBuf += FloatToStr(KM03.HSD_S_MAX) +  ",'";    // HsD硬度 側面（上限）
     sBuf += KM03.ADDYMD                + "','";    // 登録日
     sBuf += KM03.ADDTIM                + "'," ;    // 登録時間
     sBuf += IntToStr(KM03.UPDCHR)      +  "," ;    // 更新者
     sBuf += IntToStr(KM03.UPDCNT)      +  ")" ;    // 更新回数

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
bool __fastcall TForm1::CollectData(String OldKey1, String OldKey2)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ文作成
     sBuf = "update KM03 set ";
     sBuf = sBuf + "ZISNAM='"    + KM03.ZISNAM                + "', ";  // 材質名称
     sBuf = sBuf + "ZISCOD='"    + KM03.ZISCOD                + "', ";  // 材質コード
     sBuf = sBuf + "BOTAI_MIN="  + FloatToStr(KM03.BOTAI_MIN) +  ", ";  // 母体比重（下限）
     sBuf = sBuf + "BOTAI_MAX="  + FloatToStr(KM03.BOTAI_MAX) +  ", ";  // 母体比重（上限）
     sBuf = sBuf + "KOYU_MIN="   + IntToStr(KM03.KOYU_MIN)    +  ", ";  // 固有抵抗率（下限）
     sBuf = sBuf + "KOYU_MAX="   + IntToStr(KM03.KOYU_MAX)    +  ", ";  // 固有抵抗率（上限）
     sBuf = sBuf + "MAGE_MIN="   + FloatToStr(KM03.MAGE_MIN)  +  ", ";  // 曲げ強度（下限）
     sBuf = sBuf + "MAGE_MAX="   + FloatToStr(KM03.MAGE_MAX)  +  ", ";  // 曲げ強度（上限）
     sBuf = sBuf + "MAGE_TAN="   + FloatToStr(KM03.MAGE_TAN)  +  ", ";  // 曲げ強度（単位）
     sBuf = sBuf + "HSC_A_MIN="  + IntToStr(KM03.HSC_A_MIN)   +  ", ";  // HsC硬度 圧面（下限）
     sBuf = sBuf + "HSC_A_MAX="  + IntToStr(KM03.HSC_A_MAX)   +  ", ";  // HsC硬度 圧面（上限）
     sBuf = sBuf + "HSC_S_MIN="  + IntToStr(KM03.HSC_S_MIN)   +  ", ";  // HsC硬度 側面（下限）
     sBuf = sBuf + "HSC_S_MAX="  + IntToStr(KM03.HSC_S_MAX)   +  ", ";  // HsC硬度 側面（上限）
     sBuf = sBuf + "HSD_A_MIN="  + FloatToStr(KM03.HSD_A_MIN) +  ", ";  // HsD硬度 圧面（下限）
     sBuf = sBuf + "HSD_A_MAX="  + FloatToStr(KM03.HSD_A_MAX) +  ", ";  // HsD硬度 圧面（上限）
     sBuf = sBuf + "HSD_S_MIN="  + FloatToStr(KM03.HSD_S_MIN) +  ", ";  // HsD硬度 側面（下限）
     sBuf = sBuf + "HSD_S_MAX="  + FloatToStr(KM03.HSD_S_MAX) +  ", ";  // HsD硬度 側面（上限）
     sBuf = sBuf + "UPDYMD='"    + KM03.UPDYMD                + "', ";  // 登録日
     sBuf = sBuf + "UPDTIM='"    + KM03.UPDTIM                + "', ";  // 登録時間
     sBuf = sBuf + "UPDCHR="     + IntToStr(KM03.UPDCHR)      +  ", ";  // 更新者
     sBuf = sBuf + "UPDCNT="     + IntToStr(KM03.UPDCNT)      +  " " ;  // 更新回数
     sBuf = sBuf + "where ZISNAM='" + OldKey1 + "' and ZISCOD='";       // 材質コード
     sBuf += OldKey2 + "'";                                             // 材質名称

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
     sBuf = "select ZISNAM from KM03 where ZISNAM='";
     sBuf += KM03.ZISNAM + "' and ZISCOD='";        // 材質名称
     sBuf += KM03.ZISCOD + "'";                     // 材質コード

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

        if( Query1->Eof == True && Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "該当の材質が見つかりません。削除できませんでした。";
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
     sBuf = "delete from KM03 where ZISCOD='";
     sBuf += KM03.ZISCOD + "' and ZISNAM='";        // 材質コード
     sBuf += KM03.ZISNAM + "'";                     // 材質名称

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


