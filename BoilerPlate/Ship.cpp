#include "Ship.hpp"
#include <SDL2\SDL_opengl.h>

//
#include <cmath>

//
#include "Constants.hpp"


namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;

		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points)
		{
			m_angle = 0.0f;
			m_angleInRads = ANGLE_OFFSET * (Engine::Math::PI / 180);
		}

		void Ship::MoveUp()
		{
			Engine::Math::Vector2 velocity(
				10 * std::cosf(m_angleInRads), 
				10 * std::sinf(m_angleInRads)
				);
			
			Engine::Math::Vector2 newPos =
				m_position + velocity;

			Entity::Translate(newPos);
		}

		void Ship::MoveRight()
		{
			m_angle -= 5.0f;
			m_angleInRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);
		}

		void Ship::MoveLeft()
		{
			m_angle += 5.0f;
			m_angleInRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);
		}

		void Ship::Draw()
		{
			Entity::Draw(GL_LINE_LOOP, m_points);
		}
	}
}