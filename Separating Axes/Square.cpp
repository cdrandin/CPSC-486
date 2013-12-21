#include "Square.h"

/*
void perp(GLfloat* out, GLfloat* in)
{
	out[0] = in[1];
	out[1] = -in[0];
}
*/

Vector3 perp(const Vector3* in)
{
	Vector3 *out = new Vector3(in->y(), -in->x(), in->z());
	
	return *out;
}

namespace cpsc486
{
	Square::Square(void)
	{
	}
	
	Square::Square(const Vector3& corner, const Vector3& extent, const Vector3& position):z_pos(-0.5f)
	{
		
		Vector3 *square = new Vector3[4];
		Vector3 ext = Vector3(extent - corner);

		// vertices of square
		square[1] = Vector3(corner.x(), corner.y(), z_pos)  + position;
		square[2] = Vector3(corner.x() + ext.x(), corner.y(), z_pos) + position;
		square[3] = Vector3(corner.x() + ext.x(), corner.y() + ext.y(), z_pos) + position;
		square[0] = Vector3(corner.x() , corner.y() + ext.y(), z_pos) + position;
		
		// construct object
		_polygon = Polygon(4, square);

		// create edge normals
		for(int i=0;i<4;++i)
		{
			int next = (i+1)%4;

			Vector3 *e = new Vector3(square[next] - square[i]);
			e->z(z_pos);
			e->Normalize();

			_edge_normals.push_back(new Ray3(square[i], perp(e)));
		}

		delete[] square;
		square = NULL;
	}

	Square::~Square(void)
	{
	}

	cpsc486::Polygon Square::getPolygon()
	{
		return _polygon;
	}

	std::vector<Ray3*> cpsc486::Square::getEdgeNormals()
	{
		return _edge_normals;
	}

	std::vector<Vector3*> cpsc486::Square::getVertices()
	{
		return _polygon.getVertices();
	}

	void cpsc486::Square::setEdgeNormals(const std::vector<Ray3*>& ver)
	{
		for(int i=0;i<(int)_edge_normals.size();++i)
			*_edge_normals[i] = *ver[i];
	}
	
	void cpsc486::Square::updateEdgeNormals(const Vector3& velocity)
	{
		Vector3 vel = Vector3(velocity.x(), velocity.y(), 0.0f);
		std::vector<Ray3*> ray;

		Vector3 *newOrigin, *newDirection;

		for(int i=0;i<(int)_edge_normals.size();++i)
		{
			newOrigin = new Vector3(_edge_normals.at(i)->getOrigin() + vel);
			newDirection = new Vector3(_edge_normals.at(i)->getDirection() /*+ vel*/);

			ray.push_back(new Ray3(*newOrigin, *newDirection));
		}

		delete newOrigin;
		delete newDirection;

		setEdgeNormals(ray);
	}
	
	void cpsc486::Square::debugEdge()
	{
		// Draw edges of square
		// Color: RED
		glLineWidth(1.0);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		for(int i=0;i<4;++i)
		{
			int next = (i+1)%4;
			glVertex3dv(_polygon.getVertices().at(next)->constPtr());
			glVertex3dv(_polygon.getVertices().at(i)->constPtr());
		}
		glEnd();

		// Draw vertices of square
		// Color: BLUE
		glPointSize(5.0);
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_POINTS);
		for(int i=0;i<(int)getPolygon().getVertices().size();++i)
		{
			glVertex3dv(getPolygon().getVertices().at(i)->constPtr());
		}
		glEnd();
	}

	void cpsc486::Square::debugEdgeNormals()
	{
		// Draw edge normals from square
		// Color: RED
		glLineWidth(1.5);
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		for(std::vector<Ray3*>::iterator it = _edge_normals.begin(); it != _edge_normals.end(); ++it)
		{
			glVertex3dv((*it)->getOrigin().constPtr());
			glVertex3dv((*it)->getDirection().constPtr());
		}
		glEnd();

		// Draw the origion of the edge normal
		// Color: GREEN
		glPointSize(5.0);
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POINTS);
		for(int i = 0; i<(int)getEdgeNormals().size();++i)
		{
			glVertex3dv(getEdgeNormals().at(i)->getOrigin().constPtr());
		}
		glEnd();

		// Draw the direction of the edge normal
		// Color: WHITE
		glPointSize(5.0);
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_POINTS);
		for(int i = 0; i<(int)getEdgeNormals().size();++i)
		{
			glVertex3dv(getEdgeNormals().at(i)->getDirection().constPtr());
		}
		glEnd();
	}
}