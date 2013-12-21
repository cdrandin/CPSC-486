#pragma once

#include <vector>
#include "Ray3.h"
#include "Polygon.h"

using std::vector;

namespace cpsc486
{
	class Square
	{
	private:
		vector<Ray3*> _edge_normals;
		cpsc486::Polygon _polygon;

		float z_pos;

	public:
		Square(void);
		Square(const Vector3& corner, const Vector3& extent, const Vector3& position);
		~Square(void);

		cpsc486::Polygon getPolygon();
		std::vector<Ray3*> getEdgeNormals();
		std::vector<Vector3*> getVertices();

		void setEdgeNormals(const std::vector<Ray3*>& ver);
		void updateEdgeNormals(const Vector3& velocity);

		void debugEdge();
		void debugEdgeNormals();
	};
}