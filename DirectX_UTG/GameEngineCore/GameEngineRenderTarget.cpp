#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
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

	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, nullptr);
	// 1. SVTarget0 ~ 123~ 이런 식으로 여러 개의 포인터로 세팅하면 개조되게 하겠지만, 지금 당장은 1 전달 (한 개 생성)
	// 2. ID3D11RenderTargetView 여기에 그려라
	// 3. 뭐가 앞에, 뭐가 뒤에 나올지 결정하는 것인데, 지금 당장은 z값을 쓰지 않을 것이니 널포인터 전달
}