//---------------------------------------------------------------------------
#ifndef Unit11H
#define Unit11H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm11 : public TForm
{
__published:	// IDE 管理のコンポーネント
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
    TTabControl *TabControl1;
    TPanel *Panel12;
    TStringGrid *SGr1;
    TQuery *Query1;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF04Click(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ユーザー宣言
    int __fastcall CopyData_Serch(void);
    void __fastcall SetCopyData(void) ;
    
public:		// ユーザー宣言
    __fastcall TForm11(TComponent* Owner);
    bool __fastcall ChkCopyData(void);
    void __fastcall Botai_Cal2(int i);
    void __fastcall Kousetu_Cal2(int i);
    void __fastcall Teikou_Cal2(int i);
    int DataCopyFlag;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm11 *Form11;
//---------------------------------------------------------------------------
#endif
