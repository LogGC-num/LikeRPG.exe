#include "game.h"
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"

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

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && _Gameover != true) {
		UI_game(*chara);
		if (Key[KEY_INPUT_0] % 5  == 1) {
			chara->c_sta.HP--;
		}
		if (chara->check_status(chara)) {
			_Gameover = Gameover();
		}
		else if (chara->check_status(chara) == -1) {
			GameError();
		}

		
		
	}

	chara->c_sta.HP = chara->c_sta.MaxHP;
	return 0;
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