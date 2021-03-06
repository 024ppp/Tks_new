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

void __fastcall TForm2::FormActivate(TObject *Sender)
{

     int i;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // 選択フラグOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // 選択行の初期化

     switch( Form2->Tag ){

        // 検索部　にフォーカスが有る場合
        case 1:

            // 問合せ実行
            sBuf = "select DISTINCT KENSA_YMD from KM01 ORDER BY KENSA_YMD DESC";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "検査予定年月日";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 200;
            break;

        // 編集部　得意先コードにフォーカスが有る場合
        case 2:

            // 問合せ実行
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt02->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Trim(Form1->Edt02->Text) ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先コード";
            SGr1->Cells[2][0] = "得意先名称";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // 編集部　得意先品番にフォーカスが有る場合
        case 3:

            // 問合せ実行
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Trim(Form1->Edt02->Text) != "" ){
                // 得意先コード
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Trim(Form1->Edt02->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt03->Text) != "" ){
                // 得意先品番
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt06->Text) != "" ){
                // 材質名称
                if( i == 1 ){   // 得意先コードの条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Trim(Form1->Edt06->Text) ;
                sBuf = sBuf + "%'";
#if 1   // 2011.06.02 Y.Sano Add start
                i = 1;
#endif  // 2011.06.02 Y.Sano Add end
            }

#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // 条件が付いている時
                sBuf = sBuf + " and";
            }
            else{           // 条件が付いていない時
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // タイトルをセット
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "得意先品番";
            SGr1->Cells[2][0] = "自社品番";
            SGr1->Cells[3][0] = "材質名称";
            SGr1->Cells[4][0] = "材質コード";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            SGr1->ColWidths[4] = 180;
            break;

        // 編集部　ロットNOにフォーカスが有る場合
        case 4:

            // 問合せ実行
            sBuf = "select DISTINCT LOTBNG from SD21S";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt04->Text) != "" ){
                // ロットNO
                if( i == 1 ){   // 得意先品番の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 得意先品番の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " LOTBNG like '";
                sBuf = sBuf + Trim(Form1->Edt04->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            sBuf = sBuf + " ORDER BY LOTBNG";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "ロットNO";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 100;
            break;

        // 編集部　自社品番にフォーカスが有る場合
        case 5:

            // 問合せ実行
            sBuf = "select DISTINCT HINBAN from KM02";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt05->Text) != "" ){
                // 自社品番
                if( i == 1 ){   // 条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Trim(Form1->Edt05->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // 条件が付いている時
                sBuf = sBuf + " and";
            }
            else{           // 条件が付いていない時
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY HINBAN";

            // タイトルをセット
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "自社品番";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            break;

        // 編集部　材質名称、材質コードにフォーカスが有る場合
        case 6:
        case 7:

            // 問合せ実行
            sBuf = "select ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // 得意先品番
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt06->Text) != "" ){
                // 材質名称
                if( i == 1 ){   // 材質名称の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 材質名称の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Trim(Form1->Edt06->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt07->Text) != "" ){
                // 材質コード
                if( i == 1 ){   // 材質名称の条件が付いている時
                    sBuf = sBuf + " and";
                }
                else{           // 材質名称の条件が付いていない時
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISCOD like '";
                sBuf = sBuf + Trim(Form1->Edt07->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // 条件が付いている時
                sBuf = sBuf + " and";
            }
            else{           // 条件が付いていない時
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY ZISNAM";

            // タイトルをセット
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "材質名称";
            SGr1->Cells[2][0] = "材質コード";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // その他
        default:
            Close();
            return;
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
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

        // データ
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form2->Tag == 1 ){
                sBuf = Form1->InsSEPA(sBuf);
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
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

    // 選択フラグONの時
    if( SGr1->Tag ){

        switch( Form2->Tag ){

            // 検索部　検査予定日にフォーカスが有る場合
            case 1:
                Form1->EdtCOD->Text = SGr1->Cells[1][SGr1->Row];    // 得意先コード
                Form1->EdtCOD->SetFocus();
                Form1->EdtCOD->SelectAll();
                break;

            // 編集部　得意先コードにフォーカスが有る場合
            case 2:
                Form1->Edt02->Text = SGr1->Cells[1][SGr1->Row];     // 得意先コード
                Form1->Edt02->SetFocus();
                Form1->Edt02->SelectAll();
                break;

            // 編集部　得意先品番にフォーカスが有る場合
            case 3:
                Form1->Edt03->Text = SGr1->Cells[1][SGr1->Row];      // 得意先品番
                Form1->Edt05->Text = SGr1->Cells[2][SGr1->Row];      // 自社品番
                Form1->Edt06->Text = SGr1->Cells[3][SGr1->Row];      // 材質名称
                Form1->Edt07->Text = SGr1->Cells[4][SGr1->Row];      // 材質コード
                Form1->Edt03->SetFocus();
                Form1->Edt03->SelectAll();
                break;

            // 編集部　ロットNOにフォーカスが有る場合
            case 4:
                Form1->Edt04->Text = SGr1->Cells[1][SGr1->Row];      // ロットNO
                Form1->Edt04->SetFocus();
                Form1->Edt04->SelectAll();
                break;

            // 編集部　自社品番にフォーカスが有る場合
            case 5:
                Form1->Edt05->Text = SGr1->Cells[1][SGr1->Row];      // 自社品番
                Form1->Edt05->SetFocus();
                Form1->Edt05->SelectAll();
                break;

            // 編集部　材質コード、材質名称にフォーカスが有る場合
            case 6:
            case 7:
                Form1->Edt06->Text = SGr1->Cells[1][SGr1->Row];      // 材質名称
                Form1->Edt07->Text = SGr1->Cells[2][SGr1->Row];      // 材質コード
                if( Form2->Tag == 6 ){
                    Form1->Edt06->SetFocus();
                    Form1->Edt06->SelectAll();
                }
                if( Form2->Tag == 7 ){
                    Form1->Edt07->SetFocus();
                    Form1->Edt07->SelectAll();
                }
                break;

        }


    }
}
//---------------------------------------------------------------------------


