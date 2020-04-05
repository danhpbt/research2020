#ifndef _BASIC_EFFECT_H__
#define _BASIC_EFFECT_H__

#include "Typedef.h"
#include "ConvMatrix.h"

#define OPTIMIZE_SPEED_BY_MACRO
#define GLOBAL_BMP_MEMORY

#define SAFEDELETE(obj) \
	if (obj != NULL) \
	   delete obj; \
	obj = NULL;

#define LUMINANCE(r, g ,b) (int) ((0.299 * r) + (0.58 * g) + (0.11 * b))

#define LERP(t, a, b) (int)(a + t * (b - a))

#ifdef INVERT_RED

#define GET_INTENSITY_BYTE(rgba, val)		\
	byte* rgba8 = (byte*)&rgba;			\
    val = (byte)((7471 * (*(rgba8)) + 38470 * (*(rgba8 + 1)) + 19595 * (*(rgba8 + 2))) >> 16);\

#else

#define GET_INTENSITY_BYTE(rgba, val)		\
	byte* rgba8 = (byte*)&rgba;			\
    val = (byte)((7471 * (*(rgba8 + 2)) + 38470 * (*(rgba8 + 1)) + 19595 * (*(rgba8))) >> 16);\

#endif


#define FAST_SCALE_BYTE_BY_BYTE(a, b, val)			\
    int r1 = a * b + 0x80;							\
	int r2 = ((r1 >> 8) + r1) >> 8;					\
	val = (byte)r2;	

#define EVAN_MAX3(x, y, z, val)						\
	double aaa = MAX(x,y);							\
	double bbb = MAX(y,z);							\
	val = MAX(aaa, bbb);

#define EVAN_MIN3(x, y, z, val)						\
	double xxx = MIN(x,y);							\
	double yyy = MIN(y,z);							\
	val = MIN(xxx, yyy);

#define EVAN_RGB_TO_HSV(R, G, B, outH, outS, outV)					\
	double x = ((double) R) / 255.0;								\
    double y = ((double) G) / 255.0;								\
	double z = ((double) B) / 255.0;								\
	double num4_;													\
	EVAN_MAX3(x, y, z, num4_);										\
    double num5_;													\
	EVAN_MIN3(x, y, z, num5_);										\
    double num6_ = num4_ - num5_;									\
    outV = num4_;													\
    if (num4_ == 0.0)												\
    {																\
        outH = -999.0;												\
        outS = 0.0;													\
    }																\
    else															\
    {																\
        outS = num6_ / num4_;										\
        if (num4_ == num5_)											\
        {															\
            outH = -999.0;											\
        }															\
        else														\
        {															\
            if (x == num4_)											\
            {														\
                outH = ((y - z) / num6_) * 60.0;					\
            }														\
            else if (y == num4_)									\
            {														\
                outH = (2.0 + ((z - x) / num6_)) * 60.0;			\
            }														\
            else													\
            {														\
                outH = (4.0 + ((x - y) / num6_)) * 60.0;			\
            }														\
            if (outH < 0.0)											\
            {														\
                outH += 360.0;										\
            }														\
        }															\
    }																

#define ANGLE_CONTRAIN(MyAngle)										\
    if (MyAngle >= 360.0)											\
    {																\
        MyAngle -= floor((double) (MyAngle / 360.0)) * 360.0;		\
    }																\
    if (MyAngle < 0.0)												\
    {																\
        MyAngle += 360.0;											\
    }																\


#define EVAN_HSV_TO_RGB(H, S, V, bR, bG, bB)						\
	if ((S == 0.0) || (H == -999.0))								\
    {																\
        byte num = (byte) ((int) (V * 255.0));						\
        bR = num;													\
        bG = num;													\
        bB = num;													\
    }																\
    else															\
    {																\
        if (H >= 360.0)												\
        {															\
           ANGLE_CONTRAIN(H);										\
        }															\
        double _num2 = V;											\
        double _num3 = V;											\
        double _num4 = V;											\
        int _num5 = (int)floor((double) (H / 60.0));				\
        double _num6 = (H / 60.0) - _num5;							\
        double _num7 = V * (1.0 - S);								\
        double _num8 = V * (1.0 - (_num6 * S));						\
        double _num9 = V * (1.0 - ((1.0 - _num6) * S));				\
        switch (_num5)												\
        {															\
            case 0:													\
                _num2 = V;											\
                _num3 = _num9;										\
                _num4 = _num7;										\
                break;												\
																	\
            case 1:													\
                _num2 = _num8;										\
                _num3 = V;											\
                _num4 = _num7;										\
                break;												\
																	\
            case 2:													\
                _num2 = _num7;										\
                _num3 = V;											\
                _num4 = _num9;										\
                break;												\
																	\
            case 3:													\
                _num2 = _num7;										\
                _num3 = _num8;										\
                _num4 = V;											\
                break;												\
																	\
            case 4:													\
                _num2 = _num9;										\
                _num3 = _num7;										\
                _num4 = V;											\
                break;												\
																	\
            case 5:													\
                _num2 = V;											\
                _num3 = _num7;										\
                _num4 = _num8;										\
                break;												\
        }															\
        int _num10 = (int) (_num2 * 255.0);							\
        int _num11 = (int) (_num3 * 255.0);							\
        int _num12 = (int) (_num4 * 255.0);							\
        bR = (byte) _num10;											\
        bG = (byte) _num11;											\
        bB = (byte) _num12;											\
    }																\



byte* CreateGamma(double color);									
//////////////////////////////////////////////////////////////////////////
//BMP_ARGB *data:		image data									
//int width:			image width									
//int height:			image height								
																	
//////////////////////////////////////////////////////////////////////////
//COLOR_FILTER filter	color filter
//////////////////////////////////////////////////////////////////////////
/*
#ifndef _WIN32
	#ifdef __cplusplus
	extern "C"
	{
	#endif
#endif
*/		

	const unsigned int masTable[] = 
    {
        0x00000000, 0x00000000, 0,  // 0
        0x00000001, 0x00000000, 0,  // 1
        0x00000001, 0x00000000, 1,  // 2
        0xAAAAAAAB, 0x00000000, 33, // 3
        0x00000001, 0x00000000, 2,  // 4
        0xCCCCCCCD, 0x00000000, 34, // 5
        0xAAAAAAAB, 0x00000000, 34, // 6
        0x49249249, 0x49249249, 33, // 7
        0x00000001, 0x00000000, 3,  // 8
        0x38E38E39, 0x00000000, 33, // 9
        0xCCCCCCCD, 0x00000000, 35, // 10
        0xBA2E8BA3, 0x00000000, 35, // 11
        0xAAAAAAAB, 0x00000000, 35, // 12
        0x4EC4EC4F, 0x00000000, 34, // 13
        0x49249249, 0x49249249, 34, // 14
        0x88888889, 0x00000000, 35, // 15
        0x00000001, 0x00000000, 4,  // 16
        0xF0F0F0F1, 0x00000000, 36, // 17
        0x38E38E39, 0x00000000, 34, // 18
        0xD79435E5, 0xD79435E5, 36, // 19
        0xCCCCCCCD, 0x00000000, 36, // 20
        0xC30C30C3, 0xC30C30C3, 36, // 21
        0xBA2E8BA3, 0x00000000, 36, // 22
        0xB21642C9, 0x00000000, 36, // 23
        0xAAAAAAAB, 0x00000000, 36, // 24
        0x51EB851F, 0x00000000, 35, // 25
        0x4EC4EC4F, 0x00000000, 35, // 26
        0x97B425ED, 0x97B425ED, 36, // 27
        0x49249249, 0x49249249, 35, // 28
        0x8D3DCB09, 0x00000000, 36, // 29
        0x88888889, 0x00000000, 36, // 30
        0x42108421, 0x42108421, 35, // 31
        0x00000001, 0x00000000, 5,  // 32
        0x3E0F83E1, 0x00000000, 35, // 33
        0xF0F0F0F1, 0x00000000, 37, // 34
        0x75075075, 0x75075075, 36, // 35
        0x38E38E39, 0x00000000, 35, // 36
        0x6EB3E453, 0x6EB3E453, 36, // 37
        0xD79435E5, 0xD79435E5, 37, // 38
        0x69069069, 0x69069069, 36, // 39
        0xCCCCCCCD, 0x00000000, 37, // 40
        0xC7CE0C7D, 0x00000000, 37, // 41
        0xC30C30C3, 0xC30C30C3, 37, // 42
        0x2FA0BE83, 0x00000000, 35, // 43
        0xBA2E8BA3, 0x00000000, 37, // 44
        0x5B05B05B, 0x5B05B05B, 36, // 45
        0xB21642C9, 0x00000000, 37, // 46
        0xAE4C415D, 0x00000000, 37, // 47
        0xAAAAAAAB, 0x00000000, 37, // 48
        0x5397829D, 0x00000000, 36, // 49
        0x51EB851F, 0x00000000, 36, // 50
        0xA0A0A0A1, 0x00000000, 37, // 51
        0x4EC4EC4F, 0x00000000, 36, // 52
        0x9A90E7D9, 0x9A90E7D9, 37, // 53
        0x97B425ED, 0x97B425ED, 37, // 54
        0x94F2094F, 0x94F2094F, 37, // 55
        0x49249249, 0x49249249, 36, // 56
        0x47DC11F7, 0x47DC11F7, 36, // 57
        0x8D3DCB09, 0x00000000, 37, // 58
        0x22B63CBF, 0x00000000, 35, // 59
        0x88888889, 0x00000000, 37, // 60
        0x4325C53F, 0x00000000, 36, // 61
        0x42108421, 0x42108421, 36, // 62
        0x41041041, 0x41041041, 36, // 63
        0x00000001, 0x00000000, 6,  // 64
        0xFC0FC0FD, 0x00000000, 38, // 65
        0x3E0F83E1, 0x00000000, 36, // 66
        0x07A44C6B, 0x00000000, 33, // 67
        0xF0F0F0F1, 0x00000000, 38, // 68
        0x76B981DB, 0x00000000, 37, // 69
        0x75075075, 0x75075075, 37, // 70
        0xE6C2B449, 0x00000000, 38, // 71
        0x38E38E39, 0x00000000, 36, // 72
        0x381C0E07, 0x381C0E07, 36, // 73
        0x6EB3E453, 0x6EB3E453, 37, // 74
        0x1B4E81B5, 0x00000000, 35, // 75
        0xD79435E5, 0xD79435E5, 38, // 76
        0x3531DEC1, 0x00000000, 36, // 77
        0x69069069, 0x69069069, 37, // 78
        0xCF6474A9, 0x00000000, 38, // 79
        0xCCCCCCCD, 0x00000000, 38, // 80
        0xCA4587E7, 0x00000000, 38, // 81
        0xC7CE0C7D, 0x00000000, 38, // 82
        0x3159721F, 0x00000000, 36, // 83
        0xC30C30C3, 0xC30C30C3, 38, // 84
        0xC0C0C0C1, 0x00000000, 38, // 85
        0x2FA0BE83, 0x00000000, 36, // 86
        0x2F149903, 0x00000000, 36, // 87
        0xBA2E8BA3, 0x00000000, 38, // 88
        0xB81702E1, 0x00000000, 38, // 89
        0x5B05B05B, 0x5B05B05B, 37, // 90
        0x2D02D02D, 0x2D02D02D, 36, // 91
        0xB21642C9, 0x00000000, 38, // 92
        0xB02C0B03, 0x00000000, 38, // 93
        0xAE4C415D, 0x00000000, 38, // 94
        0x2B1DA461, 0x2B1DA461, 36, // 95
        0xAAAAAAAB, 0x00000000, 38, // 96
        0xA8E83F57, 0xA8E83F57, 38, // 97
        0x5397829D, 0x00000000, 37, // 98
        0xA57EB503, 0x00000000, 38, // 99
        0x51EB851F, 0x00000000, 37, // 100
        0xA237C32B, 0xA237C32B, 38, // 101
        0xA0A0A0A1, 0x00000000, 38, // 102
        0x9F1165E7, 0x9F1165E7, 38, // 103
        0x4EC4EC4F, 0x00000000, 37, // 104
        0x27027027, 0x27027027, 36, // 105
        0x9A90E7D9, 0x9A90E7D9, 38, // 106
        0x991F1A51, 0x991F1A51, 38, // 107
        0x97B425ED, 0x97B425ED, 38, // 108
        0x2593F69B, 0x2593F69B, 36, // 109
        0x94F2094F, 0x94F2094F, 38, // 110
        0x24E6A171, 0x24E6A171, 36, // 111
        0x49249249, 0x49249249, 37, // 112
        0x90FDBC09, 0x90FDBC09, 38, // 113
        0x47DC11F7, 0x47DC11F7, 37, // 114
        0x8E78356D, 0x8E78356D, 38, // 115
        0x8D3DCB09, 0x00000000, 38, // 116
        0x23023023, 0x23023023, 36, // 117
        0x22B63CBF, 0x00000000, 36, // 118
        0x44D72045, 0x00000000, 37, // 119
        0x88888889, 0x00000000, 38, // 120
        0x8767AB5F, 0x8767AB5F, 38, // 121
        0x4325C53F, 0x00000000, 37, // 122
        0x85340853, 0x85340853, 38, // 123
        0x42108421, 0x42108421, 37, // 124
        0x10624DD3, 0x00000000, 35, // 125
        0x41041041, 0x41041041, 37, // 126
        0x10204081, 0x10204081, 35, // 127
        0x00000001, 0x00000000, 7,  // 128
        0x0FE03F81, 0x00000000, 35, // 129
        0xFC0FC0FD, 0x00000000, 39, // 130
        0xFA232CF3, 0x00000000, 39, // 131
        0x3E0F83E1, 0x00000000, 37, // 132
        0xF6603D99, 0x00000000, 39, // 133
        0x07A44C6B, 0x00000000, 34, // 134
        0xF2B9D649, 0x00000000, 39, // 135
        0xF0F0F0F1, 0x00000000, 39, // 136
        0x077975B9, 0x00000000, 34, // 137
        0x76B981DB, 0x00000000, 38, // 138
        0x75DED953, 0x00000000, 38, // 139
        0x75075075, 0x75075075, 38, // 140
        0x3A196B1F, 0x00000000, 37, // 141
        0xE6C2B449, 0x00000000, 39, // 142
        0xE525982B, 0x00000000, 39, // 143
        0x38E38E39, 0x00000000, 37, // 144
        0xE1FC780F, 0x00000000, 39, // 145
        0x381C0E07, 0x381C0E07, 37, // 146
        0xDEE95C4D, 0x00000000, 39, // 147
        0x6EB3E453, 0x6EB3E453, 38, // 148
        0xDBEB61EF, 0x00000000, 39, // 149
        0x1B4E81B5, 0x00000000, 36, // 150
        0x36406C81, 0x00000000, 37, // 151
        0xD79435E5, 0xD79435E5, 39, // 152
        0xD62B80D7, 0x00000000, 39, // 153
        0x3531DEC1, 0x00000000, 37, // 154
        0xD3680D37, 0x00000000, 39, // 155
        0x69069069, 0x69069069, 38, // 156
        0x342DA7F3, 0x00000000, 37, // 157
        0xCF6474A9, 0x00000000, 39, // 158
        0xCE168A77, 0xCE168A77, 39, // 159
        0xCCCCCCCD, 0x00000000, 39, // 160
        0xCB8727C1, 0x00000000, 39, // 161
        0xCA4587E7, 0x00000000, 39, // 162
        0xC907DA4F, 0x00000000, 39, // 163
        0xC7CE0C7D, 0x00000000, 39, // 164
        0x634C0635, 0x00000000, 38, // 165
        0x3159721F, 0x00000000, 37, // 166
        0x621B97C3, 0x00000000, 38, // 167
        0xC30C30C3, 0xC30C30C3, 39, // 168
        0x60F25DEB, 0x00000000, 38, // 169
        0xC0C0C0C1, 0x00000000, 39, // 170
        0x17F405FD, 0x17F405FD, 36, // 171
        0x2FA0BE83, 0x00000000, 37, // 172
        0xBD691047, 0xBD691047, 39, // 173
        0x2F149903, 0x00000000, 37, // 174
        0x5D9F7391, 0x00000000, 38, // 175
        0xBA2E8BA3, 0x00000000, 39, // 176
        0x5C90A1FD, 0x5C90A1FD, 38, // 177
        0xB81702E1, 0x00000000, 39, // 178
        0x5B87DDAD, 0x5B87DDAD, 38, // 179
        0x5B05B05B, 0x5B05B05B, 38, // 180
        0xB509E68B, 0x00000000, 39, // 181
        0x2D02D02D, 0x2D02D02D, 37, // 182
        0xB30F6353, 0x00000000, 39, // 183
        0xB21642C9, 0x00000000, 39, // 184
        0x1623FA77, 0x1623FA77, 36, // 185
        0xB02C0B03, 0x00000000, 39, // 186
        0xAF3ADDC7, 0x00000000, 39, // 187
        0xAE4C415D, 0x00000000, 39, // 188
        0x15AC056B, 0x15AC056B, 36, // 189
        0x2B1DA461, 0x2B1DA461, 37, // 190
        0xAB8F69E3, 0x00000000, 39, // 191
        0xAAAAAAAB, 0x00000000, 39, // 192
        0x15390949, 0x00000000, 36, // 193
        0xA8E83F57, 0xA8E83F57, 39, // 194
        0x15015015, 0x15015015, 36, // 195
        0x5397829D, 0x00000000, 38, // 196
        0xA655C439, 0xA655C439, 39, // 197
        0xA57EB503, 0x00000000, 39, // 198
        0x5254E78F, 0x00000000, 38, // 199
        0x51EB851F, 0x00000000, 38, // 200
        0x028C1979, 0x00000000, 33, // 201
        0xA237C32B, 0xA237C32B, 39, // 202
        0xA16B312F, 0x00000000, 39, // 203
        0xA0A0A0A1, 0x00000000, 39, // 204
        0x4FEC04FF, 0x00000000, 38, // 205
        0x9F1165E7, 0x9F1165E7, 39, // 206
        0x27932B49, 0x00000000, 37, // 207
        0x4EC4EC4F, 0x00000000, 38, // 208
        0x9CC8E161, 0x00000000, 39, // 209
        0x27027027, 0x27027027, 37, // 210
        0x9B4C6F9F, 0x00000000, 39, // 211
        0x9A90E7D9, 0x9A90E7D9, 39, // 212
        0x99D722DB, 0x00000000, 39, // 213
        0x991F1A51, 0x991F1A51, 39, // 214
        0x4C346405, 0x00000000, 38, // 215
        0x97B425ED, 0x97B425ED, 39, // 216
        0x4B809701, 0x4B809701, 38, // 217
        0x2593F69B, 0x2593F69B, 37, // 218
        0x12B404AD, 0x12B404AD, 36, // 219
        0x94F2094F, 0x94F2094F, 39, // 220
        0x25116025, 0x25116025, 37, // 221
        0x24E6A171, 0x24E6A171, 37, // 222
        0x24BC44E1, 0x24BC44E1, 37, // 223
        0x49249249, 0x49249249, 38, // 224
        0x91A2B3C5, 0x00000000, 39, // 225
        0x90FDBC09, 0x90FDBC09, 39, // 226
        0x905A3863, 0x905A3863, 39, // 227
        0x47DC11F7, 0x47DC11F7, 38, // 228
        0x478BBCED, 0x00000000, 38, // 229
        0x8E78356D, 0x8E78356D, 39, // 230
        0x46ED2901, 0x46ED2901, 38, // 231
        0x8D3DCB09, 0x00000000, 39, // 232
        0x2328A701, 0x2328A701, 37, // 233
        0x23023023, 0x23023023, 37, // 234
        0x45B81A25, 0x45B81A25, 38, // 235
        0x22B63CBF, 0x00000000, 37, // 236
        0x08A42F87, 0x08A42F87, 35, // 237
        0x44D72045, 0x00000000, 38, // 238
        0x891AC73B, 0x00000000, 39, // 239
        0x88888889, 0x00000000, 39, // 240
        0x10FEF011, 0x00000000, 36, // 241
        0x8767AB5F, 0x8767AB5F, 39, // 242
        0x86D90545, 0x00000000, 39, // 243
        0x4325C53F, 0x00000000, 38, // 244
        0x85BF3761, 0x85BF3761, 39, // 245
        0x85340853, 0x85340853, 39, // 246
        0x10953F39, 0x10953F39, 36, // 247
        0x42108421, 0x42108421, 38, // 248
        0x41CC9829, 0x41CC9829, 38, // 249
        0x10624DD3, 0x00000000, 36, // 250
        0x828CBFBF, 0x00000000, 39, // 251
        0x41041041, 0x41041041, 38, // 252
        0x81848DA9, 0x00000000, 39, // 253
        0x10204081, 0x10204081, 36, // 254
        0x80808081, 0x00000000, 39  // 255
    };

	extern BMP_ARGB* src;

#define CROSSES		0
#define LINES		1
#define CIRCLES		2
#define SQUARES		3

#define JITTER_EDGE_NONE		0    
#define JITTER_EDGE_WRAP		1
#define JITTER_EDGE_REFLECT		2
#define JITTER_EDGE_PRIMARY		3
#define JITTER_EDGE_SECONDARY	4

class SimpleImageProcessor
{
public:
	SimpleImageProcessor()
	{
	}

public:
	static double* CreateBuffer(int byte_length)
	{
		return (double*)(new byte[byte_length]);
	}	
};

void EXPORT_DLL ColorFilter(BMP_ARGB *data, int width, int height, enum COLOR_FILTER filter);

//////////////////////////////////////////////////////////////////////////
//double red, green, blue:			value 0->1
//////////////////////////////////////////////////////////////////////////
void EXPORT_DLL Gamma(BMP_ARGB *data, int width, int height, double red, double green, double blue);

//////////////////////////////////////////////////////////////////////////
//int brightness					value -255->255
//////////////////////////////////////////////////////////////////////////
void EXPORT_DLL Brightness(BMP_ARGB *data, int width, int height, int brightness);

//////////////////////////////////////////////////////////////////////////
//double contrast					value -100->100
//////////////////////////////////////////////////////////////////////////
void EXPORT_DLL Contrast(BMP_ARGB *data, int width, int height, double contrast);

void EXPORT_DLL Grayscale(BMP_ARGB *data, int width, int height);

void EXPORT_DLL Invert(BMP_ARGB *data, int width, int height);
void EXPORT_DLL Vignette(BMP_ARGB *data, int width, int height);

//////////////////////////////////////////////////////////////////////////
void EXPORT_DLL Conv3x3(BMP_ARGB *data, int width, int height, ConvMatrix* m);
void EXPORT_DLL Smooth(BMP_ARGB *data, int width, int height, int nWeight /* default to 1 */);
void EXPORT_DLL GaussianBlur(BMP_ARGB *data, int width, int height, int nWeight /* default to 4*/);
void EXPORT_DLL MeanRemoval(BMP_ARGB *data, int width, int height, int nWeight /* default to 9*/ );
void EXPORT_DLL Sharpen(BMP_ARGB *data, int width, int height, int nWeight /* default to 11*/ );
void EXPORT_DLL EmbossLaplacian(BMP_ARGB *data, int width, int height);
void EXPORT_DLL EdgeDetectQuick(BMP_ARGB *data, int width, int height);

//////////////////////////////////////////////////////////////////////////
void OffsetFilterAbs(BMP_ARGB *data, int width, int height, IntPoint** offset);
void OffsetFilter(BMP_ARGB *data, int width, int height, IntPoint** offset);
void OffsetFilterAntiAlias(BMP_ARGB *data, int width, int height, FloatPoint** fp);

void EXPORT_DLL Flip(BMP_ARGB *data, int width, int height, bool bHorz, bool bVert);
void EXPORT_DLL RandomJitter(BMP_ARGB *data, int width, int height, short nDegree);
void EXPORT_DLL Swirl(BMP_ARGB *data, int width, int height, double fDegree, bool bSmoothing /* default fDegree to .05 */);
void EXPORT_DLL Sphere(BMP_ARGB *data, int width, int height, bool bSmoothing);
void EXPORT_DLL TimeWarp(BMP_ARGB *data, int width, int height, byte factor, bool bSmoothing);
void EXPORT_DLL Moire(BMP_ARGB *data, int width, int height, double fDegree);
void EXPORT_DLL Water(BMP_ARGB *data, int width, int height, short nWave, bool bSmoothing);
void EXPORT_DLL Pixelate(BMP_ARGB *data, int width, int height, short pixel, bool bGrid);

//double m_iCurvature		value [0.001,0.1]
void EXPORT_DLL FishEye(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing);
void EXPORT_DLL Tube(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing);
void EXPORT_DLL MyTube(BMP_ARGB *data, int width, int height, double m_iCurvature, bool m_bInverse, bool bSmoothing);
/*
void EXPORT_DLL LiquidTest(BMP_ARGB *data, int width, int height, byte* surface);
void EXPORT_DLL Agg2DImageOnImage(BMP_ARGB *bkData, int bkWidth, int bkHeight, 
							 BMP_ARGB *overlayData, int overlayWidth, int overlayHeight);
*/
//0..100 param
void EXPORT_DLL InkSketch(BMP_ARGB *data, int width, int height, int inkOutline, int coloring);
void EXPORT_DLL EdgeDetector(BMP_ARGB *data, int width, int height);
void EXPORT_DLL EdgeMaster(BMP_ARGB *data, int width, int height, int color, int amount);

