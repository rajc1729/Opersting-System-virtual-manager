#include "MMU.hpp"


//forward declaration of static members
MMU* MMU::mmu;
PageReplacement * MMU::pr;
uint16_t MMU::page_access_count;
uint16_t MMU::page_in_faults;
uint16_t MMU::tlb_access_count;
uint16_t MMU::tlb_access_faults;
MMU::TLBentry MMU::TLB[];

//class constructor
MMU::MMU()
{
	//init TLB
	clearTLB();

	//reset statistic counters
	page_access_count = 0;
	page_in_faults = 0;
	tlb_access_count = 0;
	tlb_access_faults = 0;

	//initilized selected page replacement algorithm
	if (PageReplacement::alg == PageReplacement::algorithm::LRU) {
		pr = new LeastRecentlyUsed(TLB_SIZE);
	}else {
		pr = new FirstInFirstOut(TLB_SIZE);
	}
}

// invalidates all tlb entries
void MMU::clearTLB()
{
	for (auto i = 0; i < TLB_SIZE; i++) {
		TLB[i].tableEntry.valid = false;
	}
}


//creates and/or returns singleton instance
MMU* MMU::instance() {
	if (mmu == nullptr) {
		mmu = new MMU();
	}
	return mmu;
}


//receive 32bit machine word and process control block
//throws page fault if page is not valid in ram
//outputs in hex: Logical Address, Physical Address, and byte value at address
void MMU::read(Word word, ProcessControlBlock * pcb) noexcept(false) {

	//set address object
	Address address(word);

	bool tlbHit = false;
	//Search TLB
	tlb_access_count++;
	for (auto i = 0; i < TLB_SIZE; i++) {
		if (address.pageNum() == TLB[i].pageNum && TLB[i].tableEntry.valid) {
			address.frameNum = TLB[i].tableEntry.frameNum;
			tlbHit = true;

			//update TLB entry usage if LRU
			if (PageReplacement::alg == PageReplacement::algorithm::LRU) {
				static_cast<LeastRecentlyUsed*>(pr)->updateUsage(i);
			}
			break;
		}
	}

	//if not foind in TLB
	if (!tlbHit) {
		tlb_access_faults++;
		//check if page table entry is valid
		page_access_count++;
		if (pcb->pageTable[address.pageNum()].valid) {
			//get frame number if valid
			address.frameNum = pcb->pageTable[address.pageNum()].frameNum;

			//debug
			//cout << "no fault" << endl;

			//add to tlb
			uint16_t TLBVictim = pr->findVictim();

			TLB[TLBVictim].pageNum = address.pageNum();
			TLB[TLBVictim].tableEntry.frameNum = address.frameNum;
			TLB[TLBVictim].tableEntry.valid = true;
		}
		else {
			//throw an error
			page_in_faults++;

			//debug
			//cout << "fault" << endl;
			
			throw PageFault (address.pageNum());
	
		}
	}
			
	//debug
	//cout << "Page Number " << dec << static_cast<int>(address.pageNum()) << endl;
	//cout << "Frame Number " << dec << static_cast<int>(address.frameNum) << endl;
	//cout << "Offset " << dec << static_cast<int>(address.offset()) << endl;

	//output Logical address
	cout << setfill('0') << setw(4) << uppercase << hex << address.value;
	//output Physical Address
	cout << " (" << setfill('0') << setw(4) << uppercase << hex << address.p_address() << "): ";
	//output byte value at physical address
	Ram::read(address.frameNum, address.offset());
}

//returns number of page accesses
uint16_t MMU::page_accesses()
{
	return page_access_count;
}

//returns number of page faults
uint16_t MMU::page_faults()
{
	return page_in_faults;
}

//returns number of TLB accesses
uint16_t MMU::tlb_accesses()
{
	return tlb_access_count;
}

//returns number of TLB faults
uint16_t MMU::tlb_faults()
{
	return tlb_access_faults;
}