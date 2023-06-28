#pragma once

// Ό³Έν :
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
	std::shared_ptr<class ElderKettle> KettleObject = nullptr;
	std::shared_ptr<class Player> PlayerObject = nullptr;
	std::shared_ptr<class WaitingRoom_ColMap> ThisColMap = nullptr;
	std::shared_ptr<class TransformGUI> GUI = nullptr;

	std::shared_ptr<class WaitingRoom_Map> MapObject = nullptr;
	std::shared_ptr<class PortalDoor> PortalDoorObject = nullptr;
	std::shared_ptr<class RoundBlackBox> BlackBoxPtr = nullptr;

	float PlayMapWidth_Half = 0.0f;
	float PlayMapHeight_Half = 0.0f;
	float PlayerDist = 0.0f;
	float4 CameraOriginPos = float4::Zero;
	int PortalCount = 1;

	void PlayerDebugRenderOn();
	void PlayerDebugRenderOff();
	void LevelDebugOn();
	void LevelDebugOff();
};

