#pragma once

// Ό³Έν :
class Werner_Werman : public GameEngineActor
{
public:
	// constrcuter destructer
	Werner_Werman();
	~Werner_Werman();

	// delete Function
	Werner_Werman(const Werner_Werman& _Other) = delete;
	Werner_Werman(Werner_Werman&& _Other) noexcept = delete;
	Werner_Werman& operator=(const Werner_Werman& _Other) = delete;
	Werner_Werman& operator=(Werner_Werman&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};

