#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
}

// Resource�� �߰� �� ��� RenderTarget�� Texture�� Color ����
void GameEngineRenderTarget::ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	Color = _Color;
	Texture = _Texture;
}

// ����� Clear�� RenderTarget�� ���
// �ֳ��ϸ� RenderTarget���� �׸��� ���̱� ����
void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("����Ÿ�� �䰡 �������� �ʾƼ� Ŭ��� �Ұ����մϴ�.");
		return;
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);
}

// �ƿ�ǲ������ �ǽ��ϱ� ���� Setting, (0413)���� ����� RenderTarget�� ������ ���ٴ� ������ ���ϰ� ����
// GameEngineDevice::RenderStart() ���� Clear() �ǽ�
void GameEngineRenderTarget::Setting()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("����Ÿ�� �䰡 �������� �ʾƼ� Ŭ��� �Ұ����մϴ�.");
	}

	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, nullptr);
	// 1. SVTarget0 ~ 123~ �̷� ������ ���� ���� �����ͷ� �����ϸ� �����ǰ� �ϰ�����, ���� ������ 1 ���� (�� �� ����)
	// 2. ID3D11RenderTargetView ���⿡ �׷���
	// 3. ���� �տ�, ���� �ڿ� ������ �����ϴ� ���ε�, ���� ������ z���� ���� ���� ���̴� �������� ����
}