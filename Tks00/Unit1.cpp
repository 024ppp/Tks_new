//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int keyflag;    //1 : 左から1番目の番号
                //2 : 左から2番目の番号
                //3 : 左から3番目の番号


AnsiString keystr;

char TKS10FileName[MAX_PATH];
char TKS11FileName[MAX_PATH];
char TKS12FileName[MAX_PATH];
char TKS13FileName[MAX_PATH];
char TKS14FileName[MAX_PATH];
char TKS15FileName[MAX_PATH];
char TKS16FileName[MAX_PATH];
char TKS17FileName[MAX_PATH];
char TKS18FileName[MAX_PATH];
char TKS18BFileName[MAX_PATH]; //2002/12/05 検査項目追加（現物曲げ強さ）E｡Takase
char TKS19FileName[MAX_PATH];
char TKS20FileName[MAX_PATH];
char TKS21FileName[MAX_PATH];
char TKS30FileName[MAX_PATH];
char TKS31FileName[MAX_PATH];
char TKS40FileName[MAX_PATH];
char TKS50FileName[MAX_PATH];
char TKS51FileName[MAX_PATH];
char TKS52FileName[MAX_PATH];
char TKS53FileName[MAX_PATH];
char PC12FileName[MAX_PATH];
char PC34FileName[MAX_PATH];

char PC3FileName[MAX_PATH];
char PC4FileName[MAX_PATH];

//2009.03.13 MTS E.Takase [001]  ↓
char PC5FileName[MAX_PATH];
//2009.03.13 MTS E.Takase [001]  ↑


int KikiType;               // 機器番号PC1,2,3,4
int PGNo;
int iKojoKbn = 0 ;          // 工場区分

TForm1 *Form1;
void ClearLog();

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//Form作成時
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    ClearLog();
    keyflag = 3;
    keystr = "";
    Read_Ini();
    BtnSetEnable();

    //20161020 Y.Onishi
    //工場区分表示を追加
    if ( iKojoKbn == 0 ) {
       Panel1->Caption = "品質検査システム　本社";
    }
    else if ( iKojoKbn == 1 ) {
       Panel1->Caption = "品質検査システム　広陽";
    }
    else {
       Panel1->Caption = "品質検査システム";
    }
}
//---------------------------------------------------------------------------
//パスワード入力画面表示
void __fastcall TForm1::ButtonClick(TObject *Sender)
{
    if ( BtnTKS10->Focused() && BtnTKS10->Enabled == false )  return;
    if ( BtnTKS11->Focused() && BtnTKS11->Enabled == false )  return;
    if ( BtnTKS12->Focused() && BtnTKS12->Enabled == false )  return;
    if ( BtnTKS13->Focused() && BtnTKS13->Enabled == false )  return;
    if ( BtnTKS14->Focused() && BtnTKS14->Enabled == false )  return;
    if ( BtnTKS15->Focused() && BtnTKS15->Enabled == false )  return;
    if ( BtnTKS16->Focused() && BtnTKS16->Enabled == false )  return;
    if ( BtnTKS17->Focused() && BtnTKS17->Enabled == false )  return;
    if ( BtnTKS18->Focused() && BtnTKS18->Enabled == false )  return;
    if ( BtnTKS19->Focused() && BtnTKS19->Enabled == false )  return;
    if ( BtnTKS20->Focused() && BtnTKS20->Enabled == false )  return;
    if ( BtnTKS21->Focused() && BtnTKS21->Enabled == false )  return;
    if ( BtnTKS30->Focused() && BtnTKS30->Enabled == false )  return;
    if ( BtnTKS31->Focused() && BtnTKS31->Enabled == false )  return;
    if ( BtnTKS40->Focused() && BtnTKS40->Enabled == false )  return;
    if ( BtnTKS50->Focused() && BtnTKS50->Enabled == false )  return;
    if ( BtnTKS51->Focused() && BtnTKS51->Enabled == false )  return;
    if ( BtnTKS52->Focused() && BtnTKS52->Enabled == false )  return;
    if ( BtnTKS53->Focused() && BtnTKS53->Enabled == false )  return;
    //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
    if ( BtnTKS18B->Focused() && BtnTKS18B->Enabled == false )  return;


    //Form2->Edit1->Text = IntToStr(Form1->prgFlag);

    //パスワードチェックなし
    if (BtnTKS20->Focused() || BtnTKS21->Focused() || BtnTKS31->Focused()  ) {
        USER_COD=0;
        USER_NAM="";
        BUMO_COD="";
        BUMO_NAM="";
    	Form2->PGMStart(0);
        return;
    }
    keyflag = 3;
    keystr = "";
    Form2->Edit1->Text = "";
    //パスワードデフォルト値 01
    Form2->MaskEdit1->Text = "01";
    Form2->ShowModal();
}
//---------------------------------------------------------------------------
//ボタン フォーカス取得したとき
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    BtnGetFocus();
}
//---------------------------------------------------------------------------
//プログラム終了
void __fastcall TForm1::BtnTKS99Click(TObject *Sender)
{
    Close();
}

