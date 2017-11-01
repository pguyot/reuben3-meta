#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <Arduino.h>

class Script {
	private:
		int8_t vars[10]; // SCRIPT_NUM_VARS
		bool condition();
		uint8_t* getVar();
		void getNum(uint8_t* var);
		void jump();
		uint8_t* script;
		uint8_t* script_entry;
	public:
		bool run(uint8_t* _script);
};

extern Script script;

#endif // _SCRIPT_H_
