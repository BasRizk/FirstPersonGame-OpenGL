#pragma once
#include "pch.h"
class AmmoCrate : public GameObject {

	Player * player;
public:
	float radius;
	AmmoCrate()
	{

	}
	AmmoCrate(Player * _player)
	{
		player = _player;
		radius = 4;
	}

	void Start() override
	{
		transform.position = Vector3f(0, 0, 0);
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
		glutSolidCube(1);
	}
};