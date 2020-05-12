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

// �C�� y �Ǝ��g�̈ʒu y �Ƃ̕΍����k�߂�悤�ɓ������߁A�C�ʂ������悤�ȓ����ƂȂ�B
// 
void ChrBulletAlong::update() {
	px += 0.5 * vx;

	// �]��ɂ��C�ʂɑQ�߂�������ƁA�C��̌X���ƒe�̓������𗣂���̂ŁA�C�ʂւ̑Q�߂͗}���C��
	vy += (mSea->getSeaY((int)px) - py) * 0.001;	
	py += vy;
	ChrBullet::update();
}

