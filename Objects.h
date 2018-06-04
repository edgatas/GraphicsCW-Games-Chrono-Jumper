#pragma once

#ifndef OBJECTS
#define OBJECTS

//#include <windows.h>
#include "glew.h"
#include "Path_Calculations.h"
#include "Settings.h"


#include <vector>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Object List
// Player
// Ground
// FPS

class Player
{
	private:

		float coordinatesX = 0;
		float coordinatesY = 0;

		float vSpeed;	// vertical speed
		float hSpeed;	// horizontal speed
		float jumpPower;
		float maxSpeed; // per tick

		int vState;		//	0 - Ready	1 - Up, 2 - Down, 3 - Ground
		int hState;		//	0 - Standing,	1 - Negative(Left),	2 - Positive(Right)

		int height;
		int wide;

		bool otherHCollitions;

		float timer;	
		bool dead;

		bool inAir;			
		int standingSide;	// 0 = facing left, 1 = facing right
		void checkStandingSide();	// 0 = facing left, 1 = facing right
		float animationSpeedMultiplayer;

		std::vector<TimeGhost> playerHistory;

	public:

		Player();
		~Player();

		void draw(float deltaT);

		// SETTERS
		void setCoordinates(float coordX, float coordY);
		void setCoordinatesX(float coordX);
		void setCoordinatesY(float coordY);
		void setVspeed(float speed);
		void setHspeed(float speed);
		void setVState(int state);
		void setHState(int state);
		void setMaxSpeed(float speed);
		void setOtherHCollitions(bool state);
		void setDead(bool state);

		// GETTERS
		float getCoordinatesX();
		float getCoordinatesY();
		float getMaxSpeed();
		float getVSpeed();
		float getHSpeed();
		float getJumpPower();
		int getVState();
		int getHState();
		bool getOtherHCollitions();
		int getWide();
		int getHeight();
		bool getDead();

		void addPosition();
		void recalculateHistory(float deltaT);
		std::vector<TimeGhost> getPlayerHistory() {return playerHistory;}

		// CHANGERS
		void changeTranslationX(float x);
		void changeTranslationY(float y);
};

class Ground
{
	private:
		float locationX;
		float locationY;
		int height;
		int wide;
		GLuint texture;

	public:
		Ground();
		Ground(float x, float y);
		Ground(int wideX, int heightY);
		Ground(float x, float y, int wideX, int heightY);


		float getCoordinatesX() { return locationX; }
		float getCoordinatesY() { return locationY; }
		int getHeight() { return height; }
		int getWide() { return wide; }
		GLuint getTexture() { return texture; }

		void setHeight(int height) { this->height = height; }
		void setWide(int wide) { this->wide = wide; }
		void setTexture(GLuint texture) { this->texture = texture; }

		void setCoordinates(float x, float y);
		void draw();

		friend ostream& operator<<(ostream &out, Ground &object);
};

class MovingPlatform
{
public:
	MovingPlatform(float coordinateX, float coordinateY, int wide, int height, float pointAX, float pointAY, float pointBX, float pointBY, int speed);

	// Getters
	float getCoordinatesX()	{ return coordinatesX; }
	float getCoordinatesY()	{ return coordinatesY; }
	int getWide()			{ return wide; }
	int getHeight()			{ return height; }
	float getPointAX()		{ return pointAX; }
	float getPointAY()		{ return pointAY; }
	float getPointBX()		{ return pointBX; }
	float getPointBY()		{ return pointBY; }
	int	getSpeed()			{ return speed; }
	float getHSpeed()		{ return hSpeed; }
	float getVSpeed()		{ return vSpeed; }
	float getAccel()		{ return accel; }
	int getAccelState()		{ return accelState; }
	float getSleepTime()	{ return sleepTime; }
	GLuint getTexture()		{ return texture; }
	float getOldCoordinatesX() { return oldCoordinatesX; }
	float getOldCoordinatesY() { return oldCoordinatesY; }

	// Setters
	void setCoordinatesX(float coordinatesX)	{ this->coordinatesX = coordinatesX; }
	void setCoordinatesY(float coordinatesY)	{ this->coordinatesY = coordinatesY; }
	void setWide(int wide)					{ this->wide = wide; }
	void setHeight(int height)				{ this->height = height; }
	void setPointAX(float pointAX)			{ this->pointAX = pointAX; }
	void setPointAY(float pointAY)			{ this->pointAY = pointAY; }
	void setPointBX(float pointBX)			{ this->pointBX = pointBX; }
	void setPointBY(float pointBY)			{ this->pointBY = pointBY; }
	void setSpeed(int speed)				{ this->speed = speed; }
	void setTexture(GLuint texture)			{ this->texture = texture; }
	void setHSpeed(float hSpeed)			{ this->hSpeed = hSpeed; }
	void setVSpeed(float vSpeed)			{ this->vSpeed = vSpeed; }
	void setAccel(float acceleration)		{ this->accel = acceleration; }
	void setAccelState (int accelState)		{ this->accelState = accelState; }
	void setSleepTime(float sleepTime)		{ this->sleepTime = sleepTime; }
	void setOldCoordinatesX(float coordinatesX) { this->oldCoordinatesX = coordinatesX; }
	void setOldCoordinatesY(float coordinatesY) { this->oldCoordinatesY = coordinatesY; }

	void MovingPlatform::draw();

private:

	float coordinatesX;
	float coordinatesY;
	int wide;
	int height;

	float oldCoordinatesX;
	float oldCoordinatesY;

	float pointAX;
	float pointAY;
	float pointBX;
	float pointBY;

	int speed;
	float hSpeed;
	float vSpeed;
	float accel;
	float sleepTime;

	int accelState; // 0 = FullStop, 1 = accelerating, 2 = decelerating

	GLuint texture;

};

class Marker
{
private:
	float coordinatesX;
	float coordinatesY;
public:
	Marker(float coordinatesX, float coordinatesY);
	void draw();
};

class Crystal
{
private:
	float coordinatesX;
	float coordinatesY;
	bool state;		// false = available, true = picked
public:
	Crystal(float coordinatesX, float coordinatesY);
	void draw(int sequence, float cameraX, float cameraY, VideoSettings settings);
	void draw();

	// Setters
	void setCoordinatesX(float coordinatesX) { this->coordinatesX = coordinatesX; }
	void setCoordinatesY(float coordinatesY) { this->coordinatesY = coordinatesY; }
	void setState(bool state) { this->state = state; }

	// Getters
	float getCoordinatesX() { return coordinatesX; }
	float getCoordinatesY() { return coordinatesY; }
	bool getState() { return state; }
};

#endif