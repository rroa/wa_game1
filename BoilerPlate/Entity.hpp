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
			void Update(float delta) override;
			void Render(unsigned int mode, std::vector<Engine::Math::Vector2> points);
		private:
			float m_halfWidth;
			float m_halfHeight;
		};
	}
}

#endif // !_ENTITY_H_
