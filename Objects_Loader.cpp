
#include "Objects_Loader.h"
#include "Algorithms.h"
#include "Text\glfont2.h"
#include "Settings.h"

#include <time.h>
#include <string>

// FPS CLASS

FPS::FPS()
{
	using namespace std::chrono;
	framesPerSecond = 0;
	previousTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
}

void FPS::calculate()
{
	microseconds currentTime = duration_cast< microseconds >(system_clock::now().time_since_epoch());
	float timeDiff = float (currentTime.count() - previousTime.count());
	previousTime = currentTime;
	diffSum += timeDiff;
	diffSumForFrequency += timeDiff;
	

	if (diffSum / 1000000 > 1)
	{
		framesPerSecond = countFramesPerSecond;
		countFramesPerSecond = 0;
		diffSum = 0;
		
	}
	else
	{
		countFramesPerSecond++;
	}
}

int FPS::returnFPS()
{
	return framesPerSecond;
}

void FPS::changeActivation(bool state)
{
	activated = state;
}

void FPS::draw(Camera *camera, VideoSettings *videoSettings)
{

	glLoadIdentity();

	glPushMatrix();

		glfont::GLFont myfont;
		if (!myfont.Create("Text/Arial.glf", 1)) { exit(0); }
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		myfont.Begin();
		glColor3f(1.0, 1.0, 1.0);
		myfont.DrawString("FPS: "+std::to_string(framesPerSecond), 1.0f, camera->getXCoordinates() + (videoSettings->getResolutionX() / 3)
			, camera->getYCoordinates() + (videoSettings->getResolutionY() / 3));
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glEnd();

}

// CREATABLE GROUND

GroundCreator::GroundCreator()
{
	std::cout << "NEW" << std::endl;
}

void GroundCreator::addGroundObject(Ground ground)
{
	groundObjects.push_back(ground);
	
	sortGroundObjects(groundObjects);
}

void GroundCreator::drawGround(Camera camera)
{
	float cameraX = camera.getXCoordinates();
	float cameraY = camera.getYCoordinates();

		drawingFrom = groundDrawingStart(groundObjects, cameraX - 10000);

	if (drawingFrom >= 0)
	{
		int drawingIndex = drawingFrom;

		while (drawingIndex < groundObjects.size() && groundObjects[drawingIndex].getCoordinatesX() < cameraX + 10000)
		{
			Ground test = groundObjects[drawingIndex];
			groundObjects[drawingIndex].draw();
			
			drawingIndex++;
		}
	}
}


//***********************************************************************************************************
// OPERATOR OVERLOADING
//***********************************************************************************************************

ostream& operator<<(ostream &out, vector<Ground> &objects)
{
	int size = objects.size();

	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << i << " X:" << objects[i].getCoordinatesX() << " Y:" << objects[i].getCoordinatesY() <<
			" W:" << objects[i].getWide() << " H:" << objects[i].getHeight() << std::endl;
	}
	return out;
}


//***********************************************************************************************************
// Moving Platforms
//***********************************************************************************************************


MovingPlatformHolder::MovingPlatformHolder()
{

}
void MovingPlatformHolder::addObject(MovingPlatform object)
{
	objects.push_back(object);
	sortMovingPlatformsObjects(objects);
}
void MovingPlatformHolder::drawObjects(Camera camera)
{
	int size = objects.size();
	for (unsigned int i = 0; i < size; i++)
	{
			MovingPlatform test = objects[i];
			objects[i].draw();
	}
}

void MovingPlatformHolder::activeMovement(float deltaT)
{
	platformMove(objects, deltaT);
}

//***********************************************************************************************************
// Crystals
//***********************************************************************************************************

CrystalHolder::CrystalHolder()
{

}
void CrystalHolder::addObject(Crystal crystal)
{
	objects.push_back(crystal);
}
void CrystalHolder::drawObjects(Camera camera, VideoSettings settings)
{
	int size = objects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		Crystal test = objects[i];
		objects[i].draw(i, camera.getXCoordinates(), camera.getYCoordinates(), settings);
	}
}
void CrystalHolder::changeCrystalState(int position)
{
	objects[position].setState(1);
}
bool CrystalHolder::checkCrystals()
{
	unsigned int size = objects.size();

	if (size == 0) { return false; }

	for (unsigned int i = 0; i < size; i++)
	{
		if (objects[i].getState() == false) { return false; }
	}
	return true;
}