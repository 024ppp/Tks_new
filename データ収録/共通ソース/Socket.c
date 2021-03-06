/******************************************************************************
				Copyright (C) 1999 NKK Unics Corporation
						All Right Reserved

	System Name	:	TRIS 検査システム 中間検索用
    File Name	:	Socket.c
    Create		:	1999.09.29
	Contents	:	Socket 基本ルーチン
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
******************************************************************************/
#include <stdio.h>
#include "Socket.h"

int Server_Flag = 0;

int Socket_Err_Disp = 1;

SOCKET Sock[MAXSOCKET];
SOCKET ClientSocket[MAXSOCKET];

SOCKADDR_IN local_sin[MAXSOCKET];		// Local socket - internet style

char PortName[64];		// Service Name (Port Name)
char HostName[64];		// Host Name
int Open_Flag[MAXSOCKET] = {0, 0, 0, 0, 0};

// Socket 内部関数
BOOL FillAddr_S(HWND hWnd, PSOCKADDR_IN psin, BOOL bClient);
BOOL FillAddr_C(HWND hWnd, PSOCKADDR_IN psin, BOOL bClient);

// Socket初期化
// 戻り値：	 1: 正常
//			-6: Socket初期化エラー
int Socket_Init()
{
	int status;					// status code
	WSADATA WSAData;
//	char tempo[128];

	//start socket
	if ((status = WSAStartup(MAKEWORD(1,1), &WSAData)) != 0) {
		//if (Socket_Err_Disp == 1) {
		//	sprintf(tempo, "Socket error is %d", status);
		//	MessageBox(GetFocus(), tempo, "ソケット初期化エラー", MB_OK);
		//}
		return -6;
	}

	return 1;
}

