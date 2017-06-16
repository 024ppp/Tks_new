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
#include <DBGrids.hpp>
#include <DBTables.hpp>
//#include "NumberEdit.h"
#include <Clipbrd.hpp>
#include "NumberEdit.h"
#include <DB.hpp>

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
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel10;
        TEdit *EdtCOD;
        TEdit *Edt1;
        TPanel *PnlNO;
        TEdit *Edt2;
        TPanel *Panel16;
        TPanel *Panel14;
        TPanel *Panel23;
        TPanel *Panel43;
        TEdit *Edt5;
        TQuery *Query1;
        TDatabase *Database1;
    TRadioButton *RadioButton1;
    TNumberEdit *Edt3;
    TNumberEdit *Edt4;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
        void __fastcall BtnF07Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall SGr1_KeyPress(TObject *Sender, char &Key);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
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
    bool __fastcall CollectData(String OldKey);

    struct TKM04{                // 焼成仕様マスタ
        AnsiString SYOSEI_CD;    // 焼成コード
        AnsiString RO_NO;        // 炉NO
        int        MAX_ONDO;     // MAX温度
        int        CYCLE_TIME;   // サイクルタイム
        AnsiString MEMO;         // メモ
        AnsiString ADDYMD;       // 登録日
        AnsiString ADDTIM;       // 登録時間
        AnsiString UPDYMD;       // 変更日
        AnsiString UPDTIM;       // 変更時間
        int        UPDCHR;       // 更新者
        int        UPDCNT;       // 更新回数
    }KM04;


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
