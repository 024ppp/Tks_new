//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm5 *Form5;

extern KETA_DATA KETA;
//extern KDA1_DATA Cur_Kda1;             // 選択したヒストグラムデータ

//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//「ＯＫ」
void __fastcall TForm5::Button1Click(TObject *Sender)
{
    //印刷桁数
	KETA.AVE = StrToInt(NumberEdit1->Text);
	KETA.SGM = StrToInt(NumberEdit2->Text);
	KETA.CP  = StrToInt(NumberEdit3->Text);
	KETA.K   = StrToInt(NumberEdit4->Text);
	KETA.CPK = StrToInt(NumberEdit5->Text);
	KETA.P   = StrToInt(NumberEdit6->Text);


    Form5->ModalResult = mrOk;
//    Close();
}
//---------------------------------------------------------------------------
//「キャンセル」
void __fastcall TForm5::Button2Click(TObject *Sender)
{
    Form5->ModalResult = mrCancel;
//    Close();

}
//---------------------------------------------------------------------------
//フォームアクティブ時
void __fastcall TForm5::FormActivate(TObject *Sender)
{

	NumberEdit1->Text = IntToStr( KETA.AVE );
	NumberEdit2->Text = IntToStr( KETA.SGM );      
	NumberEdit3->Text = IntToStr( KETA.CP );       
	NumberEdit4->Text = IntToStr( KETA.K );        
	NumberEdit5->Text = IntToStr( KETA.CPK );      
	NumberEdit6->Text = IntToStr( KETA.P );

}
//---------------------------------------------------------------------------
void __fastcall TForm5::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     switch(Key)
     {

         // 前項
         case VK_UP:
         case VK_LEFT:
                if(NumberEdit1->Focused() && NumberEdit1->SelStart == 0 && NumberEdit1->SelLength == 0 ){
                    Button2->SetFocus();
                    break;
                }
                if(NumberEdit2->Focused() && NumberEdit2->SelStart == 0 && NumberEdit2->SelLength == 0 ){
                    NumberEdit1->SetFocus();
                    break;
                }
                if(NumberEdit3->Focused() && NumberEdit3->SelStart == 0 && NumberEdit3->SelLength == 0 ){
                    NumberEdit2->SetFocus();
                    break;
                }
                if(NumberEdit4->Focused() && NumberEdit4->SelStart == 0 && NumberEdit4->SelLength == 0 ){
                    NumberEdit3->SetFocus();
                    break;
                }
                if(NumberEdit5->Focused() && NumberEdit5->SelStart == 0 && NumberEdit5->SelLength == 0 ){
                    NumberEdit4->SetFocus();
                    break;
                }
                if(NumberEdit6->Focused() && NumberEdit6->SelStart == 0 && NumberEdit6->SelLength == 0 ){
                    NumberEdit5->SetFocus();
                    break;
                }
                if(Button1->Focused()){
                    NumberEdit6->SetFocus();
                    break;
                }
                if(Button2->Focused()){
                    Button1->SetFocus();
                    break;
                }

                break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT:
                if(NumberEdit1->Focused() && NumberEdit1->SelStart == NumberEdit1->Text.Length() && NumberEdit1->SelLength == 0 ){
                    NumberEdit2->SetFocus();
                    break;
                }
                if(NumberEdit2->Focused() && NumberEdit2->SelStart == NumberEdit2->Text.Length() && NumberEdit2->SelLength == 0 ){
                    NumberEdit3->SetFocus();
                    break;
                }
                if(NumberEdit3->Focused() && NumberEdit3->SelStart == NumberEdit3->Text.Length() && NumberEdit3->SelLength == 0 ){
                    NumberEdit4->SetFocus();
                    break;
                }
                if(NumberEdit4->Focused() && NumberEdit4->SelStart == NumberEdit4->Text.Length() && NumberEdit4->SelLength == 0 ){
                    NumberEdit5->SetFocus();
                    break;
                }
                if(NumberEdit5->Focused() && NumberEdit5->SelStart == NumberEdit5->Text.Length() && NumberEdit5->SelLength == 0 ){
                    NumberEdit6->SetFocus();
                    break;
                }
                if(NumberEdit6->Focused() && NumberEdit6->SelStart == NumberEdit6->Text.Length() && NumberEdit6->SelLength == 0 ){
                    Button1->SetFocus();
                    break;
                }
                if(Button1->Focused()){
                    Button2->SetFocus();
                    break;
                }
                if(Button2->Focused()){
                    NumberEdit1->SetFocus();
                    break;
                }
                break;



         // Enter
         case VK_RETURN:
                if(NumberEdit1->Focused()){
                    NumberEdit2->SetFocus();
                    break;
                }
                if(NumberEdit2->Focused()){
                    NumberEdit3->SetFocus();
                    break;
                }
                if(NumberEdit3->Focused()){
                    NumberEdit4->SetFocus();
                    break;
                }
                if(NumberEdit4->Focused()){
                    NumberEdit5->SetFocus();
                    break;
                }
                if(NumberEdit5->Focused()){
                    NumberEdit6->SetFocus();
                    break;
                }
                if(NumberEdit6->Focused()){
                    Button1->SetFocus();
                    break;
                }
                if(Button1->Focused()){
                    Button1Click(Sender);
                    break;
                }
                if(Button2->Focused()){
                    Button2Click(Sender);
                    break;
                }

                break;

     }

}
//---------------------------------------------------------------------------


