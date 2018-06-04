#include "Algorithms.h"

#include <iostream>
#include <algorithm>

int groundDrawingStart(std::vector<Ground> objects, float start)
{
	int size = objects.size();

	if (size == 0) { return -1; }										// If vector is empty. Quick escape.
	if (size == 1 && objects[0].getCoordinatesX() > start) { return 0; }	// If there is only 1 object. Quick escape.
	if (objects[size - 1].getCoordinatesX() < start) { return -1; }		// If al objects have been passed. Quick escape

	int low = 0;
	int high = size - 1;

	int closest = 0;

	while (low <= high)
	{
		int middle = (low + high) / 2;

		if (objects[middle].getCoordinatesX() <= start)
		{
			low = middle + 1;
		}
		else
		{
			high = middle - 1;
		}

		if (abs(objects[middle].getCoordinatesX() - start) < abs(objects[closest].getCoordinatesX() - start))
		{
			closest = middle;
		}
	}

	while (closest - 1 > -1)
	{
		if (objects[closest].getCoordinatesX() == objects[closest - 1].getCoordinatesX()) { closest--; }
		else { break; }
	}

	return closest;
}

// Sorting objects by the X coordinate and then by the Y coordinate
void sortGroundObjects(std::vector<Ground> &objects)
{
	sort(objects.begin(), objects.end(), [](Ground g1, Ground g2)
	{
		if (g1.getCoordinatesX() == g2.getCoordinatesX())
		{
			return (g1.getCoordinatesY() < g2.getCoordinatesY());
		}
		return (g1.getCoordinatesX() < g2.getCoordinatesX());
	});
}

void sortMovingPlatformObjects(std::vector<MovingPlatform> &objects)
{
	sort(objects.begin(), objects.end(), [](MovingPlatform g1, MovingPlatform g2)
	{
		if (g1.getCoordinatesX() == g2.getCoordinatesX())
		{
			return (g1.getCoordinatesY() < g2.getCoordinatesY());
		}
		return (g1.getCoordinatesX() < g2.getCoordinatesX());
	});
}

//*****************************************************************************************************
// PLAYER
//*****************************************************************************************************


void gravity(Player &player, double deltaT)
{
	////std::cout << "GRAVITY" << std::endl;

	float g = -9.81; float frac = 0.8;

	float oldVelocity, newVelocity;
	float oldCoordinatesY, newCoordinatesY;

	oldVelocity = player.getVSpeed();
	oldCoordinatesY = player.getCoordinatesY();

	//////std::cout << "Player state: " << player.getVState() << std::endl;

	if (oldVelocity > 0) // Going up without collition
	{
		////std::cout << "CONDITION 1" << std::endl;
		newVelocity = oldVelocity + g * deltaT;
		float newCoordinatesY = oldCoordinatesY + (((oldVelocity + newVelocity) / 2.0) * deltaT);
		player.setCoordinatesY(newCoordinatesY);
		player.setVspeed(newVelocity);
		player.setVState(1);
	}
	if (oldVelocity <= 0) // Going down without collition
	{
		////std::cout << "CONDITION 2" << std::endl;
		newVelocity = oldVelocity + g * deltaT;
		float newCoordinatesY = oldCoordinatesY + (((oldVelocity + newVelocity) / 2.0) * deltaT);
		player.setCoordinatesY(newCoordinatesY);
		player.setVspeed(newVelocity);
		player.setVState(2);
	}
}

