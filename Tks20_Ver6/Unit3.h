//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Qrctrls.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
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
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel10;
    TQRLabel *QRLabel11;
    TQRLabel *QRLabel12;
    TQRLabel *QRLabel26;
    TQRLabel *QRLabel23;
    TQRLabel *QRLabel22;
    TQRLabel *QRLabel21;
    TQRLabel *QRLabel20;
    TQRLabel *QRLabel19;
    TQRLabel *QRLabel18;
    TQRLabel *QRLabel17;
    TQRLabel *QRLabel16;
    TQRLabel *QRLabel15;
    TQRLabel *QRLabel14;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel13;
    TQRLabel *QRLabel24;
    TQRLabel *QRLabel25;
    TQRLabel *QRLabel27;
    TQRLabel *QRLabel28;
    TQRLabel *QRLabel29;
    TQRLabel *QRLabel30;
    TQRLabel *QRLabel31;
    TQRLabel *QRLabel32;
    TQRLabel *QRLabel33;
    TQRLabel *QRLabel34;
    TQRBand *QRBand2;
    TQRDBText *QRDBText6;
    TQRDBText *QRDBText7;
    TQRBand *QRBand3;
    TQRShape *QRShape5;
    TQRDBText *QRDBText2;
    TQRShape *QRShape6;
    TQRLabel *QRLabel37;
    TQRLabel *QRLabel38;
    TQRLabel *QRLabel35;
    TQRLabel *QRLabel36;
    TQRLabel *QRLabel39;
    TQRShape *QRShape2;
    TQRLabel *QRLabel41;
    TQRLabel *QRLabel42;
	TQRLabel *QRLabel40;
	TQRLabel *QRLabel43;
    TQRLabel *QRLabel44;
    TQRDBText *QRDBText4;
    void __fastcall QRBand2BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRDBText6Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel35Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText3Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel39Print(TObject *sender, AnsiString &Value);
    void __fastcall QuickRep1BeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall QRLabel41Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel42Print(TObject *sender, AnsiString &Value);
    void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRLabel44Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText1Print(TObject *sender, AnsiString &Value);
    void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
