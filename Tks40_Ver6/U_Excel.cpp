//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <dir.h>


#pragma hdrstop
#include "unit1.h"
#include "unit3.h"
#include "U_Excel.h"
#define COM_DIFF 0.000001
const int E_Nums = 300;
char CDPath[1028];
char path[1028];
double E_Standard_Scale[20] = {500, 100, 50, 20, 10, 5, 2, 1, 0.5, 0.2, 0.1, 0.05,
                           0.02, 0.01, 0.005, 0.002, 0.001, 0.0005, 0.0002, 0.0001};

//extern KDB1_DATA Tmp_KDB1;             // 選択した工程能力
//extern KETA_DATA KETA;  //印刷時の桁数
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//ＣＳＶ２（工程能力調査表）データ作成
bool __fastcall TForm1::CSV2_Write()
{
    AnsiString sBuf;
    int i,n;
    int Tmp_E_Scale;
    int k;
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    AnsiString KOUMOKU_J;
    AnsiString KOUMOKU_E;
    FILE *stream;
    int tmpSOKUTEI_SU1;
    int tmpSOKUTEI_SU2;
    int tmpSOKUTEI_SU3;
    int tmpSOKUTEI_SU4;

    Tmp_E_Scale = 0;
    //カレントディレクトリの取得
    strcpy(CDPath, "X:\\");	/* 値を返す形式: X:\ で文字列を満たす */
    CDPath[0] = 'A' + getdisk();	/* X を現在のドライブ名に置き換える */
    getcurdir(0, CDPath+3);	/* 文字列部分の残りにカレントディレクトリを追加 */



    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\data2.csv");
    if( (stream = fopen( path, "w+" )) != NULL ){	//正常にﾌｧｲﾙをｵｰﾌﾟﾝできた場合

        //項目数分必要
        for ( n = 0; n < SGr1->RowCount-1; n++ ) {
            //グラフスケール 以上 未満 個数 工程能力測定データ１ を 求める
            Sub_Tmp_KDB1(n);

            //桁数指定（フォーマット）を求める
            k = Form3->KENSASYOSIKI_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1,Tmp_KDB1.SOKUTE_KET);

            Toukei_Tmp_KDB1( k );

            KETA.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE;
            KETA.SOKUTE_MIN = Tmp_KDB1.SOKUTE_MIN;
            KETA.SOKUTE_MAX = Tmp_KDB1.SOKUTE_MAX;
            KETA.SOKUTE_R   = Tmp_KDB1.SOKUTE_R  ;
            KETA.SOKUTE_SGM = Tmp_KDB1.SOKUTE_SGM;
            KETA.SOKUTE_CP  = Tmp_KDB1.SOKUTE_CP ;
            KETA.SOKUTE_CPK = Tmp_KDB1.SOKUTE_CPK;
            KETA.SOKUTE_K   = Tmp_KDB1.SOKUTE_K  ;
            KETA.SOKUTE_P   = Tmp_KDB1.SOKUTE_P  ;

	        KETA.R_str   = Form3->ConvKETA1( k,KETA.SOKUTE_R );
	        //KETA.R_str   = "#0.00";
	        KETA.AVE_str = Form3->ConvKETA1( k+1,KETA.SOKUTE_AVE );
	        KETA.MIN_str = Form3->ConvKETA1( k,KETA.SOKUTE_MIN );
	        KETA.MAX_str = Form3->ConvKETA1( k,KETA.SOKUTE_MAX );
	        KETA.SGM_str = Form3->ConvKETA2( 3,KETA.SOKUTE_SGM ,1 );
        	KETA.CP_str  = Form3->ConvKETA1( 2,KETA.SOKUTE_CP  );
	        KETA.K_str   = Form3->ConvKETA2( 2,KETA.SOKUTE_K ,2  );
	        KETA.CPK_str = Form3->ConvKETA1( 2,KETA.SOKUTE_CPK );
	        KETA.P_str   = Form3->ConvKETA1( 2,KETA.SOKUTE_P   );


            //グラフ目盛りのスケール 比較
            if ( Tmp_E_Scale < E_Scale) Tmp_E_Scale = E_Scale;

            //測定項目
            if( Tmp_KDB1.KENSA_KMK == 6 ) {
            	if ( Tmp_KDB1.JYOKEN1 == 2 || Tmp_KDB1.JYOKEN1 == 4 ) {
            		KOUMOKU_J = "硬度（側面）";
            		KOUMOKU_E = "Hardness(S)";
                } else {
            		KOUMOKU_J = "硬度";
            		KOUMOKU_E = "Hardness";

                }
			} else {
				KOUMOKU_J = Tmp_KDB1.KOUMOKU_J;
				KOUMOKU_E = Tmp_KDB1.KOUMOKU_E;
            }

		    //コンミ＆抵抗率の場合 2002/12/03 E.Takase
		    if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {
                tmpSOKUTEI_SU1 = Tmp_KDB1.HIST_SOKUT_Ori*2;
                tmpSOKUTEI_SU2 = Tmp_KDB1.HIST_SOKUT*2;
                tmpSOKUTEI_SU3 = Tmp_KDB1.SOKUTE_SU*2;
                tmpSOKUTEI_SU4 = Tmp_KDB1.SOKUTE_SU_Ori*2;
		    //コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
            } else {
                tmpSOKUTEI_SU1 = Tmp_KDB1.HIST_SOKUT_Ori;
                tmpSOKUTEI_SU2 = Tmp_KDB1.HIST_SOKUT;
                tmpSOKUTEI_SU3 = Tmp_KDB1.SOKUTE_SU;
                tmpSOKUTEI_SU4 = Tmp_KDB1.SOKUTE_SU_Ori;
            }
            //工程能力測定データ１ 規格の真ん中の値 +-？
            fprintf(stream,"%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                Tmp_KDB1.TANI.c_str(),
                KOUMOKU_J.c_str(),
                KOUMOKU_E.c_str(),
				tmpSOKUTEI_SU1,
				tmpSOKUTEI_SU2,
				Tmp_KDB1.HIST_KIKAK,
				Tmp_KDB1.HIST_MIN,
				Tmp_KDB1.HIST_MAX,
				tmpSOKUTEI_SU3,
				tmpSOKUTEI_SU4,
				KETA.SOKUTE_AVE,
				KETA.SOKUTE_MIN,
				KETA.SOKUTE_MAX,
				KETA.SOKUTE_R,
				KETA.SOKUTE_SGM,
				KETA.SOKUTE_CP,
				KETA.SOKUTE_CPK,
				KETA.SOKUTE_K,
				KETA.SOKUTE_P
                    );
            ////工程能力測定データ１ 規格の真ん中の値 +-？
            //fprintf(stream,"%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
            //    Tmp_KDB1.TANI.c_str(),
            //    KOUMOKU_J.c_str(),
            //    KOUMOKU_E.c_str(),
			//	Tmp_KDB1.HIST_SOKUT_Ori,
			//	Tmp_KDB1.HIST_SOKUT,
			//	Tmp_KDB1.HIST_KIKAK,
			//	Tmp_KDB1.HIST_MIN,
			//	Tmp_KDB1.HIST_MAX,
			//	Tmp_KDB1.SOKUTE_SU,
			//	Tmp_KDB1.SOKUTE_SU_Ori,
			//	KETA.SOKUTE_AVE,
			//	KETA.SOKUTE_MIN,
			//	KETA.SOKUTE_MAX,
			//	KETA.SOKUTE_R,
			//	KETA.SOKUTE_SGM,
			//	KETA.SOKUTE_CP,
			//	KETA.SOKUTE_CPK,
			//	KETA.SOKUTE_K,
			//	KETA.SOKUTE_P
            //        );
            //以上、未満、個数
            for ( i = 0; i < 20; i++ ) {
                fprintf(stream,"%lf,%lf,%lf\n",E_Screen_Data[0][i],E_Screen_Data[1][i],E_Screen_Data[2][i]);
            }

            //桁数指定（フォーマット）
            fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				KETA.AVE_str.c_str(),
				KETA.MIN_str.c_str(),
				KETA.MAX_str.c_str(),
				KETA.R_str.c_str(),
				KETA.SGM_str.c_str(),
				KETA.CP_str.c_str(),
				KETA.CPK_str.c_str(),
				KETA.K_str.c_str(),
				KETA.P_str.c_str()
                    );

        }
        // ファイルを閉じる
        fclose(stream);

        //data3
        // ファイルを更新用に開く
        strcpy(path,CDPath);
        strcat(path, "\\data3.csv");
        if( (stream = fopen( path, "w+" )) != NULL ){	//正常にﾌｧｲﾙをｵｰﾌﾟﾝできた場合
            //タイトル 工程能力測定データ１
            //ファイルオープン フラグ
            fprintf(stream,"1\n");
            //項目数 SEQNOMAX
            fprintf(stream,"%d\n",SGr1->RowCount-1);

            //桁数指定（フォーマット）
            fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				KETA.AVE_str.c_str(),
				KETA.MIN_str.c_str(),
				KETA.MAX_str.c_str(),
				KETA.R_str.c_str(),
				KETA.SGM_str.c_str(),
				KETA.CP_str.c_str(),
				KETA.CPK_str.c_str(),
				KETA.K_str.c_str(),
				KETA.P_str.c_str()
                    );



            //作成日 得意先品番 ロットNO 材質コード 材質名
            fprintf(stream,"%s,%s,%s,%s,%s,%d\n",
				    Form1->DelSEPA( Form1->EdtYMD->Text).c_str(),
                    Form1->EdtHIN->Text.c_str(),
                    Form1->EdtLOT->Text.c_str(),
                    Form1->EdtZIS->Text.c_str(),
                    Form1->EdtZISNAM->Caption.c_str(),
                    Tmp_E_Scale
                        );
            // ファイルを閉じる
            fclose(stream);
            return(true);
        } else {  //ﾌｧｲﾙのｵｰﾌﾟﾝに失敗した場合
		    fclose(stream);
		    return(false);
        }

 	}else{	//ﾌｧｲﾙのｵｰﾌﾟﾝに失敗した場合
		fclose(stream);
		return(false);
	}

}
//---------------------------------------------------------------------------
//Excel２（工程能力調査表） 起動
bool __fastcall TForm1::Excel2_Write()
{
/*
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\工程能力調査表.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);
*/
/*
    AnsiString FilePath;

    FilePath = CDPath;
    FilePath += "\\工程能力調査表.xls";

    // アプリケーションを実行して終了を待つ
    STARTUPINFO SupInf;
    PROCESS_INFORMATION PrcsInf;

    ::GetStartupInfo(&SupInf);
    SupInf.cb = sizeof(SupInf);
    SupInf.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
    SupInf.wShowWindow = SW_SHOW;

    bool Fin = CreateProcess( FilePath.c_str(), NULL, NULL, NULL, false,
                         NORMAL_PRIORITY_CLASS, NULL, NULL, &SupInf, &PrcsInf );
    if( Fin == true ){
         WaitForSingleObject( PrcsInf.hProcess, INFINITE );
    }
*/


    STARTUPINFO stup;
    PROCESS_INFORMATION pinf;

    stup.cb=sizeof(STARTUPINFO);
    stup.lpReserved=NULL;
    stup.lpDesktop=NULL;
    stup.lpTitle=NULL;
    stup.dwFlags=STARTF_USESHOWWINDOW;
    stup.cbReserved2=0;
    stup.lpReserved2=NULL;
    stup.wShowWindow=SW_SHOW;


    char cmdline[1028];
    strcpy(path,CDPath);
    strcat(path, "\\工程能力調査表.xls");
    wsprintf(cmdline,"\"%s\" \"%s\"",  ExcelExePATH,path);

    BOOL flag=::CreateProcess(NULL,cmdline,NULL,NULL,0,0,NULL,NULL,&stup,&pinf);

    if( flag == true ){
         WaitForSingleObject( pinf.hProcess, INFINITE );
    }


    return(true);
    return(true);


}

