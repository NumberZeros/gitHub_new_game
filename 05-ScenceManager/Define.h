///
/// SIMON
/// 
#define SIMON_WALKING_SPEED											0.15f
#define SIMON_JUMP_SPEED_Y									0.5f
#define SIMON_JUMP_DEFLECT_SPEED									0.2f
#define SIMON_GRAVITY										0.002f
#define SIMON_DIE_DEFLECT_SPEED										0.002f

#define SIMON_ATTACK_TIME									300
#define SIMON_UNTOUCHABLE_TIME										1000
#define SIMON_RESET_JUMP_TIME								500
#define SIMON_HURT_SPEED											0.002f

#define SIMON_STATE_IDLE											0
#define SIMON_STATE_WALKING									1
#define SIMON_STATE_JUMP											2
#define SIMON_STATE_SIT_DOWN								3
#define SIMON_STATE_HIT												4
#define SIMON_STATE_SIT_HIT									5
#define SIMON_STATE_STAIR_UP										6
#define SIMON_STATE_STAIR_DOWN								7
#define SIMON_STATE_STAIR_UP_HIT									8
#define SIMON_STATE_STAIR_DOWN_HIT							9
#define SIMON_STATE_HURT											10
#define SIMON_STATE_DIE										11

#define SIMON_ANI_IDLE												0
#define SIMON_ANI_WALKING									1
#define SIMON_ANI_JUMP												2
#define SIMON_ANI_SIT_DOWN									3
#define SIMON_ANI_STAND_HIT											4
#define SIMON_ANI_SIT_HIT									5
#define SIMON_ANI_LED												6
#define SIMON_ANI_STAIR_UP									7
#define SIMON_ANI_STAIR_DOWN										8
#define SIMON_ANI_STAIR_UP_HIT								9
#define SIMON_ANI_STAIR_DOWN_HIT									10
#define SIMON_ANI_HURT										11
#define SIMON_ANI_DIE												12
#define SIMON_ANI_WHIP_LV1									13
#define SIMON_ANI_WHIP_LV2											14
#define SIMON_ANI_WHIP_LV4									15

#define SIMON_HEGHT													61
#define SIMON_WIDTH											33
#define SIMON_HEGHT_RESET_SIT										4
#define SIMON_WIDTH_RESET_ATTACK							7

///
/// WEAPON
/// 

#define WEAPON_STATE_HIDDEN											0
#define WEAPON_STATE_ATTACK									1

#define WEAPON_ATTACK_TIME											500

#define WEAPON_ANI_1										0
#define WEAPON_ANI_2												1
#define WEAPON_ANI_3										2

#define WEAPON_X													10
#define WEAPON_Y											15
#define WEAPON_WIDHT_ANI_1											44;
#define WEAPON_HEGTH_ANI_1									23;

#define WEAPON_WIDHT_ANI_3											75;

///
/// PLAY SCENE
/// 

#define SCREEN_WIDTH												512
#define SCREEN_HEIGHT										448

#define SCENE_SECTION_UNKNOWN										-1
#define SCENE_SECTION_TEXTURES								2
#define SCENE_SECTION_SPRITES										3
#define SCENE_SECTION_ANIMATIONS							4
#define SCENE_SECTION_ANIMATION_SETS								5
#define SCENE_SECTION_OBJECTS								6
#define SCENE_SECTION_LOADMAP										7

#define OBJECT_TYPE_SIMON									0
#define OBJECT_TYPE_BRICK											1
#define OBJECT_TYPE_GOOMBA									2
#define OBJECT_TYPE_KOOPAS											3
#define OBJECT_TYPE_GATE									4
#define OBJECT_TYPE_WEAPON											5
#define OBJECT_TYPE_BOARD									8
#define OBJECT_TYPE_AXE												9
#define OBJECT_TYPE_KNIFE									91
#define OBJECT_TYPE_HLW												92
#define OBJECT_TYPE_ZOMBIE									10
#define OBJECT_TYPE_BLACK_LEOPARD									11
#define OBJECT_TYPE_ITEM									12
#define OBJECT_TYPE_MERMAN											13
#define OBJECT_TYPE_BOSS									15
#define OBJECT_TYPE_STAIR											14
#define OBJECT_TYPE_HEALTHBAR								16				
#define OBJECT_TYPE_TIMER											17	

#define OBJECT_TYPE_PORTAL											50

//ITEM MAP ENTRANCE
#define ID_ITEM_TYPE_GOODS									0
#define ID_ITEM_TYPE_TORCH											1
#define ID_ITEM_TYPE_CANDLE									2
#define ID_ITEM_TYPE_CHAIN									3 
#define ID_ITEM_TYPE_BIGHEART										4
#define ID_ITEM_TYPE_KNIFE									5
#define ID_ITEM_TYPE_EFFECTFIRE										6



#define MAX_SCENE_LINE												1024


///
/// ZOMBIE
/// 

#define ZOMBIE_WALKING_SPEED_X								0.13f
#define ZOMBIE_WALKING_SPEED_Y										0.2f
#define ZOMBIE_GRAVITY										0.001f
#define ZOMBIE_DEAD											1
#define ZOMBIE_BBOX_WIDTH											32
#define ZOMBIE_BBOX_HEIGHT									64
#define ZOMBIE_WALKING												0

#define BLACK_LEOPARD_IDLE									0  
#define BLACK_LEOPARD_RUN											1
#define BLACK_LEOPARD_ANI_JUMP								2
#define BLACK_LEOPARD_DESTROYED										3

#define BLACK_LEOPARD_RUNNING_SPEED_X						0.15f
#define BLACK_LEOPARD_RUNNING_SPEED_Y								0.2f
#define BLACK_LEOPARD_GRAVITY								0.001f

#define BLACK_LEOPARD_BBOX_WIDTH									64
#define BLACK_LEOPARD_BBOX_HEIGHT							32
#define BLACK_LEOPARD_BBOX_HEIGHT_DIE								64

///
/// MERMAN
/// 

#define MERMAN_JUMP_SPEED_Y											0.9f
#define MERMAN_WALKING_SPEED_X								0.13f
#define MERMAN_GRAVITY												0.002f

#define MERMAN_BBOX_WIDTH											32
#define MERMAN_BBOX_HEIGHT									64

#define MERMAN_JUMP											1
#define MERMAN_WALKING												2
#define MERMAN_SHOOT_FIREBALL								3

#define MERMAN_ANI_IDLE												0
#define MERMAN_ANI_WALKING									1
#define MERMAN_ANI_SHOOT_FIREBALL									2

///
/// ITEM
/// 




/// map
#define SCENE_1														1
#define SCENE_2												2
#define SCENE_1_ROW													10
#define SCENE_1_COL											48
#define SCENE_1_ROW_READ											4
#define SCENE_1_COL_READ									17
#define SCENE_2_ROW													12
#define SCENE_2_COL											17
#define SCENE_2_ROW_READ											4
#define SCENE_2_COL_READ									7

#define TILE_WIDTH													32
#define TILE_HEIGHT											32

#define MAX_SCENE_LINE												1024
#define map2												2484
#define map3														6000
#define map6												12000
#define map4														8000

#define max_row												100
#define max_col														100

// gate
#define gate_box_width										32
#define gate_box_height												50