#include "Score.h"

void Score::Update()
{
	
}

void Score::Render()
{
	for (int i = 0; i < 6; i++)
	{
		if (score > 10)
		{
			a[i] = score % 10;
			score /= 10;
		}
		else
			a[i] = score;
	}
	for (int i = 0; i < 2; i++)
	{
		if (mana > 10)
		{
			m[i] = mana % 10;
			mana /= 10;
		}
		else
			m[i] = mana;
	}
	for (int i = 0; i < 2; i++)
	{
		if (point > 10)
		{
			p[i] = point % 10;
			point /= 10;
		}
		else
			p[i] = point;
	}
	for (int i = 5; i >=0; i--)
	{
		animation_set->at(a[i])->Render(0, x + 110 + (5 - i) * 15, y + 13);
	}
	for (int i = 1; i >= 0; i--)
	{
		animation_set->at(m[i])->Render(0, x + 110 + (1 - i) * 15 + 300, y + 20 + 13);
	}
	for (int i = 1; i >= 0; i--)
	{
		animation_set->at(p[i])->Render(0, x + 110 + (1 - i) * 15 + 300, y + 40 + 13);
	}
}

void Score::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
