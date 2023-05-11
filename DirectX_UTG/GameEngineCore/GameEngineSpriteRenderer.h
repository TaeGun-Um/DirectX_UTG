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

	std::shared_ptr<GameEngineTexture> CurFrameTexture();

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;

	bool IsEnd();
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

	void SetFlipX();
	void SetFlipY();

	// 애니메이션이 존재하는지 확인
	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	// 애니메이션 생성
	std::shared_ptr<AnimationInfo> CreateAnimation(const std::string_view& _Name,
		const std::string_view& _SpriteName,
		float _FrameInter = 0.1f,
		int _Start = -1,
		int _End = -1,
		bool _Loop = true);

	// 애니메이션 변경(2번 인자의 Force를 바로 입력하기 위함)
	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	// 애니메이션 변경
	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

protected:

private:
	void Render(float _Delta) override;

	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;

	std::shared_ptr<AnimationInfo> CurAnimation;

	void Start() override;
};
