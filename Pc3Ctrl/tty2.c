/******************************************************************************
				Copyright (C) 1997 NKK Unics Corporation
						All Right Reserved

	System Name	:	トライス殿向け 検査システム
	File Name	:	TTY2.c
	Create		:	1999.09.28
	Contents	:	RS323 communication
	Writen by	:	Zhou Qinming (周 欽銘）(NKK Unics)
	Version		:	1.0
******************************************************************************/
#include "tty2.h"

// barCode入力文字列
extern char BarString[128];

// 環境（TTY)
extern char TTYPort[2][6];			// COM1, COM2, COM3, COM4 ....
extern int TTYDataBits[2];			// 5, 6, 7, 8
extern double TTYStopBits[2];		// 1, 1.5, 2	
extern char TTYParity[2][6];		// NONE, EVEN, ODD, MARK, SPACE
extern int TTYBuadRate[2];			// 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 128000, 256000
#if 1	// 2011.06.08 Y.Sano Add start
extern char TTYFlow[2][10];		// NONE, DTRDSR, RTSCTS, HARDWARE, XONXOFF, SOFTWARE
#endif	// 2011.06.08 Y.Sano Add start
NPTTYINFO  npTTYInfo[2] ;

DWORD FAR PASCAL CommWatchProc1( LPSTR lpData );

//---------------------------------------------------------------------------
//  LRESULT NEAR CreateTTYInfo( HWND hWnd )
//
//  Description:
//     Creates the tty information structure and sets
//     menu option availability.  Returns -1 if unsuccessful.
//
//  Parameters:
//     HWND  hWnd
//        Handle to main window.
//
//  Win-32 Porting Issues:
//     - Needed to initialize TERMWND( npTTYInfo ) for secondary thread.
//     - Needed to create/initialize overlapped structures used in reads &
//       writes to COMM device.
//
//  History:   Date       Author      Comment
//             10/18/91   BryanW      Pulled from tty window proc.
//              1/13/92   BryanW      Fixed bug with invalid handle
//                                    caused by WM_SIZE sent by
//                                    ResetTTYScreen().
//
//---------------------------------------------------------------------------

LRESULT NEAR CreateTTYInfo(int CNo, HWND hWnd )
{
//   NPTTYINFO   npTTYInfo ;

   if (NULL == (npTTYInfo[CNo] = (NPTTYINFO) LocalAlloc( LPTR, sizeof( TTYINFO ) )))
      return ( (LRESULT) -1 ) ;

   // initialize TTY info structure

   COMDEV( npTTYInfo[CNo] )        = 0 ;
   CONNECTED( npTTYInfo[CNo] )     = FALSE ;
   CURSORSTATE( npTTYInfo[CNo] )   = CS_HIDE ;
   LOCALECHO( npTTYInfo[CNo] )     = FALSE ;
   AUTOWRAP( npTTYInfo[CNo] )      = TRUE ;
   
   if (strncmp(TTYPort[CNo], "COM1", 4) == 0)
	   PORT( npTTYInfo[CNo] )      = 1 ;				
   if (strncmp(TTYPort[CNo], "COM2", 4) == 0)
	   PORT( npTTYInfo[CNo] )      = 2 ;
   if (strncmp(TTYPort[CNo], "COM3", 4) == 0)
	   PORT( npTTYInfo[CNo] )      = 3 ;
   if (strncmp(TTYPort[CNo], "COM4", 4) == 0)
	   PORT( npTTYInfo[CNo] )      = 4 ;

   switch (TTYBuadRate[CNo]) {
		case 110:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_110 ;
			break;
		case 300:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_300 ;
			break;
		case 600:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_600 ;
			break;
		case 1200:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_1200 ;
			break;
		case 2400:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_2400 ;
			break;
		case 4800:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_4800 ;
			break;
		case 9600:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_9600 ;
			break;
		case 14400:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_14400 ;
			break;
		case 19200:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_19200 ;
			break;
		case 38400:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_38400 ;
			break;
		case 56000:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_56000 ;
			break;
		case 128000:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_128000 ;
			break;
		case 256000:
			BAUDRATE( npTTYInfo[CNo] )      = CBR_256000 ;
			break;
   }
   BYTESIZE( npTTYInfo[CNo] )      = TTYDataBits[CNo] ;
   FLOWCTRL( npTTYInfo[CNo] )      = FC_RTSCTS ;
/*
#if 1	// 2011.06.08 Y.Sano Add start
   if (strncmp(TTYFlow[CNo], "NONE", 4) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_NONE ;
   if (strncmp(TTYFlow[CNo], "DTRDSR", 6) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_DTRDSR ;
   if (strncmp(TTYFlow[CNo], "RTSCTS", 6) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_RTSCTS ;
   if (strncmp(TTYFlow[CNo], "HARDWARE", 8) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_HARDWARE ;
   if (strncmp(TTYFlow[CNo], "XONXOFF", 7) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_XONXOFF ;
   if (strncmp(TTYFlow[CNo], "SOFTWARE", 8) == 0)
	   FLOWCTRL( npTTYInfo[CNo] )     = FC_XONXOFF ;
#endif	// 2011.06.08 Y.Sano Add end
*/
   if (strncmp(TTYParity[CNo], "NONE", 4) == 0)
	   PARITY( npTTYInfo[CNo] )    = NOPARITY;				
   if (strncmp(TTYParity[CNo], "EVEN", 4) == 0)
	   PARITY( npTTYInfo[CNo] )    = EVENPARITY;
   if (strncmp(TTYParity[CNo], "ODD", 3) == 0)
	   PARITY( npTTYInfo[CNo] )    = ODDPARITY;
   if (strncmp(TTYParity[CNo], "MARK", 4) == 0)
	   PARITY( npTTYInfo[CNo] )    = MARKPARITY;
   if (strncmp(TTYParity[CNo], "SPACE", 4) == 0)
	   PARITY( npTTYInfo[CNo] )    = SPACEPARITY;
   if (TTYStopBits[CNo] == 1)
	   STOPBITS( npTTYInfo[CNo] )  = ONESTOPBIT ;
   if (TTYStopBits[CNo] == 1.5)
	   STOPBITS( npTTYInfo[CNo] )  = ONE5STOPBITS ;
   if (TTYStopBits[CNo] == 2)
	   STOPBITS( npTTYInfo[CNo] )  = TWOSTOPBITS ;

   XONXOFF( npTTYInfo[CNo] )       = FALSE ;
   XSIZE( npTTYInfo[CNo] )         = 0 ;
   YSIZE( npTTYInfo[CNo] )         = 0 ;
   XSCROLL( npTTYInfo[CNo] )       = 0 ;
   YSCROLL( npTTYInfo[CNo] )       = 0 ;
   XOFFSET( npTTYInfo[CNo] )       = 0 ;
   YOFFSET( npTTYInfo[CNo] )       = 0 ;
   COLUMN( npTTYInfo[CNo] )        = 0 ;
   ROW( npTTYInfo[CNo] )           = 0 ;
   HTTYFONT( npTTYInfo[CNo] )      = NULL ;
   FGCOLOR( npTTYInfo[CNo] )       = RGB( 0, 0, 0 ) ;
   USECNRECEIVE( npTTYInfo[CNo] )  = TRUE ;
   DISPLAYERRORS( npTTYInfo[CNo] ) = TRUE ;

#ifdef WIN32

  TERMWND( npTTYInfo[CNo] ) =       hWnd ;

   // create I/O event used for overlapped reads / writes

   READ_OS( npTTYInfo[CNo] ).hEvent = CreateEvent( NULL,    // no security
                                              TRUE,    // explicit reset req
                                              FALSE,   // initial event reset
                                              NULL ) ; // no name
   if (READ_OS( npTTYInfo[CNo] ).hEvent == NULL)
   {
      //LocalFree( npTTYInfo[CNo] ) ;
      return ( -1 ) ;
   }
   WRITE_OS( npTTYInfo[CNo] ).hEvent = CreateEvent( NULL,    // no security
                                               TRUE,    // explicit reset req
                                               FALSE,   // initial event reset
                                               NULL ) ; // no name
   if (NULL == WRITE_OS( npTTYInfo[CNo] ).hEvent)
   {
      CloseHandle( READ_OS( npTTYInfo[CNo] ).hEvent ) ;
      //LocalFree( npTTYInfo[CNo] ) ;
      return ( -1 ) ;
   }

   // create "posted notification" event

   POSTEVENT( npTTYInfo[CNo] ) = CreateEvent( NULL,     // no security
                                         TRUE,     // manual reset
                                         TRUE,     // initial event is set
                                         NULL ) ;  // no name

   if (POSTEVENT( npTTYInfo[CNo] ) == NULL)
   {
      CloseHandle( READ_OS( npTTYInfo[CNo] ).hEvent ) ;
      CloseHandle( WRITE_OS( npTTYInfo[CNo] ).hEvent ) ;
      //LocalFree( npTTYInfo ) ;
      return ( -1 ) ;
   }
#endif

   // clear screen space
   //_fmemset( SCREEN( npTTYInfo ), ' ', MAXROWS * MAXCOLS ) ;

   // setup default font information

   LFTTYFONT( npTTYInfo[CNo] ).lfHeight =         9 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfWidth =          0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfEscapement =     0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfOrientation =    0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfWeight =         0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfItalic =         0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfUnderline =      0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfStrikeOut =      0 ;
   LFTTYFONT( npTTYInfo[CNo] ).lfCharSet =        OEM_CHARSET ;
   LFTTYFONT( npTTYInfo[CNo] ).lfOutPrecision =   OUT_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo[CNo] ).lfClipPrecision =  CLIP_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo[CNo] ).lfQuality =        DEFAULT_QUALITY ;
   LFTTYFONT( npTTYInfo[CNo] ).lfPitchAndFamily = FIXED_PITCH | FF_MODERN ;
   lstrcpy( LFTTYFONT( npTTYInfo[CNo] ).lfFaceName, "FixedSys" ) ;

   // set TTYInfo handle before any further message processing.

