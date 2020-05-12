#include "DxLib.h"
#include "MyDefine.h"

#include "GameManager.h"
#include <math.h>


//*** MyDefine.h の外部宣言の実装 ***//
float delta_time = 0.f;
UINT start_time = 0;
char key::state[256] = { 0 };
int key::count[256] = { 0 };


// メイン関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	GameManager gameManager;				// ゲームマネージャーの生成
	if (gameManager.Initialize() == 0) {	// ゲームマネージャー初期化
		gameManager.Loop();					// メインループ
	}
	gameManager.End();						// 終了処理
	return 0;
}