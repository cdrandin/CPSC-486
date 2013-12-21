#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/GL.h>

#include <vector>
#include "Vector3.h"

using std::vector;

namespace cpsc486
{
	// Class works assuming right-hand-rule for constructing geometric objects
	class Polygon
	{
	private:
		int num_vertices;
		std::vector<Vector3*> vertices, edges;

	public:
		Polygon(void);
		Polygon(const int& numVertices, const Vector3* v);
		
		~Polygon(void);

		const int& getNumVertices() const;

		std::vector<Vector3*> getVertices();
		void setVertices(const std::vector<Vector3*>& ver);

		std::vector<Vector3*> getEdges();
		void setEdges(const std::vector<Vector3*>& ver);

		void drawImmediate(const Vector3& color);

		void updateVertices(const Vector3& velocity);
	};
}