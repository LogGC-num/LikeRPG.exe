#pragma once
#include "DxLib.h"
#include "Chara.h"
class Chara;
#define DIFFICULT 5
#define WINDOW_SIZE_Bes 1280
#define WINDOW_SIZE_Ver 720

//�A�v���P�[�V�������̂̐ݒ蓙
void SetUp();
bool Update();
void Draw();
void Wait();
void NowLoading(int);
int gpUpdateKey();

//�^�C�g��
int Title();
//�ȉ�Esc()�܂�Degug
void Game();

void Data();

void Edit();

void Esc();

//�t�@�C������
int Data_Save(Chara*);
int Data_Load(Chara*);

