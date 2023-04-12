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

// 설명 : 템플릿 클래스, 상속받는 클래스는 <자신의 클래스명>을 붙여야 한다.
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

	// 리소스를 상속받은 클래스의 Path를 설정
	void SetPath(const std::string_view& _Value)
	{
		Path = _Value;
	}

	// 리소스를 상속받은 클래스의 Path 리턴
	std::string_view GetPath()
	{
		return Path.c_str();
	}

	// 리소스를 상속받은 클래스의 Name을 설정
	void SetName(const std::string_view& _Value)
	{
		Name = _Value;
	}

	// 리소스를 상속받은 클래스의 Name 리턴
	std::string_view GetName()
	{
		return Name.c_str();
	}

	// NamedResources에서 Name을 통해 자료 검색(Find)
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
	// 리소스를 상속받은 클래스는 Create를 활용할 수 있다.
	static std::shared_ptr<ResourcesType> Create(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		if (NamedResources.end() != NamedResources.find(UpperName))
		{
			MsgAssert("이미 존재하는 이름의 리소스를 또 만들려고 했습니다.");
			return nullptr;
		}

		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		NewRes->SetName(UpperName);

		NamedResources.insert(std::map<std::string, std::shared_ptr<ResourcesType>>::value_type(UpperName, NewRes));
		return NewRes;
	}

private:
	std::string Path;  // 상속받은 클래스의 Path
	std::string Name;  // 상속받은 클래스의 Name

	static std::map<std::string, std::shared_ptr<ResourcesType>> NamedResources; // Create 시 map으로 insert된 리소스들
	static std::list<std::shared_ptr<ResourcesType>> UnNamedRes;

	// 원하는 타이밍에 제거되도록 하기 위해 생성 후 Core에게 friend
	static void ResourcesClear()
	{
		NamedResources.clear();
		UnNamedRes.clear();
	}
};

// 템플릿 클래스는 예외적으로 헤더에서 초기화가 가능하다.
template<typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::NamedResources;

template<typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResource<ResourcesType>::UnNamedRes;
