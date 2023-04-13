#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "GameEngineRenderingPipeLine.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

// GameEngineRenderingPipeLine에서 Find 후 Pipe에 할당
void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);
}

// Pipe에 담긴 랜더를 Render
void GameEngineRenderer::Render(float _Delta)
{
	Pipe->Render();  // GameEngineRenderingPipeLine::Render()로 이동하여 파이프라인 진행
}
