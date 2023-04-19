#pragma once

#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

// 설명 : WinAPI에서 GameEngineImage와 동일한 구조 (이름만 GameEngineTexture일 뿐)
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

	// Resource에 Texture 추가
	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
	}

	static void Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
	}

	// RenderTarget 가져오기
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

	// HDC를 Texture2D에 할당 후 CreateRenderTargetView() 호출
	void ResCreate(ID3D11Texture2D* _Value);

	void CreateRenderTargetView();

};

