/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１４）                  *
*  file   name   : U_TKS14_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾘｰﾄﾞ線引張強度測定処理データアクセス関数            *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void KD41Format(void);
void SetTable41(void);
int  Kd42_Serch02( AnsiString , int , int, int );
void Kd42_Update01( int );
void Kd42_Update02( AnsiString , int, int, int );
void Kd42_Insert01( AnsiString , int ,int, int );
void SetTable43W(int);

/***********************************************************************
*  function name : int  Kd41_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線引張強度ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出 *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd41_Serch01(void)
{

    //リード線引張強度ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD41.KENSA_YMD, KD41.TOLEY_NO ";
    sBuf += "FROM KD41 ";
	sBuf += "WHERE KD41.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD41.KENSA_YMD desc, KD41.TOLEY_NO";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;

    int iRow = 0 ;
    sBuf = "NO.";
    Form2->SGr1->Cells[1][iRow] = sBuf;


    sBuf = "検査予定年月日";
    Form2->SGr1->Cells[1][iRow] = sBuf;

    sBuf = "ﾄﾚｰNO.";
    Form2->SGr1->Cells[2][iRow] = sBuf;

    iRow += 1;

    if ( Form1->Query1->RecordCount <= 0 ) {
      // ShowMessage( MSG_02 );
      return 0;
    }else {
      Form1->Query1->First();
      while( !Form1->Query1->Eof ) {

            // グリッドの最大行数が超えていないかチェックする
            if( iRow >= Form2->SGr1->RowCount ){
              Form2->SGr1->RowCount = iRow+1;
            }
            sBuf = iRow ;
            Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

            sBuf = Form1->Query1->Fields->Fields[0]->AsString;
            Form2->SGr1->Cells[1][iRow] = sBuf;

            sBuf = Form1->Query1->Fields->Fields[1]->AsString;
            Form2->SGr1->Cells[2][iRow] = sBuf;


            Form1->Query1->Next();

            iRow += 1;
      }
   }

   Form2->SGr1->RowCount = iRow;

   return 1 ;
 }


/***********************************************************************
*  function name : void Kd41_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : リード線引張強度ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD41        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd41_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

       // KD41Data構造体変数の初期化(「検索」ﾎﾞﾀﾝを押した場合)
       if( !Save_Click) KD41Format();

        //検査値のの取得
        strVal01 = DelSEPA(Form1->edtymd->Text);

        if( Save_Click ){
           n= Form1->edttlno->Value + 1;
           strVal02 = IntToStr(n);
        }else
           strVal02 = Form1->edttlno->Text;

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //問い合せ文実行
        //ソート昇順 ,検査予定日、トレーNo
	    sBuf = "SELECT *  ";
	    sBuf += "FROM KD41 ";
	    sBuf += "WHERE  KD41.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD41.TOLEY_NO = '" + strVal02 + "' ";
            sBuf += "AND KD41.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	    //2001.05.21 修正 sBuf += "ORDER BY KD41.KENSA_YMD, KD41.TOLEY_NO, KD41.SAMPLE_P";
	    sBuf += "ORDER BY KD41.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD41にデータがありません");
          return -1;
        }else {

          // 「保存」ﾎﾞﾀﾝを押して次のﾄﾚｰNOを検索する場合
          if( Save_Click )
          {
               // ﾄﾚｰNOの設定
               Form1->edttlno->Text = strVal02 ;

               // KD41Data構造体変数の初期化
                KD41Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable41();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD41Data[i].SOKUTE_KBN  && KD41Data[i].SAMPLE_P != -1 ) {
             if( KD41Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD41Data[i].DTKSHIN == KD41Data[j].DTKSHIN)
                        KD41Data[j].LINK = KD41Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 リード線長さ寸法測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
          if( KD41Data[i].SOKUTEI_NM > 2 && KD41Data[i].SOKUTE_KBN == 1 &&
              KD41Data[i].SOKUTEI_NM_CUR ) {
              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD41Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT ";
	        sBuf += "KD42.SOKUTEICHI, KD42.SOKUTEI_NO ";
	        sBuf += "FROM KD42 ";
	        sBuf += "WHERE  KD42.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD42.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD42.SAMPLE_P = '" + strVal03 + "' ";
            sBuf += "AND  KD42.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KD42.KENSA_YMD, KD42.TOLEY_NO, KD42.SAMPLE_P, KD42.SOKUTEI_NO";
	        sBuf += "ORDER BY KD42.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD42にデータがありません");
                    //return 0;
                    continue;
                 }else {
                       Form1->Query1->First();
                       while( !Form1->Query1->Eof ) {

                             if ( Form1->Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                                   n = 3;
                             }else {
                                   n =  Form1->Query1->FieldValues["SOKUTEI_NO"];
                             }

                             if ( Form1->Query1->FieldValues["SOKUTEICHI"].IsNull()) {
                                   KD41Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD41Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable41(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : KD41Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable41()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD41Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD41Data[iRec].KENSA_YMD = " ";
     }else {
          KD41Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD41Data[iRec].TOLEY_NO = 0;
     }else {
          KD41Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD41Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD41Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 &&KD41Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD41Data[iRec].DTKSCOD = " ";
     }else {
          KD41Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD41Data[iRec].DTKSHIN = " ";
     }else {
          KD41Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD41Data[iRec].LOTNO = " ";
     }else {
          KD41Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD41Data[iRec].HINBAN = " ";
     }else {
          KD41Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD41Data[iRec].ZISCOD = " ";
     }else {
          KD41Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD41Data[iRec].ZISNAM = " ";
     }else {
          KD41Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_MIN"].IsNull()) {
          KD41Data[iRec].LD_HP_MIN = 0.0;
     }else {
          KD41Data[iRec].LD_HP_MIN =  Form1->Query1->FieldValues["LD_HP_MIN"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_SPD"].IsNull()) {
          KD41Data[iRec].LD_HP_SPD = 0;
     }else {
          KD41Data[iRec].LD_HP_SPD =  Form1->Query1->FieldValues["LD_HP_SPD"];
     }

     if ( Form1->Query1->FieldValues["LD_HP_TAN"].IsNull()) {
          KD41Data[iRec].LD_HP_TAN = 0;
     }else {
          KD41Data[iRec].LD_HP_TAN =  Form1->Query1->FieldValues["LD_HP_TAN"];
     }

      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD41Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD41Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD41Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD41Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD41Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD41Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD41Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD41Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD41Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD41Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD41Data[iRec].ADDYMD = " ";
          KD41Data[iRec].SOKUTEI_NM_CUR = 0;
     }else {
          KD41Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD41Data[iRec].ADDYMD )){
             KD41Data[iRec].SOKUTEI_NM_CUR = 0 ;
          }else{
             KD41Data[iRec].SOKUTEI_NM_CUR = KD41Data[iRec].SOKUTEI_SU ;
          }
     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD41Data[iRec].ADDTIM = " ";
     }else {
          KD41Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD41Data[iRec].UPDYMD = " ";
     }else {
          KD41Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD41Data[iRec].UPDCHR = 0;
     }else {
          KD41Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD41Data[iRec].UPDCNT = 0;
     }else {
          KD41Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }
     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD41Data[iRec].MEMO =  " ";
     }else {
          KD41Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
 }

/***********************************************************************
*  function name : void KD41Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線引張強度データ構造体KD41Dataを初期化  KD41  *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD41Format(void)
{
   for( int i=0; i<30; i++){
      KD41Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD41Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD41Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD41Data[i].SOKUTE_KBN = 0;     //測定区分
      KD41Data[i].DTKSCOD = '\0';     //得意先コード
      KD41Data[i].DTKSHIN = '\0';     //得意先品番
      KD41Data[i].LOTNO = '\0';       //ロットNO
      KD41Data[i].HINBAN = '\0';      //自社品番
      KD41Data[i].ZISCOD = '\0';      //材質コード
      KD41Data[i].ZISNAM = '\0';      //材質名
      KD41Data[i].LD_HP_MIN = 0.0;    //リード線引張強度 規格下
      KD41Data[i].LD_HP_SPD = 0;      //リード線引張強度 計測速度
      KD41Data[i].LD_HP_TAN = 0;      //リード線引張強度 単位
      KD41Data[i].SOKUTEI_NM = 0;     //リード線引張強度測定個数
      KD41Data[i].SOKUTEI_SU = 0;     //リード線引張強度測定個数
      KD41Data[i].SOKUTE_AVE = 0.0;   //測定平均値
      memset(KD41Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //測定値
      KD41Data[i].ADDYMD = '\0';      //登録日
      KD41Data[i].ADDTIM = '\0';      //登録時間
      KD41Data[i].UPDYMD = '\0';      //変更日
      KD41Data[i].UPDTIM = '\0';      //変更時間
      KD41Data[i].UPDCHR = 0;         //更新者
      KD41Data[i].UPDCNT = 0;         //更新回数
      KD41Data[i].LINK = 0;
      KD41Data[i].SOKUTEI_NM_CUR = 0;
      KD41Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase
   }
}


/***********************************************************************
*  function name : void Kd41_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀをリード線引張強度ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD41  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd41_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){
               // 計測ﾃﾞｰﾀ1
             KD41Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;
    }else if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ2
             KD41Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD41Data[SamplePositionIdx-1].SOKUTEI_NM > 2){
                 n = pEdt4[SamplePositionIdx-1]->Value;
                 if( n >=3 && n<= KD41Data[SamplePositionIdx-1].SOKUTEI_NM )
                    KD41Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = pEdt3[SamplePositionIdx-1]->Value;
             }
    }

	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD41Data[i].SOKUTE_KBN == 1 && KD41Data[i].SAMPLE_P != -1 &&
			KD41Data[i].SOKUTEI_NM_CUR != 0 ){

		//担当者ｺｰﾄﾞ
		KD41Data[i].UPDCHR = USER_COD ;

		// 測定予定日
		//KD41Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

		// ﾄﾚｰNO
		//KD41Data[i].TOLEY_NO =  Form1->edttlno->Value ;

		//測定値平均値の算出
		double a = 0.0;
		for(j=0; j< KD41Data[i].SOKUTEI_NM_CUR; j++ )
			a += KD41Data[i].SOKUTEICHI[j] ;

		if( KD41Data[i].SOKUTEI_NM_CUR )
			KD41Data[i].SOKUTE_AVE = a/KD41Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD41Data[i].ADDYMD )){
				KD41Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD41Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD41Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD41Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD41Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD41Data[i].UPDCNT += 1;

				iToroku = 0;
			}


			str_c[0] = NULL ;

			//Initial Query1
			Form1->Query1->Close();
			Form1->Query1->SQL->Clear();
			if(Form1->Database1->InTransaction == false ){
				Form1->Database1->StartTransaction();
			}

			//お問い合せ文  Update
			sprintf(str_c, " update KD41 set SOKUTEI_SU=%d , SOKUTEI_1=%6.1f , SOKUTEI_2=%6.1f, SOKUTE_AVE=%9.4f,",
								KD41Data[i].SOKUTEI_NM_CUR,
								KD41Data[i].SOKUTEICHI[0],
								KD41Data[i].SOKUTEICHI[1],
								KD41Data[i].SOKUTE_AVE);


			str = str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD41Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD41Data[i].ADDYMD.c_str(),
									KD41Data[i].ADDTIM.c_str(),
									KD41Data[i].UPDCHR,
									KD41Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD41Data[i].UPDYMD.c_str(),
									KD41Data[i].UPDTIM.c_str(),
									KD41Data[i].UPDCHR,
									KD41Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD41Data[i].KENSA_YMD.c_str(),
			//					KD41Data[i].TOLEY_NO ,
			//					KD41Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD41Data[i].KENSA_YMD.c_str(),
						KD41Data[i].TOLEY_NO ,
						KD41Data[i].SAMPLE_P ,
						iKojoKbn );

			str += str_c ;
			Form1->Query1->SQL->Add(str);

			//お問い合せ文の実行
			try
			{
				Form1->Query1->ExecSQL();
				Form1->Database1->Commit();    // 成功した場合、変更をコミットする
			}
			catch(EDatabaseError& e)
			{
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}
			catch(Exception& e)
			{
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			//リード線引張強度測定（例外）ﾌｧｲﾙの更新
			if( KD41Data[i].SOKUTEI_NM > 2 ){
				Kd42_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD41Data[i].ADDYMD )) || !(IsNullSpace(KD41Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD41Data[i].ADDYMD )){
					KD41Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD41Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD41Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD41Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD41Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD41Data[i].UPDCNT += 1;

					iToroku = 0;
				}


				str_c[0] = NULL ;
				//Initial Query1
				Form1->Query1->Close();
				Form1->Query1->SQL->Clear();
				if(Form1->Database1->InTransaction == false ){
					Form1->Database1->StartTransaction();
				}
				//お問い合せ文  Update
				sprintf(str_c, " update KD41 set MEMO='%s' , ", KD41Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD41Data[i].ADDYMD.c_str(),
										KD41Data[i].ADDTIM.c_str(),
										KD41Data[i].UPDCHR,
										KD41Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD41Data[i].UPDYMD.c_str(),
										KD41Data[i].UPDTIM.c_str(),
										KD41Data[i].UPDCHR,
										KD41Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD41Data[i].KENSA_YMD.c_str(),
				//					KD41Data[i].TOLEY_NO ,
				//					KD41Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD41Data[i].KENSA_YMD.c_str(),
						KD41Data[i].TOLEY_NO ,
						KD41Data[i].SAMPLE_P ,
						iKojoKbn );

				str += str_c ;
				Form1->Query1->SQL->Add(str);

				//お問い合せ文の実行
				try
				{
					Form1->Query1->ExecSQL();
					Form1->Database1->Commit();    // 成功した場合、変更をコミットする
				}
				catch(EDatabaseError& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
				catch(Exception& e)
				{
					// ShowMessage(e.Message);
					Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
					StatBarClear( e.Message )  ;
					Update_err = 1;
				}
			}
		}
	}
}


/***********************************************************************
*  function name : void Kd42_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀをリード線引張強度(例外）ﾌｧｲﾙへ書き込む KD42*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD41Data[iRec].SOKUTEI_NM; i++ ){

         // KD42へ追加するレコード存在するかどうかのチェック
         iRtn = Kd42_Serch02( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn <= 0 ) {
                Kd42_Insert01( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）
                Kd42_Update02( KD41Data[iRec].KENSA_YMD,
                          KD41Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;
          }
    }
}

/***********************************************************************
*  function name : int IsNullSpace( AnsiString str)                   *
*                  +--------------------------------------+            *
*          引  数  | str       |  チェックする文字列      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  0      |  NULL or Space             |            *
*                  |  １     |  NULL or Space以外の文字   |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 文字列中でNULL、Space以外の文字が入っているかどうか *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int IsNullSpace( AnsiString  str )
{
   char sBuf[256];
   int i, iRtn;

   iRtn = 1;

   sBuf[0] = NULL ;
   strcpy( sBuf,str.c_str());

   for( i=0; i<str.Length(); i++ ){
      if( sBuf[i] != NULL && sBuf[i] != ' ' ){
         iRtn = 0 ;
         break ;
       }
   }

   return iRtn;

}

/***********************************************************************
*  function name : int Kd42_Serch02(AnsiString sYmd, int iTlno,        *
*                                   int iSp, int iDtNo)                *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  0      |  レコード無し              |            *
*                  |  ＞０   |  レコード数                |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : 指定したﾚｺｰﾄﾞをﾘｰﾄﾞ線引張強度例外ﾌｧｲﾙにあるかどうか *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd42_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;
       AnsiString strVal04;

        //検査値のの取得
        strVal01 = sYmd;
        strVal02 = IntToStr(iTlno);
        strVal03 = IntToStr( iSp );
        strVal04 = IntToStr( iDtNo );

        Form1->Query1->Close();
        Form1->Query1->SQL->Clear();

        //問い合せ文実行
        //ソート昇順 、検査予定日、トレーNo、サンプルポジション,ﾃﾞｰﾀNO
        sBuf = "SELECT * ";
        sBuf += "FROM KD42 ";
        sBuf += "WHERE  KD42.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD42.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD42.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD42.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD42.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD42.KENSA_YMD, KD42.TOLEY_NO, KD42.SAMPLE_P, KD42.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof )
          return 0 ;

    return  1  ;
}


/***********************************************************************
*  function name : void Kd42_Update02(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD42へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
     }
    //お問い合せ文  Update
    sprintf(str_c, " update KD42 set SOKUTEICHI=%.1f", KD41Data[iSp-1].SOKUTEICHI[iDtNo-1]);

    str = str_c ;
    str_c[0] = NULL ;

     wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND SOKUTEI_NO=%d AND KOJOKBN =%d ",
                                sYmd.c_str(), iTlno, iSp, iDtNo, iKojoKbn );     // 20160630_工場区分追加

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //お問い合せ文の実行
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // 成功した場合、変更をコミットする
     }
     catch(EDatabaseError& e)
     {
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
 }

/***********************************************************************
*  function name : void Kd42_Insert01(AnsiString sYmd, int iTlno,      *
*                                    int iSp, int iDtNo)               *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iSp        |  ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ       |            *
*                  | iDtNo      |  計測ﾃﾞｰﾀNO             |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD42へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd42_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //お問い合せ文  Update
    sprintf(str_c, " insert into  KD42(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEICHI, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%.1f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo , KD41Data[iSp-1].SOKUTEICHI[iDtNo-1] , iKojoKbn);      // 20160630_工場区分追加

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //お問い合せ文の実行
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // 成功した場合、変更をコミットする
     }
     catch(EDatabaseError& e)
     {
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
 }


/***********************************************************************
*  function name : void Kd43W_Create01(AnsiString sYmd, int iTlno,     *
*                                                       int iNum)      *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iNum       |  ロット数               |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |             | レコード数             |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 履歴作画のために KD43Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd43W_Create01(AnsiString sYmd, int iTlno, int iNum)
{
     //検査予定年月日
     Form1->StoredProc1->Params->Items[0]->AsString = sYmd;

     //ﾄﾚｰNO
     Form1->StoredProc1->Params->Items[1]->AsInteger = iTlno;

     //ロット数
     Form1->StoredProc1->Params->Items[2]->AsInteger = iNum;

     //プログラム実行
     Form1->StoredProc1->Prepare();
     Form1->StoredProc1->ExecProc();

     //レコード数
     long n  = Form1->StoredProc1->Params->Items[3]->AsInteger;

     return n;
}

/***********************************************************************
*  function name : void KD43WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : リード線引張強度履歴ﾜｰｸﾃﾞｰﾀ構造体KD43dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD43WFormat(void)
{
   for( int i=0; i<30; i++){
       KD43WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD43WData[i].LOTNO[j]  = " " ;       //ロットNO
            KD43WData[i].LD_HP_MIN[j] = 0.0  ;  //リード線引張強度 規格下
            KD43WData[i].SOKUTE_AVE[j] = 0.0;
            KD43WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD43WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD43WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd43W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD43Wﾜｰｸﾃｰﾌﾞﾙからリード線引張強度履歴データ抽出KD43W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd43W_Serch01( void)
{
       int i;
       AnsiString strVal01;

        // KD41Data構造体変数の初期化
        KD43WFormat();

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD41Data[i].SOKUTE_KBN == 0 && KD41Data[i].SAMPLE_P == -1 ) continue ;
             if( KD41Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番で検索
             strVal01 = KD41Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD43W ";
	      sBuf += "WHERE  KD43W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD43W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
              sBuf += "ORDER BY ROWNO desc" ;


              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();


              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD21にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable43W(i);
                        Form1->Query1->Next();

                     }

                     //
                    KD43WData[i].LOTCNT +=1  ;
               }


            for( int j=0; j < KD43WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD43WData[i].SOKUTEI_NM[j]; k++)
                dAve += KD43WData[i].SOKUTEI[j][k] ;

               if( KD43WData[i].SOKUTEI_NM[j] !=0 )
                  KD43WData[i].SOKUTE_AVE[j] = dAve/KD43WData[i].SOKUTEI_NM[j] ;
           }


       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable43W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD43WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable43W(int iSp)
{

     int iLotno = KD43WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD43WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD43WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD43WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }

            if ( Form1->Query1->FieldValues["LD_HP_MIN"].IsNull()) {
               KD43WData[iSp].LD_HP_MIN[iLotno] = 0.0;
            }else {
                KD43WData[iSp].LD_HP_MIN[iLotno] = Form1->Query1->FieldValues["LD_HP_MIN"];
            }

     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD43WData[iSp].DTKSHIN = " ";
     }else {
            KD43WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD43WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD43WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD43WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD43WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD43WData[iSp].LOTCNT = iLotno ;

 }

/***********************************************************************
*  function name : void CopyKD41Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD41DataをKD41Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD41Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD41Data[i].SOKUTE_KBN == 0 || KD41Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD41Data[i].LINK == 0 ){
            iLinkSp = KD41Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD41Data[i].LINK;
        }

        if( KD43WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD43WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD43WData[iLinkSp-1].DTKSHIN =  KD41Data[i].DTKSHIN;

           //ロットNO
           KD43WData[iLinkSp-1].LOTNO[0]  = KD41Data[i].LOTNO ;

           // 規格下
           KD43WData[iLinkSp-1].LD_HP_MIN[0] = KD41Data[i].LD_HP_MIN;

           KD43WData[iLinkSp-1].SOKUTEI_NM[0] = KD41Data[i].SOKUTEI_NM_CUR;

           if( KD41Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD41Data[i].SOKUTEI_NM; k++ ) {
                  KD43WData[iLinkSp-1].SOKUTEI[0][k] = KD41Data[i].SOKUTEICHI[k];
                  a += KD43WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD41Data[i].SOKUTEI_NM != 0 )
             KD43WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD41Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD43WData[iLinkSp-1].LOTCNT += 1;

          n = KD43WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD43WData[iLinkSp-1].LOTNO[n-1]  = KD41Data[i].LOTNO ;

          //リード線長さ 規格下
          KD43WData[iLinkSp-1].LD_HP_MIN[n-1] = KD41Data[i].LD_HP_MIN;

          KD43WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD41Data[i].SOKUTEI_NM_CUR;

          if( KD41Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD41Data[i].SOKUTEI_NM; k++ ) {
               KD43WData[iLinkSp-1].SOKUTEI[n-1][k] = KD41Data[i].SOKUTEICHI[k];
               a += KD43WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD43WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD41Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd43w(void)                                 *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測したｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOのﾃﾞｰﾀを履歴ﾃﾞｰﾀへ追加        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  AddKd43W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD41Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD41Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD43WData[iLinkSp-1].LOTNO[iRtn] = KD41Data[SamplePositionIdx-1].LOTNO;

   //リード線長さ 規格下
    KD43WData[iLinkSp-1].LD_HP_MIN[iRtn]= KD41Data[SamplePositionIdx-1].LD_HP_MIN;

    KD43WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KD43WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD43WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD41Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD41Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD41Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD43WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}



/***********************************************************************
*  function name : void Kd43W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd43Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd43W_Delete01(void)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    if(Form1->Database1->InTransaction == false ){
       Form1->Database1->StartTransaction();
    }

    //お問い合せ文  Update
    sprintf(str_c, " DELETE FROM KD43W");

    str = str_c ;
    str_c[0] = NULL ;

     str += str_c ;
     Form1->Query1->SQL->Add(str);

     //お問い合せ文の実行
     try
     {
         Form1->Query1->ExecSQL();
         Form1->Database1->Commit();    // 成功した場合、変更をコミットする
     }
     catch(EDatabaseError& e)
     {
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
     catch(Exception& e)
     {
       // ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       StatBarClear( e.Message )  ;
       Update_err = 1;
     }
 }
