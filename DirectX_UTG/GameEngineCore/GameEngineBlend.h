#pragma once
#include "GameEngineResource.h"

// 설명 : 아웃풋머저의 블랜드 세팅을 돕는 클래스
// 아무 세팅도 되지 않은 알파세팅은 1111블랜드이다.
// 어떤 랜더타겟에 이미 그려진 컬러를 데스크컬러, 픽셀건지기를 통해 그려야할 컬러를 소스컬러라고 한다.
// 데스크 컬러가 0011, 소스컬러가 1001일때, 이것을 어떻게 연산하여 그릴지 정하는 것이 블랜드이다.
class GameEngineBlend : public GameEngineResource<GameEngineBlend>
{
public:
	// constrcuter destructer
	GameEngineBlend();
	~GameEngineBlend();

	// delete Function
	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(GameEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(const std::string_view& _Name, const D3D11_BLEND_DESC& _Desc)
	{
		std::shared_ptr<GameEngineBlend> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

protected:
	void ResCreate(const D3D11_BLEND_DESC& _Value);

private:
	D3D11_BLEND_DESC Desc = {};
	ID3D11BlendState* State = nullptr;
	//             R G B A
	UINT Mask = 0xFFFFFFFF; // 최종블랜드 적용 옵션, 딱히 0xFFFFFFFF에서 안바꿀것임

};

