#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	SDL_Rect& GetPreviousFrame()
	{
		current_frame -= speed;
		if (current_frame <= 0)
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	inline int GetCurrentFrameNumber()
	{
		return (int)current_frame;
	}

	inline bool IsLastFrame()
	{
		if (current_frame >= frames.size() - 1)
			return true;
		return false;
	}

	inline void ResetAnimation() 
	{
		current_frame = 0.0f;
	}
};