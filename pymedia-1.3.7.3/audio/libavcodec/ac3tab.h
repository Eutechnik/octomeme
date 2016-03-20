/* tables taken directly from AC3 spec */

/* possible frequencies */
const UINT16 ac3_freqs[3] = { 48000, 44100, 32000 };

/* possible bitrates */
const UINT16 ac3_bitratetab[19] = {
    32, 40, 48, 56, 64, 80, 96, 112, 128, 
    160, 192, 224, 256, 320, 384, 448, 512, 576, 640 
};

/* AC3 MDCT window */

/* MDCT window */
const INT16 ac3_window[256] = {
    4,    7,   12,   16,   21,   28,   34,   42,
   51,   61,   72,   84,   97,  111,  127,  145,
  164,  184,  207,  231,  257,  285,  315,  347,
  382,  419,  458,  500,  544,  591,  641,  694,
  750,  810,  872,  937, 1007, 1079, 1155, 1235,
 1318, 1406, 1497, 1593, 1692, 1796, 1903, 2016,
 2132, 2253, 2379, 2509, 2644, 2783, 2927, 3076,
 3230, 3389, 3552, 3721, 3894, 4072, 4255, 4444,
 4637, 4835, 5038, 5246, 5459, 5677, 5899, 6127,
 6359, 6596, 6837, 7083, 7334, 7589, 7848, 8112,
 8380, 8652, 8927, 9207, 9491, 9778,10069,10363,
10660,10960,11264,11570,11879,12190,12504,12820,
13138,13458,13780,14103,14427,14753,15079,15407,
15735,16063,16392,16720,17049,17377,17705,18032,
18358,18683,19007,19330,19651,19970,20287,20602,
20914,21225,21532,21837,22139,22438,22733,23025,
23314,23599,23880,24157,24430,24699,24964,25225,
25481,25732,25979,26221,26459,26691,26919,27142,
27359,27572,27780,27983,28180,28373,28560,28742,
28919,29091,29258,29420,29577,29729,29876,30018,
30155,30288,30415,30538,30657,30771,30880,30985,
31086,31182,31274,31363,31447,31528,31605,31678,
31747,31814,31877,31936,31993,32046,32097,32145,
32190,32232,32272,32310,32345,32378,32409,32438,
32465,32490,32513,32535,32556,32574,32592,32608,
32623,32636,32649,32661,32671,32681,32690,32698,
32705,32712,32718,32724,32729,32733,32737,32741,
32744,32747,32750,32752,32754,32756,32757,32759,
32760,32761,32762,32763,32764,32764,32765,32765,
32766,32766,32766,32766,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,
32767,32767,32767,32767,32767,32767,32767,32767,  
};

static UINT8 masktab[253];

static const UINT8 latab[260]= {
0x0040,0x003f,0x003e,0x003d,0x003c,0x003b,0x003a,0x0039,0x0038,0x0037,
0x0036,0x0035,0x0034,0x0034,0x0033,0x0032,0x0031,0x0030,0x002f,0x002f,
0x002e,0x002d,0x002c,0x002c,0x002b,0x002a,0x0029,0x0029,0x0028,0x0027,
0x0026,0x0026,0x0025,0x0024,0x0024,0x0023,0x0023,0x0022,0x0021,0x0021,
0x0020,0x0020,0x001f,0x001e,0x001e,0x001d,0x001d,0x001c,0x001c,0x001b,
0x001b,0x001a,0x001a,0x0019,0x0019,0x0018,0x0018,0x0017,0x0017,0x0016,
0x0016,0x0015,0x0015,0x0015,0x0014,0x0014,0x0013,0x0013,0x0013,0x0012,
0x0012,0x0012,0x0011,0x0011,0x0011,0x0010,0x0010,0x0010,0x000f,0x000f,
0x000f,0x000e,0x000e,0x000e,0x000d,0x000d,0x000d,0x000d,0x000c,0x000c,
0x000c,0x000c,0x000b,0x000b,0x000b,0x000b,0x000a,0x000a,0x000a,0x000a,
0x000a,0x0009,0x0009,0x0009,0x0009,0x0009,0x0008,0x0008,0x0008,0x0008,
0x0008,0x0008,0x0007,0x0007,0x0007,0x0007,0x0007,0x0007,0x0006,0x0006,
0x0006,0x0006,0x0006,0x0006,0x0006,0x0006,0x0005,0x0005,0x0005,0x0005,
0x0005,0x0005,0x0005,0x0005,0x0004,0x0004,0x0004,0x0004,0x0004,0x0004,
0x0004,0x0004,0x0004,0x0004,0x0004,0x0003,0x0003,0x0003,0x0003,0x0003,
0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0003,0x0002,
0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,
0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0002,0x0001,0x0001,
0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};

