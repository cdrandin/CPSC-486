#include "Ray3.h"

namespace cpsc486
{
	Vector3& Ray3::PointAt(const GLfloat& t)
	{
		return _origin + (_direction * t);
	}

	Vector3& Ray3::getDirection()
	{
		return _direction;
	}

	Vector3& Ray3::getOrigin()
	{
		return _origin;
	}

	void Ray3::setDirection(const Vector3& v)
	{
		_direction += v;
	}

	void Ray3::setOrigin(const Vector3& v)
	{
		_origin += v;
	}
}