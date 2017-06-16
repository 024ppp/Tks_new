/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�P�T�j                  *
*  file   name   : Unit1.cpp                                           *
*  create        : 1999.11                                             *
*  update        :                                                     *
*  contents      : ��̔�d���胁�C���v���O����                        *
*  written by    : �� ���N �iNKK unics Corp.)                          *
*  reviced ver   : 1.0                                                 *
***********************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
// �\�����闚���ް��̍ő��
int LOTMAX = 10 ;

//----------------------------------------------------------------------------
// RS232C Open or Create �̎w���t���O
// 0: Create   1: Open
int iRS232C = 1 ;
int iChNo = 2;
int iChNo_Old=2; ;
int KikiType = 1;
int ret_232 = 0;

//----------------------------------------------------------------------------
int USER_COD ;              // �S���Һ���
AnsiString USER_NAM;        // �S���Җ�
AnsiString BUMO_COD;        // ���庰��
AnsiString BUMO_NAM;        // ���喼
int RSInputFlag;            //RS232C�ǂݍ��݃t���O

//---------------------------------------------------------------------------
//RS232C�ʐM�p�ϐ�
#define WM_Notify_WriteData WM_USER + 3040	// ����v���Z�X�ɒʒm���܂�
#define WM_Notify_WriteData1 WM_USER + 3041	// ����v���Z�X�ɒʒm���܂�

char SharedBuff[BUFFERSIZE];                    // ��MBUFFER
int  iShareFlag = 0 ;                           // RS232C�ڑ��t���O
int  ShareFlag = 0 ;                            // RS232C�Ɛڑ����邩�ǂ����̎w���t���O

//---------------------------------------------------------------------------
// KD51�\���̕ϐ�
structKD51 KD51Data[30];      // ��̔�d�ް�̧��  KD51

//KD53W�\���̕ϐ�
structKD53W KD53WData[30];    // ��̔�d�����ް�ܰ�̧��  KD53W


//---------------------------------------------------------------------------
//��ʑ���p�ϐ�
int iRec_Kd51;              // �ꗗ�������ʌ���
int CurField;               // 1: ���ق��������ɂ���
                            // 2: ���ق��v�����ɂ���
                            // 3: ���ق���ʉ��̋@�\���݂ɂ���
int ymdtl_flg;              // 1: ���ق��v���\����ɂ���
                            // 2: ���ق��ڰNO�ɂ���
int btn_flg;                //  ��ʉ��̋@�\���݂̎w���t���O


int DataNoIdx;              // ��»���ك|�W�V����NO�ɑ΂����ް�NO

int SamplePositionIdx;      // ����ك|�W�V����NO

int iFirstPosition ;        // �v�������ް��擪�̻�����߼޼��NO
int iLastPosition ;         // �v�������ް��̍Ō�� ������߼޼��NO

int iKskStart=0;            // �P: �v���J�n  0: �v���ł��Ȃ�
int AllDataChg;            // ��ʂɕ\�����Ă����ް��X�V����邩�ǂ���
int CurSampChg;
int CurDataChg;

int iSaveFlag= 0;           // Scrollbar��Change�C�x���g�Ŏg���ϐ�

int CurBackFlg =0 ;
int iKomoku=1;                //���荀�ڂ̎w���t���O

int HaveSokutei = 0 ;
int Update_err = 0;
int Save_Click =0;          //[�ۑ��v���݂��������ꍇ�̎w���t���O

int iKojoKbn = 0 ;          // �H��敪

//---------------------------------------------------------------------------
// [Option]���݂������ꍇ�g���ϐ�
int iOption = 1 ;           // iOption == 1  ���藚��\���i��ON, �FON)
                            // iOPtion == 2  �H���\�͕\���i��ON, �FON)
                            // iOption == 3   �\���Ȃ��i��OFF, �FOFF)
//---------------------------------------------------------------------------
// �\�����b�Z�[�W
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
AnsiString MSG_10 = "�f�[�^���ҏW����Ă��܂��B\n�ۑ����܂����H" ;
AnsiString MSG_11 = "�v���@��̏������Ɏ��s���܂����B�@�����y�уL�[�{�[�h����̓��͎͂g�p�\�ł��B" ;
AnsiString MSG_14 = "�v���@��̉���������܂���B�@�����y�уL�[�{�[�h����̓��͎͂g�p�\�ł��B" ;
AnsiString MSG_15 = "�v���@��͑��̃p�\�R���Ŏg�p���Ă��܂��B�@�����y�уL�[�{�[�h����̓��͎͂g�p�\�ł��B" ;
AnsiString MSG_12 = "�����f�[�^ �O ���B" ;
AnsiString MSG_13 = "��̔�d�̌v�����ʂ𔽉f�����܂����H" ;
AnsiString MSG_16 = "�R���~�̌v�����ʂ𔽉f�����܂����H" ;

//----------------------------------------------------------------------------
// ��ʺ��۰ٕۑ��ϐ�
TNumberEdit *pEdt1[30] ;    //  ���ް��P�̺��۰ق�ۑ�
TNumberEdit *pEdt2[30] ;    //  ���ް�2 �̺��۰ق�ۑ�
TNumberEdit *pEdt3[30] ;    //  ���ް�3 �̺��۰ق�ۑ�
TNumberEdit *pEdt4[30] ;    //  �ް��l�ԍ���ۑ�
TPanel *pPnlP[30] ;         //  ��NO�i�߼޼�ݔԍ��j�̺��۰ق�ۑ�
TPanel *pPnlN[30] ;         //  ��N(�ް���)�̺��۰ق�ۑ�
TScrollBar *pScrl[30];      //  ScrollBar�̺��۰ق�ۑ�

//���薾��
TNumberEdit *pEdt1_S[4] ;    //  ���ް��P�̺��۰ق�ۑ�
TNumberEdit *pEdt2_S[4] ;    //  ���ް�2 �̺��۰ق�ۑ�
TNumberEdit *pEdt3_S[4] ;    //  ���ް�3 �̺��۰ق�ۑ�
TNumberEdit *pEdt4_S[4] ;    //  �ް��l�ԍ���ۑ�
TPanel *pPnl_S[4] ;          //  ��NO�i�߼޼�ݔԍ��j�̺��۰ق�ۑ�
TScrollBar *pScrl_S[4];      //  ScrollBar�̺��۰ق�ۑ�


// �֐��̐錾
void SaveCtlID() ;
void ToDrawGraph( int, int  ) ;
void DrawRireki(TImage *GraphName,int n, char *pStr, double[10] , double[10] , double[10] , int );
void SetEnabel(int );
void SetEnter(void);
int SaveRegaiDt(void);
void CheckInKikaku(int );
int  CheckDtNo(void);
void ToNextData(void);
void ToPreData(void);
void DisplayInfo(void);
void StatBarClear(AnsiString );
void ClearRed(void) ;
void SetRed(int );
void CurseBack(void);

void ExecF1(void);
void ExecF4(void);
void ExecF6(void); //2002/11/07 E.Takase
void ExecF8(void);
void ExecF9(void);
void ExecF10(void);
void ExecF11(void);

void KD53WFormat(void);
void AddKd53W(void);
int  CheckLotNo(int ) ;
void CopyKD51Data(void) ;

int  Kd51_Serch01(void);
int  Kd51_Serch02(int flag);
void Kd51_Update01(void);
long Kd53W_Create01(AnsiString, int, int) ;
int  Kd53W_Serch01();
int  IsNullSpace(AnsiString);
int  BHijyuCal(int ,int ) ;
int CheckKomoku(int , int ) ;
extern void WriteLog(char *);
int Kd51_Serch03(void);

void Kd53W_Delete01(void);
void KD53WFormat(void);


AnsiString DelSEPA( AnsiString );
AnsiString InsSEPA( AnsiString );

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//--------------------------------------------------------------------------
void __fastcall TForm1::OnNotifyWriteData(TMessage &Message)
{
 int nNumber;
 double dVal;

 // CONNECT n:   Return:  OK/ERROR
 // [Data]

    nNumber = SharedMemory_Read(2, SharedBuff);

    // KeyBoard Pc3 Pc4
    if( KikiType == 3 || KikiType == 4 ) return ;

    if( KikiType == 1 ){

       if( iKomoku < 4  && iChNo == 6 ) return ;

       //20160728 �d�q�V���̐ؑ֋@�ڑ��ɑΉ�
       /*
        // �`���l���ԍ��P�`�T�܂ŁA�d�ʂ��v�����Ȃ�
       if( iKomoku == 4 && iChNo != 6 ) return ;
       */
       if( iKojoKbn == 0 ){
           //�{�Ђ̏ꍇ�A�]���ʂ�ɏ������s��
           if( iKomoku == 4 && iChNo != 6 ) return ;
       }
       else if( iKojoKbn == 1 ){
           //�L�z�̏ꍇ�A�ؑ֊�Ch5�Ɍq����
           if( iKomoku == 4 && iChNo != 5 ) return ;
       }
       
    }

    // Pc2�}�V���ŏd�ʂ��v�����Ȃ�
    if( KikiType == 2 && iKomoku == 4  ) return ;


     // RS232C�Ɛڑ������ꍇ
     if (iShareFlag == 1) {      // OK/ERROR

         // RS232C�Ɛڑ����������ꍇ
        if( strncmp( SharedBuff, "OK", 2) == 0 ){
            iShareFlag = 2;

         // RS232C�Ɛڑ��G���[�̏ꍇ
        }else if( strncmp( SharedBuff, "ERROR", 5) == 0 ){
             Beep();
             StatBarClear(MSG_14) ;

             iShareFlag = 0;
        }else if( strncmp( SharedBuff, "C_ERROR", 7) == 0 ){
             Beep();
             StatBarClear(MSG_15) ;

             iShareFlag = 0;
        }
     }

     // RS232C�Ɛڑ����������ꍇ �A��M��������l����ʂ֕\��
     if (iShareFlag == 2) {

         // �J�\�[���𑪒�l���۰قɍ��킹��ꍇ�����ް�����M���Ȃ�
        if( nNumber > 0 &&  strncmp( SharedBuff, "OK", 2) != 0 &&
                            strncmp(SharedBuff, "ERROR", 5) != 0 &&
                            strncmp(SharedBuff, "C_ERROR", 7) != 0 &&
                            ( !Form1->BtnF01->Focused()  &&
                              !Form1->BtnF02->Focused()  &&
                              !Form1->BtnF03->Focused()  &&
                              !Form1->BtnF05->Focused()  &&
                              !Form1->BtnF07->Focused()  &&
                              !Form1->BtnF10->Focused()  &&
                              !Form1->BtnF11->Focused()  &&
                              !Form1->BtnF12->Focused()  &&
                              !Form1->edtymd->Focused()  &&
                              !Form1->edttlno->Focused() ) &&
                             (SamplePositionIdx >= iFirstPosition &&
                                 SamplePositionIdx <= iLastPosition  )){

           dVal = atof( SharedBuff );

           if( DataNoIdx == 1 ) {
                      pEdt1_S[iKomoku-1]->Text = FormatFloat("#0.000",dVal );
           }else if (DataNoIdx == 2 ){
                      pEdt2_S[iKomoku-1]->Text = FormatFloat("#0.000",dVal );
           }else{
                      pEdt3_S[iKomoku-1]->Text = FormatFloat("#0.000",dVal );
           }
           //RS232C�ǂݍ��݃t���O 1
           RSInputFlag = 1;


           //�����ް����Z�b�g���Ă���J�[�\���������I�Ɏ��̑���l�ֈړ�
           ToNextData();

        }
    }
}

