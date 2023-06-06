#pragma once

enum class CardValue
{
	Tutorial_Fly,
	Mouse,
	Frog,
	Dragon,
	Zeplin,
	Djimmi,
	Unknown
};

// Ό³Έν :
class Stage_Title : public GameEngineActor
{
public:
	// constrcuter destructer
	Stage_Title();
	~Stage_Title();

	// delete Function
	Stage_Title(const Stage_Title& _Other) = delete;
	Stage_Title(Stage_Title&& _Other) noexcept = delete;
	Stage_Title& operator=(const Stage_Title& _Other) = delete;
	Stage_Title& operator=(Stage_Title&& _Other) noexcept = delete;

	void TitleWordSetting(CardValue _CV);
	
	void BoxPositionReset();

	int GetSelectInt()
	{
		return SelectInt;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> CardRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> WordRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> INSRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> ANDRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> LOGORenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> ConfirmRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> WouldRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> YesRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> NoRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> BoxRender = nullptr;

	float4 YesPosition = float4::Zero;
	float4 NoPosition = float4::Zero;

	int SelectInt = 0;

	CardValue CV = CardValue::Unknown;

};

