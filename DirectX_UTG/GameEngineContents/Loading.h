#pragma once

// 설명 : 임시 액터, 지울것
class GameEngineSpriteRenderer;
class Loading : public GameEngineActor
{
public:
	// constrcuter destructer
	Loading();
	~Loading();

	// delete Function
	Loading(const Loading& _Other) = delete;
	Loading(Loading&& _Other) noexcept = delete;
	Loading& operator=(const Loading& _Other) = delete;
	Loading& operator=(Loading&& _Other) noexcept = delete;

	void SetStart()
	{
		IsStart = true;
	}

	void SetOutro()
	{
		IsOutro = true;
	}

	bool GetIsEnd()
	{
		return IsEnd;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {};

private:
	std::shared_ptr<class GameEngineUIRenderer> RenderPtr = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> GlassRenderPtr = nullptr;

	float FadeTime = 0.0f;
	bool IsStart = false;
	bool IsOutro = false;
	bool IsEnd = false;

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);
};