//---------------------------------------------------------------------------
//ＣＳＶ（工程能力測定）データ作成
bool __fastcall TForm3::CSV_Write(int flag)
{
    AnsiString sBuf;
    int i;
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    AnsiString KOUMOKU_J;
    AnsiString KOUMOKU_E;
    FILE *stream;
    int tmpSOKUTEI_SU1;
    int tmpSOKUTEI_SU2;
    int tmpSOKUTEI_SU3;
    int tmpSOKUTEI_SU4;

    //担当者の取得
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    //問い合せ文実行
    //ソート昇順 得意先ｺｰﾄﾞ、検査予定日、トレーNo、サンプルポジション
    sBuf = "SELECT ";
    sBuf += "TANNAM  FROM SM12S ";
    sBuf += "WHERE  TANSYA = '" + IntToStr(Cur_Kdb1.UPDCHR) + "'" ;
    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    if( Form1->Query1->Bof == true && Form1->Query1->Eof == true){
        TANNAM = USER_NAM;
    } else {
        Form1->Query1->First();
        TANNAM = Form1->Query1->FieldValues["TANNAM"];
    }

    //カレントディレクトリの取得
    strcpy(CDPath, "X:\\");	/* 値を返す形式: X:\ で文字列を満たす */
    CDPath[0] = 'A' + getdisk();	/* X を現在のドライブ名に置き換える */
    getcurdir(0, CDPath+3);	/* 文字列部分の残りにカレントディレクトリを追加 */

    //桁数指定（フォーマット）を求める
	KETA.AVE_str = ConvKETA1( KETA.AVE,KETA.SOKUTE_AVE );
	KETA.MIN_str = ConvKETA1( KETA.MIN,KETA.SOKUTE_MIN );
	KETA.MAX_str = ConvKETA1( KETA.MAX,KETA.SOKUTE_MAX );
	KETA.R_str   = ConvKETA1( KETA.R  ,KETA.SOKUTE_R   );
	KETA.SGM_str = ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
	KETA.CP_str  = ConvKETA1( KETA.CP ,KETA.SOKUTE_CP  );
	KETA.K_str   = ConvKETA2( KETA.K  ,KETA.SOKUTE_K ,2  );
	KETA.CPK_str = ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	KETA.P_str   = ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );
	//KETA.KMK_str = KENSASYOSIKI_Set(Cur_Kdb1.KENSA_KMK,Cur_Kdb1.JYOKEN1);
	KETA.KMK_str = ConvKETA1( Edt_001->FPos,0.00);


	//測定項目
	if( Cur_Kdb1.KENSA_KMK == 6 ) {
		KOUMOKU_J = "硬度";
		KOUMOKU_E = "Hardness";
	} else {
		//コンミ＆抵抗率の場合 2002/12/03 E.Takase
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
            if ( flag == 0 ) {
		        KOUMOKU_J = Cur_Kdb1.KOUMOKU_J + "-L";
		        KOUMOKU_E = Cur_Kdb1.KOUMOKU_E + "-L";
            } else {
		        KOUMOKU_J = Cur_Kdb1.KOUMOKU_J + "-R";
		        KOUMOKU_E = Cur_Kdb1.KOUMOKU_E + "-R";
            }
        } else {
		    KOUMOKU_J = Cur_Kdb1.KOUMOKU_J;
		    KOUMOKU_E = Cur_Kdb1.KOUMOKU_E;
        }
    }

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\data.csv");
    if( (stream = fopen( path, "w+" )) != NULL ){	//正常にﾌｧｲﾙをｵｰﾌﾟﾝできた場合
        //ファイルオープン フラグ
        fprintf(stream,"1\n");
        //グラフ目盛りのスケール 担当者名
        fprintf(stream,"%d,%s\n",E_Scale,TANNAM.c_str());
        //以上、未満、個数
        for ( i = 0; i < 20; i++ ) {
            fprintf(stream,"%lf,%lf,%lf\n",E_Screen_Data[0][i],E_Screen_Data[1][i],E_Screen_Data[2][i]);
        }
        //桁数指定（フォーマット）
        fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				KETA.AVE_str.c_str(),
				KETA.MIN_str.c_str(),
				KETA.MAX_str.c_str(),
				KETA.R_str.c_str(),
				KETA.SGM_str.c_str(),
				KETA.CP_str.c_str(),
				KETA.CPK_str.c_str(),
				KETA.K_str.c_str(),
				KETA.P_str.c_str(),
				KETA.KMK_str.c_str()
                    );


        ///2003.02.13 E.Takase コメントにした
        ////工程能力測定データ１
		////コンミ＆抵抗率の場合 2002/12/03 E.Takase
		//if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
        //    tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori*2;
        //    tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT*2;
        //    tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU*2;
        //    tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori*2;
		////コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
        //} else {
        //    tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori;
        //    tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT;
        //    tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU;
        //    tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori;
        //}
        tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori;
        tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT;
        tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU;
        tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori;
        fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
				Cur_Kdb1.TANI.c_str(),
				Cur_Kdb1.KENSA_YMD.c_str(),
				Cur_Kdb1.DTKSHIN.c_str(),
				Cur_Kdb1.LOTNO.c_str(),
				Cur_Kdb1.ZISCOD.c_str(),
				Cur_Kdb1.ZISNAM.c_str(),
                KOUMOKU_J.c_str(),
                KOUMOKU_E.c_str(),
				tmpSOKUTEI_SU1,
				tmpSOKUTEI_SU2,
				Cur_Kdb1.HIST_KIKAK,
				Cur_Kdb1.HIST_MIN,
				Cur_Kdb1.HIST_MAX,
				tmpSOKUTEI_SU3,
				tmpSOKUTEI_SU4,
				KETA.SOKUTE_AVE,
				KETA.SOKUTE_MIN,
				KETA.SOKUTE_MAX,
				KETA.SOKUTE_R,
				KETA.SOKUTE_SGM,
				KETA.SOKUTE_CP,
				KETA.SOKUTE_CPK,
				KETA.SOKUTE_K,
				KETA.SOKUTE_P
                    );
        //fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
		//		Cur_Kdb1.TANI.c_str(),
		//		Cur_Kdb1.KENSA_YMD.c_str(),
		//		Cur_Kdb1.DTKSHIN.c_str(),
		//		Cur_Kdb1.LOTNO.c_str(),
		//		Cur_Kdb1.ZISCOD.c_str(),
		//		Cur_Kdb1.ZISNAM.c_str(),
        //        KOUMOKU_J.c_str(),
        //        KOUMOKU_E.c_str(),
		//		Cur_Kdb1.HIST_SOKUT_Ori,
		//		Cur_Kdb1.HIST_SOKUT,
		//		Cur_Kdb1.HIST_KIKAK,
		//		Cur_Kdb1.HIST_MIN,
		//		Cur_Kdb1.HIST_MAX,
		//		Cur_Kdb1.SOKUTE_SU,
		//		Cur_Kdb1.SOKUTE_SU_Ori,
		//		KETA.SOKUTE_AVE,
		//		KETA.SOKUTE_MIN,
		//		KETA.SOKUTE_MAX,
		//		KETA.SOKUTE_R,
		//		KETA.SOKUTE_SGM,
		//		KETA.SOKUTE_CP,
		//		KETA.SOKUTE_CPK,
		//		KETA.SOKUTE_K,
		//		KETA.SOKUTE_P
        //            );
        //工程能力測定データ２
		//コンミ＆抵抗率の場合 2002/12/03 E.Takase
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
            //2003.02.13 E.Takase
            //for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
            //   fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
            //   fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
            //}
            if ( flag == 0 ) {
                for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                    fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
                    //fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
                }
            } else {
                for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                    //fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
                    fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
                }
            }
		//コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
        } else {
            for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_CH);
            }
        }
        // ファイルを閉じる
        fclose(stream);
	    return(true);
 	}else{	//ﾌｧｲﾙのｵｰﾌﾟﾝに失敗した場合
		fclose(stream);
		return(false);
	}

}

