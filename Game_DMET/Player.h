#pragma once
#include "pch.h"

enum DIRECTION {
	STOP, FORWARD, BACKWARD, FORWARD_BACKWARD, RIGHT, FORWARD_RIGHT , BACKWARD_RIGHT , 
	FORWARD_BACKWARD_RIGHT, LEFT , FORWARD_LEFT, BACKWARD_LEFT , FORWARD_BACKWARD_LEFT, 
	LEFT_RIGHT, FORWARD_LEFT_RIGHT, BACKWARD_LEFT_RIGHT , FORWARD_BACKWARD_LEFT_RIGHT
};
inline DIRECTION operator|(DIRECTION a, DIRECTION b)
{
	return static_cast<DIRECTION>(static_cast<int>(a) | static_cast<int>(b));
}
inline DIRECTION operator~(DIRECTION a)
{
	return static_cast<DIRECTION>(~static_cast<int>(a));
}
inline DIRECTION operator&(DIRECTION a, DIRECTION b)
{
	return static_cast<DIRECTION>(static_cast<int>(a) & static_cast<int>(b));
}

class Bullet : public GameObject {

	float speed;
	float maxDistance;
	Vector3f direction;
	Vector3f position;
	GameObject * spawner;


public:
	Bullet()
	{

	}
	Bullet(Vector3f _direction, Vector3f _position , GameObject * _spawner)
	{
		direction = _direction;
		position = _position;
		spawner = _spawner;
	}

	void Start() override
	{
		transform.position = position;
		maxDistance = 50;
		speed = 2;
	}

	void Update() override
	{
		Vector3f distance = direction.unit() * speed;
		if (maxDistance - speed < 0)
			SetActive(false);
		else
			maxDistance -= speed;

		transform.Translate(distance);
		//printf("speed : %f , Direction: %f , %f , %f  \n", speed, transform.position.x , transform.position.y , transform.position.z);
		CalculateCollider();
	
		for (GameObject * enemy : spawner->freeChildren)
		{
			if (enemy->enabled && DetectCollision(enemy->boundryPoints))
			{
				printf("HIT");
				enemy->SetActive(false);
				SetActive(false);
			}
		}
		
	}

	void Display() override
	{
		glutSolidSphere(0.5, 15, 15);
	}
};

class CameraHolder : public GameObject {

public:

	CameraHolder()
	{

	}
	void Start() override
	{
		transform.position = Vector3f(-0.2, -0.2, 0.5);
		transform.localScale.x = 0.2f;
		transform.localScale.y = 0.2f;
	}

	void Update() override
	{
		//transform.rotation.y = -transform.rotation.y;
	}

	void mainFunc()
	{
		GameObject::mainFunc();
	}

	void Display() override
	{
		glutSolidCube(0.5f);
	}

};
class Player : public GameObject {

	float speed;
	float movementTimer;
	float timer;
	float walkHopDirection;
public:
	DIRECTION movementDirection;
	CameraHolder cameraHolder;
	GameObject * spawner;
	int HP;
	int ammo;
	int score;
	GLTexture tex;

	Player()
	{
		
	}
	Player(GameObject * _spawner)
	{
		spawner = _spawner;
	
	}

	void TakeDamage(float value)
	{
		HP -= value;
	}

	void Start() override
	{
		cameraHolder = CameraHolder();
		addChild(&cameraHolder, true);
		RestartGame();

		char buffer[80];
		strcpy(buffer, "textures/blu-sky-3.bmp");
		tex.Load(buffer);
	}

	void RestartGame()
	{
		transform.position = Vector3f(0, 0, 0);
		speed = 0.1;
		walkHopDirection = 0.5f;
		movementTimer = 150;
		timer = movementTimer;
		colliderRadius = 4;
		HP = 100;
		ammo = 30;
		score = 0;
		movementDirection = STOP;
	}

	void Update() override
	{
		move();
		CalculateCollider();
	}

	void mainFunc()
	{
		GameObject::mainFunc();
	}

