#include "main.h"
#define SOC_05_VALUE 936000//1800000
//======================放电表=======================
#define D_TempArrSize 7
static uint8_t DSGCaliFlaG= 0;
uint16_t CutCapValue= 0;
static uint8_t D_TempArr[D_TempArrSize]={25,30,35,40,45,50,65};

//放电 0.33
static uint16_t D_33Region[D_TempArrSize][21]={
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
//	{3092,2917,2917,2917,2912,2907,2899,2891,2880,2866,2848,2825,2794,2756,2709,2655,2594,2528,2456,2381,2300},
//	{3193,2998,2998,2995,2991,2985,2978,2970,2960,2949,2935,2916,2890,2855,2809,2750,2679,2597,2506,2407,2300},
//	{3219,3083,3083,3081,3077,3071,3065,3059,3051,3041,3030,3015,2995,2964,2919,2855,2770,2669,2557,2435,2300},
//	{3316,3146,3145,3142,3138,3131,3126,3120,3114,3107,3098,3089,3077,3062,3040,3005,2943,2841,2691,2510,2300},
//	{3380,3187,3184,3180,3174,3169,3161,3155,3149,3142,3135,3126,3116,3102,3083,3051,2993,2886,2725,2531,2300},
//	{3360,3222,3219,3215,3209,3203,3197,3192,3185,3180,3174,3168,3160,3150,3138,3121,3097,3055,2953,2705,2300},

{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}

//	#if((PROJECTCODE==BLX_48T30)||(PROJECTCODE==BLX_4824))
//		{3306,3291,3290,3288,3286,3282,3275,3266,3258,3253,3249,3246,3241,3235,3226,3215,3200,3179,3153,3137,2507},
//		{3306,3291,3290,3288,3286,3282,3275,3266,3258,3253,3249,3246,3241,3235,3226,3215,3200,3179,3153,3137,2507}
//	#else
//		{3429,3429,3242,3240,3236,3230,3223,3217,3211,3206,3201,3196,3189,3181,3172,3161,3144,3120,3079,2984,2746},
//		{3383,3383,3273,3273,3270,3267,3261,3253,3245,3239,3234,3230,3226,3220,3213,3203,3191,3173,3148,3123,3044}
//#endif
};

//放电0.5C
static uint16_t D_50Region[D_TempArrSize][21]={ 
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
//	{3066,2909,2907,2907,2903,2896,2888,2877,2863,2844,2819,2789,2752,2710,2663,2611,2556,2498,2436,2370,2300},
//	{3100,2997,2997,2997,2991,2985,2977,2967,2955,2939,2918,2889,2852,2807,2752,2691,2623,2552,2475,2391,2300},
//	{3220,3081,3083,3083,3080,3076,3071,3064,3056,3046,3034,3018,2997,2966,2920,2855,2771,2670,2559,2438,2300},
//	{3308,3124,3122,3119,3114,3107,3100,3092,3084,3074,3061,3046,3024,2993,2948,2885,2801,2700,2586,2456,2300},
//	{3291,3182,3181,3177,3173,3167,3162,3154,3148,3142,3134,3125,3115,3101,3082,3055,3007,2913,2759,2557,2300},

{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}	

//	#if((PROJECTCODE==BLX_48T30)||(PROJECTCODE==BLX_4824))
//		{3299,3277,3276,3274,3271,3267,3260,3252,3246,3241,3237,3233,3228,3221,3213,3201,3187,3166,3142,3124,2504},
//		{3299,3277,3276,3274,3271,3267,3260,3252,3246,3241,3237,3233,3228,3221,3213,3201,3187,3166,3142,3124,2504}
//	#else
//	{3359,3359,3212,3210,3206,3200,3194,3188,3181,3175,3168,3161,3152,3141,3127,3106,3076,3022,2919,2762,2567},
//	{3383,3383,3255,3253,3249,3245,3239,3232,3226,3220,3215,3209,3204,3197,3189,3177,3163,3143,3117,3074,2918}
//	#endif
};

