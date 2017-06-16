/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : トライス検査システム（ＴＫＳ２１）                  *
*  file   name   : U_Func.cpp                                          *
*  create        : 1999.10.18                                          *
*  update        :                                                     *
*  contents      : 関数                                                *
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
*  function name : AnsiString Kara(int i)                              *
*                  +--------------------------------------+            *
*          引  数  | int        | i                       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | AnsiString | i=0  "  "               |            *
*                  |            | i=1  "～"               |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : "～"をつけるかつけないか                            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
AnsiString Kara(int i)
{
        if ( i == 0 ) {
            return("  ");
        }
        else {
            return( "～" );
        }

}
/***********************************************************************
*  function name : double DivAB(double a, double b)                    *
*                  +--------------------------------------+            *
*          引  数  | double     | a, b                    |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | double     | a / b                   |            *
*                  |            | a=0 または b=0 なら 0   |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : a / b （0割りをふせぐ）                             *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
double DivAB(double a, double b)
{
        if ( a == 0 || b == 0 ) {
            return(0.0);
        }
        else {
            return( a / b );
        }

}
/***********************************************************************
*  function name : AnsiString SOKUTEIstrI(int i, int n, int val)       *
*                  +--------------------------------------+            *
*          引  数  | int        | i   測定番号            |            *
*                  | int        | n   測定区分            |            *
*                  | int        | val 測定値              |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | AnsiString | 測定しない "-" 1,2行目  |            *
*                  |            | 測定しない " " 3行目以降|            *
*                  |            | 測定する   val 文字変換 |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : 測定値を文字列に変換する                            *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
AnsiString SOKUTEIstrI(int i, int n, int val)
{
    if ( n == 0 ) {
        if ( i < 2 ) return("-");
        else return(" ");
    }
    else {
        if ( i < n ) return(IntToStr(val));
        else return(" ");
    }
}
/************************************************************************
*  function name : AnsiString SOKUTEIstrF(int i,int n,double val,int k) *
*                  +--------------------------------------+             *
*          引  数  | int        | i   測定番号            |             *
*                  | int        | n   測定区分            |             *
*                  | double     | val 測定値              |             *
*                  | int        | k   小数点以下の桁数    |             *
*                  +--------------------------------------+             *
*                  +--------------------------------------+             *
*          戻り値  | AnsiString | 測定しない "-" 1,2行目  |             *
*                  |            | 測定しない " " 3行目以降|             *
*                  |            | 測定する   val 文字変換 |             *
*                  +--------------------------------------+             *
*  create        : 1999.10                                              *
*  update        :                                                      *
*  contents      : 測定値を文字列に変換する                             *
*  written by    : 高瀬  恵利(NKK unics Corp.)                          *
************************************************************************/
AnsiString SOKUTEIstrF(int i, int n, double val, int k)
{
    AnsiString str;

    if ( n == 0 ) {
        if ( i < 2 ) return("-");
        else return(" ");
    }
    else {
        if ( i < n ) {
			switch (k)
                    {
				case 1:
                    //小数点以下の桁数 1
                    str = FormatFloat( "#0.0",val);
					break;
				case 2:
                    //小数点以下の桁数 2
                    str = FormatFloat( "#0.00",val);
					break;
				case 3:
                    //小数点以下の桁数 3
                    str = FormatFloat( "#0.000",val);
					break;
                default :
                    //小数点以下の桁数 指定なし
                    str = FloatToStr(val);
                    break;

			}
            return(str);
        }
        else return(" ");
    }
}

/***********************************************************************
*  function name : AnsiString varstr(Variant str)                      *
*                  +--------------------------------------+            *
*          引  数  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | AnsiString | str Nullのとき " "      |            *
*                  |            | str Null以外   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant→AnsiString変換処理                         *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
AnsiString varstr(Variant str)
{
AnsiString sBuf;
        ShowMessage( str );
        if ( str.IsNull()) {
        //if ( str.IsEmpty()) {
            return(" ");
        }
        else {
            sBuf = str;
            return(sBuf);
        }

}
/***********************************************************************
*  function name : int varint(Variant str)                             *
*                  +--------------------------------------+            *
*          引  数  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  | int        | str Nullのとき 0        |            *
*                  |            | str Null以外   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant→int変換処理                                *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
int varint(Variant str)
{
//        if ( str.IsEmpty()) {
        if ( str.IsNull()) {
            return(0);
        }
        else {
            return(str);
        }

}
/***********************************************************************
*  function name : double varstr(Variant str)                          *
*                  +--------------------------------------+            *
*          引  数  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          戻り値  |  double    | str Nullのとき 0.0      |            *
*                  |            | str Null以外   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant→double変換処理                             *
*  written by    : 高瀬  恵利(NKK unics Corp.)                         *
***********************************************************************/
double vardouble(Variant str)
{
        if ( str.IsNull()) {
            return(0.0);
        }
        else {
            return(str);
        }

}

