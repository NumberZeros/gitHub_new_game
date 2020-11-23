#include "Timer.h"
#include "Utils.h"
//void Timer::Start()
//{
//	start = GetTickCount();
//}

//void Timer::Stop()
//{
//	start = 0;
//}

//bool Timer::IsTimeUp()
//{
//	return GetTickCount() - start > end;
//}

void Timer::Update()
{
	if (GetTickCount() - action_time > 1000)
	{ 
	//	DebugOut(L"time: %d \f", GetTickCount() - action_time);
		timeremain -= 1;
		action_time = GetTickCount();
		if (timeremain < 0)
			timeremain = 0;
	}
	a = timeremain / 100;
	b = (timeremain - (100 * a)) / 10;
	c = timeremain - 100 * a - 10 * b;
	/*time += _a;
	timeremain = timemax - (time / CLOCKS_PER_SEC);
	num=to_string(timeremain);*/
}

void Timer::Render()
{
		animation_set->at(a)->Render(0, x + 305, y+13);
		animation_set->at(b)->Render(0, x + 14 + 305, y + 13);
		animation_set->at(c)->Render(0, x + 28 + 305, y + 13);
}

void Timer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}

//Timer::Timer()
//{
//	//a = 4;
//	//b = 0;
//	//c = 0;
//}

