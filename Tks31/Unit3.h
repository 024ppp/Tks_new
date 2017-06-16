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
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE 管理のコンポーネント
    TQuickRep *QuickRep1;
    TQRBand *QRBand1;
    TQRLabel *QRLabel1;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRLabel *QRLabel5;
    TQRBand *QRBand2;
    TQuery *Query1;
    TQRLabel *QRLabel7;
    TQRLabel *QRLabel8;
    TQRLabel *QRLabel9;
    TQRLabel *QRLabel10;
    TQRLabel *QRLabel11;
    TQRLabel *QRLabel12;
    TQRLabel *QRLabel13;
    TQRLabel *QRLabel14;
    TQRLabel *QRLabel15;
    TQRLabel *QRLabel16;
    TQRLabel *QRLabel17;
    TQRLabel *QRLabel18;
    TQRLabel *QRLabel19;
    TQRLabel *QRLabel20;
    TQRLabel *QRLabel21;
    TQRLabel *QRLabel22;
    TQRLabel *QRLabel23;
    TQRLabel *QRLabel24;
    TQRLabel *QRLabel25;
    TQRLabel *QRLabel6;
    TQRShape *QRShape1;
    TQRLabel *QRLabel26;
    TQRLabel *QRLabel27;
    TQRLabel *QRLabel28;
    TQRLabel *QRLabel29;
    TQRLabel *QRLabel30;
    TQRBand *QRBand3;
    TQRShape *QRShape2;
    TQRLabel *QRLabel31;
    TQRLabel *QRLabel32;
    TQRLabel *QRLabel34;
    TQRLabel *QRLabel33;
    TQRLabel *QRLabel35;
    TQRLabel *QRLabel36;
    TQRLabel *QRLabel37;
    TQRLabel *QRLabel38;
    TQRLabel *QRLabel39;
    TQRLabel *QRLabel40;
    TQRLabel *QRLabel41;
    TQRLabel *QRLabel42;
    void __fastcall QRLabel7Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel8Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel9Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel10Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel11Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel12Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel13Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel14Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel15Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel16Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel17Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel18Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel19Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel20Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel3Print(TObject *sender, AnsiString &Value);
    void __fastcall QRLabel4Print(TObject *sender, AnsiString &Value);
    void __fastcall QuickRep1BeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall QRBand2AfterPrint(TQRCustomBand *Sender,
          bool BandPrinted);
    void __fastcall QRLabel32Print(TObject *sender, AnsiString &Value);
    void __fastcall QuickRep1NeedData(TObject *Sender, bool &MoreData);
    void __fastcall QRBand2BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QRLabel6Print(TObject *sender, AnsiString &Value);
    int __fastcall Search(int flag);
    void __fastcall QRLabel42Print(TObject *sender, AnsiString &Value); //flag = 0 -> 合格、不合格両方検索
                                     //flag = 1 -> 合格検索
                                     //flag = 2 -> 不合格検索
private:	// ユーザー宣言
        int iPrtRow;
        int iPrtRow2;

public:		// ユーザー宣言
    int EndFlag;
    __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
