//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>

#pragma hdrstop


#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 *Form1;

KDA1_DATA Cur_Kda1;             // �I�������q�X�g�O�����f�[�^
KDA1_DATA Tmp_Kda1;             // �I�������q�X�g�O�����f�[�^

KDA2_DATA M_Kda2[1000];         // �v���f�[�^�i�ő�l�F�P�O�O�O�j
KETA_DATA KETA;  //������̌���

double E_Screen_Data[3][20];
int E_Scale;

int     SEQNOMAX;
int     USER_COD;
String  USER_NAM;
String  BUMO_COD;
String  BUMO_NAM;
bool    DataSave;
int 	RSInputFlag;

int     KENSAKU_Mode;           //�ꗗ�������[�h

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

void Tmp_Kda1_SYOKI(void);

char PC12FileName[MAX_PATH];
char PC34FileName[MAX_PATH];
char StartPATH[MAX_PATH];

int KikiType;               // �@��ԍ�PC1,2,3,4
int ShellExeFlag = 0;       // PC12Ctrl.exe ���s�t���O

int iKojoKbn = 0 ;          // �H��敪

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}

//�u�N�����v
//---------------------------------------------------------------------------
//2002/11/21 ���l �ǉ� E.Takase
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    Database1->Open();

    // �O���b�h�̏�����
    SGr1->ColWidths[0]  =	Panel8->Width;		//	No

	SGr1->ColWidths[1]  =	Panel10->Width;		//	���Ӑ�R�[�h
	SGr1->ColWidths[2]  =	Panel19->Width;		//	���Ӑ�i��
	SGr1->ColWidths[3]  =	Panel12->Width;		//	���b�gNO
	SGr1->ColWidths[4]  =	Panel18->Width;		//	���Еi��

	SGr1->ColWidths[5]  =	Panel13->Width;		//	�q�X�g�O�������萔

	SGr1->ColWidths[6]  =	Panel22->Width;		//	�@�V�@�@�@�@�K�i
	SGr1->ColWidths[7]  =	Panel14->Width;		//	�@�V�@�@�@�@�����K�i
	SGr1->ColWidths[8]  =	Panel15->Width;		//	�@�V�@�@�@�@����K�i

	SGr1->ColWidths[9]  =	Panel16->Width;		//	�ގ���

	SGr1->ColWidths[10]  =	Panel17->Width;		//	�����

    //2002/11/21 ���l �ǉ� E.Takase
	//SGr1->ColWidths[11]  =	0;		            //	�����\���
	SGr1->ColWidths[11]  =	Panel11->Width;	    //	���l

	SGr1->ColWidths[31]  =	0;		            //	�����\���
	SGr1->ColWidths[12]  =	0;		            //	SEQ-NO

	SGr1->ColWidths[13]  =	0;		            //	�ގ��R�[�h
	SGr1->ColWidths[14]  =	0;		            //	�q�X�g�O�����K�i
	SGr1->ColWidths[15]  =	0;		            //	���萔
	SGr1->ColWidths[16]  =	0;		            //	���ϒl
	SGr1->ColWidths[17]  =	0;		            //	�l�h�m
	SGr1->ColWidths[18]  =	0;		            //	�l�`�w
	SGr1->ColWidths[19]  =	0;		            //	�q
	SGr1->ColWidths[20]  =	0;		            //	�W���΍�
	SGr1->ColWidths[21]  =	0;		            //	�b�o
	SGr1->ColWidths[22]  =	0;		            //	�b�o�j
	SGr1->ColWidths[23]  =	0;		            //	�j
	SGr1->ColWidths[24]  =	0;		            //	�s�Ǘ�
	SGr1->ColWidths[25]  =	0;		            //	�o�^��
	SGr1->ColWidths[26]  =	0;		            //	�o�^����
	SGr1->ColWidths[27]  =	0;		            //	�ύX��
	SGr1->ColWidths[28]  =	0;		            //	�ύX����
	SGr1->ColWidths[29]  =	0;		            //	�X�V��
	SGr1->ColWidths[30]  =	0;		            //	�X�V��

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

    //USER_COD = 1;
    KENSAKU_Mode = 1;
    // �����\����̏�����
    EdtCOD->Text = FormatDateTime("yyyy/mm/dd",Date());

    //����A�S����
    Panel3->Caption = BUMO_COD;
    Panel4->Caption = BUMO_NAM;
    Panel6->Caption = IntToStr(USER_COD);
    Panel7->Caption = USER_NAM;

    //RS232C �ǂݍ��݃t���O
    RSInputFlag = 0;

    Read_Ini();

}
// �u�e�P�F�ꗗ�����v
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
    if( !BtnF01->Enabled )    return;
    //ShowMessage(IntToStr(KENSAKU_Mode));
    if ( KENSAKU_Mode != -1 ) Form2->ShowModal();

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
//�u�e�S�F����v
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
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

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�C���Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }
     
     //�f�[�^�x�[�X�ۑ�
     BtnF11Click(Sender);

     //2002/11/21 E.Takase
     //Cur_Kda1.KENSA_YMD = SGr1->Cells[11][SGr1->Row];
     Cur_Kda1.KENSA_YMD = SGr1->Cells[31][SGr1->Row];
     Cur_Kda1.SEQNO = StrToInt(SGr1->Cells[12][SGr1->Row]);
     Cur_Kda1.No = SGr1->Row+1;

     // Read Data Base (Kda2)
     //�f�[�^�x�[�X Query ������
     Query_Kda1->Close();
     Query_Kda1->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "* ";
     sBuf += "FROM KDA1 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kda1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kda1.SEQNO + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_�H��敪�ǉ�

     Query_Kda1->SQL->Add(sBuf);
     Query_Kda1->Open();
     Query_Kda1->Active = true;

     if ( Query_Kda1->RecordCount > 0 ) {
        Query_Kda1->First();
        if ( Query_Kda1->FieldValues["DTKSCOD"].IsNull())
           Cur_Kda1.DTKSCOD = " ";
        else
           Cur_Kda1.DTKSCOD = Query_Kda1->FieldValues["DTKSCOD"];

        if ( Query_Kda1->FieldValues["DTKSHIN"].IsNull())
           Cur_Kda1.DTKSHIN = " ";
        else
           Cur_Kda1.DTKSHIN = Query_Kda1->FieldValues["DTKSHIN"];

        if ( Query_Kda1->FieldValues["LOTNO"].IsNull())
           Cur_Kda1.LOTNO = " ";
        else
           Cur_Kda1.LOTNO = Query_Kda1->FieldValues["LOTNO"];

        if ( Query_Kda1->FieldValues["HINBAN"].IsNull())
           Cur_Kda1.HINBAN = " ";
        else
           Cur_Kda1.HINBAN = Query_Kda1->FieldValues["HINBAN"];

        if ( Query_Kda1->FieldValues["ZISCOD"].IsNull())
           Cur_Kda1.ZISCOD = " ";
        else
           Cur_Kda1.ZISCOD = Query_Kda1->FieldValues["ZISCOD"];

        if ( Query_Kda1->FieldValues["ZISNAM"].IsNull())
           Cur_Kda1.ZISNAM = " ";
        else
           Cur_Kda1.ZISNAM = Query_Kda1->FieldValues["ZISNAM"];

        if ( Query_Kda1->FieldValues["HIST_SOKUT"].IsNull())
           Cur_Kda1.HIST_SOKUT = 0;
        else
           Cur_Kda1.HIST_SOKUT = Query_Kda1->FieldValues["HIST_SOKUT"];
        Cur_Kda1.HIST_SOKUT_Ori = Cur_Kda1.HIST_SOKUT;

        if ( Query_Kda1->FieldValues["SOKUTE_KET"].IsNull())
           Cur_Kda1.SOKUTE_KET = 3;                                    //onishi
        else
           Cur_Kda1.SOKUTE_KET = Query_Kda1->FieldValues["SOKUTE_KET"];

        if ( Query_Kda1->FieldValues["HIST_KIKAK"].IsNull())
           Cur_Kda1.HIST_KIKAK = 0;
        else
           Cur_Kda1.HIST_KIKAK = Query_Kda1->FieldValues["HIST_KIKAK"];

        if ( Query_Kda1->FieldValues["HIST_MIN"].IsNull())
           Cur_Kda1.HIST_MIN = 0;
        else
           Cur_Kda1.HIST_MIN = Query_Kda1->FieldValues["HIST_MIN"];

        if ( Query_Kda1->FieldValues["HIST_MAX"].IsNull())
           Cur_Kda1.HIST_MAX = 0;
        else
           Cur_Kda1.HIST_MAX = Query_Kda1->FieldValues["HIST_MAX"];

        if ( Query_Kda1->FieldValues["SOKUTE_SU"].IsNull())
           Cur_Kda1.SOKUTE_SU = 0;
        else
           Cur_Kda1.SOKUTE_SU = Query_Kda1->FieldValues["SOKUTE_SU"];
        Cur_Kda1.SOKUTE_SU_Ori = Cur_Kda1.SOKUTE_SU;

        if ( Query_Kda1->FieldValues["SOKUTE_AVE"].IsNull())
           Cur_Kda1.SOKUTE_AVE = 0;
        else
           Cur_Kda1.SOKUTE_AVE = Query_Kda1->FieldValues["SOKUTE_AVE"];

        if ( Query_Kda1->FieldValues["SOKUTE_MIN"].IsNull())
           Cur_Kda1.SOKUTE_MIN = 0;
        else
           Cur_Kda1.SOKUTE_MIN = Query_Kda1->FieldValues["SOKUTE_MIN"];

        if ( Query_Kda1->FieldValues["SOKUTE_MAX"].IsNull())
           Cur_Kda1.SOKUTE_MAX = 0;
        else
           Cur_Kda1.SOKUTE_MAX = Query_Kda1->FieldValues["SOKUTE_MAX"];

        if ( Query_Kda1->FieldValues["SOKUTE_R"].IsNull())
           Cur_Kda1.SOKUTE_R = 0;
        else
           Cur_Kda1.SOKUTE_R = Query_Kda1->FieldValues["SOKUTE_R"];

        if ( Query_Kda1->FieldValues["SOKUTE_SGM"].IsNull())
           Cur_Kda1.SOKUTE_SGM = 0;
        else
           Cur_Kda1.SOKUTE_SGM = Query_Kda1->FieldValues["SOKUTE_SGM"];

        if ( Query_Kda1->FieldValues["SOKUTE_CP"].IsNull())
           Cur_Kda1.SOKUTE_CP = 0;
        else
           Cur_Kda1.SOKUTE_CP = Query_Kda1->FieldValues["SOKUTE_CP"];

        if ( Query_Kda1->FieldValues["SOKUTE_CPK"].IsNull())
           Cur_Kda1.SOKUTE_CPK = 0;
        else
           Cur_Kda1.SOKUTE_CPK = Query_Kda1->FieldValues["SOKUTE_CPK"];

        if ( Query_Kda1->FieldValues["SOKUTE_K"].IsNull())
           Cur_Kda1.SOKUTE_K = 0;
        else
           Cur_Kda1.SOKUTE_K = Query_Kda1->FieldValues["SOKUTE_K"];

        if ( Query_Kda1->FieldValues["SOKUTE_P"].IsNull())
           Cur_Kda1.SOKUTE_P = 0;
        else
           Cur_Kda1.SOKUTE_P = Query_Kda1->FieldValues["SOKUTE_P"];

        if ( Query_Kda1->FieldValues["UPDCNT"].IsNull())
           Cur_Kda1.UPDCNT = 0;
        else
           Cur_Kda1.UPDCNT = Query_Kda1->FieldValues["UPDCNT"];

        if ( Query_Kda1->FieldValues["ADDYMD"].IsNull())
           Cur_Kda1.ADDYMD = " ";
        else
           Cur_Kda1.ADDYMD = Query_Kda1->FieldValues["ADDYMD"];


        if ( Query_Kda1->FieldValues["ADDTIM"].IsNull())
           Cur_Kda1.ADDTIM = " ";
        else
           Cur_Kda1.ADDTIM = Query_Kda1->FieldValues["ADDTIM"];

        //2002/11/21 ���l�ǉ� E.Takase
        if ( Query_Kda1->FieldValues["MEMO"].IsNull())
           Cur_Kda1.MEMO = " ";
        else
           Cur_Kda1.MEMO = Query_Kda1->FieldValues["MEMO"];

      } else {
        Query_Kda1->Close();
        return ;
      }

     Query_Kda1->Close();

     for ( i = 0; i < Nums; i++) {
        M_Kda2[i].SOKUTEI_CH = 0;
        M_Kda2[i].DatabaseFlag = 0;
     }

     // Read Data Base (Kda2)
     //�f�[�^�x�[�X Query ������
     Query_Kda2->Close();
     Query_Kda2->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "SOKUTEI_NO, SOKUTEI_CH ";
     sBuf += "FROM KDA2 ";
     sBuf += "WHERE KENSA_YMD = '" + Cur_Kda1.KENSA_YMD + "' " + " AND SEQNO = '" + Cur_Kda1.SEQNO + "' ";
     sBuf += "AND KOJOKBN = " + IntToStr(iKojoKbn) + " "; //20160701_�H��敪�ǉ�
     sBuf += "ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

     Query_Kda2->SQL->Add(sBuf);
     Query_Kda2->Open();
     Query_Kda2->Active = true;

     if ( Query_Kda2->RecordCount > 0 ) {
        Query_Kda2->First();
        while( !Query_Kda2->Eof ) {
           if ( Query_Kda2->FieldValues["SOKUTEI_NO"].IsNull()) {
              T_No = 0;
           } else {
              T_No = Query_Kda2->FieldValues["SOKUTEI_NO"];
           }

           if (T_No > 0 && T_No <= Cur_Kda1.SOKUTE_SU) {
              M_Kda2[T_No - 1].DatabaseFlag = 1;
              if ( Query_Kda2->FieldValues["SOKUTEI_CH"].IsNull())
                 M_Kda2[T_No - 1].SOKUTEI_CH = 0;
              else
                 M_Kda2[T_No - 1].SOKUTEI_CH = Query_Kda2->FieldValues["SOKUTEI_CH"];
           }
           Query_Kda2->Next();
        }
     }

     Query_Kda2->Close();

     // ����v���O�����N������
     if (KikiType == 1 || KikiType == 2) {
        ZeroMemory( &sei, sizeof(sei) );
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	//sei.hwnd = hWnd;
	sei.lpVerb = "open";
        sei.lpFile = PC12FileName;
        //sei.nShow = SW_SHOWMINIMIZED ;
        sei.nShow = SW_SHOWNOACTIVATE | SW_SHOWMINIMIZED ;
        //sei.nShow = SW_SHOWNORMAL;
        sei.lpDirectory = StartPATH;
        sei.lpParameters = "";
        while (FindWindow("WSockWClass", "TRIS �F ���Ԍ���(PC1)") != NULL)
              Sleep(1000);
	retDLL = ShellExecuteEx(&sei);
        Sleep(2000);
        ShellExeFlag = 1;
     } else
        ShellExeFlag = 0;

     // �����ʂ��J��
     Form1->Hide();
     Form3->FormScreenInit(0);
     Form3->ShowModal();

     if (ShellExeFlag == 1)
        Sleep(2000);

     // ��ʂ̑��萔��ύX����
     //�q�X�g�O�������萔 HISUT_SOKUT
     //SGr1->Cells[5][SGr1->Row] = Cur_Kda1.HIST_SOKUT_Ori;
	 sBuf = IntToStr( Cur_Kda1.HIST_SOKUT_Ori);//	�q�X�g�O�������萔
	 SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

     //���萔 SOKUTE_SU
     SGr1->Cells[15][SGr1->Row] = Cur_Kda1.SOKUTE_SU_Ori;

     if ( StrToInt (SGr1->Cells[5][SGr1->Row]) == StrToInt (SGr1->Cells[15][SGr1->Row])) {
        sBuf = "��";//	�����
     } else  {
     	if (Cur_Kda1.SOKUTE_SU > 0 ) {
           sBuf = "�r��";//	����r��
        } else {
	   sBuf = "��";//	������
        }
     }
     SGr1->Cells[10][SGr1->Row] = sBuf;

     //���l MEMO 2002/11/21 E.Takase
     SGr1->Cells[11][SGr1->Row] = Cur_Kda1.MEMO;
     Edt9->Text = Cur_Kda1.MEMO;


}

