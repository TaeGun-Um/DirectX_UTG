#pragma once

#include "GameEngineComponent.h"

// 설명 :
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// 모든 랜더는 DirectX 파이프라인 과정을 거친 후 출력된다.
	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _Delta) override;

private:
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe; // 생성된 파이프라인을 담기 위한 shared_ptr

};
