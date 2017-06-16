//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop

#include "Unit11.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#define COM_DIFF 0.000001
// �Βl
extern pi ;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm11 *Form11;

//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//�R�s�[���f�[�^�̎擾
void __fastcall TForm11::FormActivate(TObject *Sender)
{
    int i;

    DataCopyFlag = 0;

	SGr1->RowCount = 2;

	SGr1->Cells[0][0] = "";
	SGr1->Cells[1][0] = "";
	SGr1->Cells[0][1] = "";
	SGr1->Cells[1][1] = "";

	// �O���b�h�̏�����
	SGr1->ColCount = 10;
	SGr1->ColWidths[0]  = 50;
	SGr1->ColWidths[1]  = 230;
	SGr1->ColWidths[2]  = 50;
	SGr1->ColWidths[3]  = 40;
	SGr1->ColWidths[4]  = 100;
	SGr1->ColWidths[5]  = 100;

	SGr1->ColWidths[6]  = 0;
	SGr1->ColWidths[7]  = 0;
	SGr1->ColWidths[8]  = 0;
	SGr1->ColWidths[9]  = 0;

    i = CopyData_Serch();

    SGr1->SetFocus();
    SGr1SelectCell( Sender, 1, 1, true);

}
//---------------------------------------------------------------------------
void __fastcall TForm11::SGr1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
	// �ŏ����R�[�h���ް���ϐ��֕ۑ�
    //HIST_SOKUT
	if (  SGr1->Cells[2][ARow].IsEmpty() )  Select_Str1 = " ";
	Select_Str1 = SGr1->Cells[2][ARow] ;

	//KENSA_KMK
	if ( SGr1->Cells[6][ARow].IsEmpty() )  Select_Str2 = " ";
	Select_Str2 = SGr1->Cells[6][ARow] ;

	//SEQNO
	if ( SGr1->Cells[7][ARow].IsEmpty() )  Select_Str3 = " ";
	Select_Str3 = SGr1->Cells[7][ARow] ;

	//SOKUTE_SU
	if ( SGr1->Cells[8][ARow].IsEmpty() )  Select_Str4 = " ";
	Select_Str4 = SGr1->Cells[8][ARow] ;

	//KEIJKBN
	if ( SGr1->Cells[9][ARow].IsEmpty() )  Select_Str5 = " ";
	else Select_Str5 = SGr1->Cells[9][ARow] ;

	Select_Cnt = ARow;

}
//---------------------------------------------------------------------------
//�u�e�Q�F�O���v
void __fastcall TForm11::BtnF02Click(TObject *Sender)
{
    if(SGr1->Row > 1){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }
}
//---------------------------------------------------------------------------
// �u�e�R�F�����v
void __fastcall TForm11::BtnF03Click(TObject *Sender)
{
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}
//---------------------------------------------------------------------------
//�u�e�S�F�I���v
void __fastcall TForm11::BtnF04Click(TObject *Sender)
{
    int flag = 0;
    AnsiString sMsg;

    int n;
    int m;

    n = Cur_Kdb1.HIST_SOKUT;
    m = Select_Str4.ToIntDef(0);

    if ( n != m ) {
        sMsg = "���萔���R�s�[����f�[�^�Ƃ������܂����A�����𑱍s���܂����H";
        switch( MessageDlg( sMsg, mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v
            case mrYes:
                    break;
            // �uNo�v
            case mrNo:
                    flag = 1;
                    break;
            case mrCancel:
                    flag = 1;
                    return;
                    break;
        }
    }


    //����f�[�^���R�s�[����
    if ( flag == 0 ) {
        SetCopyData();
        DataCopyFlag = 1;
    }

    //�����ʂ�
    BtnF12Click(Sender) ;

}
//---------------------------------------------------------------------------
//�u�e�P�Q�F�I���v
void __fastcall TForm11::BtnF12Click(TObject *Sender)
{
//
     Close();

}
//---------------------------------------------------------------------------
void __fastcall TForm11::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_RETURN:
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
    }

}
//---------------------------------------------------------------------------
//�f�[�^�R�s�[�� ���@����
//---------------------------------------------------------------------------
int __fastcall TForm11::CopyData_Serch(void)
{
	AnsiString str;
	int i = 1;
    int n;
    int m;

	//KDB1����f�[�^�R�s�[�����𒊏o
	Query1->Close();
	Query1->SQL->Clear();

	sBuf = " SELECT";
	sBuf += " KENSA_YMD, DTKSHIN, HINBAN, ZISCOD, ZISNAM, LOTNO, SEQNO, ";
	sBuf += " KENSA_KMK, KOUMOKU_J, KOUMOKU_E, KEIJKBN, ";
	sBuf += " TANI, HIST_SOKUT, SOKUTE_SU, ADDYMD, UPDYMD, UPDCHR, UPDCNT ";
	sBuf += " FROM KDB1";
	sBuf += " WHERE KENSA_YMD='" +  Cur_Kdb1.KENSA_YMD + "'";
	sBuf += " AND DTKSHIN='" +  Cur_Kdb1.DTKSHIN + "'";
	sBuf += " AND LOTNO='" +  Cur_Kdb1.LOTNO + "'";
    //2002/12/28 E.Takase
	//sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 ) ";
	sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 OR KENSA_KMK=12 ) ";
	sBuf += " AND SEQNO<> "+  IntToStr(Cur_Kdb1.SEQNO) ;
	sBuf += " ORDER BY SEQNO";


	//�₢���������s

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	int iRow = 0 ;
	sBuf = "NO.";
	SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
	SGr1->Cells[1][iRow] = "��������";
	SGr1->Cells[2][iRow] = "���萔";
	SGr1->Cells[3][iRow] = "����";
	SGr1->Cells[4][iRow] = "�����";
	SGr1->Cells[5][iRow] = "�X�V��";

	SGr1->Cells[6][iRow] = "KENSA_KMK";
	SGr1->Cells[7][iRow] = "SEQNO";
	SGr1->Cells[8][iRow] = "SOKUTE_SU";
	SGr1->Cells[9][iRow] = "KEIJKBN";

    iRow += 1;

    if ( Query1->Bof == true && Query1->Eof == true) {
		SGr1->Cells[1][1]=" " ;
		SGr1->Cells[2][1]=" " ;
		SGr1->Cells[3][1]=" " ;
		SGr1->Cells[4][1]=" " ;
		SGr1->Cells[5][1]=" " ;

		ShowMessage( MSG_02 );
      return 0;
    }else {
      Query1->First();
      while( !Query1->Eof ) {

			// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
			if( iRow >= SGr1->RowCount ){
			    SGr1->RowCount = iRow+1;
			}
			sBuf = iRow ;
			SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

			sBuf = Query1->FieldValues["KOUMOKU_J"];
			SGr1->Cells[1][iRow] = sBuf;
			sBuf = Query1->FieldValues["HIST_SOKUT"];
			SGr1->Cells[2][iRow] = sBuf;

            n = Query1->FieldValues["HIST_SOKUT"];
            m = Query1->FieldValues["SOKUTE_SU"];
            if ( n == m ) {
                sBuf = "��";
            } else {
                if ( m > 0 ) {
                    sBuf = "�r��";
                } else {
                    sBuf = "��";
                }
            }
			SGr1->Cells[3][iRow] = sBuf;

			sBuf = Query1->FieldValues["UPDCHR"];
			SGr1->Cells[4][iRow] = Form2->GetTANNAM(sBuf);;
		    if ( Query1->FieldValues["UPDYMD"].IsNull()) {
                sBuf = " ";
            } else  {
                sBuf = Query1->FieldValues["UPDYMD"];
            }
            if ( Trim(sBuf) == "" ) {
		        if ( Query1->FieldValues["ADDYMD"].IsNull()) {
                    sBuf = " ";
                } else  {
                    sBuf = Query1->FieldValues["ADDYMD"];
                }
            }
            if ( Trim(sBuf) != "" ) {
                sBuf = sBuf.Insert("/",5);
                sBuf = sBuf.Insert("/",8);
            }
			SGr1->Cells[5][iRow] = sBuf;

			sBuf = Query1->FieldValues["KENSA_KMK"];
			SGr1->Cells[6][iRow] = sBuf;
			sBuf = Query1->FieldValues["SEQNO"];
			SGr1->Cells[7][iRow] = sBuf;
			sBuf = Query1->FieldValues["SOKUTE_SU"];
			SGr1->Cells[8][iRow] = sBuf;
			sBuf = Query1->FieldValues["KEIJKBN"];
			SGr1->Cells[9][iRow] = sBuf;

            iRow += 1;
            Query1->Next();
      }
   }

   SGr1->RowCount = iRow;

   return (iRow) ;

}
//---------------------------------------------------------------------------
//�f�[�^�R�s�[�� �Z�b�g
//---------------------------------------------------------------------------
void __fastcall TForm11::SetCopyData(void)
{

	AnsiString str;
	int i = 1;
    int n;
    int T_No;

	//KDB2���瑪��l�𒊏o
	Query1->Close();
    Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
    sBuf = "SELECT ";
    sBuf += " SOKUTEI_NO, SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, ";
    sBuf += " SOKUTEI_MEI4, SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7 ";
    sBuf += " FROM KDB2 ";
    sBuf += " WHERE KENSA_YMD = '" + Cur_Kdb1.KENSA_YMD + "' " + " AND SEQNO = '" + Select_Str3 + "' ";
    sBuf += " AND DTKSHIN = '" + Cur_Kdb1.DTKSHIN + "' " + " AND LOTNO = '" + Cur_Kdb1.LOTNO + "' ";
    sBuf += " AND SOKUTEI_NO <= " + IntToStr(Cur_Kdb1.HIST_SOKUT) ;
    sBuf += " ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

	//�₢���������s
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    i = 0;
    if ( Query1->Bof == true && Query1->Eof == true) {
        ShowMessage( MSG_02 );
        return ;
    }else {
        Query1->First();
        while( !Query1->Eof ) {
            //����l �R�s�[
            if ( Query1->FieldValues["SOKUTEI_NO"].IsNull()) {
                i = 0;
            } else {
                i = Query1->FieldValues["SOKUTEI_NO"]-1;
            }
            if ( i < Cur_Kdb1.HIST_SOKUT ) {
                //�R���~ �ȊO�̏ꍇ
                if ( Select_Str5 != "3" ) {
                    if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                        M_Kdb2[i].SOKUTEI_MEI1 = 0;
                    else
                        M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];

                    if ( Query1->FieldValues["SOKUTEI_MEI2"].IsNull())
                        M_Kdb2[i].SOKUTEI_MEI2 = 0;
                    else
                        M_Kdb2[i].SOKUTEI_MEI2 = Query1->FieldValues["SOKUTEI_MEI2"];

                    //�R�s�[�� ��̂̏ꍇ �������R�s�[
                    if ( Cur_Kdb1.KENSA_KMK == 5 && Select_Str2 == "5" ) {
                        if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                            M_Kdb2[i].SOKUTEI_MEI3 = 0;
                        else
                            M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI3"];
                    }
                //�R���~�̏ꍇ
                } else {
                    //�R�s�[�� ��̂̏ꍇ
                    if ( Select_Str2 == "5" ) {
                        //�R�s�[�� ��̂̏ꍇ
                        if ( Cur_Kdb1.KENSA_KMK == 5 ) {
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];

                            if ( Query1->FieldValues["SOKUTEI_MEI2"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI2 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI2 = Query1->FieldValues["SOKUTEI_MEI2"];

                            if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI3 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI3"];

                        } else {
                        //�R�s�[�� ��̈ȊO�̏ꍇ
                            if ( Query1->FieldValues["SOKUTEI_MEI3"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI3"];
                        }
                    } else {
                    //�R�s�[�� ��̈ȊO�̏ꍇ
                        //�R�s�[�� ��̂̏ꍇ
                        //if ( Cur_Kdb1.KEIJKBN == 3 ) {
                        if ( Cur_Kdb1.KENSA_KMK == 5 ) {
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI3 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI3 = Query1->FieldValues["SOKUTEI_MEI1"];
                        } else {
                        //�R�s�[�� ��̈ȊO�̏ꍇ
                            if ( Query1->FieldValues["SOKUTEI_MEI1"].IsNull())
                                M_Kdb2[i].SOKUTEI_MEI1 = 0;
                            else
                                M_Kdb2[i].SOKUTEI_MEI1 = Query1->FieldValues["SOKUTEI_MEI1"];
                        }
                    }

                }
            }

            Query1->Next();
        }

        //�Čv�Z
        switch( Cur_Kdb1.KENSA_KMK ) {
            //��̔�d
            case 5:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Botai_Cal2(i);
                }
                break;
            //��R��
            case 7:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Teikou_Cal2(i);
                }
                break;
            //�Ȃ�����
            //�Ȃ�����(����)
            case 8:
            case 12:
                for ( i = 0; i < Cur_Kdb1.HIST_SOKUT; i++ ) {
                    Kousetu_Cal2(i);
                }
                break;
        }


    }


}
//---------------------------------------------------------------------------
//�f�[�^�R�s�[�������݂��邩���`�F�b�N
//---------------------------------------------------------------------------
bool __fastcall TForm11::ChkCopyData(void)
{

	AnsiString str;
	int i = 1;
    int n;
    int T_No;

	//KDB2���瑪��l�𒊏o
	Query1->Close();
    Query1->SQL->Clear();

    //�₢���������s
    //�����\����A�g���[No
	sBuf = " SELECT";
	sBuf += " KENSA_YMD, DTKSHIN, HINBAN, ZISCOD, ZISNAM, LOTNO, SEQNO, ";
	sBuf += " KENSA_KMK, KOUMOKU_J, KOUMOKU_E, KEIJKBN, ";
	sBuf += " TANI, HIST_SOKUT, SOKUTE_SU, ADDYMD, UPDYMD, UPDCHR, UPDCNT ";
	sBuf += " FROM KDB1";
	sBuf += " WHERE KENSA_YMD='" +  Cur_Kdb1.KENSA_YMD + "'";
	sBuf += " AND DTKSHIN='" +  Cur_Kdb1.DTKSHIN + "'";
	sBuf += " AND LOTNO='" +  Cur_Kdb1.LOTNO + "'";
	sBuf += " AND (KENSA_KMK=5 OR KENSA_KMK=7 OR KENSA_KMK=8 ) ";
	sBuf += " AND SEQNO<> "+  IntToStr(Cur_Kdb1.SEQNO) ;
	sBuf += " ORDER BY SEQNO";

	//�₢���������s
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

    i = 0;
    if ( Query1->Bof == true && Query1->Eof == true) {
        return false;
    }else {
        return true;
    }
}
//---------------------------------------------------------------------------
// ��̔�d�v�Z
// �����́F �d�� / �i���� * �� * �����j
// �~���F ���a * ���a * PI /4 * ����
// �R���~�F �d�� / �o�i�i���a/2�j*�i���a/2�j* PI�j - �i�i���a/2�j*�i���a/2�j* PI�j�p* ����
void __fastcall TForm11::Botai_Cal2(int i)
{
 char tempo[64];
 
 M_Kdb2[i].SOKUTEI_CH = 0;
 
 // �~��
 if (Cur_Kdb1.KEIJKBN == 2) {
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI4 /
                                  (M_Kdb2[i].SOKUTEI_MEI2/10.0 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI3/40.0);
       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);
    }
 //�R���~
 } else if (Cur_Kdb1.KEIJKBN == 3) {
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       if ( M_Kdb2[i].SOKUTEI_MEI1 == M_Kdb2[i].SOKUTEI_MEI2 ) {

          M_Kdb2[i].SOKUTEI_CH = 0;
       } else {

          M_Kdb2[i].SOKUTEI_CH =  M_Kdb2[i].SOKUTEI_MEI4/
										((pi*(M_Kdb2[i].SOKUTEI_MEI2/2.0)
											*(M_Kdb2[i].SOKUTEI_MEI2/2.0) -
										pi*(M_Kdb2[i].SOKUTEI_MEI1/2.0)
											*(M_Kdb2[i].SOKUTEI_MEI1/2.0))
										*M_Kdb2[i].SOKUTEI_MEI3/1000.0);
          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
    }
 //������
 } else {
 
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI4 /
                                  (M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI3/10.0);
       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
 
 }
}

