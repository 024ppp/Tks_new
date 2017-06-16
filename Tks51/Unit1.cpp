//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
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
     int i;

     Database1->Open();

     // グリッドの初期化
     SGr1->ColWidths[0] = Panel8->Width;
     SGr1->ColWidths[1] = Panel19->Width;
     SGr1->ColWidths[2] = Panel12->Width;
     SGr1->ColWidths[3] = Panel13->Width;
     SGr1->ColWidths[4] = Panel22->Width;
     SGr1->ColWidths[5] = Panel14->Width;
     SGr1->ColWidths[6] = Panel15->Width;
     SGr1->ColWidths[7] = Panel18->Width;
     SGr1->ColWidths[8] = Panel25->Width;
     SGr1->ColWidths[9] = Panel17->Width;
     //2002/11/11 E.Takase
     SGr1->ColWidths[10] = Panel3->Width;

     //2002/11/11 E.Takase
     //for( i=10; i<64; i++) {
     for( i=11; i<69; i++) {
         SGr1->ColWidths[i] = 0;
     }

     // 各コントロールの初期化
     InitEdt();

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
// 「Ｆ１：一覧検索」
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    Form2->ShowModal();
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
    Form1->Print();
}


//---------------------------------------------------------------------------
// 「Ｆ６：印刷」
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;
    Form3->QuickRep1->Preview();
//    Form3->QuickRep1->Print();
}


