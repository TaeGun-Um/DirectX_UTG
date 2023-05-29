#pragma once

// Ό³Έν :
class WaitingRoom_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	WaitingRoom_ColMap();
	~WaitingRoom_ColMap();

	// delete Function
	WaitingRoom_ColMap(const WaitingRoom_ColMap& _Other) = delete;
	WaitingRoom_ColMap(WaitingRoom_ColMap&& _Other) noexcept = delete;
	WaitingRoom_ColMap& operator=(const WaitingRoom_ColMap& _Other) = delete;
	WaitingRoom_ColMap& operator=(WaitingRoom_ColMap&& _Other) noexcept = delete;

	void ColMapDebugRenderOn()
	{
		IsDebugRender = true;
	}

	void ColMapDebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

	bool IsDebugRender = false;
};

