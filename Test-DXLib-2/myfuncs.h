#pragma once
#include "DxLib.h"
#include "Chara.h"
class Chara;
#define DIFFICULT 5

extern void SetUp();
extern bool Update();
extern void Draw();
extern void Wait();
extern void NowLoading(int);
extern int gpUpdateKey();
int Data_Save(Chara*);
int Data_Load(Chara*);