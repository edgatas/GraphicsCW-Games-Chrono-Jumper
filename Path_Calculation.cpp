#include "Path_Calculations.h"

#include <math.h>
#include <vector>

const float PI = 3.1415926535f;

void createTriangle()
{

}

void createSquare()
{

}

void createCircle(float *array, float x, float y, float radius)
{
	int p = 0;
	for (float i = 0; i<360; i += 5)
	{
		array[p] = x + radius * cosf(i*(PI / 180.0f));
		array[p + 1] = y + radius * sinf(i*(PI / 180.0f));
		p += 2;
	}
}



//***********************************************************************************************************
// TimeGhost Class
//***********************************************************************************************************

TimeGhost::TimeGhost(float coordinatesX, float coordinatesY, float timeToLive)
{
	this->coordinatesX = coordinatesX;
	this->coordinatesY = coordinatesY;
	this->timeToLive = timeToLive;
}