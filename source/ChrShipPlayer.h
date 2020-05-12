#pragma once
#include "ChrBullet.h"
#include <vector>


// 人がキーボード等で操る船のクラス
class ChrShipPlayer : public ChrShip{
protected:
	virtual ChrType getChrType() { return TYPE_PLAYER; }	// キャラクタータイプのゲッター
	
	std::vector<BulletType> bullet_vec;		// 使用する弾のタイプを格納する(今回は常に全て含ませた)
	int now_vec_num;	// 現在どの弾タイプを扱っているかを整数で示す(加算による弾タイプ変更のため用意)
	BulletType now_bullet_type;		// 現在の弾タイプを示す。これを切り替えて弾を複数種類扱う。
	float bullet_charge = 0;		// チャージショット用のカウンタ。時間情報が入る。

public:
	ChrShipPlayer();

	void hit();		// 衝突時の処理

	void update();	// キャラクター操作等
	void draw();	// 描画(体力ゲージ等)
};

