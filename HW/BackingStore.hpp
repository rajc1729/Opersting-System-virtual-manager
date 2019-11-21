#pragma once
#include <iostream>
#include <fstream>
#include "../Util/global.hpp"

using namespace std;

//backing store represts page data on secondary storage
class BackingStore {
public:
	~BackingStore();
	//return singleton instance
	static BackingStore * instance();
	//
	static void read(uint8_t page, char* arr );
	static bool isGood();

private:
	BackingStore();
	static BackingStore * store;
	static ifstream bin_file;
	
};