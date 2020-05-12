#pragma once
#include "MyDefine.h"



static const int N = WIDTH;	// ���l�v�Z�p���_���͉�ʂ̃s�N�Z�����Ƃ����B

// �C�ʃN���X�B�g�͐��l�v�Z�Ŋ���o���Ă���B��@�Ɋւ��ĉ��P�̗]�n����B

// ���l�v�Z�@�ɂ��ẮA
// �u�͊w�A���S���Y���ɂ��g�̃V�~�����[�V����(����̔g) - VCSSL�v
// https://www.vcssl.org/ja-jp/code/archive/0001/1100-string-wave/
// ���Q�l�Ƃ����B

class SeaLevel {
	
	// �C�ʂ̒��_�BN����ʏ��x�Ƃ݂Ȃ��� y = f(x)�̌`�Ƃ��ĕ\����B
	float seaX[N];	// �C�� x���W
	float seaY[N];	// �C�� y���W
	float seaVY[N];	// �C�� y�������x
	float seaFY[N];	// �C�� y��������

	// �e�������� (�p�����[�^�̓Q�[�����̌����ڂ��Q�l�Ɏ��s����Ō���)
	float LENGTH = 5.0f;		// ���̒���
	float DENSITY = 100.0f;		// ���x
	float TENSION = 1.3f;		// ����
	float FRICTION = 0.01f;		// �����W��
	float PULSE_WIDTH = 0.2f;	// �����g�̕�
	float PULSE_HEIGHT = -100.0f;	// �����g�̍���

	const float dx = LENGTH / (float)N;	// ��� 1 �s�N�Z��������̋���
	float dt;	// delta_time �i�[�p (delta_time�ł� �g�̌v�Z�����U���Ă��܂����Ƃ��������̂�dt�ŌŒ�Ƃ����B)

public:
	SeaLevel();
	~SeaLevel();

	void init();							// �g�̌`�󏉊���
	void updateLeftAndRightEnds();			// �g�̔������̋���(��ʗ��[�Ŕg�𔭐�)
	void updateSea();						// �g�̓`�d�̌v�Z���s���B
	int getSeaY(int x) { return seaY[x]; }	// �g�̍��� y(x) �̎擾

	void draw();	// �`��
};

