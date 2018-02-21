#include "misc.h"

#include "board.h"
#include "player.h"
#include "camera.h"
#include "text.h"
#include "data/defines.h"
#include "battle.h"
#include <Gamebuino-Meta.h>
#include <utility/Misc.h> // pixel to rgb converters

void waitCycles(uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		while(!gb.update());
	}
}

bool waitCyclesButton(uint8_t num) {
	for (uint8_t i = 0; i < num; i++) {
		waitCycles(1);
		if (gb.buttons.pressed(BUTTON_A) || gb.buttons.pressed(BUTTON_B) || gb.buttons.pressed(BUTTON_LEFT) || gb.buttons.pressed(BUTTON_RIGHT)) {
			return true;
		}
	}
	return false;
}

void waitRelease() {
	while(1) {
		waitCycles(1);
		if (gb.buttons.released(BUTTON_A) || gb.buttons.released(BUTTON_B) || gb.buttons.released(BUTTON_LEFT) || gb.buttons.released(BUTTON_RIGHT)) {
			return;
		}
	}
}

void renderAll() {
	board.render();
	player.render();
//	gb.display.setCursor(0, 0);
//	gb.display.setColor(BLACK, WHITE);
//	gb.display.print(gb.getCpuLoad());
}

void bombErase(int8_t x, int8_t y) {
	if (x < 0 || y < 0 || x >= (12*8) || y >= (8*8)) {
		return;
	}
	x /= 8;
	y /= 8;
	uint16_t tile = board.getTile(x, y);
	if (tile < SPRITE_FIRST_BOMB || tile >= SPRITE_AFTER_BOMB) {
		return;
	}
	board.eraseTile(x, y);
	board.runScript(x, y, SCRIPT_BOMB);
}

const uint8_t bomb_frames[] = {
	24, 24,
	0x02, 0x00,
	2,
	0x01,
	0x01,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x10, 0x11, 0x01, 0x99, 0x81, 0x10, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x10, 0x00, 0x11, 0x11, 0x11, 0x11, 0x10, 0x01, 0x11, 0x11,
	0x11, 0x11, 0x01, 0x01, 0x11, 0x81, 0x81, 0x11, 0x11, 0x01, 0x11, 0x11,
	0x11, 0x11, 0x10, 0x01, 0x11, 0x11, 0x11, 0x11, 0x01, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x18, 0x81, 0x11, 0x11, 0x11, 0x11, 0x18, 0x18, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x18, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x19, 0x10, 0x11, 0x11,
	0x11, 0x11, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x91, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x10, 0x11, 0x81, 0x11, 0x11, 0x01, 0x10, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x10, 0x11, 0x11, 0x81, 0x11, 0x11, 0x01, 0x11, 0x11,
	0x11, 0x11, 0x10, 0x01, 0x99, 0x11, 0x11, 0x11, 0x10, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x10, 0x11, 0x91, 0x18, 0x11, 0x10, 0x11, 0x19, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	
	
	0x10, 0x11, 0x11, 0x11, 0x11, 0x10, 0x91, 0x10, 0x11, 0x11, 0x91, 0x01,
	0x11, 0x11, 0x01, 0x18, 0x81, 0x10, 0x18, 0x11, 0x01, 0x99, 0x11, 0x11,
	0x11, 0x81, 0x01, 0x11, 0x11, 0x01, 0x11, 0x81, 0x10, 0x11, 0x18, 0x11,
	0x10, 0x10, 0x11, 0x18, 0x19, 0x01, 0x11, 0x81, 0x11, 0x01, 0x11, 0x11,
	0x11, 0x10, 0x10, 0x11, 0x01, 0x99, 0x81, 0x10, 0x11, 0x11, 0x11, 0x01,
	0x11, 0x11, 0x10, 0x00, 0x11, 0x11, 0x11, 0x11, 0x10, 0x01, 0x11, 0x11,
	0x10, 0x11, 0x01, 0x01, 0x11, 0x81, 0x81, 0x11, 0x11, 0x01, 0x91, 0x91,
	0x11, 0x11, 0x10, 0x01, 0x11, 0x11, 0x11, 0x11, 0x01, 0x11, 0x11, 0x11,
	0x19, 0x11, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x01, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x01,
	0x11, 0x00, 0x18, 0x81, 0x11, 0x11, 0x11, 0x11, 0x18, 0x18, 0x88, 0x11,
	0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x81, 0x11,
	0x18, 0x81, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x18, 0x11, 0x11, 0x10,
	0x11, 0x10, 0x11, 0x19, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x01, 0x11,
	0x00, 0x01, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x19, 0x10, 0x11, 0x01,
	0x11, 0x11, 0x18, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x91, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x10, 0x11, 0x81, 0x11, 0x11, 0x01, 0x10, 0x19, 0x91,
	0x10, 0x00, 0x11, 0x10, 0x11, 0x11, 0x81, 0x11, 0x11, 0x01, 0x01, 0x01,
	0x11, 0x11, 0x10, 0x01, 0x99, 0x11, 0x11, 0x11, 0x10, 0x11, 0x11, 0x10,
	0x91, 0x99, 0x10, 0x11, 0x91, 0x18, 0x11, 0x10, 0x11, 0x19, 0x11, 0x11,
	0x11, 0x11, 0x01, 0x11, 0x10, 0x11, 0x10, 0x11, 0x11, 0x11, 0x01, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x01, 0x11, 0x01, 0x11, 0x19, 0x11, 0x11, 0x91,
	0x01, 0x10, 0x01, 0x11, 0x01, 0x11, 0x00, 0x11, 0x11, 0x91, 0x10, 0x11,
	0x01, 0x11, 0x11, 0x11, 0x10, 0x11, 0x11, 0x10, 0x11, 0x91, 0x11, 0x10,
};

void bomb(int8_t x, int8_t y) {
	Image img(bomb_frames);
	for (uint8_t i = 0; i < 2*2 - 1; i++) {
		waitCycles(1);
		renderAll();
		gb.display.drawImage(x - 3 - 8 - camera.x, y - 5 - 8 - camera.y, img);
	}
	for (int8_t i = -1; i < 2; i++) {
		for (int8_t j = -1; j < 2; j++) {
			bombErase(x + i*6, y + j*6);
		}
	}
	img.setFrame(1);
	for (uint8_t i = 0; i < 2*2; i++) {
		waitCycles(1);
		renderAll();
		gb.display.drawImage(x - 3 - 8 - camera.x, y - 5 - 8 - camera.y, img);
	}
}

void hookshot_draw_updown(int8_t x, int8_t y1, int8_t y2) {
	if (y1 > y2) {
		return hookshot_draw_updown(x, y2, y1);
	}
	gb.display.setColor(BLACK);
	for(; y1 <= y2; y1++) {
		if (y1 % 2) {
			gb.display.drawPixel(x - camera.x, y1 - camera.y);
		} else {
			gb.display.drawPixel(x - 1 - camera.x, y1 - camera.y);
			gb.display.drawPixel(x + 1 - camera.x, y1 - camera.y);
		}
	}
}

void hookshot_draw_leftright(int8_t x1, int8_t x2, int8_t y) {
	if (x1 > x2) {
		return hookshot_draw_leftright(x2, x1, y);
	}
	gb.display.setColor(BLACK);
	for(; x1 <= x2; x1++) {
		if (x1 % 2) {
			gb.display.drawPixel(x1 - camera.x, y - camera.y);
		} else {
			gb.display.drawPixel(x1 - camera.x, y + 1 - camera.y);
			gb.display.drawPixel(x1 - camera.x, y - 1- camera.y);
		}
	}
}

