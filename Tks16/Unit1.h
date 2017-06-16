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
#include "NumberEdit.h"
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TStatusBar *StatusBar1;
        TPanel *Panel9;
        TPanel *Panel1;
        TPanel *Panel10;
        TPanel *Panel16;
        TPanel *Panel8;
        TPanel *Panel11;
        TPanel *Pan_Hsc5;
        TPanel *Panel14;
        TPanel *Panel17;
        TPanel *Pan_Hsc6;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button8;
        TButton *Button7;
        TButton *Button6;
        TButton *Button5;
        TButton *Button10;
        TButton *Button9;
        TBevel *Bevel2;
        TPanel *Panel79;
        TPanel *Panel81;
        TPanel *Panel82;
        TPanel *Panel83;
        TPanel *Panel84;
        TPanel *Panel85;
        TPanel *Panel80;
        TUpDown *Scr_Hsc2;
        TUpDown *Scr_Hsc3;
        TBevel *Bevel1;
        TPanel *Panel21;
        TPanel *Panel22;
        TPanel *Panel23;
        TPanel *Pan_Hsc;
        TPanel *Panel25;
        TBevel *Bevel3;
        TPanel *Panel26;
        TPanel *Panel27;
        TPanel *Panel28;
        TPanel *Panel29;
        TPanel *Pan_Hsd5;
        TUpDown *Scr_Hsd2;
        TPanel *Panel32;
        TPanel *Panel34;
        TPanel *Pan_Hsd6;
        TUpDown *Scr_Hsd3;
        TPanel *Panel38;
        TPanel *Panel39;
        TPanel *Panel40;
        TPanel *Panel41;
        TPanel *Panel42;
        TPanel *Pan_Hsd;
        TPanel *Panel44;
        TUpDown *Scr_Hsd1;
        TBevel *Bevel4;
        TPageControl *PageCtl_Hsd;
        TTabSheet *Hsd_Sheet1;
        TTabSheet *Hsd_Sheet2;
        TPanel *Panel101;
        TPanel *Pan_Hsd_Min1;
        TPanel *Panel103;
        TPanel *Pan_Hsd_Max1;
        TPanel *Panel105;
        TPanel *Pan_Hsd_Ave1;
        TPanel *Panel107;
        TPanel *Pan_Hsd_Cp1;
        TPanel *Panel109;
        TPanel *Pan_Hsd_Siguma1;
        TPanel *Panel111;
        TPanel *Pan_Hsd_R1;
        TPanel *Panel113;
        TPanel *Pan_Hsd_Cpk1;
        TPanel *Pan_Hsd_K1;
        TPanel *Panel116;
        TPanel *Panel117;
        TPanel *Pan_Hsd_P1;
        TPageControl *PageCtl_Hsc;
        TTabSheet *Hsc_Sheet1;
        TTabSheet *Hsc_Sheet2;
        TPanel *Panel12;
        TPanel *Pan_Hsc_Min1;
        TPanel *Panel19;
        TPanel *Pan_Hsc_Max1;
        TPanel *Panel30;
        TPanel *Pan_Hsc_Ave1;
        TPanel *Panel36;
        TPanel *Pan_Hsc_Cp1;
        TPanel *Panel45;
        TPanel *Pan_Hsc_Siguma1;
        TPanel *Panel47;
        TPanel *Pan_Hsc_R1;
        TPanel *Panel49;
        TPanel *Pan_Hsc_Cpk1;
        TPanel *Pan_Hsc_K1;
        TPanel *Panel52;
        TPanel *Panel53;
        TPanel *Pan_Hsc_P1;
        TDatabase *Database1;
        TQuery *Query1;
        TTable *KD63W;
        TStoredProc *StoredProc1;
        TPanel *Pnl7;
        TPanel *Pnl8;
        TPanel *Pnl9;
        TPanel *Pnl10;
        TPanel *Pnl11;
        TPanel *Pnl12;
        TPanel *Pan_Hsc1;
        TPanel *Pan_Hsc2;
        TPanel *Pan_Hsc3;
        TPanel *Pan_Hsc4;
        TNumberEdit *Edt_Hsc_Sample;
        TNumberEdit *Edt_Hsc11;
        TNumberEdit *Edt_Hsc12;
        TNumberEdit *Edt_Hsc21;
        TNumberEdit *Edt_Hsc22;
        TNumberEdit *Edt_Hsc23;
        TNumberEdit *Edt_Hsc14;
        TNumberEdit *Edt_Hsc24;
        TPanel *Pan_Hsd1;
        TPanel *Pan_Hsd3;
        TPanel *Pan_Hsd2;
        TPanel *Pan_Hsd4;
        TNumberEdit *Edt_Hsd_Sample;
        TNumberEdit *Edt_Hsd11;
        TNumberEdit *Edt_Hsd12;
        TNumberEdit *Edt_Hsd13;
        TNumberEdit *Edt_Hsd14;
        TNumberEdit *Edt_Hsd24;
        TNumberEdit *Edt_Hsd23;
        TNumberEdit *Edt_Hsd22;
        TNumberEdit *Edt_Hsd21;
        TImage *GraphyImg_Hsc1;
        TImage *GraphyImg_Hsd1;
        TBevel *Bevel5;
        TTabSheet *Hsc_Sheet3;
        TTabSheet *Hsc_Sheet4;
        TTabSheet *Hsd_Sheet3;
        TTabSheet *Hsd_Sheet4;
        TImage *GraphyImg_Hsc2;
        TPanel *Panel13;
        TPanel *Pan_Hsc_Min2;
        TPanel *Panel18;
        TPanel *Pan_Hsc_Max2;
        TPanel *Panel24;
        TPanel *Pan_Hsc_Ave2;
        TPanel *Panel33;
        TPanel *Pan_Hsc_R2;
        TPanel *Panel37;
        TPanel *Pan_Hsc_Siguma2;
        TPanel *Panel46;
        TPanel *Pan_Hsc_Cp2;
        TPanel *Panel50;
        TPanel *Pan_Hsc_Cpk2;
        TPanel *Panel54;
        TPanel *Pan_Hsc_K2;
        TPanel *Panel56;
        TPanel *Pan_Hsc_P2;
        TImage *GraphyImg_Hsd2;
        TPanel *Panel15;
        TPanel *Pan_Hsd_Min2;
        TPanel *Panel31;
        TPanel *Pan_Hsd_Max2;
        TPanel *Panel43;
        TPanel *Pan_Hsd_Ave2;
        TPanel *Panel51;
        TPanel *Pan_Hsd_R2;
        TPanel *Panel57;
        TPanel *Pan_Hsd_Siguma2;
        TPanel *Panel59;
        TPanel *Pan_Hsd_Cp2;
        TPanel *Panel61;
        TPanel *Pan_Hsd_Cpk2;
        TPanel *Panel63;
        TPanel *Pan_Hsd_K2;
        TPanel *Panel65;
        TPanel *Pan_Hsd_P2;
        TNumberEdit *Edt_Hsc13;
        TUpDown *Scr_Hsc1;
        TPanel *Panel20;
        TPanel *Pan_Hsc_N1;
        TPanel *Pan_Hsc_N2;
        TPanel *Panel48;
        TPanel *Panel35;
        TPanel *Pan_Hsd_N1;
        TPanel *Pan_Hsd_N2;
        TPanel *Panel58;
        TMediaPlayer *MdPlayer;
        TBitBtn *Button11;
        TBitBtn *Button12;
    TMaskEdit *edtymd;
    TPanel *Panel77;
    TUpDown *UpDownymd;
    TPanel *Panel78;
    TNumberEdit *edttlno;
    TUpDown *UpDowntlno;
    TCheckBox *CheckBoxRireki;
    TBevel *Bevel33;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall SetInit(int flag);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall StatBarClear(AnsiString sMsg);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall edtymd1Enter(TObject *Sender);
        void __fastcall edttlnoEnter(TObject *Sender);
        void __fastcall ExecF1(void);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall SetAreaInfo(int AreaNo, int SetFlag);
        void __fastcall Edt_Hsc_SampleEnter(TObject *Sender);
        void __fastcall ButtonInputMode(int Opt);
        void __fastcall Edt_Hsc_SampleExit(TObject *Sender);
        void __fastcall Edt_Hsd_SampleExit(TObject *Sender);
        void __fastcall Edt_Hsc_SampleKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edt_Hsc11Enter(TObject *Sender);
        void __fastcall Unenable(int Opt);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall SetFieldFocus(void);
        void __fastcall edtymdEnter(TObject *Sender);
        void __fastcall edtymdKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edt_Hsd_SampleEnter(TObject *Sender);
        void __fastcall Edt_Hsd11Enter(TObject *Sender);
        void __fastcall ExtractCode();
        void __fastcall Edt_Hsc14Exit(TObject *Sender);
        void __fastcall Edt_Hsc24Exit(TObject *Sender);
        void __fastcall Edt_Hsd14Exit(TObject *Sender);
        void __fastcall Edt_Hsd24Exit(TObject *Sender);
        void __fastcall Edt_Hsc11Change(TObject *Sender);
        void __fastcall Edt_Hsd11Change(TObject *Sender);
        void __fastcall Edt_Hsc11Exit(TObject *Sender);
        void __fastcall Edt_Hsd11Exit(TObject *Sender);
        void __fastcall Button111Click(TObject *Sender);
        void __fastcall FieldColor(int SampleDataIdx, int DataNoIdx, int A_Flag);
        void __fastcall PageCtl_HscChange(TObject *Sender);
        void __fastcall PageCtl_HsdChange(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Scr_Hsc11Change(TObject *Sender);
        void __fastcall Scr_Hsc1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Scr_Hsd1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Scr_Hsc2Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Scr_Hsc3Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Scr_Hsd2Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Scr_Hsd3Click(TObject *Sender, TUDBtnType Button);
        void __fastcall NextTorei();
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button11Enter(TObject *Sender);
        void __fastcall Button11Exit(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button12Enter(TObject *Sender);
        void __fastcall Button12Exit(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
    void __fastcall UpDownymdClick(TObject *Sender, TUDBtnType Button);
    void __fastcall UpDowntlnoClick(TObject *Sender, TUDBtnType Button);
    void __fastcall Read_Ini();
private:	// ユーザー宣言
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
        void __fastcall InitEdt(TNumberEdit *P_Edit, AnsiString);
        void __fastcall InitPnl(TPanel *P_Pnl, AnsiString Str);
        void __fastcall TForm1::SetMEMO(void);
        bool __fastcall TForm1::CheckChangeData(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
