#pragma once

// Ό³Έν :
class WoodPiece : public GameEngineActor
{
public:
	// constrcuter destructer
	WoodPiece();
	~WoodPiece();

	// delete Function
	WoodPiece(const WoodPiece& _Other) = delete;
	WoodPiece(WoodPiece&& _Other) noexcept = delete;
	WoodPiece& operator=(const WoodPiece& _Other) = delete;
	WoodPiece& operator=(WoodPiece&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BottleRenderPtr = nullptr;

};

