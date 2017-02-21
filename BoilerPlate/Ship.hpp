#pragma once
#ifndef _SHIP_H_
#define _SHIP_H_

//
#include <vector>

//
#include "Vector2.hpp"
#include "Entity.hpp"
#include "TransformationComponent.hpp"
#include "RigidBodyComponent.hpp"

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
			Ship(const std::vector<Engine::Math::Vector2> points, float mass = 1.0f);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void MoveUp() const;
			void MoveRight() const;
			void MoveLeft() const;
			void Update(float deltaTime) override;
			void Render() override;
		private:
			std::vector<Engine::Math::Vector2> m_points;
			Engine::Components::TransformationComponent* m_transforms;
			Engine::Components::RigidBodyComponent* m_physics;
			float m_currentSpeed;
		};
	}
}

#endif // !_SHIP_H_
