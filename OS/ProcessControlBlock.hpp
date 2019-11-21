#pragma once
#include <cstdint>
#include "../Util/global.hpp"

using namespace std;

//indicates the fame associated frame number and valid bit.
struct PageTableEntry{
    public:
    uint16_t frameNum;
    bool valid = false; 
};


//holds the page table; an array of PageTableEntries
struct ProcessControlBlock{
    PageTableEntry pageTable[PAGE_ENTRIES];
};