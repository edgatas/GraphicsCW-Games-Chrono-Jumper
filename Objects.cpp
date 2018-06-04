#include "Objects.h"

#include <iostream>

#include <chrono>

/*
Player contructor. Default jump height is set here.
*/
Player::Player()
{
	vSpeed = 0;
	hSpeed = 0;
	jumpPower = 70;
	vState = 2;
	hState = 0;
	maxSpeed = 40;
	timer = 0;
	inAir = 0;
	standingSide = 1;
	animationSpeedMultiplayer = 1;
	wide = 50;
	height = 100;

	otherHCollitions = false;
}
Player::~Player()
{
	// Nothing for now
}

// All Getters for Player class
float Player::getCoordinatesX()			{ return coordinatesX;		}	// return coordinateX
float Player::getCoordinatesY()			{ return coordinatesY;		}	// return coordianteY
float Player::getMaxSpeed()				{ return maxSpeed;			}	// return movement speed
float Player::getVSpeed()				{ return vSpeed;			}	// return vertical speed
float Player::getHSpeed()				{ return hSpeed;			}	// return horizontal speed
float Player::getJumpPower()			{ return jumpPower;			}	// return jump power
int Player::getVState()					{ return vState;			}   // return vertical state of the player
int Player::getHState()					{ return hState;			}	// return horizontal state of player
bool Player::getOtherHCollitions()		{ return otherHCollitions;	}	// return if player is touching any other horizontal surface
int Player::getWide() { return wide; }
int Player::getHeight(){ return height; }
bool Player::getDead() { return dead; }

// All setters for Player class
void Player::setCoordinates(float coordX, float coordY)
{
	coordinatesX = coordX;
	coordinatesY = coordY;
}

void Player::setVspeed(float speed) { vSpeed = speed; }
void Player::setHspeed(float speed) { hSpeed = speed; }
void Player::setCoordinatesX(float coordX) { coordinatesX = coordX; }
void Player::setCoordinatesY(float coordY) { coordinatesY = coordY; }
void Player::setVState(int state) { this->vState = state; }
void Player::setHState(int state) { this->hState = state; }
void Player::setMaxSpeed(float speed) { this->maxSpeed = speed; }
void Player::setOtherHCollitions(bool state) { this->otherHCollitions = state; }
void Player::setDead(bool state) { this->dead = state; }


void Player::addPosition()
{
	TimeGhost *temp = new TimeGhost(coordinatesX, coordinatesY, 20.0);
	playerHistory.push_back(*temp);
}

void Player::recalculateHistory(float deltaT)
{
	float newSize = playerHistory.size();
	for (signed int i = 0; i < newSize; i++)
	{
		float newTimeToLive = playerHistory[i].getTimeToLive() - deltaT;
		if (newTimeToLive < 0)
		{
			playerHistory.erase(playerHistory.begin() + i);
			newSize = playerHistory.size();
			i--;
			
		}
		else
		{
			playerHistory[i].setTimeToLive(newTimeToLive);
		}
		
	}
}

void Player::checkStandingSide()
{
	if (hSpeed > 0)
	{
		this->standingSide = 1;
	}
	else
	{
		if (hSpeed < 0)
		{
			this->standingSide = 0;
		}
	}

	if (vState == 1)
	{
		inAir = true;
	}
	if (vState == 3 && inAir == true)
	{
		inAir = false;
	}

	animationSpeedMultiplayer = 0 + abs(hSpeed / 20);
}

/*
Draw a single player
*/
void Player::draw(float deltaT)
{
	checkStandingSide();

	glPushMatrix();
	glColor3ub(255, 255, 255); // Removing any color
	glTranslatef(getCoordinatesX(), getCoordinatesY(), 0.0);
	glBegin(GL_POLYGON);

	timer += deltaT;

	//std::cout << timer << "|" << deltaT << std::endl;
	if (dead == true)
	{
		if (timer < 100)
		{
			if (standingSide == 1)
			{
				// WOUNDED 2 LEFT

				glTexCoord2f(68.0f / 256.0f, 112.0f / 256.0f);					glVertex2f(-35, 100);
				glTexCoord2f(37.0f / 256.0f, 112.0f / 256.0f);					glVertex2f(35, 100);
				glTexCoord2f(37.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(35, 0);
				glTexCoord2f(68.0f / 256.0f, 73.0f / 256.0f); 					glVertex2f(-35, 0);
				timer++;
			}
			else
			{
				glTexCoord2f(37.0f / 256.0f, 112.0f / 256.0f);					glVertex2f(-35, 100);
				glTexCoord2f(68.0f / 256.0f, 112.0f / 256.0f);					glVertex2f(35, 100);
				glTexCoord2f(68.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(35, 0);
				glTexCoord2f(37.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(-35, 0);
				timer++;
			}

		}
		else
		{
			if (standingSide == 1)
			{
				glTexCoord2f(161.0f / 256.0f, 102.0f / 256.0f);			glVertex2f(-50, 55);
				glTexCoord2f(114.0f / 256.0f, 102.0f / 256.0f);						glVertex2f(50, 55);
				glTexCoord2f(114.0f / 256.0f, 73.0f / 256.0f);			glVertex2f(50, -20);
				glTexCoord2f(161.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(-50, -20);
			}
			else
			{
				glTexCoord2f(114.0f / 256.0f, 102.0f / 256.0f);					glVertex2f(-50, 55);
				glTexCoord2f(161.0f / 256.0f, 102.0f / 256.0f);					glVertex2f(50, 55);
				glTexCoord2f(161.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(50, -20);
				glTexCoord2f(114.0f / 256.0f, 73.0f / 256.0f);					glVertex2f(-50, -20);
			}
		}
	}
	else
	{

		if (hSpeed > 0)
		{
			if (inAir == true)
			{
				// STANDING and FACING RIGHT
				glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
				glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f); 					glVertex2f(35, 100);
				glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);			glVertex2f(35, 0);
				glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f); 					glVertex2f(-35, 0);
			}
			else
			{
				if (timer < 2 / animationSpeedMultiplayer)
				{
					// WALKING 1 RIGHT
					glTexCoord2f(32.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(1.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(1.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(32.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
				}
				if (timer >= 2 / animationSpeedMultiplayer && timer < 4 / animationSpeedMultiplayer)
				{
					//WALKING 2 RIGHT
					glTexCoord2f(68.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(37.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(37.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(68.0f / 256.0f, 138.0f / 256.0f); 					glVertex2f(-35, 0);
				}
				if (timer >= 4 / animationSpeedMultiplayer)
				{
					// WALKING 3 RIGHT
					glTexCoord2f(103.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(73.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(73.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(103.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
				}
				if (timer > 6 / animationSpeedMultiplayer)
				{
					timer = 0;
				}
			}
		}

		if (hSpeed < 0)
		{
			if (inAir == true)
			{
				// STANDING and FACING LEFT
				glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
				glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(35, 100);
				glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(35, 0);
				glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(-35, 0);
			}
			else
			{
				if (timer < 2 / animationSpeedMultiplayer)
				{
					// WALKING 1 LEFT
					glTexCoord2f(1.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(32.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(32.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(1.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
				}
				if (timer >= 2 / animationSpeedMultiplayer && timer < 4 / animationSpeedMultiplayer)
				{
					// WALKING 2 LEFT
					glTexCoord2f(37.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(68.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(68.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(37.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
				}
				if (timer >= 4 / animationSpeedMultiplayer)
				{
					// WALKING 3 LEFT
					glTexCoord2f(73.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(103.0f / 256.0f, 184.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(103.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(73.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
				}
				if (timer > 6 / animationSpeedMultiplayer)
				{
					timer = 0;
				}
			}
		}

		// STANDING and FACING RIGHT
		if (hSpeed == 0)
		{
			if (standingSide == 1)
			{
				if (timer > 50)
				{
					if ((int)timer % 20 > 10)
					{
						// CHEERING <3
						glTexCoord2f(144.0f / 256.0f, 185.0f / 256.0f);			glVertex2f(-35, 100);
						glTexCoord2f(114.0f / 256.0f, 185.0f / 256.0f);						glVertex2f(35, 100);
						glTexCoord2f(114.0f / 256.0f, 138.0f / 256.0f);		glVertex2f(35, 0);
						glTexCoord2f(144.0f / 256.0f, 138.0f / 256.0f);							glVertex2f(-35, 0);
					}

					else
					{
						// STANDING
						glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
						glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f); 					glVertex2f(35, 100);
						glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);			glVertex2f(35, 0);
						glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f); 					glVertex2f(-35, 0);
					}
				}
				else
				{
					// STANDING
					glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f); 					glVertex2f(35, 100);
					glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);			glVertex2f(35, 0);
					glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f); 					glVertex2f(-35, 0);
				}
			}
			else
			{
				if (timer > 50)
				{
					if ((int)timer % 20 > 10)
					{
						// CHEERING <3
						glTexCoord2f(114.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(-35, 100);
						glTexCoord2f(144.0f / 256.0f, 185.0f / 256.0f);					glVertex2f(35, 100);
						glTexCoord2f(144.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(35, 0);
						glTexCoord2f(114.0f / 256.0f, 138.0f / 256.0f);					glVertex2f(-35, 0);
					}

					else
					{
						// STANDING
						glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
						glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(35, 100);
						glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(35, 0);
						glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(-35, 0);
					}
				}
				else
				{
					// STANDING
					glTexCoord2f(1.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(-35, 100);
					glTexCoord2f(32.0f / 256.0f, 248.0f / 256.0f);					glVertex2f(35, 100);
					glTexCoord2f(32.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(35, 0);
					glTexCoord2f(1.0f / 256.0f, 202.0f / 256.0f);					glVertex2f(-35, 0);
				}
			}
		}
	}
	glEnd();
	glPopMatrix();
}



// Change player X position by a set ammout of distance
void Player::changeTranslationX(float x)
{
	coordinatesX += x;
}

// Change player Y position by a set ammount of distance
void Player::changeTranslationY(float y)
{
	coordinatesY += y;
}

// MIGHT NEED THIS IN THE FUTURE
//
//std::vector<float> returnSpinningPlatformVertexes()
//{
//	std::vector<float> vertexes(8);
//
//	vertexes.push_back(-150);	vertexes.push_back(40);
//	vertexes.push_back(150);	vertexes.push_back(40);
//	vertexes.push_back(150);	vertexes.push_back(-40);
//	vertexes.push_back(-150);	vertexes.push_back(-40);
//
//	return vertexes;
//}
//std::vector<float> returnSpinningPlatformRotation()
//{
//	std::vector<float> vertexes(8);
//}


/*
Ground block contructor. Default coodinates 0,0
*/
Ground::Ground()
{
std:; cout << "New Ground Object" << std::endl;
}
/*
Ground block contructor with set coordinates
*/
Ground::Ground(float x, float y)
{
	locationX = x;
	locationY = y;
}
Ground::Ground(int wideX, int heightY)
{
	wide = wideX;
	height = heightY;
}


Ground::Ground(float x, float y, int wideX, int heightY)
{
	locationX = x;
	locationY = y;
	wide = wideX;
	height = heightY;

}

// Set coordinates of the ground block
void Ground::setCoordinates(float x, float y)
{
	locationX = x;
	locationY = y;
}

 //Draw a single ground block
void Ground::draw()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255); // Removing any color

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	int textureCountH = wide / 40;
	int textureCountV = height / 40;

		glTexCoord2f(0+0.01, textureCountV - 0.01);				glVertex2f(locationX - wide, locationY + height);
		glTexCoord2f(textureCountH-0.01, textureCountV - 0.01); glVertex2f(locationX + wide, locationY + height);
		glTexCoord2f(textureCountH-0.01, 0+0.01);				glVertex2f(locationX + wide, locationY - height);
		glTexCoord2f(0+0.01, 0+0.01);							glVertex2f(locationX - wide, locationY - height);

	glEnd();
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

ostream& operator<<(ostream &out, Ground &object)
{
	std::cout << "Coordinates: " << object.getCoordinatesX() << ":" << object.getCoordinatesY() << " Size: " << object.getWide() << ":" << object.getHeight() << endl;
	return out;
}


//***********************************************************************************************************
// MovingPlatform Class
//***********************************************************************************************************

MovingPlatform::MovingPlatform(float coordinateX, float coordinateY, int wide, int height, float pointAX, float pointAY, float pointBX, float pointBY, int speed)
{
	this->coordinatesX = coordinateX;
	this->coordinatesY = coordinateY;
	this->wide = wide;
	this->height = height;
	this->pointAX = pointAX;
	this->pointAY = pointAY;
	this->pointBX = pointBX;
	this->pointBY = pointBY;
	this->speed = speed;
	this->hSpeed = 0;
	this->vSpeed = 0;
	this->accel = 0.1;
	this->accelState = 0;
	this->sleepTime = 20;
}

//Draw a single ground block
void MovingPlatform::draw()
{
	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);

	int textureCountH = wide / 80;
	int textureCountV = height / 40;

	glTexCoord2f(0, textureCountV);				glVertex2f(coordinatesX - wide, coordinatesY + height);
	glTexCoord2f(textureCountH, textureCountV); glVertex2f(coordinatesX + wide, coordinatesY + height);
	glTexCoord2f(textureCountH, 0);				glVertex2f(coordinatesX + wide, coordinatesY - height);
	glTexCoord2f(0, 0);							glVertex2f(coordinatesX - wide, coordinatesY - height);

	glEnd();
	glPopMatrix();
}

//***********************************************************************************************************
// Marker Class
//***********************************************************************************************************

Marker::Marker(float coordinatesX, float coordinatesY)
{
	this->coordinatesX = coordinatesX;
	this->coordinatesY = coordinatesY;
}
void Marker::draw()
{
	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);				glVertex2f(coordinatesX - 50, coordinatesY + 100);
	glTexCoord2f(1, 1);				glVertex2f(coordinatesX + 50, coordinatesY + 100);
	glTexCoord2f(1, 0);				glVertex2f(coordinatesX + 50, coordinatesY - 0);
	glTexCoord2f(0, 0);				glVertex2f(coordinatesX - 50, coordinatesY - 0);

	glEnd();
	glPopMatrix();
}

//***********************************************************************************************************
// Marker Class
//***********************************************************************************************************

Crystal::Crystal(float coordinatesX, float coordinatesY)
{
	this->coordinatesX = coordinatesX;
	this->coordinatesY = coordinatesY;
	this->state = 0;
}

void Crystal::draw()
{
	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glBegin(GL_POLYGON);


		glTexCoord2f(0.0, 1);				glVertex2f(coordinatesX - 32, coordinatesY + 32);
		glTexCoord2f(0.5, 1);				glVertex2f(coordinatesX + 32, coordinatesY + 32);
		glTexCoord2f(0.5, 0.0);				glVertex2f(coordinatesX + 32, coordinatesY - 32);
		glTexCoord2f(0.0, 0.0);				glVertex2f(coordinatesX - 32, coordinatesY - 32);

	glEnd();
	glPopMatrix();
}

void Crystal::draw(int sequence, float cameraX, float cameraY, VideoSettings settings)
{
	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	if (state == false)
	{

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1);				glVertex2f(coordinatesX - 32, coordinatesY + 32);
		glTexCoord2f(0.5, 1);				glVertex2f(coordinatesX + 32, coordinatesY + 32);
		glTexCoord2f(0.5, 0.0);				glVertex2f(coordinatesX + 32, coordinatesY - 32);
		glTexCoord2f(0.0, 0.0);				glVertex2f(coordinatesX - 32, coordinatesY - 32);
		glEnd();

		glBegin(GL_POLYGON);
		glTexCoord2f(0.5, 1.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) - 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) + 32);
		glTexCoord2f(1.0, 1.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) + 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) + 32);
		glTexCoord2f(1.0, 0.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) + 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) - 32);
		glTexCoord2f(0.5, 0.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) - 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) - 32);
		glEnd();
		glPopMatrix();
	}
	else
	{
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) - 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) + 32);
		glTexCoord2f(0.5, 1.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) + 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) + 32);
		glTexCoord2f(0.5, 0.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) + 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) - 32);
		glTexCoord2f(0.0, 0.0);				glVertex2f(cameraX - (settings.getResolutionX() / 2.2) - 32 + 64 * sequence, cameraY + (settings.getResolutionY() / 2.3) - 32);
		glEnd();
		glPopMatrix();
	}
}

