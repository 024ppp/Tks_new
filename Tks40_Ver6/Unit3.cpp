//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <math.h>
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "SharedMemory.h"
#include "Unit11.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NumberEdit"
#pragma resource "*.dfm"
TForm3 *Form3;

#define COM_DIFF 0.000001
#define S_Cp 1.33
#define S_Cpk 1.33

// π値
double pi = 3.1415926535;

//---------------------------------------------------------------------------
//RS232C通信用変数
char SharedBuff[BUFFERSIZE];                    // 受信BUFFER
#define ConnectFlag 1
int iShareFlag = 0 ;                           // RS232C接続フラグ
int ShareFlag = 0;
int CurrentChannel = 1;                        // 現在使うチャンネル番号
int OldChannel;                                // 母体比重計測、固有抵抗率、抗折力のみ
int F4Flag, F8Flag, F9Flag;

const int Nums = 500;
TNumberEdit *T_Edit[Nums];
TPanel *T_Panel[Nums];
TPanel *S_Panel[3][20];

extern KDB1_DATA Cur_Kdb1;             // 選択したヒストグラムデータ

extern KDB2_DATA M_Kdb2[1000];         // 計測データ（最大値：１０００個）

extern int USER_COD;

double Standard_Scale[20] = {500, 100, 50, 20, 10, 5, 2, 1, 0.5, 0.2, 0.1, 0.05,
                           0.02, 0.01, 0.005, 0.002, 0.001, 0.0005, 0.0002, 0.0001};

double Screen_Data[3][20];

extern double E_Screen_Data[3][20];

extern int E_Scale;

void StatBarClear( AnsiString sMsg, int Opt );
AnsiString ConvData(int Keta, double T_double);

int MsgFlag = 0;

void WriteLog(char *Msg);

extern int ShellExeFlag;

int WriteDatabaseError = 0;    // データベースへ書込みエラーフラグ

int IsNullSpace( AnsiString  str );
void SaveKDB1();

int ScreenInitFlag = 0;

int F10Flag = 1;   // 0: Sound & Color Off
                   // 1: Sound & Color On

int EndErrorFlag = 0;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
     Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
 char DirName[256], FileName[256], tempo[64];

 WriteLog("Tks40.exe起動");

 GetCurrentDirectory(256,DirName);
 sprintf(FileName, "%s\\Tks.ini", DirName);
 GetPrivateProfileString("MAIN", "KIKITYPE", "", tempo, 64, FileName);
 KikiType = atoi(tempo);
 //2009.03.13 MTS E.Takase [001]  ↓
 //材料試験機（単独使用）は機器タイプを5とする
 //if (KikiType <= 0 || KikiType > 4)
 //if (KikiType <= 0 || KikiType > 5)
 //2009.03.13 MTS E.Takase [001]  ↑
 //20160729 KikiType=6の追加
 if (KikiType <= 0 || KikiType > 6)
    ShowMessage( MSG_00 );

 T_Edit[0] = Edt_001;
 T_Edit[1] = Edt_002;
 T_Edit[2] = Edt_003;
 T_Edit[3] = Edt_004;
 T_Edit[4] = Edt_005;
 T_Edit[5] = Edt_006;
 T_Edit[6] = Edt_007;
 T_Edit[7] = Edt_008;
 T_Edit[8] = Edt_009;
 T_Edit[9] = Edt_010;
 T_Edit[10] = Edt_011;
 T_Edit[11] = Edt_012;
 T_Edit[12] = Edt_013;
 T_Edit[13] = Edt_014;
 T_Edit[14] = Edt_015;
 T_Edit[15] = Edt_016;
 T_Edit[16] = Edt_017;
 T_Edit[17] = Edt_018;
 T_Edit[18] = Edt_019;
 T_Edit[19] = Edt_020;
 T_Edit[20] = Edt_021;
 T_Edit[21] = Edt_022;
 T_Edit[22] = Edt_023;
 T_Edit[23] = Edt_024;
 T_Edit[24] = Edt_025;
 T_Edit[25] = Edt_026;
 T_Edit[26] = Edt_027;
 T_Edit[27] = Edt_028;
 T_Edit[28] = Edt_029;
 T_Edit[29] = Edt_030;
 T_Edit[30] = Edt_031;
 T_Edit[31] = Edt_032;
 T_Edit[32] = Edt_033;
 T_Edit[33] = Edt_034;
 T_Edit[34] = Edt_035;
 T_Edit[35] = Edt_036;
 T_Edit[36] = Edt_037;
 T_Edit[37] = Edt_038;
 T_Edit[38] = Edt_039;
 T_Edit[39] = Edt_040;
 T_Edit[40] = Edt_041;
 T_Edit[41] = Edt_042;
 T_Edit[42] = Edt_043;
 T_Edit[43] = Edt_044;
 T_Edit[44] = Edt_045;
 T_Edit[45] = Edt_046;
 T_Edit[46] = Edt_047;
 T_Edit[47] = Edt_048;
 T_Edit[48] = Edt_049;
 T_Edit[49] = Edt_050;
 T_Edit[50] = Edt_051;
 T_Edit[51] = Edt_052;
 T_Edit[52] = Edt_053;
 T_Edit[53] = Edt_054;
 T_Edit[54] = Edt_055;
 T_Edit[55] = Edt_056;
 T_Edit[56] = Edt_057;
 T_Edit[57] = Edt_058;
 T_Edit[58] = Edt_059;
 T_Edit[59] = Edt_060;
 T_Edit[60] = Edt_061;
 T_Edit[61] = Edt_062;
 T_Edit[62] = Edt_063;
 T_Edit[63] = Edt_064;
 T_Edit[64] = Edt_065;
 T_Edit[65] = Edt_066;
 T_Edit[66] = Edt_067;
 T_Edit[67] = Edt_068;
 T_Edit[68] = Edt_069;
 T_Edit[69] = Edt_070;
 T_Edit[70] = Edt_071;
 T_Edit[71] = Edt_072;
 T_Edit[72] = Edt_073;
 T_Edit[73] = Edt_074;
 T_Edit[74] = Edt_075;
 T_Edit[75] = Edt_076;
 T_Edit[76] = Edt_077;
 T_Edit[77] = Edt_078;
 T_Edit[78] = Edt_079;
 T_Edit[79] = Edt_080;
 T_Edit[80] = Edt_081;
 T_Edit[81] = Edt_082;
 T_Edit[82] = Edt_083;
 T_Edit[83] = Edt_084;
 T_Edit[84] = Edt_085;
 T_Edit[85] = Edt_086;
 T_Edit[86] = Edt_087;
 T_Edit[87] = Edt_088;
 T_Edit[88] = Edt_089;
 T_Edit[89] = Edt_090;
 T_Edit[90] = Edt_091;
 T_Edit[91] = Edt_092;
 T_Edit[92] = Edt_093;
 T_Edit[93] = Edt_094;
 T_Edit[94] = Edt_095;
 T_Edit[95] = Edt_096;
 T_Edit[96] = Edt_097;
 T_Edit[97] = Edt_098;
 T_Edit[98] = Edt_099;
 T_Edit[99] = Edt_100;
 T_Edit[100] = Edt_101;
 T_Edit[101] = Edt_102;
 T_Edit[102] = Edt_103;
 T_Edit[103] = Edt_104;
 T_Edit[104] = Edt_105;
 T_Edit[105] = Edt_106;
 T_Edit[106] = Edt_107;
 T_Edit[107] = Edt_108;
 T_Edit[108] = Edt_109;
 T_Edit[109] = Edt_110;
 T_Edit[110] = Edt_111;
 T_Edit[111] = Edt_112;
 T_Edit[112] = Edt_113;
 T_Edit[113] = Edt_114;
 T_Edit[114] = Edt_115;
 T_Edit[115] = Edt_116;
 T_Edit[116] = Edt_117;
 T_Edit[117] = Edt_118;
 T_Edit[118] = Edt_119;
 T_Edit[119] = Edt_120;
 T_Edit[120] = Edt_121;
 T_Edit[121] = Edt_122;
 T_Edit[122] = Edt_123;
 T_Edit[123] = Edt_124;
 T_Edit[124] = Edt_125;
 T_Edit[125] = Edt_126;
 T_Edit[126] = Edt_127;
 T_Edit[127] = Edt_128;
 T_Edit[128] = Edt_129;
 T_Edit[129] = Edt_130;
 T_Edit[130] = Edt_131;
 T_Edit[131] = Edt_132;
 T_Edit[132] = Edt_133;
 T_Edit[133] = Edt_134;
 T_Edit[134] = Edt_135;
 T_Edit[135] = Edt_136;
 T_Edit[136] = Edt_137;
 T_Edit[137] = Edt_138;
 T_Edit[138] = Edt_139;
 T_Edit[139] = Edt_140;
 T_Edit[140] = Edt_141;
 T_Edit[141] = Edt_142;
 T_Edit[142] = Edt_143;
 T_Edit[143] = Edt_144;
 T_Edit[144] = Edt_145;
 T_Edit[145] = Edt_146;
 T_Edit[146] = Edt_147;
 T_Edit[147] = Edt_148;
 T_Edit[148] = Edt_149;
 T_Edit[149] = Edt_150;
 T_Edit[150] = Edt_151;
 T_Edit[151] = Edt_152;
 T_Edit[152] = Edt_153;
 T_Edit[153] = Edt_154;
 T_Edit[154] = Edt_155;
 T_Edit[155] = Edt_156;
 T_Edit[156] = Edt_157;
 T_Edit[157] = Edt_158;
 T_Edit[158] = Edt_159;
 T_Edit[159] = Edt_160;
 T_Edit[160] = Edt_161;
 T_Edit[161] = Edt_162;
 T_Edit[162] = Edt_163;
 T_Edit[163] = Edt_164;
 T_Edit[164] = Edt_165;
 T_Edit[165] = Edt_166;
 T_Edit[166] = Edt_167;
 T_Edit[167] = Edt_168;
 T_Edit[168] = Edt_169;
 T_Edit[169] = Edt_170;
 T_Edit[170] = Edt_171;
 T_Edit[171] = Edt_172;
 T_Edit[172] = Edt_173;
 T_Edit[173] = Edt_174;
 T_Edit[174] = Edt_175;
 T_Edit[175] = Edt_176;
 T_Edit[176] = Edt_177;
 T_Edit[177] = Edt_178;
 T_Edit[178] = Edt_179;
 T_Edit[179] = Edt_180;
 T_Edit[180] = Edt_181;
 T_Edit[181] = Edt_182;
 T_Edit[182] = Edt_183;
 T_Edit[183] = Edt_184;
 T_Edit[184] = Edt_185;
 T_Edit[185] = Edt_186;
 T_Edit[186] = Edt_187;
 T_Edit[187] = Edt_188;
 T_Edit[188] = Edt_189;
 T_Edit[189] = Edt_190;
 T_Edit[190] = Edt_191;
 T_Edit[191] = Edt_192;
 T_Edit[192] = Edt_193;
 T_Edit[193] = Edt_194;
 T_Edit[194] = Edt_195;
 T_Edit[195] = Edt_196;
 T_Edit[196] = Edt_197;
 T_Edit[197] = Edt_198;
 T_Edit[198] = Edt_199;
 T_Edit[199] = Edt_200;
 T_Edit[200] = Edt_201;
 T_Edit[201] = Edt_202;
 T_Edit[202] = Edt_203;
 T_Edit[203] = Edt_204;
 T_Edit[204] = Edt_205;
 T_Edit[205] = Edt_206;
 T_Edit[206] = Edt_207;
 T_Edit[207] = Edt_208;
 T_Edit[208] = Edt_209;
 T_Edit[209] = Edt_210;
 T_Edit[210] = Edt_211;
 T_Edit[211] = Edt_212;
 T_Edit[212] = Edt_213;
 T_Edit[213] = Edt_214;
 T_Edit[214] = Edt_215;
 T_Edit[215] = Edt_216;
 T_Edit[216] = Edt_217;
 T_Edit[217] = Edt_218;
 T_Edit[218] = Edt_219;
 T_Edit[219] = Edt_220;
 T_Edit[220] = Edt_221;
 T_Edit[221] = Edt_222;
 T_Edit[222] = Edt_223;
 T_Edit[223] = Edt_224;
 T_Edit[224] = Edt_225;
 T_Edit[225] = Edt_226;
 T_Edit[226] = Edt_227;
 T_Edit[227] = Edt_228;
 T_Edit[228] = Edt_229;
 T_Edit[229] = Edt_230;
 T_Edit[230] = Edt_231;
 T_Edit[231] = Edt_232;
 T_Edit[232] = Edt_233;
 T_Edit[233] = Edt_234;
 T_Edit[234] = Edt_235;
 T_Edit[235] = Edt_236;
 T_Edit[236] = Edt_237;
 T_Edit[237] = Edt_238;
 T_Edit[238] = Edt_239;
 T_Edit[239] = Edt_240;
 T_Edit[240] = Edt_241;
 T_Edit[241] = Edt_242;
 T_Edit[242] = Edt_243;
 T_Edit[243] = Edt_244;
 T_Edit[244] = Edt_245;
 T_Edit[245] = Edt_246;
 T_Edit[246] = Edt_247;
 T_Edit[247] = Edt_248;
 T_Edit[248] = Edt_249;
 T_Edit[249] = Edt_250;
 T_Edit[250] = Edt_251;
 T_Edit[251] = Edt_252;
 T_Edit[252] = Edt_253;
 T_Edit[253] = Edt_254;
 T_Edit[254] = Edt_255;
 T_Edit[255] = Edt_256;
 T_Edit[256] = Edt_257;
 T_Edit[257] = Edt_258;
 T_Edit[258] = Edt_259;
 T_Edit[259] = Edt_260;
 T_Edit[260] = Edt_261;
 T_Edit[261] = Edt_262;
 T_Edit[262] = Edt_263;
 T_Edit[263] = Edt_264;
 T_Edit[264] = Edt_265;
 T_Edit[265] = Edt_266;
 T_Edit[266] = Edt_267;
 T_Edit[267] = Edt_268;
 T_Edit[268] = Edt_269;
 T_Edit[269] = Edt_270;
 T_Edit[270] = Edt_271;
 T_Edit[271] = Edt_272;
 T_Edit[272] = Edt_273;
 T_Edit[273] = Edt_274;
 T_Edit[274] = Edt_275;
 T_Edit[275] = Edt_276;
 T_Edit[276] = Edt_277;
 T_Edit[277] = Edt_278;
 T_Edit[278] = Edt_279;
 T_Edit[279] = Edt_280;
 T_Edit[280] = Edt_281;
 T_Edit[281] = Edt_282;
 T_Edit[282] = Edt_283;
 T_Edit[283] = Edt_284;
 T_Edit[284] = Edt_285;
 T_Edit[285] = Edt_286;
 T_Edit[286] = Edt_287;
 T_Edit[287] = Edt_288;
 T_Edit[288] = Edt_289;
 T_Edit[289] = Edt_290;
 T_Edit[290] = Edt_291;
 T_Edit[291] = Edt_292;
 T_Edit[292] = Edt_293;
 T_Edit[293] = Edt_294;
 T_Edit[294] = Edt_295;
 T_Edit[295] = Edt_296;
 T_Edit[296] = Edt_297;
 T_Edit[297] = Edt_298;
 T_Edit[298] = Edt_299;
 T_Edit[299] = Edt_300;
 T_Edit[300] = Edt_301;
 T_Edit[301] = Edt_302;
 T_Edit[302] = Edt_303;
 T_Edit[303] = Edt_304;
 T_Edit[304] = Edt_305;
 T_Edit[305] = Edt_306;
 T_Edit[306] = Edt_307;
 T_Edit[307] = Edt_308;
 T_Edit[308] = Edt_309;
 T_Edit[309] = Edt_310;
 T_Edit[310] = Edt_311;
 T_Edit[311] = Edt_312;
 T_Edit[312] = Edt_313;
 T_Edit[313] = Edt_314;
 T_Edit[314] = Edt_315;
 T_Edit[315] = Edt_316;
 T_Edit[316] = Edt_317;
 T_Edit[317] = Edt_318;
 T_Edit[318] = Edt_319;
 T_Edit[319] = Edt_320;
 T_Edit[320] = Edt_321;
 T_Edit[321] = Edt_322;
 T_Edit[322] = Edt_323;
 T_Edit[323] = Edt_324;
 T_Edit[324] = Edt_325;
 T_Edit[325] = Edt_326;
 T_Edit[326] = Edt_327;
 T_Edit[327] = Edt_328;
 T_Edit[328] = Edt_329;
 T_Edit[329] = Edt_330;
 T_Edit[330] = Edt_331;
 T_Edit[331] = Edt_332;
 T_Edit[332] = Edt_333;
 T_Edit[333] = Edt_334;
 T_Edit[334] = Edt_335;
 T_Edit[335] = Edt_336;
 T_Edit[336] = Edt_337;
 T_Edit[337] = Edt_338;
 T_Edit[338] = Edt_339;
 T_Edit[339] = Edt_340;
 T_Edit[340] = Edt_341;
 T_Edit[341] = Edt_342;
 T_Edit[342] = Edt_343;
 T_Edit[343] = Edt_344;
 T_Edit[344] = Edt_345;
 T_Edit[345] = Edt_346;
 T_Edit[346] = Edt_347;
 T_Edit[347] = Edt_348;
 T_Edit[348] = Edt_349;
 T_Edit[349] = Edt_350;
 T_Edit[350] = Edt_351;
 T_Edit[351] = Edt_352;
 T_Edit[352] = Edt_353;
 T_Edit[353] = Edt_354;
 T_Edit[354] = Edt_355;
 T_Edit[355] = Edt_356;
 T_Edit[356] = Edt_357;
 T_Edit[357] = Edt_358;
 T_Edit[358] = Edt_359;
 T_Edit[359] = Edt_360;
 T_Edit[360] = Edt_361;
 T_Edit[361] = Edt_362;
 T_Edit[362] = Edt_363;
 T_Edit[363] = Edt_364;
 T_Edit[364] = Edt_365;
 T_Edit[365] = Edt_366;
 T_Edit[366] = Edt_367;
 T_Edit[367] = Edt_368;
 T_Edit[368] = Edt_369;
 T_Edit[369] = Edt_370;
 T_Edit[370] = Edt_371;
 T_Edit[371] = Edt_372;
 T_Edit[372] = Edt_373;
 T_Edit[373] = Edt_374;
 T_Edit[374] = Edt_375;
 T_Edit[375] = Edt_376;
 T_Edit[376] = Edt_377;
 T_Edit[377] = Edt_378;
 T_Edit[378] = Edt_379;
 T_Edit[379] = Edt_380;
 T_Edit[380] = Edt_381;
 T_Edit[381] = Edt_382;
 T_Edit[382] = Edt_383;
 T_Edit[383] = Edt_384;
 T_Edit[384] = Edt_385;
 T_Edit[385] = Edt_386;
 T_Edit[386] = Edt_387;
 T_Edit[387] = Edt_388;
 T_Edit[388] = Edt_389;
 T_Edit[389] = Edt_390;
 T_Edit[390] = Edt_391;
 T_Edit[391] = Edt_392;
 T_Edit[392] = Edt_393;
 T_Edit[393] = Edt_394;
 T_Edit[394] = Edt_395;
 T_Edit[395] = Edt_396;
 T_Edit[396] = Edt_397;
 T_Edit[397] = Edt_398;
 T_Edit[398] = Edt_399;
 T_Edit[399] = Edt_400;
 T_Edit[400] = Edt_401;
 T_Edit[401] = Edt_402;
 T_Edit[402] = Edt_403;
 T_Edit[403] = Edt_404;
 T_Edit[404] = Edt_405;
 T_Edit[405] = Edt_406;
 T_Edit[406] = Edt_407;
 T_Edit[407] = Edt_408;
 T_Edit[408] = Edt_409;
 T_Edit[409] = Edt_410;
 T_Edit[410] = Edt_411;
 T_Edit[411] = Edt_412;
 T_Edit[412] = Edt_413;
 T_Edit[413] = Edt_414;
 T_Edit[414] = Edt_415;
 T_Edit[415] = Edt_416;
 T_Edit[416] = Edt_417;
 T_Edit[417] = Edt_418;
 T_Edit[418] = Edt_419;
 T_Edit[419] = Edt_420;
 T_Edit[420] = Edt_421;
 T_Edit[421] = Edt_422;
 T_Edit[422] = Edt_423;
 T_Edit[423] = Edt_424;
 T_Edit[424] = Edt_425;
 T_Edit[425] = Edt_426;
 T_Edit[426] = Edt_427;
 T_Edit[427] = Edt_428;
 T_Edit[428] = Edt_429;
 T_Edit[429] = Edt_430;
 T_Edit[430] = Edt_431;
 T_Edit[431] = Edt_432;
 T_Edit[432] = Edt_433;
 T_Edit[433] = Edt_434;
 T_Edit[434] = Edt_435;
 T_Edit[435] = Edt_436;
 T_Edit[436] = Edt_437;
 T_Edit[437] = Edt_438;
 T_Edit[438] = Edt_439;
 T_Edit[439] = Edt_440;
 T_Edit[440] = Edt_441;
 T_Edit[441] = Edt_442;
 T_Edit[442] = Edt_443;
 T_Edit[443] = Edt_444;
 T_Edit[444] = Edt_445;
 T_Edit[445] = Edt_446;
 T_Edit[446] = Edt_447;
 T_Edit[447] = Edt_448;
 T_Edit[448] = Edt_449;
 T_Edit[449] = Edt_450;
 T_Edit[450] = Edt_451;
 T_Edit[451] = Edt_452;
 T_Edit[452] = Edt_453;
 T_Edit[453] = Edt_454;
 T_Edit[454] = Edt_455;
 T_Edit[455] = Edt_456;
 T_Edit[456] = Edt_457;
 T_Edit[457] = Edt_458;
 T_Edit[458] = Edt_459;
 T_Edit[459] = Edt_460;
 T_Edit[460] = Edt_461;
 T_Edit[461] = Edt_462;
 T_Edit[462] = Edt_463;
 T_Edit[463] = Edt_464;
 T_Edit[464] = Edt_465;
 T_Edit[465] = Edt_466;
 T_Edit[466] = Edt_467;
 T_Edit[467] = Edt_468;
 T_Edit[468] = Edt_469;
 T_Edit[469] = Edt_470;
 T_Edit[470] = Edt_471;
 T_Edit[471] = Edt_472;
 T_Edit[472] = Edt_473;
 T_Edit[473] = Edt_474;
 T_Edit[474] = Edt_475;
 T_Edit[475] = Edt_476;
 T_Edit[476] = Edt_477;
 T_Edit[477] = Edt_478;
 T_Edit[478] = Edt_479;
 T_Edit[479] = Edt_480;
 T_Edit[480] = Edt_481;
 T_Edit[481] = Edt_482;
 T_Edit[482] = Edt_483;
 T_Edit[483] = Edt_484;
 T_Edit[484] = Edt_485;
 T_Edit[485] = Edt_486;
 T_Edit[486] = Edt_487;
 T_Edit[487] = Edt_488;
 T_Edit[488] = Edt_489;
 T_Edit[489] = Edt_490;
 T_Edit[490] = Edt_491;
 T_Edit[491] = Edt_492;
 T_Edit[492] = Edt_493;
 T_Edit[493] = Edt_494;
 T_Edit[494] = Edt_495;
 T_Edit[495] = Edt_496;
 T_Edit[496] = Edt_497;
 T_Edit[497] = Edt_498;
 T_Edit[498] = Edt_499;
 T_Edit[499] = Edt_500;

 T_Panel[0] = Pan_001;
 T_Panel[1] = Pan_002;
 T_Panel[2] = Pan_003;
 T_Panel[3] = Pan_004;
 T_Panel[4] = Pan_005;
 T_Panel[5] = Pan_006;
 T_Panel[6] = Pan_007;
 T_Panel[7] = Pan_008;
 T_Panel[8] = Pan_009;
 T_Panel[9] = Pan_010;
 T_Panel[10] = Pan_011;
 T_Panel[11] = Pan_012;
 T_Panel[12] = Pan_013;
 T_Panel[13] = Pan_014;
 T_Panel[14] = Pan_015;
 T_Panel[15] = Pan_016;
 T_Panel[16] = Pan_017;
 T_Panel[17] = Pan_018;
 T_Panel[18] = Pan_019;
 T_Panel[19] = Pan_020;
 T_Panel[20] = Pan_021;
 T_Panel[21] = Pan_022;
 T_Panel[22] = Pan_023;
 T_Panel[23] = Pan_024;
 T_Panel[24] = Pan_025;
 T_Panel[25] = Pan_026;
 T_Panel[26] = Pan_027;
 T_Panel[27] = Pan_028;
 T_Panel[28] = Pan_029;
 T_Panel[29] = Pan_030;
 T_Panel[30] = Pan_031;
 T_Panel[31] = Pan_032;
 T_Panel[32] = Pan_033;
 T_Panel[33] = Pan_034;
 T_Panel[34] = Pan_035;
 T_Panel[35] = Pan_036;
 T_Panel[36] = Pan_037;
 T_Panel[37] = Pan_038;
 T_Panel[38] = Pan_039;
 T_Panel[39] = Pan_040;
 T_Panel[40] = Pan_041;
 T_Panel[41] = Pan_042;
 T_Panel[42] = Pan_043;
 T_Panel[43] = Pan_044;
 T_Panel[44] = Pan_045;
 T_Panel[45] = Pan_046;
 T_Panel[46] = Pan_047;
 T_Panel[47] = Pan_048;
 T_Panel[48] = Pan_049;
 T_Panel[49] = Pan_050;
 T_Panel[50] = Pan_051;
 T_Panel[51] = Pan_052;
 T_Panel[52] = Pan_053;
 T_Panel[53] = Pan_054;
 T_Panel[54] = Pan_055;
 T_Panel[55] = Pan_056;
 T_Panel[56] = Pan_057;
 T_Panel[57] = Pan_058;
 T_Panel[58] = Pan_059;
 T_Panel[59] = Pan_060;
 T_Panel[60] = Pan_061;
 T_Panel[61] = Pan_062;
 T_Panel[62] = Pan_063;
 T_Panel[63] = Pan_064;
 T_Panel[64] = Pan_065;
 T_Panel[65] = Pan_066;
 T_Panel[66] = Pan_067;
 T_Panel[67] = Pan_068;
 T_Panel[68] = Pan_069;
 T_Panel[69] = Pan_070;
 T_Panel[70] = Pan_071;
 T_Panel[71] = Pan_072;
 T_Panel[72] = Pan_073;
 T_Panel[73] = Pan_074;
 T_Panel[74] = Pan_075;
 T_Panel[75] = Pan_076;
 T_Panel[76] = Pan_077;
 T_Panel[77] = Pan_078;
 T_Panel[78] = Pan_079;
 T_Panel[79] = Pan_080;
 T_Panel[80] = Pan_081;
 T_Panel[81] = Pan_082;
 T_Panel[82] = Pan_083;
 T_Panel[83] = Pan_084;
 T_Panel[84] = Pan_085;
 T_Panel[85] = Pan_086;
 T_Panel[86] = Pan_087;
 T_Panel[87] = Pan_088;
 T_Panel[88] = Pan_089;
 T_Panel[89] = Pan_090;
 T_Panel[90] = Pan_091;
 T_Panel[91] = Pan_092;
 T_Panel[92] = Pan_093;
 T_Panel[93] = Pan_094;
 T_Panel[94] = Pan_095;
 T_Panel[95] = Pan_096;
 T_Panel[96] = Pan_097;
 T_Panel[97] = Pan_098;
 T_Panel[98] = Pan_099;
 T_Panel[99] = Pan_100;
 T_Panel[100] = Pan_101;
 T_Panel[101] = Pan_102;
 T_Panel[102] = Pan_103;
 T_Panel[103] = Pan_104;
 T_Panel[104] = Pan_105;
 T_Panel[105] = Pan_106;
 T_Panel[106] = Pan_107;
 T_Panel[107] = Pan_108;
 T_Panel[108] = Pan_109;
 T_Panel[109] = Pan_110;
 T_Panel[110] = Pan_111;
 T_Panel[111] = Pan_112;
 T_Panel[112] = Pan_113;
 T_Panel[113] = Pan_114;
 T_Panel[114] = Pan_115;
 T_Panel[115] = Pan_116;
 T_Panel[116] = Pan_117;
 T_Panel[117] = Pan_118;
 T_Panel[118] = Pan_119;
 T_Panel[119] = Pan_120;
 T_Panel[120] = Pan_121;
 T_Panel[121] = Pan_122;
 T_Panel[122] = Pan_123;
 T_Panel[123] = Pan_124;
 T_Panel[124] = Pan_125;
 T_Panel[125] = Pan_126;
 T_Panel[126] = Pan_127;
 T_Panel[127] = Pan_128;
 T_Panel[128] = Pan_129;
 T_Panel[129] = Pan_130;
 T_Panel[130] = Pan_131;
 T_Panel[131] = Pan_132;
 T_Panel[132] = Pan_133;
 T_Panel[133] = Pan_134;
 T_Panel[134] = Pan_135;
 T_Panel[135] = Pan_136;
 T_Panel[136] = Pan_137;
 T_Panel[137] = Pan_138;
 T_Panel[138] = Pan_139;
 T_Panel[139] = Pan_140;
 T_Panel[140] = Pan_141;
 T_Panel[141] = Pan_142;
 T_Panel[142] = Pan_143;
 T_Panel[143] = Pan_144;
 T_Panel[144] = Pan_145;
 T_Panel[145] = Pan_146;
 T_Panel[146] = Pan_147;
 T_Panel[147] = Pan_148;
 T_Panel[148] = Pan_149;
 T_Panel[149] = Pan_150;
 T_Panel[150] = Pan_151;
 T_Panel[151] = Pan_152;
 T_Panel[152] = Pan_153;
 T_Panel[153] = Pan_154;
 T_Panel[154] = Pan_155;
 T_Panel[155] = Pan_156;
 T_Panel[156] = Pan_157;
 T_Panel[157] = Pan_158;
 T_Panel[158] = Pan_159;
 T_Panel[159] = Pan_160;
 T_Panel[160] = Pan_161;
 T_Panel[161] = Pan_162;
 T_Panel[162] = Pan_163;
 T_Panel[163] = Pan_164;
 T_Panel[164] = Pan_165;
 T_Panel[165] = Pan_166;
 T_Panel[166] = Pan_167;
 T_Panel[167] = Pan_168;
 T_Panel[168] = Pan_169;
 T_Panel[169] = Pan_170;
 T_Panel[170] = Pan_171;
 T_Panel[171] = Pan_172;
 T_Panel[172] = Pan_173;
 T_Panel[173] = Pan_174;
 T_Panel[174] = Pan_175;
 T_Panel[175] = Pan_176;
 T_Panel[176] = Pan_177;
 T_Panel[177] = Pan_178;
 T_Panel[178] = Pan_179;
 T_Panel[179] = Pan_180;
 T_Panel[180] = Pan_181;
 T_Panel[181] = Pan_182;
 T_Panel[182] = Pan_183;
 T_Panel[183] = Pan_184;
 T_Panel[184] = Pan_185;
 T_Panel[185] = Pan_186;
 T_Panel[186] = Pan_187;
 T_Panel[187] = Pan_188;
 T_Panel[188] = Pan_189;
 T_Panel[189] = Pan_190;
 T_Panel[190] = Pan_191;
 T_Panel[191] = Pan_192;
 T_Panel[192] = Pan_193;
 T_Panel[193] = Pan_194;
 T_Panel[194] = Pan_195;
 T_Panel[195] = Pan_196;
 T_Panel[196] = Pan_197;
 T_Panel[197] = Pan_198;
 T_Panel[198] = Pan_199;
 T_Panel[199] = Pan_200;
 T_Panel[200] = Pan_201;
 T_Panel[201] = Pan_202;
 T_Panel[202] = Pan_203;
 T_Panel[203] = Pan_204;
 T_Panel[204] = Pan_205;
 T_Panel[205] = Pan_206;
 T_Panel[206] = Pan_207;
 T_Panel[207] = Pan_208;
 T_Panel[208] = Pan_209;
 T_Panel[209] = Pan_210;
 T_Panel[210] = Pan_211;
 T_Panel[211] = Pan_212;
 T_Panel[212] = Pan_213;
 T_Panel[213] = Pan_214;
 T_Panel[214] = Pan_215;
 T_Panel[215] = Pan_216;
 T_Panel[216] = Pan_217;
 T_Panel[217] = Pan_218;
 T_Panel[218] = Pan_219;
 T_Panel[219] = Pan_220;
 T_Panel[220] = Pan_221;
 T_Panel[221] = Pan_222;
 T_Panel[222] = Pan_223;
 T_Panel[223] = Pan_224;
 T_Panel[224] = Pan_225;
 T_Panel[225] = Pan_226;
 T_Panel[226] = Pan_227;
 T_Panel[227] = Pan_228;
 T_Panel[228] = Pan_229;
 T_Panel[229] = Pan_230;
 T_Panel[230] = Pan_231;
 T_Panel[231] = Pan_232;
 T_Panel[232] = Pan_233;
 T_Panel[233] = Pan_234;
 T_Panel[234] = Pan_235;
 T_Panel[235] = Pan_236;
 T_Panel[236] = Pan_237;
 T_Panel[237] = Pan_238;
 T_Panel[238] = Pan_239;
 T_Panel[239] = Pan_240;
 T_Panel[240] = Pan_241;
 T_Panel[241] = Pan_242;
 T_Panel[242] = Pan_243;
 T_Panel[243] = Pan_244;
 T_Panel[244] = Pan_245;
 T_Panel[245] = Pan_246;
 T_Panel[246] = Pan_247;
 T_Panel[247] = Pan_248;
 T_Panel[248] = Pan_249;
 T_Panel[249] = Pan_250;
 T_Panel[250] = Pan_251;
 T_Panel[251] = Pan_252;
 T_Panel[252] = Pan_253;
 T_Panel[253] = Pan_254;
 T_Panel[254] = Pan_255;
 T_Panel[255] = Pan_256;
 T_Panel[256] = Pan_257;
 T_Panel[257] = Pan_258;
 T_Panel[258] = Pan_259;
 T_Panel[259] = Pan_260;
 T_Panel[260] = Pan_261;
 T_Panel[261] = Pan_262;
 T_Panel[262] = Pan_263;
 T_Panel[263] = Pan_264;
 T_Panel[264] = Pan_265;
 T_Panel[265] = Pan_266;
 T_Panel[266] = Pan_267;
 T_Panel[267] = Pan_268;
 T_Panel[268] = Pan_269;
 T_Panel[269] = Pan_270;
 T_Panel[270] = Pan_271;
 T_Panel[271] = Pan_272;
 T_Panel[272] = Pan_273;
 T_Panel[273] = Pan_274;
 T_Panel[274] = Pan_275;
 T_Panel[275] = Pan_276;
 T_Panel[276] = Pan_277;
 T_Panel[277] = Pan_278;
 T_Panel[278] = Pan_279;
 T_Panel[279] = Pan_280;
 T_Panel[280] = Pan_281;
 T_Panel[281] = Pan_282;
 T_Panel[282] = Pan_283;
 T_Panel[283] = Pan_284;
 T_Panel[284] = Pan_285;
 T_Panel[285] = Pan_286;
 T_Panel[286] = Pan_287;
 T_Panel[287] = Pan_288;
 T_Panel[288] = Pan_289;
 T_Panel[289] = Pan_290;
 T_Panel[290] = Pan_291;
 T_Panel[291] = Pan_292;
 T_Panel[292] = Pan_293;
 T_Panel[293] = Pan_294;
 T_Panel[294] = Pan_295;
 T_Panel[295] = Pan_296;
 T_Panel[296] = Pan_297;
 T_Panel[297] = Pan_298;
 T_Panel[298] = Pan_299;
 T_Panel[299] = Pan_300;
 T_Panel[300] = Pan_301;
 T_Panel[301] = Pan_302;
 T_Panel[302] = Pan_303;
 T_Panel[303] = Pan_304;
 T_Panel[304] = Pan_305;
 T_Panel[305] = Pan_306;
 T_Panel[306] = Pan_307;
 T_Panel[307] = Pan_308;
 T_Panel[308] = Pan_309;
 T_Panel[309] = Pan_310;
 T_Panel[310] = Pan_311;
 T_Panel[311] = Pan_312;
 T_Panel[312] = Pan_313;
 T_Panel[313] = Pan_314;
 T_Panel[314] = Pan_315;
 T_Panel[315] = Pan_316;
 T_Panel[316] = Pan_317;
 T_Panel[317] = Pan_318;
 T_Panel[318] = Pan_319;
 T_Panel[319] = Pan_320;
 T_Panel[320] = Pan_321;
 T_Panel[321] = Pan_322;
 T_Panel[322] = Pan_323;
 T_Panel[323] = Pan_324;
 T_Panel[324] = Pan_325;
 T_Panel[325] = Pan_326;
 T_Panel[326] = Pan_327;
 T_Panel[327] = Pan_328;
 T_Panel[328] = Pan_329;
 T_Panel[329] = Pan_330;
 T_Panel[330] = Pan_331;
 T_Panel[331] = Pan_332;
 T_Panel[332] = Pan_333;
 T_Panel[333] = Pan_334;
 T_Panel[334] = Pan_335;
 T_Panel[335] = Pan_336;
 T_Panel[336] = Pan_337;
 T_Panel[337] = Pan_338;
 T_Panel[338] = Pan_339;
 T_Panel[339] = Pan_340;
 T_Panel[340] = Pan_341;
 T_Panel[341] = Pan_342;
 T_Panel[342] = Pan_343;
 T_Panel[343] = Pan_344;
 T_Panel[344] = Pan_345;
 T_Panel[345] = Pan_346;
 T_Panel[346] = Pan_347;
 T_Panel[347] = Pan_348;
 T_Panel[348] = Pan_349;
 T_Panel[349] = Pan_350;
 T_Panel[350] = Pan_351;
 T_Panel[351] = Pan_352;
 T_Panel[352] = Pan_353;
 T_Panel[353] = Pan_354;
 T_Panel[354] = Pan_355;
 T_Panel[355] = Pan_356;
 T_Panel[356] = Pan_357;
 T_Panel[357] = Pan_358;
 T_Panel[358] = Pan_359;
 T_Panel[359] = Pan_360;
 T_Panel[360] = Pan_361;
 T_Panel[361] = Pan_362;
 T_Panel[362] = Pan_363;
 T_Panel[363] = Pan_364;
 T_Panel[364] = Pan_365;
 T_Panel[365] = Pan_366;
 T_Panel[366] = Pan_367;
 T_Panel[367] = Pan_368;
 T_Panel[368] = Pan_369;
 T_Panel[369] = Pan_370;
 T_Panel[370] = Pan_371;
 T_Panel[371] = Pan_372;
 T_Panel[372] = Pan_373;
 T_Panel[373] = Pan_374;
 T_Panel[374] = Pan_375;
 T_Panel[375] = Pan_376;
 T_Panel[376] = Pan_377;
 T_Panel[377] = Pan_378;
 T_Panel[378] = Pan_379;
 T_Panel[379] = Pan_380;
 T_Panel[380] = Pan_381;
 T_Panel[381] = Pan_382;
 T_Panel[382] = Pan_383;
 T_Panel[383] = Pan_384;
 T_Panel[384] = Pan_385;
 T_Panel[385] = Pan_386;
 T_Panel[386] = Pan_387;
 T_Panel[387] = Pan_388;
 T_Panel[388] = Pan_389;
 T_Panel[389] = Pan_390;
 T_Panel[390] = Pan_391;
 T_Panel[391] = Pan_392;
 T_Panel[392] = Pan_393;
 T_Panel[393] = Pan_394;
 T_Panel[394] = Pan_395;
 T_Panel[395] = Pan_396;
 T_Panel[396] = Pan_397;
 T_Panel[397] = Pan_398;
 T_Panel[398] = Pan_399;
 T_Panel[399] = Pan_400;
 T_Panel[400] = Pan_401;
 T_Panel[401] = Pan_402;
 T_Panel[402] = Pan_403;
 T_Panel[403] = Pan_404;
 T_Panel[404] = Pan_405;
 T_Panel[405] = Pan_406;
 T_Panel[406] = Pan_407;
 T_Panel[407] = Pan_408;
 T_Panel[408] = Pan_409;
 T_Panel[409] = Pan_410;
 T_Panel[410] = Pan_411;
 T_Panel[411] = Pan_412;
 T_Panel[412] = Pan_413;
 T_Panel[413] = Pan_414;
 T_Panel[414] = Pan_415;
 T_Panel[415] = Pan_416;
 T_Panel[416] = Pan_417;
 T_Panel[417] = Pan_418;
 T_Panel[418] = Pan_419;
 T_Panel[419] = Pan_420;
 T_Panel[420] = Pan_421;
 T_Panel[421] = Pan_422;
 T_Panel[422] = Pan_423;
 T_Panel[423] = Pan_424;
 T_Panel[424] = Pan_425;
 T_Panel[425] = Pan_426;
 T_Panel[426] = Pan_427;
 T_Panel[427] = Pan_428;
 T_Panel[428] = Pan_429;
 T_Panel[429] = Pan_430;
 T_Panel[430] = Pan_431;
 T_Panel[431] = Pan_432;
 T_Panel[432] = Pan_433;
 T_Panel[433] = Pan_434;
 T_Panel[434] = Pan_435;
 T_Panel[435] = Pan_436;
 T_Panel[436] = Pan_437;
 T_Panel[437] = Pan_438;
 T_Panel[438] = Pan_439;
 T_Panel[439] = Pan_440;
 T_Panel[440] = Pan_441;
 T_Panel[441] = Pan_442;
 T_Panel[442] = Pan_443;
 T_Panel[443] = Pan_444;
 T_Panel[444] = Pan_445;
 T_Panel[445] = Pan_446;
 T_Panel[446] = Pan_447;
 T_Panel[447] = Pan_448;
 T_Panel[448] = Pan_449;
 T_Panel[449] = Pan_450;
 T_Panel[450] = Pan_451;
 T_Panel[451] = Pan_452;
 T_Panel[452] = Pan_453;
 T_Panel[453] = Pan_454;
 T_Panel[454] = Pan_455;
 T_Panel[455] = Pan_456;
 T_Panel[456] = Pan_457;
 T_Panel[457] = Pan_458;
 T_Panel[458] = Pan_459;
 T_Panel[459] = Pan_460;
 T_Panel[460] = Pan_461;
 T_Panel[461] = Pan_462;
 T_Panel[462] = Pan_463;
 T_Panel[463] = Pan_464;
 T_Panel[464] = Pan_465;
 T_Panel[465] = Pan_466;
 T_Panel[466] = Pan_467;
 T_Panel[467] = Pan_468;
 T_Panel[468] = Pan_469;
 T_Panel[469] = Pan_470;
 T_Panel[470] = Pan_471;
 T_Panel[471] = Pan_472;
 T_Panel[472] = Pan_473;
 T_Panel[473] = Pan_474;
 T_Panel[474] = Pan_475;
 T_Panel[475] = Pan_476;
 T_Panel[476] = Pan_477;
 T_Panel[477] = Pan_478;
 T_Panel[478] = Pan_479;
 T_Panel[479] = Pan_480;
 T_Panel[480] = Pan_481;
 T_Panel[481] = Pan_482;
 T_Panel[482] = Pan_483;
 T_Panel[483] = Pan_484;
 T_Panel[484] = Pan_485;
 T_Panel[485] = Pan_486;
 T_Panel[486] = Pan_487;
 T_Panel[487] = Pan_488;
 T_Panel[488] = Pan_489;
 T_Panel[489] = Pan_490;
 T_Panel[490] = Pan_491;
 T_Panel[491] = Pan_492;
 T_Panel[492] = Pan_493;
 T_Panel[493] = Pan_494;
 T_Panel[494] = Pan_495;
 T_Panel[495] = Pan_496;
 T_Panel[496] = Pan_497;
 T_Panel[497] = Pan_498;
 T_Panel[498] = Pan_499;
 T_Panel[499] = Pan_500;

 S_Panel[0][0] = Sta_01A;
 S_Panel[1][0] = Sta_01B;
 S_Panel[2][0] = Sta_01C;
 S_Panel[0][1] = Sta_02A;
 S_Panel[1][1] = Sta_02B;
 S_Panel[2][1] = Sta_02C;
 S_Panel[0][2] = Sta_03A;
 S_Panel[1][2] = Sta_03B;
 S_Panel[2][2] = Sta_03C;
 S_Panel[0][3] = Sta_04A;
 S_Panel[1][3] = Sta_04B;
 S_Panel[2][3] = Sta_04C;
 S_Panel[0][4] = Sta_05A;
 S_Panel[1][4] = Sta_05B;
 S_Panel[2][4] = Sta_05C;
 S_Panel[0][5] = Sta_06A;
 S_Panel[1][5] = Sta_06B;
 S_Panel[2][5] = Sta_06C;
 S_Panel[0][6] = Sta_07A;
 S_Panel[1][6] = Sta_07B;
 S_Panel[2][6] = Sta_07C;
 S_Panel[0][7] = Sta_08A;
 S_Panel[1][7] = Sta_08B;
 S_Panel[2][7] = Sta_08C;
 S_Panel[0][8] = Sta_09A;
 S_Panel[1][8] = Sta_09B;
 S_Panel[2][8] = Sta_09C;
 S_Panel[0][9] = Sta_10A;
 S_Panel[1][9] = Sta_10B;
 S_Panel[2][9] = Sta_10C;
 S_Panel[0][10] = Sta_11A;
 S_Panel[1][10] = Sta_11B;
 S_Panel[2][10] = Sta_11C;
 S_Panel[0][11] = Sta_12A;
 S_Panel[1][11] = Sta_12B;
 S_Panel[2][11] = Sta_12C;
 S_Panel[0][12] = Sta_13A;
 S_Panel[1][12] = Sta_13B;
 S_Panel[2][12] = Sta_13C;
 S_Panel[0][13] = Sta_14A;
 S_Panel[1][13] = Sta_14B;
 S_Panel[2][13] = Sta_14C;
 S_Panel[0][14] = Sta_15A;
 S_Panel[1][14] = Sta_15B;
 S_Panel[2][14] = Sta_15C;
 S_Panel[0][15] = Sta_16A;
 S_Panel[1][15] = Sta_16B;
 S_Panel[2][15] = Sta_16C;
 S_Panel[0][16] = Sta_17A;
 S_Panel[1][16] = Sta_17B;
 S_Panel[2][16] = Sta_17C;
 S_Panel[0][17] = Sta_18A;
 S_Panel[1][17] = Sta_18B;
 S_Panel[2][17] = Sta_18C;
 S_Panel[0][18] = Sta_19A;
 S_Panel[1][18] = Sta_19B;
 S_Panel[2][18] = Sta_19C;
 S_Panel[0][19] = Sta_20A;
 S_Panel[1][19] = Sta_20B;
 S_Panel[2][19] = Sta_20C;

}
//---------------------------------------------------------------------------

