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

	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;

public:
	//Setter
	static void SetDevice(ID3D12Device* device) { Object3D::device = device; }
	static void SetCamera(Camera* camera) { Object3D::camera = camera; }

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform
	{
		XMMATRIX viewport; //�r���[�v���W�F�N�V�����s��
		XMMATRIX world; //���[���h�s��
		XMFLOAT3 cameraPos; //�J�������W�i���[���h���W�j
	};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

private:
	//�f�o�C�X
	static ID3D12Device* device;
	//�J����
	static Camera* camera;
};

