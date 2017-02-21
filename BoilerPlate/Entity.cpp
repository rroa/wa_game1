#include "Entity.hpp"

#include <SDL2/SDL_opengl.h>

namespace Asteroids
{
	namespace Entities
	{
		Entity::Entity()
			: m_angleInRads(0)
		{
		}

		void Entity::Render(unsigned int mode, std::vector<Engine::Math::Vector2> points)
		{
			// Reset transformation matrix to identity
			//
			glLoadIdentity();

			// Translate
			//
			//glTranslatef(m_position.x, m_position.y, 0.0f);

			// Rotate
			//
			//glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

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