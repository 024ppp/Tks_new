//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
    : TForm(Owner)
{
}


//---------------------------------------------------------------------------
void __fastcall TForm5::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    if( bStop ){
        MoreData = false;
    }
    else{
        MoreData = true;
    }
}


//---------------------------------------------------------------------------
void __fastcall TForm5::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    int   i,k;
    div_t x;
    String sBuf;

    // 変数の初期化
    bStop = false;
    iPrtPosTR = 0;  // トレーNO

    // まだ続きが有るかどうかチェックします。
    for( i=0; i<Form1->SGr1->RowCount; i++ ){
        sBuf = Trim(Form1->SGr1->Cells[4][i]);
        if( sBuf.Length() > 0 ){
            k = i;
        }
    }
    x = div( k, 30 );
    LastTR = x.quot;

    // 検査予定日
    QRLbl_KENSAYMD->Caption = Form1->EdtCOD->Text;
}


//---------------------------------------------------------------------------
void __fastcall TForm5::QRBand2BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    int i,k;
    int iStartRow;
    String  sBuf;
    div_t x;


    // クリアーします
    PrtClear();

    bStop = true;
    iStartRow = iPrtPosTR * 30;
    for( i=iStartRow; i<Form1->SGr1->RowCount; i++ ){
        x = div( i, 30 );
        sBuf = Trim(Form1->SGr1->Cells[28][i]);
        if( sBuf.Length() == 0 )    sBuf = "0";
        if( i < (iStartRow+30) && LastTR >= x.quot ){
            // 左上部の印刷をします
            switch( x.rem ){
                case 0: QRLbl_TrA->Caption = x.quot + 1;
                        QRLbl_HinA01->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA01->Caption = "○";
                        QRLbl_LotA01->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA01->Caption = Form1->SGr1->Cells[7][i];       break;
                case 1: QRLbl_HinA02->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA02->Caption = "○";
                        QRLbl_LotA02->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA02->Caption = Form1->SGr1->Cells[7][i];       break;
                case 2: QRLbl_HinA03->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA03->Caption = "○";
                        QRLbl_LotA03->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA03->Caption = Form1->SGr1->Cells[7][i];       break;
                case 3: QRLbl_HinA04->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA04->Caption = "○";
                        QRLbl_LotA04->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA04->Caption = Form1->SGr1->Cells[7][i];       break;
                case 4: QRLbl_HinA05->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA05->Caption = "○";
                        QRLbl_LotA05->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA05->Caption = Form1->SGr1->Cells[7][i];       break;
                case 5: QRLbl_HinA06->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA06->Caption = "○";
                        QRLbl_LotA06->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA06->Caption = Form1->SGr1->Cells[7][i];       break;
                case 6: QRLbl_HinA07->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA07->Caption = "○";
                        QRLbl_LotA07->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA07->Caption = Form1->SGr1->Cells[7][i];       break;
                case 7: QRLbl_HinA08->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA08->Caption = "○";
                        QRLbl_LotA08->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA08->Caption = Form1->SGr1->Cells[7][i];       break;
                case 8: QRLbl_HinA09->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA09->Caption = "○";
                        QRLbl_LotA09->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA09->Caption = Form1->SGr1->Cells[7][i];       break;
                case 9: QRLbl_HinA10->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA10->Caption = "○";
                        QRLbl_LotA10->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA10->Caption = Form1->SGr1->Cells[7][i];       break;
                case 10:QRLbl_HinA11->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA11->Caption = "○";
                        QRLbl_LotA11->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA11->Caption = Form1->SGr1->Cells[7][i];       break;
                case 11:QRLbl_HinA12->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA12->Caption = "○";
                        QRLbl_LotA12->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA12->Caption = Form1->SGr1->Cells[7][i];       break;
                case 12:QRLbl_HinA13->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA13->Caption = "○";
                        QRLbl_LotA13->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA13->Caption = Form1->SGr1->Cells[7][i];       break;
                case 13:QRLbl_HinA14->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA14->Caption = "○";
                        QRLbl_LotA14->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA14->Caption = Form1->SGr1->Cells[7][i];       break;
                case 14:QRLbl_HinA15->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA15->Caption = "○";
                        QRLbl_LotA15->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA15->Caption = Form1->SGr1->Cells[7][i];       break;
                case 15:QRLbl_HinA16->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA16->Caption = "○";
                        QRLbl_LotA16->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA16->Caption = Form1->SGr1->Cells[7][i];       break;
                case 16:QRLbl_HinA17->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA17->Caption = "○";
                        QRLbl_LotA17->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA17->Caption = Form1->SGr1->Cells[7][i];       break;
                case 17:QRLbl_HinA18->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA18->Caption = "○";
                        QRLbl_LotA18->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA18->Caption = Form1->SGr1->Cells[7][i];       break;
                case 18:QRLbl_HinA19->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA19->Caption = "○";
                        QRLbl_LotA19->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA19->Caption = Form1->SGr1->Cells[7][i];       break;
                case 19:QRLbl_HinA20->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA20->Caption = "○";
                        QRLbl_LotA20->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA20->Caption = Form1->SGr1->Cells[7][i];       break;
                case 20:QRLbl_HinA21->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA21->Caption = "○";
                        QRLbl_LotA21->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA21->Caption = Form1->SGr1->Cells[7][i];       break;
                case 21:QRLbl_HinA22->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA22->Caption = "○";
                        QRLbl_LotA22->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA22->Caption = Form1->SGr1->Cells[7][i];       break;
                case 22:QRLbl_HinA23->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA23->Caption = "○";
                        QRLbl_LotA23->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA23->Caption = Form1->SGr1->Cells[7][i];       break;
                case 23:QRLbl_HinA24->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA24->Caption = "○";
                        QRLbl_LotA24->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA24->Caption = Form1->SGr1->Cells[7][i];       break;
                case 24:QRLbl_HinA25->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA25->Caption = "○";
                        QRLbl_LotA25->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA25->Caption = Form1->SGr1->Cells[7][i];       break;
                case 25:QRLbl_HinA26->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA26->Caption = "○";
                        QRLbl_LotA26->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA26->Caption = Form1->SGr1->Cells[7][i];       break;
                case 26:QRLbl_HinA27->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA27->Caption = "○";
                        QRLbl_LotA27->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA27->Caption = Form1->SGr1->Cells[7][i];       break;
                case 27:QRLbl_HinA28->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA28->Caption = "○";
                        QRLbl_LotA28->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA28->Caption = Form1->SGr1->Cells[7][i];       break;
                case 28:QRLbl_HinA29->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA29->Caption = "○";
                        QRLbl_LotA29->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA29->Caption = Form1->SGr1->Cells[7][i];       break;
                case 29:QRLbl_HinA30->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisA30->Caption = "○";
                        QRLbl_LotA30->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisA30->Caption = Form1->SGr1->Cells[7][i];       break;
            }
        }
        else if( i >= (iStartRow+30) && i < (iStartRow+60) && LastTR >= x.quot ){
            // 右上部の印刷をします
            switch( x.rem ){
                case 0: QRLbl_TrB->Caption = x.quot + 1;
                        QRLbl_HinB01->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB01->Caption = "○";
                        QRLbl_LotB01->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB01->Caption = Form1->SGr1->Cells[7][i];       break;
                case 1: QRLbl_HinB02->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB02->Caption = "○";
                        QRLbl_LotB02->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB02->Caption = Form1->SGr1->Cells[7][i];       break;
                case 2: QRLbl_HinB03->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB03->Caption = "○";
                        QRLbl_LotB03->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB03->Caption = Form1->SGr1->Cells[7][i];       break;
                case 3: QRLbl_HinB04->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB04->Caption = "○";
                        QRLbl_LotB04->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB04->Caption = Form1->SGr1->Cells[7][i];       break;
                case 4: QRLbl_HinB05->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB05->Caption = "○";
                        QRLbl_LotB05->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB05->Caption = Form1->SGr1->Cells[7][i];       break;
                case 5: QRLbl_HinB06->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB06->Caption = "○";
                        QRLbl_LotB06->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB06->Caption = Form1->SGr1->Cells[7][i];       break;
                case 6: QRLbl_HinB07->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB07->Caption = "○";
                        QRLbl_LotB07->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB07->Caption = Form1->SGr1->Cells[7][i];       break;
                case 7: QRLbl_HinB08->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB08->Caption = "○";
                        QRLbl_LotB08->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB08->Caption = Form1->SGr1->Cells[7][i];       break;
                case 8: QRLbl_HinB09->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB09->Caption = "○";
                        QRLbl_LotB09->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB09->Caption = Form1->SGr1->Cells[7][i];       break;
                case 9: QRLbl_HinB10->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB10->Caption = "○";
                        QRLbl_LotB10->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB10->Caption = Form1->SGr1->Cells[7][i];       break;
                case 10:QRLbl_HinB11->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB11->Caption = "○";
                        QRLbl_LotB11->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB11->Caption = Form1->SGr1->Cells[7][i];       break;
                case 11:QRLbl_HinB12->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB12->Caption = "○";
                        QRLbl_LotB12->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB12->Caption = Form1->SGr1->Cells[7][i];       break;
                case 12:QRLbl_HinB13->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB13->Caption = "○";
                        QRLbl_LotB13->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB13->Caption = Form1->SGr1->Cells[7][i];       break;
                case 13:QRLbl_HinB14->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB14->Caption = "○";
                        QRLbl_LotB14->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB14->Caption = Form1->SGr1->Cells[7][i];       break;
                case 14:QRLbl_HinB15->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB15->Caption = "○";
                        QRLbl_LotB15->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB15->Caption = Form1->SGr1->Cells[7][i];       break;
                case 15:QRLbl_HinB16->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB16->Caption = "○";
                        QRLbl_LotB16->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB16->Caption = Form1->SGr1->Cells[7][i];       break;
                case 16:QRLbl_HinB17->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB17->Caption = "○";
                        QRLbl_LotB17->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB17->Caption = Form1->SGr1->Cells[7][i];       break;
                case 17:QRLbl_HinB18->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB18->Caption = "○";
                        QRLbl_LotB18->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB18->Caption = Form1->SGr1->Cells[7][i];       break;
                case 18:QRLbl_HinB19->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB19->Caption = "○";
                        QRLbl_LotB19->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB19->Caption = Form1->SGr1->Cells[7][i];       break;
                case 19:QRLbl_HinB20->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB20->Caption = "○";
                        QRLbl_LotB20->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB20->Caption = Form1->SGr1->Cells[7][i];       break;
                case 20:QRLbl_HinB21->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB21->Caption = "○";
                        QRLbl_LotB21->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB21->Caption = Form1->SGr1->Cells[7][i];       break;
                case 21:QRLbl_HinB22->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB22->Caption = "○";
                        QRLbl_LotB22->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB22->Caption = Form1->SGr1->Cells[7][i];       break;
                case 22:QRLbl_HinB23->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB23->Caption = "○";
                        QRLbl_LotB23->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB23->Caption = Form1->SGr1->Cells[7][i];       break;
                case 23:QRLbl_HinB24->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB24->Caption = "○";
                        QRLbl_LotB24->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB24->Caption = Form1->SGr1->Cells[7][i];       break;
                case 24:QRLbl_HinB25->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB25->Caption = "○";
                        QRLbl_LotB25->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB25->Caption = Form1->SGr1->Cells[7][i];       break;
                case 25:QRLbl_HinB26->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB26->Caption = "○";
                        QRLbl_LotB26->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB26->Caption = Form1->SGr1->Cells[7][i];       break;
                case 26:QRLbl_HinB27->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB27->Caption = "○";
                        QRLbl_LotB27->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB27->Caption = Form1->SGr1->Cells[7][i];       break;
                case 27:QRLbl_HinB28->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB28->Caption = "○";
                        QRLbl_LotB28->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB28->Caption = Form1->SGr1->Cells[7][i];       break;
                case 28:QRLbl_HinB29->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB29->Caption = "○";
                        QRLbl_LotB29->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB29->Caption = Form1->SGr1->Cells[7][i];       break;
                case 29:QRLbl_HinB30->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisB30->Caption = "○";
                        QRLbl_LotB30->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisB30->Caption = Form1->SGr1->Cells[7][i];       break;
            }
        }
        else if( i >= (iStartRow+60) && i < (iStartRow+90) && LastTR >= x.quot ){
            // 左下部の印刷をします
            switch( x.rem ){
                case 0: QRLbl_TrC->Caption = x.quot + 1;
                        QRLbl_HinC01->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC01->Caption = "○";
                        QRLbl_LotC01->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC01->Caption = Form1->SGr1->Cells[7][i];       break;
                case 1: QRLbl_HinC02->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC02->Caption = "○";
                        QRLbl_LotC02->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC02->Caption = Form1->SGr1->Cells[7][i];       break;
                case 2: QRLbl_HinC03->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC03->Caption = "○";
                        QRLbl_LotC03->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC03->Caption = Form1->SGr1->Cells[7][i];       break;
                case 3: QRLbl_HinC04->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC04->Caption = "○";
                        QRLbl_LotC04->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC04->Caption = Form1->SGr1->Cells[7][i];       break;
                case 4: QRLbl_HinC05->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC05->Caption = "○";
                        QRLbl_LotC05->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC05->Caption = Form1->SGr1->Cells[7][i];       break;
                case 5: QRLbl_HinC06->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC06->Caption = "○";
                        QRLbl_LotC06->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC06->Caption = Form1->SGr1->Cells[7][i];       break;
                case 6: QRLbl_HinC07->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC07->Caption = "○";
                        QRLbl_LotC07->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC07->Caption = Form1->SGr1->Cells[7][i];       break;
                case 7: QRLbl_HinC08->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC08->Caption = "○";
                        QRLbl_LotC08->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC08->Caption = Form1->SGr1->Cells[7][i];       break;
                case 8: QRLbl_HinC09->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC09->Caption = "○";
                        QRLbl_LotC09->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC09->Caption = Form1->SGr1->Cells[7][i];       break;
                case 9: QRLbl_HinC10->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC10->Caption = "○";
                        QRLbl_LotC10->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC10->Caption = Form1->SGr1->Cells[7][i];       break;
                case 10:QRLbl_HinC11->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC11->Caption = "○";
                        QRLbl_LotC11->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC11->Caption = Form1->SGr1->Cells[7][i];       break;
                case 11:QRLbl_HinC12->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC12->Caption = "○";
                        QRLbl_LotC12->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC12->Caption = Form1->SGr1->Cells[7][i];       break;
                case 12:QRLbl_HinC13->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC13->Caption = "○";
                        QRLbl_LotC13->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC13->Caption = Form1->SGr1->Cells[7][i];       break;
                case 13:QRLbl_HinC14->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC14->Caption = "○";
                        QRLbl_LotC14->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC14->Caption = Form1->SGr1->Cells[7][i];       break;
                case 14:QRLbl_HinC15->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC15->Caption = "○";
                        QRLbl_LotC15->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC15->Caption = Form1->SGr1->Cells[7][i];       break;
                case 15:QRLbl_HinC16->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC16->Caption = "○";
                        QRLbl_LotC16->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC16->Caption = Form1->SGr1->Cells[7][i];       break;
                case 16:QRLbl_HinC17->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC17->Caption = "○";
                        QRLbl_LotC17->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC17->Caption = Form1->SGr1->Cells[7][i];       break;
                case 17:QRLbl_HinC18->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC18->Caption = "○";
                        QRLbl_LotC18->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC18->Caption = Form1->SGr1->Cells[7][i];       break;
                case 18:QRLbl_HinC19->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC19->Caption = "○";
                        QRLbl_LotC19->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC19->Caption = Form1->SGr1->Cells[7][i];       break;
                case 19:QRLbl_HinC20->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC20->Caption = "○";
                        QRLbl_LotC20->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC20->Caption = Form1->SGr1->Cells[7][i];       break;
                case 20:QRLbl_HinC21->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC21->Caption = "○";
                        QRLbl_LotC21->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC21->Caption = Form1->SGr1->Cells[7][i];       break;
                case 21:QRLbl_HinC22->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC22->Caption = "○";
                        QRLbl_LotC22->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC22->Caption = Form1->SGr1->Cells[7][i];       break;
                case 22:QRLbl_HinC23->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC23->Caption = "○";
                        QRLbl_LotC23->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC23->Caption = Form1->SGr1->Cells[7][i];       break;
                case 23:QRLbl_HinC24->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC24->Caption = "○";
                        QRLbl_LotC24->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC24->Caption = Form1->SGr1->Cells[7][i];       break;
                case 24:QRLbl_HinC25->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC25->Caption = "○";
                        QRLbl_LotC25->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC25->Caption = Form1->SGr1->Cells[7][i];       break;
                case 25:QRLbl_HinC26->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC26->Caption = "○";
                        QRLbl_LotC26->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC26->Caption = Form1->SGr1->Cells[7][i];       break;
                case 26:QRLbl_HinC27->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC27->Caption = "○";
                        QRLbl_LotC27->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC27->Caption = Form1->SGr1->Cells[7][i];       break;
                case 27:QRLbl_HinC28->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC28->Caption = "○";
                        QRLbl_LotC28->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC28->Caption = Form1->SGr1->Cells[7][i];       break;
                case 28:QRLbl_HinC29->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC29->Caption = "○";
                        QRLbl_LotC29->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC29->Caption = Form1->SGr1->Cells[7][i];       break;
                case 29:QRLbl_HinC30->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisC30->Caption = "○";
                        QRLbl_LotC30->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisC30->Caption = Form1->SGr1->Cells[7][i];       break;
            }
        }
        else if( i >= (iStartRow+90) && i < (iStartRow+120) && LastTR >= x.quot ){
            // 右下部の印刷をします
            switch( x.rem ){
                case 0: QRLbl_TrD->Caption = x.quot + 1;
                        QRLbl_HinD01->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD01->Caption = "○";
                        QRLbl_LotD01->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD01->Caption = Form1->SGr1->Cells[7][i];       break;
                case 1: QRLbl_HinD02->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD02->Caption = "○";
                        QRLbl_LotD02->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD02->Caption = Form1->SGr1->Cells[7][i];       break;
                case 2: QRLbl_HinD03->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD03->Caption = "○";
                        QRLbl_LotD03->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD03->Caption = Form1->SGr1->Cells[7][i];       break;
                case 3: QRLbl_HinD04->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD04->Caption = "○";
                        QRLbl_LotD04->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD04->Caption = Form1->SGr1->Cells[7][i];       break;
                case 4: QRLbl_HinD05->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD05->Caption = "○";
                        QRLbl_LotD05->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD05->Caption = Form1->SGr1->Cells[7][i];       break;
                case 5: QRLbl_HinD06->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD06->Caption = "○";
                        QRLbl_LotD06->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD06->Caption = Form1->SGr1->Cells[7][i];       break;
                case 6: QRLbl_HinD07->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD07->Caption = "○";
                        QRLbl_LotD07->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD07->Caption = Form1->SGr1->Cells[7][i];       break;
                case 7: QRLbl_HinD08->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD08->Caption = "○";
                        QRLbl_LotD08->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD08->Caption = Form1->SGr1->Cells[7][i];       break;
                case 8: QRLbl_HinD09->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD09->Caption = "○";
                        QRLbl_LotD09->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD09->Caption = Form1->SGr1->Cells[7][i];       break;
                case 9: QRLbl_HinD10->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD10->Caption = "○";
                        QRLbl_LotD10->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD10->Caption = Form1->SGr1->Cells[7][i];       break;
                case 10:QRLbl_HinD11->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD11->Caption = "○";
                        QRLbl_LotD11->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD11->Caption = Form1->SGr1->Cells[7][i];       break;
                case 11:QRLbl_HinD12->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD12->Caption = "○";
                        QRLbl_LotD12->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD12->Caption = Form1->SGr1->Cells[7][i];       break;
                case 12:QRLbl_HinD13->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD13->Caption = "○";
                        QRLbl_LotD13->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD13->Caption = Form1->SGr1->Cells[7][i];       break;
                case 13:QRLbl_HinD14->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD14->Caption = "○";
                        QRLbl_LotD14->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD14->Caption = Form1->SGr1->Cells[7][i];       break;
                case 14:QRLbl_HinD15->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD15->Caption = "○";
                        QRLbl_LotD15->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD15->Caption = Form1->SGr1->Cells[7][i];       break;
                case 15:QRLbl_HinD16->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD16->Caption = "○";
                        QRLbl_LotD16->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD16->Caption = Form1->SGr1->Cells[7][i];       break;
                case 16:QRLbl_HinD17->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD17->Caption = "○";
                        QRLbl_LotD17->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD17->Caption = Form1->SGr1->Cells[7][i];       break;
                case 17:QRLbl_HinD18->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD18->Caption = "○";
                        QRLbl_LotD18->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD18->Caption = Form1->SGr1->Cells[7][i];       break;
                case 18:QRLbl_HinD19->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD19->Caption = "○";
                        QRLbl_LotD19->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD19->Caption = Form1->SGr1->Cells[7][i];       break;
                case 19:QRLbl_HinD20->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD20->Caption = "○";
                        QRLbl_LotD20->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD20->Caption = Form1->SGr1->Cells[7][i];       break;
                case 20:QRLbl_HinD21->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD21->Caption = "○";
                        QRLbl_LotD21->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD21->Caption = Form1->SGr1->Cells[7][i];       break;
                case 21:QRLbl_HinD22->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD22->Caption = "○";
                        QRLbl_LotD22->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD22->Caption = Form1->SGr1->Cells[7][i];       break;
                case 22:QRLbl_HinD23->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD23->Caption = "○";
                        QRLbl_LotD23->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD23->Caption = Form1->SGr1->Cells[7][i];       break;
                case 23:QRLbl_HinD24->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD24->Caption = "○";
                        QRLbl_LotD24->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD24->Caption = Form1->SGr1->Cells[7][i];       break;
                case 24:QRLbl_HinD25->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD25->Caption = "○";
                        QRLbl_LotD25->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD25->Caption = Form1->SGr1->Cells[7][i];       break;
                case 25:QRLbl_HinD26->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD26->Caption = "○";
                        QRLbl_LotD26->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD26->Caption = Form1->SGr1->Cells[7][i];       break;
                case 26:QRLbl_HinD27->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD27->Caption = "○";
                        QRLbl_LotD27->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD27->Caption = Form1->SGr1->Cells[7][i];       break;
                case 27:QRLbl_HinD28->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD28->Caption = "○";
                        QRLbl_LotD28->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD28->Caption = Form1->SGr1->Cells[7][i];       break;
                case 28:QRLbl_HinD29->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD29->Caption = "○";
                        QRLbl_LotD29->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD29->Caption = Form1->SGr1->Cells[7][i];       break;
                case 29:QRLbl_HinD30->Caption = Form1->SGr1->Cells[4][i];
                        if(StrToInt(sBuf)>0) QRLbl_HisD30->Caption = "○";
                        QRLbl_LotD30->Caption = Form1->SGr1->Cells[5][i];
                        QRLbl_ZisD30->Caption = Form1->SGr1->Cells[7][i];       break;
            }
        }
        else{
            // まだ続きが有るかどうかチェックします。
            for( k=i; k<Form1->SGr1->RowCount; k++ ){
                sBuf = Trim(Form1->SGr1->Cells[4][k]);
                if( sBuf.Length() > 0 ){
                    // 続き有り
                    bStop = false;
                    k = Form1->SGr1->RowCount;
                }
            }
            i = Form1->SGr1->RowCount;
            break;
        }
    }

    // トレーNOを４トレー進めます。
    if(!bStop)    iPrtPosTR += 4;

}


