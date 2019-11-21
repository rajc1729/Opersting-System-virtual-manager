#include "FirstInFirstOut.hpp"


//@returns uint16_t : index of next FIFO victim
uint16_t FirstInFirstOut::findVictim()
{
	uint16_t victim = front;				//select victim
	front = (front +1) % reach;	        //increment front
	return victim;							//return victim
}


//class constructor
//@param int size: reach of the algorithm
FirstInFirstOut::FirstInFirstOut(int size)
{
	reach = size;
	front = 0;
}
