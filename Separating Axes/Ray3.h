#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#include "Vector3.h"


namespace cpsc486
{
	class Ray3
	{
	private:
		Vector3 _origin, _direction;
		GLfloat z_pos;

	public:
		Ray3(void):	z_pos(-0.5f), _origin(0.0,0.0,0.0),_direction(0.0,0.0,0.0){}

		Ray3(const GLfloat *origin,const GLfloat *direction):
		z_pos(-0.5f), 
		_origin(origin[0], origin[1],z_pos),
		_direction(direction[0], direction[1], z_pos){}

		Ray3(const Vector3& origin, const Vector3& direction):
		z_pos(-0.5f),
		_origin(origin),
		_direction(direction)
		{
			_origin.z(z_pos);
			_direction.z(z_pos);
		}

		~Ray3(void){}

		Vector3& PointAt(const GLfloat& t);

		Vector3& getDirection();
		Vector3& getOrigin();

		void setDirection(const Vector3& v);
		void setOrigin(const Vector3& v);
	};
}