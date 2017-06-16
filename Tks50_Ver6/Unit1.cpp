//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"

TForm1 *Form1;

int iKojoKbn = 0;                   // 工場区分

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
     int i;
     div_t x;
     AnsiString sBuf;
     TDateTime  DtTOMR;

     Database1->Open();

     // 測定数パネルを初期化
     Panel3->Visible = false;
     Panel3->Left = Panel14->Left;
     Panel3->Top = Panel20->Top + 2;
     Panel3->Tag = Panel3->Width;
     Panel3->Width = 0;
     Panel3->Left = Panel3->Left + Panel3->Tag;

     Panel21->Visible = false;
     Panel21->Left = Edt05->Left;
     Panel21->Top = 623;
     Panel21->Tag = Panel21->Width;
     Panel21->Width = 0;
     Panel21->Left = Panel21->Left + Panel21->Tag;

     // グリッドの初期化
     SGr1->ColWidths[0] = Panel8->Width;     // ﾄﾚｰ
     SGr1->ColWidths[1] = Panel19->Width;    // SP
     SGr1->ColWidths[2] = Panel23->Width;    // 工管NO
     SGr1->ColWidths[3] = Panel12->Width;    // 得意先ｺｰﾄﾞ
     SGr1->ColWidths[4] = Panel13->Width;    // 得意先品番
     SGr1->ColWidths[5] = Panel22->Width;    // ロットNO
     SGr1->ColWidths[6] = Panel14->Width;    // 自社品番
     SGr1->ColWidths[7] = Panel15->Width;    // 材質名称
     SGr1->ColWidths[8] = Panel16->Width;    // 材質ｺｰﾄﾞ
     SGr1->ColWidths[9] = Panel17->Width;    // 数量
     SGr1->ColWidths[10] = 0;                // ｿｰﾄKey
     SGr1->ColWidths[11] = 0;                // ﾋｽﾄｸﾞﾗﾑ測定数
     SGr1->ColWidths[12] = 0;                // Dumy
     SGr1->ColWidths[13] = Panel4->Width;
     SGr1->ColWidths[14] = Panel6->Width;
     SGr1->ColWidths[15] = Panel7->Width;
     SGr1->ColWidths[16] = Panel11->Width;
     SGr1->ColWidths[17] = Panel18->Width;
     SGr1->ColWidths[18] = Panel24->Width;
     SGr1->ColWidths[19] = Panel25->Width;
     SGr1->ColWidths[20] = Panel26->Width;
     SGr1->ColWidths[21] = Panel27->Width;
     SGr1->ColWidths[22] = Panel28->Width;
     SGr1->ColWidths[23] = Panel29->Width;
     SGr1->ColWidths[24] = Panel30->Width;
     SGr1->ColWidths[25] = Panel31->Width;
     SGr1->ColWidths[26] = Panel32->Width;
     SGr1->ColWidths[27] = Panel33->Width;
     SGr1->ColWidths[28] = Panel34->Width;

     // ボタンの初期化
     BtnF01->Enabled = true;
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF04->Enabled = false;
     BtnF05->Enabled = false;
     BtnF06->Enabled = false;
     BtnF07->Enabled = true;
     BtnF08->Enabled = false;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;
     BtnF11->Enabled = false;
     BtnF12->Enabled = true;

     // エディットの初期化
     //EdtCOD->Text = "";
     Edt01->Text = "";
     Edt02->Text = "";
     Edt03->Text = "";
     Edt04->Text = "";
     Edt05->Text = "";
     Edt06->Text = "";
     Edt07->Text = "";
     Edt08->Text = "";
     Edt13->Text = "";
     Edt14->Text = "";
     Edt15->Text = "";
     Edt16->Text = "";
     Edt17->Text = "";
     Edt18->Text = "";
     Edt19->Text = "";
     Edt20->Text = "";
     Edt21->Text = "";
     Edt22->Text = "";
     Edt23->Text = "";
     Edt24->Text = "";
     Edt25->Text = "";
     Edt26->Text = "";
     Edt27->Text = "";
     Edt28->Text = "";

     // 行をまとめて追加する
     for( i=0; i<SGr1->RowCount; i++ ){
         x = div( i, 30 );
         sBuf = IntToStr(x.quot + 1);
         SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
         sBuf = IntToStr(x.rem + 1);
         SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
     }

     DataSave = false;
     NotFound = true;

     // 検査予定日の初期化
     DtTOMR = Date();
     DtTOMR++;
     EdtCOD->Text = FormatDateTime("yyyy/mm/dd",DtTOMR);

     // iniファイル読み込み
     Read_Ini();

     // 工場区分表示
     //PnlKojoKbn->Caption = IntToStr(iKojoKbn);

}

//---------------------------------------------------------------------------

void __fastcall TForm1::ExtractCode(AnsiString str)
{
    //ユーザコード、ユーザ名、部署コード、部署名 抽出
    int i,n1,m,strlen;

    //初期化
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //区切り記号","の検索
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=iの時は文字列NULL
                switch(m){
                //変数に文字列代入
                    case 1:
                    //USER_COD
                        USER_COD = StrToInt(str.SubString(n1,i - n1));
                        break;
                    case 2:
                    //USER_NAM
                        USER_NAM = str.SubString(n1,i - n1);
                        break;
                    case 3:
                    //BUMO_COD
                        BUMO_COD = str.SubString(n1,i - n1);
                        break;
                    case 4:
                    //BUMO_NAM
                        BUMO_NAM = str.SubString(n1,i - n1);
                        break;
                    default:
                        break;
                }

            }
            //次の文字列開始位置
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // 初期化表示
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

}


