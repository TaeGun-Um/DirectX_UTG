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

// Pipe�� ��� ������ Render
void GameEngineRenderer::Render(float _Delta)
{
	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	// ��� ���� TransformData ��� ��, ��� ���������� ���� ī�޶� ����
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	// �ؽ�ó ���� ������� ���� �̷��͵��� ���δ� ó�� �ȴ�.
	ShaderResHelper.Setting();

	Pipe->Render();  // GameEngineRenderingPipeLine::Render()�� �̵��Ͽ� ���������� ����
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

	if (true == ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const float4x4& World = GetTransform()->GetWorldViewProjectionMatrixRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", World);
	}

	GetTransform()->GetWorldMatrix();
}

