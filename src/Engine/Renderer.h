#pragma once


#include <cmath>
#include <sstream>
#include <cmath>
#include "Shader.h"

namespace Engine {

    struct Vec3 {
        float x=0, y=0, z=0;

        Vec3 operator-() const {
            return {-x, -y, -z};
        }

        Vec3 operator+(const Vec3 other) const {
            return {x+other.x, y+other.y, z+other.z};
        }
        Vec3 operator-(const Vec3 other) const {
            return {x-other.x, y-other.y, z-other.z};
        }
        Vec3 operator*(const float scalar) const {
            return {scalar*x, scalar*y, scalar*z};
        }
        friend Vec3 operator*(const float scalar, const Vec3 vec) {
            return {scalar*vec.x, scalar*vec.y, scalar*vec.z};
        }
        Vec3 operator/(const float scalar) const {
            return {x/scalar, y/scalar, z/scalar};
        }

        void operator+=(Vec3 other) {
            x += other.x;
            y += other.y;
            z += other.z;
        }
        void operator-=(const Vec3 other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }

        bool operator!=(const Vec3 other) const {
            if (x != other.x || y != other.y || z != other.z)
                return true;
            else return false;
        }
        bool operator==(const Vec3 other) {
            return !(*this != other);
        }

        float operator[](int offset) const {
            switch (offset) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    return (float) -INT_MAX;
            }
        }

        float* toArr() {
            return reinterpret_cast<float *>(this);
        }

        std::string toString() const {
            std::stringstream ss;
            ss << "(" << x << ", " << y << ", " << z << ")";
            return ss.str();
        }

        float magnitude() const {
            return std::sqrt(x*x + y*y + z*z);
        }

        Vec3 normalized() const {
            return (*this)/magnitude();
        }
    };

    struct RendererObject {
        unsigned int vao{};
        unsigned int vbo{};
        unsigned int bufferSize{};
        Shader shader;
    };

    class Renderer {
    public:
        static RendererObject GenObject(unsigned int size,
                                        const float *Vertices,
                                        const char *vertShaderPath,
                                        const char *fragShaderPath);

        static RendererObject GenQuad(const float pos[3],
                                      const float sideLen,
                                      const char *vertShaderPath,
                                      const char *fragShaderPath);

        static void MoveQuad(RendererObject &obj, Vec3 newPos, float sideLen);

        static void DeleteQuad(RendererObject &object);

        static void SubmitObject(const RendererObject& obj);

        static float* GetVertices(RendererObject &obj);

        // utility function
        static inline float* hsv2rgb(float in[4])
        {
            in[0] *= 360;

            float        hh, p, q, t, ff;
            long         i;
            static float out[4];

            if(in[1] <= 0.0) {       // < is bogus, just shuts up warnings
                out[0] = in[2];
                out[1] = in[2];
                out[2] = in[2];
                out[3] = in[3];
                return out;
            }
            hh = in[0];
            if(hh >= 360.0) hh = 0.0f;
            hh /= 60.0f;
            i = (long)hh;
            ff = hh - i;
            p = in[2] * (1.0f -  in[1]);
            q = in[2] * (1.0f - (in[1] * ff));
            t = in[2] * (1.0f - (in[1] * (1.0f - ff)));

            switch(i) {
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


}