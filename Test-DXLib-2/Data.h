#pragma once
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"
#include "Data.h"

//Debug
typedef struct {
	int Floor;
	int Lv;
	int Ene_Type;
}Dungeon;

//Data.h内関数の管理メソッド
int Data();

//データの取得
int Load_All_Data(Chara* c_Data, Dungeon* Dun);
//データの保存
int Save_All_Data();

void Draw_Status(Chara);
void Draw_Dungeon(Dungeon Dun);