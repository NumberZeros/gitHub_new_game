#include "SubWL.h"

void SubWL::Update()
{
}

void SubWL::Render()
{
	animation_set->at(2)->Render(0, x+310, y+36);
	RenderBoundingBox();
}

void SubWL::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

SubWL::SubWL()
{

}