//---------------------------------------------------------------------------
//キーダウン時
//2002/12/05 現物曲げ強さに対応 E.Takase
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     // ステータスメッセージ

     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key){
        case VK_F12:
        case VK_RETURN:
                break;
        default:
                //今 キーダウンしたのは プログラムNOの左右どちらなのかを判断
                //if ( keyflag ) keyflag = false;
                //else keyflag = true;
                switch(keyflag){
                    case 1:
                        keyflag = 2;
                        break;
                    case 2:
                        if ( Key == 65 || Key == 66 ) {
                            keyflag = 3;
                        } else {
                            keyflag = 1;
                        }
                        break;
                    case 3:
                        keyflag = 1;
                        break;
                }
                keystr = keystr.SubString(1,2);
                break;
     }
     switch(Key){
        case VK_RETURN:
                if ( BtnTKS99->Focused()) BtnTKS99Click(Sender);
                else   ButtonClick(Sender);
                break;
        case VK_F12:
            if ( keyflag == 1 )  keystr = " ";
            else  keystr += " ";
            BtnTKS99Click(Sender);    break;

        //***********************
        //2002/12/05 E.Takase
        //case A:
        case 65:
            //曲げ強さ（18A）
            if ( keyflag == 3 ) {
                BtnSetFocus(keystr);
            } else {
                keyflag = 3;
            }
            break;

        //case B:
        case 66:
            //現物曲げ強さ（18A）
            if ( keyflag == 3 ) {
                keystr.Delete(3,1);
                keystr += "2";
                BtnSetFocus(keystr);
            } else {
                keyflag = 3;
            }
            break;


        //***********************

        //case VK_0:
        //case VK_NUMPAD0:
        case 96:
        case 48:
            if ( keyflag == 1 )  keystr = "00";
            else {
                keystr.Delete(2,1);
                keystr += "0";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_1:
        //case VK_NUMPAD1:
        case 97:
        case 49:
            if ( keyflag == 1 )  keystr = "10";
            else {
                keystr.Delete(2,1);
                keystr += "1";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_2:
        //case VK_NUMPAD2:
        case 98:
        case 50:
            if ( keyflag == 1 )  keystr = "20";
            else {
                keystr.Delete(2,1);
                keystr += "2";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_3:
        //case VK_NUMPAD3:
        case 99:
        case 51:
            if ( keyflag == 1 )  keystr = "30";
            else {
                keystr.Delete(2,1);
                keystr += "3";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_4:
        //case VK_NUMPAD4:
        case 100:
        case 52:
            if ( keyflag == 1 )  keystr = "40";
            else {
                keystr.Delete(2,1);
                keystr += "4";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_5:
        //case VK_NUMPAD5:
        case 101:
        case 53:
            if ( keyflag == 1 )  keystr = "50";
            else {
                keystr.Delete(2,1);
                keystr += "5";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_6:
        //case VK_NUMPAD6:
        case 102:
        case 54:
            if ( keyflag == 1 )  keystr = "60";
            else {
                keystr.Delete(2,1);
                keystr += "6";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_7:
        //case VK_NUMPAD7:
        case 103:
        case 55:
            if ( keyflag == 1 )  keystr = "70";
            else {
                keystr.Delete(2,1);
                keystr += "7";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_8:
        //case VK_NUMPAD8:
        case 104:
        case 56:
            if ( keyflag == 1 )  keystr = "80";
            else {
                keystr.Delete(2,1);
                keystr += "8";
            }
            BtnSetFocus(keystr);
            break;
        //case VK_9:
        //case VK_NUMPAD9:
        case 105:
        case 57:
            if ( keyflag == 1 )  keystr = "99";
            else {
                keystr.Delete(2,1);
                keystr += "9";
            }
            BtnSetFocus(keystr);
            break;
         // 次項
         case VK_DOWN:
         case VK_RIGHT:
            if ( BtnTKS10->Enabled == true && BtnTKS10->Focused())  BtnSetFocus("11");
            if ( BtnTKS11->Enabled == true && BtnTKS11->Focused())  BtnSetFocus("12");
            if ( BtnTKS12->Enabled == true && BtnTKS12->Focused())  BtnSetFocus("13");
            if ( BtnTKS13->Enabled == true && BtnTKS13->Focused())  BtnSetFocus("14");
            if ( BtnTKS14->Enabled == true && BtnTKS14->Focused())  BtnSetFocus("15");
            if ( BtnTKS15->Enabled == true && BtnTKS15->Focused())  BtnSetFocus("16");
            if ( BtnTKS16->Enabled == true && BtnTKS16->Focused())  BtnSetFocus("17");
            if ( BtnTKS17->Enabled == true && BtnTKS17->Focused())  BtnSetFocus("18");
            //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
            //if ( BtnTKS18->Enabled == true && BtnTKS18->Focused())  BtnSetFocus("19");
            if ( BtnTKS18->Enabled == true && BtnTKS18->Focused())  BtnSetFocus("182");
            if ( BtnTKS18B->Enabled == true && BtnTKS18B->Focused())  BtnSetFocus("19");

            if ( BtnTKS19->Enabled == true && BtnTKS19->Focused())  BtnSetFocus("20");
            if ( BtnTKS20->Enabled == true && BtnTKS20->Focused())  BtnSetFocus("21");
            if ( BtnTKS21->Enabled == true && BtnTKS21->Focused())  BtnSetFocus("30");
            if ( BtnTKS30->Enabled == true && BtnTKS30->Focused())  BtnSetFocus("31");
            if ( BtnTKS31->Enabled == true && BtnTKS31->Focused())  BtnSetFocus("40");
            if ( BtnTKS40->Enabled == true && BtnTKS40->Focused())  BtnSetFocus("50");
            if ( BtnTKS50->Enabled == true && BtnTKS50->Focused())  BtnSetFocus("51");
            if ( BtnTKS51->Enabled == true && BtnTKS51->Focused())  BtnSetFocus("52");
            if ( BtnTKS52->Enabled == true && BtnTKS52->Focused())  BtnSetFocus("53");
            if ( BtnTKS53->Enabled == true && BtnTKS53->Focused())  BtnSetFocus("99");
            if ( BtnTKS99->Enabled == true && BtnTKS99->Focused())  BtnSetFocus("10");
            break;
         // 前項
         case VK_UP:
         case VK_LEFT:
            if ( BtnTKS10->Enabled == true && BtnTKS10->Focused())  BtnSetFocus("99");
            if ( BtnTKS11->Enabled == true && BtnTKS11->Focused())  BtnSetFocus("10");
            if ( BtnTKS12->Enabled == true && BtnTKS12->Focused())  BtnSetFocus("11");
            if ( BtnTKS13->Enabled == true && BtnTKS13->Focused())  BtnSetFocus("12");
            if ( BtnTKS14->Enabled == true && BtnTKS14->Focused())  BtnSetFocus("13");
            if ( BtnTKS15->Enabled == true && BtnTKS15->Focused())  BtnSetFocus("14");
            if ( BtnTKS16->Enabled == true && BtnTKS16->Focused())  BtnSetFocus("15");
            if ( BtnTKS17->Enabled == true && BtnTKS17->Focused())  BtnSetFocus("16");
            if ( BtnTKS18->Enabled == true && BtnTKS18->Focused())  BtnSetFocus("17");
            //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
            //if ( BtnTKS19->Enabled == true && BtnTKS19->Focused())  BtnSetFocus("18");
            if ( BtnTKS18B->Enabled == true && BtnTKS18B->Focused())  BtnSetFocus("18");
            if ( BtnTKS19->Enabled == true && BtnTKS19->Focused())  BtnSetFocus("182");

            if ( BtnTKS20->Enabled == true && BtnTKS20->Focused())  BtnSetFocus("19");
            if ( BtnTKS21->Enabled == true && BtnTKS21->Focused())  BtnSetFocus("20");
            if ( BtnTKS30->Enabled == true && BtnTKS30->Focused())  BtnSetFocus("21");
            if ( BtnTKS31->Enabled == true && BtnTKS31->Focused())  BtnSetFocus("30");
            if ( BtnTKS40->Enabled == true && BtnTKS40->Focused())  BtnSetFocus("31");
            if ( BtnTKS50->Enabled == true && BtnTKS50->Focused())  BtnSetFocus("40");
            if ( BtnTKS51->Enabled == true && BtnTKS51->Focused())  BtnSetFocus("50");
            if ( BtnTKS52->Enabled == true && BtnTKS52->Focused())  BtnSetFocus("51");
            if ( BtnTKS53->Enabled == true && BtnTKS53->Focused())  BtnSetFocus("52");
            if ( BtnTKS99->Enabled == true && BtnTKS99->Focused())  BtnSetFocus("53");
            break;

        default :
            //if ( keyflag == 1 )  keystr = " ";
            //else {
            //    keystr.Delete(2,1);
            //    keystr += " ";
            //}
            //if ( keyflag == 1 ) {
                keystr = " ";
                keyflag = 3;
            //} else {
            //    keyflag = 1;
            //    keystr.Delete(2,1);
            //    keystr += " ";
            //}
        break;
     }
}
//---------------------------------------------------------------------------
//どのボタンにフォーカスをセットするのか
void __fastcall TForm1::BtnSetFocus(AnsiString str)
{
     switch(StrToInt(str)){
        case 10:  if( BtnTKS10->Enabled ) BtnTKS10->SetFocus();    break;
        case 11:  if( BtnTKS11->Enabled ) BtnTKS11->SetFocus();    break;
        case 12:  if( BtnTKS12->Enabled ) BtnTKS12->SetFocus();    break;
        case 13:  if( BtnTKS13->Enabled ) BtnTKS13->SetFocus();    break;
        case 14:  if( BtnTKS14->Enabled ) BtnTKS14->SetFocus();    break;
        case 15:  if( BtnTKS15->Enabled ) BtnTKS15->SetFocus();    break;
        case 16:  if( BtnTKS16->Enabled ) BtnTKS16->SetFocus();    break;
        case 17:  if( BtnTKS17->Enabled ) BtnTKS17->SetFocus();    break;
        case 18:  if( BtnTKS18->Enabled ) BtnTKS18->SetFocus();    break;
        //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
        case 182:  if( BtnTKS18B->Enabled ) BtnTKS18B->SetFocus();    break;
        case 19:  if( BtnTKS19->Enabled ) BtnTKS19->SetFocus();    break;
        case 20:  if( BtnTKS20->Enabled ) BtnTKS20->SetFocus();    break;
        case 21:  if( BtnTKS21->Enabled ) BtnTKS21->SetFocus();    break;
        case 30:  if( BtnTKS30->Enabled ) BtnTKS30->SetFocus();    break;
        case 31:  if( BtnTKS31->Enabled ) BtnTKS31->SetFocus();    break;
        case 40:  if( BtnTKS40->Enabled ) BtnTKS40->SetFocus();    break;
        case 50:  if( BtnTKS50->Enabled ) BtnTKS50->SetFocus();    break;
        case 51:  if( BtnTKS51->Enabled ) BtnTKS51->SetFocus();    break;
        case 52:  if( BtnTKS52->Enabled ) BtnTKS52->SetFocus();    break;
        case 53:  if( BtnTKS53->Enabled ) BtnTKS53->SetFocus();    break;
        case 99:  if( BtnTKS99->Enabled ) BtnTKS99->SetFocus();    break;

        break;
     }

}
//---------------------------------------------------------------------------
//どのボタンにフォーカスがあるのか判断して prgFlag に代入
//2001.05.21修正 StartFileName2を追加
//2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
void __fastcall TForm1::BtnGetFocus()
{
    if ( BtnTKS10->Focused() ) {
        PGNo = prgFlag = 10;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS10FileName);
        strcpy(StartFileName2,TKS10FileName);
        return;
    }
    if ( BtnTKS11->Focused() ) {
        PGNo = prgFlag = 11;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS11FileName);
        strcpy(StartFileName2,TKS11FileName);
        return;
    }
    if ( BtnTKS12->Focused() ) {
        PGNo = prgFlag = 12;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS12FileName);
        strcpy(StartFileName2,TKS12FileName);
        return;
    }
    if ( BtnTKS13->Focused() ) {
        PGNo = prgFlag = 13;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS13FileName);
        strcpy(StartFileName2,TKS13FileName);
        return;
    }
    if ( BtnTKS14->Focused() ) {
        PGNo = prgFlag = 14;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS14FileName);
        strcpy(StartFileName2,TKS14FileName);
        return;
    }
    if ( BtnTKS15->Focused() ) {
        PGNo = prgFlag = 15;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS15FileName);
        strcpy(StartFileName2,TKS15FileName);
        return;
    }
    if ( BtnTKS16->Focused() ) {
        PGNo = prgFlag = 16;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS16FileName);
        strcpy(StartFileName2,TKS16FileName);
        return;
    }
    if ( BtnTKS17->Focused() ) {
        PGNo = prgFlag = 17;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS17FileName);
        strcpy(StartFileName2,TKS17FileName);
        return;
    }
    if ( BtnTKS18->Focused() ) {
        PGNo = prgFlag = 18;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS18FileName);
        strcpy(StartFileName2,TKS18FileName);
        return;
    }
    //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
    if ( BtnTKS18B->Focused() ) {
        PGNo = prgFlag = 182;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS18BFileName);
        strcpy(StartFileName2,TKS18BFileName);
        return;
    }

    if ( BtnTKS19->Focused() ) {
        PGNo = prgFlag = 19;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS19FileName);
        strcpy(StartFileName2,TKS19FileName);
        return;
    }
    if ( BtnTKS20->Focused() ) {
        PGNo = prgFlag = 20;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS20FileName);
        strcpy(StartFileName2,TKS20FileName);
        return;
    }
    if ( BtnTKS21->Focused() ) {
        PGNo = prgFlag = 21;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS21FileName);
        strcpy(StartFileName2,TKS21FileName);
        return;
    }
    if ( BtnTKS30->Focused() ) {
        PGNo = prgFlag = 30;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS30FileName);
        strcpy(StartFileName2,TKS30FileName);
        return;
    }
    if ( BtnTKS31->Focused() ) {
        PGNo = prgFlag = 31;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS31FileName);
        strcpy(StartFileName2,TKS31FileName);
        return;
    }
    if ( BtnTKS40->Focused() ) {
        PGNo = prgFlag = 40;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS40FileName);
        strcpy(StartFileName2,TKS40FileName);
        return;
    }
    if ( BtnTKS50->Focused() ) {
        PGNo = prgFlag = 50;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS50FileName);
        strcpy(StartFileName2,TKS50FileName);
        return;
    }
    if ( BtnTKS51->Focused() ) {
        PGNo = prgFlag = 51;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS51FileName);
        strcpy(StartFileName2,TKS51FileName);
        return;
    }
    if ( BtnTKS52->Focused() ) {
        PGNo = prgFlag = 52;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS52FileName);
        strcpy(StartFileName2,TKS52FileName);
        return;
    }
    if ( BtnTKS53->Focused() ) {
        PGNo = prgFlag = 53;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,TKS53FileName);
        strcpy(StartFileName2,TKS53FileName);
        return;
    }
    if ( BtnTKS99->Focused() ) {
        PGNo = prgFlag = 99;  strcpy(StartFileName,StartPATH);  strcat(StartFileName,"\\");  strcat(StartFileName,"\0");
        return;
    }
    prgFlag = 0;
}

