#include "PrecompileHeader.h"
#include "NPCDataBase.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player_Overworld.h"

NPCDataBase::NPCDataBase() 
{
}

NPCDataBase::~NPCDataBase() 
{
}

void NPCDataBase::CollisionCheck(std::shared_ptr<class GameEngineCollision> _Collision)
{
	if (nullptr != _Collision->Collision(static_cast<int>(CollisionOrder::Player), ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		Isinteraction = true;
	}
	else
	{
		Isinteraction = false;
	}

	if (true == Player_Overworld::MainPlayer->GetIsIdle()
		&& true == Isinteraction
		&& true == GameEngineInput::IsDown("Attack"))
	{
		InterAction();
	}
}

void NPCDataBase::InterAction()
{
	switch (NValue)
	{
	case NPCValue::AppleTraveller:
	{
		MsgTextBox("AppleTraveller");
	}
	break;
	case NPCValue::Axeman:
	{
		MsgTextBox("Axeman");
	}
	break;
	case NPCValue::Canteen:
	{
		MsgTextBox("Canteen");
	}
	break;
	case NPCValue::Coin:
	{
		MsgTextBox("Coin");
	}
	break;
	case NPCValue::FishGirl:
	{
		MsgTextBox("FishGirl");
	}
	break;
	}
}

void NPCDataBase::NPCLoad(NPCValue _NValue)
{
	NValue = _NValue;

	switch (NValue)
	{
	case NPCValue::AppleTraveller:
	{
		if (nullptr == GameEngineSprite::Find("AppleTraveller_Blink"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("CupHead_Resource");
			NewDir.Move("CupHead_Resource");
			NewDir.Move("Image");
			NewDir.Move("Character");
			NewDir.Move("Overworld_NPCs");
			NewDir.Move("AppleTraveller");

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Blink").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_HoboStick").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Idle").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave_Intro").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("AppleTraveller_Wave_Outro").GetFullPath());
		}
	}
		break;
	case NPCValue::Axeman:
	{
		if (nullptr == GameEngineSprite::Find("Axeman_Idle"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("CupHead_Resource");
			NewDir.Move("CupHead_Resource");
			NewDir.Move("Image");
			NewDir.Move("Character");
			NewDir.Move("Overworld_NPCs");
			NewDir.Move("Axeman");

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Axeman_Idle").GetFullPath());
		}
	}
		break;
	case NPCValue::Canteen:
	{
		if (nullptr == GameEngineSprite::Find("Canteen_Idle"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("CupHead_Resource");
			NewDir.Move("CupHead_Resource");
			NewDir.Move("Image");
			NewDir.Move("Character");
			NewDir.Move("Overworld_NPCs");
			NewDir.Move("Canteen");

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Canteen_Idle").GetFullPath());
		}
	}
		break;
	case NPCValue::Coin:
	{
		if (nullptr == GameEngineSprite::Find("Coin_Blink"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("CupHead_Resource");
			NewDir.Move("CupHead_Resource");
			NewDir.Move("Image");
			NewDir.Move("Character");
			NewDir.Move("Overworld_NPCs");
			NewDir.Move("Coin");

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Blink").GetFullPath());

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Boil_A").GetFullPath());

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_A").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_B").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_C").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Hold_D").GetFullPath());

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_A").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_B").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_C").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_D").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_E").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("Coin_Transition_F").GetFullPath());
		}
	}
		break;
	case NPCValue::FishGirl:
	{
		if (nullptr == GameEngineSprite::Find("FishGirl_Idle"))
		{
			GameEngineDirectory NewDir;
			NewDir.MoveParentToDirectory("CupHead_Resource");
			NewDir.Move("CupHead_Resource");
			NewDir.Move("Image");
			NewDir.Move("Character");
			NewDir.Move("Overworld_NPCs");
			NewDir.Move("FishGirl");

			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("FishGirl_Idle").GetFullPath());
			GameEngineSprite::LoadFolder(NewDir.GetPlusFileName("FishGirl_Blink").GetFullPath());
		}
	}
		break;
	case NPCValue::Unknown:
	{
		MsgAssert("NPCSetting()을 실시하지 않았습니다. NPCValue가 Unknown입니다.");
		return;
	}
		break;
	default:
		break;
	}
}