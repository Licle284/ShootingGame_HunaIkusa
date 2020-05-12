#pragma once
#include "DxLib.h"
#include <string.h>


//***　グローバル変数 ***//
constexpr int WIDTH = 640;		// 画面幅
constexpr int HEIGHT = 480;		// 画面高さ
extern float delta_time;		// メインループ1週の時間
extern UINT start_time;			// delta_time算出用
constexpr float PI = 3.1415926f;// 円周率



//*** キー入力関係 ***//
//新・C言語　～ゲームプログラミングの館～ https://dixq.net/g/index.html　を参考とした
namespace key {
	extern char state[256];		// アプリケーション内で統一のキー状態 
	extern int count[256];		// 統一のキーの入力継続カウント
	// キーの状態更新
	inline static void update() {
		GetHitKeyStateAll(key::state);
		for (int i = 0; i < 256; i++) {
			if (state[i]) count[i]++;
			else count[i] = 0;
		}
	}

	//特定のキーの入力カウントを返す
	inline static int get(int key_state) {
		return count[key_state];
	}
}

//*** 色 ***//
// 頻繁に使用する予定のものをまとめている。
namespace color {
	const int white = GetColor(255, 255, 255);
	const int black = GetColor(0, 0, 0);
	const int red = GetColor(255, 0, 0);
	const int blue = GetColor(0, 0, 255);
	const int green = GetColor(0, 255, 0);
	const int gray = GetColor(128, 128, 128);
	const int gray2 = GetColor(200, 200, 200);
	const int yellow = GetColor(255, 255, 0);
}


