#include "battle.h"

#include <Gamebuino-Meta.h>
#include "misc.h"
#include "depack.h"
#include "player.h"
#include "board.h"
#include "sprites.h"

#include "data/enemies.h"
#include "data/largeSprites.h"

extern uint8_t decompression_buffer[];

const uint8_t enemy_backgrounds_data[] = {16, 16, 12, 0, 0, 0xFF, 1, 0x00, 0x0b,0x00, 0xb0,0x00, 0x0b,0x00, 0xb0,0x33, 0x30,0x33, 0x03,0x33, 0x30,0x33, 0x03,0xb3, 0x33,0x30, 0x33,0xb3, 0x33,0x30, 0x33,0x3b, 0x33,0x03, 0x03,0x3b, 0x33,0x03, 0x03,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0x33, 0x33,0xb3, 0xb3,0x33, 0x33,0xb3, 0xb3,0x33, 0x33,0x3b, 0x33,0x33, 0x33,0x3b, 0x33,0x33, 0x33,0x33, 0x30,0x33, 0x30,0x33, 0x30,0x33, 0x30,0x00, 0x05,0x00, 0x00,0x00, 0x05,0x00, 0x00,0x00, 0x65,0x00, 0x00,0x00, 0x65,0x00, 0x00,0x00, 0x65,0x00, 0x00,0x00, 0x65,0x00, 0x00,0x00, 0x65,0x00, 0x0b,0x00, 0x65,0x00, 0x0b,0xb0, 0x65,0x0b, 0xbb,0xb0, 0x65,0x0b, 0xbb,0x06, 0x65,0x50, 0xbb,0x06, 0x65,0x50, 0xbb,0xb0, 0x00,0x0b, 0xbb,0xb0, 0x00,0x0b, 0xbb,0x66, 0x60,0x66, 0x66,0x66, 0x65,0x66, 0x66,0x56, 0x66,0x66, 0x65,0x66, 0x66,0x66, 0x66,0x00, 0x66,0x66, 0x66,0x66, 0x60,0x00, 0x00,0x50, 0x00,0x05, 0x50,0x00, 0x55,0x00, 0x00,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x50, 0x00,0x00, 0x05,0x50, 0x00,0x00, 0x05,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x60, 0x00,0x00, 0x06,0x60, 0x00,0x00, 0x06,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0x3b,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xb3, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0x33, 0xbb,0x33, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0x33, 0xb3,0x3b, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0x3b, 0x33,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0x33,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0x88,0x8b, 0xbb,0xbb, 0xb3,0xbb, 0xbb,0xbb, 0x88,0x8b, 0xbb,0xbb, 0xbb,0x3b, 0xbb,0x88, 0xaa,0xa8, 0x8b,0xbb, 0xbb,0x33, 0xbb,0x88, 0xaa,0xa8, 0x8b,0x33, 0x3b,0x33, 0xbb,0x88, 0x8a,0x88, 0x8b,0xb3, 0x33,0xb3, 0xbb,0xbb, 0x83,0x8b, 0xbb,0xbb, 0x33,0xbb, 0xbb,0xbb, 0xb3,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xbb,0xbb, 0xb3,0x3b, 0xbb,0xff, 0xff,0xf0, 0xff,0xff, 0xff,0xf0, 0xff,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xf0, 0xf0,0x7c, 0xc0,0x7c, 0xc0,0xff, 0xff,0x80, 0xf0,0x77, 0xc0,0x77, 0xc0,0x88, 0x88,0x80, 0xf0,0x77, 0x70,0x77, 0x70,0x88, 0x88,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xff, 0xf0,0x7c, 0xc0,0x7c, 0xc0,0xf0, 0xff,0x88, 0x80,0x77, 0xc0,0x77, 0xc0,0x80, 0xf8,0x88, 0x80,0x77, 0x70,0x77, 0x70,0x80, 0xf8,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xf0, 0xff,0xff, 0xff,0xf0, 0xff,0xff, 0xff,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x60, 0x00,0x00, 0x06,0x60, 0x00,0x00, 0x06,0x66, 0x66,0x00, 0x00,0x00, 0x00,0x66, 0x66,0x66, 0x65,0x00, 0x66,0x66, 0x00,0x66, 0x65,0x66, 0x66,0x06, 0x00,0x00, 0x60,0x66, 0x66,0x65, 0x66,0x06, 0x05,0x50, 0x60,0x65, 0x65,0x66, 0x66,0x06, 0x05,0x50, 0x60,0x66, 0x66,0x66, 0x65,0x06, 0x00,0x00, 0x60,0x66, 0x66,0x56, 0x66,0x00, 0x66,0x66, 0x00,0x65, 0x66,0x66, 0x66,0x00, 0x00,0x00, 0x00,0x66, 0x65,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x60, 0x00,0x00, 0x06,0x60, 0x00,0x00, 0x06,0x66, 0x66,0x66, 0x65,0x55, 0x66,0x66, 0x66,0x66, 0x65,0x66, 0x55,0x66, 0x56,0x66, 0x65,0x66, 0x66,0x60, 0x00,0x06, 0x65,0x66, 0x66,0x65, 0x66,0x00, 0x00,0x00, 0x66,0x65, 0x65,0x66, 0x66,0x00, 0x00,0x00, 0x66,0x66, 0x66,0x66, 0x65,0x00, 0x00,0x00, 0x66,0x66, 0x66,0x56, 0x66,0x00, 0x00,0x00, 0x66,0x65, 0x66,0x66, 0x66,0x60, 0x00,0x06, 0x66,0x66, 0x65,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x60, 0x00,0x00, 0x06,0x60, 0x00,0x00, 0x06,0x66, 0x66,0x66, 0x66,0x66, 0x66,0x66, 0x66,0xdd, 0xdd,0xd6, 0x66,0xdd, 0xdd,0xd6, 0x66,0xdc, 0xdd,0xdd, 0xdd,0xdc, 0xdd,0xdd, 0xdd,0xcd, 0xcc,0xdd, 0xdd,0xcd, 0xcc,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0xcd, 0xdd,0xdd, 0xdd,0xcd, 0xdd,0xdd, 0xdc,0xdc, 0xcd,0xdd, 0xdc,0xdc, 0xcd,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0xdd, 0xdd,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x50, 0x00,0x00, 0x05,0x50, 0x00,0x00, 0x05,0x00, 0x00,0x50, 0x00,0x00, 0x00,0x50, 0x00,0x00, 0x50,0x05, 0x50,0x00, 0x50,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x50,0x50, 0x55,0x05, 0x05,0x50, 0x55,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x55, 0x05,0x05, 0x05,0x00, 0x05,0x05, 0x00,0x00, 0x05,0x05, 0x00,0x60, 0x00,0x00, 0x06,0x60, 0x00,0x00, 0x06,0xff, 0xff,0xf0, 0xff,0xff, 0xff,0xf0, 0xff,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xf0, 0xf0,0xcd, 0xd0,0xcd, 0xd0,0xff, 0xff,0x80, 0xf0,0xcc, 0xd0,0xcc, 0xd0,0x88, 0x88,0x80, 0xf0,0x7c, 0xc0,0x7c, 0xc0,0x88, 0x88,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xff, 0xf0,0xcd, 0xd0,0xcd, 0xd0,0xf0, 0xff,0x88, 0x80,0xcc, 0xd0,0xcc, 0xd0,0x80, 0xf8,0x88, 0x80,0x7c, 0xc0,0x7c, 0xc0,0x80, 0xf8,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xf0, 0xff,0xff, 0xff,0xf0, 0xff,0xff, 0xff,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x80, 0xf8,0x88, 0x88,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x44, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0x44,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x44, 0x4f,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0x44, 0x4f,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x44, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x44, 0xff,0xff, 0xff,0xff, 0xff,0xff, 0x44,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0xff, 0xff,0xff, 0xff,0xff, 0xff,0x44, 0x4f,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x4f, 0xff,0xff, 0xff,0xff, 0xff,0xf4, 0x44,0xff, 0xff,0xff, 0xff,0xff, 0xff,0x44, 0x4f,0xff, 0xff,0xff, 0xff,0xff, 0xf4,0x44, 0xff,0x0c, 0xc2,0x2c, 0xc0,0x0c, 0xc2,0x2c, 0xc0,0x20, 0xcc,0xcc, 0x12,0x20, 0xcc,0xcc, 0x02,0x02, 0x0c,0xc0, 0x21,0x12, 0x0c,0xc0, 0x20,0xc0, 0x20,0x02, 0x0c,0xc1, 0x20,0x02, 0x0c,0xc0, 0x11,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0x02, 0x0c,0x11, 0x20,0x02, 0x11,0xc0, 0x20,0x20, 0xcc,0xcc, 0x12,0x21, 0xcc,0x1c, 0x02,0x0c, 0xc2,0x2c, 0x10,0x1c, 0xc2,0x2c, 0xc1,0x0c, 0xc2,0x2c, 0xc1,0x0c, 0xc2,0x2c, 0x10,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x02,0x02, 0x0c,0xc0, 0x21,0x11, 0x1c,0xc0, 0x20,0xc0, 0x10,0x02, 0x01,0xc0, 0x21,0x02, 0x0c,0x11, 0x20,0x02, 0x1c,0xc0, 0x20,0x02, 0x0c,0x12, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x01,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x0c, 0xc2,0x2c, 0xc0,0x0c, 0xc2,0x2c, 0xc0,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x02,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x02,0x0c, 0xc2,0x2c, 0xc0,0x0c, 0xc2,0x2c, 0xc0,0x0c, 0xc2,0x2c, 0xc0,0x0c, 0xc2,0x2c, 0xc0,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x02,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0x02, 0x0c,0xc0, 0x20,0x02, 0x0c,0xc0, 0x20,0x20, 0xcc,0xcc, 0x02,0x20, 0xcc,0xcc, 0x02,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00};

