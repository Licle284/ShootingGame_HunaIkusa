#include <iostream>
#include <list>
#include <map>

#include "DxLib.h"
#include "MyDefine.h"

#include "Chr.h"
#include "ChrShip.h"
#include "ChrShipPlayer.h"
#include "ChrShipEnemy.h"
#include "SeaLevel.h"
#include "GameManager.h"


// �^�C�g���V�[���Ƃ��ăC���X�^���X���B
// �������g�̃|�C���^�����J�p�̃Q�[���}�l�[�W���[�|�C���^�Ɋi�[
GameManager::GameManager()
	:game_scene(SCENE_TITLE)
{
	gameManager = this;
}

GameManager::~GameManager()
{
}

// �L�����N�^�[���X�g�ǉ��@�\
void GameManager::addList(Chr* c) {
	chr_list.push_back(c);
}


int GameManager::Initialize() {
	//Dxlib�̐ݒ�
	ChangeWindowMode(TRUE);				// �E�B���h�E���[�h�ɐݒ�
	SetGraphMode(WIDTH, HEIGHT, 32);	// ��ʃT�C�Y�̌��� 
	SetDrawMode(DX_DRAWMODE_BILINEAR);	// �o�C���j�A�`��
	SetDrawScreen(DX_SCREEN_BACK);		// ����ʐݒ�
	if (DxLib_Init() == 1) return -1;	// DX���C�u����������

	//�^�C�g���p�̑D�̉摜
	image_ship_p = LoadGraph("ship_player.png");
	image_ship_e = LoadGraph("ship_enemy.png");
	
	//�w�i���[�h
	image_back1= LoadGraph("back1.jpg");
	image_back2 = LoadGraph("back2.jpg");
	image_back3 = LoadGraph("back4.jpg");

	//���f�[�^�̃��[�h
	sound_shot_e = LoadSoundMem("se_maoudamashii_system42.mp3");
	sound_shot_p = LoadSoundMem("se_maoudamashii_system43.mp3");
	sound_bigshot = LoadSoundMem("se_maoudamashii_element_fire09.mp3");
	sound_damage = LoadSoundMem("se_maoudamashii_battle11.mp3");
	sound_enter = LoadSoundMem("se_maoudamashii_system38.mp3");
	music_battle = LoadSoundMem("bgm_maoudamashii_8bit11.mp3");
	music_title = LoadSoundMem("bgm_maoudamashii_8bit24.mp3");
	music_lose = LoadSoundMem("bgm_maoudamashii_8bit20.mp3");

	// �Q�[���̏I���t���O�B�܂��Ă���
	end_flag = false;

	// �C�ʂ̐���
	mSea = new SeaLevel();

	// �t�H���g�ݒ�
	font_big = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_EDGE, -1, 4);
	font_bigbig = CreateFontToHandle(NULL, 120, 3, DX_FONTTYPE_EDGE, -1, 4);

	return 0;
}

void GameManager::Loop() {
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�Q�[���I��
		if (key::get(KEY_INPUT_ESCAPE) > 1) end_flag = true;
		if (end_flag) {
			if (CheckSoundMem(music_title))StopSoundMem(music_title);
			if (CheckSoundMem(music_battle))StopSoundMem(music_battle);
			if (CheckSoundMem(music_lose))StopSoundMem(music_lose);
			break;
		}

		delta_time = (GetNowCount() - start_time) / 1000.f;	// �f���^�^�C���X�V
		start_time = GetNowCount();							// ���ݎ����̕ۑ�
		key::update();										//�L�[���̍X�V

		// �Q�[���V�[�����Ƃ̕���_
		switch (game_scene) {
		case SCENE_TITLE:
			SceneTitle();
			break;
		case SCENE_BATTLE:
			SceneBattle();
			break;
		case SCENE_RESULT:
			SceneResult();
			break;
		case SCENE_MANUAL:
			SceneManual();
			break;
		default:
			end_flag = true;
		}
	}
}


