﻿#include "WinApp.h"
#include "DirectXCommon.h"
#include "Audio.h"
#include "GameScene.h"
#include "LightGroup.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
#include "PostEffect.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{

	// 汎用機能
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;	
	Audio* audio = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect1 = nullptr;
	PostEffect* postEffect2 = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->CreateGameWindow();
		
	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = Input::GetInstance();
	if (!input->Initialize(win->GetInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}
	// オーディオの初期化
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}
	// ライト静的初期化
	LightGroup::StaticInitialize(dxCommon->GetDevice());
	// パーティクルマネージャ初期化
	ParticleManager::GetInstance()->Initialize(dxCommon->GetDevice());
	//ポストエフェクト用テクスチャの読み込み
	//Sprite::LoadTexture(100, L"Resources/white1x1.png");
	//ポストエフェクトの初期化
	postEffect1 = new PostEffect();
	postEffect1->Initialize(L"Resources/shaders/PostEffectTestVS.hlsl", L"Resources/shaders/PostEffectTestPS.hlsl");

	postEffect2 = new PostEffect();
	postEffect2->Initialize(L"Resources/shaders/PostEffectTestVS2.hlsl", L"Resources/shaders/PostEffectTestPS2.hlsl");
#pragma endregion

	//FBXローダーの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input, audio);
	
	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) {	break; }

		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();

		//レンダーテクスチャへの描画
		postEffect1->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect1->PostDrawScene(dxCommon->GetCommandList());

		postEffect2->PreDrawScene(dxCommon->GetCommandList());
		postEffect1->Draw(dxCommon->GetCommandList());
		postEffect2->PostDrawScene(dxCommon->GetCommandList());

		// 描画開始
		dxCommon->PreDraw();
		//ポストエフェクトの描画
		postEffect2->Draw(dxCommon->GetCommandList());
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	safe_delete(gameScene);
	safe_delete(audio);
	safe_delete(dxCommon);
	delete postEffect2;
	delete postEffect1;

	//FBXローダーの後始末
	FbxLoader::GetInstance()->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();
	safe_delete(win);

	return 0;
}