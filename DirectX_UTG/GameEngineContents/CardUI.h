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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class Player> MainPlayer = nullptr;
	std::shared_ptr<class CardUIRenderer> CardRenderPtr0 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardRenderPtr1 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardRenderPtr2 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardRenderPtr3 = nullptr;
	std::shared_ptr<class CardUIRenderer> CardRenderPtr4 = nullptr;

	float SizeY = 0.0f;

	float Stack0 = 0.0f;
	float Stack1 = 0.0f;
	float Stack2 = 0.0f;
	float Stack3 = 0.0f;
	float Stack4 = 0.0f;

	bool Stack0Full = false;
	bool Stack1Full = false;
	bool Stack2Full = false;
	bool Stack3Full = false;
	bool Stack4Full = false;
};

