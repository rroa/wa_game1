#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <list>

#include "Scene.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"

namespace Asteroids
{
	class Game
	{
	public:
		/* =============================================================
		* CTOR
		* ============================================================= */
		Game(int width, int height);
		~Game();

		/* =============================================================
		* PUBLIC FUNCTIONS
		* ============================================================= */
		void Init();
		void Update(double deltaTime);
		void Render() const;
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void HandleInput();
		void CreatePlayer();
		void CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position = Engine::Math::Vector2::Origin) const;
		void CreateDebris(Entities::Asteroid* currentAsteroid) const;
		void CleanDeadUpBullets();
		void CheckCollisions();
		void CheckCollisionWithPlayer(Entities::Asteroid* pAsteroid) const;
		void CheckCollisionWithBullets(Entities::Asteroid* pAsteroid);
		void DestroyBullet(Entities::Bullet* bulletToDestroy);

		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;		
		Entities::Ship* m_player;
		std::list<Entities::Bullet*> m_bullets;
	};
}

#endif /* _GAME_H_ */