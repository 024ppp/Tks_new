//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop

#include "Unit11.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#define COM_DIFF 0.000001
// π値
extern pi ;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm11 *Form11;

//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//コピー元データの取得
void __fastcall TForm11::FormActivate(TObject *Sender)
{
    int i;

    DataCopyFlag = 0;

	SGr1->RowCount = 2;

	SGr1->Cells[0][0] = "";
	SGr1->Cells[1][0] = "";
	SGr1->Cells[0][1] = "";
	SGr1->Cells[1][1] = "";

	// グリッドの初期化
	SGr1->ColCount = 10;
	SGr1->ColWidths[0]  = 50;
	SGr1->ColWidths[1]  = 230;
	SGr1->ColWidths[2]  = 50;
	SGr1->ColWidths[3]  = 40;
	SGr1->ColWidths[4]  = 100;
	SGr1->ColWidths[5]  = 100;

	SGr1->ColWidths[6]  = 0;
	SGr1->ColWidths[7]  = 0;
	SGr1->ColWidths[8]  = 0;
	SGr1->ColWidths[9]  = 0;

    i = CopyData_Serch();

    SGr1->SetFocus();
    SGr1SelectCell( Sender, 1, 1, true);

}
//---------------------------------------------------------------------------
void __fastcall TForm11::SGr1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
	// 最初レコードのﾃﾞｰﾀを変数へ保存
    //HIST_SOKUT
	if (  SGr1->Cells[2][ARow].IsEmpty() )  Select_Str1 = " ";
	Select_Str1 = SGr1->Cells[2][ARow] ;

	//KENSA_KMK
	if ( SGr1->Cells[6][ARow].IsEmpty() )  Select_Str2 = " ";
	Select_Str2 = SGr1->Cells[6][ARow] ;

	//SEQNO
	if ( SGr1->Cells[7][ARow].IsEmpty() )  Select_Str3 = " ";
	Select_Str3 = SGr1->Cells[7][ARow] ;

	//SOKUTE_SU
	if ( SGr1->Cells[8][ARow].IsEmpty() )  Select_Str4 = " ";
	Select_Str4 = SGr1->Cells[8][ARow] ;

	//KEIJKBN
	if ( SGr1->Cells[9][ARow].IsEmpty() )  Select_Str5 = " ";
	else Select_Str5 = SGr1->Cells[9][ARow] ;

	Select_Cnt = ARow;

}
//---------------------------------------------------------------------------
//「Ｆ２：前項」
void __fastcall TForm11::BtnF02Click(TObject *Sender)
{
    if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}