//---------------------------------------------------------------------------
// �u�e�T�F��ʈ���v
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
// �u�e�V�F�����v
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
     if( !BtnF07->Enabled )    return;
     int iRow,i;
     AnsiString sBuf;
     AnsiString sYMD;

     sYMD = DelSEPA(EdtCOD->Text);
     if( sYMD == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "����������͂��Ă�������";
        SBr1->Update();
        KENSAKU_Mode = 1;
        return;
     }

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     //SGr1������
     SGr1->RowCount = 1;
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
     SGr1->Cells[30][0] = "";
     SGr1->Cells[31][0] = "";

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "select KENSA_YMD, SEQNO, DTKSCOD, DTKSHIN, LOTNO, HINBAN, ";
     sBuf += "ZISCOD, ZISNAM, HIST_SOKUT, HIST_KIKAK, HIST_MIN, HIST_MAX, ";
     sBuf += "SOKUTE_SU, SOKUTE_AVE, SOKUTE_MIN, SOKUTE_MAX, SOKUTE_R, ";
     sBuf += "SOKUTE_SGM, SOKUTE_CP, SOKUTE_CPK, SOKUTE_K, SOKUTE_P, ";
     sBuf += "ADDYMD, ADDTIM, UPDYMD, UPDTIM, UPDCHR, UPDCNT, MEMO";
     sBuf += " From KDA1 ";

     sBuf += " where KENSA_YMD = '";
     sBuf += sYMD + "'";
     sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof == true ) {
     //�������� �O��
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = MSG_02;
        SBr1->Update();
        KENSAKU_Mode = 1;
    	// �{�^���̏�����
    	BtnF01->Enabled = true;
    	BtnF02->Enabled = false;
    	BtnF03->Enabled = false;
    	BtnF04->Enabled = false;
    	BtnF05->Enabled = true;
    	BtnF06->Enabled = false;
    	BtnF07->Enabled = true;
    	BtnF08->Enabled = true;
    	BtnF09->Enabled = false;
    	BtnF10->Enabled = false;
    	BtnF11->Enabled = false;
    	BtnF12->Enabled = true;

        return;

     }
     iRow = 0;
     SEQNOMAX = 0;
     while( !Query1->Eof ){

          // �O���b�h�̍ő�s���������Ă��Ȃ����`�F�b�N����
          if( iRow >= SGr1->RowCount ){
              SGr1->RowCount = iRow;
          }

          // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
          sBuf = iRow + 1;//	No
          SGr1->Cells[0][iRow] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[2]->AsString;//	���Ӑ�R�[�h
          SGr1->Cells[1][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[3]->AsString;//	���Ӑ�i��
          SGr1->Cells[2][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[4]->AsString;//	���b�gNo
          SGr1->Cells[3][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[5]->AsString;//	���Еi��
          SGr1->Cells[4][iRow] = sBuf;

          sBuf = Query1->Fields->Fields[8]->AsString;//	�q�X�g�O�������萔
          SGr1->Cells[5][iRow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

          sBuf = Query1->Fields->Fields[9]->AsString;
          switch(StrToInt(sBuf))
          {
            case 1:
	        SGr1->Cells[6][iRow] = "����";

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[10]->AsString));//	�@�V�@�@�@�@�����K�i
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[11]->AsString));//	�@�V�@�@�@�@����K�i
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
	        SGr1->Cells[6][iRow] = "����";

	        sBuf = FormatFloat("#0.000",StrToFloat(Query1->Fields->Fields[10]->AsString));//	�@�V�@�@�@�@�����K�i
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf = " ";//	�@�V�@�@�@�@����K�i
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
	        SGr1->Cells[6][iRow] = "���";

	        sBuf = " ";//	�@�V�@�@�@�@�����K�i
	        SGr1->Cells[7][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

	        sBuf =FormatFloat("#0.000", StrToFloat(Query1->Fields->Fields[11]->AsString));//	�@�V�@�@�@�@����K�i
	        SGr1->Cells[8][iRow] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

          }

		sBuf = Query1->Fields->Fields[7]->AsString;//	�ގ���
		SGr1->Cells[9][iRow] = sBuf;


		if ( StrToInt (Query1->Fields->Fields[8]->AsString) == StrToInt (Query1->Fields->Fields[12]->AsString )) {
			sBuf = "��";//	�����
		} else  {
            if (StrToInt (Query1->Fields->Fields[12]->AsString ) > 0 ) {
                sBuf = "�r��";//	����r��
            } else {
                sBuf = "��";//	������
            }
        }
		SGr1->Cells[10][iRow] = sBuf;

        //���l�ǉ� 2002/11/21 E.Takase
		sBuf = Query1->Fields->Fields[28]->AsString;//	���l
		SGr1->Cells[11][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[0]->AsString;//	�����\���
		//SGr1->Cells[11][iRow] = sBuf;
		SGr1->Cells[31][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[1]->AsString;//	SEQ-NO
		SGr1->Cells[12][iRow] = sBuf;
        if ( SEQNOMAX < StrToInt(SGr1->Cells[12][iRow]))
            SEQNOMAX = StrToInt(SGr1->Cells[12][iRow]);

		sBuf = Query1->Fields->Fields[6]->AsString;//	�ގ��R�[�h
		SGr1->Cells[13][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[9]->AsString;//	�q�X�g�O�����K�i
		SGr1->Cells[14][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[12]->AsString;//	���萔
		SGr1->Cells[15][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[13]->AsString;//	���ϒl
		SGr1->Cells[16][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[14]->AsString;//	�l�h�m
		SGr1->Cells[17][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[15]->AsString;//	�l�`�w
		SGr1->Cells[18][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[16]->AsString;//	�q
		SGr1->Cells[19][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[17]->AsString;//	�W���΍�
		SGr1->Cells[20][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[18]->AsString;//	�b�o
		SGr1->Cells[21][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[19]->AsString;//	�b�o�j
		SGr1->Cells[22][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[20]->AsString;//	�j
		SGr1->Cells[23][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[21]->AsString;//	�s�Ǘ�
		SGr1->Cells[24][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[22]->AsString;//	�o�^��
		SGr1->Cells[25][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[23]->AsString;//	�o�^����
		SGr1->Cells[26][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[24]->AsString;//	�ύX��
		SGr1->Cells[27][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[25]->AsString;//	�ύX����
		SGr1->Cells[28][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[26]->AsString;//	�X�V��
		SGr1->Cells[29][iRow] = sBuf;

		sBuf = Query1->Fields->Fields[27]->AsString;//	�X�V��
		SGr1->Cells[30][iRow] = sBuf;

          // �J�[�\�������ɃZ�b�g����
          Query1->Next();

          iRow += 1;
     }

     // �ŉ��s���N���A�[
     for( i = 0; i < SGr1->ColCount; i++) {
         SGr1->Cells[i][iRow]  = "";
     }

     SGr1->RowCount = iRow + 1 ;

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

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

     KENSAKU_Mode = -1;

     SGr1SelectCell( Sender, 1, 0, true);
}

//---------------------------------------------------------------------------
//�u�e�W�F�V�K�o�^�v
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    AnsiString sBuf;
    AnsiString sYMD;
    int i;

    if( !BtnF08->Enabled )    return;
    //if( Edt1->Text == "" ){
    //    // �X�e�[�^�X���b�Z�[�W
    //    SBr1->Panels->Items[0]->Text = "�K�{���ڂ���͂��ĉ������B";
    //    SBr1->Update();
    //    return;
    //}

     sYMD = DelSEPA(EdtCOD->Text);

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�V�K�o�^���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

    //Tmp_Kda1 ������
    Tmp_Kda1_SYOKI();

    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    if ( Edt1->Text.IsEmpty() ) {
        ////ShowMessage("�K�{����(���Ӑ�R�[�h)����͂��ĉ������B");
        //SBr1->Panels->Items[0]->Text = "�K�{����(���Ӑ�R�[�h)����͂��ĉ������B";
        //SBr1->Update();
        //return;
        Edt1->Text = " ";
        Tmp_Kda1.DTKSCOD = " ";
    } else { // ���Ӑ�R�[�h
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt1->Text = StrReplace(Edt1->Text,"'","_");
        Tmp_Kda1.DTKSCOD = Edt1->Text;
    }

    if ( Edt2->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���Ӑ�i��)����͂��ĉ������B");
        SBr1->Panels->Items[0]->Text = "�K�{����(���Ӑ�i��)����͂��ĉ������B";
        SBr1->Update();
        return;
    } else { // ���Ӑ�i��
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt2->Text = StrReplace(Edt2->Text,"'","_");
        Tmp_Kda1.DTKSHIN = Edt2->Text;
    }

    if ( Edt3->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���b�gNo)����͂��ĉ������B");
        //SBr1->Panels->Items[0]->Text = "�K�{����(���b�gNo)����͂��ĉ������B";
        //SBr1->Update();
        //return;
        Edt3->Text = " ";
        Tmp_Kda1.LOTNO = " ";
    } else { // ���b�gNo
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt3->Text = StrReplace(Edt3->Text,"'","_");
        Tmp_Kda1.LOTNO = Edt3->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���Еi��)����͂��ĉ������B");
        //SBr1->Panels->Items[0]->Text = "�K�{����(���Еi��)����͂��ĉ������B";
        //SBr1->Update();
        //return;
        Edt4->Text = " ";
        Tmp_Kda1.HINBAN = " ";
    } else { // ���Еi��
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt4->Text = StrReplace(Edt4->Text,"'","_");
        Tmp_Kda1.HINBAN = Edt4->Text;
    }

    if ( Edt8->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(�ގ���)����͂��ĉ������B");
        //SBr1->Panels->Items[0]->Text = "�K�{����(�ގ���)����͂��ĉ������B";
        //SBr1->Update();
        //return;
        Edt8->Text = " ";
        Tmp_Kda1.ZISNAM = " ";
    } else { // �ގ���
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt8->Text = StrReplace(Edt8->Text,"'","_");
        Tmp_Kda1.ZISNAM = Edt8->Text;
    }
    //2002/11/21 E.Takase ���l�ǉ�
    //if ( !(Edt9->Text.IsEmpty() )) // ���l
    //    Tmp_Kda1.MEMO = Edt9->Text;
    if ( !(Edt9->Text.IsEmpty() )) // ���l
        Edt9->Text = StrReplace(Edt9->Text,"'","_");
    Tmp_Kda1.MEMO = Edt9->Text;

    //Tmp_Kda1.ZISCOD;       // �ގ��R�[�h ����
    sBuf = "SELECT ZISCOD FROM KM03 WHERE KM03.ZISNAM = '";
    sBuf += Tmp_Kda1.ZISNAM + "'";
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
    if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
      //ShowMessage( "�ގ������Ԉ���Ă��܂��B" );
      //return;
      Tmp_Kda1.ZISCOD = " ";
    }else {
      Form1->Query1->First();
      Tmp_Kda1.ZISCOD = Form1->Query1->Fields->Fields[0]->AsString;
    }

    if ( !(Edt5->Text.IsEmpty() )) // �q�X�g�O�������萔
         Tmp_Kda1.HIST_SOKUT = StrToFloat(Edt5->Text);

    if ( Cmb1->ItemIndex != -1 ) // �q�X�g�O�����K�i�i�P�C�Q�C�R�j
         Tmp_Kda1.HIST_KIKAK = Cmb1->ItemIndex + 1;

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 2  )) // �q�X�g�O���������K�i
         Tmp_Kda1.HIST_MIN = StrToFloat(Edt6->Text);

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 3  ))// �q�X�g�O��������K�i
         Tmp_Kda1.HIST_MAX = StrToFloat(Edt7->Text);

    // �o�^��
    Tmp_Kda1.ADDYMD = FormatDateTime("yyyymmdd",Date());
    // �o�^����
    Tmp_Kda1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    // �X�V��
    Tmp_Kda1.UPDCNT  = 0;
    // �X�V��
    Tmp_Kda1.UPDCHR  = USER_COD;
    // �����
    Tmp_Kda1.KENSA_YMD  = sYMD;
    // SEQNO
    Tmp_Kda1.SEQNO  = SEQNOMAX + 1;
    // ���茅
    Tmp_Kda1.SOKUTE_KET = 3;                                          //onishi


     /// AddData
     if( AddData() == False ){
        return;
     }

     //// �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = SGr1->RowCount ;                            // NO
     SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 2-sBuf.Length()) + sBuf;
		//	���Ӑ�R�[�h
		SGr1->Cells[1][SGr1->RowCount - 1] = Tmp_Kda1.DTKSCOD;
		//	���Ӑ�i��
		SGr1->Cells[2][SGr1->RowCount - 1] = Tmp_Kda1.DTKSHIN;
		//	���b�gNO
		SGr1->Cells[3][SGr1->RowCount - 1] = Tmp_Kda1.LOTNO;
		//	���Еi��
		SGr1->Cells[4][SGr1->RowCount - 1] = Tmp_Kda1.HINBAN;

		sBuf = IntToStr( Tmp_Kda1.HIST_SOKUT);//	�q�X�g�O�������萔
		SGr1->Cells[5][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

        switch(Tmp_Kda1.HIST_KIKAK )
        {
            case 1:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "����";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MAX);//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "����";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = " ";//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
		        SGr1->Cells[6][SGr1->RowCount - 1] = "���";

		        sBuf = " ";//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf =FormatFloat("#0.000", Tmp_Kda1.HIST_MAX);//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

        }

		//	�ގ���
		SGr1->Cells[9][SGr1->RowCount - 1] = Tmp_Kda1.ZISNAM;
		//	���l 2002/11/21 E.Takase
		SGr1->Cells[11][SGr1->RowCount - 1] = Tmp_Kda1.MEMO;
		//	�����\���
		//SGr1->Cells[11][SGr1->RowCount - 1] = Tmp_Kda1.KENSA_YMD;
		SGr1->Cells[31][SGr1->RowCount - 1] = Tmp_Kda1.KENSA_YMD;
		//	SEQ-NO
		SGr1->Cells[12][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.SEQNO);
		//	�ގ��R�[�h
		SGr1->Cells[13][SGr1->RowCount - 1] = Tmp_Kda1.ZISCOD;

		if ( Tmp_Kda1.HIST_SOKUT == Tmp_Kda1.SOKUTE_SU) {
			sBuf = "��";//	�����
		} else  {
            if (Tmp_Kda1.SOKUTE_SU > 0 ) {
                sBuf = "�r��";//	����r��
            } else {
                sBuf = "��";//	������
            }
        }
		SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;

		//	�ގ��R�[�h
		SGr1->Cells[13][SGr1->RowCount - 1] = Tmp_Kda1.ZISCOD;
		//	�q�X�g�O�����K�i
		SGr1->Cells[14][SGr1->RowCount - 1] = Tmp_Kda1.HIST_KIKAK;
		//	�ύX��
		SGr1->Cells[25][SGr1->RowCount - 1] = Tmp_Kda1.ADDYMD;
		//	�ύX����
		SGr1->Cells[26][SGr1->RowCount - 1] = Tmp_Kda1.ADDTIM;
		//	�X�V��
		SGr1->Cells[29][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.UPDCHR);
		//	�X�V��
		SGr1->Cells[30][SGr1->RowCount - 1] = IntToStr(Tmp_Kda1.UPDCNT);


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
     // �f�[�^��ύX�����t���O
     DataSave = true;
     SEQNOMAX ++;

}

//---------------------------------------------------------------------------
//�u�e�X�F�C���v
void __fastcall TForm1::BtnF09Click(TObject *Sender)
{
     AnsiString sYMD;
     AnsiString sBuf;
     if( !BtnF09->Enabled )    return;

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

     sYMD = DelSEPA(EdtCOD->Text);
     
    //Tmp_Kda1 ������
    Tmp_Kda1_SYOKI();
    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    //ShowMessage ("�C��");
    if ( Edt1->Text.IsEmpty() ) {
        ////ShowMessage("�K�{����(���Ӑ�R�[�h)����͂��ĉ������B");
        //SBr1->Panels->Items[0]->Text = "�K�{����(���Ӑ�R�[�h)����͂��ĉ������B";
        //SBr1->Update();
        //return;
        Edt1->Text = " ";
        Tmp_Kda1.DTKSCOD = " ";

    } else { // ���Ӑ�R�[�h
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt1->Text = StrReplace(Edt1->Text,"'","_");
        Tmp_Kda1.DTKSCOD = Edt1->Text;
    }

    if ( Edt2->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���Ӑ�i��)����͂��ĉ������B");
        SBr1->Panels->Items[0]->Text = "�K�{����(���Ӑ�i��)����͂��ĉ������B";
        SBr1->Update();
        return;
    } else { // ���Ӑ�i��
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt2->Text = StrReplace(Edt2->Text,"'","_");
        Tmp_Kda1.DTKSHIN = Edt2->Text;
    }

    if ( Edt3->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���b�gNo)����͂��ĉ������B");
        SBr1->Panels->Items[0]->Text = "�K�{����(���b�gNo)����͂��ĉ������B";
        SBr1->Update();
        return;
    } else { // ���b�gNo
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt3->Text = StrReplace(Edt3->Text,"'","_");
        Tmp_Kda1.LOTNO = Edt3->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(���Еi��)����͂��ĉ������B");
        SBr1->Panels->Items[0]->Text = "�K�{����(���Еi��)����͂��ĉ������B";
        SBr1->Update();
        return;
    } else { // ���Еi��
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt4->Text = StrReplace(Edt4->Text,"'","_");
        Tmp_Kda1.HINBAN = Edt4->Text;
    }

    if ( Edt4->Text.IsEmpty() ) {
        //ShowMessage("�K�{����(�ގ���)����͂��ĉ������B");
        SBr1->Panels->Items[0]->Text = "�K�{����(�ގ���)����͂��ĉ������B";
        SBr1->Update();
        return;
    } else { // �ގ���
        //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
        Edt8->Text = StrReplace(Edt8->Text,"'","_");
        Tmp_Kda1.ZISNAM = Edt8->Text;
    }
    //Tmp_Kda1.ZISCOD;       // �ގ��R�[�h ����
    sBuf = "SELECT ZISCOD FROM KM03 WHERE KM03.ZISNAM = '";
    sBuf += Tmp_Kda1.ZISNAM + "'";
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;
    if ( Form1->Query1->Bof == true && Form1->Query1->Eof == true) {
      //ShowMessage( "�ގ������Ԉ���Ă��܂��B" );
      //return;
      Tmp_Kda1.ZISCOD = " ";
    }else {
      Form1->Query1->First();
      Tmp_Kda1.ZISCOD = Form1->Query1->Fields->Fields[0]->AsString;
    }

    if ( !(Edt5->Text.IsEmpty() )) // �q�X�g�O�������萔
         Tmp_Kda1.HIST_SOKUT = StrToFloat(Edt5->Text);

    if ( Cmb1->ItemIndex != -1 ) // �q�X�g�O�����K�i�i�P�C�Q�C�R�j
         Tmp_Kda1.HIST_KIKAK = Cmb1->ItemIndex + 1;

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 2  )) // �q�X�g�O���������K�i
         Tmp_Kda1.HIST_MIN = StrToFloat(Edt6->Text);

    if ( ( !(Edt5->Text.IsEmpty() ) )  &&
            ( Tmp_Kda1.HIST_KIKAK == 1 || Tmp_Kda1.HIST_KIKAK== 3  ))// �q�X�g�O��������K�i
         Tmp_Kda1.HIST_MAX = StrToFloat(Edt7->Text);

    // �ύX��
    Tmp_Kda1.UPDYMD = FormatDateTime("yyyymmdd",Date());
    // �ύX����
    Tmp_Kda1.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
    if( SGr1->Cells[30][SGr1->Row] == "" ){
        Tmp_Kda1.UPDCNT  = 0;
    }
    else{
       Tmp_Kda1.UPDCNT  = StrToInt(SGr1->Cells[30][SGr1->Row]);
       Tmp_Kda1.UPDCNT += 1 ;                  // �X�V��
    }
    //2002/11/21 E.Takase
    //Tmp_Kda1.KENSA_YMD  = SGr1->Cells[11][SGr1->Row];
    Tmp_Kda1.KENSA_YMD  = SGr1->Cells[31][SGr1->Row];
    Tmp_Kda1.SEQNO  = StrToInt(SGr1->Cells[12][SGr1->Row]);
    //2002/11/27 E.Takase
    Tmp_Kda1.SOKUTE_SU  = StrToInt(SGr1->Cells[15][SGr1->Row]);

    //2002/11/21 E.Takase ���l�ǉ�
    if ( !(Edt9->Text.IsEmpty() )) // ���l
        Tmp_Kda1.MEMO = StrReplace(Edt9->Text,"'","_");
    Edt9->Text = Tmp_Kda1.MEMO;

     // CollectData
     if( CollectData(SGr1->Cells[1][SGr1->Row]) == False ){
        return;
     }

     // �f�[�^��ύX�����t���O
     DataSave = true;

		//	���Ӑ�R�[�h
		SGr1->Cells[1][SGr1->Row] = Tmp_Kda1.DTKSCOD;
		//	���Ӑ�i��
		SGr1->Cells[2][SGr1->Row] = Tmp_Kda1.DTKSHIN;
		//	���b�gNO
		SGr1->Cells[3][SGr1->Row] = Tmp_Kda1.LOTNO;
		//	���Еi��
		SGr1->Cells[4][SGr1->Row] = Tmp_Kda1.HINBAN;

		sBuf = IntToStr( Tmp_Kda1.HIST_SOKUT);//	�q�X�g�O�������萔
		SGr1->Cells[5][SGr1->Row] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;

        switch(Tmp_Kda1.HIST_KIKAK )
        {
            case 1:
		        SGr1->Cells[6][SGr1->Row] = "����";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MAX);//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 2:
		        SGr1->Cells[6][SGr1->Row] = "����";

		        sBuf = FormatFloat("#0.000",Tmp_Kda1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf = " ";//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

            case 3:
		        SGr1->Cells[6][SGr1->Row] = "���";

		        sBuf = " ";//	�@�V�@�@�@�@�����K�i
		        SGr1->Cells[7][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

		        sBuf =FormatFloat("#0.000", Tmp_Kda1.HIST_MAX);//	�@�V�@�@�@�@����K�i
		        SGr1->Cells[8][SGr1->Row] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
                break;

        }

		//	�ގ���
		SGr1->Cells[9][SGr1->Row] = Tmp_Kda1.ZISNAM;

		if ( Tmp_Kda1.HIST_SOKUT == Tmp_Kda1.SOKUTE_SU) {
			sBuf = "��";//	�����
		} else  {
            if (Tmp_Kda1.SOKUTE_SU > 0 ) {
                sBuf = "�r��";//	����r��
            } else {
                sBuf = "��";//	������
            }
        }
		SGr1->Cells[10][SGr1->Row] = sBuf;

		//	�ގ��R�[�h
		SGr1->Cells[13][SGr1->Row] = Tmp_Kda1.ZISCOD;
		//	�q�X�g�O�����K�i
		SGr1->Cells[14][SGr1->Row] = Tmp_Kda1.HIST_KIKAK;
		//	�ύX��
		SGr1->Cells[27][SGr1->Row] = Tmp_Kda1.UPDYMD;
		//	�ύX����
		SGr1->Cells[28][SGr1->Row] = Tmp_Kda1.UPDTIM;
		//	�X�V��
		SGr1->Cells[30][SGr1->Row] = IntToStr(Tmp_Kda1.UPDCNT);

		//	���l 2002/11/21 E.Takase
		SGr1->Cells[11][SGr1->Row] = Tmp_Kda1.MEMO;

     SGr1->SetFocus();
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

}

//---------------------------------------------------------------------------
//�u�e�P�O�F�폜�v
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{
     int i;
     AnsiString sYMD;

     if( !BtnF10->Enabled )    return;

     if( SGr1->Cells[1][SGr1->Row] == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�폜�Ώۂł͂���܂���B";
        SBr1->Update();
        SGr1->SetFocus();
        return;
     }

     sYMD = DelSEPA(EdtCOD->Text);

     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = "�폜���ł��D�D�D���΂炭���҂��������B";
     SBr1->Update();

    //Tmp_Kda1 ������
    Tmp_Kda1_SYOKI();

    // �f�[�^���o�b�t�@�Ɋi�[���܂��B
    //ShowMessage ("�폜");
    //�����
     //2002/11/21 E.Takase
     //Tmp_Kda1.KENSA_YMD  = SGr1->Cells[11][SGr1->Row];
     Tmp_Kda1.KENSA_YMD  = SGr1->Cells[31][SGr1->Row];
    //SEQNO
     Tmp_Kda1.SEQNO  = StrToInt(SGr1->Cells[12][SGr1->Row]);



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
         SGr1->Cells[31][i] = SGr1->Cells[31][i+1];
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
//�u�e�P�P�F�ۑ��v
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
     //ShowMessage ("�ۑ�");
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
     SGr1->SetFocus();
     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = false;
}

//---------------------------------------------------------------------------
// �u�e�P�Q�F�I���v
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{
     if( !BtnF12->Enabled )    return;
     Close();
}

//---------------------------------------------------------------------------
//�u�Z�����I�������O�v
// 2002/11/21 ���l�ǉ� E.Takase
void __fastcall TForm1::SGr1SelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    AnsiString sBuf;

    //	No
    PnlNO->Caption = SGr1->Cells[0][ARow];

    //	���Ӑ�R�[�h
    Edt1->Text = SGr1->Cells[1][ARow];

    //	���Ӑ�i��
    Edt2->Text = SGr1->Cells[2][ARow];
    //	���b�gNO
    Edt3->Text = SGr1->Cells[3][ARow];
    //	���Еi��
    Edt4->Text = SGr1->Cells[4][ARow];
    //	�q�X�g�O�������萔
    Edt5->Text = SGr1->Cells[5][ARow];

    //		�@�V�@�@�@�@�K�i
    if ( Trim( SGr1->Cells[14][ARow] ) != "" )
        Cmb1->ItemIndex =StrToInt( SGr1->Cells[14][ARow]) - 1;
    else Cmb1->ItemIndex = -1;

    //	�@�V�@�@�@�@�����K�i
    if ( Trim( SGr1->Cells[7][ARow] ) != "" ) {
        Edt6->Enabled = true;
        Edt6->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[7][ARow]));
    }
    else {
        Edt6->Text = "";
        Edt6->Enabled = false;
    }

    //	�@�V�@�@�@�@����K�i
    if ( Trim( SGr1->Cells[8][ARow] ) != "" ) {
        Edt7->Enabled = true;
        Edt7->Text = FormatFloat("#0.000",StrToFloat(SGr1->Cells[8][ARow]));
    }
    else {
        Edt7->Text = "";
        Edt7->Enabled = false;
    }

    //	�ގ�����
    Edt8->Text = SGr1->Cells[9][ARow];

    //	���l 2002/11/21 E.Takase
    Edt9->Text = SGr1->Cells[11][ARow];

}
//---------------------------------------------------------------------------
//�u�t�H�[�� KeyDown�v
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
         case VK_F2:  BtnF02Click(Sender);    break;
         case VK_F3:  BtnF03Click(Sender);    break;
         case VK_F4:  BtnF04Click(Sender);    break;
         case VK_F5:  BtnF05Click(Sender);    break;
//         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:  BtnF07Click(Sender);    break;
         case VK_F8:  BtnF08Click(Sender);    break;
         case VK_F9:  BtnF09Click(Sender);    break;
         case VK_F10: BtnF10Click(Sender);    Key = 0; break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;


         // �O��
         case VK_UP:
         case VK_LEFT:
                if(Edt1->Focused() && Edt1->SelStart == 0 && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    //2002/11/21 E.Takase ���l�ǉ�
                    //Edt8->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == 0 && Edt2->SelLength == 0 ){
                   // KENSAKU_Mode = 2;
				   //	BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == 0 && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == 0 && Edt4->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
                    //BtnF01->Enabled = false;
					Edt3->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == 0 && Edt5->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                //if(Cmb1->Focused() && Cmb1->SelStart == 0 && Cmb1->SelLength == 0 ){
                //if(Cmb1->Focused() ){
                //    KENSAKU_Mode = -1;
                //    Edt5->SetFocus();
                //    break;
                //}
                if(Cmb1->Focused() && Cmb1->SelStart == 0 && Cmb1->SelLength == 0 && Key == VK_LEFT ){
                    Edt5->SetFocus();
                    break;
                }

                if(Edt6->Focused() && Edt6->SelStart == 0 && Edt6->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                if(Edt7->Focused() && Edt7->SelStart == 0 && Edt7->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1  ) {
                        Edt6->SetFocus();
                    }else { Cmb1->SetFocus(); }
                    break;
                }
                if(Edt8->Focused() && Edt8->SelStart == 0 && Edt8->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    }else { Edt6->SetFocus(); }
                    break;
                }
                //2002/11/21 E.Takase ���l�ǉ�
                if(Edt9->Focused() && Edt9->SelStart == 0 && Edt9->SelLength == 0 ){
                    Edt8->SetFocus();
                    break;
                }

                break;

         // ����
         case VK_DOWN:
         case VK_RIGHT:
                if(Edt1->Focused() && Edt1->SelStart == Edt1->Text.Length() && Edt1->SelLength == 0 ){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused() && Edt2->SelStart == Edt2->Text.Length() && Edt2->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused() && Edt3->SelStart == Edt3->Text.Length() && Edt3->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused() && Edt4->SelStart == Edt4->Text.Length() && Edt4->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused() && Edt5->SelStart == Edt5->Text.Length() && Edt5->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                //if(Cmb1->Focused() ){
                ////if(Cmb1->Focused() && Cmb1->SelStart == Cmb1->Text.Length() && Cmb1->SelLength == 0 ){
                //    KENSAKU_Mode = -1;
                //    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 ) {
                //        Edt6->SetFocus();
                //    } else { Edt7->SetFocus(); }
                //    break;
                //}
                if(Cmb1->Focused() && Cmb1->SelStart == Cmb1->Text.Length() && Cmb1->SelLength == 0 && Key == VK_RIGHT ) {                   KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1 ) {
                        Edt6->SetFocus();
                    } else { Edt7->SetFocus(); }
                    break;
                }
                if(Edt6->Focused() && Edt6->SelStart == Edt6->Text.Length() && Edt6->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    } else { Edt8->SetFocus(); }
                    break;
                }
                //break;
                if(Edt7->Focused() && Edt7->SelStart == Edt7->Text.Length() && Edt7->SelLength == 0 ){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt8->SetFocus();
                    break;
                }
                //break;
                if(Edt8->Focused() && Edt8->SelStart == Edt8->Text.Length() && Edt8->SelLength == 0 ){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    //2002/11/21 E.Takase ���l�ǉ�
                    //Edt1->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                //2002/11/21 E.Takase ���l�ǉ�
                if(Edt9->Focused() && Edt9->SelStart == Edt9->Text.Length() && Edt9->SelLength == 0 ){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                break;


         // Enter
         case VK_RETURN:
                if(EdtCOD->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    BtnF07Click(Sender);
                    break;
                }
                if(Edt1->Focused()){
                    //KENSAKU_Mode = 3;
					//BtnF01->Enabled = true;
                    Edt2->SetFocus();
                    break;
                }
                if(Edt2->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt3->SetFocus();
                    break;
                }
                if(Edt3->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt4->SetFocus();
                    break;
                }
                if(Edt4->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt5->SetFocus();
                    break;
                }
                if(Edt5->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Cmb1->SetFocus();
                    break;
                }
                if(Cmb1->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 1 || Cmb1->ItemIndex == -1  ) {
                        Edt6->SetFocus();
                    } else { Edt7->SetFocus(); }
                    break;
                }
                if(Edt6->Focused()){
					//BtnF01->Enabled = false;
                    //KENSAKU_Mode = -1;
                    if ( Cmb1->ItemIndex == 0 || Cmb1->ItemIndex == 2 || Cmb1->ItemIndex == -1  ) {
                        Edt7->SetFocus();
                    }else { Edt8->SetFocus(); }
                    break;
                }
                if(Edt7->Focused()){
                    //KENSAKU_Mode = -1;
					//BtnF01->Enabled = false;
                    Edt8->SetFocus();
                    break;
                }
                if(Edt8->Focused()){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    //2002/11/21 E.Takase ���l�ǉ�
                    //Edt1->SetFocus();
                    Edt9->SetFocus();
                    break;
                }
                //2002/11/21 E.Takase ���l�ǉ�
                if(Edt9->Focused()){
                    //KENSAKU_Mode = 2;
					//BtnF01->Enabled = true;
                    Edt1->SetFocus();
                    break;
                }
                break;

     }

}

