#ifndef COLLIDER_H
#define COLLIDER_H

#include<vector>

#include<iostream>

#include"Vector.h"
#include"Body.h"

//class Body;
namespace A3Engine {
	class Collider
	{
	public:
		static bool Collided(Body& body1, Body& body2);
		static void HandleCollision(Body& body1, Body& body2);

	private:
		static void CalcContactPoints(Body& body1, Body& body2);

		static inline Vec3 support(std::vector<Vec3>& body1, std::vector<Vec3>& body2, Vec3 d) {
			// d is a vector direction (doesn't have to be normalized)
			// get points on the edge of the shapes in opposite directions
			Vec3 p1 = Collider::getFarthestPointInDirection(body1, d);
			Vec3 p2 = Collider::getFarthestPointInDirection(body2, d.Negate());

			// perform the Minkowski Difference
			Vec3 p3 = p1 - p2;
			// p3 is now a point in Minkowski space on the edge of the Minkowski Difference
			return p3;
		}
		static inline Vec3 averagePoint(const std::vector<Vec3>& vertices) {
			Vec3 avg;
			for (int i = 0; i < vertices.size(); i++) {
				avg += vertices[i];
			}

			avg /= vertices.size();
			return avg;
		}
		static inline Vec3 tripleProduct(Vec3 a, Vec3 b, Vec3 c) {

			Vec3 r;

			// perform b * a.dot(c) - a * b.dot(c) for 2D
			r = c.Dot(a) * b - c.Dot(b) * a;
			//(abxac)xab for 3D
			//r = a.Cross(b).Cross(c);

			return r;

		}
		static inline Vec3 getFarthestPointInDirection(std::vector<Vec3>& vertices, const Vec3 & d)
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
		static Vec3 ClosestPointToOrigin(Vec3 point1, Vec3 point2);

	};
}
#endif //!COLLIDER_H