void hookshot_up(int8_t x, int8_t y) {
	if (y < 0) {
		return;
	}
	int8_t _y = y;
	int8_t _x = x;
	x += 4; // for animation
	bool grab = false;
	bool flying = false;
	int8_t y_prev = -1;
	while(1) {
		y--;
		if (y % 2) {
			camera.centerOn(_x + 4, y + 4); // _x as we don't want random jumping
			renderAll();
			hookshot_draw_updown(x, y, _y);
			waitCycles(1);
		}
		if (y <= 0) {
			break;
		}
		if (y_prev == (y / 8)) {
			continue;
		}
		uint8_t t = board.getTile(x / 8, y / 8);
		y_prev = y / 8;
		// check if we can just fly
		if (t < SPRITE_AFTER_HOOKSHOT_FLY) {
			continue;
		}
		// check if we pass over an up-wall and set the flying flag
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_RIGHT_UP && t < SPRITE_AFTER_HOOKSHOT_WALL_LEFT_UP) {
			flying = true;
			continue;
		}
		if (t < SPRITE_AFTER_HOOKSHOT_WALL_DOWN) {
			if (flying) {
				flying = false;
				continue;
			}
			break;
		}
		
		
		
		// check if we grab onto something
		if (t >= SPRITE_FIRST_HOOKSHOT && t < SPRITE_AFTER_HOOKSHOT) {
			grab = true;
		}
		break;
	}
	// revert the last step as we want to appear in front of the object
	// this also fixes a bug where you can hookshot into things
	y++;
	if (grab) {
		for (; _y >= y; _y--) {
			if (_y % 2) {
				player.moveY(_y);
				player.focus();
				renderAll();
				hookshot_draw_updown(x, y, _y);
				waitCycles(1);
			}
		}
		player.moveTo(_x, y);
		player.focus();
		return;
	}
	for(;_y > y; y++) {
		if (y % 2) {
			camera.centerOn(_x + 4, y + 4);
			renderAll();
			hookshot_draw_updown(x, y, _y);
			waitCycles(1);
		}
	}
}

void hookshot_right(int8_t x, int8_t y) {
	if (x >= 11*8) {
		return;
	}
	int8_t _y = y;
	int8_t _x = x;
	x += 7; // for checking
	y += 4; // for animation
	
	bool grab = false;
	bool flying = false;
	int x_prev = -1;
	while(1) {
		x++;
		if (x % 2) {
			camera.centerOn(x + 4, _y + 4); // _y as we don't want random jumping
			renderAll();
			hookshot_draw_leftright(x, _x + 7, y);
			waitCycles(1);
		}
		if (x >= 12*8) {
			break;
		}
		if (x_prev == (x / 8)) {
			continue;
		}
		uint8_t t = board.getTile(x / 8, y / 8);
		x_prev = x / 8;
		// check if we can just fly
		if (t < SPRITE_AFTER_HOOKSHOT_FLY) {
			continue;
		}
		// check if we pass over an up-wall and set the flying flag
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_RIGHT && t < SPRITE_AFTER_HOOKSHOT_WALL_RIGHT) {
			flying = true;
			continue;
		}
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_LEFT_UP && t < SPRITE_AFTER_HOOKSHOT_WALL_LEFT) {
			if (flying) {
				flying = false;
				continue;
			}
			break;
		}
		
		
		
		// check if we grab onto something
		if (t >= SPRITE_FIRST_HOOKSHOT && t < SPRITE_AFTER_HOOKSHOT) {
			grab = true;
		}
		break;
	}
	// revert the last step as we want to appear in front of the object
	// this also fixes a bug where you can hookshot into things
	x--;
	if (grab) {
		for (; _x <= (x - 7); _x++) {
			if (_x % 2) {
				player.moveX(_x);
				player.focus();
				renderAll();
				hookshot_draw_leftright(x, _x + 7, y);
				waitCycles(1);
			}
		}
		player.moveTo(x - 7, _y);
		player.focus();
		return;
	}
	for(;_x + 7 < x; x--) {
		if (x % 2) {
			camera.centerOn(x + 4, _y + 4);
			renderAll();
			hookshot_draw_leftright(x, _x + 7, y);
			waitCycles(1);
		}
	}
	player.focus();
}

void hookshot_down(int8_t x, int8_t y) {
	if (y >= 7*8) {
		return;
	}
	int8_t _y = y;
	int8_t _x = x;
	x += 4; // for animation
	y += 7; // for checking
	bool grab = false;
	bool flying = false;
	int8_t y_prev = -1;
	while(1) {
		y++;
		if (y % 2) {
			camera.centerOn(_x + 4, y + 4); // _x as we don't want random jumping
			renderAll();
			hookshot_draw_updown(x, y, _y + 7);
			waitCycles(1);
		}
		if (y >= 8*8) {
			break;
		}
		if (y_prev == (y / 8)) {
			continue;
		}
		uint8_t t = board.getTile(x / 8, y / 8);
		y_prev = y / 8;
		// check if we can just fly
		if (t < SPRITE_AFTER_HOOKSHOT_FLY) {
			continue;
		}
		// check if we pass over an up-wall and set the flying flag
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_DOWN && t < SPRITE_AFTER_HOOKSHOT_WALL_DOWN) {
			flying = true;
			continue;
		}
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_RIGHT_UP && t < SPRITE_AFTER_HOOKSHOT_WALL_LEFT_UP) {
			if (flying) {
				flying = false;
				continue;
			}
			break;
		}
		
		
		
		// check if we grab onto something
		if (t >= SPRITE_FIRST_HOOKSHOT && t < SPRITE_AFTER_HOOKSHOT) {
			grab = true;
		}
		break;
	}
	// revert the last step as we want to appear in front of the object
	// this also fixes a bug where you can hookshot into things
	y--;
	if (grab) {
		for (; _y <= (y - 7); _y++) {
			if (_y % 2) {
				player.moveY(_y);
				player.focus();
				renderAll();
				hookshot_draw_updown(x, y, _y + 7);
				waitCycles(1);
			}
		}
		player.moveTo(_x, y - 7);
		player.focus();
		return;
	}
	for(;_y + 7 < y; y--) {
		if (y % 2) {
			camera.centerOn(_x + 4, y + 4);
			renderAll();
			hookshot_draw_updown(x, y, _y + 7);
			waitCycles(1);
		}
	}
}

void hookshot_left(int8_t x, int8_t y) {
	if (x < 0) {
		return;
	}
	int8_t _y = y;
	int8_t _x = x;
	y += 4; // for animation
	
	bool grab = false;
	bool flying = false;
	int x_prev = -1;
	while(1) {
		x--;
		if (x % 2) {
			camera.centerOn(x + 4, _y + 4); // _y as we don't want random jumping
			renderAll();
			hookshot_draw_leftright(x, _x, y);
			waitCycles(1);
		}
		if (x <= 0) {
			break;
		}
		if (x_prev == (x / 8)) {
			continue;
		}
		uint8_t t = board.getTile(x / 8, y / 8);
		x_prev = x / 8;
		// check if we can just fly
		if (t < SPRITE_AFTER_HOOKSHOT_FLY) {
			continue;
		}
		// check if we pass over an up-wall and set the flying flag
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_LEFT_UP && t < SPRITE_AFTER_HOOKSHOT_WALL_LEFT) {
			flying = true;
			continue;
		}
		
		if (t >= SPRITE_FIRST_HOOKSHOT_WALL_RIGHT && t < SPRITE_AFTER_HOOKSHOT_WALL_RIGHT) {
			if (flying) {
				flying = false;
				continue;
			}
			break;
		}
		
		
		
		// check if we grab onto something
		if (t >= SPRITE_FIRST_HOOKSHOT && t < SPRITE_AFTER_HOOKSHOT) {
			grab = true;
		}
		break;
	}
	// revert the last step as we want to appear in front of the object
	// this also fixes a bug where you can hookshot into things
	x++;
	if (grab) {
		for (; _x >= x; _x--) {
			if (_x % 2) {
				player.moveX(_x);
				player.focus();
				renderAll();
				hookshot_draw_leftright(x, _x, y);
				waitCycles(1);
			}
		}
		player.moveTo(x, _y);
		player.focus();
		return;
	}
	for(;_x > x; x++) {
		if (x % 2) {
			camera.centerOn(x + 4, _y + 4);
			renderAll();
			hookshot_draw_leftright(x, _x, y);
			waitCycles(1);
		}
	}
	player.focus();
}

void hookshot(int8_t x, int8_t y, Direction dir) {
	switch(dir) {
		case Direction::up:
			hookshot_up(x, y);
			break;
		case Direction::right:
			hookshot_right(x, y);
			break;
		case Direction::down:
			hookshot_down(x, y);
			break;
		case Direction::left:
			hookshot_left(x, y);
			break;
	}
}

void pushblock_up(int8_t x, int8_t y) {
	if (y <= 0) {
		return;
	}
	if (board.getTile(x, y-1) >= SPRITE_AFTER_WALK) {
		return;
	}
	board.eraseTile(x, y);
	for (uint8_t i = 0; i < 9; i++) {
		board.render();
		board.drawTile(x*8, y*8 - i, SPRITE_BLOCK);
		player.render();
		waitCycles(1);
	}
	board.setTile(x, y-1, SPRITE_BLOCK);
}

void pushblock_right(int8_t x, int8_t y) {
	if (x >= 11) {
		return;
	}
	if (board.getTile(x+1, y) >= SPRITE_AFTER_WALK) {
		return;
	}
	board.eraseTile(x, y);
	for (uint8_t i = 0; i < 9; i++) {
		board.render();
		board.drawTile(x*8 + i, y*8, SPRITE_BLOCK);
		player.render();
		waitCycles(1);
	}
	board.setTile(x + 1, y, SPRITE_BLOCK);
}

void pushblock_down(int8_t x, int8_t y) {
	if (y >= 7) {
		return;
	}
	if (board.getTile(x, y+1) >= SPRITE_AFTER_WALK) {
		return;
	}
	board.eraseTile(x, y);
	for (uint8_t i = 0; i < 9; i++) {
		board.render();
		board.drawTile(x*8, y*8 + i, SPRITE_BLOCK);
		player.render();
		waitCycles(1);
	}
	board.setTile(x, y+1, SPRITE_BLOCK);
}

void pushblock_left(int8_t x, int8_t y) {
	if (x <= 0) {
		return;
	}
	if (board.getTile(x-1, y) >= SPRITE_AFTER_WALK) {
		return;
	}
	board.eraseTile(x, y);
	for (uint8_t i = 0; i < 9; i++) {
		board.render();
		board.drawTile(x*8 - i, y*8, SPRITE_BLOCK);
		player.render();
		waitCycles(1);
	}
	board.setTile(x-1, y, SPRITE_BLOCK);
}

void pushblock(int8_t x, int8_t y, Direction dir) {
	switch(dir) {
		case Direction::up:
			pushblock_up(x, y);
			break;
		case Direction::right:
			pushblock_right(x, y);
			break;
		case Direction::down:
			pushblock_down(x, y);
			break;
		case Direction::left:
			pushblock_left(x, y);
			break;
	}
	board.runScript(x, y, SCRIPT_PUSHBLOCK);
}



bool shop(uint16_t ask, uint16_t price, bool bottle) {
	if (!text.boxPlayer(ask)) {
		return false;
	}
	
	if (bottle && !player.isCurItemBottle()) {
		text.boxPlayer(STRING_NEED_BOTTLE);
		return false;
	}
	
	if (!player.payGold(price)) {
		text.boxPlayer(STRING_NOT_ENOUGH_GOLD);
		return false;
	}
	
	text.boxPlayer(STRING_SHOP_THANKS);
	return true;
}

//typedef void (__stdcall *RenderFunction)();

void fade_to_white(void (*r)(void)) {
	const uint8_t steps = 20;
	Color* origPalette = gb.display.colorIndex;
	Color palette[16];
	gb.display.colorIndex = palette;
	
	for (uint8_t i = 0; i <= steps; i++) {
		for (uint8_t j = 0; j < 16; j++) {
			uint16_t c = (uint16_t)origPalette[j];
			Gamebuino_Meta::RGB888 rgb = Gamebuino_Meta::rgb565Torgb888(c);
			rgb.r += (0xFF - rgb.r)*i / steps;
			rgb.g += (0xFF - rgb.g)*i / steps;
			rgb.b += (0xFF - rgb.b)*i / steps;
			c = Gamebuino_Meta::rgb888Torgb565(rgb);
			palette[j] = (Color)c;
		}
		(*r)();
		waitCycles(1);
	}
	gb.display.colorIndex = origPalette;
}

void fade_to_white() {
	fade_to_white(&renderAll);
}

void fade_from_white(void (*r)(void)) {
	const uint8_t steps = 20;
	Color* origPalette = gb.display.colorIndex;
	Color palette[16];
	gb.display.colorIndex = palette;
	
	for (uint8_t i = 0; i <= steps; i++) {
		for (uint8_t j = 0; j < 16; j++) {
			uint16_t c = (uint16_t)origPalette[j];
			Gamebuino_Meta::RGB888 rgb = Gamebuino_Meta::rgb565Torgb888(c);
			rgb.r += (0xFF - rgb.r)*(steps - i) / steps;
			rgb.g += (0xFF - rgb.g)*(steps - i) / steps;
			rgb.b += (0xFF - rgb.b)*(steps - i) / steps;
			c = Gamebuino_Meta::rgb888Torgb565(rgb);
			palette[j] = (Color)c;
		}
		(*r)();
		waitCycles(1);
	}
	gb.display.colorIndex = origPalette;
}

void fade_from_white() {
	fade_from_white(&renderAll);
}

void renderBattleBar() {
	battle.render();
	battle.renderBar();
	battle.renderHpMp();
}

void renderBattle() {
	battle.render();
}

void battleInstructions() {
	if (text.boxPlayer(STRING_PERSON_DOGGLEN_BATTLE_INSTRUCTIONS_ASK)) {
		return;
	}
	fade_to_white();
	battle.load(ENEMY_MOUSE);
	battle.p.wait = battle.p.curwait = 24;
	fade_from_white(&renderBattleBar);
	renderBattleBar();
	
	waitCycles(20);
	text.box(STRING_PERSON_DOGGLEN_BATTLE_INSTRUCTIONS_BAR, false);
	battle.load(ENEMY_MOUSE);
	battle.p.wait = battle.p.curwait = 24;
	renderBattleBar();
	while(battle.p.curwait--) {
		battle.renderBar();
		waitCycles(1);
	}
	
	battle.render();
	battle.renderMenu();
	battle.renderHpMp();
	waitCycles(20);
	text.box(STRING_PERSON_DOGGLEN_BATTLE_INSTRUCTIONS_ATTACK_MENU, false);
	battle.load(ENEMY_MOUSE);
	battle.render();
	battle.renderMenu();
	battle.renderHpMp();
	waitCycles(20);
	battle.render();
	battle.playerAttackAnimation();
	battle.drawText(52, 16, "42");
	
	waitCycles(45);
	fade_to_white(&renderBattle);
	fade_from_white();
	text.boxPlayer(STRING_PERSON_DOGGLEN_BATTLE_INSTRUCTIONS_DONE);
}
