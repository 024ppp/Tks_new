/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ１９）                  *
*  file   name   : U_TKS19_Data.cpp                                    *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 座屈測定処理データアクセス関数                      *
*  written by    : 呉 亜娟 （NKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

AnsiString sBuf ;            // ワーク変数

// 関数の宣言
void KD91Format(void);
void SetTable91(void);
int  Kd92_Serch02( AnsiString , int , int, int );
void Kd92_Update01( int );
void Kd92_Update02( AnsiString , int, int, int );
void Kd92_Insert01( AnsiString , int ,int, int );
void SetTable93W(int);

/***********************************************************************
*  function name : int  Kd91_Serch01(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   iRec     | レコード数              |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 座屈ﾃﾞｰﾀﾌｧｲﾙから検査予定日、ﾄﾚｰNoを抽出             *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int Kd91_Serch01(void)
{

    //座屈ﾃﾞｰﾀﾌｧｲﾙからマスタデータを抽出
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    //問い合せ文実行
    //検査予定日、トレーNo
    sBuf = "SELECT ";
    sBuf += "DISTINCT KD91.KENSA_YMD, KD91.TOLEY_NO ";
    sBuf += "FROM KD91 ";
    sBuf += "WHERE KD91.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                 // 工場区分追加
    sBuf += "ORDER BY KD91.KENSA_YMD desc, KD91.TOLEY_NO";

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
      return -1;
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
*  function name : void Kd91_Serch02(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 座屈ﾃﾞｰﾀﾌｧｲﾙからﾃﾞｰﾀを抽出  KD91                    *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd91_Serch02( void)
{
       int n,i;
       AnsiString strVal01;
       AnsiString strVal02;
       AnsiString strVal03;

       // KD91Data構造体変数の初期化(「検索」ﾎﾞﾀﾝを押した場合)
       if( !Save_Click) KD91Format();

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
	sBuf += "FROM KD91 ";
	sBuf += "WHERE  KD91.KENSA_YMD = '" + strVal01 + "' ";
	sBuf += "AND  KD91.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND KD91.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	//2001.05.21 修正 sBuf += "ORDER BY KD91.KENSA_YMD, KD91.TOLEY_NO, KD91.SAMPLE_P";
	sBuf += "ORDER BY KD91.SAMPLE_P";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();


        if ( Form1->Query1->Eof ) {
          // ShowMessage("KD91にデータがありません");
          return -1;
        }else {

          // 「保存」ﾎﾞﾀﾝを押して次のﾄﾚｰNOを検索する場合
          if( Save_Click )
           {
               // ﾄﾚｰNOの設定
               Form1->edttlno->Text = strVal02 ;

               // KD91Data構造体変数の初期化
               KD91Format();
           }

           Form1->Query1->First();
           while( !Form1->Query1->Eof )
           {
                     SetTable91();
                     Form1->Query1->Next();

            }
       }

       //Link NO
       for( i=0; i<29; i++ ){
          if( KD91Data[i].SOKUTE_KBN  && KD91Data[i].SAMPLE_P != -1 ) {
             if( KD91Data[i].LINK == 0 ){
                for( int j=i+1; j<30; j++ ){
                  if( KD91Data[i].DTKSHIN == KD91Data[j].DTKSHIN)
                        KD91Data[j].LINK = KD91Data[i].SAMPLE_P ;
                }
             }
          }
        }

       //計測数Ｎ＞２の場合 座屈測定（例外）ﾌｧｲﾙを読み込む
       for( i=0; i<30; i++ )
       {
          if( KD91Data[i].SOKUTEI_NM > 2 && KD91Data[i].SOKUTE_KBN == 1 &&
              KD91Data[i].SOKUTEI_NM_CUR > 0 ) {
              Form1->Query1->Close();
              Form1->Query1->SQL->Clear();

              strVal03 = IntToStr( KD91Data[i].SAMPLE_P );

              //問い合せ文実行
              //ソート昇順 、検査予定日、トレーNo、サンプルポジション
	        sBuf = "SELECT ";
	        sBuf += "KD92.SOKUTEICHI, KD92.SOKUTEI_NO ";
	        sBuf += "FROM KD92 ";
	        sBuf += "WHERE  KD92.KENSA_YMD = '" + strVal01 + "' ";
	        sBuf += "AND  KD92.TOLEY_NO = '" + strVal02 + "' ";
	        sBuf += "AND  KD92.SAMPLE_P = '" + strVal03 + "' ";
                sBuf += "AND  KD92.KOJOKBN = " + IntToStr(iKojoKbn) + " ";                     // 工場区分追加
	        //2001.05.21 修正 sBuf += "ORDER BY KD92.KENSA_YMD, KD92.TOLEY_NO, KD92.SAMPLE_P, KD92.SOKUTEI_NO";
	        sBuf += "ORDER BY KD92.SOKUTEI_NO";

                 Form1->Query1->SQL->Add(sBuf);
                 Form1->Query1->Open();

                 if ( Form1->Query1->Eof ) {
                    //ShowMessage("KD92にデータがありません");
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
                                   KD91Data[i].SOKUTEICHI[n-1] = 0.0;
                             }else {
                                   KD91Data[i].SOKUTEICHI[n-1] =  Form1->Query1->FieldValues["SOKUTEICHI"];
                             }

                             Form1->Query1->Next();
                      }
                 }
          }

       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable91(int )                               *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : KD91Data構造体へﾃﾞｰﾀを設定                          *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable91()
{

     int iRec =  Form1->Query1->FieldValues["SAMPLE_P"];

      KD91Data[iRec-1].SAMPLE_P  = iRec  ;

      iRec -= 1;

     if ( Form1->Query1->FieldValues["KENSA_YMD"].IsNull()) {
          KD91Data[iRec].KENSA_YMD = " ";
     }else {
          KD91Data[iRec].KENSA_YMD = Form1->Query1->FieldValues["KENSA_YMD"];
     }

     if ( Form1->Query1->FieldValues["TOLEY_NO"].IsNull()) {
          KD91Data[iRec].TOLEY_NO = 0;
     }else {
          KD91Data[iRec].TOLEY_NO = Form1->Query1->FieldValues["TOLEY_NO"];
     }

     if ( Form1->Query1->FieldValues["SOKUTE_KBN"].IsNull()) {
          KD91Data[iRec].SOKUTE_KBN = 0;
     }else {
          KD91Data[iRec].SOKUTE_KBN =  Form1->Query1->FieldValues["SOKUTE_KBN"];

          if( HaveSokutei == 0 &&KD91Data[iRec].SOKUTE_KBN== 1 ){
              HaveSokutei = 1;
          }
     }

     if ( Form1->Query1->FieldValues["DTKSCOD"].IsNull()) {
          KD91Data[iRec].DTKSCOD = " ";
     }else {
          KD91Data[iRec].DTKSCOD =  Form1->Query1->FieldValues["DTKSCOD"];
     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
          KD91Data[iRec].DTKSHIN = " ";
     }else {
          KD91Data[iRec].DTKSHIN =  Form1->Query1->FieldValues["DTKSHIN"];
     }

     if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
          KD91Data[iRec].LOTNO = " ";
     }else {
          KD91Data[iRec].LOTNO =  Form1->Query1->FieldValues["LOTNO"];
     }

     if ( Form1->Query1->FieldValues["HINBAN"].IsNull()) {
          KD91Data[iRec].HINBAN = " ";
     }else {
          KD91Data[iRec].HINBAN =  Form1->Query1->FieldValues["HINBAN"];
     }

     if ( Form1->Query1->FieldValues["ZISCOD"].IsNull()) {
          KD91Data[iRec].ZISCOD = " ";
     }else {
          KD91Data[iRec].ZISCOD =  Form1->Query1->FieldValues["ZISCOD"];
     }

     if ( Form1->Query1->FieldValues["ZISNAM"].IsNull()) {
          KD91Data[iRec].ZISNAM = " ";
     }else {
          KD91Data[iRec].ZISNAM =  Form1->Query1->FieldValues["ZISNAM"];
     }

     if ( Form1->Query1->FieldValues["ZAKUT_MIN"].IsNull()) {
          KD91Data[iRec].ZAKUT_MIN = 0.0;
     }else {
          KD91Data[iRec].ZAKUT_MIN =  Form1->Query1->FieldValues["ZAKUT_MIN"];
     }

     if ( Form1->Query1->FieldValues["ZAKUT_MAX"].IsNull()) {
          KD91Data[iRec].ZAKUT_MAX = 0.0;
     }else {
          KD91Data[iRec].ZAKUT_MAX =  Form1->Query1->FieldValues["ZAKUT_MAX"];
     }

      if ( Form1->Query1->FieldValues["SOKUTEI_1"].IsNull()) {
          KD91Data[iRec].SOKUTEICHI[0] = 0.0;
     }else {
          KD91Data[iRec].SOKUTEICHI[0] =  Form1->Query1->FieldValues["SOKUTEI_1"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_2"].IsNull()) {
          KD91Data[iRec].SOKUTEICHI[1] = 0.0;
     }else {
          KD91Data[iRec].SOKUTEICHI[1] =  Form1->Query1->FieldValues["SOKUTEI_2"];
     }

     if ( Form1->Query1->FieldValues["SOKUTEI_NM"].IsNull()) {
          KD91Data[iRec].SOKUTEI_NM = 0;
     }else {
          KD91Data[iRec].SOKUTEI_NM =  Form1->Query1->FieldValues["SOKUTEI_NM"];
     }
     if ( Form1->Query1->FieldValues["SOKUTEI_SU"].IsNull()) {
          KD91Data[iRec].SOKUTEI_SU = 0;
     }else {
          KD91Data[iRec].SOKUTEI_SU =  Form1->Query1->FieldValues["SOKUTEI_SU"];
     }
     if ( Form1->Query1->FieldValues["SOKUTE_AVE"].IsNull()) {
          KD91Data[iRec].SOKUTE_AVE = 0.0;
     }else {
          KD91Data[iRec].SOKUTE_AVE =  Form1->Query1->FieldValues["SOKUTE_AVE"];
     }

    if ( Form1->Query1->FieldValues["ADDYMD"].IsNull()) {
          KD91Data[iRec].ADDYMD = " ";
          KD91Data[iRec].SOKUTEI_NM_CUR = 0;
     }else {
          KD91Data[iRec].ADDYMD =  Form1->Query1->FieldValues["ADDYMD"];
          if( IsNullSpace( KD91Data[iRec].ADDYMD )){
             KD91Data[iRec].SOKUTEI_NM_CUR = 0 ;
          }else{
             KD91Data[iRec].SOKUTEI_NM_CUR = KD91Data[iRec].SOKUTEI_SU ;
          }

     }

     if ( Form1->Query1->FieldValues["ADDTIM"].IsNull()) {
          KD91Data[iRec].ADDTIM = " ";
     }else {
          KD91Data[iRec].ADDTIM =  Form1->Query1->FieldValues["ADDTIM"];
     }

     if ( Form1->Query1->FieldValues["UPDYMD"].IsNull()) {
          KD91Data[iRec].UPDYMD = " ";
     }else {
          KD91Data[iRec].UPDYMD =  Form1->Query1->FieldValues["UPDYMD"];
     }

     if ( Form1->Query1->FieldValues["UPDCHR"].IsNull()) {
          KD91Data[iRec].UPDCHR = 0;
     }else {
          KD91Data[iRec].UPDCHR =  Form1->Query1->FieldValues["UPDCHR"];
     }

     if ( Form1->Query1->FieldValues["UPDCNT"].IsNull()) {
          KD91Data[iRec].UPDCNT = 0;
     }else {
          KD91Data[iRec].UPDCNT =  Form1->Query1->FieldValues["UPDCNT"];
     }

     //備考 2002/11/07 E.Takase
     if ( Form1->Query1->FieldValues["MEMO"].IsNull()) {
          KD91Data[iRec].MEMO =  " ";
     }else {
          KD91Data[iRec].MEMO =  Form1->Query1->FieldValues["MEMO"];
     }

 }

/***********************************************************************
*  function name : void KD91Format(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 座屈データ構造体KD91Dataを初期化   KD91     *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD91Format(void)
{
   for( int i=0; i<30; i++){
      KD91Data[i].KENSA_YMD =  '\0';  //検索予定日
      KD91Data[i].TOLEY_NO = 0 ;      //ﾄﾚｰNO
      KD91Data[i].SAMPLE_P = -1 ;     //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO
      KD91Data[i].SOKUTE_KBN = 0;     //測定区分
      KD91Data[i].DTKSCOD = '\0';     //得意先コード
      KD91Data[i].DTKSHIN = '\0';     //得意先品番
      KD91Data[i].LOTNO = '\0';       //ロットNO
      KD91Data[i].HINBAN = '\0';      //自社品番
      KD91Data[i].ZISCOD = '\0';      //材質コード
      KD91Data[i].ZISNAM = '\0';      //材質名
      KD91Data[i].ZAKUT_MIN = 0.0;    //座屈 規格下
      KD91Data[i].ZAKUT_MAX = 0.0;    //座屈 規格上
      KD91Data[i].SOKUTEI_NM = 0;     //座屈測定個数
      KD91Data[i].SOKUTEI_SU = 0;     //座屈測定個数
      KD91Data[i].SOKUTE_AVE = 0.0;   //測定平均値
      memset(KD91Data[i].SOKUTEICHI,(int)NULL, sizeof(double) * 100); ; //測定値
      KD91Data[i].ADDYMD = '\0';      //登録日
      KD91Data[i].ADDTIM = '\0';      //登録時間
      KD91Data[i].UPDYMD = '\0';      //変更日
      KD91Data[i].UPDTIM = '\0';      //変更時間
      KD91Data[i].UPDCHR = 0;         //更新者
      KD91Data[i].UPDCNT = 0;         //更新回数
      KD91Data[i].LINK = 0;
      KD91Data[i].SOKUTEI_NM_CUR = 0;
      KD91Data[i].MEMO = '\0';         //備考 2002/11/07 E.Takase
   }
}


/***********************************************************************
*  function name : void Kd91_Update01(void)                            *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        : 2002.11.07 備考ﾃﾞｰﾀ追加 E.Takase                    *
*  contents      : 計測ﾃﾞｰﾀを座屈ﾃﾞｰﾀﾌｧｲﾙへ書き込む  KD91              *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd91_Update01( void)
{

    int i,j,n,iToroku;
    AnsiString str;
    char str_c[256];

    Update_err =0;

    // 画面の入力ﾃﾞｰﾀを取得
    if( DataNoIdx == 1 ){
               // 計測ﾃﾞｰﾀ1
             KD91Data[SamplePositionIdx-1].SOKUTEICHI[0] = pEdt1[SamplePositionIdx-1]->Value;
    }else if( DataNoIdx == 1 ){

             // 計測ﾃﾞｰﾀ2
             KD91Data[SamplePositionIdx-1].SOKUTEICHI[1] = pEdt2[SamplePositionIdx-1]->Value;

    }else {
             // 計測ﾃﾞｰﾀ n?
             if( KD91Data[SamplePositionIdx-1].SOKUTEI_NM > 2){
                 n = pEdt4[SamplePositionIdx-1]->Value;
                 if( n >=3 && n<= KD91Data[SamplePositionIdx-1].SOKUTEI_NM )
                    KD91Data[SamplePositionIdx-1].SOKUTEICHI[n-1] = pEdt3[SamplePositionIdx-1]->Value;
             }
    }

	for( i=0; i<30; i++ ){
		iToroku = 1;

		if( KD91Data[i].SOKUTE_KBN == 1 && KD91Data[i].SAMPLE_P != -1 &&
			KD91Data[i].SOKUTEI_NM_CUR != 0 ){

			//担当者ｺｰﾄﾞ
			KD91Data[i].UPDCHR = USER_COD ;

			// 測定予定日
			//KD91Data[i].KENSA_YMD = DelSEPA(Form1->edtymd->Text);

			// ﾄﾚｰNO
			//KD91Data[i].TOLEY_NO =  Form1->edttlno->Value ;

			//測定値平均値の算出
			double a = 0.0;
			for(j=0; j< KD91Data[i].SOKUTEI_NM_CUR; j++ )
				a += KD91Data[i].SOKUTEICHI[j] ;

			if( KD91Data[i].SOKUTEI_NM_CUR )
				KD91Data[i].SOKUTE_AVE = a/KD91Data[i].SOKUTEI_NM_CUR ;

			// 登録日、登録時間
			if( IsNullSpace( KD91Data[i].ADDYMD )){
				KD91Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
				KD91Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD91Data[i].UPDCNT = 0;

			}else{
				// 変更日、変更時間
				KD91Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
				KD91Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

				//更新回数
				KD91Data[i].UPDCNT += 1;

				iToroku = 0;
			}

			//計測したﾃﾞｰﾀをKD91ﾌｧｲﾙへ更新

			str_c[0] = NULL ;

			//Initial Query1
			Form1->Query1->Close();
			Form1->Query1->SQL->Clear();
			if(Form1->Database1->InTransaction == false ){
				Form1->Database1->StartTransaction();
			}

			//お問い合せ文  Update
			sprintf(str_c, " update KD91 set SOKUTEI_SU=%d ,SOKUTEI_1=%7.0f , SOKUTEI_2=%7.0f, SOKUTE_AVE=%12.5f,",
								KD91Data[i].SOKUTEI_NM_CUR,
								KD91Data[i].SOKUTEICHI[0],
								KD91Data[i].SOKUTEICHI[1],
								KD91Data[i].SOKUTE_AVE);


			str = str_c ;
			str_c[0] = NULL ;

			//備考追加 2002/11/07 E.Takase
			sprintf(str_c, " MEMO='%s' ,",
								KD91Data[i].MEMO);
			str += str_c ;
			str_c[0] = NULL ;


			if( iToroku ){
				wsprintf(str_c, " ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD91Data[i].ADDYMD.c_str(),
									KD91Data[i].ADDTIM.c_str(),
									KD91Data[i].UPDCHR,
									KD91Data[i].UPDCNT );
			}else{
				wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
									KD91Data[i].UPDYMD.c_str(),
									KD91Data[i].UPDTIM.c_str(),
									KD91Data[i].UPDCHR,
									KD91Data[i].UPDCNT );
			}
			str += str_c ;
			str_c[0] = NULL ;

			//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
			//					KD91Data[i].KENSA_YMD.c_str(),
			//					KD91Data[i].TOLEY_NO ,
			//					KD91Data[i].SAMPLE_P );
                        // 20160630_工場区分追加
			wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD91Data[i].KENSA_YMD.c_str(),
						KD91Data[i].TOLEY_NO ,
						KD91Data[i].SAMPLE_P ,
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

			//座屈測定（例外）ﾌｧｲﾙの更新
			if( KD91Data[i].SOKUTEI_NM > 2 ){
				Kd92_Update01(i) ;
			}
		} else {
			//備考のみ入っていた場合、備考のみ保存
			if(!(IsNullSpace( KD91Data[i].ADDYMD )) || !(IsNullSpace(KD91Data[i].MEMO))){
				// 登録日、登録時間
				if( IsNullSpace( KD91Data[i].ADDYMD )){
					KD91Data[i].ADDYMD = FormatDateTime("yyyymmdd",Date());
					KD91Data[i].ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD91Data[i].UPDCNT = 0;

				}else{
					// 変更日、変更時間
					KD91Data[i].UPDYMD = FormatDateTime("yyyymmdd",Date());
					KD91Data[i].UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

					//更新回数
					KD91Data[i].UPDCNT += 1;

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
				sprintf(str_c, " update KD91 set MEMO='%s' , ", KD91Data[i].MEMO);
				str = str_c ;
				str_c[0] = NULL ;

				if( iToroku ){
					wsprintf(str_c, "ADDYMD=%s, ADDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD91Data[i].ADDYMD.c_str(),
										KD91Data[i].ADDTIM.c_str(),
										KD91Data[i].UPDCHR,
										KD91Data[i].UPDCNT );
				}else{
					wsprintf(str_c, " UPDYMD=%s, UPDTIM=%s,UPDCHR=%d,UPDCNT=%d  ",
										KD91Data[i].UPDYMD.c_str(),
										KD91Data[i].UPDTIM.c_str(),
										KD91Data[i].UPDCHR,
										KD91Data[i].UPDCNT );
				}
				str += str_c ;
				str_c[0] = NULL ;

				//wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d ",
				//					KD91Data[i].KENSA_YMD.c_str(),
				//					KD91Data[i].TOLEY_NO ,
				//					KD91Data[i].SAMPLE_P );
                                // 20160630_工場区分追加
			        wsprintf(str_c, " where KENSA_YMD =%s AND TOLEY_NO =%d AND SAMPLE_P =%d AND KOJOKBN =%d ",
						KD91Data[i].KENSA_YMD.c_str(),
						KD91Data[i].TOLEY_NO ,
						KD91Data[i].SAMPLE_P ,
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
*  function name : void Kd92_Update01(int  iRec)                       *
*                  +--------------------------------------+            *
*          引  数  |   iRec     | ｶﾚﾝﾄｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO      |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 計測ﾃﾞｰﾀを座屈測定(例外）ﾌｧｲﾙへ書き込む KD92        *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd92_Update01( int iRec)
{

    int i, iRtn;

    for( i=2; i<KD91Data[iRec].SOKUTEI_NM; i++ ){

         // KD92へ追加するレコード存在するかどうかのチェック
         iRtn = Kd92_Serch02( KD91Data[iRec].KENSA_YMD,
                          KD91Data[iRec].TOLEY_NO,
                          iRec+1, i+1);

         // 該当レコードが存在しない場合追加（Insert）
         if( iRtn <= 0 ) {
           Kd92_Insert01( KD91Data[iRec].KENSA_YMD,
                          KD91Data[iRec].TOLEY_NO,
                          iRec+1, i+1 )  ;

         }else{   // 該当レコードが存在する場合更新（Update）

           Kd92_Update02( KD91Data[iRec].KENSA_YMD,
                          KD91Data[iRec].TOLEY_NO,
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
*  function name : int Kd92_Serch02(AnsiString sYmd, int iTlno,        *
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
*  update        :                                                     *
*  contents      : 指定したﾚｺｰﾄﾞ座屈ﾃﾞｰﾀ例外ﾌｧｲﾙにあるかどうか         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd92_Serch02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
        sBuf += "FROM KD92 ";
        sBuf += "WHERE  KD92.KENSA_YMD = '" + strVal01 + "' ";
        sBuf += "AND  KD92.TOLEY_NO = '" + strVal02 + "' ";
        sBuf += "AND  KD92.SAMPLE_P = '" + strVal03 + "' ";
        sBuf += "AND  KD92.SOKUTEI_NO = '" + strVal04 + "' ";
        sBuf += "AND  KD92.KOJOKBN = " + IntToStr(iKojoKbn) + " ";              // 20160630_工場区分追加
        //2001.05.21 修正 sBuf += "ORDER BY KD92.KENSA_YMD, KD92.TOLEY_NO, KD92.SAMPLE_P, KD92.SOKUTEI_NO";

        Form1->Query1->SQL->Add(sBuf);
        Form1->Query1->Open();

        if ( Form1->Query1->RecordCount <= 0 )
          return -1 ;

    return 1;
}


/***********************************************************************
*  function name : void Kd92_Update02(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD92へ指定したﾚｺｰﾄﾞを更新する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd92_Update02( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " update KD92 set SOKUTEICHI=%7.0f", KD91Data[iSp-1].SOKUTEICHI[iDtNo-1]);

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
*  function name : void Kd92_Insert01(AnsiString sYmd, int iTlno,      *
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
*  contents      : KD92へ指定したﾚｺｰﾄﾞを追加する                       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  Kd92_Insert01( AnsiString sYmd, int iTlno, int iSp, int iDtNo)
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
    sprintf(str_c, " insert into  KD92(KENSA_YMD, TOLEY_NO,SAMPLE_P, SOKUTEI_NO, SOKUTEICHI, KOJOKBN)");	// 20160630_工場区分追加

    str = str_c ;
    str_c[0] = NULL ;

    sprintf(str_c, " values('%s',%d,%d,%d,%7.0f,%d)",sYmd.c_str(), iTlno, iSp, iDtNo , KD91Data[iSp-1].SOKUTEICHI[iDtNo-1], iKojoKbn);      // 20160630_工場区分追加

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
*  function name : void Kd93W_Create01(AnsiString sYmd, int iTlno,     *
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
*  contents      : 履歴作画のために KD93Wﾜｰｸテーブルを作成する         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
long  Kd93W_Create01(AnsiString sYmd, int iTlno, int iNum)
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
*  function name : void KD93WFormat(void)                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : 座屈計測履歴ﾜｰｸﾃﾞｰﾀ構造体KD93dataを初期化           *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void KD93WFormat(void)
{
   for( int i=0; i<30; i++){
       KD93WData[i].DTKSHIN = '\0';     //得意先品番

       for( int j=0; j< 50 ; j++ ){
            KD93WData[i].LOTNO[j]  = " " ;       //ロットNO
            KD93WData[i].ZAKUT_MIN[j] = 0.0  ;  //座屈 規格下
            KD93WData[i].ZAKUT_MAX[j] = 0.0;    //座屈 規格上
            KD93WData[i].SOKUTE_AVE[j] = 0.0;
            KD93WData[i].SOKUTEI_NM[j] = 0;
            for( int k=0; k<100; k++ )
               KD93WData[i].SOKUTEI[j][k] = 0.0;  //測定値
       }

       KD93WData[i].LOTCNT = -1;
    }
}

/***********************************************************************
*  function name : int  Kd93W_Search01(void)                           *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |    0       | Status                  |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD93Wﾜｰｸﾃｰﾌﾞﾙから座屈計測履歴データ抽出 KD93W       *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
int  Kd93W_Serch01( void)
{
       int i;
       AnsiString strVal01;

        // KD91Data構造体変数の初期化
        KD93WFormat();

        // 履歴作画データを読み込む
        for( i=0; i<30; i++ ){

             // 測定しない場合、検索しない
             if( KD91Data[i].SOKUTE_KBN == 0 && KD91Data[i].SAMPLE_P == -1 ) continue ;
             if( KD91Data[i].LINK ) continue ;

             //ｶﾚﾝﾄﾎﾟｼﾞｼｮﾝNOの品番で検索
             strVal01 = KD91Data[i].DTKSHIN;

             Form1->Query1->Close();
             Form1->Query1->SQL->Clear();

              //問い合せ文実行
              //ソート昇順 ,検査予定日、トレーNo
	      sBuf = "SELECT *  ";
	      sBuf += "FROM KD93W ";
	      sBuf += "WHERE  KD93W.DTKSHIN = '" + strVal01 + "' ";
              //20161128 Y.Onishi
              //工場区分に関わらず測定履歴を取得する
              //sBuf += "AND KD93W.KOJOKBN = " + IntToStr(iKojoKbn) + " ";        // 20160630_工場区分追加
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
                        SetTable93W(i);
                        Form1->Query1->Next();

                     }

                     //
                    KD93WData[i].LOTCNT +=1  ;
               }


            for( int j=0; j < KD93WData[i].LOTCNT; j++ ){
              double dAve =0.0;
              for( int k=0; k < KD93WData[i].SOKUTEI_NM[j]; k++)
                dAve += KD93WData[i].SOKUTEI[j][k] ;

               if( KD93WData[i].SOKUTEI_NM[j] !=0 )
                  KD93WData[i].SOKUTE_AVE[j] = dAve/KD93WData[i].SOKUTEI_NM[j] ;
           }


       }

    return 1;
}

/***********************************************************************
*  function name : void SetTable93W(int )                              *
*                  +--------------------------------------+            *
*          引  数  |   なし     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ﾜｰｸﾃﾞｰﾀKD93WDataへﾃﾞｰﾀを設定                        *
*  written by    : 呉 亜娟 (NKK unics Corp.)                           *
***********************************************************************/
void SetTable93W(int iSp)
{

     int iLotno = KD93WData[iSp].LOTCNT ;

     if(  Form1->Query1->FieldValues["LOTNO"] != KD93WData[iSp].LOTNO[iLotno] )
     {
            iLotno += 1;
            if ( Form1->Query1->FieldValues["LOTNO"].IsNull()) {
                 KD93WData[iSp].LOTNO[iLotno] = " ";
            }else {
                 KD93WData[iSp].LOTNO[iLotno] = Form1->Query1->FieldValues["LOTNO"];
            }
            if ( Form1->Query1->FieldValues["ZAKUT_MIN"].IsNull()) {
               KD93WData[iSp].ZAKUT_MIN[iLotno] = 0.0;
            }else {
                KD93WData[iSp].ZAKUT_MIN[iLotno] = Form1->Query1->FieldValues["ZAKUT_MIN"];
            }
            if ( Form1->Query1->FieldValues["ZAKUT_MAX"].IsNull()) {
               KD93WData[iSp].ZAKUT_MAX[iLotno] = 0.0;
            }else {
               KD93WData[iSp].ZAKUT_MAX[iLotno] = Form1->Query1->FieldValues["ZAKUT_MAX"];
            }


     }

     if ( Form1->Query1->FieldValues["DTKSHIN"].IsNull()) {
            KD93WData[iSp].DTKSHIN = " ";
     }else {
            KD93WData[iSp].DTKSHIN = Form1->Query1->FieldValues["DTKSHIN"];
     }

     // 測定値
     int iDtNo = KD93WData[iSp].SOKUTEI_NM[iLotno] ;

     if ( Form1->Query1->FieldValues["SOKUTEI"].IsNull()) {
         KD93WData[iSp].SOKUTEI[iLotno][iDtNo] = 0.0;
     }else {
       KD93WData[iSp].SOKUTEI[iLotno][iDtNo] = Form1->Query1->FieldValues["SOKUTEI"];
     }

     iDtNo  += 1;
     KD93WData[iSp].SOKUTEI_NM[iLotno] = iDtNo;


     KD93WData[iSp].LOTCNT = iLotno ;

 }

 /***********************************************************************
*  function name : void CopyKD91Data(void)                             *
*                  +--------------------------------------+            *
*          引  数  |   無し     |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |   なし     |                         |            *
*                  +--------------------------------------+            *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : KD91DataをKD91Wへコピーする                         *
*  written by    : 呉 亜娟(NKK unics Corp.)                            *
***********************************************************************/
void  CopyKD91Data(void)
{

   int i,n,k,iLinkSp;

   for( i=0; i<30; i++ ){

        if( KD91Data[i].SOKUTE_KBN == 0 || KD91Data[i].SAMPLE_P == -1 ) continue ;

        // ｶﾚﾝﾄ品番が始めて計測場合
        if(  KD91Data[i].LINK == 0 ){
            iLinkSp = KD91Data[i].SAMPLE_P ;
        }else {
            iLinkSp = KD91Data[i].LINK;
        }

        if( KD93WData[iLinkSp-1].LOTCNT == -1 ){

           //ﾛｯﾄNOカンター
           KD93WData[iLinkSp-1].LOTCNT = 1;

           //得意先品番
           KD93WData[iLinkSp-1].DTKSHIN =  KD91Data[i].DTKSHIN;

           //ロットNO
           KD93WData[iLinkSp-1].LOTNO[0]  = KD91Data[i].LOTNO ;

           // 規格下
           KD93WData[iLinkSp-1].ZAKUT_MIN[0] = KD91Data[i].ZAKUT_MIN;
           // 規格上
           KD93WData[iLinkSp-1].ZAKUT_MAX[0] = KD91Data[i].ZAKUT_MAX;

           KD93WData[iLinkSp-1].SOKUTEI_NM[0] = KD91Data[i].SOKUTEI_NM_CUR;

           if( KD91Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

           //測定値
           double a=0.0;
           for( k=0; k < KD91Data[i].SOKUTEI_NM; k++ ) {
                  KD93WData[iLinkSp-1].SOKUTEI[0][k] = KD91Data[i].SOKUTEICHI[k];
                  a += KD93WData[iLinkSp-1].SOKUTEI[0][k] ;
           }

            //平均値
           if( KD91Data[i].SOKUTEI_NM != 0 )
             KD93WData[iLinkSp-1].SOKUTE_AVE[0] = a/KD91Data[i].SOKUTEI_NM;

     //----------------------------------------------------------------
     // 履歴ﾃﾞｰﾀ中にｶﾚﾝﾄ品番が既存している場合
     }else{

          // 履歴ﾃﾞｰﾀの後ろへｶﾚﾝﾄﾛｯﾄNOのﾃﾞｰﾀを追加
          //ﾛｯﾄNOカンター
          KD93WData[iLinkSp-1].LOTCNT += 1;

          n = KD93WData[iLinkSp-1].LOTCNT ;

          //ロットNO
          KD93WData[iLinkSp-1].LOTNO[n-1]  = KD91Data[i].LOTNO ;

          //リード線長さ 規格下
          KD93WData[iLinkSp-1].ZAKUT_MIN[n-1] = KD91Data[i].ZAKUT_MIN;

          //リード線長さ 規格上
          KD93WData[iLinkSp-1].ZAKUT_MAX[n-1] = KD91Data[i].ZAKUT_MAX;

          KD93WData[iLinkSp-1].SOKUTEI_NM[n-1] = KD91Data[i].SOKUTEI_NM_CUR;

          if( KD91Data[i].SOKUTEI_NM_CUR == 0 ) continue ;

          //測定値
          double a=0.0;
          for( k=0; k < KD91Data[i].SOKUTEI_NM; k++ ) {
               KD93WData[iLinkSp-1].SOKUTEI[n-1][k] = KD91Data[i].SOKUTEICHI[k];
               a += KD93WData[iLinkSp-1].SOKUTEI[n-1][k] ;
          }

          KD93WData[iLinkSp-1].SOKUTE_AVE[n-1] = a/KD91Data[i].SOKUTEI_NM;
      }
   }
}


 /***********************************************************************
*  function name : void AddKd93w(void)                                 *
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
void  AddKd93W(void)
{
   int i,iLinkSp;

   //履歴ﾃﾞｰﾀﾌｧｲﾙのチェック

   if( KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR == 0 ) return ;

   //-------------------------------------
   // ｶﾚﾝﾄ品番が始めて計測場合
   if(  KD91Data[SamplePositionIdx-1].LINK == 0 ){
       iLinkSp = SamplePositionIdx ;
   }else {
       iLinkSp = KD91Data[SamplePositionIdx-1].LINK;
   }

   //履歴ﾃﾞｰﾀ中にｶﾚﾝﾄﾛｯﾄNoのINDEXNO
   int iRtn =  CheckLotNo( SamplePositionIdx ) ;
   if( iRtn <0 ) return ;

   //計測履歴ﾃﾞｰﾀの更新
   //ロットNO
    KD93WData[iLinkSp-1].LOTNO[iRtn] = KD91Data[SamplePositionIdx-1].LOTNO;

   //リード線長さ 規格下
    KD93WData[iLinkSp-1].ZAKUT_MIN[iRtn]= KD91Data[SamplePositionIdx-1].ZAKUT_MIN;

    //リード線長さ 規格上
    KD93WData[iLinkSp-1].ZAKUT_MAX[iRtn] = KD91Data[SamplePositionIdx-1].ZAKUT_MAX;

    KD93WData[iLinkSp-1].SOKUTEI_NM[iRtn] = KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR;

    //測定値
    for( i=0; i < KD93WData[iLinkSp-1].SOKUTEI_NM[iRtn]; i++ )
         KD93WData[iLinkSp-1].SOKUTEI[iRtn][i] = KD91Data[SamplePositionIdx-1].SOKUTEICHI[i];

   double dAve ;
   dAve = 0.0;
   for( i=0; i< KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR; i++ ){
        dAve += KD91Data[SamplePositionIdx-1].SOKUTEICHI[i];
   }

   dAve= dAve/KD91Data[SamplePositionIdx-1].SOKUTEI_NM_CUR ;

   KD93WData[iLinkSp-1].SOKUTE_AVE[iRtn]=dAve;

}



/***********************************************************************
*  function name : void Kd93W_Delete01(void)                           *
*                  +--------------------------------------+            *
*          引  数  | 無し       |                         |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  無し      |                         |            *
*                  +--------------------------------------+            *
*  create        : 2002.11                                             *
*  update        :                                                     *
*  contents      : Kd93Wのデータを削除する                             *
*  written by    : 高瀬 恵利(NKK unics Corp.)                           *
***********************************************************************/
void  Kd93W_Delete01(void)
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
    sprintf(str_c, " DELETE FROM KD93W");

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
