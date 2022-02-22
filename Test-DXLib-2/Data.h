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

//Data.h���֐��̊Ǘ����\�b�h
int Data();

//�f�[�^�̎擾
int Load_All_Data(Chara* c_Data, Dungeon* Dun);
//�f�[�^�̕ۑ�
int Save_All_Data();

void Draw_Status(Chara);
void Draw_Dungeon(Dungeon Dun);