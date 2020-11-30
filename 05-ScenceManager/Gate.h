#pragma once
#include"GameObject.h"
#include "Define.h"
class Gate :public CGameObject
{
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	void Render();

	//int getnextmap() { return nextmap; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	Gate();
	~Gate();
};

