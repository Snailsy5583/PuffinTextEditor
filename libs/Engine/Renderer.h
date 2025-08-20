#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

namespace Engine
{

	struct RendererObject {
		unsigned int vao {};
		unsigned int vbo {};
		unsigned int bufferSize {};
		Shader *shader;	   // doesn't take ownership of shader
	};

	class Renderer
	{
	public:
		static RendererObject GenObject(unsigned int size,
										const float *Vertices, Shader *shader);

		static RendererObject GenQuad(glm::vec3 pos, float sideLen,
									  Shader *shader);
		static RendererObject GenQuad(glm::vec3 pos, glm::vec2 size,
									  Shader *shader);

		static void MoveQuad(RendererObject &obj, glm::vec3 newPos,
							 float sideLen);
		static void MoveQuad(RendererObject &obj, glm::vec3 newPos,
							 glm::vec2 size);

		static void DeleteQuad(RendererObject &object);

		static void SubmitObject(const RendererObject &obj);

		static float *GetVertices(RendererObject &obj);

		// utility function
		static inline float *hsv2rgb(float in[4])
		{
			in[0] *= 360;

			float hh, p, q, t, ff;
			long i;
			static float out[4];

			if (in[1] <= 0.0) {	   // < is bogus, just shuts up warnings
				out[0] = in[2];
				out[1] = in[2];
				out[2] = in[2];
				out[3] = in[3];
				return out;
			}
			hh = in[0];
			if (hh >= 360.0) hh = 0.0f;
			hh /= 60.0f;
			i = (long) hh;
			ff = hh - i;
			p = in[2] * (1.0f - in[1]);
			q = in[2] * (1.0f - (in[1] * ff));
			t = in[2] * (1.0f - (in[1] * (1.0f - ff)));

			switch (i) {
			case 0:
				out[0] = in[2];
				out[1] = t;
				out[2] = p;
				break;
			case 1:
				out[0] = q;
				out[1] = in[2];
				out[2] = p;
				break;
			case 2:
				out[0] = p;
				out[1] = in[2];
				out[2] = t;
				break;

			case 3:
				out[0] = p;
				out[1] = q;
				out[2] = in[2];
				break;
			case 4:
				out[0] = t;
				out[1] = p;
				out[2] = in[2];
				break;
			case 5:
			default:
				out[0] = in[2];
				out[1] = p;
				out[2] = q;
				break;
			}
			out[3] = in[3];
			return out;
		}

	private:
		const static float m_QuadVerts[];
	};


}	 // namespace Engine