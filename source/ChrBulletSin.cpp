#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrBulletSin.h"

#include <math.h>



ChrBulletSin::ChrBulletSin():ChrBullet(getBulletType())
{
}

ChrBulletSin::~ChrBulletSin()
{
}

void ChrBulletSin::update() {
	// x�����̈ړ��ɔ��� sin �������N�����B
	px += vx;
	py += vy * sin(2 * PI * (float)px /100.f) + vy/vx;
	ChrBullet::update();
}