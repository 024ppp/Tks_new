//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <dir.h>


#pragma hdrstop
#include "unit1.h"
#include "unit3.h"
#include "U_Excel.h"
#define COM_DIFF 0.000001
const int E_Nums = 300;
char CDPath[1028];
char path[1028];
double E_Standard_Scale[20] = {500, 100, 50, 20, 10, 5, 2, 1, 0.5, 0.2, 0.1, 0.05,
                           0.02, 0.01, 0.005, 0.002, 0.001, 0.0005, 0.0002, 0.0001};

//extern KDB1_DATA Tmp_KDB1;             // �I�������H���\��
//extern KETA_DATA KETA;  //������̌���
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//�b�r�u�Q�i�H���\�͒����\�j�f�[�^�쐬
bool __fastcall TForm1::CSV2_Write()
{
    AnsiString sBuf;
    int i,n;
    int Tmp_E_Scale;
    int k;
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    AnsiString KOUMOKU_J;
    AnsiString KOUMOKU_E;
    FILE *stream;
    int tmpSOKUTEI_SU1;
    int tmpSOKUTEI_SU2;
    int tmpSOKUTEI_SU3;
    int tmpSOKUTEI_SU4;

    Tmp_E_Scale = 0;
    //�J�����g�f�B���N�g���̎擾
    strcpy(CDPath, "X:\\");	/* �l��Ԃ��`��: X:\ �ŕ�����𖞂��� */
    CDPath[0] = 'A' + getdisk();	/* X �����݂̃h���C�u���ɒu�������� */
    getcurdir(0, CDPath+3);	/* �����񕔕��̎c��ɃJ�����g�f�B���N�g����ǉ� */



    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\data2.csv");
    if( (stream = fopen( path, "w+" )) != NULL ){	//�����̧�ق���݂ł����ꍇ

        //���ڐ����K�v
        for ( n = 0; n < SGr1->RowCount-1; n++ ) {
            //�O���t�X�P�[�� �ȏ� ���� �� �H���\�͑���f�[�^�P �� ���߂�
            Sub_Tmp_KDB1(n);

            //�����w��i�t�H�[�}�b�g�j�����߂�
            k = Form3->KENSASYOSIKI_Set(Tmp_KDB1.KENSA_KMK,Tmp_KDB1.JYOKEN1,Tmp_KDB1.SOKUTE_KET);

            Toukei_Tmp_KDB1( k );

            KETA.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE;
            KETA.SOKUTE_MIN = Tmp_KDB1.SOKUTE_MIN;
            KETA.SOKUTE_MAX = Tmp_KDB1.SOKUTE_MAX;
            KETA.SOKUTE_R   = Tmp_KDB1.SOKUTE_R  ;
            KETA.SOKUTE_SGM = Tmp_KDB1.SOKUTE_SGM;
            KETA.SOKUTE_CP  = Tmp_KDB1.SOKUTE_CP ;
            KETA.SOKUTE_CPK = Tmp_KDB1.SOKUTE_CPK;
            KETA.SOKUTE_K   = Tmp_KDB1.SOKUTE_K  ;
            KETA.SOKUTE_P   = Tmp_KDB1.SOKUTE_P  ;

	        KETA.R_str   = Form3->ConvKETA1( k,KETA.SOKUTE_R );
	        //KETA.R_str   = "#0.00";
	        KETA.AVE_str = Form3->ConvKETA1( k+1,KETA.SOKUTE_AVE );
	        KETA.MIN_str = Form3->ConvKETA1( k,KETA.SOKUTE_MIN );
	        KETA.MAX_str = Form3->ConvKETA1( k,KETA.SOKUTE_MAX );
	        KETA.SGM_str = Form3->ConvKETA2( 3,KETA.SOKUTE_SGM ,1 );
        	KETA.CP_str  = Form3->ConvKETA1( 2,KETA.SOKUTE_CP  );
	        KETA.K_str   = Form3->ConvKETA2( 2,KETA.SOKUTE_K ,2  );
	        KETA.CPK_str = Form3->ConvKETA1( 2,KETA.SOKUTE_CPK );
	        KETA.P_str   = Form3->ConvKETA1( 2,KETA.SOKUTE_P   );


            //�O���t�ڐ���̃X�P�[�� ��r
            if ( Tmp_E_Scale < E_Scale) Tmp_E_Scale = E_Scale;

            //���荀��
            if( Tmp_KDB1.KENSA_KMK == 6 ) {
            	if ( Tmp_KDB1.JYOKEN1 == 2 || Tmp_KDB1.JYOKEN1 == 4 ) {
            		KOUMOKU_J = "�d�x�i���ʁj";
            		KOUMOKU_E = "Hardness(S)";
                } else {
            		KOUMOKU_J = "�d�x";
            		KOUMOKU_E = "Hardness";

                }
			} else {
				KOUMOKU_J = Tmp_KDB1.KOUMOKU_J;
				KOUMOKU_E = Tmp_KDB1.KOUMOKU_E;
            }

		    //�R���~����R���̏ꍇ 2002/12/03 E.Takase
		    if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {
                tmpSOKUTEI_SU1 = Tmp_KDB1.HIST_SOKUT_Ori*2;
                tmpSOKUTEI_SU2 = Tmp_KDB1.HIST_SOKUT*2;
                tmpSOKUTEI_SU3 = Tmp_KDB1.SOKUTE_SU*2;
                tmpSOKUTEI_SU4 = Tmp_KDB1.SOKUTE_SU_Ori*2;
		    //�R���~����R���ȊO�̏ꍇ 2002/12/03 E.Takase
            } else {
                tmpSOKUTEI_SU1 = Tmp_KDB1.HIST_SOKUT_Ori;
                tmpSOKUTEI_SU2 = Tmp_KDB1.HIST_SOKUT;
                tmpSOKUTEI_SU3 = Tmp_KDB1.SOKUTE_SU;
                tmpSOKUTEI_SU4 = Tmp_KDB1.SOKUTE_SU_Ori;
            }
            //�H���\�͑���f�[�^�P �K�i�̐^�񒆂̒l +-�H
            fprintf(stream,"%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                Tmp_KDB1.TANI.c_str(),
                KOUMOKU_J.c_str(),
                KOUMOKU_E.c_str(),
				tmpSOKUTEI_SU1,
				tmpSOKUTEI_SU2,
				Tmp_KDB1.HIST_KIKAK,
				Tmp_KDB1.HIST_MIN,
				Tmp_KDB1.HIST_MAX,
				tmpSOKUTEI_SU3,
				tmpSOKUTEI_SU4,
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
            ////�H���\�͑���f�[�^�P �K�i�̐^�񒆂̒l +-�H
            //fprintf(stream,"%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
            //    Tmp_KDB1.TANI.c_str(),
            //    KOUMOKU_J.c_str(),
            //    KOUMOKU_E.c_str(),
			//	Tmp_KDB1.HIST_SOKUT_Ori,
			//	Tmp_KDB1.HIST_SOKUT,
			//	Tmp_KDB1.HIST_KIKAK,
			//	Tmp_KDB1.HIST_MIN,
			//	Tmp_KDB1.HIST_MAX,
			//	Tmp_KDB1.SOKUTE_SU,
			//	Tmp_KDB1.SOKUTE_SU_Ori,
			//	KETA.SOKUTE_AVE,
			//	KETA.SOKUTE_MIN,
			//	KETA.SOKUTE_MAX,
			//	KETA.SOKUTE_R,
			//	KETA.SOKUTE_SGM,
			//	KETA.SOKUTE_CP,
			//	KETA.SOKUTE_CPK,
			//	KETA.SOKUTE_K,
			//	KETA.SOKUTE_P
            //        );
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

        }
        // �t�@�C�������
        fclose(stream);

        //data3
        // �t�@�C�����X�V�p�ɊJ��
        strcpy(path,CDPath);
        strcat(path, "\\data3.csv");
        if( (stream = fopen( path, "w+" )) != NULL ){	//�����̧�ق���݂ł����ꍇ
            //�^�C�g�� �H���\�͑���f�[�^�P
            //�t�@�C���I�[�v�� �t���O
            fprintf(stream,"1\n");
            //���ڐ� SEQNOMAX
            fprintf(stream,"%d\n",SGr1->RowCount-1);

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



            //�쐬�� ���Ӑ�i�� ���b�gNO �ގ��R�[�h �ގ���
            fprintf(stream,"%s,%s,%s,%s,%s,%d\n",
				    Form1->DelSEPA( Form1->EdtYMD->Text).c_str(),
                    Form1->EdtHIN->Text.c_str(),
                    Form1->EdtLOT->Text.c_str(),
                    Form1->EdtZIS->Text.c_str(),
                    Form1->EdtZISNAM->Caption.c_str(),
                    Tmp_E_Scale
                        );
            // �t�@�C�������
            fclose(stream);
            return(true);
        } else {  //̧�ق̵���݂Ɏ��s�����ꍇ
		    fclose(stream);
		    return(false);
        }

 	}else{	//̧�ق̵���݂Ɏ��s�����ꍇ
		fclose(stream);
		return(false);
	}

}
//---------------------------------------------------------------------------
//Excel�Q�i�H���\�͒����\�j �N��
bool __fastcall TForm1::Excel2_Write()
{
/*
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\�H���\�͒����\.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);
*/
/*
    AnsiString FilePath;

    FilePath = CDPath;
    FilePath += "\\�H���\�͒����\.xls";

    // �A�v���P�[�V���������s���ďI����҂�
    STARTUPINFO SupInf;
    PROCESS_INFORMATION PrcsInf;

    ::GetStartupInfo(&SupInf);
    SupInf.cb = sizeof(SupInf);
    SupInf.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
    SupInf.wShowWindow = SW_SHOW;

    bool Fin = CreateProcess( FilePath.c_str(), NULL, NULL, NULL, false,
                         NORMAL_PRIORITY_CLASS, NULL, NULL, &SupInf, &PrcsInf );
    if( Fin == true ){
         WaitForSingleObject( PrcsInf.hProcess, INFINITE );
    }
*/


    STARTUPINFO stup;
    PROCESS_INFORMATION pinf;

    stup.cb=sizeof(STARTUPINFO);
    stup.lpReserved=NULL;
    stup.lpDesktop=NULL;
    stup.lpTitle=NULL;
    stup.dwFlags=STARTF_USESHOWWINDOW;
    stup.cbReserved2=0;
    stup.lpReserved2=NULL;
    stup.wShowWindow=SW_SHOW;


    char cmdline[1028];
    strcpy(path,CDPath);
    strcat(path, "\\�H���\�͒����\.xls");
    wsprintf(cmdline,"\"%s\" \"%s\"",  ExcelExePATH,path);

    BOOL flag=::CreateProcess(NULL,cmdline,NULL,NULL,0,0,NULL,NULL,&stup,&pinf);

    if( flag == true ){
         WaitForSingleObject( pinf.hProcess, INFINITE );
    }


    return(true);
    return(true);


}

//---------------------------------------------------------------------------
//�b�r�u�i�H���\�͑���j�f�[�^�쐬
bool __fastcall TForm3::CSV_Write(int flag)
{
    AnsiString sBuf;
    int i;
    AnsiString str;
    AnsiString DTKSNAM;
    AnsiString TANNAM;
    AnsiString KOUMOKU_J;
    AnsiString KOUMOKU_E;
    FILE *stream;
    int tmpSOKUTEI_SU1;
    int tmpSOKUTEI_SU2;
    int tmpSOKUTEI_SU3;
    int tmpSOKUTEI_SU4;

    //�S���҂̎擾
    Form1->Query1->Close();
    Form1->Query1->SQL->Clear();
    //�₢���������s
    //�\�[�g���� ���Ӑ溰�ށA�����\����A�g���[No�A�T���v���|�W�V����
    sBuf = "SELECT ";
    sBuf += "TANNAM  FROM SM12S ";
    sBuf += "WHERE  TANSYA = '" + IntToStr(Cur_Kdb1.UPDCHR) + "'" ;
    Form1->Query1->SQL->Add(sBuf);
    Form1->Query1->Open();
    if( Form1->Query1->Bof == true && Form1->Query1->Eof == true){
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
	KETA.K_str   = ConvKETA2( KETA.K  ,KETA.SOKUTE_K ,2  );
	KETA.CPK_str = ConvKETA1( KETA.CPK,KETA.SOKUTE_CPK );
	KETA.P_str   = ConvKETA1( KETA.P  ,KETA.SOKUTE_P   );
	//KETA.KMK_str = KENSASYOSIKI_Set(Cur_Kdb1.KENSA_KMK,Cur_Kdb1.JYOKEN1);
	KETA.KMK_str = ConvKETA1( Edt_001->FPos,0.00);


	//���荀��
	if( Cur_Kdb1.KENSA_KMK == 6 ) {
		KOUMOKU_J = "�d�x";
		KOUMOKU_E = "Hardness";
	} else {
		//�R���~����R���̏ꍇ 2002/12/03 E.Takase
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
            if ( flag == 0 ) {
		        KOUMOKU_J = Cur_Kdb1.KOUMOKU_J + "-L";
		        KOUMOKU_E = Cur_Kdb1.KOUMOKU_E + "-L";
            } else {
		        KOUMOKU_J = Cur_Kdb1.KOUMOKU_J + "-R";
		        KOUMOKU_E = Cur_Kdb1.KOUMOKU_E + "-R";
            }
        } else {
		    KOUMOKU_J = Cur_Kdb1.KOUMOKU_J;
		    KOUMOKU_E = Cur_Kdb1.KOUMOKU_E;
        }
    }

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
        fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				KETA.AVE_str.c_str(),
				KETA.MIN_str.c_str(),
				KETA.MAX_str.c_str(),
				KETA.R_str.c_str(),
				KETA.SGM_str.c_str(),
				KETA.CP_str.c_str(),
				KETA.CPK_str.c_str(),
				KETA.K_str.c_str(),
				KETA.P_str.c_str(),
				KETA.KMK_str.c_str()
                    );


        ///2003.02.13 E.Takase �R�����g�ɂ���
        ////�H���\�͑���f�[�^�P
		////�R���~����R���̏ꍇ 2002/12/03 E.Takase
		//if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
        //    tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori*2;
        //    tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT*2;
        //    tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU*2;
        //    tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori*2;
		////�R���~����R���ȊO�̏ꍇ 2002/12/03 E.Takase
        //} else {
        //    tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori;
        //    tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT;
        //    tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU;
        //    tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori;
        //}
        tmpSOKUTEI_SU1 = Cur_Kdb1.HIST_SOKUT_Ori;
        tmpSOKUTEI_SU2 = Cur_Kdb1.HIST_SOKUT;
        tmpSOKUTEI_SU3 = Cur_Kdb1.SOKUTE_SU;
        tmpSOKUTEI_SU4 = Cur_Kdb1.SOKUTE_SU_Ori;
        fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
				Cur_Kdb1.TANI.c_str(),
				Cur_Kdb1.KENSA_YMD.c_str(),
				Cur_Kdb1.DTKSHIN.c_str(),
				Cur_Kdb1.LOTNO.c_str(),
				Cur_Kdb1.ZISCOD.c_str(),
				Cur_Kdb1.ZISNAM.c_str(),
                KOUMOKU_J.c_str(),
                KOUMOKU_E.c_str(),
				tmpSOKUTEI_SU1,
				tmpSOKUTEI_SU2,
				Cur_Kdb1.HIST_KIKAK,
				Cur_Kdb1.HIST_MIN,
				Cur_Kdb1.HIST_MAX,
				tmpSOKUTEI_SU3,
				tmpSOKUTEI_SU4,
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
        //fprintf(stream,"%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
		//		Cur_Kdb1.TANI.c_str(),
		//		Cur_Kdb1.KENSA_YMD.c_str(),
		//		Cur_Kdb1.DTKSHIN.c_str(),
		//		Cur_Kdb1.LOTNO.c_str(),
		//		Cur_Kdb1.ZISCOD.c_str(),
		//		Cur_Kdb1.ZISNAM.c_str(),
        //        KOUMOKU_J.c_str(),
        //        KOUMOKU_E.c_str(),
		//		Cur_Kdb1.HIST_SOKUT_Ori,
		//		Cur_Kdb1.HIST_SOKUT,
		//		Cur_Kdb1.HIST_KIKAK,
		//		Cur_Kdb1.HIST_MIN,
		//		Cur_Kdb1.HIST_MAX,
		//		Cur_Kdb1.SOKUTE_SU,
		//		Cur_Kdb1.SOKUTE_SU_Ori,
		//		KETA.SOKUTE_AVE,
		//		KETA.SOKUTE_MIN,
		//		KETA.SOKUTE_MAX,
		//		KETA.SOKUTE_R,
		//		KETA.SOKUTE_SGM,
		//		KETA.SOKUTE_CP,
		//		KETA.SOKUTE_CPK,
		//		KETA.SOKUTE_K,
		//		KETA.SOKUTE_P
        //            );
        //�H���\�͑���f�[�^�Q
		//�R���~����R���̏ꍇ 2002/12/03 E.Takase
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
            //2003.02.13 E.Takase
            //for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
            //   fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
            //   fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
            //}
            if ( flag == 0 ) {
                for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                    fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
                    //fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
                }
            } else {
                for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                    //fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI3);
                    fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_MEI5);
                }
            }
		//�R���~����R���ȊO�̏ꍇ 2002/12/03 E.Takase
        } else {
            for( i = 0; i < Cur_Kdb1.SOKUTE_SU  ; i++) {
                fprintf(stream,"%lf\n",M_Kdb2[i].SOKUTEI_CH);
            }
        }
        // �t�@�C�������
        fclose(stream);
	    return(true);
 	}else{	//̧�ق̵���݂Ɏ��s�����ꍇ
		fclose(stream);
		return(false);
	}

}

