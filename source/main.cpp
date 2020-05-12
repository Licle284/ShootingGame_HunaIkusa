#include "DxLib.h"
#include "MyDefine.h"

#include "GameManager.h"
#include <math.h>


//*** MyDefine.h �̊O���錾�̎��� ***//
float delta_time = 0.f;
UINT start_time = 0;
char key::state[256] = { 0 };
int key::count[256] = { 0 };


// ���C���֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	GameManager gameManager;				// �Q�[���}�l�[�W���[�̐���
	if (gameManager.Initialize() == 0) {	// �Q�[���}�l�[�W���[������
		gameManager.Loop();					// ���C�����[�v
	}
	gameManager.End();						// �I������
	return 0;
}