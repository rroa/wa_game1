#include "Bullet.hpp"

//
#include <SDL2/SDL_opengl.h>

namespace  Asteroids
{
	namespace Entities
	{
		Bullet::Bullet(Engine::Math::Vector2 position, Engine::Math::Vector2 velocity, float angle)
		{
			m_radius = 1.0f;

			// Transforms
			//
			m_transforms = new Engine::Components::TransformationComponent();

			// Apply initial transforms
			//
			m_transforms->Teleport(position);
			m_transforms->RotateInDegrees(angle);

			// Attaching transformation component
			//
			AttachComponent(m_transforms);

			// Physics
			//
			m_physics = new Engine::Components::RigidBodyComponent(
				Engine::Math::Vector2(0.0f),
				m_transforms->GetPosition()
			);

			// Attaching physics component
			//
			AttachComponent(m_physics);

			// Apply initial velocity
			//
			m_physics->ApplyForce(velocity);
		}

		void Bullet::Render()
		{
			// TODO: RR: Move this out to a renderer
			//
			glLoadIdentity();

			glPointSize(2.0f);

			glEnable(GL_POINT_SMOOTH);

			glBegin(GL_POINTS);

			glVertex2f(m_transforms->GetPosition().x, m_transforms->GetPosition().y);

			glEnd();
		}
	}
}