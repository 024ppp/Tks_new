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

HANDLE hInst;              /* current instance                      */
HWND MainhWnd;

char tempo[1024];
FILE *Testfn;

// Interface Box Control
CRITICAL_SECTION G_InterfaceBox;

int ClientNum;
char ServiceName[5][32];

typedef struct {
	int ConnectFlag;		// RS232C接続フラグ 0: 接続しない； 1: 接続
	char Buffer[128];		// データバッファ
	int NewFlag;			// 収録フラグ 0: データなし； 2: データあり
	int SocketNo;			// Socket接続番号 0: 接続しない； 1,2: Socket No
} RSDATA;

RSDATA D_Data[5];			// 各チャネルデータ

char MyRsBuf[1024+10];			
int MyRsLen;

// Socket 二つ
int SocketChannel[5] = {-1, -1, -1, -1, -1};	
HANDLE hThread1, hThread2, hThread3, hThread4, hThread5;
DWORD DW1, DW2;

// 環境(TTY)
char TTYPort[6];		// COM1, COM2, COM3, COM4
int TTYDataBits;		// 5, 6, 7, 8
double TTYStopBits;		// 1, 1.5, 2
char TTYParity[6];		// NONE, EVEN, ODD, MARK, SPACE
int TTYBuadRate;		// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000
char BarString[1024];

// 内部関数
void Sub_WM_Notify_WriteData(HWND hWnd);
void DetectProc1();
int ChangeChannel(int CNo);
int GetChannelData();
BOOL Rs232Out(BYTE *TTYChar, int len);
void MP_Init(char kiki);
void MP_Clear(void);
int DataDecode(int ChannelNo, char *DataBuf, double *T_Double1, double *T_Double2);

