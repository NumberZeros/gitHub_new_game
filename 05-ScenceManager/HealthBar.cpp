#include "HealthBar.h"

void HealthBar::Render()
{
	//CSimon* simon = new CSimon();
	for (int i = 0; i < 16; i++)
	{
		animation_set->at(0)->Render(0, i*10 + 110, 33);
	}
	/*for (int i = 0; i < hplost; i++)
	{
		animation_set->at(1)->Render(0,260 - x*i, 33);
	}*/
	RenderBoundingBox();
}
int HealthBar::UpdateHP(int _hp)
{
	//this->hp = _hp;
	return _hp;
}
void HealthBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;
	//r = x + BRICK_BBOX_WIDTH;
	//b = y + BRICK_BBOX_HEIGHT;
}
HealthBar::HealthBar()
{
	//this->hp = _hp;
}