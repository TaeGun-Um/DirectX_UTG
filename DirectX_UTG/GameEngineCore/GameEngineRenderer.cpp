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

// Pipe에 담긴 랜더를 Render
void GameEngineRenderer::Render(float _Delta)
{
	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	// 상수 버퍼 TransformData 사용 전, 뷰와 프로젝션을 월드 카메라에 적용
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	// 텍스처 세팅 상수버퍼 세팅 이런것들이 전부다 처리 된다.
	ShaderResHelper.Setting();

	Pipe->Render();  // GameEngineRenderingPipeLine::Render()로 이동하여 파이프라인 진행
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

	if (true == ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const float4x4& World = GetTransform()->GetWorldViewProjectionMatrixRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", World);
	}

	GetTransform()->GetWorldMatrix();
}

