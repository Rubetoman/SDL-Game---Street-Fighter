#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
enum pose
{
	STANDING,
	CROUCHING,
	JUMPING
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
	SDL_Rect crouch_idle;
	Animation idle;
	Animation backward;
	Animation forward;
	Animation crouch;
	Animation stand_up;
	Animation light_punch;
	Animation medium_punch;
	Animation heavy_punch;
	Animation crouch_light_punch;
	Animation crouch_medium_punch;
	Animation crouch_heavy_punch;
	iPoint position;
	pose player1_pose;
};

#endif // __MODULEPLAYER_H__