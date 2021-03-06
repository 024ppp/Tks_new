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
//ÏÌé¾
//\¢Ì
extern struct structUPDCHR {  //¸õ
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


extern struct structKD01 {  //[hü·³ KD01
    int PASS;               //[hü·³ ¸i si
    int LD_LNG_NM;          //[hü·³ ¸f[^
    double LD_LNG_MIN;      //[hü·³ Kiº
    double LD_LNG_MAX;      //[hü·³ Kiã
    double LD_LNG_VAL[100]; //[hü·³ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD01Data;

extern struct structKD11 {  //uV¡@  KD11
    int PASS;               //uV¡@  ¸i si
    int BURASI_NM;          //uV¡@ ¸f[^
    double BURASI_MIN;      //uV¡@ Kiº
    double BURASI_MAX;      //uV¡@ Kiã
    double BURASI_VAL[100]; //uV¡@ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD11Data;

extern struct structKD21 {  //uV¡@cµ  KD21
    int PASS;               //uV¡@cµ  ¸i si
    int BURASIT_NM;         //uV¡@cµ ¸f[^
    double BURASIT_MIN;     //uV¡@cµ Kiº
    double BURASIT_MAX;     //uV¡@cµ Kiã
    double BURASIT_VAL[100];//uV¡@cµ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD21Data;

extern struct structKD31 {  //[hüætïR  KD31
    int PASS;               //[hüætïR  ¸i si
    int LD_TR_NM;         	//[hüætïR ¸f[^
    double LD_TR_DEN;      	//[hüætïR ªèd³
    double LD_TR_TIME;     	//[hüætïR ªèÔ
    double LD_TR_TEKO;     	//[hüætïR ªèd¬
    double LD_TRV_VAL[100];	//[hüætïR ªèd³ ¸f[^
    double LD_TRA_VAL[100];	//[hüætïR ªèd¬ ¸f[^
    double LD_TRR_VAL[100];	//[hüætïR ªèïR ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD31Data;

extern struct structKD41 {  //[hüø£­x  KD41
    int PASS;               //[hüø£­x  ¸i si
    double LD_HP_NM;          	//[hüø£­x ¸f[^
    double LD_HP_MIN;      	//[hüø£­x Kiº
    double LD_HP_VAL[100];		//[hüø£­x ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD41Data;

extern struct structKD51 { 	//êÌäd KD51
    int PASS;             	//êÌäd ¸i si
    int BOTAI_NM;         	//êÌäd ¸f[^
    double BOTAI_MIN;   	//êÌäd Kiº
    double BOTAI_MAX;     	//êÌäd Kiã
    double BOTAI_VAL[100];	//êÌäd ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD51Data;

extern struct structKD61 {  //gdx  KD61
    int PASS;               //gdx  ¸i si
	int	HSC_A_MIN;			//gbdx³Ê Kiº
	int	HSC_A_MAX;			//  V@@@@ @Kiã
	int	HSC_S_MIN;			//  V@@@¤Ê Kiº
	int	HSC_S_MAX;			//  V@@@@@ Kiã
	int	HSC_A_VAL[100];		//gbdx³Ê ¸f[^
	int	HSC_S_VAL[100];		//  V@@@¤Ê ¸f[^
	int	HSC_A_SK_NM;		//gbªèÂ
	int	HSC_S_SK_NM;		//gbªèÂ
	double	HSD_A_MIN;		//gcdx³Ê Kiº
	double	HSD_A_MAX;		//@V@@@@@ Kiã
	double	HSD_S_MIN;		//@V@@@¤Ê Kiº
	double	HSD_S_MAX;		//@V@@@@@ Kiã
	double	HSD_A_VAL[100];	//gcdx³Ê ¸f[^
	double	HSD_S_VAL[100];	//@V@@@¤Ê ¸f[^
	int	HSD_A_SK_NM;		//gcªèÂ
	int	HSD_S_SK_NM;		//gcªèÂ
    int UPDCHR;             //XVÒ
	int HSC_SK_SU;			//gbªè
	int HSD_SK_SU;			//gcªè
}KD61Data;

extern struct structKD71 {  //ÅLïR¦  KD71
    int PASS;               //ÅLïR¦  ¸i si
    int KOYU_NM;       		//ÅLïR¦ ¸f[^
    int KOYU_MIN;   	   	//ÅLïR¦ Kiº
    int KOYU_MAX;   	   	//ÅLïR¦ Kiã
    int KOYU_VAL[100];  	//ÅLïR¦ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD71Data;

extern struct structKD81 {  //RÜÍ  KD81
    int PASS;               //RÜÍ  ¸i si
    int MAGE_NM;       	    //RÜÍ ¸f[^
    double MAGE_MIN; 	   	//RÜÍ Kiº
    double MAGE_MAX;  	  	//RÜÍ Kiã
    double MAGE_VAL[100]; 	//RÜÍ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD81Data;

extern struct structKD91 {  //Àü  KD91
    int PASS;               //Àü  ¸i si
    int ZAKUT_NM;       	//Àü ¸f[^
    int ZAKUT_MIN; 	   	    //Àü Kiº
    int ZAKUT_MAX;  	  	//Àü Kiã
    int ZAKUT_VAL[100]; 	//Àü ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD91Data;

//2002/12/05 E.Takase
extern struct structKDC1 {  //»¨RÜÍ KDC1
    int PASS;               //»¨RÜÍ ¸i si
    int MAGEG_NM;       	//»¨RÜÍ ¸f[^
    double MAGEG_MIN; 	   	//»¨RÜÍ Kiº
    double MAGEG_MAX;  	  	//»¨RÜÍ Kiã
    double MAGEG_VAL[100]; 	//»¨RÜÍ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KDC1Data;

extern struct structKD71_L {  //ÅLïR¦  KD71
    int PASS;               //ÅLïR¦  ¸i si
    int KOYU_NM;       		//ÅLïR¦ ¸f[^
    int KOYU_MIN;   	   	//ÅLïR¦ Kiº
    int KOYU_MAX;   	   	//ÅLïR¦ Kiã
    double KOYU_VAL[100];  	//ÅLïR¦ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD71Data_L;

extern struct structKD71_R {  //ÅLïR¦  KD71
    int PASS;               //ÅLïR¦  ¸i si
    int KOYU_NM;       		//ÅLïR¦ ¸f[^
    int KOYU_MIN;   	   	//ÅLïR¦ Kiº
    int KOYU_MAX;   	   	//ÅLïR¦ Kiã
    double KOYU_VAL[100];  	//ÅLïR¦ ¸f[^
    int UPDCHR;             //XVÒ
	int SOKUTEI_SU;			//ªè
}KD71Data_R;



extern struct structKM01_04 { 	//¸}X^f[^ KM01_04
	AnsiString	KENSA_YMD; 		//	¸\èNú
	int	TOLEY_NO;	            	//	g[No
	int	SAMPLE_P;       		//	Tv|WV
	int	KOKBNG;	            	//	HÇNo
	AnsiString	DTKSCOD;		//	¾ÓæR[h
	AnsiString	DTKSHIN;		//	¾ÓæiÔ
	AnsiString	LOTNO;			//	bgNo
	AnsiString	HINBAN;			//	©ÐiÔ
	AnsiString	ZISCOD;			//	Þ¿R[h
	AnsiString	ZISNAM;			//	Þ¿¼
	int	NUM;            		//	Ä¬R[h
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
	int	LD_TR_TEKO;				//	@V@@ætïR
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
	AnsiString	ADDYMD;			//	o^ú
	AnsiString	ADDTIM;			//	o^Ô
	AnsiString	UPDYMD;			//	ÏXú
	AnsiString	UPDTIM;			//	ÏXÔ
	int	UPDCHR;					//	XVÒ
	int	UPDCNT;					//	XVñ
	AnsiString	RO_NO;			//	FNo
	int	MAX_ONDO;				//	MAX·x
	int	CYCLE_TIME;				//	TCN^C
	int	SK_MAGEG;				//	ªèæª@»¨È°­x
	double	MAGEG_MIN;			//	È°­x@ºÀ
	double	MAGEG_MAX;			//	@V@@@ãÀ
	int	MAGEG_TAN;				//	@V@@@PÊ
	double	MAGEG_SPAN;			//	@V@@@Xp
        int	KOJOKBN;				//	@Hêæª
        //20161024 Y.Onishi HêæªÇÁ
}KM01_04Data;

extern int KENSAKU_Mode;        //êõ[h
                                //0 ¸ú
                                //1 ¾ÓæiÔ
                                //2 JnbgNo
                                //3 I¹bgNo

extern int DataNo;    //Åå¸f[^
extern int Master_rec;//}X^îñóüs
extern int rec;       //R[h
extern int pass;      //i1Asi0
extern int newpage;   //üy[WNo
extern AnsiString strcnd;       //¸ú
extern AnsiString strcnd2;       //¸ú
extern AnsiString DTKSHINcnd;   //¾ÓæiÔ
extern AnsiString StartLOTcnd;  //JnbgNo
extern AnsiString EndLOTcnd;    //I¹bgNo
extern AnsiString DTKSCODcnd;   //¾ÓæR[h
extern int Flagcnd;             //0¨¸úÊ  1¨¾ÓæiÔÊ

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
//ÖÌé¾
extern void UPDCHRInsert01(void);
extern void UPDCHR_Serch01(void);  //2002/12/06 E.Takase R~p
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
extern void KIKAKU_MINInsert02(void);  //2002/12/06 E.Takase R~p
extern void KIKAKU_MAXInsert01(void);
extern void PASS_FailUpdate01(void);
extern void KM01_04Sub01(void);
extern void SOKUTEIInsert01(void);
extern void SOKUTEIInsert02(void);     //2002/12/06 E.Takase R~p
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

//¾ÓæÊÉ¸õðõ
extern void UPDCHR_Make01(int CurNo);
extern void UPDCHR_2_Make01(int CurNo);  //2002/12/06 E.Takase R~p
//u¸õ=EEEEv¶ñì¬
extern void UPDCHR_Make02(void);
extern void UPDCHR_2_Make02(void);       //2002/12/06 E.Takase R~p
//TW_UPDCHR É ÇÁ
extern void UPDCHRInsert02(void);

extern int iKojoKbn ;            //Hêæª 2016/06/24 ÇÁ

#endif




