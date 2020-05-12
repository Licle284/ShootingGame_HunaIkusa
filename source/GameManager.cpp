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


// タイトルシーンとしてインスタンス化。
// 自分自身のポインタを公開用のゲームマネージャーポインタに格納
GameManager::GameManager()
	:game_scene(SCENE_TITLE)
{
	gameManager = this;
}

GameManager::~GameManager()
{
}

// キャラクターリスト追加機能
void GameManager::addList(Chr* c) {
	chr_list.push_back(c);
}


int GameManager::Initialize() {
	//Dxlibの設定
	ChangeWindowMode(TRUE);				// ウィンドウモードに設定
	SetGraphMode(WIDTH, HEIGHT, 32);	// 画面サイズの決定 
	SetDrawMode(DX_DRAWMODE_BILINEAR);	// バイリニア描画
	SetDrawScreen(DX_SCREEN_BACK);		// 裏画面設定
	if (DxLib_Init() == 1) return -1;	// DXライブラリ初期化

	//タイトル用の船の画像
	image_ship_p = LoadGraph("ship_player.png");
	image_ship_e = LoadGraph("ship_enemy.png");
	
	//背景ロード
	image_back1= LoadGraph("back1.jpg");
	image_back2 = LoadGraph("back2.jpg");
	image_back3 = LoadGraph("back4.jpg");

	//音データのロード
	sound_shot_e = LoadSoundMem("se_maoudamashii_system42.mp3");
	sound_shot_p = LoadSoundMem("se_maoudamashii_system43.mp3");
	sound_bigshot = LoadSoundMem("se_maoudamashii_element_fire09.mp3");
	sound_damage = LoadSoundMem("se_maoudamashii_battle11.mp3");
	sound_enter = LoadSoundMem("se_maoudamashii_system38.mp3");
	music_battle = LoadSoundMem("bgm_maoudamashii_8bit11.mp3");
	music_title = LoadSoundMem("bgm_maoudamashii_8bit24.mp3");
	music_lose = LoadSoundMem("bgm_maoudamashii_8bit20.mp3");

	// ゲームの終了フラグ。折っておく
	end_flag = false;

	// 海面の生成
	mSea = new SeaLevel();

	// フォント設定
	font_big = CreateFontToHandle(NULL, 80, 3, DX_FONTTYPE_EDGE, -1, 4);
	font_bigbig = CreateFontToHandle(NULL, 120, 3, DX_FONTTYPE_EDGE, -1, 4);

	return 0;
}

void GameManager::Loop() {
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ゲーム終了
		if (key::get(KEY_INPUT_ESCAPE) > 1) end_flag = true;
		if (end_flag) {
			if (CheckSoundMem(music_title))StopSoundMem(music_title);
			if (CheckSoundMem(music_battle))StopSoundMem(music_battle);
			if (CheckSoundMem(music_lose))StopSoundMem(music_lose);
			break;
		}

		delta_time = (GetNowCount() - start_time) / 1000.f;	// デルタタイム更新
		start_time = GetNowCount();							// 現在時刻の保存
		key::update();										//キー情報の更新

		// ゲームシーンごとの分岐点
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
	static int count = 0;	// タイトル動作用
	if (!CheckSoundMem(music_title)) {
		PlaySoundMem(music_title,DX_PLAYTYPE_BACK);
	}
	
	// 説明シーンへの切り替え
	if (key::get(KEY_INPUT_M) == 1) {
		game_scene = SCENE_MANUAL;	// マニュアルシーンへ
		return;
	}

	// バトルシーンの切替　準備
	if (key::get(KEY_INPUT_RETURN) == 1) {
		StopSoundMem(music_title);
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK);
		loser = TYPE_NONE;			// 敗北者をクリアする
		game_scene = SCENE_BATTLE;	// ゲームシーンをバトルへ
		InitForBattle();			// バトルシーンのための初期化処理
		return;
	}

	// 背景とタイトルの描画
	DrawGraph(0, 0, image_back2, TRUE);
	DrawStringToHandle(WIDTH/3 + 100 * sin((float)(++count)/60.f), 
						HEIGHT/6 + 50 * fabs(cos((float)count/60.f)), 
						"船戦", color::black, font_bigbig, color::gray);
	// 各文字列の描画
	char* str = "";
	if (gamemode == 4) str = "やさしい";
	if (gamemode == 3) str = "がんばろう";
	if (gamemode == 2) str = "てごわいよ";
	if (gamemode == 1) str = "最終決戦だ !!";
	DrawFormatString(WIDTH / 3, HEIGHT * 10 / 16, color::black, "難易度: %d  %s", 5 - gamemode, str);
	DrawString(WIDTH / 3, HEIGHT * 11 / 16, "  始める : ENTER", color::black);
	DrawString(WIDTH / 3, HEIGHT * 12 / 16, "操作説明 : M", color::black);
	DrawString(WIDTH / 3, HEIGHT * 13 / 16, "  終わる : ESC", color::black);

	// アクセサリーとして船を描画
	DrawRotaGraph(100, HEIGHT - 100, 3.0, 0.0,image_ship_p,TRUE);
	DrawRotaGraph(WIDTH - 100, HEIGHT - 100,3.0, 0.0,image_ship_e, TRUE,TRUE);
}


void GameManager::InitForBattle() {
	mSea->init();						// 海面の初期化
	Chr* player = new ChrShipPlayer();	// プレイヤー生成
	Chr* enemy = new ChrShipEnemy(gamemode);	// 敵の生成

	// キャラクターリストへ追加
	chr_list.push_back(player);
	chr_list.push_back(enemy);
}


void GameManager::SceneBattle() {
	if (!CheckSoundMem(music_battle)) {
		PlaySoundMem(music_battle, DX_PLAYTYPE_LOOP);	
	}

	// 背景と文字列の描画
	DrawGraph(0, 0, image_back1, TRUE);
	DrawFormatString(5, 20, color::black, " [移動:左右方向キー] [砲台傾き:上下キー] [発射:スペース] [弾の切替:W]");

	// dead_flagの立っているキャラを削除
	chr_list.remove_if([](Chr* chr) {return chr->isDead(); });
	
	// バトル終了	敗北者が確定
	if (loser != TYPE_NONE) {
		game_scene = SCENE_RESULT;

		// リストをクリアしたのち要素を削除する
		chr_list.clear();
		for (auto& chr : chr_list) {
			delete chr;
		}
		StopSoundMem(music_battle);
		return;
	}

	// 海面に関する部分
	mSea->updateSea();
	mSea->draw();

	// キャラクター全員のアップデート
	for (auto& chr : chr_list) {
		chr->update();
	}
	// キャラクター全員の描画
	for (auto& chr : chr_list) {
		chr->draw();
	}

	// キャラクター全員の当たり判定
	for (auto& src : chr_list) {
		// プレイヤー側は dst として処理 src としては処理しない
		if(src->getChrType() == TYPE_BULLET || src->getChrType() == TYPE_ENEMY){
			for (auto& dst : chr_list) {
				// 二者が同一のポインタでなく、同一のタイプでもなければ処理を行う
				if (src != dst && src->getChrType() != dst->getChrType()) {
					// 当たり判定を行う
					if (src->HitTest(dst)) {
						// 衝突時処理
						src->hit();
						dst->hit();
					}
				}
			}
		}
	}
}



void GameManager::SceneResult() {
	// 勝負の結果によってBGMを変更する。
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

	// 結果画面終了　タイトルシーンへ
	if (key::get(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(sound_enter, DX_PLAYTYPE_BACK);
		game_scene = SCENE_TITLE;
		if (loser != TYPE_PLAYER && gamemode > 1) gamemode--;	// ゲームの難易度更新
		if (CheckSoundMem(music_lose)) {
			StopSoundMem(music_lose);
		}
		music_flag = false;
		return;
	}

	// 背景描画
	DrawGraph(0, 0,image_back1, TRUE);

	// 勝敗の判定　描画
	if (loser == TYPE_PLAYER) {
		DrawFormatStringToHandle(70, 180, color::gray, font_big, "残念です...");
	}
	else if (loser == TYPE_ENEMY) {
		DrawFormatStringToHandle(120, 180, GetColor(255,100,0), font_big, "勝利 !!!");
	}

	// その他必要な文字列　描画
	DrawBox(WIDTH/2 - 130, HEIGHT/2 + 70, WIDTH/2 + 110, HEIGHT/2 + 160, color::gray2,TRUE);
	DrawString(WIDTH / 3, HEIGHT * 11 / 16, "タイトルへ戻る : ENTER", color::black);
	DrawString(WIDTH / 3, HEIGHT * 12 / 16, "終わる : ESC", color::black);
}


void GameManager::SceneManual() {
	// タイトルシーンへ戻る
	if (key::get(KEY_INPUT_RETURN) == 1) {
		game_scene = SCENE_TITLE;
		return;
	}

	// 背景描画
	DrawGraph(0,0,image_back3, TRUE);

	// テキスト表示
	DrawString(150, 140, "     ようこそ\n    ここではゲーム中の操作方法を紹介します。\n"
		"1. 方向キーの「左」と「右」で船を動かす!\n"
		"2. 方向キーの「上」と「下」で砲台の角度を調整!\n"
		"3. 「スペースキー」で弾を発射! \n"
		"4. 発射する弾は4種類。「W」を押して切り替えよう!\n"
		"5. 「スペースキー」を長押しするとチャージ弾が放てる。\n"
		"   左上のゲージの長さによってチャージ弾の姿は様々!!\n"
		"6. 敵の船にぶつかってはいけません。大ダメージです。\n"
		"全部で4つの難易度、君はどこまでクリアできるかな?\n\n\n"
		"タイトルへ戻る : ENTER", color::gray);
}


// ゲームの終了処理
void GameManager::End() {
	delete mSea;
	DxLib_End();
}


