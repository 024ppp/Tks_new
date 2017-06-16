//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TQuickRep *QuickRep1;
    TQRBand *QRBand1;
    TQRLabel *QRLabel3;
    TQRDBText *QRDBText3;
    TQRLabel *QRLabel1;
    TQRDBText *QRDBText1;
    TQRLabel *QRLabel4;
    TQRLabel *QRLabel5;
    TQRLabel *QRLabel6;
    TQRLabel *QRLabel7;
    TQRLabel *QRLabel8;
    TQRShape *QRShape2;
    TQRDBText *QRDBText6;
    TQRLabel *QRLabel37;
    TQRLabel *QRLabel38;
    TQRBand *QRBand2;
    TQRDBText *QRDBText7;
    TQRLabel *QRLabel35;
    TQRBand *QRBand3;
    TQRShape *QRShape5;
    TQRDBText *QRDBText4;
    TQRDBText *QRDBText2;
    TQRLabel *QRLabel36;
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel42;
    TQRLabel *QRLabel41;
    TQRLabel *QRLabel39;
    TQRLabel *QRLabel10;
    TQRLabel *QRLabel14;
    TQRLabel *QRLabel23;
    TQRLabel *QRLabel31;
    TQRLabel *QRLabel32;
    TQRLabel *QRLabel26;
    TQRLabel *QRLabel33;
    TQRLabel *QRLabel34;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel15;
    TQRLabel *QRLabel16;
    TQRLabel *QRLabel13;
    TQRLabel *QRLabel17;
    TQRLabel *QRLabel24;
    TQRLabel *QRLabel18;
    TQRLabel *QRLabel25;
    TQRLabel *QRLabel27;
    TQRLabel *QRLabel19;
    TQRLabel *QRLabel20;
    TQRLabel *QRLabel28;
    TQRLabel *QRLabel21;
    TQRLabel *QRLabel29;
    TQRLabel *QRLabel22;
    TQRLabel *QRLabel30;
	TQRLabel *QRLabel40;
	TQRLabel *QRLabel11;
    void __fastcall QRBand2BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRDBText6Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel35Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText3Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText1Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
    void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRLabel39Print(TObject *sender, AnsiString &Value);
    void __fastcall QuickRep1BeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall QRLabel41Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel42Print(TObject *sender, AnsiString &Value);
private:	// ユーザー宣言
public:		// ユーザー宣言
    __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