// 画面初期化
// Opt ： 0： Call from Form1
//        1： Call from Form4 (nのchange)
void __fastcall TForm3::FormScreenInit(int Opt)
{
 int i, ret;
 AnsiString YMD;
 int OldSokute_Su;

 // InputModeを決める
 if (Opt == 0)
    InputMode = 1;

 OldSokute_Su = Cur_Kdb1.SOKUTE_SU;

 ScreenInitFlag = 1;

 // 表示桁数初期化
 switch (Cur_Kdb1.KENSA_KMK) {
 case 0:
 case 1:
 case 2:
 case 5:
 case 10:
    if (Cur_Kdb1.SOKUTE_KET == 3) {
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 3;                // Defalut 小数点3桁
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0.000;
           T_Edit[i]->Color = clWindow;
       }
       if (Cur_Kdb1.KENSA_KMK == 5) {
          Edt_Sub51->FPos = 3;
          Edt_Sub52->FPos = 3;
          Edt_Sub53->FPos = 3;
          Edt_Sub54->FPos = 3;
       }
       Button1->Caption = "1/1000";            // Default 小数点3桁
    } else {
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 2;                // Defalut 小数点2桁
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0.00;
             T_Edit[i]->Color = clWindow;
       }
       if (Cur_Kdb1.KENSA_KMK == 5) {
          Edt_Sub51->FPos = 2;
          Edt_Sub52->FPos = 2;
          Edt_Sub53->FPos = 2;
          Edt_Sub54->FPos = 2;
       }
       Button1->Caption = "1/100";            // Default 小数点3桁
    }
    break;
 case 6:
    if (Cur_Kdb1.JYOKEN1 <= 2) {  // HSC
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 0;                // 整数
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0;
           T_Edit[i]->Color = clWindow;
       }
    } else {  // HSD
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 1;                // 小数点１桁
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0.0;
           T_Edit[i]->Color = clWindow;
       }
    }
    break;
 case 3:
 case 4:
 case 11:
     for (i = 0; i < Nums; i++) {
        T_Edit[i]->FPos = 1;                // Defalut 小数点2桁
        if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
           T_Edit[i]->Text = 0.0;
        T_Edit[i]->Color = clWindow;
    }
    if (Cur_Kdb1.KENSA_KMK == 3) {
       Edt_Sub31->FPos = 1;
       Edt_Sub32->FPos = 1;
    }
    /*//2002/12/28 E.Takase
    //if (Cur_Kdb1.KENSA_KMK == 8) {
    if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {
       Edt_Sub81->FPos = 3;
       Edt_Sub82->FPos = 3;
       Edt_Sub83->FPos = 1;
    } */
    break;

 //2003.02.08 E.Takase
 case 8:
 case 12: //2002/12/28 E.Takase
    if ( Cur_Kdb1.KEIJKBN == 3) { //コンミ
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 2;                // Defalut 小数点2桁
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0.00;
           T_Edit[i]->Color = clWindow;
       }
          /*
          if (Cur_Kdb1.KENSA_KMK == 3) {
             Edt_Sub31->FPos = 1;
             Edt_Sub32->FPos = 1;
          }
          */
       //}
       //2002/12/28 E.Takase
       //if (Cur_Kdb1.KENSA_KMK == 8) {
       //if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {
       Edt_Sub81->FPos = 3;
       Edt_Sub82->FPos = 3;
       Edt_Sub83->FPos = 2;
       //}
    } else {
       for (i = 0; i < Nums; i++) {
           T_Edit[i]->FPos = 1;                // Defalut 小数点2桁
           if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
              T_Edit[i]->Text = 0.0;
           T_Edit[i]->Color = clWindow;
       }
          /*
          if (Cur_Kdb1.KENSA_KMK == 3) {
             Edt_Sub31->FPos = 1;
             Edt_Sub32->FPos = 1;
          }
          */
       //}
       //2002/12/28 E.Takase
       //if (Cur_Kdb1.KENSA_KMK == 8) {
       //if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {
       Edt_Sub81->FPos = 3;
       Edt_Sub82->FPos = 3;
       Edt_Sub83->FPos = 1;
    }
    break;
 case 7:
    for (i = 0; i < Nums; i++) {
        if (Cur_Kdb1.KEIJKBN == 3) {
            T_Edit[i]->FPos = 2;                // コンミ 小数点2
        } else {
            T_Edit[i]->FPos = 0;                // Defalut 小数点なし

        }
        if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
           T_Edit[i]->Text = 0;

        T_Edit[i]->Color = clWindow;

    }
    Edt_Sub71->FPos = 3;
    Edt_Sub72->FPos = 3;
    Edt_Sub73->FPos = 2;
    Edt_Sub74->FPos = 2;
    Edt_Sub75->FPos = 2;
    Edt_Sub76->FPos = 2;
    break;

 case 9:
    for (i = 0; i < Nums; i++) {
        T_Edit[i]->FPos = 0;                // Defalut 小数点なし
        if (Opt == 0 || (Opt == 1 && i >= Cur_Kdb1.SOKUTE_SU))
           T_Edit[i]->Text = 0;

        T_Edit[i]->Color = clWindow;

    }
    break;
 }

 Cur_Kdb1.SOKUTE_SU = OldSokute_Su;

 if (Opt == 0) {
    switch (Cur_Kdb1.KENSA_KMK) {
    case 0:                     // 線長さ
      InputMode = 1;
      CurrentChannel = 1;
      if (ConnectFlag && (KikiType == 1 || KikiType == 2))
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 1:                     // 幅
      InputMode = 1;
      CurrentChannel = 2;
      if (ConnectFlag && (KikiType == 1 || KikiType == 2))
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 2:                     // その他（マイクロメータ、ノギス）
      InputMode = 1;
      CurrentChannel = 2;
      if (ConnectFlag && (KikiType == 1 || KikiType == 2))
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 3:                     // 取付抵抗
      InputMode = 3;
      CurrentChannel = 8;
      if (ConnectFlag && (KikiType == 3 || KikiType == 4))
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 4:                     // 引張り
      InputMode = 2;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
      //CurrentChannel = 7;
      CurrentChannel = 10;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑

      //2009.03.13 MTS E.Takase [001]  ↓
      //材料試験機（単独使用）は機器タイプを5とする
      //if (ConnectFlag && (KikiType == 3 || KikiType == 4))
      if (ConnectFlag && (KikiType == 5))
      //2009.03.13 MTS E.Takase [001]  ↑
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 5:                     // 母体
      InputMode = 4;
      CurrentChannel = 2;
      OldChannel = 2;
      if (ConnectFlag && (KikiType == 1 || KikiType == 2))
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 6:                     // 硬度
      InputMode = 0;
      ShareFlag = 0;
      break;
    case 7:                     // 固有抵抗
      InputMode = 5;
      ShareFlag = 0;
      if (ConnectFlag) {
         if (KikiType == 1 || KikiType == 2) {
            ShareFlag = 1;
            CurrentChannel = 2;
            OldChannel = 2;
         }
         if (KikiType == 3 || KikiType == 4) {
            ShareFlag = 1;
            CurrentChannel = 9;
            OldChannel = 9;
         }
      }
      break;
    case 8:                     // 曲げ強さ
    case 12:                    // 曲げ強さ（現物）
      InputMode = 6;
      ShareFlag = 0;
      if (ConnectFlag) {
         if (KikiType == 1 || KikiType == 2) {
            ShareFlag = 1;
            CurrentChannel = 2;
            OldChannel = 2;
         }
         //2009.03.13 MTS E.Takase [001]  ↓
         //材料試験機（単独使用）は機器タイプを5とする
         //if (KikiType == 3 || KikiType == 4) {
         if (KikiType == 5) {
         //2009.03.13 MTS E.Takase [001]  ↑
            ShareFlag = 1;
            //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
            //CurrentChannel = 7;
            //OldChannel = 7;
            CurrentChannel = 10;
            OldChannel = 10;
            //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
         }
      }
      break;
    case 9:                     // 座屈
      InputMode = 2;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
      //CurrentChannel = 7;
      CurrentChannel = 10;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑

      //2009.03.13 MTS E.Takase [001]  ↓
      //材料試験機（単独使用）は機器タイプを5とする
      //if (ConnectFlag && (KikiType == 3 || KikiType == 4))
      if (ConnectFlag && (KikiType == 5))
      //2009.03.13 MTS E.Takase [001]  ↑
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    case 10:                    // その他  （Keyborad)
      InputMode = 0;
      ShareFlag = 0;
      break;
    case 11:                    // その他   (材料機）
      InputMode = 2;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
      //CurrentChannel = 7;
      CurrentChannel = 10;
      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
      //2009.03.13 MTS E.Takase [001]  ↓
      //材料試験機（単独使用）は機器タイプを5とする
      //if (ConnectFlag && (KikiType == 3 || KikiType == 4))
      if (ConnectFlag && (KikiType == 5))
      //2009.03.13 MTS E.Takase [001]  ↑
         ShareFlag = 1;
      else
         ShareFlag = 0;
      break;
    }

    // 計測値表示（数字と色）
    // 通常は1番フィールドをFocus
    if (Cur_Kdb1.HIST_SOKUT > 0)
       CurField = 1;
    else
       CurField = 0;

    SubField = 0;

    if (Cur_Kdb1.KENSA_KMK == 5) {
       // 例外処理：母体比重：円柱？
       if (Cur_Kdb1.KEIJKBN == 2) // 母体比重 円柱
          SubField = 1;
       else
          SubField = 0;
    }


    if (Cur_Kdb1.KENSA_KMK == 7) {
       // 例外処理：固有抵抗率：円柱？
       if (Cur_Kdb1.KEIJKBN == 2) // 固有抵抗率 円柱
          SubField = 1;
       else
          SubField = 0;
    }

    if (Cur_Kdb1.KENSA_KMK == 8) {
       // 例外処理：抗折力：円柱？
       if (Cur_Kdb1.KEIJKBN == 2) // 抗折力 円柱
          SubField = 1;
       else
          SubField = 0;
    }

    //2002/12/28 E.Takase
    if (Cur_Kdb1.KENSA_KMK == 12) {
       // 例外処理：曲げ強さ（現物）：円柱？
       if (Cur_Kdb1.KEIJKBN == 2) // 曲げ強さ（現物） 円柱
          SubField = 1;
       else
          SubField = 0;
    }
 }

 // 収録データ数チェック
 if (Cur_Kdb1.HIST_SOKUT > Nums)
    Cur_Kdb1.HIST_SOKUT = Nums;

 for (i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
     if (Opt == 0 && T_Edit[i]->Value != M_Kdb2[i].SOKUTEI_CH ||
        i >= Cur_Kdb1.SOKUTE_SU)
          T_Edit[i]->Text = M_Kdb2[i].SOKUTEI_CH;
     T_Edit[i]->Font->Color = clWindowText;
 }

 // 画面タイトル表示
 // Edt_YMD->Text = FormatDateTime("YYYY/MM/DD", Cur_Kda1.KENSA_YMD);
 YMD = Cur_Kdb1.KENSA_YMD;
 YMD.Insert("/", 5);
 YMD.Insert("/", 8);
 Pan_YMD->Caption = YMD;

 Lbl_NO->Caption = Cur_Kdb1.No;
 Lbl_DTKSHIN->Caption = Cur_Kdb1.DTKSHIN ;
 Lbl_LOTNO->Caption = Cur_Kdb1.LOTNO ;
 Lbl_ZISNAM->Caption = Cur_Kdb1.ZISNAM ;
 Lbl_KOUMOKU_J->Caption = Cur_Kdb1.KOUMOKU_J;
 Lbl_KOUMOKU_E->Caption = Cur_Kdb1.KOUMOKU_E;
 Lbl_HIST_SOKUT->Caption = Cur_Kdb1.HIST_SOKUT;
 switch (Cur_Kdb1.HIST_KIKAK) {
 case 1:
      Lbl_HIST_KIKAK->Caption = "両側";
      break;
 case 2:
      Lbl_HIST_KIKAK->Caption = "下限";
      break;
 case 3:
      Lbl_HIST_KIKAK->Caption = "上限";
      break;
 }

 // 下限規格
 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
    if (Cur_Kdb1.KENSA_KMK == 7) // 抵抗率  2000.3.11
       if (Cur_Kdb1.KEIJKBN == 3 )  //コンミ 抵抗率 2003.02.08
          Lbl_HIST_MIN->Caption = FormatFloat("#0.00", Cur_Kdb1.HIST_MIN);
       else
          Lbl_HIST_MIN->Caption = FormatFloat("#0", Cur_Kdb1.HIST_MIN);
    else
       Lbl_HIST_MIN->Caption = FormatFloat("#0.000", Cur_Kdb1.HIST_MIN);
 } else
    Lbl_HIST_MIN->Caption = " ";

 // 上限規格
 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
    if (Cur_Kdb1.KENSA_KMK == 7) // 抵抗率  2000.3.11
       if (Cur_Kdb1.KEIJKBN == 3 )  //コンミ 抵抗率 2003.02.08
          Lbl_HIST_MAX->Caption = FormatFloat("#0.00", Cur_Kdb1.HIST_MAX);
       else
          Lbl_HIST_MAX->Caption = FormatFloat("#0", Cur_Kdb1.HIST_MAX);
    else
       Lbl_HIST_MAX->Caption = FormatFloat("#0.000", Cur_Kdb1.HIST_MAX);
 } else
    Lbl_HIST_MAX->Caption = " ";

 Lbl_HIST_MIN1->Caption = Lbl_HIST_MIN->Caption;
 Lbl_HIST_MAX1->Caption = Lbl_HIST_MAX->Caption;

 Lbl_Tani->Caption = Cur_Kdb1.TANI;

 if (Cur_Kdb1.HIST_SOKUT > Cur_Kdb1.SOKUTE_SU)
    Lbl_STATUS->Caption = "未";
 else
    Lbl_STATUS->Caption = "済";

 // 統計とグラフ表示
 Toukei();

 // 測定数によって、入力Field設定
 for (i = 0; i < Nums; i++) {
     if (i < Cur_Kdb1.HIST_SOKUT) {
       T_Edit[i]->Enabled = true;
       T_Edit[i]->Visible = true;
       T_Panel[i]->Visible = true;
     } else {
       T_Edit[i]->Enabled = false;
       T_Edit[i]->Visible = false;
       T_Panel[i]->Visible = false;
     }
 }

 if (Opt == 0) {
    // サブ画面Field設定
    Edt_Sub31->Enabled = false;
    Edt_Sub32->Enabled = false;
    Edt_Sub51->Enabled = false;
    Edt_Sub52->Enabled = false;
    Edt_Sub53->Enabled = false;
    Edt_Sub54->Enabled = false;
    Edt_Sub71->Enabled = false;
    Edt_Sub72->Enabled = false;
    Edt_Sub73->Enabled = false;
    Edt_Sub74->Enabled = false;
    Edt_Sub75->Enabled = false;
    Edt_Sub76->Enabled = false;
    Edt_Sub81->Enabled = false;
    Edt_Sub82->Enabled = false;
    Edt_Sub83->Enabled = false;
    Radio_Sub51->Enabled = false;
    Radio_Sub52->Enabled = false;
    Radio_Sub53->Enabled = false;
    Radio_Sub54->Enabled = false;
    Radio_Sub71->Enabled = false;
    Radio_Sub72->Enabled = false;
    Radio_Sub73->Enabled = false;
    //Radio_Sub74->Enabled = false;
    Radio_Sub81->Enabled = false;
    Radio_Sub82->Enabled = false;
    Radio_Sub83->Enabled = false;
    Button4->Enabled = false;
    Button8->Enabled = false;
    Button9->Enabled = false;
    Button9->Caption = "";
    F4Flag = 0;
    F8Flag = 0;
    F9Flag = 0;

    switch (InputMode) {
    case 1:
      if (ShareFlag) {
         Button8->Enabled = true;
         F8Flag = 1;
      }
      break;
    case 3:
      Edt_Sub31->Enabled = true;
      Edt_Sub32->Enabled = true;
      break;
    case 4:
      Edt_Sub51->Enabled = false;
      Edt_Sub52->Enabled = false;
      Edt_Sub53->Enabled = false;
      Edt_Sub54->Enabled = false;
      Radio_Sub51->Enabled = false;
      Radio_Sub52->Enabled = true;
      Radio_Sub53->Enabled = true;
      Radio_Sub54->Enabled = true;
      Button4->Enabled = true;
      F4Flag = 1;
      //2002/11/14 コンミ対応 E.Takase
      //if (Cur_Kdb1.KEIJKBN <= 1) {   // 直方体
      //   Edt_Sub51->Enabled = true;
      //   Radio_Sub51->Enabled = true;
      //   SubField = 0;
      //   //Radio_Sub51->Checked = true;
      //} else { // 円柱
      //   Radio_Sub51->Checked = false;
      //   Edt_Sub52->Enabled = true;
      //   SubField = 1;
      //   //Radio_Sub52->Checked = true;
      //}
      switch (Cur_Kdb1.KEIJKBN) {
        case 1: //直方体
         Edt_Sub51->Enabled = true;
         Radio_Sub51->Enabled = true;
         SubField = 0;
         //Radio_Sub51->Checked = true;
         break;

        case 2: //円柱
         Radio_Sub51->Checked = false;
         Edt_Sub52->Enabled = true;
         SubField = 1;
         //Radio_Sub52->Checked = true;
         break;

        case 3: //コンミ
         Edt_Sub51->Enabled = true;
         Radio_Sub51->Enabled = true;
         SubField = 0;
         //Radio_Sub51->Checked = true;
         break;
      }


      if (ShareFlag) {
         Button8->Enabled = true;
         F8Flag = 1;
      }
      break;
    case 5:
      Edt_Sub71->Enabled = false;
      Edt_Sub72->Enabled = false;
      Edt_Sub73->Enabled = false;
      Edt_Sub74->Enabled = false;
      Edt_Sub75->Enabled = false;
      Edt_Sub76->Enabled = false;
      Radio_Sub71->Enabled = false;
      Radio_Sub72->Enabled = true;
      Radio_Sub73->Enabled = true;

      //Edt_Sub71->Enabled = true;
      //Edt_Sub72->Enabled = false;
      //Radio_Sub71->Enabled = true;
      //Radio_Sub72->Enabled = true;
      //Edt_Sub73->Enabled = false;
      //Edt_Sub74->Enabled = false;
      //Edt_Sub75->Enabled = false;
      //Edt_Sub76->Enabled = false;

      if (KikiType == 1 || KikiType == 2) {
         if (ShareFlag) {
            Button8->Enabled = true;
            F8Flag = 1;
         }
      }
      SubField = 0;
      SubField1 = 0;

      //2002/11/14 コンミ対応 E.Takase
      //if (Cur_Kdb1.KEIJKBN <= 1) {   // 直方体
      //   Edt_Sub71->Enabled = true;
      //   Radio_Sub71->Enabled = true;
      //   SubField = 0;
      //   //Radio_Sub71->Checked = true;
      //} else { // 円柱
      //   SubField = 1;
      //   Edt_Sub71->Enabled = false;
      //   Edt_Sub72->Enabled = true;
      //   Radio_Sub72->Enabled = true;
      //   //Radio_Sub72->Checked = true;
      //}
      switch (Cur_Kdb1.KEIJKBN) {
        case 1: //直方体
         Edt_Sub71->Enabled = true;
         Radio_Sub71->Enabled = true;
         SubField = 0;
         //Radio_Sub71->Checked = true;
         break;

        case 2: //円柱
         SubField = 1;
         Edt_Sub71->Enabled = false;
         Edt_Sub72->Enabled = true;
         Radio_Sub72->Enabled = true;
         //Radio_Sub72->Checked = true;
         break;

        case 3: //コンミ
         SubField = 0;
         Edt_Sub71->Enabled = true;
         Edt_Sub72->Enabled = false;
         Radio_Sub71->Enabled = true;
         Radio_Sub72->Enabled = false;
         //Radio_Sub72->Checked = true;
         break;
      }

      Button4->Enabled = true;
      F4Flag = 1;
      Button9->Enabled = true;
      Button9->Caption = "プローブ";
      F9Flag = 1;
      break;
    case 6:
      Edt_Sub81->Enabled = false;
      Edt_Sub82->Enabled = false;
      Edt_Sub83->Enabled = false;
      Radio_Sub81->Enabled = false;
      Radio_Sub82->Enabled = true;
      Radio_Sub83->Enabled = true;
      Button4->Enabled = true;
      F4Flag = 1;

      if (KikiType == 1 || KikiType == 2) {
         if (ShareFlag) {
            Button8->Enabled = true;
            F8Flag = 1;
         }
      }

      //2002/11/14 コンミ対応 E.Takase
      //if (Cur_Kdb1.KEIJKBN <= 1) {   // 直方体
      //   Edt_Sub81->Enabled = true;
      //   Radio_Sub81->Enabled = true;
      //   SubField = 0;
      //   //Radio_Sub81->Checked = true;
      //} else { // 円柱
      //   SubField = 1;
      //   Edt_Sub81->Enabled = false;
      //   Edt_Sub82->Enabled = true;
      //   Radio_Sub82->Enabled = true;
      //   //Radio_Sub82->Checked = true;
      //}
      switch (Cur_Kdb1.KEIJKBN) {
        case 1: //直方体
         Edt_Sub81->Enabled = true;
         Radio_Sub81->Enabled = true;
         SubField = 0;
         //Radio_Sub81->Checked = true;
         break;

        case 2: //円柱
         SubField = 1;
         Edt_Sub81->Enabled = false;
         Edt_Sub82->Enabled = true;
         Radio_Sub82->Enabled = true;
         //Radio_Sub82->Checked = true;
         break;

        case 3: //コンミ
         Edt_Sub81->Enabled = true;
         Radio_Sub81->Enabled = true;
         Edt_Sub82->Enabled = false;
         Radio_Sub82->Enabled = false;
         SubField = 0;
         //Radio_Sub81->Checked = true;
         break;
      }

      Button9->Enabled = true;
      Button9->Caption = "スパン";
      F9Flag = 1;
      break;
    }
 }

 if (Opt == 0)
    F10Flag = 1;
    
 //測定したデータに色付け
 for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++){
     FieldColor(i, 0, 1);
 }

 if (Opt == 0) {
    // 入力領域のサイズ調整
    ScrollBox1->Left = 9;
    ScrollBox1->Top = 192;
    Pan_Sub4->Top = 208;
    Pan_Sub3->Top = 208;
    Pan_Sub5->Top = 208;
    Pan_Sub7->Top = 208;
    Pan_Sub8->Top = 208;
    switch (InputMode) {
    case 0:
    case 1:
      ScrollBox1->Height = 449;
      break;
    case 2:
      ScrollBox1->Height = 370;
      Pan_Sub4->Top = 568;
      Pan_Sub43->Caption = Cur_Kdb1.JYOKEN1;
      break;
    case 3:
      SubField = 0;
      ScrollBox1->Height = 350;
      Pan_Sub3->Top = 548;
      //Pan_Sub34->Caption = Cur_Kdb1.JYOKEN1;
      Pan_Sub34->Caption = FormatFloat("#0", Cur_Kdb1.JYOKEN1);
      Pan_Sub35->Caption = Cur_Kdb1.JYOKEN2;
      break;
    case 4:
      ScrollBox1->Height = 290;
      Pan_Sub5->Top = 490;
      break;
    case 5:
      ScrollBox1->Height = 260;
      Pan_Sub7->Top = 460;
      //Pan_Sub71->Caption = Cur_Kdb1.JYOKEN1;
      Pan_Sub71->Caption = FormatFloat("#0", Cur_Kdb1.JYOKEN1);      
      Pan_Sub72->Caption = Cur_Kdb1.JYOKEN2;
      if (Cur_Kdb1.SOKUTE_SU > 0)
         Pan_Sub73->Caption = M_Kdb2[0].SOKUTEI_MEI7;
      else
         Pan_Sub73->Caption = Cur_Kdb1.JYOKEN2;
      break;
    case 6:
      ScrollBox1->Height = 290;
      Pan_Sub8->Top = 490;
      Pan_Sub81->Caption = Cur_Kdb1.JYOKEN1;
      if (Cur_Kdb1.SOKUTE_SU > 0)
         Pan_Sub82->Caption = M_Kdb2[0].SOKUTEI_MEI4;
      else
         Pan_Sub82->Caption = Cur_Kdb1.JYOKEN1;
      break;
    }

    CurrentChangeFlag = 0;
    //2002/11/21 E.Takase
    if ( Form11->DataCopyFlag == 0 ) {
        AllChangeFlag = 0;
    } else {
        AllChangeFlag = 1;
    }
 }

 // F1無効
 //2002/12/28 E.Takase
 //if (Cur_Kdb1.KENSA_KMK == 6 || Cur_Kdb1.KENSA_KMK == 7 ||
 //   Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 8 ||
 //   Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 11 ||
 //   Cur_Kdb1.KENSA_KMK == 3)
 //   Button1->Enabled = false;
 if (Cur_Kdb1.KENSA_KMK == 6 || Cur_Kdb1.KENSA_KMK == 7 ||
     Cur_Kdb1.KENSA_KMK == 9 || Cur_Kdb1.KENSA_KMK == 8 ||
     Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 11 ||
     Cur_Kdb1.KENSA_KMK == 3 || Cur_Kdb1.KENSA_KMK == 12)
    Button1->Enabled = false;
 else
    Button1->Enabled = true;

 // シェアメモリ作成
 if (Opt == 0) {
    // Save KDB1
    SaveKDB1();

    if (ShareFlag) {
       char tempo[64];
       int AgainNo = 0;

Again1:
       ret = SharedMemory_Open(Handle, "SHARE_TRIS1", 1);
       ret = SharedMemory_Open(Handle, "SHARE_TRIS2", 2);

       if (ret < 0) {
          if (ShellExeFlag == 1) {
             Sleep(500);
             AgainNo++;
             if (AgainNo < 10)
                goto Again1;
          }
          // ステータスメッセージ
          // StatBarClear( " SharedMemory オープンエラー。  ");
          ShareFlag = 0;
          Button8->Enabled = false;
          F8Flag = 0;
          MsgFlag = 1;
          ScreenInitFlag = 0;
          return;
       }

       //RS232C接続フラグを１に設定
       iShareFlag = 1;

       sprintf(tempo, "CONNECT %d", CurrentChannel);
       SharedMemory_Write(1, 0, tempo, strlen(tempo));
    } else {
       if (Opt == 0 && Cur_Kdb1.KENSA_KMK != 10)
          MsgFlag = 1;
       ShareFlag = 0;
       Button8->Enabled = false;
       F8Flag = 0;
    }
 } else { // Opt == 1
      if (iShareFlag > 0) {
         if ((Cur_Kdb1.KENSA_KMK == 5  &&  SubField == 3) ||
             (Cur_Kdb1.KENSA_KMK == 7  && (SubField == 2 || SubField == 3)) ||
             (Cur_Kdb1.KENSA_KMK == 8  &&  SubField == 2) || // 母体比重：重量
             (Cur_Kdb1.KENSA_KMK == 12 &&  SubField == 2)) { // 母体比重：重量
                                                             // 固有抵抗率：mV/A
                                                             // 抗折力：負荷
                                                             // 曲げ強さ（現物）：負荷
            Button8->Enabled = false;
            F8Flag = 0;
         } else {
            Button8->Enabled = true;
            F8Flag = 1;
         }
      }
 }

 ScreenInitFlag = 0;
}

