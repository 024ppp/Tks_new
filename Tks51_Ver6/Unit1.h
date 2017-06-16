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
//#include "NumberEdit.h"
#include <Clipbrd.hpp>
#include <DB.hpp>
#include "NumberEdit.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TStatusBar *SBr1;
        TPanel *Panel9;
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
        TLabel *Label18;
        TLabel *Label20;
        TBevel *Bevel1;
        TPanel *Panel20;
        TPanel *Panel2;
    TPanel *PnlBumCode;
    TPanel *PnlBumName;
        TPanel *Panel5;
    TPanel *PnlTanCode;
    TPanel *PnlTanName;
        TPanel *Panel1;
    TStringGrid *SGr1;
        TPanel *Panel19;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel21;
        TPanel *Panel8;
        TPanel *Panel23;
    TEdit *EdtCOD3;
        TPanel *Panel24;
    TEdit *EdtCOD2;
        TPanel *Panel10;
    TEdit *EdtCOD1;
        TPanel *Panel22;
        TPanel *Panel16;
    TEdit *EdtCOD4;
        TPanel *Panel18;
        TPanel *Panel25;
    TLabel *LblA1;
    TLabel *LblB1;
    TLabel *LblF1;
    TLabel *LblF2;
    TLabel *LblF3;
    TLabel *LblE1;
    TLabel *LblD1;
    TLabel *LblG1;
    TLabel *LblG2;
    TLabel *LblH1;
    TLabel *LblG3;
    TLabel *LblG4;
    TLabel *LblI1;
    TLabel *LblK1;
        TBevel *Bevel2;
    TPanel *Pnl01;
    TEdit *Edt01;
    TPanel *Pnl03;
    TEdit *Edt03;
    TPanel *Pnl04;
    TEdit *Edt04;
    TEdit *Edt05;
    TPanel *Pnl05;
    TPanel *Pnl06;
    TEdit *Edt06;
    TPanel *Pnl07;
    TPanel *Pnl08;
    TPanel *Pnl09;
    TComboBox *ComBox09;
    TPanel *Pnl10;
    TPanel *Pnl12;
    TPanel *Pnl13;
    TPanel *PnlA;
    TCheckBox *ChkBoxA;
    TCheckBox *ChkBoxB;
    TCheckBox *ChkBoxF;
    TCheckBox *ChkBoxE;
    TCheckBox *ChkBoxD;
    TCheckBox *ChkBoxG;
    TCheckBox *ChkBoxH;
    TCheckBox *ChkBoxI;
    TCheckBox *ChkBoxJ;
    TCheckBox *ChkBoxK;
    TCheckBox *ChkBoxL;
    TPanel *PnlB;
    TPanel *PnlF;
    TPanel *PnlE;
    TComboBox *ComBoxE2;
    TPanel *PnlD;
    TPanel *PnlG;
    TPanel *PnlH;
    TComboBox *ComBoxH3;
    TPanel *PnlI;
    TPanel *PnlJ;
    TPanel *PnlK;
    TPanel *PnlL;
    TPanel *PnlADDYMD1;
    TPanel *PnlUPDYMD1;
    TPanel *PnlUPDCNT1;
    TPanel *PnlADDYMD2;
    TPanel *PnlUPDYMD2;
    TPanel *PnlUPDCNT2;
        TPanel *Panel47;
        TPanel *Panel48;
        TPanel *Panel49;
        TPanel *Panel50;
        TPanel *Panel51;
        TPanel *Panel52;
        TPanel *Panel53;
        TPanel *Panel54;
        TPanel *Panel55;
        TPanel *Panel56;
        TPanel *Panel57;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TBevel *Bevel6;
        TBevel *Bevel7;
    TPanel *Pnl11;
    TComboBox *ComBox11;
    TEdit *Edt02;
    TPanel *PnlC;
    TLabel *LblC1;
    TCheckBox *ChkBoxC;
        TPanel *Panel66;
    TLabel *LblJ1;
    TLabel *LblL1;
    TPanel *Panel67;
    TCheckBox *ChkBoxM;
    TPanel *PnlM;
    TLabel *LblM1;
    TLabel *LblG5;
    TLabel *LblH2;
    TLabel *LblH3;
    TBevel *Bevel3;
    TDatabase *Database1;
    TQuery *Query1;
    TNumberEdit *Edt08;
    TNumberEdit *Edt10;
    TNumberEdit *Edt12;
    TNumberEdit *Edt13;
    TNumberEdit *ChkEdtA;
    TNumberEdit *ChkEdtB;
    TNumberEdit *ChkEdtC;
    TNumberEdit *ChkEdtD;
    TNumberEdit *ChkEdtE;
    TNumberEdit *ChkEdtF;
    TNumberEdit *ChkEdtG;
    TNumberEdit *ChkEdtH;
    TNumberEdit *ChkEdtI;
    TNumberEdit *ChkEdtJ;
    TNumberEdit *ChkEdtK;
    TNumberEdit *ChkEdtL;
    TNumberEdit *ChkEdtM;
    TNumberEdit *EdtA1;
    TNumberEdit *EdtA2;
    TNumberEdit *EdtB1;
    TNumberEdit *EdtB2;
    TNumberEdit *EdtC1;
    TNumberEdit *EdtC2;
    TNumberEdit *EdtF1;
    TNumberEdit *EdtF2;
    TNumberEdit *EdtF3;
    TNumberEdit *EdtE1;
    TNumberEdit *EdtE3;
    TNumberEdit *EdtD1;
    TNumberEdit *EdtD2;
    TNumberEdit *EdtG1;
    TNumberEdit *EdtG2;
    TNumberEdit *EdtG3;
    TNumberEdit *EdtG4;
    TNumberEdit *EdtH1;
    TNumberEdit *EdtH2;
    TNumberEdit *EdtH4;
    TNumberEdit *EdtI1;
    TNumberEdit *EdtI2;
    TNumberEdit *EdtJ1;
    TNumberEdit *EdtJ2;
    TNumberEdit *EdtK1;
    TNumberEdit *EdtK2;
    TNumberEdit *EdtL1;
    TNumberEdit *EdtL2;
    TNumberEdit *EdtM1;
    TNumberEdit *EdtM2;
    TEdit *Edt07;
    TLabel *LblA2;
    TLabel *LblB2;
    TLabel *LblC2;
    TLabel *LblM2;
    TLabel *LblI2;
    TLabel *LblJ2;
    TLabel *LblK2;
    TLabel *LblL2;
    TLabel *LblF4;
    TLabel *LblE2;
    TEdit *EdtF4;
    TPanel *PnlUPDCHR1;
    TPanel *PnlUPDCHR2;
    TPanel *PnlREVCNT1;
    TPanel *PnlREVCNT2;
    TPanel *PnlMEMO;
    TEdit *EdtMEMO;
    TPanel *Panel3;
    TCheckBox *CheckBoxRireki;
    TBevel *Bevel33;
    TQuery *Query2;
    TPanel *PnlN;
    TNumberEdit *EdtN1;
    TLabel *LblN1;
    TNumberEdit *EdtN2;
    TComboBox *ComBoxN3;
    TNumberEdit *EdtN4;
    TLabel *LblN2;
    TLabel *LblN3;
    TPanel *Panel4;
    TCheckBox *ChkBoxN;
    TNumberEdit *ChkEdtN;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnF01Click(TObject *Sender);
    void __fastcall BtnF05Click(TObject *Sender);
    void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall ChkBoxClick(TObject *Sender);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr1KeyPress(TObject *Sender, char &Key);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall ComBox11Change(TObject *Sender);
    void __fastcall FormEnter(TObject *Sender);
    void __fastcall FormKeyPress(TObject *Sender, char &Key);
    void __fastcall ValueChenge(TObject *Sender);
    void __fastcall Edt10Change(TObject *Sender);
    void __fastcall SGr1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall ComBox09Change(TObject *Sender);