//---------------------------------------------------------------------------
//Excel�i�H���\�͑���j �N��
bool __fastcall TForm3::Excel_Write()
{
/*
	WORD wReturn;
    char tempo[256];
    bool retDLL;

    // �t�@�C�����X�V�p�ɊJ��
    strcpy(path,CDPath);
    strcat(path, "\\�H���\�͑���.xls");

    retDLL = ShellExecute(NULL, "open", path, "", "", SW_HIDE);
    return(retDLL);

*/

/*
    AnsiString FilePath;

    FilePath = CDPath;
    FilePath += "\\�H���\�͑���.xls";
    //FilePath = "G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE";


    // �t�@�C�����X�V�p�ɊJ��
    //strcpy(path,"\"G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE\"");
    //strcat(path,CDPath);
    //strcat(path, "\\�H���\�͑���.xls");

    strcpy(path,"'G:\\Program Files\\Microsoft Office97\\Office\\EXCEL.EXE'");

    // �A�v���P�[�V���������s���ďI����҂�
    STARTUPINFO SupInf;
    PROCESS_INFORMATION PrcsInf;

    ::GetStartupInfo(&SupInf);
    SupInf.cb = sizeof(SupInf);
    SupInf.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEONFEEDBACK;
    SupInf.wShowWindow = SW_SHOW;

    bool Fin = CreateProcess( path, NULL, NULL, NULL, false,
                         NORMAL_PRIORITY_CLASS, NULL, NULL, &SupInf, &PrcsInf );
    if( Fin == true ){
         WaitForSingleObject( PrcsInf.hProcess, INFINITE );
    }
*/

    STARTUPINFO stup;
    PROCESS_INFORMATION pinf;

    stup.cb=sizeof(STARTUPINFO);
    stup.lpReserved=NULL;
    stup.lpDesktop=NULL;
    stup.lpTitle=NULL;
    stup.dwFlags=STARTF_USESHOWWINDOW;
    stup.cbReserved2=0;
    stup.lpReserved2=NULL;
    stup.wShowWindow=SW_SHOW;


    char cmdline[1028];
    strcpy(path,CDPath);
    strcat(path, "\\�H���\�͑���.xls");
    wsprintf(cmdline,"\"%s\" \"%s\"",  Form1->ExcelExePATH,path);

    BOOL flag=::CreateProcess(NULL,cmdline,NULL,NULL,0,0,NULL,NULL,&stup,&pinf);

    if( flag == true ){
         WaitForSingleObject( pinf.hProcess, INFINITE );
    }


    return(true);
}

