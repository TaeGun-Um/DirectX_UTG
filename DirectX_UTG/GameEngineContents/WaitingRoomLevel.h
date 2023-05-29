#pragma once

#include "Loading.h"

// ���� :
class WaitingRoomLevel : public GameEngineLevel
{
public:
	static WaitingRoomLevel* WaitingRoomLevelPtr;

	// constrcuter destructer
	WaitingRoomLevel();
	~WaitingRoomLevel();

	// delete Function
	WaitingRoomLevel(const WaitingRoomLevel& _Other) = delete;
	WaitingRoomLevel(WaitingRoomLevel&& _Other) noexcept = delete;
	WaitingRoomLevel& operator=(const WaitingRoomLevel& _Other) = delete;
	WaitingRoomLevel& operator=(WaitingRoomLevel&& _Other) noexcept = delete;

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

	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class WaitingRoom_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class WaitingRoom_Map> MapObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();
};

