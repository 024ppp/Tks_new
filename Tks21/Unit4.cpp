/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : Unit4.cpp                                           *
*  create        : 2000.01.06                                          *
*  update        :                                                     *
*  contents      : データ出力部プログラム                              *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <dir.h>
#include <math.h>
#include <shellapi.h>

#include "Unit1.h"
#include "Unit3.h"
#include "Unit4.h"
int CurLine;
int PageBreakFlag;
char CDPath[256];
char path[256];
char path2[256];
char path3[256];
FILE *stream;
FILE *stream2;
FILE *stream3;
int PageNm;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//Excel（X-R管理図.xls） 起動
bool __fastcall TForm1::Excel_Write()
{
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\X-R管理図.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);

}


//---------------------------------------------------------------------------
//データ出力
int __fastcall TForm1::Write_CSVMain(void)
{
	int i,n;
    int flag;

    flag = 0;

    //カレントディレクトリの取得
    strcpy(CDPath, "X:\\");	// 値を返す形式: X:\ で文字列を満たす
    CDPath[0] = 'A' + getdisk();	// X を現在のドライブ名に置き換える
    getcurdir(0, CDPath+3);	// 文字列部分の残りにカレントディレクトリを追加

    PageNm = 0;

    // ファイルを更新用に開く
    strcpy(path,CDPath);
    strcat(path, "\\data.csv");
    strcpy(path2,CDPath);
    strcat(path2, "\\data2.csv");
    strcpy(path3,CDPath);
    strcat(path3, "\\data3.csv");
    if( ((stream = fopen( path, "w+" )) != NULL ) &&
    	((stream2 = fopen( path2, "w+" )) != NULL ) &&
        ((stream3 = fopen( path3, "w+" )) != NULL ) 		){	//正常にﾌｧｲﾙをｵｰﾌﾟﾝできた場合

    	//KD01 リード線長さ寸法 検索
        for ( i = 0; i <= 15; i++ ) {
            if ( Check_Print(i) ==1 ) {
				n = Search_KD(i);
        		if ( n > 0 ) {
        			//出力
        			Write_CSV(i);
        		}
            } else {
            	n = 0;
            }
    		if ( n > 0 || flag > 0 ) flag = 1;
        }
        if ( flag == 0 ) {
        //検索結果 0件
        	//コントロールデータ ページ数
        	fprintf(stream,"0\n%d\n",PageNm);
			// ファイルを閉じる
			fclose(stream);
			fclose(stream2);
			fclose(stream3);
			return(0);
        } else {

        	//コントロールデータ ページ数
        	fprintf(stream,"1\n%d\n",PageNm);
			// ファイルを閉じる
			fclose(stream);
			fclose(stream2);
			fclose(stream3);
			return(1);
        }

	} else {  //ﾌｧｲﾙのｵｰﾌﾟﾝに失敗した場合
		fclose(stream);
		fclose(stream2);
		fclose(stream3);
		return(-1);
	}



}

