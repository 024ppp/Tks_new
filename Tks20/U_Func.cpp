/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : U_Func.cpp                                          *
*  create        : 1999.10.18                                          *
*  update        :                                                     *
*  contents      : �֐�                                                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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
*          ��  ��  | int        | i                       |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | AnsiString | i=0  "  "               |            *
*                  |            | i=1  "�`"               |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : "�`"�����邩���Ȃ���                            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
AnsiString Kara(int i)
{
        if ( i == 0 ) {
            return("  ");
        }
        else {
            return( "�`" );
        }

}
/***********************************************************************
*  function name : double DivAB(double a, double b)                    *
*                  +--------------------------------------+            *
*          ��  ��  | double     | a, b                    |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | double     | a / b                   |            *
*                  |            | a=0 �܂��� b=0 �Ȃ� 0   |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : a / b �i0������ӂ����j                             *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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
*          ��  ��  | int        | i   ����ԍ�            |            *
*                  | int        | n   ����敪            |            *
*                  | int        | val ����l              |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | AnsiString | ���肵�Ȃ� "-" 1,2�s��  |            *
*                  |            | ���肵�Ȃ� " " 3�s�ڈȍ~|            *
*                  |            | ���肷��   val �����ϊ� |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ����l�𕶎���ɕϊ�����                            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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
*          ��  ��  | int        | i   ����ԍ�            |             *
*                  | int        | n   ����敪            |             *
*                  | double     | val ����l              |             *
*                  | int        | k   �����_�ȉ��̌���    |             *
*                  +--------------------------------------+             *
*                  +--------------------------------------+             *
*          �߂�l  | AnsiString | ���肵�Ȃ� "-" 1,2�s��  |             *
*                  |            | ���肵�Ȃ� " " 3�s�ڈȍ~|             *
*                  |            | ���肷��   val �����ϊ� |             *
*                  +--------------------------------------+             *
*  create        : 1999.10                                              *
*  update        :                                                      *
*  contents      : ����l�𕶎���ɕϊ�����                             *
*  written by    : ����  �b��(NKK unics Corp.)                          *
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
                    //�����_�ȉ��̌��� 1
                    str = FormatFloat( "#0.0",val);
					break;
				case 2:
                    //�����_�ȉ��̌��� 2
                    str = FormatFloat( "#0.00",val);
					break;
				case 3:
                    //�����_�ȉ��̌��� 3
                    str = FormatFloat( "#0.000",val);
					break;
                default :
                    //�����_�ȉ��̌��� �w��Ȃ�
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
*          ��  ��  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | AnsiString | str Null�̂Ƃ� " "      |            *
*                  |            | str Null�ȊO   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant��AnsiString�ϊ�����                         *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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
*          ��  ��  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  | int        | str Null�̂Ƃ� 0        |            *
*                  |            | str Null�ȊO   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant��int�ϊ�����                                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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
*          ��  ��  | Variant    | str                     |            *
*                  +--------------------------------------+            *
*                  +--------------------------------------+            *
*          �߂�l  |  double    | str Null�̂Ƃ� 0.0      |            *
*                  |            | str Null�ȊO   str      |            *
*                  +--------------------------------------+            *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : Variant��double�ϊ�����                             *
*  written by    : ����  �b��(NKK unics Corp.)                         *
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

