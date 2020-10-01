#ifndef BODY_H
#define BODY_H

#include<SDL.h>
#include<SDL_image.h>
#include"Vector.h"
#include<vector>

using namespace MATH;
class Body
{
private:
	double mass;									//variable to hold the value of mass
	float rotationalInertia;					//variable to hold rotational inertia
	SDL_Surface *bodyImage;
public:
	Vec3 position;								//variable to hold the value of position
	Vec3 linearVelocity;							//variable to hold the value of velocity
	Vec3 acceleration;							//variable to hold the value of acceleration

	float angle;
	Vec3 angularVelocity;						//variable to hold the value of angular velocity
	Vec3 angularAcceleration;					//variable to hold the value of angular acceleration

	Vec3 force;


	std::vector<Vec3> vertices;

	Body(double _mass);
	Body(double _mass, float _rotationalInertia);
	Body(char* _imageName, double _mass, Vec3 _position, Vec3 _linearVelocity, Vec3 _acceleration);
	void update(double timeStep);
	void UpdateOrientation(double timeStep);
	void ApplyTorque(const Vec3& _torque);
	void ApplyForceToCentre(const Vec3& force);   // update acceleration using a = F/m


	Vec3 getFarthestPointInDirection(const Vec3& d);
	void addVertex(const Vec3 _vertex);

	SDL_Surface* getImage();
	double getMass();
	float getRotationalInertia();

};
#endif //!BODY_H