/***********************************************************************
*             Copyright (c) 1999 NKK UNICS corporation                 *
*                         All rights reserved                          *
*                                                                      *
*  system name   : �g���C�X�����V�X�e���i�s�j�r�Q�P�j                  *
*  file   name   : Unit4.cpp                                           *
*  create        : 2000.01.06                                          *
*  update        :                                                     *
*  contents      : �f�[�^�o�͕��v���O����                              *
*  written by    : ����  �b��(NKK unics Corp.)                         *
*  reviced ver   : 1.0                                                 *
***********************************************************************/
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <dir.h>
#include <math.h>
#include <shellapi.h>

#include "Unit1.h"
#include "Unit3.h"
#include "Unit4.h"
int CurLine;
int PageBreakFlag;
char CDPath[256];
char path[256];
char path2[256];
char path3[256];
FILE *stream;
FILE *stream2;
FILE *stream3;
int PageNm;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//Excel�iX-R�Ǘ��}.xls�j �N��
bool __fastcall TForm1::Excel_Write()
{
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\X-R�Ǘ��}.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);

}


//---------------------------------------------------------------------------
//�f�[�^�o��
int __fastcall TForm1::Write_CSVMain(void)
{
	int i,n;
    int flag;

    flag = 0;

    //�J�����g�f�B���N�g���̎擾
    strcpy(CDPath, "X:\\");	// �l��Ԃ��`��: X:\ �ŕ�����𖞂���
    CDPath[0] = 'A' + getdisk();	// X �����݂̃h���C�u���ɒu��������
    getcurdir(0, CDPath+3);	// �����񕔕��̎c��ɃJ�����g�f�B���N�g����ǉ�

    PageNm = 0;

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\data.csv");
    strcpy(path2,CDPath);
    strcat(path2, "\\data2.csv");
    strcpy(path3,CDPath);
    strcat(path3, "\\data3.csv");
    if( ((stream = fopen( path, "w+" )) != NULL ) &&
    	((stream2 = fopen( path2, "w+" )) != NULL ) &&
        ((stream3 = fopen( path3, "w+" )) != NULL ) 		){	//�����̧�ق���݂ł����ꍇ

    	//KD01 ���[�h���������@ ����
        for ( i = 0; i <= 15; i++ ) {
            if ( Check_Print(i) ==1 ) {
				n = Search_KD(i);
        		if ( n > 0 ) {
        			//�o��
        			Write_CSV(i);
        		}
            } else {
            	n = 0;
            }
    		if ( n > 0 || flag > 0 ) flag = 1;
        }
        if ( flag == 0 ) {
        //�������� 0��
        	//�R���g���[���f�[�^ �y�[�W��
        	fprintf(stream,"0\n%d\n",PageNm);
			// �t�@�C�������
			fclose(stream);
			fclose(stream2);
			fclose(stream3);
			return(0);
        } else {

        	//�R���g���[���f�[�^ �y�[�W��
        	fprintf(stream,"1\n%d\n",PageNm);
			// �t�@�C�������
			fclose(stream);
			fclose(stream2);
			fclose(stream3);
			return(1);
        }

	} else {  //̧�ق̵���݂Ɏ��s�����ꍇ
		fclose(stream);
		fclose(stream2);
		fclose(stream3);
		return(-1);
	}



}

