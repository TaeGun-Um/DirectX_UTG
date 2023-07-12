#pragma once

// Ό³Έν :
class Dragon_BackGround : public GameEngineActor
{
public:
	static Dragon_BackGround* BackGroundPtr;

	// constrcuter destructer
	Dragon_BackGround();
	~Dragon_BackGround();

	// delete Function
	Dragon_BackGround(const Dragon_BackGround& _Other) = delete;
	Dragon_BackGround(Dragon_BackGround&& _Other) noexcept = delete;
	Dragon_BackGround& operator=(const Dragon_BackGround& _Other) = delete;
	Dragon_BackGround& operator=(Dragon_BackGround&& _Other) noexcept = delete;

	void SetIsDragonDash()
	{
		DragonDashRenderPtr->On();
		IsDragonDash = true;
	}

	bool GetIsDragonDashEnd()
	{
		return IsDragonDashEnd;
	}

protected:
	void Start();
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override {}

private:
	std::shared_ptr<class GameEngineSpriteRenderer> BackGroundRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGroundRenderPtr_Two = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> Middle_BackCloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Middle_BackCloudRenderPtr_Two = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> Middle_Two_BackCloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Middle_Two_BackCloudRenderPtr_Two = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> Low_BackCloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Low_BackCloudRenderPtr_Two = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> DragonDashRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> TowerRenderPtr = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> Low_FrontCloudRenderPtr_One = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Low_FrontCloudRenderPtr_Two = nullptr;

	void HBSCControl(std::shared_ptr<class GameEngineSpriteRenderer> _Object, float _saturation = 0.5f, float _brightness = 0.5f, float _contrast = 0.5f);
	void BackGroundLerp(float _DeltaTime);
	void MiddleCloudLerp(float _DeltaTime);
	void Middle_Two_CloudLerp(float _DeltaTime);
	void LowCloudLerp(float _DeltaTime);
	void LowFrontCloudLerp(float _DeltaTime);
	void DragonDash(float _DeltaTime);

	bool IsDragonDash = false;
	bool IsDragonDashEnd = false;

	float4 BackGroundScale = float4::Zero;
	float4 StartPosition_One = float4::Zero;
	float4 StartPosition_Two = float4::Zero;
	float4 LerpPosition_One = float4::Zero;
	float4 LerpPosition_Two = float4::Zero;

	float4 Middle_CloudScale = float4::Zero;
	float4 Middle_CloudStartPosition_One = float4::Zero;
	float4 Middle_CloudStartPosition_Two = float4::Zero;
	float4 Middle_CloudLerpPosition_One = float4::Zero;
	float4 Middle_CloudLerpPosition_Two = float4::Zero;

	float4 Middle_Two_CloudScale = float4::Zero;
	float4 Middle_Two_CloudStartPosition_One = float4::Zero;
	float4 Middle_Two_CloudStartPosition_Two = float4::Zero;
	float4 Middle_Two_CloudLerpPosition_One = float4::Zero;
	float4 Middle_Two_CloudLerpPosition_Two = float4::Zero;

	float4 Low_CloudScale = float4::Zero;
	float4 Low_CloudStartPosition_One = float4::Zero;
	float4 Low_CloudStartPosition_Two = float4::Zero;
	float4 Low_CloudLerpPosition_One = float4::Zero;
	float4 Low_CloudLerpPosition_Two = float4::Zero;

	float4 Low_FrontCloudScale = float4::Zero;
	float4 Low_FrontCloudStartPosition_One = float4::Zero;
	float4 Low_FrontCloudStartPosition_Two = float4::Zero;
	float4 Low_FrontCloudLerpPosition_One = float4::Zero;
	float4 Low_FrontCloudLerpPosition_Two = float4::Zero;

	float MoveSpeed = 0.0f;
	float BackGroudLerpTime = 0.0f;
	float Middle_CloudLerpTime = 0.0f;
	float Middle_Two_CloudLerpTime = 0.0f;
	float Low_CloudLerpTime = 0.0f;
	float Low_FrontCloudLerpTime = 0.0f;
};

