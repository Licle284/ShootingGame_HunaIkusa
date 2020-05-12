#pragma once
#include "ChrBullet.h"
#include <vector>


// �l���L�[�{�[�h���ő���D�̃N���X
class ChrShipPlayer : public ChrShip{
protected:
	virtual ChrType getChrType() { return TYPE_PLAYER; }	// �L�����N�^�[�^�C�v�̃Q�b�^�[
	
	std::vector<BulletType> bullet_vec;		// �g�p����e�̃^�C�v���i�[����(����͏�ɑS�Ċ܂܂���)
	int now_vec_num;	// ���݂ǂ̒e�^�C�v�������Ă��邩�𐮐��Ŏ���(���Z�ɂ��e�^�C�v�ύX�̂��ߗp��)
	BulletType now_bullet_type;		// ���݂̒e�^�C�v�������B�����؂�ւ��Ēe�𕡐���ވ����B
	float bullet_charge = 0;		// �`���[�W�V���b�g�p�̃J�E���^�B���ԏ�񂪓���B

public:
	ChrShipPlayer();

	void hit();		// �Փˎ��̏���

	void update();	// �L�����N�^�[���쓙
	void draw();	// �`��(�̗̓Q�[�W��)
};