//testItem�i�������ځj
void __fastcall TForm1::Write_CSV(int testItem)
{
    Query1->First();
	CurLine = 0;
    PageBreakFlag = 0;
    FormatCAL();
    
	//1�s���̃f�[�^��ǂݍ���
	ReadLineData(testItem);
    //MIN,MAX,StartYMD,EndYMD,StartLOTNO,EndLOTNO,X_AVE_MIN,X_AVE_MAX,R_MIN,R_MAX
    if ( KD.SOKUTEI_1 <= KD.SOKUTEI_2 ) {
    	CALD.MIN = KD.SOKUTEI_1;
    	CALD.MAX = KD.SOKUTEI_2;
    } else {
    	CALD.MIN = KD.SOKUTEI_2;
    	CALD.MAX = KD.SOKUTEI_1;
    }
    CALD.StartYMD = KD.KENSA_YMD;
    CALD.EndYMD = KD.KENSA_YMD;
    CALD.StartLOTNO = KD.LOTNO;
    CALD.EndLOTNO = KD.LOTNO;
    CALD.X_AVE_MIN = KD.X_AVE;
    CALD.X_AVE_MAX = KD.X_AVE;
    CALD.R_MIN = KD.R;
    CALD.R_MAX = KD.R;
	////�Ђ̌v�Z�Ɏg�p
	//CALD.SGM_n = 2;
	//CALD.SGM_x = KD.SOKUTEI_1 + KD.SOKUTEI_2;
	//CALD.SGM_x2 = ( KD.SOKUTEI_1 * KD.SOKUTEI_1 ) + ( KD.SOKUTEI_2 * KD.SOKUTEI_2 );
    ////���ϒl
	//CALD.X_AVE_AVE = KD.X_AVE;
	//CALD.R_AVE = KD.R;

	while( 1 ){
        CurLine++;

        //�f�[�^�@csv�ɏo��
        WriteLineData01(testItem);

		//MIN,MAX,StartYMD,EndYMD,StartLOTNO,EndLOTNO,X_AVE_MIN,X_AVE_MAX,R_MIN,R_MAX �̔��f
        if( KD.SOKUTEI_1 <= KD.SOKUTEI_2 ) {
        	if ( CALD.MIN > KD.SOKUTEI_1 ) CALD.MIN = KD.SOKUTEI_1;
			if ( CALD.MAX < KD.SOKUTEI_2 ) CALD.MAX = KD.SOKUTEI_2;
        } else {
        	if ( CALD.MIN > KD.SOKUTEI_2 ) CALD.MIN = KD.SOKUTEI_2;
			if ( CALD.MAX < KD.SOKUTEI_1 ) CALD.MAX = KD.SOKUTEI_1;
        }
        if ( PageBreakFlag == 1 || CALD.StartYMD > KD.KENSA_YMD ) CALD.StartYMD = KD.KENSA_YMD;
        if ( PageBreakFlag == 1 || CALD.EndYMD < KD.KENSA_YMD ) CALD.EndYMD = KD.KENSA_YMD;
        if ( PageBreakFlag == 1 || CALD.StartLOTNO > KD.LOTNO ) CALD.StartLOTNO = KD.LOTNO;
        if ( PageBreakFlag == 1 || CALD.EndLOTNO < KD.LOTNO ) CALD.EndLOTNO = KD.LOTNO;
        if ( PageBreakFlag == 1 || CALD.X_AVE_MIN > KD.X_AVE ) CALD.X_AVE_MIN = KD.X_AVE;
        if ( PageBreakFlag == 1 || CALD.X_AVE_MAX < KD.X_AVE ) CALD.X_AVE_MAX = KD.X_AVE;
        if ( PageBreakFlag == 1 || CALD.R_MIN > KD.R ) CALD.R_MIN = KD.R;
        if ( PageBreakFlag == 1 || CALD.R_MAX < KD.R ) CALD.R_MAX = KD.R;

        //�Ђ̌v�Z�Ɏg�p
        CALD.SGM_n += 2;
        CALD.SGM_x += KD.SOKUTEI_1 + KD.SOKUTEI_2;
        CALD.SGM_x2 += (( KD.SOKUTEI_1 * KD.SOKUTEI_1 ) + ( KD.SOKUTEI_2 * KD.SOKUTEI_2 ));
    	//���ϒl
		CALD.X_AVE_AVE += KD.X_AVE;
		CALD.R_AVE += KD.R;

        PageBreakFlag = 0;
        //���y�[�W���邩�ǂ����𔻒f
        //1�y�[�W 30��
        if ( CurLine >= 30 ){
            //�� ���ϒl�̌v�Z
            SubSGM(testItem);

            //xAve �� �ڐ���v�Z
            SubXAveScale(testItem);
            //R�̖ڐ���v�Z
            SubRScale();

        	//�f�[�^�Acsv�ɏo��
            WriteLineData02(testItem);
            PageNm++;
			CurLine = 0;
        	PageBreakFlag = 1;

            //CAL�̏�����
            FormatCAL();
        }

        //�J�����g���R�[�h�����̍s�ֈړ�
        //�Ō�̍s�Ȃ�I��
        Query1->Next();
        if ( Query1->Eof ) {
        	break;
        }

		//1�s���̃f�[�^��ǂݍ���
		ReadLineData(testItem);

    }

	if ( PageBreakFlag == 0 ){
        //�� ���ϒl�̌v�Z
        SubSGM(testItem);

		//xAve �� �ڐ���v�Z
        SubXAveScale(testItem);
		//R�̖ڐ���v�Z
        SubRScale();

		//�f�[�^�Acsv�ɏo��
		WriteLineData02(testItem);
        PageNm++;
		CurLine = 0;
		PageBreakFlag = 1;

        //CAL�̏�����
        FormatCAL();
    }
    
}