//---------------------------------------------------------------------------
// �ꗗ�����{�^��
void __fastcall TForm1::BtnF01Click(TObject *Sender)
{
   //�J�\�[�������ɖ߂�
   CurseBack();
   ExecF1();
}

void ExecF1(void)
{
   if( Form1->edtymd->Focused() || Form1->edttlno->Focused() ){

      // �X�e�[�^�X���b�Z�[�W
      StatBarClear( MSG_01);

     //��̔�d�ް�̧�ق���f�[�^�𒊏o
     iRec_Kd51 = Kd51_Serch01() ;

      if( iRec_Kd51 <= 0 ) {
          StatBarClear( MSG_02);
      }else{
          StatBarClear( " ");
      }

      // �ꗗ�������ʂ̕\����ʂ��J��
      Form2->ShowModal();
  }
}
//---------------------------------------------------------------------------
// �O���{�^��
void __fastcall TForm1::BtnF02Click(TObject *Sender)
{
    //�J�\�[�������ɖ߂�
    CurseBack();

    ToPreData ();
 }

//---------------------------------------------------------------------------
// �����{�^��
void __fastcall TForm1::BtnF03Click(TObject *Sender)
{
    //�J�\�[�������ɖ߂�
    CurseBack();

    ToNextData();
}

//---------------------------------------------------------------------------
//����F4
void __fastcall TForm1::BtnF04Click(TObject *Sender)
{
    //�J�\�[�������ɖ߂�
    CurseBack();
    ExecF4();
}

void ExecF4(void)
{
   if( !HaveSokutei ) return ;

   //����,��,�����A�d�ʂ��v���̏ꍇ
   if( iKomoku == 4 ){
       if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
           iKomoku = 2 ;
           Form1->Rad2->Checked = true ;
       }else{
           iKomoku = 1 ;
           Form1->Rad1->Checked = true ;
       }
   }else if( iKomoku == 1 ) {
       iKomoku =2 ;
       Form1->Rad2->Checked = true ;
   }else if( iKomoku == 2 ) {
       iKomoku =3 ;
       Form1->Rad3->Checked = true ;
   }else if( iKomoku==3 ){
       iKomoku =4 ;
       Form1->Rad4->Checked = true ;
   }
}
//---------------------------------------------------------------------------
//�}�E�X�ō��ڂ�I������ꍇ
void __fastcall TForm1::Rad1Click(TObject *Sender)
{
    int i;
    char tempo[64];

   //����,��,�����A�d�ʂ��v���̏ꍇ
   if( Rad1->Checked == true  ){
       iKomoku = 1 ;
       iChNo = iChNo_Old ;

       if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
            iKomoku  <= 3 && iChNo <= 5 ) {
             BtnF08->Enabled = true ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
       }else
            BtnF08->Enabled = false ;

   }else if( Rad2->Checked == true ) {
       iKomoku =2 ;

       iChNo = iChNo_Old ;

       if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
            iKomoku  <= 3 && iChNo <= 5 ) {
            BtnF08->Enabled = true ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
       }else
            BtnF08->Enabled = false ;

   }else if( Rad3->Checked == true ) {
       iKomoku =3 ;

       iChNo = iChNo_Old ;

       if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
            iKomoku  <= 3 && iChNo <= 5 ) {
            BtnF08->Enabled = true ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
       }else
            BtnF08->Enabled = false ;

   }else if( Rad4->Checked == true ){
       iKomoku =4 ;
       if ( ShareFlag ){

         iChNo_Old = iChNo ;

         //20160728 �d�q�V���̐ؑ֋@�ڑ��ɑΉ�
         //iChNo = 6 ;
         if( iKojoKbn == 0 ){
           //�{�Ђ̏ꍇ�A�]���ʂ�ɏ������s��
           iChNo = 6 ;
         }
         else if( iKojoKbn == 1 ){
           //�L�z�̏ꍇ�A�ؑ֊�Ch5�Ɍq����
           iChNo = 5 ;
         }

         //20160728 �d�q�V���̐ؑ֋@�ڑ��ɑΉ�
         //if(  KikiType == 1  && iKomoku  == 4 && iChNo == 6 ) {
         //if(  KikiType == 1  && iKomoku  == 4 && iChNo == 5 ) {
         if(  KikiType == 1  && iKomoku  == 4 ) {

            Form1->BtnF08->Enabled = false ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));
         }else
           Form1->BtnF08->Enabled = true ;

        // iChNo = iChNo_Old ;

       }else
         Form1->BtnF08->Enabled = false ;
   }


   // ScrollBar�̏����l�ݒ�
   int n;
   for( i=0; i<30; i++ ){

        if( KD51Data[i].SOKUTE_KBN == 1  &&
            KD51Data[i].SOKUTEI_NM > 2  ){
            n=pEdt4[i]->Value ;
            if( n > 3 ){
                pScrl[i]->Position = 3 ;
                pEdt4[i]->Text="3";
                pEdt3[i]->Text = FormatFloat("#0.00", KD51Data[i].SOKUTEI_B[2]);
            }
        }
   }

  for( i=0; i<4; i++ ){
      if( i==iKomoku-1){
          IsEnabledEdt( pEdt1_S[i], 1 );
          IsEnabledEdt( pEdt2_S[i], 1 );

      }else{
          IsEnabledEdt( pEdt1_S[i], 0 );
          IsEnabledEdt( pEdt2_S[i], 0 );
      }
   }

   //��������Q�̏ꍇ
   if( KD51Data[SamplePositionIdx-1].SOKUTEI_NM  > 2 ){

               //�R�ڈȍ~�̌v���f�[�^���۰ق�L���ɂ���
          for(int i=0; i<4; i++){
               if( i== iKomoku-1 ){
                    IsEnabledEdt( pEdt3_S[i], 1 );
                    IsEnabledEdt( pEdt4_S[i], 1 );
                    IsEnabledPnl( pPnl_S[i], 1 );
                    pScrl_S[i]->Enabled = true ;

               }else{
                    IsEnabledEdt( pEdt3_S[i], 0 );
                    IsEnabledEdt( pEdt4_S[i], 0 );
                    IsEnabledPnl( pPnl_S[i], 0 );
                    pScrl_S[i]->Min = 0;
                    pScrl_S[i]->Max = 99;
                    pScrl_S[i]->Position = 0 ;
                    pScrl_S[i]->Enabled = false ;
               }
           }
     }else{

             //�R�ڈȍ~�̌v���f�[�^���۰ق𖳌��ɂ���
           for(int i=0; i<4; i++){

                 IsEnabledEdt( pEdt3_S[i], 0 );
                 IsEnabledEdt( pEdt4_S[i], 0 );
                 pScrl_S[i]->Min = 0;
                 pScrl_S[i]->Max = 99;
                 pScrl_S[i]->Position = 0 ;
                 pScrl_S[i]->Enabled = false ;
           }
     }

    //���ق𑪒�f�[�^���ׂֈړ�
    if( DataNoIdx == 1 ){

       pEdt1_S[iKomoku-1]->SetFocus();
       pEdt1_S[iKomoku-1]->SelectAll();
    }else if( DataNoIdx == 2 ){
       pEdt2_S[iKomoku-1]->SetFocus();
       pEdt2_S[iKomoku-1]->SelectAll();
    }else {
       pEdt3_S[iKomoku-1]->SetFocus();
       pEdt3_S[iKomoku-1]->SelectAll();

    }

}
//---------------------------------------------------------------------------
//��ʈ��
void __fastcall TForm1::BtnF05Click(TObject *Sender)
{

    // �X�e�[�^�X���b�Z�[�W
     StatBarClear(MSG_09);

     Form1->Print();

     // �X�e�[�^�X���b�Z�[�W
     StatBarClear( "  ");

}

