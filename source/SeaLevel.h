#pragma once
#include "MyDefine.h"



static const int N = WIDTH;	// 数値計算用頂点数は画面のピクセル数とした。

// 海面クラス。波は数値計算で割り出している。手法に関して改善の余地あり。

// 数値計算法については、
// 「力学アルゴリズムによる波のシミュレーション(線上の波) - VCSSL」
// https://www.vcssl.org/ja-jp/code/archive/0001/1100-string-wave/
// を参考とした。

class SeaLevel {
	
	// 海面の頂点。Nを画面上のxとみなせば y = f(x)の形として表せる。
	float seaX[N];	// 海面 x座標
	float seaY[N];	// 海面 y座標
	float seaVY[N];	// 海面 y方向速度
	float seaFY[N];	// 海面 y方向張力

	// 各物理特性 (パラメータはゲーム中の見た目を参考に試行錯誤で決定)
	float LENGTH = 5.0f;		// 線の長さ
	float DENSITY = 100.0f;		// 密度
	float TENSION = 1.3f;		// 張力
	float FRICTION = 0.01f;		// 減衰係数
	float PULSE_WIDTH = 0.2f;	// 初期波の幅
	float PULSE_HEIGHT = -100.0f;	// 初期波の高さ

	const float dx = LENGTH / (float)N;	// 画面 1 ピクセル当たりの距離
	float dt;	// delta_time 格納用 (delta_timeでは 波の計算が発散してしまうことがあったのでdtで固定とした。)

public:
	SeaLevel();
	~SeaLevel();

	void init();							// 波の形状初期化
	void updateLeftAndRightEnds();			// 波の発生源の挙動(画面両端で波を発生)
	void updateSea();						// 波の伝播の計算を行う。
	int getSeaY(int x) { return seaY[x]; }	// 波の高さ y(x) の取得

	void draw();	// 描画
};

