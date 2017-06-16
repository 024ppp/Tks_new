/******************************************************************************
				Copyright (C) 1997 NKK Unics Corporation
						All Right Reserved

	System Name	:	トライス殿向け 検査システム
	                中間検査 Shared Memory(Server) , Socket(Client) PC3,PC4用
	File Name	:	ShareSocket.c
    Create		:	1999.09.30
	Contents	:	Rs232C (I/O) control
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
-------------------------------------------------------------------------------
	Date		:	1999.11.09
	Updated by	:	Zhou Qinming
	Contents:	:	専用Share Memory 1: Read	(SHARE_TRIS1)
					専用Share Memory 2: Write	(SHARE_TRIS2)
******************************************************************************/

#include <windows.h>       /* required for all Windows applications */
#include <winsock.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>
#include <process.h>       /* for _beginthread                      */

// application header file
#include "ShareSocket.h"         /* specific to this program              */

HANDLE hInst;              /* current instance                      */
HWND MainhWnd;

char tempo[1024];
char SharedBuff[BUFFERSIZE];
char CommandBuff[BUFFERSIZE];

// Interface Box Control
CRITICAL_SECTION G_InterfaceBox;

int ReadFlag;

// 内部関数
void Sub_WM_Notify_WriteData(HWND hWnd);
void DetectProc();
int ChangeChannel(int CNo);
int GetChannelData();

HANDLE hThread;

char HostName[16], ServiceName[16], MemoryName[16];

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
	wsprintf(DirName, "%s\\%s", DirName, "ShareSocket.ini");

	// Host Name
	GetPrivateProfileString("SOCKET", "HOST", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "Socket Hostを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		strcpy(HostName, tmsg);

	// Service Name
	GetPrivateProfileString("SOCKET", "SERVICE", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "Socket Serviceを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		strcpy(ServiceName, tmsg);

//	// ShareMemory Name
//	GetPrivateProfileString("SHAREMEMORY", "NAME", "Not Define", tmsg, 16, DirName);
//	if (strncmp(tmsg, "Not Define", 10) == 0) {
//		MessageBox(NULL, "シェアメモリの名前を定義して下さい", "ReadINIFile", MB_OK);
//		return FALSE;
//	} else 
//		strcpy(MemoryName, tmsg);

	// Socket 
	rtn = Socket_Init();
	if (rtn < 0) {
		SocketErrorString(rtn);
		return FALSE;
	}

	rtn = Socket_Open_Client(ServiceName, HostName, 1);
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
        "TRIS：中間検査(PC3,4)",		/* Text for window title bar.         */
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
	int rtn;
	DWORD ThreadID;

	switch (message) {

		case WM_CREATE:
			// ShareMemory Create
			rtn = SharedMemory_Create(hWnd, "SHARE_TRIS1", 1);
			if (rtn < 0)
				SharedMemoryErrorString(rtn);

			rtn = SharedMemory_Create(hWnd, "SHARE_TRIS2", 2);
			if (rtn < 0)
				SharedMemoryErrorString(rtn);

			ReadFlag = 0;

			// create thread
			//_beginthread(DetectProc, 0, NULL);
			hThread = CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
     						0, 
                            (LPTHREAD_START_ROUTINE) DetectProc,
                            (LPVOID)NULL,
                            0, &ThreadID );

			SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
			ResumeThread( hThread ) ;
			break;   /* WM_CREATE */

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case WM_Notify_WriteData:
			Sub_WM_Notify_WriteData(hWnd);
			break;

		// Clean up.  Takes care of any open socket descriptors.
		case WM_DESTROY:
			Socket_Close(1);

			Socket_End();

			SharedMemory_Close(1);
			SharedMemory_Close(2);

			PostQuitMessage(0);
			break;

		default:                       /* Passes it on if unproccessed    */
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}

// シェアメモリ受信
void Sub_WM_Notify_WriteData(HWND hWnd)
{
	int nNumber;

	nNumber = SharedMemory_Read(1, SharedBuff);
	if (nNumber > 0) {
		while (ReadFlag == 1)
			;
		EnterCriticalSection(&G_InterfaceBox);
		strcpy(CommandBuff, SharedBuff);
		ReadFlag = 1;
		LeaveCriticalSection(&G_InterfaceBox);
	} 
}

// ユーザーからCommand処理
void DetectProc()
{
	int rtn;
	int CommandID;
	int DataQuery = 0;
	DWORD DW;

	while (1) {	// 無限ループ
		if (ReadFlag == 1) {
			CommandID = 0;

			EnterCriticalSection(&G_InterfaceBox);
			// Send Command 
			rtn = Socket_Send(1, CommandBuff, strlen(CommandBuff));
			if (rtn < 0) {
				SocketErrorString(rtn);
				goto End1;
			}

			if (strncmp(CommandBuff, "CONNECT", 7) == 0) 
				CommandID = 1;

			if (strncmp(CommandBuff, "CLOSE", 5) == 0) 
				CommandID = 2;

			if (strncmp(CommandBuff, "EXIT", 4) == 0) 
				CommandID = 3;

			// 応答を待ち
			rtn = Socket_Recv(1, CommandBuff);
			if (rtn <= 0) {
				SocketErrorString(rtn);
				goto End1;
			}
			
			if (strncmp(CommandBuff, "OK", 2) == 0 && CommandID == 1)
				DataQuery = 1;

			if (strncmp(CommandBuff, "OK", 2) == 0 && CommandID == 2)
				DataQuery = 0;

			if (strncmp(CommandBuff, "OK", 2) == 0 && CommandID == 3) {
				
				SendMessage (MainhWnd, WM_CLOSE, 0, 0L) ;

				goto End1;
			}
			
			// APPへ送る
			SharedMemory_Write(2, 0, CommandBuff, strlen(CommandBuff));

			ReadFlag = 0;
			LeaveCriticalSection(&G_InterfaceBox);
		} else {
			if (DataQuery == 1) {
				rtn = Socket_Send(1, "DATA", 4);
				if (rtn < 0) {
					SocketErrorString(rtn);
					goto End1;
				}

				// 応答を待ち
				rtn = Socket_Recv(1, tempo);
				if (rtn <= 0) {
					SocketErrorString(rtn);
					goto End1;
				}
			
				if (strncmp(tempo, "NO DATA", 7) != 0) 		// APPへ送る
					SharedMemory_Write(2, 0, tempo, strlen(tempo));
				else
					Sleep(50);
			} else
				Sleep(50);
		}
	}

End1:
	ExitThread(GetExitCodeThread(hThread, &DW));
}

