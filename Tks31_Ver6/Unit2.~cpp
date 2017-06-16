/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ21）                    *
*  file   name   : Unit2.cpp                                           *
*  create        : 1999.10.20                                          *
*  update        :                                                     *
*  contents      : 一覧検索表示画面処理ﾌﾟﾛｸﾞﾗﾑ                         *
*  written by    : 高瀬  恵利（NKK unics Corp.)                        *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 *Form2;

AnsiString Select_Str;
AnsiString sBuf;
AnsiString sMsg2 = "検索結果 0 です";

int iRec ;
int KM01_KENYMDSerch01(void);
int KM01_KENYMDSerch02(void);
int KM01_LOTNOSerch01(int tmp);
int KM01_DTKSHINSerch01(void);
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{
    int i;
    Form2->SGr1->RowCount = 2;

    Form2->SGr1->Cells[0][1] = "";
    Form2->SGr1->Cells[1][1] = "";
     switch(KENSAKU_Mode)
     {
         case 1://検査日に選択したデータを入力
                iRec = KM01_KENYMDSerch01() ;
                break;

         case 2://得意先品番
                iRec = KM01_DTKSHINSerch01();
                break;

         case 3://開始ロットNo
                iRec = KM01_LOTNOSerch01(KENSAKU_Mode);
                break;

         case 4://終了ロットNo
                iRec = KM01_LOTNOSerch01(KENSAKU_Mode);
                break;

         case 5://開始検査月
                iRec = KM01_KENYMDSerch02() ;
                break;

         case 6://終了検査月
                iRec = KM01_KENYMDSerch02() ;
                break;
     }




     // グリッドの初期化
     SGr1->ColWidths[0]  = 40;
     SGr1->ColWidths[1]  = 90 ;
//     SGr1->ColWidths[2]  = 40;

     if(iRec != 0){
        // カソールを最初レコードへ設定
        SGr1->Row = 1;
        SGr1->SetFocus();

       // 最初レコードのﾃﾞｰﾀを変数へ保存
       Select_Str = SGr1->Cells[1][1] ;
//       sTL = SGr1->Cells[2][1] ;
      }else{
         BtnF02->Enabled = false;
         BtnF03->Enabled = false;
         BtnF04->Enabled = false;
      }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_RETURN:
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
     }
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

     switch(KENSAKU_Mode)
     {
         case 1://検査日に選択したデータを入力
                //Form1->EdtYMD->Text = Form1->InsSEPA( Select_Str);
				Form1->EdtYMD->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtYMD->SetFocus();
                break;

         case 2://得意先品番
                Form1->EdtTKSHIN->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtSLOT->SetFocus();
                break;

         case 3://開始ロットNo
                Form1->EdtSLOT->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtELOT->SetFocus();
                break;

         case 4://終了ロットNo
                Form1->EdtELOT->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtSYM->SetFocus();
                break;

         case 5://開始検査月
                //Form1->EdtSYM->Text = Select_Str.Insert("/",5);
                Form1->EdtSYM->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtEYM->SetFocus();
                break;

         case 6://終了検査月
                //Form1->EdtEYM->Text = Select_Str.Insert("/",5);
                Form1->EdtEYM->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtEYM->SetFocus();
                break;
     }


    Close();
}
//---------------------------------------------------------------------------

// 「Ｆ１２：終了」
void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     switch(KENSAKU_Mode)
     {
         case 1://検査日に選択したデータを入力
                // カソールを「検査予定日」へ
                Form1->EdtYMD->SetFocus();
                break;

         case 2://得意先品番
                // カソールを「検査予定日」へ
                Form1->EdtTKSHIN->SetFocus();
                break;

         case 3://開始ロットNo
                // カソールを「検査予定日」へ
                Form1->EdtSLOT->SetFocus();
                break;

         case 4://終了ロットNo
                // カソールを「検査予定日」へ
                Form1->EdtELOT->SetFocus();
                break;

         case 5://開始検査月
                // カソールを「検査予定日」へ
                Form1->EdtSYM->SetFocus();
                break;

         case 6://終了検査月
                // カソールを「検査予定日」へ
                Form1->EdtEYM->SetFocus();
                break;
     }


    Close();}
//---------------------------------------------------------------------------



void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   //ｶﾚﾝﾄレコードのﾃﾞｰﾀを変数へ保存
   Select_Str = SGr1->Cells[1][ARow] ;
   //sTL = SGr1->Cells[2][ARow] ;
}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : int  KM01_KENYMDSerch01(void)                       *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 検査予定日  抽出                                    *
*  written by    : 高瀬 恵利(NKK unics Corp.)                          *
***********************************************************************/
int KM01_KENYMDSerch01(void)
{
    AnsiString str;

    //KM01から検査日を抽出
    Form2->Query1->Close();
    Form2->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KDA1.KENSA_YMD ";
    sBuf += "FROM KDA1 ";
    sBuf += " ORDER BY KDA1.KENSA_YMD DESC";

    Form2->Query1->SQL->Add(sBuf);
    Form2->Query1->Open();
    Form2->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "検査日";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    iRow += 1;

    //if ( Form2->Query1->RecordCount <= 0 ) {
    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
      ShowMessage( sMsg2 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

            sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] =  Form1->InsSEPA(sBuf);

            Form2->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return iRow;
 }
