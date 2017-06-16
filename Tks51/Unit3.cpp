//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
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
// 得意先コード
void __fastcall TForm3::QRLbl1Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[1][iPrtRow];
}

//---------------------------------------------------------------------------
// 得意先品番
void __fastcall TForm3::QRLbl2Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[2][iPrtRow];
}

//---------------------------------------------------------------------------
// 自社品番
void __fastcall TForm3::QRLbl3Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[3][iPrtRow];
}


//---------------------------------------------------------------------------
// 材質コード
void __fastcall TForm3::QRLbl4Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[4][iPrtRow];
}

//---------------------------------------------------------------------------
// 材質名称
void __fastcall TForm3::QRLbl5Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[5][iPrtRow];
}

//---------------------------------------------------------------------------
// 焼成コード
void __fastcall TForm3::QRLbl6Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[6][iPrtRow];
}

//---------------------------------------------------------------------------
// ソートキー
void __fastcall TForm3::QRLbl7Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[7][iPrtRow];
}

//---------------------------------------------------------------------------
// 形状区分
void __fastcall TForm3::QRLbl8Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[8][iPrtRow];
}

//---------------------------------------------------------------------------
// ヒストグラムＮ
void __fastcall TForm3::QRLbl9Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[23][iPrtRow];
}

//---------------------------------------------------------------------------
// ヒストグラムＭｉｎ／Ｍａｘ
void __fastcall TForm3::QRLbl10Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    double dumy;
    dumy = StrToFloat(Form1->SGr1->Cells[25][iPrtRow]);
    Value = FormatFloat("0.000", dumy);

    dumy = StrToFloat(Form1->SGr1->Cells[26][iPrtRow]);
    Value = Value + "～" + FormatFloat("0.000", dumy);
}

//---------------------------------------------------------------------------
// 登録日
void __fastcall TForm3::QRLbl12Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[59][iPrtRow];
    if( Value.Trim() != "" ){
        Value = Value.Insert("/",5);
        Value = Value.Insert("/",8);
    }
}

//---------------------------------------------------------------------------
// 更新日
void __fastcall TForm3::QRLbl13Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    Value = Form1->SGr1->Cells[60][iPrtRow];
    if( Value.Trim() != "" ){
        Value = Value.Insert("/",5);
        Value = Value.Insert("/",8);
    }
}

//---------------------------------------------------------------------------
// 線長さ（下限／上限）
void __fastcall TForm3::QRLbl15Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    //if(StrToInt(Form1->SGr1->Cells[10][iPrtRow])>=2){
    if(StrToInt(Form1->SGr1->Cells[64][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[27][iPrtRow]);
        sBuf1 = FormatFloat("0.00", dumy);
        if( (5 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 5 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[28][iPrtRow]);
        sBuf2 = FormatFloat("0.00", dumy);
        if( (5 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 5 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "     -";
    }
}

//---------------------------------------------------------------------------
// ブラシ幅（下限／上限）
void __fastcall TForm3::QRLbl17Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[11][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[29][iPrtRow]);
        sBuf1 = FormatFloat("0.000", dumy);
        if( (6 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[30][iPrtRow]);
        sBuf2 = FormatFloat("0.000", dumy);
        if( (6 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "     -";
    }
}

//---------------------------------------------------------------------------
// ブラシ幅縦（下限／上限）
void __fastcall TForm3::QRLbl19Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[12][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[31][iPrtRow]);
        sBuf1 = FormatFloat("0.000", dumy);
        if( (6 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[32][iPrtRow]);
        sBuf2 = FormatFloat("0.000", dumy);
        if( (6 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "     -";
    }
}

//---------------------------------------------------------------------------
// リード線取付
void __fastcall TForm3::QRLbl21Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[13][iPrtRow])>=2){
        double dumy1;
        double dumy2;
        dumy1 = StrToFloat(Form1->SGr1->Cells[33][iPrtRow]);
        dumy2 = StrToFloat(Form1->SGr1->Cells[34][iPrtRow]);
        if( dumy2 != 0 )    dumy1 = dumy1 / dumy2;
        else                dumy1 = 0.0;
        Value = FormatFloat("0.0", dumy1);
    }
    else{
        Value = "-  ";
    }
}

//---------------------------------------------------------------------------
// リード線取付（Ａ）
void __fastcall TForm3::QRLbl22Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[13][iPrtRow])>=2){
        Value = Form1->SGr1->Cells[34][iPrtRow];
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// リード線取付（タイム）
void __fastcall TForm3::QRLbl23Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[13][iPrtRow])>=2){
        Value = Form1->SGr1->Cells[35][iPrtRow];
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// リード線引張
void __fastcall TForm3::QRLbl24Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[14][iPrtRow])>=2){
        double dumy;
        dumy = StrToFloat(Form1->SGr1->Cells[36][iPrtRow]);
        Value = FormatFloat("0.0", dumy);
    }
    else{
        Value = "-  ";
    }
}

