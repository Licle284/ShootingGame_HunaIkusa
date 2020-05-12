#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"


// 実体化
int ChrBullet::loaded_bullet_image[BULLET_TYPE_NUM] = { 0 };

// 弾を生成するとき、「弾タイプ」引数として受け、適切な画像を当てはめる。
ChrBullet::ChrBullet(BulletType type):Chr() {
	if (type == BULLET_NORMAL)		setBulletImage("bullet_yellow.png");
	if (type == BULLET_ALONG)		setBulletImage("bullet_red.png");
	if (type == BULLET_STRAIGHT)	setBulletImage("bullet_purple.png");
	if (type == BULLET_SIN)			setBulletImage("bullet_white.png");
}


ChrBullet::~ChrBullet()
{
}

// ロード済みのイメージはロード行程を飛ばす。
// キャラクタクラスと同様の処理を行っている。キャラクタタイプと弾タイプを分けたかった。
void ChrBullet::setBulletImage(char* filename) {
	if (loaded_bullet_image[getBulletType()] == 0) {
		loaded_bullet_image[getBulletType()] = LoadGraph(filename);
	}
	image = LoadGraph(filename);

	//当たり判定用の半径はこのように算出する。
	GetGraphSize(image, &hit_width, &hit_height);
	hit_radius = hit_height / 2;
}


// 衝突時の挙動　死亡させる。
void ChrBullet::hit() {
	dead();
}		



// 描画
void ChrBullet::draw() {
	DrawRotaGraph(px, py, 1.0, 0.0, image, TRUE);	
}