void movement(Player &player, double deltaT)
{
	////std::cout << "HORIZONTAL FREE MOVEMENT" << std::endl;
	switch (player.getHState()) //	0 - Standing,	1 - Negative(Left),	2 - Positive(Right)
	{
	case 0:
	{
		////std::cout << "CASE 0" << std::endl;

		if (std::abs(player.getHSpeed()) < 5)	// Stopping if the speed is lower then 5
		{
			player.setHspeed(0);
		}

		if (player.getHSpeed() != 0)	// Slowing character down when no key is pressed
		{
			float oldHSpeed = player.getHSpeed();
			float newHSpeed;

			if (oldHSpeed > 0)	// Checking to which side character was moving
			{
				newHSpeed = oldHSpeed - (player.getMaxSpeed() * deltaT / 10);
			}
			else
			{
				newHSpeed = oldHSpeed + (player.getMaxSpeed() * deltaT / 10);
			}

			player.setHspeed(newHSpeed);

			float oldCoordinates = player.getCoordinatesX();
			float newCoordinates = oldCoordinates + newHSpeed * deltaT;

			player.setCoordinatesX(newCoordinates);
		}
	}
	break;

	case 1:	// Moving negative (left)
	{
		////std::cout << "CASE 1" << std::endl;

		if (player.getHSpeed() > -player.getMaxSpeed())	// if speed is less then character max speed
		{	// increase speed
			//////std::cout << "CONDITION 1" << std::endl;

			float oldCoordinates = player.getCoordinatesX();
			float oldHSpeed = player.getHSpeed();
			float newHSpeed;
			if (oldHSpeed > 0) // Addition to speed reduction if player switches directions. 2.25 faster.
			{
				newHSpeed = oldHSpeed + (0 - player.getMaxSpeed()) * deltaT / 4;
			}
			else
			{
				newHSpeed = oldHSpeed + (0 - player.getMaxSpeed()) * deltaT / 10;
			}
			float newCoordinates = oldCoordinates + newHSpeed * deltaT;

			player.setCoordinatesX(newCoordinates);
			player.setHspeed(newHSpeed);
		}
		else
		{	// leave speed the same
			//////std::cout << "CONDITION 2" << std::endl;

			player.setHspeed(0 - player.getMaxSpeed()); //Setting speed to max character speed
			float oldCoordinates = player.getCoordinatesX();
			float newCoordinates = oldCoordinates + player.getHSpeed() * deltaT;

			player.setCoordinatesX(newCoordinates);
		}
	}
	break;

	case 2:	// Moving positive (right)
	{
		////std::cout << "CASE 2" << std::endl;

		if (player.getHSpeed() < player.getMaxSpeed()) // if speed is less then character max speed
		{	// increase speed
			//////std::cout << "CONDITION 1" << std::endl;

			float oldCoordinates = player.getCoordinatesX();
			float oldHSpeed = player.getHSpeed();
			float newHSpeed;
			if (oldHSpeed < 0)  // Addition to speed reduction if player switches directions. 2.25 faster.
			{
				newHSpeed = oldHSpeed + player.getMaxSpeed() * deltaT / 4;
			}
			else
			{
				newHSpeed = oldHSpeed + player.getMaxSpeed() * deltaT / 10;
			}
			float newCoordinates = oldCoordinates + newHSpeed * deltaT;

			player.setCoordinatesX(newCoordinates);
			player.setHspeed(newHSpeed);
		}
		else
		{	// leave speed the same
			//////std::cout << "CONDITION 2" << std::endl;

			player.setHspeed(player.getMaxSpeed()); //Setting speed to max character speed
			float oldCoordinates = player.getCoordinatesX();
			float newCoordinates = oldCoordinates + player.getHSpeed() * deltaT;

			player.setCoordinatesX(newCoordinates);
		}
	}
	break;
	}
	player.setHState(0);	// Setting player to standing
}

void verticalMovement(Player &player, double deltaT, vector<Ground> hCollition)
{
	//std::cout << "VERTICAL MOVEMENT" << std::endl;
	//////std::cout << "V State: " << player.getVState() << std::endl;
	float g = -9.81; float frac = 0.8;

	float oldVelocity = player.getVSpeed();
	
	//std::cout << hCollition.size() << "|" << oldVelocity << "|" << player.getVState() << std::endl;
	//std::cout << "hCollition.size() > 0 && oldVelocity < 0 && player.getVState() == 2" << std::endl;


	if (hCollition.size() > 0 && oldVelocity < 0 && player.getVState() == 2) // Going down with objects top collition. In most cases, landing on ground
	{
		//std::cout << "CONDITION 1" << std::endl;

		float newCoordinates = 0;
		newCoordinates = hCollition[0].getCoordinatesY() + hCollition[0].getHeight() + 0.1;

		player.setCoordinatesY(newCoordinates);
		player.setVspeed(0); // Removing any speed
		player.setVState(3); // Setting state to down
	}


	if (hCollition.size() > 0 && oldVelocity > 0 && player.getVState() == 1) // Going up with objects bottom collition. In most cases, hitting character head.
	{
		//std::cout << "CONDITION 2" << std::endl;

		float newCoordinates = 0;
		newCoordinates = hCollition[0].getCoordinatesY() - hCollition[0].getHeight() - 0.1 - player.getHeight();

		player.setCoordinatesY(newCoordinates);
		player.setVspeed(0); // Removing any speed
		player.setVState(2); // setting to state 3, down.
	}


	if (hCollition.size() > 0 && player.getVState() == 0) // On Ground. Starting to Jump
	{
		std::cout << "CONDITION 3" << std::endl;

		float oldCoordinatesY = player.getCoordinatesY();
		float newVelocity = oldVelocity + g * deltaT;
		float newCoordinatesY = oldCoordinatesY + (((oldVelocity + newVelocity) / 2.0) * deltaT);
		player.setCoordinatesY(newCoordinatesY);
		player.setVspeed(newVelocity);
		player.setVState(1);
	}
}

