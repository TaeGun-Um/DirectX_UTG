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

enum class RenderOrder
{
	Background,
	Platform,
	MonsterEffect,
	Monster,
	MonsterAttack,
	PlayerEffect,
	Player,
	PlayerAttack,
	Layer,
	UI,
	Debug,
	SFX,
};

enum class CollisionOrder
{
	Player,         
	PlayerSensor,
	Peashooter,
	PeashooterEX,
	Spread,
	SpreadEX,
	Monster,			
	MonsterAttack,		
	Platform,			
	ParrySpot,		    
	Portal,				
	Wall,
};