// TTY関係関数
extern LRESULT NEAR CreateTTYInfo(HWND hWnd);
extern BOOL NEAR DestroyTTYInfo(HWND hWnd);
extern BOOL NEAR OpenConnection(HWND hWnd);
extern BOOL NEAR CloseConnection(HWND hWnd);
extern int NEAR ProcessCOMMNotification(HWND hWnd, WPARAM wParam, LPARAM lParam);
extern BOOL NEAR ProcessTTYString(HWND hWnd, BYTE *bOut, int nLen );

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
	int rtn, i;

    UNREFERENCED_PARAMETER( lpCmdLine );

	// Client port name 定義
	// Set INI file name
	GetCurrentDirectory(256, DirName);
	wsprintf(DirName, "%s\\%s", DirName, "Pc3Ctrl.ini");

	// Get Client Number Port Message
	GetPrivateProfileString("MAIN", "CLIENT_NUMBER", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "Client Numberを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else {
		ClientNum = atoi(tmsg);
		if (ClientNum < 1)
			ClientNum = 1;
		if (ClientNum > 5)
			ClientNum = 5;
	}

	for (i = 0; i < ClientNum; i++) {
		sprintf(tempo, "CLIENT%d", i+1);
		GetPrivateProfileString("SERVICE", tempo, "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "Service Nameを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else
			wsprintf(ServiceName[i], "%s", tmsg);
	}

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

	for (i = 0; i < ClientNum; i++) {
		rtn = Socket_Open_Server(ServiceName[i], i+1);
		if (rtn < 0) {
			SocketErrorString(rtn);
			return FALSE;
		}
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
            0,					   /* lowest message to examine              */
            0))				       /* highest message to examine             */
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
	DWORD ThreadID;
	unsigned int cc;
	
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

			for (i = 0; i < ClientNum; i++) {
				switch (i) {
				case 0:
					// create thread 1
					hThread1 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"1",
                            0, &ThreadID );

					SetThreadPriority( hThread1, THREAD_PRIORITY_BELOW_NORMAL ) ;
					ResumeThread( hThread1 ) ;
					break;
				case 1:
					// Create Thread 2
					hThread2 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"2",
                            0, &ThreadID );

					SetThreadPriority( hThread2, THREAD_PRIORITY_BELOW_NORMAL ) ;
					ResumeThread( hThread2 ) ;
					break;
				case 2:
					// Create Thread 3
					hThread3 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"3",
                            0, &ThreadID );

					SetThreadPriority( hThread3, THREAD_PRIORITY_BELOW_NORMAL ) ;
					ResumeThread( hThread3 ) ;
					break;
				case 3:
					// Create Thread 4
					hThread4 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"4",
                            0, &ThreadID );

					SetThreadPriority( hThread4, THREAD_PRIORITY_BELOW_NORMAL ) ;
					ResumeThread( hThread4) ;
					break;
				case 4:
					// Create Thread 5
					hThread5 = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc1,
                            (LPVOID)"5",
                            0, &ThreadID );

					SetThreadPriority( hThread5, THREAD_PRIORITY_BELOW_NORMAL ) ;
					ResumeThread( hThread5) ;
					break;
				}
			}

			MyRsLen = 0;

			break;   /* WM_CREATE */

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case WM_COMMNOTIFY:	// RS232C 処理
			EnterCriticalSection(&G_InterfaceBox);
			rtn = ProcessCOMMNotification(hWnd, wParam, lParam);

			if (rtn > 1) {
				for (i = 0; i < rtn; i++) {
					if (BarString[i] != 0x0d) {
						if (MyRsLen == 0) {		// データのHeaderを探す
							if (!(BarString[i] >= '0' && BarString[i] <= '4'))
								goto Next1;		// 非Header時、スキップ
						}
						// 中断されたのHeaderをSkip
						if (MyRsLen != 0 && i == 0 && BarString[0] >= '0' && BarString[0] <= '4')
							goto Next1;

						// 正常データ
						MyRsBuf[MyRsLen] = BarString[i];
						MyRsBuf[MyRsLen+1] = '\0';
						MyRsLen++;
						if (MyRsLen > 1024) {
							MyRsLen = 0;
							MyRsBuf[0] = '\0';
						}
					} else {	// RS232Cデータ完了
						if (MyRsBuf[0] >= '0' && MyRsBuf[0] <= '4') {
							cc = MyRsBuf[0] - 0x30;
							strcpy(D_Data[cc].Buffer, MyRsBuf+1);
							if (strlen(D_Data[cc].Buffer) > 0) {
								fprintf(Testfn, "%s\n", MyRsBuf);
								D_Data[cc].NewFlag = 1;
							}
						}
						
						MyRsBuf[0] = '\0';
						MyRsLen = 0;
						GetChannelData();
					}
Next1:		
					;
				}
			}
			LeaveCriticalSection(&G_InterfaceBox);
			break;

		// Clean up.  Takes care of any open socket descriptors.
		case WM_DESTROY:

			fclose(Testfn);

			CloseConnection(hWnd);
			DestroyTTYInfo(hWnd );

			for (i = 0; i < ClientNum; i++) {
				// Close Socket
				rtn = Socket_Close(i+1);
				if (rtn < 0) {
					SocketErrorString(rtn);
					return 0;
				}
			}

			Socket_End();

			PostQuitMessage(0);
			break;

		default:                       /* Passes it on if unproccessed    */
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

// Select Channel
int ChangeChannel(int CNo)
{
	BYTE TTYChar[10];
	BOOL rtn;
	int i;

	MP_Clear();		// Clear Memory

	// ボーリング・モード１（チャネル指定）: DLE + p + 0/1 + 0/1 + 0/1 + 0/1 + 0/1
	TTYChar[0] = 0x10;				// DLE
	TTYChar[1] = 'p';				// ボーリング・モード１（チャネル指定）

	for (i = 0; i < 5; i++) {
		if (SocketChannel[0] == i || SocketChannel[1] == i || SocketChannel[2] == i ||
			SocketChannel[3] == i || SocketChannel[4] == i)
			TTYChar[2+i] = '1';				
		else 
			TTYChar[2+i] = '0';				
	}
	TTYChar[7] = 0x00;		

	// RS232CへCommandを出す
	rtn = Rs232Out(TTYChar, 8);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "ChangeChannel", MB_OK);
		return 0;
	}		

	// データリクエスト
	GetChannelData();

	return 1;
}

// データリクエスト
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

// RS232CへCommandを出す
BOOL Rs232Out(BYTE *TTYChar, int len)
{
	BOOL rtn;

	rtn = ProcessTTYString(MainhWnd, TTYChar, len);
	if (!rtn)
		return FALSE;

	return TRUE;
}

