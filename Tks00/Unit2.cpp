//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <DBTables.hpp>
#include <winbase.h>
#include <shellapi.h>

extern int KikiType;               // 機器番号PC1,2,3,4
extern int PGNo;

extern char PC12FileName[MAX_PATH];
extern char PC34FileName[MAX_PATH];

extern char PC3FileName[MAX_PATH];
extern char PC4FileName[MAX_PATH];

//2009.03.13 MTS E.Takase [001]  ↓
extern char PC5FileName[MAX_PATH];
//2009.03.13 MTS E.Takase [001]  ↑

int ExeFlag = 0;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォームキーダウン時
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key){
         // 前項
         case VK_UP:
         case VK_LEFT:
                if( Edit1->Focused() && Edit1->SelStart == 0 && Edit1->SelLength == 0 ){
                    Button2->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == 0 && MaskEdit1->SelLength == 0 ){
                    Edit1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Button1->SetFocus();
                    break;
                }
                break;
         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if( Edit1->Focused() && Edit1->SelStart == Edit1->Text.Length() && Edit1->SelLength == 0 ){
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() && MaskEdit1->SelStart == MaskEdit1->Text.Length() && MaskEdit1->SelLength == 0 ){
                    Button1->SetFocus();
                    break;
                }
                if( Button1->Focused() ) {
                    Button2->SetFocus();
                    break;
                }
                if( Button2->Focused() ) {
                    Edit1->SetFocus();
                    break;
                }
                break;

         case VK_RETURN:
                if( Edit1->Focused() ) {
                    MaskEdit1->SetFocus();
                    break;
                }
                if( MaskEdit1->Focused() ) {
                    //Button1->SetFocus();
                    OkClick(Sender);
                    break;
                }
                if( Button1->Focused() ) {
                    OkClick(Sender);
                    break;
                }
                if( Button2->Focused() ) {
                    CancleClick(Sender);
                    break;
                }

                break;
        case VK_ESCAPE:
        //case 27:
                CancleClick(Sender);
                break;
        default:
                break;
     }

}
//---------------------------------------------------------------------------
//キャンセル
void __fastcall TForm2::CancleClick(TObject *Sender)
{
    //ShowMessage("CancleClick");
    Close();
    Form1->SetFocus();
}
//---------------------------------------------------------------------------
//パスワードＯＫなら プログラムを起動
void __fastcall TForm2::OkClick(TObject *Sender)
{
    int PassFlag;

    //ユーザー名、パスワードのチェック
    PassFlag = PasswordCheck();
    PGMStart(PassFlag);

}