//---------------------------------------------------------------------------
//F7 ����
void __fastcall TForm1::BtnF07Click(TObject *Sender)
{
   int  i;
   AnsiString strVal01;
   AnsiString strVal02;
   int HaveSokutei_old ;
   int iKskStart_old ;
   int flag;

   //��������������
   strVal01 = DelSEPA(Form1->edtymd->Text);
   strVal02 = Form1->edttlno->Text;

   if( !strVal01.Length() || !strVal02.Length() ||
       IsNullSpace(strVal01) || IsNullSpace(strVal02) ||
       !edttlno->Value  ) return ;

   //�X�V�����ް����ނ��邩�ǂ����̊m�F���b�Z�[�W
   if( AllDataChg && !Save_Click){
       switch( MessageDlg( MSG_10, mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
                ExecF11();
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                return;
                break;
         }
       AllDataChg = 0;
   }

   // �X�e�[�^�X���b�Z�[�W
   StatBarClear(MSG_01) ;

   HaveSokutei_old = HaveSokutei;
   iKskStart_old = iKskStart;

   HaveSokutei = 0;
   iKskStart = 0 ;

   // ��̔�d�ް�̧�ق����ް��𒊏o  KD51
   //2003.02.06 E.Takase
   flag = 0;
   if ( Kd51_Serch03() != -1 ) {
       switch( MessageDlg( MSG_16, mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
                flag = 1;
                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                return;
                break;
         }

   }
   int iRtn = Kd51_Serch02(flag);
   if( iRtn <= 0 ) {

      if( Save_Click ){
         StatBarClear( " ") ;
         HaveSokutei = HaveSokutei_old ;
         iKskStart =  iKskStart_old ;

      }else{
         // �X�e�[�^�X���b�Z�[�W
         StatBarClear( MSG_02) ;

         //��ʂ̏�����
         SetInit(1) ;
         SetEnabel(0);

         Form1->PageCtrl->ActivePage = Form1->TabSheet1;
         GraphyImg->Canvas->Brush->Color = clMenu;
         GraphyImg->Canvas->FillRect( GraphyImg->ClientRect );
      }
      return;
   }
   //��ʂ̏�����
   SetInit(1) ;
   SetEnabel(0) ;

   // �v���ް�NO
   DataNoIdx = 1 ;

   //�������i��ON, �FON)
   iOption = 1 ;

   // �v���l�̕ύX�����������ǂ����̎w���t���O
   AllDataChg = 0;
   CurSampChg = 0;
   CurDataChg = 0;

   // KD51Data�\���̕ϐ��̏�����
   KD53WFormat();

   // ���藚������������ꍇ   2002/10/28 A.Tamura
   if( CheckBoxRireki->Checked ){

      //���b�gNO�̍ēǂݍ��݁@�@2003/1/23 A.Tamura
      strVal02 = Form1->edttlno->Text;

      //KD53W�����ް��e�[�u���̍쐬
      //int iRec = Kd53W_Create01(KD51Data[0].KENSA_YMD, KD51Data[0].TOLEY_NO, LOTMAX);
	  int iRec = Kd53W_Create01(strVal01, strVal02.ToIntDef(0), LOTMAX);
      if( iRec >0 ){

         //KD53W�����ް�̧�ق�ǂݍ���
         i = Kd53W_Serch01();

      }else{
         StatBarClear( MSG_12) ;
      }

   } else{
   	
      //KD53W�����ް� �폜
      Kd53W_Delete01();

      //KD53W�����ް� �t�H�[�}�b�g
      KD53WFormat();

      char Xstr[50][5];
      double Max[50];
      double Min[50];
      double Val[50];

      // ���p�ϐ��̏�����
      for(i=0; i<LOTMAX*5; i++ ){
         memset( Xstr[i], 0x0, 5 );
         Max[i] = 0.0;
         Min[i] = 0.0;
         Val[i] = 0.0;
      }

      // ���藚�����������Ȃ��̂ő��藚��\����ʂ��N���A���܂��B
      DrawRireki( Form1->GraphyImg, 0, &Xstr[0][0], Max, Min, Val, -1);
//      iOption = 2;
//      ToDrawGraph(1, iOption);
   }

   //�v���ް�������΂����ް��𗚗�̧�قփR�s�[
   if( HaveSokutei ) CopyKD51Data();

   // �w�肵���v���\������ڰNO�Ō�������ں��ނ���ʂփZ�b�g
   flag = 0;
   for( i=0; i<30; i++ ) {

      //������߼޼��NO���Ȃ��̏ꍇ
      if( KD51Data[i].SAMPLE_P == -1 ) {
         // �ް��P�A�ް��Q���۰�
         /*
         IsEnabledEdt( pEdt1[i], 0 );
         IsEnabledEdt( pEdt2[i], 0 );
         IsEnabledPnl( pPnlN[i], 0 );

         //��O�ް����۰�
         IsEnabledEdt( pEdt3[i], 0 );
         IsEnabledEdt( pEdt4[i], 0 );
         IsEnabledScrl(pScrl[i],0 );
         */
      }else{

         //������߼޼��NO������̏ꍇ
         //�ް��P�A�ް��Q�̐ݒ�
         pEdt1[i]->Text =  FormatFloat("#0.00",KD51Data[i].SOKUTEI_B[0] );
         pEdt2[i]->Text =  FormatFloat("#0.00",KD51Data[i].SOKUTEI_B[1] );
         pPnlN[i]->Caption = IntToStr( KD51Data[i].SOKUTEI_NM) ;

         // ��O�ް� �̐ݒ�
         if( KD51Data[i].SOKUTEI_NM > 2 ) {
            pEdt3[i]->Text =  FormatFloat("#0.00",KD51Data[i].SOKUTEI_B[2] );
            pEdt4[i]->Text =  IntToStr(3);
         }

         if(  KD51Data[i].SOKUTE_KBN == 1 ){
            // �ް��P�A�ް��Q���۰�
            IsEnabledEdt( pEdt1[i], 1 );
            IsEnabledEdt( pEdt2[i], 1 );
            IsEnabledPnl( pPnlN[i], 1 );

            // �v�������Q�̏ꍇ
            if( KD51Data[i].SOKUTEI_NM > 2 ) {
               //��O�ް����۰�
               IsEnabledEdt( pEdt3[i], 1 );
               IsEnabledEdt( pEdt4[i], 1 );
               IsEnabledScrl(pScrl[i], 1 );

               // ScrollBar�̏����l�ݒ�
               pScrl[i]->Min = 3;
               pScrl[i]->Max = KD51Data[i].SOKUTEI_NM;
               pScrl[i]->Position = 3 ;

            }

            //�ŏ��v�����R�[�h
            if( flag == 0 && HaveSokutei){
               flag=1;
               SamplePositionIdx = i+1 ;
               iFirstPosition = SamplePositionIdx ;
            }

            iLastPosition = KD51Data[i].SAMPLE_P ;
         }else{
            // �ް��P�A�ް��Q���۰�
            /*
            IsEnabledEdt( pEdt1[i], 0 );
            IsEnabledEdt( pEdt2[i], 0 );
            IsEnabledPnl( pPnlN[i], 0 );

            //��O�ް����۰�
            IsEnabledEdt( pEdt3[i], 0 );
            IsEnabledEdt( pEdt4[i], 0 );
            IsEnabledScrl(pScrl[i],0 );
            */
         }
      }
   }

   //���l���q���g�ɃZ�b�g 2002/11/08 E.Takase
   SetMEMO();

   if( HaveSokutei ){

      //��ʉ������݂�L���ɂ���
      SetEnabel(1) ;

      //���薾�׍��ږ��̐ݒ�
      if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
         Rad1->Caption ="   ��  ��" ;
         Rad2->Caption ="�@ �O  �a" ;
         Rad3->Caption ="   ��  ��" ;
         Rad4->Caption ="   �d  ��" ;
         iKomoku = 2;
         Rad2->Checked = true ;

         if( Rad2->Enabled == false && iKomoku == 2 ) Rad2->Enabled = true ;
         if( Rad1->Enabled == true ) Rad1->Enabled = false ;
      }else if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){ //�R���~�̏ꍇ 2002/11/02 E.Takase
         Rad1->Caption ="   ��  �a" ;
         Rad2->Caption ="�@ �O  �a" ;
         Rad3->Caption ="   ��  ��" ;
         Rad4->Caption ="   �d  ��" ;

         if( Rad1->Enabled==false) Rad1->Enabled = true ;
         if( Rad2->Enabled==false) Rad2->Enabled = true ;
         iKomoku =1 ;
         Rad1->Checked = true ;
      }else{
         Rad1->Caption ="   ��  ��" ;
         Rad2->Caption ="�@  ��" ;
         Rad3->Caption ="   ��  ��" ;
         Rad4->Caption ="   �d  ��" ;

         if( Rad1->Enabled==false) Rad1->Enabled = true ;
         if( Rad2->Enabled==false) Rad2->Enabled = true ;
         iKomoku =1 ;
         Rad1->Checked = true ;
      }

      if( Rad3->Enabled==false) Rad3->Enabled = true ;
      if( Rad4->Enabled==false) Rad4->Enabled = true ;

      //�ŏ��v���f�[�^����ʂփZ�b�g
      pEdt1[SamplePositionIdx-1]->SetFocus();

      DisplayInfo();

      //�ް��ް����̊���ں��ނ��X�V����ꍇ�A�ް��ް�����ǂݍ���
      //�ް����K�i�͈͓����ǂ����̃`�F�b�N
      SetRed(1) ;

      //�v����Ƃ��n�߂�
      iKskStart = 1 ;

   }else{
      Form1->PageCtrl->ActivePage = Form1->TabSheet1;
      GraphyImg->Canvas->Brush->Color = clMenu;
      GraphyImg->Canvas->FillRect( GraphyImg->ClientRect );
      SetEnabel(2) ;
   }

   // �X�e�[�^�X���b�Z�[�W
   StatBarClear("  ") ;

}
//F8  CH�؂�ւ�
void __fastcall TForm1::BtnF08Click(TObject *Sender)
{
    //�J�\�[�������ɖ߂�
    CurseBack();

    ExecF8();
}
void ExecF8()
{
    char tempo[64];

    if ( ShareFlag && ( KikiType == 1 || KikiType == 2 ) &&
         iKomoku  <= 3 && iChNo <= 5 ) {

            // �`���l���ԍ��̐ݒ�
            if ( iChNo < 5)
                 iChNo++;
            else
                 iChNo = 1;

            iChNo_Old = iChNo ;

            sprintf(tempo, "CONNECT %d", iChNo);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));

            // �X�e�[�^�X���b�Z�[�W
            //sprintf(tempo, "�`���l���ԍ��F %d", iChNo);
            //StatBarClear(tempo) ;


     }
     // iKomoku == 4: Connect 6���Œ�

}
//---------------------------------------------------------------------------

// F10 Option
void __fastcall TForm1::BtnF10Click(TObject *Sender)
{

    //�J�\�[�������ɖ߂�
    CurseBack();

    ExecF10();

}
void ExecF10(void)
{
     // iOption == 1  ���藚�����
     // iOPtion == 2  �H���\�͍��
     // iOption == 3  ���ABeep, �F --> OFF

    if( !HaveSokutei ) return ;

    if( iOption == 3 ){
       iOption = 1 ;
     }else{
       iOption += 1;
     }

     if( iOption == 1 ){
        //���藚�����
        Form1->PageCtrl->Visible = true ;

        Form1->PageCtrl->ActivePage = Form1->TabSheet1;
        //StatBarClear("���藚�� �i��ON, �FON)");

        // ��ʐF�̃��Z�b�g
        SetRed(2);
     }else if( iOption == 2 )
     {
        // �H���\�͍��
        Form1->PageCtrl->Visible = true ;
        Form1->PageCtrl->ActivePage = Form1->TabSheet2;
        //StatBarClear("�H���\�� �i��ON, �FON)");

        // ��ʐF�̃��Z�b�g
        SetRed(2) ;
     }else if( iOption == 3 )
     {
        //���̈���N���A
        Form1->PageCtrl->Visible = false ;
        //StatBarClear("���Ȃ��i��OFF, �FOFF)");

        // ��ʐF�̃��Z�b�g
        ClearRed();
     }

     //�������ƍH���\�͐}
     ToDrawGraph(SamplePositionIdx, iOption);

}
//---------------------------------------------------------------------------
// F11 �ۑ�
void __fastcall TForm1::BtnF11Click(TObject *Sender)
{
  if( !HaveSokutei ) return ;

    //�v�������ް���ۑ�����
   ExecF11();

   Save_Click = 1;

   //�����ڰNO���L��΁A�����ڰNO���ް��������I�ɉ�ʂփZ�b�g
   BtnF07Click(Sender);

   //�J�[�\�����u�ۑ��v�{�^���փZ�b�g
   if( BtnF11->Font->Color == clRed )
       BtnF12->SetFocus();
   Save_Click = 0;

}
void ExecF11(void)
{
    if( !HaveSokutei ) return ;

     // �X�e�[�^�X���b�Z�[�W
     StatBarClear(MSG_04);

    // �ް���̧��KD51�AKd52�֏�������
    Kd51_Update01();

    //�����ް����X�V�����ꍇ�̃t���O�̃N���A
    AllDataChg = 0;
    CurSampChg = 0;
    CurDataChg = 0;
    Update_err = 0;

    // �X�e�[�^�X���b�Z�[�W
    StatBarClear( " ") ;
}
//---------------------------------------------------------------------------
// F12 �߂�
void __fastcall TForm1::BtnF12Click(TObject *Sender)
{

   Close();

}

