#pragma once
#include "pch.h"
#include <glut.h>

class WoodPrism : public GameObject {
public:
	GLTexture tex;
	WoodPrism() {
		transform.localScale = Vector3f(0.2, 0.2, 0.2);
	}

	WoodPrism(float _width, float _height, float _thickness) {
		transform.localScale = Vector3f(_width, _height, _thickness);

		char buffer[80];						
		strcpy(buffer, "Textures/blu-sky-3.bmp");
		tex.Load(buffer);				// Loads a bitmap
		//loadBMP(&tex, buffer , true);

	}

	void Display() override
	{
		
		glPushMatrix();
		//tex.Use();
		//glutSolidCube(1);
		glPopMatrix();
		
		glPushMatrix();

		GLUquadricObj * qobj;
		qobj = gluNewQuadric();
		tex.Use();
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 1, 20, 20);
		gluDeleteQuadric(qobj);


		glPopMatrix();

		/*
		glPushMatrix();
		glDisable(GL_LIGHTING);	// Disable lighting 

		glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit
		glPushMatrix();
		//tex.Use();
		glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);	// Set quad normal direction.
		glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
		glVertex3f(-20, 0, -20);
		glTexCoord2f(5, 0);
		glVertex3f(20, 0, -20);
		glTexCoord2f(5, 5);
		glVertex3f(20, 0, 20);
		glTexCoord2f(0, 5);
		glVertex3f(-20, 0, 20);
		glEnd();
		glPopMatrix();
		
		glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

		glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
		glPopMatrix();
		*/
	}
};

class WoodChair : public GameObject {

public:
	WoodPrism chairLeg[4];
	WoodPrism chairPlate;
	WoodPrism chairBackStick[4];

	WoodChair()
	{
		transform.position = Vector3f(0, 0, 0);
	}

	void Start() override
	{

		float width, height, thickness, height_offset;
		width = 0.4; height = 1;
		thickness = 0.07;
		height_offset = 0.18;
		chairPlate = WoodPrism(width, thickness, width);
		chairPlate.transform.position = Vector3f(0, height_offset, 0);
		addChild(&chairPlate, true);

		
		width = width / 2 - 0.05;
		height = 0.42;
		thickness = 0.03;
		
		chairLeg[0] = WoodPrism(thickness, height, thickness);
		chairLeg[0].transform.position = Vector3f(width, 0, width);
		addChild(&chairLeg[0], true);
		chairLeg[1] = WoodPrism(thickness, height, thickness);
		chairLeg[1].transform.position = Vector3f(-width, 0, width);
		addChild(&chairLeg[1], true);
		chairLeg[2] = WoodPrism(thickness, height, thickness);
		chairLeg[2].transform.position = Vector3f(-width, 0, -width);
		addChild(&chairLeg[2], true);
		chairLeg[3] = WoodPrism(thickness, height, thickness);
		chairLeg[3].transform.position = Vector3f(width, 0, -width);
		addChild(&chairLeg[3], true);

		thickness = 0.04;
		height = 0.4;
		height_offset = 0.35;
		chairBackStick[0] = WoodPrism(thickness, height, thickness);
		chairBackStick[0].transform.position = Vector3f(-width, height_offset, width);
		addChild(&chairBackStick[0], true);
		chairBackStick[1] = WoodPrism(thickness, height, thickness);
		chairBackStick[1].transform.position = Vector3f(-width, height_offset, -width);
		addChild(&chairBackStick[1], true);
		
		thickness = 0.015;
		height = 0.05;
		height_offset = 0.35;
		chairBackStick[2] = WoodPrism(thickness, height, 0.4);
		chairBackStick[2].transform.position = Vector3f(-width, height_offset, 0);
		addChild(&chairBackStick[2], true);
		chairBackStick[3] = WoodPrism(thickness, height, 0.4);
		chairBackStick[3].transform.position = Vector3f(-width, height_offset + height + 0.01, 0);
		addChild(&chairBackStick[3], true);
	}
};
