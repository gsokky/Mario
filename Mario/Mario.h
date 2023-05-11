#include "Common.h"
#include "Object.h"

class Mario : public Object {
public:
	Mario();
	void move(WalkDirection);
	void standStill(void);
	void fall(void);
	void jump(bool);
};