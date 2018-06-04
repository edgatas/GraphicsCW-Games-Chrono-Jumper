
//and draws a spinning rectangle

//#include <windows.h>		// Header file for Windows
#include <iostream>

#include "Path_Calculations.h"
#include "Objects.h"
#include "Objects_Loader.h"
#include "Collision_Detection.h"
#include "Camera.h"
#include "Settings.h"
#include "Editor.h"
#include "Algorithms.h"
#include "Textures.h"

#include <fstream>

#include "PNG_Loader/nvImage.h"


int	mouse_x=0, mouse_y=0;
int screenWidth=1000, screenHeight=600;
bool keys[256];
float spin=0;
float speed=0;

//CIRCLES
float testCircle[144];

//MOVEMENT OF OBJECT
void jump();
bool jumpActive = false;

////CAMERA MOVEMENT
Camera *camera;

//OTHER MOVEMENT

//OBJECT POSITION
GLfloat mat[16];
bool done = false;

//SCREEN POSITION
void updateScreenPosition();
float xMin = 0;
float xMax = 1000;
float yMin = 0;
float yMax = 500;

//COLLISION DETECTION

vector<int> hCollitions;
vector<int> vCollitions;

//DRAWING FUNCTIONS
//void polygonWithoutRotation();
//void polygonWithRotation();
void drawPlayer(std::vector<float>, float translationX, float translationY);

//PLAYER
Player *player;
float timeWarp;
void respawn();

//MOUSE WORLD POSITION
float worldX;
float worldY;

// TIMER
// convert clock ticks to time increment suitable for simulation constants
double timerFrequencyRecip = 0.000005;  // Only needs to be changed to change speed of simulation but is platform independent
										// Smaller values will slow down the simulation, larger values will speed it up

__int64 prevTime = 0;				// Previous count
double deltaT = 0;

//WORLD CREATOR MODE
void EditorInit();
void loadLevel();
bool creatorMode = false;
Interface *editorUI;
int currentObject = 1;
int objectCount = 4;
float timeAfterPress = 0;
bool addObject = false;

bool ghostPlatform = false;
int platformPosition1X = 0;
int platformPosition1Y = 0;

bool freezeTime = false;

Ground *editorGroundGrassObject;
Ground *editorGroundEarthObject;
MovingPlatform *editorPlatformObject;
Crystal *editorCrystalBlueObject;

// TEXTURES
GLuint groundGrass;
GLuint groundEarth;
GLuint movingPlatform;
GLuint backGround1;
GLuint backGround2;
GLuint backGround3;
GLuint backGround4;
GLuint character1;

int warpTextures;
float warpTexuresTime;
bool warpTexturesState;
GLuint warp1;
GLuint warp2;
GLuint warp3;
GLuint warp4;
GLuint warp5;
GLuint crystals;
GLuint complete;
GLuint gameover;



//SETTINGS
VideoSettings *videoSettings;

// FPS
FPS *fps;

// OBJECTS
Ground *grassGround;
GroundCreator *groundGrassObjects;
GroundCreator *groundEarthObjects;
MovingPlatformHolder *movingPlatformObjects;
CrystalHolder *crystalObjects;

float translationX = 0;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void updateGame();			//called in winmain to update everything in the game
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();         //called in winmain to process keyboard input