//testItem（検査項目）
void __fastcall TForm1::Write_CSV(int testItem)
{
    Query1->First();
	CurLine = 0;
    PageBreakFlag = 0;
    FormatCAL();
    
	//1行分のデータを読み込む
	ReadLineData(testItem);
    //MIN,MAX,StartYMD,EndYMD,StartLOTNO,EndLOTNO,X_AVE_MIN,X_AVE_MAX,R_MIN,R_MAX
    if ( KD.SOKUTEI_1 <= KD.SOKUTEI_2 ) {
    	CALD.MIN = KD.SOKUTEI_1;
    	CALD.MAX = KD.SOKUTEI_2;
    } else {
    	CALD.MIN = KD.SOKUTEI_2;
    	CALD.MAX = KD.SOKUTEI_1;
    }
    CALD.StartYMD = KD.KENSA_YMD;
    CALD.EndYMD = KD.KENSA_YMD;
    CALD.StartLOTNO = KD.LOTNO;
    CALD.EndLOTNO = KD.LOTNO;
    CALD.X_AVE_MIN = KD.X_AVE;
    CALD.X_AVE_MAX = KD.X_AVE;
    CALD.R_MIN = KD.R;
    CALD.R_MAX = KD.R;
	////σの計算に使用
	//CALD.SGM_n = 2;
	//CALD.SGM_x = KD.SOKUTEI_1 + KD.SOKUTEI_2;
	//CALD.SGM_x2 = ( KD.SOKUTEI_1 * KD.SOKUTEI_1 ) + ( KD.SOKUTEI_2 * KD.SOKUTEI_2 );
    ////平均値
	//CALD.X_AVE_AVE = KD.X_AVE;
	//CALD.R_AVE = KD.R;

	while( 1 ){
        CurLine++;

        //データ�@csvに出力
        WriteLineData01(testItem);

		//MIN,MAX,StartYMD,EndYMD,StartLOTNO,EndLOTNO,X_AVE_MIN,X_AVE_MAX,R_MIN,R_MAX の判断
        if( KD.SOKUTEI_1 <= KD.SOKUTEI_2 ) {
        	if ( CALD.MIN > KD.SOKUTEI_1 ) CALD.MIN = KD.SOKUTEI_1;
			if ( CALD.MAX < KD.SOKUTEI_2 ) CALD.MAX = KD.SOKUTEI_2;
        } else {
        	if ( CALD.MIN > KD.SOKUTEI_2 ) CALD.MIN = KD.SOKUTEI_2;
			if ( CALD.MAX < KD.SOKUTEI_1 ) CALD.MAX = KD.SOKUTEI_1;
        }
        if ( PageBreakFlag == 1 || CALD.StartYMD > KD.KENSA_YMD ) CALD.StartYMD = KD.KENSA_YMD;
        if ( PageBreakFlag == 1 || CALD.EndYMD < KD.KENSA_YMD ) CALD.EndYMD = KD.KENSA_YMD;
        if ( PageBreakFlag == 1 || CALD.StartLOTNO > KD.LOTNO ) CALD.StartLOTNO = KD.LOTNO;
        if ( PageBreakFlag == 1 || CALD.EndLOTNO < KD.LOTNO ) CALD.EndLOTNO = KD.LOTNO;
        if ( PageBreakFlag == 1 || CALD.X_AVE_MIN > KD.X_AVE ) CALD.X_AVE_MIN = KD.X_AVE;
        if ( PageBreakFlag == 1 || CALD.X_AVE_MAX < KD.X_AVE ) CALD.X_AVE_MAX = KD.X_AVE;
        if ( PageBreakFlag == 1 || CALD.R_MIN > KD.R ) CALD.R_MIN = KD.R;
        if ( PageBreakFlag == 1 || CALD.R_MAX < KD.R ) CALD.R_MAX = KD.R;

        //σの計算に使用
        CALD.SGM_n += 2;
        CALD.SGM_x += KD.SOKUTEI_1 + KD.SOKUTEI_2;
        CALD.SGM_x2 += (( KD.SOKUTEI_1 * KD.SOKUTEI_1 ) + ( KD.SOKUTEI_2 * KD.SOKUTEI_2 ));
    	//平均値
		CALD.X_AVE_AVE += KD.X_AVE;
		CALD.R_AVE += KD.R;

        PageBreakFlag = 0;
        //改ページするかどうかを判断
        //1ページ 30個
        if ( CurLine >= 30 ){
            //σ 平均値の計算
            SubSGM(testItem);

            //xAve の 目盛り計算
            SubXAveScale(testItem);
            //Rの目盛り計算
            SubRScale();

        	//データ�Acsvに出力
            WriteLineData02(testItem);
            PageNm++;
			CurLine = 0;
        	PageBreakFlag = 1;

            //CALの初期化
            FormatCAL();
        }

        //カレントレコードを次の行へ移動
        //最後の行なら終了
        Query1->Next();
        if ( Query1->Eof ) {
        	break;
        }

		//1行分のデータを読み込む
		ReadLineData(testItem);

    }

	if ( PageBreakFlag == 0 ){
        //σ 平均値の計算
        SubSGM(testItem);

		//xAve の 目盛り計算
        SubXAveScale(testItem);
		//Rの目盛り計算
        SubRScale();

		//データ�Acsvに出力
		WriteLineData02(testItem);
        PageNm++;
		CurLine = 0;
		PageBreakFlag = 1;

        //CALの初期化
        FormatCAL();
    }
    
}

