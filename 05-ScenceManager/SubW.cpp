#include "SubW.h"

void SubW::Update()
{
}

void SubW::Render()
{
	//if (this->subw != NULL)
	{
		animation_set->at(subw)->Render(0, x + 310, y + 33);
	}

	
}

void SubW::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
