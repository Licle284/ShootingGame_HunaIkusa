


#include "GameManager.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrShip.h"

#include "ChrBulletAlong.h"
#include "ChrBulletNormal.h"
#include "ChrBulletSin.h"
#include "ChrBulletStraight.h"



ChrShip::ChrShip() : Chr() {
	// �C��̉摜�͋��ʂ̂��̂Ƃ���B	
	image_battery = LoadGraph("battery.png");
}

// �����蔻�肪�L���ƂȂ����ꍇ�A�̗�(life_point)�����A�_���[�W�^�C�����Z�b�g����B
void ChrShip::hit() {
	damage_time = 50;
	PlaySoundMem(GameManager::gameManager->sound_damage, DX_PLAYTYPE_BACK);
	life_point--;
}

// �D�Ƃ��ċ��ʂ̓���������
void ChrShip::update() {
	// �̗͂��[���Ȃ�dead�t���O�𗧂�����
	if (life_point <= 0) {
		dead();
		// �Q�[���}�l�[�W���[�ɔs�k�҂̃^�C�v��`����B
		GameManager::gameManager->setLoser(chr_type);
	}

	// x��������
	if (px < hit_width) px = hit_width;
	if (px > WIDTH - hit_width) px = WIDTH - hit_width;

	// y ���W���C�ʂɍ��킹��
	py = mSea->getSeaY(px);
	angle = atan((mSea->getSeaY(px + 25) - mSea->getSeaY(px - 25)) / 50.0);
}


// Bullet�^�C�v�ƍU���͂͒e���d�˂ĕ\�������B
void ChrShip::bulletShot(BulletType type, int num, float interval) {
	// ���v�p�x
	double a = angle + angle_battery;

	// ����ꂽ�e�^�C�v�ŁA�ʒu�A���x�A�L�����^�C�v(�G�����ǂ��炪���˂�����)��
	// �Z�b�g���ăQ�[���}�l�[�W���[�̃L�������X�g�ɒǉ��B
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
		bullet->setSpeed(shot_speed * cos(a + interval * i), shot_speed * sin(a + interval * i));	//�e�̏������x
		bullet->setChrType(getChrType());
		GameManager::gameManager->addList(bullet);
	}
}