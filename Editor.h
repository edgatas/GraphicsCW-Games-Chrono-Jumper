#pragma once

#ifndef EDITOR
#define EDITOR

#include "Camera.h"
#include "Settings.h"

class Interface
{
private:
	float topLineLenght;
	float topLineWidth = 5;
	float topLineMarginFromTop;
	float BottomBoxTopLine[8];
	float BottomBoxBottomLine[8];
	float BottomBoxLeftLine[8];
	float BottomBoxRightLine[8];
	float BottomBoxBackground[8];

	float horizontalLines[2];


	float resX;
	float resY;

public:

	Interface(Camera camera, VideoSettings settings);
	void update(Camera camera, VideoSettings settings);

	void draw();
};
	
// Find closes place for ground objects
float findClosesXCoordinates(float X);
float findClosesYCoordinates(float Y);


#endif