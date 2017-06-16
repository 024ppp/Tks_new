//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TPanel *PnlP1;
    TPanel *Panel14;
    TPanel *PnlP2;
    TPanel *PnlP3;
    TPanel *PnlP4;
    TPanel *PnlP5;
    TPanel *Pnlp6;
    TPanel *PnlP7;
    TPanel *PnlP8;
    TPanel *PnlP9;
    TPanel *PnlP10;
    TPanel *PnlP11;
    TPanel *PnlP12;
    TPanel *PnlP13;
    TPanel *PnlP14;
    TPanel *PnlP15;
    TPanel *PnlP30;
    TPanel *PnlP29;
    TPanel *PnlP28;
    TPanel *PnlP27;
    TPanel *PnlP26;
    TPanel *PnlP25;
    TPanel *PnlP24;
    TPanel *PnlP23;
    TPanel *PnlP22;
    TPanel *PnlP21;
    TPanel *PnlP20;
    TPanel *PnlP19;
    TPanel *PnlP18;
    TPanel *PnlP17;
    TPanel *PnlP16;
    TPanel *Panel49;
    TPanel *Panel10;
    TPanel *Panel43;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TEdit *Edit7;
    TEdit *Edit8;
    TEdit *Edit9;
    TEdit *Edit10;
    TEdit *Edit11;
    TEdit *Edit12;
    TEdit *Edit13;
    TEdit *Edit14;
    TEdit *Edit15;
    TEdit *Edit16;
    TEdit *Edit17;
    TEdit *Edit18;
    TEdit *Edit19;
    TEdit *Edit20;
    TEdit *Edit21;
    TEdit *Edit22;
    TEdit *Edit23;
    TEdit *Edit24;
    TEdit *Edit25;
    TEdit *Edit26;
    TEdit *Edit27;
    TEdit *Edit28;
    TEdit *Edit29;
    TEdit *Edit30;
    TPanel *Panel9;
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
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
private:	// ユーザー宣言
        void __fastcall TForm3::SetEnabel(int) ;
        void __fastcall TForm3::SetInit(int) ;
        void __fastcall TForm3::InitEdt(TEdit *P_Edit, AnsiString) ;
        void __fastcall TForm3::IsEnabledEdt(TEdit *P_Edit, int flag);
        void __fastcall TForm3::SetData(void);
        void __fastcall TForm3::ToFirstData(void);
        void __fastcall TForm3::ToNextData(int);
        int __fastcall TForm3::SrchNextFEdit(int,int) ;

public:		// ユーザー宣言
    __fastcall TForm3(TComponent* Owner);
    AnsiString __fastcall StrReplace(AnsiString str, AnsiString a, AnsiString b);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
