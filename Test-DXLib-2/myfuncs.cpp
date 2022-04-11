#include <DxLib.h>
#include <conio.h>
#include "myfuncs.h"
#include "Chara.h"
#include "UI.h"

static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 61;	//平均を取るサンプル数
static const int FPS = 65;	//設定したFPS
int Key[256];
int cWhite;
int gFont00;
int gFontTitle;
int gFontSubTitle;
int cRad;
int cOrange;


//アプリケーション自体の設定等
void SetUp() {
	SetGraphMode(1280, 720, 32);
	SetWindowSize(WINDOW_SIZE_Bes,WINDOW_SIZE_Ver);
	ChangeWindowMode(TRUE), // ウィンドウモードに設定
	DxLib_Init(),		// ＤＸライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	cWhite = GetColor(255, 255, 255);
	cRad = GetColor(255, 0, 0);
	cOrange = GetColor(240, 128, 128);
	gFont00 = CreateFontToHandle("メイリオ", 25, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	gFontTitle = CreateFontToHandle("メイリオ", 100, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	gFontSubTitle = CreateFontToHandle("メイリオ", 75, 3, DX_FONTTYPE_ANTIALIASING_EDGE);

}


bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
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
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

void NowLoading(int font) {
	DrawStringToHandle(1000, 625, "Now Loading!!", GetColor(255, 255, 255), font);
}

int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

//ファイル処理
int Data_Save(Chara *chara) {
	//ファイルクラスのポインタを生成
	FILE* fp;
	//セキュリティー強化fopen_sでは返り値がerrno_tで宣言されている
	errno_t er;
	//もしファイルが開けなかったら例外を返却、main()内でアプリを強制終了
	if ((er = fopen_s(&fp, "SaveData.dat", "wb")) != 0 || fp == 0) {
		return -1;
	}
	//Charaクラスのステータスを全部格納
	fprintf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name, chara->c_sta.Lv,
		chara->c_sta.ATK[0], chara->c_sta.ATK[1], chara->c_sta.ATK[2], chara->c_sta.DEF,
		chara->c_sta.HP, chara->c_sta.MaxHP, chara->c_sta.MP
	);
	//ファイルを閉じる
	fclose(fp);
	return 0;
}

int Data_Load(Chara *chara) {
	//Data_Save()と同じ
	FILE* fp;
	errno_t er;
	if ((er = fopen_s(&fp, "SaveData.dat", "rb")) != 0 || fp == 0) {
		return -1;
	}
	//セキュリティー強化fscanf_sでは文字列を取得する場合、その一つ後ろの引数は最大バッファになる
	//Charaクラスのステータスを全部取得
	fscanf_s(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", chara->c_sta.name, 256, &chara->c_sta.Lv,
		&chara->c_sta.ATK[0], &chara->c_sta.ATK[1], &chara->c_sta.ATK[2], &chara->c_sta.DEF,
		&chara->c_sta.HP, &chara->c_sta.MaxHP, &chara->c_sta.MP
	);
	//ファイルを閉じる
	fclose(fp);
	return 0;
}

//タイトル
int Title() {
	//UI.h及びUI.cppのUI_Title()の引数
	int select = 0;
	//ここはキー入力を伴うためループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		//キー入力
		//↓で下へ　↑で上へ　Enterで決定
		if (Key[KEY_INPUT_DOWN] % 10 == 1 || Key[KEY_INPUT_DOWN] > 60) {
			select++;
		}
		if (Key[KEY_INPUT_UP] % 10 == 1 || Key[KEY_INPUT_UP] > 60) {
			select--;
		}
		//selectは負になる可能性があるので正にする
		select > 0 ? select : select += 5;
		if (Key[KEY_INPUT_RETURN] == 1) {
			return (select % 5);
		}
		UI_title(select % 5);
	}

	//もし正常に終了した場合Enterでのif文内で終了するためエラーの返り値は-1になる
	return -1;
}

int Data_Save_D(Dungeon *dun) {
	//ファイルクラスのポインタを生成
	FILE* fp;
	//セキュリティー強化fopen_sでは返り値がerrno_tで宣言されている
	errno_t er;
	//もしファイルが開けなかったら例外を返却、main()内でアプリを強制終了
	if ((er = fopen_s(&fp, "DataDungeon.dat", "wb")) != 0 || fp == 0) {
		return -1;
	}
	//Charaクラスのステータスを全部格納
	fprintf_s(fp, "%d\n%d\n%d\n", dun->Floor,dun->Lv,dun->Ene_Type);
	//ファイルを閉じる
	fclose(fp);
	return 0;
}