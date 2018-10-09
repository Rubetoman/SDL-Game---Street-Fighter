#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect boat;
	Animation flag;
	Animation boat_girl;
	Animation boat_guys;
	Animation boat_boy;
	Animation boat_man;

private:
	int offset = 1;					// Offset for the boat y position
	bool increasing_offset = true;	// Is the offset being increased or decreased?
	int ticks_since_move = 0;		// Number of ticks since the offset was applied
};

#endif // __MODULESCENEKEN_H__