//---------------------------------------------------------------------------
//CAL�̏�����
void __fastcall TForm1::FormatCAL(void)
{
	CALD.StartYMD 		= "";		// �J�n������
	CALD.EndYMD 			= "";		// �I��������
	CALD.StartLOTNO 		= "";		// �J�n���b�gNo
	CALD.EndLOTNO 		= "";		// �I�����b�gNo
	CALD.MIN 			= 0;       	// �ŏ��l
	CALD.MAX 			= 0;       	// �ő�l
	CALD.X_AVE_MIN 		= 0;       	// X���ϒl �ŏ��l
	CALD.X_AVE_MAX 		= 0;       	// X���ϒl �ő�l
	CALD.X_AVE_AVE 		= 0;       	// X���ϒl ���ϒl
	CALD.R_MIN 			= 0;       	// R �ŏ��l
	CALD.R_MAX 			= 0;       	// R �ő�l
	CALD.R_AVE 			= 0;       	// R ���ϒl
	CALD.X_AVE_ScaleMin 	= 0;   		// X���ϒl �ڐ���̍ŏ��l
	CALD.X_AVE_ScaleMax 	= 0;   		// X���ϒl �ڐ���̍ő�l
	CALD.X_AVE_Scale 	= 0;      	// X���ϒl �ڐ���̊Ԋu
	CALD.R_ScaleMin 		= 0;       	// R �ڐ���̍ŏ��l
	CALD.R_ScaleMax 		= 0;       	// R �ڐ���̍ő�l
	CALD.R_Scale 		= 0;       	// R �ڐ���̊Ԋu
	CALD.SGM 			= 0;
	CALD.SGM_x 			= 0;
	CALD.SGM_x2 			= 0;
	CALD.SGM_n 			= 0;
	CALD.k 				= 0;
	CALD.Cp 				= 0;
	CALD.Cpk 			= 0;
}

//---------------------------------------------------------------------------
//�Ђ̌v�Z
void __fastcall TForm1::SubSGM(int testItem)
{
	double T,M;
	double TX,MX;

	//CALD.SGM_n = CALD.SGM_n - 2;

	//���ϒl
	CALD.X_AVE_AVE = CALD.X_AVE_AVE / ( CurLine * 1.0 );
	CALD.R_AVE = CALD.R_AVE / ( CurLine * 1.0 );

    //�Ђ̌v�Z
	CALD.SGM = (( CALD.SGM_n * CALD.SGM_x2 ) - ( CALD.SGM_x * CALD.SGM_x ))
    			 / ( CALD.SGM_n * ( CALD.SGM_n - 1 ) * 1.0 );
    CALD.SGM = sqrt(CALD.SGM);

    //k Cp Cpk �̌v�Z
	switch(testItem)
	{
        //�����K�i
		case  0: //���[�h������
		case  1: //�u���V��
		case  2: //�u���V��(�c����)
		case  5: //���|��d
		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
		case 10: //��R��
		case 11: //�Ȃ�����
		case 12: //����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
		case 14: //��R��(L)      //2002/12/07 E.Takase
		case 15: //��R��(R)      //2002/12/07 E.Takase
            //�K�i��
            T = KD.KIKAK_MAX - KD.KIKAK_MIN;
            //�K�i�̒��S
        	M = KD.KIKAK_MIN + (( KD.KIKAK_MAX - KD.KIKAK_MIN ) / 2.0);
            //�΍��w��
            MX = ( M - ( CALD.SGM_x / ( CALD.SGM_n * 1.0 )));
            if ( MX < 0 ) {
				MX = MX * -1.0;
            }
            CALD.k = MX / ( T / 2.0 );
            //2003/07/22 E.Takase
            if ( CALD.SGM == 0 ) {
				CALD.Cp = 0;
				CALD.Cpk = 0;
            } else {
				CALD.Cp = T / ( CALD.SGM * 6.0 );
				CALD.Cpk = ( 1 - CALD.k ) * ( T / ( CALD.SGM * 6.0 ));
            }
        	break;

        //����K�i
        case  3: //���[�h����t��R
            TX = (( CALD.SGM_x / ( CALD.SGM_n * 1.0 )) - KD.KIKAK_MAX );
            if ( TX < 0 ) {
            	TX = TX * -1.0;
            }
			CALD.Cp = TX / ( CALD.SGM * 3.0 );
            CALD.Cpk = 0;
			CALD.k = 0;
            break;
        //�����K�i
        case  4:  //���[�h����t���x
            TX = ( KD.KIKAK_MIN - ( CALD.SGM_x / ( CALD.SGM_n * 1.0 )));
            if ( TX < 0 ) {
				TX = TX * -1.0;
            }
			CALD.Cp = TX / ( CALD.SGM * 3.0 );
            CALD.Cpk = 0;
			CALD.k = 0;
            break;
        default :
			CALD.k = 0;
			CALD.Cp = 0;
			CALD.Cpk = 0;
        	break;
    }

    //UCL,LCL
    CALD.X_UCL = CALD.X_AVE_AVE + ( 3.0 * CALD.SGM );
    CALD.X_LCL = CALD.X_AVE_AVE - ( 3.0 * CALD.SGM );
    CALD.R_UCL = CALD.R_AVE + ( 3.0 * CALD.SGM );


}


