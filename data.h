#pragma once
#include"reuse.h"
#include<vector>

class Luxijun {
public:
	Luxijun() {
		delay_2ms = { 0, 2000000 };
		delay_200ms = { 0, 200000000 };
		timeout = { 0, 200000000 };
	}
	static Luxijun*instance;
	static Luxijun*getInstance() {
		if (!instance) {
			instance = new Luxijun;
		}
		return instance;
	}
	reuseSub BtoA, CtoA, DtoA, EtoA;
	os_time delay_2ms;
	os_time delay_200ms;
	Duration_t timeout;
	vector<Code> msgListB, msgListC, msgListD, msgListE;
};