//---------------------------------------------------------------------------
// 「Ｆ３：次項」
void __fastcall TForm11::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}
//---------------------------------------------------------------------------
//「Ｆ４：選択」
void __fastcall TForm11::BtnF04Click(TObject *Sender)
{
    int flag = 0;
    AnsiString sMsg;

    int n;
    int m;

    n = Cur_Kdb1.HIST_SOKUT;
    m = Select_Str4.ToIntDef(0);

    if ( n != m ) {
        sMsg = "測定数がコピーするデータとちがいますが、処理を続行しますか？";
        switch( MessageDlg( sMsg, mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」
            case mrYes:
                    break;
            // 「No」
            case mrNo:
                    flag = 1;
                    break;
            case mrCancel:
                    flag = 1;
                    return;
                    break;
        }
    }


    //測定データをコピーする
    if ( flag == 0 ) {
        SetCopyData();
        DataCopyFlag = 1;
    }

    //測定画面へ
    BtnF12Click(Sender) ;

}
//---------------------------------------------------------------------------
//「Ｆ１２：終了」
void __fastcall TForm11::BtnF12Click(TObject *Sender)
{
//
     Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm11::FormKeyDown(TObject *Sender, WORD &Key,
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
//データコピー元 候補　検索
//---------------------------------------------------------------------------
int __fastcall TForm11::CopyData_Serch(void)
{
	AnsiString str;
	int i = 1;
    int n;
    int m;

	//KDB1からデータコピー元候補を抽出
	Query1->Close();
	Query1->SQL->Clear();

	sBuf = " SELECT";
	sBuf += " KENSA_YMD, DTKSHIN, HINBAN, ZISCOD, ZISNAM, LOTNO, SEQNO, ";
	sBuf += " KENSA_KMK, KOUMOKU_J, KOUMOKU_E, KEIJKBN, ";
	sBuf += " TANI, HIST_SOKUT, SOKUTE_SU, ADDYMD, UPDYMD, UPDCHR, UPDCNT ";
	sBuf += " FROM KDB1";
	sBuf += " WHERE KENSA_YMD='" +  Cur_Kdb1.KENSA_YMD + "'";
	sBuf += " AND DTKSHIN='" +  Cur_Kdb1.DTKSHIN + "'";
	sBuf += " AND LOTNO='" +  Cur_Kdb1.LOTNO + "'";
    //2002/12/28 E.Takase
	//sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 ) ";
	sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 OR KENSA_KMK=12 ) ";
	sBuf += " AND SEQNO<> "+  IntToStr(Cur_Kdb1.SEQNO) ;
	sBuf += " ORDER BY SEQNO";


	//問い合せ文実行

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	int iRow = 0 ;
	sBuf = "NO.";
	SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
	SGr1->Cells[1][iRow] = "検査項目";
	SGr1->Cells[2][iRow] = "測定数";
	SGr1->Cells[3][iRow] = "測定";
	SGr1->Cells[4][iRow] = "測定者";
	SGr1->Cells[5][iRow] = "更新日";

	SGr1->Cells[6][iRow] = "KENSA_KMK";
	SGr1->Cells[7][iRow] = "SEQNO";
	SGr1->Cells[8][iRow] = "SOKUTE_SU";
	SGr1->Cells[9][iRow] = "KEIJKBN";

    iRow += 1;

    if ( Query1->Bof == true && Query1->Eof == true) {
		SGr1->Cells[1][1]=" " ;
		SGr1->Cells[2][1]=" " ;
		SGr1->Cells[3][1]=" " ;
		SGr1->Cells[4][1]=" " ;
		SGr1->Cells[5][1]=" " ;

		ShowMessage( MSG_02 );
      return 0;
    }else {
      Query1->First();
      while( !Query1->Eof ) {

			// グリッドの最大行数が超えていないかチェックする
			if( iRow >= SGr1->RowCount ){
			    SGr1->RowCount = iRow+1;
			}
			sBuf = iRow ;
			SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

			sBuf = Query1->FieldValues["KOUMOKU_J"];
			SGr1->Cells[1][iRow] = sBuf;
			sBuf = Query1->FieldValues["HIST_SOKUT"];
			SGr1->Cells[2][iRow] = sBuf;

            n = Query1->FieldValues["HIST_SOKUT"];
            m = Query1->FieldValues["SOKUTE_SU"];
            if ( n == m ) {
                sBuf = "済";
            } else {
                if ( m > 0 ) {
                    sBuf = "途中";
                } else {
                    sBuf = "未";
                }
            }
			SGr1->Cells[3][iRow] = sBuf;

			sBuf = Query1->FieldValues["UPDCHR"];
			SGr1->Cells[4][iRow] = Form2->GetTANNAM(sBuf);;
		    if ( Query1->FieldValues["UPDYMD"].IsNull()) {
                sBuf = " ";
            } else  {
                sBuf = Query1->FieldValues["UPDYMD"];
            }
            if ( Trim(sBuf) == "" ) {
		        if ( Query1->FieldValues["ADDYMD"].IsNull()) {
                    sBuf = " ";
                } else  {
                    sBuf = Query1->FieldValues["ADDYMD"];
                }
            }
            if ( Trim(sBuf) != "" ) {
                sBuf = sBuf.Insert("/",5);
                sBuf = sBuf.Insert("/",8);
            }
			SGr1->Cells[5][iRow] = sBuf;

			sBuf = Query1->FieldValues["KENSA_KMK"];
			SGr1->Cells[6][iRow] = sBuf;
			sBuf = Query1->FieldValues["SEQNO"];
			SGr1->Cells[7][iRow] = sBuf;
			sBuf = Query1->FieldValues["SOKUTE_SU"];
			SGr1->Cells[8][iRow] = sBuf;
			sBuf = Query1->FieldValues["KEIJKBN"];
			SGr1->Cells[9][iRow] = sBuf;

            iRow += 1;
            Query1->Next();
      }
   }

   SGr1->RowCount = iRow;

   return (iRow) ;

}
//---------------------------------------------------------------------------
//データコピー元 セット
//---------------------------------------------------------------------------
void __fastcall TForm11::SetCopyData(void)
{

	AnsiString str;
	int i = 1;
    int n;
    int T_No;

	//KDB2から測定値を抽出
	Query1->Close();
    Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += " SOKUTEI_NO, SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, ";
    sBuf += " SOKUTEI_MEI4, SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7 ";
    sBuf += " FROM KDB2 ";
    sBuf += " WHERE KENSA_YMD = '" + Cur_Kdb1.KENSA_YMD + "' " + " AND SEQNO = '" + Select_Str3 + "' ";
    sBuf += " AND DTKSHIN = '" + Cur_Kdb1.DTKSHIN + "' " + " AND LOTNO = '" + Cur_Kdb1.LOTNO + "' ";
    sBuf += " AND SOKUTEI_NO <= " + IntToStr(Cur_Kdb1.HIST_SOKUT) ;
    sBuf += " ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

	//問い合せ文実行
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    i = 0;
    if ( Query1->Bof == true && Query1->Eof == true) {
        ShowMessage( MSG_02 );
        return ;
    }else {
        Query1->First();
        while( !Query1->Eof ) {
            //測定値 コピー
            if ( Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                i = 0;
            } else {
                i = Query1->FieldValues["SOKUTEI_NO"]-1;
            }
            if ( i < Cur_Kdb1.HIST_SOKUT ) {
                //コンミ 以外の場合
                if ( Select_Str5 != "3" ) {
                    if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                        M_Kdb2[i].SOKUTEI_MEI1 = 0;
                    else
                        M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];

                    if ( Query1->FieldValues["SOKUTEI_MEI2"].IsNull())
                        M_Kdb2[i].SOKUTEI_MEI2 = 0;
                    else
                        M_Kdb2[i].SOKUTEI_MEI2 = Query1->FieldValues["SOKUTEI_MEI2"];

                    //コピー元 母体の場合 長さもコピー
                    if ( Cur_Kdb1.KENSA_KMK == 5 && Select_Str2 == "5" ) {
                        if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                            M_Kdb2[i].SOKUTEI_MEI3 = 0;
                        else
                            M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI3"];
                    }
                //コンミの場合
                } else {
                    //コピー元 母体の場合
                    if ( Select_Str2 == "5" ) {
                        //コピー先 母体の場合
                        if ( Cur_Kdb1.KENSA_KMK == 5 ) {
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];

                            if ( Query1->FieldValues["SOKUTEI_MEI2"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI2 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI2 = Query1->FieldValues["SOKUTEI_MEI2"];

                            if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI3 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI3"];

                        } else {
                        //コピー先 母体以外の場合
                            if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI3"];
                        }
                    } else {
                    //コピー元 母体以外の場合
                        //コピー先 母体の場合
                        //if ( Cur_Kdb1.KEIJKBN == 3 ) {
                        if ( Cur_Kdb1.KENSA_KMK == 5 ) {
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI3 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI1"];
                        } else {
                        //コピー先 母体以外の場合
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];
                        }
                    }

                }
            }

            Query1->Next();
        }

        //再計算
        switch( Cur_Kdb1.KENSA_KMK ) {
            //母体比重
            case 5:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Botai_Cal2(i);
                }
                break;
            //抵抗率
            case 7:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Teikou_Cal2(i);
                }
                break;
            //曲げ強さ
            //曲げ強さ(現物)
            case 8:
            case 12:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Kousetu_Cal2(i);
                }
                break;
        }


    }


}
//---------------------------------------------------------------------------
//データコピー元が存在するかをチェック
//---------------------------------------------------------------------------
bool __fastcall TForm11::ChkCopyData(void)
{

	AnsiString str;
	int i = 1;
    int n;
    int T_No;

	//KDB2から測定値を抽出
	Query1->Close();
    Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
	sBuf = " SELECT";
	sBuf += " KENSA_YMD, DTKSHIN, HINBAN, ZISCOD, ZISNAM, LOTNO, SEQNO, ";
	sBuf += " KENSA_KMK, KOUMOKU_J, KOUMOKU_E, KEIJKBN, ";
	sBuf += " TANI, HIST_SOKUT, SOKUTE_SU, ADDYMD, UPDYMD, UPDCHR, UPDCNT ";
	sBuf += " FROM KDB1";
	sBuf += " WHERE KENSA_YMD='" +  Cur_Kdb1.KENSA_YMD + "'";
	sBuf += " AND DTKSHIN='" +  Cur_Kdb1.DTKSHIN + "'";
	sBuf += " AND LOTNO='" +  Cur_Kdb1.LOTNO + "'";
	sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 ) ";
	sBuf += " AND SEQNO<> "+  IntToStr(Cur_Kdb1.SEQNO) ;
	sBuf += " ORDER BY SEQNO";

	//問い合せ文実行
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    i = 0;
    if ( Query1->Bof == true && Query1->Eof == true) {
        return false;
    }else {
        return true;
    }
}
//---------------------------------------------------------------------------
// 母体比重計算
// 直方体： 重量 / （長さ * 幅 * 高さ）
// 円柱： 直径 * 直径 * PI /4 * 高さ
// コンミ： 重量 / ｛（（直径/2）*（直径/2）* PI） - （（内径/2）*（内径/2）* PI）｝* 厚さ
void __fastcall TForm11::Botai_Cal2(int i)
{
 char tempo[64];
 
 M_Kdb2[i].SOKUTEI_CH = 0;
 
 // 円柱
 if (Cur_Kdb1.KEIJKBN == 2) {
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI4 /
                                  (M_Kdb2[i].SOKUTEI_MEI2/10.0 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI3/40.0);
       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);
    }
 //コンミ
 } else if (Cur_Kdb1.KEIJKBN == 3) {
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       if ( M_Kdb2[i].SOKUTEI_MEI1 == M_Kdb2[i].SOKUTEI_MEI2 ) {

          M_Kdb2[i].SOKUTEI_CH = 0;
       } else {

          M_Kdb2[i].SOKUTEI_CH =  M_Kdb2[i].SOKUTEI_MEI4/
										((pi*(M_Kdb2[i].SOKUTEI_MEI2/2.0)
											*(M_Kdb2[i].SOKUTEI_MEI2/2.0) -
										pi*(M_Kdb2[i].SOKUTEI_MEI1/2.0)
											*(M_Kdb2[i].SOKUTEI_MEI1/2.0))
										*M_Kdb2[i].SOKUTEI_MEI3/1000.0);
          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
    }
 //直方体
 } else {
 
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI4 /
                                  (M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI3/10.0);
       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
 
 }
}

