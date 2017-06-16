//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
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

     Database1->Open();

     // �O���b�h�̏�����
     SGr1->ColWidths[0] = Panel8->Width;
     SGr1->ColWidths[1] = Panel19->Width;
     SGr1->ColWidths[2] = Panel12->Width;
     SGr1->ColWidths[3] = Panel13->Width;
     SGr1->ColWidths[4] = Panel22->Width;
     SGr1->ColWidths[5] = Panel14->Width;
     SGr1->ColWidths[6] = Panel15->Width;
     SGr1->ColWidths[7] = Panel18->Width;
     SGr1->ColWidths[8] = Panel25->Width;
     SGr1->ColWidths[9] = Panel17->Width;
     //2002/11/11 E.Takase
     SGr1->ColWidths[10] = Panel3->Width;

     //2002/11/11 E.Takase
     //for( i=10; i<64; i++) {
     for( i=11; i<69; i++) {
         SGr1->ColWidths[i] = 0;
     }

     // �e�R���g���[���̏�����
     InitEdt();

     // �{�^���̏�����
     BtnF01->Enabled = false;
     BtnF02->Enabled = false;
     BtnF03->Enabled = false;
     BtnF04->Enabled = false;
     BtnF05->Enabled = true;
     BtnF06->Enabled = false;
     BtnF07->Enabled = true;
     BtnF08->Enabled = false;
     BtnF09->Enabled = false;
     BtnF10->Enabled = false;
     BtnF11->Enabled = false;
     BtnF12->Enabled = true;

}


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
    Form2->ShowModal();
}


//---------------------------------------------------------------------------
// �u�e�Q�F�O���v
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
    if(SGr1->Row > 0){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// �u�e�R�F�����v
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// �u�e�T�F��ʈ���v
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;
    Form1->Print();
}


//---------------------------------------------------------------------------
// �u�e�U�F����v
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;
    Form3->QuickRep1->Preview();
//    Form3->QuickRep1->Print();
}


//---------------------------------------------------------------------------
// �u�e�V�F�����v
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int i;
     int cnt;
     int iRow;
     AnsiString sBuf;


     if( !BtnF07->Enabled )    return;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�������ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "select DTKSCOD,DTKSHIN,HINBAN,ZISNAM,ZISCOD,SYOSCOD,SORTKEY,KEIJKBN,";
     sBuf = sBuf + "SK_LD_LNG, SK_BURASI, SK_BURASIT, SK_LD_TR, SK_LD_HP, SK_BOTAI, SK_KOYU, ";
     sBuf = sBuf + "SK_MAGE, SK_HSC_A, SK_HSC_S, SK_HSD_A, SK_HSD_S, SK_ZAKUT, HIST_SOKUT, ";
     sBuf = sBuf + "HIST_KIKAK, HIST_MIN, HIST_MAX, LD_LNG_MIN, LD_LNG_MAX, BURASI_MIN, BURASI_MAX, ";
     sBuf = sBuf + "BURASIT_MIN, BURASIT_MAX, LD_TR_DENA, LD_TR_DENR, LD_TR_TIME, LD_HP_KYO, ";
     sBuf = sBuf + "LD_HP_TAN, LD_HP_SPD, BOTAI_MIN, BOTAI_MAX, KOYU_MIN, KOYU_MAX, KOYU_DEN, ";
     sBuf = sBuf + "KOYU_PRO, MAGE_MIN, MAGE_MAX, MAGE_TAN, MAGE_SPAN, HSC_A_MIN, HSC_A_MAX, ";
     sBuf = sBuf + "HSC_S_MIN, HSC_S_MAX, HSD_A_MIN, HSD_A_MAX, HSD_S_MIN, HSD_S_MAX, ZAKUT_MIN, ";
     sBuf = sBuf + "ZAKUT_MAX, ADDYMD, UPDYMD, UPDCNT, DTKSNAM, LD_TR_TYPE, REVCNT, UPDCHR, ";
     sBuf = sBuf + "MEMO, ADDTIM, UPDTIM,";
     sBuf = sBuf + "SK_MAGEG, MAGEG_MIN, MAGEG_MAX, MAGEG_TAN, MAGEG_SPAN ";
     sBuf = sBuf + " from KM02";


     if( EdtCOD1->Text != "" || EdtCOD2->Text != "" || EdtCOD3->Text != "" || EdtCOD4->Text != "" ){
         sBuf += " where";
         cnt = 0;
         if( EdtCOD1->Text != "" ){
             // ���Ӑ�R�[�h
             sBuf += " DTKSCOD like '";
             sBuf += EdtCOD1->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD2->Text != "" ){
             // ���Ӑ�i��
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " DTKSHIN like '";
             sBuf += EdtCOD2->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD3->Text != "" ){
             // ���Еi��
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " HINBAN like '";
             sBuf += EdtCOD3->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         if( EdtCOD4->Text != "" ){
             // �ގ�����
             if( cnt >= 1 ) sBuf += " and";
             sBuf += " ZISNAM like '";
             sBuf += EdtCOD4->Text ;
             sBuf += "%'";
             cnt += 1;
         }
         //2002/11/11 E.Takase
         //������\�����邩�H
         if ( CheckBoxRireki->Checked == false) {
            if( cnt >= 1 ) sBuf += " and";
            sBuf += " REVCNT = 0";
         }

     } else {

         //2002/11/11 E.Takase
         //������\�����邩�H
         if ( CheckBoxRireki->Checked == false) {
            sBuf += " Where";
            sBuf += " REVCNT = 0";
         }

     }


     sBuf = sBuf + " order by DTKSCOD, DTKSHIN, REVCNT";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     SGr1->Tag = 1;

     iRow = 0;
     while( !Query1->Eof ){

          // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // �O���b�h�Ƀf�[�^���Z�b�g���܂��B

          // NO
          sBuf = iRow + 1;
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
          // ���Ӑ�R�[�h
          SGr1->Cells[1][iRow] = Query1->Fields->Fields[0]->AsString;
          // ���Ӑ�i��
          SGr1->Cells[2][iRow] = Query1->Fields->Fields[1]->AsString;
          // ���Еi��
          SGr1->Cells[3][iRow] = Query1->Fields->Fields[2]->AsString;
          // �ގ�����
          SGr1->Cells[4][iRow] = Query1->Fields->Fields[3]->AsString;
          // �ގ��R�[�h
          SGr1->Cells[5][iRow] = Query1->Fields->Fields[4]->AsString;
          // �Đ��R�[�h
          SGr1->Cells[6][iRow] = Query1->Fields->Fields[5]->AsString;
          // �\�[�g�j����
          sBuf = IntToStr(Query1->Fields->Fields[6]->AsInteger);
          SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;
          // �`��敪
          switch( Query1->Fields->Fields[7]->AsInteger ){
              case  5: sBuf = "�R���~"; break;  //2002.10.21 Add By Takase
              case  4: sBuf = "�~��";   break;
              case  3: sBuf = "��^";   break;
              case  2: sBuf = "���^";   break;
              case  1:
              default: sBuf = "���^";   break;
          }
          SGr1->Cells[8][iRow] = sBuf;

          // ����敪�@������
          //2002/11/11 E.Takase SGr1->Cells[10][iRow] = Query1->Fields->Fields[8]->AsString;
          SGr1->Cells[64][iRow] = Query1->Fields->Fields[8]->AsString;
          // ����敪�@�u���V��
          SGr1->Cells[11][iRow] = Query1->Fields->Fields[9]->AsString;
          // ����敪�@�u���V���c����
          SGr1->Cells[12][iRow] = Query1->Fields->Fields[10]->AsString;
          // ����敪�@����t��R
          SGr1->Cells[13][iRow] = Query1->Fields->Fields[11]->AsString;
          // ����敪�@���������x
          SGr1->Cells[14][iRow] = Query1->Fields->Fields[12]->AsString;
          // ����敪�@��̔�d
          SGr1->Cells[15][iRow] = Query1->Fields->Fields[13]->AsString;
          // ����敪�@�ŗL��R
          SGr1->Cells[16][iRow] = Query1->Fields->Fields[14]->AsString;
          // ����敪�@�R�ܗ�
          SGr1->Cells[17][iRow] = Query1->Fields->Fields[15]->AsString;
          // ����敪�@HsC�d�x�i���ʁj
          SGr1->Cells[18][iRow] = Query1->Fields->Fields[16]->AsString;
          // ����敪�@HsC�d�x�i���ʁj
          SGr1->Cells[19][iRow] = Query1->Fields->Fields[17]->AsString;
          // ����敪�@HsD�d�x�i���ʁj
          SGr1->Cells[20][iRow] = Query1->Fields->Fields[18]->AsString;
          // ����敪�@HsD�d�x�i���ʁj
          SGr1->Cells[21][iRow] = Query1->Fields->Fields[19]->AsString;
          // ����敪�@����
          SGr1->Cells[22][iRow] = Query1->Fields->Fields[20]->AsString;
          // �q�X�g�O�����i���萔�j
          SGr1->Cells[23][iRow] = Query1->Fields->Fields[21]->AsString;
          // �q�X�g�O�����i�K�i�j
          SGr1->Cells[24][iRow] = Query1->Fields->Fields[22]->AsString;
          // �q�X�g�O�����i�����j
          SGr1->Cells[25][iRow] = Query1->Fields->Fields[23]->AsString;
          // �q�X�g�O�����i����j
          SGr1->Cells[26][iRow] = Query1->Fields->Fields[24]->AsString;
          // ���[�h�������i�����j
          SGr1->Cells[27][iRow] = Query1->Fields->Fields[25]->AsString;
          // ���[�h�������i����j
          SGr1->Cells[28][iRow] = Query1->Fields->Fields[26]->AsString;
          // �u���V���i�����j
          SGr1->Cells[29][iRow] = Query1->Fields->Fields[27]->AsString;
          // �u���V���i����j
          SGr1->Cells[30][iRow] = Query1->Fields->Fields[28]->AsString;
          // �u���V���c�����i�����j
          SGr1->Cells[31][iRow] = Query1->Fields->Fields[29]->AsString;
          // �u���V���c�����i����j
          SGr1->Cells[32][iRow] = Query1->Fields->Fields[30]->AsString;
          // ���[�h��t��R�i�d���j
          SGr1->Cells[33][iRow] = Query1->Fields->Fields[31]->AsString;
          // ���[�h��t��R�i�d���j
          SGr1->Cells[34][iRow] = Query1->Fields->Fields[32]->AsString;
          // ���[�h��t��R�i���ԁj
          SGr1->Cells[35][iRow] = Query1->Fields->Fields[33]->AsString;
          // ���[�h���������x
          SGr1->Cells[36][iRow] = Query1->Fields->Fields[34]->AsString;
          // ���[�h���������x�i�P�ʁj
          SGr1->Cells[37][iRow] = Query1->Fields->Fields[35]->AsString;
          // ���[�h���������x�i���x�j
          SGr1->Cells[38][iRow] = Query1->Fields->Fields[36]->AsString;
          // ��̔�d�i�����j
          SGr1->Cells[39][iRow] = Query1->Fields->Fields[37]->AsString;
          // ��̔�d�i����j
          SGr1->Cells[40][iRow] = Query1->Fields->Fields[38]->AsString;
          // �ŗL��R���i�����j
          SGr1->Cells[41][iRow] = Query1->Fields->Fields[39]->AsString;
          // �ŗL��R���i����j
          SGr1->Cells[42][iRow] = Query1->Fields->Fields[40]->AsString;
          // �ŗL��R���i�d���j
          SGr1->Cells[43][iRow] = Query1->Fields->Fields[41]->AsString;
          // �ŗL��R���i�v���[�u�j
          SGr1->Cells[44][iRow] = Query1->Fields->Fields[42]->AsString;
          // �Ȃ����x�i�����j
          SGr1->Cells[45][iRow] = Query1->Fields->Fields[43]->AsString;
          // �Ȃ����x�i����j
          SGr1->Cells[46][iRow] = Query1->Fields->Fields[44]->AsString;
          // �Ȃ����x�i�P�ʁj
          SGr1->Cells[47][iRow] = Query1->Fields->Fields[45]->AsString;
          // �Ȃ����x�i�X�p���j
          SGr1->Cells[48][iRow] = Query1->Fields->Fields[46]->AsString;
          // HsC�d�x ���ʁi�����j
          SGr1->Cells[49][iRow] = Query1->Fields->Fields[47]->AsString;
          // HsC�d�x ���ʁi����j
          SGr1->Cells[50][iRow] = Query1->Fields->Fields[48]->AsString;
          // HsC�d�x ���ʁi�����j
          SGr1->Cells[51][iRow] = Query1->Fields->Fields[49]->AsString;
          // HsC�d�x ���ʁi����j
          SGr1->Cells[52][iRow] = Query1->Fields->Fields[50]->AsString;
          // HsD�d�x ���ʁi�����j
          SGr1->Cells[53][iRow] = Query1->Fields->Fields[51]->AsString;
          // HsD�d�x ���ʁi����j
          SGr1->Cells[54][iRow] = Query1->Fields->Fields[52]->AsString;
          // HsD�d�x ���ʁi�����j
          SGr1->Cells[55][iRow] = Query1->Fields->Fields[53]->AsString;
          // HsD�d�x ���ʁi����j
          SGr1->Cells[56][iRow] = Query1->Fields->Fields[54]->AsString;
          // �����i�����j
          SGr1->Cells[57][iRow] = Query1->Fields->Fields[55]->AsString;
          // �����i����j
          SGr1->Cells[58][iRow] = Query1->Fields->Fields[56]->AsString;
          // �o�^��
          SGr1->Cells[59][iRow] = Query1->Fields->Fields[57]->AsString;
          // �ύX��
          SGr1->Cells[60][iRow] = Query1->Fields->Fields[58]->AsString;
          // �X�V��
          SGr1->Cells[61][iRow] = Query1->Fields->Fields[59]->AsString;
          // ���Ӑ於��
          SGr1->Cells[62][iRow] = Query1->Fields->Fields[60]->AsString;
          // ���[�h��t��R�iTYPE�j
          SGr1->Cells[63][iRow] = Query1->Fields->Fields[61]->AsString;

          // �X�V��
          //2002/11/19 E.Takase
          //�����ԍ����u0�v�Ȃ�o�^��
          //����ȊO�Ȃ�ύX����\��
          //if( SGr1->Cells[61][iRow] != "" ) {               // �X�V��
          //   if( StrToInt(SGr1->Cells[61][iRow]) > 0 )
          //      sBuf = SGr1->Cells[60][iRow];               // �ύX��
          //   else
          //      sBuf = SGr1->Cells[59][iRow];               // �o�^��
          //}
          //else{
          //   sBuf = SGr1->Cells[59][iRow];                  // �o�^��
          //}
          if( Trim(SGr1->Cells[60][iRow]) == "" ) {
             sBuf = SGr1->Cells[59][iRow];                    // �o�^��
          }
          else{
             sBuf = SGr1->Cells[60][iRow];                    // �ύX��
          }
          sBuf = sBuf.Insert("/",5);
          sBuf = sBuf.Insert("/",8);
          SGr1->Cells[9][iRow] = sBuf;

          //2002/11/11 E.Takase
          // �����ԍ�
          SGr1->Cells[10][iRow] = Query1->Fields->Fields[62]->AsString;
          // �X�V��
          SGr1->Cells[65][iRow] = Query1->Fields->Fields[63]->AsString;
          // ���l
          SGr1->Cells[66][iRow] = Query1->Fields->Fields[64]->AsString;
          // �o�^����
          SGr1->Cells[67][iRow] = Query1->Fields->Fields[65]->AsString;
          // �X�V����
          SGr1->Cells[68][iRow] = Query1->Fields->Fields[66]->AsString;

          //2002/12/04 E.Takase
          // ����敪�@�����Ȃ����x
          SGr1->Cells[69][iRow] = Query1->Fields->Fields[67]->AsString;
          // �����Ȃ����x�i�����j
          SGr1->Cells[70][iRow] = Query1->Fields->Fields[68]->AsString;
          // �����Ȃ����x�i����j
          SGr1->Cells[71][iRow] = Query1->Fields->Fields[69]->AsString;
          // �����Ȃ����x�i�P�ʁj
          SGr1->Cells[72][iRow] = Query1->Fields->Fields[70]->AsString;
          // �����Ȃ����x�i�X�p���j
          SGr1->Cells[73][iRow] = Query1->Fields->Fields[71]->AsString;

          // �J�[�\�������ɃZ�b�g����
          Query1->Next();

          iRow += 1;
     }

     SGr1->Tag = 0;

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

     /*
     if( iRow == 0 ){

         // �������ʊY���Ȃ��̏ꍇ
         EdtCOD1->SetFocus();

         // �{�^���̏�����
         BtnF01->Enabled = false;
         BtnF02->Enabled = false;
         BtnF03->Enabled = false;
         BtnF04->Enabled = false;
         BtnF05->Enabled = true;
         BtnF06->Enabled = false;
         BtnF07->Enabled = true;
         BtnF08->Enabled = false;
         BtnF09->Enabled = false;
         BtnF10->Enabled = false;
         BtnF11->Enabled = false;
         BtnF12->Enabled = true;

     }
     else{
     */
         // �O���b�h��I��
         SGr1SelectCell( Sender, 1, 0, true);
         SGr1->Row = 0;
         SGr1->SetFocus();

         // �V�����g�����U�N�V�������J�n
         if( Database1->InTransaction == false ){
             Database1->StartTransaction();
             DataSave = false;
         }

         // �{�^���̏�����
         BtnF01->Enabled = false;
         BtnF02->Enabled = true;
         BtnF03->Enabled = true;
         BtnF04->Enabled = false;
         BtnF05->Enabled = true;
         BtnF06->Enabled = true;
         BtnF07->Enabled = true;
         BtnF08->Enabled = true;
         BtnF09->Enabled = true;
         BtnF10->Enabled = true;
         BtnF11->Enabled = true;
         BtnF12->Enabled = true;

     //}

     // �X�e�[�^�X���b�Z�[�W
     sBuf = FormatFloat( "�������� 0���ł��B", iRow );
     SBr1->Panels->Items[0]->Text = sBuf;
     SBr1->Update();

}


