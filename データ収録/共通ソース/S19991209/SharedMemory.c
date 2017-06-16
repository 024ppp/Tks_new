/******************************************************************************
				Copyright (C) 1998 NKK Unics Corporation
						All Right Reserved

	System Name	:	�ėp ���p�������֐�
    File Name	:	ShareMemory.c
    Create		:	1998.11.22
	Contents	:	���p�������֐�
	Writen by	:	�� �Ԗ�(NKK Unics)
	Version		:	1.0
******************************************************************************/
#include <windows.h>
#include <stdio.h>
#include "SharedMemory.h"

#define STYPE 0				// 0: no CreateFile;  1: CreateFile

int Err_Disp = 1;

// File Mapping�֌W�ϐ�
HANDLE MapFileHandle[MAXSHARE] = {NULL, NULL};
HANDLE hMem1[MAXSHARE] = {NULL, NULL};
LPVOID pShrMem1[MAXSHARE] = {NULL, NULL};
TRec_IFarea Comm_Buff[MAXSHARE];			// �ʐM�G���A
TRec_DataBuff DataBuffer;					// �f�[�^�G���A
int OpenFlag[MAXSHARE] = {0, 0};	// 0: ��Open;  1: Opened
int BuffType[MAXSHARE] = {0, 0};	// 0: Server(Create);  1: Client(Open)
HWND Owner[MAXSHARE];
int SM_DataFlag[MAXSHARE] = {0, 0}; // <= 0: No Data; > 0: Data Size

// File Mapping�̓������[�`��
void ErrorOut(LPSTR errstring);
HANDLE OpenMap( LPSTR MapName);
HANDLE CreateMapFile(char *MapFileName);
HANDLE CreateMap(HANDLE FileToBeMapped, LPSTR MapName, int SSize);
LPVOID MapView(HANDLE hMap, int SSize);

/*---------------------------------------------------------------------------------------
// User Interface
-----------------------------------------------------------------------------------------*/
// �ʐM�p�V�F�A�������쐬
// �߂�l:	-1: �V�F�A������ID �G���[
//			-2: �V�F�A�������G���[
//			-5: Open���܂���
//			 1: ����
int SharedMemory_Create(HWND hWnd, char *SName, int SId) 
{
	char tempo[128];

	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	if (OpenFlag[SId-1] == 1)
		return -5;

	// File Mapping
	// Step1: Create File
	if (STYPE == 0)
		MapFileHandle[SId-1] = (HANDLE)0xFFFFFFFF;
	else {
		sprintf(tempo, "ShareMemory%3d", SId);
		MapFileHandle[SId-1] = CreateMapFile(tempo);
	}
	
	// Step2: Create File Mapping
	if (hMem1[SId-1] = CreateMap(MapFileHandle[SId-1], SName, SHAREDSIZE))
		;
	else {
		if (Err_Disp == 1)
			ErrorOut("CreateMap Error");
		return -2;
	}
			
	// Step3: Map View of File
	if (pShrMem1[SId-1] = (LPVOID)MapView(hMem1[SId-1], SHAREDSIZE))
		;
	else {
		if (Err_Disp == 1)
			ErrorOut("CreateMapVeiw Error");
		return -2;
	}

	// ������
	Comm_Buff[SId-1].FHw_Owner = hWnd;
	Comm_Buff[SId-1].FHw_User = NULL;
	Comm_Buff[SId-1].Fin_Notice = 0;
	Comm_Buff[SId-1].Fdw_DataSize = 0;
	Comm_Buff[SId-1].Fby_DataBuff[0] = '\0';

	Owner[SId-1] = hWnd;

	//memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], SHAREDSIZE);
	memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], sizeof(TRec_IFarea));

	OpenFlag[SId-1] = 1;
	BuffType[SId-1] = 0;

	return 1;
}

