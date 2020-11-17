#pragma once
#include "GameObject.h"
#include"HealthBar.h"
#include"Number.h"
#include"Simon.h"
//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16
#define board_ani_set 8
#define board_ani 0

class CBoard : public CGameObject
{
	LPANIMATION_SET board;
	//LPSPRITE board;
	//float posx, posy;
	HealthBar* healsimon;
	HealthBar* heallost;
	HealthBar* healboss;
	Number numb;

	string FillNumber(string s, UINT MaxNumber);
	vector<LPSPRITE> subweapon;
	vector<LPSPRITE> doubletriple;

	int time, timeremain;
	int timemax;
	bool checktime;
public:
	CBoard();
	CBoard(int HealSimon);
	void Update(DWORD dt, int currentheal, int healboss);
	void UpdateFollowSimon(int idmap, int camx, int camy, CSimon* simon);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
};