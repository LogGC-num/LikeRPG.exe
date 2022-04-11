#include "Chara.h"
#include "myfuncs.h"

extern int Key[256];

int Chara::check_status(Chara *chara) {
	if (chara->c_sta.HP <= 0) {
		chara->c_sta.HP = 0;
		return 1;
	}
	if (chara->c_sta.Lv <= 0) {
		return -1;
	}
	return 0;
}

void Chara::Command(int* select, int* state, Chara* chara, Chara* enemy, int* turn, int *my_act) {
	if (Key[KEY_INPUT_RIGHT] % 10 == 1) {
		++*select;
	}
	if (Key[KEY_INPUT_LEFT] % 10 == 1) {
		--*select;
	}
	if (*select < 0) {
		*select += 5;
	}
	*select %= 5;
	if (Key[KEY_INPUT_RETURN] == 1) {
		if(*state == -1){
			*state = *select;
			*select = 0;
		}
		else {
			switch (*state){
				case 0:
					chara->ATK(*select, chara, enemy);
					break;
				case 1:
					chara->Item(*select, chara, enemy);
					break;
				case 2:
					chara->Action(*select, chara, enemy);
					break;
			default:
				break;
			}
			*select = 0;
			*state = -1;
			*turn = 1;
		}
	}
}

void Chara::ATK(int select, Chara* chara, Chara* enemy) {
	switch (select)
	{
	case 0:
		ATK_01(chara,enemy);
		break;
	case 1:
		ATK_02(chara,enemy);
		break;
	default:
		break;
	}
}
void Chara::ATK_01(Chara* chara, Chara* enemy) {
	//debug
	enemy->c_sta.HP -= 100;
	if (chara->c_sta.ATK[0] - enemy->c_sta.DEF > 0) {
		enemy->c_sta.HP -= chara->c_sta.ATK[0] - enemy->c_sta.DEF;
	}
	else {

	}

}
void Chara::ATK_02(Chara* chara, Chara* enemy) {
	//debug
	enemy->c_sta.HP -= 150;
	if (chara->c_sta.ATK[0] - enemy->c_sta.DEF > 0) {
		enemy->c_sta.HP -= chara->c_sta.ATK[0] - enemy->c_sta.DEF;
	}
	else {
	}
}

void Chara::Item(int select, Chara* chara, Chara* enemy){
	switch (select)
	{
	case 0:
		Item_01(chara, enemy);
		break;
	case 1:
		Item_02(chara, enemy);
		break;
	default:
		break;
	}
}
void Chara::Item_01(Chara* chara, Chara* enemy){
	if (chara->c_sta.HP >= chara->c_sta.MaxHP * 0.8) {
		chara->c_sta.HP = chara->c_sta.MaxHP;
	}
	else {
		chara->c_sta.HP += static_cast<int>(chara->c_sta.MaxHP * 0.2);
	}
}
void Chara::Item_02(Chara* chara, Chara* enemy){
	chara->c_sta.MP += 5;
}
void Chara::Action(int select, Chara* chara, Chara* enemy){
	switch (select)
	{
	case 0:
		Action_01(chara, enemy);
		break;
	case 1:
		Action_02(chara, enemy);
		break;
	default:
		break;
	}
}
void Chara::Action_01(Chara* chara, Chara* enemy){

}
void Chara::Action_02(Chara* chara, Chara* enemy){

}