Image enemy_backgrounds_image(enemy_backgrounds_data);



const Enemy_Background_Look enemy_background_looks[] = {
	{  0, { SPRITE_1, SPRITE_1, SPRITE_1, SPRITE_1 } },
	{  1, { SPRITE_203, SPRITE_203, SPRITE_203, SPRITE_203 } },
	{  2, { SPRITE_1, SPRITE_126, SPRITE_126, SPRITE_1 } },
	{  3, { SPRITE_308, SPRITE_308, SPRITE_308, SPRITE_308 } },
	{  4, { SPRITE_203, SPRITE_203, SPRITE_203, SPRITE_203 } },
	{  5, { SPRITE_203, SPRITE_203, SPRITE_203, SPRITE_203 } },
	{  6, { SPRITE_101, SPRITE_101, SPRITE_101, SPRITE_101 } },
	{  7, { SPRITE_203, SPRITE_203, SPRITE_203, SPRITE_203 } },
	{  8, { SPRITE_308, SPRITE_308, SPRITE_308, SPRITE_308 } },
	{  9, { SPRITE_229, SPRITE_228, SPRITE_228, SPRITE_229 } },
	{ 10, { SPRITE_268, SPRITE_272, SPRITE_272, SPRITE_268 } },
	{ 11, { SPRITE_268, SPRITE_272, SPRITE_272, SPRITE_268 } },
};

const uint8_t enemy_backgrounds[] = {
	0, // dogglen, has forest background for enemy explaining
	0,
	0,
	1,
	3, // aerilon, has background for speed-learning
	2,
	3,
	3,
	4,
	5,
	6,
	7,
	0, // cliff break
	2,
	8,
	9,
	2,
	10,
	10,
	11,
};


