#pragma once

// Ό³Έν :
class CardUI : public GameEngineActor
{
public:
	// constrcuter destructer
	CardUI();
	~CardUI();

	// delete Function
	CardUI(const CardUI& _Other) = delete;
	CardUI(CardUI&& _Other) noexcept = delete;
	CardUI& operator=(const CardUI& _Other) = delete;
	CardUI& operator=(CardUI&& _Other) noexcept = delete;

	void SetMainPalyer(std::shared_ptr<class Player> _MainPlayer);

	void CartUIReset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class Player> MainPlayer = nullptr;

	std::shared_ptr<class CardUIRenderer> CardBackRenderPtr0 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardBackRenderPtr1 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardBackRenderPtr2 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardBackRenderPtr3 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardBackRenderPtr4 = nullptr;

	std::shared_ptr<class CardUIRenderer> CardFrontRenderPtr0 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardFrontRenderPtr1 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardFrontRenderPtr2 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardFrontRenderPtr3 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardFrontRenderPtr4 = nullptr;

	float CardHeight = 0.0f;
	float SizeY = 0.0f;

	float Stack0 = 0.0f;
	float Stack1 = 0.0f;
	float Stack2 = 0.0f;
	float Stack3 = 0.0f;
	float Stack4 = 0.0f;
};