void horizontalMovement(Player &player, double deltaT, vector<Ground> vCollition)
{
	////std::cout << "HORIZONTAL MOVEMENT" << std::endl;
	if (vCollition.size() > 0)
	{
		int groundCoordinatesX = vCollition[0].getCoordinatesX();
		int groundWide = vCollition[0].getWide();
		float newCoordinates = 0;

		int playerCoordinatesX = player.getCoordinatesX();
		if (playerCoordinatesX < groundCoordinatesX)	// Player is to the left of the ground blocks
		{
			////std::cout << "CONDITION 1" << std::endl;
			newCoordinates = groundCoordinatesX - groundWide - 0.1 - player.getWide() / 2; // Block location + Block wide + small number
		}
		else	// Player is to the right of ground blocks
		{
			////std::cout << "CONDITION 2" << std::endl;
			newCoordinates = groundCoordinatesX + groundWide + 0.1 + player.getWide() / 2; // Block location + Block wide + small number
		}

		player.setCoordinatesX(newCoordinates);
		player.setHspeed(0);	// Setting speed to 0
		player.setHState(0);	// Setting state to standings
	}
}


//***********************************************************************************************************
// Moving Platforms
//***********************************************************************************************************

int movingPlatformDrawingStart(std::vector<MovingPlatform> objects, float start)
{
	int size = objects.size();

	if (size == 0) { return -1; }										// If vector is empty. Quick escape.
	if (size == 1 && objects[0].getCoordinatesX() > start) { return 0; }	// If there is only 1 object. Quick escape.
	if (objects[size - 1].getCoordinatesX() < start) { return -1; }		// If al objects have been passed. Quick escape

	int low = 0;
	int high = size - 1;

	int closest = 0;

	while (low <= high)
	{
		int middle = (low + high) / 2;

		if (objects[middle].getCoordinatesX() <= start)
		{
			low = middle + 1;
		}
		else
		{
			high = middle - 1;
		}

		if (abs(objects[middle].getCoordinatesX() - start) < abs(objects[closest].getCoordinatesX() - start))
		{
			closest = middle;
		}
	}

	while (closest - 1 > -1)
	{
		if (objects[closest].getCoordinatesX() == objects[closest - 1].getCoordinatesX()) { closest--; }
		else { break; }
	}

	return closest;
}
void sortMovingPlatformsObjects(std::vector<MovingPlatform> &objects)
{
	sort(objects.begin(), objects.end(), [](MovingPlatform g1, MovingPlatform g2)
	{
		if (g1.getCoordinatesX() == g2.getCoordinatesX())
		{
			return (g1.getCoordinatesY() < g2.getCoordinatesY());
		}
		return (g1.getCoordinatesX() < g2.getCoordinatesX());
	});
}

