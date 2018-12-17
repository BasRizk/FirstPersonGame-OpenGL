#pragma once
#include "pch.h"

class House : public GameObject {
public:
	Model_3DS model3ds;
	House() {
		char buffer[80];
		strcpy(buffer, "Models/house/house.3ds");
		model3ds.Load(buffer);
		transform.position = Vector3f(2, -1, 0);
	}

	void Display() override
	{
		glPushMatrix();
		glRotatef(90.f, 1, 0, 0);
		glRotated(180.f, 0, 0, 1);
		model3ds.Draw();
		glPopMatrix();
	}
};