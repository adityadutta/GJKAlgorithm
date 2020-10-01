#include "Body.h"
#include<iostream>
#include"MMath.h"

using namespace MATH;

Body::Body(double _mass)
{
	mass = _mass;
}

Body::Body(double _mass, float _rotationalInertia)
{
	mass = _mass;
	rotationalInertia = _rotationalInertia;
	position.SetZero();
	linearVelocity.SetZero();
	acceleration.SetZero();
	angle = 0.0f;
	angularVelocity.SetZero();
	angularAcceleration.SetZero();
}

//constructor to pass values in the class
Body::Body(char* _imageName, double _mass, Vec3 _position, Vec3 _linearVelocity, Vec3 _acceleration)
{
	mass = _mass;
	position = _position;
	linearVelocity = _linearVelocity;
	acceleration = _acceleration;
	bodyImage = IMG_Load(_imageName);
	if (bodyImage == nullptr) {
		/// What should we do?
	}
}
void Body::update(double timeStep)
{

	//update position from velocity times timeStep
	//position = position(init) + linearVelocity * time + 0.5 * acceleration * time ^2
	position += linearVelocity * timeStep + acceleration * 0.5 * timeStep * timeStep;

	for (int i = 0; i < this->vertices.size(); i++) {
		vertices[i] += linearVelocity * timeStep + acceleration * 0.5 * timeStep * timeStep;
	}

	//update velocity from acceleration times timeStep
	//linearVelocity = linearVelocity(init) + acceleration * time;
	linearVelocity += acceleration * timeStep;

	acceleration.SetZero();
}

void Body::UpdateOrientation(double timeStep)
{
	//angle = angle(i) + angularVel * t + 0.5 * angularAcc * t^2
	angle += (angularVelocity.Mag() * timeStep) + (angularAcceleration.Mag() * 0.5 * timeStep * timeStep);

	//angularVelocity = angularVelocity(init) + angularAcceleration * time;
	angularVelocity += angularAcceleration * timeStep;

	for (int i = 0; i < this->vertices.size(); i++) {
		float x = vertices[i].x * cos(angle * DEGREES_TO_RADIANS) - vertices[i].y * sin(angle * DEGREES_TO_RADIANS);
		float y = vertices[i].x * sin(angle * DEGREES_TO_RADIANS) + vertices[i].y * cos(angle * DEGREES_TO_RADIANS);
		vertices[i].x = x;
		vertices[i].y = y;
	}


	angularVelocity.SetZero();
}

void Body::ApplyTorque(const Vec3& _torque)
{
	//Apply torque
	//a = t/I;
	angularAcceleration = _torque / rotationalInertia;
}

void Body::ApplyForceToCentre(const Vec3& force)
{
	//a = f/m
	float fx = (force.x * cos(angle  * DEGREES_TO_RADIANS)) - (force.y * sin(angle  * DEGREES_TO_RADIANS));
	float fy = (force.y * cos(angle  * DEGREES_TO_RADIANS)) + (force.x * sin(angle  * DEGREES_TO_RADIANS));

	//set force in the body
	this->force.Set(fx, fy, 0.0f);

	//a = f/m
	acceleration = this->force / mass;
}


Vec3 Body::getFarthestPointInDirection(const Vec3 & d)
{
	Vec3 farthestPoint;
	int index = 0;
	float maxProduct = d.Dot(vertices[0]);
	for (int i = 1; i < vertices.size(); i++) {
		float product = d.Dot(vertices[i]);
		if (product > maxProduct) {
			maxProduct = product;
			index = i;
		}
	}
	farthestPoint = vertices[index];
	return farthestPoint;
}

void Body::addVertex(const Vec3 _vertex)
{
	vertices.push_back(_vertex);
}

SDL_Surface* Body::getImage() {
	return bodyImage;
}

double Body::getMass() {
	return mass;
}

float Body::getRotationalInertia() {
	return rotationalInertia;
}