// 測定値と測定規格を比較し、Fieldのいろを付ける
// initFlag 追加 2002/12/03 E.Takase
// initFlag=0：Editから値を取得し電流チェック
// initFlag=1：変数から値を取得し電流チェック
void __fastcall TForm3::FieldColor(int i, int Sound, int initFlag)
{
 int ErrorFlag = 0;
 EndErrorFlag = 0;

 // 規格判断
 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
    if (M_Kdb2[i].SOKUTEI_CH < Cur_Kdb1.HIST_MIN)
       ErrorFlag = 1;
 }

 //2008.05.21 E.Takase 規格有効判断は以上未満
 //if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
    if (M_Kdb2[i].SOKUTEI_CH+COM_DIFF >= Cur_Kdb1.HIST_MAX)
       ErrorFlag = 1;
 }


 if (Cur_Kdb1.KENSA_KMK == 3) {
    // initFlag=0：Editから値を取得し電流チェック
    if ( initFlag == 0 ) {
        // リード線取り付けの例外処理：電流チェック( 10%)
        if (Edt_Sub32->Value > COM_DIFF && (Edt_Sub32->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
            Edt_Sub32->Value < Cur_Kdb1.JYOKEN1 * 0.9))
        ErrorFlag = 1;
    // initFlag=1：変数から値を取得し電流チェック
    } else {
        // リード線取り付けの例外処理：電流チェック( 10%)
        if (M_Kdb2[i].SOKUTEI_MEI2 > COM_DIFF && (M_Kdb2[i].SOKUTEI_MEI2 > Cur_Kdb1.JYOKEN1 * 1.1 ||
            M_Kdb2[i].SOKUTEI_MEI2 < Cur_Kdb1.JYOKEN1 * 0.9))
        ErrorFlag = 1;

    }
 }

 if (Cur_Kdb1.KENSA_KMK == 7) {
    // initFlag=0：Editから値を取得し電流チェック
    if ( initFlag == 0 ) {
	    //2003/02/21 E.Takase //2002/11/14 E.Takase
	    //2003/02/21 E.Takase //コンミの場合はチェック方法かえる
	    //2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
		    // 固有抵抗率の例外処理：電流チェック（10%)
		    if (Edt_Sub74->Value > COM_DIFF && (Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
		          Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9)) {
		       if (F10Flag)
		          Edt_Sub74->Font->Color = clRed;
		       ErrorFlag = 1;
		    }
		    if (Edt_Sub76->Value > COM_DIFF && (Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
		          Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9)) {
		       if (F10Flag)
		          Edt_Sub76->Font->Color = clRed;
		       ErrorFlag = 1;
		    }
	    //2003/02/21 E.Takase } else {
		//2003/02/21 E.Takase     // 固有抵抗率の例外処理：電流チェック（10%)
		//2003/02/21 E.Takase     if (Edt_Sub74->Value > COM_DIFF) {
		//2003/02/21 E.Takase        if (F10Flag)
		//2003/02/21 E.Takase           Edt_Sub74->Font->Color = clRed;
		//2003/02/21 E.Takase        ErrorFlag = 1;
		//2003/02/21 E.Takase     }
		//2003/02/21 E.Takase     if (Edt_Sub76->Value > COM_DIFF) {
		//2003/02/21 E.Takase        if (F10Flag)
		//2003/02/21 E.Takase           Edt_Sub76->Font->Color = clRed;
		//2003/02/21 E.Takase        ErrorFlag = 1;
		//2003/02/21 E.Takase     }
	    //2003/02/21 E.Takase }
	} else {
	    //2003/02/21 E.Takase //2002/11/14 E.Takase
	    //2003/02/21 E.Takase //コンミの場合はチェック方法かえる
	    //2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
		    // 固有抵抗率の例外処理：電流チェック（10%)
		    if (M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF && (M_Kdb2[i].SOKUTEI_MEI4 > Cur_Kdb1.JYOKEN1 * 1.1 ||
		          M_Kdb2[i].SOKUTEI_MEI4 < Cur_Kdb1.JYOKEN1 * 0.9)) {
		       if (F10Flag)
		          Edt_Sub74->Font->Color = clRed;
		       ErrorFlag = 1;
		    }
		    if (M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF && (M_Kdb2[i].SOKUTEI_MEI6 > Cur_Kdb1.JYOKEN1 * 1.1 ||
		          M_Kdb2[i].SOKUTEI_MEI6 < Cur_Kdb1.JYOKEN1 * 0.9)) {
		       if (F10Flag)
		          Edt_Sub76->Font->Color = clRed;
		       ErrorFlag = 1;
		    }
	    //2003/02/21 E.Takase } else {
		//2003/02/21 E.Takase     // 固有抵抗率の例外処理：電流チェック（10%)
		//2003/02/21 E.Takase     if (M_Kdb2[i].SOKUTEI_MEI4 > COM_DIFF) {
		//2003/02/21 E.Takase        if (F10Flag)
		//2003/02/21 E.Takase           Edt_Sub74->Font->Color = clRed;
		//2003/02/21 E.Takase        ErrorFlag = 1;
		//2003/02/21 E.Takase     }
		//2003/02/21 E.Takase     if (M_Kdb2[i].SOKUTEI_MEI6 > COM_DIFF) {
		//2003/02/21 E.Takase        if (F10Flag)
		//2003/02/21 E.Takase           Edt_Sub76->Font->Color = clRed;
		//2003/02/21 E.Takase        ErrorFlag = 1;
		//2003/02/21 E.Takase     }
	    //2003/02/21 E.Takase }

	}
 }

 // 色を変わるとBeep


 if (ErrorFlag == 1 && F10Flag) {
    T_Edit[i]->Font->Color = clRed;
    if (Sound == 1 && ScreenInitFlag == 0) {
       EndErrorFlag = 1;
       Beep();
    }
 } else {
//    if ( RSInputFlag == 1 && F10Flag == 1 && i != Cur_Kdb1.HIST_SOKUT-1) {
    if ( RSInputFlag == 1 && i != Cur_Kdb1.HIST_SOKUT-1) {
       MdPlayer->FileName = "RSInput.wav";
       MdPlayer->Open();
       MdPlayer->Play();
    }
    ////2002/12/03 固有抵抗率＆コンミの場合 グレー表示 E.Takase
    //if (Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
    //    T_Edit[i]->Font->Color = clGray;
    //} else {

        T_Edit[i]->Font->Color = clWindowText;
    //}
   /*
    if (ScreenInitFlag == 0) {
       // リード線取り付けの例外処理：電流チェック( 10%)
       if (Cur_Kdb1.KENSA_KMK == 3 && (Edt_Sub32->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
          Edt_Sub32->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
          T_Edit[i]->Font->Color = clRed;
          Beep();
          EndErrorFlag = 1;
       } else {
          // 固有抵抗率の例外処理：電流チェック（10%)
          if (Cur_Kdb1.KENSA_KMK == 7 && (Edt_Sub73->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9 || Edt_Sub75->Value >
             Cur_Kdb1.JYOKEN1 * 1.1 || Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {

             T_Edit[i]->Font->Color = clRed;
             Beep();
             EndErrorFlag = 1;
          } else  {
             if ( RSInputFlag == 1 && F10Flag == 1 && i != Cur_Kdb1.HIST_SOKUT-1) {
                MdPlayer->FileName = "RSInput.wav";
        	MdPlayer->Open();
        	MdPlayer->Play();
             }
             T_Edit[i]->Font->Color = clWindowText;
          }
       }
    } else { // ScreenInitFlag == 1
       // リード線取り付けの例外処理：電流チェック( 10%)
       if (Cur_Kdb1.KENSA_KMK == 3 && (M_Kdb2[i].SOKUTEI_MEI2 > Cur_Kdb1.JYOKEN1 * 1.1 ||
          M_Kdb2[i].SOKUTEI_MEI2 < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag && F10Flag) {
          T_Edit[i]->Font->Color = clRed;
       } else {
          // 固有抵抗率の例外処理：電流チェック（10%)
          if (Cur_Kdb1.KENSA_KMK == 7 && (M_Kdb2[i].SOKUTEI_MEI4 > Cur_Kdb1.JYOKEN1 * 1.1 ||
             M_Kdb2[i].SOKUTEI_MEI4 < Cur_Kdb1.JYOKEN1 * 0.9 || M_Kdb2[i].SOKUTEI_MEI6 >
             Cur_Kdb1.JYOKEN1 * 1.1 || M_Kdb2[i].SOKUTEI_MEI6 < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {

             T_Edit[i]->Font->Color = clRed;
          } else {
             if ( RSInputFlag == 1 && F10Flag == 1 && i != Cur_Kdb1.HIST_SOKUT-1) {
                MdPlayer->FileName = "RSInput.wav";
        	MdPlayer->Open();
        	MdPlayer->Play();
             }

             T_Edit[i]->Font->Color = clWindowText;
          }
       }
    }
    */
 }

 //2002/12/03 固有抵抗率＆コンミの場合 グレー表示 E.Takase
 if (Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
    T_Edit[i]->Font->Color = clGray;
 }

 RSInputFlag = 0;
 EndErrorFlag = ErrorFlag;
}
//---------------------------------------------------------------------------

