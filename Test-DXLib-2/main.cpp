#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"


extern int Key[256];
extern int cWhite, gFont00, gFontTitle;
extern int gFontSubTitle;
extern int cRad;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetUp();
	Chara chara;
	if (Data_Load(&chara) == -1) {
		DxLib_End();
		return 0;
	}

	if (chara.Load()) {
		chara.p_setName();
	}
	
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		DrawString(200, 200, chara.c_sta.name, cWhite, TRUE);

	}
	if (Data_Save(&chara) == -1) {
		DxLib_End();
		return 0;
	}
	

	DxLib_End();
	return 0;
}