//---------------------------------------------------------------------------
//CALの初期化
void __fastcall TForm1::FormatCAL(void)
{
	CALD.StartYMD 		= "";		// 開始検査日
	CALD.EndYMD 			= "";		// 終了検査日
	CALD.StartLOTNO 		= "";		// 開始ロットNo
	CALD.EndLOTNO 		= "";		// 終了ロットNo
	CALD.MIN 			= 0;       	// 最小値
	CALD.MAX 			= 0;       	// 最大値
	CALD.X_AVE_MIN 		= 0;       	// X平均値 最小値
	CALD.X_AVE_MAX 		= 0;       	// X平均値 最大値
	CALD.X_AVE_AVE 		= 0;       	// X平均値 平均値
	CALD.R_MIN 			= 0;       	// R 最小値
	CALD.R_MAX 			= 0;       	// R 最大値
	CALD.R_AVE 			= 0;       	// R 平均値
	CALD.X_AVE_ScaleMin 	= 0;   		// X平均値 目盛りの最小値
	CALD.X_AVE_ScaleMax 	= 0;   		// X平均値 目盛りの最大値
	CALD.X_AVE_Scale 	= 0;      	// X平均値 目盛りの間隔
	CALD.R_ScaleMin 		= 0;       	// R 目盛りの最小値
	CALD.R_ScaleMax 		= 0;       	// R 目盛りの最大値
	CALD.R_Scale 		= 0;       	// R 目盛りの間隔
	CALD.SGM 			= 0;
	CALD.SGM_x 			= 0;
	CALD.SGM_x2 			= 0;
	CALD.SGM_n 			= 0;
	CALD.k 				= 0;
	CALD.Cp 				= 0;
	CALD.Cpk 			= 0;
}

//---------------------------------------------------------------------------
//σの計算
void __fastcall TForm1::SubSGM(int testItem)
{
	double T,M;
	double TX,MX;

	//CALD.SGM_n = CALD.SGM_n - 2;

	//平均値
	CALD.X_AVE_AVE = CALD.X_AVE_AVE / ( CurLine * 1.0 );
	CALD.R_AVE = CALD.R_AVE / ( CurLine * 1.0 );

    //σの計算
	CALD.SGM = (( CALD.SGM_n * CALD.SGM_x2 ) - ( CALD.SGM_x * CALD.SGM_x ))
    			 / ( CALD.SGM_n * ( CALD.SGM_n - 1 ) * 1.0 );
    CALD.SGM = sqrt(CALD.SGM);

    //k Cp Cpk の計算
	switch(testItem)
	{
        //両側規格
		case  0: //リード線長さ
		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
		case  5: //見掛比重
		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
		case 10: //抵抗率
		case 11: //曲げ強さ
		case 12: //座屈
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
		case 14: //抵抗率(L)      //2002/12/07 E.Takase
		case 15: //抵抗率(R)      //2002/12/07 E.Takase
            //規格幅
            T = KD.KIKAK_MAX - KD.KIKAK_MIN;
            //規格の中心
        	M = KD.KIKAK_MIN + (( KD.KIKAK_MAX - KD.KIKAK_MIN ) / 2.0);
            //偏差指数
            MX = ( M - ( CALD.SGM_x / ( CALD.SGM_n * 1.0 )));
            if ( MX < 0 ) {
				MX = MX * -1.0;
            }
            CALD.k = MX / ( T / 2.0 );
            //2003/07/22 E.Takase
            if ( CALD.SGM == 0 ) {
				CALD.Cp = 0;
				CALD.Cpk = 0;
            } else {
				CALD.Cp = T / ( CALD.SGM * 6.0 );
				CALD.Cpk = ( 1 - CALD.k ) * ( T / ( CALD.SGM * 6.0 ));
            }
        	break;

        //上限規格
        case  3: //リード線取付抵抗
            TX = (( CALD.SGM_x / ( CALD.SGM_n * 1.0 )) - KD.KIKAK_MAX );
            if ( TX < 0 ) {
            	TX = TX * -1.0;
            }
			CALD.Cp = TX / ( CALD.SGM * 3.0 );
            CALD.Cpk = 0;
			CALD.k = 0;
            break;
        //下限規格
        case  4:  //リード線取付強度
            TX = ( KD.KIKAK_MIN - ( CALD.SGM_x / ( CALD.SGM_n * 1.0 )));
            if ( TX < 0 ) {
				TX = TX * -1.0;
            }
			CALD.Cp = TX / ( CALD.SGM * 3.0 );
            CALD.Cpk = 0;
			CALD.k = 0;
            break;
        default :
			CALD.k = 0;
			CALD.Cp = 0;
			CALD.Cpk = 0;
        	break;
    }

    //UCL,LCL
    CALD.X_UCL = CALD.X_AVE_AVE + ( 3.0 * CALD.SGM );
    CALD.X_LCL = CALD.X_AVE_AVE - ( 3.0 * CALD.SGM );
    CALD.R_UCL = CALD.R_AVE + ( 3.0 * CALD.SGM );


}


