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
#pragma resource "*.dfm"

TForm1 *Form1;
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

     // ���萔�p�l����������
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

     // �O���b�h�̏�����
     SGr1->ColWidths[0] = Panel8->Width;     // �ڰ
     SGr1->ColWidths[1] = Panel19->Width;    // SP
     SGr1->ColWidths[2] = Panel23->Width;    // �H��NO
     SGr1->ColWidths[3] = Panel12->Width;    // ���Ӑ溰��
     SGr1->ColWidths[4] = Panel13->Width;    // ���Ӑ�i��
     SGr1->ColWidths[5] = Panel22->Width;    // ���b�gNO
     SGr1->ColWidths[6] = Panel14->Width;    // ���Еi��
     SGr1->ColWidths[7] = Panel15->Width;    // �ގ�����
     SGr1->ColWidths[8] = Panel16->Width;    // �ގ�����
     SGr1->ColWidths[9] = Panel17->Width;    // ����
     SGr1->ColWidths[10] = 0;                // ���Key
     SGr1->ColWidths[11] = 0;                // ˽ĸ��ё��萔
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

     // �{�^���̏�����
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

     // �G�f�B�b�g�̏�����
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

     // �s���܂Ƃ߂Ēǉ�����
     for( i=0; i<SGr1->RowCount; i++ ){
         x = div( i, 30 );
         sBuf = IntToStr(x.quot + 1);
         SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
         sBuf = IntToStr(x.rem + 1);
         SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
     }

     DataSave = false;
     NotFound = true;

     // �����\����̏�����
     DtTOMR = Date();
     DtTOMR++;
     EdtCOD->Text = FormatDateTime("yyyy/mm/dd",DtTOMR);

}

//---------------------------------------------------------------------------

