#pragma once

// Ό³Έν :
class Tutorial_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Tutorial_ColMap();
	~Tutorial_ColMap();

	// delete Function
	Tutorial_ColMap(const Tutorial_ColMap& _Other) = delete;
	Tutorial_ColMap(Tutorial_ColMap&& _Other) noexcept = delete;
	Tutorial_ColMap& operator=(const Tutorial_ColMap& _Other) = delete;
	Tutorial_ColMap& operator=(Tutorial_ColMap&& _Other) noexcept = delete;

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
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr;

	bool IsDebugRender = false;
};