//---------------------------------------------------------------------------
// 抗折力計算
// 直方体：N/(cm * cm): (300 * 負荷 * スパン) / ( 2 * 幅 * 厚さ * 厚さ）
//         MPa: (3 * スパン * 負荷) / (2 * 幅 * 厚さ * 厚さ）
// 円柱：  N/(cm * cm): (8 * 負荷 * スパン) / ( 100 * PI * 直径 * 直径 * 直径）
//         MPa: (8 * スパン * 負荷) / (PI * 直径 * 直径 * 直径）
// コンミ ： 負荷
void __fastcall TForm11::Kousetu_Cal2(int i)
{
 char tempo[64];

 M_Kdb2[i].SOKUTEI_CH = 0;

 //円柱
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 100.0 * M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2")  {
       if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4) /
                                   ( M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI2) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    // N/(cm * cm) or Kfg
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 //コンミ
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI3 ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
    return;

 //直方体
 } else {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 200.0 * M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2" )  {
       if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4) /
                                   ( 2.0 * M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI1 *
                                   M_Kdb2[i].SOKUTEI_MEI1) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    // N/(cm * cm)  or Kfg
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 2.0 * M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
    return;
 }


}

//---------------------------------------------------------------------------

// 固有抵抗率計算
// 直方体：(厚さ * 幅 * 平均電圧 * 1000) / (平均電流 * プローブ)
// 円柱：（平均電圧 * 半径 * 半径 * PI * 1000) / (平均電流 * プローブ)
// コンミ： 平均電圧
void __fastcall TForm11::Teikou_Cal2(int i)
{
 char tempo[64];

 M_Kdb2[i].SOKUTEI_CH = 0;

 //円柱
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                  M_Kdb2[i].SOKUTEI_MEI2/10.0 * pi/4 * 1000.0 *
                                  (M_Kdb2[i].SOKUTEI_MEI3 +
                                   M_Kdb2[i].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[i].SOKUTEI_MEI4 +
                                   M_Kdb2[i].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[i].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 //コンミ
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI3 + M_Kdb2[i].SOKUTEI_MEI5) / 2.0 ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 } else {
 //直方体
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                  M_Kdb2[i].SOKUTEI_MEI2/10.0 * 1000.0 *
                                  (M_Kdb2[i].SOKUTEI_MEI3 +
                                   M_Kdb2[i].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[i].SOKUTEI_MEI4 +
                                   M_Kdb2[i].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[i].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 }

}
//---------------------------------------------------------------------------

