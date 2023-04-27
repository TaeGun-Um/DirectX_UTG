#pragma once

// Ό³Έν :
class MouseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MouseLevel();
	~MouseLevel();

	// delete Function
	MouseLevel(const MouseLevel& _Other) = delete;
	MouseLevel(MouseLevel&& _Other) noexcept = delete;
	MouseLevel& operator=(const MouseLevel& _Other) = delete;
	MouseLevel& operator=(MouseLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:

};