//---------------------------------------------------------------------------
//SGr1KeyPress
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
         case VK_RETURN:Edt1->SetFocus();
                        KENSAKU_Mode = 2;
                        BtnF01->Enabled = true;      break;
     }

}

//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
// �f�[�^��ǉ����܂��B
bool __fastcall TForm1::AddData()
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     // �⍇�����쐬
     sBuf = "select KENSA_YMD from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // �����
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     //2002/11/21 E.Takase ���l�ǉ�
     sBuf = "insert into KDA1(";
     sBuf += " KENSA_YMD,SEQNO,DTKSCOD,DTKSHIN,LOTNO,HINBAN,";
     sBuf += "ZISCOD,ZISNAM,HIST_SOKUT,HIST_KIKAK,HIST_MIN,";
     //sBuf += "HIST_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,SOKUTE_KET )";
     sBuf += "HIST_MAX,ADDYMD,ADDTIM,UPDCHR,UPDCNT,SOKUTE_KET,MEMO, KOJOKBN )";  //20160701_�H��敪�ǉ�

     sBuf += " values('";
	 sBuf += Tmp_Kda1.KENSA_YMD				    + "',";		// �����\��N����
	 sBuf += IntToStr(Tmp_Kda1.SEQNO)		    + ",'";		// SEQ-NO
	 sBuf += Tmp_Kda1.DTKSCOD				    + "','";	// ���Ӑ�R�[�h
	 sBuf += Tmp_Kda1.DTKSHIN				    + "','";    // ���Ӑ�i��
	 sBuf += Tmp_Kda1.LOTNO					    + "','";	// ���b�gNo
	 sBuf += Tmp_Kda1.HINBAN					+ "','";	// ���Еi��
	 sBuf += Tmp_Kda1.ZISCOD					+ "','";    // �ގ��R�[�h
	 sBuf += Tmp_Kda1.ZISNAM					+ "',";     // �ގ���
	 sBuf += IntToStr(Tmp_Kda1.HIST_SOKUT)	    + ",";      // �q�X�g�O�������萔
	 sBuf += IntToStr(Tmp_Kda1.HIST_KIKAK)	    + ",";      // �q�X�g�O�����K�i�i�P�C�Q�C�R)
	 sBuf += FloatToStr(Tmp_Kda1.HIST_MIN)	    + ",";      // �q�X�g�O���������K�i
	 sBuf += FloatToStr(Tmp_Kda1.HIST_MAX)	    + ",'";     // �q�X�g�O��������K�i
	 sBuf += Tmp_Kda1.ADDYMD					+ "','";    // �o�^��
	 sBuf += Tmp_Kda1.ADDTIM					+ "','";    // �o�^����
	 sBuf += IntToStr(Tmp_Kda1.UPDCHR)		   	+ "',";     // �X�V��
	 sBuf += IntToStr(Tmp_Kda1.UPDCNT)			+ ",";      // �X�V��
	 sBuf += IntToStr(Tmp_Kda1.SOKUTE_KET)		+ ",'";     // ���茅��
	 sBuf += Tmp_Kda1.MEMO  		            + "',";      // ���l
         sBuf += IntToStr(iKojoKbn)  		            + " ";      // 20160701_�H��敪�ǉ�
     sBuf += ")";
     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }

     return(True);

}


