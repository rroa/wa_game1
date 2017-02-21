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

		const float ANGLE_OFFSET = 90.0f;
		const float THRUST = 3.0f;
		const float MAX_SPEED = 350.0f;
		const float DRAG = 0.999f;
		const int WIDTH = 1136;
		const int HEIGHT = 640;

		Ship::Ship(const std::vector<Engine::Math::Vector2> points)
			: m_points(points)
			, m_mass(0.5f)
		{
			//m_angle = 0.0f;
			m_angleInRads = ANGLE_OFFSET * (Engine::Math::PI / 180);
		}

		void Ship::MoveUp()
		{
			// Calculate impulse
			//
			if (m_mass > 0)
			{				
				float x = (THRUST / m_mass) * std::cosf(m_angleInRads);
				float y = (THRUST / m_mass) * std::sinf(m_angleInRads);
				m_velocity += Engine::Math::Vector2(x, y);
			}
		}

		void Ship::MoveRight()
		{
			/*m_angle -= 5.0f;
			m_angleInRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);*/
		}

		void Ship::MoveLeft()
		{
			/*m_angle += 5.0f;
			m_angleInRads = (m_angle + ANGLE_OFFSET) * (Engine::Math::PI / 180);*/
		}

		void Ship::Update(float delta)
		{
			//// Clamp speed
			////
			//float speed = std::fabs(m_velocity.Length());
			//if (speed > MAX_SPEED)
			//{
			//	m_velocity = Engine::Math::Vector2(
			//		(m_velocity.x / speed) * MAX_SPEED,
			//		(m_velocity.y / speed) * MAX_SPEED
			//		);

			//	speed = std::fabs(m_velocity.Length());
			//}

			//// Apply drag
			////
			//m_velocity = Engine::Math::Vector2(
			//	m_velocity.x * DRAG,
			//	m_velocity.y * DRAG
			//	);


			//// New position
			////
			//Engine::Math::Vector2 newPos(
			//	m_position.x + (m_velocity.x * delta),
			//	m_position.y + (m_velocity.y * delta)
			//);
			//	/*m_position + m_velocity;*/

			//float halfWidth = (WIDTH / 2.0f);
			//float halfHeight = (HEIGHT / 2.0f);

			//float worldMinX = -halfWidth;
			//float worldMaxX = halfWidth;

			//float worldMinY = -halfHeight;
			//float worldMaxY = halfHeight;

			//// Wrap!
			//float x = wrap(newPos.x, worldMinX, worldMaxX);
			//float y = wrap(newPos.y, worldMinY, worldMaxY);

			//newPos = Engine::Math::Vector2(x, y);

			//Entity::Translate(newPos);
		}

		void Ship::Render()
		{
			Entity::Render(GL_LINE_LOOP, m_points);
		}
	}
}