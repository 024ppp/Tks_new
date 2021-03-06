//データ
struct KD_DATA {
       AnsiString KENSA_YMD;	// 検査日
       AnsiString DTKSHIN;      // 得意先品番
       AnsiString LOTNO;    	// ロットNo
       AnsiString ZISNAM;       // 材質名
       double KIKAK_MIN;        // 下限規格
       double KIKAK_MAX;        // 上限規格
       int SOKUTE_SU;           // 測定数
       int SOKUTE_NM;           // 測定指示数
       double SOKUTEI_1;       	// 測定値1
       double SOKUTEI_2;       	// 測定値2
       double X_AVE;       		// X平均値
       double R;       			// R
       double TANI;       		// 単位

};

//計算データ
struct CAL_DATA {
       AnsiString StartYMD;		// 開始検査日
       AnsiString EndYMD;		// 終了検査日
       AnsiString StartLOTNO;	// 開始ロットNo
       AnsiString EndLOTNO;		// 終了ロットNo
       double MIN;       		// 最小値
       double MAX;       		// 最大値
       double X_AVE_MIN;       	// X平均値 最小値
       double X_AVE_MAX;       	// X平均値 最大値
       double X_AVE_AVE;       	// X平均値 平均値
       double R_MIN;       		// R 最小値
       double R_MAX;       		// R 最大値
       double R_AVE;       		// R 平均値
       double X_AVE_ScaleMin;   // X平均値 目盛りの最小値
       double X_AVE_ScaleMax;   // X平均値 目盛りの最大値
       double X_AVE_Scale;      // X平均値 目盛りの間隔
       double R_ScaleMin;       // R 目盛りの最小値
       double R_ScaleMax;       // R 目盛りの最大値
       double R_Scale;       	// R 目盛りの間隔
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


extern int     USER_COD;               //担当者コード
extern String  USER_NAM;               //担当者名
extern String  BUMO_COD;               //部署コード
extern String  BUMO_NAM;               //部署名
extern int     KENSAKU_Mode;           //一覧検索モード
                                       //１：検査予定日
                                       //２：得意先ｺｰﾄﾞ
                                       //３：得意先品番

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

extern int intKEIJKBN; //形状区分 //2002/12/07 E.Takase

