#pragma once


// �e�̔h���N���X�@�^�����ɔ�Ԓe
class ChrBulletStraight : public ChrBullet
{
public:
	ChrBulletStraight();
	~ChrBulletStraight();
	virtual BulletType getBulletType() { return BULLET_STRAIGHT; }	// �e�^�C�v�擾

	virtual void update();	// �ړ��Ȃǂ̋���
};

