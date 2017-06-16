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
     SGr1->ColWidths[0]  = Panel8->Width;       // NO
     SGr1->ColWidths[1]  = Panel43->Width;      // �Đ��d�l�R�[�h
     SGr1->ColWidths[2]  = Panel19->Width;      // �FNo
     SGr1->ColWidths[3]  = Panel16->Width;      // �ō����x
     SGr1->ColWidths[4]  = Panel14->Width;      // �T�C�N������
     SGr1->ColWidths[5]  = Panel23->Width;      // ����
     SGr1->ColWidths[6]  = 0;                   // �X�V��
     SGr1->ColWidths[7]  = 0;                   // �X�V��

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

     if( !BtnF07->Enabled )    return;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�������ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "select SYOSEI_CD,RO_NO,MAX_ONDO,CYCLE_TIME,MEMO,UPDCNT,ADDYMD,UPDYMD from KM04";
     if( EdtCOD->Text != "" ){
         sBuf += " where SYOSEI_CD like '";
         sBuf += EdtCOD->Text ;
         sBuf += "%'";
     }
     sBuf = sBuf + " order by SYOSEI_CD";
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

          sBuf = Query1->Fields->Fields[0]->AsString;      // �Đ��R�[�h
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[1]->AsString;      // �FNO
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[2]->AsString;      // �ō����x
          SGr1->Cells[3][iRow] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;      // �T�C�N�����x
          SGr1->Cells[4][iRow] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;      // ����
          SGr1->Cells[5][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;      // �X�V��
          SGr1->Cells[6][iRow] = sBuf;

          if( sBuf != "" ) {
             if( StrToInt(sBuf) > 0 )
                sBuf = Query1->Fields->Fields[7]->AsString;   // �ύX��
             else
                sBuf = Query1->Fields->Fields[6]->AsString;   // �o�^��
          }
          else{
             sBuf = Query1->Fields->Fields[6]->AsString;   // �o�^��
          }
          SGr1->Cells[7][iRow] = sBuf;

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
         EdtCOD->SetFocus();

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
         // �O���b�h��I��
         SGr1SelectCell( Sender, 1, 0, true);

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
	 if( Edt5->Text != "" ) Edt5->Text = StrReplace(Edt5->Text , "'", "_");

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM04.SYOSEI_CD  = Edt1->Text;        // �Đ��R�[�h
     KM04.RO_NO      = Edt2->Text;        // �FNO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX���x
     KM04.CYCLE_TIME = Edt4->Value;       // �T�C�N���^�C��
     KM04.MEMO       = Edt5->Text;        // ����
     KM04.ADDYMD     = FormatDateTime("yyyymmdd",Date());               // �o�^��
     KM04.ADDTIM     = FormatDateTime("hhmm",TDateTime::CurrentTime()); // �o�^����
     KM04.UPDCHR     = USER_COD;          // �X�V��
     KM04.UPDCNT     = 0;                 // �X�V��

     // AddData
     if( AddData() == False ){
        return;
     }

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = SGr1->RowCount ;                            // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;

     sBuf = KM04.SYOSEI_CD;                           // �Đ��R�[�h
     SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;

     sBuf = KM04.RO_NO;                               // �FNO
     SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;

     sBuf = IntToStr(KM04.MAX_ONDO);                  // �ō����x
     SGr1->Cells[3][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM04.CYCLE_TIME);                // �T�C�N�����x
     SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = KM04.MEMO;                                // ����
     SGr1->Cells[5][SGr1->RowCount - 1] = sBuf;

     sBuf = IntToStr(KM04.UPDCNT);                    // �X�V��
     SGr1->Cells[6][SGr1->RowCount - 1] = sBuf;

     sBuf = KM04.ADDYMD;                              // �X�V��
     SGr1->Cells[7][SGr1->RowCount - 1] = sBuf;

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
	 if( Edt5->Text != "" ) Edt5->Text = StrReplace(Edt5->Text , "'", "_");

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     KM04.SYOSEI_CD  = Edt1->Text;        // �Đ��R�[�h
     KM04.RO_NO      = Edt2->Text;        // �FNO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX���x
     KM04.CYCLE_TIME = Edt4->Value;       // �T�C�N���^�C��
     KM04.MEMO       = Edt5->Text;        // ����
     KM04.UPDYMD     = FormatDateTime("yyyymmdd",Date());               // �o�^��
     KM04.UPDTIM     = FormatDateTime("hhmm",TDateTime::CurrentTime()); // �o�^����
     KM04.UPDCHR     = USER_COD;          // �X�V��
     if( SGr1->Cells[6][SGr1->Row] == "" ){
        KM04.UPDCNT  = 0;
     }
     else{
        KM04.UPDCNT  = StrToInt(SGr1->Cells[6][SGr1->Row]);
        KM04.UPDCNT += 1 ;                  // �X�V��
     }

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row]) == False ){
        return;
     }

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = KM04.SYOSEI_CD;                           // �Đ��R�[�h
     SGr1->Cells[1][SGr1->Row] = sBuf;

     sBuf = KM04.RO_NO;                               // �FNO
     SGr1->Cells[2][SGr1->Row] = sBuf;

     sBuf = IntToStr(KM04.MAX_ONDO);                  // �ō����x
     SGr1->Cells[3][SGr1->Row] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = IntToStr(KM04.CYCLE_TIME);                // �T�C�N�����x
     SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 10 - sBuf.Length()) + sBuf;

     sBuf = KM04.MEMO;                                // ����
     SGr1->Cells[5][SGr1->Row] = sBuf;

     sBuf = IntToStr(KM04.UPDCNT);                    // �X�V��
     SGr1->Cells[6][SGr1->Row] = sBuf;

     sBuf = KM04.UPDYMD;                              // �X�V��
     SGr1->Cells[7][SGr1->Row] = sBuf;

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
     KM04.SYOSEI_CD  = Edt1->Text;        // �Đ��R�[�h
     KM04.RO_NO      = Edt2->Text;        // �FNO
     KM04.MAX_ONDO   = Edt3->Value;       // MAX���x
     KM04.CYCLE_TIME = Edt4->Value;       // �T�C�N���^�C��
     KM04.MEMO       = Edt5->Text;        // ����
     KM04.UPDCHR     = USER_COD;          // �X�V��
     if( SGr1->Cells[6][SGr1->Row] == "" ){
        KM04.UPDCNT  = 0;
     }
     else{
        KM04.UPDCNT  = StrToInt(SGr1->Cells[6][SGr1->Row]) ;        // �X�V��
     }

     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // �O���b�h�̈�s���폜���܂��B
         SGr1->Cells[1][i] = SGr1->Cells[1][i+1];        // �Đ��R�[�h
         SGr1->Cells[2][i] = SGr1->Cells[2][i+1];        // �FNO
         SGr1->Cells[3][i] = SGr1->Cells[3][i+1];        // �ō����x
         SGr1->Cells[4][i] = SGr1->Cells[4][i+1];        // �T�C�N�����x
         SGr1->Cells[5][i] = SGr1->Cells[5][i+1];        // ����
         SGr1->Cells[6][i] = SGr1->Cells[6][i+1];        // �X�V��
         SGr1->Cells[7][i] = SGr1->Cells[7][i+1];        // �X�V��
     }

     // ��s���炷
     SGr1->RowCount = SGr1->RowCount - 1;

     // �V�����s��I��
     if( SGr1->RowCount == SGr1->Row)    SGr1->Row = SGr1->Row - 1;
     else                                SGr1->Row = SGr1->Row;

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     //SGr1->SetFocus();

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
         case VK_UP:  if( SGr1->Focused() )   break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_DOWN:if( SGr1->Focused() )   break;
         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
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
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    Edt5->SetFocus();
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
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD->Focused()){
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
    // �Đ��R�[�h
    Edt1->Text = SGr1->Cells[1][ARow];
    // �FNO
    Edt2->Text = SGr1->Cells[2][ARow];
    // �ō����x
    Edt3->Text = SGr1->Cells[3][ARow];
    // �T�C�N������
    Edt4->Text = SGr1->Cells[4][ARow];
    // ����
    Edt5->Text = SGr1->Cells[5][ARow];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SGr1_KeyPress(TObject *Sender, char &Key)
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
     sBuf = "select SYOSEI_CD from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // �Đ��R�[�h

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
     sBuf = "insert into KM04(SYOSEI_CD,RO_NO,MAX_ONDO,CYCLE_TIME,MEMO,ADDYMD,ADDTIM,UPDCHR,UPDCNT)";
     sBuf += " values('";
     sBuf += KM04.SYOSEI_CD             + "','";        // �Đ��R�[�h
     sBuf += KM04.RO_NO                 + "'," ;        // �FNO
     sBuf += IntToStr(KM04.MAX_ONDO)    +  "," ;        // MAX���x
     sBuf += IntToStr(KM04.CYCLE_TIME)  +  ",'";        // �T�C�N���^�C��
     sBuf += KM04.MEMO                  + "','";        // ����
     sBuf += KM04.ADDYMD                + "','";        // �o�^��
     sBuf += KM04.ADDTIM                + "'," ;        // �o�^����
     sBuf += IntToStr(KM04.UPDCHR)      +  "," ;        // �X�V��
     sBuf += IntToStr(KM04.UPDCNT)      +  ")" ;        // �X�V��

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
     sBuf = "update KM04 set ";
     sBuf = sBuf + "SYOSEI_CD='"  + KM04.SYOSEI_CD            + "', ";  // �Đ��R�[�h
     sBuf = sBuf + "RO_NO='"      + KM04.RO_NO                + "', ";  // �FNO
     sBuf = sBuf + "MAX_ONDO="    + IntToStr(KM04.MAX_ONDO)   + ", " ;  // MAX���x
     sBuf = sBuf + "CYCLE_TIME="  + IntToStr(KM04.CYCLE_TIME) + ", " ;  // �T�C�N���^�C��
     sBuf = sBuf + "MEMO='"       + KM04.MEMO                 + "', ";  // ����
     sBuf = sBuf + "UPDYMD='"     + KM04.UPDYMD               + "', ";  // �X�V��
     sBuf = sBuf + "UPDTIM='"     + KM04.UPDTIM               + "', ";  // �X�V����
     sBuf = sBuf + "UPDCHR="      + IntToStr(KM04.UPDCHR)     + ", " ;  // �X�V��
     sBuf = sBuf + "UPDCNT="      + IntToStr(KM04.UPDCNT)     + " "  ;  // �X�V��
     sBuf = sBuf + "where SYOSEI_CD='" + OldKey + "'";

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
     sBuf = "select SYOSEI_CD from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // �Đ��R�[�h

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
            SBr1->Panels->Items[0]->Text = "�Y���̏Đ��R�[�h��������܂���B�폜�ł��܂���ł����B";
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
     sBuf = "delete from KM04 where SYOSEI_CD='";
     sBuf += KM04.SYOSEI_CD + "'";        // �Đ��R�[�h


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

