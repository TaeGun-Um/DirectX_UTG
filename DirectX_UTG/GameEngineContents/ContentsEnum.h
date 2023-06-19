#pragma once

enum class AttackDirection
{
	//Right
	Right_Up,           
	Right_DiagonalUp,   
	Right_Front,        
	Right_DiagonalDown, 
	Right_Down,         
	//Left
	Left_Up,            
	Left_DiagonalUp,    
	Left_Front,			
	Left_DiagonalDown,	
	Left_Down,			
};

enum class CollisionOrder
{
	Player,         
	PlayerParry,
	PlayerSensor,
	PlayerFrontSensor,
	PlayerBottomSensor,
	Peashooter,
	PeashooterEX,
	Spread,
	SpreadEX,
	Monster,			
	MonsterHitBox,
	MonsterAttack,
	NPC,
	ElderKettle,
	Building,
	Platform,			
	ParrySpot,		    
	Portal,				
	Wall,
};