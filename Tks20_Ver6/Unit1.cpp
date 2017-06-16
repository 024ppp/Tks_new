/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 1999.10.12                                          *
*  update        :                                                     *
*  contents      : ���C���v���O����                                    *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//�ϐ��̐錾
structUPDCHR DTKSData; //�e���Ӑ斈�̌�������
int UPDCHRNo;

structKD01 KD01Data;		  //���[�h������ KD01
structKD11 KD11Data;		  //�u���V�����@  KD11
structKD21 KD21Data;		  //�u���V�����@�c����  KD21
structKD31 KD31Data;		  //���[�h����t��R  KD31
structKD41 KD41Data;		  //���[�h���������x  KD41
structKD51 KD51Data; 		  //��̔�d KD51
structKD61 KD61Data;		  //�g���d�x  KD61
structKD71 KD71Data;		  //�ŗL��R��  KD71
structKD81 KD81Data;	  	  //�R�ܗ�  KD81
structKD91 KD91Data;	  	  //����  KD91
structKM01_04 KM01_04Data;    //�����}�X�^�f�[�^ KM01_04

//2002/12/06�@E.Takase
structKDC1 KDC1Data;	  	  //�����R�ܗ�    KDC1
structKD71_L KD71Data_L;	  //�ŗL��R�� �� KD71
structKD71_R KD71Data_R;	  //�ŗL��R�� �E KD71


int KENSAKU_Mode;               //�ꗗ�������[�h
                                //1 ������
                                //2 ���Ӑ�i��
                                //3 �J�n���b�gNo
                                //4 �I�����b�gNo

int DataNo;    //�ő匟���f�[�^����
int Master_rec;//�}�X�^������s
int rec;       //���R�[�h��
int pass;      //���i1�A�s���i0
int newpage;   //���y�[�WNo
AnsiString Last_DTKSCOD;
AnsiString strcnd;
AnsiString strcnd2;
AnsiString UPDCHRstr;
AnsiString UPDCHRstr02;
AnsiString DTKSHINcnd;   //���Ӑ�i��
AnsiString StartLOTcnd;  //�J�n���b�gNo
AnsiString EndLOTcnd;    //�I�����b�gNo
AnsiString DTKSCODcnd;   //���Ӑ�R�[�h
int Flagcnd;             //0����������  1�����Ӑ�i�ԕ�
                         //2���R���~��������  3���R���~���Ӑ�i�ԕ�
AnsiString KIKAKUMINstr;
AnsiString KIKAKUMAXstr;

int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;

int iKojoKbn = 0;                   // �H��敪


//�֐��̐錾
void UPDCHRInsert01(void);
void UPDCHR_Serch01(void);  //2002/12/06 E.Takase �R���~�p
void UPDCHR_2_Serch01(void);
AnsiString Kara(int i);
double DivAB(double a, double b);
AnsiString SOKUTEIstrI(int i, int n, int val);
AnsiString SOKUTEIstrF(int i, int n, double val, int k);
void PassSet(void);
void DataNoSet(void);
void MakeData(void);
AnsiString varstr(Variant str);
int varint(Variant str);
//AnsiString varstr(AnsiString str);
//int varint(AnsiString str);
double vardouble(Variant str);
void KM01_04Serch01(void);
void DTKSHIN_CIYCLEInsert01(void);
void KIKAKU_MINInsert01(void);
void KIKAKU_MINInsert02(void);          //2002/12/06 E.Takase �R���~�p
void KIKAKU_MAXInsert01(void);
void PASS_FailUpdate01(void);
void KM01_04Sub01(void);
void SOKUTEIInsert01(void);
void SOKUTEIInsert02(void);             //2002/12/06 E.Takase �R���~�p
void LOT_SOKUTEIInsert01(void);

void KD01_02Serch01(void);
void KD01Compare01(void);
void KD01Format01(void);

void KD11_12Serch01(void);
void KD11Compare01(void);
void KD11Format01(void);

void KD21_22Serch01(void);
void KD21Compare01(void);
void KD21Format01(void);

void KD31_32Serch01(void);
void KD31Compare01(void);
void KD31Format01(void);

void KD41_42Serch01(void);
void KD41Compare01(void);
void KD41Format01(void);