void __fastcall TForm1::ExtractCode(AnsiString str)
{
    //���[�U�R�[�h�A���[�U���A�����R�[�h�A������ ���o
    int i,n1,m,strlen;

    //������
    USER_COD = 0;
    USER_NAM = "";
    BUMO_COD = "";
    BUMO_NAM = "";

    strlen = str.Length();
    n1 = m = 1;

    for ( i = 1; i <= strlen; i++ ) {
        //��؂�L��","�̌���
        if ( str.SubString(i,1) == "," ) {
            if ( n1 < i ) {
            //n1=i�̎��͕�����NULL
                switch(m){
                //�ϐ��ɕ�������
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
            //���̕�����J�n�ʒu
            n1 = i + 1;
            m++;

        }
    }
    if ( m <= 4 ) {
        //BUMO_NAM
        BUMO_NAM = str.SubString(n1,strlen - n1 + 1);
    }

    // �������\��
    PnlBumCode->Caption = BUMO_COD;
    PnlBumName->Caption = BUMO_NAM;
    PnlTanCode->Caption = IntToStr(USER_COD);
    PnlTanName->Caption = USER_NAM;

}


//---------------------------------------------------------------------------
// �u�e�P�F�ꗗ�����v
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    if( !BtnF01->Tag ){
        ////////////////////
        // �ꗗ����
        Form2->ShowModal();
    }
    else{
        ////////////////////
        // �\�[�g
        int         i,k;
        TKM01       Tmp_KM01;
        AnsiString  sBuf;

        SBr1->Panels->Items[0]->Text = "�\�[�g���ł��D�D�D���΂炭���҂��������B ";
        SBr1->Update();

        for( i=0; i<(SGr1->RowCount-1); i++ ){
            for( k=i+1; k<SGr1->RowCount; k++ ){
                if( SGr1->Cells[10][i] == SGr1->Cells[10][k] ){         // ��ķ�
                    if( SGr1->Cells[4][i] == SGr1->Cells[4][k] ){       // ���Ӑ�i��
                        if( SGr1->Cells[5][i] > SGr1->Cells[5][k] &&
                                          SGr1->Cells[5][k] != "" ){    // ���b�gNO

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
                        if( SGr1->Cells[4][i] > SGr1->Cells[4][k] &&   // ���Ӑ�i��
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
                                       SGr1->Cells[10][k] != "" ){     // ��ķ�

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

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// �u�e�Q�F�O���v
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
    if( !BtnF02->Tag ){
        // �O��
        if(SGr1->Row > 0){
            SGr1->Row -= 1;
            SGr1->SetFocus();
        }
    }
}

//---------------------------------------------------------------------------
// �u�e�R�F�����v
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
    if( !BtnF03->Tag ){
        // ����
        if( (SGr1->RowCount-1) > SGr1->Row ){
            SGr1->Row += 1;
            SGr1->SetFocus();
        }
    }
}

//---------------------------------------------------------------------------
// �u�e�S�F�R�s�[�v
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    if( !BtnF04->Enabled )    return;

    if( !BtnF04->Tag ){
        ///////////////////
        // �R�s�[

        int         i;
        int         cnt;
        AnsiString  sBuf;

        // �R�s�[�̌����m�ۂ��܂�
        CopyCnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // �������̊m��
        if( hMemCopy ){
            GlobalUnlock( hMemCopy );
            GlobalFree( hMemCopy );
        }
        hMemCopy = GlobalAlloc( GHND, sizeof(struct TKM01) * CopyCnt );
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
            SBr1->Update();
            Beep();
            return;
        }
        KM01 = (struct TKM01 *)GlobalLock(hMemCopy);
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
            SBr1->Update();
            Beep();
            return;
        }

        // �I������Ă���͈͂��������Ɋi�[���܂�
        for( i=SGr1->Selection.Top, cnt=0; i<=SGr1->Selection.Bottom ; i++, cnt++ ) {
            sBuf = SGr1->Cells[2][i];
            strcpy( KM01[cnt].KOKBNG,  sBuf.c_str() );            // �H��NO
            sBuf = SGr1->Cells[3][i];
            strcpy( KM01[cnt].DTKSCOD, sBuf.c_str() );            // ���Ӑ溰��
            sBuf = SGr1->Cells[4][i];
            strcpy( KM01[cnt].DTKSHIN, sBuf.c_str() );            // ���Ӑ�i��
            sBuf = SGr1->Cells[5][i];
            strcpy( KM01[cnt].LOTNO,   sBuf.c_str() );            // ���b�gNO
            sBuf = SGr1->Cells[6][i];
            strcpy( KM01[cnt].HINBAN,  sBuf.c_str() );            // ���Еi��
            sBuf = SGr1->Cells[7][i];
            strcpy( KM01[cnt].ZISNAM,  sBuf.c_str() );            // �ގ�����
            sBuf = SGr1->Cells[8][i];
            strcpy( KM01[cnt].ZISCOD,  sBuf.c_str() );            // �ގ�����
            sBuf = SGr1->Cells[9][i];
            strcpy( KM01[cnt].NUM,     sBuf.c_str() );            // ����
            sBuf = SGr1->Cells[10][i];
            strcpy( KM01[cnt].SORTKEY, sBuf.c_str() );            // ��ķ�
            sBuf = SGr1->Cells[11][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ˽ĸ��ё��萔
            sBuf = SGr1->Cells[12][i];
            strcpy( KM01[cnt].KEIJKBN   ,sBuf.c_str() );          // �`��敪
            sBuf = SGr1->Cells[13][i];
            strcpy( KM01[cnt].KEIJKBNNM ,sBuf.c_str() );          // �`��敪����
            sBuf = SGr1->Cells[14][i];
            strcpy( KM01[cnt].SK_LD_LNG ,sBuf.c_str() );          // ����敪 ���[�h������
            sBuf = SGr1->Cells[15][i];
            strcpy( KM01[cnt].SK_BURASI ,sBuf.c_str() );          // ����敪 �u���V��
            sBuf = SGr1->Cells[16][i];
            strcpy( KM01[cnt].SK_BURASIT,sBuf.c_str() );          // ����敪 �u���V���c����
            sBuf = SGr1->Cells[17][i];
            strcpy( KM01[cnt].SK_LD_TR  ,sBuf.c_str() );          // ����敪 ���[�h�����t����R
            sBuf = SGr1->Cells[18][i];
            strcpy( KM01[cnt].SK_LD_HP  ,sBuf.c_str() );          // ����敪 ���[�h���������x
            sBuf = SGr1->Cells[19][i];
            strcpy( KM01[cnt].SK_BOIAI  ,sBuf.c_str() );          // ����敪 ��̔�d
            sBuf = SGr1->Cells[20][i];
            strcpy( KM01[cnt].SK_KOYU   ,sBuf.c_str() );          // ����敪 �ŗL��R��
            sBuf = SGr1->Cells[21][i];
            strcpy( KM01[cnt].SK_MAGE   ,sBuf.c_str() );          // ����敪 �Ȃ�����
            sBuf = SGr1->Cells[22][i];
            strcpy( KM01[cnt].SK_MAGEG  ,sBuf.c_str() );          // ����敪 �Ȃ���������
            sBuf = SGr1->Cells[23][i];
            strcpy( KM01[cnt].SK_HSC_A  ,sBuf.c_str() );          // ����敪 HsC�d�x�i���ʁj
            sBuf = SGr1->Cells[24][i];
            strcpy( KM01[cnt].SK_HSC_S  ,sBuf.c_str() );          // ����敪 HsC�d�x�i���ʁj
            sBuf = SGr1->Cells[25][i];
            strcpy( KM01[cnt].SK_HSD_A  ,sBuf.c_str() );          // ����敪 HsD�d�x�i���ʁj
            sBuf = SGr1->Cells[26][i];
            strcpy( KM01[cnt].SK_HSD_S  ,sBuf.c_str() );          // ����敪 HsD�d�x�i���ʁj
            sBuf = SGr1->Cells[27][i];
            strcpy( KM01[cnt].SK_ZAKUT  ,sBuf.c_str() );          // ����敪 ����
            sBuf = SGr1->Cells[28][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ˽ĸ��ё��萔
        }
    }
    else{
        ///////////////////
        // �؂���

        int   i,j;
        int   cnt;
        div_t x;
        AnsiString  sBuf;

        // �R�s�[�̌����m�ۂ��܂�
        CopyCnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // �������̊m��
        if( hMemCopy ){
            GlobalUnlock( hMemCopy );
            GlobalFree( hMemCopy );
        }
        hMemCopy = GlobalAlloc( GHND, sizeof(struct TKM01) * CopyCnt );
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(01)";
            SBr1->Update();
            Beep();
            return;
        }
        KM01 = (struct TKM01 *)GlobalLock(hMemCopy);
        if( hMemCopy == NULL ){
            SBr1->Panels->Items[0]->Text = "�������̈���m�ۂł��܂���B(02)";
            SBr1->Update();
            Beep();
            return;
        }

        // �I������Ă���͈͂��������Ɋi�[���܂�
        for( i=SGr1->Selection.Top, cnt=0; i<=SGr1->Selection.Bottom ; i++, cnt++ ) {
            sBuf = SGr1->Cells[2][i];
            strcpy( KM01[cnt].KOKBNG,  sBuf.c_str() );            // �H��NO
            sBuf = SGr1->Cells[3][i];
            strcpy( KM01[cnt].DTKSCOD, sBuf.c_str() );            // ���Ӑ溰��
            sBuf = SGr1->Cells[4][i];
            strcpy( KM01[cnt].DTKSHIN, sBuf.c_str() );            // ���Ӑ�i��
            sBuf = SGr1->Cells[5][i];
            strcpy( KM01[cnt].LOTNO,   sBuf.c_str() );            // ���b�gNO
            sBuf = SGr1->Cells[6][i];
            strcpy( KM01[cnt].HINBAN,  sBuf.c_str() );            // ���Еi��
            sBuf = SGr1->Cells[7][i];
            strcpy( KM01[cnt].ZISNAM,  sBuf.c_str() );            // �ގ�����
            sBuf = SGr1->Cells[8][i];
            strcpy( KM01[cnt].ZISCOD,  sBuf.c_str() );            // �ގ�����
            sBuf = SGr1->Cells[9][i];
            strcpy( KM01[cnt].NUM,     sBuf.c_str() );            // ����
            sBuf = SGr1->Cells[10][i];
            strcpy( KM01[cnt].SORTKEY, sBuf.c_str() );            // ��ķ�
            sBuf = SGr1->Cells[11][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ˽ĸ��ё��萔
            sBuf = SGr1->Cells[12][i];
            strcpy( KM01[cnt].KEIJKBN   ,sBuf.c_str() );          // �`��敪
            sBuf = SGr1->Cells[13][i];
            strcpy( KM01[cnt].KEIJKBNNM ,sBuf.c_str() );          // �`��敪����
            sBuf = SGr1->Cells[14][i];
            strcpy( KM01[cnt].SK_LD_LNG ,sBuf.c_str() );          // ����敪 ���[�h������
            sBuf = SGr1->Cells[15][i];
            strcpy( KM01[cnt].SK_BURASI ,sBuf.c_str() );          // ����敪 �u���V��
            sBuf = SGr1->Cells[16][i];
            strcpy( KM01[cnt].SK_BURASIT,sBuf.c_str() );          // ����敪 �u���V���c����
            sBuf = SGr1->Cells[17][i];
            strcpy( KM01[cnt].SK_LD_TR  ,sBuf.c_str() );          // ����敪 ���[�h�����t����R
            sBuf = SGr1->Cells[18][i];
            strcpy( KM01[cnt].SK_LD_HP  ,sBuf.c_str() );          // ����敪 ���[�h���������x
            sBuf = SGr1->Cells[19][i];
            strcpy( KM01[cnt].SK_BOIAI  ,sBuf.c_str() );          // ����敪 ��̔�d
            sBuf = SGr1->Cells[20][i];
            strcpy( KM01[cnt].SK_KOYU   ,sBuf.c_str() );          // ����敪 �ŗL��R��
            sBuf = SGr1->Cells[21][i];
            strcpy( KM01[cnt].SK_MAGE   ,sBuf.c_str() );          // ����敪 �Ȃ�����
            sBuf = SGr1->Cells[22][i];
            strcpy( KM01[cnt].SK_MAGEG  ,sBuf.c_str() );          // ����敪 �Ȃ���������
            sBuf = SGr1->Cells[23][i];
            strcpy( KM01[cnt].SK_HSC_A  ,sBuf.c_str() );          // ����敪 HsC�d�x�i���ʁj
            sBuf = SGr1->Cells[24][i];
            strcpy( KM01[cnt].SK_HSC_S  ,sBuf.c_str() );          // ����敪 HsC�d�x�i���ʁj
            sBuf = SGr1->Cells[25][i];
            strcpy( KM01[cnt].SK_HSD_A  ,sBuf.c_str() );          // ����敪 HsD�d�x�i���ʁj
            sBuf = SGr1->Cells[26][i];
            strcpy( KM01[cnt].SK_HSD_S  ,sBuf.c_str() );          // ����敪 HsD�d�x�i���ʁj
            sBuf = SGr1->Cells[27][i];
            strcpy( KM01[cnt].SK_ZAKUT  ,sBuf.c_str() );          // ����敪 ����
            sBuf = SGr1->Cells[28][i];
            strcpy( KM01[cnt].HIST_SOKUT,sBuf.c_str() );          // ˽ĸ��ё��萔
        }

        // �O���b�h�̃N���A�[����

        // �I������Ă���͈͂��N���A�[���܂�
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++) {
            // �O���b�h���폜���܂��B
            for( j=2; j<=28 ; j++) {
                SGr1->Cells[j][i] = "";
            }
        }

        x = div( SGr1->Selection.Top, 30 );
        // x.quot  ��
        // x.rem   �]

        if( (x.rem + CopyCnt) > 30 ){
            // �I��͈͂������̃g���[�ɂ܂������Ă���Ƃ�

            x = div( SGr1->Selection.Bottom + 1, 30 );
            // x.quot  ��
            // x.rem   �]

            for( i=(x.quot*30), cnt=0; i<(x.quot*30+30); i++, cnt++ ) {
                // �O���b�h���l�߂܂�
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
            // �I��͈͂���̃g���[�ɔ[�܂��Ă���Ƃ�
            for( i=SGr1->Selection.Top; i<(x.quot*30+30); i++ ) {
                // �O���b�h���l�߂܂�
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

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }

    // �J�[�\����擪�ɖ߂��܂�
    SGr1->Row = SGr1->Selection.Top;

}

//---------------------------------------------------------------------------
// �u�e�T�F�\��t���v
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;
    if( !BtnF05->Tag ){
        //////////////
        // �\��t��

        int         i,j,cnt;
        div_t       x;
        AnsiString  sBuf;


        // �s���܂Ƃ߂Ēǉ�����
        x = div( (SGr1->Selection.Top + CopyCnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
            }
        }

        // �R�s�[�p����������O���b�h�Ɋi�[���܂�
        for( i=SGr1->Row, cnt=0; cnt<CopyCnt ; i++, cnt++ ) {
            SGr1->Cells[2][i] = KM01[cnt].KOKBNG ;            // �H��NO
            SGr1->Cells[3][i] = KM01[cnt].DTKSCOD;            // ���Ӑ溰��
            SGr1->Cells[4][i] = KM01[cnt].DTKSHIN;            // ���Ӑ�i��
            SGr1->Cells[5][i] = KM01[cnt].LOTNO  ;            // ���b�gNO
            SGr1->Cells[6][i] = KM01[cnt].HINBAN ;            // ���Еi��
            SGr1->Cells[7][i] = KM01[cnt].ZISNAM ;            // �ގ�����
            SGr1->Cells[8][i] = KM01[cnt].ZISCOD ;            // �ގ�����
            SGr1->Cells[9][i] = KM01[cnt].NUM    ;            // ����
            SGr1->Cells[10][i]= KM01[cnt].SORTKEY;            // ��ķ�
            SGr1->Cells[11][i]= KM01[cnt].HIST_SOKUT;         // ˽ĸ��ё��萔
            SGr1->Cells[12][i]= KM01[cnt].KEIJKBN;            // �`��敪
            SGr1->Cells[13][i]= KM01[cnt].KEIJKBNNM;          // �`��敪����
            SGr1->Cells[14][i]= KM01[cnt].SK_LD_LNG;          // ����敪 ���[�h������
            SGr1->Cells[15][i]= KM01[cnt].SK_BURASI;          // ����敪 �u���V��
            SGr1->Cells[16][i]= KM01[cnt].SK_BURASIT;         // ����敪 �u���V���c����
            SGr1->Cells[17][i]= KM01[cnt].SK_LD_TR;           // ����敪 ���[�h�����t����R
            SGr1->Cells[18][i]= KM01[cnt].SK_LD_HP;           // ����敪 ���[�h���������x
            SGr1->Cells[19][i]= KM01[cnt].SK_BOIAI;           // ����敪 ��̔�d
            SGr1->Cells[20][i]= KM01[cnt].SK_KOYU;            // ����敪 �ŗL��R��
            SGr1->Cells[21][i]= KM01[cnt].SK_MAGE;            // ����敪 �Ȃ�����
            SGr1->Cells[22][i]= KM01[cnt].SK_MAGEG;           // ����敪 �Ȃ���������
            SGr1->Cells[23][i]= KM01[cnt].SK_HSC_A;           // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[24][i]= KM01[cnt].SK_HSC_S;           // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[25][i]= KM01[cnt].SK_HSD_A;           // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[26][i]= KM01[cnt].SK_HSD_S;           // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[27][i]= KM01[cnt].SK_ZAKUT;           // ����敪 ����
            SGr1->Cells[28][i]= KM01[cnt].HIST_SOKUT;         // ˽ĸ��ё��萔
        }

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// �u�e�U�F�}���^�󔒑}���v
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;
    if( !BtnF06->Tag ){
        //////////////
        // �}��

        int         i,j,end,cnt;
        div_t       x;
        AnsiString  sBuf;


        // �f�[�^���L��ŉ��s��T���܂�
        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            // �O���b�h�̈�s���폜���܂��B
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // �s���܂Ƃ߂Ēǉ�����
        x = div( (end + CopyCnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
            }
        }

        // �}������s�����ړ����܂�
        for( i=(SGr1->RowCount-30); i>=(SGr1->Row+CopyCnt) ; i-- ) {
            // �O���b�h�̈�s���폜���܂��B
            SGr1->Cells[2][i] = SGr1->Cells[2][i-CopyCnt];        // �H��NO
            SGr1->Cells[3][i] = SGr1->Cells[3][i-CopyCnt];        // ���Ӑ溰��
            SGr1->Cells[4][i] = SGr1->Cells[4][i-CopyCnt];        // ���Ӑ�i��
            SGr1->Cells[5][i] = SGr1->Cells[5][i-CopyCnt];        // ���b�gNO
            SGr1->Cells[6][i] = SGr1->Cells[6][i-CopyCnt];        // ���Еi��
            SGr1->Cells[7][i] = SGr1->Cells[7][i-CopyCnt];        // �ގ�����
            SGr1->Cells[8][i] = SGr1->Cells[8][i-CopyCnt];        // �ގ�����
            SGr1->Cells[9][i] = SGr1->Cells[9][i-CopyCnt];        // ����
            SGr1->Cells[10][i]= SGr1->Cells[10][i-CopyCnt];       // ��ķ�
            SGr1->Cells[11][i]= SGr1->Cells[11][i-CopyCnt];       // ˽ĸ��ё��萔
            SGr1->Cells[12][i]= SGr1->Cells[12][i-CopyCnt];       // �`��敪
            SGr1->Cells[13][i]= SGr1->Cells[13][i-CopyCnt];       // �`��敪����
            SGr1->Cells[14][i]= SGr1->Cells[14][i-CopyCnt];       // ����敪 ���[�h������
            SGr1->Cells[15][i]= SGr1->Cells[15][i-CopyCnt];       // ����敪 �u���V��
            SGr1->Cells[16][i]= SGr1->Cells[16][i-CopyCnt];       // ����敪 �u���V���c����
            SGr1->Cells[17][i]= SGr1->Cells[17][i-CopyCnt];       // ����敪 ���[�h�����t����R
            SGr1->Cells[18][i]= SGr1->Cells[18][i-CopyCnt];       // ����敪 ���[�h���������x
            SGr1->Cells[19][i]= SGr1->Cells[19][i-CopyCnt];       // ����敪 ��̔�d
            SGr1->Cells[20][i]= SGr1->Cells[20][i-CopyCnt];       // ����敪 �ŗL��R��
            SGr1->Cells[21][i]= SGr1->Cells[21][i-CopyCnt];       // ����敪 �Ȃ�����
            SGr1->Cells[22][i]= SGr1->Cells[22][i-CopyCnt];       // ����敪 �Ȃ���������
            SGr1->Cells[23][i]= SGr1->Cells[23][i-CopyCnt];       // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[24][i]= SGr1->Cells[24][i-CopyCnt];       // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[25][i]= SGr1->Cells[25][i-CopyCnt];       // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[26][i]= SGr1->Cells[26][i-CopyCnt];       // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[27][i]= SGr1->Cells[27][i-CopyCnt];       // ����敪 ����
            SGr1->Cells[28][i]= SGr1->Cells[28][i-CopyCnt];       // ˽ĸ��ё��萔
        }

        // �R�s�[�p����������O���b�h�Ɋi�[���܂�
        for( i=SGr1->Row, cnt=0; cnt<CopyCnt ; i++, cnt++ ) {
            SGr1->Cells[2][i] = KM01[cnt].KOKBNG ;            // �H��NO
            SGr1->Cells[3][i] = KM01[cnt].DTKSCOD;            // ���Ӑ溰��
            SGr1->Cells[4][i] = KM01[cnt].DTKSHIN;            // ���Ӑ�i��
            SGr1->Cells[5][i] = KM01[cnt].LOTNO  ;            // ���b�gNO
            SGr1->Cells[6][i] = KM01[cnt].HINBAN ;            // ���Еi��
            SGr1->Cells[7][i] = KM01[cnt].ZISNAM ;            // �ގ�����
            SGr1->Cells[8][i] = KM01[cnt].ZISCOD ;            // �ގ�����
            SGr1->Cells[9][i] = KM01[cnt].NUM    ;            // ����
            SGr1->Cells[10][i]= KM01[cnt].SORTKEY;            // ��ķ�
            SGr1->Cells[11][i]= KM01[cnt].HIST_SOKUT;         // ˽ĸ��ё��萔
            SGr1->Cells[12][i]= KM01[cnt].KEIJKBN;            // �`��敪
            SGr1->Cells[13][i]= KM01[cnt].KEIJKBNNM;          // �`��敪����
            SGr1->Cells[14][i]= KM01[cnt].SK_LD_LNG;          // ����敪 ���[�h������
            SGr1->Cells[15][i]= KM01[cnt].SK_BURASI;          // ����敪 �u���V��
            SGr1->Cells[16][i]= KM01[cnt].SK_BURASIT;         // ����敪 �u���V���c����
            SGr1->Cells[17][i]= KM01[cnt].SK_LD_TR;           // ����敪 ���[�h�����t����R
            SGr1->Cells[18][i]= KM01[cnt].SK_LD_HP;           // ����敪 ���[�h���������x
            SGr1->Cells[19][i]= KM01[cnt].SK_BOIAI;           // ����敪 ��̔�d
            SGr1->Cells[20][i]= KM01[cnt].SK_KOYU;            // ����敪 �ŗL��R��
            SGr1->Cells[21][i]= KM01[cnt].SK_MAGE;            // ����敪 �Ȃ�����
            SGr1->Cells[22][i]= KM01[cnt].SK_MAGEG;           // ����敪 �Ȃ���������
            SGr1->Cells[23][i]= KM01[cnt].SK_HSC_A;           // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[24][i]= KM01[cnt].SK_HSC_S;           // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[25][i]= KM01[cnt].SK_HSD_A;           // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[26][i]= KM01[cnt].SK_HSD_S;           // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[27][i]= KM01[cnt].SK_ZAKUT;           // ����敪 ����
            SGr1->Cells[28][i]= KM01[cnt].HIST_SOKUT;         // ˽ĸ��ё��萔
        }

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }
    else{
        //////////////
        // �󔒑}��

        int         i,j,end,cnt;
        div_t       x;
        AnsiString  sBuf;


        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        // �f�[�^���L��ŉ��s��T���܂�
        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            // �O���b�h�̈�s���폜���܂��B
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // �s���܂Ƃ߂Ēǉ�����
        x = div( (end + cnt), 30 );
        if( ((x.quot + 2) * 30) > SGr1->RowCount ){
            j=SGr1->RowCount;
            SGr1->RowCount = (x.quot + 2) * 30;
            for( i=j; i<SGr1->RowCount; i++ ){
                x = div( i, 30 );
                sBuf = IntToStr(x.quot + 1);
                SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
                sBuf = IntToStr(x.rem + 1);
                SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
            }
        }

        // �}������s�����ړ����܂�
        for( i=(SGr1->RowCount-30); i>=(SGr1->Selection.Top+cnt) ; i-- ) {
            SGr1->Cells[2][i] = SGr1->Cells[2][i-cnt];        // �H��NO
            SGr1->Cells[3][i] = SGr1->Cells[3][i-cnt];        // ���Ӑ溰��
            SGr1->Cells[4][i] = SGr1->Cells[4][i-cnt];        // ���Ӑ�i��
            SGr1->Cells[5][i] = SGr1->Cells[5][i-cnt];        // ���b�gNO
            SGr1->Cells[6][i] = SGr1->Cells[6][i-cnt];        // ���Еi��
            SGr1->Cells[7][i] = SGr1->Cells[7][i-cnt];        // �ގ�����
            SGr1->Cells[8][i] = SGr1->Cells[8][i-cnt];        // �ގ�����
            SGr1->Cells[9][i] = SGr1->Cells[9][i-cnt];        // ����
            SGr1->Cells[10][i]= SGr1->Cells[10][i-cnt];       // ��ķ�
            SGr1->Cells[11][i]= SGr1->Cells[11][i-cnt];       // ˽ĸ��ё��萔
            SGr1->Cells[12][i]= SGr1->Cells[12][i-cnt];       // �`��敪
            SGr1->Cells[13][i]= SGr1->Cells[13][i-cnt];       // �`��敪����
            SGr1->Cells[14][i]= SGr1->Cells[14][i-cnt];       // ����敪 ���[�h������
            SGr1->Cells[15][i]= SGr1->Cells[15][i-cnt];       // ����敪 �u���V��
            SGr1->Cells[16][i]= SGr1->Cells[16][i-cnt];       // ����敪 �u���V���c����
            SGr1->Cells[17][i]= SGr1->Cells[17][i-cnt];       // ����敪 ���[�h�����t����R
            SGr1->Cells[18][i]= SGr1->Cells[18][i-cnt];       // ����敪 ���[�h���������x
            SGr1->Cells[19][i]= SGr1->Cells[19][i-cnt];       // ����敪 ��̔�d
            SGr1->Cells[20][i]= SGr1->Cells[20][i-cnt];       // ����敪 �ŗL��R��
            SGr1->Cells[21][i]= SGr1->Cells[21][i-cnt];       // ����敪 �Ȃ�����
            SGr1->Cells[22][i]= SGr1->Cells[22][i-cnt];       // ����敪 �Ȃ���������
            SGr1->Cells[23][i]= SGr1->Cells[23][i-cnt];       // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[24][i]= SGr1->Cells[24][i-cnt];       // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[25][i]= SGr1->Cells[25][i-cnt];       // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[26][i]= SGr1->Cells[26][i-cnt];       // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[27][i]= SGr1->Cells[27][i-cnt];       // ����敪 ����
            SGr1->Cells[28][i]= SGr1->Cells[28][i-cnt];       // ˽ĸ��ё��萔
        }

        // �󔒍s���O���b�h�Ɋi�[���܂�
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++ ) {
            SGr1->Cells[2][i] = "";            // �H��NO
            SGr1->Cells[3][i] = "";            // ���Ӑ溰��
            SGr1->Cells[4][i] = "";            // ���Ӑ�i��
            SGr1->Cells[5][i] = "";            // ���b�gNO
            SGr1->Cells[6][i] = "";            // ���Еi��
            SGr1->Cells[7][i] = "";            // �ގ�����
            SGr1->Cells[8][i] = "";            // �ގ�����
            SGr1->Cells[9][i] = "";            // ����
            SGr1->Cells[10][i]= "";            // ��ķ�
            SGr1->Cells[11][i]= "";            // ˽ĸ��ё��萔
            SGr1->Cells[12][i]= "";            // �`��敪
            SGr1->Cells[13][i]= "";            // �`��敪����
            SGr1->Cells[14][i]= "";            // ����敪 ���[�h������
            SGr1->Cells[15][i]= "";            // ����敪 �u���V��
            SGr1->Cells[16][i]= "";            // ����敪 �u���V���c����
            SGr1->Cells[17][i]= "";            // ����敪 ���[�h�����t����R
            SGr1->Cells[18][i]= "";            // ����敪 ���[�h���������x
            SGr1->Cells[19][i]= "";            // ����敪 ��̔�d
            SGr1->Cells[20][i]= "";            // ����敪 �ŗL��R��
            SGr1->Cells[21][i]= "";            // ����敪 �Ȃ�����
            SGr1->Cells[22][i]= "";            // ����敪 �Ȃ���������
            SGr1->Cells[23][i]= "";            // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[24][i]= "";            // ����敪 HsC�d�x�i���ʁj
            SGr1->Cells[25][i]= "";            // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[26][i]= "";            // ����敪 HsD�d�x�i���ʁj
            SGr1->Cells[27][i]= "";            // ����敪 ����
            SGr1->Cells[28][i]= "";            // ˽ĸ��ё��萔
        }

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }
}

//---------------------------------------------------------------------------
// �u�e�V�F�����v
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
    if( !BtnF07->Enabled )    return;
    if( !BtnF07->Tag ){
        //////////////
        // ����
        SubSearch( Sender, DelSEPA(EdtCOD->Text));
    }
}

//---------------------------------------------------------------------------
// �u�e�W�F�V�K�o�^�^���荀�ڂ̕\��-��\���v
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    if( !BtnF08->Enabled )    return;
    if( !BtnF08->Tag ){
        //////////////
        // �V�K�o�^
        SubAdd();
    }
    else{
        //////////////
        // ���荀�ڂ̕\���^��\��
        if( Panel3->Visible == false )   SpeedButton2Click(Sender);
        else                             SpeedButton1Click(Sender);

    }
}

//---------------------------------------------------------------------------
// �u�e�X�F�C���^��ʈ���v
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
    if( !BtnF09->Enabled )    return;
    if( !BtnF09->Tag ){
        //////////////
        // �C��
        SubCorrect();
    }
    else{
        //////////////
        // ��ʈ��
        Form1->Print();
    }
}

//---------------------------------------------------------------------------
// �u�e�P�O�F�폜�^����v
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{

    if( !BtnF10->Enabled )    return;

    if( !BtnF10->Tag ){
        //////////////
        // �폜
        int   i,j,end,cnt;
        div_t       x;

        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        for( i=SGr1->Selection.Top; i<SGr1->RowCount; i++) {
            // �O���b�h���l�߂܂�
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

        // �s���܂Ƃ߂č폜����
        x = div( end, 30 );
        if( ((x.quot + 2) * 30) < SGr1->RowCount ){
            SGr1->RowCount = (x.quot + 2) * 30;
        }

/*
        // �I������Ă���͈͂��N���A�[���܂�
        end = SGr1->Row;
        for( i=SGr1->Selection.Top; i<=SGr1->Selection.Bottom ; i++) {
            // �O���b�h���폜���܂��B
            for( j=2; j<=10; j++) {
                SGr1->Cells[j][i] = "";
            }
        }

        cnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

        x = div( SGr1->Selection.Top, 30 );
        // x.quot  ��
        // x.rem   �]

        if( (x.rem + cnt) > 30 ){
            // �I��͈͂������̃g���[�ɂ܂������Ă���Ƃ�
            y = div( SGr1->Selection.Bottom + 1, 30 );
            // y.quot  ��
            // y.rem   �]

            for( i=(y.quot*30), cnt=0; i<(y.quot*30+30); i++, cnt++ ) {
                // �O���b�h���l�߂܂�
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

            // �g���[�̐擪�ȊO����I�����n�܂�A�Ȃ����g���[�S�̂��I��
            // ����Ă���ꍇ�́@�f�[�^�ړ��i�g���[���j
            if( x.rem>0 && (y.quot-x.quot)>=2 ){
                end = (y.quot - (x.quot+1)) * 30;
                for( i=((x.quot+1)*30); i<(SGr1->RowCount-end); i++ ) {
                    // �O���b�h���l�߂܂�
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                    }
                }
            }
            // ���x�A�g���[�̐擪���R�O�ȏ�I�������ꍇ�@�f�[�^�ړ��i�g���[���j
            if( x.rem==0 && (y.quot-x.quot)>=1 ){
                end = (y.quot - x.quot) * 30;
                for( i=(x.quot*30); i<(SGr1->RowCount-end); i++ ) {
                    // �O���b�h���l�߂܂�
                    for( j=2; j<=10; j++) {
                        SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                    }
                }
            }
        }
        else if( (x.rem + cnt) < 30 ){
            // �I��͈͂���̃g���[�ɔ[�܂��Ă���Ƃ�
            for( i=SGr1->Selection.Top; i<(x.quot*30+30); i++ ) {
                // �O���b�h���l�߂܂�
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
            // �I��͈͂������̃g���[�ɂ܂������Ă���Ƃ�
            y = div( SGr1->Selection.Bottom + 1, 30 );
            // y.quot  ��
            // y.rem   �]

            // ���x�A�g���[�̐擪���R�O�I�������ꍇ
            end = (y.quot - x.quot) * 30;
            for( i=(x.quot*30); i<(SGr1->RowCount-end); i++ ) {
                // �O���b�h���l�߂܂�
                for( j=2; j<=10; j++) {
                    SGr1->Cells[j][i] = SGr1->Cells[j][i+end];
                }
            }
        }

        end = SGr1->Selection.Top;
        for( i = SGr1->Selection.Top; i < (SGr1->RowCount - 1); i++) {
            if( SGr1->Cells[4][i] != "" )   end = i;
        }

        // �s���܂Ƃ߂č폜����
        x = div( end, 30 );
        if( ((x.quot + 2) * 30) < SGr1->RowCount ){
            SGr1->RowCount = (x.quot + 2) * 30;
        }

        SGr1->SetFocus();
        SGr1->Row = SGr1->Selection.Top;
*/
        SGr1->SetFocus();
        SGr1->Row = SGr1->Selection.Top;

        // �f�[�^��ύX�����t���O
        DataSave = true;

    }
    else{
        //////////////
        // ���
        Form5->QuickRep1->Preview();
        //Form5->QuickRep1->Print();

        keybd_event(VK_CONTROL,0,0,0);
        keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
    }
}

//---------------------------------------------------------------------------
// �u�e�P�P�F�ۑ��^˽Ĉ���v
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
    int iPrtCnt;
    int i;
    AnsiString sBuf;


    if( !BtnF11->Enabled )    return;
    if( !BtnF11->Tag ){
        //////////////
        // �ۑ�
        SubSave();
    }
    else{
        //////////////
        // ˽Ĉ��
        iPrtCnt = 0;
        for( i=0; i<SGr1->RowCount; i++ ){
            // ˽ĸ��ё��萔
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
                    // �荷���g���C
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
                    // �J�Z�b�g
                    Form3->QuickRep1->PrinterSettings->OutputBin = Auto;
                }
*/
                Form3->QuickRep1->Print();
            }
        }
        else{
            SBr1->Panels->Items[0]->Text = "�������q�X�g�f�[�^���L��܂���B";
            Beep();
        }
    }
}

//---------------------------------------------------------------------------
// �u�e�P�Q�F�߂�v
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
    if( !BtnF12->Enabled )    return;
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    // �X�e�[�^�X���b�Z�[�W
    if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
    }

    if( Shift.Contains(ssCtrl) ){
        BtnF01->Caption = "�\�[�g";
        BtnF02->Caption = "";
        BtnF03->Caption = "";
        BtnF04->Caption = "�؂���";
        BtnF05->Caption = "";
        BtnF06->Caption = "�󔒑}��";
        BtnF07->Caption = "";
        BtnF08->Caption = "���荀��";
        BtnF09->Caption = "��ʈ��";
        BtnF10->Caption = "���";
        BtnF11->Caption = "˽Ĉ��";
        BtnF12->Caption = "�߂�";

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
                     // �������Ƀt�H�[�J�X������ꍇ�́A�������s
                     if( EdtCOD->Focused() ){
                         BtnF07Click(Sender);
                     }
                     // �������ȊO�Ƀt�H�[�J�X������ꍇ�́A�������ɃZ�b�g�t�H�[�J�X
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


        // �O��
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

         // ����
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

                // �����\���
                if(EdtCOD->Focused()){
                    BtnF07Click(Sender);
                    break;
                }
                // �H��NO
                if(Edt01->Focused()){
                    // �H��NO�������J�n
                    if( Edt01->Text.Length() == 0 || Trim(Edt01->Text) == "0" ){
                        // ���������s���Ȃ�
                        //Edt02->SetFocus();
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                    if( SubSearchKOKANBNG( Edt01->Text ) ){
                        // �H��NO�̌����ɐ����̏ꍇ�́A�o�^���s���܂��B
                        SubAdd();
                    }
                    else{
                        // �����Ɏ��s
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
                // ���Ӑ�i��
                if(Edt03->Focused()){
                    // ���Ӑ�i�Ԃ������J�n
                    if( Edt03->Text.Length() == 0 ){
                        //Edt02->SetFocus();
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                    SBr1->Panels->Items[0]->Text = "���i�K�i�}�X�^���������Ă��܂��D�D�D";
                    SBr1->Update();
                    if( SubSearchTKSHIN( Edt03->Text, true, true ) ){
                        // ���Ӑ�i�Ԃ̌����ɐ���
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        SBr1->Panels->Items[0]->Text = "";
                        SBr1->Update();
                    }
                    else{
                        // �����Ɏ��s
                        SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ�������܂���B";
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
          BtnF01->Caption = "�ꗗ����";
          BtnF02->Caption = "�O��";
          BtnF03->Caption = "����";
          BtnF04->Caption = "�R�s�[";
          BtnF05->Caption = "�\��t��";
          BtnF06->Caption = "�}��";
          BtnF07->Caption = "����";
          BtnF08->Caption = "�V�K�o�^";
          BtnF09->Caption = "�C��";
          BtnF10->Caption = "�폜";
          BtnF11->Caption = "�ۑ�";
          BtnF12->Caption = "�߂�";

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

    // �f�[�^��ύX�������ǂ����̃t���O�`�F�b�N
    if( DataSave ){
        switch( MessageDlg( "�f�[�^���ҏW����Ă��܂��B\n�ۑ����܂����H",
                           mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
                if( !SubSave() )   CanClose = false;

//                if( Database1->InTransaction == True )  Database1->Commit();
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
//                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
                break;
        }
    }

    // �I�����̏���
    if( CanClose ){
        // �������̊J��
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
// �u�����v
void __fastcall TForm1::SubSearch( TObject *Sender, AnsiString sYMD )
{
     int i,j;
     int iRow,iCnt;
     AnsiString sBuf;
     div_t x;

     if( !BtnF07->Enabled )    return;

     if( sYMD.Length() < 8 ){
         SBr1->Panels->Items[0]->Text = "�����\������w�肵�ĉ������B";
         SBr1->Update();
         Beep();
         return;
     }

     // ��ʂ�������
     for( i=0; i<SGr1->RowCount; i++) {
         for( j=2; j<=28; j++) {
             SGr1->Cells[j][i] = "";
         }
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�������ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "select TOLEY_NO,SAMPLE_P,KOKBNG,DTKSCOD,DTKSHIN,LOTNO,HINBAN,ZISNAM,ZISCOD,NUM,SORTKEY,";
     sBuf = sBuf + "KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_KOYU,";
     sBuf = sBuf + "SK_MAGE,SK_MAGEG,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,SK_ZAKUT,HIST_SOKUT";
     sBuf = sBuf + " from KM01";
     sBuf = sBuf + " where KENSA_YMD like '";
     sBuf = sBuf + sYMD + "'";
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

          iRow = Query1->Fields->Fields[0]->AsInteger;                           // �ڰNO
          iRow = ((iRow-1) * 30) + (Query1->Fields->Fields[1]->AsInteger - 1);   // �����ݸ��߼޼��

          // �s���܂Ƃ߂Ēǉ�����
          x = div( iRow, 30 );
          if( ((x.quot + 2) * 30) > SGr1->RowCount ){
              j=SGr1->RowCount;
              SGr1->RowCount = (x.quot + 2) * 30;
              for( i=j; i<SGr1->RowCount; i++ ){
                  x = div( i, 30 );
                  sBuf = IntToStr(x.quot + 1);
                  SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
                  sBuf = IntToStr(x.rem + 1);
                  SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
              }
          }

          // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
          sBuf = Query1->Fields->Fields[2]->AsString;      // �H��NO
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;      // ���Ӑ溰��
          SGr1->Cells[3][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;      // ���Ӑ�i��
          SGr1->Cells[4][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;      // ���b�gNO
          SGr1->Cells[5][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[6]->AsString;      // ���Еi��
          SGr1->Cells[6][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[7]->AsString;      // �ގ�����
          SGr1->Cells[7][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[8]->AsString;      // �ގ�����
          SGr1->Cells[8][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[9]->AsString;      // ����
          SGr1->Cells[9][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[10]->AsString;     // ��ķ�
          SGr1->Cells[10][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[11]->AsString;     // �`��敪
          SGr1->Cells[12][iRow] = sBuf;

          switch( StrToIntDef(SGr1->Cells[12][iRow],1) ){  // �`��敪
              case 1:   SGr1->Cells[13][iRow] = "���^";    break;
              case 2:   SGr1->Cells[13][iRow] = "���^";    break;
              case 3:   SGr1->Cells[13][iRow] = "��^";    break;
              case 4:   SGr1->Cells[13][iRow] = "�~��";    break;
              case 5:   SGr1->Cells[13][iRow] = "�R���~";  break;
          }

          sBuf = Query1->Fields->Fields[12]->AsString;      // ����敪 ���[�h������
          SGr1->Cells[14][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[13]->AsString;      // ����敪 �u���V��
          SGr1->Cells[15][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[14]->AsString;      // ����敪 �u���V���c����
          SGr1->Cells[16][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[15]->AsString;      // ����敪 ���[�h�����t��
          SGr1->Cells[17][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[16]->AsString;      // ����敪 ���[�h���������x
          SGr1->Cells[18][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[17]->AsString;      // ����敪 ��̔�d
          SGr1->Cells[19][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[21]->AsString;      // ����敪 HsC�d�x�i���ʁj
          SGr1->Cells[20][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[22]->AsString;      // ����敪 HsC�d�x�i���ʁj
          SGr1->Cells[21][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[23]->AsString;      // ����敪 HsD�d�x�i���ʁj
          SGr1->Cells[22][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[24]->AsString;      // ����敪 HsD�d�x�i���ʁj
          SGr1->Cells[23][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[18]->AsString;      // ����敪 �ŗL��R��
          SGr1->Cells[24][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[19]->AsString;      // ����敪 �Ȃ�����
          SGr1->Cells[25][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[20]->AsString;      // ����敪 �Ȃ���������
          SGr1->Cells[26][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[25]->AsString;      // ����敪 ����
          SGr1->Cells[27][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[26]->AsString;      // ˽ĸ��ё��萔
          SGr1->Cells[28][iRow] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[26]->AsString;      // ˽ĸ��ё��萔
          SGr1->Cells[11][iRow] = sBuf;


          // �J�[�\�������ɃZ�b�g����
          Query1->Next();
          iCnt++;
     }

     // �P�s�ڂ�I��
     SGr1->Row = 0;
     SGr1SelectCell( Sender, 1, 0, true);

//     SGr1->SetFocus();

     /*
     // �V�����g�����U�N�V�������J�n
     if( Database1->InTransaction == false ){
         Database1->StartTransaction();
         DataSave = false;
     }
     */

     keybd_event(VK_TAB,0,0,0);
     keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);

     // �{�^���̏�����
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

     // �X�e�[�^�X���b�Z�[�W
     if( iCnt == 0 ){
         sBuf = "�V�K�o�^���s���Ă��������B";
     }
     else{
         sBuf = FormatFloat( "�������� 0���ł��B", iCnt );
     }
     SBr1->Panels->Items[0]->Text = sBuf;
     SBr1->Update();


}


//---------------------------------------------------------------------------
// �u�V�K�o�^�v
void __fastcall TForm1::SubAdd()
{
     int         i,j,end;
     AnsiString  sBuf;
     div_t       x;
     bool        flag;


     if( Edt03->Text == "" ){
         // �X�e�[�^�X���b�Z�[�W
         SBr1->Panels->Items[0]->Text = "�K�{���ڂ���͂��ĉ������B";
         SBr1->Update();
         Beep();
         return;
     }

     // ���Ӑ�i�Ԃ��������܂�
     if( SubSearchTKSHIN(Edt03->Text,false,false) == false ){
         SBr1->Panels->Items[0]->Text = "���Ӑ�i�ԂɊY�����鐻�i�K�i�}�X�^��������܂���B";
         SBr1->Update();
         Edt03->SelectAll();
         Beep();
         return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �ŏI�̃f�[�^�s��T��
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
     SGr1->Tag = SGr1->Row;      // �J�[�\���̗L��s�Ƀf�[�^�ǉ�

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = Edt01->Text;                               // �H��NO
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[2][SGr1->Tag] = sBuf;

     sBuf = Edt02->Text;                               // ���Ӑ溰��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[3][SGr1->Tag] = sBuf;

     sBuf = Edt03->Text;                               // ���Ӑ�i��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[4][SGr1->Tag] = sBuf;

     sBuf = Edt04->Text;                               // ���b�gNO
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[5][SGr1->Tag] = sBuf;

     sBuf = Edt05->Text;                               // ���Еi��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[6][SGr1->Tag] = sBuf;

     sBuf = Edt06->Text;                               // �ގ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[7][SGr1->Tag] = sBuf;

     sBuf = Edt07->Text;                               // �ގ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[8][SGr1->Tag] = sBuf;

     sBuf = Edt08->Text;                               // ����
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[9][SGr1->Tag] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

     sBuf = sSortKey;                                  // ��ķ�
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[10][SGr1->Tag] = sBuf;

     sBuf = Edt13->Tag;                                // �`��敪
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[12][SGr1->Tag] = sBuf;

     sBuf = Edt13->Text;                               // �`��敪
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[13][SGr1->Tag] = sBuf;

     sBuf = Edt14->Text;                               // ����敪 ���[�h������
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[14][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt15->Text;                               // ����敪 �u���V��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[15][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt16->Text;                               // ����敪 �u���V���c����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[16][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt17->Text;                               // ����敪 ���[�h�����t��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[17][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt18->Text;                               // ����敪 ���[�h���������x
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[18][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt19->Text;                               // ����敪 ��̔�d
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[19][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt20->Text;                               // ����敪 �ŗL��R��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[20][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt21->Text;                               // ����敪 �Ȃ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[21][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt22->Text;                               // ����敪 �Ȃ���������
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[22][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt23->Text;                               // ����敪 HsC�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[23][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt24->Text;                               // ����敪 HsC�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[24][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt25->Text;                               // ����敪 HsD�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[25][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt26->Text;                               // ����敪 HsD�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[26][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt27->Text;                               // ����敪 ����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[27][SGr1->Tag] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt28->Text;                               // ˽ĸ��ё��萔
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[28][SGr1->Tag] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

     sBuf = sHistSokut;                                // ˽ĸ��ё��萔
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[11][SGr1->Tag] = sBuf;

     // ��s���₷
     if( (SGr1->Tag + 1) > end )   end = SGr1->Tag + 1;

     // �s���܂Ƃ߂Ēǉ�����
     x = div( end, 30 );
     if( ((x.quot + 2) * 30) > SGr1->RowCount ){
         j=SGr1->RowCount;
         SGr1->RowCount = (x.quot + 2) * 30;
         for( i=j; i<SGr1->RowCount; i++ ){
             x = div( i, 30 );
             sBuf = IntToStr(x.quot + 1);
             SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �ڰNO
             sBuf = IntToStr(x.rem + 1);
             SGr1->Cells[1][i] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;     // �����ݸ��߼޼��
         }
     }

     // �V�����s��I��
     SGr1->Row = SGr1->Tag + 1;

     Edt01->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;
}


//---------------------------------------------------------------------------
// �u�C���v
void __fastcall TForm1::SubCorrect()
{
     AnsiString sBuf;

     if( SGr1->Cells[4][SGr1->Row] == "" ){
         // �X�e�[�^�X���b�Z�[�W
         SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
         SBr1->Update();
         Beep();
         return;
     }

     // ���Ӑ�i�Ԃ��������܂�
     if( SubSearchTKSHIN(Edt03->Text,false,false) == false ){
         SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ�������܂���B";
         SBr1->Update();
         Edt03->SelectAll();
         Beep();
         return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = Edt01->Text;                               // �H��NO
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = Edt02->Text;                               // ���Ӑ溰��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[3][SGr1->Row] = sBuf;

     sBuf = Edt03->Text;                               // ���Ӑ�i��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[4][SGr1->Row] = sBuf;

     sBuf = Edt04->Text;                               // ���b�gNO
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[5][SGr1->Row] = sBuf;

     sBuf = Edt05->Text;                               // ���Еi��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[6][SGr1->Row] = sBuf;

     sBuf = Edt06->Text;                               // �ގ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[7][SGr1->Row] = sBuf;

     sBuf = Edt07->Text;                               // �ގ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[8][SGr1->Row] = sBuf;

     sBuf = Edt08->Text;                               // ����
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[9][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

     sBuf = sSortKey;                                  // ��ķ�
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[10][SGr1->Row] = sBuf;

     sBuf = Edt13->Tag;                                // �`��敪
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[12][SGr1->Row] = sBuf;

     sBuf = Edt13->Text;                               // �`��敪
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[13][SGr1->Row] = sBuf;

     sBuf = Edt14->Text;                               // ����敪 ���[�h������
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[14][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt15->Text;                               // ����敪 �u���V��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[15][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt16->Text;                               // ����敪 �u���V���c����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[16][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt17->Text;                               // ����敪 ���[�h�����t��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[17][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt18->Text;                               // ����敪 ���[�h���������x
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[18][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt19->Text;                               // ����敪 ��̔�d
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[19][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt20->Text;                               // ����敪 �ŗL��R��
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[20][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt21->Text;                               // ����敪 �Ȃ�����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[21][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt22->Text;                               // ����敪 �Ȃ���������
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[22][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt23->Text;                               // ����敪 HsC�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[23][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt24->Text;                               // ����敪 HsC�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[24][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt25->Text;                               // ����敪 HsD�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[25][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt26->Text;                               // ����敪 HsD�d�x�i���ʁj
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[26][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt27->Text;                               // ����敪 ����
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[27][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = Edt28->Text;                               // ˽ĸ��ё��萔
     if( sBuf.Length() == 0 )   sBuf = " ";
     SGr1->Cells[28][SGr1->Row] = AnsiString::StringOfChar(' ', 5 - sBuf.Length()) + sBuf;

     sBuf = sHistSokut;                                // ˽ĸ��ё��萔
     if( sBuf.Length() == 0 )   sBuf = "0";
     SGr1->Cells[11][SGr1->Row] = sBuf;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;

}


//---------------------------------------------------------------------------
// �u�ۑ��v
bool __fastcall TForm1::SubSave()
{
     int        i;
     int        iDataCount;
     bool       bUpdate;
     AnsiString sBuf;
     AnsiString sDummyDate;

     // �X�e�[�^�X���b�Z�[�W
     ProgressBar1->Visible = true;
     SBr1->Panels->Items[0]->Text = "�ۑ��O�̃f�[�^�`�F�b�N���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     ProgressBar1->Position = 0;
     ProgressBar1->Min = 0;
     // �ۑ�����f�[�^�������߂܂�
     iDataCount = 0;
     for( i=0; i<SGr1->RowCount; i++ ){
         if( SGr1->Cells[4][i] != "" ) iDataCount++ ;
     }
     ProgressBar1->Max = iDataCount;


     // �������t�̃��R�[�h�����݂��邩�ǂ����⍇�����s
     sBuf = "select TOLEY_NO from KM01";
     sBuf = sBuf + " where KENSA_YMD like '" + NowKey + "'";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     bUpdate = false;
     if( !Query1->Eof ){
         // �������R�[�h���������ꍇ

         // �������s�O�̊m�F
         sBuf =        "���ɍ쐬���ꂽ�����w���f�[�^���C�����悤�Ƃ��Ă��܂��B\n";
         sBuf = sBuf + "���̌����w���̑���ς݃f�[�^�́A���̂܂܈����p����܂��B\n";
         sBuf = sBuf + "���A���A���݁A���̃R���s���[�^�ł��̌����w���𑪒蒆�̏ꍇ�́A\n";
         sBuf = sBuf + "�@�������ɏI���i�����ʂ����j���ĉ������B\n\n";
         sBuf = sBuf + "�u�����w���f�[�^�̍č쐬�v�Ɓu����ς݃f�[�^�̍Ĕz�u�v���J�n���܂��B\n";
         sBuf = sBuf + "��낵���ł����H";
         switch( MessageDlg( sBuf, mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) ){
             // �uYes�v      �������s
             case mrYes:
                 break;
             // �uNo�v       �������f
             case mrNo:
                 SBr1->Panels->Items[0]->Text = "�����𒆒f���܂����B";
                 SBr1->Update();
                 ProgressBar1->Visible = false;
                 return(true);
                 break;
         }

         bUpdate = true;

         // �ő�̓��t�{�P���擾���܂��B
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
         //     sBuf = Query1->Fields->Fields[0]->AsString;      // �ő���t
         //     TDateTime dtDate = StrToDate(sBuf);
         //     dtDate++;                                        // �ő���t�{�P
         //     sDummyDate = FormatDateTime("yyyy/mm/dd",dtDate.FormatString("YYYY/MM/DD"));
         // }
         // else{
         //     sDummyDate = "40000101";
         // }
         sDummyDate = "40000101";

         // �u�����w���f�[�^�C���ׂ̈�KM01,KD01,KD02�`KDA1,KDA2���R�s�[���܂��v
         // if( SubCopyKM01( NowKey, sDummyDate) = false ) return(false);

         // �������t�̃��R�[�h�����݂��邩�ǂ����⍇�����s
         Query1->Close();              // Initial Query
         Query1->SQL->Clear();         // Initial Query
         sBuf = "select TOLEY_NO from KM01 where KENSA_YMD='" + sDummyDate + "'";
         Query1->SQL->Add(sBuf);
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->Open();
         Query1->Active = true;
         if( !Query1->Eof ){
             // ���R�[�h�폜�̎��s
             Query1->Close();              // Initial Query
             Query1->SQL->Clear();         // Initial Query
             sBuf = "delete from KM01 where KENSA_YMD='" + sDummyDate + "'";
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

     // �X�e�[�^�X���b�Z�[�W
     ProgressBar1->Visible = true;
     SBr1->Panels->Items[0]->Text = "�����w���f�[�^�̕ۑ����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �O���b�h�̃f�[�^���c�a�ɒǉ����܂�
     for( i=0; i<SGr1->RowCount; i++ ){

         // ���Ӑ�i�Ԃ����݂���t�B�[���h�̂ݒǉ�
         if( SGr1->Cells[4][i] != "" ){

             // Initial Query
             Query1->Close();
             Query1->SQL->Clear();

             // �⍇�����쐬
             sBuf = "insert into KM01(KENSA_YMD,TOLEY_NO,SAMPLE_P,KOKBNG,DTKSCOD,DTKSHIN,LOTNO,";
             sBuf = sBuf + "HINBAN,ZISNAM,ZISCOD,NUM,SORTKEY,KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,";
             sBuf = sBuf + "SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_KOYU,SK_MAGE,SK_MAGEG,SK_HSC_A,SK_HSC_S,";
             sBuf = sBuf + "SK_HSD_A,SK_HSD_S,SK_ZAKUT,HIST_SOKUT,UPDYMD,UPDTIM,UPDCHR)";
             sBuf = sBuf + " values('";
             if( bUpdate == true ){
             // �f�[�^�X�V�̎��́A�_�~�[�̓��t�ŏ������݂܂��B
                 sBuf = sBuf + sDummyDate           + "'," ;    // �����\���
             } else {
                 sBuf = sBuf + NowKey               + "'," ;    // �����\���
             }
             sBuf = sBuf + SGr1->Cells[0][i]        +  "," ;    // �ڰNO
             sBuf = sBuf + SGr1->Cells[1][i]        +  "," ;    // ������߼޼��
             sBuf = sBuf + SGr1->Cells[2][i]        +  ",'";    // �H��NO
             sBuf = sBuf + Trim(SGr1->Cells[3][i])  + "','";    // ���Ӑ溰��
             sBuf = sBuf + SGr1->Cells[4][i]        + "','";    // ���Ӑ�i��
             sBuf = sBuf + SGr1->Cells[5][i]        + "','";    // ���b�gNO
             sBuf = sBuf + SGr1->Cells[6][i]        + "','";    // ���Еi��
             sBuf = sBuf + SGr1->Cells[7][i]        + "','";    // �ގ�����
             sBuf = sBuf + SGr1->Cells[8][i]        + "'," ;    // �ގ�����
             sBuf = sBuf + Trim(SGr1->Cells[9][i])  +  "," ;    // ����
             sBuf = sBuf + Trim(SGr1->Cells[10][i]) +  "," ;    // ��ķ�
             sBuf = sBuf + Trim(SGr1->Cells[12][i]) +  "," ;    // �`��敪
             sBuf = sBuf + Trim(SGr1->Cells[14][i]) +  "," ;    // ����敪 ���[�h������
             sBuf = sBuf + Trim(SGr1->Cells[15][i]) +  "," ;    // ����敪 �u���V��
             sBuf = sBuf + Trim(SGr1->Cells[16][i]) +  "," ;    // ����敪 �u���V���c����
             sBuf = sBuf + Trim(SGr1->Cells[17][i]) +  "," ;    // ����敪 ���[�h�����t����R
             sBuf = sBuf + Trim(SGr1->Cells[18][i]) +  "," ;    // ����敪 ���[�h���������x
             sBuf = sBuf + Trim(SGr1->Cells[19][i]) +  "," ;    // ����敪 ��̔�d
             sBuf = sBuf + Trim(SGr1->Cells[24][i]) +  "," ;    // ����敪 �ŗL��R��
             sBuf = sBuf + Trim(SGr1->Cells[25][i]) +  "," ;    // ����敪 �Ȃ�����
             sBuf = sBuf + Trim(SGr1->Cells[26][i]) +  "," ;    // ����敪 �Ȃ���������
             sBuf = sBuf + Trim(SGr1->Cells[20][i]) +  "," ;    // ����敪 HsC�d�x�i���ʁj
             sBuf = sBuf + Trim(SGr1->Cells[21][i]) +  "," ;    // ����敪 HsC�d�x�i���ʁj
             sBuf = sBuf + Trim(SGr1->Cells[22][i]) +  "," ;    // ����敪 HsD�d�x�i���ʁj
             sBuf = sBuf + Trim(SGr1->Cells[23][i]) +  "," ;    // ����敪 HsD�d�x�i���ʁj
             sBuf = sBuf + Trim(SGr1->Cells[27][i]) +  "," ;    // ����敪 ����
             sBuf = sBuf + Trim(SGr1->Cells[28][i]) +  ",'";    // ˽ĸ��ё��萔
             sBuf = sBuf + FormatDateTime("yyyymmdd",Date())               + "','";    // �ύX��
             sBuf = sBuf + FormatDateTime("hhmm",TDateTime::CurrentTime()) + "'," ;    // �ύX����
             sBuf = sBuf + IntToStr(USER_COD)                              + ")" ;    // �X�V��

             Query1->SQL->Add(sBuf);

             // �₢�������̎��s
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

             // �R�~�b�g
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

     // �f�[�^�C���̏ꍇ
     if( bUpdate == true ){

         // �u�C���O�̑���f�[�^�i�C���O�̓��t������j�������w���f�[�^�C����i�_�~�[���t���ցj
         //   ��KM01,KD01,KD02�`KDA1,KDA2�ɐݒ肵�܂��v
         if( SubSetOldValue( NowKey, sDummyDate) == false ){
             ProgressBar1->Visible = false;
             return(false);
         }

         // �u�_�~�[���t�Ŋ������������w���f�[�^�iKD01�`KA02���܂ށj��{���̑������Update���܂��v
         if( SubMoveKM01( NowKey, sDummyDate) == false ){
             ProgressBar1->Visible = false;
             return(false);
         }
     }

     ProgressBar1->Visible = false;
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ۑ������t���O
     DataSave = false;

     return(true);
}


//---------------------------------------------------------------------------
// �u�C���O�̑���f�[�^�i�C���O�̓��t������j�������w���f�[�^�C����i�_�~�[���t���ցj
//   ��KM01,KD01,KD02�`KDA1,KDA2�ɐݒ肵�܂��v
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


     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "����ς݃f�[�^�̍Ĕz�u���ł��D�D�D���΂炭���҂��������B";
     ProgressBar1->Min = 0;
     ProgressBar1->Max = ProgressBar1->Max * 10;
     ProgressBar1->Position = 0;
     SBr1->Update();

     // �V���������w���f�[�^����s�Â��[�v���A�Â������w���f�[�^���瑪��l���R�s�[���܂��B
     Query1->Close();              // Initial Query
     Query1->SQL->Clear();         // Initial Query
     sBuf = "select TOLEY_NO,SAMPLE_P,DTKSHIN,LOTNO,SK_LD_LNG,SK_BURASI,SK_BURASIT,";
     sBuf = sBuf + "SK_LD_TR,SK_LD_HP,SK_BOTAI,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,";
     sBuf = sBuf + "SK_KOYU,SK_MAGE,SK_MAGEG,SK_ZAKUT,HIST_SOKUT";
     sBuf = sBuf + " from KM01";
     sBuf = sBuf + " where KENSA_YMD like '" + sYMD_DMY + "'";
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

          // �V���������w���f�[�^�̏����擾���܂��B
          iTOLEY_NO   = Query1->Fields->Fields[0]->AsInteger;     // �g���[NO
          iSAMPLE_P   = Query1->Fields->Fields[1]->AsInteger;     // �T���v�����O�|�W�V����
          sDTKSHIN    = Query1->Fields->Fields[2]->AsString;      // ���Ӑ�i��
          sLOTNO      = Query1->Fields->Fields[3]->AsString;      // ���b�gNO
          iHIST_SOKUT = Query1->Fields->Fields[18]->AsInteger;    // �q�X�g�O�������萔
          if( iHIST_SOKUT > 0 ){
              iSEQ_NO ++ ;
          }

          // KD01�`KDA1,KDC1�܂ł����[�v���e����l�𕡎ʂ��܂��B
          for( i=0; i<=11; i++ ){
              ProgressBar1->Position++;
              switch(i){
                  case  0: // ���[�h���������@
                           sTableName1 = "KD01";
                           sTableName2 = "KD02";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[4]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  1: // �u���V�����@
                           sTableName1 = "KD11";
                           sTableName2 = "KD12";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[5]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  2: // �u���V�����@�c����
                           sTableName1 = "KD21";
                           sTableName2 = "KD22";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[6]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  3: // ���[�h����t��R
                           sTableName1 = "KD31";
                           sTableName2 = "KD32";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1V,SOKUTEI_2V,SOKUTEI_1A,SOKUTEI_2A";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[7]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  4: // ���[�h���������x
                           sTableName1 = "KD41";
                           sTableName2 = "KD42";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[8]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case  5: // ��̔�d
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
                  case  6: // �d�x
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
                  case  7: // �ŗL��R��
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
                  case  8: // �R�ܗ�
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
                  case  9: // ����
                           sTableName1 = "KD91";
                           sTableName2 = "KD92";
                           sGetField = ",SOKUTEI_SU";
                           sGetField = sGetField + ",SOKUTEI_1,SOKUTEI_2,SOKUTE_AVE";
                           sGetField = sGetField + ",ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,MEMO";
                           iSOKUT_SJ1 = Query1->Fields->Fields[17]->AsInteger;
                           iSOKUT_SJ2 = 0;
                           break;
                  case 10: // �q�X�g�O����
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
                  case 11: // �R�ܗ́i�����j
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

              // �Â������w���f�[�^���擾���܂��B
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

                  // ����ς݂̏ꍇ�́A����l��V��������f�[�^�ɕ��ʂ��܂��B
                  if( (iSOKUT_SJ1 > 0 && Query2->Fields->Fields[2]->AsInteger > 0 && i != 6 ) ||
                      ((iSOKUT_SJ1 > 0 || iSOKUT_SJ2 > 0 ||
                        Query2->Fields->Fields[2]->AsInteger > 0 ||
                        Query2->Fields->Fields[3]->AsInteger > 0 ) && i == 6 ) ){     // ���萔�Ŕ��f���܂�

                      // �₢�������̎��s
                      Query3->Close();              // Initial Query
                      Query3->SQL->Clear();         // Initial Query
                      sBuf = "UPDATE " + sTableName1;
                      switch(i){
                          case  0: // ���[�h���������@
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
                          case  1: // �u���V�����@
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
                          case  2: // �u���V�����@�c����
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
                          case  3: // ���[�h����t��R
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
                          case  4: // ���[�h���������x
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
                          case  5: // ��̔�d
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
                          case  6: // �d�x
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
                          case  7: // �ŗL��R��
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
                          case  8: // �R�ܗ�
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
                          case  9: // ����
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
                          case 10: // �q�X�g�O����
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
                          case 11: // �R�ܗ́i�����j
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

                      // ���萔�R�ȏ�̏ꍇ�́A��O���R�[�h(KDx2)���R�s�[���܂��B
                      if( (iSOKUT_SJ1 > 2 && Query2->Fields->Fields[2]->AsInteger > 2 && i != 6 ) ||
                          ((iSOKUT_SJ1 > 2 || iSOKUT_SJ2 > 2 ||
                            Query2->Fields->Fields[2]->AsInteger > 2 ||
                            Query2->Fields->Fields[3]->AsInteger > 2 ) && i == 6 ) ){     // ���萔�Ŕ��f���܂�

                          // �₢�������̎��s
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

                  // �J�[�\�������ɃZ�b�g����
                  Query2->Next();
              }
          }

          // �J�[�\�������ɃZ�b�g����
          Query1->Next();
     }

     return(true);
}


//---------------------------------------------------------------------------
// �u�_�~�[���t�Ŋ������������w���f�[�^�iKD01�`KDC2���܂ށj��{���̑������Update���܂��v
bool __fastcall TForm1::SubMoveKM01(AnsiString sYMD, AnsiString sYMD_DMY)
{

     int        i;
     AnsiString sTableName;
     AnsiString sBuf;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�V���������w���f�[�^�𐮗����ł��D�D�D���΂炭���҂��������B";
     ProgressBar1->Min = 0;
     ProgressBar1->Max = 25;
     ProgressBar1->Position = 1;
     SBr1->Update();

     // �{���̌������t���R�[�h�i�C���O�̃��R�[�h�j���폜���܂�
     Query1->Close();              // Initial Query
     Query1->SQL->Clear();         // Initial Query
     sBuf = "delete from KM01 where KENSA_YMD='" + sYMD + "'";
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
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


     // ���R�[�h�̌������t��{���̂��̂ɕύX���܂�
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

         // �₢�������̎��s
         Query1->Close();              // Initial Query
         Query1->SQL->Clear();         // Initial Query
         sBuf = "UPDATE " + sTableName + " SET KENSA_YMD='" + sYMD + "'";
         sBuf = sBuf + " WHERE KENSA_YMD='" + sYMD_DMY + "'";
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
// �u�H��NO���������܂��v
bool __fastcall TForm1::SubSearchKOKANBNG( AnsiString sKOKBNG )
{
     AnsiString sBuf;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�������ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
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
         // ���R�[�h���o
         Edt02->Text = Query1->Fields->Fields[0]->AsString;        // ���Ӑ溰��
         Edt03->Text = Query1->Fields->Fields[1]->AsString;        // ���Ӑ�i��
         Edt04->Text = Query1->Fields->Fields[2]->AsString;        // ���b�gNO
         Edt05->Text = Query1->Fields->Fields[3]->AsString;        // ���Еi��
         Edt06->Text = Query1->Fields->Fields[4]->AsString;        // �ގ�����
         Edt07->Text = Query1->Fields->Fields[5]->AsString;        // �ގ�����
         Edt08->Text = Query1->Fields->Fields[6]->AsString;        // ����
         SubSearchTKSHIN( Edt03->Text, true, false );

         SBr1->Panels->Items[0]->Text = "";
         SBr1->Update();
         return(true);
     }
     else{
         // ���R�[�h�Ȃ�
         SBr1->Panels->Items[0]->Text = "�Y������f�[�^��������܂���B";
         SBr1->Update();
         Beep();
         return(false);
     }

}


//---------------------------------------------------------------------------
// �u���Ӑ�i�Ԃ��������܂��v
bool __fastcall TForm1::SubSearchTKSHIN(AnsiString sTKSHIN, bool fSetEdit, bool fSetEditSecd)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
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
         // ���R�[�h�Ȃ�
         if( fSetEdit ){
             if( fSetEditSecd ){
                 Edt02->Text = "";    // ���Ӑ溰��
                 Edt05->Text = "";    // ���Еi��
                 Edt06->Text = "";    // �ގ�����
                 Edt07->Text = "";    // �ގ�����
             }
             Edt13->Tag  = 0;     // �`��敪
             Edt13->Text = "";    // �`��敪
             Edt14->Text = "";    // ����敪 ���[�h������
             Edt15->Text = "";    // ����敪 �u���V��
             Edt16->Text = "";    // ����敪 �u���V���c����
             Edt17->Text = "";    // ����敪 ���[�h�����t����R
             Edt18->Text = "";    // ����敪 ���[�h���������x
             Edt19->Text = "";    // ����敪 ��̔�d
             Edt20->Text = "";    // ����敪 �ŗL��R��
             Edt21->Text = "";    // ����敪 �Ȃ�����
             Edt22->Text = "";    // ����敪 �Ȃ���������
             Edt23->Text = "";    // ����敪 HsC�d�x�i���ʁj
             Edt24->Text = "";    // ����敪 HsC�d�x�i���ʁj
             Edt25->Text = "";    // ����敪 HsD�d�x�i���ʁj
             Edt26->Text = "";    // ����敪 HsD�d�x�i���ʁj
             Edt27->Text = "";    // ����敪 ����
             Edt28->Text = "";    // ˽ĸ��ё��萔
         }
         sSortKey = "";           // ��ķ�
         return(false);
     }
     else{
         // ���R�[�h���o
         if( fSetEdit ){
             if( fSetEditSecd ){
                 Edt02->Text = Query1->Fields->Fields[0]->AsString; // ���Ӑ溰��
                 Edt05->Text = Query1->Fields->Fields[1]->AsString; // ���Еi��
                 Edt06->Text = Query1->Fields->Fields[2]->AsString; // �ގ�����
                 Edt07->Text = Query1->Fields->Fields[3]->AsString; // �ގ�����
             }
             Edt13->Tag = Query1->Fields->Fields[5]->AsInteger;     // �`��敪
             switch( Edt13->Tag ){
                 case 1:   Edt13->Text = "���^";    break;
                 case 2:   Edt13->Text = "���^";    break;
                 case 3:   Edt13->Text = "��^";    break;
                 case 4:   Edt13->Text = "�~��";    break;
                 case 5:   Edt13->Text = "�R���~";  break;
             }
             Edt14->Text = Query1->Fields->Fields[6]->AsString;     // ����敪 ���[�h������
             Edt15->Text = Query1->Fields->Fields[7]->AsString;     // ����敪 �u���V��
             Edt16->Text = Query1->Fields->Fields[8]->AsString;     // ����敪 �u���V���c����
             Edt17->Text = Query1->Fields->Fields[9]->AsString;     // ����敪 ���[�h�����t��
             Edt18->Text = Query1->Fields->Fields[10]->AsString;    // ����敪 ���[�h���������x
             Edt19->Text = Query1->Fields->Fields[11]->AsString;    // ����敪 ��̔�d
             Edt24->Text = Query1->Fields->Fields[12]->AsString;    // ����敪 �ŗL��R��
             Edt25->Text = Query1->Fields->Fields[13]->AsString;    // ����敪 �Ȃ�����
             Edt26->Text = Query1->Fields->Fields[14]->AsString;    // ����敪 �Ȃ���������
             Edt20->Text = Query1->Fields->Fields[15]->AsString;    // ����敪 HsC�d�x�i���ʁj
             Edt21->Text = Query1->Fields->Fields[16]->AsString;    // ����敪 HsC�d�x�i���ʁj
             Edt22->Text = Query1->Fields->Fields[17]->AsString;    // ����敪 HsD�d�x�i���ʁj
             Edt23->Text = Query1->Fields->Fields[18]->AsString;    // ����敪 HsD�d�x�i���ʁj
             Edt27->Text = Query1->Fields->Fields[19]->AsString;    // ����敪 ����
             Edt28->Text = Query1->Fields->Fields[20]->AsString;    // ˽ĸ��ё��萔
         }
         sSortKey   = Query1->Fields->Fields[4]->AsString;          // ��ķ�
         sHistSokut = Query1->Fields->Fields[5]->AsString;          // ˽ĸ��ё��萔
         return(true);
     }

}


void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{

    // �X�e�[�^�X���b�Z�[�W
    if(SBr1->Panels->Items[0]->Text != ""){
       SBr1->Panels->Items[0]->Text = "";
       SBr1->Update();
    }

    // �ڰNO
    PnlTr->Caption = SGr1->Cells[0][ARow];
    // �����ݸ��߼޼��
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


    // �H��NO
    Edt01->Text = SGr1->Cells[2][ARow];
    // ���Ӑ溰��
    Edt02->Text = SGr1->Cells[3][ARow];
    // ���Ӑ�i��
    Edt03->Text = SGr1->Cells[4][ARow];
    // ���b�gNO
    Edt04->Text = SGr1->Cells[5][ARow];
    // ���Еi��
    Edt05->Text = SGr1->Cells[6][ARow];
    // �ގ�����
    Edt06->Text = SGr1->Cells[7][ARow];
    // �ގ�����
    Edt07->Text = SGr1->Cells[8][ARow];
    // ����
    Edt08->Text = SGr1->Cells[9][ARow];
    // �`��敪
    Edt13->Tag = StrToIntDef(SGr1->Cells[12][ARow],0);
    Edt13->Text = SGr1->Cells[13][ARow];
    // ����敪 ���[�h������
    Edt14->Text = SGr1->Cells[14][ARow];
    // ����敪 �u���V��
    Edt15->Text = SGr1->Cells[15][ARow];
    // ����敪 �u���V���c����
    Edt16->Text = SGr1->Cells[16][ARow];
    // ����敪 ���[�h�����t����R
    Edt17->Text = SGr1->Cells[17][ARow];
    // ����敪 ���[�h���������x
    Edt18->Text = SGr1->Cells[18][ARow];
    // ����敪 ��̔�d
    Edt19->Text = SGr1->Cells[19][ARow];
    // ����敪 �ŗL��R��
    Edt20->Text = SGr1->Cells[20][ARow];
    // ����敪 �Ȃ�����
    Edt21->Text = SGr1->Cells[21][ARow];
    // ����敪 �Ȃ���������
    Edt22->Text = SGr1->Cells[22][ARow];
    // ����敪 HsC�d�x�i���ʁj
    Edt23->Text = SGr1->Cells[23][ARow];
    // ����敪 HsC�d�x�i���ʁj
    Edt24->Text = SGr1->Cells[24][ARow];
    // ����敪 HsD�d�x�i���ʁj
    Edt25->Text = SGr1->Cells[25][ARow];
    // ����敪 HsD�d�x�i���ʁj
    Edt26->Text = SGr1->Cells[26][ARow];
    // ����敪 ����
    Edt27->Text = SGr1->Cells[27][ARow];
    // ˽ĸ��ё��萔
    Edt28->Text = SGr1->Cells[28][ARow];

}

//---------------------------------------------------------------------------
void __fastcall TForm1::SGr1KeyPress(TObject *Sender, char &Key)
{

     switch(Key)
     {
         // �O��
         case VK_UP:
         case VK_LEFT:  BtnF02Click(Sender);    break;

         // ����
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

    // �����\���
    if( EdtCOD->Focused() ){
        Form2->Tag = 1;
        BtnF01->Enabled = true;
        return;
    }
    // ���Ӑ溰��
    if( Edt02->Focused() ){
        Form2->Tag = 2;
        BtnF01->Enabled = true;
        return;
    }
    // ���Ӑ�i��
    if( Edt03->Focused() ){
        Form2->Tag = 3;
        BtnF01->Enabled = true;
        return;
    }
    // ���b�gNO
    if( Edt04->Focused() && (Edt03->Text.Length() > 0) ){
        Form2->Tag = 4;
        BtnF01->Enabled = true;
        return;
    }
    // ���Еi��
    if( Edt05->Focused() ){
        Form2->Tag = 5;
        BtnF01->Enabled = true;
        return;
    }
    // �ގ�����
    if( Edt06->Focused() ){
        Form2->Tag = 6;
        BtnF01->Enabled = true;
        return;
    }
    // �ގ�����
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

    // ���̑�
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

// �����\��N�����́����{�^���@2002/10/28 A.Tamura
void __fastcall TForm1::UpDownymdClick(TObject *Sender, TUDBtnType Button)
{

   try{

      //char str[256];
      //sprintf(str,"Max=%d Min=%d Pos=%d", UpDownymd->Max, UpDownymd->Min, UpDownymd->Position);

      // �����\��N����
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

     // ���萔�p�l����������
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
         // ����
         if( Panel3->Width - 17 > Panel17->Width + 1){
             SGr1->ColWidths[9] = 0;
             // �ގ�����
             if( Panel3->Width - 17> (Panel17->Width + Panel16->Width + 2) ){
                 SGr1->ColWidths[8] = 0;
                 // �ގ�����
                 if( Panel3->Width - 17> (Panel17->Width + Panel16->Width + Panel15->Width + 3) ){
                     SGr1->ColWidths[7] = 0;
                     // ���Еi��
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

     SGr1->ColWidths[6] = 0;    // ���Еi��
     SGr1->ColWidths[7] = 0;    // �ގ�����
     SGr1->ColWidths[8] = 0;    // �ގ�����
     SGr1->ColWidths[9] = 0;    // ����

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

     // ���萔�p�l����������
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

     SGr1->ColWidths[6] = Panel14->Width;    // ���Еi��
     SGr1->ColWidths[7] = Panel15->Width;    // �ގ�����
     SGr1->ColWidths[8] = Panel16->Width;    // �ގ�����
     SGr1->ColWidths[9] = Panel17->Width;    // ����

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


   //�Œ�Z���̔w�i�F���Z�b�g
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
   //   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //�I������Ă���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdSelected)){
       SGr1->Canvas->Brush->Color= clHighlight;
   }
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else{
       //if( SGr1->Cells[1][ARow] == 6 )
       SGr1->Canvas->Brush->Color= SGr1->Color;
   }
   //�w�i�F�ŏ���
   SGr1->Canvas->FillRect(Rect);

   //�Œ�Z���̗��̘g��`��
   if(SGr1->Ctl3D&&State.Contains(gdFixed))
       DrawEdge(SGr1->Canvas->Handle,&r,BDR_RAISEDINNER,BF_RECT);

   //�t�H�[�J�X�̂���Z���̕����F���Z�b�g
   if(State.Contains(gdFocused)){
//       SGr1->Canvas->Font->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlightText: SGr1->Font->Color;
//       //�t�H�[�J�X�g��`��
//       DrawFocusRect(SGr1->Canvas->Handle,&r);
   }
   //�I������Ă���Z���̕����F���Z�b�g
   else if(State.Contains(gdSelected))
       SGr1->Canvas->Font->Color= clHighlightText;
//   //�ߋ��̗����f�[�^�̏ꍇ�̕����F���Z�b�g
//   else if( SGr1->Cells[1][ARow].ToIntDef(0) == 2 )
//       SGr1->Canvas->Font->Color = clSilver;
   //���ʂ̃Z���̕����F���Z�b�g
   else
       SGr1->Canvas->Font->Color= SGr1->Font->Color;

   //�e�L�X�g�\���̈�̐ݒ�
   InflateRect(&r,-2,-2);

   //�e�L�X�g�̕\��
   DrawText(SGr1->Canvas->Handle,SGr1->Cells[ACol][ARow].c_str(),-1,&r,0); //�E��

//   if( ACol < 0 || ACol > 10 ) return;
//   if( SGr1->Cells[10][ARow].ToIntDef(0) > 0 ){
//       SGr1->Canvas->Font->Color = clYellow;
//   }

}
//---------------------------------------------------------------------------