//---------------------------------------------------------------------------
//XAve �ڐ���̌v�Z
void __fastcall TForm1::SubXAveScale(int testItem)
{
    int i,i2;
    double x;
    double s,s2;

    //UCL,LCL���`�F�b�N
    if ( CALD.X_AVE_MIN > CALD.X_UCL ) CALD.X_AVE_MIN = CALD.X_UCL;
    if ( CALD.X_AVE_MAX < CALD.X_UCL ) CALD.X_AVE_MAX = CALD.X_UCL;
    if ( CALD.X_AVE_MIN > CALD.X_LCL ) CALD.X_AVE_MIN = CALD.X_LCL;
    if ( CALD.X_AVE_MAX < CALD.X_LCL ) CALD.X_AVE_MAX = CALD.X_LCL;

    //�ڐ���̍ŏ��l�A�ő�l����
	switch(testItem)
	{
        //�����K�i
		case  0: //���[�h������
		case  1: //�u���V��
		case  2: //�u���V��(�c����)
		case  5: //���|��d
		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
		case 10: //��R��
		case 11: //�Ȃ�����
		case 12: //����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
		case 14: //��R��(L)      //2002/12/07 E.Takase
		case 15: //��R��(R)      //2002/12/07 E.Takase
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;

       	break;

        //����K�i
        case  3: //���[�h����t��R
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
			//�ŏ��l CALD.X_AVE_MIN�������_�ȉ��؂�̂�
	    	CALD.X_AVE_ScaleMin = int(CALD.X_AVE_MIN);
       	break;

        //�����K�i
        case  4:  //���[�h����t���x
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
		    //�ő�l CALD.X_AVE_MAX�������_�ȉ��؂�グ
		    if ( CALD.X_AVE_MAX - (int(CALD.X_AVE_MAX)) > 0 ) {
		    	CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX)) + 1;
		    } else {
		        CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX));
		    }
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;

       	break;

        default :
			CALD.X_AVE_MIN = KD.KIKAK_MIN;
			CALD.X_AVE_MAX = KD.KIKAK_MAX;
	    	CALD.X_AVE_ScaleMax = CALD.X_AVE_MAX;
	    	CALD.X_AVE_ScaleMin = CALD.X_AVE_MIN;
        	break;
    }


    //�ڐ���̃X�P�[��������
    CALD.X_AVE_Scale = (CALD.X_AVE_ScaleMax - CALD.X_AVE_ScaleMin) / (XScaleNM * 1.0);

/* 20000322
    //UCL,LCL���`�F�b�N
    if ( CALD.X_AVE_MIN > CALD.X_UCL ) CALD.X_AVE_MIN = CALD.X_UCL;
    if ( CALD.X_AVE_MAX < CALD.X_UCL ) CALD.X_AVE_MAX = CALD.X_UCL;
    if ( CALD.X_AVE_MIN > CALD.X_LCL ) CALD.X_AVE_MIN = CALD.X_LCL;
    if ( CALD.X_AVE_MAX < CALD.X_LCL ) CALD.X_AVE_MAX = CALD.X_LCL;

	//�ŏ��l CALD.X_AVE_MIN�������_�ȉ��؂�̂�
    CALD.X_AVE_ScaleMin = (int(CALD.X_AVE_MIN));
    //�ő�l CALD.X_AVE_MAX�������_�ȉ��؂�グ
    if ( CALD.X_AVE_MAX - (int(CALD.X_AVE_MAX)) > 0 ) {
    	CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX)) + 1;
    } else {
        CALD.X_AVE_ScaleMax = (int(CALD.X_AVE_MAX));
    }

    x = CALD.X_AVE_ScaleMax - CALD.X_AVE_ScaleMin;
    i = 1;
    s = ScaleINI * i;
    while( 1 ){
    	if ( x < ( XScaleNM * s ) ) {
        	CALD.X_AVE_Scale = s;
        	break;
        } else {
            s = s * 2;
        	i++;
        }

    }

    //�X�P�[�� 0.125 ��� ���������ėǂ���
    if ( CALD.X_AVE_Scale <= ScaleINI ) {
        x = CALD.X_AVE_MAX - CALD.X_AVE_MIN;
        //s2 = ScaleINI;
        //s = ( ScaleINI * 4 ) / ( 5.0 );
        s2 = CALD.X_AVE_Scale;
        s = ScaleINI;
        i = 0;
        while ( 1 ) {
        	if ( x >= ( XScaleNM * s ) ) {
            	CALD.X_AVE_Scale = s2;
        		break;
        	} else {
                s2 = s;
            	if ( ( i % 4 ) == 0 ) {
                	s = ( s * 4 ) / 5.0;
                } else {
                	s = s / 2.0;
                }
        		i++;
        	}
        }
        i2 = i;

        //CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin
        i = 1;
        x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MIN < x ) {
            	CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            }
        }
        if ( CALD.X_AVE_MAX > ( CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * ( XScaleNM-1 ) )) ) {
            //�X�P�[�� �v�Z������
        	if ( (( i2 - 2 ) % 4 ) == 0 ) {
            	CALD.X_AVE_Scale = ( CALD.X_AVE_Scale * 5 ) / 4.0;
            } else {
            	CALD.X_AVE_Scale = CALD.X_AVE_Scale * 2.0;
            }
        	i = 1;
        	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MIN < x ) {
            		CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                	break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            	}
        	}
        }
    	CALD.X_AVE_ScaleMax = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * ( XScaleNM-1 ) );
    }
*/