void GameManager::SceneTitle() {
	static int count = 0;	// �^�C�g������p
	if (!CheckSoundMem(music_title)) {
		PlaySoundMem(music_title,DX_PLAYTYPE_BACK);
	}
	
	// �����V�[���ւ̐؂�ւ�
	if (key::get(KEY_INPUT_M) == 1) {
		game_scene = SCENE_MANUAL;	// �}�j���A���V�[����
		return;
	}

	// �o�g���V�[���̐ؑց@����
	if (key::get(KEY_INPUT_RETURN) == 1) {
		StopSoundMem(music_title);
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK);
		loser = TYPE_NONE;			// �s�k�҂��N���A����
		game_scene = SCENE_BATTLE;	// �Q�[���V�[�����o�g����
		InitForBattle();			// �o�g���V�[���̂��߂̏���������
		return;
	}

	// �w�i�ƃ^�C�g���̕`��
	DrawGraph(0, 0, image_back2, TRUE);
	DrawStringToHandle(WIDTH/3 + 100 * sin((float)(++count)/60.f), 
						HEIGHT/6 + 50 * fabs(cos((float)count/60.f)), 
						"�D��", color::black, font_bigbig, color::gray);
	// �e������̕`��
	char* str = "";
	if (gamemode == 4) str = "�₳����";
	if (gamemode == 3) str = "����΂낤";
	if (gamemode == 2) str = "�Ă��킢��";
	if (gamemode == 1) str = "�ŏI���킾 !!";
	DrawFormatString(WIDTH / 3, HEIGHT * 10 / 16, color::black, "��Փx: %d  %s", 5 - gamemode, str);
	DrawString(WIDTH / 3, HEIGHT * 11 / 16, "  �n�߂� : ENTER", color::black);
	DrawString(WIDTH / 3, HEIGHT * 12 / 16, "������� : M", color::black);
	DrawString(WIDTH / 3, HEIGHT * 13 / 16, "  �I��� : ESC", color::black);

	// �A�N�Z�T���[�Ƃ��đD��`��
	DrawRotaGraph(100, HEIGHT - 100, 3.0, 0.0,image_ship_p,TRUE);
	DrawRotaGraph(WIDTH - 100, HEIGHT - 100,3.0, 0.0,image_ship_e, TRUE,TRUE);
}


void GameManager::InitForBattle() {
	mSea->init();						// �C�ʂ̏�����
	Chr* player = new ChrShipPlayer();	// �v���C���[����
	Chr* enemy = new ChrShipEnemy(gamemode);	// �G�̐���

	// �L�����N�^�[���X�g�֒ǉ�
	chr_list.push_back(player);
	chr_list.push_back(enemy);
}


void GameManager::SceneBattle() {
	if (!CheckSoundMem(music_battle)) {
		PlaySoundMem(music_battle, DX_PLAYTYPE_LOOP);	
	}

	// �w�i�ƕ�����̕`��
	DrawGraph(0, 0, image_back1, TRUE);
	DrawFormatString(5, 20, color::black, " [�ړ�:���E�����L�[] [�C��X��:�㉺�L�[] [����:�X�y�[�X] [�e�̐ؑ�:W]");

	// dead_flag�̗����Ă���L�������폜
	chr_list.remove_if([](Chr* chr) {return chr->isDead(); });
	
	// �o�g���I��	�s�k�҂��m��
	if (loser != TYPE_NONE) {
		game_scene = SCENE_RESULT;

		// ���X�g���N���A�����̂��v�f���폜����
		chr_list.clear();
		for (auto& chr : chr_list) {
			delete chr;
		}
		StopSoundMem(music_battle);
		return;
	}

	// �C�ʂɊւ��镔��
	mSea->updateSea();
	mSea->draw();

	// �L�����N�^�[�S���̃A�b�v�f�[�g
	for (auto& chr : chr_list) {
		chr->update();
	}
	// �L�����N�^�[�S���̕`��
	for (auto& chr : chr_list) {
		chr->draw();
	}

	// �L�����N�^�[�S���̓����蔻��
	for (auto& src : chr_list) {
		// �v���C���[���� dst �Ƃ��ď��� src �Ƃ��Ă͏������Ȃ�
		if(src->getChrType() == TYPE_BULLET || src->getChrType() == TYPE_ENEMY){
			for (auto& dst : chr_list) {
				// ��҂�����̃|�C���^�łȂ��A����̃^�C�v�ł��Ȃ���Ώ������s��
				if (src != dst && src->getChrType() != dst->getChrType()) {
					// �����蔻����s��
					if (src->HitTest(dst)) {
						// �Փˎ�����
						src->hit();
						dst->hit();
					}
				}
			}
		}
	}
}



