#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include <vector>

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
		void HandleInput();
		void Update(double deltaTime) const;
		void Render() const;
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void CreatePlayer();
		void CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position = Engine::Math::Vector2::Origin) const;
		void CreateDebris(Entities::Asteroid::AsteroidSize::Size previousSize, Engine::Math::Vector2 position) const;
		void CheckCollisions() const;
		void CheckCollisionWithPlayer(Entities::Asteroid* pAsteroid) const;
		void CheckCollisionWithBullets(Entities::Asteroid* pAsteroid);

		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;		
		Entities::Ship* m_player;
		std::vector<Entities::Bullet*> m_bullets;
	};
}

#endif /* _GAME_H_ */