//---------------------------------------------------------------------------
//ボタンをEnableにする
//2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
void __fastcall TForm1::BtnSetEnable()
{
    if ( TKS10FileName[0] == '\0' ) BtnTKS10->Enabled = false;
    else                            BtnTKS10->Enabled = true;
    if ( TKS11FileName[0] == '\0' ) BtnTKS11->Enabled = false;
    else                            BtnTKS11->Enabled = true;
    if ( TKS12FileName[0] == '\0' ) BtnTKS12->Enabled = false;
    else                            BtnTKS12->Enabled = true;
    if ( TKS13FileName[0] == '\0' ) BtnTKS13->Enabled = false;
    else                            BtnTKS13->Enabled = true;
    if ( TKS14FileName[0] == '\0' ) BtnTKS14->Enabled = false;
    else                            BtnTKS14->Enabled = true;
    if ( TKS15FileName[0] == '\0' ) BtnTKS15->Enabled = false;
    else                            BtnTKS15->Enabled = true;
    if ( TKS16FileName[0] == '\0' ) BtnTKS16->Enabled = false;
    else                            BtnTKS16->Enabled = true;
    if ( TKS17FileName[0] == '\0' ) BtnTKS17->Enabled = false;
    else                            BtnTKS17->Enabled = true;
    if ( TKS18FileName[0] == '\0' ) BtnTKS18->Enabled = false;
    else                            BtnTKS18->Enabled = true;

    //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
    if ( TKS18BFileName[0] == '\0' ) BtnTKS18B->Enabled = false;
    else                             BtnTKS18B->Enabled = true;

    if ( TKS19FileName[0] == '\0' ) BtnTKS19->Enabled = false;
    else                            BtnTKS19->Enabled = true;
    if ( TKS20FileName[0] == '\0' ) BtnTKS20->Enabled = false;
    else                            BtnTKS20->Enabled = true;
    if ( TKS21FileName[0] == '\0' ) BtnTKS21->Enabled = false;
    else                            BtnTKS21->Enabled = true;
    if ( TKS30FileName[0] == '\0' ) BtnTKS30->Enabled = false;
    else                            BtnTKS30->Enabled = true;
    if ( TKS31FileName[0] == '\0' ) BtnTKS31->Enabled = false;
    else                            BtnTKS31->Enabled = true;
    if ( TKS40FileName[0] == '\0' ) BtnTKS40->Enabled = false;
    else                            BtnTKS40->Enabled = true;
    if ( TKS50FileName[0] == '\0' ) BtnTKS50->Enabled = false;
    else                            BtnTKS50->Enabled = true;
    if ( TKS51FileName[0] == '\0' ) BtnTKS51->Enabled = false;
    else                            BtnTKS51->Enabled = true;
    if ( TKS52FileName[0] == '\0' ) BtnTKS52->Enabled = false;
    else                            BtnTKS52->Enabled = true;
    if ( TKS53FileName[0] == '\0' ) BtnTKS53->Enabled = false;
    else                            BtnTKS53->Enabled = true;
}

