/******************************************************************************
				Copyright (C) 1999 NKK Unics Corporation
						All Right Reserved

	System Name	:	TRIS �����V�X�e�� ���Ԍ���
    File Name	:	Socket.h
    Create		:	1999.09.29
	Contents	:	Socket ��{���[�`��
	Writen by	:	�� �Ԗ�(NKK Unics)
	Version		:	1.0
******************************************************************************/
#include <winsock.h>

/*
 * WinSock 2 extension -- manifest constants for shutdown()
 */
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

#define MAXSOCKET			 5	// �ő�Socket��
#define MAX_PENDING_CONNECTS 4	// the backlog allowed for listen()
#define NO_FLAGS_SET		 0	// Used with recv()/send()
#define MY_MSG_LENGTH		256	// msg buffer sent back and forth

// Socket������
// �߂�l�F	 1: ����
//			-6: Socket�������G���[
extern int  Socket_Init();

// Create Server Socket
// �߂�l�F	 1: ����
//			-1: Socket ID Error
//			-2: Open���܂���
//			-3: Socket�G���[
extern int  Socket_Open_Server(char *PName, int SId);

// Socket Accept
// �߂�l�F	1: ����
//			-3: Socket �G���[
extern int Socket_Server_Accept(int SId);

// Create Client Socket
// �߂�l�F	 1: ����
//			-1: Socket ID Error
//			-2: Open���܂���
//			-3: Socket�G���[
extern int  Socket_Open_Client(char *PName, char *HName, int SId);

// Read from Socket
// �߂�l�F	>0: �L���o�C�g��
//			-1: Socket ID Error
//			-4: Open����Ă��܂���
//			-5: Disconnected
extern int  Socket_Recv(int SId, char *RecvBuf);

// Read from Socket
// �߂�l�F	 1: ����
//			-1: Socket ID Error
//			-4: Open����Ă��܂���
extern int  Socket_Send(int SId, char *SendBuf, int len);

// Close Socket
// �߂�l�F	 1: ����
//			-1: Socket ID Error
//			-4: Open����Ă��܂���
//			-7: Socket �I���G���[
extern int  Socket_Close(int SId);

// Socket�I��
extern void Socket_End();

// Socket �G���[�\��
extern void SocketErrorString(int errno);
