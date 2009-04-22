#ifndef __SHIP_H__
#define __SHIP_H__

#include "entity.h"
#include "game.h"

class Ship : public Entity
{
public:
	Ship();
	Ship(Game *papa);
	~Ship();
	bool update();
	void on_hit();
private:
	u64 next_update;
	Game *parent;
	double sinew;
	f32 ypos;
};

#endif
