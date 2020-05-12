#include "MyDefine.h"

#include "Chr.h"
#include "ChrShip.h"
#include "ChrShipPlayer.h"

#include "GameManager.h"
#include "ChrBullet.h"
#include <vector>
#include <string>

// �Q�[���}�l�[�W���[���̉�
GameManager* GameManager::gameManager;


ChrShipPlayer::ChrShipPlayer() : ChrShip() {
	setImage("ship_player.png");			// �摜
	setPosition(WIDTH / 4, HEIGHT / 2);		// �ʒu��ʍ��ɃZ�b�g
	damage_time = 0;						// �_���[�W�c�莞�Ԃ�0
	chr_type = TYPE_PLAYER;					// �L�����^�C�v
	life_point_max = 230;					// �̗͂̍ő�l
	life_point = life_point_max;			// �̗͂��ő�l�ɃZ�b�g
	angle_battery = 0.f;					// �C���(�D�Ƃ�)���Ίp�x�Z�b�g
	px_battery = 3;		// �C���D�̒��S����E�ɂ��炷

	//�g�p����e�̃^�C�v
	bullet_vec.push_back(BULLET_NORMAL);
	bullet_vec.push_back(BULLET_STRAIGHT);
	bullet_vec.push_back(BULLET_ALONG);
	bullet_vec.push_back(BULLET_SIN);
	now_bullet_type = bullet_vec[0];
}

// �v���C���[�͂����蔻��L���������ɕt���A�u�G�v��10�{�̃_���[�W���󂯂�B
// ����đ̓�����(�݂��������蔻��L���ƂȂ�_���[�W���󂯂�)�͕s���ƂȂ�B
// ����ɒe�̍U���͂��r�I���߂ɐݒ肵��
void ChrShipPlayer::hit() {
	ChrShip::hit();
	life_point -= 10;
}


void ChrShipPlayer::update() {
	if (damage_time > 0) {
		damage_time--;
	}
	static bool spacekey_flag = false;	// �X�y�[�X�L�[��������Ă������ǂ�������������


	// x�����ړ�
	if (key::get(KEY_INPUT_LEFT) > 1) px -= 2;
	if (key::get(KEY_INPUT_RIGHT) > 1) px += 2;
	// �C��p�x����
	if (key::get(KEY_INPUT_UP) > 1)  angle_battery -= PI / 90;
	if (key::get(KEY_INPUT_DOWN) > 1)  angle_battery += PI / 90;
	// �C��p�x����
	if (angle_battery < -PI / 2.f) angle_battery = -PI / 2.f;
	if (angle_battery > 0.f) angle_battery = 0.f;

	// ���e�̎�ސؑ�
	if (key::get(KEY_INPUT_W) == 1) {
		static int num = 0;
		num++;
		num = num % bullet_vec.size();
		now_bullet_type = bullet_vec[num];
	}
	
	// �`���[�W�V���b�g�@�X�y�[�X�L�[���������Ԃɂ��Z���ω�
	if ((spacekey_flag && (key::get(KEY_INPUT_SPACE) == 0))) {
		spacekey_flag = false;

		// ���t���[���A��(�Œ�������)
		if (bullet_charge > 9) {
			spacekey_flag = true;
			bulletShot(now_bullet_type, 0, 0.4f);
			bullet_charge -= delta_time * 0.5;
		}
		// ���ˏ�ɔ���
		else if (bullet_charge > 8) {
			bulletShot(now_bullet_type, 20, 0.1f);
			bulletShot(now_bullet_type, 40, 0.05f);
			bullet_charge -= delta_time * 0.5;
		}
		// �e�̏W���̂���B
		else if (bullet_charge > 4) {
			bulletShot(now_bullet_type, 110, 0.001f);
			bullet_charge = 0.f;
		}
		// ���ˏ󔭎�
		else if (bullet_charge > 2) {
			bulletShot(now_bullet_type, 10, 0.25f);
			bulletShot(now_bullet_type, 3, 0.2f);
			bullet_charge = 0.f;
		}
		// �O���̂ݕ��ˍU��
		else if (bullet_charge > 0.4) {
			bulletShot(now_bullet_type, 5, 0.1f);
			bullet_charge = 0.f;
		}
		// �ʏ풷�����U��
		else if (bullet_charge > 0) {
			bulletShot(now_bullet_type, 0, 0.f);
		}
		// �`���[�W���� 4 �ȏ�Ō��ʉ��ω�
		if(bullet_charge > 4)PlaySoundMem(GameManager::gameManager->sound_bigshot, DX_PLAYTYPE_BACK);
		else PlaySoundMem(GameManager::gameManager->sound_shot_p, DX_PLAYTYPE_BACK);
	}

	// �`���[�W�V���b�g����
	else if (key::get(KEY_INPUT_SPACE) > 1) {
		spacekey_flag = true;
		bullet_charge += delta_time;
		if (bullet_charge > 11) bullet_charge = 10.f;
	}
	
	// �e����� �P��
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

	// �D�Ƃ��ċ��ʂ̓���
	ChrShip::update();
}


void ChrShipPlayer::draw() {
	// HP�Q�[�W
	DrawBox(50, 80, 50 + width_gage, 80 + height_gage, color::red, TRUE);
	DrawBox(50, 80, 50 + (float)life_point / (float)life_point_max * width_gage, 80 + height_gage, color::green, TRUE);
	DrawBox(48, 58, 102, 78, color::gray2, TRUE);
	DrawFormatString(50, 60, color::black, "���Ȃ�");

	// �`���[�W�Q�[�W
	DrawString(0, 110, "Charge", color::black);
	DrawBox(60, 108, 60 + width_gage, 122, color::gray, TRUE);
	int color_gage;
	if (bullet_charge > 4) color_gage = GetColor(255, 100, 0);
	else if (bullet_charge > 2) color_gage = GetColor(255, 220, 0);
	else color_gage = GetColor(0,255,100);
	DrawBox(60, 110, 60 + bullet_charge/11.f * width_gage, 120, color_gage, TRUE);
	
	// �e�̎�ށ@�\������
	DrawBox(60, 128, 132, 152, color::gray, TRUE);
	if (now_bullet_type == BULLET_NORMAL) DrawFormatString(62, 130, color::yellow, "�������e");
	else if(now_bullet_type == BULLET_STRAIGHT) DrawFormatString(62, 130,GetColor(255,0,255), "�����e");
	else if (now_bullet_type == BULLET_ALONG) DrawFormatString(62, 130, GetColor(255,230,0), "�C�ʒe");
	else if (now_bullet_type == BULLET_SIN) DrawFormatString(62, 130, color::white, "�����g�i");

	// �_���[�W�G�t�F�N�g�Ƃ��ē_�ł���悤�ɂ���
	if (damage_time == 0 || (damage_time) % 5 > 1) {
		DrawRotaGraph2(px + px_battery, py + py_battery, 0, 8, 0.8, angle + angle_battery, image_battery, TRUE);
		DrawRotaGraph(px, py, 1.0, angle, image, TRUE, FALSE);

	}
}

