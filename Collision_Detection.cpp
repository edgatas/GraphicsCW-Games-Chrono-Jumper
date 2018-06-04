#include "Collision_Detection.h"
#include "Algorithms.h"

#include <iostream>


// Method to check if object is colliding with the ground
std::vector<int> playerToGround(Player player, std::vector<Ground> ground, Camera camera)
{
	std::vector<int> numbers;	//	0 - No collition, 1 - LEFT, 2 - UP, 3 - RIGHT, 4 - DOWN

	float playerX = player.getCoordinatesX();	// Getting selected player position

	int startFromIndex = groundDrawingStart(ground, playerX - 50); // Extracting first left block in 50 units to the left

	while (startFromIndex < ground.size() && playerX < playerX + 50)	// First box collition test. Checking only X.
	{
		int groundHeight = ground[startFromIndex].getHeight();
		int groundWide = ground[startFromIndex].getWide();
		
		float groundX = ground[startFromIndex].getCoordinatesX();

		float groundLeftX = groundX - groundWide;
		float groundRightX = groundX + groundWide;

		if (playerX >= groundLeftX && playerX <= groundRightX)	//	Second box collition test. Cheching Y.
		{
			float playerY = player.getCoordinatesY();
			float groundY = ground[startFromIndex].getCoordinatesY();
			float groundBottomY = groundY - groundHeight;
			float groundTopY = groundY + groundHeight;

			if (playerY >= groundBottomY && playerY <= groundTopY)
			{
				//std::cout << "HIT HIT HIT HIT" << std::endl;

				float x1 = abs(playerX - groundLeftX);
				float x2 = abs(playerX - groundRightX);
				float y1 = abs(playerY - groundTopY);
				float y2 = abs(playerY - groundBottomY);

				if (x1 < x2)	// if true, left side touching. False, right side touching
				{
					if (x1 < y1 && x1 < y2)
					{
						std::cout << "LEFT" << std::endl;
						numbers.push_back(1);
					}
					else
					{
						if (y1 < y2)
						{
							std::cout << "TOP" << std::endl;
							numbers.push_back(2);
						}
						else
						{
							std::cout << "BOTTOM" << std::endl;
							numbers.push_back(4);
						}
					}
				}
				else
				{
					if (x2 < y1 && x2 < y2)
					{
						std::cout << "RIGHT" << std::endl;
						numbers.push_back(3);
					}
					else
					{
						if (y1 < y2)
						{
							std::cout << "TOP" << std::endl;
							numbers.push_back(2);
						}
						else
						{
							std::cout << "BOTTOM" << std::endl;
							numbers.push_back(4);
						}
					}
				}

				//return true;
			}
		}
		startFromIndex++;
	}

	for (int i = 0; i < numbers.size(); i++)
	{
		std::cout << numbers[i];
	}
	std::cout << std::endl;

	if (numbers.size() == 0)
	{
		numbers.push_back(0);
	}

	return numbers;
}

std::vector<Ground> playerToGroundHorizontal2(Player player, std::vector<Ground> ground, Camera camera)
{
	std::vector<Ground> numbers;	// 0 - No Collition, 1 - Collition with objects left, 2 - Collition with objects right

	float playerX = player.getCoordinatesX();	// Getting selected player position

	int startFromIndex = groundDrawingStart(ground, playerX - 10000); // Extracting first left block in 50 units to the left

	while (startFromIndex < ground.size() && playerX < playerX + 10000)	// First box collition test. Checking only X.
	{
		int groundHeight = ground[startFromIndex].getHeight();
		int groundWide = ground[startFromIndex].getWide();

		float groundX = ground[startFromIndex].getCoordinatesX();

		float groundLeftX = groundX - groundWide;
		float groundRightX = groundX + groundWide;

		//std::cout << playerX << " > " << groundLeftX << " && " << playerX << " < " << groundRightX << std::endl;
		if (playerX + player.getWide()/2 > groundLeftX && playerX - player.getWide() / 2 < groundRightX)	//	Second box collition test. Cheching Y.
		{
			float playerY = player.getCoordinatesY();
			float groundY = ground[startFromIndex].getCoordinatesY();
			float groundBottomY = groundY - groundHeight;
			float groundTopY = groundY + groundHeight;

			if (playerY + player.getHeight() >= groundBottomY && playerY < groundTopY)
			{
				numbers.push_back(ground[startFromIndex]);
			}
		}
		startFromIndex++;
	}

	// Comment Out
	//if (numbers.size() > 0)
	//{
	//	std::cout << "HORIZONTAL GROUND DETECTED:";
	//	for (int i = 0; i < numbers.size(); i++)
	//	{
	//		std::cout << numbers[i];
	//	}
	//	std::cout << std::endl;
	//}

	return numbers;
}

