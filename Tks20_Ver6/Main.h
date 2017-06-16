#ifndef MainMenuH
#define MainMenuH

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Chart.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Db.hpp>
#include <DBTables.hpp>


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dir.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <winbase.h>
#include <shellapi.h>
#include <Printers.hpp>
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <wingdi.h>


#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "U_MakeData.h"
#include "U_Func.h"
#include "U_KM0104.h"
#include "U_KD01.h"
#include "U_KD11.h"
#include "U_KD21.h"
#include "U_KD31.h"
#include "U_KD41.h"
#include "U_KD51.h"
#include "U_KD61.h"
#include "U_KD71.h"
#include "U_KD81.h"
#include "U_KD91.h"
#include "U_UPDCHR.h"

#include "U_KDC1.h"
#include "U_KD71_L.h"
#include "U_KD71_R.h"

#define STRMAX 500
#define DTKSCODMAX 100

//---------------------------------------------------------------------------
//�ϐ��̐錾
//�\����
extern struct structUPDCHR {  //������
    AnsiString DTKSCOD;
    AnsiString KD01;
    AnsiString KD11;
    AnsiString KD21;
    AnsiString KD31;
    AnsiString KD41;
    AnsiString KD51;
    AnsiString KD61_1;
    AnsiString KD61_2;
    AnsiString KD61_3;
    AnsiString KD61_4;
    AnsiString KD71;
    AnsiString KD81;
    AnsiString KD91;
}DTKSData;
extern int UPDCHRNo;


