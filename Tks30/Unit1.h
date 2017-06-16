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
#include <string.h>
#include "TKS30.h"

#include <DBTables.hpp>
#include <Db.hpp>
#include "NumberEdit.h"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
    TStatusBar *SBr1;
        TPanel *Panel9;
        TPanel *Panel1;
    TButton *BtnF01;
    TButton *BtnF02;
    TButton *BtnF03;
    TButton *BtnF04;
    TButton *BtnF05;
    TButton *BtnF06;
    TButton *BtnF07;
    TButton *BtnF08;
    TButton *BtnF09;
    TButton *BtnF10;
    TButton *BtnF11;
    TButton *BtnF12;
        TPanel *Panel77;
        TBevel *Bevel33;
    TStringGrid *SGr1;
        TBevel *Bevel1;
        TPanel *Panel8;
        TPanel *Panel10;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel22;
    TPanel *PnlNO;
    TEdit *Edt1;
    TEdit *Edt2;
    TEdit *Edt3;
    TEdit *Edt4;
    TEdit *Edt8;
    TComboBox *Cmb1;
        TDatabase *Database1;
        TQuery *Query_Kda2;
        TQuery *Query_Kda1;
    TQuery *Query1;
    TNumberEdit *Edt6;
    TNumberEdit *Edt7;
    TMaskEdit *EdtCOD;
	TNumberEdit *Edt5;
    TPanel *Panel11;
    TEdit *Edt9;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall BtnF04Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr1KeyPress(TObject *Sender, char &Key);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall Cmb1Change(TObject *Sender);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
    void __fastcall Read_Ini();    
private:	// ユーザー宣言
            
bool __fastcall AddData();
bool __fastcall DelData();
bool __fastcall CollectData(String OldKey);


public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
        AnsiString __fastcall DelSEPA(AnsiString sYMD);
        AnsiString __fastcall InsSEPA(AnsiString sYMD);
        void __fastcall ExtractCode(AnsiString str);
        AnsiString __fastcall StrReplace(AnsiString str, AnsiString a, AnsiString b);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------

#endif
