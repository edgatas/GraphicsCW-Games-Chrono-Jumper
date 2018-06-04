#include "Editor.h"

#include <windows.h>		// Header file for Windows
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>			// Header file for the GLu32 Library

Interface::Interface(Camera camera, VideoSettings settings)
{
	float resolutionX = settings.getResolutionX();
	float resolutionY = settings.getResolutionY();

	resX = resolutionX;
	resY = resolutionY;

}

void Interface::update(Camera camera, VideoSettings settings)
{
	float cameraX = camera.getXCoordinates();
	float cameraY = camera.getYCoordinates();

	float resolutionX = settings.getResolutionX();
	float resolutionY = settings.getResolutionY();


	// BOTTOM BOX TOP LINE
	BottomBoxTopLine[0] = cameraX - (resolutionX / 2);
	BottomBoxTopLine[1] = cameraY - (resolutionY / 3);

	BottomBoxTopLine[2] = cameraX + (resolutionX / 2);
	BottomBoxTopLine[3] = cameraY - (resolutionY / 3);

	BottomBoxTopLine[4] = cameraX + (resolutionX / 2);
	BottomBoxTopLine[5] = cameraY - (resolutionY / 3) - (resY / 50);

	BottomBoxTopLine[6] = cameraX - (resolutionX / 2);
	BottomBoxTopLine[7] = cameraY - (resolutionY / 3) - (resY / 50);

	// BOTTOM BOX BOTTOM LINE
	BottomBoxBottomLine[0] = cameraX - (resolutionX / 2);
	BottomBoxBottomLine[1] = cameraY - (resolutionY / 2);

	BottomBoxBottomLine[2] = cameraX + (resolutionX / 2);
	BottomBoxBottomLine[3] = cameraY - (resolutionY / 2);

	BottomBoxBottomLine[4] = cameraX + (resolutionX / 2);
	BottomBoxBottomLine[5] = cameraY - (resolutionY / 2) + (resY / 50);

	BottomBoxBottomLine[6] = cameraX - (resolutionX / 2);
	BottomBoxBottomLine[7] = cameraY - (resolutionY / 2) + (resY / 50);

	// BOTTOM BOX LEFT LINE
	BottomBoxLeftLine[0] = cameraX - (resolutionX / 2);
	BottomBoxLeftLine[1] = cameraY - (resolutionY / 2);

	BottomBoxLeftLine[2] = cameraX - (resolutionX / 2) + (resX / 100);
	BottomBoxLeftLine[3] = cameraY - (resolutionY / 2);

	BottomBoxLeftLine[4] = cameraX - (resolutionX / 2) + (resX / 100);
	BottomBoxLeftLine[5] = cameraY - (resolutionY / 3);

	BottomBoxLeftLine[6] = cameraX - (resolutionX / 2);
	BottomBoxLeftLine[7] = cameraY - (resolutionY / 3);

	// BOTTOM BOX RIGHT LINE
	BottomBoxRightLine[0] = cameraX + (resolutionX / 2);
	BottomBoxRightLine[1] = cameraY - (resolutionY / 2);

	BottomBoxRightLine[2] = cameraX + (resolutionX / 2) - (resX / 100);
	BottomBoxRightLine[3] = cameraY - (resolutionY / 2);

	BottomBoxRightLine[4] = cameraX + (resolutionX / 2) - (resX / 100);
	BottomBoxRightLine[5] = cameraY - (resolutionY / 3);

	BottomBoxRightLine[6] = cameraX + (resolutionX / 2);
	BottomBoxRightLine[7] = cameraY - (resolutionY / 3);

	// BOTTOM BOX RIGHT LINE
	BottomBoxBackground[0] = cameraX - (resolutionX / 2) + (resX / 100);
	BottomBoxBackground[1] = cameraY - (resolutionY / 2) + (resY / 50);

	BottomBoxBackground[2] = cameraX - (resolutionX / 2) + (resX / 100);
	BottomBoxBackground[3] = cameraY - (resolutionY / 3) - (resY / 50);;

	BottomBoxBackground[4] = cameraX + (resolutionX / 2) - (resX / 100);
	BottomBoxBackground[5] = cameraY - (resolutionY / 3) - (resY / 50);;

	BottomBoxBackground[6] = cameraX + (resolutionX / 2) - (resX / 100);
	BottomBoxBackground[7] = cameraY - (resolutionY / 2) + (resY / 50);

	// TESTING FOR APEARING AND DISAPEARING
	horizontalLines[0] = cameraX;
	horizontalLines[1] = cameraY;

}

void Interface::draw()
{
	glPushMatrix();

		glBegin(GL_POLYGON);
		glColor3ub(255, 255, 0); // YELLOW
		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(BottomBoxTopLine[i], BottomBoxTopLine[i+1]);
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();

		glBegin(GL_POLYGON);
		glColor3ub(255, 255, 0); // YELLOW
		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(BottomBoxBottomLine[i], BottomBoxBottomLine[i + 1]);
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();

		glBegin(GL_POLYGON);
		glColor3ub(0, 0, 255); //CYAN
		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(BottomBoxLeftLine[i], BottomBoxLeftLine[i + 1]);
		}
		glEnd();
	glPopMatrix();

	glPushMatrix();

	glBegin(GL_POLYGON);
		glColor3ub(0, 0, 255); //CYAN

		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(BottomBoxRightLine[i], BottomBoxRightLine[i + 1]);
		}
		glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
		glColor3ub(0, 255, 0); // GREEN
		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(BottomBoxBackground[i], BottomBoxBackground[i + 1]);
		}
		glEnd();
	glPopMatrix();



	// TESTING APEARING AND DISAPEARING
	glBegin(GL_POLYGON);
		glColor3ub(0, 255, 0); // GREEN
			glVertex2f(horizontalLines[0] + 400, -100);
			glVertex2f(horizontalLines[0] + 400, 100);
			glVertex2f(horizontalLines[0] + 400 + 1, 100);
			glVertex2f(horizontalLines[0] + 400 + 1, -100);
		glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
		glColor3ub(0, 255, 0); // GREEN
			glVertex2f(horizontalLines[0] - 400, -100);
			glVertex2f(horizontalLines[0] - 400, 100);
			glVertex2f(horizontalLines[0] - 400 - 1, 100);
			glVertex2f(horizontalLines[0] - 400 - 1, -100);
		glEnd();
	glPopMatrix();
	// FINISHING APEARING AND DISAPEARING

}

// Simple Functions //

// Find closes X point that divides by 20
float findClosesXCoordinates(float X)
{
	int leftOver = (int)X % 40;

	if (leftOver > 20)
	{
		return (int)X + 40 - leftOver;
	}
	else
	{
		return (int)X - leftOver;
	}
};

// Find closes Y point that divides by 20
float findClosesYCoordinates(float Y)
{
	int leftOver = (int)Y % 40;

	if (leftOver > 20)
	{
		return (int)Y + 40 - leftOver;
	}
	else
	{
		return (int)Y - leftOver;
	}
};