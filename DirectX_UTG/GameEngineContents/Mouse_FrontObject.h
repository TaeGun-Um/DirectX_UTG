#pragma once

// ���� :
class Mouse_FrontObject : public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse_FrontObject();
	~Mouse_FrontObject();

	// delete Function
	Mouse_FrontObject(const Mouse_FrontObject& _Other) = delete;
	Mouse_FrontObject(Mouse_FrontObject&& _Other) noexcept = delete;
	Mouse_FrontObject& operator=(const Mouse_FrontObject& _Other) = delete;
	Mouse_FrontObject& operator=(Mouse_FrontObject&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class HBSCSpriteRenderer> FrontRenderPtr_1 = nullptr;
	std::shared_ptr<class HBSCSpriteRenderer> FrontRenderPtr_2 = nullptr;
	std::shared_ptr<class HBSCSpriteRenderer> FrontRenderPtr_3 = nullptr;

	void BrightnessControl(std::shared_ptr<class HBSCSpriteRenderer> _Object, float _Brightness);

};

