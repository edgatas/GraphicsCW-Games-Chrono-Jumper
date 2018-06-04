#pragma once

#ifndef SETTINGS
#define SETTINGS

class VideoSettings
{
private:
	int screenResolutionX;
	int screenResolutionY;

public:

	VideoSettings();

	void setResolution(int x, int y);
	int getResolutionX();
	int getResolutionY();
};


#endif