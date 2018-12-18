#pragma once
#include "pch.h"

class EnemyArm : public GameObject {
	
	GLTexture tex;
	void Start() override
	{
		char buffer[80];

		transform.position = Vector3f(0.6f, 0, 0);
		transform.localScale = Vector3f(0.2f, 0.5, 0.2f);

		strcpy(buffer, "textures/blu-sky-3.bmp");
		tex.Load(buffer);
	}

	void Update() override
	{
		transform.Rotate(Vector3f(1, 0, 0 ));
	}

	void Display() override
	{
		glPushMatrix();
		glTranslated(0, -0.5, 0);
		glColor3f(1.0, 0, 0.5);
		glutSolidCube(1);
		glColor3f(1, 1, 1);
		glPopMatrix();

	}

};
class Enemy : public GameObject {
	float speed;
	Vector3f position;
	GameObject * player;
	float movementTimer;
	float timer;
	float walkHopDirection;
	GameObject * spawner;
	EnemyArm arm;
	float damage;
	float attackTimer;
	float attackDefaultTime;
public:
	GLTexture tex;
	Enemy()
	{

	}
	Enemy(float _speed, Vector3f _position, GameObject * _player , GameObject * _spawner)
	{
		speed = _speed;
		position = _position;
		player = _player;
		spawner = _spawner;
	}

	void Start() override
	{
		char buffer[80];
		transform.position = position;
		transform.localScale = Vector3f(0.75, 2.5, 0.75);
		walkHopDirection = 0.2f;
		movementTimer = 150;
		damage = 5;
		timer = movementTimer;

		attackDefaultTime = 1000;
		attackTimer = 0;
		arm = EnemyArm();
		addChild(&arm, true);

		strcpy(buffer, "textures/Rustic_Door.bmp");
		tex.Load(buffer);
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
		CalculateCollider();
		if (transform.distanceSqured(player->transform.position) < player->colliderRadius)
		{
			//transform.Translate((player->transform.position - transform.position).unit() * -speed);
			if (attackTimer < 0)
			{
				((Player*)player)->TakeDamage(damage);
				attackTimer = attackDefaultTime;
			}
			else
			{
				attackTimer -= deltaTime;
			}
		}
		else
			transform.Translate((player->transform.position - transform.position).unit() * speed);

		
		transform.Translate(Vector3f(0, 1, 0) * speed * walkHopDirection);
	}

	void Display() override
	{
		glPushMatrix();
		//glColor3d(1, 0, 0);
		//glutSolidCube(1);

		GLUquadricObj * qobj;
		qobj = gluNewQuadric();
		tex.Use();
		gluQuadricTexture(qobj, true);
		//gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 0.5, 10, 10);
		gluDeleteQuadric(qobj);
		
		glPopMatrix();
	}

	void OnDisabled() override
	{
		printf("SCORE");
		((Player*)player)->score += 5;
	}
};