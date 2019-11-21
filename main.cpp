
#include "HW/MMU.hpp"
#include "HW/Ram.hpp"
#include "HW/BackingStore.hpp"
#include "HW/Address.hpp"
#include "OS/ProcessControlBlock.hpp"
#include "OS/MemoryManager.hpp"
#include "OS/PageReplacement.hpp"
#include "OS/FirstInFirstOut.hpp"
#include "OS/LeastRecentlyUsed.hpp"
#include "Util/global.hpp"
#include <iostream>
#include <iomanip>

using namespace std;
PageReplacement::algorithm PageReplacement::alg;

int main(){

	//set page replacement algorithm by setting ALG_CHOICE at compile time in Util/global.hpp
	if (ALG_CHOICE == 0) {
		PageReplacement::alg = PageReplacement::algorithm::FIFO;
		cout << "Algorithm: FIFO\n";
	}else {
		PageReplacement::alg = PageReplacement::algorithm::LRU;
		cout << "Algorithm: LRU\n";
	}

	//pcb object contains pagetable
	ProcessControlBlock process;

	//32bit word taken from input stream
	Word word;

	//read from input stream
	while (cin >> word.value)
	{
		//instruction completion flag
		bool instructionComplete = false;
		while (!instructionComplete) {
			
			try {
				//send work to Memory Management Unit
				MMU::instance()->read(word, &process);	//may throw page fault
				instructionComplete = true;				//set flag if no fault
			}
			catch ( MMU::PageFault  fault) {
				//call Memory Manager in OS to handle fault
				MemoryManager::instance()->pageIn(fault.pageNum, &process);
				//restart insruction
			}
		}

	}

	//cout << "Page Faults " << dec << MMU::page_faults() << endl;
	//cout << "TLB hits " << dec << (MMU::tlb_accesses() - MMU::tlb_faults()) << endl;
	//cout << "TLB Accesses " << dec << MMU::tlb_accesses() << endl;
	//cout << "TLB Faults " << dec << MMU::tlb_faults() << endl;

	cout << "Page Fault Rate:\t" << dec << fixed << setprecision(4)
		<<(static_cast<float>(MMU::page_faults())/ static_cast<float>(MMU::page_accesses())) << "%\n";
	cout << "TLB Hit Rate:\t\t" << dec << fixed << setprecision(4)
		<< (static_cast<float>(MMU::tlb_accesses() - MMU::tlb_faults()) /static_cast<float>(MMU::tlb_accesses())) << "%\n";

}
