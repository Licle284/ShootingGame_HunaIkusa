#include "MyDefine.h"

#include "Chr.h"
#include "ChrShip.h"
#include "ChrShipPlayer.h"

#include "GameManager.h"
#include "ChrBullet.h"
#include <vector>
#include <string>

// ゲームマネージャー実体化
GameManager* GameManager::gameManager;


ChrShipPlayer::ChrShipPlayer() : ChrShip() {
	setImage("ship_player.png");			// 画像
	setPosition(WIDTH / 4, HEIGHT / 2);		// 位置画面左にセット
	damage_time = 0;						// ダメージ残り時間を0
	chr_type = TYPE_PLAYER;					// キャラタイプ
	life_point_max = 230;					// 体力の最大値
	life_point = life_point_max;			// 体力を最大値にセット
	angle_battery = 0.f;					// 砲台の(船との)相対角度セット
	px_battery = 3;		// 砲台を船の中心から右にずらす

	//使用する弾のタイプ
	bullet_vec.push_back(BULLET_NORMAL);
	bullet_vec.push_back(BULLET_STRAIGHT);
	bullet_vec.push_back(BULLET_ALONG);
	bullet_vec.push_back(BULLET_SIN);
	now_bullet_type = bullet_vec[0];
}

// プレイヤーはあたり判定有効処理一回に付き、「敵」の10倍のダメージを受ける。
// よって体当たり(互いが当たり判定有効となりダメージを受ける)は不利となる。
// 代わりに弾の攻撃力を比較的高めに設定した
void ChrShipPlayer::hit() {
	ChrShip::hit();
	life_point -= 10;
}


void ChrShipPlayer::update() {
	if (damage_time > 0) {
		damage_time--;
	}
	static bool spacekey_flag = false;	// スペースキーが押されていたかどうかを示すもの


	// x方向移動
	if (key::get(KEY_INPUT_LEFT) > 1) px -= 2;
	if (key::get(KEY_INPUT_RIGHT) > 1) px += 2;
	// 砲台角度調整
	if (key::get(KEY_INPUT_UP) > 1)  angle_battery -= PI / 90;
	if (key::get(KEY_INPUT_DOWN) > 1)  angle_battery += PI / 90;
	// 砲台角度制限
	if (angle_battery < -PI / 2.f) angle_battery = -PI / 2.f;
	if (angle_battery > 0.f) angle_battery = 0.f;

	// 放つ弾の種類切替
	if (key::get(KEY_INPUT_W) == 1) {
		static int num = 0;
		num++;
		num = num % bullet_vec.size();
		now_bullet_type = bullet_vec[num];
	}
	
	// チャージショット　スペースキー長押し時間により技が変化
	if ((spacekey_flag && (key::get(KEY_INPUT_SPACE) == 0))) {
		spacekey_flag = false;

		// 毎フレーム連射(最長長押し)
		if (bullet_charge > 9) {
			spacekey_flag = true;
			bulletShot(now_bullet_type, 0, 0.4f);
			bullet_charge -= delta_time * 0.5;
		}
		// 放射状に発射
		else if (bullet_charge > 8) {
			bulletShot(now_bullet_type, 20, 0.1f);
			bulletShot(now_bullet_type, 40, 0.05f);
			bullet_charge -= delta_time * 0.5;
		}
		// 弾の集合体を放つ。
		else if (bullet_charge > 4) {
			bulletShot(now_bullet_type, 110, 0.001f);
			bullet_charge = 0.f;
		}
		// 放射状発射
		else if (bullet_charge > 2) {
			bulletShot(now_bullet_type, 10, 0.25f);
			bulletShot(now_bullet_type, 3, 0.2f);
			bullet_charge = 0.f;
		}
		// 前方のみ放射攻撃
		else if (bullet_charge > 0.4) {
			bulletShot(now_bullet_type, 5, 0.1f);
			bullet_charge = 0.f;
		}
		// 通常長押し攻撃
		else if (bullet_charge > 0) {
			bulletShot(now_bullet_type, 0, 0.f);
		}
		// チャージ時間 4 以上で効果音変化
		if(bullet_charge > 4)PlaySoundMem(GameManager::gameManager->sound_bigshot, DX_PLAYTYPE_BACK);
		else PlaySoundMem(GameManager::gameManager->sound_shot_p, DX_PLAYTYPE_BACK);
	}

	// チャージショット準備
	else if (key::get(KEY_INPUT_SPACE) > 1) {
		spacekey_flag = true;
		bullet_charge += delta_time;
		if (bullet_charge > 11) bullet_charge = 10.f;
	}
	
	// 弾を放つ 単発
	if (key::get(KEY_INPUT_SPACE) == 1) {
		if (able_shot_flag) {
			able_shot_flag = false;
			bullet_charge = 0.f;
			PlaySoundMem(GameManager::gameManager->sound_shot_p, DX_PLAYTYPE_BACK);
			bulletShot(now_bullet_type, 0,0.f);
		}
	}
	else {
		able_shot_flag = true;
	}

	// 船として共通の動作
	ChrShip::update();
}


void ChrShipPlayer::draw() {
	// HPゲージ
	DrawBox(50, 80, 50 + width_gage, 80 + height_gage, color::red, TRUE);
	DrawBox(50, 80, 50 + (float)life_point / (float)life_point_max * width_gage, 80 + height_gage, color::green, TRUE);
	DrawBox(48, 58, 102, 78, color::gray2, TRUE);
	DrawFormatString(50, 60, color::black, "あなた");

	// チャージゲージ
	DrawString(0, 110, "Charge", color::black);
	DrawBox(60, 108, 60 + width_gage, 122, color::gray, TRUE);
	int color_gage;
	if (bullet_charge > 4) color_gage = GetColor(255, 100, 0);
	else if (bullet_charge > 2) color_gage = GetColor(255, 220, 0);
	else color_gage = GetColor(0,255,100);
	DrawBox(60, 110, 60 + bullet_charge/11.f * width_gage, 120, color_gage, TRUE);
	
	// 弾の種類　表示部分
	DrawBox(60, 128, 132, 152, color::gray, TRUE);
	if (now_bullet_type == BULLET_NORMAL) DrawFormatString(62, 130, color::yellow, "放物線弾");
	else if(now_bullet_type == BULLET_STRAIGHT) DrawFormatString(62, 130,GetColor(255,0,255), "直線弾");
	else if (now_bullet_type == BULLET_ALONG) DrawFormatString(62, 130, GetColor(255,230,0), "海面弾");
	else if (now_bullet_type == BULLET_SIN) DrawFormatString(62, 130, color::white, "正弦波段");

	// ダメージエフェクトとして点滅するようにする
	if (damage_time == 0 || (damage_time) % 5 > 1) {
		DrawRotaGraph2(px + px_battery, py + py_battery, 0, 8, 0.8, angle + angle_battery, image_battery, TRUE);
		DrawRotaGraph(px, py, 1.0, angle, image, TRUE, FALSE);

	}
}

