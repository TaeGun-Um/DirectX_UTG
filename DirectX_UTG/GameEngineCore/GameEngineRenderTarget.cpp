#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
	DepthTexture = nullptr;
}

// Resource에 추가 후 헤당 RenderTarget의 Texture와 Color 설정
void GameEngineRenderTarget::ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	Color = _Color;
	Texture = _Texture;
}

// 백버퍼 Clear는 RenderTarget이 담당
// 왜냐하면 RenderTarget으로 그리는 것이기 때문
void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
		return;
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	if (nullptr != DSV)
	{
		GameEngineDevice::GetContext()->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

// 아웃풋머저를 실시하기 위한 Setting, (0413)지금 현재는 RenderTarget을 여러개 쓴다는 생각은 안하고 있음
// GameEngineDevice::RenderStart() 에서 Clear() 실시
void GameEngineRenderTarget::Setting()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("랜더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다.");
	}

	ID3D11DepthStencilView* DSV = DepthTexture != nullptr ? DepthTexture->GetDSV() : nullptr;

	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, DSV);
	// 1. SVTarget0 ~ 123~ 이런 식으로 여러 개의 포인터로 세팅하면 개조되게 하겠지만, 지금 당장은 1 전달 (한 개 생성)
	// 2. ID3D11RenderTargetView 여기에 그려라
	// 3. 댑스
}

// 깊이버퍼 텍스쳐 생성
void GameEngineRenderTarget::CreateDepthTexture()
{
	D3D11_TEXTURE2D_DESC Desc = { 0, };

	Desc.ArraySize = 1;                                           // 이미지를 여러 개 겹칠 수 있음. 우리는 한개(1)
	Desc.Width = Texture->GetWidth();                             // 텍스쳐 너비
	Desc.Height = Texture->GetHeight();                           // 텍스쳐 높이
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;                  // 특수 자료형(포멧), 3바이트 float(0~1), 1바이트 int(0~255)
	Desc.SampleDesc.Count = 1;                                    // 
	Desc.SampleDesc.Quality = 0;                                  // 뭉게져서 가져올지, 아니니까 0
	Desc.MipLevels = 1;                                           // 기억안나니 1
	Desc.Usage = D3D11_USAGE_DEFAULT;                             // 오로지 그래픽카드에서만 접근 가능 (map, unmap x)
	Desc.CPUAccessFlags = 0;                                      // 그래픽카드만 접근하니 CPU는 접근 X(0)
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;   // 플래그는 댑스스텐실로 설정

	DepthTexture = GameEngineTexture::Create(Desc);               // 구조체를 기반으로 Create 실시
}