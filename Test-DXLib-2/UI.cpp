#include "DxLib.h"
#include "myfuncs.h"
#include <conio.h>
#include "Chara.h"
#include "UI.h"

extern int gFontTitle;
extern int gFont00;

//�^�C�g���ɗp����\����
typedef struct {
	int x, y;
	char choice[64];
}TITLE;

//�\����TITLE�̏�����
TITLE s_title[5] = {
	{WINDOW_SIZE_Bes / 2     ,WINDOW_SIZE_Ver / 2	   ,"U GAME START"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 30 ,"U CHECK DATA"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 60 ,"EDIT SETTING"},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 90 ,""},
	{WINDOW_SIZE_Bes / 2 + 20,WINDOW_SIZE_Ver / 2 + 120,"ESC FM HERE?"},
};


//�Q�[���^�C�g����UI
//������myfunc.h�y��myfunv.cpp��Title()�L��
void UI_title(int select) {	
	//TODO �o�[�W�����A�b�v
	DrawString(10, WINDOW_SIZE_Ver - 20, "ver.0.0.0,��", cWhite, FALSE);
	//�Q�[���^�C�g���\��
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