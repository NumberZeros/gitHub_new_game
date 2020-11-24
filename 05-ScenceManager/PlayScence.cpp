#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Gate.h"
#include "Board.h"
#include "BlackLeopard.h"
#include "Zombie.h"
#include "Item.h"
#include "Merman.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::Load()
{
	LoadObject();
	LoadMap();
}

void CPlayScene::LoadSimon(CSimon* prevSimon) {
     	player = prevSimon;
}

void CPlayScene::LoadTimer(Timer* prevTimer) {
	timer = prevTimer;
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++) {
		LPGAMEOBJECT obj = objects.at(i);
		
		if (!dynamic_cast<CSimon*>(obj))
		{
			if (!dynamic_cast<Timer*>(obj)) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
			
		}
		
			
	}
	weapon = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::ResetMap() {
	for (int i = 0; i < objects.size(); i++) 
		delete objects[i];

	objects.clear();
	player = NULL;
	timer = NULL;
	DebugOut(L"ResetMap! \n");
}

void CPlayScene::LoadMap() {
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	tilemap = new TileMap();
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;
		if (line == "[SCENEOBJECT]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_LOADMAP; continue;
		}


		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_SCENEOBJECT(line); break;
		case SCENE_SECTION_LOADMAP: _ParseSection_INFOMAP(line); break;
		}
	}
	f.close();
}

void CPlayScene::_ParseSection_SCENEOBJECT(string file) {
	ifstream f;
	f.open(file);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;// skip comment lines
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", file);
}
void CPlayScene::LoadObject() {
	ifstream f;
	f.open(L"Scenes\\Castlevania.txt");

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;// skip comment lines
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());
	int id = 0;
	int secondGood = 12;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (!player)
		{
			obj = new CSimon(x, y);
			player = (CSimon*)obj;
			player->SetState(SIMON_STATE_WALKING);
			DebugOut(L"[INFO] Player object created!\n");
		}
		else {
			obj = player;
		}
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_BLACK_LEOPARD: obj = new CBlackLeopard(); 	break;
	case OBJECT_TYPE_ZOMBIE: obj = new CZombie(); break;
	case OBJECT_TYPE_MERMAN:
		obj = new CMerman();
		break;
	case OBJECT_TYPE_WEAPON:
		obj = new CWeapon();
		weapon = (CWeapon*)obj;
		break;
	case OBJECT_TYPE_AXE:
		obj = new CAxe();
		this->axe = (CAxe*)obj;
		break;
	case OBJECT_TYPE_KNIFE:
		obj = new CKnife();
		this->knife = (CKnife*)obj;
		break;
	case OBJECT_TYPE_HLW:
		obj = new CHlw();
		this->hlw = (CHlw*)obj;
		break;
	case OBJECT_TYPE_KOOPAS: 
		obj = new CKoopas(); 
		break;
	case OBJECT_TYPE_GATE:
		obj = new Gate();
		gate = (Gate*)obj;
		break;
	case OBJECT_TYPE_BOARD:
		obj = new CBoard(8);
		board = (CBoard*)obj;
		break;
	case OBJECT_TYPE_HEALTHBAR:
		obj = new HealthBar();
		healthbar = (HealthBar*)obj;
		break;
	case OBJECT_TYPE_SCORE:
		obj = new Score();
		score = (Score*)obj;
		break;
	case OBJECT_TYPE_TIMER:
		if (!timer)
		{
			obj = new Timer();
			timer = (Timer*)obj;
		}
		else {
			obj = timer;
		}
		break;
	case OBJECT_TYPE_ITEM:
		id = atof(tokens[4].c_str());
		secondGood = atof(tokens[5].c_str());
		obj = new CItem();
		item = (CItem*)obj;
		if (id == ID_ITEM_TYPE_TORCH) { // 1
			item->SetID(ITEM_ANI_TORCH);
			item->SetState(ITEM_STATE_SHOW);
			item->secondGood = secondGood;
		}
		else if (id == ID_ITEM_TYPE_CANDLE) {
			item->SetID(ITEM_ANI_CANDLE);
			item->SetState(ITEM_STATE_SHOW);
			item->secondGood = secondGood;
		}
		break;
	case OBJECT_TYPE_BOSS:
		obj = new Boss();
		boss = (Boss*)obj;
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::_ParseSection_INFOMAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 10) return;
	int IDmap = atoi(tokens[0].c_str());
	wstring pathpic = ToWSTR(tokens[1]);
	wstring pathtxt = ToWSTR(tokens[2]);
	int num_row = atoi(tokens[3].c_str());
	int num_col = atoi(tokens[4].c_str());
	int num_row_read = atoi(tokens[5].c_str());
	int num_col_read = atoi(tokens[6].c_str());
	int tile_width = atoi(tokens[7].c_str());
	int tile_height = atoi(tokens[8].c_str());
	idstage = atoi(tokens[9].c_str());
	int r = atoi(tokens[14].c_str());
	int g = atoi(tokens[15].c_str());
	int b = atoi(tokens[16].c_str());

	tilemap->LoadMap(IDmap, pathpic.c_str(), pathtxt.c_str(), num_row, num_col, num_row_read, num_col_read, tile_width, tile_height, r, g, b);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	CGame* game = CGame::GetInstance();
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}


	if (player == NULL) return;
	if (timer == NULL) return;
	timer->Update();
	healthbar->hp = player->simon_HP;

	//simon die reset scence
	if (player->simon_HP < 1) {
		if (GetTickCount() - player->action_time > 3000) {
			ResetMap();
			CGame::GetInstance()->SwitchScene(game->current_scene);
		}
	}

	if (timer->timeremain < 1)
	{
		player->SetState(SIMON_STATE_DIE);
		if (GetTickCount() - player->action_time > 3000) 
		{
			ResetMap();
			CGame::GetInstance()->SwitchScene(game->current_scene);
		}
	}

	if (boss) {
		if (boss->x - player->x < 50) {
			boss->SetState(BOX_ATTACK);
		}
	}
	

	//// nhung ham lien quan vi tri nam o duoi nhung ham lien quan trang thai nam o tren
	float cx, cy;
	player->GetPosition(cx, cy);

	if (weapon) {
		//update position for simon
		if (!prevWeaponX || !prevWeaponY || prevWeaponX != weapon->x || prevWeaponY != weapon->y) {
			prevWeaponX = player->x;
			prevWeaponY = player->y;
			if (player->isSit) weapon->UpdatePosionWithSimon(player->GetPositionX(), player->GetPositionY() + 20, player->nx);
			weapon->UpdatePosionWithSimon(player->GetPositionX(), player->GetPositionY(), player->nx);
			weapon->level = player->level;
		}
	}
	

	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;

	float lenghtMap = (float)(tilemap->getwidthmap() - (game->GetScreenWidth() / 2));
	// fix bug camera 
	if (cx < 0) cx = 0.0f;
	if (player->x > lenghtMap) return;										// khi chuyen man da bi l�i nen tam comment 
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	board->SetPosition(cx, 0);
	healthbar->SetPosition(cx, 0);
	timer->SetPosition(cx, 0);
}

void CPlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	tilemap->Draw();
	for (int i = 0; i < objects.size(); i++) 
		objects[i]->Render();
}

/*
	Unload current scene
*/


bool CPlayScene::CheckInCam(LPGAMEOBJECT a)
{
	CGame* game = CGame::GetInstance();
	return (a->GetPositionX() >= game->GetCamPosX()) && (a->GetPositionX() < (game->GetCamPosX() + SCREEN_WIDTH)) && (a->GetPositionY() >= game->GetCamPosY()) && (a->GetPositionY() < game->GetCamPosY() + SCREEN_HEIGHT);

}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	CWeapon* weapon = ((CPlayScene*)scence)->weapon;

	if (simon->GetState() == SIMON_STATE_DIE) return;
		if (game->IsKeyDown(DIK_RIGHT)) Run(1);
		else if (game->IsKeyDown(DIK_LEFT)) Run(-1);
		else if (game->IsKeyDown(DIK_1)) weapon->level = 1;
		else if (game->IsKeyDown(DIK_2)) weapon->level = 2;
		else if (game->IsKeyDown(DIK_3)) weapon->level = 3;
		else simon->SetState(SIMON_STATE_IDLE);
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	if (game->IsKeyRelease(DIK_DOWN))
	{
		SitDown();
	}
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	CAxe* axe = ((CPlayScene*)scence)->axe;
	CKnife* knife = ((CPlayScene*)scence)->knife;
	CHlw* hlw = ((CPlayScene*)scence)->hlw;
	CPlayScene* playscene = ((CPlayScene*)scence);

	switch (KeyCode)
	{
	case DIK_SPACE:
		Jump();
		break;
	case DIK_DOWN:
		SitDown();
		break;
	case DIK_X:
		if (game->IsKeyDown(DIK_UP))
		{
			if (axe->axe_isAtk == 0)
			{
				Throw_Axe();
			}
			break;
		}
		else
			Hit();
		break;
	case DIK_A:
		simon->Reset();
		break;
	}
}


void CPlayScenceKeyHandler::Run(int _nx) {
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetNX(_nx);
	simon->SetState(SIMON_STATE_WALKING);
}

void CPlayScenceKeyHandler::Jump() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	DebugOut(L"isGrounded %d \n", simon->isGrounded);
	if (simon->isGrounded) {
		simon->SetState(SIMON_STATE_JUMP);
	}
}

void CPlayScenceKeyHandler::SitDown() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetState(SIMON_STATE_SIT_DOWN);
}

void CPlayScenceKeyHandler::Hit() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	CWeapon* weapon = ((CPlayScene*)scence)->weapon;
	if (simon->isDone) {
		weapon->SetState(WEAPON_STATE_ATTACK);
		simon->SetState(SIMON_STATE_HIT);
	}
	
}

void CPlayScenceKeyHandler::Throw_Axe() {
	CSimon* simon = ((CPlayScene*)scence)->player;
	CAxe* axe = ((CPlayScene*)scence)->axe;
	simon->SetState(SIMON_STATE_HIT);
	axe->UpdatePosionWithSimon(simon->GetPositionX(), simon->GetPositionY(), simon->nx);
	axe->speedy = AXE_SPEED_Y;
	axe->SetState(AXE_STATE_ATTACK);
}
void CPlayScenceKeyHandler::Throw_Knife()
{
	CSimon* simon = ((CPlayScene*)scence)->player;
	CKnife* knife = ((CPlayScene*)scence)->knife;
	simon->SetState(SIMON_STATE_HIT);
	knife->UpdatePosionWithSimon(simon->GetPositionX(), simon->GetPositionY(), simon->nx);
	knife->SetState(KNIFE_STATE_ATTACK);
}

void CPlayScenceKeyHandler::Throw_Holywater()
{
	CSimon* simon = ((CPlayScene*)scence)->player;
	CHlw* hlw = ((CPlayScene*)scence)->hlw;
	simon->SetState(SIMON_STATE_HIT);
	hlw->UpdatePosionWithSimon(simon->GetPositionX(), simon->GetPositionY(), simon->nx);
	hlw->speedy = HLW_SPEED_Y;
	hlw->SetState(HLW_STATE_ATTACK);
}