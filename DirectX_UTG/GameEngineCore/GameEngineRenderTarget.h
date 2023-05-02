#pragma once

#include "GameEngineTexture.h"

// ���� : WinAPI���� HDC�� ������� �ִ�. Direct������ RenderTarget�� HDC ������ ��
class GameEngineRenderTarget : public GameEngineResource<GameEngineRenderTarget>
{
public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	// Resource�� �߰� �� ��� RenderTarget�� Texture�� Color ����
	static std::shared_ptr<GameEngineRenderTarget> Create(const std::string_view& _Name, std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRenderTarget = GameEngineResource::Create(_Name);

		NewRenderTarget->ResCreate(_Texture, _Color);

		return NewRenderTarget;
	}

	// �����(ȭ��)�� ������ ������ Clear (���� �׸��� �׸��� ����)
	void Clear();

	// �ƿ�ǲ���� �ܰ踦 �ǽ��ϱ� ���� Setting �Լ�
	// GameEngineDevice::RenderStart() ���� Clear() �ǽ�
	void Setting() override;

	// ���̹��� �ؽ��� ����
	void CreateDepthTexture();

	void Reset();

protected:

private:
	float4 Color = { 0.0f, 0.0f, 0.0f, 0.0f };     // ����۸� Clear�ϱ� ���� �� ����
	std::shared_ptr<GameEngineTexture> Texture;    // RenderTarget�� ������ Texture
	std::shared_ptr<GameEngineTexture> DepthTexture;

	void ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

};

