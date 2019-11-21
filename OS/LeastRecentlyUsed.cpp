#include "LeastRecentlyUsed.hpp"


//@return uint16_t: the index of the next victim in the LRU algorithm
uint16_t LeastRecentlyUsed::findVictim()
{
	//variable to track oldest time
	time_point victim_time = chrono::high_resolution_clock::now();
	//variable to track index of oldest time
	uint16_t victim_index;

	//linear search for oldest index in LRU_list
	for (auto i = 0; i < reach; i++) {
		if (LRU_List[i] < victim_time) {
			victim_time = LRU_List[i];
			victim_index = i;
		}
	}
	//return index
	return victim_index;
}

//constructor
//@param uint16_t size: the reach of the algorithm
LeastRecentlyUsed::LeastRecentlyUsed(uint16_t size)
{
	//set size of LRU_list
	reach = size;
	LRU_List.resize(static_cast<int>(reach));

	//init time values
	for (time_point t : LRU_List) {
		t = chrono::high_resolution_clock::now();
	}
}

//@param uint16_t index: Index of a recenty used entry in the algorithm
//resets time in given entry
void LeastRecentlyUsed::updateUsage(uint16_t index)
{
	//update time in selected index
	LRU_List[index] = chrono::high_resolution_clock::now();
}
