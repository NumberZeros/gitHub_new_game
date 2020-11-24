#include "SubW.h"

void SubW::Update()
{
}

void SubW::Render()
{
	animation_set->at(subw)->Render(0, x + 310, y + 36);
}

void SubW::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