//---------------------------------------------------------------------------
//XAve 目盛りの計算
void __fastcall TForm1::SubXAveScale(int testItem)
{
    int i,i2;
    double x;
    double s,s2;

    //UCL,LCLもチェック
    if ( CALD.X_AVE_MIN > CALD.X_UCL ) CALD.X_AVE_MIN = CALD.X_UCL;
    if ( CALD.X_AVE_MAX < CALD.X_UCL ) CALD.X_AVE_MAX = CALD.X_UCL;
    if ( CALD.X_AVE_MIN > CALD.X_LCL ) CALD.X_AVE_MIN = CALD.X_LCL;
    if ( CALD.X_AVE_MAX < CALD.X_LCL ) CALD.X_AVE_MAX = CALD.X_LCL;

    //目盛りの最小値、最大値決定
	switch(testItem)
	{
        //両側規格
		case  0: //リード線長さ
		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
		case  5: //見掛比重
		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
		case 10: //抵抗率
		case 11: //曲げ強さ
		case 12: //座屈
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
		case 14: //抵抗率(L)      //2002/12/07 E.Takase
		case 15: //抵抗率(R)      //2002/12/07 E.Takase
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;

       	break;

        //上限規格
        case  3: //リード線取付抵抗
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
			//最小値 CALD.X_AVE_MINを小数点以下切り捨て
	    	CALD.X_AVE_ScaleMin = int(CALD.X_AVE_MIN);
       	break;

        //下限規格
        case  4:  //リード線取付強度
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
		    //最大値 CALD.X_AVE_MAXを小数点以下切り上げ
		    if ( CALD.X_AVE_MAX - (int(CALD.X_AVE_MAX)) > 0 ) {
		    	CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX)) + 1;
		    } else {
		        CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX));
		    }
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;

       	break;

        default :
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;
        	break;
    }


    //目盛りのスケールを決定
    CALD.X_AVE_Scale = (CALD.X_AVE_ScaleMax - CALD.X_AVE_ScaleMin) / (XScaleNM * 1.0);

/* 20000322
    //UCL,LCLもチェック
    if ( CALD.X_AVE_MIN > CALD.X_UCL ) CALD.X_AVE_MIN = CALD.X_UCL;
    if ( CALD.X_AVE_MAX < CALD.X_UCL ) CALD.X_AVE_MAX = CALD.X_UCL;
    if ( CALD.X_AVE_MIN > CALD.X_LCL ) CALD.X_AVE_MIN = CALD.X_LCL;
    if ( CALD.X_AVE_MAX < CALD.X_LCL ) CALD.X_AVE_MAX = CALD.X_LCL;

	//最小値 CALD.X_AVE_MINを小数点以下切り捨て
    CALD.X_AVE_ScaleMin = (int(CALD.X_AVE_MIN));
    //最大値 CALD.X_AVE_MAXを小数点以下切り上げ
    if ( CALD.X_AVE_MAX - (int(CALD.X_AVE_MAX)) > 0 ) {
    	CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX)) + 1;
    } else {
        CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX));
    }

    x = CALD.X_AVE_ScaleMax - CALD.X_AVE_ScaleMin;
    i = 1;
    s = ScaleINI * i;
    while( 1 ){
    	if ( x < ( XScaleNM * s ) ) {
        	CALD.X_AVE_Scale = s;
        	break;
        } else {
            s = s * 2;
        	i++;
        }

    }

    //スケール 0.125 より 小さくして良いか
    if ( CALD.X_AVE_Scale <= ScaleINI ) {
        x = CALD.X_AVE_MAX - CALD.X_AVE_MIN;
        //s2 = ScaleINI;
        //s = ( ScaleINI * 4 ) / ( 5.0 );
        s2 = CALD.X_AVE_Scale;
        s = ScaleINI;
        i = 0;
        while ( 1 ) {
        	if ( x >= ( XScaleNM * s ) ) {
            	CALD.X_AVE_Scale = s2;
        		break;
        	} else {
                s2 = s;
            	if ( ( i % 4 ) == 0 ) {
                	s = ( s * 4 ) / 5.0;
                } else {
                	s = s / 2.0;
                }
        		i++;
        	}
        }
        i2 = i;

        //CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin
        i = 1;
        x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MIN < x ) {
            	CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            }
        }
        if ( CALD.X_AVE_MAX > ( CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * ( XScaleNM-1 ) )) ) {
            //スケール 計算し直し
        	if ( (( i2 - 2 ) % 4 ) == 0 ) {
            	CALD.X_AVE_Scale = ( CALD.X_AVE_Scale * 5 ) / 4.0;
            } else {
            	CALD.X_AVE_Scale = CALD.X_AVE_Scale * 2.0;
            }
        	i = 1;
        	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MIN < x ) {
            		CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                	break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            	}
        	}
        }
    	CALD.X_AVE_ScaleMax = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * ( XScaleNM-1 ) );
    }
*/

