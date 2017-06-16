//工程能力データ
struct KDB1_DATA {
    int             No;                     // 選択番号
	AnsiString	KENSA_YMD;		//	検査年月日
	AnsiString	DTKSHIN;		//	得意先品番
	AnsiString	HINBAN;			//	自社品番
	AnsiString	ZISCOD;			//	材質コード
	AnsiString	ZISNAM;			//	材質名
	AnsiString	LOTNO;			//	ロットNO
	int	     	SEQNO;			//	SEQ-NO
	AnsiString	TANI;			//	単位
	int	     	KEIJKBN;		//	形状区分
	int	     	KENSA_KMK;		//	検査項目
	AnsiString	KOUMOKU_J;		//	検査項目名（日本語）
	AnsiString	KOUMOKU_E;		//	検査項目名（English）
	int	     	HIST_SOKUT;		//	工程能力 測定数
	int	     	HIST_SOKUT_Ori;	//	工程能力 測定数
	int	     	HIST_KIKAK;		//	工程能力 規格
	double		HIST_MIN;		//	工程能力 下限規格
	double		HIST_MAX;		//	工程能力 上限規格
	int	     	SOKUTE_SU;		//	測定数
	int	     	SOKUTE_SU_Ori;	//	測定数
	int         SOKUTE_KET;     //      有効桁数：２：2桁、３：3桁
	double		SOKUTE_AVE;		//	平均値
	double		SOKUTE_MIN;		//	ＭＩＮ
	double		SOKUTE_MAX;		//	ＭＡＸ
	double		SOKUTE_R;		//	Ｒ
	double		SOKUTE_SGM;		//	標準偏差
	double		SOKUTE_CP;		//	ＣＰ
	double		SOKUTE_CPK;		//	ＣＰＫ
	double		SOKUTE_K;		//	Ｋ
	double		SOKUTE_P;		//	不良率
	double		JYOKEN1;		//	測定条件１
	double		JYOKEN2;		//	　〃　　２
	AnsiString	JYOKEN3;		//	　〃　　３
	AnsiString	ADDYMD;			//	登録日
	AnsiString	ADDTIM;			//	登録時間
	AnsiString	UPDYMD;			//	変更日
	AnsiString	UPDTIM;			//	変更時間
	int	     	UPDCHR;			//	更新者
	int	     	UPDCNT;			//	更新回数
};

//ヒストがラム測定データ
struct KDB2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // 測定値
       double SOKUTEI_MEI1;	// 取付抵抗=電圧、母体=厚さ、固有抵抗=厚さ、抗折力=厚さ
       double SOKUTEI_MEI2;	// 取付抵抗=電流、母体=幅、固有抵抗=幅、抗折力=幅
       double SOKUTEI_MEI3;	// 母体=長さ、固有抵抗=mV L、抗折力=負荷
       double SOKUTEI_MEI4;	// 母体=重量、固有抵抗=A L、抗折力=スパン（変更値）
       double SOKUTEI_MEI5;	// 固有抵抗=mV R
       double SOKUTEI_MEI6;	// 固有抵抗=A R
       double SOKUTEI_MEI7;	// 固有抵抗=プローブ
};

//印刷桁数
struct KETA_DATA {
       int 			AVE;       // 平均値
       int 			MIN;       // 最小値
       int 			MAX;       // 最大値
       int 			R;         // R
       int 			SGM;       // 標準偏差σ
       int 			CP;        // CP
       int 			CPK;       // CPK
       int 			K;         // K
       int 			P;         // 不良率
       AnsiString 	AVE_str;   // 平均値
       AnsiString 	MIN_str;   // 最小値
       AnsiString 	MAX_str;   // 最大値
       AnsiString 	R_str;     // R
       AnsiString 	SGM_str;   // 標準偏差σ
       AnsiString 	CP_str;    // CP
       AnsiString 	CPK_str;   // CPK
       AnsiString 	K_str;     // K
       AnsiString 	P_str;     // 不良率
       AnsiString 	KMK_str;   // 検査項目
       double SOKUTE_AVE;      // 平均値
       double SOKUTE_MIN;      // 最小値
       double SOKUTE_MAX;      // 最大値
       double SOKUTE_R;        // R
       double SOKUTE_SGM;      // 標準偏差σ
       double SOKUTE_CP;       // CP
       double SOKUTE_CPK;      // CPK
       double SOKUTE_K;        // K
       double SOKUTE_P;        // 不良率
};
extern KETA_DATA KETA;

