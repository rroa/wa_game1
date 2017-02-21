#pragma once
#ifndef _TRANSFORMATION_COMPONENT_H_
#define _TRANSFORMATION_COMPONENT_H_

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Component.hpp"

namespace Engine
{
	namespace Components
	{
		class TransformationComponent : public Core::Component
		{
		public:
			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			TransformationComponent();
			~TransformationComponent();
			void Teleport(float x, float y);
			void Teleport(Math::Vector2 newPosition);

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			Math::Vector2 GetPosition() const { return m_position; }
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			Math::Vector2 m_position;
			Math::Vector3 m_rotation;
			float m_angle;
		};
	}
}

#endif // !_TRANSFORMATION_COMPONENT_H_