#ifndef __MENU_H__
#define __MENU_H__

#include "entity.h"

#include <wiisprite.h>

using namespace wsp;

class Menu : public Entity
{
public:
	Menu();
	~Menu();
	bool update();
	void on_hit();
private:
	u8 menu_sel;
	Sprite *menu_bg, *cursor;
	u64 last_time;
};

#endif
