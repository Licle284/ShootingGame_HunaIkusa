#pragma once


// �G�̑D�N���X�@
class ChrShipEnemy : public ChrShip {
	
protected:
	virtual ChrType getChrType() { return TYPE_ENEMY; }

	BulletType bullet_type;		// �g�p����e�̃^�C�v
	int level_of_enemy;	// �G�̃��x���BDxLib�̗���������ɓ���Ďg���A�l���Ⴂ�ق��������Ƃ��Ă���B

public:
	ChrShipEnemy(int gamelv);	// �������x����n���ēG�D�𐶐�

	void update();		// �G�̋���
	void draw();		// �G���̃A�N�Z�T���[�`��p(�̗̓Q�[�W�Ȃ�)
};