//---------------------------------------------------------------------------
//Excel（工程能力測定） 起動
bool __fastcall TForm3::Excel_Write()
{
/*
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\工程能力測定.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);

*/

/*
    AnsiString FilePath;

    FilePath = CDPath;
    FilePath += "\\工程能力測定.xls";
    //FilePath = "G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE";


    // ファイルを更新用に開く
    //strcpy(path,"\"G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE\"");
    //strcat(path,CDPath);
    //strcat(path, "\\工程能力測定.xls");

    strcpy(path,"'G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE'");

    // アプリケーションを実行して終了を待つ
    STARTUPINFO SupInf;
    PROCESS_INFORMATION PrcsInf;

    ::GetStartupInfo(&SupInf);
    SupInf.cb = sizeof(SupInf);
    SupInf.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
    SupInf.wShowWindow = SW_SHOW;

    bool Fin = CreateProcess( path, NULL, NULL, NULL, false,
                         NORMAL_PRIORITY_CLASS, NULL, NULL, &SupInf, &PrcsInf );
    if( Fin == true ){
         WaitForSingleObject( PrcsInf.hProcess, INFINITE );
    }
*/

    STARTUPINFO stup;
    PROCESS_INFORMATION pinf;

    stup.cb=sizeof(STARTUPINFO);
    stup.lpReserved=NULL;
    stup.lpDesktop=NULL;
    stup.lpTitle=NULL;
    stup.dwFlags=STARTF_USESHOWWINDOW;
    stup.cbReserved2=0;
    stup.lpReserved2=NULL;
    stup.wShowWindow=SW_SHOW;


    char cmdline[1028];
    strcpy(path,CDPath);
    strcat(path, "\\工程能力測定.xls");
    wsprintf(cmdline,"\"%s\" \"%s\"",  Form1->ExcelExePATH,path);

    BOOL flag=::CreateProcess(NULL,cmdline,NULL,NULL,0,0,NULL,NULL,&stup,&pinf);

    if( flag == true ){
         WaitForSingleObject( pinf.hProcess, INFINITE );
    }


    return(true);
}

