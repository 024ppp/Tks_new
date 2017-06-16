//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
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
    TQRBand *z;
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
    TQRLabel *QRLabel21;
    TQRLabel *QRLabel22;
    TQRLabel *QRLabel23;
    TQRLabel *QRLabel24;
    TQRLabel *QRLabel25;
    TQRLabel *QRLabel27;
    TQRLabel *QRLabel28;
    TQRLabel *QRLabel30;
    TQRLabel *QRLabel31;
    TQRLabel *QRLabel32;
    TQRLabel *QRLabel33;
    TQRLabel *QRLabel34;
    TQRLabel *QRLabel35;
    TQRLabel *QRLabel36;
    TQRLabel *QRLabel37;
    TQRLabel *QRLabel38;
    TQRLabel *QRLabel39;
    TQRLabel *QRLabel40;
    TQRLabel *QRLabel41;
    TQRLabel *QRLabel42;
    TQRLabel *QRLabel43;
    TQRLabel *QRLabel44;
    TQRLabel *QRLabel45;
    TQRLabel *QRLabel46;
    TQRLabel *QRLabel47;
    TQRLabel *QRLbl12;
    TQRLabel *QRLbl13;
    TQRLabel *QRLbl15;
    TQRLabel *QRLbl17;
    TQRLabel *QRLbl19;
    TQRLabel *QRLbl21;
    TQRLabel *QRLbl22;
    TQRLabel *QRLbl23;
    TQRLabel *QRLbl24;
    TQRLabel *QRLbl26;
    TQRLabel *QRLbl25;
    TQRLabel *QRLbl27;
    TQRLabel *QRLbl29;
    TQRLabel *QRLbl31;
    TQRLabel *QRLbl32;
    TQRLabel *QRLbl33;
    TQRLabel *QRLbl36;
    TQRLabel *QRLbl35;
    TQRLabel *QRLbl37;
    TQRLabel *QRLbl39;
    TQRLabel *QRLbl41;
    TQRLabel *QRLbl43;
    TQRLabel *QRLbl45;
        TQRLabel *QRLabel26;
    TQRLabel *QRLabel29;
    TQRLabel *QRLabel48;
    TQRLabel *QRLabel49;
    TQRLabel *QRLbl50;
    TQRLabel *QRLbl51;
    TQRLabel *QRLbl52;
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
    void __fastcall QRLbl12Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl13Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl15Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl17Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl19Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl21Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl22Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl23Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl24Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl25Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl26Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl27Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl29Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl31Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl32Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl33Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl35Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl36Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl37Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl39Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl41Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl43Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl45Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl51Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl50Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLbl52Print(TObject *sender, AnsiString &Value);
private:	// ユーザー宣言
    int iPrtRow;
    AnsiString sBuf1;
    AnsiString sBuf2;
    int __fastcall GetiPrtRow(int n);
public:		// ユーザー宣言
    __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
