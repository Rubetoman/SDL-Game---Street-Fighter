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
	crouch_idle.y = 1204;
	crouch_idle.w = 62;
	crouch_idle.h = 93;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 11, 60, 93});
	idle.frames.push_back({95, 11, 60, 93});
	idle.frames.push_back({184, 11, 60, 93});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 11, 60, 93});
	idle.speed = 0.08f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 125, 61, 93});
	backward.frames.push_back({628, 126, 59, 93});
	backward.frames.push_back({713, 125, 57, 93});
	backward.frames.push_back({797, 124, 57, 93});
	backward.frames.push_back({883, 126, 58, 93});
	backward.frames.push_back({974, 125, 57, 93});
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
	crouch.frames.push_back({ 32, 1204, 54, 93 });
	crouch.frames.push_back({ 115, 1204, 58, 93 });
	crouch.frames.push_back({ 197, 1204, 62, 93 });
	crouch.speed = 0.1f;

	// stand_up animation
	stand_up.frames.push_back({ 197, 1204, 62, 93 });
	stand_up.frames.push_back({ 115, 1204, 58, 93 });
	stand_up.frames.push_back({ 32, 1204, 54, 93 });
	stand_up.speed = 0.1f;

	// light_punch animation
	light_punch.frames.push_back({ 19, 269, 64, 93 });
	light_punch.frames.push_back({ 108, 269, 92, 93 });
	light_punch.speed = 0.08f;

	// medium_punch animation
	medium_punch.frames.push_back({ 252, 269, 60, 94 });
	medium_punch.frames.push_back({ 333, 269, 75, 94 });
	medium_punch.frames.push_back({ 432, 269, 109, 94 });
	medium_punch.frames.push_back({ 333, 269, 75, 94 });
	medium_punch.frames.push_back({ 252, 269, 60, 94 });
	medium_punch.speed = 0.08f;
	
	// heavy_punch animation
	heavy_punch.frames.push_back({ 252, 269, 60, 94 });
	heavy_punch.frames.push_back({ 333, 269, 75, 94 });
	heavy_punch.frames.push_back({ 432, 269, 109, 94 });
	heavy_punch.frames.push_back({ 333, 269, 75, 94 });
	heavy_punch.frames.push_back({ 252, 269, 60, 94 });
	heavy_punch.speed = 0.06f;

	// crouch_light_punch animation
	crouch_light_punch.frames.push_back({ 24, 1313, 69, 93 });
	crouch_light_punch.frames.push_back({ 118, 1313, 96, 93 });
	crouch_light_punch.speed = 0.08f;

	// crouch_medium_punch animation
	crouch_medium_punch.frames.push_back({ 264, 1313, 66, 93 });
	crouch_medium_punch.frames.push_back({ 359, 1313, 66, 93 });
	crouch_medium_punch.frames.push_back({ 450, 1313, 92, 93 });
	crouch_medium_punch.frames.push_back({ 359, 1313, 66, 93 });
	crouch_medium_punch.frames.push_back({ 264, 1313, 66, 93 });
	crouch_medium_punch.speed = 0.08f;

	// crouch_heavy_punch animation
	crouch_heavy_punch.frames.push_back({ 264, 1313, 66, 93 });
	crouch_heavy_punch.frames.push_back({ 359, 1313, 66, 93 });
	crouch_heavy_punch.frames.push_back({ 450, 1313, 92, 93 });
	crouch_heavy_punch.frames.push_back({ 359, 1313, 66, 93 });
	crouch_heavy_punch.frames.push_back({ 264, 1313, 66, 93 });
	crouch_heavy_punch.speed = 0.06f;
	
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
		if (App->input->GetKey(SDL_SCANCODE_U))			// Ryu light_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(light_punch.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_I))	// Ryu medium_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(medium_punch.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_O))	// Ryu heavy_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(heavy_punch.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_S))	// Ryu crouch animatiom
		{
			App->renderer->Blit(graphics, position.x, position.y, &(crouch.GetCurrentFrame()), 1.4f);
			player1_pose = CROUCHING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W))	// Ryu jump animation
		{
			player1_pose = JUMPING;
		}
		else if (App->input->GetKey(SDL_SCANCODE_A))	// Ryu backward animation
		{
			--position.x;
			App->renderer->Blit(graphics, position.x, position.y, &(backward.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_D))	// Ryu forward animation
		{
			++position.x;
			App->renderer->Blit(graphics, position.x, position.y, &(forward.GetCurrentFrame()), 1.4f);
		}
		else											// Ryu idle animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(idle.GetCurrentFrame()), 1.4f);
		}
		break;

	case CROUCHING:
		if (App->input->GetKey(SDL_SCANCODE_U))			// Ryu light_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(crouch_light_punch.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_I))	// Ryu medium_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(crouch_medium_punch.GetCurrentFrame()), 1.4f);
		}
		else if (App->input->GetKey(SDL_SCANCODE_O))	// Ryu heavy_punch animation
		{
			App->renderer->Blit(graphics, position.x, position.y, &(crouch_heavy_punch.GetCurrentFrame()), 1.4f);
		}
		else if (!App->input->GetKey(SDL_SCANCODE_S))	// Ryu stand_up animation
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