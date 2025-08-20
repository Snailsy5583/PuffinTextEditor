#include "glad/glad.h"
#include <iostream>

#include "Renderer.h"

namespace Engine
{


	const float Renderer::m_QuadVerts[] = {
		//     x  ,	      y  ,      z  ,	   u ,      v ,
		-0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.5f,	 -0.5f, 0.0f, 1.f, 1.f,
		-0.5f, 0.5f,  0.0f, 0.f, 0.f, 0.5f,	 0.5f,	0.0f, 1.f, 0.f,
		0.5f,  -0.5f, 0.0f, 1.f, 1.f, -0.5f, 0.5f,	0.0f, 0.f, 0.f};

	RendererObject Renderer::GenObject(unsigned int size, const float *vertices,
									   Engine::Shader *shader)
	{
		RendererObject obj = {0, 0, 0, shader};

		glGenVertexArrays(1, &obj.vao);
		glBindVertexArray(obj.vao);

		obj.bufferSize = size;

		glGenBuffers(1, &obj.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
		glBufferData(GL_ARRAY_BUFFER, obj.bufferSize, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
							  (void *) nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
							  (void *) (3 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		return obj;
	}

	RendererObject Renderer::GenQuad(glm::vec3 pos, const float sideLen,
									 Engine::Shader *shader)
	{
		return GenQuad(pos, glm::vec2(sideLen, sideLen), shader);
	}

	RendererObject Renderer::GenQuad(glm::vec3 pos, glm::vec2 size,
									 Engine::Shader *shader)
	{
		float verts[sizeof(m_QuadVerts) / sizeof(float)];

		for (int row = 0; row < 6; row++) {
			// x
			verts[(row * 5) + 0] =
				(m_QuadVerts[(row * 5) + 0] * size.x) + pos.x;
			// y
			verts[(row * 5) + 1] =
				(m_QuadVerts[(row * 5) + 1] * size.y) + pos.y;
			// z
			verts[(row * 5) + 2] = m_QuadVerts[(row * 5) + 0] + pos.z;

			for (int col = 3; col < 5; col++)
				verts[(row * 5) + col] = m_QuadVerts[(row * 5) + col];
		}

		return GenObject(sizeof(verts), verts, shader);
	}

	void Renderer::MoveQuad(RendererObject &obj, glm::vec3 newPos,
							float sideLen)
	{
		MoveQuad(obj, newPos, glm::vec2(sideLen, sideLen));
	}

	void Renderer::MoveQuad(RendererObject &obj, glm::vec3 newPos,
							glm::vec2 size)
	{
		float verts[sizeof(m_QuadVerts) / sizeof(float)];

		for (int row = 0; row < 6; row++) {
			// x
			verts[(row * 5) + 0] =
				(m_QuadVerts[(row * 5) + 0] * size.x) + newPos.x;
			// y
			verts[(row * 5) + 1] =
				(m_QuadVerts[(row * 5) + 1] * size.y) + newPos.y;
			// z
			verts[(row * 5) + 2] = m_QuadVerts[(row * 5) + 0] + newPos.z;

			for (int col = 3; col < 5; col++)
				verts[(row * 5) + col] = m_QuadVerts[(row * 5) + col];
		}

		// update vbo
		glBindVertexArray(obj.vao);
		glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
		glBufferData(GL_ARRAY_BUFFER, obj.bufferSize, verts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
							  (void *) nullptr);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
	}

	void Renderer::DeleteQuad(RendererObject &obj)
	{
		glDeleteBuffers(1, &obj.vbo);
		glDeleteVertexArrays(1, &obj.vao);
	}

	void Renderer::SubmitObject(const RendererObject &obj)
	{
		glBindVertexArray(obj.vao);
		glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
		obj.shader->Bind();

		glDrawArrays(GL_TRIANGLES, 0, obj.bufferSize);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		obj.shader->UnBind();
	}

	float *Renderer::GetVertices(RendererObject &obj)
	{
		glBindVertexArray(obj.vao);
		glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

		float *data = nullptr;
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, obj.bufferSize, data);

		return data;
	}
}	 // namespace Engine