#pragma once

#include "PixelCollision.h"

// 설명 :
class PlayerDataBase : public GameEngineActor
{
	friend class Player;

public:
	// constrcuter destructer
	PlayerDataBase();
	~PlayerDataBase();

	// delete Function
	PlayerDataBase(const PlayerDataBase& _Other) = delete;
	PlayerDataBase(PlayerDataBase&& _Other) noexcept = delete;
	PlayerDataBase& operator=(const PlayerDataBase& _Other) = delete;
	PlayerDataBase& operator=(PlayerDataBase&& _Other) noexcept = delete;

	// 플레이어로 부터의 카메라 이동 값 리턴
	float4 GetCameraMoveDistance()
	{
		return MoveDistance;
	}

	// 플레이어 MoveSpeed 설정
	void SetPlayerMoveSpeed(float _Value)
	{
		MoveSpeed = _Value;
	}

	void SetCameraSpeedRatio(float _Ratio)
	{
		CameraSpeedRatio = _Ratio;
	}

	void StartTextBoxCameraAction(bool _Is, float4 _Value)
	{
		TextBoxCameraAction = _Is;
		TextBoxActionPosition = _Value;
	}

	void SetTextBoxCameraAction(bool _Is)
	{
		TextBoxCameraAction = _Is;
	}

protected:
	void Start() override {}
	void Update(float _DeltaTime) override {}
	void Render(float _DeltaTime) override {}

	int GetHP()
	{
		return HP;
	}

	float GetEXGauge()
	{
		return EXGauge;
	}

	int GetEXStack()
	{
		return EXStack;
	}

	enum class CameraFollowType
	{
		Normal,     // Player의 위치가 곧 Camera의 위치
		Field,      // Player의 x 이동만 따라감
		Overworld,  // Player의 x, y 이동을 따라감
		None        // 미설정시 assert
	};

	void SetCameraFollowType(CameraFollowType _Type);
	void MoveCamera(float _DeltaTime);
	void CameraShake(float _DeltaTime);

	float MoveSpeed = 400.0f;

	// Status
	int HP = 3;
	float EXGauge = 0;
	int EXStack = 0;

	// Camera
	CameraFollowType CameraType = CameraFollowType::None;
	float CameraMoveSpeed = 0.0f;
	float CameraAccessTime = 0.0f;
	float CameraSpeedRatio = 2.0f;
	float CameraShakeTime = 0.0f;

	float CameraWidth_Half = 640.0f;
	float CameraHegiht_Half = 360.0f;
	float ColMapWidth_Half = 0.0f;
	float ColMapHegiht_Half = 0.0f;

	float CameraXEnd = 0.0f;
	float CameraYEnd = 0.0f;
	float CameraMoveTime = 0.0f;
	float ShakeSpeed = 1000.0f;  //

	float4 TextBoxActionPosition = float4::Zero;

	bool IsLeftEndPosition = false;
	bool IsRightEndPosition = false;
	bool IsCameraShaking = false;
	bool TextBoxCameraAction = false;

	int LeftCount = 1;
	int RightCount = 1;
	int ShakingCameraSetting = 1;
	int ShakingCount = 0;
	int ShakingMaxCount = 0;

	float4 TargetPosition = float4::Zero;
	float4 PrevCameraPosition = float4::Zero;
	float4 CameraEndPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;
	float4 CurCameraPosition = float4::Zero;

	void FieldCameraPivotCheck();
	void OverwolrdCameraPivotCheck();

	// alt + shift + .
	virtual void IdleStart() {}
	virtual void IdleUpdate(float _DeltaTime) {}
	virtual void IdleEnd() {}

	virtual void MoveStart() {}
	virtual void MoveUpdate(float _DeltaTime) {}
	virtual void MoveEnd() {}

private:

};

