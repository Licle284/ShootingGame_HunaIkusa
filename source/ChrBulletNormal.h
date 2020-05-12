#pragma once

// 弾の派生クラス　放物線を描く。この運動を通常としたため名前がNORMALとなっている。
class ChrBulletNormal:public ChrBullet
{
public:
	ChrBulletNormal();
	~ChrBulletNormal();
	virtual BulletType getBulletType() { return BULLET_NORMAL; }	// 弾タイプ取得
	virtual void update();		// 放物線挙動
};

