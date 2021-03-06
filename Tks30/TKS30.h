// qXgOªèvO
//qXgOf[^
struct KDA1_DATA {
       int No;                  // IðÔ
       AnsiString KENSA_YMD;	// ¸\èNú
       int SEQNO;		// SEQ-NO
       AnsiString DTKSCOD;	// ¾ÓæR[h
       AnsiString DTKSHIN;      // ¾ÓæiÔ
       AnsiString LOTNO;	// bgNo
       AnsiString HINBAN;	// ©ÐiÔ
       AnsiString ZISCOD;       // Þ¿R[h
       AnsiString ZISNAM;       // Þ¿¼
       int HIST_SOKUT_Ori;      // qXgOªè(Origal)
       int HIST_SOKUT;          // qXgOªè
       int HIST_KIKAK;          // qXgOKiiPCQCRj
       double HIST_MIN;         // qXgOºÀKi
       double HIST_MAX;         // qXgOãÀKi
       int SOKUTE_SU;           // ªè
       int SOKUTE_SU_Ori;
       int SOKUTE_KET;          // LøFQF2ARF3
       double SOKUTE_AVE;       // ½Ïl
       double SOKUTE_MIN;       // Å¬l
       double SOKUTE_MAX;       // Åål
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // WÎ·Ð
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // sÇ¦
       AnsiString ADDYMD;       // o^ú
       AnsiString ADDTIM;       // o^Ô
       AnsiString UPDYMD;       // ÏXú
       AnsiString UPDTIM;       // ÏXÔ
       int UPDCHR;              // XVÒ
       int UPDCNT;              // XVñ
       AnsiString MEMO ;        //õl 2002/11/07 ÇÁ E.Takase
};

//qXgªªèf[^
struct KDA2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // ªèl
};

//óü
struct KETA_DATA {
       int 			AVE;       // ½Ïl
       int 			MIN;       // Å¬l
       int 			MAX;       // Åål
       int 			R;         // R
       int 			SGM;       // WÎ·Ð
       int 			CP;        // CP
       int 			CPK;       // CPK
       int 			K;         // K
       int 			P;         // sÇ¦
       AnsiString 	AVE_str;   // ½Ïl
       AnsiString 	MIN_str;   // Å¬l
       AnsiString 	MAX_str;   // Åål
       AnsiString 	R_str;     // R
       AnsiString 	SGM_str;   // WÎ·Ð
       AnsiString 	CP_str;    // CP
       AnsiString 	CPK_str;   // CPK
       AnsiString 	K_str;     // K
       AnsiString 	P_str;     // sÇ¦
       double SOKUTE_AVE;       // ½Ïl
       double SOKUTE_MIN;       // Å¬l
       double SOKUTE_MAX;       // Åål
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // WÎ·Ð
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // sÇ¦
};
extern KETA_DATA KETA;


extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int	   RSInputFlag;
extern int     KENSAKU_Mode;           //êõ[h
                                       //PF¸\èú
                                       //QF¾Óæº°ÄÞ
                                       //RF¾ÓæiÔ

extern KDA1_DATA Cur_Kda1;             // Iðµ½qXgOf[^

extern KDA2_DATA M_Kda2[1000];         // vªf[^iÅålFPOOOÂj

extern double E_Screen_Data[3][20];

extern int E_Scale;

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

extern int iKojoKbn ;            //Hêæª 2016/06/30 ÇÁ

