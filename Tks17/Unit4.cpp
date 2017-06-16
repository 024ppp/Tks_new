//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm4 *Form4;

//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
   int DataNoIdx_Old;

     //プローブの設定
     if( EdtS->Value == 0.0 ) return ;

     Form1->PnlSpan1->Caption = EdtS->Text ;
     Form1->PnlSpan2->Caption = EdtS->Text ;

     if( KD71Data[SamplePositionIdx-1].SOKUTEI_NM  > 2 )
         Form1->PnlSpan3->Caption = EdtS->Text ;

     //プローブの保存
     if( KD71Data[SamplePositionIdx-1].SOKUTEI_NP_CUR < KD71Data[SamplePositionIdx-1].SOKUTEI_NM)
         KD71Data[SamplePositionIdx-1].SOKUTEI_NP_CUR = KD71Data[SamplePositionIdx-1].SOKUTEI_NM ;

     for( int i=0; i< KD71Data[SamplePositionIdx-1].SOKUTEI_NM; i++ ){
           KD71Data[SamplePositionIdx-1].SOKUTEI_P[i] = EdtS->Value ;

           //固有抵抗率の計算
          if( KTeikouCal(SamplePositionIdx, i+1 ) ){

              //元ﾃﾞｰﾀNOの保存
              DataNoIdx_Old = DataNoIdx ;


               if( i == 0)
                    pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0.0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[i] );
               else if( i == 1)
                    pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0.0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[i] );
               else
                    pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.0",KD71Data[SamplePositionIdx-1].SOKUTEI_T[i] );

               DataNoIdx = i+1 ;

               ///規格ﾁｪｯｸ
               CheckInKikaku(0) ;
               ToDrawGraph(SamplePositionIdx, iOption);

               //元ﾃﾞｰﾀNOへ戻る
               DataNoIdx = DataNoIdx_Old ;
           }
     }

      Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormActivate(TObject *Sender)
{
     Pnl1->Caption = FormatFloat( "#0", KD71Data[SamplePositionIdx-1].KOYU_PRO );
     EdtS->Text    = FormatFloat( "#0", KD71Data[SamplePositionIdx-1].SOKUTEI_P[0] );
     EdtS->SetFocus();
     EdtS->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::EdtSKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_RETURN:
              Button1Click(Sender);
              break;
    }
}
//---------------------------------------------------------------------------

