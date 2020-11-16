#include "HealthBar.h"

void HealthBar::Render()
{
	//CSimon* simon = new CSimon();
	for (int i = 0; i < hp; i++)
	{
		animation_set->at(0)->Render(0, x*i + 110, 33);
	}
	for (int i = 0; i < hplost; i++)
	{
		animation_set->at(1)->Render(0,260 - x*i, 33);
	}
	RenderBoundingBox();
}
void HealthBar::UpdateHP(int _hp)
{
	this->hp = _hp;
	this->hplost = 16 - hp;
}
void HealthBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//l = x;
	//t = y;
	//r = x + BRICK_BBOX_WIDTH;
	//b = y + BRICK_BBOX_HEIGHT;
}