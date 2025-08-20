#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Engine
{

	class Texture;

	class Shader
	{
	public:
		Shader(const char *vertShaderSource = nullptr,
			   const char *fragShaderSource = nullptr);
		~Shader();

		static Shader Compile(const char *vertPath, const char *fragPath);

		void SetUniform(int loc, int value) const;
		void SetUniform(int loc, bool value) const;
		void SetUniform(int loc, float value) const;
		void SetUniform(const char *name, int value) const;
		void SetUniform(const char *name, bool value) const;
		void SetUniform(const char *name, float value) const;

		void SetUniformVec(int loc, glm::vec2 value) const;
		void SetUniformVec(int loc, glm::vec3 value) const;
		void SetUniformVec(int loc, glm::vec4 value) const;

		void SetUniformVec(const char *name, glm::vec2 value) const;
		void SetUniformVec(const char *name, glm::vec3 value) const;
		void SetUniformVec(const char *name, glm::vec4 value) const;

		void SetUniformMat4(int loc, glm::mat4 value) const;
		void SetUniformMat4(const char *name, glm::mat4 value) const;

		int GetUniformLocation(const char *name) const;

		int GetAttribLocation(const char *name) const;

		void Bind() const;

		void UnBind() const;

		void AttachTexture(Texture tex);

		void Destroy();

		static std::vector<Shader *> p_ShaderList;

	private:
		static std::string ReadFile(const char *path);

		static bool CheckErrors(unsigned int shader);

	private:
		unsigned int m_ShaderProgramID;

		int m_ShaderIndex;

		std::vector<Texture> m_Textures;
	};

	class Texture
	{
	public:
		Texture() = default;
		Texture(const char *path);
		Texture(int width, int height, int channel,
				const unsigned char *buffer);

		void Bind() const;

		void UnBind() const;

		void Destroy();

	private:
		void InitFromPath(const char *path);
		void InitFromBuffer(int width, int height, int channel,
							const unsigned char *buffer);

	private:
		unsigned int m_TextureID;
	};

}	 // namespace Engine