//   SETNPTTYINFO( hWnd, npTTYInfo ) ;
/* 
   // reset the character information, etc.
   ResetTTYScreen( hWnd, npTTYInfo ) ;

   hMenu = GetMenu( hWnd ) ;
   EnableMenuItem( hMenu, IDM_DISCONNECT,
                   MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
   EnableMenuItem( hMenu, IDM_CONNECT, MF_ENABLED | MF_BYCOMMAND ) ;
*/
//   npTTYInfo = GETNPTTYINFO( hWnd );

   return ( (LRESULT) TRUE ) ;

} // end of CreateTTYInfo()

//---------------------------------------------------------------------------
//  BOOL NEAR DestroyTTYInfo( HWND hWnd )
//
//  Description:
//     Destroys block associated with TTY window handle.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to clean up event objects created during initialization.
//
//  History:   Date       Author      Comment
//              5/ 8/91   BryanW      Wrote it.
//              6/15/92   BryanW      Ported to Win-32.
//
//---------------------------------------------------------------------------

BOOL NEAR DestroyTTYInfo(int CNo, HWND hWnd )
{
//   NPTTYINFO npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   // force connection closed (if not already closed)

   if (CONNECTED( npTTYInfo[CNo] ))
      CloseConnection(CNo, hWnd ) ;

#ifdef WIN32
   // clean up event objects

   CloseHandle( READ_OS( npTTYInfo[CNo] ).hEvent ) ;
   CloseHandle( WRITE_OS( npTTYInfo[CNo] ).hEvent ) ;
   CloseHandle( POSTEVENT( npTTYInfo[CNo] ) ) ;
#endif

   DeleteObject( HTTYFONT( npTTYInfo[CNo] ) ) ;

   //LocalFree( npTTYInfo ) ;
   return ( TRUE ) ;

} // end of DestroyTTYInfo()
/*
//---------------------------------------------------------------------------
//  BOOL NEAR ResetTTYScreen( HWND hWnd, NPTTYINFO npTTYInfo )
//
//  Description:
//     Resets the TTY character information and causes the
//     screen to resize to update the scroll information.
//
//  Parameters:
//     NPTTYINFO  npTTYInfo
//        pointer to TTY info structure
//
//  History:   Date       Author      Comment
//             10/20/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR ResetTTYScreen( HWND hWnd, NPTTYINFO npTTYInfo )
{
   HDC         hDC ;
   TEXTMETRIC  tm ;
   RECT        rcWindow ;

   if (NULL == npTTYInfo)
      return ( FALSE ) ;

   if (NULL != HTTYFONT( npTTYInfo ))
      DeleteObject( HTTYFONT( npTTYInfo ) ) ;

   HTTYFONT( npTTYInfo ) = CreateFontIndirect( &LFTTYFONT( npTTYInfo ) ) ;

   hDC = GetDC( hWnd ) ;
   SelectObject( hDC, HTTYFONT( npTTYInfo ) ) ;
   GetTextMetrics( hDC, &tm ) ;
   ReleaseDC( hWnd, hDC ) ;

   XCHAR( npTTYInfo ) = tm.tmAveCharWidth  ;
   YCHAR( npTTYInfo ) = tm.tmHeight + tm.tmExternalLeading ;

   // a slimy hack to force the scroll position, region to
   // be recalculated based on the new character sizes

   GetWindowRect( hWnd, &rcWindow ) ;
   SendMessage( hWnd, WM_SIZE, SIZENORMAL,
                (LPARAM) MAKELONG( rcWindow.right - rcWindow.left,
                                   rcWindow.bottom - rcWindow.top ) ) ;

   return ( TRUE ) ;

} // end of ResetTTYScreen()
*/
//---------------------------------------------------------------------------
//  BOOL NEAR SetTTYFocus( HWND hWnd )
//
//  Description:
//     Sets the focus to the TTY window also creates caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------
BOOL NEAR SetTTYFocus(int CNo, HWND hWnd )
{
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo[CNo] ) && (CURSORSTATE( npTTYInfo[CNo] ) != CS_SHOW))
   {
      CreateCaret( hWnd, NULL, XCHAR( npTTYInfo[CNo] ), YCHAR( npTTYInfo[CNo] ) ) ;
      ShowCaret( hWnd ) ;
      CURSORSTATE( npTTYInfo[CNo] ) = CS_SHOW ;
   }
   MoveTTYCursor(CNo, hWnd ) ;
   return ( TRUE ) ;

} // end of SetTTYFocus()

//---------------------------------------------------------------------------
//  BOOL NEAR KillTTYFocus( HWND hWnd )
//
//  Description:
//     Kills TTY focus and destroys the caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR KillTTYFocus(int CNo, HWND hWnd )
{
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo[CNo]) && (CURSORSTATE( npTTYInfo[CNo] ) != CS_HIDE))
   {
      HideCaret( hWnd ) ;
      DestroyCaret() ;
      CURSORSTATE( npTTYInfo[CNo] ) = CS_HIDE ;
   }
   return ( TRUE ) ;

} // end of KillTTYFocus()

