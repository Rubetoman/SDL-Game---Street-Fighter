#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 191;
	position.y = 103;

	// crouch_idle sprite
	crouch_idle.x = 197;
	crouch_idle.y = 1211;
	crouch_idle.w = 62;
	crouch_idle.h = 86;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.08f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 7, 127, 61, 93 });
	forward.frames.push_back({ 78, 127, 61, 93 });
	forward.frames.push_back({ 162, 127, 66, 93 });
	forward.frames.push_back({ 258, 127, 65, 93 });
	forward.frames.push_back({ 352, 127, 61, 93 });
	forward.frames.push_back({ 432, 127, 61, 93 });
	forward.speed = 0.1f;

	// crouch animation
	crouch.frames.push_back({ 32, 1211, 54, 86 });
	crouch.frames.push_back({ 115, 1211, 58, 86 });
	crouch.frames.push_back({ 197, 1211, 62, 86 });
	crouch.speed = 0.1f;

	// stand_up animation
	stand_up.frames.push_back({ 197, 1211, 62, 86 });
	stand_up.frames.push_back({ 115, 1211, 58, 86 });
	stand_up.frames.push_back({ 32, 1211, 54, 86 });
	stand_up.speed = 0.1f;

	// Set player 1 pose
	player1_pose = STANDING;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	switch (player1_pose)
	{
	case STANDING:
		if (App->input->GetKey(SDL_SCANCODE_A))			// Ryu backward animation
		{
			--position.x;
			App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()), 1.4f);	
		}
		else if (App->input->GetKey(SDL_SCANCODE_D))	// Ryu forward animation
		{
			++position.x;
			App->renderer->Blit(graphics, position.x, position.y, &(forward.GetCurrentFrame()), 1.4f);	
		}
		else if (App->input->GetKey(SDL_SCANCODE_S))	// Ryu crouch animatiom
		{
			App->renderer->Blit(graphics, position.x, position.y, &(stand_up.GetCurrentFrame()), 1.4f);
			player1_pose = CROUCHING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W))	// Ryu jump animation
		{

		}
		else if (App->input->GetKey(SDL_SCANCODE_U))	// Ryu light_punch animation
		{

		}
		else											// Ryu idle animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.4f);
		}
		break;
	case CROUCHING:
		if (!App->input->GetKey(SDL_SCANCODE_S))		// Ryu stand_up animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(stand_up.GetCurrentFrame()), 1.4f);
			player1_pose = STANDING;
		}
		else											// Ryu crouch idle animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &crouch_idle, 1.4f);
		}
		break;
	case JUMPING:
		break;
	}
	
	
	return UPDATE_CONTINUE;
}