const uint8_t reuben_buffer[] = {16, 17, 1, 0, 0, 0x0A, 1, 0xaa, 0xaa,0xa0, 0x00,0x00, 0x0a,0xaa, 0xaa,0xaa, 0xaa,0x01, 0xd1,0xd1, 0xd0,0x0a, 0xaa,0xaa, 0x00,0x00, 0x00,0x1d, 0x1c,0xd0, 0xaa,0xa0, 0x88,0xe8, 0xee,0x01, 0xd1,0xcd, 0x0a,0x0e, 0x00,0x00, 0x08,0xe0, 0x1d,0x1c, 0xd0,0xa0, 0x80,0x55, 0x55,0x08, 0x01,0xd1, 0xc0,0xaa, 0x05,0x44, 0x44,0x40, 0xe0,0x1d, 0x10,0xaa, 0xa0,0x17, 0xf1,0x74, 0x08,0x00, 0x0a,0xaa, 0x00,0xd7, 0xfd,0x7f, 0x40,0x0a, 0xaa,0xa0, 0x10,0xff, 0xff,0xf4, 0x01,0x10, 0xaa,0xa0, 0xd1,0x04, 0x44,0x40, 0x1d,0xc1, 0x0a,0xa0, 0x01,0xd0, 0x00,0x05, 0x51,0xdc, 0x10,0x0f, 0x65,0x1d, 0xcd,0x5f, 0x65,0x1d, 0xc0,0x06, 0x65,0x01, 0xd1,0x56, 0x60,0x1d, 0xd0,0xa0, 0x00,0x00, 0x00,0x00, 0x00,0x01, 0xd0,0xaa, 0xa0,0x45, 0x50,0x45, 0x50,0x00, 0x0a,0xaa, 0xaa,0x00, 0x0a,0x00, 0x00,0xaa, 0xaa};

const uint8_t swoosh_buffer[] = {
	7, 15,
	0x01, 0x00,
	0,
	1,
	1,
	
	0x11, 0x11, 0x11, 0x01,
	0x11, 0x11, 0x11, 0x01,
	0x11, 0x11, 0x10, 0x01,
	0x11, 0x11, 0x10, 0x01,
	0x11, 0x11, 0x00, 0x01,
	0x11, 0x11, 0x00, 0x11,
	0x11, 0x00, 0x00, 0x11,
	0x11, 0x10, 0x01, 0x11,
	0x11, 0x00, 0x01, 0x11,
	0x11, 0x00, 0x11, 0x11,
	0x10, 0x00, 0x11, 0x11,
	0x10, 0x01, 0x11, 0x11,
	0x00, 0x01, 0x11, 0x11,
	0x00, 0x11, 0x11, 0x11,
	0x01, 0x11, 0x11, 0x11,
};

