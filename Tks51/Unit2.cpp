//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}


//---------------------------------------------------------------------------
// �u�e�Q�F�O���v
void __fastcall TForm2::BtnF02Click(TObject *Sender)
{
   if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// �u�e�R�F�����v
void __fastcall TForm2::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}


//---------------------------------------------------------------------------
// �u�e�S�F�I���v
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
     SGr1->Tag = 1;    // �I���t���OON
     Close();
}


//---------------------------------------------------------------------------
// �u�e�P�Q�F�߂�v
void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     Close();
}


//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{

     int i;
     int cnt;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // �I���t���OOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // �I���s�̏�����

     switch( Form1->BtnF01->Tag ){

        // �������@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 1:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSCOD, DTKSNAM from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            //2009/04/07 E.Takase �iREVCNT = 0�@�̏����ǉ��j
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY DTKSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 80;
            SGr1->ColWidths[2] = 400;
            break;

        // �������@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        case 2:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }

            //2009/04/07 E.Takase �iREVCNT = 0�@�̏����ǉ��j
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 4;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->Cells[3][0] = "�ގ�����";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            break;

        // �������@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 3:

            // �⍇�����s
            sBuf = "select DISTINCT HINBAN from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            //2009/04/07 E.Takase �iREVCNT = 0�@�̏����ǉ��j
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else  {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            sBuf = sBuf + " ORDER BY HINBAN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Еi��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            break;

        // �������@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
        case 4:

            // �⍇�����s
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Form1->EdtCOD1->Text != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Form1->EdtCOD1->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD2->Text != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�R�[�h�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Form1->EdtCOD2->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD3->Text != "" ){
                // ���Еi��
                if( i == 1 ){   // ���Ӑ�i�Ԃ̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�i�Ԃ̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Form1->EdtCOD3->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Form1->EdtCOD4->Text != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Form1->EdtCOD4->Text ;
                sBuf = sBuf + "%'";
                i = 1;
            }

            //2009/04/07 E.Takase �iREVCNT = 0�@�̏����ǉ��j
            if( i == 1 ){
                sBuf = sBuf + " and";
            } else {
                sBuf = sBuf + " where";
            }
            sBuf += " REVCNT = 0";

            
            sBuf = sBuf + " ORDER BY ZISNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "�ގ�����";
            SGr1->Cells[2][0] = "�ގ��R�[�h";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
        case 5:
        case 6:

            // �⍇�����s
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt01->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Form1->Edt01->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 7:
        case 8:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN from SD21S where length(ltrim(rtrim(DTKSHIN)))>0";
            if( Trim(Form1->Edt01->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " and DTKSCOD like '";
                sBuf = sBuf + Form1->Edt01->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form1->Edt03->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " and DTKSHIN like '";
                sBuf = sBuf + Form1->Edt03->Text ;
                sBuf = sBuf + "%'";
            }
            if( Trim(Form1->Edt04->Text) != "" ){
                // ���Еi��
                sBuf = sBuf + " and HINBAN like '";
                sBuf = sBuf + Form1->Edt04->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �ڍו��@�ގ����́A�ގ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 9:
        case 10:

            // �⍇�����s
            sBuf = "select DISTINCT ZISNAM, ZISCOD from KM03";
            if( Trim(Form1->Edt05->Text) != "" ){
                // �ގ�����
                sBuf = sBuf + " where ZISNAM like '";
                sBuf = sBuf + Form1->Edt05->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY ZISNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "�ގ�����";
            SGr1->Cells[2][0] = "�ގ��R�[�h";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // �ڍו��@�Đ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 11:

            // �⍇�����s
            sBuf = "select DISTINCT SYOSEI_CD, RO_NO, MAX_ONDO, CYCLE_TIME, MEMO from KM04";
            if( Trim(Form1->Edt07->Text) != "" ){
                // �Đ��R�[�h
                sBuf = sBuf + " where SYOSEI_CD like '";
                sBuf = sBuf + Form1->Edt07->Text ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY SYOSEI_CD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 6;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "�Đ�����";
            SGr1->Cells[2][0] = "�FNO";
            SGr1->Cells[3][0] = "MAX���x";
            SGr1->Cells[4][0] = "�������";
            SGr1->Cells[5][0] = "����";
            SGr1->ColWidths[0] = 40;
            SGr1->ColWidths[1] = 60;
            SGr1->ColWidths[2] = 60;
            SGr1->ColWidths[3] = 60;
            SGr1->ColWidths[4] = 60;
            SGr1->ColWidths[5] = 300;
            break;
    }

    Query1->SQL->Add(sBuf);
    ClpBrd = Clipboard();
    ClpBrd->Open();
    ClpBrd->SetTextBuf(sBuf.c_str());
    ClpBrd->Close();
    Query1->Open();
    Query1->Active = true;

    iRow = 0;
    while( !Query1->Eof ){

        iRow += 1;

        // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
        if( iRow >= SGr1->RowCount ){
            SGr1->RowCount = iRow;
        }

        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B

        // NO
        sBuf = iRow;
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            if( Form1->BtnF01->Tag == 9 && ( i == 3 || i == 4 ) ){
                // MAX���x�A�T�C�N���^�C��
                sBuf = Query1->Fields->Fields[i-1]->AsString;
                sBuf = AnsiString::StringOfChar(' ', 10-sBuf.Length()) + sBuf;
            }
            else{
                sBuf = Query1->Fields->Fields[i-1]->AsString;
            }
            SGr1->Cells[i][iRow] = sBuf;
        }

        // �J�[�\�������ɃZ�b�g����
        Query1->Next();
    }

    SGr1->RowCount = iRow + 1 ;

    fFind = true;
    if( iRow == 0 ){
        fFind = false;
        SGr1->RowCount = 2;
        SGr1->FixedRows = 1;
        // �������ʊY���Ȃ��̏ꍇ
        for( i=1; i<SGr1->ColCount; i++){
            SGr1->Cells[i][1] = "�Y������";
        }
    }
    SGr1->SetFocus();

}


//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
         case VK_RETURN:
              SGr1->Tag = 1;    // �I���t���OON
              Close();
              break;
     }

}



void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        switch( Form1->BtnF01->Tag ){

            // �������@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
            case 1:
                Form1->EdtCOD1->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�R�[�h
                Form1->EdtCOD1->SetFocus();
                Form1->EdtCOD1->SelectAll();
                break;

            // �������@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            case 2:
                Form1->EdtCOD2->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->EdtCOD3->Text = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                Form1->EdtCOD4->Text = SGr1->Cells[3][SGr1->Row];      // �ގ�����
                Form1->EdtCOD2->SetFocus();
                Form1->EdtCOD2->SelectAll();
                break;

            // �������@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 3:
                Form1->EdtCOD3->Text = SGr1->Cells[1][SGr1->Row];      // ���Еi��
                Form1->EdtCOD3->SetFocus();
                Form1->EdtCOD3->SelectAll();
                break;

            // �������@�ގ����̂Ƀt�H�[�J�X���L��ꍇ
            case 4:
                Form1->EdtCOD4->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form1->EdtCOD4->SetFocus();
                Form1->EdtCOD4->SelectAll();
                break;

            // �ڍו��@���Ӑ�R�[�h�A���Ӑ於�̂Ƀt�H�[�J�X���L��ꍇ
            case 5:
            case 6:
                Form1->Edt01->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�R�[�h
                Form1->Edt02->Text = SGr1->Cells[2][SGr1->Row];      // ���Ӑ於��
                if( Form1->BtnF01->Tag == 5 ){
                    Form1->Edt01->SetFocus();
                    Form1->Edt01->SelectAll();
                }
                if( Form1->BtnF01->Tag == 6 ){
                    Form1->Edt02->SetFocus();
                    Form1->Edt02->SelectAll();
                }
                break;

            // �ڍו��@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            // �ڍו��@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 7:
            case 8:
                Form1->Edt03->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->Edt04->Text = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                if( Form1->BtnF01->Tag == 7 ){
                    Form1->Edt03->SetFocus();
                    Form1->Edt03->SelectAll();
                }
                if( Form1->BtnF01->Tag == 8 ){
                    Form1->Edt04->SetFocus();
                    Form1->Edt04->SelectAll();
                }
                break;

            // �ڍו��@�ގ����́A�ގ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
            case 9:
            case 10:
                Form1->Edt05->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form1->Edt06->Text = SGr1->Cells[2][SGr1->Row];      // �ގ��R�[�h
                if( Form1->BtnF01->Tag ==  9 ){
                    Form1->Edt05->SetFocus();
                    Form1->Edt05->SelectAll();
                }
                if( Form1->BtnF01->Tag == 10 ){
                    Form1->Edt06->SetFocus();
                    Form1->Edt06->SelectAll();
                }
                break;

            // �ڍו��@�Đ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
            case 11:
                Form1->Edt07->Text = SGr1->Cells[1][SGr1->Row];      // �Đ�����
                Form1->Edt07->SetFocus();
                Form1->Edt07->SelectAll();
                break;
        }


    }
}
//---------------------------------------------------------------------------
