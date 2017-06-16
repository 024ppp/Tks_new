//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

// 画面ｺﾝﾄﾛｰﾙ保存変数
TEdit *pEdtMEMO[30] ;    //  備考入力のｺﾝﾄﾛｰﾙを保存

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//画面作成時の処理 2002/11/07 E.Takase
void __fastcall TForm3::FormCreate(TObject *Sender)
{
    // 画面各ｺﾝﾄﾛｰﾙを配列変数へ保存する
    pEdtMEMO[0] =  Form3->Edit1 ;
    pEdtMEMO[1] =  Form3->Edit2 ;
    pEdtMEMO[2] =  Form3->Edit3 ;
    pEdtMEMO[3] =  Form3->Edit4 ;
    pEdtMEMO[4] =  Form3->Edit5 ;
    pEdtMEMO[5] =  Form3->Edit6 ;
    pEdtMEMO[6] =  Form3->Edit7 ;
    pEdtMEMO[7] =  Form3->Edit8 ;
    pEdtMEMO[8] =  Form3->Edit9 ;
    pEdtMEMO[9] =  Form3->Edit10 ;
    pEdtMEMO[10] =  Form3->Edit11 ;
    pEdtMEMO[11] =  Form3->Edit12 ;
    pEdtMEMO[12] =  Form3->Edit13 ;
    pEdtMEMO[13] =  Form3->Edit14 ;
    pEdtMEMO[14] =  Form3->Edit15 ;
    pEdtMEMO[15] =  Form3->Edit16 ;
    pEdtMEMO[16] =  Form3->Edit17 ;
    pEdtMEMO[17] =  Form3->Edit18 ;
    pEdtMEMO[18] =  Form3->Edit19 ;
    pEdtMEMO[19] =  Form3->Edit20 ;
    pEdtMEMO[20] =  Form3->Edit21 ;
    pEdtMEMO[21] =  Form3->Edit22 ;
    pEdtMEMO[22] =  Form3->Edit23 ;
    pEdtMEMO[23] =  Form3->Edit24 ;
    pEdtMEMO[24] =  Form3->Edit25 ;
    pEdtMEMO[25] =  Form3->Edit26 ;
    pEdtMEMO[26] =  Form3->Edit27 ;
    pEdtMEMO[27] =  Form3->Edit28 ;
    pEdtMEMO[28] =  Form3->Edit29 ;
    pEdtMEMO[29] =  Form3->Edit30 ;

    //コントロールの無効
    SetEnabel(0);
    //コントロールの初期化
    SetInit(0);

}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormActivate(TObject *Sender){
    //コントロールの無効
    SetEnabel(0);
    //コントロールの初期化
    SetInit(0);
    //コントロールにデータセット
    SetData();
    //最初のコントロールに移動
    ToFirstData();
    
}
//---------------------------------------------------------------------------
//備考データを画面へセット
void __fastcall TForm3::SetData(void)
{
    int i;
	// 備考ﾃﾞｰﾀを画面へセット
	int flag = 0;
	for( i=0; i<30; i++ )
	{
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
			IsEnabledEdt( pEdtMEMO[i], 1 );
			pEdtMEMO[i]->Text =  Trim(KD91Data[i].MEMO);
		}
	}
}
//---------------------------------------------------------------------------
//入力ｺﾝﾄﾛｰﾙを初期化する
void __fastcall TForm3::SetInit(int flag)
{
    int i ;

    // ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNO及び測定個数N
    for( i=0; i<30; i++ ){
        InitEdt(pEdtMEMO[i], "");
    }
}
//---------------------------------------------------------------------------
//入力ｺﾝﾄﾛｰﾙを無効にする
void __fastcall TForm3::SetEnabel(int flag )
{
    int i;
    //画面を開く時に、入力ｺﾝﾄﾛｰﾙを無効にする
    for( i=0; i<30; i++ )
    {
        IsEnabledEdt( pEdtMEMO[i], 0 );
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm3::InitEdt(TEdit *P_Edit, AnsiString Str)
{
       P_Edit->Text = Str ;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::IsEnabledEdt(TEdit *P_Edit, int flag)
{
      // EditﾎﾞﾀﾝをEnabled or Unenabled
      //  flag == 1   true    flag == 0  false
       if( flag == 1 ){
           P_Edit->Enabled = true ;
           P_Edit->Color = clWindow;
       }else {
           P_Edit->Enabled = false ;
           P_Edit->Color = 0x00E0E0E0;
      }

}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F1:   break;
         case VK_F2:   break;
         case VK_F3:   break;
         case VK_F4:   break;
         case VK_F5:   break;
         case VK_F6:   break;
         case VK_F7:   break;

         case VK_F9:   break;
         case VK_F8:   break;
         case VK_F10:  break;
         case VK_F11:  BtnF11Click(Sender);
                       break;
         case VK_F12:  BtnF12Click(Sender); 
                       break;

         case VK_RETURN:
                       if ( BtnF11->Focused() ) { BtnF11Click(Sender); }
                       if ( BtnF12->Focused() ) { BtnF12Click(Sender); }
                       ToNextData(1);
               		   break;
         case VK_UP:   break;

         case VK_LEFT: break;
         case VK_DOWN:
                       if ( BtnF11->Focused() ) { BtnF12->SetFocus(); }
                       if ( BtnF12->Focused() ) { ToFirstData(); }
                       ToNextData(0);
               		   break;
         case VK_RIGHT:break;
     }

}
//---------------------------------------------------------------------------
//最初のコントロールへ移動
void __fastcall TForm3::ToFirstData(void)
{
    int i;
    int n;
    int iPos;
    int iFlag;



    iFlag = 0;
    for( i=0; i<30; i++ )
    {
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            iPos = SrchNextFEdit(i,1);
            if ( iPos >= 0 ) {
                pEdtMEMO[iPos]->SetFocus();
                return;
            }

		}
    }


}

