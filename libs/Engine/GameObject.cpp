#include "GameObject.h"
#include <memory>
#include <utility>

namespace Engine
{

	GameObject::GameObject(RendererObject rendererObject, glm::vec3 pos,
						   float rot) :
		m_RendererObject(rendererObject),
		m_Position(pos), m_Rotation(rot)
	{
	}

	void GameObject::Move(glm::vec3 deltaPos, float deltaRot)
	{
		m_Position += deltaPos;
		m_Rotation += deltaRot;
	}

	void GameObject::Update(float deltaTime)
	{
		for (std::unique_ptr<Component> &comp : m_Components) {
			comp->UpdateComponent(deltaTime);
		}

		if (m_UpdateCallback) m_UpdateCallback(deltaTime, this);
	}

	void GameObject::AddComponent(std::unique_ptr<Component> component)
	{
		m_Components.push_back(std::move(component));
	}

	void GameObject::SetUpdateCallback(
		std::function<void(float, GameObject *)> callback)
	{
		m_UpdateCallback = std::move(callback);
	}

	void GameObject::Render()
	{
		m_RendererObject.shader->SetUniformVec(
			"pos", glm::vec3 {m_Position.x, m_Position.y, m_Position.z});
		Renderer::SubmitObject(m_RendererObject);
	}

	Quad::Quad(float sideLength, glm::vec3 pos, float rot, Shader *shader) :
		GameObject(Renderer::GenQuad({0, 0, 0}, sideLength, shader), pos, rot),
		m_SideLength(sideLength)
	{
	}

	Circle::Circle(float radius, glm::vec3 pos, float rot, Shader *shader) :
		GameObject(Renderer::GenQuad({0, 0, 0}, radius * 2, shader), pos, rot),
		m_Radius(radius)
	{
	}

}	 // namespace Engine