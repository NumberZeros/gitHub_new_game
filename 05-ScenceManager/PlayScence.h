#pragma once
#include "Game.h"
#include "Utils.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Koopas.h"
#include "Gate.h"

#include "Brick.h"
#include "Simon.h"
#include "Zombie.h"
#include "Goomba.h"
#include "Weapon.h"
#include "Axe.h"
#include "Knife.h"
#include "Holywater.h"
#include "HealthBar.h"
#include "Board.h"
#include "Timer.h"
#include "Item.h"
#include "TileMap.h"
#include "HealthBar.h"
#include "SubW.h"
#include "Score.h"
#include "Define.h"
#include "Boss.h"
#include "BlackLeopard.h"

class CPlayScene: public CScene
{
public: 
	
	CSimon *player;					// A play scene has to have player, right? 
	Boss* boss;
	CZombie* zombie;
	CBlackLeopard* black;

	Gate* gate;

	CBrick* brick;

	CItem* item;
	CWeapon* weapon;
	CAxe* axe; 
	CKnife* knife;
	CHlw* hlw;

	HealthBar* healthbar;
	Timer* timer;
	CBoard* board;
	Score* score;
	SubW* subw;
	TileMap* tilemap;
	vector<LPSPRITE> playerHP;
	vector<LPSPRITE> enemyHP;
	vector<LPSPRITE> loseHP;

	int idstage;
	int current_scene;
	bool isIntro = false;

	vector<LPGAMEOBJECT> objects;

	float prevWeaponX, prevWeaponY;


	vector<string> linkmap;

	int isintro = 0;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	void _ParseSection_SCENEOBJECT(string line);
	void _ParseSection_INFOMAP(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	void LoadIntro();
	void LoadMapItro();
	virtual void Load();
	void LoadSimon(CSimon* prevSimon);
	void LoadTimer(Timer* prevTimer);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void ResetMap();

	void LoadMap();
	void LoadObject();

	bool CheckInCam(LPGAMEOBJECT a);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	void Run(int _nx);
	void AutoWalk(int des);
	void StairUp();
	void StairDown();
	void Jump();
	void Hit();
	void Throw_Axe();
	void Throw_Knife();
	void Throw_Holywater();
	void SitDown();
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

