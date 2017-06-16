/******************************************************************************
				Copyright (C) 1998 NKK Unics Corporation
						All Right Reserved

	System Name	:	�ėp ���p�������֐�
	File Name	:	ShareMemory.h
	Create		:	1998.11.22
	Contents	:	���p�������֐�
	Writen by	:	�� �Ԗ�(NKK Unics)
	Version		:	1.0
******************************************************************************/
// �V�F�A������
#define MAXSHARE 2		// �ő�V�F�A��������
#define BUFFERSIZE 3072	// �f�[�^�T�C�Y
#define SHAREDSIZE 4096	// �V�F�A�������T�C�Y �iBUFFERSIZE + 4 * 4 �ȏ�j
//#define TIMEOUT 500000	// �^�C�}�[�A�E�g �T00�b
#define TIMEOUT 2000

#define WM_Notify_ReqData    WM_USER + 3010  // �v���f�[�^���M���b�Z�[�W(���L������)
#define WM_Notify_WriteData  WM_USER + 3040	// ����v���Z�X�ɒʒm���܂�
#define WM_Notify_WriteData1 WM_USER + 3041	// ����v���Z�X�ɒʒm���܂�

// �v���Z�X�ԒʐM�i���p�������j�G���A�̍\����
typedef struct {
	HWND	FHw_Owner;	// ���p���������쐬����v���Z�X�̃E�B���h�E�n���h��
	HWND	FHw_User;	// ���p���������g�p����v���Z�X�̃E�B���h�E�n���h��
	int	Fin_Notice;						// 0: �Ǎ�����;  1: ��������
	DWORD	Fdw_DataSize;				// �L���f�[�^���i�o�C�g��)
	char	Fby_DataBuff[BUFFERSIZE];	// �f�[�^�G���A
} TRec_IFarea;

typedef struct {
	short	FId;						// function code
	char	DataBuff[BUFFERSIZE-2];		// Data buffer
} TRec_DataBuff;

// Declear for Shared Memory Routine

// �ʐM�p�V�F�A�������쐬
// �߂�l:	-1: �V�F�A������ID �G���[
//		-2: �V�F�A�������G���[
//		 1: ����
extern int SharedMemory_Create(HWND hWnd, char *SName, int SId);

// �ʐM�p�V�F�A�������J��
// �߂�l:	-1: �V�F�A������ID �G���[
//			-2: �V�F�A�������G���[
//			 1: ����
extern int SharedMemory_Open(HWND hWnd, char *SName, int SId);

// Share Memory Close
// �߂�l:	-1: �V�F�A������ID �G���[
//			 1: ����
extern int SharedMemory_Close(int SId);

// Read from Share Memory
// �߂�l:	-1: �V�F�A������ID �G���[
//			-4: Open����Ă��Ȃ�
//			 0: No Data or Data not ready
//			>0: �f�[�^��
// ���ӁFFortran�Ń��b�Z�[�W���Ȃ��̂ŁAWM_Notify_WriteData�̃`�F�b�N�Ȃ�
extern int SharedMemory_Read(int SId, char *RedBuf);

// send data request(Windows Message)
// �߂�l:	-1: �V�F�A������ID �G���[
//			-4: Open����Ă��Ȃ�
//			 1: ����
extern int SharedMemory_SendReq(int SId);

// Write to Share Memory
// �߂�l:	-1: �V�F�A������ID �G���[
//			-3: �^�C�}�[�A�E�g
//			-4: Open����Ă��Ȃ�
//			 1: ����
extern int SharedMemory_Write(int SId, int FId, char *RecBuf, int Len);

// receive WM_Notify_WirteData
extern void SharedMemory_Message(int D_Size, int SId);

// �V�F�A�������G���[���b�Z�[�W�̕\��
extern void SharedMemoryErrorString(int errno);

