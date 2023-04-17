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

// GameEngineRenderingPipeLine���� Find �� Pipe�� �Ҵ�
void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);

	// ��� ���� ����
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy �� �̵�
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy �� �̵�
	}
}

// Pipe�� ��� ������ Render
void GameEngineRenderer::Render(float _Delta)
{
	Pipe->Render();  // GameEngineRenderingPipeLine::Render()�� �̵��Ͽ� ���������� ����
}
