#pragma once
#include "Dxlib.h"
#include "myfuncs.h"

extern int cWhite;

//ステータスの構造体　敵味方共用
typedef struct {
	char name[256];
	int Lv;
	int HP;
	int ATK[3];
	int DEF;
	int MP;
}STATUS;

//Charaクラス　自分のクラス
class Chara
{
public:
	STATUS c_sta;
	//名前の設定(カプセル化)
	void p_setName() {
		setName(c_sta.name);
	}
	//セーブデータロード時に名前がファイルに存在しなかった場合
	//ステータスは初期化する
	int Load() {
		if (c_sta.name[0] == '\0') {
			c_sta.ATK[0] = 10;
			c_sta.ATK[1] = 10;
			c_sta.ATK[2] = 10;
			c_sta.DEF = 10;
			c_sta.HP = 100;
			c_sta.Lv = 1;
			c_sta.MP = 10;
			return 1;
		}
		else {
			return 0;
		}
	}
private:
	//名前の設定
	void setName(char name[256]) {
		bool finish = false;
		while (finish != true) {
			DrawString(100, 50, "名前を入力してください", cWhite, TRUE);
			if (KeyInputString(100, 100, 256, name, TRUE) == 1) {
				finish = true;
			}
		}
	}
};

//TODO
//武器の構造体　未完成
class Weapons {
public:
	int w_num;
	int type;
	STATUS w_sta;
};