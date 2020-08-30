#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL.h"

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
	light_punch.frames.push_back({ 19, 269, 64, 93 });
	light_punch.speed = 0.06f;

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
	heavy_punch.speed = 0.04f;

	// crouch_light_punch animation
	crouch_light_punch.frames.push_back({ 24, 1313, 69, 93 });
	crouch_light_punch.frames.push_back({ 118, 1313, 96, 93 });
	crouch_light_punch.frames.push_back({ 24, 1313, 69, 93 });
	crouch_light_punch.speed = 0.06f;

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
	crouch_heavy_punch.speed = 0.04f;

	// jump animation
	jump.frames.push_back({ 16, 846, 57, 110 });
	jump.frames.push_back({ 99, 822, 59, 110 });
	jump.frames.push_back({ 175, 804, 52, 110 });
	jump.frames.push_back({ 250, 797, 56, 110 });
	jump.frames.push_back({ 326, 812, 50, 110 });
	jump.frames.push_back({ 396, 809, 50, 110 });
	jump.frames.push_back({ 463, 818, 57, 110 });
	jump.frames.push_back({ 463, 818, 57, 110 });
	jump.frames.push_back({ 16, 846, 57, 110 });
	jump.speed = 0.04f;

	// jump_light_punch animation
	jump_light_punch.frames.push_back({ 28, 984, 55, 110 });
	jump_light_punch.frames.push_back({ 96, 984, 84, 110 });
	jump_light_punch.speed = 0.04f;
	
	// Set player 1 pose
	player_state = STANDING;

	playing_animation = nullptr;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("resources/ryu4.png"); // arcade version

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

	if (playing_animation != nullptr)
	{
		PlayFullAnimation();
	}
	else
	{
		switch (player_state)
		{
		case STANDING:
			StandingInput();
			break;

		case CROUCHING:
			CrouchingInput();
			break;

		case JUMPING:
			JumpingInput();
			break;
		default:
			player = idle.GetCurrentFrame();
		}
	}

	App->renderer->Blit(graphics, position.x, position.y, &player, Player_Anim_Speed);
	
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::PlayFullAnimation()
{
	if (playing_animation->IsLastFrame())
	{
		playing_animation->ResetAnimation();
		player_state = next_state;
		playing_animation = nullptr;
	}
	else
	{
		player = playing_animation->GetCurrentFrame();
	}
}

void ModulePlayer::StandingInput()
{
	if (App->input->GetKey(SDL_SCANCODE_U))			// Ryu light_punch animation
	{
		playing_animation = &light_punch;
		next_state = player_state;
	}
	else if (App->input->GetKey(SDL_SCANCODE_I))	// Ryu medium_punch animation
	{
		playing_animation = &medium_punch;
		next_state = player_state;
	}
	else if (App->input->GetKey(SDL_SCANCODE_O))	// Ryu heavy_punch animation
	{
		playing_animation = &heavy_punch;
		next_state = player_state;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S))	// Ryu crouch animatiom
	{
		playing_animation = &crouch;
		next_state = CROUCHING;
	}
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)	// Ryu jump animation
	{
		player_state = JUMPING;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A))	// Ryu backward animation
	{
		--position.x;
		player = backward.GetCurrentFrame();
	}
	else if (App->input->GetKey(SDL_SCANCODE_D))	// Ryu forward animation
	{
		++position.x;
		player = forward.GetCurrentFrame();
	}
	else											// Ryu idle animation
	{
		player = idle.GetCurrentFrame();
	}
}

void ModulePlayer::CrouchingInput()
{
	if (App->input->GetKey(SDL_SCANCODE_U))			// Ryu light_punch animation
	{
		playing_animation = &crouch_light_punch;
		next_state = player_state;
	}
	else if (App->input->GetKey(SDL_SCANCODE_I))	// Ryu medium_punch animation
	{
		playing_animation = &crouch_medium_punch;
		next_state = player_state;
	}
	else if (App->input->GetKey(SDL_SCANCODE_O))	// Ryu heavy_punch animation
	{
		playing_animation = &crouch_heavy_punch;
		next_state = player_state;
	}
	else if (!App->input->GetKey(SDL_SCANCODE_S))	// Ryu stand_up animation
	{
		playing_animation = &stand_up;
		next_state = STANDING;
	}
	else											// Ryu crouch idle animation
	{
		player = crouch_idle;
	}
}

void ModulePlayer::JumpingInput()
{
	switch (jump_attack) {
	case 0:
		if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)			// Ryu light_punch animation
		{
			jump_attack = 1;
			player = jump_light_punch.GetCurrentFrame();
		}
		else if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)	// Ryu medium_punch animation
		{
			playing_animation = &jump_medium_punch;
			next_state = player_state;
		}
		else if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)	// Ryu heavy_punch animation
		{
			playing_animation = &jump_heavy_punch;
			next_state = player_state;
		}
		else
		{
			player = jump.GetCurrentFrame();
		}
		break;
	case 1:
		jump_light_punch.SetFrame(1);
		player = jump_light_punch.GetCurrentFrame();
		jump_attack = 2;
		break;
	case 2:
	default:
		break;
	}

	if (position.y > 10 && up)
	{
		--position.y;
	}
	else if (position.y >= 103)
	{
		up = true;
		jump.ResetAnimation();
		jump_light_punch.ResetAnimation();
		jump_attack = 0;
		player_state = STANDING;
	}
	else
	{
		up = false;
		++position.y;
	}
	
}