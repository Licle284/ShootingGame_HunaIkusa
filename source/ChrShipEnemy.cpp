
#include "MyDefine.h"
#include "Chr.h"
#include "ChrShip.h"
#include "ChrShipPlayer.h"
#include "ChrShipEnemy.h"

#include "GameManager.h"
#include "ChrBullet.h"


// �����̎w�W gamelv ���󂯎��A�C���X�^���X��
ChrShipEnemy::ChrShipEnemy(int gamelv) : ChrShip() {
	setImage("ship_enemy.png");					// �摜�Z�b�g
	setPosition(WIDTH * 3 / 4, HEIGHT / 2);		// ��ʉE���Z�b�g
	damage_time = 0;							// �_���[�W�c��^�C��0
	chr_type = TYPE_ENEMY;						// �L�����N�^�^�C�v�@�G
	life_point_max = 170;						// �̗͍ő�l��170�ɃZ�b�g
	life_point = life_point_max;				// �̗͂��ő�l�ɃZ�b�g
	angle_battery = -PI;						// �C���(�D�Ƃ�)���Ίp�x���Z�b�g
	px_battery = -3;							// �C���D�̒��S���獶�ɂ��炷
	level_of_enemy = gamelv;					// ���x���𑗂��Ă������l�ŃZ�b�g
	
	vx = 0.f;									// x�������x������
}

void ChrShipEnemy::update() {
	if (damage_time > 0) {
		damage_time--;
	}

	// x�����ړ� �����_��
	if (GetRand(7) == 0) {
		int rand = GetRand(3);
		if (rand == 1) vx = 1.f;
		else if (rand == 2) vx = -1.f;
		else vx = 0.f;
	}
	px += vx;
	
	// �C��̊p�x����
	if (GetRand(30) > 6) angle_battery += PI / 90;
	if (GetRand(30) > 6) angle_battery -= PI / 90;

	// �C��p�x����
	if (angle_battery > -PI * 3.f / 4.f) angle_battery = -PI * 3.f / 4.f;
	if (angle_battery < -PI) angle_battery = -PI;

	// �U���s��
	// �U���s���ɏo�邩�ǂ����B
	if (GetRand((level_of_enemy + 2) * 10) == 0) {
	

		bool bigshot_flag = false;
		PlaySoundMem(GameManager::gameManager->sound_shot_e, DX_PLAYTYPE_BACK);

		// �ǂ̍U�����J��o���� �@���x�����オ��(�l���������Ȃ�)�ƁA
		// ���͂ȍU������������m�����オ��B
		if (GetRand(30) == 0) {
			// �e�̃^�C�v�A��x�ɔ��˂����(���� * 2 + 1)�A���˂����e�̊p�x�Ԋu���Z�b�g
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

	// �D�Ƃ��ċ��ʂ̓���
	ChrShip::update();
}

void ChrShipEnemy::draw() {

	//HP�Q�[�W�̕\��
	DrawBox(WIDTH - 50, 80, WIDTH - 50 - width_gage, 80 + height_gage, color::red, TRUE);
	DrawBox(WIDTH - 50 - width_gage + ((float)life_point / (float)life_point_max * width_gage), 80, WIDTH - 50 - width_gage, 80 + height_gage,color::green,TRUE);
	DrawBox(WIDTH - 52 - width_gage, 60, WIDTH - 50 - width_gage + 20, 78, color::gray2, TRUE);
	DrawFormatString(WIDTH - 50 - width_gage, 60, color::black, "�G");

	// �_���[�W�G�t�F�N�g�Ƃ��ē_�ł���悤�ɂ���
	if (damage_time == 0 || (damage_time) % 5  > 1) {
		DrawRotaGraph2(px + px_battery, py + py_battery, 0, 8, 0.8, angle + angle_battery, image_battery, TRUE);
		DrawRotaGraph(px, py, 1.0, angle, image, TRUE,TRUE);
	}
}