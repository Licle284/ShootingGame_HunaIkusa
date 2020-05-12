#pragma once


// 弾の派生クラス　海面に沿って移動する。
class ChrBulletAlong : public ChrBullet
{
public:
	ChrBulletAlong();
	~ChrBulletAlong();

	virtual BulletType getBulletType() { return BULLET_ALONG; }	// 自身の弾タイプ

	virtual void update();	// 海面に沿うような挙動
};

