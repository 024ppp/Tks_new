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

void __fastcall TForm2::FormActivate(TObject *Sender)
{

     int i;
     int iRow;
     AnsiString sBuf;

     SGr1->Tag = 0;    // �I���t���OOFF

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     SGr1->Row = 1;     // �I���s�̏�����

     switch( Form2->Tag ){

        // �������@�Ƀt�H�[�J�X���L��ꍇ
        case 1:

            // �⍇�����s
            sBuf = "select DISTINCT KENSA_YMD from KM01";
     		sBuf += " WHERE KOJOKBN = " + IntToStr(iKojoKbn);
     		sBuf += " ORDER BY KENSA_YMD DESC";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "�����\��N����";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 200;
            break;

        // �ҏW���@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 2:

            // �⍇�����s
            sBuf = "select DISTINCT TRSCOD, TRSNAM from SM16S where TKSKBN=1";
            if( Trim(Form1->Edt02->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " and TRSCOD like '";
                sBuf = sBuf + Trim(Form1->Edt02->Text) ;
                sBuf = sBuf + "%'";
            }
            sBuf = sBuf + " ORDER BY TRSCOD";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�R�[�h";
            SGr1->Cells[2][0] = "���Ӑ於��";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 100;
            SGr1->ColWidths[2] = 400;
            break;

        // �ҏW���@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
        case 3:

            // �⍇�����s
            sBuf = "select DISTINCT DTKSHIN, HINBAN, ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Trim(Form1->Edt02->Text) != "" ){
                // ���Ӑ�R�[�h
                sBuf = sBuf + " where DTKSCOD like '";
                sBuf = sBuf + Trim(Form1->Edt02->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt03->Text) != "" ){
                // ���Ӑ�i��
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt06->Text) != "" ){
                // �ގ�����
                if( i == 1 ){   // ���Ӑ�R�[�h�̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Trim(Form1->Edt06->Text) ;
                sBuf = sBuf + "%'";
#if 1   // 2011.06.02 Y.Sano Add start
                i = 1;
#endif  // 2011.06.02 Y.Sano Add end
            }

#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // �������t���Ă��鎞
                sBuf = sBuf + " and";
            }
            else{           // �������t���Ă��Ȃ���
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY DTKSHIN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 5;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Ӑ�i��";
            SGr1->Cells[2][0] = "���Еi��";
            SGr1->Cells[3][0] = "�ގ�����";
            SGr1->Cells[4][0] = "�ގ��R�[�h";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            SGr1->ColWidths[3] = 180;
            SGr1->ColWidths[4] = 180;
            break;

        // �ҏW���@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
        case 4:

            // �⍇�����s
            sBuf = "select DISTINCT LOTBNG from SD21S";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt04->Text) != "" ){
                // ���b�gNO
                if( i == 1 ){   // ���Ӑ�i�Ԃ̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // ���Ӑ�i�Ԃ̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " LOTBNG like '";
                sBuf = sBuf + Trim(Form1->Edt04->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            sBuf = sBuf + " ORDER BY LOTBNG";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���b�gNO";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 100;
            break;

        // �ҏW���@���Еi�ԂɃt�H�[�J�X���L��ꍇ
        case 5:

            // �⍇�����s
            sBuf = "select DISTINCT HINBAN from KM02";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt05->Text) != "" ){
                // ���Еi��
                if( i == 1 ){   // �������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // �������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " HINBAN like '";
                sBuf = sBuf + Trim(Form1->Edt05->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // �������t���Ă��鎞
                sBuf = sBuf + " and";
            }
            else{           // �������t���Ă��Ȃ���
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY HINBAN";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 2;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "���Еi��";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            break;

        // �ҏW���@�ގ����́A�ގ��R�[�h�Ƀt�H�[�J�X���L��ꍇ
        case 6:
        case 7:

            // �⍇�����s
            sBuf = "select ZISNAM, ZISCOD from KM02";
            i = 0;
            if( Trim(Form1->Edt03->Text) != "" ){
                // ���Ӑ�i��
                sBuf = sBuf + " where DTKSHIN like '";
                sBuf = sBuf + Trim(Form1->Edt03->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt06->Text) != "" ){
                // �ގ�����
                if( i == 1 ){   // �ގ����̂̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // �ގ����̂̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISNAM like '";
                sBuf = sBuf + Trim(Form1->Edt06->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
            if( Trim(Form1->Edt07->Text) != "" ){
                // �ގ��R�[�h
                if( i == 1 ){   // �ގ����̂̏������t���Ă��鎞
                    sBuf = sBuf + " and";
                }
                else{           // �ގ����̂̏������t���Ă��Ȃ���
                    sBuf = sBuf + " where";
                }
                sBuf = sBuf + " ZISCOD like '";
                sBuf = sBuf + Trim(Form1->Edt07->Text) ;
                sBuf = sBuf + "%'";
                i = 1;
            }
#if 1   // 2011.06.02 Y.Sano Add start
            if( i == 1 ){   // �������t���Ă��鎞
                sBuf = sBuf + " and";
            }
            else{           // �������t���Ă��Ȃ���
                sBuf = sBuf + " where";
            }
            sBuf = sBuf + " REVCNT = 0 ";
#endif  // 2011.06.02 Y.Sano Add end
            sBuf = sBuf + " ORDER BY ZISNAM";

            // �^�C�g�����Z�b�g
            SGr1->ColCount = 3;
            SGr1->Cells[0][0] = " NO";
            SGr1->Cells[1][0] = "�ގ�����";
            SGr1->Cells[2][0] = "�ގ��R�[�h";
            SGr1->ColWidths[0] = 30;
            SGr1->ColWidths[1] = 180;
            SGr1->ColWidths[2] = 180;
            break;

        // ���̑�
        default:
            Close();
            return;
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
        SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;

        // �f�[�^
        for( i=1; i<SGr1->ColCount; i++){
            sBuf = Query1->Fields->Fields[i-1]->AsString;
            if( Form2->Tag == 1 ){
                sBuf = Form1->InsSEPA(sBuf);
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
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if( !fFind )   return;

    // �I���t���OON�̎�
    if( SGr1->Tag ){

        switch( Form2->Tag ){

            // �������@�����\����Ƀt�H�[�J�X���L��ꍇ
            case 1:
                Form1->EdtCOD->Text = SGr1->Cells[1][SGr1->Row];    // ���Ӑ�R�[�h
                Form1->EdtCOD->SetFocus();
                Form1->EdtCOD->SelectAll();
                break;

            // �ҏW���@���Ӑ�R�[�h�Ƀt�H�[�J�X���L��ꍇ
            case 2:
                Form1->Edt02->Text = SGr1->Cells[1][SGr1->Row];     // ���Ӑ�R�[�h
                Form1->Edt02->SetFocus();
                Form1->Edt02->SelectAll();
                break;

            // �ҏW���@���Ӑ�i�ԂɃt�H�[�J�X���L��ꍇ
            case 3:
                Form1->Edt03->Text = SGr1->Cells[1][SGr1->Row];      // ���Ӑ�i��
                Form1->Edt05->Text = SGr1->Cells[2][SGr1->Row];      // ���Еi��
                Form1->Edt06->Text = SGr1->Cells[3][SGr1->Row];      // �ގ�����
                Form1->Edt07->Text = SGr1->Cells[4][SGr1->Row];      // �ގ��R�[�h
                Form1->Edt03->SetFocus();
                Form1->Edt03->SelectAll();
                break;

            // �ҏW���@���b�gNO�Ƀt�H�[�J�X���L��ꍇ
            case 4:
                Form1->Edt04->Text = SGr1->Cells[1][SGr1->Row];      // ���b�gNO
                Form1->Edt04->SetFocus();
                Form1->Edt04->SelectAll();
                break;

            // �ҏW���@���Еi�ԂɃt�H�[�J�X���L��ꍇ
            case 5:
                Form1->Edt05->Text = SGr1->Cells[1][SGr1->Row];      // ���Еi��
                Form1->Edt05->SetFocus();
                Form1->Edt05->SelectAll();
                break;

            // �ҏW���@�ގ��R�[�h�A�ގ����̂Ƀt�H�[�J�X���L��ꍇ
            case 6:
            case 7:
                Form1->Edt06->Text = SGr1->Cells[1][SGr1->Row];      // �ގ�����
                Form1->Edt07->Text = SGr1->Cells[2][SGr1->Row];      // �ގ��R�[�h
                if( Form2->Tag == 6 ){
                    Form1->Edt06->SetFocus();
                    Form1->Edt06->SelectAll();
                }
                if( Form2->Tag == 7 ){
                    Form1->Edt07->SetFocus();
                    Form1->Edt07->SelectAll();
                }
                break;

        }


    }
}
//---------------------------------------------------------------------------

