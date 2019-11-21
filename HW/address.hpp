#pragma once

#include <cstdint>

//struct holds 32bit machine word
struct Word {
public:
	uint32_t value;
};

//struct translates word into 8 bit page number, and 8bit offset.
//can return a 15 bit physical address if given a 7 bit frame number
struct Address : public Word {
public:
	//object constructors
	Address(Word word);
	Address(uint32_t word);
	//8 bit offset
	uint8_t offset() ;
	//7bit frame number
	uint8_t frameNum : 7;
	//8 bit page number
	uint8_t pageNum();
	//15 bit physical address (7bit-Lshift8 framenum + 8bit offset)
	uint16_t p_address();
};