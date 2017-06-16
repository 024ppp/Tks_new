//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//2002/11/11 E.Takase
//�O���b�h����C���O�̃f�[�^���擾����B
void __fastcall TForm1::GetSGrData(int ARow)
{

	KM02.DTKSCOD	 = SGr1->Cells[1][ARow];      		    // ���Ӑ�R�[�h
	KM02.DTKSNAM	 = SGr1->Cells[62][ARow];      		    // ���Ӑ於��
	KM02.DTKSHIN	 = SGr1->Cells[2][ARow];      		    // ���Ӑ�i��
	KM02.HINBAN		 = SGr1->Cells[3][ARow];       		    // ���Еi��
	KM02.ZISNAM		 = SGr1->Cells[4][ARow];       		    // �ގ���
	KM02.ZISCOD		 = SGr1->Cells[5][ARow];       		    // �ގ��R�[�h
	KM02.SYOSCOD	 = SGr1->Cells[6][ARow];      		    // �Đ��R�[�h
	KM02.SORTKEY	 = StrToInt(SGr1->Cells[7][ARow]);	    // �\�[�g�L�[
	//KM02.KEIJKBN	 = SGr1->Cells[8][ARow];      // �`��敪
    KM02.KEIJKBN     = 0            ;                          // �`��敪
    if( SGr1->Cells[8][ARow] == "���^" ) KM02.KEIJKBN = 2;
    if( SGr1->Cells[8][ARow] == "��^" ) KM02.KEIJKBN = 3;
    if( SGr1->Cells[8][ARow] == "�~��" ) KM02.KEIJKBN = 4;
    if( SGr1->Cells[8][ARow] == "�R���~" ) KM02.KEIJKBN = 5;
    if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
	KM02.HIST_SOKUT	 = StrToInt(SGr1->Cells[23][ARow]);     // �q�X�g�O�����i���萔�j
	KM02.HIST_KIKAK	 = StrToInt(SGr1->Cells[24][ARow]);     // �q�X�g�O�����i�K�i�j
	KM02.HIST_MIN	 = StrToFloat(SGr1->Cells[25][ARow]);   // �q�X�g�O�����i�����j
	KM02.HIST_MAX	 = StrToFloat(SGr1->Cells[26][ARow]);   // �q�X�g�O�����i����j
	KM02.SK_LD_LNG	 = StrToInt(SGr1->Cells[64][ARow]);     // ����敪�@������
	KM02.SK_BURASI	 = StrToInt(SGr1->Cells[11][ARow]);     // ����敪�@�u���V��
	KM02.SK_BURASIT	 = StrToInt(SGr1->Cells[12][ARow]);     // ����敪�@�u���V���c����
	KM02.SK_BOTAI	 = StrToInt(SGr1->Cells[15][ARow]);     // ����敪�@��̔�d
	KM02.SK_LD_HP	 = StrToInt(SGr1->Cells[14][ARow]);     // ����敪�@���������x
	KM02.SK_LD_TR	 = StrToInt(SGr1->Cells[13][ARow]);     // ����敪�@����t��R
	KM02.SK_KOYU	 = StrToInt(SGr1->Cells[16][ARow]);     // ����敪�@�ŗL��R
	KM02.SK_MAGE	 = StrToInt(SGr1->Cells[17][ARow]);     // ����敪�@�R�ܗ�
	KM02.SK_HSC_A	 = StrToInt(SGr1->Cells[18][ARow]);     // ����敪�@HsC�d�x�i���ʁj
	KM02.SK_HSC_S	 = StrToInt(SGr1->Cells[19][ARow]);     // ����敪�@HsC�d�x�i���ʁj
	KM02.SK_HSD_A	 = StrToInt(SGr1->Cells[20][ARow]);     // ����敪�@HsD�d�x�i���ʁj
	KM02.SK_HSD_S	 = StrToInt(SGr1->Cells[21][ARow]);     // ����敪�@HsD�d�x�i���ʁj
	KM02.SK_ZAKUT	 = StrToInt(SGr1->Cells[22][ARow]);     // ����敪�@����
	KM02.LD_LNG_MIN	 = StrToFloat(SGr1->Cells[27][ARow]);   // ���[�h�������i�����j
	KM02.LD_LNG_MAX	 = StrToFloat(SGr1->Cells[28][ARow]);  	// ���[�h�������i����j
	KM02.BURASI_MIN	 = StrToFloat(SGr1->Cells[29][ARow]);	// �u���V���i�����j
	KM02.BURASI_MAX	 = StrToFloat(SGr1->Cells[30][ARow]);   // �u���V���i����j
	KM02.BURASIT_MIN = StrToFloat(SGr1->Cells[31][ARow]);  	// �u���V���c�����i�����j
	KM02.BURASIT_MAX = StrToFloat(SGr1->Cells[32][ARow]);  	// �u���V���c�����i����j
	KM02.BOTAI_MIN	 = StrToFloat(SGr1->Cells[39][ARow]);   // ��̔�d�i�����j
	KM02.BOTAI_MAX	 = StrToFloat(SGr1->Cells[40][ARow]);   // ��̔�d�i����j
	KM02.LD_HP_KYO	 = StrToFloat(SGr1->Cells[36][ARow]);   // ���[�h���������x
	KM02.LD_HP_TAN	 = StrToInt(SGr1->Cells[37][ARow]);    	// ���[�h���������x�i�P�ʁj
	KM02.LD_HP_SPD	 = StrToInt(SGr1->Cells[38][ARow]);   	// ���[�h���������x�i���x�j
	KM02.LD_TR_DENA	 = StrToFloat(SGr1->Cells[33][ARow]);   // ���[�h��t��R�i�d���j
	KM02.LD_TR_DENR	 = StrToInt(SGr1->Cells[34][ARow]);   	// ���[�h��t��R�i�d���j
	KM02.LD_TR_TIME	 = StrToInt(SGr1->Cells[35][ARow]);   	// ���[�h��t��R�i���ԁj
	KM02.LD_TR_TYPE	 = SGr1->Cells[63][ARow];   		    // ���[�h��t��R�iTYPE�j
	KM02.KOYU_MIN	 = StrToInt(SGr1->Cells[41][ARow]);     // �ŗL��R���i�����j
	KM02.KOYU_MAX	 = StrToInt(SGr1->Cells[42][ARow]);     // �ŗL��R���i����j
	KM02.KOYU_DEN	 = StrToFloat(SGr1->Cells[43][ARow]);   // �ŗL��R���i�d���j
	KM02.KOYU_PRO	 = StrToInt(SGr1->Cells[44][ARow]);     // �ŗL��R���i�v���[�u�j
	KM02.MAGE_MIN	 = StrToFloat(SGr1->Cells[45][ARow]);   // �Ȃ����x�i�����j
	KM02.MAGE_MAX	 = StrToFloat(SGr1->Cells[46][ARow]);   // �Ȃ����x�i����j
   	KM02.MAGE_TAN	 = StrToInt(SGr1->Cells[47][ARow]);     // �Ȃ����x�i�P�ʁj
	KM02.MAGE_SPAN	 = StrToFloat(SGr1->Cells[48][ARow]);   // �Ȃ����x�i�X�p���j
	KM02.HSC_A_MIN	 = StrToInt(SGr1->Cells[49][ARow]);   	// HsC�d�x ���ʁi�����j
	KM02.HSC_A_MAX	 = StrToInt(SGr1->Cells[50][ARow]);    	// HsC�d�x ���ʁi����j
	KM02.HSC_S_MIN	 = StrToInt(SGr1->Cells[51][ARow]);    	// HsC�d�x ���ʁi�����j
	KM02.HSC_S_MAX	 = StrToInt(SGr1->Cells[52][ARow]);    	// HsC�d�x ���ʁi����j
	KM02.HSD_A_MIN	 = StrToFloat(SGr1->Cells[53][ARow]);   // HsD�d�x ���ʁi�����j
	KM02.HSD_A_MAX	 = StrToFloat(SGr1->Cells[54][ARow]);   // HsD�d�x ���ʁi����j
	KM02.HSD_S_MIN	 = StrToFloat(SGr1->Cells[55][ARow]);   // HsD�d�x ���ʁi�����j
	KM02.HSD_S_MAX	 = StrToFloat(SGr1->Cells[56][ARow]);   // HsD�d�x ���ʁi����j
	KM02.ZAKUT_MIN	 = StrToInt(SGr1->Cells[57][ARow]);    	// �����i�����j
	KM02.ZAKUT_MAX	 = StrToInt(SGr1->Cells[58][ARow]);    	// �����i����j
	KM02.ADDYMD	 = SGr1->Cells[59][ARow];               // �o�^��
	KM02.UPDYMD	 = SGr1->Cells[60][ARow];               // �ύX��
	KM02.UPDCNT	 = SGr1->Cells[61][ARow].ToIntDef(0);   // �X�V��
	KM02.REVCNT	 = SGr1->Cells[10][ARow].ToIntDef(0);   // �����ԍ�
	KM02.UPDCHR	 = SGr1->Cells[65][ARow].ToIntDef(0);   // �X�V��
	KM02.MEMO	 = SGr1->Cells[66][ARow];               // ���l
	KM02.ADDTIM	 = SGr1->Cells[67][ARow];               // �o�^����
	KM02.UPDTIM	 = SGr1->Cells[68][ARow];               // �ύX����

    //2002/12/05 �����Ȃ�����  E.Takase
  	KM02.SK_MAGEG	 = StrToInt(SGr1->Cells[69][ARow]);     // ����敪�@�����Ȃ����x
	KM02.MAGEG_MIN	 = StrToFloat(SGr1->Cells[70][ARow]);   // �����Ȃ����x�i�����j
	KM02.MAGEG_MAX	 = StrToFloat(SGr1->Cells[71][ARow]);   // �����Ȃ����x�i����j
   	KM02.MAGEG_TAN	 = StrToInt(SGr1->Cells[72][ARow]);     // �����Ȃ����x�i�P�ʁj
	KM02.MAGEG_SPAN	 = StrToFloat(SGr1->Cells[73][ARow]);   // �����Ȃ����x�i�X�p���j


}
//---------------------------------------------------------------------------
//2002/11/19 E.Takase
//�f�[�^���͕�����f�[�^���擾����B
void __fastcall TForm1::GetEdtData(void)
{
     AnsiString sBuf;
     bool       fNG;

     //2002/11/22 �u'�v���u_�v�ɒu�� E.Takase
	 if( Edt01->Text != "" ) Edt01->Text = StrReplace(Edt01->Text , "'", "_");
	 if( Edt02->Text != "" ) Edt02->Text = StrReplace(Edt02->Text , "'", "_");
	 if( Edt03->Text != "" ) Edt03->Text = StrReplace(Edt03->Text , "'", "_");
	 if( Edt04->Text != "" ) Edt04->Text = StrReplace(Edt04->Text , "'", "_");
     if( Edt05->Text != "" ) Edt05->Text = StrReplace(Edt05->Text , "'", "_");
	 if( Edt06->Text != "" ) Edt06->Text = StrReplace(Edt06->Text , "'", "_");

     if( Edt01->Text == "" )  KM02.DTKSCOD = " ";               // ���Ӑ�R�[�h
     else                     KM02.DTKSCOD = Edt01->Text ;      // ���Ӑ�R�[�h
     if( Edt02->Text == "" )  KM02.DTKSNAM = " " ;              // ���Ӑ於��
     else                     KM02.DTKSNAM = Edt02->Text ;      // ���Ӑ於��
     if( Edt03->Text == "" )  KM02.DTKSHIN = " " ;              // ���Ӑ�i��
     else                     KM02.DTKSHIN = Edt03->Text ;      // ���Ӑ�i��
     if( Edt04->Text == "" )  KM02.HINBAN  = " " ;              // ���Еi��
     else                     KM02.HINBAN  = Edt04->Text ;      // ���Еi��
     if( Edt05->Text == "" )  KM02.ZISNAM  = " " ;              // �ގ�����
     else                     KM02.ZISNAM  = Edt05->Text ;      // �ގ�����
     if( Edt06->Text == "" )  KM02.ZISCOD  = " " ;              // �ގ��R�[�h
     else                     KM02.ZISCOD  = Edt06->Text ;      // �ގ��R�[�h
     if( Edt07->Text == "" )  KM02.SYOSCOD = " " ;              // �Đ��R�[�h
     else                     KM02.SYOSCOD = Edt07->Text ;      // �Đ��R�[�h

     KM02.SORTKEY     = Edt08->Value ;                          // �\�[�g�L�[
     KM02.KEIJKBN     = 0            ;                          // �`��敪
     if( ComBox09->Text == "���^" ) KM02.KEIJKBN = 2;
     if( ComBox09->Text == "��^" ) KM02.KEIJKBN = 3;
     if( ComBox09->Text == "�~��" ) KM02.KEIJKBN = 4;
     if( ComBox09->Text == "�R���~" ) KM02.KEIJKBN = 5;         // 2002.10.30 Add By Takase
     if( KM02.KEIJKBN   == 0      ) KM02.KEIJKBN = 1;
     if( ChkBoxA->Checked ) KM02.SK_LD_LNG  = ChkEdtA->Value ;  // ����敪�@������
     else                   KM02.SK_LD_LNG  = 0 ;
     if( ChkBoxB->Checked ) KM02.SK_BURASI  = ChkEdtB->Value ;  // ����敪�@�u���V��
     else                   KM02.SK_BURASI  = 0 ;
     if( ChkBoxC->Checked ) KM02.SK_BURASIT = ChkEdtC->Value ;  // ����敪�@�u���V���c����
     else                   KM02.SK_BURASIT = 0 ;
     if( ChkBoxD->Checked ) KM02.SK_BOTAI   = ChkEdtD->Value ;  // ����敪�@��̔�d
     else                   KM02.SK_BOTAI   = 0  ;
     if( ChkBoxE->Checked ) KM02.SK_LD_HP   = ChkEdtE->Value ;  // ����敪�@���������x
     else                   KM02.SK_LD_HP   = 0 ;
     if( ChkBoxF->Checked ) KM02.SK_LD_TR   = ChkEdtF->Value ;  // ����敪�@����t��R
     else                   KM02.SK_LD_TR   = 0 ;
     if( ChkBoxG->Checked ) KM02.SK_KOYU    = ChkEdtG->Value ;  // ����敪�@�ŗL��R
     else                   KM02.SK_KOYU    = 0 ;
     if( ChkBoxH->Checked ) KM02.SK_MAGE    = ChkEdtH->Value ;  // ����敪�@�R�ܗ�
     else                   KM02.SK_MAGE    = 0 ;
     if( ChkBoxI->Checked ) KM02.SK_HSC_A   = ChkEdtI->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_A   = 0 ;
     if( ChkBoxJ->Checked ) KM02.SK_HSC_S   = ChkEdtJ->Value ;  // ����敪�@HsC�d�x�i���ʁj
     else                   KM02.SK_HSC_S   = 0 ;
     if( ChkBoxK->Checked ) KM02.SK_HSD_A   = ChkEdtK->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_A   = 0 ;
     if( ChkBoxL->Checked ) KM02.SK_HSD_S   = ChkEdtL->Value ;  // ����敪�@HsD�d�x�i���ʁj
     else                   KM02.SK_HSD_S   = 0 ;
     if( ChkBoxM->Checked ) KM02.SK_ZAKUT   = ChkEdtM->Value ;  // ����敪�@����
     else                   KM02.SK_ZAKUT   = 0 ;
     KM02.HIST_SOKUT  = Edt10->Value ;                          // �q�X�g�O�����i���萔�j
     KM02.HIST_KIKAK  = 0            ;                          // �q�X�g�O�����i�K�i�j
     if( ComBox11->Text  == "����" ) KM02.HIST_KIKAK = 2;
     if( ComBox11->Text  == "���" ) KM02.HIST_KIKAK = 3;
     if( KM02.HIST_KIKAK == 0      ) KM02.HIST_KIKAK = 1;
     KM02.HIST_MIN    = Edt12->Value ;                          // �q�X�g�O�����i�����j
     KM02.HIST_MAX    = Edt13->Value ;                          // �q�X�g�O�����i����j
     KM02.LD_LNG_MIN  = EdtA1->Value ;                          // ���[�h�������i�����j
     KM02.LD_LNG_MAX  = EdtA2->Value ;                          // ���[�h�������i����j
     KM02.BURASI_MIN  = EdtB1->Value ;                          // �u���V���i�����j
     KM02.BURASI_MAX  = EdtB2->Value ;                          // �u���V���i����j
     KM02.BURASIT_MIN = EdtC1->Value ;                          // �u���V���c�����i�����j
     KM02.BURASIT_MAX = EdtC2->Value ;                          // �u���V���c�����i����j
     KM02.BOTAI_MIN   = EdtD1->Value ;                          // ��̔�d�i�����j
     KM02.BOTAI_MAX   = EdtD2->Value ;                          // ��̔�d�i����j
     KM02.LD_HP_KYO   = EdtE1->Value ;                          // ���[�h���������x
     KM02.LD_HP_TAN   = 0;                                      // ���[�h���������x�i�P�ʁj
     sBuf = ComBoxE2->Text.UpperCase();
     if( sBuf[1] == 'K'      ) KM02.LD_HP_TAN = 1;              // Kgf
     if( KM02.LD_HP_TAN == 0 ) KM02.LD_HP_TAN = 2;              // N
     KM02.LD_HP_SPD   = EdtE3->Value ;                          // ���[�h���������x�i���x�j
     KM02.LD_TR_DENA  = EdtF1->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_DENR  = EdtF2->Value ;                          // ���[�h��t��R�i�d���j
     KM02.LD_TR_TIME  = EdtF3->Value ;                          // ���[�h��t��R�i���ԁj
     if( EdtF4->Text == "" )  KM02.LD_TR_TYPE = " " ;           // ���[�h��t��R�iTYPE�j
     else                     KM02.LD_TR_TYPE = EdtF4->Text ;
     KM02.KOYU_MIN    = EdtG1->Value ;                          // �ŗL��R���i�����j
     KM02.KOYU_MAX    = EdtG2->Value ;                          // �ŗL��R���i����j
     KM02.KOYU_DEN    = EdtG3->Value ;                          // �ŗL��R���i�d���j
     KM02.KOYU_PRO    = EdtG4->Value ;                          // �ŗL��R���i�v���[�u�j
     KM02.MAGE_MIN    = EdtH1->Value ;                          // �Ȃ����x�i�����j
     KM02.MAGE_MAX    = EdtH2->Value ;                          // �Ȃ����x�i����j
     KM02.MAGE_TAN    = 0;                                      // �Ȃ����x�i�P�ʁj
     sBuf = ComBoxH3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGE_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGE_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGE_TAN = 3;                  // MPa
     if( KM02.MAGE_TAN == 0          ) KM02.MAGE_TAN = 4;                  // N/mm2
     KM02.MAGE_SPAN   = EdtH4->Value ;                          // �Ȃ����x�i�X�p���j
     KM02.HSC_A_MIN   = EdtI1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_A_MAX   = EdtI2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSC_S_MIN   = EdtJ1->Value ;                          // HsC�d�x ���ʁi�����j
     KM02.HSC_S_MAX   = EdtJ2->Value ;                          // HsC�d�x ���ʁi����j
     KM02.HSD_A_MIN   = EdtK1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_A_MAX   = EdtK2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.HSD_S_MIN   = EdtL1->Value ;                          // HsD�d�x ���ʁi�����j
     KM02.HSD_S_MAX   = EdtL2->Value ;                          // HsD�d�x ���ʁi����j
     KM02.ZAKUT_MIN   = EdtM1->Value ;                          // �����i�����j
     KM02.ZAKUT_MAX   = EdtM2->Value ;                          // �����i����j
     KM02.ADDYMD      = FormatDateTime("yyyymmdd",Date());                // �o�^��
     KM02.ADDTIM      = FormatDateTime("hhmm",TDateTime::CurrentTime());  // �o�^����
     //KM02.UPDYMD      = FormatDateTime("yyyymmdd",Date());               // �ύX��
     //KM02.UPDTIM      = FormatDateTime("hhmm",TDateTime::CurrentTime()); // �ύX����
     KM02.UPDYMD      = "";                                    // �ύX��
     KM02.UPDTIM      = "";                                    // �ύX����
     KM02.UPDCHR      = USER_COD;                               // �X�V��
     //if( SGr1->Cells[61][SGr1->Row] == "" ){
     //   KM02.UPDCNT  = 0;
     //}
     //else{
     //   KM02.UPDCNT  = StrToInt(SGr1->Cells[61][SGr1->Row]) ;   // �X�V��
     //   KM02.UPDCNT += 1 ;
     //}
     //if( Trim(PnlUPDCNT2->Caption) == "" ||  Trim(PnlUPDCNT2->Caption) == "0" ){
     //   KM02.UPDCNT  = 1;
     //}
     //else{
     //   KM02.UPDCNT  = StrToInt(Trim(PnlUPDCNT2->Caption)) ;   // �X�V��
     //   KM02.UPDCNT += 1 ;
     //}

     //2002/11/11 E.Takase
     KM02.REVCNT      = 0;                                      // �X�V��
     KM02.MEMO        = Trim(EdtMEMO->Text) ;                   // ���l

     //2002/12/05 E.Takase  �����Ȃ����x �ǉ�
     if( ChkBoxN->Checked ) KM02.SK_MAGEG    = ChkEdtN->Value ;  // ����敪�@�����Ȃ����x
     else                   KM02.SK_MAGEG    = 0 ;
     KM02.MAGEG_MIN    = EdtN1->Value ;                          // �����Ȃ����x�i����j
     KM02.MAGEG_MAX    = EdtN2->Value ;                          // �����Ȃ����x�i����j
     KM02.MAGEG_TAN    = 0;                                      // �����Ȃ����x�i�P�ʁj
     sBuf = ComBoxN3->Text.UpperCase();
     if( sBuf[1] == 'K'              ) KM02.MAGEG_TAN = 1;                  // Kgf
     if( sBuf.SetLength(3) == "N/C"  ) KM02.MAGEG_TAN = 2;                  // N/cm2
     if( sBuf[1] == 'M'              ) KM02.MAGEG_TAN = 3;                  // MPa
     //2003/07/22 E.Takase �P�ʂɁuN�v�ǉ�
     if( sBuf[1] == 'N'              ) KM02.MAGEG_TAN = 5;                  // N
     if( KM02.MAGEG_TAN == 0          ) KM02.MAGEG_TAN = 4;                  // N/mm2
     KM02.MAGEG_SPAN   = EdtN4->Value ;                          // �����Ȃ����x�i�X�p���j

     KM02.UPDCNT = 0;
}
//---------------------------------------------------------------------------
//�f�[�^���͕��̃f�[�^���O���b�h�ɃZ�b�g���܂��B
void __fastcall TForm1::SetEdtData(int ARow)
{
     AnsiString sBuf;
     bool       fNG;

     // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
     sBuf = ARow+1 ;                                // NO
     SGr1->Cells[0][ARow] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
     sBuf = KM02.DTKSCOD;                              		// ���Ӑ�R�[�h
     SGr1->Cells[1][ARow] = sBuf;
     sBuf = KM02.DTKSHIN;                              		// ���Ӑ�i��
     SGr1->Cells[2][ARow] = sBuf;
     sBuf = KM02.HINBAN;                               		// ���Еi��
     SGr1->Cells[3][ARow] = sBuf;
     sBuf = KM02.ZISNAM;                               		// �ގ�����
     SGr1->Cells[4][ARow] = sBuf;
     sBuf = KM02.ZISCOD;                               		// �ގ��R�[�h
     SGr1->Cells[5][ARow] = sBuf;
     sBuf = KM02.SYOSCOD;                              		// �Đ��R�[�h
     SGr1->Cells[6][ARow] = sBuf;
     sBuf = IntToStr(KM02.SORTKEY);                         // �\�[�g�L�[
     SGr1->Cells[7][ARow] = AnsiString::StringOfChar(' ', 6 - sBuf.Length()) + sBuf;
     if( KM02.KEIJKBN == 1 ) sBuf = "���^";                 // �`��敪
     if( KM02.KEIJKBN == 2 ) sBuf = "���^";
     if( KM02.KEIJKBN == 3 ) sBuf = "��^";
     if( KM02.KEIJKBN == 4 ) sBuf = "�~��";
     if( KM02.KEIJKBN == 5 ) sBuf = "�R���~";               //2002.10.21 Add By Takase
     SGr1->Cells[8][ARow] = sBuf;
     sBuf = KM02.ADDYMD;                               		// �X�V��
     sBuf = sBuf.Insert("/",5);
     sBuf = sBuf.Insert("/",8);
     SGr1->Cells[9][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_LNG);                       // ����敪�@������
     //2002/11/11 E.Takase SGr1->Cells[10][ARow] = sBuf;
     SGr1->Cells[64][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASI);                       // ����敪�@�u���V��
     SGr1->Cells[11][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_BURASIT);                      // ����敪�@�u���V���c����
     SGr1->Cells[12][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_TR);                        // ����敪�@����t��R
     SGr1->Cells[13][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_LD_HP);                        // ����敪�@���������x
     SGr1->Cells[14][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_BOTAI);                        // ����敪�@��̔�d
     SGr1->Cells[15][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_KOYU);                         // ����敪�@�ŗL��R
     SGr1->Cells[16][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_MAGE);                         // ����敪�@�R�ܗ�
     SGr1->Cells[17][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_A);                        // ����敪�@HsC�d�x�i���ʁj
     SGr1->Cells[18][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_HSC_S);                        // ����敪�@HsC�d�x�i���ʁj
     SGr1->Cells[19][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_A);                        // ����敪�@HsD�d�x�i���ʁj
     SGr1->Cells[20][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_HSD_S);                        // ����敪�@HsD�d�x�i���ʁj
     SGr1->Cells[21][ARow] = sBuf;
     sBuf = IntToStr(KM02.SK_ZAKUT);                        // ����敪�@����
     SGr1->Cells[22][ARow] = sBuf;
     sBuf = IntToStr(KM02.HIST_SOKUT);                      // �q�X�g�O�����i���萔�j
     SGr1->Cells[23][ARow] = sBuf;
     sBuf = IntToStr(KM02.HIST_KIKAK);                      // �q�X�g�O�����i�K�i�j
     SGr1->Cells[24][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MIN);                      // �q�X�g�O�����i�����j
     SGr1->Cells[25][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HIST_MAX);                      // �q�X�g�O�����i����j
     SGr1->Cells[26][ARow] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MIN);                    // ���[�h�������i�����j
     SGr1->Cells[27][ARow] = sBuf;
     sBuf = FloatToStr(KM02.LD_LNG_MAX);                    // ���[�h�������i����j
     SGr1->Cells[28][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MIN);                    // �u���V���i�����j
     SGr1->Cells[29][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BURASI_MAX);                    // �u���V���i����j
     SGr1->Cells[30][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MIN);                   // �u���V���c�����i�����j
     SGr1->Cells[31][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BURASIT_MAX);                   // �u���V���c�����i����j
     SGr1->Cells[32][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MIN);                     // ��̔�d�i�����j
     SGr1->Cells[39][ARow] = sBuf;
     sBuf = FloatToStr(KM02.BOTAI_MAX);                     // ��̔�d�i����j
     SGr1->Cells[40][ARow] = sBuf;
     sBuf = FloatToStr(KM02.LD_HP_KYO);                     // ���[�h���������x
     SGr1->Cells[36][ARow] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_TAN);                       // ���[�h���������x�i�P�ʁj
     SGr1->Cells[37][ARow] = sBuf;
     sBuf = IntToStr(KM02.LD_HP_SPD);                       // ���[�h���������x�i���x�j
     SGr1->Cells[38][ARow] = sBuf;
     sBuf = FloatToStr(KM02.LD_TR_DENA);                    // ���[�h��t��R�i�d���j
     SGr1->Cells[33][ARow] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_DENR);                      // ���[�h��t��R�i�d���j
     SGr1->Cells[34][ARow] = sBuf;
     sBuf = IntToStr(KM02.LD_TR_TIME);                      // ���[�h��t��R�i���ԁj
     SGr1->Cells[35][ARow] = sBuf;
     sBuf = KM02.LD_TR_TYPE;                                // ���[�h��t��R�iTYPE�j
     SGr1->Cells[63][ARow] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MIN);                        // �ŗL��R���i�����j
     SGr1->Cells[41][ARow] = sBuf;
     sBuf = IntToStr(KM02.KOYU_MAX);                        // �ŗL��R���i����j
     SGr1->Cells[42][ARow] = sBuf;
     sBuf = FloatToStr(KM02.KOYU_DEN);                      // �ŗL��R���i�d���j
     SGr1->Cells[43][ARow] = sBuf;
     sBuf = IntToStr(KM02.KOYU_PRO);                        // �ŗL��R���i�v���[�u�j
     SGr1->Cells[44][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MIN);                      // �Ȃ����x�i�����j
     SGr1->Cells[45][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_MAX);                      // �Ȃ����x�i����j
     SGr1->Cells[46][ARow] = sBuf;
     sBuf = IntToStr(KM02.MAGE_TAN);                        // �Ȃ����x�i�P�ʁj
     SGr1->Cells[47][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGE_SPAN);                     // �Ȃ����x�i�X�p���j
     SGr1->Cells[48][ARow] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MIN);                       // HsC�d�x ���ʁi�����j
     SGr1->Cells[49][ARow] = sBuf;
     sBuf = IntToStr(KM02.HSC_A_MAX);                       // HsC�d�x ���ʁi����j
     SGr1->Cells[50][ARow] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MIN);                       // HsC�d�x ���ʁi�����j
     SGr1->Cells[51][ARow] = sBuf;
     sBuf = IntToStr(KM02.HSC_S_MAX);                       // HsC�d�x ���ʁi����j
     SGr1->Cells[52][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MIN);                     // HsD�d�x ���ʁi�����j
     SGr1->Cells[53][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HSD_A_MAX);                     // HsD�d�x ���ʁi����j
     SGr1->Cells[54][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MIN);                     // HsD�d�x ���ʁi�����j
     SGr1->Cells[55][ARow] = sBuf;
     sBuf = FloatToStr(KM02.HSD_S_MAX);                     // HsD�d�x ���ʁi����j
     SGr1->Cells[56][ARow] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MIN);                       // �����i�����j
     SGr1->Cells[57][ARow] = sBuf;
     sBuf = IntToStr(KM02.ZAKUT_MAX);                       // �����i����j
     SGr1->Cells[58][ARow] = sBuf;
     sBuf = KM02.ADDYMD;                               		// �o�^��
     SGr1->Cells[59][ARow] = sBuf;
     sBuf = KM02.UPDYMD;                               		// �ύX��
     SGr1->Cells[60][ARow] = sBuf;
     sBuf = IntToStr(KM02.UPDCNT);                          // �X�V��
     SGr1->Cells[61][ARow] = sBuf;
     sBuf = KM02.DTKSNAM;                              		// ���Ӑ於��
     SGr1->Cells[62][ARow] = sBuf;
     //2002/11/11 E.Takase
     sBuf =  IntToStr(KM02.REVCNT);                       	// �����ԍ�
     SGr1->Cells[10][ARow] = sBuf;
     sBuf =  KM02.UPDCHR;                       	        // �X�V��
     SGr1->Cells[65][ARow] = sBuf;
     sBuf =  KM02.MEMO;                       	            // ���l
     SGr1->Cells[66][ARow] = sBuf;

     //2002/12/05 E.Takase �����Ȃ����x�ǉ�
     sBuf = IntToStr(KM02.SK_MAGEG);                         // ����敪�@�����Ȃ����x
     SGr1->Cells[69][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MIN);                      // �����Ȃ����x�i�����j
     SGr1->Cells[70][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_MAX);                      // �����Ȃ����x�i����j
     SGr1->Cells[71][ARow] = sBuf;
     sBuf = IntToStr(KM02.MAGEG_TAN);                        // �����Ȃ����x�i�P�ʁj
     SGr1->Cells[72][ARow] = sBuf;
     sBuf = FloatToStr(KM02.MAGEG_SPAN);                     // �����Ȃ����x�i�X�p���j
     SGr1->Cells[73][ARow] = sBuf;


}
//---------------------------------------------------------------------------
//�����ԍ����X�V����B
//�����ԍ�0�̃f�[�^�͍X�V�����X�V
int __fastcall TForm1::UpdRirekiNo(int ARow)
{
    int iREVCNT;
    int iUPDCNT;
    AnsiString sBuf;
    AnsiString sUpdBuf;

    // Initial Query
    Query1->Close();
    Query1->SQL->Clear();

	KM02.DTKSHIN = SGr1->Cells[2][ARow];      		    // ���Ӑ�i��
	KM02.REVCNT = SGr1->Cells[10][ARow].ToIntDef(0);    // �����ԍ�

    // �⍇�����s
    sBuf = "SELECT REVCNT, UPDCNT FROM KM02 ";
    sBuf = sBuf + "WHERE DTKSHIN='" + KM02.DTKSHIN + "'";
    sBuf = sBuf + "ORDER BY REVCNT DESC";

    Query1->SQL->Add(sBuf);
    Query1->Open();
    Query1->Active = true;
    while( !Query1->Eof ){
        iREVCNT = Query1->Fields->Fields[0]->AsInteger;
        iUPDCNT = Query1->Fields->Fields[1]->AsInteger;

        //�����ԍ� �X�V
        sUpdBuf = " UPDATE KM02 SET REVCNT = " + IntToStr( iREVCNT + 1 ) ;
        if ( iREVCNT == KM02.REVCNT ) {
            sUpdBuf = sUpdBuf + ", UPDCNT = " + IntToStr( iUPDCNT + 1 ) ;
            sUpdBuf = sUpdBuf + ", UPDYMD = '" + FormatDateTime("yyyymmdd",Date()) + "'";
            sUpdBuf = sUpdBuf + ", UPDTIM = '" + FormatDateTime("hhmm",TDateTime::CurrentTime()) + "'";
        }
        sUpdBuf = sUpdBuf + " WHERE DTKSHIN = '" + KM02.DTKSHIN + "'";
        sUpdBuf = sUpdBuf + " AND REVCNT = " + IntToStr( iREVCNT ) ;

        // Initial Query
        Query2->Close();
        Query2->SQL->Clear();

	    Query2->SQL->Add(sUpdBuf);

	    // �₢�������̎��s
	    try
	    {
	        ClpBrd = Clipboard();
	        ClpBrd->Open();
	        ClpBrd->SetTextBuf(sBuf.c_str());
	        ClpBrd->Close();
	        Query2->ExecSQL();
	    }
	    catch(EDatabaseError& e)
	    {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	        //return(False);
	    }
	    catch(Exception& e)
	    {
	        SBr1->Panels->Items[0]->Text = e.Message;
	        SBr1->Update();
	        Beep();
	        //return(False);
	    }


        // �J�[�\�������ɃZ�b�g����
        Query1->Next();

    }
}
//---------------------------------------------------------------------------

