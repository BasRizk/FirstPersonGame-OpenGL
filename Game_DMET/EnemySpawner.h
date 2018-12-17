#pragma once
#include "pch.h"
class EnemySpawner : public GameObject {

	float spawnRadius;
	float spawnTime;
	float enemySpeed;
	float timer;
public:
	
	EnemySpawner()
	{

	}
	void Start() override
	{
		transform.position = Vector3f(0,0,0);
		spawnTime = 3000;
		enemySpeed = 0.1;
		spawnRadius = 8;
	}

	void Update() override
	{
		if (timer < 0)
		{
			float angle = rand() % 360;
			Vector3f position = Vector3f(spawnRadius * cos(DEG2RAD(angle)), 0, spawnRadius * sin(DEG2RAD(angle)));
			
			Enemy * enemy = new Enemy(enemySpeed, position);

			addChild(enemy, false);

			timer = spawnTime;
		}
		else
		{
			timer -= deltaTime;
		}
	}
};
