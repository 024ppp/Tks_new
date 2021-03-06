//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TQuickRep *QuickRep1;
    TQRBand *QRBand1;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRLabel *QRLabel5;
    TQRLabel *QRLabel6;
    TQRLabel *QRLabel7;
    TQRBand *QRBand3;
    TQRLabel *QRLbl1;
    TQRLabel *QRLbl2;
    TQRLabel *QRLbl6;
    TQRLabel *QRLbl4;
    TQRLabel *QRLbl5;
    TQRLabel *QRLbl3;
    TQRBand *QRBand4;
    TQRLabel *QRLabel8;
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel1;
    TQRShape *QRShape1;
    TQRShape *QRShape2;
    TQRShape *QRShape3;
    TQRLabel *QRLabel10;
    TQRLabel *QRLabel11;
    TQRLabel *QRLabel12;
    TQRLabel *QRLabel13;
    TQRLabel *QRLabel14;
    TQRLabel *QRLabel15;
    TQRLabel *QRLabel16;
    TQRLabel *QRLabel17;
    TQRLabel *QRLabel18;
    TQRLabel *QRLbl7;
    TQRLabel *QRLbl8;
    TQRLabel *QRLbl9;
    TQRLabel *QRLbl10;
        TQRLabel *QRLabel19;
	TQRLabel *QRLabel20;
    TQRBand *QRBand2;
    void __fastcall QRLbl1Print(TObject *sender, AnsiString &Value);
    void __fastcall QRBand3AfterPrint(TQRCustomBand *Sender,
          bool BandPrinted);
    void __fastcall QuickRep1BeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall QRLbl2Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl3Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl4Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl5Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl6Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel9Print(TObject *sender, AnsiString &Value);
    void __fastcall QuickRep1NeedData(TObject *Sender, bool &MoreData);
    void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRLbl7Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl8Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl9Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl10Print(TObject *sender, AnsiString &Value);
private:	// ユーザー宣言
    int iPrtRow;
    AnsiString sBuf1;
    AnsiString sBuf2;
public:		// ユーザー宣言
    __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
