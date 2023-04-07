#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture()
{
}

// Texture와 RenderTarget은 동적할당이기 때문에, 소멸자 호출 시 Release를 실시해야 한다.
GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != RenderTarget)
	{
		RenderTarget->Release();
		RenderTarget = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}

// HDC를 Texture2D에 할당 후 CreateRenderTargetView() 호출
void GameEngineTexture::Create(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	CreateRenderTargetView();
}

// Texture(HDC)를 통해 RenderTarget을 만듬
void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟을 만들 수는 없습니다.");
		return;
	}

	// RenderTarget은 여러 개 만들 수 있다.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTarget);

	if (S_OK != Result)
	{
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}
}
