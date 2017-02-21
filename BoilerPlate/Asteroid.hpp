#pragma once
#ifndef _ASTEROID_H_
#define _ASTEROID_H_

// STL
#include <vector>

// Asteroids
#include "Vector2.hpp"
#include "Entity.hpp"

namespace Asteroids
{
	namespace  Entities
	{
		class Asteroid : public Entities::Entity
		{
		public:
			/* =============================================================
			* ENUMERATORS
			* ============================================================= */
			struct AsteroidSize
			{
				enum Size
				{
					BIG = 0,
					MEDIUM = 1,
					SMALL = 2,
				};
			};

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			explicit Asteroid(AsteroidSize::Size size);
			void Update(float deltaTime) override;
			void Render() override;
			AsteroidSize::Size GetSize() const;
		private:
			void DrawCircle(float cx, float cy, float r, int num_segments);
			std::vector<Engine::Math::Vector2>    m_points;
			AsteroidSize::Size				m_size;
			int								m_sizeFactor;
			float							m_angle;
			float							m_rotation;
		};
	}	
}

#endif // !_ASTEROID_H_