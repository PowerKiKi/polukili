#include "entity.h"
#include "engine.h"

#include <wiisprite.h>

using namespace wsp;

Entity::Entity() : alive(true)
{
}

Entity::~Entity()
{
}

void Entity::set_alive(bool a)
{
	alive = a;
}

bool Entity::get_alive()
{
	return alive;
}

void Entity::set_sprite(Sprite *nsprite)
{
	csprite = nsprite;
}

Sprite *Entity::get_sprite()
{
	return csprite;
}
