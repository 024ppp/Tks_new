/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１１）                  *
*  file   name   : U_TKS11_Data.cpp                                    *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法計測  処理データアクセス関数            *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void KD11Format(void);
void SetTable11(void);
int  Kd12_Serch02( AnsiString , int , int, int );
void Kd12_Update01( int );
void Kd12_Update02( AnsiString , int, int, int );
void Kd12_Insert01( AnsiString , int ,int, int );
void SetTable13W(int);

/***********************************************************************
*  function name : int  Kd11_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出     *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd11_Serch01(void)
{

    //ブラシ幅寸法ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD11.KENSA_YMD, KD11.TOLEY_NO ";
    sBuf += "FROM KD11 ";
	sBuf += "WHERE KD11.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD11.KENSA_YMD desc, KD11.TOLEY_NO";

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

    if ( Form1->Query1->Eof ) {
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
*  function name : void Kd11_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : ブラシ幅寸法ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD11            *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd11_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

        // KD11Data構造体変数の初期化(「検索」ﾎﾞﾀﾝを押した場合)
        if( !Save_Click) KD11Format();

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
	    sBuf += "FROM KD11 ";
	    sBuf += "WHERE  KD11.KENSA_YMD = '" + strVal01 + "' ";
	    sBuf += "AND  KD11.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND KD11.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加 
	    //2001.05.21 修正 sBuf += "ORDER BY KD11.KENSA_YMD, KD11.TOLEY_NO, KD11.SAMPLE_P";
	    sBuf += "ORDER BY KD11.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD11にデータがありません");
          return -1;
        }else {

           // 「保存」ﾎﾞﾀﾝを押して次のﾄﾚｰNOを検索する場合
           if( Save_Click ){
               // ﾄﾚｰNOの設定
               Form1->edttlno->Text = strVal02 ;

               // KD11Data構造体変数の初期化
               KD11Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable11();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD11Data[i].SOKUTE_KBN  && KD11Data[i].SAMPLE_P != -1 ) {
             if( KD11Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD11Data[i].DTKSHIN == KD11Data[j].DTKSHIN)
                        KD11Data[j].LINK = KD11Data[i].SAMPLE_P ;
                }
             }
          }
       }

       //計測数Ｎ＞２の場合 ブラシ幅寸法（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
          if( KD11Data[i].SOKUTEI_NM > 2 && KD11Data[i].SOKUTE_KBN == 1 &&
              KD11Data[i].SOKUTEI_NM_CUR  ) {

              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD11Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT ";
	        sBuf += "KD12.SOKUTEICHI, KD12.SOKUTEI_NO ";
	        sBuf += "FROM KD12 ";
	        sBuf += "WHERE  KD12.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD12.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD12.SAMPLE_P = '" + strVal03 + "' ";
            sBuf += "AND  KD12.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加 
	        //2001.05.21 修正 sBuf += "ORDER BY KD12.KENSA_YMD, KD12.TOLEY_NO, KD12.SAMPLE_P, KD12.SOKUTEI_NO";
	        sBuf += "ORDER BY KD12.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->RecordCount <= 0 ) {
                    //ShowMessage("KD12にデータがありません");
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
                                   KD11Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD11Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable11(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : ブラシ幅寸法ﾃﾞｰﾀを保存する構造体KD11Dataへﾃﾞｰﾀを設定*
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable11()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD11Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD11Data[iRec].KENSA_YMD = " ";
     }else {
          KD11Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD11Data[iRec].TOLEY_NO = 0;
     }else {
          KD11Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD11Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD11Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 &&KD11Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD11Data[iRec].DTKSCOD = " ";
     }else {
          KD11Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD11Data[iRec].DTKSHIN = " ";
     }else {
          KD11Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD11Data[iRec].LOTNO = " ";
     }else {
          KD11Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD11Data[iRec].HINBAN = " ";
     }else {
          KD11Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD11Data[iRec].ZISCOD = " ";
     }else {
          KD11Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD11Data[iRec].ZISNAM = " ";
     }else {
          KD11Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["BURASI_MIN"].IsNull()) {
          KD11Data[iRec].BURASI_MIN = 0.0;
     }else {
          KD11Data[iRec].BURASI_MIN =  Form1->Query1->FieldValues["BURASI_MIN"];
     }

     if ( Form1->Query1->FieldValues["BURASI_MAX"].IsNull()) {
          KD11Data[iRec].BURASI_MAX = 0.0;
     }else {
          KD11Data[iRec].BURASI_MAX =  Form1->Query1->FieldValues["BURASI_MAX"];
     }

      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD11Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD11Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD11Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD11Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD11Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD11Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }

    if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD11Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD11Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD11Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD11Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

     if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD11Data[iRec].ADDYMD = " ";
          KD11Data[iRec].SOKUTEI_NM_CUR = 0;
     }else {
          KD11Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD11Data[iRec].ADDYMD )){
             KD11Data[iRec].SOKUTEI_NM_CUR = 0 ;
          }else{
             KD11Data[iRec].SOKUTEI_NM_CUR = KD11Data[iRec].SOKUTEI_SU ;
          }

     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD11Data[iRec].ADDTIM = " ";
     }else {
          KD11Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD11Data[iRec].UPDYMD = " ";
     }else {
          KD11Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD11Data[iRec].UPDCHR = 0;
     }else {
          KD11Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD11Data[iRec].UPDCNT = 0;
     }else {
          KD11Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }
     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD11Data[iRec].MEMO =  " ";
     }else {
          KD11Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }
 }

/***********************************************************************
*  function name : void KD11Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : ブラシ幅寸法ﾃﾞｰﾀを保存する構造体KD11Dataを初期化KD11*
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD11Format(void)
{
   for( int i=0; i<30; i++){
      KD11Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD11Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD11Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD11Data[i].SOKUTE_KBN = 0;     //測定区分
      KD11Data[i].DTKSCOD = '\0';     //得意先コード
      KD11Data[i].DTKSHIN = '\0';     //得意先品番
      KD11Data[i].LOTNO = '\0';       //ロットNO
      KD11Data[i].HINBAN = '\0';      //自社品番
      KD11Data[i].ZISCOD = '\0';      //材質コード
      KD11Data[i].ZISNAM = '\0';      //材質名
      KD11Data[i].BURASI_MIN = 0.0;   //ブラシ幅寸法 規格下
      KD11Data[i].BURASI_MAX = 0.0;   //ブラシ幅寸法 規格上
      KD11Data[i].SOKUTEI_NM = 0;     //ブラシ幅寸法計測個数
      KD11Data[i].SOKUTEI_SU = 0;     //ブラシ幅寸法計測個数
      KD11Data[i].SOKUTE_AVE = 0.0;   //測定平均値
      memset(KD11Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //測定値
      KD11Data[i].ADDYMD = '\0';      //登録日
      KD11Data[i].ADDTIM = '\0';      //登録時間
      KD11Data[i].UPDYMD = '\0';      //変更日
      KD11Data[i].UPDTIM = '\0';      //変更時間
      KD11Data[i].UPDCHR = 0;         //更新者
      KD11Data[i].UPDCNT = 0;         //更新回数
      KD11Data[i].LINK = 0;
      KD11Data[i].SOKUTEI_NM_CUR = 0;
      KD11Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase
   }
}


/***********************************************************************
*  function name : void Kd11_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀをブラシ幅寸法計測ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD11  *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd11_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err = 0;

    // 画面の入力ﾃﾞｰﾀを取得
    // 計測ﾃﾞｰﾀ1
    if( DataNoIdx == 1 )
        KD11Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;

       // 計測ﾃﾞｰﾀ2
    else if ( DataNoIdx == 2 )
        KD11Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;

    // 計測ﾃﾞｰﾀ n?
    else {
        n = pEdt4[SamplePositionIdx-1]->Value;
        if( n >=3 && n<= KD11Data[SamplePositionIdx-1].SOKUTEI_NM )
            KD11Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = pEdt3[SamplePositionIdx-1]->Value;
    }

	for( i=0; i<30; i++ ){

		iToroku = 1;

		if( KD11Data[i].SOKUTE_KBN == 1 && KD11Data[i].SAMPLE_P != -1 &&
			KD11Data[i].SOKUTEI_NM_CUR != 0 ){

			//担当者ｺｰﾄﾞ
			KD11Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			// KD11Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			// KD11Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD11Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD11Data[i].SOKUTEICHI[j] ;

			if( KD11Data[i].SOKUTEI_NM_CUR )
				KD11Data[i].SOKUTE_AVE = a/KD11Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD11Data[i].ADDYMD )){
				KD11Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD11Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD11Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD11Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD11Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD11Data[i].UPDCNT += 1;

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
			sprintf(str_c, " update KD11 set SOKUTEI_SU=%d ,SOKUTEI_1=%6.3f , SOKUTEI_2=%6.3f, SOKUTE_AVE=%9.6f,",
								KD11Data[i].SOKUTEI_NM_CUR,
								KD11Data[i].SOKUTEICHI[0],
								KD11Data[i].SOKUTEICHI[1],
								KD11Data[i].SOKUTE_AVE);


			str = str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD11Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;

			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD11Data[i].ADDYMD.c_str(),
									KD11Data[i].ADDTIM.c_str(),
									KD11Data[i].UPDCHR,
									KD11Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD11Data[i].UPDYMD.c_str(),
									KD11Data[i].UPDTIM.c_str(),
									KD11Data[i].UPDCHR,
									KD11Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD11Data[i].KENSA_YMD.c_str(),
			//					KD11Data[i].TOLEY_NO ,
			//					KD11Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD11Data[i].KENSA_YMD.c_str(),
						KD11Data[i].TOLEY_NO ,
						KD11Data[i].SAMPLE_P ,
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
				StatBarClear( e.Message )  ;
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
			}
			catch(Exception& e)
			{
				// ShowMessage(e.Message);
				Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
				Update_err = 1;
				StatBarClear( e.Message )  ;
			}

			//ブラシ幅寸法計測（例外）ﾌｧｲﾙの更新
			if( KD11Data[i].SOKUTEI_NM > 2 ){
				Kd12_Update01(i) ;
			}
		} else {
			//2002/11/22 E.Takase
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD11Data[i].ADDYMD )) || !(IsNullSpace(KD11Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD11Data[i].ADDYMD )){
					KD11Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD11Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD11Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD11Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD11Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD11Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD11 set MEMO='%s' , ", KD11Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD11Data[i].ADDYMD.c_str(),
										KD11Data[i].ADDTIM.c_str(),
										KD11Data[i].UPDCHR,
										KD11Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD11Data[i].UPDYMD.c_str(),
										KD11Data[i].UPDTIM.c_str(),
										KD11Data[i].UPDCHR,
										KD11Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD11Data[i].KENSA_YMD.c_str(),
				//					KD11Data[i].TOLEY_NO ,
				//					KD11Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
				wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
									KD11Data[i].KENSA_YMD.c_str(),
									KD11Data[i].TOLEY_NO ,
									KD11Data[i].SAMPLE_P ,
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
*  function name : void Kd12_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO-1    |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀをブラシ幅寸法計測(例外）ﾌｧｲﾙへ書き込む KD12*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD11Data[iRec].SOKUTEI_NM; i++ ){

         // KD12へ追加するレコード存在するかどうかのチェック
         iRtn = Kd12_Serch02( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn <= 0 ) {
           Kd12_Insert01( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）

           Kd12_Update02( KD11Data[iRec].KENSA_YMD,
                          KD11Data[iRec].TOLEY_NO,
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
*  create        : 1999.10                                             *
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
*  function name : int Kd12_Serch02(AnsiString sYmd, int iTlno,        *
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
*  create        : 1999.10                                             *
*  update        : 2001.05.21(SQL文 修正)                              *
*  contents      : 指定したﾚｺｰﾄﾞがブラシ幅寸法例外ﾌｧｲﾙにあるかどうか   *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd12_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD12 ";
        sBuf += "WHERE  KD12.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD12.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD12.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD12.SOKUTEI_NO = '" + strVal04 + "' ";
		sBuf += "AND  KD12.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD12.KENSA_YMD, KD12.TOLEY_NO, KD12.SAMPLE_P, KD12.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->Eof )
          return 0 ;

    return  1 ;
}


/***********************************************************************
*  function name : void Kd12_Update02(AnsiString sYmd, int iTlno,      *
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
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法ﾃﾞｰﾀﾌｧｲﾙKD12へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD12 set SOKUTEICHI=%.3f", KD11Data[iSp-1].SOKUTEICHI[iDtNo-1]);

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
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
         // ShowMessage(e.Message);
         Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
         Update_err = 1;
         StatBarClear( e.Message )  ;
     }
 }

/***********************************************************************
*  function name : void Kd12_Insert01(AnsiString sYmd, int iTlno,      *
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
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法KD12へ指定したﾚｺｰﾄﾞを追加する           *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd12_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
{
    AnsiString str;
    char str_c[256];


    str_c[0] = NULL ;

    //Initial Query1
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //お問い合せ文  Update
    sprintf(str_c, " insert into  KD12(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEICHI, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%.3f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo , KD11Data[iSp-1].SOKUTEICHI[iDtNo-1], iKojoKbn);      // 20160630_工場区分追加

     str += str_c ;
     Form1->Query1->SQL->Add(str);
     if(Form1->Database1->InTransaction == false ){
        Form1->Database1->StartTransaction();
     }

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
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
     catch(Exception& e)
     {
       //  ShowMessage(e.Message);
       Form1->Database1->Rollback();   // 失敗した場合、変更を取り消す
       Update_err = 1;
       StatBarClear( e.Message )  ;
     }
 }


/***********************************************************************
*  function name : void Kd13W_Create01(AnsiString sYmd, int iTlno,     *
*                                                       int iNum)      *
*                  +--------------------------------------+            *
*          引  数  | sYmd       |  検査予定日             |            *
*                  | iTlno      |  ﾄﾚｰNO                  |            *
*                  | iNum       |  ロット数               |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |             | レコード数             |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 履歴作画のために KD13Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd13W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD13WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ブラシ幅寸法計測履歴ﾜｰｸﾃﾞｰﾀ構造体KD13dataを初期化   *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD13WFormat(void)
{
   for( int i=0; i<30; i++){
       KD13WData[i].DTKSHIN = '\0';              //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD13WData[i].LOTNO[j]  = 0.0 ;       //ロットNO
            KD13WData[i].BURASI_MIN[j] = 0.0  ;  //ブラシ幅寸法 規格下
            KD13WData[i].BURASI_MAX[j] = 0.0;    //ブラシ幅寸法 規格上
            KD13WData[i].SOKUTE_AVE[j] = 0.0;    //計測平均値
            KD13WData[i].SOKUTEI_NM[j] = 0;      //ﾛｯﾄNO毎の計測ﾃﾞｰﾀ個数
            for( int k=0; k<100; k++ )
               KD13WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD13WData[i].LOTCNT = -1;                  //品番毎のﾛｯﾄNO数
    }
}

/***********************************************************************
*  function name : int  Kd13W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : KD13Wﾜｰｸﾃｰﾌﾞﾙからブラシ幅寸法計測履歴データ抽出KD13W*
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd13W_Serch01( void)
{
       int i,j;
       AnsiString strVal01;

        // KD13Data構造体変数の初期化
        KD13WFormat();

         // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD11Data[i].SOKUTE_KBN == 0 && KD11Data[i].SAMPLE_P == -1 ) continue ;
              if( KD11Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番で検索
             strVal01 = KD11Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	          sBuf = "SELECT *  ";
	          sBuf += "FROM KD13W ";
	          sBuf += "WHERE  KD13W.DTKSHIN = '" + strVal01 + "' ";
                  //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD13W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
              sBuf += "ORDER BY ROWNO desc" ;

              Form1->Query1->SQL->Add(sBuf);
              Form1->Query1->Open();

              if ( Form1->Query1->Eof ) {
                 // ShowMessage("KD11にデータがありません");
                 //return -1;
                 continue ;
              }else {
                    Form1->Query1->First();
                    while( !Form1->Query1->Eof )
                    {
                        SetTable13W(i);
                        Form1->Query1->Next();

                     }

                     //
                     KD13WData[i].LOTCNT +=1  ;
             }

             for( int j=0; j < KD13WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD13WData[i].SOKUTEI_NM[j]; k++)
                dAve += KD13WData[i].SOKUTEI[j][k] ;

               if( KD13WData[i].SOKUTEI_NM[j] !=0 )
                  KD13WData[i].SOKUTE_AVE[j] = dAve/KD13WData[i].SOKUTEI_NM[j] ;
             }

       }
    return 1;
}

/***********************************************************************
*  function name : void SetTable13W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD13WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable13W(int iSp)
{

     int iLotno = KD13WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD13WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD13WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD13WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }
            if ( Form1->Query1->FieldValues["BURASI_MIN"].IsNull()) {
               KD13WData[iSp].BURASI_MIN[iLotno] = 0.0;
            }else {
                KD13WData[iSp].BURASI_MIN[iLotno] = Form1->Query1->FieldValues["BURASI_MIN"];
            }
            if ( Form1->Query1->FieldValues["BURASI_MAX"].IsNull()) {
               KD13WData[iSp].BURASI_MAX[iLotno] = 0.0;
            }else {
               KD13WData[iSp].BURASI_MAX[iLotno] = Form1->Query1->FieldValues["BURASI_MAX"];
            }


     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD13WData[iSp].DTKSHIN = " ";
     }else {
            KD13WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD13WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD13WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD13WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD13WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD13WData[iSp].LOTCNT = iLotno ;

 }

 /***********************************************************************
*  function name : void CopyKD11Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD11DataをKD11Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD11Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD11Data[i].SOKUTE_KBN == 0 || KD11Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD11Data[i].LINK == 0 ){
            iLinkSp = KD11Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD11Data[i].LINK;
        }

        if( KD13WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD13WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD13WData[iLinkSp-1].DTKSHIN =  KD11Data[i].DTKSHIN;

           //ロットNO
           KD13WData[iLinkSp-1].LOTNO[0]  = KD11Data[i].LOTNO ;

           // 規格下
           KD13WData[iLinkSp-1].BURASI_MIN[0] = KD11Data[i].BURASI_MIN;
           // 規格上
           KD13WData[iLinkSp-1].BURASI_MAX[0] = KD11Data[i].BURASI_MAX;

           KD13WData[iLinkSp-1].SOKUTEI_NM[0] = KD11Data[i].SOKUTEI_NM_CUR;

           if( KD11Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD11Data[i].SOKUTEI_NM; k++ ) {
                  KD13WData[iLinkSp-1].SOKUTEI[0][k] = KD11Data[i].SOKUTEICHI[k];
                  a += KD13WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD11Data[i].SOKUTEI_NM != 0 )
             KD13WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD11Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD13WData[iLinkSp-1].LOTCNT += 1;

          n = KD13WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD13WData[iLinkSp-1].LOTNO[n-1]  = KD11Data[i].LOTNO ;

          //リード線長さ 規格下
          KD13WData[iLinkSp-1].BURASI_MIN[n-1] = KD11Data[i].BURASI_MIN;

          //リード線長さ 規格上
          KD13WData[iLinkSp-1].BURASI_MAX[n-1] = KD11Data[i].BURASI_MAX;

          KD13WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD11Data[i].SOKUTEI_NM_CUR;

          if( KD11Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD11Data[i].SOKUTEI_NM; k++ ) {
               KD13WData[iLinkSp-1].SOKUTEI[n-1][k] = KD11Data[i].SOKUTEICHI[k];
               a += KD13WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD13WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD11Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd13w(void)                                 *
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
void  AddKd13W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD11Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD11Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD13WData[iLinkSp-1].LOTNO[iRtn] = KD11Data[SamplePositionIdx-1].LOTNO;

   //リード線長さ 規格下
    KD13WData[iLinkSp-1].BURASI_MIN[iRtn]= KD11Data[SamplePositionIdx-1].BURASI_MIN;

    //リード線長さ 規格上
    KD13WData[iLinkSp-1].BURASI_MAX[iRtn] = KD11Data[SamplePositionIdx-1].BURASI_MAX;

    KD13WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KD13WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD13WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD11Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD11Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD11Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD13WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}
/***********************************************************************
*  function name : void Kd03W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd03Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd03W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD03W");

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



/***********************************************************************
*  function name : void Kd03W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd13Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd13W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD13W");

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
