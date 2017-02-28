#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "Scene.hpp"
#include "Ship.hpp"
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
		void Update(double deltaTime) const;
		void Render() const;
	private:
		/* =============================================================
		* PRIVATE FUNCTIONS
		* ============================================================= */
		void HandleInput() const;
		void CreatePlayer();
		void CreateAsteroids(int amount, Entities::Asteroid::AsteroidSize::Size size, Engine::Math::Vector2 position = Engine::Math::Vector2::Origin) const;
		void CreateDebris(Entities::Asteroid::AsteroidSize::Size previousSize, Engine::Math::Vector2 position) const;
		void CheckCollisions() const;

		/* =============================================================
		* MEMBERS
		* ============================================================= */
		Entities::Scene* m_scene;
		int m_width;
		int m_height;		
		Entities::Ship* m_player;
		std::vector<Entities::Ship*> m_ships;
	};
}

#endif /* _GAME_H_ */