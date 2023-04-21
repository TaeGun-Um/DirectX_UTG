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

	// �������� ��� ���� ����, ���̴� ���� ResHelper�� �����ؼ� �ڽ��� ResHelper �ٿ��ֱ���
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy �� �̵�
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy �� �̵�
	}

	// �츮 ������ ���, ����� ��� �������� ����� ���̱� ������, 
	// "TransformData" �� �̸����� �����ϰ�, �ش� ��� ���۴� ������ WorldViewProjectionMatrix�� ����ǵ��� ��
	if (true == ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = GetTransform()->GetTransDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
}

// Pipe�� ���õ� ������ Render
void GameEngineRenderer::Render(float _Delta)
{
	// ����ī�޶� ����
	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	// ��� ���� TransformData ��� ��, ��� ���������� ���� ī�޶� ����
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	Pipe->RenderingPipeLineSetting();

	// ������ ��� ���ۿ� ���� ����, �ؽ�ó ���� ������� ���� �̷� �͵��� ���δ� ó�� �ȴ�. ���̴� ���� �̻��ϸ� ���� ����.
	ShaderResHelper.Setting();

	// GameEngineRenderingPipeLine::Render()�� �̵��Ͽ� ���������� ����
	Pipe->Render();
}