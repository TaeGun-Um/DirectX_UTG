#pragma once

#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;

	std::shared_ptr<GameEngineSprite> Sprite;

	bool IsEndValue = false;

	void Reset();

	void Update(float _DeltaTime);

	const SpriteInfo& CurSpriteInfo();

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;
	bool ScaleToTexture = false;

	bool IsEnd();
};

class AnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view SpriteName = "";
	size_t Start = static_cast<size_t>(-1);
	size_t End = static_cast<size_t>(-1);
	float FrameInter = 0.1f;
	bool Loop = true;
	bool ScaleToTexture = false;
};

// 설명 :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	void SetScaleToTexture(const std::string_view& _Name);

	void SetTexture(const std::string_view& _Name);

	void SetScaleRatio(float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	void SetFlipX();

	void SetFlipY();

	// 애니메이션이 존재하는지 확인
	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	// 애니메이션 생성
	std::shared_ptr<AnimationInfo> CreateAnimation(const AnimationParameter& _Paramter);

	// 애니메이션 변경(2번 인자의 Force를 바로 입력하기 위함)
	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	// 애니메이션 변경
	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

	void AllAnimation();

protected:

private:
	void Render(float _Delta) override;

	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;

	std::shared_ptr<AnimationInfo> CurAnimation;

	float4 AtlasData;

	float ScaleRatio = 1.0f;

	void Start() override;
};
