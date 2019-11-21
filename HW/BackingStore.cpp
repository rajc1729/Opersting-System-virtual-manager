#include "BackingStore.hpp"
BackingStore * BackingStore::store;
ifstream BackingStore::bin_file;

//Deconstructor
BackingStore::~BackingStore()
{
	if (store) {
		//clear memory
		delete store;
	}
	//close filestream
	bin_file.close();
}

BackingStore * BackingStore::instance()
{
	//check if store instance, if not create one
	if (store == nullptr) {
		store = new BackingStore();
	}
	//return singleton instance
	return store;
}

//@param uint8_t page: 8 bit page number to read
//@param char* arr: array[PAGE_SIZE] to read page data into
void BackingStore::read(uint8_t page, char* arr)
{
	//seek to the start of the page
	bin_file.seekg(page * PAGE_SIZE);
	//read page into array param
	bin_file.read(arr, PAGE_SIZE);
}


//check the state of the filestream
bool BackingStore::isGood()
{
	return bin_file.good();
}

//class constructor
BackingStore::BackingStore()
{
	//set exception mask
	bin_file.exceptions(ifstream::badbit | ifstream::failbit);

	//read file
	try {
		bin_file.open("BACKING_STORE.bin",ifstream::binary);
	}catch(ifstream::failure err) {
		cerr << "Failure to open  file" << endl << err.what() <<endl;
	}
}


