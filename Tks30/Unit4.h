//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "NumberEdit.h"

//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TButton *Button1;
        TButton *Button2;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TNumberEdit *Edt_Number;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormScreenInit();
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Edt_NumberKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif