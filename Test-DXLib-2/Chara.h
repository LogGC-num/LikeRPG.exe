#pragma once
#include "Dxlib.h"
#include "myfuncs.h"

extern int cWhite;
//extern int cOrange;

//ステータスの構造体　敵味方共用
typedef struct _STATUS{
	char name[256];
	int Lv;
	int HP;
	int MaxHP;
	int ATK[3];
	int DEF;
	int MP;
}STATUS;


//ダンジョンのデータ
typedef struct Dungeon {
	int Floor;
	int Lv;
	int Ene_Type;
}_Dungeon;

//Charaクラス　自分のクラス
class Chara
{
public:
	STATUS c_sta;
	//名前の設定(カプセル化)
	void p_setName() {
		setName(c_sta.name);
	}
	void set_enemy_status(Dungeon*,Chara*);

	int check_status(Chara*);

	//セーブデータロード時に名前がファイルに存在しなかった場合
	//ステータスは初期化する
	int Load() {
		if (c_sta.name[0] == '\0') {
			c_sta.ATK[0] = 10;
			c_sta.ATK[1] = 10;
			c_sta.ATK[2] = 10;
			c_sta.DEF = 10;
			c_sta.HP = 100;
			c_sta.MaxHP = 100;
			c_sta.Lv = 1;
			c_sta.MP = 10;
			return 1;
		}
		else {
			return 0;
		}
	}

	void Command(int*,int*,Chara* chara, Chara* enemy,int*,int*);
	void ATK(int select,Chara *chara,Chara *enemy);
	void ATK_01(Chara* chara, Chara* enemy);
	void ATK_02(Chara* chara, Chara* enemy);
	void Item(int select, Chara* chara, Chara* enemy);
	void Item_01(Chara* chara, Chara* enemy);
	void Item_02(Chara* chara, Chara* enemy);
	void Action(int select, Chara* chara, Chara* enemy);
	void Action_01(Chara* chara, Chara* enemy);
	void Action_02(Chara* chara, Chara* enemy);
	void enemy_attack(int *ene_at,Chara* chara, Chara* enemy);

	//void Dun_to_Data(Dungeon*, Chara*);
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

typedef struct _Enemy_infomation {
	char name[256];
	int type;
}Enemy_infomation;