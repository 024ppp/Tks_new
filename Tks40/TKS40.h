//Hö\Íf[^
struct KDB1_DATA {
    int             No;                     // IðÔ
	AnsiString	KENSA_YMD;		//	¸Nú
	AnsiString	DTKSHIN;		//	¾ÓæiÔ
	AnsiString	HINBAN;			//	©ÐiÔ
	AnsiString	ZISCOD;			//	Þ¿R[h
	AnsiString	ZISNAM;			//	Þ¿¼
	AnsiString	LOTNO;			//	bgNO
	int	     	SEQNO;			//	SEQ-NO
	AnsiString	TANI;			//	PÊ
	int	     	KEIJKBN;		//	`óæª
	int	     	KENSA_KMK;		//	¸Ú
	AnsiString	KOUMOKU_J;		//	¸Ú¼iú{êj
	AnsiString	KOUMOKU_E;		//	¸Ú¼iEnglishj
	int	     	HIST_SOKUT;		//	Hö\Í ªè
	int	     	HIST_SOKUT_Ori;	//	Hö\Í ªè
	int	     	HIST_KIKAK;		//	Hö\Í Ki
	double		HIST_MIN;		//	Hö\Í ºÀKi
	double		HIST_MAX;		//	Hö\Í ãÀKi
	int	     	SOKUTE_SU;		//	ªè
	int	     	SOKUTE_SU_Ori;	//	ªè
	int         SOKUTE_KET;     //      LøFQF2ARF3
	double		SOKUTE_AVE;		//	½Ïl
	double		SOKUTE_MIN;		//	lhm
	double		SOKUTE_MAX;		//	l`w
	double		SOKUTE_R;		//	q
	double		SOKUTE_SGM;		//	WÎ·
	double		SOKUTE_CP;		//	bo
	double		SOKUTE_CPK;		//	boj
	double		SOKUTE_K;		//	j
	double		SOKUTE_P;		//	sÇ¦
	double		JYOKEN1;		//	ªèðP
	double		JYOKEN2;		//	@V@@Q
	AnsiString	JYOKEN3;		//	@V@@R
	AnsiString	ADDYMD;			//	o^ú
	AnsiString	ADDTIM;			//	o^Ô
	AnsiString	UPDYMD;			//	ÏXú
	AnsiString	UPDTIM;			//	ÏXÔ
	int	     	UPDCHR;			//	XVÒ
	int	     	UPDCNT;			//	XVñ
};

//qXgªªèf[^
struct KDB2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // ªèl
       double SOKUTEI_MEI1;	// ætïR=d³AêÌ=ú³AÅLïR=ú³ARÜÍ=ú³
       double SOKUTEI_MEI2;	// ætïR=d¬AêÌ=AÅLïR=ARÜÍ=
       double SOKUTEI_MEI3;	// êÌ=·³AÅLïR=mV LARÜÍ=×
       double SOKUTEI_MEI4;	// êÌ=dÊAÅLïR=A LARÜÍ=XpiÏXlj
       double SOKUTEI_MEI5;	// ÅLïR=mV R
       double SOKUTEI_MEI6;	// ÅLïR=A R
       double SOKUTEI_MEI7;	// ÅLïR=v[u
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
       AnsiString 	KMK_str;   // ¸Ú
       double SOKUTE_AVE;      // ½Ïl
       double SOKUTE_MIN;      // Å¬l
       double SOKUTE_MAX;      // Åål
       double SOKUTE_R;        // R
       double SOKUTE_SGM;      // WÎ·Ð
       double SOKUTE_CP;       // CP
       double SOKUTE_CPK;      // CPK
       double SOKUTE_K;        // K
       double SOKUTE_P;        // sÇ¦
};
extern KETA_DATA KETA;

