#pragma once


// �e�̔h���N���X�@�C�ʂɉ����Ĉړ�����B
class ChrBulletAlong : public ChrBullet
{
public:
	ChrBulletAlong();
	~ChrBulletAlong();

	virtual BulletType getBulletType() { return BULLET_ALONG; }	// ���g�̒e�^�C�v

	virtual void update();	// �C�ʂɉ����悤�ȋ���
};

