/******************************************************************************
				Copyright (C) 1999 NKK Unics Corporation
						All Right Reserved

	System Name	:	トライス殿向け 検査システム
	                中間検査 (Shared Memory , RS232C) PC1用
	File Name	:	Pc1Ctrl2.c
    Create		:	1999.09.28
	Contents	:	Rs232C (I/O) control
	Writen by	:	周 欽銘(NKK Unics)
	Version		:	1.0
-------------------------------------------------------------------------------
	Date		:	1999.11.08
	Updated by	:	Zhou Qinming
	Contents:	:	専用Share Memory 1: Read	(SHARE_TRIS1)
					専用Share Memory 2: Write	(SHARE_TRIS2)
******************************************************************************/

#include <windows.h>       /* required for all Windows applications */
#include <winsock.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>

// application header file
#include "Pc12Ctrl.h"         /* specific to this program              */

#define WM_COM1   WM_USER + 4010  // COM1 要求データ送信メッセージ
#define WM_COM2   WM_USER + 4011  // COM1 要求データ送信メッセージ

HANDLE hInst;              /* current instance                      */
HWND MainhWnd;

int ComNum;			// 設定ファイルからＲｓ232Ｃポート数

char tempo[1024];
char SharedBuff[BUFFERSIZE];

FILE *Testfn;

int AcceptFlag;
int CurrentNo;

// 環境(TTY)
char TTYPort[2][6];		// COM1, COM2, COM3, COM4
int TTYDataBits[2];		// 5, 6, 7, 8
double TTYStopBits[2];		// 1, 1.5, 2
char TTYParity[2][6];		// NONE, EVEN, ODD, MARK, SPACE
int TTYBuadRate[2];		// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000
char BarString[1024];
int InputFlag;
unsigned long BarTime;

// 内部関数
void Sub_WM_Notify_WriteData(HWND hWnd);
void DetectProc();
int ChangeChannel(int CNo);
int GetChannelData();
void MP_Init(char kiki);
BOOL Rs232Out(int CNo, BYTE *TTYChar, int len);
BOOL MyIsDigital(char *string);

