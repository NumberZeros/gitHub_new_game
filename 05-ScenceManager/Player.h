#pragma once

#include "Game.h"
#include "Simon.h"
#include "PlayScence.h"
#include <vector>
#include <string>
//#include "Sprites.h"


class Player
{
private:
	//SceneManager* scene;
	CPlayScene* scence;
	CGame* game;
	CSimon* simon;
	//Boss* boss;

	string information;

	vector<LPSPRITE> playerHP;
	vector<LPSPRITE> enemyHP;
	vector<LPSPRITE> loseHP;

	/*Sprite* subWeaponBox;
	Sprite* choose;*/
	LPDIRECT3DTEXTURE9 pause;
	LPDIRECT3DTEXTURE9 over;
	vector<LPSPRITE> subWeaponList;
	vector<LPSPRITE> itemList;
	int score;
	int time;
	int id_scene;
	int item;
	int energy;
	int life;
	int subWeapon;
	int simonHP;
	int bossHP;
public:
	Player(CGame* game, CPlayScene* scene);
	~Player();

	void Init();
	void Update(DWORD dt, bool stopwatch);
	void Render();
};

