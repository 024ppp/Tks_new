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
    TQRShape *QRShapeA;
    TQRShape *QRShapeB;
    TQRShape *QRShapeC;
    TQRShape *QRShapeD;
    TQRLabel *QRLabelA1;
    TQRLabel *QRLabelA2;
    TQRLabel *QRLabelA3;
    TQRLabel *QRLabelA4;
    TQRLabel *QRLabelA5;
    TQRLabel *QRLabelA6;
    TQRLabel *QRLabelB1;
    TQRLabel *QRLabelB2;
    TQRLabel *QRLabelB4;
    TQRLabel *QRLabelB3;
    TQRLabel *QRLabelB5;
    TQRLabel *QRLabelB6;
    TQRLabel *QRLabelC1;
    TQRLabel *QRLabelC4;
    TQRLabel *QRLabelC6;
    TQRLabel *QRLabelC5;
    TQRLabel *QRLabelC3;
    TQRLabel *QRLabelC2;
    TQRLabel *QRLabelD6;
    TQRLabel *QRLabelD4;
    TQRLabel *QRLabelD1;
    TQRLabel *QRLabelD2;
    TQRLabel *QRLabelD3;
    TQRLabel *QRLabelD5;
    TQRBand *QRBand2;
	TQRLabel *QRLabelA7;
	TQRLabel *QRLabelB7;
	TQRLabel *QRLabelC7;
	TQRLabel *QRLabelD7;
    void __fastcall QRBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
    void __fastcall QuickRep1BeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
    void __fastcall QuickRep1AfterPrint(TObject *Sender);
    void __fastcall QuickRep1NeedData(TObject *Sender, bool &MoreData);
private:	// ユーザー宣言
    bool bStop;
    int iPrtPos;
    int iPrtCnt;
    int iBndCnt;
    AnsiString sBuf;
    AnsiString sYMD;

    HANDLE  hMemCopy;

    struct HIST_TP{              // ﾋｽﾄｸﾞﾗﾑ検査用ﾀｯｸ印刷
        char DTKSHIN[21];        // 得意先品番
        char LOTNO[7];           // ロットNO
        int  NO;                 // 番号
    } *HIST_TPrt;

public:		// ユーザー宣言

    int iPrtStart;

    __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
