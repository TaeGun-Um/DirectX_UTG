#pragma once

enum class AttackDirection
{
	//Right
	Right_Up,           // 0
	Right_DiagonalUp,   // 1
	Right_Front,        // 2
	Right_DiagonalDown, // 3
	Right_Down,         // 4
	//Left
	Left_Up,            // 5
	Left_DiagonalUp,    // 6
	Left_Front,			// 7
	Left_DiagonalDown,	// 8
	Left_Down,			// 9
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