// 統計とグラフ表示
void __fastcall TForm3::Toukei()
{
 int i, j, k ;
 char s_str[64];
 double T_double, T_High, T_Low, T_double1, T_double2;
 int N_Mid, N_High, N_Low, n1, n2, T_index;
 int SubFlag = 0;
 int LRFlag = 0;

 if (Cur_Kdb1.HIST_MAX < Cur_Kdb1.HIST_MIN && Cur_Kdb1.HIST_KIKAK == 1) {
    T_double = Cur_Kdb1.HIST_MIN;
    Cur_Kdb1.HIST_MIN = Cur_Kdb1.HIST_MAX;
    Cur_Kdb1.HIST_MAX = T_double;
 }

 // Y軸のScale 計算
 if (Cur_Kdb1.HIST_KIKAK == 1) { // 両側チェックケース
    //T_double = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/12;
    T_double = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/16;   // 2000.5.22 修正
    for (i = 18; i >= 0; i--) {
        //if (Standard_Scale[i] > T_double) {
        if (Standard_Scale[i] >= T_double) {  // 2000.5.22  修正
           T_double = Standard_Scale[i];
           i = -1;
        }
    }

    // 2000.3.6 N_Mid <= 7なると、N_Mid倍にする
    if (Cur_Kdb1.KOUMOKU_J == "ブラシ厚さ") {  // ブラシ厚さのみを対象する
        T_double1 = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/T_double;
        N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
        if (N_Mid <= 7) {
            N_Mid = N_Mid * 2;
            T_double = T_double / 2;
        }
    }

    // 2000.5.9 表示桁数によって、pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (T_Edit[0]->FPos == 0 && T_double < 1)
       T_double = 1;
    if (T_Edit[0]->FPos == 1 && T_double < 0.1)
       T_double = 0.1;
    if (T_Edit[0]->FPos == 2 && T_double < 0.01)
       T_double = 0.01;
    if (T_Edit[0]->FPos == 3 && T_double < 0.001)
       T_double = 0.001;
    // end of add 2000.5.9

    // 下限チェック
    T_double1 = Cur_Kdb1.HIST_MIN/T_double;
    n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
    //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
    if (fabs((double)n1 * T_double - Cur_Kdb1.HIST_MIN) <= COM_DIFF) {
       T_Low = Cur_Kdb1.HIST_MIN;
       n1 = 0;
    } else {
       T_Low = (double)(n1+1) * T_double;
       n1 = 1;
    }

    // 上限チェック
    //n2 = Cur_Kda1.HIST_MAX/T_double;
    T_double1 = Cur_Kdb1.HIST_MAX/T_double;
    n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
    if (fabs((double)n2 * T_double - Cur_Kdb1.HIST_MAX) <= COM_DIFF) {
       T_High = Cur_Kdb1.HIST_MAX;
       n2 = 0;
    } else {
       T_High = (double)n2 * T_double;
       n2 = 1;
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);
    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           Screen_Data[0][i+1] = Screen_Data[1][i];
       }
       Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           Screen_Data[0][i+1] = Screen_Data[1][i];
       }
       Screen_Data[0][0] = 0;
       Screen_Data[1][N_Low-1] = Cur_Kdb1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           Screen_Data[0][N_Low+i] = Cur_Kdb1.HIST_MIN + i * T_double;
           Screen_Data[1][N_Low+i] = Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       Screen_Data[0][N_Low] = Cur_Kdb1.HIST_MIN;
       Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           Screen_Data[1][N_Low+i+1] = Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       Screen_Data[1][N_Low + N_Mid - 1] = Cur_Kdb1.HIST_MAX;
       Screen_Data[0][N_Low + N_Mid] = Cur_Kdb1.HIST_MAX;
    } else {
       Screen_Data[0][N_Low + N_Mid] = Cur_Kdb1.HIST_MAX;
       Screen_Data[1][N_Low + N_Mid] = Cur_Kdb1.HIST_MAX + T_double;
       Screen_Data[0][N_Low + N_Mid + 1] = Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           Screen_Data[1][N_Low + N_Mid + i] = Cur_Kdb1.HIST_MAX + (i+1) * T_double;
           Screen_Data[0][N_Low + N_Mid + i+1] = Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 } else { // 片側チェック
    //T_index = 12;
    // 2000.5.9 表示桁数によって、default pitch調整
    // 整数：１；小数点1桁：０．１；
    // 小数点２桁：0.01；小数点3桁：0.001
    if (T_Edit[0]->FPos == 0)
       T_index = 7;
    if (T_Edit[0]->FPos == 1)
       T_index = 10;
    if (T_Edit[0]->FPos == 2)
       T_index = 13;
    if (T_Edit[0]->FPos == 3)
       T_index = 16;
    // end of add 2000.5.9
Again1:
	if (T_index >= 20) {   //2000.11.17追加
		MessageDlg( "規格を拡大して下さい（T_indexは20を超える）", mtConfirmation, mbYesNoCancel, 0);
	}

	T_double = Standard_Scale[T_index];    // default pitch;

	if (Cur_Kdb1.SOKUTE_SU > 1) {      // 収録データがあり

		//↓�@****************************************************************
		//コンミ＆抵抗率の場合 2002/12/03 E.Takase 
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
		
			T_double2 = M_Kdb2[0].SOKUTEI_MEI3;
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				if (Cur_Kdb1.HIST_KIKAK == 2) {  //最大値を探す
					if (M_Kdb2[i].SOKUTEI_MEI3 > T_double2)
						T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
					if (M_Kdb2[i].SOKUTEI_MEI5 > T_double2)
						T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
				} else { // 最小値を探す
					if (M_Kdb2[i].SOKUTEI_MEI3 < T_double2)
						T_double2 = M_Kdb2[i].SOKUTEI_MEI3;
					if (M_Kdb2[i].SOKUTEI_MEI5 < T_double2)
						T_double2 = M_Kdb2[i].SOKUTEI_MEI5;
				}
			}
		} else {
			T_double2 = M_Kdb2[0].SOKUTEI_CH;
			for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
				if (Cur_Kdb1.HIST_KIKAK == 2) {  //最大値を探す
					if (M_Kdb2[i].SOKUTEI_CH > T_double2)
					T_double2 = M_Kdb2[i].SOKUTEI_CH;
				} else { // 最小値を探す
					if (M_Kdb2[i].SOKUTEI_CH < T_double2)
						T_double2 = M_Kdb2[i].SOKUTEI_CH;
				}
			}
		
		}
		//↑�@****************************************************************

		if (Cur_Kdb1.HIST_KIKAK == 2) {
		// 下限チェック
			T_double1 = Cur_Kdb1.HIST_MIN/T_double;
			n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
			//n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
			if (fabs((double)n1 * T_double - Cur_Kdb1.HIST_MIN) <= COM_DIFF) {
				T_Low = Cur_Kdb1.HIST_MIN;
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
			// 上限チェック
			//n2 = Cur_Kda1.HIST_MAX/T_double;
			T_double1 = Cur_Kdb1.HIST_MAX/T_double;
			n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
			if (fabs((double)n2 * T_double - Cur_Kdb1.HIST_MAX) <= COM_DIFF) {
				T_High = Cur_Kdb1.HIST_MAX;
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
	} else { // 収録データなし
       if (Cur_Kdb1.HIST_KIKAK == 2) {
          // 下限チェック
          T_double1 = Cur_Kdb1.HIST_MIN/T_double;
          n1 = T_double1 + COM_DIFF;    // Borland C++ Bug???
          //n1 = (int)(Cur_Kda1.HIST_MIN/T_double);
          if (fabs((double)n1 * T_double - Cur_Kdb1.HIST_MIN) <= COM_DIFF) {
             T_Low = Cur_Kdb1.HIST_MIN;
             n1 = 0;
          } else {
             T_Low = (double)(n1+1) * T_double;
             n1 = 1;
          }

          T_High = T_Low + 12 * T_double;
          n2 = 0;
       } else {
          // 上限チェック
          //n2 = Cur_Kda1.HIST_MAX/T_double;
          T_double1 = Cur_Kdb1.HIST_MAX/T_double;
          n2 = T_double1 + COM_DIFF;   // Borland C++ Bug???
          if (fabs((double)n2 * T_double - Cur_Kdb1.HIST_MAX) <= COM_DIFF) {
             T_High = Cur_Kdb1.HIST_MAX;
             n2 = 0;
          } else {
             T_High = (double)n2 * T_double;
             n2 = 1;
          }

          T_Low = T_High - 12 * T_double;
          // 2000.11.17追加 T_Lowをチェックする。＜０場合はピーチを小さくする
          if (T_Low < 0) {
             T_index++;
             goto Again1;
          }
          n1 = 0;
       }
    }

    // 規格以内のライン数
    T_double1 = (T_High - T_Low)/T_double;
    N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    //N_Mid = (int)((T_High - T_Low)/T_double);

    if (N_Mid <= 7 && Cur_Kdb1.KOUMOKU_J == "ブラシ厚さ") { // スケール小さいすぎ、倍にする 2000.3.6
       T_double = T_double / 2;
       if (n1 > 0) {
          if (fabs(T_Low - (Cur_Kdb1.HIST_MIN - T_double)) <= COM_DIFF) {
             n1 = 0;
             T_Low = Cur_Kdb1.HIST_MIN;
          }
       }
       if (n2 > 0) {
          if (fabs(T_High - Cur_Kdb1.HIST_MAX - T_double) <= COM_DIFF) {
             n2 = 0;
             T_High = Cur_Kdb1.HIST_MAX;
          }
       }
       T_double1 = (T_High - T_Low)/T_double;
       N_Mid = T_double1 + COM_DIFF;  // Borland C++ Bug???
    }


    N_Mid = N_Mid + n1 + n2;

    // 規格以下のライン数
    N_Low = (int)((20 - N_Mid)/2);

    if (T_High - (N_Mid + N_Low) * T_double < 0)
       N_Low = (int)(T_High / T_double) - N_Mid;

    // 規格以上のライン数
    N_High = 20 - N_Mid - N_Low;

    // 下限以下スケール
    if (n1 == 0) {
       for (i = 0; i < N_Low; i++) {
           Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           Screen_Data[0][i+1] = Screen_Data[1][i];
       }
       Screen_Data[0][0] = 0;
    } else {
       for (i = 0; i < N_Low-1; i++) {
           Screen_Data[1][i] = T_Low - (N_Low - 1 - i) * T_double;
           Screen_Data[0][i+1] = Screen_Data[1][i];
       }
       Screen_Data[0][0] = 0;
       Screen_Data[1][N_Low-1] = Cur_Kdb1.HIST_MIN;
    }

    // 規格以内スケール
    if (n1 == 0) {
       for (i = 0; i < N_Mid; i++) {
           Screen_Data[0][N_Low+i] = T_Low + i * T_double;
           Screen_Data[1][N_Low+i] = Screen_Data[0][N_Low+i] + T_double;
       }
    } else {
       Screen_Data[0][N_Low] = Cur_Kdb1.HIST_MIN;
       Screen_Data[1][N_Low] = T_Low;
       for (i = 0; i < N_Mid-1; i++) {
           Screen_Data[0][N_Low+i+1] = T_Low + i * T_double;
           Screen_Data[1][N_Low+i+1] = Screen_Data[0][N_Low+i+1] + T_double;
       }
    }

    if (n2 != 0) {
       Screen_Data[1][N_Low + N_Mid - 1] = Cur_Kdb1.HIST_MAX;
       Screen_Data[0][N_Low + N_Mid] = Cur_Kdb1.HIST_MAX;
    } else {
       Screen_Data[0][N_Low + N_Mid] = T_High;
       Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       Screen_Data[0][N_Low + N_Mid + 1] = Screen_Data[1][N_Low + N_Mid];
    }

    // 上限以上スケール
    if (n2 == 0) {
       for (i = 1; i < N_High - 1; i++) {
           Screen_Data[1][N_Low + N_Mid + i] = T_High + (i+1) * T_double;
           Screen_Data[0][N_Low + N_Mid + i+1] = Screen_Data[1][N_Low + N_Mid + i];
       }
    } else {
       Screen_Data[1][N_Low + N_Mid] = T_High + T_double;
       Screen_Data[0][N_Low + N_Mid + 1] = T_High + T_double;
       for (i = 0; i < N_High-2; i++) {
           Screen_Data[1][N_Low + N_Mid + 1 + i] = T_High + (i+2) * T_double;
           Screen_Data[0][N_Low + N_Mid + 2 + i] = T_High + (i+2) * T_double;
       }
    }
 }

	// 個数（Screen_Data[2][]）初期化
	for (i = 0; i < 20; i++)
		Screen_Data[2][i] = 0;

	// 個数 Counter
	if (Cur_Kdb1.SOKUTE_SU > 0) {
		//↓�@****************************************************************
		//コンミ＆抵抗率の場合 2002/12/03 E.Takase
		if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				//電圧 左
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI3 < Screen_Data[1][j] - COM_DIFF)) {
							//if ((Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Cur_Kdb1.HIST_MAX) <= COM_DIFF &&
							//   fabs(Screen_Data[0][j] - Cur_Kdb1.HIST_MAX) <= COM_DIFF)
							//   Screen_Data[2][j-1] += 1;
							//else
							Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI3 - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI3 >= Screen_Data[0][j] + COM_DIFF)) {
							Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
				   }
				}
				//電圧 右
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_MEI5 < Screen_Data[1][j] - COM_DIFF)) {
							//if ((Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Cur_Kdb1.HIST_MAX) <= COM_DIFF &&
							//   fabs(Screen_Data[0][j] - Cur_Kdb1.HIST_MAX) <= COM_DIFF)
							//   Screen_Data[2][j-1] += 1;
							//else
							Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}

					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_MEI5 - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_MEI5 >= Screen_Data[0][j] + COM_DIFF)) {
							Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
					}
				}
			}
		//コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
		} else {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				for (j = 19; j >= 0; j--) {
					if (j != 19) {
						if (fabs(M_Kdb2[i].SOKUTEI_CH - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= Screen_Data[0][j] + COM_DIFF &&
								M_Kdb2[i].SOKUTEI_CH < Screen_Data[1][j] - COM_DIFF)) {
							//if ((Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) &&
							//   fabs(M_Kdb2[i].SOKUTEI_CH - Cur_Kdb1.HIST_MAX) <= COM_DIFF &&
							//   fabs(Screen_Data[0][j] - Cur_Kdb1.HIST_MAX) <= COM_DIFF)
							//   Screen_Data[2][j-1] += 1;
							//else
							Screen_Data[2][j] += 1;
							//j = 20;      // 2000.3.9
							j = -1;
						}
					} else { // j == 19
						if (fabs(M_Kdb2[i].SOKUTEI_CH - Screen_Data[0][j]) <= COM_DIFF ||
								(M_Kdb2[i].SOKUTEI_CH >= Screen_Data[0][j] + COM_DIFF)) {
							Screen_Data[2][j] += 1;
							//j = 20;       // 2000.3.9
							j = -1;
						}
				   }
				}
			}

		}
		//↑�@****************************************************************

	}

 // 表示
 k = 0;
 for (i = 0; i < 20; i++) {
     if (T_Edit[0]->FPos == 2)
        sprintf(s_str, "%.2f", Screen_Data[0][19-i]);
     else
        sprintf(s_str, "%.3f", Screen_Data[0][19-i]);
     if (Screen_Data[0][19-i] >= 0 && k == 0) { // 2000.3.9
        S_Panel[0][i]->Caption = s_str;
        if (Screen_Data[0][19-i] == 0)
           k = 1;
     } else {
        S_Panel[0][i]->Caption = " ";
        k = 1;
     }

     if (T_Edit[0]->FPos == 2)
        sprintf(s_str, "%.2f", Screen_Data[1][19-i]);
     else
        sprintf(s_str, "%.3f", Screen_Data[1][19-i]);
     if (Screen_Data[1][19-i] > 0 || i == 0) { // 2000.3.9
        if (i == 0)
           S_Panel[1][i]->Caption = "以上";
        else
           S_Panel[1][i]->Caption = s_str;
     } else
        S_Panel[1][i]->Caption = " ";

     sprintf(s_str, "%d", (int)(Screen_Data[2][19-i]));
     S_Panel[2][i]->Caption = s_str;
 }

 DrawGraph();

 // 統計
 Lbl_SOKUTE_SU->Caption = 0;
 Lbl_SOKUTE_MIN->Caption = 0;
 Lbl_SOKUTE_MAX->Caption = 0;
 Lbl_SOKUTE_AVE->Caption = 0;
 Lbl_SOKUTE_R->Caption = 0;
 Lbl_SIGUMA->Caption = 0;
 Lbl_SOKUTE_CP->Caption = 0;
 if (Cur_Kdb1.HIST_KIKAK == 1) {
    Lbl_SOKUTE_CPK->Caption = 0;
    Lbl_SOKUTE_K->Caption = 0;
 }
 Lbl_SOKUTE_P->Caption = 0;
 
	if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {

		if (Cur_Kdb1.HIST_SOKUT > 0) {
			if (Cur_Kdb1.SOKUTE_SU <= 0) {
				Cur_Kdb1.SOKUTE_AVE = 0;
				Cur_Kdb1.SOKUTE_MIN = 0;
				Cur_Kdb1.SOKUTE_MAX = 0;
				Cur_Kdb1.SOKUTE_R = 0;
				Cur_Kdb1.SOKUTE_SGM = 0;
				Cur_Kdb1.SOKUTE_CP = 0;
				Cur_Kdb1.SOKUTE_CPK = 0;
				Cur_Kdb1.SOKUTE_K = 0;
				Cur_Kdb1.SOKUTE_P = 0;
				Cur_Kdb1.SOKUTE_SU = 0;
			} else {  // 統計
				Cur_Kdb1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_MEI3;
				Cur_Kdb1.SOKUTE_AVE += M_Kdb2[0].SOKUTEI_MEI5;
                if (M_Kdb2[0].SOKUTEI_MEI3 > M_Kdb2[0].SOKUTEI_MEI5) {
				    Cur_Kdb1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI5;
                    Cur_Kdb1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI3;
                } else {
				    Cur_Kdb1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_MEI3;
                    Cur_Kdb1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_MEI5;
                }
				

				// 平均値、最大値、最小値
				for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
					Cur_Kdb1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI3;
					Cur_Kdb1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_MEI5;
					if (Cur_Kdb1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI3)
						Cur_Kdb1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI3;
					if (Cur_Kdb1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_MEI5)
						Cur_Kdb1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_MEI5;
					if (Cur_Kdb1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI3)
						Cur_Kdb1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI3;
					if (Cur_Kdb1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_MEI5)
						Cur_Kdb1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_MEI5;
				}
				Cur_Kdb1.SOKUTE_AVE = Cur_Kdb1.SOKUTE_AVE/(Cur_Kdb1.SOKUTE_SU*2);

				Cur_Kdb1.SOKUTE_R = Cur_Kdb1.SOKUTE_MAX - Cur_Kdb1.SOKUTE_MIN;

				// σ
				Cur_Kdb1.SOKUTE_SGM = 0;
				Cur_Kdb1.SOKUTE_CP = 0;
				Cur_Kdb1.SOKUTE_K = 0;
				Cur_Kdb1.SOKUTE_CPK = 0;
				Cur_Kdb1.SOKUTE_P = 0;

				if (Cur_Kdb1.SOKUTE_SU > 1) {
				    for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
					    Cur_Kdb1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI3 -
											    Cur_Kdb1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI3 -
											    Cur_Kdb1.SOKUTE_AVE);
					    Cur_Kdb1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_MEI5 -
											    Cur_Kdb1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_MEI5 -
											    Cur_Kdb1.SOKUTE_AVE);
				    }
				    Cur_Kdb1.SOKUTE_SGM = sqrt(Cur_Kdb1.SOKUTE_SGM / ((Cur_Kdb1.SOKUTE_SU*2) - 1));

				    if (Cur_Kdb1.SOKUTE_SGM > COM_DIFF) {
					    switch (Cur_Kdb1.HIST_KIKAK) {
						    case 1:
							    Cur_Kdb1.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
													    (6 * Cur_Kdb1.SOKUTE_SGM);
							    // K
							    Cur_Kdb1.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - Cur_Kdb1.SOKUTE_AVE) /
												    ((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

							    // CPK
							    Cur_Kdb1.SOKUTE_CPK = (1-Cur_Kdb1.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
												    	Cur_Kdb1.HIST_MIN) / (6 * Cur_Kdb1.SOKUTE_SGM);
							    break;
							    case 2:
								    Cur_Kdb1.SOKUTE_CP = fabs((Cur_Kdb1.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
														    (3 * Cur_Kdb1.SOKUTE_SGM);
								    Cur_Kdb1.SOKUTE_K = 0;
								    Cur_Kdb1.SOKUTE_CPK = 0;
								    break;
							    case 3:
								    Cur_Kdb1.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - Cur_Kdb1.SOKUTE_AVE)) /
													        (3 * Cur_Kdb1.SOKUTE_SGM);
								    Cur_Kdb1.SOKUTE_K = 0;
								    Cur_Kdb1.SOKUTE_CPK = 0;
								    break;
					    }
					}
				}
			}

			// P 不良率
			int ErrorNo = 0;
			if (Cur_Kdb1.SOKUTE_SU > 0) {
				for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
					// 規格判断
					if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
						if (M_Kdb2[i].SOKUTEI_MEI3 < Cur_Kdb1.HIST_MIN)
							ErrorNo++;
						if (M_Kdb2[i].SOKUTEI_MEI5 < Cur_Kdb1.HIST_MIN)
							ErrorNo++;
					}

					if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                        //2008.05.21 E.Takase 規格有効判断は以上未満
						//if (M_Kdb2[i].SOKUTEI_MEI3 > Cur_Kdb1.HIST_MAX)
						if (M_Kdb2[i].SOKUTEI_MEI3+COM_DIFF >= Cur_Kdb1.HIST_MAX)
							ErrorNo++;
                        //2008.05.21 E.Takase 規格有効判断は以上未満
						//if (M_Kdb2[i].SOKUTEI_MEI5 > Cur_Kdb1.HIST_MAX)
						if (M_Kdb2[i].SOKUTEI_MEI5+COM_DIFF >= Cur_Kdb1.HIST_MAX)
							ErrorNo++;
					}
				}
				Cur_Kdb1.SOKUTE_P = (double)ErrorNo/(double)(Cur_Kdb1.SOKUTE_SU*2) * 100.0;
			} else
				Cur_Kdb1.SOKUTE_P = 0;
	    }

	} else {
		if (Cur_Kdb1.HIST_SOKUT > 0) {
			if (Cur_Kdb1.SOKUTE_SU <= 0) {
				Cur_Kdb1.SOKUTE_AVE = 0;
				Cur_Kdb1.SOKUTE_MIN = 0;
				Cur_Kdb1.SOKUTE_MAX = 0;
				Cur_Kdb1.SOKUTE_R = 0;
				Cur_Kdb1.SOKUTE_SGM = 0;
				Cur_Kdb1.SOKUTE_CP = 0;
				Cur_Kdb1.SOKUTE_CPK = 0;
				Cur_Kdb1.SOKUTE_K = 0;
				Cur_Kdb1.SOKUTE_P = 0;
				Cur_Kdb1.SOKUTE_SU = 0;
			} else {  // 統計
				Cur_Kdb1.SOKUTE_AVE = M_Kdb2[0].SOKUTEI_CH;
				Cur_Kdb1.SOKUTE_MIN = M_Kdb2[0].SOKUTEI_CH;
				Cur_Kdb1.SOKUTE_MAX = M_Kdb2[0].SOKUTEI_CH;

				// 平均値、最大値、最小値
				for (i = 1; i < Cur_Kdb1.SOKUTE_SU; i++) {
					Cur_Kdb1.SOKUTE_AVE += M_Kdb2[i].SOKUTEI_CH;
					if (Cur_Kdb1.SOKUTE_MIN > M_Kdb2[i].SOKUTEI_CH)
						Cur_Kdb1.SOKUTE_MIN = M_Kdb2[i].SOKUTEI_CH;
					if (Cur_Kdb1.SOKUTE_MAX < M_Kdb2[i].SOKUTEI_CH)
						Cur_Kdb1.SOKUTE_MAX = M_Kdb2[i].SOKUTEI_CH;
				}
				Cur_Kdb1.SOKUTE_AVE = Cur_Kdb1.SOKUTE_AVE/Cur_Kdb1.SOKUTE_SU;

				Cur_Kdb1.SOKUTE_R = Cur_Kdb1.SOKUTE_MAX - Cur_Kdb1.SOKUTE_MIN;

				// σ
				Cur_Kdb1.SOKUTE_SGM = 0;
				Cur_Kdb1.SOKUTE_CP = 0;
				Cur_Kdb1.SOKUTE_K = 0;
				Cur_Kdb1.SOKUTE_CPK = 0;
				Cur_Kdb1.SOKUTE_P = 0;

				if (Cur_Kdb1.SOKUTE_SU > 1) {
					for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
						Cur_Kdb1.SOKUTE_SGM += (M_Kdb2[i].SOKUTEI_CH -
													Cur_Kdb1.SOKUTE_AVE) * (M_Kdb2[i].SOKUTEI_CH -
													Cur_Kdb1.SOKUTE_AVE);
					}
					Cur_Kdb1.SOKUTE_SGM = sqrt(Cur_Kdb1.SOKUTE_SGM / (Cur_Kdb1.SOKUTE_SU - 1));

					if (Cur_Kdb1.SOKUTE_SGM > COM_DIFF) {
						switch (Cur_Kdb1.HIST_KIKAK) {
							case 1:
								Cur_Kdb1.SOKUTE_CP = (Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN) /
														(6 * Cur_Kdb1.SOKUTE_SGM);
								// K
								Cur_Kdb1.SOKUTE_K = fabs((Cur_Kdb1.HIST_MAX + Cur_Kdb1.HIST_MIN) /2 - Cur_Kdb1.SOKUTE_AVE) /
													((Cur_Kdb1.HIST_MAX - Cur_Kdb1.HIST_MIN)/2);

								// CPK
								Cur_Kdb1.SOKUTE_CPK = (1-Cur_Kdb1.SOKUTE_K) * (Cur_Kdb1.HIST_MAX -
														Cur_Kdb1.HIST_MIN) / (6 * Cur_Kdb1.SOKUTE_SGM);
								break;
							case 2:
								Cur_Kdb1.SOKUTE_CP = fabs((Cur_Kdb1.SOKUTE_AVE - Cur_Kdb1.HIST_MIN)) /
														(3 * Cur_Kdb1.SOKUTE_SGM);
								Cur_Kdb1.SOKUTE_K = 0;
								Cur_Kdb1.SOKUTE_CPK = 0;
								break;
							case 3:
								Cur_Kdb1.SOKUTE_CP = fabs((Cur_Kdb1.HIST_MAX - Cur_Kdb1.SOKUTE_AVE)) /
														(3 * Cur_Kdb1.SOKUTE_SGM);
								Cur_Kdb1.SOKUTE_K = 0;
								Cur_Kdb1.SOKUTE_CPK = 0;
								break;
						}
					}
				}

				// P 不良率
				int ErrorNo = 0;
				if (Cur_Kdb1.SOKUTE_SU > 0) {
					for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
						// 規格判断
						if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
							if (M_Kdb2[i].SOKUTEI_CH < Cur_Kdb1.HIST_MIN)
								ErrorNo++;
						}

						if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
                            //2008.05.21 E.Takase 規格有効判断は以上未満
							//if (M_Kdb2[i].SOKUTEI_CH > Cur_Kdb1.HIST_MAX)
							if (M_Kdb2[i].SOKUTEI_CH+COM_DIFF >= Cur_Kdb1.HIST_MAX)
								ErrorNo++;
						}
					}
					Cur_Kdb1.SOKUTE_P = (double)ErrorNo/(double)Cur_Kdb1.SOKUTE_SU * 100.0;
				} else
					Cur_Kdb1.SOKUTE_P = 0;
			}
		}

	}
    // 表示
    if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2)
       sprintf(s_str, "%.03f", Cur_Kdb1.HIST_MIN);
    else
       strcpy(s_str, " ");
    Lbl_HIST_MIN1->Caption = s_str;

    if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3)
       sprintf(s_str, "%.03f", Cur_Kdb1.HIST_MAX);
    else
       strcpy(s_str, " ");
    Lbl_HIST_MAX1->Caption = s_str;

    //sprintf(s_str, "%.03f", Cur_Kdb1.HIST_MIN);
    //Lbl_HIST_MIN1->Caption = s_str;
    //sprintf(s_str, "%.03f", Cur_Kdb1.HIST_MAX);
    //Lbl_HIST_MAX1->Caption = s_str;

    //2002/12/03 E.Takase
    //抵抗率＆コンミの場合 右・左わけているので ｎは ×2
    if (Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
        Lbl_SOKUTE_SU->Caption = Cur_Kdb1.SOKUTE_SU * 2;
    } else {
        Lbl_SOKUTE_SU->Caption = Cur_Kdb1.SOKUTE_SU;
    }

    if (Cur_Kdb1.KENSA_KMK == 7) {  // 抵抗率の表示(整数)  2000.3.11
       //コンミ 2003.02.08
       if ( Cur_Kdb1.KEIJKBN == 3 ) {
          sprintf(s_str, "%.02f", Cur_Kdb1.SOKUTE_MIN);
          Lbl_SOKUTE_MIN->Caption = s_str;
          sprintf(s_str, "%.02f", Cur_Kdb1.SOKUTE_MAX);
          Lbl_SOKUTE_MAX->Caption = s_str;
          sprintf(s_str, "%.03f", Cur_Kdb1.SOKUTE_AVE);
          //Lbl_SOKUTE_AVE->Width = 93;
          Lbl_SOKUTE_AVE->Caption = s_str;
       } else {
          sprintf(s_str, "%d", (int)(Cur_Kdb1.SOKUTE_MIN+0.5));
          Lbl_SOKUTE_MIN->Caption = s_str;
          sprintf(s_str, "%d", (int)(Cur_Kdb1.SOKUTE_MAX+0.5));
          Lbl_SOKUTE_MAX->Caption = s_str;
          sprintf(s_str, "%.1f", Cur_Kdb1.SOKUTE_AVE);
          //Lbl_SOKUTE_AVE->Width = 93;
          Lbl_SOKUTE_AVE->Caption = s_str;
       }
    } else {
       if (T_Edit[0]->FPos == 2) {
          sprintf(s_str, "%.02f", Cur_Kdb1.SOKUTE_MIN);
          Lbl_SOKUTE_MIN->Caption = s_str;
          sprintf(s_str, "%.02f", Cur_Kdb1.SOKUTE_MAX);
          Lbl_SOKUTE_MAX->Caption = s_str;
          sprintf(s_str, "%.03f", Cur_Kdb1.SOKUTE_AVE);
          //Lbl_SOKUTE_AVE->Width = 93;
          Lbl_SOKUTE_AVE->Caption = s_str;
       } else { // 3桁
          sprintf(s_str, "%.03f", Cur_Kdb1.SOKUTE_MIN);
          Lbl_SOKUTE_MIN->Caption = s_str;
          sprintf(s_str, "%.03f", Cur_Kdb1.SOKUTE_MAX);
          Lbl_SOKUTE_MAX->Caption = s_str;
          sprintf(s_str, "%.04f", Cur_Kdb1.SOKUTE_AVE);
          //Lbl_SOKUTE_AVE->Width = 93;
          Lbl_SOKUTE_AVE->Caption = s_str;
       }
    }

    if (Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN != 3) { // 抵抗率:有効数字３桁          2000.3.13
                                   // コンミの場合は通常の表示 2003.02.08
       AnsiString str;
       // R
       str = ConvData(3, Cur_Kdb1.SOKUTE_R);
       Lbl_SOKUTE_R->Caption = str;

       // σ
       str = ConvData(3, Cur_Kdb1.SOKUTE_SGM);
       Lbl_SIGUMA->Caption = str;
    } else {
       sprintf(s_str, "%.5f", Cur_Kdb1.SOKUTE_R);
       Lbl_SOKUTE_R->Caption = s_str;
       sprintf(s_str, "%.5f", Cur_Kdb1.SOKUTE_SGM);
       Lbl_SIGUMA->Caption = s_str;
    }
    if (fabs(Cur_Kdb1.SOKUTE_CP) > COM_DIFF && Cur_Kdb1.SOKUTE_CP < S_Cp && F10Flag) {
       //Beep();
       Lbl_SOKUTE_CP->Font->Color = clRed;
    } else
       Lbl_SOKUTE_CP->Font->Color = clWindowText;
    sprintf(s_str, "%.2f", Cur_Kdb1.SOKUTE_CP);
    Lbl_SOKUTE_CP->Caption = s_str;
    if (Cur_Kdb1.HIST_KIKAK == 1) {
       Panel158->Color = 0x00FEE7BA;
       Panel158->Font->Color = clBlack;
       Panel160->Color = 0x00FEE7BA;
       Panel160->Font->Color = clBlack;
       Lbl_SOKUTE_CPK->Color = clWindow;
       Lbl_SOKUTE_CPK->Font->Color = clBlack;
       Lbl_SOKUTE_K->Color = clWindow;
       Lbl_SOKUTE_K->Font->Color = clBlack;
       if (fabs(Cur_Kdb1.SOKUTE_CPK) > COM_DIFF && Cur_Kdb1.SOKUTE_CPK < S_Cpk && F10Flag) {
          //Beep();
          Lbl_SOKUTE_CPK->Font->Color = clRed;
       } else
         Lbl_SOKUTE_CPK->Font->Color = clWindowText;
       sprintf(s_str, "%.2f", Cur_Kdb1.SOKUTE_CPK);
       Lbl_SOKUTE_CPK->Caption = s_str;
       sprintf(s_str, "%.3f", Cur_Kdb1.SOKUTE_K);
       Lbl_SOKUTE_K->Caption = s_str;
    } else {
       Lbl_SOKUTE_CPK->Caption = " ";
       Lbl_SOKUTE_K->Caption = " ";
       Panel158->Color = clMenu;
       Panel158->Font->Color = clGrayText;
       Panel160->Color = clMenu;
       Panel160->Font->Color = clGrayText;
       Lbl_SOKUTE_CPK->Color = clMenu;
       Lbl_SOKUTE_CPK->Font->Color = clGrayText;
       Lbl_SOKUTE_K->Color = clMenu;
       Lbl_SOKUTE_K->Font->Color = clGrayText;
    }
    sprintf(s_str, "%.2f", Cur_Kdb1.SOKUTE_P);
    Lbl_SOKUTE_P->Caption = s_str;
}

void __fastcall TForm3::DrawGraph()
{
 int MaxNo;     // 最大個数
 int i, T_Scale, j, k;
 RECT MyRect, T_Rect;
 double T_double;
 AnsiString string;
 int Unit_Len;

 // 最大個数を求める
 //MaxNo = 0;
 //for (i = 0; i < 20; i++)
 //    if (MaxNo < Screen_Data[2][i])
 //       MaxNo = Screen_Data[2][i];
 //MaxNo += 10;
 MaxNo = Cur_Kdb1.HIST_SOKUT;

 // スケールを求める
 T_double = (double)MaxNo/10.0;
 for (i = 7; i >= 0; i--) {
    if (Standard_Scale[i] >= T_double) {
       T_double = Standard_Scale[i];
       i = -1;
    }
 }
 T_Scale = T_double;
 E_Scale = T_double;

 // Draw領域をクリアする
 MyRect = Image1->ClientRect;
 Image1->Canvas->Brush->Color = clInfoBk;
 Image1->Canvas->Brush->Style = bsSolid;
 Image1->Canvas->Pen->Color = clWhite;
 Image1->Canvas->FillRect(MyRect);

 // 色、線のスタイル、フォントを設定する
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Pen->Style = psSolid;
 Image1->Canvas->Pen->Width = 1;
 Image1->Canvas->Font->Size = 8;

 // X軸
 Image1->Canvas->MoveTo(0,MyRect.top + 24);
 Image1->Canvas->LineTo(MyRect.right-10, MyRect.top + 24);

 // メッシュ
 Image1->Canvas->Pen->Style = psDot;
 for (i = 0; i < 20; i++) {
    Image1->Canvas->MoveTo(0,MyRect.bottom - 2 - 14 * i);
    Image1->Canvas->LineTo(MyRect.right-10, MyRect.bottom - 2 - 14 * i);
 }

 for (i = 1; i <= 10; i++) {
    Image1->Canvas->MoveTo((int)((MyRect.right-10)/10) * i, MyRect.bottom - 2);
    Image1->Canvas->LineTo((int)((MyRect.right-10)/10) * i, MyRect.top + 24);
 }

 // グラフ表示
 //Image1->Canvas->Brush->Color = clBlue;
 Image1->Canvas->Brush->Color = 0x00B0B000;
 Unit_Len = (int)((MyRect.right-10)/10);
 for (i = 0; i < 20; i++) {
    if (Screen_Data[2][i] > 0) {
       //T_double = Screen_Data[2][i]/(double)T_Scale;
       //T_Rect.left = 0;
       //T_Rect.right = (int)(T_double * (int)((MyRect.right-10)/10));
       //T_Rect.top = (19 - i) * 14 + MyRect.top + 26;
       //T_Rect.bottom = (20 - i) * 14 + MyRect.top + 26;

       //Image1->Canvas->FillRect(Rect(T_Rect.left,T_Rect.top, T_Rect.right, T_Rect.bottom));

       if (T_Scale <= 10) {
          T_double = Screen_Data[2][i]/(double)T_Scale;

          T_Rect.top = (19 - i) * 14 + MyRect.top + 27;
          T_Rect.bottom = (20 - i) * 14 + MyRect.top + 24;

          for (j = 0; j < T_double * T_Scale - COM_DIFF; j++) {
              T_Rect.left = (int)((double)j * (double)Unit_Len/(double)T_Scale);
              T_Rect.right = (int)((double)(j+1) * (double)Unit_Len/(double)T_Scale)-1;
              Image1->Canvas->FillRect(Rect(T_Rect.left,T_Rect.top, T_Rect.right, T_Rect.bottom));
          }
       } else {
          T_double = Screen_Data[2][i]/(double)T_Scale;
          k = T_Scale/10;

          T_Rect.top = (19 - i) * 14 + MyRect.top + 27;
          T_Rect.bottom = (20 - i) * 14 + MyRect.top + 24;

          if (Screen_Data[2][i] == (int)(Screen_Data[2][i]/k) * k)
             k = (int)(Screen_Data[2][i]/k);
          else
             k = (int)(Screen_Data[2][i]/k) + 1;

          for (j = 0; j < k; j++) {
              T_Rect.left = (int)((double)j * (double)Unit_Len/10.0);
              T_Rect.right = (int)((double)(j+1) * (double)Unit_Len/10.0)-1;
              Image1->Canvas->FillRect(Rect(T_Rect.left,T_Rect.top, T_Rect.right, T_Rect.bottom));
          }
       }
    }
 }

 // 規格線
 Image1->Canvas->Pen->Color = clRed;
 Image1->Canvas->Pen->Style = psSolid;
 Image1->Canvas->Pen->Width = 2;
 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 2) {
    // 下限線
    for (i = 0; i < 20; i++) {
        if (fabs(Screen_Data[0][i] - Cur_Kdb1.HIST_MIN) <= COM_DIFF) {
           Image1->Canvas->MoveTo(0, (20 - i) * 14 + MyRect.top + 25);
           Image1->Canvas->LineTo(MyRect.right - 10, (20 - i) * 14 + MyRect.top + 25);
           i = 20;
        }
    }
 }

 if (Cur_Kdb1.HIST_KIKAK == 1 || Cur_Kdb1.HIST_KIKAK == 3) {
    // 上限線
    for (i = 0; i < 20; i++) {
        if (fabs(Screen_Data[0][i] - Cur_Kdb1.HIST_MAX) <= COM_DIFF) {
           Image1->Canvas->MoveTo(0, (20 - i) * 14 + MyRect.top + 25);
           Image1->Canvas->LineTo(MyRect.right - 10, (20 - i) * 14 + MyRect.top + 25);
           i = 20;
        }
    }
 }

 Image1->Canvas->Pen->Width = 1;

 // 目盛り文字
 Image1->Canvas->Pen->Color = clBlack;
 Image1->Canvas->Brush->Color = clInfoBk;
 for (i = 1; i <= 10; i++) {
     string = i * T_Scale;
     Image1->Canvas->TextOut(i * (MyRect.right - 10)/10-10, MyRect.top + 10, string);
 }

 return;
}


