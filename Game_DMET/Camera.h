#pragma once
#include "pch.h"
class Camera : public GameObject
{
public:
	Vector3f eye, center, upward;
	Vector3f rotation;
	Transform * player;
	bool firstPerson = false;
	Camera()
	{

	}
	Camera(Transform * _player)
	{
		player = _player;
	}
	void setupCamera()
	{
		

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 640 / 480, 0.0001, 5000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		look();
	}

	void Start() override
	{
		defaultPos();
	}

	void toggleViewMode()
	{
		firstPerson = !firstPerson;
	}

	void Update() override
	{

	/*	Vector3f playerForward = player->Forward();
		Vector3f playerPos = player->position;

		center = playerForward;
		eye = playerPos;
		
		center = playerForward;	*/

		if (firstPerson)
		{
			transform.rotation = player->rotation;
			transform.position = player->position;
		}
		else
		{
			transform.rotation = player->rotation;
			transform.position = player->position - ((player->Forward() - player->position).unit() * 2 + Vector3f(0, -0.4, 0));
		}
		setupCamera();
	}
	void mainFunc()
	{
		GameObject::mainFunc();
	}

	void Display() override
	{

	}



	//Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f)
	//{
	//	
	//	eye = Vector3f(eyeX, eyeY, eyeZ);
	//	center = Vector3f(centerX, centerY, centerZ);
	//	up = Vector3f(upX, upY, upZ);
	//	defaultPos();
	//}

	void defaultPos()
	{
		eye.x = 0;
		eye.y = 10;
		eye.z = 0;

		upward.x = 0;
		upward.y = 1;
		upward.z = 0;
		transform.position = Vector3f(0,0,-10);
		transform.rotation = Vector3f(0, 0, 0);
	}

	void moveX(float d)
	{
		Vector3f right = upward.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d)
	{
		eye = eye + upward.unit() * d;
		center = center + upward.unit() * d;
	}

	void moveZ(float d)
	{
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void moveForwardBackward(float d)
	{

		Vector3f tmp = center - eye;
		tmp.y = 0;
		tmp = tmp.unit();
		eye = eye + tmp * d;
	}
	void rotateX(float a)
	{
		/*Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;*/
		//Vector3f tmp = Vector3f(center.x, center.y, center.z);
		//center.y = tmp.y * cos(DEG2RAD(a)) - tmp.z * sin(DEG2RAD(a));
		//center.z = tmp.y * sin(DEG2RAD(a)) + tmp.z * cos(DEG2RAD(a));

		transform.rotation.x -= a * 0.1f;
		//rotation.x -= a * 0.1f;
	}

	void rotateY(float a)
	{
		/*Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;*/
		//Vector3f tmp = Vector3f(center.x, center.y, center.z);
		//center.x = tmp.x * cos(DEG2RAD(a)) + tmp.z * sin(DEG2RAD(a));
		//center.z = -tmp.z * sin(DEG2RAD(a)) + tmp.z * cos(DEG2RAD(a));

		transform.rotation.y += a * 0.1f;
		//rotation.y += a * 0.1f;
	}

	

	void look()
	{
		Vector3f tmp = Vector3f(0, 0, 1);

		////applying rotation around x axis
		//tmp.y = -sin(DEG2RAD(rotation.x));
		//tmp.z = cos(DEG2RAD(rotation.x));

		////applying rotation around y axis

		//center = Vector3f(tmp.x, tmp.y, tmp.z);

		//center.x = tmp.z * sin(DEG2RAD(rotation.y));
		//center.z = tmp.z * cos(DEG2RAD(rotation.y));

		center = transform.Forward();
		eye = transform.position;

		//center = center;
		//

		//printf("eye : %f , %f , %f \n", rotation.x, rotation.y, rotation.z);
		//printf("center : %f , %f , %f \n",center.x, center.y, center.z);
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			upward.x, upward.y, upward.z);
	}
};