#pragma once
#include "pch.h"

class Tree : public GameObject {
public:
	Model_3DS model3ds;
	Tree() {
		char buffer[80];
		strcpy(buffer, "Models/tree/Tree1.3ds");
		model3ds.Load(buffer);
	}

	void Display() override
	{
		glPushMatrix();
		glTranslatef(10, -1, 0);
		glScalef(0.7, 0.7, 0.7);
		model3ds.Draw();
		glPopMatrix();
	}
};