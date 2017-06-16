//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.h>
#pragma hdrstop
#include "unit1.h"
#include "unit3.h"
#include "U_Excel.h"

char CDPath[256];
char path[256];
extern KETA_DATA KETA;  //������̌���

//---------------------------------------------------------------------------
#pragma package(smart_init)


//�b�r�u�f�[�^�쐬
bool __fastcall TForm3::CSV_Write()
{
    AnsiString sBuf;
    int i;
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    FILE *stream;

    //���Ӑ於�̎擾
    // Initial Query
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();

    // �⍇�����s
    sBuf = "select TRSNAM From SM16S ";
    sBuf += " where TRSCOD = '" + Cur_Kda1.DTKSCOD + "'";

    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    Form1->Query1->Active = true;

    if ( Form1->Query1->Bof == true && Form1->Query1->Eof ) {
        //�������� �O��
        DTKSNAM = " ";
    }
    else {
        Form1->Query1->First();
        DTKSNAM = Form1->Query1->FieldValues["TRSNAM"];
    }

    //�S���҂̎擾
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    //�₢���������s
    //�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
    sBuf = "SELECT ";
    sBuf += "TANNAM  FROM SM12S ";
    sBuf += "WHERE  TANSYA = '" + IntToStr(USER_COD) + "'" ;
    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    if( Form1->Query1->Bof == true && Form1->Query1->Eof){
        TANNAM = USER_NAM;
    } else {
        Form1->Query1->First();
        TANNAM = Form1->Query1->FieldValues["TANNAM"];
    }

    //�J�����g�f�B���N�g���̎擾
    strcpy(CDPath, "X:\\");	/* �l��Ԃ��`��: X:\ �ŕ�����𖞂��� */
    CDPath[0] = 'A' + getdisk();	/* X �����݂̃h���C�u���ɒu�������� */
    getcurdir(0, CDPath+3);	/* �����񕔕��̎c��ɃJ�����g�f�B���N�g����ǉ� */

    //�����w��i�t�H�[�}�b�g�j�����߂�
	KETA.AVE_str = ConvKETA1( KETA.AVE,KETA.SOKUTE_AVE );
	KETA.MIN_str = ConvKETA1( KETA.MIN,KETA.SOKUTE_MIN );
	KETA.MAX_str = ConvKETA1( KETA.MAX,KETA.SOKUTE_MAX );
	KETA.R_str   = ConvKETA1( KETA.R  ,KETA.SOKUTE_R   );
	KETA.SGM_str = ConvKETA2( KETA.SGM,KETA.SOKUTE_SGM ,1 );
	KETA.CP_str  = ConvKETA1( KETA.CP ,KETA.SOKUTE_CP  );
	KETA.CPK_str = ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	KETA.K_str   = ConvKETA2( KETA.K  ,KETA.SOKUTE_K  ,2 );
	KETA.P_str   = ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\data.csv");
    if( (stream = fopen( path, "w+" )) != NULL ){	//�����̧�ق���݂ł����ꍇ
        //�t�@�C���I�[�v�� �t���O
        fprintf(stream,"1\n");
        //�O���t�ڐ���̃X�P�[�� �S���Җ�
        fprintf(stream,"%d,%s\n",E_Scale,TANNAM.c_str());
        //�ȏ�A�����A��
        for ( i = 0; i < 20; i++ ) {
            fprintf(stream,"%lf,%lf,%lf\n",E_Screen_Data[0][i],E_Screen_Data[1][i],E_Screen_Data[2][i]);
        }
        //�����w��i�t�H�[�}�b�g�j
        fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				KETA.AVE_str.c_str(),
				KETA.MIN_str.c_str(),
				KETA.MAX_str.c_str(),
				KETA.R_str.c_str(),
				KETA.SGM_str.c_str(),
				KETA.CP_str.c_str(),
				KETA.CPK_str.c_str(),
				KETA.K_str.c_str(),
				KETA.P_str.c_str()
                    );


        //�q�X�g�O��������f�[�^�P
        fprintf(stream,"%s,%d,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
				Cur_Kda1.KENSA_YMD.c_str(),
				Cur_Kda1.SEQNO,
				Cur_Kda1.DTKSCOD.c_str(),
                DTKSNAM.c_str(),
				Cur_Kda1.DTKSHIN.c_str(),
				Cur_Kda1.LOTNO.c_str(),
				Cur_Kda1.HINBAN.c_str(),
				Cur_Kda1.ZISCOD.c_str(),
				Cur_Kda1.ZISNAM.c_str(),
				Cur_Kda1.HIST_SOKUT_Ori,
				Cur_Kda1.HIST_SOKUT,
				Cur_Kda1.HIST_KIKAK,
				Cur_Kda1.HIST_MIN,
				Cur_Kda1.HIST_MAX,
				Cur_Kda1.SOKUTE_SU,
				Cur_Kda1.SOKUTE_SU_Ori,
				KETA.SOKUTE_AVE,
				KETA.SOKUTE_MIN,
				KETA.SOKUTE_MAX,
				KETA.SOKUTE_R,
				KETA.SOKUTE_SGM,
				KETA.SOKUTE_CP,
				KETA.SOKUTE_CPK,
				KETA.SOKUTE_K,
				KETA.SOKUTE_P
                    );
        //�q�X�g�O��������f�[�^�Q
        for( i = 0; i < Cur_Kda1.SOKUTE_SU; i++) {
            fprintf(stream,"%lf\n",M_Kda2[i].SOKUTEI_CH);
        }
        // �t�@�C�������
        fclose(stream);
	    return(true);
 	}else{	//̧�ق̵���݂Ɏ��s�����ꍇ
		fclose(stream);
		return(false);
	}

}
//Excel �N��
bool __fastcall TForm3::Excel_Write()
{
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\�q�X�g�O�������茋��.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_MINIMIZE);
    return(retDLL);

}
//�����_�ȉ�
AnsiString __fastcall TForm3::ConvKETA1(int keta,double n)
{
    int x;
    double m;
    AnsiString str;

    //�����_�ȉ� keta��
    x = pow(10,keta);
    m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

    str = "#0." + AnsiString::StringOfChar('0', keta );

    return( str );
}
//�L������
AnsiString __fastcall TForm3::ConvKETA2(int keta,double n,int SGM_K)
{
    int x,i;
    double m;
    AnsiString str;
    AnsiString tmp_s1,tmp_s2;
    int tmp_n1,tmp_n2;
    AnsiString Formatstr;
    char test[256];
    AnsiString test2;
    int flag,pos;
    int flag_M;

    //�L������
    if ( n < 0 ) {
        //�}�C�i�X
        flag_M = -1;
        n = n * -1;
    } else {
        flag_M = 1;
    }

    if ( n >= 1 ) {
        //1�ȏ�
        flag = 1;
    } else {
        //0�ȏ�1����
        flag = 2;
    }

    switch( flag ){
        case 1:
            str = FormatFloat("#0.0#", n );
            pos = str.AnsiPos(".") - 1;
            if ( pos <  keta ) {
                Formatstr = "#0." + AnsiString::StringOfChar('0', keta-pos );
            } else {
                if ( pos == keta ) {
                    Formatstr = "#0";
                } else {
                //keta = 2, n = 1234.5 �� 1200
                    Formatstr = "#0";
                    tmp_s1 = FloatToStr((int(n)));
                    tmp_n1 = tmp_s1.Length();
                    tmp_n2 = pow(10,(tmp_n1-keta));

                    //switch( SGM_K ) {
                    //    case 1:
                    //        //SGM
                    //        KETA.SOKUTE_SGM = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //
                    //    case 2:
                    //        //K
                    //        KETA.SOKUTE_K = ((int( ((int(n)) / (tmp_n2*1.0)) + 0.5 ) )* tmp_n2) * flag_M;
                    //        break;
                    //}

                }
            }
            break;

        case 2:
            x = pow(10,keta);
            m = ( int(( n * x ) + 0.5 )) / ( x * 1.0 );

            if ( n == 0 ) {
            	Formatstr = "#0."+ AnsiString::StringOfChar('0', (keta - 1));
            } else {
            	i = 1;
            	while(1) {
            		if ( int(n*( pow(10,i))) > 0 ) {
                		break;
                	} else {
                		i++;
                	}
            	}
            	Formatstr = "#0." + AnsiString::StringOfChar('0', (i - 1 + keta));
			}
            break;
    }
    return ( Formatstr );
}