struct structKM02 { 	//検査マスタデータ KM01_04
	AnsiString	DTKSCOD;		//	得意先コード
	AnsiString	DTKSHIN;		//	得意先品番
	AnsiString	HINBAN;			//	自社品番
	AnsiString	ZISCOD;			//	材質コード
	AnsiString	ZISNAM;			//	材質名
	AnsiString	SYOSCOD;		//	焼成コード
	int	SORTKEY;	      		//	ソートキー
	int	KEIJKBN;				//	形状区分
	int	SK_LD_LNG;				//	測定区分　線長さ
	int	SK_BURASI;				//	　〃　　　ブラシ幅
	int	SK_BURASIT;				//	　〃　　　ブラシ幅縦押し
	int	SK_LD_TR;				//	　〃　　　線取付抵抗
	int	SK_LD_HP;				//	　〃　　　線引張強度
	int	SK_BOTAI;				//	　〃　　　母体比重
	int	SK_KOYU;				//	　〃　　　固有抵抗
	int	SK_MAGE;				//	　〃　　　抗折力
	int	SK_HSC_A;				//	　〃　　　HsC硬度（圧面）
	int	SK_HSC_S;				//	　〃　　　HsC硬度（側面）
	int	SK_HSD_A;				//	　〃　　　HsD硬度（圧面）
	int	SK_HSD_S;				//	　〃　　　HsD硬度（側面）
	int	SK_ZAKUT;				//	　〃　　　座屈
	int	HIST_SOKUT;				//	ヒストグラム測定数
	int	HIST_KIKAK;				//	　〃　　　　　規格
	double	HIST_MIN;			//	　〃　　　　　下限規格
	double	HIST_MAX;			//	　〃　　　　　上限規格
	double	LD_LNG_MIN;			//	リード線長さ　上限
	double	LD_LNG_MAX;			//	　〃　　　　　下限
	double	BURASI_MIN;			//	ブラシ幅　上限
	double	BURASI_MAX;			//	　〃　　　下限
	double	BURASIT_MIN;		//	ブラシ幅縦押し上限
	double	BURASIT_MAX;		//	　〃　　　　　下限
	double	LD_TR_DENA;			//	リード線取付測定電圧
	double	LD_TR_DENR;			//	リード線取付測定電流
	int	LD_TR_TIME;				//	　〃　　取付測定時間
	AnsiString	LD_TR_TYPE;		//	　〃　　取付測定タイプ
	int	LD_HP_SPD;				//	リード線引張測定速度
	double	LD_HP_KYO;			//	　〃　　引張強度
	int	LD_HP_TAN;				//	　〃　　引張強度単位
	double	BOTAI_MIN;			//	母体比重　下限
	double	BOTAI_MAX;			//	　〃　　　上限
	int	KOYU_MIN;				//	固有抵抗率　下限
	int	KOYU_MAX;				//	　〃　　　　上限
	double	KOYU_DEN;			//	　〃　　　　電流
	int	KOYU_PRO;				//	　〃　　　　プローブ
	double	MAGE_MIN;			//	曲げ強度　下限
	double	MAGE_MAX;			//	　〃　　　上限
	int	MAGE_TAN;				//	　〃　　　単位
	double	MAGE_SPAN;			//	　〃　　　スパン
	int	HSC_A_MIN;				//	ＨｓＣ硬度（圧面）下限
	int	HSC_A_MAX;				//	　〃　　　　　　　上限
	int	HSC_S_MIN;				//	　〃　　　（側面）下限
	int	HSC_S_MAX;				//	　〃　　　　　　　上限
	double	HSD_A_MIN;			//	ＨｓＤ硬度（圧面）下限
	double	HSD_A_MAX;			//	　〃　　　　　　　上限
	double	HSD_S_MIN;			//	　〃　　　（側面）下限
	double	HSD_S_MAX;			//	　〃　　　　　　　上限
	int	ZAKUT_MIN;				//	座屈　下限
	int	ZAKUT_MAX;				//	　〃　上限
	double	MAGEG_MIN;			//	曲げ強度（現物）　下限
	double	MAGEG_MAX;			//	　〃　　　        上限
	int	MAGEG_TAN;				//	　〃　　　　      単位
	double	MAGEG_SPAN;			//	　〃　　　　      スパン
};
extern structKM02 KM02;



extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int RSInputFlag;
extern int     KENSAKU_Mode;           //一覧検索モード
                                       //１：検査予定日
                                       //２：得意先品番
                                       //３：ロットNO

extern KDB1_DATA Tmp_KDB1;             // 選択した工程能力
extern KDB1_DATA Cur_Kdb1;             // 選択したヒストグラムデータ
extern KDB2_DATA M_Kdb2[1000];         // 計測データ（最大値：１０００個）

extern double E_Screen_Data[3][20];

extern int E_Scale;

extern int KEIJKBN_KM02;                //KM02の製品規格の形状区分
extern int LD_HP_TAN_KM02;                //KM02の製品規格の形状区分
extern int MAGE_TAN_KM02;                //KM02の製品規格の形状区分


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

extern int iKojoKbn ;            //工場区分 2016/06/30 追加

