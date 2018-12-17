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
	Vector3f direction;
	Vector3f position;
	GameObject * spawner;

public:
	Bullet()
	{

	}
	Bullet(Vector3f _direction, float _speed, Vector3f _position , GameObject * _spawner)
	{
		speed = _speed;
		direction = _direction;
		position = _position;
		spawner = _spawner;
	}

	void Start() override
	{
		transform.position = position;
	}

	void Update() override
	{
		transform.Translate(direction.unit() * speed);
		//printf("speed : %f , Direction: %f , %f , %f  \n", speed, transform.position.x , transform.position.y , transform.position.z);
		CalculateCollider();
	
		for (GameObject * enemy : spawner->freeChildren)
		{
			if (DetectCollision(enemy->boundryPoints))
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
public:
	DIRECTION movementDirection;
	CameraHolder cameraHolder;
	GameObject * spawner;

	Player()
	{

	}
	Player(GameObject * _spawner)
	{
		spawner = _spawner;
	}

	void Start() override
	{
		cameraHolder = CameraHolder();
		addChild(&cameraHolder, true);
		transform.position = Vector3f(0, 0, 0);
		speed = 0.1;
		movementDirection = STOP;
	}

	void Update() override
	{
		move();
	}

	void mainFunc()
	{
		GameObject::mainFunc();
	}

	void Shoot()
	{
		Bullet * bullet = new Bullet((transform.Forward() - transform.position).unit(), 1 , cameraHolder.transform.position + transform.position , spawner);
		addChild(bullet, false);
		
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
			transform.Translate(fwd * speed);
			break;
		case BACKWARD:
		case BACKWARD_LEFT_RIGHT:
			transform.Translate(fwd * -speed);
			break;
		case RIGHT:
		case FORWARD_BACKWARD_RIGHT:
			fwd = fwd.cross(Vector3f(0,1,0));
			transform.Translate(fwd.unit() * speed);
			break;
		case LEFT:
		case FORWARD_BACKWARD_LEFT:
			fwd = fwd.cross(Vector3f(0,1,0));
			transform.Translate(fwd.unit() * -speed);
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
		glTranslated(-1, -1, -1);
		glutWireCube(2);
		glPopMatrix();
	}

};
