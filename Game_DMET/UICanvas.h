#pragma once
#include "pch.h"
class UICanvas : public GameObject {

public:
	int screenX = 1400;
	int screenY = 900;

	int currentAmmo = 30;
	int maxAmmo = 30;
	int score = 0;
	int hp = 100;
	Player * player;

	UICanvas()
	{

	}

	UICanvas(Player * _player)
	{
		player = _player;
	}
	void Start() override
	{
		
	}

	void Update() override
	{
		hp = player->HP;
		currentAmmo = player->ammo;
		score = player->score;
	}
	void printText(int x, int y, const char *string, float c1, float c2, float c3)
	{
		//Assume we are in MODEL_VIEW already
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluOrtho2D(0, viewport[2], viewport[3], 0);

		glDepthFunc(GL_ALWAYS);
		glColor3f(c1, c2, c3);
		glRasterPos2f(x, y);
		for (int i = 0; string[i] != '\0'; ++i)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		glDepthFunc(GL_LESS);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	void drawLine(float x1, float y1, float x2, float y2, float c1, float c2, float c3)
	{
		glPushMatrix();
		glColor3f(c1, c2, c3);
		glBegin(GL_LINES);
		glVertex3d(x1, y1, 0);
		glVertex3d(x2, y2, 0);
		glEnd();
		glPopMatrix();
	}

	void printLine(int x, int y, float length, bool isVertical, float c1, float c2, float c3)
	{
		//Assume we are in MODEL_VIEW already
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluOrtho2D(0, viewport[2], viewport[3], 0);

		glDepthFunc(GL_ALWAYS);
		glColor3f(c1, c2, c3);
		glRasterPos2f(x, y);

		if (isVertical)
			drawLine(x, y - (length / 2), x, y + (length / 2), c1, c2, c3);
		else
			drawLine(x - (length / 2), y, x + (length / 2), y, c1, c2, c3);

		glDepthFunc(GL_LESS);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	void printRect(int x, int y, float width, float height, bool startVertexCenter, float c1, float c2, float c3, float cb1, float cb2, float cb3)
	{
		//Assume we are in MODEL_VIEW already
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluOrtho2D(0, viewport[2], viewport[3], 0);

		glDepthFunc(GL_ALWAYS);
		glColor3f(c1, c2, c3);
		glRasterPos2f(x, y);

		glPushMatrix();
		glBegin(GL_POLYGON);
		if (startVertexCenter)
		{
			glVertex3d(x - (width / 2), y - (height / 2), 0);
			glVertex3d(x + (width / 2), y - (height / 2), 0);
			glVertex3d(x + (width / 2), y + (height / 2), 0);
			glVertex3d(x - (width / 2), y + (height / 2), 0);
		}
		else
		{
			glVertex3d(x, y, 0);
			glVertex3d(x + width, y, 0);
			glVertex3d(x + width, y - height, 0);
			glVertex3d(x, y - height, 0);
		}
		glEnd();
		glPopMatrix();

		if (startVertexCenter)
		{
			drawLine(x - (width / 2), y - (height / 2), x + (width / 2), y - (height / 2), cb1, cb2, cb3);
			drawLine(x + (width / 2), y - (height / 2), x + (width / 2), y + (height / 2), cb1, cb2, cb3);
			drawLine(x + (width / 2), y + (height / 2), x - (width / 2), y + (height / 2), cb1, cb2, cb3);
			drawLine(x - (width / 2), y + (height / 2), x - (width / 2), y - (height / 2), cb1, cb2, cb3);
		}
		else
		{
			drawLine(x, y, x + width, y, cb1, cb2, cb3);
			drawLine(x + width, y, x + width, y - height, cb1, cb2, cb3);
			drawLine(x + width, y - height, x, y - height, cb1, cb2, cb3);
			drawLine(x, y - height, x, y, cb1, cb2, cb3);
		}

		glDepthFunc(GL_LESS);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	void printSolidCircle(int x, int y, float r, float c1, float c2, float c3, float cb1, float cb2, float cb3)
	{
		//Assume we are in MODEL_VIEW already
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluOrtho2D(0, viewport[2], viewport[3], 0);

		glDepthFunc(GL_ALWAYS);
		glColor3f(c1, c2, c3);
		glRasterPos2f(x, y);

		glColor3f(c1, c2, c3);

		glBegin(GL_POLYGON);
		for (int i = 0; i <= 360; i++)
		{
			float degInRad = i * 3.14159 / 180;
			glVertex3f(x + (cos(degInRad)*r), y + (sin(degInRad)*r), 0);
		}
		glEnd();

		glColor3f(cb1, cb2, cb3);

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 360; i++)
		{
			float degInRad = i * 3.14159 / 180;
			glVertex3f(x + (cos(degInRad)*r), y + (sin(degInRad)*r), 0);
		}
		glEnd();

		glDepthFunc(GL_LESS);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	void printHallowCircle(int x, int y, float r, float c1, float c2, float c3)
	{
		//Assume we are in MODEL_VIEW already
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluOrtho2D(0, viewport[2], viewport[3], 0);

		glDepthFunc(GL_ALWAYS);
		glColor3f(c1, c2, c3);
		glRasterPos2f(x, y);

		glColor3f(c1, c2, c3);

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= 360; i++)
		{
			float degInRad = i * 3.14159 / 180;
			glVertex3f(x + (cos(degInRad)*r), y + (sin(degInRad)*r), 0);
		}
		glEnd();

		glDepthFunc(GL_LESS);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}


	void Display() override
	{
		char score_toString[32];
		sprintf_s(score_toString, "%d", score);
		char score_print[100] = "Score: ";
		strcat_s(score_print, score_toString);

		char hp_toString[32];
		sprintf_s(hp_toString, "%d", hp);
		char hp_print[100] = "HP: ";
		strcat_s(hp_print, hp_toString);

		char ammo_toString[32];
		sprintf_s(ammo_toString, "%d", currentAmmo);
		char ammo_print[100] = "Ammo: ";
		strcat_s(ammo_print, ammo_toString);
		sprintf_s(ammo_toString, "%d", maxAmmo);
		strcat_s(ammo_print, "/");
		strcat_s(ammo_print, ammo_toString);

		printRect(screenX * 0.01, screenY * 0.07, screenX * 0.07, screenY * 0.05, false, 0.2, 0.2, 0.2, 0, 0, 0);
		printText(screenX * 0.02, screenY * 0.05, score_print, 1, 1, 1);
		printRect(screenX * 0.89, screenY * 0.07, screenX * 0.07, screenY * 0.05, false, 0.2, 0.2, 0.2, 0, 0, 0);
		printText(screenX * 0.90, screenY * 0.05, hp_print, 0.7, 0.1, 0.1);
		printRect(screenX * 0.89, screenY * 0.97, screenX * 0.10, screenY * 0.05, false, 0.2, 0.2, 0.2, 0, 0, 0);
		printText(screenX * 0.90, screenY * 0.95, ammo_print, 1, 1, 1);
		printHallowCircle(screenX * 0.50, screenY * 0.50, screenX * 0.01, 0, 0, 0);
		printLine(screenX * 0.50, screenY * 0.50, screenX * 0.01, true, 0, 0, 0);
		printLine(screenX * 0.50, screenY * 0.50, screenX * 0.01, false, 0, 0, 0);

		glColor3f(1, 1, 1);
	}
};