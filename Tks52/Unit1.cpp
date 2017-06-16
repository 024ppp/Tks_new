//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
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
     Database1->Open();

     // �O���b�h�̏�����
     SGr1->ColWidths[0]  = Panel8->Width;                    // NO
     SGr1->ColWidths[1]  = Panel43->Width;                   // �ގ�����
     SGr1->ColWidths[2]  = Panel19->Width;                   // �ގ��R�[�h
     SGr1->ColWidths[3]  = Panel16->Width / 2;               // ��̔�d�i�����j
     SGr1->ColWidths[4]  = Panel16->Width / 2 - 1;           // ��̔�d�i����j
     SGr1->ColWidths[5]  = Panel14->Width / 2;               // �ŗL��R���i�����j
     SGr1->ColWidths[6]  = Panel14->Width / 2 - 1;           // �ŗL��R���i����j
     SGr1->ColWidths[7]  = Panel14->Width / 2;               // �Ȃ����x�i�����j
     SGr1->ColWidths[8]  = Panel14->Width / 2 - 1;           // �Ȃ����x�i����j
     SGr1->ColWidths[9]  = Panel23->Width - Panel14->Width;  // �Ȃ����x�i�P�ʁj
     SGr1->ColWidths[10] = Panel28->Width / 2;               // HsC�d�x ���ʁi�����j
     SGr1->ColWidths[11] = Panel28->Width / 2;               // HsC�d�x ���ʁi����j
     SGr1->ColWidths[12] = Panel34->Width / 2;               // HsC�d�x ���ʁi�����j
     SGr1->ColWidths[13] = Panel34->Width / 2;               // HsC�d�x ���ʁi����j
     SGr1->ColWidths[14] = Panel36->Width / 2;               // HsD�d�x ���ʁi�����j
     SGr1->ColWidths[15] = Panel36->Width / 2;               // HsD�d�x ���ʁi����j
     SGr1->ColWidths[16] = Panel41->Width / 2;               // HsD�d�x ���ʁi�����j
     SGr1->ColWidths[17] = Panel41->Width / 2;               // HsD�d�x ���ʁi����j
     SGr1->ColWidths[18] = 0;                                // �X�V��
     SGr1->ColWidths[19] = 0;                                // �X�V��

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

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "��ʈ�����ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();

    Form1->Print();

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "";
    SBr1->Update();

}


//---------------------------------------------------------------------------
// �u�e�U�F����v
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    if( !BtnF06->Enabled )    return;
    Form2->QuickRep1->Preview();
//    Form2->QuickRep1->Print();
}


