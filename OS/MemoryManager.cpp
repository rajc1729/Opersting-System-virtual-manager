#include "MemoryManager.hpp"

bool MemoryManager::freeFrameList[];
MemoryManager * MemoryManager::mm;
PageReplacement * MemoryManager::pr;

//@return MemoryManager *: pointer to singleton instance
MemoryManager * MemoryManager::instance()
{
	if (!mm) {
		mm = new MemoryManager();
	}
	return mm;
}

//loads data from backing store into ram and updates page table
//@param uint8_t pageNum: page number which generated page fault
//@param  ProcessControlBlock *pcb, pointer to procecess control block containig page table
void MemoryManager::pageIn(uint8_t pageNum, ProcessControlBlock *pcb)
{
	uint16_t frameNum;
	bool freeFrameFound = false;
	
	//search for free frame
	for (auto i = 0; i < FRAME_ENTRIES; i++) {
		if (freeFrameList[i]) {			//if free frame found
			freeFrameList[i] = false;	//mark free frame list
			freeFrameFound = true;		//set found flag
			frameNum = i;				//get frame number
			break;
		}
	}

	//use algorithm if no free frame found
	if (!freeFrameFound) {
		frameNum = pr->findVictim();
	}

	//cout << "\nNew Victim: " << static_cast<int>(frameNum) << "\n\n";
	
	//check dirty bit
	if (Ram::instance()->status[frameNum].dirty) {
		//write frame to backing store...
	}

	//check if page has been invalidated
	for (auto i = 0; i < PAGE_ENTRIES; i++) {
		if (pcb->pageTable[i].frameNum == frameNum && pcb->pageTable[i].valid) {
			pcb->pageTable[i].valid = false;
			break;
		}
	}
	
	//create new frame
	Frame  newFrame;

	//read from backing store
	BackingStore::instance()->read(pageNum, reinterpret_cast<char *>(&newFrame));

	////Debugging, output frame contents
	//for (int i = 0; i < PAGE_SIZE; i++) {
	//	if (i % 0x10 == 0 )cout << endl;
	//	else if (i % 0x4 == 0) cout << "  ";
	//	cout << setfill('0') << setw(4) << static_cast<int>(newFrame[i])  << " ";
	//		
	//}
	//cout << endl;

	//write frame to RAM
	Ram::instance()->write(frameNum, newFrame);

	//set timer for LRU on read
	if (PageReplacement::alg == PageReplacement::algorithm::LRU) {
		static_cast<LeastRecentlyUsed*>(pr)->updateUsage(frameNum);
	}


	//update page table
	pcb->pageTable[pageNum].frameNum = frameNum;
	pcb->pageTable[pageNum].valid = true;
	
}


//constructor
MemoryManager::MemoryManager()
{
	//initialize page replacement algorithm
	if (PageReplacement::alg == PageReplacement::algorithm::LRU) {
		pr = new LeastRecentlyUsed(FRAME_ENTRIES);
	}
	else {
		pr = new FirstInFirstOut(FRAME_ENTRIES);
	}

	//Init freeframelist to free
	for (auto i = 0; i <  FRAME_ENTRIES; i++) {
			freeFrameList[i] = true;
		}
}
