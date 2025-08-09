#pragma once

namespace Engine {

    class GameObject;

    class Component {
    protected:
        Component(GameObject *owner);

    public:
        virtual void UpdateComponent(float deltaTime) {};

    protected:
        GameObject *m_Owner;
    };

} // Engine
