#pragma once

#ifndef CAMERA
#define CAMERA

#include "Objects.h"

class Camera
{
private:
	float xCoordinates;
	float yCoordinates;


public:
	Camera();
	void updateCamera(Player player);


	float getXCoordinates();
	float getYCoordinates();
	void setXCoordinates(float X);
	void setYCoordinates(float Y);
	void addToXCoordinates(float X);
	void addToYCoordinates(float Y);
};


#endif