void KD51_52Serch01(void);
void KD51Compare01(void);
void KD51Format01(void);

void KD61_62Serch01(void);
void KD61Compare01(void);
void KD61Format01(void);

void KD71_72Serch01(void);
void KD71Compare01(void);
void KD71Format01(void);

void KD81_82Serch01(void);
void KD81Compare01(void);
void KD81Format01(void);

void KD91_92Serch01(void);
void KD91Compare01(void);
void KD91Format01(void);

//2002/12/05 E.Takase
void KDC1_C2Serch01(void);
void KDC1Compare01(void);
void KDC1Format01(void);

void KD71_72_LSerch01(void);
void KD71_LCompare01(void);
void KD71_LFormat01(void);

void KD71_72_RSerch01(void);
void KD71_RCompare01(void);
void KD71_RFormat01(void);


//���Ӑ�ʂɌ�����������
void UPDCHR_Make01(int CurNo);
void UPDCHR_2_Make01(int CurNo);  //2002/12/06 E.Takase �R���~�p
//�u������=�E�E�E�E�v������쐬
void UPDCHR_Make02(void);         
void UPDCHR_2_Make02(void);       //2002/12/06 E.Takase �R���~�p
//TW_UPDCHR �� �ǉ�
void UPDCHRInsert02(void);


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::FormCreate(TObject *Sender)                 *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �t�H�[���쐬��                                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Database1->Open();
    Database2->Open();
    KENSAKU_Mode = 1;
    // �����\����̏�����
    Edt_KENYMD->Text = FormatDateTime("yyyy/mm/dd",Date());
    //Edt_StartSOKU->Text = FormatDateTime("yyyy/mm",Date());
    Edt_StartSOKU->Text = "1999/12";
    Edt_EndSOKU->Text = FormatDateTime("yyyy/mm",Date());

    // ini�t�@�C���ǂݍ��ݒǉ�
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

/***********************************************************************
*  function name : TForm1::BtnF01Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �ꗗ����                                            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
     Form2->ShowModal();

}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::RadioButton1Click(TObject *Sender)          *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ʂ�I�������Ƃ�                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
     Panel_KENYMD->Color = 0x00FEE7BA;
     Panel_KENYMD->Font->Color = clWindowText;
     Edt_KENYMD->Enabled = True;
     Panel_DTKSCOD->Color = 0x00FEE7BA;
     Panel_DTKSCOD->Font->Color = clWindowText;
     Edt_DTKSCOD->Enabled = True;

     Panel_DTKSHIN->Color = clSilver;
     Panel_DTKSHIN->Font->Color = clGray;
     Edt_DTKSHIN->Enabled = False;
     Panel_LOT->Color = clSilver;
     Panel_LOT->Font->Color = clGray;
     Edt_StartLOT->Enabled = False;
     Edt_EndLOT->Enabled = False;
     Panel_SOKU->Color = clSilver;
     Panel_SOKU->Font->Color = clGray;
     Edt_StartSOKU->Enabled = False;
     Edt_EndSOKU->Enabled = False;

     Edt_KENYMD->SetFocus();
     KENSAKU_Mode = 1;

}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::RadioButton2Click(TObject *Sender)          *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �i�ԁE���b�g�ʂ�I�������Ƃ�                        *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
     Panel_KENYMD->Color = clSilver;
     Panel_KENYMD->Font->Color = clGray;
     Edt_KENYMD->Enabled = False;
     Panel_DTKSCOD->Color = clSilver;
     Panel_DTKSCOD->Font->Color = clGray;
     Edt_DTKSCOD->Enabled = False;

     Panel_DTKSHIN->Color = 0x00FEE7BA;
     Panel_DTKSHIN->Font->Color = clWindowText;
     Edt_DTKSHIN->Enabled = True;
     Panel_LOT->Color = 0x00FEE7BA;
     Panel_LOT->Font->Color = clWindowText;
     Edt_StartLOT->Enabled = True;
     Edt_EndLOT->Enabled = True;
     Panel_SOKU->Color = 0x00FEE7BA;
     Panel_SOKU->Font->Color = clWindowText;
     Edt_StartSOKU->Enabled = True;
     Edt_EndSOKU->Enabled = True;

     Edt_DTKSHIN->SetFocus();
     KENSAKU_Mode = 2;

}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::BtnF06Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ����{�^�����������Ƃ��i����j                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    AnsiString sBuf;

    if ( RadioButton1->Checked == true ) {
        Flagcnd = 0;
        strcnd = DelSEPA(Form1->Edt_KENYMD->Text);
        DTKSCODcnd = Trim(Form1->Edt_DTKSCOD->Text);
        DTKSHINcnd = "";
        StartLOTcnd = "";
        EndLOTcnd = "";
/*
        //���Ӑ�R�[�h����
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
            return;
        }
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
        }
        else {
	        //SM16S����TRSCOD�𒊏o
	        Form2->Query1->Close();
	        Form2->Query1->SQL->Clear();

	        //�₢���������s
	        //�����\����A�g���[No
	        sBuf = "SELECT ";
	        sBuf += "DISTINCT TRSCOD, TRSNAM ";
	        sBuf += "FROM SM16S ";
	        sBuf += " WHERE  TRSCOD = '" + Edt_DTKSCOD->Text + "'";
	        sBuf += " ORDER BY TRSCOD";
	        Form2->Query1->SQL->Add(sBuf);
	        Form2->Query1->Open();
	        Form2->Query1->Active = true;

	        if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
	            Form2->Select_DTKSNAM = " ";

	        }else {
	            Form2->Query1->First();
		        if ( Form2->Query1->FieldValues["TRSNAM"].IsEmpty() ) Form2->Select_DTKSNAM = " ";
	     	    else Form2->Select_DTKSNAM = Form2->Query1->FieldValues["TRSNAM"];
	        }
        }
 */

    }
    else {
        if ( Trim(Form1->Edt_DTKSHIN->Text) == "" ) {
            SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ��w�肵�Ă��������B";
            SBr1->Update();
            Form1->Edt_DTKSHIN->SetFocus();
            return;
        }
        Flagcnd = 1;
        strcnd = DelSEPA(Form1->Edt_StartSOKU->Text) + "01";
        strcnd2 = DelSEPA(Form1->Edt_EndSOKU->Text) + "99";
        DTKSHINcnd = Form1->Edt_DTKSHIN->Text;
        StartLOTcnd = Form1->Edt_StartLOT->Text;
        EndLOTcnd = Form1->Edt_EndLOT->Text;
        DTKSCODcnd = "";
    }

    //strcnd = "19991008";     //���������̐ݒ�
    //DTKSHINcnd = "021660-0510";
    //StartLOTcnd = "000001";
    //EndLOTcnd = "20000";
    Form1->ProgressBar1->Position = 0;
    Form1->ProgressBar1->Visible = true;
    MakeData();
    Form1->ProgressBar1->Position = 100;

    //���|�[�g���J��
    if ( Flagcnd == 0 ) {
        Query2->Close();
        Query2->Open();
        if ( Query2->RecordCount > 0 ) {
            Form3->QuickRep1->Print();
        }
    }
    if ( Flagcnd == 1 ) {
        Query3->Close();
        Query3->Open();
        if ( Query3->RecordCount > 0 ) {
            Form4->QuickRep1->Print();
        }
    }


    Form1->ProgressBar1->Visible = false;

}
//---------------------------------------------------------------------------


