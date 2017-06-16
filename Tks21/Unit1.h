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
#include <Db.hpp>
#include <DBTables.hpp>
#include "TKS21.h"
#include <Mask.hpp>


#define XScaleNM 9
#define RScaleNM 5
#define ScaleINI 0.125
#define A2 1.88
#define D4 3.267

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
    	TStatusBar *SBr1;
        TPanel *Panel9;
        TPanel *Panel1;
    	TButton *BtnF01;
    	TButton *BtnF02;
    	TButton *BtnF03;
    	TButton *BtnF04;
    	TButton *BtnF08;
    	TButton *BtnF07;
    	TButton *BtnF06;
    	TButton *BtnF05;
    	TButton *BtnF12;
    	TButton *BtnF11;
    	TButton *BtnF10;
    	TButton *BtnF09;
        TBevel *Bevel2;
        TPanel *Panel8;
    	TEdit *EdtTKSHIN;
        TPanel *Panel10;
    	TEdit *EdtSLOT;
    	TEdit *EdtELOT;
        TBevel *Bevel4;
        TBevel *Bevel5;
    	TDatabase *Database1;
    	TQuery *Query1;
	TBevel *Bevel1;
	TBevel *Bevel3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox13;
	TPanel *Panel11;
	TLabel *Label2;
	TMaskEdit *EdtSYMD;
	TPanel *Panel12;
	TLabel *Label1;
	TMaskEdit *EdtEYMD;
    TCheckBox *CheckBox14;
        TPanel *Panel13;
        TGroupBox *GroupBox1;
        TRadioButton *RadioHON;
        TRadioButton *RadioKOU;
        TRadioButton *RadioRYO;
        TGroupBox *GroupBox2;
        TRadioButton *RadioKANSA;
        TRadioButton *RadioLOT;
		void __fastcall BtnF01Click(TObject *Sender);
    	void __fastcall FormCreate(TObject *Sender);
    	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    	void __fastcall AllKeyEnter(TObject *Sender);
    	void __fastcall BtnF05Click(TObject *Sender);
    	void __fastcall BtnF12Click(TObject *Sender);
    	void __fastcall BtnF06Click(TObject *Sender);
    	void __fastcall EdtKeyPress(TObject *Sender, char &Key);
        void __fastcall Read_Ini();
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
		//�f�[�^�����֐�
        int __fastcall Search_MAIN(void);
        int __fastcall Search_KD(int testItem);
        //�f�[�^1�s�ǂݍ���
        void __fastcall ReadLineData(int testItem);

        //Excel�iX-R�Ǘ��}.xls�j �N��
		bool __fastcall Excel_Write();
        //�b�r�u�o��
        int __fastcall Write_CSVMain(void);
        void __fastcall Write_CSV(int testItem);
        //�f�[�^1�scsv�o��
        void __fastcall WriteLineData01(int testItem);
        void __fastcall WriteLineData02(int testItem);

        //�������ږ�
        AnsiString __fastcall KENSA_NAME(int testItem);
        //����P��
        AnsiString __fastcall KENSA_TANI(int testItem);
        //�v����
        AnsiString __fastcall KENSA_KIKI(int testItem);
        //�����K�i(1) �����K�i(2) ����K�i(3)
        int __fastcall KENSA_KIKAKU(int testItem);
        //�����_�ȉ��̌���
        int __fastcall KENSA_KETA(int testItem);
        //����(ex "#0.000")
        AnsiString __fastcall KENSA_SYOSIKI(int n);

        //�Ђ̌v�Z
        void __fastcall SubSGM(int testItem);
		//CAL�̏�����
		void __fastcall FormatCAL(void);

        //�ڐ���̌v�Z
        void __fastcall SubXAveScale(int testItem);
        void __fastcall SubRScale(void);

        AnsiString __fastcall ConvKETA1(int keta,double n);
        AnsiString __fastcall ConvKETA2(int keta,double n);
        void __fastcall ExtractCode(AnsiString str);
        AnsiString __fastcall DelSEPA(AnsiString sYMD);
        AnsiString __fastcall InsSEPA(AnsiString sYMD);

        //����`�F�b�N
        int __fastcall Check_Print(int testItem);

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

extern int iKojoKbn ;            //�H��敪 2016/06/24 �ǉ�
//---------------------------------------------------------------------------
#endif