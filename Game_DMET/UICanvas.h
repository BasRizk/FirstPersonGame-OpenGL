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
	}
	void print(int x, int y, const char *string, float c1, float c2, float c3)
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

		print(screenX * 0.02, screenY * 0.05, score_print, 1, 1, 1);
		print(screenX * 0.90, screenY * 0.05, hp_print, 1, 1, 1);
		print(screenX * 0.90, screenY * 0.95, ammo_print, 1, 1, 1);
	}
};