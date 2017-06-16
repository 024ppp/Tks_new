/******************************************************************************
				Copyright (C) 1997 NKK Unics Corporation
						All Right Reserved

	System Name	:	トライスＦＡターミナル
    File Name	:	Misc.c
    Create		:	1997.10.1
	Contents	:	
	Writen by	:	Zhou Qinming (周 欽銘）(NKK Unics)
	Version		:	1.0
******************************************************************************/
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

// 環境（Socket)
extern char Tserver[32];		// server name (hosts)
extern char Tservice[6][32];	// port name (services)

// 環境（ORACLE)
extern char DBUserID[32];		// Oracle User ID
extern char DBPassWord[32];		// Oracle PassWord
extern char DBName[32];			// DB Services Name (SQL*Net Easy Configuration)

// 環境（TTY)
extern char TTYPort[6];			// COM1, COM2, COM3, COM4 ....
extern int TTYDataBits;			// 5, 6, 7, 8
extern double TTYStopBits;		// 1, 1.5, 2	
extern char TTYParity[6];		// NONE, EVEN, ODD, MARK, SPACE
extern int TTYBuadRate;			// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000

// 機械名称、処理区分
extern char MacName1[3];		// 機械名１(K1, K3, K5 ...)
extern char MacName2[3];		// 機械名２(K2, K4, K6 ...)
extern int ProType;				// １：前処理
								// ２：配合

