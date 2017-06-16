//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

int iRec ;
int FlagToday ;

int KENSA_YMD_Serch01(int flag);
int DTKSHIN_Serch01(int flag);
int DTKSHIN_Serch02(int flag);
AnsiString sRowNo = "";

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//�u�e�S�F�I���v
void __fastcall TForm2::BtnF04Click(TObject *Sender)
{
	int tmp;
    switch(KENSAKU_Mode)
    {
         case 1://�������ɑI�������f�[�^�����
                //Form1->EdtYMD->Text = Form1->InsSEPA(Select_Str1);
                Form1->EdtYMD->Text = Select_Str1;
                Form1->EdtHIN->Text = Select_Str2;
                Form1->EdtZISNAM->Caption = Select_Str3;
                Form1->EdtZIS->Text = Select_Str5;
                Form1->EdtLOT->Text = Select_Str4;
                Form1->EdtLOT->SetFocus();
                tmp = Form1->DTKSHIN_Serch(); //����̋K�i�l������
                break;

         case 2://���Ӑ�i��
                Form1->EdtHIN->Text = Select_Str1;
                Form1->EdtZISNAM->Caption = Select_Str2;
                //2002/11/18 E.Takase
                if ( FlagToday == 0) {
                    Form1->EdtLOT->Text = Select_Str4;
                    Form1->EdtZIS->Text = Select_Str5;
                } else {
                    Form1->EdtZIS->Text = Select_Str4;
                }
                Form1->EdtLOT->SetFocus();
                break;

         //case 3://���b�gNO
         //       Form1->EdtLOT->Text = Select_Str1;
         //       Form1->EdtYMD->SetFocus();
         //      break;

    }

     Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BtnF12Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormActivate(TObject *Sender)
{

    iRec = 0;
	Form2->SGr1->RowCount = 2;

	Form2->SGr1->Cells[0][0] = "";
	Form2->SGr1->Cells[1][0] = "";
	Form2->SGr1->Cells[0][1] = "";
	Form2->SGr1->Cells[1][1] = "";

    switch(KENSAKU_Mode)
    {
        case 1:
                // �O���b�h�̏�����
                SGr1->ColCount = 7;
                SGr1->ColWidths[0]  = 50;
                SGr1->ColWidths[1]  = 75;
                SGr1->ColWidths[2]  = 200;
                SGr1->ColWidths[3]  = 150;
                SGr1->ColWidths[4]  = 60;
                SGr1->ColWidths[5]  = 95;
                SGr1->ColWidths[6]  = 0;

     			//����
     			iRec = KENSA_YMD_Serch01(KENSAKU_Mode);
                break;

        case 2:
                // �O���b�h�̏�����
                SGr1->ColCount = 6;
                if ( StrToDate(Form1->EdtYMD->Text) == Date() ) {
                	//������ == ����
                    FlagToday = 1;
                	SGr1->ColWidths[0]  = 50;
                	SGr1->ColWidths[1]  = 200;
                	SGr1->ColWidths[2]  = 200;
                	SGr1->ColWidths[3]  = 95;
                	SGr1->ColWidths[4]  = 0;
                	SGr1->ColWidths[5]  = 0;
                    //����
                    iRec = DTKSHIN_Serch01(KENSAKU_Mode);
                } else {
                	//������ != ����
                    FlagToday = 0;
                	SGr1->ColWidths[0]  = 50;
                	SGr1->ColWidths[1]  = 200;
                	SGr1->ColWidths[2]  = 200;
                	SGr1->ColWidths[3]  = 90;
                	SGr1->ColWidths[4]  = 0;
                	SGr1->ColWidths[5]  = 0;
                    //����
                    iRec = DTKSHIN_Serch02(KENSAKU_Mode);

                }

                break;
        //case 3:
        //        SGr1->ColCount = 2;
        //        // �O���b�h�̏�����
        //        SGr1->ColWidths[0]  = 50;
        //        SGr1->ColWidths[1]  = 90;
        //        break;
    }

     if( iRec > 0){
        // �J�\�[�����ŏ����R�[�h�֐ݒ�
        SGr1->Row = 1;
        SGr1->SetFocus();

        switch(KENSAKU_Mode)
        {
            case 1:
                // �ŏ����R�[�h���ް���ϐ��֕ۑ�
                Select_Str1 = SGr1->Cells[1][1] ;
                Select_Str2 = SGr1->Cells[2][1] ;
                Select_Str3 = SGr1->Cells[3][1] ;
                Select_Str4 = SGr1->Cells[4][1] ;
                Select_Str5 = SGr1->Cells[6][1] ;
                break;
            case 2:
                // �ŏ����R�[�h���ް���ϐ��֕ۑ�
                Select_Str1 = SGr1->Cells[1][1] ;
                Select_Str2 = SGr1->Cells[2][1] ;
                Select_Str3 = SGr1->Cells[3][1] ;
                Select_Str4 = SGr1->Cells[4][1] ;
                Select_Str5 = SGr1->Cells[5][1] ;
                break;
            //case 3:
            //    // �ŏ����R�[�h���ް���ϐ��֕ۑ�
            //    Select_Str1 = SGr1->Cells[1][1] ;
            //    break;
        }

        BtnF02->Enabled = true;
        BtnF03->Enabled = true;
        BtnF04->Enabled = true;

        //2001.02.26 �f�[�^�폜�{�^���ǉ�
        switch(KENSAKU_Mode)
        {
            case 1:
         		BtnF10->Enabled = true;
                break;
            default:
         		BtnF10->Enabled = false;
                break;
        }

      }else{
         BtnF02->Enabled = false;
         BtnF03->Enabled = false;
         BtnF04->Enabled = false;
         BtnF10->Enabled = false;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    ////���ă��R�[�h���ް���ϐ��֕ۑ�
    //Select_Str1 = SGr1->Cells[1][ARow] ;
    //Select_Str2 = SGr1->Cells[2][ARow] ;
    //Select_Str3 = SGr1->Cells[3][ARow] ;
    //Select_Str4 = SGr1->Cells[4][ARow] ;
    switch(KENSAKU_Mode)
    {
        case 1:
            // �ŏ����R�[�h���ް���ϐ��֕ۑ�
            if (  SGr1->Cells[1][ARow].IsEmpty() )  Select_Str1 = " ";
            Select_Str1 = SGr1->Cells[1][ARow] ;

            if ( SGr1->Cells[2][ARow].IsEmpty() )  Select_Str2 = " ";
            Select_Str2 = SGr1->Cells[2][ARow] ;

            if ( SGr1->Cells[3][ARow].IsEmpty() )  Select_Str3 = " ";
            Select_Str3 = SGr1->Cells[3][ARow] ;

            if ( SGr1->Cells[4][ARow].IsEmpty() )  Select_Str4 = " ";
            Select_Str4 = SGr1->Cells[4][ARow] ;

            if ( SGr1->Cells[6][ARow].IsEmpty() )  Select_Str5 = " ";
            else Select_Str5 = SGr1->Cells[6][ARow] ;
            break;

        case 2:
            // �ŏ����R�[�h���ް���ϐ��֕ۑ�
            if (  SGr1->Cells[1][ARow].IsEmpty() )  Select_Str1 = " ";
            Select_Str1 = SGr1->Cells[1][ARow] ;

            if ( SGr1->Cells[2][ARow].IsEmpty() )  Select_Str2 = " ";
            Select_Str2 = SGr1->Cells[2][ARow] ;

            if ( SGr1->Cells[3][ARow].IsEmpty() )  Select_Str3 = " ";
            Select_Str3 = SGr1->Cells[3][ARow] ;

            if ( SGr1->Cells[4][ARow].IsEmpty() )  Select_Str4 = " ";
            Select_Str4 = SGr1->Cells[4][ARow] ;

            if ( SGr1->Cells[5][ARow].IsEmpty() )  Select_Str5 = " ";
            else Select_Str5 = SGr1->Cells[5][ARow] ;
            break;
        //case 3:
        //    // �ŏ����R�[�h���ް���ϐ��֕ۑ�
        //    Select_Str1 = SGr1->Cells[1][ARow] ;
        //    if ( Select_Str1 == NULL )  Select_Str1 = " ";
        //    break;
        }
    Select_Cnt = ARow;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_RETURN:
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
    }
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

//�������@����
//2002/11/18 E.Takase ����ҕ\��
//---------------------------------------------------------------------------
int KENSA_YMD_Serch01(int flag)
{
	AnsiString str;
	int i = 1;

	//KM01���猟�����𒊏o
	Form2->Query1->Close();
	Form2->Query1->SQL->Clear();

	//�����\����A�g���[No
	//sBuf = "SELECT DISTINCT KENSA_YMD, DTKSHIN,ZISNAM ,ZISCOD, LOTNO";
	//sBuf += " FROM KDB1";
	//sBuf += " ORDER BY KENSA_YMD DESC,DTKSHIN, ZISCOD";
	sBuf = "SELECT KENSA_YMD, DTKSHIN, ZISNAM, HINBAN, LOTNO, Min(UPDCHR) As UPDCHR, ZISCOD";
	sBuf += " FROM KDB1";
        sBuf += " WHERE KOJOKBN = " + IntToStr(iKojoKbn);  //20160701_�H��敪�ǉ�
	sBuf += " GROUP BY KENSA_YMD, DTKSHIN, ZISNAM, HINBAN, LOTNO, ZISCOD";
	sBuf += " ORDER BY KENSA_YMD DESC,DTKSHIN, ZISCOD";


	//�₢���������s

	Form2->Query1->SQL->Add(sBuf);
	Form2->Query1->Open();
	Form2->Query1->Active = true;

	int iRow = 0 ;
	sBuf = "NO.";
	Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
	Form2->SGr1->Cells[1][iRow] = "�����";
	Form2->SGr1->Cells[2][iRow] = "���Ӑ�i��";
	Form2->SGr1->Cells[3][iRow] = "�ގ�����";
	Form2->SGr1->Cells[4][iRow] = "���b�gNO";
	Form2->SGr1->Cells[5][iRow] = "�����";

    iRow += 1;

    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true) {
		Form2->SGr1->Cells[1][1]=" " ;
		Form2->SGr1->Cells[2][1]=" " ;
		Form2->SGr1->Cells[3][1]=" " ;
		Form2->SGr1->Cells[4][1]=" " ;
		Form2->SGr1->Cells[5][1]=" " ;
		Form2->SGr1->Cells[6][1]=" " ; //2003/01/06 E.Takase

		ShowMessage( MSG_02 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

			// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
			if( iRow >= Form2->SGr1->RowCount ){
			    Form2->SGr1->RowCount = iRow+1;
			}
			sBuf = iRow ;
			Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

			sBuf = Form2->Query1->FieldValues["KENSA_YMD"];
			Form2->SGr1->Cells[1][iRow] = Form1->InsSEPA(sBuf);;
			sBuf = Form2->Query1->FieldValues["DTKSHIN"];
			Form2->SGr1->Cells[2][iRow] = sBuf;
			sBuf = Form2->Query1->FieldValues["ZISNAM"];
			Form2->SGr1->Cells[3][iRow] = sBuf;
			sBuf = Form2->Query1->FieldValues["LOTNO"];
			Form2->SGr1->Cells[4][iRow] = sBuf;

            //2003/01/06 E.Takase
			sBuf = Form2->Query1->FieldValues["ZISCOD"];
			Form2->SGr1->Cells[6][iRow] = sBuf;

			sBuf = Form2->Query1->FieldValues["UPDCHR"];
			Form2->SGr1->Cells[5][iRow] = Form2->GetTANNAM(sBuf);
            iRow += 1;
            Form2->Query1->Next();
      }
   }

   Form2->SGr1->RowCount = iRow;

   return (iRow) ;

 }

//KM02�����\���Ӑ�i�Ԃ𒊏o
int DTKSHIN_Serch01(int flag)
{
	AnsiString str;
	int i = 1;

	//KM02�����\���Ӑ�i�Ԃ𒊏o
	Form2->Query1->Close();
	Form2->Query1->SQL->Clear();

	//�����\����A�g���[No
	sBuf = "SELECT DISTINCT DTKSHIN,ZISNAM ,ZISCOD  FROM KM02";
	sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
    //2002/11/22 REVCNT = 0 �����ǉ� E.Takase
	sBuf += " AND REVCNT = 0 ";
	sBuf += " ORDER BY DTKSHIN, ZISCOD";


	//�₢���������s

	Form2->Query1->SQL->Add(sBuf);
	Form2->Query1->Open();
	Form2->Query1->Active = true;

	int iRow = 0 ;
	sBuf = "NO.";
	Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
	Form2->SGr1->Cells[1][iRow] = "���Ӑ�i��";
	Form2->SGr1->Cells[2][iRow] = "�ގ�����";
	Form2->SGr1->Cells[3][iRow] = " ";
	Form2->SGr1->Cells[4][iRow] = " ";

    iRow += 1;

    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true) {
		Form2->SGr1->Cells[1][1]=" " ;
		Form2->SGr1->Cells[2][1]=" " ;
		Form2->SGr1->Cells[3][1]=" " ;
		Form2->SGr1->Cells[4][1]=" " ;
		Form2->SGr1->Cells[5][1]=" " ;

		ShowMessage( MSG_02 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

			// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
			if( iRow >= Form2->SGr1->RowCount ){
			    Form2->SGr1->RowCount = iRow+1;
			}
			sBuf = iRow ;
			Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

			sBuf = Form2->Query1->FieldValues["DTKSHIN"];
			Form2->SGr1->Cells[1][iRow] = sBuf;
			sBuf = Form2->Query1->FieldValues["ZISNAM"];
			Form2->SGr1->Cells[2][iRow] = sBuf;
			sBuf = Form2->Query1->FieldValues["ZISCOD"];
			Form2->SGr1->Cells[4][iRow] = sBuf;

			Form2->SGr1->Cells[3][iRow] = " ";
			Form2->SGr1->Cells[5][iRow] = " ";
            iRow += 1;
            Form2->Query1->Next();
      }
   }

   Form2->SGr1->RowCount = iRow;

   return (iRow) ;

 }