void __fastcall TForm3::Edt_001Change(TObject *Sender)
{
 if (InputMode <= 2) { // directly input Mode
    CurrentChangeFlag = 1;
    AllChangeFlag = 1;

    // 計測したデータCount
    if (Cur_Kdb1.SOKUTE_SU < CurField && T_Edit[CurField-1]->Value > 0)
       Cur_Kdb1.SOKUTE_SU = CurField;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_001Enter(TObject *Sender)
{
 int Ypos, YposMin, YposMax;
 int LineNo;

 switch (InputMode) {
 case 0:
 case 1:
 case 2:
    // directly input mode
    for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
        if (T_Edit[i]->Focused()) {
           CurField = i+1;
           i = Cur_Kdb1.HIST_SOKUT;
           CurrentChangeFlag = 0;
        }
    }
    break;
 case 3:  // 取付抵抗
    for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
        if (T_Edit[i]->Focused()) {
           if (CurField > 0 && CurField <= Cur_Kdb1.HIST_SOKUT)
              T_Edit[CurField-1]->Color = clWindow;
           CurField = i+1;
           T_Edit[CurField-1]->Color = clYellow;
           i = Cur_Kdb1.HIST_SOKUT;
           CurrentChangeFlag = 0;
           switch(SubField) {
           case 0:
                Edt_Sub31->Enabled = true;
                Edt_Sub31->SetFocus();
                Edt_Sub31->SelectAll();
                break;
           case 1:
                Edt_Sub32->Enabled = true;
                Edt_Sub32->SetFocus();
                Edt_Sub32->SelectAll();
                break;
           }
        }
    }
    break;
 case 4:  // 母体
     for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
        if (T_Edit[i]->Focused()) {
           if (CurField > 0 && CurField <= Cur_Kdb1.HIST_SOKUT)
              T_Edit[CurField-1]->Color = clWindow;
           CurField = i+1;
           T_Edit[CurField-1]->Color = clYellow;
           i = Cur_Kdb1.HIST_SOKUT;
           CurrentChangeFlag = 0;
           switch(SubField) {
           case 0:
                Edt_Sub51->Enabled = true;
                Edt_Sub51->SetFocus();
                Edt_Sub51->SelectAll();
                break;
           case 1:
                Edt_Sub52->Enabled = true;
                Edt_Sub52->SetFocus();
                Edt_Sub52->SelectAll();
                break;
           case 2:
                Edt_Sub53->Enabled = true;
                Edt_Sub53->SetFocus();
                Edt_Sub53->SelectAll();
                break;
           case 3:
                Edt_Sub54->Enabled = true;
                Edt_Sub54->SetFocus();
                Edt_Sub54->SelectAll();
                break;
           }
        }
    }
    break;
 case 5:  // 固有抵抗
    for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
        if (T_Edit[i]->Focused()) {
           if (CurField > 0 && CurField <= Cur_Kdb1.HIST_SOKUT)
              T_Edit[CurField-1]->Color = clWindow;
           CurField = i+1;
           T_Edit[CurField-1]->Color = clYellow;
           i = Cur_Kdb1.HIST_SOKUT;
           CurrentChangeFlag = 0;
           Pan_Sub73->Caption = M_Kdb2[0].SOKUTEI_MEI7;
           switch(SubField) {
           case 0:
                Edt_Sub71->Enabled = true;
                Edt_Sub71->SetFocus();
                Edt_Sub71->SelectAll();
                break;
           case 1:
                Edt_Sub72->Enabled = true;
                Edt_Sub72->SetFocus();
                Edt_Sub72->SelectAll();
                break;
           case 2:
                if (SubField1 == 0) {
                   Edt_Sub73->Enabled = true;
                   Edt_Sub73->SetFocus();
                   Edt_Sub73->SelectAll();
                } else {
                   Edt_Sub74->Enabled = true;
                   Edt_Sub74->SetFocus();
                   Edt_Sub74->SelectAll();
                }
                break;
           case 3:
                if (SubField1 == 0) {
                   Edt_Sub75->Enabled = true;
                   Edt_Sub75->SetFocus();
                   Edt_Sub75->SelectAll();
                } else {
                   Edt_Sub76->Enabled = true;
                   Edt_Sub76->SetFocus();
                   Edt_Sub76->SelectAll();
                }
                break;
           }
        }
    }
    break;
 case 6:  // 抗折力
    for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
        if (T_Edit[i]->Focused()) {
           if (CurField > 0 && CurField <= Cur_Kdb1.HIST_SOKUT)
              T_Edit[CurField-1]->Color = clWindow;
           CurField = i+1;
           T_Edit[CurField-1]->Color = clYellow;
           i = Cur_Kdb1.HIST_SOKUT;
           CurrentChangeFlag = 0;
           Pan_Sub82->Caption = M_Kdb2[0].SOKUTEI_MEI4;
           switch(SubField) {
           case 0:
                Edt_Sub81->Enabled = true;
                Edt_Sub81->SetFocus();
                Edt_Sub81->SelectAll();
                break;
           case 1:
                Edt_Sub82->Enabled = true;
                Edt_Sub82->SetFocus();
                Edt_Sub82->SelectAll();
                break;
           case 2:
                Edt_Sub83->Enabled = true;
                Edt_Sub83->SetFocus();
                Edt_Sub83->SelectAll();
                break;
           }
        }
    }
    break;
 }
 if (InputMode >= 3 && InputMode <= 6) {
    // VertScrollBorの場所
    LineNo = (int)((CurField+3)/4);
    Ypos = (LineNo+1) * 29;
    YposMin = Ypos - ScrollBox1->Height;
    YposMax = (LineNo-1) * 29;
    if (LineNo == 1) { // LineNo = 1
       ScrollBox1->VertScrollBar->Position = 0;
    } else {
        if (ScrollBox1->VertScrollBar->Position < YposMin) {
           if (YposMin > 0) {
             ScrollBox1->VertScrollBar->Position = YposMin+3;
           } else
             ScrollBox1->VertScrollBar->Position = 0;
           } else {
           if (ScrollBox1->VertScrollBar->Position > YposMax) {
              if (ScrollBox1->VertScrollBar->Position - 30 > 0) {
                 ScrollBox1->VertScrollBar->Position = ScrollBox1->VertScrollBar->Position - 30;
              } else
                 ScrollBox1->VertScrollBar->Position = 0;
           }
       }
    }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_001Exit(TObject *Sender)
{
 switch(InputMode) {
    case 0:
    case 1:
    case 2:// directly input mode
         if (CurField > 0 && CurrentChangeFlag) {
            M_Kdb2[CurField-1].SOKUTEI_CH = T_Edit[CurField-1]->Value;

            if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
               Toukei();
               FieldColor(CurField-1,1,0);
            }
         }
         break;
    case 3:
         break;
    case 4:
         if (CurField > 0) {
            //M_Kdb2[CurField-1].SOKUTEI_CH = T_Edit[CurField-1]->Value;

            if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
               Toukei();
               FieldColor(CurField-1,1,0);
            }
         }
         break;
    case 5:
         break;
    case 6:
         break;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_001KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     StatBarClear( " ", 0);

     if (Key == VK_F1 || Key == VK_F2 || Key == VK_F3 || Key == VK_F4 ||
        Key == VK_F5 || Key == VK_F6 || Key == VK_F7 || Key == VK_F8 ||
        Key == VK_F9 || Key == VK_F10 || Key == VK_F11 || Key == VK_F12) {

        if (Cur_Kdb1.KENSA_KMK == 0 || Cur_Kdb1.KENSA_KMK == 1 || Cur_Kdb1.KENSA_KMK == 2 ||
           Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 6 || Cur_Kdb1.KENSA_KMK == 9 ||
           Cur_Kdb1.KENSA_KMK == 10 || Cur_Kdb1.KENSA_KMK == 11) {     // 直接入力
           Edt_001Exit(Sender);
        }

        if (Cur_Kdb1.KENSA_KMK == 3) {     // 取付抵抗
           if (Edt_Sub31->Focused())
              Edt_Sub31Exit(Sender);
           if (Edt_Sub32->Focused())
              Edt_Sub32Exit(Sender);
        }

        if (Cur_Kdb1.KENSA_KMK == 5) {     // 比重
           if (Edt_Sub51->Focused())
              Edt_Sub51Exit(Sender);
           if (Edt_Sub52->Focused())
              Edt_Sub52Exit(Sender);
           if (Edt_Sub53->Focused())
              Edt_Sub53Exit(Sender);
           if (Edt_Sub54->Focused())
              Edt_Sub54Exit(Sender);
        }

        if (Cur_Kdb1.KENSA_KMK == 7) {     // 固有抵抗
           if (Edt_Sub71->Focused())
              Edt_Sub71Exit(Sender);
           if (Edt_Sub72->Focused())
              Edt_Sub72Exit(Sender);
           if (Edt_Sub73->Focused())
              Edt_Sub73Exit(Sender);
           if (Edt_Sub74->Focused())
              Edt_Sub74Exit(Sender);
           if (Edt_Sub75->Focused())
              Edt_Sub75Exit(Sender);
           if (Edt_Sub76->Focused())
              Edt_Sub76Exit(Sender);
        }

        //2003/01/06 E.Takase
        //if (Cur_Kdb1.KENSA_KMK == 8) {     // 抗折力
        if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {     // 抗折力
           if (Edt_Sub81->Focused())
              Edt_Sub81Exit(Sender);
           if (Edt_Sub82->Focused())
              Edt_Sub82Exit(Sender);
           if (Edt_Sub83->Focused())
              Edt_Sub83Exit(Sender);
        }
     }


     switch(Key)
     {
         case VK_F1:
              Button1Click(Sender);
              break;
         case VK_F2:
              if (Cur_Kdb1.KENSA_KMK == 7) {   // 固有抵抗率
                 if (Edt_Sub73->Focused()) {
                    if (CurField > 1) {
                       Button2Click(Sender);
                       Edt_Sub76->SetFocus();
                       Edt_Sub76->SelectAll();
                    }
                    break;
                 }
                 if (Edt_Sub74->Focused()) {
                    Edt_Sub73->SetFocus();
                    Edt_Sub73->SelectAll();
                    break;
                 }
                 if (Edt_Sub75->Focused()) {
                    Edt_Sub74->SetFocus();
                    Edt_Sub74->SelectAll();
                    break;
                 }
                 if (Edt_Sub76->Focused()) {
                    Edt_Sub75->SetFocus();
                    Edt_Sub75->SelectAll();
                    break;
                 }
              }
              if (Cur_Kdb1.KENSA_KMK == 3) {   // リード線取り付け抵抗
                 if (Edt_Sub31->Focused()) {
                    if (CurField > 1) {
                       Button2Click(Sender);
                       Edt_Sub32->SetFocus();
                       Edt_Sub32->SelectAll();
                    }
                    break;
                 }
                 if (Edt_Sub32->Focused()) {
                    Edt_Sub31->SetFocus();
                    Edt_Sub31->SelectAll();
                    break;
                 }
              }
              Button2Click(Sender);
              break;

         case VK_F3:
              if (Cur_Kdb1.KENSA_KMK == 7) {   // 固有抵抗率
                 if (Edt_Sub76->Focused()) {
                    if (CurField < Cur_Kdb1.HIST_SOKUT) {
                       Button3Click(Sender);
                       Edt_Sub73->SetFocus();
                       Edt_Sub73->SelectAll();
                    }
                    break;
                 }
                 if (Edt_Sub73->Focused()) {
                    Edt_Sub74->SetFocus();
                    Edt_Sub74->SelectAll();
                    break;
                 }
                 if (Edt_Sub74->Focused()) {
                    Edt_Sub75->SetFocus();
                    Edt_Sub75->SelectAll();
                    break;
                 }
                 if (Edt_Sub75->Focused()) {
                    Edt_Sub76->SetFocus();
                    Edt_Sub76->SelectAll();
                    break;
                 }
              }

              if (Cur_Kdb1.KENSA_KMK == 3) {   // リード線取り付け抵抗
                 if (Edt_Sub32->Focused()) {
                    if (CurField < Cur_Kdb1.HIST_SOKUT) {
                       Button3Click(Sender);
                       Edt_Sub31->SetFocus();
                       Edt_Sub31->SelectAll();
                    }
                    break;
                 }
                 if (Edt_Sub31->Focused()) {
                    Edt_Sub32->SetFocus();
                    Edt_Sub32->SelectAll();
                    break;
                 }
              }
              Button3Click(Sender);
              break;

         case VK_F4:
              if (F4Flag == 1)
                 Button4Click(Sender);
              break;

         case VK_F5:
              Button5Click(Sender);
              break;

         case VK_F6:
              Button6Click(Sender);
              break;

         case VK_F7:
              Button7Click(Sender);
              break;

         case VK_F8:
              if (F8Flag == 1)
                 Button8Click(Sender);
              break;

         case VK_F9:
              if (F9Flag == 1)
                 Button9Click(Sender);
              break;

         case VK_F10:
              Button10Click(Sender);
              Key = 0;
              break;

         case VK_F11:
              Button11Click(Sender);
              break;

         case VK_F12:
              Button12Click(Sender);
              break;

         case VK_RETURN:
              if (Cur_Kdb1.KENSA_KMK == 7) { // 固有抵抗率
                 if (SubField == 2 || SubField == 3) {
                    if (SubField1 == 0) {
                       //SubField == 1;
                       //keybd_event(VK_TAB,0,0,0);
                       //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                       if (SubField == 2) {
                          Edt_Sub74->SetFocus();
                          Edt_Sub74->SelectAll();
                       } else {
                          Edt_Sub76->SetFocus();
                          Edt_Sub76->SelectAll();
                       }
                    } else {
                       SubField1 = 0;
                       if (SubField == 2) {
                           SubField = 3;
                           //keybd_event(VK_TAB,0,0,0);
                           //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                           Edt_Sub75->SetFocus();
                           Edt_Sub75->SelectAll();
                           //Radio_Sub74->Checked = true;
                       } else {
                           SubField = 2;
                           Button3Click(Sender);
                           //Radio_Sub73->Checked = true;
                       }
                    }
                 } else {
                    SubField1 = 0;
                    Button3Click(Sender);
                 }
                 break;
              }

              if (Cur_Kdb1.KENSA_KMK == 3) { // リード線抵抗
                 if (SubField == 0) {
                    SubField == 1;
                    //keybd_event(VK_TAB,0,0,0);
                    //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                    Edt_Sub32->SetFocus();
                    Edt_Sub32->SelectAll();
                 } else {
                    SubField = 0;
                    Button3Click(Sender);
                 }
                 break;
              }

              Button3Click(Sender);
              break;
/*
              if (Cur_Kdb1.KENSA_KMK == 3) { // リード線抵抗
                 if (SubField == 0) {
                    SubField == 1;
                    //keybd_event(VK_TAB,0,0,0);
                    //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                    Edt_Sub32->SetFocus();
                    Edt_Sub32->SelectAll();
                 } else {
                    SubField = 0;
                    Button3Click(Sender);
                 }
                 break;
              }

              if (Cur_Kdb1.KENSA_KMK == 7) { // 固有抵抗率
                 if (SubField == 2 || SubField == 3) {
                    if (SubField1 == 0) {
                       //SubField == 1;
                       //keybd_event(VK_TAB,0,0,0);
                       //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                       if (SubField == 2) {
                          Edt_Sub74->SetFocus();
                          Edt_Sub74->SelectAll();
                       } else {
                          Edt_Sub76->SetFocus();
                          Edt_Sub76->SelectAll();
                       }
                    } else {
                       SubField1 = 0;
                       if (SubField == 2) {
                           SubField = 3;
                           //keybd_event(VK_TAB,0,0,0);
                           //keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
                           Edt_Sub75->SetFocus();
                           Edt_Sub75->SelectAll();
                           //Radio_Sub74->Checked = true;
                       } else {
                           SubField = 2;
                           Button3Click(Sender);
                           //Radio_Sub73->Checked = true;
                       }
                    }
                 } else {
                    SubField1 = 0;
                    Button3Click(Sender);
                 }
                 break;
              }

              if (Cur_Kdb1.KENSA_KMK == 5) { // 母体比重
                 if (CurField == Cur_Kdb1.HIST_SOKUT) {
                    if (Cur_Kdb1.KEIJKBN <= 1) {
                       if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {

                          Button3Click(Sender);
                       } else {
                          T_Edit[0]->SetFocus();
                          if (EndErrorFlag == 0 && Cur_Kdb1.HIST_SOKUT > 0 && F10Flag == 1) {
                             //Beep();
                             MdPlayer->FileName = "KChang.wav";
        	             MdPlayer->Open();
        	             MdPlayer->Play();
                          }
                       }
                    } else { // 円柱
                       if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {

                          Button3Click(Sender);
                       } else {
                          T_Edit[0]->SetFocus();
                          if (EndErrorFlag == 0 && Cur_Kdb1.HIST_SOKUT > 0 && F10Flag == 1) {
                             MdPlayer->FileName = "KChang.wav";
        	             MdPlayer->Open();
        	             MdPlayer->Play();
                             //Beep();
                          }
                       }
                    }
                 } else {
                   Button3Click(Sender);
                 }
                 break;
              }

              if (Cur_Kdb1.KENSA_KMK == 8) { // 曲げ強さ
                 if (CurField == Cur_Kdb1.HIST_SOKUT) {
                    if (Cur_Kdb1.KEIJKBN <= 1) {
                       if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF ) {

                          Button3Click(Sender);
                       } else {
                          T_Edit[0]->SetFocus();
                          if (EndErrorFlag == 0 && Cur_Kdb1.HIST_SOKUT > 0 && F10Flag == 1) {
                             //Beep();
                             MdPlayer->FileName = "KChang.wav";
        	             MdPlayer->Open();
        	             MdPlayer->Play();
                          }
                       }
                    } else { // 円柱
                       if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

                          Button3Click(Sender);
                       } else {
                          T_Edit[0]->SetFocus();
                          if (EndErrorFlag == 0 && Cur_Kdb1.HIST_SOKUT > 0 && F10Flag == 1) {
                             //Beep();
                             MdPlayer->FileName = "KChang.wav";
        	             MdPlayer->Open();
        	             MdPlayer->Play();
                          }
                       }
                    }
                 } else {
                   Button3Click(Sender);
                 }
                 break;
              }

              Button3Click(Sender);
              break;
*/
         case VK_LEFT:
         case VK_UP:
              if (Edt_Sub31->Focused()) {
                 Button2Click(Sender);
                 break;
              }
              keybd_event(VK_SHIFT,0,0,0);
              keybd_event(VK_TAB,0,0,0);
              keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
              keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
              break;

         case VK_RIGHT:
         case VK_DOWN:
              if (Edt_Sub32->Focused()) {
                 Button3Click(Sender);
                 break;
              }
              keybd_event(VK_TAB,0,0,0);
              keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
              break;
     }

}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormActivate(TObject *Sender)
{
 int i;
 if (Cur_Kdb1.HIST_SOKUT > 0) {
    switch(InputMode) {
    case 0:
    case 1:
    case 2:
        T_Edit[0]->Enabled = true;
        T_Edit[0]->SetFocus();
        break;
    case 3:
        Edt_Sub31->Enabled = true;
        T_Edit[0]->SetFocus();
        break;
    case 4:
        T_Edit[0]->Enabled = true;
        T_Edit[0]->SetFocus();
        if (SubField == 0)
           Radio_Sub51->Checked = true;
        else
           Radio_Sub52->Checked = true;
        //2002/11/14 コンミ対応 E.Takase
        //if (Cur_Kdb1.KEIJKBN <= 1) {
        //   Radio_Sub52->Caption = "          幅     ";
        //   Radio_Sub53->Caption = "        長  さ   ";
        //} else {
        //   Radio_Sub52->Caption = "        直  径   ";
        //   Radio_Sub53->Caption = "        高  さ   ";
        //}
        switch(Cur_Kdb1.KEIJKBN) {
        case 1: //直方体
           Radio_Sub51->Caption = "        厚  さ   ";
           Radio_Sub52->Caption = "          幅     ";
           Radio_Sub53->Caption = "        長  さ   ";
           break;

        case 2: //円柱
           Radio_Sub51->Caption = "        厚  さ   ";
           Radio_Sub52->Caption = "        直  径   ";
           Radio_Sub53->Caption = "        高  さ   ";
           break;

        case 3: //コンミ
           Radio_Sub51->Caption = "        内  径   ";
           Radio_Sub52->Caption = "        直  径   ";
           Radio_Sub53->Caption = "        厚  さ   ";
           break;
        }


        break;
    case 5:
        T_Edit[0]->Enabled = true;
        T_Edit[0]->SetFocus();
        if (SubField == 0)
           Radio_Sub71->Checked = true;
        else
           Radio_Sub72->Checked = true;
        if (Cur_Kdb1.KEIJKBN <= 1) {
           Radio_Sub72->Caption = "          幅     ";
        } else {
           Radio_Sub72->Caption = "        直  径   ";
        }
        break;
    case 6:
        T_Edit[0]->Enabled = true;
        T_Edit[0]->SetFocus();
        if (SubField == 0)
           Radio_Sub81->Checked = true;
        else
           Radio_Sub82->Checked = true;
        if (Cur_Kdb1.KEIJKBN <= 1) {
           Radio_Sub82->Caption = "          幅     ";
        } else {
           Radio_Sub82->Caption = "        直  径   ";
        }
        break;
    }
 }



 if (MsgFlag == 1) {
    MsgFlag = 0;
    //20161128 Y.Onishi
    //PC6の場合、エラーメッセージを出さない
    //StatBarClear( "計測機器の初期化に失敗しました。キーボードからの入力は使用可能です。", 1);
    if (KikiType != 6) {
        StatBarClear( "計測機器の初期化に失敗しました。キーボードからの入力は使用可能です。", 1);
    }
 } else
    StatBarClear(" ", 0);
}
//---------------------------------------------------------------------------
// 計測項目選択(InputMode = 4, 5, 6)
void __fastcall TForm3::Button4Click(TObject *Sender)
{
 char tempo[256];

 if (InputMode >= 4) {
    // 項目を変わる音を鳴らす 2000.1.17 周
    //MdPlayer->FileName = "KChang.wav";
    //MdPlayer->Open();
    //MdPlayer->Play();
    //Beep();

    switch (InputMode) {
    case 4: // 比重
         switch (SubField) {
         case 0:
              Edt_Sub51->Enabled = false;
              Edt_Sub53->Enabled = false;
              Edt_Sub54->Enabled = false;
              Edt_Sub52->Enabled = true;
              Radio_Sub52->Checked = true;
              SubField = 1;
              //if (CurField > 0)
              // T_Edit[0]->SetFocus();
              Edt_Sub52->SetFocus();
              Edt_Sub52->SelectAll();
              if (ShareFlag) {
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              break;
         case 1:
              Edt_Sub51->Enabled = false;
              Edt_Sub52->Enabled = false;
              Edt_Sub54->Enabled = false;
              Edt_Sub53->Enabled = true;
              Radio_Sub53->Checked = true;
              SubField = 2;
              //if (CurField > 0)
              //   T_Edit[0]->SetFocus();
              Edt_Sub53->SetFocus();
              Edt_Sub53->SelectAll();
              if (ShareFlag) {
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              break;
         case 2:
              Edt_Sub51->Enabled = false;
              Edt_Sub52->Enabled = false;
              Edt_Sub53->Enabled = false;
              Edt_Sub54->Enabled = true;
              Radio_Sub54->Checked = true;
              SubField = 3;
              //if (CurField > 0)
              //   T_Edit[0]->SetFocus();
              Edt_Sub54->SetFocus();
              Edt_Sub54->SelectAll();

              //20161013 Y.Onishi
              /*
              Button8->Enabled = false;
              F8Flag = 0;
              if (KikiType == 1 && ShareFlag == 1) {
                 OldChannel = CurrentChannel;
                 CurrentChannel = 6;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              */
              //20161123 Y.Onishi
              //広陽版バグ修正
              /*
              Button8->Enabled = true;
              F8Flag = 1;
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              */
              if (iKojoKbn == 0){
                  Button8->Enabled = false;
                  F8Flag = 0;
              }
              else if (iKojoKbn == 1){
                  Button8->Enabled = true;
                  F8Flag = 1;
              }
              if (KikiType == 1 && ShareFlag == 1) {
                 //不要かも（Radio54Checkにて値設定済み）
                 if (iKojoKbn == 0){
                     CurrentChannel = 6;
                 }
                 else if (iKojoKbn == 1){
                     CurrentChannel = 5;
                 }
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              break;
         case 3:
              Edt_Sub52->Enabled = false;
              Edt_Sub53->Enabled = false;
              Edt_Sub54->Enabled = false;
              Edt_Sub51->Enabled = true;
              if (Cur_Kdb1.KEIJKBN == 2) {
                 Radio_Sub52->Checked = true;
                 SubField = 1;
                 Edt_Sub52->SetFocus();
                 Edt_Sub52->SelectAll();
              } else {
                 Radio_Sub51->Checked = true;
                 SubField = 0;
                 Edt_Sub51->SetFocus();
                 Edt_Sub51->SelectAll();
              }
              //if (CurField > 0)
              //   T_Edit[0]->SetFocus();
              if (ShareFlag) {
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              break;
         }
         break;
    case 5:  // 固有抵抗率
         switch (SubField) {
         case 0:	//厚さ
              Edt_Sub71->Enabled = false;
              Edt_Sub73->Enabled = false;
              Edt_Sub74->Enabled = false;
              Edt_Sub75->Enabled = false;
              Edt_Sub76->Enabled = false;
              Edt_Sub72->Enabled = false;
              
			  //コンミ＆抵抗率の場合 2002/12/03 E.Takase
			  if ( Cur_Kdb1.KEIJKBN == 3 ) {
	              Radio_Sub73->Checked = true;
	              Edt_Sub73->Enabled = true;
	              Edt_Sub74->Enabled = true;
	              Edt_Sub75->Enabled = true;
	              Edt_Sub76->Enabled = true;
	              SubField = 2;
	              SubField1 = 0;
	              Edt_Sub73->SetFocus();
	              Edt_Sub73->SelectAll();

	          //コンミ＆抵抗率以外の場合 2002/12/03 E.Takase
              } else {
	              Radio_Sub72->Checked = true;
	              Edt_Sub72->SetFocus();
	              Edt_Sub72->SelectAll();
	              SubField = 1;
              }
              
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              break;
         case 1:	//幅
              Edt_Sub71->Enabled = false;
              Edt_Sub72->Enabled = false;
              Edt_Sub73->Enabled = true;
              Edt_Sub74->Enabled = true;
              Edt_Sub75->Enabled = true;
              Edt_Sub76->Enabled = true;
              Radio_Sub73->Checked = true;
              SubField = 2;
              SubField1 = 0;
              Edt_Sub73->SetFocus();
              Edt_Sub73->SelectAll();
              if ((KikiType == 3 || KikiType == 4) && ShareFlag == 1) {
                 OldChannel = CurrentChannel;
                 CurrentChannel = 9;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              Button8->Enabled = false;
              F8Flag = 0;
              break;
         case 2:
              Edt_Sub72->Enabled = false;
              Edt_Sub73->Enabled = false;
              Edt_Sub74->Enabled = false;
              Edt_Sub75->Enabled = false;
              Edt_Sub76->Enabled = false;
//            Radio_Sub74->Checked = true;
//              SubField = 3;
              switch (Cur_Kdb1.KEIJKBN) {
			  //直方体＆抵抗率の場合 2002/12/03 E.Takase
			  //コンミ＆抵抗率の場合 2002/12/03 E.Takase
			  	 case 1:
			  	 case 3:
	                 Edt_Sub71->Enabled = true;
	                 Radio_Sub71->Checked = true;
	                 SubField = 0;
	                 SubField1 = 0;
	                 Edt_Sub71->SetFocus();
	                 Edt_Sub71->SelectAll();
			  	     break;
			  //円柱＆抵抗率の場合 2002/12/03 E.Takase
			  	 case 2:
	                 Edt_Sub72->Enabled = true;
	                 Radio_Sub72->Checked = true;
	                 SubField = 1;
	                 SubField1 = 0;
	                 Edt_Sub72->SetFocus();
	                 Edt_Sub72->SelectAll();
                     break;
			  }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              break;
         case 3:
              Edt_Sub72->Enabled = false;
              Edt_Sub73->Enabled = false;
              Edt_Sub74->Enabled = false;
              Edt_Sub75->Enabled = false;
              Edt_Sub76->Enabled = false;
              //SubField = 0;
              SubField1 = 0;
              if (Cur_Kdb1.KEIJKBN == 2) {
                 Edt_Sub72->Enabled = true;
                 Radio_Sub72->Checked = true;
                 SubField = 1;
                 Edt_Sub72->SetFocus();
                 Edt_Sub72->SelectAll();
              } else {
                 Edt_Sub71->Enabled = true;
                 Radio_Sub71->Checked = true;
                 SubField = 0;
                 Edt_Sub71->SetFocus();
                 Edt_Sub71->SelectAll();
              }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              break;
         }
         break;
    case 6: // 曲げ
         switch (SubField) {
         case 0:
              Edt_Sub81->Enabled = false;
              Edt_Sub82->Enabled = false;
              Edt_Sub83->Enabled = false;
              
              if ( Cur_Kdb1.KEIJKBN == 3 ) {
			  //コンミの場合 2002/12/03 E.Takase
	              Radio_Sub83->Checked = true;
	              Edt_Sub83->Enabled = true;
	              Edt_Sub83->SetFocus();
	              Edt_Sub83->SelectAll();
	              SubField = 2;
              //コンミ以外の場合 2002/12/03 E.Takase
			  } else {
	              Radio_Sub82->Checked = true;
	              Edt_Sub82->Enabled = true;
	              Edt_Sub82->SetFocus();
	              Edt_Sub82->SelectAll();
	              SubField = 1;
	          }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              break;
         case 1:
              Edt_Sub81->Enabled = false;
              Edt_Sub82->Enabled = false;
              Radio_Sub83->Checked = true;
              Edt_Sub83->Enabled = true;
              Edt_Sub83->SetFocus();
              Edt_Sub83->SelectAll();
              Edt_Sub83->Enabled = true;
              Edt_Sub81->Enabled = false;
              SubField = 2;
              //2009.03.13 MTS E.Takase [001]  ↓
              //材料試験機（単独使用）は機器タイプを5とする
              //if ((KikiType == 3 || KikiType == 4)  && ShareFlag == 1) {
              if ((KikiType == 5)  && ShareFlag == 1) {
              //2009.03.13 MTS E.Takase [001]  ↑
                 OldChannel = CurrentChannel;
                 //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
                 //CurrentChannel = 7;
                 CurrentChannel = 10;
                 //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
              }
              Button8->Enabled = false;
              F8Flag = 0;
              break;
         case 2:
              Edt_Sub82->Enabled = false;
              Edt_Sub83->Enabled = false;
              Edt_Sub81->Enabled = false;
              SubField1 = 0;
              if (Cur_Kdb1.KEIJKBN == 2) {
                 Edt_Sub82->Enabled = true;
                 Radio_Sub82->Checked = true;
                 SubField = 1;
                 Edt_Sub82->SetFocus();
                 Edt_Sub82->SelectAll();
              } else {
                 Edt_Sub81->Enabled = true;
                 Radio_Sub81->Checked = true;
                 SubField = 0;
                 Edt_Sub81->SetFocus();
                 Edt_Sub81->SelectAll();
              }
              if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
                 CurrentChannel = OldChannel;
                 sprintf(tempo, "CONNECT %d", CurrentChannel);
                 SharedMemory_Write(1, 0, tempo, strlen(tempo));
                 Button8->Enabled = true;
                 F8Flag = 1;
              }
              break;
         }
         break;
    }
 }
}
//---------------------------------------------------------------------------
// 前項
void __fastcall TForm3::Button2Click(TObject *Sender)
{
 if (Cur_Kdb1.HIST_SOKUT >0) {
    if (CurField > 1) {
       if ( !T_Edit[CurField-2]->Focused()) {
          T_Edit[CurField-2]->SetFocus();
          T_Edit[CurField-1]->SelectAll();
       }
    } else {
       T_Edit[0]->SetFocus();
       T_Edit[0]->SelectAll();
    }
 }
}
//---------------------------------------------------------------------------
// 次項
void __fastcall TForm3::Button3Click(TObject *Sender)
{
 if (CurField < Cur_Kdb1.HIST_SOKUT) {
    if (!T_Edit[CurField]->Focused()) {
       T_Edit[CurField]->SetFocus();
       T_Edit[CurField]->SelectAll();
    }
 } else
    if (Cur_Kdb1.HIST_SOKUT > 0) {
       //T_Edit[0]->SetFocus();
       //T_Edit[0]->SelectAll();
       //Beep();
       Button2->SetFocus();
       if (Cur_Kdb1.KENSA_KMK == 5) {// 母体比重
           if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
              if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           } else { // 円柱
              if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           }
           return;
        }

        if (Cur_Kdb1.KENSA_KMK == 7) {// 固有抵抗率
           if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
               if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                  M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                  M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                  M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF &&
                  M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF &&
                  M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF) {
                  T_Edit[CurField-1]->Color = clWindow;
                  Button11->SetFocus();
                  if (F10Flag == 0 || EndErrorFlag == 0) {
                     MdPlayer->FileName = "End.wav";
                     MdPlayer->Open();
                     MdPlayer->Play();
                  }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           } else { // 円柱
              if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           }
           return;
        }

        //2003/01/06 E.Takase
        //if (Cur_Kdb1.KENSA_KMK == 8) {// 曲げ
        if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12) {// 曲げ or 曲げ(現物)
           if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
              if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           } else if (Cur_Kdb1.KEIJKBN == 3) {  //コンミ　2003.02.12　E.Takase
              if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           } else { // 円柱
              if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
                 M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {
                 T_Edit[CurField-1]->Color = clWindow;
                 Button11->SetFocus();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              } else {
                 T_Edit[0]->SetFocus();
                 T_Edit[0]->SelectAll();
                 if (F10Flag == 0 || EndErrorFlag == 0) {
                    MdPlayer->FileName = "KChang.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                 }
              }
           }
           return;
        }

        T_Edit[CurField-1]->Color = clWindow;
        Button11->SetFocus();
        if (F10Flag == 0 || EndErrorFlag == 0) {
           MdPlayer->FileName = "End.wav";
           MdPlayer->Open();
           MdPlayer->Play();
        }
    }
}
//---------------------------------------------------------------------------
// 画面印刷
void __fastcall TForm3::Button5Click(TObject *Sender)
{
     Edt_001Exit(Sender);
     // ステータスメッセージ
     StatBarClear(MSG_09, 0);

     Form3->Print();
     StatBarClear(" ", 0);
}
//---------------------------------------------------------------------------
// nの追加
void __fastcall TForm3::Button7Click(TObject *Sender)
{
 int OldCursor;
 int OldSokuteSu;

     OldCursor = CurField;
     OldSokuteSu = Cur_Kdb1.HIST_SOKUT;

     Edt_001Exit(Sender);
     Form4->FormScreenInit();
     Form4->ShowModal();

     if (OldSokuteSu == Cur_Kdb1.HIST_SOKUT) {   // 変わらない
        T_Edit[OldCursor-1]->SetFocus();
        return;
     }
     AllChangeFlag = 1;

     if (OldSokuteSu > Cur_Kdb1.HIST_SOKUT) { // 減らす
        T_Edit[Cur_Kdb1.HIST_SOKUT-1]->SetFocus();
     } else {     // 増える
        T_Edit[OldSokuteSu]->SetFocus();
     }
}
//---------------------------------------------------------------------------
// チャンネル切り替え
void __fastcall TForm3::Button8Click(TObject *Sender)
{
 int OldField;
 char tempo[64];

 Edt_001Exit(Sender);

 if (ShareFlag) {
    switch(InputMode) {
    case 0:  // チャンネル切り替え機能なし
         break;
    case 1:  // PC1/2; Connect 1 〜 5
         // チャネル番号の設定
         // 現在のFocus番号を保存
         OldField = CurField;

         if (CurrentChannel < 5)
            CurrentChannel++;
         else
            CurrentChannel = 1;

         sprintf(tempo, "CONNECT %d", CurrentChannel);
         SharedMemory_Write(1, 0, tempo, strlen(tempo));

         // Focus番号を回復
         CurField = OldField;
         break;
    case 2: // チャンネルを切り替える機能無し
         // Connect 7を固定
         break;
    case 3: // チャンネルを切り替える機能無し
         // Connect 8を固定
         break;
    case 4: // PC1-2
         //20161013 Y.Onishi
         //if (SubField <= 2) {
         if (SubField <= 3) {
            // チャネル番号の設定
            // 現在のFocus番号を保存
            OldField = CurField;

            //20161013 Y.Onishi
            //if (CurrentChannel < 5)
            if (CurrentChannel < 4)
               CurrentChannel++;
            else
               CurrentChannel = 1;

            sprintf(tempo, "CONNECT %d", CurrentChannel);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));

            // Focus番号を回復
            CurField = OldField;

            OldChannel = CurrentChannel;
          }
          // SubField == 3: Connect 6を固定
          break;
    case 5: // PC1-2: SubField = 0,1
            // PC3-4: SubField = 3,4
          if (SubField == 0 || SubField == 1) {
             // チャネル番号の設定
             // 現在のFocus番号を保存
             OldField = CurField;

             if (CurrentChannel < 5)
                CurrentChannel++;
             else
                CurrentChannel = 1;

             sprintf(tempo, "CONNECT %d", CurrentChannel);
             SharedMemory_Write(1, 0, tempo, strlen(tempo));

             // Focus番号を回復
             CurField = OldField;
             OldChannel = CurrentChannel;
          }
          // SubField == 2, 3
          // Connect9を固定
          break;
    case 6:
         if (SubField == 0 || SubField == 1) {
            // チャネル番号の設定
            // 現在のFocus番号を保存
            OldField = CurField;

            if (CurrentChannel < 5)
               CurrentChannel++;
            else
               CurrentChannel = 1;

            sprintf(tempo, "CONNECT %d", CurrentChannel);
            SharedMemory_Write(1, 0, tempo, strlen(tempo));

            // Focus番号を回復
            CurField = OldField;
            OldChannel = CurrentChannel;
         }
         // SubField == 2
         // Connect 7を固定
         break;
    }
 }

 // Set Focus
 if (CurField > 0) {
    T_Edit[CurField-1]->SetFocus();
    T_Edit[CurField-1]->SelectAll();
 }

 Sleep(50);

 return;

}
//---------------------------------------------------------------------------

