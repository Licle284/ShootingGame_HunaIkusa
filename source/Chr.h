// 参考
/*
Copyright © 2002 naga3

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/





#pragma once
#include "SeaLevel.h"

// キャラクタータイプを設けて、画像データの保存や当たり判定の指標として使う。
// 列挙の中にある TYPE_BULLET は弾の画像保存には適用したが、当たり判定ではどちらが発射した弾か区別のつけ方が
// まとまらなかったので、弾を「プレイヤー」または「敵」として扱って動作させている。
enum ChrType {
	TYPE_NONE,
	TYPE_PLAYER,
	TYPE_ENEMY,
	TYPE_BULLET,

	TYPE_NUM,
};


// キャラクター基底クラス、座標と姿勢、画像描画のために共通で保有するデータを集める。
class Chr {
	bool dead_flag;	// 死亡フラグ
	static int loaded_image[TYPE_NUM];	// ロード済みの画像ハンドルをキャラクターの派生先に共有するため。
	

public:
	Chr();
	virtual ~Chr() {}

protected:
	int image;			// 画像
	float px, py;		// 位置
	double angle = 0.0; // 姿勢
	float extension;	// 画像拡大率
	float vx, vy;		// 速度

	float hit_radius;	// 当たり判定半径
	int hit_width;		// 当たり判定幅
	int hit_height;		// 当たり判定高さ
	void dead() { dead_flag = true; }	// 死亡フラグ立てる

	ChrType chr_type = TYPE_NONE;	// キャラクタータイプ
	
	

public:
	void setImage(char*);			// 画像セッター
	void setPosition(int, int);		// 位置セッター
	void setSpeed(float, float);	// 速度セッター

	float GetHitRadius() { return hit_radius; }	// 当たり判定は全て「円」としておこなう。
	int GetPosX() { return px; }	// 
	int GetPosY() { return py; }
	bool isDead() { return dead_flag; }	// 死亡フラグの様子を伝える

	bool HitTest(Chr*);		// 特定の相手の「キャラ」との当たりはんていを行うメソッド。

	void setChrType(ChrType);	// キャラクタタイプのセッター
	ChrType getChrType() { return chr_type; }	// キャラクタタイプのゲッター
	
	virtual void hit() {}		// 衝突時の挙動
	virtual void update() {}	// 移動などの挙動
	virtual void draw();		// 描画

	static SeaLevel* mSea;		// キャラクターの挙動に、海面のデータを反映したかった。
};


