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
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TPanel *Panel2;
        TPanel *Pnl1;
        TPanel *Pnl2;
        TPanel *Panel5;
        TPanel *Pnl3;
        TPanel *Pnl4;
        TStatusBar *SBr1;
        TPanel *Panel9;
        TPanel *Panel1;
        TPanel *Panel10;
        TPanel *PnlP1;
        TPanel *Panel8;
        TPanel *Panel11;
        TPanel *PnlP2;
        TPanel *PnlN1;
        TPanel *Panel14;
        TPanel *PnlN2;
        TPanel *PnlP3;
        TPanel *PnlN3;
        TPanel *PnlP4;
        TPanel *PnlN4;
        TPanel *PnlP5;
        TPanel *PnlN5;
        TPanel *Pnlp6;
        TPanel *PnlN6;
        TPanel *PnlP7;
        TPanel *PnlN7;
        TPanel *PnlP8;
        TPanel *PnlN8;
        TPanel *PnlP9;
        TPanel *PnlN9;
        TPanel *PnlP10;
        TPanel *PnlN10;
        TPanel *PnlP11;
        TPanel *PnlN11;
        TPanel *PnlP12;
        TPanel *PnlN12;
        TPanel *PnlP13;
        TPanel *PnlN13;
        TPanel *PnlP14;
        TPanel *PnlN14;
        TPanel *PnlP15;
        TPanel *PnlN15;
        TPanel *Panel43;
        TPanel *PnlP16;
        TPanel *Panel45;
        TPanel *Panel46;
        TPanel *PnlP17;
        TPanel *PnlN16;
        TPanel *Panel49;
        TPanel *PnlN17;
        TPanel *PnlP18;
        TPanel *PnlN18;
        TPanel *PnlP19;
        TPanel *PnlN19;
        TPanel *PnlP20;
        TPanel *PnlN20;
        TPanel *PnlP21;
        TPanel *PnlN21;
        TPanel *PnlP22;
        TPanel *PnlN22;
        TPanel *PnlP23;
        TPanel *PnlN23;
        TPanel *PnlP24;
        TPanel *PnlN24;
        TPanel *PnlP25;
        TPanel *PnlN25;
        TPanel *PnlP26;
        TPanel *PnlN26;
        TPanel *PnlP27;
        TPanel *PnlN27;
        TPanel *PnlP28;
        TPanel *PnlN28;
        TPanel *PnlP29;
        TPanel *PnlN29;
        TPanel *PnlP30;
        TPanel *PnlN30;
        TBevel *Bevel1;
        TButton *BtnF01;
        TButton *BtnF02;
        TButton *BtnF03;
        TButton *BtnF04;
        TButton *BtnF08;
        TButton *BtnF07;
        TButton *BtnF06;
        TButton *BtnF05;
        TButton *BtnF10;
        TButton *BtnF09;
        TPanel *Panel79;
        TPanel *Panel81;
        TPanel *Panel82;
        TPanel *Panel83;
        TPanel *Panel84;
        TPanel *Panel85;
        TPanel *Panel80;
        TPanel *Panel86;
        TScrollBar *ScrollBar1;
        TBevel *Bevel3;
        TBevel *Bevel5;
        TBevel *Bevel6;
        TBevel *Bevel7;
        TBevel *Bevel8;
        TBevel *Bevel9;
        TBevel *Bevel10;
        TBevel *Bevel11;
        TBevel *Bevel12;
        TBevel *Bevel13;
        TBevel *Bevel14;
        TBevel *Bevel15;
        TBevel *Bevel16;
        TBevel *Bevel17;
        TBevel *Bevel18;
        TBevel *Bevel19;
        TBevel *Bevel20;
        TBevel *Bevel21;
        TBevel *Bevel22;
        TBevel *Bevel23;
        TBevel *Bevel24;
        TBevel *Bevel25;
        TBevel *Bevel26;
        TBevel *Bevel27;
        TBevel *Bevel28;
        TBevel *Bevel29;
        TBevel *Bevel30;
        TBevel *Bevel31;
        TBevel *Bevel32;
        TScrollBar *ScrollBar2;
        TScrollBar *ScrollBar3;
        TScrollBar *ScrollBar4;
        TScrollBar *ScrollBar5;
        TScrollBar *ScrollBar6;
        TScrollBar *ScrollBar7;
        TScrollBar *ScrollBar8;
        TScrollBar *ScrollBar9;
        TScrollBar *ScrollBar10;
        TScrollBar *ScrollBar11;
        TScrollBar *ScrollBar12;
        TScrollBar *ScrollBar13;
        TScrollBar *ScrollBar14;
        TScrollBar *ScrollBar15;
        TScrollBar *ScrollBar16;
        TScrollBar *ScrollBar17;
        TScrollBar *ScrollBar18;
        TScrollBar *ScrollBar19;
        TScrollBar *ScrollBar20;
        TScrollBar *ScrollBar21;
        TScrollBar *ScrollBar22;
        TScrollBar *ScrollBar23;
        TScrollBar *ScrollBar24;
        TScrollBar *ScrollBar25;
        TScrollBar *ScrollBar26;
        TScrollBar *ScrollBar27;
        TScrollBar *ScrollBar28;
        TScrollBar *ScrollBar29;
        TScrollBar *ScrollBar30;
        TBevel *Bevel34;
        TPanel *Panel87;
        TPanel *Pnl5;
        TPanel *Pnl7;
        TPanel *Pnl8;
        TPanel *Pnl9;
        TPanel *Pnl10;
        TPanel *Pnl11;
        TPanel *Pnl12;
        TNumberEdit *Edt01_1;
        TNumberEdit *Edt01_2;
        TNumberEdit *Edt02_1;
        TNumberEdit *Edt02_2;
        TNumberEdit *Edt03_1;
        TNumberEdit *Edt03_2;
        TNumberEdit *Edt04_1;
        TNumberEdit *Edt04_2;
        TNumberEdit *Edt05_1;
        TNumberEdit *Edt05_2;
        TNumberEdit *Edt06_1;
        TNumberEdit *Edt06_2;
        TNumberEdit *Edt07_1;
        TNumberEdit *Edt07_2;
        TNumberEdit *Edt08_1;
        TNumberEdit *Edt08_2;
        TNumberEdit *Edt09_1;
        TNumberEdit *Edt09_2;
        TNumberEdit *Edt10_1;
        TNumberEdit *Edt10_2;
        TNumberEdit *Edt11_1;
        TNumberEdit *Edt11_2;
        TNumberEdit *Edt12_1;
        TNumberEdit *Edt12_2;
        TNumberEdit *Edt13_1;
        TNumberEdit *Edt13_2;
        TNumberEdit *Edt14_1;
        TNumberEdit *Edt14_2;
        TNumberEdit *Edt15_1;
        TNumberEdit *Edt15_2;
        TNumberEdit *Edt16_1;
        TNumberEdit *Edt16_2;
        TNumberEdit *Edt17_1;
        TNumberEdit *Edt17_2;
        TNumberEdit *Edt18_1;
        TNumberEdit *Edt18_2;
        TNumberEdit *Edt19_1;
        TNumberEdit *Edt19_2;
        TNumberEdit *Edt20_1;
        TNumberEdit *Edt20_2;
        TNumberEdit *Edt21_1;
        TNumberEdit *Edt21_2;
        TNumberEdit *Edt22_1;
        TNumberEdit *Edt22_2;
        TNumberEdit *Edt23_1;
        TNumberEdit *Edt23_2;
        TNumberEdit *Edt24_1;
        TNumberEdit *Edt24_2;
        TNumberEdit *Edt25_1;
        TNumberEdit *Edt25_2;
        TNumberEdit *Edt26_1;
        TNumberEdit *Edt26_2;
        TNumberEdit *Edt27_1;
        TNumberEdit *Edt27_2;
        TNumberEdit *Edt28_1;
        TNumberEdit *Edt28_2;
        TNumberEdit *Edt29_1;
        TNumberEdit *Edt29_2;
        TNumberEdit *Edt30_1;
        TNumberEdit *Edt30_2;
        TNumberEdit *Edt01_3;
        TNumberEdit *Edt02_3;
        TNumberEdit *Edt03_3;
        TNumberEdit *Edt04_3;
        TNumberEdit *Edt05_3;
        TNumberEdit *Edt06_3;
        TNumberEdit *Edt07_3;
        TNumberEdit *Edt08_3;
        TNumberEdit *Edt09_3;
        TNumberEdit *Edt10_3;
        TNumberEdit *Edt11_3;
        TNumberEdit *Edt12_3;
        TNumberEdit *Edt13_3;
        TNumberEdit *Edt14_3;
        TNumberEdit *Edt15_3;
        TNumberEdit *Edt16_3;
        TNumberEdit *Edt17_3;
        TNumberEdit *Edt18_3;
        TNumberEdit *Edt19_3;
        TNumberEdit *Edt20_3;
        TNumberEdit *Edt21_3;
        TNumberEdit *Edt22_3;
        TNumberEdit *Edt23_3;
        TNumberEdit *Edt24_3;
        TNumberEdit *Edt25_3;
        TNumberEdit *Edt26_3;
        TNumberEdit *Edt27_3;
        TNumberEdit *Edt29_3;
        TNumberEdit *Edt30_3;
        TNumberEdit *Edt28_3;
        TNumberEdit *Edt01_4;
        TNumberEdit *Edt02_4;
        TNumberEdit *Edt03_4;
        TNumberEdit *Edt04_4;
        TNumberEdit *Edt05_4;
        TNumberEdit *Edt06_4;
        TNumberEdit *Edt07_4;
        TNumberEdit *Edt08_4;
        TNumberEdit *Edt09_4;
        TNumberEdit *Edt10_4;
        TNumberEdit *Edt11_4;
        TNumberEdit *Edt12_4;
        TNumberEdit *Edt13_4;
        TNumberEdit *Edt14_4;
        TNumberEdit *Edt15_4;
        TNumberEdit *Edt16_4;
        TNumberEdit *Edt17_4;
        TNumberEdit *Edt18_4;
        TNumberEdit *Edt19_4;
        TNumberEdit *Edt20_4;
        TNumberEdit *Edt21_4;
        TNumberEdit *Edt22_4;
        TNumberEdit *Edt23_4;
        TNumberEdit *Edt24_4;
        TNumberEdit *Edt25_4;
        TNumberEdit *Edt26_4;
        TNumberEdit *Edt27_4;
        TNumberEdit *Edt28_4;
        TNumberEdit *Edt29_4;
        TNumberEdit *Edt30_4;
        TDatabase *Database1;
        TQuery *Query1;
        TPageControl *PageCtrl;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TImage *GraphyImg;
        TPanel *Panel3;
        TPanel *Panel88;
        TPanel *Panel89;
        TPanel *Pnl24;
        TPanel *Pnl21;
        TPanel *Pnl22;
        TPanel *Panel90;
        TPanel *Panel91;
        TPanel *Panel92;
        TPanel *Pnl31;
        TPanel *Pnl32;
        TPanel *Pnl33;
        TPanel *Panel93;
        TPanel *Panel94;
        TPanel *Panel95;
        TPanel *Pnl41;
        TPanel *Pnl42;
        TPanel *Pnl43;
        TBevel *Bevel4;
        TStoredProc *StoredProc1;
    TTable *KDC3W;
        TPanel *Panel4;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel103;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel96;
        TScrollBar *ScrlS1;
        TScrollBar *ScrlS2;
        TScrollBar *ScrlS3;
        TPanel *PnlS1;
        TPanel *PnlS2;
        TPanel *PnlS3;
        TPanel *Panel99;
        TPanel *Panel97;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel102;
        TRadioButton *Rad1;
        TRadioButton *Rad2;
        TRadioButton *Rad3;
        TLabel *Label1;
        TPanel *Pnl6;
        TPanel *Pnl6_1;
        TPanel *Pnl13;
        TNumberEdit *EdtS1_1;
        TNumberEdit *EdtS1_2;
        TNumberEdit *EdtS1_3;
        TNumberEdit *EdtS2_1;
        TNumberEdit *EdtS2_2;
        TNumberEdit *EdtS2_3;
        TNumberEdit *EdtS3_1;
        TNumberEdit *EdtS3_2;
        TNumberEdit *EdtS3_3;
        TNumberEdit *EdtS4_1;
        TNumberEdit *EdtS4_2;
        TNumberEdit *EdtS4_3;
        TPanel *PnlSpan1;
        TPanel *PnlSpan2;
        TPanel *PnlSpan3;
        TPanel *Panel15;
        TPanel *Pnl23;
        TMediaPlayer *MdPlayer;
        TBitBtn *BtnF11;
        TBitBtn *BtnF12;
    TBevel *Bevel2;
    TBevel *Bevel33;
    TPanel *Panel77;
    TPanel *Panel78;
    TNumberEdit *edttlno;
    TMaskEdit *edtymd;
    TUpDown *UpDownymd;
    TUpDown *UpDowntlno;
    TCheckBox *CheckBoxRireki;
    TPanel *Panel16;
    TRadioGroup *RGRS1;
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall BtnF02Click(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall BtnF03Click(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
        void __fastcall BtnF07Click(TObject *Sender);
        void __fastcall BtnF10Click(TObject *Sender);
        void __fastcall BtnF11Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
        void __fastcall Edt01_1Enter(TObject *Sender);
        void __fastcall Edt01_2Enter(TObject *Sender);
        void __fastcall Edt01_4Enter(TObject *Sender);
        void __fastcall ScrollBar1Enter(TObject *Sender);
        void __fastcall Edt02_1Enter(TObject *Sender);
        void __fastcall Edt02_2Enter(TObject *Sender);
        void __fastcall Edt02_3Enter(TObject *Sender);
        void __fastcall Edt02_4Enter(TObject *Sender);
        void __fastcall ScrollBar2Enter(TObject *Sender);
        void __fastcall Edt03_1Enter(TObject *Sender);
        void __fastcall Edt03_2Enter(TObject *Sender);
        void __fastcall Edt03_3Enter(TObject *Sender);
        void __fastcall Edt03_4Enter(TObject *Sender);
        void __fastcall ScrollBar3Enter(TObject *Sender);
        void __fastcall Edt04_1Enter(TObject *Sender);
        void __fastcall Edt04_2Enter(TObject *Sender);
        void __fastcall Edt04_3Enter(TObject *Sender);
        void __fastcall Edt04_4Enter(TObject *Sender);
        void __fastcall Edt01_3Enter(TObject *Sender);
        void __fastcall Edt05_1Enter(TObject *Sender);
        void __fastcall Edt05_2Enter(TObject *Sender);
        void __fastcall Edt05_3Enter(TObject *Sender);
        void __fastcall Edt05_4Enter(TObject *Sender);
        void __fastcall ScrollBar5Enter(TObject *Sender);
        void __fastcall Edt06_1Enter(TObject *Sender);
        void __fastcall Edt06_2Enter(TObject *Sender);
        void __fastcall Edt06_3Enter(TObject *Sender);
        void __fastcall Edt06_4Enter(TObject *Sender);
        void __fastcall ScrollBar6Enter(TObject *Sender);
        void __fastcall Edt07_1Enter(TObject *Sender);
        void __fastcall Edt07_2Enter(TObject *Sender);
        void __fastcall Edt07_3Enter(TObject *Sender);
        void __fastcall Edt07_4Enter(TObject *Sender);
        void __fastcall ScrollBar7Enter(TObject *Sender);
        void __fastcall Edt08_1Enter(TObject *Sender);
        void __fastcall Edt08_2Enter(TObject *Sender);
        void __fastcall Edt08_3Enter(TObject *Sender);
        void __fastcall Edt08_4Enter(TObject *Sender);
        void __fastcall ScrollBar8Enter(TObject *Sender);
        void __fastcall Edt09_1Enter(TObject *Sender);
        void __fastcall Edt09_2Enter(TObject *Sender);
        void __fastcall Edt09_3Enter(TObject *Sender);
        void __fastcall Edt09_4Enter(TObject *Sender);
        void __fastcall ScrollBar9Enter(TObject *Sender);
        void __fastcall Edt10_1Enter(TObject *Sender);
        void __fastcall Edt10_2Enter(TObject *Sender);
        void __fastcall Edt10_3Enter(TObject *Sender);
        void __fastcall Edt10_4Enter(TObject *Sender);
        void __fastcall ScrollBar10Enter(TObject *Sender);
        void __fastcall Edt11_1Enter(TObject *Sender);
        void __fastcall Edt11_2Enter(TObject *Sender);
        void __fastcall Edt11_3Enter(TObject *Sender);
        void __fastcall Edt11_4Enter(TObject *Sender);
        void __fastcall ScrollBar11Enter(TObject *Sender);
        void __fastcall Edt12_1Enter(TObject *Sender);
        void __fastcall Edt12_2Enter(TObject *Sender);
        void __fastcall Edt12_3Enter(TObject *Sender);
        void __fastcall Edt12_4Enter(TObject *Sender);
        void __fastcall ScrollBar12Enter(TObject *Sender);
        void __fastcall Edt13_1Enter(TObject *Sender);
        void __fastcall Edt13_2Enter(TObject *Sender);
        void __fastcall Edt13_3Enter(TObject *Sender);
        void __fastcall Edt13_4Enter(TObject *Sender);
        void __fastcall ScrollBar13Enter(TObject *Sender);
        void __fastcall Edt14_1Enter(TObject *Sender);
        void __fastcall Edt14_2Enter(TObject *Sender);
        void __fastcall Edt14_3Enter(TObject *Sender);
        void __fastcall Edt14_4Enter(TObject *Sender);
        void __fastcall ScrollBar14Enter(TObject *Sender);
        void __fastcall Edt15_1Enter(TObject *Sender);
        void __fastcall Edt15_2Enter(TObject *Sender);
        void __fastcall Edt15_3Enter(TObject *Sender);
        void __fastcall Edt15_4Enter(TObject *Sender);
        void __fastcall ScrollBar15Enter(TObject *Sender);
        void __fastcall Edt16_1Enter(TObject *Sender);
        void __fastcall Edt16_2Enter(TObject *Sender);
        void __fastcall Edt16_3Enter(TObject *Sender);
        void __fastcall Edt16_4Enter(TObject *Sender);
        void __fastcall ScrollBar16Enter(TObject *Sender);
        void __fastcall Edt17_1Enter(TObject *Sender);
        void __fastcall Edt17_2Enter(TObject *Sender);
        void __fastcall Edt17_3Enter(TObject *Sender);
        void __fastcall Edt17_4Enter(TObject *Sender);
        void __fastcall ScrollBar17Enter(TObject *Sender);
        void __fastcall Edt18_1Enter(TObject *Sender);
        void __fastcall Edt18_2Enter(TObject *Sender);
        void __fastcall Edt18_3Enter(TObject *Sender);
        void __fastcall Edt18_4Enter(TObject *Sender);
        void __fastcall ScrollBar18Enter(TObject *Sender);
        void __fastcall Edt19_1Enter(TObject *Sender);
        void __fastcall Edt19_2Enter(TObject *Sender);
        void __fastcall Edt19_3Enter(TObject *Sender);
        void __fastcall Edt19_4Enter(TObject *Sender);
        void __fastcall ScrollBar19Enter(TObject *Sender);
        void __fastcall Edt20_1Enter(TObject *Sender);
        void __fastcall Edt20_2Enter(TObject *Sender);
        void __fastcall Edt20_3Enter(TObject *Sender);
        void __fastcall Edt20_4Enter(TObject *Sender);
        void __fastcall ScrollBar20Enter(TObject *Sender);
        void __fastcall Edt21_1Enter(TObject *Sender);
        void __fastcall Edt21_2Enter(TObject *Sender);
        void __fastcall Edt21_3Enter(TObject *Sender);
        void __fastcall Edt21_4Enter(TObject *Sender);
        void __fastcall ScrollBar21Enter(TObject *Sender);
        void __fastcall Edt22_1Enter(TObject *Sender);
        void __fastcall Edt22_2Enter(TObject *Sender);
        void __fastcall Edt22_3Enter(TObject *Sender);
        void __fastcall Edt22_4Enter(TObject *Sender);
        void __fastcall ScrollBar22Enter(TObject *Sender);
        void __fastcall Edt23_1Enter(TObject *Sender);
        void __fastcall Edt23_2Enter(TObject *Sender);
        void __fastcall Edt23_3Enter(TObject *Sender);
        void __fastcall Edt23_4Enter(TObject *Sender);
        void __fastcall ScrollBar23Enter(TObject *Sender);
        void __fastcall Edt24_1Enter(TObject *Sender);
        void __fastcall Edt24_2Enter(TObject *Sender);
        void __fastcall Edt24_3Enter(TObject *Sender);
        void __fastcall Edt24_4Enter(TObject *Sender);
        void __fastcall ScrollBar24Enter(TObject *Sender);
        void __fastcall Edt25_1Enter(TObject *Sender);
        void __fastcall Edt25_2Enter(TObject *Sender);
        void __fastcall Edt25_3Enter(TObject *Sender);
        void __fastcall Edt25_4Enter(TObject *Sender);
        void __fastcall ScrollBar25Enter(TObject *Sender);
        void __fastcall Edt26_1Enter(TObject *Sender);
        void __fastcall Edt26_2Enter(TObject *Sender);
        void __fastcall Edt26_3Enter(TObject *Sender);
        void __fastcall Edt26_4Enter(TObject *Sender);
        void __fastcall ScrollBar26Enter(TObject *Sender);
        void __fastcall Edt27_1Enter(TObject *Sender);
        void __fastcall Edt27_2Enter(TObject *Sender);
        void __fastcall Edt27_3Enter(TObject *Sender);
        void __fastcall Edt27_4Enter(TObject *Sender);
        void __fastcall ScrollBar27Enter(TObject *Sender);
        void __fastcall Edt28_1Enter(TObject *Sender);
        void __fastcall Edt28_2Enter(TObject *Sender);
        void __fastcall Edt28_3Enter(TObject *Sender);
        void __fastcall Edt28_4Enter(TObject *Sender);
        void __fastcall ScrollBar28Enter(TObject *Sender);
        void __fastcall Edt29_1Enter(TObject *Sender);
        void __fastcall Edt29_2Enter(TObject *Sender);
        void __fastcall Edt29_3Enter(TObject *Sender);
        void __fastcall Edt29_4Enter(TObject *Sender);
        void __fastcall ScrollBar29Enter(TObject *Sender);
        void __fastcall Edt30_1Enter(TObject *Sender);
        void __fastcall Edt30_2Enter(TObject *Sender);
        void __fastcall Edt30_3Enter(TObject *Sender);
        void __fastcall Edt30_4Enter(TObject *Sender);
        void __fastcall ScrollBar30Enter(TObject *Sender);
        void __fastcall ScrollBar4Enter(TObject *Sender);
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall Edt01_1Change(TObject *Sender);
        void __fastcall edtymdChange(TObject *Sender);
        void __fastcall Edt01_4Exit(TObject *Sender);
        void __fastcall PageCtrlChange(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall EdtV1Enter(TObject *Sender);
        void __fastcall ScrollBarVChange(TObject *Sender);
        void __fastcall edttlnoEnter(TObject *Sender);
        void __fastcall BtnF04Click(TObject *Sender);
        void __fastcall BtnF09Click(TObject *Sender);
        void __fastcall BtnF08Click(TObject *Sender);
        void __fastcall Rad1Click(TObject *Sender);
        void __fastcall EdtS4_1Change(TObject *Sender);
        void __fastcall EdtS4_2Change(TObject *Sender);
        void __fastcall EdtS4_3Change(TObject *Sender);
        void __fastcall edtymdKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall EdtS1_1Exit(TObject *Sender);
        void __fastcall EdtS1_2Exit(TObject *Sender);
        void __fastcall EdtS1_3Exit(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF11Enter(TObject *Sender);
        void __fastcall BtnF11Exit(TObject *Sender);
        void __fastcall BtnF12Enter(TObject *Sender);
        void __fastcall BtnF12Exit(TObject *Sender);
	void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall UpDownymdClick(TObject *Sender, TUDBtnType Button);
    void __fastcall UpDowntlnoClick(TObject *Sender, TUDBtnType Button);
    void __fastcall RGRS1Click(TObject *Sender);
     //   void __fastcall Edt16_1Change(TObject *Sender);

private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
        __fastcall TForm1(TComponent* Owner);
        void __fastcall TForm1::SetInit(int) ;
        void __fastcall TForm1::InitEdt(TNumberEdit *P_Edit, AnsiString) ;
        void __fastcall TForm1::InitPnl(TPanel *P_Pnl, AnsiString Str) ;
        void __fastcall TForm1::IsEnabledPnl(TPanel *P_Pnl, int flag);
        void __fastcall TForm1::IsEnabledEdt(TNumberEdit *P_Edit, int flag);
        void __fastcall TForm1::IsEnabledScrl(TScrollBar *P_Scrl, int flag);
        void __fastcall TForm1::SetEnabel(int ) ;
        void __fastcall TForm1::OnEdtChange(TNumberEdit *P_Edit) ;
        void __fastcall TForm1::OnEditEnter( int spflag, int dtflag, TNumberEdit *pEdit ) ;
        void __fastcall TForm1::ExtractCode(AnsiString );
        void __fastcall TForm1::SetMEMO(void);
protected:
        void __fastcall OnNotifyWriteData(TMessage &Message);
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_Notify_WriteData1, TMessage, OnNotifyWriteData)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif