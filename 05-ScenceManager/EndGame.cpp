#include "EndGame.h"

void EndGame::Render()
{
	animation_set->at(0)->Render(1, x, y);
}

void EndGame::GetBoundingBox(float& l, float& t, float& r, float& b)
{}