//---------------------------------------------------------------------------
//  BOOL NEAR MoveTTYCursor( HWND hWnd )
//
//  Description:
//     Moves caret to current position.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR MoveTTYCursor(int CNo, HWND hWnd )
{
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   if (CONNECTED( npTTYInfo[CNo] ) && (CURSORSTATE( npTTYInfo[CNo] ) & CS_SHOW))
      SetCaretPos( (COLUMN( npTTYInfo[CNo] ) * XCHAR( npTTYInfo[CNo] )) -
                   XOFFSET( npTTYInfo[CNo] ),
                   (ROW( npTTYInfo[CNo] ) * YCHAR( npTTYInfo[CNo] )) -
                   YOFFSET( npTTYInfo[CNo] ) ) ;
   
   return ( TRUE ) ;

} // end of MoveTTYCursor()

//---------------------------------------------------------------------------
//  BOOL NEAR ProcessCOMMNotification( HWND hWnd,
//                                     WPARAM wParam, LPARAM lParam ) ;
//
//  Description:
//     Processes the WM_COMMNOTIFY message from the COMM.DRV.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WPARAM wParam
//        specifes the device (nCid)
//
//     LPARAM lParam
//        LOWORD contains event trigger
//        HIWORD is NULL
//
//  Win-32 Porting Issues:
//     - Function was constrained by WORD and LONG declarations.
//     - Processing under Win-32 is much simpler and additionally
//       requires the "posted message" flag to be cleared.
//
//  History:   Date       Author      Comment
//              5/10/91   BryanW      Wrote it.
//             10/18/91   BryanW      Updated to verify the event.
//              6/15/92   BryanW      Removed WORD and LONG constraints.
//              6/15/92   BryanW      Ported to Win-32.
//
//---------------------------------------------------------------------------

int NEAR ProcessCOMMNotification(int CNo, HWND hWnd, WPARAM wParam, LPARAM lParam )
{
   int        nLength,i , actLength;
   BYTE       abIn[ MAXBLOCK + 1] ;
//   NPTTYINFO  npTTYInfo ;
   MSG        msg ;

   actLength = 0;

  // if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
  //    return ( FALSE ) ;

   if (!CONNECTED( npTTYInfo[CNo] ))
      return ( FALSE ) ;

#ifdef WIN32
   // verify that it is a COMM event sent by our thread

   if ((CN_EVENT & LOWORD( lParam )) != CN_EVENT)
      return ( FALSE ) ;

   // We loop here since it is highly likely that the buffer
   // can been filled while we are reading this block.  This
   // is especially true when operating at high baud rates
   // (e.g. >= 9600 baud).

	do {
		if (nLength = ReadCommBlock(CNo, hWnd, (LPSTR) abIn, MAXBLOCK )) {
			// 最初と最後文字チェックする（0x02と0x03などを除く)
//			if (abIn[0] >= 0x01) {
				for (i = 0; i <= nLength-1; i++) {
//					if (abIn[i] < 0x20)
//						i = nLength;
//					else {
						BarString[actLength] = abIn[i];
						BarString[actLength+1] = '\0';
						actLength++;
//					}
				}
/*			} else {
				for (i = 1; i <= nLength-1; i++) {
					if (abIn[i] < 0x20)
						i = nLength;
					else {
						BarString[actLength] = abIn[i];
						BarString[actLength+1] = '\0';
						actLength++;
					}
				}
			}
*/		 
			 abIn[0] = '\0';
		     // force a paint

			Sleep(1);	// 150
		}
	} while (!PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE) || (nLength > 0)) ;

   // clear our "posted notification" flag

   SetEvent( POSTEVENT( npTTYInfo[CNo] ) ) ;
#else
   if (!USECNRECEIVE( npTTYInfo[CNo] ))
   {
      // verify that it is a COMM event specified by our mask

      if (CN_EVENT & LOWORD( lParam ) != CN_EVENT)
         return ( FALSE ) ;

      // For Windows 3.1, rested reset the event word so we are notified
      // when the next event occurs

      GetCommEventMask( COMDEV( npTTYInfo[CNo] ), EV_RXCHAR ) ;

      // We loop here since it is highly likely that the buffer
      // can been filled while we are reading this block.  This
      // is especially true when operating at high baud rates
      // (e.g. >= 9600 baud).

      do
      {
         if (nLength = ReadCommBlock(CNo, hWnd, (LPSTR) abIn, MAXBLOCK ))
         {
            // WriteTTYBlock( hWnd, (LPSTR) abIn, nLength ) ;

            // force a paint

            UpdateWindow( hWnd ) ;
         }
      }
      while (!PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE) || (nLength > 0)) ;
   }
   else
   {
      // verify that it is a receive event

      if (CN_RECEIVE & LOWORD( lParam ) != CN_RECEIVE)
         return ( FALSE ) ;

      do
      {
         if (nLength = ReadCommBlock(CNo, hWnd, (LPSTR) abIn, MAXBLOCK ))
         {
            // WriteTTYBlock( hWnd, (LPSTR) abIn, nLength ) ;

            // force a paint

            UpdateWindow( hWnd ) ;
         }
      }
      while ((!PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE )) ||
            (ComStat.cbInQue >= MAXBLOCK)) ;
   }
#endif

   if (actLength > 0)
	   return (actLength);
   else
       return ( TRUE ) ;

} // end of ProcessCOMMNotification()

//---------------------------------------------------------------------------
//  BOOL NEAR ProcessTTYCharacter( HWND hWnd, BYTE bOut )
//
//  Description:
//     This simply writes a character to the port and echos it
//     to the TTY screen if fLocalEcho is set.  Some minor
//     keyboard mapping could be performed here.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE bOut
//        byte from keyboard
//
//  History:   Date       Author      Comment
//              5/11/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR ProcessTTYCharacter(int CNo, HWND hWnd, BYTE bOut )
{
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   if (!CONNECTED( npTTYInfo[CNo] ))
      return ( FALSE ) ;

   WriteCommByte(CNo, hWnd, bOut ) ;
   if (LOCALECHO( npTTYInfo[CNo] ))
      WriteTTYBlock(CNo, hWnd, &bOut, 1 ) ;

   return ( TRUE ) ;

} // end of ProcessTTYCharacter()

BOOL NEAR ProcessTTYString(int CNo, HWND hWnd, BYTE *bOut, int nLen )
{
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   if (!CONNECTED( npTTYInfo[CNo] ))
      return ( FALSE ) ;

   WriteCommString(CNo, hWnd, bOut, nLen ) ;
   if (LOCALECHO( npTTYInfo[CNo] ))
      WriteTTYBlock(CNo, hWnd, bOut, nLen ) ;

   return ( TRUE ) ;

} // end of ProcessTTYCharacter()