const uint8_t battle_explosion_data[] = {36, 36, 1, 0, 0, 0x07, 1, 0x77, 0x77,0x77, 0x77,0x77, 0x77,0x7a, 0x77,0xa7, 0x7a,0x77, 0xa7,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xa7,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x77,0xa7, 0xa7,0xa7, 0xa7,0xa7, 0xa7,0xa7, 0x7a,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x7a,0x7a, 0x7a,0x77, 0x79,0x7a, 0x7a,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x7a, 0x7a,0xaa, 0x7a,0x7a, 0x77,0x79, 0x79,0x77, 0xa7,0xa7, 0xa7,0x7a, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xaa,0x77, 0x97,0x99, 0x97,0x99, 0x77,0xa7, 0xa7,0x77, 0x77,0x77, 0x77,0x77, 0x7a,0x77, 0xa7,0x7a, 0x7a,0xa7, 0x99,0x79, 0x79,0x77, 0x97,0xa7, 0xa7,0x77, 0xa7,0x77, 0x77,0x77, 0x77,0xa7, 0xa7,0x7a, 0x7a,0x79, 0x79,0x97, 0x97,0x97, 0x99,0x79, 0x7a,0xa7, 0x77,0x77, 0x77,0x77, 0xa7,0x7a, 0x7a,0xaa, 0xa7,0x97, 0x97,0x99, 0x99,0x99, 0x79,0x79, 0x77,0x77, 0x7a,0x7a, 0x77,0x77, 0x77,0x7a, 0xa7,0x77, 0x79,0x79, 0x99,0x79, 0x79,0x77, 0x99,0x79, 0x79,0x7a, 0x77,0x77, 0x77,0x77, 0xa7,0xa7, 0x77,0x99, 0x99,0x97, 0x99,0x97, 0x87,0x99, 0x97,0x97, 0x97,0x7a, 0x7a,0x77, 0x77,0x7a, 0x77,0xa7, 0x99,0x79, 0x79,0x79, 0x79,0x88, 0x88,0x87, 0x99,0x79, 0x79,0x7a, 0x7a,0x77, 0x77,0x77, 0x7a,0x77, 0x97,0x99, 0x77,0x99, 0x87,0x87, 0x78,0x88, 0x97,0x97, 0x99,0x77, 0x7a,0x7a, 0x77,0xa7, 0xaa,0x77, 0x97,0x99, 0x99,0x77, 0x88,0x88, 0x77,0x88, 0x79,0x99, 0x79,0x79, 0x97,0x77, 0x7a,0x7a, 0x77,0xa7, 0x99,0x79, 0x79,0x87, 0x87,0x88, 0x88,0x78, 0x87,0x99, 0x79,0x97, 0x7a,0x7a, 0x77,0x77, 0x77,0xa7, 0x97,0x99, 0x78,0x88, 0x88,0x87, 0x88,0x88, 0x89,0x99, 0x79,0x79, 0x7a,0x77, 0x77,0x7a, 0x7a,0x79, 0x99,0x79, 0x97,0x88, 0x78,0x77, 0xe7,0x78, 0x78,0x79, 0x97,0x97, 0x97,0x7a, 0x77,0xa7, 0x77,0xa7, 0x77,0x99, 0x98,0x88, 0xee,0xee, 0xe8,0x88, 0x87,0x99, 0x79,0x97, 0x97,0xa7, 0x77,0x7a, 0x7a,0xa7, 0x99,0x97, 0x87,0x7e, 0xe7,0xee, 0x78,0x87, 0x88,0x87, 0x97,0x79, 0x77,0x77, 0xa7,0x77, 0x77,0x79, 0x97,0x97, 0x88,0x87, 0xee,0xe7, 0x88,0x78, 0x78,0x79, 0x97,0x97, 0xa7,0xa7, 0x77,0xa7, 0xa7,0x79, 0x77,0x97, 0x88,0x78, 0xe7,0x88, 0x88,0x88, 0x78,0x87, 0x79,0x97, 0x7a,0x77, 0xa7,0x7a, 0x7a,0xa7, 0x99,0x79, 0x97,0x88, 0x88,0x87, 0x88,0x88, 0x78,0x79, 0x97,0x7a, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x79,0x77, 0x88,0x87, 0x88,0x78, 0x77,0x88, 0x88,0x79, 0x99,0x7a, 0x7a,0x7a, 0x77,0x7a, 0x7a,0x7a, 0x79,0x99, 0x78,0x78, 0x88,0x87, 0x88,0x88, 0x78,0x99, 0x79,0x7a, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x79,0x79, 0x79,0x99, 0x77,0x88, 0x87,0x88, 0x78,0x79, 0x79,0x77, 0xaa,0x77, 0x77,0x7a, 0x77,0x7a, 0x79,0x79, 0x79,0x79, 0x99,0x78, 0x79,0x97, 0x77,0x97, 0x99,0x7a, 0x77,0x7a, 0x77,0x77, 0x7a,0xa7, 0x79,0x77, 0x97,0x97, 0x77,0x97, 0x99,0x79, 0x97,0x77, 0x79,0x77, 0x7a,0x77, 0x77,0x77, 0x77,0x7a, 0x77,0x79, 0x77,0x99, 0x79,0x99, 0x79,0x79, 0x7a,0xaa, 0x79,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xa7,0xa7, 0x79,0x79, 0x77,0x79, 0x79,0x77, 0xaa,0x7a, 0x77,0xa7, 0x77,0x77, 0x77,0x77, 0x7a,0x77, 0xa7,0x7a, 0xa7,0xa7, 0xaa,0xa7, 0xa7,0xa7, 0xa7,0xa7, 0x77,0x77, 0xa7,0x77, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x77,0xa7, 0xa7,0x7a, 0x7a,0x77, 0x77,0x7a, 0x77,0xa7, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xa7,0x77, 0xa7,0xa7, 0xa7,0xa7, 0x77,0xa7, 0xa7,0xa7, 0x7a,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x77,0x7a, 0x77,0xa7, 0xa7,0xa7, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xa7,0x77, 0xa7,0x77, 0x77,0x77, 0xa7,0xa7, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0xa7, 0x77,0xa7, 0x7a,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0xa7,0x77, 0x77,0x77, 0x77,0x77, 0x77};
const uint8_t battle_bolt_data[] = {7, 8, 1, 0, 0, 0x07, 1, 0x77, 0x70,0xaa, 0x07,0x77, 0x70,0xa0, 0x77,0x77, 0x0a,0x07, 0x77,0x70, 0xa0,0x77, 0x77,0x70, 0xa0,0x00, 0x77,0x0a, 0xaa,0xaa, 0x07,0x70, 0x00,0xaa, 0x07,0x77, 0x70,0xaa, 0x07};
const uint8_t battle_ice_data[] = {8, 8, 1, 0, 0, 0x07, 1, 0x77, 0x77,0x77, 0x77,0x77, 0x77,0xcd, 0xdd,0x7c, 0xcc,0xcc, 0x77,0xdd, 0xcc,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0xcd, 0xdd,0x7c, 0xcc,0xcc, 0x77,0xdd, 0xcc,0x77, 0x77};
const uint8_t battle_stun_data[] = {7, 7, 1, 0, 0, 0x07, 1, 0x97, 0xa0,0xa7, 0x97,0x79, 0x70,0x79, 0x77,0xa7, 0x00,0x07, 0xa7,0x00, 0x0a,0x00, 0x07,0xa7, 0x00,0x07, 0xa7,0x79, 0x70,0x79, 0x77,0x97, 0xa0,0xa7, 0x97};
const uint8_t battle_poison_data[] = {8, 5, 1, 0, 0, 0x07, 1, 0x72, 0x77,0x79, 0x79,0x28, 0x29,0x77, 0x77,0x29, 0x27,0x78, 0x87,0x28, 0x27,0x89, 0x98,0x72, 0x77,0x78, 0x87};
const uint8_t battle_stun_bar[] = {3, 17, 1, 0, 0, 0x08, 1, 0x87, 0x88,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x70, 0x78,0x87, 0x88};

Image enemy_poison(battle_poison_data);
Image stun_bar(battle_stun_bar);

const uint8_t reuben_swords_data[] = {14, 11, 3, 0, 0, 0x08, 1, 0x55, 0x58,0x88, 0x88,0x88, 0x88,0x88, 0x5c,0x75, 0x88,0x88, 0x88,0x88, 0x88,0x06, 0xc7,0x58, 0x88,0x88, 0x88,0x88, 0x80,0x6c, 0x75,0x88, 0x88,0x88, 0x88,0x88, 0x06,0xc7, 0x58,0x88, 0x88,0x88, 0x88,0x80, 0x6c,0x75, 0x88,0x88, 0x88,0x88, 0x88,0x06, 0xc7,0x00, 0x88,0x88, 0x88,0x88, 0x80,0x60, 0xa0,0x58, 0x88,0x88, 0x88,0x88, 0x0a,0x0f, 0xf5,0x88, 0x88,0x88, 0x80,0xa0, 0x04,0xf5, 0x88,0x88, 0x88,0x88, 0x08,0x80, 0x08,0x88, 0x88,0x88, 0x88,0x88, 0x80,0x08, 0x88,0x85, 0x55,0x55, 0x55,0x50, 0xa0,0x58, 0x57,0x77, 0x77,0x77, 0x70,0xa0, 0xf5,0x5c, 0xcc,0xcc, 0xcc,0xc0, 0xa0,0x45, 0x80,0x00, 0x00,0x00, 0x00,0xa0, 0x08,0x88, 0x88,0x88, 0x88,0x80, 0x08,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x88,0x88, 0x00,0x58, 0x88,0x88, 0x88,0x88, 0x80,0xa5, 0xf5,0x88, 0x88,0x88, 0x88,0x88, 0x0a,0x54, 0x58,0x88, 0x88,0x88, 0x85,0x70, 0xa5,0x08, 0x88,0x88, 0x88,0x57, 0xc6,0x09, 0x08,0x88, 0x88,0x85, 0x7c,0x60, 0x80,0x88, 0x88,0x88, 0x57,0xc6, 0x08,0x88, 0x88,0x88, 0x85,0x7c, 0x60,0x88, 0x88,0x88, 0x88,0x57, 0xc6,0x08, 0x88,0x88, 0x88,0x88, 0x5c,0x60, 0x88,0x88, 0x88,0x88, 0x88,0x50, 0x08,0x88, 0x88,0x88, 0x88,0x0088};
Image reuben_image(reuben_buffer);

const uint8_t battle_menu_data[] = {27, 27, 1, 0, 0, 0x03, 1, 0x34, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x37,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x47, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x77,0x77, 0x47,0x34, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x44,0x44, 0x37};

const uint8_t battle_numbers_data[] = {5, 7, 14, 0, 0, 0x0A, 1, 0xa7, 0x77,0xa7, 0x70,0x00, 0x77,0x70, 0x70,0x77, 0x70,0x70, 0x77,0x70, 0x70,0x77, 0x70,0x00, 0x77,0xa7, 0x77,0xa7, 0xaa,0x7a, 0xa7,0xa7, 0x07,0xa7, 0x70,0x07, 0xa7,0xa7, 0x07,0xa7, 0xa7,0x07, 0xa7,0x70, 0x00,0x77, 0xa7,0x77, 0xa7,0xa7, 0x77,0xa7, 0x70,0x00, 0x77,0xa7, 0x70,0x77, 0x70,0x00, 0x77,0x70, 0x77,0xa7, 0x70,0x00, 0x77,0xa7, 0x77,0xa7, 0xa7,0x77, 0xa7,0x70, 0x00,0x77, 0xa7,0x70, 0x77,0xa7, 0x00,0x77, 0xa7,0x70, 0x77,0x70, 0x00,0x77, 0xa7,0x77, 0xa7,0xa7, 0xa7,0xa7, 0x70,0x70, 0x77,0x70, 0x70,0x77, 0x70,0x00, 0x77,0xa7, 0x70,0x77, 0xaa,0x70, 0x77,0xaa, 0xa7,0xa7, 0xa7,0x77, 0xa7,0x70, 0x00,0x77, 0x70,0x77, 0xa7,0x70, 0x00,0x77, 0xa7,0x70, 0x77,0x70, 0x00,0x77, 0xa7,0x77, 0xa7,0xa7, 0x77,0xa7, 0x70,0x00, 0x77,0x70, 0x77,0xa7, 0x70,0x00, 0x77,0x70, 0x70,0x77, 0x70,0x00, 0x77,0xa7, 0x77,0xa7, 0xa7,0x77, 0xa7,0x70, 0x00,0x77, 0xa7,0x70, 0x77,0xaa, 0x70,0x77, 0xaa,0x70, 0x77,0xaa, 0x70,0x77, 0xaa,0xa7, 0xa7,0xa7, 0x77,0xa7, 0x70,0x00, 0x77,0x70, 0x70,0x77, 0x70,0x00, 0x77,0x70, 0x70,0x77, 0x70,0x00, 0x77,0xa7, 0x77,0xa7, 0xa7,0x77, 0xa7,0x70, 0x00,0x77, 0x70,0x70, 0x77,0x70, 0x00,0x77, 0xa7,0x70, 0x77,0x70, 0x00,0x77, 0xa7,0x77, 0xa7,0xaa, 0xaa,0xa7, 0xaa,0x7a, 0xa7,0xa7, 0x07,0xa7, 0xaa,0x7a, 0xa7,0xa7, 0x07,0xa7, 0xaa,0x7a, 0xa7,0xaa, 0xaa,0xa7, 0xa7,0xa7, 0xa7,0x70, 0x70,0x77, 0x70,0x70, 0x77,0x70, 0x00,0x77, 0x70,0x70, 0x77,0x70, 0x70,0x77, 0xa7,0xa7, 0xa7,0xa7, 0xa7,0xa7, 0x70,0x70, 0x77,0x70, 0x00,0x77, 0x70,0x00, 0x77,0x70, 0x70,0x77, 0x70,0x70, 0x77,0xa7, 0xa7,0xa7, 0xa7,0x7a, 0xa7,0x70, 0x07,0xa7, 0x70,0x70, 0x77,0x70, 0x70,0x77, 0x70,0x07, 0xa7,0x70, 0x7a,0xa7, 0xa7,0xaa, 0xa7};
Image battle_numbers(battle_numbers_data);

const uint8_t BATTLE_REUBEN_POS_X = 80 - 16 - 5;
const uint8_t BATTLE_REUBEN_POS_Y = 64 - 16 - 9;