/************************************************************************
    //�X�P�[�� 0.125 ��� ���������ėǂ���
    if ( CALD.X_AVE_Scale <= ScaleINI ) {
        x = CALD.X_AVE_MAX - CALD.X_AVE_MIN;
    	i = 2;
    	s = ScaleINI / ( i * 1.0 );
    	while( 1 ){
    		if ( x > ( XScaleNM * s ) ) {
        		CALD.X_AVE_Scale = s * 2;
        		break;
        	} else {
            	s = s / 2.0;
        		i++;
        	}
    	}

        //CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin
        i = 1;
        x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MIN <= x ) {
            	CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            }
        }

        i = 1;
        x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
        while ( 1 ) {
        	if ( CALD.X_AVE_MAX >= x ) {
            	CALD.X_AVE_ScaleMax = x + CALD.X_AVE_Scale;
                break;
            } else {
            	i++;
            	x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
            }
        }
        //CALD.X_AVE_Scale OK���`�F�b�N
        if ((CALD.X_AVE_ScaleMax-CALD.X_AVE_ScaleMin)>(XScaleNM*CALD.X_AVE_Scale) ) {
        	CALD.X_AVE_Scale = CALD.X_AVE_Scale * 2;
        
        	//CALD.X_AVE_ScaleMax, CALD.X_AVE_ScaleMin ������x������
        	i = 1;
        	x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MIN <= x ) {
            		CALD.X_AVE_ScaleMin = x - CALD.X_AVE_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMin + ( CALD.X_AVE_Scale * i );
            	}
        	}

        	i = 1;
        	x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
        	while ( 1 ) {
        		if ( CALD.X_AVE_MAX >= x ) {
            		CALD.X_AVE_ScaleMax = x + CALD.X_AVE_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.X_AVE_ScaleMax - ( CALD.X_AVE_Scale * i );
            	}
        	}
        }
    }

************************************************************************/

}

//---------------------------------------------------------------------------
//R �ڐ���̌v�Z
void __fastcall TForm1::SubRScale(void)
{
    int i,i2;
    double x;
    double s,s2;

    //UCL���`�F�b�N
    if ( CALD.R_MIN > CALD.R_UCL ) CALD.R_MIN = CALD.R_UCL;
    if ( CALD.R_MAX < CALD.R_UCL ) CALD.R_MAX = CALD.R_UCL;

    // R_MIN 0�ŌŒ�
    CALD.R_MIN = 0;

	//�ŏ��l CALD.R_MIN�������_�ȉ��؂�̂�
    CALD.R_ScaleMin = (int(CALD.R_MIN));
    //�ő�l CALD.R_MAX�������_�ȉ��؂�グ
    if ( CALD.R_MAX - (int(CALD.R_MAX)) > 0 ) {
    	CALD.R_ScaleMax = (int(CALD.R_MAX)) + 1;
    } else {
        CALD.R_ScaleMax = (int(CALD.R_MAX));
    }

    x = CALD.R_ScaleMax - CALD.R_ScaleMin;
    i = 1;
    s = ScaleINI * i;
    while( 1 ){
    	if ( x <= ( ( RScaleNM-1 )  * s ) ) {

        	CALD.R_Scale = s;
            CALD.R_ScaleMax = CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) );
        	break;
        } else {
            s = s * 2;
        	i++;
        }

    }


    //�X�P�[�� 0.125 ��� ���������ėǂ���
    if ( CALD.R_Scale <= ScaleINI*2 ) {
        x = CALD.R_MAX - CALD.R_MIN;
        //s2 = ScaleINI;
        //s = ( ScaleINI * 4 ) / ( 5.0 );
        s2 = CALD.R_Scale;
        s = ScaleINI;
        i = 0;
        while ( 1 ) {
        	if ( x >= ( ( RScaleNM-1 )  * s ) ) {
            	CALD.R_Scale = s2;
        		break;
        	} else {
                s2 = s;
            	if ( ( i % 4 ) == 0 ) {
                	s = ( s * 4 ) / 5.0;
                } else {
                	s = s / 2.0;
                }
        		i++;
        	}
        }
        i2 = i;

        //CALD.R_ScaleMax, CALD.R_ScaleMin
        i = 1;
        x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MIN < x ) {
            	CALD.R_ScaleMin = x - CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            }
        }
        if ( CALD.R_MAX > ( CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) )) ) {
            //�X�P�[�� �v�Z������
        	if ( (( i2 - 2 ) % 4 ) == 0 ) {
            	CALD.R_Scale = ( CALD.R_Scale * 5 ) / 4.0;
            } else {
            	CALD.R_Scale = CALD.R_Scale * 2.0;
            }
        	i = 1;
        	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MIN < x ) {
            		CALD.R_ScaleMin = x - CALD.R_Scale;
                	break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            	}
        	}
        }
    	CALD.R_ScaleMax = CALD.R_ScaleMin + ( CALD.R_Scale * ( RScaleNM-1 ) );
    }

