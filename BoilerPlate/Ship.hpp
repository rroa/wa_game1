#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

//
#include <vector>

//
#include "Vector2.hpp"
#include "Entity.hpp"

typedef std::vector<Engine::Math::Vector2> models;

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
			Ship(const std::vector<models> ships);
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
		private:
			void CalculateMass();
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			std::vector<models> m_ships;
			float m_currentSpeed;
			int	m_currentIndex;
		};
	}
}

#endif // !_SHIP_H_
