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

// Reference at https://www.youtube.com/watch?v=9WTxwfK0sWc

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 848;
	ground.h = 64;

	// Ceiling
	ceiling.x = 90;
	ceiling.y = 8;
	ceiling.w = 734;
	ceiling.h = 48;

	// Background
	background.x = 127;
	background.y = 128;
	background.w = 664;
	background.h = 200;

	// Bucket
	bucket.x = 541;
	bucket.y = 85;
	bucket.w = 36;
	bucket.h = 34;

	// Pool
	pool.x = 164;
	pool.y = 66;
	pool.w = 337;
	pool.h = 57;

	// flag animation
	/*flag.frames.push_back({ 848, 208, 40, 40 });
	flag.frames.push_back({ 848, 256, 40, 40 });
	flag.frames.push_back({ 848, 304, 40, 40 });
	flag.speed = 0.08f;

	// Girl Animation from coordinates from ken_stage.png
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
	boat_man.speed = 0.04f;*/
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading ken scene");

	graphics = App->textures->Load("honda_stage.png");
	graphics2 = App->textures->Load("honda_stage2.png");

	// Enable the player module
	App->player->Enable();
	// trigger background music
	App->audio->PlayMusic("honda.ogg", 2.0f);

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics2, -111, 160, &ground, 1.5f);	// ground
	App->renderer->Blit(graphics2, 0, -15, &background, 1.2f);	// background
	App->renderer->Blit(graphics2, 105, 156, &bucket, 1.5f);	// bucket
	App->renderer->Blit(graphics2, 177, 125, &pool, 1.5f);		// pool
	//App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 1.8f); // flag animation
	App->renderer->Blit(graphics, -58, -15, &ceiling, 1.5f);	// ceiling

	// Pressing space triggers a switch to ken logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE)) {
		//CleanUp();
		//App->fade->FadeToBlack(App->scene_ken, nullptr, 3.0f);
	}
	return UPDATE_CONTINUE;
}