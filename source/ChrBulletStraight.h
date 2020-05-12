#pragma once


// 弾の派生クラス　真直ぐに飛ぶ弾
class ChrBulletStraight : public ChrBullet
{
public:
	ChrBulletStraight();
	~ChrBulletStraight();
	virtual BulletType getBulletType() { return BULLET_STRAIGHT; }	// 弾タイプ取得

	virtual void update();	// 移動などの挙動
};