private:	// ���[�U�[�錾

    // ���[�U�[���
    int     USER_COD;
    String  USER_NAM;
    String  BUMO_COD;
    String  BUMO_NAM;

    bool    DataSave;

    void __fastcall InitEdt();
    void __fastcall InitEdt2(bool status);
    void __fastcall EdtStatus(int tag, bool status);
    bool __fastcall AddData();
    bool __fastcall DelData();
    bool __fastcall CollectData(String OldKey);
    void __fastcall SetZAISHITSU(int flag,String KeyStr );

    struct TKM02{                // ���i�K�i�}�X�^
        AnsiString DTKSCOD;      // ���Ӑ�R�[�h
        AnsiString DTKSNAM;      // ���Ӑ於��
        AnsiString DTKSHIN;      // ���Ӑ�i��
        AnsiString HINBAN;       // ���Еi��
        AnsiString ZISCOD;       // �ގ��R�[�h
        AnsiString ZISNAM;       // �ގ���
        AnsiString SYOSCOD;      // �Đ��R�[�h
        int        SORTKEY;      // �\�[�g�L�[
        int        KEIJKBN;      // �`��敪
        int        SK_LD_LNG;    // ����敪�@������
        int        SK_BURASI;    // ����敪�@�u���V��
        int        SK_BURASIT;   // ����敪�@�u���V���c����
        int        SK_LD_TR;     // ����敪�@����t��R
        int        SK_LD_HP;     // ����敪�@���������x
        int        SK_BOTAI;     // ����敪�@��̔�d
        int        SK_KOYU;      // ����敪�@�ŗL��R
        int        SK_MAGE;      // ����敪�@�R�ܗ�
        int        SK_HSC_A;     // ����敪�@HsC�d�x�i���ʁj
        int        SK_HSC_S;     // ����敪�@HsC�d�x�i���ʁj
        int        SK_HSD_A;     // ����敪�@HsD�d�x�i���ʁj
        int        SK_HSD_S;     // ����敪�@HsD�d�x�i���ʁj
        int        SK_ZAKUT;     // ����敪�@����
        int        HIST_SOKUT;   // �q�X�g�O�����i���萔�j
        int        HIST_KIKAK;   // �q�X�g�O�����i�K�i�j
        double     HIST_MIN;     // �q�X�g�O�����i�����j
        double     HIST_MAX;     // �q�X�g�O�����i����j
        double     LD_LNG_MIN;   // ���[�h�������i�����j
        double     LD_LNG_MAX;   // ���[�h�������i����j
        double     BURASI_MIN;   // �u���V���i�����j
        double     BURASI_MAX;   // �u���V���i����j
        double     BURASIT_MIN;  // �u���V���c�����i�����j
        double     BURASIT_MAX;  // �u���V���c�����i����j
        double     LD_TR_DENA;   // ���[�h��t��R�i�d���j
        int        LD_TR_DENR;   // ���[�h��t��R�i�d���j
        int        LD_TR_TIME;   // ���[�h��t��R�i���ԁj
        AnsiString LD_TR_TYPE;   // ���[�h��t��R�iTYPE�j
        double     LD_HP_KYO;    // ���[�h���������x
        int        LD_HP_TAN;    // ���[�h���������x�i�P�ʁj
        int        LD_HP_SPD;    // ���[�h���������x�i���x�j
        double     BOTAI_MIN;    // ��̔�d�i�����j
        double     BOTAI_MAX;    // ��̔�d�i����j
        int        KOYU_MIN;     // �ŗL��R���i�����j
        int        KOYU_MAX;     // �ŗL��R���i����j
        double     KOYU_DEN;     // �ŗL��R���i�d���j
        int        KOYU_PRO;     // �ŗL��R���i�v���[�u�j
        double     MAGE_MIN;     // �Ȃ����x�i�����j
        double     MAGE_MAX;     // �Ȃ����x�i����j
        int        MAGE_TAN;     // �Ȃ����x�i�P�ʁj
        double     MAGE_SPAN;    // �Ȃ����x�i�X�p���j
        int        HSC_A_MIN;    // HsC�d�x ���ʁi�����j
        int        HSC_A_MAX;    // HsC�d�x ���ʁi����j
        int        HSC_S_MIN;    // HsC�d�x ���ʁi�����j
        int        HSC_S_MAX;    // HsC�d�x ���ʁi����j
        double     HSD_A_MIN;    // HsD�d�x ���ʁi�����j
        double     HSD_A_MAX;    // HsD�d�x ���ʁi����j
        double     HSD_S_MIN;    // HsD�d�x ���ʁi�����j
        double     HSD_S_MAX;    // HsD�d�x ���ʁi����j
        int        ZAKUT_MIN;    // �����i�����j
        int        ZAKUT_MAX;    // �����i����j
        AnsiString ADDYMD;       // �o�^��
        AnsiString ADDTIM;       // �o�^����
        AnsiString UPDYMD;       // �ύX��
        AnsiString UPDTIM;       // �ύX����
        int        UPDCHR;       // �X�V��
        int        UPDCNT;       // �X�V��
        int        REVCNT;       // �����ԍ�
        AnsiString MEMO;         // ���l                    //2002/11/21 E.Takase Add
        int        SK_MAGEG;     // ����敪�@�����Ȃ����x  //2002/12/04 E.Takase Add
        double     MAGEG_MIN;    // �����Ȃ����x�i�����j    //2002/12/04 E.Takase Add
        double     MAGEG_MAX;    // �����Ȃ����x�i����j    //2002/12/04 E.Takase Add
        int        MAGEG_TAN;    // �����Ȃ����x�i�P�ʁj    //2002/12/04 E.Takase Add
        double     MAGEG_SPAN;   // �����Ȃ����x�i�X�p���j  //2002/12/04 E.Takase Add
    }KM02;

    void __fastcall GetSGrData(int ARow);
    void __fastcall GetEdtData(void);
    void __fastcall SetEdtData(int ARow);
public:		// ���[�U�[�錾
    TClipboard *ClpBrd;
    __fastcall TForm1(TComponent* Owner);
    void __fastcall ExtractCode(AnsiString str);
    int __fastcall UpdRirekiNo(int ARow);
    void __fastcall InsSGrRirekiData(void);
    AnsiString __fastcall GetTANNAM(AnsiString strTANSYA);
    AnsiString __fastcall StrReplace(AnsiString str, AnsiString a, AnsiString b);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
