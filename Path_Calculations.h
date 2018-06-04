#pragma once

#ifndef PATH_CALCULATIONS
#define PATH_CALCULATIONS

#include<vector>

void createTriangle();

void createSquare();

void createCircle(float *array, float x, float y, float radius);

std::vector<float> createRotation();
#endif

class TimeGhost
{
private:

	float coordinatesX;
	float coordinatesY;
	float timeToLive;

public:
	TimeGhost(float coordinatesX, float coordinatesY, float timeToLive);

	float getCoordinatesX() { return coordinatesX; }
	float getCoordinatesY() { return coordinatesY; }
	float getTimeToLive() { return timeToLive; }

	void setCoordinatesX(float coordinatesX) { this->coordinatesX = coordinatesX; }
	void setCoordinatesY(float coordinatesY) { this->coordinatesY = coordinatesY; }
	void setTimeToLive(float timeToLive) { this->timeToLive = timeToLive; }

};