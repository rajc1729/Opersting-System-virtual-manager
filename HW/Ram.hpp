#pragma once

#include <iostream>
#include <iomanip>
#include <array>
#include "../Util/global.hpp"

using namespace std;
//type definitaion for Frame
//array_of_unsigned_char[FRAME_SIZE]
typedef unsigned char Frame[FRAME_SIZE];

//frame static indicator
struct Status {
	bool dirty;
	bool accessed;
};

//represents main memory
//memory is an array of frames
//frames are an array of bytes
class Ram{
public:
	static Ram * instance();
	static void read(uint8_t frameNum, uint8_t offset);
	static void write(uint8_t frameNum, Frame frameData);
	static Status status[FRAME_ENTRIES];
	~Ram();
private:
	Ram();
	static Frame memory[FRAME_ENTRIES];
	static Ram * ram;
};

