


#include "GameManager.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrShip.h"

#include "ChrBulletAlong.h"
#include "ChrBulletNormal.h"
#include "ChrBulletSin.h"
#include "ChrBulletStraight.h"



ChrShip::ChrShip() : Chr() {
	// 砲台の画像は共通のものとする。	
	image_battery = LoadGraph("battery.png");
}

// 当たり判定が有効となった場合、体力(life_point)を削り、ダメージタイムをセットする。
void ChrShip::hit() {
	damage_time = 50;
	PlaySoundMem(GameManager::gameManager->sound_damage, DX_PLAYTYPE_BACK);
	life_point--;
}

// 船として共通の動きを実装
void ChrShip::update() {
	// 体力がゼロならdeadフラグを立たせる
	if (life_point <= 0) {
		dead();
		// ゲームマネージャーに敗北者のタイプを伝える。
		GameManager::gameManager->setLoser(chr_type);
	}

	// x方向制限
	if (px < hit_width) px = hit_width;
	if (px > WIDTH - hit_width) px = WIDTH - hit_width;

	// y 座標を海面に合わせる
	py = mSea->getSeaY(px);
	angle = atan((mSea->getSeaY(px + 25) - mSea->getSeaY(px - 25)) / 50.0);
}


// Bulletタイプと攻撃力は弾を重ねて表現した。
void ChrShip::bulletShot(BulletType type, int num, float interval) {
	// 合計角度
	double a = angle + angle_battery;

	// 送られた弾タイプで、位置、速度、キャラタイプ(敵味方どちらが発射したか)を
	// セットしてゲームマネージャーのキャラリストに追加。
	for (int i = -num; i <= num; i++) {
		Chr* bullet;
		switch (type) {
		case BULLET_STRAIGHT:
			bullet = new ChrBulletStraight();
			break;
		case BULLET_ALONG:
			bullet = new ChrBulletAlong();
			break;
		case BULLET_SIN:
			bullet = new ChrBulletSin();
			break;
		default:
			bullet = new ChrBulletNormal();
		}
		bullet->setPosition(px, py);
		bullet->setSpeed(shot_speed * cos(a + interval * i), shot_speed * sin(a + interval * i));	//弾の初期速度
		bullet->setChrType(getChrType());
		GameManager::gameManager->addList(bullet);
	}
}