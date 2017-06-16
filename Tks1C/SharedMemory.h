/******************************************************************************
				Copyright (C) 1998 NKK Unics Corporation
						All Right Reserved

	System Name	:	汎用 共用メモリ関数
	File Name	:	ShareMemory.h
	Create		:	1998.11.22
	Contents	:	共用メモリ関数
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
******************************************************************************/
// シェアメモリ
#define MAXSHARE 2		// 最大シェアメモリ数
#define BUFFERSIZE 3072	// データサイズ
#define SHAREDSIZE 4096	// シェアメモリサイズ （BUFFERSIZE + 4 * 4 以上）
//#define TIMEOUT 500000	// タイマーアウト ５00秒
#define TIMEOUT 2000

#define WM_Notify_ReqData    WM_USER + 3010  // 要求データ送信メッセージ(共有メモリ)
#define WM_Notify_WriteData  WM_USER + 3040	// 相手プロセスに通知します
#define WM_Notify_WriteData1 WM_USER + 3041	// 相手プロセスに通知します

// プロセス間通信（共用メモリ）エリアの構造体
typedef struct {
	HWND	FHw_Owner;	// 共用メモリを作成するプロセスのウィンドウハンドル
	HWND	FHw_User;	// 共用メモリを使用するプロセスのウィンドウハンドル
	int	Fin_Notice;						// 0: 読込完了;  1: 書込完了
	DWORD	Fdw_DataSize;				// 有効データ長（バイト数)
	char	Fby_DataBuff[BUFFERSIZE];	// データエリア
} TRec_IFarea;

typedef struct {
	short	FId;						// function code
	char	DataBuff[BUFFERSIZE-2];		// Data buffer
} TRec_DataBuff;

// Declear for Shared Memory Routine

// 通信用シェアメモリ作成
// 戻り値:	-1: シェアメモリID エラー
//		-2: シェアメモリエラー
//		 1: 正常
extern int SharedMemory_Create(HWND hWnd, char *SName, int SId);

// 通信用シェアメモリ開く
// 戻り値:	-1: シェアメモリID エラー
//			-2: シェアメモリエラー
//			 1: 正常
extern int SharedMemory_Open(HWND hWnd, char *SName, int SId);

// Share Memory Close
// 戻り値:	-1: シェアメモリID エラー
//			 1: 正常
extern int SharedMemory_Close(int SId);

// Read from Share Memory
// 戻り値:	-1: シェアメモリID エラー
//			-4: Openされていない
//			 0: No Data or Data not ready
//			>0: データ長
// 注意：Fortranでメッセージ来ないので、WM_Notify_WriteDataのチェックなし
extern int SharedMemory_Read(int SId, char *RedBuf);

// send data request(Windows Message)
// 戻り値:	-1: シェアメモリID エラー
//			-4: Openされていない
//			 1: 正常
extern int SharedMemory_SendReq(int SId);

// Write to Share Memory
// 戻り値:	-1: シェアメモリID エラー
//			-3: タイマーアウト
//			-4: Openされていない
//			 1: 正常
extern int SharedMemory_Write(int SId, int FId, char *RecBuf, int Len);

// receive WM_Notify_WirteData
extern void SharedMemory_Message(int D_Size, int SId);

// シェアメモリエラーメッセージの表示
extern void SharedMemoryErrorString(int errno);

