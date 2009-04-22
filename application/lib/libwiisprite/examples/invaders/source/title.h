#ifndef __TITLE_H__
#define __TITLE_H__

#include "entity.h"

class Title : public Entity
{
public:
	Title();
	~Title();
	bool update();
	void on_hit();
private:
	Entity *child;
};

#endif