	void Shoot()
	{
		if (ammo > 0)
		{
			Bullet * bullet = new Bullet((transform.Forward() - transform.position).unit(), cameraHolder.transform.position + transform.position , spawner);
			addChild(bullet, false);
			ammo--;
		}		
	}

	void move()
	{
		
		Vector3f fwd = transform.Forward() - transform.position;
		fwd.y = 0;
		fwd = fwd.unit();
		//Vector3f right = fwd.cross(Vector3f(0, 1, 0));
		//Vector3f direction = Vector3f(0, 0, 0);
		//Vector3f tmp;
		//if ((movementDirection)  & FORWARD)
		//{
		//	tmp = direction + fwd;
		//	direction = tmp;
		//	printf("fwd");
		//}
		//if ((movementDirection)  & BACKWARD)
		//{
		//	tmp = direction - fwd;
		//	direction = tmp;
		//}
		//if ((movementDirection)  & LEFT)
		//{
		//	tmp = direction + right;
		//	direction = tmp;
		//}
		//if ((movementDirection)  & RIGHT)
		//{
		//	tmp = direction - right;
		//	direction = tmp;
		//}
		//printf("direction : %f , %f , %f \n", direction.x, direction.y, direction.z);
		//transform.Translate(direction.unit() * speed);

		switch (movementDirection)
		{

		case STOP :
		case FORWARD_BACKWARD:
		case LEFT_RIGHT:
			break;
		case FORWARD:
		case FORWARD_LEFT_RIGHT:
			if (timer < 0)
			{
				walkHopDirection = -walkHopDirection;
				timer = movementTimer;
			}
			else
				timer -= deltaTime;
			transform.Translate(fwd * speed);
			transform.Translate(Vector3f(0,1,0) * speed * walkHopDirection);
			break;
		case BACKWARD:
		case BACKWARD_LEFT_RIGHT:
			if (timer < 0)
			{
				walkHopDirection = -walkHopDirection;
				timer = movementTimer;
			}
			else
				timer -= deltaTime;
			transform.Translate(fwd * -speed);
			transform.Translate(Vector3f(0, 1, 0) * speed * walkHopDirection);
			break;
		case RIGHT:
		case FORWARD_BACKWARD_RIGHT:
			if (timer < 0)
			{
				walkHopDirection = -walkHopDirection;
				timer = movementTimer;
			}
			else
				timer -= deltaTime;
			fwd = fwd.cross(Vector3f(0,1,0));
			transform.Translate(fwd.unit() * speed);
			transform.Translate(Vector3f(0, 1, 0) * speed * walkHopDirection);
			break;
		case LEFT:
		case FORWARD_BACKWARD_LEFT:
			if (timer < 0)
			{
				walkHopDirection = -walkHopDirection;
				timer = movementTimer;
			}
			else
				timer -= deltaTime;
			fwd = fwd.cross(Vector3f(0,1,0));
			transform.Translate(fwd.unit() * -speed);
			transform.Translate(Vector3f(0, 1, 0) * speed * walkHopDirection);
			break;
		default:
			break;
		}
	}

	void rotateX(float a)
	{
		transform.rotation.x -= a * 0.1f;
	}

	void rotateY(float a)
	{
		transform.rotation.y += a * 0.1f;
	}

	void moveX(float d)
	{
		Vector3f right = Vector3f(0,1,0).cross(transform.Forward()).unit();
		transform.position = transform.position + right * d;
		//center = center + right * d;
	}

	void moveForwardBackward(float d)
	{
		Vector3f tmp = transform.Forward() - transform.position;
		tmp.y = 0;
		tmp = tmp.unit();
		transform.position = transform.position + tmp * d;
	}

	void Display() override
	{
		glPushMatrix();
		glTranslated(0, 0, -0.5);
		/*glutSolidCube(0.5);*/

		GLUquadricObj * qobj;
		qobj = gluNewQuadric();
		tex.Use();
		gluQuadricTexture(qobj, true);
		gluQuadricNormals(qobj, GL_SMOOTH);
		gluSphere(qobj, 0.2, 10, 10);
		gluDeleteQuadric(qobj);

		glPopMatrix();
	}

};
