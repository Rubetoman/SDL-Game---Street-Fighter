#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png
	boat.x = 9;
	boat.y = 25;
	boat.w = 512;
	boat.h = 180;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// bitt
	bitt.x = 760;
	bitt.y = 176;
	bitt.w = 31;
	bitt.h = 24;

	// bitt_small
	bitt_small.x = 800;
	bitt_small.y = 184;
	bitt_small.w = 22;
	bitt_small.h = 16;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png
	boat_girl.frames.push_back({ 625, 80, 30, 56 });
	boat_girl.frames.push_back({ 625, 16, 30, 56 });
	boat_girl.frames.push_back({ 625, 80, 30, 56 });
	boat_girl.frames.push_back({ 625, 144, 30, 56 });
	boat_girl.speed = 0.04f;

	// two boat_guys animation
	boat_guys.frames.push_back({ 552, 72, 65, 66 });
	boat_guys.frames.push_back({ 552, 8, 65, 66 });
	boat_guys.frames.push_back({ 552, 72, 65, 66 });
	boat_guys.frames.push_back({ 552, 136, 65, 66 });
	boat_guys.speed = 0.03f;

	// boat_boy animation
	boat_boy.frames.push_back({ 664, 16, 30, 56 });
	boat_boy.frames.push_back({ 664, 80, 30, 56 });
	boat_boy.frames.push_back({ 664, 16, 30, 56 });
	boat_boy.frames.push_back({ 664, 80, 30, 56 });
	boat_boy.frames.push_back({ 664, 16, 30, 56 });
	boat_boy.frames.push_back({ 664, 16, 30, 56 });
	boat_boy.speed = 0.05f;

	// boat_man animation
	boat_man.frames.push_back({ 704, 80, 48, 56 });
	boat_man.frames.push_back({ 704, 16, 48, 56 });
	boat_man.frames.push_back({ 704, 16, 48, 56 });
	boat_man.frames.push_back({ 704, 16, 48, 56 });
	boat_man.frames.push_back({ 704, 80, 48, 56 });
	boat_man.frames.push_back({ 704, 144, 48, 56 });
	boat_man.speed = 0.04f;

	// boat_upper_guy1 animation (upper part of the boat with brown jacket)
	boat_upper_guy1.frames.push_back({ 760, 16, 40, 40 });
	boat_upper_guy1.frames.push_back({ 760, 64, 40, 40 });
	boat_upper_guy1.frames.push_back({ 760, 112, 40, 40 });
	boat_upper_guy1.speed = 0.04f;
	
	// boat_upper_guy1 animation (upper part of the boat with purple cloths)
	boat_upper_guy2.frames.push_back({ 808, 24, 44, 34 });
	boat_upper_guy2.frames.push_back({ 808, 72, 44, 34 });
	boat_upper_guy2.frames.push_back({ 808, 120, 44, 34 });
	boat_upper_guy2.speed = 0.03f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Enable();
	// TODO 0: trigger background music
	App->audio->PlayMusic("ken.ogg", 2.0f);
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// TODO 5: make sure the ship goes up and down
	ticks_since_move++;

	if (ticks_since_move > 50)
	{
		ticks_since_move = 0;
		if (increasing_offset)
		{
			++offset;
		}
		else
		{
			--offset;
		}
		if (offset > 3)
		{
			increasing_offset = false;
			ticks_since_move = -100;
		}
		else if (offset < 1)
		{
			increasing_offset = true;
			ticks_since_move = -100;
		}
	}


	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste
	App->renderer->Blit(graphics, 0, -5, &background, 1.8f); // sea and sky
	App->renderer->Blit(graphics, 560, 3, &(flag.GetCurrentFrame()), 1.8f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed.
	App->renderer->Blit(graphics, 0, -5 + offset, &boat, 1.4f);

	// TODO 6: Draw the girl. Make sure it follows the ship movement!
	App->renderer->Blit(graphics, 191, 98 + offset, &(boat_girl.GetCurrentFrame()), 1.4f); // boat_girl animation
	
	// Draw rest of the animations
	App->renderer->Blit(graphics, 127, 90 + offset, &(boat_guys.GetCurrentFrame()), 1.4f);	// boat_guys animation
	App->renderer->Blit(graphics, 223, 98 + offset, &(boat_boy.GetCurrentFrame()), 1.4f);	// boat_boy animation
	App->renderer->Blit(graphics, 287, 90 + offset, &(boat_man.GetCurrentFrame()), 1.4f);	// boat_man animation
	App->renderer->Blit(graphics, 86, 20 + offset, &(boat_upper_guy1.GetCurrentFrame()), 1.4f);	// boat_upper_guy1 animation
	App->renderer->Blit(graphics, 128, 18 + offset, &(boat_upper_guy2.GetCurrentFrame()), 1.4f);	// boat_upper_guy2 animation
	
	App->renderer->Blit(graphics, 0, 165, &ground);
	//App->renderer->Blit(graphics, 162, 158, &bitt);
	App->renderer->Blit(graphics, 380, 162, &bitt_small);

	// TODO 10: Build an entire new scene "honda", you can find its
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	// Start the first scene --
	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		App->fade->FadeToBlack(App->scene_honda, this, 3.0f);
	}

	return UPDATE_CONTINUE;
}