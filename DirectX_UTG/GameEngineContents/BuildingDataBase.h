#pragma once

#include "Stage_Title.h"

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

	void InterActionOff()
	{
		IsCollisionOff = true;
	}

	void IsLevelChangeReset()
	{
		Stage_TitleCard->Off();
		Stage_TitleCard->BoxPositionReset();
		CardInterActionDelayTime = 0.0f;
		CreateCard = false;
		NextLevelPortal = false;
		BlackBoxCount = 1;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer EffectPlayer;
	GameEngineSoundPlayer EffectPlayer_Two;

	bool IsBGMOn = false;

	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FlagRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> AssitantRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	std::shared_ptr<class Stage_Title> Stage_TitleCard = nullptr;

	BuildingValue BValue = BuildingValue::Unknown;

	bool FlagCall = false;
	bool Isinteraction = false;
	bool NextLevelPortal = false;
	bool CreateCard = false;
	bool IsCollisionOff = false;

	int AnimationCount = 1;
	int BlackBoxCount = 1;

	float CardInterActionDelayTime = 0.0f;

	void CardUIOn(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void InterAction();
};

