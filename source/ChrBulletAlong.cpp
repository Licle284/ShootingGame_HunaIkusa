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

// ŠC–Ê y ‚ÆŽ©g‚ÌˆÊ’u y ‚Æ‚Ì•Î·‚ðk‚ß‚é‚æ‚¤‚É“®‚­‚½‚ßAŠC–Ê‚ð‰ˆ‚¤‚æ‚¤‚È“®‚«‚Æ‚È‚éB
// 
void ChrBulletAlong::update() {
	px += 0.5 * vx;

	// —]‚è‚É‚àŠC–Ê‚É‘Q‹ß‚µ‚·‚¬‚é‚ÆA–C‘ä‚ÌŒX‚«‚Æ’e‚Ì“®‚«‚ª‰ð—£‚·‚é‚Ì‚ÅAŠC–Ê‚Ö‚Ì‘Q‹ß‚Í—}‚¦‹C–¡
	vy += (mSea->getSeaY((int)px) - py) * 0.001;	
	py += vy;
	ChrBullet::update();
}

