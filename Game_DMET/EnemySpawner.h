#pragma once
#include "pch.h"
class EnemySpawner : public GameObject {

	float spawnRadius;
	float spawnTime;
	float enemySpeed;
	float timer;

public:
	GameObject * player;
	EnemySpawner()
	{

	}
	EnemySpawner(GameObject * _player)
	{
		player = _player;
	}
	void Start() override
	{
		RestartGame();
	}

	void RestartGame() override
	{
		freeChildren.clear();
		transform.position = Vector3f(0, 0, 0);
		spawnTime = 3000;
		timer = 2000;
		enemySpeed = 0.05;
		spawnRadius = 10;
	}

	void Update() override
	{
		if (timer < 0)
		{
			float angle = rand() % 360;
			Vector3f position = Vector3f(spawnRadius * cos(DEG2RAD(angle)), 0, spawnRadius * sin(DEG2RAD(angle)));
			
			Enemy * enemy = new Enemy(enemySpeed, position, player , this);

			addChild(enemy, false);

			timer = spawnTime;
		}
		else
		{
			timer -= deltaTime;
		}

		if (((Player *)player)->HP < 0)
		{
			player->RestartGame();
			RestartGame();
		}
	}
};
