#pragma once

#include "PixelCollision.h"

// ���� :
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

	// ���� ü����(����)
	void SwapWeapon()
	{
		WeaponType = !WeaponType;
	}

	// �÷��̾�� ������ ī�޶� �̵� �� ����
	float4 GetCameraMoveDistance()
	{
		return MoveDistance;
	}

	void SetMoveSpeed(float _Value)
	{
		MoveSpeed = _Value;
	}

	// �ȼ� �浹 ����
	void SetColMap(const std::shared_ptr<GameEngineTexture>& _ColMap, PixelCollision::Coordinate _Pivot)
	{
		PixelCollisionCheck.SetColMap(_ColMap, _Pivot);

		ColMapHegiht_Half = PixelCollisionCheck.GetColMapHeight_Half();
		ColMapWidth_Half = PixelCollisionCheck.GetColMapWidth_Half();
	}

protected:
	void Start() override {}
	void Update(float _DeltaTime) override {}
	void Render(float _DeltaTime) override {}

	enum class CameraFollowType
	{
		Normal,     // Player�� ��ġ�� �� Camera�� ��ġ
		Field,      // Player�� x �̵��� ����
		Overworld,  // Player�� x, y �̵��� ����
		None        // �̼����� assert
	};

	void SetCameraFollowType(CameraFollowType _Type);
	void MoveCamera(float _DeltaTime);
	
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationCreate_Field();
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationCreate_Overworld();
	
	void AirDashCheck(const GameEnginePixelColor& _LeftFallMapPixel, const GameEnginePixelColor& _RightFallMapPixel);
	void WallCheck(const GameEnginePixelColor& _LeftWallMapPixel, const GameEnginePixelColor& _RightWallMapPixel, float _DeltaTime);
	void PixelCheck(float _DeltaTime);
	void BottomJump(float _DeltaTime);
	void BottomJumpStateCheck();

	float MoveSpeed = 400.0f;

private:
	// Status
	int HP = 5;
	int EXGauge = 0;
	int EXStack = 0;
	bool WeaponType = true;   // true : Peashooter // false : Spread

	// Pixel
	PixelCollision PixelCollisionCheck;

	// Camera
	CameraFollowType CameraType = CameraFollowType::None;
	float CameraMoveSpeed = 0.0f;
	float CameraAccessTime = 0.0f;

	float CameraWidth_Half = 640.0f;
	float CameraHegiht_Half = 360.0f;
	float ColMapWidth_Half = 0.0f;
	float ColMapHegiht_Half = 0.0f;

	float CameraXEnd = 0.0f;
	float CameraYEnd = 0.0f;

	bool IsLeftEndPosition = false;
	bool IsRightEndPosition = false;

	int LeftCount = 1;
	int RightCount = 1;

	float4 TargetPosition = float4::Zero;
	float4 PrevCameraPosition = float4::Zero;
	float4 CameraEndPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	void FieldCameraPivotCheck();
	void OverwolrdCameraPivotCheck();

	// FSM(+Pixel Check �� bool��)
	bool IsJump = false;
	bool IsFall = false;
	bool IsDash = false;
	bool IsBottomJump = false;
	bool AirDash = false;
	bool BottomJumpAble = false;

	// alt + shift + .
	virtual void IdleStart() {}
	virtual void IdleUpdate(float _DeltaTime) {}
	virtual void IdleEnd() {}

	virtual void MoveStart() {}
	virtual void MoveUpdate(float _DeltaTime) {}
	virtual void MoveEnd() {}

};

