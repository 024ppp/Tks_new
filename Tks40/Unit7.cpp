//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit2.h"
#include "unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//˽Ēǉ�
void __fastcall TForm1::AddHIST()
{
     AnsiString sYMD,sBuf,sBuf2;
     AnsiString Tmp_KENSA_YMD,Tmp_SEQNO;

     int i = 0;
     sYMD = DelSEPA(EdtYMD->Text);
     if( sYMD == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "�쐬������͂��Ă�������";
        SBr1->Update();
        KENSAKU_Mode = 1;
		EdtYMD->SetFocus();
        return;
     }
     if( Trim(EdtHIN->Text) == "" ){
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = "���Ӑ�i�Ԃ���͂��Ă�������";
        SBr1->Update();
        KENSAKU_Mode = 2;
		EdtHIN->SetFocus();
        return;
     }
     if( Trim(EdtLOT->Text) == "" ){
        //// �X�e�[�^�X���b�Z�[�W
        //SBr1->Panels->Items[0]->Text = "���b�gNO����͂��Ă�������";
        //SBr1->Update();
        //KENSAKU_Mode = 3;
	 	//EdtLOT->SetFocus();
        //return;
        EdtLOT->Text = " ";
     }


     // �X�e�[�^�X���b�Z�[�W
     SBr1->Panels->Items[0]->Text = MSG_01;
     SBr1->Update();

     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "SELECT * ";
	 sBuf += "FROM KDA1";

     sBuf += " where LOTNO = '";
     sBuf += EdtLOT->Text + "'";
     sBuf += " AND DTKSHIN = '";
     sBuf += EdtHIN->Text + "'";
     sBuf += " order by DTKSHIN,LOTNO";

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof == true ) {
     //�������� �O��
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = MSG_02;
        SBr1->Update();
        return;

     }

     //Tmp_KENSA_YMD	= Form1->Query1->FieldValues["KENSA_YMD"];
     //Tmp_SEQNO	= Form1->Query1->FieldValues["SEQNO"];

     Tmp_KDB1.KENSA_YMD  = sYMD;
	 //Tmp_KDB1.DTKSCOD	= Form1->Query1->FieldValues["DTKSCOD"];
	 Tmp_KDB1.DTKSHIN	= Form1->Query1->FieldValues["DTKSHIN"];
	 Tmp_KDB1.LOTNO		= Form1->Query1->FieldValues["LOTNO"];
	 Tmp_KDB1.HINBAN		= Form1->Query1->FieldValues["HINBAN"];
	 Tmp_KDB1.ZISCOD		= Form1->Query1->FieldValues["ZISCOD"];
	 Tmp_KDB1.ZISNAM		= Form1->Query1->FieldValues["ZISNAM"];
	 Tmp_KDB1.HIST_SOKUT	= Form1->Query1->FieldValues["HIST_SOKUT"];
	 Tmp_KDB1.HIST_KIKAK	= Form1->Query1->FieldValues["HIST_KIKAK"];
	 Tmp_KDB1.HIST_MIN	= Form1->Query1->FieldValues["HIST_MIN"];
	 Tmp_KDB1.HIST_MAX	= Form1->Query1->FieldValues["HIST_MAX"];
	 Tmp_KDB1.SOKUTE_SU	= Form1->Query1->FieldValues["SOKUTE_SU"];
	 Tmp_KDB1.SOKUTE_KET	= Form1->Query1->FieldValues["SOKUTE_KET"];
	 Tmp_KDB1.SOKUTE_AVE	= Form1->Query1->FieldValues["SOKUTE_AVE"];
	 Tmp_KDB1.SOKUTE_MIN	= Form1->Query1->FieldValues["SOKUTE_MIN"];
	 Tmp_KDB1.SOKUTE_MAX	= Form1->Query1->FieldValues["SOKUTE_MAX"];
	 Tmp_KDB1.SOKUTE_R	= Form1->Query1->FieldValues["SOKUTE_R"];
	 Tmp_KDB1.SOKUTE_SGM	= Form1->Query1->FieldValues["SOKUTE_SGM"];
	 Tmp_KDB1.SOKUTE_CP	= Form1->Query1->FieldValues["SOKUTE_CP"];
	 Tmp_KDB1.SOKUTE_CPK	= Form1->Query1->FieldValues["SOKUTE_CPK"];
	 Tmp_KDB1.SOKUTE_K	= Form1->Query1->FieldValues["SOKUTE_K"];
	 Tmp_KDB1.SOKUTE_P	= Form1->Query1->FieldValues["SOKUTE_P"];
	 Tmp_KDB1.ADDYMD		= Form1->Query1->FieldValues["ADDYMD"];
	 Tmp_KDB1.ADDTIM		= Form1->Query1->FieldValues["ADDTIM"];
	 Tmp_KDB1.UPDYMD		= Form1->Query1->FieldValues["UPDYMD"];
	 Tmp_KDB1.UPDTIM		= Form1->Query1->FieldValues["UPDTIM"];
	 Tmp_KDB1.UPDCHR		= Form1->Query1->FieldValues["UPDCHR"];
	 Tmp_KDB1.UPDCNT		= Form1->Query1->FieldValues["UPDCNT"];

     Tmp_KDB1.SEQNO = SEQNOMAX + 1;
     Tmp_KDB1.KENSA_KMK = 1;
     Tmp_KDB1.KOUMOKU_J = Form1->Cmb1->Items->Strings[1];
     Tmp_KDB1.KOUMOKU_E = Form1->Cmb2->Items->Strings[1];
     //���i�K�i�̌`��敪�P�C�Q�C�R�Ȃ� �P
     //                  �S�Ȃ� �Q
	 switch(KEIJKBN_KM02)
	 {
		case 1: //���^�u���b�N
		case 2: //���^
		case 3: //��^
			Tmp_KDB1.KEIJKBN = 1;
			break;
		case 4: //�~��
			Tmp_KDB1.KEIJKBN = 2;
		case 5: //�R���~  //2002/12/28 E.Takase
			Tmp_KDB1.KEIJKBN = 3;
			break;
     }
     Tmp_KDB1.TANI = "mm";

     //�V�K�o�^
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "select KENSA_YMD from KDB1 ";
     sBuf +=" where KENSA_YMD='" + Tmp_KDB1.KENSA_YMD + "'";  // �����
     sBuf +=" AND SEQNO=" + IntToStr(Tmp_KDB1.SEQNO);         // SEQNO
     sBuf +=" AND DTKSHIN='" + Tmp_KDB1.DTKSHIN + "'";        // DTKSHIN
     sBuf +=" AND LOTNO='" + Tmp_KDB1.LOTNO + "'";            // LOTNO

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
        Query1->Open();
        Query1->Active = true;

        if( !(Query1->Eof == True &&  Query1->Bof == True) ){
            SBr1->Panels->Items[0]->Text = "���ɓo�^����Ă��܂��B";
            SBr1->Update();
            return;
        }
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return;
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return;
     }


     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����쐬
     sBuf = "insert into KDB1(";
	 sBuf += " KENSA_YMD,DTKSHIN,LOTNO,HINBAN,ZISCOD,ZISNAM,HIST_SOKUT,";
	 sBuf += " HIST_KIKAK,HIST_MIN,HIST_MAX,SOKUTE_SU,SOKUTE_KET,SOKUTE_AVE,";
	 sBuf += " SOKUTE_MIN,SOKUTE_MAX,SOKUTE_R,SOKUTE_SGM,SOKUTE_CP,SOKUTE_CPK,";
	 sBuf += " SOKUTE_K,SOKUTE_P,ADDYMD,ADDTIM,UPDYMD,UPDTIM,UPDCHR,UPDCNT,";
	 sBuf += " SEQNO,KENSA_KMK,KOUMOKU_J,KOUMOKU_E,KEIJKBN,TANI";
     sBuf += " )";

     sBuf += " values('";
	 sBuf += Tmp_KDB1.KENSA_YMD				+ "','";
	 sBuf += Tmp_KDB1.DTKSHIN				+ "','";
	 sBuf += Tmp_KDB1.LOTNO					+ "','";
	 sBuf += Tmp_KDB1.HINBAN				+ "','";
	 sBuf += Tmp_KDB1.ZISCOD				+ "','";
	 sBuf += Tmp_KDB1.ZISNAM				+ "',";
	 sBuf += IntToStr(Tmp_KDB1.HIST_SOKUT)	+ ",";
	 sBuf += IntToStr(Tmp_KDB1.HIST_KIKAK)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.HIST_MIN)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.HIST_MAX)	+ ",";
	 sBuf += IntToStr(Tmp_KDB1.SOKUTE_SU)	+ ",";
	 sBuf += IntToStr(Tmp_KDB1.SOKUTE_KET)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_AVE)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_MIN)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_MAX)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_R)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_SGM)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_CP)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_CPK)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_K)	+ ",";
	 sBuf += FloatToStr(Tmp_KDB1.SOKUTE_P)	+ ",'";
	 sBuf += Tmp_KDB1.ADDYMD				+ "','";
	 sBuf += Tmp_KDB1.ADDTIM				+ "','";
	 sBuf += Tmp_KDB1.UPDYMD				+ "','";
	 sBuf += Tmp_KDB1.UPDTIM				+ "',";
	 sBuf += IntToStr(Tmp_KDB1.UPDCHR)		+ ",";
	 sBuf += IntToStr(Tmp_KDB1.UPDCNT)		+ ",";

	 sBuf += IntToStr(Tmp_KDB1.SEQNO)		+ ",";
	 sBuf += IntToStr(Tmp_KDB1.KENSA_KMK)	+ ",'";
	 sBuf += Tmp_KDB1.KOUMOKU_J				+ "','";
	 sBuf += Tmp_KDB1.KOUMOKU_E				+ "',";
	 sBuf += IntToStr(Tmp_KDB1.KEIJKBN)		+ ",'";
	 sBuf += Tmp_KDB1.TANI          		+ "'";

     sBuf += ")";

     Query1->SQL->Add(sBuf);

     // �₢�������̎��s
     try
     {
         Query1->ExecSQL();
     }
     catch(EDatabaseError& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return;
     }
     catch(Exception& e)
     {
         SBr1->Panels->Items[0]->Text = e.Message;
         SBr1->Update();
         return;
     }


     //KDA2
     // Initial Query
     Query1->Close();
     Query1->SQL->Clear();

     // �⍇�����s
     sBuf = "SELECT * ";
	 sBuf += "FROM KDA2";

     sBuf += " where LOTNO = '";
     sBuf += EdtLOT->Text + "'";
     sBuf += " AND DTKSHIN = '";
     sBuf += EdtHIN->Text + "'";
     //sBuf += " where KENSA_YMD = '";
     //sBuf += Tmp_KENSA_YMD + "'";
     //sBuf += " AND SEQNO = '";
     //sBuf += Tmp_SEQNO + "'";
     sBuf += "order by KENSA_YMD,SEQNO,SOKUTEI_NO";

     Query1->SQL->Add(sBuf);
     Query1->Open();
     Query1->Active = true;

     if ( Query1->Bof == true && Query1->Eof ) {
     //�������� �O��
        // �X�e�[�^�X���b�Z�[�W
        SBr1->Panels->Items[0]->Text = MSG_02;
        SBr1->Update();
        //return;
     } else {

        //�V�K�o�^
        Query1->First();
        sBuf = "insert into KDB2(KENSA_YMD, DTKSHIN, HINBAN, ZISCOD,";
        sBuf += "ZISNAM, LOTNO, SEQNO, SOKUTEI_NO, SOKUTEI_CH";
        sBuf += " )";
        sBuf += " values('";
        sBuf += Tmp_KDB1.KENSA_YMD				+ "','";
        sBuf += Tmp_KDB1.DTKSHIN				+ "','";
        sBuf += Tmp_KDB1.HINBAN				+ "','";
        sBuf += Tmp_KDB1.ZISCOD				+ "','";
        sBuf += Tmp_KDB1.ZISNAM				+ "','";
        sBuf += Tmp_KDB1.LOTNO					+ "',";
        sBuf += IntToStr(Tmp_KDB1.SEQNO)	+ ",";
        while( !Query1->Eof ){
                 i++;
                 sBuf2 = Form1->Query1->FieldValues["SOKUTEI_NO"];
                 sBuf2 += ",";
                 sBuf2 += Form1->Query1->FieldValues["SOKUTEI_CH"];

                 sBuf2 += " )";

                 // Initial Query
                 Query2->Close();
                 Query2->SQL->Clear();
                 Query2->SQL->Add(sBuf + sBuf2);

                 // �₢�������̎��s
                 try
                 {
                          Query2->ExecSQL();
                 }
                          catch(EDatabaseError& e)
                 {
                          SBr1->Panels->Items[0]->Text = e.Message;
                          SBr1->Update();
                          return;
                 }
                 catch(Exception& e)
                 {
                          SBr1->Panels->Items[0]->Text = e.Message;
                          SBr1->Update();
                          return;
                 }

                          Query1->Next();
              }
        }

        //�V�K�f�[�^��SGr1�ɕ\��
        // �O���b�h�Ƀf�[�^���Z�b�g���܂��B
        sBuf = SGr1->RowCount;
		SGr1->Cells[0][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 3-sBuf.Length()) + sBuf;    //No

		sBuf = Tmp_KDB1.KOUMOKU_J;
		SGr1->Cells[1][SGr1->RowCount - 1] = sBuf;   //�������ځi���{��j

		sBuf = Tmp_KDB1.KOUMOKU_E;
		SGr1->Cells[2][SGr1->RowCount - 1] = sBuf;   //�������ځi�p��j

		sBuf = IntToStr(Tmp_KDB1.HIST_SOKUT);
		SGr1->Cells[4][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 6-sBuf.Length()) + sBuf;   //���萔

		sBuf = Tmp_KDB1.TANI;
		SGr1->Cells[3][SGr1->RowCount - 1] = sBuf;   //�P��

		sBuf = IntToStr(Tmp_KDB1.KEIJKBN);
		SGr1->Cells[11][SGr1->RowCount - 1] = sBuf;   //�`��敪
        switch(Tmp_KDB1.KEIJKBN)
        {
			case 1: //������
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "������";
                SGr1->Cells[30][SGr1->RowCount - 1] = "������";
                break;
            case 2: //�~��
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "�~��";
                SGr1->Cells[30][SGr1->RowCount - 1] = "�~��";
                break;
            case 3: //�R���~
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = "�R���~";
                SGr1->Cells[30][SGr1->RowCount - 1] = "�R���~";
                break;
            //case 1: //���^�u���b�N
            //    SGr1->Cells[3][SGr1->RowCount - 1] = "���^";
            //    break;
            //case 2: //���^
            //    SGr1->Cells[3][SGr1->RowCount - 1] = "���^";
            //    break;
            //case 3: //��^
            //    SGr1->Cells[3][SGr1->RowCount - 1] = "��^";
            //    break;
            //case 4: //�~��
            //    SGr1->Cells[3][SGr1->RowCount - 1] = "�~��";
            //    break;
            default:
                //2002/11/18 E.Takase SGr1->Cells[9][SGr1->RowCount - 1] = " ";
                SGr1->Cells[30][SGr1->RowCount - 1] = " ";
                break;

        }

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		          switch(Tmp_KDB1.HIST_KIKAK )   //�K�i��
		          {
		            case 1:
				        SGr1->Cells[5][SGr1->RowCount - 1] = "����";

				        sBuf = FormatFloat("#0.000",Tmp_KDB1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
				        SGr1->Cells[6][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

				        sBuf = FormatFloat("#0.000",Tmp_KDB1.HIST_MAX);//	�@�V�@�@�@�@����K�i
				        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
			                break;

		            case 2:
				        SGr1->Cells[5][SGr1->RowCount - 1] = "����";

				        sBuf = FormatFloat("#0.000",Tmp_KDB1.HIST_MIN);//	�@�V�@�@�@�@�����K�i
				        SGr1->Cells[6][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

				        sBuf = " ";//	�@�V�@�@�@�@����K�i
				        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
			                break;

			            case 3:
				        SGr1->Cells[5][SGr1->RowCount - 1] = "���";

				        sBuf = " ";//	�@�V�@�@�@�@�����K�i
				        SGr1->Cells[6][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;

				        sBuf =FormatFloat("#0.000", Tmp_KDB1.HIST_MAX);//	�@�V�@�@�@�@����K�i
				        SGr1->Cells[7][SGr1->RowCount - 1] = AnsiString::StringOfChar(' ', 9 - sBuf.Length()) + sBuf;
			                break;

		          }

				if ( Tmp_KDB1.HIST_SOKUT == Tmp_KDB1.SOKUTE_SU ) {
					sBuf = "��";//	�����
				} else  {
		            if (Tmp_KDB1.SOKUTE_SU > 0 ) {
		                sBuf = "�r��";//	����r��
		            } else {
		                sBuf = "��";//	������
		            }
		        }
				SGr1->Cells[8][SGr1->RowCount - 1] = sBuf;


		sBuf = Tmp_KDB1.KENSA_YMD;
		SGr1->Cells[10][SGr1->RowCount - 1] = sBuf;                //�����N����

		sBuf = Tmp_KDB1.DTKSHIN;
		SGr1->Cells[12][SGr1->RowCount - 1] = sBuf;                //���Ӑ�i��

		sBuf = Tmp_KDB1.HINBAN;
		SGr1->Cells[13][SGr1->RowCount - 1] = sBuf;               //���Еi��

		sBuf = Tmp_KDB1.ZISCOD;
		SGr1->Cells[14][SGr1->RowCount - 1] = sBuf;               //�ގ��R�[�h

		sBuf = Tmp_KDB1.ZISNAM;
		SGr1->Cells[15][SGr1->RowCount - 1] = sBuf;               //�ގ���

		sBuf = Tmp_KDB1.LOTNO;
		SGr1->Cells[16][SGr1->RowCount - 1] = sBuf;               //���b�gNO

		sBuf = IntToStr(Tmp_KDB1.SEQNO);
		SGr1->Cells[17][SGr1->RowCount - 1] = sBuf;               //SEQNO

		sBuf = IntToStr(Tmp_KDB1.KENSA_KMK);
		SGr1->Cells[18][SGr1->RowCount - 1] = sBuf;               //��������

		sBuf = IntToStr(Tmp_KDB1.HIST_KIKAK);
		SGr1->Cells[19][SGr1->RowCount - 1] = sBuf;               //�H���\�� �K�i

		sBuf = IntToStr(Tmp_KDB1.SOKUTE_SU);
		SGr1->Cells[20][SGr1->RowCount - 1] = sBuf;               //���萔

		sBuf = Tmp_KDB1.ADDYMD;
		SGr1->Cells[21][SGr1->RowCount - 1] = sBuf;               //�o�^��

		sBuf = Tmp_KDB1.ADDTIM;
		SGr1->Cells[22][SGr1->RowCount - 1] = sBuf;               //�o�^����

		sBuf = " ";
		SGr1->Cells[23][SGr1->RowCount - 1] = sBuf;               //�ύX��

		sBuf = " ";
		SGr1->Cells[24][SGr1->RowCount - 1] = sBuf;               //�ύX����

		sBuf = IntToStr(Tmp_KDB1.UPDCHR);
		SGr1->Cells[25][SGr1->RowCount - 1] = sBuf;               //�X�V��

		sBuf = IntToStr(Tmp_KDB1.UPDCNT);
		SGr1->Cells[26][SGr1->RowCount - 1] = sBuf;               //�X�V��

        //2002/11/18 E.Takase ����Ғǉ�
		sBuf = Tmp_KDB1.UPDCHR;
		SGr1->Cells[9][SGr1->RowCount - 1] = Form2->GetTANNAM(sBuf);

     // ��s���₷
     SGr1->RowCount = SGr1->RowCount + 1;

     // �V�����s��I��
     SGr1->Row = SGr1->RowCount - 1;

     SGr1->SetFocus();

     SBr1->Panels->Items[0]->Text = "";
     SBr1->Update();

     // �f�[�^��ύX�����t���O
     DataSave = true;
     SEQNOMAX ++;

}


//�P�ʂƋK�i�������Ă��邩�`�F�b�N
int __fastcall TForm1::CheckTANI(int K,AnsiString sTANI)
{
    if ( K == 5 && Trim(sTANI) == "" ) {
    	Cmb5->ItemIndex = 0;
    	return(1);
    }
    if ( Cmb5->Items->IndexOf( sTANI ) != -1 ) return(1);
    else  return(0);
    

}

//�K�i�ɂ������P�ʂ��Z�b�g
void __fastcall TForm1::SetTANI(int K)
{
  /*
    Cmb5->Clear();
    switch(K)
    {
        case 0: //���[�h������
            Cmb5->Items->Add( "mm" );
            break;

        case 1: //�u���V��
            Cmb5->Items->Add( "mm" );
            break;

        case 2: //�u���V�c����
            Cmb5->Items->Add( "mm" );
            break;

        case 3: //���[�h����t��R
            Cmb5->Items->Add( "mV/A" );
            break;

        case 4: //���[�h���������x
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            break;

        case 5: //��̔�d
            Cmb5->Items->Add( " " );
            break;

        case 6: //�d�x
            Cmb5->Items->Add( "HsC" );
            Cmb5->Items->Add( "HsD" );
            break;

        case 7: //�ŗL��R
            Cmb5->Items->Add( "�ʃ��Ecm" );
            break;

        case 8: //�R�ܗ�
            Cmb5->Items->Add( "Kgf/cm2" );
            Cmb5->Items->Add( "N/cm2" );
            Cmb5->Items->Add( "MPa" );
            Cmb5->Items->Add( "N/mm2" );
            break;

        case 9: //����
            Cmb5->Items->Add( "N" );
            break;

        default:
            Cmb5->Items->Add( "mm" );
            Cmb5->Items->Add( "Kgf" );
            Cmb5->Items->Add( "N" );
            Cmb5->Items->Add( "�x" );
            break;

    }
*/
    return;


}