static BMP_ARGB DifferenceBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs);
static BMP_ARGB DarkenBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs);
static BMP_ARGB ScreenBlendOp_Apply(BMP_ARGB lhs, BMP_ARGB rhs);
static BMP_ARGB DesaturateOp_Apply(BMP_ARGB color);
static unsigned char ClampToByte(int x);

void EXPORT_DLL ToonEffect(BMP_ARGB *data, int width, int height);

void EXPORT_DLL OilEffect(BMP_ARGB *data, int width, int height, int range, int levels);//java
void EXPORT_DLL PastelEffect(BMP_ARGB *data, int width, int height, int range, int levels);//paint.net
void EXPORT_DLL DreamEffect(BMP_ARGB *data, int width, int height, int focus);//paint.net

void EXPORT_DLL SmearEffect(BMP_ARGB *data, int width, int height);
void EXPORT_DLL SmearEffect(BMP_ARGB *data, int width, int height, int shape, float angle, float density,
							float scatter, int distance, float mix, bool background);

static int mixColors(float t, int rgb1, int rgb2);
//inline int lerp(float t, int a, int b);
static int lerp(float t, int a, int b);
static double AngleConstrain(double MyAngle);
static double EvanMax3(double x, double y, double z);
static double EvanMin3(double x, double y, double z);
static void EvanRGBtoHSV(int R, int G, int B, double &outH, double &outS, double &outV);
static void EvanHSVtoRGB(double H, double S, double V, byte &bR, byte &bG, byte &bB);
static byte GetIntensityByte(BMP_ARGB color);
static byte FastScaleByteByByte(byte a, byte b);


int* CreateGaussianBlurRow(int amount, int &size);
int** CreateGaussianBlurMatrix(int amount, int &size);
void EXPORT_DLL GaussianBlur_PDN(BMP_ARGB *data, int width, int height, int radius);     
void EXPORT_DLL GlowEffect_PDN(BMP_ARGB *data, int width, int height, int radius, int brightness, int contrast);
void EXPORT_DLL BrightnessAndContrastAdjustment_PDN(BMP_ARGB *data, int width, int height, int brightness, int contrast);


void EXPORT_DLL TestSpeed(int count);

void EXPORT_DLL ColorFilterEx(BMP_ARGB *data, int width, int height, int color);	

static int Sign(int val);
void EXPORT_DLL JitterEffect_PDN(BMP_ARGB *data, int width, int height, 
								 int MaxDistance, int MinDistance, int Width, int Spacing,
								 int AngleDeg, int Edge);	

void EXPORT_DLL StichEffect_PDN(BMP_ARGB *data, int width, int height, 
								int Distance, int Width, int Angle1, int Angle2, bool Wrap);

void EXPORT_DLL BokehEffect_Test(BMP_ARGB *data, int width, int height);
	

/*
#ifndef _WIN32
	#ifdef __cplusplus
	}
	#endif
#endif
*/	

#endif