//---------------------------------------------------------------------------
//INIファイル 読み込み プログラム名取得
//2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
void __fastcall TForm1::Read_Ini()
{
     int getlen1;
     char windir[MAX_PATH];	//Windows Dir
     char CurDir[MAX_PATH];	//Current Dir
     char tempo[MAX_PATH];

     //設定ファイル　( "windows\TKSMAIN.ini" or "winnt\TKSMAIN.ini" )
     char INIname[MAX_PATH];

     // 機器番号を読込む
     GetCurrentDirectory(256,CurDir);
     sprintf(INIname, "%s\\Tks.ini", CurDir);
     GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, INIname);
     KikiType = atoi(tempo);
     //2009.03.13 MTS E.Takase [001]  ↓
     //材料試験機（単独使用）は機器タイプ(KikiType)を5とする
     //if (KikiType <= 0 || KikiType > 4)
     //if (KikiType <= 0 || KikiType > 5)
     //2009.03.13 MTS E.Takase [001]  ↑
     //20160729 KikiType=6の追加（プレビュー用PC対応）
     if (KikiType <= 0 || KikiType > 6)
        KikiType = 1;

     // 工場区分を読み込む
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);	//Seed値
     iKojoKbn = atoi(tempo);

     /*Windowsﾃﾞｨﾚｸﾄﾘを検出*/
     getlen1 = GetWindowsDirectory((LPSTR)windir, sizeof(windir));
     if (getlen1 == 0){
     	ShowMessage("GetWindowsDirectory Fail");
     	return;
     }else {
     	//INIﾌｧｲﾙ名にﾊﾟｽを追加
     	wsprintf(INIname, "%s%s", windir, "\\TKSMAIN.ini");	//file name
     }

     // INIﾌｧｲﾙからの読み込み
     GetPrivateProfileString("FILE", "PATH", "", StartPATH, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS10", "", TKS10FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS11", "", TKS11FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS12", "", TKS12FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS13", "", TKS13FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS14", "", TKS14FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS15", "", TKS15FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS16", "", TKS16FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS17", "", TKS17FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS18", "", TKS18FileName, MAX_PATH, INIname);
     //2002/12/05 検査項目追加（現物曲げ強さ）E.Takase
     GetPrivateProfileString("FILE", "TKS18B", "", TKS18BFileName, MAX_PATH, INIname);

     GetPrivateProfileString("FILE", "TKS19", "", TKS19FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS20", "", TKS20FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS21", "", TKS21FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS30", "", TKS30FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS31", "", TKS31FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS40", "", TKS40FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS50", "", TKS50FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS51", "", TKS51FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS52", "", TKS52FileName, MAX_PATH, INIname);
     GetPrivateProfileString("FILE", "TKS53", "", TKS53FileName, MAX_PATH, INIname);

     GetPrivateProfileString("FILE", "PC12", "", tempo, MAX_PATH, INIname);
     strcpy(PC12FileName,StartPATH);
     strcat(PC12FileName,"\\");
     strcat(PC12FileName,tempo);

     GetPrivateProfileString("FILE", "PC34", "", tempo, MAX_PATH, INIname);
     strcpy(PC34FileName,StartPATH);
     strcat(PC34FileName,"\\");
     strcat(PC34FileName,tempo);

     GetPrivateProfileString("FILE", "PC3", "", tempo, MAX_PATH, INIname);
     strcpy(PC3FileName,StartPATH);
     strcat(PC3FileName,"\\");
     strcat(PC3FileName,tempo);

     GetPrivateProfileString("FILE", "PC4", "", tempo, MAX_PATH, INIname);
     strcpy(PC4FileName,StartPATH);
     strcat(PC4FileName,"\\");
     strcat(PC4FileName,tempo);

     //2009.03.13 MTS E.Takase [001]  ↓
     GetPrivateProfileString("FILE", "PC5", "", tempo, MAX_PATH, INIname);
     strcpy(PC5FileName,StartPATH);
     strcat(PC5FileName,"\\");
     strcat(PC5FileName,tempo);

     //2009.03.13 MTS E.Takase [001]  ↑


}


void ClearLog()
{
  char FileName[256];
  FILE *Logfn;
  SYSTEMTIME T_Time;
  char DirName[256];

  GetCurrentDirectory(sizeof(DirName), DirName);
  sprintf(FileName, "%s\\ShareMemory.Log", DirName);

  if ((Logfn = fopen(FileName, "w+")) != NULL) {
     GetLocalTime(&T_Time);

     fprintf(Logfn, "%04d/%02d/%02d  %02d:%02d:%02d  %s\n", (int)T_Time.wYear, (int)T_Time.wMonth, (int)T_Time.wDay,
					(int)T_Time.wHour, (int)T_Time.wMinute, (int)T_Time.wSecond, "KTRS Start");
     fclose(Logfn);
  }
}

//---------------------------------------------------------------------------



