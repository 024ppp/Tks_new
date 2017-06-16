/******************************************************************************
				Copyright (C) 1999 NKK Unics Corporation
						All Right Reserved

	System Name	:	トライス殿向け 検査システム
	                中間検査 (Socket Memory , RS232C) PC3用
	File Name	:	Pc3Ctrl.c
    Create		:	1999.09.30
	Contents	:	Rs232C (I/O) control
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
******************************************************************************/

#include <windows.h>       /* required for all Windows applications */
#include <winsock.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>
#include <process.h>       /* for _beginthread                      */

// application header file
#include "Pc3Ctrl.h"         /* specific to this program              */

#define WM_CREATE1   WM_USER + 5001  
#define WM_CREATE2   WM_USER + 5002  

HANDLE hInst;              /* current instance                      */
HWND MainhWnd;

char tempo[1024];
FILE *Testfn;

// Interface Box Control
CRITICAL_SECTION G_InterfaceBox;

int AcceptFlag;
int ReadFlag;
int CurrentNo;

typedef struct {
	int ConnectFlag;		// RS232C接続フラグ 0: 接続しない； 1: 接続
	char Buffer[128];		// データバッファ
	int NewFlag;			// 収録フラグ 0: データなし； 2: データあり
	int SocketNo;			// Socket接続番号 0: 接続しない； 1,2: Socket No
} RSDATA;

RSDATA D_Data[5];			// 各チャネルデータ

// 環境(TTY)
char TTYPort[6];		// COM1, COM2, COM3, COM4
int TTYDataBits;		// 5, 6, 7, 8
double TTYStopBits;		// 1, 1.5, 2
char TTYParity[6];		// NONE, EVEN, ODD, MARK, SPACE
int TTYBuadRate;		// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000
char BarString[1024];

extern void _endthread();
extern void _beginthread();

// 内部関数
void Sub_WM_Notify_WriteData(HWND hWnd);
void DetectProc1();
int ChangeChannel(int CNo);
int GetChannelData();
BOOL Rs232Out(BYTE *TTYChar, int len);
void MP_Init(char kiki);

// TTY関係関数
extern LRESULT NEAR CreateTTYInfo(HWND hWnd);
extern BOOL NEAR DestroyTTYInfo(HWND hWnd);
extern BOOL NEAR OpenConnection(HWND hWnd);
extern BOOL NEAR CloseConnection(HWND hWnd);
extern int NEAR ProcessCOMMNotification(HWND hWnd, WPARAM wParam, LPARAM lParam);
extern BOOL NEAR ProcessTTYCharacter( HWND hWnd, BYTE bOut );