static const UINT16 hth[50][3]= {
{ 0x04d0,0x04f0,0x0580 },
{ 0x04d0,0x04f0,0x0580 },
{ 0x0440,0x0460,0x04b0 },
{ 0x0400,0x0410,0x0450 },
{ 0x03e0,0x03e0,0x0420 },
{ 0x03c0,0x03d0,0x03f0 },
{ 0x03b0,0x03c0,0x03e0 },
{ 0x03b0,0x03b0,0x03d0 },
{ 0x03a0,0x03b0,0x03c0 },
{ 0x03a0,0x03a0,0x03b0 },
{ 0x03a0,0x03a0,0x03b0 },
{ 0x03a0,0x03a0,0x03b0 },
{ 0x03a0,0x03a0,0x03a0 },
{ 0x0390,0x03a0,0x03a0 },
{ 0x0390,0x0390,0x03a0 },
{ 0x0390,0x0390,0x03a0 },
{ 0x0380,0x0390,0x03a0 },
{ 0x0380,0x0380,0x03a0 },
{ 0x0370,0x0380,0x03a0 },
{ 0x0370,0x0380,0x03a0 },
{ 0x0360,0x0370,0x0390 },
{ 0x0360,0x0370,0x0390 },
{ 0x0350,0x0360,0x0390 },
{ 0x0350,0x0360,0x0390 },
{ 0x0340,0x0350,0x0380 },
{ 0x0340,0x0350,0x0380 },
{ 0x0330,0x0340,0x0380 },
{ 0x0320,0x0340,0x0370 },
{ 0x0310,0x0320,0x0360 },
{ 0x0300,0x0310,0x0350 },
{ 0x02f0,0x0300,0x0340 },
{ 0x02f0,0x02f0,0x0330 },
{ 0x02f0,0x02f0,0x0320 },
{ 0x02f0,0x02f0,0x0310 },
{ 0x0300,0x02f0,0x0300 },
{ 0x0310,0x0300,0x02f0 },
{ 0x0340,0x0320,0x02f0 },
{ 0x0390,0x0350,0x02f0 },
{ 0x03e0,0x0390,0x0300 },
{ 0x0420,0x03e0,0x0310 },
{ 0x0460,0x0420,0x0330 },
{ 0x0490,0x0450,0x0350 },
{ 0x04a0,0x04a0,0x03c0 },
{ 0x0460,0x0490,0x0410 },
{ 0x0440,0x0460,0x0470 },
{ 0x0440,0x0440,0x04a0 },
{ 0x0520,0x0480,0x0460 },
{ 0x0800,0x0630,0x0440 },
{ 0x0840,0x0840,0x0450 },
{ 0x0840,0x0840,0x04e0 },
};

static const UINT8 baptab[64]= {
    0, 1, 1, 1, 1, 1, 2, 2, 3, 3, 
    3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 
    7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 
    9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 
    12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 
    14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 
    15, 15, 15, 15,
};

const UINT8 sdecaytab[4]={ 
    0x0f, 0x11, 0x13, 0x15,
};

const UINT8 fdecaytab[4]={ 
    0x3f, 0x53, 0x67, 0x7b, 
};

const UINT16 sgaintab[4]= { 
    0x540, 0x4d8, 0x478, 0x410,
};

const UINT16 dbkneetab[4]= { 
    0x000, 0x700, 0x900, 0xb00,
};

const UINT16 floortab[8]= { 
    0x2f0, 0x2b0, 0x270, 0x230, 0x1f0, 0x170, 0x0f0, 0xf800,
};

const UINT16 fgaintab[8]= {
    0x080, 0x100, 0x180, 0x200, 0x280, 0x300, 0x380, 0x400,
};

static const UINT8 bndsz[50]={
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 
    3, 6, 6, 6, 6, 6, 6, 12, 12, 12, 12, 24, 24, 24, 24, 24 
};

static UINT8 bndtab[51]; 

/* fft & mdct sin cos tables */
static INT16 costab[64];
static INT16 sintab[64];
static INT16 fft_rev[512];
static INT16 xcos1[128];
static INT16 xsin1[128];

static UINT16 crc_table[256];
