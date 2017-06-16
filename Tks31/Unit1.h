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
#include "TKS31.h"
#include <Mask.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
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
        TPanel *Panel77;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TBevel *Bevel1;
        TBevel *Bevel3;
        TPanel *Panel8;
    TEdit *EdtTKSHIN;
        TPanel *Panel10;
    TEdit *EdtSLOT;
    TEdit *EdtELOT;
        TLabel *Label1;
        TBevel *Bevel4;
        TBevel *Bevel5;
    TPanel *Panel11;
    TLabel *Label2;
    TDatabase *Database1;
    TQuery *Query1;
    TMaskEdit *EdtYMD;
    TMaskEdit *EdtSYM;
    TMaskEdit *EdtEYM;
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        AnsiString __fastcall ConvKETA1(int keta,double n);
        AnsiString __fastcall ConvKETA2(int keta,double n,int SGM_K);
        void __fastcall ExtractCode(AnsiString str);
        AnsiString __fastcall DelSEPA(AnsiString sYMD);
        AnsiString __fastcall InsSEPA(AnsiString sYMD);
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif