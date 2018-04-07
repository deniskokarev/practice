#include "uuidmatch.h"

enum {
	P_NONE,
	P_HEX,
	P_DASH,
	P_SZ
};

/*
#!/usr/bin/env python
print "static unsigned char category[256] = {"
for c in range(0,256):
  if c>=ord('0') and c<=ord('9') or c>=ord('a') and c<=ord('f') or c>=ord('A') and c<=ord('F'):
    print "\tP_HEX,\t\t//", c
  elif c == ord('-'):
    print "\tP_DASH,\t\t//", c
  else:
    print "\tP_NONE,\t\t//", c
print "};"
*/
static unsigned char category[256] = {
	P_NONE,		// 0
	P_NONE,		// 1
	P_NONE,		// 2
	P_NONE,		// 3
	P_NONE,		// 4
	P_NONE,		// 5
	P_NONE,		// 6
	P_NONE,		// 7
	P_NONE,		// 8
	P_NONE,		// 9
	P_NONE,		// 10
	P_NONE,		// 11
	P_NONE,		// 12
	P_NONE,		// 13
	P_NONE,		// 14
	P_NONE,		// 15
	P_NONE,		// 16
	P_NONE,		// 17
	P_NONE,		// 18
	P_NONE,		// 19
	P_NONE,		// 20
	P_NONE,		// 21
	P_NONE,		// 22
	P_NONE,		// 23
	P_NONE,		// 24
	P_NONE,		// 25
	P_NONE,		// 26
	P_NONE,		// 27
	P_NONE,		// 28
	P_NONE,		// 29
	P_NONE,		// 30
	P_NONE,		// 31
	P_NONE,		// 32
	P_NONE,		// 33
	P_NONE,		// 34
	P_NONE,		// 35
	P_NONE,		// 36
	P_NONE,		// 37
	P_NONE,		// 38
	P_NONE,		// 39
	P_NONE,		// 40
	P_NONE,		// 41
	P_NONE,		// 42
	P_NONE,		// 43
	P_NONE,		// 44
	P_DASH,		// 45
	P_NONE,		// 46
	P_NONE,		// 47
	P_HEX,		// 48
	P_HEX,		// 49
	P_HEX,		// 50
	P_HEX,		// 51
	P_HEX,		// 52
	P_HEX,		// 53
	P_HEX,		// 54
	P_HEX,		// 55
	P_HEX,		// 56
	P_HEX,		// 57
	P_NONE,		// 58
	P_NONE,		// 59
	P_NONE,		// 60
	P_NONE,		// 61
	P_NONE,		// 62
	P_NONE,		// 63
	P_NONE,		// 64
	P_HEX,		// 65
	P_HEX,		// 66
	P_HEX,		// 67
	P_HEX,		// 68
	P_HEX,		// 69
	P_HEX,		// 70
	P_NONE,		// 71
	P_NONE,		// 72
	P_NONE,		// 73
	P_NONE,		// 74
	P_NONE,		// 75
	P_NONE,		// 76
	P_NONE,		// 77
	P_NONE,		// 78
	P_NONE,		// 79
	P_NONE,		// 80
	P_NONE,		// 81
	P_NONE,		// 82
	P_NONE,		// 83
	P_NONE,		// 84
	P_NONE,		// 85
	P_NONE,		// 86
	P_NONE,		// 87
	P_NONE,		// 88
	P_NONE,		// 89
	P_NONE,		// 90
	P_NONE,		// 91
	P_NONE,		// 92
	P_NONE,		// 93
	P_NONE,		// 94
	P_NONE,		// 95
	P_NONE,		// 96
	P_HEX,		// 97
	P_HEX,		// 98
	P_HEX,		// 99
	P_HEX,		// 100
	P_HEX,		// 101
	P_HEX,		// 102
	P_NONE,		// 103
	P_NONE,		// 104
	P_NONE,		// 105
	P_NONE,		// 106
	P_NONE,		// 107
	P_NONE,		// 108
	P_NONE,		// 109
	P_NONE,		// 110
	P_NONE,		// 111
	P_NONE,		// 112
	P_NONE,		// 113
	P_NONE,		// 114
	P_NONE,		// 115
	P_NONE,		// 116
	P_NONE,		// 117
	P_NONE,		// 118
	P_NONE,		// 119
	P_NONE,		// 120
	P_NONE,		// 121
	P_NONE,		// 122
	P_NONE,		// 123
	P_NONE,		// 124
	P_NONE,		// 125
	P_NONE,		// 126
	P_NONE,		// 127
	P_NONE,		// 128
	P_NONE,		// 129
	P_NONE,		// 130
	P_NONE,		// 131
	P_NONE,		// 132
	P_NONE,		// 133
	P_NONE,		// 134
	P_NONE,		// 135
	P_NONE,		// 136
	P_NONE,		// 137
	P_NONE,		// 138
	P_NONE,		// 139
	P_NONE,		// 140
	P_NONE,		// 141
	P_NONE,		// 142
	P_NONE,		// 143
	P_NONE,		// 144
	P_NONE,		// 145
	P_NONE,		// 146
	P_NONE,		// 147
	P_NONE,		// 148
	P_NONE,		// 149
	P_NONE,		// 150
	P_NONE,		// 151
	P_NONE,		// 152
	P_NONE,		// 153
	P_NONE,		// 154
	P_NONE,		// 155
	P_NONE,		// 156
	P_NONE,		// 157
	P_NONE,		// 158
	P_NONE,		// 159
	P_NONE,		// 160
	P_NONE,		// 161
	P_NONE,		// 162
	P_NONE,		// 163
	P_NONE,		// 164
	P_NONE,		// 165
	P_NONE,		// 166
	P_NONE,		// 167
	P_NONE,		// 168
	P_NONE,		// 169
	P_NONE,		// 170
	P_NONE,		// 171
	P_NONE,		// 172
	P_NONE,		// 173
	P_NONE,		// 174
	P_NONE,		// 175
	P_NONE,		// 176
	P_NONE,		// 177
	P_NONE,		// 178
	P_NONE,		// 179
	P_NONE,		// 180
	P_NONE,		// 181
	P_NONE,		// 182
	P_NONE,		// 183
	P_NONE,		// 184
	P_NONE,		// 185
	P_NONE,		// 186
	P_NONE,		// 187
	P_NONE,		// 188
	P_NONE,		// 189
	P_NONE,		// 190
	P_NONE,		// 191
	P_NONE,		// 192
	P_NONE,		// 193
	P_NONE,		// 194
	P_NONE,		// 195
	P_NONE,		// 196
	P_NONE,		// 197
	P_NONE,		// 198
	P_NONE,		// 199
	P_NONE,		// 200
	P_NONE,		// 201
	P_NONE,		// 202
	P_NONE,		// 203
	P_NONE,		// 204
	P_NONE,		// 205
	P_NONE,		// 206
	P_NONE,		// 207
	P_NONE,		// 208
	P_NONE,		// 209
	P_NONE,		// 210
	P_NONE,		// 211
	P_NONE,		// 212
	P_NONE,		// 213
	P_NONE,		// 214
	P_NONE,		// 215
	P_NONE,		// 216
	P_NONE,		// 217
	P_NONE,		// 218
	P_NONE,		// 219
	P_NONE,		// 220
	P_NONE,		// 221
	P_NONE,		// 222
	P_NONE,		// 223
	P_NONE,		// 224
	P_NONE,		// 225
	P_NONE,		// 226
	P_NONE,		// 227
	P_NONE,		// 228
	P_NONE,		// 229
	P_NONE,		// 230
	P_NONE,		// 231
	P_NONE,		// 232
	P_NONE,		// 233
	P_NONE,		// 234
	P_NONE,		// 235
	P_NONE,		// 236
	P_NONE,		// 237
	P_NONE,		// 238
	P_NONE,		// 239
	P_NONE,		// 240
	P_NONE,		// 241
	P_NONE,		// 242
	P_NONE,		// 243
	P_NONE,		// 244
	P_NONE,		// 245
	P_NONE,		// 246
	P_NONE,		// 247
	P_NONE,		// 248
	P_NONE,		// 249
	P_NONE,		// 250
	P_NONE,		// 251
	P_NONE,		// 252
	P_NONE,		// 253
	P_NONE,		// 254
	P_NONE,		// 255
};

// detect a UUID pattern e.g:
// bc25538e-8135-4f7c-9762-ed12562d745f
static UMSTATE uuid_pattern[UMPATLEN+1][P_SZ] = {
	// [0-9a-fA-F]{8}
	{0, 1, 0},		// 0
	{0, 2, 0},		// 1
	{0, 3, 0},		// 2
	{0, 4, 0},		// 3
	{0, 5, 0},		// 4
	{0, 6, 0},		// 5
	{0, 7, 0},		// 6
	{0, 8, 0},		// 7
	// -
	{0, 7, 9},		// 8
	// [0-9a-fA-F]{4}
	{0, 10, 0},		// 9
	{0, 11, 0},		// 10
	{0, 12, 0},		// 11
	{0, 13, 0},		// 12
	// -
	{0, 5, 14},		// 13
	// [0-9a-fA-F]{4}
	{0, 15, 0},		// 14
	{0, 16, 0},		// 15
	{0, 17, 0},		// 16
	{0, 18, 0},		// 17
	// -
	{0, 5, 19},		// 18
	// [0-9a-fA-F]{4}
	{0, 20, 0},		// 19
	{0, 21, 0},		// 20
	{0, 22, 0},		// 21
	{0, 23, 0},		// 22
	// -
	{0, 5, 24},		// 23
	// [0-9a-fA-F]{12}
	{0, 25, 0},		// 24
	{0, 26, 0},		// 25
	{0, 27, 0},		// 26
	{0, 28, 0},		// 27
	{0, 29, 0},		// 28
	{0, 30, 0},		// 29
	{0, 31, 0},		// 30
	{0, 32, 0},		// 31
	{0, 33, 9},		// 32
	{0, 34, 9},		// 33
	{0, 35, 9},		// 34
	{0, 36, 9},		// 35
	{0, 8, 0}	   	// 36
};

// start with automate position 0
void um_init(UMSTATE *state) {
	*state = 0;
}

// return true when ch was the last char in uuid pattern
int um_match(UMSTATE *state, char ch) {
	int cat = category[(unsigned char)ch];
	*state = uuid_pattern[*state][cat];
	if (*state == UMPATLEN) {
		*state = uuid_pattern[*state][cat];
		return 1;
	} else {
		return 0;
	}
}