//---------------------------------------------------------------------------
//次のコントロールへ移動
void __fastcall TForm3::ToNextData(int KeyFlag)
{
    int i;
    int n;
    int iPos;
    int iFlag;



    iFlag = 0;
    for( i=0; i<30; i++ )
    {
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if(  pEdtMEMO[i]->Focused() ) {
                iPos = SrchNextFEdit(i+1,KeyFlag);
                if ( iPos >= 0 ) {
                    pEdtMEMO[iPos]->SetFocus();
                    return;
                } else {
                    BtnF11->SetFocus();
                    return;
                }

            }

		}
    }


}
//---------------------------------------------------------------------------

int __fastcall TForm3::SrchNextFEdit(int n,int KeyFlag)
{
    int i;

    if ( 0 <= n && n < 30 && pEdtMEMO[n]->Enabled ) {
        return n;
    }

    if ( n >= 30 ) {
        n = 0;
    }

    if ( n < 0 ) {
        n = 30;
    }

    for( i=n; i<30; i++ )
    {
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if( pEdtMEMO[i]->Enabled ) {
                return i;

            }

		}
    }

    if ( KeyFlag == 0 ) {
    //↓の場合
        for( i=0; i<n; i++ )
        {
		    //ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		    if( KD91Data[i].SAMPLE_P == -1 )
		    {

   	        }else{
                if( pEdtMEMO[i]->Enabled ) {
                return i;

                }

		    }
        }
    }

    return -1;
}
//---------------------------------------------------------------------------
//str内にaの文字列が含まれている場合、bに置換して返す
AnsiString __fastcall TForm3::StrReplace(AnsiString str, AnsiString a, AnsiString b)
{
    int i;
    AnsiString tmpStr;

    tmpStr = str;
    while ( 1 ) {
        i = tmpStr.AnsiPos(a);
        if ( i <= 0 ) {
            return ( tmpStr );
        }

        tmpStr.Delete(i, a.Length());
        tmpStr.Insert(b, i);
    }

    return(tmpStr);
}
//---------------------------------------------------------------------------
//戻るボタンクリック時 画面を閉じる 2002/11/07 E.Takase
void __fastcall TForm3::BtnF12Click(TObject *Sender)
{
    //Close();
    Form3->ModalResult = -1;


}
//---------------------------------------------------------------------------
//OKボタンクリック時 変数に入力データ保存し画面を閉じる 2002/11/07 E.Takase
void __fastcall TForm3::BtnF11Click(TObject *Sender)
{
    int i;
	// 備考ﾃﾞｰﾀを画面へセット
	int flag = 0;
	for( i=0; i<30; i++ )
	{
		//ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝNOがないの場合
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if ( Trim(pEdtMEMO[i]->Text) == "" ) {
                KD91Data[i].MEMO = " ";
            } else {
                KD91Data[i].MEMO = StrReplace(Trim(pEdtMEMO[i]->Text), "'", "_");
            }
		}
	}

    //Close();
    Form3->ModalResult = 1;

}
//---------------------------------------------------------------------------

