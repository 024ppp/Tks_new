//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
#include "unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//��������SGr�̃Z�b�g
AnsiString __fastcall TForm1::KENSASGr_Set(int KMK,double JYOKEN, double KIKAKU, AnsiString tani)
{
	AnsiString sBuf;

    switch(KMK)
    {
        case 0: //���[�h������
        	sBuf = FormatFloat("#0.00",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-1) + sBuf);
            break;
        case 1: //�u���V��
        	sBuf = FormatFloat("#0.000",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        case 3: //���[�h����t��R
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            break;

        case 4: //���[�h���������x
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            break;

        case 5: //��̔�d
        	sBuf = FormatFloat("#0.00",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-1) + sBuf);
            break;

        case 6: //�d�x
        	switch ( int(JYOKEN) )
            {
        		case 1: //�d�x ����
        			sBuf = FormatFloat("#0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            		break;

        		case 2: //�d�x ����
        			sBuf = FormatFloat("#0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            		break;

        		case 3: //�d�x ����
        			sBuf = FormatFloat("#0.0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            		break;

        		case 4: //�d�x ����
        			sBuf = FormatFloat("#0.0",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-2) + sBuf);
            		break;

        		default:
                	sBuf = FormatFloat("#0.000",KIKAKU);
            		return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            		break;
        	}
            break;
        case 7: //�ŗL��R
        	sBuf = FormatFloat("#0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            break;

        case 8: //�R�ܗ�
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        case 9: //����
        	sBuf = FormatFloat("#0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-4) + sBuf);
            break;

        case 10: //�Ȃ������i�����j
        	sBuf = FormatFloat("#0.0",KIKAKU);
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

        default:
        	if ( tani == "N" || tani == "Kgf" ) {
        		sBuf = FormatFloat("#0.0",KIKAKU);
            } else {
            	if ( tani == "�x" ) {
               		sBuf = FormatFloat("#0.00",KIKAKU);
                } else {
                	sBuf = FormatFloat("#0.000",KIKAKU);
                }
            }
            return(AnsiString::StringOfChar(' ', 10-sBuf.Length()-0) + sBuf);
            break;

	}

}

//��������CmbIndx�̃Z�b�g
int __fastcall TForm1::KENSACmb_Set(int KMK,double JYOKEN)
{
    Cmb5->Clear();


    switch(KMK)
    {
        case 0: //���[�h������
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(13);
            break;
        case 1: //�u���V��
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(10);
            break;

        case 3: //���[�h����t��R
            Cmb5->Items->Add( "mV/A" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(7);
            break;

        case 4: //���[�h���������x
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(8);
            break;

        case 5: //��̔�d
            Cmb5->Items->Add( " " );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(0);
            break;

        case 6: //�d�x
        	switch ( int(JYOKEN) )
            {
        		case 1: //�d�x ����
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 0;
            		Edt3->FPos = 0;
            		return(1);
            		break;

        		case 2: //�d�x ����
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 0;
            		Edt3->FPos = 0;
            		return(2);
            		break;

        		case 3: //�d�x ����
            		Cmb5->Items->Add( "HsD" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 1;
            		Edt3->FPos = 1;
            		return(3);
            		break;

        		case 4: //�d�x ����
            		Cmb5->Items->Add( "HsD" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 1;
            		Edt3->FPos = 1;
            		return(4);
            		break;

        		default:
            		Cmb5->Items->Add( "HsC" );
            		Cmb5->ItemIndex = 0;
            		Edt2->FPos = 3;
            		Edt3->FPos = 3;
    				return(1);
            		break;
        	}
            break;
        case 7: //�ŗL��R
            Cmb5->Items->Add( "�ʃ��Ecm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            return(5);
            break;

        case 8: //�R�ܗ�
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(6);
            break;

        case 9: //����
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            return(18);
            break;

        case 2: //�u���V����
		        //�u���V����
		        //���[�h���X�|�b�g����
		        //���[�h���X�|�b�g��
		        //���[�h���X�|�b�g����
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(12);
            break;


        case 10: //������R
            Cmb5->Items->Add( "�x" );
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            return(12);
            break;

		case 11:  //�^�[�~�i���n�ڋ��x
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(12);
            break;

        case 12: //�Ȃ������i�����j
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            return(19);
            break;

        default:
            Cmb5->Items->Add( "mm" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "�x" );
            Cmb5->ItemIndex = 0;
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            return(12);
            break;

	}

}

//�������ڂ̃Z�b�g
void __fastcall TForm1::KENSAKMK_Set(int CmbIndx)
{
    //CmbIndx = Cmb��ItemIndex
    //EdtKMK->Text
    Cmb5->Clear();
	EdtJYOKEN1->Text = "0";
	EdtJYOKEN2->Text = "0";
	EdtJYOKEN3->Text = " ";

    Cmb3->ItemIndex = 0;
    //Cmb4->ItemIndex = 0;

	Edt2->Enabled = true;
	Edt3->Enabled = true;
    //���萔
	Edt1->Text = "30";

    //�`��敪
    switch(KM02.KEIJKBN)
    {
        case 1:
        case 2:
        case 3:
			EdtKEIJKBN->Text = "1";
            break;
        case 4:
			EdtKEIJKBN->Text = "2";
            break;
        //2002/12/28 E.Takase
        case 5:
			EdtKEIJKBN->Text = "3";
            break;
        default:
			EdtKEIJKBN->Text = "0";
            break;
    }


    switch(CmbIndx)
    {
        case 13: //���[�h������
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "0";
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            Edt2->Text = FormatFloat("#0.000",KM02.LD_LNG_MAX);
            Edt2->Text = FormatFloat("#0.000",KM02.LD_LNG_MIN);
            break;

        case 10: //�u���V��
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "1";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text = FormatFloat("#0.000",KM02.BURASI_MIN);
            Edt3->Text = FormatFloat("#0.000",KM02.BURASI_MAX);
            break;

        case 7: //���[�h����t��R
            Cmb5->Items->Add( "mV/A" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "3";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",0);
            Edt3->Text =  FormatFloat("#0.0",KM02.LD_TR_DENA);
            Cmb3->ItemIndex = 2;
            Edt2->Enabled = false;
            EdtJYOKEN1->Text = FloatToStr(KM02.LD_TR_DENR);		//���[�h����t����d��
            EdtJYOKEN2->Text = IntToStr(KM02.LD_TR_TIME);		//�@�V�@�@��t���莞��
            EdtJYOKEN3->Text = KM02.LD_TR_TYPE;					//�@�V�@�@��t����^�C�v

            break;

        case 8: //���[�h���������x
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "4";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.LD_HP_KYO);
            Edt3->Text =  FormatFloat("#0.0",0);
            Cmb3->ItemIndex = 1;
            Edt3->Enabled = false;
            EdtJYOKEN1->Text = IntToStr(KM02.LD_HP_SPD);	//���[�h���������葬�x

            break;

        case 0: //��̔�d
            Cmb5->Items->Add( " " );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "5";
            Edt2->FPos = 2;
            Edt3->FPos = 2;
            Edt2->Text =  FormatFloat("#0.00",KM02.BOTAI_MIN);
            Edt3->Text =  FormatFloat("#0.00",KM02.BOTAI_MAX);
            //if ( KM02.KEIJKBN == 4 ) Cmb4->ItemIndex = 1;
            break;

        case 1: //�d�x ����
            Cmb5->Items->Add( "HsC" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "6";
            EdtJYOKEN1->Text = "1";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.HSC_A_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.HSC_A_MAX);
            break;

        case 2: //�d�x ����
            Cmb5->Items->Add( "HsC" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "2";
        	EdtKMK->Text = "6";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.HSC_S_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.HSC_S_MAX);
            break;

        case 3: //�d�x ����
            Cmb5->Items->Add( "HsD" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "3";
        	EdtKMK->Text = "6";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.HSD_A_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.HSD_A_MAX);
            break;

        case 4: //�d�x ����
            Cmb5->Items->Add( "HsD" );
            Cmb5->ItemIndex = 0;
            EdtJYOKEN1->Text = "4";
        	EdtKMK->Text = "6";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.HSD_S_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.HSD_S_MAX);
            break;

        case 5: //�ŗL��R
            Cmb5->Items->Add( "�ʃ��Ecm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "7";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.KOYU_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.KOYU_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.KOYU_DEN);	//�ŗL��R�� �d��
            EdtJYOKEN2->Text = IntToStr(KM02.KOYU_PRO);		//�ŗL��R�� �v���[�u
            break;

        case 6: //�R�ܗ�
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "8";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.MAGE_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.MAGE_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.MAGE_SPAN);	//�R�ܗ�
            break;

        case 18: //����
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "9";
            Edt2->FPos = 0;
            Edt3->FPos = 0;
            Edt2->Text =  FormatFloat("#0",KM02.ZAKUT_MIN);
            Edt3->Text =  FormatFloat("#0",KM02.ZAKUT_MAX);
            break;

        case 9:  //�u���V����
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",KM02.HIST_MIN);
            Edt3->Text =  FormatFloat("#0.000",KM02.HIST_MAX);
            break;

        case 11: //�u���V����
        case 15: //���[�h���X�|�b�g����
        case 16: //���[�h���X�|�b�g��
        case 17: //���[�h���X�|�b�g����
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

        case 12: //������R
            Cmb5->Items->Add( "mm" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "10";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

        case 14:  //�^�[�~�i���n�ڋ��x
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->ItemIndex = 0;
            Cmb3->ItemIndex = 1; //�����K�i
        	EdtKMK->Text = "11";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",0);
            Edt3->Text =  FormatFloat("#0.0",0);
            Edt3->Enabled = false;
            break;

        case 19: //�Ȃ������i�����j
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            //2003/07/22 E.Takase �P�ʒǉ�
            Cmb5->Items->Add( "N" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "12";
            Edt2->FPos = 1;
            Edt3->FPos = 1;
            Edt2->Text =  FormatFloat("#0.0",KM02.MAGEG_MIN);
            Edt3->Text =  FormatFloat("#0.0",KM02.MAGEG_MAX);
            EdtJYOKEN1->Text = FloatToStr(KM02.MAGEG_SPAN);	//�R�ܗ�
            break;

        default:
            Cmb5->Items->Add( "mm" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "�x" );
            Cmb5->ItemIndex = 0;
        	EdtKMK->Text = "2";
            Edt2->FPos = 3;
            Edt3->FPos = 3;
            Edt2->Text =  FormatFloat("#0.000",0);
            Edt3->Text =  FormatFloat("#0.000",0);
            break;

    }



}

//����̋K�i�l������
int __fastcall TForm1::DTKSHIN_Serch()
{
	AnsiString sBuf;

	KM02.DTKSCOD		 = " ";		//	���Ӑ�R�[�h
	KM02.DTKSHIN		 = " ";		//	���Ӑ�i��
	KM02.HINBAN			 = " ";		//	���Еi��
	KM02.ZISCOD			 = " ";		//	�ގ��R�[�h
	KM02.ZISNAM			 = " ";		//	�ގ���
	KM02.SYOSCOD		 = " ";		//	�Đ��R�[�h
	KM02.SORTKEY		 = 0;	    //	�\�[�g�L�[
	KM02.KEIJKBN		 = 0;		//	�`��敪
	KM02.SK_LD_LNG		 = 0;		//	����敪�@������
	KM02.SK_BURASI		 = 0;		//	�@�V�@�@�@�u���V��
	KM02.SK_BURASIT		 = 0;		//	�@�V�@�@�@�u���V���c����
	KM02.SK_LD_TR		 = 0;		//	�@�V�@�@�@����t��R
	KM02.SK_LD_HP		 = 0;		//	�@�V�@�@�@���������x
	KM02.SK_BOTAI		 = 0;		//	�@�V�@�@�@��̔�d
	KM02.SK_KOYU		 = 0;		//	�@�V�@�@�@�ŗL��R
	KM02.SK_MAGE		 = 0;		//	�@�V�@�@�@�R�ܗ�
	KM02.SK_HSC_A		 = 0;		//	�@�V�@�@�@HsC�d�x�i���ʁj
	KM02.SK_HSC_S		 = 0; 		//	�@�V�@�@�@HsC�d�x�i���ʁj
	KM02.SK_HSD_A		 = 0;		//	�@�V�@�@�@HsD�d�x�i���ʁj
	KM02.SK_HSD_S		 = 0;		//	�@�V�@�@�@HsD�d�x�i���ʁj
	KM02.SK_ZAKUT		 = 0;		//	�@�V�@�@�@����
	KM02.HIST_SOKUT		 = 0;		//	�q�X�g�O�������萔
	KM02.HIST_KIKAK		 = 0;		//	�@�V�@�@�@�@�@�K�i
	KM02.HIST_MIN		 = 0;		//	�@�V�@�@�@�@�@�����K�i
	KM02.HIST_MAX		 = 0;		//	�@�V�@�@�@�@�@����K�i
	KM02.LD_LNG_MIN		 = 0;		//	���[�h�������@���
	KM02.LD_LNG_MAX		 = 0;		//	�@�V�@�@�@�@�@����
	KM02.BURASI_MIN		 = 0;		//	�u���V���@���
	KM02.BURASI_MAX		 = 0;		//	�@�V�@�@�@����
	KM02.BURASIT_MIN	 = 0;		//	�u���V���c�������
	KM02.BURASIT_MAX	 = 0;		//	�@�V�@�@�@�@�@����
	KM02.LD_TR_DENA		 = 0;		//	���[�h����t����d��
	KM02.LD_TR_DENR		 = 0;		//	���[�h����t����d��
	KM02.LD_TR_TIME		 = 0;		//	�@�V�@�@��t���莞��
	KM02.LD_TR_TYPE		 = " ";		//	�@�V�@�@��t����^�C�v
    KM02.LD_HP_SPD		 = 0;		//	���[�h���������葬�x
	KM02.LD_HP_KYO		 = 0;		//	�@�V�@�@�������x
	KM02.LD_HP_TAN		 = 0;		//	�@�V�@�@�������x�P��
	KM02.BOTAI_MIN		 = 0;		//	��̔�d�@����
	KM02.BOTAI_MAX		 = 0;		//	�@�V�@�@�@���
	KM02.KOYU_MIN		 = 0;		//	�ŗL��R���@����
	KM02.KOYU_MAX		 = 0;		//	�@�V�@�@�@�@���
	KM02.KOYU_DEN		 = 0;		//	�@�V�@�@�@�@�d��
	KM02.KOYU_PRO		 = 0;		//	�@�V�@�@�@�@�v���[�u
	KM02.MAGE_MIN		 = 0;		//	�Ȃ����x�@����
	KM02.MAGE_MAX		 = 0;		//	�@�V�@�@�@���
	KM02.MAGE_TAN		 = 0;		//	�@�V�@�@�@�P��
	KM02.MAGE_SPAN		 = 0;		//	�@�V�@�@�@�X�p��
	KM02.HSC_A_MIN		 = 0;		//	�g���b�d�x�i���ʁj����
	KM02.HSC_A_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM02.HSC_S_MIN		 = 0;		//	�@�V�@�@�@�i���ʁj����
	KM02.HSC_S_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM02.HSD_A_MIN		 = 0;		//	�g���c�d�x�i���ʁj����
	KM02.HSD_A_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM02.HSD_S_MIN		 = 0;		//	�@�V�@�@�@�i���ʁj����
	KM02.HSD_S_MAX		 = 0;		//	�@�V�@�@�@�@�@�@�@���
	KM02.ZAKUT_MIN		 = 0;		//	�����@����
	KM02.ZAKUT_MAX		 = 0;		//	�@�V�@���
	KM02.MAGEG_MIN		 = 0;		//	�Ȃ����x�i�����j�@����    //2002/12/28 E.Takase Add
	KM02.MAGEG_MAX		 = 0;		//	�@�V�@�@�@        ���    //2002/12/28 E.Takase Add
	KM02.MAGEG_TAN		 = 0;		//	�@�V�@�@�@        �P��    //2002/12/28 E.Takase Add
	KM02.MAGEG_SPAN		 = 0;		//	�@�V�@�@�@        �X�p��  //2002/12/28 E.Takase Add

	// Initial Query
	Query1->Close();
	Query1->SQL->Clear();

	// �⍇�����s

	sBuf = "SELECT * FROM KM02 WHERE  DTKSHIN = '";
	sBuf +=  EdtHIN->Text  + "'";
    //2002/11/22 REVCNT = 0 �����ǉ� E.Takase
	sBuf += " AND REVCNT = 0 ";

	Query1->SQL->Add(sBuf);
	Query1->Open();
	Query1->Active = true;

	if ( Query1->Bof == true && Query1->Eof == true ) {
		//�������� �O��
		// �X�e�[�^�X���b�Z�[�W
		return(0);

	}

	Query1->First();
    //sBuf = Query1->FieldValues["DTKSCOD"];
    if ( !(VarIsNull (Query1->FieldValues["DTKSCOD"] )) )
		KM02.DTKSCOD = Query1->FieldValues["DTKSCOD"];				//	���Ӑ�R�[�h

    if ( !(VarIsNull (Query1->FieldValues["DTKSHIN"])))
		KM02.DTKSHIN = Query1->FieldValues["DTKSHIN"];				//	���Ӑ�i��

    if ( !(VarIsNull (Query1->FieldValues["HINBAN"])))
		KM02.HINBAN = Query1->FieldValues["HINBAN"];				//	���Еi��

    sBuf = Query1->FieldValues["ZISCOD"];
    if ( !(VarIsNull (Query1->FieldValues["ZISCOD"])))
		KM02.ZISCOD = Query1->FieldValues["ZISCOD"];				//	�ގ��R�[�h

    if ( !(VarIsNull (Query1->FieldValues["ZISNAM"])))
		KM02.ZISNAM = Query1->FieldValues["ZISNAM"];				//	�ގ���

    if ( !(VarIsNull (Query1->FieldValues["SYOSCOD"])))
		KM02.SYOSCOD = Query1->FieldValues["SYOSCOD"];				//	�Đ��R�[�h

    if ( !(VarIsNull (Query1->FieldValues["SORTKEY"])))
		KM02.SORTKEY = Query1->FieldValues["SORTKEY"];	      		//	�\�[�g�L�[

    if ( !(VarIsNull (Query1->FieldValues["KEIJKBN"])))
		KM02.KEIJKBN = Query1->FieldValues["KEIJKBN"];				//	�`��敪

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_LNG"])))
		KM02.SK_LD_LNG = Query1->FieldValues["SK_LD_LNG"];			//	����敪�@������

    if ( !(VarIsNull (Query1->FieldValues["SK_BURASI"])))
		KM02.SK_BURASI = Query1->FieldValues["SK_BURASI"];			//	�@�V�@�@�@�u���V��

    if ( !(VarIsNull (Query1->FieldValues["SK_BURASIT"])))
		KM02.SK_BURASIT = Query1->FieldValues["SK_BURASIT"];		//	�@�V�@�@�@�u���V���c����

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_TR"])))
		KM02.SK_LD_TR = Query1->FieldValues["SK_LD_TR"];			//	�@�V�@�@�@����t��R

    if ( !(VarIsNull (Query1->FieldValues["SK_LD_HP"])))
		KM02.SK_LD_HP = Query1->FieldValues["SK_LD_HP"];			//	�@�V�@�@�@���������x

    if ( !(VarIsNull (Query1->FieldValues["SK_BOTAI"])))
		KM02.SK_BOTAI = Query1->FieldValues["SK_BOTAI"];			//	�@�V�@�@�@��̔�d

    if ( !(VarIsNull (Query1->FieldValues["SK_KOYU"])))
		KM02.SK_KOYU = Query1->FieldValues["SK_KOYU"];				//	�@�V�@�@�@�ŗL��R

    if ( !(VarIsNull (Query1->FieldValues["SK_MAGE"])))
		KM02.SK_MAGE = Query1->FieldValues["SK_MAGE"];				//	�@�V�@�@�@�R�ܗ�

    if ( !(VarIsNull (Query1->FieldValues["SK_HSC_A"])))
		KM02.SK_HSC_A = Query1->FieldValues["SK_HSC_A"];			//	�@�V�@�@�@HsC�d�x�i���ʁj

    if ( !(VarIsNull (Query1->FieldValues["SK_HSC_S"])))
		KM02.SK_HSC_S = Query1->FieldValues["SK_HSC_S"];		   	//	�@�V�@�@�@HsC�d�x�i���ʁj

    if ( !(VarIsNull (Query1->FieldValues["SK_HSD_A"])))
		KM02.SK_HSD_A = Query1->FieldValues["SK_HSD_A"];			//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Query1->FieldValues["SK_HSD_S"])))
		KM02.SK_HSD_S = Query1->FieldValues["SK_HSD_S"];			//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Query1->FieldValues["SK_ZAKUT"])))
		KM02.SK_ZAKUT = Query1->FieldValues["SK_ZAKUT"];			//	�@�V�@�@�@HsD�d�x�i���ʁj

    if ( !(VarIsNull (Query1->FieldValues["HIST_SOKUT"])))
		KM02.HIST_SOKUT = Query1->FieldValues["HIST_SOKUT"];		//	�q�X�g�O�������萔

    if ( !(VarIsNull (Query1->FieldValues["HIST_KIKAK"])))
		KM02.HIST_KIKAK = Query1->FieldValues["HIST_KIKAK"];	   	//	�@�V�@�@�@�@�@�K�i

    if ( !(VarIsNull (Query1->FieldValues["HIST_MIN"])))
		KM02.HIST_MIN = Query1->FieldValues["HIST_MIN"];			//	�@�V�@�@�@�@�@�����K�i

    if ( !(VarIsNull (Query1->FieldValues["HIST_MAX"])))
		KM02.HIST_MAX = Query1->FieldValues["HIST_MAX"];			//	�@�V�@�@�@�@�@����K�i

    if ( !(VarIsNull (Query1->FieldValues["LD_LNG_MIN"])))
		KM02.LD_LNG_MIN = Query1->FieldValues["LD_LNG_MIN"];		//	���[�h�������@���

    if ( !(VarIsNull (Query1->FieldValues["LD_LNG_MAX"])))
		KM02.LD_LNG_MAX = Query1->FieldValues["LD_LNG_MAX"];		//	�@�V�@�@�@�@�@����

    if ( !(VarIsNull (Query1->FieldValues["BURASI_MIN"])))
		KM02.BURASI_MIN = Query1->FieldValues["BURASI_MIN"];		//	�u���V���@���

    if ( !(VarIsNull (Query1->FieldValues["BURASI_MAX"])))
		KM02.BURASI_MAX = Query1->FieldValues["BURASI_MAX"];		//	�@�V�@�@�@����

    if ( !(VarIsNull (Query1->FieldValues["BURASIT_MIN"])))
		KM02.BURASIT_MIN = Query1->FieldValues["BURASIT_MIN"];		//	�u���V���c�������

    if ( !(VarIsNull (Query1->FieldValues["BURASIT_MAX"])))
		KM02.BURASIT_MAX = Query1->FieldValues["BURASIT_MAX"];		//	�@�V�@�@�@�@�@����

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_DENA"])))
		KM02.LD_TR_DENA = Query1->FieldValues["LD_TR_DENA"];		//	���[�h����t����d��

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_DENR"])))
		KM02.LD_TR_DENR = Query1->FieldValues["LD_TR_DENR"];		//	�@�V�@�@��t����d��

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_TYPE"])))
		KM02.LD_TR_TYPE = Query1->FieldValues["LD_TR_TYPE"];		//	�@�V�@�@��t����^�C�v

    if ( !(VarIsNull (Query1->FieldValues["LD_TR_TIME"])))
		KM02.LD_TR_TIME = Query1->FieldValues["LD_TR_TIME"];		//	�@�V�@�@��t���莞��

	if ( !(VarIsNull (Query1->FieldValues["LD_HP_SPD"])))
		KM02.LD_HP_SPD = Query1->FieldValues["LD_HP_SPD"];			//	���[�h���������葬�x

    if ( !(VarIsNull (Query1->FieldValues["LD_HP_KYO"])))
		KM02.LD_HP_KYO = Query1->FieldValues["LD_HP_KYO"];			//	�@�V�@�@�������x

    if ( !(VarIsNull (Query1->FieldValues["LD_HP_TAN"])))
		KM02.LD_HP_TAN = Query1->FieldValues["LD_HP_TAN"];			//	�@�V�@�@�������x�P��

    if ( !(VarIsNull (Query1->FieldValues["BOTAI_MIN"])))
		KM02.BOTAI_MIN = Query1->FieldValues["BOTAI_MIN"];			//	��̔�d�@����

    if ( !(VarIsNull (Query1->FieldValues["BOTAI_MAX"])))
		KM02.BOTAI_MAX = Query1->FieldValues["BOTAI_MAX"];			//	�@�V�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["KOYU_MIN"])))
		KM02.KOYU_MIN = Query1->FieldValues["KOYU_MIN"];		   	//	�ŗL��R���@����

    if ( !(VarIsNull (Query1->FieldValues["KOYU_MAX"])))
		KM02.KOYU_MAX = Query1->FieldValues["KOYU_MAX"];			//	�@�V�@�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["KOYU_DEN"])))
		KM02.KOYU_DEN = Query1->FieldValues["KOYU_DEN"];			//	�@�V�@�@�@�@�d��

    if ( !(VarIsNull (Query1->FieldValues["KOYU_PRO"])))
		KM02.KOYU_PRO = Query1->FieldValues["KOYU_PRO"];			//	�@�V�@�@�@�@�v���[�u

    if ( !(VarIsNull (Query1->FieldValues["MAGE_MIN"])))
		KM02.MAGE_MIN = Query1->FieldValues["MAGE_MIN"];		   	//	�Ȃ����x�@����

    if ( !(VarIsNull (Query1->FieldValues["MAGE_MAX"])))
		KM02.MAGE_MAX = Query1->FieldValues["MAGE_MAX"];			//	�@�V�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["MAGE_TAN"])))
		KM02.MAGE_TAN = Query1->FieldValues["MAGE_TAN"];			//	�@�V�@�@�@�P��

    if ( !(VarIsNull (Query1->FieldValues["MAGE_SPAN"])))
		KM02.MAGE_SPAN = Query1->FieldValues["MAGE_SPAN"];			//	�@�V�@�@�@�X�p��

    if ( !(VarIsNull (Query1->FieldValues["HSC_A_MIN"])))
		KM02.HSC_A_MIN = Query1->FieldValues["HSC_A_MIN"];			//	�g���b�d�x�i���ʁj����

    if ( !(VarIsNull (Query1->FieldValues["HSC_A_MAX"])))
		KM02.HSC_A_MAX = Query1->FieldValues["HSC_A_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["HSC_S_MIN"])))
		KM02.HSC_S_MIN = Query1->FieldValues["HSC_S_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Query1->FieldValues["HSC_S_MAX"])))
		KM02.HSC_S_MAX = Query1->FieldValues["HSC_S_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["HSD_A_MIN"])))
		KM02.HSD_A_MIN = Query1->FieldValues["HSD_A_MIN"];			//	�g���c�d�x�i���ʁj����

    if ( !(VarIsNull (Query1->FieldValues["HSD_A_MAX"])))
		KM02.HSD_A_MAX = Query1->FieldValues["HSD_A_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["HSD_S_MIN"])))
		KM02.HSD_S_MIN = Query1->FieldValues["HSD_S_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Query1->FieldValues["HSD_S_MAX"])))
		KM02.HSD_S_MAX = Query1->FieldValues["HSD_S_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    if ( !(VarIsNull (Query1->FieldValues["ZAKUT_MIN"])))
		KM02.ZAKUT_MIN = Query1->FieldValues["ZAKUT_MIN"];			//	�@�V�@�@�@�i���ʁj����

    if ( !(VarIsNull (Query1->FieldValues["ZAKUT_MAX"])))
		KM02.ZAKUT_MAX = Query1->FieldValues["ZAKUT_MAX"];			//	�@�V�@�@�@�@�@�@�@���

    //2002/12/28 E.Takase Add
    if ( !(VarIsNull (Query1->FieldValues["MAGEG_MIN"])))
		KM02.MAGEG_MIN = Query1->FieldValues["MAGEG_MIN"];		   	//	�Ȃ����x�i�����j�@����

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_MAX"])))
		KM02.MAGEG_MAX = Query1->FieldValues["MAGEG_MAX"];			//	�@�V�@�@�@		  ���

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_TAN"])))
		KM02.MAGEG_TAN = Query1->FieldValues["MAGEG_TAN"];			//	�@�V�@�@�@		  �P��

    if ( !(VarIsNull (Query1->FieldValues["MAGEG_SPAN"])))
		KM02.MAGEG_SPAN = Query1->FieldValues["MAGEG_SPAN"];		//	�@�V�@�@�@		  �X�p��

	return(1);

}
