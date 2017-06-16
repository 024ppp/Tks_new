//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"

#include "Unit1.h"
#include "Unit11.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit6.h"
#include "U_Excel.h"
//---------------------------------------------------------------------------
TForm1 *Form1;

char PC12FileName[MAX_PATH];
char PC34FileName[MAX_PATH];
char StartPATH[MAX_PATH];
//2009.03.13 MTS E.Takase [001]  ��
//�ޗ������@�i�P�Ǝg�p�j�͋@��^�C�v��5�Ƃ���
char PC5FileName[MAX_PATH];
//2009.03.13 MTS E.Takase [001]  ��
//PC3
char PC3FileName[MAX_PATH];
//PC4
char PC4FileName[MAX_PATH];

int KikiType;               // �@��ԍ�PC1,2,3,4
int ShellExeFlag = 0;       // PC12Ctrl.exe or ShareSocket.exe ���s�t���O

int     SEQNOMAX;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
int RSInputFlag;            //RS232C�ǂݍ��݃t���O
bool    DataSave;
int     KEIJKBN_KM02;           //KM02�̐��i�K�i�̌`��敪
int     LD_HP_TAN_KM02;         //KM02�̐��i�K�i�̒P��
int     MAGE_TAN_KM02;          //KM02�̐��i�K�i�̒P��
int     KENSAKU_Mode;           //�ꗗ�������[�h
KDB1_DATA Tmp_KDB1;             // �I�������H���\��

structKM02 KM02;				//�I���������Ӑ�i�Ԃ̐��i�K�i

KDB1_DATA Cur_Kdb1;             // �I�������q�X�g�O�����f�[�^
KDB2_DATA M_Kdb2[1000];         // �v���f�[�^�i�ő�l�F�P�O�O�O�j

KETA_DATA KETA;  //������̌���

double E_Screen_Data[3][20];
int E_Scale;

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
AnsiString MSG_10 = "�f�[�^��ۑ����܂����H" ;
AnsiString MSG_11 = "RS232C�ڑ��G���[���������܂����B" ;
AnsiString MSG_12 = "���萔�����炵�܂��B��낵���ł����H";
//AnsiString MSG_13 = "�v���f�[�^���R�s�[���܂����H";
AnsiString MSG_13 = "���̌������ڂ�������A���̑���σf�[�^���捞�݂܂����H";

AnsiString Select_Str1;
AnsiString Select_Str2;
AnsiString Select_Str3;
AnsiString Select_Str4;
AnsiString Select_Str5;
int Select_Cnt;
AnsiString sBuf;
AnsiString sMsg2 = "�������� 0 �ł�";

int iKojoKbn = 0 ;          // �H��敪


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

     SGr1->ColWidths[0] = Panel8->Width;    //No
     SGr1->ColWidths[1] = Panel19->Width;   //�������ځi���{��j
     SGr1->ColWidths[2] = Panel12->Width;   //�������ځi�p��j

     SGr1->ColWidths[9] = 0;			    //�`��敪��
     SGr1->ColWidths[3] = Panel11->Width;   //�P��
     SGr1->ColWidths[4] = Panel13->Width;   //���萔

     SGr1->ColWidths[5] = Panel22->Width;   //�K�i��
     SGr1->ColWidths[6] = Panel14->Width;   //����
     SGr1->ColWidths[7] = Panel15->Width;   //���
     SGr1->ColWidths[8] = Panel17->Width;   //���� �� �r�� ��
     SGr1->ColWidths[9] = Panel18->Width;   //�����


     SGr1->ColWidths[10] = 0;               //�����N����

     SGr1->ColWidths[11] = 0;               //�`��敪�R�[�h

     SGr1->ColWidths[12] = 0;               //���Ӑ�i��
     SGr1->ColWidths[13] = 0;               //���Еi��
     SGr1->ColWidths[14] = 0;               //�ގ��R�[�h
     SGr1->ColWidths[15] = 0;               //�ގ���
     SGr1->ColWidths[16] = 0;               //���b�gNO
     SGr1->ColWidths[17] = 0;               //SEQNO
     SGr1->ColWidths[18] = 0;               //��������
     SGr1->ColWidths[19] = 0;               //�H���\�� �K�i
     SGr1->ColWidths[20] = 0;               //���萔
     SGr1->ColWidths[21] = 0;               //�o�^��
     SGr1->ColWidths[22] = 0;               //�o�^����
     SGr1->ColWidths[23] = 0;               //�ύX��
     SGr1->ColWidths[24] = 0;               //�ύX����
     SGr1->ColWidths[25] = 0;               //�X�V��
     SGr1->ColWidths[26] = 0;               //�X�V��
     SGr1->ColWidths[27] = 0;               //�������1
     SGr1->ColWidths[28] = 0;               //�������2
     SGr1->ColWidths[29] = 0;               //�������3

/*
     SGr1->ColWidths[0] = 43;    //No
     SGr1->ColWidths[1] = 43;   //�������ځi���{��j
     SGr1->ColWidths[2] = 43;   //�������ځi�p��j
     SGr1->ColWidths[3] = 43;   //���萔
     SGr1->ColWidths[4] = 43;   //�K�i��
     SGr1->ColWidths[5] = 43;   //����
     SGr1->ColWidths[6] = 43;   //���
     SGr1->ColWidths[7] = 43;   //���� �� �r�� ��
     SGr1->ColWidths[8] = 40;                //�����N����
     SGr1->ColWidths[9] = 40;                //���Ӑ�i��
     SGr1->ColWidths[10] = 40;               //���Еi��
     SGr1->ColWidths[11] = 40;               //�ގ��R�[�h
     SGr1->ColWidths[12] = 40;               //�ގ���
     SGr1->ColWidths[13] = 40;               //���b�gNO
     SGr1->ColWidths[14] = 40;               //SEQNO
     SGr1->ColWidths[15] = 40;               //��������
     SGr1->ColWidths[16] = 40;               //�H���\�� �K�i
     SGr1->ColWidths[17] = 40;               //���萔
     SGr1->ColWidths[18] = 40;               //�o�^��
     SGr1->ColWidths[19] = 40;               //�o�^����
     SGr1->ColWidths[20] = 40;               //�ύX��
     SGr1->ColWidths[21] = 40;               //�ύX����
     SGr1->ColWidths[22] = 40;               //�X�V��
     SGr1->ColWidths[23] = 40;               //�X�V��
*/
     // �{�^���̏�����
     BtnF01->Enabled = true;
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

     // �����\����̏�����
     EdtYMD->Text = FormatDateTime("yyyy/mm/dd",Date());
     //USER_COD = 1;
     KENSAKU_Mode = 1;
     //����A�S����
     Panel3->Caption = BUMO_COD;
     Panel4->Caption = BUMO_NAM;
     Panel6->Caption = IntToStr(USER_COD);
     Panel7->Caption = USER_NAM;

     NotFound = true;

     //RS232C �ǂݍ��݃t���O ������
     RSInputFlag = 0;

     Read_Ini();

}
//---------------------------------------------------------------------------
//�u�e�P�F�ꗗ�����v
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
//     KENSAKU_Mode = 3;
    if( !BtnF01->Enabled )    return;
    if( !BtnF01->Tag ){
        ////////////////////
        // �ꗗ����
        Form2->ShowModal();
    }
    else{
        AddHIST();
    }

}
//---------------------------------------------------------------------------
//�u�e�Q�F�O���v
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    if( !BtnF02->Enabled )    return;
    if(SGr1->Row > 0){
        SGr1->Row -= 1;
        SGr1->SetFocus();
    }

}
//---------------------------------------------------------------------------
//�u�e�R�F�����v
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    if( !BtnF03->Enabled )    return;
    if( (SGr1->RowCount-1) > SGr1->Row ){
        SGr1->Row += 1;
        SGr1->SetFocus();
    }
}
//---------------------------------------------------------------------------
//�u�e�S�F����v
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
//     Form1->Hide();
//     Form3->Show();
 AnsiString sBuf ;
 int i, T_No;

 bool retDLL;
 bool wReturn;
 int PassFlag;
 STARTUPINFO si;
 PROCESS_INFORMATION pi;
 char curpass[MAX_PATH];
 SHELLEXECUTEINFO sei;

     if( !BtnF04->Enabled )    return;