void platformMove(std::vector<MovingPlatform> &objects, float deltaT)
{
	int size = objects.size();

	for (unsigned int i = 0; i < size; i++)
	{
		float sleepTime = objects[i].getSleepTime();

		//std::cout << "State==0,SleepTime<0 : " << objects[i].getAccelState() << "|" << sleepTime << std::endl;
		if (sleepTime < 0)
		{
			float positionAX = objects[i].getPointAX();
			float positionAY = objects[i].getPointAY();
			float positionBX = objects[i].getPointBX();
			float positionBY = objects[i].getPointBY();
			float speed = objects[i].getSpeed();

			//std::cout << "From " << positionAX << ":" << positionAY << " to " << positionBX << ":" << positionBY << "  Speed: " << speed << std::endl;

			//float differenceX = positionBX - positionAX;
			//float differenceY = positionBY - positionAY;

			//float ratio = differenceX / differenceY;

			float oldCoordinatesX = objects[i].getCoordinatesX();
			float oldCoordinatesY = objects[i].getCoordinatesY();

			objects[i].setOldCoordinatesX(oldCoordinatesX);
			objects[i].setOldCoordinatesY(oldCoordinatesY);

			//std::cout << "Old coordinates: " << oldCoordinatesX << ":" << oldCoordinatesY << std::endl;

			float newCoordinatesX;
			float newCoordinatesY;

			//if (newCoordinatesX < positionBX)
			//{
			//	//std::cout << "Condition 1" << std::endl;
			//	objects[i].setCoordinatesX(newCoordinatesX);
			//	objects[i].setCoordinatesY(newCoordinatesY);
			//}
			//else
			//{
			//	//std::cout << "Condition 2" << std::endl;
			//	objects[i].setCoordinatesX(positionBX);
			//	objects[i].setCoordinatesY(positionBY);
			//}
			////std::cout << "Process: " << objects[i].getCoordinatesX() << std::endl;


			float deltaX = positionBX - oldCoordinatesX;
			float deltaY = positionBY - oldCoordinatesY;

			float originalDeltaX = positionBX - positionAX;
			float originalDeltaY = positionBY - positionAY;
			float originalDistance = sqrt(originalDeltaX*originalDeltaX + originalDeltaY * originalDeltaY);
			//std::cout << "OriX,Y,Distance: " << originalDeltaX << "|" << originalDeltaY << "|" << originalDistance << std::endl;

			float distance = sqrt(deltaX*deltaX + deltaY*deltaY);
			//std::cout << "Delta X and Y: " << deltaX << " " << deltaY << "  Distance: " << distance << std::endl;

			float dvx = deltaX * speed / distance; //Normalizing and multiplying by max speed
			float dvy = deltaY * speed / distance;
			//std::cout << "Normalization dvx and dvy: " << dvy << ":" << dvx << std::endl;

			float hSpeed = objects[i].getHSpeed();
			float vSpeed = objects[i].getVSpeed();
			//std::cout << "Old H and V velocities: " << hSpeed << ":" << vSpeed << std::endl;

			deltaX = dvx - hSpeed;
			deltaY = dvy - vSpeed;
			//std::cout << "New delta X and Y: " << deltaX << ":" << deltaY << std::endl;

			float diffSize = sqrt(deltaX*deltaX + deltaY*deltaY);
			//std::cout << "diffSize: " << diffSize << std::endl;

			float maxAcc = objects[i].getAccel();
			float ax = maxAcc * deltaX / diffSize;
			float ay = maxAcc * deltaY / diffSize;
			//std::cout << "Acceleration ax, ay: " << ax << ":" << ay << std::endl;

			hSpeed += ax * deltaT; // dt is the time that passed since the last frame
			vSpeed += ay * deltaT; // 
			//std::cout << "New H and V velocities: " << hSpeed << ":" << vSpeed << std::endl;

			newCoordinatesX = oldCoordinatesX + hSpeed;
			newCoordinatesY = oldCoordinatesY + vSpeed;
			//std::cout << "New Coordinates: " << newCoordinatesX << ":" << newCoordinatesY << std::endl;

			objects[i].setHSpeed(hSpeed);
			objects[i].setVSpeed(vSpeed);


			// Check if destination is reached
			float deltaDistanceCheckX = positionBX - newCoordinatesX;
			float deltaDistanceCheckY = positionBY - newCoordinatesY;

			float timeToStop = hSpeed / maxAcc;
			//std::cout << "Time to stop: " << timeToStop << std::endl;
			////std::cout << "hSpeed * timeToStop / 2 >= distance " << hSpeed << "*" << timeToStop << "/2 >=" << distance << std::endl;
			//std::cout << "Original distance: " << originalDistance << " /2 >= " << distance << std::endl;
			if (originalDistance / 2 >= distance && objects[i].getAccelState() == 0)
			{
				//std::cout << "Condition 1" << std::endl;
				maxAcc = 0 - maxAcc;
				objects[i].setAccelState(1);
				objects[i].setAccel(maxAcc);
			}
			//else
			//{
			//	if (objects[i].getAccelState() == 0)
			//	{
			//		objects[i].setAccelState(1);
			//	}
			//	//std::cout << "Condition 2" << std::endl;
			//}

						float newDistance = sqrt(deltaDistanceCheckX*deltaDistanceCheckX + deltaDistanceCheckY*deltaDistanceCheckY);
			//std::cout << "NewDistance > distance " << newDistance << "|" << distance << std::endl;
			if (newDistance > distance)
			{
				objects[i].setCoordinatesX(positionBX);
				objects[i].setCoordinatesY(positionBY);
				objects[i].setAccelState(0);
				objects[i].setSleepTime(20);

				objects[i].setPointAX(positionBX);
				objects[i].setPointAY(positionBY);
				objects[i].setPointBX(positionAX);
				objects[i].setPointBY(positionAY);

				objects[i].setHSpeed(0);
				objects[i].setVSpeed(0);

				// Resetting acceleration to positive again
				maxAcc = 0 - maxAcc;
				objects[i].setAccel(maxAcc);
			}
			else
			{
				objects[i].setCoordinatesX(newCoordinatesX);
				objects[i].setCoordinatesY(newCoordinatesY);
			}
		}
		else
		{
			objects[i].setSleepTime(sleepTime - deltaT);
		}
	}
}