/************************************************************************
    //スケール 0.125 より 小さくして良いか
    if ( CALD.X_AVE_Scale <= ScaleINI ) {
        x = CALD.X_AVE_MAX - CALD.X_AVE_MIN;
    	i = 2;
    	s = ScaleINI / ( i * 1.0 );
    	while( 1 ){
    		if ( x > ( XScaleNM * s ) ) {
        		CALD.X_AVE_Scale = s * 2;
        		break;
        	} else {
            	s = s / 2.0;
        		i++;
        	}
    	}

        //CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin
        i = 1;
        x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MIN <= x ) {
            	CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            }
        }

        i = 1;
        x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MAX >= x ) {
            	CALD.X_AVE_ScaleMax = x + CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
            }
        }
        //CALD.X_AVE_Scale OKかチェック
        if ((CALD.X_AVE_ScaleMax-CALD.X_AVE_ScaleMin)>(XScaleNM*CALD.X_AVE_Scale) ) {
        	CALD.X_AVE_Scale = CALD.X_AVE_Scale * 2;
        
        	//CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin もう一度つけ直し
        	i = 1;
        	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MIN <= x ) {
            		CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            	}
        	}

        	i = 1;
        	x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MAX >= x ) {
            		CALD.X_AVE_ScaleMax = x + CALD.X_AVE_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
            	}
        	}
        }
    }

************************************************************************/

}

//---------------------------------------------------------------------------
//R 目盛りの計算
void __fastcall TForm1::SubRScale(void)
{
    int i,i2;
    double x;
    double s,s2;

    //UCLもチェック
    if ( CALD.R_MIN > CALD.R_UCL ) CALD.R_MIN = CALD.R_UCL;
    if ( CALD.R_MAX < CALD.R_UCL ) CALD.R_MAX = CALD.R_UCL;

    // R_MIN 0で固定
    CALD.R_MIN = 0;

	//最小値 CALD.R_MINを小数点以下切り捨て
    CALD.R_ScaleMin = (int(CALD.R_MIN));
    //最大値 CALD.R_MAXを小数点以下切り上げ
    if ( CALD.R_MAX - (int(CALD.R_MAX)) > 0 ) {
    	CALD.R_ScaleMax = (int(CALD.R_MAX)) + 1;
    } else {
        CALD.R_ScaleMax = (int(CALD.R_MAX));
    }

    x = CALD.R_ScaleMax - CALD.R_ScaleMin;
    i = 1;
    s = ScaleINI * i;
    while( 1 ){
    	if ( x <= ( ( RScaleNM-1 )  * s ) ) {

        	CALD.R_Scale = s;
            CALD.R_ScaleMax = CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) );
        	break;
        } else {
            s = s * 2;
        	i++;
        }

    }


    //スケール 0.125 より 小さくして良いか
    if ( CALD.R_Scale <= ScaleINI*2 ) {
        x = CALD.R_MAX - CALD.R_MIN;
        //s2 = ScaleINI;
        //s = ( ScaleINI * 4 ) / ( 5.0 );
        s2 = CALD.R_Scale;
        s = ScaleINI;
        i = 0;
        while ( 1 ) {
        	if ( x >= ( ( RScaleNM-1 )  * s ) ) {
            	CALD.R_Scale = s2;
        		break;
        	} else {
                s2 = s;
            	if ( ( i % 4 ) == 0 ) {
                	s = ( s * 4 ) / 5.0;
                } else {
                	s = s / 2.0;
                }
        		i++;
        	}
        }
        i2 = i;

        //CALD.R_ScaleMax, CALD.R_ScaleMin
        i = 1;
        x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MIN < x ) {
            	CALD.R_ScaleMin = x - CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            }
        }
        if ( CALD.R_MAX > ( CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) )) ) {
            //スケール 計算し直し
        	if ( (( i2 - 2 ) % 4 ) == 0 ) {
            	CALD.R_Scale = ( CALD.R_Scale * 5 ) / 4.0;
            } else {
            	CALD.R_Scale = CALD.R_Scale * 2.0;
            }
        	i = 1;
        	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MIN < x ) {
            		CALD.R_ScaleMin = x - CALD.R_Scale;
                	break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            	}
        	}
        }
    	CALD.R_ScaleMax = CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) );
    }

