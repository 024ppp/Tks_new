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
#include <string.h>
#include <math.h>
#include "TKS40.h"
#include "NumberEdit.h"
#include <Db.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#define MAX_PATH 1028

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
        TPanel *Panel13;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel23;
        TPanel *Panel24;
    TEdit *EdtHIN;
        TPanel *Panel10;
    TPanel *PnlNO;
        TPanel *Panel22;
    TComboBox *Cmb3;
        TPanel *Panel16;
    TEdit *EdtLOT;
        TPanel *Panel12;
    TComboBox *Cmb1;
    TComboBox *Cmb2;
    TNumberEdit *Edt1;
    TNumberEdit *Edt2;
    TNumberEdit *Edt3;
    TQuery *Query1;
    TDatabase *Database1;
    TEdit *EdtKMK;
	TEdit *EdtZIS;
    TQuery *Query_Kdb2;
    TQuery *Query_Kdb1;
	TPanel *EdtZISNAM;
    TMaskEdit *EdtYMD;
    TPanel *Panel11;
    TComboBox *Cmb5;
    TEdit *EdtKEIJKBN;
    TQuery *Query2;
	TEdit *EdtJYOKEN1;
	TEdit *EdtJYOKEN2;
	TEdit *EdtJYOKEN3;
    TPanel *Panel18;
    TEdit *Edt4;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BtnF01Click(TObject *Sender);
        void __fastcall BtnF05Click(TObject *Sender);
        void __fastcall BtnF04Click(TObject *Sender);
        void __fastcall BtnF12Click(TObject *Sender);
    void __fastcall BtnF02Click(TObject *Sender);
    void __fastcall BtnF03Click(TObject *Sender);
    void __fastcall BtnF06Click(TObject *Sender);
    void __fastcall BtnF08Click(TObject *Sender);
    void __fastcall BtnF09Click(TObject *Sender);
    void __fastcall BtnF10Click(TObject *Sender);
    void __fastcall BtnF11Click(TObject *Sender);
    void __fastcall BtnF07Click(TObject *Sender);
    void __fastcall SGr1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall SGr1KeyPress(TObject *Sender, char &Key);
    void __fastcall Cmb3Change(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall Cmb1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall Cmb2KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall AllKeyEnter(TObject *Sender);
    void __fastcall EdtHINExit(TObject *Sender);
    void __fastcall Cmb1Change(TObject *Sender);
    void __fastcall Cmb2Change(TObject *Sender);
    void __fastcall Cmb4Change(TObject *Sender);
    void __fastcall AllKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall EdtKeyPress(TObject *Sender, char &Key);
    void __fastcall Read_Ini();
	void __fastcall Cmb5Change(TObject *Sender);
private:	// ユーザー宣言
    bool __fastcall AddData();
    bool __fastcall CollectData(String OldKey);
    bool __fastcall CSV2_Write();
    bool __fastcall Excel2_Write();
    void __fastcall Sub_Tmp_KDB1(int pos);
    void __fastcall Toukei_Tmp_KDB1(int k);
    void __fastcall AddHIST();    //ﾋｽﾄ追加
	bool __fastcall DelData();
//    void __fastcall KIKAKU_MINSet(int CmbIndx);		//下限規格のセット
//    void __fastcall KIKAKU_MAXSet(int CmbIndx);		//上限規格のセット
    void __fastcall KENSAKMK_Set(int CmbIndx);		//検査項目のセット
    int __fastcall KENSACmb_Set(int KMK,double JYOKEN);//検査項目CmbIndxのセット
    AnsiString __fastcall KENSASGr_Set(int KMK,double JYOKEN, double KIKAKU, AnsiString tani);//検査項目SGrのセット
    String  NowKey;
    bool    NotFound;
    int __fastcall KDB1_Serch01(void);//KDB1検索
    int __fastcall KM02_Serch01(void);//KM02検索
	int __fastcall MAIN_Serch01(void);
	void  __fastcall Tmp_KDB1_SYOKIKA(void);


public:		// ユーザー宣言
    	int __fastcall DTKSHIN_Serch();	//既定の規格値を検索
        int __fastcall CheckTANI(int K,AnsiString sTANI);  //単位と規格があっているかチェック
        void __fastcall SetTANI(int K);                    //規格にあった単位をセット
        AnsiString __fastcall DelSEPA(AnsiString sYMD);
        AnsiString __fastcall InsSEPA(AnsiString sYMD);
        void __fastcall ExtractCode(AnsiString str);
        __fastcall TForm1(TComponent* Owner);
        int KIKAKU_KETA;									//選択されている規格の小数点以下の桁数

        int SOKUTEI_SAVE_FLAG;								//「戻る」のとき保存しないで終了にしたとき0
        AnsiString ExcelExePATH;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
