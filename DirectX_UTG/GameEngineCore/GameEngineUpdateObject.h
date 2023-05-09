#pragma once
#include "GameEngineObject.h"

// ���� : ����� Ŭ�������� protected�� Start(), Updata(). Render()�� �����ϵ��� �ϴ� Ŭ����
class GameEngineUpdateObject : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineUpdateObject();
	~GameEngineUpdateObject();

	// delete Function
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

protected:

private:

};