/******************************************************************************
    //スケール 0.125 より 小さくして良いか
    if ( CALD.R_Scale <= ScaleINI * 2 ) {
        x = CALD.R_MAX - CALD.R_MIN;
    	i = 2;
    	s = ScaleINI / ( i * 1.0 );
    	while( 1 ){
    		if ( x > ( RScaleNM * s ) ) {
        		CALD.R_Scale = s * 2;
        		break;
        	} else {
            	s = s / 2.0;
        		i++;
        	}
    	}

        //CALD.R_ScaleMax, CALD.R_ScaleMin
        i = 1;
        x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MIN <= x ) {
            	CALD.R_ScaleMin = x - CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            }
        }

        i = 1;
        x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MAX >= x ) {
            	CALD.R_ScaleMax = x + CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
            }
        }
        //CALD.R_Scale OKかチェック
        if ((CALD.R_ScaleMax-CALD.R_ScaleMin)>(RScaleNM*CALD.R_Scale) ) {
        	CALD.R_Scale = CALD.R_Scale * 2;

        	//CALD.R_ScaleMax, CALD.R_ScaleMin もう一度つけ直し
        	i = 1;
        	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MIN <= x ) {
            		CALD.R_ScaleMin = x - CALD.R_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            	}
        	}

        	i = 1;
        	x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MAX >= x ) {
            		CALD.R_ScaleMax = x + CALD.R_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
            	}
        	}
        }
    }
******************************************************************************/


}    


//---------------------------------------------------------------------------
//データ�@ csv出力
void __fastcall TForm1::WriteLineData01(int testItem)
{
	//検査日 ロットNo 測定値1 測定値2 XAve R
	fprintf(stream2,"%s,%s,%lf,%lf,%lf,%lf\n",
		InsSEPA(KD.KENSA_YMD).c_str(),
        KD.LOTNO.c_str(),
        KD.SOKUTEI_1,
        KD.SOKUTEI_2,
        KD.X_AVE,
        KD.R
    );

}

//---------------------------------------------------------------------------
//データ�A csv出力
void __fastcall TForm1::WriteLineData02(int testItem)
{
    //改ページフラグ
    fprintf(stream2,"*,0,0,0,0,0\n");

	//タイトル
    //得意先品番 測定項目 試料数 計測器 開始検査日  終了検査日
	fprintf(stream3,"%s,%s,%d,%s,%s,%s\n",
		KD.DTKSHIN.c_str(),
        KENSA_NAME(testItem).c_str(),
        (CurLine*2),
        KENSA_KIKI(testItem).c_str(),
        InsSEPA(CALD.StartYMD).c_str(),
        InsSEPA(CALD.EndYMD).c_str()
    );

    //材質名 規格 上限規格 下限規格 測定単位 開始ロットNo 終了ロットNo
	fprintf(stream3,"%s,%d,%lf,%lf,%s,%s,%s\n",
        KD.ZISNAM.c_str(),
        KENSA_KIKAKU(testItem),
        KD.KIKAK_MAX,
        KD.KIKAK_MIN,
        KENSA_TANI(testItem).c_str(),
        CALD.StartLOTNO.c_str(),
        CALD.EndLOTNO.c_str()
    );

    //min max 小数点以下桁数
	fprintf(stream3,"%lf,%lf,%d,%s,%s\n",
    	CALD.MIN,
    	CALD.MAX,
        KENSA_KETA(testItem),
        KENSA_SYOSIKI(KENSA_KETA(testItem)).c_str(),
        KENSA_SYOSIKI(KENSA_KETA(testItem) + 1).c_str()
    );

    //XAve の目盛り
	fprintf(stream3,"%lf,%lf,%lf\n",
    	CALD.X_AVE_Scale,
    	CALD.X_AVE_ScaleMin,
        CALD.X_AVE_ScaleMax
    );

    //R の目盛り
	fprintf(stream3,"%lf,%lf,%lf\n",
    	CALD.R_Scale,
    	CALD.R_ScaleMin,
        CALD.R_ScaleMax
    );
	//min max 小数点以下桁数
	fprintf(stream3,"%d,%s,%s,%s,%s\n",
		KENSA_KETA(testItem),
		KENSA_SYOSIKI(KENSA_KETA(testItem)).c_str(),
		KENSA_SYOSIKI(KENSA_KETA(testItem) + 1).c_str(),
        Form1->ConvKETA2(3,CALD.SGM).c_str(),
        Form1->ConvKETA2(3,CALD.k).c_str()
    );

    //R_AVE X_AVE_AVE SGM SGM_x k Cp Cpk X_UCL X_LCL R_UCL
	fprintf(stream3,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
    	CALD.R_AVE,
    	CALD.X_AVE_AVE,
    	CALD.SGM,
    	CALD.k,
    	CALD.Cp,
        CALD.Cpk,
    	CALD.X_UCL,
    	CALD.X_LCL,
        CALD.R_UCL
    );

}