//---------------------------------------------------------------------------
// �u�e�W�F�V�K�o�^�v
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
     int i;
     bool fNG;
     AnsiString sBuf;

     if( !BtnF08->Enabled )    return;

     if( Edt03->Text == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�K�{���ڂ���͂��ĉ������B";
        SBr1->Update();
        Beep();
        return;
     }

     // �l�`�F�b�N
	 fNG = false;
     if( !(Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0) && Edt10->Value > 0 )	fNG = true;
	 if( !(EdtA1->Value < EdtA2->Value) && ChkBoxA->Checked )   fNG = true;
     if( !(EdtB1->Value < EdtB2->Value) && ChkBoxB->Checked )	fNG = true;
     if( !(EdtC1->Value < EdtC2->Value) && ChkBoxC->Checked )	fNG = true;
     if( !(EdtD1->Value < EdtD2->Value) && ChkBoxD->Checked )	fNG = true;
     if( !(EdtG1->Value < EdtG2->Value) && ChkBoxG->Checked )	fNG = true;
     if( !(EdtH1->Value < EdtH2->Value) && ChkBoxH->Checked )	fNG = true;
     if( !(EdtI1->Value < EdtI2->Value) && ChkBoxI->Checked )	fNG = true;
     if( !(EdtJ1->Value < EdtJ2->Value) && ChkBoxJ->Checked )	fNG = true;
     if( !(EdtK1->Value < EdtK2->Value) && ChkBoxK->Checked )	fNG = true;
     if( !(EdtL1->Value < EdtL2->Value) && ChkBoxL->Checked )	fNG = true;
     if( !(EdtM1->Value < EdtM2->Value) && ChkBoxM->Checked )	fNG = true;
     if( fNG == true ){
        SBr1->Panels->Items[0]->Text = "�K�i�͈̔͂��w�肵�����Ă��������B";
        SBr1->Update();
        Beep();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
	 if( Edt01->Text != "" ) Edt01->Text = StrReplace(Edt01->Text , "'", "_");
	 if( Edt02->Text != "" ) Edt02->Text = StrReplace(Edt02->Text , "'", "_");
	 if( Edt03->Text != "" ) Edt03->Text = StrReplace(Edt03->Text , "'", "_");
	 if( Edt04->Text != "" ) Edt04->Text = StrReplace(Edt04->Text , "'", "_");
     if( Edt05->Text != "" ) Edt05->Text = StrReplace(Edt05->Text , "'", "_");
	 if( Edt06->Text != "" ) Edt06->Text = StrReplace(Edt06->Text , "'", "_");

     if( Edt01->Text == "" )  KM02.DTKSCOD = " ";               // ���Ӑ�R�[�h
     else                     KM02.DTKSCOD = Edt01->Text ;      // ���Ӑ�R�[�h
     if( Edt02->Text == "" )  KM02.DTKSNAM = " " ;              // ���Ӑ於��
     else                     KM02.DTKSNAM = Edt02->Text ;      // ���Ӑ於��
     if( Edt03->Text == "" )  KM02.DTKSHIN = " " ;              // ���Ӑ�i��
     else                     KM02.DTKSHIN = Edt03->Text ;      // ���Ӑ�i��
     if( Edt04->Text == "" )  KM02.HINBAN  = " " ;              // ���Еi��
     else                     KM02.HINBAN  = Edt04->Text ;      // ���Еi��
     if( Edt05->Text == "" )  KM02.ZISNAM  = " " ;              // �ގ�����
     else                     KM02.ZISNAM  = Edt05->Text ;      // �ގ�����
     if( Edt06->Text == "" )  KM02.ZISCOD  = " " ;              // �ގ��R�[�h
     else                     KM02.ZISCOD  = Edt06->Text ;      // �ގ��R�[�h
     if( Edt07->Text == "" )  KM02.SYOSCOD = " " ;              // �Đ��R�[�h
     else                     KM02.SYOSCOD = Edt07->Text ;      // �Đ��R�[�h

     KM02.SORTKEY = Edt08->Value ;                              // �\�[�g�L�[
     KM02.KEIJKBN = 0            ;                              // �`��敪
     if( ComBox09->Text == "���^" ) KM02.KEIJKBN = 2;
     if( ComBox09->Text == "��^" ) KM02.KEIJKBN = 3;
     if( ComBox09->Text == "�~��" ) KM02.KEIJKBN = 4;
     if( ComBox09->Text == "�R���~" ) KM02.KEIJKBN = 5;         // 2002.10.21 Add By takase
     if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
     if( ChkBoxA->Checked ) KM02.SK_LD_LNG  = ChkEdtA->Value ;  // ����敪�@������
     else                   KM02.SK_LD_LNG  = 0 ;
     if( ChkBoxB->Checked ) KM02.SK_BURASI  = ChkEdtB->Value ;  // ����敪�@�u���V��
     else                   KM02.SK_BURASI  = 0 ;
     if( ChkBoxC->Checked ) KM02.SK_BURASIT = ChkEdtC->Value ;  // ����敪�@�u���V���c����
     else                   KM02.SK_BURASIT = 0 ;
     if( ChkBoxD->Checked ) KM02.SK_BOTAI   = ChkEdtD->Value ;  // ����敪�@��̔�d
     else                   KM02.SK_BOTAI   = 0  ;
     if( ChkBoxE->Checked ) KM02.SK_LD_HP   = ChkEdtE->Value ;  // ����敪�@���������x
     else                   KM02.SK_LD_HP   = 0 ;
     if( ChkBoxF->Checked ) KM02.SK_LD_TR   = ChkEdtF->Value ;  // ����敪�@����t��R
     else                   KM02.SK_LD_TR   = 0 ;
     if( ChkBoxG->Checked ) KM02.SK_KOYU    = ChkEdtG->Value ;  // ����敪�@�ŗL��R
     else                   KM02.SK_KOYU    = 0 ;
     if( ChkBoxH->Checked ) KM02.SK_MAGE    = ChkEdtH->Value ;  // ����敪�@�R�ܗ�
     else                   KM02.SK_MAGE    = 0 ;
     if( ChkBoxI->Checked ) KM02.SK_HSC_A   = ChkEdtI->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_A   = 0 ;
     if( ChkBoxJ->Checked ) KM02.SK_HSC_S   = ChkEdtJ->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_S   = 0 ;
     if( ChkBoxK->Checked ) KM02.SK_HSD_A   = ChkEdtK->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_A   = 0 ;
     if( ChkBoxL->Checked ) KM02.SK_HSD_S   = ChkEdtL->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_S   = 0 ;
     if( ChkBoxM->Checked ) KM02.SK_ZAKUT   = ChkEdtM->Value ;  // ����敪�@����
     else                   KM02.SK_ZAKUT   = 0 ;
     KM02.HIST_SOKUT  = Edt10->Value ;                          // �q�X�g�O�����i���萔�j
     KM02.HIST_KIKAK  = 0            ;                          // �q�X�g�O�����i�K�i�j
     if( ComBox11->Text  == "����" ) KM02.HIST_KIKAK = 2;
     if( ComBox11->Text  == "���" ) KM02.HIST_KIKAK = 3;
     if( KM02.HIST_KIKAK == 0      ) KM02.HIST_KIKAK = 1;
     KM02.HIST_MIN    = Edt12->Value ;                          // �q�X�g�O�����i�����j
     KM02.HIST_MAX    = Edt13->Value ;                          // �q�X�g�O�����i����j
     KM02.LD_LNG_MIN  = EdtA1->Value ;                          // ���[�h�������i�����j
     KM02.LD_LNG_MAX  = EdtA2->Value ;                          // ���[�h�������i����j
     KM02.BURASI_MIN  = EdtB1->Value ;                          // �u���V���i�����j
     KM02.BURASI_MAX  = EdtB2->Value ;                          // �u���V���i����j
     KM02.BURASIT_MIN = EdtC1->Value ;                          // �u���V���c�����i�����j
     KM02.BURASIT_MAX = EdtC2->Value ;                          // �u���V���c�����i����j
     KM02.BOTAI_MIN   = EdtD1->Value ;                          // ��̔�d�i�����j
     KM02.BOTAI_MAX   = EdtD2->Value ;                          // ��̔�d�i����j
     KM02.LD_HP_KYO   = EdtE1->Value ;                          // ���[�h���������x
     KM02.LD_HP_TAN   = 0;                                      // ���[�h���������x�i�P�ʁj
     sBuf = ComBoxE2->Text.UpperCase();
     if( sBuf[1] == 'K'      ) KM02.LD_HP_TAN = 1;              // Kgf
     if( KM02.LD_HP_TAN == 0 ) KM02.LD_HP_TAN = 2;              // N
     KM02.LD_HP_SPD   = EdtE3->Value ;                          // ���[�h���������x�i���x�j
     KM02.LD_TR_DENA  = EdtF1->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_DENR  = EdtF2->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_TIME  = EdtF3->Value ;                          // ���[�h��t��R�i���ԁj
     if( EdtF4->Text == "" )  KM02.LD_TR_TYPE = " " ;           // ���[�h��t��R�iTYPE�j
     else                     KM02.LD_TR_TYPE = EdtF4->Text ;
     KM02.KOYU_MIN    = EdtG1->Value ;                          // �ŗL��R���i�����j
     KM02.KOYU_MAX    = EdtG2->Value ;                          // �ŗL��R���i����j
     KM02.KOYU_DEN    = EdtG3->Value ;                          // �ŗL��R���i�d���j
     KM02.KOYU_PRO    = EdtG4->Value ;                          // �ŗL��R���i�v���[�u�j
     KM02.MAGE_MIN    = EdtH1->Value ;                          // �Ȃ����x�i�����j
     KM02.MAGE_MAX    = EdtH2->Value ;                          // �Ȃ����x�i����j
     KM02.MAGE_TAN    = 0;                                      // �Ȃ����x�i�P�ʁj
     sBuf = ComBoxH3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGE_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGE_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGE_TAN = 3;                  // MPa
     if( KM02.MAGE_TAN == 0          ) KM02.MAGE_TAN = 4;                  // N/mm2
     KM02.MAGE_SPAN   = EdtH4->Value ;                          // �Ȃ����x�i�X�p���j
     KM02.HSC_A_MIN   = EdtI1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_A_MAX   = EdtI2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSC_S_MIN   = EdtJ1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_S_MAX   = EdtJ2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSD_A_MIN   = EdtK1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_A_MAX   = EdtK2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.HSD_S_MIN   = EdtL1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_S_MAX   = EdtL2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.ZAKUT_MIN   = EdtM1->Value ;                          // �����i�����j
     KM02.ZAKUT_MAX   = EdtM2->Value ;                          // �����i����j
     KM02.ADDYMD      = FormatDateTime("yyyymmdd",Date());                // �o�^��
     KM02.ADDTIM      = FormatDateTime("hhmm",TDateTime::CurrentTime());  // �o�^����
     KM02.UPDYMD      = "";                                     // �ύX��
     KM02.UPDTIM      = "";                                     // �ύX����
     KM02.UPDCHR      = USER_COD;                               // �X�V��
     KM02.UPDCNT      = 0;                                      // �X�V��

     //2002/11/11 E.Takase
     KM02.REVCNT      = 0;                                      // �X�V��
     KM02.MEMO        = Trim(EdtMEMO->Text) ;                   // ���l

     //2002/12/05 E.Takase
     if( ChkBoxN->Checked ) KM02.SK_MAGEG    = ChkEdtN->Value ;  // ����敪�@�����Ȃ����x
     else                   KM02.SK_MAGEG    = 0 ;
     KM02.MAGEG_MIN    = EdtN1->Value ;                          // �����Ȃ����x�i�����j
     KM02.MAGEG_MAX    = EdtN2->Value ;                          // �����Ȃ����x�i����j
     KM02.MAGEG_TAN    = 0;                                      // �����Ȃ����x�i�P�ʁj
     sBuf = ComBoxN3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGEG_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGEG_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGEG_TAN = 3;                  // MPa
     //2003/07/22 E.Takase �P�ʂɁuN�v�ǉ�
     if( sBuf[1] == 'N'              ) KM02.MAGEG_TAN = 5;                  // N
     if( KM02.MAGEG_TAN == 0          ) KM02.MAGEG_TAN = 4;                  // N/mm2
     KM02.MAGEG_SPAN   = EdtN4->Value ;                          // �����Ȃ����x�i�X�p���j

     // AddData
     if( AddData() == False ){
        return;
     }

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = SGr1->RowCount ;                                // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
     sBuf = KM02.DTKSCOD;                              		// ���Ӑ�R�[�h
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.DTKSHIN;                              		// ���Ӑ�i��
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.HINBAN;                               		// ���Еi��
     SGr1->Cells[3][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ZISNAM;                               		// �ގ�����
     SGr1->Cells[4][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ZISCOD;                               		// �ގ��R�[�h
     SGr1->Cells[5][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.SYOSCOD;                              		// �Đ��R�[�h
     SGr1->Cells[6][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SORTKEY);                         // �\�[�g�L�[
     SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;
     if( KM02.KEIJKBN == 1 ) sBuf = "���^";                 // �`��敪
     if( KM02.KEIJKBN == 2 ) sBuf = "���^";
     if( KM02.KEIJKBN == 3 ) sBuf = "��^";
     if( KM02.KEIJKBN == 4 ) sBuf = "�~��";
     if( KM02.KEIJKBN == 5 ) sBuf = "�R���~";               //2002.10.21 Add By Takase
     SGr1->Cells[8][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ADDYMD;                               		// �X�V��
     sBuf = sBuf.Insert("/",5);
     sBuf = sBuf.Insert("/",8);
     SGr1->Cells[9][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_LNG);                       // ����敪�@������
     //2002/11/11 E.Takase SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;
     SGr1->Cells[64][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASI);                       // ����敪�@�u���V��
     SGr1->Cells[11][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASIT);                      // ����敪�@�u���V���c����
     SGr1->Cells[12][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_TR);                        // ����敪�@����t��R
     SGr1->Cells[13][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_HP);                        // ����敪�@���������x
     SGr1->Cells[14][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_BOTAI);                        // ����敪�@��̔�d
     SGr1->Cells[15][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_KOYU);                         // ����敪�@�ŗL��R
     SGr1->Cells[16][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_MAGE);                         // ����敪�@�R�ܗ�
     SGr1->Cells[17][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_A);                        // ����敪�@HsC�d�x�i���ʁj
     SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_S);                        // ����敪�@HsC�d�x�i���ʁj
     SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_A);                        // ����敪�@HsD�d�x�i���ʁj
     SGr1->Cells[20][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_S);                        // ����敪�@HsD�d�x�i���ʁj
     SGr1->Cells[21][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.SK_ZAKUT);                        // ����敪�@����
     SGr1->Cells[22][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HIST_SOKUT);                      // �q�X�g�O�����i���萔�j
     SGr1->Cells[23][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HIST_KIKAK);                      // �q�X�g�O�����i�K�i�j
     SGr1->Cells[24][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MIN);                      // �q�X�g�O�����i�����j
     SGr1->Cells[25][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MAX);                      // �q�X�g�O�����i����j
     SGr1->Cells[26][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MIN);                    // ���[�h�������i�����j
     SGr1->Cells[27][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MAX);                    // ���[�h�������i����j
     SGr1->Cells[28][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MIN);                    // �u���V���i�����j
     SGr1->Cells[29][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MAX);                    // �u���V���i����j
     SGr1->Cells[30][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MIN);                   // �u���V���c�����i�����j
     SGr1->Cells[31][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MAX);                   // �u���V���c�����i����j
     SGr1->Cells[32][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MIN);                     // ��̔�d�i�����j
     SGr1->Cells[39][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MAX);                     // ��̔�d�i����j
     SGr1->Cells[40][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_HP_KYO);                     // ���[�h���������x
     SGr1->Cells[36][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_TAN);                       // ���[�h���������x�i�P�ʁj
     SGr1->Cells[37][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_SPD);                       // ���[�h���������x�i���x�j
     SGr1->Cells[38][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.LD_TR_DENA);                    // ���[�h��t��R�i�d���j
     SGr1->Cells[33][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_DENR);                      // ���[�h��t��R�i�d���j
     SGr1->Cells[34][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_TIME);                      // ���[�h��t��R�i���ԁj
     SGr1->Cells[35][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.LD_TR_TYPE;                                // ���[�h��t��R�iTYPE�j
     SGr1->Cells[63][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MIN);                        // �ŗL��R���i�����j
     SGr1->Cells[41][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MAX);                        // �ŗL��R���i����j
     SGr1->Cells[42][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.KOYU_DEN);                      // �ŗL��R���i�d���j
     SGr1->Cells[43][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.KOYU_PRO);                        // �ŗL��R���i�v���[�u�j
     SGr1->Cells[44][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MIN);                      // �Ȃ����x�i�����j
     SGr1->Cells[45][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MAX);                      // �Ȃ����x�i����j
     SGr1->Cells[46][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.MAGE_TAN);                        // �Ȃ����x�i�P�ʁj
     SGr1->Cells[47][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_SPAN);                     // �Ȃ����x�i�X�p���j
     SGr1->Cells[48][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MIN);                       // HsC�d�x ���ʁi�����j
     SGr1->Cells[49][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MAX);                       // HsC�d�x ���ʁi����j
     SGr1->Cells[50][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MIN);                       // HsC�d�x ���ʁi�����j
     SGr1->Cells[51][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MAX);                       // HsC�d�x ���ʁi����j
     SGr1->Cells[52][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MIN);                     // HsD�d�x ���ʁi�����j
     SGr1->Cells[53][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MAX);                     // HsD�d�x ���ʁi����j
     SGr1->Cells[54][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MIN);                     // HsD�d�x ���ʁi�����j
     SGr1->Cells[55][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MAX);                     // HsD�d�x ���ʁi����j
     SGr1->Cells[56][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MIN);                       // �����i�����j
     SGr1->Cells[57][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MAX);                       // �����i����j
     SGr1->Cells[58][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.ADDYMD;                               		// �o�^��
     SGr1->Cells[59][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.UPDYMD;                               		// �ύX��
     SGr1->Cells[60][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.UPDCNT);                          // �X�V��
     SGr1->Cells[61][SGr1->RowCount - 1] = sBuf;
     sBuf = KM02.DTKSNAM;                              		// ���Ӑ於��
     SGr1->Cells[62][SGr1->RowCount - 1] = sBuf;
     //2002/11/11 E.Takase
     sBuf =  IntToStr(KM02.REVCNT);                       	// �����ԍ�
     SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;
     sBuf =  KM02.UPDCHR;                       	        // �X�V��
     SGr1->Cells[65][SGr1->RowCount - 1] = sBuf;
     sBuf =  KM02.MEMO;                       	            // ���l
     SGr1->Cells[66][SGr1->RowCount - 1] = sBuf;

     //2002/12/05 E.Takase
     sBuf = IntToStr(KM02.SK_MAGEG);                         // ����敪�@�����Ȃ����x
     SGr1->Cells[69][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MIN);                      // �����Ȃ����x�i�����j
     SGr1->Cells[70][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MAX);                      // �����Ȃ����x�i����j
     SGr1->Cells[71][SGr1->RowCount - 1] = sBuf;
     sBuf = IntToStr(KM02.MAGEG_TAN);                        // �����Ȃ����x�i�P�ʁj
     SGr1->Cells[72][SGr1->RowCount - 1] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_SPAN);                     // �����Ȃ����x�i�X�p���j
     SGr1->Cells[73][SGr1->RowCount - 1] = sBuf;

     // ��s���₷
     SGr1->RowCount = SGr1->RowCount + 1;

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // �V�����s��I��
     SGr1->Row = SGr1->RowCount - 1;

     Edt01->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;

}


//---------------------------------------------------------------------------
// �u�e�X�F�C���v
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
     AnsiString sBuf;
     bool       fNG;

     if( !BtnF09->Enabled )    return;

     if( SGr1->Cells[2][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
        SBr1->Update();
        Beep();
        return;
     }

     // �l�`�F�b�N
	 fNG = false;
     if( !(Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0) && Edt10->Value > 0 )	fNG = true;
	 if( !(EdtA1->Value < EdtA2->Value) && ChkBoxA->Checked )   fNG = true;
     if( !(EdtB1->Value < EdtB2->Value) && ChkBoxB->Checked )	fNG = true;
     if( !(EdtC1->Value < EdtC2->Value) && ChkBoxC->Checked )	fNG = true;
     if( !(EdtD1->Value < EdtD2->Value) && ChkBoxD->Checked )	fNG = true;
     if( !(EdtG1->Value < EdtG2->Value) && ChkBoxG->Checked )	fNG = true;
     if( !(EdtH1->Value < EdtH2->Value) && ChkBoxH->Checked )	fNG = true;
     if( !(EdtI1->Value < EdtI2->Value) && ChkBoxI->Checked )	fNG = true;
     if( !(EdtJ1->Value < EdtJ2->Value) && ChkBoxJ->Checked )	fNG = true;
     if( !(EdtK1->Value < EdtK2->Value) && ChkBoxK->Checked )	fNG = true;
     if( !(EdtL1->Value < EdtL2->Value) && ChkBoxL->Checked )	fNG = true;
     if( !(EdtM1->Value < EdtM2->Value) && ChkBoxM->Checked )	fNG = true;
     if( !(EdtN1->Value < EdtN2->Value) && ChkBoxN->Checked )	fNG = true;
     if( fNG == true ){
        SBr1->Panels->Items[0]->Text = "�K�i�͈̔͂��w�肵�����Ă��������B";
        SBr1->Update();
        Beep();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     ////�����f�[�^���쐬 2002/11/11 E.Takase
     ////�@�O���b�h����C���O�̃f�[�^���擾
     //SGr1->Tag = 1;
     //GetRirekiData(SGr1->Row);
     //
     ////�A�����f�[�^�Ƃ��ăf�[�^�x�[�X�ɏo��
     //InsRirekiData();
     //
     ////�B�u�����f�[�^��\������v�̏ꍇ�A�����f�[�^��}������
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}
     //SGr1->Tag = 0;

     //�����f�[�^���쐬 2002/11/19 E.Takase
     //�@�����ԍ��X�V
     SGr1->Tag = 1;
     UpdRirekiNo(SGr1->Row);

     //�A�C����̃f�[�^���擾 2002/11/19 E.Takase
     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     GetEdtData();


     //�B�C����̃f�[�^��ǉ� 2002/11/19 E.Takase
     // AddData

     if( AddData() == False ){
        return;
     }
     //// CollectData
     //if( CollectData(SGr1->Cells[2][SGr1->Row]) == False ){
     //   return;
     //}

     //�C�����f�[�^���ŐV�ɂ���i�f�[�^�̑}���j
     //    �� ����\���̏ꍇ�̂�
     if ( CheckBoxRireki->Checked == true) {

        InsSGrRirekiData();
     }


     //�D�C����̃f�[�^���O���b�h�ɃZ�b�g���܂��B
     SetEdtData(SGr1->Row);

     SGr1->Tag = 0;

     /*
     // �ύX��
     if ( Trim(KM02.UPDYMD) != "" ) {
        sBuf = KM02.UPDYMD;
        sBuf = sBuf.Insert("/",5);
        sBuf = sBuf.Insert("/",8);
     } else {
        sBuf = "";
     }
     PnlUPDYMD2->Caption = sBuf;
     // �X�V��
     sBuf = IntToStr(KM02.UPDCNT);
     PnlUPDCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;
     */

     SGr1->SetFocus();
     SGr1SelectCell(Sender,0,SGr1->Row,true) ;
     
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;

}


//---------------------------------------------------------------------------
// �u�e�P�O�F�폜�v
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     int i;
     int j;
     AnsiString sBuf;


     if( !BtnF10->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�폜�Ώۂł͂���܂���B";
        SBr1->Update();
        Beep();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�폜���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();


     ////�����f�[�^���쐬 2002/11/11 E.Takase
     ////�@�O���b�h����C���O�̃f�[�^���擾
     //SGr1->Tag = 1;
     //GetRirekiData(SGr1->Row);
     //
     ////�A�����f�[�^�Ƃ��ăf�[�^�x�[�X�ɏo��
     //InsRirekiData();
     //
     ////�B�u�����f�[�^��\������v�̏ꍇ�A�����f�[�^��}������
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}
     //SGr1->Tag = 0;

     ////�����f�[�^���쐬 2002/11/19 E.Takase
     ////�@�����ԍ��X�V
     //SGr1->Tag = 1;
     //UpdRirekiNo(SGr1->Row);
     //
     ////�C�����f�[�^���ŐV�ɂ���i�f�[�^�̑}���j
     ////    �� ����\���̏ꍇ�̂�
     //if ( CheckBoxRireki->Checked == true) {
     //
     //   InsSGrRirekiData();
     //}

     SGr1->Tag = 0;
     //return;
     
     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM02.DTKSCOD     = Edt01->Text  ;                          // ���Ӑ�R�[�h
     KM02.DTKSNAM     = Edt02->Text  ;                          // ���Ӑ於��
     KM02.DTKSHIN     = Edt03->Text  ;                          // ���Ӑ�i��
     KM02.HINBAN      = Edt04->Text  ;                          // ���Еi��
     KM02.ZISNAM      = Edt05->Text  ;                          // �ގ�����
     KM02.ZISCOD      = Edt06->Text  ;                          // �ގ��R�[�h
     KM02.SYOSCOD     = Edt07->Text  ;                          // �Đ��R�[�h
     KM02.SORTKEY     = Edt08->Value ;                          // �\�[�g�L�[
     KM02.KEIJKBN     = 0            ;                          // �`��敪
     if( ComBox09->Text == "���^" ) KM02.KEIJKBN = 2;
     if( ComBox09->Text == "��^" ) KM02.KEIJKBN = 3;
     if( ComBox09->Text == "�~��" ) KM02.KEIJKBN = 4;
     if( ComBox09->Text == "�R���~" ) KM02.KEIJKBN = 5;         // 2002.10.30 Add By Takase
     if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
     if( ChkBoxA->Checked ) KM02.SK_LD_LNG  = ChkEdtA->Value ;  // ����敪�@������
     else                   KM02.SK_LD_LNG  = 0 ;
     if( ChkBoxB->Checked ) KM02.SK_BURASI  = ChkEdtB->Value ;  // ����敪�@�u���V��
     else                   KM02.SK_BURASI  = 0 ;
     if( ChkBoxC->Checked ) KM02.SK_BURASIT = ChkEdtC->Value ;  // ����敪�@�u���V���c����
     else                   KM02.SK_BURASIT = 0 ;
     if( ChkBoxD->Checked ) KM02.SK_BOTAI   = ChkEdtD->Value ;  // ����敪�@��̔�d
     else                   KM02.SK_BOTAI   = 0  ;
     if( ChkBoxE->Checked ) KM02.SK_LD_HP   = ChkEdtE->Value ;  // ����敪�@���������x
     else                   KM02.SK_LD_HP   = 0 ;
     if( ChkBoxF->Checked ) KM02.SK_LD_TR   = ChkEdtF->Value ;  // ����敪�@����t��R
     else                   KM02.SK_LD_TR   = 0 ;
     if( ChkBoxG->Checked ) KM02.SK_KOYU    = ChkEdtG->Value ;  // ����敪�@�ŗL��R
     else                   KM02.SK_KOYU    = 0 ;
     if( ChkBoxH->Checked ) KM02.SK_MAGE    = ChkEdtH->Value ;  // ����敪�@�R�ܗ�
     else                   KM02.SK_MAGE    = 0 ;
     if( ChkBoxI->Checked ) KM02.SK_HSC_A   = ChkEdtI->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_A   = 0 ;
     if( ChkBoxJ->Checked ) KM02.SK_HSC_S   = ChkEdtJ->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_S   = 0 ;
     if( ChkBoxK->Checked ) KM02.SK_HSD_A   = ChkEdtK->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_A   = 0 ;
     if( ChkBoxL->Checked ) KM02.SK_HSD_S   = ChkEdtL->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_S   = 0 ;
     if( ChkBoxM->Checked ) KM02.SK_ZAKUT   = ChkEdtM->Value ;  // ����敪�@����
     else                   KM02.SK_ZAKUT   = 0 ;
     KM02.HIST_SOKUT  = Edt10->Value ;                          // �q�X�g�O�����i���萔�j
     KM02.HIST_KIKAK  = 0            ;                          // �q�X�g�O�����i�K�i�j
     if( ComBox11->Text  == "����" ) KM02.HIST_KIKAK = 2;
     if( ComBox11->Text  == "���" ) KM02.HIST_KIKAK = 3;
     if( KM02.HIST_KIKAK == 0      ) KM02.HIST_KIKAK = 1;
     KM02.HIST_MIN    = Edt12->Value ;                          // �q�X�g�O�����i�����j
     KM02.HIST_MAX    = Edt13->Value ;                          // �q�X�g�O�����i����j
     KM02.LD_LNG_MIN  = EdtA1->Value ;                          // ���[�h�������i�����j
     KM02.LD_LNG_MAX  = EdtA2->Value ;                          // ���[�h�������i����j
     KM02.BURASI_MIN  = EdtB1->Value ;                          // �u���V���i�����j
     KM02.BURASI_MAX  = EdtB2->Value ;                          // �u���V���i����j
     KM02.BURASIT_MIN = EdtC1->Value ;                          // �u���V���c�����i�����j
     KM02.BURASIT_MAX = EdtC2->Value ;                          // �u���V���c�����i����j
     KM02.BOTAI_MIN   = EdtD1->Value ;                          // ��̔�d�i�����j
     KM02.BOTAI_MAX   = EdtD2->Value ;                          // ��̔�d�i����j
     KM02.LD_HP_KYO   = EdtE1->Value ;                          // ���[�h���������x
     KM02.LD_HP_TAN   = 0;                                      // ���[�h���������x�i�P�ʁj
     sBuf = ComBoxE2->Text.UpperCase();
     if( sBuf[1] == 'K'      ) KM02.LD_HP_TAN = 1;              // Kgf
     if( KM02.LD_HP_TAN == 0 ) KM02.LD_HP_TAN = 2;              // N
     KM02.LD_HP_SPD   = EdtE3->Value ;                          // ���[�h���������x�i���x�j
     KM02.LD_TR_DENA  = EdtF1->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_DENR  = EdtF2->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_TIME  = EdtF3->Value ;                          // ���[�h��t��R�i���ԁj
     KM02.LD_TR_TYPE  = EdtF4->Text  ;                          // ���[�h��t��R�iTYPE�j
     KM02.KOYU_MIN    = EdtG1->Value ;                          // �ŗL��R���i�����j
     KM02.KOYU_MAX    = EdtG2->Value ;                          // �ŗL��R���i����j
     KM02.KOYU_DEN    = EdtG3->Value ;                          // �ŗL��R���i�d���j
     KM02.KOYU_PRO    = EdtG4->Value ;                          // �ŗL��R���i�v���[�u�j
     KM02.MAGE_MIN    = EdtH1->Value ;                          // �Ȃ����x�i�����j
     KM02.MAGE_MAX    = EdtH2->Value ;                          // �Ȃ����x�i����j
     KM02.MAGE_TAN    = 0;                                      // �Ȃ����x�i�P�ʁj
     sBuf = ComBoxH3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGE_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGE_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGE_TAN = 3;                  // MPa
     if( KM02.MAGE_TAN == 0          ) KM02.MAGE_TAN = 4;                  // N/mm2
     KM02.MAGE_SPAN   = EdtH4->Value ;                          // �Ȃ����x�i�X�p���j
     KM02.HSC_A_MIN   = EdtI1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_A_MAX   = EdtI2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSC_S_MIN   = EdtJ1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_S_MAX   = EdtJ2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSD_A_MIN   = EdtK1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_A_MAX   = EdtK2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.HSD_S_MIN   = EdtL1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_S_MAX   = EdtL2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.ZAKUT_MIN   = EdtM1->Value ;                          // �����i�����j
     KM02.ZAKUT_MAX   = EdtM2->Value ;                          // �����i����j
     KM02.UPDCHR      = USER_COD;                               // �X�V��
     if( SGr1->Cells[61][SGr1->Row] == "" ){
        KM02.UPDCNT  = 0;
     }
     else{
        KM02.UPDCNT  = StrToInt(SGr1->Cells[61][SGr1->Row]) ;   // �X�V��
     }

     if( SGr1->Cells[10][SGr1->Row] == "" ){
        KM02.REVCNT  = 0;
     }
     else{
        KM02.REVCNT  = StrToInt(SGr1->Cells[10][SGr1->Row]) ;   // �����ԍ�
     }

     //2002/12/05 E.Takase
     if( ChkBoxN->Checked ) KM02.SK_MAGEG    = ChkEdtN->Value ;  // ����敪�@�����Ȃ����x
     else                   KM02.SK_MAGEG    = 0 ;
     KM02.MAGEG_MIN    = EdtN1->Value ;                          // �����Ȃ����x�i�����j
     KM02.MAGEG_MAX    = EdtN2->Value ;                          // �����Ȃ����x�i����j
     KM02.MAGEG_TAN    = 0;                                      // �����Ȃ����x�i�P�ʁj
     sBuf = ComBoxN3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGEG_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGEG_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGEG_TAN = 3;                  // MPa
     //2003/07/22 E.Takase �P�ʂɁuN�v�ǉ�
     if( sBuf[1] == 'N'              ) KM02.MAGEG_TAN = 5;                  // N
     if( KM02.MAGEG_TAN == 0          ) KM02.MAGEG_TAN = 4;                  // N/mm2
     KM02.MAGEG_SPAN   = EdtN4->Value ;                          // �����Ȃ����x�i�X�p���j

     // DelData
     if( DelData() == False ){
        return;
     }

     // ��s�Âړ�����
     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         for( j = 1; j < SGr1->ColCount; j++) {
             SGr1->Cells[j][i]  = SGr1->Cells[j][i+1];
         }
     }

     // ��s���炷
     SGr1->RowCount = SGr1->RowCount - 1;

     // �V�����s��I��
     if( SGr1->RowCount == SGr1->Row)    SGr1->Row = SGr1->Row - 1;
     else                                SGr1->Row = SGr1->Row;

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     SGr1->SetFocus();

     // �f�[�^��ύX�����t���O
     DataSave = true;

}


//---------------------------------------------------------------------------
// �u�e�P�P�F�ۑ��v
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{

     if( !BtnF11->Enabled )    return;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�ۑ����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �ύX�C�}���C�폜���i���I�ɕۑ����C���݂̃g�����U�N�V�������I��
     if( Database1->InTransaction == True ){
         Database1->Commit();
         // �V�����g�����U�N�V�������J�n
         Database1->StartTransaction();
     }
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = false;

}


//---------------------------------------------------------------------------
// �u�e�P�Q�F�߂�v
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
     // �������͏������܂���B
     if( SGr1->Tag == 1 )   return;

     AnsiString sBuf;

     //�R���g���[��������
     InitEdt2(true);

     // �󔒍s�I���Ȃ��ʃN���A�[
     if( SGr1->Cells[1][ARow].Trim() == "" &&    // ���Ӑ�R�[�h
         SGr1->Cells[2][ARow].Trim() == "" ){    // ���Ӑ�i��
         InitEdt();
         return;
         BtnF08->Enabled=true;
         BtnF09->Enabled=true;
         BtnF10->Enabled=true;
         BtnF11->Enabled=true;
     }

     // ���Ӑ�R�[�h
     Edt01->Text = SGr1->Cells[1][ARow];
     // ���Ӑ於��
     Edt02->Text = SGr1->Cells[62][ARow];
     // ���Ӑ�i��
     Edt03->Text = SGr1->Cells[2][ARow];
     // ���Еi��
     Edt04->Text = SGr1->Cells[3][ARow];
     // �ގ�����
     Edt05->Text = SGr1->Cells[4][ARow];
     // �ގ��R�[�h
     Edt06->Text = SGr1->Cells[5][ARow];
     // �Đ��d�l�R�[�h
     Edt07->Text = SGr1->Cells[6][ARow];
     // �\�[�g�L�[
     Edt08->Text = SGr1->Cells[7][ARow];
     // �`��敪
     if( !SGr1->Cells[8][ARow].AnsiCompare("���^") )   ComBox09->ItemIndex = 0;
     if( !SGr1->Cells[8][ARow].AnsiCompare("���^") )   ComBox09->ItemIndex = 1;
     if( !SGr1->Cells[8][ARow].AnsiCompare("��^") )   ComBox09->ItemIndex = 2;
     if( !SGr1->Cells[8][ARow].AnsiCompare("�~��") )   ComBox09->ItemIndex = 3;
     //2002.10.21 Add By Takase
     if( !SGr1->Cells[8][ARow].AnsiCompare("�R���~") )   ComBox09->ItemIndex = 4;
     // �q�X�g�O�����i���萔�j
     Edt10->Text = SGr1->Cells[23][ARow];
     // �q�X�g�O�����i�K�i�j
     if( SGr1->Cells[24][ARow] < "1" || SGr1->Cells[24][ARow] > "3" )   SGr1->Cells[24][ARow] = "1";
     switch( StrToInt(SGr1->Cells[24][ARow]) ){
         case 1: ComBox11->ItemIndex = 0;         // �����K�i
                 break;
         case 2: ComBox11->ItemIndex = 1;         // �����K�i
                 break;
         case 3: ComBox11->ItemIndex = 2;         // ����K�i
                 break;

     }
     // �q�X�g�O�����i�����j
     Edt12->Text = SGr1->Cells[25][ARow];
     // �q�X�g�O�����i����j
     Edt13->Text = SGr1->Cells[26][ARow];

     // ����敪�@������
     // 2002/11/11 E.Takase if( StrToInt(SGr1->Cells[10][ARow]) >= 2 ){
     if( StrToInt(SGr1->Cells[64][ARow]) >= 2 ){
         // �L��
         ChkBoxA->Checked = true;
         // 2002/11/11 E.Takase ChkEdtA->Text = SGr1->Cells[10][ARow];
         ChkEdtA->Text = SGr1->Cells[64][ARow];
         EdtStatus( ChkBoxA->Tag, true);
     }
     else{
         // ����
         ChkBoxA->Checked = false;
         ChkEdtA->Text = "2";
         EdtStatus( ChkBoxA->Tag, false);
     }
     // ����敪�@�u���V��
     if( StrToInt(SGr1->Cells[11][ARow]) >= 2 ){
         ChkBoxB->Checked = true;
         ChkEdtB->Text = SGr1->Cells[11][ARow];
         EdtStatus( ChkBoxB->Tag, true);
     }
     else{
         ChkBoxB->Checked = false;
         ChkEdtB->Text = "2";
         EdtStatus( ChkBoxB->Tag, false);
     }
     // ����敪�@�u���V���c����
     if( StrToInt(SGr1->Cells[12][ARow]) >= 2 ){
         ChkBoxC->Checked = true;
         ChkEdtC->Text = SGr1->Cells[12][ARow];
         EdtStatus( ChkBoxC->Tag, true);
     }
     else{
         ChkBoxC->Checked = false;
         ChkEdtC->Text = "2";
         EdtStatus( ChkBoxC->Tag, false);
     }
     // ����敪�@��̔�d
     if( StrToInt(SGr1->Cells[15][ARow]) >= 2 ){
         ChkBoxD->Checked = true;
         ChkEdtD->Text = SGr1->Cells[15][ARow];
         EdtStatus( ChkBoxD->Tag, true);
     }
     else{
         ChkBoxD->Checked = false;
         ChkEdtD->Text = "2";
         EdtStatus( ChkBoxD->Tag, false);
     }
     // ����敪�@���������x
     if( StrToInt(SGr1->Cells[14][ARow]) >= 2 ){
         ChkBoxE->Checked = true;
         ChkEdtE->Text = SGr1->Cells[14][ARow];
         EdtStatus( ChkBoxE->Tag, true);
     }
     else{
         ChkBoxE->Checked = false;
         ChkEdtE->Text = "2";
         EdtStatus( ChkBoxE->Tag, false);
     }
     // ����敪�@����t��R
     if( StrToInt(SGr1->Cells[13][ARow]) >= 2 ){
         ChkBoxF->Checked = true;
         ChkEdtF->Text = SGr1->Cells[13][ARow];
         EdtStatus( ChkBoxF->Tag, true);
     }
     else{
         ChkBoxF->Checked = false;
         ChkEdtF->Text = "2";
         EdtStatus( ChkBoxF->Tag, false);
     }
     // ����敪�@�ŗL��R
     if( StrToInt(SGr1->Cells[16][ARow]) >= 2 ){
         ChkBoxG->Checked = true;
         ChkEdtG->Text = SGr1->Cells[16][ARow];
         EdtStatus( ChkBoxG->Tag, true);
     }
     else{
         ChkBoxG->Checked = false;
         ChkEdtG->Text = "2";
         EdtStatus( ChkBoxG->Tag, false);
     }
     // ����敪�@�R�ܗ�
     if( StrToInt(SGr1->Cells[17][ARow]) >= 2 ){
         ChkBoxH->Checked = true;
         ChkEdtH->Text = SGr1->Cells[17][ARow];
         EdtStatus( ChkBoxH->Tag, true);
     }
     else{
         ChkBoxH->Checked = false;
         ChkEdtH->Text = "2";
         EdtStatus( ChkBoxH->Tag, false);
     }
     // ����敪�@HsC�d�x�i���ʁj
     if( StrToInt(SGr1->Cells[18][ARow]) >= 2 ){
         ChkBoxI->Checked = true;
         ChkEdtI->Text = SGr1->Cells[18][ARow];
         EdtStatus( ChkBoxI->Tag, true);
     }
     else{
         ChkBoxI->Checked = false;
         ChkEdtI->Text = "2";
         EdtStatus( ChkBoxI->Tag, false);
     }
     // ����敪�@HsC�d�x�i���ʁj
     if( StrToInt(SGr1->Cells[19][ARow]) >= 2 ){
         ChkBoxJ->Checked = true;
         ChkEdtJ->Text = SGr1->Cells[19][ARow];
         EdtStatus( ChkBoxJ->Tag, true);
     }
     else{
         ChkBoxJ->Checked = false;
         ChkEdtJ->Text = "2";
         EdtStatus( ChkBoxJ->Tag, false);
     }
     // ����敪�@HsD�d�x�i���ʁj
     if( StrToInt(SGr1->Cells[20][ARow]) >= 2 ){
         ChkBoxK->Checked = true;
         ChkEdtK->Text = SGr1->Cells[20][ARow];
         EdtStatus( ChkBoxK->Tag, true);
     }
     else{
         ChkBoxK->Checked = false;
         ChkEdtK->Text = "2";
         EdtStatus( ChkBoxK->Tag, false);
     }
     // ����敪�@HsD�d�x�i���ʁj
     if( StrToInt(SGr1->Cells[21][ARow]) >= 2 ){
         ChkBoxL->Checked = true;
         ChkEdtL->Text = SGr1->Cells[21][ARow];
         EdtStatus( ChkBoxL->Tag, true);
     }
     else{
         ChkBoxL->Checked = false;
         ChkEdtL->Text = "2";
         EdtStatus( ChkBoxL->Tag, false);
     }
     // ����敪�@����
     if( StrToInt(SGr1->Cells[22][ARow]) >= 2 ){
         ChkBoxM->Checked = true;
         ChkEdtM->Text = SGr1->Cells[22][ARow];
         EdtStatus( ChkBoxM->Tag, true);
     }
     else{
         ChkBoxM->Checked = false;
         ChkEdtM->Text = "2";
         EdtStatus( ChkBoxM->Tag, false);
     }

     // ���[�h�������i�����j
     EdtA1->Text = SGr1->Cells[27][ARow];
     // ���[�h�������i����j
     EdtA2->Text = SGr1->Cells[28][ARow];
     // �u���V���i�����j
     EdtB1->Text = SGr1->Cells[29][ARow];
     // �u���V���i����j
     EdtB2->Text = SGr1->Cells[30][ARow];
     // �u���V���c�����i�����j
     EdtC1->Text = SGr1->Cells[31][ARow];
     // �u���V���c�����i����j
     EdtC2->Text = SGr1->Cells[32][ARow];
     // ��̔�d�i�����j
     EdtD1->Text = SGr1->Cells[39][ARow];
     // ��̔�d�i����j
     EdtD2->Text = SGr1->Cells[40][ARow];
     // ���[�h���������x
     EdtE1->Text = SGr1->Cells[36][ARow];
     // ���[�h���������x�i�P�ʁj
     if( SGr1->Cells[37][ARow] < "1" || SGr1->Cells[37][ARow] > "2" )   SGr1->Cells[37][ARow] = "2";
     if( StrToInt(SGr1->Cells[37][ARow]) == 1 ){
         ComBoxE2->ItemIndex = 0;           // Kgf
     }
     else{
         ComBoxE2->ItemIndex = 1;           // N
     }
     // ���[�h���������x�i�X�s�[�h�j
     EdtE3->Text = SGr1->Cells[38][ARow];
     // ���[�h��t��R�i�d���j
     EdtF1->Text = SGr1->Cells[33][ARow];
     // ���[�h��t��R�i�d���j
     EdtF2->Text = SGr1->Cells[34][ARow];
     // ���[�h��t��R�i���ԁj
     EdtF3->Text = SGr1->Cells[35][ARow];
     // ���[�h��t��R�iTYPE�j
     EdtF4->Text = SGr1->Cells[63][ARow];
     // �ŗL��R���i�����j
     EdtG1->Text = SGr1->Cells[41][ARow];
     // �ŗL��R���i����j
     EdtG2->Text = SGr1->Cells[42][ARow];
     // �ŗL��R���i�d���j
     EdtG3->Text = SGr1->Cells[43][ARow];
     // �ŗL��R���i�v���[�u�j
     EdtG4->Text = SGr1->Cells[44][ARow];
     // �Ȃ����x�i�����j
     EdtH1->Text = SGr1->Cells[45][ARow];
     // �Ȃ����x�i����j
     EdtH2->Text = SGr1->Cells[46][ARow];
     // �Ȃ����x�i�P�ʁj
     if( SGr1->Cells[47][ARow] < "1" || SGr1->Cells[47][ARow] > "4" )   SGr1->Cells[47][ARow] = "4";
     switch( StrToInt(SGr1->Cells[47][ARow]) ){
         case 1: ComBoxH3->ItemIndex = 0;    break;     // Kgf
         case 2: ComBoxH3->ItemIndex = 1;    break;     // N/cm2
         case 3: ComBoxH3->ItemIndex = 2;    break;     // MPa
         case 4: ComBoxH3->ItemIndex = 3;    break;     // N/mm2
     }
     // �Ȃ����x�i�X�p���j
     EdtH4->Text = SGr1->Cells[48][ARow];
     // HsC�d�x ���ʁi�����j
     EdtI1->Text = SGr1->Cells[49][ARow];
     // HsC�d�x ���ʁi����j
     EdtI2->Text = SGr1->Cells[50][ARow];
     // HsC�d�x ���ʁi�����j
     EdtJ1->Text = SGr1->Cells[51][ARow];
     // HsC�d�x ���ʁi����j
     EdtJ2->Text = SGr1->Cells[52][ARow];
     // HsD�d�x ���ʁi�����j
     EdtK1->Text = SGr1->Cells[53][ARow];
     // HsD�d�x ���ʁi����j
     EdtK2->Text = SGr1->Cells[54][ARow];
     // HsD�d�x ���ʁi�����j
     EdtL1->Text = SGr1->Cells[55][ARow];
     // HsD�d�x ���ʁi����j
     EdtL2->Text = SGr1->Cells[56][ARow];
     // �����i�����j
     EdtM1->Text = SGr1->Cells[57][ARow];
     // �����i����j
     EdtM2->Text = SGr1->Cells[58][ARow];

     // �K�i�l�̃`�F�b�N
     ValueChenge(Sender);

     // �o�^��
     sBuf = SGr1->Cells[59][ARow];
     if( sBuf.Trim() != "" ){
         sBuf = sBuf.Insert("/",5);
         sBuf = sBuf.Insert("/",8);
         PnlADDYMD2->Caption = sBuf;
     }
     else PnlADDYMD2->Caption = "";
     // �ύX��
     sBuf = SGr1->Cells[60][ARow];
     if( sBuf.Trim() != "" ){
         sBuf = sBuf.Insert("/",5);
         sBuf = sBuf.Insert("/",8);
         PnlUPDYMD2->Caption = sBuf;
     }
     else PnlUPDYMD2->Caption = "";
     // �X�V��
     sBuf = SGr1->Cells[61][ARow];
     PnlUPDCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     //2002/11/11 E.Takase
     // �����ԍ�
     sBuf = SGr1->Cells[10][ARow];
     PnlREVCNT2->Caption = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;
     // �X�V��
     sBuf = GetTANNAM(SGr1->Cells[65][ARow]);
     PnlUPDCHR2->Caption = sBuf;
     // ���l
     sBuf = SGr1->Cells[66][ARow];
     EdtMEMO->Text = sBuf;

     //�����f�[�^�̏ꍇ�͕ۑ��ł��Ȃ��悤�ɂ���
     if( SGr1->Cells[10][ARow].Trim() != "0" ) {   // �����ԍ�
        InitEdt2(false);
     //   BtnF08->Enabled=false;
     //   BtnF09->Enabled=false;
     //   BtnF10->Enabled=false;
     //   BtnF11->Enabled=false;
     //
     //} else {
     //   //InitEdt();
     //   BtnF08->Enabled=true;
     //   BtnF09->Enabled=true;
     //   BtnF10->Enabled=true;
     //   BtnF11->Enabled=true;
     //

     }
     //2002/12/05 E.Takase
     // ����敪�@�����Ȃ����x
     if( StrToInt(SGr1->Cells[69][ARow]) >= 2 ){
         ChkBoxN->Checked = true;
         ChkEdtN->Text = SGr1->Cells[69][ARow];
         EdtStatus( ChkBoxN->Tag, true);
     }
     else{
         ChkBoxN->Checked = false;
         ChkEdtN->Text = "2";
         EdtStatus( ChkBoxN->Tag, false);
     }
     // �����Ȃ����x�i�����j
     EdtN1->Text = SGr1->Cells[70][ARow];
     // �����Ȃ����x�i����j
     EdtN2->Text = SGr1->Cells[71][ARow];
     // �����Ȃ����x�i�P�ʁj
     //2003/07/22 E.Takase �P�ʒǉ�
     if( SGr1->Cells[72][ARow] < "1" || SGr1->Cells[72][ARow] > "5" )   SGr1->Cells[72][ARow] = "4";
     //if( SGr1->Cells[72][ARow] < "1" || SGr1->Cells[72][ARow] > "4" )   SGr1->Cells[72][ARow] = "4";
     switch( StrToInt(SGr1->Cells[72][ARow]) ){
         case 1: ComBoxN3->ItemIndex = 0;    break;     // Kgf
         case 2: ComBoxN3->ItemIndex = 1;    break;     // N/cm2
         case 3: ComBoxN3->ItemIndex = 2;    break;     // MPa
         case 4: ComBoxN3->ItemIndex = 3;    break;     // N/mm2
	     //2003/07/22 E.Takase �P�ʂɁuN�v�ǉ�
         case 5: ComBoxN3->ItemIndex = 4;    break;     // N
     }
     // �����Ȃ����x�i�X�p���j
     EdtN4->Text = SGr1->Cells[73][ARow];

     //2002/12/28 E.Takase
     if ( ComBox09->ItemIndex == 4 ) {
        PnlB->Caption = "���a";
        ChkBoxB->Caption = "���a";
        PnlC->Caption = "�O�a";
        ChkBoxC->Caption = "�O�a";

     } else {
        PnlB->Caption = "��׼��";
        ChkBoxB->Caption = "��׼��";
        PnlC->Caption = "��׼��(�c����)";
        ChkBoxC->Caption = "��׼��(�c����)";
     }


     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();
}


//---------------------------------------------------------------------------
void __fastcall TForm1::InitEdt(void)
{
     int i;

     // �e�R���g���[���̏�����
     EdtCOD1->Text = "";
     EdtCOD2->Text = "";
     EdtCOD3->Text = "";
     EdtCOD4->Text = "";
     Edt01->Text = "";
     Edt02->Text = "";
     Edt03->Text = "";
     Edt04->Text = "";
     Edt05->Text = "";
     Edt06->Text = "";
     Edt07->Text = "";
     Edt08->Text = "";
     ComBox09->ItemIndex = 0;
     Edt10->Text = "";
     ComBox11->ItemIndex = 0;
     Edt12->Text = "";
     Edt13->Text = "";
     ChkEdtA->Text = "2";
     ChkEdtB->Text = "2";
     ChkEdtC->Text = "2";
     ChkEdtD->Text = "2";
     ChkEdtE->Text = "2";
     ChkEdtF->Text = "2";
     ChkEdtG->Text = "2";
     ChkEdtH->Text = "2";
     ChkEdtI->Text = "2";
     ChkEdtJ->Text = "2";
     ChkEdtK->Text = "2";
     ChkEdtL->Text = "2";
     ChkEdtM->Text = "2";
     EdtA1->Text = "";
     EdtA2->Text = "";
     EdtB1->Text = "";
     EdtB2->Text = "";
     EdtC1->Text = "";
     EdtC2->Text = "";
     EdtD1->Text = "";
     EdtD2->Text = "";
     EdtE1->Text = "";
     ComBoxE2->ItemIndex = 1;
     EdtE3->Text = "";
     EdtF1->Text = "";
     EdtF2->Text = "";
     EdtF3->Text = "";
     EdtF4->Text = "";
     EdtG1->Text = "";
     EdtG2->Text = "";
     EdtG3->Text = "";
     EdtG4->Text = "";
     EdtH1->Text = "";
     EdtH2->Text = "";
     ComBoxH3->ItemIndex = 2;
     EdtH4->Text = "";
     EdtI1->Text = "";
     EdtI2->Text = "";
     EdtJ1->Text = "";
     EdtJ2->Text = "";
     EdtK1->Text = "";
     EdtK2->Text = "";
     EdtL1->Text = "";
     EdtL2->Text = "";
     EdtM1->Text = "";
     EdtM2->Text = "";
     PnlADDYMD2->Caption = "";
     PnlUPDYMD2->Caption = "";
     PnlUPDCNT2->Caption = "";
     ChkBoxA->Checked = false;
     ChkBoxB->Checked = false;
     ChkBoxC->Checked = false;
     ChkBoxD->Checked = false;
     ChkBoxE->Checked = false;
     ChkBoxF->Checked = false;
     ChkBoxG->Checked = false;
     ChkBoxH->Checked = false;
     ChkBoxI->Checked = false;
     ChkBoxJ->Checked = false;
     ChkBoxK->Checked = false;
     ChkBoxL->Checked = false;
     ChkBoxM->Checked = false;
     //2002/11/11 E.Takase
     PnlUPDCHR2->Caption = "";
     PnlREVCNT2->Caption = "";
     EdtMEMO->Text = "";

     //2002/12/05 E.Takase
     ChkEdtN->Text = "2";
     EdtN1->Text = "";
     EdtN2->Text = "";
     ComBoxN3->ItemIndex = 2;
     EdtN4->Text = "";
     ChkBoxN->Checked = false;

     for( i=0; i<=14; i++ ){
         EdtStatus( i, false );
     }

     // �K�i�l�̃`�F�b�N
     ValueChenge((TObject *)Form1);

}


//---------------------------------------------------------------------------
// �q�X�g�O�����K�i
void __fastcall TForm1::ComBox11Change(TObject *Sender)
{
    // �K�i�l�̃`�F�b�N
    ValueChenge(Sender);

    switch( ComBox11->ItemIndex ){

        // ����
        case 0:
            // �q�X�g�O����Min�i�L���j
            Pnl12->Color = 0x00FEE7BA;
            Pnl12->Font->Color = clBlack;
            Edt12->Enabled = true;
            // �q�X�g�O����Max�i�L���j
            Pnl13->Color = 0x00FEE7BA;
            Pnl13->Font->Color = clBlack;
            Edt13->Enabled = true;
            break;

        // ���
        case 1:
            // �q�X�g�O����Min�i�����j
            Pnl12->Color = clSilver;
            Pnl12->Font->Color = clGray;
            Edt12->Enabled = false;
            // �q�X�g�O����Max�i�L���j
            Pnl13->Color = 0x00FEE7BA;
            Pnl13->Font->Color = clBlack;
            Edt13->Enabled = true;
            break;

        // ����
        case 2:
            // �q�X�g�O����Min�i�L���j
            Pnl12->Color = 0x00FEE7BA;
            Pnl12->Font->Color = clBlack;
            Edt12->Enabled = true;
            // �q�X�g�O����Max�i�����j
            Pnl13->Color = clSilver;
            Pnl13->Font->Color = clGray;
            Edt13->Enabled = false;
            break;
    }
}


//---------------------------------------------------------------------------
void __fastcall TForm1::ChkBoxClick(TObject *Sender)
{
    // �G�f�B�b�g�̏�Ԃ�ύX���܂�
    TCheckBox *ChkBox = (TCheckBox *)Sender;
    EdtStatus( ChkBox->Tag, ChkBox->Checked );
    // �K�i�l�̃`�F�b�N
    ValueChenge(Sender);
}


//---------------------------------------------------------------------------
void __fastcall TForm1::EdtStatus(int tag, bool status)
{
    // �G�f�B�b�g�̏�Ԃ�ύX���܂�
    switch(tag){
        case 1:
            // ���[�h������
            if( status ){
                PnlA->Color = 0x00FEE7BA;
                PnlA->Font->Color = clBlack;
                EdtA1->Enabled = true;
                EdtA2->Enabled = true;
                LblA1->Font->Color = clBlack;
                LblA2->Font->Color = clBlack;
                ChkEdtA->Enabled = true;
                ChkEdtA->Font->Color = clBlack;
            }
            else{
                PnlA->Color = clSilver;
                PnlA->Font->Color = clGray;
                EdtA1->Enabled = false;
                EdtA2->Enabled = false;
                LblA1->Font->Color = clGray;
                LblA2->Font->Color = clGray;
                ChkEdtA->Enabled = false;
                ChkEdtA->Font->Color = clGray;
            }
            break;

        case 2:
            // �u���V��
            if( status ){
                PnlB->Color = 0x00FEE7BA;
                PnlB->Font->Color = clBlack;
                EdtB1->Enabled = true;
                EdtB2->Enabled = true;
                LblB1->Font->Color = clBlack;
                LblB2->Font->Color = clBlack;
                ChkEdtB->Enabled = true;
                ChkEdtB->Font->Color = clBlack;
            }
            else{
                PnlB->Color = clSilver;
                PnlB->Font->Color = clGray;
                EdtB1->Enabled = false;
                EdtB2->Enabled = false;
                LblB1->Font->Color = clGray;
                LblB2->Font->Color = clGray;
                ChkEdtB->Enabled = false;
                ChkEdtB->Font->Color = clGray;
            }
            break;

        case 3:
            // �u���V���c����
            if( status ){
                PnlC->Color = 0x00FEE7BA;
                PnlC->Font->Color = clBlack;
                EdtC1->Enabled = true;
                EdtC2->Enabled = true;
                LblC1->Font->Color = clBlack;
                LblC2->Font->Color = clBlack;
                ChkEdtC->Enabled = true;
                ChkEdtC->Font->Color = clBlack;
            }
            else{
                PnlC->Color = clSilver;
                PnlC->Font->Color = clGray;
                EdtC1->Enabled = false;
                EdtC2->Enabled = false;
                LblC1->Font->Color = clGray;
                LblC2->Font->Color = clGray;
                ChkEdtC->Enabled = false;
                ChkEdtC->Font->Color = clGray;
            }
            break;

        case 4:
            // ���|��d
            if( status ){
                PnlD->Color = 0x00FEE7BA;
                PnlD->Font->Color = clBlack;
                EdtD1->Enabled = true;
                EdtD2->Enabled = true;
                LblD1->Font->Color = clBlack;
                ChkEdtD->Enabled = true;
                ChkEdtD->Font->Color = clBlack;
            }
            else{
                PnlD->Color = clSilver;
                PnlD->Font->Color = clGray;
                EdtD1->Enabled = false;
                EdtD2->Enabled = false;
                LblD1->Font->Color = clGray;
                ChkEdtD->Enabled = false;
                ChkEdtD->Font->Color = clGray;
            }
            break;

        case 5:
            // ���������x
            if( status ){
                PnlE->Color = 0x00FEE7BA;
                PnlE->Font->Color = clBlack;
                EdtE1->Enabled = true;
                ComBoxE2->Enabled = true;
                EdtE3->Enabled = true;
                LblE1->Font->Color = clBlack;
                LblE2->Font->Color = clBlack;
                ChkEdtE->Enabled = true;
                ChkEdtE->Font->Color = clBlack;
            }
            else{
                PnlE->Color = clSilver;
                PnlE->Font->Color = clGray;
                EdtE1->Enabled = false;
                ComBoxE2->Enabled = false;
                EdtE3->Enabled = false;
                LblE1->Font->Color = clGray;
                LblE2->Font->Color = clGray;
                ChkEdtE->Enabled = false;
                ChkEdtE->Font->Color = clGray;
            }
            break;

        case 6:
            // ����t��R
            if( status ){
                PnlF->Color = 0x00FEE7BA;
                PnlF->Font->Color = clBlack;
                EdtF1->Enabled = true;
                EdtF2->Enabled = true;
                EdtF3->Enabled = true;
                EdtF4->Enabled = true;
                LblF1->Font->Color = clBlack;
                LblF2->Font->Color = clBlack;
                LblF3->Font->Color = clBlack;
                LblF4->Font->Color = clBlack;
                ChkEdtF->Enabled = true;
                ChkEdtF->Font->Color = clBlack;
            }
            else{
                PnlF->Color = clSilver;
                PnlF->Font->Color = clGray;
                EdtF1->Enabled = false;
                EdtF2->Enabled = false;
                EdtF3->Enabled = false;
                EdtF4->Enabled = false;
                LblF1->Font->Color = clGray;
                LblF2->Font->Color = clGray;
                LblF3->Font->Color = clGray;
                LblF4->Font->Color = clGray;
                ChkEdtF->Enabled = false;
                ChkEdtF->Font->Color = clGray;
            }
            break;

        case 7:
            // ��R��
            if( status ){
                PnlG->Color = 0x00FEE7BA;
                PnlG->Font->Color = clBlack;
                EdtG1->Enabled = true;
                EdtG2->Enabled = true;
                EdtG3->Enabled = true;
                EdtG4->Enabled = true;
                LblG1->Font->Color = clBlack;
                LblG2->Font->Color = clBlack;
                LblG3->Font->Color = clBlack;
                LblG4->Font->Color = clBlack;
                LblG5->Font->Color = clBlack;
                ChkEdtG->Enabled = true;
                ChkEdtG->Font->Color = clBlack;
            }
            else{
                PnlG->Color = clSilver;
                PnlG->Font->Color = clGray;
                EdtG1->Enabled = false;
                EdtG2->Enabled = false;
                EdtG3->Enabled = false;
                EdtG4->Enabled = false;
                LblG1->Font->Color = clGray;
                LblG2->Font->Color = clGray;
                LblG3->Font->Color = clGray;
                LblG4->Font->Color = clGray;
                LblG5->Font->Color = clGray;
                ChkEdtG->Enabled = false;
                ChkEdtG->Font->Color = clGray;
            }
            break;

        case 8:
            // �Ȃ�����
            if( status ){
                PnlH->Color = 0x00FEE7BA;
                PnlH->Font->Color = clBlack;
                EdtH1->Enabled = true;
                EdtH2->Enabled = true;
                ComBoxH3->Enabled = true;
                EdtH4->Enabled = true;
                LblH1->Font->Color = clBlack;
                LblH2->Font->Color = clBlack;
                LblH3->Font->Color = clBlack;
                ChkEdtH->Enabled = true;
                ChkEdtH->Font->Color = clBlack;
            }
            else{
                PnlH->Color = clSilver;
                PnlH->Font->Color = clGray;
                EdtH1->Enabled = false;
                EdtH2->Enabled = false;
                ComBoxH3->Enabled = false;
                EdtH4->Enabled = false;
                LblH1->Font->Color = clGray;
                LblH2->Font->Color = clGray;
                LblH3->Font->Color = clGray;
                ChkEdtH->Enabled = false;
                ChkEdtH->Font->Color = clGray;
            }
            break;

        case 9:
            // �d�xHsC�i���ʁj
            if( status ){
                PnlI->Color = 0x00FEE7BA;
                PnlI->Font->Color = clBlack;
                EdtI1->Enabled = true;
                EdtI2->Enabled = true;
                LblI1->Font->Color = clBlack;
                LblI2->Font->Color = clBlack;
                ChkEdtI->Enabled = true;
                ChkEdtI->Font->Color = clBlack;
            }
            else{
                PnlI->Color = clSilver;
                PnlI->Font->Color = clGray;
                EdtI1->Enabled = false;
                EdtI2->Enabled = false;
                LblI1->Font->Color = clGray;
                LblI2->Font->Color = clGray;
                ChkEdtI->Enabled = false;
                ChkEdtI->Font->Color = clGray;
            }
            break;

        case 10:
            // �d�xHsC�i���ʁj
            if( status ){
                PnlJ->Color = 0x00FEE7BA;
                PnlJ->Font->Color = clBlack;
                EdtJ1->Enabled = true;
                EdtJ2->Enabled = true;
                LblJ1->Font->Color = clBlack;
                LblJ2->Font->Color = clBlack;
                ChkEdtJ->Enabled = true;
                ChkEdtJ->Font->Color = clBlack;
            }
            else{
                PnlJ->Color = clSilver;
                PnlJ->Font->Color = clGray;
                EdtJ1->Enabled = false;
                EdtJ2->Enabled = false;
                LblJ1->Font->Color = clGray;
                LblJ2->Font->Color = clGray;
                ChkEdtJ->Enabled = false;
                ChkEdtJ->Font->Color = clGray;
            }
            break;

        case 11:
            // �d�xHsD�i���ʁj
            if( status ){
                PnlK->Color = 0x00FEE7BA;
                PnlK->Font->Color = clBlack;
                EdtK1->Enabled = true;
                EdtK2->Enabled = true;
                LblK1->Font->Color = clBlack;
                LblK2->Font->Color = clBlack;
                ChkEdtK->Enabled = true;
                ChkEdtK->Font->Color = clBlack;
            }
            else{
                PnlK->Color = clSilver;
                PnlK->Font->Color = clGray;
                EdtK1->Enabled = false;
                EdtK2->Enabled = false;
                LblK1->Font->Color = clGray;
                LblK2->Font->Color = clGray;
                ChkEdtK->Enabled = false;
                ChkEdtK->Font->Color = clGray;
            }
            break;

        case 12:
            // �d�xHsD�i���ʁj
            if( status ){
                PnlL->Color = 0x00FEE7BA;
                PnlL->Font->Color = clBlack;
                EdtL1->Enabled = true;
                EdtL2->Enabled = true;
                LblL1->Font->Color = clBlack;
                LblL2->Font->Color = clBlack;
                ChkEdtL->Enabled = true;
                ChkEdtL->Font->Color = clBlack;
            }
            else{
                PnlL->Color = clSilver;
                PnlL->Font->Color = clGray;
                EdtL1->Enabled = false;
                EdtL2->Enabled = false;
                LblL1->Font->Color = clGray;
                LblL2->Font->Color = clGray;
                ChkEdtL->Enabled = false;
                ChkEdtL->Font->Color = clGray;
            }
            break;

        case 13:
            // ����
            if( status ){
                PnlM->Color = 0x00FEE7BA;
                PnlM->Font->Color = clBlack;
                EdtM1->Enabled = true;
                EdtM2->Enabled = true;
                LblM1->Font->Color = clBlack;
                LblM2->Font->Color = clBlack;
                ChkEdtM->Enabled = true;
                ChkEdtM->Font->Color = clBlack;
            }
            else{
                PnlM->Color = clSilver;
                PnlM->Font->Color = clGray;
                EdtM1->Enabled = false;
                EdtM2->Enabled = false;
                LblM1->Font->Color = clGray;
                LblM2->Font->Color = clGray;
                ChkEdtM->Enabled = false;
                ChkEdtM->Font->Color = clGray;
            }
            break;
        case 14:
            // �����Ȃ�����
            if( status ){
                PnlN->Color = 0x00FEE7BA;
                PnlN->Font->Color = clBlack;
                EdtN1->Enabled = true;
                EdtN2->Enabled = true;
                ComBoxN3->Enabled = true;
                EdtN4->Enabled = true;
                LblN1->Font->Color = clBlack;
                LblN2->Font->Color = clBlack;
                LblN3->Font->Color = clBlack;
                ChkEdtN->Enabled = true;
                ChkEdtN->Font->Color = clBlack;
            }
            else{
                PnlN->Color = clSilver;
                PnlN->Font->Color = clGray;
                EdtN1->Enabled = false;
                EdtN2->Enabled = false;
                ComBoxN3->Enabled = false;
                EdtN4->Enabled = false;
                LblN1->Font->Color = clGray;
                LblN2->Font->Color = clGray;
                LblN3->Font->Color = clGray;
                ChkEdtN->Enabled = false;
                ChkEdtN->Font->Color = clGray;
            }
            break;     }

}


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     // �X�e�[�^�X���b�Z�[�W
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key){
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
                      // �������Ƀt�H�[�J�X������ꍇ�́A�������s
                      if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() || EdtCOD4->Focused() || CheckBoxRireki->Focused() ){
                          BtnF07Click(Sender);
                      }
                      // �������ȊO�Ƀt�H�[�J�X������ꍇ�́A�������ɃZ�b�g�t�H�[�J�X
                      else{
                          EdtCOD1->SetFocus();
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
         case VK_UP:
         case VK_LEFT:
                // ������
                if( EdtCOD2->Focused() || EdtCOD3->Focused() || EdtCOD4->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == 0 && Edt->SelLength == 0 ){
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( EdtCOD1->Focused() && EdtCOD1->SelStart == 0 && EdtCOD1->SelLength == 0 ){
                    if(EdtCOD4->Enabled){
                        EdtCOD4->SetFocus();
                    }
                    else{
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // �ڍו�
                //2002/11/13 ���l�ǉ� E.Takase
                //2002/12/05 �����Ȃ������ǉ� E.Takase
                if( Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt05->Focused() || Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || EdtM2->Focused() || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused()  ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == 0 && Edt->SelLength == 0 ){
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                //2002/12/05 �����Ȃ������ǉ� E.Takase
                if( (ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused()
                    || ComBoxH3->Focused() || ComBoxN3->Focused()) && Key == VK_LEFT ){
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                //2002/12/05 �����Ȃ������ǉ� E.Takase
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused() ){
                    keybd_event(VK_SHIFT,0,0,0);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( Edt01->Focused() && Edt01->SelStart == 0 && Edt01->SelLength == 0 ){
                    if(EdtM2->Enabled){
                        EdtM2->SetFocus();
                    }
                    else{
                        keybd_event(VK_SHIFT,0,0,0);
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // ����
         case VK_DOWN:
         case VK_RIGHT:
                // ������
                if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == Edt->Text.Length() && Edt->SelLength == 0 ){
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( EdtCOD4->Focused() && EdtCOD4->SelStart == EdtCOD4->Text.Length() && EdtCOD4->SelLength == 0 ){
                    if(EdtCOD1->Enabled){
                        EdtCOD1->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // �ڍו�
                //2002/11/13 ���l�ǉ� E.Takase
                //2002/12/05 �����Ȃ������ǉ� E.Takase
                if( Edt01->Focused() || Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt05->Focused() || Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused()  ){
                    TEdit *Edt = (TEdit *)Sender;
                    if( Edt->SelStart == Edt->Text.Length() && Edt->SelLength == 0 ){
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                        break;
                    }
                }
                if( (ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused() ||
                        ComBoxH3->Focused() || ComBoxN3->Focused() ) && Key == VK_RIGHT ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused()){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtM2->Focused() && EdtM2->SelStart == EdtM2->Text.Length() && EdtM2->SelLength == 0 ){
                    if(Edt01->Enabled){
                        Edt01->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                // ������
                if( EdtCOD1->Focused() || EdtCOD2->Focused() || EdtCOD3->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtCOD4->Focused() ){
                    BtnF07Click(Sender);    break;
                }
                // �ڍו�
                //2002/11/13 ���l�ǉ� E.Takase
                if( Edt01->Focused() || Edt02->Focused() || Edt03->Focused() || Edt04->Focused() ||
                    Edt06->Focused() || Edt07->Focused() || Edt08->Focused() ||
                    Edt10->Focused() || Edt12->Focused() || Edt13->Focused() || ChkEdtA->Focused() ||
                    ChkEdtB->Focused() || ChkEdtC->Focused() || ChkEdtD->Focused() || ChkEdtE->Focused() ||
                    ChkEdtF->Focused() || ChkEdtG->Focused() || ChkEdtH->Focused() || ChkEdtI->Focused() ||
                    ChkEdtJ->Focused() || ChkEdtK->Focused() || ChkEdtL->Focused() || ChkEdtM->Focused() ||
                    EdtA1->Focused() || EdtA2->Focused() || EdtB1->Focused() || EdtB2->Focused() ||
                    EdtC1->Focused() || EdtC2->Focused() || EdtD1->Focused() || EdtD2->Focused() ||
                    EdtE1->Focused() || EdtE3->Focused() || EdtF1->Focused() || EdtF2->Focused() ||
                    EdtF3->Focused() || EdtF4->Focused() || EdtG1->Focused() || EdtG2->Focused() || EdtG3->Focused() ||
                    EdtG4->Focused() || EdtH1->Focused() || EdtH2->Focused() || EdtH4->Focused() ||
                    EdtI1->Focused() || EdtI2->Focused() || EdtJ1->Focused() || EdtJ2->Focused() ||
                    EdtK1->Focused() || EdtK2->Focused() || EdtL1->Focused() || EdtL2->Focused() ||
                    EdtM1->Focused() || ComBox09->Focused() || ComBox11->Focused() || ComBoxE2->Focused() ||
                    ComBoxH3->Focused()  || EdtMEMO->Focused() ||
                    ChkEdtN->Focused() || ComBoxN3->Focused() || EdtN1->Focused() || EdtN2->Focused() || EdtN4->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( ChkBoxA->Focused() || ChkBoxB->Focused() || ChkBoxC->Focused() || ChkBoxD->Focused() ||
                    ChkBoxE->Focused() || ChkBoxF->Focused() || ChkBoxG->Focused() || ChkBoxH->Focused() ||
                    ChkBoxI->Focused() || ChkBoxJ->Focused() || ChkBoxK->Focused() || ChkBoxL->Focused() ||
                    ChkBoxM->Focused() || ChkBoxN->Focused() ){
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
                if( EdtM2->Focused() ){
                    if(Edt01->Enabled){
                        Edt01->SetFocus();
                    }
                    else{
                        keybd_event(VK_TAB,0,0,0);
                        keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    }
                    break;
                }
                // �ގ�����
                if( Edt05->Focused() ){
                    // �ގ��K�i�}�X�^�[�����Ƀf�[�^���Z�b�g���܂�
                    // 2002/11/14 E.Takase �����ǉ�
                    if ( Edt05->ReadOnly == false ) {
                        SetZAISHITSU(2,Edt05->Text);
                    }
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
/*
                // �ގ��R�[�h
                if( Edt06->Focused() ){
                    // �ގ��K�i�}�X�^�[�����Ƀf�[�^���Z�b�g���܂�
                    SetZAISHITSU(1,Edt06->Text);
                    keybd_event(VK_TAB,0,0,0);
                    keybd_event(VK_TAB,0,KEYEVENTF_KEYUP,0);
                    break;
                }
*/
                break;
     }

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
         case VK_RETURN:Edt01->SetFocus();      break;
     }

}

//---------------------------------------------------------------------------
// �f�[�^��ǉ����܂��B
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "select DTKSHIN from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // �ގ��R�[�h
     //2002/11/11 E.Takase
     sBuf += "and REVCNT = " + IntToStr(KM02.REVCNT);  // �����ԍ�

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B";
            SBr1->Update();
            Beep();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     //2002/11/13 �f�[�^���� �ǉ��iREVCNT,MEMO,UPDYMD,UPDTIM�j E.Takase
     sBuf = "insert into KM02(DTKSCOD,DTKSNAM,DTKSHIN,HINBAN,ZISCOD,ZISNAM,SYOSCOD,";
     sBuf = sBuf + "SORTKEY,KEIJKBN,SK_LD_LNG,SK_BURASI,SK_BURASIT,SK_LD_TR,SK_LD_HP,";
     sBuf = sBuf + "SK_BOTAI,SK_KOYU,SK_MAGE,SK_HSC_A,SK_HSC_S,SK_HSD_A,SK_HSD_S,";
     sBuf = sBuf + "SK_ZAKUT,HIST_SOKUT,HIST_KIKAK,HIST_MIN,HIST_MAX,LD_LNG_MIN,";
     sBuf = sBuf + "LD_LNG_MAX,BURASI_MIN,BURASI_MAX,BURASIT_MIN,BURASIT_MAX,LD_TR_DENA,";
     sBuf = sBuf + "LD_TR_DENR,LD_TR_TIME,LD_TR_TYPE,LD_HP_KYO,LD_HP_TAN,LD_HP_SPD,BOTAI_MIN,";
     sBuf = sBuf + "BOTAI_MAX,KOYU_MIN,KOYU_MAX,KOYU_DEN,KOYU_PRO,MAGE_MIN,MAGE_MAX,";
     sBuf = sBuf + "MAGE_TAN,MAGE_SPAN,HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,";
     sBuf = sBuf + "HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,ZAKUT_MIN,ZAKUT_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,";
     sBuf = sBuf + "REVCNT,MEMO,UPDYMD,UPDTIM,";
     sBuf = sBuf + "SK_MAGEG, MAGEG_MIN, MAGEG_MAX, MAGEG_TAN, MAGEG_SPAN) ";
     sBuf = sBuf + " values('";
     sBuf = sBuf + KM02.DTKSCOD                 + "','" ;   // ���Ӑ�R�[�h
     sBuf = sBuf + KM02.DTKSNAM                 + "','" ;   // ���Ӑ於��
     sBuf = sBuf + KM02.DTKSHIN                 + "','" ;   // ���Ӑ�i��
     sBuf = sBuf + KM02.HINBAN                  + "','" ;   // ���Еi��
     sBuf = sBuf + KM02.ZISCOD                  + "','" ;   // �ގ��R�[�h
     sBuf = sBuf + KM02.ZISNAM                  + "','" ;   // �ގ���
     sBuf = sBuf + KM02.SYOSCOD                 + "',"  ;   // �Đ��R�[�h

     sBuf = sBuf + IntToStr(KM02.SORTKEY)       +  ","  ;   // �\�[�g�L�[
     sBuf = sBuf + IntToStr(KM02.KEIJKBN)       +  ","  ;   // �`��敪
     sBuf = sBuf + IntToStr(KM02.SK_LD_LNG)     +  ","  ;   // ����敪�@������
     sBuf = sBuf + IntToStr(KM02.SK_BURASI)     +  ","  ;   // ����敪�@�u���V��
     sBuf = sBuf + IntToStr(KM02.SK_BURASIT)    +  ","  ;   // ����敪�@�u���V���c����
     sBuf = sBuf + IntToStr(KM02.SK_LD_TR)      +  ","  ;   // ����敪�@����t��R
     sBuf = sBuf + IntToStr(KM02.SK_LD_HP)      +  ","  ;   // ����敪�@���������x

     sBuf = sBuf + IntToStr(KM02.SK_BOTAI)      +  ","  ;   // ����敪�@��̔�d
     sBuf = sBuf + IntToStr(KM02.SK_KOYU)       +  ","  ;   // ����敪�@�ŗL��R
     sBuf = sBuf + IntToStr(KM02.SK_MAGE)       +  ","  ;   // ����敪�@�R�ܗ�
     sBuf = sBuf + IntToStr(KM02.SK_HSC_A)      +  ","  ;   // ����敪�@HsC�d�x�i���ʁj
     sBuf = sBuf + IntToStr(KM02.SK_HSC_S)      +  ","  ;   // ����敪�@HsC�d�x�i���ʁj
     sBuf = sBuf + IntToStr(KM02.SK_HSD_A)      +  ","  ;   // ����敪�@HsD�d�x�i���ʁj
     sBuf = sBuf + IntToStr(KM02.SK_HSD_S)      +  ","  ;   // ����敪�@HsD�d�x�i���ʁj

     sBuf = sBuf + IntToStr(KM02.SK_ZAKUT)      +  ","  ;   // ����敪�@����
     sBuf = sBuf + IntToStr(KM02.HIST_SOKUT)    +  ","  ;   // �q�X�g�O�����i���萔�j
     sBuf = sBuf + IntToStr(KM02.HIST_KIKAK)    +  ","  ;   // �q�X�g�O�����i�K�i�j
     sBuf = sBuf + FloatToStr(KM02.HIST_MIN)    +  ","  ;   // �q�X�g�O�����i�����j
     sBuf = sBuf + FloatToStr(KM02.HIST_MAX)    +  ","  ;   // �q�X�g�O�����i����j
     sBuf = sBuf + FloatToStr(KM02.LD_LNG_MIN)  +  ","  ;   // ���[�h�������i�����j

     sBuf = sBuf + FloatToStr(KM02.LD_LNG_MAX)  +  ","  ;   // ���[�h�������i����j
     sBuf = sBuf + FloatToStr(KM02.BURASI_MIN)  +  ","  ;   // �u���V���i�����j
     sBuf = sBuf + FloatToStr(KM02.BURASI_MAX)  +  ","  ;   // �u���V���i����j
     sBuf = sBuf + FloatToStr(KM02.BURASIT_MIN) +  ","  ;   // �u���V���c�����i�����j
     sBuf = sBuf + FloatToStr(KM02.BURASIT_MAX) +  ","  ;   // �u���V���c�����i����j
     sBuf = sBuf + FloatToStr(KM02.LD_TR_DENA)  +  ","  ;   // ���[�h��t��R�i�d���j

     sBuf = sBuf + IntToStr(KM02.LD_TR_DENR)    +  ","  ;   // ���[�h��t��R�i�d���j
     sBuf = sBuf + IntToStr(KM02.LD_TR_TIME)    +  ",'" ;   // ���[�h��t��R�i���ԁj
     sBuf = sBuf + KM02.LD_TR_TYPE              + "',"  ;   // ���[�h��t��R�iTYPE�j
     sBuf = sBuf + FloatToStr(KM02.LD_HP_KYO)   +  ","  ;   // ���[�h���������x
     sBuf = sBuf + IntToStr(KM02.LD_HP_TAN)     +  ","  ;   // ���[�h���������x�i�P�ʁj
     sBuf = sBuf + IntToStr(KM02.LD_HP_SPD)     +  ","  ;   // ���[�h���������x�i���x�j
     sBuf = sBuf + FloatToStr(KM02.BOTAI_MIN)   +  ","  ;   // ��̔�d�i�����j

     sBuf = sBuf + FloatToStr(KM02.BOTAI_MAX)   +  ","  ;   // ��̔�d�i����j
     sBuf = sBuf + IntToStr(KM02.KOYU_MIN)      +  ","  ;   // �ŗL��R���i�����j
     sBuf = sBuf + IntToStr(KM02.KOYU_MAX)      +  ","  ;   // �ŗL��R���i����j
     sBuf = sBuf + FloatToStr(KM02.KOYU_DEN)    +  ","  ;   // �ŗL��R���i�d���j
     sBuf = sBuf + IntToStr(KM02.KOYU_PRO)      +  ","  ;   // �ŗL��R���i�v���[�u�j
     sBuf = sBuf + FloatToStr(KM02.MAGE_MIN)    +  ","  ;   // �Ȃ����x�i�����j
     sBuf = sBuf + FloatToStr(KM02.MAGE_MAX)    +  ","  ;   // �Ȃ����x�i����j

     sBuf = sBuf + IntToStr(KM02.MAGE_TAN)      +  ","  ;   // �Ȃ����x�i�P�ʁj
     sBuf = sBuf + FloatToStr(KM02.MAGE_SPAN)   +  ","  ;   // �Ȃ����x�i�X�p���j
     sBuf = sBuf + IntToStr(KM02.HSC_A_MIN)     +  ","  ;   // HsC�d�x ���ʁi�����j
     sBuf = sBuf + IntToStr(KM02.HSC_A_MAX)     +  ","  ;   // HsC�d�x ���ʁi����j
     sBuf = sBuf + IntToStr(KM02.HSC_S_MIN)     +  ","  ;   // HsC�d�x ���ʁi�����j
     sBuf = sBuf + IntToStr(KM02.HSC_S_MAX)     +  ","  ;   // HsC�d�x ���ʁi����j
     sBuf = sBuf + FloatToStr(KM02.HSD_A_MIN)   +  ","  ;   // HsD�d�x ���ʁi�����j

     sBuf = sBuf + FloatToStr(KM02.HSD_A_MAX)   +  ","  ;   // HsD�d�x ���ʁi����j
     sBuf = sBuf + FloatToStr(KM02.HSD_S_MIN)   +  ","  ;   // HsD�d�x ���ʁi�����j
     sBuf = sBuf + FloatToStr(KM02.HSD_S_MAX)   +  ","  ;   // HsD�d�x ���ʁi����j
     sBuf = sBuf + IntToStr(KM02.ZAKUT_MIN)     +  ","  ;   // �����i�����j
     sBuf = sBuf + IntToStr(KM02.ZAKUT_MAX)     +  ",'" ;   // �����i����j
     sBuf = sBuf + KM02.ADDYMD                  + "','" ;   // �o�^��
     sBuf = sBuf + KM02.ADDTIM                  + "',"  ;   // �o�^����
     sBuf = sBuf + IntToStr(KM02.UPDCHR)        +  ","  ;   // �X�V��
     sBuf = sBuf + IntToStr(KM02.UPDCNT)        +  ","  ;   // �X�V��
     sBuf = sBuf + IntToStr(KM02.REVCNT)        +  ",'" ;   // �����ԍ�
     sBuf = sBuf + KM02.MEMO                    +  "','" ;   // ���l
     sBuf = sBuf + KM02.UPDYMD                  + "','" ;   // �X�V��
     sBuf = sBuf + KM02.UPDTIM                  + "',"  ;   // �X�V����
     sBuf = sBuf + IntToStr(KM02.SK_MAGEG)       +  ","  ;   // ����敪�@�R�ܗ�
     sBuf = sBuf + FloatToStr(KM02.MAGEG_MIN)    +  ","  ;   // �Ȃ����x�i�����j
     sBuf = sBuf + FloatToStr(KM02.MAGEG_MAX)    +  ","  ;   // �Ȃ����x�i����j
     sBuf = sBuf + IntToStr(KM02.MAGEG_TAN)      +  ","  ;   // �Ȃ����x�i�P�ʁj
     sBuf = sBuf + FloatToStr(KM02.MAGEG_SPAN)   +  ")"  ;   // �Ȃ����x�i�X�p���j

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// �f�[�^���C�����܂��B
bool __fastcall TForm1::CollectData(String OldKey)
{

     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "update KM02 set ";
     sBuf = sBuf + "DTKSCOD='" + KM02.DTKSCOD                    + "', " ;   // ���Ӑ�R�[�h
     sBuf = sBuf + "DTKSNAM='" + KM02.DTKSNAM                    + "', " ;   // ���Ӑ於��
     sBuf = sBuf + "DTKSHIN='" + KM02.DTKSHIN                    + "', " ;   // ���Ӑ�i��
     sBuf = sBuf + "HINBAN='" + KM02.HINBAN                      + "', " ;   // ���Еi��
     sBuf = sBuf + "ZISCOD='" + KM02.ZISCOD                      + "', " ;   // �ގ��R�[�h
     sBuf = sBuf + "ZISNAM='" + KM02.ZISNAM                      + "', " ;   // �ގ���
     sBuf = sBuf + "SYOSCOD='" + KM02.SYOSCOD                    + "', " ;   // �Đ��R�[�h

     sBuf = sBuf + "SORTKEY=" + IntToStr(KM02.SORTKEY)           +  ", " ;   // �\�[�g�L�[
     sBuf = sBuf + "KEIJKBN=" + IntToStr(KM02.KEIJKBN)           +  ", " ;   // �`��敪
     sBuf = sBuf + "SK_LD_LNG=" + IntToStr(KM02.SK_LD_LNG)       +  ", " ;   // ����敪�@������
     sBuf = sBuf + "SK_BURASI=" + IntToStr(KM02.SK_BURASI)       +  ", " ;   // ����敪�@�u���V��
     sBuf = sBuf + "SK_BURASIT=" + IntToStr(KM02.SK_BURASIT)     +  ", " ;   // ����敪�@�u���V���c����
     sBuf = sBuf + "SK_LD_TR=" + IntToStr(KM02.SK_LD_TR)         +  ", " ;   // ����敪�@����t��R
     sBuf = sBuf + "SK_LD_HP=" + IntToStr(KM02.SK_LD_HP)         +  ", " ;   // ����敪�@���������x

     sBuf = sBuf + "SK_BOTAI=" + IntToStr(KM02.SK_BOTAI)         +  ", " ;   // ����敪�@��̔�d
     sBuf = sBuf + "SK_KOYU=" + IntToStr(KM02.SK_KOYU)           +  ", " ;   // ����敪�@�ŗL��R
     sBuf = sBuf + "SK_MAGE=" + IntToStr(KM02.SK_MAGE)           +  ", " ;   // ����敪�@�R�ܗ�
     sBuf = sBuf + "SK_HSC_A=" + IntToStr(KM02.SK_HSC_A)         +  ", " ;   // ����敪�@HsC�d�x�i���ʁj
     sBuf = sBuf + "SK_HSC_S=" + IntToStr(KM02.SK_HSC_S)         +  ", " ;   // ����敪�@HsC�d�x�i���ʁj
     sBuf = sBuf + "SK_HSD_A=" + IntToStr(KM02.SK_HSD_A)         +  ", " ;   // ����敪�@HsD�d�x�i���ʁj
     sBuf = sBuf + "SK_HSD_S=" + IntToStr(KM02.SK_HSD_S)         +  ", " ;   // ����敪�@HsD�d�x�i���ʁj

     sBuf = sBuf + "SK_ZAKUT=" + IntToStr(KM02.SK_ZAKUT)         +  ", " ;   // ����敪�@����
     sBuf = sBuf + "HIST_SOKUT=" + IntToStr(KM02.HIST_SOKUT)     +  ", " ;   // �q�X�g�O�����i���萔�j
     sBuf = sBuf + "HIST_KIKAK=" + IntToStr(KM02.HIST_KIKAK)     +  ", " ;   // �q�X�g�O�����i�K�i�j
     sBuf = sBuf + "HIST_MIN=" + FloatToStr(KM02.HIST_MIN)       +  ", " ;   // �q�X�g�O�����i�����j
     sBuf = sBuf + "HIST_MAX=" + FloatToStr(KM02.HIST_MAX)       +  ", " ;   // �q�X�g�O�����i����j
     sBuf = sBuf + "LD_LNG_MIN=" + FloatToStr(KM02.LD_LNG_MIN)   +  ", " ;   // ���[�h�������i�����j

     sBuf = sBuf + "LD_LNG_MAX=" + FloatToStr(KM02.LD_LNG_MAX)   +  ", " ;   // ���[�h�������i����j
     sBuf = sBuf + "BURASI_MIN=" + FloatToStr(KM02.BURASI_MIN)   +  ", " ;   // �u���V���i�����j
     sBuf = sBuf + "BURASI_MAX=" + FloatToStr(KM02.BURASI_MAX)   +  ", " ;   // �u���V���i����j
     sBuf = sBuf + "BURASIT_MIN=" + FloatToStr(KM02.BURASIT_MIN) +  ", " ;   // �u���V���c�����i�����j
     sBuf = sBuf + "BURASIT_MAX=" + FloatToStr(KM02.BURASIT_MAX) +  ", " ;   // �u���V���c�����i����j
     sBuf = sBuf + "LD_TR_DENA=" + FloatToStr(KM02.LD_TR_DENA)   +  ", " ;   // ���[�h��t��R�i�d���j

     sBuf = sBuf + "LD_TR_DENR=" + IntToStr(KM02.LD_TR_DENR)     +  ", " ;   // ���[�h��t��R�i�d���j
     sBuf = sBuf + "LD_TR_TIME=" + IntToStr(KM02.LD_TR_TIME)     +  ", " ;   // ���[�h��t��R�i���ԁj
     sBuf = sBuf + "LD_TR_TYPE='" + KM02.LD_TR_TYPE              + "', " ;   // ���[�h��t��R�iTYPE�j
     sBuf = sBuf + "LD_HP_KYO=" + FloatToStr(KM02.LD_HP_KYO)     +  ", " ;   // ���[�h���������x
     sBuf = sBuf + "LD_HP_TAN=" + IntToStr(KM02.LD_HP_TAN)       +  ", " ;   // ���[�h���������x�i�P�ʁj
     sBuf = sBuf + "LD_HP_SPD=" + IntToStr(KM02.LD_HP_SPD)       +  ", " ;   // ���[�h���������x�i���x�j
     sBuf = sBuf + "BOTAI_MIN=" + FloatToStr(KM02.BOTAI_MIN)     +  ", " ;   // ��̔�d�i�����j

     sBuf = sBuf + "BOTAI_MAX=" + FloatToStr(KM02.BOTAI_MAX)     +  ", " ;   // ��̔�d�i����j
     sBuf = sBuf + "KOYU_MIN=" + IntToStr(KM02.KOYU_MIN)         +  ", " ;   // �ŗL��R���i�����j
     sBuf = sBuf + "KOYU_MAX=" + IntToStr(KM02.KOYU_MAX)         +  ", " ;   // �ŗL��R���i����j
     sBuf = sBuf + "KOYU_DEN=" + FloatToStr(KM02.KOYU_DEN)       +  ", " ;   // �ŗL��R���i�d���j
     sBuf = sBuf + "KOYU_PRO=" + IntToStr(KM02.KOYU_PRO)         +  ", " ;   // �ŗL��R���i�v���[�u�j
     sBuf = sBuf + "MAGE_MIN=" + FloatToStr(KM02.MAGE_MIN)       +  ", " ;   // �Ȃ����x�i�����j
     sBuf = sBuf + "MAGE_MAX=" + FloatToStr(KM02.MAGE_MAX)       +  ", " ;   // �Ȃ����x�i����j

     sBuf = sBuf + "MAGE_TAN=" + IntToStr(KM02.MAGE_TAN)         +  ", " ;   // �Ȃ����x�i�P�ʁj
     sBuf = sBuf + "MAGE_SPAN=" + FloatToStr(KM02.MAGE_SPAN)     +  ", " ;   // �Ȃ����x�i�X�p���j
     sBuf = sBuf + "HSC_A_MIN=" + IntToStr(KM02.HSC_A_MIN)       +  ", " ;   // HsC�d�x ���ʁi�����j
     sBuf = sBuf + "HSC_A_MAX=" + IntToStr(KM02.HSC_A_MAX)       +  ", " ;   // HsC�d�x ���ʁi����j
     sBuf = sBuf + "HSC_S_MIN=" + IntToStr(KM02.HSC_S_MIN)       +  ", " ;   // HsC�d�x ���ʁi�����j
     sBuf = sBuf + "HSC_S_MAX=" + IntToStr(KM02.HSC_S_MAX)       +  ", " ;   // HsC�d�x ���ʁi����j
     sBuf = sBuf + "HSD_A_MIN=" + FloatToStr(KM02.HSD_A_MIN)     +  ", " ;   // HsD�d�x ���ʁi�����j

     sBuf = sBuf + "HSD_A_MAX=" + FloatToStr(KM02.HSD_A_MAX)     +  ", " ;   // HsD�d�x ���ʁi����j
     sBuf = sBuf + "HSD_S_MIN=" + FloatToStr(KM02.HSD_S_MIN)     +  ", " ;   // HsD�d�x ���ʁi�����j
     sBuf = sBuf + "HSD_S_MAX=" + FloatToStr(KM02.HSD_S_MAX)     +  ", " ;   // HsD�d�x ���ʁi����j
     sBuf = sBuf + "ZAKUT_MIN=" + IntToStr(KM02.ZAKUT_MIN)       +  ", " ;   // �����i�����j
     sBuf = sBuf + "ZAKUT_MAX=" + IntToStr(KM02.ZAKUT_MAX)       +  ", " ;   // �����i����j
     sBuf = sBuf + "UPDYMD='"    + KM02.UPDYMD                   + "', " ;   // �ύX��
     sBuf = sBuf + "UPDTIM='"    + KM02.UPDTIM                   + "', " ;   // �ύX����
     sBuf = sBuf + "UPDCHR="     + IntToStr(KM02.UPDCHR)         +  ", " ;   // �X�V��
     sBuf = sBuf + "UPDCNT="     + IntToStr(KM02.UPDCNT)         +  ","  ;   // �X�V��
     sBuf = sBuf + "REVCNT="     + IntToStr(KM02.REVCNT)         +  ", "  ;  // �����ԍ�
     sBuf = sBuf + "MEMO='"      + KM02.MEMO				     +  "' "  ;  // ���l
     sBuf = sBuf + "SK_MAGEG=" + IntToStr(KM02.SK_MAGEG)           +  ", " ;   // ����敪�@�R�ܗ�
     sBuf = sBuf + "MAGEG_MIN=" + FloatToStr(KM02.MAGEG_MIN)       +  ", " ;   // �Ȃ����x�i�����j
     sBuf = sBuf + "MAGEG_MAX=" + FloatToStr(KM02.MAGEG_MAX)       +  ", " ;   // �Ȃ����x�i����j
     sBuf = sBuf + "MAGEG_TAN=" + IntToStr(KM02.MAGEG_TAN)         +  ", " ;   // �Ȃ����x�i�P�ʁj
     sBuf = sBuf + "MAGGE_SPAN=" + FloatToStr(KM02.MAGEG_SPAN)     +  ", " ;   // �Ȃ����x�i�X�p���j

     sBuf = sBuf + "where DTKSHIN='" + OldKey + "'";
     sBuf = sBuf + "and REVCNT=" + IntToStr(KM02.REVCNT);

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// �f�[�^���폜���܂��B
bool __fastcall TForm1::DelData()
{

     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "select DTKSHIN from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // ���Ӑ�i��
     //2002/11/19 E.Takase �����ɉ����ԍ��ǉ�
     sBuf += " AND REVCNT =" + IntToStr(KM02.REVCNT); // �����ԍ�

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "�Y���̓��Ӑ�i�Ԃ�������܂���B�폜�ł��܂���ł����B";
            SBr1->Update();
            Beep();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }



     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "delete from KM02 where DTKSHIN='";
     sBuf += KM02.DTKSHIN + "'";        // ���Ӑ�i��
     //2002/11/19 E.Takase �����ɉ����ԍ��ǉ�
     sBuf += " AND REVCNT =" + IntToStr(KM02.REVCNT); // �����ԍ�


     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         ClpBrd = Clipboard();
         ClpBrd->Open();
         ClpBrd->SetTextBuf(sBuf.c_str());
         ClpBrd->Close();
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         Beep();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// �ގ��K�i�}�X�^�f�[�^����f�[�^���Z�b�g���܂��B
void __fastcall TForm1::SetZAISHITSU(int flag,String KeyStr )
{
    AnsiString sBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

    // �⍇�����s
    if( flag == 1 ){
        sBuf = "select ZISNAM,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
        sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX";
        sBuf = sBuf + " from KM03 where ZISCOD like '";
        sBuf = sBuf + KeyStr + "'";
    }
    else{
        sBuf = "select ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
        sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX";
        sBuf = sBuf + " from KM03 where ZISNAM like '";
        sBuf = sBuf + KeyStr + "'";
    }
    Query1->SQL->Add(sBuf);

    // �₢�������̎��s
    try
    {
        ClpBrd = Clipboard();
        ClpBrd->Open();
        ClpBrd->SetTextBuf(sBuf.c_str());
        ClpBrd->Close();
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            // �������ʖ���
            SBr1->Panels->Items[0]->Text = "�Y���̍ގ��K�i�f�[�^��������܂���B";
            SBr1->Update();
            Beep();
            return;
        }
        else{
            // �������ʗL��

            if( flag != 1 ){
                sBuf = Query1->Fields->Fields[0]->AsString;      // �ގ��R�[�h
                Edt06->Text = sBuf;
            }
            else{
                sBuf = Query1->Fields->Fields[0]->AsString;      // �ގ�����
                Edt05->Text = sBuf;
            }

            sBuf = FormatFloat("0.00",Query1->Fields->Fields[1]->AsFloat);      // ��̔�d�i�����j
            EdtF1->Text = sBuf;

            sBuf = FormatFloat("0.00",Query1->Fields->Fields[2]->AsFloat);      // ��̔�d�i����j
            EdtF2->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[3]->AsInteger);              // �ŗL��R���i�����j
            EdtG1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[4]->AsInteger);              // �ŗL��R���i����j
            EdtG2->Text = sBuf;

            sBuf = FormatFloat("0.###",Query1->Fields->Fields[5]->AsFloat);     // �Ȃ����x�i�����j
            EdtH1->Text = sBuf;

            sBuf = FormatFloat("0.###",Query1->Fields->Fields[6]->AsFloat);     // �Ȃ����x�i����j
            EdtH2->Text = sBuf;

            switch( Query1->Fields->Fields[7]->AsInteger ){
                case 1: ComBoxE2->ItemIndex = 0;    break;     // Kgf
                case 2: ComBoxE2->ItemIndex = 1;    break;     // N/cm2
                case 3: ComBoxE2->ItemIndex = 2;    break;     // MPa
                case 4: ComBoxE2->ItemIndex = 3;    break;     // N/mm2
            }

            sBuf = IntToStr(Query1->Fields->Fields[8]->AsInteger);              // �g���b�d�x�@���ʁi�����j
            EdtI1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[9]->AsInteger);             // �g���b�d�x�@���ʁi����j
            EdtI2->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[10]->AsInteger);             // �g���b�d�x�@���ʁi�����j
            EdtJ1->Text = sBuf;

            sBuf = IntToStr(Query1->Fields->Fields[11]->AsInteger);             // �g���b�d�x�@���ʁi����j
            EdtJ2->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[12]->AsFloat);      // �g���c�d�x�@���ʁi�����j
            EdtK1->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[13]->AsFloat);      // �g���c�d�x�@���ʁi����j
            EdtK2->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[14]->AsFloat);      // �g���c�d�x�@���ʁi�����j
            EdtL1->Text = sBuf;

            sBuf = FormatFloat("0.0",Query1->Fields->Fields[15]->AsFloat);      // �g���c�d�x�@���ʁi����j
            EdtL2->Text = sBuf;

            return;
        }
    }
    catch(EDatabaseError& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
    }
    catch(Exception& e)
    {
        SBr1->Panels->Items[0]->Text = e.Message;
        SBr1->Update();
        Beep();
        return;
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
                if( Database1->InTransaction == True )  Database1->Commit();
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                if( Database1->InTransaction == True )  Database1->Rollback();
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
                break;
        }
    }
    else{
        if( Database1->InTransaction == True )  Database1->Commit();
    }

}


void __fastcall TForm1::FormEnter(TObject *Sender)
{

    if( SGr1->Tag == 1 )    return;
    if( BtnF01->Focused() )    return;



    // �������@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
    if( EdtCOD1->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 1;
        return;
    }

    // �������@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    if( EdtCOD2->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 2;
        return;
    }

    // �������@���Еi�ԂɃt�H�[�J�X���L��ꍇ
    if( EdtCOD3->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 3;
        return;
    }

    // �������@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
    if( EdtCOD4->Focused() ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 4;
        return;
    }

    // �ڍו��@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt01->Focused() ){
    if( Edt01->Focused() && Edt01->ReadOnly == false ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 5;
        return;
    }

    // �ڍו��@���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt02->Focused() ){
    if( Edt02->Focused() && Edt02->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 6;
        return;
    }

    // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt03->Focused() ){
    if( Edt03->Focused() && Edt03->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 7;
        return;
    }

    // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt04->Focused() ){
    if( Edt04->Focused() && Edt04->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 8;
        return;
    }

    // �ڍו��@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt05->Focused() ){
    if( Edt05->Focused() && Edt05->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 9;
        return;
    }

    // �ڍו��@�ގ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt06->Focused()  ){
    if( Edt06->Focused() && Edt06->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 10;
        return;
    }

    // �ڍו��@�Đ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
    // 2002/11/14 E.Takase
    //if( Edt07->Focused() ){
    if( Edt07->Focused() && Edt07->ReadOnly == false  ){
        // �uF1�F�ꗗ�����v�{�^�����g����悤�ɂ���
        BtnF01->Enabled = true;
        BtnF01->Tag = 11;
        return;
    }

    // �uF1�F�ꗗ�����v�{�^�����g���Ȃ��悤�ɂ���
    BtnF01->Enabled = false;
    BtnF01->Tag = 0;

}


//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ValueChenge(TObject *Sender)
{
    // if( ComBox11->Focused() || Edt12->Focused() || Edt13->Focused() ){
        if( Edt12->Value < Edt13->Value || ComBox11->ItemIndex != 0 ){
            Edt12->Font->Color = clBlack;
            Edt13->Font->Color = clBlack;
        }
        else{
            Edt12->Font->Color = clRed;
            Edt13->Font->Color = clRed;
        }
    //}

    if( EdtA1->Focused() || EdtA2->Focused() || EdtA1->Enabled || EdtA2->Enabled ){
        if( EdtA1->Value < EdtA2->Value ){
            EdtA1->Font->Color = clBlack;
            EdtA2->Font->Color = clBlack;
        }
        else{
            EdtA1->Font->Color = clRed;
            EdtA2->Font->Color = clRed;
        }
    }
    if( EdtB1->Focused() || EdtB2->Focused() || EdtB1->Enabled || EdtB2->Enabled ){
        if( EdtB1->Value < EdtB2->Value ){
            EdtB1->Font->Color = clBlack;
            EdtB2->Font->Color = clBlack;
        }
        else{
            EdtB1->Font->Color = clRed;
            EdtB2->Font->Color = clRed;
        }
    }
    if( EdtC1->Focused() || EdtC2->Focused() || EdtC1->Enabled || EdtC2->Enabled ){
        if( EdtC1->Value < EdtC2->Value ){
            EdtC1->Font->Color = clBlack;
            EdtC2->Font->Color = clBlack;
        }
        else{
            EdtC1->Font->Color = clRed;
            EdtC2->Font->Color = clRed;
        }
    }
    if( EdtD1->Focused() || EdtD2->Focused() || EdtD1->Enabled || EdtD2->Enabled ){
        if( EdtD1->Value < EdtD2->Value ){
            EdtD1->Font->Color = clBlack;
            EdtD2->Font->Color = clBlack;
        }
        else{
            EdtD1->Font->Color = clRed;
            EdtD2->Font->Color = clRed;
        }
    }
    if( EdtG1->Focused() || EdtG2->Focused() || EdtG1->Enabled || EdtG2->Enabled ){
        if( EdtG1->Value < EdtG2->Value ){
            EdtG1->Font->Color = clBlack;
            EdtG2->Font->Color = clBlack;
        }
        else{
            EdtG1->Font->Color = clRed;
            EdtG2->Font->Color = clRed;
        }
    }
    if( EdtH1->Focused() || EdtH2->Focused() || EdtH1->Enabled || EdtH2->Enabled ){
        if( EdtH1->Value < EdtH2->Value ){
            EdtH1->Font->Color = clBlack;
            EdtH2->Font->Color = clBlack;
        }
        else{
            EdtH1->Font->Color = clRed;
            EdtH2->Font->Color = clRed;
        }
    }
    if( EdtI1->Focused() || EdtI2->Focused() || EdtI1->Enabled || EdtI2->Enabled ){
        if( EdtI1->Value < EdtI2->Value ){
            EdtI1->Font->Color = clBlack;
            EdtI2->Font->Color = clBlack;
        }
        else{
            EdtI1->Font->Color = clRed;
            EdtI2->Font->Color = clRed;
        }
    }
    if( EdtJ1->Focused() || EdtJ2->Focused() || EdtJ1->Enabled || EdtJ2->Enabled ){
        if( EdtJ1->Value < EdtJ2->Value ){
            EdtJ1->Font->Color = clBlack;
            EdtJ2->Font->Color = clBlack;
        }
        else{
            EdtJ1->Font->Color = clRed;
            EdtJ2->Font->Color = clRed;
        }
    }
    if( EdtK1->Focused() || EdtK2->Focused() || EdtK1->Enabled || EdtK2->Enabled ){
        if( EdtK1->Value < EdtK2->Value ){
            EdtK1->Font->Color = clBlack;
            EdtK2->Font->Color = clBlack;
        }
        else{
            EdtK1->Font->Color = clRed;
            EdtK2->Font->Color = clRed;
        }
    }
    if( EdtL1->Focused() || EdtL2->Focused() || EdtL1->Enabled || EdtL2->Enabled ){
        if( EdtL1->Value < EdtL2->Value ){
            EdtL1->Font->Color = clBlack;
            EdtL2->Font->Color = clBlack;
        }
        else{
            EdtL1->Font->Color = clRed;
            EdtL2->Font->Color = clRed;
        }
    }
    if( EdtM1->Focused() || EdtM2->Focused() || EdtM1->Enabled || EdtM2->Enabled ){
        if( EdtM1->Value < EdtM2->Value ){
            EdtM1->Font->Color = clBlack;
            EdtM2->Font->Color = clBlack;
        }
        else{
            EdtM1->Font->Color = clRed;
            EdtM2->Font->Color = clRed;
        }
    }
    //2002/12/05 E.Takase �����Ȃ������ǉ�
    if( EdtN1->Focused() || EdtN2->Focused() || EdtN1->Enabled || EdtN2->Enabled ){
        if( EdtN1->Value < EdtN2->Value ){
            EdtN1->Font->Color = clBlack;
            EdtN2->Font->Color = clBlack;
        }
        else{
            EdtN1->Font->Color = clRed;
            EdtN2->Font->Color = clRed;
        }
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edt10Change(TObject *Sender)
{
    // �q�X�g�O�������萔�̃`�F�b�N
    if( Edt10->Value > 0 ){
        Pnl11->Color = 0x00FEE7BA;
        Pnl11->Font->Color = clBlack;
        Pnl12->Color = 0x00FEE7BA;
        Pnl12->Font->Color = clBlack;
        Pnl13->Color = 0x00FEE7BA;
        Pnl13->Font->Color = clBlack;
        ComBox11->Enabled = true;
        Edt12->Enabled = true;
        Edt13->Enabled = true;
    }
    else{
        Pnl11->Color = clSilver;
        Pnl11->Font->Color = clGray;
        Pnl12->Color = clSilver;
        Pnl12->Font->Color = clGray;
        Pnl13->Color = clSilver;
        Pnl13->Font->Color = clGray;
        ComBox11->Enabled = false;
        Edt12->Enabled = false;
        Edt13->Enabled = false;
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::SGr1DrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{

   RECT r=RECT(Rect);

   //�Œ�Z���̔w�i�F���Z�b�g
   if(State.Contains(gdFixed))
       SGr1->Canvas->Brush->Color= SGr1->FixedColor;
   //�t�H�[�J�X�̂���Z���̔w�i�F���Z�b�g
//   else if(State.Contains(gdFocused))
//       SGr1->Canvas->Brush->Color= SGr1->Options.Contains(goDrawFocusSelected)? clHighlight: SGr1->Color;
   //�I������Ă���Z���̔w�i�F���Z�b�g
   else if(State.Contains(gdSelected))
       SGr1->Canvas->Brush->Color= clHighlight;
   //���ʂ̃Z���̔w�i�F���Z�b�g
   else
       SGr1->Canvas->Brush->Color= SGr1->Color;

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
   //�ߋ��̗����f�[�^�̏ꍇ�̕����F���Z�b�g
   else if( ACol > 0 && SGr1->Cells[10][ARow].ToIntDef(0) > 0 )
       SGr1->Canvas->Font->Color = clSilver;
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
//str����a�̕����񂪊܂܂�Ă���ꍇ�Ab�ɒu�����ĕԂ�
AnsiString __fastcall TForm1::StrReplace(AnsiString str, AnsiString a, AnsiString b)
{
    int i;
    AnsiString tmpStr;

    tmpStr = str;
    while ( 1 ) {
        i = tmpStr.AnsiPos(a);
        if ( i <= 0 ) {
            return ( tmpStr );
        }

        tmpStr.Delete(i, a.Length());
        tmpStr.Insert(b, i);
    }

    return(tmpStr);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ComBox09Change(TObject *Sender)
{
    //2002/12/28 E.Takase Add
    if ( ComBox09->ItemIndex == 4 ) {
        PnlB->Caption = "���a";
        ChkBoxB->Caption = "���a";
        PnlC->Caption = "�O�a";
        ChkBoxC->Caption = "�O�a";

     } else {
        PnlB->Caption = "��׼��";
        ChkBoxB->Caption = "��׼��";
        PnlC->Caption = "��׼��(�c����)";
        ChkBoxC->Caption = "��׼��(�c����)";
     }




}
//---------------------------------------------------------------------------
