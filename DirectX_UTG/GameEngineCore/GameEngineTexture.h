#pragma once
#include "GameEngineResource.h"

// ���� : WinAPI���� GameEngineImage�� ������ ���� (�̸��� GameEngineTexture�� ��)
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;

public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	// Resource�� Texture �߰�
	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
	}

	// RenderTarget ��������
	ID3D11RenderTargetView* GetRTV()
	{
		return RenderTarget;
	}

protected:

private:
	// HDC
	ID3D11Texture2D* Texture2D = nullptr;

	// 
	ID3D11RenderTargetView* RenderTarget = nullptr;

	// HDC�� Texture2D�� �Ҵ� �� CreateRenderTargetView() ȣ��
	void Create(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();

};

