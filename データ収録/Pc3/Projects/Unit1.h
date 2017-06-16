//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SharedMemory.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TListBox *ListBox1;
        TButton *Button6;
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
private:	// ユーザー宣言

public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
protected:
        void __fastcall OnNotifyWriteData(TMessage &Message);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_Notify_WriteData1, TMessage, OnNotifyWriteData)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
