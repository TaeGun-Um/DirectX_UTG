#pragma once

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

	// 무기 체인지(추후)
	void SwapWeapon()
	{
		WeaponType = !WeaponType;
	}

	// 플레이어로 부터의 카메라 이동 값 리턴
	float4 GetCameraMoveDistance()
	{
		return MoveDistance;
	}

	void SetMoveSpeed(float _Value)
	{
		MoveSpeed = _Value;
	}

protected:
	void Start() {}
	void Update(float _DeltaTime) {}
	void Render(float _DeltaTime) {}

	enum class CameraFollowType
	{
		Normal,
		Field,
		Overworld,
		None
	};

	void SetCameraFollowType(CameraFollowType _Type);
	void MoveCamera(float _DeltaTime);
	
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationCreate_Tutorial();
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationCreate_Field();
	std::shared_ptr<class GameEngineSpriteRenderer> AnimationCreate_Overworld();
	
	void PlayerMove(float _DeltaTime);
	void PlayerMove_Overworld(float _DeltaTime);
	void PixelCheck();


private:
	// Status
	int HP = 5;
	int EXGauge = 0;
	int EXStack = 0;
	float MoveSpeed = 330.0f;
	bool WeaponType = true;   // true : Peashooter // false : Spread

	// Camera
	CameraFollowType CameraType = CameraFollowType::None;
	float CameraMoveSpeed = 0.0f;
	float CameraAccessTime = 0.0f;
	float CameraFollowTime = 2.0f;

	float4 TargetPosition = float4::Zero;
	float4 PrevCameraPosition = float4::Zero;
	float4 MoveDistance = float4::Zero;

	// FSM
	// alt + shift + .
	virtual void IdleStart() {}
	virtual void IdleUpdate() {}
	virtual void IdleEnd() {}

	virtual void MoveStart() {}
	virtual void MoveUpdate() {}
	virtual void MoveEnd() {}

	virtual void DashStart() {}
	virtual void DashUpdate() {}
	virtual void DashEnd() {}

	virtual void DuckStart() {}
	virtual void DuckUpdate() {}
	virtual void DuckEnd() {}

	virtual void JumpStart() {}
	virtual void JumpUpdate() {}
	virtual void JumpEnd() {}

	virtual void SlapStart() {}
	virtual void SlapUpdate() {}
	virtual void SlapEnd() {}

	virtual void AttackStart() {}
	virtual void AttackUpdate() {}
	virtual void AttackEnd() {}

	virtual void RunAttackStart() {}
	virtual void RunAttackUpdate() {}
	virtual void RunAttackEnd() {}

	virtual void EXAttackStart() {}
	virtual void EXAttackUpdate() {}
	virtual void EXAttackEnd() {}

	virtual void HoldingStart() {}
	virtual void HoldingUpdate() {}
	virtual void HoldingEnd() {}

};

