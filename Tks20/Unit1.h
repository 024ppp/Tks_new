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
#include <Db.hpp>
#include <DBTables.hpp>
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
        TButton *BtnF08;
        TButton *BtnF07;
        TButton *BtnF06;
        TButton *BtnF05;
        TButton *BtnF12;
        TButton *BtnF11;
        TButton *BtnF10;
        TButton *BtnF09;
        TBevel *Bevel2;
        TPanel *Panel_KENYMD;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TBevel *Bevel1;
        TBevel *Bevel3;
        TPanel *Panel_DTKSHIN;
        TEdit *Edt_DTKSHIN;
        TPanel *Panel_LOT;
        TEdit *Edt_StartLOT;
        TEdit *Edt_EndLOT;
        TLabel *Label1;
        TBevel *Bevel4;
        TBevel *Bevel5;
    TQuery *Q_KM01;
    TDatabase *Database1;
    TDatabase *Database2;
    TQuery *Query2;
    TQuery *Q_TW_TKS21PR;
    TQuery *Q_Work;
    TProgressBar *ProgressBar1;
    TQuery *Query3;
    TPanel *Panel_SOKU;
    TLabel *Label2;
    TQuery *Q_STRS;
    TMaskEdit *Edt_KENYMD;
    TMaskEdit *Edt_StartSOKU;
    TMaskEdit *Edt_EndSOKU;
    TEdit *Edt_DTKSCOD;
    TPanel *Panel_DTKSCOD;
    TQuery *Q_TW_UPDCHR;
        TPanel *Panel8;
        TGroupBox *GroupBox1;
        TRadioButton *RadioHON;
        TRadioButton *RadioKOU;
        TRadioButton *RadioRYO;
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    //void __fastcall Edt_KENYMDKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    //void __fastcall Edt_DTKSHINKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    //void __fastcall Edt_StartLOTKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    //void __fastcall Edt_EndLOTKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    //void __fastcall Edt_StartSOKUKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    //void __fastcall Edt_EndSOKUKeyDown(TObject *Sender, WORD &Key,
    //      TShiftState Shift);
    void __fastcall Edt_StartLOTClick(TObject *Sender);
    void __fastcall Edt_KENYMDClick(TObject *Sender);
    void __fastcall Edt_DTKSHINClick(TObject *Sender);
    void __fastcall Edt_EndLOTClick(TObject *Sender);
    void __fastcall Edt_StartSOKUClick(TObject *Sender);
    void __fastcall Edt_EndSOKUClick(TObject *Sender);
    void __fastcall Edt_DTKSCODClick(TObject *Sender);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
	void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall Read_Ini();
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
        void __fastcall ExtractCode(AnsiString str);
        AnsiString __fastcall DelSEPA(AnsiString sYMD);
        AnsiString __fastcall InsSEPA(AnsiString sYMD);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