/******************************************************************************
    //�X�P�[�� 0.125 ��� ���������ėǂ���
    if ( CALD.R_Scale <= ScaleINI * 2 ) {
        x = CALD.R_MAX - CALD.R_MIN;
    	i = 2;
    	s = ScaleINI / ( i * 1.0 );
    	while( 1 ){
    		if ( x > ( RScaleNM * s ) ) {
        		CALD.R_Scale = s * 2;
        		break;
        	} else {
            	s = s / 2.0;
        		i++;
        	}
    	}

        //CALD.R_ScaleMax, CALD.R_ScaleMin
        i = 1;
        x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MIN <= x ) {
            	CALD.R_ScaleMin = x - CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            }
        }

        i = 1;
        x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
        while ( 1 ) {
        	if ( CALD.R_MAX >= x ) {
            	CALD.R_ScaleMax = x + CALD.R_Scale;
                break;
            } else {
            	i++;
            	x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
            }
        }
        //CALD.R_Scale OK���`�F�b�N
        if ((CALD.R_ScaleMax-CALD.R_ScaleMin)>(RScaleNM*CALD.R_Scale) ) {
        	CALD.R_Scale = CALD.R_Scale * 2;

        	//CALD.R_ScaleMax, CALD.R_ScaleMin ������x������
        	i = 1;
        	x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MIN <= x ) {
            		CALD.R_ScaleMin = x - CALD.R_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMin + ( CALD.R_Scale * i );
            	}
        	}

        	i = 1;
        	x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
        	while ( 1 ) {
        		if ( CALD.R_MAX >= x ) {
            		CALD.R_ScaleMax = x + CALD.R_Scale;
                    break;
            	} else {
            		i++;
            		x = CALD.R_ScaleMax - ( CALD.R_Scale * i );
            	}
        	}
        }
    }
******************************************************************************/


}    


//---------------------------------------------------------------------------
//�f�[�^�@ csv�o��
void __fastcall TForm1::WriteLineData01(int testItem)
{
	//������ ���b�gNo ����l1 ����l2 XAve R
	fprintf(stream2,"%s,%s,%lf,%lf,%lf,%lf\n",
		InsSEPA(KD.KENSA_YMD).c_str(),
        KD.LOTNO.c_str(),
        KD.SOKUTEI_1,
        KD.SOKUTEI_2,
        KD.X_AVE,
        KD.R
    );

}

//---------------------------------------------------------------------------
//�f�[�^�A csv�o��
void __fastcall TForm1::WriteLineData02(int testItem)
{
    //���y�[�W�t���O
    fprintf(stream2,"*,0,0,0,0,0\n");

	//�^�C�g��
    //���Ӑ�i�� ���荀�� ������ �v���� �J�n������  �I��������
	fprintf(stream3,"%s,%s,%d,%s,%s,%s\n",
		KD.DTKSHIN.c_str(),
        KENSA_NAME(testItem).c_str(),
        (CurLine*2),
        KENSA_KIKI(testItem).c_str(),
        InsSEPA(CALD.StartYMD).c_str(),
        InsSEPA(CALD.EndYMD).c_str()
    );

    //�ގ��� �K�i ����K�i �����K�i ����P�� �J�n���b�gNo �I�����b�gNo
	fprintf(stream3,"%s,%d,%lf,%lf,%s,%s,%s\n",
        KD.ZISNAM.c_str(),
        KENSA_KIKAKU(testItem),
        KD.KIKAK_MAX,
        KD.KIKAK_MIN,
        KENSA_TANI(testItem).c_str(),
        CALD.StartLOTNO.c_str(),
        CALD.EndLOTNO.c_str()
    );

    //min max �����_�ȉ�����
	fprintf(stream3,"%lf,%lf,%d,%s,%s\n",
    	CALD.MIN,
    	CALD.MAX,
        KENSA_KETA(testItem),
        KENSA_SYOSIKI(KENSA_KETA(testItem)).c_str(),
        KENSA_SYOSIKI(KENSA_KETA(testItem) + 1).c_str()
    );

    //XAve �̖ڐ���
	fprintf(stream3,"%lf,%lf,%lf\n",
    	CALD.X_AVE_Scale,
    	CALD.X_AVE_ScaleMin,
        CALD.X_AVE_ScaleMax
    );

    //R �̖ڐ���
	fprintf(stream3,"%lf,%lf,%lf\n",
    	CALD.R_Scale,
    	CALD.R_ScaleMin,
        CALD.R_ScaleMax
    );
	//min max �����_�ȉ�����
	fprintf(stream3,"%d,%s,%s,%s,%s\n",
		KENSA_KETA(testItem),
		KENSA_SYOSIKI(KENSA_KETA(testItem)).c_str(),
		KENSA_SYOSIKI(KENSA_KETA(testItem) + 1).c_str(),
        Form1->ConvKETA2(3,CALD.SGM).c_str(),
        Form1->ConvKETA2(3,CALD.k).c_str()
    );

    //R_AVE X_AVE_AVE SGM SGM_x k Cp Cpk X_UCL X_LCL R_UCL
	fprintf(stream3,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
    	CALD.R_AVE,
    	CALD.X_AVE_AVE,
    	CALD.SGM,
    	CALD.k,
    	CALD.Cp,
        CALD.Cpk,
    	CALD.X_UCL,
    	CALD.X_LCL,
        CALD.R_UCL
    );

}

