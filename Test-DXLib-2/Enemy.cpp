#include "Dxlib.h"
#include "myfuncs.h"
#include "Chara.h"

#define CAN_SETTING_NUM 2

char Enemy_type[16][64] = {
	{"slime"},
	{"goblin"},
	{"dragon"},
	{"witch"},
	{"metal"},
	{"boss"},
};

char enemy_name_type[8][8][64] = {
	//slime
	{
		"normal slime",
		"rare   slime",
		"great  slime",
	},
	//goblin
	{
		"agent ancient goblin",
		"hell  frame   goblin",
		"metabolic pop goblin",
	},
	//drangon
	{
		"ultimate    dragon",
		"nonplayable dragon",
		"domestic na dragon",
	},
	//witch
	{
		"physics   witch",
		"magical   witch",
		"fullpower witch"
	},
	//metal
	{
		"rare   metal",
		"stray  metal",
		"liquid metal",
	},
	//boss
	{
		"boss",
		"bosser",
		"bossest"
	},
};

char enemy_atk_type[8][8][64] = {
	//slime
	{
		"tackle",
		"tackle",
		"tackle",
	},
	//goblin
	{
		"tackle",
		"panch"
		"kick",
	},
	//drangon
	{
		"tackle",
		"breath",
		"fire",
	},
	//witch
	{
		"poison",
		"magical attack",
		"healing"
	},
	//metal
	{
		"tackle",
		"be firmly",
		"tackle",
	},
	//boss
	{
		"hardest panch",
		"gradest kick",
		"highper tackle"
	},
};

typedef struct TYPE_DIF {
	int ATK[3];
	double p_ATK[3];
	int HP;
	double p_HP;
	int DEF;
	double p_DEF;
}_TYPE_DIF;

//各種の個体値（倍率）及び　初期値ステータス
TYPE_DIF type_dif[8] = {
	{10,10,10,0.25,0.5,0.8,150,0.5,10,0.2},
	{15,15,15,0.25,0.5,0.6,250,0.2,15,0.2},
	{25,10,10,0.25,0.5,1.1,350,0.2,20,0.3},
	{5,5,10,0.5,0.5,0.5,150,0.2,50,0.5},
	{1,1,1,0.5,0.5,0.5,10,0.2,500,2},
	{50,35,35,1.1,1.1,1.1,500,0.8,100,0.6},
};

int name_num;
int name_length;
void Chara::set_enemy_status(Dungeon* dun, Chara* ene) {
	name_length = 0;
	name_num = GetRand(CAN_SETTING_NUM);
	while (enemy_name_type[dun->Ene_Type][name_num][name_length] != '\0') {
		ene->c_sta.name[name_length] = enemy_name_type[dun->Ene_Type][name_num][name_length];
		ene->c_sta.name[name_length + 1] = '\0';
		name_length++;
	}
	ene->c_sta.Lv = dun->Lv;
	ene->c_sta.ATK[0] = static_cast<int>(type_dif[dun->Ene_Type].ATK[0] * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_ATK[0]));
	ene->c_sta.ATK[1] = static_cast<int>(type_dif[dun->Ene_Type].ATK[1] * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_ATK[1]));
	ene->c_sta.ATK[2] = static_cast<int>(type_dif[dun->Ene_Type].ATK[2] * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_ATK[2]));
	ene->c_sta.HP = static_cast<int>(type_dif[dun->Ene_Type].HP * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_HP));
	ene->c_sta.MaxHP = static_cast<int>(type_dif[dun->Ene_Type].HP * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_HP));
	ene->c_sta.DEF = static_cast<int>(type_dif[dun->Ene_Type].DEF * (dun->Lv) * (1 + type_dif[dun->Ene_Type].p_DEF));
	ene->c_sta.MP = 9999;
}
int enemy_attack_type;
void Chara::enemy_attack(int* ene_at, Chara* chara, Chara* enemy) {
	enemy_attack_type = GetRand(2);
	switch (enemy_attack_type) {
	case 0:
		if (enemy->c_sta.ATK[0] - chara->c_sta.DEF > 0) {
			chara->c_sta.HP -= enemy->c_sta.ATK[0] - chara->c_sta.DEF;
		}
		break;
	case 1:
		if (enemy->c_sta.ATK[1] - chara->c_sta.DEF > 0) {
			chara->c_sta.HP -= enemy->c_sta.ATK[1] - chara->c_sta.DEF;
		}
		break;
	case 2:
		if (enemy->c_sta.ATK[2] - chara->c_sta.DEF > 0) {
			chara->c_sta.HP -= enemy->c_sta.ATK[2] - chara->c_sta.DEF;
		}

		break;
	default:
		break;
	}
}