// 印刷
void __fastcall TForm3::Button6Click(TObject *Sender)
{
    bool flag;
    char *ptr;
    int i,j;

    //印刷桁数 既定値  Edt_001->FPos
	//KETA.MIN = Cur_Kdb1.SOKUTE_KET;
	//KETA.MAX = Cur_Kdb1.SOKUTE_KET;
	//KETA.R = Cur_Kdb1.SOKUTE_KET;
	//KETA.AVE =  Cur_Kdb1.SOKUTE_KET + 1;
	KETA.MIN = Edt_001->FPos;
	KETA.MAX = Edt_001->FPos;
	KETA.R = Edt_001->FPos;
	KETA.AVE = Edt_001->FPos + 1;
	KETA.SGM = 3;
	KETA.CP = 2;
	KETA.K = 3;
	KETA.CPK = 2;
	KETA.P = 3;
	KETA.SOKUTE_AVE = Cur_Kdb1.SOKUTE_AVE;
	KETA.SOKUTE_MIN = Cur_Kdb1.SOKUTE_MIN;
	KETA.SOKUTE_MAX = Cur_Kdb1.SOKUTE_MAX;
	KETA.SOKUTE_R   = Cur_Kdb1.SOKUTE_R  ;
	KETA.SOKUTE_SGM = Cur_Kdb1.SOKUTE_SGM;
	KETA.SOKUTE_CP  = Cur_Kdb1.SOKUTE_CP ;
	KETA.SOKUTE_CPK = Cur_Kdb1.SOKUTE_CPK;
	KETA.SOKUTE_K   = Cur_Kdb1.SOKUTE_K  ;
	KETA.SOKUTE_P   = Cur_Kdb1.SOKUTE_P  ;

    Form6->ShowModal();
    if ( Form6->ModalResult == mrCancel ) return;


    memcpy(E_Screen_Data,Screen_Data,sizeof(Screen_Data));
	//コンミ＆抵抗率の場合 2002/12/03 E.Takase
	if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
        Tokei_TeikoL();
/*

        for ( i = 0; i < 20; i++ ) {
            E_Screen_Data[2][i] = 0;
        }

		// 個数 Counter
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				//電圧 左
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

*/
    }

    //2003.02.13 E.Takase
    //flag = CSV_Write();
    flag = CSV_Write(0);
    if ( flag ) {
        flag = Excel_Write();
        if ( !(flag) ) {
            // ステータスメッセージ
            StatusBar1->Panels->Items[0]->Text = "Excelの起動に失敗しました";
            StatusBar1->Update();

        }
    } else {
     // ステータスメッセージ
     StatusBar1->Panels->Items[0]->Text = "データ作成に失敗しました";
     StatusBar1->Update();
    }

    //2003.02.13 E.Takase
    if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
        //Sleep(10000);
        Tokei_TeikoR();
/*
        for ( i = 0; i < 20; i++ ) {
            E_Screen_Data[2][i] = 0;
        }
		// 個数 Counter
		if (Cur_Kdb1.SOKUTE_SU > 0) {
			for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
				//for (j = 0; j < 20; j++) {    //2000.3.9
				//電圧 左
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

*/
        
        flag = CSV_Write(1);
        if ( flag ) {

            flag = Excel_Write();
            if ( !(flag) ) {
                // ステータスメッセージ
                StatusBar1->Panels->Items[0]->Text = "Excelの起動に失敗しました";
                StatusBar1->Update();

            }
        } else {
        // ステータスメッセージ
        StatusBar1->Panels->Items[0]->Text = "データ作成に失敗しました";
        StatusBar1->Update();
        }

    }

	Edt_001Exit(Sender);
  return;
}

//---------------------------------------------------------------------------

void __fastcall TForm3::Button10Click(TObject *Sender)
{
 int i;

 if (F10Flag)
    F10Flag = 0;
 else
    F10Flag = 1;

 ScreenInitFlag = 1;
 for (i = 0; i < Cur_Kdb1.SOKUTE_SU; i++)
     FieldColor(i,1,1);
 Toukei();
 ScreenInitFlag = 0;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// プローブ、スパンを入力
void __fastcall TForm3::Button9Click(TObject *Sender)
{
     Edt_001Exit(Sender);
     Form5->FormScreenInit();
     Form5->ShowModal();
     AllChangeFlag = 1;

     ScreenInitFlag = 1;
     //2003/01/06 E.Takase
     //if (Cur_Kdb1.KENSA_KMK == 8) { // 曲げ
     if (Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 12 ) { // 曲げ or 曲げ（現物）
        int Old_CurField;

        Old_CurField = CurField;
        for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
            CurField = i+1;
            Kousetu_Cal();
        }
        CurField = Old_CurField;
     }

     if (Cur_Kdb1.KENSA_KMK == 7) { //抵抗率
        int Old_CurField;

        Old_CurField = CurField;
        for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
            CurField = i+1;
            Teikou_Cal();
        }
        CurField = Old_CurField;
     }
     ScreenInitFlag = 0;

     if (Cur_Kdb1.HIST_SOKUT > 0 && CurField > 0) {
        if (CurField < Cur_Kdb1.HIST_SOKUT)  {
           T_Edit[CurField-1]->SetFocus();
           T_Edit[CurField-1]->SelectAll();
        } else {
           T_Edit[0]->SetFocus();
           T_Edit[0]->SelectAll();
        }
     }

     Toukei();

     //SubField = 0;
     //if (Cur_Kdb1.KENSA_KMK == 7) {
     //   Edt_Sub72->Enabled = false;
     //   Edt_Sub73->Enabled = false;
     //   Edt_Sub74->Enabled = false;
     //   Edt_Sub75->Enabled = false;
     //   Edt_Sub76->Enabled = false;
     //   Radio_Sub71->Checked = true;
     //} else {
     //   Edt_Sub82->Enabled = false;
     //   Edt_Sub83->Enabled = false;
     //   Radio_Sub81->Checked = true;
     //}
}

//---------------------------------------------------------------------------
void __fastcall TForm3::OnNotifyWriteData(TMessage &Message)
{
 int nNumber, i;
 double dVal, dVal2;
 char *p;

 // CONNECT n:   Return:  OK/ERROR
 // [Data]

 nNumber = SharedMemory_Read(2, SharedBuff);

  // RS232Cと接続した場合
 if (iShareFlag == 1) {      // OK/ERROR

    // RS232Cと接続成功した場合
    if (strncmp( SharedBuff, "OK", 2) == 0 )
       iShareFlag = 2;

    // RS232Cと接続エラーの場合
    if (strncmp( SharedBuff, "ERROR", 5) == 0 ){
       StatBarClear("計測機器の応答がありません。検索及びキーボードからの入力は使用可能です。", 1) ;
       iShareFlag = 0;
    }

    // RS232Cと接続エラーの場合
    if (strncmp( SharedBuff, "C_ERROR", 7) == 0 ){
       StatBarClear("計測機器は他のパソコンで使用しています。検索及びキーボードからの入力は使用可能です。", 1) ;
       iShareFlag = 0;
    }
 }

 // RS232Cと接続成功した場合 、受信した測定値を画面へ表示
 if (iShareFlag == 2) {
    // カソールを測定値ｺﾝﾄﾛｰﾙに合わせる場合しかﾃﾞｰﾀを受信しない
    if( nNumber > 0 &&  strncmp( SharedBuff, "OK", 2) != 0 &&
        strncmp(SharedBuff, "ERROR", 5) != 0) {

        //RS232C読み込みフラグ 1
 	    RSInputFlag = 1;

        switch (Cur_Kdb1.KENSA_KMK) {
        case 0:   // 線長さ
        case 1:   // 幅
        case 2:   // その他（ＰＣ１，２）
        case 4:   // 引張り
        case 9:   // 座屈
        case 11:  // その他 （ＰＣ３，ＰＣ４）
              for (i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
                  if (T_Edit[i]->Focused()) {
                     dVal = atof( SharedBuff ) + COM_DIFF;
                     if (T_Edit[i]->FPos == 2)
                        T_Edit[i]->Text = FormatFloat("#0.00", dVal);
                     else
                        T_Edit[i]->Text = FormatFloat("#0.000", dVal);
                     i = Cur_Kdb1.HIST_SOKUT;
                     keybd_event(VK_RETURN, 0,0,0);
                     keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                  }
              }
              break;
        case 3:    // 取付
              // データフォーマット：nnnn.nnn nnnn.nnn
              p = strchr(SharedBuff, ' ');
              if (p != NULL) {
                 dVal = atof(SharedBuff) + COM_DIFF;
                 dVal2 = atof(p+1) + COM_DIFF;
                 if (T_Edit[CurField-1]->FPos == 2) {
                    Edt_Sub31->Text = FormatFloat("#0.00", dVal);
                    Edt_Sub32->Text = FormatFloat("#0.00", dVal2);
                    M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub31->Value;
                    M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub32->Value;
                 } else {
                    Edt_Sub31->Text = FormatFloat("#0.000", dVal);
                    Edt_Sub32->Text = FormatFloat("#0.000", dVal2);
                    M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub31->Value;
                    M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub32->Value;
                 }
                 Edt_Sub32->SetFocus();
                 keybd_event(VK_RETURN, 0,0,0);
                 keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                 /*
                 if (CurField < Cur_Kdb1.HIST_SOKUT) {
                    T_Edit[CurField]->SetFocus();
                    T_Edit[CurField]->SelectAll();
                 } else  {
                    //T_Edit[0]->SetFocus();
                    //T_Edit[0]->SelectAll();
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                    T_Edit[CurField-1]->Color = clWindow;
                    Button11->SetFocus();
                 }
                 */
              }
              break;
        case 5:    // 母体
              if (CurField > 0) {
                 dVal = atof( SharedBuff ) + COM_DIFF;
                 switch(SubField) {
                 case 0:
                      if (CurrentChannel == 6)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub51->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub51->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 1:
                      if (CurrentChannel == 6)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub52->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub52->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 2:
                      if (CurrentChannel == 6)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub53->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub53->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 3:
                      //20161013 Y.Onishi
                      //if (CurrentChannel != 6 || KikiType != 1)
                      //20161126 Y.Onishi
                      //本社天秤不具合対応
                      if (iKojoKbn == 0){
                        if (CurrentChannel != 6 || KikiType != 1)
                                return;
                        if (T_Edit[CurField-1]->FPos == 2)
                                Edt_Sub54->Text = FormatFloat("#0.00", dVal);
                        else
                                Edt_Sub54->Text = FormatFloat("#0.000", dVal);
                        break;
                      }
                      else if (iKojoKbn == 1){
                        if (CurrentChannel == 6)
                                return;
                        if (T_Edit[CurField-1]->FPos == 2)
                                Edt_Sub54->Text = FormatFloat("#0.00", dVal);
                        else
                                Edt_Sub54->Text = FormatFloat("#0.000", dVal);
                        break;
                      }

                 }
                 keybd_event(VK_RETURN, 0,0,0);
                 keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                 /*
                 // Next Field
                 if (CurField < Cur_Kdb1.HIST_SOKUT) {
                    T_Edit[CurField]->SetFocus();
                    T_Edit[CurField]->SelectAll();
                 } else {
                    //T_Edit[0]->SetFocus();
                    //T_Edit[0]->SelectAll();
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                    //Beep();

                    if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF || Edt_Sub51->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub52->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub53->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF || Edt_Sub54->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    } else { // 円柱
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub52->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub53->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF || Edt_Sub54->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    }
                 }
                 */
              }
              break;
        case 7:    // 固有抵抗
              if (CurField > 0) {
                 dVal = atof( SharedBuff ) + COM_DIFF;
                 switch(SubField) {
                 case 0:
                      if (CurrentChannel > 5)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub71->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub71->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 1:
                      if (CurrentChannel > 5)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub72->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub72->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 2:
                      if (CurrentChannel != 9)
                         return;

                      p = strchr(SharedBuff, ' ');
                      if (p != NULL) {
                         dVal = atof(SharedBuff) + COM_DIFF;
                         dVal2 = atof(p+1) + COM_DIFF;
                         if (T_Edit[CurField-1]->FPos == 2) {
                            Edt_Sub73->Text = FormatFloat("#0.00", dVal);
                            Edt_Sub74->Text = FormatFloat("#0.00", dVal2);
                            M_Kdb2[CurField-1].SOKUTEI_MEI3 = Edt_Sub73->Value;
                            M_Kdb2[CurField-1].SOKUTEI_MEI4 = Edt_Sub74->Value;
                         } else {
                           Edt_Sub73->Text = FormatFloat("#0.000", dVal);
                           Edt_Sub74->Text = FormatFloat("#0.000", dVal2);
                           M_Kdb2[CurField-1].SOKUTEI_MEI3 = Edt_Sub73->Value;
                           M_Kdb2[CurField-1].SOKUTEI_MEI4 = Edt_Sub74->Value;
                         }
                         //SubField = 3;
                         //Edt_Sub75->SetFocus();
                         //Edt_Sub75->SelectAll();
                      }
                      break;
                 case 3:
                      if (CurrentChannel != 9)
                         return;

                      p = strchr(SharedBuff, ' ');
                      if (p != NULL) {
                         dVal = atof(SharedBuff) + COM_DIFF;
                         dVal2 = atof(p+1) + COM_DIFF;
                         if (T_Edit[CurField-1]->FPos == 2) {
                            Edt_Sub75->Text = FormatFloat("#0.00", dVal);
                            Edt_Sub76->Text = FormatFloat("#0.00", dVal2);
                            M_Kdb2[CurField-1].SOKUTEI_MEI5 = Edt_Sub75->Value;
                            M_Kdb2[CurField-1].SOKUTEI_MEI6 = Edt_Sub76->Value;
                         } else {
                           Edt_Sub75->Text = FormatFloat("#0.000", dVal);
                           Edt_Sub76->Text = FormatFloat("#0.000", dVal2);
                           M_Kdb2[CurField-1].SOKUTEI_MEI5 = Edt_Sub75->Value;
                           M_Kdb2[CurField-1].SOKUTEI_MEI6 = Edt_Sub76->Value;
                         }
                         //SubField = 2;
                         //Edt_Sub73->SetFocus();
                         //Edt_Sub73->SelectAll();
                      }
                      break;
                 }
                 if (SubField == 2)
                    Edt_Sub74->SetFocus();
                 if (SubField == 3)
                    Edt_Sub76->SetFocus();
                 keybd_event(VK_RETURN, 0,0,0);
                 keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                 /*
                 // Next Field
                 if (CurField < Cur_Kdb1.HIST_SOKUT) {
                    T_Edit[CurField]->SetFocus();
                    T_Edit[CurField]->SelectAll();
                 } else {
                    //T_Edit[0]->SetFocus();
                    //T_Edit[0]->SelectAll();
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                    //Beep();
                    if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF || Edt_Sub71->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub72->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub73->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF || Edt_Sub74->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF || Edt_Sub75->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF || Edt_Sub76->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    } else { // 円柱
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub72->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub73->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF || Edt_Sub74->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF || Edt_Sub75->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF || Edt_Sub76->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    }
                 }
                 */
              }
              break;
        case 8:    // 抗折力
        case 12:   // 現物曲げ強さ　2003.02.12
              if (CurField > 0) {
                 dVal = atof( SharedBuff ) + COM_DIFF;
                 switch(SubField) {
                 case 0:
                      //2009.03.13 MTS E.Takase [001]  ↓
                      //材料試験機（単独使用）は機器タイプを5とする
                      ////2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
                      ////if (CurrentChannel == 7 || KikiType == 3 || KikiType == 4)
                      //if (CurrentChannel == 10 || KikiType == 3 || KikiType == 4)
                      ////2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
                      if (CurrentChannel == 10 || KikiType == 5)
                      //2009.03.13 MTS E.Takase [001]  ↑
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub81->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub81->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 1:
                      //2009.03.13 MTS E.Takase [001]  ↓
                      //材料試験機（単独使用）は機器タイプを5とする
                      ////2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
                      ////if (CurrentChannel == 7 || KikiType == 3 || KikiType == 4)
                      //if (CurrentChannel == 10 || KikiType == 3 || KikiType == 4)
                      ////2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
                      if (CurrentChannel == 10 || KikiType == 5)
                      //2009.03.13 MTS E.Takase [001]  ↑
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub82->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub82->Text = FormatFloat("#0.000", dVal);
                      break;
                 case 2:
                      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
                      //if (CurrentChannel != 7 || KikiType == 1 || KikiType == 2)
                      //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
                      if (CurrentChannel != 10 || KikiType == 1 || KikiType == 2)
                         return;
                      if (T_Edit[CurField-1]->FPos == 2)
                         Edt_Sub83->Text = FormatFloat("#0.00", dVal);
                      else
                         Edt_Sub83->Text = FormatFloat("#0.000", dVal);
                      break;
                 }
                 //if (CurField < Cur_Kdb1.HIST_SOKUT) {
                 //   T_Edit[CurField]->SetFocus();
                 //   T_Edit[CurField]->SelectAll();
                 //} else {
                 //   T_Edit[0]->SetFocus();
                 //   T_Edit[0]->SelectAll();
                 //}
                 keybd_event(VK_RETURN, 0,0,0);
                 keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
                 /*
                 // Next Field
                 if (CurField < Cur_Kdb1.HIST_SOKUT) {
                    T_Edit[CurField]->SetFocus();
                    T_Edit[CurField]->SelectAll();
                 } else {
                    //T_Edit[0]->SetFocus();
                    //T_Edit[0]->SelectAll();
                    MdPlayer->FileName = "End.wav";
                    MdPlayer->Open();
                    MdPlayer->Play();
                    //Beep();
                    if (Cur_Kdb1.KEIJKBN <= 1) {  // 直方体
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF || Edt_Sub81->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub82->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub83->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    } else { // 円柱
                       if ((M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF || Edt_Sub82->Value > COM_DIFF) &&
                          (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF || Edt_Sub83->Value > COM_DIFF)) {
                          T_Edit[CurField-1]->Color = clWindow;
                          Button11->SetFocus();
                       } else {
                          T_Edit[0]->SetFocus();
                          T_Edit[0]->SelectAll();
                       }
                    }
                 }
                 */
              }
              break;
        }
    }
 }
}

