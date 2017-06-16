/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 2000.01.06                                          *
*  update        : 2002.02.26(���������ǉ��F������)                    *
*  contents      : ���C���v���O����                                    *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <stdio.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int KENSAKU_Mode;           //�ꗗ�������[�h
int     USER_COD;           //�S���҃R�[�h
String  USER_NAM;           //�S���Җ�
String  BUMO_COD;           //�����R�[�h
String  BUMO_NAM;           //������

KD_DATA KD;
CAL_DATA CALD;

int intKEIJKBN; //�`��敪 //2002/12/07 E.Takase

int iKojoKbn = 0;                   // �H��敪

// ���b�Z�[�W
AnsiString MSG_00 = "�@��ԍ��iPC1�`PC4)���`���ĉ�����";
AnsiString MSG_01 = "�������ł�... ���΂炭���҂����������B" ;
AnsiString MSG_02 = "�������ʂO���B" ;
AnsiString MSG_03 = "�������ʂO���B" ;
AnsiString MSG_04 = "�X�V���ł�... ���΂炭���҂����������B" ;
AnsiString MSG_05 = "�W�v���ł�... ���΂炭���҂����������B" ;
AnsiString MSG_06 = "�X�V���ł�... ���΂炭���҂����������B" ;
AnsiString MSG_07 = "Ch  �ݒ�" ;
AnsiString MSG_08 = "�f�[�^���^���x(1/100)�ݒ�B" ;
AnsiString MSG_09 = "��ʈ�����ł�... ���΂炭���҂����������B" ;
AnsiString MSG_10 = "�f�[�^��ۑ����܂����H�B" ;
AnsiString MSG_11 = "RS232C�ڑ��G���[���������܂����B" ;
AnsiString MSG_12 = "���萔�����炵�܂��B��낵���ł����H";


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
//�t�H�[���쐬��
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Database1->Open();

    // �{�^���̏�����
    BtnF01->Enabled = true;
    BtnF02->Enabled = false;
    BtnF03->Enabled = false;
    BtnF04->Enabled = false;
    BtnF05->Enabled = true;
    BtnF06->Enabled = true;
    BtnF07->Enabled = false;
    BtnF08->Enabled = false;
    BtnF09->Enabled = false;
    BtnF10->Enabled = false;
    BtnF11->Enabled = false;
    BtnF12->Enabled = true;

    //USER_COD = 1;
    KENSAKU_Mode = 1;

    //����A�S����
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    //CheckBox1
    CheckBox1->Caption = "���[�h������";
	CheckBox2->Caption = "�u���V��";
	CheckBox3->Caption = "�u���V��(�c����)";
	CheckBox4->Caption = "���[�h����t��R";
	CheckBox5->Caption = "���[�h����t���x";
	CheckBox6->Caption = "���|��d";
	CheckBox7->Caption = "�d�x(HsC ����)";
	CheckBox8->Caption = "�d�x(HsC ����)";
	CheckBox9->Caption = "�d�x(HsD ����)";
	CheckBox10->Caption = "�d�x(HsD ����)";
	CheckBox11->Caption = "��R��";
	CheckBox12->Caption = "�Ȃ�����";
	CheckBox13->Caption = "����";
	CheckBox14->Caption = "�Ȃ�����(����)";

    //���W�I�{�^��
    RadioKANSA->Checked = true;
    RadioLOT->Checked   = false;

    // 20160630_ini�t�@�C���ǂݍ��ݒǉ�
    Read_Ini();

    //20160704�ǉ�
    if ( iKojoKbn == 0 ) {
       RadioHON->Checked = true;
       RadioKOU->Checked = false;
       RadioRYO->Checked = false;
    } else if ( iKojoKbn == 1 ) {
       RadioHON->Checked = false;
       RadioKOU->Checked = true;
       RadioRYO->Checked = false;
    } else {
       RadioHON->Checked = false;
       RadioKOU->Checked = false;
       RadioRYO->Checked = true;
    }

}

//---------------------------------------------------------------------------
//�u�e�P�F�ꗗ�����v
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
     if ( !BtnF01->Enabled ) return;
     Form2->ShowModal();
}

//-------------------------------------------------------------------------
//�u�e�T�F��ʈ���v
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{
    if( !BtnF05->Enabled )    return;
     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = MSG_09;
     SBr1->Update();

     Form1->Print();

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

}

