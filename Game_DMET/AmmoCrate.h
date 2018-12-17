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
		transform.localScale = Vector3f(3, 1, 1);
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