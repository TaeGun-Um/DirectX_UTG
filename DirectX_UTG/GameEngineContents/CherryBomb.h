#pragma once

// Ό³Έν :
class CherryBomb : public GameEngineActor
{
public:
	// constrcuter destructer
	CherryBomb();
	~CherryBomb();

	// delete Function
	CherryBomb(const CherryBomb& _Other) = delete;
	CherryBomb(CherryBomb&& _Other) noexcept = delete;
	CherryBomb& operator=(const CherryBomb& _Other) = delete;
	CherryBomb& operator=(CherryBomb&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;

};