//---------------------------------------------------------------------------
//  BOOL NEAR OpenConnection( HWND hWnd )
//
//  Description:
//     Opens communication port specified in the TTYINFO struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - OpenComm() is not supported under Win-32.  Use CreateFile()
//       and setup for OVERLAPPED_IO.
//     - Win-32 has specific communication timeout parameters.
//     - Created the secondary thread for event notification.
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR OpenConnection(int CNo, HWND hWnd )
{            
   char       szPort[ 15 ], szTemp[ 10 ] ;
   BOOL       fRetVal ;
   HCURSOR    hOldCursor, hWaitCursor ;
//   HMENU      hMenu ;
//   NPTTYINFO  npTTYInfo ;

#ifdef WIN32
   HANDLE        hCommWatchThread ;
   DWORD         dwThreadID ;
   COMMTIMEOUTS  CommTimeOuts ;
#endif

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   // show the hourglass cursor
   hWaitCursor = LoadCursor( NULL, IDC_WAIT ) ;
   hOldCursor = SetCursor( hWaitCursor ) ;

#ifdef WIN32
   // HACK!  This checks for the PORT number defined by
   // the combo box selection.  If it is greater than the
   // maximum number of ports, assume TELNET.

   if (PORT( npTTYInfo[CNo] ) > MAXPORTS)
      lstrcpy( szPort, "\\\\.\\TELNET" ) ;
   else
   {
      // load the COM prefix string and append port number
   
      //LoadString( GETHINST( hWnd ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;
      wsprintf(szTemp, "%s", "COM");
	   wsprintf( szPort, "%s%d", (LPSTR) szTemp, PORT( npTTYInfo[CNo] ) ) ;
   }
#else
   // load the COM prefix string and append port number

   LoadString( GETHINST( hWnd ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;
   wsprintf( szPort, "%s%d", (LPSTR) szTemp, PORT( npTTYInfo[CNo] ) ) ;
#endif

   // open COMM device

#ifdef WIN32
   if ((COMDEV( npTTYInfo[CNo] ) =
      CreateFile( szPort, GENERIC_READ | GENERIC_WRITE,
                  0,                    // exclusive access
                  NULL,                 // no security attrs
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL | 
                  FILE_FLAG_OVERLAPPED, // overlapped I/O
                  NULL )) == (HANDLE) -1 )
      return ( FALSE ) ;
   else
   {
      // get any early notifications

      SetCommMask( COMDEV( npTTYInfo[CNo] ), EV_RXCHAR ) ;

      // setup device buffers

      SetupComm( COMDEV( npTTYInfo[CNo] ), 4096, 4096 ) ;

      // purge any information in the buffer

      // HACK! HACK! Not really needed... the buffers are allocated
      // and clear.  If TELNET is active, the buffer will contain
      // immediate data.

//      PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
//                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

      // set up for overlapped non-blocking I/O

      CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.ReadTotalTimeoutConstant = 0 ;
      CommTimeOuts.WriteTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.WriteTotalTimeoutConstant = 5000 ;
      SetCommTimeouts( COMDEV( npTTYInfo[CNo] ), &CommTimeOuts ) ;
   }
#else
   if ((COMDEV( npTTYInfo[CNo] ) = OpenComm( szPort, RXQUEUE, TXQUEUE )) < 0)
      return ( FALSE ) ;
#endif

   fRetVal = SetupConnection(CNo, hWnd ) ;

   if (fRetVal)
   {
      CONNECTED( npTTYInfo[CNo] ) = TRUE ;

#ifdef WIN32
      // In the case of Win32, we create a secondary thread
      // to watch for an event.
		if (CNo == 0) 
			hCommWatchThread =
                      CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
                                    0, 
                                    (LPTHREAD_START_ROUTINE) CommWatchProc,
                                    (LPVOID) "0",
                                    0, &dwThreadID );
		else 
			hCommWatchThread =
                      CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
                                    0, 
                                    (LPTHREAD_START_ROUTINE) CommWatchProc1,
                                    (LPVOID) "1",
                                    0, &dwThreadID );
		if (NULL == hCommWatchThread) 
//      if (NULL == (hCommWatchThread =
//                    CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
//                                    0, 
//                                    (LPTHREAD_START_ROUTINE) CommWatchProc,
//                                    (LPVOID) npTTYInfo[CNo],
//                                    0, &dwThreadID )))
      {
         CONNECTED( npTTYInfo[CNo] ) = FALSE ;
         CloseHandle( COMDEV( npTTYInfo[CNo] ) ) ;
         fRetVal = FALSE ;
      }
      else
      {
         THREADID( npTTYInfo[CNo] ) = dwThreadID ;
         HTHREAD( npTTYInfo[CNo] ) = hCommWatchThread ;

         // Adjust thread priority
        
         SetThreadPriority( hCommWatchThread, THREAD_PRIORITY_BELOW_NORMAL ) ;	//1999.10.14
         ResumeThread( hCommWatchThread ) ;

         // assert DTR

         EscapeCommFunction( COMDEV( npTTYInfo[CNo] ), SETDTR ) ;

         SetTTYFocus(CNo, hWnd ) ;
/*
         hMenu = GetMenu( hWnd ) ;
         EnableMenuItem( hMenu, IDM_DISCONNECT,
                        MF_ENABLED | MF_BYCOMMAND ) ;
         EnableMenuItem( hMenu, IDM_CONNECT,
                        MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
*/
         // kick TELNET into operation

         ProcessCOMMNotification(CNo, hWnd, (WPARAM) COMDEV( npTTYInfo[CNo] ), 
                                  MAKELONG( CN_EVENT, 0 )) ;

      }
#else
      // Under Windows 3.1, we set up notifications from COMM.DRV

      if (!USECNRECEIVE( npTTYInfo[CNo] ))
      {
         // In this case we really are only using the notifications
         // for the received characters - it could be expanded to
         // cover the changes in CD or other status lines.

         SetCommEventMask( COMDEV( npTTYInfo[CNo] ), EV_RXCHAR ) ;

         // Enable notifications for events only.
      
         // NB:  This method does not use the specific
         // in/out queue triggers.

         EnableCommNotification( COMDEV( npTTYInfo[CNo] ), hWnd, -1, -1 ) ;
      }
      else
      {
         // Enable notification for CN_RECEIVE events.

         EnableCommNotification( COMDEV( npTTYInfo[CNo] ), hWnd, MAXBLOCK, -1 ) ;
      }

      // assert DTR

      EscapeCommFunction( COMDEV( npTTYInfo[CNo] ), SETDTR ) ;

      SetTTYFocus(CNo, hWnd ) ;
/*
      hMenu = GetMenu( hWnd ) ;
      EnableMenuItem( hMenu, IDM_DISCONNECT,
                      MF_ENABLED | MF_BYCOMMAND ) ;
      EnableMenuItem( hMenu, IDM_CONNECT,
                      MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
*/
#endif
   }
   else
   {
      CONNECTED( npTTYInfo[CNo] ) = FALSE ;

#ifdef WIN32
      CloseHandle( COMDEV( npTTYInfo[CNo] ) ) ;
#else
      CloseComm( COMDEV( npTTYInfo[CNo] ) ) ;
#endif
   }

   // restore cursor

   SetCursor( hOldCursor ) ;

   return ( fRetVal ) ;

} // end of OpenConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR SetupConnection( HWND hWnd )
//
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Win-32 requires a slightly different processing of the DCB.
//       Changes were made for configuration of the hardware handshaking
//       lines.
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

