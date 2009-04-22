#ifndef __GAME_H__
#define __GAME_H__

#include "entity.h"

#include <vector>
#include <wiisprite.h>


using std::vector;
using namespace wsp;

class Game : public Entity
{
public:
	Game();
	~Game();
	bool update();
	void on_hit();
	void add_entity(Entity *new_ent);
	vector <Entity*> *get_ent_list();
	Image *get_bullet_img();
	Image *get_enemy_img();
	void generate_wave();
private:
	Entity *player;
	// Stores enemies and bullets etc.
	vector<Entity*> ent_list;
	vector<Entity*> ent_list_tmp;
	Image *bullet_img; // No need to have EACH bullet load their own- that'd be crazy talk
	Image *enemy_img; // Fear our 3.. er 4 types of ship!
	u64 next_wave;
	u8 wave_num;
	bool show_hitbox;
};

#endif
