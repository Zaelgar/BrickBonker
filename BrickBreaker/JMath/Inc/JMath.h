// Written by Jaidon van Herwaarden

#include "Common.h"
#include "Constants.h"

// Shapes
#include "Primitive2D.h"

// Vectors
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

// Matrices
#include "Matrix4.h"
#include "Matrix3.h"

// Quaternion
#include "Quaternion.h"

// Random
#include "Random.h"

namespace JMath
{
	bool PointInCircle(const JMath::Vector2& point, const JMath::Circle& circle);
	bool Intersect(const JMath::Circle& c, const JMath::LineSegment& l, JMath::Vector2* closestPoint);
	bool Intersect(const LineSegment& a, const LineSegment& b);
	bool Intersect(JMath::Vector2 A, JMath::Vector2 B, JMath::Vector2 C, JMath::Vector2 D, float& dist, JMath::Vector2& point);
	bool Intersect(LineSegment a, LineSegment b, float& dist, Vector2& point);

	Matrix4 RotationQuaternionToMatrix(const Quaternion& q);

	Matrix4 CreateTransformMatrix(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

	void RandomPointsInRectangle(std::vector<JMath::Vector2>& points, JMath::Rect areaBounds, int numberOfPoints);
};