//---------------------------------------------------------------------------
// �u�e�V�F�����v
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int i;
     int iRow;
     AnsiString sBuf;
     AnsiString sBuf2;

    if( !BtnF07->Enabled )    return;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�������ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "select ZISNAM,ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,MAGE_MIN,MAGE_MAX,MAGE_TAN,";
     sBuf = sBuf + "HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,";
     sBuf = sBuf + "UPDCNT,ADDYMD,UPDYMD from KM03";
     i = 0;
     if( EdtCOD1->Text != "" ){
         // �ގ�����
         sBuf += " where ZISNAM like '";
         sBuf += EdtCOD1->Text ;
         sBuf += "%'";
         i = 1;
     }
     if( EdtCOD2->Text != "" ){
         // �ގ��R�[�h
         if( i == 0 )   sBuf += " where";
         else           sBuf += " and";
         sBuf += " ZISCOD like '";
         sBuf += EdtCOD2->Text ;
         sBuf += "%'";
     }
     sBuf = sBuf + " order by ZISNAM,ZISCOD";
     Query1->SQL->Add(sBuf);
     ClpBrd = Clipboard();
     ClpBrd->Open();
     ClpBrd->SetTextBuf(sBuf.c_str());
     ClpBrd->Close();
     Query1->Open();
     Query1->Active = true;

     iRow = 0;
     while( !Query1->Eof ){

          // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
          sBuf = iRow + 1;                                 // NO
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[0]->AsString;      // �ގ�����
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[1]->AsString;      // �ގ��R�[�h
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = FormatFloat("0.00",Query1->Fields->Fields[2]->AsFloat);      // ��̔�d�i�����j
          SGr1->Cells[3][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.00",Query1->Fields->Fields[3]->AsFloat);      // ��̔�d�i����j
          SGr1->Cells[4][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[4]->AsInteger);              // �ŗL��R���i�����j
          SGr1->Cells[5][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[5]->AsInteger);              // �ŗL��R���i����j
          SGr1->Cells[6][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[6]->AsFloat);     // �Ȃ����x�i�����j
          if( sBuf.Length() > 6 ){
              sBuf = FormatFloat("0",Query1->Fields->Fields[6]->AsFloat);
          }
          SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[7]->AsFloat);     // �Ȃ����x�i����j
          if( sBuf.Length() > 6 ){
              sBuf = FormatFloat("0",Query1->Fields->Fields[7]->AsFloat);
          }
          SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          switch( Query1->Fields->Fields[8]->AsInteger ){ // �Ȃ����x�i�P�ʁj
              case 1: sBuf = "Kgf/cm2";  break;   // kgf/cm2
              case 2: sBuf = "N/cm2";    break;   // N/cm2
              case 3: sBuf = "MPa";      break;   // MPa
              case 4: sBuf = "N/mm2";    break;   // N/mm2
          }
          SGr1->Cells[9][iRow] = sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[9]->AsInteger);              // �g���b�d�x�@���ʁi�����j
          SGr1->Cells[10][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[10]->AsInteger);             // �g���b�d�x�@���ʁi����j
          SGr1->Cells[11][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[11]->AsInteger);             // �g���b�d�x�@���ʁi�����j
          SGr1->Cells[12][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = IntToStr(Query1->Fields->Fields[12]->AsInteger);             // �g���b�d�x�@���ʁi����j
          SGr1->Cells[13][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[13]->AsFloat);      // �g���c�d�x�@���ʁi�����j
          SGr1->Cells[14][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[14]->AsFloat);      // �g���c�d�x�@���ʁi����j
          SGr1->Cells[15][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[15]->AsFloat);      // �g���c�d�x�@���ʁi�����j
          SGr1->Cells[16][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = FormatFloat("0.0",Query1->Fields->Fields[16]->AsFloat);      // �g���c�d�x�@���ʁi����j
          SGr1->Cells[17][iRow] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[17]->AsString;     // �X�V��
          SGr1->Cells[18][iRow] = sBuf;

          if( sBuf != "" ) {
             if( StrToInt(sBuf) > 0 )
                sBuf = Query1->Fields->Fields[19]->AsString;   // �ύX��
             else
                sBuf = Query1->Fields->Fields[18]->AsString;   // �o�^��
          }
          else{
             sBuf = Query1->Fields->Fields[18]->AsString;      // �o�^��
          }
          SGr1->Cells[19][iRow] = sBuf;                    // �X�V��

          // �J�[�\�������ɃZ�b�g����
          Query1->Next();

          iRow += 1;
     }

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

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
         SGr1SelectCell( Sender, 1, 0, true);

         SGr1->SetFocus();

         // �V�����g�����U�N�V�������J�n
         if( Database1->InTransaction == false ){
             Database1->StartTransaction();
             DataSave = false;
         }

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
     }


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
     AnsiString sBuf;

     if( !BtnF08->Enabled )    return;

     if( Edt1->Text == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�K�{���ڂ���͂��ĉ������B";
        SBr1->Update();
        Beep();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
	 if( Edt1->Text != "" ) Edt1->Text = StrReplace(Edt1->Text , "'", "_");
	 if( Edt2->Text != "" ) Edt2->Text = StrReplace(Edt2->Text , "'", "_");

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM03.ZISNAM    = Edt1->Text;      // �ގ�����
     KM03.ZISCOD    = Edt2->Text;      // �ގ��R�[�h
     KM03.BOTAI_MIN = Edt3->Value;     // ��̔�d�i�����j
     KM03.BOTAI_MAX = Edt4->Value;     // ��̔�d�i����j
     KM03.KOYU_MIN  = Edt5->Value;     // �ŗL��R���i�����j
     KM03.KOYU_MAX  = Edt6->Value;     // �ŗL��R���i����j
     KM03.MAGE_MIN  = Edt7->Value;     // �Ȃ����x�i�����j
     KM03.MAGE_MAX  = Edt8->Value;     // �Ȃ����x�i����j
     KM03.MAGE_TAN  = 0;               // �Ȃ����x�i�P�ʁj
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC�d�x ���ʁi�����j
     KM03.HSC_A_MAX = Edt10->Value;    // HsC�d�x ���ʁi����j
     KM03.HSC_S_MIN = Edt11->Value;    // HsC�d�x ���ʁi�����j
     KM03.HSC_S_MAX = Edt12->Value;    // HsC�d�x ���ʁi����j
     KM03.HSD_A_MIN = Edt13->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_A_MAX = Edt14->Value;    // HsD�d�x ���ʁi����j
     KM03.HSD_S_MIN = Edt15->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_S_MAX = Edt16->Value;    // HsD�d�x ���ʁi����j
     KM03.ADDYMD    = FormatDateTime("yyyymmdd",Date());                // �o�^��
     KM03.ADDTIM    = FormatDateTime("hhmm",TDateTime::CurrentTime());  // �o�^����
     KM03.UPDCHR    = USER_COD;        // �X�V��
     KM03.UPDCNT    = 0;               // �X�V��

     // AddData
     if( AddData() == False ){
        return;
     }

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = SGr1->RowCount ;                          // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     sBuf = KM03.ZISNAM;                              // �ގ�����
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;

     sBuf = KM03.ZISCOD;                              // �ގ��R�[�h
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MIN);       // ��̔�d�i�����j
     SGr1->Cells[3][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MAX);       // ��̔�d�i����j
     SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MIN);                  // �ŗL��R���i�����j
     SGr1->Cells[5][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MAX);                  // �ŗL��R���i����j
     SGr1->Cells[6][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MIN);         // �Ȃ����x�i�����j
     SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MAX);         // �Ȃ����x�i����j
     SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     if( KM03.MAGE_TAN == 1 ) sBuf = "Kgf/cm2";
     if( KM03.MAGE_TAN == 2 ) sBuf = "N/cm2";
     if( KM03.MAGE_TAN == 3 ) sBuf = "MPa";
     if( KM03.MAGE_TAN == 4 ) sBuf = "N/mm2";
     SGr1->Cells[9][SGr1->RowCount - 1] = sBuf;       // �Ȃ����x�i�P�ʁj

     sBuf = IntToStr(KM03.HSC_A_MIN);                 // HsC�d�x ���ʁi�����j
     SGr1->Cells[10][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_A_MAX);                 // HsC�d�x ���ʁi����j
     SGr1->Cells[11][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MIN);                 // HsC�d�x ���ʁi�����j
     SGr1->Cells[12][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MAX);                 // HsC�d�x ���ʁi����j
     SGr1->Cells[13][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MIN);        // HsD�d�x ���ʁi�����j
     SGr1->Cells[14][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MAX);        // HsD�d�x ���ʁi����j
     SGr1->Cells[15][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MIN);        // HsD�d�x ���ʁi�����j
     SGr1->Cells[16][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MAX);        // HsD�d�x ���ʁi����j
     SGr1->Cells[17][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.UPDCNT);                    // �X�V��
     SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;

     sBuf = KM03.ADDYMD;                              // �X�V��
     SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;


     // ��s���₷
     SGr1->RowCount = SGr1->RowCount + 1;

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // �V�����s��I��
     SGr1->Row = SGr1->RowCount - 1;

     Edt1->SetFocus();

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

     if( !BtnF09->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
        SBr1->Update();
        Beep();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
	 if( Edt1->Text != "" ) Edt1->Text = StrReplace(Edt1->Text , "'", "_");
	 if( Edt2->Text != "" ) Edt2->Text = StrReplace(Edt2->Text , "'", "_");

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM03.ZISNAM    = Edt1->Text;      // �ގ�����
     KM03.ZISCOD    = Edt2->Text;      // �ގ��R�[�h
     KM03.BOTAI_MIN = Edt3->Value;     // ��̔�d�i�����j
     KM03.BOTAI_MAX = Edt4->Value;     // ��̔�d�i����j
     KM03.KOYU_MIN  = Edt5->Value;     // �ŗL��R���i�����j
     KM03.KOYU_MAX  = Edt6->Value;     // �ŗL��R���i����j
     KM03.MAGE_MIN  = Edt7->Value;     // �Ȃ����x�i�����j
     KM03.MAGE_MAX  = Edt8->Value;     // �Ȃ����x�i����j
     KM03.MAGE_TAN  = 0;               // �Ȃ����x�i�P�ʁj
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC�d�x ���ʁi�����j
     KM03.HSC_A_MAX = Edt10->Value;    // HsC�d�x ���ʁi����j
     KM03.HSC_S_MIN = Edt11->Value;    // HsC�d�x ���ʁi�����j
     KM03.HSC_S_MAX = Edt12->Value;    // HsC�d�x ���ʁi����j
     KM03.HSD_A_MIN = Edt13->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_A_MAX = Edt14->Value;    // HsD�d�x ���ʁi����j
     KM03.HSD_S_MIN = Edt15->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_S_MAX = Edt16->Value;    // HsD�d�x ���ʁi����j
     KM03.UPDYMD    = FormatDateTime("yyyymmdd",Date());               // �o�^��
     KM03.UPDTIM    = FormatDateTime("hhmm",TDateTime::CurrentTime()); // �o�^����
     KM03.UPDCHR    = USER_COD;        // �X�V��
     if( SGr1->Cells[18][SGr1->Row] == "" ){
        KM03.UPDCNT  = 0;
     }
     else{
        KM03.UPDCNT  = StrToInt(SGr1->Cells[18][SGr1->Row]) ;        // �X�V��
        KM03.UPDCNT += 1 ;
     }

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row], SGr1->Cells[2][SGr1->Row]) == False ){
        return;
     }

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = KM03.ZISNAM;                              // �ގ�����
     SGr1->Cells[1][SGr1->Row] = sBuf;

     sBuf = KM03.ZISCOD;                              // �ގ��R�[�h
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MIN);       // ��̔�d�i�����j
     SGr1->Cells[3][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.00",KM03.BOTAI_MAX);       // ��̔�d�i����j
     SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MIN);                  // �ŗL��R���i�����j
     SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.KOYU_MAX);                  // �ŗL��R���i����j
     SGr1->Cells[6][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MIN);         // �Ȃ����x�i�����j
     SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.MAGE_MAX);         // �Ȃ����x�i����j
     SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     if( KM03.MAGE_TAN == 1 ) sBuf = "Kgf/cm2";
     if( KM03.MAGE_TAN == 2 ) sBuf = "N/cm2";
     if( KM03.MAGE_TAN == 3 ) sBuf = "MPa";
     if( KM03.MAGE_TAN == 4 ) sBuf = "N/mm2";
     SGr1->Cells[9][SGr1->Row] = sBuf;       // �Ȃ����x�i�P�ʁj

     sBuf = IntToStr(KM03.HSC_A_MIN);                 // HsC�d�x ���ʁi�����j
     SGr1->Cells[10][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_A_MAX);                 // HsC�d�x ���ʁi����j
     SGr1->Cells[11][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MIN);                 // HsC�d�x ���ʁi�����j
     SGr1->Cells[12][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.HSC_S_MAX);                 // HsC�d�x ���ʁi����j
     SGr1->Cells[13][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MIN);        // HsD�d�x ���ʁi�����j
     SGr1->Cells[14][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_A_MAX);        // HsD�d�x ���ʁi����j
     SGr1->Cells[15][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MIN);        // HsD�d�x ���ʁi�����j
     SGr1->Cells[16][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = FormatFloat("0.0",KM03.HSD_S_MAX);        // HsD�d�x ���ʁi����j
     SGr1->Cells[17][SGr1->Row] = AnsiString::StringOfChar(' ', 4 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM03.UPDCNT);                    // �X�V��
     SGr1->Cells[18][SGr1->Row] = sBuf;

     sBuf = KM03.UPDYMD;                              // �X�V��
     SGr1->Cells[19][SGr1->Row] = sBuf;


     SGr1->SetFocus();

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

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM03.ZISNAM    = Edt1->Text;      // �ގ���
     KM03.ZISCOD    = Edt2->Text;      // �ގ��R�[�h
     KM03.BOTAI_MIN = Edt3->Value;     // ��̔�d�i�����j
     KM03.BOTAI_MAX = Edt4->Value;     // ��̔�d�i����j
     KM03.KOYU_MIN  = Edt5->Value;     // �ŗL��R���i�����j
     KM03.KOYU_MAX  = Edt6->Value;     // �ŗL��R���i����j
     KM03.MAGE_MIN  = Edt7->Value;     // �Ȃ����x�i�����j
     KM03.MAGE_MAX  = Edt8->Value;     // �Ȃ����x�i����j
     KM03.MAGE_TAN  = 0;               // �Ȃ����x�i�P�ʁj
     if( CmbBox1->Text.UpperCase() == "KGF" ) KM03.MAGE_TAN = 1;     // kgf/cm2
     if( CmbBox1->Text.UpperCase() == "N/C" ) KM03.MAGE_TAN = 2;     // N/cm2
     if( CmbBox1->Text.UpperCase() == "N/M" ) KM03.MAGE_TAN = 4;     // N/mm2
     if( KM03.MAGE_TAN == 0                 ) KM03.MAGE_TAN = 3;     // MPa
     KM03.HSC_A_MIN = Edt9->Value;     // HsC�d�x ���ʁi�����j
     KM03.HSC_A_MAX = Edt10->Value;    // HsC�d�x ���ʁi����j
     KM03.HSC_S_MIN = Edt11->Value;    // HsC�d�x ���ʁi�����j
     KM03.HSC_S_MAX = Edt12->Value;    // HsC�d�x ���ʁi����j
     KM03.HSD_A_MIN = Edt13->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_A_MAX = Edt14->Value;    // HsD�d�x ���ʁi����j
     KM03.HSD_S_MIN = Edt15->Value;    // HsD�d�x ���ʁi�����j
     KM03.HSD_S_MAX = Edt16->Value;    // HsD�d�x ���ʁi����j
     KM03.UPDCHR    = USER_COD;        // �X�V��
     if( SGr1->Cells[18][SGr1->Row] == "" ){
        KM03.UPDCNT  = 0;
     }
     else{
        KM03.UPDCNT  = StrToInt(SGr1->Cells[18][SGr1->Row]) ;        // �X�V��
     }

     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // �O���b�h�̈�s���폜���܂��B
         SGr1->Cells[1][i]  = SGr1->Cells[1][i+1];        // �ގ�����
         SGr1->Cells[2][i]  = SGr1->Cells[2][i+1];        // �ގ��R�[�h
         SGr1->Cells[3][i]  = SGr1->Cells[3][i+1];        // ��̔�d�i�����j
         SGr1->Cells[4][i]  = SGr1->Cells[4][i+1];        // ��̔�d�i����j
         SGr1->Cells[5][i]  = SGr1->Cells[5][i+1];        // �ŗL��R���i�����j
         SGr1->Cells[6][i]  = SGr1->Cells[6][i+1];        // �ŗL��R���i����j
         SGr1->Cells[7][i]  = SGr1->Cells[7][i+1];        // �Ȃ����x�i�����j
         SGr1->Cells[8][i]  = SGr1->Cells[8][i+1];        // �Ȃ����x�i����j
         SGr1->Cells[9][i]  = SGr1->Cells[9][i+1];        // �Ȃ����x�i�P�ʁj
         SGr1->Cells[10][i] = SGr1->Cells[10][i+1];       // HsC�d�x ���ʁi�����j
         SGr1->Cells[11][i] = SGr1->Cells[11][i+1];       // HsC�d�x ���ʁi����j
         SGr1->Cells[12][i] = SGr1->Cells[12][i+1];       // HsC�d�x ���ʁi�����j
         SGr1->Cells[13][i] = SGr1->Cells[13][i+1];       // HsC�d�x ���ʁi����j
         SGr1->Cells[14][i] = SGr1->Cells[14][i+1];       // HsD�d�x ���ʁi�����j
         SGr1->Cells[15][i] = SGr1->Cells[15][i+1];       // HsD�d�x ���ʁi����j
         SGr1->Cells[16][i] = SGr1->Cells[16][i+1];       // HsD�d�x ���ʁi�����j
         SGr1->Cells[17][i] = SGr1->Cells[17][i+1];       // HsD�d�x ���ʁi����j
         SGr1->Cells[18][i] = SGr1->Cells[18][i+1];       // �X�V��
         SGr1->Cells[19][i] = SGr1->Cells[19][i+1];       // �X�V��
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



void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

     // �X�e�[�^�X���b�Z�[�W
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

     switch(Key)
     {
//         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_UP:  if( SGr1->Focused() || CmbBox1->Focused() )   break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_DOWN:if( SGr1->Focused() || CmbBox1->Focused() )   break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  // �������Ƀt�H�[�J�X������ꍇ�́A�������s
                      if( EdtCOD1->Focused() || EdtCOD2->Focused() ){
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
         case VK_LEFT:
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    Edt16->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == 0 && Edt2->SelLength == 0 ){
                    Edt1->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == 0 && Edt3->SelLength == 0 ){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == 0 && Edt4->SelLength == 0 ){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == 0 && Edt5->SelLength == 0 ){
                    Edt4->SetFocus();
                    break;
                }
                if(Edt6->Focused() && Edt6->SelStart == 0 && Edt6->SelLength == 0 ){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == 0 && Edt7->SelLength == 0 ){
                    Edt6->SetFocus();
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == 0 && Edt8->SelLength == 0 ){
                    Edt7->SetFocus();
                    break;
                }
                if(CmbBox1->Focused() && CmbBox1->SelStart == 0 && CmbBox1->SelLength == 0 && Key == VK_LEFT ){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt9->Focused() && Edt9->SelStart == 0 && Edt9->SelLength == 0 ){
                    CmbBox1->SetFocus();
                    break;
                }
                if(Edt10->Focused() && Edt10->SelStart == 0 && Edt10->SelLength == 0 ){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt11->Focused() && Edt11->SelStart == 0 && Edt11->SelLength == 0 ){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt12->Focused() && Edt12->SelStart == 0 && Edt12->SelLength == 0 ){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt13->Focused() && Edt13->SelStart == 0 && Edt13->SelLength == 0 ){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt14->Focused() && Edt14->SelStart == 0 && Edt14->SelLength == 0 ){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt15->Focused() && Edt15->SelStart == 0 && Edt15->SelLength == 0 ){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt16->Focused() && Edt16->SelStart == 0 && Edt16->SelLength == 0 ){
                    Edt15->SetFocus();
                    break;
                }
                break;

         // ����
         case VK_RIGHT:
                if(Edt1->Focused() && Edt1->SelStart == Edt1->Text.Length() && Edt1->SelLength == 0 ){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == Edt2->Text.Length() && Edt2->SelLength == 0 ){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == Edt3->Text.Length() && Edt3->SelLength == 0 ){
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == Edt4->Text.Length() && Edt4->SelLength == 0 ){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == Edt5->Text.Length() && Edt5->SelLength == 0 ){
                    Edt6->SetFocus();
                    break;
                }
                if(Edt6->Focused() && Edt6->SelStart == Edt6->Text.Length() && Edt6->SelLength == 0 ){
                    Edt7->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == Edt7->Text.Length() && Edt7->SelLength == 0 ){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == Edt8->Text.Length() && Edt8->SelLength == 0 ){
                    CmbBox1->SetFocus();
                    break;
                }
                if(CmbBox1->Focused() && CmbBox1->SelStart == CmbBox1->Text.Length() && CmbBox1->SelLength == 0 && Key == VK_RIGHT ){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt9->Focused() && Edt9->SelStart == Edt9->Text.Length() && Edt9->SelLength == 0 ){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt10->Focused() && Edt10->SelStart == Edt10->Text.Length() && Edt10->SelLength == 0 ){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt11->Focused() && Edt11->SelStart == Edt11->Text.Length() && Edt11->SelLength == 0 ){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt12->Focused() && Edt12->SelStart == Edt12->Text.Length() && Edt12->SelLength == 0 ){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt13->Focused() && Edt13->SelStart == Edt13->Text.Length() && Edt13->SelLength == 0 ){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt14->Focused() && Edt14->SelStart == Edt14->Text.Length() && Edt14->SelLength == 0 ){
                    Edt15->SetFocus();
                    break;
                }
                if(Edt15->Focused() && Edt15->SelStart == Edt15->Text.Length() && Edt15->SelLength == 0 ){
                    Edt16->SetFocus();
                    break;
                }
                if(Edt16->Focused() && Edt16->SelStart == Edt16->Text.Length() && Edt16->SelLength == 0 ){
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD1->Focused()){
                    EdtCOD2->SetFocus();
                    break;
                }
                if(EdtCOD2->Focused()){
                    BtnF07Click(Sender);
                    break;
                }
                if(Edt1->Focused()){
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused()){
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused()){
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused()){
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused()){
                    Edt6->SetFocus();
                    break;
                }
                if(Edt6->Focused()){
                    Edt7->SetFocus();
                    break;
                }
                if(Edt7->Focused()){
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused()){
                    CmbBox1->SetFocus();
                    break;
                }
                if(CmbBox1->Focused()){
                    Edt9->SetFocus();
                    break;
                }
                if(Edt9->Focused()){
                    Edt10->SetFocus();
                    break;
                }
                if(Edt10->Focused()){
                    Edt11->SetFocus();
                    break;
                }
                if(Edt11->Focused()){
                    Edt12->SetFocus();
                    break;
                }
                if(Edt12->Focused()){
                    Edt13->SetFocus();
                    break;
                }
                if(Edt13->Focused()){
                    Edt14->SetFocus();
                    break;
                }
                if(Edt14->Focused()){
                    Edt15->SetFocus();
                    break;
                }
                if(Edt15->Focused()){
                    Edt16->SetFocus();
                    break;
                }
                if(Edt16->Focused()){
                    Edt1->SetFocus();
                    break;
                }
                break;

     }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{

    // �X�e�[�^�X���b�Z�[�W
    if(SBr1->Panels->Items[0]->Text != ""){
       SBr1->Panels->Items[0]->Text = "";
       SBr1->Update();
    }

    // NO
    PnlNO->Caption = SGr1->Cells[0][ARow];
    // �ގ�����
    Edt1->Text = SGr1->Cells[1][ARow];
    // �ގ��R�[�h
    Edt2->Text = SGr1->Cells[2][ARow];
    // ��̔�d�i�����j
    Edt3->Text = SGr1->Cells[3][ARow];
    // ��̔�d�i����j
    Edt4->Text = SGr1->Cells[4][ARow];
    // �ŗL��R���i�����j
    Edt5->Text = SGr1->Cells[5][ARow];
    // �ŗL��R���i����j
    Edt6->Text = SGr1->Cells[6][ARow];
    // �Ȃ����x�i�����j
    Edt7->Text = SGr1->Cells[7][ARow];
    // �Ȃ����x�i����j
    Edt8->Text = SGr1->Cells[8][ARow];
    // �Ȃ����x�i�P�ʁj
    if( SGr1->Cells[9][ARow].UpperCase() == "KGF/CM2" )   CmbBox1->ItemIndex = 0;     // kgf/cm2
    if( SGr1->Cells[9][ARow].UpperCase() == "N/CM2"   )   CmbBox1->ItemIndex = 1;     // N/cm2
    if( SGr1->Cells[9][ARow].UpperCase() == "N/MM2"   )   CmbBox1->ItemIndex = 3;     // N/mm2
    if( SGr1->Cells[9][ARow].UpperCase() == "MPA"     )   CmbBox1->ItemIndex = 2;     // MPa
    // HsC�d�x ���ʁi�����j
    Edt9->Text = SGr1->Cells[10][ARow];
    // HsC�d�x ���ʁi����j
    Edt10->Text = SGr1->Cells[11][ARow];
    // HsC�d�x ���ʁi�����j
    Edt11->Text = SGr1->Cells[12][ARow];
    // HsC�d�x ���ʁi����j
    Edt12->Text = SGr1->Cells[13][ARow];
    // HsD�d�x ���ʁi�����j
    Edt13->Text = SGr1->Cells[14][ARow];
    // HsD�d�x ���ʁi����j
    Edt14->Text = SGr1->Cells[15][ARow];
    // HsD�d�x ���ʁi�����j
    Edt15->Text = SGr1->Cells[16][ARow];
    // HsD�d�x ���ʁi����j
    Edt16->Text = SGr1->Cells[17][ARow];

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
         case VK_RETURN:Edt1->SetFocus();       break;
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
     sBuf = "select ZISNAM from KM03 where ZISNAM='";
     sBuf += KM03.ZISNAM + "'";        // �ގ�����

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
     sBuf = "insert into KM03(ZISNAM,ZISCOD,BOTAI_MIN,BOTAI_MAX,KOYU_MIN,KOYU_MAX,";
     sBuf += "MAGE_MIN,MAGE_MAX,MAGE_TAN,HSC_A_MIN,HSC_A_MAX,HSC_S_MIN,HSC_S_MAX,";
     sBuf += "HSD_A_MIN,HSD_A_MAX,HSD_S_MIN,HSD_S_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT)";
     sBuf += " values('";
     sBuf += KM03.ZISNAM                + "','";    // �ގ�����
     sBuf += KM03.ZISCOD                + "'," ;    // �ގ��R�[�h
     sBuf += FloatToStr(KM03.BOTAI_MIN) +  "," ;    // ��̔�d�i�����j
     sBuf += FloatToStr(KM03.BOTAI_MAX) +  "," ;    // ��̔�d�i����j
     sBuf += IntToStr(KM03.KOYU_MIN)    +  "," ;    // �ŗL��R���i�����j
     sBuf += IntToStr(KM03.KOYU_MAX)    +  "," ;    // �ŗL��R���i����j
     sBuf += FloatToStr(KM03.MAGE_MIN)  +  "," ;    // �Ȃ����x�i�����j
     sBuf += FloatToStr(KM03.MAGE_MAX)  +  "," ;    // �Ȃ����x�i����j
     sBuf += FloatToStr(KM03.MAGE_TAN)  +  "," ;    // �Ȃ����x�i�P�ʁj
     sBuf += IntToStr(KM03.HSC_A_MIN)   +  "," ;    // HsC�d�x ���ʁi�����j
     sBuf += IntToStr(KM03.HSC_A_MAX)   +  "," ;    // HsC�d�x ���ʁi����j
     sBuf += IntToStr(KM03.HSC_S_MIN)   +  "," ;    // HsC�d�x ���ʁi�����j
     sBuf += IntToStr(KM03.HSC_S_MAX)   +  "," ;    // HsC�d�x ���ʁi����j
     sBuf += FloatToStr(KM03.HSD_A_MIN) +  "," ;    // HsD�d�x ���ʁi�����j
     sBuf += FloatToStr(KM03.HSD_A_MAX) +  "," ;    // HsD�d�x ���ʁi����j
     sBuf += FloatToStr(KM03.HSD_S_MIN) +  "," ;    // HsD�d�x ���ʁi�����j
     sBuf += FloatToStr(KM03.HSD_S_MAX) +  ",'";    // HsD�d�x ���ʁi����j
     sBuf += KM03.ADDYMD                + "','";    // �o�^��
     sBuf += KM03.ADDTIM                + "'," ;    // �o�^����
     sBuf += IntToStr(KM03.UPDCHR)      +  "," ;    // �X�V��
     sBuf += IntToStr(KM03.UPDCNT)      +  ")" ;    // �X�V��

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
bool __fastcall TForm1::CollectData(String OldKey1, String OldKey2)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "update KM03 set ";
     sBuf = sBuf + "ZISNAM='"    + KM03.ZISNAM                + "', ";  // �ގ�����
     sBuf = sBuf + "ZISCOD='"    + KM03.ZISCOD                + "', ";  // �ގ��R�[�h
     sBuf = sBuf + "BOTAI_MIN="  + FloatToStr(KM03.BOTAI_MIN) +  ", ";  // ��̔�d�i�����j
     sBuf = sBuf + "BOTAI_MAX="  + FloatToStr(KM03.BOTAI_MAX) +  ", ";  // ��̔�d�i����j
     sBuf = sBuf + "KOYU_MIN="   + IntToStr(KM03.KOYU_MIN)    +  ", ";  // �ŗL��R���i�����j
     sBuf = sBuf + "KOYU_MAX="   + IntToStr(KM03.KOYU_MAX)    +  ", ";  // �ŗL��R���i����j
     sBuf = sBuf + "MAGE_MIN="   + FloatToStr(KM03.MAGE_MIN)  +  ", ";  // �Ȃ����x�i�����j
     sBuf = sBuf + "MAGE_MAX="   + FloatToStr(KM03.MAGE_MAX)  +  ", ";  // �Ȃ����x�i����j
     sBuf = sBuf + "MAGE_TAN="   + FloatToStr(KM03.MAGE_TAN)  +  ", ";  // �Ȃ����x�i�P�ʁj
     sBuf = sBuf + "HSC_A_MIN="  + IntToStr(KM03.HSC_A_MIN)   +  ", ";  // HsC�d�x ���ʁi�����j
     sBuf = sBuf + "HSC_A_MAX="  + IntToStr(KM03.HSC_A_MAX)   +  ", ";  // HsC�d�x ���ʁi����j
     sBuf = sBuf + "HSC_S_MIN="  + IntToStr(KM03.HSC_S_MIN)   +  ", ";  // HsC�d�x ���ʁi�����j
     sBuf = sBuf + "HSC_S_MAX="  + IntToStr(KM03.HSC_S_MAX)   +  ", ";  // HsC�d�x ���ʁi����j
     sBuf = sBuf + "HSD_A_MIN="  + FloatToStr(KM03.HSD_A_MIN) +  ", ";  // HsD�d�x ���ʁi�����j
     sBuf = sBuf + "HSD_A_MAX="  + FloatToStr(KM03.HSD_A_MAX) +  ", ";  // HsD�d�x ���ʁi����j
     sBuf = sBuf + "HSD_S_MIN="  + FloatToStr(KM03.HSD_S_MIN) +  ", ";  // HsD�d�x ���ʁi�����j
     sBuf = sBuf + "HSD_S_MAX="  + FloatToStr(KM03.HSD_S_MAX) +  ", ";  // HsD�d�x ���ʁi����j
     sBuf = sBuf + "UPDYMD='"    + KM03.UPDYMD                + "', ";  // �o�^��
     sBuf = sBuf + "UPDTIM='"    + KM03.UPDTIM                + "', ";  // �o�^����
     sBuf = sBuf + "UPDCHR="     + IntToStr(KM03.UPDCHR)      +  ", ";  // �X�V��
     sBuf = sBuf + "UPDCNT="     + IntToStr(KM03.UPDCNT)      +  " " ;  // �X�V��
     sBuf = sBuf + "where ZISNAM='" + OldKey1 + "' and ZISCOD='";       // �ގ��R�[�h
     sBuf += OldKey2 + "'";                                             // �ގ�����

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
     sBuf = "select ZISNAM from KM03 where ZISNAM='";
     sBuf += KM03.ZISNAM + "' and ZISCOD='";        // �ގ�����
     sBuf += KM03.ZISCOD + "'";                     // �ގ��R�[�h

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

        if( Query1->Eof == True && Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "�Y���̍ގ���������܂���B�폜�ł��܂���ł����B";
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
     sBuf = "delete from KM03 where ZISCOD='";
     sBuf += KM03.ZISCOD + "' and ZISNAM='";        // �ގ��R�[�h
     sBuf += KM03.ZISNAM + "'";                     // �ގ�����

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



//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
    if( Key == VK_RETURN )   Key = 0;
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