void __fastcall TForm3::Radio_Sub51Click(TObject *Sender)
{
 char tempo[64];

     SubField = 0;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub52->Enabled = false;
     Edt_Sub53->Enabled = false;
     Edt_Sub54->Enabled = false;
     Edt_Sub51->Enabled = true;
     Edt_Sub51->SetFocus();
     Edt_Sub51->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub52Click(TObject *Sender)
{
 char tempo[64];

     SubField = 1;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub52->Enabled = true;

     Edt_Sub51->Enabled = false;
     Edt_Sub53->Enabled = false;
     Edt_Sub54->Enabled = false;

     if( Edt_Sub52->Enabled == true) {
          Edt_Sub52->SetFocus();
          Edt_Sub52->SelectAll();
     }

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub53Click(TObject *Sender)
{
 char tempo[64];

     SubField = 2;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub51->Enabled = false;
     Edt_Sub52->Enabled = false;
     Edt_Sub54->Enabled = false;
     Edt_Sub53->Enabled = true;
     Edt_Sub53->SetFocus();
     Edt_Sub53->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub54Click(TObject *Sender)
{
 char tempo[64];

     SubField = 3;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub51->Enabled = false;
     Edt_Sub52->Enabled = false;
     Edt_Sub53->Enabled = false;
     Edt_Sub54->Enabled = true;
     Edt_Sub54->SetFocus();
     Edt_Sub54->SelectAll();

     //20161013 Y.Onishi
     /*
     if (KikiType == 1 && ShareFlag == 1) {
        OldChannel = CurrentChannel;
        CurrentChannel = 6;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = false;
        F8Flag = 0;
     }
     */
     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        OldChannel = CurrentChannel;
        //20161123 Y.Onishi
        //本社の天秤取得に対応
        //CurrentChannel = 5;
        if (iKojoKbn == 0){
            CurrentChannel = 6;
        }
        else if (iKojoKbn == 1){
            CurrentChannel = 5;
        }
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = false;
        F8Flag = 0;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub51Change(TObject *Sender)
{
   CurrentChangeFlag = 1;
   AllChangeFlag = 1;
   //2002/11/15 E.Takase コンミ対応
   //円柱の場合
   if (Cur_Kdb1.KEIJKBN == 2) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub52->Value > 0 && Edt_Sub53->Value > 0 && Edt_Sub54->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;

   //コンミの場合
   } else if (Cur_Kdb1.KEIJKBN == 2) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub51->Value > 0 && Edt_Sub52->Value > 0
         && Edt_Sub53->Value > 0 && Edt_Sub54->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;
   //直方体の場合
   } else {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub51->Value > 0 && Edt_Sub52->Value > 0
         && Edt_Sub53->Value > 0 && Edt_Sub54->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub51Enter(TObject *Sender)
{
 int Old_AllChange;
 int Old_SOKUTE_SU;

 if (CurField > 0) {
    Old_AllChange = AllChangeFlag;
    Old_SOKUTE_SU = Cur_Kdb1.SOKUTE_SU;
    Edt_Sub51->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub52->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub53->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub54->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    CurrentChangeFlag = 0;
    AllChangeFlag = Old_AllChange;
    Cur_Kdb1.SOKUTE_SU = Old_SOKUTE_SU;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub51Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub51->Value;
     Botai_Cal();
 }
}
//---------------------------------------------------------------------------
// 母体比重計算
// 直方体： 重量 / （長さ * 幅 * 高さ）
// 円柱： 直径 * 直径 * PI /4 * 高さ
// 2002/11/14 E.Takase
// コンミ： 重量 / ｛（（直径/2）*（直径/2）* PI） - （（内径/2）*（内径/2）* PI）｝* 厚さ
void __fastcall TForm3::Botai_Cal()
{
 char tempo[64];

 //2002/11/15 E.Takase
 // 円柱
 if (Cur_Kdb1.KEIJKBN == 2) {
    if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[CurField-1].SOKUTEI_CH = M_Kdb2[CurField-1].SOKUTEI_MEI4 /
                                  (M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 * pi *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI3/40.0);
       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }
 //コンミ
 } else if (Cur_Kdb1.KEIJKBN == 3) {
    if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {

       if ( M_Kdb2[CurField-1].SOKUTEI_MEI1 == M_Kdb2[CurField-1].SOKUTEI_MEI2 ) {

          M_Kdb2[CurField-1].SOKUTEI_CH = 0;
       } else {

          M_Kdb2[CurField-1].SOKUTEI_CH =  M_Kdb2[CurField-1].SOKUTEI_MEI4/
										((pi*(M_Kdb2[CurField-1].SOKUTEI_MEI2/2.0)
											*(M_Kdb2[CurField-1].SOKUTEI_MEI2/2.0) -
										pi*(M_Kdb2[CurField-1].SOKUTEI_MEI1/2.0)
											*(M_Kdb2[CurField-1].SOKUTEI_MEI1/2.0))
										*M_Kdb2[CurField-1].SOKUTEI_MEI3/1000.0);
          sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
          M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       }
       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }
 //直方体
 } else {
 
    if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF) {

       M_Kdb2[CurField-1].SOKUTEI_CH = M_Kdb2[CurField-1].SOKUTEI_MEI4 /
                                  (M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI3/10.0);
       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }
 
 }
}

//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub52Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub52->Value;
     Botai_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub53Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI3 = Edt_Sub53->Value;
     Botai_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub54Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI4 = Edt_Sub54->Value;
     Botai_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub31Change(TObject *Sender)
{
   CurrentChangeFlag = 1;
   AllChangeFlag = 1;
   if (Cur_Kdb1.SOKUTE_SU < CurField &&
      (Edt_Sub31->Value > 0 || Edt_Sub32->Value > 0))
       Cur_Kdb1.SOKUTE_SU = CurField;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub31Enter(TObject *Sender)
{
 int Old_AllChange;
 int Old_SOKUTE_SU;

 if (CurField > 0) {
    Old_AllChange = AllChangeFlag;
    Old_SOKUTE_SU = Cur_Kdb1.SOKUTE_SU;

    Edt_Sub31->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub32->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;

    SubField = 0;
    CurrentChangeFlag = 0;
    AllChangeFlag = Old_AllChange;
    Cur_Kdb1.SOKUTE_SU = Old_SOKUTE_SU;

    // 電流の規格チェック
    if (Edt_Sub32->Value > COM_DIFF && ( Edt_Sub32->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
       Edt_Sub32->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) 
       Edt_Sub32->Font->Color = clRed;
    else
       Edt_Sub32->Font->Color = clWindowText;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub31Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub31->Value;
     Lead_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub32Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub32->Value;
     Lead_Cal();
 }
}
//---------------------------------------------------------------------------
// リード線取付抵抗計算
// 電圧/ 電流
void __fastcall TForm3::Lead_Cal()
{
 char tempo[64];

 if (CurrentChangeFlag) {
    M_Kdb2[CurField-1].SOKUTEI_CH = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
    M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);
    T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
    Toukei();
    if (M_Kdb2[CurField-1].SOKUTEI_CH > COM_DIFF)
       FieldColor(CurField-1,1,0);
 }
 //if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
 //    M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF) {
 //
 //   M_Kdb2[CurField-1].SOKUTEI_CH = M_Kdb2[CurField-1].SOKUTEI_MEI1 /
 //                                 M_Kdb2[CurField-1].SOKUTEI_MEI2;
 //
 //   sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
 //   M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);
 //
 //   T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
 //   if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
 //      Toukei();
 //      FieldColor(CurField-1,1,0);
 //   }
 //} else {
 //   T_Edit[CurField-1]->Text = 0;
 //   Toukei();
 //}
}

void __fastcall TForm3::Edt_Sub32Enter(TObject *Sender)
{
 if (CurField > 0) {
    CurrentChangeFlag = 0;
    Edt_Sub31->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub32->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;

    SubField = 1;

    // 電流の規格チェック
    if (Edt_Sub32->Value > COM_DIFF && ( Edt_Sub32->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
       Edt_Sub32->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
       Edt_Sub32->Font->Color = clRed;
    } else
       Edt_Sub32->Font->Color = clWindowText;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub71Change(TObject *Sender)
{
   CurrentChangeFlag = 1;
   AllChangeFlag = 1;

   //2002/11/15 E.Takase コンミ対応
   //円柱の場合
   if (Cur_Kdb1.KEIJKBN == 2) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub72->Value > 0 && Edt_Sub73->Value > 0 &&
          Edt_Sub74->Value > 0 && Edt_Sub75->Value > 0 &&
          Edt_Sub76->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;
   //コンミの場合
   } else if (Cur_Kdb1.KEIJKBN == 3) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub71->Value > 0 && Edt_Sub73->Value > 0 &&
          Edt_Sub74->Value > 0 && Edt_Sub75->Value > 0 &&
          Edt_Sub76->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;
   //直方体の場合
   } else {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub71->Value > 0 && Edt_Sub72->Value > 0
         && Edt_Sub73->Value > 0 && Edt_Sub74->Value > 0 &&
         Edt_Sub75->Value > 0 && Edt_Sub76->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;
   }


}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub71Enter(TObject *Sender)
{
 int Old_AllChange;
 int Old_SOKUTE_SU;

 if (CurField > 0) {
    Old_AllChange = AllChangeFlag;
    Old_SOKUTE_SU = Cur_Kdb1.SOKUTE_SU;

    Edt_Sub71->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub72->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub73->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub74->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub76->Text = M_Kdb2[CurField-1].SOKUTEI_MEI6;
    Pan_Sub73->Caption = M_Kdb2[CurField-1].SOKUTEI_MEI7;

    CurrentChangeFlag = 0;
    AllChangeFlag = Old_AllChange;
    Cur_Kdb1.SOKUTE_SU = Old_SOKUTE_SU;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub71Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub71->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

// 固有抵抗率計算
// 直方体：(厚さ * 幅 * 平均電圧 * 1000) / (平均電流 * プローブ)
// 円柱：（平均電圧 * 半径 * 半径 * PI * 1000) / (平均電流 * プローブ)
// 2002/11/14 E.Takase
// コンミ： 平均電圧
void __fastcall TForm3::Teikou_Cal()
{
 char tempo[64];

 //円柱
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[CurField-1].SOKUTEI_CH = (M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 * pi/4 * 1000.0 *
                                  (M_Kdb2[CurField-1].SOKUTEI_MEI3 +
                                   M_Kdb2[CurField-1].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[CurField-1].SOKUTEI_MEI4 +
                                   M_Kdb2[CurField-1].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (Edt_Sub74->Focused()) {
          if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub74->Font->Color = clRed;
          } else
             Edt_Sub74->Font->Color = clWindowText;
       }

       if (Edt_Sub76->Focused()) {
          if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub76->Font->Color = clRed;
          } else
             Edt_Sub76->Font->Color = clWindowText;
       }
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }

 //コンミ
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF ) {

       M_Kdb2[CurField-1].SOKUTEI_CH = (M_Kdb2[CurField-1].SOKUTEI_MEI3 + M_Kdb2[CurField-1].SOKUTEI_MEI5) / 2.0 ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (Edt_Sub74->Focused()) {
          if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub74->Font->Color = clRed;
          } else
             Edt_Sub74->Font->Color = clWindowText;
       }

       if (Edt_Sub76->Focused()) {
          if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub76->Font->Color = clRed;
          } else
             Edt_Sub76->Font->Color = clWindowText;
       }
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }

 } else {
 //直方体
    if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI4 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI5 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI6 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI7 > COM_DIFF ) {

       M_Kdb2[CurField-1].SOKUTEI_CH = (M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 * 1000.0 *
                                  (M_Kdb2[CurField-1].SOKUTEI_MEI3 +
                                   M_Kdb2[CurField-1].SOKUTEI_MEI5)/2.0) /
                                   ((M_Kdb2[CurField-1].SOKUTEI_MEI4 +
                                   M_Kdb2[CurField-1].SOKUTEI_MEI6)/2.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI7/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (Edt_Sub74->Focused()) {
          if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub74->Font->Color = clRed;
          } else
             Edt_Sub74->Font->Color = clWindowText;
       }

       if (Edt_Sub76->Focused()) {
          if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
             Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
             Beep();
             Edt_Sub76->Font->Color = clRed;
          } else
             Edt_Sub76->Font->Color = clWindowText;
       }
       if (RSInputFlag) {
          MdPlayer->FileName = "RSInput.wav";
          MdPlayer->Open();
          MdPlayer->Play();
          RSInputFlag = 0;
       }
       Toukei();
    }

 }

}

void __fastcall TForm3::Edt_Sub72Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub72->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub73Enter(TObject *Sender)
{
 if (CurField > 0) {
    if (!Edt_Sub73->Enabled) {
       Edt_Sub73->Enabled = true;
       Edt_Sub74->Enabled = true;
    }
    CurrentChangeFlag = 0;
    Edt_Sub71->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub72->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub73->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub74->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub76->Text = M_Kdb2[CurField-1].SOKUTEI_MEI6;

    Edt_Sub73->Font->Color = clWindowText;
    Edt_Sub75->Font->Color = clWindowText;
    
    SubField1 = 0;
    SubField = 2;

    // 電流の規格チェック
    if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
        Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
        Edt_Sub74->Font->Color = clRed;
    } else
        Edt_Sub74->Font->Color = clWindowText;

    if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
        Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
        Edt_Sub76->Font->Color = clRed;
    else
        Edt_Sub76->Font->Color = clWindowText;


    //2003/02/21 E.Takase // コンミ以外の場合チェックする 2002/11/15 E.Takase
    // 抵抗率＆コンミの場合電圧をチェックする 2002/12/03 E.Takase
    //2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
    //2003/02/21 E.Takase
    //2003/02/21 E.Takase     if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
    //2003/02/21 E.Takase         Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
    //2003/02/21 E.Takase         Edt_Sub74->Font->Color = clRed;
    //2003/02/21 E.Takase     } else
    //2003/02/21 E.Takase         Edt_Sub74->Font->Color = clWindowText;
    //2003/02/21 E.Takase
    //2003/02/21 E.Takase     if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
    //2003/02/21 E.Takase         Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
    //2003/02/21 E.Takase         Edt_Sub76->Font->Color = clRed;
    //2003/02/21 E.Takase     else
    //2003/02/21 E.Takase         Edt_Sub76->Font->Color = clWindowText;
    //2003/02/21 E.Takase } else {
        //2003/02/21 E.Takase Edt_Sub74->Font->Color = clWindowText;
        //2003/02/21 E.Takase Edt_Sub76->Font->Color = clWindowText;

    if (Cur_Kdb1.KEIJKBN == 3 ) {   //2003/02/21 E.Takase
        //電圧 チェック
        if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
            if (Edt_Sub73->Value > COM_DIFF && ( Edt_Sub73->Value > Cur_Kdb1.HIST_MAX ||
                Edt_Sub73->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                Edt_Sub73->Font->Color = clRed;
            } else {
                Edt_Sub73->Font->Color = clWindowText;
            }
            if (Edt_Sub75->Value > COM_DIFF && ( Edt_Sub75->Value > Cur_Kdb1.HIST_MAX ||
                Edt_Sub75->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                Edt_Sub75->Font->Color = clRed;
            } else {
                Edt_Sub75->Font->Color = clWindowText;
            }
        }


    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub74Enter(TObject *Sender)
{
 if (CurField > 0) {
    if (!Edt_Sub74->Enabled) {
       Edt_Sub73->Enabled = true;
       Edt_Sub74->Enabled = true;
    }
    CurrentChangeFlag = 0;
    Edt_Sub71->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub72->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub73->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub74->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub76->Text = M_Kdb2[CurField-1].SOKUTEI_MEI6;

    Edt_Sub73->Font->Color = clWindowText;
    Edt_Sub75->Font->Color = clWindowText;
    
    SubField1 = 1;
    SubField = 2;
    
    // 電流の規格チェック
	if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	   Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
	   Beep();
	   Edt_Sub74->Font->Color = clRed;
	} else
	   Edt_Sub74->Font->Color = clWindowText;

	if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	   Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	   Edt_Sub76->Font->Color = clRed;
	else
	   Edt_Sub76->Font->Color = clWindowText;

	//2003/02/21 E.Takase // コンミ以外の場合チェックする 2002/11/15 E.Takase
    //2003/02/21 E.Takase // 抵抗率＆コンミの場合電圧をチェックする 2002/12/03 E.Takase
	//2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
	//2003/02/21 E.Takase     // 電流の規格チェック
	//2003/02/21 E.Takase     if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag) {
	//2003/02/21 E.Takase        Beep();
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clRed;
	//2003/02/21 E.Takase     } else
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;
    //2003/02/21 E.Takase
	//2003/02/21 E.Takase     if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clRed;
	//2003/02/21 E.Takase     else
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
	//2003/02/21 E.Takase } else {
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;
    if (Cur_Kdb1.KEIJKBN == 3 ) {   //2003/02/21 E.Takase
           //電圧 チェック
           if ( Cur_Kdb1.KENSA_KMK == 7  && Cur_Kdb1.KEIJKBN == 3 ) {
               if (Edt_Sub73->Value > COM_DIFF && ( Edt_Sub73->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub73->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub73->Font->Color = clRed;
               } else {
                   Edt_Sub73->Font->Color = clWindowText;
               }
               if (Edt_Sub75->Value > COM_DIFF && ( Edt_Sub75->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub75->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub75->Font->Color = clRed;
               } else {
                   Edt_Sub75->Font->Color = clWindowText;
            }
        }
	}



 }


}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub73Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI3 = Edt_Sub73->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub74Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI4 = Edt_Sub74->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub75Enter(TObject *Sender)
{
 if (CurField > 0) {
    if (!Edt_Sub75->Enabled) {
       Edt_Sub75->Enabled = true;
       Edt_Sub76->Enabled = true;
    }
    CurrentChangeFlag = 0;
    Edt_Sub71->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub72->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub73->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub74->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub76->Text = M_Kdb2[CurField-1].SOKUTEI_MEI6;

    Edt_Sub73->Font->Color = clWindowText;
    Edt_Sub75->Font->Color = clWindowText;
    
    SubField1 = 0;
    SubField = 3;
    
	    // 電流の規格チェック
	    if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	       Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	       Edt_Sub76->Font->Color = clRed;
	    else
	       Edt_Sub76->Font->Color = clWindowText;

	    if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	       Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	       Edt_Sub74->Font->Color = clRed;
	    else
	       Edt_Sub74->Font->Color = clWindowText;

	//2003/02/21 E.Takase // コンミ以外の場合チェックする 2002/11/15 E.Takase
    //2003/02/21 E.Takase // 抵抗率＆コンミの場合電圧をチェックする 2002/12/03 E.Takase
	//2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
	//2003/02/21 E.Takase     // 電流の規格チェック
	//2003/02/21 E.Takase     if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clRed;
	//2003/02/21 E.Takase     else
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
    //2003/02/21 E.Takase
	//2003/02/21 E.Takase     if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clRed;
	//2003/02/21 E.Takase     else
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;
    //2003/02/21 E.Takase
	//2003/02/21 E.Takase } else {
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;


    if (Cur_Kdb1.KEIJKBN == 3 ) {   //2003/02/21 E.Takase
           //電圧 チェック
           if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
              if (Edt_Sub73->Value > COM_DIFF && ( Edt_Sub73->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub73->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub73->Font->Color = clRed;
               } else {
                   Edt_Sub73->Font->Color = clWindowText;
               }
               if (Edt_Sub75->Value > COM_DIFF && ( Edt_Sub75->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub75->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub75->Font->Color = clRed;
               } else {
                   Edt_Sub75->Font->Color = clWindowText;
               }
           }

	}
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub75Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI5 = Edt_Sub75->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub76Enter(TObject *Sender)
{
 if (CurField > 0) {
    if (!Edt_Sub76->Enabled) {
       Edt_Sub75->Enabled = true;
       Edt_Sub76->Enabled = true;
    }
    CurrentChangeFlag = 0;
    Edt_Sub71->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub72->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub73->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Edt_Sub74->Text = M_Kdb2[CurField-1].SOKUTEI_MEI4;
    Edt_Sub75->Text = M_Kdb2[CurField-1].SOKUTEI_MEI5;
    Edt_Sub76->Text = M_Kdb2[CurField-1].SOKUTEI_MEI6;

    Edt_Sub73->Font->Color = clWindowText;
    Edt_Sub75->Font->Color = clWindowText;
    
    SubField1 = 1;
    SubField = 3;

    // 電流の規格チェック
	if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	   Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	   Edt_Sub76->Font->Color = clRed;
	else
	   Edt_Sub76->Font->Color = clWindowText;

    if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	   Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	   Edt_Sub74->Font->Color = clRed;
	else
	   Edt_Sub74->Font->Color = clWindowText;

	//2003/02/21 E.Takase // コンミ以外の場合チェックする 2002/11/15 E.Takase
    //2003/02/21 E.Takase // 抵抗率＆コンミの場合電圧をチェックする 2002/12/03 E.Takase
	//2003/02/21 E.Takase if (Cur_Kdb1.KEIJKBN != 3 ) {
    //2003/02/21 E.Takase
	//2003/02/21 E.Takase     // 電流の規格チェック
	//2003/02/21 E.Takase     if (Edt_Sub76->Value > COM_DIFF && ( Edt_Sub76->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub76->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clRed;
	//2003/02/21 E.Takase     else
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
    //2003/02/21 E.Takase
	//2003/02/21 E.Takase     if (Edt_Sub74->Value > COM_DIFF && ( Edt_Sub74->Value > Cur_Kdb1.JYOKEN1 * 1.1 ||
	//2003/02/21 E.Takase        Edt_Sub74->Value < Cur_Kdb1.JYOKEN1 * 0.9) && F10Flag)
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clRed;
	//2003/02/21 E.Takase     else
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;
	//2003/02/21 E.Takase } else {
	//2003/02/21 E.Takase        Edt_Sub76->Font->Color = clWindowText;
	//2003/02/21 E.Takase        Edt_Sub74->Font->Color = clWindowText;

    if (Cur_Kdb1.KEIJKBN == 3 ) { //2003/02/21 E.Takase
           //電圧 チェック
           if ( Cur_Kdb1.KENSA_KMK == 7 && Cur_Kdb1.KEIJKBN == 3 ) {
               if (Edt_Sub73->Value > COM_DIFF && ( Edt_Sub73->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub73->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub73->Font->Color = clRed;
               } else {
                   Edt_Sub73->Font->Color = clWindowText;
               }
               if (Edt_Sub75->Value > COM_DIFF && ( Edt_Sub75->Value > Cur_Kdb1.HIST_MAX ||
                   Edt_Sub75->Value < Cur_Kdb1.HIST_MIN) && F10Flag) {
                   Edt_Sub75->Font->Color = clRed;
               } else {
                   Edt_Sub75->Font->Color = clWindowText;
            }
        }
	}


 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub76Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI6 = Edt_Sub76->Value;
     Teikou_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub71Click(TObject *Sender)
{
 char tempo[64];

     SubField = 0;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub72->Enabled = false;
     Edt_Sub73->Enabled = false;
     Edt_Sub74->Enabled = false;
     Edt_Sub75->Enabled = false;
     Edt_Sub76->Enabled = false;
     Edt_Sub71->Enabled = true;
     Edt_Sub71->SetFocus();
     Edt_Sub71->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub72Click(TObject *Sender)
{
 char tempo[64];

     SubField = 1;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub71->Enabled = false;
     Edt_Sub73->Enabled = false;
     Edt_Sub74->Enabled = false;
     Edt_Sub75->Enabled = false;
     Edt_Sub76->Enabled = false;
     Edt_Sub72->Enabled = true;
     Edt_Sub72->SetFocus();
     Edt_Sub72->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}

//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub73Click(TObject *Sender)
{
 char tempo[64];

     SubField = 2;
     SubField1 = 0;

     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub72->Enabled = false;
     Edt_Sub73->Enabled = true;
     Edt_Sub74->Enabled = true;
     Edt_Sub75->Enabled = true;
     Edt_Sub76->Enabled = true;
     Edt_Sub71->Enabled = false;
     Edt_Sub73->SetFocus();
     Edt_Sub73->SelectAll();

     if ((KikiType == 3 || KikiType == 4) && ShareFlag == 1) {
        OldChannel = CurrentChannel;
        CurrentChannel = 9;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
     }
     Button8->Enabled = false;
     F8Flag = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub74Click(TObject *Sender)
{
 char tempo[64];

     SubField = 3;
     SubField1 = 0;

     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub72->Enabled = false;
     Edt_Sub73->Enabled = true;
     Edt_Sub74->Enabled = true;
     Edt_Sub75->Enabled = true;
     Edt_Sub76->Enabled = true;
     Edt_Sub71->Enabled = false;
     Edt_Sub75->SetFocus();
     Edt_Sub75->SelectAll();

     if ((KikiType == 3 || KikiType == 4) && ShareFlag == 1) {
        OldChannel = CurrentChannel;
        CurrentChannel = 9;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
     }
     Button8->Enabled = false;
     F8Flag = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub81Click(TObject *Sender)
{
 char tempo[64];

     SubField = 0;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub82->Enabled = false;
     Edt_Sub83->Enabled = false;
     Edt_Sub81->Enabled = true;
     Edt_Sub81->SetFocus();
     Edt_Sub81->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub82Click(TObject *Sender)
{
 char tempo[64];

     SubField = 1;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub81->Enabled = false;
     Edt_Sub83->Enabled = false;
     Edt_Sub82->Enabled = true;
     Edt_Sub82->SetFocus();
     Edt_Sub82->SelectAll();

     if ((KikiType == 1 || KikiType == 2) && ShareFlag == 1) {
        CurrentChannel = OldChannel;
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
        Button8->Enabled = true;
        F8Flag = 1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Radio_Sub83Click(TObject *Sender)
{
 char tempo[64];

     SubField = 2;
     // (CurField > 1) {
     // T_Edit[0]->SetFocus();
     //
     Edt_Sub81->Enabled = false;
     Edt_Sub82->Enabled = false;
     Edt_Sub83->Enabled = true;
     Edt_Sub83->SetFocus();
     Edt_Sub83->SelectAll();

     //2009.03.13 MTS E.Takase [001]  ↓
     //材料試験機（単独使用）は機器タイプを5とする
     //if ((KikiType == 3 || KikiType == 4)  && ShareFlag == 1) {
     if ((KikiType == 5)  && ShareFlag == 1) {
     //2009.03.13 MTS E.Takase [001]  ↑
        OldChannel = CurrentChannel;
        //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↓
        //CurrentChannel = 7;
        CurrentChannel = 10;
        //2009.03.04 E.Takase 材料試験機のチャンネル番号変更（CurrentChannel=7→10）↑
        sprintf(tempo, "CONNECT %d", CurrentChannel);
        SharedMemory_Write(1, 0, tempo, strlen(tempo));
     }
     Button8->Enabled = false;
     F8Flag = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub81Change(TObject *Sender)
{
   CurrentChangeFlag = 1;
   AllChangeFlag = 1;

//   if (Cur_Kdb1.KEIJKBN == 1) {      // 直方体
//      if (Cur_Kdb1.SOKUTE_SU < CurField &&
//         (Edt_Sub81->Value > 0 && Edt_Sub82->Value > 0
//         && Edt_Sub83->Value > 0))
//         Cur_Kdb1.SOKUTE_SU = CurField;
//   } else { // 円柱
//      if (Cur_Kdb1.SOKUTE_SU < CurField &&
//         (Edt_Sub82->Value > 0 && Edt_Sub83->Value > 0))
//         Cur_Kdb1.SOKUTE_SU = CurField;
//   }

   //2002/11/15 E.Takase コンミ対応
   //円柱の場合
   if (Cur_Kdb1.KEIJKBN == 2) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub82->Value > 0 && Edt_Sub83->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;

   //コンミの場合
   } else if (Cur_Kdb1.KEIJKBN == 3) {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub81->Value > 0 && Edt_Sub83->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;


   //直方体の場合
   } else {
      if (Cur_Kdb1.SOKUTE_SU < CurField &&
         (Edt_Sub81->Value > 0 && Edt_Sub82->Value > 0
         && Edt_Sub83->Value > 0))
         Cur_Kdb1.SOKUTE_SU = CurField;

   }



}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub81Enter(TObject *Sender)
{
 int Old_AllChange;
 int Old_SOKUTE_SU;

 if (CurField > 0) {
    Old_AllChange = AllChangeFlag;
    Old_SOKUTE_SU = Cur_Kdb1.SOKUTE_SU;

    Edt_Sub81->Text = M_Kdb2[CurField-1].SOKUTEI_MEI1;
    Edt_Sub82->Text = M_Kdb2[CurField-1].SOKUTEI_MEI2;
    Edt_Sub83->Text = M_Kdb2[CurField-1].SOKUTEI_MEI3;
    Pan_Sub82->Caption = M_Kdb2[CurField-1].SOKUTEI_MEI4;

    AllChangeFlag = Old_AllChange;
    Cur_Kdb1.SOKUTE_SU = Old_SOKUTE_SU;
    CurrentChangeFlag = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub81Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI1 = Edt_Sub81->Value;
     Kousetu_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub82Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI2 = Edt_Sub82->Value;
     Kousetu_Cal();
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Edt_Sub83Exit(TObject *Sender)
{
 if (CurField > 0 && CurrentChangeFlag) {
     EndErrorFlag = 0;
     M_Kdb2[CurField-1].SOKUTEI_MEI3 = Edt_Sub83->Value;
     Kousetu_Cal();
 }
}
//---------------------------------------------------------------------------

// 抗折力計算
// 直方体：N/(cm * cm): (300 * 負荷 * スパン) / ( 2 * 幅 * 厚さ * 厚さ）
//         MPa: (3 * スパン * 負荷) / (2 * 幅 * 厚さ * 厚さ）
// 円柱：  N/(cm * cm): (8 * 負荷 * スパン) / ( 100 * PI * 直径 * 直径 * 直径）
//         MPa: (8 * スパン * 負荷) / (PI * 直径 * 直径 * 直径）
// 2002/11/14
// コンミ ： 負荷
void __fastcall TForm3::Kousetu_Cal()
{
 char tempo[64];

 //円柱
 if (Cur_Kdb1.KEIJKBN == 2 ) {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[CurField-1].SOKUTEI_CH = (8.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4/10.0) /
                                   ( 100.0 * M_Kdb2[CurField-1].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
          M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

          T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
          if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
             Toukei();
             FieldColor(CurField-1,1,0);
          }
       } else {
          T_Edit[CurField-1]->Text = 0;
          Toukei();
       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2")  {
       if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[CurField-1].SOKUTEI_CH = (8.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4) /
                                   ( M_Kdb2[CurField-1].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2) ;

          sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
          M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

          T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
          if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
             Toukei();
             FieldColor(CurField-1,1,0);
          }
       } else {
          T_Edit[CurField-1]->Text = 0;
          Toukei();
       }
       return;
    }

    // N/(cm * cm) or Kfg
    if (M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[CurField-1].SOKUTEI_CH = (8.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4/10.0) /
                                   ( M_Kdb2[CurField-1].SOKUTEI_MEI2 * pi *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       Toukei();
    }

 //コンミ
 } else if ( Cur_Kdb1.KEIJKBN == 3 ) {
    if (M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[CurField-1].SOKUTEI_CH = M_Kdb2[CurField-1].SOKUTEI_MEI3 ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       if (RSInputFlag) {
           MdPlayer->FileName = "RSInput.wav";
           MdPlayer->Open();
           MdPlayer->Play();
           RSInputFlag = 0;
       }
       Toukei();
    }
    return;

 //直方体
 } else {
    if (Cur_Kdb1.TANI == "MPa") {
       if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[CurField-1].SOKUTEI_CH = (3.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4/10.0) /
                                   ( 200.0 * M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0) ;

          sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
          M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

          T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
          if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
             Toukei();
             FieldColor(CurField-1,1,0);
          }
       } else {
          T_Edit[CurField-1]->Text = 0;
          if (RSInputFlag) {
              MdPlayer->FileName = "RSInput.wav";
              MdPlayer->Open();
              MdPlayer->Play();
              RSInputFlag = 0;
          }
          Toukei();
       }
       return;
    }

    if (Cur_Kdb1.TANI == "N/mm2" )  {
       if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
          M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

          M_Kdb2[CurField-1].SOKUTEI_CH = (3.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4) /
                                   ( 2.0 * M_Kdb2[CurField-1].SOKUTEI_MEI2 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1) ;

          sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
          M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

          T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
          if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
             Toukei();
             FieldColor(CurField-1,1,0);
          }
       } else {
          T_Edit[CurField-1]->Text = 0;
          if (RSInputFlag) {
             MdPlayer->FileName = "RSInput.wav";
             MdPlayer->Open();
             MdPlayer->Play();
             RSInputFlag = 0;
          }
          Toukei();
       }
       return;
    }

    // N/(cm * cm)  or Kfg
    if (M_Kdb2[CurField-1].SOKUTEI_MEI1 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI2 > COM_DIFF &&
       M_Kdb2[CurField-1].SOKUTEI_MEI3 > COM_DIFF) {

       M_Kdb2[CurField-1].SOKUTEI_CH = (3.0 * M_Kdb2[CurField-1].SOKUTEI_MEI3 *
                                  M_Kdb2[CurField-1].SOKUTEI_MEI4/10.0) /
                                   ( 2.0 * M_Kdb2[CurField-1].SOKUTEI_MEI2/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0 *
                                   M_Kdb2[CurField-1].SOKUTEI_MEI1/10.0) ;

       sprintf(tempo, "%.3f", M_Kdb2[CurField-1].SOKUTEI_CH);
       M_Kdb2[CurField-1].SOKUTEI_CH = atof(tempo);

       T_Edit[CurField-1]->Text = M_Kdb2[CurField-1].SOKUTEI_CH;
       if (CurrentChangeFlag == 1 && CurField <= Cur_Kdb1.SOKUTE_SU) {
          Toukei();
          FieldColor(CurField-1,1,0);
       }
    } else {
       T_Edit[CurField-1]->Text = 0;
       Toukei();
    }
    return;
 }


}

void __fastcall TForm3::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 int button;
 char tempo[64];

   if (CurField > 0)
      T_Edit[CurField-1]->Color = clWindow;

   if (AllChangeFlag == 1 ){  // Updated ?
      button = MessageDlg( MSG_10.c_str(), mtConfirmation, mbYesNoCancel, 0);
      if (button == mrCancel){
         return;
      } else {  // YES or No
         if (button == mrNo) {
            if (ShareFlag) {
               sprintf(tempo, "CLOSE");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               sprintf(tempo, "EXIT");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               SharedMemory_Close(1);
               SharedMemory_Close(2);
            }
            AllChangeFlag = 0;
            Close();
            return;
         } else{  // Yes
            Button11Click(Sender);
            if (ShareFlag) {
               sprintf(tempo, "CLOSE");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               sprintf(tempo, "EXIT");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               SharedMemory_Close(1);
               SharedMemory_Close(2);
            }
            AllChangeFlag = 0;
            Close();
            return ;
         }
      }
   } else {
     if (ShareFlag) {
        sprintf(tempo, "CLOSE");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));

        sprintf(tempo, "EXIT");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));

        SharedMemory_Close(1);
        SharedMemory_Close(2);
     }
     Close();
   }        
}
//---------------------------------------------------------------------------

//ステータスメッセージの表示
void StatBarClear( AnsiString sMsg, int Opt )
{
     // ステータスメッセージ
     if (Opt == 1 && F10Flag) {
        Beep();
        Form3->StatusBar1->Font->Color = clRed;
     } else
        Form3->StatusBar1->Font->Color = clWindowText;

     Form3->StatusBar1->SimpleText =  sMsg;

     Form3->StatusBar1->Update();
}

// 文字列中でNULL、Space以外の文字が入っているかどうか
int IsNullSpace( AnsiString  str )
{
   char sBuf[256];
   int i, iRtn;

   iRtn = 1;

   sBuf[0] = NULL ;
   strcpy( sBuf,str.c_str());

   for( i=0; i<str.Length(); i++ ){
      if( sBuf[i] != NULL && sBuf[i] != ' ' ){
         iRtn = 0 ;
         break ;
       }
   }

   return iRtn;

}
// 小数点桁数を変更
void __fastcall TForm3::Button1Click(TObject *Sender)
{
 int OldField;

 if (Cur_Kdb1.KENSA_KMK == 6 || Cur_Kdb1.KENSA_KMK == 3 ||
    Cur_Kdb1.KENSA_KMK == 4 || Cur_Kdb1.KENSA_KMK == 11 ||
    Cur_Kdb1.KENSA_KMK == 8 || Cur_Kdb1.KENSA_KMK == 9 ||
    Cur_Kdb1.KENSA_KMK == 7 || Cur_Kdb1.KENSA_KMK == 12 )
    return;

 Edt_001Exit(Sender);

 // 現在のFocus番号を保存
 OldField = CurField;

 // 桁数を変わる
 for (int i = 0; i < Nums; i++) {
     if (T_Edit[i]->FPos == 3)
          T_Edit[i]->FPos = 2;
     else
          T_Edit[i]->FPos = 3;
     T_Edit[i]->Text = M_Kdb2[i].SOKUTEI_CH;
 }

 switch (InputMode) {
 case 4:  // 母体比重
    if (T_Edit[0]->FPos == 3) {
       Edt_Sub51->FPos = 3;
       Edt_Sub52->FPos = 3;
       Edt_Sub53->FPos = 3;
       Edt_Sub54->FPos = 3;
    } else {
       Edt_Sub51->FPos = 2;
       Edt_Sub52->FPos = 2;
       Edt_Sub53->FPos = 2;
       Edt_Sub54->FPos = 2;
    }
    break;
 case 3:  // リード線取付抵抗
    if (T_Edit[0]->FPos == 3) {
       Edt_Sub31->FPos = 3;
       Edt_Sub32->FPos = 3;
    } else {
       Edt_Sub31->FPos = 2;
       Edt_Sub32->FPos = 2;
    }
    break;
 case 5:  // 固有抵抗率
    if (T_Edit[0]->FPos == 3) {
       Edt_Sub71->FPos = 3;
       Edt_Sub72->FPos = 3;
       Edt_Sub73->FPos = 3;
       Edt_Sub74->FPos = 3;
       Edt_Sub75->FPos = 3;
       Edt_Sub76->FPos = 3;
    } else {
       Edt_Sub71->FPos = 2;
       Edt_Sub72->FPos = 2;
       Edt_Sub73->FPos = 2;
       Edt_Sub74->FPos = 2;
       Edt_Sub75->FPos = 2;
       Edt_Sub76->FPos = 2;
    }
    break;
 case 6:  // 抗折力
    if (T_Edit[0]->FPos == 3) {
       Edt_Sub81->FPos = 3;
       Edt_Sub82->FPos = 3;
       Edt_Sub83->FPos = 3;
    } else {
       Edt_Sub81->FPos = 2;
       Edt_Sub82->FPos = 2;
       Edt_Sub83->FPos = 2;
    }
    break;
 }

 // Buttonのタイトルを変わる
 if (T_Edit[0]->FPos == 3) {
    Cur_Kdb1.SOKUTE_KET = 3;
    Button1->Caption = "1/1000";
 } else {
    Button1->Caption = "1/100";
    Cur_Kdb1.SOKUTE_KET = 2;
 }

 // Focus番号を回復
 CurField = OldField;
 CurrentChangeFlag = 0;

 // Set Focus
 if (CurField > 0) {
    T_Edit[CurField-1]->SetFocus();
    T_Edit[CurField-1]->SelectAll();
 }

 // 統計とグラフ表示
 Toukei();

 AllChangeFlag = 1;

}
//---------------------------------------------------------------------------
// 保存
void __fastcall TForm3::Button11Click(TObject *Sender)
{
 AnsiString str, UPDYMD, UPDTIM;
 char str_c[2048];

 Edt_001Exit(Sender);

 if (AllChangeFlag == 0) {
    if (Button11->Font->Color == clRed)
       Button12->SetFocus();
    return;
 }

 // ステータスメッセージ
 StatBarClear(MSG_04, 0) ;

 WriteDatabaseError = 0;

 // データベースのデータ範囲をチェック (Kdb1)
 if (Cur_Kdb1.HIST_SOKUT > 999)
    Cur_Kdb1.HIST_SOKUT = 999;
 if (Cur_Kdb1.HIST_SOKUT < 0)
    Cur_Kdb1.HIST_SOKUT = 0;

 if (Cur_Kdb1.SOKUTE_SU > Cur_Kdb1.HIST_SOKUT)
    Cur_Kdb1.SOKUTE_SU = Cur_Kdb1.HIST_SOKUT;

 //2003/01/06 E.Takase
 //if (fabs(Cur_Kdb1.SOKUTE_AVE) > 9999.9999)
 //   Cur_Kdb1.SOKUTE_AVE = 9999.9999;
 if (fabs(Cur_Kdb1.SOKUTE_AVE) > 999999.9999)
    Cur_Kdb1.SOKUTE_AVE = 999999.9999;

 if (fabs(Cur_Kdb1.SOKUTE_MIN) > 999999.999)
    Cur_Kdb1.SOKUTE_MIN = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_MAX) > 999999.999)
    Cur_Kdb1.SOKUTE_MAX = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_R) > 999999.999)
    Cur_Kdb1.SOKUTE_R = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_SGM) > 9999.99999)
    Cur_Kdb1.SOKUTE_SGM = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_CP) > 9999.99999)
    Cur_Kdb1.SOKUTE_CP = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_CPK) > 9999.99999)
    Cur_Kdb1.SOKUTE_CPK = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_K) > 9999.99999)
    Cur_Kdb1.SOKUTE_K = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_P) > 9999.99999)
    Cur_Kdb1.SOKUTE_P = 9999.99999;

 // Update Date & Time
 //UPDYMD = FormatDateTime("yyyymmdd",Date());
 //UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
 if (IsNullSpace( Cur_Kdb1.ADDYMD )){
     Cur_Kdb1.ADDYMD = FormatDateTime("yyyymmdd",Date());
     Cur_Kdb1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

     //更新回数
     Cur_Kdb1.UPDCNT = 0;
 } else {
     // 変更日、変更時間
     Cur_Kdb1.UPDYMD = FormatDateTime("yyyymmdd",Date());
     Cur_Kdb1.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

     //更新回数
     Cur_Kdb1.UPDCNT += 1;
 }

 // Save 計測データ
 // Update KDA1
 Form1->Query_Kdb1->Close();
 Form1->Query_Kdb1->SQL->Clear();
 if( Form1->Database1->InTransaction == false ){
     Form1->Database1->StartTransaction();
 }

 sprintf(str_c, "update KDB1 set HIST_SOKUT=%d, SOKUTE_SU=%d, SOKUTE_AVE=%8.4f, SOKUTE_KET=%d, ",
                        Cur_Kdb1.HIST_SOKUT, Cur_Kdb1.SOKUTE_SU, Cur_Kdb1.SOKUTE_AVE, Cur_Kdb1.SOKUTE_KET);
 //sprintf(str_c, "update KDB1 set HIST_SOKUT=%d, SOKUTE_SU=%d, SOKUTE_AVE=%8.4f, ",
 //                       Cur_Kdb1.HIST_SOKUT, Cur_Kdb1.SOKUTE_SU, Cur_Kdb1.SOKUTE_AVE);
 str = str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_MIN=%9.3f, SOKUTE_MAX=%9.3f, SOKUTE_R=%9.3f,",
                 Cur_Kdb1.SOKUTE_MIN, Cur_Kdb1.SOKUTE_MAX, Cur_Kdb1.SOKUTE_R);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_SGM=%9.5f, SOKUTE_CP=%9.5f, SOKUTE_CPK=%9.5f,",
                 Cur_Kdb1.SOKUTE_SGM, Cur_Kdb1.SOKUTE_CP, Cur_Kdb1.SOKUTE_CPK);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_K=%9.5f, SOKUTE_P=%9.5f, ADDYMD = '%s', ADDTIM = '%s', UPDYMD='%s',",
                 Cur_Kdb1.SOKUTE_K, Cur_Kdb1.SOKUTE_P, Cur_Kdb1.ADDYMD.c_str(),
                 Cur_Kdb1.ADDTIM.c_str(), Cur_Kdb1.UPDYMD.c_str());
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "UPDTIM='%s', UPDCHR=%d, UPDCNT=%d",
               Cur_Kdb1.UPDTIM.c_str(), USER_COD , Cur_Kdb1.UPDCNT);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, " where KENSA_YMD ='%s' and SEQNO =%d and DTKSHIN = '%s' and LOTNO = '%s' and KOJOKBN = %d ",
                        Cur_Kdb1.KENSA_YMD.c_str(),
                        Cur_Kdb1.SEQNO, Cur_Kdb1.DTKSHIN, Cur_Kdb1.LOTNO,
                        iKojoKbn);      //20160701_工場区分追加
 str += str_c ;
 Form1->Query_Kdb1->SQL->Add(str);

 //お問い合せ文の実行
 try
 {
    Form1->Query_Kdb1->ExecSQL();
    Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
 }
 catch(EDatabaseError& e)
 {
    Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
    WriteDatabaseError = 1;
    //goto Err1;
 }

 // Update KDB2
