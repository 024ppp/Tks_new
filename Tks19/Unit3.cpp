//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

// ��ʺ��۰ٕۑ��ϐ�
TEdit *pEdtMEMO[30] ;    //  ���l���̺͂��۰ق�ۑ�

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//��ʍ쐬���̏��� 2002/11/07 E.Takase
void __fastcall TForm3::FormCreate(TObject *Sender)
{
    // ��ʊe���۰ق�z��ϐ��֕ۑ�����
    pEdtMEMO[0] =  Form3->Edit1 ;
    pEdtMEMO[1] =  Form3->Edit2 ;
    pEdtMEMO[2] =  Form3->Edit3 ;
    pEdtMEMO[3] =  Form3->Edit4 ;
    pEdtMEMO[4] =  Form3->Edit5 ;
    pEdtMEMO[5] =  Form3->Edit6 ;
    pEdtMEMO[6] =  Form3->Edit7 ;
    pEdtMEMO[7] =  Form3->Edit8 ;
    pEdtMEMO[8] =  Form3->Edit9 ;
    pEdtMEMO[9] =  Form3->Edit10 ;
    pEdtMEMO[10] =  Form3->Edit11 ;
    pEdtMEMO[11] =  Form3->Edit12 ;
    pEdtMEMO[12] =  Form3->Edit13 ;
    pEdtMEMO[13] =  Form3->Edit14 ;
    pEdtMEMO[14] =  Form3->Edit15 ;
    pEdtMEMO[15] =  Form3->Edit16 ;
    pEdtMEMO[16] =  Form3->Edit17 ;
    pEdtMEMO[17] =  Form3->Edit18 ;
    pEdtMEMO[18] =  Form3->Edit19 ;
    pEdtMEMO[19] =  Form3->Edit20 ;
    pEdtMEMO[20] =  Form3->Edit21 ;
    pEdtMEMO[21] =  Form3->Edit22 ;
    pEdtMEMO[22] =  Form3->Edit23 ;
    pEdtMEMO[23] =  Form3->Edit24 ;
    pEdtMEMO[24] =  Form3->Edit25 ;
    pEdtMEMO[25] =  Form3->Edit26 ;
    pEdtMEMO[26] =  Form3->Edit27 ;
    pEdtMEMO[27] =  Form3->Edit28 ;
    pEdtMEMO[28] =  Form3->Edit29 ;
    pEdtMEMO[29] =  Form3->Edit30 ;

    //�R���g���[���̖���
    SetEnabel(0);
    //�R���g���[���̏�����
    SetInit(0);

}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormActivate(TObject *Sender){
    //�R���g���[���̖���
    SetEnabel(0);
    //�R���g���[���̏�����
    SetInit(0);
    //�R���g���[���Ƀf�[�^�Z�b�g
    SetData();
    //�ŏ��̃R���g���[���Ɉړ�
    ToFirstData();
    
}
//---------------------------------------------------------------------------
//���l�f�[�^����ʂփZ�b�g
void __fastcall TForm3::SetData(void)
{
    int i;
	// ���l�ް�����ʂփZ�b�g
	int flag = 0;
	for( i=0; i<30; i++ )
	{
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
			IsEnabledEdt( pEdtMEMO[i], 1 );
			pEdtMEMO[i]->Text =  Trim(KD91Data[i].MEMO);
		}
	}
}
//---------------------------------------------------------------------------
//���ͺ��۰ق�����������
void __fastcall TForm3::SetInit(int flag)
{
    int i ;

    // ������߼޼��NO�y�ё����N
    for( i=0; i<30; i++ ){
        InitEdt(pEdtMEMO[i], "");
    }
}
//---------------------------------------------------------------------------
//���ͺ��۰ق𖳌��ɂ���
void __fastcall TForm3::SetEnabel(int flag )
{
    int i;
    //��ʂ��J�����ɁA���ͺ��۰ق𖳌��ɂ���
    for( i=0; i<30; i++ )
    {
        IsEnabledEdt( pEdtMEMO[i], 0 );
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm3::InitEdt(TEdit *P_Edit, AnsiString Str)
{
       P_Edit->Text = Str ;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::IsEnabledEdt(TEdit *P_Edit, int flag)
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

void __fastcall TForm3::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     switch(Key)
     {
         case VK_F1:   break;
         case VK_F2:   break;
         case VK_F3:   break;
         case VK_F4:   break;
         case VK_F5:   break;
         case VK_F6:   break;
         case VK_F7:   break;

         case VK_F9:   break;
         case VK_F8:   break;
         case VK_F10:  break;
         case VK_F11:  BtnF11Click(Sender);
                       break;
         case VK_F12:  BtnF12Click(Sender); 
                       break;

         case VK_RETURN:
                       if ( BtnF11->Focused() ) { BtnF11Click(Sender); }
                       if ( BtnF12->Focused() ) { BtnF12Click(Sender); }
                       ToNextData(1);
               		   break;
         case VK_UP:   break;

         case VK_LEFT: break;
         case VK_DOWN:
                       if ( BtnF11->Focused() ) { BtnF12->SetFocus(); }
                       if ( BtnF12->Focused() ) { ToFirstData(); }
                       ToNextData(0);
               		   break;
         case VK_RIGHT:break;
     }

}
//---------------------------------------------------------------------------
//�ŏ��̃R���g���[���ֈړ�
void __fastcall TForm3::ToFirstData(void)
{
    int i;
    int n;
    int iPos;
    int iFlag;



    iFlag = 0;
    for( i=0; i<30; i++ )
    {
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            iPos = SrchNextFEdit(i,1);
            if ( iPos >= 0 ) {
                pEdtMEMO[iPos]->SetFocus();
                return;
            }

		}
    }


}

//---------------------------------------------------------------------------
//���̃R���g���[���ֈړ�
void __fastcall TForm3::ToNextData(int KeyFlag)
{
    int i;
    int n;
    int iPos;
    int iFlag;



    iFlag = 0;
    for( i=0; i<30; i++ )
    {
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if(  pEdtMEMO[i]->Focused() ) {
                iPos = SrchNextFEdit(i+1,KeyFlag);
                if ( iPos >= 0 ) {
                    pEdtMEMO[iPos]->SetFocus();
                    return;
                } else {
                    BtnF11->SetFocus();
                    return;
                }

            }

		}
    }


}
//---------------------------------------------------------------------------

