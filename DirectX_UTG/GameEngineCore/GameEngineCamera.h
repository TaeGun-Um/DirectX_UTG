#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"

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

	// 뷰포트 세팅
	void Setting();

	void Update(float _DeltaTime) override;

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

	// 카메라가 어떤 타입인지 설정(원근 or 직교)
	void SetProjectionType(CameraType _Type)
	{
		ProjectionType = _Type;
	}

	inline bool IsFreeCamera()
	{
		return FreeCamera;
	}

protected:
	void Start() override;

private:
	bool FreeCamera = false;
	D3D11_VIEWPORT ViewPortData; // 뷰포트 구조체, Start에서 세팅

	float4x4 View;          // 카메라 뷰 행렬
	float4x4 Projection;    // 카메라 프로젝션 행렬
	float4x4 ViewPort;      // 카메라 뷰포트 행렬

	TransformData OldData;

	CameraType ProjectionType = CameraType::None; // 카메라 타입

	float Width = 0.0f;     // 창 너비
	float Height = 0.0f;    // 창 높이

	float FOV = 60.0f;      // 화각
	float Near = 0.1f;      // 근평면
	float Far = 10000.0f;   // 원평면

};

