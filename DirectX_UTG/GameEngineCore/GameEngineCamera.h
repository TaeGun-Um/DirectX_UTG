#pragma once
#include "GameEngineActor.h"

// 설명 : 카메라 생성용, MainCamera는 레벨 생성 시 무조건 한개 생성됨
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

	// 카메라 뷰행렬 리턴
	inline float4x4 GetView()
	{
		return View;
	}

	// 카메라 프로젝션 행렬 리턴
	inline float4x4 GetProjection()
	{
		return Projection;
	}

	// 카메라 뷰포트 행렬 리턴
	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	float4x4 View;          // 카메라 뷰 행렬
	float4x4 Projection;    // 카메라 프로젝션 행렬
	float4x4 ViewPort;      // 카메라 뷰포트 행렬

	float Near = 0.1f;      // 근평면
	float Far = 10000.0f;   // 원평면

};

