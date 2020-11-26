#include "Board.h"

string CBoard::FillNumber(string s, UINT MaxNumber)
{
	return string();
}

CBoard::CBoard()
{
}

CBoard::CBoard(int HealSimon)
{
	//board = CAnimationSets::GetInstance()->Get(board_ani_set);
	//healsimon = new HealthBar(HealSimon);
}

void CBoard::Update(DWORD dt, int currentheal, int healboss)
{
}

void CBoard::UpdateFollowSimon(int idmap, int camx, int camy, CSimon* simon)
{
	
	//heallost->Render(lose_heal, camx, camy);
}

void CBoard::Render()
{
	animation_set->at(0)->Render(0, x, y);
	RenderBoundingBox();
}

void CBoard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
