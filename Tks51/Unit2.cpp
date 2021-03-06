//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}


//---------------------------------------------------------------------------
// 「Ｆ２：前項」
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// 「Ｆ３：次項」
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// 「Ｆ４：選択」
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
     SGr1->Tag = 1;    // 選択フラグON
     Close();
}


//---------------------------------------------------------------------------
// 「Ｆ１２：戻る」
void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     Close();
}


//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{

     int i;
     int cnt;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // 選択フラグOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // 選択行の初期化

     switch( Form1->BtnF01->Tag ){

        // 検索部　得意先コードにフォーカスが有る場合
        case 1:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSCOD, DTKSNAM from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            //2009/04/07 E.Takase （REVCNT = 0　の条件追加）
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY DTKSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 80;
            SGr1->ColWidths[2] = 400;
            break;

        // 検索部　得意先品番にフォーカスが有る場合
        case 2:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }

            //2009/04/07 E.Takase （REVCNT = 0　の条件追加）
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->Cells[3][0] = "材質名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // 検索部　自社品番にフォーカスが有る場合
        case 3:

            // 問合せ実行
            sBuf = "select DISTINCT HINBAN from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            //2009/04/07 E.Takase （REVCNT = 0　の条件追加）
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else  {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY HINBAN";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // 検索部　材質名称にフォーカスが有る場合
        case 4:

            // 問合せ実行
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先コードの条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // 自社品番
                if( i == 1 ){   // 得意先品番の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先品番の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }

            //2009/04/07 E.Takase （REVCNT = 0　の条件追加）
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            
            sBuf = sBuf + " ORDER BY ZISNAM";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "材質名称";
            SGr1->Cells[2][0] = "材質コード";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // 詳細部　得意先コード、得意先名称にフォーカスが有る場合
        case 5:
        case 6:

            // 問合せ実行
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt01->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Form1->Edt01->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // 詳細部　得意先品番にフォーカスが有る場合
        // 詳細部　自社品番にフォーカスが有る場合
        case 7:
        case 8:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt01->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " and DTKSCOD like '";
                sBuf = sBuf + Form1->Edt01->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form1->Edt03->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " and DTKSHIN like '";
                sBuf = sBuf + Form1->Edt03->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form1->Edt04->Text) != "" ){
                // 自社品番
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form1->Edt04->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // 詳細部　材質名称、材質コードにフォーカスが有る場合
        case 9:
        case 10:

            // 問合せ実行
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form1->Edt05->Text) != "" ){
                // 材質名称
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form1->Edt05->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "材質名称";
            SGr1->Cells[2][0] = "材質コード";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // 詳細部　焼成コードにフォーカスが有る場合
        case 11:

            // 問合せ実行
            sBuf = "select DISTINCT SYOSEI_CD, RO_NO, MAX_ONDO, CYCLE_TIME, MEMO from KM04";
            if( Trim(Form1->Edt07->Text) != "" ){
                // 焼成コード
                sBuf = sBuf + " where SYOSEI_CD like '";
                sBuf = sBuf + Form1->Edt07->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY SYOSEI_CD";

            // タイトルをセット
            SGr1->ColCount = 6;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "焼成ｺｰﾄﾞ";
            SGr1->Cells[2][0] = "炉NO";
            SGr1->Cells[3][0] = "MAX温度";
            SGr1->Cells[4][0] = "ｻｲｸﾙﾀｲﾑ";
            SGr1->Cells[5][0] = "メモ";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 60;
            SGr1->ColWidths[2] = 60;
            SGr1->ColWidths[3] = 60;
            SGr1->ColWidths[4] = 60;
            SGr1->ColWidths[5] = 300;
            break;
    }

    Query1->SQL->Add(sBuf);
    ClpBrd = Clipboard();
    ClpBrd->Open();
    ClpBrd->SetTextBuf(sBuf.c_str());
    ClpBrd->Close();
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        iRow += 1;

        // グリッドの最大行数が超えていないかチェックする
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // グリッドにデータをセットします。

        // NO
        sBuf = iRow;
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            if( Form1->BtnF01->Tag == 9 && ( i == 3 || i == 4 ) ){
                // MAX温度、サイクルタイム
                sBuf = Query1->Fields->Fields[i-1]->AsString;
                sBuf = AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf;
            }
            else{
                sBuf = Query1->Fields->Fields[i-1]->AsString;
            }
            SGr1->Cells[i][iRow] = sBuf;
        }

        // カーソルを次にセットする
        Query1->Next();
    }

    SGr1->RowCount = iRow + 1 ;

    fFind = true;
    if( iRow == 0 ){
        fFind = false;
        SGr1->RowCount = 2;
        SGr1->FixedRows = 1;
        // 検索結果該当なしの場合
        for( i=1; i<SGr1->ColCount; i++){
            SGr1->Cells[i][1] = "該当無し";
        }
    }
    SGr1->SetFocus();

}


