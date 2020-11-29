#include "Intro.h"

void Intro::Render()
{
	animation_set->at(0)->Render(1, x, y);
}

void Intro::GetBoundingBox(float& l, float& t, float& r, float& b)
{}