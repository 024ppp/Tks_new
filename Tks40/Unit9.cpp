//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
#include "unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//検査項目SGrのセット
AnsiString __fastcall TForm1::KENSASGr_Set(int KMK,double JYOKEN, double KIKAKU, AnsiString tani)
{
	AnsiString sBuf;

    switch(KMK)
    {
        case 0: //リード線長さ
        	sBuf = FormatFloat("#0.00",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-1) + sBuf);
            break;
        case 1: //ブラシ幅
        	sBuf = FormatFloat("#0.000",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        case 3: //リード線取付抵抗
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            break;

        case 4: //リード線引張強度
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            break;

        case 5: //母体比重
        	sBuf = FormatFloat("#0.00",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-1) + sBuf);
            break;

        case 6: //硬度
        	switch ( int(JYOKEN) )
            {
        		case 1: //硬度 圧面
        			sBuf = FormatFloat("#0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            		break;

        		case 2: //硬度 側面
        			sBuf = FormatFloat("#0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            		break;

        		case 3: //硬度 圧面
        			sBuf = FormatFloat("#0.0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            		break;

        		case 4: //硬度 側面
        			sBuf = FormatFloat("#0.0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            		break;

        		default:
                	sBuf = FormatFloat("#0.000",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            		break;
        	}
            break;
        case 7: //固有抵抗
        	sBuf = FormatFloat("#0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            break;

        case 8: //抗折力
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        case 9: //座屈
        	sBuf = FormatFloat("#0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            break;

        case 10: //曲げ強さ（現物）
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        default:
        	if ( tani == "N" || tani == "Kgf" ) {
        		sBuf = FormatFloat("#0.0",KIKAKU);
            } else {
            	if ( tani == "度" ) {
               		sBuf = FormatFloat("#0.00",KIKAKU);
                } else {
                	sBuf = FormatFloat("#0.000",KIKAKU);
                }
            }
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

	}

}

//検査項目CmbIndxのセット
int __fastcall TForm1::KENSACmb_Set(int KMK,double JYOKEN)
{
    Cmb5->Clear();


    switch(KMK)
    {
        case 0: //リード線長さ
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(13);
            break;
        case 1: //ブラシ幅
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(10);
            break;

        case 3: //リード線取付抵抗
            Cmb5->Items->Add( "mV/A" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(7);
            break;

        case 4: //リード線引張強度
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(8);
            break;

        case 5: //母体比重
            Cmb5->Items->Add( " " );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(0);
            break;

        case 6: //硬度
        	switch ( int(JYOKEN) )
            {
        		case 1: //硬度 圧面
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 0;
            		Edt3->FPos = 0;
            		return(1);
            		break;

        		case 2: //硬度 側面
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 0;
            		Edt3->FPos = 0;
            		return(2);
            		break;

        		case 3: //硬度 圧面
            		Cmb5->Items->Add( "HsD" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 1;
            		Edt3->FPos = 1;
            		return(3);
            		break;

        		case 4: //硬度 側面
            		Cmb5->Items->Add( "HsD" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 1;
            		Edt3->FPos = 1;
            		return(4);
            		break;

        		default:
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 3;
            		Edt3->FPos = 3;
    				return(1);
            		break;
        	}
            break;
        case 7: //固有抵抗
            Cmb5->Items->Add( "μΩ・cm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            return(5);
            break;

        case 8: //抗折力
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(6);
            break;

        case 9: //座屈
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            return(18);
            break;

        case 2: //ブラシ厚さ
		        //ブラシ長さ
		        //リード線スポット厚さ
		        //リード線スポット幅
		        //リード線スポット長さ
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(12);
            break;


        case 10: //摺動面R
            Cmb5->Items->Add( "度" );
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(12);
            break;

		case 11:  //ターミナル溶接強度
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(12);
            break;

        case 12: //曲げ強さ（現物）
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(19);
            break;

        default:
            Cmb5->Items->Add( "mm" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "度" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(12);
            break;

	}

}

//検査項目のセット
void __fastcall TForm1::KENSAKMK_Set(int CmbIndx)
{
    //CmbIndx = CmbのItemIndex
    //EdtKMK->Text
    Cmb5->Clear();
	EdtJYOKEN1->Text = "0";
	EdtJYOKEN2->Text = "0";
	EdtJYOKEN3->Text = " ";

    Cmb3->ItemIndex = 0;
    //Cmb4->ItemIndex = 0;

	Edt2->Enabled = true;
	Edt3->Enabled = true;
    //測定数
	Edt1->Text = "30";

    //形状区分
    switch(KM02.KEIJKBN)
    {
        case 1:
        case 2:
        case 3:
			EdtKEIJKBN->Text = "1";
            break;
        case 4:
			EdtKEIJKBN->Text = "2";
            break;
        //2002/12/28 E.Takase
        case 5:
			EdtKEIJKBN->Text = "3";
            break;
        default:
			EdtKEIJKBN->Text = "0";
            break;
    }


    switch(CmbIndx)
    {
        case 13: //リード線長さ
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "0";
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            Edt2->Text = FormatFloat("#0.000",KM02.LD_LNG_MAX);
            Edt2->Text = FormatFloat("#0.000",KM02.LD_LNG_MIN);
            break;

        case 10: //ブラシ幅
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "1";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text = FormatFloat("#0.000",KM02.BURASI_MIN);
            Edt3->Text = FormatFloat("#0.000",KM02.BURASI_MAX);
            break;

        case 7: //リード線取付抵抗
            Cmb5->Items->Add( "mV/A" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "3";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",0);
            Edt3->Text =  FormatFloat("#0.0",KM02.LD_TR_DENA);
            Cmb3->ItemIndex = 2;
            Edt2->Enabled = false;
            EdtJYOKEN1->Text = FloatToStr(KM02.LD_TR_DENR);		//リード線取付測定電流
            EdtJYOKEN2->Text = IntToStr(KM02.LD_TR_TIME);		//　〃　　取付測定時間
            EdtJYOKEN3->Text = KM02.LD_TR_TYPE;					//　〃　　取付測定タイプ

            break;

        case 8: //リード線引張強度
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "4";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.LD_HP_KYO);
            Edt3->Text =  FormatFloat("#0.0",0);
            Cmb3->ItemIndex = 1;
            Edt3->Enabled = false;
            EdtJYOKEN1->Text = IntToStr(KM02.LD_HP_SPD);	//リード線引張測定速度

            break;

        case 0: //母体比重
            Cmb5->Items->Add( " " );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "5";
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            Edt2->Text =  FormatFloat("#0.00",KM02.BOTAI_MIN);
            Edt3->Text =  FormatFloat("#0.00",KM02.BOTAI_MAX);
            //if ( KM02.KEIJKBN == 4 ) Cmb4->ItemIndex = 1;
            break;

        case 1: //硬度 圧面
            Cmb5->Items->Add( "HsC" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "6";
            EdtJYOKEN1->Text = "1";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.HSC_A_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.HSC_A_MAX);
            break;

        case 2: //硬度 側面
            Cmb5->Items->Add( "HsC" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "2";
        	EdtKMK->Text = "6";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.HSC_S_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.HSC_S_MAX);
            break;

        case 3: //硬度 圧面
            Cmb5->Items->Add( "HsD" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "3";
        	EdtKMK->Text = "6";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.HSD_A_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.HSD_A_MAX);
            break;

        case 4: //硬度 側面
            Cmb5->Items->Add( "HsD" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "4";
        	EdtKMK->Text = "6";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.HSD_S_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.HSD_S_MAX);
            break;

        case 5: //固有抵抗
            Cmb5->Items->Add( "μΩ・cm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "7";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.KOYU_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.KOYU_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.KOYU_DEN);	//固有抵抗率 電流
            EdtJYOKEN2->Text = IntToStr(KM02.KOYU_PRO);		//固有抵抗率 プローブ
            break;

        case 6: //抗折力
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "8";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.MAGE_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.MAGE_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.MAGE_SPAN);	//抗折力
            break;

        case 18: //座屈
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "9";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.ZAKUT_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.ZAKUT_MAX);
            break;

        case 9:  //ブラシ厚さ
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",KM02.HIST_MIN);
            Edt3->Text =  FormatFloat("#0.000",KM02.HIST_MAX);
            break;

        case 11: //ブラシ長さ
        case 15: //リード線スポット厚さ
        case 16: //リード線スポット幅
        case 17: //リード線スポット長さ
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

        case 12: //摺動面R
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "10";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

        case 14:  //ターミナル溶接強度
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->ItemIndex = 0;
            Cmb3->ItemIndex = 1; //下限規格
        	EdtKMK->Text = "11";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",0);
            Edt3->Text =  FormatFloat("#0.0",0);
            Edt3->Enabled = false;
            break;

        case 19: //曲げ強さ（現物）
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            //2003/07/22 E.Takase 単位追加
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "12";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.MAGEG_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.MAGEG_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.MAGEG_SPAN);	//抗折力
            break;

        default:
            Cmb5->Items->Add( "mm" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "度" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

    }



}

//既定の規格値を検索
int __fastcall TForm1::DTKSHIN_Serch()
{
	AnsiString sBuf;

	KM02.DTKSCOD		 = " ";		//	得意先コード
	KM02.DTKSHIN		 = " ";		//	得意先品番
	KM02.HINBAN			 = " ";		//	自社品番
	KM02.ZISCOD			 = " ";		//	材質コード
	KM02.ZISNAM			 = " ";		//	材質名
	KM02.SYOSCOD		 = " ";		//	焼成コード
	KM02.SORTKEY		 = 0;	    //	ソートキー
	KM02.KEIJKBN		 = 0;		//	形状区分
	KM02.SK_LD_LNG		 = 0;		//	測定区分　線長さ
	KM02.SK_BURASI		 = 0;		//	　〃　　　ブラシ幅
	KM02.SK_BURASIT		 = 0;		//	　〃　　　ブラシ幅縦押し
	KM02.SK_LD_TR		 = 0;		//	　〃　　　線取付抵抗
	KM02.SK_LD_HP		 = 0;		//	　〃　　　線引張強度
	KM02.SK_BOTAI		 = 0;		//	　〃　　　母体比重
	KM02.SK_KOYU		 = 0;		//	　〃　　　固有抵抗
	KM02.SK_MAGE		 = 0;		//	　〃　　　抗折力
	KM02.SK_HSC_A		 = 0;		//	　〃　　　HsC硬度（圧面）
	KM02.SK_HSC_S		 = 0; 		//	　〃　　　HsC硬度（側面）
	KM02.SK_HSD_A		 = 0;		//	　〃　　　HsD硬度（圧面）
	KM02.SK_HSD_S		 = 0;		//	　〃　　　HsD硬度（側面）
	KM02.SK_ZAKUT		 = 0;		//	　〃　　　座屈
	KM02.HIST_SOKUT		 = 0;		//	ヒストグラム測定数
	KM02.HIST_KIKAK		 = 0;		//	　〃　　　　　規格
	KM02.HIST_MIN		 = 0;		//	　〃　　　　　下限規格
	KM02.HIST_MAX		 = 0;		//	　〃　　　　　上限規格
	KM02.LD_LNG_MIN		 = 0;		//	リード線長さ　上限
	KM02.LD_LNG_MAX		 = 0;		//	　〃　　　　　下限
	KM02.BURASI_MIN		 = 0;		//	ブラシ幅　上限
	KM02.BURASI_MAX		 = 0;		//	　〃　　　下限
	KM02.BURASIT_MIN	 = 0;		//	ブラシ幅縦押し上限
	KM02.BURASIT_MAX	 = 0;		//	　〃　　　　　下限
	KM02.LD_TR_DENA		 = 0;		//	リード線取付測定電圧
	KM02.LD_TR_DENR		 = 0;		//	リード線取付測定電流
	KM02.LD_TR_TIME		 = 0;		//	　〃　　取付測定時間
	KM02.LD_TR_TYPE		 = " ";		//	　〃　　取付測定タイプ
    KM02.LD_HP_SPD		 = 0;		//	リード線引張測定速度
	KM02.LD_HP_KYO		 = 0;		//	　〃　　引張強度
	KM02.LD_HP_TAN		 = 0;		//	　〃　　引張強度単位
	KM02.BOTAI_MIN		 = 0;		//	母体比重　下限
	KM02.BOTAI_MAX		 = 0;		//	　〃　　　上限
	KM02.KOYU_MIN		 = 0;		//	固有抵抗率　下限
	KM02.KOYU_MAX		 = 0;		//	　〃　　　　上限
	KM02.KOYU_DEN		 = 0;		//	　〃　　　　電流
	KM02.KOYU_PRO		 = 0;		//	　〃　　　　プローブ
	KM02.MAGE_MIN		 = 0;		//	曲げ強度　下限
	KM02.MAGE_MAX		 = 0;		//	　〃　　　上限
	KM02.MAGE_TAN		 = 0;		//	　〃　　　単位
	KM02.MAGE_SPAN		 = 0;		//	　〃　　　スパン
	KM02.HSC_A_MIN		 = 0;		//	ＨｓＣ硬度（圧面）下限
	KM02.HSC_A_MAX		 = 0;		//	　〃　　　　　　　上限
	KM02.HSC_S_MIN		 = 0;		//	　〃　　　（側面）下限
	KM02.HSC_S_MAX		 = 0;		//	　〃　　　　　　　上限
	KM02.HSD_A_MIN		 = 0;		//	ＨｓＤ硬度（圧面）下限
	KM02.HSD_A_MAX		 = 0;		//	　〃　　　　　　　上限
	KM02.HSD_S_MIN		 = 0;		//	　〃　　　（側面）下限
	KM02.HSD_S_MAX		 = 0;		//	　〃　　　　　　　上限
	KM02.ZAKUT_MIN		 = 0;		//	座屈　下限
	KM02.ZAKUT_MAX		 = 0;		//	　〃　上限
	KM02.MAGEG_MIN		 = 0;		//	曲げ強度（現物）　下限    //2002/12/28 E.Takase Add
	KM02.MAGEG_MAX		 = 0;		//	　〃　　　        上限    //2002/12/28 E.Takase Add
	KM02.MAGEG_TAN		 = 0;		//	　〃　　　        単位    //2002/12/28 E.Takase Add
	KM02.MAGEG_SPAN		 = 0;		//	　〃　　　        スパン  //2002/12/28 E.Takase Add

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// 問合せ実行

	sBuf = "SELECT * FROM KM02 WHERE  DTKSHIN = '";
	sBuf +=  EdtHIN->Text  + "'";
    //2002/11/22 REVCNT = 0 条件追加 E.Takase
	sBuf += " AND REVCNT = 0 ";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof == true ) {
		//検索結果 ０件
		// ステータスメッセージ
		return(0);

	}

	Query1->First();
    //sBuf = Query1->FieldValues["DTKSCOD"];
    if ( !(VarIsNull (Query1->FieldValues["DTKSCOD"] )) )
		KM02.DTKSCOD = Query1->FieldValues["DTKSCOD"];				//	得意先コード

    if ( !(VarIsNull (Query1->FieldValues["DTKSHIN"])))
		KM02.DTKSHIN = Query1->FieldValues["DTKSHIN"];				//	得意先品番

    if ( !(VarIsNull (Query1->FieldValues["HINBAN"])))
		KM02.HINBAN = Query1->FieldValues["HINBAN"];				//	自社品番

    sBuf = Query1->FieldValues["ZISCOD"];
    if ( !(VarIsNull (Query1->FieldValues["ZISCOD"])))
		KM02.ZISCOD = Query1->FieldValues["ZISCOD"];				//	材質コード

    if ( !(VarIsNull (Query1->FieldValues["ZISNAM"])))
		KM02.ZISNAM = Query1->FieldValues["ZISNAM"];				//	材質名

    if ( !(VarIsNull (Query1->FieldValues["SYOSCOD"])))
		KM02.SYOSCOD = Query1->FieldValues["SYOSCOD"];				//	焼成コード

    if ( !(VarIsNull (Query1->FieldValues["SORTKEY"])))
		KM02.SORTKEY = Query1->FieldValues["SORTKEY"];	      		//	ソートキー

    if ( !(VarIsNull (Query1->FieldValues["KEIJKBN"])))
		KM02.KEIJKBN = Query1->FieldValues["KEIJKBN"];				//	形状区分

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_LNG"])))
		KM02.SK_LD_LNG = Query1->FieldValues["SK_LD_LNG"];			//	測定区分　線長さ

    if ( !(VarIsNull (Query1->FieldValues["SK_BURASI"])))
		KM02.SK_BURASI = Query1->FieldValues["SK_BURASI"];			//	　〃　　　ブラシ幅

    if ( !(VarIsNull (Query1->FieldValues["SK_BURASIT"])))
		KM02.SK_BURASIT = Query1->FieldValues["SK_BURASIT"];		//	　〃　　　ブラシ幅縦押し

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_TR"])))
		KM02.SK_LD_TR = Query1->FieldValues["SK_LD_TR"];			//	　〃　　　線取付抵抗

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_HP"])))
		KM02.SK_LD_HP = Query1->FieldValues["SK_LD_HP"];			//	　〃　　　線引張強度

    if ( !(VarIsNull (Query1->FieldValues["SK_BOTAI"])))
		KM02.SK_BOTAI = Query1->FieldValues["SK_BOTAI"];			//	　〃　　　母体比重

    if ( !(VarIsNull (Query1->FieldValues["SK_KOYU"])))
		KM02.SK_KOYU = Query1->FieldValues["SK_KOYU"];				//	　〃　　　固有抵抗

    if ( !(VarIsNull (Query1->FieldValues["SK_MAGE"])))
		KM02.SK_MAGE = Query1->FieldValues["SK_MAGE"];				//	　〃　　　抗折力

    if ( !(VarIsNull (Query1->FieldValues["SK_HSC_A"])))
		KM02.SK_HSC_A = Query1->FieldValues["SK_HSC_A"];			//	　〃　　　HsC硬度（圧面）

    if ( !(VarIsNull (Query1->FieldValues["SK_HSC_S"])))
		KM02.SK_HSC_S = Query1->FieldValues["SK_HSC_S"];		   	//	　〃　　　HsC硬度（側面）

    if ( !(VarIsNull (Query1->FieldValues["SK_HSD_A"])))
		KM02.SK_HSD_A = Query1->FieldValues["SK_HSD_A"];			//	　〃　　　HsD硬度（圧面）

    if ( !(VarIsNull (Query1->FieldValues["SK_HSD_S"])))
		KM02.SK_HSD_S = Query1->FieldValues["SK_HSD_S"];			//	　〃　　　HsD硬度（側面）

    if ( !(VarIsNull (Query1->FieldValues["SK_ZAKUT"])))
		KM02.SK_ZAKUT = Query1->FieldValues["SK_ZAKUT"];			//	　〃　　　HsD硬度（側面）

    if ( !(VarIsNull (Query1->FieldValues["HIST_SOKUT"])))
		KM02.HIST_SOKUT = Query1->FieldValues["HIST_SOKUT"];		//	ヒストグラム測定数

    if ( !(VarIsNull (Query1->FieldValues["HIST_KIKAK"])))
		KM02.HIST_KIKAK = Query1->FieldValues["HIST_KIKAK"];	   	//	　〃　　　　　規格

    if ( !(VarIsNull (Query1->FieldValues["HIST_MIN"])))
		KM02.HIST_MIN = Query1->FieldValues["HIST_MIN"];			//	　〃　　　　　下限規格

    if ( !(VarIsNull (Query1->FieldValues["HIST_MAX"])))
		KM02.HIST_MAX = Query1->FieldValues["HIST_MAX"];			//	　〃　　　　　上限規格

    if ( !(VarIsNull (Query1->FieldValues["LD_LNG_MIN"])))
		KM02.LD_LNG_MIN = Query1->FieldValues["LD_LNG_MIN"];		//	リード線長さ　上限

    if ( !(VarIsNull (Query1->FieldValues["LD_LNG_MAX"])))
		KM02.LD_LNG_MAX = Query1->FieldValues["LD_LNG_MAX"];		//	　〃　　　　　下限

    if ( !(VarIsNull (Query1->FieldValues["BURASI_MIN"])))
		KM02.BURASI_MIN = Query1->FieldValues["BURASI_MIN"];		//	ブラシ幅　上限

    if ( !(VarIsNull (Query1->FieldValues["BURASI_MAX"])))
		KM02.BURASI_MAX = Query1->FieldValues["BURASI_MAX"];		//	　〃　　　下限

    if ( !(VarIsNull (Query1->FieldValues["BURASIT_MIN"])))
		KM02.BURASIT_MIN = Query1->FieldValues["BURASIT_MIN"];		//	ブラシ幅縦押し上限

    if ( !(VarIsNull (Query1->FieldValues["BURASIT_MAX"])))
		KM02.BURASIT_MAX = Query1->FieldValues["BURASIT_MAX"];		//	　〃　　　　　下限

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_DENA"])))
		KM02.LD_TR_DENA = Query1->FieldValues["LD_TR_DENA"];		//	リード線取付測定電圧

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_DENR"])))
		KM02.LD_TR_DENR = Query1->FieldValues["LD_TR_DENR"];		//	　〃　　取付測定電流

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_TYPE"])))
		KM02.LD_TR_TYPE = Query1->FieldValues["LD_TR_TYPE"];		//	　〃　　取付測定タイプ

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_TIME"])))
		KM02.LD_TR_TIME = Query1->FieldValues["LD_TR_TIME"];		//	　〃　　取付測定時間

	if ( !(VarIsNull (Query1->FieldValues["LD_HP_SPD"])))
		KM02.LD_HP_SPD = Query1->FieldValues["LD_HP_SPD"];			//	リード線引張測定速度

    if ( !(VarIsNull (Query1->FieldValues["LD_HP_KYO"])))
		KM02.LD_HP_KYO = Query1->FieldValues["LD_HP_KYO"];			//	　〃　　引張強度

    if ( !(VarIsNull (Query1->FieldValues["LD_HP_TAN"])))
		KM02.LD_HP_TAN = Query1->FieldValues["LD_HP_TAN"];			//	　〃　　引張強度単位

    if ( !(VarIsNull (Query1->FieldValues["BOTAI_MIN"])))
		KM02.BOTAI_MIN = Query1->FieldValues["BOTAI_MIN"];			//	母体比重　下限

    if ( !(VarIsNull (Query1->FieldValues["BOTAI_MAX"])))
		KM02.BOTAI_MAX = Query1->FieldValues["BOTAI_MAX"];			//	　〃　　　上限

    if ( !(VarIsNull (Query1->FieldValues["KOYU_MIN"])))
		KM02.KOYU_MIN = Query1->FieldValues["KOYU_MIN"];		   	//	固有抵抗率　下限

    if ( !(VarIsNull (Query1->FieldValues["KOYU_MAX"])))
		KM02.KOYU_MAX = Query1->FieldValues["KOYU_MAX"];			//	　〃　　　　上限

    if ( !(VarIsNull (Query1->FieldValues["KOYU_DEN"])))
		KM02.KOYU_DEN = Query1->FieldValues["KOYU_DEN"];			//	　〃　　　　電流

    if ( !(VarIsNull (Query1->FieldValues["KOYU_PRO"])))
		KM02.KOYU_PRO = Query1->FieldValues["KOYU_PRO"];			//	　〃　　　　プローブ

    if ( !(VarIsNull (Query1->FieldValues["MAGE_MIN"])))
		KM02.MAGE_MIN = Query1->FieldValues["MAGE_MIN"];		   	//	曲げ強度　下限

    if ( !(VarIsNull (Query1->FieldValues["MAGE_MAX"])))
		KM02.MAGE_MAX = Query1->FieldValues["MAGE_MAX"];			//	　〃　　　上限

    if ( !(VarIsNull (Query1->FieldValues["MAGE_TAN"])))
		KM02.MAGE_TAN = Query1->FieldValues["MAGE_TAN"];			//	　〃　　　単位

    if ( !(VarIsNull (Query1->FieldValues["MAGE_SPAN"])))
		KM02.MAGE_SPAN = Query1->FieldValues["MAGE_SPAN"];			//	　〃　　　スパン

    if ( !(VarIsNull (Query1->FieldValues["HSC_A_MIN"])))
		KM02.HSC_A_MIN = Query1->FieldValues["HSC_A_MIN"];			//	ＨｓＣ硬度（圧面）下限

    if ( !(VarIsNull (Query1->FieldValues["HSC_A_MAX"])))
		KM02.HSC_A_MAX = Query1->FieldValues["HSC_A_MAX"];			//	　〃　　　　　　　上限

    if ( !(VarIsNull (Query1->FieldValues["HSC_S_MIN"])))
		KM02.HSC_S_MIN = Query1->FieldValues["HSC_S_MIN"];			//	　〃　　　（側面）下限

    if ( !(VarIsNull (Query1->FieldValues["HSC_S_MAX"])))
		KM02.HSC_S_MAX = Query1->FieldValues["HSC_S_MAX"];			//	　〃　　　　　　　上限

    if ( !(VarIsNull (Query1->FieldValues["HSD_A_MIN"])))
		KM02.HSD_A_MIN = Query1->FieldValues["HSD_A_MIN"];			//	ＨｓＤ硬度（圧面）下限

    if ( !(VarIsNull (Query1->FieldValues["HSD_A_MAX"])))
		KM02.HSD_A_MAX = Query1->FieldValues["HSD_A_MAX"];			//	　〃　　　　　　　上限

    if ( !(VarIsNull (Query1->FieldValues["HSD_S_MIN"])))
		KM02.HSD_S_MIN = Query1->FieldValues["HSD_S_MIN"];			//	　〃　　　（側面）下限

    if ( !(VarIsNull (Query1->FieldValues["HSD_S_MAX"])))
		KM02.HSD_S_MAX = Query1->FieldValues["HSD_S_MAX"];			//	　〃　　　　　　　上限

    if ( !(VarIsNull (Query1->FieldValues["ZAKUT_MIN"])))
		KM02.ZAKUT_MIN = Query1->FieldValues["ZAKUT_MIN"];			//	　〃　　　（側面）下限

    if ( !(VarIsNull (Query1->FieldValues["ZAKUT_MAX"])))
		KM02.ZAKUT_MAX = Query1->FieldValues["ZAKUT_MAX"];			//	　〃　　　　　　　上限

    //2002/12/28 E.Takase Add
    if ( !(VarIsNull (Query1->FieldValues["MAGEG_MIN"])))
		KM02.MAGEG_MIN = Query1->FieldValues["MAGEG_MIN"];		   	//	曲げ強度（現物）　下限

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_MAX"])))
		KM02.MAGEG_MAX = Query1->FieldValues["MAGEG_MAX"];			//	　〃　　　		  上限

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_TAN"])))
		KM02.MAGEG_TAN = Query1->FieldValues["MAGEG_TAN"];			//	　〃　　　		  単位

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_SPAN"])))
		KM02.MAGEG_SPAN = Query1->FieldValues["MAGEG_SPAN"];		//	　〃　　　		  スパン

	return(1);

}