//---------------------------------------------------------------------------
//SGr1��pos�s�ڂ̑���f�[�^�� Tmp_KDB1�ɑ��
void __fastcall TForm1::Sub_Tmp_KDB1(int pos)
{
    AnsiString sBuf;
    int i,T_No;

	Tmp_KDB1.No				= 0;        // �I��ԍ�
	Tmp_KDB1.KENSA_YMD		= "";		//	�����N����
	Tmp_KDB1.DTKSHIN		= ""; 		//	���Ӑ�i��
	Tmp_KDB1.HINBAN			= "";		//	���Еi��
	Tmp_KDB1.ZISCOD			= "";		//	�ގ��R�[�h
	Tmp_KDB1.ZISNAM			= "";		//	�ގ���
	Tmp_KDB1.LOTNO			= "";		//	���b�gNO
	Tmp_KDB1.SEQNO			= 0;		//	SEQ-NO
	Tmp_KDB1.KENSA_KMK		= 0;		//	��������
	Tmp_KDB1.KOUMOKU_J		= "";		//	�������ږ��i���{��j
	Tmp_KDB1.KOUMOKU_E		= "";		//	�������ږ��iEnglish�j
	Tmp_KDB1.HIST_SOKUT		= 0;		//	�H���\�� ���萔
	Tmp_KDB1.HIST_SOKUT_Ori	= 0;	    //	�H���\�� ���萔
	Tmp_KDB1.HIST_KIKAK		= 0;		//	�H���\�� �K�i
	Tmp_KDB1.HIST_MIN		= 0;		//	�H���\�� �����K�i
	Tmp_KDB1.HIST_MAX		= 0;		//	�H���\�� ����K�i
	Tmp_KDB1.SOKUTE_SU		= 0;		//	���萔
	Tmp_KDB1.SOKUTE_SU_Ori	= 0;	    //	���萔
	Tmp_KDB1.SOKUTE_KET		= 0;        //      �L�������F�Q�F2���A�R�F3��
	Tmp_KDB1.SOKUTE_AVE		= 0;		//	���ϒl
	Tmp_KDB1.SOKUTE_MIN		= 0;		//	�l�h�m
	Tmp_KDB1.SOKUTE_MAX		= 0;		//	�l�`�w
	Tmp_KDB1.SOKUTE_R		= 0;		//	�q
	Tmp_KDB1.SOKUTE_SGM		= 0;		//	�W���΍�
	Tmp_KDB1.SOKUTE_CP		= 0;		//	�b�o
	Tmp_KDB1.SOKUTE_CPK		= 0;		//	�b�o�j
	Tmp_KDB1.SOKUTE_K		= 0;		//	�j
	Tmp_KDB1.SOKUTE_P		= 0;		//	�s�Ǘ�
	Tmp_KDB1.JYOKEN1		= 0;		//	��������P
	Tmp_KDB1.JYOKEN2		= 0;		//	�@�V�@�@�Q
	Tmp_KDB1.ADDYMD			= "";		//	�o�^��
	Tmp_KDB1.ADDTIM			= "";		//	�o�^����
	Tmp_KDB1.UPDYMD			= "";		//	�ύX��
	Tmp_KDB1.UPDTIM			= "";		//	�ύX����
	Tmp_KDB1.UPDCHR			= 0;		//	�X�V��
	Tmp_KDB1.UPDCNT			= 0;		//	�X�V��
	Tmp_KDB1.TANI			= "";		//	�P��

    //2002/12/03 E.Takase
	Tmp_KDB1.KEIJKBN	    = 0;		//	�`��敪

     Tmp_KDB1.KENSA_YMD = Form1->DelSEPA( EdtYMD->Text);
     Tmp_KDB1.DTKSHIN = EdtHIN->Text;
     Tmp_KDB1.LOTNO = EdtLOT->Text;
     Tmp_KDB1.SEQNO = StrToInt(SGr1->Cells[17][pos]);
     Tmp_KDB1.No = pos + 1;


     // Read Data Base (KdB1)
     //�f�[�^�x�[�X Query ������
     Query_Kdb1->Close();
     Query_Kdb1->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "* ";
     sBuf += "FROM KDB1 ";
     sBuf += "WHERE KENSA_YMD = '" + Tmp_KDB1.KENSA_YMD + "' " ;
     sBuf +=  " AND SEQNO = " + IntToStr(Tmp_KDB1.SEQNO);
	 sBuf += " AND DTKSHIN = '" + Tmp_KDB1.DTKSHIN	 + "'";
	 sBuf += " AND LOTNO = '" + Tmp_KDB1.LOTNO + "'";
         sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�
     sBuf += " ORDER BY KENSA_YMD,DTKSHIN,LOTNO, SEQNO";

     Query_Kdb1->SQL->Add(sBuf);
     Query_Kdb1->Open();
     Query_Kdb1->Active = true;

     if ( Query_Kdb1->RecordCount > 0 ) {
        Query_Kdb1->First();

        if ( Query_Kdb1->FieldValues["DTKSHIN"].IsNull())
           Tmp_KDB1.DTKSHIN = " ";
        else
           Tmp_KDB1.DTKSHIN = Query_Kdb1->FieldValues["DTKSHIN"];

        if ( Query_Kdb1->FieldValues["HINBAN"].IsNull())
           Tmp_KDB1.HINBAN = " ";
        else
           Tmp_KDB1.HINBAN = Query_Kdb1->FieldValues["HINBAN"];

        if ( Query_Kdb1->FieldValues["ZISCOD"].IsNull())
           Tmp_KDB1.ZISCOD = " ";
        else
           Tmp_KDB1.ZISCOD = Query_Kdb1->FieldValues["ZISCOD"];

        if ( Query_Kdb1->FieldValues["ZISNAM"].IsNull())
           Tmp_KDB1.ZISNAM = " ";
        else
           Tmp_KDB1.ZISNAM = Query_Kdb1->FieldValues["ZISNAM"];

        if ( Query_Kdb1->FieldValues["LOTNO"].IsNull())
           Tmp_KDB1.LOTNO = " ";
        else
           Tmp_KDB1.LOTNO = Query_Kdb1->FieldValues["LOTNO"];

        if ( Query_Kdb1->FieldValues["KENSA_KMK"].IsNull())
           Tmp_KDB1.KENSA_KMK = 0;
        else
           Tmp_KDB1.KENSA_KMK = Query_Kdb1->FieldValues["KENSA_KMK"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_J"].IsNull())
           Tmp_KDB1.KOUMOKU_J = " ";
        else
           Tmp_KDB1.KOUMOKU_J = Query_Kdb1->FieldValues["KOUMOKU_J"];

        if ( Query_Kdb1->FieldValues["KOUMOKU_E"].IsNull())
           Tmp_KDB1.KOUMOKU_E = " ";
        else
           Tmp_KDB1.KOUMOKU_E = Query_Kdb1->FieldValues["KOUMOKU_E"];

        if ( Query_Kdb1->FieldValues["HIST_SOKUT"].IsNull())
           Tmp_KDB1.HIST_SOKUT = 0;
        else
           Tmp_KDB1.HIST_SOKUT = Query_Kdb1->FieldValues["HIST_SOKUT"];
        Tmp_KDB1.HIST_SOKUT_Ori = Tmp_KDB1.HIST_SOKUT;

        if ( Query_Kdb1->FieldValues["HIST_KIKAK"].IsNull())
           Tmp_KDB1.HIST_KIKAK = 0;
        else
           Tmp_KDB1.HIST_KIKAK = Query_Kdb1->FieldValues["HIST_KIKAK"];

        if ( Query_Kdb1->FieldValues["HIST_MIN"].IsNull())
           Tmp_KDB1.HIST_MIN = 0;
        else
           Tmp_KDB1.HIST_MIN = Query_Kdb1->FieldValues["HIST_MIN"];

        if ( Query_Kdb1->FieldValues["HIST_MAX"].IsNull())
           Tmp_KDB1.HIST_MAX = 0;
        else
           Tmp_KDB1.HIST_MAX = Query_Kdb1->FieldValues["HIST_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SU"].IsNull())
           Tmp_KDB1.SOKUTE_SU = 0;
        else
           Tmp_KDB1.SOKUTE_SU = Query_Kdb1->FieldValues["SOKUTE_SU"];
        Tmp_KDB1.SOKUTE_SU_Ori = Tmp_KDB1.SOKUTE_SU;

        if ( Query_Kdb1->FieldValues["SOKUTE_AVE"].IsNull())
           Tmp_KDB1.SOKUTE_AVE = 0;
        else
           Tmp_KDB1.SOKUTE_AVE = Query_Kdb1->FieldValues["SOKUTE_AVE"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MIN"].IsNull())
           Tmp_KDB1.SOKUTE_MIN = 0;
        else
           Tmp_KDB1.SOKUTE_MIN = Query_Kdb1->FieldValues["SOKUTE_MIN"];

        if ( Query_Kdb1->FieldValues["SOKUTE_MAX"].IsNull())
           Tmp_KDB1.SOKUTE_MAX = 0;
        else
           Tmp_KDB1.SOKUTE_MAX = Query_Kdb1->FieldValues["SOKUTE_MAX"];

        if ( Query_Kdb1->FieldValues["SOKUTE_R"].IsNull())
           Tmp_KDB1.SOKUTE_R = 0;
        else
           Tmp_KDB1.SOKUTE_R = Query_Kdb1->FieldValues["SOKUTE_R"];

        if ( Query_Kdb1->FieldValues["SOKUTE_SGM"].IsNull())
           Tmp_KDB1.SOKUTE_SGM = 0;
        else
           Tmp_KDB1.SOKUTE_SGM = Query_Kdb1->FieldValues["SOKUTE_SGM"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CP"].IsNull())
           Tmp_KDB1.SOKUTE_CP = 0;
        else
           Tmp_KDB1.SOKUTE_CP = Query_Kdb1->FieldValues["SOKUTE_CP"];

        if ( Query_Kdb1->FieldValues["SOKUTE_CPK"].IsNull())
           Tmp_KDB1.SOKUTE_CPK = 0;
        else
           Tmp_KDB1.SOKUTE_CPK = Query_Kdb1->FieldValues["SOKUTE_CPK"];

        if ( Query_Kdb1->FieldValues["SOKUTE_K"].IsNull())
           Tmp_KDB1.SOKUTE_K = 0;
        else
           Tmp_KDB1.SOKUTE_K = Query_Kdb1->FieldValues["SOKUTE_K"];

        if ( Query_Kdb1->FieldValues["SOKUTE_P"].IsNull())
           Tmp_KDB1.SOKUTE_P = 0;
        else
           Tmp_KDB1.SOKUTE_P = Query_Kdb1->FieldValues["SOKUTE_P"];

        if ( Query_Kdb1->FieldValues["JYOKEN1"].IsNull())
           Tmp_KDB1.JYOKEN1 = 0;
        else
           Tmp_KDB1.JYOKEN1 = Query_Kdb1->FieldValues["JYOKEN1"];

        if ( Query_Kdb1->FieldValues["JYOKEN2"].IsNull())
           Tmp_KDB1.JYOKEN2 = 0;
        else
           Tmp_KDB1.JYOKEN2 = Query_Kdb1->FieldValues["JYOKEN2"];

        if ( Query_Kdb1->FieldValues["UPDCNT"].IsNull())
           Tmp_KDB1.UPDCNT = 0;
        else
           Tmp_KDB1.UPDCNT = Query_Kdb1->FieldValues["UPDCNT"];

        if ( Query_Kdb1->FieldValues["TANI"].IsNull())
           Tmp_KDB1.TANI = "";
        else
           Tmp_KDB1.TANI = Query_Kdb1->FieldValues["TANI"];

        if ( Query_Kdb1->FieldValues["SOKUTE_KET"].IsNull())
           Tmp_KDB1.SOKUTE_KET = 0;
        else
           Tmp_KDB1.SOKUTE_KET = Query_Kdb1->FieldValues["SOKUTE_KET"];

        //2002/12/03 E.Takase
        if ( Query_Kdb1->FieldValues["KEIJKBN"].IsNull())
           Tmp_KDB1.KEIJKBN = 0;
        else
           Tmp_KDB1.KEIJKBN = Query_Kdb1->FieldValues["KEIJKBN"];



      } else {
        Query_Kdb1->Close();
        return ;
      }

     Query_Kdb1->Close();


     for ( i = 0; i < Nums; i++) {
        M_Kdb2[i].SOKUTEI_CH = 0;
        M_Kdb2[i].SOKUTEI_MEI1 = 0;
        M_Kdb2[i].SOKUTEI_MEI2 = 0;
        M_Kdb2[i].SOKUTEI_MEI3 = 0;
        M_Kdb2[i].SOKUTEI_MEI4 = 0;
        M_Kdb2[i].SOKUTEI_MEI5 = 0;
        M_Kdb2[i].SOKUTEI_MEI6 = 0;
        M_Kdb2[i].SOKUTEI_MEI7 = 0;
        M_Kdb2[i].DatabaseFlag = 0;
     }

     // Read Data Base (Kdb2)
     //�f�[�^�x�[�X Query ������
     Query_Kdb2->Close();
     Query_Kdb2->SQL->Clear();

     //�₢���������s
     //�����\����A�g���[No
     sBuf = "SELECT ";
     sBuf += "SOKUTEI_NO, SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, ";
     sBuf += "SOKUTEI_MEI4, SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7 ";
     sBuf += "FROM KDB2 ";
     sBuf += "WHERE KENSA_YMD = '" + Tmp_KDB1.KENSA_YMD + "' ";
     sBuf +=  " AND SEQNO = " + IntToStr(Tmp_KDB1.SEQNO);
	 sBuf += " AND DTKSHIN = '" + Tmp_KDB1.DTKSHIN	 + "'";
	 sBuf += " AND LOTNO = '" + Tmp_KDB1.LOTNO + "'";
         sBuf += " AND KOJOKBN = " + IntToStr(iKojoKbn) + " ";    //20160701_�H��敪�ǉ�
     sBuf += " ORDER BY KENSA_YMD, SEQNO, SOKUTEI_NO";

     Query_Kdb2->SQL->Add(sBuf);
     Query_Kdb2->Open();
     Query_Kdb2->Active = true;

     if ( Query_Kdb2->RecordCount > 0 ) {
        Query_Kdb2->First();
        while( !Query_Kdb2->Eof ) {
           if ( Query_Kdb2->FieldValues["SOKUTEI_NO"].IsNull()) {
              T_No = 0;
           } else {
              T_No = Query_Kdb2->FieldValues["SOKUTEI_NO"];
           }

           if (T_No > 0) {
              M_Kdb2[T_No - 1].DatabaseFlag = 1;
              if ( Query_Kdb2->FieldValues["SOKUTEI_CH"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_CH = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_CH = Query_Kdb2->FieldValues["SOKUTEI_CH"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI1"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI1 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI1 = Query_Kdb2->FieldValues["SOKUTEI_MEI1"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI2"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI2 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI2 = Query_Kdb2->FieldValues["SOKUTEI_MEI2"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI3"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI3 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI3 = Query_Kdb2->FieldValues["SOKUTEI_MEI3"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI4"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI4 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI4 = Query_Kdb2->FieldValues["SOKUTEI_MEI4"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI5"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI5 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI5 = Query_Kdb2->FieldValues["SOKUTEI_MEI5"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI6"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI6 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI6 = Query_Kdb2->FieldValues["SOKUTEI_MEI6"];

              if ( Query_Kdb2->FieldValues["SOKUTEI_MEI7"].IsNull())
                 M_Kdb2[T_No - 1].SOKUTEI_MEI7 = 0;
              else
                 M_Kdb2[T_No - 1].SOKUTEI_MEI7 = Query_Kdb2->FieldValues["SOKUTEI_MEI7"];
           }
           Query_Kdb2->Next();
        }
     }

     Query_Kdb2->Close();

}
//---------------------------------------------------------------------------
// ���v�ƃO���t�\��
void __fastcall TForm1::Toukei_Tmp_KDB1(int k)
{
 int MaxNo;     // �ő��
 int T_Scale;
 AnsiString string;

 int i, j;
 char s_str[64];
 double T_double, T_High, T_Low, T_double1, T_double2;
 int N_Mid, N_High, N_Low, n1, n2, T_index;
 int SubFlag = 0;

 if (Tmp_KDB1.HIST_MAX < Tmp_KDB1.HIST_MIN && Tmp_KDB1.HIST_KIKAK == 1) {
    T_double = Tmp_KDB1.HIST_MIN;
    Tmp_KDB1.HIST_MIN = Tmp_KDB1.HIST_MAX;
    Tmp_KDB1.HIST_MAX = T_double;
 }

 // Y����Scale �v�Z
 if (Tmp_KDB1.HIST_KIKAK == 1) { // �����`�F�b�N�P�[�X
    //T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
    T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/16;   // 2000.5.22 �C��
    for (i = 18; i >= 0; i--) {
        //if (E_Standard_Scale[i] > T_double) {
        if (E_Standard_Scale[i] >= T_double) {  // 2000.5.22  �C��
           T_double = E_Standard_Scale[i];
           i = -1;
        }
    }

    // 2000.3.6 N_Mid <= 7�Ȃ�ƁAN_Mid�{�ɂ���
    if (Tmp_KDB1.KOUMOKU_J == "�u���V����") {  // �u���V�����݂̂�Ώۂ���
        T_double1 = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/T_double;
        N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
        if (N_Mid <= 7) {
            N_Mid = N_Mid * 2;
            T_double = T_double / 2;
        }
    }

    // 2000.5.9 �\�������ɂ���āApitch����
    // �����F�P�G�����_1���F�O�D�P�G
    // �����_�Q���F0.01�G�����_3���F0.001
    if (k == 0 && T_double < 1)
       T_double = 1;
    if (k == 1 && T_double < 0.1)
       T_double = 0.1;
    if (k == 2 && T_double < 0.01)
       T_double = 0.01;
    if (k == 3 && T_double < 0.001)
       T_double = 0.001;
    // end of add 2000.5.9

    // �����`�F�b�N
    T_double1 = Tmp_KDB1.HIST_MIN/T_double;
    n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
    //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
    if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
       T_Low = Tmp_KDB1.HIST_MIN;
       n1 = 0;
    } else {
       T_Low = (double)(n1+1) * T_double;
       n1 = 1;
    }

    // ����`�F�b�N
    //n2 = Cur_Kda1.HIST_MAX/T_double;
    T_double1 = Tmp_KDB1.HIST_MAX/T_double;
    n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
    if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
       T_High = Tmp_KDB1.HIST_MAX;
       n2 = 0;
    } else {
       T_High = (double)n2 * T_double;
       n2 = 1;
    }

    // �K�i�ȓ��̃��C����
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = N_Mid + n1 + n2;

    // �K�i�ȉ��̃��C����
    N_Low = (int)((20 - N_Mid)/2);

    // �K�i�ȏ�̃��C����
    N_High = 20 - N_Mid - N_Low;

    // �����ȉ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // �K�i�ȓ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[1][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // ����ȏ�X�P�[��
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = Tmp_KDB1.HIST_MAX + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 } else { // �Б��`�F�b�N
    //T_index = 12;
    // 2000.5.9 �\�������ɂ���āAdefault pitch����
    // �����F�P�G�����_1���F�O�D�P�G
    // �����_�Q���F0.01�G�����_3���F0.001
    if (k == 0)
       T_index = 7;
    if (k == 1)
       T_index = 10;
    if (k == 2)
       T_index = 13;
    if (k == 3)
       T_index = 16;
    // end of add 2000.5.9
Again1:
    if (T_index >= 20) {   //2000.11.17�ǉ�
       MessageDlg( "�K�i���g�債�ĉ������iT_index��20�𒴂���j", mtConfirmation, mbYesNoCancel, 0);
    }

    T_double = E_Standard_Scale[T_index];    // default pitch;

    if (Tmp_KDB1.SOKUTE_SU > 1) {      // ���^�f�[�^������
        //�R���~����R���̏ꍇ 2002/12/03 E.Takase
        if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {

            T_double2 = M_Kdb2[0].SOKUTEI_MEI3;
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //�ő�l��T��
                    if (M_Kdb2[i].SOKUTEI_MEI3 > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
                } else { // �ŏ��l��T��
                    if (M_Kdb2[i].SOKUTEI_MEI3 < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
                }
            }
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //�ő�l��T��
                    if (M_Kdb2[i].SOKUTEI_MEI5 > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
                } else { // �ŏ��l��T��
                    if (M_Kdb2[i].SOKUTEI_MEI5 < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
                }
            }

        //�R���~����R���ȊO�̏ꍇ 2002/12/03 E.Takase
        } else {
            T_double2 = M_Kdb2[0].SOKUTEI_CH;
            for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
                if (Tmp_KDB1.HIST_KIKAK == 2) {  //�ő�l��T��
                    if (M_Kdb2[i].SOKUTEI_CH > T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_CH;
                } else { // �ŏ��l��T��
                    if (M_Kdb2[i].SOKUTEI_CH < T_double2)
                        T_double2 = M_Kdb2[i].SOKUTEI_CH;
                }
            }

        }

       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // �����`�F�b�N
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;

          if (T_double2 > T_Low + 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   T_index--;
                   SubFlag = 1;
                   goto Again1;
                }
             }
          }

/*        2000.5.9 delete
          if (T_double2 < T_Low + 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }
*/
          n2 = 0;
       } else {
          // ����`�F�b�N
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;

          if (T_Low < 0)
             T_Low = 0;

          if (T_double2 < T_High - 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   SubFlag = 1;
                   T_index--;
                   goto Again1;
                }
             }
          }
/*        2000.5.9 delete
          if (T_double2 > T_High - 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }
*/
          n1 = 0;
       }
    } else { // ���^�f�[�^�Ȃ�
       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // �����`�F�b�N
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;
          n2 = 0;
       } else {
          // ����`�F�b�N
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;
          // 2000.11.17�ǉ� T_Low���`�F�b�N����B���O�ꍇ�̓s�[�`������������
          if (T_Low < 0) {
             T_index++;
             goto Again1;
          }
          n1 = 0;
       }
    }

    // �K�i�ȓ��̃��C����
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);

    if (N_Mid <= 7 && Tmp_KDB1.KOUMOKU_J == "�u���V����") { // �X�P�[�������������A�{�ɂ��� 2000.3.6
       T_double = T_double / 2;
       if (n1 > 0) {
          if (fabs(T_Low - (Tmp_KDB1.HIST_MIN - T_double)) <= COM_DIFF) {
             n1 = 0;
             T_Low = Tmp_KDB1.HIST_MIN;
          }
       }
       if (n2 > 0) {
          if (fabs(T_High - Tmp_KDB1.HIST_MAX - T_double) <= COM_DIFF) {
             n2 = 0;
             T_High = Tmp_KDB1.HIST_MAX;
          }
       }
       T_double1 = (T_High - T_Low)/T_double;
       N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    }


    N_Mid = N_Mid + n1 + n2;

    // �K�i�ȉ��̃��C����
    N_Low = (int)((20 - N_Mid)/2);

    if (T_High - (N_Mid + N_Low) * T_double < 0)
       N_Low = (int)(T_High / T_double) - N_Mid;

    // �K�i�ȏ�̃��C����
    N_High = 20 - N_Mid - N_Low;

    // �����ȉ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // �K�i�ȓ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = T_High;
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // ����ȏ�X�P�[��
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = T_High + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 }

 // ���iE_Screen_Data[2][]�j������
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

	// �� Counter
	if (Tmp_KDB1.SOKUTE_SU > 0) {
		//�R���~����R���̏ꍇ 2002/12/03 E.Takase
		if ( Tmp_KDB1.KENSA_KMK == 7 && Tmp_KDB1.KEIJKBN == 3 ) {
			//�d�� ��
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI3 < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
			//�d�� ��
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI5 < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
		//�R���~����R���ȊO�̏ꍇ 2002/12/03 E.Takase
		} else {
			for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
							//if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
							//   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
							//   E_Screen_Data[2][j-1] += 1;
							//else
							E_Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
							E_Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
		}
	}


 // �ő�������߂�
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // �X�P�[�������߂�
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;