//---------------------------------------------------------------------------
void __fastcall TForm1::edtymdKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       // �X�e�[�^�X���b�Z�[�W
     if(SBr1->SimpleText != ""){
        SBr1->SimpleText = "";
        SBr1->Update();
     }
     switch(Key)
     {
         case VK_F1:  ExecF1();               break;
         case VK_F2:  ToPreData();            break;
         case VK_F3:  ToNextData();           break;
         case VK_F4:  ExecF4();               break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F7:
                 //�������Ƀt�H�[�J�X������ꍇ�A�������s
                 BtnF07Click(Sender);
                 break;
         case VK_F8: ExecF8();               break;
         case VK_F10:
                      Key = 0;
                      ExecF10();
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         case VK_RETURN:

                      //������
                      if( edtymd->Focused()){
                           edttlno->SetFocus();
                          break;
                       }

                       if( edttlno->Focused() || CheckBoxRireki->Focused() ){
                           BtnF07Click( Sender);

                          break;
                       }

                break;

     }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       // �X�e�[�^�X���b�Z�[�W
     if(SBr1->SimpleText != ""){
        SBr1->SimpleText = "";
        SBr1->Update();
     }
     switch(Key)
     {
         case VK_F1:  ExecF1();               break;
         case VK_F2:  ToPreData();            break;
         case VK_F3:  ToNextData();           break;
         case VK_F4:  ExecF4();               break;
         case VK_F5:  BtnF05Click(Sender);    break;
         case VK_F6:  BtnF06Click(Sender);    break;
         case VK_F7:
              //�������ȊO�Ƀt�H�[�J�X������ꍇ�A�������Ƀt�H�[�J�X���Z�b�g
              edtymd->SetFocus();
              break;
         case VK_F8: ExecF8();               break;
         case VK_F10:
                      Key = 0;
                      ExecF10();
                      break;
         case VK_F11: BtnF11Click(Sender);    break;
         case VK_F12: BtnF12Click(Sender);    break;

         case VK_RETURN:
                       //�f�[�^�v����
                        if( !BtnF01->Focused() && !BtnF02->Focused() &&
                            !BtnF03->Focused() && !BtnF04->Focused() &&
                            !BtnF05->Focused() && !BtnF06->Focused() &&
                            !BtnF07->Focused() && !BtnF08->Focused() &&
                            !BtnF09->Focused() && !BtnF10->Focused() &&
                            !BtnF11->Focused() && !BtnF12->Focused() ){
                             ToNextData();
                        }
                break;
         case VK_UP:
                break ;
         case VK_LEFT:

                ToPreData();
                break;
         case VK_DOWN:
                break ;
         case VK_RIGHT:

                ToNextData();
                break;


     }
}


//------------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
     edtymd->SetFocus();

     //������߼޼��NO�̏�����
     SamplePositionIdx = 1;

     // �v���ް�NO
     DataNoIdx = 1 ;

     //�v����Ǝn�߂邩�ǂ����̎w���t���O
     iKskStart = 0 ;

     // �v���l�̕ύX�����������ǂ����̎w���t���O
     AllDataChg = 0;
     CurSampChg = 0;
     CurDataChg = 0;

     //�S���Җ��A���喼�Ȃǂ���ʂփZ�b�g
     Pnl1->Caption = BUMO_COD ;
     Pnl2->Caption = BUMO_NAM ;
     Pnl3->Caption = IntToStr(USER_COD );
     Pnl4->Caption = USER_NAM ;

     //20161128 Y.Onishi
     //PC6�̏ꍇ�A�G���[���b�Z�[�W���o���Ȃ�
     //if (ret_232 < 0) {
     //       Beep();
     //       StatBarClear(MSG_11) ;
     //}
     if (KikiType != 6) {
        if (ret_232 < 0) {
            Beep();
            StatBarClear(MSG_11) ;
        }
     }
}

