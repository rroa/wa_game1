#include "Ship.hpp"
#include <SDL2\SDL_opengl.h>

//
#include <cmath>
#include "MathUtilities.hpp"

namespace Asteroids
{
	namespace Entities
	{
		const float ANGLE_OFFSET = 90.0f;
		const float THRUST = 3.0f;
		const float MAX_SPEED = 350.0f;
		const float ROTATION_SPEED = 5.0f;

		Ship::Ship(const std::vector<Engine::Math::Vector2> points, float mass)
			: m_points(points)
		{
			// Transforms
			//
			m_transforms = new Engine::Components::TransformationComponent();

			// Attaching transformation component
			//
			AttachComponent(m_transforms);

			// Physics
			//
			m_physics = new Engine::Components::RigidBodyComponent(
				Engine::Math::Vector2(0.0f),
				m_transforms->GetPosition(),
				mass,
				0.999f
			);
			
			// Attaching physics component
			//
			AttachComponent(m_physics);
		}

		void Ship::MoveUp() const
		{			
			m_physics->ApplyForce(
				Engine::Math::Vector2(THRUST), 
				m_transforms->GetAngleIRadians() + Engine::Math::DegreesToRadians(ANGLE_OFFSET)
			);
		}

		void Ship::MoveRight() const
		{
			m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() - ROTATION_SPEED);
		}

		void Ship::MoveLeft() const
		{
			m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() + ROTATION_SPEED);
		}

		void Ship::Update(float deltaTime)
		{
			// Clamp speed
			//
			float speed = fabs(m_physics->GetVelocity().Length());
			if (speed > MAX_SPEED)
			{
				m_physics->SetVelocity(
					Engine::Math::Vector2(
						(m_physics->GetVelocity().x / speed) * MAX_SPEED,
						(m_physics->GetVelocity().y / speed) * MAX_SPEED
					)
				);

				m_currentSpeed = fabs(m_physics->GetVelocity().Length());
			}

			Entity::Update(deltaTime);
		}

		void Ship::Render()
		{
			Entity::Render(GL_LINE_LOOP, m_points);
		}
	}
}
