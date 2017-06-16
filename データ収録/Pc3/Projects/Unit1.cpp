//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "Unit1.h"

#define WM_Notify_WriteData WM_USER + 3040	// 相手プロセスに通知します
#define WM_Notify_WriteData1 WM_USER + 3041	// 相手プロセスに通知します

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
char SharedBuff[BUFFERSIZE];
char tempo[1024];

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 int ret;

     // シェアメモリ作成
     ret = SharedMemory_Open(Handle, "SHARE_TRIS1", 1);
     if (ret < 0) {
     	MessageBox(Handle, "Open SharedMemory Error", "", MB_OK);
     	return;
     }

     ret = SharedMemory_Open(Handle, "SHARE_TRIS2", 2);
     if (ret < 0) {
     	MessageBox(Handle, "Open SharedMemory Error", "", MB_OK);
     	return;
     }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
     SharedMemory_Write(1, 0, "EXIT", 4);
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
     sprintf(tempo, "CONNECT 7");
     SharedMemory_Write(1, 0, tempo, strlen(tempo));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
     SharedMemory_Close(1);
     SharedMemory_Close(2);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OnNotifyWriteData(TMessage &Message)
{
 int nNumber;

     nNumber = SharedMemory_Read(2, SharedBuff);
     if (nNumber > 0) {
     	ListBox1->Items->Add(SharedBuff);
     }
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
     sprintf(tempo, "CONNECT 8");
     SharedMemory_Write(1, 0, tempo, strlen(tempo));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
     sprintf(tempo, "CONNECT 9");
     SharedMemory_Write(1, 0, tempo, strlen(tempo));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
     sprintf(tempo, "CONNECT 10");
     SharedMemory_Write(1, 0, tempo, strlen(tempo));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
     sprintf(tempo, "CONNECT 11");
     SharedMemory_Write(1, 0, tempo, strlen(tempo));
}
//---------------------------------------------------------------------------