// �ʐM�p�V�F�A�������J��
// �߂�l:	-1: �V�F�A������ID �G���[
//			-2: �V�F�A�������G���[
//			-5: Open���܂���
//			 1: ����
int SharedMemory_Open(HWND hWnd, char *SName, int SId)
{
	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	if (OpenFlag[SId-1] == 1)
		return -5;

	// File Mapping
	// Step1: Open File Mapping
	if (hMem1[SId-1] = OpenMap(SName))
		;
	else {
		if (Err_Disp == 1)
			ErrorOut("Open Map Error");
		return -2;
	}
			
	// Step2: Map View of File
	if (pShrMem1[SId-1] = (LPVOID)MapView(hMem1[SId-1], SHAREDSIZE))
		;
	else {
		if (Err_Disp == 1)
			ErrorOut("MapVeiw Error");
		return -2;
	}

	// Read Virtual Memory
	//memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
	memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], sizeof(TRec_IFarea));

	Comm_Buff[SId-1].FHw_User = hWnd;

	Owner[SId-1] = hWnd;

	// Rewrite Virtual Memory
	//memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], SHAREDSIZE);
	memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], sizeof(TRec_IFarea));

	OpenFlag[SId-1] = 1;
	BuffType[SId-1] = 1;

	return 1;
}

