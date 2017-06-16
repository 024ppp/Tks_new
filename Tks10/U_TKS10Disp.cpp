

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)



//---------------------------------------------------------------------------
void DisplayInfo()
{
     pEdt1[SamplePositionIdx-1]->SetFocus();

    // Pnl3->Caption = KD11Data[SamplePositionIdx-1].UPDCHR ;
     Form1->Pnl5->Caption = FormatFloat("#0.00", KD11Data[SamplePositionIdx-1].LD_LNG_MIN) ;
     Form1->Pnl6->Caption = FormatFloat("#0.00", KD11Data[SamplePositionIdx-1].LD_LNG_MAX) ;
     Form1->Pnl7->Caption = KD11Data[SamplePositionIdx-1].DTKSCOD ;
     Form1->Pnl8->Caption = KD11Data[SamplePositionIdx-1].DTKSHIN ;
     Form1->Pnl9->Caption = KD11Data[SamplePositionIdx-1].LOTNO ;
     Form1->Pnl10->Caption = KD11Data[SamplePositionIdx-1].HINBAN ;
     Form1->Pnl11->Caption = KD11Data[SamplePositionIdx-1].ZISCOD ;
     Form1->Pnl12->Caption = KD11Data[SamplePositionIdx-1].ZISNAM ;

     //çÏâÊ
     ToDrawGraph(SamplePositionIdx);
}

