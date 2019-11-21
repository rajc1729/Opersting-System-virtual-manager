#include "Ram.hpp"

Frame Ram::memory[];
Ram * Ram::ram;
Status Ram::status[];

//returns singleton instance
Ram * Ram::instance()
{
	if (ram == nullptr) {
		ram = new Ram();
	}
	return ram;
}

//@param uint8_t frameNum: index of desired frame
//@param uint8_t offset: index of desired byte value in frame
//outputs to console the value in given frame index at given offset
void Ram::read(uint8_t frameNum, uint8_t offset)
{
	//update accessed bit
	status[frameNum].accessed = true;

	//output in hex and dec the byte value
	cout << setfill('0') << setw(2) << uppercase << hex << static_cast<int>(memory[frameNum][offset]);
	cout << "(" << dec << static_cast<int>(static_cast<char>(memory[frameNum][offset])) << ")\n";


	////debug output entire frame
	//for (int i = 0; i < PAGE_SIZE; i++) {
	//	if (i % 0x10 == 0)cout << endl;
	//	else if (i % 0x4 == 0) cout << "  ";
	//	cout << setfill('0') << setw(2) << static_cast<int>(memory[frameNum][i]) << " ";

	//}
	//cout << endl;
}

//@param uint8_t frameNum: index of desired frame
//@param Frame frameData: array of bytes to store intro main memory
//page in frame data
void Ram::write(uint8_t frameNum, Frame frameData)
{
	
	//copy array
	for (int i = 0; i < FRAME_SIZE; i++) {
		memory[frameNum][i] = frameData[i];
	}
	//reset flags
	status[frameNum].dirty = false;
	status[frameNum].accessed = false;
}



//class constructor
Ram::Ram()
{	//initialize status bits
	for (int i = 0; i < FRAME_ENTRIES; i++) {
		status[i].accessed = false;
		status[i].dirty = false;
	}
}

//class deconstructor
Ram::~Ram()
{
	if (ram) {
		delete ram;
	}
}