//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
         case VK_RETURN:
              SGr1->Tag = 1;    // 選択フラグON
              Close();
              break;
     }

}



void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // 検索部　得意先コードにフォーカスが有る場合
            case 1:
                Form1->EdtCOD1->Text = SGr1->Cells[1][SGr1->Row];      // 得意先コード
                Form1->EdtCOD1->SetFocus();
                Form1->EdtCOD1->SelectAll();
                break;

            // 検索部　得意先品番にフォーカスが有る場合
            case 2:
                Form1->EdtCOD2->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->EdtCOD3->Text = SGr1->Cells[2][SGr1->Row];      // 自社品番
                Form1->EdtCOD4->Text = SGr1->Cells[3][SGr1->Row];      // 材質名称
                Form1->EdtCOD2->SetFocus();
                Form1->EdtCOD2->SelectAll();
                break;

            // 検索部　自社品番にフォーカスが有る場合
            case 3:
                Form1->EdtCOD3->Text = SGr1->Cells[1][SGr1->Row];      // 自社品番
                Form1->EdtCOD3->SetFocus();
                Form1->EdtCOD3->SelectAll();
                break;

            // 検索部　材質名称にフォーカスが有る場合
            case 4:
                Form1->EdtCOD4->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form1->EdtCOD4->SetFocus();
                Form1->EdtCOD4->SelectAll();
                break;

            // 詳細部　得意先コード、得意先名称にフォーカスが有る場合
            case 5:
            case 6:
                Form1->Edt01->Text = SGr1->Cells[1][SGr1->Row];      // 得意先コード
                Form1->Edt02->Text = SGr1->Cells[2][SGr1->Row];      // 得意先名称
                if( Form1->BtnF01->Tag == 5 ){
                    Form1->Edt01->SetFocus();
                    Form1->Edt01->SelectAll();
                }
                if( Form1->BtnF01->Tag == 6 ){
                    Form1->Edt02->SetFocus();
                    Form1->Edt02->SelectAll();
                }
                break;

            // 詳細部　得意先品番にフォーカスが有る場合
            // 詳細部　自社品番にフォーカスが有る場合
            case 7:
            case 8:
                Form1->Edt03->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->Edt04->Text = SGr1->Cells[2][SGr1->Row];      // 自社品番
                if( Form1->BtnF01->Tag == 7 ){
                    Form1->Edt03->SetFocus();
                    Form1->Edt03->SelectAll();
                }
                if( Form1->BtnF01->Tag == 8 ){
                    Form1->Edt04->SetFocus();
                    Form1->Edt04->SelectAll();
                }
                break;

            // 詳細部　材質名称、材質コードにフォーカスが有る場合
            case 9:
            case 10:
                Form1->Edt05->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form1->Edt06->Text = SGr1->Cells[2][SGr1->Row];      // 材質コード
                if( Form1->BtnF01->Tag ==  9 ){
                    Form1->Edt05->SetFocus();
                    Form1->Edt05->SelectAll();
                }
                if( Form1->BtnF01->Tag == 10 ){
                    Form1->Edt06->SetFocus();
                    Form1->Edt06->SelectAll();
                }
                break;

            // 詳細部　焼成コードにフォーカスが有る場合
            case 11:
                Form1->Edt07->Text = SGr1->Cells[1][SGr1->Row];      // 焼成ｺｰﾄﾞ
                Form1->Edt07->SetFocus();
                Form1->Edt07->SelectAll();
                break;
        }


    }
}
//---------------------------------------------------------------------------

