#pragma once
#include "DxLib.h"
#include "Chara.h"
class Chara;
#define DIFFICULT 5
#define WINDOW_SIZE_Bes 1280
#define WINDOW_SIZE_Ver 720

//アプリケーション自体の設定等
void SetUp();
bool Update();
void Draw();
void Wait();
void NowLoading(int);
int gpUpdateKey();

//タイトル
int Title();
//以下Esc()までDegug
void Game();

void Data();

void Edit();

void Esc();

//ファイル処理
int Data_Save(Chara*);
int Data_Load(Chara*);

