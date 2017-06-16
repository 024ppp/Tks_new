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
#include <Mask.hpp>
#include <Clipbrd.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>

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
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel10;
        TEdit *Edt03;
        TEdit *Edt02;
        TPanel *PnlTr;
        TEdit *Edt04;
        TEdit *Edt05;
        TPanel *Panel22;
        TEdit *Edt07;
        TPanel *Panel16;
        TPanel *PnlSp;
        TEdit *Edt01;
        TEdit *Edt06;
        TPanel *Panel23;
        TDatabase *Database1;
        TQuery *Query1;
        TQuery *Query2;
        TNumberEdit *Edt08;
        TMaskEdit *EdtCOD;
        TProgressBar *ProgressBar1;
        TUpDown *UpDownymd;
        TPanel *Panel3;
        TQuery *Query3;
        TPanel *Panel4;
        TPanel *Panel6;
        TLabel *Label2;
        TPanel *Panel7;
        TLabel *Label3;
        TPanel *Panel11;
        TLabel *Label4;
        TPanel *Panel18;
        TLabel *Label5;
        TPanel *Panel24;
        TLabel *Label6;
        TPanel *Panel25;
        TLabel *Label7;
        TPanel *Panel26;
        TLabel *Label8;
        TPanel *Panel27;
        TLabel *Label9;
        TPanel *Panel28;
        TLabel *Label10;
        TPanel *Panel29;
        TLabel *Label11;
        TPanel *Panel30;
        TLabel *Label12;
        TPanel *Panel31;
        TLabel *Label13;
        TPanel *Panel32;
        TLabel *Label14;
        TPanel *Panel33;
        TLabel *Label15;
        TPanel *Panel34;
        TLabel *Label16;
        TLabel *Label17;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TPanel *Panel21;
        TEdit *Edt13;
        TNumberEdit *Edt14;
        TNumberEdit *Edt15;
        TNumberEdit *Edt16;
        TNumberEdit *Edt17;
        TNumberEdit *Edt18;
        TNumberEdit *Edt19;
        TNumberEdit *Edt20;
        TNumberEdit *Edt21;
        TNumberEdit *Edt22;
        TNumberEdit *Edt23;
        TNumberEdit *Edt28;
        TNumberEdit *Edt27;
        TNumberEdit *Edt26;
        TNumberEdit *Edt25;
        TNumberEdit *Edt24;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton5;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
        void __fastcall AllKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall AllKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF04Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall SGr1KeyPress(TObject *Sender, char &Key);
    void __fastcall AllEnter(TObject *Sender);
    void __fastcall AllKeyPress(TObject *Sender, char &Key);
        void __fastcall UpDownymdClick(TObject *Sender, TUDBtnType Button);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SGr1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);

private:	// ユーザー宣言
    // ユーザー情報
    int     USER_COD;
    String  USER_NAM;
    String  BUMO_COD;
    String  BUMO_NAM;

    String  NowKey;
    bool    NotFound;
    bool    DataSave;

    HANDLE  hMemCopy;
    int     CopyCnt;

    struct TKM01{                // 検査指示マスタ
        char KOKBNG[7];          // 工管NO
        char DTKSCOD[6];         // 得意先ｺｰﾄﾞ
        char DTKSHIN[21];        // 得意先品番
        char LOTNO[7];           // ロットNO
        char HINBAN[21];         // 自社品番
        char ZISCOD[21];         // 材質ｺｰﾄﾞ
        char ZISNAM[21];         // 材質名称
        char NUM[10];            // 数量
        char SORTKEY[4];         // ｿｰﾄｷｰ
        char KEIJKBN[2];         // 形状区分
        char KEIJKBNNM[6];       // 形状区分名称
        char SK_LD_LNG[5];       // 測定区分 リード線長さ
        char SK_BURASI[5];       // 測定区分 ブラシ幅
        char SK_BURASIT[5];      // 測定区分 ブラシ幅縦押し
        char SK_LD_TR[5];        // 測定区分 リード線取り付け抵抗
        char SK_LD_HP[5];        // 測定区分 リード線引張強度
        char SK_BOIAI[5];        // 測定区分 母体比重
        char SK_KOYU[5];         // 測定区分 固有抵抗率
        char SK_MAGE[5];         // 測定区分 曲げ強さ
        char SK_MAGEG[5];        // 測定区分 曲げ強さ現物
        char SK_HSC_A[5];        // 測定区分 HsC硬度（側面）
        char SK_HSC_S[5];        // 測定区分 HsC硬度（圧面）
        char SK_HSD_A[5];        // 測定区分 HsD硬度（側面）
        char SK_HSD_S[5];        // 測定区分 HsD硬度（圧面）
        char SK_ZAKUT[5];        // 測定区分 座屈
        char HIST_SOKUT[6];      // ﾋｽﾄｸﾞﾗﾑ測定数
    }*KM01;
    String  sSortKey;            // ｿｰﾄｷｰ用ﾊﾞｯﾌｧ
    String  sHistSokut;          // ﾋｽﾄｸﾞﾗﾑ測定数用ﾊﾞｯﾌｧ

    void __fastcall SubSearch(TObject *Sender, AnsiString sYMD);
    void __fastcall SubAdd();
    void __fastcall SubCorrect();
    bool __fastcall SubSearchKOKANBNG(AnsiString sKOKBNG);
    bool __fastcall SubSearchTKSHIN(AnsiString sTKSHIN, bool fSetEdit, bool fSetEditSecd );
    bool __fastcall SubSave();
    bool __fastcall SubSetOldValue(AnsiString sYMD, AnsiString sYMD_DMY);
    bool __fastcall SubMoveKM01(AnsiString sYMD, AnsiString sYMD_DMY);

public:		// ユーザー宣言
    TClipboard *ClpBrd;
    __fastcall TForm1(TComponent* Owner);
    AnsiString __fastcall DelSEPA(AnsiString sYMD);
    AnsiString __fastcall InsSEPA(AnsiString sYMD);
    void __fastcall ExtractCode(AnsiString str);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
