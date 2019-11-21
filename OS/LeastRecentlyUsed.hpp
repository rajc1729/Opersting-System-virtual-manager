#pragma once

#include <chrono>
#include <vector>
#include  "PageReplacement.hpp"

using namespace std;
//type definition for time value
typedef chrono::high_resolution_clock::time_point time_point;

//Last Recently used algorithm selects victim based on
//usage and time values.
struct LeastRecentlyUsed: PageReplacement{
public:
	uint16_t findVictim();
	LeastRecentlyUsed(uint16_t size);
	void updateUsage(uint16_t index);
private:
	vector<time_point> LRU_List;
};