//放电1C
static uint16_t D_100Region[D_TempArrSize][21]={ 
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
//	{2905,2810,2830,2848,2861,2868,2870,2867,2860,2848,2830,2804,2770,2728,2678,2622,2562,2500,2435,2368,2300},
//	{2981,2887,2907,2924,2934,2940,2941,2939,2932,2922,2906,2882,2849,2804,2748,2682,2611,2538,2463,2384,2300},
//	{3109,2984,2994,3004,3009,3011,3009,3006,3000,2992,2982,2968,2950,2924,2885,2825,2741,2640,2531,2418,2300},
//	{3138,3028,3034,3040,3042,3042,3038,3033,3027,3019,3008,2994,2975,2948,2908,2847,2761,2658,2547,2430,2300},
//	{3204,3101,3104,3104,3103,3100,3096,3089,3084,3077,3069,3060,3048,3033,3013,2986,2942,2863,2723,2533,2300},

{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}
	
//#if(FACTURECODE==GTDS_FAC_ND) 
//	#if(PROJECTCODE==ND_4824)

//	{3227,3140,3141,3141,3139,3135,3131,3127,3120,3114,3106,3097,3086,3071,3052,3026,2987,2916,2779,2577,2300},
//	{3261,3163,3159,3158,3157,3156,3154,3151,3148,3144,3139,3133,3126,3119,3110,3098,3083,3062,3019,2901,2378}
//	#elif(PROJECTCODE==ND_4820)
//	{3227,3140,3141,3141,3139,3135,3131,3127,3120,3114,3106,3097,3086,3071,3052,3026,2987,2916,2779,2577,2300},
//	{3332,3201,3206,3203,3200,3196,3191,3186,3180,3175,3169,3163,3155,3146,3134,3120,3103,3082,3040,2972,2500}
//	#elif(PROJECTCODE==ND_4816)
//	{3227,3140,3141,3141,3139,3135,3131,3127,3120,3114,3106,3097,3086,3071,3052,3026,2987,2916,2779,2577,2300},
//	{3322,3268,3265,3261,3255,3248,3240,3233,3227,3220,3214,3209,3204,3197,3190,3179,3166,3146,3120,3080,2766}
//	#else
//	{3227,3140,3141,3141,3139,3135,3131,3127,3120,3114,3106,3097,3086,3071,3052,3026,2987,2916,2779,2577,2300},
//	{3332,3201,3206,3203,3200,3196,3191,3186,3180,3175,3169,3163,3155,3146,3134,3120,3103,3082,3040,2972,2500}
//	#endif
//#elif(FACTURECODE==GTDS_FAC_BLX) 
//	#if(PROJECTCODE==BLX_48T30)
//	{3299,3262,3261,3259,3256,3252,3245,3234,3229,3225,3220,3215,3209,3201,3191,3178,3159,3136,3117,3032,2504},
//	{3299,3262,3261,3259,3256,3252,3245,3234,3229,3225,3220,3215,3209,3201,3191,3178,3159,3136,3117,3032,2504}
//	#elif((PROJECTCODE==BLX_48T20)||(PROJECTCODE==BLX_48Z20))
//	{3326,3257,3255,3252,3248,3244,3239,3233,3228,3223,3219,3214,3208,3199,3189,3177,3160,3138,3111,3050,2667},
//	{3326,3257,3255,3252,3248,3244,3239,3233,3228,3223,3219,3214,3208,3199,3189,3177,3160,3138,3111,3050,2667}
//	#elif(PROJECTCODE==BLX_4824)
//	{3253,3233,3228,3226,3223,3219,3215,3210,3216,3212,3208,3203,3198,3193,3183,3170,3143,3123,3102,3058,2703},
//	{3253,3233,3228,3226,3223,3219,3215,3210,3216,3212,3208,3203,3198,3193,3183,3170,3143,3123,3102,3058,2703}
//	#else	
//	{3253,3233,3228,3226,3223,3219,3215,3210,3216,3212,3208,3203,3198,3193,3183,3170,3143,3123,3102,3058,2703},
//	{3253,3233,3228,3226,3223,3219,3215,3210,3216,3212,3208,3203,3198,3193,3183,3170,3143,3123,3102,3058,2703}
//	#endif
//#else

//	{3227,3140,3141,3141,3139,3135,3131,3127,3120,3114,3106,3097,3086,3071,3052,3026,2987,2916,2779,2577,2300},
//	{3332,3201,3206,3203,3200,3196,3191,3186,3180,3175,3169,3163,3155,3146,3134,3120,3103,3082,3040,2972,2500}
//#endif
};

//======================充电表=======================
#define C_TempArrSize 4
static uint8_t C_TempArr[C_TempArrSize]={40,45,50,65};

//充电 0.33
static uint16_t C_33Region[C_TempArrSize][21]={
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}
//{3650,3649,3612,3569,3543,3524,3509,3497,3487,3479,3471,3463,3457,3452,3446,3439,3425,3402,3379,3326,2687},
//{3650,3649,3549,3507,3484,3470,3458,3449,3442,3434,3426,3418,3411,3405,3401,3396,3380,3354,3328,3283,2765},
//{3650,3517,3472,3454,3443,3435,3429,3423,3417,3410,3402,3395,3391,3387,3385,3377,3359,3334,3311,3262,2809},
//{3649,3455,3428,3417,3410,3406,3402,3398,3390,3381,3372,3367,3363,3361,3358,3351,3332,3306,3281,3238,2812}
};

//充电0.5C
static uint16_t C_50Region[C_TempArrSize][21]={ 
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}
//{3650,3649,3641,3590,3560,3539,3523,3509,3498,3489,3480,3473,3466,3461,3456,3450,3438,3419,3395,3369,3042},
//{3650,3649,3641,3590,3560,3539,3523,3509,3498,3489,3480,3473,3466,3461,3456,3450,3438,3419,3395,3369,3042},
//{3650,3649,3567,3525,3502,3487,3475,3465,3457,3449,3441,3434,3427,3422,3418,3412,3399,3376,3350,3322,2972},
////{3649,3496,3459,3442,3433,3426,3421,3415,3408,3401,3393,3387,3382,3379,3376,3369,3351,3324,3299,3253,2818} 
//{3630,3482,3448,3433,3425,3419,3415,3404,3397,3396,3390,3386,3383,3381,3379,3370,3352,3326,3304,3232,2818}
};

