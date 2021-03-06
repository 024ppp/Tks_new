//---------------------------------------------------------------------------
#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "NumberEdit.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TNumberEdit *Edt_Number;
        TButton *Button1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormScreenInit();
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Edt_NumberKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
