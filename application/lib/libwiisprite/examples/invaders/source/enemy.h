#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include "game.h"

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(Game *papa);
	~Enemy();
	bool update();
	void on_hit();
private:
	Game *parent;
	double xsp;
	f32 ly;
	bool dying;
};

#endif
