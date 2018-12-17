#pragma once
#include "pch.h"

class BlenderModel : public GameObject {
public:
	Model_3DS model3ds;
	BlenderModel() {

	}

	BlenderModel(char* _filepath) {
		char buffer[80];
		strcpy(buffer, _filepath);
		model3ds.Load(buffer);
	}

	void Display() override
	{
		model3ds.Draw();
	}
};