//�����f�[�^���O���b�h�ɑ}���B
void __fastcall TForm1::InsSGrRirekiData(void)
{
    int i;
    int flag;
    int ARow;
    AnsiString sBuf;
    AnsiString sDTKSHIN;
    int iREVCNT;

    ARow = SGr1->Row ;
    sDTKSHIN = SGr1->Cells[2][ARow];
    iREVCNT = SGr1->Cells[10][ARow].ToIntDef(0);
    //�X�V���A�X�V�񐔂��C��
    SGr1->Cells[60][ARow] = FormatDateTime("yyyymmdd",Date());
    SGr1->Cells[61][ARow] = IntToStr(SGr1->Cells[61][ARow].ToIntDef(0) + 1);

    //�ŐV�̃f�[�^�̈ʒu������
    flag = 0;
    if ( iREVCNT != 0 ) {
        for ( i = ARow-1; i >= 0; i-- ) {
            if ( SGr1->Cells[10][i].ToIntDef(0) == 0 ) {
                ARow = i;
                flag = 1;
                break;
            }
        }

        if ( flag == 0 ) {
            for ( i = ARow+1; i < SGr1->RowCount-1 ; i++ ) {
                if ( SGr1->Cells[10][i].ToIntDef(0) == 0 ) {
                    ARow = i;
                    flag = 1;
                    break;
                }
            }
        }

    }

        SGr1->RowCount++;

    //2008/02/22 E.Takase �ii >= ARow �� i > ARow �j
    //for ( i = SGr1->RowCount; i >= ARow; i-- ) {
    for ( i = SGr1->RowCount; i > ARow; i-- ) {
		SGr1->Cells[0][i] = SGr1->Cells[0][i-1];
		SGr1->Cells[1][i] = SGr1->Cells[1][i-1];
		SGr1->Cells[2][i] = SGr1->Cells[2][i-1];
		SGr1->Cells[3][i] = SGr1->Cells[3][i-1];
		SGr1->Cells[4][i] = SGr1->Cells[4][i-1];
		SGr1->Cells[5][i] = SGr1->Cells[5][i-1];
		SGr1->Cells[6][i] = SGr1->Cells[6][i-1];
		SGr1->Cells[7][i] = SGr1->Cells[7][i-1];
		SGr1->Cells[8][i] = SGr1->Cells[8][i-1];
		SGr1->Cells[9][i] = SGr1->Cells[9][i-1];
		SGr1->Cells[10][i] = SGr1->Cells[10][i-1];
		SGr1->Cells[11][i] = SGr1->Cells[11][i-1];
		SGr1->Cells[12][i] = SGr1->Cells[12][i-1];
		SGr1->Cells[13][i] = SGr1->Cells[13][i-1];
		SGr1->Cells[14][i] = SGr1->Cells[14][i-1];
		SGr1->Cells[15][i] = SGr1->Cells[15][i-1];
		SGr1->Cells[16][i] = SGr1->Cells[16][i-1];
		SGr1->Cells[17][i] = SGr1->Cells[17][i-1];
		SGr1->Cells[18][i] = SGr1->Cells[18][i-1];
		SGr1->Cells[19][i] = SGr1->Cells[19][i-1];
		SGr1->Cells[20][i] = SGr1->Cells[20][i-1];
		SGr1->Cells[21][i] = SGr1->Cells[21][i-1];
		SGr1->Cells[22][i] = SGr1->Cells[22][i-1];
		SGr1->Cells[23][i] = SGr1->Cells[23][i-1];
		SGr1->Cells[24][i] = SGr1->Cells[24][i-1];
		SGr1->Cells[25][i] = SGr1->Cells[25][i-1];
		SGr1->Cells[26][i] = SGr1->Cells[26][i-1];
		SGr1->Cells[27][i] = SGr1->Cells[27][i-1];
		SGr1->Cells[28][i] = SGr1->Cells[28][i-1];
		SGr1->Cells[29][i] = SGr1->Cells[29][i-1];
		SGr1->Cells[30][i] = SGr1->Cells[30][i-1];
		SGr1->Cells[31][i] = SGr1->Cells[31][i-1];
		SGr1->Cells[32][i] = SGr1->Cells[32][i-1];
		SGr1->Cells[33][i] = SGr1->Cells[33][i-1];
		SGr1->Cells[34][i] = SGr1->Cells[34][i-1];
		SGr1->Cells[35][i] = SGr1->Cells[35][i-1];
		SGr1->Cells[36][i] = SGr1->Cells[36][i-1];
		SGr1->Cells[37][i] = SGr1->Cells[37][i-1];
		SGr1->Cells[38][i] = SGr1->Cells[38][i-1];
		SGr1->Cells[39][i] = SGr1->Cells[39][i-1];
		SGr1->Cells[40][i] = SGr1->Cells[40][i-1];
		SGr1->Cells[41][i] = SGr1->Cells[41][i-1];
		SGr1->Cells[42][i] = SGr1->Cells[42][i-1];
		SGr1->Cells[43][i] = SGr1->Cells[43][i-1];
		SGr1->Cells[44][i] = SGr1->Cells[44][i-1];
		SGr1->Cells[45][i] = SGr1->Cells[45][i-1];
		SGr1->Cells[46][i] = SGr1->Cells[46][i-1];
		SGr1->Cells[47][i] = SGr1->Cells[47][i-1];
		SGr1->Cells[48][i] = SGr1->Cells[48][i-1];
		SGr1->Cells[49][i] = SGr1->Cells[49][i-1];
		SGr1->Cells[50][i] = SGr1->Cells[50][i-1];
		SGr1->Cells[51][i] = SGr1->Cells[51][i-1];
		SGr1->Cells[52][i] = SGr1->Cells[52][i-1];
		SGr1->Cells[53][i] = SGr1->Cells[53][i-1];
		SGr1->Cells[54][i] = SGr1->Cells[54][i-1];
		SGr1->Cells[55][i] = SGr1->Cells[55][i-1];
		SGr1->Cells[56][i] = SGr1->Cells[56][i-1];
		SGr1->Cells[57][i] = SGr1->Cells[57][i-1];
		SGr1->Cells[58][i] = SGr1->Cells[58][i-1];
		SGr1->Cells[59][i] = SGr1->Cells[59][i-1];
		SGr1->Cells[60][i] = SGr1->Cells[60][i-1];
		SGr1->Cells[61][i] = SGr1->Cells[61][i-1];
		SGr1->Cells[62][i] = SGr1->Cells[62][i-1];
		SGr1->Cells[63][i] = SGr1->Cells[63][i-1];
		SGr1->Cells[64][i] = SGr1->Cells[64][i-1];
		SGr1->Cells[65][i] = SGr1->Cells[65][i-1];
		SGr1->Cells[66][i] = SGr1->Cells[66][i-1];
		SGr1->Cells[67][i] = SGr1->Cells[67][i-1];
		SGr1->Cells[68][i] = SGr1->Cells[68][i-1];

        //2002/12/05 E.Takase
		SGr1->Cells[69][i] = SGr1->Cells[69][i-1];
		SGr1->Cells[70][i] = SGr1->Cells[70][i-1];
		SGr1->Cells[71][i] = SGr1->Cells[71][i-1];
		SGr1->Cells[72][i] = SGr1->Cells[72][i-1];
		SGr1->Cells[73][i] = SGr1->Cells[73][i-1];

        //�f�[�^�C�������i�Ԃ̉����ԍ����X�V
        if ( KM02.DTKSHIN == SGr1->Cells[2][i] ) {
            SGr1->Cells[10][i] = StrToInt(SGr1->Cells[10][i])+1;
        }

    }


     //No���X�V
	 for ( i = ARow; i < SGr1->RowCount-1; i++ ) {
        sBuf = i + 1;
        SGr1->Cells[0][i] = AnsiString::StringOfChar(' ', 4-sBuf.Length()) + sBuf;
     }

     SGr1->Row = ARow ;
}

