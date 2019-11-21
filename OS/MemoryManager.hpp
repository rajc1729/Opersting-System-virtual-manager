#pragma once
#include <cstdint>
#include "../Util/global.hpp"
#include "../HW/Ram.hpp"
#include "../HW/BackingStore.hpp"
#include "ProcessControlBlock.hpp"
#include "PageReplacement.hpp"
#include "FirstInFirstOut.hpp"
#include "LeastRecentlyUsed.hpp"


using namespace std;

//Memroy manager handles page faults
//loads the contests of the backing store into main memory
class MemoryManager {
public:
	static MemoryManager * instance();
	static void pageIn(uint8_t pageNum, ProcessControlBlock *pcb);

		
private:
	MemoryManager();
	static MemoryManager * mm;
	static bool freeFrameList[FRAME_ENTRIES];
	static PageReplacement * pr;
};