//======================静态表=======================
//温度系数
static uint16_t TempTable[5][2]={
{20,76},
{30,85},
{40,92},
{50,97},
{65,100}};
//低温静态表
#define K_TempArrSize 8
static uint8_t K_TempArr[K_TempArrSize]={20,25,30,35,40,45,50,65};
static uint16_t K_Region[K_TempArrSize][21]={
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}, 
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}, 
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}, 
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}, 
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}, 
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400},
	{4200,4120,4066,4010,3956,3907,3861,3815,3773,3737,3691,3657,3636,3619,3607,3589,3569,3536,3497,3447,3400}
};
/*
static uint16_t K_Region[K_TempArrSize][21]={
//#if(FACTURECODE==GTDS_FAC_ND) 
#if(FACTURECODE==GTDS_FAC_BLX) 
	{3316,3218,3214,3210,3210,3198,3191,3184,3177,3170,3162,3152,3138,3118,3088,3037,2950,2813,2632,2589,2500}, 
	{3434,3258,3255,3252,3246,3239,3231,3223,3215,3208,3202,3195,3186,3174,3156,3129,3079,2991,2789,2503,2500}, 
	{3439,3282,3280,3277,3273,3266,3258,3249,3242,3237,3232,3227,3220,3212,3199,3178,3144,3078,2936,2652,2502}, 
	{3427,3297,3296,3294,3291,3286,3277,3266,3258,3254,3252,3248,3244,3238,3229,3216,3196,3168,3141,3044,2501}, 
	{3491,3305,3305,3304,3301,3297,3290,3277,3267,3263,3260,3258,3254,3249,3239,3227,3208,3182,3157,3081,2502}, 
	{3484,3330,3328,3326,3325,3320,3319,3317,3315,3310,3295,3288,3271,3268,3257,3240,3223,3198,3180,3102,2900},
	{3484,3330,3328,3326,3325,3320,3319,3317,3315,3310,3295,3288,3271,3268,3257,3240,3223,3198,3180,3102,2900},
	{3484,3330,3328,3326,3325,3320,3319,3317,3315,3310,3295,3288,3271,3268,3257,3240,3223,3198,3180,3102,2900}
#else 
	{3316,3218,3214,3210,3210,3198,3191,3184,3177,3170,3162,3152,3138,3118,3088,3037,2950,2813,2632,2589,2500}, 
	{3434,3258,3255,3252,3246,3239,3231,3223,3215,3208,3202,3195,3186,3174,3156,3129,3079,2991,2789,2503,2500}, 
	{3439,3282,3280,3277,3273,3266,3258,3249,3242,3237,3232,3227,3220,3212,3199,3178,3144,3078,2936,2652,2502}, 
	{3427,3297,3296,3294,3291,3286,3277,3266,3258,3254,3252,3248,3244,3238,3229,3216,3196,3168,3141,3044,2501}, 
	{3491,3305,3305,3304,3301,3297,3290,3277,3267,3263,3260,3258,3254,3249,3239,3227,3208,3182,3157,3081,2502}, 
	{3441,3310,3311,3310,3309,3306,3300,3285,3273,3269,3267,3265,3262,3257,3250,3234,3216,3192,3171,3103,2900}, 
	{3450,3314,3314,3314,3312,3310,3306,3293,3278,3273,3271,3269,3266,3261,3252,3237,3220,3196,3175,3106,2900}, 
	{3484,3320,3318,3317,3316,3314,3312,3302,3283,3278,3275,3273,3271,3268,3257,3240,3223,3198,3180,3102,2900}
#endif 
};
*/


//ZHQL_1013
//查电压表求soc
uint16_t Get_TableV_SOC(uint8_t AverageTemperature,uint8_t* TempArr,uint8_t TempArrSize,uint16_t SingVol,uint16_t* VolCorrect)
{
	uint8_t	t_i= 0;
	uint8_t	v_i=0;
	int16_t VoltValue= 0;
	int16_t VoltValueH= 0;
	int16_t SOCvalue= 0;
	
	//printf("AverageTemperature=%d\r\n",AverageTemperature);		//AverageTemperature=27
	//printf("SingVol=%d\r\n",SingVol);		//SingVol=4165
	
	//查找温度区间
	for(t_i=0;t_i<TempArrSize;t_i++)		//T=27 --> t_i=2
	{
		if(AverageTemperature<TempArr[t_i])
		{
			break;
		}
	}
	for(v_i= 0;v_i<21;v_i++)
	{

		if(t_i==0)
		{
			VoltValue=(int16_t)VolCorrect[t_i*21+v_i];
			if(v_i>0)
			{
				VoltValueH=(int16_t)VolCorrect[t_i*21+v_i-1];
			}
			else
			{
				VoltValueH=(int16_t)VolCorrect[t_i*21+v_i];
			}
		}
		else
		{
			if(v_i>0)
			{
				VoltValueH= (int16_t)VolCorrect[(t_i-1)*21+v_i-1];	
				//DBG_PRINTF("VoltValueH=%d\r\n",VoltValueH);
			}
			else
			{
				VoltValueH= (int16_t)VolCorrect[(t_i-1)*21+v_i];
				//DBG_PRINTF("VoltValueH=%d\r\n",VoltValueH);		
			}
			VoltValue=(int16_t)VolCorrect[(t_i-1)*21+v_i];
			//DBG_PRINTF("VoltValue=%d\r\n",VoltValue);		
		}
		if(SingVol>VoltValue)
		{
			break;
		}
	}
	if(v_i== 0)
	{
		SOCvalue=100;
	}
	else	if(v_i<=20)
	{
		if(VoltValueH>VoltValue)
		{
			SOCvalue= (20-v_i)*5+(5*(SingVol-VoltValue)/(VoltValueH-VoltValue));
		}
		else
		{
			SOCvalue= 100;
		}
	}
	else
	{
		SOCvalue=0;
	}
	
	//GT_SOC_SET_TEMP(( u32 )( ( GT_SOC_GET_FULL()* SOCvalue / 100L ) ));
	return (uint16_t)SOCvalue;
}


