#pragma once 
#include "Runtime/Components/MeshData.h"

//#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
//#include <chrono>

namespace pine {

	MeshData::MeshData()
	{
		
	}

	/*Mesh::Mesh(const std::string& fileName)
	{
		model = OBJModel(fileName).ToIndexedModel();

		Mesh::InitMesh(*this->model);
	}*/

	MeshData::MeshData(std::vector<vec3>& positions)
	{
		this->m_Positions = positions;
	}

	MeshData::MeshData(std::vector<vec3>& positions, std::vector<unsigned int>& indices)
	{
		this->m_Positions = positions;
		this->m_Indices = indices;
	}

	MeshData::MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector<vec3>& normals)
	{
		this->m_Positions = positions;
		this->m_TexCoords = uv;
		this->m_Normals = normals;
	}

	MeshData::MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector<unsigned int>& indices)
	{
		this->m_Positions = positions;
		this->m_TexCoords = uv;
		this->m_Indices = indices;
	}

	MeshData::MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector<vec3>& normals, std::vector<unsigned int>& indices)
	{
		this->m_Positions = positions;
		this->m_TexCoords = uv;
		this->m_Normals = normals;
		this->m_Indices = indices;
	}

	/*Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
	{
		IndexedModel* model = new IndexedModel();

		for (unsigned int i = 0; i < numVertices; i++)
		{
			model->positions.push_back(*vertices[i].GetPos());
			model->texCoords.push_back(*vertices[i].GetTexCoord());
			model->normals.push_back(*vertices[i].GetNormal());
		}

		for (unsigned int i = 0; i < numIndices; i++)
			model->indices.push_back(indices[i]);
		this->model = model;
		InitMesh(*this->model);
	}*/

	MeshData::~MeshData()
	{
		// TODO: delete all buffers
		glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
		glDeleteVertexArrays(1, &m_vertexArrayObject);
	}

	//void Mesh::Draw()
	//{
	//	if (!m_Buffered) InitMesh();

	//	glBindVertexArray(m_vertexArrayObject);

	//	//glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	//	glDrawElementsBaseVertex(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0, 0);

	//	glBindVertexArray(0);
	//}


	//bool Mesh::RayIntersectsTriangle(vec3 rayOrigin,
	//	vec3 rayVector,
	//	std::vector<unsigned int> indeces,
	//	vec3& outIntersectionPoint,
	//	const Transform& transform)
	//{
	//	const float EPSILON = 0.0000001;

	//	mat4 model = transform.GetModel();

	//	vec4 v0(this->model->positions[indeces[0]].x, this->model->positions[indeces[0]].y, this->model->positions[indeces[0]].z, 1);
	//	vec4 v1(this->model->positions[indeces[1]].x, this->model->positions[indeces[1]].y, this->model->positions[indeces[1]].z, 1);
	//	vec4 v2(this->model->positions[indeces[2]].x, this->model->positions[indeces[2]].y, this->model->positions[indeces[2]].z, 1);
	//	v0 = model * v0;
	//	v1 = model * v1;
	//	v2 = model * v2;
	//	vec3 vertex0(v0.x, v0.y, v0.z);
	//	vec3 vertex1(v1.x, v1.y, v1.z);
	//	vec3 vertex2(v2.x, v2.y, v2.z);

	//	vec3 edge1, edge2, h, s, q;
	//	float a, f, u, v;
	//	edge1 = vertex1 - vertex0;
	//	edge2 = vertex2 - vertex0;
	//	h = cross(rayVector, edge2);
	//	a = dot(edge1, h);

	//	if (a > -EPSILON && a < EPSILON)
	//		return false;    // This ray is parallel to this triangle.
	//	f = 1.0 / a;
	//	s = rayOrigin - vertex0;
	//	u = f * dot(s, h);

	//	if (u < 0.0 || u > 1.0)
	//		return false;
	//	q = cross(s, edge1);
	//	v = f * dot(rayVector, q);
	//	if (v < 0.0 || u + v > 1.0)
	//		return false;
	//	// At this stage we can compute t to find out where the intersection point is on the line.
	//	float t = f * dot(edge2, q);
	//	if (t > EPSILON) // ray intersection
	//	{
	//		outIntersectionPoint = rayOrigin + rayVector * t;
	//		return true;
	//	}
	//	else // This means that there is a line intersection but not a ray intersection.
	//		return false;
	//}

	//std::vector<vec3> Mesh::GetMouseIntersections(vec3 rayOrigin, vec3 rayVector, std::vector<int>& intersectionIndeces, const Transform& transform)
	//{
	//	std::vector<vec3> intersections;

	//	int i = 0;
	//	do {
	//		vec3 intersection;
	//		std::vector<unsigned int> indeces;
	//		indeces.push_back(model->indices[i]);
	//		indeces.push_back(model->indices[i + 1]);
	//		indeces.push_back(model->indices[i + 2]);

	//		//auto start = std::chrono::high_resolution_clock::now();
	//		if (RayIntersectsTriangle(rayOrigin,
	//			rayVector,
	//			indeces,
	//			intersection,
	//			transform))
	//		{
	//			intersections.push_back(intersection);
	//			intersectionIndeces.push_back(i);
	//		}

	//		//std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);

	//		i += 3;
	//	} while (i < model->indices.size());

	//	return intersections;
	//}

	//vec2 Mesh::CalculateTexturePosition(vec3 intersection, int faceIndex, Transform transform)
	//{
	//	//calculate crosssection
	//	mat4 m = transform.GetModel();
	//	vec4 v0(model->positions[model->indices[faceIndex]].x, model->positions[model->indices[faceIndex]].y, model->positions[model->indices[faceIndex]].z, 1);
	//	vec4 v1(model->positions[model->indices[faceIndex + 1]].x, model->positions[model->indices[faceIndex + 1]].y, model->positions[model->indices[faceIndex + 1]].z, 1);
	//	vec4 v2(model->positions[model->indices[faceIndex + 2]].x, model->positions[model->indices[faceIndex + 2]].y, model->positions[model->indices[faceIndex + 2]].z, 1);
	//	v0 = m * v0;
	//	v1 = m * v1;
	//	v2 = m * v2;
	//	vec3 a(v0.x, v0.y, v0.z);
	//	vec3 b(v1.x, v1.y, v1.z);
	//	vec3 c(v2.x, v2.y, v2.z);
	//	/*
	//	vec3 a = this->model->positions[model->indices[faceIndex]];
	//	vec3 b = this->model->positions[model->indices[faceIndex+1]];
	//	vec3 c = this->model->positions[model->indices[faceIndex+2]];*/
	//	vec3 cross = cross(b - a, c - a);

	//	//do the projection on one of the axis
	//	vec2 a2, b2, c2, p2;

	//	if (abs(cross.x) >= abs(cross.y) && abs(cross.x) >= abs(cross.z)) {
	//		a2 = vec2(a.y, a.z);
	//		b2 = vec2(b.y, b.z);
	//		c2 = vec2(c.y, c.z);
	//		p2 = vec2(intersection.y, intersection.z);
	//	}
	//	else if (abs(cross.y) >= abs(cross.x) && abs(cross.y) >= abs(cross.z)) {
	//		a2 = vec2(a.x, a.z);
	//		b2 = vec2(b.x, b.z);
	//		c2 = vec2(c.x, c.z);
	//		p2 = vec2(intersection.x, intersection.z);
	//	}
	//	else {
	//		a2 = vec2(a.x, a.y);
	//		b2 = vec2(b.x, b.y);
	//		c2 = vec2(c.x, c.y);
	//		p2 = vec2(intersection.x, intersection.y);
	//	}

	//	//get barycentric coordinates
	//	float u, v, w;
	//	Barycentric(p2, a2, b2, c2, u, v, w);

	//	vec2 tex_coord_a = model->texCoords[model->indices[faceIndex]];
	//	vec2 tex_coord_b = model->texCoords[model->indices[faceIndex + 1]];
	//	vec2 tex_coord_c = model->texCoords[model->indices[faceIndex + 2]];

	//	vec2 hover_tex_coords = BarycentricToCartesian(tex_coord_a, tex_coord_b, tex_coord_c, u, v, w);

	//	//std::cout << "x: " << hover_tex_coords.x << " || y: " << hover_tex_coords.y << " [" << faceIndex << "]" << std::endl;

	//	return hover_tex_coords;
	//}

	//void Mesh::Barycentric(vec2 p, vec2 a, vec2 b, vec2 c, float& u, float& v, float& w)
	//{
	//	vec2 v0 = b - a, v1 = c - a, v2 = p - a;
	//	float den = v0.x * v1.y - v1.x * v0.y;
	//	v = (v2.x * v1.y - v1.x * v2.y) / den;
	//	w = (v0.x * v2.y - v2.x * v0.y) / den;
	//	u = 1.0f - v - w;
	//}

	//vec2 Mesh::BarycentricToCartesian(vec2 a, vec2 b, vec2 c, float u, float v, float w)
	//{
	//	vec2 p;

	//	p.x = a.x * u + b.x * v + c.x * w;
	//	p.y = a.y * u + b.y * v + c.y * w;

	//	return p;
	//}

}