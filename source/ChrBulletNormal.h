#pragma once

// �e�̔h���N���X�@��������`���B���̉^����ʏ�Ƃ������ߖ��O��NORMAL�ƂȂ��Ă���B
class ChrBulletNormal:public ChrBullet
{
public:
	ChrBulletNormal();
	~ChrBulletNormal();
	virtual BulletType getBulletType() { return BULLET_NORMAL; }	// �e�^�C�v�擾
	virtual void update();		// ����������
};