// Write to Share Memory
// �߂�l:	-1: �V�F�A������ID �G���[
//			-3: �^�C�}�[�A�E�g
//			-4: Open����Ă��Ȃ�
//			 1: ����
BOOL SharedMemory_Write(int SId, int FId, char *WrtBuf, int Len)
{
	unsigned long itime;
	int ret;

	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	if (OpenFlag[SId-1] != 1)
		return -4;

	Sleep(1);

	// Read Virtual Memory Status
	//memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
	memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], sizeof(TRec_IFarea));

	// check read�����t���O
	if (Comm_Buff[SId-1].Fin_Notice != 0) {
Retry1:
		// �^�C�}�[�A�E�g�`�F�b�N
		itime = GetCurrentTime();

		while (GetCurrentTime() - itime < TIMEOUT) {
			// Read Virtual Memory Status
			//memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
			memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], sizeof(TRec_IFarea));

			if (Comm_Buff[SId-1].Fin_Notice == 0)
				break;
			Sleep(1);
		}

		Comm_Buff[SId-1].Fin_Notice = 0;

		if (Comm_Buff[SId-1].Fin_Notice != 0) {
			ret = MessageBox(GetFocus(), "�^�C�}�[�A�E�g�B�I�����܂����H", "�m�F", MB_YESNO);
			if (ret == IDYES)  // �I��
				PostQuitMessage(0);
			else
				goto Retry1;
		}
	}

	Comm_Buff[SId-1].Fin_Notice = 1;
	Comm_Buff[SId-1].Fdw_DataSize = Len+2;

	DataBuffer.FId = FId;
	memcpy(DataBuffer.DataBuff, WrtBuf, Len);
	memcpy(Comm_Buff[SId-1].Fby_DataBuff, (char *)&DataBuffer, Len+2);

	// Write Virtual Memory
	//memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], SHAREDSIZE);
	memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], sizeof(TRec_IFarea));

	// ���M����Windows���b�Z�[�WID�𑊎�֑���
	if (BuffType[SId-1] == 0) { // Server��
		if (SId == 1)
			PostMessage(Comm_Buff[SId-1].FHw_User, WM_Notify_WriteData, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
		else
			PostMessage(Comm_Buff[SId-1].FHw_User, WM_Notify_WriteData1, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
	} else { // Client��
		if (SId == 1)
			PostMessage(Comm_Buff[SId-1].FHw_Owner, WM_Notify_WriteData, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
		else
			PostMessage(Comm_Buff[SId-1].FHw_Owner, WM_Notify_WriteData1, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
	}
/*
	// �^�C�}�[�A�E�g�`�F�b�N
Retry2:
	itime = GetCurrentTime();

	while (GetCurrentTime() - itime < TIMEOUT) {
		// Read Virtual Memory Status
		memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
		if (Comm_Buff[SId-1].Fin_Notice == 0)
			break;
		Sleep(1);
	}

	if (Comm_Buff[SId-1].Fin_Notice == 1) {
		ret = MessageBox(GetFocus(), "�^�C�}�[�A�E�g�B�I�����܂����H", "�m�F", MB_YESNO);
		if (ret == IDYES)  // �I��
			PostQuitMessage(0);
		else
			goto Retry2;
	} 
*/
	return 1;
}

// Read from Share Memory
// �߂�l:	-1: �V�F�A������ID �G���[
//			-4: Open����Ă��Ȃ�
//			 0: No Data or Data not ready
//		    >0: �f�[�^��
int SharedMemory_Read(int SId, char *ReadBuf)
{
	unsigned long itime;
	int ret;

	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	if (OpenFlag[SId-1] != 1)
		return -4;

	// receive WM_Notify_WriteData message
//	if (SM_DataFlag[SId-1] <= 0) {
//		Sleep(100);
//		return 0;
//	}

/*	// ���M����Windows���b�Z�[�WID�𑊎�֑���
	if (BuffType[SId-1] == 0) // Server��
		PostMessage(Comm_Buff[SId-1].FHw_User, WM_Notify_ReqData, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
	else // Client��
		PostMessage(Comm_Buff[SId-1].FHw_Owner, WM_Notify_ReqData, 
					(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
*/
	// Read Virtual Memory Status
	//memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
	memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], sizeof(TRec_IFarea));

	// check Write�����t���O
	if (Comm_Buff[SId-1].Fin_Notice != 1) {
Retry1:
		// �^�C�}�[�A�E�g�`�F�b�N
		itime = GetCurrentTime();

		while (GetCurrentTime() - itime < TIMEOUT) {
			// Read Virtual Memory Status
			//memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], SHAREDSIZE);
			memcpy((char *)&Comm_Buff[SId-1], (LPCTSTR)pShrMem1[SId-1], sizeof(TRec_IFarea));
			if (Comm_Buff[SId-1].Fin_Notice == 1)
				break;
			Sleep(10);
		}

		Comm_Buff[SId-1].Fin_Notice = 1;

		if (Comm_Buff[SId-1].Fin_Notice != 1) {
			ret = MessageBox(GetFocus(), "�^�C�}�[�A�E�g�B�I�����܂����H", "�m�F", MB_YESNO);
			if (ret == IDYES)  // �I��
				PostQuitMessage(0);
			else
				goto Retry1;
		}
	}

//	if (Comm_Buff[SId-1].Fdw_DataSize <= 0) {
	if (Comm_Buff[SId-1].Fin_Notice != 1 || Comm_Buff[SId-1].Fdw_DataSize <= 0) {
		Sleep(1);
		return 0;
	}

	Comm_Buff[SId-1].Fin_Notice = 0;
	SM_DataFlag[SId-1] = 0;
	memcpy((char *)&DataBuffer, Comm_Buff[SId-1].Fby_DataBuff, Comm_Buff[SId-1].Fdw_DataSize);
	if (Comm_Buff[SId-1].Fdw_DataSize > 2) {
		ret = Comm_Buff[SId-1].Fdw_DataSize-2;
		memcpy(ReadBuf, DataBuffer.DataBuff,  ret);
		ReadBuf[ret] = '\0';
	} else {
		ReadBuf[0] = '\0';
		ret = 0;
	}

	// Rewrite Virtual Memory Status
	//memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], SHAREDSIZE);
	memcpy((char *)pShrMem1[SId-1], (char *)&Comm_Buff[SId-1], sizeof(TRec_IFarea));

	return ret;
}
/*
// send data request(Windows Message)
// �߂�l:	-1: �V�F�A������ID �G���[
//			-4: Open����Ă��Ȃ�
//			 1: ����
int SharedMemory_SendReq(int SId)
{
	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	if (OpenFlag[SId-1] != 1)
		return -4;

	// ���M����Windows���b�Z�[�WID�𑊎�֑���
	if (BuffType[SId-1] == 0) // Server��
		PostMessage(Comm_Buff[SId-1].FHw_User, WM_Notify_ReqData, 
			(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);
	else // Client��
		PostMessage(Comm_Buff[SId-1].FHw_Owner, WM_Notify_ReqData, 
			(WPARAM)Comm_Buff[SId-1].Fdw_DataSize, (LPARAM)SId);

	return 1;
}
*/
// Share Memory Close
// �߂�l:	-1: �V�F�A������ID �G���[
//			 1: ����
BOOL SharedMemory_Close(int SId)
{
	if (SId <= 0 || SId > MAXSHARE)
		return -1;

	// unmap view, close mapping and file!
	if (pShrMem1[SId-1]) {
		UnmapViewOfFile(pShrMem1[SId-1]);
		pShrMem1[SId-1] = NULL;
	}

	if (hMem1[SId-1]) {
		CloseHandle(hMem1[SId-1]);
		hMem1[SId-1] = NULL;
	}

	if (MapFileHandle[SId-1] && MapFileHandle[SId-1] != INVALID_HANDLE_VALUE) {
		CloseHandle(MapFileHandle[SId-1]);
		MapFileHandle[SId-1] = NULL;
	}

	OpenFlag[SId-1] = 0;
	BuffType[SId-1] = 0;

	return 1;
}

// �V�F�A�������G���[���b�Z�[�W�̕\��
void SharedMemoryErrorString(int errno)
{
	switch (errno) {
		case -1:
			MessageBox(GetFocus(), "�V�F�A������ID�G���[", "", MB_OK);
			break;
		case -2:
			MessageBox(GetFocus(), "�V�F�A�������G���[", "", MB_OK);
			break;
		case -3:
			MessageBox(GetFocus(), "�^�C�}�[�A�E�g", "", MB_OK);
			break;
		case -4:
			MessageBox(GetFocus(), "Open����Ă��Ȃ�", "", MB_OK);
			break;
		case -5:
			MessageBox(GetFocus(), "Open���܂���", "", MB_OK);
			break;
		default:
			;
	}
}

// receive WM_Notify_WirteData message
void SharedMemory_Message(int D_Size, int SId)
{
	if (SId <= 0 || SId > MAXSHARE)
		return;

	SM_DataFlag[SId-1] = D_Size;
}

/*-------------------------------------------------------------------------------------
// File Mapping's Basic Routine
---------------------------------------------------------------------------------------*/
void ErrorOut(LPSTR errstring)
{
   MessageBox(GetFocus(), errstring, NULL, MB_OK);
}

/*************************************************************************
 * HANDLE OpenMap(LPSTR MapName)
 *
 * Purpose: Open the mapping object pointed to by MapName
 *
 * Inputs: none
 *
 * Returns: handle to mapped object or NULL if failure
 *
 * Calls: OpenFileMapping, ErrorOut
 *
\*************************************************************************/
HANDLE OpenMap( LPSTR MapName)
{
	HANDLE hAMap;

	hAMap= OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
                          TRUE,
                          MapName);

	if (hAMap == NULL) {
		if (Err_Disp == 1)
			ErrorOut("OpenFileMapping");
		return(NULL);
	} else
		return(hAMap);
}