//---------------------------------------------------------------------------
// �R�ܗ͌v�Z
// �����́FN/(cm * cm): (300 * ���� * �X�p��) / ( 2 * �� * ���� * �����j
//         MPa: (3 * �X�p�� * ����) / (2 * �� * ���� * �����j
// �~���F  N/(cm * cm): (8 * ���� * �X�p��) / ( 100 * PI * ���a * ���a * ���a�j
//         MPa: (8 * �X�p�� * ����) / (PI * ���a * ���a * ���a�j
// �R���~ �F ����
void __fastcall TForm11::Kousetu_Cal2(int i)
{
 char tempo[64];

 M_Kdb2[i].SOKUTEI_CH = 0;

 //�~��
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 100.0 * M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2")  {
       if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4) /
                                   ( M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI2) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    // N/(cm * cm) or Kfg
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = (8.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( M_Kdb2[i].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI2/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 //�R���~
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = M_Kdb2[i].SOKUTEI_MEI3 ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
    return;

 //������
 } else {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 200.0 * M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2" )  {
       if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4) /
                                   ( 2.0 * M_Kdb2[i].SOKUTEI_MEI2 *
                                   M_Kdb2[i].SOKUTEI_MEI1 *
                                   M_Kdb2[i].SOKUTEI_MEI1) ;

          sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
          M_Kdb2[i].SOKUTEI_CH = atof(tempo);

       }
       return;
    }

    // N/(cm * cm)  or Kfg
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[i].SOKUTEI_CH = (3.0 * M_Kdb2[i].SOKUTEI_MEI3 *
                                  M_Kdb2[i].SOKUTEI_MEI4/10.0) /
                                   ( 2.0 * M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[i].SOKUTEI_MEI1/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }
    return;
 }


}

