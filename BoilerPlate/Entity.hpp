#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

// STDLIB
#include <vector>

// ENGINE
#include "Vector2.hpp"
#include "GameObject.hpp"
#include "TransformationComponent.hpp"
#include "RigidBodyComponent.hpp"

namespace Asteroids
{
	namespace Entities
	{
		class Entity : public Engine::Core::GameObject
		{
		public:
			/* =============================================================
			* ENUMERATORS
			* ============================================================= */
			struct EntityState
			{
				enum State
				{
					NORMAL = 0,
					COLLIDED = 1,
					DELETED = 2,
				};
			};

			/* =============================================================
			* CTOR
			* ============================================================= */
			Entity();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Update(double delta) override;
			void Render(unsigned int mode, std::vector<Engine::Math::Vector2> points, Engine::Math::Vector3 color = Engine::Math::Vector3(1.0));
			
			// TODO: RR: Move out to rigid body component
			//
			bool IsColliding(Entity* rhs);
			bool CanCollide() const { return m_canCollide; }
			void SetCollision(bool canCollide) { m_canCollide = canCollide; }

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			Engine::Math::Vector2 GetPosition() const { return m_transforms->GetPosition(); };
		protected:
			/* =============================================================
			* PROTECTED MEMBERS
			* ============================================================= */
			Engine::Components::TransformationComponent* m_transforms;
			Engine::Components::RigidBodyComponent* m_physics;
			EntityState::State m_state;
			float m_radius; // TODO: RR: Move this to rigid body component
			bool m_canCollide; // TODO: RR: Move this to rigid body component
		private:
			/* =============================================================
			* PRIVATE MEMBERS
			* ============================================================= */
			float m_sceneHalfWidth;
			float m_sceneHalfHeight;
		};
	}
}

#endif // !_ENTITY_H_