BOOL NEAR SetupConnection(int CNo, HWND hWnd )
{
   BOOL       fRetVal ;
   BYTE       bSet ;
   DCB        dcb ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

#ifdef WIN32
   dcb.DCBlength = sizeof( DCB ) ;
#endif

   GetCommState( COMDEV( npTTYInfo[CNo] ), &dcb ) ;

   dcb.BaudRate = BAUDRATE( npTTYInfo[CNo] ) ;
   dcb.ByteSize = BYTESIZE( npTTYInfo[CNo] ) ;
   dcb.Parity = PARITY( npTTYInfo[CNo] ) ;
   dcb.StopBits = STOPBITS( npTTYInfo[CNo] ) ;

   // setup hardware flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo[CNo] ) & FC_DTRDSR) != 0) ;
#ifdef WIN32
   dcb.fOutxDsrFlow = bSet ;
   if (bSet)
      dcb.fDtrControl = DTR_CONTROL_HANDSHAKE ;
   else
      dcb.fDtrControl = DTR_CONTROL_ENABLE ;
#else
   dcb.fOutxDsrFlow = dcb.fDtrflow = bSet ;
   dcb.DsrTimeout = (bSet) ? 30 : 0 ;
#endif

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo[CNo] ) & FC_RTSCTS) != 0) ;
#ifdef WIN32
   dcb.fOutxCtsFlow = bSet ;
   if (bSet)
      dcb.fRtsControl = RTS_CONTROL_HANDSHAKE ;
   else
      dcb.fRtsControl = RTS_CONTROL_ENABLE ;
#else
   dcb.fOutxCtsFlow = dcb.fRtsflow = bSet ;
   dcb.CtsTimeout = (bSet) ? 30 : 0 ;
#endif

   // setup software flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo[CNo] ) & FC_XONXOFF) != 0) ;

   dcb.fInX = dcb.fOutX = bSet ;
   dcb.XonChar = ASCII_XON ;
   dcb.XoffChar = ASCII_XOFF ;
   dcb.XonLim = 100 ;
   dcb.XoffLim = 100 ;

   // other various settings

   dcb.fBinary = TRUE ;
   dcb.fParity = TRUE ;

#ifndef WIN32
   dcb.fRtsDisable = FALSE ;
   dcb.fDtrDisable = FALSE ;
   fRetVal = !(SetCommState( &dcb ) < 0) ;
#else
   fRetVal = SetCommState( COMDEV( npTTYInfo[CNo] ), &dcb ) ;
#endif

   return ( fRetVal ) ;

} // end of SetupConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR CloseConnection( HWND hWnd )
//
//  Description:
//     Closes the connection to the port.  Resets the connect flag
//     in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to stop secondary thread.  SetCommMask() will signal the
//       WaitCommEvent() event and the thread will halt when the
//       CONNECTED() flag is clear.
//     - Use new PurgeComm() API to clear communications driver before
//       closing device.
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//              6/15/92   BryanW      Ported to Win-32.
//
//---------------------------------------------------------------------------

BOOL NEAR CloseConnection(int CNo, HWND hWnd )
{
//   HMENU      hMenu ;
//   NPTTYINFO  npTTYInfo ;

// if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   // set connected flag to FALSE

   CONNECTED( npTTYInfo[CNo] ) = FALSE ;

#ifdef WIN32
   // disable event notification and wait for thread
   // to halt

   SetCommMask( COMDEV( npTTYInfo[CNo] ), 0 ) ;

   // block until thread has been halted

   while (THREADID( npTTYInfo[CNo] ) != 0) ;
#else
   // Disable event notification.  Using a NULL hWnd tells
   // the COMM.DRV to disable future notifications.

   EnableCommNotification( COMDEV( npTTYInfo[CNo] ), NULL, -1, -1 ) ;
#endif

   // kill the focus

   KillTTYFocus(CNo, hWnd ) ;

#ifdef WIN32
   // drop DTR

   EscapeCommFunction( COMDEV( npTTYInfo[CNo] ), CLRDTR ) ;

   // purge any outstanding reads/writes and close device handle

   PurgeComm( COMDEV( npTTYInfo[CNo] ), PURGE_TXABORT | PURGE_RXABORT |
                                   PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   CloseHandle( COMDEV( npTTYInfo[CNo] ) ) ;
#else
   // drop DTR

   EscapeCommFunction( COMDEV( npTTYInfo[CNo] ), CLRDTR ) ;

   // close comm connection

   CloseComm( COMDEV( npTTYInfo[CNo] ) ) ;
#endif

   // change the selectable items in the menu
/*
   hMenu = GetMenu( hWnd ) ;
   EnableMenuItem( hMenu, IDM_DISCONNECT,
                   MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
   EnableMenuItem( hMenu, IDM_CONNECT,
                   MF_ENABLED | MF_BYCOMMAND ) ;
*/
   return ( TRUE ) ;

} // end of CloseConnection()

//---------------------------------------------------------------------------
//  int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided block.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//  History:   Date       Author      Comment
//              5/10/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------
int NEAR ReadCommBlock(int CNo, HWND hWnd, LPSTR lpszBlock, int nMaxLength )
{
#ifdef WIN32
   BOOL       fReadStat ;
   COMSTAT    ComStat ;
   DWORD      dwErrorFlags, dwLength ;
#else
   int        nError, nLength ;
#endif

   char       szError[ 10 ] ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

#ifdef WIN32
   ClearCommError( COMDEV( npTTYInfo[CNo] ), &dwErrorFlags, &ComStat ) ;
   if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo[CNo] ))
   {
      wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
      WriteTTYBlock(CNo, hWnd, szError, lstrlen( szError ) ) ;
   }

   dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;

   if (dwLength > 0)
   {
      fReadStat = ReadFile( COMDEV( npTTYInfo[CNo] ), lpszBlock,
                            dwLength, &dwLength, &READ_OS( npTTYInfo[CNo] ) ) ;
      if (!fReadStat)
      {
         if (GetLastError() == ERROR_IO_PENDING)
         {
            // wait for a second for this transmission to complete

            if (WaitForSingleObject( READ_OS( npTTYInfo[CNo] ).hEvent, 1000 ))
               dwLength = 0 ;
            else
            {
               GetOverlappedResult( COMDEV( npTTYInfo[CNo] ),
                                    &READ_OS( npTTYInfo[CNo] ),
                                    &dwLength, FALSE ) ;
               READ_OS( npTTYInfo[CNo] ).Offset += dwLength ;
            }
         }
         else
            // some other error occurred

            dwLength = 0 ;
      }
   }

   return ( dwLength ) ;
#else
   nLength = ReadComm( COMDEV( npTTYInfo[CNo] ), lpszBlock, nMaxLength ) ;

   if (nLength < 0)
   {
      nLength *= -1 ;
      while (nError = GetCommError( COMDEV( npTTYInfo[CNo] ), NULL ))
      {
         if (DISPLAYERRORS( npTTYInfo[CNo] ))
         {
            wsprintf( szError, "<CE-%d>", nError ) ;
            WriteTTYBlock(CNo, hWnd, szError, lstrlen( szError ) ) ;
         }
      }
   }
   return ( nLength ) ;
#endif


} // end of ReadCommBlock()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteCommByte( HWND hWnd, BYTE bByte )
//
//  Description:
//     Writes a byte to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE bByte
//        byte to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//  History:   Date       Author      Comment
//              5/10/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------
BOOL NEAR WriteCommByte(int CNo, HWND hWnd, BYTE bByte )
{
#ifdef WIN32
   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
#endif
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

#ifdef WIN32
   fWriteStat = WriteFile( COMDEV( npTTYInfo[CNo] ), (LPSTR) &bByte, 1,
                           &dwBytesWritten, &WRITE_OS( npTTYInfo[CNo] ) ) ;
   if (!fWriteStat && (GetLastError() == ERROR_IO_PENDING))
   {
      // wait for a second for this transmission to complete

      if (WaitForSingleObject( WRITE_OS( npTTYInfo[CNo] ).hEvent, 1000 ))
         dwBytesWritten = 0 ;
      else
      {
         GetOverlappedResult( COMDEV( npTTYInfo[CNo] ),
                              &WRITE_OS( npTTYInfo[CNo] ),
                              &dwBytesWritten, FALSE ) ;
         WRITE_OS( npTTYInfo[CNo] ).Offset += dwBytesWritten ;
      }
   }
#else
   WriteComm( COMDEV( npTTYInfo[CNo] ), (LPSTR) &bByte, 1 ) ;
#endif
   return ( TRUE ) ;

} // end of WriteCommByte()