//---------------------------------------------------------------------------
// 「Ｆ１：一覧検索」
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    if( !BtnF01->Tag ){
        ////////////////////
        // 一覧検索
        Form2->ShowModal();
    }
    else{
        ////////////////////
        // ソート
        int         i,k;
        TKM01       Tmp_KM01;
        AnsiString  sBuf;

        SBr1->Panels->Items[0]->Text = "ソート中です．．．しばらくお待ち下さい。 ";
        SBr1->Update();

        for( i=0; i<(SGr1->RowCount-1); i++ ){
            for( k=i+1; k<SGr1->RowCount; k++ ){
                if( SGr1->Cells[10][i] == SGr1->Cells[10][k] ){         // ｿｰﾄｷｰ
                    if( SGr1->Cells[4][i] == SGr1->Cells[4][k] ){       // 得意先品番
                        if( SGr1->Cells[5][i] > SGr1->Cells[5][k] &&
                                          SGr1->Cells[5][k] != "" ){    // ロットNO

                            sBuf = SGr1->Cells[2][i];
                            strcpy( Tmp_KM01.KOKBNG    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[3][i];
                            strcpy( Tmp_KM01.DTKSCOD   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[4][i];
                            strcpy( Tmp_KM01.DTKSHIN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[5][i];
                            strcpy( Tmp_KM01.LOTNO     ,sBuf.c_str() );
                            sBuf = SGr1->Cells[6][i];
                            strcpy( Tmp_KM01.HINBAN    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[7][i];
                            strcpy( Tmp_KM01.ZISNAM    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[8][i];
                            strcpy( Tmp_KM01.ZISCOD    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[9][i];
                            strcpy( Tmp_KM01.NUM       ,sBuf.c_str() );
                            sBuf = SGr1->Cells[10][i];
                            strcpy( Tmp_KM01.SORTKEY   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[11][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );
                            sBuf = SGr1->Cells[12][i];
                            strcpy( Tmp_KM01.KEIJKBN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[13][i];
                            strcpy( Tmp_KM01.KEIJKBNNM ,sBuf.c_str() );
                            sBuf = SGr1->Cells[14][i];
                            strcpy( Tmp_KM01.SK_LD_LNG ,sBuf.c_str() );
                            sBuf = SGr1->Cells[15][i];
                            strcpy( Tmp_KM01.SK_BURASI ,sBuf.c_str() );
                            sBuf = SGr1->Cells[16][i];
                            strcpy( Tmp_KM01.SK_BURASIT,sBuf.c_str() );
                            sBuf = SGr1->Cells[17][i];
                            strcpy( Tmp_KM01.SK_LD_TR  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[18][i];
                            strcpy( Tmp_KM01.SK_LD_HP  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[19][i];
                            strcpy( Tmp_KM01.SK_BOIAI  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[20][i];
                            strcpy( Tmp_KM01.SK_KOYU   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[21][i];
                            strcpy( Tmp_KM01.SK_MAGE   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[22][i];
                            strcpy( Tmp_KM01.SK_MAGEG  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[23][i];
                            strcpy( Tmp_KM01.SK_HSC_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[24][i];
                            strcpy( Tmp_KM01.SK_HSC_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[25][i];
                            strcpy( Tmp_KM01.SK_HSD_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[26][i];
                            strcpy( Tmp_KM01.SK_HSD_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[27][i];
                            strcpy( Tmp_KM01.SK_ZAKUT  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[28][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );

                            SGr1->Cells[2][i] = SGr1->Cells[2][k] ;
                            SGr1->Cells[3][i] = SGr1->Cells[3][k] ;
                            SGr1->Cells[4][i] = SGr1->Cells[4][k] ;
                            SGr1->Cells[5][i] = SGr1->Cells[5][k] ;
                            SGr1->Cells[6][i] = SGr1->Cells[6][k] ;
                            SGr1->Cells[7][i] = SGr1->Cells[7][k] ;
                            SGr1->Cells[8][i] = SGr1->Cells[8][k] ;
                            SGr1->Cells[9][i] = SGr1->Cells[9][k] ;
                            SGr1->Cells[10][i]= SGr1->Cells[10][k];
                            SGr1->Cells[11][i]= SGr1->Cells[11][k];
                            SGr1->Cells[12][i]= SGr1->Cells[12][k];
                            SGr1->Cells[13][i]= SGr1->Cells[13][k];
                            SGr1->Cells[14][i]= SGr1->Cells[14][k];
                            SGr1->Cells[15][i]= SGr1->Cells[15][k];
                            SGr1->Cells[16][i]= SGr1->Cells[16][k];
                            SGr1->Cells[17][i]= SGr1->Cells[17][k];
                            SGr1->Cells[18][i]= SGr1->Cells[18][k];
                            SGr1->Cells[19][i]= SGr1->Cells[19][k];
                            SGr1->Cells[20][i]= SGr1->Cells[20][k];
                            SGr1->Cells[21][i]= SGr1->Cells[21][k];
                            SGr1->Cells[22][i]= SGr1->Cells[22][k];
                            SGr1->Cells[23][i]= SGr1->Cells[23][k];
                            SGr1->Cells[24][i]= SGr1->Cells[24][k];
                            SGr1->Cells[25][i]= SGr1->Cells[25][k];
                            SGr1->Cells[26][i]= SGr1->Cells[26][k];
                            SGr1->Cells[27][i]= SGr1->Cells[27][k];
                            SGr1->Cells[28][i]= SGr1->Cells[28][k];

                            SGr1->Cells[2][k] = Tmp_KM01.KOKBNG    ;
                            SGr1->Cells[3][k] = Tmp_KM01.DTKSCOD   ;
                            SGr1->Cells[4][k] = Tmp_KM01.DTKSHIN   ;
                            SGr1->Cells[5][k] = Tmp_KM01.LOTNO     ;
                            SGr1->Cells[6][k] = Tmp_KM01.HINBAN    ;
                            SGr1->Cells[7][k] = Tmp_KM01.ZISNAM    ;
                            SGr1->Cells[8][k] = Tmp_KM01.ZISCOD    ;
                            SGr1->Cells[9][k] = Tmp_KM01.NUM       ;
                            SGr1->Cells[10][k]= Tmp_KM01.SORTKEY   ;
                            SGr1->Cells[11][k]= Tmp_KM01.HIST_SOKUT;
                            SGr1->Cells[12][k]= Tmp_KM01.KEIJKBN   ;
                            SGr1->Cells[13][k]= Tmp_KM01.KEIJKBNNM ;
                            SGr1->Cells[14][k]= Tmp_KM01.SK_LD_LNG ;
                            SGr1->Cells[15][k]= Tmp_KM01.SK_BURASI ;
                            SGr1->Cells[16][k]= Tmp_KM01.SK_BURASIT;
                            SGr1->Cells[17][k]= Tmp_KM01.SK_LD_TR  ;
                            SGr1->Cells[18][k]= Tmp_KM01.SK_LD_HP  ;
                            SGr1->Cells[19][k]= Tmp_KM01.SK_BOIAI  ;
                            SGr1->Cells[20][k]= Tmp_KM01.SK_KOYU   ;
                            SGr1->Cells[21][k]= Tmp_KM01.SK_MAGE   ;
                            SGr1->Cells[22][k]= Tmp_KM01.SK_MAGEG  ;
                            SGr1->Cells[23][k]= Tmp_KM01.SK_HSC_A  ;
                            SGr1->Cells[24][k]= Tmp_KM01.SK_HSC_S  ;
                            SGr1->Cells[25][k]= Tmp_KM01.SK_HSD_A  ;
                            SGr1->Cells[26][k]= Tmp_KM01.SK_HSD_S  ;
                            SGr1->Cells[27][k]= Tmp_KM01.SK_ZAKUT  ;
                            SGr1->Cells[28][k]= Tmp_KM01.HIST_SOKUT;

                        }
                    }
                    else{
                        if( SGr1->Cells[4][i] > SGr1->Cells[4][k] &&   // 得意先品番
                                          SGr1->Cells[4][k] != "" ){

                            sBuf = SGr1->Cells[2][i];
                            strcpy( Tmp_KM01.KOKBNG    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[3][i];
                            strcpy( Tmp_KM01.DTKSCOD   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[4][i];
                            strcpy( Tmp_KM01.DTKSHIN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[5][i];
                            strcpy( Tmp_KM01.LOTNO     ,sBuf.c_str() );
                            sBuf = SGr1->Cells[6][i];
                            strcpy( Tmp_KM01.HINBAN    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[7][i];
                            strcpy( Tmp_KM01.ZISNAM    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[8][i];
                            strcpy( Tmp_KM01.ZISCOD    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[9][i];
                            strcpy( Tmp_KM01.NUM       ,sBuf.c_str() );
                            sBuf = SGr1->Cells[10][i];
                            strcpy( Tmp_KM01.SORTKEY   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[11][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );
                            sBuf = SGr1->Cells[12][i];
                            strcpy( Tmp_KM01.KEIJKBN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[13][i];
                            strcpy( Tmp_KM01.KEIJKBNNM ,sBuf.c_str() );
                            sBuf = SGr1->Cells[14][i];
                            strcpy( Tmp_KM01.SK_LD_LNG ,sBuf.c_str() );
                            sBuf = SGr1->Cells[15][i];
                            strcpy( Tmp_KM01.SK_BURASI ,sBuf.c_str() );
                            sBuf = SGr1->Cells[16][i];
                            strcpy( Tmp_KM01.SK_BURASIT,sBuf.c_str() );
                            sBuf = SGr1->Cells[17][i];
                            strcpy( Tmp_KM01.SK_LD_TR  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[18][i];
                            strcpy( Tmp_KM01.SK_LD_HP  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[19][i];
                            strcpy( Tmp_KM01.SK_BOIAI  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[20][i];
                            strcpy( Tmp_KM01.SK_KOYU   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[21][i];
                            strcpy( Tmp_KM01.SK_MAGE   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[22][i];
                            strcpy( Tmp_KM01.SK_MAGEG  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[23][i];
                            strcpy( Tmp_KM01.SK_HSC_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[24][i];
                            strcpy( Tmp_KM01.SK_HSC_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[25][i];
                            strcpy( Tmp_KM01.SK_HSD_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[26][i];
                            strcpy( Tmp_KM01.SK_HSD_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[27][i];
                            strcpy( Tmp_KM01.SK_ZAKUT  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[28][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );

                            SGr1->Cells[2][i] = SGr1->Cells[2][k] ;
                            SGr1->Cells[3][i] = SGr1->Cells[3][k] ;
                            SGr1->Cells[4][i] = SGr1->Cells[4][k] ;
                            SGr1->Cells[5][i] = SGr1->Cells[5][k] ;
                            SGr1->Cells[6][i] = SGr1->Cells[6][k] ;
                            SGr1->Cells[7][i] = SGr1->Cells[7][k] ;
                            SGr1->Cells[8][i] = SGr1->Cells[8][k] ;
                            SGr1->Cells[9][i] = SGr1->Cells[9][k] ;
                            SGr1->Cells[10][i]= SGr1->Cells[10][k];
                            SGr1->Cells[11][i]= SGr1->Cells[11][k];
                            SGr1->Cells[12][i]= SGr1->Cells[12][k];
                            SGr1->Cells[13][i]= SGr1->Cells[13][k];
                            SGr1->Cells[14][i]= SGr1->Cells[14][k];
                            SGr1->Cells[15][i]= SGr1->Cells[15][k];
                            SGr1->Cells[16][i]= SGr1->Cells[16][k];
                            SGr1->Cells[17][i]= SGr1->Cells[17][k];
                            SGr1->Cells[18][i]= SGr1->Cells[18][k];
                            SGr1->Cells[19][i]= SGr1->Cells[19][k];
                            SGr1->Cells[20][i]= SGr1->Cells[20][k];
                            SGr1->Cells[21][i]= SGr1->Cells[21][k];
                            SGr1->Cells[22][i]= SGr1->Cells[22][k];
                            SGr1->Cells[23][i]= SGr1->Cells[23][k];
                            SGr1->Cells[24][i]= SGr1->Cells[24][k];
                            SGr1->Cells[25][i]= SGr1->Cells[25][k];
                            SGr1->Cells[26][i]= SGr1->Cells[26][k];
                            SGr1->Cells[27][i]= SGr1->Cells[27][k];
                            SGr1->Cells[28][i]= SGr1->Cells[28][k];

                            SGr1->Cells[2][k] = Tmp_KM01.KOKBNG    ;
                            SGr1->Cells[3][k] = Tmp_KM01.DTKSCOD   ;
                            SGr1->Cells[4][k] = Tmp_KM01.DTKSHIN   ;
                            SGr1->Cells[5][k] = Tmp_KM01.LOTNO     ;
                            SGr1->Cells[6][k] = Tmp_KM01.HINBAN    ;
                            SGr1->Cells[7][k] = Tmp_KM01.ZISNAM    ;
                            SGr1->Cells[8][k] = Tmp_KM01.ZISCOD    ;
                            SGr1->Cells[9][k] = Tmp_KM01.NUM       ;
                            SGr1->Cells[10][k]= Tmp_KM01.SORTKEY   ;
                            SGr1->Cells[11][k]= Tmp_KM01.HIST_SOKUT;
                            SGr1->Cells[12][k]= Tmp_KM01.KEIJKBN   ;
                            SGr1->Cells[13][k]= Tmp_KM01.KEIJKBNNM ;
                            SGr1->Cells[14][k]= Tmp_KM01.SK_LD_LNG ;
                            SGr1->Cells[15][k]= Tmp_KM01.SK_BURASI ;
                            SGr1->Cells[16][k]= Tmp_KM01.SK_BURASIT;
                            SGr1->Cells[17][k]= Tmp_KM01.SK_LD_TR  ;
                            SGr1->Cells[18][k]= Tmp_KM01.SK_LD_HP  ;
                            SGr1->Cells[19][k]= Tmp_KM01.SK_BOIAI  ;
                            SGr1->Cells[20][k]= Tmp_KM01.SK_KOYU   ;
                            SGr1->Cells[21][k]= Tmp_KM01.SK_MAGE   ;
                            SGr1->Cells[22][k]= Tmp_KM01.SK_MAGEG  ;
                            SGr1->Cells[23][k]= Tmp_KM01.SK_HSC_A  ;
                            SGr1->Cells[24][k]= Tmp_KM01.SK_HSC_S  ;
                            SGr1->Cells[25][k]= Tmp_KM01.SK_HSD_A  ;
                            SGr1->Cells[26][k]= Tmp_KM01.SK_HSD_S  ;
                            SGr1->Cells[27][k]= Tmp_KM01.SK_ZAKUT  ;
                            SGr1->Cells[28][k]= Tmp_KM01.HIST_SOKUT;

                        }
                    }
                }
                else{
                    if( SGr1->Cells[10][i] > SGr1->Cells[10][k] &&
                                       SGr1->Cells[10][k] != "" ){     // ｿｰﾄｷｰ

                            sBuf = SGr1->Cells[2][i];
                            strcpy( Tmp_KM01.KOKBNG    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[3][i];
                            strcpy( Tmp_KM01.DTKSCOD   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[4][i];
                            strcpy( Tmp_KM01.DTKSHIN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[5][i];
                            strcpy( Tmp_KM01.LOTNO     ,sBuf.c_str() );
                            sBuf = SGr1->Cells[6][i];
                            strcpy( Tmp_KM01.HINBAN    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[7][i];
                            strcpy( Tmp_KM01.ZISNAM    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[8][i];
                            strcpy( Tmp_KM01.ZISCOD    ,sBuf.c_str() );
                            sBuf = SGr1->Cells[9][i];
                            strcpy( Tmp_KM01.NUM       ,sBuf.c_str() );
                            sBuf = SGr1->Cells[10][i];
                            strcpy( Tmp_KM01.SORTKEY   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[11][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );
                            sBuf = SGr1->Cells[12][i];
                            strcpy( Tmp_KM01.KEIJKBN   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[13][i];
                            strcpy( Tmp_KM01.KEIJKBNNM ,sBuf.c_str() );
                            sBuf = SGr1->Cells[14][i];
                            strcpy( Tmp_KM01.SK_LD_LNG ,sBuf.c_str() );
                            sBuf = SGr1->Cells[15][i];
                            strcpy( Tmp_KM01.SK_BURASI ,sBuf.c_str() );
                            sBuf = SGr1->Cells[16][i];
                            strcpy( Tmp_KM01.SK_BURASIT,sBuf.c_str() );
                            sBuf = SGr1->Cells[17][i];
                            strcpy( Tmp_KM01.SK_LD_TR  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[18][i];
                            strcpy( Tmp_KM01.SK_LD_HP  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[19][i];
                            strcpy( Tmp_KM01.SK_BOIAI  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[20][i];
                            strcpy( Tmp_KM01.SK_KOYU   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[21][i];
                            strcpy( Tmp_KM01.SK_MAGE   ,sBuf.c_str() );
                            sBuf = SGr1->Cells[22][i];
                            strcpy( Tmp_KM01.SK_MAGEG  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[23][i];
                            strcpy( Tmp_KM01.SK_HSC_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[24][i];
                            strcpy( Tmp_KM01.SK_HSC_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[25][i];
                            strcpy( Tmp_KM01.SK_HSD_A  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[26][i];
                            strcpy( Tmp_KM01.SK_HSD_S  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[27][i];
                            strcpy( Tmp_KM01.SK_ZAKUT  ,sBuf.c_str() );
                            sBuf = SGr1->Cells[28][i];
                            strcpy( Tmp_KM01.HIST_SOKUT,sBuf.c_str() );

                            SGr1->Cells[2][i] = SGr1->Cells[2][k] ;
                            SGr1->Cells[3][i] = SGr1->Cells[3][k] ;
                            SGr1->Cells[4][i] = SGr1->Cells[4][k] ;
                            SGr1->Cells[5][i] = SGr1->Cells[5][k] ;
                            SGr1->Cells[6][i] = SGr1->Cells[6][k] ;
                            SGr1->Cells[7][i] = SGr1->Cells[7][k] ;
                            SGr1->Cells[8][i] = SGr1->Cells[8][k] ;
                            SGr1->Cells[9][i] = SGr1->Cells[9][k] ;
                            SGr1->Cells[10][i]= SGr1->Cells[10][k];
                            SGr1->Cells[11][i]= SGr1->Cells[11][k];
                            SGr1->Cells[12][i]= SGr1->Cells[12][k];
                            SGr1->Cells[13][i]= SGr1->Cells[13][k];
                            SGr1->Cells[14][i]= SGr1->Cells[14][k];
                            SGr1->Cells[15][i]= SGr1->Cells[15][k];
                            SGr1->Cells[16][i]= SGr1->Cells[16][k];
                            SGr1->Cells[17][i]= SGr1->Cells[17][k];
                            SGr1->Cells[18][i]= SGr1->Cells[18][k];
                            SGr1->Cells[19][i]= SGr1->Cells[19][k];
                            SGr1->Cells[20][i]= SGr1->Cells[20][k];
                            SGr1->Cells[21][i]= SGr1->Cells[21][k];
                            SGr1->Cells[22][i]= SGr1->Cells[22][k];
                            SGr1->Cells[23][i]= SGr1->Cells[23][k];
                            SGr1->Cells[24][i]= SGr1->Cells[24][k];
                            SGr1->Cells[25][i]= SGr1->Cells[25][k];
                            SGr1->Cells[26][i]= SGr1->Cells[26][k];
                            SGr1->Cells[27][i]= SGr1->Cells[27][k];
                            SGr1->Cells[28][i]= SGr1->Cells[28][k];

                            SGr1->Cells[2][k] = Tmp_KM01.KOKBNG    ;
                            SGr1->Cells[3][k] = Tmp_KM01.DTKSCOD   ;
                            SGr1->Cells[4][k] = Tmp_KM01.DTKSHIN   ;
                            SGr1->Cells[5][k] = Tmp_KM01.LOTNO     ;
                            SGr1->Cells[6][k] = Tmp_KM01.HINBAN    ;
                            SGr1->Cells[7][k] = Tmp_KM01.ZISNAM    ;
                            SGr1->Cells[8][k] = Tmp_KM01.ZISCOD    ;
                            SGr1->Cells[9][k] = Tmp_KM01.NUM       ;
                            SGr1->Cells[10][k]= Tmp_KM01.SORTKEY   ;
                            SGr1->Cells[11][k]= Tmp_KM01.HIST_SOKUT;
                            SGr1->Cells[12][k]= Tmp_KM01.KEIJKBN   ;
                            SGr1->Cells[13][k]= Tmp_KM01.KEIJKBNNM ;
                            SGr1->Cells[14][k]= Tmp_KM01.SK_LD_LNG ;
                            SGr1->Cells[15][k]= Tmp_KM01.SK_BURASI ;
                            SGr1->Cells[16][k]= Tmp_KM01.SK_BURASIT;
                            SGr1->Cells[17][k]= Tmp_KM01.SK_LD_TR  ;
                            SGr1->Cells[18][k]= Tmp_KM01.SK_LD_HP  ;
                            SGr1->Cells[19][k]= Tmp_KM01.SK_BOIAI  ;
                            SGr1->Cells[20][k]= Tmp_KM01.SK_KOYU   ;
                            SGr1->Cells[21][k]= Tmp_KM01.SK_MAGE   ;
                            SGr1->Cells[22][k]= Tmp_KM01.SK_MAGEG  ;
                            SGr1->Cells[23][k]= Tmp_KM01.SK_HSC_A  ;
                            SGr1->Cells[24][k]= Tmp_KM01.SK_HSC_S  ;
                            SGr1->Cells[25][k]= Tmp_KM01.SK_HSD_A  ;
                            SGr1->Cells[26][k]= Tmp_KM01.SK_HSD_S  ;
                            SGr1->Cells[27][k]= Tmp_KM01.SK_ZAKUT  ;
                            SGr1->Cells[28][k]= Tmp_KM01.HIST_SOKUT;

                    }
                }
            }
        }

        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();

        // データを変更したフラグ
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// 「Ｆ２：前項」
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
    if( !BtnF02->Tag ){
        // 前項
        if(SGr1->Row > 0){
            SGr1->Row -= 1;
            SGr1->SetFocus();
        }
    }
}

//---------------------------------------------------------------------------
// 「Ｆ３：次項」
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
    if( !BtnF03->Tag ){
        // 次項
        if( (SGr1->RowCount-1) > SGr1->Row ){
            SGr1->Row += 1;
            SGr1->SetFocus();
        }
    }
}

//---------------------------------------------------------------------------
// 「Ｆ４：コピー」
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled )    return;

    if( !BtnF04->Tag ){
        ///////////////////
        // コピー

        int         i;
        int         cnt;
        AnsiString  sBuf;

        // コピーの個数を確保します
        CopyCnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // メモリの確保
        if( hMemCopy ){
            GlobalUnlock( hMemCopy );
            GlobalFree( hMemCopy );
        }
        hMemCopy = GlobalAlloc( GHND, sizeof(struct TKM01) * CopyCnt );
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
            SBr1->Update();
            Beep();
            return;
        }
        KM01 = (struct TKM01 *)GlobalLock(hMemCopy);
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
            SBr1->Update();
            Beep();
            return;
        }

        // 選択されている範囲をメモリに格納します
        for( i=SGr1->Selection.Top, cnt=0; i<=SGr1->Selection.Bottom ; i++, cnt++ ) {
            sBuf = SGr1->Cells[2][i];
            strcpy( KM01[cnt].KOKBNG,  sBuf.c_str() );            // 工管NO
            sBuf = SGr1->Cells[3][i];
            strcpy( KM01[cnt].DTKSCOD, sBuf.c_str() );            // 得意先ｺｰﾄﾞ
            sBuf = SGr1->Cells[4][i];
            strcpy( KM01[cnt].DTKSHIN, sBuf.c_str() );            // 得意先品番
            sBuf = SGr1->Cells[5][i];
            strcpy( KM01[cnt].LOTNO,   sBuf.c_str() );            // ロットNO
            sBuf = SGr1->Cells[6][i];
            strcpy( KM01[cnt].HINBAN,  sBuf.c_str() );            // 自社品番
            sBuf = SGr1->Cells[7][i];
            strcpy( KM01[cnt].ZISNAM,  sBuf.c_str() );            // 材質名称
            sBuf = SGr1->Cells[8][i];
            strcpy( KM01[cnt].ZISCOD,  sBuf.c_str() );            // 材質ｺｰﾄﾞ
            sBuf = SGr1->Cells[9][i];
            strcpy( KM01[cnt].NUM,     sBuf.c_str() );            // 数量
            sBuf = SGr1->Cells[10][i];
            strcpy( KM01[cnt].SORTKEY, sBuf.c_str() );            // ｿｰﾄｷｰ
            sBuf = SGr1->Cells[11][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ﾋｽﾄｸﾞﾗﾑ測定数
            sBuf = SGr1->Cells[12][i];
            strcpy( KM01[cnt].KEIJKBN   ,sBuf.c_str() );          // 形状区分
            sBuf = SGr1->Cells[13][i];
            strcpy( KM01[cnt].KEIJKBNNM ,sBuf.c_str() );          // 形状区分名称
            sBuf = SGr1->Cells[14][i];
            strcpy( KM01[cnt].SK_LD_LNG ,sBuf.c_str() );          // 測定区分 リード線長さ
            sBuf = SGr1->Cells[15][i];
            strcpy( KM01[cnt].SK_BURASI ,sBuf.c_str() );          // 測定区分 ブラシ幅
            sBuf = SGr1->Cells[16][i];
            strcpy( KM01[cnt].SK_BURASIT,sBuf.c_str() );          // 測定区分 ブラシ幅縦押し
            sBuf = SGr1->Cells[17][i];
            strcpy( KM01[cnt].SK_LD_TR  ,sBuf.c_str() );          // 測定区分 リード線取り付け抵抗
            sBuf = SGr1->Cells[18][i];
            strcpy( KM01[cnt].SK_LD_HP  ,sBuf.c_str() );          // 測定区分 リード線引張強度
            sBuf = SGr1->Cells[19][i];
            strcpy( KM01[cnt].SK_BOIAI  ,sBuf.c_str() );          // 測定区分 母体比重
            sBuf = SGr1->Cells[20][i];
            strcpy( KM01[cnt].SK_KOYU   ,sBuf.c_str() );          // 測定区分 固有抵抗率
            sBuf = SGr1->Cells[21][i];
            strcpy( KM01[cnt].SK_MAGE   ,sBuf.c_str() );          // 測定区分 曲げ強さ
            sBuf = SGr1->Cells[22][i];
            strcpy( KM01[cnt].SK_MAGEG  ,sBuf.c_str() );          // 測定区分 曲げ強さ現物
            sBuf = SGr1->Cells[23][i];
            strcpy( KM01[cnt].SK_HSC_A  ,sBuf.c_str() );          // 測定区分 HsC硬度（側面）
            sBuf = SGr1->Cells[24][i];
            strcpy( KM01[cnt].SK_HSC_S  ,sBuf.c_str() );          // 測定区分 HsC硬度（圧面）
            sBuf = SGr1->Cells[25][i];
            strcpy( KM01[cnt].SK_HSD_A  ,sBuf.c_str() );          // 測定区分 HsD硬度（側面）
            sBuf = SGr1->Cells[26][i];
            strcpy( KM01[cnt].SK_HSD_S  ,sBuf.c_str() );          // 測定区分 HsD硬度（圧面）
            sBuf = SGr1->Cells[27][i];
            strcpy( KM01[cnt].SK_ZAKUT  ,sBuf.c_str() );          // 測定区分 座屈
            sBuf = SGr1->Cells[28][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ﾋｽﾄｸﾞﾗﾑ測定数
        }
    }
    else{
        ///////////////////
        // 切り取り

        int   i,j;
        int   cnt;
        div_t x;
        AnsiString  sBuf;

        // コピーの個数を確保します
        CopyCnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // メモリの確保
        if( hMemCopy ){
            GlobalUnlock( hMemCopy );
            GlobalFree( hMemCopy );
        }
        hMemCopy = GlobalAlloc( GHND, sizeof(struct TKM01) * CopyCnt );
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(01)";
            SBr1->Update();
            Beep();
            return;
        }
        KM01 = (struct TKM01 *)GlobalLock(hMemCopy);
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "メモリ領域を確保できません。(02)";
            SBr1->Update();
            Beep();
            return;
        }

        // 選択されている範囲をメモリに格納します
        for( i=SGr1->Selection.Top, cnt=0; i<=SGr1->Selection.Bottom ; i++, cnt++ ) {
            sBuf = SGr1->Cells[2][i];
            strcpy( KM01[cnt].KOKBNG,  sBuf.c_str() );            // 工管NO
            sBuf = SGr1->Cells[3][i];
            strcpy( KM01[cnt].DTKSCOD, sBuf.c_str() );            // 得意先ｺｰﾄﾞ
            sBuf = SGr1->Cells[4][i];
            strcpy( KM01[cnt].DTKSHIN, sBuf.c_str() );            // 得意先品番
            sBuf = SGr1->Cells[5][i];
            strcpy( KM01[cnt].LOTNO,   sBuf.c_str() );            // ロットNO
            sBuf = SGr1->Cells[6][i];
            strcpy( KM01[cnt].HINBAN,  sBuf.c_str() );            // 自社品番
            sBuf = SGr1->Cells[7][i];
            strcpy( KM01[cnt].ZISNAM,  sBuf.c_str() );            // 材質名称
            sBuf = SGr1->Cells[8][i];
            strcpy( KM01[cnt].ZISCOD,  sBuf.c_str() );            // 材質ｺｰﾄﾞ
            sBuf = SGr1->Cells[9][i];
            strcpy( KM01[cnt].NUM,     sBuf.c_str() );            // 数量
            sBuf = SGr1->Cells[10][i];
            strcpy( KM01[cnt].SORTKEY, sBuf.c_str() );            // ｿｰﾄｷｰ
            sBuf = SGr1->Cells[11][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ﾋｽﾄｸﾞﾗﾑ測定数
            sBuf = SGr1->Cells[12][i];
            strcpy( KM01[cnt].KEIJKBN   ,sBuf.c_str() );          // 形状区分
            sBuf = SGr1->Cells[13][i];
            strcpy( KM01[cnt].KEIJKBNNM ,sBuf.c_str() );          // 形状区分名称
            sBuf = SGr1->Cells[14][i];
            strcpy( KM01[cnt].SK_LD_LNG ,sBuf.c_str() );          // 測定区分 リード線長さ
            sBuf = SGr1->Cells[15][i];
            strcpy( KM01[cnt].SK_BURASI ,sBuf.c_str() );          // 測定区分 ブラシ幅
            sBuf = SGr1->Cells[16][i];
            strcpy( KM01[cnt].SK_BURASIT,sBuf.c_str() );          // 測定区分 ブラシ幅縦押し
            sBuf = SGr1->Cells[17][i];
            strcpy( KM01[cnt].SK_LD_TR  ,sBuf.c_str() );          // 測定区分 リード線取り付け抵抗
            sBuf = SGr1->Cells[18][i];
            strcpy( KM01[cnt].SK_LD_HP  ,sBuf.c_str() );          // 測定区分 リード線引張強度
            sBuf = SGr1->Cells[19][i];
            strcpy( KM01[cnt].SK_BOIAI  ,sBuf.c_str() );          // 測定区分 母体比重
            sBuf = SGr1->Cells[20][i];
            strcpy( KM01[cnt].SK_KOYU   ,sBuf.c_str() );          // 測定区分 固有抵抗率
            sBuf = SGr1->Cells[21][i];
            strcpy( KM01[cnt].SK_MAGE   ,sBuf.c_str() );          // 測定区分 曲げ強さ
            sBuf = SGr1->Cells[22][i];
            strcpy( KM01[cnt].SK_MAGEG  ,sBuf.c_str() );          // 測定区分 曲げ強さ現物
            sBuf = SGr1->Cells[23][i];
            strcpy( KM01[cnt].SK_HSC_A  ,sBuf.c_str() );          // 測定区分 HsC硬度（側面）
            sBuf = SGr1->Cells[24][i];
            strcpy( KM01[cnt].SK_HSC_S  ,sBuf.c_str() );          // 測定区分 HsC硬度（圧面）
            sBuf = SGr1->Cells[25][i];
            strcpy( KM01[cnt].SK_HSD_A  ,sBuf.c_str() );          // 測定区分 HsD硬度（側面）
            sBuf = SGr1->Cells[26][i];
            strcpy( KM01[cnt].SK_HSD_S  ,sBuf.c_str() );          // 測定区分 HsD硬度（圧面）
            sBuf = SGr1->Cells[27][i];
            strcpy( KM01[cnt].SK_ZAKUT  ,sBuf.c_str() );          // 測定区分 座屈
            sBuf = SGr1->Cells[28][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // グリッドのクリアー処理

        // 選択されている範囲をクリアーします
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++) {
            // グリッドを削除します。
            for( j=2; j<=28 ; j++) {
                SGr1->Cells[j][i] = "";
            }
        }

        x = div( SGr1->Selection.Top, 30 );
        // x.quot  商
        // x.rem   余

        if( (x.rem + CopyCnt) > 30 ){
            // 選択範囲が複数のトレーにまたがっているとき

            x = div( SGr1->Selection.Bottom + 1, 30 );
            // x.quot  商
            // x.rem   余

            for( i=(x.quot*30), cnt=0; i<(x.quot*30+30); i++, cnt++ ) {
                // グリッドを詰めます
                if( (30 - x.rem) > cnt ){
                    for( j=2; j<=28; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+x.rem];
                    }
                }
                else{
                    for( j=2; j<=28; j++) {
                        SGr1->Cells[j][i] = "";
                    }
                }
            }
        }
        else if( (x.rem + CopyCnt) < 30 ){
            // 選択範囲が一つのトレーに納まっているとき
            for( i=SGr1->Selection.Top; i<(x.quot*30+30); i++ ) {
                // グリッドを詰めます
                if( (i + CopyCnt) < (x.quot*30+30) ){
                    for( j=2; j<=28; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+CopyCnt];
                    }
                }
                else{
                    for( j=2; j<=28; j++) {
                        SGr1->Cells[j][i] = "";
                    }
                }
            }
        }

        // データを変更したフラグ
        DataSave = true;

    }

    // カーソルを先頭に戻します
    SGr1->Row = SGr1->Selection.Top;

}

//---------------------------------------------------------------------------
// 「Ｆ５：貼り付け」
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;
    if( !BtnF05->Tag ){
        //////////////
        // 貼り付け

        int         i,j,cnt;
        div_t       x;
        AnsiString  sBuf;


        // 行をまとめて追加する
        x = div( (SGr1->Selection.Top + CopyCnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
            }
        }

        // コピー用メモリからグリッドに格納します
        for( i=SGr1->Row, cnt=0; cnt<CopyCnt ; i++, cnt++ ) {
            SGr1->Cells[2][i] = KM01[cnt].KOKBNG ;            // 工管NO
            SGr1->Cells[3][i] = KM01[cnt].DTKSCOD;            // 得意先ｺｰﾄﾞ
            SGr1->Cells[4][i] = KM01[cnt].DTKSHIN;            // 得意先品番
            SGr1->Cells[5][i] = KM01[cnt].LOTNO  ;            // ロットNO
            SGr1->Cells[6][i] = KM01[cnt].HINBAN ;            // 自社品番
            SGr1->Cells[7][i] = KM01[cnt].ZISNAM ;            // 材質名称
            SGr1->Cells[8][i] = KM01[cnt].ZISCOD ;            // 材質ｺｰﾄﾞ
            SGr1->Cells[9][i] = KM01[cnt].NUM    ;            // 数量
            SGr1->Cells[10][i]= KM01[cnt].SORTKEY;            // ｿｰﾄｷｰ
            SGr1->Cells[11][i]= KM01[cnt].HIST_SOKUT;         // ﾋｽﾄｸﾞﾗﾑ測定数
            SGr1->Cells[12][i]= KM01[cnt].KEIJKBN;            // 形状区分
            SGr1->Cells[13][i]= KM01[cnt].KEIJKBNNM;          // 形状区分名称
            SGr1->Cells[14][i]= KM01[cnt].SK_LD_LNG;          // 測定区分 リード線長さ
            SGr1->Cells[15][i]= KM01[cnt].SK_BURASI;          // 測定区分 ブラシ幅
            SGr1->Cells[16][i]= KM01[cnt].SK_BURASIT;         // 測定区分 ブラシ幅縦押し
            SGr1->Cells[17][i]= KM01[cnt].SK_LD_TR;           // 測定区分 リード線取り付け抵抗
            SGr1->Cells[18][i]= KM01[cnt].SK_LD_HP;           // 測定区分 リード線引張強度
            SGr1->Cells[19][i]= KM01[cnt].SK_BOIAI;           // 測定区分 母体比重
            SGr1->Cells[20][i]= KM01[cnt].SK_KOYU;            // 測定区分 固有抵抗率
            SGr1->Cells[21][i]= KM01[cnt].SK_MAGE;            // 測定区分 曲げ強さ
            SGr1->Cells[22][i]= KM01[cnt].SK_MAGEG;           // 測定区分 曲げ強さ現物
            SGr1->Cells[23][i]= KM01[cnt].SK_HSC_A;           // 測定区分 HsC硬度（側面）
            SGr1->Cells[24][i]= KM01[cnt].SK_HSC_S;           // 測定区分 HsC硬度（圧面）
            SGr1->Cells[25][i]= KM01[cnt].SK_HSD_A;           // 測定区分 HsD硬度（側面）
            SGr1->Cells[26][i]= KM01[cnt].SK_HSD_S;           // 測定区分 HsD硬度（圧面）
            SGr1->Cells[27][i]= KM01[cnt].SK_ZAKUT;           // 測定区分 座屈
            SGr1->Cells[28][i]= KM01[cnt].HIST_SOKUT;         // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // データを変更したフラグ
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// 「Ｆ６：挿入／空白挿入」
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;
    if( !BtnF06->Tag ){
        //////////////
        // 挿入

        int         i,j,end,cnt;
        div_t       x;
        AnsiString  sBuf;


        // データが有る最下行を探します
        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            // グリッドの一行を削除します。
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // 行をまとめて追加する
        x = div( (end + CopyCnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
            }
        }

        // 挿入する行だけ移動します
        for( i=(SGr1->RowCount-30); i>=(SGr1->Row+CopyCnt) ; i-- ) {
            // グリッドの一行を削除します。
            SGr1->Cells[2][i] = SGr1->Cells[2][i-CopyCnt];        // 工管NO
            SGr1->Cells[3][i] = SGr1->Cells[3][i-CopyCnt];        // 得意先ｺｰﾄﾞ
            SGr1->Cells[4][i] = SGr1->Cells[4][i-CopyCnt];        // 得意先品番
            SGr1->Cells[5][i] = SGr1->Cells[5][i-CopyCnt];        // ロットNO
            SGr1->Cells[6][i] = SGr1->Cells[6][i-CopyCnt];        // 自社品番
            SGr1->Cells[7][i] = SGr1->Cells[7][i-CopyCnt];        // 材質名称
            SGr1->Cells[8][i] = SGr1->Cells[8][i-CopyCnt];        // 材質ｺｰﾄﾞ
            SGr1->Cells[9][i] = SGr1->Cells[9][i-CopyCnt];        // 数量
            SGr1->Cells[10][i]= SGr1->Cells[10][i-CopyCnt];       // ｿｰﾄｷｰ
            SGr1->Cells[11][i]= SGr1->Cells[11][i-CopyCnt];       // ﾋｽﾄｸﾞﾗﾑ測定数
            SGr1->Cells[12][i]= SGr1->Cells[12][i-CopyCnt];       // 形状区分
            SGr1->Cells[13][i]= SGr1->Cells[13][i-CopyCnt];       // 形状区分名称
            SGr1->Cells[14][i]= SGr1->Cells[14][i-CopyCnt];       // 測定区分 リード線長さ
            SGr1->Cells[15][i]= SGr1->Cells[15][i-CopyCnt];       // 測定区分 ブラシ幅
            SGr1->Cells[16][i]= SGr1->Cells[16][i-CopyCnt];       // 測定区分 ブラシ幅縦押し
            SGr1->Cells[17][i]= SGr1->Cells[17][i-CopyCnt];       // 測定区分 リード線取り付け抵抗
            SGr1->Cells[18][i]= SGr1->Cells[18][i-CopyCnt];       // 測定区分 リード線引張強度
            SGr1->Cells[19][i]= SGr1->Cells[19][i-CopyCnt];       // 測定区分 母体比重
            SGr1->Cells[20][i]= SGr1->Cells[20][i-CopyCnt];       // 測定区分 固有抵抗率
            SGr1->Cells[21][i]= SGr1->Cells[21][i-CopyCnt];       // 測定区分 曲げ強さ
            SGr1->Cells[22][i]= SGr1->Cells[22][i-CopyCnt];       // 測定区分 曲げ強さ現物
            SGr1->Cells[23][i]= SGr1->Cells[23][i-CopyCnt];       // 測定区分 HsC硬度（側面）
            SGr1->Cells[24][i]= SGr1->Cells[24][i-CopyCnt];       // 測定区分 HsC硬度（圧面）
            SGr1->Cells[25][i]= SGr1->Cells[25][i-CopyCnt];       // 測定区分 HsD硬度（側面）
            SGr1->Cells[26][i]= SGr1->Cells[26][i-CopyCnt];       // 測定区分 HsD硬度（圧面）
            SGr1->Cells[27][i]= SGr1->Cells[27][i-CopyCnt];       // 測定区分 座屈
            SGr1->Cells[28][i]= SGr1->Cells[28][i-CopyCnt];       // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // コピー用メモリからグリッドに格納します
        for( i=SGr1->Row, cnt=0; cnt<CopyCnt ; i++, cnt++ ) {
            SGr1->Cells[2][i] = KM01[cnt].KOKBNG ;            // 工管NO
            SGr1->Cells[3][i] = KM01[cnt].DTKSCOD;            // 得意先ｺｰﾄﾞ
            SGr1->Cells[4][i] = KM01[cnt].DTKSHIN;            // 得意先品番
            SGr1->Cells[5][i] = KM01[cnt].LOTNO  ;            // ロットNO
            SGr1->Cells[6][i] = KM01[cnt].HINBAN ;            // 自社品番
            SGr1->Cells[7][i] = KM01[cnt].ZISNAM ;            // 材質名称
            SGr1->Cells[8][i] = KM01[cnt].ZISCOD ;            // 材質ｺｰﾄﾞ
            SGr1->Cells[9][i] = KM01[cnt].NUM    ;            // 数量
            SGr1->Cells[10][i]= KM01[cnt].SORTKEY;            // ｿｰﾄｷｰ
            SGr1->Cells[11][i]= KM01[cnt].HIST_SOKUT;         // ﾋｽﾄｸﾞﾗﾑ測定数
            SGr1->Cells[12][i]= KM01[cnt].KEIJKBN;            // 形状区分
            SGr1->Cells[13][i]= KM01[cnt].KEIJKBNNM;          // 形状区分名称
            SGr1->Cells[14][i]= KM01[cnt].SK_LD_LNG;          // 測定区分 リード線長さ
            SGr1->Cells[15][i]= KM01[cnt].SK_BURASI;          // 測定区分 ブラシ幅
            SGr1->Cells[16][i]= KM01[cnt].SK_BURASIT;         // 測定区分 ブラシ幅縦押し
            SGr1->Cells[17][i]= KM01[cnt].SK_LD_TR;           // 測定区分 リード線取り付け抵抗
            SGr1->Cells[18][i]= KM01[cnt].SK_LD_HP;           // 測定区分 リード線引張強度
            SGr1->Cells[19][i]= KM01[cnt].SK_BOIAI;           // 測定区分 母体比重
            SGr1->Cells[20][i]= KM01[cnt].SK_KOYU;            // 測定区分 固有抵抗率
            SGr1->Cells[21][i]= KM01[cnt].SK_MAGE;            // 測定区分 曲げ強さ
            SGr1->Cells[22][i]= KM01[cnt].SK_MAGEG;           // 測定区分 曲げ強さ現物
            SGr1->Cells[23][i]= KM01[cnt].SK_HSC_A;           // 測定区分 HsC硬度（側面）
            SGr1->Cells[24][i]= KM01[cnt].SK_HSC_S;           // 測定区分 HsC硬度（圧面）
            SGr1->Cells[25][i]= KM01[cnt].SK_HSD_A;           // 測定区分 HsD硬度（側面）
            SGr1->Cells[26][i]= KM01[cnt].SK_HSD_S;           // 測定区分 HsD硬度（圧面）
            SGr1->Cells[27][i]= KM01[cnt].SK_ZAKUT;           // 測定区分 座屈
            SGr1->Cells[28][i]= KM01[cnt].HIST_SOKUT;         // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // データを変更したフラグ
        DataSave = true;

    }
    else{
        //////////////
        // 空白挿入

        int         i,j,end,cnt;
        div_t       x;
        AnsiString  sBuf;


        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // データが有る最下行を探します
        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            // グリッドの一行を削除します。
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // 行をまとめて追加する
        x = div( (end + cnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
            }
        }

        // 挿入する行だけ移動します
        for( i=(SGr1->RowCount-30); i>=(SGr1->Selection.Top+cnt) ; i-- ) {
            SGr1->Cells[2][i] = SGr1->Cells[2][i-cnt];        // 工管NO
            SGr1->Cells[3][i] = SGr1->Cells[3][i-cnt];        // 得意先ｺｰﾄﾞ
            SGr1->Cells[4][i] = SGr1->Cells[4][i-cnt];        // 得意先品番
            SGr1->Cells[5][i] = SGr1->Cells[5][i-cnt];        // ロットNO
            SGr1->Cells[6][i] = SGr1->Cells[6][i-cnt];        // 自社品番
            SGr1->Cells[7][i] = SGr1->Cells[7][i-cnt];        // 材質名称
            SGr1->Cells[8][i] = SGr1->Cells[8][i-cnt];        // 材質ｺｰﾄﾞ
            SGr1->Cells[9][i] = SGr1->Cells[9][i-cnt];        // 数量
            SGr1->Cells[10][i]= SGr1->Cells[10][i-cnt];       // ｿｰﾄｷｰ
            SGr1->Cells[11][i]= SGr1->Cells[11][i-cnt];       // ﾋｽﾄｸﾞﾗﾑ測定数
            SGr1->Cells[12][i]= SGr1->Cells[12][i-cnt];       // 形状区分
            SGr1->Cells[13][i]= SGr1->Cells[13][i-cnt];       // 形状区分名称
            SGr1->Cells[14][i]= SGr1->Cells[14][i-cnt];       // 測定区分 リード線長さ
            SGr1->Cells[15][i]= SGr1->Cells[15][i-cnt];       // 測定区分 ブラシ幅
            SGr1->Cells[16][i]= SGr1->Cells[16][i-cnt];       // 測定区分 ブラシ幅縦押し
            SGr1->Cells[17][i]= SGr1->Cells[17][i-cnt];       // 測定区分 リード線取り付け抵抗
            SGr1->Cells[18][i]= SGr1->Cells[18][i-cnt];       // 測定区分 リード線引張強度
            SGr1->Cells[19][i]= SGr1->Cells[19][i-cnt];       // 測定区分 母体比重
            SGr1->Cells[20][i]= SGr1->Cells[20][i-cnt];       // 測定区分 固有抵抗率
            SGr1->Cells[21][i]= SGr1->Cells[21][i-cnt];       // 測定区分 曲げ強さ
            SGr1->Cells[22][i]= SGr1->Cells[22][i-cnt];       // 測定区分 曲げ強さ現物
            SGr1->Cells[23][i]= SGr1->Cells[23][i-cnt];       // 測定区分 HsC硬度（側面）
            SGr1->Cells[24][i]= SGr1->Cells[24][i-cnt];       // 測定区分 HsC硬度（圧面）
            SGr1->Cells[25][i]= SGr1->Cells[25][i-cnt];       // 測定区分 HsD硬度（側面）
            SGr1->Cells[26][i]= SGr1->Cells[26][i-cnt];       // 測定区分 HsD硬度（圧面）
            SGr1->Cells[27][i]= SGr1->Cells[27][i-cnt];       // 測定区分 座屈
            SGr1->Cells[28][i]= SGr1->Cells[28][i-cnt];       // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // 空白行をグリッドに格納します
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++ ) {
            SGr1->Cells[2][i] = "";            // 工管NO
            SGr1->Cells[3][i] = "";            // 得意先ｺｰﾄﾞ
            SGr1->Cells[4][i] = "";            // 得意先品番
            SGr1->Cells[5][i] = "";            // ロットNO
            SGr1->Cells[6][i] = "";            // 自社品番
            SGr1->Cells[7][i] = "";            // 材質名称
            SGr1->Cells[8][i] = "";            // 材質ｺｰﾄﾞ
            SGr1->Cells[9][i] = "";            // 数量
            SGr1->Cells[10][i]= "";            // ｿｰﾄｷｰ
            SGr1->Cells[11][i]= "";            // ﾋｽﾄｸﾞﾗﾑ測定数
            SGr1->Cells[12][i]= "";            // 形状区分
            SGr1->Cells[13][i]= "";            // 形状区分名称
            SGr1->Cells[14][i]= "";            // 測定区分 リード線長さ
            SGr1->Cells[15][i]= "";            // 測定区分 ブラシ幅
            SGr1->Cells[16][i]= "";            // 測定区分 ブラシ幅縦押し
            SGr1->Cells[17][i]= "";            // 測定区分 リード線取り付け抵抗
            SGr1->Cells[18][i]= "";            // 測定区分 リード線引張強度
            SGr1->Cells[19][i]= "";            // 測定区分 母体比重
            SGr1->Cells[20][i]= "";            // 測定区分 固有抵抗率
            SGr1->Cells[21][i]= "";            // 測定区分 曲げ強さ
            SGr1->Cells[22][i]= "";            // 測定区分 曲げ強さ現物
            SGr1->Cells[23][i]= "";            // 測定区分 HsC硬度（側面）
            SGr1->Cells[24][i]= "";            // 測定区分 HsC硬度（圧面）
            SGr1->Cells[25][i]= "";            // 測定区分 HsD硬度（側面）
            SGr1->Cells[26][i]= "";            // 測定区分 HsD硬度（圧面）
            SGr1->Cells[27][i]= "";            // 測定区分 座屈
            SGr1->Cells[28][i]= "";            // ﾋｽﾄｸﾞﾗﾑ測定数
        }

        // データを変更したフラグ
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// 「Ｆ７：検索」
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
    if( !BtnF07->Enabled )    return;
    if( !BtnF07->Tag ){
        //////////////
        // 検索
        SubSearch( Sender, DelSEPA(EdtCOD->Text));
    }
}

//---------------------------------------------------------------------------
// 「Ｆ８：新規登録／測定項目の表示-非表示」
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    if( !BtnF08->Enabled )    return;
    if( !BtnF08->Tag ){
        //////////////
        // 新規登録
        SubAdd();
    }
    else{
        //////////////
        // 測定項目の表示／非表示
        if( Panel3->Visible == false )   SpeedButton2Click(Sender);
        else                             SpeedButton1Click(Sender);

    }
}

//---------------------------------------------------------------------------
// 「Ｆ９：修正／画面印刷」
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
    if( !BtnF09->Enabled )    return;
    if( !BtnF09->Tag ){
        //////////////
        // 修正
        SubCorrect();
    }
    else{
        //////////////
        // 画面印刷
        Form1->Print();
    }
}

//---------------------------------------------------------------------------
// 「Ｆ１０：削除／印刷」
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{

    if( !BtnF10->Enabled )    return;

    if( !BtnF10->Tag ){
        //////////////
        // 削除
        int   i,j,end,cnt;
        div_t       x;

        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        for( i=SGr1->Selection.Top; i<SGr1->RowCount; i++) {
            // グリッドを詰めます
            if( (i + cnt) >= SGr1->RowCount ){
                for( j=2; j<=28; j++) {
                    SGr1->Cells[j][i] = SGr1->Cells[j][i+cnt];
                }
            }
            else{
                for( j=2; j<=28; j++) {
                    SGr1->Cells[j][i] = SGr1->Cells[j][i+cnt];
                }
            }
        }

        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // 行をまとめて削除する
        x = div( end, 30 );
        if( ((x.quot + 2) * 30) < SGr1->RowCount ){
            SGr1->RowCount = (x.quot + 2) * 30;
        }

/*
        // 選択されている範囲をクリアーします
        end = SGr1->Row;
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++) {
            // グリッドを削除します。
            for( j=2; j<=10; j++) {
                SGr1->Cells[j][i] = "";
            }
        }

        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        x = div( SGr1->Selection.Top, 30 );
        // x.quot  商
        // x.rem   余

        if( (x.rem + cnt) > 30 ){
            // 選択範囲が複数のトレーにまたがっているとき
            y = div( SGr1->Selection.Bottom + 1, 30 );
            // y.quot  商
            // y.rem   余

            for( i=(y.quot*30), cnt=0; i<(y.quot*30+30); i++, cnt++ ) {
                // グリッドを詰めます
                if( (30 - y.rem) > cnt ){
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+y.rem];
                    }
                }
                else{
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = "";
                    }
                }
            }

            // トレーの先頭以外から選択が始まり、なおかつトレー全体が選択
            // されている場合の　データ移動（トレー毎）
            if( x.rem>0 && (y.quot-x.quot)>=2 ){
                end = (y.quot - (x.quot+1)) * 30;
                for( i=((x.quot+1)*30); i<(SGr1->RowCount-end); i++ ) {
                    // グリッドを詰めます
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                    }
                }
            }
            // 丁度、トレーの先頭より３０個以上選択した場合　データ移動（トレー毎）
            if( x.rem==0 && (y.quot-x.quot)>=1 ){
                end = (y.quot - x.quot) * 30;
                for( i=(x.quot*30); i<(SGr1->RowCount-end); i++ ) {
                    // グリッドを詰めます
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                    }
                }
            }
        }
        else if( (x.rem + cnt) < 30 ){
            // 選択範囲が一つのトレーに納まっているとき
            for( i=SGr1->Selection.Top; i<(x.quot*30+30); i++ ) {
                // グリッドを詰めます
                if( (i + cnt) < (x.quot*30+30) ){
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+cnt];
                    }
                }
                else{
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = "";
                    }
                }
            }
        }
        else{
            // 選択範囲が複数のトレーにまたがっているとき
            y = div( SGr1->Selection.Bottom + 1, 30 );
            // y.quot  商
            // y.rem   余

            // 丁度、トレーの先頭より３０個選択した場合
            end = (y.quot - x.quot) * 30;
            for( i=(x.quot*30); i<(SGr1->RowCount-end); i++ ) {
                // グリッドを詰めます
                for( j=2; j<=10; j++) {
                    SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                }
            }
        }

        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // 行をまとめて削除する
        x = div( end, 30 );
        if( ((x.quot + 2) * 30) < SGr1->RowCount ){
            SGr1->RowCount = (x.quot + 2) * 30;
        }

        SGr1->SetFocus();
        SGr1->Row = SGr1->Selection.Top;
*/
        SGr1->SetFocus();
        SGr1->Row = SGr1->Selection.Top;

        // データを変更したフラグ
        DataSave = true;

    }
    else{
        //////////////
        // 印刷
        Form5->QuickRep1->Preview();
        //Form5->QuickRep1->Print();

        keybd_event(VK_CONTROL,0,0,0);
        keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
    }
}

//---------------------------------------------------------------------------
// 「Ｆ１１：保存／ﾋｽﾄ印刷」
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
    int iPrtCnt;
    int i;
    AnsiString sBuf;


    if( !BtnF11->Enabled )    return;
    if( !BtnF11->Tag ){
        //////////////
        // 保存
        SubSave();
    }
    else{
        //////////////
        // ﾋｽﾄ印刷
        iPrtCnt = 0;
        for( i=0; i<SGr1->RowCount; i++ ){
            // ﾋｽﾄｸﾞﾗﾑ測定数
            sBuf = SGr1->Cells[28][i];
            if( sBuf.Length() > 0 ){
                if( StrToInt(sBuf) > 0 ){
                    iPrtCnt++ ;
                }
            }
        }
        if( iPrtCnt > 0 ){
            Form4->ShowModal();
            if( Form4->Tag >= 1 ){
/*
                if( Form4->RBtn1->Checked ){
                    // 手差しトレイ
                    Form3->QuickRep1->PrinterSettings->OutputBin = Tractor;
		    // First
                    // Upper
                    // Lower
                    // Middle
                    // Manual
                    // Envelope
                    // EnvManual
                    // Auto
                    // Tractor
                    // SmallFormat
                    // LargeFormat
                    // LargeCapacity
                    // Cassette
                    // Last
                }
                else{
                    // カセット
                    Form3->QuickRep1->PrinterSettings->OutputBin = Auto;
                }
*/
                Form3->QuickRep1->Print();
            }
        }
        else{
            SBr1->Panels->Items[0]->Text = "印刷するヒストデータが有りません。";
            Beep();
        }
    }
}

//---------------------------------------------------------------------------
// 「Ｆ１２：戻る」
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
    if( !BtnF12->Enabled )    return;
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    // ステータスメッセージ
    if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
    }

    if( Shift.Contains(ssCtrl) ){
        BtnF01->Caption = "ソート";
        BtnF02->Caption = "";
        BtnF03->Caption = "";
        BtnF04->Caption = "切り取り";
        BtnF05->Caption = "";
        BtnF06->Caption = "空白挿入";
        BtnF07->Caption = "";
        BtnF08->Caption = "測定項目";
        BtnF09->Caption = "画面印刷";
        BtnF10->Caption = "印刷";
        BtnF11->Caption = "ﾋｽﾄ印刷";
        BtnF12->Caption = "戻る";

        if( NotFound ){
            BtnF01->Enabled = false;
            BtnF02->Enabled = false;
            BtnF03->Enabled = false;
            BtnF04->Enabled = false;
            BtnF05->Enabled = false;
            BtnF06->Enabled = false;
            BtnF07->Enabled = false;
            BtnF08->Enabled = false;
            BtnF09->Enabled = true;
            BtnF10->Enabled = false;
            BtnF11->Enabled = false;
            BtnF12->Enabled = true;
        }
        else{
            BtnF01->Enabled = true;
            BtnF02->Enabled = false;
            BtnF03->Enabled = false;
            BtnF04->Enabled = true;
            BtnF05->Enabled = false;
            BtnF06->Enabled = true;
            BtnF07->Enabled = false;
            BtnF08->Enabled = true;
            BtnF09->Enabled = true;
            BtnF10->Enabled = true;
            BtnF11->Enabled = true;
            BtnF12->Enabled = true;
        }

        BtnF01->Tag = 1;
        BtnF02->Tag = 1;
        BtnF03->Tag = 1;
        BtnF04->Tag = 1;
        BtnF05->Tag = 1;
        BtnF06->Tag = 1;
        BtnF07->Tag = 1;
        BtnF08->Tag = 1;
        BtnF09->Tag = 1;
        BtnF10->Tag = 1;
        BtnF11->Tag = 1;
        BtnF12->Tag = 1;
    }

    switch(Key) {
        case VK_F1:  BtnF01Click(Sender);    break;
        case VK_UP:  if( SGr1->Focused() )   break;
        case VK_F2:  BtnF02Click(Sender);    break;
        case VK_DOWN:if( SGr1->Focused() )   break;
        case VK_F3:  BtnF03Click(Sender);    break;
        case VK_F4:  BtnF04Click(Sender);    break;
        case VK_F5:  BtnF05Click(Sender);    break;
        case VK_F6:  BtnF06Click(Sender);    break;
        case VK_F7:
                     // 検索部にフォーカスがある場合は、検索実行
                     if( EdtCOD->Focused() ){
                         BtnF07Click(Sender);
                     }
                     // 検索部以外にフォーカスがある場合は、検索部にセットフォーカス
                     else{
                         EdtCOD->SetFocus();
                     }
                     break;
        case VK_F8:  BtnF08Click(Sender);    break;
        case VK_F9:  BtnF09Click(Sender);    break;
        case VK_F10: BtnF10Click(Sender);
                     Key = 0;
                     break;
        case VK_F11: BtnF11Click(Sender);    break;
        case VK_F12: BtnF12Click(Sender);    break;


        // 前項
        case VK_LEFT:
                if(Edt01->Focused() && Edt01->SelStart == 0 && Edt01->SelLength == 0 ){
                    Edt08->SetFocus();
                    break;
                }
                if(Edt02->Focused() && Edt02->SelStart == 0 && Edt02->SelLength == 0 ){
                    //Edt01->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt03->Focused() && Edt03->SelStart == 0 && Edt03->SelLength == 0 ){
                    //Edt02->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt04->Focused() && Edt04->SelStart == 0 && Edt04->SelLength == 0 ){
                    //Edt03->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt05->Focused() && Edt05->SelStart == 0 && Edt05->SelLength == 0 ){
                    //Edt04->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt06->Focused() && Edt06->SelStart == 0 && Edt06->SelLength == 0 ){
                    //Edt05->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt07->Focused() && Edt07->SelStart == 0 && Edt07->SelLength == 0 ){
                    //Edt06->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt08->Focused() && Edt08->SelStart == 0 && Edt08->SelLength == 0 ){
                    //Edt07->SetFocus();
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                break;

         // 次項
         case VK_RIGHT:
                if(Edt01->Focused() && Edt01->SelStart == Edt01->Text.Length() && Edt01->SelLength == 0 ){
                    //Edt02->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt02->Focused() && Edt02->SelStart == Edt02->Text.Length() && Edt02->SelLength == 0 ){
                    //Edt03->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt03->Focused() && Edt03->SelStart == Edt03->Text.Length() && Edt03->SelLength == 0 ){
                    //Edt04->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt04->Focused() && Edt04->SelStart == Edt04->Text.Length() && Edt04->SelLength == 0 ){
                    //Edt05->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt05->Focused() && Edt05->SelStart == Edt05->Text.Length() && Edt05->SelLength == 0 ){
                    //Edt06->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt06->Focused() && Edt06->SelStart == Edt06->Text.Length() && Edt06->SelLength == 0 ){
                    //Edt07->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt07->Focused() && Edt07->SelStart == Edt07->Text.Length() && Edt07->SelLength == 0 ){
                    //Edt08->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt08->Focused() && Edt08->SelStart == Edt08->Text.Length() && Edt08->SelLength == 0 ){
                    Edt01->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:

                // 検査予定日
                if(EdtCOD->Focused()){
                    BtnF07Click(Sender);
                    break;
                }
                // 工管NO
                if(Edt01->Focused()){
                    // 工管NOを検索開始
                    if( Edt01->Text.Length() == 0 || Trim(Edt01->Text) == "0" ){
                        // 検索を実行しない
                        //Edt02->SetFocus();
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                    if( SubSearchKOKANBNG( Edt01->Text ) ){
                        // 工管NOの検索に成功の場合は、登録を行います。
                        SubAdd();
                    }
                    else{
                        // 検索に失敗
                        Edt01->SelectAll();
                    }
                    break;
                }
                if(Edt02->Focused()){
                    //Edt03->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                // 得意先品番
                if(Edt03->Focused()){
                    // 得意先品番を検索開始
                    if( Edt03->Text.Length() == 0 ){
                        //Edt02->SetFocus();
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                    SBr1->Panels->Items[0]->Text = "製品規格マスタを検索しています．．．";
                    SBr1->Update();
                    if( SubSearchTKSHIN( Edt03->Text, true, true ) ){
                        // 得意先品番の検索に成功
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        SBr1->Panels->Items[0]->Text = "";
                        SBr1->Update();
                    }
                    else{
                        // 検索に失敗
                        SBr1->Panels->Items[0]->Text = "得意先品番が見つかりません。";
                        SBr1->Update();
                        Beep();
                        Edt03->SelectAll();
                    }
                    break;
                }
                if(Edt04->Focused()){
                    //Edt05->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt05->Focused()){
                    //Edt06->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt06->Focused()){
                    //Edt07->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt07->Focused()){
                    //Edt08->SetFocus();
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if(Edt08->Focused()){
                    Edt01->SetFocus();
                    //keybd_event(VK_TAB,0,0,0);
                    //keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                break;

     }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if( Key == 17 ){
          BtnF01->Caption = "一覧検索";
          BtnF02->Caption = "前項";
          BtnF03->Caption = "次項";
          BtnF04->Caption = "コピー";
          BtnF05->Caption = "貼り付け";
          BtnF06->Caption = "挿入";
          BtnF07->Caption = "検索";
          BtnF08->Caption = "新規登録";
          BtnF09->Caption = "修正";
          BtnF10->Caption = "削除";
          BtnF11->Caption = "保存";
          BtnF12->Caption = "戻る";

          if( NotFound ){
              BtnF01->Enabled = true;
              BtnF02->Enabled = false;
              BtnF03->Enabled = false;
              BtnF04->Enabled = false;
              BtnF05->Enabled = false;
              BtnF06->Enabled = false;
              BtnF07->Enabled = true;
              BtnF08->Enabled = false;
              BtnF09->Enabled = false;
              BtnF10->Enabled = false;
              BtnF11->Enabled = false;
              BtnF12->Enabled = true;
          }
          else{
              BtnF01->Enabled = false;
              BtnF02->Enabled = true;
              BtnF03->Enabled = true;
              BtnF04->Enabled = true;
              BtnF05->Enabled = true;
              BtnF06->Enabled = true;
              BtnF07->Enabled = true;
              BtnF08->Enabled = true;
              BtnF09->Enabled = true;
              BtnF10->Enabled = true;
              BtnF11->Enabled = true;
              BtnF12->Enabled = true;
          }
          BtnF01->Tag = 0;
          BtnF02->Tag = 0;
          BtnF03->Tag = 0;
          BtnF04->Tag = 0;
          BtnF05->Tag = 0;
          BtnF06->Tag = 0;
          BtnF07->Tag = 0;
          BtnF08->Tag = 0;
          BtnF09->Tag = 0;
          BtnF10->Tag = 0;
          BtnF11->Tag = 0;
          BtnF12->Tag = 0;
      }
}


void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{

    // データを変更したかどうかのフラグチェック
    if( DataSave ){
        switch( MessageDlg( "データが編集されています。\n保存しますか？",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // 「Yes」      保存
            case mrYes:
                if( !SubSave() )   CanClose = false;

//                if( Database1->InTransaction == True )  Database1->Commit();
                break;
            // 「No」       変更を破棄
            case mrNo:
//                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // 「Cancel」   キャンセル
            case mrCancel:
                CanClose = false;
                break;
        }
    }

    // 終了時の処理
    if( CanClose ){
        // メモリの開放
        if( hMemCopy ){
            GlobalUnlock( hMemCopy );
            GlobalFree( hMemCopy );
        }
    }
/*
    else{
        if( Database1->InTransaction == True )  Database1->Commit();
    }
*/
}

//---------------------------------------------------------------------------
// 「検索」
void __fastcall TForm1::SubSearch( TObject *Sender, AnsiString sYMD )
{
     int i,j;
     int iRow,iCnt;
     AnsiString sBuf;
     div_t x;

     if( !BtnF07->Enabled )    return;

     if( sYMD.Length() < 8 ){
         SBr1->Panels->Items[0]->Text = "検査予定日を指定して下さい。";
         SBr1->Update();
         Beep();
         return;
     }

     // 画面を初期化
     for( i=0; i<SGr1->RowCount; i++) {
         for( j=2; j<=28; j++) {
             SGr1->Cells[j][i] = "";
         }
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select TOLEY_NO,SAMPLE_P,KOKBNG,DTKSCOD,DTKSHIN,LOTNO,HINBAN,ZISNAM,ZISCOD,NUM,SORTKEY,";
     sBuf = sBuf + "KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_KOYU,";
     sBuf = sBuf + "SK_MAGE,SK_MAGEG,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,SK_ZAKUT,HIST_SOKUT";
     sBuf = sBuf + " from KM01";
     sBuf = sBuf + " where KENSA_YMD like '";
     sBuf = sBuf + sYMD + "'";
     sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                        // 20160623_工場区分追加
     sBuf = sBuf + " order by TOLEY_NO,SAMPLE_P";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     NowKey = sYMD;

     iRow = 0;
     iCnt = 0;
     while( !Query1->Eof ){

          iRow = Query1->Fields->Fields[0]->AsInteger;                           // ﾄﾚｰNO
          iRow = ((iRow-1) * 30) + (Query1->Fields->Fields[1]->AsInteger - 1);   // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ

          // 行をまとめて追加する
          x = div( iRow, 30 );
          if( ((x.quot + 2) * 30) > SGr1->RowCount ){
              j=SGr1->RowCount;
              SGr1->RowCount = (x.quot + 2) * 30;
              for( i=j; i<SGr1->RowCount; i++ ){
                  x = div( i, 30 );
                  sBuf = IntToStr(x.quot + 1);
                  SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
                  sBuf = IntToStr(x.rem + 1);
                  SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
              }
          }

          // グリッドにデータをセットします。
          sBuf = Query1->Fields->Fields[2]->AsString;      // 工管NO
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;      // 得意先ｺｰﾄﾞ
          SGr1->Cells[3][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;      // 得意先品番
          SGr1->Cells[4][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;      // ロットNO
          SGr1->Cells[5][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[6]->AsString;      // 自社品番
          SGr1->Cells[6][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[7]->AsString;      // 材質名称
          SGr1->Cells[7][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[8]->AsString;      // 材質ｺｰﾄﾞ
          SGr1->Cells[8][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[9]->AsString;      // 数量
          SGr1->Cells[9][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[10]->AsString;     // ｿｰﾄｷｰ
          SGr1->Cells[10][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[11]->AsString;     // 形状区分
          SGr1->Cells[12][iRow] = sBuf;

          switch( StrToIntDef(SGr1->Cells[12][iRow],1) ){  // 形状区分
              case 1:   SGr1->Cells[13][iRow] = "小型";    break;
              case 2:   SGr1->Cells[13][iRow] = "中型";    break;
              case 3:   SGr1->Cells[13][iRow] = "大型";    break;
              case 4:   SGr1->Cells[13][iRow] = "円柱";    break;
              case 5:   SGr1->Cells[13][iRow] = "コンミ";  break;
          }

          sBuf = Query1->Fields->Fields[12]->AsString;      // 測定区分 リード線長さ
          SGr1->Cells[14][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[13]->AsString;      // 測定区分 ブラシ幅
          SGr1->Cells[15][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[14]->AsString;      // 測定区分 ブラシ幅縦押し
          SGr1->Cells[16][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[15]->AsString;      // 測定区分 リード線取り付け
          SGr1->Cells[17][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[16]->AsString;      // 測定区分 リード線引張強度
          SGr1->Cells[18][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[17]->AsString;      // 測定区分 母体比重
          SGr1->Cells[19][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[21]->AsString;      // 測定区分 HsC硬度（圧面）
          SGr1->Cells[20][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[22]->AsString;      // 測定区分 HsC硬度（側面）
          SGr1->Cells[21][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[23]->AsString;      // 測定区分 HsD硬度（圧面）
          SGr1->Cells[22][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[24]->AsString;      // 測定区分 HsD硬度（側面）
          SGr1->Cells[23][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[18]->AsString;      // 測定区分 固有抵抗率
          SGr1->Cells[24][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[19]->AsString;      // 測定区分 曲げ強さ
          SGr1->Cells[25][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[20]->AsString;      // 測定区分 曲げ強さ現物
          SGr1->Cells[26][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[25]->AsString;      // 測定区分 座屈
          SGr1->Cells[27][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[26]->AsString;      // ﾋｽﾄｸﾞﾗﾑ測定数
          SGr1->Cells[28][iRow] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[26]->AsString;      // ﾋｽﾄｸﾞﾗﾑ測定数
          SGr1->Cells[11][iRow] = sBuf;


          // カーソルを次にセットする
          Query1->Next();
          iCnt++;
     }

     // １行目を選択
     SGr1->Row = 0;
     SGr1SelectCell( Sender, 1, 0, true);

//     SGr1->SetFocus();

     /*
     // 新しいトランザクションを開始
     if( Database1->InTransaction == false ){
         Database1->StartTransaction();
         DataSave = false;
     }
     */

     keybd_event(VK_TAB,0,0,0);
     keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);

     // ボタンの初期化
     BtnF01->Enabled = true;
     BtnF02->Enabled = true;
     BtnF03->Enabled = true;
     BtnF04->Enabled = true;
     BtnF05->Enabled = true;
     BtnF06->Enabled = true;
     BtnF07->Enabled = true;
     BtnF08->Enabled = true;
     BtnF09->Enabled = true;
     BtnF10->Enabled = true;
     BtnF11->Enabled = true;
     BtnF12->Enabled = true;

     NotFound = false;

     // ステータスメッセージ
     if( iCnt == 0 ){
         sBuf = "新規登録を行ってください。";
     }
     else{
         sBuf = FormatFloat( "検索結果 0件です。", iCnt );
     }
     SBr1->Panels->Items[0]->Text = sBuf;
     SBr1->Update();


}


//---------------------------------------------------------------------------
// 「新規登録」
void __fastcall TForm1::SubAdd()
{
     int         i,j,end;
     AnsiString  sBuf;
     div_t       x;
     bool        flag;


     if( Edt03->Text == "" ){
         // ステータスメッセージ
         SBr1->Panels->Items[0]->Text = "必須項目を入力して下さい。";
         SBr1->Update();
         Beep();
         return;
     }

     // 得意先品番を検索します
     if( SubSearchTKSHIN(Edt03->Text,false,false) == false ){
         SBr1->Panels->Items[0]->Text = "得意先品番に該当する製品規格マスタが見つかりません。";
         SBr1->Update();
         Edt03->SelectAll();
         Beep();
         return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新規登録中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // 最終のデータ行を探す
     end = 0;
     flag = false;
     for( i=0; i<SGr1->RowCount; i++ ){
         sBuf = Trim(SGr1->Cells[4][i]);
         if( sBuf.Length() == 0 && flag == false ){
             flag = true;
         }
         if( sBuf.Length() > 0 ){
             end = i;
         }
     }
     SGr1->Tag = SGr1->Row;      // カーソルの有る行にデータ追加

     // グリッドにデータをセットします。
     sBuf = Edt01->Text;                               // 工管NO
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[2][SGr1->Tag] = sBuf;

     sBuf = Edt02->Text;                               // 得意先ｺｰﾄﾞ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[3][SGr1->Tag] = sBuf;

     sBuf = Edt03->Text;                               // 得意先品番
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[4][SGr1->Tag] = sBuf;

     sBuf = Edt04->Text;                               // ロットNO
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[5][SGr1->Tag] = sBuf;

     sBuf = Edt05->Text;                               // 自社品番
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[6][SGr1->Tag] = sBuf;

     sBuf = Edt06->Text;                               // 材質名称
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[7][SGr1->Tag] = sBuf;

     sBuf = Edt07->Text;                               // 材質ｺｰﾄﾞ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[8][SGr1->Tag] = sBuf;

     sBuf = Edt08->Text;                               // 数量
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[9][SGr1->Tag] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

     sBuf = sSortKey;                                  // ｿｰﾄｷｰ
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[10][SGr1->Tag] = sBuf;

     sBuf = Edt13->Tag;                                // 形状区分
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[12][SGr1->Tag] = sBuf;

     sBuf = Edt13->Text;                               // 形状区分
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[13][SGr1->Tag] = sBuf;

     sBuf = Edt14->Text;                               // 測定区分 リード線長さ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[14][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt15->Text;                               // 測定区分 ブラシ幅
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[15][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt16->Text;                               // 測定区分 ブラシ幅縦押し
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[16][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt17->Text;                               // 測定区分 リード線取り付け
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[17][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt18->Text;                               // 測定区分 リード線引張強度
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[18][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt19->Text;                               // 測定区分 母体比重
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[19][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt20->Text;                               // 測定区分 固有抵抗率
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[20][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt21->Text;                               // 測定区分 曲げ強さ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[21][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt22->Text;                               // 測定区分 曲げ強さ現物
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[22][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt23->Text;                               // 測定区分 HsC硬度（側面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[23][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt24->Text;                               // 測定区分 HsC硬度（圧面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[24][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt25->Text;                               // 測定区分 HsD硬度（側面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[25][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt26->Text;                               // 測定区分 HsD硬度（圧面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[26][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt27->Text;                               // 測定区分 座屈
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[27][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt28->Text;                               // ﾋｽﾄｸﾞﾗﾑ測定数
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[28][SGr1->Tag] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

     sBuf = sHistSokut;                                // ﾋｽﾄｸﾞﾗﾑ測定数
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[11][SGr1->Tag] = sBuf;

     // 一行増やす
     if( (SGr1->Tag + 1) > end )   end = SGr1->Tag + 1;

     // 行をまとめて追加する
     x = div( end, 30 );
     if( ((x.quot + 2) * 30) > SGr1->RowCount ){
         j=SGr1->RowCount;
         SGr1->RowCount = (x.quot + 2) * 30;
         for( i=j; i<SGr1->RowCount; i++ ){
             x = div( i, 30 );
             sBuf = IntToStr(x.quot + 1);
             SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ﾄﾚｰNO
             sBuf = IntToStr(x.rem + 1);
             SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
         }
     }

     // 新しい行を選択
     SGr1->Row = SGr1->Tag + 1;

     Edt01->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;
}


//---------------------------------------------------------------------------
// 「修正」
void __fastcall TForm1::SubCorrect()
{
     AnsiString sBuf;

     if( SGr1->Cells[4][SGr1->Row] == "" ){
         // ステータスメッセージ
         SBr1->Panels->Items[0]->Text = "修正対象ではありません。";
         SBr1->Update();
         Beep();
         return;
     }

     // 得意先品番を検索します
     if( SubSearchTKSHIN(Edt03->Text,false,false) == false ){
         SBr1->Panels->Items[0]->Text = "得意先品番が見つかりません。";
         SBr1->Update();
         Edt03->SelectAll();
         Beep();
         return;
     }

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "修正中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // グリッドにデータをセットします。
     sBuf = Edt01->Text;                               // 工管NO
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = Edt02->Text;                               // 得意先ｺｰﾄﾞ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[3][SGr1->Row] = sBuf;

     sBuf = Edt03->Text;                               // 得意先品番
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[4][SGr1->Row] = sBuf;

     sBuf = Edt04->Text;                               // ロットNO
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[5][SGr1->Row] = sBuf;

     sBuf = Edt05->Text;                               // 自社品番
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[6][SGr1->Row] = sBuf;

     sBuf = Edt06->Text;                               // 材質名称
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[7][SGr1->Row] = sBuf;

     sBuf = Edt07->Text;                               // 材質ｺｰﾄﾞ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[8][SGr1->Row] = sBuf;

     sBuf = Edt08->Text;                               // 数量
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[9][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

     sBuf = sSortKey;                                  // ｿｰﾄｷｰ
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[10][SGr1->Row] = sBuf;

     sBuf = Edt13->Tag;                                // 形状区分
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[12][SGr1->Row] = sBuf;

     sBuf = Edt13->Text;                               // 形状区分
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[13][SGr1->Row] = sBuf;

     sBuf = Edt14->Text;                               // 測定区分 リード線長さ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[14][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt15->Text;                               // 測定区分 ブラシ幅
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[15][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt16->Text;                               // 測定区分 ブラシ幅縦押し
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[16][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt17->Text;                               // 測定区分 リード線取り付け
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[17][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt18->Text;                               // 測定区分 リード線引張強度
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[18][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt19->Text;                               // 測定区分 母体比重
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[19][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt20->Text;                               // 測定区分 固有抵抗率
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[20][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt21->Text;                               // 測定区分 曲げ強さ
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[21][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt22->Text;                               // 測定区分 曲げ強さ現物
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[22][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt23->Text;                               // 測定区分 HsC硬度（側面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[23][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt24->Text;                               // 測定区分 HsC硬度（圧面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[24][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt25->Text;                               // 測定区分 HsD硬度（側面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[25][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt26->Text;                               // 測定区分 HsD硬度（圧面）
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[26][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt27->Text;                               // 測定区分 座屈
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[27][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt28->Text;                               // ﾋｽﾄｸﾞﾗﾑ測定数
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[28][SGr1->Row] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

     sBuf = sHistSokut;                                // ﾋｽﾄｸﾞﾗﾑ測定数
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[11][SGr1->Row] = sBuf;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを変更したフラグ
     DataSave = true;

}


//---------------------------------------------------------------------------
// 「保存」
bool __fastcall TForm1::SubSave()
{
     int        i;
     int        iDataCount;
     bool       bUpdate;
     AnsiString sBuf;
     AnsiString sDummyDate;

     // ステータスメッセージ
     ProgressBar1->Visible = true;
     SBr1->Panels->Items[0]->Text = "保存前のデータチェック中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     ProgressBar1->Position = 0;
     ProgressBar1->Min = 0;
     // 保存するデータ数を求めます
     iDataCount = 0;
     for( i=0; i<SGr1->RowCount; i++ ){
         if( SGr1->Cells[4][i] != "" ) iDataCount++ ;
     }
     ProgressBar1->Max = iDataCount;


     // 同じ日付のレコードが存在するかどうか問合せ実行
     sBuf = "select TOLEY_NO from KM01";
     sBuf = sBuf + " where KENSA_YMD like '" + NowKey + "'";
     sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                        // 20160623_工場区分追加
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     bUpdate = false;
     if( !Query1->Eof ){
         // 同じレコードがあった場合

         // 処理続行前の確認
         sBuf =        "既に作成された検査指示データを修正しようとしています。\n";
         sBuf = sBuf + "この検査指示の測定済みデータは、そのまま引き継がれます。\n";
         sBuf = sBuf + "※但し、現在、他のコンピュータでこの検査指示を測定中の場合は、\n";
         sBuf = sBuf + "　ただちに終了（測定画面を閉じる）して下さい。\n\n";
         sBuf = sBuf + "「検査指示データの再作成」と「測定済みデータの再配置」を開始します。\n";
         sBuf = sBuf + "よろしいですか？";
         switch( MessageDlg( sBuf, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) ){
             // 「Yes」      処理続行
             case mrYes:
                 break;
             // 「No」       処理中断
             case mrNo:
                 SBr1->Panels->Items[0]->Text = "処理を中断しました。";
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 return(true);
                 break;
         }

         bUpdate = true;

         // 最大の日付＋１を取得します。
         // Query1->Close();              // Initial Query
         // Query1->SQL->Clear();         // Initial Query
         // sBuf = "select max(KENSA_YMD) as KENSA_YMD_MAX from KM01";
         // Query1->SQL->Add(sBuf);
         // ClpBrd = Clipboard();
         // ClpBrd->Open();
         // ClpBrd->SetTextBuf(sBuf.c_str());
         // ClpBrd->Close();
         // Query1->Open();
         // Query1->Active = true;
         //
         // if( !Query1->Eof ){
         //     sBuf = Query1->Fields->Fields[0]->AsString;      // 最大日付
         //     TDateTime dtDate = StrToDate(sBuf);
         //     dtDate++;                                        // 最大日付＋１
         //     sDummyDate = FormatDateTime("yyyy/mm/dd",dtDate.FormatString("YYYY/MM/DD"));
         // }
         // else{
         //     sDummyDate = "40000101";
         // }
         sDummyDate = "40000101";

         // 「検査指示データ修正の為のKM01,KD01,KD02〜KDA1,KDA2をコピーします」
         // if( SubCopyKM01( NowKey, sDummyDate) = false ) return(false);

         // 同じ日付のレコードが存在するかどうか問合せ実行
         Query1->Close();              // Initial Query
         Query1->SQL->Clear();         // Initial Query
         sBuf = "select TOLEY_NO from KM01 where KENSA_YMD='" + sDummyDate + "'";
         sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                    // 20160623_工場区分追加
         Query1->SQL->Add(sBuf);
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->Open();
         Query1->Active = true;
         if( !Query1->Eof ){
             // レコード削除の実行
             Query1->Close();              // Initial Query
             Query1->SQL->Clear();         // Initial Query
             sBuf = "delete from KM01 where KENSA_YMD='" + sDummyDate + "'";
             sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                // 20160623_工場区分追加
             Query1->SQL->Add(sBuf);
             try {
                 ClpBrd = Clipboard();
                 ClpBrd->Open();
                 ClpBrd->SetTextBuf(sBuf.c_str());
                 ClpBrd->Close();
                 Query1->ExecSQL();
             } catch(EDatabaseError& e) {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 Beep();
                 return(false);
             } catch(Exception& e) {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 Beep();
                 return(false);
             }
         }
     }

     // ステータスメッセージ
     ProgressBar1->Visible = true;
     SBr1->Panels->Items[0]->Text = "検査指示データの保存中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // グリッドのデータをＤＢに追加します
     for( i=0; i<SGr1->RowCount; i++ ){

         // 得意先品番が存在するフィールドのみ追加
         if( SGr1->Cells[4][i] != "" ){

             // Initial Query
             Query1->Close();
             Query1->SQL->Clear();

             // 問合せ文作成
             sBuf = "insert into KM01(KENSA_YMD,TOLEY_NO,SAMPLE_P,KOKBNG,DTKSCOD,DTKSHIN,LOTNO,";
             sBuf = sBuf + "HINBAN,ZISNAM,ZISCOD,NUM,SORTKEY,KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,";
             sBuf = sBuf + "SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_KOYU,SK_MAGE,SK_MAGEG,SK_HSC_A,SK_HSC_S,";
             sBuf = sBuf + "SK_HSD_A,SK_HSD_S,SK_ZAKUT,HIST_SOKUT,UPDYMD,UPDTIM,UPDCHR,KOJOKBN)"; // 20160623_工場区分追加
             sBuf = sBuf + " values('";
             if( bUpdate == true ){
             // データ更新の時は、ダミーの日付で書き込みます。
                 sBuf = sBuf + sDummyDate           + "'," ;    // 検査予定日
             } else {
                 sBuf = sBuf + NowKey               + "'," ;    // 検査予定日
             }
             sBuf = sBuf + SGr1->Cells[0][i]        +  "," ;    // ﾄﾚｰNO
             sBuf = sBuf + SGr1->Cells[1][i]        +  "," ;    // ｻﾝﾌﾟﾙﾎﾟｼﾞｼｮﾝ
             sBuf = sBuf + SGr1->Cells[2][i]        +  ",'";    // 工管NO
             sBuf = sBuf + Trim(SGr1->Cells[3][i])  + "','";    // 得意先ｺｰﾄﾞ
             sBuf = sBuf + SGr1->Cells[4][i]        + "','";    // 得意先品番
             sBuf = sBuf + SGr1->Cells[5][i]        + "','";    // ロットNO
             sBuf = sBuf + SGr1->Cells[6][i]        + "','";    // 自社品番
             sBuf = sBuf + SGr1->Cells[7][i]        + "','";    // 材質名称
             sBuf = sBuf + SGr1->Cells[8][i]        + "'," ;    // 材質ｺｰﾄﾞ
             sBuf = sBuf + Trim(SGr1->Cells[9][i])  +  "," ;    // 数量
             sBuf = sBuf + Trim(SGr1->Cells[10][i]) +  "," ;    // ｿｰﾄｷｰ
             sBuf = sBuf + Trim(SGr1->Cells[12][i]) +  "," ;    // 形状区分
             sBuf = sBuf + Trim(SGr1->Cells[14][i]) +  "," ;    // 測定区分 リード線長さ
             sBuf = sBuf + Trim(SGr1->Cells[15][i]) +  "," ;    // 測定区分 ブラシ幅
             sBuf = sBuf + Trim(SGr1->Cells[16][i]) +  "," ;    // 測定区分 ブラシ幅縦押し
             sBuf = sBuf + Trim(SGr1->Cells[17][i]) +  "," ;    // 測定区分 リード線取り付け抵抗
             sBuf = sBuf + Trim(SGr1->Cells[18][i]) +  "," ;    // 測定区分 リード線引張強度
             sBuf = sBuf + Trim(SGr1->Cells[19][i]) +  "," ;    // 測定区分 母体比重
             sBuf = sBuf + Trim(SGr1->Cells[24][i]) +  "," ;    // 測定区分 固有抵抗率
             sBuf = sBuf + Trim(SGr1->Cells[25][i]) +  "," ;    // 測定区分 曲げ強さ
             sBuf = sBuf + Trim(SGr1->Cells[26][i]) +  "," ;    // 測定区分 曲げ強さ現物
             sBuf = sBuf + Trim(SGr1->Cells[20][i]) +  "," ;    // 測定区分 HsC硬度（圧面）
             sBuf = sBuf + Trim(SGr1->Cells[21][i]) +  "," ;    // 測定区分 HsC硬度（側面）
             sBuf = sBuf + Trim(SGr1->Cells[22][i]) +  "," ;    // 測定区分 HsD硬度（圧面）
             sBuf = sBuf + Trim(SGr1->Cells[23][i]) +  "," ;    // 測定区分 HsD硬度（側面）
             sBuf = sBuf + Trim(SGr1->Cells[27][i]) +  "," ;    // 測定区分 座屈
             sBuf = sBuf + Trim(SGr1->Cells[28][i]) +  ",'";    // ﾋｽﾄｸﾞﾗﾑ測定数
             sBuf = sBuf + FormatDateTime("yyyymmdd",Date())               + "','";    // 変更日
             sBuf = sBuf + FormatDateTime("hhmm",TDateTime::CurrentTime()) + "'," ;    // 変更時間

             //sBuf = sBuf + IntToStr(USER_COD)                              + ")" ;    // 更新者
             sBuf = sBuf + IntToStr(USER_COD)                              + "," ;    // 更新者
             sBuf = sBuf + IntToStr(iKojoKbn)                               + ")" ;    // 工場区分

             Query1->SQL->Add(sBuf);

             // 問い合せ文の実行
             try {
                 ClpBrd = Clipboard();
                 ClpBrd->Open();
                 ClpBrd->SetTextBuf(sBuf.c_str());
                 ClpBrd->Close();
                 Query1->ExecSQL();
             } catch(EDatabaseError& e) {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 Beep();
                 return(false);
             } catch(Exception& e) {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 Beep();
                 return(false);
             }

             ProgressBar1->Position++;

             // コミット
/*
             sBuf = "commit";
             Query1->SQL->Add(sBuf);

             try
             {
                 Query1->ExecSQL();
             }
             catch(EDatabaseError& e)
             {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 return;
             }
             catch(Exception& e)
             {
                 SBr1->Panels->Items[0]->Text = e.Message;
                 SBr1->Update();
                 return;
             }
*/
         }
     }

     // データ修正の場合
     if( bUpdate == true ){

         // 「修正前の測定データ（修正前の日付側から）を検査指示データ修正後（ダミー日付側へ）
         //   のKM01,KD01,KD02〜KDA1,KDA2に設定します」
         if( SubSetOldValue( NowKey, sDummyDate) == false ){
             ProgressBar1->Visible = false;
             return(false);
         }

         // 「ダミー日付で完成した検査指示データ（KD01〜KA02を含む）を本来の測定日へUpdateします」
         if( SubMoveKM01( NowKey, sDummyDate) == false ){
             ProgressBar1->Visible = false;
             return(false);
         }
     }

     ProgressBar1->Visible = false;
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // データを保存したフラグ
     DataSave = false;

     return(true);
}


//---------------------------------------------------------------------------
// 「修正前の測定データ（修正前の日付側から）を検査指示データ修正後（ダミー日付側へ）
//   のKM01,KD01,KD02〜KDA1,KDA2に設定します」
bool __fastcall TForm1::SubSetOldValue(AnsiString sYMD, AnsiString sYMD_DMY)
{

     int        i;
     int 	iTOLEY_NO;
     int        iSAMPLE_P;
     int        iHIST_SOKUT;
     int        iSEQ_NO;
     int        iSOKUT_SJ1;
     int        iSOKUT_SJ2;
     int        iBuf;
     AnsiString sDTKSHIN;
     AnsiString sLOTNO;
     AnsiString sTableName1;
     AnsiString sTableName2;
     AnsiString sGetField;
     AnsiString sBuf;


     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "測定済みデータの再配置中です．．．しばらくお待ち下さい。";
     ProgressBar1->Min = 0;
     ProgressBar1->Max = ProgressBar1->Max * 10;
     ProgressBar1->Position = 0;
     SBr1->Update();

     // 新しい検査指示データを一行づつループし、古い検査指示データから測定値をコピーします。
     Query1->Close();              // Initial Query
     Query1->SQL->Clear();         // Initial Query
     sBuf = "select TOLEY_NO,SAMPLE_P,DTKSHIN,LOTNO,SK_LD_LNG,SK_BURASI,SK_BURASIT,";
     sBuf = sBuf + "SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,";
     sBuf = sBuf + "SK_KOYU,SK_MAGE,SK_MAGEG,SK_ZAKUT,HIST_SOKUT";
     sBuf = sBuf + " from KM01";
     sBuf = sBuf + " where KENSA_YMD like '" + sYMD_DMY + "'";
     sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                       // 20160623_工場区分追加
     sBuf = sBuf + " order by TOLEY_NO,SAMPLE_P";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     iSEQ_NO = 0;

     while( !Query1->Eof ){

          // 新しい検査指示データの情報を取得します。
          iTOLEY_NO   = Query1->Fields->Fields[0]->AsInteger;     // トレーNO
          iSAMPLE_P   = Query1->Fields->Fields[1]->AsInteger;     // サンプリングポジション
          sDTKSHIN    = Query1->Fields->Fields[2]->AsString;      // 得意先品番
          sLOTNO      = Query1->Fields->Fields[3]->AsString;      // ロットNO
          iHIST_SOKUT = Query1->Fields->Fields[18]->AsInteger;    // ヒストグラム測定数
          if( iHIST_SOKUT > 0 ){
              iSEQ_NO ++ ;
          }

          // KD01〜KDA1,KDC1までをループし各測定値を複写します。
          for( i=0; i<=11; i++ ){
              ProgressBar1->Position++;
              switch(i){
                  case  0: // リード線長さ寸法
                           sTableName1 = "KD01";
                           sTableName2 = "KD02";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[4]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  1: // ブラシ幅寸法
                           sTableName1 = "KD11";
                           sTableName2 = "KD12";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[5]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  2: // ブラシ幅寸法縦押し
                           sTableName1 = "KD21";
                           sTableName2 = "KD22";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[6]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  3: // リード線取付抵抗
                           sTableName1 = "KD31";
                           sTableName2 = "KD32";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1V,SOKUTEI_2V,SOKUTEI_1A,SOKUTEI_2A";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[7]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  4: // リード線引張強度
                           sTableName1 = "KD41";
                           sTableName2 = "KD42";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[8]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  5: // 母体比重
                           sTableName1 = "KD51";
                           sTableName2 = "KD52";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1S,SOKUTEI_2S,SOKUTEI_1H,SOKUTEI_2H";
                           sGetField = sGetField + ",SOKUTEI_1N,SOKUTEI_2N,SOKUTEI_1J,SOKUTEI_2J";
                           sGetField = sGetField + ",SOKUTEI_1B,SOKUTEI_2B,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[9]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  6: // 硬度
                           sTableName1 = "KD61";
                           sTableName2 = "KD62";
                           sGetField = ",HSC_SK_SU,HSD_SK_SU";
                           sGetField = sGetField + ",HSC_A_1,HSC_S_1,HSC_A_2,HSC_S_2";
                           sGetField = sGetField + ",HSC_A_AVE,HSC_S_AVE";
                           sGetField = sGetField + ",HSD_A_1,HSD_S_1,HSD_A_2,HSD_S_2";
                           sGetField = sGetField + ",HSD_A_AVE,HSD_S_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[10]->AsInteger;
                           iBuf       = Query1->Fields->Fields[11]->AsInteger;
                           if( iSOKUT_SJ1 > 0 )   iSOKUT_SJ1 = iSOKUT_SJ1;
                           else if( iBuf > 0 )    iSOKUT_SJ1 = iBuf;
                           else                   iSOKUT_SJ1 = 0;
                           iSOKUT_SJ2 = Query1->Fields->Fields[12]->AsInteger;
                           iBuf       = Query1->Fields->Fields[13]->AsInteger;
                           if( iSOKUT_SJ2 > 0 )   iSOKUT_SJ2 = iSOKUT_SJ2;
                           else if( iBuf > 0 )    iSOKUT_SJ2 = iBuf;
                           else                   iSOKUT_SJ2 = 0;
                           break;
                  case  7: // 固有抵抗率
                           sTableName1 = "KD71";
                           sTableName2 = "KD72";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1S,SOKUTEI_2S,SOKUTEI_1H,SOKUTEI_2H";
                           sGetField = sGetField + ",SOKUTEV_1R,SOKUTEV_2R,SOKUTEV_1L,SOKUTEV_2L";
                           sGetField = sGetField + ",SOKUTEA_1R,SOKUTEA_2R,SOKUTEA_1L,SOKUTEA_2L";
                           sGetField = sGetField + ",SOKUTEI_1P,SOKUTEI_2P,SOKUTEI_1T,SOKUTEI_2T";
                           sGetField = sGetField + ",SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[14]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  8: // 抗折力
                           sTableName1 = "KD81";
                           sTableName2 = "KD82";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1S,SOKUTEI_2S,SOKUTEI_1H,SOKUTEI_2H";
                           sGetField = sGetField + ",SOKUTEI_1K,SOKUTEI_2K,SOKUTEI_1P,SOKUTEI_2P";
                           sGetField = sGetField + ",SOKUTEI_1M,SOKUTEI_2M,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[15]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  9: // 座屈
                           sTableName1 = "KD91";
                           sTableName2 = "KD92";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[17]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case 10: // ヒストグラム
                           sTableName1 = "KDA1";
                           sTableName2 = "KDA2";
                           sGetField = ",SOKUTE_SU";
                           sGetField = sGetField + ",SOKUTE_KET,SOKUTE_AVE,SOKUTE_MIN,SOKUTE_MAX";
                           sGetField = sGetField + ",SOKUTE_R,SOKUTE_SGM,SOKUTE_CP,SOKUTE_CPK";
                           sGetField = sGetField + ",SOKUTE_K,SOKUTE_P";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[18]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case 11: // 抗折力（現物）
                           sTableName1 = "KDC1";
                           sTableName2 = "KDC2";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1S,SOKUTEI_2S,SOKUTEI_1H,SOKUTEI_2H";
                           sGetField = sGetField + ",SOKUTEI_1K,SOKUTEI_2K,SOKUTEI_1P,SOKUTEI_2P";
                           sGetField = sGetField + ",SOKUTEI_1M,SOKUTEI_2M,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[16]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
              }

              // 古い検査指示データを取得します。
              Query2->Close();              // Initial Query
              Query2->SQL->Clear();         // Initial Query
              if( i == 10 ){
                  sBuf = "select KENSA_YMD,SEQNO";
              } else {
                  sBuf = "select TOLEY_NO,SAMPLE_P";
              }
              sBuf = sBuf + sGetField;
              sBuf = sBuf + " from " + sTableName1;
              sBuf = sBuf + " where KENSA_YMD='" + sYMD + "'";
              sBuf = sBuf + " and DTKSHIN='" + sDTKSHIN + "'";
              sBuf = sBuf + " and LOTNO='" + sLOTNO + "'";
              //test
              sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                        // 20160623_工場区分追加

              if( i == 10 ){
                  sBuf = sBuf + " order by SEQNO";
              } else {
                  sBuf = sBuf + " order by TOLEY_NO,SAMPLE_P";
              }
              Query2->SQL->Add(sBuf);
              ClpBrd = Clipboard();
              ClpBrd->Open();
              ClpBrd->SetTextBuf(sBuf.c_str());
              ClpBrd->Close();
              try {
                  Query2->Open();
                  Query2->Active = true;
              } catch(EDatabaseError& e) {
                  SBr1->Panels->Items[0]->Text = e.Message;
                  SBr1->Update();
                  ProgressBar1->Visible = false;
                  Beep();
                  return(false);
              } catch(Exception& e) {
                  SBr1->Panels->Items[0]->Text = e.Message;
                  SBr1->Update();
                  ProgressBar1->Visible = false;
                  Beep();
                  return(false);
              }

              while( !Query2->Eof ){

                  // 測定済みの場合は、測定値を新しい測定データに複写します。
                  if( (iSOKUT_SJ1 > 0 && Query2->Fields->Fields[2]->AsInteger > 0 && i != 6 ) ||
                      ((iSOKUT_SJ1 > 0 || iSOKUT_SJ2 > 0 ||
                        Query2->Fields->Fields[2]->AsInteger > 0 ||
                        Query2->Fields->Fields[3]->AsInteger > 0 ) && i == 6 ) ){     // 測定数で判断します

                      // 問い合せ文の実行
                      Query3->Close();              // Initial Query
                      Query3->SQL->Clear();         // Initial Query
                      sBuf = "UPDATE " + sTableName1;
                      switch(i){
                          case  0: // リード線長さ寸法
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[6]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[7]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[8]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[9]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[12]->AsString + "'";
                                   break;
                          case  1: // ブラシ幅寸法
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[6]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[7]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[8]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[9]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[12]->AsString + "'";
                                   break;
                          case  2: // ブラシ幅寸法縦押し
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[6]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[7]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[8]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[9]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[12]->AsString + "'";
                                   break;
                          case  3: // リード線取付抵抗
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1V=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2V=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1A=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2A=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[10]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[11]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[12]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[13]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[14]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[15]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[16]->AsString + "'";
                                   break;
                          case  4: // リード線引張強度
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[6]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[7]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[8]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[9]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[12]->AsString + "'";
                                   break;
                          case  5: // 母体比重
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1S=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2S=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1H=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2H=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1N=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2N=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1J=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2J=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1B=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2B=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[13]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[14]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[15]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[16]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[17]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[18]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[19]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[20]->AsString + "'";
                                   break;
                          case  6: // 硬度
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET HSC_SK_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET HSC_SK_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   if( iSOKUT_SJ2 >= Query2->Fields->Fields[3]->AsInteger ){
                                      sBuf = sBuf + ",HSD_SK_SU=" + IntToStr(Query2->Fields->Fields[3]->AsInteger);
                                   } else{
                                      sBuf = sBuf + ",HSD_SK_SU=" + IntToStr(iSOKUT_SJ2);
                                   }
#if 1   // 2011.06.02 Y.Sano Mod start
                                   sBuf = sBuf + ",HSC_A_1=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",HSC_S_1=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",HSC_A_2=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",HSC_S_2=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
#else   // 2011.06.02 Y.Sano Mod start
                                   sBuf = sBuf + ",HSC_A_1=" + IntToStr(Query2->Fields->Fields[4]->AsInteger);
                                   sBuf = sBuf + ",HSC_S_1=" + IntToStr(Query2->Fields->Fields[5]->AsInteger);
                                   sBuf = sBuf + ",HSC_A_2=" + IntToStr(Query2->Fields->Fields[6]->AsInteger);
                                   sBuf = sBuf + ",HSC_S_2=" + IntToStr(Query2->Fields->Fields[7]->AsInteger);
#endif  // 2011.06.02 Y.Sano Mod end
                                   sBuf = sBuf + ",HSC_A_AVE=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",HSC_S_AVE=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
#if 1   // 2011.06.02 Y.Sano Mod start
                                   sBuf = sBuf + ",HSD_A_1=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",HSD_S_1=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",HSD_A_2=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",HSD_S_2=" + FloatToStr(Query2->Fields->Fields[13]->AsFloat);
#else   // 2011.06.02 Y.Sano Mod start
                                   sBuf = sBuf + ",HSD_A_1=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",HSD_S_1=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",HSD_A_2=" + IntToStr(Query2->Fields->Fields[12]->AsInteger);
                                   sBuf = sBuf + ",HSD_S_2=" + IntToStr(Query2->Fields->Fields[13]->AsInteger);
#endif  // 2011.06.02 Y.Sano Mod end
                                   sBuf = sBuf + ",HSD_A_AVE=" + FloatToStr(Query2->Fields->Fields[14]->AsFloat);
                                   sBuf = sBuf + ",HSD_S_AVE=" + FloatToStr(Query2->Fields->Fields[15]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[16]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[17]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[18]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[19]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[20]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[21]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[22]->AsString + "'";
                                   break;
                          case  7: // 固有抵抗率
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1S=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2S=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1H=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2H=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEV_1R=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEV_2R=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEV_1L=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEV_2L=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEA_1R=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEA_2R=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEA_1L=" + FloatToStr(Query2->Fields->Fields[13]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEA_2L=" + FloatToStr(Query2->Fields->Fields[14]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1P=" + IntToStr(Query2->Fields->Fields[15]->AsInteger);
                                   sBuf = sBuf + ",SOKUTEI_2P=" + IntToStr(Query2->Fields->Fields[16]->AsInteger);
                                   sBuf = sBuf + ",SOKUTEI_1T=" + IntToStr(Query2->Fields->Fields[17]->AsInteger);
                                   sBuf = sBuf + ",SOKUTEI_2T=" + IntToStr(Query2->Fields->Fields[18]->AsInteger);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[19]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[20]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[21]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[22]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[23]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[24]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[25]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[26]->AsString + "'";
                                   break;
                          case  8: // 抗折力
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1S=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2S=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1H=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2H=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1K=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2K=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1P=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2P=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1M=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2M=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[13]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[14]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[15]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[16]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[17]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[18]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[19]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[20]->AsString + "'";
                                   break;
                          case  9: // 座屈
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1=" + IntToStr(Query2->Fields->Fields[3]->AsInteger);
                                   sBuf = sBuf + ",SOKUTEI_2=" + IntToStr(Query2->Fields->Fields[4]->AsInteger);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[6]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[7]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[8]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[9]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[10]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[11]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[12]->AsString + "'";
                                   break;
                          case 10: // ヒストグラム
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTE_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTE_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTE_KET=" + IntToStr(Query2->Fields->Fields[3]->AsInteger);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_MIN=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_MAX=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_R=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_SGM=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_CP=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_CPK=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_K=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_P=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[13]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[14]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[15]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[16]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[17]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[18]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[19]->AsString + "'";
                                   break;
                          case 11: // 抗折力（現物）
                                   if( iSOKUT_SJ1 >= Query2->Fields->Fields[2]->AsInteger ){
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(Query2->Fields->Fields[2]->AsInteger);
                                   } else{
                                      sBuf = sBuf + " SET SOKUTEI_SU=" + IntToStr(iSOKUT_SJ1);
                                   }
                                   sBuf = sBuf + ",SOKUTEI_1S=" + FloatToStr(Query2->Fields->Fields[3]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2S=" + FloatToStr(Query2->Fields->Fields[4]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1H=" + FloatToStr(Query2->Fields->Fields[5]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2H=" + FloatToStr(Query2->Fields->Fields[6]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1K=" + FloatToStr(Query2->Fields->Fields[7]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2K=" + FloatToStr(Query2->Fields->Fields[8]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1P=" + FloatToStr(Query2->Fields->Fields[9]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2P=" + FloatToStr(Query2->Fields->Fields[10]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_1M=" + FloatToStr(Query2->Fields->Fields[11]->AsFloat);
                                   sBuf = sBuf + ",SOKUTEI_2M=" + FloatToStr(Query2->Fields->Fields[12]->AsFloat);
                                   sBuf = sBuf + ",SOKUTE_AVE=" + FloatToStr(Query2->Fields->Fields[13]->AsFloat);
                                   sBuf = sBuf + ",ADDYMD='" + Query2->Fields->Fields[14]->AsString + "'";
                                   sBuf = sBuf + ",ADDTIM='" + Query2->Fields->Fields[15]->AsString + "'";
                                   sBuf = sBuf + ",UPDYMD='" + Query2->Fields->Fields[16]->AsString + "'";
                                   sBuf = sBuf + ",UPDTIM='" + Query2->Fields->Fields[17]->AsString + "'";
                                   sBuf = sBuf + ",UPDCHR=" + IntToStr(Query2->Fields->Fields[18]->AsInteger);
                                   sBuf = sBuf + ",UPDCNT=" + IntToStr(Query2->Fields->Fields[19]->AsInteger);
                                   sBuf = sBuf + ",MEMO='" + Query2->Fields->Fields[20]->AsString + "'";
                                   break;
                      }

                      sBuf = sBuf + " WHERE KENSA_YMD='" + sYMD_DMY + "'";
                      sBuf = sBuf + " and DTKSHIN='" + sDTKSHIN + "'";
                      sBuf = sBuf + " and LOTNO='" + sLOTNO + "'";
                      sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                        // 20160623_工場区分追加
                      Query3->SQL->Add(sBuf);
                      try {
                          ClpBrd = Clipboard();
                          ClpBrd->Open();
                          ClpBrd->SetTextBuf(sBuf.c_str());
                          ClpBrd->Close();
                          Query3->ExecSQL();
                      } catch(EDatabaseError& e) {
                          SBr1->Panels->Items[0]->Text = e.Message;
                          SBr1->Update();
                          ProgressBar1->Visible = false;
                          Beep();
                          return(false);
                      } catch(Exception& e) {
                          SBr1->Panels->Items[0]->Text = e.Message;
                          SBr1->Update();
                          ProgressBar1->Visible = false;
                          Beep();
                          return(false);
                      }

                      // 測定数３以上の場合は、例外レコード(KDx2)もコピーします。
                      if( (iSOKUT_SJ1 > 2 && Query2->Fields->Fields[2]->AsInteger > 2 && i != 6 ) ||
                          ((iSOKUT_SJ1 > 2 || iSOKUT_SJ2 > 2 ||
                            Query2->Fields->Fields[2]->AsInteger > 2 ||
                            Query2->Fields->Fields[3]->AsInteger > 2 ) && i == 6 ) ){     // 測定数で判断します

                          // 問い合せ文の実行
                          Query3->Close();              // Initial Query
                          Query3->SQL->Clear();         // Initial Query
                          sBuf = "UPDATE " + sTableName2;
                          sBuf = sBuf + " SET KENSA_YMD='" + sYMD_DMY + "'";
                          if( i == 10 ){
                              sBuf = sBuf + ",SEQNO=" + IntToStr(iSEQ_NO);
                          } else {
                              sBuf = sBuf + ",TOLEY_NO=" + IntToStr(iTOLEY_NO);
                              sBuf = sBuf + ",SAMPLE_P=" + IntToStr(iSAMPLE_P);
                          }
                          sBuf = sBuf + " WHERE KENSA_YMD='" + sYMD + "'";
                          if( i == 10 ){
                              sBuf = sBuf + " and SEQNO=" + IntToStr(Query2->Fields->Fields[1]->AsInteger);
                          } else {
                              sBuf = sBuf + " and TOLEY_NO=" + IntToStr(Query2->Fields->Fields[0]->AsInteger);
                              sBuf = sBuf + " and SAMPLE_P=" + IntToStr(Query2->Fields->Fields[1]->AsInteger);
                          }
                          sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                        // 20160623_工場区分追加
                          
                          Query3->SQL->Add(sBuf);
                          try {
                              ClpBrd = Clipboard();
                              ClpBrd->Open();
                              ClpBrd->SetTextBuf(sBuf.c_str());
                              ClpBrd->Close();
                              Query3->ExecSQL();
                          } catch(EDatabaseError& e) {
                              SBr1->Panels->Items[0]->Text = e.Message;
                              SBr1->Update();
                              ProgressBar1->Visible = false;
                              Beep();
                              return(false);
                          } catch(Exception& e) {
                              SBr1->Panels->Items[0]->Text = e.Message;
                              SBr1->Update();
                              ProgressBar1->Visible = false;
                              Beep();
                              return(false);
                          }
                          
                      }
                  }

                  // カーソルを次にセットする
                  Query2->Next();
              }
          }

          // カーソルを次にセットする
          Query1->Next();
     }

     return(true);
}


//---------------------------------------------------------------------------
// 「ダミー日付で完成した検査指示データ（KD01〜KDC2を含む）を本来の測定日へUpdateします」
bool __fastcall TForm1::SubMoveKM01(AnsiString sYMD, AnsiString sYMD_DMY)
{

     int        i;
     AnsiString sTableName;
     AnsiString sBuf;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "新しい検査指示データを整理中です．．．しばらくお待ち下さい。";
     ProgressBar1->Min = 0;
     ProgressBar1->Max = 25;
     ProgressBar1->Position = 1;
     SBr1->Update();

     // 本来の検査日付レコード（修正前のレコード）を削除します
     Query1->Close();              // Initial Query
     Query1->SQL->Clear();         // Initial Query
     sBuf = "delete from KM01 where KENSA_YMD='" + sYMD + "'";
     sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                       // 20160623_工場区分追加
     Query1->SQL->Add(sBuf);

     // 問い合せ文の実行
     try {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     } catch(EDatabaseError& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         ProgressBar1->Visible = false;
         Beep();
         return(false);
     } catch(Exception& e) {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         ProgressBar1->Visible = false;
         Beep();
         return(false);
     }


     // レコードの検査日付を本来のものに変更します
     for( i=0; i<=24; i++ ){

         ProgressBar1->Position++;
         switch(i){
             case  0: sTableName = "KM01";   break;
             case  1: sTableName = "KD01";   break;
             case  2: sTableName = "KD02";   break;
             case  3: sTableName = "KD11";   break;
             case  4: sTableName = "KD12";   break;
             case  5: sTableName = "KD21";   break;
             case  6: sTableName = "KD22";   break;
             case  7: sTableName = "KD31";   break;
             case  8: sTableName = "KD32";   break;
             case  9: sTableName = "KD41";   break;
             case 10: sTableName = "KD42";   break;
             case 11: sTableName = "KD51";   break;
             case 12: sTableName = "KD52";   break;
             case 13: sTableName = "KD61";   break;
             case 14: sTableName = "KD62";   break;
             case 15: sTableName = "KD71";   break;
             case 16: sTableName = "KD72";   break;
             case 17: sTableName = "KD81";   break;
             case 18: sTableName = "KD82";   break;
             case 19: sTableName = "KD91";   break;
             case 20: sTableName = "KD92";   break;
             case 21: sTableName = "KDA1";   break;
             case 22: sTableName = "KDA2";   break;
             case 23: sTableName = "KDC1";   break;
             case 24: sTableName = "KDC2";   break;
         }

         // 問い合せ文の実行
         Query1->Close();              // Initial Query
         Query1->SQL->Clear();         // Initial Query
         sBuf = "UPDATE " + sTableName + " SET KENSA_YMD='" + sYMD + "'";
         sBuf = sBuf + " WHERE KENSA_YMD='" + sYMD_DMY + "'";
         sBuf = sBuf + " and KOJOKBN = " + IntToStr(iKojoKbn);                   // 20160623_工場区分追加
         Query1->SQL->Add(sBuf);
         try {
             ClpBrd = Clipboard();
             ClpBrd->Open();
             ClpBrd->SetTextBuf(sBuf.c_str());
             ClpBrd->Close();
             Query1->ExecSQL();
         } catch(EDatabaseError& e) {
             SBr1->Panels->Items[0]->Text = e.Message;
             SBr1->Update();
             ProgressBar1->Visible = false;
             Beep();
             return(false);
         } catch(Exception& e) {
             SBr1->Panels->Items[0]->Text = e.Message;
             SBr1->Update();
             ProgressBar1->Visible = false;
             Beep();
             return(false);
         }
     }
     ProgressBar1->Position = ProgressBar1->Max;

     return(true);
}


//---------------------------------------------------------------------------
// 「工管NOを検索します」
bool __fastcall TForm1::SubSearchKOKANBNG( AnsiString sKOKBNG )
{
     AnsiString sBuf;

     // ステータスメッセージ
     SBr1->Panels->Items[0]->Text = "検索中です．．．しばらくお待ち下さい。";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select DTKSCOD,DTKSHIN,LOTBNG,HINBAN,ZISNAM,ZISHIN,SIJISU from SD21S";
     sBuf = sBuf + " where KOKBNG=" + sKOKBNG;
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     if( !(Query1->Eof == True &&  Query1->Bof == True) ){
         // レコード検出
         Edt02->Text = Query1->Fields->Fields[0]->AsString;        // 得意先ｺｰﾄﾞ
         Edt03->Text = Query1->Fields->Fields[1]->AsString;        // 得意先品番
         Edt04->Text = Query1->Fields->Fields[2]->AsString;        // ロットNO
         Edt05->Text = Query1->Fields->Fields[3]->AsString;        // 自社品番
         Edt06->Text = Query1->Fields->Fields[4]->AsString;        // 材質名称
         Edt07->Text = Query1->Fields->Fields[5]->AsString;        // 材質ｺｰﾄﾞ
         Edt08->Text = Query1->Fields->Fields[6]->AsString;        // 数量
         SubSearchTKSHIN( Edt03->Text, true, false );

         SBr1->Panels->Items[0]->Text = "";
         SBr1->Update();
         return(true);
     }
     else{
         // レコードなし
         SBr1->Panels->Items[0]->Text = "該当するデータが見つかりません。";
         SBr1->Update();
         Beep();
         return(false);
     }

}


//---------------------------------------------------------------------------
// 「得意先品番を検索します」
bool __fastcall TForm1::SubSearchTKSHIN(AnsiString sTKSHIN, bool fSetEdit, bool fSetEditSecd)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // 問合せ実行
     sBuf = "select DTKSCOD,HINBAN,ZISNAM,ZISCOD,SORTKEY,KEIJKBN,";
     sBuf = sBuf + "SK_LD_LNG,SK_BURASI,SK_BURASIT,SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_KOYU,";
     sBuf = sBuf + "SK_MAGE,SK_MAGEG,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,SK_ZAKUT,HIST_SOKUT";
     sBuf = sBuf + " from KM02 where DTKSHIN='" + sTKSHIN + "'";
     sBuf = sBuf + " and REVCNT=0";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     if( Query1->Eof == True && Query1->Bof == True ){
         // レコードなし
         if( fSetEdit ){
             if( fSetEditSecd ){
                 Edt02->Text = "";    // 得意先ｺｰﾄﾞ
                 Edt05->Text = "";    // 自社品番
                 Edt06->Text = "";    // 材質名称
                 Edt07->Text = "";    // 材質ｺｰﾄﾞ
             }
             Edt13->Tag  = 0;     // 形状区分
             Edt13->Text = "";    // 形状区分
             Edt14->Text = "";    // 測定区分 リード線長さ
             Edt15->Text = "";    // 測定区分 ブラシ幅
             Edt16->Text = "";    // 測定区分 ブラシ幅縦押し
             Edt17->Text = "";    // 測定区分 リード線取り付け抵抗
             Edt18->Text = "";    // 測定区分 リード線引張強度
             Edt19->Text = "";    // 測定区分 母体比重
             Edt20->Text = "";    // 測定区分 固有抵抗率
             Edt21->Text = "";    // 測定区分 曲げ強さ
             Edt22->Text = "";    // 測定区分 曲げ強さ現物
             Edt23->Text = "";    // 測定区分 HsC硬度（側面）
             Edt24->Text = "";    // 測定区分 HsC硬度（圧面）
             Edt25->Text = "";    // 測定区分 HsD硬度（側面）
             Edt26->Text = "";    // 測定区分 HsD硬度（圧面）
             Edt27->Text = "";    // 測定区分 座屈
             Edt28->Text = "";    // ﾋｽﾄｸﾞﾗﾑ測定数
         }
         sSortKey = "";           // ｿｰﾄｷｰ
         return(false);
     }
     else{
         // レコード検出
         if( fSetEdit ){
             if( fSetEditSecd ){
                 Edt02->Text = Query1->Fields->Fields[0]->AsString; // 得意先ｺｰﾄﾞ
                 Edt05->Text = Query1->Fields->Fields[1]->AsString; // 自社品番
                 Edt06->Text = Query1->Fields->Fields[2]->AsString; // 材質名称
                 Edt07->Text = Query1->Fields->Fields[3]->AsString; // 材質ｺｰﾄﾞ
             }
             Edt13->Tag = Query1->Fields->Fields[5]->AsInteger;     // 形状区分
             switch( Edt13->Tag ){
                 case 1:   Edt13->Text = "小型";    break;
                 case 2:   Edt13->Text = "中型";    break;
                 case 3:   Edt13->Text = "大型";    break;
                 case 4:   Edt13->Text = "円柱";    break;
                 case 5:   Edt13->Text = "コンミ";  break;
             }
             Edt14->Text = Query1->Fields->Fields[6]->AsString;     // 測定区分 リード線長さ
             Edt15->Text = Query1->Fields->Fields[7]->AsString;     // 測定区分 ブラシ幅
             Edt16->Text = Query1->Fields->Fields[8]->AsString;     // 測定区分 ブラシ幅縦押し
             Edt17->Text = Query1->Fields->Fields[9]->AsString;     // 測定区分 リード線取り付け
             Edt18->Text = Query1->Fields->Fields[10]->AsString;    // 測定区分 リード線引張強度
             Edt19->Text = Query1->Fields->Fields[11]->AsString;    // 測定区分 母体比重
             Edt24->Text = Query1->Fields->Fields[12]->AsString;    // 測定区分 固有抵抗率
             Edt25->Text = Query1->Fields->Fields[13]->AsString;    // 測定区分 曲げ強さ
             Edt26->Text = Query1->Fields->Fields[14]->AsString;    // 測定区分 曲げ強さ現物
             Edt20->Text = Query1->Fields->Fields[15]->AsString;    // 測定区分 HsC硬度（圧面）
             Edt21->Text = Query1->Fields->Fields[16]->AsString;    // 測定区分 HsC硬度（側面）
             Edt22->Text = Query1->Fields->Fields[17]->AsString;    // 測定区分 HsD硬度（圧面）
             Edt23->Text = Query1->Fields->Fields[18]->AsString;    // 測定区分 HsD硬度（側面）
             Edt27->Text = Query1->Fields->Fields[19]->AsString;    // 測定区分 座屈
             Edt28->Text = Query1->Fields->Fields[20]->AsString;    // ﾋｽﾄｸﾞﾗﾑ測定数
         }
         sSortKey   = Query1->Fields->Fields[4]->AsString;          // ｿｰﾄｷｰ
         sHistSokut = Query1->Fields->Fields[5]->AsString;          // ﾋｽﾄｸﾞﾗﾑ測定数
         return(true);
     }

}


void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{

    // ステータスメッセージ
    if(SBr1->Panels->Items[0]->Text != ""){
       SBr1->Panels->Items[0]->Text = "";
       SBr1->Update();
    }

    // ﾄﾚｰNO
    PnlTr->Caption = SGr1->Cells[0][ARow];
    // ｻﾝﾌﾟﾘﾝｸﾞﾎﾟｼﾞｼｮﾝ
    PnlSp->Caption = SGr1->Cells[1][ARow];

    if( (StrToInt(PnlTr->Caption) % 2) == 0 ){
       PnlTr->Color = SGr1->FixedColor - 0x0001163A;
    } else{
       PnlTr->Color = SGr1->FixedColor;
    }

    div_t x=div(StrToInt(PnlSp->Caption)-1,6);
    if( (x.quot % 2) == 1 ){
       if( (StrToInt(PnlTr->Caption) % 2) == 1)
          PnlSp->Color= 0x00C1FFC1 - 0x0001163A;
       else
          PnlSp->Color= 0x00C1FFC1;
    } else{
       if( (StrToInt(PnlTr->Caption) % 2) == 1)
          PnlSp->Color= 0x00C1FFC1;
       else
          PnlSp->Color= 0x00C1FFC1 - 0x0001163A;
    }


    // 工管NO
    Edt01->Text = SGr1->Cells[2][ARow];
    // 得意先ｺｰﾄﾞ
    Edt02->Text = SGr1->Cells[3][ARow];
    // 得意先品番
    Edt03->Text = SGr1->Cells[4][ARow];
    // ロットNO
    Edt04->Text = SGr1->Cells[5][ARow];
    // 自社品番
    Edt05->Text = SGr1->Cells[6][ARow];
    // 材質ｺｰﾄﾞ
    Edt06->Text = SGr1->Cells[7][ARow];
    // 材質名称
    Edt07->Text = SGr1->Cells[8][ARow];
    // 数量
    Edt08->Text = SGr1->Cells[9][ARow];
    // 形状区分
    Edt13->Tag = StrToIntDef(SGr1->Cells[12][ARow],0);
    Edt13->Text = SGr1->Cells[13][ARow];
    // 測定区分 リード線長さ
    Edt14->Text = SGr1->Cells[14][ARow];
    // 測定区分 ブラシ幅
    Edt15->Text = SGr1->Cells[15][ARow];
    // 測定区分 ブラシ幅縦押し
    Edt16->Text = SGr1->Cells[16][ARow];
    // 測定区分 リード線取り付け抵抗
    Edt17->Text = SGr1->Cells[17][ARow];
    // 測定区分 リード線引張強度
    Edt18->Text = SGr1->Cells[18][ARow];
    // 測定区分 母体比重
    Edt19->Text = SGr1->Cells[19][ARow];
    // 測定区分 固有抵抗率
    Edt20->Text = SGr1->Cells[20][ARow];
    // 測定区分 曲げ強さ
    Edt21->Text = SGr1->Cells[21][ARow];
    // 測定区分 曲げ強さ現物
    Edt22->Text = SGr1->Cells[22][ARow];
    // 測定区分 HsC硬度（側面）
    Edt23->Text = SGr1->Cells[23][ARow];
    // 測定区分 HsC硬度（圧面）
    Edt24->Text = SGr1->Cells[24][ARow];
    // 測定区分 HsD硬度（側面）
    Edt25->Text = SGr1->Cells[25][ARow];
    // 測定区分 HsD硬度（圧面）
    Edt26->Text = SGr1->Cells[26][ARow];
    // 測定区分 座屈
    Edt27->Text = SGr1->Cells[27][ARow];
    // ﾋｽﾄｸﾞﾗﾑ測定数
    Edt28->Text = SGr1->Cells[28][ARow];

}

//---------------------------------------------------------------------------
void __fastcall TForm1::SGr1KeyPress(TObject *Sender, char &Key)
{

     switch(Key)
     {
         // 前項
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // 次項
         case VK_DOWN:
         case VK_RIGHT: BtnF03Click(Sender);    break;

         // Enter
         case VK_RETURN:
                        //Edt01->SetFocus();
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
     }

}


void __fastcall TForm1::AllEnter(TObject *Sender)
{

    // 検査予定日
    if( EdtCOD->Focused() ){
        Form2->Tag = 1;
        BtnF01->Enabled = true;
        return;
    }
    // 得意先ｺｰﾄﾞ
    if( Edt02->Focused() ){
        Form2->Tag = 2;
        BtnF01->Enabled = true;
        return;
    }
    // 得意先品番
    if( Edt03->Focused() ){
        Form2->Tag = 3;
        BtnF01->Enabled = true;
        return;
    }
    // ロットNO
    if( Edt04->Focused() && (Edt03->Text.Length() > 0) ){
        Form2->Tag = 4;
        BtnF01->Enabled = true;
        return;
    }
    // 自社品番
    if( Edt05->Focused() ){
        Form2->Tag = 5;
        BtnF01->Enabled = true;
        return;
    }
    // 材質名称
    if( Edt06->Focused() ){
        Form2->Tag = 6;
        BtnF01->Enabled = true;
        return;
    }
    // 材質ｺｰﾄﾞ
    if( Edt07->Focused() ){
        Form2->Tag = 7;
        BtnF01->Enabled = true;
        return;
    }

    if( BtnF01->Focused() || BtnF02->Focused() ||
        BtnF03->Focused() || BtnF04->Focused() ||
        BtnF05->Focused() || BtnF06->Focused() ||
        BtnF07->Focused() || BtnF08->Focused() ||
        BtnF09->Focused() || BtnF10->Focused() ||
        BtnF11->Focused() || BtnF12->Focused() ){
        return;
    }

    // その他
    Form2->Tag = 0;
    BtnF01->Enabled = false;

}


//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::DelSEPA(AnsiString sYMD)
{
    int         iPos;
    AnsiString  sRet;

    sRet = sYMD;
    while( (iPos = sRet.AnsiPos("/")) != 0){
        sRet.Delete(iPos,1);
    }

    return( sRet );
}


//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::InsSEPA(AnsiString sYMD)
{
    AnsiString  sRet;

    sRet = sYMD;
    sRet.Insert("/",5);
    sRet.Insert("/",8);

    return( sRet );
}


//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}

// 検査予定年月日の↑↓ボタン　2002/10/28 A.Tamura
void __fastcall TForm1::UpDownymdClick(TObject *Sender, TUDBtnType Button)
{

   try{

      //char str[256];
      //sprintf(str,"Max=%d Min=%d Pos=%d", UpDownymd->Max, UpDownymd->Min, UpDownymd->Position);

      // 検査予定年月日
      EdtCOD->SetFocus();
      TDateTime dtDate = StrToDate(EdtCOD->Text);
      if( Button == Comctrls::btNext ){
         dtDate++;
      } else{
         dtDate--;
      }
      EdtCOD->Text = FormatDateTime("yyyy/mm/dd",dtDate.FormatString("YYYY/MM/DD"));
   }
   catch(...){
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
     int i;
     int iLeft;
     int iUpdate;
     int iBuf;

     // 測定数パネルを初期化
     iLeft = Panel3->Left - Panel3->Tag;
     Panel3->Visible = true;
     Panel21->Visible = true;
     for( i = Panel3->Left; i > iLeft; i = iUpdate ){
         iUpdate = iLeft + ((i-iLeft) / 1.5);
         iBuf = Panel3->Left;
         Panel3->Left  = iUpdate;
         Panel21->Left  = iUpdate;
         Panel3->Width += iBuf - iUpdate;
         Panel21->Width += iBuf - iUpdate;
//         Panel3->Update();
//         Panel21->Update();
         // 数量
         if( Panel3->Width - 17 > Panel17->Width + 1){
             SGr1->ColWidths[9] = 0;
             // 材質ｺｰﾄﾞ
             if( Panel3->Width - 17> (Panel17->Width + Panel16->Width + 2) ){
                 SGr1->ColWidths[8] = 0;
                 // 材質名称
                 if( Panel3->Width - 17> (Panel17->Width + Panel16->Width + Panel15->Width + 3) ){
                     SGr1->ColWidths[7] = 0;
                     // 自社品番
                     if( Panel3->Width - 17> (Panel17->Width + Panel16->Width + Panel15->Width + Panel14->Width + 4) ){
                         SGr1->ColWidths[6] = 0;
                     } else{
                         SGr1->ColWidths[6] = Panel14->Width - (Panel3->Width - 17 - Panel17->Width - Panel16->Width - Panel15->Width) + 4;
                     }
                 } else{
                     SGr1->ColWidths[7] = Panel15->Width - (Panel3->Width - 17 - Panel17->Width - Panel16->Width) + 3;
                 }
             } else{
                 SGr1->ColWidths[8] = Panel16->Width - (Panel3->Width - 17 - Panel17->Width) + 2;
             }
         } else{
             SGr1->ColWidths[9] = Panel17->Width - (Panel3->Width - 17) + 1;
         }
         SGr1->Repaint();

     }
     Panel3->Left  = iLeft;
     Panel3->Width = Panel3->Tag;
     Panel21->Left  = iLeft;
     Panel21->Width = Panel21->Tag;

     SGr1->ColWidths[6] = 0;    // 自社品番
     SGr1->ColWidths[7] = 0;    // 材質名称
     SGr1->ColWidths[8] = 0;    // 材質ｺｰﾄﾞ
     SGr1->ColWidths[9] = 0;    // 数量

     Edt05->Visible = false;
     Edt06->Visible = false;
     Edt07->Visible = false;
     Edt08->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
     int i;
     int iLeft;
     int iUpdate;

     // 測定数パネルを初期化
     iLeft = Panel3->Left + Panel3->Tag;
     for( i = Panel3->Left; i < iLeft-1; i = iUpdate ){
         iUpdate = i + ((iLeft-i) / 1.05);
         Panel3->Width = iUpdate - Panel3->Left;
         Panel21->Width = iUpdate - Panel21->Left;
         Panel3->Left  = iUpdate;
         Panel21->Left  = iUpdate;
         Panel3->Update();
         Panel21->Update();
     }
     Panel3->Left  = iLeft;
     Panel21->Left  = iLeft;
     Panel3->Width = 0;
     Panel21->Width = 0;
     Panel3->Visible = false;
     Panel21->Visible = false;

     SGr1->ColWidths[6] = Panel14->Width;    // 自社品番
     SGr1->ColWidths[7] = Panel15->Width;    // 材質名称
     SGr1->ColWidths[8] = Panel16->Width;    // 材質ｺｰﾄﾞ
     SGr1->ColWidths[9] = Panel17->Width;    // 数量

     Edt05->Visible = true;
     Edt06->Visible = true;
     Edt07->Visible = true;
     Edt08->Visible = true;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SGr1DrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{

   RECT r=RECT(Rect);


   //固定セルの背景色をセット
   if(State.Contains(gdFixed)){
       if( ACol == 0 ){
           if( (SGr1->Cells[0][ARow] % 2) == 1)
              SGr1->Canvas->Brush->Color= SGr1->FixedColor;
           else
              SGr1->Canvas->Brush->Color= SGr1->FixedColor - 0x0001163A;
       }
       else if( ACol == 1){
           div_t x=div(StrToInt(SGr1->Cells[1][ARow])-1,6);
           if( (x.quot % 2) == 1 ){
               if( (SGr1->Cells[0][ARow] % 2) == 1)
                   SGr1->Canvas->Brush->Color= 0x00C1FFC1 - 0x0001163A;
               else
                   SGr1->Canvas->Brush->Color= 0x00C1FFC1;
           } else{
               if( (SGr1->Cells[0][ARow] % 2) == 1)
                   SGr1->Canvas->Brush->Color= 0x00C1FFC1;
               else
                   SGr1->Canvas->Brush->Color= 0x00C1FFC1 - 0x0001163A;
           }
       }
   }
   //   //フォーカスのあるセルの背景色をセット
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //選択されているセルの背景色をセット
   else if(State.Contains(gdSelected)){
       SGr1->Canvas->Brush->Color= clHighlight;
   }
   //普通のセルの背景色をセット
   else{
       //if( SGr1->Cells[1][ARow] == 6 )
       SGr1->Canvas->Brush->Color= SGr1->Color;
   }
   //背景色で消去
   SGr1->Canvas->FillRect(Rect);

   //固定セルの立体枠を描く
   if(SGr1->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr1->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //フォーカスのあるセルの文字色をセット
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //フォーカス枠を描く
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
   }
   //選択されているセルの文字色をセット
   else if(State.Contains(gdSelected))
       SGr1->Canvas->Font->Color= clHighlightText;
//   //過去の履歴データの場合の文字色をセット
//   else if( SGr1->Cells[1][ARow].ToIntDef(0) == 2 )
//       SGr1->Canvas->Font->Color = clSilver;
   //普通のセルの文字色をセット
   else
       SGr1->Canvas->Font->Color= SGr1->Font->Color;

   //テキスト表示領域の設定
   InflateRect(&r,-2,-2);

   //テキストの表示
   DrawText(SGr1->Canvas->Handle,SGr1->Cells[ACol][ARow].c_str(),-1,&r,0); //右寄せ

//   if( ACol < 0 || ACol > 10 ) return;
//   if( SGr1->Cells[10][ARow].ToIntDef(0) > 0 ){
//       SGr1->Canvas->Font->Color = clYellow;
//   }

}
//---------------------------------------------------------------------------
//INIファイル 読み込み 工場区分取得
void __fastcall TForm1::Read_Ini()
{
     int getlen1;
     char windir[MAX_PATH];	//Windows Dir
     char CurDir[MAX_PATH];	//Current Dir
     char tempo[MAX_PATH];

     //設定ファイル　( "windows\TKSMAIN.ini" or "winnt\TKSMAIN.ini" )
     char INIname[MAX_PATH];

     // 機器番号を読込む
     GetCurrentDirectory(256,CurDir);
     sprintf(INIname, "%s\\Tks.ini", CurDir);
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);
     iKojoKbn = atoi(tempo);
     
}
//---------------------------------------------------------------------------