void Battle::playerAttackAnimation() {
	Image reuben_swords(reuben_swords_data);
	reuben_swords.setFrame(0);
	gb.display.drawImage(BATTLE_REUBEN_POS_X - 8, BATTLE_REUBEN_POS_Y + 4, reuben_swords);
	waitCycles(2);
	
	render();
	reuben_swords.setFrame(1);
	gb.display.drawImage(BATTLE_REUBEN_POS_X - 10, BATTLE_REUBEN_POS_Y + 10, reuben_swords);
	waitCycles(2);
	
	render();
	reuben_swords.setFrame(2);
	gb.display.drawImage(BATTLE_REUBEN_POS_X - 8, BATTLE_REUBEN_POS_Y + 12, reuben_swords);
	waitCycles(2);
	
	Image swoosh(swoosh_buffer);
	gb.display.drawImage(15, 39, swoosh);
	gb.display.drawImage(22, 27, swoosh);
}

void Battle::playerJump() {
	uint8_t x = BATTLE_REUBEN_POS_X;
	uint8_t y = BATTLE_REUBEN_POS_Y;
	for (uint8_t i = 0; i < 9; i++) {
		y--;
		render(false);
		gb.display.drawImage(x, y, reuben_image);
		while(!gb.update());
	}
	for (uint8_t i = 0; i < 9; i++) {
		y++;
		render(false);
		gb.display.drawImage(x, y, reuben_image);
		while(!gb.update());
	}
	render();
}

void Battle::enemyBlink() {
	for (uint8_t i = 0; i < 4; i++) {
		render(true, false);
		while(!gb.update());
		render();
		while(!gb.update());
	}
}

void Battle::fireAnimation(uint8_t x, uint8_t y) {
	Image fire(battle_explosion_data);
	for (uint8_t i = 0; i < 10; i++) {
		render();
		gb.display.drawImage(x, y, fire);
		while(!gb.update());
		render();
		while(!gb.update());
	}
}

void Battle::boltAnimation(uint8_t x, uint8_t y) {
	Image bolt(battle_bolt_data);
	uint8_t yy = 0;
	uint8_t yyy = 0;
	render();
	for (uint8_t i = 0; i < 20; i++) {
		gb.display.clear(WHITE);
		while(!gb.update());
		render();
		yy = 0;
		while (yy < yyy) {
			gb.display.drawImage(x, yy, bolt);
			yy += 8;
		}
		while(!gb.update());
		if (yyy < y) {
			yyy += 8;
		}
	}
}

void Battle::iceAnimation() {
	Image ice(battle_ice_data);
	uint8_t j_end = 1;
	for (uint8_t i = 0; i < 20; i++) {
		gb.display.clear(LIGHTBLUE);
		while(!gb.update());
		render();
		for (uint8_t j = 0; j < j_end; j++) {
			for (uint8_t k = 0; k < 8; k++) {
				gb.display.drawImage(k*8, j*8, ice);
			}
		}
		while(!gb.update());
		if (j_end < 8) {
			j_end++;
		}
	}
}

void Battle::stunAnimation() {
	Image stun(battle_stun_data);
	
	render();
	gb.display.drawImage(60, 19, stun);
	waitCycles(4);
	
	render();
	gb.display.drawImage(48, 13, stun);
	waitCycles(4);
	
	render();
	gb.display.drawImage(40, 15, stun);
	waitCycles(4);
}


uint16_t Battle::calcPlayerDamage(Battle_Attack_Type type) {
	uint16_t upper = (2*p.lvl*p.lvl + random(10*p.lvl) + 2) * p.sword;
	uint16_t lower = 2*e.lvl;
	uint16_t ret = (upper + (lower / 2)) / lower;
	if (type == Battle_Attack_Type::normal) {
		return ret;
	}
	return (e.slots[(uint8_t)type - 1] & 0x0F) * ret;
}

uint16_t Battle::calcEnemyDamage() {
	uint16_t upper = 5 + random(10*e.lvl) + e.lvl*e.lvl*e.lvl;
	uint16_t lower = 2*p.lvl + 4*(random(p.armor) + p.armor) + p.armor*p.armor;
	return ((upper + (lower / 2)) / lower) * 5;
}

void Battle::playerAttack(Battle_Attack_Type type) {
	uint16_t damage = calcPlayerDamage(type);
	
	char text[10];
	sprintf(text, "%d", damage);
	drawText(52, 16, text);
	waitCycles(45);
	if (damage > e.hp) {
		e.hp = 0;
	} else {
		e.hp -= damage;
	}
	p.state = Battle_Player_State::normal;
	p.curwait = p.wait;
}

bool Battle::useMp(uint8_t amount) {
	if (amount > p.mp) {
		return false;
	}
	p.mp = player.useMp(amount);
	return true;
}


void Battle::enemyAttack() {
	e.curwait = e.wait;
	enemyBlink();
	
	switch(e.slots[random(5)] & 0xF0) {
		case 0x00:
		default:
			// normal attack
			enemyNormalAttack();
			break;
		case 0x10:
			// fire attack
			enemyFireAttack();
			break;
		case 0x20:
			// bolt attack
			enemyBoltAttack();
			break;
		case 0x30:
			// poison
			if (p.poison) {
				enemyNormalAttack();
				break;
			}
			p.poison = e.wait;
			break;
		case 0x40:
			// stun
			if (p.stuncounter) {
				enemyNormalAttack();
				break;
			}
			p.stuncounter = e.wait;
			enemyAttack();
			break;
	}
}

void Battle::enemyNormalAttack() {
	uint8_t damage = calcEnemyDamage();
	char text[10];
	sprintf(text, "%d", damage);
	
	Image swoosh(swoosh_buffer);
	
	for (int8_t i = 8; i >= 0; i -= 2) {
		for (uint8_t j = 0; j < i; j += 2) {
			render(true, true, j);
			gb.display.drawImage(BATTLE_REUBEN_POS_X + 8, BATTLE_REUBEN_POS_Y - 7 + j, swoosh);
			gb.display.drawImage(BATTLE_REUBEN_POS_X + 1, BATTLE_REUBEN_POS_Y + 5 + j, swoosh);
			drawText(60, 20 + j, text);
			while(!gb.update());
		}
	}
	
	render();
	gb.display.drawImage(BATTLE_REUBEN_POS_X + 8, BATTLE_REUBEN_POS_Y - 7, swoosh);
	gb.display.drawImage(BATTLE_REUBEN_POS_X + 1, BATTLE_REUBEN_POS_Y + 5, swoosh);
	drawText(60, 20, text);
	
	waitCycles(15);
	p.hp = player.damage(damage);
}