//---------------------------------------------------------------------------
// リード線引張（単位）
void __fastcall TForm3::QRLbl25Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[14][iPrtRow])>=2){
        int  dumy;
        if( Form1->SGr1->Cells[37][iPrtRow] < "1" || Form1->SGr1->Cells[37][iPrtRow] > "3" ){
            dumy = 2;
        }
        else{
            dumy = StrToInt(Form1->SGr1->Cells[37][iPrtRow]);
        }
        switch( dumy ){
            case 1: Value = "Kgf";    break;     // Kgf
            case 2: Value = "N"  ;    break;     // N
            case 3: Value = "MPa";    break;     // MPa
        }
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// リード線引張（Speed）
void __fastcall TForm3::QRLbl26Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[14][iPrtRow])>=2){
        Value = Form1->SGr1->Cells[38][iPrtRow];
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// 母体比重（下限／上限）
void __fastcall TForm3::QRLbl27Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[15][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[39][iPrtRow]);
        sBuf1 = FormatFloat("0.00", dumy);
        if( (6 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 6 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[40][iPrtRow]);
        sBuf2 = FormatFloat("0.00", dumy);
        if( (6 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 6 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "     -";
    }
}

//---------------------------------------------------------------------------
// 固有抵抗（下限／上限）
void __fastcall TForm3::QRLbl29Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[16][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[41][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[42][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "-    ";
    }
}

//---------------------------------------------------------------------------
// 固有抵抗（Ａ）
void __fastcall TForm3::QRLbl31Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[16][iPrtRow])>=2){
        double dumy;
        dumy = StrToFloat(Form1->SGr1->Cells[43][iPrtRow]);
        Value = FormatFloat("0.0", dumy);
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// 固有抵抗（ﾌﾟﾛｰﾌﾞ）
void __fastcall TForm3::QRLbl32Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[16][iPrtRow])>=2){
        Value = Form1->SGr1->Cells[44][iPrtRow];
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// 抗折力（下限）
void __fastcall TForm3::QRLbl33Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[17][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[45][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[46][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "-    ";
    }
}

//---------------------------------------------------------------------------
// 抗折力（単位）
void __fastcall TForm3::QRLbl35Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[17][iPrtRow])>=2){
        int  dumy;
        if( Form1->SGr1->Cells[47][iPrtRow] < "1" || Form1->SGr1->Cells[47][iPrtRow] > "3" ){
            dumy = 3;
        }
        else{
            dumy = StrToInt(Form1->SGr1->Cells[47][iPrtRow]);
        }
        switch( dumy ){
            case 1: Value = "Kgf";    break;     // Kgf
            case 2: Value = "N"  ;    break;     // N
            case 3: Value = "MPa";    break;     // MPa
        }
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// 抗折力（スパン）
void __fastcall TForm3::QRLbl36Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[17][iPrtRow])>=2){
        double dumy;
        dumy = StrToFloat(Form1->SGr1->Cells[48][iPrtRow]);
        Value = FormatFloat("0.0", dumy);
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
// 座屈（下限／上限）
void __fastcall TForm3::QRLbl37Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[22][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[57][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[58][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;

        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "    -";
    }
}

//---------------------------------------------------------------------------
// 硬度ＨｓＣ圧面（下限／上限）
void __fastcall TForm3::QRLbl39Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[18][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[49][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (2 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 2 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[50][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (2 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 2 - sBuf2.Length() ) + sBuf2;

        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "  -";
    }
}

//---------------------------------------------------------------------------
// 硬度ＨｓＣ側面（下限／上限）
void __fastcall TForm3::QRLbl41Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[19][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[51][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (2 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 2 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[52][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (2 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 2 - sBuf2.Length() ) + sBuf2;

        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "  -";
    }
}

//---------------------------------------------------------------------------
// 硬度ＨｓＤ圧面（下限／上限）
void __fastcall TForm3::QRLbl43Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[20][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[53][iPrtRow]);
        sBuf1 = FormatFloat("0.0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[54][iPrtRow]);
        sBuf2 = FormatFloat("0.0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;

        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "   -";
    }
}

//---------------------------------------------------------------------------
// 硬度ＨｓＤ側面（下限／上限）
void __fastcall TForm3::QRLbl45Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[21][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[55][iPrtRow]);
        sBuf1 = FormatFloat("0.0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[56][iPrtRow]);
        sBuf2 = FormatFloat("0.0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;

        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "   -";
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm3::QRBand3AfterPrint(TQRCustomBand *Sender,
      bool BandPrinted)
{
    iPrtRow += 1;
    //2002/12/05 E.Takase
    iPrtRow = GetiPrtRow(iPrtRow);
}

//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1BeforePrint(TCustomQuickRep *Sender,
      bool &PrintReport)
{
    iPrtRow = 0;
    //2002/12/05 E.Takase
    iPrtRow = GetiPrtRow(iPrtRow);

    QRLabel26->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TForm3::QRLabel9Print(TObject *sender, AnsiString &Value)
{
    Value = IntToStr(QuickRep1->PageNumber);
}

//---------------------------------------------------------------------------
void __fastcall TForm3::QuickRep1NeedData(TObject *Sender, bool &MoreData)
{
    MoreData = iPrtRow < (Form1->SGr1->RowCount - 1);
    if( !MoreData ){
        QRLabel26->Enabled = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm3::QRBand1BeforePrint(TQRCustomBand *Sender,
      bool &PrintBand)
{
    if(QuickRep1->PageNumber == 1)  QRLabel1->Enabled = true;
    else                            QRLabel1->Enabled = false;
}

//---------------------------------------------------------------------------
// 現物曲げ強さ（下限）
void __fastcall TForm3::QRLbl52Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[69][iPrtRow])>=2){
        double dumy;
        sBuf1 = "";
        sBuf2 = "";
        dumy = StrToFloat(Form1->SGr1->Cells[70][iPrtRow]);
        sBuf1 = FormatFloat("0", dumy);
        if( (4 - sBuf1.Length()) > 0 )
           sBuf1 = AnsiString::StringOfChar(' ', 4 - sBuf1.Length() ) + sBuf1;

        dumy = StrToFloat(Form1->SGr1->Cells[71][iPrtRow]);
        sBuf2 = FormatFloat("0", dumy);
        if( (4 - sBuf2.Length()) > 0 )
           sBuf2 = AnsiString::StringOfChar(' ', 4 - sBuf2.Length() ) + sBuf2;
        Value = sBuf1 + "～" + sBuf2;
    }
    else{
        Value = "-    ";
    }
}

//---------------------------------------------------------------------------
//  現物曲げ強さ（単位）
void __fastcall TForm3::QRLbl50Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[69][iPrtRow])>=2){
        int  dumy;
        if( Form1->SGr1->Cells[72][iPrtRow] < "1" || Form1->SGr1->Cells[72][iPrtRow] > "3" ){
            dumy = 3;
        }
        else{
            dumy = StrToInt(Form1->SGr1->Cells[72][iPrtRow]);
        }
        switch( dumy ){
            case 1: Value = "Kgf";    break;     // Kgf
            case 2: Value = "N"  ;    break;     // N
            case 3: Value = "MPa";    break;     // MPa
        }
    }
    else{
        Value = "";
    }
}

//---------------------------------------------------------------------------
//  現物曲げ強さ（スパン）
void __fastcall TForm3::QRLbl51Print(TObject *sender, AnsiString &Value)
{
    Value = "";
    if(StrToInt(Form1->SGr1->Cells[69][iPrtRow])>=2){
        double dumy;
        dumy = StrToFloat(Form1->SGr1->Cells[73][iPrtRow]);
        Value = FormatFloat("0.0", dumy);
    }
    else{
        Value = "";
    }
}
//---------------------------------------------------------------------------
// iPrtRowの位置のデータが履歴データの場合は次のデータにする
int __fastcall TForm3::GetiPrtRow(int n)
{
    int i;

    if ( Form1->SGr1->Cells[10][n] == "0" ) {
        return(n) ;
    } else {
        for ( i = n+1; i < (Form1->SGr1->RowCount); i++ ) {
            if ( Form1->SGr1->Cells[10][i] == "0" ) {
                return(i) ;
            }
        }

    }
    return(Form1->SGr1->RowCount) ;
}
