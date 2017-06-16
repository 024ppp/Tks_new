//�q�X�g�O��������v���O����
//�q�X�g�O�����f�[�^
struct KDA1_DATA {
       int No;                  // �I��ԍ�
       AnsiString KENSA_YMD;	// �����\��N����
       int SEQNO;       		// SEQ-NO
       AnsiString DTKSCOD;  	// ���Ӑ�R�[�h
       AnsiString DTKSHIN;      // ���Ӑ�i��
       AnsiString LOTNO;    	// ���b�gNo
       AnsiString HINBAN;   	// ���Еi��
       AnsiString ZISCOD;       // �ގ��R�[�h
       AnsiString ZISNAM;       // �ގ���
       int HIST_SOKUT_Ori;      // �q�X�g�O�������萔(Origal)
       int HIST_SOKUT;          // �q�X�g�O�������萔
       int HIST_KIKAK;          // �q�X�g�O�����K�i�i�P�C�Q�C�R�j
       double HIST_MIN;         // �q�X�g�O���������K�i
       double HIST_MAX;         // �q�X�g�O��������K�i
       int SOKUTE_SU;           // ���萔
       int SOKUTE_SU_Ori;
       double SOKUTE_AVE;       // ���ϒl
       double SOKUTE_MIN;       // �ŏ��l
       double SOKUTE_MAX;       // �ő�l
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // �W���΍���
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // �s�Ǘ�
       AnsiString ADDYMD;       // �o�^��
       AnsiString ADDTIM;       // �o�^����
       AnsiString UPDYMD;       // �ύX��
       AnsiString UPDTIM;       // �ύX����
       int UPDCHR;              // �X�V��
       int UPDCNT;              // �X�V��
};

//�q�X�g�O��������f�[�^
struct KDA2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // ����l
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
       double SOKUTE_AVE;       // ���ϒl
       double SOKUTE_MIN;       // �ŏ��l
       double SOKUTE_MAX;       // �ő�l
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // �W���΍���
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // �s�Ǘ�
};
extern KETA_DATA KETA;

extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int     KENSAKU_Mode;           //�ꗗ�������[�h
                                       //�P�F�����\���
                                       //�Q�F���Ӑ溰��
                                       //�R�F���Ӑ�i��

extern KDA1_DATA Cur_Kda1;             // �I�������q�X�g�O�����f�[�^

extern KDA2_DATA M_Kda2[1000];         // �v���f�[�^�i�ő�l�F�P�O�O�O�j


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

