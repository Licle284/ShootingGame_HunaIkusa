#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrBulletStraight.h"



ChrBulletStraight::ChrBulletStraight():ChrBullet(getBulletType())
{
}


ChrBulletStraight::~ChrBulletStraight()
{
}

// �����^�����s���B
void ChrBulletStraight::update() {
	px += vx;
	py += vy;
	ChrBullet::update();
}