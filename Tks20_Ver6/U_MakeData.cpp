/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_MakeData.cpp                                      *
*  create        : 1999.10.18                                          *
*  update        :                                                     *
*  contents      : 印刷データ作成プログラム                            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

/***********************************************************************
*  function name : void MakeData(void)                                 *
*                  +--------------------------------------+            *
*          引  数  | なし       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | なし       |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 印刷データを作成する                                *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
void MakeData(void)
{
    int i,j,n;
    double k;
    Master_rec = 3;//マスタ情報印刷行
    rec = 0;       //レコード数
    pass = 1;      //合格1、不合格0
    newpage = 1;   //改ページNo
    Last_DTKSCOD = "";
    AnsiString str;
    //空白文字の設定
    //strcpy(strBlank_c,"   ");

    KM01_04Serch01();        //検査指示マスタからマスタデータを抽出

    //ワークテーブルに印刷データを入力していく
    //ワークテーブル 初期化
    //Initial Query
    Form1->Q_TW_TKS21PR->Close();
    Form1->Q_TW_TKS21PR->SQL->Clear();
    str = "delete from TW_TKS21PR";
    Form1->Q_TW_TKS21PR->SQL->Add(str);

    //execute sql
    try
    {
        Form1->Q_TW_TKS21PR->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
        ShowMessage(e.Message);
    }
    catch(Exception& e)
    {
        ShowMessage(e.Message);
    }
    Form1->Q_TW_TKS21PR->Close();

    //ワークテーブル(検査員) 初期化
    //Initial Query
    Form1->Q_TW_UPDCHR->Close();
    Form1->Q_TW_UPDCHR->SQL->Clear();
    str = "delete from TW_UPDCHR";
    Form1->Q_TW_UPDCHR->SQL->Add(str);

    //execute sql
    try
    {
        Form1->Q_TW_UPDCHR->ExecSQL();
    }
    catch(EDatabaseError& e)
    {
        ShowMessage(e.Message);
    }
    catch(Exception& e)
    {
        ShowMessage(e.Message);
    }
    Form1->Q_TW_UPDCHR->Close();


    //if ( Form1->Q_KM01->RecordCount == 0 ) {
    if ( Form1->Q_KM01->Bof == true  && Form1->Q_KM01->Eof == true ) {
        ShowMessage("検索データありません");
        return;
    }
    Form1->Q_KM01->First();
    Last_DTKSCOD = Form1->Q_KM01->FieldValues["DTKSCOD"];
    i = 0;
    n = Form1->Q_KM01->RecordCount;
    k = 100 / ( n * 1.0 );
    while( !Form1->Q_KM01->Eof ) {

        Form1->ProgressBar1->Position = int(k * i);

		//文字配列の初期化
		//memset(KM01_04Data, (int)NULL, sizeof(struct structKM01_04));
        pass = 1;
        DataNo = 0;
        KD01Format01();
        KD11Format01();
        KD21Format01();
        KD31Format01();
        KD41Format01();
        KD51Format01();
        KD61Format01();
        KD71Format01();
        KD81Format01();
        KD91Format01();

        //2002.12.05 E.Takase コンミ用の処理追加
        KDC1Format01();
        KD71_LFormat01();
        KD71_RFormat01();


        /**********************/
        /*                    */
        /* 得意先品番から規格 */
        /*                    */
        /**********************/
        KM01_04Sub01();                 //カレントレコードの内容を変数に代入

        if ( Last_DTKSCOD != KM01_04Data.DTKSCOD )  {
            Last_DTKSCOD = KM01_04Data.DTKSCOD;
            newpage++;
        }


        /*************************/
        /*                       */
        /*   検査値の行を追加    */
        /*                       */
        /*************************/
        //検査値を入力する行を追加

        //検査値を更新していく
        KD01_02Serch01();               //リード線長さデータファイルからデータを抽出
        KD01Compare01();                //リード線長さデータが規格内かどうかを判断

        KD11_12Serch01();               //ブラシ幅寸法データファイルからデータを抽出
        KD11Compare01();                //ブラシ幅寸法データが規格内かどうかを判断

        KD21_22Serch01();               //ブラシ幅寸法縦押しデータファイルからデータを抽出
        KD21Compare01();                //ブラシ幅寸法縦押しデータが規格内かどうかを判断

        //コンミ印刷の場合は実行しない
        if ( Flagcnd == 0 || Flagcnd == 1 ) {
           KD31_32Serch01();               //リード線取付抵抗データファイルからデータを抽出
           KD31Compare01();                //リード線取付抵抗データが規格内かどうかを判断

           KD41_42Serch01();               //リード線引張強度データファイルからデータを抽出
           KD41Compare01();                //リード線引張強度データが規格内かどうかを判断
        }

        KD51_52Serch01();               //母体比重データファイルからデータを抽出
        KD51Compare01();                //母体比重データが規格内かどうかを判断

        KD61_62Serch01();               //Ｈｓ硬度データファイルからデータを抽出
        KD61Compare01();                //Ｈｓ硬度データが規格内かどうかを判断

        KD71_72Serch01();               //固有抵抗率データファイルからデータを抽出
        KD71Compare01();                //固有抵抗率データが規格内かどうかを判断

        KD81_82Serch01();               //抗折力データファイルからデータを抽出
        KD81Compare01();                //抗折力データが規格内かどうかを判断

        KD91_92Serch01();               //座屈データファイルからデータを抽出
        KD91Compare01();                //座屈データが規格内かどうかを判断

        //コンミ印刷の場合は実行する
        if ( Flagcnd == 2 || Flagcnd == 3 ) {

           KD71_72_LSerch01();               //固有抵抗率左データファイルからデータを抽出
           KD71_LCompare01();                //固有抵抗率左データが規格内かどうかを判断
           KD71_72_RSerch01();               //固有抵抗率右データファイルからデータを抽出
           KD71_RCompare01();                //固有抵抗率右データが規格内かどうかを判断
           KDC1_C2Serch01();                 //現物曲げデータファイルからデータを抽出
           KDC1Compare01();                  //現物曲げデータが規格内かどうかを判断

        }

        PassSet();                      //合格か不合格か決定
        DataNoSet();                    //最大測定データ数決定

        //if ( pass == 1 ) {
        //    if ( KD61Data.PASS == 0 ) {
        //        pass = 0;
        //        PASS_FailUpdate01();    //不合格フラグをつける
        //    }
        //}

	switch(Flagcnd)
	{
		case 0:
            if ( DataNo != -1 ) {
                Master_rec = 2;

                //検査員文字列作成
                UPDCHR_Make01(i);

                UPDCHR_Serch01();               //更新者のグループ化

                DTKSHIN_CIYCLEInsert01();       //得意先品番から ｻｲｸﾙ時間までのデータをワークに追加

                KIKAKU_MINInsert01();           //検査項目の規格下のデータをワークに追加

                KIKAKU_MAXInsert01();           //検査項目の規格上のデータをワークに追加

                SOKUTEIInsert01();              //検査項目の測定値のデータをワークに追加
            }
			break;

		case 1:
            if ( DataNo != -1 ) {
                Master_rec = 1;

                KIKAKU_MINInsert01();           //検査項目の規格下のデータをワークに追加

                KIKAKU_MAXInsert01();           //検査項目の規格上のデータをワークに追加

                UPDCHR_Serch01();               //更新者のグループ化

                LOT_SOKUTEIInsert01();       //得意先品番から ｻｲｸﾙ時間までのデータをワークに追加


                SOKUTEIInsert01();              //検査項目の測定値のデータをワークに追加

                UPDCHRInsert01();               //検査員のデータをワークに追加
            }
			break;
		case 2:
            if ( DataNo != -1 ) {
                Master_rec = 2;

                //検査員文字列作成
                UPDCHR_2_Make01(i);

                UPDCHR_Serch01();               //更新者のグループ化

                DTKSHIN_CIYCLEInsert01();       //得意先品番から ｻｲｸﾙ時間までのデータをワークに追加

                KIKAKU_MINInsert02();           //検査項目の規格下のデータをワークに追加

                KIKAKU_MAXInsert01();           //検査項目の規格上のデータをワークに追加

                SOKUTEIInsert02();              //検査項目の測定値のデータをワークに追加
            }
			break;

		case 3:
            if ( DataNo != -1 ) {
                Master_rec = 1;

                KIKAKU_MINInsert02();           //検査項目の規格下のデータをワークに追加

                KIKAKU_MAXInsert01();           //検査項目の規格上のデータをワークに追加

                UPDCHR_Serch01();               //更新者のグループ化

                LOT_SOKUTEIInsert01();       //得意先品番から ｻｲｸﾙ時間までのデータをワークに追加


                SOKUTEIInsert02();              //検査項目の測定値のデータをワークに追加

                UPDCHRInsert01();               //検査員のデータをワークに追加
            }
			break;
	}


        Form1->Q_KM01->Next();  //次のレコードに移動
        i++;
    }


    if ( Flagcnd == 0 ) {
        if ( DataNo != -1 ) {
            //検査員文字列作成
            UPDCHR_Make01(-2);
        }
    }

}


