#pragma once
#include "pch.h"
class Enemy : public GameObject {
	float speed;
	Vector3f position;
public:
	Enemy()
	{

	}
	Enemy(float _speed, Vector3f _position)
	{
		speed = _speed;
		position = _position;
	}

	void Start() override
	{
		transform.position = position;
	}

	void Update() override
	{
		CalculateCollider();
	}

	void Display() override
	{
		glColor3d(1, 0, 0);
		glutSolidCube(2);
	}
};