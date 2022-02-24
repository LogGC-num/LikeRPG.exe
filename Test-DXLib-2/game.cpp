#include "game.h"
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"

#define ATTACK	0
#define ITEM	1
#define ACTION	2

extern int Key[256];
extern int gFont00;

int Game_main(Chara *chara) {
	//�Z�[�u�f�[�^�����[�h
	//�����A�Z�[�u�f�[�^���ɖ��O�����݂��Ȃ��ꍇ
	//�X�e�[�^�X�̏������Ɩ��O�̓��͂��s��
	if (chara->Load()) {
		chara->p_setName();
		Data_Save(chara);
	}

	bool _Gameover = false;
	int Command_state = 5;
	int Command_select = 0;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && _Gameover != true) {
		UI_game(*chara,Command_state,Command_select % 5);
		DrawFormatString(200, 200, cWhite, "state : %d\nselect : %d", Command_state, Command_select);
		//Debug
		if (Key[KEY_INPUT_0] % 5  == 1) {
			chara->c_sta.HP--;
		}
		//HP��0�ȉ��ɂȂ�����Q�[���I�[�o�[
		if (chara->check_status(chara)) {
			_Gameover = Gameover();
		}
		//Lv��0�ȉ��ɂȂ�Ȃ��̂ł���
		//�Ȃ����ꍇ�A�v���P�[�V�����G���[�����s
		else if (chara->check_status(chara) == -1) {
			GameError();
		}
		if (Key[KEY_INPUT_RIGHT] == 1) {
			Command_select++;
		}
		if (Key[KEY_INPUT_LEFT] == 1) {
			Command_select--;
		}
		if (Key[KEY_INPUT_RETURN] == 1) {
			//�����e�R�}���h��Back��I��������R�}���h�I���ɖ߂�
			if (Command_state != 5 && Command_select % 5 == 4) {
				Command_state = 5;
				Command_select = 0;
			}
			//�����łȂ��Ȃ�R�}���h�I�����s��
			else {
				if (Command_select <= 3) {
					Command_state = Command_select % 5;
					Command_select = 0;
				}
			}

			if (Command_state != 5 && Command_select % 5 != 4) {
				switch (Command_state)
				{
				case ATTACK:
					Game_battle_Attack(*chara,Command_select);
					break;
				case ITEM:
					break;
				case ACTION:
					break;
				default:
					break;
				}
			}
		}
		Command_select > 0 ? Command_select%=5 : Command_select = 5;		
	}

	chara->c_sta.HP = chara->c_sta.MaxHP;
	return 0;
}

void Game_battle(Chara *chara) {

}

void Game_battle_Attack(Chara chara,int select) {

}

bool Gameover() {
	DrawStringToHandle(350, 400, "GAME OVER\nPlease push Esc", cWhite, gFont00, FALSE, FALSE);
	if (Key[KEY_INPUT_ESCAPE] == 1) {
		return true;
	}
	return false;
	
}

char error_sentence[1024] = "�f�[�^�̔񐮍�������������܂����B\n�t�H���_����SaveData.dat���������A�ċN�����Ă��������B\n�����������Ȃ��ꍇ�A����҂ɘA�����Ă��������B";
void GameError() {
	DrawStringToHandle(500, 10, "Warning!!!", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(500, 100, "Application Error!!!", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(500, 120, error_sentence, cWhite, gFont00, FALSE, FALSE);

}