#pragma once

#include "Model.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

class Object3D
{
protected:
	//Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//Setter
	static void SetDevice(ID3D12Device* device) { Object3D::device = device; }
	static void SetCamera(Camera* camera) { Object3D::camera = camera; }
private:
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
};

