#include "Common.h"
#include "bgObject.h"

class Brick : public bgObject {
	int brickNumber;
public:
	Brick();
	void initializeBricks(Brick*);
	void setBrickNumber(int);
};