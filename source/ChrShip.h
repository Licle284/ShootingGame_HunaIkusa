#pragma once
#include "ChrBullet.h"


// 船クラス　弾を打ち出す機能を有する。またゲーム本体クラスへ、このクラスの命とタイプが影響を与える。
// 波の影響など船らしい挙動や行動制限などをこのクラスで計算し、具体的な戦いは派生クラスに一任する。
class ChrShip : public Chr {

public:
	ChrShip();

protected:
	bool able_shot_flag;		// 弾を打てる状態か
	float shot_speed = 5.f;		// 弾の初期速度
	int damage_time;			// ダメージエフェクトの残り時間

	int life_point;			// 船の体力
	int life_point_max;		// 体力の最大値

	int width_for_angle = 20;	// 船の傾き算出用の幅の半分

	int image_battery;		// 砲台の画像
	double angle_battery;	// 砲台の船との相対角度
	int px_battery;			// 砲台と船との相対座標
	int py_battery = -3;	// 〃

	int width_gage = 150;	// 体力表示用のゲージの幅
	int height_gage = 20;	// ゲージ高さ

public:

	virtual ChrType getChrType() = 0;	// 船の下の改装、敵とプレイヤーで実装

	virtual void hit();		// 衝突時の挙動
	virtual void update();	// 移動などの挙動
	virtual void draw() {};		// 描画

	// 弾タイプ、個数、一発ごとの発射角度間隔から、弾を生成する
	void bulletShot(BulletType type, int num, float interval);	
};

