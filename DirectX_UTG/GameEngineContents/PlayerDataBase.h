#pragma once

// Ό³Έν :
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

	void SwapWeapon()
	{
		WeaponType = !WeaponType;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	// Status
	int HP = 5;
	int EXGauge = 0;
	int EXStack = 0;
	float MoveSpeed = 500.0f;
	bool WeaponType = true;   // true : Peashooter // false : Spread

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

