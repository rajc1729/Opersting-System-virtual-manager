#pragma once

#include "PageReplacement.hpp"


struct FirstInFirstOut :PageReplacement {
public:
	uint16_t findVictim();
	FirstInFirstOut(int size);
private:
	//index of next victim
	uint16_t front;
};