//
//   FUNCTION: CenterWindow(HWND, HWND)
//
//   PURPOSE: Centers one window over another. 
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
// 		This functionwill center one window over another ensuring that 
//		the placement of the window is within the 'working area', meaning 
//		that it is both within the display limits of the screen, and not 
//		obscured by the tray or other framing elements of the desktop.
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
	RECT    rChild, rParent, rWorkArea;
	int     wChild, hChild, wParent, hParent;
	int     xNew, yNew;
	BOOL 	bResult;

	// Get the Height and Width of the child window
	GetWindowRect (hwndChild, &rChild);
	wChild = rChild.right - rChild.left;
	hChild = rChild.bottom - rChild.top;

	// Get the Height and Width of the parent window
	GetWindowRect (hwndParent, &rParent);
	wParent = rParent.right - rParent.left;
	hParent = rParent.bottom - rParent.top;

	// Get the limits of the 'workarea'
	bResult = SystemParametersInfo(
		SPI_GETWORKAREA,	// system parameter to query or set
		sizeof(RECT),
		&rWorkArea,
		0);
	if (!bResult) {
		rWorkArea.left = rWorkArea.top = 0;
		rWorkArea.right = GetSystemMetrics(SM_CXSCREEN);
		rWorkArea.bottom = GetSystemMetrics(SM_CYSCREEN);
	}

	// Calculate new X position, then adjust for workarea
	xNew = rParent.left + ((wParent - wChild) /2);
	if (xNew < rWorkArea.left) {
		xNew = rWorkArea.left;
	} else if ((xNew+wChild) > rWorkArea.right) {
		xNew = rWorkArea.right - wChild;
	}

	// Calculate new Y position, then adjust for workarea
	yNew = rParent.top  + ((hParent - hChild) /2);
	if (yNew < rWorkArea.top) {
		yNew = rWorkArea.top;
	} else if ((yNew+hChild) > rWorkArea.bottom) {
		yNew = rWorkArea.bottom - hChild;
	}

	// Set it, and return
	return SetWindowPos (hwndChild, NULL, xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// read INI file's message
// ININame: INI file name
// typeflag: 0: Socket, Oracle, TTY;  1: Oracle, TTY; 2: Socket, Oracle, TTY, 機械名、処理区分
// ServiceNum: 0: Service; 1: Service1; 2: Service2; 3: Service3
int ReadINIFile(char *ININame, int typeflag, int ServiceNum) 
{
char DirName[256], tmsg[16];

	// Set INI file name
//	GetCurrentDirectory(256, DirName);
//	wsprintf(DirName, "%s\\%s", DirName, ININame);
	strcpy(DirName, ININame);

	if (typeflag != 1) {
		// Get SOCKET host Message
		GetPrivateProfileString("SOCKET", "HOST", "Not Define", Tserver, 32, DirName);
		if (strncmp(Tserver, "Not Define", 10) == 0) {
			MessageBox(NULL, "Socket hostを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		}

		// Get SOCKET host Message
		GetPrivateProfileString("SOCKET", "SERVICE", "Not Define", Tservice[0], 32, DirName);
		if (strncmp(Tservice[0], "Not Define", 10) == 0) {
			MessageBox(NULL, "Socket serviceを定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		}

		if (ServiceNum >= 1) {
			GetPrivateProfileString("SOCKET", "SERVICE1", "Not Define", Tservice[1], 32, DirName);
			if (strncmp(Tservice[1], "Not Define", 10) == 0) {
				MessageBox(NULL, "Socket serviceを定義して下さい", "ReadINIFile", MB_OK);
				return FALSE;
			}
		}

		if (ServiceNum >= 2) {
			GetPrivateProfileString("SOCKET", "SERVICE2", "Not Define", Tservice[2], 32, DirName);
			if (strncmp(Tservice[2], "Not Define", 10) == 0) {
				MessageBox(NULL, "Socket serviceを定義して下さい", "ReadINIFile", MB_OK);
				return FALSE;
			}
		}

		if (ServiceNum >= 3) {
			GetPrivateProfileString("SOCKET", "SERVICE3", "Not Define", Tservice[3], 32, DirName);
			if (strncmp(Tservice[3], "Not Define", 10) == 0) {
				MessageBox(NULL, "Socket serviceを定義して下さい", "ReadINIFile", MB_OK);
				return FALSE;
			}
		}
	}

	// Get DB UserID Message
	GetPrivateProfileString("DATABASE", "USERID", "Not Define", DBUserID, 32, DirName);
	if (strncmp(DBUserID, "Not Define", 10) == 0) {
		MessageBox(NULL, "DATABASE UserIDを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	}

	// Get DB Password Message
	GetPrivateProfileString("DATABASE", "PASSWORD", "Not Define", DBPassWord, 32, DirName);
	if (strncmp(DBPassWord, "Not Define", 10) == 0) {
		MessageBox(NULL, "DATABASE Passwordを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
	}

	// Get DB Name Message
	GetPrivateProfileString("DATABASE", "DBNAME", "Not Define", DBName, 32, DirName);
	if (strncmp(DBName, "Not Define", 10) == 0) {
		MessageBox(NULL, "DATABASE Nameを定義して下さい", "ReadINIFile", MB_OK);
		return FALSE;
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

	if (typeflag == 2) { // 機械名、処理区分
		GetPrivateProfileString("TYPE", "NAME1", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "機械名１を定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else {
			strncpy(MacName1, tmsg, 2);
			MacName1[2] = '\0';
		}

		GetPrivateProfileString("TYPE", "NAME2", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "機械名２を定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else {
			strncpy(MacName2, tmsg, 2);
			MacName2[2] = '\0';
		}

		GetPrivateProfileString("TYPE", "TYPE", "Not Define", tmsg, 16, DirName);
		if (strncmp(tmsg, "Not Define", 10) == 0) {
			MessageBox(NULL, "処理区分を定義して下さい", "ReadINIFile", MB_OK);
			return FALSE;
		} else {
			ProType = atoi(tmsg);
		}
	}

	return TRUE;
}

// Warning Beep
// nType: 0: ﾋﾟ
//        1: ﾋﾟｯﾋﾟ
//        2: ﾋﾟｰ
void PlayBeep(int nType)
{
unsigned long itime;
int i;

	if (nType == 0) {	// ﾋﾟ
//		MessageBeep(MB_OK);
//		MessageBeep(0xFFFFFFFF);
		for (i = 0; i < 100; i++) 
			Beep(0, 0);
//		itime = GetCurrentTime();
//		while ((GetCurrentTime() - itime) < 100) {
//			Beep(50,50);
//			MessageBeep(0xFFFFFFFF);
//		}
		return;
	}

	if (nType == 1) {	// ﾋﾟｯﾋﾟ
//		MessageBeep(0xFFFFFFFF);
//		itime = GetCurrentTime();
//		while ((GetCurrentTime() - itime) < 100) {
//			MessageBeep(0xFFFFFFFF);
//		}
		for (i = 0; i < 50; i++) 
			Beep(0, 0);
		itime = GetCurrentTime();
		while ((GetCurrentTime() - itime) < 50) {
			Sleep(10);
		}
//		MessageBeep(0xFFFFFFFF);
//		itime = GetCurrentTime();
//		while ((GetCurrentTime() - itime) < 100) {
//			MessageBeep(0xFFFFFFFF);
//		}
		for (i = 0; i < 50; i++) 
			Beep(0, 0);
		return;
	}

	if (nType == 2) {	// ﾋﾟｰ
		for (i = 0; i < 150; i++) 
			Beep(0, 0);
//		MessageBeep(0xFFFFFFFF);
//		itime = GetCurrentTime();
//		while ((GetCurrentTime() - itime) < 1000) {
//			MessageBeep(0xFFFFFFFF);
//		}
		return;
	}
}

// 月の日数を計算
// yearr: 4桁 （"1998", "2000" ...)
// monthh: 2桁 ("01", "02" ...)
int month_len( yearr, monthh )
char *yearr ;
char *monthh ;
{
    static int len[] = {
                         31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31
                        } ;

    if (atoi(monthh) == 2 ) {
       if ( atoi( yearr )%4 == 0 && atoi(yearr)%100 != 0 || atoi(yearr)%400 == 0) return (29) ;
       else return (28) ;
    }
    else {
       return(len[atoi(monthh)-1]) ;
    }
}

// 二つ日付の日数を計算
// y1, m1, d1: 最初日付
// y2, m2, d2: 最終日付
int caldays(y1,m1,d1,y2,m2,d2)
int y1,m1,d1;
int y2,m2,d2;
{

    char yy[5],mm[3];
    int  i,j,len1;
	int	 days;

    if( y1==y2){ // 同じ年
		if( m1==m2 ){ // 同じ月
            days = d2-d1+1;
			return days;
		} else { // 月違う
            for( i = m1; i<=m2; i++){
                yy[0] = '\0';
                mm[0] = '\0';
                sprintf( yy,"%04d", y1) ;
                sprintf( mm,"%02d", i) ;
                len1 = month_len(yy,mm) ;
 
                if( i== m1 ) // 最初月
                     days = len1-d1+1;
                else if( i==m2 ) // 最終月
                     days = days+d2;
                else
                     days = days+len1 ;
            }
			return days;
       }
    }else{ // 年違う
       for( i=y1; i<=y2; i++ ){
           if( i== y1 ){ // 最初年計算
               for( j = m1; j<=12; j++ ){
                      yy[0] = '\0';
                      mm[0] = '\0';
                      sprintf( yy,"%04d", y1) ;
                      sprintf( mm,"%02d", j) ;
                      len1 = month_len(yy,mm) ;

                      if( j== m1 )
                           days = len1-d1+1;
                      else
                           days = days+len1 ;
               }
           } else if( i== y2 ) { // 最終年計算
               for( j = 1; j<=m2; j++ ){
                      yy[0] = '\0';
                      mm[0] = '\0';
                      sprintf( yy,"%04d", y2) ;
                      sprintf( mm,"%02d", j) ;
                      len1 = month_len(yy,mm) ;

                      if( j== m2 )
                           days = days+d2;
                      else
                           days = days+len1 ;
               }
           } else // 普通年計算
               days = days+365;
        }
    }
}

// 日付を計算
// Input : 
//		開始日付: y1, m1, d1
//		日数：days
// Output:
//		終了日付：y2, m2, d2
void NewDate(int y1, int m1, int d1, int days, int *y2, int *m2, int *d2)
{
	int len1;
	char t1[16], t2[16];

	*y2 = y1;
	*m2 = m1;
	*d2 = d1;

START1:
	sprintf(t1, "%04d", *y2);
	sprintf(t2, "%02d", *m2);
	len1 = month_len(t1, t2);
	len1 = len1 - *d2 + 1;

	if (len1 <= 0)
		return;

	if (days >= len1) {
		*m2 = *m2 + 1;
		*d2 = 1;
		days = days - len1;
		if (*m2 > 12) {
			*y2 = *y2 + 1;
			*m2 = 1;
		}
	} else { // len1 < days
		*d2 = *d2 + days;
		days = 0;
	}

	if (days <= 0)
		return;
	else
		goto START1;
}

// 時間計算(分）
int CalTime(int year1, int mon1, int day1, int hour1, int min1, int year2, int mon2, int day2, int hour2, int min2)
{
	int days, min;

	days = caldays(year1,mon1,day1,year2,mon2,day2);
	min = (days-1) * 1440; // 60 * 24 * days

	min = min + (hour2 - hour1)*60 + (min2 - min1);

	return min;
}

// 時間計算（秒）
int CalTimeSec(int year1, int mon1, int day1, int hour1, int min1, int sec1, int year2, int mon2, int day2, int hour2, int min2, int sec2)
{
	int days, min, sec;

	days = caldays(year1,mon1,day1,year2,mon2,day2);
	min = (days-1) * 1440; // 60 * 24 * days

	min = min + (hour2 - hour1)*60 + (min2 - min1);

	sec = min * 60 + sec2 - sec1;

	return sec;
}

// get current date and current time
void Z_GetDateTime(int *year, int *mon, int *day, int *hour, int *min, int *sec)
{
time_t ltime;
struct tm *today;

	time(&ltime);
	today = localtime(&ltime);

	*year = today->tm_year + 1900;
	*mon = today->tm_mon + 1;
	*day = today->tm_mday;

	*hour = today->tm_hour;
	*min = today->tm_min;
	*sec = today->tm_sec;

	return;
}

