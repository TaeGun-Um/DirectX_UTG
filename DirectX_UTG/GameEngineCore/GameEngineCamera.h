#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"

// ���� : ī�޶� ������, MainCamera�� ���� ���� �� ������ �Ѱ� ������
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

	// ����Ʈ ����
	void Setting();

	void Update(float _DeltaTime) override;

	// ī�޶� ����� ����
	inline float4x4 GetView()
	{
		return View;
	}

	// ī�޶� �������� ��� ����
	inline float4x4 GetProjection()
	{
		return Projection;
	}

	// ī�޶� ����Ʈ ��� ����
	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}

	// ī�޶� � Ÿ������ ����(���� or ����)
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
	D3D11_VIEWPORT ViewPortData; // ����Ʈ ����ü, Start���� ����

	float4x4 View;          // ī�޶� �� ���
	float4x4 Projection;    // ī�޶� �������� ���
	float4x4 ViewPort;      // ī�޶� ����Ʈ ���

	TransformData OldData;

	CameraType ProjectionType = CameraType::None; // ī�޶� Ÿ��

	float Width = 0.0f;     // â �ʺ�
	float Height = 0.0f;    // â ����

	float FOV = 60.0f;      // ȭ��
	float Near = 0.1f;      // �����
	float Far = 10000.0f;   // �����

};

