#include "HealthBar.h"

void HealthBar::Update(CSimon* simon)
{
	//this->hp = simon->simon_HP;
}

void HealthBar::Render()
{
	//CSimon* simon = new CSimon();
	for (int i = 0; i < hp; i++)
	{
		animation_set->at(0)->Render(0, x+110+10*i, y+33);
	}
	for (int i = 0; i < 16-hp; i++)
	{
		animation_set->at(1)->Render(0,x+260 - 10 *i, y+33);
	}
	for (int i = 0; i < 16; i++)
	{
		animation_set->at(2)->Render(0, x + 110 + 10 * i, y + 52);
	}
	//animation_set->at(0)->Render(0, x+110, y+33);
	RenderBoundingBox();
}
//int HealthBar::UpdateHP(int _hp)
//{
//	//this->hp = _hp;
//	return _hp;
//}

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