//---------------------------------------------------------------------------
//�u�e�U�F����v
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
//    if ( Search_MAIN() > 0 ) {
//    	if ( Write_CSVMain() ) {
//        	ShowMessage("����I");
//       } else {
//        	ShowMessage("CSV�o�͎��s");
//        }
//
//    } else {
//    	ShowMessage("�������� 0��");
//    }

	AnsiString sBuf;

    //�w�肳�ꂽ���Ӑ�i�Ԃ̌`�������
	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

    sBuf = "SELECT KEIJKBN  FROM KM02 ";
	sBuf += " where DTKSHIN = '" + EdtTKSHIN->Text + "'";
	sBuf += " and REVCNT = 0";
	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof ) {
		//�������� �O��
        ShowMessage("�������� 0���ł�");
		return;
	}
	intKEIJKBN = Form1->Query1->FieldValues["KEIJKBN"];



    //�w�肳�ꂽ���荀�ڂ����
	switch(Write_CSVMain())
	{
    	case 0:
        	ShowMessage("�������� 0���ł�");
            break;

    	case -1:
        	ShowMessage("CSV�o�� ���s���܂���");
            break;

    	case 1:

            if (!(Excel_Write() )) ShowMessage("Excel�̋N���Ɏ��s���܂���");
            break;

        default:
        	ShowMessage("�f�[�^�쐬 ���s���܂���");
            break;

	}

}

//�u�e�P�Q�F�I���v
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();

}
//�uFormKey�_�E���v
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
         case VK_F1:  BtnF01Click(Sender);    break;
//         case VK_F2:  BtnF02Click(Sender);    break;
//         case VK_F3:  BtnF03Click(Sender);    break;
//         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
//         case VK_F7:  BtnF07Click(Sender);    break;
//         case VK_F8:  BtnF08Click(Sender);    break;
//         case VK_F9:  BtnF09Click(Sender);    break;
//         case VK_F10: BtnF10Click(Sender);    break;
//         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;


         // �O��
         case VK_UP:
         case VK_LEFT:
                //���Ӑ�i��
                if(EdtTKSHIN->Focused() && EdtTKSHIN->SelStart == 0 && EdtTKSHIN->SelLength == 0 ){
                    EdtEYMD->SetFocus();
                    break;
                }
                //�J�n���b�g
                if(EdtSLOT->Focused() && EdtSLOT->SelStart == 0 && EdtSLOT->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                //�I�����b�g
                if(EdtELOT->Focused() && EdtELOT->SelStart == 0 && EdtELOT->SelLength == 0 ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //2001.02.26�ǉ�
                //�J�n��
                if(EdtSYMD->Focused() && EdtSYMD->SelStart == 0 && EdtSYMD->SelLength == 0 ){
                    EdtELOT->SetFocus();
                    break;
                }
                //�I����
                if(EdtEYMD->Focused() && EdtEYMD->SelStart == 0 && EdtEYMD->SelLength == 0 ){
                    EdtSYMD->SetFocus();
                    break;
                }

                break;

         // ����
         case VK_DOWN:
         case VK_RIGHT:
                //���Ӑ�i��
                if(EdtTKSHIN->Focused() && EdtTKSHIN->SelStart == EdtTKSHIN->Text.Length() && EdtTKSHIN->SelLength == 0 ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //�J�n���b�g
                if(EdtSLOT->Focused() && EdtSLOT->SelStart == EdtSLOT->Text.Length() && EdtSLOT->SelLength == 0 ){
                    EdtELOT->SetFocus();
                    break;
                }
                //�I�����b�g
                if(EdtELOT->Focused() && EdtELOT->SelStart == EdtELOT->Text.Length() && EdtELOT->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                //2001.02.26�ǉ�
                //�J�n��
                if(EdtSYMD->Focused() && EdtSYMD->SelStart == EdtSYMD->Text.Length() && EdtSYMD->SelLength == 0 ){
                    EdtEYMD->SetFocus();
                    break;
                }
                //�I����
                if(EdtEYMD->Focused() && EdtEYMD->SelStart == EdtEYMD->Text.Length() && EdtEYMD->SelLength == 0 ){
                    EdtTKSHIN->SetFocus();
                    break;
                }

                break;

         // Enter
         case VK_RETURN:
                //���Ӑ�i��
                if(EdtTKSHIN->Focused() ){
                    EdtSLOT->SetFocus();
                    break;
                }
                //�J�n���b�g
                if(EdtSLOT->Focused()){
                    EdtELOT->SetFocus();
                    break;
                }
                //�I�����b�g
                if(EdtELOT->Focused()){
                    EdtSYMD->SetFocus();
                    break;
                }
                //2001.02.26�ǉ�
                //�J�n��
                if(EdtSYMD->Focused()){
                    EdtEYMD->SetFocus();
                    break;
                }
                //�I����
                if(EdtEYMD->Focused()){
                    EdtTKSHIN->SetFocus();
                    break;
                }
                break;

     }
}

//---------------------------------------------------------------------------
//�u�t�H�[�J�X�擾���v
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtTKSHIN->Focused() ){
        KENSAKU_Mode = 2;
        BtnF01->Enabled = true;
        return;
    }
    if(EdtSLOT->Focused() ){
        KENSAKU_Mode = 3;
        BtnF01->Enabled = true;
        return;
    }
    if(EdtELOT->Focused() ){
        KENSAKU_Mode = 4;
        BtnF01->Enabled = true;
        return;
    }

    KENSAKU_Mode = -1;
    BtnF01->Enabled = false;

}