// TTY関係関数
extern LRESULT NEAR CreateTTYInfo(int CNo, HWND hWnd);
extern BOOL NEAR DestroyTTYInfo(int CNo, HWND hWnd);
extern BOOL NEAR OpenConnection(int CNo, HWND hWnd);
extern BOOL NEAR CloseConnection(int Cno, HWND hWnd);
extern int NEAR ProcessCOMMNotification(int CNo, HWND hWnd, WPARAM wParam, LPARAM lParam);
extern BOOL NEAR ProcessTTYCharacter(int CNo, HWND hWnd, BYTE bOut );
extern BOOL NEAR ProcessTTYString(int CNo, HWND hWnd, BYTE *bOut, int nLen );

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

    UNREFERENCED_PARAMETER( lpCmdLine );

	// Client port name 定義
	// Set INI file name
	GetCurrentDirectory(256, DirName);
	wsprintf(DirName, "%s\\%s", DirName, "Pc12ctrl.ini");

	// Rs232Cポート数
	// Get TTY Port Message
	GetPrivateProfileString("MAIN", "COMNUM", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Port数を定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else {
		ComNum = atoi(tmsg);
		if (ComNum < 1)
			ComNum = 1;
		if (ComNum > 2)
			ComNum = 2;
	}

	// COM1
	// Get TTY Port Message
	GetPrivateProfileString("COM1", "PORT", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Port Nameを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		wsprintf(TTYPort[0], "%s", tmsg);

	// Get TTY DataBits Message
	GetPrivateProfileString("COM1", "DATABITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Databitsを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else
		TTYDataBits[0] = atoi(tmsg);

	// Get TTY StopBits Message
	GetPrivateProfileString("COM1", "STOPBITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Stopbitsを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		TTYStopBits[0] = atof(tmsg);

	// Get TTY Parity Message
	GetPrivateProfileString("COM1", "PARITY", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Parityを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		wsprintf(TTYParity[0], "%s", tmsg);

	// Get TTY Buad Rate Message
	GetPrivateProfileString("COM1", "BUADRATE", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY BuadRateを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	} else 
		TTYBuadRate[0] = atoi(tmsg);

	if (ComNum == 2) {
		// COM2 
		// Get TTY Port Message
		GetPrivateProfileString("COM2", "PORT", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "TTY Port Nameを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else
			wsprintf(TTYPort[1], "%s", tmsg);

		// Get TTY DataBits Message
		GetPrivateProfileString("COM2", "DATABITS", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "TTY Databitsを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else
			TTYDataBits[1] = atoi(tmsg);

		// Get TTY StopBits Message
		GetPrivateProfileString("COM2", "STOPBITS", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "TTY Stopbitsを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else 
			TTYStopBits[1] = atof(tmsg);

		// Get TTY Parity Message
		GetPrivateProfileString("COM2", "PARITY", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "TTY Parityを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else 
			wsprintf(TTYParity[1], "%s", tmsg);

		// Get TTY Buad Rate Message
		GetPrivateProfileString("COM2", "BUADRATE", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "TTY BuadRateを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else 
			TTYBuadRate[1] = atoi(tmsg);
	}

	if (!hPrevInstance)                  /* Other instances of app running? */
        if (!InitApplication(hInstance)) /* Initialize shared things        */
            return (FALSE);              /* Exits if unable to initialize   */

    /*
    *   Perform initializations that apply to a specific instance
    */
    if (!InitInstance(hInstance, nCmdShow))
        return (FALSE);

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
        "TRIS ： 中間検査(PC1)",		/* Text for window title bar.         */
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
	int nNumber;
	static char MyComBuf[256];
	static int MyComBufLen;
	static char MyComBuf2[256];
	static int MyComBufLen2;
	char *Tstring;
	double T_Double;
	int i, j;

	switch (message) {

		case WM_CREATE:

			GetCurrentDirectory(sizeof(tempo), tempo);
			sprintf(SharedBuff, "%s\\LogPC1.dat", tempo);

			Testfn = fopen(SharedBuff, "w+");
			if (Testfn == NULL) {
				MessageBox(hWnd, "Create Log Data file error", "", MB_OK);
				return 0;
			}

			// Create TTY info for COM1 (Rs232C) communication
			if (CreateTTYInfo(0, hWnd) <= 0)
				return 0;

			if (!OpenConnection(0, hWnd)) {
				int TTYFlag = 0;
				int retry = 0;
					
				// 最大５回接続
				while (retry < 5 && TTYFlag == 0) {
					Sleep(1000);
					rtn = OpenConnection(0, hWnd);
					if (rtn >= 1)
						TTYFlag = 1;
					retry++;
				}
				if (TTYFlag == 0) {
					MessageBox(hWnd, "COM #1 Connection failed", "TTY", MB_OK);
					return 0;					
				} 
			}

			if (ComNum == 2) {
				// Create TTY info for COM2 (Rs232C) communication
				if (CreateTTYInfo(1, hWnd) <= 0)
					return 0;

				if (!OpenConnection(1, hWnd)) {
					int TTYFlag = 0;
					int retry = 0;
					
					// 最大５回接続
					while (retry < 5 && TTYFlag == 0) {
						Sleep(1000);
						rtn = OpenConnection(1, hWnd);
						if (rtn >= 1)
							TTYFlag = 1;
						retry++;
					}
					if (TTYFlag == 0) {
						MessageBox(hWnd, "COM #2 Connection failed", "TTY", MB_OK);
						return 0;					
					} 
				}
			}

			// ShareMemory Create
			rtn = SharedMemory_Create(hWnd, "SHARE_TRIS1", 1);
			if (rtn < 0)
				SharedMemoryErrorString(rtn);

			// ShareMemory Create
			rtn = SharedMemory_Create(hWnd, "SHARE_TRIS2", 2);
			if (rtn < 0)
				SharedMemoryErrorString(rtn);

			AcceptFlag = -1;
			MyComBufLen = 0;
			MyComBufLen2 = 0;

			break;   /* WM_CREATE */

		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				ShowWindow(hWnd, SW_MINIMIZE);
			break;

		case WM_COM2:	// RS232C 処理(COM2)	電子天秤 Channel 6
			rtn = ProcessCOMMNotification(1, hWnd, wParam, lParam);
			if (AcceptFlag == 1 && rtn > 0 && CurrentNo == 6) {
				BarString[rtn] = '\0';

				// 0X0D：終了フラグ
				strncpy(MyComBuf2+MyComBufLen2, BarString, rtn);
				MyComBufLen2 = MyComBufLen2 + rtn;
				MyComBuf2[MyComBufLen2] = '\0';
				MyComBuf2[MyComBufLen2+1] = '\0';

				if (strchr(MyComBuf2, 0x0D) != NULL) {
					fprintf(Testfn, "Ori_%s\n", BarString);
					fprintf(Testfn, "MyBuf_%s\n", MyComBuf2);
					
					j = 0;
					for (i = 0; i < strlen(MyComBuf2); i++) {
						if (MyComBuf2[i] == '+' || MyComBuf2[i] == '-') {
							j = i;
							i = strlen(MyComBuf2)+1;
						}
					}

					//if (MyComBuf2[0] == '+') 				
					//	T_Double = atof(MyComBuf2 + 1);
					//else
					//	T_Double = atof(MyComBuf2);
					T_Double = atof(MyComBuf2+j+1);

					sprintf(BarString, "%.4f", T_Double);
					if (CurrentNo == 6) 
						nNumber = SharedMemory_Write(2, 0, BarString, strlen(BarString));
					MyComBuf2[0] = '\0';
					MyComBufLen2 = 0;
					fprintf(Testfn, "%s\n", BarString);
				}
			}
			break;

		case WM_COM1:	// RS232C 処理 (COM1)
			rtn = ProcessCOMMNotification(0, hWnd, wParam, lParam);
			if (AcceptFlag == 1 && rtn > 0) {

				BarString[rtn] = '\0';

				// 0X0D：終了フラグ
				strncpy(MyComBuf+MyComBufLen, BarString, rtn);
				MyComBufLen = MyComBufLen + rtn;
				MyComBuf[MyComBufLen] = '\0';

				if (strchr(BarString, 0x0D) != NULL) {
					if ((Tstring = strchr(MyComBuf, 0x02)) != NULL) {	// STX
						if (strchr(Tstring+2, 0x02) == NULL) {
							if (MyIsDigital(Tstring+2) && MyComBufLen > 3) {
								T_Double = atof(Tstring+2);
								sprintf(MyComBuf, "%.4f", T_Double);
								if (CurrentNo >= 1 && CurrentNo <= 5)
									nNumber = SharedMemory_Write(2, 0, MyComBuf, strlen(MyComBuf));
								MyComBufLen = 0;
								fprintf(Testfn, "%s\n", MyComBuf);
								ChangeChannel(CurrentNo);
							} else { // 無効データ
								MyComBuf[0] = '\0';
								MyComBufLen = 0;
								ChangeChannel(CurrentNo);
							}
						}
					} else {
						MyComBufLen = 0;
						if (strchr(MyComBuf, 0x04) != NULL) {	// EOT
							GetChannelData();		// 1999.10.14
						} else {
							if (strchr(MyComBuf, 0x06) != NULL) {	// ACK
								//sprintf(tempo, "OK");
								//nNumber = SharedMemory_Write(2, 0, tempo, strlen(tempo));
								GetChannelData();		// 1999.10.14
							} 
						}
					}
				}
			}
			break;

		case WM_Notify_WriteData:
			Sub_WM_Notify_WriteData(hWnd);
			break;

		// Clean up.  Takes care of any open socket descriptors.
		case WM_DESTROY:
			fclose(Testfn);

			AcceptFlag = 0;
			Sleep(1000);
			
			// COM1 Close
			CloseConnection(0, hWnd);
			DestroyTTYInfo(0, hWnd );
		
			if (ComNum == 2) {
				// COM2 Close
				CloseConnection(1, hWnd);
				DestroyTTYInfo(1, hWnd );
			}

			// SharedMemory Close
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
	int nNumber, id;

	nNumber = SharedMemory_Read(1, SharedBuff);
	if (nNumber > 0) {
		if (strncmp(SharedBuff, "CONNECT ", 8) == 0) {
			sscanf(SharedBuff, "%*s %d", &id);
			if (id < 1 || id > 6 || (id == 6 && ComNum == 1)) {
				//sprintf(tempo, "チャンネル番号は１から６までです");
				sprintf(tempo, "C_ERROR");
				nNumber = SharedMemory_Write(2, 0, tempo, strlen(tempo));
				return;
			}
			nNumber = ChangeChannel(id);
			if (nNumber <= 0) {
				//sprintf(tempo, "チャンネル番号を切り替え失敗！");
				sprintf(tempo, "ERROR");
				nNumber = SharedMemory_Write(2, 0, tempo, strlen(tempo));
				return;
			} else {
				//sprintf(tempo, "チャンネル番号(%d)に切り替えました！", id);
				sprintf(tempo, "OK");
				nNumber = SharedMemory_Write(2, 0, tempo, strlen(tempo));
				fprintf(Testfn, "%s\n", tempo);
				CurrentNo = id;
				AcceptFlag = 1;
			}
		}
		if (strncmp(SharedBuff, "CLOSE", 5) == 0) {
			AcceptFlag = -1;
		}
		if (strncmp(SharedBuff, "EXIT", 4) == 0) {
			AcceptFlag = 0;
			Sleep(1000);
			PostQuitMessage(0);
		}
	} else
		if (nNumber < 0)
			SharedMemoryErrorString(nNumber);
}

// チャンネルを選択
int ChangeChannel(int CNo)
{
	BYTE TTYChar[10];
	BOOL rtn;

	if (CNo >= 1 && CNo <= 5) {	// Connecter
		TTYChar[0] = 0x04;				// EOT
		TTYChar[1] = 'C';				// Cancel
		TTYChar[2] = 0x0D;				// CR
		rtn = Rs232Out(0, TTYChar, 3);

		if (!rtn) {
			MessageBox(MainhWnd, "送信エラー(RS232C)", "ChangeChannel", MB_OK);
			return 0;
		}		
		
		TTYChar[0] = 0x04;				// EOT
		TTYChar[1] = 0x30 + CNo;		// Port No. of Connecter
		TTYChar[2] = 0x0D;				// CR
		rtn = Rs232Out(0, TTYChar, 3);

		if (!rtn) {
			MessageBox(MainhWnd, "送信エラー(RS232C)", "ChangeChannel", MB_OK);
			return 0;
		}		
	}

	return 1;
}

// Read Commandを出す
int GetChannelData()
{
	BYTE TTYChar[10];
	BOOL rtn;

	if (CurrentNo >= 1 && CurrentNo <= 5) {	// Get data of Channel 1 -- 5 of Connecter
		// Connecterへ
		TTYChar[0] = 0x05;		// ENQ
		TTYChar[1] = 0x0D;		// CR
		rtn = Rs232Out(0, TTYChar, 2);

		if (!rtn) {
			MessageBox(MainhWnd, "送信エラー(RS232C)", "GetChannelData", MB_OK);
			return 0;
		}			
		Sleep(70);	// Wait Time
	}

	return 1;
}

// ＲＳ２３２へ出力
BOOL Rs232Out(int CNo, BYTE *TTYChar, int len)
{
	BOOL rtn;

	rtn = ProcessTTYString(CNo, MainhWnd, TTYChar, len);
	if (!rtn)
		return FALSE;

	return TRUE;
}

// 数字判断
BOOL MyIsDigital(char *string)
{
	int i, len;
	int DFlag = 0;

	len = strlen(string) - 1;
	for (i = 0; i < len; i++) 
		if (!((string[i] >= '0' && string[i] <= '9') || string[i] == '.' || string[i] == ' ' ||
			string[i] == '+' || string[i] == '-'))
			return FALSE;
		else
			if (string[i] >= '0' && string[i] <= '9')
				DFlag = 1;

	if (DFlag == 1)
		return TRUE;
	else
		return FALSE;
}
