#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ceiling;
	SDL_Rect bucket;
	SDL_Rect pool;
	Animation water;
	Animation poster_left;
	Animation poster_right;
	/*Animation flag;
	Animation boat_girl;
	Animation boat_guys;
	Animation boat_boy;
	Animation boat_man;*/

private:
	//int offset = 1;					// Offset for the boat y position
	//bool increasing_offset = true;	// Is the offset being increased or decreased?
	//int ticks_since_move = 0;		// Number of ticks since the offset was applied
};

#endif // __MODULESCENEHONDA_H__
