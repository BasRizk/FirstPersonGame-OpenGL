#pragma once
#include "pch.h"
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
#define RAD2DEG(a) (a * 57.2958)
#define PlanetRadiusFactor 1.0f / 1185.0f
#define OrbetRadiusFactor 1.0f / 5.7f


using namespace std;

class Color
{
public:
	float r;

	float g;

	float b;

	float a;

	Color() {}
	Color(float red, float green, float blue) : r(red / 100.0f), g(green / 100.0f), b(blue / 100.0f), a(1) {}
	Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {}
};

enum Space
{
	self,
	world
};

void DrawCircle(float x, float y, float radius, bool midPoint, Color color, float minAngle, float maxAngle)
{
	float angle = 0;
	float x_value;
	float y_value;
	glPushMatrix();
	glTranslated(x, y, 0);
	glBegin(GL_LINE_LOOP);
	glColor4f(color.r, color.g, color.b, color.a);
	for (angle = minAngle; angle < maxAngle; angle += 5)
	{
		x_value = radius * cos((angle / 180.0f) * 3.14);
		y_value = radius * sin((angle / 180.0f) * 3.14);
		glVertex3f(x_value, 0, y_value);
	}
	glEnd();
	glPopMatrix();
}

void DrawCircle(float x, float y, float radius, bool midPoint, Color color)
{
	DrawCircle(x, y, radius, midPoint, color, 0, 360);
}

class Transform
{
public:
	Vector3f position;
	Vector3f localScale;
	Vector3f rotation;
	
	Transform * parent;

	static Transform defaultParentTranform;

	Transform()
	{
		position = Vector3f(0, 0, 0);
		localScale = Vector3f(1, 1, 1);
		rotation = Vector3f(0, 0, 0);
	}
	void Translate(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}

	void Translate(Vector3f direction)
	{
		Translate(direction.x, direction.y, direction.z);
	}

	void Rotate(float x, float y, float z, Space space)
	{
		switch (space)
		{
	/*	case self:
			localRotation().x += x;
			localRotation().y += y;
			localRotation().z += z;
			break;*/
		case world:
			rotation.x += x;
			rotation.y += y;
			rotation.z += z;
			break;
		default:
			break;
		}
	}

	void Rotate(Vector3f angle, Space space)
	{
		Rotate(angle.x, angle.y, angle.z, space);
	}

	void Rotate(Vector3f angle)
	{
		Rotate(angle.x, angle.y, angle.z, self);
	}

	void Rotate(float x, float y, float z)
	{
		Rotate(x, y, z, self);
	}


	void ScaleAdd(Vector3f scaleFactor)
	{
		localScale = localScale + scaleFactor;
	}

	Vector3f Forward()
	{
		Vector3f tmp = Vector3f(0, 0, 1);
		//Rotation Around X
		tmp.y = tmp.y * cos(DEG2RAD(rotation.x)) - tmp.z * sin(DEG2RAD(rotation.x));
		tmp.z = tmp.y * sin(DEG2RAD(rotation.x)) + tmp.z * cos(DEG2RAD(rotation.x));
		
		

		Vector3f forward = Vector3f(tmp.x, tmp.y, tmp.z);
		//Rotation Around Y
		forward.x = tmp.x * cos(DEG2RAD(rotation.y)) + tmp.z * sin(DEG2RAD(rotation.y));
		forward.z = -tmp.x * sin(DEG2RAD(rotation.y)) + tmp.z * cos(DEG2RAD(rotation.y));
		
		return forward + position;
	}

	Vector3f localRotation()
	{
		return rotation - parent->rotation;
	}

};
class GameObject
{
public:
	Transform transform;
	clock_t start;
	clock_t deltaTime;
	float boundryPoints[4];
	vector<GameObject *> connectedChildren;
	vector<GameObject *> freeChildren;
	bool isGameOn;
	// Vector3 boundryPointsDistanceFromPivot[4];
	// bool defaultCollider = true;
	
	GameObject()
	{
		transform = Transform();
		transform.parent = &Transform::defaultParentTranform;

		printf("%s\n", "CONS");
		start = clock();
		Start();
	}

	virtual void Start()
	{
		// printf("%s\n", "wrong");
	}

	virtual void Display()
	{
	}

