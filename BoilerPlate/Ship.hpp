#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

//
#include <vector>

//
#include "Vector2.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"

typedef std::vector<Engine::Math::Vector2> points_set;

namespace Asteroids
{
	namespace Entities
	{
		class Ship : public Entity
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			explicit Ship(const std::vector<points_set> ships);
			~Ship();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void MoveUp() const;
			void MoveRight() const;
			void MoveLeft() const;
			void ChangeShip();
			void Update(float deltaTime) override;
			void Render() override;
			void Respawn();
			Bullet* Shoot();
		private:
			void CalculateMass();
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			std::vector<points_set> m_ships;
			float m_currentSpeed;
			int	m_currentIndex;
			int m_nRespawnTime;
			bool m_pulse = false;
			int  m_currentPulseCount;
			int  m_totalPulseCount;
			Engine::Math::Vector3 m_currentColor;
		};
	}
}

#endif // !_SHIP_H_
