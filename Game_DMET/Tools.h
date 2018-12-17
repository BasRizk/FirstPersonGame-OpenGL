#pragma once




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
class Vector3f
{
public:
	float x, y, z;
	

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}

public: static Vector3f up;
public: static Vector3f down;
	static Vector3f left;
	static Vector3f right;
	static Vector3f forward;
	static Vector3f backward;

	Vector3f operator+(Vector3f v)
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f v)
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n)
	{
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n)
	{
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit()
	{
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v)
	{
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	float  dot(Vector3f v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
};

//Vector3f Vector3f::up = Vector3f(0, 1, 0);
Vector3f Vector3f::down = Vector3f(0, -1, 0);
Vector3f Vector3f::forward = Vector3f(0, 0, 1);
Vector3f Vector3f::backward = Vector3f(0, 0, -1);
Vector3f Vector3f::right = Vector3f(1, 0, 0);
Vector3f Vector3f::left = Vector3f(-1, 0, 0);


//void DrawRectangle(float x, float y, float height, float width, bool midPoint)
//{
//	DrawRectangle(x, y, height, width, midPoint, Color(1, 1, 1));
//}