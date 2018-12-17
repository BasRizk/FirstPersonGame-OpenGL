#pragma once
#include "pch.h"
class Enemy : public GameObject {
	float speed;
	Vector3f position;
	Transform * player;
	float movementTimer;
	float timer;
	float walkHopDirection;
public:
	Enemy()
	{

	}
	Enemy(float _speed, Vector3f _position, Transform * _player)
	{
		speed = _speed;
		position = _position;
		player = _player;
	}

	void Start() override
	{
		transform.position = position;
		walkHopDirection = 0.2f;
		movementTimer = 150;
		timer = movementTimer;
	}

	void Update() override
	{
		if (timer < 0)
		{
			walkHopDirection = -walkHopDirection;
			timer = movementTimer;
		}
		else
			timer -= deltaTime;
		transform.Translate((player->position - transform.position).unit() * speed);
		transform.Translate(Vector3f(0, 1, 0) * speed * walkHopDirection);
		CalculateCollider();
	}

	void Display() override
	{
		glColor3d(1, 0, 0);
		glutSolidCube(2);
	}
};