	void CalculateCollider()
	{
		// if (defaultCollider)
		// {
		// 	boundryPoints[0] = Vector3(position.x - scale.x * 0.5f, position.y - scale.y * 0.5f, 0);
		// 	boundryPoints[1] = Vector3(position.x + scale.x * 0.5f, position.y - scale.y * 0.5f, 0);
		// 	boundryPoints[2] = Vector3(position.x + scale.x * 0.5f, position.y + scale.y * 0.5f, 0);
		// 	boundryPoints[3] = Vector3(position.x - scale.x * 0.5f, position.y + scale.y * 0.5f, 0);
		// }
		// else
		// {
		// 	for (int i = 0; i < 4; i++)
		// 	{
		// 		boundryPoints[i].Add(boundryPointsDistanceFromPivot[i]);
		// 		boundryPoints[i].Add(position);
		// 	}
		// }
		boundryPoints[0] = transform.position.x - transform.localScale.x * 0.5f;
		boundryPoints[1] = transform.position.x + transform.localScale.x * 0.5f;
		boundryPoints[2] = transform.position.y - transform.localScale.y * 0.5f;
		boundryPoints[3] = transform.position.y + transform.localScale.y * 0.5f;
	}

	bool DetectCollision(float points[])
	{
		if (boundryPoints[0] > points[1] || boundryPoints[1] < points[0] || boundryPoints[3] < points[2] || boundryPoints[2] > points[3])
			return false;
		else
			return true;

		// if (points[0]-> > boundryPoints[0].x && points[0].x < boundryPoints[1].x || points[1].x > boundryPoints[0].x && points[1].x < boundryPoints[1].x)
		// {
		// 	if (points[0].y > boundryPoints[0].y && points[0].y < boundryPoints[2].y || points[2].y > boundryPoints[0].y && points[2].y < boundryPoints[2].y)
		// 	{
		// 		return true;
		// 	}
		// }
		// else if (points[0].x > boundryPoints[0].x && points[0].x < boundryPoints[1].x || points[1].x > boundryPoints[0].x && points[1].x < boundryPoints[1].x)
		// {
		// 	if (points[0].y > boundryPoints[0].y && points[0].y < boundryPoints[2].y || points[2].y > boundryPoints[0].y && points[2].y < boundryPoints[2].y)
		// 	{
		// 		return true;
		// 	}
		// }
		// return false;
	}
	void addChild(GameObject *obj, bool connected)
	{
		obj->Start();
		if(connected)
			connectedChildren.push_back(obj);
		else
			freeChildren.push_back(obj);
	}
	

	void internalUpdate()
	{
	}

	virtual void Update()
	{
		printf("%s\n", "update BASE");
	}

	void mainFunc()
	{
		// printf("%s\n","main");
		deltaTime = clock() - start;
		start = clock();
		Update();
		glPushMatrix();
		// glTranslated(position.x + translateFactor.x, position.y + translateFactor.y, position.z + translateFactor.z);
		// glRotated(rotation + rotateFactor, 0, 0, 1);
		// glScaled(scale.x, scale.y, scale.z);

		//glTranslated(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);

		//glRotated(transform.localRotation.x, 1, 0, 0);
		//glRotated(transform.localRotation.y, 0, 1, 0);
		//glRotated(transform.localRotation.z, 0, 0, 1);


		//if (transform.parent != NULL)
		//{
		//	



		//glTranslated(transform.parent->position.x, transform.parent->position.y, transform.parent->position.z);

		//glRotated(transform.parent->rotation.x, 1, 0, 0);
		//glRotated(transform.parent->rotation.y, 0, 1, 0);
		//glRotated(transform.parent->rotation.z, 0, 0, 1);

		//glTranslated(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);

		//glRotated(transform.localRotation.x, 1, 0, 0);
		//glRotated(transform.localRotation.y, 0, 1, 0);
		//glRotated(transform.localRotation.z, 0, 0, 1);

		//glScaled(transform.parent->localScale.x, transform.parent->localScale.y, transform.parent->localScale.z);
		////}
		//glScaled(transform.localScale.x, transform.localScale.y, transform.localScale.z);

		glTranslated(transform.position.x, transform.position.y, transform.position.z);

		glRotated(transform.rotation.y, 0, 1, 0);
		glRotated(transform.rotation.x, 1, 0, 0);
		glRotated(transform.rotation.z, 0, 0, 1);
		
		glScaled(transform.localScale.x, transform.localScale.y, transform.localScale.z);

		Display();

		for (GameObject *obj1 : connectedChildren)
		{
			obj1->mainFunc();
		}

		glPopMatrix();

		for (GameObject *obj1 : freeChildren)
		{
			obj1->mainFunc();
		}
	}
};