extern struct structKD01 {  //���[�h������ KD01
    int PASS;               //���[�h������ �������i �s���i
    int LD_LNG_NM;          //���[�h������ �����f�[�^��
    double LD_LNG_MIN;      //���[�h������ �K�i��
    double LD_LNG_MAX;      //���[�h������ �K�i��
    double LD_LNG_VAL[100]; //���[�h������ �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD01Data;

extern struct structKD11 {  //�u���V�����@  KD11
    int PASS;               //�u���V�����@  �������i �s���i
    int BURASI_NM;          //�u���V�����@ �����f�[�^��
    double BURASI_MIN;      //�u���V�����@ �K�i��
    double BURASI_MAX;      //�u���V�����@ �K�i��
    double BURASI_VAL[100]; //�u���V�����@ �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD11Data;

extern struct structKD21 {  //�u���V�����@�c����  KD21
    int PASS;               //�u���V�����@�c����  �������i �s���i
    int BURASIT_NM;         //�u���V�����@�c���� �����f�[�^��
    double BURASIT_MIN;     //�u���V�����@�c���� �K�i��
    double BURASIT_MAX;     //�u���V�����@�c���� �K�i��
    double BURASIT_VAL[100];//�u���V�����@�c���� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD21Data;

extern struct structKD31 {  //���[�h����t��R  KD31
    int PASS;               //���[�h����t��R  �������i �s���i
    int LD_TR_NM;         	//���[�h����t��R �����f�[�^��
    double LD_TR_DEN;      	//���[�h����t��R ����d��
    double LD_TR_TIME;     	//���[�h����t��R ���莞��
    double LD_TR_TEKO;     	//���[�h����t��R ����d��
    double LD_TRV_VAL[100];	//���[�h����t��R ����d�� �����f�[�^
    double LD_TRA_VAL[100];	//���[�h����t��R ����d�� �����f�[�^
    double LD_TRR_VAL[100];	//���[�h����t��R �����R �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD31Data;

extern struct structKD41 {  //���[�h���������x  KD41
    int PASS;               //���[�h���������x  �������i �s���i
    double LD_HP_NM;          	//���[�h���������x �����f�[�^��
    double LD_HP_MIN;      	//���[�h���������x �K�i��
    double LD_HP_VAL[100];		//���[�h���������x �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD41Data;

extern struct structKD51 { 	//��̔�d KD51
    int PASS;             	//��̔�d �������i �s���i
    int BOTAI_NM;         	//��̔�d �����f�[�^��
    double BOTAI_MIN;   	//��̔�d �K�i��
    double BOTAI_MAX;     	//��̔�d �K�i��
    double BOTAI_VAL[100];	//��̔�d �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD51Data;

extern struct structKD61 {  //�g���d�x  KD61
    int PASS;               //�g���d�x  �������i �s���i
	int	HSC_A_MIN;			//�g���b�d�x���� �K�i��
	int	HSC_A_MAX;			//  �V�@�@�@�@ �@�K�i��
	int	HSC_S_MIN;			//  �V�@�@�@���� �K�i��
	int	HSC_S_MAX;			//  �V�@�@�@�@�@ �K�i��
	int	HSC_A_VAL[100];		//�g���b�d�x���� �����f�[�^
	int	HSC_S_VAL[100];		//  �V�@�@�@���� �����f�[�^
	int	HSC_A_SK_NM;		//�g���b�����
	int	HSC_S_SK_NM;		//�g���b�����
	double	HSD_A_MIN;		//�g���c�d�x���� �K�i��
	double	HSD_A_MAX;		//�@�V�@�@�@�@�@ �K�i��
	double	HSD_S_MIN;		//�@�V�@�@�@���� �K�i��
	double	HSD_S_MAX;		//�@�V�@�@�@�@�@ �K�i��
	double	HSD_A_VAL[100];	//�g���c�d�x���� �����f�[�^
	double	HSD_S_VAL[100];	//�@�V�@�@�@���� �����f�[�^
	int	HSD_A_SK_NM;		//�g���c�����
	int	HSD_S_SK_NM;		//�g���c�����
    int UPDCHR;             //�X�V��
	int HSC_SK_SU;			//�g���b���萔
	int HSD_SK_SU;			//�g���c���萔
}KD61Data;

extern struct structKD71 {  //�ŗL��R��  KD71
    int PASS;               //�ŗL��R��  �������i �s���i
    int KOYU_NM;       		//�ŗL��R�� �����f�[�^��
    int KOYU_MIN;   	   	//�ŗL��R�� �K�i��
    int KOYU_MAX;   	   	//�ŗL��R�� �K�i��
    int KOYU_VAL[100];  	//�ŗL��R�� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD71Data;

extern struct structKD81 {  //�R�ܗ�  KD81
    int PASS;               //�R�ܗ�  �������i �s���i
    int MAGE_NM;       	    //�R�ܗ� �����f�[�^��
    double MAGE_MIN; 	   	//�R�ܗ� �K�i��
    double MAGE_MAX;  	  	//�R�ܗ� �K�i��
    double MAGE_VAL[100]; 	//�R�ܗ� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD81Data;

extern struct structKD91 {  //����  KD91
    int PASS;               //����  �������i �s���i
    int ZAKUT_NM;       	//���� �����f�[�^��
    int ZAKUT_MIN; 	   	    //���� �K�i��
    int ZAKUT_MAX;  	  	//���� �K�i��
    int ZAKUT_VAL[100]; 	//���� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD91Data;

//2002/12/05 E.Takase
extern struct structKDC1 {  //�����R�ܗ� KDC1
    int PASS;               //�����R�ܗ� �������i �s���i
    int MAGEG_NM;       	//�����R�ܗ� �����f�[�^��
    double MAGEG_MIN; 	   	//�����R�ܗ� �K�i��
    double MAGEG_MAX;  	  	//�����R�ܗ� �K�i��
    double MAGEG_VAL[100]; 	//�����R�ܗ� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KDC1Data;

extern struct structKD71_L {  //�ŗL��R��  KD71
    int PASS;               //�ŗL��R��  �������i �s���i
    int KOYU_NM;       		//�ŗL��R�� �����f�[�^��
    int KOYU_MIN;   	   	//�ŗL��R�� �K�i��
    int KOYU_MAX;   	   	//�ŗL��R�� �K�i��
    double KOYU_VAL[100];  	//�ŗL��R�� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD71Data_L;

extern struct structKD71_R {  //�ŗL��R��  KD71
    int PASS;               //�ŗL��R��  �������i �s���i
    int KOYU_NM;       		//�ŗL��R�� �����f�[�^��
    int KOYU_MIN;   	   	//�ŗL��R�� �K�i��
    int KOYU_MAX;   	   	//�ŗL��R�� �K�i��
    double KOYU_VAL[100];  	//�ŗL��R�� �����f�[�^
    int UPDCHR;             //�X�V��
	int SOKUTEI_SU;			//���萔
}KD71Data_R;



extern struct structKM01_04 { 	//�����}�X�^�f�[�^ KM01_04
	AnsiString	KENSA_YMD; 		//	�����\��N����
	int	TOLEY_NO;	            	//	�g���[No
	int	SAMPLE_P;       		//	�T���v���|�W�V����
	int	KOKBNG;	            	//	�H��No
	AnsiString	DTKSCOD;		//	���Ӑ�R�[�h
	AnsiString	DTKSHIN;		//	���Ӑ�i��
	AnsiString	LOTNO;			//	���b�gNo
	AnsiString	HINBAN;			//	���Еi��
	AnsiString	ZISCOD;			//	�ގ��R�[�h
	AnsiString	ZISNAM;			//	�ގ���
	int	NUM;            		//	�Đ��R�[�h
	AnsiString	SYOSCOD;		//	�Đ��R�[�h
	int	SORTKEY;	      		//	�\�[�g�L�[
	int	KEIJKBN;				//	�`��敪
	int	SK_LD_LNG;				//	����敪�@������
	int	SK_BURASI;				//	�@�V�@�@�@�u���V��
	int	SK_BURASIT;				//	�@�V�@�@�@�u���V���c����
	int	SK_LD_TR;				//	�@�V�@�@�@����t��R
	int	SK_LD_HP;				//	�@�V�@�@�@���������x
	int	SK_BOTAI;				//	�@�V�@�@�@��̔�d
	int	SK_KOYU;				//	�@�V�@�@�@�ŗL��R
	int	SK_MAGE;				//	�@�V�@�@�@�R�ܗ�
	int	SK_HSC_A;				//	�@�V�@�@�@HsC�d�x�i���ʁj
	int	SK_HSC_S;				//	�@�V�@�@�@HsC�d�x�i���ʁj
	int	SK_HSD_A;				//	�@�V�@�@�@HsD�d�x�i���ʁj
	int	SK_HSD_S;				//	�@�V�@�@�@HsD�d�x�i���ʁj
	int	SK_ZAKUT;				//	�@�V�@�@�@����
	int	HIST_SOKUT;				//	�q�X�g�O�������萔
	int	HIST_KIKAK;				//	�@�V�@�@�@�@�@�K�i
	double	HIST_MIN;			//	�@�V�@�@�@�@�@�����K�i
	double	HIST_MAX;			//	�@�V�@�@�@�@�@����K�i
	double	LD_LNG_MIN;			//	���[�h�������@���
	double	LD_LNG_MAX;			//	�@�V�@�@�@�@�@����
	double	BURASI_MIN;			//	�u���V���@���
	double	BURASI_MAX;			//	�@�V�@�@�@����
	double	BURASIT_MIN;		//	�u���V���c�������
	double	BURASIT_MAX;		//	�@�V�@�@�@�@�@����
	double	LD_TR_DENA;			//	���[�h����t����d��
	double	LD_TR_DENR;			//	���[�h����t����d��
	int	LD_TR_TIME;				//	�@�V�@�@��t���莞��
	int	LD_TR_TEKO;				//	�@�V�@�@��t��R
	int	LD_HP_SPD;				//	���[�h���������葬�x
	double	LD_HP_KYO;			//	�@�V�@�@�������x
	int	LD_HP_TAN;				//	�@�V�@�@�������x�P��
	double	BOTAI_MIN;			//	��̔�d�@����
	double	BOTAI_MAX;			//	�@�V�@�@�@���
	int	KOYU_MIN;				//	�ŗL��R���@����
	int	KOYU_MAX;				//	�@�V�@�@�@�@���
	double	KOYU_DEN;			//	�@�V�@�@�@�@�d��
	int	KOYU_PRO;				//	�@�V�@�@�@�@�v���[�u
	double	MAGE_MIN;			//	�Ȃ����x�@����
	double	MAGE_MAX;			//	�@�V�@�@�@���
	int	MAGE_TAN;				//	�@�V�@�@�@�P��
	double	MAGE_SPAN;			//	�@�V�@�@�@�X�p��
	int	HSC_A_MIN;				//	�g���b�d�x�i���ʁj����
	int	HSC_A_MAX;				//	�@�V�@�@�@�@�@�@�@���
	int	HSC_S_MIN;				//	�@�V�@�@�@�i���ʁj����
	int	HSC_S_MAX;				//	�@�V�@�@�@�@�@�@�@���
	double	HSD_A_MIN;			//	�g���c�d�x�i���ʁj����
	double	HSD_A_MAX;			//	�@�V�@�@�@�@�@�@�@���
	double	HSD_S_MIN;			//	�@�V�@�@�@�i���ʁj����
	double	HSD_S_MAX;			//	�@�V�@�@�@�@�@�@�@���
	int	ZAKUT_MIN;				//	�����@����
	int	ZAKUT_MAX;				//	�@�V�@���
	AnsiString	ADDYMD;			//	�o�^��
	AnsiString	ADDTIM;			//	�o�^����
	AnsiString	UPDYMD;			//	�ύX��
	AnsiString	UPDTIM;			//	�ύX����
	int	UPDCHR;					//	�X�V��
	int	UPDCNT;					//	�X�V��
	AnsiString	RO_NO;			//	�FNo
	int	MAX_ONDO;				//	MAX���x
	int	CYCLE_TIME;				//	�T�C�N���^�C��
	int	SK_MAGEG;				//	����敪�@�����Ȃ����x
	double	MAGEG_MIN;			//	�Ȃ����x�@����
	double	MAGEG_MAX;			//	�@�V�@�@�@���
	int	MAGEG_TAN;				//	�@�V�@�@�@�P��
	double	MAGEG_SPAN;			//	�@�V�@�@�@�X�p��
        int	KOJOKBN;				//	�@�H��敪
        //20161024 Y.Onishi �H��敪�ǉ�
}KM01_04Data;

extern int KENSAKU_Mode;        //�ꗗ�������[�h
                                //0 ������
                                //1 ���Ӑ�i��
                                //2 �J�n���b�gNo
                                //3 �I�����b�gNo

extern int DataNo;    //�ő匟���f�[�^��
extern int Master_rec;//�}�X�^������s
extern int rec;       //���R�[�h��
extern int pass;      //���i1�A�s���i0
extern int newpage;   //���y�[�WNo
extern AnsiString strcnd;       //������
extern AnsiString strcnd2;       //������
extern AnsiString DTKSHINcnd;   //���Ӑ�i��
extern AnsiString StartLOTcnd;  //�J�n���b�gNo
extern AnsiString EndLOTcnd;    //�I�����b�gNo
extern AnsiString DTKSCODcnd;   //���Ӑ�R�[�h
extern int Flagcnd;             //0����������  1�����Ӑ�i�ԕ�

extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;


extern AnsiString Last_DTKSCOD;
extern AnsiString UPDCHRstr;
extern AnsiString UPDCHRstr02;
extern AnsiString KIKAKUMINstr;
extern AnsiString KIKAKUMAXstr;

//---------------------------------------------------------------------------
//�֐��̐錾
extern void UPDCHRInsert01(void);
extern void UPDCHR_Serch01(void);  //2002/12/06 E.Takase �R���~�p
extern void UPDCHR_Serch01(void);
extern void MakeData(void);
extern AnsiString varstr(Variant str);
extern int varint(Variant str);
//extern AnsiString varstr(AnsiString str);
//extern int varint(AnsiString str);

extern double vardouble(Variant str);
extern void KM01_04Serch01(void);
extern void DTKSHIN_CIYCLEInsert01(void);
extern void KIKAKU_MINInsert01(void);
extern void KIKAKU_MINInsert02(void);  //2002/12/06 E.Takase �R���~�p
extern void KIKAKU_MAXInsert01(void);
extern void PASS_FailUpdate01(void);
extern void KM01_04Sub01(void);
extern void SOKUTEIInsert01(void);
extern void SOKUTEIInsert02(void);     //2002/12/06 E.Takase �R���~�p
extern void LOT_SOKUTEIInsert01(void);
extern void KD01_02Serch01(void);
extern void KD01Compare01(void);
extern void KD01Format01(void);

extern void KD11_12Serch01(void);
extern void KD11Compare01(void);
extern void KD11Format01(void);

extern void KD21_22Serch01(void);
extern void KD21Compare01(void);
extern void KD21Format01(void);

extern void KD31_32Serch01(void);
extern void KD31Compare01(void);
extern void KD31Format01(void);

extern void KD41_42Serch01(void);
extern void KD41Compare01(void);
extern void KD41Format01(void);

extern void KD51_52Serch01(void);
extern void KD51Compare01(void);
extern void KD51Format01(void);

extern void KD61_62Serch01(void);
extern void KD61Compare01(void);
extern void KD61Format01(void);

extern void KD71_72Serch01(void);
extern void KD71Compare01(void);
extern void KD71Format01(void);

extern void KD81_82Serch01(void);
extern void KD81Compare01(void);
extern void KD81Format01(void);

extern void KD91_92Serch01(void);
extern void KD91Compare01(void);
extern void KD91Format01(void);

//2002/12/05 E.Takase
extern void KDC1_C2Serch01(void);
extern void KDC1Compare01(void);
extern void KDC1Format01(void);

extern void KD71_72_LSerch01(void);
extern void KD71_LCompare01(void);
extern void KD71_LFormat01(void);

extern void KD71_72_RSerch01(void);
extern void KD71_RCompare01(void);
extern void KD71_RFormat01(void);

extern double DivAB(double a, double b);
extern AnsiString SOKUTEIstrI(int i, int n, int val);
extern AnsiString SOKUTEIstrF(int i, int n, double val, int k);
extern void PassSet(void);
extern void DataNoSet(void);

extern AnsiString Kara(int i);

//���Ӑ�ʂɌ�����������
extern void UPDCHR_Make01(int CurNo);
extern void UPDCHR_2_Make01(int CurNo);  //2002/12/06 E.Takase �R���~�p
//�u������=�E�E�E�E�v������쐬
extern void UPDCHR_Make02(void);
extern void UPDCHR_2_Make02(void);       //2002/12/06 E.Takase �R���~�p
//TW_UPDCHR �� �ǉ�
extern void UPDCHRInsert02(void);

extern int iKojoKbn ;            //�H��敪 2016/06/24 �ǉ�

#endif



