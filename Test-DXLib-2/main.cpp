#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"
#include "Data.h"
#include "game.h"


extern int Key[256];
extern int cWhite, gFont00, gFontTitle;
extern int gFontSubTitle;
extern int cRad;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//アプリケーション起動時のウィンドウ調整など
	SetUp();

	//Charaクラスのインスタンス生成
	Chara chara;
	Dungeon enemy;

	//もしセーブデータ格納ファイルが開けなかった場合アプリを強制終了
	if (Load_All_Data(&chara,&enemy) == -1) {
		DxLib_End();
		return 0;
	}

	bool App_End = false;
	//例外もしくはEsc...を押さないとアプリを終了しない
	while (App_End != true) {
		//タイトルの表示
		switch (Title()) {
			//Game.cpp及びGame.hへ
		case 0:
			//もしGameが例外参照した場合アプリを強制終了
			if (Game_main(&chara,&enemy) == -1) {
				DxLib_End(); return 0;
			}
			break;
			//Data.cpp及びData.hへ
		case 1:		Data();					break;
			//Edit.cpp及びEdit.hへ
		case 2:								break;
			//後々機能追加？
		case 3:
			//アプリ終了、データを格納したいのでswitch文は抜ける
		case 4:		App_End = true;			break;
			//例外、アプリを強制終了　データの保証はされない
		case -1:	DxLib_End(); return 0;	break;
		}
	}

	//ファイルを開けなかったら強制終了
	//データをファイルに格納
	if (Data_Save(&chara) == -1) {
		DxLib_End();
		return 0;
	}
	if (Data_Save_D(&enemy) == -1) {
		DxLib_End();
		return 0;
	}

	DxLib_End();
	return 0;
}