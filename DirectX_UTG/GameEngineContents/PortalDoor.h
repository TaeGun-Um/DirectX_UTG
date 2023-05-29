#pragma once

enum class PortalValue
{
	WaitingRoom,
	Tutorial,
	Overworld,
	Frog,
	Dragon,
	Mouse,
	Unknown,
};

// Ό³Έν :
class PortalDoor : public GameEngineActor
{
public:
	// constrcuter destructer
	PortalDoor();
	~PortalDoor();

	// delete Function
	PortalDoor(const PortalDoor& _Other) = delete;
	PortalDoor(PortalDoor&& _Other) noexcept = delete;
	PortalDoor& operator=(const PortalDoor& _Other) = delete;
	PortalDoor& operator=(PortalDoor&& _Other) noexcept = delete;

	void SetPortalValue(PortalValue _Value)
	{
		PV = _Value;
	}

	void PortalDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void PortalDebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EnterMessageRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> RenderCollisionPtr = nullptr;

	PortalValue PV = PortalValue::Unknown;

	float4 EnterMessageRenderMaxScale = float4::Zero;
	float4 EnterMessageRenderMinScale = float4::Zero;
	float4 EnterMessageRenderDelayScale = float4::Zero;
	float ScaleMaxTime = 0.0f;
	float ScaleMinTime = 0.0f;
	int BlackBoxCount = 1;
	int ScaleCount = 1;

	bool ScaleCheckStart = false;
	bool IsDebugRender = false;
	bool IsTurn = false;

	void LevelChange();
	void CollisionCheck(float _DeltaTime);
	void EnterMessageScaleUp(float _DeltaTime);
	void EnterMessageScaleDown(float _DeltaTime);
};

