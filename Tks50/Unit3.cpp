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

    // �o���h�����
    if( (iPrtStart <= iBndCnt*4+0) )   PrtA =true;
    if( (iPrtStart <= iBndCnt*4+1) )   PrtB =true;
    if( (iPrtStart <= iBndCnt*4+2) )   PrtC =true;
    if( (iPrtStart <= iBndCnt*4+3) )   PrtD =true;

    iBndCnt++ ;

    if( PrtA ){

        QRLabelA1->Caption = sYMD;
        QRLabelA2->Caption = "�i��:";
        QRLabelA3->Caption = "���b�g:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// ���Ӑ�i��
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
        QRLabelA5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ���b�gNO
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
        QRLabelA4->Caption = ""; // ���Ӑ�i��
        QRLabelA7->Caption = ""; //    �V
        QRLabelA5->Caption = ""; // ���b�gNO
        QRLabelA6->Caption = ""; // NO
        QRShapeA->Pen->Color = clWhite;
    }

    if( PrtB ){
        QRLabelB1->Caption = sYMD;
        QRLabelB2->Caption = "�i��:";
        QRLabelB3->Caption = "���b�g:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// ���Ӑ�i��
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
        QRLabelB5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ���b�gNO
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
        QRLabelB4->Caption = ""; // ���Ӑ�i��
        QRLabelB7->Caption = ""; //    �V
        QRLabelB5->Caption = ""; // ���b�gNO
        QRLabelB6->Caption = ""; // NO
        QRShapeB->Pen->Color = clWhite;
    }

    if( PrtC ){
        QRLabelC1->Caption = sYMD;
        QRLabelC2->Caption = "�i��:";
        QRLabelC3->Caption = "���b�g:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// ���Ӑ�i��
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
        QRLabelC5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ���b�gNO
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
        QRLabelC4->Caption = ""; // ���Ӑ�i��
        QRLabelC7->Caption = ""; //    �V
        QRLabelC5->Caption = ""; // ���b�gNO
        QRLabelC6->Caption = ""; // NO
        QRShapeC->Pen->Color = clWhite;
    }

    if( PrtD ){
        QRLabelD1->Caption = sYMD;
        QRLabelD2->Caption = "�i��:";
        QRLabelD3->Caption = "���b�g:";
        sHIN = HIST_TPrt[iPrtPos].DTKSHIN;// ���Ӑ�i��
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
        QRLabelD5->Caption = HIST_TPrt[iPrtPos].LOTNO;  // ���b�gNO
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
        QRLabelD4->Caption = ""; // ���Ӑ�i��
        QRLabelD7->Caption = ""; //    �V
        QRLabelD5->Caption = ""; // ���b�gNO
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

    // �����\���
    sYMD = Form1->EdtCOD->Text;

    // �������̊m��
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
        // ˽ĸ��ё��萔
        sBuf = Form1->SGr1->Cells[28][i];
        if( sBuf.Length() > 0 ){
            if( StrToInt(Form1->SGr1->Cells[28][i]) > 0 ){
                sBuf = Form1->SGr1->Cells[5][i];      // ���b�gNO
                strcpy( HIST_TPrt[iPrtCnt].LOTNO , sBuf.c_str() );
                sBuf = Form1->SGr1->Cells[4][i];      // ���Ӑ�i��
                strcpy( HIST_TPrt[iPrtCnt].DTKSHIN, sBuf.c_str() );
                if( sBufNO == sBuf ){
                    // �O�̕i�ԂƓ�����
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
                HIST_TPrt[iPrtCnt].NO = cnt;                        // �ԍ�
                iPrtCnt++;
            }
        }
    }

}


//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1AfterPrint(TObject *Sender)
{
    // �������̊m��
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