//---------------------------------------------------------------------------
//プログラムの起動
void __fastcall TForm2::PGMStart(int PassFlag)
{
    bool retDLL;
    bool wReturn;
    char curpass[MAX_PATH];
    STARTUPINFO si;
    AnsiString str;
    PROCESS_INFORMATION pi;
    SHELLEXECUTEINFO sei;
    int StartFlag;   // 0: 測定プログラム起動しない;  1: PC12プログラム起動する
                     // 2: PC34プログラム起動する
    HWND thWnd;
    int SleepTime;


    HANDLE hMutex = NULL; //2001.05.21　追加
    bool bRtn;            //2001.05.21　追加
    AnsiString tmpstr;    //2001.05.21　追加
    AnsiString tmpstr2;   //2001.05.21　追加


    if (ExeFlag == 1)
       return;

    strcpy(curpass , Form1->StartPATH);
    strcat(curpass, "\\");
    str = IntToStr(Form1->USER_COD) + "," + Form1->USER_NAM + "," + Form1->BUMO_COD + "," + Form1->BUMO_NAM;


    switch(PassFlag){
        case 0:
             // 収録データプログラム起動
             StartFlag = 0;
             switch (PGNo) {
             	case 10:
             	case 11:
             	case 12:
                case 15:
                  	if (KikiType == 1 || KikiType == 2)
                     	   StartFlag = 1;
                        break;

                case 13:
                  	//if (KikiType == 3 || KikiType == 4)
                     	   //StartFlag = 2;
                        if (KikiType == 3)
                           StartFlag = 3;
                        break;
             	case 14:
                        if (KikiType == 5)
                           StartFlag = 5;
                        break;
             	case 19:
                  	/*if (KikiType == 3 || KikiType == 4)
                     	   StartFlag = 2;
                        else if (KikiType == 5)
                           StartFlag = 5;
                        break; */
                        if (KikiType == 5)
                           StartFlag = 5;
                        break;
             	case 17:
                  	if (KikiType == 1 || KikiType == 2)
                     	   StartFlag = 1;
                  	//else if (KikiType == 3 || KikiType == 4)
                        else if (KikiType == 4)
                     	     StartFlag = 4;
                        break;
             	case 18:
             	case 182:
                  	if (KikiType == 1 || KikiType == 2)
                     	   StartFlag = 1;
                        else if (KikiType == 5)
                           StartFlag = 5;
                  	else
                           //20161128 Y.Onishi
                           //Kikitype=6で18A,18B起動時、エクスプローラが開くバグを修正
                     	   //StartFlag = 2;
                        break;
             	}

                /* PC12,3,4,5の起動部分 */
                //PC12
             	if (StartFlag >= 1) {
                   ExeFlag = 1;
                   ZeroMemory( &sei, sizeof(sei) );
                   sei.cbSize = sizeof(sei);
                   sei.fMask = SEE_MASK_NOCLOSEPROCESS;
                   //sei.hwnd = hWnd;
                   sei.lpVerb = "open";
                   if (StartFlag == 1) {
                       sei.lpFile = PC12FileName;
                       SleepTime = 0;
                       while ((thWnd = FindWindow("WSockWClass", "TRIS ： 中間検査(PC1)")) != NULL) {
                             Sleep(1000);
                             SleepTime += 1000;
                             if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します 2000.8.10
                                DestroyWindow(thWnd);
                                Sleep(1000);
                                break;
                             }
                       }
                //PC3
                } else if (StartFlag == 3) {
                   sei.lpFile = PC3FileName;
                   SleepTime = 0;
                   while ((thWnd = FindWindow("WSockWClass", "TRIS：中間検査(PC3)")) != NULL) {
                         Sleep(1000);
                         SleepTime += 1000;
                         if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します 2000.8.10
                            DestroyWindow(thWnd);
                            Sleep(1000);
                            break;
                         }
                   }
                //PC4
                } else if (StartFlag == 4) {
                   sei.lpFile = PC4FileName;
                   SleepTime = 0;
                   while ((thWnd = FindWindow("WSockWClass", "TRIS：中間検査(PC4)")) != NULL) {
                         Sleep(1000);
                         SleepTime += 1000;
                         if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します 2000.8.10
                            DestroyWindow(thWnd);
                            Sleep(1000);
                            break;
                         }
                   }
                //PC5
                } else if (StartFlag == 5) {
                   sei.lpFile = PC5FileName;
                   SleepTime = 0;
                   while ((thWnd = FindWindow("WSockWClass", "TRIS：中間検査(PC5)")) != NULL) {
                         Sleep(1000);
                         SleepTime += 1000;
                         if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します 2000.8.10
                            DestroyWindow(thWnd);
                            Sleep(1000);
                            break;
                         }
                   }


                } else {
                   //20160729 KikiType=6の追加により、コメントアウト
                   /* sei.lpFile = PC34FileName;
                   SleepTime = 0;
                   while ((thWnd = FindWindow("WSockWClass", "TRIS：中間検査(PC3,4)")) != NULL) {
                         Sleep(1000);
                         SleepTime += 1000;
                         if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します 2000.8.10
                            DestroyWindow(thWnd);
                            Sleep(1000);
                            break;
                         }
                   } */                   
                }

                	sei.nShow = SW_SHOWMINIMIZED ;
                	//sei.nShow = SW_SHOWNORMAL;
                	sei.lpDirectory = curpass;
                	sei.lpParameters = str.c_str();
                        retDLL = ShellExecuteEx(&sei);
                	Sleep(1000);
             }

            	//プログラムの起動

                //***********************************************************************************
                //***********************************************************************************
                //2001.05.21追加
                //2重起動のチェック
				SleepTime = 0;
				tmpstr = Form1->StartFileName2;
				tmpstr2 = "品質検査システム[" + tmpstr.SubString(1,tmpstr.Length()-4) + "]";
				//while ((hMutex = FindWindow(NULL, tmpstr2.c_str())) != NULL) {
				//      Sleep(1000);
				//      SleepTime += 1000;
				//      if (SleepTime > 5000) {  // 5秒以降、指定されたプログラムを破棄します
                //         bRtn = PostMessage(hMutex,WM_CLOSE,0,0);
				//         Sleep(1000);
				//         break;
				//      }
				//}

				if ((hMutex = FindWindow(NULL, tmpstr2.c_str())) != NULL) {
				      //Sleep(1000);
                      bRtn = PostMessage(hMutex,WM_CLOSE,0,0);
				      Sleep(1000);
                      //CloseHandle(hMutex);
				}

                //***********************************************************************************
                //***********************************************************************************

    		    ZeroMemory( &sei, sizeof(sei) );
    		    sei.cbSize = sizeof(sei);
    		    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    		    //sei.hwnd = hWnd;
    		    sei.lpVerb = "open";
    		    sei.lpFile = Form1->StartFileName;
    		    sei.nShow = SW_SHOWNORMAL;
            	sei.lpDirectory = curpass;
            	sei.lpParameters = str.c_str();
	    		retDLL = ShellExecuteEx(&sei);

            	if (StartFlag >= 1) {
               	Sleep(1000);
               	ExeFlag = 0;
            	}

           		Close();
            	Form1->SetFocus();
            	break;

        case 1:
            ShowMessage("ユーザ名を入力してください");
            Edit1->SetFocus();
            break;

        case 2:
            ShowMessage("ユーザ名が間違っています");
            Edit1->SetFocus();
            break;

        case 3:
            ShowMessage("パスワードが間違っています");
            MaskEdit1->SetFocus();
            break;

        case 4:
            ShowMessage("パスワードが登録されていません");
            MaskEdit1->SetFocus();
            break;

        default :
            break;

     }
}
//---------------------------------------------------------------------------
//パスワードのチェック
int __fastcall TForm2::PasswordCheck()
{
     AnsiString sBuf;

     //ユーザー名検索

     if ( Edit1->Text.IsEmpty() ) return(1);

	 Form1->USER_COD = 0;
	 Form1->USER_NAM = "";
	 Form1->BUMO_COD = "";
	 Form1->BUMO_NAM = "";

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "SELECT TANSYA, TANNAM, SZKBSY FROM SM12S WHERE  TANSYA = ";
     sBuf += Edit1->Text;

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
        return(2);
     }

     Form1->USER_COD = StrToInt(Query1->FieldValues["TANSYA"]);
     Form1->USER_NAM = Query1->FieldValues["TANNAM"];
     Form1->BUMO_COD = Query1->FieldValues["SZKBSY"];

     //部署名検索
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     sBuf = "SELECT BSYCOD, BSYNAM FROM SM13S WHERE BSYCOD = '";
     sBuf += Form1->BUMO_COD + "'";

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
         Form1->BUMO_NAM = "";
     } else {
         Form1->BUMO_NAM = Query1->FieldValues["BSYNAM"];
     }

     //パスワードの検索
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     sBuf = "SELECT USRID, PASSWD FROM KM11 WHERE USRID = ";
     sBuf = sBuf + IntToStr(Form1->USER_COD);
     sBuf = sBuf + " and ukoymd<='" + FormatDateTime("yyyymmdd",Date()) +"'";   // 有効年月日の判断を追加

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //検索結果 ０件
        return(4);
     }
     //パスワードの比較
     if ( MaskEdit1->Text != Query1->FieldValues["PASSWD"] ) {
        //パスワード間違っている
        return(3);
     }
     return(0);
}

//---------------------------------------------------------------------------
//フォームアクティブ時
void __fastcall TForm2::FormActivate(TObject *Sender)
{
     Edit1->SetFocus();

}
//---------------------------------------------------------------------------
//フォーム作成時
void __fastcall TForm2::FormCreate(TObject *Sender)
{
    Database1->Open();

}
//---------------------------------------------------------------------------




void __fastcall TForm2::FormKeyPress(TObject *Sender, char &Key)
{
     switch(Key){
         // 前項
         case VK_RETURN:
                Key = 0;
                break;
     }

}
//---------------------------------------------------------------------------

