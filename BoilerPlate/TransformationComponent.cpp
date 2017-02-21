#include "TransformationComponent.hpp"

namespace Engine
{
	namespace Components
	{
		const std::string COMP_NAME = "TRANSFORMATION_COMPONENT";

		TransformationComponent::TransformationComponent()
			: Component(COMP_NAME)
		    , m_angle(0)
		{
		}

		TransformationComponent::~TransformationComponent()
		{}

		void TransformationComponent::Teleport(float x, float y)
		{
			m_position.x = x;
			m_position.y = y;
		}

		void TransformationComponent::Teleport(Math::Vector2 newPosition)
		{
			m_position = newPosition;
		}
	}
}