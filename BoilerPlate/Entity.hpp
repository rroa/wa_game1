#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

// STDLIB
#include <vector>

// ENGINE
#include "Vector2.hpp"
#include "GameObject.hpp"

namespace Asteroids
{
	namespace Entities
	{
		class Entity : public Engine::Core::GameObject
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			Entity();

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Render(unsigned int mode, std::vector<Engine::Math::Vector2> points);
		protected:
			float m_angleInRads;
		};
	}
}

#endif // !_ENTITY_H_