/*2000/05/09
 if (Tmp_KDB1.HIST_MAX < Tmp_KDB1.HIST_MIN && Tmp_KDB1.HIST_KIKAK == 1) {
    T_double = Tmp_KDB1.HIST_MIN;
    Tmp_KDB1.HIST_MIN = Tmp_KDB1.HIST_MAX;
    Tmp_KDB1.HIST_MAX = T_double;
 }

 // Y����Scale �v�Z
 if (Tmp_KDB1.HIST_KIKAK == 1) { // �����`�F�b�N�P�[�X
    T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
    for (i = 18; i >= 0; i--) {
        if (E_Standard_Scale[i] > T_double) {
           T_double = E_Standard_Scale[i];
           i = -1;
        }
    }

    // 2000.3.6 N_Mid <= 7�Ȃ�ƁAN_Mid�{�ɂ���
    if (Tmp_KDB1.KOUMOKU_J == "�u���V����") {  // �u���V�����݂̂�Ώۂ���
        T_double1 = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/T_double;
        N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
        if (N_Mid <= 7) {
            N_Mid = N_Mid * 2;
            T_double = T_double / 2;
        }
    }

    // 2000.5.9 �\�������ɂ���āApitch����
    // �����F�P�G�����_1���F�O�D�P�G
    // �����_�Q���F0.01�G�����_3���F0.001
    if (KETA.SOKUTE_MIN == 0 && T_double < 1)
       T_double = 1;
    if (KETA.SOKUTE_MIN == 1 && T_double < 0.1)
       T_double = 0.1;
    if (KETA.SOKUTE_MIN == 2 && T_double < 0.01)
       T_double = 0.01;
    if (KETA.SOKUTE_MIN == 3 && T_double < 0.001)
       T_double = 0.001;
    // end of add 2000.5.9


    // �����`�F�b�N
    T_double1 = Tmp_KDB1.HIST_MIN/T_double;
    n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
    //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
    if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
       T_Low = Tmp_KDB1.HIST_MIN;
       n1 = 0;
    } else {
       T_Low = (double)(n1+1) * T_double;
       n1 = 1;
    }

    // ����`�F�b�N
    //n2 = Cur_Kda1.HIST_MAX/T_double;
    T_double1 = Tmp_KDB1.HIST_MAX/T_double;
    n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
    if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
       T_High = Tmp_KDB1.HIST_MAX;
       n2 = 0;
    } else {
       T_High = (double)n2 * T_double;
       n2 = 1;
    }

    // �K�i�ȓ��̃��C����
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = N_Mid + n1 + n2;

    // �K�i�ȉ��̃��C����
    N_Low = (int)((20 - N_Mid)/2);

    // �K�i�ȏ�̃��C����
    N_High = 20 - N_Mid - N_Low;

    // �����ȉ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // �K�i�ȓ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[1][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // ����ȏ�X�P�[��
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = Tmp_KDB1.HIST_MAX + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 } else { // �Б��`�F�b�N
    T_index = 12;
    // 2000.5.9 �\�������ɂ���āAdefault pitch����
    // �����F�P�G�����_1���F�O�D�P�G
    // �����_�Q���F0.01�G�����_3���F0.001
    if (KETA.SOKUTE_MIN == 0)
       T_index = 7;
    if (KETA.SOKUTE_MIN == 1)
       T_index = 10;
    if (KETA.SOKUTE_MIN == 2)
       T_index = 13;
    if (KETA.SOKUTE_MIN == 3)
       T_index = 16;
    // end of add 2000.5.9
Again1:
    T_double = E_Standard_Scale[T_index];    // default :0.02;

    if (Tmp_KDB1.SOKUTE_SU > 1) {      // ���^�f�[�^������
       T_double2 = M_Kdb2[0].SOKUTEI_CH;
       for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
          if (Tmp_KDB1.HIST_KIKAK == 2) {  //�ő�l��T��
            if (M_Kdb2[i].SOKUTEI_CH > T_double2)
               T_double2 = M_Kdb2[i].SOKUTEI_CH;
          } else { // �ŏ��l��T��
            if (M_Kdb2[i].SOKUTEI_CH < T_double2)
               T_double2 = M_Kdb2[i].SOKUTEI_CH;
          }
       }

       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // �����`�F�b�N
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;

          if (T_double2 > T_Low + 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   T_index--;
                   SubFlag = 1;
                   goto Again1;
                }
             }
          }

          if (T_double2 < T_Low + 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }

          n2 = 0;
       } else {
          // ����`�F�b�N
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;

          if (T_Low < 0)
             T_Low = 0;

          if (T_double2 < T_High - 14 * T_double) {
             if (T_index >= 1) {
                if (SubFlag != 2) {
                   SubFlag = 1;
                   T_index--;
                   goto Again1;
                }
             }
          }

          if (T_double2 > T_High - 7 * T_double) {
             if (T_index <= 18) {
                if (SubFlag != 1) {
                   SubFlag = 2;
                   T_index++;
                   goto Again1;
                }
             }
          }

          n1 = 0;
       }
    } else { // ���^�f�[�^�Ȃ�
       if (Tmp_KDB1.HIST_KIKAK == 2) {
          // �����`�F�b�N
          T_double1 = Tmp_KDB1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Tmp_KDB1.HIST_MIN) <= COM_DIFF) {
             T_Low = Tmp_KDB1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;
          n2 = 0;
       } else {
          // ����`�F�b�N
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Tmp_KDB1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Tmp_KDB1.HIST_MAX) <= COM_DIFF) {
             T_High = Tmp_KDB1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;
          n1 = 0;
       }
    }

    // �K�i�ȓ��̃��C����
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);

    if (N_Mid <= 7 && Tmp_KDB1.KOUMOKU_J == "�u���V����") { // �X�P�[�������������A�{�ɂ��� 2000.3.6
       T_double = T_double / 2;
       if (n1 > 0) {
          if (fabs(T_Low - (Tmp_KDB1.HIST_MIN - T_double)) <= COM_DIFF) {
             n1 = 0;
             T_Low = Tmp_KDB1.HIST_MIN;
          }
       }
       if (n2 > 0) {
          if (fabs(T_High - Tmp_KDB1.HIST_MAX - T_double) <= COM_DIFF) {
             n2 = 0;
             T_High = Tmp_KDB1.HIST_MAX;
          }
       }
       T_double1 = (T_High - T_Low)/T_double;
       N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    }


    N_Mid = N_Mid + n1 + n2;

    // �K�i�ȉ��̃��C����
    N_Low = (int)((20 - N_Mid)/2);

    if (T_High - (N_Mid + N_Low) * T_double < 0)
       N_Low = (int)(T_High / T_double) - N_Mid;

    // �K�i�ȏ�̃��C����
    N_High = 20 - N_Mid - N_Low;

    // �����ȉ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           E_Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           E_Screen_Data[0][i+1] = E_Screen_Data[1][i];
       }
       E_Screen_Data[0][0] = 0;
       E_Screen_Data[1][N_Low-1] = Tmp_KDB1.HIST_MIN;
    }

    // �K�i�ȓ��X�P�[��
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           E_Screen_Data[0][N_Low+i] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       E_Screen_Data[0][N_Low] = Tmp_KDB1.HIST_MIN;
       E_Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           E_Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           E_Screen_Data[1][N_Low+i+1] = E_Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       E_Screen_Data[1][N_Low + N_Mid - 1] = Tmp_KDB1.HIST_MAX;
       E_Screen_Data[0][N_Low + N_Mid] = Tmp_KDB1.HIST_MAX;
    } else {
       E_Screen_Data[0][N_Low + N_Mid] = T_High;
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = E_Screen_Data[1][N_Low + N_Mid];
    }

    // ����ȏ�X�P�[��
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           E_Screen_Data[1][N_Low + N_Mid + i] = T_High + (i+1) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + i+1] = E_Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       E_Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       E_Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           E_Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           E_Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 }

 // ���iE_Screen_Data[2][]�j������
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

 // �� Counter
 if (Tmp_KDB1.SOKUTE_SU > 0) {
    for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
        for (j = 0; j < 20; j++) {
           if (j != 19) {
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
                  M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
                     //if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
                     //   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
                     //   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
                     //   E_Screen_Data[2][j-1] += 1;
                     //else
                        E_Screen_Data[2][j] += 1;
                  j = 20;
              }
           } else { // j == 19
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
                 E_Screen_Data[2][j] += 1;
                 j = 20;
              }
           }
        }
    }
 }


 if (Tmp_KDB1.HIST_SOKUT > 0) {
    if (Tmp_KDB1.SOKUTE_SU <= 0) {
       Tmp_KDB1.SOKUTE_AVE = 0;
       Tmp_KDB1.SOKUTE_MIN = 0;
       Tmp_KDB1.SOKUTE_MAX = 0;
       Tmp_KDB1.SOKUTE_R = 0;
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_P = 0;
       Tmp_KDB1.SOKUTE_SU = 0;
    } else {  // ���v
       Tmp_KDB1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_CH;
       Tmp_KDB1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_CH;
       Tmp_KDB1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_CH;

       // ���ϒl�A�ő�l�A�ŏ��l
       for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
           Tmp_KDB1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_CH;
           if (Tmp_KDB1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_CH)
              Tmp_KDB1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_CH;
           if (Tmp_KDB1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_CH)
              Tmp_KDB1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_CH;
       }
       Tmp_KDB1.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE/Tmp_KDB1.SOKUTE_SU;

       Tmp_KDB1.SOKUTE_R = Tmp_KDB1.SOKUTE_MAX - Tmp_KDB1.SOKUTE_MIN;

       // ��
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_P = 0;

       if (Tmp_KDB1.SOKUTE_SU > 1) {
          for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
              Tmp_KDB1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE);
          }
          Tmp_KDB1.SOKUTE_SGM = sqrt(Tmp_KDB1.SOKUTE_SGM / (Tmp_KDB1.SOKUTE_SU - 1));

          if (Tmp_KDB1.SOKUTE_SGM > COM_DIFF) {
             switch (Tmp_KDB1.HIST_KIKAK) {
             case 1:
                  Tmp_KDB1.SOKUTE_CP = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN) /
                                   (6 * Tmp_KDB1.SOKUTE_SGM);
                  // K
                  Tmp_KDB1.SOKUTE_K = fabs((Tmp_KDB1.HIST_MAX + Tmp_KDB1.HIST_MIN) /2 - Tmp_KDB1.SOKUTE_AVE) /
                                ((Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/2);

                  // CPK
                  Tmp_KDB1.SOKUTE_CPK = (1-Tmp_KDB1.SOKUTE_K) * (Tmp_KDB1.HIST_MAX -
                                  Tmp_KDB1.HIST_MIN) / (6 * Tmp_KDB1.SOKUTE_SGM);
                  break;
             case 2:
                  Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.SOKUTE_AVE - Tmp_KDB1.HIST_MIN)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                  Tmp_KDB1.SOKUTE_K = 0;
                  Tmp_KDB1.SOKUTE_CPK = 0;
                  break;
             case 3:
                  Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.HIST_MAX - Tmp_KDB1.SOKUTE_AVE)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                  Tmp_KDB1.SOKUTE_K = 0;
                  Tmp_KDB1.SOKUTE_CPK = 0;
                  break;
             }
          }
       }

       // P �s�Ǘ�
       int ErrorNo = 0;
       if (Tmp_KDB1.SOKUTE_SU > 0) {
          for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
              // �K�i���f
              if (Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 2) {
                 if (M_Kdb2[i].SOKUTEI_CH < Tmp_KDB1.HIST_MIN)
                    ErrorNo++;
              }

              if (Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) {
                 if (M_Kdb2[i].SOKUTEI_CH > Tmp_KDB1.HIST_MAX)
                    ErrorNo++;
              }
          }
          Tmp_KDB1.SOKUTE_P = (double)ErrorNo/(double)Tmp_KDB1.SOKUTE_SU * 100.0;
       } else
          Tmp_KDB1.SOKUTE_P = 0;
    }
}
 // �ő�������߂�
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // �X�P�[�������߂�
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;

*/


