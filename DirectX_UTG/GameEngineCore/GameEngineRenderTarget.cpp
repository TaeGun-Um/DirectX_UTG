#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
	DepthTexture = nullptr;
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

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	if (nullptr != DSV)
	{
		GameEngineDevice::GetContext()->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
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

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, DSV);
	// 1. SVTarget0 ~ 123~ �̷� ������ ���� ���� �����ͷ� �����ϸ� �����ǰ� �ϰ�����, ���� ������ 1 ���� (�� �� ����)
	// 2. ID3D11RenderTargetView ���⿡ �׷���
	// 3. ��
}

// ���̹��� �ؽ��� ����
void GameEngineRenderTarget::CreateDepthTexture()
{
	D3D11_TEXTURE2D_DESC Desc = { 0, };

	Desc.ArraySize = 1;                                           // �̹����� ���� �� ��ĥ �� ����. �츮�� �Ѱ�(1)
	Desc.Width = Texture->GetWidth();                             // �ؽ��� �ʺ�
	Desc.Height = Texture->GetHeight();                           // �ؽ��� ����
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;                  // Ư�� �ڷ���(����), 3����Ʈ float(0~1), 1����Ʈ int(0~255)
	Desc.SampleDesc.Count = 1;                                    // 
	Desc.SampleDesc.Quality = 0;                                  // �������� ��������, �ƴϴϱ� 0
	Desc.MipLevels = 1;                                           // ���ȳ��� 1
	Desc.Usage = D3D11_USAGE_DEFAULT;                             // ������ �׷���ī�忡���� ���� ���� (map, unmap x)
	Desc.CPUAccessFlags = 0;                                      // �׷���ī�常 �����ϴ� CPU�� ���� X(0)
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;   // �÷��״� �𽺽��ٽǷ� ����

	DepthTexture = GameEngineTexture::Create(Desc);               // ����ü�� ������� Create �ǽ�
}