struct structKM02 { 	//¸}X^f[^ KM01_04
	AnsiString	DTKSCOD;		//	¾ÓæR[h
	AnsiString	DTKSHIN;		//	¾ÓæiÔ
	AnsiString	HINBAN;			//	©ÐiÔ
	AnsiString	ZISCOD;			//	Þ¿R[h
	AnsiString	ZISNAM;			//	Þ¿¼
	AnsiString	SYOSCOD;		//	Ä¬R[h
	int	SORTKEY;	      		//	\[gL[
	int	KEIJKBN;				//	`óæª
	int	SK_LD_LNG;				//	ªèæª@ü·³
	int	SK_BURASI;				//	@V@@@uV
	int	SK_BURASIT;				//	@V@@@uVcµ
	int	SK_LD_TR;				//	@V@@@üætïR
	int	SK_LD_HP;				//	@V@@@üø£­x
	int	SK_BOTAI;				//	@V@@@êÌäd
	int	SK_KOYU;				//	@V@@@ÅLïR
	int	SK_MAGE;				//	@V@@@RÜÍ
	int	SK_HSC_A;				//	@V@@@HsCdxi³Êj
	int	SK_HSC_S;				//	@V@@@HsCdxi¤Êj
	int	SK_HSD_A;				//	@V@@@HsDdxi³Êj
	int	SK_HSD_S;				//	@V@@@HsDdxi¤Êj
	int	SK_ZAKUT;				//	@V@@@Àü
	int	HIST_SOKUT;				//	qXgOªè
	int	HIST_KIKAK;				//	@V@@@@@Ki
	double	HIST_MIN;			//	@V@@@@@ºÀKi
	double	HIST_MAX;			//	@V@@@@@ãÀKi
	double	LD_LNG_MIN;			//	[hü·³@ãÀ
	double	LD_LNG_MAX;			//	@V@@@@@ºÀ
	double	BURASI_MIN;			//	uV@ãÀ
	double	BURASI_MAX;			//	@V@@@ºÀ
	double	BURASIT_MIN;		//	uVcµãÀ
	double	BURASIT_MAX;		//	@V@@@@@ºÀ
	double	LD_TR_DENA;			//	[hüætªèd³
	double	LD_TR_DENR;			//	[hüætªèd¬
	int	LD_TR_TIME;				//	@V@@ætªèÔ
	AnsiString	LD_TR_TYPE;		//	@V@@ætªè^Cv
	int	LD_HP_SPD;				//	[hüø£ªè¬x
	double	LD_HP_KYO;			//	@V@@ø£­x
	int	LD_HP_TAN;				//	@V@@ø£­xPÊ
	double	BOTAI_MIN;			//	êÌäd@ºÀ
	double	BOTAI_MAX;			//	@V@@@ãÀ
	int	KOYU_MIN;				//	ÅLïR¦@ºÀ
	int	KOYU_MAX;				//	@V@@@@ãÀ
	double	KOYU_DEN;			//	@V@@@@d¬
	int	KOYU_PRO;				//	@V@@@@v[u
	double	MAGE_MIN;			//	È°­x@ºÀ
	double	MAGE_MAX;			//	@V@@@ãÀ
	int	MAGE_TAN;				//	@V@@@PÊ
	double	MAGE_SPAN;			//	@V@@@Xp
	int	HSC_A_MIN;				//	gbdxi³ÊjºÀ
	int	HSC_A_MAX;				//	@V@@@@@@@ãÀ
	int	HSC_S_MIN;				//	@V@@@i¤ÊjºÀ
	int	HSC_S_MAX;				//	@V@@@@@@@ãÀ
	double	HSD_A_MIN;			//	gcdxi³ÊjºÀ
	double	HSD_A_MAX;			//	@V@@@@@@@ãÀ
	double	HSD_S_MIN;			//	@V@@@i¤ÊjºÀ
	double	HSD_S_MAX;			//	@V@@@@@@@ãÀ
	int	ZAKUT_MIN;				//	Àü@ºÀ
	int	ZAKUT_MAX;				//	@V@ãÀ
	double	MAGEG_MIN;			//	È°­xi»¨j@ºÀ
	double	MAGEG_MAX;			//	@V@@@        ãÀ
	int	MAGEG_TAN;				//	@V@@@@      PÊ
	double	MAGEG_SPAN;			//	@V@@@@      Xp
};
extern structKM02 KM02;



extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int RSInputFlag;
extern int     KENSAKU_Mode;           //êõ[h
                                       //PF¸\èú
                                       //QF¾ÓæiÔ
                                       //RFbgNO

extern KDB1_DATA Tmp_KDB1;             // Iðµ½Hö\Í
extern KDB1_DATA Cur_Kdb1;             // Iðµ½qXgOf[^
extern KDB2_DATA M_Kdb2[1000];         // vªf[^iÅålFPOOOÂj

extern double E_Screen_Data[3][20];

extern int E_Scale;

extern int KEIJKBN_KM02;                //KM02Ì»iKiÌ`óæª
extern int LD_HP_TAN_KM02;                //KM02Ì»iKiÌ`óæª
extern int MAGE_TAN_KM02;                //KM02Ì»iKiÌ`óæª


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

