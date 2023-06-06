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

	float4 MinScale = float4::Zero;
	float4 CardMaxScale = float4::Zero;
	float4 INSMaxScale = float4::Zero;
	float4 ANDMaxScale = float4::Zero;
	float4 LOGOMaxScale = float4::Zero;
	float4 WouldMaxScale = float4::Zero;
	float4 BoxMaxScale = float4::Zero;
	float4 YesMaxScale = float4::Zero;
	float4 NoMaxScale = float4::Zero;
	float4 WordMaxScale = float4::Zero;

	float4 INSEndPosition = float4::Zero;
	float4 ANDEndPosition = float4::Zero;
	float4 LOGOEndPosition = float4::Zero;
	float4 WouldEndPosition = float4::Zero;
	float4 YesEndPosition = float4::Zero;
	float4 NoEndPosition = float4::Zero;
	float4 BoxEndPosition = float4::Zero;

	float ScaleMaxTime = 0.0f;
	int SelectInt = 0;
	bool OnLogicEnd = false;

	CardValue CV = CardValue::Unknown;

	void BoxInitSetting();
	void OnLogic(float _DeltaTime);
};

