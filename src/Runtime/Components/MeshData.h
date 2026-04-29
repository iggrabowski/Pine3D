#pragma once
#include "Runtime/Components/Transform.h"
//#include "Runtime/RenderCore/VertexBuffer.h"
//#include "Runtime/RenderCore/VertexArray.h"

#include <GL/glew.h>
#include <string>
#include <vector>

#include "Material.h"

#define NUM_BUFFERS 6
#define INVALID_MATERIAL 0xFFFFFFFF
#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2
#define TANGENT_LOCATION 3
#define BITANGENT_LOCATION 4

namespace pine {

	/*struct Vertex
	{
	public:
		Vertex(const vec3& pos, const vec2& texCoord, const vec3& normal)
		{
			m_Pos = pos;
			m_TexCoord = texCoord;
			m_Normal = normal;
		}

		vec3* GetPos() { return &m_Pos; }
		vec2* GetTexCoord() { return &m_TexCoord; }
		vec3* GetNormal() { return &m_Normal; }

	private:
		vec3 m_Pos;
		vec2 m_TexCoord;
		vec3 m_Normal;
	};*/

	enum MeshBufferPositions
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		TANGENT_VB,
		BITANGENT_VB,
		INDEX_VB,
		POSITIONS_COUNT
	};

	struct MeshBufferDataInfo
	{
		MeshBufferPositions position;
		std::string attributeName;
	};

	inline MeshBufferDataInfo meshBufferDataTypes[POSITIONS_COUNT] = {
		{ POSITION_VB, "position" },
		{ TEXCOORD_VB, "texCoord" },
		{ NORMAL_VB, "normal" },
		{ TANGENT_VB, "tangent" },
		{ BITANGENT_VB, "bitangent" },
		{ INDEX_VB, "" } // No attribute for index buffer
	};

	class OpenGLRenderer;


	class MeshData {
		friend OpenGLRenderer;
	public:
		std::vector<vec3>			m_Positions;
		std::vector<vec2>			m_TexCoords;
		std::vector<vec3>			m_Normals;
		// Tangents for normal mapping
		std::vector<vec3>			m_Tangents;
		std::vector<vec3>			m_Bitangents;
		std::vector<unsigned int>		m_Indices;

		MeshData();
		//Mesh(const std::string& fileName);
		MeshData(std::vector<vec3>& positions);
		MeshData(std::vector<vec3>& positions, std::vector<unsigned int>& indices);
		MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector<unsigned int>& indices);	
		MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector <vec3>& normals);
		MeshData(std::vector<vec3>& positions, std::vector<vec2>& uv, std::vector<vec3>& normals, std::vector<unsigned int>& indices);

		void InitMesh();
		//void Draw();
		/*bool RayIntersectsTriangle(vec3 rayOrigin,
			vec3 rayVector,
			std::vector<unsigned int> indeces,
			vec3& outIntersectionPoint,
			const Transform& transform);
		std::vector<vec3> GetMouseIntersections(vec3 rayOrigin, vec3 rayVector, std::vector<int>& intersectionIndeces, const Transform& transform);
		vec2 CalculateTexturePosition(vec3 intersection, int faceIndex, Transform transform);
		void Barycentric(vec2 p, vec2 a, vec2 b, vec2 c, float& u, float& v, float& w);
		vec2 BarycentricToCartesian(vec2 a, vec2 b, vec2 c, float u, float v, float w);*/

		virtual ~MeshData();
	protected:

	private:
		bool _buffered = false;
		unsigned int	_VA;
		unsigned int	_VB;
		unsigned int	_EB;

		//static const unsigned int NUM_BUFFERS = 4;
		//void operator=(const Mesh& mesh) {}
		//Mesh(const Mesh& mesh) {}

		//void InitMesh(const IndexedModel& model);

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		//const IndexedModel* model;
		//unsigned int m_numIndices;
	};

}