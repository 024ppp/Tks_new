/******************************************************************************
				Copyright (C) 1999 NKK Unics Corporation
						All Right Reserved

	System Name	:	TRIS 検査システム 中間検索
    File Name	:	Socket.h
    Create		:	1999.09.29
	Contents	:	Socket 基本ルーチン
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
******************************************************************************/
#include <winsock.h>

/*
 * WinSock 2 extension -- manifest constants for shutdown()
 */
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

#define MAXSOCKET			 5	// 最大Socket数
#define MAX_PENDING_CONNECTS 4	// the backlog allowed for listen()
#define NO_FLAGS_SET		 0	// Used with recv()/send()
#define MY_MSG_LENGTH		256	// msg buffer sent back and forth

// Socket初期化
// 戻り値：	 1: 正常
//			-6: Socket初期化エラー
extern int  Socket_Init();

// Create Server Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-2: Openしました
//			-3: Socketエラー
extern int  Socket_Open_Server(char *PName, int SId);

// Socket Accept
// 戻り値：	1: 正常
//			-3: Socket エラー
extern int Socket_Server_Accept(int SId);

// Create Client Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-2: Openしました
//			-3: Socketエラー
extern int  Socket_Open_Client(char *PName, char *HName, int SId);

// Read from Socket
// 戻り値：	>0: 有効バイト数
//			-1: Socket ID Error
//			-4: Openされていません
//			-5: Disconnected
extern int  Socket_Recv(int SId, char *RecvBuf);

// Read from Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-4: Openされていません
extern int  Socket_Send(int SId, char *SendBuf, int len);

// Close Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-4: Openされていません
//			-7: Socket 終了エラー
extern int  Socket_Close(int SId);

// Socket終了
extern void Socket_End();

// Socket エラー表示
extern void SocketErrorString(int errno);
