#include <iostream>
#include <fstream>
#include "Intro.h"

#include "PlayScence.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

// load intro

void CPlayScene::LoadIntro()
{
	isintro = true;
	LoadObject();
	LoadMapItro();
}

void CPlayScene::LoadMapItro()
{
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


		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }


		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_SCENEOBJECT(line); break;
		}
	}
	f.close();
}

void CPlayScene::Load()
{
	CGame* game = CGame::GetInstance();

	if (game->current_scene == 4 && player)
		player->StartMap4();
	isIntro = false;
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
	int id_item = 0;
	int secondGood = 12;
	int id_fireball = 14;
	int fireball = 4;

	int id_brick = 1;
	int x_brick = 1;
	float lenghtStair = 0.0f;
	float min, max;
	int ybat;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_INTRO_MAP:
		obj = new Intro();
		break;
	case OBJECT_TYPE_SIMON:
		if (!player)
		{
			obj = new CSimon(x, y);
			player = (CSimon*)obj;
			player->SetState(SIMON_STATE_WALKING);
			
			if (isintro) {
				player->nx = -1;
				player->isAutoMove = true;
			}
			DebugOut(L"[INFO] Player object created!\n");
		}
		else {
			obj = player;
			player->nx = 1;
			player->isAutoMove = false;
		}
		break;
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		brick = (CBrick*)obj;
		id_brick = atof(tokens[4].c_str());
		x_brick = atof(tokens[5].c_str());
		lenghtStair = atof(tokens[6].c_str());
		brick->lenghtStair = lenghtStair;
		if (id_brick == OBJECT_TYPE_BRICK_ULR) {  // 111
			brick->type = BRICK_TYPE_ULR;
			brick->brick_x = x_brick;
		}
		else if (id_brick == OBJECT_TYPE_BRICK_URL) { // 112
			brick->type = BRICK_TYPE_URL;
			brick->brick_x = x_brick;
		}
		else if (id_brick == OBJECT_TYPE_BRICK_DLR) { // 113
			brick->type = BRICK_TYPE_DLR;
			brick->brick_x = x_brick;
		}
		else if (id_brick == OBJECT_TYPE_BRICK_DRL) { // 114
			brick->type = BRICK_TYPE_DRL;
			brick->brick_x = x_brick;
		}
		else 
			brick->type = id_brick;
		break;
	case OBJECT_TYPE_ZOMBIE:
		min = atof(tokens[4].c_str());
		max = atof(tokens[5].c_str());
		obj = new CZombie();
		zombie = (CZombie*)obj;
		zombie->min = min;
		zombie->max = max;
		break;
	case OBJECT_TYPE_BLACK_LEOPARD: 
		obj = new CBlackLeopard(); 
		black = (CBlackLeopard*)obj;
		break;
	case OBJECT_TYPE_BLACK_LEOPARD_2:
		obj = new CBlackLeopard();
		black_2 = (CBlackLeopard*)obj;
		break;
	case OBJECT_TYPE_MERMAN:
		srand(time(NULL));
		obj = new CMerman();
		merman = (CMerman*)obj;
		merman->SetState(MERMAN_JUMP);
		//merman->x = rand() % (150 - 10 + 1) + 10;
		merman->nx = rand() % (1 - (-1) + 1) - 1;
		break;
	case OBJECT_TYPE_FB:
		obj = new CFB();
		this->fb = (CFB*)obj;
		break;
	case OBJECT_TYPE_VAMPIREBAT:
		ybat = atof(tokens[2].c_str());
		min = atof(tokens[4].c_str());
		max = atof(tokens[5].c_str());
		obj = new CVampireBat();
		vampirebat = (CVampireBat*)obj;
		vampirebat->min = min;
		vampirebat->ybat = ybat;
		vampirebat->max = max;
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
	case OBJECT_TYPE_SUBW:
		obj = new SubW();
		subw = (SubW*)obj;
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
		id_item = atof(tokens[4].c_str());
		secondGood = atof(tokens[5].c_str());
		obj = new CItem();
		item = (CItem*)obj;
		if (id_item == ID_ITEM_TYPE_TORCH) { // 1
			item->SetID(ITEM_ANI_TORCH);
			item->SetState(ITEM_STATE_SHOW);
			item->secondGood = secondGood;
		}
		else if (id_item == ID_ITEM_TYPE_CANDLE) {
			item->SetID(ITEM_ANI_CANDLE);
			item->SetState(ITEM_STATE_SHOW);
			item->secondGood = secondGood;
		}
		else if (id_item == ID_ITEM_TYPE_BRICK) {
			item->SetID(ITEM_ANI_BRICK);
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
	if (boss != NULL) {
		healthbar->hpboss = boss->boss_HP;
	}

	//Map intro 
	/*if (isIntro) {
		player->x += player->dx;
	}*/
	timer->Update();
	healthbar->hp = player->simon_HP;
	score->score = player->simon_Score;
	score->mana = player->simon_Mana;
	score->point = player->simon_P;
	subw->subw = player->simon_Sub;
	score->stage = player->simon_stage;
	if (boss != NULL)
		healthbar->hpboss = boss->boss_HP;
	

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
	if (game->current_scene == 4 && player->y >= 350)
	{
		player->SetState(SIMON_STATE_DIE);
		if (GetTickCount() - player->action_time > 3000)
		{
			ResetMap();
			CGame::GetInstance()->SwitchScene(game->current_scene);
		}
	};

	if (boss) {
		
		if (boss->isAttack) {
			boss->Update(player, dt);
		}
		else {
			if (boss->x - player->x < 50) {
				boss->SetState(BOX_ATTACK);
			}
		}
	}
	if (merman)
	{
		if (merman->isAttack)
		{
			if (fb->fb_isAtk == false)
			fb->Attack(merman->x, merman->y + 15, merman->nx,3500);
			//fb->
			//fb->speedy = AXE_SPEED_Y;
		}
	}
	if (black)
	{
		if (black->x - player->x < 150)
		{
			black->SetState(BLACK_LEOPARD_RUN);
		}
	}

	if (black_2)
	{
		if (black_2->x - player->x < 150)
		{
			black_2->SetState(BLACK_LEOPARD_RUN);
		}
	}

	if (player->isEndGame)
	{
		timer->isStop = true;
		if (timer->timeremain != 1)
		{
			if (GetTickCount() - score->action_time_score > 50)
			{
				//	DebugOut(L"time: %d \f", GetTickCount() - action_time);
				player->simon_Score += 1;
				score->action_time_score = GetTickCount();
			}
		}
		if (player->simon_Mana > 0)
		{
			if (GetTickCount() - score->action_time_score > 50)
			{
				//	DebugOut(L"time: %d \f", GetTickCount() - action_time);
				player->simon_Score += 1;
				player->simon_Mana -= 1;
				score->action_time_score = GetTickCount();
			}
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
	score->SetPosition(cx, 0);
	subw->SetPosition(cx, 0);
}

void CPlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	if(tilemap)
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

	if (simon->GetState() == SIMON_STATE_DIE || simon->isAutoMove) return;

	if (game->IsKeyDown(DIK_RIGHT)) {
		if (!simon->isOnStair) 
			Run(1);
	}		
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (!simon->isOnStair)
			Run(-1);
	}	
	else if (game->IsKeyDown(DIK_UP))
	{
		if (simon->simon_stair_type == 0) return;
		if (simon->simon_stair_type == 1) {
			CGame::GetInstance()->SwitchScene(game->current_scene + 1);
			simon->simon_stage += 1;
		}
		if (simon->simon_stair_type == BRICK_TYPE_ULR)
			simon->nx = 1;
		else if (simon->simon_stair_type == BRICK_TYPE_URL)
			simon->nx = -1;
		if (simon->simon_stair_type == BRICK_TYPE_DLR && simon->isOnStair == true)
			simon->nx = -1;
		else if (simon->simon_stair_type == BRICK_TYPE_DRL && simon->isOnStair == true)
			simon->nx = -1;
		if(simon->startStair == 0)
			simon->startStair = simon->x;
		if (simon->startStair != simon->x) {
			if (simon->nx < 0) {
				if (simon->startStair - simon->x > simon->lenghtStair)
					simon->ResetStair();
				else
					simon->SetState(SIMON_STATE_STAIR_UP);
			}
			else {
				if (simon->x - simon->startStair > simon->lenghtStair)
					simon->ResetStair();
				else
					simon->SetState(SIMON_STATE_STAIR_UP);
			}
		}
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->simon_stair_type == 0) return;
		if (simon->simon_stair_type == 1) {
			CGame::GetInstance()->SwitchScene(game->current_scene + 1);
			simon->simon_stage += 1;
		}
		else if (simon->simon_stair_type == BRICK_TYPE_DLR)
			simon->nx = 1;
		else if (simon->simon_stair_type == BRICK_TYPE_DRL)
			simon->nx = -1;
		/*if (simon->simon_stair_type == BRICK_TYPE_ULR && simon->isOnStair == true)
			simon->nx = -1;
		else if (simon->simon_stair_type == BRICK_TYPE_URL && simon->isOnStair == true)
			simon->nx = 1;*/
		if (simon->startStair == 0)
			simon->startStair = simon->x;


		if (simon->startStair != simon->x) {
			if (simon->nx < 0) {
				if (simon->startStair - simon->x < simon->lenghtStair)
					simon->ResetStair();
				else
					simon->SetState(SIMON_STATE_STAIR_DOWN);
			}
			else {
				if (simon->x - simon->startStair > simon->lenghtStair)
					simon->ResetStair();
				else
					simon->SetState(SIMON_STATE_STAIR_DOWN);
			}
		}
	}
	else if (simon->isOnStair)
	{
		simon->isStairUp = false;
		simon->isStairDown = false;
	}
	else 
		simon->SetState(SIMON_STATE_IDLE);
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	if (game->IsKeyRelease(DIK_DOWN))
		SitDown();
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->player;
	CAxe* axe = ((CPlayScene*)scence)->axe;
	CKnife* knife = ((CPlayScene*)scence)->knife;
	CHlw* hlw = ((CPlayScene*)scence)->hlw;
	CPlayScene* playscene = ((CPlayScene*)scence);
	CBrick* brick = ((CPlayScene*)scence)->brick;
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->isOnStair)
			return;
		else 
		Jump();
		break;
	case DIK_DOWN:
		SitDown();
		break;
	case DIK_X:
		if (simon->isDoneAttack)
		{
			if (game->IsKeyDown(DIK_UP))
			{
				if (axe->axe_isAtk != 0 || simon->simon_Mana < 0) return;
				if (simon->simon_Mana > 0) {
					if (simon->simon_Sub == 0)
						Throw_Knife();
					else if (simon->simon_Sub == 1)
						Throw_Holywater();
					else if (simon->simon_Sub == 2)
						Throw_Axe();
					simon->simon_Mana -= 1;
				}
				break;
			}
			else
				Hit();
		}
		break;
	case DIK_A:
		simon->Reset();
		break;
	}
}


void CPlayScenceKeyHandler::Run(int _nx) {
	CSimon* simon = ((CPlayScene*)scence)->player;
	if (simon->isDone) 
	{
		simon->SetNX(_nx);
		simon->SetState(SIMON_STATE_WALKING);
	}
}

void CPlayScenceKeyHandler::StairUp()
{
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetState(SIMON_STATE_STAIR_UP);

}
void CPlayScenceKeyHandler::StairDown()
{
	CSimon* simon = ((CPlayScene*)scence)->player;
	simon->SetState(SIMON_STATE_STAIR_DOWN);

}

void CPlayScenceKeyHandler::AutoWalk(int des) {
	CSimon* simon = ((CPlayScene*)scence)->player;
	if (des - simon->x != 0)
	{
		if (des - simon->x > 0)
		{
			Run(1);
		}
		else if (des - simon->x < 0)
		{
			Run(-1);
		}
	}
	else simon->SetState(SIMON_STATE_IDLE);
}
void CPlayScenceKeyHandler::Jump() {
	CSimon* simon = ((CPlayScene*)scence)->player;
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