//---------------------------------------------------------------------------
// �e�R���g���[�����g�p�s�ɂ���
void __fastcall TForm1::InitEdt2(bool status)
{
    int i;
    bool Rstatus;
    bool Cstatus;
    TColor cBack;
    
    Rstatus = false;
    Cstatus = true;
    if ( status ) {
        //�g�p�\
        cBack = clWindow;
        //Rstatus = false;
    } else {
        //�g�p�s��
        cBack = 0x00D0D0D0;
        //Rstatus = true;
    }
	Edt01->ReadOnly = Rstatus;
    Edt01->Font->Color=clBlack;
	Edt03->ReadOnly = Rstatus;
	Edt04->ReadOnly = Rstatus;
	Edt05->ReadOnly = Rstatus;
	Edt06->ReadOnly = Rstatus;
	//ComBox09->ReadOnly = Rstatus;
	//ChkBoxA->ReadOnly = Rstatus;
	//ChkBoxB->ReadOnly = Rstatus;
	//ChkBoxF->ReadOnly = Rstatus;
	//ChkBoxE->ReadOnly = Rstatus;
	//ChkBoxD->ReadOnly = Rstatus;
	//ChkBoxG->ReadOnly = Rstatus;
	//ChkBoxH->ReadOnly = Rstatus;
	//ChkBoxI->ReadOnly = Rstatus;
	//ChkBoxJ->ReadOnly = Rstatus;
	//ChkBoxK->ReadOnly = Rstatus;
	//ChkBoxL->ReadOnly = Rstatus;
	//ComBoxE2->ReadOnly = Rstatus;
	//ComBoxH3->ReadOnly = Rstatus;
	//ComBox11->ReadOnly = Rstatus;
	Edt02->ReadOnly = Rstatus;
	//ChkBoxC->ReadOnly = Rstatus;
	//ChkBoxM->ReadOnly = Rstatus;
	Edt08->ReadOnly = Rstatus;
	Edt10->ReadOnly = Rstatus;
	Edt12->ReadOnly = Rstatus;
	Edt13->ReadOnly = Rstatus;
	ChkEdtA->ReadOnly = Rstatus;
	ChkEdtB->ReadOnly = Rstatus;
	ChkEdtC->ReadOnly = Rstatus;
	ChkEdtD->ReadOnly = Rstatus;
	ChkEdtE->ReadOnly = Rstatus;
	ChkEdtF->ReadOnly = Rstatus;
	ChkEdtG->ReadOnly = Rstatus;
	ChkEdtH->ReadOnly = Rstatus;
	ChkEdtI->ReadOnly = Rstatus;
	ChkEdtJ->ReadOnly = Rstatus;
	ChkEdtK->ReadOnly = Rstatus;
	ChkEdtL->ReadOnly = Rstatus;
	ChkEdtM->ReadOnly = Rstatus;
	EdtA1->ReadOnly = Rstatus;
	EdtA2->ReadOnly = Rstatus;
	EdtB1->ReadOnly = Rstatus;
	EdtB2->ReadOnly = Rstatus;
	EdtC1->ReadOnly = Rstatus;
	EdtC2->ReadOnly = Rstatus;
	EdtF1->ReadOnly = Rstatus;
	EdtF2->ReadOnly = Rstatus;
	EdtF3->ReadOnly = Rstatus;
	EdtE1->ReadOnly = Rstatus;
	EdtE3->ReadOnly = Rstatus;
	EdtD1->ReadOnly = Rstatus;
	EdtD2->ReadOnly = Rstatus;
	EdtG1->ReadOnly = Rstatus;
	EdtG2->ReadOnly = Rstatus;
	EdtG3->ReadOnly = Rstatus;
	EdtG4->ReadOnly = Rstatus;
	EdtH1->ReadOnly = Rstatus;
	EdtH2->ReadOnly = Rstatus;
	EdtH4->ReadOnly = Rstatus;
	EdtI1->ReadOnly = Rstatus;
	EdtI2->ReadOnly = Rstatus;
	EdtJ1->ReadOnly = Rstatus;
	EdtJ2->ReadOnly = Rstatus;
	EdtK1->ReadOnly = Rstatus;
	EdtK2->ReadOnly = Rstatus;
	EdtL1->ReadOnly = Rstatus;
	EdtL2->ReadOnly = Rstatus;
	EdtM1->ReadOnly = Rstatus;
	EdtM2->ReadOnly = Rstatus;
	Edt07->ReadOnly = Rstatus;
	EdtF4->ReadOnly = Rstatus;
	EdtMEMO->ReadOnly = Rstatus;

	ComBox09->Enabled = Cstatus;
	ChkBoxA->Enabled = Cstatus;
	ChkBoxB->Enabled = Cstatus;
	ChkBoxF->Enabled = Cstatus;
	ChkBoxE->Enabled = Cstatus;
	ChkBoxD->Enabled = Cstatus;
	ChkBoxG->Enabled = Cstatus;
	ChkBoxH->Enabled = Cstatus;
	ChkBoxI->Enabled = Cstatus;
	ChkBoxJ->Enabled = Cstatus;
	ChkBoxK->Enabled = Cstatus;
	ChkBoxL->Enabled = Cstatus;
	ComBoxE2->Enabled = Cstatus;
	ComBoxH3->Enabled = Cstatus;
	ComBox11->Enabled = Cstatus;
	ChkBoxC->Enabled = Cstatus;
	ChkBoxM->Enabled = Cstatus;

	Edt01->Color = cBack;
	Edt03->Color = cBack;
	Edt04->Color = cBack;
	Edt05->Color = cBack;
	Edt06->Color = cBack;
	ComBox09->Color = cBack;
	//ChkBoxA->Color = cBack;
	//ChkBoxB->Color = cBack;
	//ChkBoxF->Color = cBack;
	//ChkBoxE->Color = cBack;
	//ChkBoxD->Color = cBack;
	//ChkBoxG->Color = cBack;
	//ChkBoxH->Color = cBack;
	//ChkBoxI->Color = cBack;
	//ChkBoxJ->Color = cBack;
	//ChkBoxK->Color = cBack;
	//ChkBoxL->Color = cBack;
	ComBoxE2->Color = cBack;
	ComBoxH3->Color = cBack;
	ComBox11->Color = cBack;
	Edt02->Color = cBack;
	//ChkBoxC->Color = cBack;
	//ChkBoxM->Color = cBack;
	Edt08->Color = cBack;
	Edt10->Color = cBack;
	Edt12->Color = cBack;
	Edt13->Color = cBack;
	ChkEdtA->Color = cBack;
	ChkEdtB->Color = cBack;
	ChkEdtC->Color = cBack;
	ChkEdtD->Color = cBack;
	ChkEdtE->Color = cBack;
	ChkEdtF->Color = cBack;
	ChkEdtG->Color = cBack;
	ChkEdtH->Color = cBack;
	ChkEdtI->Color = cBack;
	ChkEdtJ->Color = cBack;
	ChkEdtK->Color = cBack;
	ChkEdtL->Color = cBack;
	ChkEdtM->Color = cBack;
	EdtA1->Color = cBack;
	EdtA2->Color = cBack;
	EdtB1->Color = cBack;
	EdtB2->Color = cBack;
	EdtC1->Color = cBack;
	EdtC2->Color = cBack;
	EdtF1->Color = cBack;
	EdtF2->Color = cBack;
	EdtF3->Color = cBack;
	EdtE1->Color = cBack;
	EdtE3->Color = cBack;
	EdtD1->Color = cBack;
	EdtD2->Color = cBack;
	EdtG1->Color = cBack;
	EdtG2->Color = cBack;
	EdtG3->Color = cBack;
	EdtG4->Color = cBack;
	EdtH1->Color = cBack;
	EdtH2->Color = cBack;
	EdtH4->Color = cBack;
	EdtI1->Color = cBack;
	EdtI2->Color = cBack;
	EdtJ1->Color = cBack;
	EdtJ2->Color = cBack;
	EdtK1->Color = cBack;
	EdtK2->Color = cBack;
	EdtL1->Color = cBack;
	EdtL2->Color = cBack;
	EdtM1->Color = cBack;
	EdtM2->Color = cBack;
	Edt07->Color = cBack;
	EdtF4->Color = cBack;
	EdtMEMO->Color = cBack;
	PnlADDYMD2->Color = cBack;
	PnlUPDCHR2->Color = cBack;
	PnlUPDYMD2->Color = cBack;
	PnlUPDCNT2->Color = cBack;
	PnlREVCNT2->Color = cBack;

    //2002/12/05 E.Takase
	ChkEdtN->ReadOnly = Rstatus;
	EdtN1->ReadOnly = Rstatus;
	EdtN2->ReadOnly = Rstatus;
	EdtN4->ReadOnly = Rstatus;
	ChkBoxN->Enabled = Cstatus;
	ComBoxN3->Enabled = Cstatus;
	ChkEdtN->Color = cBack;
	EdtN1->Color = cBack;
	EdtN2->Color = cBack;
	EdtN4->Color = cBack;
	ComBoxN3->Color = cBack;

}

//---------------------------------------------------------------------------
//�S���҃R�[�h����S���Җ����擾
AnsiString __fastcall TForm1::GetTANNAM(AnsiString strTANSYA)
{
     AnsiString sBuf;

     //���[�U�[������

     if ( Trim(strTANSYA) == "" ) return(" ");

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "SELECT TANNAM FROM SM12S WHERE  TANSYA = ";
     sBuf += strTANSYA;

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //�������� �O��
        return(" ");
     }

     return Query1->FieldValues["TANNAM"];


}
//---------------------------------------------------------------------------
