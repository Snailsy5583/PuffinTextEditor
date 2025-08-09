//
// Created by r6awe on 6/6/2023.
//

#pragma once

#include <functional>
#include <memory>

#include "Component.h"
#include "Renderer.h"

namespace Engine {

    class GameObject {
    public:
        GameObject(RendererObject rendererObject, Vec3 pos, float rot);

        void AddComponent(std::unique_ptr<Component> component);

        virtual void Move(Vec3 deltaPos, float deltaRot);

        virtual void Update(float deltaTime);

        void Render();

        void SetUpdateCallback(std::function<void(float, GameObject*)>
            callback);

    public:
        inline RendererObject& GetRendererObject()
        { return m_RendererObject; }
        inline const Vec3& GetPosition() const { return m_Position; }
        inline const float& GetRotation() const { return m_Rotation; }
        inline float GetScale   () const { return m_Scale;    }

        template<class T> T* TryGetComponent() {
            for (auto &comp : m_Components) {
                T *specifiedComp = dynamic_cast<T*>(comp.get());
                if (specifiedComp)
                    return specifiedComp;
            }
            return nullptr;
        }

    protected:
        RendererObject m_RendererObject;

        std::vector<std::unique_ptr<Component>> m_Components;

        std::function<void(float, GameObject*)> m_UpdateCallback;

        Vec3 m_Position;
        float m_Rotation;
        float m_Scale = 1;
    };

    class Quad : public GameObject {
    public:
        Quad(float sideLength, Vec3 pos, float rot);

        float GetSideLength() const { return m_SideLength; }

    protected:
        float m_SideLength;
    };

    class Circle : public GameObject {
    public:
        Circle(float radius, Vec3 pos, float rot);

        float GetRadius() const { return m_Radius; }

    private:
        float m_Radius;
    };

} // Engine
