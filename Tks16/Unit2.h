//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TTabControl *TabControl1;
        TPanel *Panel12;
        TStringGrid *SGr1;
        TPanel *Panel9;
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
        TButton *BtnF01;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall SGr1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
        void __fastcall BtnF02Click(TObject *Sender);
        void __fastcall BtnF03Click(TObject *Sender);
        void __fastcall BtnF04Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
