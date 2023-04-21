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

	// 랜더러의 상수 버퍼 세팅, 쉐이더 내의 ResHelper를 복사해서 자신의 ResHelper 붙여넣기함
	{
		const GameEngineShaderResHelper& Res = Pipe->GetVertexShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy 로 이동
	}

	{
		const GameEngineShaderResHelper& Res = Pipe->GetPixelShader()->GetShaderResHelper();
		ShaderResHelper.Copy(Res); // GameEngineShaderResHelper::Copy 로 이동
	}

	// 우리 엔진의 약속, 행렬은 모든 랜더러에 적용될 것이기 때문에, 
	// "TransformData" 이 이름으로 고정하고, 해당 상수 버퍼는 무조건 WorldViewProjectionMatrix가 적용되도록 함
	if (true == ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = GetTransform()->GetTransDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
}

// Pipe가 세팅된 랜더러 Render
void GameEngineRenderer::Render(float _Delta)
{
	// 메인카메라 세팅
	std::shared_ptr<GameEngineCamera> MainCamera = GetLevel()->GetMainCamera();

	if (nullptr == MainCamera)
	{
		assert(false);
		return;
	}

	// 상수 버퍼 TransformData 사용 전, 뷰와 프로젝션을 월드 카메라에 적용
	GetTransform()->SetCameraMatrix(MainCamera->GetView(), MainCamera->GetProjection());

	Pipe->RenderingPipeLineSetting();

	// 복붙한 상수 버퍼에 값을 세팅, 텍스처 세팅 상수버퍼 세팅 이런 것들이 전부다 처리 된다. 쉐이더 값이 이상하면 여길 봐라.
	ShaderResHelper.Setting();

	// GameEngineRenderingPipeLine::Render()로 이동하여 파이프라인 진행
	Pipe->Render();
}