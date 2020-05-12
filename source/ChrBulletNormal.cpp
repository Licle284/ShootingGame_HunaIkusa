#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrBulletNormal.h"



ChrBulletNormal::ChrBulletNormal():ChrBullet(getBulletType())
{
}

ChrBulletNormal::~ChrBulletNormal()
{
}

// �����^����������
void ChrBulletNormal::update() {
	px += vx;
	vy += gravity * delta_time;
	py += vy;
	ChrBullet::update();
}
