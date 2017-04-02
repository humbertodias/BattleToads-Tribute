#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
enum anim_status
{
	IDLE_RIGHT,
	IDLE_LEFT,
	WALKING_RIGHT,
	WALKING_LEFT,
	JUMPING,
	ATTACKING
};
class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation walk;
	iPoint position;
	float coordZ;
	anim_status AnimStatus;
};

#endif // __MODULEPLAYER_H__