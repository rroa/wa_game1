#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.hpp"

namespace  Asteroids
{
	namespace Entities
	{
		class Bullet : public Entity
		{
		public:
			/* =============================================================
			* CTOR
			* ============================================================= */
			Bullet(Engine::Math::Vector2 position, Engine::Math::Vector2 velocity, float angle);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			void Render() override;
		};
	}
}

#endif // !_BULLET_H_