#pragma once
#include "GameEngineActor.h"

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	float4x4 View;          // ī�޶� �� ���
	float4x4 Projection;    // ī�޶� �������� ���
	float4x4 ViewPort;      // ī�޶� ����Ʈ ���

	float Near = 0.1f;      // �����
	float Far = 10000.0f;   // �����

};

