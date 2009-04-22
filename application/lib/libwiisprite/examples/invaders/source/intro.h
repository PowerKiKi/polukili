#ifndef __INTRO_H__
#define __INTRO_H__

#include "entity.h"
#include <wiisprite.h>

using namespace wsp;

class Intro : public Entity
{
public:
	Intro();
	~Intro();
	bool update();
	void on_hit();
private:
	u64 start_time;
	Quad fade;
	u8 fade_alpha;
};

#endif