/**************************************************************************
 * HANDLE CreateMapFile(char *MapFileName)
 *
 * Purpose: Create a Map file to map named share memory
 *
 * Inputs:  none
 *
 * Returns: MapFileHandle - a handle to the file
 *                        or NULL if failure
 *
 * Calls:   CreateFile, ErrorOut
 *
\**************************************************************************/
HANDLE CreateMapFile(char *MapFileName)
{
	HANDLE MapFileHandle;

	MapFileHandle= CreateFile(MapFileName,
                             GENERIC_READ | GENERIC_WRITE,
                             FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL,
                             CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                             NULL);

	if (MapFileHandle == INVALID_HANDLE_VALUE) {
		if (Err_Disp == 1)
			ErrorOut("CreateFile");
		return(NULL);
	} else
		return(MapFileHandle);
}

/**************************************************************************
 * HANDLE CreateMap(HANDLE FileToBeMapped, char *MapName )
 *
 * Purpose: Create File Mapping object using the open file handle
 *
 * Inputs:  FileToBeMapped - handle to the file
 *
 * Returns: MapHandle - handle to the file mapping object
 *                    or NULL if failure
 *
 * Calls:   CreateFileMapping, ErrorOut
\**************************************************************************/
HANDLE CreateMap(HANDLE FileToBeMapped, LPSTR MapName, int SSize)
{
	HANDLE MapHandle;

	MapHandle= CreateFileMapping(FileToBeMapped,
                                NULL,
                                PAGE_READWRITE,
                                0,
                                SSize,
                                MapName);

	if (MapHandle == NULL) {
		if (Err_Disp == 1)
			ErrorOut("CreateFileMapping");
		return(NULL);
	} else
		return(MapHandle);
}

/**************************************************************************
 * LPVOID MapView(HANDLE hMap)
 *
 * Purpose: Map the file mapping object into address space
 *
 * Inputs:  hMap - handle to the mapping object
 *
 * Returns: MappedPointer - pointer to the address space that the
 *                        object is mapped into
 *                        or NULL if failure
 *
 * Calls:   MapViewOfFile, ErrorOut
 *
\**************************************************************************/
LPVOID MapView(HANDLE hMap, int SSize)
{
	LPVOID MappedPointer;

	MappedPointer= MapViewOfFile(hMap, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, SSize);
	if (MappedPointer == NULL) {
		if (Err_Disp == 1)
			ErrorOut("MapViewOfFile");
		return(NULL);
	} else
		return(MappedPointer);
}
