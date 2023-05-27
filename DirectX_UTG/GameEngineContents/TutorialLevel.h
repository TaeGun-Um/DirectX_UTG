#pragma once

#include "Loading.h"

// ���� :
class TutorialLevel : public GameEngineLevel
{
public:
	static TutorialLevel* TutorialLevelPtr;

	// constrcuter destructer
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

	void LoadingOn()
	{
		LoadingPtr->SetLoadingPtrOn();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Loading> LoadingPtr = nullptr;

	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class Tutorial_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class Tutorial_Map> MapObject = nullptr;
	std::shared_ptr<class Tutorial_Target> TargetObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();
};

