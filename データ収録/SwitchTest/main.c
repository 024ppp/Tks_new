/************************************************************************/
/*  Program     : IFDUMMY												*/
/*  File        : main.c												*/
/*  Description : Simulator of I/F BOX									*/
/*  Revision    : 1.00													*/
/*  Date        : 2007.11.20 (JFE Mie Tech Service co.ltd)				*/
/************************************************************************/
/*==[Include]===========================================================*/
#include <windows.h> 
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h> 
#include "resource.h" 
//#include "tty.h"
/*==[Constant Definition]===============================================*/
#define UM_ENDCREATE	(WM_USER+101)
#define UM_DATAREAD		(WM_USER+102)

/*==[ProtoType]=========================================================*/
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM); 
int ReadIniInfo(void);
// TTY関係関数
extern LRESULT NEAR CreateTTYInfo(HWND hWnd);
extern BOOL NEAR DestroyTTYInfo(HWND hWnd);
extern BOOL NEAR OpenConnection(HWND hWnd);
extern BOOL NEAR CloseConnection(HWND hWnd);
extern int NEAR ProcessCOMMNotification(HWND hWnd, WPARAM wParam, LPARAM lParam);
extern BOOL NEAR ProcessTTYString(HWND hWnd, BYTE *bOut, int nLen );

/*==[Global Variable]===================================================*/
// 環境(TTY)
char TTYPort[6];		// COM1, COM2, COM3, COM4
char TTYDataBits;		// 5, 6, 7, 8
double TTYStopBits;		// 1, 1.5, 2
char TTYParity[6];		// NONE, EVEN, ODD, MARK, SPACE
int TTYBuadRate;		// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000
char TTYFlow[10];		// NONE, DTRDSR, RTSCTS, HARDWARE, XONXOFF, SOFTWARE
char BarString[128];
int IsOpen;


/*==[Function]==========================================================*/
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) 
{ 
	HWND		hwnd;
	MSG			msg;
	WNDCLASSEX	winc;

	/* Initialize Window Class Structure	*/
	ZeroMemory(&winc,sizeof(WNDCLASSEX));
	winc.cbSize			= sizeof( WNDCLASSEX);
	winc.style			= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= DlgProc;
	winc.cbClsExtra		= 0;
	winc.cbWndExtra		= DLGWINDOWEXTRA;
	winc.hInstance		= hCurInst;
	winc.hIcon			= LoadIcon(hCurInst , MAKEINTRESOURCE(IDI_ICON_MAIN));
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= "CHSWITCHEST";

	/* Regist Class			*/
	if (!RegisterClassEx(&winc)) return -1;

	/* Create Dialog		*/
	hwnd = CreateDialog(hCurInst , MAKEINTRESOURCE(IDD_DLG_MAIN) , NULL , NULL);
	if (hwnd == NULL){
		/* On Error		*/
		/* Error Description From Error No	*/
		LPTSTR lpBuffer;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			LANG_USER_DEFAULT,
			(LPTSTR)&lpBuffer,
			0,
			NULL );
		/* Display Error	*/
		MessageBox(hwnd, lpBuffer, "error message", MB_ICONHAND|MB_OK);
	    LocalFree(lpBuffer);		
		return -1;
	}

	/* Message Loop		*/
	while(GetMessage(&msg , NULL , 0 , 0)) {
		if( IsDialogMessage(hwnd,&msg) == FALSE ){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;

} 

/* Window Procedure For Main Dialog	*/
LRESULT CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) 
{ 
	int					rtn;
	static int			ch = 0;
	BYTE TTYChar[10];

	switch (msg) { 
	case WM_INITDIALOG:
		break; 
	case WM_COMMAND: 
		switch (wp) { 
		case IDOK: 
//			if (MessageBox( hWnd, (LPCTSTR)"Are You Sure To Exit?", (LPCTSTR)"Exit", 
//							MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL) { 
//				break; 
//			}
			PostMessage(hWnd,WM_CLOSE,0,0);
			break; 
		case IDC_BTN_CHGCH:
			ch = ch % 5 + 1;

			TTYChar[0] = 0x04;				// EOT
			TTYChar[1] = 'C';				// Cancel
			TTYChar[2] = 0x0D;				// CR
			ProcessTTYString(hWnd, TTYChar, 3 );
			//Sleep(100);
			TTYChar[0] = 0x04;				// EOT
			TTYChar[1] = 0x30 + ch;		// Port No. of Connecter
			TTYChar[2] = 0x0D;				// CR
			ProcessTTYString(hWnd, TTYChar, 3 );

			break;

		case IDC_BTN_DATA:

			TTYChar[0] = 0x05;				// EOT
			TTYChar[1] = 0x0D;				// CR
			ProcessTTYString(hWnd, TTYChar, 2 );

			break;
		}
		break;
	case UM_DATAREAD:
		TTYChar[0] = 0x04;				// EOT
		TTYChar[1] = 'C';				// Cancel
		TTYChar[2] = 0x0D;				// CR
		ProcessTTYString(hWnd, TTYChar, 3 );
		//Sleep(100);
		TTYChar[0] = 0x04;				// EOT
		TTYChar[1] = 0x30 + ch;		// Port No. of Connecter
		TTYChar[2] = 0x0D;				// CR
		ProcessTTYString(hWnd, TTYChar, 3 );
		break;
	case WM_CREATE:
		IsOpen = 0;
		/* Read Board Name Form Ini File	*/
		if( ReadIniInfo() != 0 ){
			PostMessage(hWnd,WM_CLOSE,0,0);
			break;
		}

		// Create TTY info for COMM3 (Bar code) communication
		if (CreateTTYInfo(hWnd) <= 0){
			PostMessage(hWnd,WM_CLOSE,0,0);
			break;
		}

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
				MessageBox(hWnd, "COM Connection failed", "Proc5 TTY", MB_OK);
				PostMessage(hWnd,WM_CLOSE,0,0);
				break;
			} 
		}
		IsOpen = 1;
		PostMessage(hWnd,UM_ENDCREATE,0,0);
		break;
	case WM_COMMNOTIFY:	// BarCode Read 処理
		rtn = ProcessCOMMNotification(hWnd, wp, lp);
		if (BarString[0] != '\0' && rtn > 1) {
			if( strchr(BarString,0x02) != NULL ){
				SetDlgItemText(hWnd, IDC_EDT_DATA, (LPCTSTR)BarString+2);
				SendMessage(hWnd,UM_DATAREAD,NULL,NULL);
			}
		}