//---------------------------------------------------------------------------
//検査項目名
AnsiString __fastcall TForm1::KENSA_NAME(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{
		case  0: //リード線長さ
            sBuf = "リード線長さ";
			return(sBuf);
        	break;

		case  1: //ブラシ幅
            sBuf = "ブラシ幅";
			return(sBuf);
        	break;

		case  2: //ブラシ幅(縦押し)
            sBuf = "ブラシ幅(縦押し)";
			return(sBuf);
        	break;

		case  3: //リード線取付抵抗
            sBuf = "リード線取付抵抗";
			return(sBuf);
        	break;

		case  4: //リード線取付強度
            sBuf = "リード線取付強度";
			return(sBuf);
        	break;

		case  5: //見掛比重
            sBuf = "見掛比重";
			return(sBuf);
        	break;

		case  6: //硬度(HsC 圧面)
            sBuf = "硬度(HsC 圧面)";
			return(sBuf);
        	break;

		case  7: //硬度(HsC 側面)
            sBuf = "硬度(HsC 側面)";
			return(sBuf);
        	break;

		case  8: //硬度(HsD 圧面)
            sBuf = "硬度(HsD 圧面)";
			return(sBuf);
        	break;

		case  9: //硬度(HsD 側面)
            sBuf = "硬度(HsD 側面)";
			return(sBuf);
        	break;

		case 10: //抵抗率
            sBuf = "抵抗率";
			return(sBuf);
        	break;

		case 11: //曲げ強さ
            sBuf = "曲げ強さ";
			return(sBuf);
        	break;

		case 12: //座屈
            sBuf = "座屈";
			return(sBuf);
        	break;

		case 13: //曲げ強さ(現物) //200212/07 E.Takase
            sBuf = "曲げ強さ(現物)";
			return(sBuf);
        	break;

		case 14: //抵抗率(L) //200212/07 E.Takase
            sBuf = "抵抗率(L)";
			return(sBuf);
        	break;

		case 15: //抵抗率(R) //200212/07 E.Takase
            sBuf = "抵抗率(R)";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//測定単位
AnsiString __fastcall TForm1::KENSA_TANI(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{
		case  0://リード線長さ
		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
            sBuf = "mm";
			return(sBuf);
        	break;

		case  3: //リード線取付抵抗
            sBuf = "mV/A";
			return(sBuf);
        	break;

		case  4: //リード線取付強度
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
			}
			break;

		case  5: //見掛比重
            sBuf = "―";
			return(sBuf);
        	break;

		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
            sBuf = "HsC";
			return(sBuf);
        	break;


		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
            sBuf = "HsD";
			return(sBuf);
        	break;

		case 10: //抵抗率
		case 14: //抵抗率(L) //2002/12/07 E.Takase
		case 15: //抵抗率(R) //2002/12/07 E.Takase
            sBuf = "μΩ・cm";
			return(sBuf);
        	break;

		case 11: //曲げ強さ
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf/cm2";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N/cm2";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
				case 4:
		            sBuf = "N/mm2";
					return(sBuf);
		        	break;
			}
            break;

        //2003/07/22 E.Takase 単位追加
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf/cm2";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N/cm2";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
				case 4:
		            sBuf = "N/mm2";
					return(sBuf);
		        	break;
				case 5:
		            sBuf = "N";
					return(sBuf);
		        	break;
			}
            break;
		case 12: //座屈
            sBuf = "N";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//計測器
AnsiString __fastcall TForm1::KENSA_KIKI(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{

		case  0: //リード線長さ寸法
            sBuf = "ノギス";
			return(sBuf);
        	break;

		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
            sBuf = "マイクロメータ";
			return(sBuf);
        	break;

		case  3: //リード線取付抵抗
            sBuf = "取付抵抗測定器";
			return(sBuf);
        	break;

		case  4: //リード線取付強度
		case 12: //座屈
            sBuf = "材料試験機";
			return(sBuf);
        	break;

		case  5: //見掛比重
            sBuf = "マイクロメータ、電子天秤";
			return(sBuf);
        	break;

		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
            sBuf = "C型ショア硬度計";
			return(sBuf);
        	break;

		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
            sBuf = "D型ショア硬度計";
			return(sBuf);
        	break;

		case 10: //抵抗率
		case 14: //抵抗率(L) //2002/12/07 E.Takase
		case 15: //抵抗率(R) //2002/12/07 E.Takase
            sBuf = "抵抗率測定器";
			return(sBuf);
        	break;

		case 11: //曲げ強さ
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
            sBuf = "材料試験機";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//両側規格(1) 下限規格(2) 上限規格(3)
int __fastcall TForm1::KENSA_KIKAKU(int testItem)
{
	switch(testItem)
	{
		case  0:// リード線長さ
		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
		case  5: //見掛比重
		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
		case 10: //抵抗率
		case 11: //曲げ強さ
		case 12: //座屈
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
		case 14: //抵抗率(L)      //2002/12/07 E.Takase
		case 15: //抵抗率(R)      //2002/12/07 E.Takase
			return(1);
        	break;

		case  3: //リード線取付抵抗
			return(3);
        	break;

		case  4: //リード線取付強度
			return(2);
        	break;

        default :
			return(1);
        	break;
    }

}

//---------------------------------------------------------------------------
//小数点以下の桁数
int __fastcall TForm1::KENSA_KETA(int testItem)
{
	switch(testItem)
	{
		case  0: //リード線長さ
		case  5: //見掛比重
			return(2);
         	break;

		case  1: //ブラシ幅
		case  2: //ブラシ幅(縦押し)
			return(3);
         	break;

		case  3: //リード線取付抵抗
		case  4: //リード線取付強度
		case  8: //硬度(HsD 圧面)
		case  9: //硬度(HsD 側面)
		case 11: //曲げ強さ
		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
			return(1);
         	break;

		case  6: //硬度(HsC 圧面)
		case  7: //硬度(HsC 側面)
		case 10: //抵抗率
		case 14: //抵抗率(L) //2002/12/07 E.Takase
		case 15: //抵抗率(R) //2002/12/07 E.Takase
		case 12: //座屈
			return(0);
         	break;

        default :
			return(3);
         break;
    }

}

//---------------------------------------------------------------------------
//書式(ex "#0.000")
AnsiString __fastcall TForm1::KENSA_SYOSIKI(int n)
{
	int i;
    AnsiString sBuf;

    sBuf = "";
    for ( i = 1; i <= n; i++ ) {
    	sBuf = sBuf + "0";
    }

    if ( n > 0 ) {
    	sBuf = "#0." + sBuf;
    } else {
    	sBuf = "0";
    }
    return(sBuf);

}

//---------------------------------------------------------------------------
//印刷するかを判断
int __fastcall TForm1::Check_Print(int testItem)
{
	switch(testItem)
	{
		case  0: //リード線長さ
			if ( Form1->CheckBox1->Checked == True ) return(1);
			else return(0);
        	break;

		case  1: //ブラシ幅
			if ( Form1->CheckBox2->Checked == True ) return(1);
			else return(0);
        	break;

		case  2: //ブラシ幅(縦押し)
			if ( Form1->CheckBox3->Checked == True ) return(1);
			else return(0);
        	break;

		case  3: //リード線取付抵抗
			if ( Form1->CheckBox4->Checked == True ) return(1);
			else return(0);
        	break;

		case  4: //リード線取付強度
			if ( Form1->CheckBox5->Checked == True ) return(1);
			else return(0);
        	break;

		case  5: //見掛比重
			if ( Form1->CheckBox6->Checked == True ) return(1);
			else return(0);
        	break;


		case  6: //硬度(HsC 圧面)
			if ( Form1->CheckBox7->Checked == True ) return(1);
			else return(0);
        	break;


		case  7: //硬度(HsC 側面)
			if ( Form1->CheckBox8->Checked == True ) return(1);
			else return(0);
        	break;

		case  8: //硬度(HsD 圧面)
			if ( Form1->CheckBox9->Checked == True ) return(1);
			else return(0);
        	break;

		case  9: //硬度(HsD 側面)
			if ( Form1->CheckBox10->Checked == True ) return(1);
			else return(0);
        	break;

		case 10: //抵抗率
            //2002/12/07 E.Takase
			//if ( Form1->CheckBox11->Checked == True ) return(1);
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN != 5 ) return(1);
			else return(0);
        	break;

		case 11: //曲げ強さ
			if ( Form1->CheckBox12->Checked == True ) return(1);
			else return(0);
        	break;

		case 12: //座屈
			if ( Form1->CheckBox13->Checked == True ) return(1);
			else return(0);
        	break;

		case 13: //曲げ強さ(現物) //2002/12/07 E.Takase
			if ( Form1->CheckBox14->Checked == True ) return(1);
			else return(0);
        	break;

		case 14: //抵抗率(L)
            //2002/12/07 E.Takase
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN == 5 ) return(1);
			else return(0);
        	break;

		case 15: //抵抗率(R)
            //2002/12/07 E.Takase
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN == 5 ) return(1);
			else return(0);
        	break;

        default :
			return(0);
        	break;
    }
	return(0);

}
