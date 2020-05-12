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

// 直線運動を行う
void ChrBulletStraight::update() {
	px += vx;
	py += vy;
	ChrBullet::update();
}
