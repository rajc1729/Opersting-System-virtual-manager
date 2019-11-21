#pragma once
#include "Address.hpp"
#include "../OS/ProcessControlBlock.hpp"
#include "../Util/global.hpp"
#include "../OS/ProcessControlBlock.hpp"
#include "../OS/MemoryManager.hpp"
#include "../OS/PageReplacement.hpp"
#include "../OS/LeastRecentlyUsed.hpp"
#include "../OS/FirstInFirstOut.hpp"
#include <exception>

using namespace std;

class MMU{
public:
	//Translationg lookaside buffer intry
	//holds page number, frame number and valid bit
	struct TLBentry {
		uint16_t pageNum;
		PageTableEntry tableEntry;
	};

	//Page fault exception
	//Holds the index of the page that caused the fault
	struct PageFault :public exception {
		uint16_t pageNum;
		PageFault(uint16_t n) :pageNum(n) {};
	};


	static void clearTLB();	//tlb initializer
	static MMU* instance(); //instance accessor method
	static void read(Word word, ProcessControlBlock * pcb)noexcept(false);
	static uint16_t page_accesses();
	static uint16_t page_faults();
	static uint16_t tlb_accesses();
	static uint16_t tlb_faults();

private:
	MMU();					//private constructor
	static MMU * mmu;		//singleton instance

	static uint16_t page_access_count;
	static uint16_t page_in_faults;
	static uint16_t tlb_access_count;
	static uint16_t tlb_access_faults;
	static TLBentry TLB[TLB_SIZE];
	static PageReplacement * pr;
};


