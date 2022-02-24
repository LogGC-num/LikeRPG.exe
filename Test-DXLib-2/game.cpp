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
	//セーブデータをロード
	//もし、セーブデータ内に名前が存在しない場合
	//ステータスの初期化と名前の入力を行う
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
		//HPが0以下になったらゲームオーバー
		if (chara->check_status(chara)) {
			_Gameover = Gameover();
		}
		//Lvは0以下にならないのでもし
		//なった場合アプリケーションエラーを実行
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
			//もし各コマンドでBackを選択したらコマンド選択に戻る
			if (Command_state != 5 && Command_select % 5 == 4) {
				Command_state = 5;
				Command_select = 0;
			}
			//そうでないならコマンド選択を行う
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

char error_sentence[1024] = "データの非整合性が発見されました。\nフォルダ内のSaveData.datを消去し、再起動してください。\nもし解決しない場合、制作者に連絡してください。";
void GameError() {
	DrawStringToHandle(500, 10, "Warning!!!", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(500, 100, "Application Error!!!", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(500, 120, error_sentence, cWhite, gFont00, FALSE, FALSE);

}