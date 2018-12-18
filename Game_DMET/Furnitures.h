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
		strcpy(buffer, "Textures/wood.bmp");
		tex.Load(buffer);				// Loads a bitmap
		//loadBMP(&tex, buffer , true);

	}

	void Display() override
	{
		
		glPushMatrix();

		GLUquadricObj * qobj;
		qobj = gluNewQuadric();
		tex.Use();
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 1, 5, 5);
		gluDeleteQuadric(qobj);


		glPopMatrix();
	}

};

class WoodChair : public GameObject {

public:
	WoodPrism chairLeg[4];
	WoodPrism chairPlate;
	WoodPrism chairBackStick[4];

	WoodChair()
	{
		transform.position = Vector3f(0, 0.5, -0.5);
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
		height = 0.40;
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

	void Update() override{
		CalculateCollider();
	}
};

class WoodTable : public GameObject {

public:
	WoodPrism tableLeg[4];
	WoodPrism tablePlate;

	WoodTable()
	{
		transform.position = Vector3f(1, 0.5, -0.5);
	}

	void Start() override
	{

		float width, height, thickness, height_offset;
		width = 0.5; height = 0.5;
		thickness = 0.08;
		height_offset = 0.22;
		tablePlate = WoodPrism(width, thickness, width+0.1);
		tablePlate.transform.position = Vector3f(0, height_offset, 0);
		addChild(&tablePlate, true);


		width = width / 2 - 0.05;
		height = 0.3;
		thickness = 0.03;

		tableLeg[0] = WoodPrism(thickness, height, thickness);
		tableLeg[0].transform.position = Vector3f(width, 0, width);
		addChild(&tableLeg[0], true);
		tableLeg[1] = WoodPrism(thickness, height, thickness);
		tableLeg[1].transform.position = Vector3f(-width, 0, width);
		addChild(&tableLeg[1], true);
		tableLeg[2] = WoodPrism(thickness, height, thickness);
		tableLeg[2].transform.position = Vector3f(-width, 0, -width);
		addChild(&tableLeg[2], true);
		tableLeg[3] = WoodPrism(thickness, height, thickness);
		tableLeg[3].transform.position = Vector3f(width, 0, -width);
		addChild(&tableLeg[3], true);
	}

	void Update() override {
		CalculateCollider();
	}
};

class Wall : public GameObject {

public:
	Wall()
	{

	}
	Wall(Vector3f _position, Vector3f _rotation, Vector3f _scale)
	{
		transform.position = _position;
		transform.rotation = _rotation;
		transform.localScale = _scale;
	}

	void Update() override
	{
		CalculateCollider();
	}

	void Display() override
	{
		//glutSolidCube(1);
	}


};


class House : public GameObject {
public:
	Model_3DS model3ds;
	WoodTable table;
	WoodChair chair;
	Wall wall1;
	Wall wall2;
	Wall wall3;

	House() {
		char buffer[80];
		strcpy(buffer, "Models/house/house.3ds");
		model3ds.Load(buffer);
		transform.position = Vector3f(2, -1, 0);
	}

	void Start() override {
		wall1 = Wall(Vector3f(2, 0, 1.5), Vector3f(0, 0, 0), Vector3f(6, 5, 2));
		addChild(&wall1, false);
		wall2 = Wall(Vector3f(3, 0, -2), Vector3f(0, 0, 0), Vector3f(4, 5, 2));
		addChild(&wall2, false);
		wall3 = Wall(Vector3f(-2, 0, 0), Vector3f(0, 0, 0), Vector3f(2, 5, 4));
		addChild(&wall3, false);
		table = WoodTable();
		addChild(&table, true);
		chair = WoodChair();
		addChild(&chair, true);
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
