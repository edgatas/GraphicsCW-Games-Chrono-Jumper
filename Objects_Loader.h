#pragma once

#ifndef OBJECTS_LOADER
#define OBJECTS_LOADER

//#include <windows.h>
#include "glew.h"

#include "Objects.h"
#include "Camera.h"
#include "Settings.h"


#include <iostream>
#include <vector>


using namespace std;

class FPS
{
private:
	int countFramesPerSecond = 0;
	int framesPerSecond = 0;

	microseconds previousTime;
	float diffSum = 0;
	float diffSumForFrequency = 0;

	bool activated = false;

public:
	FPS();
	void calculate();
	int returnFPS();

	void changeActivation(bool state);
	void draw(Camera *camera, VideoSettings *videoSettings);

};


class GroundCreator
{
private:
	std::vector<Ground> groundObjects;
	int drawingFrom;
	int lastPosition;

	friend ostream& operator<<(ostream &out, vector<Ground> &objects);

public:
	GroundCreator();
	void addGroundObject(Ground ground);
	void drawGround(Camera camera);

	std::vector<Ground> getGroundObjects() { return groundObjects; }
};


class MovingPlatformHolder
{
private:
	std::vector<MovingPlatform> objects;
	int drawingFrom;
	int lastPosition;

public:
	MovingPlatformHolder();
	void addObject(MovingPlatform platform);
	void drawObjects(Camera camera);
	void activeMovement(float deltaT);

	std::vector<MovingPlatform> getObjects() { return objects; }
};

class CrystalHolder
{
private:
	std::vector<Crystal> objects;
public:
	CrystalHolder();
	void addObject(Crystal crystal);
	void drawObjects(Camera camera, VideoSettings settings);
	void changeCrystalState(int position);
	bool checkCrystals();

	std::vector<Crystal> getObjects() { return objects; }
};
#endif