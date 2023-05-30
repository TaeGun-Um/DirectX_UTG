#pragma once

// Ό³Έν :
class Frog_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog_ColMap();
	~Frog_ColMap();

	// delete Function
	Frog_ColMap(const Frog_ColMap& _Other) = delete;
	Frog_ColMap(Frog_ColMap&& _Other) noexcept = delete;
	Frog_ColMap& operator=(const Frog_ColMap& _Other) = delete;
	Frog_ColMap& operator=(Frog_ColMap&& _Other) noexcept = delete;

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

