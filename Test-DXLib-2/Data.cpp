#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"
#include "Data.h"

extern int Key[256];
extern int gFont00;

char char_Data[16][256];
char char_Dungeons[8][64];


int Data() {
	//データ格納用のCharaクラスのインスタンス生成
	Chara c_Data;
	Dungeon Dun;
	//データ取得
	Load_All_Data(&c_Data, &Dun);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		//Escボタンで戻る
		DrawString(10, WINDOW_SIZE_Ver - 20, "Back to Title -> push Esc",cWhite,FALSE);
		if (Key[KEY_INPUT_ESCAPE] == 1) {
			return 0;
		}
		//Charaクラスのステータスを表示
		Draw_Status(c_Data);
		Draw_Dungeon(Dun);
	}
	
	return 0;
}

int Load_All_Data(Chara *c_Data,Dungeon *Dun) {
	//ファイルクラスのポインタを生成
	FILE* fp;
	//セキュリティー強化fopen_sでは返り値がerrno_tで宣言されている
	errno_t er;
	//もしファイルが開けなかったら例外を返却、main()内でアプリを強制終了
	if (0 != (er = fopen_s(&fp, "SaveData.dat", "rb"))) {
		return -1;
	}
	//Charaクラスのステータスを全部格納
	fscanf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", c_Data->c_sta.name, 256, &c_Data->c_sta.Lv,
		&c_Data->c_sta.ATK[0], &c_Data->c_sta.ATK[1], &c_Data->c_sta.ATK[2], &c_Data->c_sta.DEF,
		&c_Data->c_sta.HP,&c_Data->c_sta.MaxHP, &c_Data->c_sta.MP
	);
	//int型のデータをchar型に変換
	_itoa_s(c_Data->c_sta.ATK[0], char_Data[0], 16, 10);
	_itoa_s(c_Data->c_sta.ATK[1], char_Data[1], 16, 10);
	_itoa_s(c_Data->c_sta.ATK[2], char_Data[2], 16, 10);
	_itoa_s(c_Data->c_sta.DEF, char_Data[3], 16, 10);
	_itoa_s(c_Data->c_sta.HP, char_Data[4], 16, 10);
	_itoa_s(c_Data->c_sta.MaxHP, char_Data[5], 16, 10);
	_itoa_s(c_Data->c_sta.Lv, char_Data[6], 16, 10);
	_itoa_s(c_Data->c_sta.MP, char_Data[7], 16, 10);

	//ファイルを閉じる
	fclose(fp);

	//ファイルを開く
	if (0 != (er = fopen_s(&fp, "DataDungeon.dat", "rb")) || fp == 0) {
		return -1;
	}

	fscanf_s(fp, "%d\n%d\n%d\n", &Dun->Floor, &Dun->Lv, &Dun->Ene_Type);
	_itoa_s(Dun->Floor, char_Dungeons[0], 16, 10);
	_itoa_s(Dun->Lv, char_Dungeons[1], 16, 10);
	_itoa_s(Dun->Ene_Type, char_Dungeons[2], 16, 10);

	//ファイルを閉じる
	fclose(fp);

	return 0;
}

int Save_All_Data() {
	return 0;
}

//ステータス名の配列
char Status_name[16][64] = {
	{"ATK.1"},
	{"ATK.2"},
	{"ATK.3"},
	{"DEF"},
	{"HP"},
	{"MaxHP"},
	{"Lv"},
	{"MP"},
};

char Status_Dungeons[8][64] = {
	{"Floor"},
	{"Enemy's Lv"},
	{"Enemy's name"},
};

//Charaクラスのステータスを表示
void Draw_Status(Chara chara) {
	int Coordinate[2] = { WINDOW_SIZE_Bes / 3,WINDOW_SIZE_Ver / 8 };
	DrawStringToHandle(10, 10, "Your Status", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(Coordinate[0]-250, Coordinate[1], "What your Name?", cWhite, gFont00, FALSE, FALSE);
	DrawStringToHandle(Coordinate[0], Coordinate[1], chara.c_sta.name, cWhite, gFont00, FALSE, FALSE);
	for (int i = 0; i < 7; i++) {
		DrawStringToHandle(Coordinate[0] - 250, Coordinate[1] += 40, Status_name[i], cWhite, gFont00, FALSE, FALSE);
		DrawStringToHandle(Coordinate[0], Coordinate[1], char_Data[i], cWhite, gFont00, FALSE, FALSE);
	}

}

extern char Enemy_type[16][64];

void Draw_Dungeon(Dungeon Dun) {
	int Coordinate[2] = { WINDOW_SIZE_Bes / 3,WINDOW_SIZE_Ver / 8 + 300 };
	DrawStringToHandle(10, Coordinate[1] += 40, "Dungeons Data", cWhite, gFont00, FALSE, FALSE);

	for (int i = 0; i < 3; i++) {
		DrawStringToHandle(Coordinate[0] - 250, Coordinate[1] += 40, Status_Dungeons[i], cWhite, gFont00, FALSE, FALSE);
		if (i == 2) {
			DrawStringToHandle(Coordinate[0], Coordinate[1], Enemy_type[Dun.Ene_Type], cWhite, gFont00, FALSE, FALSE);
		}
		else {
			DrawStringToHandle(Coordinate[0], Coordinate[1], char_Dungeons[i], cWhite, gFont00, FALSE, FALSE);
		}
	}
}