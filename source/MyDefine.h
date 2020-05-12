#pragma once
#include "DxLib.h"
#include <string.h>


//***�@�O���[�o���ϐ� ***//
constexpr int WIDTH = 640;		// ��ʕ�
constexpr int HEIGHT = 480;		// ��ʍ���
extern float delta_time;		// ���C�����[�v1�T�̎���
extern UINT start_time;			// delta_time�Z�o�p
constexpr float PI = 3.1415926f;// �~����



//*** �L�[���͊֌W ***//
//�V�EC����@�`�Q�[���v���O���~���O�̊ف` https://dixq.net/g/index.html�@���Q�l�Ƃ���
namespace key {
	extern char state[256];		// �A�v���P�[�V�������œ���̃L�[��� 
	extern int count[256];		// ����̃L�[�̓��͌p���J�E���g
	// �L�[�̏�ԍX�V
	inline static void update() {
		GetHitKeyStateAll(key::state);
		for (int i = 0; i < 256; i++) {
			if (state[i]) count[i]++;
			else count[i] = 0;
		}
	}

	//����̃L�[�̓��̓J�E���g��Ԃ�
	inline static int get(int key_state) {
		return count[key_state];
	}
}

//*** �F ***//
// �p�ɂɎg�p����\��̂��̂��܂Ƃ߂Ă���B
namespace color {
	const int white = GetColor(255, 255, 255);
	const int black = GetColor(0, 0, 0);
	const int red = GetColor(255, 0, 0);
	const int blue = GetColor(0, 0, 255);
	const int green = GetColor(0, 255, 0);
	const int gray = GetColor(128, 128, 128);
	const int gray2 = GetColor(200, 200, 200);
	const int yellow = GetColor(255, 255, 0);
}


