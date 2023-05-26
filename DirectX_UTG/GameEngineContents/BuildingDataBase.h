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
		FlagCall = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AssitantRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	BuildingValue BValue = BuildingValue::Unknown;

	bool FlagCall = false;

	void CreateFlag();

};