//---------------------------------------------------------------------------
void __fastcall TForm5::QRLbl_PagePrint(TObject *sender, AnsiString &Value)
{
    Value = IntToStr(QuickRep1->PageNumber);
}


//---------------------------------------------------------------------------
void __fastcall TForm5::PrtClear()
{
    QRLbl_TrA->Caption="";
    QRLbl_HinA01->Caption=""; QRLbl_HisA01->Caption=""; QRLbl_LotA01->Caption=""; QRLbl_ZisA01->Caption="";
    QRLbl_HinA02->Caption=""; QRLbl_HisA02->Caption=""; QRLbl_LotA02->Caption=""; QRLbl_ZisA02->Caption="";
    QRLbl_HinA03->Caption=""; QRLbl_HisA03->Caption=""; QRLbl_LotA03->Caption=""; QRLbl_ZisA03->Caption="";
    QRLbl_HinA04->Caption=""; QRLbl_HisA04->Caption=""; QRLbl_LotA04->Caption=""; QRLbl_ZisA04->Caption="";
    QRLbl_HinA05->Caption=""; QRLbl_HisA05->Caption=""; QRLbl_LotA05->Caption=""; QRLbl_ZisA05->Caption="";
    QRLbl_HinA06->Caption=""; QRLbl_HisA06->Caption=""; QRLbl_LotA06->Caption=""; QRLbl_ZisA06->Caption="";
    QRLbl_HinA07->Caption=""; QRLbl_HisA07->Caption=""; QRLbl_LotA07->Caption=""; QRLbl_ZisA07->Caption="";
    QRLbl_HinA08->Caption=""; QRLbl_HisA08->Caption=""; QRLbl_LotA08->Caption=""; QRLbl_ZisA08->Caption="";
    QRLbl_HinA09->Caption=""; QRLbl_HisA09->Caption=""; QRLbl_LotA09->Caption=""; QRLbl_ZisA09->Caption="";
    QRLbl_HinA10->Caption=""; QRLbl_HisA10->Caption=""; QRLbl_LotA10->Caption=""; QRLbl_ZisA10->Caption="";
    QRLbl_HinA11->Caption=""; QRLbl_HisA11->Caption=""; QRLbl_LotA11->Caption=""; QRLbl_ZisA11->Caption="";
    QRLbl_HinA12->Caption=""; QRLbl_HisA12->Caption=""; QRLbl_LotA12->Caption=""; QRLbl_ZisA12->Caption="";
    QRLbl_HinA13->Caption=""; QRLbl_HisA13->Caption=""; QRLbl_LotA13->Caption=""; QRLbl_ZisA13->Caption="";
    QRLbl_HinA14->Caption=""; QRLbl_HisA14->Caption=""; QRLbl_LotA14->Caption=""; QRLbl_ZisA14->Caption="";
    QRLbl_HinA15->Caption=""; QRLbl_HisA15->Caption=""; QRLbl_LotA15->Caption=""; QRLbl_ZisA15->Caption="";
    QRLbl_HinA16->Caption=""; QRLbl_HisA16->Caption=""; QRLbl_LotA16->Caption=""; QRLbl_ZisA16->Caption="";
    QRLbl_HinA17->Caption=""; QRLbl_HisA17->Caption=""; QRLbl_LotA17->Caption=""; QRLbl_ZisA17->Caption="";
    QRLbl_HinA18->Caption=""; QRLbl_HisA18->Caption=""; QRLbl_LotA18->Caption=""; QRLbl_ZisA18->Caption="";
    QRLbl_HinA19->Caption=""; QRLbl_HisA19->Caption=""; QRLbl_LotA19->Caption=""; QRLbl_ZisA19->Caption="";
    QRLbl_HinA20->Caption=""; QRLbl_HisA20->Caption=""; QRLbl_LotA20->Caption=""; QRLbl_ZisA20->Caption="";
    QRLbl_HinA21->Caption=""; QRLbl_HisA21->Caption=""; QRLbl_LotA21->Caption=""; QRLbl_ZisA21->Caption="";
    QRLbl_HinA22->Caption=""; QRLbl_HisA22->Caption=""; QRLbl_LotA22->Caption=""; QRLbl_ZisA22->Caption="";
    QRLbl_HinA23->Caption=""; QRLbl_HisA23->Caption=""; QRLbl_LotA23->Caption=""; QRLbl_ZisA23->Caption="";
    QRLbl_HinA24->Caption=""; QRLbl_HisA24->Caption=""; QRLbl_LotA24->Caption=""; QRLbl_ZisA24->Caption="";
    QRLbl_HinA25->Caption=""; QRLbl_HisA25->Caption=""; QRLbl_LotA25->Caption=""; QRLbl_ZisA25->Caption="";
    QRLbl_HinA26->Caption=""; QRLbl_HisA26->Caption=""; QRLbl_LotA26->Caption=""; QRLbl_ZisA26->Caption="";
    QRLbl_HinA27->Caption=""; QRLbl_HisA27->Caption=""; QRLbl_LotA27->Caption=""; QRLbl_ZisA27->Caption="";
    QRLbl_HinA28->Caption=""; QRLbl_HisA28->Caption=""; QRLbl_LotA28->Caption=""; QRLbl_ZisA28->Caption="";
    QRLbl_HinA29->Caption=""; QRLbl_HisA29->Caption=""; QRLbl_LotA29->Caption=""; QRLbl_ZisA29->Caption="";
    QRLbl_HinA30->Caption=""; QRLbl_HisA30->Caption=""; QRLbl_LotA30->Caption=""; QRLbl_ZisA30->Caption="";

    QRLbl_TrB->Caption="";
    QRLbl_HinB01->Caption=""; QRLbl_HisB01->Caption=""; QRLbl_LotB01->Caption=""; QRLbl_ZisB01->Caption="";
    QRLbl_HinB02->Caption=""; QRLbl_HisB02->Caption=""; QRLbl_LotB02->Caption=""; QRLbl_ZisB02->Caption="";
    QRLbl_HinB03->Caption=""; QRLbl_HisB03->Caption=""; QRLbl_LotB03->Caption=""; QRLbl_ZisB03->Caption="";
    QRLbl_HinB04->Caption=""; QRLbl_HisB04->Caption=""; QRLbl_LotB04->Caption=""; QRLbl_ZisB04->Caption="";
    QRLbl_HinB05->Caption=""; QRLbl_HisB05->Caption=""; QRLbl_LotB05->Caption=""; QRLbl_ZisB05->Caption="";
    QRLbl_HinB06->Caption=""; QRLbl_HisB06->Caption=""; QRLbl_LotB06->Caption=""; QRLbl_ZisB06->Caption="";
    QRLbl_HinB07->Caption=""; QRLbl_HisB07->Caption=""; QRLbl_LotB07->Caption=""; QRLbl_ZisB07->Caption="";
    QRLbl_HinB08->Caption=""; QRLbl_HisB08->Caption=""; QRLbl_LotB08->Caption=""; QRLbl_ZisB08->Caption="";
    QRLbl_HinB09->Caption=""; QRLbl_HisB09->Caption=""; QRLbl_LotB09->Caption=""; QRLbl_ZisB09->Caption="";
    QRLbl_HinB10->Caption=""; QRLbl_HisB10->Caption=""; QRLbl_LotB10->Caption=""; QRLbl_ZisB10->Caption="";
    QRLbl_HinB11->Caption=""; QRLbl_HisB11->Caption=""; QRLbl_LotB11->Caption=""; QRLbl_ZisB11->Caption="";
    QRLbl_HinB12->Caption=""; QRLbl_HisB12->Caption=""; QRLbl_LotB12->Caption=""; QRLbl_ZisB12->Caption="";
    QRLbl_HinB13->Caption=""; QRLbl_HisB13->Caption=""; QRLbl_LotB13->Caption=""; QRLbl_ZisB13->Caption="";
    QRLbl_HinB14->Caption=""; QRLbl_HisB14->Caption=""; QRLbl_LotB14->Caption=""; QRLbl_ZisB14->Caption="";
    QRLbl_HinB15->Caption=""; QRLbl_HisB15->Caption=""; QRLbl_LotB15->Caption=""; QRLbl_ZisB15->Caption="";
    QRLbl_HinB16->Caption=""; QRLbl_HisB16->Caption=""; QRLbl_LotB16->Caption=""; QRLbl_ZisB16->Caption="";
    QRLbl_HinB17->Caption=""; QRLbl_HisB17->Caption=""; QRLbl_LotB17->Caption=""; QRLbl_ZisB17->Caption="";
    QRLbl_HinB18->Caption=""; QRLbl_HisB18->Caption=""; QRLbl_LotB18->Caption=""; QRLbl_ZisB18->Caption="";
    QRLbl_HinB19->Caption=""; QRLbl_HisB19->Caption=""; QRLbl_LotB19->Caption=""; QRLbl_ZisB19->Caption="";
    QRLbl_HinB20->Caption=""; QRLbl_HisB20->Caption=""; QRLbl_LotB20->Caption=""; QRLbl_ZisB20->Caption="";
    QRLbl_HinB21->Caption=""; QRLbl_HisB21->Caption=""; QRLbl_LotB21->Caption=""; QRLbl_ZisB21->Caption="";
    QRLbl_HinB22->Caption=""; QRLbl_HisB22->Caption=""; QRLbl_LotB22->Caption=""; QRLbl_ZisB22->Caption="";
    QRLbl_HinB23->Caption=""; QRLbl_HisB23->Caption=""; QRLbl_LotB23->Caption=""; QRLbl_ZisB23->Caption="";
    QRLbl_HinB24->Caption=""; QRLbl_HisB24->Caption=""; QRLbl_LotB24->Caption=""; QRLbl_ZisB24->Caption="";
    QRLbl_HinB25->Caption=""; QRLbl_HisB25->Caption=""; QRLbl_LotB25->Caption=""; QRLbl_ZisB25->Caption="";
    QRLbl_HinB26->Caption=""; QRLbl_HisB26->Caption=""; QRLbl_LotB26->Caption=""; QRLbl_ZisB26->Caption="";
    QRLbl_HinB27->Caption=""; QRLbl_HisB27->Caption=""; QRLbl_LotB27->Caption=""; QRLbl_ZisB27->Caption="";
    QRLbl_HinB28->Caption=""; QRLbl_HisB28->Caption=""; QRLbl_LotB28->Caption=""; QRLbl_ZisB28->Caption="";
    QRLbl_HinB29->Caption=""; QRLbl_HisB29->Caption=""; QRLbl_LotB29->Caption=""; QRLbl_ZisB29->Caption="";
    QRLbl_HinB30->Caption=""; QRLbl_HisB30->Caption=""; QRLbl_LotB30->Caption=""; QRLbl_ZisB30->Caption="";

    QRLbl_TrC->Caption="";
    QRLbl_HinC01->Caption=""; QRLbl_HisC01->Caption=""; QRLbl_LotC01->Caption=""; QRLbl_ZisC01->Caption="";
    QRLbl_HinC02->Caption=""; QRLbl_HisC02->Caption=""; QRLbl_LotC02->Caption=""; QRLbl_ZisC02->Caption="";
    QRLbl_HinC03->Caption=""; QRLbl_HisC03->Caption=""; QRLbl_LotC03->Caption=""; QRLbl_ZisC03->Caption="";
    QRLbl_HinC04->Caption=""; QRLbl_HisC04->Caption=""; QRLbl_LotC04->Caption=""; QRLbl_ZisC04->Caption="";
    QRLbl_HinC05->Caption=""; QRLbl_HisC05->Caption=""; QRLbl_LotC05->Caption=""; QRLbl_ZisC05->Caption="";
    QRLbl_HinC06->Caption=""; QRLbl_HisC06->Caption=""; QRLbl_LotC06->Caption=""; QRLbl_ZisC06->Caption="";
    QRLbl_HinC07->Caption=""; QRLbl_HisC07->Caption=""; QRLbl_LotC07->Caption=""; QRLbl_ZisC07->Caption="";
    QRLbl_HinC08->Caption=""; QRLbl_HisC08->Caption=""; QRLbl_LotC08->Caption=""; QRLbl_ZisC08->Caption="";
    QRLbl_HinC09->Caption=""; QRLbl_HisC09->Caption=""; QRLbl_LotC09->Caption=""; QRLbl_ZisC09->Caption="";
    QRLbl_HinC10->Caption=""; QRLbl_HisC10->Caption=""; QRLbl_LotC10->Caption=""; QRLbl_ZisC10->Caption="";
    QRLbl_HinC11->Caption=""; QRLbl_HisC11->Caption=""; QRLbl_LotC11->Caption=""; QRLbl_ZisC11->Caption="";
    QRLbl_HinC12->Caption=""; QRLbl_HisC12->Caption=""; QRLbl_LotC12->Caption=""; QRLbl_ZisC12->Caption="";
    QRLbl_HinC13->Caption=""; QRLbl_HisC13->Caption=""; QRLbl_LotC13->Caption=""; QRLbl_ZisC13->Caption="";
    QRLbl_HinC14->Caption=""; QRLbl_HisC14->Caption=""; QRLbl_LotC14->Caption=""; QRLbl_ZisC14->Caption="";
    QRLbl_HinC15->Caption=""; QRLbl_HisC15->Caption=""; QRLbl_LotC15->Caption=""; QRLbl_ZisC15->Caption="";
    QRLbl_HinC16->Caption=""; QRLbl_HisC16->Caption=""; QRLbl_LotC16->Caption=""; QRLbl_ZisC16->Caption="";
    QRLbl_HinC17->Caption=""; QRLbl_HisC17->Caption=""; QRLbl_LotC17->Caption=""; QRLbl_ZisC17->Caption="";
    QRLbl_HinC18->Caption=""; QRLbl_HisC18->Caption=""; QRLbl_LotC18->Caption=""; QRLbl_ZisC18->Caption="";
    QRLbl_HinC19->Caption=""; QRLbl_HisC19->Caption=""; QRLbl_LotC19->Caption=""; QRLbl_ZisC19->Caption="";
    QRLbl_HinC20->Caption=""; QRLbl_HisC20->Caption=""; QRLbl_LotC20->Caption=""; QRLbl_ZisC20->Caption="";
    QRLbl_HinC21->Caption=""; QRLbl_HisC21->Caption=""; QRLbl_LotC21->Caption=""; QRLbl_ZisC21->Caption="";
    QRLbl_HinC22->Caption=""; QRLbl_HisC22->Caption=""; QRLbl_LotC22->Caption=""; QRLbl_ZisC22->Caption="";
    QRLbl_HinC23->Caption=""; QRLbl_HisC23->Caption=""; QRLbl_LotC23->Caption=""; QRLbl_ZisC23->Caption="";
    QRLbl_HinC24->Caption=""; QRLbl_HisC24->Caption=""; QRLbl_LotC24->Caption=""; QRLbl_ZisC24->Caption="";
    QRLbl_HinC25->Caption=""; QRLbl_HisC25->Caption=""; QRLbl_LotC25->Caption=""; QRLbl_ZisC25->Caption="";
    QRLbl_HinC26->Caption=""; QRLbl_HisC26->Caption=""; QRLbl_LotC26->Caption=""; QRLbl_ZisC26->Caption="";
    QRLbl_HinC27->Caption=""; QRLbl_HisC27->Caption=""; QRLbl_LotC27->Caption=""; QRLbl_ZisC27->Caption="";
    QRLbl_HinC28->Caption=""; QRLbl_HisC28->Caption=""; QRLbl_LotC28->Caption=""; QRLbl_ZisC28->Caption="";
    QRLbl_HinC29->Caption=""; QRLbl_HisC29->Caption=""; QRLbl_LotC29->Caption=""; QRLbl_ZisC29->Caption="";
    QRLbl_HinC30->Caption=""; QRLbl_HisC30->Caption=""; QRLbl_LotC30->Caption=""; QRLbl_ZisC30->Caption="";

    QRLbl_TrD->Caption="";
    QRLbl_HinD01->Caption=""; QRLbl_HisD01->Caption=""; QRLbl_LotD01->Caption=""; QRLbl_ZisD01->Caption="";
    QRLbl_HinD02->Caption=""; QRLbl_HisD02->Caption=""; QRLbl_LotD02->Caption=""; QRLbl_ZisD02->Caption="";
    QRLbl_HinD03->Caption=""; QRLbl_HisD03->Caption=""; QRLbl_LotD03->Caption=""; QRLbl_ZisD03->Caption="";
    QRLbl_HinD04->Caption=""; QRLbl_HisD04->Caption=""; QRLbl_LotD04->Caption=""; QRLbl_ZisD04->Caption="";
    QRLbl_HinD05->Caption=""; QRLbl_HisD05->Caption=""; QRLbl_LotD05->Caption=""; QRLbl_ZisD05->Caption="";
    QRLbl_HinD06->Caption=""; QRLbl_HisD06->Caption=""; QRLbl_LotD06->Caption=""; QRLbl_ZisD06->Caption="";
    QRLbl_HinD07->Caption=""; QRLbl_HisD07->Caption=""; QRLbl_LotD07->Caption=""; QRLbl_ZisD07->Caption="";
    QRLbl_HinD08->Caption=""; QRLbl_HisD08->Caption=""; QRLbl_LotD08->Caption=""; QRLbl_ZisD08->Caption="";
    QRLbl_HinD09->Caption=""; QRLbl_HisD09->Caption=""; QRLbl_LotD09->Caption=""; QRLbl_ZisD09->Caption="";
    QRLbl_HinD10->Caption=""; QRLbl_HisD10->Caption=""; QRLbl_LotD10->Caption=""; QRLbl_ZisD10->Caption="";
    QRLbl_HinD11->Caption=""; QRLbl_HisD11->Caption=""; QRLbl_LotD11->Caption=""; QRLbl_ZisD11->Caption="";
    QRLbl_HinD12->Caption=""; QRLbl_HisD12->Caption=""; QRLbl_LotD12->Caption=""; QRLbl_ZisD12->Caption="";
    QRLbl_HinD13->Caption=""; QRLbl_HisD13->Caption=""; QRLbl_LotD13->Caption=""; QRLbl_ZisD13->Caption="";
    QRLbl_HinD14->Caption=""; QRLbl_HisD14->Caption=""; QRLbl_LotD14->Caption=""; QRLbl_ZisD14->Caption="";
    QRLbl_HinD15->Caption=""; QRLbl_HisD15->Caption=""; QRLbl_LotD15->Caption=""; QRLbl_ZisD15->Caption="";
    QRLbl_HinD16->Caption=""; QRLbl_HisD16->Caption=""; QRLbl_LotD16->Caption=""; QRLbl_ZisD16->Caption="";
    QRLbl_HinD17->Caption=""; QRLbl_HisD17->Caption=""; QRLbl_LotD17->Caption=""; QRLbl_ZisD17->Caption="";
    QRLbl_HinD18->Caption=""; QRLbl_HisD18->Caption=""; QRLbl_LotD18->Caption=""; QRLbl_ZisD18->Caption="";
    QRLbl_HinD19->Caption=""; QRLbl_HisD19->Caption=""; QRLbl_LotD19->Caption=""; QRLbl_ZisD19->Caption="";
    QRLbl_HinD20->Caption=""; QRLbl_HisD20->Caption=""; QRLbl_LotD20->Caption=""; QRLbl_ZisD20->Caption="";
    QRLbl_HinD21->Caption=""; QRLbl_HisD21->Caption=""; QRLbl_LotD21->Caption=""; QRLbl_ZisD21->Caption="";
    QRLbl_HinD22->Caption=""; QRLbl_HisD22->Caption=""; QRLbl_LotD22->Caption=""; QRLbl_ZisD22->Caption="";
    QRLbl_HinD23->Caption=""; QRLbl_HisD23->Caption=""; QRLbl_LotD23->Caption=""; QRLbl_ZisD23->Caption="";
    QRLbl_HinD24->Caption=""; QRLbl_HisD24->Caption=""; QRLbl_LotD24->Caption=""; QRLbl_ZisD24->Caption="";
    QRLbl_HinD25->Caption=""; QRLbl_HisD25->Caption=""; QRLbl_LotD25->Caption=""; QRLbl_ZisD25->Caption="";
    QRLbl_HinD26->Caption=""; QRLbl_HisD26->Caption=""; QRLbl_LotD26->Caption=""; QRLbl_ZisD26->Caption="";
    QRLbl_HinD27->Caption=""; QRLbl_HisD27->Caption=""; QRLbl_LotD27->Caption=""; QRLbl_ZisD27->Caption="";
    QRLbl_HinD28->Caption=""; QRLbl_HisD28->Caption=""; QRLbl_LotD28->Caption=""; QRLbl_ZisD28->Caption="";
    QRLbl_HinD29->Caption=""; QRLbl_HisD29->Caption=""; QRLbl_LotD29->Caption=""; QRLbl_ZisD29->Caption="";
    QRLbl_HinD30->Caption=""; QRLbl_HisD30->Caption=""; QRLbl_LotD30->Caption=""; QRLbl_ZisD30->Caption="";
}






