#pragma once

// Ό³Έν :
class Mouse_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse_Map();
	~Mouse_Map();

	// delete Function
	Mouse_Map(const Mouse_Map& _Other) = delete;
	Mouse_Map(Mouse_Map&& _Other) noexcept = delete;
	Mouse_Map& operator=(const Mouse_Map& _Other) = delete;
	Mouse_Map& operator=(Mouse_Map&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class HBSCSpriteRenderer> WallBGRenderPtr = nullptr;
	std::shared_ptr<class HBSCSpriteRenderer> HouseBGRenderPtr = nullptr;

	void BrightnessControl(std::shared_ptr<class HBSCSpriteRenderer> _Object, float _saturation = 0.5f, float _brightness = 0.5f, float _contrast = 0.5f);
};