BOOL NEAR WriteCommString(int CNo, HWND hWnd, BYTE *bByte, int nLen )
{
#ifdef WIN32
   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
#endif
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

#ifdef WIN32
   fWriteStat = WriteFile( COMDEV( npTTYInfo[CNo] ), (LPSTR) bByte, nLen,
                           &dwBytesWritten, &WRITE_OS( npTTYInfo[CNo] ) ) ;
   if (!fWriteStat && (GetLastError() == ERROR_IO_PENDING))
   {
      // wait for a second for this transmission to complete

      if (WaitForSingleObject( WRITE_OS( npTTYInfo[CNo] ).hEvent, 1000 ))
         dwBytesWritten = 0 ;
      else
      {
         GetOverlappedResult( COMDEV( npTTYInfo[CNo] ),
                              &WRITE_OS( npTTYInfo[CNo] ),
                              &dwBytesWritten, FALSE ) ;
         WRITE_OS( npTTYInfo[CNo] ).Offset += dwBytesWritten ;
      }
   }
#else
   WriteComm( COMDEV( npTTYInfo[CNo] ), (LPSTR) bByte, nLen ) ;
#endif
   return ( TRUE ) ;

} // end of WriteCommByte()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteTTYBlock( HWND hWnd, LPSTR lpBlock, int nLength )
//
//  Description:
//     Writes block to TTY screen.  Nothing fancy - just
//     straight TTY.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpBlock
//        far pointer to block of data
//
//     int nLength
//        length of block
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//              5/20/91   BryanW      Modified... not character based,
//                                    block based now.  It was processing
//                                    per char.
//
//---------------------------------------------------------------------------
BOOL NEAR WriteTTYBlock(int CNo, HWND hWnd, LPSTR lpBlock, int nLength )
{
   int        i ;
//   NPTTYINFO  npTTYInfo ;
   RECT       rect ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
//      return ( FALSE ) ;

   for (i = 0 ; i < nLength; i++)
   {
      switch (lpBlock[ i ])
      {
         case ASCII_BEL:
            // Bell
            MessageBeep( 0 ) ;
            break ;
   
         case ASCII_BS:
            // Backspace
            if (COLUMN( npTTYInfo[CNo] ) > 0)
               COLUMN( npTTYInfo[CNo] ) -- ;
            MoveTTYCursor(CNo, hWnd ) ;
            break ;
   
         case ASCII_CR:
            // Carriage return
            COLUMN( npTTYInfo[CNo] ) = 0 ;
            MoveTTYCursor(CNo, hWnd ) ;
            if (!NEWLINE( npTTYInfo[CNo] ))
               break;
   
            // fall through
   
         case ASCII_LF:
            // Line feed
            if (ROW( npTTYInfo[CNo] )++ == MAXROWS - 1)
            {
               _fmemmove( (LPSTR) (SCREEN( npTTYInfo[CNo] )),
                          (LPSTR) (SCREEN( npTTYInfo[CNo] ) + MAXCOLS),
                          (MAXROWS - 1) * MAXCOLS ) ;
               _fmemset( (LPSTR) (SCREEN( npTTYInfo[CNo] ) + (MAXROWS - 1) * MAXCOLS),
                         ' ', MAXCOLS ) ;
               InvalidateRect( hWnd, NULL, FALSE ) ;
               ROW( npTTYInfo[CNo] )-- ;
            }
            MoveTTYCursor(CNo, hWnd ) ;
            break ;

         default:
            *(SCREEN( npTTYInfo[CNo] ) + ROW( npTTYInfo[CNo] ) * MAXCOLS +
                COLUMN( npTTYInfo[CNo] )) = lpBlock[ i ] ;
            rect.left = (COLUMN( npTTYInfo[CNo] ) * XCHAR( npTTYInfo[CNo] )) -
                        XOFFSET( npTTYInfo[CNo] ) ;
            rect.right = rect.left + XCHAR( npTTYInfo[CNo] ) ;
            rect.top = (ROW( npTTYInfo[CNo] ) * YCHAR( npTTYInfo[CNo] )) -
                       YOFFSET( npTTYInfo[CNo] ) ;
            rect.bottom = rect.top + YCHAR( npTTYInfo[CNo] ) ;
            InvalidateRect( hWnd, &rect, FALSE ) ;

            // Line wrap
            if (COLUMN( npTTYInfo[CNo] ) < MAXCOLS - 1)
               COLUMN( npTTYInfo[CNo] )++ ;
            else if (AUTOWRAP( npTTYInfo[CNo] ))
               WriteTTYBlock(CNo, hWnd, "\r\n", 2 ) ;
            break;
      }
   }
   return ( TRUE ) ;

} // end of WriteTTYBlock()
/*
//---------------------------------------------------------------------------
//  VOID NEAR GoModalDialogBoxParam( HINSTANCE hInstance,
//                                   LPCSTR lpszTemplate, HWND hWnd,
//                                   DLGPROC lpDlgProc, LPARAM lParam )
//
//  Description:
//     It is a simple utility function that simply performs the
//     MPI and invokes the dialog box with a DWORD paramter.
//
//  Parameters:
//     similar to that of DialogBoxParam() with the exception
//     that the lpDlgProc is not a procedure instance
//
//  History:   Date       Author      Comment
//              5/10/91   BryanW      Wrote it.
//
//---------------------------------------------------------------------------

VOID NEAR GoModalDialogBoxParam( HINSTANCE hInstance, LPCSTR lpszTemplate,
                                 HWND hWnd, DLGPROC lpDlgProc, LPARAM lParam )
{
   DLGPROC  lpProcInstance ;

   lpProcInstance = (DLGPROC) MakeProcInstance( (FARPROC) lpDlgProc,
                                                hInstance ) ;
   DialogBoxParam( hInstance, lpszTemplate, hWnd, lpProcInstance, lParam ) ;
   FreeProcInstance( (FARPROC) lpProcInstance ) ;

} // end of GoModalDialogBoxParam()

//---------------------------------------------------------------------------
//  VOID NEAR FillComboBox( HINSTANCE hInstance, HWND hCtrlWnd, int nIDString,
//                          WORD NEAR *npTable, WORD wTableLen,
//                          WORD wCurrentSetting )
//
//  Description:
//     Fills the given combo box with strings from the resource
//     table starting at nIDString.  Associated items are
//     added from given table.  The combo box is notified of
//     the current setting.
//
//  Parameters:
//     HINSTANCE hInstance
//        handle to application instance
//
//     HWND hCtrlWnd
//        handle to combo box control
//
//     int nIDString
//        first resource string id
//
//     DWORD NEAR *npTable
//        near point to table of associated values
//
//     WORD wTableLen
//        length of table
//
//     DWORD dwCurrentSetting
//        current setting (for combo box selection)
//
//  History:   Date       Author      Comment
//             10/20/91   BryanW      Pulled from the init procedure.
//
//---------------------------------------------------------------------------

VOID NEAR FillComboBox( HINSTANCE hInstance, HWND hCtrlWnd, int nIDString,
                        DWORD NEAR *npTable, WORD wTableLen,
                        DWORD dwCurrentSetting )
{
   char  szBuffer[ MAXLEN_TEMPSTR ] ;
   WORD  wCount, wPosition ;

   for (wCount = 0; wCount < wTableLen; wCount++)
   {
      // load the string from the string resources and
      // add it to the combo box

      LoadString( hInstance, nIDString + wCount, szBuffer, sizeof( szBuffer ) ) ;
      wPosition = LOWORD( SendMessage( hCtrlWnd, CB_ADDSTRING, 0,
                                       (LPARAM) (LPSTR) szBuffer ) ) ;

      // use item data to store the actual table value

      SendMessage( hCtrlWnd, CB_SETITEMDATA, (WPARAM) wPosition,
                   (LPARAM) *(npTable + wCount) ) ;

      // if this is our current setting, select it

      if (*(npTable + wCount) == dwCurrentSetting)
         SendMessage( hCtrlWnd, CB_SETCURSEL, (WPARAM) wPosition, 0L ) ;
   }

} // end of FillComboBox()

//---------------------------------------------------------------------------
//  BOOL NEAR SettingsDlgInit( HWND hDlg )
//
//  Description:
//     Puts current settings into dialog box (via CheckRadioButton() etc.)
//
//  Parameters:
//     HWND hDlg
//        handle to dialog box
//
//  Win-32 Porting Issues:
//     - Constants require DWORD arrays for baud rate table, etc.
//     - There is no "MAXCOM" function in Win-32.  Number of COM ports
//       is assumed to be 4.
//
//  History:   Date       Author      Comment
//              5/11/91   BryanW      Wrote it.
//             10/20/91   BryanW      Dialog revision.
//             10/24/91   BryanW      Fixed bug with EscapeCommFunction().
//              6/15/92   BryanW      Ported to Win-32.
//
//---------------------------------------------------------------------------

BOOL NEAR SettingsDlgInit( HWND hDlg )
{
   char       szBuffer[ MAXLEN_TEMPSTR ], szTemp[ MAXLEN_TEMPSTR ] ;
//   NPTTYINFO  npTTYInfo ;
   WORD       wCount, wMaxCOM, wPosition ;

//   if (NULL == (npTTYInfo = (NPTTYINFO) GET_PROP( hDlg, ATOM_TTYINFO )))
//      return ( FALSE ) ;

#ifdef WIN32
   wMaxCOM = MAXPORTS ;
#else
   wMaxCOM = LOWORD( EscapeCommFunction( NULL, GETMAXCOM ) ) + 1 ;
#endif

   // load the COM prefix from resources

   LoadString( GETHINST( hDlg ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;

   // fill port combo box and make initial selection

   for (wCount = 0; wCount < wMaxCOM; wCount++)
   {
      wsprintf( szBuffer, "%s%d", (LPSTR) szTemp, wCount + 1 ) ;
      SendDlgItemMessage( hDlg, IDD_PORTCB, CB_ADDSTRING, 0,
                          (LPARAM) (LPSTR) szBuffer ) ;
   }

#ifdef WIN32 
   SendDlgItemMessage( hDlg, IDD_PORTCB, CB_ADDSTRING, 0,
                       (LPARAM) (LPSTR) "TELNET" ) ;
#endif
   SendDlgItemMessage( hDlg, IDD_PORTCB, CB_SETCURSEL,
                       (WPARAM) (PORT( npTTYInfo ) - 1), 0L ) ;

   // disable COM port combo box if connection has already been
   // established (e.g. OpenComm() already successful)

   EnableWindow( GetDlgItem( hDlg, IDD_PORTCB ), !CONNECTED( npTTYInfo ) ) ;

   // fill baud combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_BAUDCB ),
                 IDS_BAUD110, BaudTable,
                 sizeof( BaudTable ) / sizeof( BaudTable[ 0 ] ),
                 BAUDRATE( npTTYInfo ) ) ;

   // fill data bits combo box and make initial selection

   for (wCount = 5; wCount < 9; wCount++)
   {
      wsprintf( szBuffer, "%d", wCount ) ;
      wPosition = LOWORD( SendDlgItemMessage( hDlg, IDD_DATABITSCB,
                                              CB_ADDSTRING, 0,
                                              (LPARAM) (LPSTR) szBuffer ) ) ;

      // if current selection, tell the combo box

      if (wCount == BYTESIZE( npTTYInfo ))
         SendDlgItemMessage( hDlg, IDD_DATABITSCB, CB_SETCURSEL,
                             (WPARAM) wPosition, 0L ) ;
   }

   // fill parity combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_PARITYCB ),
                 IDS_PARITYNONE, ParityTable,
                 sizeof( ParityTable ) / sizeof( ParityTable[ 0 ] ),
                 PARITY( npTTYInfo ) ) ;

   // fill stop bits combo box and make initial selection

   FillComboBox( GETHINST( hDlg ), GetDlgItem( hDlg, IDD_STOPBITSCB ),
                 IDS_ONESTOPBIT, StopBitsTable,
                 sizeof( StopBitsTable ) / sizeof ( StopBitsTable ),
                 STOPBITS( npTTYInfo ) ) ;

   // initalize the flow control settings

   CheckDlgButton( hDlg, IDD_DTRDSR,
                   (FLOWCTRL( npTTYInfo ) & FC_DTRDSR) > 0 ) ;
   CheckDlgButton( hDlg, IDD_RTSCTS,
                   (FLOWCTRL( npTTYInfo ) & FC_RTSCTS) > 0 ) ;
   CheckDlgButton( hDlg, IDD_XONXOFF,
                   (FLOWCTRL( npTTYInfo ) & FC_XONXOFF) > 0 ) ;

   // other TTY settings

   CheckDlgButton( hDlg, IDD_AUTOWRAP, AUTOWRAP( npTTYInfo ) ) ;
   CheckDlgButton( hDlg, IDD_NEWLINE, NEWLINE( npTTYInfo ) ) ;
   CheckDlgButton( hDlg, IDD_LOCALECHO, LOCALECHO( npTTYInfo ) ) ;

   // control options

#ifdef WIN32
   // "Use CN_RECEIVE" is not valid under Win-32

   EnableWindow( GetDlgItem( hDlg, IDD_USECNRECEIVE ), FALSE ) ;
#else
   CheckDlgButton( hDlg, IDD_USECNRECEIVE, USECNRECEIVE( npTTYInfo ) ) ;

   // disable Use CN_RECEIVE option if connection has already been
   // established (e.g. OpenComm() already successful)

   EnableWindow( GetDlgItem( hDlg, IDD_USECNRECEIVE ),
                 !CONNECTED( npTTYInfo ) ) ;
#endif

   CheckDlgButton( hDlg, IDD_DISPLAYERRORS, DISPLAYERRORS( npTTYInfo ) ) ;

   return ( TRUE ) ;

} // end of SettingsDlgInit()

//---------------------------------------------------------------------------
//  BOOL NEAR SettingsDlgTerm( HWND hDlg )
//
//  Description:
//     Puts dialog contents into TTY info structure.
//
//  Parameters:
//     HWND hDlg
//        handle to settings dialog
//
//  Win-32 Porting Issues:
//     - Baud rate requires DWORD values.
//
//  History:   Date       Author      Comment
//              5/11/91   BryanW      Wrote it.
//              6/15/92   BryanW      Ported to Win-32.
//
//---------------------------------------------------------------------------

BOOL NEAR SettingsDlgTerm( HWND hDlg )
{
//   NPTTYINFO  npTTYInfo ;
   WORD       wSelection ;

//   if (NULL == (npTTYInfo = (NPTTYINFO) GET_PROP( hDlg, ATOM_TTYINFO )))
//      return ( FALSE ) ;

   // get port selection

   PORT( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_PORTCB,
                                          CB_GETCURSEL,
                                          0, 0L ) ) + 1 ) ;
   // get baud rate selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_BAUDCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
#ifdef WIN32
   BAUDRATE( npTTYInfo ) =
      SendDlgItemMessage( hDlg, IDD_BAUDCB, CB_GETITEMDATA,
                          (WPARAM) wSelection, 0L ) ;
#else
   BAUDRATE( npTTYInfo ) =
      LOWORD( SendDlgItemMessage( hDlg, IDD_BAUDCB, CB_GETITEMDATA,
                                  (WPARAM) wSelection, 0L ) ) ;
#endif

   // get data bits selection

   BYTESIZE( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_DATABITSCB,
                                          CB_GETCURSEL,
                                          0, 0L ) ) + 5 ) ;

   // get parity selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_PARITYCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
   PARITY( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_PARITYCB,
                                          CB_GETITEMDATA,
                                          (WPARAM) wSelection,
                                          0L ) ) ) ;

   // get stop bits selection

   wSelection =
      LOWORD( SendDlgItemMessage( hDlg, IDD_STOPBITSCB, CB_GETCURSEL,
                                  0, 0L ) ) ;
   STOPBITS( npTTYInfo ) =
      LOBYTE( LOWORD( SendDlgItemMessage( hDlg, IDD_STOPBITSCB,
                                          CB_GETITEMDATA,
                                          (WPARAM) wSelection, 0L ) ) ) ;

   // get flow control settings

   FLOWCTRL( npTTYInfo ) = 0 ;
   if (IsDlgButtonChecked( hDlg, IDD_DTRDSR ))
      FLOWCTRL( npTTYInfo ) |= FC_DTRDSR ;
   if (IsDlgButtonChecked( hDlg, IDD_RTSCTS ))
      FLOWCTRL( npTTYInfo ) |= FC_RTSCTS ;
   if (IsDlgButtonChecked( hDlg, IDD_XONXOFF ))
      FLOWCTRL( npTTYInfo ) |= FC_XONXOFF ;

   // get other various settings

   AUTOWRAP( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_AUTOWRAP ) ;
   NEWLINE( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_NEWLINE ) ;
   LOCALECHO( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_LOCALECHO ) ;

   // control options

   USECNRECEIVE( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_USECNRECEIVE ) ;
   DISPLAYERRORS( npTTYInfo ) = IsDlgButtonChecked( hDlg, IDD_DISPLAYERRORS ) ;

   return ( TRUE ) ;

} // end of SettingsDlgTerm()

*/
#ifdef WIN32

