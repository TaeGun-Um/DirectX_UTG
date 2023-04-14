#pragma once
#include "GameEngineResource.h"

// 설명 : GameEngineRenderingPipeLine에서 인풋레이아웃을 만들 때 활용하는 클래스
class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	// constrcuter destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Relase();

	// 만들어진 버텍스 버퍼와 버텍스 쉐이더를 받고 그걸 기반으로 인풋 레이아웃 생성
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);

	// 생성된 인풋 레이아웃으로 세팅
	void Setting() override;

protected:

private:
	ID3D11InputLayout* InputLayOut = nullptr;

};

