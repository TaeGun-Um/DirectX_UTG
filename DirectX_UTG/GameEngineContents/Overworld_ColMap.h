#pragma once

// Ό³Έν :
class Overworld_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Overworld_ColMap();
	~Overworld_ColMap();

	// delete Function
	Overworld_ColMap(const Overworld_ColMap& _Other) = delete;
	Overworld_ColMap(Overworld_ColMap&& _Other) noexcept = delete;
	Overworld_ColMap& operator=(const Overworld_ColMap& _Other) = delete;
	Overworld_ColMap& operator=(Overworld_ColMap&& _Other) noexcept = delete;
	
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

