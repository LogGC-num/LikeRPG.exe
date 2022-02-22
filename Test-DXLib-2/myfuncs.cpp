#include<DxLib.h>
#include<conio.h>
#include"myfuncs.h"
#include "Chara.h"


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

void SetUp() {
	SetGraphMode(1280, 720, 32);
	SetWindowSize(1280, 720);
	ChangeWindowMode(TRUE), // �E�B���h�E���[�h�ɐݒ�
	DxLib_Init(),		// �c�w���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�

	cWhite = GetColor(255, 255, 255);
	cRad = GetColor(255, 0, 0);
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

int Data_Save(Chara *chara) {
	FILE* fp;
	errno_t er;
	if (0 != (er =fopen_s(&fp, "SaveData.dat", "wb"))) {
		return -1;
	}
	fprintf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name,chara->c_sta.Lv,
		chara->c_sta.ATK[0], chara->c_sta.ATK[1], chara->c_sta.ATK[2], chara->c_sta.DEF,
		chara->c_sta.HP,chara->c_sta.MP
		);

	fclose(fp);
	return 0;
}

int Data_Load(Chara *chara) {
	FILE* fp;
	errno_t er;
	if (0 != (er = fopen_s(&fp, "SaveData.dat", "rb"))) {
		return -1;
	}
	fscanf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name,256, &chara->c_sta.Lv,
		&chara->c_sta.ATK[0], &chara->c_sta.ATK[1], &chara->c_sta.ATK[2], &chara->c_sta.DEF,
		&chara->c_sta.HP, &chara->c_sta.MP
	);

	fclose(fp);
	return 0;
}