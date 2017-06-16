/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ３０                    *
*  file   name   : Unit2.cpp                                           *
*  create        : 1999.11.05                                          *
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
AnsiString Select_Str2;
AnsiString Select_Str3;
AnsiString Select_Str4;
AnsiString Select_Str5;
AnsiString Select_Str6;
AnsiString Select_Str7;
AnsiString Select_Str8;
AnsiString Select_Str9;
int Select_Cnt;
AnsiString sBuf;
AnsiString sMsg2 = "検索結果 0 です";

int iRec ;
int Serch01(int flag);
int KDA1_KENYMDSerch01(void);
int KM02_DTKSCODSerch01(void);
int KM02_DTKSHINSerch01(void);

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{

    
     Form2->SGr1->RowCount = 2;
     Form2->SGr1->ColCount = 2;

     Form2->SGr1->Cells[0][1] = "";
     Form2->SGr1->Cells[1][1] = "";

     iRec = Serch01(KENSAKU_Mode);


     // グリッドの初期化
     SGr1->ColWidths[0]  = 40;
     SGr1->ColWidths[1]  = 90 ;
//     SGr1->ColWidths[2]  = 40;

     if( iRec){
        // カソールを最初レコードへ設定
        SGr1->Row = 1;
        SGr1->SetFocus();

       // 最初レコードのﾃﾞｰﾀを変数へ保存
       Select_Str = SGr1->Cells[1][1] ;
       if ( KENSAKU_Mode == 3 ) {
			Select_Str2 = SGr1->Cells[2][1] ;
			Select_Str3 = SGr1->Cells[3][1] ;
			Select_Str4 = SGr1->Cells[4][1] ;
			Select_Str5 = SGr1->Cells[5][1] ;
			Select_Str6 = SGr1->Cells[6][1] ;
			Select_Str7 = SGr1->Cells[7][1] ;
            Select_Str8 = SGr1->Cells[8][1] ;
			Select_Str9 = SGr1->Cells[9][1] ;

       }


//       sTL = SGr1->Cells[2][1] ;
         BtnF02->Enabled = true;
         BtnF03->Enabled = true;
         BtnF04->Enabled = true;


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
     AnsiString str;

     switch(KENSAKU_Mode)
     {
         case 1://検査日に選択したデータを入力
                //str = Select_Str;
                //str.Insert("/",5);
                //str.Insert("/",8);
                Form1->EdtCOD->Text = Select_Str;
                // カソールを「検査予定日」へ
                Form1->EdtCOD->SetFocus();
                break;

         case 2://得意先ｺｰﾄﾞ
                Form1->Edt1->Text = Select_Str;
                // カソールを「得意先ｺｰﾄﾞ」へ
                Form1->Edt1->SetFocus();
                break;

         case 3://得意先品番
                Form1->Edt2->Text = Select_Str;
                Form1->Edt4->Text = Select_Str3;
                Form1->Edt5->Text = Select_Str6;
                if ( Select_Str7 == NULL ) {
					Form1->Cmb1->ItemIndex = StrToInt( Select_Str7)-1;
                } else {
                    Form1->Cmb1->ItemIndex = 0;
                }
                Form1->Edt8->Text = Select_Str5;

                Form1->Edt6->Text = "0";
                Form1->Edt7->Text = "0";
                switch( Form1->Cmb1->ItemIndex){
                    case 0: //0 両側
                        Form1->Edt6->Text = Select_Str8;
                        Form1->Edt7->Text = Select_Str9;
                        Form1->Edt6->Enabled = true;
                        Form1->Edt7->Enabled = true;
                        break;
                    case 1: //0 下限
                        Form1->Edt6->Text = Select_Str8;
                        Form1->Edt7->Text = Select_Str9;
                        Form1->Edt6->Enabled = true;
                        Form1->Edt7->Enabled = false;
                        break;
                    case 2: //0 上限
                        Form1->Edt6->Text = Select_Str8;
                        Form1->Edt7->Text = Select_Str9;
                        Form1->Edt6->Enabled = false;
                        Form1->Edt7->Enabled = true;
                        break;
                }

/*                //ARow
                //Tmp_Kda1.DTKSHIN = Form2->Query1->Fields->Fields[0]->AsString;
                //Tmp_Kda1.DTKSCOD = Form2->Query1->Fields->Fields[1]->AsString;
                //Tmp_Kda1.ZISCOD = Form2->Query1->Fields->Fields[2]->AsString;
                //Tmp_Kda1.ZISNAM = Form2->Query1->Fields->Fields[3]->AsString;
                //Tmp_Kda1.HIST_SOKUT = StrToInt(Form2->Query1->Fields->Fields[4]->AsString);
                //Tmp_Kda1.HIST_KIKAK = StrToInt(Form2->Query1->Fields->Fields[5]->AsString);
                //Tmp_Kda1.HIST_MIN = StrToFloat(Form2->Query1->Fields->Fields[6]->AsString);
                //Tmp_Kda1.HIST_MAX = StrToFloatForm2->Query1->Fields->Fields[7]->AsString);


                Form1->Edt4->Text = Form2->Query1->FieldValues["HINBAN"];
                Form1->Edt5->Text = Form2->Query1->FieldValues["HIST_SOKUT"];
                if ( VarIsNull(Form2->Query1->FieldValues["HIST_KIKAK"]) )
                	Form1->Cmb1->ItemIndex = 0;
                else
                	Form1->Cmb1->ItemIndex = StrToInt( Form2->Query1->FieldValues["HIST_KIKAK"])-1;
                //Form1->Edt6->Text = Form2->FieldValues["HIST_MIN"];
                //Form1->Edt7->Text = Form2->FieldValues["HIST_MAX"];
                Form1->Edt8->Text = Form2->Query1->FieldValues["ZISNAM"];

                Form1->Edt6->Text = "0";
                Form1->Edt7->Text = "0";
                switch( Form1->Cmb1->ItemIndex){
                    case 0: //0 両側
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MIN"]) ))
                        	Form1->Edt6->Text = Form2->Query1->FieldValues["HIST_MIN"];
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MAX"]) ))
	                        Form1->Edt7->Text = Form2->Query1->FieldValues["HIST_MAX"];
                        Form1->Edt6->Enabled = true;
                        Form1->Edt7->Enabled = true;
                        break;
                    case 1: //0 下限
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MIN"]) ))
                        	Form1->Edt6->Text = Form2->Query1->FieldValues["HIST_MIN"];
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MAX"]) ))
	                        Form1->Edt7->Text = Form2->Query1->FieldValues["HIST_MAX"];
                        Form1->Edt6->Enabled = true;
                        Form1->Edt7->Enabled = false;
                        break;
                    case 2: //0 上限
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MIN"]) ))
                        	Form1->Edt6->Text = Form2->Query1->FieldValues["HIST_MIN"];
                    	if ( !(VarIsNull(Form2->Query1->FieldValues["HIST_MAX"]) ))
	                        Form1->Edt7->Text = Form2->Query1->FieldValues["HIST_MAX"];
                        Form1->Edt6->Enabled = false;
                        Form1->Edt7->Enabled = true;
                        break;
                }
                */
                //カソールを「得意先品番」へ
                Form1->Edt2->SetFocus();
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
                Form1->EdtCOD->SetFocus();
                break;

         case 2://得意先ｺｰﾄﾞ
                // カソールを「得意先ｺｰﾄﾞ」へ
                Form1->Edt1->SetFocus();
                break;

         case 3://得意先品番
                // カソールを「得意先品番」へ
                Form1->Edt2->SetFocus();
                break;
     }


    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
   //ｶﾚﾝﾄレコードのﾃﾞｰﾀを変数へ保存
   Select_Str = SGr1->Cells[1][ARow] ;
   if ( KENSAKU_Mode == 3 ) {
	   Select_Str2 = SGr1->Cells[2][ARow] ;
	   Select_Str3 = SGr1->Cells[3][ARow] ;
	   Select_Str4 = SGr1->Cells[4][ARow] ;
	   Select_Str5 = SGr1->Cells[5][ARow] ;
	   Select_Str6 = SGr1->Cells[6][ARow] ;
	   Select_Str7 = SGr1->Cells[7][ARow] ;
	   Select_Str8 = SGr1->Cells[8][ARow] ;
	   Select_Str9 = SGr1->Cells[9][ARow] ;

   }
   Select_Cnt = ARow;
}

//---------------------------------------------------------------------------
//検索
int Serch01(int flag)
{
    AnsiString str;
    int i = 1;

    //KM01から検査日を抽出
    Form2->Query1->Close();
    Form2->Query1->SQL->Clear();
    switch(flag)
    {
         case 1://検査日に選択したデータを入力
                //検査予定日、トレーNo
                sBuf = "SELECT DISTINCT KENSA_YMD FROM KDA1";
                sBuf += " WHERE KOJOKBN = " + IntToStr(iKojoKbn);            //20160701_工場区分追加
                sBuf += " ORDER BY KDA1.KENSA_YMD DESC";
               //iRec = KDA1_KENYMDSerch01() ;
                break;

         case 2://得意先ｺｰﾄﾞ
                //sBuf = "SELECT DISTINCT DTKSCOD FROM KM02";
                //sBuf += " WHERE DTKSCOD LIKE '" + Form1->Edt1->Text + "%'";
                //sBuf += " ORDER BY KM02.DTKSCOD";
    			sBuf = "SELECT ";
    			sBuf += "DISTINCT KM02.DTKSCOD, SM16S.TRSNAM ";
    			sBuf += "FROM KM02,SM16S ";
    			sBuf += " WHERE  (KM02.DTKSCOD = SM16S.TRSCOD (+))";
    			sBuf += " AND KM02.DTKSCOD LIKE '" + Form1->Edt1->Text + "%'";
                //2002/11/22 E.Takase 改訂番号=0 条件追加
    			sBuf += " AND KM02.REVCNT = 0 ";
    			sBuf += " ORDER BY KM02.DTKSCOD";
                break;

         case 3://得意先品番
                sBuf = "SELECT DISTINCT DTKSHIN,DTKSCOD, HINBAN,ZISCOD, ZISNAM,";
                sBuf += " HIST_SOKUT, HIST_KIKAK, HIST_MIN, HIST_MAX FROM KM02";
                //sBuf = "SELECT DISTINCT DTKSHIN FROM KM02";
                sBuf += " WHERE DTKSHIN LIKE '" + Form1->Edt2->Text + "%'";
                //2002/11/22 E.Takase 改訂番号=0 条件追加
    			sBuf += " AND KM02.REVCNT = 0 ";

                if ( (Form1->Edt1->Text) != "" ) {
                    sBuf += " AND KM02.DTKSCOD ='" + Form1->Edt1->Text + "'";
                }
                sBuf += " ORDER BY KM02.DTKSHIN";
                break;

    }

    //問い合せ文実行

    Form2->Query1->SQL->Add(sBuf);
    Form2->Query1->Open();
    Form2->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    switch(flag)
    {
        case 1:
                 Form2->SGr1->ColCount = 2;
        		 Form2->SGr1->Cells[1][iRow] = "測定日";
        		 break;
        case 2:
                 Form2->SGr1->ColCount = 3;
                 Form2->SGr1->ColWidths[2]  = 200;
        		 Form2->SGr1->Cells[1][iRow] = "得意先ｺｰﾄﾞ";
        		 Form2->SGr1->Cells[2][iRow] = "得意先名";

                 break;
        case 3:
                 Form2->SGr1->ColCount = 9;
                 Form2->SGr1->ColWidths[2]  = 0;
                 Form2->SGr1->ColWidths[3]  = 0;
                 Form2->SGr1->ColWidths[4]  = 0;
                 Form2->SGr1->ColWidths[5]  = 0;
                 Form2->SGr1->ColWidths[6]  = 0;
                 Form2->SGr1->ColWidths[7]  = 0;
                 Form2->SGr1->ColWidths[8]  = 0;
        		 Form2->SGr1->Cells[1][iRow] = "得意先品番";
                 break;
    }
    //Form2->SGr1->Cells[1][iRow] = sBuf;

    iRow += 1;

    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true) {
      ShowMessage( MSG_02 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
                Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

            //sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            //if ( flag == 1 ) Form2->SGr1->Cells[1][iRow] = Form1->InsSEPA(sBuf);
            //else Form2->SGr1->Cells[1][iRow] = sBuf;

    		switch(flag)
    		{
        		case 1:  //sBuf = "測定日";
            			sBuf = Form2->Query1->Fields->Fields[0]->AsString;
            			Form2->SGr1->Cells[1][iRow] = Form1->InsSEPA(sBuf);
                		break;
        		case 2:  //sBuf = "得意先ｺｰﾄﾞ";
            			sBuf = Form2->Query1->Fields->Fields[0]->AsString;
                        Form2->SGr1->Cells[1][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[1]->AsString;
                        Form2->SGr1->Cells[2][iRow] = sBuf;
                		break;
        		case 3:  sBuf = "得意先品番";
            			sBuf = Form2->Query1->Fields->Fields[0]->AsString;
                        Form2->SGr1->Cells[1][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[1]->AsString;
                        Form2->SGr1->Cells[2][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[2]->AsString;
                        Form2->SGr1->Cells[3][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[3]->AsString;
                        Form2->SGr1->Cells[4][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[4]->AsString;
                        Form2->SGr1->Cells[5][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[5]->AsString;
                        Form2->SGr1->Cells[6][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[6]->AsString;
                        Form2->SGr1->Cells[7][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[7]->AsString;
                        Form2->SGr1->Cells[8][iRow] = sBuf;
            			sBuf = Form2->Query1->Fields->Fields[8]->AsString;
                        Form2->SGr1->Cells[9][iRow] = sBuf;
                		break;
    		}


            iRow += 1;
            Form2->Query1->Next();
      }
   }

   Form2->SGr1->RowCount = iRow;

   return (iRow) ;

 }