/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
*\***************************************************************************/
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	char DirName[256], tmsg[16];
	int rtn;

    UNREFERENCED_PARAMETER( lpCmdLine );

	// Client port name 定義
	// Set INI file name
	GetCurrentDirectory(256, DirName);
	wsprintf(DirName, "%s\\%s", DirName, "Pc3Ctrl.ini");

	// Get TTY Port Message
	GetPrivateProfileString("TTY", "PORT", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Port Nameを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		wsprintf(TTYPort, "%s", tmsg);

	// Get TTY DataBits Message
	GetPrivateProfileString("TTY", "DATABITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Databitsを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		TTYDataBits = atoi(tmsg);

	// Get TTY StopBits Message
	GetPrivateProfileString("TTY", "STOPBITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Stopbitsを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		TTYStopBits = atof(tmsg);

	// Get TTY Parity Message
	GetPrivateProfileString("TTY", "PARITY", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Parityを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		wsprintf(TTYParity, "%s", tmsg);

	// Get TTY Buad Rate Message
	GetPrivateProfileString("TTY", "BUADRATE", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY BuadRateを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		TTYBuadRate = atoi(tmsg);

	// Socket 
	rtn = Socket_Init();
	if (rtn < 0) {
		SocketErrorString(rtn);
		return FALSE;
	}

	rtn = Socket_Open_Server("tproc1", 1);
	if (rtn < 0) {
		SocketErrorString(rtn);
		return FALSE;
	}

	rtn = Socket_Open_Server("tproc2", 2);
	if (rtn < 0) {
		SocketErrorString(rtn);
		return FALSE;
	}

    if (!hPrevInstance)                  /* Other instances of app running? */
        if (!InitApplication(hInstance)) /* Initialize shared things        */
            return (FALSE);              /* Exits if unable to initialize   */

    /*
    *   Perform initializations that apply to a specific instance
    */
    if (!InitInstance(hInstance, nCmdShow))
        return (FALSE);

	// Initialize the critical section brfore the threads so that it is ready when the threads execute
	InitializeCriticalSection(&G_InterfaceBox);

    /*
    *   Acquire and dispatch messages until a WM_QUIT message is received.
    */
    while (GetMessage(&msg,        /* message structure                      */
            NULL,                  /* handle of window receiving the message */
            0,             /* lowest message to examine              */
            0))            /* highest message to examine             */
        {
        TranslateMessage(&msg);    /* Translates virtual key codes           */
        DispatchMessage(&msg);     /* Dispatches message to window           */
   }

	// free critical section
	DeleteCriticalSection(&G_InterfaceBox);

    return (msg.wParam);           /* Returns the value from PostQuitMessage */
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)       /* current instance             */
{
    WNDCLASS  wc;

    /* Fill in window class structure with parameters that describe the       */
    /* main window.                                                           */

    wc.style = 0;						        /* Class style(s).                    */
    wc.lpfnWndProc = (WNDPROC)MainWndProc;      /* Function to retrieve messages for  */
												/* windows of this class.             */
    wc.cbClsExtra = 0;							/* No per-class extra data.           */
    wc.cbWndExtra = 0;							/* No per-window extra data.          */
    wc.hIcon = LoadIcon (hInstance, "wsockicon"); /* Icon name from .RC        */
    wc.hInstance = hInstance;					/* Application that owns the class.   */
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  NULL;					/* Name of menu resource in .RC file. */
    wc.lpszClassName = "WSockWClass";			/* Name used in call to CreateWindow. */

    /* Register the window class and return success/failure code. */
    return (RegisterClass(&wc));
}

/****************************************************************************\
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
*\***************************************************************************/
BOOL InitInstance(
    HANDLE          hInstance,          /* Current instance identifier.       */
    int             nCmdShow)           /* Param for first ShowWindow() call. */
{
    HWND            hWnd;               /* Main window handle.                */

    /* Save the instance handle in static variable, which will be used in  */
    /* many subsequence calls from this application to Windows.            */

    hInst = hInstance;

    /* Create a main window for this application instance.  */
    hWnd = CreateWindow(
        "WSockWClass",                  /* See RegisterClass() call.          */
        "Pc3Ctrl",						/* Text for window title bar.         */
        WS_BORDER,			            /* Window style.                      */
        CW_USEDEFAULT,                  /* Default horizontal position.       */
        CW_USEDEFAULT,                  /* Default vertical position.         */
        100,							/* Default width.                     */
        100,							/* Default height.                    */
        NULL,                           /* Overlapped windows have no parent. */
        NULL,                           /* Use the window class menu.         */
        hInstance,                      /* This instance owns this window.    */
        NULL                            /* Pointer not needed.                */
    );

    /* If window could not be created, return "failure" */

    if (!hWnd)
        return (FALSE);

	MainhWnd = hWnd;

    /* Make the window visible; update its client area; and return "success" */

    ShowWindow(hWnd, nCmdShow);  /* Show the window                        */
    UpdateWindow(hWnd);          /* Sends WM_PAINT message                 */
    return (TRUE);               /* Returns the value from PostQuitMessage */
}

/****************************************************************************\
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes main window messages
*
* MESSAGES:
*  WM_CREATE   - Open TTY
*				Create SharedMemory
*  WM_DESTROY - Close TTY
*\***************************************************************************/
LONG APIENTRY MainWndProc(
        HWND hWnd,                /* window handle                   */
        UINT message,             /* type of message                 */
        UINT wParam,              /* additional information          */
        LONG lParam)              /* additional information          */
{
	int rtn, i;
//	int nNumber;
	HANDLE hThread;
	DWORD ThreadID;

	switch (message) {

		case WM_CREATE:

			GetCurrentDirectory(sizeof(tempo), tempo);
			sprintf(tempo, "%s\\LogPc3.dat", tempo);
			Testfn = fopen(tempo, "w+");
			if (Testfn == NULL) {
				MessageBox(hWnd, "Create Log file Error", "", MB_OK);
				return 0;
			}

			// Create TTY info for COM (Rs232C) communication
			if (CreateTTYInfo(hWnd) <= 0)
				return 0;

			if (!OpenConnection(hWnd)) {
				int TTYFlag = 0;
				int retry = 0;
					
				// 最大５回接続
				while (retry < 5 && TTYFlag == 0) {
					Sleep(1000);
					rtn = OpenConnection(hWnd);
					if (rtn >= 1)
						TTYFlag = 1;
					retry++;
				}
				if (TTYFlag == 0) {
					MessageBox(hWnd, "COM Connection failed", "TTY", MB_OK);
					return 0;					
				} 
			}

			// Multiplexer 初期化
			MP_Init('1');

			// D_Data初期化
			for (i = 0; i < 5; i++) {
				D_Data[i].ConnectFlag = 0;
				D_Data[i].Buffer[0] = '\0';
				D_Data[i].NewFlag = 0;
				D_Data[i].SocketNo = 0;
			}

			CurrentNo = -1;

			// create thread 
			//_beginthread(DetectProc, 0, NULL);
			hThread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"1",
                            0, &ThreadID );

			SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
			ResumeThread( hThread ) ;

			hThread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"2",
                            0, &ThreadID );

			SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
			ResumeThread( hThread ) ;

			break;   /* WM_CREATE */

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case WM_COMMNOTIFY:	// RS232C 処理
			EnterCriticalSection(&G_InterfaceBox);
			rtn = ProcessCOMMNotification(hWnd, wParam, lParam);
			if (rtn > 0) {
				BarString[rtn] = '\0';
				//if (strchr(BarString, 0x02) != NULL) {	// STX		1999.10.05
					if (rtn > 1 && CurrentNo >= 0) {
						strcpy(D_Data[CurrentNo].Buffer, BarString);
						D_Data[CurrentNo].NewFlag = 1;
						fprintf(Testfn, "%d, %s\n", CurrentNo, BarString);
					}
					//ChangeChannel(CurrentNo);
					//ReadFlag = 0;
				//}
/*				if (strchr(BarString, 0x04) != NULL) {	// EOT
					ReadFlag = 0;
				}
				if (strchr(BarString, 0x15) != NULL) {	// NAK
					ReadFlag = 0;
				}
				if (strchr(BarString, 0x06) != NULL) {	// ACK
					ReadFlag = 0;
				}
*/
			}
			LeaveCriticalSection(&G_InterfaceBox);
			break;
/*
		case WM_CREATE1:
			Sleep(1000);
			// Close Socket
			rtn = Socket_Close(1);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return 0;
			}

			// Create Socket
			rtn = Socket_Open_Server("tproc1", 1);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return FALSE;
			}

			hThread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"1",
                            0, &ThreadID );

			SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
			ResumeThread( hThread ) ;
			break;

		case WM_CREATE2:
			Sleep(1000);
			// Close Socket
			rtn = Socket_Close(2);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return 0;
			}

			// Create Socket
			rtn = Socket_Open_Server("tproc2", 2);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return FALSE;
			}

			hThread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"2",
                            0, &ThreadID );

			SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
			ResumeThread( hThread ) ;
			break;
*/		
		// Clean up.  Takes care of any open socket descriptors.
		case WM_DESTROY:

			fclose(Testfn);

			CloseConnection(hWnd);
			DestroyTTYInfo(hWnd );

			// Close Socket
			rtn = Socket_Close(1);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return 0;
			}

			rtn = Socket_Close(2);
			if (rtn < 0) {
				SocketErrorString(rtn);
				return 0;
			}

			Socket_End();

			PostQuitMessage(0);
			break;

		default:                       /* Passes it on if unproccessed    */
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

int ChangeChannel(int CNo)
{
	BYTE TTYChar[10];
	BOOL rtn;

	// 直接Multiplexer
	TTYChar[0] = 0x10;				// DLE
	TTYChar[1] = '0' + CNo;			// CNo
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "ChangeChannel", MB_OK);
		return 0;
	}		

	// CR
//	TTYChar[0] = 0x10;		// DLE
//	TTYChar[1] = 'X';		// X
//	TTYChar[2] = 0x00;		
//	rtn = Rs232Out(TTYChar, 3);

//	if (!rtn) {
//		MessageBox(MainhWnd, "送信エラー(RS232C)", "ChangeChannel", MB_OK);
//		return 0;
//	}		

	CurrentNo = CNo;

	return 1;
}

int GetChannelData()
{
	BYTE TTYChar[10];
	BOOL rtn;

	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 'R';		// R
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "GetChannelData", MB_OK);
		return 0;
	}		

	return 1;
}

