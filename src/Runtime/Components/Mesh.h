#pragma once
#include "Runtime/Components/Transform.h"
//#include "Runtime/RenderCore/VertexBuffer.h"
//#include "Runtime/RenderCore/VertexArray.h"

#include <GL/glew.h>
#include <string>
#include <vector>

#define NUM_BUFFERS 4

namespace pine {

	/*struct Vertex
	{
	public:
		Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
		{
			m_Pos = pos;
			m_TexCoord = texCoord;
			m_Normal = normal;
		}

		glm::vec3* GetPos() { return &m_Pos; }
		glm::vec2* GetTexCoord() { return &m_TexCoord; }
		glm::vec3* GetNormal() { return &m_Normal; }

	private:
		glm::vec3 m_Pos;
		glm::vec2 m_TexCoord;
		glm::vec3 m_Normal;
	};*/

	enum MeshBufferPositions
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB
	};

	class OpenGLRenderer;

	class Mesh {
		friend OpenGLRenderer;
	public:
		std::vector<glm::vec3>			m_positions;
		std::vector<glm::vec2>			m_texCoords;
		std::vector<glm::vec3>			m_normals;
		std::vector<unsigned int>		m_indices;

		Mesh();
		//Mesh(const std::string& fileName);
		Mesh(std::vector<glm::vec3>& positions, std::vector<unsigned int>& indices);
		Mesh(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uv, std::vector<unsigned int>& indices);	
		Mesh(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uv, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices);

		void InitMesh();
		//void Draw();
		/*bool RayIntersectsTriangle(glm::vec3 rayOrigin,
			glm::vec3 rayVector,
			std::vector<unsigned int> indeces,
			glm::vec3& outIntersectionPoint,
			const Transform& transform);
		std::vector<glm::vec3> GetMouseIntersections(glm::vec3 rayOrigin, glm::vec3 rayVector, std::vector<int>& intersectionIndeces, const Transform& transform);
		glm::vec2 CalculateTexturePosition(glm::vec3 intersection, int faceIndex, Transform transform);
		void Barycentric(glm::vec2 p, glm::vec2 a, glm::vec2 b, glm::vec2 c, float& u, float& v, float& w);
		glm::vec2 BarycentricToCartesian(glm::vec2 a, glm::vec2 b, glm::vec2 c, float u, float v, float w);*/

		virtual ~Mesh();
	protected:

	private:
		bool _buffered = false;
		unsigned int	_VA;	//unused for now
		unsigned int	_VB;	//unused for now
		unsigned int	_EB;	//unused for now

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