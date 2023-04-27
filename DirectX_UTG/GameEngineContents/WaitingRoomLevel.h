#pragma once

// Ό³Έν :
class WaitingRoomLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	WaitingRoomLevel();
	~WaitingRoomLevel();

	// delete Function
	WaitingRoomLevel(const WaitingRoomLevel& _Other) = delete;
	WaitingRoomLevel(WaitingRoomLevel&& _Other) noexcept = delete;
	WaitingRoomLevel& operator=(const WaitingRoomLevel& _Other) = delete;
	WaitingRoomLevel& operator=(WaitingRoomLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};

