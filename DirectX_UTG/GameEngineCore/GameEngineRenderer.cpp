#include "PrecompileHeader.h"
#include "GameEngineRenderer.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineLevel.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineShaderResHelper.h"
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

	// 상수 버퍼 세팅
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy 로 이동
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy 로 이동
	}
}

// Pipe에 담긴 랜더를 Render
void GameEngineRenderer::Render(float _Delta)
{
	Pipe->Render();  // GameEngineRenderingPipeLine::Render()로 이동하여 파이프라인 진행
}
