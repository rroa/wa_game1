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

		Ship::Ship(const std::vector<manifold> points)
			: m_ships(points)
			, m_currentIndex(0)
			, m_nRespawnTime(0)
		{

			m_radius = 10.0f;

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
				1.0f,
				0.999f
			);
			
			// Attaching physics component
			//
			AttachComponent(m_physics);

			// Trigger mass calculation
			//
			CalculateMass();
		}

		Ship::~Ship()
		{
			// Clear points allocation per model
			//
			for(auto model : m_ships)
			{
				model.clear();
			}

			// Clear ships collection
			//
			m_ships.clear();

			// Destroying base
			//
			Entity::~Entity();
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

		void Ship::ChangeShip()
		{
			m_currentIndex++;
			if (m_currentIndex > (m_ships.size() - 1))
			{
				m_currentIndex = 0;
			}

			CalculateMass();
		}

		void Ship::Update(float deltaTime)
		{
			// Clamp speed
			//
			float speed = fabs(m_physics->GetSpeed());
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
			if(!m_canCollide)
			{
				if(m_nRespawnTime == 120)
				{
					SetCollision(true);
					m_nRespawnTime = 0;
				}
				
				m_nRespawnTime++;
				Entity::Render(GL_LINE_LOOP, m_ships[m_currentIndex], Engine::Math::Vector3(1.0f, 0.0f, 0.0f));

				return;
			}
			
			// Draw ship
			Entity::Render(GL_LINE_LOOP, m_ships[m_currentIndex]);				
		}

		void Ship::Respawn()
		{
			SetCollision(false);
			m_transforms->Teleport(0.0f, 0.0f);
			m_transforms->ResetOrientation();
			m_physics->SetVelocity(Engine::Math::Vector2(0.f, 0.f));
		}

		void Ship::CalculateMass()
		{
			// Set the mass, proportional to the ship size (asumming points defines size)
			//
			m_physics->SetMass(m_ships[m_currentIndex].size() / 10.0f);
		}
	}
}