/* 2000.3.6 �ύX
 int MaxNo;     // �ő��
 int T_Scale;
 AnsiString string;

 int i, j;
 char s_str[64];
 double T_double, T_High, T_Low, T_double1, T_double2;
 int N_Mid, N_High, N_Low, n1, n2, T_index;

 // Y����Scale �v�Z
 //   T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/12;
 //   for (i = 18; i >= 0; i--) {
 //       if (E_Standard_Scale[i] > T_double) {
 //          T_double = E_Standard_Scale[i];
 //          i = -1;
 //       }
 //   }


    // �K�i�ȓ��̃��C����
    switch(Tmp_KDB1.HIST_KIKAK)
    {
        case 1: //�����`�F�b�N�P�[�X
		    	T_double = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/20;
	        break;
        case 2: //�����`�F�b�N�P�[�X
            	//�����K�i �ő�l������
				if (Tmp_KDB1.SOKUTE_SU > 1) {      // ���^�f�[�^������
					T_double2 = M_Kdb2[0].SOKUTEI_CH;
					for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
					// �ő�l��T��
						if (M_Kdb2[i].SOKUTEI_CH > T_double2)
							T_double2 = M_Kdb2[i].SOKUTEI_CH;
					}
       			}
		    	T_double = (T_double2 - Tmp_KDB1.HIST_MIN)/20;
            break;

        case 3: //����`�F�b�N�P�[�X
            	//����K�i �ŏ��l������
				if (Tmp_KDB1.SOKUTE_SU > 1) {      // ���^�f�[�^������
					T_double2 = M_Kdb2[0].SOKUTEI_CH;
					for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
					// �ŏ��l��T��
						if (M_Kdb2[i].SOKUTEI_CH < T_double2)
							T_double2 = M_Kdb2[i].SOKUTEI_CH;
					}
       			}

		    	T_double = (Tmp_KDB1.HIST_MAX - T_double2)/20;

            break;
    }

    //N_Mid = T_double1;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = 20;

    // �K�i�ȉ��̃��C����
    N_Low = 0;

    // �K�i�ȏ�̃��C����
    N_High = 0;

    // �K�i�ȓ��X�P�[��
	for (i = 0; i < N_Mid; i++) {
		E_Screen_Data[0][N_Low+i] = Tmp_KDB1.HIST_MIN + i * T_double;
		E_Screen_Data[1][N_Low+i] = E_Screen_Data[0][N_Low+i] + T_double;
	}



 // ���iE_Screen_Data[2][]�j������
 for (i = 0; i < 20; i++)
     E_Screen_Data[2][i] = 0;

 // �� Counter
 if (Tmp_KDB1.SOKUTE_SU > 0) {
    for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
        for (j = 0; j < 20; j++) {
           if (j != 19) {
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF &&
                  M_Kdb2[i].SOKUTEI_CH < E_Screen_Data[1][j] - COM_DIFF)) {
                     //if ((Tmp_KDB1.HIST_KIKAK == 1 || Tmp_KDB1.HIST_KIKAK == 3) &&
                     //   fabs(M_Kdb2[i].SOKUTEI_CH - Tmp_KDB1.HIST_MAX) <= COM_DIFF &&
                     //   fabs(E_Screen_Data[0][j] - Tmp_KDB1.HIST_MAX) <= COM_DIFF)
                     //   E_Screen_Data[2][j-1] += 1;
                     //else
                        E_Screen_Data[2][j] += 1;
                  j = 20;
              }
           } else { // j == 19
              if (fabs(M_Kdb2[i].SOKUTEI_CH - E_Screen_Data[0][j]) <= COM_DIFF ||
                 (M_Kdb2[i].SOKUTEI_CH >= E_Screen_Data[0][j] + COM_DIFF)) {
                 E_Screen_Data[2][j] += 1;
                 j = 20;
              }
           }
        }
    }
 }


 if (Tmp_KDB1.HIST_SOKUT > 0) {
    if (Tmp_KDB1.SOKUTE_SU <= 0) {
       Tmp_KDB1.SOKUTE_AVE = 0;
       Tmp_KDB1.SOKUTE_MIN = 0;
       Tmp_KDB1.SOKUTE_MAX = 0;
       Tmp_KDB1.SOKUTE_R = 0;
       Tmp_KDB1.SOKUTE_SGM = 0;
       Tmp_KDB1.SOKUTE_CP = 0;
       Tmp_KDB1.SOKUTE_CPK = 0;
       Tmp_KDB1.SOKUTE_K = 0;
       Tmp_KDB1.SOKUTE_P = 0;
       Tmp_KDB1.SOKUTE_SU = 0;
    } else {  // ���v
      Tmp_KDB1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_CH;
      Tmp_KDB1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_CH;
      Tmp_KDB1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_CH;

      // ���ϒl�A�ő�l�A�ŏ��l
      for (i = 1; i < Tmp_KDB1.SOKUTE_SU; i++) {
          Tmp_KDB1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_CH;
          if (Tmp_KDB1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_CH)
             Tmp_KDB1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_CH;
          if (Tmp_KDB1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_CH)
             Tmp_KDB1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_CH;
      }
      Tmp_KDB1.SOKUTE_AVE = Tmp_KDB1.SOKUTE_AVE/Tmp_KDB1.SOKUTE_SU;

      Tmp_KDB1.SOKUTE_R = Tmp_KDB1.SOKUTE_MAX - Tmp_KDB1.SOKUTE_MIN;

      // ��
      Tmp_KDB1.SOKUTE_SGM = 0;
      Tmp_KDB1.SOKUTE_CP = 0;
      Tmp_KDB1.SOKUTE_K = 0;
      Tmp_KDB1.SOKUTE_CPK = 0;
      if (Tmp_KDB1.SOKUTE_SU > 1) {
         for (i = 0; i < Tmp_KDB1.SOKUTE_SU; i++) {
             Tmp_KDB1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_CH -
                                 Tmp_KDB1.SOKUTE_AVE);
         }
         Tmp_KDB1.SOKUTE_SGM = sqrt(Tmp_KDB1.SOKUTE_SGM / (Tmp_KDB1.SOKUTE_SU - 1));

         if (Tmp_KDB1.SOKUTE_SGM > COM_DIFF) {
            switch (Tmp_KDB1.HIST_KIKAK) {
            case 1:
                 Tmp_KDB1.SOKUTE_CP = (Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN) /
                                   (6 * Tmp_KDB1.SOKUTE_SGM);
                 // K
                 Tmp_KDB1.SOKUTE_K = fabs((Tmp_KDB1.HIST_MAX + Tmp_KDB1.HIST_MIN) /2 - Tmp_KDB1.SOKUTE_AVE) /
                                ((Tmp_KDB1.HIST_MAX - Tmp_KDB1.HIST_MIN)/2);

                 // CPK
                 Tmp_KDB1.SOKUTE_CPK = (1-Tmp_KDB1.SOKUTE_K) * (Tmp_KDB1.HIST_MAX -
                                  Tmp_KDB1.HIST_MIN) / (6 * Tmp_KDB1.SOKUTE_SGM);
                 break;
            case 2:
                 Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.SOKUTE_AVE - Tmp_KDB1.HIST_MIN)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                 Tmp_KDB1.SOKUTE_K = 0;
                 Tmp_KDB1.SOKUTE_CPK = 0;
                 break;
            case 3:
                 Tmp_KDB1.SOKUTE_CP = fabs((Tmp_KDB1.HIST_MAX - Tmp_KDB1.SOKUTE_AVE)) /
                                   (3 * Tmp_KDB1.SOKUTE_SGM);
                 Tmp_KDB1.SOKUTE_K = 0;
                 Tmp_KDB1.SOKUTE_CPK = 0;
                 break;
            }
         }
      }

      // P
      Tmp_KDB1.SOKUTE_P = 0;

    }
}
 // �ő�������߂�
 MaxNo = 0;
 for (i = 0; i < 20; i++)
     if (MaxNo < E_Screen_Data[2][i])
        MaxNo = E_Screen_Data[2][i];
 MaxNo += 10;

 // �X�P�[�������߂�
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (E_Standard_Scale[i] > T_double) {
       T_double = E_Standard_Scale[i];
       i = -1;
    }
 }
 E_Scale = T_double;
*/
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

    if ( keta > 0 ) {
    	str = "#0." + AnsiString::StringOfChar('0', keta );
	} else {
    	str = "#0";
    }
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