std::vector<Ground> playerToGroundVertical2(Player player, std::vector<Ground> ground, Camera camera)
{
	std::vector<Ground> numbers;	// All object player is touching

	float playerX = player.getCoordinatesX();	// Getting selected player position

	int startFromIndex = groundDrawingStart(ground, playerX - 10000); // Extracting first left block in 50 units to the left

	while (startFromIndex < ground.size() && ground[startFromIndex].getCoordinatesX() < playerX + 10000)	// First box collition test. Checking only X.
	{
		int groundHeight = ground[startFromIndex].getHeight();
		int groundWide = ground[startFromIndex].getWide();

		float groundX = ground[startFromIndex].getCoordinatesX();

		float groundLeftX = groundX - groundWide;
		float groundRightX = groundX + groundWide;

		//std::cout << playerX << " >= " << groundLeftX << " && " << playerX << " <= " << groundRightX << std::endl;
		if (playerX + player.getWide() / 2 > groundLeftX && playerX - player.getWide() / 2 < groundRightX)	//	Second box collition test. Cheching Y.
		{
			//std::cout << "PASSED" << std::endl;
			float playerY = player.getCoordinatesY();
			float groundY = ground[startFromIndex].getCoordinatesY();
			float groundBottomY = groundY - groundHeight;
			float groundTopY = groundY + groundHeight;

			if (playerY + player.getHeight() >= groundBottomY && playerY <= groundTopY)
			{
				numbers.push_back(ground[startFromIndex]);
			}
		}
		startFromIndex++;
	}

	// Comment Out
	//if (numbers.size() > 0)
	//{
	//	std::cout << "VERTICAL WALL DETECTED:";
	//	for (int i = 0; i < numbers.size(); i++)
	//	{
	//		std::cout << numbers[i];
	//	}
	//	std::cout << std::endl;
	//}

	return numbers;
}


std::vector<MovingPlatform> playerToMovingPlatformVertical(Player player, std::vector<MovingPlatform> platforms, Camera camera)
{
	std::vector<MovingPlatform> objectsWithCollition;
	float playerX = player.getCoordinatesX();	// Getting selected player position

	int size = platforms.size();
	for (unsigned int i = 0; i < size; i++)	// First box collition test. Checking only X.
	{
		int platformHeight = platforms[i].getHeight();
		int platformWide = platforms[i].getWide();

		float platformX = platforms[i].getCoordinatesX();

		float platformLeftX = platformX - platformWide;
		float platformRightX = platformX + platformWide;

		//std::cout << playerX << " >= " << platformLeftX << " && " << playerX << " <= " << platformRightX << std::endl;
		if (playerX + player.getWide()/3 >= platformLeftX && playerX - player.getWide() / 3 <= platformRightX)	//	Second box collition test. Cheching Y.
		{
			//std::cout << "PASSED" << std::endl;
			float playerY = player.getCoordinatesY();
			float platformY = platforms[i].getCoordinatesY();
			float platformBottomY = platformY - platformHeight;
			float platformTopY = platformY + platformHeight;

			if (playerY >= platformBottomY && playerY <= platformTopY)
			{
				objectsWithCollition.push_back(platforms[i]);
			}
		}
	}
	return objectsWithCollition;
}
std::vector<MovingPlatform> playerToMovingPlatformHorizontal(Player player, std::vector<MovingPlatform> platforms, Camera camera)
{
	std::vector<MovingPlatform> objectsWithCollition;

	float playerX = player.getCoordinatesX();	// Getting selected player position

	int size = platforms.size();
	for (unsigned int i = 0; i < size; i++)	// First box collition test. Checking only X.
	{
		int platformHeight = platforms[i].getHeight();
		int platformWide = platforms[i].getWide();

		float platformX = platforms[i].getCoordinatesX();

		float platformLeftX = platformX - platformWide;
		float platformRightX = platformX + platformWide;

		//std::cout << playerX << " > " << platformLeftX << " && " << playerX << " < " << platformRightX << std::endl;
		if (playerX > platformLeftX && playerX < platformRightX)	//	Second box collition test. Cheching Y.
		{
			float playerY = player.getCoordinatesY();
			float platformY = platforms[i].getCoordinatesY();
			float platformBottomY = platformY - platformHeight;
			float platformTopY = platformY + platformHeight;

			if (playerY >= platformBottomY && playerY < platformTopY)
			{
				objectsWithCollition.push_back(platforms[i]);
			}
		}
	}
	return objectsWithCollition;
}



int playerToCrystal(Player player, std::vector<Crystal> crystal)
{
	float playerX = player.getCoordinatesX();	// Getting selected player position
	float playerY = player.getCoordinatesY() + 50;	// Getting selected player position

	int size = crystal.size();

	for (unsigned int i = 0; i < size; i++)
	{
		float crystalX = crystal[i].getCoordinatesX();	// Getting selected crystal position
		float crystalY = crystal[i].getCoordinatesY();	// Getting selected crystal position

		float distanceX = (crystalX - playerX) * (crystalX - playerX) + 25;
		float distanceY = (crystalY - playerY) * (crystalY - playerY) + 25;
		float combined = distanceX + distanceY;
		float radius = 64 * 64;

		if (combined < radius) // Detected
		{
			std::cout << "Detected" << std::endl;
			return i;
		}

	}
	return -1;

}