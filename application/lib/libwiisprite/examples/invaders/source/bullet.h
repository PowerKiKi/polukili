#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"
#include "game.h"

class Bullet : public Entity
{
public:
	Bullet(Game *papa,f32 x, f32 y);
	~Bullet();
	bool update();
	void on_hit();
private:
	u64 next_update;
	Game *parent;
};

#endif