//---------------------------------------------------------------------------
//SGr1のpos行目の測定データを Tmp_KDB1に代入
void __fastcall TForm1::Sub_Tmp_KDB1(int pos)
{
    AnsiString sBuf;
    int i,T_No;

	Tmp_KDB1.No				= 0;        // 選択番号
	Tmp_KDB1.KENSA_YMD		= "";		//	検査年月日
	Tmp_KDB1.DTKSHIN		= ""; 		//	得意先品番
	Tmp_KDB1.HINBAN			= "";		//	自社品番
	Tmp_KDB1.ZISCOD			= "";		//	材質コード
	Tmp_KDB1.ZISNAM			= "";		//	材質名
	Tmp_KDB1.LOTNO			= "";		//	ロットNO
	Tmp_KDB1.SEQNO			= 0;		//	SEQ-NO
	Tmp_KDB1.KENSA_KMK		= 0;		//	検査項目
	Tmp_KDB1.KOUMOKU_J		= "";		//	検査項目名（日本語）
	Tmp_KDB1.KOUMOKU_E		= "";		//	検査項目名（English）
	Tmp_KDB1.HIST_SOKUT		= 0;		//	工程能力 測定数
	Tmp_KDB1.HIST_SOKUT_Ori	= 0;	    //	工程能力 測定数
	Tmp_KDB1.HIST_KIKAK		= 0;		//	工程能力 規格
	Tmp_KDB1.HIST_MIN		= 0;		//	工程能力 下限規格
	Tmp_KDB1.HIST_MAX		= 0;		//	工程能力 上限規格
	Tmp_KDB1.SOKUTE_SU		= 0;		//	測定数
	Tmp_KDB1.SOKUTE_SU_Ori	= 0;	    //	測定数
	Tmp_KDB1.SOKUTE_KET		= 0;        //      有効桁数：２：2桁、３：3桁
	Tmp_KDB1.SOKUTE_AVE		= 0;		//	平均値
	Tmp_KDB1.SOKUTE_MIN		= 0;		//	ＭＩＮ
	Tmp_KDB1.SOKUTE_MAX		= 0;		//	ＭＡＸ
	Tmp_KDB1.SOKUTE_R		= 0;		//	Ｒ
	Tmp_KDB1.SOKUTE_SGM		= 0;		//	標準偏差
	Tmp_KDB1.SOKUTE_CP		= 0;		//	ＣＰ
	Tmp_KDB1.SOKUTE_CPK		= 0;		//	ＣＰＫ
	Tmp_KDB1.SOKUTE_K		= 0;		//	Ｋ
	Tmp_KDB1.SOKUTE_P		= 0;		//	不良率
	Tmp_KDB1.JYOKEN1		= 0;		//	測定条件１
	Tmp_KDB1.JYOKEN2		= 0;		//	　〃　　２
	Tmp_KDB1.ADDYMD			= "";		//	登録日
	Tmp_KDB1.ADDTIM			= "";		//	登録時間
	Tmp_KDB1.UPDYMD			= "";		//	変更日
	Tmp_KDB1.UPDTIM			= "";		//	変更時間
	Tmp_KDB1.UPDCHR			= 0;		//	更新者
	Tmp_KDB1.UPDCNT			= 0;		//	更新回数
	Tmp_KDB1.TANI			= "";		//	単位

    //2002/12/03 E.Takase
	Tmp_KDB1.KEIJKBN	    = 0;		//	形状区分

     Tmp_KDB1.KENSA_YMD = Form1->DelSEPA( EdtYMD->Text);
     Tmp_KDB1.DTKSHIN = EdtHIN->Text;
     Tmp_KDB1.LOTNO = EdtLOT->Text;
     Tmp_KDB1.SEQNO = StrToInt(SGr1->Cells[17][pos]);
     Tmp_KDB1.No = pos + 1;


     // Read Data Base (KdB1)
     //データベース Query 初期化
     Query_Kdb1->Close();
     Query_Kdb1->SQL->Clear();

     //問い合せ文実行
     //検査予定日、トレーNo
     sBuf = "SELECT ";
     sBuf += "* ";
     sBuf += "FROM KDB1 ";
     sBuf += "WHERE KENSA_YMD = '" + Tmp_KDB1.KENSA_YMD + "' " ;
     sBuf +=  " AND SEQNO = " + IntToStr(Tmp_KDB1.SEQNO);
	 sBuf += " AND DTKSHIN = '" + Tmp_KDB1.DTKSHIN	 + "'";
	 sBuf += " AND LOTNO = '" + Tmp_KDB1.LOTNO + "'";
         sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加
     sBuf += " ORDER BY KENSA_YMD,DTKSHIN,LOTNO, SEQNO";

     Query_Kdb1->SQL->Add(sBuf);
     Query_Kdb1->Open();
     Query_Kdb1->Active = true;

     if ( Query_Kdb1->RecordCount > 0 ) {
        Query_Kdb1->First();

        if ( Query_Kdb1->FieldValues["DTKSHIN"].IsNull())
           Tmp_KDB1.DTKSHIN = " ";
        else
           Tmp_KDB1.DTKSHIN = Query_Kdb1->FieldValues["DTKSHIN"];

        if ( Query_Kdb1->FieldValues["HINBAN"].IsNull())
           Tmp_KDB1.HINBAN = " ";
        else
           Tmp_KDB1.HINBAN = Query_Kdb1->FieldValues["HINBAN"];

        if ( Query_Kdb1->FieldValues["ZISCOD"].IsNull())
           Tmp_KDB1.ZISCOD = " ";
        else
           Tmp_KDB1.ZISCOD = Query_Kdb1->FieldValues["ZISCOD"];

        if ( Query_Kdb1->FieldValues["ZISNAM"].IsNull())
           Tmp_KDB1.ZISNAM = " ";
        else
           Tmp_KDB1.ZISNAM = Query_Kdb1->FieldValues["ZISNAM"];

        if ( Query_Kdb1->FieldValues["LOTNO"].IsNull())
           Tmp_KDB1.LOTNO = " ";
        else
           Tmp_KDB1.LOTNO = Query_Kdb1->FieldValues["LOTNO"];

        if ( Query_Kdb1->FieldValues["KENSA_KMK"].IsNull())
           Tmp_KDB1.KENSA_KMK = 0;
        else
           Tmp_KDB1.KENSA_KMK = Query_Kdb1->FieldValues["KENSA_KMK"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_J"].IsNull())
           Tmp_KDB1.KOUMOKU_J = " ";
        else
           Tmp_KDB1.KOUMOKU_J = Query_Kdb1->FieldValues["KOUMOKU_J"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_E"].IsNull())
           Tmp_KDB1.KOUMOKU_E = " ";
        else
           Tmp_KDB1.KOUMOKU_E = Query_Kdb1->FieldValues["KOUMOKU_E"];

        if ( Query_Kdb1->FieldValues["HIST_SOKUT"].IsNull())
           Tmp_KDB1.HIST_SOKUT = 0;
        else
           Tmp_KDB1.HIST_SOKUT = Query_Kdb1->FieldValues["HIST_SOKUT"];
        Tmp_KDB1.HIST_SOKUT_Ori = Tmp_KDB1.HIST_SOKUT;

        if ( Query_Kdb1->FieldValues["HIST_KIKAK"].IsNull())
           Tmp_KDB1.HIST_KIKAK = 0;
        else
           Tmp_KDB1.HIST_KIKAK = Query_Kdb1->FieldValues["HIST_KIKAK"];

        if ( Query_Kdb1->FieldValues["HIST_MIN"].IsNull())
           Tmp_KDB1.HIST_MIN = 0;
        else
           Tmp_KDB1.HIST_MIN = Query_Kdb1->FieldValues["HIST_MIN"];

        if ( Query_Kdb1->FieldValues["HIST_MAX"].IsNull())
           Tmp_KDB1.HIST_MAX = 0;
        else
           Tmp_KDB1.HIST_MAX = Query_Kdb1->FieldValues["HIST_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SU"].IsNull())
           Tmp_KDB1.SOKUTE_SU = 0;
        else
           Tmp_KDB1.SOKUTE_SU = Query_Kdb1->FieldValues["SOKUTE_SU"];
        Tmp_KDB1.SOKUTE_SU_Ori = Tmp_KDB1.SOKUTE_SU;

        if ( Query_Kdb1->FieldValues["SOKUTE_AVE"].IsNull())
           Tmp_KDB1.SOKUTE_AVE = 0;
        else
           Tmp_KDB1.SOKUTE_AVE = Query_Kdb1->FieldValues["SOKUTE_AVE"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MIN"].IsNull())
           Tmp_KDB1.SOKUTE_MIN = 0;
        else
           Tmp_KDB1.SOKUTE_MIN = Query_Kdb1->FieldValues["SOKUTE_MIN"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MAX"].IsNull())
           Tmp_KDB1.SOKUTE_MAX = 0;
        else
           Tmp_KDB1.SOKUTE_MAX = Query_Kdb1->FieldValues["SOKUTE_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_R"].IsNull())
           Tmp_KDB1.SOKUTE_R = 0;
        else
           Tmp_KDB1.SOKUTE_R = Query_Kdb1->FieldValues["SOKUTE_R"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SGM"].IsNull())
           Tmp_KDB1.SOKUTE_SGM = 0;
        else
           Tmp_KDB1.SOKUTE_SGM = Query_Kdb1->FieldValues["SOKUTE_SGM"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CP"].IsNull())
           Tmp_KDB1.SOKUTE_CP = 0;
        else
           Tmp_KDB1.SOKUTE_CP = Query_Kdb1->FieldValues["SOKUTE_CP"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CPK"].IsNull())
           Tmp_KDB1.SOKUTE_CPK = 0;
        else
           Tmp_KDB1.SOKUTE_CPK = Query_Kdb1->FieldValues["SOKUTE_CPK"];

        if ( Query_Kdb1->FieldValues["SOKUTE_K"].IsNull())
           Tmp_KDB1.SOKUTE_K = 0;
        else
           Tmp_KDB1.SOKUTE_K = Query_Kdb1->FieldValues["SOKUTE_K"];

        if ( Query_Kdb1->FieldValues["SOKUTE_P"].IsNull())
           Tmp_KDB1.SOKUTE_P = 0;
        else
           Tmp_KDB1.SOKUTE_P = Query_Kdb1->FieldValues["SOKUTE_P"];

        if ( Query_Kdb1->FieldValues["JYOKEN1"].IsNull())
           Tmp_KDB1.JYOKEN1 = 0;
        else
           Tmp_KDB1.JYOKEN1 = Query_Kdb1->FieldValues["JYOKEN1"];

        if ( Query_Kdb1->FieldValues["JYOKEN2"].IsNull())
           Tmp_KDB1.JYOKEN2 = 0;
        else
           Tmp_KDB1.JYOKEN2 = Query_Kdb1->FieldValues["JYOKEN2"];

        if ( Query_Kdb1->FieldValues["UPDCNT"].IsNull())
           Tmp_KDB1.UPDCNT = 0;
        else
           Tmp_KDB1.UPDCNT = Query_Kdb1->FieldValues["UPDCNT"];

        if ( Query_Kdb1->FieldValues["TANI"].IsNull())
           Tmp_KDB1.TANI = "";
        else
           Tmp_KDB1.TANI = Query_Kdb1->FieldValues["TANI"];

        if ( Query_Kdb1->FieldValues["SOKUTE_KET"].IsNull())
           Tmp_KDB1.SOKUTE_KET = 0;
        else
           Tmp_KDB1.SOKUTE_KET = Query_Kdb1->FieldValues["SOKUTE_KET"];

        //2002/12/03 E.Takase
        if ( Query_Kdb1->FieldValues["KEIJKBN"].IsNull())
           Tmp_KDB1.KEIJKBN = 0;
        else
           Tmp_KDB1.KEIJKBN = Query_Kdb1->FieldValues["KEIJKBN"];



      } else {
        Query_Kdb1->Close();
        return ;
      }

     Query_Kdb1->Close();


     for ( i = 0; i < Nums; i++) {
        M_Kdb2[i].SOKUTEI_CH = 0;
        M_Kdb2[i].SOKUTEI_MEI1 = 0;
        M_Kdb2[i].SOKUTEI_MEI2 = 0;
        M_Kdb2[i].SOKUTEI_MEI3 = 0;
        M_Kdb2[i].SOKUTEI_MEI4 = 0;
        M_Kdb2[i].SOKUTEI_MEI5 = 0;
        M_Kdb2[i].SOKUTEI_MEI6 = 0;
        M_Kdb2[i].SOKUTEI_MEI7 = 0;
        M_Kdb2[i].DatabaseFlag = 0;
     }

     // Read Data Base (Kdb2)
     //データベース Query 初期化
     Query_Kdb2->Close();
     Query_Kdb2->SQL->Clear();

     //問い合せ文実行
     //検査予定日、トレーNo
     sBuf = "SELECT ";
     sBuf += "SOKUTEI_NO, SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, ";
     sBuf += "SOKUTEI_MEI4, SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7 ";
     sBuf += "FROM KDB2 ";
     sBuf += "WHERE KENSA_YMD = '" + Tmp_KDB1.KENSA_YMD + "' ";
     sBuf +=  " AND SEQNO = " + IntToStr(Tmp_KDB1.SEQNO);
	 sBuf += " AND DTKSHIN = '" + Tmp_KDB1.DTKSHIN	 + "'";
	 sBuf += " AND LOTNO = '" + Tmp_KDB1.LOTNO + "'";
         sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_工場区分追加
     sBuf += " ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

     Query_Kdb2->SQL->Add(sBuf);
     Query_Kdb2->Open();
     Query_Kdb2->Active = true;

     if ( Query_Kdb2->RecordCount > 0 ) {
        Query_Kdb2->First();
        while( !Query_Kdb2->Eof ) {
           if ( Query_Kdb2->FieldValues["SOKUTEI_NO"].IsNull()) {
              T_No = 0;
           } else {
              T_No = Query_Kdb2->FieldValues["SOKUTEI_NO"];
           }

           if (T_No > 0) {
              M_Kdb2[T_No - 1].DatabaseFlag = 1;
              if ( Query_Kdb2->FieldValues["SOKUTEI_CH"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_CH = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_CH = Query_Kdb2->FieldValues["SOKUTEI_CH"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI1"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI1 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI1 = Query_Kdb2->FieldValues["SOKUTEI_MEI1"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI2"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI2 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI2 = Query_Kdb2->FieldValues["SOKUTEI_MEI2"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI3"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI3 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI3 = Query_Kdb2->FieldValues["SOKUTEI_MEI3"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI4"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI4 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI4 = Query_Kdb2->FieldValues["SOKUTEI_MEI4"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI5"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI5 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI5 = Query_Kdb2->FieldValues["SOKUTEI_MEI5"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI6"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI6 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI6 = Query_Kdb2->FieldValues["SOKUTEI_MEI6"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI7"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI7 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI7 = Query_Kdb2->FieldValues["SOKUTEI_MEI7"];
           }
           Query_Kdb2->Next();
        }
     }

     Query_Kdb2->Close();

}
//---------------------------------------------------------------------------
// 統計とグラフ表示
void __fastcall TForm1::Toukei_Tmp_KDB1(int k)
{
 int MaxNo;     // 最大個数
 int T_Scale;
 AnsiString string;

 int i, j;
 char s_str[64];
 double T_double, T_High, T_Low, T_double1, T_double2;
 int N_Mid, N_High, N_Low, n1, n2, T_index;
 int SubFlag = 0;

 if (Tmp_KDB1.HIST_MAX < Tmp_KDB1.HIST_MIN && Tmp_KDB1.HIST_KIKAK == 1) {
    T_double = Tmp_KDB1.HIST_MIN;
    Tmp_KDB1.HIST_MIN = Tmp_KDB1.HIST_MAX;
    Tmp_KDB1.HIST_MAX = T_double;
 }

 // Y軸のScale 計算
 if (Tmp_KDB1.HIST_KIKAK == 1) { // 両側チェックケース
    //T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
    T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/16;   // 2000.5.22 修正
    for (i = 18; i >= 0; i--) {
        //if (E_Standard_Scale[i] > T_double) {
        if (E_Standard_Scale[i] >= T_double) {  // 2000.5.22  修正
           T_double = E_Standard_Scale[i];
           i = -1;
        }
    }

    // 2000.3.6 N_Mid <= 7なると、N_Mid倍にする
    if (Tmp_KDB1.KOUMOKU_J == "ブラシ厚さ") {  // ブラシ厚さのみを対象する
        T_double1 = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/T_double;
        N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
        if (N_Mid <= 7) {
            N_Mid = N_Mid * 2;
            T_double = T_double / 2;
        }
    }

    // 2000.5.9 表示桁数によって、pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (k == 0 && T_double < 1)
       T_double = 1;
    if (k == 1 && T_double < 0.1)
       T_double = 0.1;
    if (k == 2 && T_double < 0.01)
       T_double = 0.01;
    if (k == 3 && T_double < 0.001)
       T_double = 0.001;
    // end of add 2000.5.9

    // 下限チェック
    T_double1 = Tmp_KDB1.HIST_MIN/T_double;
    n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
    //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
    if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
       T_Low = Tmp_KDB1.HIST_MIN;
       n1 = 0;
    } else {
       T_Low = (double)(n1+1) * T_double;
       n1 = 1;
    }

    // 上限チェック
    //n2 = Cur_Kda1.HIST_MAX/T_double;
    T_double1 = Tmp_KDB1.HIST_MAX/T_double;
    n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
    if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
       T_High = Tmp_KDB1.HIST_MAX;
       n2 = 0;
    } else {
       T_High = (double)n2 * T_double;
       n2 = 1;
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[1][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = Tmp_KDB1.HIST_MAX + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 } else { // 片側チェック
    //T_index = 12;
    // 2000.5.9 表示桁数によって、default pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (k == 0)
       T_index = 7;
    if (k == 1)
       T_index = 10;
    if (k == 2)
       T_index = 13;
    if (k == 3)
       T_index = 16;
    // end of add 2000.5.9
Again1:
    if (T_index >= 20) {   //2000.11.17追加
       MessageDlg( "規格を拡大して下さい（T_indexは20を超える）", mtConfirmation, mbYesNoCancel, 0);
    }

    T_double = E_Standard_Scale[T_index];    // default pitch;

    if (Tmp_KDB1.SOKUTE_SU > 1) {      // 収録データがあり
        //コンミ＆抵抗率の場合 2002/12/03 E.Takase
        if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {

            T_double2 = M_Kdb2[0].SOKUTEI_MEI3;
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //最大値を探す
                    if (M_Kdb2[i].SOKUTEI_MEI3 > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
                } else { // 最小値を探す
                    if (M_Kdb2[i].SOKUTEI_MEI3 < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
                }
            }
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //最大値を探す
                    if (M_Kdb2[i].SOKUTEI_MEI5 > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
                } else { // 最小値を探す
                    if (M_Kdb2[i].SOKUTEI_MEI5 < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
                }
            }

        //コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
        } else {
            T_double2 = M_Kdb2[0].SOKUTEI_CH;
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //最大値を探す
                    if (M_Kdb2[i].SOKUTEI_CH > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_CH;
                } else { // 最小値を探す
                    if (M_Kdb2[i].SOKUTEI_CH < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_CH;
                }
            }

        }

       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // 下限チェック
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;

          if (T_double2 > T_Low + 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   T_index--;
                   SubFlag = 1;
                   goto Again1;
                }
             }
          }

/*        2000.5.9 delete
          if (T_double2 < T_Low + 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }
*/
          n2 = 0;
       } else {
          // 上限チェック
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;

          if (T_Low < 0)
             T_Low = 0;

          if (T_double2 < T_High - 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   SubFlag = 1;
                   T_index--;
                   goto Again1;
                }
             }
          }
/*        2000.5.9 delete
          if (T_double2 > T_High - 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }
*/
          n1 = 0;
       }
    } else { // 収録データなし
       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // 下限チェック
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;
          n2 = 0;
       } else {
          // 上限チェック
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;
          // 2000.11.17追加 T_Lowをチェックする。＜０場合はピーチを小さくする
          if (T_Low < 0) {
             T_index++;
             goto Again1;
          }
          n1 = 0;
       }
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);

    if (N_Mid <= 7 && Tmp_KDB1.KOUMOKU_J == "ブラシ厚さ") { // スケール小さいすぎ、倍にする 2000.3.6
       T_double = T_double / 2;
       if (n1 > 0) {
          if (fabs(T_Low - (Tmp_KDB1.HIST_MIN - T_double)) <= COM_DIFF) {
             n1 = 0;
             T_Low = Tmp_KDB1.HIST_MIN;
          }
       }
       if (n2 > 0) {
          if (fabs(T_High - Tmp_KDB1.HIST_MAX - T_double) <= COM_DIFF) {
             n2 = 0;
             T_High = Tmp_KDB1.HIST_MAX;
          }
       }
       T_double1 = (T_High - T_Low)/T_double;
       N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    }


    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    if (T_High - (N_Mid + N_Low) * T_double < 0)
       N_Low = (int)(T_High / T_double) - N_Mid;

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = T_High;
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = T_High + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 }

 // 個数（E_Screen_Data[2][]）初期化
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

	// 個数 Counter
	if (Tmp_KDB1.SOKUTE_SU > 0) {
		//コンミ＆抵抗率の場合 2002/12/03 E.Takase
		if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {
			//電圧 左
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI3 < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
			//電圧 左
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI5 < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
		//コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
		} else {
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
		}
	}


 // 最大個数を求める
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // スケールを求める
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;




/*2000/05/09
 if (Tmp_KDB1.HIST_MAX < Tmp_KDB1.HIST_MIN && Tmp_KDB1.HIST_KIKAK == 1) {
    T_double = Tmp_KDB1.HIST_MIN;
    Tmp_KDB1.HIST_MIN = Tmp_KDB1.HIST_MAX;
    Tmp_KDB1.HIST_MAX = T_double;
 }

 // Y軸のScale 計算
 if (Tmp_KDB1.HIST_KIKAK == 1) { // 両側チェックケース
    T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
    for (i = 18; i >= 0; i--) {
        if (E_Standard_Scale[i] > T_double) {
           T_double = E_Standard_Scale[i];
           i = -1;
        }
    }

    // 2000.3.6 N_Mid <= 7なると、N_Mid倍にする
    if (Tmp_KDB1.KOUMOKU_J == "ブラシ厚さ") {  // ブラシ厚さのみを対象する
        T_double1 = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/T_double;
        N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
        if (N_Mid <= 7) {
            N_Mid = N_Mid * 2;
            T_double = T_double / 2;
        }
    }

    // 2000.5.9 表示桁数によって、pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (KETA.SOKUTE_MIN == 0 && T_double < 1)
       T_double = 1;
    if (KETA.SOKUTE_MIN == 1 && T_double < 0.1)
       T_double = 0.1;
    if (KETA.SOKUTE_MIN == 2 && T_double < 0.01)
       T_double = 0.01;
    if (KETA.SOKUTE_MIN == 3 && T_double < 0.001)
       T_double = 0.001;
    // end of add 2000.5.9


    // 下限チェック
    T_double1 = Tmp_KDB1.HIST_MIN/T_double;
    n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
    //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
    if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
       T_Low = Tmp_KDB1.HIST_MIN;
       n1 = 0;
    } else {
       T_Low = (double)(n1+1) * T_double;
       n1 = 1;
    }

    // 上限チェック
    //n2 = Cur_Kda1.HIST_MAX/T_double;
    T_double1 = Tmp_KDB1.HIST_MAX/T_double;
    n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
    if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
       T_High = Tmp_KDB1.HIST_MAX;
       n2 = 0;
    } else {
       T_High = (double)n2 * T_double;
       n2 = 1;
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[1][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = Tmp_KDB1.HIST_MAX + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 } else { // 片側チェック
    T_index = 12;
    // 2000.5.9 表示桁数によって、default pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (KETA.SOKUTE_MIN == 0)
       T_index = 7;
    if (KETA.SOKUTE_MIN == 1)
       T_index = 10;
    if (KETA.SOKUTE_MIN == 2)
       T_index = 13;
    if (KETA.SOKUTE_MIN == 3)
       T_index = 16;
    // end of add 2000.5.9
Again1:
    T_double = E_Standard_Scale[T_index];    // default :0.02;

    if (Tmp_KDB1.SOKUTE_SU > 1) {      // 収録データがあり
       T_double2 = M_Kdb2[0].SOKUTEI_CH;
       for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
          if (Tmp_KDB1.HIST_KIKAK == 2) {  //最大値を探す
            if (M_Kdb2[i].SOKUTEI_CH > T_double2)
               T_double2 = M_Kdb2[i].SOKUTEI_CH;
          } else { // 最小値を探す
            if (M_Kdb2[i].SOKUTEI_CH < T_double2)
               T_double2 = M_Kdb2[i].SOKUTEI_CH;
          }
       }

       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // 下限チェック
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;

          if (T_double2 > T_Low + 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   T_index--;
                   SubFlag = 1;
                   goto Again1;
                }
             }
          }

          if (T_double2 < T_Low + 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }

          n2 = 0;
       } else {
          // 上限チェック
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;

          if (T_Low < 0)
             T_Low = 0;

          if (T_double2 < T_High - 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   SubFlag = 1;
                   T_index--;
                   goto Again1;
                }
             }
          }

          if (T_double2 > T_High - 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }

          n1 = 0;
       }
    } else { // 収録データなし
       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // 下限チェック
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;
          n2 = 0;
       } else {
          // 上限チェック
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;
          n1 = 0;
       }
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);

    if (N_Mid <= 7 && Tmp_KDB1.KOUMOKU_J == "ブラシ厚さ") { // スケール小さいすぎ、倍にする 2000.3.6
       T_double = T_double / 2;
       if (n1 > 0) {
          if (fabs(T_Low - (Tmp_KDB1.HIST_MIN - T_double)) <= COM_DIFF) {
             n1 = 0;
             T_Low = Tmp_KDB1.HIST_MIN;
          }
       }
       if (n2 > 0) {
          if (fabs(T_High - Tmp_KDB1.HIST_MAX - T_double) <= COM_DIFF) {
             n2 = 0;
             T_High = Tmp_KDB1.HIST_MAX;
          }
       }
       T_double1 = (T_High - T_Low)/T_double;
       N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    }


    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    if (T_High - (N_Mid + N_Low) * T_double < 0)
       N_Low = (int)(T_High / T_double) - N_Mid;

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = T_High;
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = T_High + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 }

 // 個数（E_Screen_Data[2][]）初期化
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

 // 個数 Counter
 if (Tmp_KDB1.SOKUTE_SU > 0) {
    for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
        for (j = 0; j < 20; j++) {
           if (j != 19) {
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
                  M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
                     //if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
                     //   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
                     //   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
                     //   E_Screen_Data[2][j-1] += 1;
                     //else
                        E_Screen_Data[2][j] += 1;
                  j = 20;
              }
           } else { // j == 19
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
                 E_Screen_Data[2][j] += 1;
                 j = 20;
              }
           }
        }
    }
 }


 if (Tmp_KDB1.HIST_SOKUT > 0) {
    if (Tmp_KDB1.SOKUTE_SU <= 0) {
       Tmp_KDB1.SOKUTE_AVE = 0;
       Tmp_KDB1.SOKUTE_MIN = 0;
       Tmp_KDB1.SOKUTE_MAX = 0;
       Tmp_KDB1.SOKUTE_R = 0;
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_P = 0;
       Tmp_KDB1.SOKUTE_SU = 0;
    } else {  // 統計
       Tmp_KDB1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_CH;
       Tmp_KDB1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_CH;
       Tmp_KDB1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_CH;

       // 平均値、最大値、最小値
       for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
           Tmp_KDB1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_CH;
           if (Tmp_KDB1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_CH)
              Tmp_KDB1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_CH;
           if (Tmp_KDB1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_CH)
              Tmp_KDB1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_CH;
       }
       Tmp_KDB1.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE/Tmp_KDB1.SOKUTE_SU;

       Tmp_KDB1.SOKUTE_R = Tmp_KDB1.SOKUTE_MAX - Tmp_KDB1.SOKUTE_MIN;

       // σ
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_P = 0;

       if (Tmp_KDB1.SOKUTE_SU > 1) {
          for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
              Tmp_KDB1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE);
          }
          Tmp_KDB1.SOKUTE_SGM = sqrt(Tmp_KDB1.SOKUTE_SGM / (Tmp_KDB1.SOKUTE_SU - 1));

          if (Tmp_KDB1.SOKUTE_SGM > COM_DIFF) {
             switch (Tmp_KDB1.HIST_KIKAK) {
             case 1:
                  Tmp_KDB1.SOKUTE_CP = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN) /
                                   (6 * Tmp_KDB1.SOKUTE_SGM);
                  // K
                  Tmp_KDB1.SOKUTE_K = fabs((Tmp_KDB1.HIST_MAX + Tmp_KDB1.HIST_MIN) /2 - Tmp_KDB1.SOKUTE_AVE) /
                                ((Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/2);

                  // CPK
                  Tmp_KDB1.SOKUTE_CPK = (1-Tmp_KDB1.SOKUTE_K) * (Tmp_KDB1.HIST_MAX -
                                  Tmp_KDB1.HIST_MIN) / (6 * Tmp_KDB1.SOKUTE_SGM);
                  break;
             case 2:
                  Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.SOKUTE_AVE - Tmp_KDB1.HIST_MIN)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                  Tmp_KDB1.SOKUTE_K = 0;
                  Tmp_KDB1.SOKUTE_CPK = 0;
                  break;
             case 3:
                  Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.HIST_MAX - Tmp_KDB1.SOKUTE_AVE)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                  Tmp_KDB1.SOKUTE_K = 0;
                  Tmp_KDB1.SOKUTE_CPK = 0;
                  break;
             }
          }
       }

       // P 不良率
       int ErrorNo = 0;
       if (Tmp_KDB1.SOKUTE_SU > 0) {
          for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
              // 規格判断
              if (Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 2) {
                 if (M_Kdb2[i].SOKUTEI_CH < Tmp_KDB1.HIST_MIN)
                    ErrorNo++;
              }

              if (Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) {
                 if (M_Kdb2[i].SOKUTEI_CH > Tmp_KDB1.HIST_MAX)
                    ErrorNo++;
              }
          }
          Tmp_KDB1.SOKUTE_P = (double)ErrorNo/(double)Tmp_KDB1.SOKUTE_SU * 100.0;
       } else
          Tmp_KDB1.SOKUTE_P = 0;
    }
}
 // 最大個数を求める
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // スケールを求める
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;

*/


/* 2000.3.6 変更
 int MaxNo;     // 最大個数
 int T_Scale;
 AnsiString string;

 int i, j;
 char s_str[64];
 double T_double, T_High, T_Low, T_double1, T_double2;
 int N_Mid, N_High, N_Low, n1, n2, T_index;

 // Y軸のScale 計算
 //   T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
 //   for (i = 18; i >= 0; i--) {
 //       if (E_Standard_Scale[i] > T_double) {
 //          T_double = E_Standard_Scale[i];
 //          i = -1;
 //       }
 //   }


    // 規格以内のライン数
    switch(Tmp_KDB1.HIST_KIKAK)
    {
        case 1: //両側チェックケース
		    	T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/20;
	        break;
        case 2: //下限チェックケース
            	//下限規格 最大値を検索
				if (Tmp_KDB1.SOKUTE_SU > 1) {      // 収録データがあり
					T_double2 = M_Kdb2[0].SOKUTEI_CH;
					for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
					// 最大値を探す
						if (M_Kdb2[i].SOKUTEI_CH > T_double2)
							T_double2 = M_Kdb2[i].SOKUTEI_CH;
					}
       			}
		    	T_double = (T_double2 - Tmp_KDB1.HIST_MIN)/20;
            break;

        case 3: //上限チェックケース
            	//上限規格 最小値を検索
				if (Tmp_KDB1.SOKUTE_SU > 1) {      // 収録データがあり
					T_double2 = M_Kdb2[0].SOKUTEI_CH;
					for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
					// 最小値を探す
						if (M_Kdb2[i].SOKUTEI_CH < T_double2)
							T_double2 = M_Kdb2[i].SOKUTEI_CH;
					}
       			}

		    	T_double = (Tmp_KDB1.HIST_MAX - T_double2)/20;

            break;
    }

    //N_Mid = T_double1;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = 20;

    // 規格以下のライン数
    N_Low = 0;

    // 規格以上のライン数
    N_High = 0;

    // 規格以内スケール
	for (i = 0; i < N_Mid; i++) {
		E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
		E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
	}



 // 個数（E_Screen_Data[2][]）初期化
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

 // 個数 Counter
 if (Tmp_KDB1.SOKUTE_SU > 0) {
    for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
        for (j = 0; j < 20; j++) {
           if (j != 19) {
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
                  M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
                     //if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
                     //   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
                     //   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
                     //   E_Screen_Data[2][j-1] += 1;
                     //else
                        E_Screen_Data[2][j] += 1;
                  j = 20;
              }
           } else { // j == 19
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
                 E_Screen_Data[2][j] += 1;
                 j = 20;
              }
           }
        }
    }
 }


 if (Tmp_KDB1.HIST_SOKUT > 0) {
    if (Tmp_KDB1.SOKUTE_SU <= 0) {
       Tmp_KDB1.SOKUTE_AVE = 0;
       Tmp_KDB1.SOKUTE_MIN = 0;
       Tmp_KDB1.SOKUTE_MAX = 0;
       Tmp_KDB1.SOKUTE_R = 0;
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_P = 0;
       Tmp_KDB1.SOKUTE_SU = 0;
    } else {  // 統計
      Tmp_KDB1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_CH;
      Tmp_KDB1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_CH;
      Tmp_KDB1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_CH;

      // 平均値、最大値、最小値
      for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
          Tmp_KDB1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_CH;
          if (Tmp_KDB1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_CH)
             Tmp_KDB1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_CH;
          if (Tmp_KDB1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_CH)
             Tmp_KDB1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_CH;
      }
      Tmp_KDB1.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE/Tmp_KDB1.SOKUTE_SU;

      Tmp_KDB1.SOKUTE_R = Tmp_KDB1.SOKUTE_MAX - Tmp_KDB1.SOKUTE_MIN;

      // σ
      Tmp_KDB1.SOKUTE_SGM = 0;
      Tmp_KDB1.SOKUTE_CP = 0;
      Tmp_KDB1.SOKUTE_K = 0;
      Tmp_KDB1.SOKUTE_CPK = 0;
      if (Tmp_KDB1.SOKUTE_SU > 1) {
         for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
             Tmp_KDB1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE);
         }
         Tmp_KDB1.SOKUTE_SGM = sqrt(Tmp_KDB1.SOKUTE_SGM / (Tmp_KDB1.SOKUTE_SU - 1));

         if (Tmp_KDB1.SOKUTE_SGM > COM_DIFF) {
            switch (Tmp_KDB1.HIST_KIKAK) {
            case 1:
                 Tmp_KDB1.SOKUTE_CP = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN) /
                                   (6 * Tmp_KDB1.SOKUTE_SGM);
                 // K
                 Tmp_KDB1.SOKUTE_K = fabs((Tmp_KDB1.HIST_MAX + Tmp_KDB1.HIST_MIN) /2 - Tmp_KDB1.SOKUTE_AVE) /
                                ((Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/2);

                 // CPK
                 Tmp_KDB1.SOKUTE_CPK = (1-Tmp_KDB1.SOKUTE_K) * (Tmp_KDB1.HIST_MAX -
                                  Tmp_KDB1.HIST_MIN) / (6 * Tmp_KDB1.SOKUTE_SGM);
                 break;
            case 2:
                 Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.SOKUTE_AVE - Tmp_KDB1.HIST_MIN)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                 Tmp_KDB1.SOKUTE_K = 0;
                 Tmp_KDB1.SOKUTE_CPK = 0;
                 break;
            case 3:
                 Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.HIST_MAX - Tmp_KDB1.SOKUTE_AVE)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                 Tmp_KDB1.SOKUTE_K = 0;
                 Tmp_KDB1.SOKUTE_CPK = 0;
                 break;
            }
         }
      }

      // P
      Tmp_KDB1.SOKUTE_P = 0;

    }
}
 // 最大個数を求める
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // スケールを求める
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;
*/
}

//小数点以下
AnsiString __fastcall TForm3::ConvKETA1(int keta,double n)
{
    int x;
    double m;
    AnsiString str;

    //小数点以下 keta桁
    x = pow(10,keta);
    m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

    if ( keta > 0 ) {
    	str = "#0." + AnsiString::StringOfChar('0', keta );
	} else {
    	str = "#0";
    }
    return( str );
}
//有効桁数
AnsiString __fastcall TForm3::ConvKETA2(int keta,double n,int SGM_K)
{
    int x,i;
    double m;
    AnsiString str;
    AnsiString tmp_s1,tmp_s2;
    int tmp_n1,tmp_n2;
    AnsiString Formatstr;
    char test[256];
    AnsiString test2;
    int flag,pos;
    int flag_M;

    //有効桁数
    if ( n < 0 ) {
        //マイナス
        flag_M = -1;
        n = n * -1;
    } else {
        flag_M = 1;
    }

    if ( n >= 1 ) {
        //1以上
        flag = 1;
    } else {
        //0以上1未満
        flag = 2;
    }

    switch( flag ){
        case 1:
            str = FormatFloat("#0.0#", n );
            pos = str.AnsiPos(".") - 1;
            if ( pos <  keta ) {
                Formatstr = "#0." + AnsiString::StringOfChar('0', keta-pos );
            } else {
                if ( pos == keta ) {
                    Formatstr = "#0";
                } else {
                //keta = 2, n = 1234.5 → 1200
                    Formatstr = "#0";
                    tmp_s1 = FloatToStr((int(n)));
                    tmp_n1 = tmp_s1.Length();
                    tmp_n2 = pow(10,(tmp_n1-keta));

                    //switch( SGM_K ) {
                    //    case 1:
                    //        //SGM
                    //        KETA.SOKUTE_SGM = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //
                    //    case 2:
                    //        //K
                    //        KETA.SOKUTE_K = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //}

                }
            }
            break;

        case 2:
            x = pow(10,keta);
            m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

            if ( n == 0 ) {
            	Formatstr = "#0."+ AnsiString::StringOfChar('0', (keta - 1));
            } else {
            	i = 1;
            	while(1) {
            		if ( int(n*( pow(10,i))) > 0 ) {
                		break;
                	} else {
                		i++;
                	}
            	}
            	Formatstr = "#0." + AnsiString::StringOfChar('0', (i - 1 + keta));
			}
            break;
    }
    return ( Formatstr );
}

//検査項目小数点以下の桁数の書式セット
int __fastcall TForm3::KENSASYOSIKI_Set(int KMK,double JYOKEN,int KETA)
{
	int sBuf;

    switch(KMK)
    {
        case 0: //リード線長さ
        	//sBuf = 2;
            sBuf = KETA;
            break;
        case 1: //ブラシ幅
        	//sBuf = 3;
           sBuf = KETA;
            break;

        case 3: //リード線取付抵抗
        	sBuf = 1;
            break;

        case 4: //リード線引張強度
        	sBuf =1;
            break;

        case 5: //母体比重
        	//sBuf = 2;
            sBuf = KETA;
            break;

        case 6: //硬度
        	switch ( int(JYOKEN) )
            {
        		case 1: //硬度 圧面
        			sBuf = 0;
            		break;

        		case 2: //硬度 側面
        			sBuf = 0;
            		break;

        		case 3: //硬度 圧面
        			sBuf = 1;
            		break;

        		case 4: //硬度 側面
        			sBuf = 1;
            		break;

        		default:
                	sBuf = 3;
            		break;
        	}
            break;
        case 7: //固有抵抗
        	sBuf = 0;
            break;

        case 8: //抗折力
        	sBuf = 1;
            break;

        case 9: //座屈
        	sBuf = 0;
            break;

        case 2: //その他（ノギス）
        	//sBuf = 3;
            sBuf = KETA;
            break;

        case 10: //その他（キーボード）
        	//sBuf = 2;
            sBuf = KETA;
             break;

        case 11: //その他（材料試験機）
        	sBuf = 1;
            break;

        default:
        	sBuf = 3;
	}
	return( sBuf );
}


//---------------------------------------------------------------------------
//統計 抵抗率 コンミの場合 L
void __fastcall TForm3::Tokei_TeikoL(void)
{
	int i,j;
	
	for ( i = 0; i < 20; i++ ) {
	    E_Screen_Data[2][i] = 0;
	}

	// 個数 Counter
	if (Cur_Kdb1.SOKUTE_SU > 0) {
		for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
			//for (j = 0; j < 20; j++) {    //2000.3.9
			//電圧 左
			for (j = 19; j >= 0; j--) {
				if (j != 19) {
					if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF &&
							M_Kdb2[i].SOKUTEI_MEI3 < E_Screen_Data[1][j] - COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						j = -1;
					}
				} else { // j == 19
					if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						//j = 20;       // 2000.3.9
						j = -1;
					}
			    }
			}
		}

	}

	if (Cur_Kdb1.HIST_SOKUT > 0) {
		if (Cur_Kdb1.SOKUTE_SU <= 0) {
			KETA.SOKUTE_AVE = 0;
			KETA.SOKUTE_MIN = 0;
			KETA.SOKUTE_MAX = 0;
			KETA.SOKUTE_R = 0;
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_P = 0;
			//KETA.SOKUTE_SU = 0;
		} else {  // 統計
			KETA.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_MEI3;
			KETA.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI3;
			KETA.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI3;

			// 平均値、最大値、最小値
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				KETA.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI3;
				if (KETA.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI3)
					KETA.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI3;
				if (KETA.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI3)
					KETA.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI3;
			}
			KETA.SOKUTE_AVE = KETA.SOKUTE_AVE/Cur_Kdb1.SOKUTE_SU;

			KETA.SOKUTE_R = KETA.SOKUTE_MAX - KETA.SOKUTE_MIN;

			// σ
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_P = 0;

			if (Cur_Kdb1.SOKUTE_SU > 1) {
			    for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				    KETA.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI3 -
										    KETA.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI3 -
										    KETA.SOKUTE_AVE);
			    }
			    KETA.SOKUTE_SGM = sqrt(KETA.SOKUTE_SGM / (Cur_Kdb1.SOKUTE_SU - 1));

			    if (KETA.SOKUTE_SGM > COM_DIFF) {
				    switch (Cur_Kdb1.HIST_KIKAK) {
					    case 1:
						    KETA.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
												    (6 * KETA.SOKUTE_SGM);
						    // K
						    KETA.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - KETA.SOKUTE_AVE) /
											    ((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

						    // CPK
						    KETA.SOKUTE_CPK = (1-KETA.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
											    	Cur_Kdb1.HIST_MIN) / (6 * KETA.SOKUTE_SGM);
						    break;
						    case 2:
							    KETA.SOKUTE_CP = fabs((KETA.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
													    (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
						    case 3:
							    KETA.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - KETA.SOKUTE_AVE)) /
												        (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
				    }
				}
			}
		}

		// P 不良率
		int ErrorNo = 0;
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				// 規格判断
				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
					if (M_Kdb2[i].SOKUTEI_MEI3 < Cur_Kdb1.HIST_MIN)
						ErrorNo++;
				}

				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                    //2008.05.21 E.Takase 規格有効判断は以上未満
					//if (M_Kdb2[i].SOKUTEI_MEI3 > Cur_Kdb1.HIST_MAX)
					if (M_Kdb2[i].SOKUTEI_MEI3+COM_DIFF >= Cur_Kdb1.HIST_MAX)
						ErrorNo++;
				}
			}
			KETA.SOKUTE_P = (double)ErrorNo/(double)Cur_Kdb1.SOKUTE_SU * 100.0;
		} else
			KETA.SOKUTE_P = 0;
	}

}

