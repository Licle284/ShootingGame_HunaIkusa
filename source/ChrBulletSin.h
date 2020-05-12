#pragma once

// 弾の派生クラス　正弦波を組み込んだ動きを持つ弾
class ChrBulletSin :public ChrBullet
{
public:
	ChrBulletSin();
	~ChrBulletSin();

	virtual BulletType getBulletType() { return BULLET_SIN; }	// 弾タイプ取得
	virtual void update();	// 正弦波を参考にした挙動
};

