//�H���\�̓f�[�^
struct KDB1_DATA {
    int             No;                     // �I��ԍ�
	AnsiString	KENSA_YMD;		//	�����N����
	AnsiString	DTKSHIN;		//	���Ӑ�i��
	AnsiString	HINBAN;			//	���Еi��
	AnsiString	ZISCOD;			//	�ގ��R�[�h
	AnsiString	ZISNAM;			//	�ގ���
	AnsiString	LOTNO;			//	���b�gNO
	int	     	SEQNO;			//	SEQ-NO
	AnsiString	TANI;			//	�P��
	int	     	KEIJKBN;		//	�`��敪
	int	     	KENSA_KMK;		//	��������
	AnsiString	KOUMOKU_J;		//	�������ږ��i���{��j
	AnsiString	KOUMOKU_E;		//	�������ږ��iEnglish�j
	int	     	HIST_SOKUT;		//	�H���\�� ���萔
	int	     	HIST_SOKUT_Ori;	//	�H���\�� ���萔
	int	     	HIST_KIKAK;		//	�H���\�� �K�i
	double		HIST_MIN;		//	�H���\�� �����K�i
	double		HIST_MAX;		//	�H���\�� ����K�i
	int	     	SOKUTE_SU;		//	���萔
	int	     	SOKUTE_SU_Ori;	//	���萔
	int         SOKUTE_KET;     //      �L�������F�Q�F2���A�R�F3��
	double		SOKUTE_AVE;		//	���ϒl
	double		SOKUTE_MIN;		//	�l�h�m
	double		SOKUTE_MAX;		//	�l�`�w
	double		SOKUTE_R;		//	�q
	double		SOKUTE_SGM;		//	�W���΍�
	double		SOKUTE_CP;		//	�b�o
	double		SOKUTE_CPK;		//	�b�o�j
	double		SOKUTE_K;		//	�j
	double		SOKUTE_P;		//	�s�Ǘ�
	double		JYOKEN1;		//	��������P
	double		JYOKEN2;		//	�@�V�@�@�Q
	AnsiString	JYOKEN3;		//	�@�V�@�@�R
	AnsiString	ADDYMD;			//	�o�^��
	AnsiString	ADDTIM;			//	�o�^����
	AnsiString	UPDYMD;			//	�ύX��
	AnsiString	UPDTIM;			//	�ύX����
	int	     	UPDCHR;			//	�X�V��
	int	     	UPDCNT;			//	�X�V��
};

//�q�X�g����������f�[�^
struct KDB2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // ����l
       double SOKUTEI_MEI1;	// ��t��R=�d���A���=�����A�ŗL��R=�����A�R�ܗ�=����
       double SOKUTEI_MEI2;	// ��t��R=�d���A���=���A�ŗL��R=���A�R�ܗ�=��
       double SOKUTEI_MEI3;	// ���=�����A�ŗL��R=mV L�A�R�ܗ�=����
       double SOKUTEI_MEI4;	// ���=�d�ʁA�ŗL��R=A L�A�R�ܗ�=�X�p���i�ύX�l�j
       double SOKUTEI_MEI5;	// �ŗL��R=mV R
       double SOKUTEI_MEI6;	// �ŗL��R=A R
       double SOKUTEI_MEI7;	// �ŗL��R=�v���[�u
};

//�������
struct KETA_DATA {
       int 			AVE;       // ���ϒl
       int 			MIN;       // �ŏ��l
       int 			MAX;       // �ő�l
       int 			R;         // R
       int 			SGM;       // �W���΍���
       int 			CP;        // CP
       int 			CPK;       // CPK
       int 			K;         // K
       int 			P;         // �s�Ǘ�
       AnsiString 	AVE_str;   // ���ϒl
       AnsiString 	MIN_str;   // �ŏ��l
       AnsiString 	MAX_str;   // �ő�l
       AnsiString 	R_str;     // R
       AnsiString 	SGM_str;   // �W���΍���
       AnsiString 	CP_str;    // CP
       AnsiString 	CPK_str;   // CPK
       AnsiString 	K_str;     // K
       AnsiString 	P_str;     // �s�Ǘ�
       AnsiString 	KMK_str;   // ��������
       double SOKUTE_AVE;      // ���ϒl
       double SOKUTE_MIN;      // �ŏ��l
       double SOKUTE_MAX;      // �ő�l
       double SOKUTE_R;        // R
       double SOKUTE_SGM;      // �W���΍���
       double SOKUTE_CP;       // CP
       double SOKUTE_CPK;      // CPK
       double SOKUTE_K;        // K
       double SOKUTE_P;        // �s�Ǘ�
};
extern KETA_DATA KETA;

struct structKM02 { 	//�����}�X�^�f�[�^ KM01_04
	AnsiString	DTKSCOD;		//	���Ӑ�R�[�h
	AnsiString	DTKSHIN;		//	���Ӑ�i��
	AnsiString	HINBAN;			//	���Еi��
	AnsiString	ZISCOD;			//	�ގ��R�[�h
	AnsiString	ZISNAM;			//	�ގ���
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
	AnsiString	LD_TR_TYPE;		//	�@�V�@�@��t����^�C�v
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
	double	MAGEG_MIN;			//	�Ȃ����x�i�����j�@����
	double	MAGEG_MAX;			//	�@�V�@�@�@        ���
	int	MAGEG_TAN;				//	�@�V�@�@�@�@      �P��
	double	MAGEG_SPAN;			//	�@�V�@�@�@�@      �X�p��
};
extern structKM02 KM02;



extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int RSInputFlag;
extern int     KENSAKU_Mode;           //�ꗗ�������[�h
                                       //�P�F�����\���
                                       //�Q�F���Ӑ�i��
                                       //�R�F���b�gNO

extern KDB1_DATA Tmp_KDB1;             // �I�������H���\��
extern KDB1_DATA Cur_Kdb1;             // �I�������q�X�g�O�����f�[�^
extern KDB2_DATA M_Kdb2[1000];         // �v���f�[�^�i�ő�l�F�P�O�O�O�j

extern double E_Screen_Data[3][20];

extern int E_Scale;

extern int KEIJKBN_KM02;                //KM02�̐��i�K�i�̌`��敪
extern int LD_HP_TAN_KM02;                //KM02�̐��i�K�i�̌`��敪
extern int MAGE_TAN_KM02;                //KM02�̐��i�K�i�̌`��敪


extern AnsiString MSG_00;
extern AnsiString MSG_01;
extern AnsiString MSG_02;
extern AnsiString MSG_03;
extern AnsiString MSG_04;
extern AnsiString MSG_05;
extern AnsiString MSG_06;
extern AnsiString MSG_07;
extern AnsiString MSG_08;
extern AnsiString MSG_09;
extern AnsiString MSG_10;
extern AnsiString MSG_11;
extern AnsiString MSG_12;
extern AnsiString MSG_13;

extern AnsiString Select_Str1;
extern AnsiString Select_Str2;
extern AnsiString Select_Str3;
extern AnsiString Select_Str4;
extern AnsiString Select_Str5;
extern int Select_Cnt;
extern AnsiString sBuf;
extern AnsiString sMsg2;

extern int iKojoKbn ;            //�H��敪 2016/06/30 �ǉ�

