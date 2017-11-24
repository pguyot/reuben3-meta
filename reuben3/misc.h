#ifndef _MISC_H_
#define _MISC_H_
#include <Arduino.h>

#include "player.h" // for Direction datatype

void waitCycles(uint8_t num);
bool waitCyclesButton(uint8_t num);
void waitRelease();
void renderAll();
void statsMenu();
void bomb(int8_t x, int8_t y);
void hookshot(int8_t x, int8_t y, Direction dir);

#endif // _MISC_H_