/*
     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     Cur_Kdb1.KENSA_YMD = SGr1->Cells[14][SGr1->Row];
     Cur_Kdb1.SEQNO = StrToInt(SGr1->Cells[15][SGr1->Row]);
     Cur_Kdb1.No = SGr1->Row+1;
*/
     // Test
     //Cur_Kdb1.KENSA_YMD = "19991108";
     //Cur_Kdb1.SEQNO = 1;
     //Cur_Kdb1.No = 5;
     if( SGr1->Cells[1][SGr1->Row] == "" || Trim(SGr1->Cells[19][SGr1->Row]) == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "����Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     //�����l ����l�̔�r
     switch( StrToInt(SGr1->Cells[19][SGr1->Row]) ){
        case 1:         // �����K�i
           // �����K�i
           if ( Trim( SGr1->Cells[6][SGr1->Row] ) == "" ) SGr1->Cells[6][SGr1->Row] = "0";
           // ����K�i
           if ( Trim( SGr1->Cells[7][SGr1->Row] ) == "" ) SGr1->Cells[7][SGr1->Row] = "0";
           if ( StrToFloat(SGr1->Cells[6][SGr1->Row]) >= StrToFloat(SGr1->Cells[7][SGr1->Row]) ) {
              // �X�e�[�^�X���b�Z�[�W
              SBr1->Panels->Items[0]->Text = "�K�i�l�𐳂����w�肵�Ă��������B";
              SBr1->Update();
              SGr1->SetFocus();
              return;
           }
           break;

        case 2:         // �����K�i
           // �����K�i
           if ( Trim( SGr1->Cells[6][SGr1->Row] ) == "" ) SGr1->Cells[6][SGr1->Row] = "0";
           break;

        case 3:         // ����K�i
           // ����K�i
           if ( Trim( SGr1->Cells[7][SGr1->Row] ) == "" ) SGr1->Cells[7][SGr1->Row] = "0";
           if ( StrToFloat(SGr1->Cells[7][SGr1->Row]) == 0 ) {
              // �X�e�[�^�X���b�Z�[�W
              SBr1->Panels->Items[0]->Text = "�K�i�l�𐳂����w�肵�Ă��������B";
              SBr1->Update();
              SGr1->SetFocus();
              return;
    	   }
           break;
     }

     //�f�[�^�x�[�X�ۑ�
     BtnF11Click(Sender);

     Cur_Kdb1.KENSA_YMD = DelSEPA(EdtYMD->Text);
     Cur_Kdb1.SEQNO = StrToInt(SGr1->Cells[17][SGr1->Row]);
     Cur_Kdb1.No = SGr1->Row+1;


     // Read Data Base (KdB1)
     //�f�[�^�x�[�X Query ������
     Query_Kdb1->Close();
     Query_Kdb1->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "* ";
     sBuf += "FROM KDB1 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kdb1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kdb1.SEQNO + "' ";
	 sBuf += " AND DTKSHIN = '" + EdtHIN->Text + "'";
	 sBuf += " AND LOTNO = '" + EdtLOT->Text + "'";
         sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_�H��敪�ǉ�

     Query_Kdb1->SQL->Add(sBuf);
     Query_Kdb1->Open();
     Query_Kdb1->Active = true;

     if ( Query_Kdb1->RecordCount > 0 ) {
        Query_Kdb1->First();

        if ( Query_Kdb1->FieldValues["DTKSHIN"].IsNull())
           Cur_Kdb1.DTKSHIN = " ";
        else
           Cur_Kdb1.DTKSHIN = Query_Kdb1->FieldValues["DTKSHIN"];

        if ( Query_Kdb1->FieldValues["HINBAN"].IsNull())
           Cur_Kdb1.HINBAN = " ";
        else
           Cur_Kdb1.HINBAN = Query_Kdb1->FieldValues["HINBAN"];

        if ( Query_Kdb1->FieldValues["ZISCOD"].IsNull())
           Cur_Kdb1.ZISCOD = " ";
        else
           Cur_Kdb1.ZISCOD = Query_Kdb1->FieldValues["ZISCOD"];

        if ( Query_Kdb1->FieldValues["ZISNAM"].IsNull())
           Cur_Kdb1.ZISNAM = " ";
        else
           Cur_Kdb1.ZISNAM = Query_Kdb1->FieldValues["ZISNAM"];

        if ( Query_Kdb1->FieldValues["LOTNO"].IsNull())
           Cur_Kdb1.LOTNO = " ";
        else
           Cur_Kdb1.LOTNO = Query_Kdb1->FieldValues["LOTNO"];

        if ( Query_Kdb1->FieldValues["KENSA_KMK"].IsNull())
           Cur_Kdb1.KENSA_KMK = 0;
        else
           Cur_Kdb1.KENSA_KMK = Query_Kdb1->FieldValues["KENSA_KMK"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_J"].IsNull())
           Cur_Kdb1.KOUMOKU_J = " ";
        else
           Cur_Kdb1.KOUMOKU_J = Query_Kdb1->FieldValues["KOUMOKU_J"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_E"].IsNull())
           Cur_Kdb1.KOUMOKU_E = " ";
        else
           Cur_Kdb1.KOUMOKU_E = Query_Kdb1->FieldValues["KOUMOKU_E"];

        if ( Query_Kdb1->FieldValues["TANI"].IsNull())
           Cur_Kdb1.TANI = " ";
        else
           Cur_Kdb1.TANI = Query_Kdb1->FieldValues["TANI"];

        if ( Query_Kdb1->FieldValues["KEIJKBN"].IsNull())
           Cur_Kdb1.KEIJKBN = 0;
        else
           Cur_Kdb1.KEIJKBN = Query_Kdb1->FieldValues["KEIJKBN"];

        if ( Query_Kdb1->FieldValues["HIST_SOKUT"].IsNull())
           Cur_Kdb1.HIST_SOKUT = 0;
        else
           Cur_Kdb1.HIST_SOKUT = Query_Kdb1->FieldValues["HIST_SOKUT"];
        Cur_Kdb1.HIST_SOKUT_Ori = Cur_Kdb1.HIST_SOKUT;

        if ( Query_Kdb1->FieldValues["HIST_KIKAK"].IsNull())
           Cur_Kdb1.HIST_KIKAK = 0;
        else
           Cur_Kdb1.HIST_KIKAK = Query_Kdb1->FieldValues["HIST_KIKAK"];

        if ( Query_Kdb1->FieldValues["HIST_MIN"].IsNull())
           Cur_Kdb1.HIST_MIN = 0;
        else
           Cur_Kdb1.HIST_MIN = Query_Kdb1->FieldValues["HIST_MIN"];

        if ( Query_Kdb1->FieldValues["HIST_MAX"].IsNull())
           Cur_Kdb1.HIST_MAX = 0;
        else
           Cur_Kdb1.HIST_MAX = Query_Kdb1->FieldValues["HIST_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SU"].IsNull())
           Cur_Kdb1.SOKUTE_SU = 0;
        else
           Cur_Kdb1.SOKUTE_SU = Query_Kdb1->FieldValues["SOKUTE_SU"];
        Cur_Kdb1.SOKUTE_SU_Ori = Cur_Kdb1.SOKUTE_SU;

        if ( Query_Kdb1->FieldValues["SOKUTE_KET"].IsNull())
           Cur_Kdb1.SOKUTE_KET = 2;
        else
           Cur_Kdb1.SOKUTE_KET = Query_Kdb1->FieldValues["SOKUTE_KET"];

        if ( Query_Kdb1->FieldValues["SOKUTE_AVE"].IsNull())
           Cur_Kdb1.SOKUTE_AVE = 0;
        else
           Cur_Kdb1.SOKUTE_AVE = Query_Kdb1->FieldValues["SOKUTE_AVE"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MIN"].IsNull())
           Cur_Kdb1.SOKUTE_MIN = 0;
        else
           Cur_Kdb1.SOKUTE_MIN = Query_Kdb1->FieldValues["SOKUTE_MIN"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MAX"].IsNull())
           Cur_Kdb1.SOKUTE_MAX = 0;
        else
           Cur_Kdb1.SOKUTE_MAX = Query_Kdb1->FieldValues["SOKUTE_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_R"].IsNull())
           Cur_Kdb1.SOKUTE_R = 0;
        else
           Cur_Kdb1.SOKUTE_R = Query_Kdb1->FieldValues["SOKUTE_R"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SGM"].IsNull())
           Cur_Kdb1.SOKUTE_SGM = 0;
        else
           Cur_Kdb1.SOKUTE_SGM = Query_Kdb1->FieldValues["SOKUTE_SGM"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CP"].IsNull())
           Cur_Kdb1.SOKUTE_CP = 0;
        else
           Cur_Kdb1.SOKUTE_CP = Query_Kdb1->FieldValues["SOKUTE_CP"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CPK"].IsNull())
           Cur_Kdb1.SOKUTE_CPK = 0;
        else
           Cur_Kdb1.SOKUTE_CPK = Query_Kdb1->FieldValues["SOKUTE_CPK"];

        if ( Query_Kdb1->FieldValues["SOKUTE_K"].IsNull())
           Cur_Kdb1.SOKUTE_K = 0;
        else
           Cur_Kdb1.SOKUTE_K = Query_Kdb1->FieldValues["SOKUTE_K"];

        if ( Query_Kdb1->FieldValues["SOKUTE_P"].IsNull())
           Cur_Kdb1.SOKUTE_P = 0;
        else
           Cur_Kdb1.SOKUTE_P = Query_Kdb1->FieldValues["SOKUTE_P"];

        if ( Query_Kdb1->FieldValues["JYOKEN1"].IsNull())
           Cur_Kdb1.JYOKEN1 = 0;
        else
           Cur_Kdb1.JYOKEN1 = Query_Kdb1->FieldValues["JYOKEN1"];

        if ( Query_Kdb1->FieldValues["JYOKEN2"].IsNull())
           Cur_Kdb1.JYOKEN2 = 0;
        else
           Cur_Kdb1.JYOKEN2 = Query_Kdb1->FieldValues["JYOKEN2"];

        if ( Query_Kdb1->FieldValues["UPDCNT"].IsNull())
           Cur_Kdb1.UPDCNT = 0;
        else
           Cur_Kdb1.UPDCNT = Query_Kdb1->FieldValues["UPDCNT"];

        if ( Query_Kdb1->FieldValues["UPDCHR"].IsNull())
           Cur_Kdb1.UPDCHR = 0;
        else
           Cur_Kdb1.UPDCHR = Query_Kdb1->FieldValues["UPDCHR"];

        if ( Query_Kdb1->FieldValues["TANI"].IsNull())
           Cur_Kdb1.TANI = "";
        else
           Cur_Kdb1.TANI = Query_Kdb1->FieldValues["TANI"];


      } else {
        Query_Kdb1->Close();
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�������ʂO���ł����iKDB1�j�B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
      }

     Query_Kdb1->Close();

     for ( i = 0; i < Nums; i++) {
        M_Kdb2[i].SOKUTEI_CH = 0;
        M_Kdb2[i].SOKUTEI_MEI1 = 0;
        M_Kdb2[i].SOKUTEI_MEI2 = 0;
        M_Kdb2[i].SOKUTEI_MEI3 = 0;
        //2002/12/28 E.Takase if (Cur_Kdb1.KENSA_KMK == 8)
        if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12)
           M_Kdb2[i].SOKUTEI_MEI4 = Cur_Kdb1.JYOKEN1;
        else
           M_Kdb2[i].SOKUTEI_MEI4 = 0;
        M_Kdb2[i].SOKUTEI_MEI5 = 0;
        M_Kdb2[i].SOKUTEI_MEI6 = 0;
        if (Cur_Kdb1.KENSA_KMK == 7)
           M_Kdb2[i].SOKUTEI_MEI7 = Cur_Kdb1.JYOKEN2;
        else
           M_Kdb2[i].SOKUTEI_MEI7 = 0;
        M_Kdb2[i].DatabaseFlag = 0;
     }

     // Read Data Base (Kdb2)
     //�f�[�^�x�[�X Query ������
     Query_Kdb2->Close();
     Query_Kdb2->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "SOKUTEI_NO, SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, ";
     sBuf += "SOKUTEI_MEI4, SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7 ";
     sBuf += "FROM KDB2 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kdb1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kdb1.SEQNO + "' ";
     sBuf += " AND DTKSHIN = '" + Cur_Kdb1.DTKSHIN + "' " + " AND LOTNO = '" + Cur_Kdb1.LOTNO + "' ";
     sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_�H��敪�ǉ�
     sBuf += "ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

     Query_Kdb2->SQL->Add(sBuf);
     Query_Kdb2->Open();
     Query_Kdb2->Active = true;

     if ( Query_Kdb2->RecordCount > 0 ) {
        Query_Kdb2->First();
        while( !Query_Kdb2->Eof ) {
           if ( Query_Kdb2->FieldValues["SOKUTEI_NO"].IsNull()) {
              T_No = 0;
           } else {
              T_No = Query_Kdb2->FieldValues["SOKUTEI_NO"];
           }

           if (T_No > 0) {
              M_Kdb2[T_No - 1].DatabaseFlag = 1;
//              if (T_No <= Cur_Kdb1.SOKUTE_SU) {
                 if ( Query_Kdb2->FieldValues["SOKUTEI_CH"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_CH = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_CH = Query_Kdb2->FieldValues["SOKUTEI_CH"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI1"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI1 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI1 = Query_Kdb2->FieldValues["SOKUTEI_MEI1"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI2"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI2 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI2 = Query_Kdb2->FieldValues["SOKUTEI_MEI2"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI3"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI3 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI3 = Query_Kdb2->FieldValues["SOKUTEI_MEI3"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI4"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI4 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI4 = Query_Kdb2->FieldValues["SOKUTEI_MEI4"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI5"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI5 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI5 = Query_Kdb2->FieldValues["SOKUTEI_MEI5"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI6"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI6 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI6 = Query_Kdb2->FieldValues["SOKUTEI_MEI6"];

                 if ( Query_Kdb2->FieldValues["SOKUTEI_MEI7"].IsNull())
                    M_Kdb2[T_No - 1].SOKUTEI_MEI7 = 0;
                 else
                    M_Kdb2[T_No - 1].SOKUTEI_MEI7 = Query_Kdb2->FieldValues["SOKUTEI_MEI7"];
//              } else {
//                 M_Kdb2[T_No - 1].SOKUTEI_CH = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI1 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI2 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI3 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI4 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI5 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI6 = 0;
//                 M_Kdb2[T_No - 1].SOKUTEI_MEI7 = 0;
//              }
           }
           Query_Kdb2->Next();
        }
     }

     Query_Kdb2->Close();

     //2002/12/28 E.Takase
     //if (Cur_Kdb1.KENSA_KMK == 7 || Cur_Kdb1.KENSA_KMK == 8) {
     if (Cur_Kdb1.KENSA_KMK == 7 || Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {
        for (i = 1; i < Nums; i++) {
            if (Cur_Kdb1.KENSA_KMK == 7)
               M_Kdb2[i].SOKUTEI_MEI7 = M_Kdb2[0].SOKUTEI_MEI7;
            else
               M_Kdb2[i].SOKUTEI_MEI4 = M_Kdb2[0].SOKUTEI_MEI4;
        }
     }

    //2002/11/20 E.Takase
    //��̔�d�E��R���E�Ȃ������̏ꍇ ���� �R�s�[��������ꍇ
    //2002/12/28 E.Takase
    //�Ȃ������i�����j�̏ꍇ��
    //�f�[�^�R�s�[��ʂ�\��
    Form11->DataCopyFlag = 0;
    if (Form11->ChkCopyData() &&
        (Cur_Kdb1.KENSA_KMK == 5 || Cur_Kdb1.KENSA_KMK == 7 ||
         Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12 )) {
        switch( MessageDlg( MSG_13, mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v
            case mrYes:
                Form11->ShowModal();
                break;
            // �uNo�v
            case mrNo:
                break;
            case mrCancel:
                return;
                break;
        }
    }
     


     // ����v���O�����N������
     ZeroMemory( &sei, sizeof(sei) );
     sei.cbSize = sizeof(sei);
     sei.fMask = SEE_MASK_NOCLOSEPROCESS;
     //sei.hwnd = hWnd;
     sei.lpVerb = "open";
     //sei.nShow = SW_SHOWMINIMIZED ;
     sei.nShow = SW_SHOWNOACTIVATE | SW_SHOWMINIMIZED ;
     //sei.nShow = SW_SHOWNORMAL;
     sei.lpDirectory = StartPATH;
     sei.lpParameters = "";
     if (KikiType == 1 || KikiType == 2) {  // PC1,2
        //2002/12/28 E.Takase
        //if (Cur_Kdb1.KENSA_KMK == 0 || Cur_Kdb1.KENSA_KMK == 1 || Cur_Kdb1.KENSA_KMK == 2 ||
        //   Cur_Kdb1.KENSA_KMK == 5 || Cur_Kdb1.KENSA_KMK == 7 || Cur_Kdb1.KENSA_KMK == 8 ) {
        if (Cur_Kdb1.KENSA_KMK == 0 || Cur_Kdb1.KENSA_KMK == 1 || Cur_Kdb1.KENSA_KMK == 2 ||
           Cur_Kdb1.KENSA_KMK == 5 || Cur_Kdb1.KENSA_KMK == 7 || Cur_Kdb1.KENSA_KMK == 8  ||
           Cur_Kdb1.KENSA_KMK == 12 ) {
           sei.lpFile = PC12FileName;
           while (FindWindow("WSockWClass", "TRIS �F ���Ԍ���(PC1)") != NULL)
                 Sleep(1000);
           retDLL = ShellExecuteEx(&sei);
           Sleep(2000);
           ShellExeFlag = 1;
        } else
           ShellExeFlag = 0;

     //20160729 PC3,PC4�̒ǉ�
     //PC3
     } else if (KikiType == 3) { //PC3

        if (Cur_Kdb1.KENSA_KMK == 3 || Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 7 ||
           Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 11 ||
           Cur_Kdb1.KENSA_KMK == 12 ) {

           sei.lpFile = PC3FileName;
           while (FindWindow("WSockWClass", "TRIS�F���Ԍ���(PC3)") != NULL)
                 Sleep(1000);
           retDLL = ShellExecuteEx(&sei);
           Sleep(2000);
           ShellExeFlag = 1;
        } else
           ShellExeFlag = 0;

     //PC4
     } else if (KikiType == 4) { //PC4

        if (Cur_Kdb1.KENSA_KMK == 3 || Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 7 ||
           Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 11 ||
           Cur_Kdb1.KENSA_KMK == 12 ) {

           sei.lpFile = PC4FileName;
           while (FindWindow("WSockWClass", "TRIS�F���Ԍ���(PC4)") != NULL)
                 Sleep(1000);
           retDLL = ShellExecuteEx(&sei);
           Sleep(2000);
           ShellExeFlag = 1;
        } else
           ShellExeFlag = 0;

     //2009.03.13 MTS E.Takase [001]  ��
     //�ޗ������@�i�P�Ǝg�p�j�͋@��^�C�v��5�Ƃ���
     } else if (KikiType == 5) { //PC5

        if (Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 ||
            Cur_Kdb1.KENSA_KMK == 11 ||Cur_Kdb1.KENSA_KMK == 12 ) {

           sei.lpFile = PC5FileName;
           while (FindWindow("WSockWClass", "TRIS�F���Ԍ���(PC5)") != NULL)
                 Sleep(1000);
           retDLL = ShellExecuteEx(&sei);
           Sleep(2000);
           ShellExeFlag = 1;
        } else
           ShellExeFlag = 0;

     //2009.03.13 MTS E.Takase [001]  ��
     } else { //KikiType=6
        //20160729 KikiType=6�̒ǉ�
        /*
        //2002/12/28 E.Takase
        //if (Cur_Kdb1.KENSA_KMK == 3 || Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 7 ||
        //   Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 11) {

        if (Cur_Kdb1.KENSA_KMK == 3 || Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 7 ||
           Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 11 ||
           Cur_Kdb1.KENSA_KMK == 12 ) {

           sei.lpFile = PC34FileName;
           while (FindWindow("WSockWClass", "TRIS�F���Ԍ���(PC3,4)") != NULL)
                 Sleep(1000);
           retDLL = ShellExecuteEx(&sei);
           Sleep(2000);
           ShellExeFlag = 1;
        } else
           ShellExeFlag = 0;
        */
     }

     //MessageDlg( "Start Of ScreenInit", mtConfirmation, mbYesNoCancel, 0);

     // �v����ʂ��J��
     Form3->ScreenInitFlag = 0;
     Form3->FormScreenInit(0);
     Form1->Hide();

     //����ۑ��t���O
     SOKUTEI_SAVE_FLAG = 1;
     //MessageDlg( "End Of ScreenInit", mtConfirmation, mbYesNoCancel, 0);

     Form3->ShowModal();

     if (ShellExeFlag == 1)
        Sleep(2000);

     // ��ʂ̑��萔��ύX����
     //�q�X�g�O�������萔 HISUT_SOKUT
     sBuf = IntToStr(Cur_Kdb1.HIST_SOKUT_Ori);
     SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;
     Edt1->Text = sBuf;
     
     //���萔 SOKUTE_SU
     SGr1->Cells[20][SGr1->Row] = Cur_Kdb1.SOKUTE_SU_Ori;

     if ( SOKUTEI_SAVE_FLAG != 0 ) {
     //�u�߂�v�̂Ƃ��ۑ����Ȃ��ŏI���ɂ����Ƃ��� ����
     	if ( StrToInt (SGr1->Cells[4][SGr1->Row]) == StrToInt (SGr1->Cells[20][SGr1->Row])) {
        	sBuf = "��";//	�����
     	} else  {
     		if (Cur_Kdb1.SOKUTE_SU > 0 ) {
           	sBuf = "�r��";//	����r��
        	} else {
	   			sBuf = "��";//	������
        	}
     	}
     	SGr1->Cells[8][SGr1->Row] = sBuf;

        //2002/11/18 E.Takase
        //�����
        SGr1->Cells[9][SGr1->Row] = Form2->GetTANNAM(Cur_Kdb1.UPDCHR);
     }

	 //����ۑ��t���O
     SOKUTEI_SAVE_FLAG = 1;

     SGr1->SetFocus();
}
//---------------------------------------------------------------------------
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
//�u�e�U�FExcel�o�́v
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{
    bool flag;
    char *ptr;

    //������� ����l
	KETA.MIN = 2;
	KETA.MAX = 2;
	KETA.R = 2;
	KETA.AVE =  2 + 1;
	KETA.SGM = 3;
	KETA.CP = 2;
	KETA.K = 3;
	KETA.CPK = 2;
	KETA.P = 3;
	//KETA.SOKUTE_AVE = Cur_Kdb1.SOKUTE_AVE;
	//KETA.SOKUTE_MIN = Cur_Kdb1.SOKUTE_MIN;
	//KETA.SOKUTE_MAX = Cur_Kdb1.SOKUTE_MAX;
	//KETA.SOKUTE_R   = Cur_Kdb1.SOKUTE_R  ;
	//KETA.SOKUTE_SGM = Cur_Kdb1.SOKUTE_SGM;
	//KETA.SOKUTE_CP  = Cur_Kdb1.SOKUTE_CP ;
	//KETA.SOKUTE_CPK = Cur_Kdb1.SOKUTE_CPK;
	//KETA.SOKUTE_K   = Cur_Kdb1.SOKUTE_K  ;
	//KETA.SOKUTE_P   = Cur_Kdb1.SOKUTE_P  ;

//    Form6->ShowModal();
//    if ( Form6->ModalResult == mrCancel ) return;

    
    if( !BtnF06->Enabled )    return;
    flag = CSV2_Write();
    if ( flag ) {

        flag = Excel2_Write();
        if ( !(flag) ) {
            // �X�e�[�^�X���b�Z�[�W
            SBr1->Panels->Items[0]->Text = "Excel�̋N���Ɏ��s���܂���";
            SBr1->Update();

        }

    } else {
     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�f�[�^�쐬�Ɏ��s���܂���";
     SBr1->Update();

    }
}
//---------------------------------------------------------------------------
//�u�e�V�F�����v
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     int iRow,i;
     AnsiString sYMD;
     AnsiString sBuf;

     if( !BtnF07->Enabled )    return;

     sYMD = DelSEPA(EdtYMD->Text);
     if( sYMD == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�쐬������͂��Ă�������";
        SBr1->Update();
        KENSAKU_Mode = 1;
		EdtYMD->SetFocus();
        return;
     }
     if( EdtHIN->Text == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ���͂��Ă�������";
        SBr1->Update();
        KENSAKU_Mode = 2;
		EdtHIN->SetFocus();
        return;
     }
     if( EdtLOT->Text == "" ){
        //// �X�e�[�^�X���b�Z�[�W
        //SBr1->Panels->Items[0]->Text = "���b�gNO����͂��Ă�������";
        //SBr1->Update();
        ////KENSAKU_Mode = 3;
	 	//EdtLOT->SetFocus();
        //return;
        EdtLOT->Text = " ";
     }


     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     //SGr1������
     SGr1->RowCount = 1;
     iRow = SGr1->RowCount;

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }
/*
     SGr1->Cells[0][0] = "";
     SGr1->Cells[1][0] = "";
     SGr1->Cells[2][0] = "";
     SGr1->Cells[3][0] = "";
     SGr1->Cells[4][0] = "";
     SGr1->Cells[5][0] = "";
     SGr1->Cells[6][0] = "";
     SGr1->Cells[7][0] = "";
     SGr1->Cells[8][0] = "";
     SGr1->Cells[9][0] = "";
     SGr1->Cells[10][0] = "";
     SGr1->Cells[11][0] = "";
     SGr1->Cells[12][0] = "";
     SGr1->Cells[13][0] = "";
     SGr1->Cells[14][0] = "";
     SGr1->Cells[15][0] = "";
     SGr1->Cells[16][0] = "";
     SGr1->Cells[17][0] = "";
     SGr1->Cells[18][0] = "";
     SGr1->Cells[19][0] = "";
     SGr1->Cells[20][0] = "";
     SGr1->Cells[21][0] = "";
     SGr1->Cells[22][0] = "";
     SGr1->Cells[23][0] = "";
     SGr1->Cells[24][0] = "";
     SGr1->Cells[25][0] = "";
     SGr1->Cells[26][0] = "";
     SGr1->Cells[27][0] = "";
     SGr1->Cells[28][0] = "";
     SGr1->Cells[29][0] = "";
*/

     //KDB1 KM02 ����
     if ( MAIN_Serch01() == 0 ) {
     	//�������� �O��
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ����i�K�i�}�X�^�ɓo�^����Ă��܂���";
        SBr1->Update();
        EdtHIN->SetFocus();
        KENSAKU_Mode = 2;
     	// �{�^���̏�����
     	BtnF01->Enabled = true;
     	BtnF02->Enabled = false;
     	BtnF03->Enabled = false;
     	BtnF04->Enabled = false;
     	BtnF05->Enabled = true;
     	BtnF06->Enabled = true;
     	BtnF07->Enabled = true;
     	BtnF08->Enabled = false;
     	BtnF09->Enabled = false;
     	BtnF10->Enabled = false;
     	BtnF11->Enabled = false;
     	BtnF12->Enabled = true;
        NotFound = true;
        return;

     }

     iRow = SGr1->RowCount - 1;
     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     SGr1->SetFocus();


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

     KENSAKU_Mode = -1;
     BtnF01->Enabled = false;
     SGr1SelectCell( Sender, 1, 0, true);


}

//---------------------------------------------------------------------------
//�u�e�W�F�V�K�o�^�v
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    AnsiString sYMD;
    int i;

    sYMD = DelSEPA(EdtYMD->Text);

    if( !BtnF08->Enabled )    return;

    // �X�e�[�^�X���b�Z�[�W
    SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
    SBr1->Update();
    //Tmp_KDB1������
    Tmp_KDB1_SYOKIKA();

    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    if ( Cmb1->Text.IsEmpty() ) {
        //Empty�̎��A�X�y�[�X������
        //SBr1->Panels->Items[0]->Text = "�K�{����(�������ځi���{��j)����͂��ĉ������B";
        //SBr1->Update();
        //Cmb1->SetFocus();
        //return;
        Cmb1->Text = "";
        Tmp_KDB1.KOUMOKU_J = " ";
    } else { //�������ځi���{��j
        Tmp_KDB1.KOUMOKU_J = Cmb1->Text;
    }

    //	��������
    if( Trim(EdtKMK->Text) == "" )  Tmp_KDB1.KENSA_KMK	=-1;
	else Tmp_KDB1.KENSA_KMK	= StrToInt(EdtKMK->Text);

    if ( Cmb2->Text.IsEmpty() ) {
        //Empty�̎��A�X�y�[�X������
        //SBr1->Panels->Items[0]->Text = "�K�{����(�������ځi�p��j)����͂��ĉ������B";
        //SBr1->Update();
        //Cmb2->SetFocus();
        //return;
        Cmb2->Text = "";
        Tmp_KDB1.KOUMOKU_E = " ";

    } else { //�������ځi�p��j
        Tmp_KDB1.KOUMOKU_E = Cmb2->Text;
    }
    if ( Edt1->Text.IsEmpty() ) {
        SBr1->Panels->Items[0]->Text = "�K�{���ځi���萔�j����͂��ĉ������B";
        SBr1->Update();
        Edt1->SetFocus();
        return;
    } else { //���萔
        Tmp_KDB1.HIST_SOKUT = StrToInt(Edt1->Text);
    }
    if ( Cmb3->ItemIndex == -1 ) {
        SBr1->Panels->Items[0]->Text = "�K�{���ځi�K�i�j����͂��ĉ������B";
        SBr1->Update();
        Cmb3->SetFocus();
        return;
    } else { //�K�i
        Tmp_KDB1.HIST_KIKAK = Cmb3->ItemIndex + 1;

    }

    //�����l ����l�̔�r
    if ( Tmp_KDB1.HIST_KIKAK == 1 ) {
    	if ( StrToFloat(Edt2->Text) >= StrToFloat(Edt3->Text) ) {
        	SBr1->Panels->Items[0]->Text = "�K�i�l���m�F���ĉ������B";
        	SBr1->Update();
        	Edt2->SetFocus();
        	return;
    	}
    }
    //����l�̃`�F�b�N
    if ( Tmp_KDB1.HIST_KIKAK == 3 ) {
    	if ( StrToFloat(Edt3->Text) <= 0) {
        	SBr1->Panels->Items[0]->Text = "����K�i�l���m�F���ĉ������B";
        	SBr1->Update();
        	Edt3->SetFocus();
        	return;
    	}
    }

    if ( ( !(Edt2->Text.IsEmpty() ) )  &&
            ( Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK== 2  )) // �q�X�g�O���������K�i
         Tmp_KDB1.HIST_MIN = StrToFloat(Edt2->Text);

    if ( ( !(Edt3->Text.IsEmpty() ) )  &&
            ( Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK== 3  ))// �q�X�g�O��������K�i
         Tmp_KDB1.HIST_MAX = StrToFloat(Edt3->Text);

    //�`��敪
    if ( EdtKEIJKBN->Text == "" ) Tmp_KDB1.KEIJKBN = 0;
    else Tmp_KDB1.KEIJKBN = StrToInt( EdtKEIJKBN->Text );


    //�P��
    //Check
    if ( (CheckTANI( Tmp_KDB1.KENSA_KMK, Cmb5->Text )) == 0 ) {
    //�P�� �Ԉ���Ă���
        SBr1->Panels->Items[0]->Text = "�P�ʂ��Ԉ���Ă��܂��B";
        SBr1->Update();
        Cmb5->SetFocus();
        return;
    }
    Tmp_KDB1.TANI = Cmb5->Text;

    // �o�^��
    Tmp_KDB1.ADDYMD = FormatDateTime("yyyymmdd",Date());
    // �o�^����
    Tmp_KDB1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // �X�V��
    Tmp_KDB1.UPDCNT  = 0;
    // �X�V��
    Tmp_KDB1.UPDCHR  = USER_COD;
    // �����
    Tmp_KDB1.KENSA_YMD  = sYMD;
    //// ���Ӑ�i��
    //Tmp_KDB1.DTKSHIN  = EdtHIN->Text;
    //// �ގ��R�[�h
    //Tmp_KDB1.ZISCOD  = EdtZIS->Caption;
    ///�ގ���
    //Tmp_KDB1.ZISNAM = EdtZISNAM->Text;


    // ���Ӑ�i��
    if( EdtHIN->Text.IsEmpty() ) Tmp_KDB1.DTKSHIN = " ";
    Tmp_KDB1.DTKSHIN  = EdtHIN->Text;
    // �ގ��R�[�h
    Tmp_KDB1.ZISCOD  = EdtZIS->Text;
    if( Tmp_KDB1.ZISCOD.IsEmpty() ) Tmp_KDB1.ZISCOD = " ";
    //�ގ���
    Tmp_KDB1.ZISNAM = EdtZISNAM->Caption;
    if( Tmp_KDB1.ZISNAM.IsEmpty() ) Tmp_KDB1.ZISNAM = " ";

    //���茅
    Tmp_KDB1.SOKUTE_KET = 2;

    ////��������P �������ڂ���̔�d�̎� �j�l�O�Q�̌`��敪����
    //if ( Tmp_KDB1.KENSA_KMK == 5 ) {
    //    sBuf = "SELECT KEIJKBN FROM KM02 WHERE KM02.DTKSHIN = '";
    //    sBuf += Tmp_KDB1.DTKSHIN + "'";
    //    Form1->Query1->Close();
    //    Form1->Query1->SQL->Clear();
    //
    //    Form1->Query1->SQL->Add(sBuf);
    //    Form1->Query1->Open();
    //    Form1->Query1->Active = true;
    //    if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
    //       Tmp_KDB1.JYOKEN1 = 0;
    //    } else { Tmp_KDB1.JYOKEN1 = StrToFloat(Form1->Query1->Fields->Fields[0]->AsString); }
    //} else { Tmp_KDB1.JYOKEN1 = 0; }

    //���Еi��
    Tmp_KDB1.HINBAN = KM02.HINBAN;
    //sBuf = "SELECT HINBAN FROM KM02 WHERE KM02.DTKSHIN = '";
    //sBuf += Tmp_KDB1.DTKSHIN + "'";
    //sBuf += " AND KM02.DTKSHIN = '";
    //sBuf += Tmp_KDB1.DTKSHIN + "'";
    //
    //Form1->Query1->Close();
    //Form1->Query1->SQL->Clear();
    //
    //Form1->Query1->SQL->Add(sBuf);
    //Form1->Query1->Open();
    //Form1->Query1->Active = true;
    //if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
    //  //ShowMessage( "�ގ������Ԉ���Ă��܂��B" );
    //  //return;
    //  Tmp_KDB1.HINBAN = " ";
    //}else {
    //  Form1->Query1->First();
    //  Tmp_KDB1.HINBAN = Form1->Query1->Fields->Fields[0]->AsString;
    //}
    // ���b�gNo
    Tmp_KDB1.LOTNO  = EdtLOT->Text;
    // SEQNO
    Tmp_KDB1.SEQNO  = SEQNOMAX + 1;
    // �������
    Tmp_KDB1.JYOKEN1  = StrToFloat(EdtJYOKEN1->Text);
    Tmp_KDB1.JYOKEN2  = StrToFloat(EdtJYOKEN2->Text);
    Tmp_KDB1.JYOKEN3  = EdtJYOKEN3->Text;

     //AddData
     if( AddData() == False ){
        return;
     }

        //�V�K�f�[�^��SGr1�ɕ\��
        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
        sBuf = SGr1->RowCount;
		SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

		sBuf = Tmp_KDB1.KOUMOKU_J;
		SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;   //�������ځi���{��j

		sBuf = Tmp_KDB1.KOUMOKU_E;
		SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;   //�������ځi�p��j

		sBuf = IntToStr(Tmp_KDB1.HIST_SOKUT);
		SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;   //���萔

		sBuf = Tmp_KDB1.TANI;
		SGr1->Cells[3][SGr1->RowCount - 1] = sBuf;   //�P��

		sBuf = IntToStr(Tmp_KDB1.KEIJKBN);
		SGr1->Cells[11][SGr1->RowCount - 1] = sBuf;   //�`��敪
        switch(Tmp_KDB1.KEIJKBN)
        {
			case 1: //������
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "������";
                SGr1->Cells[30][SGr1->RowCount - 1] = "������";
                break;
            case 2: //�~��
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "�~��";
                SGr1->Cells[30][SGr1->RowCount - 1] = "�~��";
                break;
            case 3: //�R���~ 2002/11/14 E.Takase
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "�R���~";
                SGr1->Cells[30][SGr1->RowCount - 1] = "�R���~";
                break;
            default:
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = " ";
                SGr1->Cells[30][SGr1->RowCount - 1] = " ";
                break;

        }

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		switch(StrToInt(sBuf))   //�K�i��
		{
			case 1:
				SGr1->Cells[5][SGr1->RowCount - 1] = "����";

				//�����K�i
                SGr1->Cells[6][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //����K�i
                SGr1->Cells[7][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

			case 2:
				SGr1->Cells[5][SGr1->RowCount - 1] = "����";

				//�����K�i
                SGr1->Cells[6][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //����K�i
                SGr1->Cells[7][SGr1->RowCount - 1] = " ";

				break;

			case 3:
				SGr1->Cells[5][SGr1->RowCount - 1] = "���";

                //�����K�i
				SGr1->Cells[6][SGr1->RowCount - 1] = " ";

                //����K�i
                SGr1->Cells[7][SGr1->RowCount - 1] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

		}
		if ( Tmp_KDB1.HIST_SOKUT == Tmp_KDB1.SOKUTE_SU ) {
			sBuf = "��";//	�����
		} else  {
			if (Tmp_KDB1.SOKUTE_SU > 0 ) {
				sBuf = "�r��";//	����r��
			} else {
				sBuf = "��";//	������
			}
		}
		SGr1->Cells[8][SGr1->RowCount - 1] = sBuf;


		sBuf = Tmp_KDB1.KENSA_YMD;
		SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;               //�����N����

		sBuf = Tmp_KDB1.DTKSHIN;
		SGr1->Cells[12][SGr1->RowCount - 1] = sBuf;               //���Ӑ�i��

		sBuf = Tmp_KDB1.HINBAN;
		SGr1->Cells[13][SGr1->RowCount - 1] = sBuf;               //���Еi��

		sBuf = Tmp_KDB1.ZISCOD;
		SGr1->Cells[14][SGr1->RowCount - 1] = sBuf;               //�ގ��R�[�h

		sBuf = Tmp_KDB1.ZISNAM;
		SGr1->Cells[15][SGr1->RowCount - 1] = sBuf;               //�ގ���

		sBuf = Tmp_KDB1.LOTNO;
		SGr1->Cells[16][SGr1->RowCount - 1] = sBuf;               //���b�gNO

		sBuf = IntToStr(Tmp_KDB1.SEQNO);
		SGr1->Cells[17][SGr1->RowCount - 1] = sBuf;               //SEQNO

		sBuf = IntToStr(Tmp_KDB1.KENSA_KMK);
		SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;               //��������

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;               //�H���\�� �K�i

		sBuf = IntToStr(Tmp_KDB1.SOKUTE_SU);
		SGr1->Cells[20][SGr1->RowCount - 1] = sBuf;               //���萔

		sBuf = Tmp_KDB1.ADDYMD;
		SGr1->Cells[21][SGr1->RowCount - 1] = sBuf;               //�o�^��

		sBuf = Tmp_KDB1.ADDTIM;
		SGr1->Cells[22][SGr1->RowCount - 1] = sBuf;               //�o�^����

		sBuf = " ";
		SGr1->Cells[23][SGr1->RowCount - 1] = sBuf;               //�ύX��

		sBuf = " ";
		SGr1->Cells[24][SGr1->RowCount - 1] = sBuf;               //�ύX����

		sBuf = IntToStr(Tmp_KDB1.UPDCHR);
		SGr1->Cells[25][SGr1->RowCount - 1] = sBuf;               //�X�V��

		sBuf = IntToStr(Tmp_KDB1.UPDCNT);
		SGr1->Cells[26][SGr1->RowCount - 1] = sBuf;               //�X�V��

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN1);
		SGr1->Cells[27][SGr1->RowCount - 1] = sBuf;               //�������1

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN2);
		SGr1->Cells[28][SGr1->RowCount - 1] = sBuf;               //�������2

		sBuf = Tmp_KDB1.JYOKEN3;
		SGr1->Cells[29][SGr1->RowCount - 1] = sBuf;               //�������3

        //2002/11/18 E.Takase ����Ғǉ�
		sBuf = Tmp_KDB1.UPDCHR;
		SGr1->Cells[9][SGr1->RowCount - 1] = Form2->GetTANNAM(sBuf);
     // ��s���₷
     SGr1->RowCount = SGr1->RowCount + 1;


     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][SGr1->RowCount-1]  = "";
     }

     // �V�����s��I��
     SGr1->Row = SGr1->RowCount - 1;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;
     SEQNOMAX ++;
//     // �{�^���̏�����
//     BtnF01->Enabled = true;
//     BtnF02->Enabled = true;
//     BtnF03->Enabled = true;
//     BtnF04->Enabled = true;
//     BtnF05->Enabled = true;
//     BtnF06->Enabled = true;
//     BtnF07->Enabled = true;
//     BtnF08->Enabled = true;
//     BtnF09->Enabled = true;
//     BtnF10->Enabled = true;
//     BtnF11->Enabled = true;
//     BtnF12->Enabled = true;

}
//---------------------------------------------------------------------------
//�u�e�X�F�C���v
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
    AnsiString sBuf;
    AnsiString sYMD;


    if( !BtnF09->Enabled )    return;
    sYMD = DelSEPA(EdtYMD->Text);

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�C�����ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();


    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    if ( Cmb1->Text.IsEmpty() ) {
        //Empty�̎��A�X�y�[�X������
        //SBr1->Panels->Items[0]->Text = "�K�{����(�������ځi���{��j)����͂��ĉ������B";
        //SBr1->Update();
        //Cmb1->SetFocus();
        //return;
        Cmb1->Text = "";
        Tmp_KDB1.KOUMOKU_J = " ";

    } else { //�������ځi���{��j
        Tmp_KDB1.KOUMOKU_J = Cmb1->Text;
    }
    //	��������
    if( Trim(EdtKMK->Text) == "" )  Tmp_KDB1.KENSA_KMK	=-1;
	else Tmp_KDB1.KENSA_KMK	= StrToInt(EdtKMK->Text);

    if ( Cmb2->Text.IsEmpty() ) {
        //Empty�̎��A�X�y�[�X������
        //SBr1->Panels->Items[0]->Text = "�K�{����(�������ځi�p��j)����͂��ĉ������B";
        //SBr1->Update();
        //Cmb2->SetFocus();
        //return;
        Cmb2->Text = "";
        Tmp_KDB1.KOUMOKU_E = " ";

    } else { //�������ځi�p��j
        Tmp_KDB1.KOUMOKU_E = Cmb2->Text;
    }
    if ( Edt1->Text.IsEmpty() ) {
        SBr1->Panels->Items[0]->Text = "�K�{���ځi���萔�j����͂��ĉ������B";
        SBr1->Update();
        Edt1->SetFocus();
        return;
    } else { //���萔
        Tmp_KDB1.HIST_SOKUT = StrToInt(Edt1->Text);
    }
    if ( Cmb3->ItemIndex == -1 ) {
        SBr1->Panels->Items[0]->Text = "�K�{���ځi�K�i�j����͂��ĉ������B";
        SBr1->Update();
        Cmb3->SetFocus();
        return;
    } else { //�K�i
        Tmp_KDB1.HIST_KIKAK = Cmb3->ItemIndex + 1;
    }

    //�����l ����l�̔�r
    if ( Tmp_KDB1.HIST_KIKAK == 1 ) {
    	if ( StrToFloat(Edt2->Text) >= StrToFloat(Edt3->Text) ) {
        	SBr1->Panels->Items[0]->Text = "�K�i�l���m�F���ĉ������B";
        	SBr1->Update();
        	Edt2->SetFocus();
        	return;
    	}
    }
    //����l�̃`�F�b�N
    if ( Tmp_KDB1.HIST_KIKAK == 3 ) {
    	if ( StrToFloat(Edt3->Text) <= 0) {
        	SBr1->Panels->Items[0]->Text = "����K�i�l���m�F���ĉ������B";
        	SBr1->Update();
        	Edt3->SetFocus();
        	return;
    	}
    }

    if ( ( !(Edt2->Text.IsEmpty() ) )  &&
            ( Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK== 2  )) // �q�X�g�O���������K�i
         Tmp_KDB1.HIST_MIN = StrToFloat(Edt2->Text);

    if ( ( !(Edt3->Text.IsEmpty() ) )  &&
            ( Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK== 3  ))// �q�X�g�O��������K�i
         Tmp_KDB1.HIST_MAX = StrToFloat(Edt3->Text);

    //�`��敪
    if ( EdtKEIJKBN->Text == "" ) Tmp_KDB1.KEIJKBN = 0;
    else Tmp_KDB1.KEIJKBN = StrToInt( EdtKEIJKBN->Text );

    //�P��
    //Check
    if ( (CheckTANI( Tmp_KDB1.KENSA_KMK, Cmb5->Text )) == 0 ) {
    //�P�� �Ԉ���Ă���
        SBr1->Panels->Items[0]->Text = "�P�ʂ��Ԉ���Ă��܂��B";
        SBr1->Update();
        Cmb5->SetFocus();
        return;
    }
    Tmp_KDB1.TANI = Cmb5->Text;

    // �X�V��
    Tmp_KDB1.UPDYMD = FormatDateTime("yyyymmdd",Date());
    // �X�V����
    Tmp_KDB1.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // �X�V��
    if( SGr1->Cells[26][SGr1->Row] == "" ){
        Tmp_KDB1.UPDCNT  = 0;
    }
    else{
       Tmp_KDB1.UPDCNT  = StrToInt(SGr1->Cells[26][SGr1->Row]);
       Tmp_KDB1.UPDCNT += 1 ;                  // �X�V��
    }
    // �X�V��
    Tmp_KDB1.UPDCHR  = USER_COD;
    // �����
    Tmp_KDB1.KENSA_YMD  = sYMD;

    // ���Ӑ�i��
    if( EdtHIN->Text.IsEmpty() ) Tmp_KDB1.DTKSHIN = " ";
    Tmp_KDB1.DTKSHIN  = EdtHIN->Text;
    // �ގ��R�[�h
    Tmp_KDB1.ZISCOD  = EdtZIS->Text;
    if( Tmp_KDB1.ZISCOD.IsEmpty() ) Tmp_KDB1.ZISCOD = " ";
    //�ގ���
    Tmp_KDB1.ZISNAM = EdtZISNAM->Caption;
    if( Tmp_KDB1.ZISNAM.IsEmpty() ) Tmp_KDB1.ZISNAM = " ";
    // �������
    Tmp_KDB1.JYOKEN1  = StrToFloat(EdtJYOKEN1->Text);
    Tmp_KDB1.JYOKEN2  = StrToFloat(EdtJYOKEN2->Text);
    Tmp_KDB1.JYOKEN3  = EdtJYOKEN3->Text;

    //���Еi��
    Tmp_KDB1.HINBAN = KM02.HINBAN;
    // ���b�gNo
    Tmp_KDB1.LOTNO  = EdtLOT->Text;
    // SEQNO
    Tmp_KDB1.SEQNO  = StrToInt(SGr1->Cells[17][SGr1->Row]);
    // ���萔
    Tmp_KDB1.SOKUTE_SU  = StrToInt(SGr1->Cells[20][SGr1->Row]);


    
     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row]) == False ){
        return;
     }

     // �f�[�^��ύX�����t���O
     DataSave = true;

        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
        sBuf = SGr1->Row+1;
		SGr1->Cells[0][SGr1->Row] = AnsiString::StringOfChar(' ', 5-sBuf.Length()) + sBuf;    //No

		sBuf = Tmp_KDB1.KOUMOKU_J;
		SGr1->Cells[1][SGr1->Row] = sBuf;   //�������ځi���{��j

		sBuf = Tmp_KDB1.KOUMOKU_E;
		SGr1->Cells[2][SGr1->Row] = sBuf;   //�������ځi�p��j

		sBuf = IntToStr(Tmp_KDB1.HIST_SOKUT);
		SGr1->Cells[4][SGr1->Row] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;   //���萔

		sBuf = Tmp_KDB1.TANI;
		SGr1->Cells[3][SGr1->Row] = sBuf;   //�P��

		sBuf = IntToStr(Tmp_KDB1.KEIJKBN);
		SGr1->Cells[11][SGr1->Row] = sBuf;   //�`��敪
        switch(Tmp_KDB1.KEIJKBN)
        {
			case 1: //������
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->Row] = "������";
                SGr1->Cells[30][SGr1->Row] = "������";
                break;
            case 2: //�~��
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->Row] = "�~��";
                SGr1->Cells[30][SGr1->Row] = "�~��";
                break;
            case 3: //�R���~ 2002/11/14 E.Takase
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->Row] = "�R���~";
                SGr1->Cells[30][SGr1->Row] = "�R���~";
                break;
            default:
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->Row] = " ";
                SGr1->Cells[30][SGr1->Row] = " ";
                break;

        }
		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		switch(StrToInt(sBuf))   //�K�i��
		{
			case 1:
				SGr1->Cells[5][SGr1->Row] = "����";

				//�����K�i
                SGr1->Cells[6][SGr1->Row] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //����K�i
                SGr1->Cells[7][SGr1->Row] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

			case 2:
				SGr1->Cells[5][SGr1->Row] = "����";

				//�����K�i
                SGr1->Cells[6][SGr1->Row] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MIN, Tmp_KDB1.TANI);
                //����K�i
                SGr1->Cells[7][SGr1->Row] = " ";

				break;

			case 3:
				SGr1->Cells[5][SGr1->Row] = "���";

                //�����K�i
				SGr1->Cells[6][SGr1->Row] = " ";

                //����K�i
                SGr1->Cells[7][SGr1->Row] = KENSASGr_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1 , Tmp_KDB1.HIST_MAX, Tmp_KDB1.TANI);

				break;

		}
		if ( Tmp_KDB1.HIST_SOKUT == Tmp_KDB1.SOKUTE_SU ) {
			sBuf = "��";//	�����
		} else  {
			if (Tmp_KDB1.SOKUTE_SU > 0 ) {
				sBuf = "�r��";//	����r��
			} else {
				sBuf = "��";//	������
			}
		}
		SGr1->Cells[8][SGr1->Row] = sBuf;


		sBuf = Tmp_KDB1.KENSA_YMD;
		SGr1->Cells[10][SGr1->Row] = sBuf;                //�����N����

		sBuf = Tmp_KDB1.DTKSHIN;
		SGr1->Cells[12][SGr1->Row] = sBuf;                //���Ӑ�i��

		sBuf = Tmp_KDB1.HINBAN;
		SGr1->Cells[13][SGr1->Row] = sBuf;               //���Еi��

		sBuf = Tmp_KDB1.ZISCOD;
		SGr1->Cells[14][SGr1->Row] = sBuf;               //�ގ��R�[�h

		sBuf = Tmp_KDB1.ZISNAM;
		SGr1->Cells[15][SGr1->Row] = sBuf;               //�ގ���

		sBuf = Tmp_KDB1.LOTNO;
		SGr1->Cells[16][SGr1->Row] = sBuf;               //���b�gNO

		sBuf = IntToStr(Tmp_KDB1.SEQNO);
		SGr1->Cells[17][SGr1->Row] = sBuf;               //SEQNO

		sBuf = IntToStr(Tmp_KDB1.KENSA_KMK);
		SGr1->Cells[18][SGr1->Row] = sBuf;               //��������

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		SGr1->Cells[19][SGr1->Row] = sBuf;               //�H���\�� �K�i

		sBuf = IntToStr(Tmp_KDB1.SOKUTE_SU);
		SGr1->Cells[20][SGr1->Row] = sBuf;               //���萔

		//sBuf = Tmp_KDB1.ADDYMD;
		//SGr1->Cells[21][SGr1->Row] = sBuf;               //�o�^��

		//sBuf = Tmp_KDB1.ADDTIM;
		//SGr1->Cells[22][SGr1->Row] = sBuf;               //�o�^����

		sBuf = Tmp_KDB1.UPDYMD;
		SGr1->Cells[23][SGr1->Row] = sBuf;               //�ύX��

		sBuf = Tmp_KDB1.UPDTIM;
		SGr1->Cells[24][SGr1->Row] = sBuf;               //�ύX����

		sBuf = IntToStr(Tmp_KDB1.UPDCHR);
		SGr1->Cells[25][SGr1->Row] = sBuf;               //�X�V��

		sBuf = IntToStr(Tmp_KDB1.UPDCNT);
		SGr1->Cells[26][SGr1->Row] = sBuf;               //�X�V��

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN1);
		SGr1->Cells[27][SGr1->Row] = sBuf;               //�������1

		sBuf = FloatToStr(Tmp_KDB1.JYOKEN2);
		SGr1->Cells[28][SGr1->Row] = sBuf;               //�������2

		sBuf = Tmp_KDB1.JYOKEN3;
		SGr1->Cells[29][SGr1->Row] = sBuf;               //�������2

        //2002/11/18 E.Takase ����Ғǉ�
		sBuf = Tmp_KDB1.UPDCHR;
		SGr1->Cells[9][SGr1->RowCount - 1] = Form2->GetTANNAM(sBuf);

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();


}
//---------------------------------------------------------------------------
//�u�e�P�O�F�폜�v
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
    int i;

    if( !BtnF10->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�폜�Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�폜���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

     // �f�[�^���o�b�t�@�Ɋi�[���܂��B
     //�����
     Tmp_KDB1.KENSA_YMD  = SGr1->Cells[10][SGr1->Row];
     //���Ӑ�i��
     Tmp_KDB1.DTKSHIN  = EdtHIN->Text;
     //SEQNO
     Tmp_KDB1.SEQNO  = StrToInt(SGr1->Cells[17][SGr1->Row]);
     //LOTNO
     Tmp_KDB1.LOTNO  = SGr1->Cells[16][SGr1->Row];


     // DelData
     if( DelData() == False ){
        return;
     }

     for( i = SGr1->Row; i < (SGr1->RowCount - 1); i++) {
         // �O���b�h�̈�s���폜���܂��B
         SGr1->Cells[1][i] = SGr1->Cells[1][i+1];
         SGr1->Cells[2][i] = SGr1->Cells[2][i+1];
         SGr1->Cells[3][i] = SGr1->Cells[3][i+1];
         SGr1->Cells[4][i] = SGr1->Cells[4][i+1];
         SGr1->Cells[5][i] = SGr1->Cells[5][i+1];
         SGr1->Cells[6][i] = SGr1->Cells[6][i+1];
         SGr1->Cells[7][i] = SGr1->Cells[7][i+1];
         SGr1->Cells[8][i] = SGr1->Cells[8][i+1];
         SGr1->Cells[9][i] = SGr1->Cells[9][i+1];
         SGr1->Cells[10][i] = SGr1->Cells[10][i+1];
         SGr1->Cells[11][i] = SGr1->Cells[11][i+1];
         SGr1->Cells[12][i] = SGr1->Cells[12][i+1];
         SGr1->Cells[13][i] = SGr1->Cells[13][i+1];
         SGr1->Cells[14][i] = SGr1->Cells[14][i+1];
         SGr1->Cells[15][i] = SGr1->Cells[15][i+1];
         SGr1->Cells[16][i] = SGr1->Cells[16][i+1];
         SGr1->Cells[17][i] = SGr1->Cells[17][i+1];
         SGr1->Cells[18][i] = SGr1->Cells[18][i+1];
         SGr1->Cells[19][i] = SGr1->Cells[19][i+1];
         SGr1->Cells[20][i] = SGr1->Cells[20][i+1];
         SGr1->Cells[21][i] = SGr1->Cells[21][i+1];
         SGr1->Cells[22][i] = SGr1->Cells[22][i+1];
         SGr1->Cells[23][i] = SGr1->Cells[23][i+1];
         SGr1->Cells[24][i] = SGr1->Cells[24][i+1];
         SGr1->Cells[25][i] = SGr1->Cells[25][i+1];
         SGr1->Cells[26][i] = SGr1->Cells[26][i+1];
         SGr1->Cells[27][i] = SGr1->Cells[27][i+1];
         SGr1->Cells[28][i] = SGr1->Cells[28][i+1];
         SGr1->Cells[29][i] = SGr1->Cells[29][i+1];
         SGr1->Cells[30][i] = SGr1->Cells[30][i+1];
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
//�u�e�P�P�F�ۑ��v
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
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
//�u�e�P�Q�F�I���v
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------
//�I�����Ă���s�̃f�[�^��\��
void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
	int CmbNo;

    //No
    PnlNO->Caption = SGr1->Cells[0][ARow];

    //�������ځi���{��j
    if ( Trim(SGr1->Cells[1][ARow]) != "" &&  Trim(SGr1->Cells[18][ARow]) != "" &&  Trim(SGr1->Cells[27][ARow]) != "") {
    	//CmbNo = KENSACmb_Set(StrToInt(SGr1->Cells[18][ARow]),StrToInt(SGr1->Cells[27][ARow]));
    	CmbNo = KENSACmb_Set(StrToInt(SGr1->Cells[18][ARow]),StrToFloat(SGr1->Cells[27][ARow]));
    } else {
    	CmbNo = KENSACmb_Set(12,0);
    	CmbNo = 12;
    }

    if ( Trim(SGr1->Cells[1][ARow]) == "" ) {
        Cmb1->ItemIndex = -1;
        Cmb1->Text = " ";
    }
    else {
        if ( CmbNo == 12 ) {
        	Cmb1->ItemIndex = Cmb1->Items->IndexOf( SGr1->Cells[1][ARow] );
            if ( Cmb1->ItemIndex == -1 ) {
            	Cmb1->Text = SGr1->Cells[1][ARow];
            }
        } else {
        	Cmb1->ItemIndex = CmbNo;
        }
    	//Cmb1->ItemIndex = KENSACmb_Set(StrToInt(SGr1->Cells[18][ARow]),StrToInt(SGr1->Cells[27][ARow]));
        //if ( StrToInt(SGr1->Cells[18][ARow]) == 10 )  {
        //    Cmb1->ItemIndex = 12;
        //    Cmb1->Text = SGr1->Cells[1][ARow];
        //}
    }
    //�������ځi�p��j
    if ( Trim(SGr1->Cells[2][ARow]) == "" ) {
        Cmb2->ItemIndex = -1;
        Cmb2->Text = " ";
    }
    else {
        if ( CmbNo == 12 ) {
        	Cmb2->ItemIndex = Cmb2->Items->IndexOf( SGr1->Cells[2][ARow] );
            if ( Cmb2->ItemIndex == -1 ) {
            	Cmb2->Text = SGr1->Cells[2][ARow];
            }
        } else {
        	Cmb2->ItemIndex = CmbNo;
        }

    	//Cmb2->ItemIndex = KENSACmb_Set(StrToInt(SGr1->Cells[18][ARow]),StrToInt(SGr1->Cells[27][ARow]));
        //if ( StrToInt(SGr1->Cells[18][ARow]) == 10 )  {
        //    Cmb2->ItemIndex = 12;
        //    Cmb2->Text = SGr1->Cells[2][ARow];
        //}

    }
    //��������
    EdtKMK->Text = SGr1->Cells[18][ARow];


    //�`��敪
    //if ( Trim(SGr1->Cells[11][ARow]) == "" ) Cmb4->ItemIndex = -1;
    //else   Cmb4->ItemIndex = StrToInt(SGr1->Cells[11][ARow])-1;
    EdtKEIJKBN->Text = SGr1->Cells[11][ARow];

    //������� EdtJYOKEN
    EdtJYOKEN1->Text = SGr1->Cells[27][ARow];
    EdtJYOKEN2->Text = SGr1->Cells[28][ARow];
    EdtJYOKEN3->Text = SGr1->Cells[29][ARow];

    //�P��
    if ( Trim( EdtKMK->Text ) == ""  )  SetTANI(10);
    else SetTANI( StrToInt( EdtKMK->Text ));
    Cmb5->Text = SGr1->Cells[3][ARow];

    //���萔
    Edt1->Text = SGr1->Cells[4][ARow];
    if( Trim(SGr1->Cells[20][ARow]) != "" ){
        if ( (StrToInt(SGr1->Cells[20][ARow])) == 0 ) {
           //���� �� �g�p��
           Edt1->Enabled = true;
        } else {
           //���� �� OR �r�� �g�p�s��
           Edt1->Enabled = false;
        }
    }else{
        //���� �� �g�p��
        Edt1->Enabled = true;
    }

    //		�@�V�@�@�@�@�K�i
    if ( Trim(SGr1->Cells[5][ARow]) == "" ) Cmb3->ItemIndex = -1;
    else Cmb3->ItemIndex = StrToInt(SGr1->Cells[19][ARow])-1;


    //	�@�V�@�@�@�@�����K�i
    if ( Trim( SGr1->Cells[6][ARow] ) != "" ) {
        Edt2->Enabled = true;
        Edt2->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[6][ARow]));
    }
    else {
        Edt2->Text = "";
        Edt2->Enabled = false;
    }

    //	�@�V�@�@�@�@����K�i
    if ( Trim( SGr1->Cells[7][ARow] ) != "" ) {
        Edt3->Enabled = true;
        Edt3->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[7][ARow]));
    }
    else {
        Edt3->Text = "";
        Edt3->Enabled = false;
    }

    //2002/11/18 E.Takase
    //�����
    if ( Trim( SGr1->Cells[9][ARow] ) != "" ) {
        Edt4->Text = SGr1->Cells[9][ARow];
    }
    else {
        Edt4->Text = "";
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    AnsiString sBuf;
    int tmp;
     // �X�e�[�^�X���b�Z�[�W
     if(SBr1->Panels->Items[0]->Text != ""){
        SBr1->Panels->Items[0]->Text = "";
        SBr1->Update();
     }

    if( Shift.Contains(ssCtrl) ){
        BtnF01->Caption = "˽Ēǉ�";
        BtnF02->Caption = "";
        BtnF03->Caption = "";
        BtnF04->Caption = "";
        BtnF05->Caption = "";
        BtnF06->Caption = "";
        BtnF07->Caption = "";
        BtnF08->Caption = "";
        BtnF09->Caption = "";
        BtnF10->Caption = "";
        BtnF11->Caption = "";
        BtnF12->Caption = "�߂�";

        if( !(NotFound) || ( Trim(DelSEPA(EdtYMD->Text)) != "" && EdtHIN->Text != ""  && EdtLOT->Text != "")){
            BtnF01->Enabled = true;
            BtnF02->Enabled = false;
            BtnF03->Enabled = false;
            BtnF04->Enabled = true;
            BtnF05->Enabled = false;
            BtnF06->Enabled = true;
            BtnF07->Enabled = true;
            BtnF08->Enabled = true;
            BtnF09->Enabled = true;
            BtnF10->Enabled = true;
            BtnF11->Enabled = true;
            BtnF12->Enabled = true;
        }
        else{
            BtnF01->Enabled = false;
            BtnF02->Enabled = false;
            BtnF03->Enabled = false;
            BtnF04->Enabled = false;
            BtnF05->Enabled = false;
            BtnF06->Enabled = false;
            BtnF07->Enabled = false;
            BtnF08->Enabled = false;
            BtnF09->Enabled = false;
            BtnF10->Enabled = false;
            BtnF11->Enabled = false;
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

     switch(Key)
     {
         case VK_F1:  BtnF01Click(Sender);    Key = 0; break;
         case VK_F2:  BtnF02Click(Sender);    Key = 0; break;
         case VK_F3:  BtnF03Click(Sender);    Key = 0; break;
         case VK_F4:  BtnF04Click(Sender);    Key = 0; break;
         case VK_F5:  BtnF05Click(Sender);    Key = 0; break;
         case VK_F6:  BtnF06Click(Sender);    Key = 0; break;
         case VK_F7:  BtnF07Click(Sender);    Key = 0; break;
         case VK_F8:  BtnF08Click(Sender);    Key = 0; break;
         case VK_F9:  BtnF09Click(Sender);    Key = 0; break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    Key = 0; break;
         case VK_F12: BtnF12Click(Sender);    Key = 0; break;


         // �O��
         case VK_UP:
         case VK_LEFT:
                if(EdtYMD->Focused() && EdtYMD->SelStart == 0 && EdtYMD->SelLength == 0){
                    //KENSAKU_Mode = 3; BtnF01->Enabled = true;
                    EdtLOT->SetFocus();
                    break;
                }
                if(EdtHIN->Focused() && EdtHIN->SelStart == 0 && EdtHIN->SelLength == 0){
                    //KENSAKU_Mode = 1; BtnF01->Enabled = true;
                    EdtYMD->SetFocus();
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == 0 && EdtLOT->SelLength == 0){
                    //KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    EdtHIN->SetFocus();
                    break;
                }
                //�������� ���{��
                if(Cmb1->Focused() && Cmb1->SelStart == 0 && Cmb1->SelLength == 0 ){
                    if ( Key == VK_LEFT ){
                        //Cmb4->SetFocus();
                        //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                        if ( Edt3->Enabled == true )  Edt3->SetFocus();
                        else if ( Edt2->Enabled == true )  Edt2->SetFocus();
                            else Cmb3->SetFocus();
                    }
                    break;
                }
//                if (Cmb1->Focused() && Key == VK_UP
//                   && ( EdtKMK->Text == "10" || Cmb1->ItemIndex == -1 || Cmb1->ItemIndex >=10 ) )  {
//                    Cmb1->ItemIndex = 9;
//                    break;
//                }
				//�������� �p��
                if(Cmb2->Focused() && Cmb2->SelStart == 0 && Cmb2->SelLength == 0 ) {
                    if ( Key == VK_LEFT ){
                        //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                        Cmb1->SetFocus();
                    }
                    break;
                }
//                if (Cmb2->Focused() && Key == VK_UP
//                   && ( EdtKMK->Text == "10" || Cmb2->ItemIndex == -1 || Cmb2->ItemIndex >=10 ) )  {
//                    Cmb2->ItemIndex = 9;
//                    break;
//                }
                //�P��
                if(Cmb5->Focused() && Cmb5->SelStart == 0 && Cmb5->SelLength == 0 ) {
                    //if ( Key == VK_LEFT ){
                    //    Cmb4->SetFocus();
                    //}
                    //if ( Key == VK_UP
                    //     && ( Cmb2->ItemIndex == -1 || EdtKMK->Text == "10" ))  {
                    //    Cmb4->ItemIndex = 9;
                    //}

                    if ( Key == VK_LEFT ){
                        Cmb2->SetFocus();
                    }
                    if ( Key == VK_UP
                         && ( Cmb2->ItemIndex == -1  || EdtKMK->Text == "10" ) )  {
                        Cmb5->ItemIndex = 9;
                    }

                    break;
                }
                //���萔
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb5->SetFocus();
                    break;
                }
                //�K�i ���� ���� ���
                if(Cmb3->Focused() && Cmb3->SelStart == 0 && Cmb3->SelLength == 0 && Key == VK_LEFT  ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Edt1->SetFocus(); BtnF01->Enabled = false;
                    break;
                }
                //�����l
                if(Edt2->Focused() && Edt2->SelStart == 0 && Edt2->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb3->SetFocus();
                    break;
                }
                //����l
                if(Edt3->Focused() && Edt3->SelStart == 0 && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    if ( Edt2->Enabled == true )  Edt2->SetFocus();
                    else if ( Edt3->Enabled == true )  Edt3->SetFocus();
                        else Cmb3->SetFocus();
                    break;
                }

				////�`��敪
                //if(Cmb4->Focused() && Cmb4->SelStart == 0 && Cmb4->SelLength == 0 ) {
                //
                //    if ( Key == VK_LEFT ){
                //        //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                //        if ( Edt3->Enabled == true )  Edt3->SetFocus();
                //        else if ( Edt2->Enabled == true )  Edt2->SetFocus();
                //            else Cmb3->SetFocus();
                //    }
                //    break;
                //}
                break;

         // ����
         case VK_DOWN:
         case VK_RIGHT:
                if(EdtYMD->Focused() && EdtYMD->SelStart == EdtYMD->Text.Length()  && EdtYMD->SelLength == 0){
                    //KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    EdtHIN->SetFocus();
                    break;
                }
                if(EdtHIN->Focused() && EdtHIN->SelStart == EdtHIN->Text.Length()  && EdtHIN->SelLength == 0){
                    //KENSAKU_Mode = 3; BtnF01->Enabled = true;
                    //���Ӑ�i�Ԃ��琻�i�K�i�����߂�
                    tmp = DTKSHIN_Serch(); //����̋K�i�l������
					EdtZIS->Text = KM02.ZISCOD;
					EdtZISNAM->Caption = KM02.ZISNAM;
					KEIJKBN_KM02 = KM02.KEIJKBN;
					LD_HP_TAN_KM02 = KM02.LD_HP_TAN;
					MAGE_TAN_KM02 = KM02.MAGE_TAN;
                    EdtLOT->SetFocus();
                    break;
                }
                if(EdtLOT->Focused() && EdtLOT->SelStart == EdtLOT->Text.Length()  && EdtLOT->SelLength == 0){
                    //KENSAKU_Mode = 1; BtnF01->Enabled = true;
                    EdtYMD->SetFocus();
                    break;
                }

                if(Cmb1->Focused() && Cmb1->SelStart == Cmb1->Text.Length() && Cmb1->SelLength == 0  && Key == VK_RIGHT ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb2->SetFocus();
                    break;
                }

                if(Cmb2->Focused() && Cmb2->SelStart == Cmb2->Text.Length() && Cmb2->SelLength == 0 && Key == VK_RIGHT  ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb5->SetFocus();
                    break;
                }


                if(Cmb5->Focused() && Cmb5->SelStart == Cmb5->Text.Length() && Cmb5->SelLength == 0 && Key == VK_RIGHT  ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Edt1->SetFocus();
                    break;
                }

                if(Edt1->Focused() && Edt1->SelStart == Edt1->Text.Length() && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb3->SetFocus();
                    break;
                }
                if(Cmb3->Focused() && Cmb3->SelStart == Cmb3->Text.Length() && Cmb3->SelLength == 0 && Key == VK_RIGHT  ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    if ( Edt2->Enabled == true )  Edt2->SetFocus();
                    else  if ( Edt3->Enabled == true )  Edt3->SetFocus();
                        else Cmb1->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == Edt2->Text.Length() && Edt2->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    if ( Edt3->Enabled == true )  Edt3->SetFocus();
                    else Cmb1->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == Edt3->Text.Length() && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                //if(Cmb4->Focused() && Cmb4->SelStart == Cmb4->Text.Length() && Cmb4->SelLength == 0 && Key == VK_RIGHT  ){
                //    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                //    Cmb1->SetFocus();
                //    break;
                //}
                break;


         // Enter
         case VK_RETURN:
                if(EdtYMD->Focused() && !(EdtYMD->Text.IsEmpty())){
                //if(EdtYMD->Focused() && (EdtYMD->Text != "    /  /  ")){
                    //KENSAKU_Mode = 2; BtnF01->Enabled = true;
                    EdtHIN->SetFocus();
                    break;
                }

                if(EdtHIN->Focused() && !(EdtHIN->Text.IsEmpty())){
                    //���Ӑ�i�Ԃ��琻�i�K�i�����߂�
                    tmp = DTKSHIN_Serch(); //����̋K�i�l������
                    if ( tmp == 0 ) {
                    //�������� 0
                    // �X�e�[�^�X���b�Z�[�W
                    	EdtHIN->SelStart = 0;
                        EdtHIN->SelLength = EdtHIN->Text.Length();
        				SBr1->Panels->Items[0]->Text = "���i�K�i�}�X�^�ɓo�^����Ă��܂���B";
        				SBr1->Update();
                    } else {
						EdtZIS->Text = KM02.ZISCOD;
						EdtZISNAM->Caption = KM02.ZISNAM;
						KEIJKBN_KM02 = KM02.KEIJKBN;
						LD_HP_TAN_KM02 = KM02.LD_HP_TAN;
						MAGE_TAN_KM02 = KM02.MAGE_TAN;
                    	EdtLOT->SetFocus();
                    }
                    break;
                }

                //if(EdtLOT->Focused() && !(EdtLOT->Text.IsEmpty())){
                if(EdtLOT->Focused()){
                    ////KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    BtnF07Click(Sender);
                    //EdtYMD->SetFocus();
                    break;
                }

                if(Cmb1->Focused()){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb2->SetFocus();
                    break;
                }
                if(Cmb2->Focused()){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb5->SetFocus();
                    break;
                }
                if(Cmb5->Focused()){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Edt1->SetFocus();
                    break;
                }
                if(Edt1->Focused() ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb3->SetFocus();
                    break;
                }
                if(Cmb3->Focused() ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    if ( Edt2->Enabled == true ) Edt2->SetFocus();
                    else if ( Edt3->Enabled == true ) Edt3->SetFocus();
                        else Cmb1->SetFocus();
                    break;
                }
                if(Edt2->Focused() ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    if ( Edt3->Enabled == true ) Edt3->SetFocus();
                    else Cmb1->SetFocus();
                    break;
                }
                if(Edt3->Focused() ){
                    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                //if(Cmb4->Focused()){
                //    //KENSAKU_Mode = -1; BtnF01->Enabled = false;
                //    Cmb1->SetFocus();
                //    break;
                //}
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
         case VK_RETURN:Cmb1->SetFocus();
                        KENSAKU_Mode = -1;
                        BtnF01->Enabled = false;      break;
     }

}
//---------------------------------------------------------------------------
//�K�i �ύX��
void __fastcall TForm1::Cmb3Change(TObject *Sender)
{
    switch( Cmb3->ItemIndex){
        case 0: //0 ����
            Edt2->Enabled = true;
            Edt3->Enabled = true;
            break;
        case 1: //0 ����
            Edt2->Enabled = true;
            Edt3->Text = "0";
            Edt3->Enabled = false;
            break;
        case 2: //0 ���
            Edt2->Text = "0";
            Edt2->Enabled = false;
            Edt3->Enabled = true;
            break;
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
        if( Database1->InTransaction == True )  Database1->Rollback();
    }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Cmb1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if ( EdtKMK->Text != "10" ) {
        if ( Cmb1->ItemIndex == -1 || Cmb1->ItemIndex == 10 ) {
            EdtKMK->Text = "10";
            if ( Cmb2->ItemIndex != -1 ) {
                Cmb2->ItemIndex = 10;
                Cmb2->Text = " ";
            }
        }else {
            EdtKMK->Text = Cmb1->ItemIndex;
            Cmb2->ItemIndex = Cmb1->ItemIndex;
            //if ( Cmb1->ItemIndex != -1 ||  (Cmb1->Text.IsEmpty()) )
        }
    } else {
        //if ((Cmb1->ItemIndex == -1 || Cmb1->ItemIndex == 10) &&  (Cmb2->Text.IsEmpty()) ) {
        if ((Cmb1->ItemIndex != -1 && Cmb1->ItemIndex != 10)  ) {
            EdtKMK->Text = Cmb1->ItemIndex;
            Cmb2->ItemIndex = Cmb1->ItemIndex;
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Cmb2KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if ( EdtKMK->Text != "10" ) {
        if ( Cmb2->ItemIndex == -1 || Cmb2->ItemIndex == 10 ) {
            EdtKMK->Text = "10";
            if ( Cmb1->ItemIndex != -1 ) {
                Cmb1->ItemIndex = 10;
                Cmb1->Text = " ";
            }

        }else {
            EdtKMK->Text = Cmb2->ItemIndex;
            Cmb1->ItemIndex = Cmb2->ItemIndex;
        }
    }
    else {
        //if (( Cmb2->ItemIndex != -1 || Cmb2->ItemIndex != 10) && (Cmb1->Text.IsEmpty()) ) {
        if (( Cmb2->ItemIndex != -1 && Cmb2->ItemIndex != 10) ) {
            EdtKMK->Text = Cmb2->ItemIndex;
            Cmb1->ItemIndex = Cmb2->ItemIndex;
        }
    }
    
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtYMD->Focused()){
        KENSAKU_Mode = 1; BtnF01->Enabled = true;
        return;
    }
    if(EdtHIN->Focused()){
        KENSAKU_Mode = 2; BtnF01->Enabled = true;
        return;
    }
//    if(EdtLOT->Focused()){
//        KENSAKU_Mode = 3; BtnF01->Enabled = true;
//        return;
//    }

    KENSAKU_Mode = -1; BtnF01->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtHINExit(TObject *Sender)
{
/*	AnsiString sBuf;
	//�ގ��R�[�h ����

	//���Ӑ�i�Ԃ��琻�i�K�i�����߂�
	DTKSHIN_Serch(); //����̋K�i�l������

	EdtZIS->Text = KM02.ZISCOD;
	EdtZISNAM->Caption = KM02.ZISNAM;
	KEIJKBN_KM02 = KM02.KEIJKBN;
	LD_HP_TAN_KM02 = KM02.LD_HP_TAN;
	MAGE_TAN_KM02 = KM02.MAGE_TAN;


    //�`��敪������  KEIJKBN_KM02
	    Query1->Close();
	    Query1->SQL->Clear();

	    sBuf = "SELECT ZISNAM, ZISCOD, KEIJKBN, LD_HP_TAN, MAGE_TAN FROM KM02";
	    sBuf += " WHERE KM02.DTKSHIN = '" + EdtHIN->Text + "'";

	    //�₢���������s
	    Query1->SQL->Add(sBuf);
	    Query1->Open();
	    Query1->Active = true;
	    if ( Query1->Bof == true && Query1->Eof == true) {
	    }else {
	        Query1->First();
	        EdtZISNAM->Text = Query1->Fields->Fields[0]->AsString;
	        EdtZIS->Caption = Query1->Fields->Fields[1]->AsString;
            KEIJKBN_KM02 = StrToInt(Query1->Fields->Fields[2]->AsString);
            LD_HP_TAN_KM02 = StrToInt(Query1->Fields->Fields[3]->AsString);
            MAGE_TAN_KM02 = StrToInt(Query1->Fields->Fields[4]->AsString);

	    }

*/
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Cmb1Change(TObject *Sender)
{
    if ( EdtKMK->Text != "10" ) {
        if ( Cmb1->Items->IndexOf( Cmb1->Text ) == -1
                           || Cmb1->Items->IndexOf( Cmb1->Text )>= 12 ) {
            //EdtKMK->Text = "9";
            if ( Cmb2->Items->IndexOf( Cmb2->Text ) != -1
                           || Cmb2->Items->IndexOf( Cmb2->Text )>= 12 ) {
                if ( Cmb1->Items->IndexOf( Cmb1->Text )>= 12 ) {
                  Cmb2->ItemIndex = Cmb1->Items->IndexOf( Cmb1->Text );
                  //Cmb2->Text = Cmb1->Text;
                } else {
                  Cmb2->ItemIndex = 12;
                  Cmb2->Text = " ";
                }
            } else {
            	Cmb2->ItemIndex = Cmb1->Items->IndexOf( Cmb1->Text );
            }
        }else {
            //EdtKMK->Text = Cmb1->ItemIndex;
            Cmb2->ItemIndex = Cmb1->ItemIndex;
            //if ( Cmb1->ItemIndex != -1 ||  (Cmb1->Text.IsEmpty()) )
        }
    } else {
//        if ((Cmb1->ItemIndex != -1 && Cmb1->ItemIndex != 10)  ) {
        if ( Cmb1->Items->IndexOf( Cmb1->Text ) != -1
                           && Cmb1->Items->IndexOf( Cmb1->Text )< 12 ) {
            //EdtKMK->Text = Cmb1->ItemIndex;
            Cmb2->ItemIndex = Cmb1->ItemIndex;
        }
        if ( Cmb1->Items->IndexOf( Cmb1->Text )>= 12 ) {
           Cmb2->ItemIndex = Cmb1->Items->IndexOf( Cmb1->Text );
           //Cmb2->Text = Cmb1->Text;
        }

    }

    //�������� �Q�F�u���V���i�c�j�� ���ԂɂȂ����̂ŏC��
    //if ( StrToInt( EdtKMK->Text ) >= 2 ) EdtKMK->Text = IntToStr( StrToInt( EdtKMK->Text ) + 1 );
    //KENSAKMK_Set(Cmb1->ItemIndex);
    KENSAKMK_Set(Cmb1->Items->IndexOf( Cmb1->Text ));
    //SetTANI( StrToInt( EdtKMK->Text ));

    //Cmb5->ItemIndex = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Cmb2Change(TObject *Sender)
{
    if ( EdtKMK->Text != "10" ) {
        if (Cmb2->Items->IndexOf( Cmb2->Text ) == -1
                           || Cmb2->Items->IndexOf( Cmb2->Text )>= 12 ) {
            //EdtKMK->Text = "9";
//            if ( Cmb1->ItemIndex != -1 ) {
            if ( Cmb1->Items->IndexOf( Cmb1->Text ) != -1
                           || Cmb1->Items->IndexOf( Cmb1->Text )>= 12 ) {
                if ( Cmb2->Items->IndexOf( Cmb2->Text )>= 12 ) {
                  Cmb1->ItemIndex = Cmb2->ItemIndex;
                  //Cmb1->Text = Cmb2->Text;
                } else {
                  Cmb1->ItemIndex = 12;
                  Cmb1->Text = " ";
                }
            } else {
            	Cmb1->ItemIndex = Cmb2->Items->IndexOf( Cmb2->Text );
            }

        }else {
            //EdtKMK->Text = Cmb2->ItemIndex;
            Cmb1->ItemIndex = Cmb2->ItemIndex;
        }
    }
    else {
//        if (( Cmb2->ItemIndex != -1 && Cmb2->ItemIndex != 10) ) {
        if ( Cmb2->Items->IndexOf( Cmb2->Text ) != -1
                           && Cmb2->Items->IndexOf( Cmb2->Text )< 12 ) {
            //EdtKMK->Text = Cmb2->ItemIndex;
            Cmb1->ItemIndex = Cmb2->ItemIndex;
        }
        if ( Cmb2->Items->IndexOf( Cmb2->Text )>= 12 ) {
           Cmb1->ItemIndex = Cmb2->ItemIndex;
           //Cmb1->Text = Cmb2->Text;
        }

    }
    //�������� �Q�F�u���V���i�c�j�� ���ԂɂȂ����̂ŏC��
    //if ( StrToInt( EdtKMK->Text ) >= 2 ) EdtKMK->Text = IntToStr( StrToInt( EdtKMK->Text ) + 1 );
	//KENSAKMK_Set(Cmb2->ItemIndex);
	KENSAKMK_Set(Cmb2->Items->IndexOf( Cmb2->Text ));

    //SetTANI( StrToInt( EdtKMK->Text ));
    //Cmb5->ItemIndex = 0;

}
//�������ڂ����̑��̂Ƃ��P�ʂɂ���Čv���@�팈�肷��
void __fastcall TForm1::Cmb5Change(TObject *Sender)
{
//mm 0      -> �m�M�X(2)
//Kgf,N 1,2 -> �ޗ������@(11)
//�x 3      -> �L�[�{�[�h(10)
	int n;

	if ( Trim(EdtKMK->Text) == "" ) {
    	return;
    } else {
    	n = StrToInt(EdtKMK->Text);
    }

    switch(n)
    {   //���̑��̂Ƃ�����
        case 2:
        case 10:
        case 11:
			if( Cmb5->Text == "mm") {
				EdtKMK->Text = "2";
				Edt2->FPos = 3;
				Edt3->FPos = 3;
            }
			if( Cmb5->Text == "Kgf") {
				EdtKMK->Text = "11";
				Edt2->FPos = 1;
				Edt3->FPos = 1;
            }
			if( Cmb5->Text == "N") {
				EdtKMK->Text = "11";
				Edt2->FPos = 1;
				Edt3->FPos = 1;
            }
			if( Cmb5->Text == "�x") {
				EdtKMK->Text = "10";
				Edt2->FPos = 2;
				Edt3->FPos = 2;
            }
            break;
        default:
            break;
    }




}
//---------------------------------------------------------------------------

//�`��敪 �敪�I��
void __fastcall TForm1::Cmb4Change(TObject *Sender)
{
    //EdtKEIJKBN->Text = IntToStr(Cmb4->ItemIndex + 1);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::AllKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
      if( Key == 17 ){
          BtnF01->Caption = "�ꗗ����";
          BtnF02->Caption = "�O��";
          BtnF03->Caption = "����";
          BtnF04->Caption = "����";
          BtnF05->Caption = "��ʈ��";
          //BtnF06->Caption = "Excel�o��";
          BtnF06->Caption = "���";
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
              BtnF05->Enabled = true;
              BtnF06->Enabled = true;
              BtnF07->Enabled = true;
              BtnF08->Enabled = true;
              BtnF09->Enabled = false;
              BtnF10->Enabled = false;
              BtnF11->Enabled = false;
              BtnF12->Enabled = true;
          }
          else{
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
//INI�t�@�C�� �ǂݍ��� �v���O�������擾
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
     GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, INIname);
     KikiType = atoi(tempo);
     //2009.03.13 MTS E.Takase [001]  ��
     //�ޗ������@�i�P�Ǝg�p�j�͋@��^�C�v��5�Ƃ���
     //if (KikiType <= 0 || KikiType > 4)
     //if (KikiType <= 0 || KikiType > 5)
     //2009.03.13 MTS E.Takase [001]  ��
     //20160729 KikiType=6�̒ǉ�
     if (KikiType <= 0 || KikiType > 6)
        KikiType = 1;

     // �H��敪��ǂݍ���
     GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, INIname);
     iKojoKbn = atoi(tempo);

     /*Windows�ިڸ�؂����o*/
     getlen1 = GetWindowsDirectory((LPSTR)windir, sizeof(windir));
     if (getlen1 == 0){
     	ShowMessage("GetWindowsDirectory Fail");
     	return;
     }else {
     	//INI̧�ٖ����߽��ǉ�
     	wsprintf(INIname, "%s%s", windir, "\\TKSMAIN.ini");	//file name
     }

     // INI̧�ق���̓ǂݍ���
     GetPrivateProfileString("FILE", "PATH", "", StartPATH, MAX_PATH, INIname);

     GetPrivateProfileString("FILE", "PC12", "", tempo, MAX_PATH, INIname);
     strcpy(PC12FileName,StartPATH);
     strcat(PC12FileName,"\\");
     strcat(PC12FileName,tempo);

     GetPrivateProfileString("FILE", "PC34", "", tempo, MAX_PATH, INIname);
     strcpy(PC34FileName,StartPATH);
     strcat(PC34FileName,"\\");
     strcat(PC34FileName,tempo);

     //20160729 PC3,PC4�̒ǉ�
     //PC3
     GetPrivateProfileString("FILE", "PC3", "", tempo, MAX_PATH, INIname);
     strcpy(PC3FileName,StartPATH);
     strcat(PC3FileName,"\\");
     strcat(PC3FileName,tempo);

     //PC4
     GetPrivateProfileString("FILE", "PC4", "", tempo, MAX_PATH, INIname);
     strcpy(PC4FileName,StartPATH);
     strcat(PC4FileName,"\\");
     strcat(PC4FileName,tempo);

     //2009.03.13 MTS E.Takase [001]  ��
     //�ޗ������@�i�P�Ǝg�p�j�͋@��^�C�v��5�Ƃ���
     GetPrivateProfileString("FILE", "PC5", "", tempo, MAX_PATH, INIname);
     strcpy(PC5FileName,StartPATH);
     strcat(PC5FileName,"\\");
     strcat(PC5FileName,tempo);
     //2009.03.13 MTS E.Takase [001]  ��

     //2003.02.18 Excel.Exe�̃t���p�X�ǉ�
     GetPrivateProfileString("EXCEL", "PATH", "", tempo, MAX_PATH, INIname);
     ExcelExePATH = tempo;
}







//---------------------------------------------------------------------------