//************************************************************************
//  DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
//
//  Description:
//     A secondary thread that will watch for COMM events.
//
//  Parameters:
//     LPSTR lpData
//        32-bit pointer argument
//
//  Win-32 Porting Issues:
//     - Added this thread to watch the communications device and
//       post notifications to the associated window.
//
//  History:   Date       Author      Comment
//             12/31/91   BryanW      Wrote it.
//              6/12/92   BryanW      CommWaitEvent() now uses
//                                    an overlapped structure.
//
//************************************************************************

DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
{
   DWORD       dwTransfer, dwEvtMask ;
//   NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;

   int CNo = atoi(lpData);

   memset( &os, 0, sizeof( OVERLAPPED ) ) ;

   // create I/O event used for overlapped read

   os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
   if (os.hEvent == NULL)
   {
      MessageBox( NULL, "Failed to create event for thread!", "TTY Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
      return ( FALSE ) ;
   }

   if (!SetCommMask( COMDEV( npTTYInfo[CNo] ), EV_RXCHAR ))
      return ( FALSE ) ;

   while ( CONNECTED( npTTYInfo[CNo] ) )
   {
      dwEvtMask = 0 ;

      if (!WaitCommEvent( COMDEV( npTTYInfo[CNo] ), &dwEvtMask, &os ))
      {
         if (ERROR_IO_PENDING == GetLastError())
         {
            GetOverlappedResult( COMDEV( npTTYInfo[CNo] ), &os, &dwTransfer, TRUE ) ;
            os.Offset += dwTransfer ;
         }
      }

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
         // wait for "posted notification" flag to clear

         //WaitForSingleObject( POSTEVENT( npTTYInfo[CNo] ), 0xFFFFFFFF ) ;		// 1999.10.15
		  Sleep(100);

		  // reset event

         ResetEvent( POSTEVENT( npTTYInfo[CNo] ) ) ;

         // last message was processed, O.K. to post
//			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COMMNOTIFY,
  //                    (WPARAM) COMDEV( npTTYInfo[CNo] ),
    //                  MAKELONG( CN_EVENT, 0 ) ) ;
		 if (CNo == 0)
			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COM1,
                      (WPARAM) COMDEV( npTTYInfo[CNo] ),
                      MAKELONG( CN_EVENT, 0 ) ) ;
		 else
			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COM2,
                      (WPARAM) COMDEV( npTTYInfo[CNo] ),
                      MAKELONG( CN_EVENT, 0 ) ) ;
      }
   }

   // get rid of event handle

   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")

   THREADID( npTTYInfo[CNo] ) = 0 ;
   HTHREAD( npTTYInfo[CNo] ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()

DWORD FAR PASCAL CommWatchProc1( LPSTR lpData )
{
   DWORD       dwTransfer, dwEvtMask ;
//   NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;

   int CNo = atoi(lpData);

   memset( &os, 0, sizeof( OVERLAPPED ) ) ;

   // create I/O event used for overlapped read

   os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
   if (os.hEvent == NULL)
   {
      MessageBox( NULL, "Failed to create event for thread!", "TTY Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
      return ( FALSE ) ;
   }

   if (!SetCommMask( COMDEV( npTTYInfo[CNo] ), EV_RXCHAR ))
      return ( FALSE ) ;

   while ( CONNECTED( npTTYInfo[CNo] ) )
   {
      dwEvtMask = 0 ;

      if (!WaitCommEvent( COMDEV( npTTYInfo[CNo] ), &dwEvtMask, &os ))
      {
         if (ERROR_IO_PENDING == GetLastError())
         {
            GetOverlappedResult( COMDEV( npTTYInfo[CNo] ), &os, &dwTransfer, TRUE ) ;
            os.Offset += dwTransfer ;
         }
      }

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
         // wait for "posted notification" flag to clear

         //WaitForSingleObject( POSTEVENT( npTTYInfo[CNo] ), 0xFFFFFFFF ) ;		// 1999.10.15
		  Sleep(100);

		  // reset event

         ResetEvent( POSTEVENT( npTTYInfo[CNo] ) ) ;

         // last message was processed, O.K. to post
//			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COMMNOTIFY,
  //                    (WPARAM) COMDEV( npTTYInfo[CNo] ),
    //                  MAKELONG( CN_EVENT, 0 ) ) ;
		 if (CNo == 0)
			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COM1,
                      (WPARAM) COMDEV( npTTYInfo[CNo] ),
                      MAKELONG( CN_EVENT, 0 ) ) ;
		 else
			PostMessage( TERMWND( npTTYInfo[CNo] ), WM_COM2,
                      (WPARAM) COMDEV( npTTYInfo[CNo] ),
                      MAKELONG( CN_EVENT, 0 ) ) ;
      }
   }

   // get rid of event handle

   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")

   THREADID( npTTYInfo[CNo] ) = 0 ;
   HTHREAD( npTTYInfo[CNo] ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()

#endif