//---------------------------------------------------------------------------
//統計 抵抗率 コンミの場合 R
void __fastcall TForm3::Tokei_TeikoR(void)
{
	int i,j;
	
	for ( i = 0; i < 20; i++ ) {
	    E_Screen_Data[2][i] = 0;
	}

	// 個数 Counter
	if (Cur_Kdb1.SOKUTE_SU > 0) {
		for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
			//for (j = 0; j < 20; j++) {    //2000.3.9
			//電圧 左
			for (j = 19; j >= 0; j--) {
				if (j != 19) {
					if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF &&
							M_Kdb2[i].SOKUTEI_MEI5 < E_Screen_Data[1][j] - COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						j = -1;
					}
				} else { // j == 19
					if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						//j = 20;       // 2000.3.9
						j = -1;
					}
			    }
			}
		}

	}

	if (Cur_Kdb1.HIST_SOKUT > 0) {
		if (Cur_Kdb1.SOKUTE_SU <= 0) {
			KETA.SOKUTE_AVE = 0;
			KETA.SOKUTE_MIN = 0;
			KETA.SOKUTE_MAX = 0;
			KETA.SOKUTE_R = 0;
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_P = 0;
			//KETA.SOKUTE_SU = 0;
		} else {  // 統計
			KETA.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_MEI5;
			KETA.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI5;
			KETA.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI5;

			// 平均値、最大値、最小値
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				KETA.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI5;
				if (KETA.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI5)
					KETA.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI5;
				if (KETA.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI5)
					KETA.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI5;
			}
			KETA.SOKUTE_AVE = KETA.SOKUTE_AVE/Cur_Kdb1.SOKUTE_SU;

			KETA.SOKUTE_R = KETA.SOKUTE_MAX - KETA.SOKUTE_MIN;

			// σ
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_P = 0;

			if (Cur_Kdb1.SOKUTE_SU > 1) {
			    for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				    KETA.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI5 -
										    KETA.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI5 -
										    KETA.SOKUTE_AVE);
			    }
			    KETA.SOKUTE_SGM = sqrt(KETA.SOKUTE_SGM / (Cur_Kdb1.SOKUTE_SU - 1));

			    if (KETA.SOKUTE_SGM > COM_DIFF) {
				    switch (Cur_Kdb1.HIST_KIKAK) {
					    case 1:
						    KETA.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
												    (6 * KETA.SOKUTE_SGM);
						    // K
						    KETA.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - KETA.SOKUTE_AVE) /
											    ((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

						    // CPK
						    KETA.SOKUTE_CPK = (1-KETA.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
											    	Cur_Kdb1.HIST_MIN) / (6 * KETA.SOKUTE_SGM);
						    break;
						    case 2:
							    KETA.SOKUTE_CP = fabs((KETA.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
													    (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
						    case 3:
							    KETA.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - KETA.SOKUTE_AVE)) /
												        (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
				    }
				}
			}
		}

		// P 不良率
		int ErrorNo = 0;
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				// 規格判断
				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
					if (M_Kdb2[i].SOKUTEI_MEI5 < Cur_Kdb1.HIST_MIN)
						ErrorNo++;
				}

				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                    //2008.05.21 E.Takase 規格有効判断は以上未満
					//if (M_Kdb2[i].SOKUTEI_MEI5 > Cur_Kdb1.HIST_MAX)
					if (M_Kdb2[i].SOKUTEI_MEI5+COM_DIFF > Cur_Kdb1.HIST_MAX)
						ErrorNo++;
				}
			}
			KETA.SOKUTE_P = (double)ErrorNo/(double)Cur_Kdb1.SOKUTE_SU * 100.0;
		} else
			KETA.SOKUTE_P = 0;
	}

}

