#include "Asteroid.hpp"
#include "Constants.hpp"
#include <SDL2/SDL_opengl.h>

namespace Asteroids
{
	namespace Entities
	{
		const size_t NUM_POINTS = 16;
		const float MIN_SIZE = 25.0f;
		const float MAX_SIZE = 45.0f;

		Asteroid::Asteroid(AsteroidSize::Size size)
			: m_size(size)
			, m_angle(0.0f)
			, m_rotation(120)
		{
			m_sizeFactor = (int)size + 1;

			// Calculating the MIN/MAX size of the asteroid based on the size enum value
			//
			float min = MIN_SIZE / m_sizeFactor;
			float max = MAX_SIZE / m_sizeFactor;

			//type = ASTEROID_PLAYERTYPE;

			for (size_t i = 0; i < NUM_POINTS; ++i)
			{
				const float radians = (i / static_cast<float>(NUM_POINTS)) * 2.0f * Engine::Math::PI;
				// TODO: RR: Move this to a rand in range function
				const float randDist = min + (max - min) * (rand() / static_cast<float>(RAND_MAX));

				m_points.push_back(Engine::Math::Vector2(sinf(radians) * randDist, cosf(radians) * randDist));
			}

			//m_radius = (min + max) * 0.5f;
		}

		void Asteroid::Update(float deltaTime)
		{
			// Rotate the asteroid.
			//
			m_angle += m_rotation * deltaTime;

			Entity::Update(deltaTime);
		}

		/*void Asteroid::ApplyImpulse(Engine::Math::Vector2 impulse)
		{*/
			/*if (m_mass > 0)
			{
				m_velocity.x += (impulse.x / m_mass) * cosf(m_rotation * (Engine::Math::PI / 180)) + m_sizeFactor;
				m_velocity.y += (impulse.y / m_mass) * sinf(m_rotation * (Engine::Math::PI / 180)) + m_sizeFactor;
			}*/
		//}

		Asteroid::AsteroidSize::Size Asteroid::GetSize() const
		{
			return m_size;
		}

		void Asteroid::Render()
		{
			/*glLoadIdentity();
			glTranslatef(m_position.x, m_position.y, 0.0f);
			glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

			glBegin(GL_LINE_LOOP);

			std::vector<Engine::Vector2>::iterator it = m_points.begin();
			for (; it != m_points.end(); ++it)
			{
				glVertex2f((*it).x, (*it).y);
			}

			glEnd();*/

			//glLoadIdentity();
			//DrawCircle(m_position.x, m_position.y, m_radius, 16);
		}

		void Asteroid::DrawCircle(float cx, float cy, float r, int num_segments)
		{
			float theta = 2 * 3.1415926 / float(num_segments);
			float tangetial_factor = tanf(theta);//calculate the tangential factor 

			float radial_factor = cosf(theta);//calculate the radial factor 

			float x = r;//we start at angle = 0 

			float y = 0;

			glBegin(GL_LINE_LOOP);
			for (int ii = 0; ii < num_segments; ii++)
			{
				glVertex2f(x + cx, y + cy);//output vertex 

										   //calculate the tangential vector 
										   //remember, the radial vector is (x, y) 
										   //to get the tangential vector we flip those coordinates and negate one of them 

				float tx = -y;
				float ty = x;

				//add the tangential vector 

				x += tx * tangetial_factor;
				y += ty * tangetial_factor;

				//correct using the radial factor 

				x *= radial_factor;
				y *= radial_factor;
			}
			glEnd();
		}
	}
}
