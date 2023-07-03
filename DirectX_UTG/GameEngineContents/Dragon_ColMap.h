#pragma once

// Ό³Έν :
class Dragon_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Dragon_ColMap();
	~Dragon_ColMap();

	// delete Function
	Dragon_ColMap(const Dragon_ColMap& _Other) = delete;
	Dragon_ColMap(Dragon_ColMap&& _Other) noexcept = delete;
	Dragon_ColMap& operator=(const Dragon_ColMap& _Other) = delete;
	Dragon_ColMap& operator=(Dragon_ColMap&& _Other) noexcept = delete;

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