//查温度表求soc
uint16_t Get_TableT_Coefficient(uint8_t AverageTemperature )
{
	uint8_t	i= 0;
	uint16_t Powervalue= 1050;
	uint16_t SOCH= 0;
	uint16_t SOCL= 0;
	uint16_t T_H= 0;
	uint16_t T_L= 0;
	uint16_t DelTSOC= 0;
	for(i= 0;i<5;i++)
	{
		if(AverageTemperature<TempTable[i][0])
		{
			if(i>0)
			{
				T_L= TempTable[i-1][0];
				T_H= TempTable[i][0];
				SOCL= TempTable[i-1][1];
				SOCH= TempTable[i][1];
			}
			else
			{
				T_L= TempTable[i][0];
				T_H= TempTable[i][0];
				SOCL= TempTable[i][1];
				SOCH= TempTable[i][1];
			}
			break;
		}
	}
	if((T_H>T_L)&&(SOCH>SOCL))
	{
		DelTSOC=  ((AverageTemperature-T_L)*(SOCH-SOCL)/(T_H-T_L));
	}
	else
	{
		DelTSOC=  0;
	}
	if(i==0)
	{
		Powervalue=105000/TempTable[0][1];
	}
	else if(i<5)
	{
		if((SOCL+DelTSOC)>50)
		{
			Powervalue=105000/(SOCL+DelTSOC);
		}
		else
		{
			Powervalue=105000/80;
		}
	}
	else
	{
		Powervalue= 1050;
	}
	return Powervalue;
}


//循环次数读取---待修改
void  CycleCount_Init(void)
{

//	S_WORD data ;
	syspara.RemainCap= 0;
#ifdef DBG_Printf_CYC
	printf("CycleCount_Init:  %d ",flashpara.CycleCount);
#endif	
	if(flashpara.CycleCount<3500)
	{
		if(flashpara.CycleCount>100)
		{
			syspara.FullChargeCap = (uint32_t)DESIGN_CAP - DESIGN_CAP/100*((flashpara.CycleCount-100)/CFG_Value_SJian);//100次以后 每80次衰减 1%	 //ZHQL1013
		}
		else
		{
			syspara.FullChargeCap = DESIGN_CAP;
		}
	}
	else
	{
		syspara.FullChargeCap= DESIGN_CAP/10;
	}

	
#ifdef DBG_Printf_CYC
	printf(" R= %d  F= %d \r\n",syspara.RemainCap,syspara.FullChargeCap);
#endif	
	return ;
}

//SOC初始化条件
uint8_t isSocInitEnable(uint8_t* curve,uint16_t* baseVol)
{
	uint8_t ret = Cal_NO;
//	if((syspara.voltAvg>2500)&&(syspara.voltAvg<5000)&&(syspara.voltMax<3800)&&(syspara.voltMin>2500))
	if((syspara.voltAvg>2750)&&(syspara.voltAvg<4500)&&(syspara.voltMax<6000)&&(syspara.voltMin>2750))
	{
		ret = Cal_OK;
		if((syspara.batStat == STATE_CHG)&&((abs(syspara.current))>100))
		{
			//根据放电倍率选择电压曲线
			if((abs(syspara.current))<(DESIGN_CAP_MULT(40))) *curve = CURVE_C_33; 
			else *curve = CURVE_C_50; 
		}
		else *curve = CURVE_STATIC; 
		
		//基准电压选择：用最高/最低/平均电压去查表
		if(syspara.voltMin<3400) *baseVol = syspara.voltMin; 
		else 	if(syspara.voltMax>4300) *baseVol = syspara.voltMax; 
		else *baseVol = syspara.voltAvg;
		rt_kprintf("SOCInitbaseVol=%d\r\n",*baseVol);
	}
	return ret;
}

//百分比
uint8_t Get_Percent(uint32_t val,uint32_t total)
{
	return (uint8_t)((val+(total/200))/(total/100));
}

