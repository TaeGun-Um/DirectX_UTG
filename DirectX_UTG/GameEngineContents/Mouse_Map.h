#pragma once

// Ό³Έν :
class Mouse_Map : public GameEngineActor
{
	friend class Werner_Werman;
	friend class Katzenwagen;

public:
	static Mouse_Map* MouseMapPtr;

	// constrcuter destructer
	Mouse_Map();
	~Mouse_Map();

	// delete Function
	Mouse_Map(const Mouse_Map& _Other) = delete;
	Mouse_Map(Mouse_Map&& _Other) noexcept = delete;
	Mouse_Map& operator=(const Mouse_Map& _Other) = delete;
	Mouse_Map& operator=(Mouse_Map&& _Other) noexcept = delete;

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	GameEngineSoundPlayer EffectPlayer;

	std::shared_ptr<class GameEngineSpriteRenderer> WallBGRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> HouseBGRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Phase2PlatformRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> PlatformCollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> PlatformCollisionPtr = nullptr;

	bool IsDebugRender = false;
	bool IsPhase2 = false;
	bool IsPhase3 = false;
	bool IsEnd = false;
	bool Phase3MapSetting = false;

	void PlatformSound();
	void Phase3Setting();
	void HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation = 0.5f, float _brightness = 0.5f, float _contrast = 0.5f);
};