// if (Cur_Kdb1.HIST_SOKUT < Cur_Kdb1.HIST_SOKUT_Ori) {
    // 余分データを削除（SOKUTEI_NO > Cur_Kda1.HIST_SOKUT)
    Form1->Database1->StartTransaction();
    Form1->Query_Kdb2->Close();
    Form1->Query_Kdb2->SQL->Clear();

//    sprintf(str_c, "delete kdb2 where KENSA_YMD = '%s' and SEQNO = %d and SOKUTEI_NO > %d and DTKSHIN = '%s' and LOTNO = '%s'",
//                   Cur_Kdb1.KENSA_YMD.c_str(), Cur_Kdb1.SEQNO, Cur_Kdb1.HIST_SOKUT,
//                   Cur_Kdb1.DTKSHIN, Cur_Kdb1.LOTNO);
    sprintf(str_c, "delete kdb2 where KENSA_YMD = '%s' and SEQNO = %d and DTKSHIN = '%s' and LOTNO = '%s' and KOJOKBN = %d ",
                   Cur_Kdb1.KENSA_YMD.c_str(), Cur_Kdb1.SEQNO, Cur_Kdb1.DTKSHIN, Cur_Kdb1.LOTNO, iKojoKbn);
    str = str_c;
    Form1->Query_Kdb2->SQL->Add(str);

    //お問い合せ文の実行
    try
    {
       Form1->Query_Kdb2->ExecSQL();
       Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
    }
    catch(EDatabaseError& e)
    {
       Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
       WriteDatabaseError = 1;
       //goto Err1;
    }
// }

 // 各計測データを保存する
// for (int i = 0; i < Cur_Kdb1.SOKUTE_SU; i++) {
 for (int i = 0; i < Cur_Kdb1.HIST_SOKUT; i++) {
     // データベースのデータ範囲をチェック (Kdb1)
     if (fabs(M_Kdb2[i].SOKUTEI_CH) > 999999.999)
        M_Kdb2[i].SOKUTEI_CH = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI1) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI1 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI2) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI2 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI3) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI3 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI4) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI4 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI5) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI5 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI6) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI6 = 999999.999;

     if (fabs(M_Kdb2[i].SOKUTEI_MEI7) > 999999.999)
        M_Kdb2[i].SOKUTEI_MEI7 = 999999.999;

     Form1->Database1->StartTransaction();
/*
     if (M_Kdb2[i].DatabaseFlag == 1) {
       // Update
       Form1->Query_Kdb2->Close();
       Form1->Query_Kdb2->SQL->Clear();

       sprintf(str_c, "update KDB2 set SOKUTEI_CH=%9.3f, SOKUTEI_MEI1=%9.3f, SOKUTEI_MEI2=%9.3f, ",
                        M_Kdb2[i].SOKUTEI_CH, M_Kdb2[i].SOKUTEI_MEI1, M_Kdb2[i].SOKUTEI_MEI2);
       str = str_c ;
       str_c[0] = NULL ;

       sprintf(str_c, " SOKUTEI_MEI3=%9.3f, SOKUTEI_MEI4=%9.3f, SOKUTEI_MEI5=%9.3f, SOKUTEI_MEI6=%9.3f, ",
                        M_Kdb2[i].SOKUTEI_MEI3, M_Kdb2[i].SOKUTEI_MEI4, M_Kdb2[i].SOKUTEI_MEI5,
                        M_Kdb2[i].SOKUTEI_MEI6);
       str += str_c;
       str_c[0] = NULL ;

       sprintf(str_c, " SOKUTEI_MEI7=%9.3f where KENSA_YMD = '%s' and SEQNO = %d and SOKUTEI_NO = %d and DTKSHIN = '%s' and LOTNO = '%s'",
                        M_Kdb2[i].SOKUTEI_MEI7, Cur_Kdb1.KENSA_YMD.c_str(), Cur_Kdb1.SEQNO, i+1, Cur_Kdb1.DTKSHIN, Cur_Kdb1.LOTNO);
       str += str_c ;
       Form1->Query_Kdb2->SQL->Add(str);

       //お問い合せ文の実行
       try
       {
          Form1->Query_Kdb2->ExecSQL();
          Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
       }
       catch(EDatabaseError& e)
       {
          Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
          WriteDatabaseError = 1;
          //goto Err1;
       }
    } else {
*/
      // Insert
       Form1->Query_Kdb2->Close();
       Form1->Query_Kdb2->SQL->Clear();

       sprintf(str_c, "%s%s%s", "insert into KDB2 (KENSA_YMD, SEQNO, DTKSHIN, LOTNO, HINBAN, ZISCOD, ZISNAM, SOKUTEI_NO,",
                      " SOKUTEI_CH, SOKUTEI_MEI1, SOKUTEI_MEI2, SOKUTEI_MEI3, SOKUTEI_MEI4, ",
                      " SOKUTEI_MEI5, SOKUTEI_MEI6, SOKUTEI_MEI7, KOJOKBN)");
       str = str_c ;
       str_c[0] = NULL;

       sprintf(str_c, " values('%s', %d, '%s', '%s', '%s', '%s', '%s', %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %d)",
                        Cur_Kdb1.KENSA_YMD.c_str(), Cur_Kdb1.SEQNO,
                        Cur_Kdb1.DTKSHIN.c_str(), Cur_Kdb1.LOTNO.c_str(),
                        Cur_Kdb1.HINBAN.c_str(), Cur_Kdb1.ZISCOD.c_str(),
                        Cur_Kdb1.ZISNAM.c_str(), i+1, M_Kdb2[i].SOKUTEI_CH,
                        M_Kdb2[i].SOKUTEI_MEI1, M_Kdb2[i].SOKUTEI_MEI2,
                        M_Kdb2[i].SOKUTEI_MEI3, M_Kdb2[i].SOKUTEI_MEI4,
                        M_Kdb2[i].SOKUTEI_MEI5, M_Kdb2[i].SOKUTEI_MEI6,
                        M_Kdb2[i].SOKUTEI_MEI7,
                        iKojoKbn);             //20160701_工場区分追加

       str += str_c;
       Form1->Query_Kdb2->SQL->Add(str);

       //お問い合せ文の実行
       try
       {
          Form1->Query_Kdb2->ExecSQL();
          Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
          M_Kdb2[i].DatabaseFlag = 1;
       }
       catch(EDatabaseError& e)
       {
        Form1->Database1->Rollback(); // 成功した場合，変更をコミットする;
        WriteDatabaseError = 1;
        //goto Err1;
       }
    }
// }

 //Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
 StatBarClear(" ", 0) ;

 if (WriteDatabaseError == 0) {
    AllChangeFlag = 0;

    Cur_Kdb1.HIST_SOKUT_Ori = Cur_Kdb1.HIST_SOKUT;
    Cur_Kdb1.SOKUTE_SU_Ori = Cur_Kdb1.SOKUTE_SU;
    if (Button11->Font->Color == clRed)
       Button12->SetFocus();
    return;
 } else {
   //Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
   AllChangeFlag = 1;
   return;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button11Enter(TObject *Sender)
{
 if (ScreenInitFlag == 0)
    Button11->Font->Color = clRed;
 else
    Button11->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button11Exit(TObject *Sender)
{
    Button11->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button12Click(TObject *Sender)
{
 int button;
 char tempo[64];

   if (CurField > 0)
      T_Edit[CurField-1]->Color = clWindow;

   if (AllChangeFlag == 1 ){  // Updated ?
      button = MessageDlg( MSG_10.c_str(), mtConfirmation, mbYesNoCancel, 0);
      if (button == mrCancel){
         return;
      } else {  // YES or No
         if (button == mrNo) {
            if (ShareFlag) {
               sprintf(tempo, "CLOSE");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               sprintf(tempo, "EXIT");
               SharedMemory_Write(1, 0, tempo, strlen(tempo));

               SharedMemory_Close(1);
               SharedMemory_Close(2);
            }
            //「戻る」のとき保存しないで終了にしたとき
            Form1->SOKUTEI_SAVE_FLAG = 0;
            AllChangeFlag = 0;
            Close();
            return;
         } else{  // Yes
            Button11Click(Sender);
            if (WriteDatabaseError == 0) {
               if (ShareFlag) {
                  sprintf(tempo, "CLOSE");
                  SharedMemory_Write(1, 0, tempo, strlen(tempo));

                  sprintf(tempo, "EXIT");
                  SharedMemory_Write(1, 0, tempo, strlen(tempo));

                  SharedMemory_Close(1);
                  SharedMemory_Close(2);
               }
               AllChangeFlag = 0;
               Close();
            }
            return;
         }
      }
   } else {
     if (ShareFlag) {
        sprintf(tempo, "CLOSE");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));

        sprintf(tempo, "EXIT");
        SharedMemory_Write(1, 0, tempo, strlen(tempo));

        SharedMemory_Close(1);
        SharedMemory_Close(2);
     }
     Close();
   }        
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button12Enter(TObject *Sender)
{
 Button12->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button12Exit(TObject *Sender)
{
 Button12->Font->Color = clBlack;
}
//---------------------------------------------------------------------------

// 保存 KDB1
void SaveKDB1()
{
 AnsiString str, UPDYMD, UPDTIM;
 char str_c[2048];

 WriteDatabaseError = 0;

 // データベースのデータ範囲をチェック (Kdb1)
 if (Cur_Kdb1.HIST_SOKUT > 999)
    Cur_Kdb1.HIST_SOKUT = 999;
 if (Cur_Kdb1.HIST_SOKUT < 0)
    Cur_Kdb1.HIST_SOKUT = 0;

 if (Cur_Kdb1.SOKUTE_SU > Cur_Kdb1.HIST_SOKUT)
    Cur_Kdb1.SOKUTE_SU = Cur_Kdb1.HIST_SOKUT;

 //2003/01/06 E.Takase
 //if (fabs(Cur_Kdb1.SOKUTE_AVE) > 9999.9999)
 //   Cur_Kdb1.SOKUTE_AVE = 9999.9999;
 if (fabs(Cur_Kdb1.SOKUTE_AVE) > 999999.9999)
    Cur_Kdb1.SOKUTE_AVE = 999999.9999;

 if (fabs(Cur_Kdb1.SOKUTE_MIN) > 999999.999)
    Cur_Kdb1.SOKUTE_MIN = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_MAX) > 999999.999)
    Cur_Kdb1.SOKUTE_MAX = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_R) > 999999.999)
    Cur_Kdb1.SOKUTE_R = 999999.999;

 if (fabs(Cur_Kdb1.SOKUTE_SGM) > 9999.99999)
    Cur_Kdb1.SOKUTE_SGM = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_CP) > 9999.99999)
    Cur_Kdb1.SOKUTE_CP = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_CPK) > 9999.99999)
    Cur_Kdb1.SOKUTE_CPK = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_K) > 9999.99999)
    Cur_Kdb1.SOKUTE_K = 9999.99999;

 if (fabs(Cur_Kdb1.SOKUTE_P) > 9999.99999)
    Cur_Kdb1.SOKUTE_P = 9999.99999;

 // Update Date & Time
 //UPDYMD = FormatDateTime("yyyymmdd",Date());
 //UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());
 if (IsNullSpace( Cur_Kdb1.ADDYMD )){
     Cur_Kdb1.ADDYMD = FormatDateTime("yyyymmdd",Date());
     Cur_Kdb1.ADDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

     //更新回数
     Cur_Kdb1.UPDCNT = 0;
 } else {
     // 変更日、変更時間
     Cur_Kdb1.UPDYMD = FormatDateTime("yyyymmdd",Date());
     Cur_Kdb1.UPDTIM = FormatDateTime("hhmm",TDateTime::CurrentTime());

     //更新回数
     Cur_Kdb1.UPDCNT += 1;
 }

 // Save 計測データ
 // Update KDA1
 Form1->Query_Kdb1->Close();
 Form1->Query_Kdb1->SQL->Clear();
 if( Form1->Database1->InTransaction == false ){
     Form1->Database1->StartTransaction();
 }

 sprintf(str_c, "update KDB1 set HIST_SOKUT=%d, SOKUTE_SU=%d, SOKUTE_AVE=%8.4f, SOKUTE_KET=%d, ",
                        Cur_Kdb1.HIST_SOKUT, Cur_Kdb1.SOKUTE_SU, Cur_Kdb1.SOKUTE_AVE, Cur_Kdb1.SOKUTE_KET);
 //sprintf(str_c, "update KDB1 set HIST_SOKUT=%d, SOKUTE_SU=%d, SOKUTE_AVE=%8.4f, ",
 //                       Cur_Kdb1.HIST_SOKUT, Cur_Kdb1.SOKUTE_SU, Cur_Kdb1.SOKUTE_AVE);
 str = str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_MIN=%9.3f, SOKUTE_MAX=%9.3f, SOKUTE_R=%9.3f,",
                 Cur_Kdb1.SOKUTE_MIN, Cur_Kdb1.SOKUTE_MAX, Cur_Kdb1.SOKUTE_R);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_SGM=%9.5f, SOKUTE_CP=%9.5f, SOKUTE_CPK=%9.5f,",
                 Cur_Kdb1.SOKUTE_SGM, Cur_Kdb1.SOKUTE_CP, Cur_Kdb1.SOKUTE_CPK);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, "SOKUTE_K=%9.5f, SOKUTE_P=%9.5f, ADDYMD = '%s', ADDTIM = '%s', UPDYMD='%s',",
                 Cur_Kdb1.SOKUTE_K, Cur_Kdb1.SOKUTE_P, Cur_Kdb1.ADDYMD.c_str(),
                 Cur_Kdb1.ADDTIM.c_str(), Cur_Kdb1.UPDYMD.c_str());
 str += str_c ;
 str_c[0] = NULL ;

 //2002/11/19 測定者を保存しない E.Takase
 //sprintf(str_c, "UPDTIM='%s', UPDCHR=%d, UPDCNT=%d",
 //              Cur_Kdb1.UPDTIM.c_str(), USER_COD , Cur_Kdb1.UPDCNT);
 sprintf(str_c, "UPDTIM='%s',  UPDCNT=%d",
               Cur_Kdb1.UPDTIM.c_str(), Cur_Kdb1.UPDCNT);
 str += str_c ;
 str_c[0] = NULL ;

 sprintf(str_c, " where KENSA_YMD ='%s' and SEQNO =%d and DTKSHIN = '%s' and LOTNO = '%s' and KOJOKBN = %d ",
                        Cur_Kdb1.KENSA_YMD.c_str(),
                        Cur_Kdb1.SEQNO, Cur_Kdb1.DTKSHIN, Cur_Kdb1.LOTNO,
                        iKojoKbn);      //20160701_工場区分追加
 str += str_c ;
 Form1->Query_Kdb1->SQL->Add(str);

 //お問い合せ文の実行
 try
 {
    Form1->Query_Kdb1->ExecSQL();
    Form1->Database1->Commit(); // 成功した場合，変更をコミットする;
 }
 catch(EDatabaseError& e)
 {
    Form1->Database1->Rollback(); // 失敗した場合，変更を取り消す
    WriteDatabaseError = 1;
    //goto Err1;
 }

 return;
}

// 有効数字３桁(2000.3.13)
// 例：12345.67 --> 12300
//     12.34567 --> 12.3
//     0.123456 --> 0.123
//     0.012345 --> 0.0123
//     0.00001234 --> 0.0000123
// 修正：2000.3.27
// 例：12345.67 --> 12346
AnsiString ConvData(int Keta, double T_data)
{
 int flag_M, flag, pos, T_int, T_int1;
 AnsiString str, FormatStr;
 double T_double;

 if (T_double < 0) {
    flag_M = -1;   // マイナス
    T_double = fabs(T_data);
 } else {
    flag_M = 1;
    T_double = T_data;
 }

 if (T_double >= 1) // １以上
    flag = 1;
 else    // １未満
    flag = 2;

 if (flag == 1) { // １以上
    str = FormatFloat("#0.000", T_double);
    pos = str.AnsiPos(".")-1;
    if (pos < Keta) {
       FormatStr = "#0." + AnsiString::StringOfChar('0', Keta-pos);
       str = FormatFloat(FormatStr, T_double * flag_M);
       return (str);
    } else {  // pos >= Keta
       if (pos == Keta) {
          str = FormatFloat("#0", T_double * flag_M);
          return (str);
       } else { // Pos > Keta
          // 2000.3.27 修正
          //T_int = pow(10, pos-Keta);
          //T_int1 = int(int(T_double)/T_int + 0.5);
          //T_double = T_int1 * T_int;
          //str = FormatFloat("#0", T_double * flag_M);
          //return (str);
          str = FormatFloat("#0", T_double * flag_M);
          return (str);
       }
    }
 } else {    // 1未満
    if (T_double <= COM_DIFF) {   // 0
       FormatStr = "#0." + AnsiString::StringOfChar('0', (Keta-1));
       str = FormatFloat(FormatStr, 0.0);
       return (str);
    } else {  // ０じゃない
       T_int = 1;
       while (1) {
          if (int(T_double * pow(10,T_int)) > 0) {
             break;
          } else
             T_int++;
       }
       FormatStr = "#0." + AnsiString::StringOfChar('0', (T_int - 1 + Keta));
       str = FormatFloat(FormatStr, T_double * flag_M);
       return (str);
    }
 }
}
void __fastcall TForm3::Button13Click(TObject *Sender)
{
    Form11->Show();
}
//---------------------------------------------------------------------------



