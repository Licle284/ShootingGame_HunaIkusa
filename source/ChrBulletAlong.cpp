#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrBullet.h"
#include "ChrBulletAlong.h"



ChrBulletAlong::ChrBulletAlong():ChrBullet(getBulletType())
{
}

ChrBulletAlong::~ChrBulletAlong()
{
}

// 海面 y と自身の位置 y との偏差を縮めるように動くため、海面を沿うような動きとなる。
// 
void ChrBulletAlong::update() {
	px += 0.5 * vx;

	// 余りにも海面に漸近しすぎると、砲台の傾きと弾の動きが解離するので、海面への漸近は抑え気味
	vy += (mSea->getSeaY((int)px) - py) * 0.001;	
	py += vy;
	ChrBullet::update();
}