//---------------------------------------------------------------------------
// �f�[�^���C�����܂��B
//2002/11/21 E.Takase ���l�ǉ�
bool __fastcall TForm1::CollectData(String OldKey)
{
     AnsiString sBuf;

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     //2002/11/21 E.Takase ���l�ǉ�
     sBuf = "update KDA1 set ";
     sBuf = sBuf + "DTKSCOD='"    + Tmp_Kda1.DTKSCOD      + "', "; // ���Ӑ�R�[�h
     sBuf = sBuf + "DTKSHIN='"    + Tmp_Kda1.DTKSHIN      + "', "; // ���Ӑ�i��
     sBuf = sBuf + "LOTNO='"      + Tmp_Kda1.LOTNO        + "', "; // ���b�gNo
     sBuf = sBuf + "HINBAN='"     + Tmp_Kda1.HINBAN       + "', "; // ���Еi��
     sBuf = sBuf + "ZISNAM='"     + Tmp_Kda1.ZISNAM       + "', "; // �ގ���
     sBuf = sBuf + "ZISCOD='"     + Tmp_Kda1.ZISCOD       + "', "; // �ގ��R�[�h ����
     sBuf = sBuf + "HIST_SOKUT="  + Tmp_Kda1.HIST_SOKUT   + ", ";  // �q�X�g�O�������萔
     sBuf = sBuf + "HIST_KIKAK="  + Tmp_Kda1.HIST_KIKAK   + ", ";  // �q�X�g�O�����K�i�i�P�C�Q�C�R�j
     sBuf = sBuf + "HIST_MIN="    + Tmp_Kda1.HIST_MIN     + ", ";  // �q�X�g�O���������K�i
     sBuf = sBuf + "HIST_MAX="    + Tmp_Kda1.HIST_MAX     + ", ";  // �q�X�g�O��������K�i
     sBuf = sBuf + "UPDYMD='"     + Tmp_Kda1.UPDYMD       + "', "; // �ύX��
     sBuf = sBuf + "UPDTIM='"     + Tmp_Kda1.UPDTIM       + "', "; // �ύX����
     sBuf = sBuf + "UPDCNT='"     + Tmp_Kda1.UPDCNT       + "', "; // �X�V��
     sBuf = sBuf + "MEMO='"       + Tmp_Kda1.MEMO         + "' ";   // ���l
     sBuf = sBuf + "where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";
     sBuf = sBuf + "AND SEQNO=" + Tmp_Kda1.SEQNO + "";
     sBuf = sBuf + " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
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
     sBuf = "select KENSA_YMD from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // �����
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( Query1->Eof == True &&  Query1->Bof == True ){
            SBr1->Panels->Items[0]->Text = "�Y���̃f�[�^��������܂���B�폜�ł��܂���ł����B";
            SBr1->Update();
            return(False);
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }



     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "delete from KDA1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // �����
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf +=" AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�


     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }


     //KDA2
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "delete from KDA2 ";
     sBuf +=" where KENSA_YMD='" + Tmp_Kda1.KENSA_YMD + "'";  // �����
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_Kda1.SEQNO);            // SEQNO
     sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�


     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return(False);
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
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
//�u�b�����P �ύX�v
void __fastcall TForm1::Cmb1Change(TObject *Sender)
{
    switch( Cmb1->ItemIndex){
        case 0: //0 ����
            Edt6->Enabled = true;
            Edt7->Enabled = true;
            break;
        case 1: //0 ����
            Edt6->Enabled = true;
            Edt7->Text = "0";
            Edt7->Enabled = false;
            break;
        case 2: //0 ���
            Edt6->Text = "0";
            Edt6->Enabled = false;
            Edt7->Enabled = true;
            break;
    }
}
//---------------------------------------------------------------------------
void Tmp_Kda1_SYOKI(void)
{
	Tmp_Kda1.No = 0;				// �I��ԍ�
	Tmp_Kda1.KENSA_YMD = "";		// �����\��N����
	Tmp_Kda1.SEQNO = 0;				// SEQ-NO
	Tmp_Kda1.DTKSCOD = "";			// ���Ӑ�R�[�h
	Tmp_Kda1.DTKSHIN = "";      	// ���Ӑ�i��
	Tmp_Kda1.LOTNO = "";			// ���b�gNo
	Tmp_Kda1.HINBAN = "";			// ���Еi��
	Tmp_Kda1.ZISCOD = "";       	// �ގ��R�[�h
	Tmp_Kda1.ZISNAM = "";       	// �ގ���
	Tmp_Kda1.HIST_SOKUT_Ori = 0;    // �q�X�g�O�������萔(Origal)
	Tmp_Kda1.HIST_SOKUT = 0;        // �q�X�g�O�������萔
	Tmp_Kda1.HIST_KIKAK = 0;        // �q�X�g�O�����K�i�i�P�C�Q�C�R�j
	Tmp_Kda1.HIST_MIN = 0.0;        // �q�X�g�O���������K�i
	Tmp_Kda1.HIST_MAX = 0.0;        // �q�X�g�O��������K�i
	Tmp_Kda1.SOKUTE_SU = 0;         // ���萔
	Tmp_Kda1.SOKUTE_AVE = 0.0;      // ���ϒl
	Tmp_Kda1.SOKUTE_MIN = 0.0;      // �ŏ��l
	Tmp_Kda1.SOKUTE_MAX = 0.0;      // �ő�l
	Tmp_Kda1.SOKUTE_R = 0.0;        // R
	Tmp_Kda1.SOKUTE_SGM = 0.0;      // �W���΍���
	Tmp_Kda1.SOKUTE_CP = 0.0;       // CP
	Tmp_Kda1.SOKUTE_CPK = 0.0;      // CPK
	Tmp_Kda1.SOKUTE_K = 0.0;        // K
	Tmp_Kda1.SOKUTE_P = 0.0;        // �s�Ǘ�
	Tmp_Kda1.ADDYMD = "";       	// �o�^��
	Tmp_Kda1.ADDTIM = "";       	// �o�^����
	Tmp_Kda1.UPDYMD = "";       	// �ύX��
	Tmp_Kda1.UPDTIM = "";       	// �ύX����
	Tmp_Kda1.UPDCHR = 0;            // �X�V��
	Tmp_Kda1.UPDCNT = 0;            // �X�V��
	Tmp_Kda1.MEMO = "";             // ���l
}


//---------------------------------------------------------------------------
void __fastcall TForm1::AllKeyEnter(TObject *Sender)
{
    if(EdtCOD->Focused() ){
        KENSAKU_Mode = 1;
        BtnF01->Enabled = true;
        return;
    }
    if(Edt1->Focused() ){
        KENSAKU_Mode = 2;
        BtnF01->Enabled = true;
        return;
    }
    if(Edt2->Focused() ){
        KENSAKU_Mode = 3;
        BtnF01->Enabled = true;
        return;
    }

    KENSAKU_Mode = -1;
    BtnF01->Enabled = false;

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

    //����A�S����
    Form3->Panel3->Caption = BUMO_COD;
    Form3->Panel4->Caption = BUMO_NAM;
    Form3->Panel6->Caption = IntToStr(USER_COD);
    Form3->Panel7->Caption = USER_NAM;


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
     if (KikiType <= 0 || KikiType > 4)
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

