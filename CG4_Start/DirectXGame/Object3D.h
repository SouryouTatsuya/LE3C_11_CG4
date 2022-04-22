#pragma once

#include "Model.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class Object3d
{
protected:
	//Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;

public:
	//Setter
	static void SetDevice(ID3D12Device* device) { Object3d::device = device; }
	static void SetCamera(Camera* camera) { Object3d::camera = camera; }

	//定数バッファ用データ構造体
	struct ConstBufferDataTransform
	{
		XMMATRIX viewport; //ビュープロジェクション行列
		XMMATRIX world; //ワールド行列
		XMFLOAT3 cameraPos; //カメラ座標（ワールド座標）
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

private:
	//デバイス
	static ID3D12Device* device;
	//カメラ
	static Camera* camera;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
};