//---------------------------------------------------------------------------
//�������ږ�
AnsiString __fastcall TForm1::KENSA_NAME(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{
		case  0: //���[�h������
            sBuf = "���[�h������";
			return(sBuf);
        	break;

		case  1: //�u���V��
            sBuf = "�u���V��";
			return(sBuf);
        	break;

		case  2: //�u���V��(�c����)
            sBuf = "�u���V��(�c����)";
			return(sBuf);
        	break;

		case  3: //���[�h����t��R
            sBuf = "���[�h����t��R";
			return(sBuf);
        	break;

		case  4: //���[�h����t���x
            sBuf = "���[�h����t���x";
			return(sBuf);
        	break;

		case  5: //���|��d
            sBuf = "���|��d";
			return(sBuf);
        	break;

		case  6: //�d�x(HsC ����)
            sBuf = "�d�x(HsC ����)";
			return(sBuf);
        	break;

		case  7: //�d�x(HsC ����)
            sBuf = "�d�x(HsC ����)";
			return(sBuf);
        	break;

		case  8: //�d�x(HsD ����)
            sBuf = "�d�x(HsD ����)";
			return(sBuf);
        	break;

		case  9: //�d�x(HsD ����)
            sBuf = "�d�x(HsD ����)";
			return(sBuf);
        	break;

		case 10: //��R��
            sBuf = "��R��";
			return(sBuf);
        	break;

		case 11: //�Ȃ�����
            sBuf = "�Ȃ�����";
			return(sBuf);
        	break;

		case 12: //����
            sBuf = "����";
			return(sBuf);
        	break;

		case 13: //�Ȃ�����(����) //200212/07 E.Takase
            sBuf = "�Ȃ�����(����)";
			return(sBuf);
        	break;

		case 14: //��R��(L) //200212/07 E.Takase
            sBuf = "��R��(L)";
			return(sBuf);
        	break;

		case 15: //��R��(R) //200212/07 E.Takase
            sBuf = "��R��(R)";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//����P��
AnsiString __fastcall TForm1::KENSA_TANI(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{
		case  0://���[�h������
		case  1: //�u���V��
		case  2: //�u���V��(�c����)
            sBuf = "mm";
			return(sBuf);
        	break;

		case  3: //���[�h����t��R
            sBuf = "mV/A";
			return(sBuf);
        	break;

		case  4: //���[�h����t���x
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
			}
			break;

		case  5: //���|��d
            sBuf = "�\";
			return(sBuf);
        	break;

		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
            sBuf = "HsC";
			return(sBuf);
        	break;


		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
            sBuf = "HsD";
			return(sBuf);
        	break;

		case 10: //��R��
		case 14: //��R��(L) //2002/12/07 E.Takase
		case 15: //��R��(R) //2002/12/07 E.Takase
            sBuf = "�ʃ��Ecm";
			return(sBuf);
        	break;

		case 11: //�Ȃ�����
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf/cm2";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N/cm2";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
				case 4:
		            sBuf = "N/mm2";
					return(sBuf);
		        	break;
			}
            break;

        //2003/07/22 E.Takase �P�ʒǉ�
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
			switch(int(KD.TANI))
			{
				case 1:
		            sBuf = "Kgf/cm2";
					return(sBuf);
		        	break;
				case 2:
		            sBuf = "N/cm2";
					return(sBuf);
		        	break;
				case 3:
		            sBuf = "MPa";
					return(sBuf);
		        	break;
				case 4:
		            sBuf = "N/mm2";
					return(sBuf);
		        	break;
				case 5:
		            sBuf = "N";
					return(sBuf);
		        	break;
			}
            break;
		case 12: //����
            sBuf = "N";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//�v����
AnsiString __fastcall TForm1::KENSA_KIKI(int testItem)
{
    AnsiString sBuf;
	switch(testItem)
	{

		case  0: //���[�h���������@
            sBuf = "�m�M�X";
			return(sBuf);
        	break;

		case  1: //�u���V��
		case  2: //�u���V��(�c����)
            sBuf = "�}�C�N�����[�^";
			return(sBuf);
        	break;

		case  3: //���[�h����t��R
            sBuf = "��t��R�����";
			return(sBuf);
        	break;

		case  4: //���[�h����t���x
		case 12: //����
            sBuf = "�ޗ������@";
			return(sBuf);
        	break;

		case  5: //���|��d
            sBuf = "�}�C�N�����[�^�A�d�q�V��";
			return(sBuf);
        	break;

		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
            sBuf = "C�^�V���A�d�x�v";
			return(sBuf);
        	break;

		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
            sBuf = "D�^�V���A�d�x�v";
			return(sBuf);
        	break;

		case 10: //��R��
		case 14: //��R��(L) //2002/12/07 E.Takase
		case 15: //��R��(R) //2002/12/07 E.Takase
            sBuf = "��R�������";
			return(sBuf);
        	break;

		case 11: //�Ȃ�����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
            sBuf = "�ޗ������@";
			return(sBuf);
        	break;

        default :
            sBuf = " ";
			return(sBuf);
        	break;
    }
	sBuf = " ";
	return(sBuf);

}

//---------------------------------------------------------------------------
//�����K�i(1) �����K�i(2) ����K�i(3)
int __fastcall TForm1::KENSA_KIKAKU(int testItem)
{
	switch(testItem)
	{
		case  0:// ���[�h������
		case  1: //�u���V��
		case  2: //�u���V��(�c����)
		case  5: //���|��d
		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
		case 10: //��R��
		case 11: //�Ȃ�����
		case 12: //����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
		case 14: //��R��(L)      //2002/12/07 E.Takase
		case 15: //��R��(R)      //2002/12/07 E.Takase
			return(1);
        	break;

		case  3: //���[�h����t��R
			return(3);
        	break;

		case  4: //���[�h����t���x
			return(2);
        	break;

        default :
			return(1);
        	break;
    }

}

//---------------------------------------------------------------------------
//�����_�ȉ��̌���
int __fastcall TForm1::KENSA_KETA(int testItem)
{
	switch(testItem)
	{
		case  0: //���[�h������
		case  5: //���|��d
			return(2);
         	break;

		case  1: //�u���V��
		case  2: //�u���V��(�c����)
			return(3);
         	break;

		case  3: //���[�h����t��R
		case  4: //���[�h����t���x
		case  8: //�d�x(HsD ����)
		case  9: //�d�x(HsD ����)
		case 11: //�Ȃ�����
		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
			return(1);
         	break;

		case  6: //�d�x(HsC ����)
		case  7: //�d�x(HsC ����)
		case 10: //��R��
		case 14: //��R��(L) //2002/12/07 E.Takase
		case 15: //��R��(R) //2002/12/07 E.Takase
		case 12: //����
			return(0);
         	break;

        default :
			return(3);
         break;
    }

}

//---------------------------------------------------------------------------
//����(ex "#0.000")
AnsiString __fastcall TForm1::KENSA_SYOSIKI(int n)
{
	int i;
    AnsiString sBuf;

    sBuf = "";
    for ( i = 1; i <= n; i++ ) {
    	sBuf = sBuf + "0";
    }

    if ( n > 0 ) {
    	sBuf = "#0." + sBuf;
    } else {
    	sBuf = "0";
    }
    return(sBuf);

}

//---------------------------------------------------------------------------
//������邩�𔻒f
int __fastcall TForm1::Check_Print(int testItem)
{
	switch(testItem)
	{
		case  0: //���[�h������
			if ( Form1->CheckBox1->Checked == True ) return(1);
			else return(0);
        	break;

		case  1: //�u���V��
			if ( Form1->CheckBox2->Checked == True ) return(1);
			else return(0);
        	break;

		case  2: //�u���V��(�c����)
			if ( Form1->CheckBox3->Checked == True ) return(1);
			else return(0);
        	break;

		case  3: //���[�h����t��R
			if ( Form1->CheckBox4->Checked == True ) return(1);
			else return(0);
        	break;

		case  4: //���[�h����t���x
			if ( Form1->CheckBox5->Checked == True ) return(1);
			else return(0);
        	break;

		case  5: //���|��d
			if ( Form1->CheckBox6->Checked == True ) return(1);
			else return(0);
        	break;


		case  6: //�d�x(HsC ����)
			if ( Form1->CheckBox7->Checked == True ) return(1);
			else return(0);
        	break;


		case  7: //�d�x(HsC ����)
			if ( Form1->CheckBox8->Checked == True ) return(1);
			else return(0);
        	break;

		case  8: //�d�x(HsD ����)
			if ( Form1->CheckBox9->Checked == True ) return(1);
			else return(0);
        	break;

		case  9: //�d�x(HsD ����)
			if ( Form1->CheckBox10->Checked == True ) return(1);
			else return(0);
        	break;

		case 10: //��R��
            //2002/12/07 E.Takase
			//if ( Form1->CheckBox11->Checked == True ) return(1);
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN != 5 ) return(1);
			else return(0);
        	break;

		case 11: //�Ȃ�����
			if ( Form1->CheckBox12->Checked == True ) return(1);
			else return(0);
        	break;

		case 12: //����
			if ( Form1->CheckBox13->Checked == True ) return(1);
			else return(0);
        	break;

		case 13: //�Ȃ�����(����) //2002/12/07 E.Takase
			if ( Form1->CheckBox14->Checked == True ) return(1);
			else return(0);
        	break;

		case 14: //��R��(L)
            //2002/12/07 E.Takase
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN == 5 ) return(1);
			else return(0);
        	break;

		case 15: //��R��(R)
            //2002/12/07 E.Takase
			if ( Form1->CheckBox11->Checked == True && intKEIJKBN == 5 ) return(1);
			else return(0);
        	break;

        default :
			return(0);
        	break;
    }
	return(0);

}