#pragma once

// Ό³Έν :
class Dragon_FrontGround : public GameEngineActor
{
public:
	// constrcuter destructer
	Dragon_FrontGround();
	~Dragon_FrontGround();

	// delete Function
	Dragon_FrontGround(const Dragon_FrontGround& _Other) = delete;
	Dragon_FrontGround(Dragon_FrontGround&& _Other) noexcept = delete;
	Dragon_FrontGround& operator=(const Dragon_FrontGround& _Other) = delete;
	Dragon_FrontGround& operator=(Dragon_FrontGround&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> FrontCloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FrontCloudRenderPtr_Two = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> CloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> CloudRenderPtr_Two = nullptr;

	void HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation = 0.5f, float _brightness = 0.5f, float _contrast = 0.5f);
	void FrontCloudLerp(float _DeltaTime);
	void CloudLerp(float _DeltaTime);

	float4 Low_FrontCloudScale = float4::Zero;
	float4 Low_FrontCloudStartPosition_One = float4::Zero;
	float4 Low_FrontCloudStartPosition_Two = float4::Zero;
	float4 Low_FrontCloudLerpPosition_One = float4::Zero;
	float4 Low_FrontCloudLerpPosition_Two = float4::Zero;

	float4 FrontCloudScale = float4::Zero;
	float4 FrontCloudStartPosition_One = float4::Zero;
	float4 FrontCloudStartPosition_Two = float4::Zero;
	float4 FrontCloudLerpPosition_One = float4::Zero;
	float4 FrontCloudLerpPosition_Two = float4::Zero;

	float Low_FrontCloudLerpTime = 0.0f;
	float FrontCloudLerpTime = 0.0f;
};