//SOC初始化
void OCV_SOC_Init(void)
{
	uint8_t soc = 0;
//	static uint8_t count_Cyc = 0;
	uint8_t curveChange = 0;//曲线表
	uint16_t baseVolChange = 0;//基准电压
	
	syspara.FullChargeCap = 18720000;	// 2*2600*3600，应该还要*1000毫秒，这里就算是约分了吧 //DESIGN_CAP;
	
//	if(count_Cyc<3)
//	{
//		count_Cyc++;
//		return ;	//直接结束函数
//	}
	
	//电池处于静置状态,则每分钟计一次时
//	if(syspara.batStat==STATE_STATIC) syspara.OCVCalibrateTimer=rt_tick_get()/60000;
//	else syspara.OCVCalibrateTimer=1;
//	if(syspara.OCVCalibrateTimer%2==0) sysflag.bits.socInit_Flag=0;		//如果超过30分钟,则重新通过OCV估算SOC

//#if DEBUG_SOC
//	rt_kprintf("OCVCalibrateTimer=%d\r\n",syspara.OCVCalibrateTimer);
//#endif
	
	if(0==sysflag.bits.socInit_Flag)	//只运行第一次来查表确定电流积分值
	{
		if(isSocInitEnable(&curveChange,&baseVolChange))
		{
			switch(curveChange)
			{
				case CURVE_C_33:		// 三分之一速率充电表
					soc = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)C_TempArr,C_TempArrSize,baseVolChange,(uint16_t*)C_33Region);
					break;
				case CURVE_C_50:		//二分之一速率充电表
					soc = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)C_TempArr,C_TempArrSize,baseVolChange,(uint16_t*)C_50Region);
					break;
				case CURVE_STATIC:	//静置状态电压查表
					soc = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)K_TempArr,K_TempArrSize,baseVolChange,(uint16_t*)K_Region);	//查表法SOC
					break;
				default:break;
			}
			if(soc<=100)
			{
				sysflag.bits.socInit_Flag = 1;
				syspara.RemainCap = syspara.FullChargeCap/100*soc;
			}
		}
		else soc= 0;
	}
}

//SOC末端修正:充满时置满,放完时置零
void Soc_ClrOrSetCtrl(void)
{
	static uint8_t SetTimer = 0;		//置满前计数,减小误差
	static uint8_t ClearTimer = 0;	//清零前计数,减小误差
	static uint8_t SOCClrFlag = 0;
	static uint8_t SOCSetFlag = 0;
	static uint8_t SetFlagCLrTime= 0;
	static uint8_t ClrFlagCLrTime= 0;

	//放电停止积分
	if((syspara.SOC<2)&&(syspara.voltMin > 3350)) sysflag.bits.StopSocCutFlag=1;
	else sysflag.bits.StopSocCutFlag= 0;
	
	//充电停止积分
	if((syspara.SOC>98)&&(syspara.voltMax <4250)) sysflag.bits.StopSocAdddFlag=1;
	else sysflag.bits.StopSocAdddFlag= 0;

	if( syspara.batStat == STATE_CHG )//充电状态下置满
	{
		SetFlagCLrTime= 0;
		ClearTimer = 0;

		if(ClrFlagCLrTime<10) ClrFlagCLrTime++;
		else
		{
			SOCClrFlag=0;
			syspara.batteryStatus.bits.FullDis= 0;
		}
		//if((((syspara.voltMax >= CFG_SOC_SET_VMIN)||(O_V.alarmFlag))&&(syspara.voltMax <=CFG_SOC_SET_VMAX))||(((syspara.voltAvg>= 4100)||(O_TV.alarmFlag))&&(syspara.voltAvg <=CFG_SOC_SET_VMAX)))  
		if((syspara.voltMax >= CFG_SOC_SET_VMIN)||(syspara.voltAvg>=4180))  
		{
			SetTimer++;
			if(SetTimer>3)
			{
				SetTimer = 0;				
				SOCSetFlag=1;		//正式置满标志
			}
		}
		else SetTimer = 0;
	}
	//放电状态下SOC置零
	//else if((( syspara.batStat != STATE_CHG )||(syspara.voltAvg<= 3400))&&((abs(syspara.current))<(DESIGN_CAP_MULT(110))))//非充电状态下清零
	else if((( syspara.batStat != STATE_CHG )&&(syspara.voltAvg<= 3400)))
	{
		SetTimer= 0;	
		ClrFlagCLrTime= 0;
		if(syspara.current<(-200))
		{
			if(SetFlagCLrTime<10) SetFlagCLrTime++;
			else
			{
				SOCSetFlag=0;
				syspara.batteryStatus.bits.FullChg= 0;
			}
		}	
		else SetFlagCLrTime= 0;
		if(((syspara.voltMin >= CFG_SOC_CLEAR_VMIN)&&(syspara.voltMin <= CFG_SOC_CLEAR_VMAX))||(userAlarm.bits.U_V))  
		{
			ClearTimer++;
			if(ClearTimer>3)
			{
				ClearTimer = 0;				
				SOCClrFlag=1;		//正式清零标志
			}
		}
		else ClearTimer = 0;
	}
	else
	{
		ClearTimer = 0;
		SetTimer= 0;	
	}

	if(SOCClrFlag==1)					//电量清零
	{
		if(syspara.RemainCap>SOC_05_VALUE) syspara.RemainCap -= SOC_05_VALUE;
		else
		{
			syspara.RemainCap= 0;
			SOCClrFlag= 0;
			syspara.batteryStatus.bits.FullDis= 1;
		}
	}
	else if(SOCSetFlag==1)		//电量置满
	{
		//电量<90%
		if(syspara.RemainCap<(syspara.FullChargeCap-(SOC_05_VALUE*2))) syspara.RemainCap+= (SOC_05_VALUE*2);
		else
		{
			syspara.RemainCap= syspara.FullChargeCap;
			SOCSetFlag= 0;
			syspara.batteryStatus.bits.FullChg= 1;
		}
	}
}

