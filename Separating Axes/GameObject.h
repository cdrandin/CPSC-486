#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "Vector3.h"
#include "Square.h"
#include "Ray3.h"
#include "Polygon.h"

namespace cpsc486
{
	class GameObject
	{
	private:
		Vector3 _position, _velocity, _color;
		cpsc486::Square _square;
		GLfloat z_pos;

	public:
		GameObject(void);
		~GameObject(void);

		// Square
		void setSquare(const Square& s);
		void setSquare(const Square& s, const Vector3& position);

		Square getSquare();
		
		// Position
		const Vector3& getPosition() const;
		void setPosition(const Vector3& v);

		// Vector
		const Vector3& getVelocity() const;
		void setVelocity(const Vector3& v);

		// Color
		const Vector3& getColor() const;
		void setColor(const Vector3& v);

		void move();

		void drawPosition();
	};
}