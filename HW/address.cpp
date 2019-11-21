#include "Address.hpp"

//constructor
Address::Address(uint32_t word)
{
	value = word;
}
//copy constructor
Address::Address(Word word)
{
	value = word.value;
}


//return 8bit offset
uint8_t Address::offset()
{
	//mask last 8 bits
	return (value & 0b11111111);
}

//return 8 bit page number
uint8_t Address::pageNum()
{
	//mask bits 9 thru 16, rightshift 8
	return ((value & 0b1111111100000000) >> 8);
}

//return 15 bit physical address
uint16_t Address::p_address()
{
	//leftshift framenum by 8, add last 8 bits of word 
	return ((frameNum << 8) + (value & 0b11111111));
}