void GameManager::SceneResult() {
	// �����̌��ʂɂ����BGM��ύX����B
	static bool music_flag = false;
	if (!music_flag) {
		if (loser == TYPE_PLAYER) {
			PlaySoundMem(music_lose, DX_PLAYTYPE_BACK);
		}
		else { 
			PlaySoundMem(music_title, DX_PLAYTYPE_BACK);
		}
		music_flag = true;
	}

	// ���ʉ�ʏI���@�^�C�g���V�[����
	if (key::get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK);
		game_scene = SCENE_TITLE;
		if (loser != TYPE_PLAYER && gamemode > 1) gamemode--;	// �Q�[���̓�Փx�X�V
		if (CheckSoundMem(music_lose)) {
			StopSoundMem(music_lose);
		}
		music_flag = false;
		return;
	}

	// �w�i�`��
	DrawGraph(0, 0,image_back1, TRUE);

	// ���s�̔���@�`��
	if (loser == TYPE_PLAYER) {
		DrawFormatStringToHandle(70, 180, color::gray, font_big, "�c�O�ł�...");
	}
	else if (loser == TYPE_ENEMY) {
		DrawFormatStringToHandle(120, 180, GetColor(255,100,0), font_big, "���� !!!");
	}

	// ���̑��K�v�ȕ�����@�`��
	DrawBox(WIDTH/2 - 130, HEIGHT/2 + 70, WIDTH/2 + 110, HEIGHT/2 + 160, color::gray2,TRUE);
	DrawString(WIDTH / 3, HEIGHT * 11 / 16, "�^�C�g���֖߂� : ENTER", color::black);
	DrawString(WIDTH / 3, HEIGHT * 12 / 16, "�I��� : ESC", color::black);
}


void GameManager::SceneManual() {
	// �^�C�g���V�[���֖߂�
	if (key::get(KEY_INPUT_RETURN) == 1) {
		game_scene = SCENE_TITLE;
		return;
	}

	// �w�i�`��
	DrawGraph(0,0,image_back3, TRUE);

	// �e�L�X�g�\��
	DrawString(150, 140, "     �悤����\n    �����ł̓Q�[�����̑�����@���Љ�܂��B\n"
		"1. �����L�[�́u���v�Ɓu�E�v�őD�𓮂���!\n"
		"2. �����L�[�́u��v�Ɓu���v�ŖC��̊p�x�𒲐�!\n"
		"3. �u�X�y�[�X�L�[�v�Œe�𔭎�! \n"
		"4. ���˂���e��4��ށB�uW�v�������Đ؂�ւ��悤!\n"
		"5. �u�X�y�[�X�L�[�v�𒷉�������ƃ`���[�W�e�����Ă�B\n"
		"   ����̃Q�[�W�̒����ɂ���ă`���[�W�e�̎p�͗l�X!!\n"
		"6. �G�̑D�ɂԂ����Ă͂����܂���B��_���[�W�ł��B\n"
		"�S����4�̓�Փx�A�N�͂ǂ��܂ŃN���A�ł��邩��?\n\n\n"
		"�^�C�g���֖߂� : ENTER", color::gray);
}


// �Q�[���̏I������
void GameManager::End() {
	delete mSea;
	DxLib_End();
}


