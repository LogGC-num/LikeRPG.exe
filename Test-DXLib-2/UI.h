#pragma once
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"

void UI_title(int);
void UI_game(Chara,int,int);
void UI_game_chara_status(Chara chara);
void UI_game_enemy_status(Chara enemy);

//�R�}���h�I������UI
//state : 0 -> Attack , 1 -> Item , 2 -> Action , 3,4,,5 -> �R�}���h�I��
int UI_game_command(int state,int select);


int UI_game_command_Attack(int select);
int UI_game_command_Item(int select);
int UI_game_command_Action(int select);