//---------------------------------------------------------------------------
//�����_�ȉ�
AnsiString __fastcall TForm1::ConvKETA1(int keta,double n)
{
    int x;
    double m;
    AnsiString str;

    //�����_�ȉ� keta��
    x = pow(10,keta);
    m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

    str = "#0." + AnsiString::StringOfChar('0', keta );

    return( str );
}
//---------------------------------------------------------------------------
//�L������
AnsiString __fastcall TForm1::ConvKETA2(int keta,double n)
{
    int i,x;
    double m;
    AnsiString str;
    AnsiString tmp_s1,tmp_s2;
    int tmp_n1,tmp_n2;
    AnsiString Formatstr;
    char test[256];
    AnsiString test2;
    int flag,pos;
    int flag_M;

    //�L������
    if ( n < 0 ) {
        //�}�C�i�X
        flag_M = -1;
        n = n * -1;
    } else {
        flag_M = 1;
    }

    if ( n >= 1 ) {
        //1�ȏ�
        flag = 1;
    } else {
        //0�ȏ�1����
        flag = 2;
    }

    switch( flag ){
        case 1:
            str = FormatFloat("#0.0#", n );
            pos = str.AnsiPos(".") - 1;
            if ( pos <  keta ) {
                Formatstr = "#0." + AnsiString::StringOfChar('0', keta-pos );
            } else {
                if ( pos == keta ) {
                    Formatstr = "#0";
                } else {
                //keta = 2, n = 1234.5 �� 1200
                    Formatstr = "#0";
                    tmp_s1 = FloatToStr((int(n)));
                    tmp_n1 = tmp_s1.Length();
                    tmp_n2 = pow(10,(tmp_n1-keta));

                }
            }
            break;

        case 2:
            x = pow(10,keta);
            m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

            if ( n == 0 ) {
            	Formatstr = "#0."+ AnsiString::StringOfChar('0', (keta - 1));
            } else {
            	i = 1;
            	while(1) {
            		if ( int(n*( pow(10,i))) > 0 ) {
                		break;
                	} else {
                		i++;
                	}
            	}
            	Formatstr = "#0." + AnsiString::StringOfChar('0', (i - 1 + keta));
			}
            break;
    }
    return ( Formatstr );
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

    //����A�S����
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;


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

void __fastcall TForm1::EdtKeyPress(TObject *Sender, char &Key)
{
    //�r�[�v���Ȃ炳�Ȃ��悤�ɂ���
    switch(Key){
        // ���^�[��
        case VK_RETURN:
            Key = 0;
            break;
    }
    
}
//---------------------------------------------------------------------------
//INI�t�@�C�� �ǂݍ��� �H��敪�擾
void __fastcall TForm1::Read_Ini()
{
     int getlen1;
     char windir[MAX_PATH];	//Windows Dir
     char CurDir[MAX_PATH];	//Current Dir
     char tempo[MAX_PATH];

     //�ݒ�t�@�C���@( "windows\TKSMAIN.ini" or "winnt\TKSMAIN.ini" )
     char INIname[MAX_PATH];

     // �@��ԍ���Ǎ���
     GetCurrentDirectory(256,CurDir);
     sprintf(INIname, "%s\\Tks.ini", CurDir);
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);
     iKojoKbn = atoi(tempo);
     
}



//---------------------------------------------------------------------------


