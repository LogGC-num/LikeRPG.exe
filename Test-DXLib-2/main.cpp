#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"


extern int Key[256];
extern int cWhite, gFont00, gFontTitle;
extern int gFontSubTitle;
extern int cRad;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�A�v���P�[�V�����N�����̃E�B���h�E�����Ȃ�
	SetUp();

	//Chara�N���X�̃C���X�^���X����
	Chara chara;

	//�����Z�[�u�f�[�^�i�[�t�@�C�����J���Ȃ������ꍇ�A�v���������I��
	if (Data_Load(&chara) == -1) {
		DxLib_End();
		return 0;
	}

	//�Z�[�u�f�[�^�����[�h
	//�����A�Z�[�u�f�[�^���ɖ��O�����݂��Ȃ��ꍇ
	//�X�e�[�^�X�̏������Ɩ��O�̓��͂��s��
	if (chara.Load()) {
		chara.p_setName();
	}
	
	//�^�C�g���̕\��
	switch (Title()) {
		//Game.cpp�y��Game.h��
	case 0:		Game();					break;
		//Data.cpp�y��Data.h��
	case 1:		Data();					break;
		//Edit.cpp�y��Edit.h��
	case 2:		Edit();					break;
		//��X�@�\�ǉ��H
	case 3:
		//�A�v���I���A�f�[�^���i�[�������̂�switch���͔�����
	case 4:								break;
		//��O�A�A�v���������I���@�f�[�^�̕ۏ؂͂���Ȃ�
	case -1:	DxLib_End(); return 0;	break;
	}

	//�t�@�C�����J���Ȃ������狭���I��
	//�f�[�^���t�@�C���Ɋi�[
	if (Data_Save(&chara) == -1) {
		DxLib_End();
		return 0;
	}
	

	DxLib_End();
	return 0;
}