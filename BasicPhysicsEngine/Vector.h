#ifndef VECTOR_H
#define VECTOR_H

#include<string>
#include<sstream>
#include<math.h>

namespace MATH {

#pragma region MACROS

#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS (M_PI / 180.0f)
#endif	

#define VECTOR3_ZERO	Vec3(0.0f, 0.0f, 0.0f)
#define VECTOR3_BACK	Vec3(0.0f, 0.0f, 1.0f)
#define VECTOR3_DOWN	Vec3(0.0f, -1.0f, 0.0f)
#define VECTOR3_FORWARD Vec3(0.0f, 0.0f, -1.0f)
#define VECTOR3_LEFT	Vec3(-1.0f, 0.0f, 0.0f)
#define VECTOR3_RIGHT	Vec3(1.0f, 0.0f, 0.0f)
#define VECTOR3_UP		Vec3(0.0f, 1.0f, 0.0f)


#pragma endregion

	struct Vec3
	{
		float x, y, z;

		Vec3();
		Vec3(float _x, float _y, float _z);

		float Mag() const;				// return the length (magnitude) of the vector
		float LengthSquared() const;
		Vec3 Normalize() const;					// converts vector into the unit vector
		Vec3 Negate() const;

		Vec3 Add(const Vec3& V) const;
		float Dot(const Vec3& V) const;  // returns the dot product
		Vec3 Cross(const Vec3& V) const;
		Vec3 DivideBy(float a) const;
		Vec3 Multiply(float a) const;
		Vec3 Subtract(const Vec3& V) const;

		void Set(const Vec3& V);
		void Set(float _x, float _y, float _z);
		void SetZero();						// set x and y to zero

		static float Distance(const Vec3& V1, const Vec3& V2);

		inline const std::string toString() const {
			std::stringstream stringStream;
			stringStream << "Vec3[ " << x << ", " << y << ", " << z << "]";
			return stringStream.str();
		}

		//overloading operators
		inline const Vec3 operator -() const			// negate vector. Const member can’t modify object
		{
			return Negate();
		}
		inline const Vec3 operator /(float rhs) const		// divide by a number "a"
		{
			return DivideBy(rhs);
		}
		inline const Vec3 operator *(float rhs) const		// multiply by a number "a"
		{
			return Multiply(rhs);
		}
		inline const Vec3 operator +(const Vec3& rhs) const	//add two vectors without changing values
		{
			return Add(rhs);
		}
		inline const Vec3 operator -(const Vec3& rhs) const
		{
			return Subtract(rhs);
		}
		inline const Vec3 operator += (const Vec3& rhs) // add a vector and assign. Using pass-by-const-reference
		{
			Set(Add(rhs));
			return *this;
		}
		inline const Vec3 operator -= (const Vec3& rhs) // subtract a vector to this vector
		{
			Set(Subtract(rhs));
			return *this;
		}
		inline const Vec3 operator *= (float rhs)		// multiply by a number “a” and set its value
		{
			Set(Multiply(rhs));
			return *this;
		}
		inline const Vec3 operator /= (float rhs)
		{
			Set(DivideBy(rhs));
			return *this;
		}
		inline const Vec3 operator = (const Vec3& rhs)
		{
			Set(rhs);
			return *this;
		}
		const bool operator == (const Vec3& rhs); // compare 2 vectors

		//friend function
		//multiplication is associative a*b = b*a
		//lhs * rhs 
		//float a;
		//a * vector
		//to overcome the ambiguity of the vector being on the rhs rather than on the lhs
		friend inline Vec3 operator * (float lhs, const Vec3& rhs)
		{
			return rhs.Multiply(lhs);
		}
	};

	struct Vec4 {
		float x, y, z, w;

		Vec4();
		Vec4(float _x, float _y, float _z, float _w);

		// Return the magnitude of the vector using Pythagoras’s theorem
		float Mag() const;

