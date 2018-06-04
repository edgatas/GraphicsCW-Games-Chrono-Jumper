#pragma once

#ifndef COLLISION_DETECTION
#define COLLISION_DETECTION

#include "Objects.h"
#include "Camera.h"

#include <vector>

std::vector<int> playerToGround(Player player, std::vector<Ground> ground, Camera camera);

//std::vector<int> playerToGroundVertical(Player player, std::vector<Ground> ground, Camera camera);
//std::vector<int> playerToGroundHorizontal(Player player, std::vector<Ground> ground, Camera camera);

std::vector<Ground> playerToGroundVertical2(Player player, std::vector<Ground> ground, Camera camera);
std::vector<Ground> playerToGroundHorizontal2(Player player, std::vector<Ground> ground, Camera camera);


std::vector<MovingPlatform> playerToMovingPlatformVertical(Player player, std::vector<MovingPlatform> platforms, Camera camera);
std::vector<MovingPlatform> playerToMovingPlatformHorizontal(Player player, std::vector<MovingPlatform> platforms, Camera camera);

int playerToCrystal(Player player, std::vector<Crystal> ground);

#endif