// ユーザーからのCommand 処理
// Channel 7: 材料試験機
// Channel 8: 固有抵抗率測定機
// Channel 9: リード線
void DetectProc1(char *CNo)
{
	int rtn, id, i;
	char SocketBuf1[1024];
	int ChannelNo = -1;
	int SocketNo;
	int SendFlag = 0;
	double T_Double1, T_Double2;

	// Socket No
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
						if (id < 7 || id > 11) {
							//sprintf(SocketBuf1, "チャンネル番号は１から５までです");
							strcpy(SocketBuf1, "ERROR");
							rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
							if (rtn < 0) 
								SocketErrorString(rtn);
							SendFlag = 1;
						} else {
							EnterCriticalSection(&G_InterfaceBox);
							id = id - 7;
							if (D_Data[id].SocketNo == 0 || D_Data[id].SocketNo == SocketNo) {
								SocketChannel[SocketNo-1] = id;
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
							EnterCriticalSection(&G_InterfaceBox);
							if (D_Data[ChannelNo].ConnectFlag == 1 && D_Data[ChannelNo].SocketNo == SocketNo 
									&& D_Data[ChannelNo].NewFlag == 1) {	// データあり
								rtn = DataDecode(ChannelNo, D_Data[ChannelNo].Buffer, &T_Double1, &T_Double2);
								if (rtn > 0) {
									if (ChannelNo == 0)
										sprintf(tempo, "%f", T_Double1);
									else 
										sprintf(tempo, "%f %f", T_Double1, T_Double2);
									rtn = Socket_Send(SocketNo, tempo, strlen(tempo));
									if (rtn < 0) {
										SocketErrorString(rtn);	
									}
								} else {
									strcpy(SocketBuf1, "NO DATA");
									rtn = Socket_Send(SocketNo, SocketBuf1, strlen(SocketBuf1));
									if (rtn < 0) {
										SocketErrorString(rtn);
									}
								}
								for (i = 0; i < 128; i++)
									D_Data[ChannelNo].Buffer[i] = ' ';
								D_Data[ChannelNo].Buffer[0] = '\0';
								D_Data[ChannelNo].NewFlag = 0;
								SendFlag = 1;
							} else {
								Sleep(100);		// 1/10秒
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
							SocketChannel[SocketNo-1] = -1;
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
						SocketChannel[SocketNo-1] = -1;
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
					ExitThread(GetExitCodeThread(hThread1, &DW1));
				else 
					ExitThread(GetExitCodeThread(hThread2, &DW2));
			}
		}
	} else {
		MessageBox(MainhWnd, "Socket Accept Error", "", MB_OK);
	}

	if (SocketNo == 1)
		ExitThread(GetExitCodeThread(hThread1, &DW1));
	else 
		ExitThread(GetExitCodeThread(hThread2, &DW2));
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

	// チャネルIDの付加
	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 'E';		// E
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

	if (!rtn) {
		MessageBox(MainhWnd, "送信エラー(RS232C)", "MP_Init", MB_OK);
		return;
	}

	MP_Clear();

	return;
}

// Clear Multiplexer Memory
void MP_Clear()
{
	BYTE TTYChar[10];
	BOOL rtn;

	// バッファ メモリ クリアー （スレーブ --> マスタ）
	TTYChar[0] = 0x10;		// DLE
	TTYChar[1] = 'L';		// K
	TTYChar[2] = 0x00;		
	rtn = Rs232Out(TTYChar, 3);

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

	return;
}

// データ分析
int DataDecode(int ChannelNo, char *DataBuf, double *T_Double1, double *T_Double2)
{
	char *string;
	static Channel0_ReadFlag = 0;
	char CmpString[64];

	if (ChannelNo == 1 || ChannelNo == 2) {
		// Format :  nnnnn.nnmVnn.nnnA
		if ((string = strchr(DataBuf, 'm')) == NULL)
			return 0;
		if (*(string+1) == 'V' && *(string+8) =='A') {
			*string = '\0';
			*T_Double1 = atof(DataBuf);
			*T_Double2 = atof(string+2);
			return 1;
		} else 
			return 0;

		*T_Double1 = 0.0;
		return 1;
	} else {
		if (ChannelNo == 0) {
			// Format: "1)MAX LOAD POINT"の次行
			if (Channel0_ReadFlag == 1) {
				*T_Double1 = atof(DataBuf);
				*T_Double2 = 0;
				Channel0_ReadFlag = 0;
				return 1;
			} else {
				strcpy(CmpString, " 1)MAX LOAD POINT");
				if (strncmp(DataBuf, CmpString, strlen(CmpString)) == 0) 
					Channel0_ReadFlag = 1;
				*T_Double1 = 0.0;
				*T_Double2 = 0.0;
				return 0;
			}
		}
	}
	return 0;
}
