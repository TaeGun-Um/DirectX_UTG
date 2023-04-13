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

// GameEngineRenderingPipeLine���� Find �� Pipe�� �Ҵ�
void GameEngineRenderer::SetPipeLine(const std::string_view& _Name)
{
	Pipe = GameEngineRenderingPipeLine::Find(_Name);
}

// Pipe�� ��� ������ Render
void GameEngineRenderer::Render(float _Delta)
{
	Pipe->Render();  // GameEngineRenderingPipeLine::Render()�� �̵��Ͽ� ���������� ����
}
