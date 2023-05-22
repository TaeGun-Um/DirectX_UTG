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
	std::shared_ptr<class GameEngineCollision> RenderPtrCollisionPtr = nullptr;

	PortalValue PV = PortalValue::Unknown;

	void LevelChange();
	bool IsDebugRender = false;
};