//�������ڏ����_�ȉ��̌����̏����Z�b�g
int __fastcall TForm3::KENSASYOSIKI_Set(int KMK,double JYOKEN,int KETA)
{
	int sBuf;

    switch(KMK)
    {
        case 0: //���[�h������
        	//sBuf = 2;
            sBuf = KETA;
            break;
        case 1: //�u���V��
        	//sBuf = 3;
           sBuf = KETA;
            break;

        case 3: //���[�h����t��R
        	sBuf = 1;
            break;

        case 4: //���[�h���������x
        	sBuf =1;
            break;

        case 5: //��̔�d
        	//sBuf = 2;
            sBuf = KETA;
            break;

        case 6: //�d�x
        	switch ( int(JYOKEN) )
            {
        		case 1: //�d�x ����
        			sBuf = 0;
            		break;

        		case 2: //�d�x ����
        			sBuf = 0;
            		break;

        		case 3: //�d�x ����
        			sBuf = 1;
            		break;

        		case 4: //�d�x ����
        			sBuf = 1;
            		break;

        		default:
                	sBuf = 3;
            		break;
        	}
            break;
        case 7: //�ŗL��R
        	sBuf = 0;
            break;

        case 8: //�R�ܗ�
        	sBuf = 1;
            break;

        case 9: //����
        	sBuf = 0;
            break;

        case 2: //���̑��i�m�M�X�j
        	//sBuf = 3;
            sBuf = KETA;
            break;

        case 10: //���̑��i�L�[�{�[�h�j
        	//sBuf = 2;
            sBuf = KETA;
             break;

        case 11: //���̑��i�ޗ������@�j
        	sBuf = 1;
            break;

        default:
        	sBuf = 3;
	}
	return( sBuf );
}


