#include "Vector.h"
#include<iostream>
using namespace MATH;

//default constructor for vector3
Vec3::Vec3()
{
	SetZero();
}

//parameterized constructor to pass in values to vector3
Vec3::Vec3(float _x, float _y, float _z)
{
	Set(_x, _y, _z);
}

//using pythagorean theorem to find length of vector
float Vec3::Mag() const
{
	return sqrt(LengthSquared());
}

//using pythagorean theorem to find length of vector
float Vec3::LengthSquared() const
{
	return (x*x + y * y + z * z);
}

//normalizing vector to 1
Vec3 Vec3::Normalize() const
{
	return DivideBy(Mag());
}

//negating vector
Vec3 Vec3::Negate() const
{
	return Vec3(-x, -y, -z);
}

//adding two vector3
Vec3 Vec3::Add(const Vec3& V) const
{
	return Vec3(x + V.x, y + V.y, z + V.z);
}

//dot product of given vector
float Vec3::Dot(const Vec3& V) const
{
	float tempX, tempY, tempZ, dotProduct;
	tempX = x * V.x;
	tempY = y * V.y;
	tempZ = z * V.z;
	dotProduct = tempX + tempY + tempZ;
	return dotProduct;
}

//cross product of given vector
Vec3 Vec3::Cross(const Vec3& V) const
{
	return Vec3(y * V.z - z * V.y,
		z * V.x - x * V.z,
		x * V.y - y * V.x);
}

//dividing vector3 by float a
Vec3 Vec3::DivideBy(float a) const
{
	return Vec3(x / a, y / a, z / a);
}

//multiplying  vector3 by float a
Vec3 Vec3::Multiply(float a) const
{
	return DivideBy(1 / a);
}

//sutracting two vector3
Vec3 Vec3::Subtract(const Vec3& V) const
{
	return Vec3(x - V.x, y - V.y, z - V.z);
}

//setting vector3 to another vector3
void Vec3::Set(const Vec3& V)
{
	x = V.x;
	y = V.y;
	z = V.z;
}

//passing the parameters in the class
void Vec3::Set(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

//calling th set function to set the values to zero
void Vec3::SetZero()
{
	Set(0.0f, 0.0f, 0.0f);
}

float Vec3::Distance(const Vec3 &V1, const Vec3 &V2) {
	Vec3 r = V1 - V2;
	return(r.Mag());
}

const bool Vec3::operator==(const Vec3 & rhs)
{
	if (x == rhs.x && y == rhs.y && z == rhs.z) {
		return true;
	}

	return false;
}

///Vec4 Methods

//default constructor for vector3
Vec4::Vec4()
{
	SetZero();
}

//parameterized constructor to pass in values to vector3
Vec4::Vec4(float _x, float _y, float _z, float _w)
{
	Set(_x, _y, _z, _w);
}

//using pythagorean theorem to find length of vector
float Vec4::Mag() const
{
	return sqrt(LengthSquared());
}

//using pythagorean theorem to find length of vector
float Vec4::LengthSquared() const
{
	return (x*x + y * y + z * z + w * w);
}

//normalizing vector to 1
Vec4 Vec4::Normalize() const
{
	return DivideBy(Mag());
}

//adding two vector3
Vec4 Vec4::Add(const Vec4& V) const
{
	return Vec4(x + V.x, y + V.y, z + V.z, w + V.w);
}

//dot product of given vector
float Vec4::Dot(const Vec4& V) const
{
	float tempX, tempY, tempZ, tempW, dotProduct;
	tempX = x * V.x;
	tempY = y * V.y;
	tempZ = z * V.z;
	tempW = w * V.w;
	dotProduct = tempX + tempY + tempZ + tempW;
	return dotProduct;
}

//dividing vector3 by float a
Vec4 Vec4::DivideBy(float a) const
{
	return Vec4(x / a, y / a, z / a, w / a);
}

//multiplying  vector3 by float a
Vec4 Vec4::Multiply(float a) const
{
	return DivideBy(1 / a);
}

//sutracting two vector3
Vec4 Vec4::Subtract(const Vec4& V) const
{
	return Vec4(x - V.x, y - V.y, z - V.z, w - V.w);
}

//setting vector3 to another vector3
void Vec4::Set(const Vec4& V)
{
	x = V.x;
	y = V.y;
	z = V.z;
	w = V.w;
}

//passing the parameters in the class
void Vec4::Set(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

//calling th set function to set the values to zero
void Vec4::SetZero()
{
	Set(0.0f, 0.0f, 0.0f, 0.0f);
}

///
///RAY METHODS
///
Ray::Ray(Vec3 _start, Vec3 _dir) {
	start = _start;
	dir = _dir;
}

Vec3 Ray::currentPosition(float t) {
	//calculating position at t
	//p(t) = S + Vt
	Vec3 position = start + dir * t;
	return position;
}

///
///PLANE METHODS
///
Plane::Plane(float _x, float _y, float _z, float _w) {
	plane.Set(_x, _y, _z, _w);
}

Plane::Plane(const Vec3& V0, const Vec3& V1, const Vec3& V2) {
	//e1 = B - A, e2 = C - B
	Vec3 e1 = V1 - V0;
	Vec3 e2 = V2 - V1;
	// N = e1 X e2
	Vec3 tempNormal = e1.Cross(e2);
	// d = -(N.A / |N|)
	float d = -(tempNormal.Dot(V0) / tempNormal.Mag());
	//normalizing the normal
	Vec4 normalizedNormal(tempNormal.Normalize().x, tempNormal.Normalize().y, tempNormal.Normalize().z, d);
	plane.Set(normalizedNormal);
}

Vec3 Plane::intersectionPoint(Ray ray) {
	//normal of the plane
	Vec3 normal(plane.x, plane.y, plane.z);
	//checking if N.V is zero
	if (abs(normal.Dot(ray.dir)) < VERY_SMALL) {
		//homogenous form of the ray
		Vec4 ray4D(ray.start.x, ray.start.y, ray.start.z, 1.0f);
		//checking if line lies on plane, <L.S>
		if (abs(this->plane.Dot(ray4D)) < VERY_SMALL) {
			std::cout << "Line lies on the plane\n";
			return Vec3();
		}
		else {
			//if line is parallel to plane
			std::cout << "Line is parallel to the plane\n";
			return Vec3();
		}
	}
	else {
		//calculating t, t = -(D + N.S)/ N.V
		float t = -((plane.w + (normal.Dot(ray.start))) / (normal.Dot(ray.dir)));
		//calculating the point of intersection
		Vec3 intersectPoint;
		intersectPoint = ray.currentPosition(t);

		return intersectPoint;
	}
}