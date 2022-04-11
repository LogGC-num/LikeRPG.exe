#include <DxLib.h>
#include <conio.h>
#include "myfuncs.h"
#include "Chara.h"
#include "UI.h"

static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 61;	//���ς����T���v����
static const int FPS = 65;	//�ݒ肵��FPS
int Key[256];
int cWhite;
int gFont00;
int gFontTitle;
int gFontSubTitle;
int cRad;
int cOrange;


//�A�v���P�[�V�������̂̐ݒ蓙
void SetUp() {
	SetGraphMode(1280, 720, 32);
	SetWindowSize(WINDOW_SIZE_Bes,WINDOW_SIZE_Ver);
	ChangeWindowMode(TRUE), // �E�B���h�E���[�h�ɐݒ�
	DxLib_Init(),		// �c�w���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	cWhite = GetColor(255, 255, 255);
	cRad = GetColor(255, 0, 0);
	cOrange = GetColor(240, 128, 128);
	gFont00 = CreateFontToHandle("���C���I", 25, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	gFontTitle = CreateFontToHandle("���C���I", 100, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	gFontSubTitle = CreateFontToHandle("���C���I", 75, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

}


bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	DrawFormatString(1200, 700, GetColor(255, 255, 255), "%.1ffps", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

void NowLoading(int font) {
	DrawStringToHandle(1000, 625, "Now Loading!!", GetColor(255, 255, 255), font);
}

int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

//�t�@�C������
int Data_Save(Chara *chara) {
	//�t�@�C���N���X�̃|�C���^�𐶐�
	FILE* fp;
	//�Z�L�����e�B�[����fopen_s�ł͕Ԃ�l��errno_t�Ő錾����Ă���
	errno_t er;
	//�����t�@�C�����J���Ȃ��������O��ԋp�Amain()���ŃA�v���������I��
	if ((er = fopen_s(&fp, "SaveData.dat", "wb")) != 0 || fp == 0) {
		return -1;
	}
	//Chara�N���X�̃X�e�[�^�X��S���i�[
	fprintf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name, chara->c_sta.Lv,
		chara->c_sta.ATK[0], chara->c_sta.ATK[1], chara->c_sta.ATK[2], chara->c_sta.DEF,
		chara->c_sta.HP, chara->c_sta.MaxHP, chara->c_sta.MP
	);
	//�t�@�C�������
	fclose(fp);
	return 0;
}

int Data_Load(Chara *chara) {
	//Data_Save()�Ɠ���
	FILE* fp;
	errno_t er;
	if ((er = fopen_s(&fp, "SaveData.dat", "rb")) != 0 || fp == 0) {
		return -1;
	}
	//�Z�L�����e�B�[����fscanf_s�ł͕�������擾����ꍇ�A���̈���̈����͍ő�o�b�t�@�ɂȂ�
	//Chara�N���X�̃X�e�[�^�X��S���擾
	fscanf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name, 256, &chara->c_sta.Lv,
		&chara->c_sta.ATK[0], &chara->c_sta.ATK[1], &chara->c_sta.ATK[2], &chara->c_sta.DEF,
		&chara->c_sta.HP, &chara->c_sta.MaxHP, &chara->c_sta.MP
	);
	//�t�@�C�������
	fclose(fp);
	return 0;
}

//�^�C�g��
int Title() {
	//UI.h�y��UI.cpp��UI_Title()�̈���
	int select = 0;
	//�����̓L�[���͂𔺂����߃��[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		//�L�[����
		//���ŉ��ց@���ŏ�ց@Enter�Ō���
		if (Key[KEY_INPUT_DOWN] % 10 == 1 || Key[KEY_INPUT_DOWN] > 60) {
			select++;
		}
		if (Key[KEY_INPUT_UP] % 10 == 1 || Key[KEY_INPUT_UP] > 60) {
			select--;
		}
		//select�͕��ɂȂ�\��������̂Ő��ɂ���
		select > 0 ? select : select += 5;
		if (Key[KEY_INPUT_RETURN] == 1) {
			return (select % 5);
		}
		UI_title(select % 5);
	}

	//��������ɏI�������ꍇEnter�ł�if�����ŏI�����邽�߃G���[�̕Ԃ�l��-1�ɂȂ�
	return -1;
}

int Data_Save_D(Dungeon *dun) {
	//�t�@�C���N���X�̃|�C���^�𐶐�
	FILE* fp;
	//�Z�L�����e�B�[����fopen_s�ł͕Ԃ�l��errno_t�Ő錾����Ă���
	errno_t er;
	//�����t�@�C�����J���Ȃ��������O��ԋp�Amain()���ŃA�v���������I��
	if ((er = fopen_s(&fp, "DataDungeon.dat", "wb")) != 0 || fp == 0) {
		return -1;
	}
	//Chara�N���X�̃X�e�[�^�X��S���i�[
	fprintf_s(fp, "%d\n%d\n%d\n", dun->Floor,dun->Lv,dun->Ene_Type);
	//�t�@�C�������
	fclose(fp);
	return 0;
}