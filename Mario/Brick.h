#include "Common.h"
#include "bgObject.h"

class Brick : public bgObject {
	int brickNumber;
public:
	//dummmy constructor
	Brick();
	void setBrickNumber(int);
	////parameterized constructor
	//Brick(int);
};