//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::QRBand1BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    AnsiString   sHIN;
    int          iLen;
    bool    PrtA, PrtB, PrtC, PrtD ;

    PrtA = false;
    PrtB = false;
    PrtC = false;
    PrtD = false;

    // バンド印刷回数
    if( (iPrtStart <= iBndCnt*4+0) )   PrtA =true;
    if( (iPrtStart <= iBndCnt*4+1) )   PrtB =true;
    if( (iPrtStart <= iBndCnt*4+2) )   PrtC =true;
    if( (iPrtStart <= iBndCnt*4+3) )   PrtD =true;

    iBndCnt++ ;

    if( PrtA ){

        QRLabelA1->Caption = sYMD;
        QRLabelA2->Caption = "品番:";
        QRLabelA3->Caption = "ロット:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// 得意先品番
        if( sHIN.Length() >14 ){
            QRLabelA4->Caption = sHIN.SetLength(14);
            sHIN = HIST_TPrt[iPrtPos].DTKSHIN;
            iLen = sHIN.Length() - 14;
            if( iLen <= 0 ) iLen = 0;
            QRLabelA7->Caption = sHIN.SubString(15, iLen);
        }
        else{
            QRLabelA4->Caption = sHIN;
            QRLabelA7->Caption = "";
        }
        QRLabelA5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ロットNO
        if( HIST_TPrt[iPrtPos].NO > 0 ){                // NO
            QRLabelA6->Caption = IntToStr(HIST_TPrt[iPrtPos].NO);
        }
        else{
            QRLabelA6->Caption = "";
        }
        QRShapeA->Pen->Color = clBlack;
        iPrtPos++;
        if( iPrtPos >= iPrtCnt ){
            PrtB = false;
            PrtC = false;
            PrtD = false;
            bStop = true;
        }
    }
    else{
        QRLabelA1->Caption = "";
        QRLabelA2->Caption = "";
        QRLabelA3->Caption = "";
        QRLabelA4->Caption = ""; // 得意先品番
        QRLabelA7->Caption = ""; //    〃
        QRLabelA5->Caption = ""; // ロットNO
        QRLabelA6->Caption = ""; // NO
        QRShapeA->Pen->Color = clWhite;
    }

    if( PrtB ){
        QRLabelB1->Caption = sYMD;
        QRLabelB2->Caption = "品番:";
        QRLabelB3->Caption = "ロット:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// 得意先品番
        if( sHIN.Length() >14 ){
            QRLabelB4->Caption = sHIN.SetLength(14);
            sHIN = HIST_TPrt[iPrtPos].DTKSHIN;
            iLen = sHIN.Length() - 14;
            if( iLen <= 0 ) iLen = 0;
            QRLabelB7->Caption = sHIN.SubString(15, iLen);
        }
        else{
            QRLabelB4->Caption = sHIN;
            QRLabelB7->Caption = "";
        }
        QRLabelB5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ロットNO
        if( HIST_TPrt[iPrtPos].NO > 0 ){                // NO
            QRLabelB6->Caption = IntToStr(HIST_TPrt[iPrtPos].NO);
        }
        else{
            QRLabelB6->Caption = "";
        }
        QRShapeB->Pen->Color = clBlack;
        iPrtPos++;
        if( iPrtPos >= iPrtCnt ){
            PrtC = false;
            PrtD = false;
            bStop = true;
        }
    }
    else{
        QRLabelB1->Caption = "";
        QRLabelB2->Caption = "";
        QRLabelB3->Caption = "";
        QRLabelB4->Caption = ""; // 得意先品番
        QRLabelB7->Caption = ""; //    〃
        QRLabelB5->Caption = ""; // ロットNO
        QRLabelB6->Caption = ""; // NO
        QRShapeB->Pen->Color = clWhite;
    }

    if( PrtC ){
        QRLabelC1->Caption = sYMD;
        QRLabelC2->Caption = "品番:";
        QRLabelC3->Caption = "ロット:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// 得意先品番
        if( sHIN.Length() >14 ){
            QRLabelC4->Caption = sHIN.SetLength(14);
            sHIN = HIST_TPrt[iPrtPos].DTKSHIN;
            iLen = sHIN.Length() - 14;
            if( iLen <= 0 ) iLen = 0;
            QRLabelC7->Caption = sHIN.SubString(15, iLen);
        }
        else{
            QRLabelC4->Caption = sHIN;
            QRLabelC7->Caption = "";
        }
        QRLabelC5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ロットNO
        if( HIST_TPrt[iPrtPos].NO > 0 ){                // NO
            QRLabelC6->Caption = IntToStr(HIST_TPrt[iPrtPos].NO);
        }
        else{
            QRLabelC6->Caption = "";
        }
        QRShapeC->Pen->Color = clBlack;
        iPrtPos++;
        if( iPrtPos >= iPrtCnt ){
            PrtD = false;
            bStop = true;
        }
    }
    else{
        QRLabelC1->Caption = "";
        QRLabelC2->Caption = "";
        QRLabelC3->Caption = "";
        QRLabelC4->Caption = ""; // 得意先品番
        QRLabelC7->Caption = ""; //    〃
        QRLabelC5->Caption = ""; // ロットNO
        QRLabelC6->Caption = ""; // NO
        QRShapeC->Pen->Color = clWhite;
    }

    if( PrtD ){
        QRLabelD1->Caption = sYMD;
        QRLabelD2->Caption = "品番:";
        QRLabelD3->Caption = "ロット:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// 得意先品番
        if( sHIN.Length() >14 ){
            QRLabelD4->Caption = sHIN.SetLength(14);
            sHIN = HIST_TPrt[iPrtPos].DTKSHIN;
            iLen = sHIN.Length() - 14;
            if( iLen <= 0 ) iLen = 0;
            QRLabelD7->Caption = sHIN.SubString(15, iLen);
        }
        else{
            QRLabelD4->Caption = sHIN;
            QRLabelD7->Caption = "";
        }
        QRLabelD5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ロットNO
        if( HIST_TPrt[iPrtPos].NO > 0 ){                // NO
            QRLabelD6->Caption = IntToStr(HIST_TPrt[iPrtPos].NO);
        }
        else{
            QRLabelD6->Caption = "";
        }
        QRShapeD->Pen->Color = clBlack;
        iPrtPos++;
        if( iPrtPos >= iPrtCnt ){
            bStop = true;
        }
    }
    else{
        QRLabelD1->Caption = "";
        QRLabelD2->Caption = "";
        QRLabelD3->Caption = "";
        QRLabelD4->Caption = ""; // 得意先品番
        QRLabelD7->Caption = ""; //    〃
        QRLabelD5->Caption = ""; // ロットNO
        QRLabelD6->Caption = ""; // NO
        QRShapeD->Pen->Color = clWhite;
    }

}


