//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit10.h"
#include "Unit2.h"
#include "unit1.h"
extern KDB1_DATA Tmp_KDB1;             // 選択した工程能力
//---------------------------------------------------------------------------
#pragma package(smart_init)
//検索 メイン
int __fastcall TForm1::MAIN_Serch01(void)
{
	// 新しいトランザクションを開始
	if( Database1->InTransaction == false ){
		Database1->StartTransaction();
		DataSave = false;
	}
	if ( KDB1_Serch01() == 0) {
    	//KM02検索
        if ( KM02_Serch01() == 0 ) {
        	return(0);
        }
    }
    return(1);
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
//KM02 検索
int __fastcall TForm1::KM02_Serch01(void)
{
	int iRow,i;
	AnsiString sBuf;

/*
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	//検索方法② KM02から
	sBuf = "SELECT *  FROM KM02";
	sBuf += " where DTKSHIN = '" + EdtHIN->Text + "'";
	sBuf += " AND ZISCOD = '" + EdtZIS->Text + "'";
	sBuf += "order by DTKSHIN,ZISCOD";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;
*/
	//KM02 検索
	if ( DTKSHIN_Serch() == 0) {
		//検索結果 ０件
		return(0);
	}

	iRow = 0;
	SEQNOMAX = 0;
    //Tmp_KDB1初期化
    Tmp_KDB1_SYOKIKA();

    // 測定日
    Tmp_KDB1.KENSA_YMD  = DelSEPA(EdtYMD->Text);
    // 得意先品番
    if( EdtHIN->Text.IsEmpty() ) Tmp_KDB1.DTKSHIN = " ";
    Tmp_KDB1.DTKSHIN  = EdtHIN->Text;
    //自社品番
    Tmp_KDB1.HINBAN = KM02.HINBAN;
    // 材質コード
    Tmp_KDB1.ZISCOD  = EdtZIS->Text;
    if( Tmp_KDB1.ZISCOD.IsEmpty() ) Tmp_KDB1.ZISCOD = " ";
    //材質名
    Tmp_KDB1.ZISNAM = EdtZISNAM->Caption;
    if( Tmp_KDB1.ZISNAM.IsEmpty() ) Tmp_KDB1.ZISNAM = " ";
    // ロットNo
    Tmp_KDB1.LOTNO  = EdtLOT->Text;
    //測定桁
    Tmp_KDB1.SOKUTE_KET = 2;
    //形状区分
    switch(KM02.KEIJKBN)
    {
        case 1:
        case 2:
        case 3:
			Tmp_KDB1.KEIJKBN = 1;
            break;
        case 4:
			Tmp_KDB1.KEIJKBN = 2;
            break;
        //2002/11/13 コンミ対応 E.Takase
        case 5:
			Tmp_KDB1.KEIJKBN = 3;
            break;
        default:
			Tmp_KDB1.KEIJKBN = 0;
            break;
    }
	//測定数
	Tmp_KDB1.HIST_SOKUT = 30;
    //測定桁
    Tmp_KDB1.SOKUTE_KET = 2;
    // 登録日
    Tmp_KDB1.ADDYMD = FormatDateTime("yyyymmdd",Date());
    // 登録時間
    Tmp_KDB1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // 更新回数
    Tmp_KDB1.UPDCNT  = 0;
    // 更新者
    Tmp_KDB1.UPDCHR  = USER_COD;

    for ( i = 1; i <= 7; i++ ){
    	// SEQNO
    	Tmp_KDB1.SEQNO  = i;

		switch ( i ) {
	        case 1: //母体比重
	        	Tmp_KDB1.KENSA_KMK = 5;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[0];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[0];
	            Tmp_KDB1.TANI = " ";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.BOTAI_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.BOTAI_MAX;
	            Tmp_KDB1.JYOKEN1 = 0;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;

	        case 2: //硬度 圧面
	        	Tmp_KDB1.KENSA_KMK = 6;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[1];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[1];
	            Tmp_KDB1.TANI = "HsC";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.HSC_A_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.HSC_A_MAX;
	            Tmp_KDB1.JYOKEN1 = 1;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;

	        case 3: //硬度 圧面
	        	Tmp_KDB1.KENSA_KMK = 6;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[3];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[3];
	            Tmp_KDB1.TANI = "HsD";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.HSD_A_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.HSD_A_MAX;
	            Tmp_KDB1.JYOKEN1 = 3;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;

	        case 4: //固有抵抗
	        	Tmp_KDB1.KENSA_KMK = 7;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[5];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[5];
	            Tmp_KDB1.TANI = "μΩ・cm";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.KOYU_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.KOYU_MAX;
	            Tmp_KDB1.JYOKEN1 = KM02.KOYU_DEN;
	            Tmp_KDB1.JYOKEN2 = KM02.KOYU_PRO;
	            break;

	        case 5: //抗折力
	        	Tmp_KDB1.KENSA_KMK = 8;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[6];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[6];
	            Tmp_KDB1.TANI = "MPa";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.MAGE_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.MAGE_MAX;
	            Tmp_KDB1.JYOKEN1 = KM02.MAGE_SPAN;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;

	        case 6:  //ブラシ厚さ
	        	Tmp_KDB1.KENSA_KMK = 2;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[9];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[9];
	            Tmp_KDB1.TANI = "mm";
	            Tmp_KDB1.HIST_KIKAK = KM02.HIST_KIKAK;
	            Tmp_KDB1.HIST_MIN = KM02.HIST_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.HIST_MAX;
	            Tmp_KDB1.JYOKEN1 = 0;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;

	        case 7: //ブラシ幅
	        	Tmp_KDB1.KENSA_KMK = 1;
				Tmp_KDB1.KOUMOKU_J = Cmb1->Items->Strings[10];
				Tmp_KDB1.KOUMOKU_E = Cmb2->Items->Strings[10];
	            Tmp_KDB1.TANI = "mm";
	            Tmp_KDB1.HIST_KIKAK = 1;
	            Tmp_KDB1.HIST_MIN = KM02.BURASI_MIN;
	            Tmp_KDB1.HIST_MAX = KM02.BURASI_MAX;
	            Tmp_KDB1.JYOKEN1 = 0;
	            Tmp_KDB1.JYOKEN2 = 0;
	            break;
		}

		//AddData
		if( AddData() == False ){
        	SBr1->Panels->Items[0]->Text = "初期データ登録中に登録失敗しました。";
        	SBr1->Update();
			return(1);
		}
        //新規データをSGr1に表示
        // グリッドにデータをセットします。
        sBuf = SGr1->RowCount;
		SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

		sBuf = Tmp_KDB1.KOUMOKU_J;
		SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;   //検査項目（日本語）

		sBuf = Tmp_KDB1.KOUMOKU_E;
		SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;   //検査項目（英語）

		sBuf = IntToStr(Tmp_KDB1.HIST_SOKUT);
		SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;   //測定数

		sBuf = Tmp_KDB1.TANI;
		SGr1->Cells[3][SGr1->RowCount - 1] = sBuf;   //単位

		sBuf = IntToStr(Tmp_KDB1.KEIJKBN);
		SGr1->Cells[11][SGr1->RowCount - 1] = sBuf;   //形状区分
        switch(Tmp_KDB1.KEIJKBN)
        {
			case 1: //直方体
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "直方体";
                SGr1->Cells[30][SGr1->RowCount - 1] = "直方体";
                break;
            case 2: //円柱
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "円柱";
                SGr1->Cells[30][SGr1->RowCount - 1] = "円柱";
                break;
            case 3: //コンミ
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "コンミ";
                SGr1->Cells[30][SGr1->RowCount - 1] = "コンミ";
                break;
            default:
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = " ";
                SGr1->Cells[30][SGr1->RowCount - 1] = " ";
                break;

        }

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		switch(StrToInt(sBuf))   //規格名
		{
			case 1:
				SGr1->Cells[5][SGr1->RowCount - 1] = "両側";

				//下限規格
                SGr1->Cells[6][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //上限規格
                SGr1->Cells[7][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

			case 2:
				SGr1->Cells[5][SGr1->RowCount - 1] = "下限";

				//下限規格
                SGr1->Cells[6][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //上限規格
                SGr1->Cells[7][SGr1->RowCount - 1] = " ";

				break;

			case 3:
				SGr1->Cells[5][SGr1->RowCount - 1] = "上限";

                //下限規格
				SGr1->Cells[6][SGr1->RowCount - 1] = " ";

                //上限規格
                SGr1->Cells[7][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

		}
		if ( Tmp_KDB1.HIST_SOKUT == Tmp_KDB1.SOKUTE_SU ) {
			sBuf = "済";//	測定済
		} else  {
			if (Tmp_KDB1.SOKUTE_SU > 0 ) {
				sBuf = "途中";//	測定途中
			} else {
				sBuf = "未";//	未測定
			}
		}
		SGr1->Cells[8][SGr1->RowCount - 1] = sBuf;


		sBuf = Tmp_KDB1.KENSA_YMD;
		SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;                //検査年月日

		sBuf = Tmp_KDB1.DTKSHIN;
		SGr1->Cells[12][SGr1->RowCount - 1] = sBuf;                //得意先品番

		sBuf = Tmp_KDB1.HINBAN;
		SGr1->Cells[13][SGr1->RowCount - 1] = sBuf;               //自社品番

		sBuf = Tmp_KDB1.ZISCOD;
		SGr1->Cells[14][SGr1->RowCount - 1] = sBuf;               //材質コード

		sBuf = Tmp_KDB1.ZISNAM;
		SGr1->Cells[15][SGr1->RowCount - 1] = sBuf;               //材質名

		sBuf = Tmp_KDB1.LOTNO;
		SGr1->Cells[16][SGr1->RowCount - 1] = sBuf;               //ロットNO

		sBuf = IntToStr(Tmp_KDB1.SEQNO);
		SGr1->Cells[17][SGr1->RowCount - 1] = sBuf;               //SEQNO

		sBuf = IntToStr(Tmp_KDB1.KENSA_KMK);
		SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;               //検査項目

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;               //工程能力 規格

		sBuf = IntToStr(Tmp_KDB1.SOKUTE_SU);
		SGr1->Cells[20][SGr1->RowCount - 1] = sBuf;               //測定数

		sBuf = Tmp_KDB1.ADDYMD;
		SGr1->Cells[21][SGr1->RowCount - 1] = sBuf;               //登録日

		sBuf = Tmp_KDB1.ADDTIM;
		SGr1->Cells[22][SGr1->RowCount - 1] = sBuf;               //登録時間

		sBuf = " ";
		SGr1->Cells[23][SGr1->RowCount - 1] = sBuf;               //変更日

		sBuf = " ";
		SGr1->Cells[24][SGr1->RowCount - 1] = sBuf;               //変更時間

		sBuf = IntToStr(Tmp_KDB1.UPDCHR);
		SGr1->Cells[25][SGr1->RowCount - 1] = sBuf;               //更新者

		sBuf = IntToStr(Tmp_KDB1.UPDCNT);
		SGr1->Cells[26][SGr1->RowCount - 1] = sBuf;               //更新回数

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN1);
		SGr1->Cells[27][SGr1->RowCount - 1] = sBuf;               //測定条件1

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN2);
		SGr1->Cells[28][SGr1->RowCount - 1] = sBuf;               //測定条件2

		sBuf = Tmp_KDB1.JYOKEN3;
		SGr1->Cells[29][SGr1->RowCount - 1] = sBuf;               //測定条件3

         //2002/11/18 E.Takase 測定者追加
		sBuf = Tmp_KDB1.UPDCHR;
		SGr1->Cells[9][SGr1->RowCount - 1] = Form2->GetTANNAM(sBuf);

		// 一行増やす
		SGr1->RowCount = SGr1->RowCount + 1;
		SEQNOMAX++;
    }
     //// 新しい行を選択
     //SGr1->Row = SGr1->RowCount - 1;
     //
     //SGr1->SetFocus();
     //
     //SBr1->Panels->Items[0]->Text = "";
     //SBr1->Update();
     //
     // データを変更したフラグ
     DataSave = true;

	return(1);
}
//KDB1から検索
int __fastcall TForm1::KDB1_Serch01(void)
{
	int iRow,i;
	AnsiString sBuf;

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行
	//検索方法① KDB1から
	sBuf = "SELECT *  FROM KDB1";
	sBuf += " where KENSA_YMD = '" + DelSEPA(EdtYMD->Text) + "'";
	sBuf += " AND DTKSHIN = '" + EdtHIN->Text + "'";
	sBuf += " AND LOTNO = '" + EdtLOT->Text + "'";
	sBuf += "order by KENSA_YMD,SEQNO";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//検索結果 ０件
		//検索方法② KM02から

		return(0);

	}
	iRow = 0;
	SEQNOMAX = 0;

	while( !Query1->Eof ){

		// グリッドの最大行数が超えていないかチェックする
		if( iRow >= SGr1->RowCount ){
			SGr1->RowCount = iRow + 1;
		}

		//SEQNO
		if ( SEQNOMAX < StrToInt (Form1->Query1->FieldValues["SEQNO"])){
			SEQNOMAX =  StrToInt (Form1->Query1->FieldValues["SEQNO"]);
		}

		// グリッドにデータをセットします。
		sBuf = iRow + 1;
		SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

		sBuf = Form1->Query1->FieldValues["KOUMOKU_J"];
		SGr1->Cells[1][iRow] = sBuf;   //検査項目（日本語）

		sBuf = Form1->Query1->FieldValues["KOUMOKU_E"];
		SGr1->Cells[2][iRow] = sBuf;   //検査項目（英語）

		sBuf = Form1->Query1->FieldValues["HIST_SOKUT"];
		SGr1->Cells[4][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;   //測定数

		sBuf = Form1->Query1->FieldValues["TANI"];
		SGr1->Cells[3][iRow] = sBuf;   //単位

		sBuf = Form1->Query1->FieldValues["KEIJKBN"];
		SGr1->Cells[11][iRow] = sBuf;   //形状区分
			switch(StrToInt(sBuf))
			{
				case 1: //直方体
					//2002/11/18 E.Takase SGr1->Cells[9][iRow] = "直方体";
					SGr1->Cells[30][iRow] = "直方体";
					break;
				case 2: //円柱
					//2002/11/18 E.Takase SGr1->Cells[9][iRow] = "円柱";
					SGr1->Cells[30][iRow] = "円柱";
					break;
				case 3: //コンミ 2002/11/14 E.Takase
					//2002/11/18 E.Takase SGr1->Cells[9][iRow] = "コンミ";
					SGr1->Cells[30][iRow] = "コンミ";
					break;
				default:
					//2002/11/18 E.Takase SGr1->Cells[9][iRow] = " ";
					SGr1->Cells[30][iRow] = " ";
					break;
			}
		sBuf = Form1->Query1->FieldValues["JYOKEN1"];
		SGr1->Cells[27][iRow] = sBuf;               //測定条件1

		sBuf = Form1->Query1->FieldValues["JYOKEN2"];
		SGr1->Cells[28][iRow] = sBuf;               //測定条件2

		sBuf = Form1->Query1->FieldValues["JYOKEN3"];
		SGr1->Cells[29][iRow] = sBuf;               //測定条件3

		sBuf = Form1->Query1->FieldValues["KENSA_KMK"];
		SGr1->Cells[18][iRow] = sBuf;               //検査項目

		sBuf = Form1->Query1->FieldValues["HIST_KIKAK"];
		switch(StrToInt(sBuf))   //規格名
		{
			case 1:
				SGr1->Cells[5][iRow] = "両側";

				sBuf = FormatFloat("#0.000",StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]));//	　〃　　　　下限規格
		           //SGr1->Cells[6][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           //					StrToInt(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]), Form1->Query1->FieldValues["TANI"]);
		           SGr1->Cells[6][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           					StrToFloat(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]), Form1->Query1->FieldValues["TANI"]);

				sBuf = FormatFloat("#0.000",StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]));//	　〃　　　　上限規格
		           //SGr1->Cells[7][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           //					StrToInt(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]), Form1->Query1->FieldValues["TANI"]);
		           SGr1->Cells[7][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           					StrToFloat(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]), Form1->Query1->FieldValues["TANI"]);

				break;

			case 2:
				SGr1->Cells[5][iRow] = "下限";
		           //下限規格
				sBuf = FormatFloat("#0.000",StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]));
		           //SGr1->Cells[6][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           //					StrToInt(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]), Form1->Query1->FieldValues["TANI"]);
		           SGr1->Cells[6][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           					StrToFloat(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MIN"]), Form1->Query1->FieldValues["TANI"]);

				//上限規格
				SGr1->Cells[7][iRow] = " ";
				break;

			case 3:
				SGr1->Cells[5][iRow] = "上限";

		           //下限規格
				SGr1->Cells[6][iRow] = " ";

				sBuf = FormatFloat("#0.000",StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]));//	　〃　　　　上限規格
		           //SGr1->Cells[7][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           //					StrToInt(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]), Form1->Query1->FieldValues["TANI"]);
		           SGr1->Cells[7][iRow] = KENSASGr_Set(StrToInt(SGr1->Cells[18][iRow]),
		           					StrToFloat(SGr1->Cells[27][iRow]), StrToFloat(Form1->Query1->FieldValues["HIST_MAX"]), Form1->Query1->FieldValues["TANI"]);
				break;

		}

		if ( StrToInt (Form1->Query1->FieldValues["HIST_SOKUT"]) == StrToInt (Form1->Query1->FieldValues["SOKUTE_SU"] )) {
			sBuf = "済";//	測定済
		} else  {
			if (StrToInt (Form1->Query1->FieldValues["SOKUTE_SU"]) > 0 ) {
				sBuf = "途中";//	測定途中
			} else {
				sBuf = "未";//	未測定
			}
		}
		SGr1->Cells[8][iRow] = sBuf;


		sBuf = Form1->Query1->FieldValues["KENSA_YMD"];
		SGr1->Cells[10][iRow] = sBuf;                //検査年月日

		sBuf = Form1->Query1->FieldValues["DTKSHIN"];
		SGr1->Cells[12][iRow] = sBuf;                //得意先品番

		sBuf = Form1->Query1->FieldValues["HINBAN"];
		SGr1->Cells[13][iRow] = sBuf;               //自社品番

		sBuf = Form1->Query1->FieldValues["ZISCOD"];
		SGr1->Cells[14][iRow] = sBuf;               //材質コード

		sBuf = Form1->Query1->FieldValues["ZISNAM"];
		SGr1->Cells[15][iRow] = sBuf;               //材質名

		sBuf = Form1->Query1->FieldValues["LOTNO"];
		SGr1->Cells[16][iRow] = sBuf;               //ロットNO

		sBuf = Form1->Query1->FieldValues["SEQNO"];
		SGr1->Cells[17][iRow] = sBuf;               //SEQNO



		sBuf = Form1->Query1->FieldValues["HIST_KIKAK"];
		SGr1->Cells[19][iRow] = sBuf;               //工程能力 規格

		sBuf = Form1->Query1->FieldValues["SOKUTE_SU"];
		SGr1->Cells[20][iRow] = sBuf;               //測定数

		if ( Form1->Query1->FieldValues["ADDYMD"].IsNull())
			sBuf = " ";
		else
			sBuf = Form1->Query1->FieldValues["ADDYMD"];
		SGr1->Cells[21][iRow] = sBuf;               //登録日

		if ( Form1->Query1->FieldValues["ADDTIM"].IsNull())
			sBuf = " ";
		else
			sBuf = Form1->Query1->FieldValues["ADDTIM"];
		SGr1->Cells[22][iRow] = sBuf;               //登録時間

		if ( Form1->Query1->FieldValues["UPDYMD"].IsNull())
			sBuf = " ";
		else
			sBuf = Form1->Query1->FieldValues["UPDYMD"];
		SGr1->Cells[23][iRow] = sBuf;               //変更日

		if ( Form1->Query1->FieldValues["UPDTIM"].IsNull())
			sBuf = " ";
		else
			sBuf = Form1->Query1->FieldValues["UPDTIM"];
		SGr1->Cells[24][iRow] = sBuf;               //変更時間

		sBuf = Form1->Query1->FieldValues["UPDCHR"];
		SGr1->Cells[25][iRow] = sBuf;               //更新者

		sBuf = Form1->Query1->FieldValues["UPDCNT"];
		SGr1->Cells[26][iRow] = sBuf;               //更新回数

        //2002/11/18 E.Takase 測定者追加
		sBuf = Form1->Query1->FieldValues["UPDCHR"];
		SGr1->Cells[9][SGr1->RowCount - 1] = Form2->GetTANNAM(sBuf);
		// カーソルを次にセットする
		Query1->Next();

		iRow += 1;
	}
    SGr1->RowCount = iRow + 1;
     SGr1->Cells[0][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[1][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[2][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[3][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[4][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[5][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[6][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[7][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[8][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[9][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[10][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[11][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[12][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[13][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[14][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[15][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[16][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[17][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[18][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[19][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[20][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[21][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[22][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[23][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[24][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[25][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[26][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[27][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[28][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[29][SGr1->RowCount - 1 ] = "";
     SGr1->Cells[30][SGr1->RowCount - 1 ] = "";
	return(1);
}