int __fastcall TForm3::SrchNextFEdit(int n,int KeyFlag)
{
    int i;

    if ( 0 <= n && n < 30 && pEdtMEMO[n]->Enabled ) {
        return n;
    }

    if ( n >= 30 ) {
        n = 0;
    }

    if ( n < 0 ) {
        n = 30;
    }

    for( i=n; i<30; i++ )
    {
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if( pEdtMEMO[i]->Enabled ) {
                return i;

            }

		}
    }

    if ( KeyFlag == 0 ) {
    //���̏ꍇ
        for( i=0; i<n; i++ )
        {
		    //������߼޼��NO���Ȃ��̏ꍇ
		    if( KD91Data[i].SAMPLE_P == -1 )
		    {

   	        }else{
                if( pEdtMEMO[i]->Enabled ) {
                return i;

                }

		    }
        }
    }

    return -1;
}
//---------------------------------------------------------------------------
//str����a�̕����񂪊܂܂�Ă���ꍇ�Ab�ɒu�����ĕԂ�
AnsiString __fastcall TForm3::StrReplace(AnsiString str, AnsiString a, AnsiString b)
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
//�߂�{�^���N���b�N�� ��ʂ���� 2002/11/07 E.Takase
void __fastcall TForm3::BtnF12Click(TObject *Sender)
{
    //Close();
    Form3->ModalResult = -1;


}
//---------------------------------------------------------------------------
//OK�{�^���N���b�N�� �ϐ��ɓ��̓f�[�^�ۑ�����ʂ���� 2002/11/07 E.Takase
void __fastcall TForm3::BtnF11Click(TObject *Sender)
{
    int i;
	// ���l�ް�����ʂփZ�b�g
	int flag = 0;
	for( i=0; i<30; i++ )
	{
		//������߼޼��NO���Ȃ��̏ꍇ
		if( KD91Data[i].SAMPLE_P == -1 )
		{

		}else{
            if ( Trim(pEdtMEMO[i]->Text) == "" ) {
                KD91Data[i].MEMO = " ";
            } else {
                KD91Data[i].MEMO = StrReplace(Trim(pEdtMEMO[i]->Text), "'", "_");
            }
		}
	}

    //Close();
    Form3->ModalResult = 1;

}
//---------------------------------------------------------------------------

