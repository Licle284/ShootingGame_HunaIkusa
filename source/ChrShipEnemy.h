#pragma once


// 敵の船クラス　
class ChrShipEnemy : public ChrShip {
	
protected:
	virtual ChrType getChrType() { return TYPE_ENEMY; }

	BulletType bullet_type;		// 使用する弾のタイプ
	int level_of_enemy;	// 敵のレベル。DxLibの乱数生成器に入れて使う、値が低いほうが強いとしている。

public:
	ChrShipEnemy(int gamelv);	// 強さレベルを渡して敵船を生成

	void update();		// 敵の挙動
	void draw();		// 敵側のアクセサリー描画用(体力ゲージなど)
};