//KDB1�����\���Ӑ�i�Ԃ𒊏o
//2002/11/18 E.Takase ����ҕ\��
int DTKSHIN_Serch02(int flag)
{
	AnsiString str;
	int i = 1;

	//KDB1�����\���Ӑ�i�Ԃ𒊏o
	Form2->Query1->Close();
	Form2->Query1->SQL->Clear();

	//�����\����A�g���[No
	//sBuf = "SELECT DISTINCT DTKSHIN,ZISNAM ,ZISCOD,LOTNO FROM KDB1";
	//sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
	//sBuf += " AND KENSA_YMD = '" + Form1->DelSEPA(Form1->EdtYMD->Text) + "'";
	//sBuf += " ORDER BY DTKSHIN, ZISCOD";
    //2002/11/18 ����҂��擾���� E.Takase
	sBuf = "SELECT DTKSHIN, ZISNAM, HINBAN, LOTNO, Min(UPDCHR) As UPDCHR, ZISCOD";
	sBuf += " FROM KDB1";
	sBuf += " WHERE DTKSHIN LIKE '" + Form1->EdtHIN->Text + "%'";
	sBuf += " AND KENSA_YMD = '" + Form1->DelSEPA(Form1->EdtYMD->Text) + "'";
        sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�
	sBuf += " GROUP BY DTKSHIN, ZISNAM, HINBAN, LOTNO, ZISCOD";
	sBuf += " ORDER BY DTKSHIN, ZISCOD";


	//�₢���������s

	Form2->Query1->SQL->Add(sBuf);
	Form2->Query1->Open();
	Form2->Query1->Active = true;

	int iRow = 0 ;
	sBuf = "NO.";
	Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;
	Form2->SGr1->Cells[1][iRow] = "���Ӑ�i��";
	Form2->SGr1->Cells[2][iRow] = "�ގ�����";
	Form2->SGr1->Cells[3][iRow] = "�����";
	Form2->SGr1->Cells[4][iRow] = "���b�gNO";

    iRow += 1;

    if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true) {
		Form2->SGr1->Cells[1][1]=" " ;
		Form2->SGr1->Cells[2][1]=" " ;
		Form2->SGr1->Cells[3][1]=" " ;
		Form2->SGr1->Cells[4][1]=" " ;
		Form2->SGr1->Cells[5][1]=" " ;

		ShowMessage( MSG_02 );
      return 0;
    }else {
      Form2->Query1->First();
      while( !Form2->Query1->Eof ) {

			// �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
			if( iRow >= Form2->SGr1->RowCount ){
			    Form2->SGr1->RowCount = iRow+1;
			}
			sBuf = iRow ;
			Form2->SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;

			sBuf = Form2->Query1->FieldValues["DTKSHIN"];
			Form2->SGr1->Cells[1][iRow] = sBuf;

			sBuf = Form2->Query1->FieldValues["ZISNAM"];
			Form2->SGr1->Cells[2][iRow] = sBuf;

			sBuf = Form2->Query1->FieldValues["ZISCOD"];
			Form2->SGr1->Cells[5][iRow] = sBuf;

			sBuf = Form2->Query1->FieldValues["LOTNO"];
			Form2->SGr1->Cells[4][iRow] = sBuf;

			sBuf = Form2->Query1->FieldValues["UPDCHR"];
			Form2->SGr1->Cells[3][iRow] = Form2->GetTANNAM(sBuf);

            iRow += 1;
            Form2->Query1->Next();
      }
   }

   Form2->SGr1->RowCount = iRow;

   return (iRow) ;

 }