void Battle::enemyFireAttack() {
	fireAnimation(BATTLE_REUBEN_POS_X - 10, BATTLE_REUBEN_POS_Y - 10);
	uint8_t damage = calcEnemyDamage()*2;
	render();
	char text[10];
	sprintf(text, "%d", damage);
	drawText(60, 20, text);
	waitCycles(45);
	p.hp = player.damage(damage);
}

void Battle::enemyBoltAttack() {
	boltAnimation(BATTLE_REUBEN_POS_X + 4, BATTLE_REUBEN_POS_Y + 4);
	uint8_t damage = calcEnemyDamage()*4;
	render();
	char text[10];
	sprintf(text, "%d", damage);
	drawText(57, 20, text);
	waitCycles(45);
	p.hp = player.damage(damage);
}

void Battle::enemyPoison() {
	uint8_t damage = e.lvl;
	p.hp = player.damage(damage);
	p.poison = e.wait;
	
	render();
	char text[10];
	sprintf(text, "%d", damage);
	drawText(57, 20, text);
	waitCycles(45);
	
}

Image enemyImage;

void Battle::render(bool render_reuben, bool render_enemy, int8_t y_offset) {
	// render top background
	for (uint8_t i = 0; i < 80/16; i++) {
		gb.display.drawImage(i*16, 0 + y_offset, enemy_backgrounds_image);
	}
	// render 4x4 grid of background tiles
	for (uint8_t y = 2; y < 8;) {
		for (uint8_t x = 0; x < 10;) {
			sprites.setFrame(background_look->sprites[0]);
			gb.display.drawImage(x*8, y*8 + y_offset, sprites);
			x++;
			sprites.setFrame(background_look->sprites[1]);
			gb.display.drawImage(x*8, y*8 + y_offset, sprites);
			x++;
		}
		y++;
		for (uint8_t x = 0; x < 10;) {
			sprites.setFrame(background_look->sprites[2]);
			gb.display.drawImage(x*8, y*8 + y_offset, sprites);
			x++;
			sprites.setFrame(background_look->sprites[3]);
			gb.display.drawImage(x*8, y*8 + y_offset, sprites);
			x++;
		}
		y++;
	}
	
	// render enemy
	if (render_enemy) {
		gb.display.drawImage(enemies[i].xpos, enemies[i].ypos + y_offset, enemyImage);
		if (e.stuncounter) {
			gb.display.setColor(BLACK);
			gb.display.drawRect(0, 16 + y_offset, 48, 48);
			gb.display.setColor(WHITE);
			gb.display.drawRect(1, 17 + y_offset, 46, 46);
		}
	}
	
	// render player
	if (render_reuben) {
		gb.display.drawImage(BATTLE_REUBEN_POS_X, BATTLE_REUBEN_POS_Y + y_offset, reuben_image);
		if (p.poison) {
			gb.display.drawImage(BATTLE_REUBEN_POS_X + 4, BATTLE_REUBEN_POS_Y - 6 + y_offset, enemy_poison);
		}
		if (p.stuncounter) {
			gb.display.drawImage(BATTLE_REUBEN_POS_X - 4, BATTLE_REUBEN_POS_Y + y_offset, stun_bar);
			gb.display.drawImage(BATTLE_REUBEN_POS_X + 17, BATTLE_REUBEN_POS_Y + y_offset, stun_bar);
		}
	}
	
	gb.display.setCursor(0, 0);
	gb.display.setColor(BLACK, WHITE);
	gb.display.print(gb.getCpuLoad());
}

