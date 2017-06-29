/*
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2017, James Jackson - BYU MAGICC Lab, Provo UT
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef __cplusplus
extern "C" {
#endif
#include <turbotrig/turbotrig.h>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

static const float atan_max_x = 1.000000;
static const float atan_min_x = 0.000000;
static const int16_t atan_num_entries = 500;
static const float atan_scale_factor = 10000.000000;
static const int16_t atan_lookup_table[500] = {
0,	20,	40,	60,	80,	100,	120,	140,	160,	180,
200,	220,	240,	260,	280,	300,	320,	340,	360,	380,
400,	420,	440,	460,	480,	500,	520,	539,	559,	579,
599,	619,	639,	659,	679,	699,	719,	739,	759,	778,
798,	818,	838,	858,	878,	898,	917,	937,	957,	977,
997,	1016,	1036,	1056,	1076,	1096,	1115,	1135,	1155,	1175,
1194,	1214,	1234,	1253,	1273,	1293,	1312,	1332,	1352,	1371,
1391,	1411,	1430,	1450,	1469,	1489,	1508,	1528,	1548,	1567,
1587,	1606,	1626,	1645,	1664,	1684,	1703,	1723,	1742,	1762,
1781,	1800,	1820,	1839,	1858,	1878,	1897,	1916,	1935,	1955,
1974,	1993,	2012,	2032,	2051,	2070,	2089,	2108,	2127,	2146,
2166,	2185,	2204,	2223,	2242,	2261,	2280,	2299,	2318,	2337,
2355,	2374,	2393,	2412,	2431,	2450,	2469,	2487,	2506,	2525,
2544,	2562,	2581,	2600,	2618,	2637,	2656,	2674,	2693,	2712,
2730,	2749,	2767,	2786,	2804,	2823,	2841,	2859,	2878,	2896,
2915,	2933,	2951,	2970,	2988,	3006,	3024,	3043,	3061,	3079,
3097,	3115,	3133,	3151,	3169,	3187,	3206,	3224,	3241,	3259,
3277,	3295,	3313,	3331,	3349,	3367,	3385,	3402,	3420,	3438,
3456,	3473,	3491,	3509,	3526,	3544,	3561,	3579,	3596,	3614,
3631,	3649,	3666,	3684,	3701,	3719,	3736,	3753,	3771,	3788,
3805,	3822,	3839,	3857,	3874,	3891,	3908,	3925,	3942,	3959,
3976,	3993,	4010,	4027,	4044,	4061,	4078,	4095,	4112,	4128,
4145,	4162,	4179,	4195,	4212,	4229,	4245,	4262,	4278,	4295,
4311,	4328,	4344,	4361,	4377,	4394,	4410,	4426,	4443,	4459,
4475,	4491,	4508,	4524,	4540,	4556,	4572,	4588,	4604,	4620,
4636,	4652,	4668,	4684,	4700,	4716,	4732,	4748,	4764,	4779,
4795,	4811,	4827,	4842,	4858,	4874,	4889,	4905,	4920,	4936,
4951,	4967,	4982,	4998,	5013,	5028,	5044,	5059,	5074,	5090,
5105,	5120,	5135,	5150,	5166,	5181,	5196,	5211,	5226,	5241,
5256,	5271,	5286,	5301,	5315,	5330,	5345,	5360,	5375,	5389,
5404,	5419,	5434,	5448,	5463,	5477,	5492,	5507,	5521,	5535,
5550,	5564,	5579,	5593,	5608,	5622,	5636,	5650,	5665,	5679,
5693,	5707,	5721,	5736,	5750,	5764,	5778,	5792,	5806,	5820,
5834,	5848,	5862,	5875,	5889,	5903,	5917,	5931,	5944,	5958,
5972,	5985,	5999,	6013,	6026,	6040,	6053,	6067,	6080,	6094,
6107,	6121,	6134,	6147,	6161,	6174,	6187,	6201,	6214,	6227,
6240,	6253,	6267,	6280,	6293,	6306,	6319,	6332,	6345,	6358,
6371,	6384,	6397,	6409,	6422,	6435,	6448,	6461,	6473,	6486,
6499,	6511,	6524,	6537,	6549,	6562,	6574,	6587,	6599,	6612,
6624,	6637,	6649,	6661,	6674,	6686,	6698,	6711,	6723,	6735,
6747,	6760,	6772,	6784,	6796,	6808,	6820,	6832,	6844,	6856,
6868,	6880,	6892,	6904,	6916,	6928,	6940,	6951,	6963,	6975,
6987,	6998,	7010,	7022,	7033,	7045,	7057,	7068,	7080,	7091,
7103,	7114,	7126,	7137,	7149,	7160,	7171,	7183,	7194,	7205,
7217,	7228,	7239,	7250,	7261,	7273,	7284,	7295,	7306,	7317,
7328,	7339,	7350,	7361,	7372,	7383,	7394,	7405,	7416,	7427,
7438,	7448,	7459,	7470,	7481,	7491,	7502,	7513,	7524,	7534,
7545,	7555,	7566,	7577,	7587,	7598,	7608,	7619,	7629,	7640,
7650,	7660,	7671,	7681,	7691,	7702,	7712,	7722,	7733,	7743,
7753,	7763,	7773,	7783,	7794,	7804,	7814,	7824,	7834,	7844,
};

static const float asin_max_x = 1.000000;
static const float asin_min_x = 0.000000;
static const int16_t asin_num_entries = 500;
static const float asin_scale_factor = 10000.000000;
static const int16_t asin_lookup_table[501] = {
0,	20,	40,	60,	80,	100,	120,	140,	160,	180,
200,	220,	240,	260,	280,	300,	320,	340,	360,	380,
400,	420,	440,	460,	480,	500,	520,	540,	560,	580,
600,	620,	640,	660,	681,	701,	721,	741,	761,	781,
801,	821,	841,	861,	881,	901,	921,	941,	961,	982,
1002,	1022,	1042,	1062,	1082,	1102,	1122,	1142,	1163,	1183,
1203,	1223,	1243,	1263,	1284,	1304,	1324,	1344,	1364,	1384,
1405,	1425,	1445,	1465,	1485,	1506,	1526,	1546,	1566,	1587,
1607,	1627,	1647,	1668,	1688,	1708,	1729,	1749,	1769,	1790,
1810,	1830,	1851,	1871,	1891,	1912,	1932,	1952,	1973,	1993,
2014,	2034,	2054,	2075,	2095,	2116,	2136,	2157,	2177,	2198,
2218,	2239,	2259,	2280,	2300,	2321,	2341,	2362,	2382,	2403,
2424,	2444,	2465,	2486,	2506,	2527,	2547,	2568,	2589,	2610,
2630,	2651,	2672,	2692,	2713,	2734,	2755,	2775,	2796,	2817,
2838,	2859,	2880,	2900,	2921,	2942,	2963,	2984,	3005,	3026,
3047,	3068,	3089,	3110,	3131,	3152,	3173,	3194,	3215,	3236,
3257,	3278,	3300,	3321,	3342,	3363,	3384,	3405,	3427,	3448,
3469,	3490,	3512,	3533,	3554,	3576,	3597,	3618,	3640,	3661,
3683,	3704,	3726,	3747,	3769,	3790,	3812,	3833,	3855,	3876,
3898,	3920,	3941,	3963,	3985,	4006,	4028,	4050,	4072,	4093,
4115,	4137,	4159,	4181,	4203,	4225,	4246,	4268,	4290,	4312,
4334,	4357,	4379,	4401,	4423,	4445,	4467,	4489,	4511,	4534,
4556,	4578,	4601,	4623,	4645,	4668,	4690,	4712,	4735,	4757,
4780,	4802,	4825,	4848,	4870,	4893,	4916,	4938,	4961,	4984,
5007,	5029,	5052,	5075,	5098,	5121,	5144,	5167,	5190,	5213,
5236,	5259,	5282,	5305,	5329,	5352,	5375,	5398,	5422,	5445,
5469,	5492,	5515,	5539,	5562,	5586,	5610,	5633,	5657,	5681,
5704,	5728,	5752,	5776,	5800,	5824,	5848,	5872,	5896,	5920,
5944,	5968,	5992,	6016,	6041,	6065,	6089,	6114,	6138,	6163,
6187,	6212,	6236,	6261,	6286,	6311,	6335,	6360,	6385,	6410,
6435,	6460,	6485,	6510,	6535,	6561,	6586,	6611,	6637,	6662,
6687,	6713,	6739,	6764,	6790,	6816,	6841,	6867,	6893,	6919,
6945,	6971,	6997,	7023,	7050,	7076,	7102,	7129,	7155,	7182,
7208,	7235,	7262,	7288,	7315,	7342,	7369,	7396,	7423,	7450,
7478,	7505,	7532,	7560,	7587,	7615,	7643,	7670,	7698,	7726,
7754,	7782,	7810,	7838,	7867,	7895,	7923,	7952,	7981,	8009,
8038,	8067,	8096,	8125,	8154,	8183,	8213,	8242,	8271,	8301,
8331,	8360,	8390,	8420,	8450,	8481,	8511,	8541,	8572,	8602,
8633,	8664,	8695,	8726,	8757,	8788,	8820,	8851,	8883,	8915,
8947,	8979,	9011,	9043,	9076,	9108,	9141,	9174,	9207,	9240,
9273,	9306,	9340,	9374,	9407,	9442,	9476,	9510,	9545,	9579,
9614,	9649,	9684,	9720,	9755,	9791,	9827,	9863,	9900,	9936,
9973,	10010,	10047,	10084,	10122,	10160,	10198,	10236,	10275,	10314,
10353,	10392,	10432,	10471,	10512,	10552,	10593,	10634,	10675,	10717,
10759,	10801,	10844,	10886,	10930,	10973,	11018,	11062,	11107,	11152,
11198,	11244,	11290,	11337,	11385,	11433,	11481,	11530,	11580,	11630,
11681,	11732,	11784,	11837,	11890,	11944,	11999,	12054,	12111,	12168,
12226,	12285,	12346,	12407,	12469,	12532,	12597,	12663,	12730,	12799,
12870,	12942,	13017,	13093,	13171,	13252,	13336,	13423,	13513,	13606,
13705,	13808,	13917,	14033,	14157,	14293,	14442,	14612,	14813,	15075,
15708
};


int32_t sign(int32_t y)
{
  return (0 < y) - (y < 0);
}

float fsign(float y)
{
  return (0.0 < y) - (y < 0.0);
}

float asin_approx(float x)
{
  return turboasin(x);
}


float turboatan(float x)
{
  // atan is symmetric
  if (x < 0)
  {
    return -1.0*turboatan(-1.0*x);
  }
  // This uses a sweet identity to wrap the domain of atan onto (0,1)
  if (x > 1.0)
  {
    return M_PI/2.0 - turboatan(1.0/x);
  }

  float t = (x - atan_min_x)/(float)(atan_max_x - atan_min_x) * (float)atan_num_entries;
  int16_t index = (int)t;
  float dx = t - index;

  if (index >= atan_num_entries)
      return atan_lookup_table[atan_num_entries-1]/atan_scale_factor;
  else if (index < atan_num_entries - 1)
      return atan_lookup_table[index]/atan_scale_factor + dx * (atan_lookup_table[index + 1] - atan_lookup_table[index])/atan_scale_factor;
  else
      return atan_lookup_table[index]/atan_scale_factor + dx * (atan_lookup_table[index] - atan_lookup_table[index - 1])/atan_scale_factor;
}


float atan2_approx(float y, float x)
{
  // algorithm from wikipedia: https://en.wikipedia.org/wiki/Atan2
  if (x == 0.0)
  {
    if (y < 0.0)
    {
      return - M_PI/2.0;
    }
    else if ( y > 0.0)
    {
      return M_PI/2.0;
    }
    else
    {
      return 0.0;
    }
  }

  float arctan = turboatan(y/x);

  if (x < 0.0)
  {
    if ( y < 0)
    {
      return arctan - M_PI;
    }
    else
    {
      return arctan + M_PI;
    }
  }

  else
  {
      return arctan;
  }
}


int32_t turboatan_taylor(int32_t x)
{
  if (x > 1000)
  {
    return 1571-turboatan(1000000/x);
  }

  return (972*x/1000) - (((191*x*x)/1000)*x)/(1000*1000); // the weird order of operations is to prevent overflow
}


int32_t turbocos(int32_t x)
{
  return turbosin(x + 1571);
}


int32_t turbosin(int32_t x)
{
  // wrap to +/- PI
  if (x < -3142)
    x += 6283;
  else if (x >  3142)
    x -= 6283;

  if (x < 0)
  {
    return (1273 * x)/1000 + (405 * x * x)/(1000000);
  }
  else
  {
    return (1273 * x)/1000 - (405 * x * x)/(1000000);
  }

  return x;
}


float turboasin(float x)
{
  if (x < 0.0)
  {
    return -1.0*turboasin(-1.0*x);
  }

  float t = (x - asin_min_x)/(float)(asin_max_x - asin_min_x) * (float)asin_num_entries;
  int16_t index = (int)t;
  float dx = t - index;

  if (index >= asin_num_entries)
      return asin_lookup_table[500]/asin_scale_factor;
  else if (index < asin_num_entries - 1)
      return asin_lookup_table[index]/asin_scale_factor + dx * (asin_lookup_table[index + 1] - asin_lookup_table[index])/asin_scale_factor;
  else
      return asin_lookup_table[index]/asin_scale_factor + dx * (asin_lookup_table[index] - asin_lookup_table[index - 1])/asin_scale_factor;
}
#ifdef __cplusplus
}
#endif