//CHG校准条件
uint8_t isCali_CHG_Enable(uint8_t* curve,uint16_t* baseVol)
{
	static uint8_t timeout[2] = {0};
	uint8_t ret = Cal_NO;//
	if(((abs(syspara.current))>=(DESIGN_CAP_MULT(20)))&&((abs(syspara.current))<(DESIGN_CAP_MULT(40))))
	{
		timeout[0]++;
		timeout[1]=0;
	}
	else if(((abs(syspara.current))>=(DESIGN_CAP_MULT(40)))&&((abs(syspara.current))<(DESIGN_CAP_MULT(60))))
	{
		timeout[1]++;
		timeout[0]=0;
	}
	else
	{
		timeout[0]=0;
		timeout[1]=0;
	}
	if((timeout[0]>TimeOut(10))
	||(timeout[1]>TimeOut(10)))
	{
		ret = Cal_OK;
		if(timeout[0]>TimeOut(10))//待修改
		{
			*curve = CURVE_C_33;
			timeout[0]= 0;
		}
		else if(timeout[1]>TimeOut(10))
		{
			*curve = CURVE_C_50;
			timeout[1]= 0;
		}
		
		//基准电压选择
		if (abs((int)(syspara.voltMax-syspara.voltAvg)>=20))
		{
			*baseVol = syspara.voltMax;
		}
		else *baseVol = syspara.voltAvg;	
	}

	return ret;
}

//CHG校准
uint8_t GetFactor_Cali_CHG(uint16_t* factor)
{
	uint8_t socv = 0;
	uint8_t ret = Cal_NO;
	uint16_t baseVolChange = 0;
	uint8_t curveChange = 0;

	if(isCali_CHG_Enable(&curveChange,&baseVolChange))
	{
		switch(curveChange)
		{
			case CURVE_C_33:
			{
				socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)C_TempArr,C_TempArrSize,baseVolChange,(uint16_t*)C_33Region);
			}break;
			case CURVE_C_50:
			{
				socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)C_TempArr,C_TempArrSize,baseVolChange,(uint16_t*)C_50Region);
			}break;
			
			default:break;
		}
		if((syspara.SOC>80) &&((abs((int)(syspara.SOC-socv)))>5))
		{
			ret = Cal_OK;
			if(100>socv)
			{
				*factor = (uint32_t)(100-syspara.SOC)*1000/(100-socv);
			}
			else
			{
				*factor =  2000;
			}
			if(*factor>1200)
			{
				*factor= 1200;
			}
			else	if(*factor<500)
			{
				*factor= 500;
			}
		}
		else if((abs((int)(syspara.SOC-socv)))<=1)
		{
			*factor= 1000;
			 ret = Cal_OK;
		}
		else if((syspara.SOC<socv)&&(syspara.IntegralPower_C<1000))
		{
				*factor = 1000;
				ret = Cal_OK;
		}
		else if((syspara.SOC>socv)&&(syspara.IntegralPower_C>1000))
		{
				*factor = 1000;
				ret = Cal_OK;
		}
	}
	return ret;
}

//DSG校准条件
uint8_t isCali_DSG_Enable(uint8_t* curve,uint16_t* baseVol)
{
	static uint8_t timeout[3] = {0};
	uint8_t ret = Cal_NO;//
	if(((abs(syspara.current))>=(DESIGN_CAP_MULT(20)))&&((abs(syspara.current))<(DESIGN_CAP_MULT(40))))
	{
		timeout[0]++;
		timeout[1]=0;
		timeout[2]=0;
		
	}
	else if(((abs(syspara.current))>=(DESIGN_CAP_MULT(40)))&&((abs(syspara.current))<(DESIGN_CAP_MULT(60))))
	{
		timeout[1]++;
		timeout[0]=0;
		timeout[2]=0;
	}
	else if(((abs(syspara.current))>=(DESIGN_CAP_MULT(60)))&&((abs(syspara.current))<(DESIGN_CAP_MULT(110))))
	{
		timeout[2]++;
		timeout[1]=0;
		timeout[0]=0;
	}
	else
	{
		timeout[0]=0;
		timeout[1]=0;
		timeout[2]=0;
	}
		if((timeout[0]>TimeOut(10))
		||(timeout[1]>TimeOut(10))
		||(timeout[2]>TimeOut(10)))
		{
			ret = Cal_OK;
			if(timeout[0]>TimeOut(10))//待修改
			{
				*curve = CURVE_D_33;
				timeout[0]= 0;
			}
			else if(timeout[1]>TimeOut(10))
			{
				*curve = CURVE_D_50;
				timeout[1]= 0;
			}
			else if(timeout[2]>TimeOut(10))
			{
				*curve = CURVE_D_100;
				timeout[2]= 0;
			}
			
			//基准电压选择
			*baseVol = syspara.voltMin;		
		}

	return ret;
}

