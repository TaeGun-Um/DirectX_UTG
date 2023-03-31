#pragma once
#include "GameEngineActor.h"

// 설명 : 뷰 행렬을 활용하기 위한 카메라 액터, 레벨 생성 시 maincamera가 shared_ptr로 즉시 하나 생성된다(GELevel의 생성자 단계에서 생성됨).
class GameEngineCamera : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	inline float4x4 GetView()
	{
		return View;
	}

	inline float4x4 GetProjection()
	{
		return Projection;
	}

	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	float4x4 View;        // 카메라의 뷰 행렬 결과가 적용된 값
	float4x4 Projection;
	float4x4 ViewPort;
	float Near = 0.1f;
	float Far = 10000.0f;

};