//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    int     i;
    int     cnt;
    String  sBufNO;

    bStop = false;
    iBndCnt = 0;
    iPrtPos = 0;

    iPrtCnt = 0;
    for( i=0; i<Form1->SGr1->RowCount; i++ ){
        sBuf = Form1->SGr1->Cells[28][i];
        if( sBuf.Length() > 0 ){
            if( StrToInt(Form1->SGr1->Cells[28][i]) > 0 ){
                iPrtCnt++;
            }
        }
    }

    // 検査予定日
    sYMD = Form1->EdtCOD->Text;

    // メモリの確保
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }
    hMemCopy = GlobalAlloc( GHND, sizeof(struct HIST_TP) * iPrtCnt );
    if( hMemCopy == NULL ){
        return;
    }
    HIST_TPrt = (struct HIST_TP *)GlobalLock(hMemCopy);
    if( hMemCopy == NULL ){
        return;
    }

    iPrtCnt = 0;
    cnt = 0;
    sBufNO = "";
    for( i=0; i<Form1->SGr1->RowCount; i++ ){
        // ﾋｽﾄｸﾞﾗﾑ測定数
        sBuf = Form1->SGr1->Cells[28][i];
        if( sBuf.Length() > 0 ){
            if( StrToInt(Form1->SGr1->Cells[28][i]) > 0 ){
                sBuf = Form1->SGr1->Cells[5][i];      // ロットNO
                strcpy( HIST_TPrt[iPrtCnt].LOTNO , sBuf.c_str() );
                sBuf = Form1->SGr1->Cells[4][i];      // 得意先品番
                strcpy( HIST_TPrt[iPrtCnt].DTKSHIN, sBuf.c_str() );
                if( sBufNO == sBuf ){
                    // 前の品番と同じ時
                    if( cnt == 0 ){
                        HIST_TPrt[iPrtCnt-1].NO = 1;
                        cnt++;
                    }
                    cnt++;
                }
                else{
                    cnt=0;
                    sBufNO = Form1->SGr1->Cells[4][i];
                }
                HIST_TPrt[iPrtCnt].NO = cnt;                        // 番号
                iPrtCnt++;
            }
        }
    }

}


//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1AfterPrint(TObject *Sender)
{
    // メモリの確保
    if( hMemCopy ){
        GlobalUnlock( hMemCopy );
        GlobalFree( hMemCopy );
    }
}


//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    if( bStop ){
        MoreData = false;
    }
    else{
        MoreData = true;
    }
}
//---------------------------------------------------------------------------

