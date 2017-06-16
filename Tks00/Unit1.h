//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Grids.hpp>
#include <Graphics.hpp>
#include <Windows.h>
#include <string.h>


#define MAX_PATH 256
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TStatusBar *SBr1;
        TPanel *Panel9;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TImage *Image1;
    TButton *BtnTKS10;
    TButton *BtnTKS11;
    TButton *BtnTKS12;
    TButton *BtnTKS13;
    TButton *BtnTKS14;
    TButton *BtnTKS15;
    TButton *BtnTKS16;
    TButton *BtnTKS17;
    TButton *BtnTKS18;
    TButton *BtnTKS19;
    TButton *BtnTKS99;
    TButton *BtnTKS52;
    TButton *BtnTKS51;
    TButton *BtnTKS50;
    TButton *BtnTKS40;
    TButton *BtnTKS31;
    TButton *BtnTKS30;
    TButton *BtnTKS20;
    TButton *BtnTKS53;
    TBevel *Bevel1;
    TBevel *Bevel2;
    TBevel *Bevel3;
    TBevel *Bevel4;
    TBevel *Bevel5;
    TBevel *Bevel6;
    TBevel *Bevel7;
	TButton *BtnTKS21;
    TButton *BtnTKS18B;
        void __fastcall ButtonClick(TObject *Sender);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnTKS99Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
private:	// ユーザー宣言
            int prgFlag;    //どのプログラムを起動するか
            AnsiString USRNAM;    //ユーザ名
            AnsiString USRPASSWORD;    //パスワード

            void __fastcall BtnGetFocus();
            void __fastcall BtnSetFocus(AnsiString str);
            void __fastcall BtnSetEnable();
            void __fastcall Read_Ini();

public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
            char StartFileName[MAX_PATH];
            char StartFileName2[MAX_PATH]; //2001.05.21追加
            char StartPATH[MAX_PATH];

            int     USER_COD;
            String  USER_NAM;
            String  BUMO_COD;
            String  BUMO_NAM;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern int iKojoKbn ;            //工場区分
//---------------------------------------------------------------------------
#endif
