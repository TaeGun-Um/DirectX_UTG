#include "GameEngineTexture.h"

GameEngineTexture::GameEngineTexture()
{
}

// Texture�� RenderTarget�� �����Ҵ��̱� ������, �Ҹ��� ȣ�� �� Release�� �ǽ��ؾ� �Ѵ�.
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

// HDC�� Texture2D�� �Ҵ� �� CreateRenderTargetView() ȣ��
void GameEngineTexture::Create(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	CreateRenderTargetView();
}

// Texture(HDC)�� ���� RenderTarget�� ����
void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴ� ����Ÿ���� ���� ���� �����ϴ�.");
		return;
	}

	// RenderTarget�� ���� �� ���� �� �ִ�.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RenderTarget);

	if (S_OK != Result)
	{
		MsgAssert("����Ÿ�� ������ �����߽��ϴ�.");
		return;
	}
}