//---------------------------------------------------------------------------

// �ŗL��R���v�Z
// �����́F(���� * �� * ���ϓd�� * 1000) / (���ϓd�� * �v���[�u)
// �~���F�i���ϓd�� * ���a * ���a * PI * 1000) / (���ϓd�� * �v���[�u)
// �R���~�F ���ϓd��
void __fastcall TForm11::Teikou_Cal2(int i)
{
 char tempo[64];

 M_Kdb2[i].SOKUTEI_CH = 0;

 //�~��
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI2/10.0 *
                                  M_Kdb2[i].SOKUTEI_MEI2/10.0 * pi/4 * 1000.0 *
                                  (M_Kdb2[i].SOKUTEI_MEI3 +
                                   M_Kdb2[i].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[i].SOKUTEI_MEI4 +
                                   M_Kdb2[i].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[i].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 //�R���~
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI3 + M_Kdb2[i].SOKUTEI_MEI5) / 2.0 ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 } else {
 //������
    if (M_Kdb2[i].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[i].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[i].SOKUTEI_CH = (M_Kdb2[i].SOKUTEI_MEI1/10.0 *
                                  M_Kdb2[i].SOKUTEI_MEI2/10.0 * 1000.0 *
                                  (M_Kdb2[i].SOKUTEI_MEI3 +
                                   M_Kdb2[i].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[i].SOKUTEI_MEI4 +
                                   M_Kdb2[i].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[i].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[i].SOKUTEI_CH);
       M_Kdb2[i].SOKUTEI_CH = atof(tempo);

    }

 }

}
//---------------------------------------------------------------------------