//DSG校准
uint8_t GetFactor_Cali_DSG(uint16_t* factor)
{
	uint8_t socv = 0;
	uint8_t ret = Cal_NO;
	uint16_t baseVolChange = 0;
	uint8_t curveChange = 0;

	if(isCali_DSG_Enable(&curveChange,&baseVolChange))
	{
		switch(curveChange)
		{
			case CURVE_D_33:
			{
				socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)D_TempArr,D_TempArrSize,baseVolChange,(uint16_t*)D_33Region);
			}break;
			case CURVE_D_50:
			{
				socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)D_TempArr,D_TempArrSize,baseVolChange,(uint16_t*)D_50Region);
			}break;
			case CURVE_D_100:
			{
				socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)D_TempArr,D_TempArrSize,baseVolChange,(uint16_t*)D_100Region);
			}break;
			
			default:break;
		}

		if(((syspara.SOC>0)&&(syspara.SOC<=CFG_StartSOC))||((socv<=CFG_StartSOC)&&(syspara.tempAvg>60)))
		{
			DSGCaliFlaG= 1;
			if(abs((int)(syspara.SOC-socv))>5)
			{
				if(0 != socv)
				{
					if(socv>0)
					{
						*factor =  (uint16_t)((uint32_t)syspara.SOC*1050L/socv);
					}
				}
				else
				{
					*factor= 2000;
				}
				ret = Cal_OK;
			}
			else if(abs((int)(syspara.SOC-socv))<=1)
			{
				*factor = 1050;
				ret = Cal_OK;
			}
			else if((syspara.SOC<socv)&&(syspara.IntegralPower>1050))
			{
				*factor = 1050;
				ret = Cal_OK;
			}

			if(*factor > 2000)
			{
				*factor= 2000;
			}
			else	if((*factor<1000)&&(syspara.tempAvg>60))
			{
				*factor= 1000;
			}
			else if(*factor < 500)
			{
				*factor= 500;
			}
		}
		else
		{
			DSGCaliFlaG= 0;
		}
		//printf("P= %d  %d\r\n",*factor,ret );
	}
	if(DSGCaliFlaG==0)
	{
		ret = Cal_Temp;
	}
	return ret;
}


//静态校准条件
uint8_t isCali_STATIC_Enable(uint8_t* curve,uint16_t* baseVol)
{
	static uint8_t timeout = 0;
	uint8_t ret = Cal_NO;//
	if((abs(syspara.current))<(DESIGN_CAP_MULT(10)))
	{
		timeout++;
		if(timeout>TimeOut(10))
		{
			ret = Cal_OK;
			//曲线选择
			*curve = CURVE_STATIC;
			//基准电压选择
			if(syspara.voltMax>3340)
			{
				*baseVol = syspara.voltMax;
			}
			else if(syspara.voltMin<3150)
			{
				*baseVol = syspara.voltMin;
			}
			else if((abs((int)(syspara.voltMax - syspara.voltMin)))>20)
			{
				*baseVol = syspara.voltMax;
			}
			else *baseVol = syspara.voltAvg;	
		}
	}
	else timeout = 0;
	return ret;
}

//静态校准
uint8_t GetFactor_Cali_STATIC(uint16_t* factor)
{
	uint8_t socv = 0;
	uint8_t ret = Cal_NO;
	uint16_t baseVolChange = 0;
	uint8_t curveChange = 0;

	if(isCali_STATIC_Enable(&curveChange,&baseVolChange))
	{
		socv = Get_TableV_SOC(syspara.tempAvg,(uint8_t*)K_TempArr,K_TempArrSize,baseVolChange,(uint16_t*)K_Region);
		if((((socv>0)&&(socv<30))||((socv>80)&&(socv<100)))&&((abs((int)(syspara.SOC-socv))>30)))
		{
			ret= Cal_OK;
			if(socv>0)
			{
				*factor =  (uint16_t)((uint32_t)syspara.SOC*1000L/socv);
			}
			else
			{
				*factor= 2000;
			}
			if(*factor>2000)
			{
				*factor= 2000;
			}
			else	if(*factor<900)
			{
				*factor= 900;
			}
		}
	}
	return ret;
}

//静态温度系数校准
uint8_t GetFactor_Cali_DSGTempCoeff(uint16_t* factor)//待修改
{
//	uint8_t soct = 0;
	uint8_t ret = Cal_NO;
	

	if(syspara.SOC>CFG_StartSOC)	
	{
	*factor = Get_TableT_Coefficient(syspara.tempAvg);
	ret = Cal_OK;

	if(*factor>2000)
	{
		*factor= 2000;
	}
	else	if(*factor<500)
	{
		*factor= 500;
	}
		//printf("GetFactor_Cali_DSGTempCoeff= %d  %d %d\r\n",syspara.tempAvg,*factor,ret );
	}
	return ret;
}