//--------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  char DirName[256], FileName[256], tempo[64];

      WriteLog("TKS15.exe�N��");

      // �@��ԍ���Ǎ���
      GetCurrentDirectory(256,DirName);
      sprintf(FileName, "%s\\Tks.ini", DirName);
      GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, FileName);							//Seed�l
      KikiType = atoi(tempo);
      if ( KikiType <= 0 || KikiType > 4)
          ret_232 = -1;
         // StatBarClear(MSG_00) ;

      ShareFlag = 0;
      if (iRS232C) {
         if (KikiType == 1 || KikiType == 2) {
            ShareFlag = 1;
         }
      }

      // �H��敪��ǂݍ���
      GetPrivateProfileString("MAIN", "KOJOKBN", "", tempo, 64, FileName);
      iKojoKbn = atoi(tempo);

     // �V�F�A�������쐬
     if (ShareFlag) {

        ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS1", 1);
        ret_232 = SharedMemory_Open(Handle, "SHARE_TRIS2", 2);

        if (ret_232 < 0) {
           ShareFlag = 0;
        }else{

           //RS232C�ڑ��t���O���P�ɐݒ�
           iShareFlag = 1;

           sprintf(tempo, "CONNECT %d", iChNo);
           SharedMemory_Write(1, 0, tempo, strlen(tempo));
        }
     }

	  //RS232C �ǂݍ��݃t���O ������
      RSInputFlag = 0;

      // �ް��x�[�X�Ƃ̐ڑ�
      Database1->Open() ;

      // ��ʂɊe���۰�ID��ۑ�����
      SaveCtlID() ;

      // ��ʂ��J���ۂ̏����l�ް��̐ݒ�
      SetInit(0) ;

      // �v���\����A�ڰNO�A�ꗗ��������, �����������A�����ɂ���
      SetEnabel (0);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::InitEdt(TNumberEdit *P_Edit, AnsiString Str)
{
       P_Edit->Text = Str ;
}
//--------------------------------------------------------------------------
void __fastcall TForm1::InitPnl(TPanel *P_Pnl, AnsiString Str)
{
        P_Pnl->Caption = Str ;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::SetInit(int flag)
{
     int i ;

      // ���C����ʂ̏�����
      if( flag == 0 ){

         // �v���\��N����
         edtymd->Text = FormatDateTime("yyyy/mm/dd",Date());

         // �g���[NO
         edttlno->Text ="1";
      }


      // ������߼޼��NO�y�ё����N
      for( i=0; i<30; i++ ){
          InitEdt(pEdt1[i], "0.0");
          InitEdt(pEdt2[i], "0.0");
          InitEdt(pEdt3[i], "0.0");
          InitEdt(pEdt4[i], "0");
          InitPnl(pPnlN[i], "0") ;
      }

      //�������ُ��̕\��
      InitPnl(Pnl5, "0.00") ;
      InitPnl(Pnl6, "0.00") ;
      InitPnl(Pnl7, " ") ;
      InitPnl(Pnl8, " ") ;
      InitPnl(Pnl9, " ") ;
      InitPnl(Pnl10, " ") ;
      InitPnl(Pnl11, " ") ;
      InitPnl(Pnl12, " ") ;

      //ScrollBar�̏����l�̐ݒ�
      for( i=0; i<30; i++ )
      {
        pScrl[i]->Min = 0;
        pScrl[i]->Max = 99;
        pScrl[i]->Position =0;
      }

      //�H���\�ͺ��۰ق̃N���A
      InitPnl(Pnl21, "0.00") ;
      InitPnl(Pnl22, "0.00") ;
      InitPnl(Pnl23, "0.000") ;
      InitPnl(Pnl24, "0") ;

      InitPnl(Pnl31, "0.00000") ;
      InitPnl(Pnl32, "0.00000") ;
      InitPnl(Pnl33, "0.00") ;

      InitPnl(Pnl41, "0.00") ;
      InitPnl(Pnl42, "0.000") ;
      InitPnl(Pnl43, "0.000") ;

      //���薾��
      for( i=0; i<4; i++ ){
        InitEdt(pEdt1_S[i], "0.000");
        InitEdt(pEdt2_S[i], "0.000");
        InitEdt(pEdt3_S[i], "0.000");

        InitEdt(pEdt4_S[i], "0");
        InitPnl(pPnl_S[i], "0") ;

        pScrl_S[i]->Min = 0;
        pScrl_S[i]->Max = 99;
        pScrl_S[i]->Position =0;
      }
}

//--------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledPnl(TPanel *P_Pnl, int flag)
{
       // �p�l�����݂�Enabled or Unenabled
       //  flag == 1   true    flag == 0  false
       if( flag == 1 ){
           P_Pnl->Enabled = true ;
       }else {
           P_Pnl->Enabled = false ;
        }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledEdt(TNumberEdit *P_Edit, int flag)
{
      // Edit���݂�Enabled or Unenabled
      //  flag == 1   true    flag == 0  false
       if( flag == 1 ){
           P_Edit->Enabled = true ;
           P_Edit->Color = clWindow;
       }else {
           P_Edit->Enabled = false ;
           P_Edit->Color = 0x00E0E0E0;
      }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::IsEnabledScrl(TScrollBar *P_Scrl, int flag)
{
       // Scroll���݂�Enabled or Unenabled
       //  flag == 1   true    flag == 0  false
       if( flag == 1 )
           P_Scrl->Enabled = true ;
       else
           P_Scrl->Enabled = false ;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetEnabel(int flag )
{
  int i;

  if( flag == 0 ){

      //��ʂ��J�����ɁA���ͺ��۰ق𖳌��ɂ���
      for( i=0; i<30; i++ )
      {
       IsEnabledEdt( pEdt1[i], 0 );
       IsEnabledEdt( pEdt2[i], 0 );
       IsEnabledEdt( pEdt3[i], 0 );
       IsEnabledEdt( pEdt4[i], 0 );
       IsEnabledPnl( pPnlP[i], 0 );
       IsEnabledPnl( pPnlN[i], 0 );
       IsEnabledScrl( pScrl[i],0 );
       }

       //�v�����׺��۰�
       for( i=0; i<4; i++ ){
            IsEnabledEdt( pEdt1_S[i], 0 );
            IsEnabledEdt( pEdt2_S[i], 0 );
            IsEnabledEdt( pEdt3_S[i], 0 );
            IsEnabledEdt( pEdt4_S[i], 0 );
            IsEnabledPnl( pPnl_S[i], 0 );
            IsEnabledScrl( pScrl_S[i],0 );
       }
       Rad1->Enabled = false ;
       Rad2->Enabled = false ;
       Rad3->Enabled = false ;
       Rad4->Enabled = false ;

       //�O���A�����A������݂Ȃǂ𖳌��ɂ���
       BtnF02->Enabled = false ;
       BtnF03->Enabled = false ;
       BtnF04->Enabled = false ;
      // BtnF06->Enabled = false ;
      // BtnF09->Enabled = false ;
       BtnF10->Enabled = false ;
       BtnF11->Enabled = false ;
  }else if( flag == 1 ){

         //�O���A�����A������݂Ȃǂ�L���ɂ���
         if( BtnF02->Enabled==false)  BtnF02->Enabled = true ;
         if( BtnF03->Enabled==false)  BtnF03->Enabled = true ;
         if( BtnF04->Enabled==false)  BtnF04->Enabled = true ;
        // if( BtnF06->Enabled==false)  BtnF06->Enabled = true ;
        // if( BtnF09->Enabled==false) BtnF09->Enabled = true ;
         if( BtnF10->Enabled==false) BtnF10->Enabled = true ;
         if( BtnF11->Enabled==false) BtnF11->Enabled = true ;
  }else{
         //�O���A�����A������݂Ȃǂ𖳌��ɂ���
         if( BtnF02->Enabled==true) BtnF02->Enabled = false ;
         if( BtnF03->Enabled==true) BtnF03->Enabled = false ;
         if( BtnF04->Enabled==true) BtnF04->Enabled = false ;
        // if( BtnF06->Enabled==true) BtnF06->Enabled = false ;
        // if( BtnF09->Enabled==true) BtnF09->Enabled = false ;
         if( BtnF10->Enabled==true) BtnF10->Enabled = false ;
         if( BtnF11->Enabled==true) BtnF11->Enabled = false ;
  }

  if( ShareFlag && ( KikiType == 1 || KikiType == 2 ) ) {
       BtnF08->Enabled = true ;
  }else
       BtnF08->Enabled = false ;


}

//---------------------------------------------------------------------------
void __fastcall TForm1:: OnEditEnter( int spflag, int dtflag, TNumberEdit *pEdit )
{

    int pos, i;
 //   int SamplePositionIdx_old;

    // spflag :  ������߼޼��NO
    // dtflag :  ��»�����߼޼��NO�ɑ΂��Ă��ް�NO

    if( CurBackFlg ) return ;

     //�v���f�[�^���w���t���O
    CurField = 2;

    //�ꗗ�������݂𖳌��ɂ���
    BtnF01->Enabled = false ;

    //���Ķ��وʒu�̔w�i�F�����F�֖߂�
    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
    }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
    }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
    }

    // �ް�NO�̐ݒ�
    if( dtflag == 1 || dtflag == 2 ){
       DataNoIdx = dtflag;
    }else {
       DataNoIdx = pEdit->Value;
    }

    // ����ك|�W�V�����ԍ��̐ݒ�
    if( spflag != SamplePositionIdx ){

        //���Ļ�����߼޼�݃f�[�^�𗚗�̧�ق֒ǉ�
        if( CurSampChg ){
          AddKd53W();
          CurSampChg = 0;}

        SamplePositionIdx = spflag ;

       //���薾�׍��ږ��̐ݒ�
       if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
          Rad1->Caption ="   ��  ��" ;
          Rad2->Caption ="�@ �O  �a" ;
          Rad3->Caption ="   ��  ��" ;
          Rad4->Caption ="   �d  ��" ;
          if( iKomoku == 1 ){
              iKomoku = 2;
              Rad2->Checked = true ;
          }
          if( Rad2->Enabled == false && iKomoku == 2 ) Rad2->Enabled = true ;
          if( Rad1->Enabled == true ) Rad1->Enabled = false ;
       }else if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 5 ){ //�R���~�̏ꍇ 2002/11/02 E.Takase
          Rad1->Caption ="   ��  �a" ;
          Rad2->Caption ="�@ �O  �a" ;
          Rad3->Caption ="   ��  ��" ;
          Rad4->Caption ="   �d  ��" ;
          if( Rad1->Enabled == false ) Rad1->Enabled = true ;
       }else{
          Rad1->Caption ="   ��  ��" ;
          Rad2->Caption ="�@  ��" ;
          Rad3->Caption ="   ��  ��" ;
          Rad4->Caption ="   �d  ��" ;
          if( Rad1->Enabled == false ) Rad1->Enabled = true ;
       }

        DisplayInfo();
    }

   ToDrawGraph(SamplePositionIdx, iOption);

    //����f�[�^���ׂ̕\��
     if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 ){
        pEdt1_S[0]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[0] );
        pEdt2_S[0]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[1] );
     }else{
        pEdt1_S[0]->Text = "0.000";
        pEdt2_S[0]->Text = "0.000";
     }

     pEdt1_S[1]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[0] );
     pEdt2_S[1]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[1] );
     pEdt1_S[2]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[0] );
     pEdt2_S[2]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[1] );
     pEdt1_S[3]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[0] );
     pEdt2_S[3]->Text =  FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[1] );

     for( i=0; i<4; i++ ){
      if( i==iKomoku-1){
          IsEnabledEdt( pEdt1_S[i], 1 );
          IsEnabledEdt( pEdt2_S[i], 1 );

      }else{
          IsEnabledEdt( pEdt1_S[i], 0 );
          IsEnabledEdt( pEdt2_S[i], 0 );
      }
     }

    //��������Q�̏ꍇ
    if( KD51Data[SamplePositionIdx-1].SOKUTEI_NM  > 2 ){

            //3�ڈȍ~�̃f�[�^NO
             pos = pEdt4[SamplePositionIdx-1]->Value ;

            //ScrollBar�̏�����
            for(  i=0; i<4; i++){

                if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 && i== 0 )  continue ;
                 pScrl_S[i]->Min = 0;
                 pScrl_S[i]->Max = 99;

                 // ��̔�d�ɍ��킹�č��ږ��ׂ�ScrollBar��ݒ肷��
                 pScrl_S[i]->Min = 3;
                 pScrl_S[i]->Max = KD51Data[SamplePositionIdx-1].SOKUTEI_NM;
                 pScrl_S[i]->Position = pos ;

            }

             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[pos-1] );
             else
                 pEdt3_S[0]->Text = "0.00" ;

             pEdt3_S[1]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[pos-1] );
             pEdt3_S[2]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[pos-1] );
             pEdt3_S[3]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[pos-1] );


             for( i=0; i<4; i++ ){

                if(  KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 && i== 0 ){
                     pEdt4_S[i]->Text = "0" ;
                     pPnl_S[i]->Caption = "0" ;
                }else {
                    pEdt4_S[i]->Text = IntToStr(pos) ;

                    //������̐ݒ�
                    pPnl_S[i]->Caption = IntToStr( KD51Data[SamplePositionIdx-1].SOKUTEI_NM );
                }

               //�R�ڈȍ~�̌v���f�[�^���۰ق�L���ɂ���
               if( i== iKomoku-1 ){
                    IsEnabledEdt( pEdt3_S[i], 1 );
                    IsEnabledEdt( pEdt4_S[i], 1 );
                    IsEnabledPnl( pPnl_S[i], 1 );
                    pScrl_S[i]->Enabled = true ;

               }else{
                    IsEnabledEdt( pEdt3_S[i], 0 );
                    IsEnabledEdt( pEdt4_S[i], 0 );
                    IsEnabledPnl( pPnl_S[i], 0 );
                    pScrl_S[i]->Enabled = false ;
               }
            }

     }else{

             //�R�ڈȍ~�̌v���f�[�^���۰ق𖳌��ɂ���
           for(int i=0; i<4; i++){

                 if( i== 3 )
                     pEdt3_S[i]->Text = "0.000" ;
                 else
                     pEdt3_S[i]->Text = "0.00" ;

                 pEdt4_S[i]->Text = "0" ;
                 if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                     pPnl_S[i]->Caption = IntToStr( KD51Data[SamplePositionIdx-1].SOKUTEI_NM ) ;

                 IsEnabledEdt( pEdt3_S[i], 0 );
                 IsEnabledEdt( pEdt4_S[i], 0 );
                 pScrl_S[i]->Min = 0;
                 pScrl_S[i]->Max = 99;
                 pScrl_S[i]->Position = 0 ;
                 pScrl_S[i]->Enabled = false ;
           }
     }

    //���ق𑪒�f�[�^���ׂֈړ�
    if( DataNoIdx == 1 ){

       pEdt1_S[iKomoku-1]->SetFocus();
       pEdt1_S[iKomoku-1]->SelectAll();
    }else if( DataNoIdx == 2 ){
       pEdt2_S[iKomoku-1]->SetFocus();
       pEdt2_S[iKomoku-1]->SelectAll();
    }else {
       pEdt3_S[iKomoku-1]->SetFocus();
       pEdt3_S[iKomoku-1]->SelectAll();

    }

    CurDataChg = 0;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::edttlnoEnter(TObject *Sender)
{
      if( CurBackFlg ) return ;

       //����������
      CurField = 1;
      BtnF01->Enabled = true ;

      if(  edtymd->Focused() ) ymdtl_flg = 1;
      if(  edttlno->Focused()) ymdtl_flg = 2;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::EdtV1Enter(TObject *Sender)
{
    if( CurBackFlg ) return ;

    BtnF01->Enabled = false ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clWindow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clWindow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clWindow;
     }

    // �ް�NO�̐ݒ�
    if( pEdt1_S[iKomoku-1]->Focused() )
        DataNoIdx = 1;
    else if( pEdt2_S[iKomoku-1]->Focused() )
        DataNoIdx = 2;
    else if( pEdt3_S[iKomoku-1]->Focused() ||
             pEdt4_S[iKomoku-1]->Focused() ||
             pScrl_S[iKomoku-1]->Focused() )   DataNoIdx= pEdt4_S[iKomoku-1]->Value ;

    if( DataNoIdx == 1 ){
       pEdt1[SamplePositionIdx-1]->Color = clYellow;
     }else if( DataNoIdx == 2 ){
       pEdt2[SamplePositionIdx-1]->Color = clYellow;
     }else {
       pEdt3[SamplePositionIdx-1]->Color = clYellow;
     }

}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_1Enter(TObject *Sender)
{
          OnEditEnter(1,1,Edt01_4);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_2Enter(TObject *Sender)
{

    OnEditEnter(1,2,Edt01_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_3Enter(TObject *Sender)
{
    OnEditEnter(1,3,Edt01_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt01_4Enter(TObject *Sender)
{
    OnEditEnter(1,4,Edt01_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Enter(TObject *Sender)
{
    OnEditEnter(1,5,Edt01_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_1Enter(TObject *Sender)
{
    OnEditEnter(2,1,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_2Enter(TObject *Sender)
{
    OnEditEnter(2,2,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_3Enter(TObject *Sender)
{
    OnEditEnter(2,3,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt02_4Enter(TObject *Sender)
{
    OnEditEnter(2,4,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar2Enter(TObject *Sender)
{
    OnEditEnter(2,5,Edt02_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_1Enter(TObject *Sender)
{
    OnEditEnter(3,1,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_2Enter(TObject *Sender)
{
    OnEditEnter(3,2,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_3Enter(TObject *Sender)
{
    OnEditEnter(3,3,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt03_4Enter(TObject *Sender)
{
    OnEditEnter(3,4,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar3Enter(TObject *Sender)
{
    OnEditEnter(3,5,Edt03_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_1Enter(TObject *Sender)
{
    OnEditEnter(4,1,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_2Enter(TObject *Sender)
{
    OnEditEnter(4,2,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_3Enter(TObject *Sender)
{
    OnEditEnter(4,3,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt04_4Enter(TObject *Sender)
{
    OnEditEnter(4,4,Edt04_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar4Enter(TObject *Sender)
{
    OnEditEnter(4,5,Edt04_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_1Enter(TObject *Sender)
{
     OnEditEnter(5,1,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_2Enter(TObject *Sender)
{
     OnEditEnter(5,2,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_3Enter(TObject *Sender)
{
     OnEditEnter(5,3,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt05_4Enter(TObject *Sender)
{
     OnEditEnter(5,4,Edt05_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar5Enter(TObject *Sender)
{
     OnEditEnter(5,5,Edt05_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt06_1Enter(TObject *Sender)
{
     OnEditEnter(6,1,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_2Enter(TObject *Sender)
{
     OnEditEnter(6,2,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_3Enter(TObject *Sender)
{
     OnEditEnter(6,3,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt06_4Enter(TObject *Sender)
{
     OnEditEnter(6,4,Edt06_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar6Enter(TObject *Sender)
{
     OnEditEnter(6,5,Edt06_4);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edt07_1Enter(TObject *Sender)
{
      OnEditEnter(7,1,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_2Enter(TObject *Sender)
{
       OnEditEnter(7,2,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_3Enter(TObject *Sender)
{
       OnEditEnter(7,3,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt07_4Enter(TObject *Sender)
{
      OnEditEnter(7,4,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar7Enter(TObject *Sender)
{
       OnEditEnter(7,5,Edt07_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_1Enter(TObject *Sender)
{
       OnEditEnter(8,1,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_2Enter(TObject *Sender)
{
       OnEditEnter(8,2,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_3Enter(TObject *Sender)
{
       OnEditEnter(8,3,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt08_4Enter(TObject *Sender)
{
       OnEditEnter(8,4,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar8Enter(TObject *Sender)
{
       OnEditEnter(8,5,Edt08_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_1Enter(TObject *Sender)
{
        OnEditEnter(9,1,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_2Enter(TObject *Sender)
{
        OnEditEnter(9,2,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_3Enter(TObject *Sender)
{
        OnEditEnter(9,3,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt09_4Enter(TObject *Sender)
{
        OnEditEnter(9,4,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar9Enter(TObject *Sender)
{
        OnEditEnter(9,5,Edt09_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_1Enter(TObject *Sender)
{
        OnEditEnter(10,1,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_2Enter(TObject *Sender)
{
         OnEditEnter(10,2,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_3Enter(TObject *Sender)
{
        OnEditEnter(10,3,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt10_4Enter(TObject *Sender)
{
        OnEditEnter(10,4,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar10Enter(TObject *Sender)
{
        OnEditEnter(10,5,Edt10_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_1Enter(TObject *Sender)
{
        OnEditEnter(11,1,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_2Enter(TObject *Sender)
{
         OnEditEnter(11,2,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_3Enter(TObject *Sender)
{
        OnEditEnter(11,3,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt11_4Enter(TObject *Sender)
{
        OnEditEnter(11,4,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar11Enter(TObject *Sender)
{
        OnEditEnter(11,5,Edt11_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_1Enter(TObject *Sender)
{
        OnEditEnter(12,1,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_2Enter(TObject *Sender)
{
        OnEditEnter(12,2,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_3Enter(TObject *Sender)
{
       OnEditEnter(12,3,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt12_4Enter(TObject *Sender)
{
       OnEditEnter(12,4,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar12Enter(TObject *Sender)
{
       OnEditEnter(12,5,Edt12_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_1Enter(TObject *Sender)
{
       OnEditEnter(13,1,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_2Enter(TObject *Sender)
{
       OnEditEnter(13,2,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_3Enter(TObject *Sender)
{
       OnEditEnter(13,3,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt13_4Enter(TObject *Sender)
{
       OnEditEnter(13,4,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar13Enter(TObject *Sender)
{
       OnEditEnter(13,5,Edt13_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_1Enter(TObject *Sender)
{
       OnEditEnter(14,1,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_2Enter(TObject *Sender)
{
       OnEditEnter(14,2,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_3Enter(TObject *Sender)
{
       OnEditEnter(14,3,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt14_4Enter(TObject *Sender)
{
       OnEditEnter(14,4,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar14Enter(TObject *Sender)
{
       OnEditEnter(14,5,Edt14_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_1Enter(TObject *Sender)
{
       OnEditEnter(15,1,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_2Enter(TObject *Sender)
{
       OnEditEnter(15,2,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_3Enter(TObject *Sender)
{
       OnEditEnter(15,3,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt15_4Enter(TObject *Sender)
{
       OnEditEnter(15,4,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar15Enter(TObject *Sender)
{
       OnEditEnter(15,5,Edt15_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_1Enter(TObject *Sender)
{
       OnEditEnter(16,1,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_2Enter(TObject *Sender)
{
       OnEditEnter(16,2,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_3Enter(TObject *Sender)
{
       OnEditEnter(16,3,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt16_4Enter(TObject *Sender)
{
       OnEditEnter(16,4,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar16Enter(TObject *Sender)
{
       OnEditEnter(16,5,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_1Enter(TObject *Sender)
{
       OnEditEnter(17,1,Edt16_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_2Enter(TObject *Sender)
{
       OnEditEnter(17,2,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_3Enter(TObject *Sender)
{
       OnEditEnter(17,3,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt17_4Enter(TObject *Sender)
{
       OnEditEnter(17,4,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar17Enter(TObject *Sender)
{
       OnEditEnter(17,5,Edt17_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_1Enter(TObject *Sender)
{
       OnEditEnter(18,1,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_2Enter(TObject *Sender)
{
       OnEditEnter(18,2,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_3Enter(TObject *Sender)
{
       OnEditEnter(18,3,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt18_4Enter(TObject *Sender)
{
       OnEditEnter(18,4,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar18Enter(TObject *Sender)
{
       OnEditEnter(18,5,Edt18_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_1Enter(TObject *Sender)
{
       OnEditEnter(19,1,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_2Enter(TObject *Sender)
{
       OnEditEnter(19,2,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_3Enter(TObject *Sender)
{
       OnEditEnter(19,3,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt19_4Enter(TObject *Sender)
{
       OnEditEnter(19,4,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar19Enter(TObject *Sender)
{
       OnEditEnter(19,5,Edt19_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_1Enter(TObject *Sender)
{
       OnEditEnter(20,1,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_2Enter(TObject *Sender)
{
       OnEditEnter(20,2,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_3Enter(TObject *Sender)
{
       OnEditEnter(20,3,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt20_4Enter(TObject *Sender)
{
       OnEditEnter(20,4,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar20Enter(TObject *Sender)
{
       OnEditEnter(20,5,Edt20_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_1Enter(TObject *Sender)
{
       OnEditEnter(21,1,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_2Enter(TObject *Sender)
{
        OnEditEnter(21,2,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_3Enter(TObject *Sender)
{
       OnEditEnter(21,3,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt21_4Enter(TObject *Sender)
{
       OnEditEnter(21,4,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar21Enter(TObject *Sender)
{
       OnEditEnter(21,5,Edt21_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_1Enter(TObject *Sender)
{
       OnEditEnter(22,1,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_2Enter(TObject *Sender)
{
       OnEditEnter(22,2,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_3Enter(TObject *Sender)
{
       OnEditEnter(22,3,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt22_4Enter(TObject *Sender)
{
       OnEditEnter(22,4,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar22Enter(TObject *Sender)
{
       OnEditEnter(22,5,Edt22_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_1Enter(TObject *Sender)
{
       OnEditEnter(23,1,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_2Enter(TObject *Sender)
{
       OnEditEnter(23,2,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_3Enter(TObject *Sender)
{
       OnEditEnter(23,3,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt23_4Enter(TObject *Sender)
{
       OnEditEnter(23,4,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar23Enter(TObject *Sender)
{
       OnEditEnter(23,5,Edt23_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_1Enter(TObject *Sender)
{
       OnEditEnter(24,1,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_2Enter(TObject *Sender)
{
       OnEditEnter(24,2,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_3Enter(TObject *Sender)
{
       OnEditEnter(24,3,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt24_4Enter(TObject *Sender)
{
       OnEditEnter(24,4,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar24Enter(TObject *Sender)
{
       OnEditEnter(24,5,Edt24_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_1Enter(TObject *Sender)
{
       OnEditEnter(25,1,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_2Enter(TObject *Sender)
{
       OnEditEnter(25,2,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_3Enter(TObject *Sender)
{
       OnEditEnter(25,3,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt25_4Enter(TObject *Sender)
{
       OnEditEnter(25,4,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar25Enter(TObject *Sender)
{
       OnEditEnter(25,5,Edt25_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_1Enter(TObject *Sender)
{
       OnEditEnter(26,1,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_2Enter(TObject *Sender)
{
       OnEditEnter(26,2,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_3Enter(TObject *Sender)
{
       OnEditEnter(26,3,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt26_4Enter(TObject *Sender)
{
       OnEditEnter(26,4,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar26Enter(TObject *Sender)
{
       OnEditEnter(26,5,Edt26_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_1Enter(TObject *Sender)
{
       OnEditEnter(27,1,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_2Enter(TObject *Sender)
{
       OnEditEnter(27,2,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_3Enter(TObject *Sender)
{
       OnEditEnter(27,3,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt27_4Enter(TObject *Sender)
{
       OnEditEnter(27,4,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar27Enter(TObject *Sender)
{
       OnEditEnter(27,5,Edt27_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_1Enter(TObject *Sender)
{
       OnEditEnter(28,1,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_2Enter(TObject *Sender)
{
       OnEditEnter(28,2,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_3Enter(TObject *Sender)
{
       OnEditEnter(28,3,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt28_4Enter(TObject *Sender)
{
       OnEditEnter(28,4,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar28Enter(TObject *Sender)
{
       OnEditEnter(28,5,Edt28_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_1Enter(TObject *Sender)
{
       OnEditEnter(29,1,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_2Enter(TObject *Sender)
{
       OnEditEnter(29,2,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_3Enter(TObject *Sender)
{
       OnEditEnter(29,3,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt29_4Enter(TObject *Sender)
{
       OnEditEnter(29,4,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar29Enter(TObject *Sender)
{
       OnEditEnter(29,5,Edt29_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_1Enter(TObject *Sender)
{
       OnEditEnter(30,1,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_2Enter(TObject *Sender)
{
       OnEditEnter(30,2,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_3Enter(TObject *Sender)
{
       OnEditEnter(30,3,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edt30_4Enter(TObject *Sender)
{
       OnEditEnter(30,4,Edt30_4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar30Enter(TObject *Sender)
{
       OnEditEnter(30,5,Edt30_4);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
/*
   //�v����Ǝn�܂�O �A�܂�u�����v���݂������O
   if( ! iKskStart )  return ;

   // �}�E�X��ScrollBar��ύX����ȊO�̏ꍇ
   if( iSaveFlag ) return ;

   // �}�E�X��ScrollBar��ύX����ꍇ
   if( SamplePositionIdx > 0 &&
       ( SamplePositionIdx >= iFirstPosition && SamplePositionIdx <= iLastPosition ) &&
         DataNoIdx > 2   ){

          if( SaveRegaiDt()< 0) return ;
          CheckInKikaku(1);
          ToDrawGraph(SamplePositionIdx, iOption);

          int pos = pScrl[SamplePositionIdx-1]->Position ;
          pEdt4[SamplePositionIdx-1]->Text = IntToStr(pos);

          // �ް��X�V
          pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",
                                      KD51Data[SamplePositionIdx-1].SOKUTEI_B[pos-1] );

          pEdt3[SamplePositionIdx-1]->SetFocus();

          // �X�V�����f�[�^���`�F�b�N����
          CheckInKikaku(0);

      }
   */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBarVChange(TObject *Sender)
{

   //�v����Ǝn�܂�O �A�܂�u�����v���݂������O
   if( ! iKskStart )  return ;

      // �}�E�X��ScrollBar��ύX����ȊO�̏ꍇ
   if( iSaveFlag ) return ;

   // �}�E�X��ScrollBar��ύX����ꍇ
   if( SamplePositionIdx >0 &&
       ( SamplePositionIdx >= iFirstPosition && SamplePositionIdx <= iLastPosition ) &&
         DataNoIdx > 2   ){

          if(SaveRegaiDt()<0) return ;;
          CheckInKikaku(1);
          ToDrawGraph(SamplePositionIdx, iOption);

          int pos = pScrl_S[iKomoku-1]->Position ;

          //��d�𓯎��ɍX�V
          pEdt4[SamplePositionIdx-1]->Text = IntToStr(pos);
          pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",
                                      KD51Data[SamplePositionIdx-1].SOKUTEI_B[pos-1] );

          pEdt3[SamplePositionIdx-1]->SetFocus();

          // �X�V�����f�[�^���`�F�b�N����
          CheckInKikaku(0);
      }
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Edt01_1Change(TObject *Sender)
{
 /*   if(  !iKskStart )  return ;

   //  TNumberEdit *Edt = (TNumberEdit *)Sender;

     //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
     AllDataChg = 1;
     CurSampChg = 1;
     CurDataChg = 1;


    // �v�������f�[�^Count
    if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR < DataNoIdx ){
         KD51Data[SamplePositionIdx-1].SOKUTEI_NB_CUR = DataNoIdx ;
     }
  */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_1Exit(TObject *Sender)
{
    double a;

    if( CurBackFlg ) return ;

    // �v���l�̃`�F�b�N
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

    //   CurDataChg = 0;

      if( DataNoIdx == 1 ){

          a =KD51Data[SamplePositionIdx-1].SOKUTEI_S[0] ;
         if(  fabs(pEdt1_S[0]->Value - a ) > 0.000001){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = DataNoIdx ;
            }

            //����l�P
            if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                KD51Data[SamplePositionIdx-1].SOKUTEI_S[0] = pEdt1_S[0]->Value;

            //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, 1 );
             pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[0] );

         }
      }else if( DataNoIdx == 2 ){

         a =KD51Data[SamplePositionIdx-1].SOKUTEI_S[1] ;
         if(  fabs(pEdt2_S[0]->Value - a) >0.000001 ){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = DataNoIdx ;
            }

            //����l�Q
            if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                KD51Data[SamplePositionIdx-1].SOKUTEI_S[1] = pEdt2_S[0]->Value;
            //��̔�d�̌v�Z
            BHijyuCal(SamplePositionIdx, 2 );
            pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[1] );
          }

      }else{

          // F2 ,F3, Return���������ꍇ
          int n=pEdt4_S[0]->Value ;
          a = KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] ;

         if(  fabs(pEdt3_S[0]->Value - a) > 0.00000001 ){

              //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
              AllDataChg = 1;
              CurSampChg = 1;
              CurDataChg = 1;

             // �v�������f�[�^Count
             if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR < n  )
                  KD51Data[SamplePositionIdx-1].SOKUTEI_NS_CUR = n ;

             if(  KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4)
                 KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] = pEdt3_S[0]->Value;

             //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, n ) ;
             pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
         }
         /*
          // �}�E�X�ŗ����ꍇ
          if( ! iSaveFlag )     SaveRegaiDt() ;
          if( CurDataChg )
              pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
           CheckInKikaku(1);

          if( iSaveFlag ) return ;
          */
      }

     //��R�l�K�i�̃`�F�b�N
      CheckInKikaku(1);

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_2Exit(TObject *Sender)
{
    double a;

    if( CurBackFlg ) return ;

   // �v���l�̃`�F�b�N
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

    //   CurDataChg = 0;

      if( DataNoIdx == 1 ){

         a = KD51Data[SamplePositionIdx-1].SOKUTEI_H[0] ;

         if(  fabs(pEdt1_S[1]->Value - a ) > 0.000001){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = DataNoIdx ;
            }

            //����l�P
            KD51Data[SamplePositionIdx-1].SOKUTEI_H[0] = pEdt1_S[1]->Value;

            //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, 1 );
             pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[0] );

         }
      }else if( DataNoIdx == 2 ){

          a = KD51Data[SamplePositionIdx-1].SOKUTEI_H[1] ;
          if(  fabs(pEdt2_S[1]->Value - a) >0.000001 ){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = DataNoIdx ;
            }

            KD51Data[SamplePositionIdx-1].SOKUTEI_H[1] = pEdt2_S[1]->Value;

            //��̔�d�̌v�Z
            BHijyuCal(SamplePositionIdx, 2 );
            pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[1] );
          }

      }else{

          // F2 ,F3, Return���������ꍇ
          int n=pEdt4_S[1]->Value ;

          a = KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] ;

         if(  fabs(pEdt3_S[1]->Value - a) > 0.00000001 ){

              //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
              AllDataChg = 1;
              CurSampChg = 1;
              CurDataChg = 1;

             // �v�������f�[�^Count
             if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR < n )
                  KD51Data[SamplePositionIdx-1].SOKUTEI_NH_CUR = n ;


              KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] = pEdt3_S[1]->Value;

             //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, n ) ;
             pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
         }

         /*
          // �}�E�X�ŗ����ꍇ
          if( ! iSaveFlag )     SaveRegaiDt() ;
          if( CurDataChg )
              pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
           CheckInKikaku(1);

          if( iSaveFlag ) return ; */
      }

     //��R�l�K�i�̃`�F�b�N
      CheckInKikaku(1);

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_3Exit(TObject *Sender)
{
    double a;

    if( CurBackFlg ) return ;

   // �v���l�̃`�F�b�N
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

    //   CurDataChg = 0;

      if( DataNoIdx == 1 ){

          a =  KD51Data[SamplePositionIdx-1].SOKUTEI_N[0] ;
         if(  fabs(pEdt1_S[2]->Value - a ) > 0.000001){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR < DataNoIdx )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR = DataNoIdx ;


            //����l�P
            KD51Data[SamplePositionIdx-1].SOKUTEI_N[0] = pEdt1_S[2]->Value;

            //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, 1 );
             pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[0] );

         }
      }else if( DataNoIdx == 2 ){

         a =  KD51Data[SamplePositionIdx-1].SOKUTEI_N[1] ;
         if(  fabs(pEdt2_S[2]->Value - a) >0.000001 ){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR = DataNoIdx ;
            }
            //����l�Q
            KD51Data[SamplePositionIdx-1].SOKUTEI_N[1] = pEdt2_S[2]->Value;

            //��̔�d�̌v�Z
            BHijyuCal(SamplePositionIdx, 2 );
            pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[1] );
          }

      }else{

          // F2 ,F3, Return���������ꍇ
          int n=pEdt4_S[2]->Value ;

          a = KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] ;
         if(  fabs(pEdt3_S[2]->Value - a) > 0.00000001 ){

              //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
              AllDataChg = 1;
              CurSampChg = 1;
              CurDataChg = 1;

              // �v�������f�[�^Count
              if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR < n )
                   KD51Data[SamplePositionIdx-1].SOKUTEI_NN_CUR = n ;

              KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] = pEdt3_S[iKomoku-1]->Value;

              //��̔�d�̌v�Z
              BHijyuCal(SamplePositionIdx, n ) ;
              pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
         }
       /*
          // �}�E�X�ŗ����ꍇ
          if( ! iSaveFlag )     SaveRegaiDt() ;
          if( CurDataChg )
              pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
           CheckInKikaku(1);

          if( iSaveFlag ) return ; */
      }

     //��R�l�K�i�̃`�F�b�N
      CheckInKikaku(1);

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS1_4Exit(TObject *Sender)
{
    double a;

    if( CurBackFlg ) return ;

   // �v���l�̃`�F�b�N
     if( iKskStart && ! CurBackFlg && SamplePositionIdx >= 1 ) {

    //   CurDataChg = 0;

      if( DataNoIdx == 1 ){

         a = KD51Data[SamplePositionIdx-1].SOKUTEI_J[0] ;

         if(  fabs(pEdt1_S[3]->Value - a ) > 0.000001){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR = DataNoIdx ;
            }

            //����l�P
            KD51Data[SamplePositionIdx-1].SOKUTEI_J[0] = pEdt1_S[3]->Value;

            //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, 1 );
             pEdt1[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[0] );

         }
      }else if( DataNoIdx == 2 ){

         a = KD51Data[SamplePositionIdx-1].SOKUTEI_J[1] ;

         if(  fabs(pEdt2_S[3]->Value - a) >0.000001 ){

             //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
            AllDataChg = 1;
            CurSampChg = 1;
            CurDataChg = 1;

            // �v�������f�[�^Count
            if ( KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR < DataNoIdx ){
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR = DataNoIdx ;
            }


            //����l�Q
            KD51Data[SamplePositionIdx-1].SOKUTEI_J[1] = pEdt2_S[3]->Value;

            //��̔�d�̌v�Z
            BHijyuCal(SamplePositionIdx, 2 );
            pEdt2[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[1] );
          }

      }else{

          // F2 ,F3, Return���������ꍇ
          int n=pEdt4_S[3]->Value ;

          a = KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] ;

          if(  fabs(pEdt3_S[3]->Value - a) > 0.00000001 ){

              //��ʂɕ\�����Ă����ް��l���X�V�����ꍇ
              AllDataChg = 1;
              CurSampChg = 1;
              CurDataChg = 1;

             // �v�������f�[�^Count
             if( KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR < n )
                 KD51Data[SamplePositionIdx-1].SOKUTEI_NJ_CUR = n ;

             KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] = pEdt3_S[iKomoku-1]->Value;

             //��̔�d�̌v�Z
             BHijyuCal(SamplePositionIdx, n ) ;
             pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
         }

         /*
          // �}�E�X�ŗ����ꍇ
          if( ! iSaveFlag )     SaveRegaiDt() ;
          if( CurDataChg )
              pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
           CheckInKikaku(1);

          if( iSaveFlag ) return ;
          */
      }

     //��R�l�K�i�̃`�F�b�N
      CheckInKikaku(1);

   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::edtymdChange(TObject *Sender)
{
     // �X�e�[�^�X���b�Z�[�W
     StatBarClear( "  ");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edt01_4Exit(TObject *Sender)
{
     // ���͂����ް�NO �R�`�X�X�𒴂��Ă��邩�ǂ����̃`�F�b�N
   if( iKskStart ){
        CheckDtNo() ;
        CurDataChg = 0;
   }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::PageCtrlChange(TObject *Sender)
{
       if( !HaveSokutei ) return ;

       // �X�e�[�^�X���b�Z�[�W
       StatBarClear( "  ");

        //���藚�����
       if( Form1->PageCtrl->ActivePage == TabSheet1)
          iOption = 1 ;
       if( Form1->PageCtrl->ActivePage == TabSheet2)
          iOption = 2;

       ToDrawGraph(SamplePositionIdx, iOption);

}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    char tempo[56];

    // �f�[�^��ύX�������ǂ����̃t���O�`�F�b�N
    if( AllDataChg ){
        switch( MessageDlg( MSG_10, mtConfirmation, mbYesNoCancel, 0) ){
            // �uYes�v      �ۑ�
            case mrYes:
               // BtnF11Click(Sender);

               // �X�e�[�^�X���b�Z�[�W
               StatBarClear(MSG_04);

               // �ް���̧��KD01�AKd02�֏�������
               Kd51_Update01();

               //�����ް����X�V�����ꍇ�̃t���O�̃N���A
               AllDataChg = 0;
               CurSampChg = 0;
               CurDataChg = 0;

               // �X�e�[�^�X���b�Z�[�W
               StatBarClear( " ") ;

                if( Update_err ){
                  CanClose = false;
                  Update_err = 0;
                }

                break;
            // �uNo�v       �ύX��j��
            case mrNo:
                break;
            // �uCancel�v   �L�����Z��
            case mrCancel:
                CanClose = false;
                break;
        }
    }

    if( CanClose == true ) {

      if (ShareFlag) {
        sprintf(tempo, "CLOSE");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));

        sprintf(tempo, "EXIT");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        
        SharedMemory_Close(1);
        SharedMemory_Close(2);
      }

    }
}


//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_1Change(TObject *Sender)
{
   int n;
   if( iKskStart ) {

         n = pEdt4_S[0]->Value;

         if( n >= 3 && n <= KD51Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[0]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
             else
                 pEdt3_S[0]->Text = "0.000" ;

             pEdt3_S[1]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );
             pEdt3_S[2]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] );
             pEdt3_S[3]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] );


             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pPnl_S[0]->Caption = "0" ;
              }else{
                     pScrl_S[0]->Position = n ;
              }

             for( int i= 1; i<4; i++ ){
                    pEdt4_S[i]->Text = IntToStr(n) ;
                    pScrl_S[i]->Position = n ;
             }

             DataNoIdx = n ;

            iSaveFlag = 0;

         }

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_2Change(TObject *Sender)
{
int n;
   if( iKskStart ) {

         n = pEdt4_S[1]->Value;

         if( n >= 3 && n <= KD51Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[1]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
             else
                 pEdt3_S[0]->Text = "0.000" ;

             pEdt3_S[1]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );
             pEdt3_S[2]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] );
             pEdt3_S[3]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] );


             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pEdt4_S[0]->Text = "0" ;
                     pPnl_S[0]->Caption = "0" ;
              }else{
                    pEdt4_S[0]->Text = IntToStr(n) ;
                    pScrl_S[0]->Position = n ;
              }

               pScrl_S[1]->Position = n ;

             for( int i= 2; i<4; i++ ){
                    pEdt4_S[i]->Text = IntToStr(n) ;
                    pScrl_S[i]->Position = n ;
             }

             DataNoIdx = n;
            iSaveFlag = 0;

         }

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_3Change(TObject *Sender)
{
 int n;
   if( iKskStart ) {

         n = pEdt4_S[2]->Value;

         if( n >= 3 && n <= KD51Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[2]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
             else
                 pEdt3_S[0]->Text = "0.000" ;

             pEdt3_S[1]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );
             pEdt3_S[2]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] );
             pEdt3_S[3]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] );


             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pEdt4_S[0]->Text = "0" ;
                     pPnl_S[0]->Caption = "0" ;
              }else{
                    pEdt4_S[0]->Text = IntToStr(n) ;
                    pScrl_S[0]->Position = n ;
              }

              pScrl_S[1]->Position = n ;
              pEdt4_S[1]->Text = IntToStr(n) ;

              pScrl_S[2]->Position = n ;

              pScrl_S[3]->Position = n ;
              pEdt4_S[3]->Text = IntToStr(n) ;

              DataNoIdx = n;

              iSaveFlag = 0;

         }

   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdtS4_4Change(TObject *Sender)
{
int n;
   if( iKskStart ) {

         n = pEdt4_S[3]->Value;

         if( n >= 3 && n <= KD51Data[SamplePositionIdx-1].SOKUTEI_NM ){

            if( n == pScrl_S[3]->Position || n== 0 ) return ;

            iSaveFlag = 1 ;

            pEdt3[SamplePositionIdx-1]->Text = FormatFloat("#0.00",KD51Data[SamplePositionIdx-1].SOKUTEI_B[n-1] );
            pEdt4[SamplePositionIdx-1]->Text = IntToStr(n);
            pScrl[SamplePositionIdx-1]->Position = n ;

             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN != 4 )
                 pEdt3_S[0]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_S[n-1] );
             else
                 pEdt3_S[0]->Text = "0.000" ;

             pEdt3_S[1]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_H[n-1] );
             pEdt3_S[2]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_N[n-1] );
             pEdt3_S[3]->Text = FormatFloat("#0.000",KD51Data[SamplePositionIdx-1].SOKUTEI_J[n-1] );


             if( KD51Data[SamplePositionIdx-1].KEIJYO_KBN == 4 ){
                     pEdt4_S[0]->Text = "0" ;
                     pPnl_S[0]->Caption = "0" ;
              }else{
                    pEdt4_S[0]->Text = IntToStr(n) ;
                    pScrl_S[0]->Position = n ;
              }

              pScrl_S[1]->Position = n ;
              pEdt4_S[1]->Text = IntToStr(n) ;

              pScrl_S[2]->Position = n ;
              pEdt4_S[2]->Text = IntToStr(n) ;

              pScrl_S[3]->Position = n ;

              DataNoIdx = n;

              iSaveFlag = 0;

         }

   }
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
}



void __fastcall TForm1::BtnF11Enter(TObject *Sender)
{
   BtnF11->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF11Exit(TObject *Sender)
{
  BtnF11->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Enter(TObject *Sender)
{
   BtnF12->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF12Exit(TObject *Sender)
{
 BtnF12->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

// �����\��N�����́����{�^���@2002/10/28 A.Tamura
void __fastcall TForm1::UpDownymdClick(TObject *Sender, TUDBtnType Button)
{

   try{

      //char str[256];
      //sprintf(str,"Max=%d Min=%d Pos=%d", UpDownymd->Max, UpDownymd->Min, UpDownymd->Position);

      // �����\��N����
      edtymd->SetFocus();
      TDateTime dtDate = StrToDate(edtymd->Text);
      if( Button == Comctrls::btNext ){
         dtDate++;
      } else{
         dtDate--;
      }
      edtymd->Text = FormatDateTime("yyyy/mm/dd",dtDate.FormatString("YYYY/MM/DD"));
   }
   catch(...){
   }
}
//---------------------------------------------------------------------------

// �g���[NO�́����{�^���@2002/10/28 A.Tamura
void __fastcall TForm1::UpDowntlnoClick(TObject *Sender, TUDBtnType Button)
{
   int i;

   try{
      //char str[256];
      //sprintf(str, "Max=%d Min=%d Pos=%d",UpDowntlno->Max, UpDowntlno->Min, UpDowntlno->Position);

      // �g���[NO - 1
      edttlno->SetFocus();
      i = StrToInt(edttlno->Text);
      if( Button == Comctrls::btNext ){
         if( i < 99 )i++;
      } else{
         if( i > 1 ) i--;
      }
      edttlno->Text = IntToStr(i);
   }
   catch(...){
   }

}
//---------------------------------------------------------------------------
//���l���͉�� �\�� 2002/11/07 Add E.Takase
void __fastcall TForm1::BtnF06Click(TObject *Sender)
{

    //�J�\�[�������ɖ߂�
    CurseBack();
    ExecF6();
    //���l���q���g�ɃZ�b�g 2002/11/08 E.Takase
    if ( Form3->ModalResult == 1 ) {

        SetMEMO();
        AllDataChg = 1;
    }
}
void ExecF6(void)
{
    if( !HaveSokutei ) return ;

    Form3->ShowModal();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//���l���q���g�ɃZ�b�g 2002/11/07 E.Takse
void __fastcall TForm1::SetMEMO(void)
{
    int i;

	for( i=0; i<30; i++ )
    {
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD51Data[i].SAMPLE_P == -1 )
		{
			//pPnlP[i]->ShowHint = false;
			pEdt1[i]->ShowHint = false;
			pEdt2[i]->ShowHint = false;
			pEdt3[i]->ShowHint = false;
			pEdt4[i]->ShowHint = false;
			pScrl[i]->ShowHint = false;
			pPnlN[i]->ShowHint = false;
		} else {
			if ( Trim(KD51Data[i].MEMO) != "" ) {
				//pPnlP[i]->Hint = KD51Data[i].MEMO;
				pEdt1[i]->Hint = KD51Data[i].MEMO;
				pEdt2[i]->Hint = KD51Data[i].MEMO;
				pEdt3[i]->Hint = KD51Data[i].MEMO;
				pEdt4[i]->Hint = KD51Data[i].MEMO;
				pScrl[i]->Hint = KD51Data[i].MEMO;
				pPnlN[i]->Hint = KD51Data[i].MEMO;

				//pPnlP[i]->ShowHint = true;
				pEdt1[i]->ShowHint = true;
				pEdt2[i]->ShowHint = true;
				pEdt3[i]->ShowHint = true;
				pEdt4[i]->ShowHint = true;
				pScrl[i]->ShowHint = true;
				pPnlN[i]->ShowHint = true;

			} else {
				//pPnlP[i]->ShowHint = false;
				pEdt1[i]->ShowHint = false;
				pEdt2[i]->ShowHint = false;
				pEdt3[i]->ShowHint = false;
				pEdt4[i]->ShowHint = false;
				pScrl[i]->ShowHint = false;
				pPnlN[i]->ShowHint = false;

			}
		}
	 }

}
//---------------------------------------------------------------------------

