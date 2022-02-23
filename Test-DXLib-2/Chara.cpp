#include "Chara.h"

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