#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"

extern int gFontTitle;
extern int gFont00;

//タイトルに用いる構造体
typedef struct _TITLE {
	int x, y;
	char choice[64];
}TITLE;

//構造体TITLEの初期化
TITLE s_title[5] = {
	{WINDOW_SIZE_Bes / 2     ,WINDOW_SIZE_Ver / 2	   ,"U GAME START"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 30 ,"U CHECK DATA"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 60 ,"EDIT SETTING"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 90 ,""},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 120,"ESC FM HERE?"},
};


//ゲームタイトルのUI
//引数はmyfunc.h及びmyfunv.cppのTitle()記載
void UI_title(int select) {	
	//TODO バージョンアップ
	DrawString(10, WINDOW_SIZE_Ver - 20, "ver.0.0.0,β", cWhite, FALSE);
	//ゲームタイトル表示
	DrawFormatStringToHandle(WINDOW_SIZE_Bes / 4, WINDOW_SIZE_Ver / 4, cWhite, gFontTitle, "LikeRPG.exe");
	for (int i = 0; i < 5; i++) {
		if (i == select) {
			s_title[i].x = WINDOW_SIZE_Bes / 2; 
		}
		else {
			s_title[i].x = WINDOW_SIZE_Bes / 2 + 20; 
		}
		if (i == 0 || i == 2) {
			DrawFormatStringToHandle(s_title[i].x - 200, s_title[i].y, cWhite, gFont00, "developing...");
		}
		DrawFormatStringToHandle(s_title[i].x, s_title[i].y, cWhite, gFont00, s_title[i].choice);
	}
}

void UI_game(Chara chara) {
	//テキストボックスの表示
	//上部
	DrawBox(10, 10, WINDOW_SIZE_Bes - 10, 150, cWhite, FALSE);
	//左部
	DrawBox(10, 160, WINDOW_SIZE_Bes / 4, WINDOW_SIZE_Ver - 160, cWhite, FALSE);
	//右部
	DrawBox(WINDOW_SIZE_Bes - WINDOW_SIZE_Bes / 4, 160, WINDOW_SIZE_Bes - 10, WINDOW_SIZE_Ver - 160, cWhite, FALSE);
	//下部
	DrawBox(10, WINDOW_SIZE_Ver-150, WINDOW_SIZE_Bes-10, WINDOW_SIZE_Ver-10, cWhite, FALSE);

	UI_game_chara_status(chara);
}

//ゲームモード内で使うUI

double HP_ber;
char UI_chara_Stutas_name[16][32] = {
	"Name",
	"Lv",
	"HP",
	"ATK.1",
	"ATK.2",
	"ATK.3",
	"DEF",
	"MP",
};
int UI_game_chara_status_coordinate;
void UI_game_chara_status(Chara chara) {
	UI_game_chara_status_coordinate = 170;
	for (int i = 0; i < 8; i++, UI_game_chara_status_coordinate += 40) {
		DrawFormatStringToHandle(20, UI_game_chara_status_coordinate, cWhite, gFont00, UI_chara_Stutas_name[i]);
	}
	DrawFormatStringToHandle(120, 170, cWhite, gFont00, "%s", chara.c_sta.name);
	DrawFormatStringToHandle(120, 210, cWhite, gFont00, "%d", chara.c_sta.Lv);
	DrawFormatStringToHandle(120, 250, cWhite, gFont00, "%d / %d", chara.c_sta.HP,chara.c_sta.MaxHP);
	DrawFormatStringToHandle(120, 290, cWhite, gFont00, "%d", chara.c_sta.ATK[0]);
	DrawFormatStringToHandle(120, 330, cWhite, gFont00, "%d", chara.c_sta.ATK[1]);
	DrawFormatStringToHandle(120, 370, cWhite, gFont00, "%d", chara.c_sta.ATK[2]);
	DrawFormatStringToHandle(120, 410, cWhite, gFont00, "%d", chara.c_sta.DEF);
	DrawFormatStringToHandle(120, 450, cWhite, gFont00, "%d", chara.c_sta.MP);
	HP_ber = static_cast<double>(chara.c_sta.HP) / static_cast<double>(chara.c_sta.MaxHP);
	DrawFormatString(300, 300, cWhite, "Debug : %f", HP_ber);
	DrawBox(20, 490, WINDOW_SIZE_Bes / 4 - 20, 510, cWhite, FALSE);
	DrawBox(20, 490, static_cast<int>((WINDOW_SIZE_Bes / 4 - 40) * HP_ber) + 20, 510, cWhite, TRUE);
}