#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"


// ���̉�
int ChrBullet::loaded_bullet_image[BULLET_TYPE_NUM] = { 0 };

// �e�𐶐�����Ƃ��A�u�e�^�C�v�v�����Ƃ��Ď󂯁A�K�؂ȉ摜�𓖂Ă͂߂�B
ChrBullet::ChrBullet(BulletType type):Chr() {
	if (type == BULLET_NORMAL)		setBulletImage("bullet_yellow.png");
	if (type == BULLET_ALONG)		setBulletImage("bullet_red.png");
	if (type == BULLET_STRAIGHT)	setBulletImage("bullet_purple.png");
	if (type == BULLET_SIN)			setBulletImage("bullet_white.png");
}


ChrBullet::~ChrBullet()
{
}

// ���[�h�ς݂̃C���[�W�̓��[�h�s�����΂��B
// �L�����N�^�N���X�Ɠ��l�̏������s���Ă���B�L�����N�^�^�C�v�ƒe�^�C�v�𕪂����������B
void ChrBullet::setBulletImage(char* filename) {
	if (loaded_bullet_image[getBulletType()] == 0) {
		loaded_bullet_image[getBulletType()] = LoadGraph(filename);
	}
	image = LoadGraph(filename);

	//�����蔻��p�̔��a�͂��̂悤�ɎZ�o����B
	GetGraphSize(image, &hit_width, &hit_height);
	hit_radius = hit_height / 2;
}


// �Փˎ��̋����@���S������B
void ChrBullet::hit() {
	dead();
}		



// �`��
void ChrBullet::draw() {
	DrawRotaGraph(px, py, 1.0, 0.0, image, TRUE);	
}