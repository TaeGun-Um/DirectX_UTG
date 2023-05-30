#pragma once

#include "Loading.h"

// ���� :
class OverworldLevel : public GameEngineLevel
{
public:
	static OverworldLevel* OverworldLevelPtr;

	// constrcuter destructer
	OverworldLevel();
	~OverworldLevel();

	// delete Function
	OverworldLevel(const OverworldLevel& _Other) = delete;
	OverworldLevel(OverworldLevel&& _Other) noexcept = delete;
	OverworldLevel& operator=(const OverworldLevel& _Other) = delete;
	OverworldLevel& operator=(OverworldLevel&& _Other) noexcept = delete;

	std::shared_ptr<class FadeEffect> FEffect = nullptr;

	void LoadingOn()
	{
		LoadingPtr->SetLoadingPtrOn();
	}

	std::shared_ptr<class RoundBlackBox> GetBlackBoxPtr()
	{
		return BlackBoxPtr;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Loading> LoadingPtr = nullptr;

	std::shared_ptr<class Player_Overworld> PlayerObject = nullptr;
	std::shared_ptr<class Overworld_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class Overworld_Map> MapObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();

	int DebugBoxCount = 1;
};

