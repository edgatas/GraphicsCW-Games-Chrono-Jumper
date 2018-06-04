#include "Camera.h"

Camera::Camera()
{
	xCoordinates = 0;
	yCoordinates = 0;
}

void Camera::updateCamera(Player player)
{
	xCoordinates = player.getCoordinatesX();
	yCoordinates = player.getCoordinatesY();
}

float Camera::getXCoordinates()
{
	return xCoordinates;
}

float Camera::getYCoordinates()
{
	return yCoordinates;
}

void Camera::setXCoordinates(float x)
{
	xCoordinates = x;
}

void Camera::setYCoordinates(float y)
{
	yCoordinates = y;
}

void Camera::addToXCoordinates(float X)
{
	xCoordinates += X;
}
void Camera::addToYCoordinates(float Y)
{
	yCoordinates += Y;
}
