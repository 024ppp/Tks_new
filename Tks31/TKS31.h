//ヒストグラム測定プログラム
//ヒストグラムデータ
struct KDA1_DATA {
       int No;                  // 選択番号
       AnsiString KENSA_YMD;	// 検査予定年月日
       int SEQNO;       		// SEQ-NO
       AnsiString DTKSCOD;  	// 得意先コード
       AnsiString DTKSHIN;      // 得意先品番
       AnsiString LOTNO;    	// ロットNo
       AnsiString HINBAN;   	// 自社品番
       AnsiString ZISCOD;       // 材質コード
       AnsiString ZISNAM;       // 材質名
       int HIST_SOKUT_Ori;      // ヒストグラム測定数(Origal)
       int HIST_SOKUT;          // ヒストグラム測定数
       int HIST_KIKAK;          // ヒストグラム規格（１，２，３）
       double HIST_MIN;         // ヒストグラム下限規格
       double HIST_MAX;         // ヒストグラム上限規格
       int SOKUTE_SU;           // 測定数
       int SOKUTE_SU_Ori;
       double SOKUTE_AVE;       // 平均値
       double SOKUTE_MIN;       // 最小値
       double SOKUTE_MAX;       // 最大値
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // 標準偏差σ
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // 不良率
       AnsiString ADDYMD;       // 登録日
       AnsiString ADDTIM;       // 登録時間
       AnsiString UPDYMD;       // 変更日
       AnsiString UPDTIM;       // 変更時間
       int UPDCHR;              // 更新者
       int UPDCNT;              // 更新回数
};

//ヒストグラム測定データ
struct KDA2_DATA {
       int DatabaseFlag;        // 1: Read from Database
       double SOKUTEI_CH;       // 測定値
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
       double SOKUTE_AVE;       // 平均値
       double SOKUTE_MIN;       // 最小値
       double SOKUTE_MAX;       // 最大値
       double SOKUTE_R;         // R
       double SOKUTE_SGM;       // 標準偏差σ
       double SOKUTE_CP;        // CP
       double SOKUTE_CPK;       // CPK
       double SOKUTE_K;         // K
       double SOKUTE_P;         // 不良率
};
extern KETA_DATA KETA;

extern int     SEQNOMAX;
extern int     USER_COD;
extern String  USER_NAM;
extern String  BUMO_COD;
extern String  BUMO_NAM;
extern bool    DataSave;
extern int     KENSAKU_Mode;           //一覧検索モード
                                       //１：検査予定日
                                       //２：得意先ｺｰﾄﾞ
                                       //３：得意先品番

extern KDA1_DATA Cur_Kda1;             // 選択したヒストグラムデータ

extern KDA2_DATA M_Kda2[1000];         // 計測データ（最大値：１０００個）


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

