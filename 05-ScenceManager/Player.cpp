#include "Player.h"

Player::Player(CGame* game, CPlayScene* scene)
{
	this->scence = scence;
	this->game = game;
}

void Player::Init()
{
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < 16; i++)
	{
		playerHP.push_back(sprites->Get(126));
		loseHP.push_back(sprites->Get(127));
		enemyHP.push_back(sprites->Get(128));
	}
}

void Player::Update(DWORD dt, bool stopwatch)
{
	simonHP = 16;
}

void Player::Render()
{
	/*RECT rect;
	information = "draw something";
	SetRect(&rect, 0, 15, SCREEN_WIDTH, 80);
	if (game->GetFont() != NULL)
		game->GetFont()->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));*/

	for (int i = 0; i < simonHP; i++)
	{
		playerHP[i]->Draw(0, -1, 105 + i * 9, 31);
	}
}
