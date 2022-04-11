#pragma once
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "Data.h"

int Game_main(Chara*,Dungeon*);
bool Gameover();
void GameError();

void Game_battle(Chara*);
void Game_battle_Attack(Chara chara,int select);