// Create Server Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-2: Openしました
//			-3: Socketエラー
int Socket_Open_Server(char *PName, int SId)
{
	//SOCKADDR_IN local_sin;		// Local socket - internet style
	//int local_sin_len;

	Server_Flag = 1;

	if (SId <= 0 || SId > MAXSOCKET)
		return -1;
	
	if (Open_Flag[SId-1] == 1)
		return -2;

	Sock[SId-1] = socket(AF_INET, SOCK_STREAM, 0);
	if (Sock[SId-1] == INVALID_SOCKET) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "ソケット作成エラー(socket)", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

	strcpy(PortName, PName);

	if (!FillAddr_S(GetFocus(), &local_sin[SId-1], FALSE)) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "IPアドレスエラー(FillAddr)", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

	if (bind(Sock[SId-1], (struct sockaddr FAR *)&local_sin[SId-1], sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "bind() failed", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

	if (listen(Sock[SId-1], MAX_PENDING_CONNECTS) < 0) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "listen() failed", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

//	local_sin_len = sizeof(local_sin);
//	Sock[SId-1] = accept(Sock[SId-1], (struct sockaddr FAR *)&local_sin, &local_sin_len);
//	if (Sock[SId-1] < 0) {
//		if (Socket_Err_Disp == 1) 
//			MessageBox(GetFocus(), "accept failed", "", MB_OK);
//		Socket_Close(SId);
//		return -3;
//	}

//	Open_Flag[SId-1] = 1;

	return 1;
}

int Socket_Server_Accept(int SId)
{
	//SOCKADDR_IN local_sin;		// Local socket - internet style
	//int local_sin_len;

	//local_sin_len = sizeof(local_sin[SId-1]);
	//Sock[SId-1] = accept(Sock[SId-1], (struct sockaddr FAR *)&local_sin[SId-1], &local_sin_len);
	ClientSocket[SId-1] = accept(Sock[SId-1], 0, 0);
	if (ClientSocket[SId-1] < 0) {
		//if (Socket_Err_Disp == 1) 
		//	MessageBox(GetFocus(), "accept failed", "", MB_OK);
		Socket_Close(SId);
		return -3;
	}

	Open_Flag[SId-1] = 1;

	return 1;
}

// Create Client Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-2: Openしました
//			-3: Socketエラー
int Socket_Open_Client(char *PName, char *HName, int SId)
{
	//SOCKADDR_IN local_sin;		// Local socket - internet style

	Server_Flag = 0;

	if (SId <= 0 || SId > MAXSOCKET)
		return -1;
	
	if (Open_Flag[SId-1] == 1)
		return -2;

	Sock[SId-1] = socket(AF_INET, SOCK_STREAM, 0);
	if (Sock[SId-1] == INVALID_SOCKET) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "socket() failed", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

	strcpy(PortName, PName);
	strcpy(HostName, HName);

	if (!FillAddr_C(GetFocus(), &local_sin[SId-1], TRUE)) {
		if (Socket_Err_Disp == 1) {
			MessageBox(GetFocus(), "FillAddr() failed", "Socket Error", MB_OK);
		}
		Socket_Close(SId);
		return -3;
	}

	if (connect(Sock[SId-1], (PSOCKADDR)&local_sin[SId-1], sizeof(SOCKADDR_IN)) < 0) {
		//if (Socket_Err_Disp == 1) {
		//	MessageBox(GetFocus(), "connect() failed", "Socket Error", MB_OK);
		//}
		Socket_Close(SId);
		return -3;
	}

	Open_Flag[SId-1] = 1;

	return 1;
}

// Read from Socket
// 戻り値：	>0: 有効バイト数
//			-1: Socket ID Error
//			-4: Openされていません
//			-5: Disconnected
int Socket_Recv(int SId, char *RecvBuf)
{
	int status;
	char SockBuf[MY_MSG_LENGTH];

	if (SId <= 0 || SId > MAXSOCKET)
		return -1;
	
	if (Open_Flag[SId-1] != 1)
		return -4;

	if (Server_Flag == 1) 
		status = recv(ClientSocket[SId-1], SockBuf, MY_MSG_LENGTH, NO_FLAGS_SET);
	else
		status = recv(Sock[SId-1], SockBuf, MY_MSG_LENGTH, NO_FLAGS_SET);
	if (status == SOCKET_ERROR) {
		//if (Socket_Err_Disp == 1)
		//	MessageBox(GetFocus(), "Socket Disconnect", "Socket_Recv", MB_OK);
		Socket_Close(SId);
		return -5;
	}

	SockBuf[status] = '\0';
	strcpy(RecvBuf, SockBuf);

	return status;
}

// Send to Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-4: Openされていません
int Socket_Send(int SId, char *SendBuf, int len)
{
	char SockBuf[MY_MSG_LENGTH];

	if (SId <= 0 || SId > MAXSOCKET)
		return -1;
	
	if (Open_Flag[SId-1] != 1)
		return -4;

	memcpy(SockBuf, SendBuf, len);
	SockBuf[len] = '\0';

	if (Server_Flag == 1)
		send(ClientSocket[SId-1], SockBuf, strlen(SockBuf), NO_FLAGS_SET);
	else
		send(Sock[SId-1], SockBuf, strlen(SockBuf), NO_FLAGS_SET);

	return 1;
}

// Close Socket
// 戻り値：	 1: 正常
//			-1: Socket ID Error
//			-4: Openされていません
//			-7: Socket 終了エラー
int Socket_Close(int SId)
{
	int ret;

	if (SId <= 0 || SId > MAXSOCKET)
		return -1;
	
	if (Open_Flag[SId-1] != 1)
		return 1;
//		return -4;

	if (Server_Flag == 1) {
		ret = shutdown(ClientSocket[SId-1], SD_SEND);
		if (ret != 0)
			return -7;

		ret = closesocket(ClientSocket[SId-1]);
		if (ret != 0)
			return -7;
	} else {
		ret = shutdown(Sock[SId-1], SD_SEND);
		if (ret != 0)
			return -7;

		ret = closesocket(Sock[SId-1]);
		if (ret != 0)
			return -7;
	}

	Open_Flag[SId-1] = 0;

	return 1;
}

// Socket終了
void Socket_End()
{
	int i;

	for (i = 0; i < MAXSOCKET; i++) 
		Open_Flag[i] = 0;

	WSACleanup();
}

// Socket エラー表示
void SocketErrorString(int errno)
{
	switch (errno) {
		case -1:
			MessageBox(GetFocus(), "Socket IDエラー", "", MB_OK);
			break;
		case -2:
			MessageBox(GetFocus(), "Socket Openしました", "", MB_OK);
			break;
		case -3:
			MessageBox(GetFocus(), "Socketエラー", "", MB_OK);
			break;
		case -4:
			MessageBox(GetFocus(), "Openされていない", "", MB_OK);
			break;
		case -5:
			MessageBox(GetFocus(), "相手Disconnected", "", MB_OK);
			break;
		case -6:
			MessageBox(GetFocus(), "Socket初期化エラー", "", MB_OK);
			break;
		case -7:
			MessageBox(GetFocus(), "Socket終了エラー", "", MB_OK);
			break;
		default:
			;
	}
}

/*****************************************************************************
	Socket 基本ルーチン
******************************************************************************/

/****************************************************************************\
*
*    FUNCTION:  FillAddr_S(HWND, PSOCKADDR_IN, BOOL)
*
*    PURPOSE:  Retrieves the IP address and port number.
*
*    COMMENTS:	Server
*				call bind(), listen() and accept().
*				a SOCKADDR_IN structure is filled.
*
*   ASSUMPTION:
*      PortName is a global variable that contains service name (Post Name)
*
*\***************************************************************************/
BOOL FillAddr_S(HWND hWnd, PSOCKADDR_IN psin, BOOL bClient)
{
	DWORD dwSize;
	PSERVENT pse;
	char TszBuff[ MY_MSG_LENGTH ];
	char tempo[256];

	psin->sin_family = AF_INET;

	// server
	// Retrieve my ip address.  Assuming the hosts file in
    //in %systemroot%/system/drivers/etc/hosts contains my computer name.

	dwSize = sizeof(TszBuff);
    gethostname(TszBuff, dwSize);

    psin->sin_addr.s_addr = INADDR_ANY;
 
    //   Find the service name, szBuff, which is a type tcp protocol in
    //   the "services" file.
    pse = getservbyname(PortName, "tcp");
    if (pse == NULL)  {
		if (Socket_Err_Disp == 1) {
			sprintf(tempo, "%d is the error. Make sure this is a valid TCP service.", WSAGetLastError());
			MessageBox(hWnd, tempo, "getservbyname(sock) failed", MB_OK);
		}
        return FALSE;
	}
    psin->sin_port = pse->s_port;

   return TRUE;
}

/****************************************************************************\
*
*    FUNCTION:  FillAddr_C(HWND, PSOCKADDR_IN, BOOL)
*
*    PURPOSE:  Retrieves the IP address and port number.
*
*    COMMENTS:	a client is preparing to call connect()
*				a SOCKADDR_IN structure is filled.
*
*   ASSUMPTION:
*				HostName: remote host name
*				PortName: port name
*\***************************************************************************/
BOOL FillAddr_C(HWND hWnd, PSOCKADDR_IN psin, BOOL bClient)
{
	PHOSTENT phe;
	PSERVENT pse;
	char szTemp[200];

	psin->sin_family = AF_INET;

	// client
	phe = gethostbyname(HostName);
	if (phe == NULL) {
		if (Socket_Err_Disp == 1) {
			wsprintf(szTemp, "%d is the error. Make sure '%s' is listed in the hosts file.", WSAGetLastError(), HostName);
			MessageBox(hWnd, szTemp, "gethostbyname() failed.", MB_OK);
		}
        return FALSE;
	}
    
	memcpy((char FAR *)&(psin->sin_addr), phe->h_addr, phe->h_length);

	pse = getservbyname(PortName, "tcp");
	if (pse == NULL)  {
		if (Socket_Err_Disp == 1) {
			wsprintf(szTemp, "%d is the error. Make sure this is a valid TCP service.", WSAGetLastError());
			MessageBox(hWnd, szTemp, "getservbyname(sock) failed", MB_OK);
		}
        return FALSE;
	}
    psin->sin_port = pse->s_port;

	return TRUE;
}

