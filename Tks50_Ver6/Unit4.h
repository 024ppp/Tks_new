//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "NumberEdit.h"
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TButton *Button1;
    TButton *Button2;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TNumberEdit *EdtNum;
    TLabel *Label4;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EdtNumKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ユーザー宣言
public:		// ユーザー宣言
    __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