		// Normalize the vector by dividing it by it’s magnitude
		Vec4 Normalize() const;
		float LengthSquared() const;

		Vec4 Add(const Vec4& V) const;
		float Dot(const Vec4& V) const;  // returns the dot product
		Vec4 DivideBy(float a) const;
		Vec4 Multiply(float a) const;
		Vec4 Subtract(const Vec4& V) const;

		void Set(const Vec4& V);
		void Set(float _x, float _y, float _z, float _w);
		void SetZero();

		inline const Vec4 operator /(float rhs) const		// divide by a number "a"
		{
			return DivideBy(rhs);
		}
		inline const Vec4 operator *(float rhs) const		// multiply by a number "a"
		{
			return Multiply(rhs);
		}
		inline const Vec4 operator +(const Vec4& rhs) const	//add two vectors without changing values
		{
			return Add(rhs);
		}
		inline const Vec4 operator -(const Vec4& rhs) const
		{
			return Subtract(rhs);
		}
		inline const Vec4 operator += (const Vec4& rhs) // add a vector and assign. Using pass-by-const-reference
		{
			Set(Add(rhs));
			return *this;
		}
		inline const Vec4 operator -= (const Vec4& rhs) // subtract a vector to this vector
		{
			Set(Subtract(rhs));
			return *this;
		}
		inline const Vec4 operator *= (float rhs)		// multiply by a number “a” and set its value
		{
			Set(Multiply(rhs));
			return *this;
		}
		inline const Vec4 operator /= (float rhs)
		{
			Set(DivideBy(rhs));
			return *this;
		}
		inline const Vec4 operator = (const Vec4& rhs)
		{
			Set(rhs);
			return *this;
		}

		//friend function
		//multiplication is associative a*b = b*a
		//lhs * rhs 
		//float a;
		//a * vector
		//to overcome the ambiguity of the vector being on the rhs rather than on the lhs
		friend inline Vec4 operator * (float lhs, const Vec4& rhs)
		{
			return rhs.Multiply(lhs);
		}

		inline const std::string toString() const {
			std::stringstream stringStream;
			stringStream << "Vec4[ " << x << ", " << y << ", " << z << ", " << w << "]";
			return stringStream.str();
		}
	};

	struct Vec2 {   /// Someone is going to want this someday, I hope not.
		float  x, y;	///  Structures are default public!
		void Vec2::Load(float _x, float _y) {
			x = _x;
			y = _y;
		}
		/// Here's a set of constructors
		Vec2(float s = float(0.0)) { Load(s, s); }
		Vec2(float _x, float _y) { Load(_x, _y); }
		/// In this context "const" means I promise not to modify anything v points to   
		Vec2(const Vec2& v) { Load(v.x, v.y); }


		/// Now we can use the Vec2 like an array but we'll need two overloads
		const float operator [] (int index) const {  /// This one is for reading the Vec2 as if where an array
			return *(&x + index);
		}
		float& operator [] (int index) { /// This one is for writing to the Vec2 as if where an array - check out the term lvalue
			return *(&x + index);
		}
	};

	struct Ray {
		Vec3 start;
		Vec3 dir;

		Ray(Vec3 _start, Vec3 _dir);

		// Where are we along the Ray? 
		// Calculate position = start + dir * t
		Vec3 currentPosition(float t);

	};

	struct Plane {
		Vec4 plane;

		// Set the member variables of the plane
		Plane(float _x, float _y, float _z, float _d);
		// Define the plane using three points that are on the plane
		Plane(const Vec3& v0, const Vec3& v1, const Vec3& v2);
		// Find the intersection point of a ray passing through this plane
		Vec3 intersectionPoint(Ray ray);


		inline const std::string toString() const {
			std::stringstream stringStream;
			stringStream << "Plane[ " << plane.x << ", " << plane.y << ", " << plane.z << ", " << plane.w << "]";
			return stringStream.str();
		}
	};
}
#endif //!VECTOR_H

