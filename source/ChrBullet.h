#pragma once
#include "Chr.h"

// �����̈قȂ�4��ނ̒e��p�ӂ����B
enum BulletType {
	BULLET_NORMAL,
	BULLET_ALONG,
	BULLET_STRAIGHT,
	BULLET_SIN,

	BULLET_TYPE_NUM,
};

// �e�N���X�ł͏Փˎ��̋�����`��A���[�h�ς݂̒e�̉摜�Ȃǂ��܂Ƃ߂Ă���B
class ChrBullet : public Chr {
	static int loaded_bullet_image[BULLET_TYPE_NUM];	// ���[�h�ς݉摜�̊i�[�ꏊ
protected:
	float gravity = 2.f;	// �d�͉����x���`�A����͑D���d�͂𖳎����Ă���ׁA�e�N���X�Ɏ��������B
	

public:
	ChrBullet(BulletType type);	// �R���X�g���N�^�ł͒e�̃^�C�v�������Ɏw�肷��B
	~ChrBullet();

	void setBulletImage(char* filename);	// �摜�Z�b�^�[
	virtual BulletType getBulletType() { return BULLET_NORMAL; }	// �^�C�v�Q�b�^�[

	virtual void hit();			// �Փˎ��̋���
	// �e�S�̂ɋ��ʂ���s���͈͐����̂ݎ���
	virtual void update() { if (px > WIDTH || px < 0 || py > HEIGHT || py < -10000) dead(); }	// �ړ��Ȃǂ̋���
	virtual void draw();		// �`��
};