/*************    START OF OPENGL FUNCTIONS   ****************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// Do I even need this here? Going to check tomorrow !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	processKeys();

	////CIRCLE DRAWING
	//glPushMatrix();
	//glBegin(GL_LINE_LOOP);
	//for (int i = 0; i < 144; i++)
	//{
	//	glVertex2f(testCircle[i], testCircle[i + 1]);
	//	i++;
	//}
	//glEnd();
	//glPopMatrix();

	// BACKGROUNDS

	float cameraX = camera->getXCoordinates();
	float camreaY = camera->getYCoordinates();

	float resolutionX = videoSettings->getResolutionX();
	float resolutionY = videoSettings->getResolutionY();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backGround3);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);

	glTexCoord2f(cameraX / 4000 - 1, 1);	glVertex2f(cameraX - resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 4000, 1);		glVertex2f(cameraX + resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 4000, 0);		glVertex2f(cameraX + resolutionX / 2, camreaY - resolutionY / 2);
	glTexCoord2f(cameraX / 4000 - 1, 0);	glVertex2f(cameraX - resolutionX / 2, camreaY - resolutionY / 2);


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backGround4);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);

	glTexCoord2f(cameraX / 10000 - 1, 1);	glVertex2f(cameraX - resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 10000, 1);		glVertex2f(cameraX + resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 10000, 0);		glVertex2f(cameraX + resolutionX / 2, camreaY - resolutionY / 2);
	glTexCoord2f(cameraX / 10000 - 1, 0);	glVertex2f(cameraX - resolutionX / 2, camreaY - resolutionY / 2);


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();



	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backGround2);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);

	glTexCoord2f(cameraX / 3000 - 1, 1);	glVertex2f(cameraX - resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 3000, 1); glVertex2f(cameraX + resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX / 3000, 0);	glVertex2f(cameraX + resolutionX / 2, camreaY - resolutionY / 2);
	glTexCoord2f(cameraX / 3000 - 1, 0);	glVertex2f(cameraX - resolutionX / 2, camreaY - resolutionY / 2);


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backGround1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();

	glColor3ub(255, 255, 255); // Removing any color

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_POLYGON);

	glTexCoord2f(cameraX/2000 -1, 1);	glVertex2f(cameraX - resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX/2000, 1); glVertex2f(cameraX + resolutionX / 2, camreaY + resolutionY / 2);
	glTexCoord2f(cameraX/2000, 0);	glVertex2f(cameraX + resolutionX / 2, camreaY - resolutionY / 2);
	glTexCoord2f(cameraX/2000 -1, 0);	glVertex2f(cameraX - resolutionX / 2, camreaY - resolutionY / 2);


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnd();
	glPopMatrix();





	if (creatorMode == true)
	{
		//editorUI->update(*camera, *videoSettings);
		//editorUI->draw();

		int cameraSpeedMultiplayer = 100;
		if (keys['W'])
		{
			camera->setYCoordinates(camera->getYCoordinates() + deltaT * cameraSpeedMultiplayer);
		}
		if (keys['S'])
		{
			camera->setYCoordinates(camera->getYCoordinates() - deltaT * cameraSpeedMultiplayer);
		}
		if (keys['A'])
		{
			camera->setXCoordinates(camera->getXCoordinates() - deltaT * cameraSpeedMultiplayer);
		}
		if (keys['D'])
		{
			camera->setXCoordinates(camera->getXCoordinates() + deltaT * cameraSpeedMultiplayer);
		}

		if (keys['E'] && timeAfterPress > 5)
		{
			timeAfterPress = 0;
			if (currentObject == objectCount)
			{
				currentObject = 1;
			}
			else
			{
				currentObject++;
			}
		}
		if (keys['Q'] && timeAfterPress > 5)
		{
			timeAfterPress = 0;
			if (currentObject == 1)
			{
				currentObject = objectCount;
			}
			else
			{
				currentObject--;
			}
		}

		if (keys['F'] && timeAfterPress > 5)
		{
			timeAfterPress = 0;
			if (freezeTime == false)
			{
				freezeTime = true;
			}
			else
			{
				freezeTime = false;
			}
			
		}
		if (keys[VK_F9] && timeAfterPress > 5)
		{
			delete crystalObjects;
			init();
		}

		if (keys[VK_F3] && timeAfterPress > 5)
		{
			remove("GameData/grassGround.txt");
			remove("GameData/earthGround.txt");
			remove("GameData/crystals.txt");
			remove("GameData/platforms.txt");
		}

		if (keys[VK_F2] && timeAfterPress > 5)
		{
			timeAfterPress = 0;
			delete groundGrassObjects;
			delete groundEarthObjects;
			delete movingPlatformObjects;
			delete crystalObjects;
			init();
		}
		if (keys[VK_F1] && timeAfterPress > 5)
		{
			timeAfterPress = 0;
			
			// GRASS GROUND
			ofstream groundGrassOut;
			groundGrassOut.open("GameData/grassGround.txt", ios::out | ios::trunc);
			if (groundGrassOut.is_open())
			{
				vector<Ground> temp = groundGrassObjects->getGroundObjects();
				int size = temp.size();
				for (unsigned int i = 0; i < size; i++)
				{
					groundGrassOut << temp[i].getCoordinatesX() << " " << temp[i].getCoordinatesY() << " " << temp[i].getHeight() << " " << temp[i].getWide() << "\n";
				}
				groundGrassOut.close();
			}
			// EARTH GROUND
			ofstream EarthGrassOut;
			EarthGrassOut.open("GameData/earthGround.txt", ios::out | ios::trunc);
			if (EarthGrassOut.is_open())
			{
				vector<Ground> temp = groundEarthObjects->getGroundObjects();
				int size = temp.size();
				for (unsigned int i = 0; i < size; i++)
				{
					EarthGrassOut << temp[i].getCoordinatesX() << " " << temp[i].getCoordinatesY() << " " << temp[i].getHeight() << " " << temp[i].getWide() << "\n";
				}
				EarthGrassOut.close();
			}
			// CRYSTALS
			ofstream crystalsOut;
			crystalsOut.open("GameData/crystals.txt", ios::out | ios::trunc);
			if (crystalsOut.is_open())
			{
				vector<Crystal> temp = crystalObjects->getObjects();
				int size = temp.size();
				for (unsigned int i = 0; i < size; i++)
				{
					crystalsOut << temp[i].getCoordinatesX() << " " << temp[i].getCoordinatesY() << "\n";
				}
				crystalsOut.close();
			}

			// PLATFORMS
			ofstream platformsOut;
			platformsOut.open("GameData/platforms.txt", ios::out | ios::trunc);
			if (platformsOut.is_open())
			{
				vector<MovingPlatform> temp = movingPlatformObjects->getObjects();
				int size = temp.size();
				for (unsigned int i = 0; i < size; i++)
				{
					platformsOut << temp[i].getPointAX() << " " << temp[i].getPointAY() << " " <<
						temp[i].getPointAX() << " " << temp[i].getPointAY() << " " << temp[i].getPointBX() << " " << temp[i].getPointBY() << " " <<
						temp[i].getWide() << " " << temp[i].getHeight() << " " << temp[i].getSpeed() << "\n";
				}
				platformsOut.close();
			}
		}


		switch (currentObject)
		{
		case 1:
		{
			if (keys['T'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorGroundGrassObject->setWide(editorGroundGrassObject->getWide() + 40);
			}
			if (keys['G'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorGroundGrassObject->setWide(editorGroundGrassObject->getWide() - 40);
			}

			editorGroundGrassObject->setCoordinates(findClosesXCoordinates(worldX), findClosesYCoordinates(worldY));
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, editorGroundGrassObject->getTexture());
			editorGroundGrassObject->draw();
			glDisable(GL_TEXTURE_2D);

			if (addObject == true)
			{
				groundGrassObjects->addGroundObject(*editorGroundGrassObject);
				addObject = false;
			}

		}
		break;

		case 2:
		{
			if (keys['T'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorGroundEarthObject->setWide(editorGroundEarthObject->getWide() + 40);
			}
			if (keys['G'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorGroundEarthObject->setWide(editorGroundEarthObject->getWide() - 40);
			}

			editorGroundEarthObject->setCoordinates(findClosesXCoordinates(worldX), findClosesYCoordinates(worldY));

			editorGroundEarthObject->setCoordinates(findClosesXCoordinates(worldX), findClosesYCoordinates(worldY));
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, editorGroundEarthObject->getTexture());
			editorGroundEarthObject->draw();
			glDisable(GL_TEXTURE_2D);

			if (addObject == true)
			{

				groundEarthObjects->addGroundObject(*editorGroundEarthObject);
				addObject = false;
			}
		}
		break;

		case 3:
		{
			if (keys['T'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorPlatformObject->setWide(editorPlatformObject->getWide() + 40);
			}
			if (keys['G'] && timeAfterPress > 2)
			{
				timeAfterPress = 0;
				editorPlatformObject->setWide(editorPlatformObject->getWide() - 40);
			}

			editorPlatformObject->setCoordinatesX(findClosesXCoordinates(worldX));
			editorPlatformObject->setCoordinatesY(findClosesYCoordinates(worldY));

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, editorPlatformObject->getTexture());
			editorPlatformObject->draw();
			glDisable(GL_TEXTURE_2D);

			if (addObject == true)
			{
				if (ghostPlatform == false)
				{

					platformPosition1X = findClosesXCoordinates(worldX);
					platformPosition1Y = findClosesXCoordinates(worldY);

					ghostPlatform = true;
				}
				else
				{
					editorPlatformObject->setCoordinatesX(platformPosition1X);
					editorPlatformObject->setCoordinatesY(platformPosition1Y);
					editorPlatformObject->setPointAX(platformPosition1X);
					editorPlatformObject->setPointAY(platformPosition1Y);
					editorPlatformObject->setPointBX(findClosesXCoordinates(worldX));
					editorPlatformObject->setPointBY(findClosesYCoordinates(worldY));
					editorPlatformObject->setSpeed(20);


					movingPlatformObjects->addObject(*editorPlatformObject);
					addObject = false;
					ghostPlatform = false;

				}
				addObject = false;
			}
		}
		break;

		case 4:
		{
			editorCrystalBlueObject->setCoordinatesX(findClosesXCoordinates(worldX));
			editorCrystalBlueObject->setCoordinatesY(findClosesXCoordinates(worldY));
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, crystals);
			editorCrystalBlueObject->draw();
			glDisable(GL_TEXTURE_2D);

			if (addObject == true)
			{

				crystalObjects->addObject(*editorCrystalBlueObject);
				addObject = false;
			}

		}
		break;
		}



		if (ghostPlatform == true)
		{

			glPushMatrix();

			glColor3ub(255, 0, 0); // Removing any color
			glLineWidth(5.0);

			glBegin(GL_LINES);

			glVertex2f(platformPosition1X, platformPosition1Y);
			glVertex2f(findClosesXCoordinates(worldX), findClosesXCoordinates(worldY));

			glEnd();
			glPopMatrix();
		}

	}
	else
	{
		timeWarp += deltaT;
		if (keys['A'] && player->getDead() == false)
		{
			player->setHState(1);	// Setting state to negative movement
			camera->setXCoordinates(player->getCoordinatesX());
		}
		if (keys['D'] && player->getDead() == false)
		{
			player->setHState(2);	// Setting state to positive movement
			camera->setXCoordinates(player->getCoordinatesX());
		}
		if (keys[VK_SPACE] && timeAfterPress > 5 && player->getDead() == false)
		{
			if (player->getVState() == 3)
			{
				jump();
			}
		}
		// Total Reset
		if (keys[VK_F5])
		{
			//std::cout << "FULL RESET ACTIVATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			delete groundGrassObjects;
			delete groundEarthObjects;
			delete movingPlatformObjects;
			delete crystalObjects;
			init();
		}
		if (keys['J'] && timeWarp > 30 && player->getDead() == false)
		{
			timeWarp = 0;
			player->setCoordinatesX(player->getPlayerHistory()[0].getCoordinatesX());
			player->setCoordinatesY(player->getPlayerHistory()[0].getCoordinatesY());
		}
		if (keys['R'] && timeAfterPress > 30)
		{
			timeAfterPress = 0;
			respawn();
		}
	}


	glLoadIdentity();



	glEnable(GL_TEXTURE_2D);

	if (warpTexuresTime <= 0) { warpTexturesState = true; }
	if (warpTexuresTime >= 50) { warpTexturesState = false; }

	if (warpTexturesState == true)
	{
		warpTexuresTime += deltaT * 5;
	}
	else
	{
		warpTexuresTime -= deltaT * 5;
	}

	warpTextures = (int)warpTexuresTime / 10;
	switch (warpTextures)
	{
	case 0:
	{
		glBindTexture(GL_TEXTURE_2D, warp1);
	}
	break;
	case 1:
	{
		glBindTexture(GL_TEXTURE_2D, warp2);
	}
	break;
	case 2:
	{
		glBindTexture(GL_TEXTURE_2D, warp3);
	}
	break;
	case 3:
	{
		glBindTexture(GL_TEXTURE_2D, warp4);
	}
	break;
	case 4:
	{
		glBindTexture(GL_TEXTURE_2D, warp5);
	}
	break;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (player->getPlayerHistory().size() > 0 && timeWarp > 30)
	{
		Marker *mark = new Marker(player->getPlayerHistory()[0].getCoordinatesX(), player->getPlayerHistory()[0].getCoordinatesY());
		mark->draw();
	}


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);




	////// TESTING SIDE


	//////*std::cout << grassGround->getCoordinatesX() << " " << testingGround->getCoordinatesY() << " " << worldX << " " << worldY << std::endl;

	if (groundGrassObjects->getGroundObjects().size() > 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, groundGrass);
		groundGrassObjects->drawGround(*camera);
		glDisable(GL_TEXTURE_2D);
	}

	if (groundEarthObjects->getGroundObjects().size() > 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, groundEarth);
		groundEarthObjects->drawGround(*camera);
		glDisable(GL_TEXTURE_2D);
	}
	if (movingPlatformObjects->getObjects().size() > 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, movingPlatform);
		movingPlatformObjects->drawObjects(*camera);
		glDisable(GL_TEXTURE_2D);
	}

	if (crystalObjects->getObjects().size() > 0)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, crystals);
		crystalObjects->drawObjects(*camera, *videoSettings);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, character1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	player->draw(deltaT);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	if (player->getDead())
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, gameover);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();

		glColor3ub(255, 255, 255); // Removing any color

		glBegin(GL_POLYGON);

		glTexCoord2f(0.0, 1.0);		glVertex2f(camera->getXCoordinates() - (videoSettings->getResolutionX() / 2), camera->getYCoordinates() + (videoSettings->getResolutionY() / 2));
		glTexCoord2f(1.0, 1.0);		glVertex2f(camera->getXCoordinates() + (videoSettings->getResolutionX() / 2), camera->getYCoordinates() + (videoSettings->getResolutionY() / 2));
		glTexCoord2f(1.0, 0.0);		glVertex2f(camera->getXCoordinates() + (videoSettings->getResolutionX() / 2), camera->getYCoordinates() - (videoSettings->getResolutionY() / 2));
		glTexCoord2f(0.0, 0.0);		glVertex2f(camera->getXCoordinates() - (videoSettings->getResolutionX() / 2), camera->getYCoordinates() - (videoSettings->getResolutionY() / 2));

		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}


	if (crystalObjects->checkCrystals())
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, complete);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();

		glColor3ub(255, 255, 255); // Removing any color

		glBegin(GL_POLYGON);


		glTexCoord2f(0.0, 1.0);		glVertex2f(camera->getXCoordinates() - (videoSettings->getResolutionX() / 2),
			camera->getYCoordinates() + (videoSettings->getResolutionY() / 2));
		glTexCoord2f(1.0, 1.0);		glVertex2f(camera->getXCoordinates() + (videoSettings->getResolutionX() / 2),
			camera->getYCoordinates() + (videoSettings->getResolutionY() / 2));
		glTexCoord2f(1.0, 0.0);		glVertex2f(camera->getXCoordinates() + (videoSettings->getResolutionX() / 2),
			camera->getYCoordinates() - (videoSettings->getResolutionY() / 2));
		glTexCoord2f(0.0, 0.0);		glVertex2f(camera->getXCoordinates() - (videoSettings->getResolutionX() / 2),
			camera->getYCoordinates() - (videoSettings->getResolutionY() / 2));

		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}


	glFlush();

	if (player->getCoordinatesY() < -1000)
	{
		player->setCoordinates(0, 50);
		player->setHspeed(0);
		player->setVspeed(0);
		player->setVState(2);
	}

	//std::cout << "X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;

	//std::cout << "********************************************************************" << std::endl;

	//std::cout << groundGrassObjects->getgroundGrassObjects() << std::endl;



	// SETTINGS
	//videoSettings->setResolution(screenWidth, screenHeight);
}

void updateGame()
{
	fps->calculate();

	updateScreenPosition();

	// COLLISION DETECTION AND MOVEMENT
		
	// GRAVITY 
	//std::cout << "New X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;

	//std::cout << "GRAVITY IS ACTIVE" << std::endl;
	gravity(*player, deltaT);

	// HORIONTAL PLANE COLLITION

	//std::cout << "After Gravity X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;
	vector<Ground> vCollitions2 = playerToGroundHorizontal2(*player, groundGrassObjects->getGroundObjects(), *camera);
	verticalMovement(*player, deltaT, vCollitions2);



	vector<MovingPlatform> vCollitionsPlatform = playerToMovingPlatformHorizontal(*player, movingPlatformObjects->getObjects(), *camera);
	if (vCollitionsPlatform.size() > 0)
	{
		//verticalMovement(*player, deltaT, vCollitionsPlatform);
		//player->setOtherHCollitions(true);
		freezeTime = true;
		player->setDead(true);
	}
	else
	{
		//player->setOtherHCollitions(false);
	}

	//std::cout << "After Vertical Collition X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;

	movement(*player, deltaT);
	//std::cout << "After Movement X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;

	// VERTICAL PLANE COLLITION

	vector<Ground> hCollitions2 = playerToGroundVertical2(*player, groundGrassObjects->getGroundObjects(), *camera);
	horizontalMovement(*player, deltaT, hCollitions2);
	hCollitions2 = playerToGroundVertical2(*player, groundEarthObjects->getGroundObjects(), *camera);
	horizontalMovement(*player, deltaT, hCollitions2);

	//std::cout << "After Horizontal Collition X:" << player->getCoordinatesX() << " Y:" << player->getCoordinatesY() << std::endl;

	int crystalCheck = playerToCrystal(*player, crystalObjects->getObjects());
	if (crystalCheck != -1)
	{
		crystalObjects->changeCrystalState(crystalCheck);
	}



	// COLLITION END

	if (movingPlatformObjects->getObjects().size() > 0 && freezeTime == false)
	{
		movingPlatformObjects->activeMovement(deltaT);
	}
	
	player->recalculateHistory(deltaT);
	player->addPosition();


	vector<MovingPlatform> hCollitionsPlatform = playerToMovingPlatformVertical(*player, movingPlatformObjects->getObjects(), *camera);
	if (hCollitionsPlatform.size() > 0)
	{
		freezeTime = true;
		player->setDead(true);
	}



	timeAfterPress += deltaT;
}

void reshape(int width, int height)// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height; 		

	glViewport(0,0,width,height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(xMin,xMax,yMin,yMax);					// set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}

void respawn()
{
	player->setCoordinates(0, 100);
	timeWarp = 0;
	delete groundGrassObjects;
	delete groundEarthObjects;
	delete movingPlatformObjects;
	delete crystalObjects;
	groundGrassObjects = new GroundCreator();
	groundEarthObjects = new GroundCreator();
	movingPlatformObjects = new MovingPlatformHolder();
	crystalObjects = new CrystalHolder();
	loadLevel();
	freezeTime = false;
	player->setDead(false);
}

void init()
{

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	reshape(screenWidth, screenHeight);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	player = new Player();
	player->setCoordinates(0, 100);
	timeWarp = 0;
	camera = new Camera;

	videoSettings = new VideoSettings();
	videoSettings->setResolution(screenWidth, screenHeight);
	
	editorUI = new Interface(*camera, *videoSettings);

	fps = new FPS();

	// TESTING SIDE

	grassGround = new Ground(0.0,0.0,40,40);

	groundGrassObjects = new GroundCreator();
	groundEarthObjects = new GroundCreator();
	movingPlatformObjects = new MovingPlatformHolder();
	crystalObjects = new CrystalHolder();

	groundGrassObjects->addGroundObject(*grassGround);

	warpTextures = 0;
	warpTexuresTime = 0;
	warpTexturesState = false;
	groundGrass = loadPNG("Textures/Ground1.png");
	groundEarth = loadPNG("Textures/Ground2.png");
	movingPlatform = loadPNG("Textures/MovingPlatform.png");
	backGround1 = loadPNG("Textures/parallax-forest-front-trees.png");
	backGround2 = loadPNG("Textures/parallax-forest-middle-trees.png");
	backGround3 = loadPNG("Textures/parallax-forest-back-trees.png");
	backGround4 = loadPNG("Textures/parallax-forest-lights.png");
	character1 = loadPNG("Textures/Character.png");
	warp1 = loadPNG("Textures/warp1.png");
	warp2 = loadPNG("Textures/warp2.png");
	warp3 = loadPNG("Textures/warp3.png");
	warp4 = loadPNG("Textures/warp4.png");
	warp5 = loadPNG("Textures/warp5.png");
	crystals = loadPNG("Textures/Crystals.png");
	complete = loadPNG("Textures/Complete.PNG");
	gameover = loadPNG("Textures/GameOver.PNG");


	loadLevel();

	player->setDead(false);
}

void EditorInit()
{
	editorGroundGrassObject = new Ground(40, 40);
	editorGroundGrassObject->setTexture(groundGrass);

	editorPlatformObject = new MovingPlatform(0, 0, 80, 40, 5, 5, 5, 5, 5);
	editorPlatformObject->setTexture(movingPlatform);

	editorGroundEarthObject = new Ground(40, 40);
	editorGroundEarthObject->setTexture(groundEarth);

	editorCrystalBlueObject = new Crystal(0, 0);

}

void loadLevel()
{
	fstream grassGroundIn("GameData/grassGround.txt", fstream::in);
	if (grassGroundIn.is_open())
	{
		float coordX, coordY, height, wide;
		float oldCoordX = 1, oldCoordY = 1;

		while (grassGroundIn.eof() == false)
		{
			grassGroundIn >> coordX >> coordY >> height >> wide;
			if ((oldCoordX != coordX) && (oldCoordY != coordY) && abs(coordX) < 10000000)
			{
				Ground *temp = new Ground(coordX, coordY, wide, height);
				groundGrassObjects->addGroundObject(*temp);
			}
		}
		oldCoordX = coordX;
		oldCoordY = coordY;
	}

	fstream earthGroundIn("GameData/earthGround.txt", fstream::in);
	if (earthGroundIn.is_open())
	{
		float coordX, coordY, height, wide;
		float oldCoordX = 1, oldCoordY = 1;

		while (earthGroundIn.eof() == false)
		{
			earthGroundIn >> coordX >> coordY >> height >> wide;
			if ((oldCoordX != coordX) && (oldCoordY != coordY) && abs(coordX) < 10000000)
			{
				Ground *temp = new Ground(coordX, coordY, wide, height);
				groundEarthObjects->addGroundObject(*temp);
			}
		}
		oldCoordX = coordX;
		oldCoordY = coordY;
	}

	fstream crystalsIn("GameData/crystals.txt", fstream::in);
	if (crystalsIn.is_open())
	{
		float coordX, coordY;
		float oldCoordX = 1, oldCoordY = 1;


		while (crystalsIn.eof() == false)
		{
			crystalsIn >> coordX >> coordY;
			if ((oldCoordX != coordX) || (oldCoordY != coordY) && abs(coordX) < 10000000)
			{
				Crystal *temp = new Crystal(coordX, coordY);
				crystalObjects->addObject(*temp);
			}
			oldCoordX = coordX;
			oldCoordY = coordY;
		}
	}



	fstream platformsIn("GameData/platforms.txt", fstream::in);
	if (platformsIn.is_open())
	{
		float coordX, coordY, height, wide, coordAX, coordAY, coordBX, coordBY, speed;
		float oldCoordX = 1, oldCoordY = 1;

		while (platformsIn.eof() == false)
		{
			platformsIn >> coordX >> coordY >> coordAX >> coordAY >> coordBX >> coordBY >> wide >> height >> speed;
			if ((oldCoordX != coordX) && (oldCoordY != coordY) && abs(coordX) < 10000000)
			{
				MovingPlatform *temp = new MovingPlatform(coordX, coordY, wide, height, coordAX, coordAY, coordBX, coordBY, speed);
				movingPlatformObjects->addObject(*temp);
			}
		}
		oldCoordX = coordX;
		oldCoordY = coordY;
	}
}

void processKeys()
{

	// Mode Change. Gameplay/Creative
	if (keys['Z'] && timeAfterPress > 5)
	{
		timeAfterPress = 0;
		if (creatorMode == false)
		{
			creatorMode = true;
			EditorInit();
		}
		else
		{
			creatorMode = false;
		}
	}

}

void jump()
{
	player->setVspeed(player->getJumpPower());
	player->setVState(0);
}

void updateScreenPosition()
{
	if (creatorMode == false)
	{
		camera->updateCamera(*player);
	}
	
	xMin = camera->getXCoordinates() - (videoSettings->getResolutionX() / 2);
	xMax = camera->getXCoordinates() + (videoSettings->getResolutionX() / 2);
	yMin = camera->getYCoordinates() - (videoSettings->getResolutionY() / 2);
	yMax = camera->getYCoordinates() + (videoSettings->getResolutionY() / 2);

	videoSettings->setResolution(screenWidth, screenHeight);
	reshape(videoSettings->getResolutionX(),videoSettings->getResolutionY());
}

/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;


			// Get the current time
			LARGE_INTEGER t;
			QueryPerformanceCounter(&t);
			__int64 currentTime = t.QuadPart;

			__int64 ticksElapsed = currentTime - prevTime;					// Ticks elapsed since the previous time step
			double deltaTTemp = double(ticksElapsed) * timerFrequencyRecip;		// Convert to second
			//cout << ticksElapsed << " " << deltaT << endl;
																			// STEP THE SIMULATION
			if (deltaTTemp < 100) { deltaT = deltaTTemp; }
			processKeys();							//process keyboard

			updateGame();

			display();								// Draw The Scene
			SwapBuffers(hDC);						// Swap Buffers (Double Buffering)

			// Advance timer
			prevTime = currentTime;					// use the current time as the previous time in the next step

		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);

				if (creatorMode == true)
				{
					addObject = true;
				}
			}
		break;

		case WM_LBUTTONUP:
			{

			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);

				worldX = LOWORD(lParam) + xMin;
				worldY = screenHeight - HIWORD(lParam) + yMin;
		}
		break;

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window

	init();

	reshape(width, height);							// Set Up Our Perspective GL Screen


	
	return true;									// Success
}



