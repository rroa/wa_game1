#pragma once
#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_

#include "Component.hpp"
#include "Vector2.hpp"

namespace Engine
{
	namespace Components
	{
		class RigidBodyComponent : public Core::Component
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			RigidBodyComponent();
			RigidBodyComponent(Math::Vector2 gravity, Math::Vector2 position, float mass = 1.0f, float dragFactor = 1.0f);
			~RigidBodyComponent();
			
			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Update(float deltaTime) override;
			void AddForce(Math::Vector2 force);

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			float GetMass() const { return m_mass; }
			Math::Vector2 GetVelocity() const { return m_velocity; }
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			float m_mass;
			float m_drag;
			Math::Vector2 m_position;
			Math::Vector2 m_force;
			Math::Vector2 m_gravity;
			Math::Vector2 m_velocity;
		};
	}
}

#endif // !PHYSICS_COMPONENT_HPP