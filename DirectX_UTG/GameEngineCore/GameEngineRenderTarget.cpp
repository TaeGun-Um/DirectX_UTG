#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
}

// Resource에 추가 후 헤당 RenderTarget의 Texture와 Color 설정
void GameEngineRenderTarget::Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
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
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);
}