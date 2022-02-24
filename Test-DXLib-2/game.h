#pragma once
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"

int Game_main(Chara*);
bool Gameover();
void GameError();

void Game_battle(Chara*);
void Game_battle_Attack(Chara chara,int select);