BOOL Rs232Out(BYTE *TTYChar, int len)
{
	int i;
	BOOL rtn;

	for (i = 0; i < len; i++) {
		rtn = ProcessTTYCharacter(MainhWnd, TTYChar[i]);
		if (!rtn)
			return FALSE;
	}

	return TRUE;
}

void DetectProc1(char *CNo)
{
	int rtn, id, i;
	char SocketBuf1[1024];
	int ChannelNo = -1;
	int SocketNo;
	int SendFlag = 0;

	SocketNo = atoi(CNo);

	if (Socket_Server_Accept(SocketNo) > 0) {
		while (1) {	// 無限ループ
			rtn = Socket_Recv(SocketNo, SocketBuf1);
			if (rtn > 0) {
				SendFlag = 0;

				if (strlen(SocketBuf1) > 3) {

					// CONNECT X 処理
					if (strncmp(SocketBuf1, "CONNECT ", 8) == 0) {
						sscanf(SocketBuf1, "%*s %d", &id);
						if (id < 1 || id > 5) {
							//sprintf(SocketBuf1, "チャンネル番号は１から５までです");
							strcpy(SocketBuf1, "ERROR");
							rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
							if (rtn < 0) 
								SocketErrorString(rtn);
							SendFlag = 1;
						} else {
							EnterCriticalSection(&G_InterfaceBox);
							id = id - 1;
							if (D_Data[id].SocketNo == 0 || D_Data[id].SocketNo == SocketNo) {
								rtn = ChangeChannel(id);
								if (rtn > 0) {
									if (ChannelNo >= 0) {
										D_Data[ChannelNo].SocketNo = 0;
										D_Data[ChannelNo].Buffer[0] = '\0';
										D_Data[ChannelNo].NewFlag = 0;
										D_Data[ChannelNo].ConnectFlag = 0;
									}
									D_Data[id].SocketNo = SocketNo;
									D_Data[id].Buffer[0] = '\0';
									D_Data[id].NewFlag = 0;
									D_Data[id].ConnectFlag = 1;
									ChannelNo = id;
									strcpy(SocketBuf1, "OK");
									rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
									if (rtn < 0) 
										SocketErrorString(rtn);
									fprintf(Testfn, "SocketNo = %d, Connect %d OK\n", SocketNo, ChannelNo);
									SendFlag = 1;
								} else {
									strcpy(SocketBuf1, "ERROR");
									rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
									if (rtn < 0) 
										SocketErrorString(rtn);
									SendFlag = 1;
								}
							} else {
								strcpy(SocketBuf1, "ERROR");
								rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
								if (rtn < 0) 
									SocketErrorString(rtn);
								SendFlag = 1;
							} 
							LeaveCriticalSection(&G_InterfaceBox);
						}
					}

					// Data
					if (strncmp(SocketBuf1, "DATA", 4) == 0) {
						if (ChannelNo >= 0) {
							Sleep(100);
							EnterCriticalSection(&G_InterfaceBox);
							ChangeChannel(ChannelNo);
							rtn = GetChannelData();
							if (D_Data[ChannelNo].ConnectFlag == 1 && D_Data[ChannelNo].SocketNo == SocketNo 
									&& D_Data[ChannelNo].NewFlag == 1) {
								rtn = Socket_Send(SocketNo, D_Data[ChannelNo].Buffer, strlen(D_Data[ChannelNo].Buffer));
								if (rtn < 0) {
									SocketErrorString(rtn);	
								}
								D_Data[ChannelNo].Buffer[0] = '\0';
								D_Data[ChannelNo].NewFlag = 0;
								SendFlag = 1;
							} else {
								strcpy(SocketBuf1, "NO DATA");
								rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
								if (rtn < 0) {
									SocketErrorString(rtn);
								}
								SendFlag = 1;
							}
							LeaveCriticalSection(&G_InterfaceBox);
						} else {
							strcpy(SocketBuf1, "ERROR");
							rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
							if (rtn < 0) 
								SocketErrorString(rtn);
							SendFlag = 1;
						}
					}

					// Close
					if (strncmp(SocketBuf1, "CLOSE", 5) == 0) {
						if (ChannelNo >= 0) {
							EnterCriticalSection(&G_InterfaceBox);
							D_Data[ChannelNo].SocketNo = 0;
							ChannelNo = -1;
							strcpy(SocketBuf1, "OK");
							rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
							if (rtn < 0) {
								SocketErrorString(rtn);
							}
							SendFlag = 1;
							LeaveCriticalSection(&G_InterfaceBox);
						} else {
							strcpy(SocketBuf1, "OK");
							rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
							if (rtn < 0) 
								SocketErrorString(rtn);
							SendFlag = 1;
						}
					}

					// Exit
					if (strncmp(SocketBuf1, "EXIT", 4) == 0) {
						EnterCriticalSection(&G_InterfaceBox);
						for (i = 0; i < 5; i++) {
							if (D_Data[i].SocketNo == SocketNo)
								D_Data[i].SocketNo = 0;
						}
						ChannelNo = -1;
						strcpy(SocketBuf1, "OK");
						rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
						if (rtn < 0) {
							SocketErrorString(rtn);
						}
						SendFlag = 1;
						LeaveCriticalSection(&G_InterfaceBox);
					}
				}
				
				if (SendFlag == 0) {
					strcpy(SocketBuf1, "ERROR");
					rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
					if (rtn < 0) {
						SocketErrorString(rtn);
					}
				}
			} else {
				if (rtn < 0) 
					SocketErrorString(rtn);

				if (SocketNo == 1) 
					SendMessage (MainhWnd, WM_CREATE1, 0, 0L) ;
				else
					SendMessage (MainhWnd, WM_CREATE2, 0, 0L) ;

				_endthread();
			}
		}
	} else {
		MessageBox(MainhWnd, "Socket Accept Error", "", MB_OK);
	}

	_endthread();
}

// Multiplexer 初期化
void MP_Init(char kiki)
{
	BYTE TTYChar[10];
	BOOL rtn;

	// 機器選択
	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 0x40;		// @
	TTYChar[2] = kiki;		// 1
	TTYChar[3] = 0x00;		
	rtn = Rs232Out(TTYChar, 4);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "MP_Init", MB_OK);
		return;
	}
	
	// バッファ メモリ クリアー （マスタ --> スレーブ）
	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 'K';		// K
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "MP_Init", MB_OK);
		return;
	}

	// バッファ メモリ クリアー （スレーブ --> マスタ）
	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 'L';		// K
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "MP_Init", MB_OK);
		return;
	}

	return;
}
