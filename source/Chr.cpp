// 参考
/*
Copyright © 2002 naga3

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/





#include "GameManager.h"
#include "Chr.h"

#include "DxLib.h"


// キャラクタが参照する海面ポインタ
SeaLevel* Chr::mSea;

// 実体化
int Chr::loaded_image[TYPE_NUM] = { 0 };

// 死亡フラグを折り、キャラクタ用海面ポインタに、ゲームマネージャが管理する海面ポインタ(実体)を渡す。
Chr::Chr() {
	dead_flag = false;
	mSea = GameManager::gameManager->mSea;
}

// ロード済みの画像はロード行程を飛ばす。
void Chr::setImage(char* filename) {
	if (loaded_image[getChrType()] == 0) {
		loaded_image[getChrType()] = LoadGraph(filename);
	}
	image = LoadGraph(filename);
	
	//当たり判定用の半径はこのように算出する。
	GetGraphSize(image, &hit_width, &hit_height);
	hit_radius = hit_height / 2;
}

// 位置と速度のセッター
void Chr::setPosition(int _px, int _py) {
	px = _px; py = _py;
}
void Chr::setSpeed(float _vx, float _vy) {
	vx = _vx; vy = _vy;
}

// シンプルな描画(キャラクタのみ)
void Chr::draw() {
	DrawGraph(px, py, image, TRUE);
}

// キャラクタ同士の当たり判定円周の交差を基準とする。
bool Chr::HitTest(Chr* dst) {
	float x2 = (px - dst->px) * (px - dst->px);
	float y2 = (py - dst->py) * (py - dst->py);
	float r2 = (hit_radius + dst->hit_radius) * (hit_radius + dst->hit_radius);
	if (x2 + y2 < r2) return true;
	return false;
}

// キャラクタタイプセッター
void Chr::setChrType(ChrType c) {
	chr_type = c;
}