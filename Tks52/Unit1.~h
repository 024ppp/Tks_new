//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Grids.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include "NumberEdit.h"
#include <Clipbrd.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel2;
    TPanel *PnlBumCode;
    TPanel *PnlBumName;
        TPanel *Panel5;
    TPanel *PnlTanCode;
    TPanel *PnlTanName;
    TStatusBar *SBr1;
        TPanel *Panel9;
        TPanel *Panel1;
    TButton *BtnF01;
    TButton *BtnF02;
    TButton *BtnF03;
    TButton *BtnF04;
    TButton *BtnF05;
    TButton *BtnF06;
    TButton *BtnF07;
    TButton *BtnF08;
    TButton *BtnF09;
    TButton *BtnF10;
    TButton *BtnF11;
    TButton *BtnF12;
    TStringGrid *SGr1;
        TBevel *Bevel1;
        TPanel *Panel8;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel10;
    TEdit *EdtCOD2;
    TEdit *Edt1;
    TPanel *PnlNO;
    TEdit *Edt2;
        TPanel *Panel16;
        TPanel *Panel18;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel22;
        TPanel *Panel23;
        TPanel *Panel24;
        TPanel *Panel25;
        TPanel *Panel26;
        TPanel *Panel28;
        TPanel *Panel29;
        TPanel *Panel30;
        TPanel *Panel31;
        TPanel *Panel27;
        TPanel *Panel32;
        TPanel *Panel33;
        TPanel *Panel34;
        TPanel *Panel35;
        TPanel *Panel36;
        TPanel *Panel37;
        TPanel *Panel38;
        TPanel *Panel39;
        TPanel *Panel40;
        TPanel *Panel41;
        TPanel *Panel42;
        TPanel *Panel43;
        TPanel *Panel44;
    TComboBox *CmbBox1;
    TDatabase *Database1;
    TQuery *Query1;
    TNumberEdit *Edt3;
    TNumberEdit *Edt4;
    TNumberEdit *Edt5;
    TNumberEdit *Edt6;
    TNumberEdit *Edt7;
    TNumberEdit *Edt8;
    TNumberEdit *Edt9;
    TNumberEdit *Edt10;
    TNumberEdit *Edt11;
    TNumberEdit *Edt12;
    TNumberEdit *Edt13;
    TNumberEdit *Edt14;
    TNumberEdit *Edt15;
    TNumberEdit *Edt16;
    TPanel *Panel3;
    TEdit *EdtCOD1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall SGr1KeyPress(TObject *Sender, char &Key);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
private:	// ユーザー宣言

    // ユーザー情報
    int     USER_COD;
    String  USER_NAM;
    String  BUMO_COD;
    String  BUMO_NAM;

    bool    DataSave;

    bool __fastcall AddData();
    bool __fastcall DelData();
    bool __fastcall CollectData(String OldKey1, String OldKey2);

    struct TKM03{                // 材質規格マスタ
        AnsiString ZISCOD;       // 材質コード
        AnsiString ZISNAM;       // 材質名
        double     BOTAI_MIN;    // 母体比重（下限）
        double     BOTAI_MAX;    // 母体比重（上限）
        int        KOYU_MIN;     // 固有抵抗率（下限）
        int        KOYU_MAX;     // 固有抵抗率（上限）
        double     MAGE_MIN;     // 曲げ強度（下限）
        double     MAGE_MAX;     // 曲げ強度（上限）
        int        MAGE_TAN;     // 曲げ強度（単位）
        int        HSC_A_MIN;    // HsC硬度 圧面（下限）
        int        HSC_A_MAX;    // HsC硬度 圧面（上限）
        int        HSC_S_MIN;    // HsC硬度 側面（下限）
        int        HSC_S_MAX;    // HsC硬度 側面（上限）
        double     HSD_A_MIN;    // HsD硬度 圧面（下限）
        double     HSD_A_MAX;    // HsD硬度 圧面（上限）
        double     HSD_S_MIN;    // HsD硬度 側面（下限）
        double     HSD_S_MAX;    // HsD硬度 側面（上限）
        AnsiString ADDYMD;       // 登録日
        AnsiString ADDTIM;       // 登録時間
        AnsiString UPDYMD;       // 変更日
        AnsiString UPDTIM;       // 変更時間
        int        UPDCHR;       // 更新者
        int        UPDCNT;       // 更新回数
    }KM03;

public:		// ユーザー宣言
    TClipboard *ClpBrd;
    __fastcall TForm1(TComponent* Owner);
    void __fastcall ExtractCode(AnsiString str);
    AnsiString __fastcall StrReplace(AnsiString str, AnsiString a, AnsiString b);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