/***********************************************************************
*  function name : TForm1::BtnF07Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �ƍ��{�^�����������Ƃ��i�v���r���[�j                *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
    AnsiString sBuf;

    if ( RadioButton1->Checked == true ) {
        Flagcnd = 0;
        strcnd = DelSEPA(Form1->Edt_KENYMD->Text);
        DTKSCODcnd = Trim(Form1->Edt_DTKSCOD->Text);
        DTKSHINcnd = "";
        StartLOTcnd = "";
        EndLOTcnd = "";

        //���Ӑ�R�[�h����
/*
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
        }
        else {
	        //SM16S����TRSCOD�𒊏o
	        Form2->Query1->Close();
	        Form2->Query1->SQL->Clear();

	        //�₢���������s
	        //�����\����A�g���[No
	        sBuf = "SELECT ";
	        sBuf += "DISTINCT TRSCOD, TRSNAM ";
	        sBuf += "FROM SM16S ";
	        sBuf += " WHERE  TRSCOD = '" + Edt_DTKSCOD->Text + "'";
	        sBuf += " ORDER BY TRSCOD";
	        Form2->Query1->SQL->Add(sBuf);
	        Form2->Query1->Open();
	        Form2->Query1->Active = true;

	        if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
	            Form2->Select_DTKSNAM = " ";

	        }else {
	            Form2->Query1->First();
		        if ( Form2->Query1->FieldValues["TRSNAM"].IsEmpty() ) Form2->Select_DTKSNAM = " ";
	     	    else Form2->Select_DTKSNAM = Form2->Query1->FieldValues["TRSNAM"];
	        }
        }
*/
    }
    else {
        if ( Trim(Form1->Edt_DTKSHIN->Text) == "" ) {
             SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ��w�肵�Ă��������B";
             SBr1->Update();
             Form1->Edt_DTKSHIN->SetFocus();
             return;
        }
        Flagcnd = 1;
        strcnd = DelSEPA(Form1->Edt_StartSOKU->Text) + "01";
        strcnd2 = DelSEPA(Form1->Edt_EndSOKU->Text) + "99";
        DTKSHINcnd = Form1->Edt_DTKSHIN->Text;
        StartLOTcnd = Form1->Edt_StartLOT->Text;
        EndLOTcnd = Form1->Edt_EndLOT->Text;
        DTKSCODcnd = "";
    }


    //strcnd = "19991008";     //���������̐ݒ�
    //DTKSHINcnd = "021660-0510";
    //StartLOTcnd = "000001";
    //EndLOTcnd = "20000";
    Form1->ProgressBar1->Position = 0;
    Form1->ProgressBar1->Visible = true;
    MakeData();
    Form1->ProgressBar1->Position = 100;

    //���|�[�g���J��
    if ( Flagcnd == 0 ) {
        Query2->Close();
        Query2->Open();
        if ( Query2->RecordCount > 0 ) {
           Form3->QuickRep1->Preview();
        }
    }
    if ( Flagcnd == 1 ) {
        Query3->Close();
        Query3->Open();
        if ( Query3->RecordCount > 0 ) {
            Form4->QuickRep1->Preview();
        }
     }


    Form1->ProgressBar1->Visible = false;

}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::BtnF12Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �I���{�^�����������Ƃ��i�I���j                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
    Form1->Close();
}
//---------------------------------------------------------------------------


