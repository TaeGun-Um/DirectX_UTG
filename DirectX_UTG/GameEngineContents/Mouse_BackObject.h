#pragma once

// Ό³Έν :
class Mouse_BackObject : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse_BackObject();
	~Mouse_BackObject();

	// delete Function
	Mouse_BackObject(const Mouse_BackObject& _Other) = delete;
	Mouse_BackObject(Mouse_BackObject&& _Other) noexcept = delete;
	Mouse_BackObject& operator=(const Mouse_BackObject& _Other) = delete;
	Mouse_BackObject& operator=(Mouse_BackObject&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Bullet1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Bullet2 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Bullet3 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Bullet4 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Stool1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Stool2 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Thimble1 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Thimble2 = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Dice = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr_Table = nullptr;


	void BrightnessControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation = 0.5f, float _brightness = 0.5f, float _contrast = 0.5f);
};

