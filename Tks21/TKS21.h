//�f�[�^
struct KD_DATA {
       AnsiString KENSA_YMD;	// ������
       AnsiString DTKSHIN;      // ���Ӑ�i��
       AnsiString LOTNO;    	// ���b�gNo
       AnsiString ZISNAM;       // �ގ���
       double KIKAK_MIN;        // �����K�i
       double KIKAK_MAX;        // ����K�i
       int SOKUTE_SU;           // ���萔
       int SOKUTE_NM;           // ����w����
       double SOKUTEI_1;       	// ����l1
       double SOKUTEI_2;       	// ����l2
       double X_AVE;       		// X���ϒl
       double R;       			// R
       double TANI;       		// �P��

};

//�v�Z�f�[�^
struct CAL_DATA {
       AnsiString StartYMD;		// �J�n������
       AnsiString EndYMD;		// �I��������
       AnsiString StartLOTNO;	// �J�n���b�gNo
       AnsiString EndLOTNO;		// �I�����b�gNo
       double MIN;       		// �ŏ��l
       double MAX;       		// �ő�l
       double X_AVE_MIN;       	// X���ϒl �ŏ��l
       double X_AVE_MAX;       	// X���ϒl �ő�l
       double X_AVE_AVE;       	// X���ϒl ���ϒl
       double R_MIN;       		// R �ŏ��l
       double R_MAX;       		// R �ő�l
       double R_AVE;       		// R ���ϒl
       double X_AVE_ScaleMin;   // X���ϒl �ڐ���̍ŏ��l
       double X_AVE_ScaleMax;   // X���ϒl �ڐ���̍ő�l
       double X_AVE_Scale;      // X���ϒl �ڐ���̊Ԋu
       double R_ScaleMin;       // R �ڐ���̍ŏ��l
       double R_ScaleMax;       // R �ڐ���̍ő�l
       double R_Scale;       	// R �ڐ���̊Ԋu
	   double SGM;
	   double SGM_x;
	   double SGM_x2;
	   int SGM_n;
	   double k;
	   double Cp;
	   double Cpk;
	   double X_UCL;
	   double X_LCL;
	   double R_UCL;
};


extern int     USER_COD;               //�S���҃R�[�h
extern String  USER_NAM;               //�S���Җ�
extern String  BUMO_COD;               //�����R�[�h
extern String  BUMO_NAM;               //������
extern int     KENSAKU_Mode;           //�ꗗ�������[�h
                                       //�P�F�����\���
                                       //�Q�F���Ӑ溰��
                                       //�R�F���Ӑ�i��

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


extern KD_DATA KD;
extern CAL_DATA CALD;

extern int intKEIJKBN; //�`��敪 //2002/12/07 E.Takase
