#pragma once

// �e�̔h���N���X�@�����g��g�ݍ��񂾓��������e
class ChrBulletSin :public ChrBullet
{
public:
	ChrBulletSin();
	~ChrBulletSin();

	virtual BulletType getBulletType() { return BULLET_SIN; }	// �e�^�C�v�擾
	virtual void update();	// �����g���Q�l�ɂ�������
};

