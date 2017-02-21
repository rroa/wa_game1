#include "Entity.hpp"

#include <SDL2/SDL_opengl.h>
#include "Scene.hpp"
#include "RigidBodyComponent.hpp"
#include "TransformationComponent.hpp"

namespace Asteroids
{
	namespace Entities
	{
		inline float wrap(float axis, float min, float max)
		{
			if (axis < min)
			{
				return max - (min - axis);
			}

			if (axis > max)
			{
				return min + (axis - max);
			}

			return axis;
		}

		Entity::Entity()
			: m_transforms(nullptr)
		    , m_physics(nullptr)
		    , m_halfWidth(0)
			, m_halfHeight(0)
		{}

		void Entity::Update(float deltaTime)
		{
			if (!GetParent()) return;

			Scene* scene = dynamic_cast<Scene*>(GetParent());
			if (!scene) return;

			m_halfWidth = (scene->GetWidth() / 2.0f);
			m_halfHeight = (scene->GetHeight() / 2.0f);

			if (!m_physics || !m_transforms) return;

			// Time stepping the position
			//
			Engine::Math::Vector2 newPos(
				m_transforms->GetPosition().x + (m_physics->GetVelocity().x * deltaTime),
				m_transforms->GetPosition().y + (m_physics->GetVelocity().y * deltaTime)
			);

			// Getting axis limits
			//
			float worldMinX = -m_halfWidth;
			float worldMaxX = m_halfWidth;

			float worldMinY = -m_halfHeight;
			float worldMaxY = m_halfHeight;

			// Wrap!
			float x = wrap(newPos.x, worldMinX, worldMaxX);
			float y = wrap(newPos.y, worldMinY, worldMaxY);

			// Set the new position
			m_transforms->Teleport(x, y);

			// Base update
			//
			GameObject::Update(deltaTime);
		}

		void Entity::Render(unsigned int mode, std::vector<Engine::Math::Vector2> points)
		{
			Engine::Components::TransformationComponent* transforms = GetComponent<Engine::Components::TransformationComponent>();
			if (!transforms) return;

			// Reset transformation matrix to identity
			//
			glLoadIdentity();

			// Translate
			//
			glTranslatef(transforms->GetPosition().x, transforms->GetPosition().y, 0.0f);

			// Rotate
			//
			glRotatef(transforms->GetAngleInDegrees(), 0.0f, 0.0f, 1.0f);

			// Draw
			//
			glBegin(mode);
				for (auto point : points)
				{
					glVertex2f(point.x, point.y);
				}
			glEnd();

			// Call base class render
			//
			GameObject::Render();
		}
	}
}
