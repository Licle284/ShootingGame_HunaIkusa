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

// 放物運動をさせる
void ChrBulletNormal::update() {
	px += vx;
	vy += gravity * delta_time;
	py += vy;
	ChrBullet::update();
}
