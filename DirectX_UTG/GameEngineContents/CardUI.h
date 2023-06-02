#pragma once

// ���� :
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
	std::shared_ptr<class CardUIRenderer> RenderPtr = nullptr;
	std::shared_ptr<class Player> MainPlayer = nullptr;

	int Stack = 0;
};