/***********************************************************************
*  function name : int  KM01_KENYMDSerch02(void)                       *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 検査予定日（年月）  抽出                            *
*  written by    : 高瀬 恵利(NKK unics Corp.)                          *
***********************************************************************/
int KM01_KENYMDSerch02(void)
{
    AnsiString str;
    int i = 1;
    int flag = 0;
    //KM01から検査日を抽出
    Form2->Query1->Close();
    Form2->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KDA1.KENSA_YMD ";
    sBuf += "FROM KDA1 ";
    sBuf += " ORDER BY KDA1.KENSA_YMD DESC";

    Form2->Query1->SQL->Add(sBuf);
    Form2->Query1->Open();
    Form2->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "測定月";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    iRow += 1;

    //if ( Form2->Query1->RecordCount <= 0 ) {
    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
      ShowMessage( sMsg2 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {
            sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            for ( i = 1; i < iRow; i++) {
                if ( Form2->SGr1->Cells[1][i] == sBuf.SubString(1,6).Insert("/",5) ) {
                    flag = 1;
                    break;
                }
            }
            if ( flag == 0 ) {
                // グリッドの最大行数が超えていないかチェックする
                if( iRow >= Form2->SGr1->RowCount ){
                    Form2->SGr1->RowCount = iRow+1;
                }
                sBuf = iRow ;
                Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

                sBuf = Form2->Query1->Fields->Fields[0]->AsString;
                Form2->SGr1->Cells[1][iRow] = sBuf.SubString(1,6).Insert("/",5);

                iRow += 1;
            }
            flag = 0;
            Form2->Query1->Next();
      }
   }

   Form2->SGr1->RowCount = iRow;

   return (iRow) ;
 }

/***********************************************************************
*  function name : int  KM01_LOTNOSerch01(void)                        *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ロットNo   抽出                                    *
*  written by    : 高瀬 恵利(NKK unics Corp.)                          *
***********************************************************************/
int KM01_LOTNOSerch01(int tmp)
{
    AnsiString str;

    //KM01からロットNoを抽出
    Form2->Query1->Close();
    Form2->Query1->SQL->Clear();

    //問い合せ文実行
    //ロットNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KM01.LOTNO ";
    sBuf += "FROM KM01 ";
    if ( tmp == 3 ) {
    //StartLOT
    	sBuf += "WHERE LOTNO LIKE '" + Form1->EdtSLOT->Text + "%'";
    } else {
    //EndLOT
    	sBuf += "WHERE LOTNO LIKE '" + Form1->EdtELOT->Text + "%'";
    }
    if ( Trim( Form1->EdtTKSHIN->Text ) != "" ) {
        sBuf += "AND KM01.DTKSHIN = '" + Trim( Form1->EdtTKSHIN->Text ) + "'";
    }
    sBuf += " ORDER BY KM01.LOTNO";

    Form2->Query1->SQL->Add(sBuf);
    Form2->Query1->Open();
    Form2->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "ロットNo";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    iRow += 1;

    //if ( Form2->Query1->RecordCount <= 0 ) {
    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
      ShowMessage( sMsg2 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

            sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] = sBuf;

            Form2->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return iRow ;
 }

/***********************************************************************
*  function name : int  KM01_DTKSHINSerch01(void)                      *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 得意先品番  抽出                                    *
*  written by    : 高瀬 恵利(NKK unics Corp.)                          *
***********************************************************************/
int KM01_DTKSHINSerch01(void)
{
    AnsiString str;
    //KM01からロットNoを抽出
    Form2->Query1->Close();
    Form2->Query1->SQL->Clear();

    //問い合せ文実行
    //ロットNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KM01.DTKSHIN ";
    sBuf += "FROM KM01 ";
    sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtTKSHIN->Text + "%'";
    if ( Trim( Form1->EdtSLOT->Text ) != "" ) {
        sBuf += "AND KM01.LOTNO >= '" + Trim( Form1->EdtSLOT->Text ) + "'";
    }
    if ( Trim( Form1->EdtELOT->Text ) != "" ) {
		sBuf += "AND KM01.LOTNO <= '" + Trim( Form1->EdtELOT->Text ) + "'";
    }

    sBuf += " ORDER BY KM01.DTKSHIN";

    Form2->Query1->SQL->Add(sBuf);
    Form2->Query1->Open();
    Form2->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "得意先品番";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    iRow += 1;

    //if ( Form2->Query1->RecordCount <= 0 ) {
    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
      ShowMessage( sMsg2 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

            sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] = sBuf;

            Form2->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return iRow ;
 }

