#pragma once

// Ό³Έν :
class CherryBomb_Fire : public GameEngineActor
{
public:
	// constrcuter destructer
	CherryBomb_Fire();
	~CherryBomb_Fire();

	// delete Function
	CherryBomb_Fire(const CherryBomb_Fire& _Other) = delete;
	CherryBomb_Fire(CherryBomb_Fire&& _Other) noexcept = delete;
	CherryBomb_Fire& operator=(const CherryBomb_Fire& _Other) = delete;
	CherryBomb_Fire& operator=(CherryBomb_Fire&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};

