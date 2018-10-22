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
const float Player_Anim_Speed = 1.4f;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void PlayFullAnimation();
	void StandingInput();
	void CrouchingInput();
	void JumpingingInput();
public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect crouch_idle;
	SDL_Rect player;
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
	Animation jump;
	Animation jump_light_punch;
	Animation jump_medium_punch;
	Animation jump_heavy_punch;
	iPoint position;
	pose player_state;
	Animation* playing_animation;
	pose next_state;

private:
	bool up = false;
	unsigned jump_attack = 0;
};

#endif // __MODULEPLAYER_H__