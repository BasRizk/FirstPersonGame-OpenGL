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

public:
	Bullet()
	{

	}
	Bullet(Vector3f _direction, float _speed, Vector3f _position)
	{
		speed = _speed;
		direction = _direction;
		position = _position;
	}

	void Start() override
	{
		transform.position = position;
	}

	void Update() override
	{
		transform.Translate(direction * speed);
		printf("speed : %f , Direction: %f , %f , %f  \n", speed, direction.x , direction.y , direction.z);
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
	Bullet bullet;
	void Start() override
	{
		cameraHolder = CameraHolder();
		addChild(&cameraHolder , true);
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
		bullet = Bullet((transform.Forward() - transform.position).unit(), 0.1f , cameraHolder.transform.position + transform.position);
		addChild(&bullet, false);
	}

	void move()
	{
		Vector3f tmp = transform.Forward() - transform.position;
		tmp.y = 0;
		tmp = tmp.unit();
		switch (movementDirection)
		{

		case STOP :
		case FORWARD_BACKWARD:
		case LEFT_RIGHT:
			break;
		case FORWARD:
		case FORWARD_LEFT_RIGHT:
			transform.Translate(tmp * speed);
			break;
		case BACKWARD:
		case BACKWARD_LEFT_RIGHT:
			transform.Translate(tmp * -speed);
			break;
		case RIGHT:
		case FORWARD_BACKWARD_RIGHT:
			tmp = tmp.cross(Vector3f(0,1,0));
			transform.Translate(tmp.unit() * speed);
			break;
		case LEFT:
		case FORWARD_BACKWARD_LEFT:
			tmp = tmp.cross(Vector3f(0,1,0));
			transform.Translate(tmp.unit() * -speed);
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
