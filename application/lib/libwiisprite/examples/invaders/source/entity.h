#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <wiisprite.h>

using namespace wsp;

class Engine;

class Entity
{
public:
	Entity();
	~Entity();
	virtual bool update() = 0;
	virtual void on_hit() = 0;
	
	void set_engine(Engine *eng);
	Engine *get_engine();
	void set_alive(bool a);
	bool get_alive();

	void set_sprite(Sprite *csprite);
	Sprite *get_sprite();
private:
	bool alive;
	Sprite *csprite;
};

#endif