/***********************************************************************
*  function name : TForm1::BtnF02Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �������ʂ�I��                                      *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{

    RadioButton1->Checked = true;
    RadioButton1Click(Sender);
}
//---------------------------------------------------------------------------

/***********************************************************************
*  function name : TForm1::BtnF03Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �i�ԁE���b�gNo�ʂ�I��                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    RadioButton2->Checked = true;
    RadioButton2Click(Sender);

}
//---------------------------------------------------------------------------


/***********************************************************************
*  function name : TForm1::FormKeyDown(TObject *Sender, WORD &Key,     *
*                                                 TShiftState Shift)   *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : �t�H�[���L�[�_�E�����@                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
//    KENSAKU_Mode = 1;

    SBr1->Panels->Items[0]->Text = " ";
    SBr1->Update();
    switch(Key)
     {
         case VK_F1:  BtnF01Click(Sender);    break;
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  BtnF07Click(Sender);    break;
         case VK_F9:  BtnF09Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);    break;
//         case VK_F10: BtnF10Click(Sender);    break;
//         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;
//         case VK_RETURN:
//            Form1->Edt_StartSOKU->SetFocus();
//          break;

         // �O��
         case VK_UP:
         case VK_LEFT:
                if(Edt_KENYMD->Focused() && Edt_KENYMD->SelStart == 0 && Edt_KENYMD->SelLength == 1 ){
                    KENSAKU_Mode = 7; BtnF01->Enabled = true;
                    Edt_DTKSCOD->SetFocus();
                    Key = 0;
                    break;
                }
                if(Edt_DTKSCOD->Focused() && Edt_DTKSCOD->SelStart == 0 && Edt_DTKSCOD->SelLength == 0 ){
                    KENSAKU_Mode = 1; BtnF01->Enabled = true;
                    Edt_KENYMD->SetFocus();
                    Key = 0;
                    break;
                }
                if(Edt_DTKSHIN->Focused() && Edt_DTKSHIN->SelStart == 0 && Edt_DTKSHIN->SelLength == 0 ){
                    KENSAKU_Mode = 6; BtnF01->Enabled = true;
                    Edt_EndSOKU->SetFocus();
                    break;
                }
                if(Edt_StartLOT->Focused() && Edt_StartLOT->SelStart == 0 && Edt_StartLOT->SelLength == 0 ){
                    KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    Edt_DTKSHIN->SetFocus();
                    break;
                }
                if(Edt_EndLOT->Focused() && Edt_EndLOT->SelStart == 0 && Edt_EndLOT->SelLength == 0 ){
                    KENSAKU_Mode = 3; BtnF01->Enabled = true;
                    Edt_StartLOT->SetFocus();
                    Key = 0;
                    break;
                }
                if(Edt_StartSOKU->Focused() && Edt_StartSOKU->SelStart == 0 && Edt_StartSOKU->SelLength == 1 ){
                    KENSAKU_Mode = 4; BtnF01->Enabled = true;
                    Edt_EndLOT->SetFocus();
                    Key = 0;
                    break;
                }
                if(Edt_EndSOKU->Focused() && Edt_EndSOKU->SelStart == 0 && Edt_EndSOKU->SelLength == 1 ){
                    KENSAKU_Mode = 5; BtnF01->Enabled = true;
                    Edt_StartSOKU->SetFocus();
                    Key = 0;
                    break;
                }
                break;


         // ����
         case VK_DOWN:
         case VK_RIGHT:
                if(Edt_KENYMD->Focused() && Edt_KENYMD->SelStart == Edt_KENYMD->Text.Length()  && Edt_KENYMD->SelLength == 0 ){
                    KENSAKU_Mode = 7; BtnF01->Enabled = true;
                    Edt_DTKSCOD->SetFocus();
                    break;
                }
                if(Edt_DTKSCOD->Focused() && Edt_DTKSCOD->SelStart == Edt_DTKSCOD->Text.Length()  && Edt_DTKSCOD->SelLength == 0 ){
                    KENSAKU_Mode = 1; BtnF01->Enabled = true;
                    Edt_KENYMD->SetFocus();
                    break;
                }
                if(Edt_DTKSHIN->Focused() && Edt_DTKSHIN->SelStart == Edt_DTKSHIN->Text.Length()  && Edt_DTKSHIN->SelLength == 0 ){
                    KENSAKU_Mode = 3; BtnF01->Enabled = true;
                    Edt_StartLOT->SetFocus();
                    break;
                }
                if(Edt_StartLOT->Focused() && Edt_StartLOT->SelStart == Edt_StartLOT->Text.Length()  && Edt_StartLOT->SelLength == 0 ){
                    KENSAKU_Mode = 4; BtnF01->Enabled = true;
                    Edt_EndLOT->SetFocus();
                    break;
                }
                if(Edt_EndLOT->Focused() && Edt_EndLOT->SelStart == Edt_EndLOT->Text.Length()  && Edt_EndLOT->SelLength == 0 ){
                    KENSAKU_Mode = 5; BtnF01->Enabled = true;
                    Edt_StartSOKU->SetFocus();
                    break;
                }
                if(Edt_StartSOKU->Focused() && Edt_StartSOKU->SelStart == Edt_StartSOKU->Text.Length()  && Edt_StartSOKU->SelLength == 0 ){
                    KENSAKU_Mode = 5; BtnF01->Enabled = true;
                    Edt_EndSOKU->SetFocus();
                    break;
                }
                if(Edt_EndSOKU->Focused() && Edt_EndSOKU->SelStart == Edt_EndSOKU->Text.Length()  && Edt_EndSOKU->SelLength == 0 ){
                    KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    Edt_DTKSHIN->SetFocus();
                    break;
                }
                break;

         case VK_RETURN:
         {
                if(Edt_KENYMD->Focused()){
                    KENSAKU_Mode = 7; BtnF01->Enabled = true;
                    Edt_DTKSCOD->SetFocus();
                    break;
                }
                if(Edt_DTKSCOD->Focused()){
                    KENSAKU_Mode = 1; BtnF01->Enabled = true;
                    Edt_KENYMD->SetFocus();
                    break;
                }
                if(Edt_DTKSHIN->Focused()){
                    KENSAKU_Mode = 3; BtnF01->Enabled = true;
                    Edt_StartLOT->SetFocus();
                    break;
                }
                if(Edt_StartLOT->Focused()){
                    KENSAKU_Mode = 4; BtnF01->Enabled = true;
                    Edt_EndLOT->SetFocus();
                    break;
                }
                if(Edt_EndLOT->Focused()){
                    KENSAKU_Mode = 5; BtnF01->Enabled = true;
                    Edt_StartSOKU->SetFocus();
                    break;
                }
                if(Edt_StartSOKU->Focused()){
                    KENSAKU_Mode = 5; BtnF01->Enabled = true;
                    Edt_EndSOKU->SetFocus();
                    break;
                }
                if(Edt_EndSOKU->Focused()){
                    KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    Edt_DTKSHIN->SetFocus();
                    break;
                }
                break;
        }
        break;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_KENYMDClick(TObject *Sender)
{
    KENSAKU_Mode = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_DTKSHINClick(TObject *Sender)
{
    KENSAKU_Mode = 2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_StartLOTClick(TObject *Sender)
{
    KENSAKU_Mode = 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_EndLOTClick(TObject *Sender)
{
    KENSAKU_Mode = 4;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_StartSOKUClick(TObject *Sender)
{
    KENSAKU_Mode = 5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt_EndSOKUClick(TObject *Sender)
{
    KENSAKU_Mode = 6;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt_DTKSCODClick(TObject *Sender)
{
    KENSAKU_Mode = 7;

}
//---------------------------------------------------------------------------
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
/***********************************************************************
*  function name : TForm1::BtnF05Click(TObject *Sender)                *
*  create        : 1999.10                                             *
*  update        :                                                     *
*  contents      : ��ʈ���{�^�����������Ƃ��i��ʈ���j�@            *
*  written by    : ����  �b��(NKK unics Corp.)                         *
***********************************************************************/
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{

     Form1->Print();


}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
    AnsiString sBuf;

    if ( RadioButton1->Checked == true ) {
        Flagcnd = 2;
        strcnd = DelSEPA(Form1->Edt_KENYMD->Text);
        DTKSCODcnd = Trim(Form1->Edt_DTKSCOD->Text);
        DTKSHINcnd = "";
        StartLOTcnd = "";
        EndLOTcnd = "";
/*
        //���Ӑ�R�[�h����
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
            return;
        }
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
        }
        else {
	        //SM16S����TRSCOD�𒊏o
	        Form2->Query1->Close();
	        Form2->Query1->SQL->Clear();

	        //�₢���������s
	        //�����\����A�g���[No
	        sBuf = "SELECT ";
	        sBuf += "DISTINCT TRSCOD, TRSNAM ";
	        sBuf += "FROM SM16S ";
	        sBuf += " WHERE  TRSCOD = '" + Edt_DTKSCOD->Text + "'";
	        sBuf += " ORDER BY TRSCOD";
	        Form2->Query1->SQL->Add(sBuf);
	        Form2->Query1->Open();
	        Form2->Query1->Active = true;

	        if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
	            Form2->Select_DTKSNAM = " ";

	        }else {
	            Form2->Query1->First();
		        if ( Form2->Query1->FieldValues["TRSNAM"].IsEmpty() ) Form2->Select_DTKSNAM = " ";
	     	    else Form2->Select_DTKSNAM = Form2->Query1->FieldValues["TRSNAM"];
	        }
        }
 */

    }
    else {
        if ( Trim(Form1->Edt_DTKSHIN->Text) == "" ) {
            SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ��w�肵�Ă��������B";
            SBr1->Update();
            Form1->Edt_DTKSHIN->SetFocus();
            return;
        }
        Flagcnd = 3;
        strcnd = DelSEPA(Form1->Edt_StartSOKU->Text) + "01";
        strcnd2 = DelSEPA(Form1->Edt_EndSOKU->Text) + "99";
        DTKSHINcnd = Form1->Edt_DTKSHIN->Text;
        StartLOTcnd = Form1->Edt_StartLOT->Text;
        EndLOTcnd = Form1->Edt_EndLOT->Text;
        DTKSCODcnd = "";
    }

    //strcnd = "19991008";     //���������̐ݒ�
    //DTKSHINcnd = "021660-0510";
    //StartLOTcnd = "000001";
    //EndLOTcnd = "20000";
    Form1->ProgressBar1->Position = 0;
    Form1->ProgressBar1->Visible = true;
    MakeData();
    Form1->ProgressBar1->Position = 100;

    //���|�[�g���J��
    if ( Flagcnd == 2 ) {
        Query2->Close();
        Query2->Open();
        if ( Query2->RecordCount > 0 ) {
            Form5->QuickRep1->Print();
        }
    }
    if ( Flagcnd == 3 ) {
        Query3->Close();
        Query3->Open();
        if ( Query3->RecordCount > 0 ) {
            Form6->QuickRep1->Print();
        }
    }


    Form1->ProgressBar1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
    AnsiString sBuf;

    if ( RadioButton1->Checked == true ) {
        Flagcnd = 2;
        strcnd = DelSEPA(Form1->Edt_KENYMD->Text);
        DTKSCODcnd = Trim(Form1->Edt_DTKSCOD->Text);
        DTKSHINcnd = "";
        StartLOTcnd = "";
        EndLOTcnd = "";

        //���Ӑ�R�[�h����
/*
        if ( Edt_DTKSCOD->Text == "" ) {
            Form2->Select_DTKSNAM = " ";
        }
        else {
	        //SM16S����TRSCOD�𒊏o
	        Form2->Query1->Close();
	        Form2->Query1->SQL->Clear();

	        //�₢���������s
	        //�����\����A�g���[No
	        sBuf = "SELECT ";
	        sBuf += "DISTINCT TRSCOD, TRSNAM ";
	        sBuf += "FROM SM16S ";
	        sBuf += " WHERE  TRSCOD = '" + Edt_DTKSCOD->Text + "'";
	        sBuf += " ORDER BY TRSCOD";
	        Form2->Query1->SQL->Add(sBuf);
	        Form2->Query1->Open();
	        Form2->Query1->Active = true;

	        if ( Form2->Query1->Bof == true && Form2->Query1->Eof == true ) {
	            Form2->Select_DTKSNAM = " ";

	        }else {
	            Form2->Query1->First();
		        if ( Form2->Query1->FieldValues["TRSNAM"].IsEmpty() ) Form2->Select_DTKSNAM = " ";
	     	    else Form2->Select_DTKSNAM = Form2->Query1->FieldValues["TRSNAM"];
	        }
        }
*/
    }
    else {
        if ( Trim(Form1->Edt_DTKSHIN->Text) == "" ) {
             SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ��w�肵�Ă��������B";
             SBr1->Update();
             Form1->Edt_DTKSHIN->SetFocus();
             return;
        }
        Flagcnd = 3;
        strcnd = DelSEPA(Form1->Edt_StartSOKU->Text) + "01";
        strcnd2 = DelSEPA(Form1->Edt_EndSOKU->Text) + "99";
        DTKSHINcnd = Form1->Edt_DTKSHIN->Text;
        StartLOTcnd = Form1->Edt_StartLOT->Text;
        EndLOTcnd = Form1->Edt_EndLOT->Text;
        DTKSCODcnd = "";
    }


    //strcnd = "19991008";     //���������̐ݒ�
    //DTKSHINcnd = "021660-0510";
    //StartLOTcnd = "000001";
    //EndLOTcnd = "20000";
    Form1->ProgressBar1->Position = 0;
    Form1->ProgressBar1->Visible = true;
    MakeData();
    Form1->ProgressBar1->Position = 100;

    //���|�[�g���J��
    if ( Flagcnd == 2 ) {
        Query2->Close();
        Query2->Open();
        if ( Query2->RecordCount > 0 ) {
           Form5->QuickRep1->Preview();
        }
    }
    if ( Flagcnd == 3 ) {
        Query3->Close();
        Query3->Open();
        if ( Query3->RecordCount > 0 ) {
            Form6->QuickRep1->Preview();
        }
     }


    Form1->ProgressBar1->Visible = false;

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

