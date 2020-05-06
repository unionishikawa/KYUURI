#include "DxLib.h"
#include "Player.h"
#include<vector>
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(width,height,32);
	SetDrawScreen(DX_SCREEN_BACK);
	
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	Player p;
	enemy e[ENEMY_NUM];
	int count=0;
	while (!CheckHitKey(KEY_INPUT_SPACE)) {
		DrawFormatString(50, height/2, GetColor(100, 255, 255), "TO START  PRESS SPACE BUTTON", point / 3);
	}
	while (!CheckHitKey(KEY_INPUT_ESCAPE)) {
		if (end_f==true) {
			ClearDrawScreen();
			DrawFormatString(10, 20, GetColor(255, 255, 255), "CONTINUE PRESS ANY BUTTON", point / 3);
			DrawGraph(0,0,LoadGraph("Image3.png"),TRUE);
			ScreenFlip();
			WaitKey();
			point = 0;
			end_f = false;
		}
		count++;

		ClearDrawScreen();
		DrawFormatString(0, 20, GetColor(255,255,255), "score: %d", point/3);
		DrawLine(p.getp(0),0,p.getp(0),height,GetColor(40,40,40),3);
		p.move();
		p.show();
		
		for (int i = 0; i < ENEMY_NUM;i++) {
			if (e[i].live==TRUE) {
				e[i].dead(p.getp(0),p.getp(1));
				e[i].move();
				e[i].show();
			}
		}
		if (point%10==0) {
			DrawFormatString(0, 20, GetColor(255, 255, 255), "BONUS");
			point *= 1.1;
		}
		if (count>=60) {
			count = 0;
			//printfDx("spawn!");
			for (int i = 0; i < ENEMY_NUM;i++) {
				if (e[i].live==FALSE) {
					e[i].live = TRUE;
					i = ENEMY_NUM;
					break;
				}
			}
		}
		
		ScreenFlip();
		WaitVSync(1);
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}