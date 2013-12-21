#include "GameObject.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace cpsc486
{
	GameObject::GameObject(void): z_pos(-0.5f), _position(0.0, 0.0, z_pos), _velocity()
	{
	}

	GameObject::~GameObject(void)
	{
	}

	void GameObject::setSquare(const Square& s)
	{
		_square = Square(s);
	}

	Square GameObject::getSquare()
	{
		return _square;
	}

	const Vector3& GameObject::getPosition() const
	{
		return _position;
	}

	void GameObject::setPosition(const Vector3& v)
	{
		_position = v;

		std::vector<Vector3*> data = _square.getPolygon().getVertices();
		for(int i=0;i<(int)data.size();++i)
			*data.at(i) += v;

		_square.getPolygon().setVertices(data);
	}

	const Vector3& GameObject::getVelocity() const
	{
		return _velocity;
	}

	void GameObject::setVelocity(const Vector3& v)
	{
		_velocity = v;
		_velocity.z(z_pos);
	}

	const Vector3& GameObject::getColor() const
	{
		return _color;
	}
	void GameObject::setColor(const Vector3& v)
	{
		_color = v;
	}

	void GameObject::move()
	{
		_position += _velocity;
		_position.z(z_pos); // restrict onto one z-plane

		_square.getPolygon().updateVertices(_velocity);
		_square.updateEdgeNormals(_velocity);
	}

	void GameObject::drawPosition()
	{
		glPointSize(5.0);
		glColor3f(0.8,0.196078,0.6);
		glBegin(GL_POINTS);
			glVertex3dv(_position.constPtr());
		glEnd();
	}
}
