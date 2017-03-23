/* VEST-4 core accumulator input and output bit permutations */

static const vest_core_inputs	vest_4_structure[vest_4_bits] =
{
	{  0,  1,  2,  3,  4, 52},	/*  0 */
	{  0,  1,  2,  3,  4, 12},	/*  1 */
	{  0,  1,  2,  3,  4, 65},	/*  2 */
	{  0,  1,  2,  3,  4, 77},	/*  3 */
	{  0,  1,  2,  3,  4, 55},	/*  4 */
	{  4,  4,  1,  3,  2, 80},	/*  5 */
	{  5,  5,  0,  4,  3, 70},	/*  6 */
	{  1,  1,  3,  2,  6, 54},	/*  7 */
	{  2,  2,  7,  0,  6, 49},	/*  8 */
	{  3,  3,  7,  2,  6, 21},	/*  9 */
	{  5,  6,  2,  0,  3, 37},	/* 10 */
	{  4,  5,  1,  7,  8, 20},	/* 11 */
	{  9,  8,  6,  5,  7, 42},	/* 12 */
	{ 10,  5,  6,  4,  7, 22},	/* 13 */
	{  8, 12,  7,  5, 10, 73},	/* 14 */
	{  7, 11, 14, 10,  5, 74},	/* 15 */
	{ 13,  4,  8,  3,  1, 31},	/* 16 */
	{  5, 13,  9, 16, 15, 58},	/* 17 */
	{  8, 17,  6,  7,  9, 82},	/* 18 */
	{ 18,  5, 14,  8, 11, 13},	/* 19 */
	{  2, 16, 18,  9,  3, 11},	/* 20 */
	{ 15,  3, 13, 10, 16, 36},	/* 21 */
	{  7, 18, 15,  9,  5,  0},	/* 22 */
	{ 22,  5, 19, 11, 14, 38},	/* 23 */
	{ 18, 15, 17,  5, 20, 32},	/* 24 */
	{ 24, 21, 18, 14,  8, 50},	/* 25 */
	{  9, 16, 17, 15, 22, 71},	/* 26 */
	{ 25, 13, 21, 15, 10, 45},	/* 27 */
	{ 27, 22, 25, 15, 11, 79},	/* 28 */
	{ 16, 19, 22,  1, 23, 43},	/* 29 */
	{ 26, 18, 24, 16, 20, 61},	/* 30 */
	{ 10, 30, 15,  0, 14, 24},	/* 31 */
	{ 31, 27, 25, 28, 15, 23},	/* 32 */
	{ 20, 17, 26, 24, 16,  6},	/* 33 */
	{ 18, 24, 21, 25, 27, 53},	/* 34 */
	{ 30, 24, 20, 26, 18, 29},	/* 35 */
	{ 35, 34, 29, 25, 19,  7},	/* 36 */
	{ 29,  5, 31, 28, 19, 62},	/* 37 */
	{ 19, 18, 36, 35,  6, 75},	/* 38 */
	{ 26, 33,  5, 17, 37, 14},	/* 39 */
	{ 39, 20, 37, 29, 23, 68},	/* 40 */
	{ 40, 30, 31, 33, 32, 60},	/* 41 */
	{ 19, 34, 28, 36, 25, 30},	/* 42 */
	{ 33, 39, 42, 32, 26, 69},	/* 43 */
	{ 24, 25,  4, 28, 42, 59},	/* 44 */
	{ 44, 41, 38, 12,  9, 17},	/* 45 */
	{ 36, 42, 39, 40, 33, 27},	/* 46 */
	{ 10, 43, 46, 32, 30,  2},	/* 47 */
	{ 32, 43, 41, 37, 39, 35},	/* 48 */
	{ 48, 47, 45, 43, 32, 28},	/* 49 */
	{ 37, 46, 40, 43, 47, 64},	/* 50 */
	{ 48, 27, 31, 37, 28,  9},	/* 51 */
	{ 38, 51, 26, 35, 41, 81},	/* 52 */
	{ 35, 52, 46, 42, 33, 16},	/* 53 */
	{ 27, 24, 48, 17, 25, 72},	/* 54 */
	{ 23, 51, 48, 44, 38, 10},	/* 55 */
	{ 41, 40, 49, 45, 39,  3},	/* 56 */
	{ 56, 39, 29, 36, 42, 67},	/* 57 */
	{ 50, 54, 40, 57, 56, 19},	/* 58 */
	{ 33, 36, 18, 40, 39, 44},	/* 59 */
	{ 21, 47, 59, 40, 13, 26},	/* 60 */
	{ 28, 57, 27, 58, 54,  4},	/* 61 */
	{ 61, 55, 56, 45, 48, 76},	/* 62 */
	{ 54, 62, 56, 61, 46, 41},	/* 63 */
	{  1, 49,  5, 38, 59, 34},	/* 64 */
	{ 64, 53, 51, 58, 48, 39},	/* 65 */
	{ 53, 22, 44, 41, 11, 57},	/* 66 */
	{ 60, 63, 34, 66, 49, 78},	/* 67 */
	{ 56, 52, 50, 57, 63, 33},	/* 68 */
	{ 58, 50, 57, 65, 68, 47},	/* 69 */
	{ 67, 64, 61, 57, 63, 15},	/* 70 */
	{ 70, 34, 67, 60, 66, 48},	/* 71 */
	{ 65, 48, 13, 51, 69, 63},	/* 72 */
	{ 72, 69, 66, 62, 55, 18},	/* 73 */
	{ 17, 69, 52, 51, 48,  1},	/* 74 */
	{ 59, 71, 68, 64, 63,  8},	/* 75 */
	{ 66, 60, 73, 71, 59, 46},	/* 76 */
	{ 76, 74, 53, 51, 60, 25},	/* 77 */
	{ 75, 74, 72, 12, 76, 40},	/* 78 */
	{ 76, 75, 58, 68, 77, 66},	/* 79 */
	{ 75, 68, 79, 73, 78, 51},	/* 80 */
	{ 68, 79, 73, 47, 77, 56},	/* 81 */
	{ 81, 76, 78, 79, 80,  5},	/* 82 */
};

/* VEST-4 root cipher family */

static const u32	provest_4[vest_4_family_words] =
{
	/* RNS counters indexes (rns) */
	  0, 16, 17, 18,  1, 19, 20,  2, 21, 22, 23, 24, 25, 26, 27, 28,
	
	/* Feedback functions indexes (vest_f) */
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
	
	/* Input bit permutation indexes (p5) */
	  0, 86, 69, 83, 84, 45, 52, 32, 67,105,112,104,101,114, 32, 70, 97,109,105,108,
	121, 32, 84,114,101,101, 10, 68,101,115,105,103,110,101,100, 32, 98,121, 32, 83,
	101, 97,110, 32, 79, 39, 78,101,105,108, 10, 67, 66, 32, 67, 97,112,105,116, 97,
	108, 32, 77, 97,110, 97,103,101,109,101,110,116, 32, 83, 46, 65, 46,  0
};