//剩余SOC校准
uint8_t RealRemainCap_Calibration(void)
{
	uint8_t caliFlag = 0;
	static uint16_t caliFactor = 0;//校准因子
#if(TEST_CYC==0)	
	switch(syspara.batStat)
	{
		case STATE_CHG:
			DSGCaliFlaG= 0;
			caliFlag = GetFactor_Cali_CHG(&caliFactor);
			if(caliFlag==Cal_OK)
			{
				syspara.IntegralPower_C= caliFactor;
			}
			break;
		case STATE_DSG:
			{

				caliFlag = GetFactor_Cali_DSG(&caliFactor);
				if(caliFlag==Cal_Temp)
				{
					caliFlag = GetFactor_Cali_DSGTempCoeff(&caliFactor);
				}
				if(caliFlag==Cal_OK)
				{
					syspara.IntegralPower = caliFactor;
				}
			}
			break;
		case STATE_STATIC:
			//caliFlag = GetFactor_Cali_STATIC(&caliFactor);
			break;
		default:break;
	}
	
	//计算校准系数

#endif
	return caliFlag;
}


/**
  ******************************************************************************
  * 剩余容量：电流积分计算
  ******************************************************************************
  */
void RemainCap_Integral(int32_t curr,uint16_t time)
{	
	//int64_t accCap = (int64_t)curr*time*IntegralPower/1000/200;		//安时积分容量
	int32_t accCap = curr*time/1000;		//安时积分容量
	//uint8_t AddValue= 0;
	
	#if(DEBUG_SOC)
		rt_kprintf("curr=%d time=%d accCap=%d\r\n",curr,time,accCap);
	#endif
	
	//如果出现充放电容量置满或置零时直接将安时积分=0
	if(((accCap>0)&&(sysflag.bits.StopSocAdddFlag==1))||((accCap<0)&&(sysflag.bits.StopSocCutFlag==1)))
	{
		accCap= 0;
	}
	
	//accCap=accCap-(AddValue+CutCapValue);
	//CutCapValue= 0;
	
	if(accCap<0)
	{
		if(syspara.RemainCap>=(abs(accCap)))
		{
			syspara.RemainCap += accCap;
		}
		else syspara.RemainCap =0;
	}
	else syspara.RemainCap += accCap;
	
	if(syspara.RemainCap>=syspara.FullChargeCap) syspara.RemainCap = syspara.FullChargeCap;
	
	#if(DEBUG_SOC)
		rt_kprintf("RemainCap/FullChargeCap=%d/%d\r\n",syspara.RemainCap,syspara.FullChargeCap);
	#endif
}


//总放电容量累加--循环次数
void Cycle_Integral(int32_t curr,uint16_t time)
{
	static uint16_t  chgTime= 0;
	static uint16_t  DSGTime= 0;
	static uint8_t  chgstat= 0;
	static uint8_t  Shotstat= 0;
	static uint8_t UVFalg= 0;
	static uint16_t noShortime= 0;
	static uint16_t noUVtime= 0;
//	S_WORD data ;
	if(STATE_DSG == syspara.batStat)
	{
		chgTime= 0;
		if(DSGTime>TimeOut(30))
		{
			chgstat= 0;
		}
		else
		{
			DSGTime++;
		}
		syspara.TotalDsgCap += ((abs(curr))*time/200);
		if((syspara.TotalDsgCap>=syspara.FullChargeCap)&&(syspara.FullChargeCap>(DESIGN_CAP/3)))
		{
			syspara.TotalDsgCap = 0;
			flashpara.CycleCount++;
			//ZHQL1013
			if(flashpara.CycleCount>100)
			{
				syspara.FullChargeCap = (uint32_t)DESIGN_CAP - DESIGN_CAP/100*((flashpara.CycleCount-100)/CFG_Value_SJian);//100次以后 每80次衰减 1%	 //ZHQL1013
			}
			else
			{
				syspara.FullChargeCap = DESIGN_CAP;
			}
		}
	}
	else 	if(STATE_CHG == syspara.batStat)
	{
		DSGTime= 0;
		if(chgTime>=((uint16_t)TimeOut(3000)))
		{
			chgTime= 0;
			chgstat= 1;
			flashpara.cyc_CHG++;
		}
		else
		{
			if(chgstat==0)
			{
				chgTime++;
			}
		}

	}

	//计算过放次数
	if((U_V_2300.alarmFlag==1)&&(syspara.voltMin<=2800))
	{
		noUVtime= 0;
		if(UVFalg==0)
		{
			UVFalg=1;
			flashpara.P_UV_Count++;
		}
	}
	else if(syspara.voltMin>2800)
	{
		if(noUVtime<30)
		{
			noUVtime++;
		}
		else
		{
			UVFalg=0;
		}
	}
	else
	{
		noUVtime= 0;
	}
	
	if(Shotstat==1)
	{
		if(userAlarm.bits.S_C_D==0)
		{
			if(noShortime<30)
			{
				noShortime++;
			}
			else
			{
				Shotstat=0;
			}
		}
	}
	else
	{
		noShortime=0;
		if(userAlarm.bits.S_C_D==1)
		{
			flashpara.shortCnt++;
			Shotstat= 1;
		}
	}
}



