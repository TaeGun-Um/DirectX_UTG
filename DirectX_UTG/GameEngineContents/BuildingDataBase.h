#pragma once

enum class BuildingValue
{
	Home,
	Tutorial_Fly,
	Mouse,
	Frog,
	Dragon,
	Zeplin,
	Djimmi,
	Unknown
};

// Ό³Έν :
class BuildingDataBase : public GameEngineActor
{
public:
	static BuildingDataBase* HomePtr;
	static BuildingDataBase* Tutorial_FlyPtr;
	static BuildingDataBase* MousePtr;
	static BuildingDataBase* FrogPtr;
	static BuildingDataBase* DragonPtr;
	static BuildingDataBase* ZeplinPtr;
	static BuildingDataBase* DjimmiPtr;

	// constrcuter destructer
	BuildingDataBase();
	~BuildingDataBase();

	// delete Function
	BuildingDataBase(const BuildingDataBase& _Other) = delete;
	BuildingDataBase(BuildingDataBase&& _Other) noexcept = delete;
	BuildingDataBase& operator=(const BuildingDataBase& _Other) = delete;
	BuildingDataBase& operator=(BuildingDataBase&& _Other) noexcept = delete;

	void BuildingSetting(BuildingValue _BValue);

	void FlagUpSetting()
	{
		if (BuildingValue::Home == BValue || BuildingValue::Tutorial_Fly == BValue)
		{
			return; 
		}

		FlagCall = true;
	}

	void CollisionRenderOn()
	{
		CollisionRenderPtr->On();
	}

	void CollisionRenderOff()
	{
		CollisionRenderPtr->Off();
	}

	void IsLevelChangeReset()
	{
		IsLevelChange = false;
		BlackBoxCount = 1;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FlagRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AssitantRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;


	BuildingValue BValue = BuildingValue::Unknown;

	bool FlagCall = false;
	bool Isinteraction = false;
	bool IsLevelChange = false;

	int AnimationCount = 1;
	int BlackBoxCount = 1;

	void CollisionCheck();
	void InterAction();
};

