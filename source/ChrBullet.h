#pragma once
#include "Chr.h"

// 挙動の異なる4種類の弾を用意した。
enum BulletType {
	BULLET_NORMAL,
	BULLET_ALONG,
	BULLET_STRAIGHT,
	BULLET_SIN,

	BULLET_TYPE_NUM,
};

// 弾クラスでは衝突時の挙動や描画、ロード済みの弾の画像などをまとめている。
class ChrBullet : public Chr {
	static int loaded_bullet_image[BULLET_TYPE_NUM];	// ロード済み画像の格納場所
protected:
	float gravity = 2.f;	// 重力加速度を定義、今回は船が重力を無視している為、弾クラスに持たせた。
	

public:
	ChrBullet(BulletType type);	// コンストラクタでは弾のタイプも同時に指定する。
	~ChrBullet();

	void setBulletImage(char* filename);	// 画像セッター
	virtual BulletType getBulletType() { return BULLET_NORMAL; }	// タイプゲッター

	virtual void hit();			// 衝突時の挙動
	// 弾全体に共通する行動範囲制限のみ実装
	virtual void update() { if (px > WIDTH || px < 0 || py > HEIGHT || py < -10000) dead(); }	// 移動などの挙動
	virtual void draw();		// 描画
};

