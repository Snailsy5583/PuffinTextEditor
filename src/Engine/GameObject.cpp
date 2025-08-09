#include <memory>
#include <utility>
#include "GameObject.h"

namespace Engine {

    GameObject::GameObject(RendererObject rendererObject, Vec3 pos, float rot)
        : m_RendererObject(std::move(rendererObject)), m_Position(pos), m_Rotation(rot)
    {}

    void GameObject::Move(Vec3 deltaPos, float deltaRot) {
        m_Position += deltaPos;
        m_Rotation += deltaRot;
    }

    void GameObject::Update(float deltaTime) {
        for (std::unique_ptr<Component> &comp : m_Components)
        {
            comp->UpdateComponent(deltaTime);
        }

        if (m_UpdateCallback)
            m_UpdateCallback(deltaTime, this);
    }

    void GameObject::AddComponent(std::unique_ptr<Component> component) {
        m_Components.push_back(std::move(component));
    }

    void GameObject::SetUpdateCallback(std::function<void(float, GameObject*)>
        callback) {
        m_UpdateCallback = std::move(callback);
    }

    void GameObject::Render() {
        float pos[] = {
            m_Position.x, m_Position.y, m_Position.z
        };

        m_RendererObject.shader.SetUniformVec(
            "pos", 3, pos
        );
        Renderer::SubmitObject(m_RendererObject);
    }

    Quad::Quad(float sideLength, Vec3 pos, float rot)
        : GameObject(
            Renderer::GenQuad(
                new float[] {0,0,0},
                sideLength,
                "Assets/quad.vert",
                "Assets/quad.frag"
            ), pos, rot
        ), m_SideLength(sideLength)
    {}

    Circle::Circle(float radius, Vec3 pos, float rot)
        : GameObject(
        Renderer::GenQuad(
                new float[] {0,0,0},
                radius*2,
                "Assets/circle.vert",
                "Assets/circle.frag"
            ), pos, rot
        ), m_Radius(radius)
    {}

} // Engine