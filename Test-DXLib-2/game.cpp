#include "game.h"
#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"
#include "Data.h"

#define ATTACK	0
#define ITEM	1
#define ACTION	2

extern int Key[256];
extern int gFont00;

void Clear();

int Game_main(Chara *chara,Dungeon *d_ene) {
	//セーブデータをロード
	//もし、セーブデータ内に名前が存在しない場合
	//ステータスの初期化と名前の入力を行う
	if (chara->Load()) {
		chara->p_setName();
		Data_Save(chara);
	}
	Chara enemy;
	enemy.Load();
	enemy.set_enemy_status(d_ene,&enemy);

	bool _Gameover = false;
	int Command_state = -1;
	int Command_select = 0;
	int my_act = 0;
	int ene_at = 0;
	//0->chara 1->enemy
	int turn = 0;
	int counter = 0;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && _Gameover != true) {
		UI_game(*chara,Command_state,Command_select % 5);
		UI_game_enemy_status(enemy);
		DrawFormatString(200, 200, cWhite, "state : %d\nselect : %d", Command_state, Command_select);
		DrawFormatString(200, 250, cWhite, "turn : %d", turn);
		DrawFormatString(200, 300, cWhite, "type : %d", d_ene->Ene_Type);

		//Debug
		if (Key[KEY_INPUT_0] % 5  == 1) {
			chara->c_sta.HP--;
		}
		if (Key[KEY_INPUT_1] % 5 == 1) {
			enemy.c_sta.HP--;
		}
		//HPが0以下になったらゲームオーバー
		if (chara->check_status(chara )|| turn == -1) {
			turn = -1;
			_Gameover = Gameover();
		}
		if (enemy.check_status(&enemy) || turn == -2) {
			turn = -2;
			Clear();
			if (counter == 0) {
				d_ene->Ene_Type = GetRand(5);
				d_ene->Floor++;
				d_ene->Lv += GetRand(2);
				if (Data_Save_D(d_ene) == -1) {
					DxLib_End();
					return 0;
				}
				counter++;
			}
		}
		//Lvは0以下にならないのでもし
		//なった場合アプリケーションエラーを実行
		else if (chara->check_status(chara) == -1) {
			GameError();
		}

		if (turn == 0) {
			chara->Command(&Command_select, &Command_state, chara, &enemy,&turn,&my_act);
		}
		else if(turn == 1){
			enemy.enemy_attack(&ene_at,chara, &enemy);
			turn = 0;
		}
		else {
			if (Key[KEY_INPUT_ESCAPE]) {
				break;
			}
		}
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

void Clear() {
	DrawStringToHandle(500, 10, "CLEAR!!", cWhite, gFont00, FALSE, FALSE);
}