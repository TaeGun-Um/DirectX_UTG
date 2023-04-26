#pragma once

#include "GameEngineTexture.h"

// 설명 : WinAPI에서 HDC를 배운적이 있다. Direct에서는 RenderTarget이 HDC 역할을 함
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget>
{
public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	// Resource에 추가 후 헤당 RenderTarget의 Texture와 Color 설정
	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::Create(_Name);

		NewRenderTarget->ResCreate(_Texture, _Color);

		return NewRenderTarget;
	}

	// 백버퍼(화면)를 일정한 색으로 Clear (다음 그림을 그리기 위함)
	void Clear();

	// 아웃풋머저 단계를 실시하기 위한 Setting 함수
	// GameEngineDevice::RenderStart() 에서 Clear() 실시
	void Setting() override;

	// 깊이버퍼 텍스쳐 생성
	void CreateDepthTexture();

protected:

private:
	float4 Color = { 0.0f, 0.0f, 0.0f, 0.0f };     // 백버퍼를 Clear하기 위한 색 지정
	std::shared_ptr<GameEngineTexture> Texture;    // RenderTarget을 생성한 Texture
	std::shared_ptr<GameEngineTexture> DepthTexture;

	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

};

