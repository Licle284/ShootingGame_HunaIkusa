#pragma once
#include <list>
#include "Chr.h"


// 海面クラスの宣言
class SeaLevel;
// キャラクタクラスの宣言
class Chr;

// ゲーム中のシーン切替に用いる。
enum GameScene {
	SCENE_TITLE,
	SCENE_BATTLE,
	SCENE_RESULT,
	SCENE_MANUAL,
};

// 各々のクラスが互いのデータを必要とするとき、唯一のゲームマネージャを通すようにしかったため
// staticクラス とした。
static class GameManager {
private:
	GameScene game_scene;	// 現在のシーンを入れる。
	bool end_flag;		// ゲーム終了フラグ
	ChrType loser;		// 敗北したキャラのタイプを格納する。

	std::list<Chr*> chr_list;	// キャラクタを収めるリスト。一括処理用。

	int gamemode = 4;	// ゲームの難易度。4 から 1 になるにつれ難しくなる

	// 各フォント
	int font_big;
	int font_bigbig;
	// タイトル用　船の画像
	int image_ship_p;
	int image_ship_e;
	// 背景画像
	int image_back1;
	int image_back2;
	int image_back3;


public:
	GameManager();
	~GameManager();

	static GameManager* gameManager;	// ポインタを通してクラス間の情報をやり取りする。
	
	// 各音源データ
	int sound_shot_p;
	int sound_shot_e;
	int sound_bigshot;
	int sound_damage;
	int sound_enter;
	int music_battle;
	int music_title;
	int music_lose;
	

	void addList(Chr*);		// キャラクタを一括処理用リストへ追加
	void setLoser(ChrType ct) { loser = ct;	};	// 敗北者のタイプをセットする

	int Initialize();	// ゲーム初期化
	void Loop();		// ゲームのメインループ
	void End();			// ゲーム終了

	// 各シーンのメソッド
	void SceneTitle();
	void SceneBattle();
	void SceneResult();
	void SceneManual();

	void InitForBattle();	// バトルシーンの初期化

	SeaLevel* mSea;		// 海面クラスのポインタ。船が挙動の計算に用いる。
};

