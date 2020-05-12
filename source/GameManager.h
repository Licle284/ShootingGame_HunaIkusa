#pragma once
#include <list>
#include "Chr.h"


// �C�ʃN���X�̐錾
class SeaLevel;
// �L�����N�^�N���X�̐錾
class Chr;

// �Q�[�����̃V�[���ؑւɗp����B
enum GameScene {
	SCENE_TITLE,
	SCENE_BATTLE,
	SCENE_RESULT,
	SCENE_MANUAL,
};

// �e�X�̃N���X���݂��̃f�[�^��K�v�Ƃ���Ƃ��A�B��̃Q�[���}�l�[�W����ʂ��悤�ɂ�����������
// static�N���X �Ƃ����B
static class GameManager {
private:
	GameScene game_scene;	// ���݂̃V�[��������B
	bool end_flag;		// �Q�[���I���t���O
	ChrType loser;		// �s�k�����L�����̃^�C�v���i�[����B

	std::list<Chr*> chr_list;	// �L�����N�^�����߂郊�X�g�B�ꊇ�����p�B

	int gamemode = 4;	// �Q�[���̓�Փx�B4 ���� 1 �ɂȂ�ɂ����Ȃ�

	// �e�t�H���g
	int font_big;
	int font_bigbig;
	// �^�C�g���p�@�D�̉摜
	int image_ship_p;
	int image_ship_e;
	// �w�i�摜
	int image_back1;
	int image_back2;
	int image_back3;


public:
	GameManager();
	~GameManager();

	static GameManager* gameManager;	// �|�C���^��ʂ��ăN���X�Ԃ̏�������肷��B
	
	// �e�����f�[�^
	int sound_shot_p;
	int sound_shot_e;
	int sound_bigshot;
	int sound_damage;
	int sound_enter;
	int music_battle;
	int music_title;
	int music_lose;
	

	void addList(Chr*);		// �L�����N�^���ꊇ�����p���X�g�֒ǉ�
	void setLoser(ChrType ct) { loser = ct;	};	// �s�k�҂̃^�C�v���Z�b�g����

	int Initialize();	// �Q�[��������
	void Loop();		// �Q�[���̃��C�����[�v
	void End();			// �Q�[���I��

	// �e�V�[���̃��\�b�h
	void SceneTitle();
	void SceneBattle();
	void SceneResult();
	void SceneManual();

	void InitForBattle();	// �o�g���V�[���̏�����

	SeaLevel* mSea;		// �C�ʃN���X�̃|�C���^�B�D�������̌v�Z�ɗp����B
};