//---------------------------------------------------------------------------
//���v ��R�� �R���~�̏ꍇ L
void __fastcall TForm3::Tokei_TeikoL(void)
{
	int i,j;
	
	for ( i = 0; i < 20; i++ ) {
	    E_Screen_Data[2][i] = 0;
	}

	// �� Counter
	if (Cur_Kdb1.SOKUTE_SU > 0) {
		for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
			//for (j = 0; j < 20; j++) {    //2000.3.9
			//�d�� ��
			for (j = 19; j >= 0; j--) {
				if (j != 19) {
					if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF &&
							M_Kdb2[i].SOKUTEI_MEI3 < E_Screen_Data[1][j] - COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						j = -1;
					}
				} else { // j == 19
					if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI3 >= E_Screen_Data[0][j] + COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						//j = 20;       // 2000.3.9
						j = -1;
					}
			    }
			}
		}

	}

	if (Cur_Kdb1.HIST_SOKUT > 0) {
		if (Cur_Kdb1.SOKUTE_SU <= 0) {
			KETA.SOKUTE_AVE = 0;
			KETA.SOKUTE_MIN = 0;
			KETA.SOKUTE_MAX = 0;
			KETA.SOKUTE_R = 0;
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_P = 0;
			//KETA.SOKUTE_SU = 0;
		} else {  // ���v
			KETA.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_MEI3;
			KETA.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI3;
			KETA.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI3;

			// ���ϒl�A�ő�l�A�ŏ��l
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				KETA.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI3;
				if (KETA.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI3)
					KETA.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI3;
				if (KETA.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI3)
					KETA.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI3;
			}
			KETA.SOKUTE_AVE = KETA.SOKUTE_AVE/Cur_Kdb1.SOKUTE_SU;

			KETA.SOKUTE_R = KETA.SOKUTE_MAX - KETA.SOKUTE_MIN;

			// ��
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_P = 0;

			if (Cur_Kdb1.SOKUTE_SU > 1) {
			    for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				    KETA.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI3 -
										    KETA.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI3 -
										    KETA.SOKUTE_AVE);
			    }
			    KETA.SOKUTE_SGM = sqrt(KETA.SOKUTE_SGM / (Cur_Kdb1.SOKUTE_SU - 1));

			    if (KETA.SOKUTE_SGM > COM_DIFF) {
				    switch (Cur_Kdb1.HIST_KIKAK) {
					    case 1:
						    KETA.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
												    (6 * KETA.SOKUTE_SGM);
						    // K
						    KETA.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - KETA.SOKUTE_AVE) /
											    ((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

						    // CPK
						    KETA.SOKUTE_CPK = (1-KETA.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
											    	Cur_Kdb1.HIST_MIN) / (6 * KETA.SOKUTE_SGM);
						    break;
						    case 2:
							    KETA.SOKUTE_CP = fabs((KETA.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
													    (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
						    case 3:
							    KETA.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - KETA.SOKUTE_AVE)) /
												        (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
				    }
				}
			}
		}

		// P �s�Ǘ�
		int ErrorNo = 0;
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				// �K�i���f
				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
					if (M_Kdb2[i].SOKUTEI_MEI3 < Cur_Kdb1.HIST_MIN)
						ErrorNo++;
				}

				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                    //2008.05.21 E.Takase �K�i�L�����f�͈ȏ㖢��
					//if (M_Kdb2[i].SOKUTEI_MEI3 > Cur_Kdb1.HIST_MAX)
					if (M_Kdb2[i].SOKUTEI_MEI3+COM_DIFF >= Cur_Kdb1.HIST_MAX)
						ErrorNo++;
				}
			}
			KETA.SOKUTE_P = (double)ErrorNo/(double)Cur_Kdb1.SOKUTE_SU * 100.0;
		} else
			KETA.SOKUTE_P = 0;
	}

}

