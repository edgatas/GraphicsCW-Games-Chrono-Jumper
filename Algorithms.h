#pragma once

#ifndef ALGORITHMS
#define ALGORITHMS

#include <vector>
#include "Objects.h"
#include "Objects_Loader.h"

using namespace std;

//***********************************************************************************************************
// Ground
//***********************************************************************************************************
int groundDrawingStart(std::vector<Ground> objects, float start);
void sortGroundObjects(std::vector<Ground> &objects);

//***********************************************************************************************************
// Player
//***********************************************************************************************************

void gravity(Player &player, double deltaT);
void movement(Player &player, double deltaT);

void verticalMovement(Player &player, double deltaT, vector<Ground> hCollition);
void horizontalMovement(Player &player, double deltaT, vector<Ground> vCollition);

void verticalMovement(Player &player, double deltaT, vector<MovingPlatform> hCollition);
void horizontalMovement(Player &player, double deltaT, vector<MovingPlatform> vCollition);

//void verticalMovement(Player &player, double deltaT, std::vector<MovingPlatform> hCollition);
//void horizontalMovement(Player &player, double deltaT, std::vector<MovingPlatform> vCollition);
//***********************************************************************************************************
// Moving Platforms
//***********************************************************************************************************

int movingPlatformDrawingStart(std::vector<MovingPlatform> objects, float start);
void sortMovingPlatformsObjects(std::vector<MovingPlatform> &objects);
void platformMove(std::vector<MovingPlatform> &objects, float deltaT);

// Low Size vector. Does value exist in the vector. Use for up to 10-15 values.
template <class T>
bool vectorLowFindValue(std::vector<T> vector, T check)
{
	for (T value : vector)
	{
		if (value == check) { return true; }
	}
	return false;
}

#endif;