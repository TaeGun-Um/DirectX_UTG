#pragma once

// Ό³Έν :
class Mouse_ColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse_ColMap();
	~Mouse_ColMap();

	// delete Function
	Mouse_ColMap(const Mouse_ColMap& _Other) = delete;
	Mouse_ColMap(Mouse_ColMap&& _Other) noexcept = delete;
	Mouse_ColMap& operator=(const Mouse_ColMap& _Other) = delete;
	Mouse_ColMap& operator=(Mouse_ColMap&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};

