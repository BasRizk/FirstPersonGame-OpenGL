#pragma once
#include "pch.h"

void DrawRectangle(float x, float y, float height, float width, bool midPoint, Color color)
{
	glBegin(GL_POLYGON);
	if (midPoint)
	{
		glColor4f(color.r, color.g, color.b, color.a);
		glVertex3f(x - (width * 0.5f), y + (height * 0.5f), 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x + (width * 0.5f), y + (height * 0.5f), 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x + (width * 0.5f), y - (height * 0.5f), 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x - (width * 0.5f), y - (height * 0.5f), 0.0f);
	}
	else
	{
		glColor4f(color.r, color.g, color.b, color.a);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x, y, 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x + width, y, 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x + width, y + height, 0.0f);
		// glColor3f(color.r, color.g, color.b);
		glVertex3f(x, y + height, 0.0f);
	}
	glEnd();
}
class UI : public GameObject {
	void Start() override
	{
		transform.position = Vector3f(0, 0, 1);
	}

	void Update() override
	{

	}

	void Display() override
	{
		//glutSolidCube(0.5);
		glBegin(GL_POLYGON);
		glVertex2d(0.5, 0.5);
		glVertex2d(1.5, 0);
		glVertex2d(1.5, 1.5);
		glVertex2d(0, 1);
		//glVertex2d(0, 1);
		glEnd();
	}
};