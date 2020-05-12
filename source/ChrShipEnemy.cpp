
#include "MyDefine.h"
#include "Chr.h"
#include "ChrShip.h"
#include "ChrShipPlayer.h"
#include "ChrShipEnemy.h"

#include "GameManager.h"
#include "ChrBullet.h"


// 強さの指標 gamelv を受け取り、インスタンス化
ChrShipEnemy::ChrShipEnemy(int gamelv) : ChrShip() {
	setImage("ship_enemy.png");					// 画像セット
	setPosition(WIDTH * 3 / 4, HEIGHT / 2);		// 画面右側セット
	damage_time = 0;							// ダメージ残りタイム0
	chr_type = TYPE_ENEMY;						// キャラクタタイプ　敵
	life_point_max = 170;						// 体力最大値を170にセット
	life_point = life_point_max;				// 体力を最大値にセット
	angle_battery = -PI;						// 砲台の(船との)相対角度をセット
	px_battery = -3;							// 砲台を船の中心から左にずらす
	level_of_enemy = gamelv;					// レベルを送られてきた数値でセット
	
	vx = 0.f;									// x方向速度初期化
}

void ChrShipEnemy::update() {
	if (damage_time > 0) {
		damage_time--;
	}

	// x方向移動 ランダム
	if (GetRand(7) == 0) {
		int rand = GetRand(3);
		if (rand == 1) vx = 1.f;
		else if (rand == 2) vx = -1.f;
		else vx = 0.f;
	}
	px += vx;
	
	// 砲台の角度調整
	if (GetRand(30) > 6) angle_battery += PI / 90;
	if (GetRand(30) > 6) angle_battery -= PI / 90;

	// 砲台角度制限
	if (angle_battery > -PI * 3.f / 4.f) angle_battery = -PI * 3.f / 4.f;
	if (angle_battery < -PI) angle_battery = -PI;

	// 攻撃行動
	// 攻撃行動に出るかどうか。
	if (GetRand((level_of_enemy + 2) * 10) == 0) {
	

		bool bigshot_flag = false;
		PlaySoundMem(GameManager::gameManager->sound_shot_e, DX_PLAYTYPE_BACK);

		// どの攻撃を繰り出すか 　レベルが上がる(値が小さくなる)と、
		// 強力な攻撃が発動する確率が上がる。
		if (GetRand(30) == 0) {
			// 弾のタイプ、一度に発射する個数(引数 * 2 + 1)、発射した弾の角度間隔をセット
			bulletShot(BULLET_NORMAL, 3, 0.2);
		}
		else if (GetRand(level_of_enemy * 15) == 0) {
			bulletShot(BULLET_NORMAL, 10, 0.3);
			bigshot_flag = true;
		}
		else if (GetRand(level_of_enemy * 20) == 0) {
			bulletShot(BULLET_NORMAL, GetRand(30 - 6 * level_of_enemy), 0.05);
			bigshot_flag = true;
		}

		if (GetRand(30) == 0) {
			bulletShot(BULLET_STRAIGHT, 4, 0.2);
		}
		else if (GetRand(level_of_enemy * 20) == 0) {
			bulletShot(BULLET_STRAIGHT, GetRand(30 - 6 * level_of_enemy), 0.3);
			bigshot_flag = true;
		}

		if (GetRand(30) == 0) {
			bulletShot(BULLET_SIN, 3, 0.4);
		}
		else if (GetRand(level_of_enemy * 25) == 0) {
			bulletShot(BULLET_SIN, GetRand(30 - 6 * level_of_enemy), 0.3);
			bigshot_flag = true;
		}

		if (GetRand(30) == 0) {
			bulletShot(BULLET_ALONG, 3, 0.2);
		}
		else if (GetRand(level_of_enemy * 25) == 0) {
			bulletShot(BULLET_ALONG, GetRand(30 - 6 * level_of_enemy), 0.2);
			bigshot_flag = true;
		}
		
		bulletShot(BULLET_NORMAL,0, 0.0);
		if(bigshot_flag)PlaySoundMem(GameManager::gameManager->sound_bigshot,DX_PLAYTYPE_BACK);
	}

	// 船として共通の動作
	ChrShip::update();
}

void ChrShipEnemy::draw() {

	//HPゲージの表示
	DrawBox(WIDTH - 50, 80, WIDTH - 50 - width_gage, 80 + height_gage, color::red, TRUE);
	DrawBox(WIDTH - 50 - width_gage + ((float)life_point / (float)life_point_max * width_gage), 80, WIDTH - 50 - width_gage, 80 + height_gage,color::green,TRUE);
	DrawBox(WIDTH - 52 - width_gage, 60, WIDTH - 50 - width_gage + 20, 78, color::gray2, TRUE);
	DrawFormatString(WIDTH - 50 - width_gage, 60, color::black, "敵");

	// ダメージエフェクトとして点滅するようにする
	if (damage_time == 0 || (damage_time) % 5  > 1) {
		DrawRotaGraph2(px + px_battery, py + py_battery, 0, 8, 0.8, angle + angle_battery, image_battery, TRUE);
		DrawRotaGraph(px, py, 1.0, angle, image, TRUE,TRUE);
	}
}