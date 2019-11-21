#pragma once
#include "ProcessControlBlock.hpp"
#include <cstdint>

//interface class for page replacement algorithms.
//selects victim frams based on FIFO or LRU patterns
class PageReplacement {
public:
	enum algorithm{FIFO = 0, LRU = 1};
	virtual uint16_t findVictim() = 0;
	static algorithm alg;

protected:
	PageReplacement();
	uint16_t reach;
private:
	
};