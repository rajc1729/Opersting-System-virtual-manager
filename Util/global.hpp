#pragma once
constexpr auto PAGE_ENTRIES = 256;
constexpr auto PAGE_SIZE = 256;
constexpr auto TLB_SIZE = 16;
constexpr auto FRAME_SIZE = 256;
constexpr auto FRAME_ENTRIES = 128;

/******************************************************
*Page Replacement Algorithm choice during compile time
* 0 = FIFO
* 1 = LRU
******************************************************/
constexpr auto ALG_CHOICE = 0;
//constexpr auto ALG_CHOICE = 1;