#pragma once

#include "NPC_TextBox.h"

enum class KettleState
{
	Idle,
	TalkA,
	TalkAtoB,
	TalkBtoA,
	TalkB,
	Bottle_Intro,
	Bottle_Loop,
	Bottle_Outro,
};

// Ό³Έν :
class ElderKettle : public GameEngineActor
{
public:
	static ElderKettle* ElderKettlePtr;

	// constrcuter destructer
	ElderKettle();
	~ElderKettle();

	// delete Function
	ElderKettle(const ElderKettle& _Other) = delete;
	ElderKettle(ElderKettle&& _Other) noexcept = delete;
	ElderKettle& operator=(const ElderKettle& _Other) = delete;
	ElderKettle& operator=(ElderKettle&& _Other) noexcept = delete;

	void DebugRenderOn()
	{
		IsDebugRender = true;
	}

	void DebugRenderOff()
	{
		IsDebugRender = false;
	}

	void TextBoxPositionSetting()
	{
		ScriptInit();
	}
	
	void CreateBoxOn()
	{
		CreateBox = true;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BottleRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> EnterMessageRenderPtr = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CollisionRenderPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> CollisionPtr = nullptr;

	std::shared_ptr<class NPC_TextBox> NPC_TextBoxRender = nullptr;
	std::shared_ptr<class GameEngineFontRenderer> FontRender = nullptr;

	bool IsDebugRender = false;

	void ActorInitSetting();
	void CollisionCheck(float _DeltaTime);
	void EnterMessageScaleUp(float _DeltaTime);
	void EnterMessageScaleDown(float _DeltaTime);

	float4 EnterMessageRenderMaxScale = float4::Zero;
	float4 EnterMessageRenderMinScale = float4::Zero;
	float4 EnterMessageRenderDelayScale = float4::Zero;
	float ScaleMaxTime = 0.0f;
	float ScaleMinTime = 0.0f;
	int ScaleCount = 1;
	bool ScaleCheckStart = false;

	bool Isinteraction = false;
	bool CreateBox = false;
	bool NextStep = false;
	bool IsScriptChange = false;
	bool IsPop = false;
	bool TextEnd = false;

	int TextCount = 0;
	int TextEndCount = 0;
	int PopCount = 1;

	float BoxInterActionDelayTime = 0.0f;
	float TalkStateChangeTime = 0.0f;

	std::vector<std::string_view> NPCScript;
	void TextBoxOn(float _DeltaTime);
	void ScriptInit();
	void ScriptChange();
	size_t NumberofLines();
	size_t NumberofCharacters();
	void TextBoxSetting();
	void FontPositionSetting();

	KettleState StateValue = KettleState::Idle;

	void ChangeState(KettleState _StateValue);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void TalkAStart();
	void TalkAUpdate(float _DeltaTime);
	void TalkAEnd();

	void TalkAtoBStart();
	void TalkAtoBUpdate(float _DeltaTime);
	void TalkAtoBEnd();

	void TalkBtoAStart();
	void TalkBtoAUpdate(float _DeltaTime);
	void TalkBtoAEnd();

	void TalkBStart();
	void TalkBUpdate(float _DeltaTime);
	void TalkBEnd();

	void Bottle_IntroStart();
	void Bottle_IntroUpdate(float _DeltaTime);
	void Bottle_IntroEnd();

	void Bottle_LoopStart();
	void Bottle_LoopUpdate(float _DeltaTime);
	void Bottle_LoopEnd();

	void Bottle_OutroStart();
	void Bottle_OutroUpdate(float _DeltaTime);
	void Bottle_OutroEnd();

};

