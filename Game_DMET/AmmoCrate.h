#pragma once
#include "pch.h"
class AmmoCrate : public GameObject {

	Player * player;
public:
	float radius;
	GLTexture tex;
	AmmoCrate()
	{

	}
	AmmoCrate(Player * _player)
	{
		player = _player;
		radius = 4;

		char buffer[80];
		strcpy(buffer, "Textures/wood.bmp");
		tex.Load(buffer);				
	}

	void Start() override
	{
		transform.position = Vector3f(0, -0.1, 0);
		transform.localScale = Vector3f(1, 1, 1);
		transform.rotation = Vector3f(0, 90, 0);
	}

	void Update() override
	{
		CalculateCollider();
		if (transform.distanceSqured(player->transform.position) < radius)
		{
			player->ammo = 30;
		}
	}

	void Display() override
	{
		glPushMatrix();
		tex.Use();
		//glEnable(GL_DEPTH_TEST);
		//glBegin(GL_POLYGON);
		//glTranslated(2, 0, 2);
		//glRotated(90, 0, 1, 0);
		//glVertex3f(-0.5, -0.5, -0.5);       // P1
		//glTexCoord2f(0, 0);
		//glVertex3f(-0.5, 0.5, -0.5);       // P2
		//glTexCoord2f(5, 0);
		//glVertex3f(0.5, 0.5, -0.5);       // P3
		//glTexCoord2f(5, 5);
		//glVertex3f(0.5, -0.5, -0.5);       // P4
		//glTexCoord2f(0, 5);
		//glEnd();

		//glutSolidCube(1);
		//glPopMatrix();

		glBegin(GL_POLYGON);
		glVertex3f(0.5, -0.5, -0.5);      // P1 is red
		glVertex3f(0.5, 0.5, -0.5);      // P2 is green
		glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
		glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple
		glEnd();


		// White side - BACK
		glBegin(GL_POLYGON);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glEnd();

		// Purple side - RIGHT
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.5, 1.0);
		glVertex3f(0.5, -0.5, -0.5);
		glTexCoord2f(0, 0);
		glVertex3f(0.5, 0.5, -0.5);
		glTexCoord2f(5, 0);
		glVertex3f(0.5, 0.5, 0.5);
		glTexCoord2f(5, 5);
		glVertex3f(0.5, -0.5, 0.5);
		glTexCoord2f(5, 0);
		glEnd();


		// Green side - LEFT
		glBegin(GL_POLYGON);
		//glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();


		// Blue side - TOP
		glBegin(GL_POLYGON);
		//glColor3f(1.0, 0.0, 1.0);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glEnd();
		

		// Red side - BOTTOM
		glBegin(GL_POLYGON);
		//glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();

		glColor3f(1, 1, 1);
		glPopMatrix();

	}
};