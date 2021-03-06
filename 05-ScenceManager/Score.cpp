#include "Score.h"

void Score::Update()
{
	if (GetTickCount() - action_time_score > 50)
	{
		//	DebugOut(L"time: %d \f", GetTickCount() - action_time);
		score += 1;
		action_time_score = GetTickCount();
	}
}

void Score::Render()
{
	//animation_set->at(0)->Render(0, x  + 10, y );
	//animation_set->at(1)->Render(0, x  + 25, y );
	//animation_set->at(2)->Render(0, x + 40, y );
	//animation_set->at(3)->Render(0, x + 55, y );
	//animation_set->at(4)->Render(0, x + 70, y );
	//animation_set->at(5)->Render(0, x + 85, y );
	/*for (int i = 0; i < 6; i++)
	{
		if (score >= 10)
		{
			a[i] = score % 10;
			score /= 10;
		}
		else
			a[i] = score;
	}*/

	m[1] = mana / 10;
	m[0] = mana % 10;
	p[1] = point / 10;
	p[0] = point % 10;
	a[5] = score / 100000;
	a[4] = (score% 100000) / 10000;
	a[3] = (score%10000) / 1000;
	a[2] = (score%1000) / 100;
	a[1] = (score%100) / 10;
	a[0] = (score % 10) % 10;
	for (int i = 5; i >= 0; i--)
	{
		animation_set->at(a[i])->Render(0, x +(5-i)* 15+ 110, y+ 13);
	}
	for (int i = 1; i >= 0; i--)
	{
		animation_set->at(m[i])->Render(0, x +(1-i)* 15+300+ 110, y+20+ 13);
	}
	for (int i = 1; i >= 0; i--)
	{
		animation_set->at(p[i])->Render(0, x + (1 - i) * 15+300+ 110, y+36+ 13);
	}
	animation_set->at(0)->Render(0, x +  360 + 110, y + 10);
	animation_set->at(stage)->Render(0, x + 375 + 110, y + 10);
}

void Score::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
