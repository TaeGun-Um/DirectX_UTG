#pragma once

// Ό³Έν :
class WaitingRoom_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	WaitingRoom_Map();
	~WaitingRoom_Map();

	// delete Function
	WaitingRoom_Map(const WaitingRoom_Map& _Other) = delete;
	WaitingRoom_Map(WaitingRoom_Map&& _Other) noexcept = delete;
	WaitingRoom_Map& operator=(const WaitingRoom_Map& _Other) = delete;
	WaitingRoom_Map& operator=(WaitingRoom_Map&& _Other) noexcept = delete;

	void MapDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void MapDebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BGRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CouchRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ChairRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> VignetteRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> NoteRenderPtr = nullptr;

	bool IsDebugRender = false;
	int NoteCount = 0;
};