//---------------------------------------------------------------------------
// 「Ｆ７：検索」
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int i;
     int cnt;
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
     sBuf = "select DTKSCOD,DTKSHIN,HINBAN,ZISNAM,ZISCOD,SYOSCOD,SORTKEY,KEIJKBN,";
     sBuf = sBuf + "SK_LD_LNG, SK_BURASI, SK_BURASIT, SK_LD_TR, SK_LD_HP, SK_BOTAI, SK_KOYU, ";
     sBuf = sBuf + "SK_MAGE, SK_HSC_A, SK_HSC_S, SK_HSD_A, SK_HSD_S, SK_ZAKUT, HIST_SOKUT, ";
     sBuf = sBuf + "HIST_KIKAK, HIST_MIN, HIST_MAX, LD_LNG_MIN, LD_LNG_MAX, BURASI_MIN, BURASI_MAX, ";
     sBuf = sBuf + "BURASIT_MIN, BURASIT_MAX, LD_TR_DENA, LD_TR_DENR, LD_TR_TIME, LD_HP_KYO, ";
     sBuf = sBuf + "LD_HP_TAN, LD_HP_SPD, BOTAI_MIN, BOTAI_MAX, KOYU_MIN, KOYU_MAX, KOYU_DEN, ";
     sBuf = sBuf + "KOYU_PRO, MAGE_MIN, MAGE_MAX, MAGE_TAN, MAGE_SPAN, HSC_A_MIN, HSC_A_MAX, ";
     sBuf = sBuf + "HSC_S_MIN, HSC_S_MAX, HSD_A_MIN, HSD_A_MAX, HSD_S_MIN, HSD_S_MAX, ZAKUT_MIN, ";
     sBuf = sBuf + "ZAKUT_MAX, ADDYMD, UPDYMD, UPDCNT, DTKSNAM, LD_TR_TYPE, REVCNT, UPDCHR, ";
     sBuf = sBuf + "MEMO, ADDTIM, UPDTIM,";
     sBuf = sBuf + "SK_MAGEG, MAGEG_MIN, MAGEG_MAX, MAGEG_TAN, MAGEG_SPAN ";
     sBuf = sBuf + " from KM02";


     if( EdtCOD1->Text != "" || EdtCOD2->Text != "" || EdtCOD3->Text != "" || EdtCOD4->Text != "" ){
         sBuf += " where";
         cnt = 0;
         if( EdtCOD1->Text != "" ){
             // 得意先コード
             sBuf += " DTKSCOD like '";
             sBuf += EdtCOD1->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD2->Text != "" ){
             // 得意先品番
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " DTKSHIN like '";
             sBuf += EdtCOD2->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD3->Text != "" ){
             // 自社品番
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " HINBAN like '";
             sBuf += EdtCOD3->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD4->Text != "" ){
             // 材質名称
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " ZISNAM like '";
             sBuf += EdtCOD4->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         //2002/11/11 E.Takase
         //履歴を表示するか？
         if ( CheckBoxRireki->Checked == false) {
            if( cnt >= 1 ) sBuf += " and";
            sBuf += " REVCNT = 0";
         }

     } else {

         //2002/11/11 E.Takase
         //履歴を表示するか？
         if ( CheckBoxRireki->Checked == false) {
            sBuf += " Where";
            sBuf += " REVCNT = 0";
         }

     }


     sBuf = sBuf + " order by DTKSCOD, DTKSHIN, REVCNT";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     SGr1->Tag = 1;

     iRow = 0;
     while( !Query1->Eof ){

          // グリッドの最大行数が超えていないかチェックする
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // グリッドにデータをセットします。

          // NO
          sBuf = iRow + 1;
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
          // 得意先コード
          SGr1->Cells[1][iRow] = Query1->Fields->Fields[0]->AsString;
          // 得意先品番
          SGr1->Cells[2][iRow] = Query1->Fields->Fields[1]->AsString;
          // 自社品番
          SGr1->Cells[3][iRow] = Query1->Fields->Fields[2]->AsString;
          // 材質名称
          SGr1->Cells[4][iRow] = Query1->Fields->Fields[3]->AsString;
          // 材質コード
          SGr1->Cells[5][iRow] = Query1->Fields->Fields[4]->AsString;
          // 焼成コード
          SGr1->Cells[6][iRow] = Query1->Fields->Fields[5]->AsString;
          // ソートＫｅｙ
          sBuf = IntToStr(Query1->Fields->Fields[6]->AsInteger);
          SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;
          // 形状区分
          switch( Query1->Fields->Fields[7]->AsInteger ){
              case  5: sBuf = "コンミ"; break;  //2002.10.21 Add By Takase
              case  4: sBuf = "円柱";   break;
              case  3: sBuf = "大型";   break;
              case  2: sBuf = "中型";   break;
              case  1:
              default: sBuf = "小型";   break;
          }
          SGr1->Cells[8][iRow] = sBuf;

          // 測定区分　線長さ
          //2002/11/11 E.Takase SGr1->Cells[10][iRow] = Query1->Fields->Fields[8]->AsString;
          SGr1->Cells[64][iRow] = Query1->Fields->Fields[8]->AsString;
          // 測定区分　ブラシ幅
          SGr1->Cells[11][iRow] = Query1->Fields->Fields[9]->AsString;
          // 測定区分　ブラシ幅縦押し
          SGr1->Cells[12][iRow] = Query1->Fields->Fields[10]->AsString;
          // 測定区分　線取付抵抗
          SGr1->Cells[13][iRow] = Query1->Fields->Fields[11]->AsString;
          // 測定区分　線引張強度
          SGr1->Cells[14][iRow] = Query1->Fields->Fields[12]->AsString;
          // 測定区分　母体比重
          SGr1->Cells[15][iRow] = Query1->Fields->Fields[13]->AsString;
          // 測定区分　固有抵抗
          SGr1->Cells[16][iRow] = Query1->Fields->Fields[14]->AsString;
          // 測定区分　抗折力
          SGr1->Cells[17][iRow] = Query1->Fields->Fields[15]->AsString;
          // 測定区分　HsC硬度（圧面）
          SGr1->Cells[18][iRow] = Query1->Fields->Fields[16]->AsString;
          // 測定区分　HsC硬度（側面）
          SGr1->Cells[19][iRow] = Query1->Fields->Fields[17]->AsString;
          // 測定区分　HsD硬度（圧面）
          SGr1->Cells[20][iRow] = Query1->Fields->Fields[18]->AsString;
          // 測定区分　HsD硬度（側面）
          SGr1->Cells[21][iRow] = Query1->Fields->Fields[19]->AsString;
          // 測定区分　座屈
          SGr1->Cells[22][iRow] = Query1->Fields->Fields[20]->AsString;
          // ヒストグラム（測定数）
          SGr1->Cells[23][iRow] = Query1->Fields->Fields[21]->AsString;
          // ヒストグラム（規格）
          SGr1->Cells[24][iRow] = Query1->Fields->Fields[22]->AsString;
          // ヒストグラム（下限）
          SGr1->Cells[25][iRow] = Query1->Fields->Fields[23]->AsString;
          // ヒストグラム（上限）
          SGr1->Cells[26][iRow] = Query1->Fields->Fields[24]->AsString;
          // リード線長さ（下限）
          SGr1->Cells[27][iRow] = Query1->Fields->Fields[25]->AsString;
          // リード線長さ（上限）
          SGr1->Cells[28][iRow] = Query1->Fields->Fields[26]->AsString;
          // ブラシ幅（下限）
          SGr1->Cells[29][iRow] = Query1->Fields->Fields[27]->AsString;
          // ブラシ幅（上限）
          SGr1->Cells[30][iRow] = Query1->Fields->Fields[28]->AsString;
          // ブラシ幅縦押し（下限）
          SGr1->Cells[31][iRow] = Query1->Fields->Fields[29]->AsString;
          // ブラシ幅縦押し（上限）
          SGr1->Cells[32][iRow] = Query1->Fields->Fields[30]->AsString;
          // リード取付抵抗（電圧）
          SGr1->Cells[33][iRow] = Query1->Fields->Fields[31]->AsString;
          // リード取付抵抗（電流）
          SGr1->Cells[34][iRow] = Query1->Fields->Fields[32]->AsString;
          // リード取付抵抗（時間）
          SGr1->Cells[35][iRow] = Query1->Fields->Fields[33]->AsString;
          // リード線引張強度
          SGr1->Cells[36][iRow] = Query1->Fields->Fields[34]->AsString;
          // リード線引張強度（単位）
          SGr1->Cells[37][iRow] = Query1->Fields->Fields[35]->AsString;
          // リード線引張強度（速度）
          SGr1->Cells[38][iRow] = Query1->Fields->Fields[36]->AsString;
          // 母体比重（下限）
          SGr1->Cells[39][iRow] = Query1->Fields->Fields[37]->AsString;
          // 母体比重（上限）
          SGr1->Cells[40][iRow] = Query1->Fields->Fields[38]->AsString;
          // 固有抵抗率（下限）
          SGr1->Cells[41][iRow] = Query1->Fields->Fields[39]->AsString;
          // 固有抵抗率（上限）
          SGr1->Cells[42][iRow] = Query1->Fields->Fields[40]->AsString;
          // 固有抵抗率（電流）
          SGr1->Cells[43][iRow] = Query1->Fields->Fields[41]->AsString;
          // 固有抵抗率（プローブ）
          SGr1->Cells[44][iRow] = Query1->Fields->Fields[42]->AsString;
          // 曲げ強度（下限）
          SGr1->Cells[45][iRow] = Query1->Fields->Fields[43]->AsString;
          // 曲げ強度（上限）
          SGr1->Cells[46][iRow] = Query1->Fields->Fields[44]->AsString;
          // 曲げ強度（単位）
          SGr1->Cells[47][iRow] = Query1->Fields->Fields[45]->AsString;
          // 曲げ強度（スパン）
          SGr1->Cells[48][iRow] = Query1->Fields->Fields[46]->AsString;
          // HsC硬度 圧面（下限）
          SGr1->Cells[49][iRow] = Query1->Fields->Fields[47]->AsString;
          // HsC硬度 圧面（上限）
          SGr1->Cells[50][iRow] = Query1->Fields->Fields[48]->AsString;
          // HsC硬度 側面（下限）
          SGr1->Cells[51][iRow] = Query1->Fields->Fields[49]->AsString;
          // HsC硬度 側面（上限）
          SGr1->Cells[52][iRow] = Query1->Fields->Fields[50]->AsString;
          // HsD硬度 圧面（下限）
          SGr1->Cells[53][iRow] = Query1->Fields->Fields[51]->AsString;
          // HsD硬度 圧面（上限）
          SGr1->Cells[54][iRow] = Query1->Fields->Fields[52]->AsString;
          // HsD硬度 側面（下限）
          SGr1->Cells[55][iRow] = Query1->Fields->Fields[53]->AsString;
          // HsD硬度 側面（上限）
          SGr1->Cells[56][iRow] = Query1->Fields->Fields[54]->AsString;
          // 座屈（下限）
          SGr1->Cells[57][iRow] = Query1->Fields->Fields[55]->AsString;
          // 座屈（上限）
          SGr1->Cells[58][iRow] = Query1->Fields->Fields[56]->AsString;
          // 登録日
          SGr1->Cells[59][iRow] = Query1->Fields->Fields[57]->AsString;
          // 変更日
          SGr1->Cells[60][iRow] = Query1->Fields->Fields[58]->AsString;
          // 更新回数
          SGr1->Cells[61][iRow] = Query1->Fields->Fields[59]->AsString;
          // 得意先名称
          SGr1->Cells[62][iRow] = Query1->Fields->Fields[60]->AsString;
          // リード取付抵抗（TYPE）
          SGr1->Cells[63][iRow] = Query1->Fields->Fields[61]->AsString;

          // 更新日
          //2002/11/19 E.Takase
          //改訂番号が「0」なら登録日
          //それ以外なら変更日を表示
          //if( SGr1->Cells[61][iRow] != "" ) {               // 更新回数
          //   if( StrToInt(SGr1->Cells[61][iRow]) > 0 )
          //      sBuf = SGr1->Cells[60][iRow];               // 変更日
          //   else
          //      sBuf = SGr1->Cells[59][iRow];               // 登録日
          //}
          //else{
          //   sBuf = SGr1->Cells[59][iRow];                  // 登録日
          //}
          if( Trim(SGr1->Cells[60][iRow]) == "" ) {
             sBuf = SGr1->Cells[59][iRow];                    // 登録日
          }
          else{
             sBuf = SGr1->Cells[60][iRow];                    // 変更日
          }
          sBuf = sBuf.Insert("/",5);
          sBuf = sBuf.Insert("/",8);
          SGr1->Cells[9][iRow] = sBuf;

          //2002/11/11 E.Takase
          // 改訂番号
          SGr1->Cells[10][iRow] = Query1->Fields->Fields[62]->AsString;
          // 更新者
          SGr1->Cells[65][iRow] = Query1->Fields->Fields[63]->AsString;
          // 備考
          SGr1->Cells[66][iRow] = Query1->Fields->Fields[64]->AsString;
          // 登録時間
          SGr1->Cells[67][iRow] = Query1->Fields->Fields[65]->AsString;
          // 更新時間
          SGr1->Cells[68][iRow] = Query1->Fields->Fields[66]->AsString;

          //2002/12/04 E.Takase
          // 測定区分　現物曲げ強度
          SGr1->Cells[69][iRow] = Query1->Fields->Fields[67]->AsString;
          // 現物曲げ強度（下限）
          SGr1->Cells[70][iRow] = Query1->Fields->Fields[68]->AsString;
          // 現物曲げ強度（上限）
          SGr1->Cells[71][iRow] = Query1->Fields->Fields[69]->AsString;
          // 現物曲げ強度（単位）
          SGr1->Cells[72][iRow] = Query1->Fields->Fields[70]->AsString;
          // 現物曲げ強度（スパン）
          SGr1->Cells[73][iRow] = Query1->Fields->Fields[71]->AsString;

          // カーソルを次にセットする
          Query1->Next();

          iRow += 1;
     }

     SGr1->Tag = 0;

     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

     /*
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
     */
         // グリッドを選択
         SGr1SelectCell( Sender, 1, 0, true);
         SGr1->Row = 0;
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

     //}

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
     bool fNG;
     AnsiString sBuf;

     if( !BtnF08->Enabled )    return;

     if( Edt03->Text == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "必須項目を入力して下さい。";
        SBr1->Update();
        Beep();
        return;
     }

     // 値チェック
	 fNG = false;
     if( !(Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0) && Edt10->Value > 0 )	fNG = true;
	 if( !(EdtA1->Value < EdtA2->Value) && ChkBoxA->Checked )   fNG = true;
     if( !(EdtB1->Value < EdtB2->Value) && ChkBoxB->Checked )	fNG = true;
     if( !(EdtC1->Value < EdtC2->Value) && ChkBoxC->Checked )	fNG = true;
     if( !(EdtD1->Value < EdtD2->Value) && ChkBoxD->Checked )	fNG = true;
     if( !(EdtG1->Value < EdtG2->Value) && ChkBoxG->Checked )	fNG = true;
     if( !(EdtH1->Value < EdtH2->Value) && ChkBoxH->Checked )	fNG = true;
     if( !(EdtI1->Value < EdtI2->Value) && ChkBoxI->Checked )	fNG = true;
     if( !(EdtJ1->Value < EdtJ2->Value) && ChkBoxJ->Checked )	fNG = true;
     if( !(EdtK1->Value < EdtK2->Value) && ChkBoxK->Checked )	fNG = true;
     if( !(EdtL1->Value < EdtL2->Value) && ChkBoxL->Checked )	fNG = true;
     if( !(EdtM1->Value < EdtM2->Value) && ChkBoxM->Checked )	fNG = true;
     if( fNG == true ){
        SBr1->Panels->Items[0]->Text = "規格の範囲を指定し直してください。";
        SBr1->Update();
        Beep();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // データをバッファに格納します。
     //2002/11/22 「'」→「_」に置換 E.Takase
	 if( Edt01->Text != "" ) Edt01->Text = StrReplace(Edt01->Text , "'", "_");
	 if( Edt02->Text != "" ) Edt02->Text = StrReplace(Edt02->Text , "'", "_");
	 if( Edt03->Text != "" ) Edt03->Text = StrReplace(Edt03->Text , "'", "_");
	 if( Edt04->Text != "" ) Edt04->Text = StrReplace(Edt04->Text , "'", "_");
     if( Edt05->Text != "" ) Edt05->Text = StrReplace(Edt05->Text , "'", "_");
	 if( Edt06->Text != "" ) Edt06->Text = StrReplace(Edt06->Text , "'", "_");

     if( Edt01->Text == "" )  KM02.DTKSCOD = " ";               // 得意先コード
     else                     KM02.DTKSCOD = Edt01->Text ;      // 得意先コード
     if( Edt02->Text == "" )  KM02.DTKSNAM = " " ;              // 得意先名称
     else                     KM02.DTKSNAM = Edt02->Text ;      // 得意先名称
     if( Edt03->Text == "" )  KM02.DTKSHIN = " " ;              // 得意先品番
     else                     KM02.DTKSHIN = Edt03->Text ;      // 得意先品番
     if( Edt04->Text == "" )  KM02.HINBAN  = " " ;              // 自社品番
     else                     KM02.HINBAN  = Edt04->Text ;      // 自社品番
     if( Edt05->Text == "" )  KM02.ZISNAM  = " " ;              // 材質名称
     else                     KM02.ZISNAM  = Edt05->Text ;      // 材質名称
     if( Edt06->Text == "" )  KM02.ZISCOD  = " " ;              // 材質コード
     else                     KM02.ZISCOD  = Edt06->Text ;      // 材質コード
     if( Edt07->Text == "" )  KM02.SYOSCOD = " " ;              // 焼成コード
     else                     KM02.SYOSCOD = Edt07->Text ;      // 焼成コード

     KM02.SORTKEY = Edt08->Value ;                              // ソートキー
     KM02.KEIJKBN = 0            ;                              // 形状区分
     if( ComBox09->Text == "中型" ) KM02.KEIJKBN = 2;
     if( ComBox09->Text == "大型" ) KM02.KEIJKBN = 3;
     if( ComBox09->Text == "円柱" ) KM02.KEIJKBN = 4;
     if( ComBox09->Text == "コンミ" ) KM02.KEIJKBN = 5;         // 2002.10.21 Add By takase
     if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
     if( ChkBoxA->Checked ) KM02.SK_LD_LNG  = ChkEdtA->Value ;  // 測定区分　線長さ
     else                   KM02.SK_LD_LNG  = 0 ;
     if( ChkBoxB->Checked ) KM02.SK_BURASI  = ChkEdtB->Value ;  // 測定区分　ブラシ幅
     else                   KM02.SK_BURASI  = 0 ;
     if( ChkBoxC->Checked ) KM02.SK_BURASIT = ChkEdtC->Value ;  // 測定区分　ブラシ幅縦押し
     else                   KM02.SK_BURASIT = 0 ;
     if( ChkBoxD->Checked ) KM02.SK_BOTAI   = ChkEdtD->Value ;  // 測定区分　母体比重
     else                   KM02.SK_BOTAI   = 0  ;
     if( ChkBoxE->Checked ) KM02.SK_LD_HP   = ChkEdtE->Value ;  // 測定区分　線引張強度
     else                   KM02.SK_LD_HP   = 0 ;
     if( ChkBoxF->Checked ) KM02.SK_LD_TR   = ChkEdtF->Value ;  // 測定区分　線取付抵抗
     else                   KM02.SK_LD_TR   = 0 ;
     if( ChkBoxG->Checked ) KM02.SK_KOYU    = ChkEdtG->Value ;  // 測定区分　固有抵抗
     else                   KM02.SK_KOYU    = 0 ;
     if( ChkBoxH->Checked ) KM02.SK_MAGE    = ChkEdtH->Value ;  // 測定区分　抗折力
     else                   KM02.SK_MAGE    = 0 ;
     if( ChkBoxI->Checked ) KM02.SK_HSC_A   = ChkEdtI->Value ;  // 測定区分　HsC硬度（圧面）
     else                   KM02.SK_HSC_A   = 0 ;
     if( ChkBoxJ->Checked ) KM02.SK_HSC_S   = ChkEdtJ->Value ;  // 測定区分　HsC硬度（側面）
     else                   KM02.SK_HSC_S   = 0 ;
     if( ChkBoxK->Checked ) KM02.SK_HSD_A   = ChkEdtK->Value ;  // 測定区分　HsD硬度（圧面）
     else                   KM02.SK_HSD_A   = 0 ;
     if( ChkBoxL->Checked ) KM02.SK_HSD_S   = ChkEdtL->Value ;  // 測定区分　HsD硬度（側面）
     else                   KM02.SK_HSD_S   = 0 ;
     if( ChkBoxM->Checked ) KM02.SK_ZAKUT   = ChkEdtM->Value ;  // 測定区分　座屈
     else                   KM02.SK_ZAKUT   = 0 ;
     KM02.HIST_SOKUT  = Edt10->Value ;                          // ヒストグラム（測定数）
     KM02.HIST_KIKAK  = 0            ;                          // ヒストグラム（規格）
     if( ComBox11->Text  == "下限" ) KM02.HIST_KIKAK = 2;
     if( ComBox11->Text  == "上限" ) KM02.HIST_KIKAK = 3;
     if( KM02.HIST_KIKAK == 0      ) KM02.HIST_KIKAK = 1;
     KM02.HIST_MIN    = Edt12->Value ;                          // ヒストグラム（下限）
     KM02.HIST_MAX    = Edt13->Value ;                          // ヒストグラム（上限）
     KM02.LD_LNG_MIN  = EdtA1->Value ;                          // リード線長さ（下限）
     KM02.LD_LNG_MAX  = EdtA2->Value ;                          // リード線長さ（上限）
     KM02.BURASI_MIN  = EdtB1->Value ;                          // ブラシ幅（下限）
     KM02.BURASI_MAX  = EdtB2->Value ;                          // ブラシ幅（上限）
     KM02.BURASIT_MIN = EdtC1->Value ;                          // ブラシ幅縦押し（下限）
     KM02.BURASIT_MAX = EdtC2->Value ;                          // ブラシ幅縦押し（上限）
     KM02.BOTAI_MIN   = EdtD1->Value ;                          // 母体比重（下限）
     KM02.BOTAI_MAX   = EdtD2->Value ;                          // 母体比重（上限）
     KM02.LD_HP_KYO   = EdtE1->Value ;                          // リード線引張強度
     KM02.LD_HP_TAN   = 0;                                      // リード線引張強度（単位）
     sBuf = ComBoxE2->Text.UpperCase();
     if( sBuf[1] == 'K'      ) KM02.LD_HP_TAN = 1;              // Kgf
     if( KM02.LD_HP_TAN == 0 ) KM02.LD_HP_TAN = 2;              // N
     KM02.LD_HP_SPD   = EdtE3->Value ;                          // リード線引張強度（速度）
     KM02.LD_TR_DENA  = EdtF1->Value ;                          // リード取付抵抗（電圧）
     KM02.LD_TR_DENR  = EdtF2->Value ;                          // リード取付抵抗（電流）
     KM02.LD_TR_TIME  = EdtF3->Value ;                          // リード取付抵抗（時間）
     if( EdtF4->Text == "" )  KM02.LD_TR_TYPE = " " ;           // リード取付抵抗（TYPE）
     else                     KM02.LD_TR_TYPE = EdtF4->Text ;
     KM02.KOYU_MIN    = EdtG1->Value ;                          // 固有抵抗率（下限）
     KM02.KOYU_MAX    = EdtG2->Value ;                          // 固有抵抗率（上限）
     KM02.KOYU_DEN    = EdtG3->Value ;                          // 固有抵抗率（電流）
     KM02.KOYU_PRO    = EdtG4->Value ;                          // 固有抵抗率（プローブ）
     KM02.MAGE_MIN    = EdtH1->Value ;                          // 曲げ強度（下限）
     KM02.MAGE_MAX    = EdtH2->Value ;                          // 曲げ強度（上限）
     KM02.MAGE_TAN    = 0;                                      // 曲げ強度（単位）
     sBuf = ComBoxH3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGE_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGE_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGE_TAN = 3;                  // MPa
     if( KM02.MAGE_TAN == 0          ) KM02.MAGE_TAN = 4;                  // N/mm2
     KM02.MAGE_SPAN   = EdtH4->Value ;                          // 曲げ強度（スパン）
     KM02.HSC_A_MIN   = EdtI1->Value ;                          // HsC硬度 圧面（下限）
     KM02.HSC_A_MAX   = EdtI2->Value ;                          // HsC硬度 圧面（上限）
     KM02.HSC_S_MIN   = EdtJ1->Value ;                          // HsC硬度 側面（下限）
     KM02.HSC_S_MAX   = EdtJ2->Value ;                          // HsC硬度 側面（上限）
     KM02.HSD_A_MIN   = EdtK1->Value ;                          // HsD硬度 圧面（下限）
     KM02.HSD_A_MAX   = EdtK2->Value ;                          // HsD硬度 圧面（上限）
     KM02.HSD_S_MIN   = EdtL1->Value ;                          // HsD硬度 側面（下限）
     KM02.HSD_S_MAX   = EdtL2->Value ;                          // HsD硬度 側面（上限）
     KM02.ZAKUT_MIN   = EdtM1->Value ;                          // 座屈（下限）
     KM02.ZAKUT_MAX   = EdtM2->Value ;                          // 座屈（上限）
     KM02.ADDYMD      = FormatDateTime("yyyymmdd",Date());                // 登録日
     KM02.ADDTIM      = FormatDateTime("hhmm",TDateTime::CurrentTime());  // 登録時間
     KM02.UPDYMD      = "";                                     // 変更日
     KM02.UPDTIM      = "";                                     // 変更時間
     KM02.UPDCHR      = USER_COD;                               // 更新者
     KM02.UPDCNT      = 0;                                      // 更新回数

     //2002/11/11 E.Takase
     KM02.REVCNT      = 0;                                      // 更新回数
     KM02.MEMO        = Trim(EdtMEMO->Text) ;                   // 備考

     //2002/12/05 E.Takase
     if( ChkBoxN->Checked ) KM02.SK_MAGEG    = ChkEdtN->Value ;  // 測定区分　現物曲げ強度
     else                   KM02.SK_MAGEG    = 0 ;
     KM02.MAGEG_MIN    = EdtN1->Value ;                          // 現物曲げ強度（下限）
     KM02.MAGEG_MAX    = EdtN2->Value ;                          // 現物曲げ強度（上限）
     KM02.MAGEG_TAN    = 0;                                      // 現物曲げ強度（単位）
     sBuf = ComBoxN3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGEG_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGEG_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGEG_TAN = 3;                  // MPa
     //2003/07/22 E.Takase 単位に「N」追加
     if( sBuf[1] == 'N'              ) KM02.MAGEG_TAN = 5;                  // N
     if( KM02.MAGEG_TAN == 0          ) KM02.MAGEG_TAN = 4;                  // N/mm2
     KM02.MAGEG_SPAN   = EdtN4->Value ;                          // 現物曲げ強度（スパン）

     // AddData
     if( AddData() == False ){
        return;
     }

     // グリッドにデータをセットします。
     sBuf = SGr1->RowCount ;                                // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
     sBuf = KM02.DTKSCOD;                              		// 得意先コード
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.DTKSHIN;                              		// 得意先品番
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.HINBAN;                               		// 自社品番
     SGr1->Cells[3][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ZISNAM;                               		// 材質名称
     SGr1->Cells[4][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ZISCOD;                               		// 材質コード
     SGr1->Cells[5][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.SYOSCOD;                              		// 焼成コード
     SGr1->Cells[6][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SORTKEY);                         // ソートキー
     SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;
     if( KM02.KEIJKBN == 1 ) sBuf = "小型";                 // 形状区分
     if( KM02.KEIJKBN == 2 ) sBuf = "中型";
     if( KM02.KEIJKBN == 3 ) sBuf = "大型";
     if( KM02.KEIJKBN == 4 ) sBuf = "円柱";
     if( KM02.KEIJKBN == 5 ) sBuf = "コンミ";               //2002.10.21 Add By Takase
     SGr1->Cells[8][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ADDYMD;                               		// 更新日
     sBuf = sBuf.Insert("/",5);
     sBuf = sBuf.Insert("/",8);
     SGr1->Cells[9][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_LNG);                       // 測定区分　線長さ
     //2002/11/11 E.Takase SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;
     SGr1->Cells[64][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASI);                       // 測定区分　ブラシ幅
     SGr1->Cells[11][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASIT);                      // 測定区分　ブラシ幅縦押し
     SGr1->Cells[12][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_TR);                        // 測定区分　線取付抵抗
     SGr1->Cells[13][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_HP);                        // 測定区分　線引張強度
     SGr1->Cells[14][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BOTAI);                        // 測定区分　母体比重
     SGr1->Cells[15][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_KOYU);                         // 測定区分　固有抵抗
     SGr1->Cells[16][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_MAGE);                         // 測定区分　抗折力
     SGr1->Cells[17][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_A);                        // 測定区分　HsC硬度（圧面）
     SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_S);                        // 測定区分　HsC硬度（側面）
     SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_A);                        // 測定区分　HsD硬度（圧面）
     SGr1->Cells[20][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_S);                        // 測定区分　HsD硬度（側面）
     SGr1->Cells[21][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_ZAKUT);                        // 測定区分　座屈
     SGr1->Cells[22][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HIST_SOKUT);                      // ヒストグラム（測定数）
     SGr1->Cells[23][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HIST_KIKAK);                      // ヒストグラム（規格）
     SGr1->Cells[24][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MIN);                      // ヒストグラム（下限）
     SGr1->Cells[25][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MAX);                      // ヒストグラム（上限）
     SGr1->Cells[26][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MIN);                    // リード線長さ（下限）
     SGr1->Cells[27][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MAX);                    // リード線長さ（上限）
     SGr1->Cells[28][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MIN);                    // ブラシ幅（下限）
     SGr1->Cells[29][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MAX);                    // ブラシ幅（上限）
     SGr1->Cells[30][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MIN);                   // ブラシ幅縦押し（下限）
     SGr1->Cells[31][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MAX);                   // ブラシ幅縦押し（上限）
     SGr1->Cells[32][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MIN);                     // 母体比重（下限）
     SGr1->Cells[39][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MAX);                     // 母体比重（上限）
     SGr1->Cells[40][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_HP_KYO);                     // リード線引張強度
     SGr1->Cells[36][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_TAN);                       // リード線引張強度（単位）
     SGr1->Cells[37][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_SPD);                       // リード線引張強度（速度）
     SGr1->Cells[38][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_TR_DENA);                    // リード取付抵抗（電圧）
     SGr1->Cells[33][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_DENR);                      // リード取付抵抗（電流）
     SGr1->Cells[34][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_TIME);                      // リード取付抵抗（時間）
     SGr1->Cells[35][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.LD_TR_TYPE;                                // リード取付抵抗（TYPE）
     SGr1->Cells[63][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MIN);                        // 固有抵抗率（下限）
     SGr1->Cells[41][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MAX);                        // 固有抵抗率（上限）
     SGr1->Cells[42][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.KOYU_DEN);                      // 固有抵抗率（電流）
     SGr1->Cells[43][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_PRO);                        // 固有抵抗率（プローブ）
     SGr1->Cells[44][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MIN);                      // 曲げ強度（下限）
     SGr1->Cells[45][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MAX);                      // 曲げ強度（上限）
     SGr1->Cells[46][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.MAGE_TAN);                        // 曲げ強度（単位）
     SGr1->Cells[47][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_SPAN);                     // 曲げ強度（スパン）
     SGr1->Cells[48][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MIN);                       // HsC硬度 圧面（下限）
     SGr1->Cells[49][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MAX);                       // HsC硬度 圧面（上限）
     SGr1->Cells[50][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MIN);                       // HsC硬度 側面（下限）
     SGr1->Cells[51][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MAX);                       // HsC硬度 側面（上限）
     SGr1->Cells[52][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MIN);                     // HsD硬度 圧面（下限）
     SGr1->Cells[53][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MAX);                     // HsD硬度 圧面（上限）
     SGr1->Cells[54][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MIN);                     // HsD硬度 側面（下限）
     SGr1->Cells[55][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MAX);                     // HsD硬度 側面（上限）
     SGr1->Cells[56][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MIN);                       // 座屈（下限）
     SGr1->Cells[57][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MAX);                       // 座屈（上限）
     SGr1->Cells[58][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ADDYMD;                               		// 登録日
     SGr1->Cells[59][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.UPDYMD;                               		// 変更日
     SGr1->Cells[60][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.UPDCNT);                          // 更新回数
     SGr1->Cells[61][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.DTKSNAM;                              		// 得意先名称
     SGr1->Cells[62][SGr1->RowCount - 1] = sBuf;
     //2002/11/11 E.Takase
     sBuf =  IntToStr(KM02.REVCNT);                       	// 改訂番号
     SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;
     sBuf =  KM02.UPDCHR;                       	        // 更新者
     SGr1->Cells[65][SGr1->RowCount - 1] = sBuf;
     sBuf =  KM02.MEMO;                       	            // 備考
     SGr1->Cells[66][SGr1->RowCount - 1] = sBuf;

     //2002/12/05 E.Takase
     sBuf = IntToStr(KM02.SK_MAGEG);                         // 測定区分　現物曲げ強度
     SGr1->Cells[69][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MIN);                      // 現物曲げ強度（下限）
     SGr1->Cells[70][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MAX);                      // 現物曲げ強度（上限）
     SGr1->Cells[71][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.MAGEG_TAN);                        // 現物曲げ強度（単位）
     SGr1->Cells[72][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_SPAN);                     // 現物曲げ強度（スパン）
     SGr1->Cells[73][SGr1->RowCount - 1] = sBuf;

     // 一行増やす
     SGr1->RowCount = SGr1->RowCount + 1;

     // 最下行をクリアー
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // 新しい行を選択
     SGr1->Row = SGr1->RowCount - 1;

     Edt01->SetFocus();

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
     bool       fNG;

     if( !BtnF09->Enabled )    return;

     if( SGr1->Cells[2][SGr1->Row] == "" ){
        // ステータスメッセージ
        SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
        SBr1->Update();
        Beep();
        return;
     }

     // 値チェック
	 fNG = false;
     if( !(Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0) && Edt10->Value > 0 )	fNG = true;
	 if( !(EdtA1->Value < EdtA2->Value) && ChkBoxA->Checked )   fNG = true;
     if( !(EdtB1->Value < EdtB2->Value) && ChkBoxB->Checked )	fNG = true;
     if( !(EdtC1->Value < EdtC2->Value) && ChkBoxC->Checked )	fNG = true;
     if( !(EdtD1->Value < EdtD2->Value) && ChkBoxD->Checked )	fNG = true;
     if( !(EdtG1->Value < EdtG2->Value) && ChkBoxG->Checked )	fNG = true;
     if( !(EdtH1->Value < EdtH2->Value) && ChkBoxH->Checked )	fNG = true;
     if( !(EdtI1->Value < EdtI2->Value) && ChkBoxI->Checked )	fNG = true;
     if( !(EdtJ1->Value < EdtJ2->Value) && ChkBoxJ->Checked )	fNG = true;
     if( !(EdtK1->Value < EdtK2->Value) && ChkBoxK->Checked )	fNG = true;
     if( !(EdtL1->Value < EdtL2->Value) && ChkBoxL->Checked )	fNG = true;
     if( !(EdtM1->Value < EdtM2->Value) && ChkBoxM->Checked )	fNG = true;
     if( !(EdtN1->Value < EdtN2->Value) && ChkBoxN->Checked )	fNG = true;
     if( fNG == true ){
        SBr1->Panels->Items[0]->Text = "規格の範囲を指定し直してください。";
        SBr1->Update();
        Beep();
        return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     ////履歴データを作成 2002/11/11 E.Takase
     ////�@グリッドから修正前のデータを取得
     //SGr1->Tag = 1;
     //GetRirekiData(SGr1->Row);
     //
     ////�A履歴データとしてデータベースに出力
     //InsRirekiData();
     //
     ////�B「履歴データを表示する」の場合、履歴データを挿入する
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}
     //SGr1->Tag = 0;

     //履歴データを作成 2002/11/19 E.Takase
     //�@改訂番号更新
     SGr1->Tag = 1;
     UpdRirekiNo(SGr1->Row);

     //�A修正後のデータを取得 2002/11/19 E.Takase
     // データをバッファに格納します。
     GetEdtData();


     //�B修正後のデータを追加 2002/11/19 E.Takase
     // AddData

     if( AddData() == False ){
        return;
     }
     //// CollectData
     //if( CollectData(SGr1->Cells[2][SGr1->Row]) == False ){
     //   return;
     //}

     //�C改訂データを最新にする（データの挿入）
     //    ↑ 履歴表示の場合のみ
     if ( CheckBoxRireki->Checked == true) {

        InsSGrRirekiData();
     }


     //�D修正後のデータをグリッドにセットします。
     SetEdtData(SGr1->Row);

     SGr1->Tag = 0;

     /*
     // 変更日
     if ( Trim(KM02.UPDYMD) != "" ) {
        sBuf = KM02.UPDYMD;
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
     } else {
        sBuf = "";
     }
     PnlUPDYMD2->Caption = sBuf;
     // 更新回数
     sBuf = IntToStr(KM02.UPDCNT);
     PnlUPDCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;
     */

     SGr1->SetFocus();
     SGr1SelectCell(Sender,0,SGr1->Row,true) ;
     
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
     int j;
     AnsiString sBuf;


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


     ////履歴データを作成 2002/11/11 E.Takase
     ////�@グリッドから修正前のデータを取得
     //SGr1->Tag = 1;
     //GetRirekiData(SGr1->Row);
     //
     ////�A履歴データとしてデータベースに出力
     //InsRirekiData();
     //
     ////�B「履歴データを表示する」の場合、履歴データを挿入する
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}
     //SGr1->Tag = 0;

     ////履歴データを作成 2002/11/19 E.Takase
     ////�@改訂番号更新
     //SGr1->Tag = 1;
     //UpdRirekiNo(SGr1->Row);
     //
     ////�C改訂データを最新にする（データの挿入）
     ////    ↑ 履歴表示の場合のみ
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}

     SGr1->Tag = 0;
     //return;
     
     // データをバッファに格納します。
     KM02.DTKSCOD     = Edt01->Text  ;                          // 得意先コード
     KM02.DTKSNAM     = Edt02->Text  ;                          // 得意先名称
     KM02.DTKSHIN     = Edt03->Text  ;                          // 得意先品番
     KM02.HINBAN      = Edt04->Text  ;                          // 自社品番
     KM02.ZISNAM      = Edt05->Text  ;                          // 材質名称
     KM02.ZISCOD      = Edt06->Text  ;                          // 材質コード
     KM02.SYOSCOD     = Edt07->Text  ;                          // 焼成コード
     KM02.SORTKEY     = Edt08->Value ;                          // ソートキー
     KM02.KEIJKBN     = 0            ;                          // 形状区分
     if( ComBox09->Text == "中型" ) KM02.KEIJKBN = 2;
     if( ComBox09->Text == "大型" ) KM02.KEIJKBN = 3;
     if( ComBox09->Text == "円柱" ) KM02.KEIJKBN = 4;
     if( ComBox09->Text == "コンミ" ) KM02.KEIJKBN = 5;         // 2002.10.30 Add By Takase
     if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
     if( ChkBoxA->Checked ) KM02.SK_LD_LNG  = ChkEdtA->Value ;  // 測定区分　線長さ
     else                   KM02.SK_LD_LNG  = 0 ;
     if( ChkBoxB->Checked ) KM02.SK_BURASI  = ChkEdtB->Value ;  // 測定区分　ブラシ幅
     else                   KM02.SK_BURASI  = 0 ;
     if( ChkBoxC->Checked ) KM02.SK_BURASIT = ChkEdtC->Value ;  // 測定区分　ブラシ幅縦押し
     else                   KM02.SK_BURASIT = 0 ;
     if( ChkBoxD->Checked ) KM02.SK_BOTAI   = ChkEdtD->Value ;  // 測定区分　母体比重
     else                   KM02.SK_BOTAI   = 0  ;
     if( ChkBoxE->Checked ) KM02.SK_LD_HP   = ChkEdtE->Value ;  // 測定区分　線引張強度
     else                   KM02.SK_LD_HP   = 0 ;
     if( ChkBoxF->Checked ) KM02.SK_LD_TR   = ChkEdtF->Value ;  // 測定区分　線取付抵抗
     else                   KM02.SK_LD_TR   = 0 ;
     if( ChkBoxG->Checked ) KM02.SK_KOYU    = ChkEdtG->Value ;  // 測定区分　固有抵抗
     else                   KM02.SK_KOYU    = 0 ;
     if( ChkBoxH->Checked ) KM02.SK_MAGE    = ChkEdtH->Value ;  // 測定区分　抗折力
     else                   KM02.SK_MAGE    = 0 ;
     if( ChkBoxI->Checked ) KM02.SK_HSC_A   = ChkEdtI->Value ;  // 測定区分　HsC硬度（圧面）
     else                   KM02.SK_HSC_A   = 0 ;
     if( ChkBoxJ->Checked ) KM02.SK_HSC_S   = ChkEdtJ->Value ;  // 測定区分　HsC硬度（側面）
     else                   KM02.SK_HSC_S   = 0 ;
     if( ChkBoxK->Checked ) KM02.SK_HSD_A   = ChkEdtK->Value ;  // 測定区分　HsD硬度（圧面）
     else                   KM02.SK_HSD_A   = 0 ;
     if( ChkBoxL->Checked ) KM02.SK_HSD_S   = ChkEdtL->Value ;  // 測定区分　HsD硬度（側面）
     else                   KM02.SK_HSD_S   = 0 ;
     if( ChkBoxM->Checked ) KM02.SK_ZAKUT   = ChkEdtM->Value ;  // 測定区分　座屈
     else                   KM02.SK_ZAKUT   = 0 ;
     KM02.HIST_SOKUT  = Edt10->Value ;                          // ヒストグラム（測定数）
     KM02.HIST_KIKAK  = 0            ;                          // ヒストグラム（規格）
     if( ComBox11->Text  == "下限" ) KM02.HIST_KIKAK = 2;
     if( ComBox11->Text  == "上限" ) KM02.HIST_KIKAK = 3;
     if( KM02.HIST_KIKAK == 0      ) KM02.HIST_KIKAK = 1;
     KM02.HIST_MIN    = Edt12->Value ;                          // ヒストグラム（下限）
     KM02.HIST_MAX    = Edt13->Value ;                          // ヒストグラム（上限）
     KM02.LD_LNG_MIN  = EdtA1->Value ;                          // リード線長さ（下限）
     KM02.LD_LNG_MAX  = EdtA2->Value ;                          // リード線長さ（上限）
     KM02.BURASI_MIN  = EdtB1->Value ;                          // ブラシ幅（下限）
     KM02.BURASI_MAX  = EdtB2->Value ;                          // ブラシ幅（上限）
     KM02.BURASIT_MIN = EdtC1->Value ;                          // ブラシ幅縦押し（下限）
     KM02.BURASIT_MAX = EdtC2->Value ;                          // ブラシ幅縦押し（上限）
     KM02.BOTAI_MIN   = EdtD1->Value ;                          // 母体比重（下限）
     KM02.BOTAI_MAX   = EdtD2->Value ;                          // 母体比重（上限）
     KM02.LD_HP_KYO   = EdtE1->Value ;                          // リード線引張強度
     KM02.LD_HP_TAN   = 0;                                      // リード線引張強度（単位）
     sBuf = ComBoxE2->Text.UpperCase();
     if( sBuf[1] == 'K'      ) KM02.LD_HP_TAN = 1;              // Kgf
     if( KM02.LD_HP_TAN == 0 ) KM02.LD_HP_TAN = 2;              // N
     KM02.LD_HP_SPD   = EdtE3->Value ;                          // リード線引張強度（速度）
     KM02.LD_TR_DENA  = EdtF1->Value ;                          // リード取付抵抗（電圧）
     KM02.LD_TR_DENR  = EdtF2->Value ;                          // リード取付抵抗（電流）
     KM02.LD_TR_TIME  = EdtF3->Value ;                          // リード取付抵抗（時間）
     KM02.LD_TR_TYPE  = EdtF4->Text  ;                          // リード取付抵抗（TYPE）
     KM02.KOYU_MIN    = EdtG1->Value ;                          // 固有抵抗率（下限）
     KM02.KOYU_MAX    = EdtG2->Value ;                          // 固有抵抗率（上限）
     KM02.KOYU_DEN    = EdtG3->Value ;                          // 固有抵抗率（電流）
     KM02.KOYU_PRO    = EdtG4->Value ;                          // 固有抵抗率（プローブ）
     KM02.MAGE_MIN    = EdtH1->Value ;                          // 曲げ強度（下限）
     KM02.MAGE_MAX    = EdtH2->Value ;                          // 曲げ強度（上限）
     KM02.MAGE_TAN    = 0;                                      // 曲げ強度（単位）
     sBuf = ComBoxH3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGE_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGE_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGE_TAN = 3;                  // MPa
     if( KM02.MAGE_TAN == 0          ) KM02.MAGE_TAN = 4;                  // N/mm2
     KM02.MAGE_SPAN   = EdtH4->Value ;                          // 曲げ強度（スパン）
     KM02.HSC_A_MIN   = EdtI1->Value ;                          // HsC硬度 圧面（下限）
     KM02.HSC_A_MAX   = EdtI2->Value ;                          // HsC硬度 圧面（上限）
     KM02.HSC_S_MIN   = EdtJ1->Value ;                          // HsC硬度 側面（下限）
     KM02.HSC_S_MAX   = EdtJ2->Value ;                          // HsC硬度 側面（上限）
     KM02.HSD_A_MIN   = EdtK1->Value ;                          // HsD硬度 圧面（下限）
     KM02.HSD_A_MAX   = EdtK2->Value ;                          // HsD硬度 圧面（上限）
     KM02.HSD_S_MIN   = EdtL1->Value ;                          // HsD硬度 側面（下限）
     KM02.HSD_S_MAX   = EdtL2->Value ;                          // HsD硬度 側面（上限）
     KM02.ZAKUT_MIN   = EdtM1->Value ;                          // 座屈（下限）
     KM02.ZAKUT_MAX   = EdtM2->Value ;                          // 座屈（上限）
     KM02.UPDCHR      = USER_COD;                               // 更新者
     if( SGr1->Cells[61][SGr1->Row] == "" ){
        KM02.UPDCNT  = 0;
     }
     else{
        KM02.UPDCNT  = StrToInt(SGr1->Cells[61][SGr1->Row]) ;   // 更新回数
     }

     if( SGr1->Cells[10][SGr1->Row] == "" ){
        KM02.REVCNT  = 0;
     }
     else{
        KM02.REVCNT  = StrToInt(SGr1->Cells[10][SGr1->Row]) ;   // 改訂番号
     }

     //2002/12/05 E.Takase
     if( ChkBoxN->Checked ) KM02.SK_MAGEG    = ChkEdtN->Value ;  // 測定区分　現物曲げ強度
     else                   KM02.SK_MAGEG    = 0 ;
     KM02.MAGEG_MIN    = EdtN1->Value ;                          // 現物曲げ強度（下限）
     KM02.MAGEG_MAX    = EdtN2->Value ;                          // 現物曲げ強度（上限）
     KM02.MAGEG_TAN    = 0;                                      // 現物曲げ強度（単位）
     sBuf = ComBoxN3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGEG_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGEG_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGEG_TAN = 3;                  // MPa
     //2003/07/22 E.Takase 単位に「N」追加
     if( sBuf[1] == 'N'              ) KM02.MAGEG_TAN = 5;                  // N
     if( KM02.MAGEG_TAN == 0          ) KM02.MAGEG_TAN = 4;                  // N/mm2
     KM02.MAGEG_SPAN   = EdtN4->Value ;                          // 現物曲げ強度（スパン）

     // DelData
     if( DelData() == False ){
        return;
     }

     // 一行づつ移動する
     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         for( j = 1; j < SGr1->ColCount; j++) {
             SGr1->Cells[j][i]  = SGr1->Cells[j][i+1];
         }
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


//---------------------------------------------------------------------------
void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
     // 検索中は処理しません。
     if( SGr1->Tag == 1 )   return;

     AnsiString sBuf;

     //コントロール初期化
     InitEdt2(true);

     // 空白行選択なら画面クリアー
     if( SGr1->Cells[1][ARow].Trim() == "" &&    // 得意先コード
         SGr1->Cells[2][ARow].Trim() == "" ){    // 得意先品番
         InitEdt();
         return;
         BtnF08->Enabled=true;
         BtnF09->Enabled=true;
         BtnF10->Enabled=true;
         BtnF11->Enabled=true;
     }

     // 得意先コード
     Edt01->Text = SGr1->Cells[1][ARow];
     // 得意先名称
     Edt02->Text = SGr1->Cells[62][ARow];
     // 得意先品番
     Edt03->Text = SGr1->Cells[2][ARow];
     // 自社品番
     Edt04->Text = SGr1->Cells[3][ARow];
     // 材質名称
     Edt05->Text = SGr1->Cells[4][ARow];
     // 材質コード
     Edt06->Text = SGr1->Cells[5][ARow];
     // 焼成仕様コード
     Edt07->Text = SGr1->Cells[6][ARow];
     // ソートキー
     Edt08->Text = SGr1->Cells[7][ARow];
     // 形状区分
     if( !SGr1->Cells[8][ARow].AnsiCompare("小型") )   ComBox09->ItemIndex = 0;
     if( !SGr1->Cells[8][ARow].AnsiCompare("中型") )   ComBox09->ItemIndex = 1;
     if( !SGr1->Cells[8][ARow].AnsiCompare("大型") )   ComBox09->ItemIndex = 2;
     if( !SGr1->Cells[8][ARow].AnsiCompare("円柱") )   ComBox09->ItemIndex = 3;
     //2002.10.21 Add By Takase
     if( !SGr1->Cells[8][ARow].AnsiCompare("コンミ") )   ComBox09->ItemIndex = 4;
     // ヒストグラム（測定数）
     Edt10->Text = SGr1->Cells[23][ARow];
     // ヒストグラム（規格）
     if( SGr1->Cells[24][ARow] < "1" || SGr1->Cells[24][ARow] > "3" )   SGr1->Cells[24][ARow] = "1";
     switch( StrToInt(SGr1->Cells[24][ARow]) ){
         case 1: ComBox11->ItemIndex = 0;         // 両側規格
                 break;
         case 2: ComBox11->ItemIndex = 1;         // 下限規格
                 break;
         case 3: ComBox11->ItemIndex = 2;         // 上限規格
                 break;

     }
     // ヒストグラム（下限）
     Edt12->Text = SGr1->Cells[25][ARow];
     // ヒストグラム（上限）
     Edt13->Text = SGr1->Cells[26][ARow];

     // 測定区分　線長さ
     // 2002/11/11 E.Takase if( StrToInt(SGr1->Cells[10][ARow]) >= 2 ){
     if( StrToInt(SGr1->Cells[64][ARow]) >= 2 ){
         // 有効
         ChkBoxA->Checked = true;
         // 2002/11/11 E.Takase ChkEdtA->Text = SGr1->Cells[10][ARow];
         ChkEdtA->Text = SGr1->Cells[64][ARow];
         EdtStatus( ChkBoxA->Tag, true);
     }
     else{
         // 無効
         ChkBoxA->Checked = false;
         ChkEdtA->Text = "2";
         EdtStatus( ChkBoxA->Tag, false);
     }
     // 測定区分　ブラシ幅
     if( StrToInt(SGr1->Cells[11][ARow]) >= 2 ){
         ChkBoxB->Checked = true;
         ChkEdtB->Text = SGr1->Cells[11][ARow];
         EdtStatus( ChkBoxB->Tag, true);
     }
     else{
         ChkBoxB->Checked = false;
         ChkEdtB->Text = "2";
         EdtStatus( ChkBoxB->Tag, false);
     }
     // 測定区分　ブラシ幅縦押し
     if( StrToInt(SGr1->Cells[12][ARow]) >= 2 ){
         ChkBoxC->Checked = true;
         ChkEdtC->Text = SGr1->Cells[12][ARow];
         EdtStatus( ChkBoxC->Tag, true);
     }
     else{
         ChkBoxC->Checked = false;
         ChkEdtC->Text = "2";
         EdtStatus( ChkBoxC->Tag, false);
     }
     // 測定区分　母体比重
     if( StrToInt(SGr1->Cells[15][ARow]) >= 2 ){
         ChkBoxD->Checked = true;
         ChkEdtD->Text = SGr1->Cells[15][ARow];
         EdtStatus( ChkBoxD->Tag, true);
     }
     else{
         ChkBoxD->Checked = false;
         ChkEdtD->Text = "2";
         EdtStatus( ChkBoxD->Tag, false);
     }
     // 測定区分　線引張強度
     if( StrToInt(SGr1->Cells[14][ARow]) >= 2 ){
         ChkBoxE->Checked = true;
         ChkEdtE->Text = SGr1->Cells[14][ARow];
         EdtStatus( ChkBoxE->Tag, true);
     }
     else{
         ChkBoxE->Checked = false;
         ChkEdtE->Text = "2";
         EdtStatus( ChkBoxE->Tag, false);
     }
     // 測定区分　線取付抵抗
     if( StrToInt(SGr1->Cells[13][ARow]) >= 2 ){
         ChkBoxF->Checked = true;
         ChkEdtF->Text = SGr1->Cells[13][ARow];
         EdtStatus( ChkBoxF->Tag, true);
     }
     else{
         ChkBoxF->Checked = false;
         ChkEdtF->Text = "2";
         EdtStatus( ChkBoxF->Tag, false);
     }
     // 測定区分　固有抵抗
     if( StrToInt(SGr1->Cells[16][ARow]) >= 2 ){
         ChkBoxG->Checked = true;
         ChkEdtG->Text = SGr1->Cells[16][ARow];
         EdtStatus( ChkBoxG->Tag, true);
     }
     else{
         ChkBoxG->Checked = false;
         ChkEdtG->Text = "2";
         EdtStatus( ChkBoxG->Tag, false);
     }
     // 測定区分　抗折力
     if( StrToInt(SGr1->Cells[17][ARow]) >= 2 ){
         ChkBoxH->Checked = true;
         ChkEdtH->Text = SGr1->Cells[17][ARow];
         EdtStatus( ChkBoxH->Tag, true);
     }
     else{
         ChkBoxH->Checked = false;
         ChkEdtH->Text = "2";
         EdtStatus( ChkBoxH->Tag, false);
     }
     // 測定区分　HsC硬度（圧面）
     if( StrToInt(SGr1->Cells[18][ARow]) >= 2 ){
         ChkBoxI->Checked = true;
         ChkEdtI->Text = SGr1->Cells[18][ARow];
         EdtStatus( ChkBoxI->Tag, true);
     }
     else{
         ChkBoxI->Checked = false;
         ChkEdtI->Text = "2";
         EdtStatus( ChkBoxI->Tag, false);
     }
     // 測定区分　HsC硬度（側面）
     if( StrToInt(SGr1->Cells[19][ARow]) >= 2 ){
         ChkBoxJ->Checked = true;
         ChkEdtJ->Text = SGr1->Cells[19][ARow];
         EdtStatus( ChkBoxJ->Tag, true);
     }
     else{
         ChkBoxJ->Checked = false;
         ChkEdtJ->Text = "2";
         EdtStatus( ChkBoxJ->Tag, false);
     }
     // 測定区分　HsD硬度（圧面）
     if( StrToInt(SGr1->Cells[20][ARow]) >= 2 ){
         ChkBoxK->Checked = true;
         ChkEdtK->Text = SGr1->Cells[20][ARow];
         EdtStatus( ChkBoxK->Tag, true);
     }
     else{
         ChkBoxK->Checked = false;
         ChkEdtK->Text = "2";
         EdtStatus( ChkBoxK->Tag, false);
     }
     // 測定区分　HsD硬度（側面）
     if( StrToInt(SGr1->Cells[21][ARow]) >= 2 ){
         ChkBoxL->Checked = true;
         ChkEdtL->Text = SGr1->Cells[21][ARow];
         EdtStatus( ChkBoxL->Tag, true);
     }
     else{
         ChkBoxL->Checked = false;
         ChkEdtL->Text = "2";
         EdtStatus( ChkBoxL->Tag, false);
     }
     // 測定区分　座屈
     if( StrToInt(SGr1->Cells[22][ARow]) >= 2 ){
         ChkBoxM->Checked = true;
         ChkEdtM->Text = SGr1->Cells[22][ARow];
         EdtStatus( ChkBoxM->Tag, true);
     }
     else{
         ChkBoxM->Checked = false;
         ChkEdtM->Text = "2";
         EdtStatus( ChkBoxM->Tag, false);
     }

     // リード線長さ（下限）
     EdtA1->Text = SGr1->Cells[27][ARow];
     // リード線長さ（上限）
     EdtA2->Text = SGr1->Cells[28][ARow];
     // ブラシ幅（下限）
     EdtB1->Text = SGr1->Cells[29][ARow];
     // ブラシ幅（上限）
     EdtB2->Text = SGr1->Cells[30][ARow];
     // ブラシ幅縦押し（下限）
     EdtC1->Text = SGr1->Cells[31][ARow];
     // ブラシ幅縦押し（上限）
     EdtC2->Text = SGr1->Cells[32][ARow];
     // 母体比重（下限）
     EdtD1->Text = SGr1->Cells[39][ARow];
     // 母体比重（上限）
     EdtD2->Text = SGr1->Cells[40][ARow];
     // リード線引張強度
     EdtE1->Text = SGr1->Cells[36][ARow];
     // リード線引張強度（単位）
     if( SGr1->Cells[37][ARow] < "1" || SGr1->Cells[37][ARow] > "2" )   SGr1->Cells[37][ARow] = "2";
     if( StrToInt(SGr1->Cells[37][ARow]) == 1 ){
         ComBoxE2->ItemIndex = 0;           // Kgf
     }
     else{
         ComBoxE2->ItemIndex = 1;           // N
     }
     // リード線引張強度（スピード）
     EdtE3->Text = SGr1->Cells[38][ARow];
     // リード取付抵抗（電圧）
     EdtF1->Text = SGr1->Cells[33][ARow];
     // リード取付抵抗（電流）
     EdtF2->Text = SGr1->Cells[34][ARow];
     // リード取付抵抗（時間）
     EdtF3->Text = SGr1->Cells[35][ARow];
     // リード取付抵抗（TYPE）
     EdtF4->Text = SGr1->Cells[63][ARow];
     // 固有抵抗率（下限）
     EdtG1->Text = SGr1->Cells[41][ARow];
     // 固有抵抗率（上限）
     EdtG2->Text = SGr1->Cells[42][ARow];
     // 固有抵抗率（電流）
     EdtG3->Text = SGr1->Cells[43][ARow];
     // 固有抵抗率（プローブ）
     EdtG4->Text = SGr1->Cells[44][ARow];
     // 曲げ強度（下限）
     EdtH1->Text = SGr1->Cells[45][ARow];
     // 曲げ強度（上限）
     EdtH2->Text = SGr1->Cells[46][ARow];
     // 曲げ強度（単位）
     if( SGr1->Cells[47][ARow] < "1" || SGr1->Cells[47][ARow] > "4" )   SGr1->Cells[47][ARow] = "4";
     switch( StrToInt(SGr1->Cells[47][ARow]) ){
         case 1: ComBoxH3->ItemIndex = 0;    break;     // Kgf
         case 2: ComBoxH3->ItemIndex = 1;    break;     // N/cm2
         case 3: ComBoxH3->ItemIndex = 2;    break;     // MPa
         case 4: ComBoxH3->ItemIndex = 3;    break;     // N/mm2
     }
     // 曲げ強度（スパン）
     EdtH4->Text = SGr1->Cells[48][ARow];
     // HsC硬度 圧面（下限）
     EdtI1->Text = SGr1->Cells[49][ARow];
     // HsC硬度 圧面（上限）
     EdtI2->Text = SGr1->Cells[50][ARow];
     // HsC硬度 側面（下限）
     EdtJ1->Text = SGr1->Cells[51][ARow];
     // HsC硬度 側面（上限）
     EdtJ2->Text = SGr1->Cells[52][ARow];
     // HsD硬度 圧面（下限）
     EdtK1->Text = SGr1->Cells[53][ARow];
     // HsD硬度 圧面（上限）
     EdtK2->Text = SGr1->Cells[54][ARow];
     // HsD硬度 側面（下限）
     EdtL1->Text = SGr1->Cells[55][ARow];
     // HsD硬度 側面（上限）
     EdtL2->Text = SGr1->Cells[56][ARow];
     // 座屈（下限）
     EdtM1->Text = SGr1->Cells[57][ARow];
     // 座屈（上限）
     EdtM2->Text = SGr1->Cells[58][ARow];

     // 規格値のチェック
     ValueChenge(Sender);

     // 登録日
     sBuf = SGr1->Cells[59][ARow];
     if( sBuf.Trim() != "" ){
         sBuf = sBuf.Insert("/",5);
         sBuf = sBuf.Insert("/",8);
         PnlADDYMD2->Caption = sBuf;
     }
     else PnlADDYMD2->Caption = "";
     // 変更日
     sBuf = SGr1->Cells[60][ARow];
     if( sBuf.Trim() != "" ){
         sBuf = sBuf.Insert("/",5);
         sBuf = sBuf.Insert("/",8);
         PnlUPDYMD2->Caption = sBuf;
     }
     else PnlUPDYMD2->Caption = "";
     // 更新回数
     sBuf = SGr1->Cells[61][ARow];
     PnlUPDCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     //2002/11/11 E.Takase
     // 改訂番号
     sBuf = SGr1->Cells[10][ARow];
     PnlREVCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;
     // 更新者
     sBuf = GetTANNAM(SGr1->Cells[65][ARow]);
     PnlUPDCHR2->Caption = sBuf;
     // 備考
     sBuf = SGr1->Cells[66][ARow];
     EdtMEMO->Text = sBuf;

     //履歴データの場合は保存できないようにする
     if( SGr1->Cells[10][ARow].Trim() != "0" ) {   // 改訂番号
        InitEdt2(false);
     //   BtnF08->Enabled=false;
     //   BtnF09->Enabled=false;
     //   BtnF10->Enabled=false;
     //   BtnF11->Enabled=false;
     //
     //} else {
     //   //InitEdt();
     //   BtnF08->Enabled=true;
     //   BtnF09->Enabled=true;
     //   BtnF10->Enabled=true;
     //   BtnF11->Enabled=true;
     //
     }

     //2002/12/05 E.Takase
     // 測定区分　現物曲げ強度
     if( StrToInt(SGr1->Cells[69][ARow]) >= 2 ){
         ChkBoxN->Checked = true;
         ChkEdtN->Text = SGr1->Cells[69][ARow];
         EdtStatus( ChkBoxN->Tag, true);
     }
     else{
         ChkBoxN->Checked = false;
         ChkEdtN->Text = "2";
         EdtStatus( ChkBoxN->Tag, false);
     }
     // 現物曲げ強度（下限）
     EdtN1->Text = SGr1->Cells[70][ARow];
     // 現物曲げ強度（上限）
     EdtN2->Text = SGr1->Cells[71][ARow];
     // 現物曲げ強度（単位）
     //2003/07/22 E.Takase 単位追加
     if( SGr1->Cells[72][ARow] < "1" || SGr1->Cells[72][ARow] > "5" )   SGr1->Cells[72][ARow] = "4";
     //if( SGr1->Cells[72][ARow] < "1" || SGr1->Cells[72][ARow] > "4" )   SGr1->Cells[72][ARow] = "4";
     switch( StrToInt(SGr1->Cells[72][ARow]) ){
         case 1: ComBoxN3->ItemIndex = 0;    break;     // Kgf
         case 2: ComBoxN3->ItemIndex = 1;    break;     // N/cm2
         case 3: ComBoxN3->ItemIndex = 2;    break;     // MPa
         case 4: ComBoxN3->ItemIndex = 3;    break;     // N/mm2
	     //2003/07/22 E.Takase 単位に「N」追加
         case 5: ComBoxN3->ItemIndex = 4;    break;     // N
     }
     // 現物曲げ強度（スパン）
     EdtN4->Text = SGr1->Cells[73][ARow];

     //2002/12/28 E.Takase
     if ( ComBox09->ItemIndex == 4 ) {
        PnlB->Caption = "内径";
        ChkBoxB->Caption = "内径";
        PnlC->Caption = "外径";
        ChkBoxC->Caption = "外径";

     } else {
        PnlB->Caption = "ﾌﾞﾗｼ幅";
        ChkBoxB->Caption = "ﾌﾞﾗｼ幅";
        PnlC->Caption = "ﾌﾞﾗｼ幅(縦押し)";
        ChkBoxC->Caption = "ﾌﾞﾗｼ幅(縦押し)";
     }


     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::InitEdt(void)
{
     int i;

     // 各コントロールの初期化
     EdtCOD1->Text = "";
     EdtCOD2->Text = "";
     EdtCOD3->Text = "";
     EdtCOD4->Text = "";
     Edt01->Text = "";
     Edt02->Text = "";
     Edt03->Text = "";
     Edt04->Text = "";
     Edt05->Text = "";
     Edt06->Text = "";
     Edt07->Text = "";
     Edt08->Text = "";
     ComBox09->ItemIndex = 0;
     Edt10->Text = "";
     ComBox11->ItemIndex = 0;
     Edt12->Text = "";
     Edt13->Text = "";
     ChkEdtA->Text = "2";
     ChkEdtB->Text = "2";
     ChkEdtC->Text = "2";
     ChkEdtD->Text = "2";
     ChkEdtE->Text = "2";
     ChkEdtF->Text = "2";
     ChkEdtG->Text = "2";
     ChkEdtH->Text = "2";
     ChkEdtI->Text = "2";
     ChkEdtJ->Text = "2";
     ChkEdtK->Text = "2";
     ChkEdtL->Text = "2";
     ChkEdtM->Text = "2";
     EdtA1->Text = "";
     EdtA2->Text = "";
     EdtB1->Text = "";
     EdtB2->Text = "";
     EdtC1->Text = "";
     EdtC2->Text = "";
     EdtD1->Text = "";
     EdtD2->Text = "";
     EdtE1->Text = "";
     ComBoxE2->ItemIndex = 1;
     EdtE3->Text = "";
     EdtF1->Text = "";
     EdtF2->Text = "";
     EdtF3->Text = "";
     EdtF4->Text = "";
     EdtG1->Text = "";
     EdtG2->Text = "";
     EdtG3->Text = "";
     EdtG4->Text = "";
     EdtH1->Text = "";
     EdtH2->Text = "";
     ComBoxH3->ItemIndex = 2;
     EdtH4->Text = "";
     EdtI1->Text = "";
     EdtI2->Text = "";
     EdtJ1->Text = "";
     EdtJ2->Text = "";
     EdtK1->Text = "";
     EdtK2->Text = "";
     EdtL1->Text = "";
     EdtL2->Text = "";
     EdtM1->Text = "";
     EdtM2->Text = "";
     PnlADDYMD2->Caption = "";
     PnlUPDYMD2->Caption = "";
     PnlUPDCNT2->Caption = "";
     ChkBoxA->Checked = false;
     ChkBoxB->Checked = false;
     ChkBoxC->Checked = false;
     ChkBoxD->Checked = false;
     ChkBoxE->Checked = false;
     ChkBoxF->Checked = false;
     ChkBoxG->Checked = false;
     ChkBoxH->Checked = false;
     ChkBoxI->Checked = false;
     ChkBoxJ->Checked = false;
     ChkBoxK->Checked = false;
     ChkBoxL->Checked = false;
     ChkBoxM->Checked = false;
     //2002/11/11 E.Takase
     PnlUPDCHR2->Caption = "";
     PnlREVCNT2->Caption = "";
     EdtMEMO->Text = "";

     //2002/12/05 E.Takase
     ChkEdtN->Text = "2";
     EdtN1->Text = "";
     EdtN2->Text = "";
     ComBoxN3->ItemIndex = 2;
     EdtN4->Text = "";
     ChkBoxN->Checked = false;

     for( i=0; i<=14; i++ ){
         EdtStatus( i, false );
     }

     // 規格値のチェック
     ValueChenge((TObject *)Form1);

}


//---------------------------------------------------------------------------
// ヒストグラム規格
void __fastcall TForm1::ComBox11Change(TObject *Sender)
{
    // 規格値のチェック
    ValueChenge(Sender);

    switch( ComBox11->ItemIndex ){

        // 両側
        case 0:
            // ヒストグラムMin（有効）
            Pnl12->Color = 0x00FEE7BA;
            Pnl12->Font->Color = clBlack;
            Edt12->Enabled = true;
            // ヒストグラムMax（有効）
            Pnl13->Color = 0x00FEE7BA;
            Pnl13->Font->Color = clBlack;
            Edt13->Enabled = true;
            break;

        // 上限
        case 1:
            // ヒストグラムMin（無効）
            Pnl12->Color = clSilver;
            Pnl12->Font->Color = clGray;
            Edt12->Enabled = false;
            // ヒストグラムMax（有効）
            Pnl13->Color = 0x00FEE7BA;
            Pnl13->Font->Color = clBlack;
            Edt13->Enabled = true;
            break;

        // 下限
        case 2:
            // ヒストグラムMin（有効）
            Pnl12->Color = 0x00FEE7BA;
            Pnl12->Font->Color = clBlack;
            Edt12->Enabled = true;
            // ヒストグラムMax（無効）
            Pnl13->Color = clSilver;
            Pnl13->Font->Color = clGray;
            Edt13->Enabled = false;
            break;
    }
}


//---------------------------------------------------------------------------
void __fastcall TForm1::ChkBoxClick(TObject *Sender)
{
    // エディットの状態を変更します
    TCheckBox *ChkBox = (TCheckBox *)Sender;
    EdtStatus( ChkBox->Tag, ChkBox->Checked );
    // 規格値のチェック
    ValueChenge(Sender);
}


//---------------------------------------------------------------------------
void __fastcall TForm1::EdtStatus(int tag, bool status)
{
    // エディットの状態を変更します
    switch(tag){
        case 1:
            // リード線長さ
            if( status ){
                PnlA->Color = 0x00FEE7BA;
                PnlA->Font->Color = clBlack;
                EdtA1->Enabled = true;
                EdtA2->Enabled = true;
                LblA1->Font->Color = clBlack;
                LblA2->Font->Color = clBlack;
                ChkEdtA->Enabled = true;
                ChkEdtA->Font->Color = clBlack;
            }
            else{
                PnlA->Color = clSilver;
                PnlA->Font->Color = clGray;
                EdtA1->Enabled = false;
                EdtA2->Enabled = false;
                LblA1->Font->Color = clGray;
                LblA2->Font->Color = clGray;
                ChkEdtA->Enabled = false;
                ChkEdtA->Font->Color = clGray;
            }
            break;

        case 2:
            // ブラシ幅
            if( status ){
                PnlB->Color = 0x00FEE7BA;
                PnlB->Font->Color = clBlack;
                EdtB1->Enabled = true;
                EdtB2->Enabled = true;
                LblB1->Font->Color = clBlack;
                LblB2->Font->Color = clBlack;
                ChkEdtB->Enabled = true;
                ChkEdtB->Font->Color = clBlack;
            }
            else{
                PnlB->Color = clSilver;
                PnlB->Font->Color = clGray;
                EdtB1->Enabled = false;
                EdtB2->Enabled = false;
                LblB1->Font->Color = clGray;
                LblB2->Font->Color = clGray;
                ChkEdtB->Enabled = false;
                ChkEdtB->Font->Color = clGray;
            }
            break;

        case 3:
            // ブラシ幅縦押し
            if( status ){
                PnlC->Color = 0x00FEE7BA;
                PnlC->Font->Color = clBlack;
                EdtC1->Enabled = true;
                EdtC2->Enabled = true;
                LblC1->Font->Color = clBlack;
                LblC2->Font->Color = clBlack;
                ChkEdtC->Enabled = true;
                ChkEdtC->Font->Color = clBlack;
            }
            else{
                PnlC->Color = clSilver;
                PnlC->Font->Color = clGray;
                EdtC1->Enabled = false;
                EdtC2->Enabled = false;
                LblC1->Font->Color = clGray;
                LblC2->Font->Color = clGray;
                ChkEdtC->Enabled = false;
                ChkEdtC->Font->Color = clGray;
            }
            break;

        case 4:
            // 見掛比重
            if( status ){
                PnlD->Color = 0x00FEE7BA;
                PnlD->Font->Color = clBlack;
                EdtD1->Enabled = true;
                EdtD2->Enabled = true;
                LblD1->Font->Color = clBlack;
                ChkEdtD->Enabled = true;
                ChkEdtD->Font->Color = clBlack;
            }
            else{
                PnlD->Color = clSilver;
                PnlD->Font->Color = clGray;
                EdtD1->Enabled = false;
                EdtD2->Enabled = false;
                LblD1->Font->Color = clGray;
                ChkEdtD->Enabled = false;
                ChkEdtD->Font->Color = clGray;
            }
            break;

        case 5:
            // 線引張強度
            if( status ){
                PnlE->Color = 0x00FEE7BA;
                PnlE->Font->Color = clBlack;
                EdtE1->Enabled = true;
                ComBoxE2->Enabled = true;
                EdtE3->Enabled = true;
                LblE1->Font->Color = clBlack;
                LblE2->Font->Color = clBlack;
                ChkEdtE->Enabled = true;
                ChkEdtE->Font->Color = clBlack;
            }
            else{
                PnlE->Color = clSilver;
                PnlE->Font->Color = clGray;
                EdtE1->Enabled = false;
                ComBoxE2->Enabled = false;
                EdtE3->Enabled = false;
                LblE1->Font->Color = clGray;
                LblE2->Font->Color = clGray;
                ChkEdtE->Enabled = false;
                ChkEdtE->Font->Color = clGray;
            }
            break;

        case 6:
            // 線取付抵抗
            if( status ){
                PnlF->Color = 0x00FEE7BA;
                PnlF->Font->Color = clBlack;
                EdtF1->Enabled = true;
                EdtF2->Enabled = true;
                EdtF3->Enabled = true;
                EdtF4->Enabled = true;
                LblF1->Font->Color = clBlack;
                LblF2->Font->Color = clBlack;
                LblF3->Font->Color = clBlack;
                LblF4->Font->Color = clBlack;
                ChkEdtF->Enabled = true;
                ChkEdtF->Font->Color = clBlack;
            }
            else{
                PnlF->Color = clSilver;
                PnlF->Font->Color = clGray;
                EdtF1->Enabled = false;
                EdtF2->Enabled = false;
                EdtF3->Enabled = false;
                EdtF4->Enabled = false;
                LblF1->Font->Color = clGray;
                LblF2->Font->Color = clGray;
                LblF3->Font->Color = clGray;
                LblF4->Font->Color = clGray;
                ChkEdtF->Enabled = false;
                ChkEdtF->Font->Color = clGray;
            }
            break;

        case 7:
            // 抵抗率
            if( status ){
                PnlG->Color = 0x00FEE7BA;
                PnlG->Font->Color = clBlack;
                EdtG1->Enabled = true;
                EdtG2->Enabled = true;
                EdtG3->Enabled = true;
                EdtG4->Enabled = true;
                LblG1->Font->Color = clBlack;
                LblG2->Font->Color = clBlack;
                LblG3->Font->Color = clBlack;
                LblG4->Font->Color = clBlack;
                LblG5->Font->Color = clBlack;
                ChkEdtG->Enabled = true;
                ChkEdtG->Font->Color = clBlack;
            }
            else{
                PnlG->Color = clSilver;
                PnlG->Font->Color = clGray;
                EdtG1->Enabled = false;
                EdtG2->Enabled = false;
                EdtG3->Enabled = false;
                EdtG4->Enabled = false;
                LblG1->Font->Color = clGray;
                LblG2->Font->Color = clGray;
                LblG3->Font->Color = clGray;
                LblG4->Font->Color = clGray;
                LblG5->Font->Color = clGray;
                ChkEdtG->Enabled = false;
                ChkEdtG->Font->Color = clGray;
            }
            break;

        case 8:
            // 曲げ強さ
            if( status ){
                PnlH->Color = 0x00FEE7BA;
                PnlH->Font->Color = clBlack;
                EdtH1->Enabled = true;
                EdtH2->Enabled = true;
                ComBoxH3->Enabled = true;
                EdtH4->Enabled = true;
                LblH1->Font->Color = clBlack;
                LblH2->Font->Color = clBlack;
                LblH3->Font->Color = clBlack;
                ChkEdtH->Enabled = true;
                ChkEdtH->Font->Color = clBlack;
            }
            else{
                PnlH->Color = clSilver;
                PnlH->Font->Color = clGray;
                EdtH1->Enabled = false;
                EdtH2->Enabled = false;
                ComBoxH3->Enabled = false;
                EdtH4->Enabled = false;
                LblH1->Font->Color = clGray;
                LblH2->Font->Color = clGray;
                LblH3->Font->Color = clGray;
                ChkEdtH->Enabled = false;
                ChkEdtH->Font->Color = clGray;
            }
            break;

        case 9:
            // 硬度HsC（圧面）
            if( status ){
                PnlI->Color = 0x00FEE7BA;
                PnlI->Font->Color = clBlack;
                EdtI1->Enabled = true;
                EdtI2->Enabled = true;
                LblI1->Font->Color = clBlack;
                LblI2->Font->Color = clBlack;
                ChkEdtI->Enabled = true;
                ChkEdtI->Font->Color = clBlack;
            }
            else{
                PnlI->Color = clSilver;
                PnlI->Font->Color = clGray;
                EdtI1->Enabled = false;
                EdtI2->Enabled = false;
                LblI1->Font->Color = clGray;
                LblI2->Font->Color = clGray;
                ChkEdtI->Enabled = false;
                ChkEdtI->Font->Color = clGray;
            }
            break;

        case 10:
            // 硬度HsC（側面）
            if( status ){
                PnlJ->Color = 0x00FEE7BA;
                PnlJ->Font->Color = clBlack;
                EdtJ1->Enabled = true;
                EdtJ2->Enabled = true;
                LblJ1->Font->Color = clBlack;
                LblJ2->Font->Color = clBlack;
                ChkEdtJ->Enabled = true;
                ChkEdtJ->Font->Color = clBlack;
            }
            else{
                PnlJ->Color = clSilver;
                PnlJ->Font->Color = clGray;
                EdtJ1->Enabled = false;
                EdtJ2->Enabled = false;
                LblJ1->Font->Color = clGray;
                LblJ2->Font->Color = clGray;
                ChkEdtJ->Enabled = false;
                ChkEdtJ->Font->Color = clGray;
            }
            break;

        case 11:
            // 硬度HsD（圧面）
            if( status ){
                PnlK->Color = 0x00FEE7BA;
                PnlK->Font->Color = clBlack;
                EdtK1->Enabled = true;
                EdtK2->Enabled = true;
                LblK1->Font->Color = clBlack;
                LblK2->Font->Color = clBlack;
                ChkEdtK->Enabled = true;
                ChkEdtK->Font->Color = clBlack;
            }
            else{
                PnlK->Color = clSilver;
                PnlK->Font->Color = clGray;
                EdtK1->Enabled = false;
                EdtK2->Enabled = false;
                LblK1->Font->Color = clGray;
                LblK2->Font->Color = clGray;
                ChkEdtK->Enabled = false;
                ChkEdtK->Font->Color = clGray;
            }
            break;

        case 12:
            // 硬度HsD（側面）
            if( status ){
                PnlL->Color = 0x00FEE7BA;
                PnlL->Font->Color = clBlack;
                EdtL1->Enabled = true;
                EdtL2->Enabled = true;
                LblL1->Font->Color = clBlack;
                LblL2->Font->Color = clBlack;
                ChkEdtL->Enabled = true;
                ChkEdtL->Font->Color = clBlack;
            }
            else{
                PnlL->Color = clSilver;
                PnlL->Font->Color = clGray;
                EdtL1->Enabled = false;
                EdtL2->Enabled = false;
                LblL1->Font->Color = clGray;
                LblL2->Font->Color = clGray;
                ChkEdtL->Enabled = false;
                ChkEdtL->Font->Color = clGray;
            }
            break;

        case 13:
            // 座屈
            if( status ){
                PnlM->Color = 0x00FEE7BA;
                PnlM->Font->Color = clBlack;
                EdtM1->Enabled = true;
                EdtM2->Enabled = true;
                LblM1->Font->Color = clBlack;
                LblM2->Font->Color = clBlack;
                ChkEdtM->Enabled = true;
                ChkEdtM->Font->Color = clBlack;
            }
            else{
                PnlM->Color = clSilver;
                PnlM->Font->Color = clGray;
                EdtM1->Enabled = false;
                EdtM2->Enabled = false;
                LblM1->Font->Color = clGray;
                LblM2->Font->Color = clGray;
                ChkEdtM->Enabled = false;
                ChkEdtM->Font->Color = clGray;
            }
            break;
        case 14:
            // 現物曲げ強さ
            if( status ){
                PnlN->Color = 0x00FEE7BA;
                PnlN->Font->Color = clBlack;
                EdtN1->Enabled = true;
                EdtN2->Enabled = true;
                ComBoxN3->Enabled = true;
                EdtN4->Enabled = true;
                LblN1->Font->Color = clBlack;
                LblN2->Font->Color = clBlack;
                LblN3->Font->Color = clBlack;
                ChkEdtN->Enabled = true;
                ChkEdtN->Font->Color = clBlack;
            }
            else{
                PnlN->Color = clSilver;
                PnlN->Font->Color = clGray;
                EdtN1->Enabled = false;
                EdtN2->Enabled = false;
                ComBoxN3->Enabled = false;
                EdtN4->Enabled = false;
                LblN1->Font->Color = clGray;
                LblN2->Font->Color = clGray;
                LblN3->Font->Color = clGray;
                ChkEdtN->Enabled = false;
                ChkEdtN->Font->Color = clGray;
            }
            break;     }

}


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     // ステータスメッセージ
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key){
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
                      // 検索部にフォーカスがある場合は、検索実行
                      if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() || EdtCOD4->Focused() || CheckBoxRireki->Focused() ){
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
         case VK_UP:
         case VK_LEFT:
                // 検索部
                if( EdtCOD2->Focused() || EdtCOD3->Focused() || EdtCOD4->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == 0 && Edt->SelLength == 0 ){
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( EdtCOD1->Focused() && EdtCOD1->SelStart == 0 && EdtCOD1->SelLength == 0 ){
                    if(EdtCOD4->Enabled){
                        EdtCOD4->SetFocus();
                    }
                    else{
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // 詳細部
                //2002/11/13 備考追加 E.Takase
                //2002/12/05 現物曲げ強さ追加 E.Takase
                if( Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt05->Focused() || Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || EdtM2->Focused() || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused()  ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == 0 && Edt->SelLength == 0 ){
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                //2002/12/05 現物曲げ強さ追加 E.Takase
                if( (ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused()
                    || ComBoxH3->Focused() || ComBoxN3->Focused()) && Key == VK_LEFT ){
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                //2002/12/05 現物曲げ強さ追加 E.Takase
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused() ){
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( Edt01->Focused() && Edt01->SelStart == 0 && Edt01->SelLength == 0 ){
                    if(EdtM2->Enabled){
                        EdtM2->SetFocus();
                    }
                    else{
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                // 検索部
                if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == Edt->Text.Length() && Edt->SelLength == 0 ){
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( EdtCOD4->Focused() && EdtCOD4->SelStart == EdtCOD4->Text.Length() && EdtCOD4->SelLength == 0 ){
                    if(EdtCOD1->Enabled){
                        EdtCOD1->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // 詳細部
                //2002/11/13 備考追加 E.Takase
                //2002/12/05 現物曲げ強さ追加 E.Takase
                if( Edt01->Focused() || Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt05->Focused() || Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused()  ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == Edt->Text.Length() && Edt->SelLength == 0 ){
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( (ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused() ||
                        ComBoxH3->Focused() || ComBoxN3->Focused() ) && Key == VK_RIGHT ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused()){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtM2->Focused() && EdtM2->SelStart == EdtM2->Text.Length() && EdtM2->SelLength == 0 ){
                    if(Edt01->Enabled){
                        Edt01->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                // 検索部
                if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtCOD4->Focused() ){
                    BtnF07Click(Sender);    break;
                }
                // 詳細部
                //2002/11/13 備考追加 E.Takase
                if( Edt01->Focused() || Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused() ||
                    ComBoxH3->Focused()  || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || ComBoxN3->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtM2->Focused() ){
                    if(Edt01->Enabled){
                        Edt01->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // 材質名称
                if( Edt05->Focused() ){
                    // 材質規格マスターを元にデータをセットします
                    // 2002/11/14 E.Takase 条件追加
                    if ( Edt05->ReadOnly == false ) {
                        SetZAISHITSU(2,Edt05->Text);
                    }
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
/*
                // 材質コード
                if( Edt06->Focused() ){
                    // 材質規格マスターを元にデータをセットします
                    SetZAISHITSU(1,Edt06->Text);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
*/
                break;
     }

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
         case VK_RETURN:Edt01->SetFocus();      break;
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
     sBuf = "select DTKSHIN from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // 材質コード
     //2002/11/11 E.Takase
     sBuf += "and REVCNT = " + IntToStr(KM02.REVCNT);  // 改訂番号

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
     //2002/11/13 データ項目 追加（REVCNT,MEMO,UPDYMD,UPDTIM） E.Takase
     sBuf = "insert into KM02(DTKSCOD,DTKSNAM,DTKSHIN,HINBAN,ZISCOD,ZISNAM,SYOSCOD,";
     sBuf = sBuf + "SORTKEY,KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,SK_LD_TR,SK_LD_HP,";
     sBuf = sBuf + "SK_BOTAI,SK_KOYU,SK_MAGE,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,";
     sBuf = sBuf + "SK_ZAKUT,HIST_SOKUT,HIST_KIKAK,HIST_MIN,HIST_MAX,LD_LNG_MIN,";
     sBuf = sBuf + "LD_LNG_MAX,BURASI_MIN,BURASI_MAX,BURASIT_MIN,BURASIT_MAX,LD_TR_DENA,";
     sBuf = sBuf + "LD_TR_DENR,LD_TR_TIME,LD_TR_TYPE,LD_HP_KYO,LD_HP_TAN,LD_HP_SPD,BOTAI_MIN,";
     sBuf = sBuf + "BOTAI_MAX,KOYU_MIN,KOYU_MAX,KOYU_DEN,KOYU_PRO,MAGE_MIN,MAGE_MAX,";
     sBuf = sBuf + "MAGE_TAN,MAGE_SPAN,HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,";
     sBuf = sBuf + "HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,ZAKUT_MIN,ZAKUT_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,";
     sBuf = sBuf + "REVCNT,MEMO,UPDYMD,UPDTIM,";
     sBuf = sBuf + "SK_MAGEG, MAGEG_MIN, MAGEG_MAX, MAGEG_TAN, MAGEG_SPAN) ";
     sBuf = sBuf + " values('";
     sBuf = sBuf + KM02.DTKSCOD                 + "','" ;   // 得意先コード
     sBuf = sBuf + KM02.DTKSNAM                 + "','" ;   // 得意先名称
     sBuf = sBuf + KM02.DTKSHIN                 + "','" ;   // 得意先品番
     sBuf = sBuf + KM02.HINBAN                  + "','" ;   // 自社品番
     sBuf = sBuf + KM02.ZISCOD                  + "','" ;   // 材質コード
     sBuf = sBuf + KM02.ZISNAM                  + "','" ;   // 材質名
     sBuf = sBuf + KM02.SYOSCOD                 + "',"  ;   // 焼成コード

     sBuf = sBuf + IntToStr(KM02.SORTKEY)       +  ","  ;   // ソートキー
     sBuf = sBuf + IntToStr(KM02.KEIJKBN)       +  ","  ;   // 形状区分
     sBuf = sBuf + IntToStr(KM02.SK_LD_LNG)     +  ","  ;   // 測定区分　線長さ
     sBuf = sBuf + IntToStr(KM02.SK_BURASI)     +  ","  ;   // 測定区分　ブラシ幅
     sBuf = sBuf + IntToStr(KM02.SK_BURASIT)    +  ","  ;   // 測定区分　ブラシ幅縦押し
     sBuf = sBuf + IntToStr(KM02.SK_LD_TR)      +  ","  ;   // 測定区分　線取付抵抗
     sBuf = sBuf + IntToStr(KM02.SK_LD_HP)      +  ","  ;   // 測定区分　線引張強度

     sBuf = sBuf + IntToStr(KM02.SK_BOTAI)      +  ","  ;   // 測定区分　母体比重
     sBuf = sBuf + IntToStr(KM02.SK_KOYU)       +  ","  ;   // 測定区分　固有抵抗
     sBuf = sBuf + IntToStr(KM02.SK_MAGE)       +  ","  ;   // 測定区分　抗折力
     sBuf = sBuf + IntToStr(KM02.SK_HSC_A)      +  ","  ;   // 測定区分　HsC硬度（圧面）
     sBuf = sBuf + IntToStr(KM02.SK_HSC_S)      +  ","  ;   // 測定区分　HsC硬度（側面）
     sBuf = sBuf + IntToStr(KM02.SK_HSD_A)      +  ","  ;   // 測定区分　HsD硬度（圧面）
     sBuf = sBuf + IntToStr(KM02.SK_HSD_S)      +  ","  ;   // 測定区分　HsD硬度（側面）

     sBuf = sBuf + IntToStr(KM02.SK_ZAKUT)      +  ","  ;   // 測定区分　座屈
     sBuf = sBuf + IntToStr(KM02.HIST_SOKUT)    +  ","  ;   // ヒストグラム（測定数）
     sBuf = sBuf + IntToStr(KM02.HIST_KIKAK)    +  ","  ;   // ヒストグラム（規格）
     sBuf = sBuf + FloatToStr(KM02.HIST_MIN)    +  ","  ;   // ヒストグラム（下限）
     sBuf = sBuf + FloatToStr(KM02.HIST_MAX)    +  ","  ;   // ヒストグラム（上限）
     sBuf = sBuf + FloatToStr(KM02.LD_LNG_MIN)  +  ","  ;   // リード線長さ（下限）

     sBuf = sBuf + FloatToStr(KM02.LD_LNG_MAX)  +  ","  ;   // リード線長さ（上限）
     sBuf = sBuf + FloatToStr(KM02.BURASI_MIN)  +  ","  ;   // ブラシ幅（下限）
     sBuf = sBuf + FloatToStr(KM02.BURASI_MAX)  +  ","  ;   // ブラシ幅（上限）
     sBuf = sBuf + FloatToStr(KM02.BURASIT_MIN) +  ","  ;   // ブラシ幅縦押し（下限）
     sBuf = sBuf + FloatToStr(KM02.BURASIT_MAX) +  ","  ;   // ブラシ幅縦押し（上限）
     sBuf = sBuf + FloatToStr(KM02.LD_TR_DENA)  +  ","  ;   // リード取付抵抗（電圧）

     sBuf = sBuf + IntToStr(KM02.LD_TR_DENR)    +  ","  ;   // リード取付抵抗（電流）
     sBuf = sBuf + IntToStr(KM02.LD_TR_TIME)    +  ",'" ;   // リード取付抵抗（時間）
     sBuf = sBuf + KM02.LD_TR_TYPE              + "',"  ;   // リード取付抵抗（TYPE）
     sBuf = sBuf + FloatToStr(KM02.LD_HP_KYO)   +  ","  ;   // リード線引張強度
     sBuf = sBuf + IntToStr(KM02.LD_HP_TAN)     +  ","  ;   // リード線引張強度（単位）
     sBuf = sBuf + IntToStr(KM02.LD_HP_SPD)     +  ","  ;   // リード線引張強度（速度）
     sBuf = sBuf + FloatToStr(KM02.BOTAI_MIN)   +  ","  ;   // 母体比重（下限）

     sBuf = sBuf + FloatToStr(KM02.BOTAI_MAX)   +  ","  ;   // 母体比重（上限）
     sBuf = sBuf + IntToStr(KM02.KOYU_MIN)      +  ","  ;   // 固有抵抗率（下限）
     sBuf = sBuf + IntToStr(KM02.KOYU_MAX)      +  ","  ;   // 固有抵抗率（上限）
     sBuf = sBuf + FloatToStr(KM02.KOYU_DEN)    +  ","  ;   // 固有抵抗率（電流）
     sBuf = sBuf + IntToStr(KM02.KOYU_PRO)      +  ","  ;   // 固有抵抗率（プローブ）
     sBuf = sBuf + FloatToStr(KM02.MAGE_MIN)    +  ","  ;   // 曲げ強度（下限）
     sBuf = sBuf + FloatToStr(KM02.MAGE_MAX)    +  ","  ;   // 曲げ強度（上限）

     sBuf = sBuf + IntToStr(KM02.MAGE_TAN)      +  ","  ;   // 曲げ強度（単位）
     sBuf = sBuf + FloatToStr(KM02.MAGE_SPAN)   +  ","  ;   // 曲げ強度（スパン）
     sBuf = sBuf + IntToStr(KM02.HSC_A_MIN)     +  ","  ;   // HsC硬度 圧面（下限）
     sBuf = sBuf + IntToStr(KM02.HSC_A_MAX)     +  ","  ;   // HsC硬度 圧面（上限）
     sBuf = sBuf + IntToStr(KM02.HSC_S_MIN)     +  ","  ;   // HsC硬度 側面（下限）
     sBuf = sBuf + IntToStr(KM02.HSC_S_MAX)     +  ","  ;   // HsC硬度 側面（上限）
     sBuf = sBuf + FloatToStr(KM02.HSD_A_MIN)   +  ","  ;   // HsD硬度 圧面（下限）

     sBuf = sBuf + FloatToStr(KM02.HSD_A_MAX)   +  ","  ;   // HsD硬度 圧面（上限）
     sBuf = sBuf + FloatToStr(KM02.HSD_S_MIN)   +  ","  ;   // HsD硬度 側面（下限）
     sBuf = sBuf + FloatToStr(KM02.HSD_S_MAX)   +  ","  ;   // HsD硬度 側面（上限）
     sBuf = sBuf + IntToStr(KM02.ZAKUT_MIN)     +  ","  ;   // 座屈（下限）
     sBuf = sBuf + IntToStr(KM02.ZAKUT_MAX)     +  ",'" ;   // 座屈（上限）
     sBuf = sBuf + KM02.ADDYMD                  + "','" ;   // 登録日
     sBuf = sBuf + KM02.ADDTIM                  + "',"  ;   // 登録時間
     sBuf = sBuf + IntToStr(KM02.UPDCHR)        +  ","  ;   // 更新者
     sBuf = sBuf + IntToStr(KM02.UPDCNT)        +  ","  ;   // 更新回数
     sBuf = sBuf + IntToStr(KM02.REVCNT)        +  ",'" ;   // 改訂番号
     sBuf = sBuf + KM02.MEMO                    +  "','" ;   // 備考
     sBuf = sBuf + KM02.UPDYMD                  + "','" ;   // 更新日
     sBuf = sBuf + KM02.UPDTIM                  + "',"  ;   // 更新時間
     sBuf = sBuf + IntToStr(KM02.SK_MAGEG)       +  ","  ;   // 測定区分　抗折力
     sBuf = sBuf + FloatToStr(KM02.MAGEG_MIN)    +  ","  ;   // 曲げ強度（下限）
     sBuf = sBuf + FloatToStr(KM02.MAGEG_MAX)    +  ","  ;   // 曲げ強度（上限）
     sBuf = sBuf + IntToStr(KM02.MAGEG_TAN)      +  ","  ;   // 曲げ強度（単位）
     sBuf = sBuf + FloatToStr(KM02.MAGEG_SPAN)   +  ")"  ;   // 曲げ強度（スパン）

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
     sBuf = "update KM02 set ";
     sBuf = sBuf + "DTKSCOD='" + KM02.DTKSCOD                    + "', " ;   // 得意先コード
     sBuf = sBuf + "DTKSNAM='" + KM02.DTKSNAM                    + "', " ;   // 得意先名称
     sBuf = sBuf + "DTKSHIN='" + KM02.DTKSHIN                    + "', " ;   // 得意先品番
     sBuf = sBuf + "HINBAN='" + KM02.HINBAN                      + "', " ;   // 自社品番
     sBuf = sBuf + "ZISCOD='" + KM02.ZISCOD                      + "', " ;   // 材質コード
     sBuf = sBuf + "ZISNAM='" + KM02.ZISNAM                      + "', " ;   // 材質名
     sBuf = sBuf + "SYOSCOD='" + KM02.SYOSCOD                    + "', " ;   // 焼成コード

     sBuf = sBuf + "SORTKEY=" + IntToStr(KM02.SORTKEY)           +  ", " ;   // ソートキー
     sBuf = sBuf + "KEIJKBN=" + IntToStr(KM02.KEIJKBN)           +  ", " ;   // 形状区分
     sBuf = sBuf + "SK_LD_LNG=" + IntToStr(KM02.SK_LD_LNG)       +  ", " ;   // 測定区分　線長さ
     sBuf = sBuf + "SK_BURASI=" + IntToStr(KM02.SK_BURASI)       +  ", " ;   // 測定区分　ブラシ幅
     sBuf = sBuf + "SK_BURASIT=" + IntToStr(KM02.SK_BURASIT)     +  ", " ;   // 測定区分　ブラシ幅縦押し
     sBuf = sBuf + "SK_LD_TR=" + IntToStr(KM02.SK_LD_TR)         +  ", " ;   // 測定区分　線取付抵抗
     sBuf = sBuf + "SK_LD_HP=" + IntToStr(KM02.SK_LD_HP)         +  ", " ;   // 測定区分　線引張強度

     sBuf = sBuf + "SK_BOTAI=" + IntToStr(KM02.SK_BOTAI)         +  ", " ;   // 測定区分　母体比重
     sBuf = sBuf + "SK_KOYU=" + IntToStr(KM02.SK_KOYU)           +  ", " ;   // 測定区分　固有抵抗
     sBuf = sBuf + "SK_MAGE=" + IntToStr(KM02.SK_MAGE)           +  ", " ;   // 測定区分　抗折力
     sBuf = sBuf + "SK_HSC_A=" + IntToStr(KM02.SK_HSC_A)         +  ", " ;   // 測定区分　HsC硬度（圧面）
     sBuf = sBuf + "SK_HSC_S=" + IntToStr(KM02.SK_HSC_S)         +  ", " ;   // 測定区分　HsC硬度（側面）
     sBuf = sBuf + "SK_HSD_A=" + IntToStr(KM02.SK_HSD_A)         +  ", " ;   // 測定区分　HsD硬度（圧面）
     sBuf = sBuf + "SK_HSD_S=" + IntToStr(KM02.SK_HSD_S)         +  ", " ;   // 測定区分　HsD硬度（側面）

     sBuf = sBuf + "SK_ZAKUT=" + IntToStr(KM02.SK_ZAKUT)         +  ", " ;   // 測定区分　座屈
     sBuf = sBuf + "HIST_SOKUT=" + IntToStr(KM02.HIST_SOKUT)     +  ", " ;   // ヒストグラム（測定数）
     sBuf = sBuf + "HIST_KIKAK=" + IntToStr(KM02.HIST_KIKAK)     +  ", " ;   // ヒストグラム（規格）
     sBuf = sBuf + "HIST_MIN=" + FloatToStr(KM02.HIST_MIN)       +  ", " ;   // ヒストグラム（下限）
     sBuf = sBuf + "HIST_MAX=" + FloatToStr(KM02.HIST_MAX)       +  ", " ;   // ヒストグラム（上限）
     sBuf = sBuf + "LD_LNG_MIN=" + FloatToStr(KM02.LD_LNG_MIN)   +  ", " ;   // リード線長さ（下限）

     sBuf = sBuf + "LD_LNG_MAX=" + FloatToStr(KM02.LD_LNG_MAX)   +  ", " ;   // リード線長さ（上限）
     sBuf = sBuf + "BURASI_MIN=" + FloatToStr(KM02.BURASI_MIN)   +  ", " ;   // ブラシ幅（下限）
     sBuf = sBuf + "BURASI_MAX=" + FloatToStr(KM02.BURASI_MAX)   +  ", " ;   // ブラシ幅（上限）
     sBuf = sBuf + "BURASIT_MIN=" + FloatToStr(KM02.BURASIT_MIN) +  ", " ;   // ブラシ幅縦押し（下限）
     sBuf = sBuf + "BURASIT_MAX=" + FloatToStr(KM02.BURASIT_MAX) +  ", " ;   // ブラシ幅縦押し（上限）
     sBuf = sBuf + "LD_TR_DENA=" + FloatToStr(KM02.LD_TR_DENA)   +  ", " ;   // リード取付抵抗（電圧）

     sBuf = sBuf + "LD_TR_DENR=" + IntToStr(KM02.LD_TR_DENR)     +  ", " ;   // リード取付抵抗（電流）
     sBuf = sBuf + "LD_TR_TIME=" + IntToStr(KM02.LD_TR_TIME)     +  ", " ;   // リード取付抵抗（時間）
     sBuf = sBuf + "LD_TR_TYPE='" + KM02.LD_TR_TYPE              + "', " ;   // リード取付抵抗（TYPE）
     sBuf = sBuf + "LD_HP_KYO=" + FloatToStr(KM02.LD_HP_KYO)     +  ", " ;   // リード線引張強度
     sBuf = sBuf + "LD_HP_TAN=" + IntToStr(KM02.LD_HP_TAN)       +  ", " ;   // リード線引張強度（単位）
     sBuf = sBuf + "LD_HP_SPD=" + IntToStr(KM02.LD_HP_SPD)       +  ", " ;   // リード線引張強度（速度）
     sBuf = sBuf + "BOTAI_MIN=" + FloatToStr(KM02.BOTAI_MIN)     +  ", " ;   // 母体比重（下限）

     sBuf = sBuf + "BOTAI_MAX=" + FloatToStr(KM02.BOTAI_MAX)     +  ", " ;   // 母体比重（上限）
     sBuf = sBuf + "KOYU_MIN=" + IntToStr(KM02.KOYU_MIN)         +  ", " ;   // 固有抵抗率（下限）
     sBuf = sBuf + "KOYU_MAX=" + IntToStr(KM02.KOYU_MAX)         +  ", " ;   // 固有抵抗率（上限）
     sBuf = sBuf + "KOYU_DEN=" + FloatToStr(KM02.KOYU_DEN)       +  ", " ;   // 固有抵抗率（電流）
     sBuf = sBuf + "KOYU_PRO=" + IntToStr(KM02.KOYU_PRO)         +  ", " ;   // 固有抵抗率（プローブ）
     sBuf = sBuf + "MAGE_MIN=" + FloatToStr(KM02.MAGE_MIN)       +  ", " ;   // 曲げ強度（下限）
     sBuf = sBuf + "MAGE_MAX=" + FloatToStr(KM02.MAGE_MAX)       +  ", " ;   // 曲げ強度（上限）

     sBuf = sBuf + "MAGE_TAN=" + IntToStr(KM02.MAGE_TAN)         +  ", " ;   // 曲げ強度（単位）
     sBuf = sBuf + "MAGE_SPAN=" + FloatToStr(KM02.MAGE_SPAN)     +  ", " ;   // 曲げ強度（スパン）
     sBuf = sBuf + "HSC_A_MIN=" + IntToStr(KM02.HSC_A_MIN)       +  ", " ;   // HsC硬度 圧面（下限）
     sBuf = sBuf + "HSC_A_MAX=" + IntToStr(KM02.HSC_A_MAX)       +  ", " ;   // HsC硬度 圧面（上限）
     sBuf = sBuf + "HSC_S_MIN=" + IntToStr(KM02.HSC_S_MIN)       +  ", " ;   // HsC硬度 側面（下限）
     sBuf = sBuf + "HSC_S_MAX=" + IntToStr(KM02.HSC_S_MAX)       +  ", " ;   // HsC硬度 側面（上限）
     sBuf = sBuf + "HSD_A_MIN=" + FloatToStr(KM02.HSD_A_MIN)     +  ", " ;   // HsD硬度 圧面（下限）

     sBuf = sBuf + "HSD_A_MAX=" + FloatToStr(KM02.HSD_A_MAX)     +  ", " ;   // HsD硬度 圧面（上限）
     sBuf = sBuf + "HSD_S_MIN=" + FloatToStr(KM02.HSD_S_MIN)     +  ", " ;   // HsD硬度 側面（下限）
     sBuf = sBuf + "HSD_S_MAX=" + FloatToStr(KM02.HSD_S_MAX)     +  ", " ;   // HsD硬度 側面（上限）
     sBuf = sBuf + "ZAKUT_MIN=" + IntToStr(KM02.ZAKUT_MIN)       +  ", " ;   // 座屈（下限）
     sBuf = sBuf + "ZAKUT_MAX=" + IntToStr(KM02.ZAKUT_MAX)       +  ", " ;   // 座屈（上限）
     sBuf = sBuf + "UPDYMD='"    + KM02.UPDYMD                   + "', " ;   // 変更日
     sBuf = sBuf + "UPDTIM='"    + KM02.UPDTIM                   + "', " ;   // 変更時間
     sBuf = sBuf + "UPDCHR="     + IntToStr(KM02.UPDCHR)         +  ", " ;   // 更新者
     sBuf = sBuf + "UPDCNT="     + IntToStr(KM02.UPDCNT)         +  ","  ;   // 更新回数
     sBuf = sBuf + "REVCNT="     + IntToStr(KM02.REVCNT)         +  ", "  ;  // 改訂番号
     sBuf = sBuf + "MEMO='"      + KM02.MEMO				     +  "' "  ;  // 備考
     sBuf = sBuf + "SK_MAGEG=" + IntToStr(KM02.SK_MAGEG)           +  ", " ;   // 測定区分　抗折力
     sBuf = sBuf + "MAGEG_MIN=" + FloatToStr(KM02.MAGEG_MIN)       +  ", " ;   // 曲げ強度（下限）
     sBuf = sBuf + "MAGEG_MAX=" + FloatToStr(KM02.MAGEG_MAX)       +  ", " ;   // 曲げ強度（上限）
     sBuf = sBuf + "MAGEG_TAN=" + IntToStr(KM02.MAGEG_TAN)         +  ", " ;   // 曲げ強度（単位）
     sBuf = sBuf + "MAGGE_SPAN=" + FloatToStr(KM02.MAGEG_SPAN)     +  ", " ;   // 曲げ強度（スパン）

     sBuf = sBuf + "where DTKSHIN='" + OldKey + "'";
     sBuf = sBuf + "and REVCNT=" + IntToStr(KM02.REVCNT);

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
     sBuf = "select DTKSHIN from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // 得意先品番
     //2002/11/19 E.Takase 条件に改訂番号追加
     sBuf += " AND REVCNT =" + IntToStr(KM02.REVCNT); // 改訂番号

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
            SBr1->Panels->Items[0]->Text = "該当の得意先品番が見つかりません。削除できませんでした。";
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
     sBuf = "delete from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // 得意先品番
     //2002/11/19 E.Takase 条件に改訂番号追加
     sBuf += " AND REVCNT =" + IntToStr(KM02.REVCNT); // 改訂番号


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
// 材質規格マスタデータからデータをセットします。
void __fastcall TForm1::SetZAISHITSU(int flag,String KeyStr )
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // 問合せ実行
    if( flag == 1 ){
        sBuf = "select ZISNAM,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
        sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX";
        sBuf = sBuf + " from KM03 where ZISCOD like '";
        sBuf = sBuf + KeyStr + "'";
    }
    else{
        sBuf = "select ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
        sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX";
        sBuf = sBuf + " from KM03 where ZISNAM like '";
        sBuf = sBuf + KeyStr + "'";
    }
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
            // 検索結果無し
            SBr1->Panels->Items[0]->Text = "該当の材質規格データが見つかりません。";
            SBr1->Update();
            Beep();
            return;
        }
        else{
            // 検索結果有り

            if( flag != 1 ){
                sBuf = Query1->Fields->Fields[0]->AsString;      // 材質コード
                Edt06->Text = sBuf;
            }
            else{
                sBuf = Query1->Fields->Fields[0]->AsString;      // 材質名称
                Edt05->Text = sBuf;
            }

            sBuf = FormatFloat("0.00",Query1->Fields->Fields[1]->AsFloat);      // 母体比重（下限）
            EdtF1->Text = sBuf;

            sBuf = FormatFloat("0.00",Query1->Fields->Fields[2]->AsFloat);      // 母体比重（上限）
            EdtF2->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[3]->AsInteger);              // 固有抵抗率（下限）
            EdtG1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[4]->AsInteger);              // 固有抵抗率（上限）
            EdtG2->Text = sBuf;

            sBuf = FormatFloat("0.###",Query1->Fields->Fields[5]->AsFloat);     // 曲げ強度（下限）
            EdtH1->Text = sBuf;

            sBuf = FormatFloat("0.###",Query1->Fields->Fields[6]->AsFloat);     // 曲げ強度（上限）
            EdtH2->Text = sBuf;

            switch( Query1->Fields->Fields[7]->AsInteger ){
                case 1: ComBoxE2->ItemIndex = 0;    break;     // Kgf
                case 2: ComBoxE2->ItemIndex = 1;    break;     // N/cm2
                case 3: ComBoxE2->ItemIndex = 2;    break;     // MPa
                case 4: ComBoxE2->ItemIndex = 3;    break;     // N/mm2
            }

            sBuf = IntToStr(Query1->Fields->Fields[8]->AsInteger);              // ＨｓＣ硬度　圧面（下限）
            EdtI1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[9]->AsInteger);             // ＨｓＣ硬度　圧面（上限）
            EdtI2->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[10]->AsInteger);             // ＨｓＣ硬度　側面（下限）
            EdtJ1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[11]->AsInteger);             // ＨｓＣ硬度　側面（上限）
            EdtJ2->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[12]->AsFloat);      // ＨｓＤ硬度　圧面（下限）
            EdtK1->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[13]->AsFloat);      // ＨｓＤ硬度　圧面（上限）
            EdtK2->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[14]->AsFloat);      // ＨｓＤ硬度　側面（下限）
            EdtL1->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[15]->AsFloat);      // ＨｓＤ硬度　側面（上限）
            EdtL2->Text = sBuf;

            return;
        }
    }
    catch(EDatabaseError& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }
    catch(Exception& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }

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


void __fastcall TForm1::FormEnter(TObject *Sender)
{

    if( SGr1->Tag == 1 )    return;
    if( BtnF01->Focused() )    return;



    // 検索部　得意先コードにフォーカスが有る場合
    if( EdtCOD1->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // 検索部　得意先品番にフォーカスが有る場合
    if( EdtCOD2->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // 検索部　自社品番にフォーカスが有る場合
    if( EdtCOD3->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // 検索部　材質名称にフォーカスが有る場合
    if( EdtCOD4->Focused() ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // 詳細部　得意先コードにフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt01->Focused() ){
    if( Edt01->Focused() && Edt01->ReadOnly == false ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // 詳細部　得意先名称にフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt02->Focused() ){
    if( Edt02->Focused() && Edt02->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // 詳細部　得意先品番にフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt03->Focused() ){
    if( Edt03->Focused() && Edt03->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // 詳細部　自社品番にフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt04->Focused() ){
    if( Edt04->Focused() && Edt04->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // 詳細部　材質名称にフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt05->Focused() ){
    if( Edt05->Focused() && Edt05->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // 詳細部　材質コードにフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt06->Focused()  ){
    if( Edt06->Focused() && Edt06->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // 詳細部　焼成コードにフォーカスが有る場合
    // 2002/11/14 E.Takase
    //if( Edt07->Focused() ){
    if( Edt07->Focused() && Edt07->ReadOnly == false  ){
        // 「F1：一覧検索」ボタンを使えるようにする
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // 「F1：一覧検索」ボタンを使えないようにする
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}


//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ValueChenge(TObject *Sender)
{
    // if( ComBox11->Focused() || Edt12->Focused() || Edt13->Focused() ){
        if( Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0 ){
            Edt12->Font->Color = clBlack;
            Edt13->Font->Color = clBlack;
        }
        else{
            Edt12->Font->Color = clRed;
            Edt13->Font->Color = clRed;
        }
    //}

    if( EdtA1->Focused() || EdtA2->Focused() || EdtA1->Enabled || EdtA2->Enabled ){
        if( EdtA1->Value < EdtA2->Value ){
            EdtA1->Font->Color = clBlack;
            EdtA2->Font->Color = clBlack;
        }
        else{
            EdtA1->Font->Color = clRed;
            EdtA2->Font->Color = clRed;
        }
    }
    if( EdtB1->Focused() || EdtB2->Focused() || EdtB1->Enabled || EdtB2->Enabled ){
        if( EdtB1->Value < EdtB2->Value ){
            EdtB1->Font->Color = clBlack;
            EdtB2->Font->Color = clBlack;
        }
        else{
            EdtB1->Font->Color = clRed;
            EdtB2->Font->Color = clRed;
        }
    }
    if( EdtC1->Focused() || EdtC2->Focused() || EdtC1->Enabled || EdtC2->Enabled ){
        if( EdtC1->Value < EdtC2->Value ){
            EdtC1->Font->Color = clBlack;
            EdtC2->Font->Color = clBlack;
        }
        else{
            EdtC1->Font->Color = clRed;
            EdtC2->Font->Color = clRed;
        }
    }
    if( EdtD1->Focused() || EdtD2->Focused() || EdtD1->Enabled || EdtD2->Enabled ){
        if( EdtD1->Value < EdtD2->Value ){
            EdtD1->Font->Color = clBlack;
            EdtD2->Font->Color = clBlack;
        }
        else{
            EdtD1->Font->Color = clRed;
            EdtD2->Font->Color = clRed;
        }
    }
    if( EdtG1->Focused() || EdtG2->Focused() || EdtG1->Enabled || EdtG2->Enabled ){
        if( EdtG1->Value < EdtG2->Value ){
            EdtG1->Font->Color = clBlack;
            EdtG2->Font->Color = clBlack;
        }
        else{
            EdtG1->Font->Color = clRed;
            EdtG2->Font->Color = clRed;
        }
    }
    if( EdtH1->Focused() || EdtH2->Focused() || EdtH1->Enabled || EdtH2->Enabled ){
        if( EdtH1->Value < EdtH2->Value ){
            EdtH1->Font->Color = clBlack;
            EdtH2->Font->Color = clBlack;
        }
        else{
            EdtH1->Font->Color = clRed;
            EdtH2->Font->Color = clRed;
        }
    }
    if( EdtI1->Focused() || EdtI2->Focused() || EdtI1->Enabled || EdtI2->Enabled ){
        if( EdtI1->Value < EdtI2->Value ){
            EdtI1->Font->Color = clBlack;
            EdtI2->Font->Color = clBlack;
        }
        else{
            EdtI1->Font->Color = clRed;
            EdtI2->Font->Color = clRed;
        }
    }
    if( EdtJ1->Focused() || EdtJ2->Focused() || EdtJ1->Enabled || EdtJ2->Enabled ){
        if( EdtJ1->Value < EdtJ2->Value ){
            EdtJ1->Font->Color = clBlack;
            EdtJ2->Font->Color = clBlack;
        }
        else{
            EdtJ1->Font->Color = clRed;
            EdtJ2->Font->Color = clRed;
        }
    }
    if( EdtK1->Focused() || EdtK2->Focused() || EdtK1->Enabled || EdtK2->Enabled ){
        if( EdtK1->Value < EdtK2->Value ){
            EdtK1->Font->Color = clBlack;
            EdtK2->Font->Color = clBlack;
        }
        else{
            EdtK1->Font->Color = clRed;
            EdtK2->Font->Color = clRed;
        }
    }
    if( EdtL1->Focused() || EdtL2->Focused() || EdtL1->Enabled || EdtL2->Enabled ){
        if( EdtL1->Value < EdtL2->Value ){
            EdtL1->Font->Color = clBlack;
            EdtL2->Font->Color = clBlack;
        }
        else{
            EdtL1->Font->Color = clRed;
            EdtL2->Font->Color = clRed;
        }
    }
    if( EdtM1->Focused() || EdtM2->Focused() || EdtM1->Enabled || EdtM2->Enabled ){
        if( EdtM1->Value < EdtM2->Value ){
            EdtM1->Font->Color = clBlack;
            EdtM2->Font->Color = clBlack;
        }
        else{
            EdtM1->Font->Color = clRed;
            EdtM2->Font->Color = clRed;
        }
    }
    //2002/12/05 E.Takase 現物曲げ強さ追加
    if( EdtN1->Focused() || EdtN2->Focused() || EdtN1->Enabled || EdtN2->Enabled ){
        if( EdtN1->Value < EdtN2->Value ){
            EdtN1->Font->Color = clBlack;
            EdtN2->Font->Color = clBlack;
        }
        else{
            EdtN1->Font->Color = clRed;
            EdtN2->Font->Color = clRed;
        }
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edt10Change(TObject *Sender)
{
    // ヒストグラム測定数のチェック
    if( Edt10->Value > 0 ){
        Pnl11->Color = 0x00FEE7BA;
        Pnl11->Font->Color = clBlack;
        Pnl12->Color = 0x00FEE7BA;
        Pnl12->Font->Color = clBlack;
        Pnl13->Color = 0x00FEE7BA;
        Pnl13->Font->Color = clBlack;
        ComBox11->Enabled = true;
        Edt12->Enabled = true;
        Edt13->Enabled = true;
    }
    else{
        Pnl11->Color = clSilver;
        Pnl11->Font->Color = clGray;
        Pnl12->Color = clSilver;
        Pnl12->Font->Color = clGray;
        Pnl13->Color = clSilver;
        Pnl13->Font->Color = clGray;
        ComBox11->Enabled = false;
        Edt12->Enabled = false;
        Edt13->Enabled = false;
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SGr1DrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{

   RECT r=RECT(Rect);

   //固定セルの背景色をセット
   if(State.Contains(gdFixed))
       SGr1->Canvas->Brush->Color= SGr1->FixedColor;
   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected))
       SGr1->Canvas->Brush->Color= clHighlight;
   //普通のセルの背景色をセット
   else
       SGr1->Canvas->Brush->Color= SGr1->Color;

   //背景色で消去
   SGr1->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr1->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr1->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       SGr1->Canvas->Font->Color= clHighlightText;
   //過去の履歴データの場合の文字色をセット
   else if( ACol > 0 && SGr1->Cells[10][ARow].ToIntDef(0) > 0 )
       SGr1->Canvas->Font->Color = clSilver;
   //普通のセルの文字色をセット
   else
       SGr1->Canvas->Font->Color= SGr1->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr1->Canvas->Handle,SGr1->Cells[ACol][ARow].c_str(),-1,&r,0); //右寄せ

//   if( ACol < 0 || ACol > 10 ) return;
//   if( SGr1->Cells[10][ARow].ToIntDef(0) > 0 ){
//       SGr1->Canvas->Font->Color = clYellow;
//   }

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



void __fastcall TForm1::ComBox09Change(TObject *Sender)
{
    //2002/12/28 E.Takase Add
    if ( ComBox09->ItemIndex == 4 ) {
        PnlB->Caption = "内径";
        ChkBoxB->Caption = "内径";
        PnlC->Caption = "外径";
        ChkBoxC->Caption = "外径";

     } else {
        PnlB->Caption = "ﾌﾞﾗｼ幅";
        ChkBoxB->Caption = "ﾌﾞﾗｼ幅";
        PnlC->Caption = "ﾌﾞﾗｼ幅(縦押し)";
        ChkBoxC->Caption = "ﾌﾞﾗｼ幅(縦押し)";
     }




}
//---------------------------------------------------------------------------

