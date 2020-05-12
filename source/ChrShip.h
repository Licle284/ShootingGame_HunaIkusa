#pragma once
#include "ChrBullet.h"


// �D�N���X�@�e��ł��o���@�\��L����B�܂��Q�[���{�̃N���X�ցA���̃N���X�̖��ƃ^�C�v���e����^����B
// �g�̉e���ȂǑD�炵��������s�������Ȃǂ����̃N���X�Ōv�Z���A��̓I�Ȑ킢�͔h���N���X�Ɉ�C����B
class ChrShip : public Chr {

public:
	ChrShip();

protected:
	bool able_shot_flag;		// �e��łĂ��Ԃ�
	float shot_speed = 5.f;		// �e�̏������x
	int damage_time;			// �_���[�W�G�t�F�N�g�̎c�莞��

	int life_point;			// �D�̗̑�
	int life_point_max;		// �̗͂̍ő�l

	int width_for_angle = 20;	// �D�̌X���Z�o�p�̕��̔���

	int image_battery;		// �C��̉摜
	double angle_battery;	// �C��̑D�Ƃ̑��Ίp�x
	int px_battery;			// �C��ƑD�Ƃ̑��΍��W
	int py_battery = -3;	// �V

	int width_gage = 150;	// �̗͕\���p�̃Q�[�W�̕�
	int height_gage = 20;	// �Q�[�W����

public:

	virtual ChrType getChrType() = 0;	// �D�̉��̉����A�G�ƃv���C���[�Ŏ���

	virtual void hit();		// �Փˎ��̋���
	virtual void update();	// �ړ��Ȃǂ̋���
	virtual void draw() {};		// �`��

	// �e�^�C�v�A���A�ꔭ���Ƃ̔��ˊp�x�Ԋu����A�e�𐶐�����
	void bulletShot(BulletType type, int num, float interval);	
};

