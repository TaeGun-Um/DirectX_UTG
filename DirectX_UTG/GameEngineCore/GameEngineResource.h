#pragma once
#include <string>
#include <string_view>
#include <map>
#include <list>
#include <memory>
#include <GameEngineCore/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineDevice.h"

// ���� : ���ø� Ŭ����, ��ӹ޴� Ŭ������ <�ڽ��� Ŭ������>�� �ٿ��� �Ѵ�.
template<typename ResourcesType>
class GameEngineResource : public GameEngineNameObject
{
public:
	friend class GameEngineCore;

	// constrcuter destructer
	GameEngineResource() {}
	virtual ~GameEngineResource() = 0 {}

	// delete Function
	GameEngineResource(const GameEngineResource& _Other) = delete;
	GameEngineResource(GameEngineResource&& _Other) noexcept = delete;
	GameEngineResource& operator=(const GameEngineResource& _Other) = delete;
	GameEngineResource& operator=(GameEngineResource&& _Other) noexcept = delete;

	// ���ҽ��� ��ӹ��� Ŭ������ Path�� ����
	void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	// ���ҽ��� ��ӹ��� Ŭ������ Path ����
	std::string_view GetPath()
	{
		return Path.c_str();
	}

	// ���ҽ��� ��ӹ��� Ŭ������ Name�� ����
	void SetName(const std::string_view& _Value)
	{
		Name = _Value;
	}

	// ���ҽ��� ��ӹ��� Ŭ������ Name ����
	std::string_view GetName()
	{
		return Name.c_str();
	}

	// NamedResources���� Name�� ���� �ڷ� �˻�(Find)
	static std::shared_ptr<ResourcesType> Find(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() == NamedResources.find(UpperName.c_str()))
		{
			return nullptr;
		}

		return NamedResources[UpperName];
	}

protected:
	// ���ҽ��� ��ӹ��� Ŭ������ Create�� Ȱ���� �� �ִ�.
	static std::shared_ptr<ResourcesType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("�̹� �����ϴ� �̸��� ���ҽ��� �� ������� �߽��ϴ�.");
			return nullptr;
		}

		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		NewRes->SetName(UpperName);

		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourcesType>>::value_type(UpperName, NewRes));
		return NewRes;
	}

private:
	std::string Path;  // ��ӹ��� Ŭ������ Path
	std::string Name;  // ��ӹ��� Ŭ������ Name

	static std::map<std::string, std::shared_ptr<ResourcesType>> NamedResources; // Create �� map���� insert�� ���ҽ���
	static std::list<std::shared_ptr<ResourcesType>> UnNamedRes;

	// ���ϴ� Ÿ�ֿ̹� ���ŵǵ��� �ϱ� ���� ���� �� Core���� friend
	static void ResourcesClear()
	{
		NamedResources.clear();
		UnNamedRes.clear();
	}
};

// ���ø� Ŭ������ ���������� ������� �ʱ�ȭ�� �����ϴ�.
template<typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::NamedResources;

template<typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::UnNamedRes;