Battle_Done Battle::loop() {
	uint8_t cursor_menu = 0;
	uint8_t cursor_magic = 0;
	Image menu_image(battle_menu_data);
	while(1) {
		if (!gb.update()) {
			continue;
		}
		render();
		
		bool player_disp_hp = true;
		if (gb.buttons.pressed(BUTTON_C)) {
			statsMenu();
			continue; // make sure we do accidental shadowbutton triggers
		}
		if (p.stuncounter) {
			// we are stunned
			p.stuncounter--;
		} else if (p.curwait) {
			// we still have to wait
			p.curwait--;
			cursor_menu = 0;
			gb.display.setColor(BROWN);
			gb.display.drawFastHLine(54, 64 - 16 - 8 - 8, 24);
			gb.display.drawFastHLine(54, 64 - 16 - 8 - 10, 24);
			gb.display.drawPixel(53, 64 - 16 - 8 - 9);
			gb.display.drawPixel(53 + 25, 64 - 16 - 8 - 9);
			gb.display.setColor(RED);
			gb.display.drawFastHLine(54, 64 - 16 - 8 - 9, 24 * (p.wait - p.curwait) / p.wait);
		} else {
			switch(p.state) {
				case Battle_Player_State::normal:
				{
					// Normal attack menu
					if (gb.buttons.pressed(BUTTON_UP)) {
						if (cursor_menu) {
							cursor_menu--;
						} else {
							cursor_menu = 3;
						}
					}
					
					if (gb.buttons.pressed(BUTTON_DOWN)) {
						if (cursor_menu < 3) {
							cursor_menu++;
						} else {
							cursor_menu = 0;
						}
					}
					
					gb.display.drawImage(53, 6, menu_image);
					
					gb.display.setColor(BEIGE);
					gb.display.fillRect(54, 7 + 6*cursor_menu, 6*4 + 1, 7);
					gb.display.setColor(BLACK);
					gb.display.setCursor(55, 8);
					gb.display.println("Attack");
					gb.display.setCursorX(55);
					gb.display.println("Magic");
					gb.display.setCursorX(55);
					gb.display.println("Item");
					gb.display.setCursorX(55);
					gb.display.println("Run");
					
					
					if (gb.buttons.pressed(BUTTON_A)) {
						render();
						switch(cursor_menu) {
							case 0:
								playerAttackAnimation();
								playerAttack(Battle_Attack_Type::normal);
								break;
							case 1:
								p.state = Battle_Player_State::magic;
								cursor_magic = 0;
								break;
							case 2:
								// TODO: items
								break;
							case 3:
								if (!(e.slots[4] & 0x0F)) {
									break;
								}
								// TODO: no running away from maru
								if (!random(2)) {
									return Battle_Done::run;
								}
								p.state = Battle_Player_State::normal;
								p.curwait = p.wait;
								break;
						}
					}
					break;
				}
				case Battle_Player_State::magic:
					// Magic attack menu
					player_disp_hp = false;
					
					if (gb.buttons.pressed(BUTTON_UP)) {
						if (cursor_magic) {
							cursor_magic--;
						} else {
							cursor_magic = 3;
						}
					}
					
					if (gb.buttons.pressed(BUTTON_DOWN)) {
						if (cursor_magic < 3) {
							cursor_magic++;
						} else {
							cursor_magic = 0;
						}
					}
					
					gb.display.drawImage(53, 6, menu_image);
					gb.display.setColor(BEIGE);
					gb.display.fillRect(54, 7 + 6*cursor_magic, 6*4 + 1, 7);
					gb.display.setColor(BLACK);
					gb.display.setCursor(55, 8);
					gb.display.println("Fire");
					gb.display.setCursorX(55);
					gb.display.println("Ice");
					gb.display.setCursorX(55);
					gb.display.println("Bolt");
					gb.display.setCursorX(55);
					gb.display.println("Stun");
					
					if (gb.buttons.pressed(BUTTON_A)) {
						render();
						switch(cursor_magic) {
							case 0:
								if (useMp(5)) {
									playerJump();
									fireAnimation(7, 22);
									playerAttack(Battle_Attack_Type::fire);
								}
								break;
							case 1:
								if (useMp(5)) {
									playerJump();
									iceAnimation();
									playerAttack(Battle_Attack_Type::ice);
								}
								break;
							case 2:
								if (useMp(5)) {
									playerJump();
									boltAnimation(21, 36);
									playerAttack(Battle_Attack_Type::bolt);
								}
								break;
							case 3:
								if (useMp(10)) {
									playerJump();
									stunAnimation();
									e.stuncounter = 0xFF;
									p.state = Battle_Player_State::normal;
									cursor_menu = 0;
								}
								break;
						}
					}
					if (gb.buttons.pressed(BUTTON_B)) {
						p.state = Battle_Player_State::normal;
					}
					break;
			}
		}
		
		if (player_disp_hp) {
			char text[10];
			sprintf(text, "HP:%d", p.hp);
			drawText(52, 58, text);
		} else {
			char text[10];
			sprintf(text, "MP:%d", p.mp);
			drawText(52, 58, text);
		}
		
		if (e.stuncounter) {
			// enemy is stunned
			e.stuncounter--;
		} else if (e.curwait) {
			// enemy has to wait
			e.curwait--;
		} else if (!random(25)) {
			// ATTACK!!!
			enemyAttack();
		}
		
		if (p.poison) {
			if (!(--p.poison)) {
				enemyPoison();
			}
		}
		if (p.hp <= 0) {
			return Battle_Done::lose;
		}
		if (e.hp <= 0) {
			return Battle_Done::win;
		}
	}
}

void Battle::drawText(uint8_t x, uint8_t y, char* text) {
	x--;
	y--;
	while (char c = *(text++)) {
		const char chars[] = "0123456789:HMP";
		battle_numbers.setFrame((uint32_t)memchr(chars, c, sizeof(chars)) - (uint32_t)chars);
		gb.display.drawImage(x, y, battle_numbers);
		x += 4;
	}
}

bool Battle::fight(uint8_t _i) {
	i = _i;
	p.lvl = player.getLvl();
	p.hp = player.getHp();
	p.mp = player.getMp();
	p.armor = player.armor;
	p.wait = player.wait;
	p.sword = player.sword;
	p.stuncounter = 0;
	p.poison = 0;
	p.state = Battle_Player_State::normal;
	
	p.lvl = 4;
	p.wait = 50;
	p.sword = WEAPON_STICK;
	
	e.lvl = enemies[i].lvl;
	e.hp = enemies[i].hp;
	e.wait = enemies[i].wait;
	e.slots[0] = enemies[i].sl1;
	e.slots[1] = enemies[i].sl2;
	e.slots[2] = enemies[i].sl3;
	e.slots[3] = enemies[i].sl4;
	e.slots[4] = enemies[i].sl5;
	
	e.wait = 50;
	
	
	background_look = &enemy_background_looks[enemy_backgrounds[board.getWorldId()]];
	enemy_backgrounds_image.setFrame(background_look->frame_id);
	
	// time to check for dynamic lvl / exp / wait
	if (e.lvl > 200)  {
		int16_t lvl = p.lvl - random(e.lvl & 0x0F) - 2;
		e.lvl = lvl <= 0 ? 1 : lvl;
	}
	if (e.hp >= 0xFF00) {
		e.hp &= 0xFF;
		e.hp = (player.getHpMax() + (e.hp/2)) / e.hp;
	}
	if (p.lvl - e.lvl > 6) {
		e.lvl = random(p.lvl - e.lvl - 1);
		if ((e.wait - p.wait) > 30) {
			e.wait = e.wait - random(e.wait - p.wait);
		}
	}
	
	
	p.curwait = p.wait;
	e.curwait = e.wait;
	
	aP_depack(EnemySprites[i], decompression_buffer);
	enemyImage.init(decompression_buffer);
	return loop() != Battle_Done::lose;
}


Battle battle;
