#include "PlayScence.h"

Boss::Boss()
{
	height = BOX_WIDTH;
	width = BOX_HEIGTH;
	SetState(BOX_SLEEP);
}

Boss::Boss(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);

	if (isAttack) 
	{
		/*CGame* game = CGame::GetInstance();
		DebugOut(L"x %f cam right \n", game->GetCamPosX());
		if (x < game->GetCamPosX() - 20 && y > 400 && x > game->GetCamPosX() - SCREEN_WIDTH + 20) {
			
		}*/
	}
}

bool Boss::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
	return false;
}

void Boss::Render()
{
	animation_set->at(state)->Render(nx, x, y, 255);

	RenderBoundingBox();
}

void Boss::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
		case BOX_ATTACK:
			isAttack = true;
			break;
		case BOX_DIE:
			isAttack = false;
			action_time = GetTickCount();
			isDie = true;
			break;
		default:
			isAttack = false;
			action_time = 0;
			break;
	}
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = y + height;

}
