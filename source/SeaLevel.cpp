#include "MyDefine.h"
#include "SeaLevel.h"
#include <math.h>


// �v�Z�� y = 0 ���_�̊C�ʂ���ʂ̒��ւ��炷
const float offsetY = (float)HEIGHT / 2.0 + 100.f;

// �����Ə�����
SeaLevel::SeaLevel(){
	init();
}

SeaLevel::~SeaLevel()
{
}

// �C�ʂ̌`�󏉊���
void  SeaLevel::init() {
	// x �����̐ݒ�
	for (int i = 0; i < N; i++) {
		float x = i * dx;
		seaX[i] = x;
	}

	// �C�ʂ̏������� y(x) �����߂�
	float initX = LENGTH / 2;
	for (int i = 0; i < N; i++) {
		float x = i * dx;
		// �K�E�X�֐���p���Ċ��炩��
		seaY[i] = PULSE_HEIGHT *
			expf(-(x - initX)*(x - initX) / (2 * PULSE_WIDTH * PULSE_WIDTH)) + offsetY;
		seaVY[i] = 0.0;		// �C�ʂ̏������x�[��
	}
	dt = 0.008;		// �C�ʂɑ΂��Ẵf���^�^�C��
}


//�C�ʂ̓���(�쓮��)  ��ʗ��[�� y �𓮂����B
void SeaLevel::updateLeftAndRightEnds() {
	// 0 : �� ,       1 : �E     �Ƃ���

	// �K�v�ϐ������p�ӂ���
	static float time[2] = { 0.f };
	static float time_period[2] = { 1.f, 1.f };
	static float wave_speed[2] = { 1.f,1.f };

	for (int i = 0; i < 2; i++) {
		// �O��̔g��������I���Ă��琶��
		if (time[i] == 0.0) {
			time_period[i] = 5.f + GetRand(100) / 10.f;	// �����������_���Ō��� 
			time[i] = time_period[i];					// ���ԕϐ��Ɏ������Z�b�g
			wave_speed[i] = (GetRand(20) / 20.f - 0.5f) * 0.5;	// �U���������_���Ō���	
		}

		// ���ԕϐ��̌��Z
		if (time[i] > 0) {
			time[i] -= delta_time;
		}
		// ���ԕϐ���0�ƂȂ�����g����������Ƃ�������
		else {
			time[i] = 0.0;
			if (i == 0) seaY[0] = offsetY;		// ���[�̍��W�����܂߂ɏ�����
			if (i == 1) seaY[N - 1] = offsetY;	// �덷�~�ςɋN������C�ʒ[�̋ɒ[�ȓ�����h��
		}

		// ���[�� y ���W�ψʂ̈ړ�
		if (i == 0) {
			seaY[0] += wave_speed[i] * sinf(time[i] / time_period[i] * 2 * PI);
		}
		if (i == 1) {
			seaY[N - 1] += wave_speed[i] * sinf(time[i] / time_period[i] * 2 * PI);
		}
	}
}


// �C�ʂ̓���(�퓮����)
void SeaLevel::updateSea() {
	// �g�̔���
	updateLeftAndRightEnds();

	// ���ʂ��v�Z
	float m = DENSITY * LENGTH / (N + 1);

	// �e���_ y(x) �ɂ�����Y�������͂̌v�Z�B�قڃI�C���[�@�ł��邽�ߕs����B
	for (int i = 1; i < N - 1; i++) {
		seaFY[i] = (seaY[i + 1] + seaY[i - 1] - 2.f * seaY[i]) * TENSION / dx - FRICTION * seaVY[i];
	}
	
	// ���[�ɂ͒��͂͂�����Ȃ��Ƃ���
	// (��ʓ��̒��_�Ɉ��������A�쓮���ז�����邱�Ƃ͂Ȃ�)
	seaFY[0] = 0.0;
	seaFY[N - 1] = 0.0;
	
	// �Z�o���ꂽ���͂���Ay �������x�A y �����ψʂ������Z�o
	for (int i = 0; i < N; i++) {
		seaVY[i] += seaFY[i] / m * dt;
		seaY[i] += seaVY[i] / m * dt;	// delta_time �ɂ���ƕs����
	}
}


// ����ꂽx-y���W�̂Ƃ���C�ʂ�`��
void SeaLevel::draw() {
	for (int i = 0; i < N - 1; i++) {
		int x = seaX[i]/dx;
		int y = seaY[i];
		DrawLineAA(x, y, x, HEIGHT, GetColor(50, 100, 250));
	}
}
