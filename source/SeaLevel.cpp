#include "MyDefine.h"
#include "SeaLevel.h"
#include <math.h>


// 計算上 y = 0 原点の海面を画面の中へずらす
const float offsetY = (float)HEIGHT / 2.0 + 100.f;

// 生成と初期化
SeaLevel::SeaLevel(){
	init();
}

SeaLevel::~SeaLevel()
{
}

// 海面の形状初期化
void  SeaLevel::init() {
	// x 方向の設定
	for (int i = 0; i < N; i++) {
		float x = i * dx;
		seaX[i] = x;
	}

	// 海面の初期高さ y(x) を決める
	float initX = LENGTH / 2;
	for (int i = 0; i < N; i++) {
		float x = i * dx;
		// ガウス関数を用いて滑らかに
		seaY[i] = PULSE_HEIGHT *
			expf(-(x - initX)*(x - initX) / (2 * PULSE_WIDTH * PULSE_WIDTH)) + offsetY;
		seaVY[i] = 0.0;		// 海面の初期速度ゼロ
	}
	dt = 0.008;		// 海面に対してのデルタタイム
}


//海面の動き(駆動部)  画面両端の y を動かす。
void SeaLevel::updateLeftAndRightEnds() {
	// 0 : 左 ,       1 : 右     とする

	// 必要変数を二つずつ用意する
	static float time[2] = { 0.f };
	static float time_period[2] = { 1.f, 1.f };
	static float wave_speed[2] = { 1.f,1.f };

	for (int i = 0; i < 2; i++) {
		// 前回の波が一周し終えてから生成
		if (time[i] == 0.0) {
			time_period[i] = 5.f + GetRand(100) / 10.f;	// 周期をランダムで決定 
			time[i] = time_period[i];					// 時間変数に周期をセット
			wave_speed[i] = (GetRand(20) / 20.f - 0.5f) * 0.5;	// 振幅をランダムで決定	
		}

		// 時間変数の減算
		if (time[i] > 0) {
			time[i] -= delta_time;
		}
		// 時間変数が0となったら波が一周したということ
		else {
			time[i] = 0.0;
			if (i == 0) seaY[0] = offsetY;		// 両端の座標をこまめに初期化
			if (i == 1) seaY[N - 1] = offsetY;	// 誤差蓄積に起因する海面端の極端な動きを防ぐ
		}

		// 両端の y 座標変位の移動
		if (i == 0) {
			seaY[0] += wave_speed[i] * sinf(time[i] / time_period[i] * 2 * PI);
		}
		if (i == 1) {
			seaY[N - 1] += wave_speed[i] * sinf(time[i] / time_period[i] * 2 * PI);
		}
	}
}


// 海面の動き(被動部分)
void SeaLevel::updateSea() {
	// 波の発生
	updateLeftAndRightEnds();

	// 質量を計算
	float m = DENSITY * LENGTH / (N + 1);

	// 各頂点 y(x) にかかるY方向張力の計算。ほぼオイラー法であるため不安定。
	for (int i = 1; i < N - 1; i++) {
		seaFY[i] = (seaY[i + 1] + seaY[i - 1] - 2.f * seaY[i]) * TENSION / dx - FRICTION * seaVY[i];
	}
	
	// 両端には張力はかからないとした
	// (画面内の頂点に引っ張られ、駆動が邪魔されることはない)
	seaFY[0] = 0.0;
	seaFY[N - 1] = 0.0;
	
	// 算出された張力から、y 方向速度、 y 方向変位を順次算出
	for (int i = 0; i < N; i++) {
		seaVY[i] += seaFY[i] / m * dt;
		seaY[i] += seaVY[i] / m * dt;	// delta_time にすると不安定
	}
}


// 得られたx-y座標のとおり海面を描画
void SeaLevel::draw() {
	for (int i = 0; i < N - 1; i++) {
		int x = seaX[i]/dx;
		int y = seaY[i];
		DrawLineAA(x, y, x, HEIGHT, GetColor(50, 100, 250));
	}
}