void verticalMovement(Player &player, double deltaT, vector<MovingPlatform> hCollition)
{
	float playerYCoordinates = player.getCoordinatesY();
	float platformYCoordinates = hCollition[0].getCoordinatesY();

	float platformXCoordinates = hCollition[0].getCoordinatesX();
	float platformXOldCoordinates = hCollition[0].getOldCoordinatesX();
	float deltaX = platformXCoordinates - platformXOldCoordinates;

	//std::cout << "Old,New,Dif" << platformXOldCoordinates << "|" << platformXCoordinates << "|" << deltaX << std::endl;
	//std::cout << "playerYCoordinates > platformYCoordinates" << playerYCoordinates << "|" << platformYCoordinates << std::endl;
	//std::cout << player.getVSpeed() << std::endl;
	if (playerYCoordinates > platformYCoordinates)
	{
		//std::cout << "Condition 1" << std::endl;
		float platformHeight = hCollition[0].getHeight();
		player.setCoordinatesY(platformYCoordinates + platformHeight);
		player.setCoordinatesX(player.getCoordinatesX() + deltaX);
		player.setVState(2);
		player.setVspeed(0);
	}
	else
	{
		//std::cout << "Condition 2" << std::endl;
		float platformHeight = hCollition[0].getHeight();
		player.setCoordinatesY(platformYCoordinates - platformHeight - 0.1);
		player.setVspeed(0);
	}

}
void horizontalMovement(Player &player, double deltaT, vector<MovingPlatform> vCollition)
{
	//std::cout << "PLATFORM HORIZONTAL MOVEMENT" << std::endl;
	if (vCollition.size() > 0)
	{
		if (player.getCoordinatesY() != vCollition[0].getCoordinatesY() + vCollition[0].getHeight())
		{
			int platformCoordinatesX = vCollition[0].getCoordinatesX();
			int platformWide = vCollition[0].getWide();
			float newCoordinates = 0;

			int playerCoordinatesX = player.getCoordinatesX();
			if (playerCoordinatesX < platformCoordinatesX)	// Player is to the left of the platform blocks
			{
				//std::cout << "CONDITION 1" << std::endl;
				newCoordinates = platformCoordinatesX - platformWide - 0.1; // Block location + Block wide + small number
			}
			else	// Player is to the right of platform blocks
			{
				//std::cout << "CONDITION 2" << std::endl;
				newCoordinates = platformCoordinatesX + platformWide + 0.1; // Block location + Block wide + small number
			}

			player.setCoordinatesX(newCoordinates);
			player.setHspeed(0);	// Setting speed to 0
			player.setHState(0);	// Setting state to standings
		}
	}
}