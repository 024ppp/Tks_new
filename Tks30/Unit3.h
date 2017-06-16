//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "NumberEdit.h"
#include <DBTables.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>

#define WM_Notify_WriteData  WM_USER + 3040	// 相手プロセスに通知します
#define WM_Notify_WriteData1 WM_USER + 3041	// 相手プロセスに通知します
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel77;
        TStatusBar *StatusBar1;
        TPanel *Panel9;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TBevel *Bevel33;
        TPanel *Panel8;
        TPanel *Panel10;
        TPanel *Panel19;
        TPanel *Panel12;
        TPanel *Panel18;
        TPanel *Panel13;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel17;
        TPanel *Panel16;
        TPanel *Lbl_NO;
        TPanel *Lbl_DTKSCOD;
        TPanel *Lbl_DTKSHIN;
        TPanel *Lbl_LOTNO;
        TPanel *Lbl_HINBAN;
        TPanel *Lbl_HIST_SOKUT;
        TPanel *Lbl_HIST_MIN;
        TPanel *Lbl_HIST_MAX;
        TPanel *Lbl_HIST_ZISNAM;
        TPanel *Lbl_STATUS;
        TPanel *Panel31;
        TPanel *Panel32;
        TPanel *Panel57;
        TPanel *Panel58;
        TPanel *Panel34;
        TPanel *Panel35;
        TPanel *Panel36;
        TPanel *Panel37;
        TBevel *Bevel3;
        TPanel *Panel141;
        TPanel *Panel142;
        TPanel *Panel144;
        TPanel *Lbl_HIST_MIN1;
        TPanel *Lbl_HIST_MAX1;
        TStaticText *StaticText1;
        TPanel *Panel143;
        TPanel *Lbl_SOKUTE_AVE;
        TPanel *Panel148;
        TPanel *Lbl_SOKUTE_SU;
        TPanel *Panel150;
        TPanel *Lbl_SOKUTE_MIN;
        TPanel *Panel152;
        TPanel *Lbl_SOKUTE_MAX;
        TPanel *Panel154;
        TPanel *Lbl_SIGUMA;
        TPanel *Panel156;
        TPanel *Lbl_SOKUTE_CP;
        TPanel *Panel158;
        TPanel *Lbl_SOKUTE_CPK;
        TPanel *Panel160;
        TPanel *Lbl_SOKUTE_K;
        TPanel *Panel162;
        TPanel *Lbl_SOKUTE_R;
        TScrollBox *ScrollBox2;
        TPanel *Panel165;
        TPanel *Panel167;
        TPanel *Panel168;
        TPanel *Panel166;
        TPanel *Sta_01A;
        TPanel *Sta_01B;
        TPanel *Sta_01C;
        TPanel *Sta_02A;
        TPanel *Sta_02B;
        TPanel *Sta_02C;
        TPanel *Sta_04C;
        TPanel *Sta_04B;
        TPanel *Sta_04A;
        TPanel *Sta_03A;
        TPanel *Sta_03B;
        TPanel *Sta_03C;
        TPanel *Sta_05C;
        TPanel *Sta_05A;
        TPanel *Sta_06A;
        TPanel *Sta_05B;
        TPanel *Sta_06B;
        TPanel *Sta_06C;
        TPanel *Sta_07C;
        TPanel *Sta_07B;
        TPanel *Sta_07A;
        TPanel *Sta_08A;
        TPanel *Sta_08B;
        TPanel *Sta_08C;
        TPanel *Sta_09C;
        TPanel *Sta_09A;
        TPanel *Sta_10A;
        TPanel *Sta_09B;
        TPanel *Sta_10B;
        TPanel *Sta_10C;
        TPanel *Sta_11C;
        TPanel *Sta_11B;
        TPanel *Sta_11A;
        TPanel *Sta_12A;
        TPanel *Sta_12B;
        TPanel *Sta_12C;
        TPanel *Sta_13C;
        TPanel *Sta_13A;
        TPanel *Sta_14A;
        TPanel *Sta_13B;
        TPanel *Sta_14B;
        TPanel *Sta_14C;
        TPanel *Sta_15C;
        TPanel *Sta_15B;
        TPanel *Sta_15A;
        TPanel *Sta_16A;
        TPanel *Sta_16B;
        TPanel *Sta_16C;
        TPanel *Sta_17C;
        TPanel *Sta_17A;
        TPanel *Sta_18A;
        TPanel *Sta_17B;
        TPanel *Sta_18B;
        TPanel *Sta_18C;
        TPanel *Sta_19C;
        TPanel *Sta_19B;
        TPanel *Sta_19A;
        TPanel *Sta_20A;
        TPanel *Sta_20B;
        TPanel *Sta_20C;
        TPanel *Panel229;
        TPanel *Lbl_SOKUTE_P;
        TPanel *Panel231;
        TPanel *Panel232;
        TPanel *Lbl_HIST_KIKAK;
        TStaticText *StaticText2;
        TScrollBox *ScrollBox1;
        TPanel *Pan_001;
        TPanel *Pan_002;
        TPanel *Pan_003;
        TPanel *Pan_004;
        TPanel *Pan_005;
        TPanel *Pan_006;
        TPanel *Pan_007;
        TPanel *Pan_008;
        TPanel *Pan_009;
        TPanel *Pan_010;
        TPanel *Pan_011;
        TPanel *Pan_012;
        TPanel *Pan_013;
        TPanel *Pan_014;
        TPanel *Pan_015;
        TPanel *Pan_016;
        TPanel *Pan_017;
        TPanel *Pan_018;
        TPanel *Pan_019;
        TPanel *Pan_020;
        TPanel *Pan_021;
        TPanel *Pan_022;
        TPanel *Pan_023;
        TPanel *Pan_024;
        TPanel *Pan_025;
        TPanel *Pan_026;
        TPanel *Pan_027;
        TPanel *Pan_028;
        TPanel *Pan_029;
        TPanel *Pan_030;
        TPanel *Pan_031;
        TPanel *Pan_032;
        TPanel *Pan_033;
        TPanel *Pan_034;
        TPanel *Pan_035;
        TPanel *Pan_036;
        TPanel *Pan_037;
        TPanel *Pan_038;
        TPanel *Pan_039;
        TPanel *Pan_040;
        TPanel *Pan_041;
        TPanel *Pan_042;
        TPanel *Pan_043;
        TPanel *Pan_044;
        TPanel *Pan_045;
        TPanel *Pan_046;
        TPanel *Pan_047;
        TPanel *Pan_048;
        TPanel *Pan_049;
        TPanel *Pan_050;
        TPanel *Pan_051;
        TPanel *Pan_052;
        TPanel *Pan_053;
        TPanel *Pan_054;
        TPanel *Pan_055;
        TPanel *Pan_056;
        TPanel *Pan_057;
        TPanel *Pan_058;
        TPanel *Pan_059;
        TPanel *Pan_060;
        TPanel *Pan_061;
        TPanel *Pan_062;
        TPanel *Pan_063;
        TPanel *Pan_064;
        TPanel *Pan_065;
        TPanel *Pan_066;
        TPanel *Pan_067;
        TPanel *Pan_068;
        TPanel *Pan_077;
        TPanel *Pan_078;
        TPanel *Pan_079;
        TPanel *Pan_080;
        TPanel *Pan_076;
        TPanel *Pan_075;
        TPanel *Pan_074;
        TPanel *Pan_073;
        TPanel *Pan_069;
        TPanel *Pan_070;
        TPanel *Pan_071;
        TPanel *Pan_072;
        TPanel *Pan_081;
        TPanel *Pan_085;
        TPanel *Pan_089;
        TPanel *Pan_082;
        TPanel *Pan_086;
        TPanel *Pan_090;
        TPanel *Pan_083;
        TPanel *Pan_087;
        TPanel *Pan_091;
        TPanel *Pan_084;
        TPanel *Pan_088;
        TPanel *Pan_092;
        TPanel *Pan_093;
        TPanel *Pan_097;
        TPanel *Pan_094;
        TPanel *Pan_098;
        TPanel *Pan_095;
        TPanel *Pan_099;
        TPanel *Pan_096;
        TPanel *Pan_100;
        TNumberEdit *Edt_001;
        TNumberEdit *Edt_002;
        TNumberEdit *Edt_003;
        TNumberEdit *Edt_004;
        TNumberEdit *Edt_005;
        TNumberEdit *Edt_006;
        TNumberEdit *Edt_007;
        TNumberEdit *Edt_008;
        TNumberEdit *Edt_009;
        TNumberEdit *Edt_010;
        TNumberEdit *Edt_011;
        TNumberEdit *Edt_012;
        TNumberEdit *Edt_013;
        TNumberEdit *Edt_014;
        TNumberEdit *Edt_015;
        TNumberEdit *Edt_016;
        TNumberEdit *Edt_017;
        TNumberEdit *Edt_018;
        TNumberEdit *Edt_019;
        TNumberEdit *Edt_020;
        TNumberEdit *Edt_021;
        TNumberEdit *Edt_022;
        TNumberEdit *Edt_023;
        TNumberEdit *Edt_024;
        TNumberEdit *Edt_025;
        TNumberEdit *Edt_026;
        TNumberEdit *Edt_027;
        TNumberEdit *Edt_028;
        TNumberEdit *Edt_029;
        TNumberEdit *Edt_030;
        TNumberEdit *Edt_031;
        TNumberEdit *Edt_032;
        TNumberEdit *Edt_036;
        TNumberEdit *Edt_035;
        TNumberEdit *Edt_034;
        TNumberEdit *Edt_033;
        TNumberEdit *Edt_037;
        TNumberEdit *Edt_038;
        TNumberEdit *Edt_039;
        TNumberEdit *Edt_040;
        TNumberEdit *Edt_041;
        TNumberEdit *Edt_042;
        TNumberEdit *Edt_043;
        TNumberEdit *Edt_044;
        TNumberEdit *Edt_045;
        TNumberEdit *Edt_046;
        TNumberEdit *Edt_047;
        TNumberEdit *Edt_048;
        TNumberEdit *Edt_049;
        TNumberEdit *Edt_050;
        TNumberEdit *Edt_051;
        TNumberEdit *Edt_052;
        TNumberEdit *Edt_053;
        TNumberEdit *Edt_054;
        TNumberEdit *Edt_055;
        TNumberEdit *Edt_056;
        TNumberEdit *Edt_057;
        TNumberEdit *Edt_058;
        TNumberEdit *Edt_059;
        TNumberEdit *Edt_060;
        TNumberEdit *Edt_061;
        TNumberEdit *Edt_062;
        TNumberEdit *Edt_063;
        TNumberEdit *Edt_064;
        TNumberEdit *Edt_065;
        TNumberEdit *Edt_066;
        TNumberEdit *Edt_067;
        TNumberEdit *Edt_068;
        TNumberEdit *Edt_069;
        TNumberEdit *Edt_070;
        TNumberEdit *Edt_071;
        TNumberEdit *Edt_072;
        TNumberEdit *Edt_073;
        TNumberEdit *Edt_074;
        TNumberEdit *Edt_075;
        TNumberEdit *Edt_076;
        TNumberEdit *Edt_077;
        TNumberEdit *Edt_078;
        TNumberEdit *Edt_079;
        TNumberEdit *Edt_080;
        TNumberEdit *Edt_081;
        TNumberEdit *Edt_082;
        TNumberEdit *Edt_083;
        TNumberEdit *Edt_084;
        TNumberEdit *Edt_085;
        TNumberEdit *Edt_086;
        TNumberEdit *Edt_087;
        TNumberEdit *Edt_088;
        TNumberEdit *Edt_089;
        TNumberEdit *Edt_090;
        TNumberEdit *Edt_091;
        TNumberEdit *Edt_092;
        TNumberEdit *Edt_093;
        TNumberEdit *Edt_094;
        TNumberEdit *Edt_095;
        TNumberEdit *Edt_096;
        TNumberEdit *Edt_097;
        TNumberEdit *Edt_098;
        TNumberEdit *Edt_099;
        TNumberEdit *Edt_100;
        TPanel *Pan_101;
        TNumberEdit *Edt_101;
        TPanel *Pan_102;
        TNumberEdit *Edt_102;
        TPanel *Pan_103;
        TNumberEdit *Edt_103;
        TPanel *Pan_104;
        TNumberEdit *Edt_104;
        TPanel *Pan_105;
        TNumberEdit *Edt_105;
        TPanel *Pan_106;
        TNumberEdit *Edt_106;
        TPanel *Pan_107;
        TNumberEdit *Edt_107;
        TPanel *Pan_108;
        TNumberEdit *Edt_108;
        TPanel *Pan_109;
        TNumberEdit *Edt_109;
        TPanel *Pan_110;
        TNumberEdit *Edt_110;
        TPanel *Pan_111;
        TNumberEdit *Edt_111;
        TPanel *Pan_112;
        TNumberEdit *Edt_112;
        TPanel *Pan_113;
        TNumberEdit *Edt_113;
        TPanel *Pan_114;
        TNumberEdit *Edt_114;
        TPanel *Pan_115;
        TNumberEdit *Edt_115;
        TPanel *Pan_116;
        TNumberEdit *Edt_116;
        TPanel *Pan_117;
        TNumberEdit *Edt_117;
        TPanel *Pan_118;
        TNumberEdit *Edt_118;
        TPanel *Pan_119;
        TNumberEdit *Edt_119;
        TPanel *Pan_120;
        TNumberEdit *Edt_120;
        TPanel *Pan_121;
        TNumberEdit *Edt_121;
        TPanel *Pan_122;
        TNumberEdit *Edt_122;
        TPanel *Pan_123;
        TNumberEdit *Edt_123;
        TPanel *Pan_124;
        TNumberEdit *Edt_124;
        TPanel *Pan_125;
        TNumberEdit *Edt_125;
        TPanel *Pan_126;
        TNumberEdit *Edt_126;
        TPanel *Pan_127;
        TNumberEdit *Edt_127;
        TPanel *Pan_128;
        TNumberEdit *Edt_128;
        TPanel *Pan_129;
        TNumberEdit *Edt_129;
        TPanel *Pan_130;
        TNumberEdit *Edt_130;
        TPanel *Pan_131;
        TNumberEdit *Edt_131;
        TPanel *Pan_132;
        TNumberEdit *Edt_132;
        TPanel *Pan_133;
        TNumberEdit *Edt_133;
        TPanel *Pan_134;
        TNumberEdit *Edt_134;
        TPanel *Pan_135;
        TNumberEdit *Edt_135;
        TPanel *Pan_136;
        TNumberEdit *Edt_136;
        TPanel *Pan_137;
        TNumberEdit *Edt_137;
        TPanel *Pan_138;
        TNumberEdit *Edt_138;
        TPanel *Pan_139;
        TNumberEdit *Edt_139;
        TPanel *Pan_140;
        TNumberEdit *Edt_140;
        TPanel *Pan_141;
        TNumberEdit *Edt_141;
        TPanel *Pan_142;
        TNumberEdit *Edt_142;
        TPanel *Pan_143;
        TNumberEdit *Edt_143;
        TPanel *Pan_144;
        TNumberEdit *Edt_144;
        TPanel *Pan_145;
        TNumberEdit *Edt_145;
        TPanel *Pan_146;
        TNumberEdit *Edt_146;
        TPanel *Pan_147;
        TNumberEdit *Edt_147;
        TPanel *Pan_148;
        TNumberEdit *Edt_148;
        TPanel *Pan_149;
        TNumberEdit *Edt_149;
        TPanel *Pan_150;
        TNumberEdit *Edt_150;
        TPanel *Pan_151;
        TNumberEdit *Edt_151;
        TPanel *Pan_152;
        TNumberEdit *Edt_152;
        TPanel *Pan_153;
        TNumberEdit *Edt_153;
        TPanel *Pan_154;
        TNumberEdit *Edt_154;
        TPanel *Pan_155;
        TNumberEdit *Edt_155;
        TPanel *Pan_156;
        TNumberEdit *Edt_156;
        TPanel *Pan_157;
        TNumberEdit *Edt_157;
        TPanel *Pan_158;
        TNumberEdit *Edt_158;
        TPanel *Pan_159;
        TNumberEdit *Edt_159;
        TPanel *Pan_160;
        TNumberEdit *Edt_160;
        TPanel *Pan_161;
        TNumberEdit *Edt_161;
        TPanel *Pan_162;
        TNumberEdit *Edt_162;
        TPanel *Pan_163;
        TNumberEdit *Edt_163;
        TPanel *Pan_164;
        TNumberEdit *Edt_164;
        TPanel *Pan_165;
        TNumberEdit *Edt_165;
        TPanel *Pan_166;
        TNumberEdit *Edt_166;
        TPanel *Pan_167;
        TNumberEdit *Edt_167;
        TPanel *Pan_168;
        TNumberEdit *Edt_168;
        TPanel *Pan_169;
        TNumberEdit *Edt_169;
        TPanel *Pan_170;
        TNumberEdit *Edt_170;
        TPanel *Pan_171;
        TNumberEdit *Edt_171;
        TPanel *Pan_172;
        TNumberEdit *Edt_172;
        TPanel *Pan_177;
        TNumberEdit *Edt_177;
        TPanel *Pan_178;
        TNumberEdit *Edt_178;
        TPanel *Pan_179;
        TNumberEdit *Edt_179;
        TPanel *Pan_180;
        TNumberEdit *Edt_180;
        TPanel *Pan_181;
        TNumberEdit *Edt_181;
        TPanel *Pan_182;
        TNumberEdit *Edt_182;
        TPanel *Pan_183;
        TNumberEdit *Edt_183;
        TPanel *Pan_184;
        TNumberEdit *Edt_184;
        TPanel *Pan_185;
        TNumberEdit *Edt_185;
        TPanel *Pan_186;
        TNumberEdit *Edt_186;
        TPanel *Pan_187;
        TNumberEdit *Edt_187;
        TPanel *Pan_188;
        TNumberEdit *Edt_188;
        TPanel *Pan_189;
        TNumberEdit *Edt_189;
        TPanel *Pan_190;
        TNumberEdit *Edt_190;
        TPanel *Pan_191;
        TNumberEdit *Edt_191;
        TPanel *Pan_192;
        TNumberEdit *Edt_192;
        TPanel *Pan_193;
        TNumberEdit *Edt_193;
        TPanel *Pan_194;
        TNumberEdit *Edt_194;
        TPanel *Pan_195;
        TNumberEdit *Edt_195;
        TPanel *Pan_196;
        TNumberEdit *Edt_196;
        TPanel *Pan_197;
        TNumberEdit *Edt_197;
        TPanel *Pan_198;
        TNumberEdit *Edt_198;
        TPanel *Pan_199;
        TNumberEdit *Edt_199;
        TPanel *Pan_200;
        TNumberEdit *Edt_200;
        TPanel *Pan_173;
        TNumberEdit *Edt_173;
        TPanel *Pan_174;
        TNumberEdit *Edt_174;
        TPanel *Pan_175;
        TNumberEdit *Edt_175;
        TPanel *Pan_176;
        TNumberEdit *Edt_176;
        TPanel *Pan_201;
        TNumberEdit *Edt_201;
        TPanel *Pan_202;
        TNumberEdit *Edt_202;
        TPanel *Pan_203;
        TNumberEdit *Edt_203;
        TPanel *Pan_204;
        TNumberEdit *Edt_204;
        TPanel *Pan_205;
        TNumberEdit *Edt_205;
        TPanel *Pan_206;
        TNumberEdit *Edt_206;
        TPanel *Pan_207;
        TNumberEdit *Edt_207;
        TPanel *Pan_208;
        TNumberEdit *Edt_208;
        TPanel *Pan_209;
        TNumberEdit *Edt_209;
        TPanel *Pan_210;
        TNumberEdit *Edt_210;
        TPanel *Pan_211;
        TNumberEdit *Edt_211;
        TPanel *Pan_212;
        TNumberEdit *Edt_212;
        TPanel *Pan_213;
        TNumberEdit *Edt_213;
        TPanel *Pan_214;
        TNumberEdit *Edt_214;
        TPanel *Pan_215;
        TNumberEdit *Edt_215;
        TPanel *Pan_216;
        TNumberEdit *Edt_216;
        TPanel *Pan_217;
        TNumberEdit *Edt_217;
        TPanel *Pan_218;
        TNumberEdit *Edt_218;
        TPanel *Pan_219;
        TNumberEdit *Edt_219;
        TPanel *Pan_220;
        TNumberEdit *Edt_220;
        TPanel *Pan_221;
        TNumberEdit *Edt_221;
        TPanel *Pan_222;
        TNumberEdit *Edt_222;
        TPanel *Pan_223;
        TNumberEdit *Edt_223;
        TPanel *Pan_224;
        TNumberEdit *Edt_224;
        TPanel *Pan_225;
        TNumberEdit *Edt_225;
        TPanel *Pan_226;
        TNumberEdit *Edt_226;
        TPanel *Pan_227;
        TNumberEdit *Edt_227;
        TPanel *Pan_228;
        TNumberEdit *Edt_228;
        TPanel *Pan_229;
        TNumberEdit *Edt_229;
        TPanel *Pan_230;
        TNumberEdit *Edt_230;
        TPanel *Pan_231;
        TNumberEdit *Edt_231;
        TPanel *Pan_232;
        TNumberEdit *Edt_232;
        TPanel *Pan_233;
        TNumberEdit *Edt_233;
        TPanel *Pan_234;
        TNumberEdit *Edt_234;
        TPanel *Pan_235;
        TNumberEdit *Edt_235;
        TPanel *Pan_236;
        TNumberEdit *Edt_236;
        TPanel *Pan_237;
        TNumberEdit *Edt_237;
        TPanel *Pan_238;
        TNumberEdit *Edt_238;
        TPanel *Pan_239;
        TNumberEdit *Edt_239;
        TPanel *Pan_240;
        TNumberEdit *Edt_240;
        TPanel *Pan_241;
        TNumberEdit *Edt_241;
        TPanel *Pan_242;
        TNumberEdit *Edt_242;
        TPanel *Pan_243;
        TNumberEdit *Edt_243;
        TPanel *Pan_244;
        TNumberEdit *Edt_244;
        TPanel *Pan_245;
        TNumberEdit *Edt_245;
        TPanel *Pan_246;
        TNumberEdit *Edt_246;
        TPanel *Pan_247;
        TNumberEdit *Edt_247;
        TPanel *Pan_248;
        TNumberEdit *Edt_248;
        TPanel *Pan_249;
        TNumberEdit *Edt_249;
        TPanel *Pan_250;
        TNumberEdit *Edt_250;
        TPanel *Pan_251;
        TNumberEdit *Edt_251;
        TPanel *Pan_252;
        TNumberEdit *Edt_252;
        TPanel *Pan_253;
        TNumberEdit *Edt_253;
        TPanel *Pan_254;
        TNumberEdit *Edt_254;
        TPanel *Pan_255;
        TNumberEdit *Edt_255;
        TPanel *Pan_256;
        TNumberEdit *Edt_256;
        TPanel *Pan_257;
        TNumberEdit *Edt_257;
        TPanel *Pan_258;
        TNumberEdit *Edt_258;
        TPanel *Pan_259;
        TNumberEdit *Edt_259;
        TPanel *Pan_260;
        TNumberEdit *Edt_260;
        TPanel *Pan_261;
        TNumberEdit *Edt_261;
        TPanel *Pan_262;
        TNumberEdit *Edt_262;
        TPanel *Pan_263;
        TNumberEdit *Edt_263;
        TPanel *Pan_264;
        TNumberEdit *Edt_264;
        TPanel *Pan_265;
        TNumberEdit *Edt_265;
        TPanel *Pan_266;
        TNumberEdit *Edt_266;
        TPanel *Pan_267;
        TNumberEdit *Edt_267;
        TPanel *Pan_268;
        TNumberEdit *Edt_268;
        TPanel *Pan_269;
        TNumberEdit *Edt_269;
        TPanel *Pan_270;
        TNumberEdit *Edt_270;
        TPanel *Pan_271;
        TNumberEdit *Edt_271;
        TPanel *Pan_272;
        TNumberEdit *Edt_272;
        TPanel *Pan_273;
        TNumberEdit *Edt_273;
        TPanel *Pan_274;
        TNumberEdit *Edt_274;
        TPanel *Pan_275;
        TNumberEdit *Edt_275;
        TPanel *Pan_276;
        TNumberEdit *Edt_276;
        TPanel *Pan_277;
        TNumberEdit *Edt_277;
        TPanel *Pan_278;
        TNumberEdit *Edt_278;
        TPanel *Pan_279;
        TNumberEdit *Edt_279;
        TPanel *Pan_280;
        TNumberEdit *Edt_280;
        TPanel *Pan_281;
        TNumberEdit *Edt_281;
        TPanel *Pan_282;
        TNumberEdit *Edt_282;
        TPanel *Pan_283;
        TNumberEdit *Edt_283;
        TPanel *Pan_284;
        TNumberEdit *Edt_284;
        TPanel *Pan_285;
        TNumberEdit *Edt_285;
        TPanel *Pan_286;
        TNumberEdit *Edt_286;
        TPanel *Pan_287;
        TNumberEdit *Edt_287;
        TPanel *Pan_288;
        TNumberEdit *Edt_288;
        TPanel *Pan_289;
        TNumberEdit *Edt_289;
        TPanel *Pan_290;
        TNumberEdit *Edt_290;
        TPanel *Pan_291;
        TNumberEdit *Edt_291;
        TPanel *Pan_292;
        TNumberEdit *Edt_292;
        TPanel *Pan_293;
        TNumberEdit *Edt_293;
        TPanel *Pan_294;
        TNumberEdit *Edt_294;
        TPanel *Pan_295;
        TNumberEdit *Edt_295;
        TPanel *Pan_296;
        TNumberEdit *Edt_296;
        TPanel *Pan_297;
        TNumberEdit *Edt_297;
        TPanel *Pan_298;
        TNumberEdit *Edt_298;
        TPanel *Pan_299;
        TNumberEdit *Edt_299;
        TPanel *Pan_300;
        TNumberEdit *Edt_300;
        TPanel *Pan_YMD;
        TImage *Image1;
        TPanel *Pan_301;
        TNumberEdit *Edt_301;
        TPanel *Pan_302;
        TNumberEdit *Edt_302;
        TPanel *Pan_303;
        TNumberEdit *Edt_303;
        TPanel *Pan_304;
        TNumberEdit *Edt_304;
        TNumberEdit *Edt_308;
        TPanel *Pan_308;
        TNumberEdit *Edt_307;
        TPanel *Pan_307;
        TNumberEdit *Edt_306;
        TPanel *Pan_306;
        TNumberEdit *Edt_305;
        TPanel *Pan_305;
        TPanel *Pan_309;
        TNumberEdit *Edt_309;
        TPanel *Pan_310;
        TNumberEdit *Edt_310;
        TPanel *Pan_311;
        TNumberEdit *Edt_311;
        TPanel *Pan_312;
        TNumberEdit *Edt_312;
        TNumberEdit *Edt_316;
        TPanel *Pan_316;
        TNumberEdit *Edt_315;
        TPanel *Pan_315;
        TNumberEdit *Edt_314;
        TPanel *Pan_314;
        TNumberEdit *Edt_313;
        TPanel *Pan_313;
        TPanel *Pan_317;
        TNumberEdit *Edt_317;
        TPanel *Pan_318;
        TNumberEdit *Edt_318;
        TPanel *Pan_319;
        TNumberEdit *Edt_319;
        TPanel *Pan_320;
        TNumberEdit *Edt_320;
        TNumberEdit *Edt_324;
        TPanel *Pan_324;
        TNumberEdit *Edt_323;
        TPanel *Pan_323;
        TNumberEdit *Edt_322;
        TPanel *Pan_322;
        TNumberEdit *Edt_321;
        TPanel *Pan_321;
        TPanel *Pan_325;
        TNumberEdit *Edt_325;
        TPanel *Pan_326;
        TNumberEdit *Edt_326;
        TPanel *Pan_327;
        TNumberEdit *Edt_327;
        TPanel *Pan_328;
        TNumberEdit *Edt_328;
        TNumberEdit *Edt_332;
        TPanel *Pan_332;
        TNumberEdit *Edt_331;
        TPanel *Pan_331;
        TNumberEdit *Edt_330;
        TPanel *Pan_330;
        TNumberEdit *Edt_329;
        TPanel *Pan_329;
        TPanel *Pan_333;
        TNumberEdit *Edt_333;
        TPanel *Pan_334;
        TNumberEdit *Edt_334;
        TPanel *Pan_335;
        TNumberEdit *Edt_335;
        TPanel *Pan_336;
        TNumberEdit *Edt_336;
        TPanel *Pan_337;
        TNumberEdit *Edt_337;
        TPanel *Pan_338;
        TNumberEdit *Edt_338;
        TPanel *Pan_339;
        TNumberEdit *Edt_339;
        TPanel *Pan_340;
        TNumberEdit *Edt_340;
        TNumberEdit *Edt_344;
        TPanel *Pan_344;
        TNumberEdit *Edt_343;
        TPanel *Pan_343;
        TNumberEdit *Edt_342;
        TPanel *Pan_342;
        TNumberEdit *Edt_341;
        TPanel *Pan_341;
        TPanel *Pan_345;
        TNumberEdit *Edt_345;
        TPanel *Pan_346;
        TNumberEdit *Edt_346;
        TPanel *Pan_347;
        TNumberEdit *Edt_347;
        TPanel *Pan_348;
        TNumberEdit *Edt_348;
        TNumberEdit *Edt_352;
        TPanel *Pan_352;
        TNumberEdit *Edt_351;
        TPanel *Pan_351;
        TNumberEdit *Edt_350;
        TNumberEdit *Edt_349;
        TPanel *Pan_350;
        TPanel *Pan_349;
        TPanel *Pan_353;
        TNumberEdit *Edt_353;
        TPanel *Pan_354;
        TNumberEdit *Edt_354;
        TPanel *Pan_355;
        TNumberEdit *Edt_355;
        TPanel *Pan_356;
        TNumberEdit *Edt_356;
        TNumberEdit *Edt_360;
        TPanel *Pan_360;
        TNumberEdit *Edt_359;
        TPanel *Pan_359;
        TNumberEdit *Edt_358;
        TPanel *Pan_358;
        TNumberEdit *Edt_357;
        TPanel *Pan_357;
        TPanel *Pan_361;
        TNumberEdit *Edt_361;
        TPanel *Pan_362;
        TNumberEdit *Edt_362;
        TPanel *Pan_363;
        TNumberEdit *Edt_363;
        TPanel *Pan_364;
        TNumberEdit *Edt_364;
        TNumberEdit *Edt_368;
        TPanel *Pan_368;
        TNumberEdit *Edt_367;
        TPanel *Pan_367;
        TNumberEdit *Edt_366;
        TPanel *Pan_366;
        TNumberEdit *Edt_365;
        TPanel *Pan_365;
        TPanel *Pan_369;
        TNumberEdit *Edt_369;
        TPanel *Pan_370;
        TNumberEdit *Edt_370;
        TPanel *Pan_371;
        TNumberEdit *Edt_371;
        TPanel *Pan_372;
        TNumberEdit *Edt_372;
        TNumberEdit *Edt_376;
        TPanel *Pan_376;
        TNumberEdit *Edt_375;
        TPanel *Pan_375;
        TNumberEdit *Edt_374;
        TPanel *Pan_374;
        TNumberEdit *Edt_373;
        TPanel *Pan_373;
        TPanel *Pan_377;
        TNumberEdit *Edt_377;
        TPanel *Pan_378;
        TNumberEdit *Edt_378;
        TPanel *Pan_379;
        TNumberEdit *Edt_379;
        TPanel *Pan_380;
        TNumberEdit *Edt_380;
        TNumberEdit *Edt_384;
        TPanel *Pan_384;
        TNumberEdit *Edt_383;
        TPanel *Pan_383;
        TNumberEdit *Edt_382;
        TPanel *Pan_382;
        TNumberEdit *Edt_381;
        TPanel *Pan_381;
        TPanel *Pan_385;
        TNumberEdit *Edt_385;
        TPanel *Pan_386;
        TNumberEdit *Edt_386;
        TPanel *Pan_387;
        TNumberEdit *Edt_387;
        TPanel *Pan_388;
        TNumberEdit *Edt_388;
        TNumberEdit *Edt_392;
        TPanel *Pan_392;
        TNumberEdit *Edt_391;
        TPanel *Pan_391;
        TNumberEdit *Edt_390;
        TPanel *Pan_390;
        TNumberEdit *Edt_389;
        TPanel *Pan_389;
        TPanel *Pan_393;
        TNumberEdit *Edt_393;
        TPanel *Pan_394;
        TNumberEdit *Edt_394;
        TPanel *Pan_395;
        TNumberEdit *Edt_395;
        TPanel *Pan_396;
        TNumberEdit *Edt_396;
        TNumberEdit *Edt_400;
        TPanel *Pan_400;
        TNumberEdit *Edt_399;
        TPanel *Pan_399;
        TNumberEdit *Edt_398;
        TPanel *Pan_398;
        TNumberEdit *Edt_397;
        TPanel *Pan_397;
        TPanel *Pan_401;
        TNumberEdit *Edt_401;
        TPanel *Pan_402;
        TNumberEdit *Edt_402;
        TPanel *Pan_403;
        TNumberEdit *Edt_403;
        TPanel *Pan_404;
        TNumberEdit *Edt_404;
        TPanel *Pan_405;
        TNumberEdit *Edt_405;
        TPanel *Pan_406;
        TNumberEdit *Edt_406;
        TPanel *Pan_407;
        TNumberEdit *Edt_407;
        TPanel *Pan_408;
        TNumberEdit *Edt_408;
        TPanel *Pan_409;
        TNumberEdit *Edt_409;
        TPanel *Pan_410;
        TNumberEdit *Edt_410;
        TPanel *Pan_411;
        TNumberEdit *Edt_411;
        TPanel *Pan_412;
        TNumberEdit *Edt_412;
        TPanel *Pan_413;
        TNumberEdit *Edt_413;
        TPanel *Pan_414;
        TNumberEdit *Edt_414;
        TPanel *Pan_415;
        TNumberEdit *Edt_415;
        TPanel *Pan_416;
        TNumberEdit *Edt_416;
        TPanel *Pan_417;
        TNumberEdit *Edt_417;
        TPanel *Pan_418;
        TNumberEdit *Edt_418;
        TPanel *Pan_419;
        TNumberEdit *Edt_419;
        TPanel *Pan_420;
        TNumberEdit *Edt_420;
        TPanel *Pan_421;
        TNumberEdit *Edt_421;
        TPanel *Pan_422;
        TNumberEdit *Edt_422;
        TPanel *Pan_423;
        TNumberEdit *Edt_423;
        TPanel *Pan_424;
        TNumberEdit *Edt_424;
        TPanel *Pan_425;
        TNumberEdit *Edt_425;
        TPanel *Pan_426;
        TNumberEdit *Edt_426;
        TPanel *Pan_427;
        TNumberEdit *Edt_427;
        TPanel *Pan_428;
        TNumberEdit *Edt_428;
        TPanel *Pan_429;
        TNumberEdit *Edt_429;
        TPanel *Pan_430;
        TNumberEdit *Edt_430;
        TPanel *Pan_431;
        TNumberEdit *Edt_431;
        TPanel *Pan_432;
        TNumberEdit *Edt_432;
        TPanel *Pan_433;
        TNumberEdit *Edt_433;
        TPanel *Pan_434;
        TNumberEdit *Edt_434;
        TPanel *Pan_435;
        TNumberEdit *Edt_435;
        TPanel *Pan_436;
        TNumberEdit *Edt_436;
        TPanel *Pan_437;
        TNumberEdit *Edt_437;
        TPanel *Pan_438;
        TNumberEdit *Edt_438;
        TPanel *Pan_439;
        TNumberEdit *Edt_439;
        TPanel *Pan_440;
        TNumberEdit *Edt_440;
        TPanel *Pan_441;
        TNumberEdit *Edt_441;
        TPanel *Pan_442;
        TNumberEdit *Edt_442;
        TPanel *Pan_443;
        TNumberEdit *Edt_443;
        TPanel *Pan_444;
        TNumberEdit *Edt_444;
        TPanel *Pan_445;
        TNumberEdit *Edt_445;
        TPanel *Pan_446;
        TNumberEdit *Edt_446;
        TPanel *Pan_447;
        TNumberEdit *Edt_447;
        TPanel *Pan_448;
        TNumberEdit *Edt_448;
        TPanel *Pan_449;
        TNumberEdit *Edt_449;
        TPanel *Pan_450;
        TNumberEdit *Edt_450;
        TPanel *Pan_451;
        TNumberEdit *Edt_451;
        TPanel *Pan_452;
        TNumberEdit *Edt_452;
        TPanel *Pan_453;
        TNumberEdit *Edt_453;
        TPanel *Pan_454;
        TNumberEdit *Edt_454;
        TPanel *Pan_455;
        TNumberEdit *Edt_455;
        TPanel *Pan_456;
        TNumberEdit *Edt_456;
        TPanel *Pan_457;
        TNumberEdit *Edt_457;
        TPanel *Pan_458;
        TNumberEdit *Edt_458;
        TPanel *Pan_459;
        TNumberEdit *Edt_459;
        TPanel *Pan_460;
        TPanel *Pan_461;
        TNumberEdit *Edt_461;
        TPanel *Pan_462;
        TNumberEdit *Edt_462;
        TPanel *Pan_463;
        TNumberEdit *Edt_463;
        TPanel *Pan_464;
        TNumberEdit *Edt_464;
        TPanel *Pan_465;
        TNumberEdit *Edt_465;
        TPanel *Pan_466;
        TNumberEdit *Edt_466;
        TPanel *Pan_467;
        TNumberEdit *Edt_467;
        TPanel *Pan_468;
        TNumberEdit *Edt_468;
        TPanel *Pan_469;
        TNumberEdit *Edt_469;
        TPanel *Pan_470;
        TNumberEdit *Edt_470;
        TPanel *Pan_471;
        TNumberEdit *Edt_471;
        TPanel *Pan_472;
        TNumberEdit *Edt_472;
        TPanel *Pan_473;
        TNumberEdit *Edt_473;
        TPanel *Pan_474;
        TNumberEdit *Edt_474;
        TPanel *Pan_475;
        TNumberEdit *Edt_475;
        TPanel *Pan_476;
        TNumberEdit *Edt_476;
        TPanel *Pan_477;
        TNumberEdit *Edt_477;
        TPanel *Pan_478;
        TNumberEdit *Edt_478;
        TPanel *Pan_479;
        TNumberEdit *Edt_479;
        TPanel *Pan_480;
        TNumberEdit *Edt_480;
        TPanel *Pan_481;
        TNumberEdit *Edt_481;
        TPanel *Pan_482;
        TNumberEdit *Edt_482;
        TPanel *Pan_483;
        TNumberEdit *Edt_483;
        TPanel *Pan_484;
        TNumberEdit *Edt_484;
        TPanel *Pan_485;
        TNumberEdit *Edt_485;
        TPanel *Pan_486;
        TNumberEdit *Edt_486;
        TPanel *Pan_487;
        TNumberEdit *Edt_487;
        TPanel *Pan_488;
        TNumberEdit *Edt_488;
        TPanel *Pan_489;
        TNumberEdit *Edt_489;
        TPanel *Pan_490;
        TNumberEdit *Edt_490;
        TPanel *Pan_491;
        TNumberEdit *Edt_491;
        TPanel *Pan_492;
        TNumberEdit *Edt_492;
        TPanel *Pan_493;
        TNumberEdit *Edt_493;
        TPanel *Pan_494;
        TNumberEdit *Edt_494;
        TPanel *Pan_495;
        TNumberEdit *Edt_495;
        TPanel *Pan_496;
        TNumberEdit *Edt_496;
        TPanel *Pan_497;
        TNumberEdit *Edt_497;
        TPanel *Pan_498;
        TNumberEdit *Edt_498;
        TPanel *Pan_499;
        TNumberEdit *Edt_499;
        TPanel *Pan_500;
        TNumberEdit *Edt_500;
        TNumberEdit *Edt_460;
        TMediaPlayer *MdPlayer;
        TBitBtn *Button11;
        TBitBtn *Button12;
    TPanel *Panel11;
    TEdit *EdtMEMO;
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormScreenInit(int Opt);
        void __fastcall Edt_001Enter(TObject *Sender);
        void __fastcall Edt_001Exit(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall FieldColor(int i);
        void __fastcall Edt_001Change(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Edt_001KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Toukei();
        void __fastcall DrawGraph();
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button11Enter(TObject *Sender);
        void __fastcall Button11Exit(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button12Enter(TObject *Sender);
        void __fastcall Button12Exit(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
    void __fastcall EdtMEMOChange(TObject *Sender);
private:	// ユーザー宣言
        int CurField;          // Current focus field No
        int CurrentChangeFlag; // Current Filed Change Flag
        int AllChangeFlag;       // All of field change flag
        int KikiType;            // 1: PC1; 2: PC2; 3: PC3; PC4

public:		// ユーザー宣言
        __fastcall TForm3(TComponent* Owner);
        bool __fastcall CSV_Write();
        bool __fastcall Excel_Write();
        AnsiString __fastcall ConvKETA1(int keta,double n);
        AnsiString __fastcall ConvKETA2(int keta,double n,int SGM_K);



protected:
        void __fastcall OnNotifyWriteData(TMessage &Message);
//        void __fastcall OnNotifyWriteData1(TMessage &Message);
BEGIN_MESSAGE_MAP
//        MESSAGE_HANDLER(WM_Notify_WriteData, TMessage, OnNotifyWriteData)
        MESSAGE_HANDLER(WM_Notify_WriteData1, TMessage, OnNotifyWriteData)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
extern const int Nums;
//---------------------------------------------------------------------------
#endif
