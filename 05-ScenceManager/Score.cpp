#include "Score.h"

void Score::Update()
{
}

void Score::Render()
{
	animation_set->at(0)->Render(0, x  + 10, y );
	animation_set->at(1)->Render(0, x  + 25, y );
	animation_set->at(2)->Render(0, x + 40, y );
	animation_set->at(3)->Render(0, x + 55, y );
	animation_set->at(4)->Render(0, x + 70, y );
	animation_set->at(5)->Render(0, x + 85, y );
}

void Score::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