//---------------------------------------------------------------------------
//���v ��R�� �R���~�̏ꍇ R
void __fastcall TForm3::Tokei_TeikoR(void)
{
	int i,j;
	
	for ( i = 0; i < 20; i++ ) {
	    E_Screen_Data[2][i] = 0;
	}

	// �� Counter
	if (Cur_Kdb1.SOKUTE_SU > 0) {
		for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
			//for (j = 0; j < 20; j++) {    //2000.3.9
			//�d�� ��
			for (j = 19; j >= 0; j--) {
				if (j != 19) {
					if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF &&
							M_Kdb2[i].SOKUTEI_MEI5 < E_Screen_Data[1][j] - COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						j = -1;
					}
				} else { // j == 19
					if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - E_Screen_Data[0][j]) <= COM_DIFF ||
							(M_Kdb2[i].SOKUTEI_MEI5 >= E_Screen_Data[0][j] + COM_DIFF)) {
						E_Screen_Data[2][j] += 1;
						//j = 20;       // 2000.3.9
						j = -1;
					}
			    }
			}
		}

	}

	if (Cur_Kdb1.HIST_SOKUT > 0) {
		if (Cur_Kdb1.SOKUTE_SU <= 0) {
			KETA.SOKUTE_AVE = 0;
			KETA.SOKUTE_MIN = 0;
			KETA.SOKUTE_MAX = 0;
			KETA.SOKUTE_R = 0;
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_P = 0;
			//KETA.SOKUTE_SU = 0;
		} else {  // ���v
			KETA.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_MEI5;
			KETA.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI5;
			KETA.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI5;

			// ���ϒl�A�ő�l�A�ŏ��l
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				KETA.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI5;
				if (KETA.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI5)
					KETA.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI5;
				if (KETA.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI5)
					KETA.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI5;
			}
			KETA.SOKUTE_AVE = KETA.SOKUTE_AVE/Cur_Kdb1.SOKUTE_SU;

			KETA.SOKUTE_R = KETA.SOKUTE_MAX - KETA.SOKUTE_MIN;

			// ��
			KETA.SOKUTE_SGM = 0;
			KETA.SOKUTE_CP = 0;
			KETA.SOKUTE_K = 0;
			KETA.SOKUTE_CPK = 0;
			KETA.SOKUTE_P = 0;

			if (Cur_Kdb1.SOKUTE_SU > 1) {
			    for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				    KETA.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI5 -
										    KETA.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI5 -
										    KETA.SOKUTE_AVE);
			    }
			    KETA.SOKUTE_SGM = sqrt(KETA.SOKUTE_SGM / (Cur_Kdb1.SOKUTE_SU - 1));

			    if (KETA.SOKUTE_SGM > COM_DIFF) {
				    switch (Cur_Kdb1.HIST_KIKAK) {
					    case 1:
						    KETA.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
												    (6 * KETA.SOKUTE_SGM);
						    // K
						    KETA.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - KETA.SOKUTE_AVE) /
											    ((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

						    // CPK
						    KETA.SOKUTE_CPK = (1-KETA.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
											    	Cur_Kdb1.HIST_MIN) / (6 * KETA.SOKUTE_SGM);
						    break;
						    case 2:
							    KETA.SOKUTE_CP = fabs((KETA.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
													    (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
						    case 3:
							    KETA.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - KETA.SOKUTE_AVE)) /
												        (3 * KETA.SOKUTE_SGM);
							    KETA.SOKUTE_K = 0;
							    KETA.SOKUTE_CPK = 0;
							    break;
				    }
				}
			}
		}

		// P �s�Ǘ�
		int ErrorNo = 0;
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				// �K�i���f
				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
					if (M_Kdb2[i].SOKUTEI_MEI5 < Cur_Kdb1.HIST_MIN)
						ErrorNo++;
				}

				if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                    //2008.05.21 E.Takase �K�i�L�����f�͈ȏ㖢��
					//if (M_Kdb2[i].SOKUTEI_MEI5 > Cur_Kdb1.HIST_MAX)
					if (M_Kdb2[i].SOKUTEI_MEI5+COM_DIFF > Cur_Kdb1.HIST_MAX)
						ErrorNo++;
				}
			}
			KETA.SOKUTE_P = (double)ErrorNo/(double)Cur_Kdb1.SOKUTE_SU * 100.0;
		} else
			KETA.SOKUTE_P = 0;
	}

}