//		Sleep(500);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case UM_ENDCREATE:
		break;
	case WM_DESTROY:
		if( IsOpen ){
			CloseConnection(hWnd);
			DestroyTTYInfo(hWnd );
		}
		PostQuitMessage(0);
		break;
	} 
	return DefDlgProc(hWnd,msg,wp,lp);
} 

int ReadIniInfo(void)
{
	char DirName[MAX_PATH], tmsg[16];

	/* Create Reading Ini File Path	*/
	GetCurrentDirectory(MAX_PATH,DirName);
	strcat(DirName,"\\SwitchTest.ini");

	// Get TTY Port Message
	GetPrivateProfileString("TTY", "PORT", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Port Nameを定義して下さい", "ReadINIFile", MB_OK);
		return -1;
	} else
		wsprintf(TTYPort, "%s", tmsg);

	// Get TTY DataBits Message
	GetPrivateProfileString("TTY", "DATABITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Databitsを定義して下さい", "ReadINIFile", MB_OK);
		return -2;
	} else
		TTYDataBits = atoi(tmsg);

	// Get TTY StopBits Message
	GetPrivateProfileString("TTY", "STOPBITS", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Stopbitsを定義して下さい", "ReadINIFile", MB_OK);
		return -3;
	} else 
		TTYStopBits = atof(tmsg);

	// Get TTY Parity Message
	GetPrivateProfileString("TTY", "PARITY", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Parityを定義して下さい", "ReadINIFile", MB_OK);
		return -4;
	} else 
		wsprintf(TTYParity, "%s", tmsg);

	// Get TTY Buad Rate Message
	GetPrivateProfileString("TTY", "BUADRATE", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY BuadRateを定義して下さい", "ReadINIFile", MB_OK);
		return -5;
	} else 
		TTYBuadRate = atoi(tmsg);

	// Get TTY Flow Control Message
	GetPrivateProfileString("TTY", "FLOWCTRL", "Not Define", tmsg, 16, DirName);
	if (strncmp(tmsg, "Not Define", 10) == 0) {
		MessageBox(NULL, "TTY Flow Controlを定義して下さい", "ReadINIFile", MB_OK);
		return -4;
	} else 
		wsprintf(TTYFlow, "%s", tmsg);

	return 0;

}


