#include "Polygon.h"

cpsc486::Polygon::Polygon(void)
{
}

cpsc486::Polygon::Polygon(const int& numVertices, const Vector3* v):
num_vertices(numVertices)
{
	for(int i=0;i<num_vertices;++i)
	{
		vertices.push_back(new Vector3(v[i]));
	}

	// Create the edges
	edges.push_back(new Vector3(*vertices[1] - *vertices[0]));
	edges.push_back(new Vector3(*vertices[2] - *vertices[1]));
	edges.push_back(new Vector3(*vertices[3] - *vertices[2]));
	edges.push_back(new Vector3(*vertices[0] - *vertices[3]));
}

cpsc486::Polygon::~Polygon(void)
{
}

const int& cpsc486::Polygon::getNumVertices() const 
{
	return num_vertices;
}

std::vector<Vector3*> cpsc486::Polygon::getVertices()
{
	return vertices;
}

void cpsc486::Polygon::setVertices(const std::vector<Vector3*>& ver)
{
	for(int i=0;i<num_vertices;++i)
	{
		*vertices[i] = *ver[i];
	}
}

std::vector<Vector3*> cpsc486::Polygon::getEdges()
{
	return edges;
}
		
void cpsc486::Polygon::setEdges(const std::vector<Vector3*>& ver)
{
	for(int i=0;i<num_vertices;++i)
	{
		*edges[i] = *ver[i];
	}
}


void cpsc486::Polygon::drawImmediate(const Vector3& color)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	Vector3* c = new Vector3(color);
	glColor3dv(c->constPtr());
	for(std::vector<Vector3*>::iterator it = vertices.begin();it != vertices.end();++it)
	{
		glVertex3dv((*it)->constPtr());
	}
	glEnd();
	glPushMatrix();
}

void cpsc486::Polygon::updateVertices(const Vector3& velocity)
{
	Vector3 vel = Vector3(velocity.x(), velocity.y(), 0.0f);
	std::vector<Vector3*> dataV, dataE;
	
	for(int i=0;i<num_vertices;++i)
	{
		dataV.push_back(new Vector3(*(vertices.at(i)) + vel));
		dataE.push_back(new Vector3(*(edges.at(i)) + vel));
	}

	setVertices(dataV);
	setEdges(dataE);
} 
 