//2001.02.26 �f�[�^�폜�{�^���ǉ�
//�I�����ꂽ�f�[�^�iKDB1,KDB2�j�̍폜
void __fastcall TForm2::BtnF10Click(TObject *Sender)
{

	//�������[�h1�̂Ƃ��̂ݗL��
    switch(KENSAKU_Mode)
    {
        case 1:
            //
        	switch( MessageDlg( "�I�������f�[�^���폜���܂����H",
                           mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) ){
            	// �uYes�v      �ۑ�
            	case mrYes:

                	break;
            	// �uNo�v       �ύX��j��
            	case mrNo:
                	return;
                	break;
        	}


     		if ( DelData_Form2() ) {
            //����
            	Form2->Activate();
                //// �f�[�^��ύX�����t���O
			    //DataSave = true;
                if( Form1->Database1->InTransaction == True ){
                    Form1->Database1->Commit();
                    // �V�����g�����U�N�V�������J�n
                    Form1->Database1->StartTransaction();
                }

                // �f�[�^��ύX�����t���O
                DataSave = false;

            } else {
            //���s
            	return;
            }


            break;
        default:
      		return;
            break;
    }

}
//---------------------------------------------------------------------------
// �f�[�^���폜���܂��B
bool __fastcall TForm2::DelData_Form2()
{
    AnsiString sBuf;
    AnsiString sWhere1;
    AnsiString sWhere2;
    AnsiString sWhere3;

    int CopyCnt;
    int sPos;
    int ePos;
    int i;

    sPos = SGr1->Selection.Top;
    ePos = SGr1->Selection.Bottom;
    CopyCnt = SGr1->Selection.Bottom - SGr1->Selection.Top + 1;

	for ( i = sPos; i <= ePos; i++ ) {
	    //�����
	    if (  SGr1->Cells[1][i].IsEmpty() )  sWhere1 = " ";
	    sWhere1 = SGr1->Cells[1][i] ;

	    //DTKSHIN
	    if (  SGr1->Cells[2][i].IsEmpty() )  sWhere2 = " ";
	    sWhere2 = SGr1->Cells[2][i] ;

	    //LOTNO
	    if (  SGr1->Cells[4][i].IsEmpty() )  sWhere3 = " ";
	    sWhere3 = SGr1->Cells[4][i] ;


	     // Initial Query
	     Form1->Query1->Close();
	     Form1->Query1->SQL->Clear();


	     // �⍇�����쐬
	     sBuf = "select KENSA_YMD from KDB1 ";
	     sBuf +=" where KENSA_YMD='" + Form1->DelSEPA( sWhere1 ) + "'";  // �����
	     sBuf +=" AND DTKSHIN='" + sWhere2 + "'";        // DTKSHIN
	     sBuf +=" AND LOTNO='" + sWhere3 + "'";            // LOTNO
             sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�

	     Form1->Query1->SQL->Add(sBuf);

	     // �₢�������̎��s
	     try
	     {
	        Form1->Query1->Open();
	        Form1->Query1->Active = true;

	        if( Form1->Query1->Eof == True &&  Form1->Query1->Bof == True ){
	            ShowMessage( "�Y���̃f�[�^��������܂���B�폜�ł��܂���ł����B");
	            return(False);
	        }
	     }
	     catch(EDatabaseError& e)
	     {
	         ShowMessage( e.Message );
	         return(False);
	     }
	     catch(Exception& e)
	     {
	         ShowMessage(  e.Message );
	         return(False);
	     }



	     // Initial Query
	     Form1->Query1->Close();
	     Form1->Query1->SQL->Clear();

	     // �⍇�����쐬
	     sBuf = "delete from KDB1 ";
	     sBuf +=" where KENSA_YMD='" + Form1->DelSEPA( sWhere1 ) + "'";  	// �����
	     sBuf +=" AND DTKSHIN='" + sWhere2 + "'";      	// DTKSHIN
	     sBuf +=" AND LOTNO='" + sWhere3 + "'";      		// LOTNO
             sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�


	     Form1->Query1->SQL->Add(sBuf);

	     // �₢�������̎��s
	     try
	     {
	         Form1->Query1->ExecSQL();
	     }
	     catch(EDatabaseError& e)
	     {
	         ShowMessage( e.Message );
	         return(False);
	     }
	     catch(Exception& e)
	     {
	         ShowMessage( e.Message );
	         return(False);
	     }

	     // Initial Query
	     Form1->Query1->Close();
	     Form1->Query1->SQL->Clear();

	     // �⍇�����쐬
	     sBuf = "delete from KDB2 ";
	     sBuf +=" where KENSA_YMD='" + Form1->DelSEPA( sWhere1 ) + "'";  	// �����
	     sBuf +=" AND DTKSHIN='" + sWhere2 + "'";      	// DTKSHIN
	     sBuf +=" AND LOTNO='" + sWhere3 + "'";      		// LOTNO
             sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�


	     Form1->Query1->SQL->Add(sBuf);

	     // �₢�������̎��s
	     try
	     {
	         Form1->Query1->ExecSQL();
	     }
	     catch(EDatabaseError& e)
	     {
	         ShowMessage( e.Message );
	         return(False);
	     }
	     catch(Exception& e)
	     {
	         ShowMessage( e.Message );
	         return(False);
	     }
	}

     return(True);

}
//---------------------------------------------------------------------------
//2002/11/14 E.Takase
//�S���҃R�[�h����S���Җ�����������
AnsiString __fastcall TForm2::GetTANNAM(AnsiString strTANSYA)
{

    AnsiString sBuf;

    // Initial Query
    Form2->Query2->Close();
    Form2->Query2->SQL->Clear();

    // �⍇�����쐬
	sBuf = "SELECT TANNAM FROM SM12S";
	sBuf += " WHERE TANSYA=" + strTANSYA;

    Form2->Query2->SQL->Add(sBuf);
	Form2->Query2->Open();
	Form2->Query2->Active = true;

	if ( Form2->Query2->Bof == true && Form2->Query2->Eof == true) {
		return strTANSYA;
		//return " ";
	} else {
		Form2->Query2->First();
		sBuf = Form2->Query2->FieldValues["TANNAM"];
        return sBuf;
	}


}
//---------------------------------------------------------------------------




