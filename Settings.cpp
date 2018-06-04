#include "Settings.h"

VideoSettings::VideoSettings()
{
	screenResolutionX = 0;
	screenResolutionY = 0;
}

void VideoSettings::setResolution(int x, int y)
{
	screenResolutionX = x;
	screenResolutionY = y;
}

int VideoSettings::getResolutionX()
{
	return screenResolutionX;
}

int VideoSettings::getResolutionY()
{
	return screenResolutionY;
}