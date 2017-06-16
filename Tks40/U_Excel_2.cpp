//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "unit1.h"
#include "unit3.h"
#include "U_Excel_2.h"
#define COM_DIFF 0.000001
const int E_Nums = 300;
char CDPath[256];
char path[256];
double E_Standard_Scale[20] = {500, 100, 50, 20, 10, 5, 2, 1, 0.5, 0.2, 0.1, 0.05,
                           0.02, 0.01, 0.005, 0.002, 0.001, 0.0005, 0.0002, 0.0001};

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
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    FILE *stream;

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

            Toukei_Tmp_KDB1();
            KETA.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE;
            KETA.SOKUTE_MIN = Tmp_KDB1.SOKUTE_MIN;
            KETA.SOKUTE_MAX = Tmp_KDB1.SOKUTE_MAX;
            KETA.SOKUTE_R   = Tmp_KDB1.SOKUTE_R  ;
            KETA.SOKUTE_SGM = Tmp_KDB1.SOKUTE_SGM;
            KETA.SOKUTE_CP  = Tmp_KDB1.SOKUTE_CP ;
            KETA.SOKUTE_CPK = Tmp_KDB1.SOKUTE_CPK;
            KETA.SOKUTE_K   = Tmp_KDB1.SOKUTE_K  ;
            KETA.SOKUTE_P   = Tmp_KDB1.SOKUTE_P  ;

            //桁数指定（フォーマット）を求める
	        KETA.R_str   = Form3->ConvKETA1( KETA.R,KETA.SOKUTE_R );
	        //KETA.R_str   = "#0.00";
	        KETA.AVE_str = Form3->ConvKETA1( KETA.AVE,KETA.SOKUTE_AVE );
	        KETA.MIN_str = Form3->ConvKETA1( KETA.MIN,KETA.SOKUTE_MIN );
	        KETA.MAX_str = Form3->ConvKETA1( KETA.MAX,KETA.SOKUTE_MAX );
	        KETA.SGM_str = Form3->ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
        	KETA.CP_str  = Form3->ConvKETA1( KETA.CP ,KETA.SOKUTE_CP  );
	        KETA.K_str   = Form3->ConvKETA2( KETA.K  ,KETA.SOKUTE_K ,2  );
	        KETA.CPK_str = Form3->ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	        KETA.P_str   = Form3->ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );


            //グラフ目盛りのスケール 比較
            if ( Tmp_E_Scale < E_Scale) Tmp_E_Scale = E_Scale;

            //工程能力測定データ１ 規格の真ん中の値 +-？
            fprintf(stream,"%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                Tmp_KDB1.KOUMOKU_J.c_str(),
                Tmp_KDB1.KOUMOKU_E.c_str(),
				Tmp_KDB1.HIST_SOKUT_Ori,
				Tmp_KDB1.HIST_SOKUT,
				Tmp_KDB1.HIST_KIKAK,
				Tmp_KDB1.HIST_MIN,
				Tmp_KDB1.HIST_MAX,
				Tmp_KDB1.SOKUTE_SU,
				Tmp_KDB1.SOKUTE_SU_Ori,
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
            //以上、未満、個数
            for ( i = 0; i < 20; i++ ) {
                fprintf(stream,"%lf,%lf,%lf\n",E_Screen_Data[0][i],E_Screen_Data[1][i],E_Screen_Data[2][i]);
            }

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
                    Form1->EdtZIS->Caption.c_str(),
                    Form1->EdtZISNAM->Text.c_str(),
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
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\工程能力調査表.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_MINIMIZE);
    return(retDLL);

}

